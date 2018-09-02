{******************************************************************************}
{                                                       	               }
{ Winsock2 Service Provider API interface Unit for Object Pascal               }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: ws2spi.h, released June 2000. The original Pascal      }
{ code is: WS2spi.pas, released December 2000. The initial developer of the    }
{ Pascal code is Marcel van Brakel (brakelm@chello.nl).                        }
{                                                                              }
{ Portions created by Marcel van Brakel are Copyright (C) 1999-2001            }
{ Marcel van Brakel. All Rights Reserved.                                      }
{ 								               }
{ Obtained through: Joint Endeavour of Delphi Innovators (Project JEDI)        }
{								               }
{ You may retrieve the latest version of this file at the Project JEDI home    }
{ page, located at http://delphi-jedi.org or my personal homepage located at   }
{ http://members.chello.nl/m.vanbrakel2                                        }
{								               }
{ The contents of this file are used with permission, subject to the Mozilla   }
{ Public License Version 1.1 (the "License"); you may not use this file except }
{ in compliance with the License. You may obtain a copy of the License at      }
{ http://www.mozilla.org/MPL/MPL-1.1.html                                      }
{                                                                              }
{ Software distributed under the License is distributed on an "AS IS" basis,   }
{ WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for }
{ the specific language governing rights and limitations under the License.    }
{                                                                              }
{ Alternatively, the contents of this file may be used under the terms of the  }
{ GNU Lesser General Public License (the  "LGPL License"), in which case the   }
{ provisions of the LGPL License are applicable instead of those above.        }
{ If you wish to allow use of your version of this file only under the terms   }
{ of the LGPL License and not to allow others to use your version of this file }
{ under the MPL, indicate your decision by deleting  the provisions above and  }
{ replace  them with the notice and other provisions required by the LGPL      }
{ License.  If you do not delete the provisions above, a recipient may use     }
{ your version of this file under either the MPL or the LGPL License.          }
{ 								               }
{ For more information about the LGPL: http://www.gnu.org/copyleft/lesser.html }
{ 								               }
{******************************************************************************}

unit JwaWS2spi;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "ws2spi.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinType, JwaWinSock2;

(*
 * Ensure structures are packed consistently.
 *)

{$IFNDEF _WIN64}
{$ALIGN ON}
{$ELSE}
{$ALIGN OFF}
{$ENDIF}

const
  WSPDESCRIPTION_LEN = 255;
  {$EXTERNALSYM WSPDESCRIPTION_LEN}

  WSS_OPERATION_IN_PROGRESS = $00000103;
  {$EXTERNALSYM WSS_OPERATION_IN_PROGRESS}

type
  WSPData = record
    wVersion: WORD;
    wHighVersion: WORD;
    szDescription: array [0..WSPDESCRIPTION_LEN] of WCHAR;
  end;
  {$EXTERNALSYM WSPData}
  LPWSPDATA = ^WSPData;
  {$EXTERNALSYM LPWSPDATA}
  TWSPData = WSPDATA;
  PWSPData = LPWSPDATA;

  _WSATHREADID = record
    ThreadHandle: HANDLE;
    Reserved: DWORD;
  end;
  {$EXTERNALSYM _WSATHREADID}
  WSATHREADID = _WSATHREADID;
  {$EXTERNALSYM WSATHREADID}
  LPWSATHREADID = ^WSATHREADID;
  {$EXTERNALSYM LPWSATHREADID}
  TWSAThreadID = WSATHREADID;
  PWSAThreadID = LPWSATHREADID;

(*
 * Pointer to a blocking callback. A pointer to a blocking callback is
 * returned from the WPUQueryBlockingCallback() upcall. Note that this
 * function's signature is not identical to an application's blocking
 * hook function.
 *)

type
  LPBLOCKINGCALLBACK = function (dwContext: DWORD): BOOL; stdcall;
  {$EXTERNALSYM LPBLOCKINGCALLBACK}
  TBlockingCallback = LPBLOCKINGCALLBACK;

(*
 * Pointer to a user APC function. This is used as a parameter to the
 * WPUQueueUserApc() upcall. Note that this function's signature is not
 * identical to an application's completion routine.
 *)

  LPWSAUSERAPC = procedure (dwContext: DWORD); stdcall;
  {$EXTERNALSYM LPWSAUSERAPC}
  TWsaUserApc = LPWSAUSERAPC;

(*
 * Pointers to the individual entries in a service provider's proc table.
 *)

  LPWSPACCEPT = function (s: TSocket; addr: PSockAddr; addrlen: PINT;
    lpfnCondition: LPCONDITIONPROC; dwCallbackData: DWORD; var Errno: Integer): TSocket; stdcall;
  {$EXTERNALSYM LPWSPACCEPT}
  TWspAccept = LPWSPACCEPT;

  LPWSPADDRESSTOSTRING = function (lpsaAddress: LPSOCKADDR; dwAddressLength: DWORD;
    lpProtocolInfo: LPWSAPROTOCOL_INFOW; lpszAddressString: LPWSTR;
    var lpdwAddressStringLength: DWORD; var lpErrno: Integer): Integer; stdcall;
  {$EXTERNALSYM LPWSPADDRESSTOSTRING}
  TWspAddressToString = LPWSPADDRESSTOSTRING;

  LPWSPASYNCSELECT = function (s: TSocket; hWnd: HWND; wMsg: u_int; lEvent: Longint; var lpErrno: Integer): Integer; stdcall;
  {$EXTERNALSYM LPWSPASYNCSELECT}
  TWspASyncSelect = LPWSPASYNCSELECT;

  LPWSPBIND = function (s: TSocket; var name: sockaddr; namelen: Integer; var lpErrno: Integer): Integer; stdcall;
  {$EXTERNALSYM LPWSPBIND}
  TWspBind = LPWSPBIND;

  LPWSPCANCELBLOCKINGCALL = function (var lpErrno: Integer): Integer; stdcall;
  {$EXTERNALSYM LPWSPCANCELBLOCKINGCALL}
  TWspCancelBlockingCall = LPWSPCANCELBLOCKINGCALL;

  LPWSPCLEANUP = function (var lpErrno: Integer): Integer; stdcall;
  {$EXTERNALSYM LPWSPCLEANUP}
  TWspCleanup = LPWSPCLEANUP;

  LPWSPCLOSESOCKET = function (s: TSocket; var lpErrno: Integer): Integer; stdcall;
  {$EXTERNALSYM LPWSPCLOSESOCKET}
  TWspCloseSocket = LPWSPCLOSESOCKET;

  LPWSPCONNECT = function (s: TSocket; name: PSockAddr; namelen: Integer; lpCallerData: LPWSABUF;
    lpCalleeData: LPWSABUF; lpSQOS: LPQOS; lpGQOS: LPQOS; var lpErrno: Integer): Integer; stdcall;
  {$EXTERNALSYM LPWSPCONNECT}
  TWspConnect = LPWSPCONNECT;

  LPWSPDUPLICATESOCKET = function (s: TSocket; dwProcessId: DWORD; lpProtocolInfo: LPWSAPROTOCOL_INFOW; var lpErrno: Integer): Integer; stdcall;
  {$EXTERNALSYM LPWSPDUPLICATESOCKET}
  TWspDuplicateSocket = LPWSPDUPLICATESOCKET;

  LPWSPENUMNETWORKEVENTS = function (s: TSocket; hEventObject: WSAEVENT; lpNetworkEvents: LPWSANETWORKEVENTS; var lpErrno: Integer): Integer; stdcall;
  {$EXTERNALSYM LPWSPENUMNETWORKEVENTS}
  TWspEnumNetworkEvents = LPWSPENUMNETWORKEVENTS;

  LPWSPEVENTSELECT = function (s: TSocket; hEventObject: WSAEVENT; lNetworkEvents: Longint; var lpErrno: Integer): Integer; stdcall;
  {$EXTERNALSYM LPWSPEVENTSELECT}
  TWspEventSelect = LPWSPEVENTSELECT;

  LPWSPGETOVERLAPPEDRESULT = function (s: TSocket; lpOverlapped: LPWSAOVERLAPPED;
    var lpcbTransfer: DWORD; fWait: BOOL; lpdwFlags: DWORD; var lpErrno: Integer): BOOL; stdcall;
  {$EXTERNALSYM LPWSPGETOVERLAPPEDRESULT}
  TWspGetOverlappedResult = LPWSPGETOVERLAPPEDRESULT;

  LPWSPGETPEERNAME = function (s: TSocket; var name: sockaddr; var namelen, lpErrno: Integer): Integer; stdcall;
  {$EXTERNALSYM LPWSPGETPEERNAME}
  TWspGetPeerName = LPWSPGETPEERNAME;

  LPWSPGETSOCKNAME = function (s: TSocket; var name: sockaddr; var namelen, lpErrno: Integer): Integer; stdcall;
  {$EXTERNALSYM LPWSPGETSOCKNAME}
  TWspGetSockName = LPWSPGETSOCKNAME;

  LPWSPGETSOCKOPT = function (s: TSocket; level, optname: Integer; optval: PChar; var optlen, lpErrno: Integer): Integer; stdcall;
  {$EXTERNALSYM LPWSPGETSOCKOPT}
  TWspGetSockOpt = LPWSPGETSOCKOPT;

  LPWSPGETQOSBYNAME = function (s: TSocket; var lpQOSName: WSABUF; lpQOS: LPQOS; lpErrno: Integer): BOOL; stdcall;
  {$EXTERNALSYM LPWSPGETQOSBYNAME}
  TWspGetQosByName = LPWSPGETQOSBYNAME;

  LPWSPIOCTL = function (s: TSocket; dwIoControlCode: DWORD; lpvInBuffer: LPVOID; cbInBuffer: DWORD;
    lpvOutBuffer: LPVOID; cbOutBuffer: DWORD; var lpcbBytesReturned: DWORD;
    lpOverlapped: LPWSAOVERLAPPED; lpCompletionRoutine: LPWSAOVERLAPPED_COMPLETION_ROUTINE;
    lpThreadId: LPWSATHREADID; var lpErrno: Integer): Integer; stdcall;
  {$EXTERNALSYM LPWSPIOCTL}
  TWspIoctl = LPWSPIOCTL;

  LPWSPJOINLEAF = function (s: TSocket; name: sockaddr; namelen: Integer; lpCallerData: LPWSABUF;
    lpCalleeData: LPWSABUF; lpSQOS, lpGQOS: LPQOS; dwFlags: DWORD; var lpErrno: Integer): TSocket; stdcall;
  {$EXTERNALSYM LPWSPJOINLEAF}
  TWspJoinLeaf = LPWSPJOINLEAF;

  LPWSPLISTEN = function (s: TSocket; backlog: Integer; var lpErrno: Integer): Integer; stdcall;
  {$EXTERNALSYM LPWSPLISTEN}
  TWspListen = LPWSPLISTEN;

  LPWSPRECV = function (s: TSocket; lpBuffers: LPWSABUF; dwBufferCount: DWORD;
    var lpNumberOfBytesRecvd, lpFlags: DWORD; lpOverlapped: LPWSAOVERLAPPED;
    lpCompletionRoutine: LPWSAOVERLAPPED_COMPLETION_ROUTINE; lpThreadId: LPWSATHREADID;
    var lpErrno: Integer): Integer; stdcall;
  {$EXTERNALSYM LPWSPRECV}
  TWspRecv = LPWSPRECV;

  LPWSPRECVDISCONNECT = function (s: TSocket; lpInboundDisconnectData: LPWSABUF; var lpErrno: Integer): Integer; stdcall;
  {$EXTERNALSYM LPWSPRECVDISCONNECT}
  TWspRecvDisconnect = LPWSPRECVDISCONNECT;

  LPWSPRECVFROM = function (s: TSocket; lpBuffers: LPWSABUF; dwBufferCount: DWORD;
    var lpNumberOfBytesRecvd, lpFlags: DWORD; lpFrom: PSockAddr; lpFromlen: PINT;
    lpOverlapped: LPWSAOVERLAPPED; lpCompletionRoutine: LPWSAOVERLAPPED_COMPLETION_ROUTINE;
    lpThreadId: LPWSATHREADID; var lpErrno: Integer): Integer; stdcall;
  {$EXTERNALSYM LPWSPRECVFROM}
  TWspRecvFrom = LPWSPRECVFROM;

  LPWSPSELECT = function (nfds: Integer; readfds, writefds, exceptfds: PFdSet; timeout: PTimeVal; var lpErrno: Integer): Integer; stdcall;
  {$EXTERNALSYM LPWSPSELECT}
  TWspSelect = LPWSPSELECT;

  LPWSPSEND = function (s: TSocket; lpBuffers: LPWSABUF; dwBufferCount: DWORD;
    var lpNumberOfBytesSent: DWORD; dwFlags: DWORD; lpOverlapped: LPWSAOVERLAPPED;
    lpCompletionRoutine: LPWSAOVERLAPPED_COMPLETION_ROUTINE;
    lpThreadId: LPWSATHREADID; var lpErrno: Integer): Integer; stdcall;
  {$EXTERNALSYM LPWSPSEND}
  TWspSend = LPWSPSEND;

  LPWSPSENDDISCONNECT = function (s: TSocket; lpOutboundDisconnectData: LPWSABUF; var lpErrno: Integer): Integer; stdcall;
  {$EXTERNALSYM LPWSPSENDDISCONNECT}
  TWspSendDisconnect = LPWSPSENDDISCONNECT;

  LPWSPSENDTO = function (s: TSocket; lpBuffers: LPWSABUF; dwBufferCount: DWORD;
    var lpNumberOfBytesSent: DWORD; dwFlags: DWORD; lpTo: PSockAddr; iTolen: Integer;
    lpOverlapped: LPWSAOVERLAPPED; lpCompletionRoutine: LPWSAOVERLAPPED_COMPLETION_ROUTINE;
    lpThreadId: LPWSATHREADID; var lpErrno: Integer): Integer; stdcall;
  {$EXTERNALSYM LPWSPSENDTO}
  TWspSendTo = LPWSPSENDTO;

  LPWSPSETSOCKOPT = function (s: TSocket; level, optname: Integer; optval: PChar; optlen: Integer; var lpErrno: Integer): Integer; stdcall;
  {$EXTERNALSYM LPWSPSETSOCKOPT}
  TWspSetSockOpt = LPWSPSETSOCKOPT;

  LPWSPSHUTDOWN = function (s: TSocket; how: Integer; var lpErrno: Integer): Integer; stdcall;
  {$EXTERNALSYM LPWSPSHUTDOWN}
  TWspShutdown = LPWSPSHUTDOWN;

  LPWSPSOCKET = function (af, type_, protocol: Integer; lpProtocolInfo: LPWSAPROTOCOL_INFOW;
    g: GROUP; dwFlags: DWORD; var lpErrno: Integer): TSocket; stdcall;
  {$EXTERNALSYM LPWSPSOCKET}
  TWspSocket = LPWSPSOCKET;

  LPWSPSTRINGTOADDRESS = function (AddressString: LPWSTR; AddressFamily: Integer;
    lpProtocolInfo: LPWSAPROTOCOL_INFOW; lpAddress: LPSOCKADDR;
    var lpAddressLength, lpErrno: Integer): Integer; stdcall;
  {$EXTERNALSYM LPWSPSTRINGTOADDRESS}
  TWspStringToAddress = LPWSPSTRINGTOADDRESS;

(*
 * A service provider proc table. This structure is returned by value
 * from the service provider's WSPStartup() entrypoint.
 *)

type
  _WSPPROC_TABLE = record
    lpWSPAccept: LPWSPACCEPT;
    lpWSPAddressToString: LPWSPADDRESSTOSTRING;
    lpWSPAsyncSelect: LPWSPASYNCSELECT;
    lpWSPBind: LPWSPBIND;
    lpWSPCancelBlockingCall: LPWSPCANCELBLOCKINGCALL;
    lpWSPCleanup: LPWSPCLEANUP;
    lpWSPCloseSocket: LPWSPCLOSESOCKET;
    lpWSPConnect: LPWSPCONNECT;
    lpWSPDuplicateSocket: LPWSPDUPLICATESOCKET;
    lpWSPEnumNetworkEvents: LPWSPENUMNETWORKEVENTS;
    lpWSPEventSelect: LPWSPEVENTSELECT;
    lpWSPGetOverlappedResult: LPWSPGETOVERLAPPEDRESULT;
    lpWSPGetPeerName: LPWSPGETPEERNAME;
    lpWSPGetSockName: LPWSPGETSOCKNAME;
    lpWSPGetSockOpt: LPWSPGETSOCKOPT;
    lpWSPGetQOSByName: LPWSPGETQOSBYNAME;
    lpWSPIoctl: LPWSPIOCTL;
    lpWSPJoinLeaf: LPWSPJOINLEAF;
    lpWSPListen: LPWSPLISTEN;
    lpWSPRecv: LPWSPRECV;
    lpWSPRecvDisconnect: LPWSPRECVDISCONNECT;
    lpWSPRecvFrom: LPWSPRECVFROM;
    lpWSPSelect: LPWSPSELECT;
    lpWSPSend: LPWSPSEND;
    lpWSPSendDisconnect: LPWSPSENDDISCONNECT;
    lpWSPSendTo: LPWSPSENDTO;
    lpWSPSetSockOpt: LPWSPSETSOCKOPT;
    lpWSPShutdown: LPWSPSHUTDOWN;
    lpWSPSocket: LPWSPSOCKET;
    lpWSPStringToAddress: LPWSPSTRINGTOADDRESS;
  end;
  {$EXTERNALSYM _WSPPROC_TABLE}
  WSPPROC_TABLE = _WSPPROC_TABLE;
  {$EXTERNALSYM WSPPROC_TABLE}
  LPWSPPROC_TABLE = ^WSPPROC_TABLE;
  {$EXTERNALSYM LPWSPPROC_TABLE}
  TWspProcTable = WSPPROC_TABLE;
  PWspProcTable = LPWSPPROC_TABLE;

(*
 * Pointers to the individual entries in the upcall table.
 *)

type
  LPWPUCLOSEEVENT = function (hEvent: WSAEVENT; var lpErrno: Integer): BOOL; stdcall;
  {$EXTERNALSYM LPWPUCLOSEEVENT}
  TWpuCloseEvent = LPWPUCLOSEEVENT;

  LPWPUCLOSESOCKETHANDLE = function (s: TSocket; var lpErrno: Integer): Integer; stdcall;
  {$EXTERNALSYM LPWPUCLOSESOCKETHANDLE}
  TWpuCloseSocketHandle = LPWPUCLOSESOCKETHANDLE;

  LPWPUCREATEEVENT = function (var lpErrno: Integer): WSAEVENT; stdcall;
  {$EXTERNALSYM LPWPUCREATEEVENT}
  TWpuCreateEvent = LPWPUCREATEEVENT;

  LPWPUCREATESOCKETHANDLE = function (dwCatalogEntryId, dwContext: DWORD;
    var lpErrno: Integer): TSocket; stdcall;
  {$EXTERNALSYM LPWPUCREATESOCKETHANDLE}
  TWpuCreateSocketHandle = LPWPUCREATESOCKETHANDLE;

  LPWPUFDISSET = function (s: TSocket; fdset: PFdSet): Integer; stdcall;
  {$EXTERNALSYM LPWPUFDISSET}
  TWpuFdIsSet = LPWPUFDISSET;

  LPWPUGETPROVIDERPATH = function (const lpProviderId: TGUID;
    lpszProviderDllPath: PWCHAR; var lpProviderDllPathLen, lpErrno: Integer): Integer; stdcall;
  {$EXTERNALSYM LPWPUGETPROVIDERPATH}
  TWpuGetProviderPath = LPWPUGETPROVIDERPATH;

  LPWPUMODIFYIFSHANDLE = function (dwCatalogEntryId: DWORD; ProposedHandle: TSocket;
    var lpErrno: Integer): TSocket; stdcall;
  {$EXTERNALSYM LPWPUMODIFYIFSHANDLE}
  TWpuMoifyIfsHandle = LPWPUMODIFYIFSHANDLE;

  LPWPUPOSTMESSAGE = function (hWnd: HWND; Msg: UINT; wParam: WPARAM; lParam: LPARAM): BOOL; stdcall;
  {$EXTERNALSYM LPWPUPOSTMESSAGE}
  TWpuPostMessage = LPWPUPOSTMESSAGE;

  LPWPUQUERYBLOCKINGCALLBACK = function (dwCatalogEntryId: DWORD; var lplpfnCallback: LPBLOCKINGCALLBACK;
    lpdwContext: LPDWORD; var lpErrno: Integer): Integer; stdcall;
  {$EXTERNALSYM LPWPUQUERYBLOCKINGCALLBACK}
  TWpuQueryBlockingCallback = LPWPUQUERYBLOCKINGCALLBACK;

  LPWPUQUERYSOCKETHANDLECONTEXT = function (s: TSocket; lpContext: LPDWORD;
    var lpErrno: Integer): Integer; stdcall;
  {$EXTERNALSYM LPWPUQUERYSOCKETHANDLECONTEXT}
  TWpuQuerySocketHandleContext = LPWPUQUERYSOCKETHANDLECONTEXT;

  LPWPUQUEUEAPC = function (lpThreadId: LPWSATHREADID; lpfnUserApc: LPWSAUSERAPC;
    dwContext: DWORD; var lpErrno: Integer): Integer; stdcall;
  {$EXTERNALSYM LPWPUQUEUEAPC}
  TWpuQueueApc = LPWPUQUEUEAPC;

  LPWPURESETEVENT = function (hEvent: WSAEVENT; var lpErrno: Integer): BOOL; stdcall;
  {$EXTERNALSYM LPWPURESETEVENT}
  TWpuResetEvent = LPWPURESETEVENT;

  LPWPUSETEVENT = function (hEvent: WSAEVENT; var lpErrno: Integer): BOOL; stdcall;
  {$EXTERNALSYM LPWPUSETEVENT}
  TWpuSetEvent = LPWPUSETEVENT;

  LPWPUOPENCURRENTTHREAD = function (lpThreadId: LPWSATHREADID; var lpErrno: Integer): Integer; stdcall;
  {$EXTERNALSYM LPWPUOPENCURRENTTHREAD}
  TWpuOpenCurrentThread = LPWPUOPENCURRENTTHREAD;

  LPWPUCLOSETHREAD = function (lpThreadId: LPWSATHREADID; var lpErrno: Integer): Integer; stdcall;
  {$EXTERNALSYM LPWPUCLOSETHREAD}
  TWpuCloseThread = LPWPUCLOSETHREAD;

// Available only directly from ws2_32.dll

  LPWPUCOMPLETEOVERLAPPEDREQUEST = function (s: TSocket; lpOverlapped: LPWSAOVERLAPPED;
    dwError: DWORD; cbTransferred: DWORD; var lpErrno: Integer): Integer; stdcall;
  {$EXTERNALSYM LPWPUCOMPLETEOVERLAPPEDREQUEST}
  TWpuCompleteOverlappedRequest = LPWPUCOMPLETEOVERLAPPEDREQUEST;

(*
 * The upcall table. This structure is passed by value to the service
 * provider's WSPStartup() entrypoint.
 *)

  _WSPUPCALLTABLE = record
    lpWPUCloseEvent: LPWPUCLOSEEVENT;
    lpWPUCloseSocketHandle: LPWPUCLOSESOCKETHANDLE;
    lpWPUCreateEvent: LPWPUCREATEEVENT;
    lpWPUCreateSocketHandle: LPWPUCREATESOCKETHANDLE;
    lpWPUFDIsSet: LPWPUFDISSET;
    lpWPUGetProviderPath: LPWPUGETPROVIDERPATH;
    lpWPUModifyIFSHandle: LPWPUMODIFYIFSHANDLE;
    lpWPUPostMessage: LPWPUPOSTMESSAGE;
    lpWPUQueryBlockingCallback: LPWPUQUERYBLOCKINGCALLBACK;
    lpWPUQuerySocketHandleContext: LPWPUQUERYSOCKETHANDLECONTEXT;
    lpWPUQueueApc: LPWPUQUEUEAPC;
    lpWPUResetEvent: LPWPURESETEVENT;
    lpWPUSetEvent: LPWPUSETEVENT;
    lpWPUOpenCurrentThread: LPWPUOPENCURRENTTHREAD;
    lpWPUCloseThread: LPWPUCLOSETHREAD;
  end;
  {$EXTERNALSYM _WSPUPCALLTABLE}
  WSPUPCALLTABLE = _WSPUPCALLTABLE;
  {$EXTERNALSYM WSPUPCALLTABLE}
  LPWSPUPCALLTABLE = ^WSPUPCALLTABLE;
  {$EXTERNALSYM LPWSPUPCALLTABLE}
  TWspUpCallTable = WSPUPCALLTABLE;
  PWspUpCallTable = LPWSPUPCALLTABLE;  

(*
 *  WinSock 2 SPI socket function prototypes
 *)

//function WSPStartup(wVersionRequested: WORD; lpWSPData: LPWSPDATA;
//  lpProtocolInfo: LPWSAPROTOCOL_INFOW; UpcallTable: WSPUPCALLTABLE;
//  lpProcTable: LPWSPPROC_TABLE): Integer; stdcall;
//{$EXTERNALSYM WSPStartup}

type
  LPWSPSTARTUP = function (wVersionRequested: WORD; lpWSPData: LPWSPDATA;
    lpProtocolInfo: LPWSAPROTOCOL_INFOW; UpcallTable: WSPUPCALLTABLE;
    lpProcTable: LPWSPPROC_TABLE): Integer; stdcall;
  {$EXTERNALSYM LPWSPSTARTUP}
  TWspStartUp = LPWSPSTARTUP;

(*
 * Installation and configuration entrypoints.
 *)

function WSCEnumProtocols(lpiProtocols: PINT; lpProtocolBuffer: LPWSAPROTOCOL_INFOW;
  var lpdwBufferLength: DWORD; var lpErrno: Integer): Integer; stdcall;
{$EXTERNALSYM WSCEnumProtocols}

type
  LPWSCENUMPROTOCOLS = function (lpiProtocols: PINT; lpProtocolBuffer: LPWSAPROTOCOL_INFOW;
    var lpdwBufferLength: DWORD; var lpErrno: Integer): Integer; stdcall;
  {$EXTERNALSYM LPWSCENUMPROTOCOLS}
  TWscEnumProtocols = LPWSCENUMPROTOCOLS;

{$IFDEF _WIN64}

//
// 64-bit architectures capable of running 32-bit code have
// separate 64-bit and 32-bit catalogs.  API with '32' prefix
// allow 32 bit catalog manipulations by 64 bit process.
//

function WSCEnumProtocols32(lpiProtocols: PINT; lpProtocolBuffer: LPWSAPROTOCOL_INFOW; lpdwBufferLength: LPDWORD; lpErrno: PINT): Integer; stdcall;
{$EXTERNALSYM WSCEnumProtocols32}

{$ENDIF _WIN64}

function WSCDeinstallProvider(const lpProviderId: TGUID; var lpErrno: Integer): Integer; stdcall;
{$EXTERNALSYM WSCDeinstallProvider}

type
  LPWSCDEINSTALLPROVIDER = function (const lpProviderId: TGUID; var lpErrno: Integer): Integer; stdcall;
  {$EXTERNALSYM LPWSCDEINSTALLPROVIDER}
  TWscDeinstallProvider = LPWSCDEINSTALLPROVIDER;

{$IFDEF _WIN64}

function WSCDeinstallProvider32(lpProviderId: PGUID; lpErrno: PINT): Integer; stdcall;
{$EXTERNALSYM WSCDeinstallProvider32}

{$ENDIF _WIN64}

function WSCInstallProvider(const lpProviderId: TGUID; lpszProviderDllPath: PWCHAR;
  lpProtocolInfoList: LPWSAPROTOCOL_INFOW; dwNumberOfEntries: DWORD; var lpErrno: Integer): Integer; stdcall;
{$EXTERNALSYM WSCInstallProvider}

type
  LPWSCINSTALLPROVIDER = function (const lpProviderId: TGUID; lpszProviderDllPath: PWCHAR;
    lpProtocolInfoList: LPWSAPROTOCOL_INFOW; dwNumberOfEntries: DWORD; var lpErrno: Integer): Integer; stdcall;
  {$EXTERNALSYM LPWSCINSTALLPROVIDER}
  TWscInstallProvider = LPWSCINSTALLPROVIDER;

{$IFDEF _WIN64}

//
// This API manipulates 64-bit and 32-bit catalogs simulteneously.
// It is needed to guarantee the same catalog IDs for provider catalog
// entries in both 64-bit and 32-bit catalogs.
//

function WSCInstallProvider64_32(lpProviderId: PGUID; lpszProviderDllPath: PWCHAR; lpProtocolInfoList: LPWSAPROTOCOL_INFOW;
  dwNumberOfEntries: DWORD; lpErrno: PINT): Integer; stdcall;
{$EXTERNALSYM WSCInstallProvider64_32}

{$ENDIF _WIN64}

function WSCGetProviderPath(const lpProviderId: TGUID; lpszProviderDllPath: PWCHAR;
  var lpProviderDllPathLen, lpErrno: Integer): Integer; stdcall;
{$EXTERNALSYM WSCGetProviderPath}

type
  LPWSCGETPROVIDERPATH = function (const lpProviderId: TGUID; lpszProviderDllPath: PWCHAR;
  var lpProviderDllPathLen, lpErrno: Integer): Integer; stdcall;
  {$EXTERNALSYM LPWSCGETPROVIDERPATH}
  TWscGetProviderPath = LPWSCGETPROVIDERPATH;

{$IFDEF _WIN64}

function WSCGetProviderPath32(lpProviderId: PGUID; lpszProviderDllPath: PWCHAR; lpProviderDllPathLen: PINT; lpErrno: PINT): Integer; stdcall;
{$EXTERNALSYM WSCGetProviderPath32}

{$ENDIF _WIN64}

function WSCUpdateProvider(lpProviderId: PGUID; lpszProviderDllPath: PWCHAR; lpProtocolInfoList: LPWSAPROTOCOL_INFOW;
  dwNumberOfEntries: DWORD; lpErrno: PINT): Integer; stdcall;
{$EXTERNALSYM WSCUpdateProvider}

type
  LPWSCUPDATEPROVIDER = function (lpProviderId: PGUID; lpszProviderDllPath: PWCHAR; lpProtocolInfoList: LPWSAPROTOCOL_INFOW;
    dwNumberOfEntries: DWORD; lpErrno: PINT): Integer; stdcall;
  {$EXTERNALSYM LPWSCUPDATEPROVIDER}

{$IFDEF _WIN64}

function WSCUpdateProvider32(lpProviderId: PGUID; lpszProviderDllPath: PWCHAR; lpProtocolInfoList: LPWSAPROTOCOL_INFOW;
  dwNumberOfEntries: DWORD; lpErrno: PINT): Integer; stdcall;
{$EXTERNALSYM WSCUpdateProvider32}

{$ENDIF _WIN64}

function WSCInstallQOSTemplate(const Guid: TGUID; QosName: LPWSABUF; Qos: LPQOS): Integer; stdcall;
{$EXTERNALSYM WSCInstallQOSTemplate}

type
  LPWSCINSTALLQOSTEMPLATE = function (const Guid: TGUID; QosName: LPWSABUF; Qos: LPQOS): Integer; stdcall;
  {$EXTERNALSYM LPWSCINSTALLQOSTEMPLATE}
  TWscInstallQosTemplate = LPWSCINSTALLQOSTEMPLATE;

function WSCRemoveQOSTemplate(const Guid: TGUID; QosName: LPWSABUF): Integer; stdcall;
{$EXTERNALSYM WSCRemoveQOSTemplate}

type
  LPWSCREMOVEQOSTEMPLATE = function (const Guid: TGUID; QosName: LPWSABUF): Integer; stdcall;
  {$EXTERNALSYM LPWSCREMOVEQOSTEMPLATE}
  TWscRemoveQosTemplate = LPWSCREMOVEQOSTEMPLATE;

(*
 *  The following upcall function prototypes are only used by WinSock 2 DLL and
 *  should not be used by any service providers.
 *

function WPUCloseEvent(hEvent: WSAEVENT; var lpErrno: Integer): BOOL; stdcall;
{$EXTERNALSYM WPUCloseEvent}

function WPUCloseSocketHandle(s: TSocket; var lpErrno: Integer): Integer; stdcall;
{$EXTERNALSYM WPUCloseSocketHandle}

function WPUCreateEvent(var lpErrno: Integer): WSAEVENT; stdcall;
{$EXTERNALSYM WPUCreateEvent}

function WPUCreateSocketHandle(dwCatalogEntryId, dwContext: DWORD; var lpErrno: Integer): SOCKET; stdcall;
{$EXTERNALSYM WPUCreateSocketHandle}

function WPUFDIsSet(s: TSocket; const fdset: fd_set): Integer; stdcall;
{$EXTERNALSYM WPUFDIsSet}

function WPUGetProviderPath(const lpProviderId: TGUID; lpszProviderDllPath: PWCHAR;
  var lpProviderDllPathLen, lpErrno: : Integer): Integer; stdcall;
{$EXTERNALSYM WPUGetProviderPath}

function WPUModifyIFSHandle(dwCatalogEntryId: DWORD; ProposedHandle: SOCKET; var lpErrno: Integer): SOCKET; stdcall;
{$EXTERNALSYM WPUModifyIFSHandle}

function WPUPostMessage(hWnd: HWND; Msg: UINT; wParam: WPARAM; lParam: LPARAM): BOOL; stdcall;
{$EXTERNALSYM WPUPostMessage}

function WPUQueryBlockingCallback(dwCatalogEntryId: DWORD; var lplpfnCallback: LPBLOCKINGCALLBACK;
  var lpdwContext: DWORD_PTR; var lpErrno: Integer): Integer; stdcall;
{$EXTERNALSYM WPUQueryBlockingCallback}

function WPUQuerySocketHandleContext(s: SOCKET; var lpContext: DWORD_PTR; lpErrno: Integer): Integer; stdcall;
{$EXTERNALSYM WPUQuerySocketHandleContext}

function WPUQueueApc(lpThreadId: LPWSATHREADID; lpfnUserApc: LPWSAUSERAPC;
  dwContext: DWORD_PTR; var lpErrno: Integer): Integer; stdcall;
{$EXTERNALSYM WPUQueueApc}

function WPUResetEvent(hEvent: WSAEVENT; var lpErrno: Integer): BOOL; stcall;
{$EXTERNALSYM WPUResetEvent}

function WPUSetEvent(hEvent: WSAEVENT; var lpErrno: Integer): BOOL; stdcall;
{$EXTERNALSYM WPUSetEvent}

function WPUCompleteOverlappedRequest(s: SOCKET; lpOverlapped: LPWSAOVERLAPPED;
  dwError, cbTransferred: DWORD; var lpErrno: Integer): Integerl stdcall;
{$EXTERNALSYM WPUCompleteOverlappedRequest}

function WPUOpenCurrentThread(lpThreadId: LPWSATHREADID; lpErrno: PINT): Integer; stdcall;
{$EXTERNALSYM WPUOpenCurrentThread}

function WPUCloseThread(lpThreadId: LPWSATHREADID; lpErrno: PINT): Integer; stdcall;
{$EXTERNALSYM WPUCloseThread}

*)

(*
 * Installing and uninstalling name space providers.
 *)

//
// SPI and API for enumerating name space providers are
// currently equivalent since there is no concept of a hidden
// name space provider
//

//TODO
//#define WSCEnumNameSpaceProviders WSAEnumNameSpaceProvidersW
//#define LPFN_WSCENUMNAMESPACEPROVIDERS LPFN_WSAENUMNAMESPACEPROVIDERSW

{$IFDEF _WIN64}

function WSCEnumNameSpaceProviders32(lpdwBufferLength: LPDWORD; lpnspBuffer: LPWSANAMESPACE_INFOW): Integer; stdcall;
{$EXTERNALSYM WSCEnumNameSpaceProviders32}

{$ENDIF _WIN64}

function WSCInstallNameSpace(lpszIdentifier, lpszPathName: LPWSTR; dwNameSpace,
  dwVersion: DWORD; const lpProviderId: TGUID): Integer; stdcall;
{$EXTERNALSYM WSCInstallNameSpace}

type
  LPWSCINSTALLNAMESPACE = function (lpszIdentifier, lpszPathName: LPWSTR;
    dwNameSpace, dwVersion: DWORD; const lpProviderId: TGUID): Integer; stdcall;
  {$EXTERNALSYM LPWSCINSTALLNAMESPACE}
  TWscInstallNamespace = LPWSCINSTALLNAMESPACE;

{$IFDEF _WIN64}

function WSCInstallNameSpace32(lpszIdentifier, lpszPathName: LPWSTR; dwNameSpace, dwVersion: DWORD; lpProviderId: PGUID): Integer; stdcall;
{$EXTERNALSYM WSCInstallNameSpace32}

{$ENDIF _WIN64}

function WSCUnInstallNameSpace(const lpProviderId: TGUID): Integer; stdcall;
{$EXTERNALSYM WSCUnInstallNameSpace}

type
  LPWSCUNINSTALLNAMESPACE = function (const lpProviderId: TGUID): Integer; stdcall;
  {$EXTERNALSYM LPWSCUNINSTALLNAMESPACE}
  TWscUninstallNamespace = LPWSCUNINSTALLNAMESPACE;

{$IFDEF _WIN64}

function WSCUnInstallNameSpace32(lpProviderId: PGUID): Integer; stdcall;
{$EXTERNALSYM WSCUnInstallNameSpace32}

{$ENDIF _WIN64}

function WSCEnableNSProvider(const lpProviderId: TGUID; fEnable: BOOL): Integer; stdcall;
{$EXTERNALSYM WSCEnableNSProvider}

type
  LPWSCENABLENSPROVIDER = function (const lpProviderId: TGUID; fEnable: BOOL): Integer; stdcall;
  {$EXTERNALSYM LPWSCENABLENSPROVIDER}
  TWscEnableNsProvider = LPWSCENABLENSPROVIDER;

{$IFDEF _WIN64}

function WSCEnableNSProvider32(lpProviderId: PGUID; fEnable: BOOL): Integer; stdcall;
{$EXTERNALSYM WSCEnableNSProvider32}

{$ENDIF _WIN64}


(*
 * Pointers to the individual entries in the namespace proc table.
 *)

type
  LPNSPCLEANUP = function (const lpProviderId: TGUID): Integer; stdcall;
  {$EXTERNALSYM LPNSPCLEANUP}
  TNspCleanup = LPNSPCLEANUP;

  LPNSPLOOKUPSERVICEBEGIN = function (const lpProviderId: TGUID;
    lpqsRestrictions: LPWSAQUERYSETW; lpServiceClassInfo: LPWSASERVICECLASSINFOW;
    dwControlFlags: DWORD; lphLookup: LPHANDLE): Integer; stdcall;
  {$EXTERNALSYM LPNSPLOOKUPSERVICEBEGIN}
  TNspLookupServiceBegin = LPNSPLOOKUPSERVICEBEGIN;

  LPNSPLOOKUPSERVICENEXT = function (hLookup: HANDLE; dwControlFlags: DWORD;
    lpdwBufferLength: LPDWORD; lpqsResults: LPWSAQUERYSETW): Integer; stdcall;
  {$EXTERNALSYM LPNSPLOOKUPSERVICENEXT}
  TNspLookupServiceNext = LPNSPLOOKUPSERVICENEXT;

  LPNSPIOCTL = function (hLookup: HANDLE; dwControlCode: DWORD; lpvInBuffer: LPVOID;
    cbInBuffer: DWORD; lpvOutBuffer: LPVOID; cbOutBuffer: DWORD; lpcbBytesReturned: LPDWORD;
    lpCompletion: LPWSACOMPLETION; lpThreadId: LPWSATHREADID): Integer; stdcall;
  {$EXTERNALSYM LPNSPIOCTL}

  LPNSPLOOKUPSERVICEEND = function (hLookup: HANDLE): Integer; stdcall;
  {$EXTERNALSYM LPNSPLOOKUPSERVICEEND}
  TNspLookupServiceEnd = LPNSPLOOKUPSERVICEEND;

  LPNSPSETSERVICE = function (const lpProviderId: TGUID;
    lpServiceClassInfo: LPWSASERVICECLASSINFOW; lpqsRegInfo: LPWSAQUERYSETW;
    essOperation: WSAESETSERVICEOP; dwControlFlags: DWORD): Integer; stdcall;
  {$EXTERNALSYM LPNSPSETSERVICE}
  TNspSetService = LPNSPSETSERVICE;

  LPNSPINSTALLSERVICECLASS = function (const lpProviderId: TGUID;
    lpServiceClassInfo: LPWSASERVICECLASSINFOW): Integer; stdcall;
  {$EXTERNALSYM LPNSPINSTALLSERVICECLASS}
  TNspInstallServiceClass = LPNSPINSTALLSERVICECLASS;

  LPNSPREMOVESERVICECLASS = function (const lpProviderId, lpServiceClassId: TGUID): Integer; stdcall;
  {$EXTERNALSYM LPNSPREMOVESERVICECLASS}
  TNspRemoveServiceClass = LPNSPREMOVESERVICECLASS;

  LPNSPGETSERVICECLASSINFO = function (const lpProviderId: TGUID; lpdwBufSize: LPDWORD;
    lpServiceClassInfo: LPWSASERVICECLASSINFOW): Integer; stdcall;
  {$EXTERNALSYM LPNSPGETSERVICECLASSINFO}
  TNspGetServiceClassInfo = LPNSPGETSERVICECLASSINFO;

(*
 * The name space service provider procedure table.
 *)

type
  _NSP_ROUTINE = record
    (* Structure version information: *)
    cbSize: DWORD;
    dwMajorVersion: DWORD;
    dwMinorVersion: DWORD;
    (* Procedure-pointer table: *)
    NSPCleanup: LPNSPCLEANUP;
    NSPLookupServiceBegin: LPNSPLOOKUPSERVICEBEGIN;
    NSPLookupServiceNext: LPNSPLOOKUPSERVICENEXT;
    NSPLookupServiceEnd: LPNSPLOOKUPSERVICEEND;
    NSPSetService: LPNSPSETSERVICE;
    NSPInstallServiceClass: LPNSPINSTALLSERVICECLASS;
    NSPRemoveServiceClass: LPNSPREMOVESERVICECLASS;
    NSPGetServiceClassInfo: LPNSPGETSERVICECLASSINFO;
    // These APIs were added later, so must appear here
    // to keep the pointers in the structure in order.
    // Namespaces unaware of these APIs will set cbSize
    // to match the size of FIELD_OFFSET(NSP_ROUTINE, NSPIoctl).
    NSPIoctl: LPNSPIOCTL;
  end;
  {$EXTERNALSYM _NSP_ROUTINE}
  NSP_ROUTINE = _NSP_ROUTINE;
  {$EXTERNALSYM NSP_ROUTINE}
  LPNSP_ROUTINE = ^NSP_ROUTINE;
  {$EXTERNALSYM LPNSP_ROUTINE}
  TNspRoutines = NSP_ROUTINE;
  PNspRoutines = LPNSP_ROUTINE;

(*
 * Startup procedures.
 *)

//function NSPStartup(const lpProviderId: TGUID; lpnspRoutines:  LPNSP_ROUTINE): Integer; stdcall;
//{$EXTERNALSYM NSPStartup}

type
  LPNSPSTARTUP = function (const lpProviderId: TGUID; lpnspRoutines:  LPNSP_ROUTINE): Integer; stdcall;
  {$EXTERNALSYM LPNSPSTARTUP}
  TNspStartup = LPNSPSTARTUP;

implementation

const
  ws2_32 = 'ws2_32.dll';
  qosname = 'qosname.dll';


{$IFDEF DYNAMIC_LINK}
var
  _WSCEnumProtocols: Pointer;

function WSCEnumProtocols;
begin
  GetProcedureAddress(_WSCEnumProtocols, ws2_32, 'WSCEnumProtocols');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSCEnumProtocols]
  end;
end;
{$ELSE}
function WSCEnumProtocols; external ws2_32 name 'WSCEnumProtocols';
{$ENDIF DYNAMIC_LINK}
{$IFDEF _WIN64}

{$IFDEF DYNAMIC_LINK}
var
  _WSCEnumProtocols32: Pointer;

function WSCEnumProtocols32;
begin
  GetProcedureAddress(_WSCEnumProtocols32, ws2_32, 'WSCEnumProtocols32');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSCEnumProtocols32]
  end;
end;
{$ELSE}
function WSCEnumProtocols32; external ws2_32 name 'WSCEnumProtocols32';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _WSCDeinstallProvider: Pointer;

function WSCDeinstallProvider;
begin
  GetProcedureAddress(_WSCDeinstallProvider, ws2_32, 'WSCDeinstallProvider');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSCDeinstallProvider]
  end;
end;
{$ELSE}
function WSCDeinstallProvider; external ws2_32 name 'WSCDeinstallProvider';
{$ENDIF DYNAMIC_LINK}
{$IFDEF _WIN64}

{$IFDEF DYNAMIC_LINK}
var
  _WSCDeinstallProvider32: Pointer;

function WSCDeinstallProvider32;
begin
  GetProcedureAddress(_WSCDeinstallProvider32, ws2_32, 'WSCDeinstallProvider32');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSCDeinstallProvider32]
  end;
