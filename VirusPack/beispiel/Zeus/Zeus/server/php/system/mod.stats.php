<?php if(!defined('__INDEX__'))die();
if(isset($_GET['reset'])&&PRIV&PRIV_STATS_RESET&&($_GET['reset']==1||$_GET['reset']==2))
{
  mysql_query('UPDATE '.TABLE_STATS.' SET '.($_GET['reset']==1?'inst':'time').'=0');
  header('Location: '.QUERY_STRING);
  die();
}

$width=200;
HTMLBegin(LNG_MSTATS);

$logs_a=MODULES&MODULE_LOGS&&PRIV&PRIV_STATS_LOGS&&MODULES&MODULE_LOGS_DB;
$stats_a=PRIV&PRIV_STATS_STATS;
$bots_a=MODULES&MODULE_BOTS&&PRIV&PRIV_BOTS;

print '<table width="'.($width*2).'" class="tbl1"><tr><td class="td1" colspan="2">'.LNG_MSTATS_TT.'</td></tr>';
$i=0;
if($logs_a)
{
  $logs_count=0;
  $ll=strlen(TABLE_LOGS.'_');
  $tbf=TABLE_LOGS.'_';
  if(($r=mysql_list_tables(MYSQL_DB)))while(($m=mysql_fetch_array($r)))if(strncmp($tbf,$m[0],$ll)===0&&($mt=@mysql_fetch_row(mysql_query('SELECT COUNT(id) FROM '.$m[0].$bidq2))))$logs_count+=$mt[0];
  print '<tr><td class="tdx1">'.LNG_MSTATS_TT_LOGS.'</td><td  class="tdx1" align="right"><b>'.$logs_count.'</b></td></tr>';
  $i++;
}

$tmp='-';
if(($mt=@mysql_fetch_row(mysql_query('SELECT MIN(ftime) FROM '.TABLE_STATS))))$tmp=$mt[0]>0?ftime(LNG_FORMAT_DT,$mt[0]):'-';
print '<tr><td width="100%" class="tdx'.($i%2?2:1).'">'.LNG_MSTATS_TT_FBOT.'</td><td class="tdx'.($i%2?2:1).'" align="right" nowrap><b>'.$tmp.'</b></td></tr>';
$i++;

$tmp=0;
if(($mt=@mysql_fetch_row(mysql_query('SELECT COUNT(comp_id) FROM '.TABLE_STATS))))$tmp=$mt[0];
print '<tr><td class="tdx'.($i%2?2:1).'">'.LNG_MSTATS_TT_BOTS.'</td><td class="tdx'.($i%2?2:1).'" align="right"><b>'.$tmp.'</b></td></tr>';
$i++;

if($bots_a)
{
  $tmp=0;
  if(($mt=@mysql_fetch_row(mysql_query('SELECT COUNT(comp_id) FROM '.TABLE_STATS.' WHERE time>='.(time()-86400).$bidq))))$tmp=$mt[0];
  print '<tr><td class="tdx'.($i%2?2:1).'">'.LNG_MSTATS_TT_BOTS24.'</td><td class="tdx'.($i%2?2:1).'" align="right"><b>'.$tmp.'</b></td></tr>';
  $i++;
}
print '</table><br><table class="tbl1"><tr><td class="td1" colspan="2">'.LNG_MSTATS_BOTNET.'&nbsp;';

$bn=isset($_GET['bn'])?$_GET['bn']:'';
$bidq='';
$bidq2='';
if($bn!=''){$bidq=' AND bn=\''.addslashes($bn).'\'';$bidq2=' WHERE bn=\''.addslashes($bn).'\'';}

$r=mysql_query('SELECT DISTINCT bn FROM '.TABLE_STATS);
$bids='';
if($r)while(($m=mysql_fetch_array($r)))if($m[0]!='')$bids.='<option value="'.$m[0].'"'.($bn==$m[0]?' selected':'').'>'.$m[0].'</option>';
print '<select id="bn"><option value="">'.LNG_MSTATS_BOTNET_ANY.'</option>'.$bids.'</select>&nbsp;<input class="ism" type="button" value="'.LNG_MSTATS_BOTNET_APPLY.'" onClick="var bn=document.getElementById(\'bn\');window.location=\''.QUERY_STRING.'&bn=\'+bn.options[bn.selectedIndex].value;"></td></tr><tr><td valign="top">';

if($stats_a)DrawStat(LNG_MSTATS_INSTS,'SELECT country FROM '.TABLE_STATS.' WHERE inst>0'.$bidq,1);
if($bots_a)
{
  if($stats_a)print '</td><td valign="top">';
  DrawStat(LNG_MSTATS_ONLINE,'SELECT country FROM '.TABLE_STATS.' WHERE time>=\''.(time()-OPT_BTONT*60).'\''.$bidq,2);
}
print '</td></tr></table>';
HTMLEnd();

function DrawStat($name,$query,$id)
{
  global $width;
  print '<table width="'.$width.'" class="tbl1">';
  if($r=mysql_query($query))
  {
    $list=array();
    $af=mysql_affected_rows();
    $sr=PRIV&PRIV_STATS_RESET;
    
    print '<tr><td align="left" class="td1" width="100%"'.($sr?'':' colspan="2"').'>'.$name.' ('.$af.')</td>';
    if($sr)print '<td class="td1" align="center"><input type="button" value="'.LNG_MSTATS_RESET.'" class="ism" width="100%" onClick="if(confirm(\''.addslashes(sprintf(LNG_MSTATS_RESET_P,$name)).'\'))window.location=\''.QUERY_STRING.'&reset='.$id.'\';"></td>';
    print '</tr>';

    if($af>0)
    {
      while($m=mysql_fetch_row($r))
      {
        if($m[0]=='')$m[0]=0;
        @$list[$m[0]]++;
      }
      arsort($list);
      $cnts=array_keys($list);
      $c=count($cnts);
      for($i=0,$j=0;$i<$c;$i++)if($cnts[$i]!='0')
      {
        $a=($j%2==0?1:2);
        print '<tr><td width="100%" class="tdx'.$a.'" align="left">'.$cnts[$i].'</td><td class="tdx'.$a.'" align="right"><b>'.$list[$cnts[$i]].'</b></td></tr>';
        $j++;
      }
    }
    else print '<tr><td colspan="2" align="center" class="tdx1"><i>'.LNG_MSTATS_EMPTY.'</i></td></tr>';
  }
  else print '<tr><td class="td1">'.$name.' (0)</td></tr><tr class="tdx1"><td>'.mysql_error().'</td></tr>';
  print '</table>';
}
?>