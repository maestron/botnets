<html>

<head>
  <title>Proxy Info</title>
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
 <form action='?action=ViewComments&ID={m_nID}&save=1' method='POST'>
 <tr bgcolor='#C0C0C0' height='20'>
  <td align='center'>
   <b>Commentaries</b>
  </td>
 </tr>

 <tr height='20'>
  <td align='center'>
   <textarea name='comments' style='width:100%;height:192px;'>{m_strInfo}</textarea>
  </td>
 </tr>

 <tr bgcolor='#EFEFEF' height='20'>
  <td align='center'>
   <input type='submit' value='Save' title='Насрать в каментах!' onclick='window.opener.location.reload();'> &nbsp; &nbsp; <input type='button' value='Close' onclick='window.close();'>
  </td>
 </tr>
 </form>
</table>

</body>

</html>