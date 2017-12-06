<?php

// LIBRERIA PARA EL PREVIEW DE SITIOS; A VERIFICAR CONTRA DESPACHADOR NUEVO v4

// WebAbility v3
// Main Index Site wrapper.to see pages from admin
// Ing. Philippe Thomassigny (c) 2000 to 2008

error_reporting(E_ALL);
set_time_limit(300);

$errors = null;
ob_start();

// We take at first the microtime to evaluate calculation time of page.
$BASE_MIB = microtime();

// The wrapper config variables are set by the installation system
// THE DRIVE SYSTEM is done to assure windows-unix compatibility of transporting application
if (isset($_SERVER["WINDIR"]))
{
  $DRIVEBASE       = "C:";
  $DRIVEREPOSITORY = "C:";
  $DRIVEADMIN      = "C:";
  $DRIVESITE       = "C:";
}
else
{
  $DRIVEBASE = $DRIVEREPOSITORY = $DRIVEADMIN = $DRIVESITE = "";
}

global $BASEDIR, $REPOSITORYDIR, $SITEDIR;
$BASEDIR       = $DRIVEBASE       . "/home/sites/base4site-UV";
$REPOSITORYDIR = $DRIVEREPOSITORY . "/home/sites/base4site-UV/sites/UV/repository/";
$ADMINDIR      = $DRIVEADMIN      . "/home/sites/base4site-UV/sites/UV/admin/";
$SITEDIR       = $DRIVESITE       . "/home/sites/base4site-UV/sites/UV/site/";

// Just in case for multiple site and php apache config
set_include_path(".".PATH_SEPARATOR.$BASEDIR."/include");

// implements autoload
include_once $BASEDIR."/include/common/__autoload.lib";

// When arriving here, we enter in the "normal" HTML wrapper.
// Each page is wrapped through the index.
// The index gives the basic functions and includes to the included libraries.

$SHOW_EXCEPTION = true; // debug version

if (isset($_GET["DEBUG"]) && file_exists($REPOSITORYDIR."candebug.site.afo"))
{
  $fcandebug = fopen($REPOSITORYDIR."candebug.site.afo", "rb");
  $candebug = unserialize(fread($fcandebug, filesize($REPOSITORYDIR."candebug.site.afo")));
  fclose($fcandebug);

  // Debug information:
  define ("DBG_DOMINION", $candebug["dominion"]);
  define ("DBG_DOMVAR", $candebug["domvar"]);
  define ("DBG_DOMDB", $candebug["domdb"]);
  define ("DBG_DOMLIST", $candebug["domlist"]);
  define ("DBG_DOMMASK", $candebug["dommask"]);
  define ("DBG_BASE", $candebug["base"]);
  define ("DBG_ENGINE", $candebug["engine"]);
  define ("DBG_SCRIPT", $candebug["script"]);
  define ("DBG_PROFILER", $candebug["profiler"]);
  $SHOW_EXCEPTION = $candebug["exception"];
}

