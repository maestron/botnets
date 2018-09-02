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
 <tr bgcolor='#E4E4E4' height='20'>
  <td align='center' align='center' width='43'>
   <b>Type</b>
  </td>
  <td align='center' width='141'>
   <b>Adress and Port</b>
  </td>
  <td align='center' width='61'>
   <b>Status</b>
  </td>
 </tr>

 <tr bgcolor='#EFEFEF' height='20'>
  <td>HTTP:</td>
  <td>{strAdressH}</td>
  <td>{strStatusH}</td>
 </tr>

 <tr bgcolor='#EFEFEF' height='20'>
  <td>Sock:</td>
  <td>{strAdressS}</td>
  <td>{strStatusS}</td>
 </tr>
 <tr>
  <td colspan='3' bgcolor='#EFEFEF' style='font-size:7pt;'>
   {strInfo}
  </td>
 </tr>
</table>

<a name='{m_nID}'></a>
<script>
//location.href='#{m_nID}';
</script>

</body>

</html>