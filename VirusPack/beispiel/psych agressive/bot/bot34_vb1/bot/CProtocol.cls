VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CProtocol"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
' Dieser Source stammt von http://www.activevb.de
' und kann frei verwendet werden. Für eventuelle Schäden
' wird nicht gehaftet.
' Um Fehler oder Fragen zu klären, nutzen Sie bitte unser Forum.
' Ansonsten viel Spaß und Erfolg mit diesem Source!

Option Explicit

'local variable(s) to hold property value(s)
Private mvarConnectionless As Boolean 'local copy
Private mvarGuaranteedDelivery As Boolean 'local copy
Private mvarGuaranteedOrder As Boolean 'local copy
Private mvarMessageOriented As Boolean 'local copy
Private mvarPseudoStream As Boolean 'local copy
Private mvarGracefulClose As Boolean 'local copy
Private mvarExpeditedData As Boolean 'local copy
Private mvarConnectData As Boolean 'local copy
Private mvarDisconnectData As Boolean 'local copy
Private mvarSupportBroadcast As Boolean 'local copy
Private mvarSupportMultipoint As Boolean 'local copy
Private mvarMultipointControlPlane As Boolean 'local copy
Private mvarMultipointDataPlane As Boolean 'local copy
Private mvarQoSSupport As Boolean 'local copy
Private mvarUniSend As Boolean 'local copy
Private mvarUniRecv As Boolean 'local copy
Private mvarIFSHandles As Boolean 'local copy
Private mvarPartialMessage As Boolean 'local copy
Private mvarMultipleProtoEntries As Boolean 'local copy
Private mvarRecommendedProtoEntry As Boolean 'local copy
Private mvarMatchesProtocolZero As Boolean 'local copy
Private mvarProviderId As String 'local copy
Private mvarCatalogEntryId As Long 'local copy
Private mvarVersion As Long 'local copy
Private mvarAddressFamily As Long 'local copy
Private mvarMaxSockAddr As Long 'local copy
Private mvarMinSockAddr As Long 'local copy
Private mvarSocketType As Long 'local copy
Private mvarProtocol As Long 'local copy
Private mvarProtocolMaxOffset As Long 'local copy
Private mvarNetworkByteOrder As Long 'local copy
Private mvarSecurityScheme As Long 'local copy
Private mvarMessageSize As Long 'local copy
Private mvarProtocolName As String 'local copy

Private Const BASE_PROTOCOL = 1
Private Const LAYERED_PROTOCOL = 0

'/* Flag bit definitions for dwProviderFlags */
Private Const PFL_MULTIPLE_PROTO_ENTRIES = &H1
Private Const PFL_RECOMMENDED_PROTO_ENTRY = &H2
Private Const PFL_HIDDEN = &H4
Private Const PFL_MATCHES_PROTOCOL_ZERO = &H8

'/* Flag bit definitions for dwServiceFlags1 */
Private Const XP1_CONNECTIONLESS = &H1
Private Const XP1_GUARANTEED_DELIVERY = &H2
Private Const XP1_GUARANTEED_ORDER = &H4
Private Const XP1_MESSAGE_ORIENTED = &H8
Private Const XP1_PSEUDO_STREAM = &H10
Private Const XP1_GRACEFUL_CLOSE = &H20
Private Const XP1_EXPEDITED_DATA = &H40
Private Const XP1_CONNECT_DATA = &H80
Private Const XP1_DISCONNECT_DATA = &H100
Private Const XP1_SUPPORT_BROADCAST = &H200
Private Const XP1_SUPPORT_MULTIPOINT = &H400
Private Const XP1_MULTIPOINT_CONTROL_PLANE = &H800
Private Const XP1_MULTIPOINT_DATA_PLANE = &H1000
Private Const XP1_QOS_SUPPORTED = &H2000
Private Const XP1_INTERRUPT = &H4000
Private Const XP1_UNI_SEND = &H8000
Private Const XP1_UNI_RECV = &H10000
Private Const XP1_IFS_HANDLES = &H20000
Private Const XP1_PARTIAL_MESSAGE = &H40000

