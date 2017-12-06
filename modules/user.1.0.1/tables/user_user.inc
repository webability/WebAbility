<?php

// WebAbility Version: >= 6
// Language: PHP
// Creation: 28/11/2002, Ing. Philippe Thomassigny
// Modification: on CVS

// TABLE: user_user:
// All the administrators of the base system.

// Needed table: user_user

$user_user = new \dominion\DB_Table("user_user", "user_usr_", \dominion\DB_Table::TABLE);

// Key of the user, automatic consecutive
$user_user->AddField(
  new \dominion\DB_FieldInteger("key", new \dominion\DB_Check(array(\dominion\DB_Check::PK, \dominion\DB_Check::AI)) )
);

// The status of the administrator:
// X = Suspended, A = Active, S = Superuser  (superusers can connect to master and have all the rights by default)
$user_user->AddField(
  new \dominion\DB_FieldVarchar("status", 1, new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

// Name of the administrator.
$user_user->AddField(
  new \dominion\DB_FieldVarchar("name", 255, new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

// Username (login) of the administrator
$user_user->AddField(
  new \dominion\DB_FieldVarchar("un", 255, new \dominion\DB_Check(array(\dominion\DB_Check::NN, \dominion\DB_Check::UI)) )
);

// Password of the administrator
// natural if "not encrypted", or MD5 if the flag is "encrypted"
// If the flag is encrypted, recuperating the password is assigning any random password
$user_user->AddField(
  new \dominion\DB_FieldVarchar("pw", 255, new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

// Mail of the administrator
$user_user->AddField(
  new \dominion\DB_FieldVarchar("mail", 255, new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

// sex, M/F
$user_user->AddField(
  new \dominion\DB_FieldVarchar("sex", 1, new \dominion\DB_Check(array(\dominion\DB_Check::NN)) )
);

// fields of special data of user
// example: BOSS=...\nTEL=...\nUNIT=...
// Those fields are used into the data of the user
$user_user->AddField(
  new \dominion\DB_FieldText("fields")
);

// extra info
$user_user->AddField(
  new \dominion\DB_FieldText("info")
);

// The administrator who create or is responsible of this one.
// if null, it is a super user
$user_user->AddField(
  new \dominion\DB_FieldInteger("father", new \dominion\DB_Check(array(\dominion\DB_Check::FK.".user_user.user_usr_key", \dominion\DB_Check::TR, \dominion\DB_Check::IN)) )
);

// The date of creation
$user_user->AddField(
  new \dominion\DB_FieldDateTime("date", new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

?>