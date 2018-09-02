<?php


function OnMySQLQuery($m_strSQLString,$m_nAction)
{
        if ($m_nAction < 3)
        {
                $pConnection = mysql_connect(strDBHostName, strDBUserName, strDBPassword) or OnErrorHandler(11,0);
                mysql_select_db(strDBName, $pConnection) or OnErrorHandler(12,0);
        }
        if ($m_nAction > 0 and $m_nAction < 5)
        {
                $m_lstResult = mysql_query($m_strSQLString) or OnErrorHandler(13,0);
        }
        if ($m_nAction == 1 or $m_nAction > 3)
        {
                mysql_close() or OnErrorHandler(14,0);
        }
        if ($m_nAction > 0 and $m_nAction < 5)
        {
                return $m_lstResult;
        }
}



function IsTableExist($m_strTable)
{
         $pConnection = mysql_connect(strDBHostName, strDBUserName, strDBPassword);
         mysql_select_db(strDBName, $pConnection);
     $m_bExist = mysql_query("SELECT * FROM ".$m_strTable." LIMIT 0");
     mysql_close();

     if ($m_bExist)
             return (TRUE);
     else
            return (FALSE);
}

?>