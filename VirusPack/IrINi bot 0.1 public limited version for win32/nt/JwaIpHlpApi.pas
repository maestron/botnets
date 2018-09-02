{******************************************************************************}
{                                                       	               }
{ Internet Protocol Helper API interface Unit for Object Pascal                }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: iphlpapi.h, released August 2000. The original Pascal  }
{ code is: IpHlpApi.pas, released September 2000. The initial developer of the }
{ Pascal code is Marcel van Brakel (brakelm@chello.nl).                        }
{                                                                              }
{ Portions created by Marcel van Brakel are Copyright (C) 1999-2001            }
{ Marcel van Brakel. All Rights Reserved.                                      }
{ 								               }
{ Contributor(s): John C. Penman (jcp@craiglockhart.com)                       }
{                 Vladimir Vassiliev (voldemarv@hotpop.com)                    }
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

unit JwaIpHlpApi;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "iphlpapi.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaIpExport, JwaIpRtrMib, JwaIpTypes, JwaWinType, JwaWinBase, JwaWinSock;

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// IPRTRMIB.H has the definitions of the strcutures used to set and get     //
// information                                                              //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

// #include <iprtrmib.h>
// #include <ipexport.h>
// #include <iptypes.h>

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// The GetXXXTable APIs take a buffer and a size of buffer.  If the buffer  //
// is not large enough, the APIs return ERROR_INSUFFICIENT_BUFFER  and      //
// *pdwSize is the required buffer size                                     //
// The bOrder is a BOOLEAN, which if TRUE sorts the table according to      //
// MIB-II (RFC XXXX)                                                        //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Retrieves the number of interfaces in the system. These include LAN and  //
// WAN interfaces                                                           //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

function GetNumberOfInterfaces(var pdwNumIf: DWORD): DWORD; stdcall;
{$EXTERNALSYM GetNumberOfInterfaces}

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Gets the MIB-II ifEntry                                                  //
// The dwIndex field of the MIB_IFROW should be set to the index of the     //
// interface being queried                                                  //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

function GetIfEntry(pIfRow: PMIB_IFROW): DWORD; stdcall;
{$EXTERNALSYM GetIfEntry}

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Gets the MIB-II IfTable                                                  //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

function GetIfTable(pIfTable: PMIB_IFTABLE; var pdwSize: ULONG; bOrder: BOOL): DWORD; stdcall;
{$EXTERNALSYM GetIfTable}

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Gets the Interface to IP Address mapping                                 //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

function GetIpAddrTable(pIpAddrTable: PMIB_IPADDRTABLE; var pdwSize: ULONG; bOrder: BOOL): DWORD; stdcall;
{$EXTERNALSYM GetIpAddrTable}

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Gets the current IP Address to Physical Address (ARP) mapping            //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

function GetIpNetTable(pIpNetTable: PMIB_IPNETTABLE; var pdwSize: ULONG; bOrder: BOOL): DWORD; stdcall;
{$EXTERNALSYM GetIpNetTable}

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Gets the IP Routing Table  (RFX XXXX)                                    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

function GetIpForwardTable(pIpForwardTable: PMIB_IPFORWARDTABLE; var pdwSize: ULONG;
  bOrder: BOOL): DWORD; stdcall;
{$EXTERNALSYM GetIpForwardTable}

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Gets TCP Connection/UDP Listener Table                                   //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

function GetTcpTable(pTcpTable: PMIB_TCPTABLE; var pdwSize: DWORD; bOrder: BOOL): DWORD; stdcall;
{$EXTERNALSYM GetTcpTable}

function GetUdpTable(pUdpTable: PMIB_UDPTABLE; var pdwSize: DWORD; bOrder: BOOL): DWORD; stdcall;
{$EXTERNALSYM GetUdpTable}

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Gets IP/ICMP/TCP/UDP Statistics                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

function GetIpStatistics(var pStats: MIB_IPSTATS): DWORD; stdcall;
{$EXTERNALSYM GetIpStatistics}

function GetIpStatisticsEx(pStats: PMIB_IPSTATS; dwFamily: DWORD): DWORD; stdcall;
{$EXTERNALSYM GetIpStatisticsEx}

function GetIcmpStatistics(var pStats: MIB_ICMP): DWORD; stdcall;
{$EXTERNALSYM GetIcmpStatistics}

