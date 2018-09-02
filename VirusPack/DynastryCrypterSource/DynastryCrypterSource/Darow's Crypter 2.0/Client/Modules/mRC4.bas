Attribute VB_Name = "mRC4"

Function RC4ED(ByVal InString As String, ByVal password As String) As String

    Dim S(0 To 255) As Integer
    Dim K(0 To 255) As Integer
    Dim i As Integer, j As Integer, tmp As Integer
    Dim t As Integer
    Dim outstring As String


    For tmp = 0 To 255
        S(tmp) = tmp
        K(tmp) = Asc(Mid(password, 1 + (tmp Mod Len(password)), 1))
    Next



    For i = 0 To 255
        j = (j + S(i) + K(i)) Mod 256
        Swap S(i), S(j)
    Next

    i = 0
    j = 0
    outstring = ""


    For tmp = 1 To Len(InString)
        i = (i + 1) Mod 256
        j = (j + S(i)) Mod 256
        Swap S(i), S(j)
        t = (S(i) + S(j)) Mod 256
        outstring = outstring & Chr((mXor(S(t), Asc(Mid(InString, tmp, 1)))))
    Next

    RC4ED = outstring
End Function

Function mXor(i As Integer, j As Integer) As Integer
If i = j Then
mXor = j
Else
mXor = i Xor j
End If
End Function

Sub Swap(ByRef a As Integer, ByRef b As Integer)
Dim t As Integer
t = a
a = b
b = t
End Sub
