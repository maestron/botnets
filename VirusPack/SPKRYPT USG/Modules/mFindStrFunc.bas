Attribute VB_Name = "mFindStrFunc"
Public Function FindStr(hText As String, strcount As Long, Strings As String)

Dim hTemp() As String
Dim hString() As String
Dim hCount As Long
Dim i, k As Long

If Not Trim$(hText) = vbNullString Then

hTemp() = Split(hText, vbNewLine)

For i = 0 To UBound(hTemp)

    If InStr(1, LCase$(hTemp(i)), "public declare function") Or _
    InStr(1, LCase$(hTemp(i)), "declare function") Or _
    InStr(1, LCase$(hTemp(i)), "private declare function") Or _
    InStr(1, LCase$(hTemp(i)), "public declare sub") Or _
    InStr(1, LCase$(hTemp(i)), "private declare sub") Or _
    InStr(1, LCase$(hTemp(i)), " lib ") Then

Else

If InStr(1, hTemp(i), Chr$(34)) Then

hString() = Split(hTemp(i), Chr$(34))

For k = 1 To UBound(hString) Step 2
 
    
    
    If Not Trim$(Replace$(hString(k), Chr$(0), vbNullString)) = vbNullString Then
        strcount = strcount + 1
        '.SubItems(3) = String_Reverse(hString(k))
        If Len(hString(k)) > 0 Then
        Strings = Strings & Chr(34) & hString(k) & Chr(34) & ":"
        End If

    End If
    

Next k

End If
 
End If
 
Next i
End If
 
End Function
Public Function FindFunctions(hText As String, funccount As Long, Functions As String)

Dim hTemp() As String
Dim hSubs() As String
Dim i As Integer
Dim k As Integer

If Not Trim$(hText) = vbNullString Then

hTemp() = Split(hText, vbNewLine)

If InStr(1, LCase$(hTemp(i)), "main") = 0 Then

For i = 0 To UBound(hTemp)

    If InStr(1, LCase$(hTemp(i)), "public declare function") Or _
    InStr(1, LCase$(hTemp(i)), "declare function") Or _
    InStr(1, LCase$(hTemp(i)), "private declare function") Or _
    InStr(1, LCase$(hTemp(i)), "public declare sub") Or _
    InStr(1, LCase$(hTemp(i)), "private declare sub") Or _
    InStr(1, LCase$(hTemp(i)), " lib ") Then

Else

    If InStr(1, LCase$(hTemp(i)), "public function") Or _
    InStr(1, LCase$(hTemp(i)), "private function") Or _
    InStr(1, LCase$(hTemp(i)), "sub ") Or _
    InStr(1, LCase$(hTemp(i)), "public sub ") Or _
    InStr(1, LCase$(hTemp(i)), "private sub ") Or _
    InStr(1, LCase$(hTemp(i)), "function ") Then

hSubs() = Split(hTemp(i), ",")

If Not Trim$(Back(TextToMed(hTemp(i), Left$(hTemp(i), 2), "("), " ")) = vbNullString Then

        Functions = Functions & Trim$(Back(TextToMed(hTemp(i), Left$(hTemp(i), 2), "("), " ")) & ":"
        


End If

If Not Trim$(Back(TextToMed(hTemp(i), " ", "("), " ")) = vbNullString Then
funccount = funccount + 1
        Functions = Functions & Trim$(Back(TextToMed(hTemp(i), " ", "("), " ")) & ":"
       

If Len(TextToMed(hTemp(i), "(", ")")) > 0 Then

If Not Trim$(Replace$(Replace$(Replace$(Trim$(TextToMed(hTemp(i), "(", ")")), "ByVal", vbNullString), "ByRef", vbNullString), "Optional", vbNullString)) = vbNullString Then

    funccount = funccount + 1
    
    Functions = Functions & Trim$(Replace$(Replace$(Replace$(Trim$(TextToMed(hTemp(i), "(", " ")), "ByVal", vbNullString), "ByRef", vbNullString), "Optional", vbNullString)) & ":"
      

