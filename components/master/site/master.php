<?php

// WebAbility(r) v6
// master.php / Main Master index
// WRAPPER TO MASTER DISPATCHER
// Ing. Philippe Thomassigny (c) 2001-2017

error_reporting(E_ALL);
ini_set('display_errors', true);
set_time_limit(600);  // 10 minutes max, some databases are very slow...
// We fix something until we get the user needs by config to avoid date warnings
setlocale(LC_ALL, 'es_MX.UTF8', 'es_MX', '');
date_default_timezone_set('America/Mexico_City');

Header('Cache-Control: must-revalidate');
Header('Expires: ' . gmdate('D, d M Y H:i:s', time() - 86400) . ' GMT'); // today - 24h, we do NOT cache anything

// We regenerate the master if needed (outside cannot interfere)
$install = isset($_GET['install'])?$_GET['install']:null;
if ($install == 'do')
{
  // This action only regenerates master.php and master.js.php and is harmless if anybody call this function, it does not have any interaction with external user, but is used to regerate the paths in the files
  // dont need to delete all, only a file is enough so install will regenerate the good wrappers
  @unlink('master.js.php');
  header('Location: /install.php');
  die();
}

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
$INDEXPHP = 'master';
$JSPHP = 'master.js.php';

set_include_path('.'.PATH_SEPARATOR.$BASEDIR.'include');

// implements autoload && special getBaseDir function
include_once '__autoload.lib';

$SHOW_EXCEPTION = $SHOW_OB = 3;

// We redirect if we are in .php mode: the .htaccess is provided for seo URLs
if (isset($_SERVER['REQUEST_URI']))
{
  $URI = strtolower($_SERVER['REQUEST_URI']);
  if ($URI)
  {
    if (substr($URI, 0, 11) == '/master.php')
    {
      header('Location: /master' . substr($URI, 11));
      return;
    }
  }
}

// we setup some variables we need
$URI = $QUERY = $HASH = $BASE_P = $config = null;

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
if (substr($BASE_P, 0, 7) != '/master')
  $BASE_P = null;
else
  $BASE_P = substr($BASE_P, 7);

