VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CSocketMaster"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
'********************************************************************************
'
'Name.......... CSocketMaster
'File.......... c.cls
'Version....... 1.1
'Dependencies.. Requires modSocketMaster.bas code module
'Description... Winsock api implementation class
'Author........ Emiliano Scavuzzo <anshoku@yahoo.com>
'Date.......... February, 22nd 2004

'Copyright (c) 2004 by Emiliano Scavuzzo
'Rosario, Argentina
'
'Based on CSocket by Oleg Gdalevich
'Subclassing based on WinSubHook2 by Paul Caton <Paul_Caton@hotmail.com>
'
'********************************************************************************

Option Explicit

'==============================================================================
'API FUNCTIONS
'==============================================================================

Private Declare Function api_socket Lib "ws2_32.dll" Alias "socket" (ByVal af As Long, ByVal s_type As Long, ByVal Protocol As Long) As Long
Private Declare Function api_GlobalLock Lib "kernel32" Alias "GlobalLock" (ByVal hMem As Long) As Long
Private Declare Function api_GlobalUnlock Lib "kernel32" Alias "GlobalUnlock" (ByVal hMem As Long) As Long
Private Declare Function api_htons Lib "ws2_32.dll" Alias "htons" (ByVal hostshort As Integer) As Integer
Private Declare Function api_ntohs Lib "ws2_32.dll" Alias "ntohs" (ByVal netshort As Integer) As Integer
Private Declare Function api_connect Lib "ws2_32.dll" Alias "connect" (ByVal s As Long, ByRef name As sockaddr_in, ByVal namelen As Long) As Long
Private Declare Function api_gethostname Lib "ws2_32.dll" Alias "gethostname" (ByVal host_name As String, ByVal namelen As Long) As Long
Private Declare Function api_gethostbyname Lib "ws2_32.dll" Alias "gethostbyname" (ByVal host_name As String) As Long
Private Declare Function api_bind Lib "ws2_32.dll" Alias "bind" (ByVal s As Long, ByRef name As sockaddr_in, ByRef namelen As Long) As Long
Private Declare Function api_getsockname Lib "ws2_32.dll" Alias "getsockname" (ByVal s As Long, ByRef name As sockaddr_in, ByRef namelen As Long) As Long
Private Declare Function api_getpeername Lib "ws2_32.dll" Alias "getpeername" (ByVal s As Long, ByRef name As sockaddr_in, ByRef namelen As Long) As Long
Private Declare Function api_inet_addr Lib "ws2_32.dll" Alias "inet_addr" (ByVal cp As String) As Long
Private Declare Function api_send Lib "ws2_32.dll" Alias "send" (ByVal s As Long, ByRef buf As Any, ByVal buflen As Long, ByVal flags As Long) As Long
Private Declare Function api_sendto Lib "ws2_32.dll" Alias "sendto" (ByVal s As Long, ByRef buf As Any, ByVal buflen As Long, ByVal flags As Long, ByRef toaddr As sockaddr_in, ByVal tolen As Long) As Long
Private Declare Function api_getsockopt Lib "ws2_32.dll" Alias "getsockopt" (ByVal s As Long, ByVal level As Long, ByVal optname As Long, optval As Any, optlen As Long) As Long
Private Declare Function api_setsockopt Lib "ws2_32.dll" Alias "setsockopt" (ByVal s As Long, ByVal level As Long, ByVal optname As Long, optval As Any, ByVal optlen As Long) As Long
Private Declare Function api_recv Lib "ws2_32.dll" Alias "recv" (ByVal s As Long, ByRef buf As Any, ByVal buflen As Long, ByVal flags As Long) As Long
Private Declare Function api_recvfrom Lib "ws2_32.dll" Alias "recvfrom" (ByVal s As Long, ByRef buf As Any, ByVal buflen As Long, ByVal flags As Long, ByRef from As sockaddr_in, ByRef fromlen As Long) As Long
Private Declare Function api_WSACancelAsyncRequest Lib "ws2_32.dll" Alias "WSACancelAsyncRequest" (ByVal hAsyncTaskHandle As Long) As Long
Private Declare Function api_listen Lib "ws2_32.dll" Alias "listen" (ByVal s As Long, ByVal backlog As Long) As Long
Private Declare Function api_accept Lib "ws2_32.dll" Alias "accept" (ByVal s As Long, ByRef addr As sockaddr_in, ByRef addrlen As Long) As Long
Private Declare Function api_inet_ntoa Lib "ws2_32.dll" Alias "inet_ntoa" (ByVal inn As Long) As Long
Private Declare Function api_gethostbyaddr Lib "ws2_32.dll" Alias "gethostbyaddr" (addr As Long, ByVal addr_len As Long, ByVal addr_type As Long) As Long
Private Declare Function api_ioctlsocket Lib "ws2_32.dll" Alias "ioctlsocket" (ByVal s As Long, ByVal cmd As Long, ByRef argp As Long) As Long
Private Declare Function api_closesocket Lib "ws2_32.dll" Alias "closesocket" (ByVal s As Long) As Long

'==============================================================================
'CONSTANTS
'==============================================================================
Public Enum SockState
    sckClosed = 0
    sckOpen
    sckListening
    sckConnectionPending
    sckResolvingHost
    sckHostResolved
    sckConnecting
    sckConnected
    sckClosing
    sckError
End Enum

Public Enum DestResolucion 'asynchronic host resolution destination
    destConnect = 0
    'destSendUDP = 1
End Enum

Private Const SOMAXCONN As Long = 5

Public Enum ProtocolConstants
    sckTCPProtocol = 0
    sckUDPProtocol = 1
End Enum

Private Const MSG_PEEK  As Long = &H2

'==============================================================================
'EVENTS
'==============================================================================

Public Event CloseSck()
Public Event Connect()
Public Event ConnectionRequest(ByVal requestID As Long)
Public Event DataArrival(ByVal bytesTotal As Long)
Public Event Error(ByVal Number As Integer, Description As String, ByVal sCode As Long, ByVal Source As String, ByVal HelpFile As String, ByVal HelpContext As Long, CancelDisplay As Boolean)
Public Event SendComplete()
Public Event SendProgress(ByVal bytesSent As Long, ByVal bytesRemaining As Long)

'==============================================================================
'MEMBER VARIABLES
'==============================================================================
Private m_lngSocketHandle       As Long                 'socket handle
Private m_enmState              As SockState            'socket state
Private m_strTag                As String               'tag
Private m_strRemoteHost         As String               'remote host
Private m_lngRemotePort         As Long                 'remote port
Private m_strRemoteHostIP       As String               'remote host ip
Private m_lngLocalPort          As Long                 'local port
Private m_lngLocalPortBind      As Long                 'temporary local port
Private m_strLocalIP            As String               'local IP
Private m_enmProtocol           As ProtocolConstants    'protocol used (TCP / UDP)

Private m_lngMemoryPointer  As Long 'memory pointer used as buffer when resolving host
Private m_lngMemoryHandle   As Long 'buffer memory handle

Private m_lngSendBufferLen  As Long 'winsock buffer size for sends
Private m_lngRecvBufferLen  As Long 'winsock buffer size for receives

Private m_strSendBuffer As String   'local incoming buffer
Private m_strRecvBuffer As String   'local outgoing buffer

Private m_blnAcceptClass As Boolean 'if True then this is a Accept socket class
Private m_colWaitingResolutions As Collection   'hosts waiting to be resolved by the system

'  ****  WARNING WARNING WARNING WARNING ******
'This sub MUST be the first on the class. DO NOT attempt
'to change it's location or the code will CRASH.
'This sub receives system messages from our WndProc.
Public Sub WndProc(ByVal hwnd As Long, ByVal uMsg As Long, ByVal wParam As Long, ByVal lParam As Long)
Select Case uMsg

Case RESOLVE_MESSAGE
    
    PostResolution wParam, HiWord(lParam)
    
Case SOCKET_MESSAGE
    
    PostSocket LoWord(lParam), HiWord(lParam)
    
