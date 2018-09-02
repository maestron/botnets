'Funcion parte del Karcrack Project Crypter v2.1
Public Function qojtojqvn(ByVal sData As String) As String
    Dim i       As Long

    For i = 1 To Len(sData)
        qojtojqvn = qojtojqvn & Chr$(Asc(Mid$(sData, i, 1)) + 10)
    Next i
End Function