end;
{$ELSE}
function WSCDeinstallProvider32; external ws2_32 name 'WSCDeinstallProvider32';
{$ENDIF DYNAMIC_LINK}
{$ENDIF _WIN64}

{$IFDEF DYNAMIC_LINK}
var
  _WSCInstallProvider: Pointer;

function WSCInstallProvider;
begin
  GetProcedureAddress(_WSCInstallProvider, ws2_32, 'WSCInstallProvider');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSCInstallProvider]
  end;
end;
{$ELSE}
function WSCInstallProvider; external ws2_32 name 'WSCInstallProvider';
{$ENDIF DYNAMIC_LINK}
{$IFDEF _WIN64}

{$IFDEF DYNAMIC_LINK}
var
  _WSCInstallProvider64_32: Pointer;

function WSCInstallProvider64_32;
begin
  GetProcedureAddress(_WSCInstallProvider64_32, ws2_32, 'WSCInstallProvider64_32');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSCInstallProvider64_32]
  end;
end;
{$ELSE}
function WSCInstallProvider64_32; external ws2_32 name 'WSCInstallProvider64_32';
{$ENDIF DYNAMIC_LINK}
{$ENDIF _WIN64}

{$IFDEF DYNAMIC_LINK}
var
  _WSCGetProviderPath: Pointer;