End Select
End Sub

Private Sub Class_Initialize()
'socket's handle default value
m_lngSocketHandle = INVALID_SOCKET

'initiate resolution collection
Set m_colWaitingResolutions = New Collection

'initiate processes and winsock service
modSocketMaster.InitiateProcesses
End Sub

Private Sub Class_Terminate()
'clean hostname resolution system
CleanResolutionSystem

'destroy socket if it exists
If Not m_blnAcceptClass Then DestroySocket

'clean processes and finish winsock service
modSocketMaster.FinalizeProcesses

'clean resolution collection
Set m_colWaitingResolutions = Nothing
End Sub

'==============================================================================
'PROPERTIES
'==============================================================================

Public Property Get RemotePort() As Long
RemotePort = m_lngRemotePort
End Property

Public Property Let RemotePort(ByVal lngPort As Long)
If m_enmProtocol = sckTCPProtocol And m_enmState <> sckClosed Then
    'err.raise sckInvalidOp, "c.RemotePort", "Invalid operation at current state"
End If

If lngPort < 0 Or lngPort > 65535 Then
    'err.raise sckInvalidArg, "c.RemotePort", "The argument passed to a function was not in the correct format or in the specified range."
Else
    m_lngRemotePort = lngPort
End If
End Property

Public Property Get RemoteHost() As String
RemoteHost = m_strRemoteHost
End Property

Public Property Let RemoteHost(ByVal strHost As String)
If m_enmProtocol = sckTCPProtocol And m_enmState <> sckClosed Then
    'err.raise sckInvalidOp, "c.RemoteHost", "Invalid operation at current state"
End If

m_strRemoteHost = strHost
End Property

Public Property Get RemoteHostIP() As String
RemoteHostIP = m_strRemoteHostIP
End Property

Public Property Get LocalPort() As Long
If m_lngLocalPortBind = 0 Then
    LocalPort = m_lngLocalPort
Else
    LocalPort = m_lngLocalPortBind
End If
End Property

Public Property Let LocalPort(ByVal lngPort As Long)
If m_enmState <> sckClosed Then
    'err.raise sckInvalidOp, "c.LocalPort", "Invalid operation at current state"
End If
If lngPort < 0 Or lngPort > 65535 Then
    'err.raise sckInvalidArg, "c.LocalPort", "The argument passed to a function was not in the correct format or in the specified range."
Else
    m_lngLocalPort = lngPort
End If
End Property

Public Property Get State() As SockState
State = m_enmState
End Property

Public Property Get LocalHostName() As String
LocalHostName = GetLocalHostName
End Property

Public Property Get LocalIP() As String
If m_enmState = sckOpen Or m_enmState = sckListening Then
    LocalIP = m_strLocalIP
Else
    LocalIP = GetLocalIP
End If
End Property

Public Property Get BytesReceived() As Long
If m_enmProtocol = sckTCPProtocol Then
    BytesReceived = Len(m_strRecvBuffer)
Else
    BytesReceived = GetBufferLenUDP
End If
End Property

Public Property Get SocketHandle() As Long
SocketHandle = m_lngSocketHandle
End Property

Public Property Get Tag() As String
Tag = m_strTag
End Property

Public Property Let Tag(ByVal strTag As String)
m_strTag = strTag
End Property

Public Property Get Protocol() As ProtocolConstants
Protocol = m_enmProtocol
End Property

Public Property Let Protocol(ByVal enmProtocol As ProtocolConstants)
If m_enmState <> sckClosed Then
    'err.raise sckInvalidOp, "c.Protocol", "Invalid operation at current state"
Else
    m_enmProtocol = enmProtocol
End If
End Property

'Destroys the socket if it exists and unregisters it
'from control list.
Private Sub DestroySocket()
If Not m_lngSocketHandle = INVALID_SOCKET Then

    Dim lngResult As Long
    
    lngResult = api_closesocket(m_lngSocketHandle)
    
    If lngResult = SOCKET_ERROR Then
        
        m_enmState = sckError: 'Debug.Print "STATE: sckError"
        Dim lngErrorCode As Long
        lngErrorCode = Err.LastDllError
        'err.raise lngErrorCode, "c.DestroySocket", GetErrorDescription(lngErrorCode)
    
    Else
        
        'Debug.Print "OK Destroyed socket " & m_lngSocketHandle
        modSocketMaster.UnregisterSocket m_lngSocketHandle
        m_lngSocketHandle = INVALID_SOCKET
    
    End If
    
End If
End Sub

Public Sub CloseSck()
If m_lngSocketHandle = INVALID_SOCKET Then Exit Sub

m_enmState = sckClosing: 'Debug.Print "STATE: sckClosing"
CleanResolutionSystem
DestroySocket
     
m_lngLocalPortBind = 0
m_strRemoteHostIP = ""
m_strRecvBuffer = ""
m_strSendBuffer = ""
m_lngSendBufferLen = 0
m_lngRecvBufferLen = 0

m_enmState = sckClosed: 'Debug.Print "STATE: sckClosed"

End Sub

'Tries to create a socket if there isn't one yet and registers
'it to the control list.
'Returns TRUE if it has success
Private Function SocketExists() As Boolean
SocketExists = True
Dim lngResult As Long
Dim lngErrorCode As Long

'check if there is a socket already
If m_lngSocketHandle = INVALID_SOCKET Then
    
    'decide what kind of socket we are creating, TCP or UDP
    If m_enmProtocol = sckTCPProtocol Then
        lngResult = api_socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)
    Else
        lngResult = api_socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)
    End If
    
    If lngResult = INVALID_SOCKET Then
        
        m_enmState = sckError: 'Debug.Print "STATE: sckError"
        'Debug.Print "ERROR trying to create socket"
        SocketExists = False
        lngErrorCode = Err.LastDllError
        Dim blnCancelDisplay As Boolean
        blnCancelDisplay = True
        RaiseEvent Error(lngErrorCode, GetErrorDescription(lngErrorCode), 0, "c.SocketExists", "", 0, blnCancelDisplay)
        'If blnCancelDisplay = False Then MsgBox GetErrorDescription(lngErrorCode), vbOKOnly, "c.SocketExists"
    Else
        
        'Debug.Print "OK Created socket: " & lngResult
        m_lngSocketHandle = lngResult
        'set and get some socket options
        ProcessOptions
        SocketExists = modSocketMaster.RegisterSocket(m_lngSocketHandle, ObjPtr(Me), True)
    
    End If
End If
End Function

'Tries to connect to RemoteHost if it was passed, or uses
'm_strRemoteHost instead. If it is a hostname tries to
'resolve it first.
Public Sub Connect(Optional RemoteHost As Variant, Optional RemotePort As Variant)
If m_enmState <> sckClosed Then
    'err.raise sckInvalidOp, "c.Connect", "Invalid operation at current state"
End If

If Not IsMissing(RemoteHost) Then
        m_strRemoteHost = CStr(RemoteHost)
End If

'for some reason we get a GPF if we try to
'resolve a null string, so we replace it with
'an empty string
If m_strRemoteHost = vbNullString Then
    m_strRemoteHost = ""
End If

'check if RemotePort is a number between 1 and 65535
If Not IsMissing(RemotePort) Then
    If IsNumeric(RemotePort) Then
        If CLng(RemotePort) > 65535 Or CLng(RemotePort) < 1 Then
            'err.raise sckInvalidArg, "c.Connect", "The argument passed to a function was not in the correct format or in the specified range."
        Else
            m_lngRemotePort = CLng(RemotePort)
        End If
    Else
        'err.raise sckUnsupported, "c.Connect", "Unsupported variant type."
    End If
End If

'create a socket if there isn't one yet
If Not SocketExists Then Exit Sub

'If we are using UDP we just bind the socket and exit
'silently. Remember UDP is a connectionless protocol.
If m_enmProtocol = sckUDPProtocol Then
    If BindInternal Then
        m_enmState = sckOpen: 'Debug.Print "STATE: sckOpen"
    End If
    Exit Sub
