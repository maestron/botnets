<?php
$adminpass="ultra";
$pass=$_GET['pass'] ;
echo "<html><head><title>ACHTUNG</title></head><body vlink='#055595' bgcolor='#002140' bgcolor='#002140' background='bg.bmp' leftmargin='2' rightmargin='1' topmargin='1' marginwidth='1' marginheight='1'><p><link href='style1.css' rel='stylesheet' type='text/css'><script language='JavaScript' src='link.js' type='text/javascript'></script><TD vAlign=top></TD>";
if($pass!=$adminpass):
echo "<center> <font color='#b1dbdd' size=7px>ACHTUNG!</font><BR><BR><BR><BR><BR><BR><font color='#ffffff' size=4px>для входа нужно ввести пароль !</font><BR><BR> <a  class='red' name='f77rv1' href='http://ya.ru'>уйти</a><br><form method=get action=stat.php><table><TR><Td> Пароль: &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input style='width:180px;' class='inp' value='password' type='Text' name='pass'><br><br></TR></td><TR><td valign=top><input type='submit' value='вход' class='inp'></td></TR></table></form></body></html>";
exit;
endif;
echo "<a  class='red' name='f77rdv1' href='stat.php?pass=$pass'>обновить</a><br>";

$count=ereg_replace("<","",$count);
$count=ereg_replace(">","",$count);
$count=ereg_replace("\"","",$count);
$count=ereg_replace("/","",$count);
$count=ereg_replace(";","",$count);
$count=ereg_replace("%","",$count);
if($count==""):
$date=date("d.m.Y");
$tim=date("H:i:s");
$out=explode(":", $tim);
$out1=explode(".", $date);
$count=$out1[0];
if($out[0]==16): $count=$out1[0]+1;endif;
if($out[0]==17): $count=$out1[0]+1;endif;
if($out[0]==18): $count=$out1[0]+1;endif;
if($out[0]==19): $count=$out1[0]+1;endif;
if($out[0]==20): $count=$out1[0]+1;endif;
if($out[0]==21): $count=$out1[0]+1;endif;
if($out[0]==22): $count=$out1[0]+1;endif;
if($out[0]==23): $count=$out1[0]+1;endif;
if($count==32): $count="01";endif;
endif;
if($count==1): $count="01";endif;
if($count==2): $count="02";endif;
if($count==3): $count="03";endif;
if($count==4): $count="04";endif;
if($count==5): $count="05";endif;
if($count==6): $count="06";endif;
if($count==7): $count="07";endif;
if($count==8): $count="08";endif;
if($count==9): $count="09";endif;
if($count>31||$count<1):
echo "ERROR";
echo $count;
exit;
endif;
echo $count;
echo "<html><font size=2px>";
echo "<br> lamerz log A-311 Death by Corpse<br><br>";
$logdata=file("logs/N1$count.txt");
$kolvo=count($logdata);
$kolvo1=$kolvo-66;
for($i=$kolvo1;$i<$kolvo;$i++) {
$logdata1=$logdata[$i];
if($logdata1!=""):
echo "$logdata1<br>";
endif;
}
echo "</html></font>";
//end logging
exit;
?>