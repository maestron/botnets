<?php
	// Config.php	
	
	// Zeiten
	$time_on = (2*60)+15;			// Zeit die er als online angezeigt wird in Sekunden
	$time_inaktiv = 2*24*60*60; 	// Zeit nachdem ein Bot als inaktiv gewertet wird
	$time_tot = 5*24*60*60; 		// Zeit ab die ein Bot als tot gewertet wird
	
	// Login
	$login_session_max = 5*60*60;	// Wie lange eine Session maximal dauern darf
	$login_session_inaktiv = 30*60;	// Wann Session inaktiv (Zeit die Vergangen ist Seit der letzten Aktion)
	
	
	// MySQL
	$mysql_server = "localhost";
	$mysql_user = "";
	$mysql_pw = "";
	$mysql_db = "";
	$link = mysql_connect($mysql_server, $mysql_user, $mysql_pw);
	mysql_select_db($mysql_db, $link);
?>