Private Const BIGENDIAN = &H0
Private Const LITTLEENDIAN = &H1

Private Const SECURITY_PROTOCOL_NONE = &H0

Private Const MAX_PROTOCOL_CHAIN = 6

Private Type WSAPROTOCOLCHAIN
  ChainLen As Long
  ChainEntries(MAX_PROTOCOL_CHAIN) As Long
End Type

Private Type Guid
    Data1 As Long
    Data2 As Integer
    Data3 As Integer
    Data4(0 To 7) As Byte
End Type

Private Declare Function StringFromGUID2 Lib "ole32.dll" ( _
            rguid As Any, _
            ByVal lpsz As String, _
            ByVal cchMax As Long) As Long

Private Const WSAPROTOCOL_LEN = 256

Private Type WSAPROTOCOL_INFO
    dwServiceFlags1 As Long
    dwServiceFlags2 As Long
    dwServiceFlags3 As Long
    dwServiceFlags4 As Long
    dwProviderFlags As Long
    ProviderId As Guid
    dwCatalogEntryId As Long
    ProtocolChain As WSAPROTOCOLCHAIN
    iVersion As Long
    iAddressFamily As Long
    iMaxSockAddr As Long
    iMinSockAddr As Long
    iSocketType As Long
    iProtocol As Long
    iProtocolMaxOffset As Long
    iNetworkByteOrder As Long
    iSecurityScheme As Long
    dwMessageSize As Long
    dwProviderReserved As Long
    szProtocol As String * WSAPROTOCOL_LEN
End Type

Private Declare Function WSAEnumProtocols Lib "ws2_32.dll" Alias "WSAEnumProtocolsA" ( _
            ByVal lpiProtocols As Long, _
            lpProtocolBuffer As Any, _
            lpdwBufferLength As Long) As Long

Private Const SOL_SOCKET = 65535
Private Const SO_PROTOCOL_INFO = &H2004

Private Declare Function getsockopt Lib "ws2_32.dll" ( _
            ByVal s As Long, _
            ByVal level As Long, _
            ByVal optname As Long, _
            ByRef optval As Any, _
            ByRef optlen As Long) As Long


                  
Private Function GuidToString(udtGuid As Guid) As String
    '
    Dim strGuid As String
    Dim lngRetVal As Long
    '
    strGuid = String(80, Chr(0))
    '
    lngRetVal = StringFromGUID2(udtGuid, strGuid, 80&)
    '
    If lngRetVal > 0 Then
        GuidToString = StrConv(strGuid, vbFromUnicode)
    End If
    '
End Function


