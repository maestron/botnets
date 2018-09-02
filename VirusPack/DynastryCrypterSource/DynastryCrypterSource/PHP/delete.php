<?php
	include 'config.php';
	
	if ($_SESSION['auth'] == md5($_SERVER['REMOTE_ADDR']))
	{
		$szUsername = $_POST['username'];
		if (!$szUsername)
			die();
		
		$hSql = mysql_connect('localhost', $db_username, $db_password);
		if (!$hSql)
		{
			echo 'Could not connect to database.';
			die();
		}
	
		mysql_select_db($db_name, $hSql);
		$hResult = mysql_query("DELETE FROM `$table_name` WHERE Username='$szUsername'");
		if (!$hResult)
		{
			echo 'Could not delete user.';
			die();
		}
		else
		{
			echo 'User deleted.<br><br>';
			echo '<a href="list.php">Back</a>';
		}
			
		mysql_close($hSql);	
	}
?>