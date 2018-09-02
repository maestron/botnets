<?php if(!defined('__INDEX__'))die();
if($_SERVER['REQUEST_METHOD']=='POST')
{
  SetError(0);
  SetOK(0);
  if(isset($_POST['old_pass'])&&isset($_POST['new_pass1'])&&isset($_POST['new_pass2']))
  {
    if($_POST['new_pass1']==''||$_POST['new_pass1']!=$_POST['new_pass2']||$_POST['new_pass1']==$_POST['old_pass'])SetError(1);
    else if(strlen($_POST['new_pass1'])<6||strlen($_POST['new_pass1'])>64)SetError(3);
    else
    {
      $m=GetUserData('pass');
      if($m[0]!=md5($_POST['old_pass']))SetError(2);
      else 
      {
        mysql_query("UPDATE users SET pass='".md5($_POST['new_pass1'])."' WHERE id='".$_SESSION['id']."' LIMIT 1");
        $_SESSION['pass']=md5($_POST['new_pass1']);
        SetOK(1);
      }
    }
  }
  header('Location: '.QUERY_STRING);
  die();
}

HTMLBegin(LNG_MUSER);
ShowError('LNG_MUSER_ERROR_');
ShowOK('LNG_MUSER_OK_');
print '<form method="POST" action="'.QUERY_STRING.'"><table class="tbl1"><tr><td><table class="tbl1" width="100%"><tr><td class="td1" colspan="2">'.LNG_MUSER_PASS.'</td></tr>'.
      '<tr><td>'.LNG_MUSER_OLD_PASS.'</td><td><input type="password" name="old_pass"></td></tr>'.
      '<tr><td>'.LNG_MUSER_NEW_PASS1.'</td><td><input type="password" name="new_pass1"></td></tr>'.
      '<tr><td>'.LNG_MUSER_NEW_PASS2.'</td><td><input type="password" name="new_pass2"></td></tr></table></tr></td>'.
      '<tr><td colspan="2" align="right"><input class="ism" type="submit" value="'.LNG_MUSER_CHANGE.'"></td></tr></table></form>';
HTMLEnd();
?>