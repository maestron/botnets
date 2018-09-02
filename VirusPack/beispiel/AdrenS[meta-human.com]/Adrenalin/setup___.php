<?php

set_time_limit(0);
error_reporting(0);
session_start();

include("dll/dll_Set.php");
include("dll/dll_MySQL.php");
include("dll/dll_Handle.php");

OnSettings($_REQUEST["do"]);

function OnSettings($m_nDo)
{
        if($m_nDo==1)
        {
                $pConfig = fopen("dll/dll_Set.php", "w");
                fwrite($pConfig,"<?php\n");
                fwrite($pConfig,"define(\"strDBHostName\", \"".$_REQUEST["mysqlServer"]."\");\n");
                fwrite($pConfig,"define(\"strDBUserName\", \"".$_REQUEST["mysqlUser"]."\");\n");
                fwrite($pConfig,"define(\"strDBPassword\", \"".$_REQUEST["mysqlPassword"]."\");\n");
                fwrite($pConfig,"define(\"strDBName\", \"".$_REQUEST["mysqlDatabase"]."\");\n");
                fwrite($pConfig,"?>\n");
                fclose($pConfig);

                include("dll/dll_Page.php");
                
                $m_lstUser = OnMySQLQuery("SELECT strUsername, strPassword  FROM tbl_users WHERE ID='1'",1);
                $m_arrUser = mysql_fetch_array($m_lstUser);
                
                $m_arrVariables["strFirstUser"]     = $m_arrUser["strUsername"]."";
                $m_arrVariables["strFisrtPassword"] = $m_arrUser["strPassword"]."";
                
   if($m_arrVariables["strFirstUser"]==""):             

OnMySQLQuery("INSERT INTO tbl_users (strUsername,strPassword) VALUES('".addslashes($_REQUEST["firstUser"])."','".addslashes($_REQUEST["firstPassword"])."' )",1);
   
   else:     
OnMySQLQuery("UPDATE tbl_users SET strUsername='".$_REQUEST["firstUser"]."', strPassword='".$_REQUEST["firstPassword"]."' WHERE ID='1'",1);
   endif;
                header("Location: setup.php");
                die();
        }

        include("dll/dll_Page.php");

        global $m_arrVariables;

        $m_arrVariables["m_nYear"]    = date("Y");
        $m_arrVariables["m_nMonth"]   = date("m")-1;
        $m_arrVariables["m_nDay"]     = date("d");
        $m_arrVariables["m_nHours"]   = date("H");
        $m_arrVariables["m_nMinutes"] = date("i");
        $m_arrVariables["m_nSeconds"] = date("s");
        $m_arrVariables["strSection"] = "Settings";

        $m_arrVariables["strServer"]   = strDBHostName."";
        $m_arrVariables["strUser"]     = strDBUserName."";
        $m_arrVariables["strPassword"] = strDBPassword."";
        $m_arrVariables["strDatabase"] = strDBName."";

        if(!IsTableExist("tbl_users"))
        {
                $m_arrVariables["strFisrtUser"]     = "";
                $m_arrVariables["strFisrtPassword"] = "";
                $m_arrVariables["strFisrtUIN"] = "";
        }
        else
        {
                $m_lstUser = OnMySQLQuery("SELECT strUsername, strPassword  FROM tbl_users WHERE ID='1'",1);
                $m_arrUser = mysql_fetch_array($m_lstUser);
                
                $m_arrVariables["strFirstUser"]     = $m_arrUser["strUsername"]."";
                $m_arrVariables["strFisrtPassword"] = $m_arrUser["strPassword"]."";
        }

        $pVariablesTemplate = new clTemplate;

        $pVariablesTemplate->OnPrintFile("templates/snpSettings.tpl",$m_arrVariables);
}



?>



