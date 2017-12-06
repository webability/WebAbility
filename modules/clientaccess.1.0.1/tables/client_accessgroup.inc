<?php

// WebAbility Version: >= 3.02.04
// Module: BASE
// Language: PHP
// Creation: 31/03/2008
// Modification: on CVS

// TABLE: client_accessgroup,

$client_accessgroup = new \dominion\DB_Table("client_accessgroup", "client_acg_", \dominion\DB_Table::TABLE);

// KEY
$client_accessgroup->AddField(
  new \dominion\DB_FieldVarchar("key", 30, new \dominion\DB_check(array(\dominion\DB_Check::PK)))
);

// NAME
$client_accessgroup->AddField(
  new \dominion\DB_FieldVarchar("name", 255, new \dominion\DB_Check(\dominion\DB_Check::NN))
);

// NAME
$client_accessgroup->AddField(
  new \dominion\DB_FieldVarchar("module", 15, new \dominion\DB_Check(array(\dominion\DB_Check::NN, \dominion\DB_Check::FK.'.base_module.base_mod_key')) )
);

// DESCRIPTION
$client_accessgroup->AddField(
  new \dominion\DB_FieldText("description")
);

?>