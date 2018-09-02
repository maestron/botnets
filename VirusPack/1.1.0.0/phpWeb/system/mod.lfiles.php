<?php if(!defined('__INDEX__'))die();

if(isset($_GET['del'])&&strncmp(strtoupper($_GET['del']),strtoupper(PATH_LFILES).'/',strlen(PATH_LFILES)+1)===0&&!strstr($_GET['del'],'..')&&strcmp(strtoupper($_GET['del']),strtoupper(PATH_LFILES))!=0)
{
  if(is_dir($_GET['del']))ClearDir($_GET['del']);
  else @unlink($_GET['del']);
  header('Location: '.QUERY_STRING.'&dir='.urlencode(dirname($_GET['del'])));
  die();
}

$dir=(isset($_GET['dir'])?$_GET['dir']:PATH_LFILES);
if(strncmp(strtoupper($dir),strtoupper(PATH_LFILES).'/',strlen(PATH_LFILES)+1)!==0||strstr($dir,'..'))$dir=PATH_LFILES;

HTMLBegin(LNG_MLFILES,'function DelFile(f,q){if(confirm(q))window.location=\''.QUERY_STRING.'&del=\'+f;}');
ReadFolder($dir);
HTMLEnd();

function ReadFolder($dir)
{
$i=0;
$tsize=0;
$tfiles=0;
$cols=PRIV&PRIV_LOGS_FILES_EDIT?5:4;
print '<table class="tbl1" width="600"><tr><td class="td1" colspan="'.$cols.'">'.htmlentities($dir).'</td></tr><tr><td class="td1">#</td><td class="td1" width="100%">'.LNG_MLFILES_C_NAME.'</td><td class="td1" width="100" nowrap>'.LNG_MLFILES_C_SIZE.'</td><td class="td1" nowrap>'.LNG_MLFILES_C_MDATE.'</td>';
if(PRIV&PRIV_LOGS_FILES_EDIT)print '<td class="td1" width="80">'.LNG_MLFILES_C_ACTIONS.'</td>';
print '</tr>';
$isroot=strcmp(strtoupper($dir),strtoupper(PATH_LFILES))!=0?false:true;
if(!$isroot)
{
  $a=($i%2==0?1:2);
  $upl=dirname($dir);
  print '<tr><td class="tdx'.$a.'" align="right">'.($i+1).'</td><td class="tdx'.$a.'"><a class="ca" href="'.QUERY_STRING.'&dir='.urlencode($upl).'">'.htmlentities('..').'</a></td>'.
        '<td class="tdx'.$a.'" align="right" nowrap>'.LNG_MLFILES_TYPE_UPLEVEL.'</td>'.
        '<td class="tdx'.$a.'" align="right" nowrap>'.ftime(LNG_FORMAT_DT, filemtime($upl)).'</td>';
  if(PRIV&PRIV_LOGS_FILES_EDIT)print '<td class="tdx'.$a.'" align="center">&nbsp;</td>';
  print '</tr>';
  $i++;
}
$ok = 0;
if(!($d=@opendir($dir)))print '<tr><td class="tdx'.($i%2==0?1:2).'" colspan="'.$cols.'">'.LNG_MLFILES_ERROR1.'</td></tr>';
else
{
  $ok = 1;
  $dirs=array();
  $files=array();
  while(($file=readdir($d)))if($file!='.'&&$file!='..')
  {
    if(is_dir($dir.'/'.$file))$dirs[]=$file;
    else $files[]=$file;
  }
  closedir($d);
  
  foreach($dirs as $file)
  {
    $a=($i%2==0?1:2);
    $ff=$dir.'/'.$file;
    print '<tr><td class="tdx'.$a.'" align="right">'.($i+1).'</td><td class="tdx'.$a.'"><a class="ca" href="'.QUERY_STRING.'&dir='.urlencode($ff).'">'.htmlentities($file).'</a></td>'.
          '<td class="tdx'.$a.'" align="right" nowrap>'.LNG_MLFILES_TYPE_DIR.'</td>'.
          '<td class="tdx'.$a.'" align="right" nowrap>'.ftime(LNG_FORMAT_DT, filemtime($ff)).'</td>';
    if(PRIV&PRIV_LOGS_FILES_EDIT)print '<td class="tdx'.$a.'" align="center"><input class="ism" type="button" value="'.LNG_MLFILES_DEL.'" onClick="javascript:DelFile(\''.$ff.'\',\''.addslashes(sprintf(LNG_MLFILES_DELQ,$file)).'\');return false;"></td>';
    print '</tr>';
    $i++;
  }
  
  foreach($files as $file)
  {
    $a=($i%2==0?1:2);
    $ff=$dir.'/'.$file;
    $ss=filesize($ff);
    $tsize+=$ss;
    print '<tr><td class="tdx'.$a.'" align="right">'.($i+1).'</td><td class="tdx'.$a.'"><a href="'.$ff.'">'.htmlentities($file).'</a></td>'.
          '<td class="tdx'.$a.'" align="right" nowrap>'.htmlentities($ss).'</td>'.
          '<td class="tdx'.$a.'" align="right" nowrap>'.ftime(LNG_FORMAT_DT, filemtime($ff)).'</td>';
    if(PRIV&PRIV_LOGS_FILES_EDIT)print '<td class="tdx'.$a.'" align="center"><input class="ism" type="button" value="'.LNG_MLFILES_DEL.'" onClick="javascript:DelFile(\''.$ff.'\',\''.addslashes(sprintf(LNG_MLFILES_DELQ,$file)).'\');return false;"></td>';
    print '</tr>';
    $i++;
    $tfiles++;
  }
}
if($ok&&$isroot&&$i==0)print '<tr><td class="tdx'.($i%2==0?1:2).'" colspan="'.$cols.'" align="center">'.LNG_MLFILES_EMPTY.'</td></tr>';
print '<tr><td class="td1" colspan="'.$cols.'">'.sprintf(LNG_MLFILES_TOTAL,$tsize,$tfiles).'</td></tr></table>';
}
function ClearDir($dir)
{
if(!($dh=@opendir($dir)))return false;
while(($file=@readdir($dh))!==false)if($file!='.'&&$file!='..')
{
  if(is_dir($dir.'/'.$file))
  {
    ClearDir($dir.'/'.$file);
    @rmdir($dir.'/'.$file);
  }
  else @unlink($dir.'/'.$file);
}
closedir($dh);
return @rmdir($dir)?true:false;
}
?>