{if $notauth}

{display tpl='auth.tpl'}

{else}

{literal}
<script>

 function wnd( url )
 {
        window.open( url, "", "statusbar=no,menubar=no,toolbar=no,scrollbars=yes,resizable=no,width=400,height=200");
 }

</script>
{/literal}

<table>
<tr>
 <td>
 welcome <b>{$userinfo.login}</b> [ <a href='index.php?logout=1'>logout</a> ]<br>
 server time: {$time|date_format:"%d.%M.%Y/%H:%M:%S"}<br>

 {if $admin}

 [ <a href='admin.php'>manage accounts</a> |
   <a href="javascript:wnd('index.php?getlist=1')">get socks list</a> |
   <a href="javascript:wnd('index.php?getlist=2')">get http list</a> |
   <a href='dloader.php'>downloader</a> |
   <a href='upd.php'>updater</a> |
   <a href='info.php'>info</a> ]

 {else}
 [
   <a href="javascript:wnd('index.php?getlist=1')">get socks list</a> |
   <a href="javascript:wnd('index.php?getlist=2')">get http list</a> ]<br>
 you has used <b>{$userinfo.used_proxies}</b> proxies<br>
 {if $userinfo.total_proxies!=0}
 <b>{$userinfo.total_proxies - $userinfo.used_proxies}</b> proxies left<br>
 {/if}
 {if $userinfo.valid_to!=0}
 your account valid to <b>{$userinfo.valid_to|date_format}</b>
 {/if}

 {/if}

 </td>
</tr>
</table>

<form action='index.php' method='POST'>
<table>
<tr height='20'><td class='HEADER'><b>Filter</b></td></tr>
<tr class='ITEM'>
 <td>
 <table callspacing='0'><tr><td colspan='2'>
 <table>

{section name=i loop=$countries}
 <tr>
  <td>
  <input type='checkbox' name='flt[country][{$countries[i].code}]' value='{$countries[i].code}' {if $countries[i].checked}checked{/if}>
  <img src='{$countries[i].flag}'> {$countries[i].name}
  </td>
  <td><b>({$countries[i].num})</b></td>
 </tr>
{/section}

 </table>
 </td>
</tr>
<tr>
 <td align='right'><input type='text' name='flt[addr]' value='{$flt.addr}'></td>
 <td>IP address (you can use * symbols for mask)</td>
</tr>
<tr>
 <td align='right'><input type='text' name='flt[city]' value='{$flt.city}'></td>
 <td>city</td>
</tr>
<tr>
 <td align='right'><input type='text' name='flt[region]' value='{$flt.region}'></td>
 <td>region</td>
</tr>
<tr>
 <td align='right'>
 from:<input type='text' name='flt[speed_from]' size='5' value='{$flt.speed_from}'>
 to:<input type='text' name='flt[speed_to]' size='5' value='{$flt.speed_to}'></td>
 <td>proxy speed (Kb/s)</td>
</tr>
<tr>
 <td align='right'>
 <select name='flt[order]'>
  <option value=1 {if $flt.order==1}selected{/if}>speed</option>
  <option value=2 {if $flt.order==2}selected{/if}>country</option>
  <option value=3 {if $flt.order==3}selected{/if}>last request</option>
 </select>
 </td>
 <td>order param</td>
</tr>
<tr><td align='right'><input type='submit' value='submit'></td><td></td></tr>
</td>
</tr>
</table>
</table>
</form>

<table cellpadding='1' cellspacing='1'>

{if $proxies}

<tr height='20'><td class='HEADER' colspan='{if $admin}9{else}8{/if}'><b>{$total_proxies}</b> proxies in list</td></tr>
<tr class='LIST' height='20'>
 <td class='HEAD'>last request</td>
 <td class='HEAD'>address</td>
 <td class='HEAD'>country</td>
 <td class='HEAD'>city/region</td>
 <td class='HEAD'>speed</td>
 <td class='HEAD'>check</td>
 <td class='HEAD'>get it</td>
 {if $admin}<td class='HEAD'>kill</td>{/if}
</tr>

{section name=i loop=$proxies}

<tr class='ITEM'>
 <td align='right'>{$proxies[i].last_request|date_format:"%d.%m.%y/%H:%M:%S"}</td>
 <td>{hide_ip ip=$proxies[i].addr}</td>
 <td><img src='{$proxies[i].flag}'> {$proxies[i].country_full}</td>
 <td>{$proxies[i].city}/{$proxies[i].region}</td>
 <td align='right'>{$proxies[i].speed}</td>
 <td>[ <a href="javascript:wnd('check.php?id={$proxies[i].id}')">check</a> ]</td>
 <td>[ <a href="javascript:wnd('get.php?id={$proxies[i].id}')">get it</a> ]</td>
 {if $admin}<td>[ <a href="index.php?kill={$proxies[i].id}">kill</a> ]</td>{/if}
</tr>

{/section}

{else}

<tr height='20'><td><b>no proxies in list</b></td></tr>

{/if}

</table>

{$pages}

{/if}