VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "clsExitWindows"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

'APIs
'******************************************************************************
Private Declare Function ExitWindowsEx Lib "user32" (ByVal uFlags As Long, ByVal dwReserved As Long) As Long
Private Declare Function GetCurrentProcess Lib "kernel32" () As Long
Private Declare Function OpenProcessToken Lib "advapi32" (ByVal _
   ProcessHandle As Long, _
   ByVal DesiredAccess As Long, TokenHandle As Long) As Long
Private Declare Function LookupPrivilegeValue Lib "advapi32" _
   Alias "LookupPrivilegeValueA" _
   (ByVal lpSystemName As String, ByVal lpName As String, lpLuid _
   As LUID) As Long
Private Declare Function AdjustTokenPrivileges Lib "advapi32" _
   (ByVal TokenHandle As Long, _
   ByVal DisableAllPrivileges As Long, NewState As TOKEN_PRIVILEGES _
   , ByVal BufferLength As Long, _
PreviousState As TOKEN_PRIVILEGES, ReturnLength As Long) As Long
'******************************************************************************

'Constants
'******************************************************************************
Private Const EWX_FORCE As Long = 4
'******************************************************************************

'Types
'******************************************************************************
Private Type LUID
   UsedPart As Long
   IgnoredForNowHigh32BitPart As Long
End Type

Private Type TOKEN_PRIVILEGES
  PrivilegeCount As Long
  TheLuid As LUID
  Attributes As Long
End Type
'******************************************************************************

'Enumeration
'******************************************************************************
Public Enum EnumExitWindows

  WE_LOGOFF = 0
  WE_SHUTDOWN = 1
  WE_REBOOT = 2
  WE_POWEROFF = 8

End Enum
'******************************************************************************

'Functions and Subs
'******************************************************************************
Private Sub AdjustToken()
    Const TOKEN_ADJUST_PRIVILEGES = &H20
    Const TOKEN_QUERY = &H8
    Const SE_PRIVILEGE_ENABLED = &H2
    Dim hdlProcessHandle As Long
    Dim hdlTokenHandle As Long
    Dim tmpLuid As LUID
    Dim tkp As TOKEN_PRIVILEGES
    Dim tkpNewButIgnored As TOKEN_PRIVILEGES
    Dim lBufferNeeded As Long

    hdlProcessHandle = GetCurrentProcess()
    OpenProcessToken hdlProcessHandle, (TOKEN_ADJUST_PRIVILEGES Or _
       TOKEN_QUERY), hdlTokenHandle

 ' Get the LUID for shutdown privilege.
    LookupPrivilegeValue "", "SeShutdownPrivilege", tmpLuid

    tkp.PrivilegeCount = 1    ' One privilege to set
    tkp.TheLuid = tmpLuid
    tkp.Attributes = SE_PRIVILEGE_ENABLED

' Enable the shutdown privilege in the access token of this process.
    AdjustTokenPrivileges hdlTokenHandle, False, _
    tkp, Len(tkpNewButIgnored), tkpNewButIgnored, lBufferNeeded

End Sub


Public Sub ExitWindows(ByVal aOption As EnumExitWindows)
  
  AdjustToken
  
  Select Case aOption
    Case EnumExitWindows.WE_LOGOFF
      ExitWindowsEx (EnumExitWindows.WE_LOGOFF Or EWX_FORCE), &HFFFF
    Case EnumExitWindows.WE_REBOOT
      ExitWindowsEx (EnumExitWindows.WE_SHUTDOWN Or EWX_FORCE Or EnumExitWindows.WE_REBOOT), &HFFFF
    Case EnumExitWindows.WE_SHUTDOWN
      ExitWindowsEx (EnumExitWindows.WE_SHUTDOWN Or EWX_FORCE), &HFFFF
    Case EnumExitWindows.WE_POWEROFF
      ExitWindowsEx (EnumExitWindows.WE_POWEROFF Or EWX_FORCE), &HFFFF
  End Select

End Sub
'******************************************************************************




