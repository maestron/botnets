<?php

include_once('auth.php');

require('mycommon.php');
require('html.php');

$ttt=microtime();
$ttt=((double)strstr($ttt, ' ')+(double)substr($ttt,0,strpos($ttt,' ')));

$STAT_TBL = '`stat_down`';
$HEAD_NADPIS = "Download file counters&nbsp;";
(!isset($_GET['p']) ? $_GET['p']='down' : '');

$PLOT_STYLE = array(
'bar'=>'#c0cbeb',
'bg'=>'#e5f2f7',
'x_bg'=>'606680'//#808ebf
);



$_ = array(
'tstat_Jan'=>'Jan', //Months
'tstat_Feb'=>'Feb',
'tstat_Mar'=>'Mar',
'tstat_Apr'=>'Apr',
'tstat_May'=>'May',
'tstat_Jun'=>'Jun',
'tstat_Jul'=>'Jul',
'tstat_Aug'=>'Aug',
'tstat_Sep'=>'Sep',
'tstat_Oct'=>'Oct',
'tstat_Nov'=>'Nov',
'tstat_Dec'=>'Dec',
'tstat_Su'=>'Sun', //Day of week
'tstat_Mo'=>'Mon',
'tstat_Tu'=>'Tue',
'tstat_We'=>'Wen',
'tstat_Th'=>'Thu',
'tstat_Fr'=>'Fri',
'tstat_Sa'=>'Sat',);



$mres = @mysql_connect($BOT_DBHOST,$BOT_DBLOGIN,$BOT_DBPASS) or die("Could not connect to DB.<br> MySQL Message:".mysql_error());

if(!mysql_select_db($BOT_DBNAME))
die('Could not select DB <br> Mysql message:'.mysql_error());


if(isset($_GET['clear'])){
	clear_stats($_GET['clear'],$mres);
	header('Location: gettime.php'.(isset($_GET['p']) ? '?p='.$_GET['p'] : ''));
};



$STAT=3;
$STAT_TIME=1;
include_once('head.php');


if(isset($_GET['p'])){

	if($_GET['p']=='down')
	$STAT_TBL = '`stat_down`';

	switch ($_GET['p']){
		case 'down':
			$STAT_TBL = '`stat_down`';
			$PLOT_STYLE['x_bg']="#606680";
			break;

		case 'rap':
			$STAT_TBL = '`stat_bot_rap`';
			$HEAD_NADPIS = "Bot`s raports ";
			$PLOT_STYLE['x_bg']="#808ebf";
			break;
			
		case 'sent':
			$STAT_TBL = '`stat_msgsent`';
			$HEAD_NADPIS = "Zupacha: Messages sent";
			$PLOT_STYLE['x_bg']="#F8C5AF";
			break;

	};

};






if(isset($_GET['x']))
add_record($mres);




HTML_HEADER($HEAD_NADPIS);

//echo HTML_STAT_GETTIME();



// Functions ++++++++++++++++++++++++++++++++++++++++



function clear_stats($type,$mres){
	global $STAT_TBL;


	if($type=='all'){

		$q = "DELETE FROM $STAT_TBL";
		mysql_query($q,$mres)or die('Could not delete.'.mysql_error());;
		return  mysql_affected_rows($mres);
	};


	$q = "DELETE FROM $STAT_TBL where `date`='".addslashes($type)."'";
	mysql_query($q,$mres) or die('Could not delete.'.mysql_error());
	return  mysql_affected_rows($mres);


};



function get_month($x,$mres){
	global $tm,$_,$STAT_TBL;

	$year = $tm['lyear']-1;

	$y = array();

	for($i=0;$i<count($x);$i++){

		if($x[$i]=='1')
		$year = $tm['lyear'];

		if(strlen($year)<2)
		$year = '0'.$year;
		if(strlen($x[$i])<2)
		$x[$i] = '0'.$x[$i];


		$q = "SELECT * FROM $STAT_TBL WHERE `date` like ('%/".$x[$i]."/".$year."')";

		$result =  mysql_query($q,$mres);
		$sum_=0;
		if(mysql_num_rows($result)){

			for($j=0;$j<mysql_num_rows($result);$j++){

				$row = mysql_fetch_object($result);
				$sum_ += get_totall_day($row->date,$mres);
			};
			$y[] = $sum_;
		}else
		$y[]=0;
	};

	return $y;

};


