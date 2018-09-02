<?php

$selleradded = isset($_Messages['SellerAdded']) ? "<b style='color: green;'>Seller added</b><br><br>" : "";


if (isset($_GET['edit_id'])){
	$selleredit =<<<EOF
	<table cellpadding="0" cellspacing="0">
	<tr>
		<td width="3"><img src="./images/stl.gif" width="3" height="3"></td>
		<td bgcolor="#273238"></td>
		<td width="3"><img src="./images/str.gif" width="3" height="3"></td>
	</tr>
	<tr>
		<td bgcolor="#273238"></td>
		<td bgcolor="#273238" style="padding: 5px;">
			<b>Edit seller:</b>
			<form method="post" id="sellersedit" action="{$_SERVER['PHP_SELF']}?c=sellers&edit_id={$seller['id']}" style="margin: 0px;">
			<input type="hidden" name="action" value="edit">
			<table>
			<tr>
				<td>Seller name:</td>
				<td><input type="text" name="name" style="width: 150px;" value="{$seller['name']}"></td>
			</tr>
			<tr>
				<td>Uploading file:</td>
				<td><select name="file" style="width: 150px;"><option value='0'>-- Random file</option>{$seller['files']}</select></td>
			</tr>
			<tr>
				<td valign="top">Exploits:</td>
				<td><table>{$seller['exploits']}</table></td>
			</tr>
			<tr>
				<td>&nbsp;</td>
				<td><input type="image" src="./images/button.gif" width="129" height="25"><a href="javascript:document.getElementById('sellersedit').submit();" style="color: white; text-decoration: none; font-weight: bold; position: relative; top: -8px; left: -77px;">Edit</a></td>
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
	$selleredit = "";
}

$sellersdata = "";
for ($i = 0; $i < count($sellers); $i++){
	$sellersdata .= "
	<tr>
	<td class='tdb'><a href='" . $_SERVER['PHP_SELF'] . "?seller_id=" . $sellers[$i]['id'] . "' class='al'>stat</a>&nbsp;</td>
	<td class='tdb'>&nbsp;<nobr><a href='" . str_replace("admin.php", "stat.php", strtolower($_SERVER['PHP_SELF'])) . "?seller=" . $sellers[$i]['hash'] . "' target='_blank' class='al'>stat link</a></nobr>&nbsp;</td>
	<td class='tdb'><nobr><a href='javascript://' onclick='prompt(\"Copy this link (Ctrl+C)\", \"" . $config['UrlToFolder'] . "show.php?s=" . $sellers[$i]['hash'] . "\");' class='al'>traffic link</a></nobr>&nbsp;</td>
	<td class='tdb'><a href='" . $_SERVER['PHP_SELF'] . "?c=sellers&edit_id=" . $sellers[$i]['id'] . "'><img src='./images/icone.gif' width='11' height='11' border='0' alt='Edit' title='Edit'></a></td>
	<td class='tdb'>&nbsp;<a href='" . $_SERVER['PHP_SELF'] . "?c=sellers&clear_id=" . $sellers[$i]['id'] . "'><img src='./images/iconc.gif' width='13' height='16' border='0' alt='Clear' title='Clear' align='absmiddle'></a>&nbsp;</td>
	<td class='tdb'><a href='" . $_SERVER['PHP_SELF'] . "?c=sellers&delete_id=" . $sellers[$i]['id'] . "'><img src='./images/icond.gif' width='14' height='14' border='0' alt='Delete' title='Delete' align='absmiddle'></a>&nbsp;</td>
	<td class='tdb'>" . $sellers[$i]['name'] . "</td>
	<td class='tdb'>" . (isset($sellers[$i]['file']) ? $sellers[$i]['file'] : "<i>Random file</i>") . "</td>
	<td class='tdb'>" . ((count($sellers[$i]['exploits']) > 0) ? implode(", ", $sellers[$i]['exploits']) : "<i>exploits not selected</i>"). "</td>
	<td class='tdb' align='center'>" . $sellers[$i]['hosts'] . "</td>
	<td class='tdb' align='center'>" . $sellers[$i]['frags'] . "</td>
	<td class='tdb' align='center'>" . (($sellers[$i]['hosts'] == 0) ? "0" : round(($sellers[$i]['frags'] / $sellers[$i]['hosts'] * 100), 2)) . "%</td>
	</tr>
	";
}
if (count($sellers) == 0){
	$sellersdata = "<tr><td colspan='10'>Sellers list is empty</td></tr>";
}

$CONTENT =<<<EOF
{$selleradded}
{$selleredit}

<table cellpadding="0" cellspacing="0">
<tr>
	<td width="3"><img src="./images/stl.gif" width="3" height="3"></td>
	<td bgcolor="#273238"></td>
	<td width="3"><img src="./images/str.gif" width="3" height="3"></td>
</tr>
<tr>
	<td bgcolor="#273238"></td>
	<td bgcolor="#273238" style="padding: 5px;">

		<img src="./images/icona.gif" width="15" height="15" align="absmiddle">&nbsp;<a href="javascript://" onclick="if (document.getElementById('addseller').style.display == 'none'){ document.getElementById('addseller').style.display = 'block'; } else { document.getElementById('addseller').style.display = 'none'; }"><b>Add seller</b></a>
		<div style="display: none;" id="addseller">
		<form method="post" action="{$_SERVER['PHP_SELF']}?c=sellers" style="margin: 0px;" id="sellers">
		<input type="hidden" name="action" value="add">
		<table>
		<tr>
			<td>Seller name:</Td>
			<td><input type="text" name="name" style="width: 150px;"></td>
		</tr>
		<tr>
			<td>Uploading file:</td>
			<td><select name="file" style="width: 150px;"><option value='0'>-- Random file</option>{$files}</select></TD>
		</tr>
		<tr>
			<td valign="top">Exploits:</td>
			<td><table>{$exploits}</table></td>
		</tr>
		<tr>
			<td>&nbsp;</td>
			<td><input type="image" src="./images/button.gif" width="129" height="25"><a href="javascript:document.getElementById('sellers').submit();" style="color: white; text-decoration: none; font-weight: bold; position: relative; top: -8px; left: -77px;">Add</a></td>
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
	<b>Sellers list:</b>
	<table cellpadding="0" cellspacing="0" width="720">
	<tr>
		<td>&nbsp;</td>
		<td>&nbsp;</td>
		<td>&nbsp;</td>
		<td>&nbsp;</td>
		<td>&nbsp;</td>
		<td>&nbsp;</td>
		<td class="tbg"><nobr>&nbsp;Seller name&nbsp;</td>
		<td class="tbg"><nobr>&nbsp;Uploading file&nbsp;</td>
		<td class="tbg">&nbsp;Exploits&nbsp;</td>
		<td class="tbg">&nbsp;Hosts&nbsp;</td>
		<td class="tbg">&nbsp;Frags&nbsp;</td>
		<td class="tbg">&nbsp;Percentage&nbsp;</td>
	</tr>
	{$sellersdata}
	</table>
</div>
EOF;


?>