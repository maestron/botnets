{literal}
<script>
 function hide()
 {
      if (document.getElementById('usr[by_time]').checked)
           document.getElementById('valid_to').style.display = '';
      else {
           document.getElementById('valid_to').style.display = 'none';
           document.getElementById('usr[valid_to]').value = '';
      }

      if (document.getElementById('usr[by_proxies]').checked)
           document.getElementById('total_proxies').style.display = '';
      else {
           document.getElementById('total_proxies').style.display = 'none';
           document.getElementById('usr[total_proxies]').value = '';
      }
 }
</script>
{/literal}

<form action='admin.php' method='POST'>
<table>
<tr height='20'><td class='HEADER'><b>{if $edit}Edit user{else}Add user{/if}</b></td></tr>
<tr class='ITEM'><td>
<table callspacing='0'>
{if $errmsg}
<tr><td colspan='2'><font color='red'><b>errors:</b><br>{$errmsg}</font></td></tr>
{/if}
<tr>
 <td colspan='2'><b>Account information</b></td>
</tr>
<tr>
 <td align='right'>login</td>
 <td><input type='text' name='usr[login]' value='{$usr.login}'></td>
</tr>
<tr>
 <td align='right'>password</td>
 <td><input type='password' name='usr[pass1]'></td>
</tr>
<tr>
 <td align='right'>confirm</td>
 <td><input type='password' name='usr[pass2]'></td>
</tr>
<tr><td colspan='2'><b>Account type</b></td></tr>
<tr>
 <td align='right'><input type='checkbox' name='usr[by_time]' value='1' {if $usr.by_time}checked{/if} onClick='hide()'></td>
 <td>restriction by time</td>
</tr>
<tr id='valid_to' {if !$usr.by_time}style='display:none'{/if}>
 <td align='right'>valid to date</td>
 <td><input type='text' name='usr[valid_to]' value='{$usr.valid_to}'><small>('d.m.Y' - e.g. 8.11.2006)</small></td>
</tr>
<tr>
 <td align='right'><input type='checkbox' name='usr[by_proxies]' value='1' {if $usr.by_proxies}checked{/if} onClick='hide()'></td>
 <td>restriction by number of used proxies</td>
</tr>
<tr id='total_proxies' {if !$usr.by_proxies}style='display:none'{/if}>
 <td align='right'>num of proxies</td>
 <td><input type='text' name='usr[total_proxies]' size='8' value='{$usr.total_proxies}'></td>
</tr>
<tr><td colspan='2'><b>Account details</b></td></tr>
<tr>
 <td align='right'>e-mail</td>
 <td><input type='text' name='usr[email]' value='{$usr.email}'></td>
</tr>
<tr>
 <td align='right'>icq</td>
 <td><input type='text' name='usr[icq]' value='{$usr.icq}'></td>
</tr>
<tr>
 <td align='right'>note</td>
 <td><textarea name='usr[note]' rows='3' cols='30'>{$usr.note}</textarea></td>
</tr>
<tr><td colspan='2'><b>Script access</b></td></tr>
<tr>
 <td align='right'>client IP</td>
 <td><input type='text' name='usr[ip]' value='{$usr.ip}'></td>
</tr>
<tr><td colspan='2'>num of proxies, returned by one request</td></tr>
<tr>
 <td></td>
 <td><input type='text' name='usr[nprx]' value='{$usr.nprx}' size='8'> (0 - return all)</td>
</tr>
<tr><td colspan='2'><i>* All account information fields is required</i></td></tr>
<tr>
 <td align='right'></td>
 <td><input type='submit' name='submit' value='{if $edit}edit{else}add{/if}'> <input type="reset" value="reset"></td>
</tr>
</table>
</td></tr>
</table>
</form>