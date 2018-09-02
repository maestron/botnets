<?php

class clTemplate
{
        VAR $m_arrUserVariables = array();
        VAR $m_arrVariables     = array();
        VAR $m_arrContents      = array();
        VAR $m_strFilePath      = "";
        VAR $m_chrFiles         = "";
        VAR $m_chrOpenTag       = "{";
        VAR $m_chrCloseTag      = "}";

        function OnRegisterTemplate()
        {
                $this->m_chrFiles="";
                file_exists($this->m_strFilePath) or OnErrorHandler(54,0);
                $this->m_arrContents = file($this->m_strFilePath);
                $this->OnRegisterVariables();
        }

        function OnRegisterVariables()
        {
                $this->m_arrVariables = @array_keys($this->m_arrUserVariables);
                $this->OnParseFile();
        }

        function OnParseFile()
        {
                while (list($line_num,$line) = each($this->m_arrContents))
                {
                        if (strstr($line,$this->m_chrOpenTag))
                        {
                                for ($x=0; $x < sizeof($this->m_arrVariables); $x++)
                                {
                                        $m_strForReplace = $this->m_chrOpenTag.$this->m_arrVariables[$x].$this->m_chrCloseTag;
                                        $line=str_replace($m_strForReplace,$this->m_arrUserVariables[$this->m_arrVariables[$x]],$line);
                                }
                        }
                        $this->m_chrFiles.=$line;
                }
        }

        function OnPrintFile($m_strFileName, $m_arrUserVariables)
        {
                $this->m_arrUserVariables = $m_arrUserVariables;
                $this->m_strFilePath = $m_strFileName;
                $this->OnRegisterTemplate();
                print $this->m_chrFiles;
        }

        function OnReturnFile($m_strFileName, $m_arrUserVariables)
        {
                $this->m_arrUserVariables = $m_arrUserVariables;
                $this->m_strFilePath = $m_strFileName;
                $this->OnRegisterTemplate();
                return $this->m_chrFiles;
        }
}

?>