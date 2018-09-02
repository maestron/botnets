<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<html>
	<head>
		<title>Fragus</title>
		<meta http-equiv="Content-Type" content="text/html; charset=windows-1251">
		<style>
		BODY {
			background-color: black;
			font-family: Trebuchet MS, Verdana, Arial;
			color: white;
			font-size: 12px;
			background: black url('./images/bg.png');
		}
		TD {
			font-family: Trebuchet MS, Verdana, Arial;
			color: white;
			font-size: 15px;
		}
		INPUT, TEXTAREA, SELECT {
			font-family: Trebuchet MS, Verdana, Arial;
			font-size: 12px;
			width: 180px;
		}
		A:link, A:visited, A:active {
			text-decoration: underline;
			color: white;
		}
		A:hover {
			color: #e3e3e3;
			text-decoration: none;
		}
		H1 {
			color: white;
			font-size: 18px;
		}
		</style>
	</head>
	<body>
		<br>
		<center>
		<table width="911" cellpadding="0" cellspacing="0" height="95">
			<tr>
				<td width="118"><a href="<?php echo $_SERVER['PHP_SELF']; ?>"><img src="./images/logo.png" width="118" height="95" border="0" alt="Fragus"></a></td>
				<td align="right" valign="bottom">
					&nbsp;
				</td>
			</tr>
		</table>

		<br><br>
		<table width="400" cellpadding="0" cellspacing="0">
		<tr>
			<td width="24"><img src="./images/tl.png" width="24" height="27"></td>
			<td background="./images/tc.png">&nbsp;</td>
			<td width="24"><img src="./images/tr.png" width="24" height="27"></td>
		</tr>
		<tr>
			<td background="./images/lc.png">&nbsp;</td>
			<td background="./images/cbg.png">
				<h1>Авторизация</h1>
				<center>
					<?php
					if (isset($_Errors['FailsLogin'])){
					?>
					<b style="color: red;">Не верный логин или пароль</b><br><br>
					<?php
					}
					?>
					<form method="post" id="auth" action="<?php echo $_SERVER['PHP_SELF']; ?>">
					<input type="hidden" name="auth" value="1">
					<table cellpadding="0" cellspacing="0">
					<tr>
						<td height="35" width="80">Логин:</td>
						<td><input type="text" id="login" name="login"<?php echo isset($_POST['login']) ? " value=\"" . trim(htmlspecialchars($_POST['login'])) . "\"" : ""; ?>></td>
					</tr>
					<tr>
						<td height="35">Пароль:</td>
						<td><input type="password" name="password"></td>
					</tr>
					<tr>
						<td height="35">Язык:</td>
						<td><select name="language"><?php echo $langoptions; ?></td>
					</tr>
					</table>
					<input type="image" src="./images/button.png" style="width: 160px; height: 25px; margin-left: 35px; margin-bottom: -20px; margin-top: 20px;"><a href="javascript:document.getElementById('auth').submit();" style="color: white; text-decoration: none; font-weight: bold; position: relative; top: 12px; left: -95px; font-size: 12px;">Войти</a>
					</form>
				</center>
				<script language="JavaScript">
				document.onload = document.getElementById('login').focus();
				</script>
			</td>
			<td background="./images/rc.png">&nbsp;</td>
		</tr>
		<tr>
			<td width="24"><img src="./images/bl.png" width="24" height="27"></td>
			<td background="./images/bc.png">&nbsp;</td>
			<td width="24"><img src="./images/br.png" width="24" height="27"></td>
		</tr>
		</table>
	</center>
 </body>
</html>