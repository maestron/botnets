<?php



$link = $config['UrlToFolder'] . "show.php" . $sellerhash;
$iframe = htmlspecialchars("<iframe src=\"" . $link . "\" width=\"1\" height=\"1\" style=\"display:none;\"></iframe>");
$packediframe = htmlspecialchars("<script language=\"JavaScript\">" . JavaScript::encrypt("document.write('<iframe src=\"" . $link . "\" width=\"1\" height=\"1\" style=\"display:none;\"></iframe>')", $config['CryptSignature']) . "</script>");


////////
$CONTENT =<<<EOF
<span style="color: black; font-size: 13px;">Показать ссылку на трафик для:</span> <select onchange="location.href='{$_SERVER['PHP_SELF']}?c=trafficlinks&seller_id=' + this.value;"><option value="0">Суммарно</option>{$selleroptions}</select><br><br>


Прямая ссылка:<br>
<input type="text" style="width: 100%;" readonly="readonly" onclick="this.focus(); this.select();" value="{$link}">

<br><br>
Ифрейм:<br>
<input type="text" style="width: 100%;" readonly="readonly" onclick="this.focus(); this.select();" value="{$iframe}">

<br><br>
Закриптованный ифрейм:<br>
<textarea style="width: 100%; height: 150px;" readonly="readonly" onclick="this.focus(); this.select();">{$packediframe}</textarea>


EOF;


?>