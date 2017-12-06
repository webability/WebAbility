<?php

// WebAbility Version: >= 3.01.01
// Language: PHP
// Creation: 22/09/2002, Ing. Philippe Thomassigny
// Modification: on CVS

$user_userprofile = new \dominion\DB_Table("user_userprofile", "user_usp_", \dominion\DB_Table::TABLE);

$user_userprofile->AddField(
  new \dominion\DB_FieldInteger("user", new \dominion\DB_Check(array(\dominion\DB_Check::NN, \dominion\DB_Check::FK.".user_user.user_usr_key", \dominion\DB_Check::DC, \dominion\DB_Check::IN)) )
);

$user_userprofile->AddField(
  new \dominion\DB_FieldVarchar("profile", 30, new \dominion\DB_Check(array(\dominion\DB_Check::NN, \dominion\DB_Check::FK.".user_profile.user_pro_key", \dominion\DB_Check::DC, \dominion\DB_Check::IN )) )
);

?>