End If

'try to get a 32 bits long that is used to identify a host
Dim lngAddress As Long
lngAddress = ResolveIfHostname(m_strRemoteHost, destConnect)

'We've got two options here:
'1) m_strRemoteHost was an IP, so a resolution wasn't
'   necessary, and now lngAddress is a 32 bits long and
'   we proceed to connect.
'2) m_strRemoteHost was a hostname, so a resolution was
'   necessary and it's taking place right now. We leave
'   silently.

If lngAddress <> vbNull Then
    ConnectToIP lngAddress, 0
End If

End Sub

'When the system resolves a hostname in asynchronous way we
'call this function to decide what to do with the result.
Private Sub PostResolution(ByVal lngAsynHandle As Long, ByVal lngErrorCode As Long)
If m_enmState <> sckResolvingHost Then Exit Sub

Dim enmDestination As DestResolucion

'find out what the resolution destination was
enmDestination = m_colWaitingResolutions.Item("R" & lngAsynHandle)
'erase that record from the collection since we won't need it any longer
m_colWaitingResolutions.Remove "R" & lngAsynHandle

If lngErrorCode = 0 Then 'if there weren't errors trying to resolve the hostname
    
    m_enmState = sckHostResolved: 'Debug.Print "STATE: sckHostResolved"
    
    Dim udtHostent As HOSTENT
    Dim lngPtrToIP As Long
    Dim arrIpAddress(1 To 4) As Byte
    Dim lngRemoteHostAddress As Long
    Dim Count As Integer
    Dim strIpAddress As String
    
    api_CopyMemory udtHostent, ByVal m_lngMemoryPointer, LenB(udtHostent)
    api_CopyMemory lngPtrToIP, ByVal udtHostent.hAddrList, 4
    api_CopyMemory arrIpAddress(1), ByVal lngPtrToIP, 4
    api_CopyMemory lngRemoteHostAddress, ByVal lngPtrToIP, 4
    
    'free memmory, won't need it any longer
    FreeMemory
    
    'We turn the 32 bits long into a readable string.
    'Note: we don't need this string. I put this here just
    'in case you need it.
    For Count = 1 To 4
        strIpAddress = strIpAddress & arrIpAddress(Count) & "."
    Next
        
    strIpAddress = Left$(strIpAddress, Len(strIpAddress) - 1)
    
    'Decide what to do with the result according to the destination
    Select Case enmDestination
    
    Case destConnect
        ConnectToIP lngRemoteHostAddress, 0
    
    End Select

Else 'there were errors trying to resolve the hostname

    'free buffer memory
    FreeMemory
    
    Select Case enmDestination
        
    Case destConnect
        ConnectToIP vbNull, lngErrorCode
        
    End Select

End If
End Sub

'This procedure is called by the WindowProc callback function
'from the modSocketMaster module. The lngEventID argument is an
'ID of the network event occurred for the socket. The lngErrorCode
'argument contains an error code only if an error was occurred
'during an asynchronous execution.
Private Sub PostSocket(ByVal lngEventID As Long, ByVal lngErrorCode As Long)

'handle any possible error
If lngErrorCode <> 0 Then
    m_enmState = sckError: 'Debug.Print "STATE: sckError"
    Dim blnCancelDisplay As Boolean
    blnCancelDisplay = True
    RaiseEvent Error(lngErrorCode, GetErrorDescription(lngErrorCode), 0, "c.PostSocket", "", 0, blnCancelDisplay)
    'If blnCancelDisplay = False Then MsgBox GetErrorDescription(lngErrorCode), vbOKOnly, "c.PostSocket"
    Exit Sub
End If

Dim udtSockAddr As sockaddr_in
Dim lngResult As Long
Dim lngBytesReceived As Long

Select Case lngEventID

'======================================================================

Case FD_CONNECT

    'Arrival of this message means that the connection initiated by the call
    'of the connect Winsock API function was successfully established.

    'Debug.Print "FD_CONNECT " & m_lngSocketHandle
    
    If m_enmState <> sckConnecting Then
        'Debug.Print "WARNING: Omitting FD_CONNECT"
        Exit Sub
    End If
    
    'Get the connection local end-point parameters
    lngResult = api_getpeername(m_lngSocketHandle, udtSockAddr, LenB(udtSockAddr))
        
    If lngResult = 0 Then
        m_lngRemotePort = modSocketMaster.IntegerToUnsigned(api_ntohs(udtSockAddr.sin_port))
        m_strRemoteHostIP = StringFromPointer(api_inet_ntoa(udtSockAddr.sin_addr))
    End If
    
    m_enmState = sckConnected: 'Debug.Print "STATE: sckConnected"
    RaiseEvent Connect

'======================================================================

Case FD_WRITE

    'This message means that the socket in a write-able
    'state, that is, buffer for outgoing data of the transport
    'service is empty and ready to receive data to send through
    'the network.
    
    'Debug.Print "FD_WRITE " & m_lngSocketHandle
    
    If m_enmState <> sckConnected Then
        'Debug.Print "WARNING: Omitting FD_WRITE"
        Exit Sub
    End If
    
    If Len(m_strSendBuffer) > 0 Then
        SendBufferedData
    End If
    
'======================================================================

Case FD_READ

    'Some data has arrived for this socket.

    'Debug.Print "FD_READ " & m_lngSocketHandle
    
    If m_enmProtocol = sckTCPProtocol Then
        
        If m_enmState <> sckConnected Then
            'Debug.Print "WARNING: Omitting FD_READ"
            Exit Sub
        End If
        
        'Call the RecvDataToBuffer function that move arrived data
        'from the Winsock buffer to the local one and returns number
        'of bytes received.
    
        lngBytesReceived = RecvDataToBuffer
    
        If lngBytesReceived > 0 Then
            RaiseEvent DataArrival(Len(m_strRecvBuffer))
        End If
    
    Else 'UDP protocol
        
        If m_enmState <> sckOpen Then
            'Debug.Print "WARNING: Omitting FD_READ"
            Exit Sub
        End If
        
        'If we use UDP we don't remove data from winsock buffer.
        'We just let the user know the amount received so
        'he/she can decide what to do.
        
        lngBytesReceived = GetBufferLenUDP
        
        If lngBytesReceived > 0 Then
            RaiseEvent DataArrival(lngBytesReceived)
        End If
        
        
        'Now the buffer is emptied no matter what the user
        'dicided to do with the received data
        EmptyBuffer
    End If
    
    
'======================================================================

Case FD_ACCEPT

    'When the socket is in a listening state, arrival of this message
    'means that a connection request was received. Call the accept
    'Winsock API function in oreder to create a new socket for the
    'requested connection.
  
    'Debug.Print "FD_ACCEPT " & m_lngSocketHandle
    If m_enmState <> sckListening Then
        'Debug.Print "WARNING: Omitting FD_ACCEPT"
        Exit Sub
    End If
    
    lngResult = api_accept(m_lngSocketHandle, udtSockAddr, LenB(udtSockAddr))
    
    If lngResult = INVALID_SOCKET Then
        lngErrorCode = Err.LastDllError
        'err.raise lngErrorCode, "c.PostSocket", GetErrorDescription(lngErrorCode)
    Else
        'We assign a temporal instance of CSocketMaster to
        'handle this new socket until user accepts (or not)
        'the new connection
        modSocketMaster.RegisterAccept lngResult
        
        'We change remote info before firing ConnectionRequest
        'event so the user can see which host is trying to
        'connect.
        
        Dim lngTempRP As Long
        Dim strTempRHIP As String
        Dim strTempRH As String
        lngTempRP = m_lngRemotePort
        strTempRHIP = m_strRemoteHostIP
        strTempRH = m_strRemoteHost
        
        GetRemoteInfo lngResult, m_lngRemotePort, m_strRemoteHostIP, m_strRemoteHost
        
        'Debug.Print "OK Accepted socket: " & lngResult
        RaiseEvent ConnectionRequest(lngResult)
        
        'we return original info
        If m_enmState = sckListening Then
             m_lngRemotePort = lngTempRP
             m_strRemoteHostIP = strTempRHIP
             m_strRemoteHost = strTempRH
        End If
        
        'This is very important. If the connection wasn't accepted
        'we must close the socket.
        If IsAcceptRegistered(lngResult) Then
            api_closesocket lngResult
            modSocketMaster.UnregisterSocket lngResult
            modSocketMaster.UnregisterAccept lngResult
            'Debug.Print "OK Closed accepted socket: " & lngResult
        End If
    End If
    
