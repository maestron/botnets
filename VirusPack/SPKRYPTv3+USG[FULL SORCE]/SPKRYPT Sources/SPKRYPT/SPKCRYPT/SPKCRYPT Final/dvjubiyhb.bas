Attribute VB_Name = "dvjubiyhb"

Public Function mkfpkgmrj(ByVal sData As String) As String
    Dim i       As Long

    For i = 1 To Len(sData)
        mkfpkgmrj = mkfpkgmrj & Chr$(Asc(Mid$(sData, i, 1)) Xor &H5B)
    Next i
End Function
