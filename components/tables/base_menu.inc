<?php

// WebAbility Version: >= 3.01.01
// Language: PHP
// Creation: 22/09/2002, Ing. Philippe Thomassigny
// Modification: on CVS

$base_menu = new \dominion\DB_Table("base_menu", "base_men_", \dominion\DB_Table::TABLE);

$base_menu->AddField(
  new \dominion\DB_FieldVarchar("key", 60, new \dominion\DB_Check(array(\dominion\DB_Check::PK)) )
);

$base_menu->AddField(
  new \dominion\DB_FieldVarchar("module", 15, new \dominion\DB_Check(array(\dominion\DB_Check::NN, \dominion\DB_Check::FK.".base_module.base_mod_key", \dominion\DB_Check::DC)) )
);

$base_menu->AddField(
  new \dominion\DB_FieldInteger("order", new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

$base_menu->AddField(
  new \dominion\DB_FieldVarchar("theme", 30, new \dominion\DB_Check(array(\dominion\DB_Check::NN, \dominion\DB_Check::FK.".base_menutheme.base_mth_key", \dominion\DB_Check::DC, \dominion\DB_Check::IN)) )
);

$base_menu->AddField(
  new \dominion\DB_FieldVarchar("father", 60, new \dominion\DB_Check(array(\dominion\DB_Check::FK.".base_menu.base_men_key", \dominion\DB_Check::DC, \dominion\DB_Check::IN)) )
);

$base_menu->AddField(
  new \dominion\DB_FieldVarchar("template", 30 )
);

$base_menu->AddField(
  new \dominion\DB_FieldVarchar("name", 255, new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

$base_menu->AddField(
  new \dominion\DB_FieldVarchar("link", 255, new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

$base_menu->AddField(
  new \dominion\DB_FieldVarchar("params", 255 )
);

$base_menu->AddField(
  new \dominion\DB_FieldVarchar("icon", 255 )
);

$base_menu->AddField(
  new \dominion\DB_FieldVarchar("condition", 30 )
);

$base_menu->AddField(
  new \dominion\DB_FieldVarchar("help", 255 )
);

$base_menu->AddField(
  new \dominion\DB_FieldInteger("used", new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

$base_menu->AddField(
  new \dominion\DB_FieldDateTime("datelast", new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

?>