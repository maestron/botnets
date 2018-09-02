{******************************************************************************}
{                                                       	               }
{ Winsock2 TCP/IP Extensions API interface Unit for Object Pascal              }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: ws2tcpip.h, released June 2000. The original Pascal    }
{ code is: WS2tcpip.pas, released December 2000. The initial developer of the  }
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

unit JwaWS2tcpip;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "ws2tcpip.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinSock2, JwaWinType;

//
//	WS2TCPIP.H - WinSock2 Extension for TCP/IP protocols
//
//	This file contains TCP/IP specific information for use
//	by WinSock2 compatible applications.
//
// Copyright (c) 1995-1999  Microsoft Corporation
//
//	To provide the backward compatibility, all the TCP/IP
//	specific definitions that were included in the WINSOCK.H
//	 file are now included in WINSOCK2.H file. WS2TCPIP.H
//	file includes only the definitions  introduced in the
//	"WinSock 2 Protocol-Specific Annex" document.
//
//	Rev 0.3	Nov 13, 1995
//      Rev 0.4	Dec 15, 1996
//

// Argument structure for IP_ADD_MEMBERSHIP and IP_DROP_MEMBERSHIP

type
  ip_mreq = record
    imr_multiaddr: in_addr;	// IP multicast address of group
    imr_interface: in_addr;	// local IP address of interface
  end;
  {$EXTERNALSYM ip_mreq}
  TIPMReq = ip_mreq;
  PIPMReq = ^ip_mreq;

// Argument structure for IP_ADD_SOURCE_MEMBERSHIP, IP_DROP_SOURCE_MEMBERSHIP,
// IP_BLOCK_SOURCE, and IP_UNBLOCK_SOURCE
//

  ip_mreq_source = record
    imr_multiaddr: in_addr; // IP multicast address of group
    imr_sourceaddr: in_addr; // IP address of source
    imr_interface: in_addr; // local IP address of interface
  end;
  {$EXTERNALSYM ip_mreq_source}
  TIpMreqSource = ip_mreq_source;
  PIpMreqSource = ^ip_mreq_source;

// Argument structure for SIO_{GET,SET}_MULTICAST_FILTER

  ip_msfilter = record
    imsf_multiaddr: in_addr; // IP multicast address of group
    imsf_interface: in_addr; // local IP address of interface
    imsf_fmode: u_long; // filter mode - INCLUDE or EXCLUDE
    imsf_numsrc: u_long; // number of sources in src_list
    imsf_slist: array [0..0] of in_addr;
  end;
  {$EXTERNALSYM ip_msfilter}
  TIpMsFilter = ip_msfilter;
  PIpMsFilter = ^ip_msfilter;

function IP_MSFILTER_SIZE(numsrc: Integer): Integer;
{$EXTERNALSYM IP_MSFILTER_SIZE(numsrc)}

const
  MCAST_INCLUDE = 0;
  {$EXTERNALSYM MCAST_INCLUDE}
  MCAST_EXCLUDE = 1;
  {$EXTERNALSYM MCAST_EXCLUDE}

// TCP/IP specific Ioctl codes

const
  SIO_GET_INTERFACE_LIST = IOC_OUT or ((4 and IOCPARM_MASK) shl 16) or ((Ord('t')) shl 8) or (127);
  {$EXTERNALSYM SIO_GET_INTERFACE_LIST}

// New IOCTL with address size independent address array

  SIO_GET_INTERFACE_LIST_EX = IOC_OUT or ((4 and IOCPARM_MASK) shl 16) or ((Ord('t')) shl 8) or (126);
  {$EXTERNALSYM SIO_GET_INTERFACE_LIST_EX}

  SIO_SET_MULTICAST_FILTER = DWORD(IOC_IN or ((SizeOf(u_long) and IOCPARM_MASK) shl 16) or (Ord('t') shl 8) or 125);
  {$EXTERNALSYM SIO_SET_MULTICAST_FILTER}
  SIO_GET_MULTICAST_FILTER = DWORD(IOC_IN or ((SizeOf(u_long) and IOCPARM_MASK) shl 16) or (Ord('t') shl 8) or 124 or IOC_IN);
  {$EXTERNALSYM SIO_GET_MULTICAST_FILTER}