function GetIcmpStatisticsEx(pStats: PMIB_ICMP_EX; dwFamily: DWORD): DWORD; stdcall;
{$EXTERNALSYM GetIcmpStatisticsEx}

function GetTcpStatistics(var pStats: MIB_TCPSTATS): DWORD; stdcall;
{$EXTERNALSYM GetTcpStatistics}

function GetTcpStatisticsEx(pStats: PMIB_TCPSTATS; dwFamily: DWORD): DWORD; stdcall;
{$EXTERNALSYM GetTcpStatisticsEx}

function GetUdpStatistics(var pStats: MIB_UDPSTATS): DWORD; stdcall;
{$EXTERNALSYM GetUdpStatistics}

function GetUdpStatisticsEx(pStats: PMIB_UDPSTATS; dwFamily: DWORD): DWORD; stdcall;
{$EXTERNALSYM GetUdpStatisticsEx}

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Used to set the ifAdminStatus on an interface.  The only fields of the   //
// MIB_IFROW that are relevant are the dwIndex (index of the interface      //
// whose status needs to be set) and the dwAdminStatus which can be either  //
// MIB_IF_ADMIN_STATUS_UP or MIB_IF_ADMIN_STATUS_DOWN                       //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

function SetIfEntry(const pIfRow: MIB_IFROW): DWORD; stdcall;
{$EXTERNALSYM SetIfEntry}

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Used to create, modify or delete a route.  In all cases the              //
// dwForwardIfIndex, dwForwardDest, dwForwardMask, dwForwardNextHop and     //
// dwForwardPolicy MUST BE SPECIFIED. Currently dwForwardPolicy is unused   //
// and MUST BE 0.                                                           //
// For a set, the complete MIB_IPFORWARDROW structure must be specified     //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

function CreateIpForwardEntry(const pRoute: MIB_IPFORWARDROW): DWORD; stdcall;
{$EXTERNALSYM CreateIpForwardEntry}

function SetIpForwardEntry(const pRoute: MIB_IPFORWARDROW): DWORD; stdcall;
{$EXTERNALSYM SetIpForwardEntry}

