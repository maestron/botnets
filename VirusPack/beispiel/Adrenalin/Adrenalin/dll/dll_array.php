<?php
function OnSplitRecords($m_nAllRecords,$m_nRecordsPerPage,$m_nCurrentPage,$m_strHrefString)
{
        $m_nAllPages = intval($m_nAllRecords/$m_nRecordsPerPage)+1;

        if(substr($m_nAllRecords, -1) == 0)
        {
                $m_nAllPages--;
        }

        for($i=1; $i<=$m_nAllPages; $i++)
        {
                $m_nFrom=$i*$m_nRecordsPerPage-$m_nRecordsPerPage;

                if($m_nCurrentPage != $i)
                {
                        $m_strPages .= "| <a href='".$m_strHrefString."&OutputFrom=".$m_nFrom."&CurrentPage=".$i."'>".((($i-1)*$m_nRecordsPerPage)+1)."-".($i*$m_nRecordsPerPage<=$m_nAllRecords?$i*$m_nRecordsPerPage:$m_nAllRecords)."</a>\n";
                }
                else
                {
                        $m_strPages .= "| <b>".((($i-1)*$m_nRecordsPerPage)+1)."-".($i*$m_nRecordsPerPage<=$m_nAllRecords?$i*$m_nRecordsPerPage:$m_nAllRecords)."</b>\n";
                }
        }

        return substr($m_strPages,1,strlen($m_strPages));
}

function OnSplitRecordsListBox($m_nAllRecords,$m_nRecordsPerPage,$m_nCurrentPage,$m_strHrefString)
{
        $m_nAllPages = intval($m_nAllRecords/$m_nRecordsPerPage)+1;

        if(substr($m_nAllRecords, -1) == 0)
        {
                $m_nAllPages--;
        }

        $m_strPages = "<select name='pages' style='width:222px; background-color: #BBBBBB;' onChange=\"location.href=this.value;\">";

        for($i=1; $i<=$m_nAllPages; $i++)
        {
                $m_nFrom=$i*$m_nRecordsPerPage-$m_nRecordsPerPage;

                if($m_nCurrentPage != $i)
                {
                        $m_strPages .= "<option value='".$m_strHrefString."&OutputFrom=".$m_nFrom."&CurrentPage=".$i."'>".((($i-1)*$m_nRecordsPerPage)+1)."-".($i*$m_nRecordsPerPage<=$m_nAllRecords?$i*$m_nRecordsPerPage:$m_nAllRecords)."</option>\n";
                }
                else
                {
                        $m_strPages .= "<option style='background-color:black;color:white;' selected>".((($i-1)*$m_nRecordsPerPage)+1)."-".($i*$m_nRecordsPerPage<=$m_nAllRecords?$i*$m_nRecordsPerPage:$m_nAllRecords)."</option>\n";
                }
        }

        $m_strPages .= "</select>";

        return $m_strPages;
}

function OnBackAndForward($m_nAllRecords,$m_nRecordsPerPage,$m_nCurrentPage,$m_strHrefString)
{
        $m_nAllPages = intval($m_nAllRecords/$m_nRecordsPerPage)+1;

        if(substr($m_nAllRecords, -1) == 0)
        {
                $m_nAllPages--;
        }

        for($i=1; $i<=$m_nAllPages; $i++)
        {
                $m_nFrom=$i*$m_nRecordsPerPage-$m_nRecordsPerPage;

                if($m_nCurrentPage != $i)
                {
                        if($m_nI!="")
                        {
                                $m_strCaption = "Next page";
                        }
                        else
                        {
                                $m_strCaption = "Prev page";
                        }

                        $m_arrPages[$i] = "<a href='".$m_strHrefString."&OutputFrom=".$m_nFrom."&CurrentPage=".$i."'>".$m_strCaption."</a>\n";
                }
                else
                {
                        $m_arrPages[$i] = "<b>".((($i-1)*$m_nRecordsPerPage)+1)."-".($i*$m_nRecordsPerPage<=$m_nAllRecords?$i*$m_nRecordsPerPage:$m_nAllRecords)."</b>\n";
                        $m_nI = $i;
                }
        }

        $m_arrPages[-1] = "<a href='".$m_strHrefString."&OutputFrom=0&CurrentPage=1'>Begin</a>\n";
        $m_arrPages[-2] = "<a href='".$m_strHrefString."&OutputFrom=".$m_nFrom."&CurrentPage=".$m_nAllPages."'>End</a>\n";


        if($m_arrPages[$m_nI-1]=="")
        {
                $m_arrPages[$m_nI-1] = "<font color='#CCCCCC'>Prev page</font>";
        }

        if($m_arrPages[$m_nI+1]=="")
        {
                $m_arrPages[$m_nI+1] = "<font color='#CCCCCC'>Next page</font>";
        }

        return$m_arrPages[-1]." | ".$m_arrPages[$m_nI-1]." | ".$m_arrPages[$m_nI+1]." | ".$m_arrPages[-2];
}



function OnSplitRecordsEx($m_nCurrentPage,$m_nFirstPage,$m_nAllRecords,$m_nLinksOnPage,$m_nRecordsOnPage,$m_nStep,$m_strScriptName)
{
        $m_nLastPage    = (($m_nFirstPage+$m_nLinksOnPage)>ceil($m_nAllRecords/$m_nRecordsOnPage))?ceil($m_nAllRecords/$m_nRecordsOnPage):$m_nFirstPage+$m_nLinksOnPage-1;
        $m_nPrevousPage = (($m_nFirstPage-$m_nStep)>0)?$m_nFirstPage-$m_nStep:1;
        $m_nNextPage    = (($m_nFirstPage+$m_nStep)>=ceil($m_nAllRecords/$m_nRecordsOnPage))?(ceil($m_nAllRecords/$m_nRecordsOnPage)) : $m_nFirstPage+$m_nStep;

        if ($m_nFirstPage > 1)
                $m_strPages="<a href=".$m_strScriptName."?cpage=".$m_nCurrentPage."&fpage=".$m_nPrevousPage.">Назад</a>&nbsp;\r\n";

        for ($i=$m_nFirstPage; $i<=$m_nLastPage; $i++)
        {
                if ($m_nCurrentPage != $i)
                        $m_strPages.="<a href=".$m_strScriptName."?cpage=".$i."&fpage=".$m_nFirstPage.">[".$i."]</a>&nbsp;\r\n";
                else
                        $m_strPages.="[".$m_nCurrentPage."]&nbsp;\r\n";
        }

        if ($m_nLastPage < ceil($m_nAllRecords/$m_nRecordsOnPage))
                $m_strPages.="<a href=".$m_strScriptName."?cpage=".$m_nCurrentPage."&fpage=".$m_nNextPage.">Вперед</a>";

        return $m_strPages;
}

?>