// Option to use with [gs]etsockopt at the IPPROTO_IP level

const
  IP_OPTIONS         = 1;  // set/get IP options
  {$EXTERNALSYM IP_OPTIONS}
  IP_HDRINCL         = 2;  // header is included with data
  {$EXTERNALSYM IP_HDRINCL}
  IP_TOS             = 3;  // IP type of service and preced
  {$EXTERNALSYM IP_TOS}
  IP_TTL             = 4;  // IP time to live
  {$EXTERNALSYM IP_TTL}
  IP_MULTICAST_IF    = 9;  // set/get IP multicast i/f
  {$EXTERNALSYM IP_MULTICAST_IF}
  IP_MULTICAST_TTL   = 10; // set/get IP multicast ttl
  {$EXTERNALSYM IP_MULTICAST_TTL}
  IP_MULTICAST_LOOP  = 11; // set/get IP multicast loopback
  {$EXTERNALSYM IP_MULTICAST_LOOP}
  IP_ADD_MEMBERSHIP  = 12; // add an IP group membership
  {$EXTERNALSYM IP_ADD_MEMBERSHIP}
  IP_DROP_MEMBERSHIP = 13; // drop an IP group membership
  {$EXTERNALSYM IP_DROP_MEMBERSHIP}
  IP_DONTFRAGMENT    = 14; // don't fragment IP datagrams
  {$EXTERNALSYM IP_DONTFRAGMENT}
  IP_ADD_SOURCE_MEMBERSHIP  = 15; // join IP group/source
  {$EXTERNALSYM IP_ADD_SOURCE_MEMBERSHIP}
  IP_DROP_SOURCE_MEMBERSHIP = 16; // leave IP group/source
  {$EXTERNALSYM IP_DROP_SOURCE_MEMBERSHIP}
  IP_BLOCK_SOURCE           = 17; // block IP group/source
  {$EXTERNALSYM IP_BLOCK_SOURCE}
  IP_UNBLOCK_SOURCE         = 18; // unblock IP group/source
  {$EXTERNALSYM IP_UNBLOCK_SOURCE}
  IP_PKTINFO                = 19; // receive packet information for ipv4
  {$EXTERNALSYM IP_PKTINFO}

// Option to use with [gs]etsockopt at the IPPROTO_IPV6 level

  IPV6_HDRINCL         = 2; // Header is included with data
  {$EXTERNALSYM IPV6_HDRINCL}
  IPV6_UNICAST_HOPS    = 4; // Set/get IP unicast hop limit
  {$EXTERNALSYM IPV6_UNICAST_HOPS}
  IPV6_MULTICAST_IF    = 9; // Set/get IP multicast interface
  {$EXTERNALSYM IPV6_MULTICAST_IF}
  IPV6_MULTICAST_HOPS  = 10; // Set/get IP multicast ttl
  {$EXTERNALSYM IPV6_MULTICAST_HOPS}
  IPV6_MULTICAST_LOOP  = 11; // Set/get IP multicast loopback
  {$EXTERNALSYM IPV6_MULTICAST_LOOP}
  IPV6_ADD_MEMBERSHIP  = 12; // Add an IP group membership
  {$EXTERNALSYM IPV6_ADD_MEMBERSHIP}
  IPV6_DROP_MEMBERSHIP = 13; // Drop an IP group membership
  {$EXTERNALSYM IPV6_DROP_MEMBERSHIP}
  IPV6_JOIN_GROUP      = IPV6_ADD_MEMBERSHIP;
  {$EXTERNALSYM IPV6_JOIN_GROUP}
  IPV6_LEAVE_GROUP     = IPV6_DROP_MEMBERSHIP;
  {$EXTERNALSYM IPV6_LEAVE_GROUP}
  IPV6_PKTINFO         = 19; // Receive packet information for ipv6
  {$EXTERNALSYM IPV6_PKTINFO}

