CREATE TABLE `botlisting` (
`serial` VARCHAR( 200 ) NOT NULL ,
`name` VARCHAR( 200 ) NOT NULL ,
`status` VARCHAR( 200 ) NOT NULL ,
`time` VARCHAR( 20 ) NOT NULL ,
`ip` VARCHAR( 25 ) NOT NULL ,
`ID` INT( 20 ) NOT NULL AUTO_INCREMENT ,
PRIMARY KEY ( `ID` )
);

CREATE TABLE `loglisting` (
`ID` INT( 20 ) NOT NULL AUTO_INCREMENT ,
`command` VARCHAR( 800 ) NOT NULL ,
PRIMARY KEY ( `ID` )
);

CREATE TABLE `commandlisting` (
`botID` INT( 20 ) NOT NULL ,
`command` VARCHAR( 800 ) NOT NULL ,
`cmdID` INT( 20 ) NOT NULL AUTO_INCREMENT ,
PRIMARY KEY ( `cmdID` )
);