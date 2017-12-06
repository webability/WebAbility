<?php
// WebAbility Version: >= 3.01.01
// Language: PHP
// Creation: 04/11/2002, Ing. Philippe Thomassigny
// Modification: on CVS

// TABLE: client_access:
// Access levels for user for security module

// Needed table: client_accessgroup

$client_access = new \dominion\DB_Table("client_access", "client_acc_", \dominion\DB_Table::TABLE);

// The key is numeric and hand-coded
$client_access->AddField(
  new \dominion\DB_FieldVarchar("key", 30, new \dominion\DB_Check(\dominion\DB_Check::PK) )
);

// The name of the security access
$client_access->AddField(
  new \dominion\DB_FieldVarchar("name", 255, new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

// The name of the security access
$client_access->AddField(
  new \dominion\DB_FieldVarchar("group", 30, new \dominion\DB_Check(array(\dominion\DB_Check::NN, \dominion\DB_Check::FK.'.client_accessgroup.client_acg_key')) )
);

// The description of the access
$client_access->AddField(
  new \dominion\DB_FieldText("description")
);

?>