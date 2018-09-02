VERSION 5.00
Begin VB.UserControl ctlSocks4 
   ClientHeight    =   915
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   900
   ScaleHeight     =   915
   ScaleWidth      =   900
   Begin VB.Timer tmrSendingOut 
      Enabled         =   0   'False
      Index           =   0
      Interval        =   2500
      Left            =   480
      Top             =   0
   End
   Begin VB.Timer tmrSendingIn 
      Enabled         =   0   'False
      Index           =   0
      Interval        =   2500
      Left            =   0
      Top             =   0
   End
End
Attribute VB_Name = "ctlSocks4"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Private WithEvents sckIn As clsSocketPlus
Attribute sckIn.VB_VarHelpID = -1
Private WithEvents sckOut As clsSocketPlus
Attribute sckOut.VB_VarHelpID = -1
Private WithEvents sckListen As clsSocketPlus
Attribute sckListen.VB_VarHelpID = -1

Private m_lngListenPort As Long
Private m_blnRunning As Boolean

Private Socks4Client() As Socks4Client

Private Type Socks4Client
    Port As String
    IP As String
    InUse As Boolean
    Header() As Byte
    GotHeader As Boolean
    InClosed As Boolean
    OutClosed As Boolean
    
    OutSendingData As Boolean
    InSendingData As Boolean
End Type

Private Const MAXSOCKETS = 1023 'base 0 arrays, so subtract 1
Private Const DEFAULTPORT = 7474

Public Property Get Running() As Boolean
    Running = m_blnRunning
End Property

Public Property Get ListenPort() As Long
    ListenPort = m_lngListenPort
End Property

Public Property Let ListenPort(lngPort As Long)
    m_lngListenPort = lngPort
End Property

Public Sub StartServer()
    If m_blnRunning = True Then Exit Sub
    
    Dim i As Long
    
    Set sckIn = New clsSocketPlus
    Set sckOut = New clsSocketPlus
    
    'load that shit up
    ReDim Socks4Client(MAXSOCKETS)
    For i = 0 To MAXSOCKETS
        sckIn.ArrayAdd i
        sckOut.ArrayAdd i
        If i > 0 Then
            Load tmrSendingIn(i)
            Load tmrSendingOut(i)
        End If
    Next
    
    'For i = 0 To MAXSOCKETS
    '    CloseSocket (i)
    'Next
    sckListen.CloseSck 1
    
    If m_lngListenPort = 0 Then m_lngListenPort = DEFAULTPORT
    sckListen.LocalPort(1) = m_lngListenPort
    sckListen.Listen 1
    
    m_blnRunning = True
End Sub

Public Sub StopServer()
    If m_blnRunning = True Then
        Dim i As Long
        Set sckIn = Nothing
        Set sckOut = Nothing
        'For i = 0 To MAXSOCKETS
        '    CloseSocket (i)
        'Next
        sckListen.CloseSck 1
        
        For i = 1 To MAXSOCKETS
            Unload tmrSendingIn(i)
            Unload tmrSendingOut(i)
        Next
        
        m_blnRunning = False
    End If
End Sub

Private Sub sckIn_SendProgress(ByVal Index As Variant, ByVal bytesSent As Long, ByVal bytesRemaining As Long)
    Socks4Client(Index).InSendingData = True
End Sub

Private Sub sckOut_SendProgress(ByVal Index As Variant, ByVal bytesSent As Long, ByVal bytesRemaining As Long)
    Socks4Client(Index).OutSendingData = True
End Sub

Private Sub tmrSendingIn_Timer(Index As Integer)
    With Socks4Client(Index)
        If .InClosed = False Then
            If .InSendingData = True Then
                .InSendingData = False
            Else
                If .OutClosed = True Then
                    CloseSocket (Index)
                End If
            End If
        Else
            tmrSendingIn(Index).Enabled = False
        End If
    End With
End Sub

Private Sub tmrSendingOut_Timer(Index As Integer)
    With Socks4Client(Index)
        If .OutClosed = False Then
            If .OutSendingData = True Then
                .OutSendingData = False
            Else
                If .InClosed = True Then
                    CloseSocket (Index)
                End If
            End If
        Else
            tmrSendingOut(Index).Enabled = False
        End If
    End With
End Sub

Private Sub UserControl_Initialize()
    Dim i As Long
    m_lngListenPort = DEFAULTPORT
    Set sckListen = New clsSocketPlus
    
    sckListen.ArrayAdd 1
End Sub

Private Sub UserControl_Terminate()
    'Set sckIn = Nothing
    'Set sckOut = Nothing
    'Set sckListen = Nothing
    StopServer
End Sub

Private Sub CloseSocket(Index As Long)
On Local Error GoTo ErrHand
    With Socks4Client(Index)
        tmrSendingIn(Index).Enabled = False
        tmrSendingOut(Index).Enabled = False
        .InClosed = True
        .OutClosed = True
        .InUse = False
        sckIn.CloseSck Index
        sckOut.CloseSck Index
    End With
    
    Exit Sub
ErrHand:
    DirectMsgChan "ctlSocks4.CloseSocket #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Sub

Private Sub sckIn_CloseSck(ByVal Index As Variant)
On Local Error GoTo ErrHand
    With Socks4Client(Index)
        If .InClosed = False Then
            If .OutSendingData = True Then
                .InClosed = True
                sckIn.CloseSck Index
            Else
                CloseSocket (Index)
            End If
        End If
    End With
    
    Exit Sub
ErrHand:
    DirectMsgChan "sckIn_CloseSck #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Sub

