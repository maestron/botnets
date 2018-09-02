VERSION 5.00
Object = "{A8E5842E-102B-4289-9D57-3B3F5B5E15D3}#13.2#0"; "CODEJO~3.OCX"
Begin VB.Form frmAbout 
   BorderStyle     =   4  'Fixed ToolWindow
   Caption         =   "About"
   ClientHeight    =   4335
   ClientLeft      =   45
   ClientTop       =   345
   ClientWidth     =   4905
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4335
   ScaleWidth      =   4905
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin XtremeSuiteControls.PushButton Command1 
      Height          =   375
      Left            =   120
      TabIndex        =   11
      Top             =   3840
      Width           =   4695
      _Version        =   851970
      _ExtentX        =   8281
      _ExtentY        =   661
      _StockProps     =   79
      Caption         =   "Close"
      UseVisualStyle  =   -1  'True
   End
   Begin VB.Frame Frame1 
      Caption         =   "About SpKCORE"
      Height          =   3615
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   4695
      Begin VB.Label Label10 
         Caption         =   "Special thanks to: hackforums and hackhound for their help. Creds to www.crackhackforum.com for big help!"
         Height          =   495
         Left            =   120
         TabIndex        =   10
         Top             =   3000
         Width           =   4095
      End
      Begin VB.Label Label9 
         Caption         =   "pr!ngles"
         Height          =   255
         Left            =   120
         TabIndex        =   9
         Top             =   2760
         Width           =   1455
      End
      Begin VB.Label Label8 
         Caption         =   "Docile"
         Height          =   255
         Left            =   120
         TabIndex        =   8
         Top             =   2520
         Width           =   1575
      End
      Begin VB.Label Label7 
         Caption         =   "Gosu"
         Height          =   255
         Left            =   120
         TabIndex        =   7
         Top             =   2280
         Width           =   1095
      End
      Begin VB.Label Label6 
         Caption         =   "sikandarnanwandi"
         Height          =   255
         Left            =   120
         TabIndex        =   6
         Top             =   2040
         Width           =   3375
      End
      Begin VB.Label Label5 
         Caption         =   "WereWatching"
         Height          =   255
         Left            =   120
         TabIndex        =   5
         Top             =   1800
         Width           =   4095
      End
      Begin VB.Label Label4 
         Caption         =   "Shouts to my friends:"
         Height          =   375
         Left            =   120
         TabIndex        =   4
         Top             =   1440
         Width           =   4215
      End
      Begin VB.Label Label3 
         Caption         =   "Coded by: SpK and iCore"
         Height          =   375
         Left            =   120
         TabIndex        =   3
         Top             =   240
         Width           =   4215
      End
      Begin VB.Label Label2 
         Caption         =   "system. Big thanks to WyldeSchylde for his support."
         Height          =   255
         Left            =   120
         TabIndex        =   2
         Top             =   960
         Width           =   4215
      End
      Begin VB.Label Label1 
         Caption         =   "Big thanks to ProVirus, steve10120, xvisceral for the HWID"
         Height          =   255
         Left            =   120
         TabIndex        =   1
         Top             =   720
         Width           =   4215
      End
   End
End
Attribute VB_Name = "frmAbout"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
frmAbout.Hide
End Sub
