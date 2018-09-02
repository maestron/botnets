<? if(!defined('__INDEX__'))die();
function HTMLBegin($title, $script = '', $pmenu = '')
{
  global $MNC,$MND;
  header('Content-Type: text/html; charset='.LNG_CODEPAGE);
  print '<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN"><html><head><title>'.LNG_TITLE.' :: '.$title.'</title>'.
        '<meta http-equiv="Content-Type" content="text/html; charset='.LNG_CODEPAGE.'"><link rel="stylesheet" href="theme/style.css" type="text/css"></head>';
  if($script != '')print '<script language="JavaScript">'.$script.'</script>';
  if($pmenu != '')print '<script language="JavaScript">'.$pmenu.'</script><script language="JavaScript" src="theme/menu.js"></script>';
  print '<body'.($pmenu != '' ? ' onclick="HideLastMenu()"' : '').'><table border="0" cellspacing="0" cellpadding="0" width="100%" height="100%"><tr><td class="top" colspan="2">&nbsp;'.LNG_TITLE.' :: '.$title.'</td></tr>';
  if(isset($MNC) && isset($MND) && isset($_SESSION['id']))
  {
    print '<tr><td class="mnu" valign="top"><div class="mnuh">'.LNG_MM_INFO.'</div><div class="mnui">'.LNG_MM_INFO_UN.' '.
          (isset($_SESSION['login']) ? $_SESSION['login'] : '-').'<br>'.LNG_MM_INFO_DATE.' '.gmdate(LNG_FORMAT_DATA).'<br>'.
          LNG_MM_INFO_TIME.' '.gmdate(LNG_FORMAT_TIME).'</div>';
    for($i = 0; $i < $MNC; $i += 4)if(PRIV & $MND[$i + 2] && ($MND[$i + 3] ==0 || MODULES & $MND[$i + 3]))
    {
      if($MND[$i] === 0)print '<div class="mnul"></div><div class="mnuh">'.$MND[$i + 1].'</div>';
      else print '<a class="mnua" href="'.$_SERVER['PHP_SELF'].'?m='.$MND[$i].'">'.(MODULE == $MND[$i] ? '&rarr;&nbsp;' : '').$MND[$i + 1].'</a>';
    }
    print '<div class="mnul"></div><a class="mnua" href="'.$_SERVER['PHP_SELF'].'?m=logout">'.LNG_MM_LOGOUT.'</a></td>';
  }
  print '<td class="op" valign="top" align="center">';
}

function HTMLEnd()
{
  print '</td></tr><tr><td colspan="2" class="cp">'.LNG_COPYRIGHT.'&nbsp;&nbsp;</td></table></body></html>';
}

function HTMLSmall($title, $data, $script = '', $pmenu = '')
{
  header('Content-Type: text/html; charset='.LNG_CODEPAGE);
  print '<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN"><html><head><title>'.LNG_TITLE.
        ' :: '.$title.'</title><meta http-equiv="Content-Type" content="text/html; charset='.LNG_CODEPAGE.
        '"><link rel="stylesheet" href="theme/style.css" type="text/css"></head>';
  if($script != '')print '<script language="JavaScript">'.$script.'</script>';
  if($pmenu != '')print'<script language="JavaScript">'.$pmenu.'</script><script language="JavaScript" src="theme/menu.js"></script>';
  print '<body'.($pmenu != '' ? ' onclick="HideLastMenu()"' : '').'>'.$data.'</body></html>';
}

function HTMLBox($text, $width = 0)
{
  print '<br><table class="tbl1"'.($width != 0 ? ' width="'.$width.'"' : '').'><tr><td align="center">'.$text.'</td></tr></table><br>';
}

function HTMLPopupMenuItem($id)
{
  return '<div style="display:none" id="menuSlide'.$id.'" align="left"></div>';
}
?>