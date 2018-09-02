<?php
	include_once("expl_ie6_adodb.php");
	include_once("expl_ie6_mdac.php");
	include_once("expl_ie6_wvf.php");
	if (_browser()=="Internet Explorer 6.0"){
		ie6_adodb();
//		ie6_mdac();
//		ie6_wvf();
//		
	}
	if (eregi("Internet Explorer 5",_browser())){
		ie6_adodb();
		ie6_mdac();
	}
	if (eregi("Internet Explorer 4",_browser())){
		ie6_mdac();
	}
?>