function get_totall_day($lrep,$mres){
	global $tm,$STAT_TBL;

	$q = "SELECT sum(`h_00`+`h_01`+`h_02`+`h_03`+`h_04`+`h_05`+`h_06`+`h_07`+`h_08`+`h_09`+`h_10`+`h_11`+`h_12`+`h_13`
+`h_14`+`h_15`+`h_16`+`h_17`+`h_18`+`h_19`+`h_20`+`h_21`+`h_22`+`h_23`) as sum
FROM $STAT_TBL where date='".$lrep."';";

	$result =  mysql_query($q,$mres);

	if(!mysql_num_rows($result)){
		return 0;
	};
	$row = mysql_fetch_object($result);
	return (!$row->sum ? 0 : $row->sum);
};


function get_totall($lrep,$m,$mres){
	global $tm,$STAT_TBL;

	$last_year=0;
	$last_month=0;
	$counted_days=0;
	$totall_days=0;

	if(strlen($m)<2)
	$m = '0'.$m;
	$q = "SELECT * FROM $STAT_TBL WHERE `date` like ('%/".$m.'/'.$tm['lyear']."')";
	//echo '<br>'.$q.' ';
	$result = mysql_query($q,$mres);
	$sum_ = 0;
	for($i=0;$i<mysql_num_rows($result);$i++){
		$row = mysql_fetch_array($result);
		if(!mysql_num_rows($result))
		echo '';
		else{
			for($j=0;$j<24;$j++){
				$c = $j;
				if(strlen($c)<2)
				$c = '0'.$c;
				$sum_ += intval($row['h_'.$c]);
			};
		};

	};
	$last_month=$sum_;



	$q = "SELECT * FROM $STAT_TBL WHERE `date` like ('%/".'%/'.$tm['lyear']."')";
	//echo '<br>'.$q.' ';
	$result = mysql_query($q,$mres);
	$sum_ = 0;
	for($i=0;$i<mysql_num_rows($result);$i++){
		$row = mysql_fetch_array($result);
		if(!mysql_num_rows($result))
		echo '';
		else{
			for($j=0;$j<24;$j++){
				$c = $j;
				if(strlen($c)<2)
				$c = '0'.$c;
				$sum_ += intval($row['h_'.$c]);
			};
		};

	};
	$last_year=$sum_;


	$q = "SELECT count(date) as cnt FROM $STAT_TBL WHERE `date` like ('%/".'%/'.$tm['lyear']."')";
	$result = mysql_query($q,$mres);
	$row = mysql_fetch_object($result);
	$counted_days = $row->cnt;

	$q = "SELECT count(date) as cnt FROM $STAT_TBL";
	$result = mysql_query($q,$mres);
	$row = mysql_fetch_object($result);
	$totall_days = $row->cnt;

	$tbl ="<table align=center bgcolor=#FFFFFF><tr>"
	.'<td><li>Today totall:'.get_totall_day($lrep,$mres).'</td></tr>'
	.'<tr><td>Month:'.$last_month.'</td></tr>'
	.'<tr><td>Last Year:'.$last_year.'</td></tr>'
	.'<tr><td>'.str_repeat('_',15).'</td></tr>'
	.'<tr><td><i>Counted days:'.$counted_days.'<br>Totall days:'.$totall_days.'</td></tr>'
	.'</table><br><br><br><br>';

	return $tbl;

};


