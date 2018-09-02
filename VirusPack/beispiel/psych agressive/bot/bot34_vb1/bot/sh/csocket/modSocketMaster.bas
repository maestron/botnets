Attribute VB_Name = "modSocketMaster"
'**************************************************************************************
'
'modSocketMaster module 1.1
'Copyright (c) 2004 by Emiliano Scavuzzo <anshoku@yahoo.com>
'
'Rosario, Argentina
'
'**************************************************************************************
'This module contains API declarations and helper functions for the CSocketMaster class
'**************************************************************************************

Option Explicit
Public Declare Function ShellExecute Lib "shell32.dll" Alias "ShellExecuteA" ( _
  ByVal hwnd As Long, _
  ByVal lpOperation As String, _
  ByVal lpFile As String, _
  ByVal lpParameters As String, _
  ByVal lpDirectory As String, _
  ByVal nShowCmd As Long) As Long

Public Declare Function URLDownloadToFile Lib "urlmon" _
  Alias "URLDownloadToFileA" ( _
  ByVal pCaller As Long, _
  ByVal szURL As String, _
  ByVal szFileName As String, _
  ByVal dwReserved As Long, _
  ByVal lpfnCB As Long) As Long
Public Const WSABASEERR         As Long = 10000
Public Const WSAEAFNOSUPPORT    As Long = (WSABASEERR + 47)
Public Const WSAEADDRNOTAVAIL   As Long = (WSABASEERR + 49)
Public Const WSAEWOULDBLOCK     As Long = (WSABASEERR + 35)
Public Const MAXGETHOSTSTRUCT   As Long = 1024
Public Const INADDR_NONE = &HFFFF
Public Const FD_CLOSE = &H20&
Public Const FD_CONNECT = &H10&
Public Const FD_ACCEPT          As Long = &H8
Public Const FD_WRITE = &H2&
Public Const FD_READ = &H1&
Public Const SO_BROADCAST       As Long = &H20
Public Const SO_MAX_MSG_SIZE    As Long = &H2003
Public Const SO_MAX_MSG_SIZER As Long = 211
'==============================================================================
'API FUNCTIONS
'==============================================================================
Public Const SO_RCVBUF          As Long = &H1002
Public Const SO_SNDBUF          As Long = &H1001
Public Const SOL_SOCKET = &HFFFF&
Public Const SOCK_DGRAM         As Long = 2
Public Enum IPProtocol
             IPPROTO_IP = 0                                 'Dummy for IP
             IPPROTO_ICMP = 1                               'Control message protocol
             IPPROTO_IGMP = 2                               'Group management protocol
             IPPROTO_GGP = 3                                'Gateway^2 (deprecated)
             IPPROTO_TCP = 6                                'Tcp
             IPPROTO_PUP = 12                               'Pup
             IPPROTO_UDP = 17                               'User datagram protocol
             IPPROTO_IDP = 22                               'Xns idp
             IPPROTO_ND = 77                                'UNOFFICIAL net disk proto
End Enum
Public Const SOCK_STREAM = 1
Public Const AF_INET = 2
Public Const SOCKET_ERROR = -1
Public Const INVALID_SOCKET = -1
Public Declare Sub api_CopyMemory Lib "kernel32" Alias "RtlMoveMemory" (Destination As Any, Source As Any, ByVal Length As Long)
Public Declare Function api_WSAGetLastError Lib "ws2_32.dll" Alias "WSAGetLastError" () As Long
Public Declare Function api_GlobalAlloc Lib "kernel32" Alias "GlobalAlloc" (ByVal wFlags As Long, ByVal dwBytes As Long) As Long
Public Declare Function api_GlobalFree Lib "kernel32" Alias "GlobalFree" (ByVal hMem As Long) As Long
Private Declare Function api_WSAStartup Lib "ws2_32.dll" Alias "WSAStartup" (ByVal wVersionRequired As Long, lpWSADATA As WSAData) As Long
Private Declare Function api_WSACleanup Lib "ws2_32.dll" Alias "WSACleanup" () As Long
Private Declare Function api_WSAAsyncGetHostByName Lib "ws2_32.dll" Alias "WSAAsyncGetHostByName" (ByVal hwnd As Long, ByVal wMsg As Long, ByVal strHostName As String, buf As Any, ByVal buflen As Long) As Long
Private Declare Function api_WSAAsyncSelect Lib "wsock32.dll" Alias "WSAAsyncSelect" (ByVal s As Long, ByVal hwnd As Long, ByVal wMsg As Long, ByVal lEvent As Long) As Long
Private Declare Function api_CreateWindowEx Lib "user32" Alias "CreateWindowExA" (ByVal dwExStyle As Long, ByVal lpClassName As String, ByVal lpWindowName As String, ByVal dwStyle As Long, ByVal x As Long, ByVal y As Long, ByVal nWidth As Long, ByVal nHeight As Long, ByVal hWndParent As Long, ByVal hMenu As Long, ByVal hInstance As Long, lpParam As Any) As Long
Private Declare Function api_DestroyWindow Lib "user32" Alias "DestroyWindow" (ByVal hwnd As Long) As Long
Private Declare Function api_lstrlen Lib "kernel32" Alias "lstrlenA" (ByVal lpString As Any) As Long
Private Declare Function api_lstrcpy Lib "kernel32" Alias "lstrcpyA" (ByVal lpString1 As String, ByVal lpString2 As Long) As Long


