<?php
	include 'config.php';
	if ($_SESSION['auth'] == md5($_SERVER['REMOTE_ADDR']))
	{
		echo '<html>';
		echo '<title>User Stats</table>';
		echo '<body bgcolor="#BDBDBD"';
		echo '<center><table border=2 >';
		echo '<tr><td width="123"><a href="list.php"><center>Main</center></a></td>';
		echo '<td width="123"><a href="create.php"><center>Create</center></a></td>';
		echo '<td width="123"><a href="edit.php"><center>Edit</center></a></td>';
		echo '<td width="123"><a href="profile.php"><center>Profile</center></a></td>';
		echo '<td width="123"><a href="stats.php"><center>Stats</center></a></td>';
		echo '</tr></table><br><br>';
		echo '<form method="post" action="stats.php">';
		echo '<input type="submit" name="submit" value="Reset Stats" />';
		echo '</form>';
		
		$hSql = mysql_connect('localhost', $db_username, $db_password);
		if (!$hSql)
		{
			echo 'Could not connect to database.';
			die();
		}
		
		if ($_POST['submit'])
		{
			mysql_select_db($db_name, $hSql);
			$hResult = mysql_query("TRUNCATE TABLE Stats");
		}
	
		mysql_select_db($db_name, $hSql);
		$hResult = mysql_query("SELECT * FROM Stats");
		if ($hResult) 
		{
			echo '<center><table border="1">';
			echo '<tr>';
			echo '<td width="95">';
			echo '<center><b>Username</b></center>';
			echo '</td>';
			echo '<td width="95">';
			echo '<center><b>IP</b></center>';
			echo '</td>';
			echo '<td width="95">';
			echo '<center><b>Hardware ID</b></center>';
			echo '</td>';
			echo '<td width="95">';
			echo '<center><b>PC Username</b></center>';
			echo '</td>';
			echo '<td width="95">';
			echo '<center><b>Country</b></center>';
			echo '</td>';
			echo '</tr>';
			while ($data = mysql_fetch_array($hResult))
			{
				echo '<tr>';
				echo '<td width="95">';
				echo '<center>' . $data['Username'] . '</center>'; 
				echo '</td>';
				echo '<td width="95">';
				echo '<center>' . $data['IPAddress'] . '</center>'; 
				echo '</td>';
				echo '<td width="95">';
				echo '<center>' . $data['HardwareID'] . '</center>';
				echo '</td>';
				echo '<td width="95">';
				echo '<center>' . $data['PCUsername'] . '</center>';
				echo '</td>';
				echo '<td width="95">';
				echo '<center>' . $data['Country'] . '</center>';
				echo '</td>';
				echo '</tr>';
			}
		}
		echo '</table></body></html>';
		mysql_close($hSql);
	}
?>