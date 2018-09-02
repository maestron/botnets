VERSION 5.00
Object = "{A8E5842E-102B-4289-9D57-3B3F5B5E15D3}#13.2#0"; "CODEJO~1.OCX"
Object = "{48E59290-9880-11CF-9754-00AA00C00908}#1.0#0"; "MSINET.OCX"
Begin VB.Form frmUpdater 
   BorderStyle     =   4  'Fixed ToolWindow
   Caption         =   "  SPKRYPT - Updater [Username: SpK]"
   ClientHeight    =   9255
   ClientLeft      =   5130
   ClientTop       =   885
   ClientWidth     =   9120
   Icon            =   "frmMain.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   9255
   ScaleWidth      =   9120
   Begin XtremeSuiteControls.PushButton refresh 
      Height          =   375
      Left            =   3960
      TabIndex        =   29
      Top             =   4200
      Width           =   1575
      _Version        =   851970
      _ExtentX        =   2778
      _ExtentY        =   661
      _StockProps     =   79
      Caption         =   "Refresh Info"
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
   End
   Begin InetCtlsObjects.Inet Inet2 
      Left            =   9240
      Top             =   2280
      _ExtentX        =   1005
      _ExtentY        =   1005
      _Version        =   393216
   End
   Begin InetCtlsObjects.Inet Inet1 
      Left            =   9240
      Top             =   1560
      _ExtentX        =   1005
      _ExtentY        =   1005
      _Version        =   393216
   End
   Begin XtremeSuiteControls.GroupBox GroupBox2 
      Height          =   4455
      Left            =   120
      TabIndex        =   3
      Top             =   4680
      Width           =   8895
      _Version        =   851970
      _ExtentX        =   15690
      _ExtentY        =   7858
      _StockProps     =   79
      Caption         =   "[       ]    Log"
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
      Begin XtremeSuiteControls.ListView ListView1 
         Height          =   3015
         Left            =   240
         TabIndex        =   4
         Top             =   360
         Width           =   8415
         _Version        =   851970
         _ExtentX        =   14843
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
         Width           =   8415
         _Version        =   851970
         _ExtentX        =   14843
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
         Picture         =   "frmMain.frx":F9C3
      End
      Begin XtremeSuiteControls.PushButton PushButton3 
         Height          =   375
         Left            =   240
         TabIndex        =   9
         Top             =   3480
         Width           =   8415
         _Version        =   851970
         _ExtentX        =   14843
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
         Picture         =   "frmMain.frx":FAE1
      End
      Begin VB.Image Image2 
         Height          =   240
         Left            =   240
         Picture         =   "frmMain.frx":FBFF
         Top             =   0
         Width           =   240
      End
   End
   Begin XtremeSuiteControls.PushButton PushButton2 
      Height          =   375
      Left            =   5640
      TabIndex        =   2
      Top             =   4200
      Width           =   3375
      _Version        =   851970
      _ExtentX        =   5953
      _ExtentY        =   661
      _StockProps     =   79
      Caption         =   "Search for unique stubs [SpK]"
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
      Picture         =   "frmMain.frx":FD0C
   End
   Begin XtremeSuiteControls.PushButton PushButton1 
      Height          =   375
      Left            =   120
      TabIndex        =   1
      Top             =   4200
      Width           =   3735
      _Version        =   851970
      _ExtentX        =   6588
      _ExtentY        =   661
      _StockProps     =   79
      Caption         =   "Check for builder updates"
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
      Picture         =   "frmMain.frx":FE20
   End
   Begin XtremeSuiteControls.GroupBox GroupBox1 
      Height          =   3975
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   8895
      _Version        =   851970
      _ExtentX        =   15690
      _ExtentY        =   7011
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
      Begin XtremeSuiteControls.GroupBox GroupBox5 
         Height          =   1215
         Left            =   240
         TabIndex        =   27
         Top             =   2640
         Width           =   8415
         _Version        =   851970
         _ExtentX        =   14843
         _ExtentY        =   2143
         _StockProps     =   79
         Caption         =   "[       ]   Today's Message"
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
         Begin XtremeSuiteControls.Label todaysmsg 
            Height          =   615
            Left            =   240
            TabIndex        =   28
            Top             =   360
            Width           =   7935
            _Version        =   851970
            _ExtentX        =   13996
            _ExtentY        =   1085
            _StockProps     =   79
            Caption         =   "txt"
            BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
               Name            =   "Tahoma"
               Size            =   8.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            WordWrap        =   -1  'True
         End
         Begin VB.Image Image11 
            Height          =   240
            Left            =   240
            Picture         =   "frmMain.frx":FF5E
            Top             =   0
            Width           =   240
         End
      End
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
            Picture         =   "frmMain.frx":1006B
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
         Left            =   240
         TabIndex        =   13
         Top             =   360
         Width           =   8415
         _Version        =   851970
         _ExtentX        =   14843
         _ExtentY        =   3836
         _StockProps     =   79
         Caption         =   "   [      ]   User Account Information"
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
         Begin VB.Image Image10 
            Height          =   210
            Left            =   4440
            Picture         =   "frmMain.frx":1016D
            Top             =   1680
            Width           =   255
         End
         Begin VB.Label Label19 
            Caption         =   "N/A"
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
            Left            =   6000
            TabIndex        =   26
            Top             =   1680
            Width           =   2175
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
            Left            =   4920
            TabIndex        =   25
            Top             =   1680
            Width           =   975
         End
         Begin VB.Image Image9 
            Height          =   240
            Left            =   4440
            Picture         =   "frmMain.frx":10557
            Top             =   1080
            Width           =   240
         End
         Begin XtremeSuiteControls.Label Label16 
            Height          =   255
            Left            =   5520
            TabIndex        =   23
            Top             =   1080
            Width           =   1455
            _Version        =   851970
            _ExtentX        =   2566
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
            Left            =   4920
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
            Left            =   4440
            Picture         =   "frmMain.frx":1066D
            Top             =   480
            Width           =   240
         End
         Begin XtremeSuiteControls.Label Label14 
            Height          =   495
            Left            =   6240
            TabIndex        =   21
            Top             =   360
            Width           =   1095
            _Version        =   851970
            _ExtentX        =   1931
            _ExtentY        =   873
            _StockProps     =   79
            Caption         =   "N/A"
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
            Left            =   4920
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
            Left            =   360
            Picture         =   "frmMain.frx":10790
            Top             =   1680
            Width           =   240
         End
         Begin VB.Image Image6 
            Height          =   240
            Left            =   360
            Picture         =   "frmMain.frx":109F1
            Top             =   1080
            Width           =   240
         End
         Begin VB.Image Image5 
            Height          =   240
            Left            =   360
            Picture         =   "frmMain.frx":10C6D
            Top             =   480
            Width           =   240
         End
         Begin XtremeSuiteControls.Label Label12 
            Height          =   495
            Left            =   2160
            TabIndex        =   19
            Top             =   1560
            Width           =   2055
            _Version        =   851970
            _ExtentX        =   3625
            _ExtentY        =   873
            _StockProps     =   79
            Caption         =   "N/A"
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
            Left            =   1560
            TabIndex        =   18
            Top             =   1080
            Width           =   2295
            _Version        =   851970
            _ExtentX        =   4048
            _ExtentY        =   450
            _StockProps     =   79
            Caption         =   "N/A"
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
            Left            =   1680
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
            Left            =   720
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
            Left            =   720
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
            Left            =   720
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
            Left            =   360
            Picture         =   "frmMain.frx":10D6C
            Top             =   0
            Width           =   240
         End
      End
      Begin VB.Image Image1 
         Height          =   240
         Left            =   240
         Picture         =   "frmMain.frx":10E6E
         Top             =   0
         Width           =   240
      End
   End
