<?

include "common.php";

?>

<html>
<head>
<title>Get proxy</title>
<style>
BODY {
     BACKGROUND: #F1F0E7
}
TABLE {
     BACKGROUND: #FFCC99;
     BORDER: 1px solid black
}
TD {
     FONT-SIZE: 8pt; FONT-FAMILY: Verdana;
     TEXT-ALIGN: right
}
</style>
</head>
<body>
<center>

<?

if (!check_auth())
{
     die("<table cellpadding=2><tr><td><b>not auth</b></td></tr></table>");
}

if (!isset($_GET['id']))
     die("<table cellpadding=2><tr><td><b>proxy not found</b></td></tr></table>");

$sql = "SELECT *
        FROM `stat`
        WHERE `id`='{$_GET['id']}'
";

$r = db_query($sql);

if (mysql_num_rows($r) == 0)
     die("<table cellpadding=2><tr><td><b>proxy not found</b></td></tr></table>");

$f = mysql_fetch_array($r);

if (!isset($_SESSION['admin']))
{
      $sql = "SELECT * FROM `users` WHERE `login`='{$_SESSION['login']}'";
      $r = db_query($sql);
      if (mysql_num_rows($r) == 0)
      {
           die("<table cellpadding=2><tr><td><b>not auth</b></td></tr></table>");
      }

      $userinfo = mysql_fetch_array($r);
      if (($userinfo['valid_to'] == 0 || $userinfo['valid_to'] > time()) &&
          ($userinfo['total_proxies'] == 0 || $userinfo['total_proxies'] > $userinfo['used_proxies']))
      {
           $sql = "UPDATE `users`
                   SET `used_proxies`=`used_proxies`+1
                   WHERE `login`='{$_SESSION['login']}'
           ";
           db_query($sql);
      } else
           die("<table cellpadding=2><tr><td><b>account blocked</b></td></tr></table>");
}

echo "<table cellpadding=2><tr><td><b>{$f['addr']}</b></td><td></td></tr>".
     "<tr><td>HTTP port:</td><td><b>{$f['hport']}</b></td></tr>".
     "<tr><td>SOCKS 4/4+/5 port:</td><td><b>{$f['sport']}</b></td></tr>".
     "</table>";

?>

</center>
</body>
</html>