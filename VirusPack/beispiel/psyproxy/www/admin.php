<?

require_once "common.php";

if (!check_auth() || !isset($_SESSION['admin']))
{
      logout();
      header("location: index.php");
}

if (isset($_POST['usr']))
{
      $a_vals = $_POST['usr'];

      if (empty($a_vals['login']))
            $errmsg .= "invalid login<br>";

      if ($_POST['submit']=="add" && empty($a_vals['pass1']))
            $errmsg .= "invalid password<br>";

      if ($a_vals['pass1'] !== $a_vals['pass2'])
            $errmsg .= "passwords missmatch<br>";

      if (isset($a_vals['by_time']) && empty($a_vals['valid_to']))
            $errmsg .= "invalid account validity time<br>";

      if (isset($a_vals['by_proxies']) && empty($a_vals['total_proxies']))
            $errmsg .= "invalid number of proxies<br>";

      $a_vals['t_stamp'] = 0;
      if (!empty($a_vals['valid_to']))
      {
            $t_arr = explode(".", $a_vals['valid_to']);
            if (sizeof($t_arr) < 3 || !checkdate($t_arr[1], $t_arr[0], $t_arr[2]))
                  $errmsg .= "invalid account validity time<br>";

            $a_vals['t_stamp'] = mktime(0, 0, 0, $t_arr[1], $t_arr[0], $t_arr[2]);
      }

      if (isset($errmsg))
      {
            $smarty->assign("errmsg", $errmsg);
            $smarty->assign("usr", $a_vals);
            $smarty->assign("edit", true);
      } else {
            $a_vals['icq'] = intval($a_vals['icq']);
            $a_vals['total_proxies'] = intval($a_vals['total_proxies']);

            $uid = sprintf("%X", crc32(md5($a_vals['login'])));

            $a_vals['nprx'] = intval($a_vals['nprx']);

            if ($_POST['submit']=="add")
            {
                  $sql = "INSERT INTO `users`
                          (`id`, `login`, `pass`, `registered`, `valid_to`, `used_proxies`, `total_proxies`, `email`, `icq`, `note`, `ip`, `nprx`)
                          VALUES
                          ('$uid', '{$a_vals['login']}', '".md5(md5($a_vals['pass1']))."', '".time()."', '{$a_vals['t_stamp']}',
                          '0', '{$a_vals['total_proxies']}', '{$a_vals['email']}', '{$a_vals['icq']}', '{$a_vals['note']}',
                          '{$a_vals['ip']}', '{$a_vals['nprx']}')
                  ";
            } else {
                  $sql = "UPDATE `users` SET
                          `valid_to`='{$a_vals['t_stamp']}', `total_proxies`='{$a_vals['total_proxies']}',
                          `email`='{$a_vals['email']}', `icq`='{$a_vals['icq']}', `note`='{$a_vals['note']}',
                          `ip`='{$a_vals['ip']}', `nprx`='{$a_vals['nprx']}'
                          WHERE `login`='{$a_vals['login']}'
                  ";
            }
            db_query($sql);
            header("location: admin.php");
      }
}
elseif (isset($_GET['del']))
{
      $sql = "DELETE
              FROM `users`
              WHERE `login`='".addslashes($_GET['del'])."'
      ";
      db_query($sql);
      header("location: admin.php");
}
elseif (isset($_GET['edit']))
{
      $sql = "SELECT *
              FROM `users`
              WHERE `login`='".addslashes($_GET['edit'])."'
      ";
      $r = db_query($sql);
      $a_vals = mysql_fetch_array($r);

      if ($a_vals['valid_to'] > 0)
      {
             $a_vals['valid_to'] = date('d.m.Y', $a_vals['valid_to']);
             $a_vals['by_time'] = 1;
      }

      if ($a_vals['total_proxies'] > 0)
      {
             $a_vals['by_proxies'] = 1;
      }

      $smarty->assign("edit", true);
      $smarty->assign("usr", $a_vals);
} else {

      $sql = "SELECT * FROM `users`";
      $r = db_query($sql);
      while ($f = mysql_fetch_array($r))
             $users[] = $f;

      if (isset($users))
      {
             $smarty->assign("users", $users);
             $smarty->assign("total_users", sizeof($users));
      }
}

$smarty->assign("tpl", "admin.tpl");
$smarty->display("index.tpl");

?>