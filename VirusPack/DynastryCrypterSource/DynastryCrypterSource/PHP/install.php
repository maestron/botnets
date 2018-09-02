<?php 
	echo '<html>';
	echo '<title>SC-Protection System</table>';
	echo '<center><body bgcolor="#BDBDBD"';
	echo '<b><font size="+2">Installation</font></b><br><br>';
	echo '<form method="post" action="install.php">';
	echo 'Admin Login:<br>';
	echo '<input type="text" name="admin_login" style="background-color: #DEDEDE" /><br>';
	echo 'Password:<br>';
	echo '<input type="password" name="admin_password" style="background-color: #DEDEDE" /><br><br>';
	echo '<input type="submit" name="submit" value="Install" />';
	echo '</form>';
	echo '</body>';
	echo '</html>';
	
	$admin_username = $_POST['admin_login'];
	$admin_password = $_POST['admin_password'];
	
	if ($admin_username && $admin_password)
	{
		include 'config.php';
		
		$hSql = mysql_connect('localhost', $db_username, $db_password);
		if (!$hSql)
		{
			echo 'Could not connect to database.';
			die();
		}
		mysql_select_db($db_name, $hSql);
		$hResult = mysql_query("CREATE TABLE Admin(Username varchar(20), MD5 varchar(32))");
		if ($hResult)
		{
			$admin_password = md5($admin_password);
			$hResult = mysql_query("INSERT INTO Admin(Username, MD5) VALUES('$admin_username', '$admin_password')");
			if ($hResult)
			{
				mysql_select_db($db_name, $hSql);
				$hResult = mysql_query("CREATE TABLE `$table_name`(Username varchar(20), HardwareID varchar(20), Enabled varchar(1))");
				if ($hResult)
				{
					mysql_select_db($db_name, $hSql);
					$hResult = mysql_query("CREATE TABLE Stats(Username varchar(20), IPAddress varchar(20), HardwareID varchar(20), PCUsername varchar(30), Country varchar(30))");
					if ($hResult)
					{
						echo 'Installed.';
						echo '<br><br><b>Please delete install.php.</b>';
					}
					else
						echo 'Error creating stats table';
				}
				else
					echo 'Error creating users table.';
			}
			else 
				echo 'Error inserting admin info.';
		}
		else
		 echo 'Error adding admin table.';
	mysql_close($hSql);	
	}
	
?>