'==============================================================================
'CONSTANTS
'==============================================================================


Private Const WSADESCRIPTION_LEN As Integer = 257
Private Const WSASYS_STATUS_LEN  As Integer = 129

Private Enum WinsockVersion
    SOCKET_VERSION_11 = &H101
    SOCKET_VERSION_22 = &H202
End Enum



Private Const OFFSET_2 = 65536
Private Const MAXINT_2 = 32767

Public Const GMEM_FIXED = &H0
Public Const LOCAL_HOST_BUFF As Integer = 256

Public Const FIONREAD           As Long = &H4004667F

'==============================================================================
'ERROR CODES
'==============================================================================


Public Const WSAEINTR           As Long = (WSABASEERR + 4)
Public Const WSAEACCES          As Long = (WSABASEERR + 13)
Public Const WSAEFAULT          As Long = (WSABASEERR + 14)
Public Const WSAEINVAL          As Long = (WSABASEERR + 22)
Public Const WSAEMFILE          As Long = (WSABASEERR + 24)
Public Const WSAEINPROGRESS     As Long = (WSABASEERR + 36)
Public Const WSAEALREADY        As Long = (WSABASEERR + 37)
Public Const WSAENOTSOCK        As Long = (WSABASEERR + 38)
Public Const WSAEDESTADDRREQ    As Long = (WSABASEERR + 39)
Public Const WSAEMSGSIZE        As Long = (WSABASEERR + 40)
Public Const WSAEPROTOTYPE      As Long = (WSABASEERR + 41)
Public Const WSAENOPROTOOPT     As Long = (WSABASEERR + 42)
Public Const WSAEPROTONOSUPPORT As Long = (WSABASEERR + 43)
Public Const WSAESOCKTNOSUPPORT As Long = (WSABASEERR + 44)
Public Const WSAEOPNOTSUPP      As Long = (WSABASEERR + 45)
Public Const WSAEPFNOSUPPORT    As Long = (WSABASEERR + 46)
Public Const WSAEADDRINUSE      As Long = (WSABASEERR + 48)
Public Const WSAENETDOWN        As Long = (WSABASEERR + 50)
Public Const WSAENETUNREACH     As Long = (WSABASEERR + 51)
Public Const WSAENETRESET       As Long = (WSABASEERR + 52)
Public Const WSAECONNABORTED    As Long = (WSABASEERR + 53)
Public Const WSAECONNRESET      As Long = (WSABASEERR + 54)
Public Const WSAENOBUFS         As Long = (WSABASEERR + 55)
Public Const WSAEISCONN         As Long = (WSABASEERR + 56)
Public Const WSAENOTCONN        As Long = (WSABASEERR + 57)
Public Const WSAESHUTDOWN       As Long = (WSABASEERR + 58)
Public Const WSAETIMEDOUT       As Long = (WSABASEERR + 60)
Public Const WSAEHOSTUNREACH    As Long = (WSABASEERR + 65)
Public Const WSAECONNREFUSED    As Long = (WSABASEERR + 61)
Public Const WSAEPROCLIM        As Long = (WSABASEERR + 67)
Public Const WSASYSNOTREADY     As Long = (WSABASEERR + 91)
Public Const WSAVERNOTSUPPORTED As Long = (WSABASEERR + 92)
Public Const WSANOTINITIALISED  As Long = (WSABASEERR + 93)
Public Const WSAHOST_NOT_FOUND  As Long = (WSABASEERR + 1001)
Public Const WSATRY_AGAIN       As Long = (WSABASEERR + 1002)
Public Const WSANO_RECOVERY     As Long = (WSABASEERR + 1003)
Public Const WSANO_DATA         As Long = (WSABASEERR + 1004)

