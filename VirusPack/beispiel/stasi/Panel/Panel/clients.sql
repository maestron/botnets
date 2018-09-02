--
-- Tabellenstruktur für Tabelle `clients`
--

CREATE TABLE IF NOT EXISTS `clients` (
  `id` int(11) NOT NULL auto_increment,
  `hwid` char(32) NOT NULL,
  `install` int(11) NOT NULL,
  `connect` int(11) NOT NULL,
  `cmd` longtext NOT NULL,
  `pcname` char(50) NOT NULL,
  `country` char(255) NOT NULL,
  `winver` char(100) NOT NULL,
  `nat` int(11) NOT NULL,
  KEY `id` (`id`)
) TYPE=MyISAM  AUTO_INCREMENT=9 ;