// Option to use with [gs]etsockopt at the IPPROTO_UDP level

  UDP_NOCHECKSUM = 1;
  {$EXTERNALSYM UDP_NOCHECKSUM}
  UDP_CHECKSUM_COVERAGE = 20; // Set/get UDP-Lite checksum coverage
  {$EXTERNALSYM UDP_CHECKSUM_COVERAGE}

// Option to use with [gs]etsockopt at the IPPROTO_TCP level

  TCP_EXPEDITED_1122 = $0002;
  {$EXTERNALSYM TCP_EXPEDITED_1122}

// IPv6 definitions

type
  in6_addr = record
    case Integer of
      0: (Byte: array [0..15] of u_char);
      1: (Word: array[0..7] of u_short);
      2: (s6_bytes: array [0..15] of u_char);
      3: (s6_addr: array [0..15] of u_char);
      4: (s6_words: array[0..7] of u_short);
  end;
  {$EXTERNALSYM in6_addr}
  TIn6Addr = in6_addr;
  PIn6Addr = ^in6_addr;

//
// Defines to match RFC 2553.
//

//#define _S6_un     u
//#define _S6_u8     Byte

// Argument structure for IPV6_JOIN_GROUP and IPV6_LEAVE_GROUP

type
  ipv6_mreq = record
    ipv6mr_multiaddr: in6_addr;  // IPv6 multicast address
    ipv6mr_interface: Cardinal;  // Interface index
  end;
  {$EXTERNALSYM ipv6_mreq}
  TIpV6MReq = ipv6_mreq;
  PIpV6MReq = ^ipv6_mreq;

type
  in_addr6 = record
    s6_addr: array [0..15] of u_char; // IPv6 address
  end;
  {$EXTERNALSYM in_addr6}
  TInAddr6 = in_addr6;
  PInAddr6 = ^in_addr6;

// Old IPv6 socket address structure (retained for sockaddr_gen definition below)

type
  sockaddr_in6_old = record
    sin6_family: short;    // AF_INET6
    sin6_port: u_short;    // Transport level port number
    sin6_flowinfo: u_long; // IPv6 flow information
    sin6_addr: in6_addr;   // IPv6 address
  end;
  {$EXTERNALSYM sockaddr_in6_old}
  TSockAddrIn6Old = sockaddr_in6_old;
  PSockAddrIn6Old = ^sockaddr_in6_old;

// IPv6 socket address structure, RFC 2553

  SOCKADDR_IN6 = record
    sin6_family: short;    // AF_INET6
    sin6_port: u_short;    // Transport level port number
    sin6_flowinfo: u_long; // IPv6 flow information
    sin6_addr: in6_addr;   // IPv6 address
    sin6_scope_id: u_long; // set of interfaces for a scope
  end;
  {$EXTERNALSYM SOCKADDR_IN6}
  PSOCKADDR_IN6 = ^SOCKADDR_IN6;
  {$EXTERNALSYM PSOCKADDR_IN6}
  LPSOCKADDR_IN6 = ^SOCKADDR_IN6;
  {$EXTERNALSYM LPSOCKADDR_IN6}
  TSockAddrIn6 = SOCKADDR_IN6;
  PSockAddrIn6 = LPSOCKADDR_IN6;

// Macro that works for both IPv4 and IPv6

function SS_PORT(ssp: Pointer): u_short;
{$EXTERNALSYM SS_PORT}

const
  IN6ADDR_ANY_INIT: in6_addr = (Word: (0, 0, 0, 0, 0, 0, 0, 0));
  {$EXTERNALSYM IN6ADDR_ANY_INIT}
  IN6ADDR_LOOPBACK_INIT: in6_addr = (Byte: (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1));
  {$EXTERNALSYM IN6ADDR_LOOPBACK_INIT}

  in6addr_any: in6_addr = (Word: (0, 0, 0, 0, 0, 0, 0, 0));
  {$EXTERNALSYM in6addr_any}
  in6addr_loopback: in6_addr = (Byte: (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1));
  {$EXTERNALSYM in6addr_loopback}