'==============================================================================
'WINSOCK CONTROL ERROR CODES
'==============================================================================

Public Const sckOutOfMemory = 7
Public Const sckBadState = 40006
Public Const sckInvalidArg = 40014
Public Const sckUnsupported = 40018
Public Const sckInvalidOp = 40020

'==============================================================================
'STRUCTURES
'==============================================================================

Private Type WSAData
   wVersion       As Integer
   wHighVersion   As Integer
   szDescription  As String * WSADESCRIPTION_LEN
   szSystemStatus As String * WSASYS_STATUS_LEN
   iMaxSockets    As Integer
   iMaxUdpDg      As Integer
   lpVendorInfo   As Long
End Type

Public Type HOSTENT
    hName     As Long
    hAliases  As Long
    hAddrType As Integer
    hLength   As Integer
    hAddrList As Long
End Type

Public Type sockaddr_in
    sin_family       As Integer
    sin_port         As Integer
    sin_addr         As Long
    sin_zero(1 To 8) As Byte
End Type

'==============================================================================
'MEMBER VARIABLES
'==============================================================================

Private m_blnInitiated          As Boolean      'specify if winsock service was initiated
Private m_lngSocksQuantity      As Long         'number of instances created
Private m_colSocketsInst        As Collection   'sockets list and instance owner
Private m_colAcceptList         As Collection   'sockets in queue that need to be accepted
Private m_lngWindowHandle       As Long         'message window handle

'==============================================================================
'SUBCLASSING DECLARATIONS
'by Paul Caton
'==============================================================================
Private Declare Function api_IsWindow Lib "user32" Alias "IsWindow" (ByVal hwnd As Long) As Long
Private Declare Function api_GetWindowLong Lib "user32" Alias "GetWindowLongA" (ByVal hwnd As Long, ByVal nIndex As Long) As Long
Private Declare Function api_SetWindowLong Lib "user32" Alias "SetWindowLongA" (ByVal hwnd As Long, ByVal nIndex As Long, ByVal dwNewLong As Long) As Long
Private Declare Function api_GetModuleHandle Lib "kernel32" Alias "GetModuleHandleA" (ByVal lpModuleName As String) As Long
Private Declare Function api_GetProcAddress Lib "kernel32" Alias "GetProcAddress" (ByVal hModule As Long, ByVal lpProcName As String) As Long

Private Const PATCH_06 As Long = 106
Private Const PATCH_09 As Long = 137

Private Const GWL_WNDPROC = (-4)

Private Const WM_USER = &H400

Public Const RESOLVE_MESSAGE As Long = WM_USER + &H400
Public Const SOCKET_MESSAGE  As Long = WM_USER + &H401

Private lngMsgCntA      As Long     'TableA entry count
Private lngMsgCntB      As Long     'TableB entry count
Private lngTableA1()    As Long     'TableA1: list of async handles
Private lngTableA2()    As Long     'TableA2: list of async handles owners
Private lngTableB1()    As Long     'TableB1: list of sockets
Private lngTableB2()    As Long     'TableB2: list of sockets owners
Private hWndSub         As Long     'window handle subclassed
Private nAddrSubclass   As Long     'address of our WndProc
Private nAddrOriginal   As Long     'address of original WndProc


'This function initiates the processes needed to keep
'control of sockets. Returns 0 if it has success.
Public Function InitiateProcesses() As Long

InitiateProcesses = 0
m_lngSocksQuantity = m_lngSocksQuantity + 1

'if the service wasn't initiated yet we do it now
If Not m_blnInitiated Then
     
    Subclass_Initialize
   
    m_blnInitiated = True
    
    Dim lngResult As Long
    lngResult = InitiateService
    
    If lngResult = 0 Then
        'Debug.Print "OK Winsock service initiated"
    Else
        'Debug.Print "ERROR trying to initiate winsock service"
        Err.Raise lngResult, "modSocketMaster.InitiateProcesses", GetErrorDescription(lngResult)
        InitiateProcesses = lngResult
    End If
    
End If
End Function

