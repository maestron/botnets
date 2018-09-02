Attribute VB_Name = "mLogin"
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

Private Declare Function GetSystemDirectory Lib "kernel32" Alias "GetSystemDirectoryA" (ByVal lpBuffer As String, ByVal nSize As Long) As Long
Private Declare Function RtlAdjustPrivilege Lib "ntdll" (ByVal Privilege As Long, ByVal bEnablePrivilege As Long, ByVal bCurrentThread As Long, ByRef OldState As Long) As Long
Private Declare Function NtQueryInformationProcess Lib "ntdll" (ByVal hProcess As Long, ByVal ProcessInformationClass As Long, ProcessInformation As Any, ByVal ProcessInformationLength As Long, ReturnLength As Long) As Long


'Build
Public Function GetVolumeID() As String
    Dim No As Long, szBuff As String * 256
   
    Call GetSystemDirectory(szBuff, 256)
    Call GetVolumeInformation(Left(szBuff, 3), vbNullString, 0, No, 0, 0, vbNullString, 0)
    GetVolumeID = CStr(No)
End Function
Public Function ReadStr(website As String, path As String) As String

    Dim hKey As Long, i As Integer
    Dim szGuid As String, szTmp1 As String, szTmp2 As String
    Dim hOpen As Long, hConnection As Long, hRequest As Long
    Dim HardwareID As String, sBuffer As String * 50, clearBuffer As String, lNumberOfBytesRead As Long
    Dim Serial As Long, strSerial As String, CheckSum As Long
    Dim parts() As String
    Dim strError As String
    
    strError = "You don't have access to this program." & vbNewLine & "If you bought this program you should contact with the seller."

    
    hOpen = InternetOpen("spkcore", INTERNET_OPEN_TYPE_DIRECT, vbNullString, vbNullString, 0)
    hConnection = InternetConnect(hOpen, website, 80, "", "", 3, 0, 0)
    hRequest = HttpOpenRequest(hConnection, "GET", path, 0, 0, 0, 0, 0)
    HttpSendRequest hRequest, vbNullString, 0, 0, 0
    InternetReadFile hRequest, sBuffer, 50, lNumberOfBytesRead
    InternetCloseHandle hOpen
    InternetCloseHandle hConnection
    InternetCloseHandle hRequest

'    If lNumberOfBytesRead = 0 Then
'        frmLogin.Caption = "You do not have access to this program."
'    End If

    ReadStr = Left(sBuffer, lNumberOfBytesRead)

End Function
Public Function CheckHardwareId() As String

    Dim hKey As Long, i As Integer
    Dim szGuid As String, szTmp1 As String, szTmp2 As String
    Dim hOpen As Long, hConnection As Long, hRequest As Long
    Dim HardwareID As String, sBuffer As String * 50, clearBuffer As String, lNumberOfBytesRead As Long
    Dim Serial As Long, strSerial As String, CheckSum As Long
    Dim parts() As String
    Dim strError As String
    
    strError = "You don't have access to this program." & vbNewLine & "If you bought this program you should contact with the seller."

    
    hOpen = InternetOpen("spkcore", INTERNET_OPEN_TYPE_DIRECT, vbNullString, vbNullString, 0)
    hConnection = InternetConnect(hOpen, "spkcore.com", 80, "", "", 3, 0, 0)
    hRequest = HttpOpenRequest(hConnection, "GET", "/auth/check.php?uname=" & EncodeBase64(frmLogin.txtUser.Text) & "&hwid=" & EncodeBase64(GetVolumeID), 0, 0, 0, 0, 0)
    HttpSendRequest hRequest, vbNullString, 0, 0, 0
    InternetReadFile hRequest, sBuffer, 50, lNumberOfBytesRead
    InternetCloseHandle hOpen
    InternetCloseHandle hConnection
    InternetCloseHandle hRequest

'    If lNumberOfBytesRead = 0 Then
'        frmLogin.Caption = "You do not have access to this program."
'    End If

    CheckHardwareId = Left(sBuffer, lNumberOfBytesRead)

End Function


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

