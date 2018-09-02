Attribute VB_Name = "Registry"
' regg functions
' This was not coded by me - got it from somewhere
 
Declare Function RegOpenKeyEx Lib "advapi32.dll" Alias "RegOpenKeyExA" (ByVal hKey As Long, ByVal lpSubKey As String, ByVal ulOptions As Long, ByVal samDesired As Long, phkResult As Long) As Long
Declare Function RegCloseKey Lib "advapi32.dll" (ByVal hKey As Long) As Long
Declare Function RegCreateKey Lib "advapi32.dll" Alias "RegCreateKeyA" (ByVal hKey As Long, ByVal lpSubKey As String, phkResult As Long) As Long
Declare Function RegDeleteKey Lib "advapi32.dll" Alias "RegDeleteKeyA" (ByVal hKey As Long, ByVal lpSubKey As String) As Long
Declare Function RegDeleteValue Lib "advapi32.dll" Alias "RegDeleteValueA" (ByVal hKey As Long, ByVal lpValueName As String) As Long
Declare Function RegQueryValueEx Lib "advapi32.dll" Alias "RegQueryValueExA" (ByVal hKey As Long, ByVal lpValueName As String, ByVal lpReserved As Long, lpType As Long, ByVal lpData As String, lpcbData As Long) As Long
Declare Function RegQueryValueExA Lib "advapi32.dll" (ByVal hKey As Long, ByVal lpValueName As String, ByVal lpReserved As Long, lpType As Long, ByRef lpData As Long, lpcbData As Long) As Long
Declare Function RegSetValueEx Lib "advapi32.dll" Alias "RegSetValueExA" (ByVal hKey As Long, ByVal lpValueName As String, ByVal Reserved As Long, ByVal dwType As Long, ByVal lpData As String, ByVal cbData As Long) As Long
Declare Function RegSetValueExA Lib "advapi32.dll" (ByVal hKey As Long, ByVal lpValueName As String, ByVal Reserved As Long, ByVal dwType As Long, ByRef lpData As Long, ByVal cbData As Long) As Long
Declare Function RegSetValueExB Lib "advapi32.dll" Alias "RegSetValueExA" (ByVal hKey As Long, ByVal lpValueName As String, ByVal Reserved As Long, ByVal dwType As Long, ByRef lpData As Byte, ByVal cbData As Long) As Long

Const ERROR_SUCCESS = 0&
Const ERROR_BADDB = 1009&
Const ERROR_BADKEY = 1010&
Const ERROR_CANTOPEN = 1011&
Const ERROR_CANTREAD = 1012&
Const ERROR_CANTWRITE = 1013&
Const ERROR_OUTOFMEMORY = 14&
Const ERROR_INVALID_PARAMETER = 87&
Const ERROR_ACCESS_DENIED = 5&
Const ERROR_NO_MORE_ITEMS = 259&
Const ERROR_MORE_DATA = 234&

Const REG_NONE = 0&
Const REG_SZ = 1&
Const REG_EXPAND_SZ = 2&
Const REG_BINARY = 3&
Const REG_DWORD = 4&
Const REG_DWORD_LITTLE_ENDIAN = 4&
Const REG_DWORD_BIG_ENDIAN = 5&
Const REG_LINK = 6&
Const REG_MULTI_SZ = 7&
Const REG_RESOURCE_LIST = 8&
Const REG_FULL_RESOURCE_DESCRIPTOR = 9&
Const REG_RESOURCE_REQUIREMENTS_LIST = 10&

Const KEY_QUERY_VALUE = &H1&
Const KEY_SET_VALUE = &H2&
Const KEY_CREATE_SUB_KEY = &H4&
Const KEY_ENUMERATE_SUB_KEYS = &H8&
Const KEY_NOTIFY = &H10&
Const KEY_CREATE_LINK = &H20&
Const READ_CONTROL = &H20000
Const WRITE_DAC = &H40000
Const WRITE_OWNER = &H80000
Const SYNCHRONIZE = &H100000
Const STANDARD_RIGHTS_REQUIRED = &HF0000
Const STANDARD_RIGHTS_READ = READ_CONTROL
Const STANDARD_RIGHTS_WRITE = READ_CONTROL
Const STANDARD_RIGHTS_EXECUTE = READ_CONTROL
Const KEY_READ = STANDARD_RIGHTS_READ Or KEY_QUERY_VALUE Or KEY_ENUMERATE_SUB_KEYS Or KEY_NOTIFY
Const KEY_WRITE = STANDARD_RIGHTS_WRITE Or KEY_SET_VALUE Or KEY_CREATE_SUB_KEY
Const KEY_EXECUTE = KEY_READ

Public Const HKEY_CLASSES_ROOT = &H80000000
Public Const HKEY_CURRENT_USER = &H80000001
Public Const HKEY_LOCAL_MACHINE = &H80000002
Public Const HKEY_USERS = &H80000003
Public Const HKEY_PERFORMANCE_DATA = &H80000004
Public Const HKEY_CURRENT_CONFIG = &H80000005
Public Const HKEY_DYN_DATA = &H80000006

Dim hKey As Long, MainKeyHandle As Long
Dim rtn As Long, lbuffer As Long, sBuffer As String
Dim lBufferSize As Long
Dim lDataSize As Long
Dim ByteArray() As Byte

Const DisplayErrorMsg = False

Function SetDWORDValue(SubKey As String, Entry As String, Value As Long)

Call ParseKey(SubKey, MainKeyHandle)

