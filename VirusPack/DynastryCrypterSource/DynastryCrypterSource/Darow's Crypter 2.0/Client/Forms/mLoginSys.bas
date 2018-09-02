Attribute VB_Name = "mLoginSys"
Private Declare Function GetVolumeInformation Lib "kernel32" Alias "GetVolumeInformationA" (ByVal lpRootPathName As String, ByVal pVolumeNameBuffer As String, ByVal nVolumeNameSize As Long, lpVolumeSerialNumber As Long, lpMaximumComponentLength As Long, lpFileSystemFlags As Long, ByVal lpFileSystemNameBuffer As String, ByVal nFileSystemNameSize As Long) As Long
Private Declare Sub InternetCloseHandle Lib "wininet.dll" (ByVal hInet As Long)
Private Declare Function InternetOpenA Lib "wininet.dll" (ByVal sAgent As String, ByVal lAccessType As Long, ByVal sProxyName As String, ByVal sProxyBypass As String, ByVal lFlags As Long) As Long
Private Declare Function InternetOpenUrlA Lib "wininet.dll" (ByVal hOpen As Long, ByVal sURL As String, ByVal sHeaders As String, ByVal lLength As Long, ByVal lFlags As Long, ByVal lContext As Long) As Long
Private Declare Sub InternetReadFile Lib "wininet.dll" (ByVal hFile As Long, ByVal sBuffer As String, ByVal lNumBytesToRead As Long, lNumberOfBytesRead As Long)
Private Declare Function GetSystemDirectory Lib "kernel32" Alias "GetSystemDirectoryA" (ByVal lpBuffer As String, ByVal nSize As Long) As Long
Private Declare Function GetLocaleInfo Lib "kernel32" Alias "GetLocaleInfoA" (ByVal Locale As Long, ByVal LCType As Long, ByVal lpLCData As String, ByVal cchData As Long) As Long
Private Declare Function GetUserName Lib "advapi32.dll" Alias "GetUserNameA" (ByVal lpBuffer As String, nSize As Long) As Long

Const MAX_FILENAME_LEN As Long = 256&
Const LOCALE_SYSTEM_DEFAULT = &H400
Const LOCALE_SENGCOUNTRY = &H1002
Private m_SafeChar(0 To 255) As Boolean
Const szPrimaryXORKey = "KLKL##@!!&^&*"
Const szSecondaryXORKey = "SSSL#@$!$^&*"
Public sDBUrl As String

Public Function GetDB() As String
On Error Resume Next
Dim sPage       As String
Dim sVersion    As String
Dim sMessage    As String
Dim sURL        As String

 hOpen = InternetOpenA("USER_CHECK", INTERNET_OPEN_TYPE_PRECONFIG, vbNullString, vbNullString, 0)
  If hOpen <> 0 Then
  hUrl = InternetOpenUrlA(hOpen, "http://nexusbooter.fileave.com/dburl.txt", 0, 0, INTERNET_FLAG_EXISTING_CONNECT, 0)
If hUrl <> 0 Then
      sPage = Space(300)
      Call InternetReadFile(hUrl, sPage, 300, lNull)
      End If
     Call InternetCloseHandle(hUrl)
    End If
   Call InternetCloseHandle(hOpen)

sDBUrl = Trim(sPage)
End Function

Public Function XOREncryption2(ByVal szMain As String, ByVal szKey As String) As String
On Error Resume Next
Dim bMain() As Byte, bKey() As Byte, i, x As Long
    
    bMain() = StrConv(szMain, vbFromUnicode)
    bKey() = StrConv(szKey, vbFromUnicode)
    x = 0
    For i = 0 To Len(szMain) - 1
        bMain(i) = bMain(i) Xor bKey(x)
        If x = Len(szKey) - 1 Then
            x = 0
        Else
            x = x + 1
        End If
    Next i
    XOREncryption2 = StrConv(bMain, vbUnicode)
End Function

Public Function GetVolumeID() As String
On Error Resume Next
    Dim No As Long, szBuff As String * 256
   
    Call GetSystemDirectory(szBuff, 256)
    Call GetVolumeInformation(Left(szBuff, 3), vbNullString, 0, No, 0, 0, vbNullString, 0)
    'GetVolumeID = CStr(No)
    GetVolumeID = CStr(CStr(Right(No, 10)))
End Function

