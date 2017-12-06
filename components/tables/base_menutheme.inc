<?php

// WebAbility Version: >= 3.01.01
// Language: PHP
// Creation: 22/09/2002, Ing. Philippe Thomassigny
// Modification: on CVS

// TABLE: base_menutheme:

// Needed table: NONE

$base_menutheme = new \dominion\DB_Table("base_menutheme", "base_mth_", \dominion\DB_Table::CATALOG);

$base_menutheme->AddField(
  new \dominion\DB_FieldVarchar("key", 30, new \dominion\DB_Check(\dominion\DB_Check::PK) )
);

$base_menutheme->AddField(
  new \dominion\DB_FieldVarchar("module", 15, new \dominion\DB_Check(array(\dominion\DB_Check::NN, \dominion\DB_Check::FK.".base_module.base_mod_key", \dominion\DB_Check::DC)) )
);

$base_menutheme->AddField(
  new \dominion\DB_FieldInteger("order", new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

$base_menutheme->AddField(
  new \dominion\DB_FieldVarchar("name", 255, new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

$base_menutheme->AddField(
  new \dominion\DB_FieldVarchar("template", 30 )
);

$base_menutheme->AddField(
  new \dominion\DB_FieldVarchar("icon", 255 )
);

$base_menutheme->AddField(
  new \dominion\DB_FieldVarchar("cond", 30 )
);

$base_menutheme->AddField(
  new \dominion\DB_FieldVarchar("help", 255 )
);

?>