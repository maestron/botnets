<?php

include("html_panel_header.php");

function _stat_referers()
{
	GLOBAL $hits_referer, $loads_referer, $hosts_referer;
	_load_vars();
	_make_stat2('статистика по рефералах',array('Реферал','Хиты','Хосты'),@$hits_referer,@$loads_referer,@$hosts_referer);
}

_stat_referers();

include("html_panel_footer.php");

?>