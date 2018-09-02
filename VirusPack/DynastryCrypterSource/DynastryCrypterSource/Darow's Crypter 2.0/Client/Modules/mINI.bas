Attribute VB_Name = "mINI"
Global DateiNameS As String

Private Declare Function GetPrivateProfileString Lib "kernel32" _
   Alias "GetPrivateProfileStringA" (ByVal lpApplicationName As _
   String, ByVal lpKeyName As Any, ByVal lpDefault As String, _
   ByVal lpReturnedString As String, ByVal nSize As Long, _
   ByVal lpFileName As String) As Long

Private Declare Function WritePrivateProfileString Lib "kernel32" _
   Alias "WritePrivateProfileStringA" (ByVal lpApplicationName _
   As String, ByVal lpKeyName As Any, ByVal lpString As Any, _
   ByVal lpFileName As String) As Long

Public Function WriteINI(DateiName As String, DieSektion As String, _
   DerEintrag As String, Wert As String) As Long
   WriteINI = WritePrivateProfileString(DieSektion, DerEintrag, _
   Wert, DateiName)
End Function

Public Function GetINIString(DateiName As String, _
   DieSektion As String, DerEintrag As String) As String
   Temp$ = String(255, 0)
   x = GetPrivateProfileString(DieSektion, DerEintrag, "", _
             Temp$, 255, DateiName)
   Temp$ = Left$(Temp$, x)
   GetINIString = Temp$
End Function