function WSCGetProviderPath;
begin
  GetProcedureAddress(_WSCGetProviderPath, ws2_32, 'WSCGetProviderPath');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSCGetProviderPath]
  end;
end;
{$ELSE}
function WSCGetProviderPath; external ws2_32 name 'WSCGetProviderPath';
{$ENDIF DYNAMIC_LINK}
{$IFDEF _WIN64}

{$IFDEF DYNAMIC_LINK}
var
  _WSCGetProviderPath32: Pointer;

function WSCGetProviderPath32;
begin
  GetProcedureAddress(_WSCGetProviderPath32, ws2_32, 'WSCGetProviderPath32');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSCGetProviderPath32]
  end;
end;
{$ELSE}
function WSCGetProviderPath32; external ws2_32 name 'WSCGetProviderPath32';
{$ENDIF DYNAMIC_LINK}
{$ENDIF _WIN64}

{$IFDEF DYNAMIC_LINK}
var
  _WSCUpdateProvider: Pointer;

function WSCUpdateProvider;
begin
  GetProcedureAddress(_WSCUpdateProvider, ws2_32, 'WSCUpdateProvider');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSCUpdateProvider]
  end;
end;
{$ELSE}
function WSCUpdateProvider; external ws2_32 name 'WSCUpdateProvider';
{$ENDIF DYNAMIC_LINK}
{$IFDEF _WIN64}

