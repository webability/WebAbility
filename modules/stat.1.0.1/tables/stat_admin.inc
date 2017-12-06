<?php

// WebAbility Version: >= 3.01.01
// Language: PHP
// Creation: 22/09/2002, Ing. Philippe Thomassigny
// Modification: on CVS

// TABLE: stat_admin:

// Needed table: NONE

// This table doesnt use FK on page, browser, language or client, it's just a log table.

$stat_admin = new \dominion\DB_Table("stat_admin", "stat_adm_", \dominion\DB_Table::LOG );

$stat_admin->AddField(
  new \dominion\DB_FieldInteger("key", new \dominion\DB_Check(array(\dominion\DB_Check::PK, \dominion\DB_Check::AI)) )
);

$stat_admin->AddField(
  new \dominion\DB_FieldVarchar("page", 255, new \dominion\DB_Check(array(\dominion\DB_Check::NN, \dominion\DB_Check::IN )) )
);

$stat_admin->AddField(
  new \dominion\DB_FieldVarchar("language", 2, new \dominion\DB_Check(array(\dominion\DB_Check::NN, \dominion\DB_Check::IN)) )
);

$stat_admin->AddField(
  new \dominion\DB_FieldVarchar("skin", 30, null )
);

$stat_admin->AddField(
  new \dominion\DB_FieldVarchar("ip", 15, new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

$stat_admin->AddField(
  new \dominion\DB_FieldVarchar("host", 100, new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

$stat_admin->AddField(
  new \dominion\DB_FieldDateTime("date", new \dominion\DB_Check(array(\dominion\DB_Check::NN, \dominion\DB_Check::IN)) )
);

// time inside load ms
$stat_admin->AddField(
  new \dominion\DB_FieldReal("time", new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

$stat_admin->AddField(
  new \dominion\DB_FieldInteger("user", new \dominion\DB_Check(\dominion\DB_Check::IN) )
);

$stat_admin->AddField(
  new \dominion\DB_FieldText("params", new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

?>