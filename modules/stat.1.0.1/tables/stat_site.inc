<?php

// WebAbility Version: >= 3.01.01
// Language: PHP
// Creation: 22/09/2002, Ing. Philippe Thomassigny
// Modification: on CVS

// TABLE: stat_site:

// Needed table: NONE

// This table doesnt use FK on page, browser, language or client, it's just a statistical table.

$stat_site = new \dominion\DB_Table("stat_site", "stat_sit_", \dominion\DB_Table::LOG );

$stat_site->AddField(
  new \dominion\DB_FieldInteger("key", new \dominion\DB_Check(array(\dominion\DB_Check::PK, \dominion\DB_Check::AI)) )
);

$stat_site->AddField(
  new \dominion\DB_FieldVarchar("page", 255, new \dominion\DB_Check(array(\dominion\DB_Check::NN, \dominion\DB_Check::IN )) )
);

$stat_site->AddField(
  new \dominion\DB_FieldVarchar("browser", 30, new \dominion\DB_Check(array(\dominion\DB_Check::NN, \dominion\DB_Check::IN )) )
);

$stat_site->AddField(
  new \dominion\DB_FieldVarchar("language", 2, new \dominion\DB_Check(array(\dominion\DB_Check::NN, \dominion\DB_Check::IN)) )
);

$stat_site->AddField(
  new \dominion\DB_FieldVarchar("version", 30, null )
);

$stat_site->AddField(
  new \dominion\DB_FieldVarchar("templateversion", 30, null )
);

$stat_site->AddField(
  new \dominion\DB_FieldVarchar("skin", 30, null )
);

$stat_site->AddField(
  new \dominion\DB_FieldVarchar("ip", 100, new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

$stat_site->AddField(
  new \dominion\DB_FieldVarchar("host", 100, new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

$stat_site->AddField(
  new \dominion\DB_FieldDateTime("date", new \dominion\DB_Check(array(\dominion\DB_Check::NN, \dominion\DB_Check::IN)) )
);

// time inside load ms
$stat_site->AddField(
  new \dominion\DB_FieldReal("time1", new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

// time inside create base ms
$stat_site->AddField(
  new \dominion\DB_FieldReal("time2", new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

// time inside calculate page ms
$stat_site->AddField(
  new \dominion\DB_FieldReal("time3", new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

// time inside create page ms
$stat_site->AddField(
  new \dominion\DB_FieldReal("time4", new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

// time print ms
$stat_site->AddField(
  new \dominion\DB_FieldReal("time5", new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

// time outside all ms
$stat_site->AddField(
  new \dominion\DB_FieldReal("time6", new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

$stat_site->AddField(
  new \dominion\DB_FieldInteger("client", new \dominion\DB_Check(\dominion\DB_Check::IN) )
);

$stat_site->AddField(
  new \dominion\DB_FieldText("params", new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

?>