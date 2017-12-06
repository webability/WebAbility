<?php

// WebAbility Version: >= 3.01.01
// Module: CLNT.3.01.01
// Language: PHP
// Creation: 31/07/2003
// Modification: on CVS

// TABLE: client_profile,
// clients group

// Needed table: None

$client_profile = new \dominion\DB_Table("client_profile", "client_pro_", \dominion\DB_Table::TABLE);

//PK
$client_profile->AddField(
  new \dominion\DB_FieldVarchar("key", 30, new \dominion\DB_check(\dominion\DB_Check::PK))
);

$client_profile->AddField(
  new \dominion\DB_FieldVarchar("name", 255, new \dominion\DB_check(\dominion\DB_Check::NN))
);

//status 1 = active, 2 = not active
$client_profile->AddField(
  new \dominion\DB_FieldInteger("status", new \dominion\DB_check(\dominion\DB_Check::NN))
);

?>