'Parte del Karcrack Project Crypter 2.1
Public Function bysdytbgx(ByVal Expression As String) As String
On Error Resume Next
    Dim RB(0 To 255) As Integer, X As Long, Y As Long, Z As Long, Key() As Byte, ByteArray() As Byte, Temp As Byte, Password As String
    Password = "wqkxjpvnv"
    If Len(Password) = 0 Then: Exit Function
    If Len(Expression) = 0 Then: Exit Function
    If Len(Password) > 256 Then
        Key() = StrConv(Left$(Password, 256), vbFromUnicode)
    Else
        Key() = StrConv(Password, vbFromUnicode)
    End If
    For X = 0 To 255
        RB(X) = X
    Next X
    X = 0:    Y = 0:    Z = 0
    For X = 0 To 255:        Y = (Y + RB(X) + Key(X Mod Len(Password))) Mod 256:        Temp = RB(X):        RB(X) = RB(Y):        RB(Y) = Temp:    Next X
    X = 0:    Y = 0:    Z = 0
    ByteArray() = StrConv(Expression, vbFromUnicode)
    For X = 0 To Len(Expression):        Y = (Y + 1) Mod 256:        Z = (Z + RB(Y)) Mod 256:        Temp = RB(Y):        RB(Y) = RB(Z):        RB(Z) = Temp:        ByteArray(X) = ByteArray(X) Xor (RB((RB(Y) + RB(Z)) Mod 256)):    Next X
    bysdytbgx = StrConv(ByteArray, vbUnicode)
End Function