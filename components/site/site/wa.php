<?php

// WebAbility(r) v.5
// wa.php / Main Site engine wrapper
// WRAPPER TO MAIN SITE DISPATCHER
// Ing. Philippe Thomassigny (c) 2001-2010

error_reporting(E_ALL);
ini_set('display_errors', true);

// We take at first the microtime to evaluate calculation time of page.
$BASE_MIB = microtime();

// The wrapper config variables are set by the installation system
// THE DRIVE SYSTEM is done to assure windows-unix compatibility of transporting application
if (isset($_SERVER["WINDIR"]))
{
  $BASEDRIVE       = "__BASEDRIVE__";
  $REPOSITORYDRIVE = "__REPOSITORYDRIVE__";
  $ADMINDRIVE      = "__ADMINDRIVE__";
  $SITEDRIVE       = "__SITEDRIVE__";
}
else
{
  $BASEDRIVE = $REPOSITORYDRIVE = $ADMINDRIVE = $SITEDRIVE = "";
}

global $BASEDIR, $REPOSITORYDIR, $SITEDIR;
$BASEDIR       = $BASEDRIVE       . "__BASEDIR__";
$REPOSITORYDIR = $REPOSITORYDRIVE . "__REPOSITORYDIR__";
$ADMINDIR      = $ADMINDRIVE      . "__ADMINDIR__";
$SITEDIR       = $SITEDRIVE       . "__SITEDIR__";

// Just in case for multiple site and php apache config
set_include_path(".".PATH_SEPARATOR.$BASEDIR."/include");

// implements __autoload
include_once $BASEDIR."/include/common/__autoload.lib";

try
{
  // we create the base object
  include_once "site/Base.lib";
  $base = new Base($BASEDIR, $REPOSITORYDIR, $ADMINDIR, $SITEDIR);
  WAMessage::setMessagesFile($BASEDIR.'/components/static/'.$base->Language.'.xml');
}
catch (Exception $exception)
{
}





?>