function DeleteIpForwardEntry(const pRoute: MIB_IPFORWARDROW): DWORD; stdcall;
{$EXTERNALSYM DeleteIpForwardEntry}

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Used to set the ipForwarding to ON or OFF (currently only ON->OFF is     //
// allowed) and to set the defaultTTL.  If only one of the fields needs to  //
// be modified and the other needs to be the same as before the other field //
// needs to be set to MIB_USE_CURRENT_TTL or MIB_USE_CURRENT_FORWARDING as  //
// the case may be                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

function SetIpStatistics(const pIpStats: MIB_IPSTATS): DWORD; stdcall;
{$EXTERNALSYM SetIpStatistics}

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Used to set the defaultTTL.                                              //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

function SetIpTTL(nTTL: UINT): DWORD; stdcall;
{$EXTERNALSYM SetIpTTL}

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Used to create, modify or delete an ARP entry.  In all cases the dwIndex //
// dwAddr field MUST BE SPECIFIED.                                          //
// For a set, the complete MIB_IPNETROW structure must be specified         //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

function CreateIpNetEntry(const pArpEntry: MIB_IPNETROW): DWORD; stdcall;
{$EXTERNALSYM CreateIpNetEntry}

function SetIpNetEntry(const pArpEntry: MIB_IPNETROW): DWORD; stdcall;
{$EXTERNALSYM SetIpNetEntry}

function DeleteIpNetEntry(const pArpEntry: MIB_IPNETROW): DWORD; stdcall;
{$EXTERNALSYM DeleteIpNetEntry}

function FlushIpNetTable(dwIfIndex: DWORD): DWORD; stdcall;
{$EXTERNALSYM FlushIpNetTable}

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Used to create or delete a Proxy ARP entry. The dwIndex is the index of  //
// the interface on which to PARP for the dwAddress.  If the interface is   //
// of a type that doesnt support ARP, e.g. PPP, then the call will fail     //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

function CreateProxyArpEntry(dwAddress, dwMask, dwIfIndex: DWORD): DWORD; stdcall;
{$EXTERNALSYM CreateProxyArpEntry}

function DeleteProxyArpEntry(dwAddress, dwMask, dwIfIndex: DWORD): DWORD; stdcall;
{$EXTERNALSYM DeleteProxyArpEntry}

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Used to set the state of a TCP Connection. The only state that it can be //
// set to is MIB_TCP_STATE_DELETE_TCB.  The complete MIB_TCPROW structure   //
// MUST BE SPECIFIED                                                        //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

function SetTcpEntry(const pTcpRow: MIB_TCPROW): DWORD; stdcall;
{$EXTERNALSYM SetTcpEntry}

function GetInterfaceInfo(pIfTable: PIP_INTERFACE_INFO; var dwOutBufLen: ULONG): DWORD; stdcall;
{$EXTERNALSYM GetInterfaceInfo}

function GetUniDirectionalAdapterInfo(pIPIfInfo: PIP_UNIDIRECTIONAL_ADAPTER_ADDRESS;
  var dwOutBufLen: ULONG): DWORD; stdcall;
{$EXTERNALSYM GetUniDirectionalAdapterInfo(OUT PIP_UNIDIRECTIONAL_ADAPTER_ADDRESS pIPIfInfo}

function NhpAllocateAndGetInterfaceInfoFromStack(out ppTable: PIP_INTERFACE_NAME_INFO;
  pdwCount: PDWORD; bOrder: BOOL; hHeap: HANDLE; dwFlags: DWORD): DWORD; stdcall;
{$EXTERNALSYM NhpAllocateAndGetInterfaceInfoFromStack}

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Gets the "best" outgoing interface for the specified destination address //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

function GetBestInterface(dwDestAddr: IPAddr; var pdwBestIfIndex: DWORD): DWORD; stdcall;
{$EXTERNALSYM GetBestInterface}

function GetBestInterfaceEx(pDestAddr: PSockAddr; var pdwBestIfIndex: DWORD): DWORD; stdcall;
{$EXTERNALSYM GetBestInterfaceEx}

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Gets the best (longest matching prefix) route for the given destination  //
// If the source address is also specified (i.e. is not 0x00000000), and    //
// there are multiple "best" routes to the given destination, the returned  //
// route will be one that goes out over the interface which has an address  //
// that matches the source address                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

function GetBestRoute(dwDestAddr, dwSourceAddr: DWORD; pBestRoute: PMIB_IPFORWARDROW): DWORD; stdcall;
{$EXTERNALSYM GetBestRoute}

function NotifyAddrChange(var Handle: THandle; overlapped: POVERLAPPED): DWORD; stdcall;
{$EXTERNALSYM NotifyAddrChange}

function NotifyRouteChange(var Handle: THandle; overlapped: POVERLAPPED): DWORD; stdcall;
{$EXTERNALSYM NotifyRouteChange}

function CancelIPChangeNotify(notifyOverlapped: LPOVERLAPPED): BOOL; stdcall;
{$EXTERNALSYM CancelIPChangeNotify}

function GetAdapterIndex(AdapterName: LPWSTR; var IfIndex: ULONG): DWORD; stdcall;
{$EXTERNALSYM GetAdapterIndex}

function AddIPAddress(Address: IPAddr; IpMask: IPMask; IfIndex: DWORD;
  var NTEContext, NTEInstance: ULONG): DWORD; stdcall;
{$EXTERNALSYM AddIPAddress}

function DeleteIPAddress(NTEContext: ULONG): DWORD; stdcall;
{$EXTERNALSYM DeleteIPAddress}

function GetNetworkParams(pFixedInfo: PFIXED_INFO; var pOutBufLen: ULONG): DWORD; stdcall;
{$EXTERNALSYM GetNetworkParams}

function GetAdaptersInfo(pAdapterInfo: PIP_ADAPTER_INFO; var pOutBufLen: ULONG): DWORD; stdcall;
{$EXTERNALSYM GetAdaptersInfo}

function GetAdapterOrderMap: PIP_ADAPTER_ORDER_MAP; stdcall;
{$EXTERNALSYM GetAdapterOrderMap}

//
// The following functions require Winsock2.
//

function GetAdaptersAddresses(Family: ULONG; Flags: DWORD; Reserved: PVOID;
  pAdapterAddresses: PIP_ADAPTER_ADDRESSES; pOutBufLen: PULONG): DWORD; stdcall;
{$EXTERNALSYM GetAdaptersAddresses}

function GetPerAdapterInfo(IfIndex: ULONG; pPerAdapterInfo: PIP_PER_ADAPTER_INFO;
  var pOutBufLen: ULONG): DWORD; stdcall;
{$EXTERNALSYM GetPerAdapterInfo}

function IpReleaseAddress(const AdapterInfo: IP_ADAPTER_INDEX_MAP): DWORD; stdcall;
{$EXTERNALSYM IpReleaseAddress}

function IpRenewAddress(const AdapterInfo: IP_ADAPTER_INDEX_MAP): DWORD; stdcall;
{$EXTERNALSYM IpRenewAddress}

function SendARP(const DestIP, SrcIP: IPAddr; pMacAddr: PULONG; var PhyAddrLen: ULONG): DWORD; stdcall;
{$EXTERNALSYM SendARP}

function GetRTTAndHopCount(DestIpAddress: IPAddr; var HopCount: ULONG;
  MaxHops: ULONG; var RTT: ULONG): BOOL; stdcall;
{$EXTERNALSYM GetRTTAndHopCount}

function GetFriendlyIfIndex(IfIndex: DWORD): DWORD; stdcall;
{$EXTERNALSYM GetFriendlyIfIndex}

function EnableRouter(var pHandle: THandle; pOverlapped: POVERLAPPED): DWORD; stdcall;
{$EXTERNALSYM EnableRouter}

function UnenableRouter(pOverlapped: POVERLAPPED; lpdwEnableCount: LPDWORD): DWORD; stdcall;
{$EXTERNALSYM UnenableRouter}

function DisableMediaSense(var pHandle: HANDLE; pOverLapped: POVERLAPPED): DWORD; stdcall;
{$EXTERNALSYM DisableMediaSense}

function RestoreMediaSense(pOverlapped: POVERLAPPED; lpdwEnableCount: LPDWORD): DWORD; stdcall;
{$EXTERNALSYM RestoreMediaSense}

function GetIpErrorString(ErrorCode: IP_STATUS; Buffer: PWCHAR; var Size: DWORD): DWORD; stdcall;
{$EXTERNALSYM GetIpErrorString}

implementation

const
  iphlpapilib = 'iphlpapi.dll';


{$IFDEF DYNAMIC_LINK}
var
  _GetNumberOfInterfaces: Pointer;

function GetNumberOfInterfaces;
begin
  GetProcedureAddress(_GetNumberOfInterfaces, iphlpapilib, 'GetNumberOfInterfaces');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetNumberOfInterfaces]
  end;
end;
{$ELSE}
function GetNumberOfInterfaces; external iphlpapilib name 'GetNumberOfInterfaces';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetIfEntry: Pointer;

function GetIfEntry;
begin
  GetProcedureAddress(_GetIfEntry, iphlpapilib, 'GetIfEntry');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetIfEntry]
  end;
