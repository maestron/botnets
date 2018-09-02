<?

include "config.php";

if (!mysql_connect($opt['mysql_host'], $opt['mysql_user'], $opt['mysql_pass']))
        die("Ops! Cant connect to MySQL server.");

if (@!mysql_select_db($opt['mysql_base']))
        die("mysql_select_db() error.");

?>