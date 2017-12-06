<?php

// WebAbility Version: >= 3.01.01
// Language: PHP
// Creation: 22/09/2002, Ing. Philippe Thomassigny
// Modification: on CVS

$user_connectionhistory = new \dominion\DB_Table("user_connectionhistory", "user_coh_", \dominion\DB_Table::HISTORY);

$user_connectionhistory->AddField(
  new \dominion\DB_FieldInteger("key", new \dominion\DB_Check(array(\dominion\DB_Check::NN)) )
);

$user_connectionhistory->AddField(
  new \dominion\DB_FieldInteger("user", new \dominion\DB_Check(array(\dominion\DB_Check::NN, \dominion\DB_Check::FK.".user_user.user_usr_key", \dominion\DB_Check::TR, \dominion\DB_Check::IN)) )
);

$user_connectionhistory->AddField(
  new \dominion\DB_FieldDateTime("date", new \dominion\DB_Check(array(\dominion\DB_Check::NN, \dominion\DB_Check::IN)) )
);

$user_connectionhistory->AddField(
  new \dominion\DB_FieldDateTime("datelast", new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

$user_connectionhistory->AddField(
  new \dominion\DB_FieldVarchar("id", 24, new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

$user_connectionhistory->AddField(
  new \dominion\DB_FieldVarchar("ip", 15, new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

?>