'======================================================================
    
Case FD_CLOSE
    
    'This message means that the remote host is closing the conection
    
    'Debug.Print "FD_CLOSE " & m_lngSocketHandle
    
    If m_enmState <> sckConnected Then
        'Debug.Print "WARNING: Omitting FD_CLOSE"
        Exit Sub
    End If
    
    m_enmState = sckClosing: 'Debug.Print "STATE: sckClosing"
    RaiseEvent CloseSck
    
End Select
End Sub

'Connect to a given 32 bits long ip
Private Sub ConnectToIP(ByVal lngRemoteHostAddress As Long, ByVal lngErrorCode As Long)

Dim blnCancelDisplay As Boolean

'Check and handle errors
If lngErrorCode <> 0 Then
    m_enmState = sckError: 'Debug.Print "STATE: sckError"
    blnCancelDisplay = True
    RaiseEvent Error(lngErrorCode, GetErrorDescription(lngErrorCode), 0, "c.ConnectToIP", "", 0, blnCancelDisplay)
    'If blnCancelDisplay = False Then MsgBox GetErrorDescription(lngErrorCode), vbOKOnly, "c.ConnectToIP"
    Exit Sub
End If

'Here we bind the socket
If Not BindInternal Then Exit Sub

'Debug.Print "OK Connecting to: " + m_strRemoteHost + " " + m_strRemoteHostIP
m_enmState = sckConnecting: 'Debug.Print "STATE: sckConnecting"

Dim udtSockAddr As sockaddr_in
Dim lngResult As Long

'Build the sockaddr_in structure to pass it to the connect
'Winsock API function as an address of the remote host.
With udtSockAddr
    .sin_addr = lngRemoteHostAddress
    .sin_family = AF_INET
    .sin_port = api_htons(modSocketMaster.UnsignedToInteger(m_lngRemotePort))
End With

'Call the connect Winsock API function in order to establish connection.
lngResult = api_connect(m_lngSocketHandle, udtSockAddr, LenB(udtSockAddr))

'Check and handle errors
If lngResult = SOCKET_ERROR Then
    lngErrorCode = Err.LastDllError
    If lngErrorCode <> WSAEWOULDBLOCK Then
        If lngErrorCode = WSAEADDRNOTAVAIL Then
            'err.raise WSAEADDRNOTAVAIL, "c.ConnectToIP", GetErrorDescription(WSAEADDRNOTAVAIL)
        Else
            m_enmState = sckError: 'Debug.Print "STATE: sckError"
            blnCancelDisplay = True
            RaiseEvent Error(lngErrorCode, GetErrorDescription(lngErrorCode), 0, "c.ConnectToIP", "", 0, blnCancelDisplay)
            'If blnCancelDisplay = False Then MsgBox GetErrorDescription(lngErrorCode), vbOKOnly, "c.ConnectToIP"
        End If
    End If
End If

End Sub

Public Sub Bind(Optional LocalPort As Variant, Optional LocalIP As Variant)
If m_enmState <> sckClosed Then
    'err.raise sckInvalidOp, "c.Bind", "Invalid operation at current state"
End If

If BindInternal(LocalPort, LocalIP) Then
    m_enmState = sckOpen: 'Debug.Print "STATE: sckOpen"
End If
End Sub

'This function binds a socket to a local port and IP.
'Retunrs TRUE if it has success.
Private Function BindInternal(Optional ByVal varLocalPort As Variant, Optional ByVal varLocalIP As Variant) As Boolean
If m_enmState = sckOpen Then
    BindInternal = True
    Exit Function
End If

Dim lngLocalPortInternal As Long
Dim strLocalHostInternal As String
Dim strIP As String
Dim lngAddressInternal As Long
Dim lngResult As Long
Dim lngErrorCode As Long

BindInternal = False

'Check if varLocalPort is a number between 0 and 65535
If Not IsMissing(varLocalPort) Then
    
    If IsNumeric(varLocalPort) Then
        If varLocalPort < 0 Or varLocalPort > 65535 Then
            BindInternal = False
            'err.raise sckInvalidArg, "c.BindInternal", "The argument passed to a function was not in the correct format or in the specified range."
        Else
            lngLocalPortInternal = CLng(varLocalPort)
        End If
    Else
        BindInternal = False
        'err.raise sckUnsupported, "c.BindInternal", "Unsupported variant type."
    End If
    
Else
    
    lngLocalPortInternal = m_lngLocalPort
    
End If

If Not IsMissing(varLocalIP) Then
    If varLocalIP <> vbNullString Then
        strLocalHostInternal = CStr(varLocalIP)
    Else
        strLocalHostInternal = GetLocalIP
    End If
Else
    strLocalHostInternal = GetLocalIP
End If

'get a 32 bits long IP
lngAddressInternal = ResolveIfHostnameSync(strLocalHostInternal, strIP, lngResult)

If lngResult <> 0 Then
    'err.raise sckInvalidArg, "c.BindInternal", "Invalid argument"
End If

'create a socket if there isn't one yet
If Not SocketExists Then Exit Function

Dim udtSockAddr As sockaddr_in

With udtSockAddr
    .sin_addr = lngAddressInternal
    .sin_family = AF_INET
    .sin_port = api_htons(modSocketMaster.UnsignedToInteger(lngLocalPortInternal))
End With

'bind the socket
lngResult = api_bind(m_lngSocketHandle, udtSockAddr, LenB(udtSockAddr))

If lngResult = SOCKET_ERROR Then

    lngErrorCode = Err.LastDllError
    'err.raise lngErrorCode, "c.BindInternal", GetErrorDescription(lngErrorCode)
    
Else

    m_strLocalIP = strIP
    
    If lngLocalPortInternal <> 0 Then
    
        'Debug.Print "OK Bind HOST: " & strLocalHostInternal & " PORT: " & lngLocalPortInternal
        m_lngLocalPort = lngLocalPortInternal
        
    Else
        lngResult = GetLocalPort(m_lngSocketHandle)
        
        If lngResult = SOCKET_ERROR Then
            lngErrorCode = Err.LastDllError
            'err.raise lngErrorCode, "c.BindInternal", GetErrorDescription(lngErrorCode)
        Else
            'Debug.Print "OK Bind HOST: " & strLocalHostInternal & " PORT: " & lngResult
            m_lngLocalPortBind = lngResult
        End If
        
    End If
    
    BindInternal = True
End If
End Function

'Allocate some memory for HOSTEN structure and returns
'a pointer to this buffer if no error occurs.
'Returns 0 if it fails.
Private Function AllocateMemory() As Long
m_lngMemoryHandle = api_GlobalAlloc(GMEM_FIXED, MAXGETHOSTSTRUCT)

If m_lngMemoryHandle <> 0 Then
    m_lngMemoryPointer = api_GlobalLock(m_lngMemoryHandle)
    
    If m_lngMemoryPointer <> 0 Then
        api_GlobalUnlock (m_lngMemoryHandle)
        AllocateMemory = m_lngMemoryPointer
    Else
        api_GlobalFree (m_lngMemoryHandle)
        AllocateMemory = m_lngMemoryPointer '0
    End If

Else
    AllocateMemory = m_lngMemoryHandle '0
End If
End Function

'Free memory allocated by AllocateMemory
Private Sub FreeMemory()
If m_lngMemoryHandle <> 0 Then
    m_lngMemoryHandle = 0
    m_lngMemoryPointer = 0
    api_GlobalFree m_lngMemoryHandle
