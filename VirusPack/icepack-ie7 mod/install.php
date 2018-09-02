<?php
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	IcePack Lite Edition
-----------------------------------------------------
	2007 (c) IDT Group
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" 
"http://www.w3.org/TR/html4/loose.dtd">
<html>
	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=windows-1251">
		<title>Установка IcePack Platinum Edition</title>
	</head>
	<body>
		<?
		include "mysql.php";
		include "db.php";
		
		$db = new db;
		
		$db->query("DROP TABLE IF EXISTS statistics");
		$db->query("DROP TABLE IF EXISTS config");
		$db->query("DROP TABLE IF EXISTS ftp");
		$db->query("DROP TABLE IF EXISTS traffic");
		$db->query("CREATE TABLE `config` (`id` int(11) NOT NULL auto_increment, `vkey` varchar(255) default NULL, `value` varchar(1024) default NULL, PRIMARY KEY  (`id`)) ENGINE=MyISAM DEFAULT CHARSET=cp1251 AUTO_INCREMENT=1 ;");
		$db->query("CREATE TABLE `ftp` (`id` int(11) NOT NULL auto_increment,`data` varchar(255) NOT NULL,`valid` tinyint(4) NOT NULL,PRIMARY KEY  (`id`)) ENGINE=MyISAM AUTO_INCREMENT=1451 DEFAULT CHARSET=cp1251 AUTO_INCREMENT=1451 ;");
		$db->query("CREATE TABLE `statistics` (`id` int(10) unsigned NOT NULL auto_increment,`datetime` text,`ip` varchar(15) default NULL,`browser` varchar(255) default NULL,`type` varchar(255) default NULL,`os` varchar(255) default NULL,`country` varchar(255) default NULL,`referer` varchar(255) default NULL,`is_dw` tinyint(1) unsigned NOT NULL default '0',KEY `id` (`id`)) ENGINE=MyISAM DEFAULT CHARSET=cp1251 AUTO_INCREMENT=1 ;");
		$db->query("CREATE TABLE `traffic` (`id` int(11) NOT NULL,`count` int(11) NOT NULL,PRIMARY KEY  (`id`)) ENGINE=MyISAM DEFAULT CHARSET=cp1251;");
		$db->query("INSERT INTO `traffic` VALUES (1, 0);");

    ?>
		<div align="center">
			<h4>Установка завершена</h4>
			Войдите в панель управления (Имя/Пароль: root/toor) и измените настройки: <a href="admin/index.php?do=settings">настройки</a><br>Удалите <b>install.php</b>
	</body>
</html>
