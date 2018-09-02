<?php
	include 'config.php';
	
	function XOREncryption($pString, $pCrypt)
    {
    	// String for crypted string
    	$strCrypted = "";
    	// Integer for cipher position
    	$intPos = 0;
    	// Integer for length of cipher string
    	$intCryptLen = strlen($pCrypt);
    	// Integer for length of passed string
    	$intStringLen = strlen($pString);
    	// Go through each character in passed string
    	for ($intCur = 0; $intCur < $intStringLen; $intCur++)
    	{
    		// Check key postion
    		if ($intPos >= $intCryptLen)
    			$intPos = 0;
    		// XOR character verse cipher
    		$strCrypted .= $pString[$intCur] ^ $pCrypt[$intPos];
    		// Go to next position in key
    		$intPos++;
    	}
    	
    	// Return crypted string
    	return $strCrypted;
    }
    
  if ($_SERVER['HTTP_USER_AGENT'] != 'USER_CHECK')
  	die();

	$szUsername = $HTTP_GET_VARS['username'];
	$ID = XOREncryption($HTTP_GET_VARS['id'], $first_xor_key);
	$PC_username = $HTTP_GET_VARS['pcusername'];
	$country = $HTTP_GET_VARS['loc'];
	$user_ip = $_SERVER['REMOTE_ADDR'];
	
	$szPadding = XOREncryption($ID, $second_xor_key) . Chr(0);
	
	$hSql = mysql_connect('localhost', $db_username, $db_password);
	if (!$hSql)
		die();
	
	mysql_select_db($db_name, $hSql);
	$hResult = mysql_query("SELECT * FROM `$table_name`");
	if ($hResult) 
	{
		while ($data = mysql_fetch_array($hResult))
		{
			if ($data['Username'] == $szUsername && $data['HardwareID'] == $ID && $data['Enabled'] == '1')
			{
				mysql_select_db($db_name, $hSql);
				$hResult2 = mysql_query("INSERT INTO `Stats`(Username, IPAddress, HardwareID, PCUsername, Country) VALUES('$szUsername', '$user_ip', '$ID', '$PC_username', '$country')");	
				if ($hResult2)
					echo 'User accepted: ' . $szPadding;
			}
		}
	}
	else
		echo 'No database entries found.';

	mysql_close($hSql);
?>