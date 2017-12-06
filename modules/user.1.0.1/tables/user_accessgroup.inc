<?php

// WebAbility Version: >= 6
// Module: BASE
// Language: PHP
// Creation: 31/03/2008
// Modification: on CVS

// TABLE: user_accessgroup,

$user_accessgroup = new \dominion\DB_Table("user_accessgroup", "user_acg_", \dominion\DB_Table::TABLE);

// KEY
$user_accessgroup->AddField(
  new \dominion\DB_FieldVarchar("key", 30, new \dominion\DB_check(array(\dominion\DB_Check::PK)))
);

// NAME
$user_accessgroup->AddField(
  new \dominion\DB_FieldVarchar("name", 255, new \dominion\DB_Check(\dominion\DB_Check::NN))
);

// DESCRIPTION
$user_accessgroup->AddField(
  new \dominion\DB_FieldText("descr")
);

?>