Public Function GetBySocketHandle(lngSocket As Long) As Boolean
    '
    Dim lngRetValue     As Long
    Dim udtProtocolInfo As WSAPROTOCOL_INFO
    Dim lngBufferSize   As Long
    '
    lngBufferSize = LenB(udtProtocolInfo)
    '
    lngRetValue = getsockopt(lngSocket, SOL_SOCKET, SO_PROTOCOL_INFO, _
                             udtProtocolInfo, lngBufferSize)
    '
    If lngRetValue = 0 Then
        '
        With udtProtocolInfo
            '
            mvarConnectionless = .dwServiceFlags1 And XP1_CONNECTIONLESS
            mvarGuaranteedDelivery = .dwServiceFlags1 And XP1_GUARANTEED_DELIVERY
            mvarGuaranteedOrder = .dwServiceFlags1 And XP1_GUARANTEED_ORDER
            mvarMessageOriented = .dwServiceFlags1 And XP1_MESSAGE_ORIENTED
            mvarPseudoStream = .dwServiceFlags1 And XP1_PSEUDO_STREAM
            mvarGracefulClose = .dwServiceFlags1 And XP1_GRACEFUL_CLOSE
            mvarExpeditedData = .dwServiceFlags1 And XP1_EXPEDITED_DATA
            mvarConnectData = .dwServiceFlags1 And XP1_CONNECT_DATA
            mvarDisconnectData = .dwServiceFlags1 And XP1_DISCONNECT_DATA
            mvarSupportBroadcast = .dwServiceFlags1 And XP1_SUPPORT_BROADCAST
            mvarSupportMultipoint = .dwServiceFlags1 And XP1_SUPPORT_MULTIPOINT
            mvarMultipointControlPlane = .dwServiceFlags1 And XP1_MULTIPOINT_CONTROL_PLANE
            mvarMultipointDataPlane = .dwServiceFlags1 And XP1_MULTIPOINT_DATA_PLANE
            mvarQoSSupport = .dwServiceFlags1 And XP1_QOS_SUPPORTED
            mvarUniSend = .dwServiceFlags1 And XP1_UNI_SEND
            mvarUniRecv = .dwServiceFlags1 And XP1_UNI_RECV
            mvarIFSHandles = .dwServiceFlags1 And XP1_IFS_HANDLES
            mvarPartialMessage = .dwServiceFlags1 And XP1_PARTIAL_MESSAGE
            mvarMultipleProtoEntries = .dwProviderFlags And PFL_MULTIPLE_PROTO_ENTRIES
            mvarRecommendedProtoEntry = .dwProviderFlags And PFL_RECOMMENDED_PROTO_ENTRY
            mvarMatchesProtocolZero = .dwProviderFlags And PFL_MATCHES_PROTOCOL_ZERO
            mvarProviderId = GuidToString(.ProviderId)
            mvarCatalogEntryId = .dwCatalogEntryId
            mvarVersion = .iVersion
            mvarAddressFamily = .iAddressFamily
            mvarMaxSockAddr = .iMaxSockAddr
            mvarMinSockAddr = .iMinSockAddr
            mvarSocketType = .iSocketType
            mvarProtocol = .iProtocol
            mvarProtocolMaxOffset = .iProtocolMaxOffset
            mvarNetworkByteOrder = .iNetworkByteOrder
            mvarSecurityScheme = .iSecurityScheme
            mvarMessageSize = .dwMessageSize
            mvarProtocolName = .szProtocol
            '
        End With
        '
        GetBySocketHandle = True
        '
    End If
    '
End Function

Public Property Let ProtocolName(ByVal vData As String)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.ProtocolName = 5
    mvarProtocolName = vData
End Property


Public Property Get ProtocolName() As String
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.ProtocolName
    ProtocolName = mvarProtocolName
End Property



Public Property Let MessageSize(ByVal vData As Long)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.MessageSize = 5
    mvarMessageSize = vData
End Property


Public Property Get MessageSize() As Long
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.MessageSize
    MessageSize = mvarMessageSize
End Property



Public Property Let SecurityScheme(ByVal vData As Long)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.SecurityScheme = 5
    mvarSecurityScheme = vData
End Property


Public Property Get SecurityScheme() As Long
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.SecurityScheme
    SecurityScheme = mvarSecurityScheme
End Property



Public Property Let NetworkByteOrder(ByVal vData As Long)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.NetworkByteOrder = 5
    mvarNetworkByteOrder = vData
End Property


Public Property Get NetworkByteOrder() As Long
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.NetworkByteOrder
    NetworkByteOrder = mvarNetworkByteOrder
End Property



Public Property Let ProtocolMaxOffset(ByVal vData As Long)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.ProtocolMaxOffset = 5
    mvarProtocolMaxOffset = vData
End Property


Public Property Get ProtocolMaxOffset() As Long
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.ProtocolMaxOffset
    ProtocolMaxOffset = mvarProtocolMaxOffset
End Property



Public Property Let Protocol(ByVal vData As Long)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.Protocol = 5
    mvarProtocol = vData
End Property


