Attribute VB_Name = "modKillProc"
Option Explicit

Private Type LUID
   lowpart As Long
   highpart As Long
End Type

Private Type TOKEN_PRIVILEGES
    PrivilegeCount As Long
    LuidUDT As LUID
    Attributes As Long
End Type

Const TOKEN_ADJUST_PRIVILEGES = &H20
Const TOKEN_QUERY = &H8
Const SE_PRIVILEGE_ENABLED = &H2
Const PROCESS_ALL_ACCESS = &H1F0FFF

Private Declare Function GetVersion Lib "kernel32" () As Long
Private Declare Function GetCurrentProcess Lib "kernel32" () As Long
Private Declare Function CloseHandle Lib "kernel32" (ByVal hObject As Long) As _
    Long
Private Declare Function OpenProcessToken Lib "advapi32" (ByVal ProcessHandle _
    As Long, ByVal DesiredAccess As Long, TokenHandle As Long) As Long
Private Declare Function LookupPrivilegeValue Lib "advapi32" Alias _
    "LookupPrivilegeValueA" (ByVal lpSystemName As String, _
    ByVal lpName As String, lpLuid As LUID) As Long
Private Declare Function AdjustTokenPrivileges Lib "advapi32" (ByVal _
    TokenHandle As Long, ByVal DisableAllPrivileges As Long, _
    NewState As TOKEN_PRIVILEGES, ByVal BufferLength As Long, _
    PreviousState As Any, ReturnLength As Any) As Long
Public Declare Function OpenProcess Lib "kernel32" (ByVal dwDesiredAccess As _
    Long, ByVal bInheritHandle As Long, ByVal dwProcessID As Long) As Long
Private Declare Function TerminateProcess Lib "kernel32" (ByVal hProcess As _
    Long, ByVal uExitCode As Long) As Long
    
Private Declare Function GetWindowThreadProcessId Lib "user32" (ByVal hwnd As Long, lpdwProcessId As Long) As Long

' Terminate any application and return an exit code to Windows
' This works under NT/2000, even when the calling process
' doesn't have the privilege to terminate the application
' (for example, this may happen when the process was launched
'  by yet another program)
'
' Usage:  Dim pID As Long
'         pID = Shell("Notepad.Exe", vbNormalFocus)
'         '...
'         If KillProcess(pID, 0) Then
'             MsgBox "Notepad was terminated"
'         End If

Public Function KillProcess(Optional ByVal hProcessID As Long, Optional ByVal ProcessHWND As Long, Optional ByVal ExitCode As Long) _
    As Boolean
    Dim hToken As Long
    Dim hProcess As Long
    Dim tp As TOKEN_PRIVILEGES
    
    If hProcessID = 0 And ProcessHWND = 0 Then Exit Function
    'if they specified a hwnd, turn it into a process ID
    If ProcessHWND > 0 Then Call GetWindowThreadProcessId(ProcessHWND, hProcessID)
    
    ' Windows NT/2000 require a special treatment
    ' to ensure that the calling process has the
    ' privileges to shut down the system
    
    ' under NT the high-order bit (that is, the sign bit)
    ' of the value retured by GetVersion is cleared
    If GetVersion() >= 0 Then
        ' open the tokens for the current process
        ' exit if any error
        If OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES Or _
            TOKEN_QUERY, hToken) = 0 Then
            GoTo CleanUp
        End If
        
        ' retrieves the locally unique identifier (LUID) used
        ' to locally represent the specified privilege name
        ' (first argument = "" means the local system)
        ' Exit if any error
        If LookupPrivilegeValue("", "SeDebugPrivilege", tp.LuidUDT) = 0 Then
            GoTo CleanUp
        End If
    
        ' complete the TOKEN_PRIVILEGES structure with the # of
        ' privileges and the desired attribute
        tp.PrivilegeCount = 1
        tp.Attributes = SE_PRIVILEGE_ENABLED
    
        ' try to acquire debug privilege for this process
        ' exit if error
        If AdjustTokenPrivileges(hToken, False, tp, 0, ByVal 0&, _
            ByVal 0&) = 0 Then
            GoTo CleanUp
        End If
    End If
    
    ' now we can finally open the other process
    ' while having complete access on its attributes
    ' exit if any error
    hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, hProcessID)
    If hProcess Then
        ' call was successful, so we can kill the application
        ' set return value for this function
        KillProcess = (TerminateProcess(hProcess, ExitCode) <> 0)
        ' close the process handle
        CloseHandle hProcess
    End If
    
    If GetVersion() >= 0 Then
        ' under NT restore original privileges
        tp.Attributes = 0
        AdjustTokenPrivileges hToken, False, tp, 0, ByVal 0&, ByVal 0&
        
CleanUp:
        If hToken Then CloseHandle hToken
    End If
End Function
