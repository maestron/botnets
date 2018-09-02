<?php
	include 'config.php';
	
	if ($_SESSION['auth'] == md5($_SERVER['REMOTE_ADDR']))
	{
		echo '<html>';
		echo '<title>Add User</table>';
		echo '<body bgcolor="#BDBDBD"';
		echo '<center><table border=2 >';
		echo '<tr><td width="123"><a href="list.php"><center>Main</center></a></td>';
		echo '<td width="123"><a href="create.php"><center>Create</center></a></td>';
		echo '<td width="123"><a href="edit.php"><center>Edit</center></a></td>';
		echo '<td width="123"><a href="profile.php"><center>Profile</center></a></td>';
		echo '<td width="123"><a href="stats.php"><center>Stats</center></a></td>';
		echo '</tr></table></center><br><br>';
		echo '<center><form method="post" action="create.php">';
		echo 'Username:';
		echo '<br>';
		echo '<input type="text" name="username" style="background-color: #DEDEDE" />';
		echo '<br>';
		echo 'Hardware ID:';
		echo '<br>';
		echo '<input type="text" name="id" style="background-color: #DEDEDE" />';
		echo '<br>';
		echo '<br>';
		echo 'Account Enabled: <input type="checkbox" name="enabled" />';
		echo '<br>';
		echo '<br>';
		echo '<input type="submit" name="submit" value="Create" />';
		echo '</center></body>';
		echo '</html';
		
		$szUsername = $_POST['username'];
		$ID = $_POST['id'];
		$enabled = $_POST['enabled'];
	
		if (!$szUsername || !$ID) 
			die();
	
		if ($enabled)
			$enabled = "1";
		$hSql = mysql_connect('localhost', $db_username, $db_password);
		if (!$hSql)
		{
			echo 'Could not connect to database.';
			die();
		}
	
		mysql_select_db($db_name, $hSql);
		$hResult = mysql_query("INSERT INTO `$table_name`(Username, HardwareID, Enabled) VALUES('$szUsername', '$ID', '$enabled')");
		if (!$hResult)
		{
			echo 'Could not insert user info.';
			die();
		}
		else
		{
			echo '<script type="text/javascript">';
			echo 'window.location = "list.php"';
			echo '</script>';
		}
	
		mysql_close($hSql);
	}
?>