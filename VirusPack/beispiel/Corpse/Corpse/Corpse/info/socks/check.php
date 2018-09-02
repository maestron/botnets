<?php
$ip = $_GET['ip'];
$port = $_GET['hport'];
$socks = $_GET['port'];
$site = "http://209.160.72.83/info/test.txt";

$time=microtime();
$time=explode(' ',$time);
$time_start=$time[1]+$time[0];

$fp = @fsockopen($ip,$port);
if(@!$fp) {
    echo "NE RABOTAET! :(";
} else {
	fputs($fp, "GET $site HTTP/1.0\r\nHost: $ip\r\n\r\n");

	$time=microtime();
	$time=explode(' ',$time);
	$time_stop=$time[1]+$time[0];
	$timetoanswer=$time_stop-$time_start;
	$timetoanswer=substr($timetoanswer,0,5);

	echo '<HTML><LINK href="main.css" type=text/css rel=stylesheet><BODY><BR><TABLE WIDTH=80% cellpadding=0 cellspacing=0 border=0 align=center>';
	echo "<TR><TD width=60%>SPEED:</TD><TD width=60%>$timetoanswer</TD></TR><TR><TD width=60%>SOCKS 4/5:</TD><TD>$ip:$socks</TD></TR>";
	echo "<TR><TD width=60%>HTTP:</TD><TD>$ip:$port</TD></TR><TR><TD colspan=2 align=center>good ;)</TD></TR></TABLE>";
	echo "<TR><TD colspan=2><div align=center><INPUT type=button class=\"BUTTON2\" value=\"MARK AS USED\" onClick=\"window.open('mark.php?check=$ip','child','scrollbars=no,width=250,height=100');\"></div></TD></TR>";
}
fclose($fp);

?>
