<?php


if(array_key_exists('getland',$_GET)){

//Creating AJAX-friendly tech.	
	
	require_once "lib/JsHttpRequest/JsHttpRequest.php";
	$JsHttpRequest =& new JsHttpRequest("windows-1251");
	
	$L_NAVI = "Select Country: <a href=\"javascript:doLoad('".land_mini_navigate($_GET['getland'],'next')."');\" title=\"Next land:".land_mini_navigate($_GET['getland'],'next')."\">Next</a>"
	."&nbsp;&nbsp;<a href=\"javascript:doLoad('".land_mini_navigate($_GET['getland'],'prev')."');\" title=\"".land_mini_navigate($_GET['getland'],'prev')." &#8212 Previous land.\">Prev.</a>";

	$_RESULT = array(
	"LAND_STAT"     => gen_land_perc($_GET['getland']),
	"LAND_NAVIG"   => $L_NAVI
	);

	exit;

};




function countrys_soft_ttl($type){
global $_SESSION;
	



 $CL_ARR = array();
 
 foreach ( $_SESSION['TOP_LAND_LIST'] as $LND){
 	
 	$CL_ARR[$LND] = get_country_soft_ttl_cnt($type,$LND);
 	
 };

  $cnt_soft_name = count(get_softname($type));
    
  arsort($CL_ARR,SORT_NUMERIC);
  
  if($cnt_soft_name){
     $CL_ARR = array_chunk($CL_ARR,$cnt_soft_name,true);
   $CL_ARR = $CL_ARR[0];
  };
  
 return $CL_ARR;
	
};









function get_country_soft_ttl_cnt($type,$land){
global $mres,$SOFT_TBL;


 $S_ARR = get_softname($type);
 
 
	$str_q='sum(';
	foreach ($S_ARR as $NAME)
	$str_q .= '`'.$NAME.'`+';

	if(substr($str_q,-1)=='+')
	$str_q = substr($str_q,0,-1);
    $str_q .=')';
	 
	$q =  'SELECT '.$str_q.' as cnt FROM `'.$SOFT_TBL.'` WHERE `LAND`="'.$land.'";';
 
	$result = @mysql_query($q,$mres);
	 
 if(!@mysql_num_rows($result))
 return 0;
 
 $row = mysql_fetch_object($result);
 return ($row->cnt!=''? $row->cnt :0);	
 
};





function land_mini_navigate($curr_land,$way='next'){
	global $_SESSION;

	if(!isset($_SESSION['TOP_LAND_LIST']))
	return 'UNK';

	$LL = $_SESSION['TOP_LAND_LIST'];

	for($i=0;$i<count($LL);$i++){


		if(strtoupper($LL[$i])==strtoupper($curr_land)){
			if($i<=1)
			$PREV_L = $LL[count($LL)-1];
			else
			$PREV_L = $LL[$i-1];

			if($i==(count($LL)-1))
			$NEXT_L = $LL[0];
			else
			$NEXT_L = $LL[$i+1];

		};
	};

  switch ($way){
  	case 'prev':
  		 return $NEXT_L; 
  	case 'next':
  		 return $PREV_L;
  };

 return '';


};




function top_software_allcount($type=''){
	global $mres,$SOFT_TBL;

	$S_ARR = get_softname($type);

	//makes coun of all values of $type into variable $CNT;
	$str_q='';
	foreach ($S_ARR as $NAME)
	$str_q .= 'sum(`'.$NAME.'`)+';

	if(substr($str_q,-1)=='+')
	$str_q = substr($str_q,0,-1);

	$q =  'SELECT '.$str_q.' as cnt FROM `'.$SOFT_TBL.'`;';

	$result = mysql_query($q,$mres);
	if(!@mysql_num_rows($result))
	return 0;

	$row = mysql_fetch_object($result);
	return $row->cnt;

};






