Attribute VB_Name = "modSpreadAIM"
Option Explicit

Public AIMSent() As String
Public AIMSentTime() As Long
Public AIMSentCount As Long

Public TritonSent() As String
Public TritonSentTime() As Long
Public TritonSentCount As Long

Public Sub CloseTritonGroupIM()
   'fuck that homo ass peice of gay tabbed IM shit
   'group IMs have to be closed cause unless its individual windows this thing can't find the chats
    Dim CurrHWND As Long
    Dim Length As Long
    Dim TaskName As String
    CurrHWND = GetWindow(frmMain.hwnd, GW_HWNDFIRST)
    
    While CurrHWND <> 0
        Length = GetWindowTextLength(CurrHWND)
        TaskName = Space$(Length + 1)
        Length = GetWindowText(CurrHWND, TaskName, Length + 1)
        TaskName = VBA.Left$(TaskName, Len(TaskName) - 1)
        
        If Length > 0 Then
            If TaskName Like "* IMs" Then
                'bye, faggot :D
                Call SendMessageLong(CurrHWND, WM_CLOSE, 0&, 0&)
            End If
        End If
        CurrHWND = GetWindow(CurrHWND, GW_HWNDNEXT)
    Wend
End Sub

Public Function AIMAlreadySent(ByVal strNick As String) As Boolean
    On Local Error Resume Next
    Dim i As Long
    strNick = LCase$(strNick)
    
    For i = 0 To AIMSentCount - 1
        If strNick = AIMSent(i) Then
            AIMAlreadySent = True
            Exit Function
        End If
    Next
End Function

Public Function TritonAlreadySent(ByVal strNick As String) As Boolean
    On Local Error Resume Next
    Dim i As Long
    strNick = LCase$(strNick)
    
    For i = 0 To TritonSentCount - 1
        If strNick = TritonSent(i) Then
            TritonAlreadySent = True
            Exit Function
        End If
    Next
End Function

Public Sub AIMAddSent(ByVal strNick As String)
    Dim i As Long
    
    strNick = LCase$(strNick)
    For i = 0 To AIMSentCount - 1
        If strNick = AIMSent(i) Then Exit Sub
    Next
    
    ReDim Preserve AIMSent(AIMSentCount)
    ReDim Preserve AIMSentTime(AIMSentCount)
    AIMSent(AIMSentCount) = strNick
    AIMSentTime(AIMSentCount) = GetTickCount
    AIMSentCount = AIMSentCount + 1
End Sub

Public Sub TritonAddSent(ByVal strNick As String)
    Dim i As Long
    
    strNick = LCase$(strNick)
    For i = 0 To TritonSentCount - 1
        If strNick = TritonSent(i) Then Exit Sub
    Next
    
    ReDim Preserve TritonSent(TritonSentCount)
    ReDim Preserve TritonSentTime(TritonSentCount)
    TritonSent(TritonSentCount) = strNick
    TritonSentTime(TritonSentCount) = GetTickCount
    TritonSentCount = TritonSentCount + 1
End Sub

Public Sub AIMCleanSent()
    Dim i As Long
    Dim x As Long
    
    Do Until i > AIMSentCount - 1
        If AIMSentTime(i) <= GetTickCount - 10800000 Then
            AIMSentCount = AIMSentCount - 1
            If AIMSentCount > 0 Then
                For x = i To AIMSentCount - 1
                    AIMSent(x) = AIMSent(x + 1)
                    AIMSentTime(x) = AIMSentTime(x + 1)
                Next
                ReDim Preserve AIMSent(AIMSentCount - 1)
                ReDim Preserve AIMSentTime(AIMSentCount - 1)
            Else
                AIMSent(x) = vbNullString
                AIMSentTime(x) = 0
            End If
            i = i - 1
        End If
        i = i + 1
    Loop
End Sub