function get_day_hours($x,$mres){
	global $tm,$STAT_TBL;


	// $x - calculating
	//     $current_hour = date("G",time());
	// for ($k = $current_hour - 23; $k <= $current_hour; $x[] = ($k < 0) ? ($k + 24) : $k, $k++);


	$q = "SELECT * FROM $STAT_TBL  WHERE date='".$tm['lrep_prev_day']."' limit 1;";
	$result = mysql_query($q,$mres);
	//some action
	$row = mysql_fetch_array($result);

	$h_days =array();

	if(!mysql_num_rows($result))
	$h_days = array_fill(0,24,0);
	else
	for($i=0;$i<24;$i++){
		$c = $i;
		if(strlen($c)<2)
		$c = '0'.$c;

		$h_days[] = $row['h_'.$c];

	};


	$q = "SELECT * FROM $STAT_TBL  WHERE date='".$tm['lrep']."' limit 1;";
	$result = mysql_query($q,$mres);

	$row = mysql_fetch_array($result);

	if(!mysql_num_rows($result)){
		//$h_days .= range(0,23);
		//$h_days = array_fill(22,48,0);
		$h_days = array_pad($h_days,48,0);
	}else
	for($i=0;$i<24;$i++){
		$c = $i;
		if(strlen($c)<2)
		$c = '0'.$c;

		$h_days[] = $row['h_'.$c];
	};


	$h_arr = array();
	for($i=0;$i<24;$i++){

		if($i==$x[0]){
			for($j=$i;$j<($i+24);$j++)
			$h_arr[]=$h_days[$j];

			break;
		};
	};

	//echo $x[1];
	//echo count($h_days);

	$h_days = $h_arr;

	//some action 2
	//$ret = '';
	// for($i=0;$i<count($h_days);$i++)
	// $ret .= $h_days[$i].' ';

	return $h_days;

};

function get_day_month($x,$mres){
	global $tm,$STAT_TBL;

	$days_res = array();
	$_new_nonth = 0;
	$m = $tm['lmonth'];

	($m==1 ? $m=12 : $m-=1);


	for($i=0;$i<count($x);$i++){



		if($x[$i]=='1'){
		($m==12 ? $m=1 : $m+=1);
		//$_new_nonth = 1;
		};
		//echo  $x[$i].' ';

		if(strlen($m)<2)
		$m ='0'.$m;

		$q = "SELECT * FROM $STAT_TBL WHERE `date`='".$x[$i].'/'.$m.'/'.$tm['lyear']."' limit 1";
		// echo '<br>'.$q.' ';
		$result = mysql_query($q,$mres);
		$row = mysql_fetch_array($result);

		$sum_ = 0;
		if(!mysql_num_rows($result))
		echo '';
		else{
			for($j=0;$j<24;$j++){
				$c = $j;
				if(strlen($c)<2)
				$c = '0'.$c;
				$sum_ += intval($row['h_'.$c]);
			};
		};

		$days_res[] = $sum_;

	};


	return $days_res;


};


function add_record($mres){
	global $tm,$STAT_TBL;

	$q = "UPDATE $STAT_TBL SET `h_".$tm['lhour']."`=`h_".$tm['lhour']."`+1 WHERE `date`='".$tm['lrep']."';";
	mysql_query($q,$mres);

	if(!mysql_affected_rows($mres)){

		$q = "INSERT INTO $STAT_TBL(`date`,`year`,`month`,`day`) values('".$tm['lrep']."','".$tm['lrep']."','".$tm['lmonth']."','".$tm['lday']."');";
		mysql_query($q,$mres);

		if(mysql_affected_rows($mres))
		add_record($mres);
	};

};




//optical correction of the graphical output
function bbc_graph_spacer($last, $nr, $values) {
	if ($nr == $last) $str = "none";
	else $str = ($values[$nr] > $values[($nr + 1)]) ? "solid" : "none";

	$str .= " none ";

	if ($nr === 0) $str .= "none";
	else $str .= ($values[$nr] >= $values[($nr - 1)]) ? "solid" : "none";

	// $str = 'none';
	return $str;
}







