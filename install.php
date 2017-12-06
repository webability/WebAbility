<?php

// WebAbility(r) v.6
// install.php / Main Installer index
// Ing. Philippe Thomassigny (c) 2001-2017

error_reporting(E_ALL);
ini_set('display_errors', true);
set_time_limit(600);  // 10 minutes max, some systems are very slow...

Header('Cache-Control: must-revalidate');
Header('Expires: ' . gmdate('D, d M Y H:i:s', time() - 86400) . ' GMT'); // today - 24h, we do NOT cache anything

// personalize the script
$availablelanguages = array('en' => 'English', 'es' => 'Español', 'fr' => 'Français');
$defaultlanguage = 'en';
$extralanguages = array();
$messages = array();
global $messages;

if (file_exists('./install.script.php'))
{
  require 'install.script.php';
}
setMessages($extralanguages);

// we check PHP version 5.3 at least
if (!defined('PHP_VERSION_ID'))
{
  $version = explode('.', PHP_VERSION);
  define('PHP_VERSION_ID', ($version[0] * 10000 + $version[1] * 100 + $version[2]));
}

if (PHP_VERSION_ID < 50300)
{
  $message = getMessage('error.php53');
  print getHeader() . implode('<br /><br />', $message) . getFooter();
  return;
}

// basic check of:
// XML, mandatory
// SHM, GD, recommended
$SHARED = $GD = $XML = false;
if (function_exists('simplexml_load_string'))
  $XML = true;

if (!$XML)
{
  $message = getMessage('error.xml');
  print getHeader() . implode('<br /><br />', $message) . getFooter();
  return;
}

if (function_exists('sem_get'))
  $SHARED = true;
if (function_exists('imagecreate'))
  $GD = true;
$confirmed = isset($_GET['confirmed']);

if (!$confirmed && (!$SHARED || !$GD))
{
  print getHeader();
  if (!$SHARED)
  {
    $message = getMessage('error.shared');
    print implode('<br /><br />', $message);
  }
  if (!$GD)
  {
    $message = getMessage('error.gd');
    print implode('<br /><br />', $message);
  }
  $message = getMessage('error.confirm');
  print '<br /><br />' . implode('<br /><br />', $message) . getFooter();
  return;
}

$BASEDIR = $REPOSITORYDIR = null;

if (file_exists('./install.dir.php'))
{
  require 'install.dir.php';
}
if (!$BASEDIR || !$REPOSITORYDIR)
{
  $BASEDIR = findBaseDir();
  $REPOSITORYDIR = findRepositoryDir();
}

// WE CHECK HERE THE DIRECTORIES AND FILES ARE OK
if ($BASEDIR && $REPOSITORYDIR && checkBase($BASEDIR) == 2 && checkRepository($REPOSITORYDIR) == 2  && file_exists('master.php') && file_exists('master.js.php'))
{
  header('Location: /master.php?install');
  return;
}

if (!$BASEDIR || !$REPOSITORYDIR || checkBase($BASEDIR) != 2 || checkRepository($REPOSITORYDIR) != 2  )
{
  if (!$REPOSITORYDIR)
    $REPOSITORYDIR = $BASEDIR . 'repository/';
  print askDirectories($BASEDIR, $REPOSITORYDIR, $availablelanguages, $defaultlanguage, $confirmed);
  return;
}

// HERE STARTS THE MASTER FILES INSTALLATION

set_include_path('.'.PATH_SEPARATOR.$BASEDIR.'include');

// implements autoload
include_once '__autoload.lib';

// extended mod by default, can be changed later in the master
\core\WAFile::setDirMask(0755);
\core\WAFile::setFileMask(0644);
// we copy the directories
try
{
  $res = \core\WAFile::copyFile($BASEDIR.'components/master/site', '.');
  $res = \core\WAFile::copyFile($BASEDIR.'components/master/pages', $BASEDIR.'application/pagesmaster');
}
catch (\FileException $e)
{
  $message = getMessage('error.access');
  print implode('<br /><br />', $message);
  @unlink('master.php');
  @unlink('master.js.php');
  return;
}

