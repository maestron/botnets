<?php
$new = $_GET['new'];
if (isset($new)) $newbot = 1; else $newbot = 0;
include ("./includes/config.php");
include ("./includes/geoip.php");
include ("./includes/dbfunctions.php");
checktables();
function detect_country($ip) {
        $gi = geoip_open ("includes/GeoIP.dat", GEOIP_STANDARD);
        $country = geoip_country_name_by_addr ($gi, $ip);
        if(empty($country)) $country = "Unknown";
        return $country;
}
function MSI_browser(){
$user_agent = $_SERVER["HTTP_USER_AGENT"];
	if(strpos($user_agent, 'MSIE') )
	{
		$browsers="Internet Explorer";
		$temp=explode( ";", substr( $user_agent, strpos( $user_agent, "MSIE" ) + 5 ) );
		$version=$temp[0];
return $version;
}
}

function ip(){
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
          if($ar[$i]!='')
          {$user_ip = $ar[$i];  break;   }
          if($i==sizeof($ar)-1){$user_ip = 'unknown';}
          }
       }
   return $user_ip;
}
$user_agent = $_SERVER["HTTP_USER_AGENT"];
$ip=ip();
$country = detect_country($ip);
$checkunique = query ("select ip_address from visitors where ip_address = '$ip' ");
if ( mysql_num_rows($checkunique) == 0 )
query ("insert into visitors (ip_address,country,new) values ('$ip' , '$country', '$newbot')");
?>
