<?php

// WebAbility Version: >= 6
// Module: client
// Language: PHP
// Creation: 20/02/2017
// Modification: on CVS

// TABLE: client_client,
// clients

$client_client = new \dominion\DB_Table("client_client", "client_cli_", \dominion\DB_Table::TABLE);

//PK, SEQUENCE
$client_client->AddField(
  new \dominion\DB_FieldInteger("key", new \dominion\DB_Check(array(\dominion\DB_Check::PK, \dominion\DB_Check::AI)))
);

// A ok, P pending, X banned
$client_client->AddField(
  new \dominion\DB_FieldVarchar("status", 1, new \dominion\DB_Check(array(\dominion\DB_Check::NN)))
);

$client_client->AddField(
  new \dominion\DB_FieldVarchar("name", 255, new \dominion\DB_Check(\dominion\DB_Check::NN))
);

$client_client->AddField(
  new \dominion\DB_FieldVarchar("lastname", 255, new \dominion\DB_Check(\dominion\DB_Check::NN))
);

$client_client->AddField(
  new \dominion\DB_FieldVarchar("avatar", 255)
);

//RAWURLENCODE, CLIENT MAIL
$client_client->AddField(
  new \dominion\DB_FieldVarchar("mail", 255, new \dominion\DB_Check(\dominion\DB_Check::NN))
);

//RAWURLENCODED, CLIENT PASSWORD
$client_client->AddField(
  new \dominion\DB_FieldVarchar("password", 127, new \dominion\DB_Check(\dominion\DB_Check::NN))
);

// origin, native, facebook, etc
$client_client->AddField(
  new \dominion\DB_FieldVarchar("origin", 10, new \dominion\DB_Check(array(\dominion\DB_Check::NN)) )
);

// geolocalization register
$client_client->AddField(
  new \dominion\DB_FieldVarchar("firstcountry", 5, new \dominion\DB_Check(\dominion\DB_Check::FK.'.country_country.country_cou_key'))
);

// geolocalizacion last connection
$client_client->AddField(
  new \dominion\DB_FieldVarchar("lastcountry", 5, new \dominion\DB_Check(\dominion\DB_Check::FK.'.country_country.country_cou_key'))
);

// DATETIME insert
$client_client->AddField(
  new \dominion\DB_FieldDateTime("date", new \dominion\DB_Check(\dominion\DB_Check::NN))
);

// DATETIME LAST ACTIVITY
$client_client->AddField(
  new \dominion\DB_FieldDateTime("datelast")
);

// DATETIME password expire
$client_client->AddField(
  new \dominion\DB_FieldDateTime("passwordexpire")
);

// DATETIME user expire
$client_client->AddField(
  new \dominion\DB_FieldDateTime("expire")
);

?>