//-----------------------------------------
function top_software($type,$prefix=0,$totalcount=1){
	global $mres,$SOFT_TBL;

	$S_ARR = get_softname($type);

	if(!count($S_ARR))
	return $S_ARR;


	$SN_ARR =array();

	foreach ($S_ARR as $NAME){

		$q = 'SELECT sum(`'.$NAME.'`) as cnt FROM `'.$SOFT_TBL.'`;';
		$result = mysql_query($q,$mres);

		$row = mysql_fetch_object($result);

		if($prefix)
		$arr_key = $NAME;
		else
		$arr_key = substr($NAME,strpos($NAME,'_')+1);

		$SN_ARR[$arr_key] = $row->cnt; //.'-'.@round(($row->cnt/$CNT)*100);
	};

	mysql_free_result($result);
	arsort($SN_ARR,SORT_NUMERIC);
	return  $SN_ARR;


};






//-----------------------------------------
function get_softname($type='all',$prefix=1){
	global $mres,$SOFT_TBL;

	//strlen(trim($type))=='' ? $type='all' : '' ;

	$q = "SELECT * FROM `".$SOFT_TBL."` LIMIT 1";
	$result = mysql_query($q,$mres);
	$S_ARR = array();

	while(@$f = mysql_fetch_field($result))
	if($f->name!='LAND')
	$S_ARR[] = $f->name;

	@mysql_free_result($result);

	if($type=='all')
	return $S_ARR;

	$RE_ARR = array();


	foreach ($S_ARR as $SFT){
		if(strpos($SFT,'_')){
			if(substr($SFT,0,strlen($type))==$type)
			if($prefix)
			$RE_ARR[]=$SFT;
			else
			$RE_ARR[]=substr($SFT,strpos($SFT,'_')+1);

		};

	};
	//print_r($S_ARR);

	return $RE_ARR;

};







function get_full_name($NAME,$type){
	include('softlist.php');

	if($type==''){
		$type = substr($NAME,0,1);
		$NAME = substr($NAME,2);
	};

	@eval("\$ARR = $".strtoupper($type)."_SOFT;");


	foreach (@$ARR as $k=>$v){
		if($k==$NAME)
		return $v;
	};
	return $NAME;

};





function sort_by_top_software($ARR,$type=''){
	$TS_ARR = top_software($type,1);

	$N_ARR = array();

	foreach ($TS_ARR as $key=>$val){
		$N_ARR[$key]=$ARR[$key];
	};

	return $N_ARR;

};






function get_soft_by_county($LAND,$type=''){
	global $mres,$SOFT_TBL;

	$S_ARR = get_softname($type);

	$str_q='';
	foreach ($S_ARR as $NAME)
	$str_q .= ' `'.$NAME.'`,';

	if(substr($str_q,-1)==',')
	$str_q = substr($str_q,0,-1);

	$q =  'SELECT '.$str_q.' FROM `'.$SOFT_TBL.'` WHERE `LAND`="'.$LAND.'";';

	$R_ARR = array();


	$result = mysql_query($q,$mres);
	if(!mysql_num_rows($result)){
		foreach ($S_ARR as $N)
		$R_ARR[$N]=0;
		return $R_ARR;
	};

	$row =mysql_fetch_assoc($result);
	foreach ($S_ARR as $N){
		if(trim($row[$N])=='')
		$row[$N]=0;
		$R_ARR[$N]=$row[$N];
	};

	mysql_free_result($result);
	return $R_ARR;


};









