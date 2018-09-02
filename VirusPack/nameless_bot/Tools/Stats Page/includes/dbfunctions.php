<?php
error_reporting(0);

function quite()
{
exit ('<body text=#FF0000 bgcolor=#000000><p><font face=Tahoma><b>&nbsp;[ Nameless Bot ]</b></font></p><p><b>Critical Error ..</b></p><p>Could not connect to the database, please check and vaildate the database info in config.php </p>');
}

$connect = @mysql_connect ($db_host, $db_username, $db_password);
if (!(@mysql_select_db ($db_name))) quite();

function checktables()
{
$check2 = query("select * from visitors");
if (!$check2) { quite(); return false; }
else return ture;
}
function query($query) 
{
global $connect;
return mysql_query($query,$connect);
}


function all_bots()
{
$total = query("select id from visitors");
$total = mysql_num_rows($total);
return $total;
}


function new_bots()
{

$total = query("select new from visitors where new = 1");
$total = mysql_num_rows($total);
return $total;

}

if (query ("select * from visitors") )
{
$all_bots = all_bots();
$new_bots = new_bots();
}


function bots_countries()
{

global $all_bots;
global $new_bots;

$counter= true;
$allcountries = query("select country, count(*) as total from visitors group by country desc");
while ( $country = mysql_fetch_array($allcountries) )
{
echo "<tr>
		<td bgcolor=\"#FFFFFF\" width=\"233\">
		<p align=\"center\">
		<font color=\"#000000\" face=\"Verdana\" style=\"font-size: 7pt\">$country[country]</font></td>
		<td bgcolor=\"#FFFFFF\">
		<p align=\"center\"><font color=\"#000000\" face=\"Verdana\" style=\"font-size: 7pt\">$country[total]</font></td>
	";

$total = $country[total];
if ( $total != 0 &&  $counter )
echo "<td bgcolor=\"#4A83B5\" width=\"22%\">
		<p align=\"center\">
		<font face=\"Verdana\" style=\"font-size: 7pt; font-weight:700\" color=\"#FFFFFF\">$all_bots</font></td>
			<td bgcolor=\"#4A83B5\" width=\"22%\">
		<p align=\"center\"><span style=\"font-weight: 700\">
		<font face=\"Verdana\" style=\"font-size: 7pt\" color=\"#FFFFFF\">$new_bots</font></span></td>";
$counter= false;
}



}


?>