end;
{$ELSE}
function GetIfEntry; external iphlpapilib name 'GetIfEntry';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetIfTable: Pointer;

function GetIfTable;
begin
  GetProcedureAddress(_GetIfTable, iphlpapilib, 'GetIfTable');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetIfTable]
  end;
end;
{$ELSE}
function GetIfTable; external iphlpapilib name 'GetIfTable';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetIpAddrTable: Pointer;

function GetIpAddrTable;
begin
  GetProcedureAddress(_GetIpAddrTable, iphlpapilib, 'GetIpAddrTable');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetIpAddrTable]
  end;
end;
{$ELSE}
function GetIpAddrTable; external iphlpapilib name 'GetIpAddrTable';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetIpNetTable: Pointer;

function GetIpNetTable;
begin
  GetProcedureAddress(_GetIpNetTable, iphlpapilib, 'GetIpNetTable');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetIpNetTable]
  end;
end;
{$ELSE}
function GetIpNetTable; external iphlpapilib name 'GetIpNetTable';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetIpForwardTable: Pointer;

function GetIpForwardTable;
begin
  GetProcedureAddress(_GetIpForwardTable, iphlpapilib, 'GetIpForwardTable');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetIpForwardTable]
  end;
end;
{$ELSE}
function GetIpForwardTable; external iphlpapilib name 'GetIpForwardTable';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetTcpTable: Pointer;

function GetTcpTable;
begin
  GetProcedureAddress(_GetTcpTable, iphlpapilib, 'GetTcpTable');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetTcpTable]
  end;
end;
{$ELSE}
function GetTcpTable; external iphlpapilib name 'GetTcpTable';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetUdpTable: Pointer;