function prepare_countrys_ttl_tbl($LAND_ARR,$bgcolor='F2F2F2'){
	
	include('lang.php');
	
		$CNT =0;
   if(count($LAND_ARR))
		foreach ($LAND_ARR as $key=>$val){
		$CNT += $val;
	};

	$ret = '';
	


   if(count($LAND_ARR) && $CNT)
	foreach (@$LAND_ARR as $key=>$val){
			$perc = round(($val/$CNT)*100);
			
			$id = rand(123,3321);
	if($perc == 0)
	$bgcolor = 'FFFFFF';
	elseif ($perc > 0 && $perc < 50)
	 $bgcolor = 'FCFCFC';
	 elseif ($perc > 50 && $perc < 60)
	 $bgcolor = 'EFEFEF';
	elseif ($perc > 60 && $perc < 80)
	$bgcolor = 'DFDFDF';
	elseif ($perc >80)
	$bgcolor = 'F2F2F2';
	
		$ret .= " <tr bgcolor=\"#".$bgcolor."\"> "."\n"
		." <td width=\"4%\"><img src=\"img/stat_img/ext_".strtolower($key).".png\" id=\"sid".$id."\" with=14 height=14 border=0 style='filter:alpha(opacity=9);-moz-opacity:0.09' onMouseover='makevisible(this,0)' onMouseout='makevisible(this,1)'></td> "."\n"
		." <td width=\"42%\" nowrap=\"nowrap\"><a href=\"javascript:doLoad('".strtoupper($key)."');\" style='text-decoration: none; color: #606680' onMouseover='makevisible(sid".$id.",0)' onMouseout='makevisible(sid".$id.",1)' >".$LNG[strtolower($key)]."</a></td> "."\n"
		." <td width=\"27%\">".$val."</td> "."\n"
		." <td width=\"21%\">".$perc."%</td> "."\n"
		." </tr>";
	};

	return $ret;
	
	
	
};




function prepare_tblland_perc($SOFT){

	$CNT =0;
	foreach ($SOFT as $key=>$val){
		$CNT += $val;
	};

	$ret = '';

	foreach ($SOFT as $key=>$val) {

		$hint = '<a title="\''.get_full_name($key,'')."'  ".'Installed:'.$val.'">';
		$b_hint='</a>';

		$perc = @round(($val/$CNT)*100);

		if($perc<=0){
			$hint = '';
			$b_hint = '';
		};
		//$perc = 72;

		if($perc>68){
			$td1perc = '<div align="right">'.$hint.$perc.$b_hint.'<font size=-3>%</font>&nbsp;</div>';
			$td2perc= '';
		}else if($perc<=68){
			$td1perc= '';
			$td2perc = '&nbsp;'.$hint.$perc.$b_hint.'<font size=-3>%</font>';
		};
		
		$ret .= "<tr> "."\n"
		//."<td width=\"17%\" bgcolor=\"#F2F2F2\"><img src=\"img/stat_img/".$key.".jpg\" width=\"14\" height=\"14\" style='filter:alpha(opacity=20);-moz-opacity:0.2'>"

		."<td colspan=\"2\" nowrap=\"nowrap\"> "."\n"

		."<table width=\"100%\" height=\"8\" cellpadding=\"0\" cellspacing=\"0\" class=\"percbar1\"> "."\n"
		."<tr><td bgcolor=\"#FCEFA7\" width=\"".$perc."%\" >".$td1perc."</td><td width=\"".(100-$perc)."%\">".$td2perc."</td></tr> "."\n"
		."</table> "."\n"
		."</td> "."\n"
		."<td width=\"10%\" bgcolor=\"#F2F2F2\">".$val
		// ."<table width=\"100%\" height=\"8\" cellpadding=\"0\" cellspacing=\"0\" class=\"percbar1\"  background=\"img/stat_img/".$key.".jpg\" style='filter:alpha(opacity=20);-moz-opacity:0.2'><tr><td>123</td></tr></table>"
		."</td>"
		."</tr>";

	};

	return $ret;
};







//-----------------------------------------
function prepare_tbl_soft($SOFT,$type='a',$bgcolor='F2F2F2'){

	$CNT =0;
	foreach ($SOFT as $key=>$val){
		$CNT += $val;
	};

	$ret = '';

	foreach ($SOFT as $key=>$val){
		$ret .= " <tr bgcolor=\"#".$bgcolor."\"> "."\n"
		." <td width=\"4%\"><img src=\"img/stat_img/".$type."_".$key.".jpg\" with=14 height=14 border=0 ></td> "."\n"
		." <td width=\"42%\">".get_full_name($key,$type)."</td> "."\n"
		." <td width=\"27%\">".$val."</td> "."\n"
		." <td width=\"21%\">".@round(($val/$CNT)*100)."%</td> "."\n"
		." </tr>";
	};

	return $ret;

};


