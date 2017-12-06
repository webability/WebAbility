<?php

// WebAbility Version: >= 3.01.01
// Language: PHP
// Creation: 25/11/2002, Ing. Philippe Thomassigny
// Modification: on CVS

// TABLE: user_profile:
// The differents profiles for administrators
// The profiles are cumulatives for administrators

$user_profile = new \dominion\DB_Table("user_profile", "user_pro_", \dominion\DB_Table::TABLE);

// Primary key, numeric, system assigned
$user_profile->AddField(
  new \dominion\DB_FieldVarchar("key", 30, new \dominion\DB_Check(\dominion\DB_Check::PK))
);

// The status of the profile. Any profile can be desactivated at any moment.
// 1 = ok, 2 = desactivated
$user_profile->AddField(
  new \dominion\DB_FieldInteger("status", new \dominion\DB_Check(\dominion\DB_Check::NN ) )
);

// The name of the profile.
$user_profile->AddField(
  new \dominion\DB_FieldVarchar("name", 255, new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

// Any comment on this profile.
$user_profile->AddField(
  new \dominion\DB_FieldText("descr")
);

?>