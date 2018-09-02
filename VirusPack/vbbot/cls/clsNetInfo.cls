VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "clsNetInfo"
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

Public Enum ServerTypes
    SV_TYPE_WORKSTATION = &H1
    SV_TYPE_SERVER = &H2 ' All Servers
    SV_TYPE_SQLSERVER = &H4  ' SQL Server
    SV_TYPE_DOMAIN_CTRL = &H8
    SV_TYPE_DOMAIN_BAKCTRL = &H10
    SV_TYPE_TIME_SOURCE = &H20
    SV_TYPE_AFP = &H40
    SV_TYPE_NOVELL = &H80
    SV_TYPE_DOMAIN_MEMBER = &H100
    SV_TYPE_PRINTQ_SERVER = &H200
    SV_TYPE_DIALIN_SERVER = &H400
    SV_TYPE_XENIX_SERVER = &H800
    SV_TYPE_SERVER_UNIX = SV_TYPE_XENIX_SERVER
    SV_TYPE_NT = &H1000
    SV_TYPE_WFW = &H2000
    SV_TYPE_SERVER_MFPN = &H4000
    SV_TYPE_SERVER_NT = &H8000
    SV_TYPE_POTENTIAL_BROWSER = &H10000
    SV_TYPE_BACKUP_BROWSER = &H20000
    SV_TYPE_MASTER_BROWSER = &H40000
    SV_TYPE_DOMAIN_MASTER = &H80000
    SV_TYPE_SERVER_OSF = &H100000
    SV_TYPE_SERVER_VMS = &H200000
    SV_TYPE_WINDOWS = &H400000  '/* Windows95 and above */
    SV_TYPE_DFS = &H800000  '/* Root of a DFS tree */
    SV_TYPE_CLUSTER_NT = &H1000000  '/* NT Cluster */
    SV_TYPE_DCE = &H10000000  '/* IBM DSS (Directory and Security Services) or equivalent */
    SV_TYPE_ALTERNATE_XPORT = &H20000000  '/* return list for alternate transport */
    SV_TYPE_LOCAL_LIST_ONLY = &H40000000  '/* Return local list only */
    SV_TYPE_DOMAIN_ENUM = &H80000000
    SV_TYPE_ALL = &HFFFFFFFF  '/* handy for NetServerEnum2 */
End Enum

Public Function ServerList(ServerType As ServerTypes) As String
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
            ServerList$ = vbNullString
            Exit Function
        End If
        Call NetApiBufferFree(BufPtr)
    Loop While nEntriesRead < nTotalEntries
    sTemp$ = ""
    For nK% = 0 To UBound(ServerNames())
        If Len(Trim$(Replace$(ServerNames(nK%), Chr$(0), ""))) > 0 Then sTemp$ = sTemp$ & ServerNames(nK%) & ", "
    Next nK%
    If Right$(sTemp$, 2) = ", " Then sTemp$ = Left$(sTemp$, Len(sTemp$) - 2)
    ServerList$ = sTemp$
Exit Function
ErrTrap:
    ServerList$ = vbNullString
End Function

Private Function PointerToString(lpszString As Long) As String
    Dim lpszStr1 As String, lpszStr2 As String, nRes As Long
    lpszStr1 = String(1000, "*")
    nRes = lstrcpy(lpszStr1, lpszString)
    lpszStr2 = (StrConv(lpszStr1, vbFromUnicode))
    PointerToString = Left(lpszStr2, InStr(lpszStr2, Chr$(0)) - 1)
End Function

