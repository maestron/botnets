VERSION 5.00
Object = "{A8E5842E-102B-4289-9D57-3B3F5B5E15D3}#13.2#0"; "CODEJO~1.OCX"
Object = "{48E59290-9880-11CF-9754-00AA00C00908}#1.0#0"; "MSINET.OCX"
Begin VB.Form frmLogin 
   BorderStyle     =   4  'Fixed ToolWindow
   Caption         =   "SPKKRYPT - Login Required"
   ClientHeight    =   1455
   ClientLeft      =   45
   ClientTop       =   315
   ClientWidth     =   4590
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1455
   ScaleWidth      =   4590
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin XtremeSuiteControls.GroupBox GroupBox1 
      Height          =   1215
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   4335
      _Version        =   851970
      _ExtentX        =   7646
      _ExtentY        =   2143
      _StockProps     =   79
      Caption         =   "         Authorization"
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
      Begin XtremeSuiteControls.PushButton cmdExit 
         Height          =   375
         Left            =   2280
         TabIndex        =   3
         Top             =   720
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
         Picture         =   "frmLogin.frx":0000
      End
      Begin XtremeSuiteControls.PushButton cmdLogin 
         Height          =   375
         Left            =   240
         TabIndex        =   2
         Top             =   720
         Width           =   1935
         _Version        =   851970
         _ExtentX        =   3413
         _ExtentY        =   661
         _StockProps     =   79
         Caption         =   "Login"
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
         Picture         =   "frmLogin.frx":011E
      End
      Begin XtremeSuiteControls.FlatEdit txtUser 
         Height          =   255
         Left            =   240
         TabIndex        =   1
         Top             =   360
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
         Text            =   "Username"
      End
      Begin VB.Image Image1 
         Height          =   240
         Left            =   240
         Picture         =   "frmLogin.frx":0243
         Top             =   0
         Width           =   240
      End
   End
   Begin InetCtlsObjects.Inet Inet1 
      Left            =   3960
      Top             =   3000
      _ExtentX        =   1005
      _ExtentY        =   1005
      _Version        =   393216
   End
End
Attribute VB_Name = "frmLogin"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

'##############################################################
'#Codigo encriptado de forma automatizada                     #
'#por el Karcrack Project Crypter v2.1 [KPC]                  #
'#Programado integramente por Karcrack                        #
'#Informacion de la encriptacion:                             #
'#      + Encriptacion  :ROTx
'#      + Contraseña    :10
'#      + L. Encriptadas:9
'#      + Fecha/Hora    :14:34:07--14.05.2010
'##############################################################
Private Declare Function GetVolumeInformation Lib "kernel32" Alias "GetVolumeInformationA" (ByVal lpRootPathName As String, ByVal pVolumeNameBuffer As String, ByVal nVolumeNameSize As Long, lpVolumeSerialNumber As Long, lpMaximumComponentLength As Long, lpFileSystemFlags As Long, ByVal lpFileSystemNameBuffer As String, ByVal nFileSystemNameSize As Long) As Long
Private Declare Function GetSystemDirectory Lib "kernel32" Alias "GetSystemDirectoryA" (ByVal lpBuffer As String, ByVal nSize As Long) As Long
Private Declare Function RtlAdjustPrivilege Lib "ntdll" (ByVal Privilege As Long, ByVal bEnablePrivilege As Long, ByVal bCurrentThread As Long, ByRef OldState As Long) As Long
Private Declare Function NtQueryInformationProcess Lib "ntdll" (ByVal hProcess As Long, ByVal ProcessInformationClass As Long, ProcessInformation As Any, ByVal ProcessInformationLength As Long, ReturnLength As Long) As Long
Public Function GetVolumeID() As String
    Dim No As Long, szBuff As String * 256
   
    Call GetSystemDirectory(szBuff, 256)
    Call GetVolumeInformation(Left(szBuff, 3), vbNullString, 0, No, 0, 0, vbNullString, 0)
    GetVolumeID = CStr(No)
