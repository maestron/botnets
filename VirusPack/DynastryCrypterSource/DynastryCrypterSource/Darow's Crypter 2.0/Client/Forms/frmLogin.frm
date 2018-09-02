VERSION 5.00
Begin VB.Form frmLogin 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Login System"
   ClientHeight    =   1650
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   1875
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   Picture         =   "frmLogin.frx":0000
   ScaleHeight     =   1650
   ScaleWidth      =   1875
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox Text2 
      Height          =   285
      IMEMode         =   3  'DISABLE
      Left            =   240
      PasswordChar    =   "*"
      TabIndex        =   4
      Top             =   960
      Width           =   1455
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Login"
      Height          =   255
      Left            =   480
      TabIndex        =   2
      Top             =   1320
      Width           =   975
   End
   Begin VB.TextBox Text1 
      Height          =   285
      Left            =   240
      TabIndex        =   1
      Top             =   360
      Width           =   1455
   End
   Begin VB.Label Label2 
      BackStyle       =   0  'Transparent
      Caption         =   "AuthCode:"
      ForeColor       =   &H00FFFFFF&
      Height          =   255
      Left            =   480
      TabIndex        =   3
      Top             =   720
      Width           =   855
   End
   Begin VB.Label Label1 
      BackStyle       =   0  'Transparent
      Caption         =   "Username:"
      ForeColor       =   &H00FFFFFF&
      Height          =   255
      Left            =   480
      TabIndex        =   0
      Top             =   120
      Width           =   855
   End
End
Attribute VB_Name = "frmLogin"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
On Error Resume Next
If Len(Text2.Text) <> 6 Then
MsgBox "Auth code invalid"
Exit Sub
End If
If CheckUser(Text1.Text, Text2.Text) = True Then
Call SaveInfo
fDynastyCrypt.Show
frmAbout.Label2.Caption = Text1.Text
Me.Hide
Else
MsgBox "Invalid details"
End If
End Sub

Private Sub SaveInfo()
DateiNameS = App.Path & "\settings.ini"
Call WriteINI(DateiNameS, "Login", "Username", Text1.Text)
Call WriteINI(DateiNameS, "Login", "AuthCode", Text2.Text)
Call WriteINI(DateiNameS, "Login", "Enabled", "1")
End Sub

Private Sub Form_Load()
On Error Resume Next
DateiNameS = App.Path & "\settings.ini"
Text1.Text = GetINIString(DateiNameS, "Login", "Username")
Text2.Text = GetINIString(DateiNameS, "Login", "AuthCode")
End Sub