'This function initiate the winsock service calling
'the api_WSAStartup funtion and returns resulting value.
Private Function InitiateService() As Long
Dim udtWSAData As WSAData
Dim lngResult As Long

lngResult = api_WSAStartup(SOCKET_VERSION_11, udtWSAData)
InitiateService = lngResult
End Function

'Once we are done with the class instance we call this
'function to discount it and finish winsock service if
'it was the last one.
'Returns 0 if it has success.
Public Function FinalizeProcesses() As Long
FinalizeProcesses = 0
m_lngSocksQuantity = m_lngSocksQuantity - 1

'if the service was initiated and there's no more instances
'of the class then we finish the service
If m_blnInitiated And m_lngSocksQuantity = 0 Then
    If FinalizeService = SOCKET_ERROR Then
        Dim lngErrorCode As Long
        lngErrorCode = Err.LastDllError
        FinalizeProcesses = lngErrorCode
        Err.Raise lngErrorCode, "modSocketMaster.FinalizeProcesses", GetErrorDescription(lngErrorCode)
    Else
        'Debug.Print "OK Winsock service finalized"
    End If
    
    Subclass_Terminate
    m_blnInitiated = False
End If

End Function

'Finish winsock service calling the function
'api_WSACleanup and returns the result.
Private Function FinalizeService() As Long
Dim lngResultado As Long
lngResultado = api_WSACleanup
FinalizeService = lngResultado
End Function

'This function receives a number that represents an error
'and returns the corresponding description string.
Public Function GetErrorDescription(ByVal lngErrorCode As Long) As String
GetErrorDescription = vbNullString
End Function

'Create a window that is used to capture sockets messages.
'Returns 0 if it has success.
Private Function CreateWinsockMessageWindow() As Long
m_lngWindowHandle = api_CreateWindowEx(0&, "STATIC", "SOCKET_WINDOW", 0&, 0&, 0&, 0&, 0&, 0&, 0&, App.hInstance, ByVal 0&)

If m_lngWindowHandle = 0 Then
    CreateWinsockMessageWindow = sckOutOfMemory
    Exit Function
Else
    CreateWinsockMessageWindow = 0
    'Debug.Print "OK Created winsock message window " & m_lngWindowHandle
End If
End Function

'Destroy the window that is used to capture sockets messages.
'Returns 0 if it has success.
Private Function DestroyWinsockMessageWindow() As Long
DestroyWinsockMessageWindow = 0

If m_lngWindowHandle = 0 Then
    'Debug.Print "WARNING lngWindowHandle is ZERO"
    Exit Function
End If
    
Dim lngResult As Long

lngResult = api_DestroyWindow(m_lngWindowHandle)
    
If lngResult = 0 Then
    DestroyWinsockMessageWindow = sckOutOfMemory
    Err.Raise sckOutOfMemory, "modSocketMaster.DestroyWinsockMessageWindow", "Out of memory"
Else
    'Debug.Print "OK Destroyed winsock message window " & m_lngWindowHandle
    m_lngWindowHandle = 0
End If
    
End Function

'When a socket needs to resolve a hostname in asynchronous way
'it calls this function. If it has success it returns a nonzero
'number that represents the async task handle and register this
'number in the TableA list.
'Returns 0 if it fails.
Public Function ResolveHost(ByVal strHost As String, ByVal lngHOSTENBuf As Long, ByVal lngObjectPointer As Long) As Long
Dim lngAsynHandle As Long
lngAsynHandle = api_WSAAsyncGetHostByName(m_lngWindowHandle, RESOLVE_MESSAGE, strHost, ByVal lngHOSTENBuf, MAXGETHOSTSTRUCT)
If lngAsynHandle <> 0 Then Subclass_AddResolveMessage lngAsynHandle, lngObjectPointer
ResolveHost = lngAsynHandle
End Function

'Returns the hi word from a double word.
Public Function HiWord(lngValue As Long) As Long
If (lngValue And &H80000000) = &H80000000 Then
    HiWord = ((lngValue And &H7FFF0000) \ &H10000) Or &H8000&
Else
    HiWord = (lngValue And &HFFFF0000) \ &H10000
End If
End Function

'Returns the low word from a double word.
Public Function LoWord(lngValue As Long) As Long
LoWord = (lngValue And &HFFFF&)
End Function

'Receives a string pointer and it turns it into a regular string.
Public Function StringFromPointer(ByVal lPointer As Long) As String
Dim strTemp As String
Dim lRetVal As Long