function GetUdpTable;
begin
  GetProcedureAddress(_GetUdpTable, iphlpapilib, 'GetUdpTable');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetUdpTable]
  end;
end;
{$ELSE}
function GetUdpTable; external iphlpapilib name 'GetUdpTable';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetIpStatistics: Pointer;

function GetIpStatistics;
begin
  GetProcedureAddress(_GetIpStatistics, iphlpapilib, 'GetIpStatistics');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetIpStatistics]
  end;
end;
{$ELSE}
function GetIpStatistics; external iphlpapilib name 'GetIpStatistics';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetIpStatisticsEx: Pointer;

function GetIpStatisticsEx;
begin
  GetProcedureAddress(_GetIpStatisticsEx, iphlpapilib, 'GetIpStatisticsEx');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetIpStatisticsEx]
  end;
end;
{$ELSE}
function GetIpStatisticsEx; external iphlpapilib name 'GetIpStatisticsEx';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetIcmpStatistics: Pointer;

function GetIcmpStatistics;
begin
  GetProcedureAddress(_GetIcmpStatistics, iphlpapilib, 'GetIcmpStatistics');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetIcmpStatistics]
  end;
end;
{$ELSE}
function GetIcmpStatistics; external iphlpapilib name 'GetIcmpStatistics';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetIcmpStatisticsEx: Pointer;

function GetIcmpStatisticsEx;
begin
  GetProcedureAddress(_GetIcmpStatisticsEx, iphlpapilib, 'GetIcmpStatisticsEx');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetIcmpStatisticsEx]
  end;
end;
{$ELSE}
function GetIcmpStatisticsEx; external iphlpapilib name 'GetIcmpStatisticsEx';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetTcpStatistics: Pointer;

function GetTcpStatistics;
begin
  GetProcedureAddress(_GetTcpStatistics, iphlpapilib, 'GetTcpStatistics');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetTcpStatistics]
  end;
end;
{$ELSE}
function GetTcpStatistics; external iphlpapilib name 'GetTcpStatistics';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetTcpStatisticsEx: Pointer;

function GetTcpStatisticsEx;
begin
  GetProcedureAddress(_GetTcpStatisticsEx, iphlpapilib, 'GetTcpStatisticsEx');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetTcpStatisticsEx]
  end;
end;
{$ELSE}
function GetTcpStatisticsEx; external iphlpapilib name 'GetTcpStatisticsEx';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetUdpStatistics: Pointer;

function GetUdpStatistics;
begin
  GetProcedureAddress(_GetUdpStatistics, iphlpapilib, 'GetUdpStatistics');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetUdpStatistics]
  end;
end;
{$ELSE}
function GetUdpStatistics; external iphlpapilib name 'GetUdpStatistics';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetUdpStatisticsEx: Pointer;

function GetUdpStatisticsEx;
begin
  GetProcedureAddress(_GetUdpStatisticsEx, iphlpapilib, 'GetUdpStatisticsEx');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetUdpStatisticsEx]
  end;
end;
{$ELSE}
function GetUdpStatisticsEx; external iphlpapilib name 'GetUdpStatisticsEx';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SetIfEntry: Pointer;

function SetIfEntry;
begin
  GetProcedureAddress(_SetIfEntry, iphlpapilib, 'SetIfEntry');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SetIfEntry]
  end;
end;
{$ELSE}
function SetIfEntry; external iphlpapilib name 'SetIfEntry';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CreateIpForwardEntry: Pointer;

function CreateIpForwardEntry;
begin
  GetProcedureAddress(_CreateIpForwardEntry, iphlpapilib, 'CreateIpForwardEntry');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CreateIpForwardEntry]
  end;
end;
{$ELSE}
function CreateIpForwardEntry; external iphlpapilib name 'CreateIpForwardEntry';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SetIpForwardEntry: Pointer;

function SetIpForwardEntry;
begin
  GetProcedureAddress(_SetIpForwardEntry, iphlpapilib, 'SetIpForwardEntry');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SetIpForwardEntry]
  end;
end;
{$ELSE}
function SetIpForwardEntry; external iphlpapilib name 'SetIpForwardEntry';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DeleteIpForwardEntry: Pointer;

function DeleteIpForwardEntry;
begin
  GetProcedureAddress(_DeleteIpForwardEntry, iphlpapilib, 'DeleteIpForwardEntry');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DeleteIpForwardEntry]
  end;
