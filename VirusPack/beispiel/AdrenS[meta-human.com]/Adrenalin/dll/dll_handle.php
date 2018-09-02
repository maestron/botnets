<?php


function OnNotice($m_crColor,$m_strMessage,$m_strButton)
{
        print "
        <title>ERROR</title>
    <table width='100%' height='100%'>
     <tr>
      <td align='center' valign='middle'>
      <table width='410' border='1' bordercolor='".$m_crColor."' cellpadding='10' cellspacing='0'>
       <tr>
        <td align='center'>
        <font face='tahoma' size='2' color='".$m_crColor."'>".$m_strMessage."<p>
        <a href='javascript:history.back();'><font color='".$m_crColor."'>".$m_strButton."</font></a>
        </font>
        </td>
       </tr>
      </table>
      </td>
     </tr>
    </table>
    ";

        exit();
}

function OnNotice2($m_crColor,$m_strMessage,$m_strButton,$m_URL)
{
        print "
        <title>Information</title>
    <table width='100%' height='100%'>
     <tr>
      <td align='center' valign='middle'>
      <table width='410' border='1' bordercolor='".$m_crColor."' cellpadding='10' cellspacing='0'>
       <tr>
        <td align='center'>
        <font face='tahoma' size='2' color='".$m_crColor."'>".$m_strMessage."<p>
        <a href='".$m_URL."'><font color='".$m_crColor."'>".$m_strButton."</font></a>
        </font>
        </td>
       </tr>
      </table>
      </td>
     </tr>
    </table>
    ";

        exit();
}

function OnErrorHandler($m_nCode,$m_nLanguageID)
{
     //   OnNotice("RED",OnGetError($m_nCode,$m_nLanguageID),"Back");
     $rtu=OnGetError($m_nCode,$m_nLanguageID);
     echo "$rtu";
}



function OnGetError($m_nCode,$m_nLanguageID)
{
        // Фатальные ошибки.

        // Ошибки MySQL.
        $m_arrErrorMessages[11][0] = "Невозможно установить соединение с сервером MySQL";
        $m_arrErrorMessages[11][1] = "Couldn't connect to the MySQL server";
        $m_arrErrorMessages[12][0] = "Невозможно открыть базу данных";
        $m_arrErrorMessages[12][1] = "Couldn't open the database";
        $m_arrErrorMessages[13][0] = "Ошибка выполнения SQL команды.<br>".mysql_error();
        $m_arrErrorMessages[13][1] = "Error in the SQL statement's executing<br>".mysql_error();
        $m_arrErrorMessages[14][0] = "Невозможно закрыть соединение с сервером MySQL";
        $m_arrErrorMessages[14][1] = "Couldn't close connection with MySQL server";

        // Ошибки исполнения.
        $m_arrErrorMessages[51][0] = "Некорректный адрес электронной почты";
        $m_arrErrorMessages[51][1] = "Incorrect E-Mail adress";
        $m_arrErrorMessages[52][0] = "Поля со звёздочкой (*) должны быть заполнены";
        $m_arrErrorMessages[52][1] = "Fields with star (*) must be entered";
        $m_arrErrorMessages[53][0] = "Невозможно открыть библиотеку dll_JSAdmin.";
        $m_arrErrorMessages[53][1] = "Couldn't open the library dll_JSAdmin.js";
        $m_arrErrorMessages[54][0] = "Запрошенный файл шаблона не найден";
        $m_arrErrorMessages[54][1] = "Requested template file not found";

        return ($m_arrErrorMessages[$m_nCode][$m_nLanguageID]);
}

?>