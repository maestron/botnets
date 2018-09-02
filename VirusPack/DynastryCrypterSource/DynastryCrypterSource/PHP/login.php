<?php
	include 'config.php';
	
	if ($_SESSION['auth'] == md5($_SERVER['REMOTE_ADDR']))
		header("Location: list.php");

	echo '<html>';
	echo '<title>SC-Protection System</table>';
	echo '<center><body bgcolor="#BDBDBD">';
	echo '<b><font size="+2">Admin Login</font></b><br><br>';
	echo '<form method="post" action="login.php">';
	echo 'Admin Login:<br>';
	echo '<input type="text" name="admin_login" /><br>';
	echo 'Password:<br>';
	echo '<input type="password" name="admin_password" /><br><br>';
	echo '<input type="submit" name="submit" value="Login" />';
	echo '</form>';
	echo '</body>';
	echo '</html>';

	if ($_POST['submit'])
	{
		if ($_POST['admin_login'] && $_POST['admin_password'])
		{
			$hSql = mysql_connect('localhost', $db_username, $db_password); 
			if (!$hSql)
			{
				echo 'Could not connect to database.';
				die();
			}
			$admin_username = mysql_real_escape_string(trim($_POST['admin_login']));
			$admin_password = md5(mysql_real_escape_string(trim($_POST['admin_password'])));
			mysql_select_db($db_name, $hSql);
			$hResult = mysql_query("SELECT * FROM Admin");
			if ($hResult) 
			{
				$data = mysql_fetch_array($hResult);
				if ($data['Username'] == $admin_username && $data['MD5'] == $admin_password)
				{
					$hResult = $_SESSION['auth'] = md5($_SERVER['REMOTE_ADDR']);
					if ($hResult)
					{
						echo '<script type="text/javascript">';
						echo 'window.location = "list.php"';
						echo '</script>';
					}
					else
						echo 'Could not save session.';
				}
				else
					echo 'Bad user/pass';
			}
			mysql_close($hSql);
		}
	}
?>