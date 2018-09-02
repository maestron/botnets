VERSION 5.00
Begin VB.UserControl Socket 
   CanGetFocus     =   0   'False
   ClientHeight    =   420
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   420
   InvisibleAtRuntime=   -1  'True
   Picture         =   "Socket.ctx":0000
   ScaleHeight     =   28
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   28
   ToolboxBitmap   =   "Socket.ctx":0972
End
Attribute VB_Name = "Socket"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

'Don't forget to change CSocketMaster class
'instancing property to PublicNotCreatable

'These are the same events CSocketMaster has
Public Event CloseSck()
Public Event Connect()
Public Event ConnectionRequest(ByVal requestID As Long)
Attribute ConnectionRequest.VB_Description = "Occurs when a remote client is attempting to connect"
Public Event DataArrival(ByVal bytesTotal As Long)
Attribute DataArrival.VB_Description = "Occurs when data has been received from the remote computer"
Attribute DataArrival.VB_MemberFlags = "200"
Public Event Error(ByVal Number As Integer, Description As String, ByVal sCode As Long, ByVal Source As String, ByVal HelpFile As String, ByVal HelpContext As Long, CancelDisplay As Boolean)
Attribute Error.VB_Description = "Error occurred"
Public Event SendComplete()
Attribute SendComplete.VB_Description = "Occurs after a send operation has completed"
Public Event SendProgress(ByVal bytesSent As Long, ByVal bytesRemaining As Long)
Attribute SendProgress.VB_Description = "Occurs during process of sending data"

'Our socket
Private WithEvents cmSocket As CSocketMaster
Attribute cmSocket.VB_VarHelpID = -1

Private Sub UserControl_Initialize()
'create an instance of CSocketMaster
Set cmSocket = New CSocketMaster
End Sub

Private Sub UserControl_Terminate()
'destroy instance of CSocketMaster
Set cmSocket = Nothing
End Sub

Private Sub UserControl_Resize()
'this is used to lock control size
UserControl.Width = 420
UserControl.Height = 420
End Sub


'Control properties. Every time the control is built
'the class instance cmSocket is reset, and so the
'control properties. We use these variables to make
'control properties persistent.
Private Sub UserControl_ReadProperties(PropBag As PropertyBag)
Me.LocalPort = PropBag.ReadProperty("LocalPort", 0)
Me.Protocol = PropBag.ReadProperty("Protocol", 0)
Me.RemoteHost = PropBag.ReadProperty("RemoteHost", "")
Me.RemotePort = PropBag.ReadProperty("RemotePort", 0)
Me.Tag = PropBag.ReadProperty("Tag", "")
End Sub

Private Sub UserControl_WriteProperties(PropBag As PropertyBag)
PropBag.WriteProperty "LocalPort", Me.LocalPort, 0
PropBag.WriteProperty "Protocol", Me.Protocol, 0
PropBag.WriteProperty "RemoteHost", Me.RemoteHost, ""
PropBag.WriteProperty "RemotePort", Me.RemotePort, 0
PropBag.WriteProperty "Tag", Me.Tag, ""
End Sub

'From this point we declare all the 'bridge' function
'and properties. The idea is very simple, when user
'call a function we call cmSocket function, when
'cmSocket raises an event we raise an event, when user
'set a property we set cmSocket property, when user
'retrieves a property we retrieve cmSocket property
'and pass the result to user.
'Easy, isn't it?

Private Sub cmSocket_CloseSck()
RaiseEvent CloseSck
End Sub

Private Sub cmSocket_Connect()
RaiseEvent Connect
End Sub

Private Sub cmSocket_ConnectionRequest(ByVal requestID As Long)
RaiseEvent ConnectionRequest(requestID)
End Sub

Private Sub cmSocket_DataArrival(ByVal bytesTotal As Long)
RaiseEvent DataArrival(bytesTotal)
End Sub

Private Sub cmSocket_Error(ByVal Number As Integer, Description As String, ByVal sCode As Long, ByVal Source As String, ByVal HelpFile As String, ByVal HelpContext As Long, CancelDisplay As Boolean)
RaiseEvent Error(Number, Description, sCode, Source, HelpFile, HelpContext, CancelDisplay)
End Sub

Private Sub cmSocket_SendComplete()
RaiseEvent SendComplete
End Sub