{$IFDEF DYNAMIC_LINK}
var
  _WSCUpdateProvider32: Pointer;

function WSCUpdateProvider32;
begin
  GetProcedureAddress(_WSCUpdateProvider32, ws2_32, 'WSCUpdateProvider32');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSCUpdateProvider32]
  end;
end;
{$ELSE}
function WSCUpdateProvider32; external ws2_32 name 'WSCUpdateProvider32';
{$ENDIF DYNAMIC_LINK}
{$ENDIF _WIN64}

{$IFDEF DYNAMIC_LINK}
var
  _WSCInstallQOSTemplate: Pointer;

function WSCInstallQOSTemplate;
begin
  GetProcedureAddress(_WSCInstallQOSTemplate, JwaWs2spi.qosname, 'WSCInstallQOSTemplate');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSCInstallQOSTemplate]
  end;
end;
{$ELSE}
function WSCInstallQOSTemplate; external qosname name 'WSCInstallQOSTemplate';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSCRemoveQOSTemplate: Pointer;

function WSCRemoveQOSTemplate;
begin
  GetProcedureAddress(_WSCRemoveQOSTemplate, JwaWs2spi.qosname, 'WSCRemoveQOSTemplate');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSCRemoveQOSTemplate]
  end;
end;
{$ELSE}
function WSCRemoveQOSTemplate; external qosname name 'WSCRemoveQOSTemplate';
{$ENDIF DYNAMIC_LINK}
{$IFDEF _WIN64}