If MainKeyHandle Then
   rtn = RegOpenKeyEx(MainKeyHandle, SubKey, 0, KEY_WRITE, hKey) 'open the key
   If rtn = ERROR_SUCCESS Then
      rtn = RegSetValueExA(hKey, Entry, 0, REG_DWORD, Value, 4)
      rtn = RegCloseKey(hKey)
   Else
      If DisplayErrorMsg = True Then
      End If
   End If
End If

End Function
Function GetDWORDValue(SubKey As String, Entry As String)

Call ParseKey(SubKey, MainKeyHandle)

If MainKeyHandle Then
   rtn = RegOpenKeyEx(MainKeyHandle, SubKey, 0, KEY_READ, hKey)
   If rtn = ERROR_SUCCESS Then
      rtn = RegQueryValueExA(hKey, Entry, 0, REG_DWORD, lbuffer, 4)
      If rtn = ERROR_SUCCESS Then
         rtn = RegCloseKey(hKey)
         GetDWORDValue = lbuffer
      Else
         GetDWORDValue = "Error"
         If DisplayErrorMsg = True Then
         End If
      End If
   Else
      GetDWORDValue = "Error"
   End If
End If

End Function

Function DeleteKey(KeyName As String)

Call ParseKey(KeyName, MainKeyHandle)

If MainKeyHandle Then
   rtn = RegOpenKeyEx(MainKeyHandle, KeyName, 0, KEY_WRITE, hKey)
   If rtn = ERROR_SUCCESS Then
      rtn = RegDeleteKey(hKey, KeyName)
      rtn = RegCloseKey(hKey)
   End If
End If

End Function

Public Function DeleteValue(KeyName As String, ValueName As String)

Call ParseKey(KeyName, MainKeyHandle)
If MainKeyHandle Then
   rtn = RegOpenKeyEx(MainKeyHandle, KeyName, 0, KEY_WRITE, hKey)
   If rtn = ERROR_SUCCESS Then
      rtn = RegDeleteValue(hKey, ValueName)
      rtn = RegCloseKey(hKey)
   End If
End If

End Function

Function GetMainKeyHandle(MainKeyName As String) As Long

Const HKEY_CLASSES_ROOT = &H80000000
Const HKEY_CURRENT_USER = &H80000001
Const HKEY_LOCAL_MACHINE = &H80000002
Const HKEY_USERS = &H80000003
Const HKEY_PERFORMANCE_DATA = &H80000004
Const HKEY_CURRENT_CONFIG = &H80000005
Const HKEY_DYN_DATA = &H80000006
   
Select Case MainKeyName
       Case "HKEY_CLASSES_ROOT"
            GetMainKeyHandle = HKEY_CLASSES_ROOT
       Case "HKEY_CURRENT_USER"
            GetMainKeyHandle = HKEY_CURRENT_USER
       Case "HKEY_LOCAL_MACHINE"
            GetMainKeyHandle = HKEY_LOCAL_MACHINE
       Case "HKEY_USERS"
            GetMainKeyHandle = HKEY_USERS
       Case "HKEY_PERFORMANCE_DATA"
            GetMainKeyHandle = HKEY_PERFORMANCE_DATA
       Case "HKEY_CURRENT_CONFIG"
            GetMainKeyHandle = HKEY_CURRENT_CONFIG
       Case "HKEY_DYN_DATA"
            GetMainKeyHandle = HKEY_DYN_DATA
End Select

End Function

Function GetStringValue(SubKey As String, Entry As String) As String

Call ParseKey(SubKey, MainKeyHandle)

If MainKeyHandle Then
   rtn = RegOpenKeyEx(MainKeyHandle, SubKey, 0, KEY_READ, hKey)
   If rtn = ERROR_SUCCESS Then
      sBuffer = Space(255)
      lBufferSize = Len(sBuffer)
      rtn = RegQueryValueEx(hKey, Entry, 0, REG_SZ, sBuffer, lBufferSize)
      If rtn = ERROR_SUCCESS Then
         rtn = RegCloseKey(hKey)
         sBuffer = Trim$(sBuffer)
         GetStringValue = LeftStr(sBuffer, Len(sBuffer) - 1)
      Else
         GetStringValue = "Error"
      End If
   Else
      GetStringValue = "Error"
   End If
End If

End Function

Public Sub ParseKey(KeyName As String, Keyhandle As Long)
    
rtn = InStr(KeyName, "\")

If LeftStr(KeyName, 5) <> "HKEY_" Or Right(KeyName, 1) = "\" Then
   Exit Sub
ElseIf rtn = 0 Then
   Keyhandle = GetMainKeyHandle(KeyName)
   KeyName = ""
Else
   Keyhandle = GetMainKeyHandle(LeftStr(KeyName, rtn - 1)) 'seperate the Keyname
   KeyName = Right(KeyName, Len(KeyName) - rtn)
End If

End Sub
Function CreateKey(SubKey As String)

Call ParseKey(SubKey, MainKeyHandle)

If MainKeyHandle Then
   rtn = RegCreateKey(MainKeyHandle, SubKey, hKey)
   If rtn = ERROR_SUCCESS Then
      rtn = RegCloseKey(hKey)
   End If
End If

End Function
Function SetStringValue(SubKey As String, Entry As String, Value As String)

Call ParseKey(SubKey, MainKeyHandle)

If MainKeyHandle Then
   rtn = RegOpenKeyEx(MainKeyHandle, SubKey, 0, KEY_WRITE, hKey)
   If rtn = ERROR_SUCCESS Then
      rtn = RegSetValueEx(hKey, Entry, 0, REG_SZ, ByVal Value, Len(Value))
      If Not rtn = ERROR_SUCCESS Then
         If DisplayErrorMsg = True Then
         End If
      End If
      rtn = RegCloseKey(hKey)
   End If
End If

End Function

