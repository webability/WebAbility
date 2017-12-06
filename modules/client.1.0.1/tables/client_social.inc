<?php

// TABLE: client_social:
// client socials of kiwilimon

$client_social = new \dominion\DB_Table('client_social', 'client_cso_', \dominion\DB_Table::TABLE);

// primary key
$client_social->AddField(
  new \dominion\DB_FieldInteger('key', new \dominion\DB_Check(array(\dominion\DB_Check::PK, \dominion\DB_Check::AI)) )
);

// Client key
$client_social->AddField(
  new \dominion\DB_FieldInteger('client', new \dominion\DB_Check(array(\dominion\DB_Check::NN, \dominion\DB_Check::FK.'.client_client.client_cli_key', \dominion\DB_Check::DC, \dominion\DB_Check::IN)) )
);

// Client ID on Social network
$client_social->AddField(
  new \dominion\DB_FieldVarchar('id', 60, new \dominion\DB_Check(array(\dominion\DB_Check::NN)) )
);

// origin : Social network ID
$client_social->AddField(
  new \dominion\DB_FieldVarchar('origen', 20, new \dominion\DB_Check(array(\dominion\DB_Check::NN)) )
);

// 1 = active, 2 = unlinked, 3 = pending
$client_social->AddField(
  new \dominion\DB_FieldInteger('status', new \dominion\DB_Check(array(\dominion\DB_Check::NN)) )
);

// email
$client_social->AddField(
  new \dominion\DB_FieldVarchar('email', 255, new \dominion\DB_Check(array(\dominion\DB_Check::IN)) )
);

// first name
$client_social->AddField(
  new \dominion\DB_FieldVarchar('firstname', 255 )
);

// family name
$client_social->AddField(
  new \dominion\DB_FieldVarchar('familyname', 255 )
);

// Extra json social network object
$client_social->AddField(
  new \dominion\DB_FieldText('extra')
);

// Social network full image
$client_social->AddField(
  new \dominion\DB_FieldVarchar('avatar', 4000)
);

// Social network tiny image
$client_social->AddField(
  new \dominion\DB_FieldVarchar('avatarthumb', 4000)
);

// Password, null if social network, set if native
$client_social->AddField(
  new \dominion\DB_FieldVarchar('password', 255 )
);

// register timestamp
$client_social->AddField(
  new \dominion\DB_FieldDateTime('creationdate')
);

$client_social->AddField(
  new \dominion\DB_FieldDateTime('modificationdate')
);


?>