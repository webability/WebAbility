<?php

// WebAbility Version: >= 3.01.01
// Language: PHP
// Creation: 22/09/2002, Ing. Philippe Thomassigny
// Modification: on CVS

$base_syslogtype = new \dominion\DB_Table("base_syslogtype", "base_slt_", \dominion\DB_Table::SYSCATALOG);

$base_syslogtype->AddField(
  new \dominion\DB_FieldInteger("key", new \dominion\DB_Check(array(\dominion\DB_Check::PK)))
);

$base_syslogtype->AddField(
  new \dominion\DB_FieldVarchar("name", 255, new \dominion\DB_Check(\dominion\DB_Check::NN))
);

?>