{$IFDEF DYNAMIC_LINK}
var
  _WSCEnumNameSpaceProviders32: Pointer;

function WSCEnumNameSpaceProviders32;
begin
  GetProcedureAddress(_WSCEnumNameSpaceProviders32, ws2_32, 'WSCEnumNameSpaceProviders32');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSCEnumNameSpaceProviders32]
  end;
end;
{$ELSE}
function WSCEnumNameSpaceProviders32; external ws2_32 name 'WSCEnumNameSpaceProviders32';
{$ENDIF DYNAMIC_LINK}
{$ENDIF _WIN64}

{$IFDEF DYNAMIC_LINK}
var
  _WSCInstallNameSpace: Pointer;

function WSCInstallNameSpace;
begin
  GetProcedureAddress(_WSCInstallNameSpace, ws2_32, 'WSCInstallNameSpace');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSCInstallNameSpace]
  end;
end;
{$ELSE}
function WSCInstallNameSpace; external ws2_32 name 'WSCInstallNameSpace';
{$ENDIF DYNAMIC_LINK}
{$IFDEF _WIN64}

{$IFDEF DYNAMIC_LINK}
var
  _WSCInstallNameSpace32: Pointer;

function WSCInstallNameSpace32;
begin
  GetProcedureAddress(_WSCInstallNameSpace32, ws2_32, 'WSCInstallNameSpace32');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSCInstallNameSpace32]
  end;
