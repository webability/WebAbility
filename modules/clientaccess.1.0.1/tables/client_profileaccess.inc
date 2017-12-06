<?php

// WebAbility Version: >= 3.01.01
// Language: PHP
// Creation: 22/09/2002, Ing. Philippe Thomassigny
// Modification: on CVS

$client_profileaccess = new \dominion\DB_Table("client_profileaccess", "client_pra_", \dominion\DB_Table::TABLE);

$client_profileaccess->AddField(
  new \dominion\DB_FieldVarchar("profile", 30, new \dominion\DB_Check(\dominion\DB_Check::NN, \dominion\DB_Check::FK.".client_profile.client_pro_key", \dominion\DB_Check::DC) )
);


$client_profileaccess->AddField(
  new \dominion\DB_FieldVarchar("access", 30, new \dominion\DB_Check(\dominion\DB_Check::NN, \dominion\DB_Check::FK.".client_access.client_acc_key", \dominion\DB_Check::DC) )
);

?>