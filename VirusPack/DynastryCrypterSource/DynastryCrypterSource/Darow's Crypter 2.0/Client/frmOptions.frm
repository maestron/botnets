VERSION 5.00
Begin VB.Form frmOptions 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Options"
   ClientHeight    =   6645
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   4230
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   6645
   ScaleWidth      =   4230
   StartUpPosition =   3  'Windows Default
   Begin VB.Frame Frame4 
      Caption         =   "Clone File"
      Height          =   855
      Left            =   120
      TabIndex        =   16
      Top             =   2880
      Width           =   3975
      Begin VB.CommandButton Command3 
         Caption         =   "Browse"
         Height          =   255
         Left            =   3120
         TabIndex        =   18
         Top             =   360
         Width           =   735
      End
      Begin VB.TextBox txtClone 
         Height          =   285
         Left            =   120
         TabIndex        =   17
         Top             =   360
         Width           =   2895
      End
   End
   Begin VB.Frame Frame3 
      Caption         =   "Key"
      Height          =   1575
      Left            =   120
      TabIndex        =   12
      Top             =   4920
      Width           =   3975
      Begin VB.CommandButton Command2 
         Caption         =   "Generate"
         Height          =   255
         Left            =   1320
         TabIndex        =   15
         Top             =   1200
         Width           =   1335
      End
      Begin VB.TextBox txtKey 
         Enabled         =   0   'False
         Height          =   285
         Left            =   720
         TabIndex        =   14
         Top             =   720
         Width           =   2535
      End
      Begin VB.OptionButton Option1 
         Caption         =   "Blowfish"
         Enabled         =   0   'False
         Height          =   255
         Left            =   1440
         TabIndex        =   13
         Top             =   360
         Value           =   -1  'True
         Width           =   975
      End
   End
   Begin VB.Frame Frame2 
      Caption         =   "Icon"
      Height          =   975
      Left            =   120
      TabIndex        =   8
      Top             =   3840
      Width           =   3975
      Begin VB.PictureBox Picture1 
         Height          =   615
         Left            =   1560
         ScaleHeight     =   555
         ScaleWidth      =   675
         TabIndex        =   9
         Top             =   240
         Width           =   735
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "Add Section"
      Height          =   1215
      Left            =   120
      TabIndex        =   3
      Top             =   1560
      Width           =   3975
      Begin VB.CommandButton Command1 
         Caption         =   "Random"
         Height          =   255
         Left            =   1920
         TabIndex        =   7
         Top             =   720
         Width           =   855
      End
      Begin VB.TextBox txtSecName 
         Height          =   285
         Left            =   120
         TabIndex        =   5
         Top             =   720
         Width           =   1575
      End
      Begin VB.CheckBox chk_AS 
         Caption         =   "Add New Section"
         Height          =   255
         Left            =   120
         TabIndex        =   4
         Top             =   240
         Width           =   1815
      End
      Begin VB.Label Label1 
         Caption         =   "Section name:"
         Height          =   255
         Left            =   120
         TabIndex        =   6
         Top             =   480
         Width           =   1215
      End
   End
   Begin VB.Frame frmOptions 
      Caption         =   "Options"
      Height          =   1335
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   3975
      Begin VB.CheckBox chk_PAD 
         Caption         =   "Remove PADDINGX"
         Height          =   255
         Left            =   120
         TabIndex        =   11
         Top             =   960
         Width           =   2055
      End
      Begin VB.CheckBox chk_EOF 
         Caption         =   "Save EOF"
         Height          =   255
         Left            =   120
         TabIndex        =   10
         Top             =   720
         Width           =   1455
      End
      Begin VB.CheckBox chk_SR 
         Caption         =   "StripRelocations"
         Height          =   255
         Left            =   120
         TabIndex        =   2
         Top             =   480
         Width           =   1575
      End
      Begin VB.CheckBox chk_RA 
         Caption         =   "ReAlign PE"
         Height          =   255
         Left            =   120
         TabIndex        =   1
         Top             =   240
         Width           =   1335
      End
   End
End
Attribute VB_Name = "frmOptions"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim CD As cFileDialog
Private Declare Sub InitCommonControls Lib "comctl32" ()

Private Sub Command1_Click()
Dim Matrix As String
  
 Randomize Timer
  For x = 1 To Val(7)
   Matrix = Matrix & Chr(CLng(58 * Rnd + 1) + 64)
  Next x
  
txtSecName.Text = "." & Matrix
End Sub

Private Sub Command2_Click()
Dim Matrix As String
  
 Randomize Timer
  For x = 1 To Val(36)
   Matrix = Matrix & Chr(CLng(58 * Rnd + 1) + 64)
  Next x
  
txtKey.Text = Matrix
End Sub

Private Sub Command3_Click()
CD.Filter = "PE Files (*.exe*)|*.exe*"
CD.Filename = ""
CD.ShowOpen
txtClone.Text = CD.Filename
End Sub

Private Sub Form_Load()
On Error Resume Next
Set CD = New cFileDialog
InitCommonControls
Call Command2_Click
End Sub

Private Sub Form_QueryUnload(Cancel As Integer, UnloadMode As Integer)
Me.Hide
End Sub

Private Sub Form_Terminate()
Me.Hide
End Sub

Private Sub Form_Unload(Cancel As Integer)
Me.Hide
End Sub

Private Sub Picture1_Click()
With CD
.DialogTitle = "Select Icon"
.Filter = "Icon|*.ico"
.ShowOpen
If Not CD.Filename = vbNullString Then
bIcon = True
sIcon = CD.Filename
Picture1.Picture = LoadPicture(CD.Filename)
End If
End With
End Sub
