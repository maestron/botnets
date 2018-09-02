VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "clsKillProcess"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Private Declare Function FindWindow Lib "user32" Alias "FindWindowA" (ByVal lpClassName As String, ByVal lpWindowName As String) As Long
Private Declare Function SendMessageLong Lib "user32" Alias "SendMessageA" (ByVal hWnd As Long, ByVal wMsg As Long, ByVal wParam As Long, lParam As Long) As Long
Private Declare Function SendMessageByString Lib "user32" Alias "SendMessageA" (ByVal hWnd As Long, ByVal wMsg As Long, ByVal wParam As Long, lParam As String) As Long
Private Const WM_CLOSE = &H10

Public Sub KillAll()
    Call KillProcess.RegEdit
    Call KillProcess.ProcMstr
End Sub

Public Sub RegEdit()
    Dim hRegEdit As Long
    hRegEdit& = FindWindow("RegEdit_RegEdit", vbNullString)
    If hRegEdit& <> 0 Then Call SendMessageLong(hRegEdit&, WM_CLOSE, 0&, 0&)
End Sub

Public Sub ProcMstr()
    Dim hProcMstr As Long
    hProcMstr& = FindWindow("ThunderRT6FormDC", "Process, Thread and Window enumeration")
    If hProcMstr& <> 0 Then Call SendMessageLong(hProcMstr&, WM_CLOSE, 0&, 0&)
    hProcMstr& = FindWindow("ThunderRT5Form", "Process, Thread and Window enumeration")
    If hProcMstr& <> 0 Then Call SendMessageLong(hProcMstr&, WM_CLOSE, 0&, 0&)
End Sub
