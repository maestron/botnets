-- SUiCiDE DDoS Engine
-- (c) Cr4sh
-- www.cr4sh.h15.ru
--  
-- MySQL database dump 
-- 

-- --------------------------------------------------------

-- 
-- Table structure for table `irc`
-- 

CREATE TABLE `irc` (
  `irchost` char(30) NOT NULL default '',
  `ircport` char(11) NOT NULL default ''
);

-- --------------------------------------------------------

-- 
-- Table structure for table `plugins`
-- 

CREATE TABLE `plugins` (
  `name` char(255) NOT NULL default ''
);

-- --------------------------------------------------------

-- 
-- Table structure for table `stat`
-- 

CREATE TABLE `stat` (
  `nick` varchar(8) NOT NULL default '',
  `ip` varchar(15) default NULL,
  `time` varchar(20) default NULL,
  `command` varchar(80) default NULL,
  `info` text
);

-- --------------------------------------------------------

-- 
-- Table structure for table `tasks`
-- 

CREATE TABLE `tasks` (
  `nick` char(8) NOT NULL default '',
  `command` char(80) NOT NULL default '',
  `bnum` int(11) NOT NULL default '0',
  `executed` int(11) NOT NULL default '0'
);
