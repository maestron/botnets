VERSION 5.00
Begin VB.Form Form1 
   AutoRedraw      =   -1  'True
   Caption         =   "Framez v1.14"
   ClientHeight    =   4635
   ClientLeft      =   1320
   ClientTop       =   2160
   ClientWidth     =   8610
   LinkTopic       =   "Form1"
   Picture         =   "Form1.frx":0000
   ScaleHeight     =   4635
   ScaleWidth      =   8610
   Begin VB.PictureBox Picture1 
      Appearance      =   0  'Flat
      AutoRedraw      =   -1  'True
      BackColor       =   &H80000005&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   4830
      Left            =   5850
      Picture         =   "Form1.frx":197C
      ScaleHeight     =   4830
      ScaleWidth      =   2715
      TabIndex        =   6
      Top             =   -15
      Width           =   2715
      Begin Project1.Framez Framez1 
         Height          =   1440
         Left            =   135
         TabIndex        =   7
         Top             =   60
         Width           =   2460
         _ExtentX        =   4339
         _ExtentY        =   2540
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BackColor       =   8421631
         ForeColor       =   13977088
         ForeColorDisabled=   13977088
         XP7_BorderColor =   65280
         Caption         =   "XP Blue/Silver"
         Transparent     =   -1  'True
      End
      Begin Project1.Framez Framez2 
         Height          =   1440
         Left            =   135
         TabIndex        =   8
         Top             =   1680
         Width           =   2460
         _ExtentX        =   4339
         _ExtentY        =   2540
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         FrameStyle      =   12
         ForeColor       =   677017
         ForeColorDisabled=   677017
         XP7_BorderColor =   8421631
         Caption         =   "XP Olive Green"
         Transparent     =   -1  'True
      End
      Begin Project1.Framez Framez7 
         Height          =   1230
         Left            =   165
         TabIndex        =   11
         Top             =   3240
         Width           =   2355
         _ExtentX        =   2672
         _ExtentY        =   2170
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         FrameStyle      =   10
         BackColor       =   16777215
         Caption         =   "Control"
         Transparent     =   -1  'True
      End
   End
   Begin Project1.Framez Framez11 
      Height          =   1230
      Left            =   2070
      TabIndex        =   5
      Top             =   2100
      Width           =   1515
      _ExtentX        =   2672
      _ExtentY        =   2170
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      FrameStyle      =   10
      Caption         =   "Control"
   End
   Begin Project1.Framez Framez10 
      Height          =   1230
      Left            =   315
      TabIndex        =   4
      Top             =   2055
      Width           =   1515
      _ExtentX        =   2672
      _ExtentY        =   2170
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      FrameStyle      =   5
      Caption         =   "Button"
   End
   Begin Project1.Framez Framez9 
      Height          =   1230
      Left            =   3870
      TabIndex        =   3
      Top             =   2085
      Width           =   1515
      _ExtentX        =   2672
      _ExtentY        =   2170
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      FrameStyle      =   6
      XP7_BorderColor =   8421631
      Caption         =   "Etched In"
   End
   Begin Project1.Framez Framez6 
      Height          =   1530
      Left            =   3825
      TabIndex        =   2
      Top             =   135
      Width           =   1845
      _ExtentX        =   3254
      _ExtentY        =   2699
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      FrameStyle      =   9
      BackColor       =   12648447
      XP7_BorderColor =   15065045
      Caption         =   "Etched Out - Yellow"
   End
   Begin Project1.Framez Framez5 
      Height          =   1395
      Left            =   2085
      TabIndex        =   1
      Top             =   90
      Width           =   1515
      _ExtentX        =   2672
      _ExtentY        =   2170
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      FrameStyle      =   2
      BackColor       =   16777215
      ForeColorDisabled=   0
      XP7_BorderColor =   15065045
      Caption         =   "Sunken Out"
      Transparent     =   -1  'True
   End
   Begin Project1.Framez Framez4 
      Height          =   1230
      Left            =   195
      TabIndex        =   0
      Top             =   135
      Width           =   1515
      _ExtentX        =   2672
      _ExtentY        =   2170
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      FrameStyle      =   1
      XP7_BorderColor =   15065045
      Caption         =   "Raised Out"
      Transparent     =   -1  'True
   End
   Begin Project1.Framez Framez3 
      Height          =   1065
      Left            =   120
      TabIndex        =   9
      Top             =   3420
      Width           =   5580
      _ExtentX        =   9843
      _ExtentY        =   3625
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      FrameStyle      =   13
      ForeColorDisabled=   0
      XP7_BorderColor =   -2147483632
      Caption         =   "Windows 7 - Button Shadow Border Color"
      Begin VB.TextBox Text1 
         Height          =   390
         Left            =   270
         TabIndex        =   10
         Text            =   "Text1"
         Top             =   450
         Width           =   5010
      End
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'' /////////////////////////////////////
'' //      Framez v1.14               //
'' //     Ed Wilk / Edgemeal 2009     //
'' /////////////////////////////////////
'
'Note:
' When you change the background image of a Framez container,
' (Form or Picture box) you need to call it's ReDraw property.
' Changing any of the Framez properties will also redraw the control.

Option Explicit

Private Sub Form_Unload(Cancel As Integer)
    Set Form1 = Nothing
End Sub

