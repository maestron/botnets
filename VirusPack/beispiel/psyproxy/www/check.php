<?

include "common.php";

?>

<html>
<head>
<title>Check proxy</title>
<style>
BODY {
     BORDER: 1px solid black;
     FONT-SIZE: 8pt; FONT-FAMILY: Verdana;
     BACKGROUND: #F1F0E7
}
</style>
</head>
<body>

<?

set_time_limit(0);

function check($addr, $port)
{
     $mk_time = getmicrotime();

     $s = socket_create(AF_INET, SOCK_STREAM, 0);
     if (!$s)
     {
              echo "<font color=red>socket_create() fails</font> : "
                   .socket_strerror(socket_last_error($s))."<br>";
              return false;
     }

     socket_set_option($s, SOL_SOCKET,  SO_SNDTIMEO, array("sec"=>30, "usec"=>0));

     if (!@socket_connect($s, $addr, $port))
     {
              echo "<font color=red>connection fails</font> : "
                   .socket_strerror(socket_last_error($s))."<br>";
              return false;
     }

     $request = "GET http://ya.ru/ HTTP/1.0\r\n\r\n";
     echo "<b>connected!</b> sending request..."
         ."<font color=green><pre>$request</pre></font>";
     socket_write($s, $request, strlen($request));

     echo "<b>response:</b><br>";
     $str='';
     while ($out = socket_read($s, 1024))
            $str .= $out;

     if (!socket_last_error($s))
     {
          echo "<font color=green><pre>".substr($str, 0, strpos($str, "\r\n\r\n"))
              ."</pre></font><p><b>OK!</b><br>";

          echo sprintf("Ping time: %.3f sec", getmicrotime()-$mk_time);
     } else {
          echo "<font color=red>connection fails</font> : "
                   .socket_strerror(socket_last_error($s))."<br>";
          return false;
     }

     return true;
}

if (!isset($_GET['id']))
     die("<font color=#FF0066>Proxy not found</font>");

$sql = "SELECT *
        FROM `stat`
        WHERE `id`='{$_GET['id']}'
";

$r = db_query($sql);

if (mysql_num_rows($r) == 0)
     die("<font color=#FF0066>Proxy not found</font>");

$f = mysql_fetch_array($r);

check($f['addr'], $f['hport']);

?>

</body>
</html>