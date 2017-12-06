<?php

// WebAbility Version: >= 3.01.01
// Language: PHP
// Creation: 22/09/2002, Ing. Philippe Thomassigny
// Modification: on CVS

$base_syslog = new \dominion\DB_Table("base_syslog", "base_syl_", \dominion\DB_Table::LOG);

$base_syslog->AddField(
  new \dominion\DB_FieldInteger("key", new \dominion\DB_Check(array(\dominion\DB_Check::PK, \dominion\DB_Check::AI)) )
);

$base_syslog->AddField(
  new \dominion\DB_FieldDateTime("date", new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

$base_syslog->AddField(
  new \dominion\DB_FieldInteger("type", new \dominion\DB_Check(array(\dominion\DB_Check::NN, \dominion\DB_Check::FK.".base_syslogtype.base_slt_key", \dominion\DB_Check::TR, \dominion\DB_Check::IN)) )
);

$base_syslog->AddField(
  new \dominion\DB_FieldText("descr", new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

$base_syslog->AddField(
  new \dominion\DB_FieldText("url")
);

?>