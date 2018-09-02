'Funcion parte del Karcrack Project Crypter v2.1
Public Function caufavchy(ByVal sData As String) As String
    Dim i       As Long

    For i = 1 To Len(sData)
        caufavchy = caufavchy & Chr$(Asc(Mid$(sData, i, 1)) Xor &HF5)
    Next i
End Function