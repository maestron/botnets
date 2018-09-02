Attribute VB_Name = "mEncrypt"
Function StrToChar(hText As String) As String
Dim i As Integer, hTemp As String
If Len(hText) > 0 Then
For i = 1 To Len(hText)
hTemp = hTemp & "Chr(" & Asc(Mid(hText, i, 1)) & ")" & " & "
Next i
StrToChar = Left$(hTemp, Len(hTemp) - 3)
End If
End Function
Public Function RotXEncrypt(strInput As String)
    Dim n As Integer, i As Integer
    n = 13
    For i = 1 To Len(strInput)
        Mid(strInput, i, 1) = Chr(Asc(Mid(strInput, i, 1)) + n)
    Next i
    RotXEncrypt = "(" & Chr(34) & strInput & Chr(34) & ")"
End Function
Public Function RotXDecrypt(strInput As String)
    Dim n As Integer, i As Integer
    n = 13
    For i = 1 To Len(strInput)
        Mid(strInput, i, 1) = Chr(Asc(Mid(strInput, i, 1)) - n)
    Next i
    RotXDecrypt = strInput
End Function