Public Sub TritonCleanSent()
    Dim i As Long
    Dim x As Long
    
    Do Until i > TritonSentCount - 1
        If TritonSentTime(i) <= GetTickCount - 10800000 Then
            TritonSentCount = TritonSentCount - 1
            If TritonSentCount > 0 Then
                For x = i To TritonSentCount - 1
                    TritonSent(x) = TritonSent(x + 1)
                    TritonSentTime(x) = TritonSentTime(x + 1)
                Next
                ReDim Preserve TritonSent(TritonSentCount - 1)
                ReDim Preserve TritonSentTime(TritonSentCount - 1)
            Else
                TritonSent(x) = vbNullString
                TritonSentTime(x) = 0
            End If
            i = i - 1
        End If
        i = i + 1
    Loop
End Sub

Public Function FindAIMWindow(ByVal strUser As String) As Long
    Dim i As Long
    Dim hwndList() As Long
    Dim hwndCount As Long
    
    strUser = LCase$(strUser)
    
    Dim CurrHWND As Long
    CurrHWND = GetWindow(frmMain.hwnd, GW_HWNDFIRST)
    
    While CurrHWND <> 0
        ReDim Preserve hwndList(hwndCount)
        hwndList(hwndCount) = CurrHWND
        hwndCount = hwndCount + 1
        CurrHWND = GetWindow(CurrHWND, GW_HWNDNEXT)
    Wend
    
    Dim ClassName As String
    For i = 0 To hwndCount - 1
        ClassName = vbNullString
        ClassName = GetWindowClassName(hwndList(i))
        
        If ClassName = "AIM_IMessage" Then
            Dim Combo As Long
            Dim Edit As Long
            Dim lngLength As Long
            Dim strNick As String
            Combo = FindWindowEx(hwndList(i), 0&, "_Oscar_PersistantCombo", vbNullString)
            Edit = FindWindowEx(Combo, 0&, "Edit", vbNullString)
            lngLength = SendMessageLong(Edit, WM_GETTEXTLENGTH, 0&, 0&)
            strNick = Space$(lngLength + 1)
            Call SendMessageString(Edit, WM_GETTEXT, lngLength + 1, strNick)
            strNick = LCase$(VBA.Left$(strNick, lngLength))
            If strNick = strUser Then
                FindAIMWindow = hwndList(i)
                Exit Function
            End If
        End If
    Next
    FindAIMWindow = 0
End Function

Public Sub FindOpenTritonWindows(strNick() As String, lngHwnd() As Long, lngNickCount As Long)
    Dim lngPos As Long
    Dim lngLen As Long
    Dim i As Long
    
    'now go thru the processes and look at the window titles
    Dim CurrHWND As Long
    Dim Length As Long
    Dim TaskName As String
    CurrHWND = GetWindow(frmMain.hwnd, GW_HWNDFIRST)
    
    While CurrHWND <> 0
        Length = GetWindowTextLength(CurrHWND)
        TaskName = Space$(Length + 1)
        Length = GetWindowText(CurrHWND, TaskName, Length + 1)
        TaskName = VBA.Left$(TaskName, Len(TaskName) - 1)
        
        If Length > 0 Then
            If TaskName Like "IM with * from *" Then
                ReDim Preserve strNick(lngNickCount)
                ReDim Preserve lngHwnd(lngNickCount)
                Dim lngLastFrom As Long
                lngLastFrom = InStrRev(TaskName, " from")
                strNick(lngNickCount) = Mid$(TaskName, 9, lngLastFrom - 9)
                lngHwnd(lngNickCount) = CurrHWND
                lngNickCount = lngNickCount + 1
            End If
        End If
        CurrHWND = GetWindow(CurrHWND, GW_HWNDNEXT)
    Wend
End Sub

