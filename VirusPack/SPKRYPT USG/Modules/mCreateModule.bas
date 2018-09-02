Attribute VB_Name = "mCreateModule"
Function CreateModuleROT(Attributes As String, Module As String, FunctionName As String, path As String)
F = FreeFile
Dim n As String
Dim i As String
Dim strInput As String

n = StrGen(5, 9)
i = StrGen(5, 9)
strInput = StrGen(5, 20)

Open path & "\" & Module & ".bas" For Output As #F
Print #F, "Attribute VB_Name = " & Chr(34) & Attributes & Chr(34)
Print #F, "Public Function " & FunctionName & "(" & strInput & " As String)"
Print #F, "Dim " & n & " As Integer, " & i & " As Integer"
Print #F, n & " = 13"
Print #F, "For " & i & " = 1 To Len(" & strInput & ")"
Print #F, "Mid(" & strInput & ", " & i & ", 1) = Chr(Asc(Mid(" & strInput & ", " & i & ", 1)) - " & n & ")"
Print #F, "Next " & i
Print #F, FunctionName & " = " & strInput
Print #F, "End Function"
If frmMain.chkJunkFunc.Value = xtpChecked Then
Dim Trash4 As String
Dim iMaxFunc4 As Integer
Dim iMinFunc4 As Integer
iMaxFunc4 = frmMain.txtMaxFunc.Text
iMinFunc4 = frmMain.txtMinFunc.Text
If frmMain.chkTrashFunc.Value = xtpChecked Then
Trash4 = FakeFunction(Int((iMaxFunc4 - txtMinFunc4 + 1) * Rnd) + txtMinFunc4, True)
Else
Trash4 = FakeFunction(Int((iMaxFunc4 - txtMinFunc4 + 1) * Rnd) + txtMinFunc4, False)
End If
Print #F, Trash
End If
Close #F
End Function

