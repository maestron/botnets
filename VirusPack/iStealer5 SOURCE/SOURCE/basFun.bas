Attribute VB_Name = "basFun"
Option Explicit

'Hardwareid
Private Const READ_CONTROL As Long = &H20000
Private Const STANDARD_RIGHTS_READ As Long = (READ_CONTROL)
Private Const KEY_QUERY_VALUE As Long = &H1
Private Const KEY_ENUMERATE_SUB_KEYS As Long = &H8
Private Const KEY_NOTIFY As Long = &H10
Private Const SYNCHRONIZE As Long = &H100000
Private Const KEY_WOW64_64KEY As Long = &H100  '// 64-bit Key
Private Const KEY_READ As Long = ((STANDARD_RIGHTS_READ Or KEY_QUERY_VALUE Or KEY_ENUMERATE_SUB_KEYS Or KEY_NOTIFY) And (Not SYNCHRONIZE))

Private Const HKEY_LOCAL_MACHINE As Long = &H80000002
Private Const REG_SZ = 1
Private Const ERROR_SUCCESS = 0&

Private Declare Function RegOpenKeyEx Lib "advapi32.dll" Alias "RegOpenKeyExA" (ByVal hKey As Long, ByVal lpSubKey As String, ByVal ulOptions As Long, ByVal samDesired As Long, ByRef phkResult As Long) As Long
Private Declare Function RegQueryValueEx Lib "advapi32.dll" Alias "RegQueryValueExA" (ByVal hKey As Long, ByVal lpValueName As String, ByVal lpReserved As Long, ByRef lpType As Long, ByRef lpData As Any, ByRef lpcbData As Long) As Long
Private Declare Function RegCloseKey Lib "advapi32.dll" (ByVal hKey As Long) As Long

'HDD
Private Declare Function GetVolumeInformation Lib "kernel32" Alias "GetVolumeInformationA" (ByVal lpRootPathName As String, ByVal lpVolumeNameBuffer As String, ByVal nVolumeNameSize As Long, lpVolumeSerialNumber As Long, lpMaximumComponentLength As Long, lpFileSystemFlags As Long, ByVal lpFileSystemNameBuffer As String, ByVal nFileSystemNameSize As Long) As Long
Private Declare Function GetDriveType Lib "kernel32" Alias "GetDriveTypeA" (ByVal nDrive As String) As Long

'Internet
Public Declare Function InternetOpen Lib "wininet" Alias "InternetOpenA" (ByVal sAgent As String, ByVal lAccessType As Long, ByVal sProxyName As String, ByVal sProxyBypass As String, ByVal lFlags As Long) As Long
Public Declare Function InternetOpenUrl Lib "wininet" Alias "InternetOpenUrlA" (ByVal hInternetSession As Long, ByVal lpszUrl As String, ByVal lpszHeaders As String, ByVal dwHeadersLength As Long, ByVal dwFlags As Long, ByVal dwContext As Long) As Long
Public Declare Function InternetConnect Lib "wininet.dll" Alias "InternetConnectA" (ByVal hInternetSession As Long, ByVal sServerName As String, ByVal nServerPort As Integer, ByVal sUserName As String, ByVal sPassword As String, ByVal lService As Long, ByVal lFlags As Long, ByVal lContext As Long) As Long
Public Declare Function HttpOpenRequest Lib "wininet.dll" Alias "HttpOpenRequestA" (ByVal hHttpSession As Long, ByVal sVerb As String, ByVal sObjectName As String, ByVal sVersion As String, ByVal sReferer As String, ByVal something As Long, ByVal lFlags As Long, ByVal lContext As Long) As Long
Public Declare Function HttpSendRequest Lib "wininet.dll" Alias "HttpSendRequestA" (ByVal hHttpRequest As Long, ByVal sHeaders As String, ByVal lHeadersLength As Long, ByVal sOptional As String, ByVal lOptionalLength As Long) As Long
Public Declare Function InternetReadFile Lib "wininet" (ByVal hFile As Long, ByVal sBuffer As String, ByVal lNumBytesToRead As Long, lNumberOfBytesRead As Long) As Integer
Public Declare Function InternetCloseHandle Lib "wininet.dll" (ByVal hInet As Long) As Integer
Public Const INTERNET_OPEN_TYPE_DIRECT = 1
Public Const INTERNET_FLAG_RELOAD = &H80000000

