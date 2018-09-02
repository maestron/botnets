<?php if(!defined('__INDEX__'))die();
$pedt=PRIV&PRIV_USERS_EDIT;
if(isset($_GET['del'])&&$pedt&&is_numeric($_GET['del']))
{
  if($_GET['del']!=$_SESSION['id'])mysql_query('DELETE FROM  '.TABLE_USERS.' WHERE id='.$_GET['del'].' LIMIT 1');
  header('Location: '.QUERY_STRING);
  die();  
}
else if(((isset($_GET['new'])&&$pedt)||(isset($_GET['edit'])&&is_numeric($_GET['edit']))))
{
  $new=isset($_GET['new']);
  $cont=0;
  $login='';
  $pass='';
  $priv=0;
  
  if(isset($_POST['login']))
  {
    $login=trim($_POST['login']);
    $pass=trim(@$_POST['pass']);
    $kg=array_keys($_POST);
    $cg=count($kg);
    $priv=0;
    for($i=0;$i<$cg;$i++)if(substr($kg[$i],0,5)=='priv_'&&is_numeric(($pr=substr($kg[$i],5))))$priv|=$pr;

    if(strlen($login)<4||strlen($login)>10)SetError(3);
    else if((strlen($pass)<6||strlen($pass)>64) && ($new || (!$new && strlen($pass)!=0)))SetError(2);
    else
    {
      $data='login=\''.addslashes($login).'\', priv=\''.$priv.'\'';
      if(strlen($pass))$data .= ', pass=\''.md5($pass).'\'';
      $r=mysql_query('SELECT id FROM '.TABLE_USERS.' WHERE login=\''.addslashes($login).'\' LIMIT 1');
      if($r&&mysql_affected_rows()==1&&($m=mysql_fetch_row($r)))
      {
        if($new||$m[0]!=$_GET['edit'])SetError(1);
        else {mysql_query('UPDATE '.TABLE_USERS.' SET '.$data.' WHERE id=\''.$_GET['edit'].'\' LIMIT 1');$cont=1;}
      }
      else
      {
        if($new)mysql_query('INSERT INTO '.TABLE_USERS.' SET '.$data);
        else mysql_query('UPDATE '.TABLE_USERS.' SET '.$data.' WHERE id=\''.$_GET['edit'].'\' LIMIT 1');
        $cont=1;
      }
    }
  }
  else if(!$new&&($r=mysql_query('SELECT login,pass,priv FROM '.TABLE_USERS.' WHERE id='.$_GET['edit'].' LIMIT 1'))&&($m=mysql_fetch_row($r)))
  {
    $login=$m[0];
    $pass='';
    $priv=$m[2];
  }
  
  if($cont>0)header('Location: '.QUERY_STRING);
  else
  {
    HTMLBegin(LNG_MUSERS_F);
    ShowError('LNG_MUSERS_ERROR_');
    
    $en=($pedt&&($new||$_GET['edit']!=$_SESSION['id']));
  
    if($en)print '<form method="POST" action="'.QUERY_STRING.'&'.($new?'new':'edit='.$_GET['edit']).'">';
    print '<table class="tbl1" width="300"><tr><td class="td1" colspan="2">'.($new?LNG_MUSERS_F_ADD:($pedt&&$_GET['edit']!=$_SESSION['id']?LNG_MUSERS_F_EDIT:LNG_MUSERS_F_VIEW)).'</td></tr>'.
          '<tr><td>'.LNG_MUSERS_F_LOGIN.'</td><td width="100%"><input type="text" '.($en?'':'readonly ').'name="login" value="'.htmlentities($login).'" style="width:100%"></td></tr>'.
          '<tr><td>'.LNG_MUSERS_F_PASS.'</td><td width="100%"><input type="text" '.($en?'':'readonly ').'name="pass" value="'.htmlentities($pass).'" style="width:100%"></td></tr>'.
          '<tr><td colspan="2"><table class="tbl1" width="100%"><tr><td class="td1">'.LNG_MUSERS_F_PRIV.'</td></tr>';
  
    Priv(0,                 0,LNG_MUSERS_F_PRIV_STATS,           PRIV_STATS,           $priv,$en);
    Priv(MODULE_LOGS,       1,LNG_MUSERS_F_PRIV_STATS_LOGS,      PRIV_STATS_LOGS,      $priv,$en);
    Priv(0,                 1,LNG_MUSERS_F_PRIV_STATS_STATS,     PRIV_STATS_STATS,     $priv,$en);
    Priv(0,                 1,LNG_MUSERS_F_PRIV_STATS_RESET,     PRIV_STATS_RESET,     $priv,$en);
  
    Priv(MODULE_BOTS,       0,LNG_MUSERS_F_PRIV_BOTS,            PRIV_BOTS,            $priv,$en);
    Priv(MODULE_BOTS_SOCKS, 1,LNG_MUSERS_F_PRIV_BOTS_SOCKS,      PRIV_BOTS_SOCKS,      $priv,$en);
    Priv(MODULE_BOTS_PROXY, 1,LNG_MUSERS_F_PRIV_BOTS_PROXY,      PRIV_BOTS_PROXY,      $priv,$en);
    Priv(MODULE_BOTS_LC_SS, 1,LNG_MUSERS_F_PRIV_BOTS_LC_SS,      PRIV_BOTS_LC_SS,      $priv,$en);
    
    Priv(MODULE_BOTS_CMDS,  0,LNG_MUSERS_F_PRIV_BOTS_CMDS,       PRIV_BOTS_CMDS,       $priv,$en);
    Priv(MODULE_BOTS_CMDS,  1,LNG_MUSERS_F_PRIV_BOTS_CMDS_EDIT,  PRIV_BOTS_CMDS_EDIT,  $priv,$en);
    
    Priv(MODULE_LOGS_DB,    0,LNG_MUSERS_F_PRIV_LOGS_DB,         PRIV_LOGS_DB,         $priv,$en);
    Priv(MODULE_LOGS_DB,    1,LNG_MUSERS_F_PRIV_LOGS_DB_EDIT,    PRIV_LOGS_DB_EDIT,    $priv,$en);

    Priv(MODULE_LOGS_TMPS,  0,LNG_MUSERS_F_PRIV_LOGS_DBT,        PRIV_LOGS_DBT,        $priv,$en);
    Priv(MODULE_LOGS_TMPS,  1,LNG_MUSERS_F_PRIV_LOGS_DBT_EDIT,   PRIV_LOGS_DBT_EDIT,   $priv,$en);

    Priv(MODULE_LOGS_FILES, 0,LNG_MUSERS_F_PRIV_LOGS_FILES,      PRIV_LOGS_FILES,      $priv,$en);
    Priv(MODULE_LOGS_FILES, 1,LNG_MUSERS_F_PRIV_LOGS_FILES_EDIT, PRIV_LOGS_FILES_EDIT, $priv,$en);

    Priv(MODULE_USERS,      0,LNG_MUSERS_F_PRIV_USERS,           PRIV_USERS,           $priv,$en);
    Priv(MODULE_USERS,      1,LNG_MUSERS_F_PRIV_USERS_EDIT,      PRIV_USERS_EDIT,      $priv,$en);
   
    Priv(0,                 0,LNG_MUSERS_F_PRIV_USER,            PRIV_USER,            $priv,$en);
    Priv(0,                 0,LNG_MUSERS_F_PRIV_OPTIONS,         PRIV_OPTIONS,         $priv,$en);

    print '</table></tr></td><tr><td colspan="2" align="right">';
    if($en)print '<input class="ism" type="submit" value="'.($new?LNG_MUSERS_F_ADD_OK:($pedt&&$_GET['edit']!=$_SESSION['id']?LNG_MUSERS_F_EDIT_OK:'')).'">&nbsp;';
    print '<input class="ism" type="submit" value="'.LNG_MUSERS_F_BACK.'" onClick="window.location.href=\''.QUERY_STRING.'\';return false;"></td></tr></table>';
    if($en)print '</form>';
    HTMLEnd();
  }
  die();  
}

