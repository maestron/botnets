<?php

include_once("config.php");

function antihack(){
	GLOBAL $user, $pass, $admin;
	if (@$user!=$admin['user'] || @$pass!=$admin['pass'])
	{
		include_once("html_admin_go.php");
		exit;
	}
}
antihack();
?>