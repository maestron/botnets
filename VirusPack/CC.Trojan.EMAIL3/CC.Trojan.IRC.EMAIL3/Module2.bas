Attribute VB_Name = "Module2"
      Private Type LUID
         UsedPart As Long
         IgnoredForNowHigh32BitPart As Long
      End Type

      Private Type TOKEN_PRIVILEGES
        PrivilegeCount As Long
        TheLuid As LUID
        Attributes As Long
      End Type

      Private Const EWX_SHUTDOWN As Long = 1
      Private Const EWX_FORCE As Long = 4
      Private Const EWX_REBOOT = 2

      Private Declare Function ExitWindowsEx Lib "user32" (ByVal _
           dwOptions As Long, ByVal dwReserved As Long) As Long

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


         LookupPrivilegeValue "", "SeShutdownPrivilege", tmpLuid

         tkp.PrivilegeCount = 1
         tkp.TheLuid = tmpLuid
         tkp.Attributes = SE_PRIVILEGE_ENABLED

         AdjustTokenPrivileges hdlTokenHandle, False, _
         tkp, Len(tkpNewButIgnored), tkpNewButIgnored, lBufferNeeded

     End Sub
 
 
Public Sub ShutDown()
 AdjustToken
 ExitWindowsEx (EWX_SHUTDOWN), &HFFFF
End Sub

Public Sub ReStart()
  AdjustToken
  ExitWindowsEx (EWX_FORCE), &HFFFF

End Sub
Public Sub ReBooT()
  AdjustToken
  ExitWindowsEx (EWX_REBOOT), &HFFFF
End Sub



