<?php
	include('config.php');
	if (!($conid = mysql_connect($SQLHOST,$SQLLOGIN,$SQLPWD))) {
		die("mysql_connect error");
	}
	if (!mysql_select_db($SQLDB,$conid)) {
		die("mysql_select_db error");
	}

	if (!mysql_query("CREATE TABLE IF NOT EXISTS `".$TABLENAME."` (
  `id` int(11) NOT NULL auto_increment,
  `ti` int(11) NOT NULL,
  `os` tinyint(4) NOT NULL,
  `br` tinyint(4) NOT NULL,
  `cn` smallint(6) NOT NULL,
  `ip` int(11) NOT NULL,
  `ok` tinyint(4) NOT NULL,
  `sp` tinyint(4) NOT NULL default '0',
  `ma` tinyint(4) NOT NULL default '0',
  `mi` tinyint(4) NOT NULL default '0',
  UNIQUE KEY `ip` (`ip`),
  KEY `id` (`id`)
) ENGINE=MyISAM;",$conid)) die("mysql_query error");

	die("ok");
?>
