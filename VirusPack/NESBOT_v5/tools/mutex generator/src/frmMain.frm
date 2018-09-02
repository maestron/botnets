VERSION 5.00
Begin VB.Form frmMain 
   BackColor       =   &H00404040&
   BorderStyle     =   4  'Fixed ToolWindow
   Caption         =   "mutex generator"
   ClientHeight    =   465
   ClientLeft      =   45
   ClientTop       =   285
   ClientWidth     =   2265
   BeginProperty Font 
      Name            =   "Tahoma"
      Size            =   8.25
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   465
   ScaleWidth      =   2265
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Begin VB.CommandButton Command1 
      Appearance      =   0  'Flat
      BackColor       =   &H00404040&
      Caption         =   "&generate"
      Height          =   240
      Left            =   1200
      TabIndex        =   1
      Top             =   145
      Width           =   990
   End
   Begin VB.TextBox Text1 
      Appearance      =   0  'Flat
      BackColor       =   &H00404040&
      ForeColor       =   &H00FFFFFF&
      Height          =   285
      Left            =   120
      Locked          =   -1  'True
      TabIndex        =   0
      Top             =   120
      Width           =   975
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
Text1.Text = RandomString("#N##NN#NN")
End Sub

Private Sub Form_Load()
PutWindowOnTop frmMain
End Sub
