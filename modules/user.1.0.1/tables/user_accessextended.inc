<?php
// WebAbility Version: >= 3.01.01
// Language: PHP
// Creation: 05/11/2002, Ing. Philippe Thomassigny
// Modification: on CVS

// TABLE: user_accessextended:
// Extended access levels for user for security module
// The extended levels are used for accesses applied on table records.

// Needed table: NONE

$user_accessextended = new \dominion\DB_Table("user_accessextended", "user_ace_", \dominion\DB_Table::CATALOG);

// The primary key is hand enterable key. The key is a number relative
//    to the base number of each module installed.
$user_accessextended->AddField(
  new \dominion\DB_FieldVarchar("key", 30, new \dominion\DB_Check(\dominion\DB_Check::PK) )
);

// The name of the extended access
$user_accessextended->AddField(
  new \dominion\DB_FieldVarchar("name", 255, new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

// right group, optional
$user_accessextended->AddField(
  new \dominion\DB_FieldVarchar("group", 30, new \dominion\DB_Check(array(\dominion\DB_Check::FK.".user_accessgroup.user_acg_key", \dominion\DB_Check::IN)))
);

$user_accessextended->AddField(
  new \dominion\DB_FieldText("queries", new \dominion\DB_Check(\dominion\DB_Check::NN))
);

$user_accessextended->AddField(
  new \dominion\DB_FieldText("descr")
);

?>