if (substr($BASEDIR, 1, 1) == ':')
{
  $BASEDRIVE = substr($BASEDIR, 0, 2);
  $BASEDIR = substr($BASEDIR, 2);
}
else
  $BASEDRIVE = 'C:';
if (substr($REPOSITORYDIR, 1, 1) == ':')
{
  $REPOSITORYDRIVE = substr($REPOSITORYDIR, 0, 2);
  $REPOSITORYDIR = substr($REPOSITORYDIR, 2);
}
else
  $REPOSITORYDRIVE = 'C:';
$d = str_replace('\\', '/', getcwd());

if (substr($d, 1, 1) == ':')
{
  $MASTERDRIVE = substr($d, 0, 2);
  $MASTERDIR = substr($d, 2);
}
else
{
  $MASTERDRIVE = 'C:';
  $MASTERDIR = $d;
}

// we change the .php files
$code = file_get_contents('./master.php');
$code = str_replace('__BASEDRIVE__', $BASEDRIVE, $code);
$code = str_replace('__BASEDIR__', $BASEDIR, $code);
$code = str_replace('__REPOSITORYDRIVE__', $REPOSITORYDRIVE, $code);
$code = str_replace('__REPOSITORYDIR__', $REPOSITORYDIR, $code);
file_put_contents('./master.php', $code);

$code = file_get_contents('./master.js.php');
$code = str_replace('__BASEDRIVE__', $BASEDRIVE, $code);
$code = str_replace('__BASEDIR__', $BASEDIR, $code);
$code = str_replace('__REPOSITORYDRIVE__', $REPOSITORYDRIVE, $code);
$code = str_replace('__REPOSITORYDIR__', $REPOSITORYDIR, $code);
file_put_contents('./master.js.php', $code);

// we redirect to the master
header('Location: /master.php?install');

function findBaseDir()
{
  // we determine os (we cant use DB_Debug because we need this directory to load it !!!)
  $OS = 'Unix';
  if (strpos(strtolower(PHP_OS), 'win') !== false)
    $OS = 'Win';
  elseif (strpos(strtolower(PHP_OS), 'mac') !== false)
    $OS = 'Mac';

  $d = getcwd();
  if ($OS == 'Win')
  {
    $ed = explode('/', str_replace('\\', '/', $d));
  }
  else
  {
    $ed = explode('/', $d);
  }
  // we search into the path where is the base dir
  $c = count($ed) - 1;
  while ($c > 0)
  {
    unset($ed[$c]);
    $bd = implode('/', $ed);
    if (is_dir($bd.'/include') && is_dir($bd.'/components') && is_file($bd.'/include/__autoload.lib'))
      return $bd . '/';
    $c--;
  }
  return null;
}

function checkBase($dir)
{
  if (! (is_dir($dir.'/include') && is_dir($dir.'/components') && is_file($dir.'/include/__autoload.lib')) )
    return 0;
  // check we can READ and load libraries
  $result = 2;
  $fname = $dir.'/components/install/version.conf';
  $f = @fopen($fname, 'rb');
  if (!$f)
    $result = 1;
  else
    fclose($f);
  $fname = $dir.'/include/__autoload.lib';
  $f = @fopen($fname, 'rb');
  if (!$f)
    $result = 1;
  else
    fclose($f);
  return $result;
}

function findRepositoryDir()
{
  // we determine os (we cant use DB_Debug because we need this directory to load it !!!)
  $OS = 'Unix';
  if (strpos(strtolower(PHP_OS), 'win') !== false)
    $OS = 'Win';
  elseif (strpos(strtolower(PHP_OS), 'mac') !== false)
    $OS = 'Mac';

  $d = getcwd();
  if ($OS == 'Win')
  {
    $ed = explode('/', str_replace('\\', '/', $d));
  }
  else
  {
    $ed = explode('/', $d);
  }
  // we search into the path where is the base dir
  $c = count($ed) - 1;
  while ($c > 0)
  {
    unset($ed[$c]);
    $bd = implode('/', $ed);
    if (is_dir($bd.'/repository'))
      return $bd.'/repository/';
    $c--;
  }
  return null;
}

function checkRepository($dir)
{
  if (!is_dir($dir))
    return 0;
  $fname = $dir.'/test.temp';
  $f = @fopen($fname, 'wb');
  if (!$f)
    return 1;
  fclose($f);
  unlink($fname);
  return 2;
}

