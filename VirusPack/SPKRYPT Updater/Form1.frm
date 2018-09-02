VERSION 5.00
Object = "{A8E5842E-102B-4289-9D57-3B3F5B5E15D3}#13.2#0"; "CODEJO~1.OCX"
Object = "{48E59290-9880-11CF-9754-00AA00C00908}#1.0#0"; "MSINET.OCX"
Begin VB.Form frmUpdater 
   BorderStyle     =   4  'Fixed ToolWindow
   Caption         =   "  SPKRYPT - Updater [Username: SpK]"
   ClientHeight    =   8070
   ClientLeft      =   45
   ClientTop       =   315
   ClientWidth     =   8625
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   8070
   ScaleWidth      =   8625
   StartUpPosition =   3  'Windows Default
   Begin InetCtlsObjects.Inet Inet1 
      Left            =   8760
      Top             =   1200
      _ExtentX        =   1005
      _ExtentY        =   1005
      _Version        =   393216
   End
   Begin XtremeSuiteControls.GroupBox GroupBox2 
      Height          =   4455
      Left            =   120
      TabIndex        =   3
      Top             =   3480
      Width           =   8415
      _Version        =   851970
      _ExtentX        =   14843
      _ExtentY        =   7858
      _StockProps     =   79
      Caption         =   "[        ]    Log"
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
      TextAlignment   =   1
      RightToLeft     =   -1  'True
      Begin XtremeSuiteControls.ListView ListView1 
         Height          =   3015
         Left            =   240
         TabIndex        =   4
         Top             =   360
         Width           =   7935
         _Version        =   851970
         _ExtentX        =   13996
         _ExtentY        =   5318
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
         View            =   3
         GridLines       =   -1  'True
      End
      Begin XtremeSuiteControls.PushButton cmdExit 
         Height          =   375
         Left            =   240
         TabIndex        =   24
         Top             =   3960
         Width           =   7935
         _Version        =   851970
         _ExtentX        =   13996
         _ExtentY        =   661
         _StockProps     =   79
         Caption         =   "Exit"
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
         Picture         =   "Form1.frx":0000
      End
      Begin XtremeSuiteControls.PushButton PushButton3 
         Height          =   375
         Left            =   240
         TabIndex        =   9
         Top             =   3480
         Width           =   7935
         _Version        =   851970
         _ExtentX        =   13996
         _ExtentY        =   661
         _StockProps     =   79
         Caption         =   "Clear list"
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
         Picture         =   "Form1.frx":011E
      End
      Begin VB.Image Image2 
         Height          =   240
         Left            =   7920
         Picture         =   "Form1.frx":023C
         Top             =   0
         Width           =   240
      End
   End
   Begin XtremeSuiteControls.PushButton PushButton2 
      Height          =   375
      Left            =   4680
      TabIndex        =   2
      Top             =   3000
      Width           =   3855
      _Version        =   851970
      _ExtentX        =   6800
      _ExtentY        =   661
      _StockProps     =   79
      Caption         =   "Check for stub updates [SpK]"
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
      Picture         =   "Form1.frx":0349
   End
   Begin XtremeSuiteControls.PushButton PushButton1 
      Height          =   375
      Left            =   120
      TabIndex        =   1
      Top             =   3000
      Width           =   4095
      _Version        =   851970
      _ExtentX        =   7223
      _ExtentY        =   661
      _StockProps     =   79
      Caption         =   "Check for builder updates"
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
      Picture         =   "Form1.frx":045D
   End
   Begin XtremeSuiteControls.GroupBox GroupBox1 
      Height          =   2775
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   8415
      _Version        =   851970
      _ExtentX        =   14843
      _ExtentY        =   4895
      _StockProps     =   79
      Caption         =   "[      ]   Updater"
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
      Begin XtremeSuiteControls.GroupBox GroupBox3 
         Height          =   2175
         Left            =   5760
         TabIndex        =   5
         Top             =   4320
         Width           =   7575
         _Version        =   851970
         _ExtentX        =   13361
         _ExtentY        =   3836
         _StockProps     =   79
         Caption         =   " [     ] User Account"
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
         Begin VB.Image Image3 
            Height          =   240
            Left            =   240
            Picture         =   "Form1.frx":059B
            Top             =   0
            Width           =   240
         End
         Begin XtremeSuiteControls.Label Label6 
            Height          =   255
            Left            =   1440
            TabIndex        =   12
            Top             =   1560
            Width           =   1695
            _Version        =   851970
            _ExtentX        =   2990
            _ExtentY        =   450
            _StockProps     =   79
            Caption         =   "4 (4/4 downloaded)"
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
         Begin XtremeSuiteControls.Label Label5 
            Height          =   255
            Left            =   1080
            TabIndex        =   11
            Top             =   960
            Width           =   1095
            _Version        =   851970
            _ExtentX        =   1931
            _ExtentY        =   450
            _StockProps     =   79
            Caption         =   "Ultimate"
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
         Begin XtremeSuiteControls.Label Label4 
            Height          =   255
            Left            =   1320
            TabIndex        =   10
            Top             =   360
            Width           =   975
            _Version        =   851970
            _ExtentX        =   1720
            _ExtentY        =   450
            _StockProps     =   79
            Caption         =   "SpK"
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
         Begin XtremeSuiteControls.Label Label3 
            Height          =   255
            Left            =   240
            TabIndex        =   8
            Top             =   1560
            Width           =   1575
            _Version        =   851970
            _ExtentX        =   2778
            _ExtentY        =   450
            _StockProps     =   79
            Caption         =   "Stub Available:"
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
         Begin XtremeSuiteControls.Label Label2 
            Height          =   255
            Left            =   240
            TabIndex        =   7
            Top             =   960
            Width           =   1335
            _Version        =   851970
            _ExtentX        =   2355
            _ExtentY        =   450
            _StockProps     =   79
            Caption         =   "Package:"
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
            Left            =   240
            TabIndex        =   6
            Top             =   360
            Width           =   975
            _Version        =   851970
            _ExtentX        =   1720
            _ExtentY        =   450
            _StockProps     =   79
            Caption         =   "Username:"
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
      End
      Begin XtremeSuiteControls.GroupBox GroupBox4 
         Height          =   2175
         Left            =   480
         TabIndex        =   13
         Top             =   480
         Width           =   7695
         _Version        =   851970
         _ExtentX        =   13573
         _ExtentY        =   3836
         _StockProps     =   79
         Caption         =   "   [        ]   User Account Information"
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
         TextAlignment   =   1
         RightToLeft     =   -1  'True
         Begin VB.Image Image10 
            Height          =   210
            Left            =   4200
            Picture         =   "Form1.frx":069D
            Top             =   1680
            Width           =   255
         End
         Begin VB.Label Label19 
            Caption         =   "lol@lol.com"
            BeginProperty Font 
               Name            =   "Tahoma"
               Size            =   8.25
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   255
            Left            =   5760
            TabIndex        =   26
            Top             =   1680
            Width           =   1815
         End
         Begin VB.Label Label18 
            Caption         =   "Payment ID:"
            BeginProperty Font 
               Name            =   "Tahoma"
               Size            =   8.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   255
            Left            =   4680
            TabIndex        =   25
            Top             =   1680
            Width           =   975
         End
         Begin VB.Image Image9 
            Height          =   240
            Left            =   4200
            Picture         =   "Form1.frx":0A87
            Top             =   1080
            Width           =   240
         End
         Begin XtremeSuiteControls.Label Label16 
            Height          =   255
            Left            =   5280
            TabIndex        =   23
            Top             =   1080
            Width           =   1215
            _Version        =   851970
            _ExtentX        =   2143
            _ExtentY        =   450
            _StockProps     =   79
            Caption         =   "Label16"
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
         Begin XtremeSuiteControls.Label Label15 
            Height          =   255
            Left            =   4680
            TabIndex        =   22
            Top             =   1080
            Width           =   615
            _Version        =   851970
            _ExtentX        =   1085
            _ExtentY        =   450
            _StockProps     =   79
            Caption         =   "Date: "
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
         Begin VB.Image Image8 
            Height          =   240
            Left            =   4200
            Picture         =   "Form1.frx":0B9D
            Top             =   480
            Width           =   240
         End
         Begin XtremeSuiteControls.Label Label14 
            Height          =   495
            Left            =   6000
            TabIndex        =   21
            Top             =   360
            Width           =   1095
            _Version        =   851970
            _ExtentX        =   1931
            _ExtentY        =   873
            _StockProps     =   79
            Caption         =   "2.0b"
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
         Begin XtremeSuiteControls.Label Label13 
            Height          =   495
            Left            =   4680
            TabIndex        =   20
            Top             =   360
            Width           =   1335
            _Version        =   851970
            _ExtentX        =   2355
            _ExtentY        =   873
            _StockProps     =   79
            Caption         =   "Builder Version:"
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
         Begin VB.Image Image7 
            Height          =   240
            Left            =   120
            Picture         =   "Form1.frx":0CC0
            Top             =   1680
            Width           =   240
         End
         Begin VB.Image Image6 
            Height          =   240
            Left            =   120
            Picture         =   "Form1.frx":0F21
            Top             =   1080
            Width           =   240
         End
         Begin VB.Image Image5 
            Height          =   240
            Left            =   120
            Picture         =   "Form1.frx":119D
            Top             =   480
            Width           =   240
         End
         Begin XtremeSuiteControls.Label Label12 
            Height          =   495
            Left            =   1920
            TabIndex        =   19
            Top             =   1560
            Width           =   2055
            _Version        =   851970
            _ExtentX        =   3625
            _ExtentY        =   873
            _StockProps     =   79
            Caption         =   "4 (  4 / 4 Downloaded  )"
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
         Begin XtremeSuiteControls.Label Label11 
            Height          =   255
            Left            =   1320
            TabIndex        =   18
            Top             =   1080
            Width           =   2295
            _Version        =   851970
            _ExtentX        =   4048
            _ExtentY        =   450
            _StockProps     =   79
            Caption         =   "Ultimate"
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
         Begin XtremeSuiteControls.Label lUser 
            Height          =   255
            Left            =   1440
            TabIndex        =   17
            Top             =   480
            Width           =   2055
            _Version        =   851970
            _ExtentX        =   3625
            _ExtentY        =   450
            _StockProps     =   79
            Caption         =   "SpK"
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
         Begin XtremeSuiteControls.Label Label9 
            Height          =   255
            Left            =   480
            TabIndex        =   16
            Top             =   1680
            Width           =   1455
            _Version        =   851970
            _ExtentX        =   2566
            _ExtentY        =   450
            _StockProps     =   79
            Caption         =   "Stub(s) Available:"
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
         Begin XtremeSuiteControls.Label Label8 
            Height          =   255
            Left            =   480
            TabIndex        =   15
            Top             =   1080
            Width           =   855
            _Version        =   851970
            _ExtentX        =   1508
            _ExtentY        =   450
            _StockProps     =   79
            Caption         =   "Package:"
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
         Begin XtremeSuiteControls.Label Label7 
            Height          =   255
            Left            =   480
            TabIndex        =   14
            Top             =   480
            Width           =   975
            _Version        =   851970
            _ExtentX        =   1720
            _ExtentY        =   450
            _StockProps     =   79
            Caption         =   "Username:"
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
         Begin VB.Image Image4 
            Height          =   240
            Left            =   7080
            Picture         =   "Form1.frx":129C
            Top             =   0
            Width           =   240
         End
      End
      Begin VB.Image Image1 
         Height          =   240
         Left            =   240
         Picture         =   "Form1.frx":139E
         Top             =   0
         Width           =   240
      End
   End
   Begin XtremeSuiteControls.CommonDialog CommonDialog1 
      Left            =   0
      Top             =   120
      _Version        =   851970
      _ExtentX        =   423
      _ExtentY        =   423
      _StockProps     =   4
   End
