Attribute VB_Name = "mDecString"
Public Function DecString() As String
DecString = DecString & "Attribute VB_Name = " & X & F.Text1(4).Text & X & vbCrLf & vbNewLine
DecString = DecString & "Public Function Decrypt(strData As String, strPassword As String) As String" & vbCrLf & _
"Dim average, n, X, Y, tint As Integer, tchar As String * 3, outputSTR, tmp As String" & vbCrLf & _
"Dim doINT As Long" & vbCrLf & _
"     If Chr(CInt(Left(strData, 3)) - average) = " & X & "%" & X & " Then" & vbCrLf & _
"          strData = Right(strData, Len(strData) - 3)" & vbCrLf & _
"              Y = Len(strData)" & vbCrLf & _
"              Do Until X = Y / 3" & vbCrLf & _
"                    tchar = Left(strData, 3)" & vbCrLf & _
"                    X = X + 1" & vbCrLf & _
"                    tint = CInt(tchar)" & vbCrLf & _
"                    tmp = Chr(tint - average)" & vbCrLf & _
"                    outputSTR = outputSTR & tmp" & vbCrLf & _
"                    strData = Right(strData, Len(strData) - 3)" & vbCrLf & _
"               Loop" & vbCrLf & _
"               Decrypt = outputSTR" & vbCrLf & _
"     Else" & vbCrLf & _
"     End If" & vbCrLf & _
"End Function" & vbCrLf

End Function
