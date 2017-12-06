<?php

// WebAbility Version: >= 3.01.01
// Module: CLNT.3.01.01
// Language: PHP
// Creation: 31/07/2003
// Modification: on CVS

// TABLE: client_clientaccess,
// clients accesss

// Needed table: None

$client_clientaccess = new \dominion\DB_Table("client_clientaccess", "client_cac_", \dominion\DB_Table::TABLE);

$client_clientaccess->AddField(
  new \dominion\DB_FieldInteger("client", new \dominion\DB_Check(\dominion\DB_Check::NN, \dominion\DB_Check::FK.".client_client.client_cli_key", \dominion\DB_Check::DC))
);

//status 1 = active, 2 = not active
$client_clientaccess->AddField(
  new \dominion\DB_FieldVarchar("access", 30, new \dominion\DB_Check(\dominion\DB_Check::NN, \dominion\DB_Check::FK.".client_access.client_acc_key", \dominion\DB_Check::DC))
);

?>