End If

End If

If UBound(hSubs) > 0 Then

For k = 0 To UBound(hSubs)

If k = 0 Then

If Not Trim$(Replace$(Replace$(Replace$(Trim$(TextToMed(hSubs(k), "(", "As")), "ByVal", vbNullString), "ByRef", vbNullString), "Optional", vbNullString)) = vbNullString Then
funccount = funccount + 1
    
        Functions = Functions & Trim$(Replace$(Replace$(Replace$(Trim$(TextToMed(hSubs(k), "(", "As")), "ByVal", vbNullString), "ByRef", vbNullString), "Optional", vbNullString)) & ":"
  

End If

Else

If Not Trim$(Replace$(Replace$(Replace$(Trim$(Replace$(TextToMed(hSubs(k), " ", "As"), "()", vbNullString)), "ByVal", vbNullString), "ByRef", vbNullString), "Optional", vbNullString)) = vbNullString Then
funccount = funccount + 1
   Functions = Functions & Trim$(Replace$(Replace$(Replace$(Trim$(Replace$(TextToMed(hSubs(k), " ", "As"), "()", vbNullString)), "ByVal", vbNullString), "ByRef", vbNullString), "Optional", vbNullString)) & ":"
    

End If

End If

Next k

End If

End If

End If

End If

Next i

End If

End If
End Function

Public Function FindVar(hText As String, varcount As Long, variables As String)

Dim hTemp() As String
Dim hComs() As String
Dim Tipo As String
Dim Tipo2 As String
Dim i, k As Long

If Not Trim$(hText) = vbNullString Then

hTemp() = Split(hText, vbNewLine)

For i = 0 To UBound(hTemp)

    If InStr(1, LCase$(hTemp(i)), "public declare function") Or _
    InStr(1, LCase$(hTemp(i)), "declare function") Or _
    InStr(1, LCase$(hTemp(i)), "private declare function") Or _
    InStr(1, LCase$(hTemp(i)), "public declare sub") Or _
    InStr(1, LCase$(hTemp(i)), "private declare sub") Or _
    InStr(1, LCase$(hTemp(i)), " lib ") Then

Else

If InStr(1, LCase$(hTemp(i)), "dim") Then

If InStr(1, hTemp(i), "Dim") Then Tipo = "Dim" Else: Tipo = "dim"

If InStr(1, hTemp(i), ",") Then

hComs() = Split(hTemp(i), ",")

For k = 0 To UBound(hComs) - 1
 
If Len(hComs(k)) > 0 Then
    variables = variables & Trim$(Back(hComs(k), " ")) & ":"
End If

 
Next k

Else

If InStr(1, hTemp(i), "As") Then Tipo2 = "As" Else: Tipo2 = "as"

If hTemp(i) <> vbNullString Then

    varcount = varcount + 1
variables = variables & Trim$(Replace$(TextToMed(hTemp(i), Tipo, Tipo2), "()", vbNullString)) & ":"
End If



End If
End If
End If
 
 
Next i


End If


End Function
Public Function TextToMed(Text As String, Delimeter1 As String, Delimeter2 As String)
On Error Resume Next
TextToMed = Left$(Mid$(Text, InStr(Text, Delimeter1) + Len(Delimeter1)), InStr(Mid$(Text, InStr(Text, Delimeter1) + Len(Delimeter1)), Delimeter2) - 1)
End Function
Function Back(hData As String, Char As String) As String

If InStrRev(hData, Char) <> 0 Then Back = Right$(hData, Len(hData) - InStrRev(hData, Char))

End Function

Public Function Alg1(Chrs As Variant) As String
Dim xxx
For xxx = 1 To Chrs
Randomize
Alg1 = Alg1 & Chr(CLng((65 - 90) * Rnd + 90))
Next xxx
End Function
