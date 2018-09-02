<form action='index.php' method='POST'>
<table>
<tr height='20'><td class='HEADER'><b>Auth</b></td></tr>
<tr class='ITEM'>
 <td>
 <table callspacing='0'>
 {if $errmsg}<tr><td></td><td><font color=red>{$errmsg}</font></td></tr>{/if}
 <tr>
  <td align='right'> Login:</td>
  <td><input type='text' name='login'></td>
 </tr>
 <tr>
  <td align='right'> Password:</td>
  <td><input type='password' name='pass'></td>
 </tr>
 <tr><td></td><td><input type='submit' value='go'></td></tr>
 </table>
 </td>
</tr>
</table>
</form>