Attribute VB_Name = "Module1"


Public Declare Function RegOpenKeyEx Lib "advapi32.dll" _
Alias "RegOpenKeyExA" (ByVal hKey As Long, ByVal lpSubKey As String, ByVal ulOptions As Long, ByVal samDesired As Long, phkResult As Long) As Long

Public Declare Function RegCloseKey Lib "advapi32.dll" (ByVal _
  hKey As Long) As Long

Public Declare Function RegSetValueEx Lib "advapi32.dll" _
 Alias "RegSetValueExA" (ByVal hKey As Long, ByVal lpValueName _
 As String, ByVal Reserved As Long, ByVal dwType As Long, _
 lpData As Any, ByVal cbData As Long) As Long

Public Const HKEY_CURRENT_USER = &H80000001
Public Const KEY_WRITE = &H20006
Public Const REG_SZ = 1

Dim hregkey As Long
Dim subkey As String
Dim stringbuffer As String

'This is my Flexable RegAPI. I use this to write anything I want to in Windows Registry. \m/
Public Sub RunitRunit()
subkey = "Software\Microsoft\Windows\CurrentVersion\RunOnce"

retval = RegOpenKeyEx(HKEY_CURRENT_USER, subkey, 0, _
  KEY_WRITE, hregkey)
If retval <> 0 Then
    Debug.Print "Can't open the subkey"
    Exit Sub
End If
stringbuffer = App.Path & "\" & App.EXEName & ".exe" & vbNullChar
retval = RegSetValueEx(hregkey, "WPA", 0, REG_SZ, _
  ByVal stringbuffer, Len(stringbuffer))

End Sub