function askDirectories($BASEDIR, $REPOSITORYDIR, $availablelanguages, $defaultlanguage, $confirmed)
{
  $LANG = isset($_POST['LANG'])?$_POST['LANG']:null;
  if (!$LANG)
  {
    $string = @$_SERVER['HTTP_ACCEPT_LANGUAGE'];
    $LANG = substr($string, 0, 2);
  }

  if (!$LANG || !isset($availablelanguages[$LANG]))
  {
    $LANG = $defaultlanguage;
  }

  $bdir = isset($_POST['BASEDIR'])?$_POST['BASEDIR']:null;
  $rdir = isset($_POST['REPOSITORYDIR'])?$_POST['REPOSITORYDIR']:null;
  if ($bdir)
    $BASEDIR = $bdir;
  if ($rdir)
    $REPOSITORYDIR = $rdir;
  $baseok = $repositoryok = false;
  $resbase = $BASEDIR?checkBase($BASEDIR):0;
  $resrepository = $REPOSITORYDIR?checkRepository($REPOSITORYDIR):0;

  $txt = getHeader();

  foreach($availablelanguages as $lang => $langname)
  {
    $display = ($LANG != $lang)?'display: none;':'';

    $message1 = $message2 = '';
    if ($BASEDIR)
    {
      if ( $resbase == 0)
        $message1 = getMessage('error.basenotvalid', $lang);
      elseif ( $resbase == 1)
        $message1 = getMessage('error.basenotreadable', $lang);
      else
        $baseok = true;
    }
    if ($REPOSITORYDIR)
    {
      if ($resrepository == 0)
        $message2 = getMessage('error.repositorynotvalid', $lang);
      elseif ($resrepository == 1)
        $message2 = getMessage('error.repositorynotwritable', $lang);
      else
        $repositoryok = true;
    }

    if ($baseok && $repositoryok)
    {
      // we write the directories file
      $f = fopen('./install.dir.php', 'wb');
      fwrite($f, "<?php\n\$BASEDIR='$BASEDIR';\n\$REPOSITORYDIR='$REPOSITORYDIR';\n?>");
      fclose($f);
      header('Location: /install.php' . ($confirmed?'?confirmed':''));
      return '';
    }

    $title = getMessage('title', $lang);
    $intro = getMessage('intro', $lang);
    $basedir = getMessage('basedir', $lang);
    $repositorydir = getMessage('repositorydir', $lang);
    $nextstep = getMessage('nextstep', $lang);
    $htmlconfirmed = $confirmed?'?confirmed':'';

    $txt .= <<<EOF
<div id="$lang" style="$display">
<h1>{$title}</h1>
EOF;

    foreach($availablelanguages as $selectlang => $selectlangname)
    {
      $color = ($selectlang == $lang)?'red':'blue';
      $onclick = '';
      if ($selectlang != $lang)
      {
        $onclick = <<<EOF
 onclick="document.getElementById('$lang').style.display='none'; document.getElementById('$selectlang').style.display='';"
EOF;
      }

      $txt .= <<<EOF
[<span style="color: $color; cursor: pointer;"$onclick>$selectlangname</span>]
EOF;
    }

    $txt .= <<<EOF
<br />
<br />
<div style="border: 2px solid blue; background-color: #eeeeff; padding: 10px;">
{$intro}
</div>
<br />
{$message1}
{$message2}
<form method="post" action="/install.php$htmlconfirmed" style="border: 2px solid green; background-color: #eeffee; padding: 10px;">
{$basedir}<input type="text" name="BASEDIR" style="width: 300px;" value="$BASEDIR"><br />
{$repositorydir}<input type="text" name="REPOSITORYDIR" style="width: 300px;" value="$REPOSITORYDIR"><br />
<input type="submit" value="{$nextstep}">
<input type="hidden" name="LANG" value="en">
</form>
</div>
EOF;
  }

  $txt .= getFooter();

  return $txt;
}