end;
{$ELSE}
function WSCInstallNameSpace32; external ws2_32 name 'WSCInstallNameSpace32';
{$ENDIF DYNAMIC_LINK}
{$ENDIF _WIN64}

{$IFDEF DYNAMIC_LINK}
var
  _WSCUnInstallNameSpace: Pointer;

function WSCUnInstallNameSpace;
begin
  GetProcedureAddress(_WSCUnInstallNameSpace, ws2_32, 'WSCUnInstallNameSpace');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSCUnInstallNameSpace]
  end;
end;
{$ELSE}
function WSCUnInstallNameSpace; external ws2_32 name 'WSCUnInstallNameSpace';
{$ENDIF DYNAMIC_LINK}
{$IFDEF _WIN64}

{$IFDEF DYNAMIC_LINK}
var
  _WSCUnInstallNameSpace32: Pointer;

function WSCUnInstallNameSpace32;
begin
  GetProcedureAddress(_WSCUnInstallNameSpace32, ws2_32, 'WSCUnInstallNameSpace32');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSCUnInstallNameSpace32]
  end;
end;
{$ELSE}
function WSCUnInstallNameSpace32; external ws2_32 name 'WSCUnInstallNameSpace32';
{$ENDIF DYNAMIC_LINK}
{$ENDIF _WIN64}

{$IFDEF DYNAMIC_LINK}
var
  _WSCEnableNSProvider: Pointer;

function WSCEnableNSProvider;
begin
  GetProcedureAddress(_WSCEnableNSProvider, ws2_32, 'WSCEnableNSProvider');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSCEnableNSProvider]
  end;
end;
{$ELSE}
function WSCEnableNSProvider; external ws2_32 name 'WSCEnableNSProvider';
{$ENDIF DYNAMIC_LINK}
{$IFDEF _WIN64}

{$IFDEF DYNAMIC_LINK}
var
  _WSCEnableNSProvider32: Pointer;

function WSCEnableNSProvider32;
begin
  GetProcedureAddress(_WSCEnableNSProvider32, ws2_32, 'WSCEnableNSProvider32');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSCEnableNSProvider32]
  end;
end;
{$ELSE}
function WSCEnableNSProvider32; external ws2_32 name 'WSCEnableNSProvider32';
{$ENDIF DYNAMIC_LINK}
{$ENDIF _WIN64}

end.
