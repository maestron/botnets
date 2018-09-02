<?php


////////
$CONTENT = '
<form method="post" id="preferences" name="preferences" action="' . $_SERVER['PHP_SELF'] . '?c=preferences">
<input type="hidden" name="action" value="save">
<b style="color: black; font-size: 13px; padding-left: 18px; line-height: 28px;">Admin panel:</b>
<table width="100%" cellpadding="0" cellspacing="0">
<tr>
	<td width="3"><img src="./images/stl.gif" width="3" height="3"></td>
	<td bgcolor="#273238"></td>
	<td width="3"><img src="./images/str.gif" width="3" height="3"></td>
</tr>
<tr>
	<td bgcolor="#273238"></td>
	<td bgcolor="#273238" style="padding: 5px;">
		<table width="100%">
		<tr>
			<td>
				Admin login:<br>
				<input type="text" style="width: 300px;" name="conf_login" value="' . htmlspecialchars($config['AdminLogin']) . '">
				<br><br>
			</td>
			<td>
				Admin password (if you want to change):<br>
				<input type="text" style="width: 100%;" name="conf_pass">
				<br><br>
			</td>
		</tr>
		<tr>
			<td>
				Default admin panel language:<br>
				<select name="conf_language" style="width: 300px;">' . $langoptions . '</select>
			</td>
			<td width="300">
				Time for ajax autoreload (in seconds):<br>
				<input type="text" style="width: 100%;" name="conf_ajaxseconds" value="' . htmlspecialchars($config['AdminAjaxSeconds']) . '">
			</td>
		</tr>
		</table>
		<br style="font-size: 3px;">
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
<b style="color: black; font-size: 13px; padding-left: 18px; line-height: 28px;">URLs for normal fuctioning (of the system):</b>
<table width="100%" cellpadding="0" cellspacing="0">
<tr>
	<td width="3"><img src="./images/stl.gif" width="3" height="3"></td>
	<td bgcolor="#273238"></td>
	<td width="3"><img src="./images/str.gif" width="3" height="3"></td>
</tr>
<tr>
	<td bgcolor="#273238"></td>
	<td bgcolor="#273238" style="padding: 5px;">
		Url to Fragus:<br>
		<input type="text" style="width: 100%;" name="conf_url" value="' . htmlspecialchars($config['UrlToFolder']) . '">
		<br><br>
		Redirect to url upon completion:<br>
		<input type="text" style="width: 100%;" name="conf_finishurl" value="' . htmlspecialchars($config['FinishRedirect']) . '">
		<br><br>
		Redirect to url on double visit:<br>
		<input type="text" style="width: 100%;" name="conf_doubleurl" value="' . htmlspecialchars($config['DoubleIpRedirect']) . '">
		<br><br style="font-size: 3px;">
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
<b style="color: black; font-size: 13px; padding-left: 18px; line-height: 28px;">Default preferences:</b>
<table width="100%" cellpadding="0" cellspacing="0">
<tr>
	<td width="3"><img src="./images/stl.gif" width="3" height="3"></td>
	<td bgcolor="#273238"></td>
	<td width="3"><img src="./images/str.gif" width="3" height="3"></td>
</tr>
<tr>
	<td bgcolor="#273238"></td>
	<td bgcolor="#273238" style="padding: 5px;">
		<table width="100%">
		<tr>
			<td valign="top">
				Ajax check before use next exploit:<br>
				<select name="conf_ajaxcheck" style="width: 200px;"><option value="0">No</option><option value="1"' . ($config['AjaxCheckBeforeExploit'] ? ' selected' : '') . '>Yes</option></select>
				<br><br>
				Default file to load:<br>
				<select name="conf_defaultfile" style="width: 200px;"><option value="0">-- Random file</option>' . $fileslist . '</select>
			</td>
			<td valign="top" width="300">
				Default exploits:<br>
				<table width="300" cellpadding="0" cellspacing="0"><tr>' . $exploits . '</tr></table>
			</td>
		</tr>
		</table>
	</td>
	<td bgcolor="#273238"></td>
</tr>
<tr>
	<td><img src="./images/sbl.gif" width="3" height="3"></td>
	<td bgcolor="#273238"></td>
	<td><img src="./images/sbr.gif" width="3" height="3"></td>
</tr>
</table>
<input type="image" src="./images/button.png" style="width: 160px; height: 25px; margin-left: margin-bottom: -40px; margin-top: 20px;"><a href="javascript:document.getElementById(\'preferences\').submit();" style="color: white; text-decoration: none; font-weight: bold; position: relative; top: -8px; left: -125px; font-size: 12px;">Save preferences</a>
</form>
';


?>