function  land_pec_navi(){
	global  $STAT_DEF_LAND_SS,$_SESSION;
	
	$ret = '';
	$ret .= "<td width=\"144\" bgcolor=\"F2F2F2\" nowrap=\"nowrap\"><div id=\"LAND_NAVIG\">Select Country: <a href=\"javascript:doLoad('".($STAT_DEF_LAND_SS=='COUNTRIES' ? reset($_SESSION['TOP_LAND_LIST']) : $STAT_DEF_LAND_SS)."');\">Go to Detailed</a></div> </td>";
	return $ret;
};








function gen_countrys_ratings(){
	
	
		$ret="<div id=\"resultland\"><table width=\"100%\" border=\"1\" cellpadding=\"0\" cellspacing=\"2\"   bordercolor=\"#FFFFFF\"   > "."\n"
	." <tr> "."\n"
	." <td></td> "."\n"
	." <td width=\"42%\"><strong>Country</strong></td> "."\n"
	." <td colspan=\"2\"><div align=\"right\"><strong>Rating</strong></div></td> "."\n"
	.'</tr><tr>'
	." <td colspan=\"4\"><div align=\"center\" class=\"chck\">Anti Virus <!--&nbsp;&#8212;&nbsp;<font size=-5 color=#000000>".count(get_softname('a'))."</font>--></div></td> "."\n"
	." </tr>  "."\n";
	// $ret .=" <td colspan=\"4\"><div align=\"center\" class=\"chck\">Antivirus &nbsp;&#8212;&nbsp;<font size=-5 color=#000000>".count(get_softname('a'))."</font></div></td> "."\n"
	//." </tr> "."\n";
	$ret .= prepare_countrys_ttl_tbl(countrys_soft_ttl('a'));;


	if(count(get_softname('s')))
	$ret .=" <td colspan=\"4\"><div align=\"center\" class=\"chck\">Anti SpyWare <!-- &nbsp;&#8212;&nbsp;<font size=-5 color=#000000>".count(get_softname('s'))."</font>--></div></td> "."\n"
	." </tr> "."\n";
	$ret .= prepare_countrys_ttl_tbl(countrys_soft_ttl('s'));;


	$ret .=" <tr> "."\n"
	." <td></td> "."\n"
	." <td colspan=\"3\">&nbsp;<!--Soft names Totally: <strong>".count(get_softname())."</strong>--></td> "."\n"
	." </tr> "."\n"
	." <td></td> "."\n"
	." <td colspan=\"3\">&nbsp;<!--Software installed: <strong>".top_software_allcount()."</strong>--></td> "."\n"
	." </tr> "."\n"
	." </table></div>"."\n";


	return $ret;
	
	
	
	
};



