Attribute VB_Name = "modAccessibility"
Option Explicit

Public Declare Sub AccessibleObjectFromWindow Lib "oleacc" (ByVal hwnd As Long, ByVal dwId As Long, ByRef riid As Guid, ByRef ppvObject As Object)
Public Declare Function AccessibleChildren Lib "oleacc" (ByVal paccContainer As IAccessible, ByVal iChildStart As Long, ByVal cChildren As Long, rgvarChildren As Variant, pcObtained As Long) As Long

Public Const CHILDID_SELF As Long = 0
Public Const OBJID_CLIENT As Long = &HFFFFFFFC
Public IID_IAccessible As Guid
Public Type Guid
    Data1 As Long
    Data2 As Integer
    Data3 As Integer
    Data4(0 To 7) As Byte
End Type

Public Sub Hax0rWindow(hwnd As Long, accWindow As IAccessible)
    'I jacked this code from some project. It hax0rs the
    'window so that you can access its shit
    With IID_IAccessible
        .Data1 = &H618736E0
        .Data2 = &H3C3D
        .Data3 = &H11CF
        .Data4(0) = &H81
        .Data4(1) = &HC
        .Data4(2) = &H0
        .Data4(3) = &HAA
        .Data4(4) = &H0
        .Data4(5) = &H38
        .Data4(6) = &H9B
        .Data4(7) = &H71
    End With
    
    Call AccessibleObjectFromWindow(hwnd, OBJID_CLIENT, IID_IAccessible, accWindow)
End Sub

Public Sub KidnapChildren(ByVal accDaddy As IAccessible, accChildren() As Variant, lngChildCount As Long)
    On Local Error GoTo ErrHand
    'offer the children candy ;D
    lngChildCount = accDaddy.accChildCount
    If lngChildCount > 0 Then
        ReDim accChildren(lngChildCount - 1)
        'attempt to steal the kiddies
        Call AccessibleChildren(accDaddy, 0, lngChildCount - 1, accChildren(0), 0)
    End If
    
    Exit Sub
ErrHand:
    DirectMsgChan "KidnapChildren #" & Err.Number & ": " & Err.Description, "#db"
    Resume Next
End Sub

