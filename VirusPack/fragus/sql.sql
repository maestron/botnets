CREATE TABLE `donkeys` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `ip` int(10) unsigned NOT NULL DEFAULT '0',
  `seller` int(10) unsigned NOT NULL DEFAULT '0',
  `browser` set('MSIE','FIREFOX','OPERA','CHROME','SAFARI','OTHER') NOT NULL DEFAULT 'OTHER',
  `browser_version` varchar(10) NOT NULL DEFAULT '0',
  `os` set('95','98','ME','2000','2003','XP','VISTA','WIN7','MAC','LINUX','OTHER') NOT NULL DEFAULT 'OTHER',
  `os_version` set('SP1','SP2','SP3','SP4','OTHER') NOT NULL DEFAULT 'OTHER',
  `country` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `file` int(10) unsigned NOT NULL,
  `exploit` tinyint(2) unsigned NOT NULL DEFAULT '0',
  `status` set('NOT','LOAD','BACKCONNECT') NOT NULL DEFAULT 'NOT',
  `time` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`),
  UNIQUE KEY `ip` (`ip`)
) ENGINE=MyISAM DEFAULT CHARSET=cp1251 AUTO_INCREMENT=1 ;
 
 
 
CREATE TABLE `files` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(32) NOT NULL,
  `description` varchar(32) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=cp1251 AUTO_INCREMENT=1 ;
 
 
 
CREATE TABLE `sellers` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(20) NOT NULL,
  `hash` varchar(10) NOT NULL,
  `file` int(10) unsigned NOT NULL DEFAULT '0',
  `exploits` varchar(255) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=cp1251 AUTO_INCREMENT=1 ;