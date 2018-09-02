VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Demo of Transparent Checkbox"
   ClientHeight    =   3090
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   4680
   BeginProperty Font 
      Name            =   "MS Sans Serif"
      Size            =   9.75
      Charset         =   0
      Weight          =   700
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   ForeColor       =   &H00C0C0C0&
   LinkTopic       =   "Form1"
   Picture         =   "Form1.frx":0000
   ScaleHeight     =   3090
   ScaleWidth      =   4680
   StartUpPosition =   2  'CenterScreen
   Begin Project1.CkBx CkBx4 
      Height          =   375
      Left            =   285
      TabIndex        =   4
      Top             =   1230
      Width           =   1905
      _ExtentX        =   3360
      _ExtentY        =   661
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Albert"
         Size            =   15.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   255
   End
   Begin VB.TextBox Text1 
      Height          =   315
      Left            =   1815
      TabIndex        =   3
      Top             =   195
      Width           =   2115
   End
   Begin Project1.CkBx CkBx3 
      Height          =   255
      Left            =   285
      TabIndex        =   2
      Top             =   870
      Width           =   1005
      _ExtentX        =   1773
      _ExtentY        =   450
      CheckColor      =   2
      Enabled         =   0   'False
      Value           =   1
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   16761024
   End
   Begin Project1.CkBx CkBx2 
      Height          =   315
      Left            =   285
      TabIndex        =   1
      Top             =   540
      Width           =   945
      _ExtentX        =   1667
      _ExtentY        =   556
      CheckColor      =   1
      Enabled         =   0   'False
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   65280
   End
   Begin Project1.CkBx CkBx1 
      Height          =   315
      Left            =   285
      TabIndex        =   0
      Top             =   210
      Width           =   1365
      _ExtentX        =   2408
      _ExtentY        =   556
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   255
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub CkBx1_Click()
   If CkBx1.Value = 1 Then
      CkBx2.Enabled = True
      CkBx3.Enabled = True
   Else
      CkBx2.Enabled = False
      CkBx3.Enabled = False
   End If
End Sub

Private Sub CkBx2_Click()
   If CkBx2.Value = 1 Then
      Text1.Text = "You clicked me."
   Else
      Text1.Text = ""
   End If
End Sub

Private Sub CkBx4_Click()
    If CkBx4.Value = 0 Then
       CkBx4.ForeColor = vbRed
    Else
       CkBx4.ForeColor = vbWhite
    End If
End Sub

Private Sub Form_Load()
   CkBx2.Enabled = False
End Sub
