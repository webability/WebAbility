<?php

// WebAbility Version: >= 3.01.01
// Language: PHP
// Creation: 22/09/2002, Ing. Philippe Thomassigny
// Modification: on CVS

$client_profileaccessextended = new \dominion\DB_Table("client_profileaccessextended", "client_pae_", \dominion\DB_Table::TABLE);

$client_profileaccessextended->AddField(
  new \dominion\DB_FieldVarchar("profile", 30, new \dominion\DB_Check(array(\dominion\DB_Check::NN, \dominion\DB_Check::FK.".client_profile.client_pro_key", \dominion\DB_Check::DC, \dominion\DB_Check::IN)) )
);

$client_profileaccessextended->AddField(
  new \dominion\DB_FieldVarchar("extaccess", 30, new \dominion\DB_Check(array(\dominion\DB_Check::NN, \dominion\DB_Check::FK.".client_accessextended.client_ace_key", \dominion\DB_Check::DC, \dominion\DB_Check::IN)) )
);

$client_profileaccessextended->AddField(
  new \dominion\DB_FieldVarchar("extkey", 255, new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

?>