HTMLBegin(LNG_MUSERS,'function DelUser(uid,q){if(confirm(q))window.location=\''.QUERY_STRING.'&del=\'+uid;}');
$r=mysql_query('SELECT id,login FROM '.TABLE_USERS);
$total=mysql_affected_rows();
print '<table class="tbl1"><tr><td class="td1" colspan="'.($pedt?2:3).'">'.LNG_MUSERS_LIST.'&nbsp;('.$total.')</td>';
if($pedt)print '<td class="td1" align="center"><input type="submit" value="'.LNG_MUSERS_ADD.'" class="ism" style="width:100%" onClick="window.location=\''.QUERY_STRING.'&new\';"></td>';
print '</tr><tr><td class="td1" align="right">'.LNG_MUSERS_ID.'</td><td class="td1">'.LNG_MUSERS_LOGIN.'</td><td class="td1">&nbsp;</td></tr>';
if($total<1)print '<tr><td align="center" colspan="3" class="tdx1"><i>None :) DB error?</i></td></tr></table>';
else while(($m=mysql_fetch_row($r)))
{
  $act=$m[0]==$_SESSION['id'];
  $j=0;
  $a=(($j++)%2==0?1:2);
  print '<tr><td align="right" class="tdx'.$a.'">'.$m[0].'</td><td class="tdx'.$a.'">'.htmlentities($m[1]).'</td><td class="tdx'.$a.'" align="center"><input class="ism" style="width:90%" type="button" value="'.($pedt&&!$act?LNG_MUSERS_EDIT:LNG_MUSERS_VIEW).'" onClick="window.location=\''.QUERY_STRING.'&edit='.$m[0].'\';return false;">';
  if($pedt)print '<input '.($act?'disabled ':'').'class="ism" style="width:90%" type="button" value="'.LNG_MUSERS_DEL.'" onClick="javascript:DelUser(\''.$m['0'].'\',\''.addslashes(sprintf(LNG_MUSERS_DEL_Q,$m[1])).'\');return false;">';
  print '</td></tr>';
}
print '</table>';
HTMLEnd();

function Priv($mod,$lev,$name,$priv,$stat,$en)
{
  if($mod!=0&&!(MODULES&$mod))return;
  if($lev==0)$name='<b>'.$name.'</b>';
  print'<tr><td colspan="2">'.str_repeat('&nbsp;',$lev*4).'<input '.($en?'':'disabled ').'type="checkbox" name="priv_'.intval($priv).'"'.($stat&$priv?' checked':'').'>&nbsp;'.$name.'</td></tr>';
}
?>