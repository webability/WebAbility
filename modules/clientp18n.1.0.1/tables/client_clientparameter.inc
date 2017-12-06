<?php

// TABLE: client_clientparameter:
// chef params of kiwilimon

$client_clientparameter = new \dominion\DB_Table("client_clientparameter", "kl_clp_", \dominion\DB_Table::TABLE);

$client_clientparameter->AddField(
  new \dominion\DB_FieldInteger("client", new \dominion\DB_Check(array(\dominion\DB_Check::NN, \dominion\DB_Check::FK.".client_client.client_cli_key", \dominion\DB_Check::DC, \dominion\DB_Check::MI.'.id')) )
);

$client_clientparameter->AddField(
  new \dominion\DB_FieldVarchar("id", 20, new \dominion\DB_Check(array(\dominion\DB_Check::NN, \dominion\DB_Check::IN)) )
);

$client_clientparameter->AddField(
  new \dominion\DB_FieldText("value")
);

?>