<html>

<head>
  <title>{strCaption}</title>
</head>

<style>
TD
{
        font-family: Tahoma;
        font-size: 8pt;
}
</style>

<body>
<table width='100%' height='100%'>
 <tr>
  <td align='center'>

  <table width='200' cellspacing='0' cellpadding='4' height='100' border='0' style='border:1px solid #000000'>
  <form name='loginForm' action='{strAction}' method='POST'>
   <tr>
    <td colspan='2' bgcolor='C0C0C0'>
    <b>{strCaption}</b>
    </td>
   </tr>
   <tr>
    <td>
     Username:
    </td>
    <td>
     <input type='text' name='username' style='width:123px;'>
    </td>
   </tr>
   <tr>
    <td>
     Password:
    </td>
    <td>
     <input type='password' name='password' style='width:123px;'>
    </td>
   </tr>
   <tr>
    <td width='*' colspan='2' align='center'><input type='submit' value='Submit'> &nbsp; &nbsp; <input type='reset' value='Reset'></td>
   </tr>
   </form>
  </table>

  </td>
 </tr>
</table>

</body>

</html>