End If
End Sub

Private Function GetLocalHostName() As String
Dim strHostNameBuf As String * LOCAL_HOST_BUFF
Dim lngResult As Long

lngResult = api_gethostname(strHostNameBuf, LOCAL_HOST_BUFF)

If lngResult = SOCKET_ERROR Then
    GetLocalHostName = vbNullString
    Dim lngErrorCode As Long
    lngErrorCode = Err.LastDllError
    'err.raise lngErrorCode, "c.GetLocalHostName", GetErrorDescription(lngErrorCode)
Else
    GetLocalHostName = Left(strHostNameBuf, InStr(1, strHostNameBuf, Chr(0)) - 1)
End If
End Function

Private Function GetLocalIP() As String
Dim lngResult As Long
Dim lngPtrToIP As Long
Dim strLocalHost As String
Dim arrIpAddress(1 To 4) As Byte
Dim Count As Integer
Dim udtHostent As HOSTENT
Dim strIpAddress As String

strLocalHost = GetLocalHostName

lngResult = api_gethostbyname(strLocalHost)

If lngResult = 0 Then
    GetLocalIP = vbNullString
    Dim lngErrorCode As Long
    lngErrorCode = Err.LastDllError
    'err.raise lngErrorCode, "c.GetLocalIP", GetErrorDescription(lngErrorCode)
Else
    api_CopyMemory udtHostent, ByVal lngResult, LenB(udtHostent)
    api_CopyMemory lngPtrToIP, ByVal udtHostent.hAddrList, 4
    api_CopyMemory arrIpAddress(1), ByVal lngPtrToIP, 4
   
    For Count = 1 To 4
        strIpAddress = strIpAddress & arrIpAddress(Count) & "."
    Next
   
    strIpAddress = Left$(strIpAddress, Len(strIpAddress) - 1)
    GetLocalIP = strIpAddress
End If
End Function

'If Host is an IP doesn't resolve anything and returns a
'a 32 bits long IP.
'If Host isn't an IP then returns vbNull, tries to resolve it
'in asynchronous way and acts according to enmDestination.
Private Function ResolveIfHostname(ByVal Host As String, ByVal enmDestination As DestResolucion) As Long
Dim lngAddress As Long
lngAddress = api_inet_addr(Host)

If lngAddress = INADDR_NONE Then 'if Host isn't an IP
    
    ResolveIfHostname = vbNull
    m_enmState = sckResolvingHost: 'Debug.Print "STATE: sckResolvingHost"
    
    If AllocateMemory Then
        
        Dim lngAsynHandle As Long
        lngAsynHandle = modSocketMaster.ResolveHost(Host, m_lngMemoryPointer, ObjPtr(Me))
        
        If lngAsynHandle = 0 Then
            FreeMemory
            m_enmState = sckError: 'Debug.Print "STATE: sckError"
            Dim lngErrorCode As Long
            lngErrorCode = Err.LastDllError
            Dim blnCancelDisplay As Boolean
            blnCancelDisplay = True
            RaiseEvent Error(lngErrorCode, GetErrorDescription(lngErrorCode), 0, "c.ResolveIfHostname", "", 0, blnCancelDisplay)
            'If blnCancelDisplay = False Then MsgBox GetErrorDescription(lngErrorCode), vbOKOnly, "c.ResolveIfHostname"
        Else
            m_colWaitingResolutions.Add enmDestination, "R" & lngAsynHandle
            'Debug.Print "Resolving host " & Host; " with handle " & lngAsynHandle
        End If
        
    Else
        
        m_enmState = sckError: 'Debug.Print "STATE: sckError"
        'Debug.Print "Error trying to allocate memory"
        'err.raise sckOutOfMemory, "c.ResolveIfHostname", "Out of memory"
        
    End If
    
Else 'if Host is an IP doen't need to resolve anything
    ResolveIfHostname = lngAddress
End If
End Function

'Resolves a hots (if necessary) in synchronous way
'If succeeds returns a 32 bits long IP,
'strHostIP = readable IP string and lngErrorCode = 0
'If fails returns vbNull,
'strHostIP = vbNullString and lngErrorCode <> 0
Private Function ResolveIfHostnameSync(ByVal Host As String, ByRef strHostIP As String, ByRef lngErrorCode As Long) As Long
Dim lngPtrToHOSTENT As Long
Dim udtHostent As HOSTENT
Dim lngAddress As Long
Dim lngPtrToIP As Long
Dim arrIpAddress(1 To 4) As Byte
Dim Count As Integer

If Host = vbNullString Then
    strHostIP = vbNullString
    lngErrorCode = WSAEAFNOSUPPORT
    ResolveIfHostnameSync = vbNull
    Exit Function
End If

lngAddress = api_inet_addr(Host)

If lngAddress = INADDR_NONE Then 'if Host isn't an IP
    
    lngPtrToHOSTENT = api_gethostbyname(Host)
    
    If lngPtrToHOSTENT = 0 Then
        lngErrorCode = Err.LastDllError
        strHostIP = vbNullString
        ResolveIfHostnameSync = vbNull
    Else
        api_CopyMemory udtHostent, ByVal lngPtrToHOSTENT, LenB(udtHostent)
        api_CopyMemory lngPtrToIP, ByVal udtHostent.hAddrList, 4
        api_CopyMemory arrIpAddress(1), ByVal lngPtrToIP, 4
        api_CopyMemory lngAddress, ByVal lngPtrToIP, 4
        
        For Count = 1 To 4
            strHostIP = strHostIP & arrIpAddress(Count) & "."
        Next
        
        strHostIP = Left$(strHostIP, Len(strHostIP) - 1)
        
        lngErrorCode = 0
        ResolveIfHostnameSync = lngAddress
    End If
    
Else 'if Host is an IP doen't need to resolve anything
    
    lngErrorCode = 0
    strHostIP = Host
    ResolveIfHostnameSync = lngAddress
    
End If
End Function

'Returns local port from a connected or bound socket.
'Returns SOCKET_ERROR if fails.
Private Function GetLocalPort(ByVal lngSocket As Long) As Long
Dim udtSockAddr As sockaddr_in
Dim lngResult As Long

lngResult = api_getsockname(lngSocket, udtSockAddr, LenB(udtSockAddr))

If lngResult = SOCKET_ERROR Then
    GetLocalPort = SOCKET_ERROR
Else
    GetLocalPort = modSocketMaster.IntegerToUnsigned(api_ntohs(udtSockAddr.sin_port))
End If
End Function

Public Sub SendData(data As Variant)

Dim arrData() As Byte 'We store the data here before send it

If m_enmProtocol = sckTCPProtocol Then
    If m_enmState <> sckConnected Then
        'err.raise sckBadState, "c.SendData", "Wrong protocol or connection state for the requested transaction or request"
        Exit Sub
    End If
Else 'If we use UDP we create a socket if there isn't one yet
    If Not SocketExists Then Exit Sub
    If Not BindInternal Then Exit Sub
    m_enmState = sckOpen: 'Debug.Print "STATE: sckOpen"
End If

