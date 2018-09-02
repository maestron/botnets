VERSION 5.00
Object = "{A8E5842E-102B-4289-9D57-3B3F5B5E15D3}#13.2#0"; "CODEJO~3.OCX"
Begin VB.Form Form1 
   BorderStyle     =   4  'Fixed ToolWindow
   Caption         =   "SPKRYPT | HWID Gen"
   ClientHeight    =   1650
   ClientLeft      =   45
   ClientTop       =   345
   ClientWidth     =   3510
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1650
   ScaleWidth      =   3510
   StartUpPosition =   3  'Windows Default
   Begin XtremeSuiteControls.GroupBox GroupBox1 
      Height          =   1455
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   3255
      _Version        =   851970
      _ExtentX        =   5741
      _ExtentY        =   2566
      _StockProps     =   79
      Caption         =   "      Hardware ID"
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Tahoma"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      UseVisualStyle  =   -1  'True
      Begin XtremeSuiteControls.PushButton Command2 
         Height          =   255
         Left            =   1680
         TabIndex        =   3
         Top             =   720
         Width           =   1335
         _Version        =   851970
         _ExtentX        =   2355
         _ExtentY        =   450
         _StockProps     =   79
         Caption         =   "Copy"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         UseVisualStyle  =   -1  'True
      End
      Begin XtremeSuiteControls.PushButton Command1 
         Height          =   255
         Left            =   240
         TabIndex        =   2
         Top             =   720
         Width           =   1335
         _Version        =   851970
         _ExtentX        =   2355
         _ExtentY        =   450
         _StockProps     =   79
         Caption         =   "Generate"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         UseVisualStyle  =   -1  'True
      End
      Begin XtremeSuiteControls.FlatEdit Text1 
         Height          =   255
         Left            =   240
         TabIndex        =   1
         Top             =   360
         Width           =   2775
         _Version        =   851970
         _ExtentX        =   4895
         _ExtentY        =   450
         _StockProps     =   77
         BackColor       =   -2147483643
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
      End
      Begin XtremeSuiteControls.Label Label1 
         Height          =   255
         Left            =   360
         TabIndex        =   4
         Top             =   1080
         Width           =   2535
         _Version        =   851970
         _ExtentX        =   4471
         _ExtentY        =   450
         _StockProps     =   79
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
      End
      Begin VB.Image Image1 
         Height          =   225
         Left            =   120
         Picture         =   "Form1.frx":0000
         Top             =   0
         Width           =   240
      End
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Sub Command1_Click()
Text1.Text = GetVolumeID
Label1.Caption = "Generated."
End Sub

Private Sub Command2_Click()
If Text1.Text = "" Then
MsgBox "Generate HWID first."
Else
Clipboard.SetText Text1.Text
Label1.Caption = "Copied to clipboard."

End If
End Sub

