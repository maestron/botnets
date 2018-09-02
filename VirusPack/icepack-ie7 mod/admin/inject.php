<?php
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	IcePack Platinum Edition
-----------------------------------------------------
	2007 (c) IDT Group
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
?>
<html>
	<head>
		<meta http-equiv="refresh" content="25">
		<style>
		.tableBorder
		{
		border-left:      1px solid #EEEEEE;
		border-right:     1px solid #EEEEEE;
		margin:           0 0 3px 0;
		padding:          0;
		}
		.tableHeading
		{
		font-family:       Lucida Grande, Verdana, Geneva, Sans-serif;
		font-size:         11px;
		font-weight:       bold;
		color:             #fff;
		padding:           5px 6px 5px 6px;
		background:        #fff url(images/bg_table_heading.jpg) repeat-x left top;
		border-top:        1px solid #ceeafe;
		border-bottom:     1px solid #ceeafe;
		margin-bottom:     1px;
		text-align:        left;
		}
		.tableCellTwo
		{
		font-family:       Lucida Grande, Verdana, Geneva, Sans-serif;
		font-size:         11px;
		color:             #333;
		padding:           4px 10px 4px 6px;
		border-top:        2px solid #fff;
		border-bottom:     1px solid #ceeafe;
		background:        #FFF url(images/bg_cell_two.jpg) repeat-x left top;
		}
		</style>
	</head>
	<body>
	<div align="center">
		<table cellpadding="0" cellspacing="0" border="0" class="tableBorder" width="90%">
			<tr>
				<td class="tableHeading">Хост</td>
				<td class="tableHeading">Статус</td>
			</tr>
			<tr>
<?
if (@filesize("tmp/inject.txt") == 0) echo "Загрузка...";
$fo = @fopen ("tmp/inject.txt", "r");
$data = @fread($fo, @filesize("tmp/inject.txt"));
@fclose($fo);
echo $data;
?>
		</table>
	</div>		
	</body>
</html>