function bbc_plot($x, $y, $width, $height) {
	global $PLOT_STYLE;
	// $x = range('a','j');
	//  $y = range(1,20);

	//for($i=1;$i<count($y);$i++)
	// $y[$i] = rand(1,34);

	// Various sizes
	$nb_x = count($x);
	$nb_y = count($y);
	$nb = !empty($x) ? min($nb_x, $nb_y) : $nb_y;
	$bar_width = round($width / $nb);

	// Finding the maxima
	for ($k = 0, $max_y = 0; $k < $nb; $max_y = max($y[$k],$max_y), $k++);
	// The height of one unit
	@$unit_height = !empty($max_y) ? (0.92 * ($height / $max_y)) : 0;
	$str  = "<table class=\"cntbox\" border=\"0\" cellspacing=\"0\" cellpadding=\"0\" width=\"100%\">\n"
	."<tr style=\"background-color: ".$PLOT_STYLE['bg']."\">\n";


	for ($k = 0; $k < $nb; $k++) {
		$bar_height = round($y[$k] * $unit_height);

		//echo  $bar_height."<br>";

		$str .= "<td valign=\"bottom\" align=\"center\" width=\"$bar_width\" height=\"$height\">\n"
		."<table align=\"center\" border=\"0\"  cellspacing=\"0\" cellpadding=\"0\" width=\"100%\">\n"
		."<tr>\n";

		if ($y[$k]) {
			$numb = ($y[$k] >= 1000) ? substr(($tmp = $y[$k] / 1000) ,0 , (strpos($tmp, ".") + 2))."k" : $y[$k];

			$str .= "<td align=\"center\" valign=\"bottom\" class=\"sky\" height=\"".($height - $bar_height)."\" "
			."style=\"white-space: nowrap; border-style: none ".bbc_graph_spacer(($nb - 1), $k, $y)."\">"
			."<span class=\"graph\">$numb</span>"
			."</td>\n"
			."</tr>\n" //c0cbeb
			."<tr style=\"background-color:".$PLOT_STYLE['bar']."\">\n"#FF000F
			."<td title=\"".$y[$k]." \" height=\"$bar_height\" class=\"brd\" "
			."style=\"border-width: 1px; border-color: #00000;white-space: nowrap; border-style: solid  ".bbc_graph_spacer(($nb - 1), $k, $y)."\"></td>\n";
		}
		else $str .= "<td style=\"white-space: nowrap;\" height=\"$height\"></td>\n";

		$str .= "</tr>\n"
		."</table>\n"
		."</td>\n";
	}

	$str .= "</tr>\n"
	."<tr style=\"background-color: ".$PLOT_STYLE['x_bg']." \">\n";

	for ($k = 0; $k < $nb; $k++) {

		$str .= "<td valign=\"bottom\" align=\"center\" width=\"".$bar_width."\" height=\"15\">\n"
		."<table class=\"brd\" style=\"border-style: solid solid none none\" align=\"center\" border=\"0\" "
		."cellspacing=\"0\" cellpadding=\"0\" width=\"100%\">\n"
		."<tr>\n"
		."<td align=\"center\" height=\"15\" class=\"capt\">".$x[$k]."</td>\n"
		."</tr>\n"
		."</table>\n"
		."</td>\n";
	}

	$str .= "</tr>\n"
	."</table>\n";
	return $str;


}

