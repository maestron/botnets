<?

if (@!mysql_connect($opt['mysql_host'], $opt['mysql_user'], $opt['mysql_pass']))
        die("<font color=#FF0066>Ops! Cant connect to MySQL server</font>");

if (@!mysql_select_db($opt['mysql_base']))
        die("<font color=#FF0066>mysql_select_db() error</font>");

function db_query($sql)
{
        $r = mysql_query($sql);

        if (mysql_error())
                die("<font color=#FF0066>SQL request error : ".mysql_error()."</font>");

        return $r;
}

?>