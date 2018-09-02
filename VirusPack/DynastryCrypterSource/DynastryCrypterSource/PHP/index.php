<?php 
	include 'config.php';
	if ($_SESSION['auth'] != md5($_SERVER['REMOTE_ADDR']))
		header('Location: login.php');
	else
		header('Location: list.php');
?>