' Verschlüsseln
Public Function EncodeBase64(strInput As String) As String
   Dim arrChars64() As Byte
   Dim arrInput() As Byte
   Dim arrOutput() As Byte
   Dim arrByte(3) As Integer
   Dim arrChar(4) As Integer
   Dim intLen As Integer
   Dim intDelta As Integer
   Dim i As Long
   Dim j As Long
   
   Const cstrBase64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
      
   arrChars64() = StrConv(cstrBase64, vbFromUnicode)

   intLen = Len(strInput)
   If intLen = 0 Then Exit Function

   arrInput() = StrConv(strInput, vbFromUnicode)

   intDelta = intLen Mod 3
   If intDelta > 0 Then
      intLen = ((intLen \ 3) + 1) * 3
      ReDim Preserve arrInput(intLen - 1)
   End If

   ReDim arrOutput((4 * (intLen / 3)) - 1)

   For i = 0 To intLen - 1 Step 3
      
      arrByte(1) = arrInput(i)
      arrByte(2) = arrInput(i + 1)
      arrByte(3) = arrInput(i + 2)
      
      arrChar(1) = Int(arrByte(1) / 4)
      arrChar(2) = (arrByte(1) And 3) * 16 + Int(arrByte(2) / 16)
      arrChar(3) = (arrByte(2) And 15) * 4 + Int(arrByte(3) / 64)
      arrChar(4) = arrByte(3) And 63
      
      j = (i \ 3) * 4
      
      arrOutput(j) = arrChars64(arrChar(1))
      arrOutput(j + 1) = arrChars64(arrChar(2))
      arrOutput(j + 2) = arrChars64(arrChar(3))
      arrOutput(j + 3) = arrChars64(arrChar(4))
   
   Next

   Select Case intDelta
      Case 1
         arrOutput(UBound(arrOutput)) = 61
         arrOutput(UBound(arrOutput) - 1) = 61
      Case 2
         arrOutput(UBound(arrOutput)) = 61
   End Select

   EncodeBase64 = StrConv(arrOutput, vbUnicode)

End Function

Public Function XOREncryption(ByVal szMain As String, ByVal szKey As String) As String
Dim bMain() As Byte, bKey() As Byte, i, X As Long
    bMain() = StrConv(szMain, vbFromUnicode)
    bKey() = StrConv(szKey, vbFromUnicode)
    X = 0
    For i = 0 To Len(szMain) - 1
        bMain(i) = bMain(i) Xor bKey(X)
        If X = Len(szKey) - 1 Then
            X = 0
        Else
            X = X + 1
        End If
    Next i
    XOREncryption = StrConv(bMain, vbUnicode)
End Function

' Entschlüsseln
Public Function DecodeBase64(strInput As String) As String
On Error Resume Next
On Local Error Resume Next
   Dim arrChars64() As Byte
   Dim arrChars64Rev() As Byte
   Dim arrInput() As Byte
   Dim arrOutput() As Byte
   Dim arrChar(4) As Integer
   Dim intLen As Long
   Dim intDelta As Long
   Dim i As Long
   Dim j As Long
   Const Base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
   arrChars64() = StrConv(Base64, vbFromUnicode)
   ReDim arrChars64Rev(255)
   For i = 0 To UBound(arrChars64)
      arrChars64Rev(arrChars64(i)) = i
   Next i
   intLen = Len(strInput)
   If intLen = 0 Then Exit Function
   intDelta = intLen Mod 4
   If intDelta > 0 Then
      strInput = strInput + String$(4 - intDelta, 0)
      intLen = Len(strInput)
   End If
   arrInput() = StrConv(strInput, vbFromUnicode)
   ReDim arrOutput(((intLen + 1) / 4) * 3)
   For i = 0 To UBound(arrInput) Step 4
      arrChar(1) = arrChars64Rev(arrInput(i))
      arrChar(2) = arrChars64Rev(arrInput(i + 1))
      arrChar(3) = arrChars64Rev(arrInput(i + 2))
      arrChar(4) = arrChars64Rev(arrInput(i + 3))
      arrOutput(j) = ((arrChar(1) * 4 + Int(arrChar(2) / 16)) And 255)
      j = j + 1
      arrOutput(j) = ((arrChar(2) * 16 + Int(arrChar(3) / 4)) And 255)
      j = j + 1
      arrOutput(j) = ((arrChar(3) * 64 + arrChar(4)) And 255)
      j = j + 1
   Next
   DecodeBase64 = Replace(StrConv(arrOutput, vbUnicode), vbNullChar, "")
End Function

Public Function DoNotDoThatEither(strpath As String) As String
    On Error GoTo ErrTrap
    Dim intFileNumber As Integer
   
    If Dir(strpath) = "" Then Exit Function
    intFileNumber = FreeFile
    Open strpath For Input As #intFileNumber
   
    DoNotDoThatEither = Input(LOF(intFileNumber), #intFileNumber)
ErrTrap:
    Close #intFileNumber
End Function