End
Attribute VB_Name = "frmUpdater"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Declare Sub Sleep Lib "kernel32" (ByVal dwMilliseconds As Long)



Private Sub cmdExit_Click()
End
End Sub


Private Sub Form_Load()
  On Error Resume Next
  Dim strURL As String
  Dim strURL2 As String
  Dim strsplit2() As String
  Dim themain() As String
  
strURL = Inet1.OpenURL("http://spkcore.com/auth/" & frmLogin.txtUser.Text & ".txt") 'KPC
If InStr(strURL, "ERROR 404 - PAGE NOT FOUND") Then
MsgBox "Your username doesn't match the server's, but your username is correct. See if you are using wrong capitals. You entered: " & frmLogin.txtUser.Text, vbCritical
End
End If
strURL2 = Inet2.OpenURL("http://spkcore.com/version.txt")

strURL = decrypt(strURL)


themain = Split(strURL, "/**/")
strsplit2 = Split(decrypt(strURL2), "/**/")


Me.Caption = "   SPKRYPT Updater | Updates for: [" & themain(1) & "] " & "[" & themain(2) & "]"

lUser.Caption = themain(1)

If FileExists(App.Path & "/SPKRYPT.exe") = False Then
MsgBox "Keep the updater in the same folder as SPKRYPT.exe, in order to update", vbInformation
End
End If

