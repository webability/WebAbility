<?php

// WebAbility Version: >= 6
// Module: country
// Language: PHP
// Creation: 29/04/2017
// Modification: on CVS

// TABLE: country_country,
// countries and states

// Needed table: country_country (hierarchy)
// rules: key of 2 chars = country ISO 2 chars key
//        key > 2 chars = state in country (2 char ISO country + state number or abbr)

$country_country = new \dominion\DB_Table("country_country", "country_cou_", \dominion\DB_Table::TABLE);

// PK
$country_country->AddField(
  new \dominion\DB_FieldVarchar("key", 8, new \dominion\DB_check(\dominion\DB_Check::PK))
);

//
$country_country->AddField(
  new \dominion\DB_FieldVarchar("name", 100, new \dominion\DB_check(\dominion\DB_Check::NN))
);

//
$country_country->AddField(
  new \dominion\DB_FieldVarchar("father", 8, new \dominion\DB_check(array(\dominion\DB_Check::FK.".country_country.country_cou_key")))
);

// extra field (3 char ISO field, id of state, number of state, etc) if any
$country_country->AddField(
  new \dominion\DB_FieldVarchar("iso3", 3)
);

// php geo ip extra id if any (states)
$country_country->AddField(
  new \dominion\DB_FieldVarchar("geoip", 3)
);

?>