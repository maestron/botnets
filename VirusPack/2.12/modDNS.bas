Attribute VB_Name = "modDNS"
Option Explicit

Private Type HOSTENT
  hName As Long
  hAliases As Long
  hAddrType As Integer
  hLength As Integer
  hAddrList As Long
End Type

Private Type WSAData
  wVersion As Integer
  wHighVersion As Integer
  szDescription(0 To 256) As Byte
  szSystemStatus(0 To 128) As Byte
  iMaxSockets As Integer
  iMaxUdpDg As Integer
  lpszVendorInfo As Long
End Type

'Private Declare Function WSAStartup Lib "wsock32" (ByVal VersionReq As Long, WSADataReturn As WSADATA) As Long
'Private Declare Function WSACleanup Lib "wsock32" () As Long
Private Declare Function inet_addr Lib "WSOCK32.DLL" (ByVal ipaddress$) As Long
Private Declare Function gethostbyaddr Lib "wsock32" (addr As Long, addrlen As Long, addrType As Long) As Long
Private Declare Function gethostbyname Lib "wsock32" (ByVal Hostname As String) As Long
Private Declare Sub RtlMoveMemory Lib "kernel32" (hpvDest As Any, ByVal hpvSource As Long, ByVal cbCopy As Long)

'checks if string is valid IP address
Public Function IsIP(ByVal strIP As String) As Boolean
  On Local Error Resume Next
  Dim t As String: Dim s As String: Dim i As Integer
  s = strIP
  While InStr(s, ".") <> 0
    t = VBA.Left$(s, InStr(s, ".") - 1)
    If IsNumeric(t) And Val(t) >= 0 And Val(t) <= 255 Then s = Mid$(s, InStr(s, ".") + 1) _
      Else Exit Function
    i = i + 1
  Wend
  t = s
  If IsNumeric(t) And InStr(t, ".") = 0 And Len(t) = Len(Trim$(Str(Val(t)))) And _
    Val(t) >= 0 And Val(t) <= 255 And strIP <> "255.255.255.255" And i = 3 Then IsIP = True
  If Err.Number > 0 Then
    Err.Clear
  End If
End Function

'resolves IP address to host name
Private Function NameByAddr(strAddr As String) As String
  On Local Error Resume Next
  Dim nRet As Long
  Dim lIP As Long
  Dim strHost As String * 255: Dim strTemp As String
  Dim hst As HOSTENT
  
  If IsIP(strAddr) Then
    lIP = inet_addr(strAddr)
    nRet = gethostbyaddr(lIP, 4, 2)
    If nRet <> 0 Then
      RtlMoveMemory hst, nRet, Len(hst)
      RtlMoveMemory ByVal strHost, hst.hName, 255
      strTemp = strHost
      If InStr(strTemp, Chr(10)) <> 0 Then strTemp = VBA.Left$(strTemp, InStr(strTemp, Chr(0)) - 1)
      strTemp = Trim$(strTemp)
      NameByAddr = strTemp
    Else
      Exit Function
    End If
  Else
    Exit Function
  End If
  If Err.Number > 0 Then
    Err.Clear
  End If
End Function

'resolves host name to IP address
Private Function AddrByName(ByVal strHost As String)
  On Local Error Resume Next
  Dim hostent_addr As Long
  Dim hst As HOSTENT
  Dim hostip_addr As Long
  Dim temp_ip_address() As Byte
  Dim i As Integer
  Dim ip_address As String
  If IsIP(strHost) Then
    AddrByName = strHost
    Exit Function
  End If
  hostent_addr = gethostbyname(strHost)
  If hostent_addr = 0 Then
    Exit Function
  End If
  RtlMoveMemory hst, hostent_addr, LenB(hst)
  RtlMoveMemory hostip_addr, hst.hAddrList, 4
  ReDim temp_ip_address(1 To hst.hLength)
  RtlMoveMemory temp_ip_address(1), hostip_addr, hst.hLength
  For i = 1 To hst.hLength
    ip_address = ip_address & temp_ip_address(i) & "."
  Next
  ip_address = Mid$(ip_address, 1, Len(ip_address) - 1)
  AddrByName = ip_address
  If Err.Number > 0 Then
    Err.Clear
  End If
End Function

Public Function AddressToName(strIP As String)
  AddressToName = TrimNull(NameByAddr(strIP))
End Function

Public Function NameToAddress(strName As String)
  NameToAddress = TrimNull(AddrByName(strName))
End Function

Public Function FilterHostname(strShit As String) As String
    Dim i As Long
    Dim strOut As String
    Dim strChar As String
    For i = 1 To Len(strShit)
        strChar = Mid$(strShit, i, 1)
        If IsNotGay(strChar) Then
            strOut = strOut & strChar
        Else
            FilterHostname = strOut
            Exit Function
        End If
    Next
    FilterHostname = strOut
End Function

Private Function IsNotGay(strChar) As Boolean
    If strChar Like "[0-9A-Za-z.-]" Then IsNotGay = True
End Function
