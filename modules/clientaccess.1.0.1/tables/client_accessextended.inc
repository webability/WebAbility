<?php

// WebAbility Version: >= 3.01.01
// Language: PHP
// Creation: 05/11/2002, Ing. Philippe Thomassigny
// Modification: on CVS

// TABLE: client_accessextended:
// Extended clientaccess levels for user for security module
// The extended levels are used for clientaccesses applied on table records.

// Needed table: NONE

$client_accessextended = new \dominion\DB_Table("client_accessextended", "client_ace_", \dominion\DB_Table::CATALOG);

// The primary key is hand enterable key. The key is a number relative
//    to the base number of each module installed.
$client_accessextended->AddField(
  new \dominion\DB_FieldVarchar("key",30, new \dominion\DB_Check(\dominion\DB_Check::PK) )
);

// The name of the extended clientaccess
$client_accessextended->AddField(
  new \dominion\DB_FieldVarchar("name", 255, new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

// The name of the security access
$client_accessextended->AddField(
  new \dominion\DB_FieldVarchar("group", 30, new \dominion\DB_Check(array(\dominion\DB_Check::NN, \dominion\DB_Check::FK.'.client_accessgroup.client_acg_key')) )
);

$client_accessextended->AddField(
  new \dominion\DB_FieldText("queries", new \dominion\DB_Check(\dominion\DB_Check::NN))
);

$client_accessextended->AddField(
  new \dominion\DB_FieldText("description")
);

?>