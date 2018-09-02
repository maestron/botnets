<?php

if ($_GET['id'] != ''){
	$puntero = fopen('HID3.txt', 'r');
	while(!feof($puntero)){
		$base = explode('|', fgets($puntero));
		if($base[0] == $_GET['id']){
			fclose($puntero);
			$checksum = 0;
			for ($i=24; $i<35; $i++) {
				$checksum += $_GET['id']{$i} * $i;
			}
			echo 'OK|'.$base[1].'|'.$checksum;
			exit;
		}
	}
	fclose($puntero);
	echo "ER";
}else{
	echo "ER";
}

?>