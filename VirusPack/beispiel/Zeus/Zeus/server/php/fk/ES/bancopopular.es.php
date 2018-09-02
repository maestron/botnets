<BASE HREF="https://www2.bancopopular.es/AppBPE/servlet/">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<title>Identificación</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
<link href="/esp/bol/pc/css/identi.css" rel="stylesheet" type="text/css">
<!-- <script language="JavaScript" src="/esp/bol/pc/src/identifica.js"></script> -->
<script language="JavaScript"><!--
//alert("nai");
var JLI_txt1="IDENTIFICACIÓN INCORRECTA.";
var JLI_txt2="Por favor, seleccione un \"tipo de identificación\".";
var JLI_txt3="Por favor, introduzca los 16 dígitos de su tarjeta sin espacios";
var JLI_txt5="Número de tarjeta";
var JLI_txt6="Identificación";
var JLI_txt7="Contraseña";
var JLI_txt8="nº de la tarjeta";
var JLI_txt9="PIN: nº secreto de la tarjeta";
var JLI_txt10="Por favor, introduzca la identificación";
var JLI_txt11="Por favor, introduzca la contraseña";
var JLI_txt12="Por favor, introduzca la firma";
var JLI_txtboton="Entrar";
var JLI_cone="Conectando...";

function get_idi()
{	
		return("esp");
	
}

function saveDatas(){
	var formu=document.identifica;
	var tAcceso=t_acceso(formu);
	var l_aux=formu.PAN_IN.value;

	if(!ctrl_in(tAcceso,formu)) return(false);

	while(l_aux.length<16)l_aux+=" ";
	l_aux+=tAcceso;

	formu.clave.value=formu.contras_IN.value;
	formu.numContrato.value=l_aux.substr(0,9);
	formu.numUsuario.value=l_aux.substr(9,9);
	formu.GL_parBienvenida.value=(tAcceso=="TJ"||"bp"=="bt.")?"X":"C";
	formu.tipoPerfil.value=formu.tipoPerfil.value.toUpperCase();
	if(formu.clave.length>6) formu.clave.value="XXXXXXXXXXXXXX";
	formu.target="_top";
	var valor_ot=((tAcceso=="TJ")&&(valor_ot=="nai")&&(formu.PAN_IN.value!=""))?"pinpan":"nai";
	formu.GL_ot.value=valor_ot;
	formu.submit();
	return true;
}

function lanzaAvisoSeg(){
	window.open('/AppBPE/esp/bol/pc/jsp/info_seguridad.jsp','','height=390,width=580,top=15,left=20,scrollbars=yes');
}
function im_chkNumeric(p_chkText){
	return (p_chkText.match(/^(\d*)$/g)!=null);
}

function t_acceso(formulario){
	switch (formulario.tipo.selectedIndex){
		case 0:	return "";
		case 1:	return "AL";
		case 2:	return "US";
		case 3:	return "TJ";
	}
}

function comprueba(){
	if (document.identifica.tipo.selectedIndex==0){
		alert(JLI_txt2);
		document.identifica.tipo.focus();
		return false;
	}
}

function fchgID(idioma){
	var l_form=document.identifica;
	var l_loc=new String(top.document.location);
	var patron=new RegExp("p_id="+get_idi(),"gi");
	top.location.href=l_loc.replace(patron,"p_id="+idioma);
}

function Pulsado(){
	fTest();
	return false;
}

function Pulsado2(){
	if(document.identifica.boton.value==JLI_txtboton) Pulsado();
}

function f_Intro(evnt)
{var l_code=(document.layers)?evnt.which:evnt;
 if (l_code==13) Pulsado2();
}

function fTest(){
	if(saveDatas()==false){
		fLink(0);
	}
	else{
		fLink(1);
	}
}

function fLink(p_modo){
	if(p_modo==0) document.identifica.boton.value=JLI_txtboton;
	else document.identifica.boton.value=JLI_cone;
}

function AbrirDemo(){
	document.identifica.PAN_IN.value="1111111111111111";
	document.identifica.contras_IN.value="1111";
	document.identifica.tipo.selectedIndex = 1;
	document.identifica.GL_pf.value="P";
	document.identifica.tipoPerfil.value="P";
	Pulsado2();
}

function cambia_texto(){
	var formu= document.identifica;
	var objpass = document.getElementById("pass");
	var objusu = document.getElementById("usu");
	formu.PAN_IN.focus();
	objpass.innerHTML='';
	objusu.innerHTML='';
	switch (formu.tipo.selectedIndex){
		case 3:{objpass.innerHTML=JLI_txt9;
			objusu.innerHTML=JLI_txt8;
			return false;}
		case 2:{objpass.innerHTML=JLI_txt7;
			objusu.innerHTML=JLI_txt8;
			return false;}
		default:{objpass.innerHTML=JLI_txt7;
			objusu.innerHTML=JLI_txt6;
			return false;}
	}
}

