[ <a href="index.php">back to proxies list</a> ]<p>

<form action=dloader.php?d=add method="POST">
<table>
<tr height='20'><td class='HEADER'><b>Add file</b></td></tr>
<tr class='ITEM'>
<td>
<table>
<tr><td align="right">url</td><td><input type="text" name="url" id="url" size="30"></td></tr>
<tr><td align="right">downloads</td><td><input type="text" name="dnum" id="dnum" size="5"> (0 for unlimited)</td></tr>
<tr><td></td><td><input type="submit" value="add"></td></tr>
</table>
</td>
</tr>
</table>
</form>

<table cellspacing='1'>

{if $files}

<tr height='20'><td class='HEADER' colspan='4'><b>{$files_num}</b> files in list</td></tr>
<tr class='LIST' height='20'>
  <td class='HEAD'>url</td>
  <td class='HEAD'>downloads</td>
  <td class='HEAD'>downloaded</td>
  <td class='HEAD'>delete</td>
</tr>

{section name=i loop=$files}
<tr class='ITEM'>
  <td>{$files[i].url}</td>
  <td align='center'>{if $files[i].dnum==0}-{else}{$files[i].dnum}{/if}</td>
  <td align='center'>{$files[i].dtotal}</td>
  <td>[ <a href=dloader.php?d=del&id={$files[i].id}>delete</a> ]</td>
</tr>
{/section}

{else}

<tr height='20'><td><b>no files in list</b></td></tr>

{/if}

</table>
<p>
[ <a href="index.php">back to proxies list</a> ]