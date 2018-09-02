DROP DATABASE IF EXISTS `PolySploits`;
CREATE DATABASE `PolySploits`;
USE PolySploits;

CREATE TABLE `hits` (
  `ip` char(15) NOT NULL default '',
  `country` char(7) NOT NULL default '',
  `browser` char(25) NOT NULL default '',
  `os` char(25) NOT NULL default '',
  `referer` char(255) NOT NULL default ''
) TYPE=MyISAM COMMENT='Статистика по хитах';

CREATE TABLE `hosts` (
  `ip` char(15) NOT NULL default '',
  `country` char(7) NOT NULL default '',
  `browser` char(25) NOT NULL default '',
  `os` char(25) NOT NULL default '',
  `referer` char(255) NOT NULL default ''
) TYPE=MyISAM COMMENT='Статистика по хостах';

CREATE TABLE `loads` (
  `ip` char(15) NOT NULL default '',
  `country` char(7) NOT NULL default '',
  `browser` char(25) NOT NULL default '',
  `os` char(25) NOT NULL default '',
  `referer` char(255) NOT NULL default ''
) TYPE=MyISAM COMMENT='Статистика по загрузках';