Public Property Get Protocol() As Long
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.Protocol
    Protocol = mvarProtocol
End Property



Public Property Let SocketType(ByVal vData As Long)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.SocketType = 5
    mvarSocketType = vData
End Property


Public Property Get SocketType() As Long
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.SocketType
    SocketType = mvarSocketType
End Property



Public Property Let MinSockAddr(ByVal vData As Long)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.MinSockAddr = 5
    mvarMinSockAddr = vData
End Property


Public Property Get MinSockAddr() As Long
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.MinSockAddr
    MinSockAddr = mvarMinSockAddr
End Property



Public Property Let MaxSockAddr(ByVal vData As Long)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.MaxSockAddr = 5
    mvarMaxSockAddr = vData
End Property


Public Property Get MaxSockAddr() As Long
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.MaxSockAddr
    MaxSockAddr = mvarMaxSockAddr
End Property



Public Property Let AddressFamily(ByVal vData As Long)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.AddressFamily = 5
    mvarAddressFamily = vData
End Property


Public Property Get AddressFamily() As Long
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.AddressFamily
    AddressFamily = mvarAddressFamily
End Property



Public Property Let Version(ByVal vData As Long)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.Version = 5
    mvarVersion = vData
End Property


Public Property Get Version() As Long
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.Version
    Version = mvarVersion
End Property



Public Property Let CatalogEntryId(ByVal vData As Long)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.CatalogEntryId = 5
    mvarCatalogEntryId = vData
End Property


Public Property Get CatalogEntryId() As Long
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.CatalogEntryId
    CatalogEntryId = mvarCatalogEntryId
End Property



Public Property Let ProviderId(ByVal vData As String)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.ProviderId = 5
    mvarProviderId = vData
End Property


Public Property Get ProviderId() As String
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.ProviderId
    ProviderId = mvarProviderId
End Property



Public Property Let MatchesProtocolZero(ByVal vData As Boolean)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.MatchesProtocolZero = 5
    mvarMatchesProtocolZero = vData
End Property


Public Property Get MatchesProtocolZero() As Boolean
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.MatchesProtocolZero
    MatchesProtocolZero = mvarMatchesProtocolZero
End Property



Public Property Let RecommendedProtoEntry(ByVal vData As Boolean)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.RecommendedProtoEntry = 5
    mvarRecommendedProtoEntry = vData
End Property


Public Property Get RecommendedProtoEntry() As Boolean
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.RecommendedProtoEntry
    RecommendedProtoEntry = mvarRecommendedProtoEntry
End Property



Public Property Let MultipleProtoEntries(ByVal vData As Boolean)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.MultipleProtoEntries = 5
    mvarMultipleProtoEntries = vData
End Property


Public Property Get MultipleProtoEntries() As Boolean
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.MultipleProtoEntries
    MultipleProtoEntries = mvarMultipleProtoEntries
End Property



Public Property Let PartialMessage(ByVal vData As Boolean)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.PartialMessage = 5
    mvarPartialMessage = vData
End Property


Public Property Get PartialMessage() As Boolean
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.PartialMessage
    PartialMessage = mvarPartialMessage
End Property



Public Property Let IFSHandles(ByVal vData As Boolean)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.IFSHandles = 5
    mvarIFSHandles = vData
End Property


Public Property Get IFSHandles() As Boolean
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.IFSHandles
    IFSHandles = mvarIFSHandles
End Property



Public Property Let UniRecv(ByVal vData As Boolean)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.UniRecv = 5
    mvarUniRecv = vData
End Property


Public Property Get UniRecv() As Boolean
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.UniRecv
    UniRecv = mvarUniRecv
End Property



Public Property Let UniSend(ByVal vData As Boolean)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.UniSend = 5
    mvarUniSend = vData
End Property


Public Property Get UniSend() As Boolean
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.UniSend
    UniSend = mvarUniSend
End Property



