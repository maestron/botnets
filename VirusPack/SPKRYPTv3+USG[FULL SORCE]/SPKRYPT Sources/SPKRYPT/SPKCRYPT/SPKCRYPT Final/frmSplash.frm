VERSION 5.00
Begin VB.Form frmSplash 
   BorderStyle     =   0  'None
   Caption         =   "Form2"
   ClientHeight    =   3000
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   6000
   LinkTopic       =   "Form2"
   Picture         =   "frmSplash.frx":0000
   ScaleHeight     =   3000
   ScaleWidth      =   6000
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin VB.Timer SplashTimer 
      Interval        =   3500
      Left            =   120
      Top             =   240
   End
End
Attribute VB_Name = "frmSplash"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private ReadyToUnload As Boolean
Private TimerExpired As Boolean
Private Declare Function SetWindowPos Lib "USER32" (ByVal hWnd As Long, ByVal hWndInsertAfter As Long, ByVal x As Long, ByVal Y As Long, ByVal cx As Long, ByVal cy As Long, ByVal wFlags As Long) As Long
Private Const SWP_NOMOVE = &H2
Private Const SWP_NOSIZE = &H1
Private Const HWND_TOPMOST = -1

Private Sub HideSplash()
frmMain.Show
Unload Me
End Sub

Public Sub ReadyToWork()
ReadyToUnload = True
If TimerExpired Then HideSplash
End Sub

Public Sub ShowSplash()
SplashTimer.Interval = 5500
    
Left = (Screen.Width - Width) / 2
Top = (Screen.Height - Height) / 2

SetWindowPos hWnd, HWND_TOPMOST, 0, 0, 0, 0, _
SWP_NOMOVE + SWP_NOSIZE
Me.Show
End Sub

Private Sub Form_Load()
  
frmSplash.Top = (Screen.Height * 0.85) / 2 - frmSplash.Height / 2
frmSplash.Left = Screen.Width / 2 - frmSplash.Width / 2
frmSplash.ReadyToWork

End Sub

' The minimum time has expired.
Private Sub SplashTimer_Timer()
TimerExpired = True
SplashTimer.Enabled = False
If ReadyToUnload Then HideSplash
End Sub



