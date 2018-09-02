Attribute VB_Name = "mod1"
Public Declare Function SetWindowPos Lib "user32" (ByVal hwnd As Long, ByVal hWndInsertAfter As Long, ByVal x As Long, ByVal y As Long, ByVal cx As Long, ByVal cy As Long, ByVal wFlags As Long) As Long
Const HWND_TOPMOST = -1
Const SWP_NOMOVE = &H2
Const SWP_NOSIZE = &H1

Public Function PutWindowOnTop(pFrm As Form)
Dim lngWindowPosition As Long

lngWindowPosition = SetWindowPos(pFrm.hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE Or SWP_NOSIZE)
End Function


' generate a random string
'
' the mask can contain the following special chars
'    ? : any ASCII character (1-127)
'    # : a digit
'    A : an alphabetic char
'    N : an alphanumeric char
'    H : an hex char
' all other chars are taken literally
' Example: a random-generated phone number
'   phone = RandomString("(###)-####-####")
Function RandomString(ByVal mask As String) As String
    Dim i As Integer
    Dim acode As Integer
    Dim options As String
    Dim char As String
    
    ' initialize result with proper lenght
    RandomString = mask
    
    For i = 1 To Len(mask)
        ' get the character
        char = Mid$(mask, i, 1)
        Select Case char
            Case "?"
                char = Chr$(1 + Rnd * 127)
                options = ""
            Case "#"
                options = "0123456789"
            Case "A"
                options = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
            Case "N"
                options = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0" _
                    & "123456789"
            Case "H"
                options = "0123456789ABCDEF"
            Case Else
                ' don't modify the character
                options = ""
        End Select
    
        ' select a random char in the option string
        If Len(options) Then
            ' select a random char
            ' note that we add an extra char, in case RND returns 1
            char = Mid$(options & Right$(options, 1), 1 + Int(Rnd * Len(options) _
                ), 1)
        End If
        
        ' insert the character in result string
        Mid(RandomString, i, 1) = char
    Next

End Function