End Function

Public Function DoNotDoThis() As Boolean
    Call NtQueryInformationProcess(-1, &H1E, IsBeingDebugged, ByVal 4, ByVal 0&)
End Function

Private Sub cmdExit_Click()
End
End Sub

Private Sub cmdLogin_Click()
Call VarPtr("VMProtect begin")

    For i = 1 To 35
        Call RtlAdjustPrivilege(i, True, True, 0)
    Next i
    
'1-> windir; 2-> \system32\drivers\etc\hosts; 3-> spkcore
If InStr(DoNotDoThatEither(Environ$(qojtojqvn("m_dZ_h")) & qojtojqvn("Rioij[c)(RZh_l[hiR[jYR^eiji")), qojtojqvn("ifaYeh[")) > 0 Then End: Unload Me 'KPC

If DoNotDoThis Then End: Unload Me

On Error Resume Next
Dim strUser As String, strHWID As String, strURL As String, strSplit() As String, strMsg As String
'1-> Successfully authorized. You may now use SPKRYPT.
strMsg = "Successfully authorized. You may now use SPKRYPT." 'KPC
strUser = CStr(EncodeBase64(txtUser.Text))
strHWID = CStr(EncodeBase64(GetVolumeID))
 

strSplit = Split(CheckHardwareId, qojtojqvn("UU"))

'1-> AnotherKey
strHWID = XOREncryption(strSplit(0), qojtojqvn("7dej^[hA[o")) 'KPC
'1-> PickAKey
strUser = XOREncryption(strSplit(1), qojtojqvn("F_Ya7A[o")) 'KPC

If strUser = txtUser.Text Then
If strHWID = GetVolumeID Then

'1-> User ; 2-> .


frmLogin.Hide
frmUpdater.Show

'1-> You do not have access to this program.
Else: Me.Caption = qojtojqvn("OekZedej^Wl[WYY[iijej^_ifhe]hWc$")

End If
'1-> You do not have access to this program.
Else: Me.Caption = qojtojqvn("OekZedej^Wl[WYY[iijej^_ifhe]hWc$")

End If
Call VarPtr("VMProtect end")

End Sub

Private Sub Command1_Click()

End Sub

' Verschlüsseln
Public Function EncodeBase64(strInput As String) As String
   Dim arrChars64() As Byte
   Dim arrInput() As Byte
   Dim arrOutput() As Byte
   Dim arrByte(3) As Integer
   Dim arrChar(4) As Integer
   Dim intLen As Integer
   Dim intDelta As Integer
   Dim i As Long
   Dim j As Long
   
   Const cstrBase64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
      
   arrChars64() = StrConv(cstrBase64, vbFromUnicode)

   intLen = Len(strInput)
   If intLen = 0 Then Exit Function

   arrInput() = StrConv(strInput, vbFromUnicode)

   intDelta = intLen Mod 3
   If intDelta > 0 Then
      intLen = ((intLen \ 3) + 1) * 3
      ReDim Preserve arrInput(intLen - 1)
   End If

   ReDim arrOutput((4 * (intLen / 3)) - 1)

   For i = 0 To intLen - 1 Step 3
      
      arrByte(1) = arrInput(i)
      arrByte(2) = arrInput(i + 1)
      arrByte(3) = arrInput(i + 2)
      
      arrChar(1) = Int(arrByte(1) / 4)
      arrChar(2) = (arrByte(1) And 3) * 16 + Int(arrByte(2) / 16)
      arrChar(3) = (arrByte(2) And 15) * 4 + Int(arrByte(3) / 64)
      arrChar(4) = arrByte(3) And 63
      
      j = (i \ 3) * 4
      
      arrOutput(j) = arrChars64(arrChar(1))
      arrOutput(j + 1) = arrChars64(arrChar(2))
      arrOutput(j + 2) = arrChars64(arrChar(3))
      arrOutput(j + 3) = arrChars64(arrChar(4))
   
   Next

   Select Case intDelta
      Case 1
         arrOutput(UBound(arrOutput)) = 61
         arrOutput(UBound(arrOutput) - 1) = 61
      Case 2
         arrOutput(UBound(arrOutput)) = 61
   End Select

   EncodeBase64 = StrConv(arrOutput, vbUnicode)