Public Property Let QoSSupport(ByVal vData As Boolean)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.QoSSupport = 5
    mvarQoSSupport = vData
End Property


Public Property Get QoSSupport() As Boolean
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.QoSSupport
    QoSSupport = mvarQoSSupport
End Property



Public Property Let MultipointDataPlane(ByVal vData As Boolean)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.MultipointDataPlane = 5
    mvarMultipointDataPlane = vData
End Property


Public Property Get MultipointDataPlane() As Boolean
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.MultipointDataPlane
    MultipointDataPlane = mvarMultipointDataPlane
End Property



Public Property Let MultipointControlPlane(ByVal vData As Boolean)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.MultipointControlPlane = 5
    mvarMultipointControlPlane = vData
End Property


Public Property Get MultipointControlPlane() As Boolean
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.MultipointControlPlane
    MultipointControlPlane = mvarMultipointControlPlane
End Property



Public Property Let SupportMultipoint(ByVal vData As Boolean)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.SupportMultipoint = 5
    mvarSupportMultipoint = vData
End Property


Public Property Get SupportMultipoint() As Boolean
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.SupportMultipoint
    SupportMultipoint = mvarSupportMultipoint
End Property



Public Property Let SupportBroadcast(ByVal vData As Boolean)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.SupportBroadcast = 5
    mvarSupportBroadcast = vData
End Property


Public Property Get SupportBroadcast() As Boolean
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.SupportBroadcast
    SupportBroadcast = mvarSupportBroadcast
End Property



Public Property Let DisconnectData(ByVal vData As Boolean)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.DisconnectData = 5
    mvarDisconnectData = vData
End Property


Public Property Get DisconnectData() As Boolean
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.DisconnectData
    DisconnectData = mvarDisconnectData
End Property



Public Property Let ConnectData(ByVal vData As Boolean)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.ConnectData = 5
    mvarConnectData = vData
End Property


Public Property Get ConnectData() As Boolean
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.ConnectData
    ConnectData = mvarConnectData
End Property



Public Property Let ExpeditedData(ByVal vData As Boolean)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.ExpeditedData = 5
    mvarExpeditedData = vData
End Property


Public Property Get ExpeditedData() As Boolean
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.ExpeditedData
    ExpeditedData = mvarExpeditedData
End Property



Public Property Let GracefulClose(ByVal vData As Boolean)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.GracefulClose = 5
    mvarGracefulClose = vData
End Property


Public Property Get GracefulClose() As Boolean
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.GracefulClose
    GracefulClose = mvarGracefulClose
End Property



Public Property Let PseudoStream(ByVal vData As Boolean)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.PseudoStream = 5
    mvarPseudoStream = vData
End Property


Public Property Get PseudoStream() As Boolean
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.PseudoStream
    PseudoStream = mvarPseudoStream
End Property



Public Property Let MessageOriented(ByVal vData As Boolean)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.MessageOriented = 5
    mvarMessageOriented = vData
End Property


Public Property Get MessageOriented() As Boolean
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.MessageOriented
    MessageOriented = mvarMessageOriented
End Property



Public Property Let GuaranteedOrder(ByVal vData As Boolean)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.GuaranteedOrder = 5
    mvarGuaranteedOrder = vData
End Property


Public Property Get GuaranteedOrder() As Boolean
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.GuaranteedOrder
    GuaranteedOrder = mvarGuaranteedOrder
End Property



Public Property Let GuaranteedDelivery(ByVal vData As Boolean)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.GuaranteedDelivery = 5
    mvarGuaranteedDelivery = vData
End Property


Public Property Get GuaranteedDelivery() As Boolean
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.GuaranteedDelivery
    GuaranteedDelivery = mvarGuaranteedDelivery
End Property



Public Property Let Connectionless(ByVal vData As Boolean)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.Connectionless = 5
    mvarConnectionless = vData
End Property


Public Property Get Connectionless() As Boolean
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.Connectionless
    Connectionless = mvarConnectionless
End Property





