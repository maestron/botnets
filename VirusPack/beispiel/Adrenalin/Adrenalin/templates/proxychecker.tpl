<html>

<head>
  <title>Proxy checker</title>
</head>

<style>
TD, TEXTAREA, INPUT
{
        font-family: Tahoma;
        font-size: 8pt;
}
</style>

<script> window.focus(); </script>

<body leftMargin='0' topMargin='0' rightMargin='0' bottomMargin='0' marginHeight='0' marginWidth='0'>

<table width='100%'>
 <tr bgcolor='#C0C0C0' height='20'>
  <td align='center' colspan='3'>
   <b>Proxy Checker</b>
  </td>
 </tr>

 <tr bgcolor='#E4E4E4' height='20'>
  <td align='center' align='center'>
   <b>Type</b>
  </td>
  <td align='center'>
   <b>Adress and Port</b>
  </td>
  <td align='center'>
   <b>Status</b>
  </td>
 </tr>

 <tr bgcolor='#EFEFEF' height='20'>
  <td>
   HTTP:
  </td>
  <td>{strAdressH}</td>
  <td>{strStatusH}</td>
 </tr>

 <tr bgcolor='#EFEFEF' height='20'>
  <td>
   Sock:
  </td>
  <td>{strAdressS}</td>
  <td>{strStatusS}</td>
 </tr>
 <tr>
  <td colspan='3' bgcolor='#EFEFEF' style='font-size:7pt;' height='37'>
   {strInfo}
  </td>
 </tr>
 <tr bgcolor='#EFEFEF' height='20'>
  <td align='center' colspan='3'>
   <input type='button' value='Close' onclick='window.close();'>
  </td>
 </tr>
</table>

</body>

</html>