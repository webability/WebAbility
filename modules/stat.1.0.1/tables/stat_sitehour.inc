<?php

// WebAbility Version: >= 3.01.01
// Language: PHP
// Creation: 22/09/2002, Ing. Philippe Thomassigny
// Modification: on CVS

// TABLE: stat_sitehour:

// Needed table: NONE

// This table doesnt use FK on page, browser, language or client, it's just a statistical table.

$stat_sitehour = new \dominion\DB_Table("stat_sitehour", "stat_sto_", \dominion\DB_Table::LOG );

$stat_sitehour->AddField(
  new \dominion\DB_FieldInteger("key", new \dominion\DB_Check(array(\dominion\DB_Check::PK, \dominion\DB_Check::AI)) )
);


$stat_sitehour->AddField(
  new \dominion\DB_FieldVarchar("page", 50, new \dominion\DB_Check(array(\dominion\DB_Check::NN, \dominion\DB_Check::MU.".year.month.day.hour")))
);

$stat_sitehour->AddField(
  new \dominion\DB_FieldInteger("year", new \dominion\DB_Check(array(\dominion\DB_Check::NN)) )
);

$stat_sitehour->AddField(
  new \dominion\DB_FieldInteger("month", new \dominion\DB_Check(array(\dominion\DB_Check::NN)) )
);

$stat_sitehour->AddField(
  new \dominion\DB_FieldInteger("day", new \dominion\DB_Check(array(\dominion\DB_Check::NN)) )
);

$stat_sitehour->AddField(
  new \dominion\DB_FieldInteger("hour", new \dominion\DB_Check(array(\dominion\DB_Check::NN)) )
);

$stat_sitehour->AddField(
  new \dominion\DB_FieldInteger("numaccess", new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

$stat_sitehour->AddField(
  new \dominion\DB_FieldDateTime("lastaccess", new \dominion\DB_Check(\dominion\DB_Check::NN) )
);


// in ms
$stat_sitehour->AddField(
  new \dominion\DB_FieldReal("timeaccess", new \dominion\DB_Check(\dominion\DB_Check::NN) )
);


// average time inside load ms
$stat_sitehour->AddField(
  new \dominion\DB_FieldReal("time1", new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

// time inside create base ms
$stat_sitehour->AddField(
  new \dominion\DB_FieldReal("time2", new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

// time inside calculate page ms
$stat_sitehour->AddField(
  new \dominion\DB_FieldReal("time3", new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

// time inside create page ms
$stat_sitehour->AddField(
  new \dominion\DB_FieldReal("time4", new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

// time print ms
$stat_sitehour->AddField(
  new \dominion\DB_FieldReal("time5", new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

// time outside all ms
$stat_sitehour->AddField(
  new \dominion\DB_FieldReal("time6", new \dominion\DB_Check(\dominion\DB_Check::NN) )
);

?>