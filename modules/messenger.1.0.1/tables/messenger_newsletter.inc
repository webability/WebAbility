<?php

// TABLE: messenger_newsletter:
// All the recetas del bot of kiwilimon

$messenger_newsletter = new \dominion\DB_Table("messenger_newsletter", "messenger_new_", \dominion\DB_Table::TABLE);

// Key of the client, automatic consecutive
$messenger_newsletter->AddField(
  new \dominion\DB_FieldInteger("key", new \dominion\DB_Check(array(\dominion\DB_Check::PK, \dominion\DB_Check::AI)) )
);

// fecha
$messenger_newsletter->AddField(
  new \dominion\DB_FieldDate("date", new \dominion\DB_Check(array(\dominion\DB_Check::NN)) )
);

// Type
$messenger_newsletter->AddField(
  new \dominion\DB_FieldInteger("type", new \dominion\DB_Check(array(\dominion\DB_Check::NN)))
);

// Title
$messenger_newsletter->AddField(
  new \dominion\DB_FieldVarchar("title", 400)
);

// Text
$messenger_newsletter->AddField(
  new \dominion\DB_FieldVarchar("text", 400)
);

// image
$messenger_newsletter->AddField(
  new \dominion\DB_FieldVarchar("image", 400)
);

?>