'We need to convert data variant into a byte array
Select Case varType(data)
        Case vbString
            Dim strdata As String
            strdata = CStr(data)
            If Len(strdata) = 0 Then Exit Sub
            ReDim arrData(Len(strdata) - 1)
            arrData() = StrConv(strdata, vbFromUnicode)
        Case vbArray + vbByte
            Dim strArray As String
            strArray = StrConv(data, vbUnicode)
            If Len(strArray) = 0 Then Exit Sub
            arrData() = StrConv(strArray, vbFromUnicode)
        Case vbBoolean
            Dim blnData As Boolean
            blnData = CBool(data)
            ReDim arrData(LenB(blnData) - 1)
            api_CopyMemory arrData(0), blnData, LenB(blnData)
        Case vbByte
            Dim bytData As Byte
            bytData = CByte(data)
            ReDim arrData(LenB(bytData) - 1)
            api_CopyMemory arrData(0), bytData, LenB(bytData)
        Case vbCurrency
            Dim curData As Currency
            curData = CCur(data)
            ReDim arrData(LenB(curData) - 1)
            api_CopyMemory arrData(0), curData, LenB(curData)
        Case vbDate
            Dim datData As Date
            datData = CDate(data)
            ReDim arrData(LenB(datData) - 1)
            api_CopyMemory arrData(0), datData, LenB(datData)
        Case vbDouble
            Dim dblData As Double
            dblData = CDbl(data)
            ReDim arrData(LenB(dblData) - 1)
            api_CopyMemory arrData(0), dblData, LenB(dblData)
        Case vbInteger
            Dim intData As Integer
            intData = CInt(data)
            ReDim arrData(LenB(intData) - 1)
            api_CopyMemory arrData(0), intData, LenB(intData)
        Case vbLong
            Dim lngData As Long
            lngData = CLng(data)
            ReDim arrData(LenB(lngData) - 1)
            api_CopyMemory arrData(0), lngData, LenB(lngData)
        Case vbSingle
            Dim sngData As Single
            sngData = CSng(data)
            ReDim arrData(LenB(sngData) - 1)
            api_CopyMemory arrData(0), sngData, LenB(sngData)
        Case Else
            'err.raise sckUnsupported, "c.SendData", "Unsupported variant type."
    End Select

'if there's already something in the buffer that means we are
'already sending data, so we put the new data in the buffer
'and exit silently
If Len(m_strSendBuffer) > 0 Then
    m_strSendBuffer = m_strSendBuffer + StrConv(arrData(), vbUnicode)
    Exit Sub
Else
    m_strSendBuffer = m_strSendBuffer + StrConv(arrData(), vbUnicode)
End If

'send the data
SendBufferedData

End Sub

'Check which protocol we are using to decide which
'function should handle the data sending.
Private Sub SendBufferedData()
If m_enmProtocol = sckTCPProtocol Then
    SendBufferedDataTCP
Else
    SendBufferedDataUDP
End If
End Sub

'Send buffered data if we are using UDP protocol.
Private Sub SendBufferedDataUDP()
Dim lngAddress As Long
Dim udtSockAddr As sockaddr_in
Dim arrData() As Byte
Dim lngBufferLength As Long
Dim lngResult As Long
Dim lngErrorCode As Long

   
Dim strTemp As String
lngAddress = ResolveIfHostnameSync(m_strRemoteHost, strTemp, lngErrorCode)
    
If lngErrorCode <> 0 Then
    m_strSendBuffer = ""
    
    If lngErrorCode = WSAEAFNOSUPPORT Then
        'err.raise lngErrorCode, "c.SendBufferedDataUDP", GetErrorDescription(lngErrorCode)
    Else
        'err.raise sckInvalidArg, "c.SendBufferedDataUDP", "Invalid argument"
    End If
End If

With udtSockAddr
    .sin_addr = lngAddress
    .sin_family = AF_INET
    .sin_port = api_htons(modSocketMaster.UnsignedToInteger(m_lngRemotePort))
End With
    
lngBufferLength = Len(m_strSendBuffer)
    
arrData() = StrConv(m_strSendBuffer, vbFromUnicode)
    
m_strSendBuffer = ""

lngResult = api_sendto(m_lngSocketHandle, arrData(0), lngBufferLength, 0&, udtSockAddr, LenB(udtSockAddr))
    
If lngResult = SOCKET_ERROR Then
    lngErrorCode = Err.LastDllError
    m_enmState = sckError: 'Debug.Print "STATE: sckError"
    Dim blnCancelDisplay As Boolean
    blnCancelDisplay = True
    RaiseEvent Error(lngErrorCode, GetErrorDescription(lngErrorCode), 0, "c.SendBufferedDataUDP", "", 0, blnCancelDisplay)
    'If blnCancelDisplay = False Then MsgBox GetErrorDescription(lngErrorCode), vbOKOnly, "c.SendBufferedDataUDP"
End If
    
End Sub

'Send buffered data if we are using TCP protocol.
Private Sub SendBufferedDataTCP()

Dim arrData()       As Byte
Dim lngBufferLength As Long
Dim lngResult    As Long
Dim lngTotalSent As Long

Do Until lngResult = SOCKET_ERROR Or Len(m_strSendBuffer) = 0

    lngBufferLength = Len(m_strSendBuffer)

    If lngBufferLength > m_lngSendBufferLen Then
        lngBufferLength = m_lngSendBufferLen
        arrData() = StrConv(Left$(m_strSendBuffer, m_lngSendBufferLen), vbFromUnicode)
    Else
        arrData() = StrConv(m_strSendBuffer, vbFromUnicode)
    End If

    lngResult = api_send(m_lngSocketHandle, arrData(0), lngBufferLength, 0&)

    If lngResult = SOCKET_ERROR Then
        Dim lngErrorCode As Long
        lngErrorCode = Err.LastDllError
    
        If lngErrorCode = WSAEWOULDBLOCK Then
            'Debug.Print "WARNING: Send buffer full, waiting..."
            If lngTotalSent > 0 Then RaiseEvent SendProgress(lngTotalSent, Len(m_strSendBuffer))
        Else
            m_enmState = sckError: 'Debug.Print "STATE: sckError"
            Dim blnCancelDisplay As Boolean
            blnCancelDisplay = True
            RaiseEvent Error(lngErrorCode, GetErrorDescription(lngErrorCode), 0, "c.SendBufferedData", "", 0, blnCancelDisplay)
            'If blnCancelDisplay = False Then MsgBox GetErrorDescription(lngErrorCode), vbOKOnly, "c.SendBufferedData"
        End If

    Else
        'Debug.Print "OK Bytes sent: " & lngResult
        lngTotalSent = lngTotalSent + lngResult
        If Len(m_strSendBuffer) > lngResult Then
            m_strSendBuffer = Mid$(m_strSendBuffer, lngResult + 1)
        Else
            'Debug.Print "OK Finished SENDING"
            m_strSendBuffer = ""
            Dim lngTemp As Long
            lngTemp = lngTotalSent
            lngTotalSent = 0
            RaiseEvent SendProgress(lngTemp, 0)
            RaiseEvent SendComplete
        End If
    End If

Loop

End Sub

'This function retrieves data from the Winsock buffer
'into the class local buffer. The function returns number
'of bytes retrieved (received).
Private Function RecvDataToBuffer() As Long
Dim arrBuffer() As Byte
Dim lngBytesReceived As Long
Dim strBuffTemporal As String

ReDim arrBuffer(m_lngRecvBufferLen - 1)

lngBytesReceived = api_recv(m_lngSocketHandle, arrBuffer(0), m_lngRecvBufferLen, 0&)

If lngBytesReceived = SOCKET_ERROR Then
    
    m_enmState = sckError: 'Debug.Print "STATE: sckError"
    Dim lngErrorCode As Long
    lngErrorCode = Err.LastDllError
    'err.raise lngErrorCode, "c.RecvDataToBuffer", GetErrorDescription(lngErrorCode)
    
ElseIf lngBytesReceived > 0 Then
    
    strBuffTemporal = StrConv(arrBuffer(), vbUnicode)
    m_strRecvBuffer = m_strRecvBuffer & Left$(strBuffTemporal, lngBytesReceived)
    RecvDataToBuffer = lngBytesReceived
    
End If

End Function

'Retrieves some socket options.
'If it is an UDP socket also sets SO_BROADCAST option.
Private Sub ProcessOptions()
Dim lngResult As Long
Dim lngBuffer As Long
Dim lngErrorCode As Long

