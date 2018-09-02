Attribute VB_Name = "mAPI"
Public Function ApiCall() As String
ApiCall = ApiCall & "Attribute VB_Name = " & X & F.Text1(0).Text & X & vbCrLf & vbNewLine
ApiCall = ApiCall & "Option Explicit" & vbCrLf & _
"Private Declare Function FreeLibrary Lib " & X & "kernel32" & X & " (ByVal hLibModule As Long) As Long" & vbCrLf & _
"Private mlngParameters() As Long" & vbCrLf & _
"Private mlngAddress As Long" & vbCrLf & _
"Private mbytCode() As Byte" & vbCrLf & _
"Private mlngCP As Long" & vbCrLf & _
"Private Type xbyte" & vbCrLf & _
"    arr() As Byte" & vbCrLf & _
"End Type" & vbCrLf & _
"Private Declare Function LoadLibrary Lib " & X & "kernel32" & X & " Alias " & X & "LoadLibraryA" & X & " (ByVal lpLibFileName As String) As Long" & vbCrLf & _
"Public Function CallAPIByName(libName As String, funcName As String, ParamArray FuncParams()) As Long" & vbCrLf & _
"Dim lpszASD As String * 384" & vbCrLf & _
"Dim arr() As Variant" & vbCrLf & _
"arr() = FuncParams()" & vbCrLf & _
"CallAPIByName = CallRemote(libName, funcName, arr())" & vbCrLf & _
"Dim i As Long" & vbCrLf & _
"For i = LBound(FuncParams()) To UBound(FuncParams())" & vbCrLf & _
"FuncParams(i) = arr(i)" & vbCrLf & _
"Next i" & vbCrLf & _
"End Function" & vbCrLf
ApiCall = ApiCall & "Public Function CallRemote(libName As String, funcName As String, FuncParams() As Variant) As Long" & vbCrLf & _
"Dim i As Integer" & vbCrLf & _
"Dim lpszASD As String * 384" & vbCrLf & _
"Dim wasString() As Boolean" & vbCrLf & _
"Dim keineparams As Boolean" & vbCrLf & _
"Dim lb As Long" & vbCrLf & _
"ReDim mlngParameters(0)" & vbCrLf & _
"ReDim mbytCode(0)" & vbCrLf & _
"mlngAddress = 0" & vbCrLf & _
"Dim x() As xbyte" & vbCrLf & _
"If UBound(FuncParams()) = -1 Then" & vbCrLf & _
"keineparams = True" & vbCrLf & _
"GoTo keineparams" & vbCrLf & _
"End If" & vbCrLf & _
"On Error GoTo 0" & vbCrLf & _
"ReDim wasString(UBound(FuncParams()))" & vbCrLf & _
"For i = LBound(FuncParams()) To UBound(FuncParams())" & vbCrLf & _
"wasString(i) = False" & vbCrLf & _
"If VarType(FuncParams(i)) = vbString Then" & vbCrLf & _
"ReDim Preserve x(i)" & vbCrLf & _
"x(i).arr = StrConv(FuncParams(i), vbFromUnicode) & Chr(0)" & vbCrLf & _
"FuncParams(i) = VarPtr(x(i).arr(0))" & vbCrLf & _
"wasString(i) = True" & vbCrLf & _
"End If" & vbCrLf & _
"Next i" & vbCrLf
ApiCall = ApiCall & "keineparams:" & vbCrLf & _
"lb = LoadLibrary(ByVal libName)" & vbCrLf & _
"If lb = 0 Then" & vbCrLf & _
"Exit Function" & vbCrLf & _
"End If" & vbCrLf & _
"mlngAddress = GetProcAddress(lb, ByVal funcName)" & vbCrLf & _
"If mlngAddress = 0 Then" & vbCrLf & _
"FreeLibrary lb" & vbCrLf & _
"Exit Function" & vbCrLf & _
"End If" & vbCrLf & _
"ReDim mlngParameters(UBound(FuncParams) + 1)" & vbCrLf & _
"For i = 1 To UBound(mlngParameters)" & vbCrLf & _
"mlngParameters(i) = CLng(FuncParams(i - 1))" & vbCrLf & _
"Next i" & vbCrLf & _
"CallRemote = CallWindowProcA(PrepareCode, 0, 0, 0, 0)" & vbCrLf & _
"FreeLibrary lb" & vbCrLf & _
"If keineparams Then Exit Function" & vbCrLf & _
"For i = LBound(FuncParams()) To UBound(FuncParams())" & vbCrLf & _
"If wasString(i) Then" & vbCrLf & _
"FuncParams(i) = StrConv(x(i).arr(), vbUnicode)" & vbCrLf & _
"End If" & vbCrLf & _
"Next i" & vbCrLf & _
"End Function" & vbCrLf
ApiCall = ApiCall & "Private Function PrepareCode() As Long" & vbCrLf & _
"Dim lpszASD As String * 384" & vbCrLf & _
"Dim lngX As Long, codeStart As Long" & vbCrLf & _
"ReDim mbytCode(18 + 32 + 6 * UBound(mlngParameters))" & vbCrLf & _
"codeStart = GetAlignedCodeStart(VarPtr(mbytCode(0)))" & vbCrLf & _
"mlngCP = codeStart - VarPtr(mbytCode(0))" & vbCrLf & _
"For lngX = 0 To mlngCP - 1" & vbCrLf & _
"mbytCode(lngX) = &HCC" & vbCrLf & _
"Next" & vbCrLf & _
"AddByteToCode &H58" & vbCrLf & _
"AddByteToCode &H59" & vbCrLf & _
"AddByteToCode &H59" & vbCrLf & _
"AddByteToCode &H59" & vbCrLf & _
"AddByteToCode &H59" & vbCrLf & _
"AddByteToCode &H50" & vbCrLf & _
"For lngX = UBound(mlngParameters) To 1 Step -1" & vbCrLf & _
"AddByteToCode &H68 'push wwxxyyzz" & vbCrLf & _
"AddLongToCode mlngParameters(lngX)" & vbCrLf & _
"Next" & vbCrLf & _
"AddCallToCode mlngAddress" & vbCrLf & _
"AddByteToCode &HC3" & vbCrLf & _
"AddByteToCode &HCC" & vbCrLf & _
"PrepareCode = codeStart" & vbCrLf & _
"End Function" & vbCrLf
ApiCall = ApiCall & "Private Sub AddCallToCode(lngAddress As Long)" & vbCrLf & _
"Dim lpszASD As String * 384" & vbCrLf & _
"AddByteToCode &HE8" & vbCrLf & _
"AddLongToCode lngAddress - VarPtr(mbytCode(mlngCP)) - 4" & vbCrLf & _
"End Sub" & vbCrLf & _
"Private Sub AddLongToCode(lng As Long)" & vbCrLf & _
"Dim lpszASD As String * 384" & vbCrLf & _
"Dim intX As Integer" & vbCrLf & _
"Dim byt(3) As Byte" & vbCrLf & _
"CopyMemory byt(0), lng, 4" & vbCrLf & _
"For intX = 0 To 3" & vbCrLf & _
"AddByteToCode byt(intX)" & vbCrLf & _
"Next" & vbCrLf & _
"End Sub" & vbCrLf & _
"Private Sub AddByteToCode(byt As Byte)" & vbCrLf & _
"mbytCode(mlngCP) = byt" & vbCrLf & _
"mlngCP = mlngCP + 1" & vbCrLf & _
"End Sub" & vbCrLf & _
"Private Function GetAlignedCodeStart(lngAddress As Long) As Long" & vbCrLf & _
"GetAlignedCodeStart = lngAddress + (15 - (lngAddress - 1) Mod 16)" & vbCrLf & _
"If (15 - (lngAddress - 1) Mod 16) = 0 Then GetAlignedCodeStart = GetAlignedCodeStart + 16" & vbCrLf & _
"End Function" & vbCrLf

End Function
