<?php
include_once('../mysqllog.php');
$check = $_GET['check'];

$link = mysql_connect($mysql_host, $mysql_login, $mysql_pass) or die("Could not connect: " . mysql_error());
mysql_select_db($mysql_db, $link) or die("Could not select : " . mysql_error());
$query = 'UPDATE socks SET  `used` = 1 WHERE `ip` = "'. $check . '"';
$result = mysql_query($query, $link) or die("Could not execute: " . mysql_error());
$query = 'COMMIT';
$result = mysql_query($query, $link) or die("Could not execute: " . mysql_error());
mysql_close($link);
echo "<div align=center><FONT color=red><B>POMECEN KAK USED</B></FONT></div>\r\n";

?>
