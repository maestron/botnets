Attribute VB_Name = "modPublic"
Option Explicit

Public InIDE As Integer
Public SocketCount As Integer
Public SocketStatus() As String
Public BNC_RELAY As Integer

Public Function Crypt(Optional sString As String) As String
    On Error GoTo ErrTrap
    Dim sTemp As String, nK As Integer
    For nK% = 1 To Len(sString$)
        sTemp$ = sTemp$ & Chr$(Asc%(Mid$(sString$, nK%, 1)) + 20)
    Next nK%
    Crypt$ = sTemp$
Exit Function
ErrTrap:
End Function

Public Function DeCrypt(Optional sString As String) As String
    On Error GoTo ErrTrap
    Dim sTemp As String, nK As Integer
    For nK% = 1 To Len(sString$)
        sTemp$ = sTemp$ & Chr$(Asc%(Mid$(sString$, nK%, 1)) - 20)
    Next nK%
    DeCrypt$ = sTemp$
Exit Function
ErrTrap:
End Function

Public Function CreateSocket(sReason As String) As Integer
    On Error GoTo ErrTrap
    Dim nK As Integer
    For nK% = 0 To SocketCount%
        If frmMain.socket(nK%).State = sckClosed Then Call KillSocket(nK%)
    Next nK%
    SocketCount% = SocketCount% + 1
    Call Load(frmMain.socket(SocketCount%))
    If SocketCount% <> 0 Then
        ReDim Preserve SocketStatus(UBound(SocketStatus()) + 1)
    Else
        ReDim SocketStatus(1)
    End If
    SocketStatus(SocketCount%) = sReason$
    CreateSocket% = SocketCount%
Exit Function
ErrTrap:
    If Err.Number = 9 Then Resume Next
    If Err.Number = 360 Then Resume Next
End Function

Public Sub KillSocket(nIndex As Integer)
    On Error GoTo ErrTrap
    If nIndex% = 0 Then Exit Sub
    SocketStatus(nIndex%) = ""
    Call CleanSocketStatus(nIndex%)
Exit Sub
ErrTrap:
    If Err.Number = 9 Then Resume Next
    If Err.Number = 362 Then Resume Next
End Sub

Private Sub CleanSocketStatus(nIndex As Integer)
    On Error GoTo ErrTrap
    Dim sTempStatus() As String, nK As Integer, nCount As Integer
    Call Unload(frmMain.socket(nIndex%))
    SocketStatus(nIndex%) = ""
    ReDim sTempStatus(UBound(SocketStatus()) - 1)
    For nK% = 0 To UBound(SocketStatus())
        If SocketStatus(nK%) <> "" Then
            sTempStatus(nCount%) = SocketStatus(nK%)
            nCount% = nCount% + 1
            SocketCount% = SocketCount% - 1
        End If
    Next nK%
    ReDim SocketStatus(UBound(sTempStatus()))
    For nK% = 0 To UBound(sTempStatus())
        SocketStatus(nK%) = sTempStatus(nK%)
    Next nK%
    If SocketCount% < 1 Then SocketCount% = 0
    For nK% = 0 To SocketCount%
        If SocketStatus(nK%) = "Bridge" Then Bot.BridgeIndex = nK%
    Next nK%
Exit Sub
ErrTrap:
    If Err.Number = 9 Then Resume Next
    If Err.Number = 362 Then Resume Next
End Sub