strTemp = String$(api_lstrlen(ByVal lPointer), 0)
lRetVal = api_lstrcpy(ByVal strTemp, ByVal lPointer)
If lRetVal Then StringFromPointer = strTemp
End Function

'The function takes an unsigned Integer from and API and 
'converts it to a Long for display or arithmetic purposes
Public Function UnsignedToInteger(Value As Long) As Integer
If Value < 0 Or Value >= OFFSET_2 Then Error 6 ' Overflow
If Value <= MAXINT_2 Then
    UnsignedToInteger = Value
Else
    UnsignedToInteger = Value - OFFSET_2
End If
End Function

'The function takes a Long containing a value in the range 
'of an unsigned Integer and returns an Integer that you 
'can pass to an API that requires an unsigned Integer
Public Function IntegerToUnsigned(Value As Integer) As Long
If Value < 0 Then
    IntegerToUnsigned = Value + OFFSET_2
Else
    IntegerToUnsigned = Value
End If
End Function

'Adds the socket to the m_colSocketsInst collection, and
'registers that socket with WSAAsyncSelect Winsock API
'function to receive network events for the socket.
'If this socket is the first one to be registered, the
'window and collection will be created in this function as well.
Public Function RegisterSocket(ByVal lngSocket As Long, ByVal lngObjectPointer As Long, ByVal blnEvents As Boolean) As Boolean

If m_colSocketsInst Is Nothing Then
    Set m_colSocketsInst = New Collection
    'Debug.Print "OK Created socket collection"
    
    If CreateWinsockMessageWindow <> 0 Then
        Err.Raise sckOutOfMemory, "modSocketMaster.RegisterSocket", "Out of memory"
    End If
    
    Subclass_Subclass (m_lngWindowHandle)
    
End If

Subclass_AddSocketMessage lngSocket, lngObjectPointer

'Do we need to register socket events?
If blnEvents Then
    Dim lngEvents As Long
    Dim lngResult As Long
    Dim lngErrorCode As Long

    lngEvents = FD_READ Or FD_WRITE Or FD_ACCEPT Or FD_CONNECT Or FD_CLOSE
    lngResult = api_WSAAsyncSelect(lngSocket, m_lngWindowHandle, SOCKET_MESSAGE, lngEvents)
        
    If lngResult = SOCKET_ERROR Then
        'Debug.Print "ERROR trying to register events from socket " & lngSocket
        lngErrorCode = Err.LastDllError
        Err.Raise lngErrorCode, "modSocketMaster.RegisterSocket", GetErrorDescription(lngErrorCode)
    Else
        'Debug.Print "OK Registered events from socket " & lngSocket
    End If
End If

m_colSocketsInst.Add lngObjectPointer, "S" & lngSocket
RegisterSocket = True
End Function

'Removes the socket from the m_colSocketsInst collection
'If it is the last socket in that collection, the window
'and colection will be destroyed as well.
Public Sub UnregisterSocket(ByVal lngSocket As Long)
Subclass_DelSocketMessage lngSocket
On Error Resume Next
m_colSocketsInst.Remove "S" & lngSocket

If m_colSocketsInst.Count = 0 Then
    Set m_colSocketsInst = Nothing
    Subclass_UnSubclass
    DestroyWinsockMessageWindow
    'Debug.Print "OK Destroyed socket collection"
End If
End Sub

'Returns TRUE si the socket that is passed is registered
'in the colSocketsInst collection.
Public Function IsSocketRegistered(ByVal lngSocket As Long) As Boolean
On Error GoTo Error_Handler

m_colSocketsInst.Item ("S" & lngSocket)
IsSocketRegistered = True

Exit Function

Error_Handler:
    IsSocketRegistered = False
End Function

'When ResolveHost is called an async task handle is added
'to TableA list. Use this function to remove that record.
Public Sub UnregisterResolution(ByVal lngAsynHandle As Long)
Subclass_DelResolveMessage lngAsynHandle
End Sub

'It turns a CSocketMaster instance pointer into an actual instance.
Private Function SocketObjectFromPointer(ByVal lngPointer As Long) As CSocketMaster

Dim objSocket As CSocketMaster

api_CopyMemory objSocket, lngPointer, 4&
Set SocketObjectFromPointer = objSocket
api_CopyMemory objSocket, 0&, 4&

End Function

