<?php

function dRead($name) {
	return mysql_real_escape_string($_POST[$name]);
}
function showBotCount($iCount, $iMax) {
	if ($iCount == 0) {
		return "0 (0%)";
	} elseif($iCount == $iMax) {
		return $iCount." (100%)";
	} else {
		return $iCount." (".round(($iCount / $iMax) * 100, 2)."%)";
	}
}

function pHash($Password) {
	return(md5('%'.$Password.'$'.sha1($Password).'|#~'));
}
?>