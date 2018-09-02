<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" version="-//W3C//DTD XHTML 1.1//EN" xml:lang="en">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>Stasi Lite</title>

<script type="text/javascript" src="javascripts/prototype.js"> </script> 
<script type="text/javascript" src="javascripts/effects.js"> </script> 
<script type="text/javascript" src="javascripts/window.js"> </script> 
<script type="text/javascript" src="javascripts/window_ext.js"> </script> 
<script type="text/javascript" src="javascripts/debug.js"> </script> 
<script type="text/javascript" src="desktop.js"> </script>
<link href="style.css" rel="stylesheet" type="text/css">
<link href="themes/default.css" rel="stylesheet" type="text/css"> 
<link href="themes/alphacube.css" rel="stylesheet" type="text/css"> 
<style type="text/css">
<!--
body,td,th {
	color: #000000;
}
-->
</style></head>

<body onload="showStat()">
  <div id="mainicons">
<table width="300" border="0" cellpadding="0" cellspacing="15" id="icons">
      <tr>
        <td width="80" height="78" onClick="showArbeitsplatz();"><table width="80" border="0" align="center" cellpadding="0" cellspacing="0">
            <tr>
              <td><div align="center"><img src="images/Computer.png" alt="Arbeitsplatz" width="64" height="64" /></div></td>
            </tr>
            <tr>
              <td><div align="center">Arbeitsplatz</div></td>
            </tr>
        </table></td>
        <td width="80" onClick="showBots();"><table width="80" border="0" align="center" cellpadding="0" cellspacing="0">
            <tr>
              <td><div align="center"><img src="images/Network Connection Control Panel.png" alt="Bots" width="64" height="64" /></div></td>
            </tr>
            <tr>
              <td><div align="center">Bots</div></td>
            </tr>
        </table></td>
        <td width="80" onClick="showExec();"><table width="80" border="0" align="center" cellpadding="0" cellspacing="0">
            <tr>
              <td><div align="center"><img src="images/Execute.png" alt="Befehle" width="64" height="64" /></div></td>
            </tr>
            <tr>
              <td><div align="center">Befehle</div></td>
            </tr>
        </table></td>
      </tr>
    </table>
  </div>
  <div id="papericons"> 
	<table width="110" border="0" align="right" cellpadding="0" cellspacing="15" id="icons">
      <tr>
        <td width="80" onClick="showLogout();"><table width="80" border="0" align="center" cellpadding="0" cellspacing="0">
            <tr>
              <td><div align="center"><img src="images/Sleeping Computer.png" alt="Logout" width="64" height="64" /></div></td>
            </tr>
            <tr>
              <td><div align="center">Logout</div></td>
            </tr>
        </table></td>
      </tr>
    </table>
  </div>
  
</body>
</html>