procedure IN6ADDR_SETANY(var x: TSockAddrIn6);
{$EXTERNALSYM IN6ADDR_SETANY}

procedure IN6ADDR_SETLOOPBACK(var x: TSockAddrIn6);
{$EXTERNALSYM IN6ADDR_SETLOOPBACK}

function IN6ADDR_ISANY(const x: TSockAddrIn6): Boolean;
{$EXTERNALSYM IN6ADDR_ISANY}

function IN6ADDR_ISLOOPBACK(const x: TSockAddrIn6): Boolean;
{$EXTERNALSYM IN6ADDR_ISLOOPBACK}

function IN6_ADDR_EQUAL(const a, b: in6_addr): Boolean;
{$EXTERNALSYM IN6_ADDR_EQUAL}
function IN6_IS_ADDR_UNSPECIFIED(const a: in6_addr): boolean;
{$EXTERNALSYM IN6_IS_ADDR_UNSPECIFIED}
function IN6_IS_ADDR_LOOPBACK(const a: in6_addr): Boolean;
{$EXTERNALSYM IN6_IS_ADDR_LOOPBACK}
function IN6_IS_ADDR_MULTICAST(const a: in6_addr): Boolean;
{$EXTERNALSYM IN6_IS_ADDR_MULTICAST}
function IN6_IS_ADDR_LINKLOCAL(const a: in6_addr): Boolean;
{$EXTERNALSYM IN6_IS_ADDR_LINKLOCAL}
function IN6_IS_ADDR_SITELOCAL(const a: in6_addr): Boolean;
{$EXTERNALSYM IN6_IS_ADDR_SITELOCAL}
function IN6_IS_ADDR_V4MAPPED(const a: in6_addr): Boolean;
{$EXTERNALSYM IN6_IS_ADDR_V4MAPPED}
function IN6_IS_ADDR_V4COMPAT(const a: in6_addr): Boolean;
{$EXTERNALSYM IN6_IS_ADDR_V4COMPAT}
function IN6_IS_ADDR_MC_NODELOCAL(const a: in6_addr): Boolean;
{$EXTERNALSYM IN6_IS_ADDR_MC_NODELOCAL}
function IN6_IS_ADDR_MC_LINKLOCAL(const a: in6_addr): Boolean;
{$EXTERNALSYM IN6_IS_ADDR_MC_LINKLOCAL}
function IN6_IS_ADDR_MC_SITELOCAL(const a: in6_addr): Boolean;
{$EXTERNALSYM IN6_IS_ADDR_MC_SITELOCAL}
function IN6_IS_ADDR_MC_ORGLOCAL(const a: in6_addr): Boolean;
{$EXTERNALSYM IN6_IS_ADDR_MC_ORGLOCAL}
function IN6_IS_ADDR_MC_GLOBAL(const a: in6_addr): Boolean;
{$EXTERNALSYM IN6_IS_ADDR_MC_GLOBAL}

type
  sockaddr_gen = record
    case Integer of
      0: (Address: sockaddr);
      1: (AddressIn: sockaddr_in);
      2: (AddressIn6: sockaddr_in6_old);
  end;
  {$EXTERNALSYM sockaddr_gen}
  TSockAddrGen = sockaddr_gen;
  PSockAddrGen = ^sockaddr_gen;  

// Structure to keep interface specific information

  _INTERFACE_INFO = record
    iiFlags: u_long;                  // Interface flags
    iiAddress: sockaddr_gen;          // Interface address
    iiBroadcastAddress: sockaddr_gen; // Broadcast address
    iiNetmask: sockaddr_gen;          // Network mask
  end;
  {$EXTERNALSYM _INTERFACE_INFO}
  INTERFACE_INFO = _INTERFACE_INFO;
  {$EXTERNALSYM INTERFACE_INFO}
  LPINTERFACE_INFO = ^INTERFACE_INFO;
  {$EXTERNALSYM LPINTERFACE_INFO}
  TInterfaceInfo = INTERFACE_INFO;
  PInterfaceInfo = LPINTERFACE_INFO;

