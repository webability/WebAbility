<?php

// WebAbility Version: >= 3.01.01
// Module: CLNT.3.01.01
// Language: PHP
// Creation: 31/07/2003
// Modification: on CVS

// TABLE: client_clientaccessextended,
// clients accesss

// Needed table: None

$client_clientaccessextended = new \dominion\DB_Table("client_clientaccessextendedextended", "client_cae_", \dominion\DB_Table::TABLE);

$client_clientaccessextended->AddField(
  new \dominion\DB_FieldInteger("client", new \dominion\DB_Check(\dominion\DB_Check::NN, \dominion\DB_Check::FK.".client_client.client_cli_key", \dominion\DB_Check::DC))
);

//status 1 = active, 2 = not active
$client_clientaccessextended->AddField(
  new \dominion\DB_FieldVarchar("accessextended", 30, new \dominion\DB_Check(\dominion\DB_Check::NN, \dominion\DB_Check::FK.".client_accessextended.client_ace_key", \dominion\DB_Check::DC))
);

//Clave externa
$client_clientaccessextended->AddField(
  new \dominion\DB_FieldVarchar("extkey", 30)
);

?>