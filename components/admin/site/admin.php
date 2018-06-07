<?php

// WebAbility(r) v6
// admin.php / Main admin index
// WRAPPER TO ADMIN DISPATCHER
// Ing. Philippe Thomassigny (c) 2001-2015

error_reporting(E_ALL);
ini_set('display_errors', true);
set_time_limit(600);  // 10 minutes max, some databases are very slow...
// We fix something until we get the user needs by config to avoid date warnings
setlocale(LC_ALL, 'es_MX.UTF8', 'es_MX', '');
date_default_timezone_set('America/Mexico_City');

Header('Cache-Control: must-revalidate');
Header('Expires: ' . gmdate('D, d M Y H:i:s', time() - 86400) . ' GMT'); // today - 24h, we do NOT cache anything

if (isset($_SERVER['WINDIR']))
{
  $BASEDRIVE       = '__BASEDRIVE__';
  $REPOSITORYDRIVE = '__REPOSITORYDRIVE__';
}
else
{
  $BASEDRIVE = $REPOSITORYDRIVE = '';
}

global $BASEDIR, $REPOSITORYDIR, $INDEXPHP, $JSPHP;
$BASEDIR       = $BASEDRIVE       . '__BASEDIR__';
$REPOSITORYDIR = $REPOSITORYDRIVE . '__REPOSITORYDIR__';
$INDEXPHP = 'admin';
$JSPHP = 'admin.js.php';

set_include_path('.'.PATH_SEPARATOR.$BASEDIR.'/include');

// implements autoload && special getBaseDir function
include_once '__autoload.lib';

$SHOW_EXCEPTION = $SHOW_OB = 3;

// We redirect if we are in .php mode: the .htaccess is provided for seo URLs
if (isset($_SERVER['REQUEST_URI']))
{
  $URI = strtolower($_SERVER['REQUEST_URI']);
  if ($URI)
  {
    if (substr($URI, 0, 11) == '/admin.php')
    {
      header('Location: /admin' . substr($URI, 11));
      return;
    }
  }
}

// we setup some variables we need
$URI = $QUERY = $HASH = $BASE_P = $Master = null;

if (isset($_SERVER['REQUEST_URI']))
  $URI = strtolower($_SERVER['REQUEST_URI']);
if ($URI)
{
  // Remove query part (already managed by PHP) and hash part
  if (strpos($URI, '#') !== false)
  {
    $HASH = substr($URI, strpos($URI, '#'));
    $URI = substr($URI, 0, strpos($URI, '#'));
  }
  if (strpos($URI, '?') !== false)
  {
    $QUERY = substr($URI, strpos($URI, '?'));
    $URI = substr($URI, 0, strpos($URI, '?'));
  }
  if (substr($URI, -1) == '/' && strlen($URI) > 1)
  {
    // NO ACEPTAMOS URLS QUE TERMINAN CON /, REDIRECCIONAMOS !!
    $URI = substr($URI, 0, -1);
    header('HTTP/1.1 301 Moved Permanently');
    header('Location: ' . $URI . $QUERY . $HASH);
    return;
  }
  if (strlen($URI) > 1)
    $BASE_P = $URI;
}
if (substr($BASE_P, 0, 6) != '/admin')
  $BASE_P = null;
else
  $BASE_P = substr($BASE_P, 6);

