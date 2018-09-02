<?php



class cl_Zip
{
        var $m_arrCompressedData   = array();
        var $m_arrCentralFolder    = array();
        var $m_strEofCentralFolder = "\x50\x4b\x05\x06\x00\x00\x00\x00";
        var $m_nOldOffsett = 0;

        function OnAddFolder($m_strName)
        {
                $m_strName = str_replace("\\", "/", $m_strName);

                $m_strCompressedData  = "\x50\x4b\x03\x04";
                $m_strCompressedData .= "\x0a\x00";
                $m_strCompressedData .= "\x00\x00";
                $m_strCompressedData .= "\x00\x00";
                $m_strCompressedData .= "\x00\x00\x00\x00";

                $m_strCompressedData .= pack("V",0);
                $m_strCompressedData .= pack("V",0);
                $m_strCompressedData .= pack("V",0);
                $m_strCompressedData .= pack("v", strlen($m_strName) );
                $m_strCompressedData .= pack("v", 0 );
                $m_strCompressedData .= $m_strName;

                $m_strCompressedData .= pack("V",$m_strCRC);
                $m_strCompressedData .= pack("V",$m_nCompressedFileLength);
                $m_strCompressedData .= pack("V",$m_nFileLength);

                $this -> m_arrCompressedData[] = $m_strCompressedData;

                $m_nNewOffset = strlen(implode("", $this->m_arrCompressedData));

                $m_strCentralFolder  = "\x50\x4b\x01\x02";
                $m_strCentralFolder .="\x00\x00";
                $m_strCentralFolder .="\x0a\x00";
                $m_strCentralFolder .="\x00\x00";
                $m_strCentralFolder .="\x00\x00";
                $m_strCentralFolder .="\x00\x00\x00\x00";
                $m_strCentralFolder .= pack("V",0);
                $m_strCentralFolder .= pack("V",0);
                $m_strCentralFolder .= pack("V",0);
                $m_strCentralFolder .= pack("v", strlen($m_strName) );
                $m_strCentralFolder .= pack("v", 0 );
                $m_strCentralFolder .= pack("v", 0 );
                $m_strCentralFolder .= pack("v", 0 );
                $m_strCentralFolder .= pack("v", 0 );
                $m_strExternalInfo   = "\x00\x00\x10\x00";
                $m_strExternalInfo   = "\xff\xff\xff\xff";
                $m_strCentralFolder .= pack("V", 16 );

                $m_strCentralFolder .= pack("V", $this -> m_nOldOffsett );
                $this -> m_nOldOffsett = $m_nNewOffset;

                $m_strCentralFolder .= $m_strName;

                $this -> m_arrCentralFolder[] = $m_strCentralFolder;

        }

        function OnAddFile($m_strData, $m_strName)
        {
                $m_strName = str_replace("\\", "/", $m_strName);

                $m_strCompressedFile     = "\x50\x4b\x03\x04";
                $m_strCompressedFile    .= "\x14\x00";
                $m_strCompressedFile    .= "\x00\x00";
                $m_strCompressedFile    .= "\x08\x00";
                $m_strCompressedFile    .= "\x00\x00\x00\x00";

                $m_nFileLength           = strlen($m_strData);
                $m_strCRC                = crc32($m_strData);
                $m_strCompressedCRC      = gzcompress($m_strData);
                $m_strCompressedCRC      = substr( substr($m_strCompressedCRC, 0, strlen($m_strCompressedCRC) - 4), 2); // fix crc bug
                $m_nCompressedFileLength = strlen($m_strCompressedCRC);
                $m_strCompressedFile    .= pack("V",$m_strCRC);
                $m_strCompressedFile    .= pack("V",$m_nCompressedFileLength);
                $m_strCompressedFile    .= pack("V",$m_nFileLength);
                $m_strCompressedFile    .= pack("v", strlen($m_strName));
                $m_strCompressedFile    .= pack("v", 0 );
                $m_strCompressedFile    .= $m_strName;

                $m_strCompressedFile .= $m_strCompressedCRC;

                $m_strCompressedFile .= pack("V",$m_strCRC);
                $m_strCompressedFile .= pack("V",$m_nCompressedFileLength);
                $m_strCompressedFile .= pack("V",$m_nFileLength);

                $this -> m_arrCompressedData[] = $m_strCompressedFile;

                $m_nNewOffset = strlen(implode("", $this->m_arrCompressedData));

                $m_strCentralFolder  = "\x50\x4b\x01\x02";
                $m_strCentralFolder .="\x00\x00";
                $m_strCentralFolder .="\x14\x00";
                $m_strCentralFolder .="\x00\x00";
                $m_strCentralFolder .="\x08\x00";
                $m_strCentralFolder .="\x00\x00\x00\x00";
                $m_strCentralFolder .= pack("V",$m_strCRC);
                $m_strCentralFolder .= pack("V",$m_nCompressedFileLength);
                $m_strCentralFolder .= pack("V",$m_nFileLength);
                $m_strCentralFolder .= pack("v", strlen($m_strName) );
                $m_strCentralFolder .= pack("v", 0 );
                $m_strCentralFolder .= pack("v", 0 );
                $m_strCentralFolder .= pack("v", 0 );
                $m_strCentralFolder .= pack("v", 0 );
                $m_strCentralFolder .= pack("V", 32 );
                $m_strCentralFolder .= pack("V", $this -> m_nOldOffsett );

                $this -> m_nOldOffsett = $m_nNewOffset;
                $m_strCentralFolder   .= $m_strName;

                $this -> m_arrCentralFolder[] = $m_strCentralFolder;
        }

        function OnDumpFileOut()
        {
                $m_strData = implode("", $this -> m_arrCompressedData);
                $m_strCentralFolder = implode("", $this -> m_arrCentralFolder);

                return $m_strData.$m_strCentralFolder.$this -> m_strEofCentralFolder.
                       pack("v", sizeof($this -> m_arrCentralFolder)).
                       pack("v", sizeof($this -> m_arrCentralFolder)).
                       pack("V", strlen($m_strCentralFolder)).
                       pack("V", strlen($m_strData))."\x00\x00";
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
}

?>