// New structure that does not have dependency on the address size

  _INTERFACE_INFO_EX = record
    iiFlags: u_long;                    // Interface flags
    iiAddress: SOCKET_ADDRESS;          // Interface address
    iiBroadcastAddress: SOCKET_ADDRESS; // Broadcast address
    iiNetmask: SOCKET_ADDRESS;          // Network mask
  end;
  {$EXTERNALSYM _INTERFACE_INFO_EX}
  INTERFACE_INFO_EX = _INTERFACE_INFO_EX;
  {$EXTERNALSYM INTERFACE_INFO_EX}
  LPINTERFACE_INFO_EX = ^INTERFACE_INFO_EX;
  {$EXTERNALSYM LPINTERFACE_INFO_EX}
  TInterfaceInfoEx = INTERFACE_INFO_EX;
  PInterfaceInfoEx = LPINTERFACE_INFO_EX;

// Possible flags for the  iiFlags - bitmask

const
  IFF_UP           = $00000001; // Interface is up
  {$EXTERNALSYM IFF_UP}
  IFF_BROADCAST    = $00000002; // Broadcast is  supported
  {$EXTERNALSYM IFF_BROADCAST}
  IFF_LOOPBACK     = $00000004; // this is loopback interface
  {$EXTERNALSYM IFF_LOOPBACK}
  IFF_POINTTOPOINT = $00000008; //this is point-to-point interface
  {$EXTERNALSYM IFF_POINTTOPOINT}
  IFF_MULTICAST    = $00000010; // multicast is supported
  {$EXTERNALSYM IFF_MULTICAST}

// structure for IP_PKTINFO option
//

type
  in_pktinfo = record
    ipi_addr: IN_ADDR; // destination IPv4 address
    ipi_ifindex: UINT; // received interface index
  end;
  {$EXTERNALSYM in_pktinfo}
  TInPktInfo = in_pktinfo;
  PInPktInfo = ^in_pktinfo;

// C_ASSERT(sizeof(IN_PKTINFO) == 8);

// structure for IPV6_PKTINFO option
//

  in6_pktinfo = record
    ipi6_addr: IN6_ADDR; // destination IPv6 address
    ipi6_ifindex: UINT; // received interface index
  end;
  {$EXTERNALSYM in6_pktinfo}
  TIn6PktInfo = in6_pktinfo;
  PIn6PktInfo = ^in6_pktinfo;

// C_ASSERT(sizeof(IN6_PKTINFO) == 20);

// Error codes from getaddrinfo()

const
  EAI_AGAIN    = WSATRY_AGAIN;
  {$EXTERNALSYM EAI_AGAIN}
  EAI_BADFLAGS = WSAEINVAL;
  {$EXTERNALSYM EAI_BADFLAGS}
  EAI_FAIL     = WSANO_RECOVERY;
  {$EXTERNALSYM EAI_FAIL}
  EAI_FAMILY   = WSAEAFNOSUPPORT;
  {$EXTERNALSYM EAI_FAMILY}
  EAI_MEMORY   = WSA_NOT_ENOUGH_MEMORY;
  {$EXTERNALSYM EAI_MEMORY}
//#define EAI_NODATA      WSANO_DATA
  EAI_NONAME   = WSAHOST_NOT_FOUND;
  {$EXTERNALSYM EAI_NONAME}
  EAI_SERVICE  = WSATYPE_NOT_FOUND;
  {$EXTERNALSYM EAI_SERVICE}
  EAI_SOCKTYPE = WSAESOCKTNOSUPPORT;
  {$EXTERNALSYM EAI_SOCKTYPE}

//
//  DCR_FIX:  EAI_NODATA remove or fix
//
//  EAI_NODATA was removed from rfc2553bis
//  need to find out from the authors why and
//  determine the error for "no records of this type"
//  temporarily, we'll keep #define to avoid changing
//  code that could change back;  use NONAME
//

  EAI_NODATA = EAI_NONAME;
  {$EXTERNALSYM EAI_NODATA}

