<?

error_reporting(E_ALL ^ E_NOTICE);

session_start();

require_once "config.php";
require_once "MySQL.php";
include_once "libs/Smarty.class.php";

$smarty = new Smarty();

$smarty->compile_dir="./templates_c/";

$smarty->register_function("display", "display");
$smarty->register_function("hide_ip", "hide_ip");

function display($params)
{
     global $smarty;

     $smarty->display($params['tpl']);
}

function getmicrotime()
{
     list ($usec, $sec) = explode(" ", microtime());
     return ((float)$usec + (float)$sec);
}

function auth($login, $pass)
{
    global $opt;

    Sleep(3);

    if ($login == $opt['user'] && $pass == $opt['pass'])
    {
        $_SESSION['login'] = $login;
        $_SESSION['admin'] = true;

        header("location: index.php");
    } else {  // это не админ =)
        $sql = "SELECT * FROM `users` WHERE `login`='$login'";
        $r = db_query($sql);
        if (mysql_num_rows($r) == '1')
        {
             $f = mysql_fetch_array($r);
             if (md5(md5($pass)) === $f['pass'])
             {
                  if (($f['valid_to'] == 0 || $f['valid_to'] > time()) &&
                      ($f['total_proxies'] == 0 || $f['total_proxies'] > $f['used_proxies']))
                  {
                      $_SESSION['login'] = $login;
                      header("location: index.php");
                  } else return "account blocked (time or proxies limit)";
             }
        }
    }

    return "login error";
}

function hide_ip($param)
{
        $a = explode(".", $param['ip']);
        $a[2] = $a[3] = "***";
        return implode(".", $a);
}

function check_auth()
{
    if ($_SESSION['login'])
        return true;

    return false;
}

function logout()
{
    unset($_SESSION['login'], $_SESSION['admin']);
}

?>