If m_enmProtocol = sckTCPProtocol Then
    lngResult = api_getsockopt(m_lngSocketHandle, SOL_SOCKET, SO_RCVBUF, lngBuffer, LenB(lngBuffer))
    
    If lngResult = SOCKET_ERROR Then
        lngErrorCode = Err.LastDllError
        'err.raise lngErrorCode, "c.ProcessOptions", GetErrorDescription(lngErrorCode)
    Else
        m_lngRecvBufferLen = lngBuffer
    End If

    lngResult = api_getsockopt(m_lngSocketHandle, SOL_SOCKET, SO_SNDBUF, lngBuffer, LenB(lngBuffer))

    If lngResult = SOCKET_ERROR Then
        lngErrorCode = Err.LastDllError
        'err.raise lngErrorCode, "c.ProcessOptions", GetErrorDescription(lngErrorCode)
    Else
        m_lngSendBufferLen = lngBuffer
    End If

Else
    lngBuffer = 1
    lngResult = api_setsockopt(m_lngSocketHandle, SOL_SOCKET, SO_BROADCAST, lngBuffer, LenB(lngBuffer))
    
    lngResult = api_getsockopt(m_lngSocketHandle, SOL_SOCKET, SO_MAX_MSG_SIZE, lngBuffer, LenB(lngBuffer))

    If lngResult = SOCKET_ERROR Then
        lngErrorCode = Err.LastDllError
        'err.raise lngErrorCode, "c.ProcessOptions", GetErrorDescription(lngErrorCode)
    Else
        m_lngRecvBufferLen = lngBuffer
        m_lngSendBufferLen = lngBuffer
    End If
End If


'Debug.Print "Winsock buffer size for sends: " & m_lngRecvBufferLen
'Debug.Print "Winsock buffer size for receives: " & m_lngSendBufferLen
End Sub

Public Sub GetData(ByRef data As Variant, Optional varType As Variant, Optional maxLen As Variant)

If m_enmProtocol = sckTCPProtocol Then
    If m_enmState <> sckConnected And Not m_blnAcceptClass Then
        'err.raise sckBadState, "c.GetData", "Wrong protocol or connection state for the requested transaction or request"
        Exit Sub
    End If
Else
    If m_enmState <> sckOpen Then
        'err.raise sckBadState, "c.GetData", "Wrong protocol or connection state for the requested transaction or request"
        Exit Sub
    End If
    If GetBufferLenUDP = 0 Then Exit Sub
End If

If Not IsMissing(maxLen) Then
    If IsNumeric(maxLen) Then
        If CLng(maxLen) < 0 Then
            'err.raise sckInvalidArg, "c.GetData", "The argument passed to a function was not in the correct format or in the specified range."
        End If
    Else
        If m_enmProtocol = sckTCPProtocol Then
            maxLen = Len(m_strRecvBuffer)
        Else
            maxLen = GetBufferLenUDP
        End If
    End If
End If

Dim lngBytesRecibidos  As Long

lngBytesRecibidos = RecvData(data, False, varType, maxLen)
'Debug.Print "OK Bytes obtained from buffer: " & lngBytesRecibidos

End Sub

Public Sub PeekData(ByRef data As Variant, Optional varType As Variant, Optional maxLen As Variant)

End Sub


'This function is to retrieve data from the buffer. If we are using TCP
'then the data is retrieved from a local buffer (m_strRecvBuffer). If we
'are using UDP the data is retrieved from winsock buffer.
'It can be called by two public methods of the class - GetData and PeekData.
'Behavior of the function is defined by the blnPeek argument. If a value of
'that argument is TRUE, the function returns number of bytes in the
'buffer, and copy data from that buffer into the data argument.
'If a value of the blnPeek is FALSE, then this function returns number of
'bytes received, and move data from the buffer into the data
'argument. MOVE means that data will be removed from the buffer.
Private Function RecvData(ByRef data As Variant, ByVal blnPeek As Boolean, Optional varClass As Variant, Optional maxLen As Variant) As Long

Dim blnMaxLenMiss   As Boolean
Dim blnClassMiss As Boolean
Dim strRecvData     As String
Dim lngBufferLen    As Long
Dim arrBuffer()     As Byte
Dim lngErrorCode    As Long

If m_enmProtocol = sckTCPProtocol Then
    lngBufferLen = Len(m_strRecvBuffer)
Else
    lngBufferLen = GetBufferLenUDP
End If

blnMaxLenMiss = IsMissing(maxLen)
blnClassMiss = IsMissing(varClass)

'Select type of data
If varType(data) = vbEmpty Then
    If blnClassMiss Then varClass = vbArray + vbByte
Else
    varClass = varType(data)
End If

'As stated on Winsock control documentation if the
'data type passed is string or byte array type then
'we must take into account maxLen argument.
'If it is another type maxLen is ignored.
If varClass = vbString Or varClass = vbArray + vbByte Then

    If blnMaxLenMiss Then 'if maxLen argument is missing
    
        If lngBufferLen = 0 Then
        
            RecvData = 0
        
            arrBuffer = StrConv("", vbFromUnicode)
            data = arrBuffer

            Exit Function
    
        Else
            
            RecvData = lngBufferLen
            arrBuffer = BuildArray(lngBufferLen, blnPeek, lngErrorCode)

        End If

    Else 'if maxLen argument is not missing

        If maxLen = 0 Or lngBufferLen = 0 Then

            RecvData = 0
        
            arrBuffer = StrConv("", vbFromUnicode)
            data = arrBuffer
            
            If m_enmProtocol = sckUDPProtocol Then
                EmptyBuffer
                'err.raise WSAEMSGSIZE, "c.RecvData", GetErrorDescription(WSAEMSGSIZE)
            End If
            
            Exit Function
        
        ElseIf maxLen > lngBufferLen Then
            
            RecvData = lngBufferLen
            arrBuffer = BuildArray(lngBufferLen, blnPeek, lngErrorCode)

        Else
            
            RecvData = CLng(maxLen)
            arrBuffer() = BuildArray(CLng(maxLen), blnPeek, lngErrorCode)

        End If
    
    End If
        
End If

    Select Case varClass
    
    Case vbString
        Dim strdata As String
        strdata = StrConv(arrBuffer(), vbUnicode)
        data = strdata
    Case vbArray + vbByte
        data = arrBuffer
    Case vbBoolean
        Dim blnData As Boolean
        If LenB(blnData) > lngBufferLen Then Exit Function
        arrBuffer = BuildArray(LenB(blnData), blnPeek, lngErrorCode)
        RecvData = LenB(blnData)
        api_CopyMemory blnData, arrBuffer(0), LenB(blnData)
        data = blnData
    Case vbByte
        Dim bytData As Byte
        If LenB(bytData) > lngBufferLen Then Exit Function
        arrBuffer = BuildArray(LenB(bytData), blnPeek, lngErrorCode)
        RecvData = LenB(bytData)
        api_CopyMemory bytData, arrBuffer(0), LenB(bytData)
        data = bytData
    Case vbCurrency
        Dim curData As Currency
        If LenB(curData) > lngBufferLen Then Exit Function
        arrBuffer = BuildArray(LenB(curData), blnPeek, lngErrorCode)
        RecvData = LenB(curData)
        api_CopyMemory curData, arrBuffer(0), LenB(curData)
        data = curData
    Case vbDate
        Dim datData As Date
        If LenB(datData) > lngBufferLen Then Exit Function
        arrBuffer = BuildArray(LenB(datData), blnPeek, lngErrorCode)
        RecvData = LenB(datData)
        api_CopyMemory datData, arrBuffer(0), LenB(datData)
        data = datData
    Case vbDouble
        Dim dblData As Double
        If LenB(dblData) > lngBufferLen Then Exit Function
        arrBuffer = BuildArray(LenB(dblData), blnPeek, lngErrorCode)
        RecvData = LenB(dblData)
        api_CopyMemory dblData, arrBuffer(0), LenB(dblData)
        data = dblData
    Case vbInteger
        Dim intData As Integer
        If LenB(intData) > lngBufferLen Then Exit Function
        arrBuffer = BuildArray(LenB(intData), blnPeek, lngErrorCode)
        RecvData = LenB(intData)
        api_CopyMemory intData, arrBuffer(0), LenB(intData)
        data = intData
    Case vbLong
        Dim lngData As Long
        If LenB(lngData) > lngBufferLen Then Exit Function
        arrBuffer = BuildArray(LenB(lngData), blnPeek, lngErrorCode)
        RecvData = LenB(lngData)
        api_CopyMemory lngData, arrBuffer(0), LenB(lngData)
        data = lngData
    Case vbSingle
        Dim sngData As Single
        If LenB(sngData) > lngBufferLen Then Exit Function
        arrBuffer = BuildArray(LenB(sngData), blnPeek, lngErrorCode)
        RecvData = LenB(sngData)
        api_CopyMemory sngData, arrBuffer(0), LenB(sngData)
        data = sngData
    Case Else
        'err.raise sckUnsupported, "c.RecvData", "Unsupported variant type."
       
    End Select

