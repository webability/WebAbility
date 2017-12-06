<?php

// WebAbility(r) v.5
// index.php / Main Admin index
// WRAPPER TO MAIN ADMIN JS DISPATCHER
// Ing. Philippe Thomassigny (c) 2001-2010

error_reporting(E_ALL);
ini_set('display_errors', true);
set_time_limit(600);  // 10 minutes max, some databases are very slow...

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

global $BASEDIR, $REPOSITORYDRIVE;
$BASEDIR       = $BASEDRIVE       . '__BASEDIR__';
$REPOSITORYDIR = $REPOSITORYDRIVE . '__REPOSITORYDIR__';

set_include_path('.'.PATH_SEPARATOR.$BASEDIR.'/include');
// implements autoload
include_once '__autoload.lib';

$js = new \tools\js\js();
$js->getJS($BASEDIR, $REPOSITORYDIR);

?>