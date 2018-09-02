[ <a href="index.php">back to proxies list</a> ]<p>
{display tpl='form.tpl'}

<table cellpadding='1' cellspacing='1'>

{if $users}

<tr height='20'>
 <td class='HEADER' colspan='12'><b>{$total_users}</b> users in database</b></td>
</tr>
<tr class='LIST' height='20'>
  <td class='HEAD'>login</td>
  <td class='HEAD'>UID</td>
  <td class='HEAD'>registered</td>
  <td class='HEAD'>e-mail</td>
  <td class='HEAD'>ICQ</td>
  <td class='HEAD'>time limit</td>
  <td class='HEAD'>proxies limit</td>
  <td class='HEAD'>used proxies</td>
  <td class='HEAD'>note</td>
  <td class='HEAD'>access IP</td>
  <td class='HEAD'>request limit</td>
  <td class='HEAD'>delete</td>
</tr>

{section name=i loop=$users}
<tr class='ITEM'>
 <td><a href='admin.php?edit={$users[i].login}'>{$users[i].login}</a></td>
 <td>{$users[i].id}</td>
 <td>{$users[i].registered|date_format}</td>
 <td>{$users[i].email}</td>
 <td>{$users[i].icq}</td>
 <td>{if $users[i].valid_to=='0'}<center>-</center>{else}{$users[i].valid_to|date_format}{/if}</td>
 <td align=right>{if $users[i].total_proxies=='0'}<center>-</center>{else}{$users[i].total_proxies}{/if}</td>
 <td align='right'>{$users[i].used_proxies}</td>
 <td><i>{$users[i].note}</i></td>
 <td>{$users[i].ip}</td>
 <td align='right'>{$users[i].nprx}</td> 
 <td>[ <a href='admin.php?del={$users[i].login}'>delete</a> ]</td>
</tr>
{/section}

{else}

{if !$edit}
<tr height='20'><td><b>no users in database</b></td></tr>
{/if}

{/if}

</table>
<p>[ <a href="index.php">back to proxies list</a> ]