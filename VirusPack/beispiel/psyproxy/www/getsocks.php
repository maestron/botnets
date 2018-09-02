<?

$denymsg = "Access deny. Contact with service administrator.";

require_once "common.php";

header("Content-type: text/plain");

$uid = addslashes($_SERVER['QUERY_STRING']);
$sql = "SELECT * FROM `users` WHERE `id`='$uid'";
$r = db_query($sql);
if (mysql_num_rows($r) != 1)
       die($denymsg);
$userinfo = mysql_fetch_array($r);

if (($userinfo['ip'] !== $_SERVER['REMOTE_ADDR']) ||                 // check IP
    ($userinfo['valid_to'] > 0 && $userinfo['valid_to'] < time()))   // check account validity time
       die($denymsg);

$nprx = intval($userinfo['nprx']);
if ($nprx > 0)
       $limit = "LIMIT 0,$nprx";

$sql = "SELECT * FROM `stat` WHERE ".time()."-`last_request`<".($opt['request_timeout']*60)." ORDER BY `last_request` DESC ".$limit;
$r = db_query($sql);

while ($f = mysql_fetch_array($r))
       echo "{$f['addr']}:{$f['sport']}\n";

?>