function gen_land_perc($LAND){

	include('lang.php');

	$ret = " <div id=\"resultland\"><table width=\"90%\" border=\"0\" align=\"center\" cellpadding=\"0\" bordercolor=\"#CCCCCC\" bgcolor=\"#FFFFFF\" > "."\n"
	." <tr > "."\n"
	." <td></td> "."\n"
	." <td width=\"42%\" nowrap=\"nowrap\" colspan=\"1\"><strong>Country </strong>".str_repeat('&nbsp;',5)."<strong>Count</strong></td> "."\n"
	//." <td colspan=\"1\"><div align=\"right\"><strong>Rating</strong></div</td> "."\n"

	." </tr>  "."\n"
	." <tr class=\"percbar1\"> "."\n"
	." <td width=\"12\" bgcolor=\"#F2F2F2\" class=\"percbar1\"><img src=\"img/stat_img/ext_".strtolower($LAND).".png\" with=13 height=14 border=0 ></td> "."\n"
	//." </tr> "."\n"
	." <td colspan=\"2\"><div align=\"center\" class=\"chck\"><a title=\"".$LNG[strtolower($LAND)]."\">".$LAND."</a>&nbsp;&#8212&nbsp;Anti Virus</div></td> "."\n"
	//." <td width=\"88%\" bgcolor=\"#F2F2F2\" nowrap=\"nowrap\">&nbsp;<a title=\"s\">".$LNG[strtolower($LAND)]."</a</td> "."\n"
	// ."<td width=\"17%\" bgcolor=\"#F2F2F2\">s</td>"
	." </tr>";

	$ret .= prepare_tblland_perc(sort_by_top_software(get_soft_by_county($LAND,'a'),'a'));


	if(count(get_softname('s')))
	$ret .=" <td width=\"12\" bgcolor=\"#F2F2F2\" class=\"percbar1\"><img src=\"img/stat_img/ext_".strtolower($LAND).".png\" with=13 height=14 border=0></td> "."\n"
	." <td colspan=\"2\"><div align=\"center\" class=\"chck\"><!--a title=\"".$LNG[strtolower($LAND)]."\">".$LAND."</a>&nbsp;&#8212&nbsp;-->Anti SpyWare</div></td> "."\n"
	." </tr> "."\n";

	$ret .= prepare_tblland_perc(sort_by_top_software(get_soft_by_county($LAND,'s'),'s'));


	$ret .= "<tr> "."\n"
	." <td colspan=\"3\" nowrap=\"nowrap\">Antivirus installed: <strong>".get_country_soft_ttl_cnt('a',$LAND)."</strong></td> "."\n"
	." </tr>"
	."<tr> "."\n"
	." <td colspan=\"3\" nowrap=\"nowrap\">Spyware installed: <strong>".get_country_soft_ttl_cnt('s',$LAND)."</strong></td> "."\n"
	." </tr>";

	$ret .='</table></div>';
	return $ret;
};









function gen_glob_soft_tbl(){



	$ret="<table width=\"100%\" border=\"1\" cellpadding=\"0\"  bordercolor=\"#FFFFFF\" > "."\n"
	." <tr> "."\n"
	." <td></td> "."\n"
	." <td width=\"42%\"><strong>Software</strong></td> "."\n"
	." <td colspan=\"2\"><div align=\"right\"><strong>Rating</strong></div</td> "."\n"
	.'</tr><tr>'
	." <td colspan=\"4\"><div align=\"center\" class=\"chck\">Anti Virus &nbsp;&#8212;&nbsp;<font size=-5 color=#000000>".count(get_softname('a'))."</font></div></td> "."\n"
	." </tr>  "."\n";
	// $ret .=" <td colspan=\"4\"><div align=\"center\" class=\"chck\">Antivirus &nbsp;&#8212;&nbsp;<font size=-5 color=#000000>".count(get_softname('a'))."</font></div></td> "."\n"
	//." </tr> "."\n";
	$ret .= prepare_tbl_soft(top_software('a'));


	if(count(get_softname('s')))
	$ret .=" <td colspan=\"4\"><div align=\"center\" class=\"chck\">Anti SpyWare &nbsp;&#8212;&nbsp;<font size=-5 color=#000000>".count(get_softname('s'))."</font></div></td> "."\n"
	." </tr> "."\n";
	$ret .= prepare_tbl_soft(top_software('s'),'s');


	$ret .=" <tr> "."\n"
	." <td></td> "."\n"
	." <td colspan=\"3\">Soft names Totally: <strong>".count(get_softname())."</strong></td> "."\n"
	." </tr> "."\n"
	." <td></td> "."\n"
	." <td colspan=\"3\">Software installed: <strong>".top_software_allcount()."</strong></td> "."\n"
	." </tr> "."\n"
	." </table>"."\n";


	return $ret;
};


?>