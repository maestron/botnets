<?php


function OnValidateMail($m_strMail)
{
        if (eregi("^[a-z0-9]+([-_\.]?[a-z0-9])+@[a-z0-9]+([-_\.]?[a-z0-9])+\.[a-z]{2,4}", $m_strMail))
            return (TRUE);
        else
            return (FALSE);
}



function OnPrepareString($m_strString)
{
        $m_strString = addslashes($m_strString);

        $m_strString = str_replace ("<",   "&lt;",  $m_strString);
        $m_strString = str_replace (">",   "&gt;",  $m_strString);
        $m_strString = str_replace ("\r",  "",      $m_strString);
        $m_strString = str_replace ("\n",  "<br>",  $m_strString);
        $m_strString = str_replace ("'",   "&#34",  $m_strString);
        $m_strString = str_replace ("%",   "&#37;", $m_strString);
        $m_strString = str_replace ("!",   "&#33;", $m_strString);
        $m_strString = str_replace ("^ +", "",      $m_strString);
        $m_strString = str_replace (" +$", "",      $m_strString);
        $m_strString = str_replace (" +",  " ",     $m_strString);
        $m_strString = str_replace ("|",   "l",     $m_strString);
        $m_strString = str_replace ("'", "&#39",    $m_strString);
        $m_strString = str_replace ("`", "&#96",    $m_strString);

        return ($m_strString);
}



function OnParityColor($m_nParity,$m_strColorOne,$m_strColorTwo)
{
        if($m_nParity%2==0)
                   return $m_strColorOne;
        else
                     return $m_strColorTwo;
}


function OnCheckDate($m_strDay,$m_strMonth,$m_strYear)
{
        $m_arrDays=array(31,28,31,30,31,30,31,31,30,31,30,31);

        if ($m_strYear%4==0) $m_arrDays[1]=29; else $m_arrDays[1]=28;
                if ($m_strDay>$m_arrDays[$m_strMonth-1])
                        $m_strDay=$m_arrDays[$m_strMonth-1];

        return $m_strDay;
}


function OnChangeURL($m_strString)
{
        $m_strCMSPath = substr(strCMSPath,3);
        $m_strString  = str_replace(strHostName,"",$m_strString);
        $m_strString  = str_replace(str_replace("www.","",strHostName),"",$m_strString);
        $m_strString  = str_replace($m_strCMSPath,"",$m_strString);

        return $m_strString;
}


function OnReplacePseudoTags($m_strTags,$m_strString)
{
        $m_arrTags = explode("|",$m_strTags);

        for($i=0;$i<count($m_arrTags);$i++)
        {
                $m_strString = str_replace("[".$m_arrTags[$i]."]","<".$m_arrTags[$i].">",str_replace("[/".$m_arrTags[$i]."]","</".$m_arrTags[$i].">",$m_strString));
        }

        $m_strString = preg_replace("#([\t\r\n ])([a-z0-9]+?){1}://([\w\-]+\.([\w\-]+\.)*[\w]+(:[0-9]+)?(/[^ \"\n\r\t<]*)?)#i", '\1<a href="\2://\3">\2://\3</a>', $m_strString);
    $m_strString = preg_replace("#([\t\r\n ])(www|ftp)\.(([\w\-]+\.)*[\w]+(:[0-9]+)?(/[^ \"\n\r\t<]*)?)#i", '\1<a href="http://\2.\3">\2.\3</a>', $m_strString);
    $m_strString = preg_replace("#([\n ])([a-z0-9\-_.]+?)@([\w\-]+\.([\w\-\.]+\.)*[\w]+)#i", "\\1<a href=\"mailto:\\2@\\3\">\\2@\\3</a>", $m_strString);
    $m_strString = substr($m_strString, 1);

        return $m_strString;
}

?>