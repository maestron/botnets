<html><title>ZUNKER</title>
<body leftmargin="0" rightmargin="0" topmargin="0">
<META HTTP-EQUIV="Cashe-control" content="no-cashe"> 
<META http-equiv=Content-Type content="text/html; charset=windows-1251">
<link rel="shortcut icon" href="img/favicon.ico">  
<LINK href="img/style.css" type=text/css rel=stylesheet>


<table width="100%" border="0" align="center" cellpadding="0" cellspacing="0" class="navActive">
  <tr>
     <td width="16">&nbsp;</td>
    <td width="71"><? echo set_scob((isset($STAT) ? $STAT : 0)); ?><a href="getglobal.php">statistics</a><? echo set_scob((isset($STAT) ? $STAT : 0)); ?></td>
    <td width="70" nowrap=\"nowrap\"><? echo set_scob((isset($CTRL) ? 1 : 0)); ?><a href="task_zu.php">control</a><? echo set_scob((isset($CTRL) ? 1 : 0)); ?></td>
    <td width="70%">[<a href="../readme.txt">help</a>]</td>
	 <td width="145" nowrap="nowrap"><font size="1">ZUnker Panel v<? echo $UNKER_VERSION; ?></font> </td>
    <td width="90" nowrap="nowrap">[<a href="auth.php?logout">LOG OUT</a>]</td>
    <td width="37">&nbsp;</td>
  </tr>
  <tr>
  <td colspan="7" bgcolor="#F9F9F9"height="4">
  </td>
  </tr>
  <?

  //echo(isset($STAT)? '<font color="#FF000F">[</font>' : '[' );

  $HTML_CONTROL = " <tr> "
  ." <td width=\"16\" bgcolor=\"#FCFCFC\">&nbsp;</td> "
  ." <td width=\"71\" bgcolor=\"#FCFCFC\">&nbsp;</td> "
  ." <td height=\"4\" bgcolor=\"#FCFCFC\" nowrap=\"nowrap\"><font size=1>".@set_scob(($CTRL==1?1:0))."<a href=\"task.php\">Loader</a>".@set_scob(($CTRL==1?1:0))."</font></td> "
  ." <td height=\"4\" colspan=\"4\" bgcolor=\"#FCFCFC\"><font size=1>".@set_scob(($CTRL==2?1:0))."<a href=\"task_zu.php\">Zupacha</a>".@set_scob(($CTRL==2?1:0))."</font></td> "
  ." </tr>";

  $HTML_CONTROL_ZU = " <tr> "
  ." <td width=\"16\" bgcolor=\"#FCFCFC\">&nbsp;</td> "
  ." <td width=\"71\" bgcolor=\"#FCFCFC\">&nbsp;</td> "
  ." <td height=\"4\" bgcolor=\"#FCFCFC\" nowrap=\"nowrap\"><font size=1>".@set_scob(($CTRL==1?1:0))."<a href=\"task.php\">Loader</a>".@set_scob(($CTRL==1?1:0))."</font></td> "
  ." <td height=\"4\" colspan=\"4\" bgcolor=\"#FCFCFC\"><font size=1>"."<a href=\"task_zu.php\">Zupacha</a>"."</font></td> "
  ." </tr>"
  ." <tr> "
  ." <td width=\"16\" bgcolor=\"#FFFFFF\">&nbsp;</td> "
  ." <td width=\"71\" bgcolor=\"#FFFFFF\"><font size=1></font></td> "
  ." <td height=\"4\" bgcolor=\"#FFFFFF\" nowrap=\"nowrap\"><font size=1></font></td> "
  ." <td height=\"4\" colspan=\"4\" bgcolor=\"#FFFFFF\"><font size=1>".@set_scob(($CTRL_ZU==1 ? 1 : 0))."<a href=\"task_zu.php\">Control</a>".@set_scob(($CTRL_ZU==1 ? 1 : 0))."&nbsp;".@set_scob(($CTRL_ZU==2 ? 1 : 0))."<a href=\"tpledit_zu.php\">Template Editor</a>".@set_scob(($CTRL_ZU==2 ? 1 : 0))."</font></td> "
  ." </tr>";



  $HTML_H_SATAT  = " <tr> "
  ." <td width=\"16\" bgcolor=\"#FFFFFF\">&nbsp;</td> "
  ." <td width=\"71\" bgcolor=\"#FFFFFF\"><font size=1>".@set_scob(($STAT===1?1:0))."<a href=\"getglobal.php\">Global</a>".@set_scob(($STAT===1?1:0))."</font></td> "
  ." <td height=\"4\" bgcolor=\"#FFFFFF\" nowrap=\"nowrap\"><font size=1>".@set_scob(($STAT==2?1:0))."<a href=\"getdown.php\">Downloaded files</a>".@set_scob(($STAT==2?1:0))."</font></td> "
  ." <td height=\"4\" colspan=\"4\" bgcolor=\"#FFFFFF\"><font size=1>".(isset($STAT_TIME) ? "" :"[")."<a href=\"gettime.php\">Time statistics</a>".(isset($STAT_TIME) ? "" :"]")."</font></td> "
  ." </tr>";

  $HTML_H_STAT_TIME =
  " <tr> "
  ." <td width=\"16\" bgcolor=\"#FFFFFF\">&nbsp;</td> "
  ." <td width=\"71\" bgcolor=\"#FFFFFF\"><font size=1></font></td> "
  ." <td height=\"4\" bgcolor=\"#FFFFFF\" nowrap=\"nowrap\"><font size=1></font></td> "
  ." <td height=\"4\" colspan=\"4\" bgcolor=\"#FFFFFF\"><font size=1>".
  @set_scob(($_GET['p']=='down' ? 1 : 0))."<a href=\"gettime.php?p=down\">Downloaded files</a>".@set_scob(($_GET['p']=='down' ? 1 : 0))."&nbsp;"
  .@set_scob(($_GET['p']=='rap' ? 1 : 0))."<a href=\"gettime.php?p=rap\">Bot`s raports</a>".@set_scob(($_GET['p']=='rap' ? 1 : 0))."&nbsp;"
  .@set_scob(($_GET['p']=='sent' ? 1 : 0))."<a href=\"gettime.php?p=sent\">Messages sent</a>".@set_scob(($_GET['p']=='sent' ? 1 : 0))."</font></td> "
  ." </tr>";


  //echo (isset($CTRL) ? $HTML_CONTROL : '');
  echo (isset($STAT) ? $HTML_H_SATAT : '' );
  echo (isset($STAT_TIME) ? $HTML_H_STAT_TIME : '' );
  echo (isset($CTRL) ? ($CTRL == 2 ? $HTML_CONTROL_ZU : $HTML_CONTROL ) : '');



  function set_scob($var,$c="#FF000F"){
  	global $cnt;

  	($cnt==1?$cnt=0:$cnt=1);

  	if($var){
  		$ret = ($cnt==1 ? '<font color="'.$c.'">[</font>':'<font color="'.$c.'">]</font>');
  	}else
  	$ret = ($cnt==1 ? '[':']');


  	return  $ret;
  };

  	?>

</table>
<br>