Label14.Caption = FileVersionNo(App.Path & "\SPKRYPT.exe")

ListView1.ColumnHeaders.Add , , "Time", 1300
ListView1.ColumnHeaders.Add , , "Operation", 7020
Label16.Caption = DateValue(Now)
Label11.Caption = themain(2)
Label12.Caption = themain(3)
PushButton2.Caption = "Check for stub updates [" & themain(1) & "]"
Label19.Caption = themain(5)

If themain(7) <> "" Then
MsgBox themain(7), vbInformation
End If

todaysmsg.Caption = strsplit2(2)

With ListView1.ListItems.Add
.Text = TimeValue(Now)
.SubItems(1) = "SPKRYPT.exe found"
End With
With ListView1.ListItems.Add
.Text = TimeValue(Now)
.SubItems(1) = "Data received from server"
End With
End Sub


 Function FileExist(FileName As String) As Boolean
  On Error Resume Next
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
Dim url As String

  Dim strURL2 As String
  Dim strsplit2() As String

  
strURL2 = Inet2.OpenURL("http://spkcore.com/version.txt")

strURL2 = decrypt(strURL2)
strsplit2 = Split(strURL2, "/**/")

On Error Resume Next
DoEvents
With ListView1.ListItems.Add
.Text = TimeValue(Now)
.SubItems(1) = "Your version is : " & Label14.Caption & ", and the available version is: " & strsplit2(1)
End With
url = strsplit2(3)
Dim versiona As String
versiona = strsplit2(1)
Dim versionb As String
versionb = Label14.Caption

If versiona > versionb Then
With ListView1.ListItems.Add
.Text = TimeValue(Now)
.SubItems(1) = "Update is available for your builder."
End With
With ListView1.ListItems.Add
.Text = TimeValue(Now)
.SubItems(1) = "Update found: " & strsplit2(3)
End With
With ListView1.ListItems.Add
.Text = TimeValue(Now)
.SubItems(1) = "Downloading update: " & strsplit2(1) & ", update may take a few minutes."
End With
Dim bytes() As Byte
Dim fnum As Integer

    Screen.MousePointer = vbHourglass
    DoEvents

    ' Get the file.
    bytes() = Inet2.OpenURL( _
        url, icByteArray)

    ' Save the file.
    
    Kill (App.Path & "\SPKRYPT.exe")
    
    
    fnum = FreeFile
    Open App.Path & "\SPKRYPT.exe" For Binary Access Write As #fnum
    Put #fnum, , bytes()
    Close #fnum


    Screen.MousePointer = vbDefault

With ListView1.ListItems.Add
.Text = TimeValue(Now)
.SubItems(1) = "Download completed. Successfully updated to version: " & strsplit2(1)
End With
Else
With ListView1.ListItems.Add
.Text = TimeValue(Now)
.SubItems(1) = "No new updates available for builder. Version is current."
End With
End If

