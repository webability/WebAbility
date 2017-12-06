<?php

// WebAbility Version: >= 3.01.01
// Language: PHP
// Creation: 25/11/2002, Ing. Philippe Thomassigny
// Modification: on CVS

// TABLE used: user_flag

$user_flag = new \dominion\DB_Table("user_flag", "user_flg_", \dominion\DB_Table::TABLE);

$user_flag->AddField(
  new \dominion\DB_FieldInteger("user", new \dominion\DB_Check(array(\dominion\DB_Check::NN, \dominion\DB_Check::FK.".user_user.user_usr_key", \dominion\DB_Check::DC, \dominion\DB_Check::IN)) )
);

$user_flag->AddField(
  new \dominion\DB_FieldVarchar("id", 60, new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

$user_flag->AddField(
  new \dominion\DB_FieldText("value")
);

?>