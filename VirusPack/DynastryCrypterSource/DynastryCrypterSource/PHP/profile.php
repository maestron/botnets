<?php
	include 'config.php';
	if ($_SESSION['auth'] == md5($_SERVER['REMOTE_ADDR']))
	{
		echo '<html>';
		echo '<title>Admin Profile</table>';
		echo '<body bgcolor="#BDBDBD"';
		echo '<center><table border=2 >';
		echo '<tr><td width="123"><a href="list.php"><center>Main</center></a></td>';
		echo '<td width="123"><a href="create.php"><center>Create</center></a></td>';
		echo '<td width="123"><a href="edit.php"><center>Edit</center></a></td>';
		echo '<td width="123"><a href="profile.php"><center>Profile</center></a></td>';
		echo '<td width="123"><a href="stats.php"><center>Stats</center></a></td>';
		echo '</tr></table></center><br><br>';
		echo '<center><form method="post" action="profile.php">';
		echo 'Admin Username:<br>';
		echo '<input type="text" name="admin_username" style="background-color: #DEDEDE" /><br>';
		echo 'Old Password:<br>';
		echo '<input type="password" name="old_password" style="background-color: #DEDEDE" /><br>';
		echo 'New Password:<br>';
		echo '<input type="password" name="new_password" style="background-color: #DEDEDE" /><br><br>';
		echo '<input type="submit" name="submit" value="Change" />';
		echo '</form></center>';
		echo '</body>';
		echo '</html>'; 
	}
	$old_password = $_POST['old_password'];
	$new_password = $_POST['new_password'];
	$admin_username = $_POST['admin_username'];
	
	if ($old_password && $new_password && $admin_username && $_POST['submit'])
	{
		$hSql = mysql_connect('localhost', $db_username, $db_password);
		if (!$hSql)
		{
			echo 'Could not connect to database.';
			die();
		}
		mysql_select_db($db_name, $hSql);
		$hResult = mysql_query("SELECT * FROM Admin");
		if ($hResult) 
		{
			$old_password = md5($old_password);
			$data = mysql_fetch_array($hResult);
			if ($data['Username'] == $admin_username && $data['MD5'] == $old_password)
			{
				mysql_select_db($db_name, $hSql);
				$new_password = md5($new_password);
				$hResult = mysql_query("UPDATE `Admin` SET MD5='$new_password'  WHERE Username='$admin_username'");
				if ($hResult)
					echo '<center>Password changed.</center>';
				else
					echo '<center>Could not update password.</center>';
			}
			else
				echo '<center>Old password incorrect.</center>';
		}
		else
			echo '<center>No database entries found.</center>';
	mysql_close($hSql);
	}
?>