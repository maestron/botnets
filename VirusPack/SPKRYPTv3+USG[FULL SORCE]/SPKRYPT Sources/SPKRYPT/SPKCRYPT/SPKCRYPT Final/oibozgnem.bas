'Funcion parte del Karcrack Project Crypter v2.1
Public Function rpkuplrwo(ByVal sData As String) As String
    Dim i       As Long
    For i = 1 To Len(sData) Step 2
       rpkuplrwo = rpkuplrwo & Chr$(Val("&H" & Mid$(sData, i, 2)))
    Next i
End Function