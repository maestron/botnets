Attribute VB_Name = "mEncRC4"
Public Function EncRC4() As String
EncRC4 = EncRC4 & "Attribute VB_Name = " & X & F.Text1(1).Text & X & vbCrLf & vbNewLine
EncRC4 = EncRC4 & "Function RC4ED(ByVal InString As String, ByVal password As String) As String" & vbCrLf & _
"On Error Resume Next" & vbCrLf & _
"    Dim S(0 To 255) As Integer" & vbCrLf & _
"    Dim K(0 To 255) As Integer" & vbCrLf & _
"    Dim i As Integer, j As Integer, tmp As Integer" & vbCrLf & _
"    Dim t As Integer" & vbCrLf & _
"    Dim outstring As String" & vbCrLf & _
"    For tmp = 0 To 255" & vbCrLf & _
"        S(tmp) = tmp" & vbCrLf & _
"        K(tmp) = Asc(Mid(password, 1 + (tmp Mod Len(password)), 1))" & vbCrLf & _
"    Next" & vbCrLf & _
"    For i = 0 To 255" & vbCrLf & _
"        j = (j + S(i) + K(i)) Mod 256" & vbCrLf & _
"        Swap S(i), S(j)" & vbCrLf & _
"    Next" & vbCrLf & _
"    i = 0" & vbCrLf & _
"    j = 0" & vbCrLf & _
"    outstring = " & X & "" & X & vbCrLf & _
"    For tmp = 1 To Len(InString)" & vbCrLf & _
"        i = (i + 1) Mod 256" & vbCrLf & _
"        j = (j + S(i)) Mod 256" & vbCrLf & _
"        Swap S(i), S(j)" & vbCrLf & _
"        t = (S(i) + S(j)) Mod 256" & vbCrLf & _
"        outstring = outstring & Chr((mXor(S(t), Asc(Mid(InString, tmp, 1)))))" & vbCrLf & _
"    Next" & vbCrLf
EncRC4 = EncRC4 & "    RC4ED = outstring" & vbCrLf & _
"End Function" & vbCrLf & _
"Function mXor(i As Integer, j As Integer) As Integer" & vbCrLf & _
"If i = j Then" & vbCrLf & _
"mXor = j" & vbCrLf & _
"Else" & vbCrLf & _
"mXor = i Xor j" & vbCrLf & _
"End If" & vbCrLf & _
"End Function" & vbCrLf & _
"Sub Swap(ByRef a As Integer, ByRef b As Integer)" & vbCrLf & _
"Dim t As Integer" & vbCrLf & _
"t = a" & vbCrLf & _
"a = b" & vbCrLf & _
"b = t" & vbCrLf & _
"End Sub" & vbCrLf

End Function



