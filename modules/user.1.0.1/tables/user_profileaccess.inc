<?php

// WebAbility Version: >= 3.01.01
// Language: PHP
// Creation: 22/09/2002, Ing. Philippe Thomassigny
// Modification: on CVS

$user_profileaccess = new \dominion\DB_Table("user_profileaccess", "user_pra_", \dominion\DB_Table::TABLE);

$user_profileaccess->AddField(
  new \dominion\DB_FieldVarchar("profile", 30, new \dominion\DB_Check(\dominion\DB_Check::NN, \dominion\DB_Check::FK.".user_profile.user_pro_key", \dominion\DB_Check::DC) )
);


$user_profileaccess->AddField(
  new \dominion\DB_FieldVarchar("access", 30, new \dominion\DB_Check(\dominion\DB_Check::NN, \dominion\DB_Check::FK.".user_access.user_acc_key", \dominion\DB_Check::DC) )
);

?>