'Build
Public Declare Sub CopyMemory Lib "kernel32" Alias "RtlMoveMemory" (pDst As Any, pSrc As Any, ByVal ByteLen As Long)

Public Sub CheckHardwareId()
    Dim hKey As Long, i As Integer
    Dim szGuid As String, szTmp1 As String, szTmp2 As String
    Dim hOpen As Long, hConnection As Long, hRequest As Long
    Dim HardwareID As String, sBuffer As String * 50, clearBuffer As String, lNumberOfBytesRead As Long
    Dim Serial As Long, strSerial As String, CheckSum As Long
    Dim parts() As String
    Dim strError As String
    
    strError = "This copy don't have license." & vbNewLine & "If you bought this program you should contact with the seller."

    If RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\Microsoft\Cryptography", 0, KEY_READ Or KEY_WOW64_64KEY, hKey) <> ERROR_SUCCESS Then End
    szGuid = String(256, Chr(0))
    If RegQueryValueEx(hKey, "MachineGuid", 0&, REG_SZ, ByVal szGuid, 256) <> ERROR_SUCCESS Then End
    RegCloseKey hKey
    
    If GetDriveType("C:\") <> 3 Or GetVolumeInformation("C:\", vbNullString, 0, Serial, 0, 0, vbNullString, 0) = False Then End
    
    szGuid = Replace(szGuid, "-", "")
    szTmp1 = Mid(szGuid, 8, 12)
    szTmp2 = Mid(szGuid, 12, 12)
    For i = 1 To 12
        HardwareID = HardwareID & Hex(Asc(Mid(szTmp1, i, 1)) + Asc(Mid(szTmp2, i, 1)))
    Next i
    
    strSerial = Trim(Str(Abs(Serial)))
    For i = Len(strSerial) To 10
        strSerial = strSerial & "0"
    Next i
    HardwareID = HardwareID & strSerial
    
    CheckSum = 0
    For i = 24 To 34
        CheckSum = CheckSum + (Val(Mid(HardwareID, i + 1, 1)) * i)
    Next i

    hOpen = InternetOpen("HID", INTERNET_OPEN_TYPE_DIRECT, vbNullString, vbNullString, 0)
    hConnection = InternetConnect(hOpen, "Your Website", 80, "", "", 3, 0, 0)
    hRequest = HttpOpenRequest(hConnection, "GET", "/HID3.php?id=" & HardwareID, 0, 0, 0, 0, 0)
    HttpSendRequest hRequest, vbNullString, 0, 0, 0
    InternetReadFile hRequest, sBuffer, 50, lNumberOfBytesRead
    InternetCloseHandle hOpen
    InternetCloseHandle hConnection
    InternetCloseHandle hRequest
    
    If lNumberOfBytesRead = 0 Then
        MsgBox "The program can't connect to internet.", vbCritical
        End
    End If

    clearBuffer = Left(sBuffer, lNumberOfBytesRead)
    parts = Split(clearBuffer, "|", , vbTextCompare)

    If parts(0) = "OK" Then
        If parts(2) = CheckSum Then
            frmAbout.Label7.Caption = "Licensed to: " & parts(1)
        Else
            MsgBox strError, vbCritical
            End
        End If
    ElseIf parts(0) = "ER" Then
        MsgBox strError, vbCritical
        End
    Else
        MsgBox "The program can't connect to internet.", vbCritical
        End
    End If

End Sub

Public Function StripNulls(OriginalStr As String) As String
    If (InStr(OriginalStr, Chr(0)) > 0) Then
        OriginalStr = Left(OriginalStr, InStr(OriginalStr, Chr(0)) - 1)
    End If
    StripNulls = OriginalStr
End Function

Public Function GetFileFromPath(sStr As String) As String
    Dim sTmp As String
    sTmp = Right(sStr, Len(sStr) - InStrRev(sStr, "\"))
    If Len(sTmp) > 49 Then
        GetFileFromPath = Right(sTmp, 31)
    Else
        GetFileFromPath = sTmp
    End If
End Function

Public Function UnXor2(sStr As String) As String
    Dim i As Long, B() As Byte
    B() = StrConv(sStr, vbFromUnicode)
    For i = 0 To Len(sStr) - 1
        B(i) = B(i) Xor (i Mod 5) + 1
    Next i
    UnXor2 = StrConv(B, vbUnicode)
End Function