try
{
  /* Special error handler for PHP < 7 */
  function WAErrorHandler($errno, $errstr, $errfile, $errline)
  {
    throw new \common\WAError($errstr);
  }
  set_error_handler('WAErrorHandler', E_ERROR);
  
  $errors = null;
  ob_start();

  if (!file_exists($REPOSITORYDIR.'base.conf'))
    throw new \core\WAError('Error: there is no base configuration file.');
  if (!file_exists($REPOSITORYDIR.'admin.conf'))
    throw new \core\WAError('Error: there is no admin configuration file.');

  $config = new \xconfig\XConfig(file_get_contents($REPOSITORYDIR.'base.conf'));
  $admin = new \xconfig\XConfig(file_get_contents($REPOSITORYDIR.'admin.conf'));
  $config->merge($admin);

  setlocale(LC_ALL, $config['locale']);
  date_default_timezone_set($config['timezone']);
  \core\WAFile::setDirMask($config['defdirmask']);
  \core\WAFile::setFileMask($config['deffilemask']);
  set_time_limit($config['timelimit']);
  
/*
  $SHOW_EXCEPTION = $config["exception"];
  $SHOW_OB = $config["ob"];
  if ($config["debug"])
  {
    \core\WADebug::setDebug($config["debug"]);
    \core\WADebug::setLevel($config["level"]);
    \core\WADebug::setRedirect($config["redirect"], $config["file"]);
  }
*/

  $BASE_MIE = microtime();

  $pleaselogin = false;

  // we create the base object
  $base = new \common\BaseAdmin($config);

  \core\WAMessage::setMessagesFile($base->config->BASEDIR.'/components/static/'.$base->Language.'.xml');

  if (isset($_GET['OrderSecurity']) && $_GET['OrderSecurity'] == 'Disconnect')
  {
    // $base already disconnected us
    header('Location: /'.$INDEXPHP);
    return;
  }

  // we check if the security is OK
  // 2 posibilities: 1. Not connected. ask for the main screen and login
  //                 2. Master connected, ask for any app, json, etc.

  if (!$base->user)
  {
    if ($URI != '/admin' && substr($URI, 0, 17) != '/admin/adminmain/')
    {
      $pleaselogin = true;
      throw new \throwables\adminError(\core\WAMessage::getMessage('admin.noaccess').' '.$URI);
    }
  }

  $engine = new \xamboo\engine($URI);
  $code = $engine->run($BASE_P);
  if ($code instanceof \core\WATemplate)
    $code = $code->resolve();
  $code = str_replace(array('__SKIN__', '__INDEXPHP__', '__JSPHP__'), array('admin', $INDEXPHP, $JSPHP), $code);

  $ob = ob_get_contents();
  ob_end_clean();

  $obshow = $ob?showlog_string($SHOW_OB, $ob):null;

  print $code;
  print $obshow;

  return; // gracefull end
}
catch (\Exception $exception)
{
  $ob = ob_get_contents();
  ob_end_clean();

  // the way to throw the error depends on the asked page: json: send a json object, other: send normal page object
  // 1. get the protocol
  $json = false;
  if (substr($URI, -4) == 'json')
    $json = true;

  if ($json)
  {
    // we notify a necesary login
    if ($pleaselogin)
      $mess = '{error:true,login:true}';
    else
    {
      $mess = '';
      if ($ob && $SHOW_OB > 0)
        $mess .= showlog_string($SHOW_EXCEPTION, $exception);
      if ($SHOW_EXCEPTION > 0)
        $mess .= showlog_string($SHOW_EXCEPTION, $exception);
      $mess = '{"error":true,"login":false,"message":'."'".str_replace(array("\\", "'", "\r", "\n"), array("\\\\", "\\'", "", "\\n"), $mess)."'}";
    }
    print $mess;
  }
  else
  {
    if (($SHOW_OB >= 2 || $SHOW_EXCEPTION >= 2))
    {
      print <<<EOF
  <?xml version="1.0" encoding="UTF-8"?>
  <!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
  <html>
  <head>
    <meta name="Generator" content="WebAbility(r) v4 - www.webability.info - (c) 1999-2008, Ing. Philippe Thomassigny C." />
    <meta name="Component" content="Admin Engine - Exception Manager" />
    <meta http-equiv="PRAGMA" content="NO-CACHE" />
    <meta http-equiv="Expires" content="-1" />
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
  </head>
  <body>
EOF;
    }

    if ($ob && $SHOW_OB > 0)
      print showlog_string($SHOW_EXCEPTION, $ob);

    if ($SHOW_EXCEPTION > 0)
      print showlog_string($SHOW_EXCEPTION, $exception->__toString());

    if (($SHOW_OB >= 2 || $SHOW_EXCEPTION >= 2))
    {
      print <<<EOF
  </body>
  </html>
EOF;
    }
  }
}
catch (\Error $error)
{
  print "Uncatchable Error: " . $error; 
}

function showlog_string($SHOW, $str)
{
  global $REPOSITORYDIR;

  if ($SHOW == 1 || $SHOW == 3)
  {
    \core\WAFile::createDirectory($REPOSITORYDIR, 'logs');
    $str = "\n" . date('H:i:s', time()) . ' - ' . $str;
    $fname = $REPOSITORYDIR.'logs/log_'.date('Y-m-d', time()).'.log';
    $fp = fopen($fname, 'at');
    fwrite($fp, $str);
    fclose($fp);
  }
  if ($SHOW >= 2)
    return $str;
  return null;
}

?>