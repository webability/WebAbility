<?php

// TABLE: messenger_message:
// detalle de la sesion de chat

$messenger_message = new \dominion\DB_Table("messenger_message", "messenger_msg_", \dominion\DB_Table::TABLE);

// Key of the client, automatic consecutive
$messenger_message->AddField(
  new \dominion\DB_FieldInteger("key", new \dominion\DB_Check(array(\dominion\DB_Check::PK, \dominion\DB_Check::AI)) )
);

// client key
$messenger_message->AddField(
  new \dominion\DB_FieldInteger("client", new \dominion\DB_Check(array(\dominion\DB_Check::FK . '.client_client.client_cli_key', \dominion\DB_Check::IN)) )
);

// origin (can have more that one messener in the app)
// should be an origin table
$messenger_message->AddField(
  new \dominion\DB_FieldInteger("origin", new \dominion\DB_Check(array(\dominion\DB_Check::NN)) )
);

// echo
// 2 = yes (us to the user)
// 1 = no (user to us)
$messenger_message->AddField(
  new \dominion\DB_FieldInteger("echo", new \dominion\DB_Check(array(\dominion\DB_Check::NN)) )
);

// status
// 1 = not clasified
// 2 = user usefull
// 3 = spam, unusefull
// 4 = archived
// 10 = newsletter sent
$messenger_message->AddField(
  new \dominion\DB_FieldInteger("status", new \dominion\DB_Check(array(\dominion\DB_Check::NN)) )
);

// id of messenger
$messenger_message->AddField(
  new \dominion\DB_FieldVarchar("id", 60, new \dominion\DB_Check(array(\dominion\DB_Check::NN)) )
);

// messenger sequence
$messenger_message->AddField(
  new \dominion\DB_FieldInteger("seq")
);

// type
$messenger_message->AddField(
  new \dominion\DB_FieldVarchar("type", 10, new \dominion\DB_Check(array(\dominion\DB_Check::NN)) )
);

// text message
$messenger_message->AddField(
  new \dominion\DB_FieldVarchar("text", 4096, new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

// The date of creation
$messenger_message->AddField(
  new \dominion\DB_FieldDateTime("date", new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

// extra: JSON que with extra message data (audio video, files etc)
$messenger_message->AddField(
  new \dominion\DB_FieldVarchar("extra", 4096)
);

// message id
$messenger_message->AddField(
  new \dominion\DB_FieldVarchar("mid", 40, new \dominion\DB_Check(array(\dominion\DB_Check::IN)) )
);

// timestamp unix message received
$messenger_message->AddField(
  new \dominion\DB_FieldInteger("received")
);

// timestamp message read
$messenger_message->AddField(
  new \dominion\DB_FieldInteger("read")
);

// operator
$messenger_message->AddField(
  new \dominion\DB_FieldInteger("operator", new \dominion\DB_Check(array(\dominion\DB_Check::FK . '.user_user.user_usr_key')) )
);

// mass message / newsletter
$messenger_message->AddField(
  new \dominion\DB_FieldInteger("newsletter", new \dominion\DB_Check(array(\dominion\DB_Check::FK . '.messenger_newsletter.messenger_new_key')) )
);

?>