end;
{$ELSE}
function DeleteIpForwardEntry; external iphlpapilib name 'DeleteIpForwardEntry';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SetIpStatistics: Pointer;

function SetIpStatistics;
begin
  GetProcedureAddress(_SetIpStatistics, iphlpapilib, 'SetIpStatistics');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SetIpStatistics]
  end;
end;
{$ELSE}
function SetIpStatistics; external iphlpapilib name 'SetIpStatistics';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SetIpTTL: Pointer;

function SetIpTTL;
begin
  GetProcedureAddress(_SetIpTTL, iphlpapilib, 'SetIpTTL');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SetIpTTL]
  end;
end;
{$ELSE}
function SetIpTTL; external iphlpapilib name 'SetIpTTL';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CreateIpNetEntry: Pointer;

function CreateIpNetEntry;
begin
  GetProcedureAddress(_CreateIpNetEntry, iphlpapilib, 'CreateIpNetEntry');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CreateIpNetEntry]
  end;
end;
{$ELSE}
function CreateIpNetEntry; external iphlpapilib name 'CreateIpNetEntry';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SetIpNetEntry: Pointer;

function SetIpNetEntry;
begin
  GetProcedureAddress(_SetIpNetEntry, iphlpapilib, 'SetIpNetEntry');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SetIpNetEntry]
  end;
end;
{$ELSE}
function SetIpNetEntry; external iphlpapilib name 'SetIpNetEntry';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DeleteIpNetEntry: Pointer;

function DeleteIpNetEntry;
begin
  GetProcedureAddress(_DeleteIpNetEntry, iphlpapilib, 'DeleteIpNetEntry');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DeleteIpNetEntry]
  end;
end;
{$ELSE}
function DeleteIpNetEntry; external iphlpapilib name 'DeleteIpNetEntry';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _FlushIpNetTable: Pointer;

function FlushIpNetTable;
begin
  GetProcedureAddress(_FlushIpNetTable, iphlpapilib, 'FlushIpNetTable');
  asm
    mov esp, ebp
    pop ebp
    jmp [_FlushIpNetTable]
  end;
end;
{$ELSE}
function FlushIpNetTable; external iphlpapilib name 'FlushIpNetTable';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CreateProxyArpEntry: Pointer;

function CreateProxyArpEntry;
begin
  GetProcedureAddress(_CreateProxyArpEntry, iphlpapilib, 'CreateProxyArpEntry');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CreateProxyArpEntry]
  end;
end;
{$ELSE}
function CreateProxyArpEntry; external iphlpapilib name 'CreateProxyArpEntry';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DeleteProxyArpEntry: Pointer;

function DeleteProxyArpEntry;
begin
  GetProcedureAddress(_DeleteProxyArpEntry, iphlpapilib, 'DeleteProxyArpEntry');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DeleteProxyArpEntry]
  end;
end;
{$ELSE}
function DeleteProxyArpEntry; external iphlpapilib name 'DeleteProxyArpEntry';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SetTcpEntry: Pointer;

function SetTcpEntry;
begin
  GetProcedureAddress(_SetTcpEntry, iphlpapilib, 'SetTcpEntry');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SetTcpEntry]
  end;
end;
{$ELSE}
function SetTcpEntry; external iphlpapilib name 'SetTcpEntry';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetInterfaceInfo: Pointer;

function GetInterfaceInfo;
begin
  GetProcedureAddress(_GetInterfaceInfo, iphlpapilib, 'GetInterfaceInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetInterfaceInfo]
  end;
end;
{$ELSE}
function GetInterfaceInfo; external iphlpapilib name 'GetInterfaceInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetUniDirectionalAdapterInfo: Pointer;

function GetUniDirectionalAdapterInfo;
begin
  GetProcedureAddress(_GetUniDirectionalAdapterInfo, iphlpapilib, 'GetUniDirectionalAdapterInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetUniDirectionalAdapterInfo]
  end;
end;
{$ELSE}
function GetUniDirectionalAdapterInfo; external iphlpapilib name 'GetUniDirectionalAdapterInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NhpAllocateAndGetInterfaceInfoFromStack: Pointer;

function NhpAllocateAndGetInterfaceInfoFromStack;
begin
  GetProcedureAddress(_NhpAllocateAndGetInterfaceInfoFromStack, iphlpapilib, 'NhpAllocateAndGetInterfaceInfoFromStack');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NhpAllocateAndGetInterfaceInfoFromStack]
  end;
end;
{$ELSE}
function NhpAllocateAndGetInterfaceInfoFromStack; external iphlpapilib name 'NhpAllocateAndGetInterfaceInfoFromStack';
{$ENDIF DYNAMIC_LINK}



{$IFDEF DYNAMIC_LINK}
var
  _GetBestInterface: Pointer;

function GetBestInterface;
begin
  GetProcedureAddress(_GetBestInterface, iphlpapilib, 'GetBestInterface');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetBestInterface]
  end;
