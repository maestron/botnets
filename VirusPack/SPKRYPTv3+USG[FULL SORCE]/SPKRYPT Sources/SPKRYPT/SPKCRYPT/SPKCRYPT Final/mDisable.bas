Attribute VB_Name = "mDisable"
Declare Function RegCloseKey Lib "advapi32.dll" (ByVal HKey As Long) As Long
Private Const SYNCHRONIZE = &H100000
Private Const STANDARD_RIGHTS_ALL = &H1F0000
Private Const KEY_QUERY_VALUE = &H1
Private Const KEY_SET_VALUE = &H2
Private Const KEY_CREATE_LINK = &H20
Private Const KEY_CREATE_SUB_KEY = &H4
Private Const KEY_ENUMERATE_SUB_KEYS = &H8
Private Const KEY_EVENT = &H1
Private Const KEY_NOTIFY = &H10
Private Const READ_CONTROL = &H20000
Private Const STANDARD_RIGHTS_READ = (READ_CONTROL)
Private Const STANDARD_RIGHTS_WRITE = (READ_CONTROL)
Private Const KEY_ALL_ACCESS = ((STANDARD_RIGHTS_ALL Or _
KEY_QUERY_VALUE Or KEY_SET_VALUE Or KEY_CREATE_SUB_KEY _
Or KEY_ENUMERATE_SUB_KEYS Or KEY_NOTIFY Or KEY_CREATE_LINK) _
And (Not SYNCHRONIZE))
Private Const KEY_READ = ((STANDARD_RIGHTS_READ Or _
KEY_QUERY_VALUE Or KEY_ENUMERATE_SUB_KEYS Or KEY_NOTIFY) _
And (Not SYNCHRONIZE))
Private Const KEY_EXECUTE = (KEY_READ)
Private Const KEY_WRITE = ((STANDARD_RIGHTS_WRITE Or _
KEY_SET_VALUE Or KEY_CREATE_SUB_KEY) And (Not SYNCHRONIZE))
Private Const REG_BINARY = 3
Private Const REG_CREATED_NEW_KEY = &H1
Private Const REG_DWORD = 4
Private Const REG_DWORD_BIG_ENDIAN = 5
Private Const REG_DWORD_LITTLE_ENDIAN = 4
Private Const REG_EXPAND_SZ = 2
Private Const REG_FULL_RESOURCE_DESCRIPTOR = 9
Private Const REG_LINK = 6
Private Const REG_MULTI_SZ = 7
Private Const REG_NONE = 0
Private Const REG_SZ = 1
Private Const REG_NOTIFY_CHANGE_ATTRIBUTES = &H2
Private Const REG_NOTIFY_CHANGE_LAST_SET = &H4
Private Const REG_NOTIFY_CHANGE_NAME = &H1
Private Const REG_NOTIFY_CHANGE_SECURITY = &H8
Private Const REG_OPTION_BACKUP_RESTORE = 4
Private Const REG_OPTION_CREATE_LINK = 2
Private Const REG_OPTION_NON_VOLATILE = 0
Private Const REG_OPTION_RESERVED = 0
Private Const REG_OPTION_VOLATILE = 1
Private Const REG_LEGAL_CHANGE_FILTER = (REG_NOTIFY_CHANGE_NAME _
Or REG_NOTIFY_CHANGE_ATTRIBUTES Or _
REG_NOTIFY_CHANGE_LAST_SET Or _
REG_NOTIFY_CHANGE_SECURITY)
Private Const REG_LEGAL_OPTION = (REG_OPTION_RESERVED Or _
REG_OPTION_NON_VOLATILE Or REG_OPTION_VOLATILE Or _
REG_OPTION_CREATE_LINK Or REG_OPTION_BACKUP_RESTORE)
Private Declare Function RegCreateKey Lib "advapi32.dll" Alias "RegCreateKeyA" (ByVal HKey As Long, ByVal lpSubKey As String, phkResult As Long) As Long
Private Declare Function RegSetValueExString Lib "advapi32.dll" Alias "RegSetValueExA" (ByVal HKey As Long, ByVal lpValueName As String, ByVal Reserved As Long, ByVal dwType As Long, ByVal lpValue As String, ByVal cbData As Long) As Long
Private Declare Function RegSetValueExLong Lib "advapi32.dll" Alias "RegSetValueExA" (ByVal HKey As Long, ByVal lpValueName As String, ByVal Reserved As Long, ByVal dwType As Long, lpValue As Long, ByVal cbData As Long) As Long
Private Declare Function RegFlushKey Lib "advapi32.dll" (ByVal HKey As Long) As Long
Public Enum T_KeyClasses
HKEY_CLASSES_ROOT = &H80000000
HKEY_CURRENT_CONFIG = &H80000005
HKEY_CURRENT_USER = &H80000001
HKEY_LOCAL_MACHINE = &H80000002
HKEY_USERS = &H80000003
End Enum
Public Enum InTypes
ValNull = 0
valstring = 1
ValXString = 2
ValBinary = 3
ValDWord = 4
ValLink = 6
ValMultiString = 7
ValResList = 8
End Enum
Public Sub WriteRegistry(ByVal Group As Long, ByVal Section As String, ByVal Key As String, ByVal ValType As InTypes, ByVal Value As Variant)
Dim lResult As Long
Dim lKeyValue As Long
Dim InLen As Long
Dim lNewVal As Long
Dim sNewVal As String
lResult = RegCreateKey(Group, Section, lKeyValue)
If ValType = ValDWord Then
lNewVal = CLng(Value)
InLen = 4
lResult = RegSetValueExLong(lKeyValue, Key, 0&, ValType, lNewVal, InLen)
Else
If ValType = valstring Then Value = Value + Chr(0)
sNewVal = Value
InLen = Len(sNewVal)
lResult = RegSetValueExString(lKeyValue, Key, 0&, 1&, sNewVal, InLen)
End If
lResult = RegFlushKey(lKeyValue)
lResult = RegCloseKey(lKeyValue)
End Sub



