<?php
	include 'config.php';
	
	if ($_SESSION['auth'] == md5($_SERVER['REMOTE_ADDR']))
	{
		$szUsername = $HTTP_GET_VARS['username'];
		$ID = $HTTP_GET_VARS['id'];
		
		$enabled = $_POST['enabled'];
		$submit = $_POST['submit'];
		
		if (!$submit)
		{
			echo '<html>';
			echo '<title>Edit User</table>';
			echo '<body bgcolor="#BDBDBD"';
			echo '<center><table border=2 >';
			echo '<tr><td width="123"><a href="list.php"><center>Main</center></a></td>';
			echo '<td width="123"><a href="create.php"><center>Create</center></a></td>';
			echo '<td width="123"><a href="edit.php"><center>Edit</center></a></td>';
			echo '<td width="123"><a href="profile.php"><center>Profile</center></a></td>';
			echo '<td width="123"><a href="stats.php"><center>Stats</center></a></td>';
			echo '</tr></table></center><br><br>';
			echo '<center><form method="post" action="edit.php">';
			echo 'Username:';
			echo '<br>';
			echo '<input type="text" name="username" style="background-color: #DEDEDE" value=' . $szUsername . ' />';
			echo '<br>';
			echo 'Hardware ID:';
			echo '<br>';
			echo '<input type="text" name="id" style="background-color: #DEDEDE" value= ' .  $ID . ' />';
			echo '<br>';
			echo '<br>';
			echo 'Account Enabled: <input type="checkbox" name="enabled" value="1" />';
			echo '<br>';
			echo '<br>';
			echo '<input type="submit" name="submit" value="Edit" />';
			echo '</form><br><br>';
			echo 'Delete User: <br>';
			echo '<form method="post" action="delete.php">';
			echo '<input type="text" name="username" style="background-color: #DEDEDE" /><br><br>';
			echo '<input type="submit" name"submit" value="Delete" />';
			echo '</form>';
			echo '</center></body>';
			echo '</html><br>';
		}
		
		if ($submit)
		{
			$szUsername = $_POST['username'];
			$ID = $_POST['id'];
			$hSql = mysql_connect('localhost', $db_username, $db_password);
			if (!$hSql)
			{
				echo 'Could not connect to database.';
				die();
			}
	
			mysql_select_db($db_name, $hSql);
			$hResult = mysql_query("UPDATE `$table_name` SET HardwareID='$ID', Enabled='$enabled' WHERE Username='$szUsername'");
			if (!$hResult)
			{
				echo 'Could not update user.' . mysql_error();
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
	}
?>