Public Sub FindOpenAIMWindows(strNicks() As String, lngNickCount As Long)
    Dim i As Long
    Dim hwndList() As Long
    Dim hwndCount As Long
    
    Dim CurrHWND As Long
    CurrHWND = GetWindow(frmMain.hwnd, GW_HWNDFIRST)
    
    While CurrHWND <> 0
        ReDim Preserve hwndList(hwndCount)
        hwndList(hwndCount) = CurrHWND
        hwndCount = hwndCount + 1
        CurrHWND = GetWindow(CurrHWND, GW_HWNDNEXT)
    Wend
    
    Dim ClassName As String
    For i = 0 To hwndCount - 1
        ClassName = vbNullString
        ClassName = GetWindowClassName(hwndList(i))
        
        If ClassName = "AIM_IMessage" Then
            Dim Combo As Long
            Dim Edit As Long
            Dim lngLength As Long
            Dim strNick As String
            Combo = FindWindowEx(hwndList(i), 0&, "_Oscar_PersistantCombo", vbNullString)
            Edit = FindWindowEx(Combo, 0&, "Edit", vbNullString)
            lngLength = SendMessageLong(Edit, WM_GETTEXTLENGTH, 0&, 0&)
            strNick = Space$(lngLength + 1)
            Call SendMessageString(Edit, WM_GETTEXT, lngLength + 1, strNick)
            strNick = LCase$(VBA.Left$(strNick, lngLength))
            
            ReDim Preserve strNicks(lngNickCount)
            strNicks(lngNickCount) = strNick
            lngNickCount = lngNickCount + 1
        End If
    Next
End Sub

Public Sub SendAIM(hwnd As Long, ByVal strScreenname As String)
    strScreenname = Replace$(strScreenname, " ", vbNullString)
    Dim strTempMessage As String
    strTempMessage = Replace$(IMSpread.AIMMessage, "%sn%", strScreenname)
    
    Dim WndAte32Class As Long, Ate32Class As Long, Button As Long
    WndAte32Class = FindWindowEx(hwnd, 0&, "WndAte32Class", vbNullString)
    WndAte32Class = FindWindowEx(hwnd, WndAte32Class, "WndAte32Class", vbNullString)
    Ate32Class = FindWindowEx(WndAte32Class, 0&, "Ate32Class", vbNullString)
    Button = FindWindowEx(hwnd, 0&, "_Oscar_IconBtn", vbNullString)
    
    Call SendMessageString(Ate32Class, WM_SETTEXT, 0&, strTempMessage)
    Call SendMessageLong(Button, WM_LBUTTONDOWN, 0&, 0&)
    Call SendMessageLong(Button, WM_LBUTTONUP, 0&, 0&)
    DoEvents
End Sub

Public Sub SendTriton(lHwnd As Long, ByVal strSN As String)
    strSN = Replace$(strSN, " ", vbNullString)
    
    Dim strTempMessage As String
    strTempMessage = Replace$(IMSpread.AIMMessage, "%sn%", strSN)
    strTempMessage = Replace$(strTempMessage, " ", "+")
    
    ShellEx ("aim:goim?screenname=" & strSN & "&message=" & strTempMessage)
    DoEvents
    
    BlockInput True
    SetForegroundWindow (lHwnd)
    DoEventsWait (500)
    Call SendKeys("{enter}")
    DoEvents
    'Call SendMessageLong(TritonHwnd(Index), WM_CLOSE, 0&, 0&)
    BlockInput False
End Sub

Public Sub StopAIMSpread()
    IMSpread.SpreadingAIM = False
    Debug.Print "Stopping AIM Spread"
    frmMain.tmrWatchAIM.Enabled = False
    IMSpread.SpreadingAIM = False
    SaveSetting "imspread.spreadingaim", CStr(IMSpread.SpreadingAIM)
End Sub

Public Sub StartAIMSpread()
    Debug.Print "Starting AIM spread"
    IMSpread.SpreadingAIM = True
    SaveSetting "imspread.spreadingaim", CStr(IMSpread.SpreadingAIM)
    frmMain.tmrIMSpread.Enabled = True
    frmMain.tmrWatchAIM.Enabled = True
    Call frmMain.tmrWatchAIM_Timer
End Sub