end;
{$ELSE}
function GetBestInterface; external iphlpapilib name 'GetBestInterface';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetBestInterfaceEx: Pointer;

function GetBestInterfaceEx;
begin
  GetProcedureAddress(_GetBestInterfaceEx, iphlpapilib, 'GetBestInterfaceEx');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetBestInterfaceEx]
  end;
end;
{$ELSE}
function GetBestInterfaceEx; external iphlpapilib name 'GetBestInterfaceEx';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetBestRoute: Pointer;

function GetBestRoute;
begin
  GetProcedureAddress(_GetBestRoute, iphlpapilib, 'GetBestRoute');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetBestRoute]
  end;
end;
{$ELSE}
function GetBestRoute; external iphlpapilib name 'GetBestRoute';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NotifyAddrChange: Pointer;

function NotifyAddrChange;
begin
  GetProcedureAddress(_NotifyAddrChange, iphlpapilib, 'NotifyAddrChange');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NotifyAddrChange]
  end;
end;
{$ELSE}
function NotifyAddrChange; external iphlpapilib name 'NotifyAddrChange';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NotifyRouteChange: Pointer;

function NotifyRouteChange;
begin
  GetProcedureAddress(_NotifyRouteChange, iphlpapilib, 'NotifyRouteChange');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NotifyRouteChange]
  end;
end;
{$ELSE}
function NotifyRouteChange; external iphlpapilib name 'NotifyRouteChange';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CancelIPChangeNotify: Pointer;

function CancelIPChangeNotify;
begin
  GetProcedureAddress(_CancelIPChangeNotify, iphlpapilib, 'CancelIPChangeNotify');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CancelIPChangeNotify]
  end;
end;
{$ELSE}
function CancelIPChangeNotify; external iphlpapilib name 'CancelIPChangeNotify';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetAdapterIndex: Pointer;

function GetAdapterIndex;
begin
  GetProcedureAddress(_GetAdapterIndex, iphlpapilib, 'GetAdapterIndex');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetAdapterIndex]
  end;
end;
{$ELSE}
function GetAdapterIndex; external iphlpapilib name 'GetAdapterIndex';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _AddIPAddress: Pointer;

function AddIPAddress;
begin
  GetProcedureAddress(_AddIPAddress, iphlpapilib, 'AddIPAddress');
  asm
    mov esp, ebp
    pop ebp
    jmp [_AddIPAddress]
  end;
end;
{$ELSE}
function AddIPAddress; external iphlpapilib name 'AddIPAddress';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DeleteIPAddress: Pointer;

function DeleteIPAddress;
begin
  GetProcedureAddress(_DeleteIPAddress, iphlpapilib, 'DeleteIPAddress');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DeleteIPAddress]
  end;
end;
{$ELSE}
function DeleteIPAddress; external iphlpapilib name 'DeleteIPAddress';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetNetworkParams: Pointer;

function GetNetworkParams;
begin
  GetProcedureAddress(_GetNetworkParams, iphlpapilib, 'GetNetworkParams');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetNetworkParams]
  end;
end;
{$ELSE}
function GetNetworkParams; external iphlpapilib name 'GetNetworkParams';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetAdaptersInfo: Pointer;

function GetAdaptersInfo;
begin
  GetProcedureAddress(_GetAdaptersInfo, iphlpapilib, 'GetAdaptersInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetAdaptersInfo]
  end;
end;
{$ELSE}
function GetAdaptersInfo; external iphlpapilib name 'GetAdaptersInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetAdapterOrderMap: Pointer;

function GetAdapterOrderMap;
begin
  GetProcedureAddress(_GetAdapterOrderMap, iphlpapilib, 'GetAdapterOrderMap');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetAdapterOrderMap]
  end;
