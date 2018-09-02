Attribute VB_Name = "Module3"
Option Explicit
Public Declare Function GetSystemMenu Lib "user32" _
    (ByVal hwnd As Long, _
     ByVal bRevert As Long) As Long

Public Declare Function RemoveMenu Lib "user32" _
    (ByVal hMenu As Long, _
     ByVal nPosition As Long, _
     ByVal wFlags As Long) As Long
Public Const MF_BYPOSITION = &H400&


Public Sub DisableCloseWindowButton(frm As Form)
    Dim hSysMenu As Long
    hSysMenu = GetSystemMenu(frm.hwnd, 0)
    RemoveMenu hSysMenu, 6, MF_BYPOSITION
    RemoveMenu hSysMenu, 5, MF_BYPOSITION
End Sub

