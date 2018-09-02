<?if(!defined('__INDEX__'))die();
$page = '<center>';
if($error == 2)$page .= '<center class="error">'.LNG_MLOGIN_BADLOGIN.'</center><br><br>';
$page .= '<form method="POST" action="'.QUERY_STRING.'"><table class="tbl1"><tr><td colspan="2" class="td1">'.LNG_MLOGIN.'</td></tr><tr><td>'.LNG_MLOGIN_USER.'</td><td><input type="text" value="" name="l" style="width:170px"></td></tr><tr><td>'.LNG_MLOGIN_PASS.'</td><td><input type="password" value="" name="p" style="width:170px"></td></tr><tr><td>'.LNG_MLOGIN_LNG.'</td><td><select name="lng" style="width:170px">';
$list = explode(',', LNG_LIST);
foreach($list as $v)
{
  $ll = explode('|', $v);
  $page .= '<option value="'.$ll[1].'"'.($ll[1] == $_SESSION['lng'] ? ' selected' : '').'>'.$ll[0].'</option>';
}
$page .= '</select></td></tr><tr><td>&nbsp;</td></tr><tr><td colspan="2" align="left"><input type="checkbox" class="ism" name="rmb" value="1">&nbsp;'.LNG_MLOGIN_REMEMBER.'</td></tr><tr><td colspan="2" align="right"><input type="submit" class="ism" value="'.LNG_MLOGIN_ACTION.'"></td></tr></table></form></center>';
HTMLSmall(LNG_MLOGIN, $page);
?>