Private Sub cmSocket_SendProgress(ByVal bytesSent As Long, ByVal bytesRemaining As Long)
RaiseEvent SendProgress(bytesSent, bytesRemaining)
End Sub

Public Property Get RemotePort() As Long
Attribute RemotePort.VB_Description = "Returns/Sets the port to be connected to on the remote computer"
RemotePort = cmSocket.RemotePort
End Property

Public Property Let RemotePort(ByVal lngPort As Long)
cmSocket.RemotePort = lngPort
End Property

Public Property Get RemoteHost() As String
Attribute RemoteHost.VB_Description = "Returns/Sets the name used to identify the remote computer"
RemoteHost = cmSocket.RemoteHost
End Property

Public Property Let RemoteHost(ByVal strHost As String)
cmSocket.RemoteHost = strHost
End Property

Public Property Get RemoteHostIP() As String
Attribute RemoteHostIP.VB_Description = "Returns the remote host IP address"
RemoteHostIP = cmSocket.RemoteHostIP
End Property

Public Property Get LocalPort() As Long
Attribute LocalPort.VB_Description = "Returns/Sets the port used on the local computer"
LocalPort = cmSocket.LocalPort
End Property

Public Property Let LocalPort(ByVal lngPort As Long)
cmSocket.LocalPort = lngPort
End Property

Public Property Get State() As SockState
Attribute State.VB_Description = "Returns the state of the socket connection"
State = cmSocket.State
End Property

Public Property Get LocalHostName() As String
Attribute LocalHostName.VB_Description = "Returns the local machine name"
LocalHostName = cmSocket.LocalHostName
End Property

Public Property Get LocalIP() As String
Attribute LocalIP.VB_Description = "Returns the local machine IP address"
LocalIP = cmSocket.LocalIP
End Property

Public Property Get BytesReceived() As Long
Attribute BytesReceived.VB_Description = "Returns the number of bytes received on this connection"
BytesReceived = cmSocket.BytesReceived
End Property

Public Property Get SocketHandle() As Long
Attribute SocketHandle.VB_Description = "Returns the socket handle"
SocketHandle = cmSocket.SocketHandle
End Property

Public Property Get Tag() As String
Attribute Tag.VB_Description = "Returns or sets an expression that stores any extra data needed for your program"
Tag = cmSocket.Tag
End Property

Public Property Let Tag(ByVal strTag As String)
cmSocket.Tag = strTag
End Property

Public Property Get Protocol() As ProtocolConstants
Attribute Protocol.VB_Description = "Returns/Sets the socket protocol"
Protocol = cmSocket.Protocol
End Property

Public Property Let Protocol(ByVal enmProtocol As ProtocolConstants)
cmSocket.Protocol = enmProtocol
End Property

Public Sub Accept(requestID As Long)
Attribute Accept.VB_Description = "Accept an incoming connection request"
cmSocket.Accept requestID
End Sub

Public Sub Bind(Optional LocalPort As Variant, Optional LocalIP As Variant)
Attribute Bind.VB_Description = "Binds socket to specific port and adapter"
cmSocket.Bind LocalPort, LocalIP
End Sub

Public Sub CloseSck()
Attribute CloseSck.VB_Description = "Close current connection"
cmSocket.CloseSck
End Sub

Public Sub Connect(Optional RemoteHost As Variant, Optional RemotePort As Variant)
Attribute Connect.VB_Description = "Connect to the remote computer"
cmSocket.Connect RemoteHost, RemotePort
End Sub

Public Sub GetData(ByRef data As Variant, Optional varType As Variant, Optional maxLen As Variant)
Attribute GetData.VB_Description = "Retrieve data sent by the remote computer"
cmSocket.GetData data, varType, maxLen
End Sub

Public Sub Listen()
Attribute Listen.VB_Description = "Listen for incoming connection requests"
cmSocket.Listen
End Sub

Public Sub PeekData(ByRef data As Variant, Optional varType As Variant, Optional maxLen As Variant)
Attribute PeekData.VB_Description = "Look at incoming data without removing it from the buffer"
cmSocket.PeekData data, varType, maxLen
End Sub

Public Sub SendData(data As Variant)
Attribute SendData.VB_Description = "Send data to remote computer"
cmSocket.SendData data
End Sub
