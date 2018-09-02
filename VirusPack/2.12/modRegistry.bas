Attribute VB_Name = "modRegistry"
Option Explicit

Private Declare Function RegCloseKey Lib "advapi32.dll" (ByVal hKey As Long) As Long
Private Declare Function RegCreateKey Lib "advapi32.dll" Alias "RegCreateKeyA" (ByVal hKey As Long, ByVal lpSubKey As String, phkResult As Long) As Long
Private Declare Function RegDeleteKey Lib "advapi32.dll" Alias "RegDeleteKeyA" (ByVal hKey As Long, ByVal lpSubKey As String) As Long
Private Declare Function RegDeleteValue Lib "advapi32.dll" Alias "RegDeleteValueA" (ByVal hKey As Long, ByVal lpValueName As String) As Long
Private Declare Function RegOpenKey Lib "advapi32.dll" Alias "RegOpenKeyA" (ByVal hKey As Long, ByVal lpSubKey As String, phkResult As Long) As Long
Private Declare Function RegQueryValueEx Lib "advapi32.dll" Alias "RegQueryValueExA" (ByVal hKey As Long, ByVal lpValueName As String, ByVal lpReserved As Long, lpType As Long, lpData As Any, lpcbData As Long) As Long
Private Declare Function RegSetValueEx Lib "advapi32.dll" Alias "RegSetValueExA" (ByVal hKey As Long, ByVal lpValueName As String, ByVal Reserved As Long, ByVal dwType As Long, lpData As Any, ByVal cbData As Long) As Long
Private Declare Function RegEnumKeyEx Lib "advapi32.dll" Alias "RegEnumKeyExA" (ByVal hKey As Long, ByVal dwIndex As Long, ByVal lpName As String, lpcbName As Long, ByVal lpReserved As Long, ByVal lpClass As String, lpcbClass As Long, lpftLastWriteTime As FILETIME) As Long
    
Public Const HKEY_CLASSES_ROOT = &H80000000
Public Const HKEY_CURRENT_USER = &H80000001
Public Const HKEY_LOCAL_MACHINE = &H80000002
Public Const HKEY_USERS = &H80000003
Public Const HKEY_PERFORMANCE_DATA = &H80000004

Private Const ERROR_SUCCESS = 0&
Private Const REG_SZ = 1&
Private Const REG_DWORD = 4&
Private Const REG_MULTI_SZ = 7&

Private Type GetRegValue
    ValueName As String * 255
    ValueNameL As Long
    ValueL As Long
    FirstChar As Byte
    OtherChar(251) As Byte
End Type

Private Type FILETIME
    dwLowDateTime As Long
    dwHighDateTime As Long
End Type

Public Function GetString(hKey As Long, strPath As String, strValue As String) As String
    On Local Error Resume Next
    Dim keyhand As Long
    Dim datatype As Long
    Dim lResult As Long
    Dim strBuf As String
    Dim lDataBufSize As Long
    Dim intZeroPos As Integer
    Dim lValueType
    
    Call RegOpenKey(hKey, strPath, keyhand)
    lResult = RegQueryValueEx(keyhand, strValue, 0&, lValueType, ByVal 0&, lDataBufSize)
    If lValueType = REG_SZ Or lValueType = REG_MULTI_SZ Then
        strBuf = String(lDataBufSize, " ")
        lResult = RegQueryValueEx(keyhand, strValue, 0&, 0&, ByVal strBuf, lDataBufSize)
        If lResult = ERROR_SUCCESS Then
            If lValueType = REG_SZ Then
                intZeroPos = InStr(strBuf, Chr$(0))
                If intZeroPos > 0 Then
                    GetString = VBA.Left$(strBuf, intZeroPos - 1)
                Else
                    GetString = strBuf
                End If
            ElseIf lValueType = REG_MULTI_SZ Then
                'get everything but trailing null chars
                GetString = TrimNull(strBuf)
            End If
        End If
    End If
    RegCloseKey (keyhand)
End Function

Public Sub SaveString(hKey As Long, strPath As String, strValue As String, strData As String, Optional blnMultiSz As Boolean = False)
    On Local Error Resume Next
    Dim keyhand As Long
    
    Call RegCreateKey(hKey, strPath, keyhand)
    If blnMultiSz = False Then
        Call RegSetValueEx(keyhand, strValue, 0, REG_SZ, ByVal strData, Len(strData))
    Else
        Call RegSetValueEx(keyhand, strValue, 0, REG_MULTI_SZ, ByVal strData, Len(strData))
    End If
    Call RegCloseKey(keyhand)
End Sub

Public Sub SaveDword(ByVal hKey As Long, ByVal strPath As String, ByVal strValueName As String, ByVal lData As Long)
    On Local Error Resume Next
    Dim keyhand As Long
    Call RegCreateKey(hKey, strPath, keyhand)
    Call RegSetValueEx(keyhand, strValueName, 0&, REG_DWORD, lData, 4)
    Call RegCloseKey(keyhand)
End Sub

Public Function GetDword(ByVal hKey As Long, ByVal strPath As String, ByVal strValueName As String) As Long
    On Local Error Resume Next
    Dim lValueType As Long
    Dim lBuf As Long
    Dim keyhand As Long
    Dim lResult As Long
    
    lResult = RegOpenKey(hKey, strPath, keyhand)
    lResult = RegQueryValueEx(keyhand, strValueName, 0&, lValueType, lBuf, 4)
    If lResult = ERROR_SUCCESS Then
        If lValueType = REG_DWORD Then
            GetDword = lBuf
        End If
    End If
    Call RegCloseKey(keyhand)
End Function

'Public Sub DeleteKey(ByVal hkey As Long, ByVal strKey As String)
'    on local error resume next
'    Call RegDeleteKey(hkey, strKey)
'End Sub

Public Sub DeleteValue(ByVal hKey As Long, ByVal strPath As String, ByVal strValue As String)
    On Local Error Resume Next
    Dim keyhand As Long
    Call RegOpenKey(hKey, strPath, keyhand)
    Call RegDeleteValue(keyhand, strValue)
    Call RegCloseKey(keyhand)
End Sub

Public Function KeyExists(ByVal hKey As Long, strPath As String) As Boolean
    Dim keyhand As Long
    If RegOpenKey(hKey, strPath, keyhand) = ERROR_SUCCESS Then
        KeyExists = True
    Else
        KeyExists = False
    End If
    RegCloseKey (keyhand)
End Function

Public Sub test()
    Dim sTest() As String
    sTest = EnumKey(HKEY_PERFORMANCE_DATA, "\")
    MsgBox UBound(sTest)
End Sub

Public Function EnumKey(ByVal hKey As Long, strPath As String) As String()
    Dim hndKey As Long
    Dim CurKey As Byte
    Dim Done As Integer
    Dim FTime As FILETIME
    Dim RetVal() As GetRegValue
    Dim Keys() As String
    
    Call RegOpenKey(hKey, strPath, hndKey)
  
    Do
      ReDim Preserve RetVal(CurKey)
      With RetVal(CurKey)
        .ValueNameL = 255
        Done = RegEnumKeyEx(hndKey, CurKey, .ValueName, .ValueNameL, 0, _
              vbNull, vbNull, FTime)
        If Done = 259 Then Exit Do
        ReDim Preserve Keys(CurKey)
        Keys(CurKey) = Left(.ValueName, .ValueNameL)
      End With
      CurKey = CurKey + 1
    Loop
    EnumKey = Keys
    
    Call RegCloseKey(hndKey)
End Function
