<?php


function OnUploadFile($m_strToFolder,$pTemporaryFile,$pFile,$m_arrExtension)
{
        $m_arrFile          = explode(".", strtolower($pFile));
        $m_arrExtensionEx   = explode("|", $m_arrExtension);
        $m_nArrayLength     = count($m_arrFile);
        $m_strUserExtension = trim($m_arrFile[$m_nArrayLength-1]);

        foreach ($m_arrExtensionEx as $m_strGrantedExtension)
        {
                if(trim($m_strGrantedExtension) == $m_strUserExtension)
                {
                        $m_bFlag = 1;
                        break;
                }
                else
                        $m_bFlag = 0;
        }

        if($m_arrExtension=="ALL")
                $m_bFlag = 1;

        if($m_bFlag == 1)
        {
                if(move_uploaded_file($pTemporaryFile, $m_strToFolder.$pFile))
                        return (TRUE);
                else
                        return (FALSE);
        }
        else
                return (FALSE);
}

function OnGetFileSource($m_strPath)
{
        $m_arrFile  = file($m_strPath);
        $m_strSource ="";

        for($i=0;$i<count($m_arrFile);$i++)
        {
                $m_strSource .= $m_arrFile[$i];
        }

        return $m_strSource;
}

?>