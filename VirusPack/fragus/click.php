<?php
include("./secure/config.php");
mysql_connect($config['MysqlHost'], $config['MysqlUser'], $config['MysqlPassword']) or die("Could not connect to mysql server.");
mysql_select_db($config['MysqlDbname']) or die("Could not select database.");
mysql_query("UPDATE `donkeys` SET `status` = 'BACKCONNECT' WHERE `ip` = INET_ATON('" . mysql_real_escape_string($_SERVER['REMOTE_ADDR']) . "')");
mysql_close();
?>