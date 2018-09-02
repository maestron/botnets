VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "HWID Decrypter - SpK"
   ClientHeight    =   600
   ClientLeft      =   75
   ClientTop       =   375
   ClientWidth     =   6060
   LinkTopic       =   "Form1"
   ScaleHeight     =   600
   ScaleWidth      =   6060
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Command1 
      Caption         =   "Decrypt"
      Height          =   375
      Left            =   4080
      TabIndex        =   1
      Top             =   120
      Width           =   1815
   End
   Begin VB.TextBox Text1 
      Height          =   375
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   3855
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
If Text1.Text = "" Then
Else
Text1.Text = decrypt(decrypt(Text1.Text))

Text1.Text = Left(Text1.Text, Len(Text1.Text) - 8)


End If
End Sub
Public Function decrypt(strInput As String)
    Dim n As Integer, i As Integer
    n = 13
    For i = 1 To Len(strInput)
        Mid(strInput, i, 1) = Chr(Asc(Mid(strInput, i, 1)) - n)
    Next i
    decrypt = strInput
End Function
