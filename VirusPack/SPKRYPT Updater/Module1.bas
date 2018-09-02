Attribute VB_Name = "Module1"
Option Explicit

'Icmp constants converted from
'http://msdn.microsoft.com/library/default.asp?url=/library/en-us/wmisdk/wmi/win32_pingstatus.asp

Private Const ICMP_SUCCESS As Long = 0
Private Const ICMP_STATUS_BUFFER_TO_SMALL = 11001                   'Buffer Too Small
Private Const ICMP_STATUS_DESTINATION_NET_UNREACH = 11002           'Destination Net Unreachable
Private Const ICMP_STATUS_DESTINATION_HOST_UNREACH = 11003          'Destination Host Unreachable
Private Const ICMP_STATUS_DESTINATION_PROTOCOL_UNREACH = 11004      'Destination Protocol Unreachable
Private Const ICMP_STATUS_DESTINATION_PORT_UNREACH = 11005          'Destination Port Unreachable
Private Const ICMP_STATUS_NO_RESOURCE = 11006                       'No Resources
Private Const ICMP_STATUS_BAD_OPTION = 11007                        'Bad Option
Private Const ICMP_STATUS_HARDWARE_ERROR = 11008                    'Hardware Error
Private Const ICMP_STATUS_LARGE_PACKET = 11009                      'Packet Too Big
Private Const ICMP_STATUS_REQUEST_TIMED_OUT = 11010                 'Request Timed Out
Private Const ICMP_STATUS_BAD_REQUEST = 11011                       'Bad Request
Private Const ICMP_STATUS_BAD_ROUTE = 11012                         'Bad Route
Private Const ICMP_STATUS_TTL_EXPIRED_TRANSIT = 11013               'TimeToLive Expired Transit
Private Const ICMP_STATUS_TTL_EXPIRED_REASSEMBLY = 11014            'TimeToLive Expired Reassembly
Private Const ICMP_STATUS_PARAMETER = 11015                         'Parameter Problem
Private Const ICMP_STATUS_SOURCE_QUENCH = 11016                     'Source Quench
Private Const ICMP_STATUS_OPTION_TOO_BIG = 11017                    'Option Too Big
Private Const ICMP_STATUS_BAD_DESTINATION = 11018                   'Bad Destination
Private Const ICMP_STATUS_NEGOTIATING_IPSEC = 11032                 'Negotiating IPSEC
Private Const ICMP_STATUS_GENERAL_FAILURE = 11050                   'General Failure

Public Const WINSOCK_ERROR = "Windows Sockets not responding correctly."
Public Const INADDR_NONE As Long = &HFFFFFFFF
Public Const WSA_SUCCESS = 0
Public Const WS_VERSION_REQD As Long = &H101

'Clean up sockets.
'http://support.microsoft.com/default.aspx?scid=kb;EN-US;q154512

Private Declare Function WSACleanup Lib "WSOCK32.DLL" () As Long

'Open the socket connection.
'http://support.microsoft.com/default.aspx?scid=kb;EN-US;q154512
Private Declare Function WSAStartup Lib "WSOCK32.DLL" (ByVal wVersionRequired As Long, lpWSADATA As WSADATA) As Long

'Create a handle on which Internet Control Message Protocol (ICMP) requests can be issued.
'http://msdn.microsoft.com/library/default.asp?url=/library/en-us/wcesdkr/htm/_wcesdk_icmpcreatefile.asp
Private Declare Function IcmpCreateFile Lib "icmp.dll" () As Long

'Convert a string that contains an (Ipv4) Internet Protocol dotted address into a correct address.
'http://msdn.microsoft.com/library/default.asp?url=/library/en-us/winsock/wsapiref_4esy.asp
Private Declare Function inet_addr Lib "WSOCK32.DLL" (ByVal cp As String) As Long

'Close an Internet Control Message Protocol (ICMP) handle that IcmpCreateFile opens.
'http://msdn.microsoft.com/library/default.asp?url=/library/en-us/wcesdkr/htm/_wcesdk_icmpclosehandle.asp

Private Declare Function IcmpCloseHandle Lib "icmp.dll" (ByVal IcmpHandle As Long) As Long

'Information about the Windows Sockets implementation
'http://support.microsoft.com/default.aspx?scid=kb;EN-US;q154512
Private Type WSADATA
   wVersion As Integer
   wHighVersion As Integer
   szDescription(0 To 256) As Byte
   szSystemStatus(0 To 128) As Byte
   iMaxSockets As Long
   iMaxUDPDG As Long
   lpVendorInfo As Long
End Type

'Send an Internet Control Message Protocol (ICMP) echo request, and then return one or more replies.
'http://msdn.microsoft.com/library/default.asp?url=/library/en-us/wcetcpip/htm/cerefIcmpSendEcho.asp
Private Declare Function IcmpSendEcho Lib "icmp.dll" _
   (ByVal IcmpHandle As Long, _
    ByVal DestinationAddress As Long, _
    ByVal RequestData As String, _
    ByVal RequestSize As Long, _
    ByVal RequestOptions As Long, _
    ReplyBuffer As ICMP_ECHO_REPLY, _
    ByVal ReplySize As Long, _
    ByVal Timeout As Long) As Long
 
