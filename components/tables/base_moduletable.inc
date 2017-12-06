<?php

// WebAbility Version: >= 3.01.01
// Language: PHP
// Creation: 04/11/2002, Ing. Philippe Thomassigny
// Modification: on CVS

// TABLE: base_moduletable:
// Tables into the system loaded by each module
// This information is used for inter-modules delete cascade and integrity check

$base_moduletable = new \dominion\DB_Table("base_moduletable", "base_mot_", \dominion\DB_Table::CATALOG);

// The key is the table identification
$base_moduletable->AddField(
  new \dominion\DB_FieldVarchar("key", 100, new \dominion\DB_Check(\dominion\DB_Check::PK) )
);

// The module owner of the table. Foreign key to the table base_module
$base_moduletable->AddField(
  new \dominion\DB_FieldVarchar("module", 15, new \dominion\DB_Check(array(\dominion\DB_Check::NN, \dominion\DB_Check::FK.".base_module.base_mod_key", \dominion\DB_Check::DC, \dominion\DB_Check::IN)) )
);

?>