try
{
  // We load the default $base object (database conection, security and all others)
  include_once "site/Base.lib";

  // We load page/element objects and base parser
  include_once "site/Engine.lib";

  $BASE_MIE = microtime();

  // we create the base object
  $base = new Base($BASEDIR, $REPOSITORYDIR, $ADMINDIR, $SITEDIR);

  // get the mode, mandatory
  $BASE_MODE = $base->HTTPRequest->getParameter("MODE", Base_Common::ALPHANUMERIC);

  // check if the MODE is OK => correspond to admin cookie AND the IP correspond too
  // where is the mode from: admin ? ( R or A respectively)
  $MODEWHERE = substr($BASE_MODE, 0, 1);
  // the connection key of the user
  $MODEKEY = substr($BASE_MODE, 1);

  require $base->getTableDefPath("BASE_user");
  $BASE_user->setDB($base->connector[0]);

  require $base->getTableDefPath("BASE_connection");
  $BASE_connection->setDB($base->connector[0]);

  $res = $BASE_connection->doSelectCondition(new DB_Condition("id", "=", $MODEKEY));

  $modeok = false;
  if ($res)
  {
    $modeok = true;
  }

  if (!$modeok)
  {
    die("P�gina no autorizada");
  }

  // We set language if has to be changed, or reinject cookie
  $BASE_LANG = $base->sendcookielanguage($base->HTTPRequest->getParameter("LANG", Base_Common::ALPHANUMERIC));

  // We get the client browser too
  $BASE_BROW = $base->HTTPRequest->getParameter("BROW", Base_Common::ALPHANUMERIC);

  // We get the page number
  $BASE_P = $base->HTTPRequest->getParameter("P", Base_Common::ALPHANUMERIC);

  // We get the version forced number: $V is the VERSION to use (main page) (if not default) (must be published)
  $BASE_V = $base->HTTPRequest->getParameter("V", Base_Common::ALPHANUMERIC);

  // We get the template version forced number: $TV is the TEMPLATE VERSION to use (main page) (if not default) (must be published)
  $BASE_TV = $base->HTTPRequest->getParameter("TV", Base_Common::ALPHANUMERIC);

  // We force the skin while we define real use of it
  $BASE_SKIN = "clean";

  // do we simulate client ?




  // check client !
  $base->checkClient();





  // We take inner time
  $BASE_MBI1 = microtime();

  // We create the page object (page properties) from the "engine.lib"
  $BASE_page = new Engine($base, $BASE_P, $BASE_SKIN, $BASE_LANG, $BASE_BROW, $BASE_V, $BASE_TV, false, null, null, true);

  // We take inner time
  $BASE_MBI2 = microtime();

  // We calculate the page itself
  $page = $BASE_page->createPage();

  // We take end microtime to evaluate calculation time of page.
  $BASE_MBI3 = microtime();

  $errors = ob_get_contents();
  ob_end_clean();

  print $page;

  // We take the end print microtime
  $BASE_MBI4 = microtime();

  // Calc stats if activated and if all correct
  if ($base->getConfig("site.ifstatistics"))
  {
    $base->insertStat(
      $base->calculatePureTime($BASE_MIB,$BASE_MIE),
      $base->calculatePureTime($BASE_MIE,$BASE_MBI1),
      $base->calculatePureTime($BASE_MBI1,$BASE_MBI2),
      $base->calculatePureTime($BASE_MBI2,$BASE_MBI3),
      $base->calculatePureTime($BASE_MBI3,$BASE_MBI4),
      $base->calculatePureTime($BASE_MIB,$BASE_MBI4),
      $BASE_page);
  }

  $BASE_ME = microtime();

  // We print the stats if asked
  if ($base->getConfig("site.showstatistics") == 1)
  {
    $legend1 = $base->getLanguageEntry("base", "timeinsideload", $BASE_LANG);
    $legend2 = $base->getLanguageEntry("base", "timeinsidebase", $BASE_LANG);
    $legend3 = $base->getLanguageEntry("base", "timeinsidecalculated", $BASE_LANG);
    $legend4 = $base->getLanguageEntry("base", "timeinsidecreated", $BASE_LANG);
    $legend5 = $base->getLanguageEntry("base", "timeprint", $BASE_LANG);
    $legend6 = $base->getLanguageEntry("base", "timeoutsideall", $BASE_LANG);

    print "<br>\n $legend1: ".$base->calculateTime($BASE_MIB,$BASE_MIE);
    print "<br>\n $legend2: ".$base->calculateTime($BASE_MIE,$BASE_MBI1);
    print "<br>\n $legend3: ".$base->calculateTime($BASE_MBI1,$BASE_MBI2);
    print "<br>\n $legend4: ".$base->calculateTime($BASE_MBI2,$BASE_MBI3);
    print "<br>\n $legend5: ".$base->calculateTime($BASE_MBI3,$BASE_MBI4);
    print "<br>\n $legend6: ".$base->calculateTime($BASE_MIB,$BASE_ME);
  }
}
catch (Exception $exception)
{
  $errors = ob_get_contents();
  ob_end_clean();

  if ($SHOW_EXCEPTION)
    print $exception->__toString();

  if ($base)
  {
    // Log exception !!
    $base->insertSysLog(5, $exception->__toString(), $_SERVER["REQUEST_URI"]);

    // add Stats
    if ($base->getConfig("site.ifstatistics"))
    {
      $base->insertStat(
        $base->calculatePureTime(0,0),
        $base->calculatePureTime(0,0),
        $base->calculatePureTime(0,0),
        $base->calculatePureTime(0,0),
        $base->calculatePureTime(0,0),
        $base->calculatePureTime(0,0),
        (isset($BASE_page)?$BASE_page:null));
    }
  }
}

if ($errors && $SHOW_EXCEPTION)
{
  print "\n<br />\nReported errors:<br />\n".$errors;
}
if ($errors && $base)
{
  $base->insertSysLog(5, $errors, $_SERVER["REQUEST_URI"]);
}

?>