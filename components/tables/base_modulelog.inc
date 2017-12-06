<?php

// WebAbility Version: >= 3.01.01
// Language: PHP
// Creation: 04/11/2002, Ing. Philippe Thomassigny
// Modification: on CVS

// TABLE: base_modulelog:
// Log of Modules and versions changes installed in the system

$base_modulelog = new \dominion\DB_Table("base_modulelog", "base_mol_", \dominion\DB_Table::LOG);

// Sequencial automatic key, assigned by system
$base_modulelog->AddField(
  new \dominion\DB_FieldInteger("key", new \dominion\DB_Check(array(\dominion\DB_Check::PK, \dominion\DB_Check::AI)) )
);

// the module upon this log entry. Foreign key to the base_module table.
$base_modulelog->AddField(
  new \dominion\DB_FieldVarchar("module", 15, new \dominion\DB_Check(array(\dominion\DB_Check::NN, \dominion\DB_Check::FK.".base_module.base_mod_key", \dominion\DB_Check::DC, \dominion\DB_Check::IN)) )
);

// The version of the module upon this log entry.
//   It is the same format as the base_mod_version field.
$base_modulelog->AddField(
  new \dominion\DB_FieldVarchar("version", 15, new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

// The date and time of log entry
$base_modulelog->AddField(
  new \dominion\DB_FieldDateTime("date", new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

// The description of the action executed upon this log entry
$base_modulelog->AddField(
  new \dominion\DB_FieldVarchar("action", 255, new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

?>