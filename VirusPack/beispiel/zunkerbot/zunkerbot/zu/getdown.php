<?

require('mycommon.php');
include_once('lang.php');
include_once('html.php');


error_reporting(0);

$mres = mysql_connect($BOT_DBHOST,$BOT_DBLOGIN,$BOT_DBPASS) or die('Check MySQl Options.'.mysql_error());
mysql_select_db($BOT_DBNAME);


if(isset($_GET['id'])){
	
echo $HTML_CLEAN_HEAD;
	
echo '<br><br><center>';

get_inf_md5($_GET['id']);	
echo '</center>';

exit;	
};


include_once('auth.php');
$STAT=2;
include_once('head.php');


$ttt=microtime();
$ttt=((double)strstr($ttt, ' ')+(double)substr($ttt,0,strpos($ttt,' ')));

if(isset($_GET['clear']))
 clear_country($_GET['clear'],$mres);


HTML_HEADER("Downloaded files&nbsp;");


echo draw_results(get_counry($mres),$mres);


//include_once('bottom.php');

//FUNCTIONS +++++++++++

function clear_country($land,$mres){
	
	$q = 'DELETE FROM `downfiles` WHERE `Dland`="'.strtoupper($land).'"';		
mysql_query($q,$mres);	
	
	return mysql_affected_rows($mres);		
};





function draw_results($countries,$mres){

	
$tbl = "<table class=cntbox border=\"0\" align=\"center\" cellpadding=\"1\" cellspacing=\"8\" >";	
$tr=3;
$td=0;

  for($i=0;$i<count($countries);$i++){
  	
  	//if($td==1)
   	//$tr = 1;
   	if($td == 3){
   	$tr=3;
   	$td=0;	   		
   	};
   	
   	if($tr==3) 
   	 $tbl .="<tr>";
   	   
   	      	      	  
   	 $tbl .="<td>".draw_counry($countries[$i],$mres)."</td>";
     $tr -=1;
   	 $td +=1;
  	   
   	if($tr==0) 
   	 $tbl .="</tr>";
  	  
  	
  	
  	
  	
  };
	
$tbl .="</table>";
  
return $tbl;
	
};






function draw_counry($land,$mres,$client=0){
global $LNG;

$lnk= $_SERVER["HTTP_HOST"].$_SERVER["SCRIPT_NAME"];
$inf = $lnk.'?id='.create_md5_link('1',$land);

$link='<a href="'.$inf.'">Client Link</a>';

$button = '<input type=button onClick="javascript:prompt(\'Copy Text below. It is link for client statistics for these country or file.\',\''.$inf.'\');" value="Get Link">';
//$button = $link;

$lllk = "<a href=getdown.php?id=".create_md5_link('1',$land).">Clint Link</a>";


	$q = "SELECT * FROM `downfiles` WHERE Dland = '".$land."';";
	$result = mysql_query($q,$mres);
	
 $tbl = "<table width=\"234\" border=\"0\" cellpadding=\"1\" cellspacing=\"1\"> "
." <tr class=\"file2\"> "
."<td colspan=\"5\" class=\"bhead\"><div align=\"center\">Downloaded Files&nbsp;(".$land.")&nbsp;&nbsp".($client ? '' : "<a href=\"getdown.php?clear=".$land."\">Clear</a>&nbsp;&nbsp;&nbsp;&nbsp;<a href=getdown.php?id=".create_md5_link('0',$land).">Clint Link</a>")."</div></td> "
." </tr> "
." <tr class=\"file2\"> "
." <td width=\"28\" bgcolor=#FCFCFC>Land</td> "
." <td width=\"81\" nowrap=\"nowrap\" bgcolor=#FCFCFC>File Name</td> "
." <td width=\"42\" bgcolor=#FCFCFC nowrap=\"nowrap\">Installed</td> "
." <td width=\"45\" bgcolor=#FCFCFC nowrap=\"nowrap\">File Size </td> "
." <td width=\"82\" bgcolor=#FCFCFC nowrap=\"nowrap\">Client-side stat.</td> "
." </tr>";

	$cnt =1;
 while ($row = mysql_fetch_object($result)){
 		
 $tbl .=" <tr class=\"file".$cnt."\"> "
." <td width=\"28\" class=\"file".$cnt."\"><img src=\"img/stat_img/ext_".strtolower($row->Dland).".png\" width=\"14\" height=\"14\" alt=\"".$row->Dland.' | '.@$LNG[strtolower($row->Dland)]."\"></td> "
." <td width=\"81\" class=\"file".$cnt."\">".$row->Dfname."</td> "
." <td width=\"62\" class=\"file".$cnt."\">&nbsp;<font color=black>".$row->Dcnt."</font></td> "
." <td width=\"45\" class=\"file".$cnt."\">".number_format($row->Dsize)."&nbsp</td> "
." <td width=\"62\" bgcolor=#FCFCFC nowrap=\"nowrap\">&nbsp;&nbsp;".($client ? '' : "<a href=getdown.php?id=".create_md5_link('1',$row->Dfname.$row->Dsize).">Clint Link</a>")."</td> "
." </tr>";	
 	

 if($cnt==2)
     $cnt=1;
     else 
     $cnt=2; 	
     
 };

 $tbl .="</table>";
 
 return $tbl;
	
};





