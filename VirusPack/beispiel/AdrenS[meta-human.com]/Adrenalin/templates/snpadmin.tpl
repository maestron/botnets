<html>

<head>
  <title>S'n'P Service</title>
</head>

<style>
TD, SELECT, TEXTAREA, INPUT
{
        font-family: Tahoma;
        font-size: 8pt;
}

A:link
{
        color: BLUE;
        text-decoration: none;
}

A:visited
{
        color: BLUE;
        text-decoration: none;
}

A:hover
{
        color: #E14C22;
        text-decoration: underline;
}

A:active
{
        color: BLUE;
        text-decoration: none;
}

</style>

<script language='javascript'>

var pServerDate = new Date();

pServerDate.setFullYear({m_nYear});
pServerDate.setMonth({m_nMonth});
pServerDate.setDate({m_nDay});
pServerDate.setHours({m_nHours});
pServerDate.setMinutes({m_nMinutes});
pServerDate.setSeconds({m_nSeconds});

var nSeconds = pServerDate.getSeconds();

function OnShowServerClock()
{
          pServerDate.setSeconds(nSeconds);

          if(nSeconds >= 60)
             nSeconds = 1;
          else
             nSeconds++;

          nSecond = pServerDate.getSeconds();
          nHour   = pServerDate.getHours();
          nMinute = pServerDate.getMinutes();
          nDay    = pServerDate.getDate();
          nMonth  = pServerDate.getMonth() + 1;
          nYear   = pServerDate.getFullYear();

          if(nSecond <= 9)
             nSecond = "0" + nSecond;
          if(nMinute <= 9)
             nMinute = "0" + nMinute;
          if(nHour <= 9)
             nHour   = "0" + nHour;
          if(nDay  <= 9)
             nDay    = "0" + nDay ;

          if(nMonth == 1)
             strMonth="January";
          if(nMonth == 2)
             strMonth="February";
          if(nMonth == 3)
             strMonth="March";
          if(nMonth == 4)
             strMonth="April";
          if(nMonth == 5)
             strMonth="May";
          if(nMonth == 6)
             strMonth="June";
          if(nMonth == 7)
             strMonth="July";
          if(nMonth == 8)
             strMonth="August";
          if(nMonth == 9)
             strMonth="September";
          if(nMonth == 10)
             strMonth="October";
          if(nMonth == 11)
             strMonth="November";
          if(nMonth == 12)
             strMonth="December";

          setTimeout("OnShowServerClock()", 1000);

          document.getElementById("l_Clock").innerHTML = "{strExpiredDate}<b>Current server date: </b>" + nDay + " " + strMonth + " " + nYear + ", "+ nHour + ":" + nMinute + ":" + nSecond;
}

function _checkAllProxies(strIDs)
{
        window.open('?action=CheckProxies&IDs='+strIDs,'proxyChecker','height=600,width=270,top=300,left=300,status=no,location=no,scrollbars=yes,toolbar=no,directories=no,menubar=1,resizable=0');
}

function _checkProxy(nID)
{
        window.open('?action=CheckProxy&ID='+nID,'proxyChecker'+nID,'height=153,width=250,top=300,left=300,status=no,location=no,toolbar=no,directories=no,menubar=0,resizable=0');
}

function _showFullInfo(nID)
{
        window.open('?action=ViewComments&ID='+nID,'proxyComments'+nID,'height=250,width=250,top=300,left=300,status=no,location=no,toolbar=no,directories=no,menubar=0,resizable=0');
}

</script>

<body bgcolor='#C0C0C0' onload='OnShowServerClock();' leftmargin='0' topmargin='0' marginwidth='0' marginheight='0'>
<table width='100%' height='100%' cellspacing='0' cellpadding='0' border='0'>
 <tr>
  <td align='center' valign='top'>

  <table width='1003' height='100%' cellspacing='4' cellpadding='4'>
   <tr>
    <td bgcolor='#FFFFFF' height='84'>
     <img src="../images/i_Logotype.gif" width="984" valign='top' height="84" alt="" border=0 style='border:1px solid gray;'>
    </td>
   </tr>
   <tr>
    <td bgcolor='#FFFFFF' height='25' align='right'>
     <div id='l_Clock'></div>
    </td>
   </tr>
    <td bgcolor='#FFFFFF' height='25'>
    <table cellspacing='1' cellpadding='0' height='15'>
     <tr>
      <td width='70'><b>Main menu</b>: </td>
      <td width='1' align='center' bgcolor='#000000'> </td>
      <td width='110' align='center' id='HomeCell'><a href='?' id='Home'>Home</a></td>
      <td width='1' align='center' bgcolor='#000000'> </td>
      {strSections}
      <td width='110' align='center'><a href='?action=Logout'>Logout</a></td>
           <td width='1' align='center' bgcolor='#000000'> </td>
  
     </tr>
    </table>
    </td>
   </tr>
   <tr>
    <td bgcolor='#FFFFFF' height='25'>
    <table cellspacing='1' cellpadding='0' height='15'>
     <tr>
      <td width='70'><b>Tools</b>: </td>
      <td width='1' align='center' bgcolor='#000000'> </td>
      <td width='110' align='center' id='ProxyCell'><a href='?action=SocksAndProxies&RealIP=1&orderBy=6&orderType=DESC' id='Proxy'>Socks and Proxies</a></td>
      </td>
 
      <td width='1' align='center' bgcolor='#000000'> </td>
      {strSections2}
     </tr>
    </table>
    <div id='NoObj'></div>
    <div id='NoObjCell'></div>
    <script>
      document.getElementById("{strSection}").style.fontWeight="bold";
      document.getElementById("{strSection}Cell").style.backgroundColor="#CDD5E4";
    </script>
    </td>
   </tr>
   <tr>
    <td bgcolor='#FFFFFF' valign='top' height='*'>
    {strContent}
    <BR><BR>
        <HR color=gray SIZE=1>

     (c) Shine Group

    </td>
   </tr>
  </table>

  </td>
 </tr>
</table>

</body>

</html>