function bbc_show_plot_time_type($time_type, $width, $height) {
	global $BBC_TIMESTAMP, $BBC_TIME_OFFSET, $access, $_,$mres,$tm;

	$last_time = isset($access['time']['last']) ? $access['time']['last'] : 0;
	$last_time = time();
	$current_time = $BBC_TIMESTAMP + ($BBC_TIME_OFFSET * 60);
	$current_time = time();

	$nb_seconds_in_day  = 86400;
	$nb_seconds_in_week = 7 * $nb_seconds_in_day;
	$last_month = date("n", $last_time) - 1;
	$nb_seconds_in_last_year = (date("L", $last_time) ? 366 : 365) * $nb_seconds_in_day;


	switch ($time_type) {
		case "hour":
			$current_hour = date("G", $current_time);
			$last_hour    = date("G", $last_time);


			for ($k = $current_hour - 23; $k <= $current_hour; $x[] = ($k < 0) ? ($k + 24) : $k, $k++);

			$y = get_day_hours($x,$mres);

			break;




		case "totall":

			// $x[]=$tm["lrep_prev_day"];
			//echo get_totall($tm["lrep_prev_day"],$mres);
			// $y[]=get_totall($tm["lrep_prev_day"],$tm['lmonth']-1,$mres);

			$x[]=$tm["lrep"].'&nbsp;<small>(Today)</small>';
			$y[]=get_totall($tm["lrep"],$tm['lmonth'],$mres);;

			break;



		case "wday":
			$day_name = array($_['tstat_Su'], $_['tstat_Mo'], $_['tstat_Tu'],
			$_['tstat_We'], $_['tstat_Th'], $_['tstat_Fr'],
			$_['tstat_Sa']);

			$current_wday = date("w", $current_time);
			$last_wday    = date("w", $last_time);

			for ($k = $current_wday - 6; $k <= $current_wday;
			$x[] = $day_name[($k < 0) ? $k + 7 : $k], $k++);
			for ($k = 0; $k < 7; $y[$k] = 0, $k++);
			if (($current_time - $last_time) <= $nb_seconds_in_week) {
				$elapsed = $current_wday - $last_wday;
				$elapsed = ($elapsed < 0) ? $elapsed + 7 : $elapsed;

				for ($k = $elapsed; $k < 7; $k++) {
					$y[$k - $elapsed] = $access['time']['wday'][($last_wday + 1 + $k) % 7];
				}
			}
			break;


		case "day":
			$current_day    = date("j", $current_time) - 1;
			$last_day       = date("j", $last_time) - 1;
			$time_in_prec_month = $current_time - ($current_day + 1) * $nb_seconds_in_day;
			$lg_prec_month  = date("t", $time_in_prec_month);
			$lg_prec_month  = ($current_day >= $lg_prec_month) ? ($current_day + 1) : $lg_prec_month;
			$current_month  = date("n", $current_time);
			$prec_month     = date("n", $time_in_prec_month);

			// Computing the $x
			for ($k = $current_day + 1; $k < $lg_prec_month; $x[] = ($k + 1), $k++);
			for ($k = 0; $k <= $current_day; $x[] = ($k + 1), $k++);
			$y = get_day_month($x,$mres);


			break;


		case "month":
			$month_name = array($_['tstat_Jan'], $_['tstat_Feb'], $_['tstat_Mar'], $_['tstat_Apr'], $_['tstat_May'],
			$_['tstat_Jun'], $_['tstat_Jul'], $_['tstat_Aug'], $_['tstat_Sep'], $_['tstat_Oct'],
			$_['tstat_Nov'], $_['tstat_Dec']);

			$current_month = date("n", $current_time) - 1;
			$last_month    = date("n", $last_time) - 1;

			$m_x = array();
			for ($k = $current_month - 11; $k <= $current_month; $k++){


				$x[] = $month_name[(($k < 0) ? ($k + 12) : $k)];

				$m_x[] = ((($k < 0) ? ($k + 12) : $k)==0 ? 12 :($k < 0) ? ($k + 12) : $k);
				//echo '<br>'.((($k < 0) ? ($k + 12) : $k)==0 ? 12 :($k < 0) ? ($k + 12) : $k);
			};

			$y = get_month($m_x,$mres);

			break;
	}

	return bbc_plot($x, $y, $width, $height);
}


// MAIN

echo "<table align=\"center\" border=\"0\" width=\"640\" class=\"cntbox\" cellpadding=\"15\" cellspacing=\"0\">\n"
."<tr>\n"
."<td class=\"head\" colspan=\"2\">Day&nbsp;(<small>hours</small>)<br /></td>\n"
."</tr>\n"
."<tr>\n"
."<td align=\"center\" colspan=\"2\">\n"
.bbc_show_plot_time_type("hour", 640, 200)
."</td>\n"
."</tr>\n"
."<tr>\n"
."<td class=\"head\">Totally</td>\n"
."<td class=\"head\">Last year&nbsp;(<small>For each month</small>)</td>\n"
."</tr>\n"
."<tr>\n"
."<td align=\"center\">\n" // <table border=0 width=203><tr><td>&nbsp;</td></tr></table><br><br>Totall:".get_totall_day($tm['lrep'],$mres)
.bbc_show_plot_time_type("totall", 203, 200)
."</td>\n"
."<td align=\"center\">\n"
.bbc_show_plot_time_type("month", 407, 200)
."</td>\n"
."</tr>\n"
."<tr>\n"
."<td class=\"head\" colspan=\"2\">Month&nbsp;(<small>Calculating for each day of month</small>)</td>\n"
."</tr>\n"
."<tr>\n"
."<td align=\"center\" colspan=\"2\">\n"
.bbc_show_plot_time_type("day", 640, 200)
."</td>\n"
."</tr>\n"
."</table>\n";

$ddd=microtime();
$ddd=((double)strstr($ddd, ' ')+(double)substr($ddd,0,strpos($ddd,' ')));
echo ("<br><center><p>(Time generating stats:".(number_format(($ddd-$ttt),2))." seconds)</p>Reset time statistics :<br> [<a href=gettime.php?clear=".urldecode($tm['lrep'])."&p=".$_GET['p'].">Current day</a>]&nbsp;[<a href=gettime.php?clear=all&p=".$_GET['p']." onclick=\"return erease()\";>All</a>]<center><br>");



?>