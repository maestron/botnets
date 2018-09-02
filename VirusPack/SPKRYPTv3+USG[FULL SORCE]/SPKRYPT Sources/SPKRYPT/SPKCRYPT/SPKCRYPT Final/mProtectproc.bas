Attribute VB_Name = "mProtectproc"
Option Explicit
 
Private Const ANYSIZE_ARRAY = 1
Private Const TOKEN_ADJUST_PRIVILEGES = &H20
Private Const TOKEN_QUERY = &H8
Private Const SE_PRIVILEGE_ENABLED = &H2
 
Private Type LUID
    LowPart As Long
    HighPart As Long
End Type
Private Type LUID_AND_ATTRIBUTES
        pLuid As LUID
        Attributes As Long
End Type
Private Type TOKEN_PRIVILEGES
    PrivilegeCount As Long
    Privileges(ANYSIZE_ARRAY) As LUID_AND_ATTRIBUTES
End Type
 

Private Declare Function AdjustTokenPrivileges Lib "advapi32.dll" (ByVal TokenHandle As Long, ByVal DisableAllPrivileges As Long, NewState As TOKEN_PRIVILEGES, ByVal BufferLength As Long, PreviousState As TOKEN_PRIVILEGES, ReturnLength As Long) As Long
Private Declare Function LookupPrivilegeValue Lib "advapi32" Alias "LookupPrivilegeValueA" (ByVal lpSystemName As String, ByVal lpName As String, lpLUID As LUID) As Long
Private Declare Function GetCurrentProcess Lib "kernel32" () As Long
Private Declare Function OpenProcessToken Lib "advapi32.dll" (ByVal ProcessHandle As Long, ByVal DesiredAccess As Long, TokenHandle As Long) As Long
 

Public Const SE_CREATE_TOKEN_NAME As String = "SeCreateTokenPrivilege"
Public Const SE_ASSIGNPRIMARYTOKEN_NAME As String = "SeAssignPrimaryTokenPrivilege"
Public Const SE_LOCK_MEMORY_NAME As String = "SeLockMemoryPrivilege"
Public Const SE_INCREASE_QUOTA_NAME As String = "SeIncreaseQuotaPrivilege"
Public Const SE_UNSOLICITED_INPUT_NAME As String = "SeUnsolicitedInputPrivilege"
Public Const SE_MACHINE_ACCOUNT_NAME As String = "SeMachineAccountPrivilege"
Public Const SE_TCB_NAME As String = "SeTcbPrivilege"
Public Const SE_SECURITY_NAME As String = "SeSecurityPrivilege"
Public Const SE_TAKE_OWNERSHIP_NAME As String = "SeTakeOwnershipPrivilege"
Public Const SE_LOAD_DRIVER_NAME As String = "SeLoadDriverPrivilege"
Public Const SE_SYSTEM_PROFILE_NAME As String = "SeSystemProfilePrivilege"
Public Const SE_SYSTEMTIME_NAME As String = "SeSystemtimePrivilege"
Public Const SE_PROF_SINGLE_PROCESS_NAME As String = "SeProfileSingleProcessPrivilege"
Public Const SE_INC_BASE_PRIORITY_NAME As String = "SeIncreaseBasePriorityPrivilege"
Public Const SE_CREATE_PAGEFILE_NAME As String = "SeCreatePagefilePrivilege"
Public Const SE_CREATE_PERMANENT_NAME As String = "SeCreatePermanentPrivilege"
Public Const SE_BACKUP_NAME As String = "SeBackupPrivilege"
Public Const SE_RESTORE_NAME As String = "SeRestorePrivilege"
Public Const SE_SHUTDOWN_NAME As String = "SeShutdownPrivilege"
Public Const SE_DEBUG_NAME As String = "SeDebugPrivilege"
Public Const SE_AUDIT_NAME As String = "SeAuditPrivilege"
Public Const SE_SYSTEM_ENVIRONMENT_NAME As String = "SeSystemEnvironmentPrivilege"
Public Const SE_CHANGE_NOTIFY_NAME As String = "SeChangeNotifyPrivilege"
Public Const SE_REMOTE_SHUTDOWN_NAME As String = "SeRemoteShutdownPrivilege"

Public Declare Function RtlSetProcessIsCritical Lib "ntdll.dll" (ByVal NewValue As Boolean, ByVal OldValue As Boolean, ByVal WinLogon As Boolean)
 
Public Function GetPrivilegs(ByVal privilegio As String) As Long

Dim lpLUID As LUID
Dim lpToken As TOKEN_PRIVILEGES
Dim lpAntToken As TOKEN_PRIVILEGES
Dim hToken As Long
Dim hProcess As Long
Dim res As Long
 
hProcess = GetCurrentProcess()
res = OpenProcessToken(hProcess, TOKEN_ADJUST_PRIVILEGES Or TOKEN_QUERY, hToken)
If res = 0 Then
    Exit Function
End If
res = LookupPrivilegeValue(vbNullString, privilegio, lpLUID)
If res = 0 Then
    Exit Function
End If
With lpToken
    .PrivilegeCount = 1
    .Privileges(0).Attributes = SE_PRIVILEGE_ENABLED
    .Privileges(0).pLuid = lpLUID
End With
 
res = AdjustTokenPrivileges(hToken, False, lpToken, Len(lpToken), lpAntToken, Len(lpAntToken))
If res = 0 Then
    Exit Function
End If
GetPrivilegs = res
End Function


