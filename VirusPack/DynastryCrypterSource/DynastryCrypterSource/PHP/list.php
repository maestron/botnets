<?php
	include 'config.php';
	
	if ($_SESSION['auth'] == md5($_SERVER['REMOTE_ADDR']))
	{
		$hSql = mysql_connect('localhost', $db_username, $db_password);
		if (!$hSql)
		{
			echo 'Could not connect to database.';
			die();
		}
	
		mysql_select_db($db_name, $hSql);
		$hResult = mysql_query("SELECT * FROM `$table_name`");
		if ($hResult) 
		{
			echo '<html>';
			echo '<title>Users List</table>';
			echo '<center><body bgcolor="#BDBDBD"';
			echo '<center><table border=2 >';
			echo '<tr><td width="123"><a href="list.php"><center>Main</center></a></td>';
			echo '<td width="123"><a href="create.php"><center>Create</center></a></td>';
			echo '<td width="123"><a href="edit.php"><center>Edit</center></a></td>';
			echo '<td width="123"><a href="profile.php"><center>Profile</center></a></td>';
			echo '<td width="123"><a href="stats.php"><center>Stats</center></a></td>';
			echo '</tr></table></center><br><br>';
			echo '<table border="1">';
			echo '<tr>';
			echo '<td width="123">';
			echo '<center><b>Username</b></center>';
			echo '</td>';
			echo '<td width="123">';
			echo '<center><b>Hardware ID</b></center>';
			echo '</td>';
			echo '<td width="123">';
			echo '<center><b>Enabled</b></center>';
			echo '</td>';
			echo '</tr>';
			while ($data = mysql_fetch_array($hResult))
			{
				echo '<tr>';
				echo '<td width="123">';
				echo '<center><a href="edit.php?username=' . $data['Username'] .'&id=' . $data['HardwareID'] . ' ">' . $data['Username'] . '</a></center>'; 
				echo '</td>';
				echo '<td width="123">';
				echo '<center>' . $data['HardwareID'] . '</center>';
				echo '</td>';
				echo '<td width="123">';
				echo '<center>' . $data['Enabled'] . '</center>';
				echo '</td>';
				echo '</tr>';
			}
			echo '</table>';
			echo '</body>';
			echo '</html>';
		}
		mysql_close($hSql);
	}
?>