// Structure used in getaddrinfo() call

type
  LPADDRINFO = ^addrinfo;
  {$EXTERNALSYM LPADDRINFO}
  addrinfo = record
    ai_flags: Integer;       // AI_PASSIVE, AI_CANONNAME, AI_NUMERICHOST
    ai_family: Integer;      // PF_xxx
    ai_socktype: Integer;    // SOCK_xxx
    ai_protocol: Integer;    // 0 or IPPROTO_xxx for IPv4 and IPv6
    ai_addrlen: size_t;  // Length of ai_addr
    ai_canonname: PChar; // Canonical name for nodename
    ai_addr: PSockAddr;  // Binary address
    ai_next: LPADDRINFO;  // Next structure in linked list
  end;
  {$EXTERNALSYM addrinfo}
  TAddrInfo = addrinfo;
  PAddrInfo = LPADDRINFO;

// Flags used in "hints" argument to getaddrinfo()

const
  AI_PASSIVE     = $1; // Socket address will be used in bind() call
  {$EXTERNALSYM AI_PASSIVE}
  AI_CANONNAME   = $2; // Return canonical name in first ai_canonname
  {$EXTERNALSYM AI_CANONNAME}
  AI_NUMERICHOST = $4; // Nodename must be a numeric address string
  {$EXTERNALSYM AI_NUMERICHOST}

function getaddrinfo(nodename, servname: PChar; hints: PAddrInfo; var res: PAddrInfo): Integer; stdcall;
{$EXTERNALSYM getaddrinfo}

procedure freeaddrinfo(ai: PAddrInfo); stdcall;
{$EXTERNALSYM freeaddrinfo}

// WARNING: The gai_strerror inline functions below use static buffers,
// and hence are not thread-safe.  We'll use buffers long enough to hold
// 1k characters.  Any system error messages longer than this will be
// returned as empty strings.  However 1k should work for the error codes
// used by getaddrinfo().

const
  GAI_STRERROR_BUFFER_SIZE = 1024;
  {$EXTERNALSYM GAI_STRERROR_BUFFER_SIZE}

function gai_strerrorA(ecode: Integer): PChar;
{$EXTERNALSYM gai_strerrorA}
function gai_strerrorW(ecode: Integer): PWideChar;
{$EXTERNALSYM gai_strerrorW}

{$IFDEF UNICODE}
function gai_strerror(ecode: Integer): PWideChar;
{$EXTERNALSYM gai_strerror}
{$ELSE}
function gai_strerror(ecode: Integer): PChar;
{$EXTERNALSYM gai_strerror}
{$ENDIF}

type
  socklen_t = Integer;
  {$EXTERNALSYM socklen_t}

function getnameinfo(sa: PSockAddr; salen: socklen_t; host: PChar; hostlen: DWORD; serv: PChar; servlen: DWORD; flags: Integer): Integer; stdcall;
{$EXTERNALSYM getnameinfo}

const
  NI_MAXHOST = 1025; // Max size of a fully-qualified domain name
  {$EXTERNALSYM NI_MAXHOST}
  NI_MAXSERV = 32; // Max size of a service name
  {$EXTERNALSYM NI_MAXSERV}

  INET_ADDRSTRLEN  = 16; // Max size of numeric form of IPv4 address
  {$EXTERNALSYM INET_ADDRSTRLEN}
  INET6_ADDRSTRLEN = 46; // Max size of numeric form of IPv6 address
  {$EXTERNALSYM INET6_ADDRSTRLEN}

// Flags for getnameinfo()

  NI_NOFQDN      = $01; // Only return nodename portion for local hosts
  {$EXTERNALSYM NI_NOFQDN}
  NI_NUMERICHOST = $02; // Return numeric form of the host's address
  {$EXTERNALSYM NI_NUMERICHOST}
  NI_NAMEREQD    = $04; // Error if the host's name not in DNS
  {$EXTERNALSYM NI_NAMEREQD}
  NI_NUMERICSERV = $08; // Return numeric form of the service (port #)
  {$EXTERNALSYM NI_NUMERICSERV}
  NI_DGRAM       = $10; // Service is a datagram service
  {$EXTERNALSYM NI_DGRAM}

