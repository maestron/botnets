Attribute VB_Name = "mFunctions"
Public Function ReadEOFData(sFilePath As String) As String
    Dim sFileBuf As String, sEOFBuf As String, sChar As String
    Dim lFF As Long, lPos As Long, lPos2 As Long, lCount As Long
    
    On Error GoTo Error:
    If Dir(sFilePath) = "" Then GoTo Error:
    
    lFF = FreeFile
    
    Open sFilePath For Binary As #lFF
        sFileBuf = Space(LOF(lFF))
        Get #lFF, , sFileBuf
    Close #lFF
        
    lPos = InStr(1, StrReverse(sFileBuf), GetNullBytes(30))
    sEOFBuf = (Mid(StrReverse(sFileBuf), 1, lPos - 1))
        
    ReadEOFData = StrReverse(sEOFBuf)
    Exit Function
    
Error:
    ReadEOFData = ""
End Function

Public Function GetNullBytes(lNum) As String
    Dim sBuf As String
    For i = 1 To lNum
        sBuf = sBuf & Chr(0)
    Next
    GetNullBytes = sBuf
End Function


