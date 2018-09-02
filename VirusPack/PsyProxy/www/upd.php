<?

require_once "common.php";

if (!check_auth() || !isset($_SESSION['admin']))
{
      logout();
      header("location: index.php");
}

if (isset($_POST['chost']))
{
     $sql = "UPDATE `opt` SET `value`='".addslashes($_POST['chost'])."' WHERE `name`='chost'";
     db_query($sql);
     header("location: upd.php");
}

if (isset($_POST['upd']))
{
     $sql = "UPDATE `opt` SET `value`='".addslashes($_POST['upd'])."' WHERE `name`='upd'";
     db_query($sql);
     header("location: upd.php");
}

$sql = "SELECT `value` FROM `opt` WHERE `name`='chost'";
$r = db_query($sql);
if (mysql_num_rows($r) > 0)
{
     $smarty->assign("chost", mysql_result($r, 0, 0));
}

$sql = "SELECT `value` FROM `opt` WHERE `name`='upd'";
$r = db_query($sql);
if (mysql_num_rows($r) > 0)
{
     $smarty->assign("upd", mysql_result($r, 0, 0));
}

$smarty->assign("tpl", "upd.tpl");
$smarty->display("index.tpl");

?>