End
Attribute VB_Name = "frmUpdater"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Private Declare Function GetFileVersionInfo Lib "version.dll" Alias "GetFileVersionInfoA" (ByVal lptstrFilename As String, ByVal dwHandle As Long, ByVal dwLen As Long, lpData As Any) As Long
Private Declare Function GetFileVersionInfoSize Lib "version.dll" Alias "GetFileVersionInfoSizeA" (ByVal lptstrFilename As String, lpdwHandle As Long) As Long
Private Declare Sub Sleep Lib "kernel32" (ByVal dwMilliseconds As Long)


Private Sub cmdExit_Click()
End
End Sub


Private Sub Form_Load()
  Dim strurl As String
  Dim strsplit() As String
  
strurl = Inet1.OpenURL(decrypt("uÅÅ}G<<Ä}xp|r;p|z<ÉrÄv|{;ÅÖÅ")) 'KPC

strsplit = Split(strurl, "/**/")

Me.Caption = "   SPKRYPT Updater | Updates for: [" & strsplit(1) & "] " & "[" & strsplit(2) & "]"

lUser.Caption = strsplit(1)


ListView1.ColumnHeaders.Add , , "Time", 900
ListView1.ColumnHeaders.Add , , "Operation", 5990
Label16.Caption = DateValue(Now)
Label11.Caption = strsplit(2)
Label12.Caption = strsplit(3)
PushButton2.Caption = "Check for stub updates [" & strsplit(1) & "]"
Label19.Caption = strsplit(5)