function get_counry($mres){
	
	$q = "select `Dland` from (SELECT * FROM `downfiles` group by Dland ) as `dfiles`  order by Dtime DESC;";
	
$result	= mysql_query($q,$mres);
	if(!mysql_num_rows($result))
     return 0;		
	
     $ret = array();
     
     while ($row = mysql_fetch_object($result)){
     	
     	$ret[]=$row->Dland;
     	
     };
     
     return $ret;
};







function create_md5_link($index,$name){

$ret =  $index.substr(md5($name.date('m',time())),0,15);
	
return $ret;

};




function get_inf_md5($indexmd5){
global $mres;
	
$index = substr($indexmd5,0,1);

switch ($index){
	case 0: {
	$type = 'land';
	$land = get_land_bymd5(substr($indexmd5,1,15));	
	echo draw_counry($land,$mres,1);
	break;
	}
	case 1: {
		$type = 'file';	
	
	 echo gen_file_tbl(get_file_bymd5(substr($indexmd5,1,15)));
	};
};



};





function get_file_bymd5($md5){
global $mres;

$q = "SELECT * FROM `downfiles`";

$res = mysql_query($q,$mres);
if(!mysql_num_rows($res))
return '';
  
$larr=array();

while (($row = mysql_fetch_object($res))) {
	$larr[$row->Did]= array(
	'Dfname'=>$row->Dfname,
	'Dsize'=>$row->Dsize,
	'Dcnt'=>$row->Dcnt,
	'Did'=>$row->Did	
	);
}



foreach ($larr as $l=>$arr){
	
//echo substr(md5($arr['Dfname'].$arr['Dsize']),0,15).' 888 '.$md5;
	if(substr(md5($arr['Dfname'].$arr['Dsize'].date('m',time())),0,15) == $md5){	  
     //  echo $arr['Dfname'].'  -:'.$arr['Dsize'].' ='.$arr['Dcnt'].'f';
		return $arr;	
	}
	 
		
};

return '';
	
};






function get_land_bymd5($md5){
global $mres;

$q = "SELECT * FROM `downfiles`";

$res = mysql_query($q,$mres);
if(!mysql_num_rows($res))
return '';
  
$larr=array();

while (($row = mysql_fetch_object($res))) {
	$larr[]=$row->Dland;
}

$larr = array_unique($larr);

foreach ($larr as $l){

	if(substr(md5($l.date('m',time())),0,15) == $md5)
	 return $l;
		
};

return '';
	
};




function gen_file_tbl($arr){
	
	if(!count($arr))
	return '';
	
//print_r($arr);
	
 $tbl = "<table width=\"234\" border=\"0\" cellpadding=\"1\" cellspacing=\"1\"> "
." <tr class=\"file2\"> "
."<td colspan=\"3\" class=\"bhead\"><div align=\"center\">Downloaded File</div></td> "
." </tr> "
." <tr class=\"file2\"> "
." <td width=\"81\" nowrap=\"nowrap\" bgcolor=#FCFCFC>File Name</td> "
." <td width=\"42\" bgcolor=#FCFCFC nowrap=\"nowrap\">Installed</td> "
." <td width=\"45\" bgcolor=#FCFCFC nowrap=\"nowrap\">File Size </td> "
." </tr>";

$cnt=1;
		
 $tbl .=" <tr class=\"file".$cnt."\"> "
." <td width=\"81\" class=\"file".$cnt."\">".$arr['Dfname']."</td> "
." <td width=\"62\" class=\"file".$cnt."\">&nbsp;<font color=black>".$arr['Dcnt']."</font></td> "
." <td width=\"45\" class=\"file".$cnt."\">".number_format($arr['Dsize'])."&nbsp</td> "
." </tr>";	
	
	 $tbl .="</table>";
	 
return $tbl;
};



?>