function getMessage($id, $lang = null)
{
  global $messages;
  if (!$lang)
  {
    $msg = array();
    foreach($messages as $l => $m)
      $msg[$l] = $m[$id];
    return $msg;
  }
  return $messages[$lang][$id];
}

function setMessages($extralanguages)
{
  global $messages;

  $messages['en'] = array(
    'error.php53' => 'CRITICAL ERROR: You need PHP 5.3 or superior to install WebAbility&reg; v6',
    'error.xml' => 'CRITICAL ERROR: You need the simpleXML extension activated in PHP in order to install WebAbility&reg; v6',
    'error.shared' => 'WARNING: It is hightly recommended to have the shared memory extension activated in PHP in order to install WebAbility&reg; v6',
    'error.gd' => 'WARNING: It is hightly recommended to have the GD extension activated in PHP in order to install WebAbility&reg; v6',
    'error.confirm' => '<a href="install.php?confirmed">Acknowledge this information and follow with the installation.</a>',
    'error.access' => 'ERROR: The master files could not be installed. Please check that the directory access is available in read/write mode for the Apache owner.',
    'error.basenotvalid' => '<div style="border: 2px solid red; background-color: #ffeeee; padding: 10px;">
The base directory is not valid. Please verify the base directory contains \'include\' and \'components\' subdirectories.
</div><br />',
    'error.basenotreadable' => '<div style="border: 2px solid red; background-color: #ffeeee; padding: 10px;">
The base directory is not readable. Please verify the access rights.
</div><br />',
    'error.repositorynotvalid' => '<div style="border: 2px solid red; background-color: #ffeeee; padding: 10px;">
The repository directory is not valid. Please verify this directory exists and the Apache daemon have full access on it. The default repository is generally placed into [BASE DIR]/repository
</div><br />',
    'error.repositorynotwritable' => '<div style="border: 2px solid red; background-color: #ffeeee; padding: 10px;">
The repository directory is not writable. Please verify the access rights.
</div><br />',
    'title' => 'WebAbility&reg; v6 - Installation',
    'intro' => 'The WebAbility&reg; v6 automatic installation system could not find the basic application directories.<br />
The user running Apache daemon must have full access on those directories and files.<br />
Please specify them:<br />',
    'basedir' => 'Base directory: ',
    'repositorydir' => 'Repository directory: ',
    'nextstep' => 'Next step'
  );

  $messages['es'] = array(
    'error.php53' => 'ERROR CRÍTICO: Necesita PHP 5.3 o superior para poder instalar el WebAbility&reg; v6',
    'error.xml' => 'ERROR CRÍTICO: Necesita la extensión simpleXML activada en PHP para poder instalar WebAbility&reg; v6',
    'error.shared' => 'IMPORTANTE: Es altamente recomendado tener la extensión de memoria compartida (shared memory) activada en PHP para instalar WebAbility&reg; v6',
    'error.gd' => 'IMPORTANTE: Es altamente recomendado tener la extensión GD activada en PHP para instalar WebAbility&reg; v6',
    'error.confirm' => '<a href="install.php?confirmed">Aceptar esta información y seguir con la instalación.</a>',
    'error.access' => 'ERROR: LOS ARCHIVOS DEL SITIO MAESTRO NO PUDIERON SER INSTALADOS. VERIFIQUE QUE LOS ACCESOS PARA EL DIRECTORIO SON AUTORIZADOS PARA EL USUARIO DEL APACHE.',
    'error.basenotvalid' => '<div style="border: 2px solid red; background-color: #ffeeee; padding: 10px;">
La carpeta base no es válida. Verifique que la carpeta contenga los sub-directorios \'include\' y \'components\'.
</div><br />',
    'error.basenotreadable' => '<div style="border: 2px solid red; background-color: #ffeeee; padding: 10px;">
La carpeta base no es legible. Verifique los derechos sobre la carpeta.
</div><br />',
    'error.repositorynotvalid' => '<div style="border: 2px solid red; background-color: #ffeeee; padding: 10px;">
La carpeta del repositorio no es válida. Verifique que esta carpeta exista y que el usuario del Apache tenga accesos completos sobre ella. En general, la ruta del repositorio esta en [DIR BASE]/repository
</div><br />',
    'error.repositorynotwritable' => '<div style="border: 2px solid red; background-color: #ffeeee; padding: 10px;">
La carpeta del repositorio no es escribible. Verifique los derechos sobre la carpeta.
</div><br />',
    'title' => 'WebAbility&reg; v6 - Instalación',
    'intro' => 'El sistema de instalación automático de WebAbility&reg; v6 no pudo encontrar las carpetas básicas del sistema.<br />
El usuario corriendo el demonio de Apache necesita tener acceso completo a estas carpetas y archivos.<br />
Por favor, especifique las rutas correctas:<br />',
    'basedir' => 'Carpeta base: ',
    'repositorydir' => 'Carpeta del repositorio: ',
    'nextstep' => 'Siguiente'
  );

  $messages['fr'] = array(
    'error.php53' => 'ERREUR CRITIQUE: PHP 5.3 ou superieur doit être installé pour pouvoir utiliser WebAbility&reg; v6',
    'error.xml' => "ERREUR CRITIQUE: L'expansion simpleXML doit être instalée pour pouvoir utiliser WebAbility&reg; v6",
    'error.shared' => "IMPORTANT: Il est recommendé d'avoir l'expansion de mémoire compartie (shared memory) activée dans PHP pour installer WebAbility&reg; v6",
    'error.gd' => "IMPORTANT: Il est recommendé d'avoir l'expansion GD activée dans PHP pour installer WebAbility&reg; v6",
    'error.confirm' => '<a href="install.php?confirmed">Valider cette information et procéder avec l\'installation.</a>',
    'error.access' => 'ERREUR: LES FICHIERS DU SITE MAITRE N\'ONT PAS PU ETRE INSTALLES. VEUILLEZ VERIFIER LES DROITS D\'ACCES DE L\'UTILISATEUR D\'APACHE SUR CE REPERTOIRE.',
    'error.basenotvalid' => '<div style="border: 2px solid red; background-color: #ffeeee; padding: 10px;">
Le répertoire de base n\'est pas valide. Veuillez vérifier que le répertoire contient les sous-répertoires \'include\' et \'components\'.
</div><br />',
    'error.basenotreadable' => '<div style="border: 2px solid red; background-color: #ffeeee; padding: 10px;">
Le répertoire de base n\'est pas lisible. Veuillez vérifier les droits d\'accès.
</div><br />',
    'error.repositorynotvalid' => '<div style="border: 2px solid red; background-color: #ffeeee; padding: 10px;">
Le répertoire de données n\'est pas valide. Veuillez verifier que ce répertoire existe et que l\'utilisateur d\'Apache a pleins droits sur celui-ci. Le répertoire est en général dans [REP BASE]/repository
</div><br />',
    'error.repositorynotwritable' => '<div style="border: 2px solid red; background-color: #ffeeee; padding: 10px;">
Le répertoire de données n\'est pas habilité en écriture. Veuillez verifier les droits d\'accès.
</div><br />',
    'title' => 'WebAbility&reg; v6 - Installation',
    'intro' => 'Le système d\'installation automatique de WebAbility&reg; v6 n\'a pas pu trouver les répertoires de base de l\'application.<br />
L\'utilisateur d\'Apache doit avoir l\'accès complet sur ces répertoires et fichers.<br />
Veuillez specifier les routes correctes:<br />',
    'basedir' => 'Répertoire de base: ',
    'repositorydir' => 'Répertoire des données: ',
    'nextstep' => 'Next step'
  );

  if ($extralanguages)
  {
    foreach($extralanguages as $k => $l)
    {
      $messages[$k] = $l;
    }
  }

}

function getHeader()
{
  return <<<EOF
<!DOCTYPE html>
<html lang="es">
<head>
  <title>WebAbility&reg; v6</title>
  <meta name="Master" content="WebAbility(r) v6 - www.webability.info - (c) 1999-2017, Ing. Philippe Thomassigny C." />
  <meta name="Component" content="Install Engine" />
  <meta http-equiv="PRAGMA" content="NO-CACHE" />
  <meta http-equiv="Expires" content="-1" />
  <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
</head>
<body style="font-family: Verdana;">
EOF;
}

function getFooter()
{
  return <<<EOF
</body>
</html>
EOF;
}

?>