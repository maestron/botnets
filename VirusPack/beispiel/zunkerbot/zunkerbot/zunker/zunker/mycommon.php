<?php

$UNKER_VERSION ='1.4.3-RC4';
$UNKER_RELEASE_DATE ='14.05.2006';


//User
$user = 'root';
$pass = 'pass';

//Main Database connection----------------------------------------
$BOT_DBHOST='localhost';
$BOT_DBLOGIN='lo';
$BOT_DBPASS='lo';

//Main Database option
$BOT_DBNAME='lo';
$BOT_DBTBL='bots';
$BOT_CRYPT_PARAM='0';





//Server address
$S_ADDR = 'http://'.@$HTTP_SERVER_VARS['SERVER_NAME'];

//Enter on page----------------------------------------
$login_index='index.php';

//Img way;----------------------------------------
$img_way='img/';

//Login Type
$Login_type="2";


//Statistic----------------------------------------
$MATCH=10;
$MATCH_COUNTRIES=20;
$SOFT_TBL = 'antisoft_glob';



//Default land for Global-soft statistic, where soft statistics is show.
$STAT_DEF_LAND_SS = 'COUNTRIES';








////////////////////////////////////////UNKER-BASED properties (don`t need to change)

$tm = array(
"lday"=>date('d',time()),
"ltme"=>date('H:i:s',time()),
"lhour"=>date('H',time()),
"lmonth"=>date('m',time()),
"lyear"=>date('y',time()),
"lrep"=>date('d',time()).'/'.date('m',time()).'/'.date('y',time()),
"lrep_prev_day"=>(date('d',time())-1).'/'.date('m',time()).'/'.date('y',time())
);



?>