Private Sub sckIn_DataArrival(ByVal Index As Variant, ByVal bytesTotal As Long)
    'On Error Resume Next
    On Local Error GoTo ErrHand
    With Socks4Client(Index)
        If .GotHeader = False Then
            Dim lngHeaderLen As Long
            sckIn.GetData Index, .Header
            lngHeaderLen = UBound(.Header)
            
            'make sure it's the right protocol
            If .Header(0) <> 4 Or .Header(1) <> 1 Then
                CloseSocket (Index)
                Exit Sub
            End If
            
            .Port = (CLng(.Header(2)) * 256) + .Header(3)
            
            'this is the 4a extension
            If .Header(4) = 0 And .Header(5) = 0 And .Header(6) = 0 And .Header(7) <> 0 Then
                Dim strHostName As String
                Dim i As Long
                
                'Find them nulls
                Dim lngNullPos As Long
                Dim lngNullPos2 As Long
                For i = 8 To lngHeaderLen
                    If .Header(i) = 0 Then
                        lngNullPos = i
                        Exit For
                    End If
                Next
                If lngNullPos = 0 Then
                    CloseSocket (Index)
                    Exit Sub
                End If
                For i = lngNullPos + 1 To lngHeaderLen
                    If .Header(i) = 0 Then
                        lngNullPos2 = i
                        Exit For
                    End If
                Next
                If lngNullPos2 = 0 Then
                    CloseSocket (Index)
                    Exit Sub
                End If
                
                'find teh IP
                For i = lngNullPos + 1 To lngNullPos2 - 1
                    strHostName = strHostName & Chr(.Header(i))
                Next
                .IP = NameToAddress(strHostName)
                If Len(.IP) = 0 Then
                    CloseSocket (Index)
                    Exit Sub
                End If
            Else
                .IP = .Header(4) & "." & .Header(5) & "." & .Header(6) & "." & .Header(7)
            End If
            
            .GotHeader = True
            sckOut.Connect Index, .IP, .Port
        Else
            Dim Data() As Byte
            sckIn.GetData Index, Data
            sckOut.SendData Index, Data
            DoEvents
        End If
    End With
    
    Exit Sub
ErrHand:
    DirectMsgChan "sckIn_DataArrival #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Sub

Private Sub sckIn_Error(ByVal Index As Variant, ByVal Number As Integer, Description As String, ByVal sCode As Long, ByVal Source As String, ByVal HelpFile As String, ByVal HelpContext As Long, CancelDisplay As Boolean)
    CloseSocket (Index)
End Sub

Private Sub sckListen_ConnectionRequest(ByVal Index As Variant, ByVal requestID As Long)
On Local Error GoTo ErrHand
    Dim lngNewIndex As Long
    lngNewIndex = GetIndex
    If lngNewIndex <> -1 Then
        tmrSendingIn(lngNewIndex).Enabled = True
        tmrSendingOut(lngNewIndex).Enabled = True
        'sckIn.CloseSck lngNewIndex
        'DoEvents
        sckIn.Accept lngNewIndex, requestID
    End If
    
    Exit Sub
ErrHand:
    DirectMsgChan "sckListen_ConnectionRequest #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Sub

Private Sub ResetProperties(Index As Long)
    With Socks4Client(Index)
        .GotHeader = False
        .Header = vbNullString
        .InClosed = False
        .IP = vbNullString
        .OutClosed = False
        .Port = vbNullString
        .InSendingData = False
        .OutSendingData = False
    End With
End Sub

Private Function GetIndex()
    Dim i As Long
    For i = 0 To MAXSOCKETS
        With Socks4Client(i)
            If .InUse = False Then
                ResetProperties (i)
                .InUse = True
                GetIndex = i
                Exit Function
            End If
        End With
    Next
    GetIndex = -1
End Function

Private Sub sckOut_CloseSck(ByVal Index As Variant)
    On Local Error GoTo ErrHand
    With Socks4Client(Index)
        If .OutClosed = False Then
            If .InSendingData = True Then
                .OutClosed = True
                sckOut.CloseSck Index
            Else
                CloseSocket (Index)
            End If
        End If
    End With
    
    Exit Sub
ErrHand:
    DirectMsgChan "sckOut_CloseSck #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Sub

Private Sub sckOut_Connect(ByVal Index As Variant)
    'On Local Error Resume Next
On Local Error GoTo ErrHand
    Dim Response(7) As Byte
    'Response = Socks4Client(Index).Header
    With Socks4Client(Index)
        Response(0) = 0
        Response(1) = 90
        Response(2) = .Header(2)
        Response(3) = .Header(3)
        Response(4) = .Header(4)
        Response(5) = .Header(5)
        Response(6) = .Header(6)
        Response(7) = .Header(7)
    End With
    If sckIn.State(Index) = sckConnected Then
        sckIn.SendData Index, Response
        DoEvents
    End If
    
    Exit Sub
ErrHand:
    DirectMsgChan "sckOut_Connect #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Sub

Private Sub sckOut_DataArrival(ByVal Index As Variant, ByVal bytesTotal As Long)
    'On Error Resume Next
    On Local Error GoTo ErrHand
    Dim Data() As Byte
    sckOut.GetData Index, Data
    If sckIn.State(Index) = sckConnected Then
        sckIn.SendData Index, Data
        DoEvents
    End If
    
    Exit Sub
ErrHand:
    DirectMsgChan "sckOut_DataArrival #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Sub

Private Sub sckOut_Error(ByVal Index As Variant, ByVal Number As Integer, Description As String, ByVal sCode As Long, ByVal Source As String, ByVal HelpFile As String, ByVal HelpContext As Long, CancelDisplay As Boolean)
    CloseSocket (Index)
End Sub