end;
{$ELSE}
function GetAdapterOrderMap; external iphlpapilib name 'GetAdapterOrderMap';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetAdaptersAddresses: Pointer;

function GetAdaptersAddresses;
begin
  GetProcedureAddress(_GetAdaptersAddresses, iphlpapilib, 'GetAdaptersAddresses');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetAdaptersAddresses]
  end;
end;
{$ELSE}
function GetAdaptersAddresses; external iphlpapilib name 'GetAdaptersAddresses';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetPerAdapterInfo: Pointer;

function GetPerAdapterInfo;
begin
  GetProcedureAddress(_GetPerAdapterInfo, iphlpapilib, 'GetPerAdapterInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetPerAdapterInfo]
  end;
end;
{$ELSE}
function GetPerAdapterInfo; external iphlpapilib name 'GetPerAdapterInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _IpReleaseAddress: Pointer;

function IpReleaseAddress;
begin
  GetProcedureAddress(_IpReleaseAddress, iphlpapilib, 'IpReleaseAddress');
  asm
    mov esp, ebp
    pop ebp
    jmp [_IpReleaseAddress]
  end;
end;
{$ELSE}
function IpReleaseAddress; external iphlpapilib name 'IpReleaseAddress';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _IpRenewAddress: Pointer;

function IpRenewAddress;
begin
  GetProcedureAddress(_IpRenewAddress, iphlpapilib, 'IpRenewAddress');
  asm
    mov esp, ebp
    pop ebp
    jmp [_IpRenewAddress]
  end;
end;
{$ELSE}
function IpRenewAddress; external iphlpapilib name 'IpRenewAddress';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SendARP: Pointer;

function SendARP;
begin
  GetProcedureAddress(_SendARP, iphlpapilib, 'SendARP');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SendARP]
  end;
end;
{$ELSE}
function SendARP; external iphlpapilib name 'SendARP';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetRTTAndHopCount: Pointer;

function GetRTTAndHopCount;
begin
  GetProcedureAddress(_GetRTTAndHopCount, iphlpapilib, 'GetRTTAndHopCount');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetRTTAndHopCount]
  end;
end;
{$ELSE}
function GetRTTAndHopCount; external iphlpapilib name 'GetRTTAndHopCount';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetFriendlyIfIndex: Pointer;

function GetFriendlyIfIndex;
begin
  GetProcedureAddress(_GetFriendlyIfIndex, iphlpapilib, 'GetFriendlyIfIndex');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetFriendlyIfIndex]
  end;
end;
{$ELSE}
function GetFriendlyIfIndex; external iphlpapilib name 'GetFriendlyIfIndex';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _EnableRouter: Pointer;

function EnableRouter;
begin
  GetProcedureAddress(_EnableRouter, iphlpapilib, 'EnableRouter');
  asm
    mov esp, ebp
    pop ebp
    jmp [_EnableRouter]
  end;
end;
{$ELSE}
function EnableRouter; external iphlpapilib name 'EnableRouter';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _UnenableRouter: Pointer;

function UnenableRouter;
begin
  GetProcedureAddress(_UnenableRouter, iphlpapilib, 'UnenableRouter');
  asm
    mov esp, ebp
    pop ebp
    jmp [_UnenableRouter]
  end;
end;
{$ELSE}
function UnenableRouter; external iphlpapilib name 'UnenableRouter';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DisableMediaSense: Pointer;

function DisableMediaSense;
begin
  GetProcedureAddress(_DisableMediaSense, iphlpapilib, 'DisableMediaSense');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DisableMediaSense]
  end;
end;
{$ELSE}
function DisableMediaSense; external iphlpapilib name 'DisableMediaSense';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RestoreMediaSense: Pointer;

function RestoreMediaSense;
begin
  GetProcedureAddress(_RestoreMediaSense, iphlpapilib, 'RestoreMediaSense');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RestoreMediaSense]
  end;
end;
{$ELSE}
function RestoreMediaSense; external iphlpapilib name 'RestoreMediaSense';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetIpErrorString: Pointer;

function GetIpErrorString;
begin
  GetProcedureAddress(_GetIpErrorString, iphlpapilib, 'GetIpErrorString');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetIpErrorString]
  end;
end;
{$ELSE}
function GetIpErrorString; external iphlpapilib name 'GetIpErrorString';
{$ENDIF DYNAMIC_LINK}

end.
