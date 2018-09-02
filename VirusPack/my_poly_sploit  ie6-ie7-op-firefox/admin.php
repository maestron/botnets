<?php
	include_once("config.php");
	include_once("vars.php");
	function admin(){
		GLOBAL $user,$pass,$admin;
		if (@$user!=$admin['user'] || @$pass!=$admin['pass'])
		{
			include_once("html_admin.php");
			return 0;
		}
			setcookie("user", $user);
			setcookie("pass", $pass);
			include_once("html_panel_go.php");
			return 0;
	}
	admin();
?>