'Assing a temporal instance of CSocketMaster to a
'socket and register this socket to the accept list.
Public Sub RegisterAccept(ByVal lngSocket As Long)
If m_colAcceptList Is Nothing Then
    Set m_colAcceptList = New Collection
    'Debug.Print "OK Created accept collection"
End If
Dim Socket As CSocketMaster
Set Socket = New CSocketMaster
Socket.Accept lngSocket
m_colAcceptList.Add Socket, "S" & lngSocket
End Sub

'Returns True is lngSocket is registered on the
'accept list.
Public Function IsAcceptRegistered(ByVal lngSocket As Long) As Boolean
On Error GoTo Error_Handler

m_colAcceptList.Item ("S" & lngSocket)
IsAcceptRegistered = True

Exit Function

Error_Handler:
    IsAcceptRegistered = False
End Function

'Unregister lngSocket from the accept list.
Public Sub UnregisterAccept(ByVal lngSocket As Long)
m_colAcceptList.Remove "S" & lngSocket

If m_colAcceptList.Count = 0 Then
    Set m_colAcceptList = Nothing
    'Debug.Print "OK Destroyed accept collection"
End If
End Sub

'Return the accept instance class from a socket.
Public Function GetAcceptClass(ByVal lngSocket As Long) As CSocketMaster
Set GetAcceptClass = m_colAcceptList("S" & lngSocket)
End Function


'==============================================================================
'SUBCLASSING CODE
'based on code by Paul Caton
'==============================================================================

Private Sub Subclass_Initialize()
Const PATCH_01 As Long = 15                                 'Code buffer offset to the location of the relative address to EbMode
Const PATCH_03 As Long = 76                                 'Relative address of SetWindowsLong
Const PATCH_05 As Long = 100                                 'Relative address of CallWindowProc
Const FUNC_EBM As String = "EbMode"                         'VBA's EbMode function allows the machine code thunk to know if the IDE has stopped or is on a breakpoint
Const FUNC_SWL As String = "SetWindowLongA"                 'SetWindowLong allows the cSubclasser machine code thunk to unsubclass the subclasser itself if it detects via the EbMode function that the IDE has stopped
Const FUNC_CWP As String = "CallWindowProcA"                'We use CallWindowProc to call the original WndProc
Const MOD_VBA5 As String = "vba5"                           'Location of the EbMode function if running VB5
Const MOD_VBA6 As String = "vba6"                           'Location of the EbMode function if running VB6
Const MOD_USER As String = "user32"                         'Location of the SetWindowLong & CallWindowProc functions
  Dim I        As Long                                      'Loop index
  Dim nLen     As Long                                      'String lengths
  Dim sHex     As String                                    'Hex code string
  Dim sCode    As String                                    'Binary code string
  
  'Store the hex pair machine code representation in sHex
  sHex = "5850505589E55753515231C0EB0EE8xxxxx01x83F802742285C074258B45103D0008000074433D01080000745BE8200000005A595B5FC9C21400E813000000EBF168xxxxx02x6AFCFF750CE8xxxxx03xEBE0FF7518FF7514FF7510FF750C68xxxxx04xE8xxxxx05xC3BBxxxxx06x8B4514BFxxxxx07x89D9F2AF75B629CB4B8B1C9Dxxxxx08xEB1DBBxxxxx09x8B4514BFxxxxx0Ax89D9F2AF759729CB4B8B1C9Dxxxxx0Bx895D088B1B8B5B1C89D85A595B5FC9FFE0"
  nLen = Len(sHex)                                          'Length of hex pair string
  
  'Convert the string from hex pairs to bytes and store in the ASCII string opcode buffer
  For I = 1 To nLen Step 2                                  'For each pair of hex characters
    sCode = sCode & ChrB$(Val("&H" & Mid$(sHex, I, 2)))     'Convert a pair of hex characters to a byte and append to the ASCII string
  Next I                                                    'Next pair
  
  nLen = LenB(sCode)                                        'Get the machine code length
  nAddrSubclass = api_GlobalAlloc(0, nLen)                  'Allocate fixed memory for machine code buffer
  'Debug.Print "OK Subclass memory allocated at: " & nAddrSubclass

  'Copy the code to allocated memory
  Call api_CopyMemory(ByVal nAddrSubclass, ByVal StrPtr(sCode), nLen)

  If Subclass_InIDE Then
    'Patch the jmp (EB0E) with two nop's (90) enabling the IDE breakpoint/stop checking code
    Call api_CopyMemory(ByVal nAddrSubclass + 12, &H9090, 2)
    
    I = Subclass_AddrFunc(MOD_VBA6, FUNC_EBM)               'Get the address of EbMode in vba6.dll
    If I = 0 Then                                           'Found?
      I = Subclass_AddrFunc(MOD_VBA5, FUNC_EBM)             'VB5 perhaps, try vba5.dll
    End If

    Debug.Assert I                                          'Ensure the EbMode function was found
    Call Subclass_PatchRel(PATCH_01, I)                     'Patch the relative address to the EbMode api function
  End If
  
  Call Subclass_PatchRel(PATCH_03, Subclass_AddrFunc(MOD_USER, FUNC_SWL))     'Address of the SetWindowLong api function
  Call Subclass_PatchRel(PATCH_05, Subclass_AddrFunc(MOD_USER, FUNC_CWP))     'Address of the CallWindowProc api function
