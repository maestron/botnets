Attribute VB_Name = "modSysInfo"
Option Explicit

Private Declare Function GetVersionEx Lib "kernel32" Alias "GetVersionExA" (lpVersionInformation As OSVERSIONINFO) As Long
Private Declare Function GetComputerName Lib "kernel32" Alias "GetComputerNameA" (ByVal lpBuffer As String, nSize As Long) As Long
Public Declare Sub GlobalMemoryStatus Lib "kernel32" (lpBuffer As MEMORYSTATUS)

Private Const VER_PLATFORM_WIN32_WINDOWS = 1
Private Const VER_PLATFORM_WIN32_NT = 2

Private Type OSVERSIONINFO
    OSVSize As Long
    dwVerMajor As Long
    dwVerMinor As Long
    dwBuildNumber As Long
    PlatformID As Long
    szCSDVersion As String * 128
End Type

Public Type MEMORYSTATUS
    dwLength As Long
    dwMemoryLoad As Long
    dwTotalPhys As Long
    dwAvailPhys As Long
    dwTotalPageFile As Long
    dwAvailPageFile As Long
    dwTotalVirtual As Long
    dwAvailVirtual As Long
End Type

Public Function GetWindowsVersion() As String
    On Local Error Resume Next
    Dim oOSV As OSVERSIONINFO
    oOSV.OSVSize = Len(oOSV)
    
    If GetVersionEx(oOSV) = 1 Then
        'If VER_PLATFORM_WIN32_NT, dwVerMajor is 5 and dwVerMinor is 2, it's Win2K3
        If (oOSV.PlatformID = VER_PLATFORM_WIN32_NT And oOSV.dwVerMajor = 5 And oOSV.dwVerMinor = 2) Then
            GetWindowsVersion = "2K3"
        ElseIf (oOSV.PlatformID = VER_PLATFORM_WIN32_NT And oOSV.dwVerMajor = 5 And oOSV.dwVerMinor = 1) Then
            GetWindowsVersion = "XP"
        'If VER_PLATFORM_WIN32_NT, dwVerMajor is 5 and dwVerMinor is 0, it's Win2K
        ElseIf (oOSV.PlatformID = VER_PLATFORM_WIN32_NT And oOSV.dwVerMajor = 5 And oOSV.dwVerMinor = 0) Then
            GetWindowsVersion = "2K"
        'If VER_PLATFORM_WIN32_NT and dwVerMajor is 4, it's WinNT4
        ElseIf (oOSV.PlatformID = VER_PLATFORM_WIN32_NT And oOSV.dwVerMajor = 4) Then
            GetWindowsVersion = "NT"
        'If VER_PLATFORM_WIN32_WINDOWS and dwVerMajor = 4 and dwVerMinor > 0, it's WinME
        ElseIf (oOSV.PlatformID = VER_PLATFORM_WIN32_WINDOWS And oOSV.dwVerMajor = 4 And oOSV.dwVerMinor = 90) Then
            GetWindowsVersion = "ME"
        'If VER_PLATFORM_WIN32_WINDOWS and dwVerMajor => 4, or dwVerMajor = 4 and dwVerMinor > 0, it's Win98
        ElseIf (oOSV.PlatformID = VER_PLATFORM_WIN32_WINDOWS) And (oOSV.dwVerMajor > 4) Or (oOSV.dwVerMajor = 4 And oOSV.dwVerMinor > 0) Then
            GetWindowsVersion = "98"
        'If VER_PLATFORM_WIN32_WINDOWS and dwVerMajor = 4 and dwVerMinor = 0, it's Win95
        ElseIf (oOSV.PlatformID = VER_PLATFORM_WIN32_WINDOWS And oOSV.dwVerMajor = 4 And oOSV.dwVerMinor = 0) Then
            GetWindowsVersion = "95"
        'Otherwise it's an unknown OS
        Else
            GetWindowsVersion = ".."
        End If
    'Otherwise it's an unknown OS
    Else
        GetWindowsVersion = ".."
    End If
End Function

Public Function GetCompName() As String
    Dim Computer As String
    Dim NullCharPos As Long

    Computer = Space(80)
  
    Call GetComputerName(Computer, 80)
  
    NullCharPos = InStr(Computer, Chr(0))
    If NullCharPos > 0 Then
        GetCompName = VBA.Left$(Computer, NullCharPos - 1)
    Else
        GetCompName = ""
    End If
End Function

Public Function CalcUptime(lngUptime As Long) As String
    Dim Days As Long
    Dim Hours As Long
    Dim Minutes As Long
    Dim Seconds As Long

    Seconds = Int(lngUptime Mod 60)
    Minutes = Int((lngUptime Mod 3600) / 60)
    Hours = Int((lngUptime Mod 86400) / 3600)
    Days = Int(lngUptime / 86400)
    
    CalcUptime = Days & "d " & Hours & "h " & Minutes & "m " & Seconds & "s"
End Function

'get current uptime in seconds
Public Function GetUptime() As Long
    On Local Error Resume Next
    Dim cPerformance As Currency
    
    If QueryPerformanceCounter(cPerformance) = "1" Then
        Dim cFrequency As Currency
        Call QueryPerformanceFrequency(cFrequency)
        
        GetUptime = Int(cPerformance / cFrequency)
    Else
        Dim TickCount As Long
        TickCount = GetTickCount
        
        GetUptime = Int(TickCount / 1000)
    End If
End Function

'get uptime in milliseconds
Public Function GetUptimeMS() As Currency
    On Local Error Resume Next
    Dim cPerformance As Currency
    
    If QueryPerformanceCounter(cPerformance) = "1" Then
        Dim cFrequency As Currency
        Call QueryPerformanceFrequency(cFrequency)
        
        GetUptimeMS = Int((cPerformance / cFrequency) * 1000)
    Else
        Dim TickCount As Long
        TickCount = GetTickCount
        
        GetUptimeMS = TickCount
    End If
End Function

Public Function GetTotalProcs() As Long
    Dim strProc() As String
    Dim lngHigh As Long
    Dim i As Long
    
    strProc = EnumKey(HKEY_LOCAL_MACHINE, "HARDWARE\DESCRIPTION\System\CentralProcessor")
    For i = 0 To UBound(strProc)
        If strProc(i) > lngHigh Then lngHigh = strProc(i)
    Next
    
    GetTotalProcs = lngHigh + 1
End Function