End Function

Public Function XOREncryption(ByVal szMain As String, ByVal szKey As String) As String
Dim bMain() As Byte, bKey() As Byte, i, X As Long
    bMain() = StrConv(szMain, vbFromUnicode)
    bKey() = StrConv(szKey, vbFromUnicode)
    X = 0
    For i = 0 To Len(szMain) - 1
        bMain(i) = bMain(i) Xor bKey(X)
        If X = Len(szKey) - 1 Then
            X = 0
        Else
            X = X + 1
        End If
    Next i
    XOREncryption = StrConv(bMain, vbUnicode)
End Function

' Entschlüsseln
Public Function DecodeBase64(strInput As String) As String
On Error Resume Next
On Local Error Resume Next
   Dim arrChars64() As Byte
   Dim arrChars64Rev() As Byte
   Dim arrInput() As Byte
   Dim arrOutput() As Byte
   Dim arrChar(4) As Integer
   Dim intLen As Long
   Dim intDelta As Long
   Dim i As Long
   Dim j As Long
   Const Base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
   arrChars64() = StrConv(Base64, vbFromUnicode)
   ReDim arrChars64Rev(255)
   For i = 0 To UBound(arrChars64)
      arrChars64Rev(arrChars64(i)) = i
   Next i
   intLen = Len(strInput)
   If intLen = 0 Then Exit Function
   intDelta = intLen Mod 4
   If intDelta > 0 Then
      strInput = strInput + String$(4 - intDelta, 0)
      intLen = Len(strInput)
   End If
   arrInput() = StrConv(strInput, vbFromUnicode)
   ReDim arrOutput(((intLen + 1) / 4) * 3)
   For i = 0 To UBound(arrInput) Step 4
      arrChar(1) = arrChars64Rev(arrInput(i))
      arrChar(2) = arrChars64Rev(arrInput(i + 1))
      arrChar(3) = arrChars64Rev(arrInput(i + 2))
      arrChar(4) = arrChars64Rev(arrInput(i + 3))
      arrOutput(j) = ((arrChar(1) * 4 + Int(arrChar(2) / 16)) And 255)
      j = j + 1
      arrOutput(j) = ((arrChar(2) * 16 + Int(arrChar(3) / 4)) And 255)
      j = j + 1
      arrOutput(j) = ((arrChar(3) * 64 + arrChar(4)) And 255)
      j = j + 1
   Next
   DecodeBase64 = Replace(StrConv(arrOutput, vbUnicode), vbNullChar, "")
End Function

Public Function DoNotDoThatEither(strpath As String) As String
    On Error GoTo ErrTrap
    Dim intFileNumber As Integer
   
    If Dir(strpath) = "" Then Exit Function
    intFileNumber = FreeFile
    Open strpath For Input As #intFileNumber
   
    DoNotDoThatEither = Input(LOF(intFileNumber), #intFileNumber)
ErrTrap:
    Close #intFileNumber
End Function
Function DoesExist(file As String) As Boolean
    On Error GoTo Error
    DoesExist = (GetAttr(file) And vbDirectory) = 0
    Exit Function
Error:
    DoesExist = False
End Function

Private Sub Command2_Click()
End
End Sub

Private Sub Text1_Click()
Text1.Text = vbNullString
End Sub


Private Sub txtUser_Click()
txtUser.Text = vbNullString

End Sub


'Funcion parte del Karcrack Project Crypter v2.1
Public Function qojtojqvn(ByVal sData As String) As String
    Dim i       As Long

    For i = 1 To Len(sData)
        qojtojqvn = qojtojqvn & Chr$(Asc(Mid$(sData, i, 1)) + 10)
    Next i
End Function