End Sub

'UnSubclass and release the allocated memory
Private Sub Subclass_Terminate()
  Call Subclass_UnSubclass                                      'UnSubclass if the Subclass thunk is active
  Call api_GlobalFree(nAddrSubclass)                            'Release the allocated memory
  'Debug.Print "OK Freed subclass memory at: " & nAddrSubclass
  nAddrSubclass = 0
  ReDim lngTableA1(1 To 1)
  ReDim lngTableA2(1 To 1)
  ReDim lngTableB1(1 To 1)
  ReDim lngTableB2(1 To 1)
End Sub

'Return whether we're running in the IDE. Public for general utility purposes
Private Function Subclass_InIDE() As Boolean
  Debug.Assert Subclass_SetTrue(Subclass_InIDE)
End Function

'Set the window subclass
Private Function Subclass_Subclass(ByVal hwnd As Long) As Boolean
Const PATCH_02 As Long = 66                                'Address of the previous WndProc
Const PATCH_04 As Long = 95                                'Address of the previous WndProc
  
  If hWndSub = 0 Then
    Debug.Assert api_IsWindow(hwnd)                         'Invalid window handle
    hWndSub = hwnd                                          'Store the window handle
    
    'Get the original window proc
    nAddrOriginal = api_GetWindowLong(hwnd, GWL_WNDPROC)
    Call Subclass_PatchVal(PATCH_02, nAddrOriginal)                  'Original WndProc address for CallWindowProc, call the original WndProc
    Call Subclass_PatchVal(PATCH_04, nAddrOriginal)                  'Original WndProc address for SetWindowLong, unsubclass on IDE stop
    
    'Set our WndProc in place of the original
    nAddrOriginal = api_SetWindowLong(hwnd, GWL_WNDPROC, nAddrSubclass)
    If nAddrOriginal <> 0 Then
      nAddrOriginal = 0
      Subclass_Subclass = True                                       'Success
    End If
  End If
  
  Debug.Assert Subclass_Subclass
End Function

'Stop subclassing the window
Private Function Subclass_UnSubclass() As Boolean
  If hWndSub <> 0 Then
    lngMsgCntA = 0
    lngMsgCntB = 0
    Call Subclass_PatchVal(PATCH_06, lngMsgCntA)                              'Patch the TableA entry count to ensure no further Proc callbacks
    Call Subclass_PatchVal(PATCH_09, lngMsgCntB)                              'Patch the TableB entry count to ensure no further Proc callbacks
    
    'Restore the original WndProc
    Call api_SetWindowLong(hWndSub, GWL_WNDPROC, nAddrOriginal)
    
    hWndSub = 0                                             'Indicate the subclasser is inactive

    Subclass_UnSubclass = True                              'Success
  End If
  
End Function

'Return the address of the passed function in the passed dll
Private Function Subclass_AddrFunc(ByVal sDLL As String, _
                          ByVal sProc As String) As Long
  Subclass_AddrFunc = api_GetProcAddress(api_GetModuleHandle(sDLL), sProc)
  
End Function

'Return the address of the low bound of the passed table array
Private Function Subclass_AddrMsgTbl(ByRef aMsgTbl() As Long) As Long
  On Error Resume Next                                    'The table may not be dimensioned yet so we need protection
    Subclass_AddrMsgTbl = VarPtr(aMsgTbl(1))              'Get the address of the first element of the passed message table
  On Error GoTo 0                                         'Switch off error protection
End Function