'if BuildArray returns an error is handled here
If lngErrorCode <> 0 Then
    'err.raise lngErrorCode, "c.RecvData", GetErrorDescription(lngErrorCode)
End If

End Function

'Returns a byte array of Size bytes filled with incoming buffer data.
Private Function BuildArray(ByVal Size As Long, ByVal blnPeek As Boolean, ByRef lngErrorCode As Long) As Byte()
Dim strdata As String

If m_enmProtocol = sckTCPProtocol Then
        
    strdata = Left$(m_strRecvBuffer, CLng(Size))
    BuildArray = StrConv(strdata, vbFromUnicode)
                
    If Not blnPeek Then
        m_strRecvBuffer = Mid$(m_strRecvBuffer, Size + 1)
    End If

Else 'UDP protocol
    Dim arrBuffer() As Byte
    Dim lngResult As Long
    Dim udtSockAddr As sockaddr_in
    Dim lngFlags As Long
    
    If blnPeek Then lngFlags = MSG_PEEK
    
    ReDim arrBuffer(Size - 1)
    
    lngResult = api_recvfrom(m_lngSocketHandle, arrBuffer(0), Size, lngFlags, udtSockAddr, LenB(udtSockAddr))
    
    If lngResult = SOCKET_ERROR Then
        lngErrorCode = Err.LastDllError
    End If
    
    BuildArray = arrBuffer
    GetRemoteInfoFromSI udtSockAddr, m_lngRemotePort, m_strRemoteHostIP, m_strRemoteHost
    
End If
End Function

'Clean resolution system that is in charge of
'asynchronous hostname resolutions.
Private Sub CleanResolutionSystem()
Dim varAsynHandle As Variant

'cancel async resolutions if they're still running
For Each varAsynHandle In m_colWaitingResolutions
    api_WSACancelAsyncRequest varAsynHandle
    modSocketMaster.UnregisterResolution varAsynHandle
Next

'free memory buffer where resolution results are stored
FreeMemory
End Sub

Public Sub Listen()
If m_enmState <> sckClosed And m_enmState <> sckOpen Then
    'err.raise sckInvalidOp, "c.Listen", "Invalid operation at current state"
End If

If Not SocketExists Then Exit Sub
If Not BindInternal Then Exit Sub

Dim lngResult As Long

lngResult = api_listen(m_lngSocketHandle, SOMAXCONN)

If lngResult = SOCKET_ERROR Then
    Dim lngErrorCode As Long
    lngErrorCode = Err.LastDllError
    'err.raise lngErrorCode, "c.Listen", GetErrorDescription(lngErrorCode)
Else
    m_enmState = sckListening: 'Debug.Print "STATE: sckListening"
End If

End Sub

Public Sub Accept(requestID As Long)
If m_enmState <> sckClosed Then
    'err.raise sckInvalidOp, "c.Accept", "Invalid operation at current state"
End If

Dim lngResult As Long
Dim udtSockAddr As sockaddr_in
Dim lngErrorCode As Long

m_lngSocketHandle = requestID
m_enmProtocol = sckTCPProtocol
ProcessOptions

If Not modSocketMaster.IsAcceptRegistered(requestID) Then
    If IsSocketRegistered(requestID) Then
        'err.raise sckBadState, "c.Accept", "Wrong protocol or connection state for the requested transaction or request"
    Else
        m_blnAcceptClass = True
        m_enmState = sckConnected: 'Debug.Print "STATE: sckConnected"
        modSocketMaster.RegisterSocket m_lngSocketHandle, ObjPtr(Me), False
        Exit Sub
    End If
End If

Dim clsSocket As CSocketMaster
Set clsSocket = GetAcceptClass(requestID)
modSocketMaster.UnregisterAccept requestID

lngResult = api_getsockname(m_lngSocketHandle, udtSockAddr, LenB(udtSockAddr))

If lngResult = SOCKET_ERROR Then
    
    lngErrorCode = Err.LastDllError
    'err.raise lngErrorCode, "c.Accept", GetErrorDescription(lngErrorCode)
    
Else

    m_lngLocalPortBind = IntegerToUnsigned(api_ntohs(udtSockAddr.sin_port))
    m_strLocalIP = StringFromPointer(api_inet_ntoa(udtSockAddr.sin_addr))
    
End If

GetRemoteInfo m_lngSocketHandle, m_lngRemotePort, m_strRemoteHostIP, m_strRemoteHost
m_enmState = sckConnected: 'Debug.Print "STATE: sckConnected"

If clsSocket.BytesReceived > 0 Then
    clsSocket.GetData m_strRecvBuffer
End If

modSocketMaster.Subclass_ChangeOwner requestID, ObjPtr(Me)

If Len(m_strRecvBuffer) > 0 Then RaiseEvent DataArrival(Len(m_strRecvBuffer))

If clsSocket.State = sckClosing Then
    m_enmState = sckClosing: 'Debug.Print "STATE: sckClosing"
    RaiseEvent CloseSck
End If

Set clsSocket = Nothing
End Sub

'Retrieves remote info from a connected socket.
'If succeeds returns TRUE and loads the arguments.
'If fails returns FALSE and arguments are not loaded.
Private Function GetRemoteInfo(ByVal lngSocket As Long, ByRef lngRemotePort As Long, ByRef strRemoteHostIP As String, ByRef strRemoteHost As String) As Boolean
GetRemoteInfo = False
Dim lngResult As Long
Dim udtSockAddr As sockaddr_in

lngResult = api_getpeername(lngSocket, udtSockAddr, LenB(udtSockAddr))

If lngResult = 0 Then
    GetRemoteInfo = True
    GetRemoteInfoFromSI udtSockAddr, lngRemotePort, strRemoteHostIP, strRemoteHost
Else
   lngRemotePort = 0
   strRemoteHostIP = ""
   strRemoteHost = ""
End If
End Function

'Gets remote info from a sockaddr_in structure.
Private Sub GetRemoteInfoFromSI(ByRef udtSockAddr As sockaddr_in, ByRef lngRemotePort As Long, ByRef strRemoteHostIP As String, ByRef strRemoteHost As String)

'Dim lngResult As Long
'Dim udtHostent As HOSTENT

lngRemotePort = IntegerToUnsigned(api_ntohs(udtSockAddr.sin_port))
strRemoteHostIP = StringFromPointer(api_inet_ntoa(udtSockAddr.sin_addr))
'lngResult = api_gethostbyaddr(udtSockAddr.sin_addr, 4&, AF_INET)

'If lngResult <> 0 Then
'    api_CopyMemory udtHostent, ByVal lngResult, LenB(udtHostent)
'    strRemoteHost = StringFromPointer(udtHostent.hName)
'Else
    m_strRemoteHost = ""
'End If

End Sub

'Returns winsock incoming buffer length from an UDP socket.
Private Function GetBufferLenUDP() As Long
Dim lngResult As Long
Dim lngBuffer As Long
lngResult = api_ioctlsocket(m_lngSocketHandle, FIONREAD, lngBuffer)

If lngResult = SOCKET_ERROR Then
    GetBufferLenUDP = 0
Else
    GetBufferLenUDP = lngBuffer
End If
End Function

'Empty winsock incoming buffer from an UDP socket.
Private Sub EmptyBuffer()
Dim B As Byte
api_recv m_lngSocketHandle, B, Len(B), 0&
End Sub
