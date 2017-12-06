<?php

// WebAbility Version: >= 3.01.01
// Language: PHP
// Creation: 04/11/2002, Ing. Philippe Thomassigny
// Modification: on CVS

// TABLE: base_module:
// Modules and versions installed in the system
// The base "BASE" is also into this table

// Needed table: NONE

$base_module = new \dominion\DB_Table("base_module", "base_mod_", \dominion\DB_Table::SYSCATALOG);

// The key is 3-5 characters for Base internal components,
//   and 6 to 8 characters for User external components
$base_module->AddField(
  new \dominion\DB_FieldVarchar("key", 15, new \dominion\DB_Check(\dominion\DB_Check::PK) )
);

// The name describes what the module do. It is written in the installation language.
//   The is also an entry into the language theme of base system
$base_module->AddField(
  new \dominion\DB_FieldVarchar("name", 255, new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

// The verions is formatted xx.yy.zz where "xx" if major version number, "yy" release and "zz" the patch.
//   The system check the repository version of a module with this field, and compare it with the scripts version
$base_module->AddField(
  new \dominion\DB_FieldVarchar("version", 15, new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

// The version date contains the date of the official release of this module
$base_module->AddField(
  new \dominion\DB_FieldDate("versiondate", new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

// The date contains the last actualization or installation
$base_module->AddField(
  new \dominion\DB_FieldDateTime("date", new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

// The installed flag: 1 if installed, 0 if not
$base_module->AddField(
  new \dominion\DB_FieldInteger("installed", new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

// The examples installed flag: 1 if installed, 0 if not
$base_module->AddField(
  new \dominion\DB_FieldInteger("examples", new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

?>