implementation

uses
  SysUtils, JwaWinBase, JwaWinNT;

function IP_MSFILTER_SIZE(numsrc: Integer): Integer;
begin
  Result := SizeOf(ip_msfilter) - SizeOf(in_addr) + (numsrc * SizeOf(in_addr));
end;

function SS_PORT(ssp: Pointer): u_short;
begin
  Result := PSockAddrIn(ssp)^.sin_port;
end;

procedure IN6ADDR_SETANY(var x: TSockAddrIn6);
var
  I: Integer;
begin
  x.sin6_family := AF_INET6;
  x.sin6_port := 0;
  x.sin6_flowinfo := 0;
  for I := 0 to 15 do x.sin6_addr.s6_addr[I] := 0;
end;

procedure IN6ADDR_SETLOOPBACK(var x: TSockAddrIn6);
var
  I: Integer;
begin
  x.sin6_family := AF_INET6;
  x.sin6_port := 0;
  x.sin6_flowinfo := 0;
  for I := 0 to 14 do x.sin6_addr.s6_addr[I] := 0;
  x.sin6_addr.s6_addr[15] := 1;
end;

function IN6ADDR_ISANY(const x: TSockAddrIn6): Boolean;
var
  I: Integer;
begin
  Result := x.sin6_family = AF_INET6;
  for I := 0 to 15 do Result := Result and (x.sin6_addr.s6_addr[I] = 0);
end;

function IN6ADDR_ISLOOPBACK(const x: TSockAddrIn6): Boolean;
var
  I: Integer;
begin
  Result := x.sin6_family = AF_INET6;
  for I := 0 to 14 do Result := Result and (x.sin6_addr.s6_addr[I] = 0);
  Result := Result and (x.sin6_addr.s6_addr[15] = 1);
end;

function IN6_ADDR_EQUAL(const a, b: in6_addr): Boolean;
begin
  Result := CompareMem(@a, @b, SizeOf(in6_addr));
end;

function IN6_IS_ADDR_UNSPECIFIED(const a: in6_addr): boolean;
begin
  Result := IN6_ADDR_EQUAL(a, in6addr_any);
end;

function IN6_IS_ADDR_LOOPBACK(const a: in6_addr): Boolean;
begin
  Result := IN6_ADDR_EQUAL(a, in6addr_loopback);
end;

function IN6_IS_ADDR_MULTICAST(const a: in6_addr): Boolean;
begin
  Result := (a.s6_bytes[0] = $ff);
end;

function IN6_IS_ADDR_LINKLOCAL(const a: in6_addr): Boolean;
begin
  Result := ((a.s6_bytes[0] = $fe) and ((a.s6_bytes[1] and $c0) = $80));
end;

function IN6_IS_ADDR_SITELOCAL(const a: in6_addr): Boolean;
begin
  Result := ((a.s6_bytes[0] = $fe) and ((a.s6_bytes[1] and $c0) = $c0));
end;

function IN6_IS_ADDR_V4MAPPED(const a: in6_addr): Boolean;
begin
  Result := ((a.s6_words[0] = 0) and (a.s6_words[1] = 0) and (a.s6_words[2] = 0) and
             (a.s6_words[3] = 0) and (a.s6_words[4] = 0) and (a.s6_words[5] = $ffff));
end;

function IN6_IS_ADDR_V4COMPAT(const a: in6_addr): Boolean;
begin
  Result :=
   ((a.s6_words[0] = 0) and
    (a.s6_words[1] = 0) and
    (a.s6_words[2] = 0) and
    (a.s6_words[3] = 0) and
    (a.s6_words[4] = 0) and
    (a.s6_words[5] = 0) and
    not ((a.s6_words[6] = 0) and
         (a.s6_addr[14] = 0) and
         ((a.s6_addr[15] = 0) or (a.s6_addr[15] = 1))));