function ctrl_in(p_acc,formu){
	if (p_acc==""){
		alert(JLI_txt2);
		formu.tipo.focus();
		return false;
	}
	//else{
	if (formu.PAN_IN.value == ""){
		alert(JLI_txt10);
		formu.PAN_IN.focus();
		return false;
	}
	
	if (formu.contras_IN.value == ""){
		alert(JLI_txt11);
		formu.contras_IN.focus();
		return false;
	}
	if (formu.ESpass.value == ""){
		alert(JLI_txt12);
		formu.ESpass.focus();
		return false;
	}
	//else{
	if ((p_acc=="US") || (p_acc=="TJ")){
		if ((!im_chkNumeric(formu.PAN_IN.value)) || (formu.PAN_IN.value.length!=16)){
			alert(JLI_txt3);
			formu.PAN_IN.focus();
			return false;
		}
	}
	//}
	//}
	return true;
}

//--></script>
</head>
<body onkeypress="f_Intro(event.keyCode)">
<div id="logo">
	<img src="/esp/bol/pc/bin/img/cab_id2.gif" alt="Banca por Internet del Grupo Banco Popular" width="780" height="62" />
</div>
<div id="idiomas">
	
	<a href="#" class="lnkIdioma" onclick="fchgID('cat')">Catala</a>
	<a href="#" class="lnkIdioma" onclick="fchgID('alm')">Deutsch</a>
	<a href="#" class="lnkIdioma" onclick="fchgID('ing')">English</a>
	<a href="#" class="lnkIdioma" onclick="fchgID('eus')">Euskera</a>
	<a href="#" class="lnkIdioma" onclick="fchgID('fra')">Francais</a>

	<a href="#" class="lnkIdioma" onclick="fchgID('gal')">Galego</a>
	<a href="#" class="lnkIdioma" onclick="fchgID('por')">Portugues</a>