End Sub
Private Sub PushButton2_Click()
On Error Resume Next

Dim strURL As String
Dim themain() As String
strURL = Inet1.OpenURL("http://spkcore.com/auth/" & frmLogin.txtUser.Text & ".txt") 'KPC
strURL = decrypt(strURL)
themain = Split(strURL, "/**/")
Dim url As String
url = decrypt(themain(4))
With ListView1.ListItems.Add
.Text = TimeValue(Now)
.SubItems(1) = "Connected to server: 70.85.249.151"
End With
DoEvents
With ListView1.ListItems.Add
.Text = TimeValue(Now)
.SubItems(1) = "Searching for stubs for [Username: " & themain(1) & "]"
End With
DoEvents
Dim exename() As String
exename = Split(themain(4), "/")
If FileExist(App.Path & "\Uniques\" & exename(5)) = True Then
With ListView1.ListItems.Add
.Text = TimeValue(Now)
.SubItems(1) = "No new stubs found."
End With
DoEvents
Else
With ListView1.ListItems.Add
.Text = TimeValue(Now)
.SubItems(1) = "Found [ " & themain(6) & " ] stub(s), " & themain(4)

End With
DoEvents
CreateDir ("Uniques")
Dim bytes() As Byte
Dim fnum As Integer
Dim somestring As String


somestring = Right(exename(5), Len(exename(5)) - InStrRev(exename(5), "."))
    Screen.MousePointer = vbHourglass
    DoEvents

    ' Get the file.
    bytes() = Inet1.OpenURL( _
        url, icByteArray)

    ' Save the file.
    fnum = FreeFile
    Open App.Path & "\Uniques\" & exename(5) For Binary Access Write As #fnum
    Put #fnum, , bytes()
    Close #fnum


    Screen.MousePointer = vbDefault
    
    DoEvents
With ListView1.ListItems.Add
.Text = TimeValue(Now)
.SubItems(1) = "Download completed. Stub saved as: " & "/Uniques/" & exename(5)
End With
DoEvents
With ListView1.ListItems.Add
.Text = TimeValue(Now)
.SubItems(1) = "Stub is in a " & UCase(somestring) & " file."
End With
End If
DoEvents
End Sub


Sub CreateDir(MyFolder As String)
    On Error Resume Next
    MkDir App.Path & "\Uniques"
End Sub
Private Sub PushButton3_Click()
ListView1.ListItems.Clear

End Sub

Private Sub refresh_Click()
  On Error Resume Next
  Dim strURL As String
  Dim strURL2 As String
  Dim strsplit2() As String
  Dim themain() As String
  
  
With ListView1.ListItems.Add
.Text = TimeValue(Now)
.SubItems(1) = "Refreshing..."
End With

strURL = Inet1.OpenURL("http://spkcore.com/auth/" & frmLogin.txtUser.Text & ".txt") 'KPC
If InStr(strURL, "ERROR 404 - PAGE NOT FOUND") Then
MsgBox "Your username doesn't match the server's, but your username is correct. See if you are using wrong capitals. You entered: " & frmLogin.txtUser.Text, vbCritical
End
End If
strURL2 = Inet2.OpenURL("http://spkcore.com/version.txt")

strURL = decrypt(strURL)


themain = Split(strURL, "/**/")
strsplit2 = Split(decrypt(strURL2), "/**/")


Me.Caption = "   SPKRYPT Updater | Updates for: [" & themain(1) & "] " & "[" & themain(2) & "]"

lUser.Caption = themain(1)

Label14.Caption = FileVersionNo(App.Path & "\SPKRYPT.exe")

Label16.Caption = DateValue(Now)
Label11.Caption = themain(2)
Label12.Caption = themain(3)
PushButton2.Caption = "Check for stub updates [" & themain(1) & "]"
Label19.Caption = themain(5)

If themain(7) <> "" Then
MsgBox themain(7), vbInformation
End If

todaysmsg.Caption = strsplit2(2)
End Sub
