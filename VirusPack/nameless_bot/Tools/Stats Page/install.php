<html dir="ltr">
<head>
<meta http-equiv="Content-Language" content="en-us">
<meta http-equiv="Content-Type" content="text/html; charset=windows-1252">
<title>NamelessBot - Stats Panel - Installer</title>
</head>
<body bgcolor="#FFFFFF">
<?php
include("./includes/config.php");
include("./includes/dbfunctions.php");

function create_tables()
{

$table = query ("CREATE TABLE `visitors` (
  `id` int(11) NOT NULL auto_increment,
  `ip_address` varchar(50) NOT NULL,
  `country` varchar(50) NOT NULL,
  `new` int(11) NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 AUTO_INCREMENT=1;");

if($table) return true;
else return false;
}

if (create_tables()) 
echo '</font><font color="#3A6D99">[+] </font><font color="#4A83B5">Table 
Visitors Created Successfully ..</font></b></font></p>
<p align="center"><font face="Arial" size="2"><b><font color="#4A83B5">&nbsp;</font></b><b><font color="#3A6D99">[-]</font><font color="#00FF00">
</font><font color="#3A6D99">Database Installed Successfully</font></b></font></p>';
else quite();
?>