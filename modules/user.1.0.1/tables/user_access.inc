<?php
// WebAbility Version: >= 3.01.01
// Language: PHP
// Creation: 04/11/2002, Ing. Philippe Thomassigny
// Modification: on CVS

// TABLE: user_access:
// Access levels for user for security module

// Needed table: NONE

$user_access = new \dominion\DB_Table("user_access", "user_acc_", \dominion\DB_Table::SYSCATALOG);

// The key is numeric and hand-coded
$user_access->AddField(
  new \dominion\DB_FieldVarchar("key", 30, new \dominion\DB_Check(\dominion\DB_Check::PK) )
);

// The name of the security access
$user_access->AddField(
  new \dominion\DB_FieldVarchar("name", 255, new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

// right group, optional
$user_access->AddField(
  new \dominion\DB_FieldVarchar("group", 30, new \dominion\DB_Check(array(\dominion\DB_Check::FK.".user_accessgroup.user_acg_key", \dominion\DB_Check::IN)))
);

// The description of the access
$user_access->AddField(
  new \dominion\DB_FieldText("descr")
);

?>