\core\WAMessage::addMessages(array(
  'master.critical' => 'Critical Error: There is no language installed. Please contact the administrator.',
  'master.updatemissing' => 'Error: There is a consistance error in the Master, The file needed to update the system is missing. Please contact your administrator.',
  'master.updated' => 'Master site updated. Reload the page.',
  'master.reload' => 'Click here if the page is not automatically reloaded',
  'master.noaccess' => 'Error: You do not have access to this library.'
  )
);

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

  if (!file_exists($REPOSITORYDIR.'base.conf') || !file_exists($REPOSITORYDIR.'master.conf'))
  {
    // default extended right, changeable once the master is installed
    \core\WAFile::setDirMask(0755);
    \core\WAFile::setFileMask(0644);

    // Main Dev. Framework dispatcher
    $base = new \common\BaseMaster(
      new \xconfig\XConfig(array('entries' => array('BASEDIR' => $BASEDIR,
            'REPOSITORYDIR' => $REPOSITORYDIR,
            'PAGESDIR' => $BASEDIR . 'application/',
            'PAGESCONTAINER' => 'pagesmaster/',
            'acceptpathparameters' => 'yes'
            ))));
    $base->mainpage = 'preinstall';

    // personalize the script
    if (file_exists('./install.script.php'))
    {
      require 'install.script.php';
      if (isset($forcelanguage))
        $base->HTTPRequest->setParameterPost('LANGUAGE', $forcelanguage);
      if (isset($forcecountry))
        $base->HTTPRequest->setParameterPost('COUNTRY', $forcecountry);
    }

    $knownlanguages = $base->getLocalLanguages();
    $firstlanguage = current($knownlanguages);
    if (!$firstlanguage)
    {
      throw new \throwables\masterError(WAMessage::getMessage('master.critical1'));
    }

    // we get the language and the country (if already set)
    $LANGUAGE = $base->HTTPRequest->getParameter('LANGUAGE', \xamboo\Validator::SET, $knownlanguages);
    if (!$LANGUAGE)
      $LANGUAGE = $firstlanguage;   // get local installed language

    // we set current defaults
    $base->Language = $LANGUAGE;
    \core\WAMessage::setMessagesFile($BASEDIR.'components/static/'.$base->Language.'.xml');

    // Call the engine with the page
    $engine = new \xamboo\engine($URI);
    $code = $engine->run($BASE_P);
    if ($code instanceof \core\WATemplate)
      $code = $code->resolve();
    $code = str_replace(array('__SKIN__', '__INDEXPHP__', '__JSPHP__'), array('master', $INDEXPHP, $JSPHP), $code);

    $ob = ob_get_contents();
    ob_end_clean();

    $obshow = $ob?showlog_string($SHOW_OB, $ob):null;

    print $code;
    print $obshow;

    return; // gracefull end
  }
  
  $config = new \xconfig\XConfig(file_get_contents($REPOSITORYDIR.'base.conf'));
  $master = new \xconfig\XConfig(file_get_contents($REPOSITORYDIR.'master.conf'));
  $config->merge($master);

  setlocale(LC_ALL, $config['locale']);
  date_default_timezone_set($config['timezone']);
  \core\WAFile::setDirMask($config['defdirmask']);
  \core\WAFile::setFileMask($config['deffilemask']);
  
  // =============================================================================================
  // IF WE ARE HERE, MEANS THE MASTER IS INSTALLED.

  // The variable $Master MUST exists when creating the base object
  // $Master variable contains the master AFO (username, password, language, basedirs)
  $pleaselogin = false;

  $base = new \common\BaseMaster($config);

  \core\WAMessage::setMessagesFile($base->config->BASEDIR.'components/static/'.$base->Language.'.xml');

  // check the version if any upgrade available
  if (!isset($config->version) || $config->version != \common\BASE::VERSION)
  {
    // need upgrade
    $ob = ob_get_contents();
    ob_end_clean();

    $up = new \install\upgrade();
    $res = $up->upgrade($config->version);
    if ($res === true)
    {
      print \core\WAMessage::getMessage('master.updated') . '<a href="/master.php">' . \core\WAMessage::getMessage('master.reload') . '</a><br />';
      $config->version = \common\BASE::VERSION;
//      $base->writeFastObject(null, 'master', $config);
// ****************** REWRITE GOOD VERSION INTO CONFIG FILES


    }
    else
      print $res;
    return;
  }

  if (isset($_GET['OrderSecurity']) && $_GET['OrderSecurity'] == 'Disconnect')
  {
    header('Location: /'.$INDEXPHP);
    return;
  }

  // we check if the security is OK
  // 2 posibilities: 1. Not connected. ask for the main screen and login
  //                 2. Master connected, ask for any app, json, etc.
  // There are only 2 pages that can enter without session: /master and /master/mastermain
  if (!$base->user)
  {
    if ($URI != '/master' && substr($URI, 0, 19) != '/master/mastermain/')
    {
      $json = true;
      $pleaselogin = true;
      throw new \core\WAException(\core\WAMessage::getMessage('master.noaccess').' '.$URI);
    }
  }

  // Call the engine with the page
  $engine = new \xamboo\engine($URI);
  $code = $engine->run($BASE_P);
  if ($code instanceof \core\WATemplate)
    $code = $code->resolve();
  $code = str_replace(array('__SKIN__', '__INDEXPHP__', '__JSPHP__'), array('master', $INDEXPHP, $JSPHP), $code);

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
      $mess = '{"error":true,"login":true}';
    else
    {
      $mess = '';
      if ($ob && $SHOW_OB > 0)
        $mess .= showlog_string($SHOW_OB, $ob);
      if ($SHOW_EXCEPTION > 0)
        $mess .= showlog_string($SHOW_EXCEPTION, $exception->__toString());
      $mess = '{"error":true,"login":false,"messages":'."'".str_replace(array("\\", "'", "\r", "\n"), array("\\\\", "\\'", "", "\\n"), $mess)."'}";
    }
    print $mess;
  }
  else
  {
    if ($SHOW_OB >= 2 || $SHOW_EXCEPTION >= 2)
    {
      print <<<EOF
  <?xml version="1.0" encoding="UTF-8"?>
  <!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
  <html>
  <head>
    <meta name="Master" content="WebAbility(r) v5 - www.webability.info - (c) 1999-2012, Ing. Philippe Thomassigny C." />
    <meta name="Component" content="Master Engine - Exception Manager" />
    <meta http-equiv="PRAGMA" content="NO-CACHE" />
    <meta http-equiv="Expires" content="-1" />
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
  </head>
  <body>
EOF;
    }

    if ($ob && $SHOW_OB > 0)
      print showlog_string($SHOW_OB, $ob);

    if ($SHOW_EXCEPTION > 0)
      print showlog_string($SHOW_EXCEPTION, $exception->__toString());

    if ($SHOW_OB >= 2 || $SHOW_EXCEPTION >= 2)
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