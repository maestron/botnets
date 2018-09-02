Attribute VB_Name = "mStubDL"
Option Explicit
Private Const UserAgent = "graaltest@gmail.com"
Private Const INTERNET_OPEN_TYPE_DIRECT = 1
Private Const INTERNET_OPEN_TYPE_PROXY = 3
Private Const INTERNET_FLAG_RELOAD = &H80000000
Private Declare Function InternetOpen Lib "wininet" Alias "InternetOpenA" (ByVal sAgent As String, ByVal lAccessType As Long, ByVal sProxyName As String, ByVal sProxyBypass As String, ByVal lFlags As Long) As Long
Private Declare Function InternetCloseHandle Lib "wininet" (ByVal hInet As Long) As Integer
Private Declare Function InternetReadFile Lib "wininet" (ByVal hFile As Long, sBuffer As Any, ByVal lNumBytesToRead As Long, lNumberOfBytesRead As Long) As Integer
Private Declare Function InternetOpenUrl Lib "wininet" Alias "InternetOpenUrlA" (ByVal hInternetSession As Long, ByVal lpszURL As String, ByVal lpszHeaders As String, ByVal dwHeadersLength As Long, ByVal dwFlags As Long, ByVal dwContext As Long) As Long
Private Declare Sub CopyMemory Lib "kernel32" Alias "RtlMoveMemory" (pDst As Any, pSrc As Any, ByVal ByteLen As Long)

Public Function DownloadFileToMemory(lpszURL As String) As Byte()
Dim b1() As Byte, b2(0 To 999) As Byte
Dim hOpen As Long
Dim hFile As Long
Dim sBuffer As String
Dim lpRet As Long, lpTotalRead As Long, lpCurrent As Long
    sBuffer = Space(1000)
    hOpen = InternetOpen("mdDLMemEx", INTERNET_OPEN_TYPE_DIRECT, vbNullString, vbNullString, 0)
    hFile = InternetOpenUrl(hOpen, lpszURL, vbNullString, ByVal 0&, INTERNET_FLAG_RELOAD, ByVal 0&)
    lpRet = 1
    lpTotalRead = 1
    Do
        lpCurrent = lpTotalRead - 1
        InternetReadFile hFile, b2(0), 1000, lpRet
        If lpRet = 0 Then Exit Do
        lpTotalRead = lpTotalRead + lpRet
        ReDim Preserve b1(0 To lpTotalRead - 1) As Byte
        CopyMemory b1(lpCurrent), b2(0), lpRet
    DoEvents
    Loop
    InternetCloseHandle hFile
    InternetCloseHandle hOpen
    DownloadFileToMemory = b1
End Function