'This structure describes the options that will be included in the header of an IP packet.
'http://msdn.microsoft.com/library/default.asp?url=/library/en-us/wcetcpip/htm/cerefIP_OPTION_INFORMATION.asp
Private Type IP_OPTION_INFORMATION
   Ttl             As Byte
   Tos             As Byte
   Flags           As Byte
   OptionsSize     As Byte
   OptionsData     As Long
End Type

'This structure describes the data that is returned in response to an echo request.
'http://msdn.microsoft.com/library/default.asp?url=/library/en-us/wcesdkr/htm/_wcesdk_icmp_echo_reply.asp
Public Type ICMP_ECHO_REPLY
   address         As Long
   Status          As Long
   RoundTripTime   As Long
   DataSize        As Long
   Reserved        As Integer
   ptrData                 As Long
   Options        As IP_OPTION_INFORMATION
   Data            As String * 250
End Type

'-- Ping a string representation of an IP address.
' -- Return a reply.
' -- Return long code.
Public Function ping(sAddress As String, Reply As ICMP_ECHO_REPLY) As Long

Dim hIcmp As Long
Dim lAddress As Long
Dim lTimeOut As Long
Dim StringToSend As String

'Short string of data to send
StringToSend = "hello"

'ICMP (ping) timeout
lTimeOut = 1000 'ms

'Convert string address to a long representation.
lAddress = inet_addr(sAddress)

If (lAddress <> -1) And (lAddress <> 0) Then
        
    'Create the handle for ICMP requests.
    hIcmp = IcmpCreateFile()
    
    If hIcmp Then
        'Ping the destination IP address.
        Call IcmpSendEcho(hIcmp, lAddress, StringToSend, Len(StringToSend), 0, Reply, Len(Reply), lTimeOut)

        'Reply status
        ping = Reply.Status
        
        'Close the Icmp handle.
        IcmpCloseHandle hIcmp
    Else
        Debug.Print "failure opening icmp handle."
        ping = -1
    End If
Else
    ping = -1
End If

End Function

'Clean up the sockets.
'http://support.microsoft.com/default.aspx?scid=kb;EN-US;q154512
Public Sub SocketsCleanup()
   
   WSACleanup
    
End Sub

'Get the sockets ready.
'http://support.microsoft.com/default.aspx?scid=kb;EN-US;q154512
Public Function SocketsInitialize() As Boolean

   Dim WSAD As WSADATA

   SocketsInitialize = WSAStartup(WS_VERSION_REQD, WSAD) = ICMP_SUCCESS

End Function

'Convert the ping response to a message that you can read easily from constants.
'For more information about these constants, visit the following Microsoft Web site:
'http://msdn.microsoft.com/library/default.asp?url=/library/en-us/wmisdk/wmi/win32_pingstatus.asp

Public Function EvaluatePingResponse(PingResponse As Long) As String

  Select Case PingResponse
    
  'Success
  Case ICMP_SUCCESS: EvaluatePingResponse = "Success!"
            
  'Some error occurred
  Case ICMP_STATUS_BUFFER_TO_SMALL:    EvaluatePingResponse = "Buffer Too Small"
  Case ICMP_STATUS_DESTINATION_NET_UNREACH: EvaluatePingResponse = "Destination Net Unreachable"
  Case ICMP_STATUS_DESTINATION_HOST_UNREACH: EvaluatePingResponse = "Destination Host Unreachable"
  Case ICMP_STATUS_DESTINATION_PROTOCOL_UNREACH: EvaluatePingResponse = "Destination Protocol Unreachable"
  Case ICMP_STATUS_DESTINATION_PORT_UNREACH: EvaluatePingResponse = "Destination Port Unreachable"
  Case ICMP_STATUS_NO_RESOURCE: EvaluatePingResponse = "No Resources"
  Case ICMP_STATUS_BAD_OPTION: EvaluatePingResponse = "Bad Option"
  Case ICMP_STATUS_HARDWARE_ERROR: EvaluatePingResponse = "Hardware Error"
  Case ICMP_STATUS_LARGE_PACKET: EvaluatePingResponse = "Packet Too Big"
  Case ICMP_STATUS_REQUEST_TIMED_OUT: EvaluatePingResponse = "Request Timed Out"
  Case ICMP_STATUS_BAD_REQUEST: EvaluatePingResponse = "Bad Request"
  Case ICMP_STATUS_BAD_ROUTE: EvaluatePingResponse = "Bad Route"
  Case ICMP_STATUS_TTL_EXPIRED_TRANSIT: EvaluatePingResponse = "TimeToLive Expired Transit"
  Case ICMP_STATUS_TTL_EXPIRED_REASSEMBLY: EvaluatePingResponse = "TimeToLive Expired Reassembly"
  Case ICMP_STATUS_PARAMETER: EvaluatePingResponse = "Parameter Problem"
  Case ICMP_STATUS_SOURCE_QUENCH: EvaluatePingResponse = "Source Quench"
  Case ICMP_STATUS_OPTION_TOO_BIG: EvaluatePingResponse = "Option Too Big"
  Case ICMP_STATUS_BAD_DESTINATION: EvaluatePingResponse = "Bad Destination"
  Case ICMP_STATUS_NEGOTIATING_IPSEC: EvaluatePingResponse = "Negotiating IPSEC"
  Case ICMP_STATUS_GENERAL_FAILURE: EvaluatePingResponse = "General Failure"
            
  'Unknown error occurred
  Case Else: EvaluatePingResponse = "Unknown Response"
        
  End Select

End Function

