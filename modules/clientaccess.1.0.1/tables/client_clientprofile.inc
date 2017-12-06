<?php

// WebAbility Version: >= 3.01.01
// Module: CLNT.3.01.01
// Language: PHP
// Creation: 31/07/2003
// Modification: on CVS

// TABLE: client_clientprofile,
// clients profiles

// Needed table: None

$client_clientprofile = new \dominion\DB_Table("client_clientprofile", "client_cpr_", \dominion\DB_Table::TABLE);

$client_clientprofile->AddField(
  new \dominion\DB_FieldInteger("client", new \dominion\DB_Check(\dominion\DB_Check::NN, \dominion\DB_Check::FK.".client_client.client_cli_key", \dominion\DB_Check::DC))
);

//status 1 = active, 2 = not active
$client_clientprofile->AddField(
  new \dominion\DB_FieldVarchar("profile", 30, new \dominion\DB_Check(\dominion\DB_Check::NN, \dominion\DB_Check::FK.".client_profile.client_pro_key", \dominion\DB_Check::DC))
);

?>