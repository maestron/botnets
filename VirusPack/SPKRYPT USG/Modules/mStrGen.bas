Attribute VB_Name = "mStrGen"
Public Function StrGen(iMin As Integer, iMax As Integer)
sChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVQYZ"

start:
Dim iLen As Integer
Randomize
iLen = Int((iMax - iMin + 1) * Rnd) + iMin

For I = 1 To iLen
    Randomize
    StrGen = StrGen & Mid(sChars, Int(Rnd * Len(sChars) + 1), 1)
Next

Dim dd() As String
dd = Split(Blacklist, ":")
Dim normal As Boolean
If InStr(Blacklist, StrGen) <> 0 Then
    normal = False
    For I = 0 To UBound(dd)
        If StrGen = dd(I) Then
            normal = True
            Exit For
        End If
    Next
    
    If normal = True Then
        normal = False
        GoTo start
    Else
        Blacklist = Blacklist & StrGen & ":"
    End If
Else
    Blacklist = Blacklist & StrGen & ":"
End If

End Function