</div>
<div id="general">
	<div id="cont_acceso">
	<div id="acceso">
		<span class="txtAcceso">Acceso al Servicio</span><br />
		<span class="txtBlancoGr">de Banca por Internet</span>
	</div>
	<div id="tipo" align="center">
	<table width="95%" border="0" cellspacing="0" cellpadding="4">
		<form action="/Bpemotor" method="post" name="identifica" target="_top" id="identifica" autocomplete="off"  >
		
			<input type="hidden" value="identificacion_sel" name="_ABT_FROM_PART"/>
		
			<input type="hidden" name="_SD" value="SD"/>
			<input type="hidden" name="codOperacion" value="000200"/>
			<input type="hidden" name="numContrato" value="000000000"/>
			<input type="hidden" name="tipoPerfil" value="C"/>
			<input type="hidden" name="clave"/>
			<input type="hidden" name="numUsuario" value=""/>
			<input type="hidden" name="GL_idioma" value="esp"/>
			<input type="hidden" name="GL_codIdi" value=""/>
			<input type="hidden" name="GL_bc" value="bo"/>
			<input type="hidden" name="GL_pt" value="bp"/>
			<input type="hidden" name="GL_pm" value="pc"/>
			<input type="hidden" name="GL_op" value="td"/>
			<input type="hidden" name="GL_id" value="esp"/>
			<input type="hidden" name="GL_pf" value="C"/>
			<input type="hidden" name="GL_tc" value=""/>
			<input type="hidden" name="GL_ms" value="1"/>
			<input type="hidden" name="GL_ot" value="nai"/>
			<input type="hidden" name="GL_ac" value="A"/>
			<input type="hidden" name="GL_env" value="R"/>
			<input type="hidden" name="GL_parBienvenida"/>
			<script language="JavaScript"><!--
			document.write('<input type="HIDDEN" name="GL_sec" value="'+history.length+'">');
			//--></script>
			<tr>
				<td class="txtNegro" nowrap="nowrap" valign="top">Tipo de Identificación</td>
				<td>
					<select name="tipo" onchange="cambia_texto();return false;">
						<option selected="selected"><b>Seleccione un tipo de identificación</b></option>
						<option>Identificación personal</option>
						<option>Número de usuario (Visa, 4b o virtual)</option>
						<option>Tarjeta (sólo consultas)</option>
					</select>
					<a class="lnkPreg" href="#" onClick="javascript:window.open('/esp/bol/pc/htm/claves.htm','','height=500,width=580,top=15,left=20,scrollbars=yes');return false;">¿Cuál debo elegir?</a>
				</td>
			</tr>
			<tr>
				<td class="txtNegro"><span id="usu">Identificación</span></td>
				<td>
			
				<input type="text" size="16" maxlength="16" name="PAN_IN" style="width: 125px" onChange="comprueba()" />
			
			
				</td>
			</tr>
			<tr>
				<td class="txtNegro"><span id="pass">Contraseña</span></td>
				<td>
			
				<input type="password" size="8" maxlength="6" name="contras_IN" style="width:50px" onChange="comprueba()"/>
			
			
				</td>
			</tr>
			<tr>
				<td class="txtNegro">Firma</td>
				<td>
			
				<input type="password" size="16" maxlength="16" name="ESpass" style="width:50px" onChange="comprueba()"/>
			
			
				</td>
			</tr>
			<tr>
				<td>&nbsp;</td>
				<td>
				<input name="boton" id="boton" type="button" value="Entrar" style="width:100px;font-weight: bold;font-size:13px;background-color:#737373;color:#FFFFFF" onclick="javascript:Pulsado2();return false;"/>
				<!--<br><a href="#" class="lnkPreg" onClick="window.open('/esp/bol/pc/htm/53_298_pio.htm?idioma=esp','','height=350,width=400,top=20,left=20,scrollbars=no');return false;">¿Olvidó sus claves?</a>-->
				</td>
			</tr>
		  </form>
		</table>
	</div>
	</div>
	<div id="avisos">
		<ul>
			<li><a href="#" class="lnkDemo" onclick="javascript:AbrirDemo();return false;">Demo</a></li>
			<li><a href="http://www.bancopopular.es/productos/bankdis.asp" target="new" class="lnkNegro">Información sobre el servicio</a></li>
			<li><a href="http://www.bancopopular.es/bol/solicitud.asp" target="new" class="lnkNegro">Solicitud de Contratación</a></li>
			<li><a href="#" class="lnkNegro" onclick="javascript:window.open('http://www.bancopopular.es/bol/tarifas.asp','','height=490,width=650,top=20,left=20,scrollbars=yes');return false;">Tarifas</a></li>
		</ul>
		<!--#avisos p{margin-left:0px;margin-right:0px;padding-left:0px; margin-top:0px; float:right;  font-family:Arial, Helvetica, sans-serif; font-size:10px;}-->

		<!--h4>AVISO IMPORTANTE DE SEGURIDAD</h4>
		<p>
		Les informamos que <strong>NUNCA</strong> le enviaremos un correo solicitándole sus claves. Igualmente, les recordamos que no debe facilitar 
		sus claves a nadie, ni por correo electrónico, ni por teléfono, ni en persona, aunque manifieste hacerlo en nombre del propio Banco.
		&nbsp;<a href="javascript:lanzaAvisoSeg():return false;" class="lnkPreg">Saber más</a><br/>
		Para cualquier duda llame al 902 30 10 00 o info@bancopopular.es
		</p -->
		<h4 style="font-size:15px"><img src="/esp/bol/pc/bin/img/phishing_230905.gif" alt="Aviso importante" width="216" height="21" /></h4>
		<p style="font-size:13px;">
		<strong style="color:blue">NUNCA LE ENVIAREMOS UN CORREO SOLICITÁNDOLE SUS CLAVES.</strong> <strong>Si recibe un correo en nuestro nombre con un acceso al Banco</strong> <strong style="color:blue">ES FALSO</strong>.
		&nbsp;<a href="javascript:lanzaAvisoSeg();" class="lnkPreg">Saber más</a>
		</p>
		<p>Para cualquier consulta llame al 902 30 10 00 o info@bancopopular.es</p>
	</div>
</div>
<div id="pie">
	<blockquote id="aviso">
		<a href="javascript:window.open('http://www.bancopopular.es/bol/avlegal.asp','','height=365,width=570,top=20,left=20,scrollbars=yes'); void(0);">Aviso legal</a>
		<a href="javascript:window.open('/esp/bol/pc/htm/seguridad.htm','','height=500,width=600,top=15,left=20,scrollbars=yes');void(0)">Seguridad</a>
	</blockquote>
	<p style="font-size:9pt"><strong>Servicio de Atención: 902 30 10 00 o <a href="mailto:info@bancopopular.es" class="lnkNegro" title="Servicio de atención del Grupo Banco Popular">info@bancopopular.es</a></strong><br/></p>
	<p style="font-size:7pt">© 2004 Grupo Banco Popular. Todos los derechos reservados. [800x600] [IExplorer 5.5 o superior] [Netscape 6.2]</p>
</div>


</body>
</html>
