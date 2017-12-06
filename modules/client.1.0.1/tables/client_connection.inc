<?php

// WebAbility Version: >= 3.01.01
// Language: PHP
// Creation: 22/09/2002, Ing. Philippe Thomassigny
// Modification: on CVS

// TABLE: client_connection:

$client_connection = new \dominion\DB_Table("client_connection", "client_con_", \dominion\DB_Table::TABLE);

$client_connection->AddField(
  new \dominion\DB_FieldInteger("key", new \dominion\DB_Check(array(\dominion\DB_Check::PK, \dominion\DB_Check::NN, \dominion\DB_Check::AI)) )
);

$client_connection->AddField(
  new \dominion\DB_FieldInteger("client", new \dominion\DB_Check(array(\dominion\DB_Check::NN, \dominion\DB_Check::FK.".client_client.client_cli_key", \dominion\DB_Check::DC, \dominion\DB_Check::IN)) )
);

$client_connection->AddField(
  new \dominion\DB_FieldDateTime("date", new \dominion\DB_Check(array(\dominion\DB_Check::NN, \dominion\DB_Check::IN)) )
);

$client_connection->AddField(
  new \dominion\DB_FieldDateTime("datelast", new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

$client_connection->AddField(
  new \dominion\DB_FieldVarchar("id", 24, new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

$client_connection->AddField(
  new \dominion\DB_FieldVarchar("ip", 32, new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

?>