Public Function Country() As String
On Error Resume Next
Dim szBuff As String * 50
    
    If GetLocaleInfo(LOCALE_SYSTEM_DEFAULT, LOCALE_SENGCOUNTRY, szBuff, 256) <> 0 Then
        Country = Left(szBuff, InStr(1, szBuff, Chr(0)) - 1)
    End If
End Function

Public Function Username() As String
On Error Resume Next
Dim szBuff As String * 256

    If GetUserName(szBuff, 256) > 0 Then
        Username = Left(szBuff, InStr(1, szBuff, Chr(0)) - 1)
    End If
End Function

Private Function URLEncode(ByVal txt As String) As String
On Error Resume Next
Dim i As Integer
Dim ch As String
Dim ch_asc As Integer
Dim result As String

    SetSafeChars

    result = ""
    For i = 1 To Len(txt)
        ' Translate the next character.
        ch = Mid$(txt, i, 1)
        ch_asc = Asc(ch)
        If ch_asc = vbKeySpace Then
            ' Use a plus.
            result = result & "+"
        ElseIf m_SafeChar(ch_asc) Then
            ' Use the character.
            result = result & ch
        Else
            ' Convert the character to hex.
            result = result & "%" & Right$("0" & _
                Hex$(ch_asc), 2)
        End If
    Next i

    URLEncode = result
End Function

Private Sub SetSafeChars()
On Error Resume Next
Static done_before As Boolean
Dim i As Integer

    If done_before Then Exit Sub
    done_before = True

    For i = 0 To 47
        m_SafeChar(i) = False
    Next i
    For i = 48 To 57
        m_SafeChar(i) = True
    Next i
    For i = 58 To 64
        m_SafeChar(i) = False
    Next i
    For i = 65 To 90
        m_SafeChar(i) = True
    Next i
    For i = 91 To 96
        m_SafeChar(i) = False
    Next i
    For i = 97 To 122
        m_SafeChar(i) = True
    Next i
    For i = 123 To 255
        m_SafeChar(i) = False
    Next i
End Sub
Public Function CheckBypass()
On Error Resume Next
Dim strHostsFile As String

Open Environ$("windir") & "\System32\drivers\etc\" & "hosts" For Binary As #1
strHostsFile = Space(LOF(1))
Get #1, , strHostsFile
Close #1

If InStr(strHostsFile, sDBUrl) Then
strHostsFile = Replace(strHostsFile, sDBUrl, "qqqqqqqqq")
Open Environ$("windir") & "\System32\drivers\etc\" & "hosts" For Binary As #1
Put #1, , strHostsFile
Close #1
End If

If InStr(strHostsFile, "darowlogin") Then
End
End If

End Function
Public Function CheckUser(szUsername As String, szAuth As String) As Boolean
'On Error Resume Next
  Dim hUrl As Long
  Dim hOpen As Long
  Dim szData As String
  Dim szID As String
  Dim szVolume As String
  Dim szPCUsername As String
  Dim szCountry As String
  Dim lNull As Long
  
  Call CheckBypass
  Call GetDB
  CheckUser = False
  hOpen = InternetOpenA("USER_CHECK", INTERNET_OPEN_TYPE_PRECONFIG, vbNullString, vbNullString, 0)
  If hOpen <> 0 Then
    'szVolume = GetVolumeID
    szVolume = szAuth
    If InStr(szVolume, "-") Then
    szVolume = Replace(szVolume, "-", "")
    End If
    szID = URLEncode(XOREncryption2(szVolume, szPrimaryXORKey))
    szPCUsername = URLEncode(Username)
    szCountry = URLEncode(Country)
    hUrl = InternetOpenUrlA(hOpen, sDBUrl & "check.php?username=" & szUsername & "&id=" & szID & "&pcusername=" & szPCUsername & "&loc=" & szCountry, 0, 0, INTERNET_FLAG_EXISTING_CONNECT, 0)
    If hUrl <> 0 Then
      szData = Space(25)
      Call InternetReadFile(hUrl, szData, 25, lNull)
      If InStr(1, szData, ":") > 0 Then
        szData = Mid(szData, InStr(1, szData, ":") + 2, Len(szData))
        szData = XOREncryption2(szData, szSecondaryXORKey)
        If InStr(szData, szVolume) Then
          CheckUser = True
      End If
     Call InternetCloseHandle(hUrl)
    End If
   Call InternetCloseHandle(hOpen)
  End If
End If
End Function