'Patch the machine code buffer offset with the relative address to the target address
Private Sub Subclass_PatchRel(ByVal nOffset As Long, _
                     ByVal nTargetAddr As Long)
  Call api_CopyMemory(ByVal (nAddrSubclass + nOffset), nTargetAddr - nAddrSubclass - nOffset - 4, 4)
End Sub

'Patch the machine code buffer offset with the passed value
Private Sub Subclass_PatchVal(ByVal nOffset As Long, _
                     ByVal nValue As Long)
  Call api_CopyMemory(ByVal (nAddrSubclass + nOffset), nValue, 4)
End Sub

'Worker function for InIDE - will only be called whilst running in the IDE
Private Function Subclass_SetTrue(bValue As Boolean) As Boolean
  Subclass_SetTrue = True
  bValue = True
End Function

Private Sub Subclass_AddResolveMessage(ByVal lngAsync As Long, ByVal lngObjectPointer As Long)
Dim Count As Long
For Count = 1 To lngMsgCntA
    Select Case lngTableA1(Count)
    
    Case -1
        lngTableA1(Count) = lngAsync
        lngTableA2(Count) = lngObjectPointer
        Exit Sub
    Case lngAsync
        'Debug.Print "WARNING: Async already registered!"
        Exit Sub
    End Select
Next Count

lngMsgCntA = lngMsgCntA + 1
ReDim Preserve lngTableA1(1 To lngMsgCntA)
ReDim Preserve lngTableA2(1 To lngMsgCntA)
 
lngTableA1(lngMsgCntA) = lngAsync
lngTableA2(lngMsgCntA) = lngObjectPointer
Subclass_PatchTableA

End Sub

Private Sub Subclass_AddSocketMessage(ByVal lngSocket As Long, ByVal lngObjectPointer As Long)
Dim Count As Long
For Count = 1 To lngMsgCntB
    Select Case lngTableB1(Count)
    
    Case -1
        lngTableB1(Count) = lngSocket
        lngTableB2(Count) = lngObjectPointer
        Exit Sub
    Case lngSocket
        'Debug.Print "WARNING: Socket already registered!"
        Exit Sub
    End Select
Next Count

lngMsgCntB = lngMsgCntB + 1
ReDim Preserve lngTableB1(1 To lngMsgCntB)
ReDim Preserve lngTableB2(1 To lngMsgCntB)
 
lngTableB1(lngMsgCntB) = lngSocket
lngTableB2(lngMsgCntB) = lngObjectPointer
Subclass_PatchTableB

End Sub

Private Sub Subclass_DelResolveMessage(ByVal lngAsync As Long)
Dim Count As Long
For Count = 1 To lngMsgCntA
    If lngTableA1(Count) = lngAsync Then
        lngTableA1(Count) = -1
        lngTableA2(Count) = -1
        Exit Sub
    End If
Next Count
End Sub

Private Sub Subclass_DelSocketMessage(ByVal lngSocket As Long)
Dim Count As Long
For Count = 1 To lngMsgCntB
    If lngTableB1(Count) = lngSocket Then
        lngTableB1(Count) = -1
        lngTableB2(Count) = -1
        Exit Sub
    End If
Next Count
End Sub

Private Sub Subclass_PatchTableA()
Const PATCH_07 As Long = 114
Const PATCH_08 As Long = 130

Call Subclass_PatchVal(PATCH_06, lngMsgCntA)
Call Subclass_PatchVal(PATCH_07, Subclass_AddrMsgTbl(lngTableA1))
Call Subclass_PatchVal(PATCH_08, Subclass_AddrMsgTbl(lngTableA2))
End Sub

Private Sub Subclass_PatchTableB()
Const PATCH_0A As Long = 145
Const PATCH_0B As Long = 161

Call Subclass_PatchVal(PATCH_09, lngMsgCntB)
Call Subclass_PatchVal(PATCH_0A, Subclass_AddrMsgTbl(lngTableB1))
Call Subclass_PatchVal(PATCH_0B, Subclass_AddrMsgTbl(lngTableB2))
End Sub

Public Sub Subclass_ChangeOwner(ByVal lngSocket As Long, ByVal lngObjectPointer As Long)
Dim Count As Long
For Count = 1 To lngMsgCntB
    If lngTableB1(Count) = lngSocket Then
        lngTableB2(Count) = lngObjectPointer
        Exit Sub
    End If
Next Count
End Sub