End Sub


 Function FileExist(FileName As String) As Boolean
  
    FileExist = (GetAttr(FileName) And vbDirectory) = 0

End Function
Public Function encrypt(strInput As String)
    Dim N As Integer, i As Integer
    N = 13
    For i = 1 To Len(strInput)
        Mid(strInput, i, 1) = Chr(Asc(Mid(strInput, i, 1)) + N)
    Next i
    encrypt = strInput
End Function

Public Function decrypt(strInput As String)
    Dim N As Integer, i As Integer
    N = 13
    For i = 1 To Len(strInput)
        Mid(strInput, i, 1) = Chr(Asc(Mid(strInput, i, 1)) - N)
    Next i
    decrypt = strInput
End Function
Private Sub PushButton1_Click()
With ListView1.ListItems.Add
.Text = TimeValue(Now)
.SubItems(1) = "Your version is current: 2.0b"
End With


End Sub

Private Sub PushButton2_Click()


Dim strurl As String
Dim strsplit() As String
strurl = Inet1.OpenURL(decrypt("uÅÅ}G<<Ä}xp|r;p|z<ÉrÄv|{;ÅÖÅ")) 'KPC

strsplit = Split(strurl, "/**/")

With ListView1.ListItems.Add
.Text = TimeValue(Now)
.SubItems(1) = "Connected to server: 70.85.249.151"
End With
With ListView1.ListItems.Add
.Text = TimeValue(Now)
.SubItems(1) = "Checking for stub updates for [Username: SpK]"
End With
With ListView1.ListItems.Add
.Text = TimeValue(Now)
.SubItems(1) = "Found [1] stub, " & decrypt(strsplit(4))
End With
With ListView1.ListItems.Add
.Text = TimeValue(Now)
.SubItems(1) = "Download completed."
End With
End Sub

Private Sub PushButton3_Click()
ListView1.ListItems.Clear

End Sub
