<?php

// WebAbility Version: >= 3.01.01
// Language: PHP
// Creation: 04/11/2002, Ing. Philippe Thomassigny
// Modification: on CVS

// TABLE: base_modulefile:
// Contains the reference of the files installed with and used by a module

$base_modulefile = new \dominion\DB_Table("base_modulefile", "base_mof_", \dominion\DB_Table::TABLE);

// Sequencial automatic key, assigned by system
$base_modulefile->AddField(
  new \dominion\DB_FieldInteger("key", new \dominion\DB_Check(array(\dominion\DB_Check::PK, \dominion\DB_Check::AI)) )
);

// The module owner of this file. It is a foreign key to base_module
$base_modulefile->AddField(
  new \dominion\DB_FieldVarchar("module", 15, new \dominion\DB_Check(array(\dominion\DB_Check::NN, \dominion\DB_Check::FK.".base_module.base_mod_key", \dominion\DB_Check::DC)) )
);

// The directory of the file, relative to the root of base base directory
$base_modulefile->AddField(
  new \dominion\DB_FieldVarchar("dir", 255, new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

// The name of the file. This is a natural no-encoded field, so names cannot require
// special characters like \, ", ', etc.
$base_modulefile->AddField(
  new \dominion\DB_FieldVarchar("name", 255, new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

// The date of the last modification of the file into the operating system
$base_modulefile->AddField(
  new \dominion\DB_FieldDateTime("date", new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

// The size of the file
$base_modulefile->AddField(
  new \dominion\DB_FieldInteger("size", new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

// The type of the file: R = Root usable library, A = Admin usable library, C = Cartridge usable Library (bean), O = Other files
$base_modulefile->AddField(
  new \dominion\DB_FieldVarchar("type", 1, new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

// The calling name for the wrappers and the modules wrapper (types R, A, C)
$base_modulefile->AddField(
  new \dominion\DB_FieldVarchar("callname", 255, null )
);

// The menu admin id (for type = A)
$base_modulefile->AddField(
  new \dominion\DB_FieldVarchar("menuid", 255, null )
);

// The father for menu path (type = A/R)
$base_modulefile->AddField(
  new \dominion\DB_FieldInteger("father", new \dominion\DB_Check(array(\dominion\DB_Check::FK.".base_modulefile.base_mof_key", \dominion\DB_Check::IN)) )
);

// The father for menu path (type = A/R)
$base_modulefile->AddField(
  new \dominion\DB_FieldText("variables")
);

?>