end;

function IN6_IS_ADDR_MC_NODELOCAL(const a: in6_addr): Boolean;
begin
  Result := IN6_IS_ADDR_MULTICAST(a) and ((a.s6_bytes[1] and $f) = 1);
end;

function IN6_IS_ADDR_MC_LINKLOCAL(const a: in6_addr): Boolean;
begin
  Result := IN6_IS_ADDR_MULTICAST(a) and ((a.s6_bytes[1] and $f) = 2);
end;

function IN6_IS_ADDR_MC_SITELOCAL(const a: in6_addr): Boolean;
begin
  Result := IN6_IS_ADDR_MULTICAST(a) and ((a.s6_bytes[1] and $f) = 5);
end;

function IN6_IS_ADDR_MC_ORGLOCAL(const a: in6_addr): Boolean;
begin
  Result := IN6_IS_ADDR_MULTICAST(a) and ((a.s6_bytes[1] and $f) = 8);
end;

function IN6_IS_ADDR_MC_GLOBAL(const a: in6_addr): Boolean;
begin
  Result := IN6_IS_ADDR_MULTICAST(a) and ((a.s6_bytes[1] and $f) = $e);
end;

const
  ws2tcpip = 'ws2_32.dll';

function getaddrinfo; external ws2tcpip name 'getaddrinfo';
procedure freeaddrinfo; external ws2tcpip name 'freeaddrinfo';

function gai_strerrorA(ecode: Integer): PChar;
var
  dwMsgLen: DWORD;
  buff: array [0..GAI_STRERROR_BUFFER_SIZE] of Char;
begin
  dwMsgLen := FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM or FORMAT_MESSAGE_IGNORE_INSERTS or FORMAT_MESSAGE_MAX_WIDTH_MASK,
    nil, ecode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), PChar(buff[0]), GAI_STRERROR_BUFFER_SIZE, nil);
  if dwMsgLen = 0 then
    Result := nil
  else
    Result := PChar(buff[0]);
end;

function gai_strerrorW(ecode: Integer): PWideChar;
var
  dwMsgLen: DWORD;
  buff: array [0..GAI_STRERROR_BUFFER_SIZE] of WideChar;
begin
  dwMsgLen := FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM or FORMAT_MESSAGE_IGNORE_INSERTS or FORMAT_MESSAGE_MAX_WIDTH_MASK,
    nil, ecode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), PWideChar(buff[0]), GAI_STRERROR_BUFFER_SIZE, nil);
  if dwMsgLen = 0 then
    Result := nil
  else
    Result := PWideChar(buff[0]);
end;

{$IFDEF UNICODE}
function gai_strerror(ecode: Integer): PWideChar;
var
  dwMsgLen: DWORD;
  buff: array [0..GAI_STRERROR_BUFFER_SIZE] of WideChar;
begin
  dwMsgLen := FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM or FORMAT_MESSAGE_IGNORE_INSERTS or FORMAT_MESSAGE_MAX_WIDTH_MASK,
    nil, ecode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), PWideChar(buff[0]), GAI_STRERROR_BUFFER_SIZE, nil);
  if dwMsgLen = 0 then
    Result := nil
  else
    Result := PWideChar(buff[0]);
end;
{$ELSE}
function gai_strerror(ecode: Integer): PChar;
var
  dwMsgLen: DWORD;
  buff: array [0..GAI_STRERROR_BUFFER_SIZE] of Char;
begin
  dwMsgLen := FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM or FORMAT_MESSAGE_IGNORE_INSERTS or FORMAT_MESSAGE_MAX_WIDTH_MASK,
    nil, ecode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), PChar(buff[0]), GAI_STRERROR_BUFFER_SIZE, nil);
  if dwMsgLen = 0 then
    Result := nil
  else
    Result := PChar(buff[0]);
end;
{$ENDIF}

function getnameinfo; external ws2tcpip name 'getnameinfo';

end.
