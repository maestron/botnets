<?php

error_reporting (1);
include('dll/dll_Set.php');
include('dll/dll_MySQL.php');
include('dll/dll_Handle.php');

$id = preg_replace("/[^\w_\.\-]/", "", $_REQUEST["id"]);
   
if(strlen($id)==32): 
OnMySQLQuery("",0);  
$m_lst = OnMySQLQuery("SELECT * FROM dld where lid='".$id."' ",3);
$m_arr = mysql_fetch_assoc($m_lst);
$file="fls/".$m_arr["dld"];
OnMySQLQuery("UPDATE dld set cnt=cnt+1 where lid='".$id."' ",3);
$myip=getenv("REMOTE_ADDR");
// ip2geo
        include("Service/IP2Location.inc");
        $ip = IP2Location_open("Service/IP-COUNTRY-REGION-CITY.BIN", IP2LOCATION_STANDARD);
        $record = IP2Location_get_record($ip, $myip, COUNTRYLONG);
        $cntry = addslashes($record->country_long);



if ($m_arr["dld"]!="" && file_exists($file))
   {
   OnMySQLQuery("INSERT INTO ".$m_arr["dtbl"]." (ip,country) VALUES('".$myip."','".$cntry."')",3);         
           header("Content-type: application/octet-stream");
           header("Content-Disposition: attachment; filename=".$m_arr["dld"]."");
           header("Content-Transfer-Encoding: binary");
           header('Content-Length: '.filesize($file));
           @set_time_limit(0);
           @readfile($file);
   }
   OnMySQLQuery("",5);
           exit;   
endif;
echo "denide!";
exit;
?>

