Attribute VB_Name = "mFakeFunction"
Public Function FakeFunction(iLen As Integer, bTrashLines As Boolean) As String
Dim sName As String
Dim Temporary As String
Dim sInteger As Integer
Dim sTrash As String
sTrash = ""
Temporary = ""
sName = ""
FakeFunction = ""


For u = 1 To iLen
    Temporary = ""
    Randomize
    sName = StrGen(10, 20)
    sInteger = Int(Rnd * 4)
    
    Dim Types(3) As String
    Types(0) = "Private Sub "
    Types(1) = "Public Sub "
    Types(2) = "Private Function "
    Types(3) = "Public Function "
    

    
    Temporary = Types(sInteger) & sName & "()"
    Randomize
    

    If bTrashLines = True Then
        imax = frmMain.txtMaxAPI
        imin = frmMain.txtMinAPI
        Randomize
        iLen2 = Int((imax - imin + 1) * Rnd) + imin
        For i = 1 To iLen2
            sTrash = sTrash & TrashSubs & vbNewLine
        Next
    Else
        sTrash = ""
    End If
    
    Temporary = Temporary & vbNewLine
    Temporary = Temporary & sTrash
    
    If sInteger = 0 Or sInteger = 1 Then
        Temporary = Temporary & vbNewLine & "End Sub"
    Else
        Temporary = Temporary & vbNewLine & "End Function"
    End If
    
    
    FakeFunction = FakeFunction & vbNewLine & Temporary
Next

End Function

Private Function TrashSubs() As String
Dim Temporary As String
Dim sInteger As Integer
Dim TemporaryName As String
Dim Types(4) As String
Types(1) = "String"
Types(2) = "Integer"
Types(3) = "Long"
Types(4) = "Currency"
Temporary = ""
TemporaryName = ""
Randomize
sInteger = Int(Rnd * 4) + 1
TemporaryName = StrGen(10, 20)



Select Case sInteger
    Case 1
        Temporary = "Dim " & TemporaryName & " As String" & vbNewLine & TemporaryName & " = " & Chr(34) & Chr(34)
  Case 2
        Temporary = "Dim " & TemporaryName & " As String" & vbNewLine & TemporaryName & " = " & Chr(34) & Chr(34)
 Case 3
       Temporary = "Dim " & TemporaryName & " As String" & vbNewLine & TemporaryName & " = " & Chr(34) & Chr(34)
 Case 4
        Temporary = "Dim " & TemporaryName & " As String" & vbNewLine & TemporaryName & " = " & Chr(34) & Chr(34)
 
  '  Case 2
   '     Randomize
    '    Temporary = "Dim " & TemporaryName & " As " & Types(Int(Rnd * 4) + 1) & vbNewLine & _
     '           TemporaryName & " = " & """" & Int(Rnd * 10000) + 1 & """"
   ' Case 3
    '    Randomize
     '   Temporary = "if " & """" & TemporaryName & """" & " = " & """" & StrGen(10, 20) & """" & " Then End"
   ' Case 4
    '    Dim sInteger2 As Integer
     '   Randomize
      '  If Int(Rnd * 2) + 1 = 1 Then
       '     sInteger2 = Int(Rnd * 5)
        '    Temporary = "Dim " & TemporaryName & " as integer" & vbNewLine & _
         '           "For " & TemporaryName & " = " & sInteger2 & " To " & sInteger2 + Int(Rnd * 10) + 1 & vbNewLine & _
          '          "   DoEvents" & vbNewLine & _
           '         "Next " & TemporaryName
        'Else
         '   Randomize
          '  Temporary = "Dim " & TemporaryName & " As Integer" & vbNewLine & _
           '         TemporaryName & " = " & Int(Rnd * 15) & vbNewLine & _
            '        "Do while " & TemporaryName & " < " & Int(Rnd * 20) + 20 & vbNewLine & _
             '       "   DoEvents:" & TemporaryName & " = " & TemporaryName & " + 1" & vbNewLine & _
              '      "Loop"
       ' End If
End Select

TrashSubs = Temporary
End Function



