<?php

// WebAbility Version: >= 3.01.01
// Language: PHP
// Creation: 22/09/2002, Ing. Philippe Thomassigny
// Modification: on CVS

$user_profileaccessextended = new \dominion\DB_Table("user_profileaccessextended", "user_pae_", \dominion\DB_Table::TABLE);

$user_profileaccessextended->AddField(
  new \dominion\DB_FieldVarchar("profile", 30, new \dominion\DB_Check(array(\dominion\DB_Check::NN, \dominion\DB_Check::FK.".user_profile.user_pro_key", \dominion\DB_Check::DC, \dominion\DB_Check::IN)) )
);

$user_profileaccessextended->AddField(
  new \dominion\DB_FieldVarchar("extaccess", 30, new \dominion\DB_Check(array(\dominion\DB_Check::NN, \dominion\DB_Check::FK.".user_accessextended.user_ace_key", \dominion\DB_Check::DC, \dominion\DB_Check::IN)) )
);

$user_profileaccessextended->AddField(
  new \dominion\DB_FieldVarchar("extkey", 255, new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

?>