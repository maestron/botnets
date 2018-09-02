<?php
	while(list($key,$value)=each($_POST))	{$$key=$value;}
	while(list($key,$value)=each($_GET))	{$$key=$value;}
	while(list($key,$value)=each($_COOKIE))	{$$key=$value;}
?>