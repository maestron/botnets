{******************************************************************************}
{                                                       	               }
{ Winsock2 API interface Unit for Object Pascal                                }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: winsock2.h, released June 2000. The original Pascal    }
{ code is: WinSock2.pas, released December 2000. The initial developer of the  }
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

unit JwaWinsock2;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "winsock2.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaQos, JwaWinType, JwaWinBase, JwaWinError, JwaWinNT;

type // TODO
  ULONG_PTR = ULONG;
  DWORD_PTR = DWORD;
  PPChar = ^PChar;
  {$NODEFINE PPChar}
  HANDLE = THandle;
  {$NODEFINE HANDLE}
  LPHANDLE = ^THandle;
  {$NODEFINE LPHANDLE}
  LPBYTE = ^BYTE;
  {$NODEFINE LPBYTE}
  LPVOID = Pointer;
  {$NODEFINE LPVOID}
  USHORT = Word;
  {$NODEFINE USHORT}
  UCHAR = Byte;
  {$NODEFINE UCHAR}
  ULONG = Cardinal;
  {$NODEFINE ULONG}

//#include <pshpack4.h>
{$ALIGN ON}

// Winsock2.h -- definitions to be used with the WinSock 2 DLL and
//               WinSock 2 applications.
//
// This header file corresponds to version 2.2.x of the WinSock API
// specification.
//
// This file includes parts which are Copyright (c) 1982-1986 Regents
// of the University of California.  All rights reserved.  The
// Berkeley Software License Agreement specifies the terms and
// conditions for redistribution.
//

(*
 * Default: include function prototypes, don't include function typedefs.
 *)

{$IFNDEF INCL_WINSOCK_API_PROTOTYPES}
const
  INCL_WINSOCK_API_PROTOTYPES = 1;
  {$EXTERNALSYM INCL_WINSOCK_API_PROTOTYPES}
{$ENDIF}

{$IFNDEF INCL_WINSOCK_API_TYPEDEFS}
const
  INCL_WINSOCK_API_TYPEDEFS = 0;
  {$EXTERNALSYM INCL_WINSOCK_API_TYPEDEFS}
{$ENDIF}

const
  WINSOCK_VERSION = $0202;
  {$EXTERNALSYM WINSOCK_VERSION}

//
// Basic system type definitions, taken from the BSD file sys/types.h.
//

type
  u_char = Byte;
  {$EXTERNALSYM u_char}
  u_short = Word;
  {$EXTERNALSYM u_short}
  u_int = Cardinal;
  {$EXTERNALSYM u_int}
  u_long = Cardinal;
  {$EXTERNALSYM u_long}
  u_int64 = Int64; // unsigned __int64 !! TODO For Delphi 7 ??
  {$EXTERNALSYM u_int64}

//
// The new type to be used in all
// instances which refer to sockets.
//

type
  TSocket = Cardinal;

//
// Select uses arrays of SOCKETs.  These macros manipulate such
// arrays.  FD_SETSIZE may be defined by the user before including
// this file, but the default here should be >= 64.
//
// CAVEAT IMPLEMENTOR and USER: THESE MACROS AND TYPES MUST BE
// INCLUDED IN WINSOCK2.H EXACTLY AS SHOWN HERE.
//

const
  FD_SETSIZE = 64;
  {$EXTERNALSYM FD_SETSIZE}

type
  fd_set = record
    fd_count: u_int;                                 // how many are SET?
    fd_array: array [0..FD_SETSIZE - 1] of TSocket;   // an array of SOCKETs
  end;
  {$EXTERNALSYM fd_set}
  TFdSet = fd_set;
  PFdSet = ^fd_set;

function __WSAFDIsSet(s: TSocket; var FDSet: TFDSet): Integer; stdcall;
{$EXTERNALSYM __WSAFDIsSet}

procedure FD_CLR(fd: TSocket; var fdset: TFdSet);
{$EXTERNALSYM FD_CLR}

procedure _FD_SET(fd: TSocket; var fdset: TFDSet);
//{$EXTERNALSYM FD_SET}

procedure FD_ZERO(var fdset: TFdSet);
{$EXTERNALSYM FD_ZERO}

function FD_ISSET(fd: TSocket; var fdset: TFdSet): Boolean;
{$EXTERNALSYM FD_ISSET}

//
// Structure used in select() call, taken from the BSD file sys/time.h.
//

type
  timeval = record
    tv_sec: Longint;         // seconds
    tv_usec: Longint;        // and microseconds
  end;
  {$EXTERNALSYM timeval}
  TTimeVal = timeval;
  PTimeVal = ^timeval;

//
// Operations on timevals.
//
// NB: timercmp does not work for >= or <=.
//

function timerisset(const tvp: TTimeVal): Boolean;
{$EXTERNALSYM timerisset}

//function timercmp(const tvp, uvp: TTimeVal; cmp): Boolean;
//{$EXTERNALSYM timercmp}

procedure timerclear(var tvp: TTimeVal);
{$EXTERNALSYM timerclear}

//
// Commands for ioctlsocket(),  taken from the BSD file fcntl.h.
//
//
// Ioctl's have the command encoded in the lower word,
// and the size of any in or out parameters in the upper
// word.  The high 2 bits of the upper word are used
// to encode the in/out status of the parameter; for now
// we restrict parameters to at most 128 bytes.
//

const
  IOCPARM_MASK = $7f;              // parameters must be < 128 bytes
  {$EXTERNALSYM IOCPARM_MASK}
  IOC_VOID     = $20000000;        // no parameters
  {$EXTERNALSYM IOC_VOID}
  IOC_OUT      = $40000000;        // copy out parameters
  {$EXTERNALSYM IOC_OUT}
  IOC_IN       = DWORD($80000000); // copy in parameters
  {$EXTERNALSYM IOC_IN}
  IOC_INOUT    = DWORD(IOC_IN or IOC_OUT);
  {$EXTERNALSYM IOC_INOUT}

  // 0x20000000 distinguishes new & old ioctl's

function _IO(x, y: DWORD): DWORD;
{$EXTERNALSYM _IO}

function _IOR(x, y, t: DWORD): DWORD;
{$EXTERNALSYM _IOR}

function _IOW(x, y, t: DWORD): DWORD;
{$EXTERNALSYM _IOW}

const
  FIONREAD = IOC_OUT or ((SizeOf(u_long) and IOCPARM_MASK) shl 16) or (Ord('f') shl 8) or 127; // get # bytes to read
  {$EXTERNALSYM FIONREAD}
  FIONBIO = IOC_IN or ((SizeOf(u_long) and IOCPARM_MASK) shl 16) or (Ord('f') shl 8) or 126; // set/clear non-blocking i/o
  {$EXTERNALSYM FIONBIO}
  FIOASYNC = IOC_IN or ((SizeOf(u_long) and IOCPARM_MASK) shl 16) or (Ord('f') shl 8) or 125; // set/clear async i/o
  {$EXTERNALSYM FIOASYNC}

// Socket I/O Controls

  SIOCSHIWAT = DWORD(IOC_IN or ((SizeOf(u_long) and IOCPARM_MASK) shl 16) or (Ord('s') shl 8) or 0); // set high watermark
  {$EXTERNALSYM SIOCSHIWAT}
  SIOCGHIWAT = IOC_OUT or ((SizeOf(u_long) and IOCPARM_MASK) shl 16) or (Ord('s') shl 8) or 1; // get high watermark
  {$EXTERNALSYM SIOCGHIWAT}
  SIOCSLOWAT = DWORD(IOC_IN or ((SizeOf(u_long) and IOCPARM_MASK) shl 16) or (Ord('s') shl 8) or 2); // set low watermark
  {$EXTERNALSYM SIOCSLOWAT}
  SIOCGLOWAT = IOC_OUT or ((SizeOf(u_long) and IOCPARM_MASK) shl 16) or (Ord('s') shl 8) or 3; // get low watermark
  {$EXTERNALSYM SIOCGLOWAT}
  SIOCATMARK = IOC_OUT or ((SizeOf(u_long) and IOCPARM_MASK) shl 16) or (Ord('s') shl 8) or 7; // at oob mark?
  {$EXTERNALSYM SIOCATMARK}

//
// Structures returned by network data base library, taken from the
// BSD file netdb.h.  All addresses are supplied in host order, and
// returned in network order (suitable for use in system calls).
//

type
  hostent = record
    h_name: PChar;           // official name of host
    h_aliases: PPChar;  // alias list
    h_addrtype: Smallint;             // host address type
    h_length: Smallint;               // length of address
    case Integer of
      0: (h_addr_list: PPChar); // list of addresses
      1: (h_addr: PPChar);          // address, for backward compat
  end;
  {$EXTERNALSYM hostent}
  THostEnt = hostent;
  PHostEnt = ^hostent;

//
// It is assumed here that a network number
// fits in 32 bits.
//

type
  netent = record
    n_name: PChar;           // official name of net
    n_aliases: PPChar;  // alias list
    n_addrtype: Smallint;             // net address type
    n_net: u_long;                  // network #
  end;
  {$EXTERNALSYM netent}
  TNetEnt = netent;
  PNetEnt = ^netent;

  servent = record
    s_name: PChar;           // official service name
    s_aliases: PPChar;  // alias list
    s_port: Smallint;                 // port #
    s_proto: PChar;          // protocol to use
  end;
  {$EXTERNALSYM servent}
  TServEnt = servent;
  PServEnt = ^servent;

  protoent = record
    p_name: PChar;           // official protocol name
    p_aliases: PPChar;  // alias list
    p_proto: Smallint;                // protocol #
  end;
  {$EXTERNALSYM protoent}
  TProtoEnt = protoent;
  PProtoEnt = ^protoent;

//
// Constants and structures defined by the internet system,
// Per RFC 790, September 1981, taken from the BSD file netinet/in.h.
//

//
// Protocols
//

const
  IPPROTO_IP   = 0; // dummy for IP
  {$EXTERNALSYM IPPROTO_IP}
  IPPROTO_HOPOPTS = 0; // IPv6 hop-by-hop options
  {$EXTERNALSYM IPPROTO_HOPOPTS}
  IPPROTO_ICMP = 1; // control message protocol
  {$EXTERNALSYM IPPROTO_ICMP}
  IPPROTO_IGMP = 2; // internet group management protocol
  {$EXTERNALSYM IPPROTO_IGMP}
  IPPROTO_GGP  = 3; // gateway^2 (deprecated)
  {$EXTERNALSYM IPPROTO_GGP}
  IPPROTO_IPV4 = 4; // IPv4
  {$EXTERNALSYM IPPROTO_IPV4}
  IPPROTO_TCP  = 6; // tcp
  {$EXTERNALSYM IPPROTO_TCP}
  IPPROTO_PUP  = 12; // pup
  {$EXTERNALSYM IPPROTO_PUP}
  IPPROTO_UDP  = 17; // user datagram protocol
  {$EXTERNALSYM IPPROTO_UDP}
  IPPROTO_IDP  = 22; // xns idp
  {$EXTERNALSYM IPPROTO_IDP}
  IPPROTO_IPV6 = 41; // IPv6
  {$EXTERNALSYM IPPROTO_IPV6}
  IPPROTO_ROUTING        = 43;              // IPv6 routing header
  {$EXTERNALSYM IPPROTO_ROUTING}
  IPPROTO_FRAGMENT       = 44;              // IPv6 fragmentation header
  {$EXTERNALSYM IPPROTO_FRAGMENT}
  IPPROTO_ESP            = 50;              // IPsec ESP header
  {$EXTERNALSYM IPPROTO_ESP}
  IPPROTO_AH             = 51;              // IPsec AH
  {$EXTERNALSYM IPPROTO_AH}
  IPPROTO_ICMPV6         = 58;              // ICMPv6
  {$EXTERNALSYM IPPROTO_ICMPV6}
  IPPROTO_NONE           = 59;              // IPv6 no next header
  {$EXTERNALSYM IPPROTO_NONE}
  IPPROTO_DSTOPTS        = 60;              // IPv6 destination options
  {$EXTERNALSYM IPPROTO_DSTOPTS}
  IPPROTO_ND   = 77; // UNOFFICIAL net disk proto
  {$EXTERNALSYM IPPROTO_ND}
  IPPROTO_ICLFXBM = 78;
  {$EXTERNALSYM IPPROTO_ICLFXBM}

  IPPROTO_RAW  = 255; // raw IP packet
  {$EXTERNALSYM IPPROTO_RAW}
  IPPROTO_MAX  = 256;
  {$EXTERNALSYM IPPROTO_MAX}

//
// Port/socket numbers: network standard functions
//

  IPPORT_ECHO       = 7;
  {$EXTERNALSYM IPPORT_ECHO}
  IPPORT_DISCARD    = 9;
  {$EXTERNALSYM IPPORT_DISCARD}
  IPPORT_SYSTAT     = 11;
  {$EXTERNALSYM IPPORT_SYSTAT}
  IPPORT_DAYTIME    = 13;
  {$EXTERNALSYM IPPORT_DAYTIME}
  IPPORT_NETSTAT    = 15;
  {$EXTERNALSYM IPPORT_NETSTAT}
  IPPORT_FTP        = 21;
  {$EXTERNALSYM IPPORT_FTP}
  IPPORT_TELNET     = 23;
  {$EXTERNALSYM IPPORT_TELNET}
  IPPORT_SMTP       = 25;
  {$EXTERNALSYM IPPORT_SMTP}
  IPPORT_TIMESERVER = 37;
  {$EXTERNALSYM IPPORT_TIMESERVER}
  IPPORT_NAMESERVER = 42;
  {$EXTERNALSYM IPPORT_NAMESERVER}
  IPPORT_WHOIS      = 43;
  {$EXTERNALSYM IPPORT_WHOIS}
  IPPORT_MTP        = 57;
  {$EXTERNALSYM IPPORT_MTP}

//
// Port/socket numbers: host specific functions
//

  IPPORT_TFTP    = 69;
  {$EXTERNALSYM IPPORT_TFTP}
  IPPORT_RJE     = 77;
  {$EXTERNALSYM IPPORT_RJE}
  IPPORT_FINGER  = 79;
  {$EXTERNALSYM IPPORT_FINGER}
  IPPORT_TTYLINK = 87;
  {$EXTERNALSYM IPPORT_TTYLINK}
  IPPORT_SUPDUP  = 95;
  {$EXTERNALSYM IPPORT_SUPDUP}

//
// UNIX TCP sockets
//

  IPPORT_EXECSERVER  = 512;
  {$EXTERNALSYM IPPORT_EXECSERVER}
  IPPORT_LOGINSERVER = 513;
  {$EXTERNALSYM IPPORT_LOGINSERVER}
  IPPORT_CMDSERVER   = 514;
  {$EXTERNALSYM IPPORT_CMDSERVER}
  IPPORT_EFSSERVER   = 520;
  {$EXTERNALSYM IPPORT_EFSSERVER}

//
// UNIX UDP sockets
//

  IPPORT_BIFFUDP     = 512;
  {$EXTERNALSYM IPPORT_BIFFUDP}
  IPPORT_WHOSERVER   = 513;
  {$EXTERNALSYM IPPORT_WHOSERVER}
  IPPORT_ROUTESERVER = 520;
  {$EXTERNALSYM IPPORT_ROUTESERVER}

  // 520+1 also used

//
// Ports < IPPORT_RESERVED are reserved for
// privileged processes (e.g. root).
//

  IPPORT_RESERVED = 1024;
  {$EXTERNALSYM IPPORT_RESERVED}

//
// Link numbers
//

  IMPLINK_IP        = 155;
  {$EXTERNALSYM IMPLINK_IP}
  IMPLINK_LOWEXPER  = 156;
  {$EXTERNALSYM IMPLINK_LOWEXPER}
  IMPLINK_HIGHEXPER = 158;
  {$EXTERNALSYM IMPLINK_HIGHEXPER}

//
// Internet address (old style... should be updated)
//

type
  SunB = packed record
    s_b1, s_b2, s_b3, s_b4: u_char;
  end;
  {$EXTERNALSYM SunB}

  SunC = packed record
    s_c1, s_c2, s_c3, s_c4: Char;
  end;
  {$NODEFINE SunC}

  SunW = packed record
    s_w1, s_w2: u_short;
  end;
  {$EXTERNALSYM SunW}

  in_addr = record
    case Integer of
      0: (S_un_b: SunB);
      1: (S_un_c: SunC);
      2: (S_un_w: SunW);
      3: (S_addr: u_long);
    // #define s_addr  S_un.S_addr // can be used for most tcp & ip code
    // #define s_host  S_un.S_un_b.s_b2 // host on imp
    // #define s_net   S_un.S_un_b.s_b1  // netword
    // #define s_imp   S_un.S_un_w.s_w2 // imp
    // #define s_impno S_un.S_un_b.s_b4 // imp #
    // #define s_lh    S_un.S_un_b.s_b3 // logical host
  end;
  {$EXTERNALSYM in_addr}
  TInAddr = in_addr;
  PInAddr = ^in_addr;

//
// Definitions of bits in internet address integers.
// On subnets, the decomposition of addresses to host and net parts
// is done according to subnet mask, not the masks here.
//

function IN_CLASSA(i: DWORD): Boolean;
{$EXTERNALSYM IN_CLASSA}

const
  IN_CLASSA_NET    = DWORD($ff000000);
  {$EXTERNALSYM IN_CLASSA_NET}
  IN_CLASSA_NSHIFT = 24;
  {$EXTERNALSYM IN_CLASSA_NSHIFT}
  IN_CLASSA_HOST   = $00ffffff;
  {$EXTERNALSYM IN_CLASSA_HOST}
  IN_CLASSA_MAX    = 128;
  {$EXTERNALSYM IN_CLASSA_MAX}

function IN_CLASSB(i: DWORD): Boolean;
{$EXTERNALSYM IN_CLASSB}

const
  IN_CLASSB_NET    = DWORD($ffff0000);
  {$EXTERNALSYM IN_CLASSB_NET}
  IN_CLASSB_NSHIFT = 16;
  {$EXTERNALSYM IN_CLASSB_NSHIFT}
  IN_CLASSB_HOST   = $0000ffff;
  {$EXTERNALSYM IN_CLASSB_HOST}
  IN_CLASSB_MAX    = 65536;
  {$EXTERNALSYM IN_CLASSB_MAX}

function IN_CLASSC(i: DWORD): Boolean;
{$EXTERNALSYM IN_CLASSC}

const
  IN_CLASSC_NET    = DWORD($ffffff00);
  {$EXTERNALSYM IN_CLASSC_NET}
  IN_CLASSC_NSHIFT = 8;
  {$EXTERNALSYM IN_CLASSC_NSHIFT}
  IN_CLASSC_HOST   = $000000ff;
  {$EXTERNALSYM IN_CLASSC_HOST}

function IN_CLASSD(i: DWORD): Boolean;
{$EXTERNALSYM IN_CLASSD}

const
  IN_CLASSD_NET    = DWORD($f0000000); // These ones aren't really
  {$EXTERNALSYM IN_CLASSD_NET}
  IN_CLASSD_NSHIFT = 28; // net and host fields, but
  {$EXTERNALSYM IN_CLASSD_NSHIFT}
  IN_CLASSD_HOST   = $0fffffff; // routing needn't know.
  {$EXTERNALSYM IN_CLASSD_HOST}

function IN_MULTICAST(i: DWORD): Boolean;
{$EXTERNALSYM IN_MULTICAST}

const
  INADDR_ANY       = u_long($00000000);
  {$EXTERNALSYM INADDR_ANY}
  INADDR_LOOPBACK  = $7f000001;
  {$EXTERNALSYM INADDR_LOOPBACK}
  INADDR_BROADCAST = u_long($ffffffff);
  {$EXTERNALSYM INADDR_BROADCAST}
  INADDR_NONE      = DWORD($ffffffff);
  {$EXTERNALSYM INADDR_NONE}

  ADDR_ANY         = INADDR_ANY;
  {$EXTERNALSYM ADDR_ANY}

//
// Socket address, internet style.
//

type
  sockaddr_in = record
    sin_family: Smallint;
    sin_port: u_short;
    sin_addr: in_addr;
    sin_zero: array [0..7] of Char;
  end;
  {$EXTERNALSYM sockaddr_in}
  TSockAddrIn = sockaddr_in;
  PSockAddrIn = ^sockaddr_in;

const
  WSADESCRIPTION_LEN = 256;
  {$EXTERNALSYM WSADESCRIPTION_LEN}
  WSASYS_STATUS_LEN  = 128;
  {$EXTERNALSYM WSASYS_STATUS_LEN}

type
  WSAData = record
    wVersion: WORD;
    wHighVersion: WORD;
    szDescription: array [0..WSADESCRIPTION_LEN] of Char;
    szSystemStatus: array [0..WSASYS_STATUS_LEN] of Char;
    iMaxSockets: Word;
    iMaxUdpDg: Word;
    lpVendorInfo: PChar;
  end;
  {$EXTERNALSYM WSAData}
  LPWSADATA = ^WSAData;
  {$EXTERNALSYM LPWSADATA}
  TWsaData = WSAData;
  PWsaData = LPWSADATA;

//
// Definitions related to sockets: types, address families, options,
// taken from the BSD file sys/socket.h.
//

//
// This is used instead of -1, since the
// SOCKET type is unsigned.
//

const
  INVALID_SOCKET = TSocket(not 0);
  {$EXTERNALSYM INVALID_SOCKET}
  SOCKET_ERROR   = -1;
  {$EXTERNALSYM SOCKET_ERROR}

//
// The  following  may  be used in place of the address family, socket type, or
// protocol  in  a  call  to WSASocket to indicate that the corresponding value
// should  be taken from the supplied WSAPROTOCOL_INFO structure instead of the
// parameter itself.
//

  FROM_PROTOCOL_INFO = -1;
  {$EXTERNALSYM FROM_PROTOCOL_INFO}

//
// Types
//

  SOCK_STREAM    = 1; // stream socket
  {$EXTERNALSYM SOCK_STREAM}
  SOCK_DGRAM     = 2; // datagram socket
  {$EXTERNALSYM SOCK_DGRAM}
  SOCK_RAW       = 3; // raw-protocol interface
  {$EXTERNALSYM SOCK_RAW}
  SOCK_RDM       = 4; // reliably-delivered message
  {$EXTERNALSYM SOCK_RDM}
  SOCK_SEQPACKET = 5; // sequenced packet stream
  {$EXTERNALSYM SOCK_SEQPACKET}

//
// Option flags per-socket.
//

  SO_DEBUG       = $0001; // turn on debugging info recording
  {$EXTERNALSYM SO_DEBUG}
  SO_ACCEPTCONN  = $0002; // socket has had listen()
  {$EXTERNALSYM SO_ACCEPTCONN}
  SO_REUSEADDR   = $0004; // allow local address reuse
  {$EXTERNALSYM SO_REUSEADDR}
  SO_KEEPALIVE   = $0008; // keep connections alive
  {$EXTERNALSYM SO_KEEPALIVE}
  SO_DONTROUTE   = $0010; // just use interface addresses
  {$EXTERNALSYM SO_DONTROUTE}
  SO_BROADCAST   = $0020; // permit sending of broadcast msgs
  {$EXTERNALSYM SO_BROADCAST}
  SO_USELOOPBACK = $0040; // bypass hardware when possible
  {$EXTERNALSYM SO_USELOOPBACK}
  SO_LINGER      = $0080; // linger on close if data present
  {$EXTERNALSYM SO_LINGER}
  SO_OOBINLINE   = $0100; // leave received OOB data in line
  {$EXTERNALSYM SO_OOBINLINE}

  SO_DONTLINGER       = DWORD(not SO_LINGER);
  {$EXTERNALSYM SO_DONTLINGER}
  SO_EXCLUSIVEADDRUSE = DWORD(not SO_REUSEADDR); // disallow local address reuse
  {$EXTERNALSYM SO_EXCLUSIVEADDRUSE}

//
// Additional options.
//

  SO_SNDBUF   = $1001; // send buffer size
  {$EXTERNALSYM SO_SNDBUF}
  SO_RCVBUF   = $1002; // receive buffer size
  {$EXTERNALSYM SO_RCVBUF}
  SO_SNDLOWAT = $1003; // send low-water mark
  {$EXTERNALSYM SO_SNDLOWAT}
  SO_RCVLOWAT = $1004; // receive low-water mark
  {$EXTERNALSYM SO_RCVLOWAT}
  SO_SNDTIMEO = $1005; // send timeout
  {$EXTERNALSYM SO_SNDTIMEO}
  SO_RCVTIMEO = $1006; // receive timeout
  {$EXTERNALSYM SO_RCVTIMEO}
  SO_ERROR    = $1007; // get error status and clear
  {$EXTERNALSYM SO_ERROR}
  SO_TYPE     = $1008; // get socket type
  {$EXTERNALSYM SO_TYPE}

//
// WinSock 2 extension -- new options
//

  SO_GROUP_ID       = $2001; // ID of a socket group
  {$EXTERNALSYM SO_GROUP_ID}
  SO_GROUP_PRIORITY = $2002; // the relative priority within a group
  {$EXTERNALSYM SO_GROUP_PRIORITY}
  SO_MAX_MSG_SIZE   = $2003; // maximum message size
  {$EXTERNALSYM SO_MAX_MSG_SIZE}
  SO_PROTOCOL_INFOA = $2004; // WSAPROTOCOL_INFOA structure
  {$EXTERNALSYM SO_PROTOCOL_INFOA}
  SO_PROTOCOL_INFOW = $2005; // WSAPROTOCOL_INFOW structure
  {$EXTERNALSYM SO_PROTOCOL_INFOW}

{$IFDEF UNICODE}
  SO_PROTOCOL_INFO = SO_PROTOCOL_INFOW;
  {$EXTERNALSYM SO_PROTOCOL_INFO}
{$ELSE}
  SO_PROTOCOL_INFO = SO_PROTOCOL_INFOA;
  {$EXTERNALSYM SO_PROTOCOL_INFO}
{$ENDIF}

  PVD_CONFIG            = $3001; // configuration info for service provider
  {$EXTERNALSYM PVD_CONFIG}
  SO_CONDITIONAL_ACCEPT = $3002; // enable true conditional accept:
                                 //  connection is not ack-ed to the
                                 //  other side until conditional
                                 //  function returns CF_ACCEPT
  {$EXTERNALSYM SO_CONDITIONAL_ACCEPT}

//
// TCP options.
//

  TCP_NODELAY = $0001;
  {$EXTERNALSYM TCP_NODELAY}

//
// Address families.
//

  AF_UNSPEC = 0; // unspecified
  {$EXTERNALSYM AF_UNSPEC}

//
// Although  AF_UNSPEC  is  defined for backwards compatibility, using
// AF_UNSPEC for the "af" parameter when creating a socket is STRONGLY
// DISCOURAGED.    The  interpretation  of  the  "protocol"  parameter
// depends  on the actual address family chosen.  As environments grow
// to  include  more  and  more  address families that use overlapping
// protocol  values  there  is  more  and  more  chance of choosing an
// undesired address family when AF_UNSPEC is used.
//

  AF_UNIX      = 1; // local to host (pipes, portals
  {$EXTERNALSYM AF_UNIX}
  AF_INET      = 2; // internetwork: UDP, TCP, etc.
  {$EXTERNALSYM AF_INET}
  AF_IMPLINK   = 3; // arpanet imp addresses
  {$EXTERNALSYM AF_IMPLINK}
  AF_PUP       = 4; // pup protocols: e.g. BSP
  {$EXTERNALSYM AF_PUP}
  AF_CHAOS     = 5; // mit CHAOS protocols
  {$EXTERNALSYM AF_CHAOS}
  AF_NS        = 6; // XEROX NS protocols
  {$EXTERNALSYM AF_NS}
  AF_IPX       = AF_NS; // IPX protocols: IPX, SPX, etc.
  {$EXTERNALSYM AF_IPX}
  AF_ISO       = 7; // ISO protocols
  {$EXTERNALSYM AF_ISO}
  AF_OSI       = AF_ISO; // OSI is ISO
  {$EXTERNALSYM AF_OSI}
  AF_ECMA      = 8; // european computer manufacturers
  {$EXTERNALSYM AF_ECMA}
  AF_DATAKIT   = 9; // datakit protocols
  {$EXTERNALSYM AF_DATAKIT}
  AF_CCITT     = 10; // CCITT protocols, X.25 etc
  {$EXTERNALSYM AF_CCITT}
  AF_SNA       = 11; // IBM SNA
  {$EXTERNALSYM AF_SNA}
  AF_DECnet    = 12; // DECnet
  {$EXTERNALSYM AF_DECnet}
  AF_DLI       = 13; // Direct data link interface
  {$EXTERNALSYM AF_DLI}
  AF_LAT       = 14; // LAT
  {$EXTERNALSYM AF_LAT}
  AF_HYLINK    = 15; // NSC Hyperchannel
  {$EXTERNALSYM AF_HYLINK}
  AF_APPLETALK = 16; // AppleTalk
  {$EXTERNALSYM AF_APPLETALK}
  AF_NETBIOS   = 17; // NetBios-style addresses
  {$EXTERNALSYM AF_NETBIOS}
  AF_VOICEVIEW = 18; // VoiceView
  {$EXTERNALSYM AF_VOICEVIEW}
  AF_FIREFOX   = 19; // Protocols from Firefox
  {$EXTERNALSYM AF_FIREFOX}
  AF_UNKNOWN1  = 20; // Somebody is using this!
  {$EXTERNALSYM AF_UNKNOWN1}
  AF_BAN       = 21; // Banyan
  {$EXTERNALSYM AF_BAN}
  AF_ATM       = 22; // Native ATM Services
  {$EXTERNALSYM AF_ATM}
  AF_INET6     = 23; // Internetwork Version 6
  {$EXTERNALSYM AF_INET6}
  AF_CLUSTER   = 24; // Microsoft Wolfpack
  {$EXTERNALSYM AF_CLUSTER}
  AF_12844     = 25; // IEEE 1284.4 WG AF
  {$EXTERNALSYM AF_12844}
  AF_IRDA      = 26; // IrDA
  {$EXTERNALSYM AF_IRDA}
  AF_NETDES    = 28; // Network Designers OSI & gateway enabled protocols
  {$EXTERNALSYM AF_NETDES}

  AF_TCNPROCESS = 29;
  {$EXTERNALSYM AF_TCNPROCESS}
  AF_TCNMESSAGE = 30;
  {$EXTERNALSYM AF_TCNMESSAGE}
  AF_ICLFXBM    = 31;
  {$EXTERNALSYM AF_ICLFXBM}

  AF_MAX = 32;
  {$EXTERNALSYM AF_MAX}

//
// Structure used by kernel to store most
// addresses.
//

type
  sockaddr = record
    sa_family: u_short;              // address family
    sa_data: array [0..13] of Char;            // up to 14 bytes of direct address
  end;
  {$EXTERNALSYM sockaddr}
  TSockAddr = sockaddr;
  PSockAddr = ^sockaddr;

//
// Portable socket structure (RFC 2553).
//

//
// Desired design of maximum size and alignment.
// These are implementation specific.
//

const
  _SS_MAXSIZE   = 128;               // Maximum size.
  {$EXTERNALSYM _SS_MAXSIZE}
  _SS_ALIGNSIZE = SizeOf(Int64);  // Desired alignment.
  {$EXTERNALSYM _SS_ALIGNSIZE}

//
// Definitions used for sockaddr_storage structure paddings design.
//

  _SS_PAD1SIZE = _SS_ALIGNSIZE - SizeOf(short);
  {$EXTERNALSYM _SS_PAD1SIZE}
  _SS_PAD2SIZE = _SS_MAXSIZE - (SizeOf(short) + _SS_PAD1SIZE + _SS_ALIGNSIZE);
  {$EXTERNALSYM _SS_PAD2SIZE}
  
type
  sockaddr_storage = record
    ss_family: short;               // Address family.
    __ss_pad1: array [0.._SS_PAD1SIZE - 1] of char;  // 6 byte pad, this is to make
                                   // implementation specific pad up to
                                   // alignment field that follows explicit
                                   // in the data structure.
    __ss_align: Int64;            // Field to force desired structure.
    __ss_pad2: array [0.._SS_PAD2SIZE - 1] of char;  // 112 byte pad to achieve desired size;
                                   // _SS_MAXSIZE value minus size of
                                   // ss_family, __ss_pad1, and
                                   // __ss_align fields is 112.
  end;
  {$EXTERNALSYM sockaddr_storage}
  TSockAddrStorage = sockaddr_storage;
  PSockAddrStorage = ^sockaddr_storage;

//
// Structure used by kernel to pass protocol
// information in raw sockets.
//

  sockproto = record
    sp_family: u_short;              // address family
    sp_protocol: u_short;            // protocol
  end;
  {$EXTERNALSYM sockproto}
  TSockProto = sockproto;
  PSockProto = ^sockproto;

//
// Protocol families, same as address families for now.
//

const
  PF_UNSPEC    = AF_UNSPEC;
  {$EXTERNALSYM PF_UNSPEC}
  PF_UNIX      = AF_UNIX;
  {$EXTERNALSYM PF_UNIX}
  PF_INET      = AF_INET;
  {$EXTERNALSYM PF_INET}
  PF_IMPLINK   = AF_IMPLINK;
  {$EXTERNALSYM PF_IMPLINK}
  PF_PUP       = AF_PUP;
  {$EXTERNALSYM PF_PUP}
  PF_CHAOS     = AF_CHAOS;
  {$EXTERNALSYM PF_CHAOS}
  PF_NS        = AF_NS;
  {$EXTERNALSYM PF_NS}
  PF_IPX       = AF_IPX;
  {$EXTERNALSYM PF_IPX}
  PF_ISO       = AF_ISO;
  {$EXTERNALSYM PF_ISO}
  PF_OSI       = AF_OSI;
  {$EXTERNALSYM PF_OSI}
  PF_ECMA      = AF_ECMA;
  {$EXTERNALSYM PF_ECMA}
  PF_DATAKIT   = AF_DATAKIT;
  {$EXTERNALSYM PF_DATAKIT}
  PF_CCITT     = AF_CCITT;
  {$EXTERNALSYM PF_CCITT}
  PF_SNA       = AF_SNA;
  {$EXTERNALSYM PF_SNA}
  PF_DECnet    = AF_DECnet;
  {$EXTERNALSYM PF_DECnet}
  PF_DLI       = AF_DLI;
  {$EXTERNALSYM PF_DLI}
  PF_LAT       = AF_LAT;
  {$EXTERNALSYM PF_LAT}
  PF_HYLINK    = AF_HYLINK;
  {$EXTERNALSYM PF_HYLINK}
  PF_APPLETALK = AF_APPLETALK;
  {$EXTERNALSYM PF_APPLETALK}
  PF_VOICEVIEW = AF_VOICEVIEW;
  {$EXTERNALSYM PF_VOICEVIEW}
  PF_FIREFOX   = AF_FIREFOX;
  {$EXTERNALSYM PF_FIREFOX}
  PF_UNKNOWN1  = AF_UNKNOWN1;
  {$EXTERNALSYM PF_UNKNOWN1}
  PF_BAN       = AF_BAN;
  {$EXTERNALSYM PF_BAN}
  PF_ATM       = AF_ATM;
  {$EXTERNALSYM PF_ATM}
  PF_INET6     = AF_INET6;
  {$EXTERNALSYM PF_INET6}

  PF_MAX = AF_MAX;
  {$EXTERNALSYM PF_MAX}

//
// Structure used for manipulating linger option.
//

type
  linger = record
    l_onoff: u_short;                // option on/off
    l_linger: u_short;               // linger time
  end;
  {$EXTERNALSYM linger}
  TLinger = linger;
  PLinger = ^linger;

//
// Level number for (get/set)sockopt() to apply to socket itself.
//

const
  SOL_SOCKET = $ffff; // options for socket level
  {$EXTERNALSYM SOL_SOCKET}

//
// Maximum queue length specifiable by listen.
//

  SOMAXCONN = $7fffffff;
  {$EXTERNALSYM SOMAXCONN}

  MSG_OOB       = $1; // process out-of-band data
  {$EXTERNALSYM MSG_OOB}
  MSG_PEEK      = $2; // peek at incoming message
  {$EXTERNALSYM MSG_PEEK}
  MSG_DONTROUTE = $4; // send without using routing tables
  {$EXTERNALSYM MSG_DONTROUTE}

  MSG_PARTIAL   = $8000; // partial send or recv for message xport
  {$EXTERNALSYM MSG_PARTIAL}

//
// WinSock 2 extension -- new flags for WSASend(), WSASendTo(), WSARecv() and
//                          WSARecvFrom()
//

  MSG_INTERRUPT = $10; // send/recv in the interrupt context
  {$EXTERNALSYM MSG_INTERRUPT}

  MSG_MAXIOVLEN = 16;
  {$EXTERNALSYM MSG_MAXIOVLEN}

//
// Define constant based on rfc883, used by gethostbyxxxx() calls.
//

  MAXGETHOSTSTRUCT = 1024;
  {$EXTERNALSYM MAXGETHOSTSTRUCT}

//
// WinSock 2 extension -- bit values and indices for FD_XXX network events
//

  FD_READ_BIT                     = 0;
  {$EXTERNALSYM FD_READ_BIT}
  FD_READ                         = (1 shl FD_READ_BIT);
  {$EXTERNALSYM FD_READ}

  FD_WRITE_BIT                    = 1;
  {$EXTERNALSYM FD_WRITE_BIT}
  FD_WRITE                        = (1 shl FD_WRITE_BIT);
  {$EXTERNALSYM FD_WRITE}

  FD_OOB_BIT                      = 2;
  {$EXTERNALSYM FD_OOB_BIT}
  FD_OOB                          = (1 shl FD_OOB_BIT);
  {$EXTERNALSYM FD_OOB}

  FD_ACCEPT_BIT                   = 3;
  {$EXTERNALSYM FD_ACCEPT_BIT}
  FD_ACCEPT                       = (1 shl FD_ACCEPT_BIT);
  {$EXTERNALSYM FD_ACCEPT}

  FD_CONNECT_BIT                  = 4;
  {$EXTERNALSYM FD_CONNECT_BIT}
  FD_CONNECT                      = (1 shl FD_CONNECT_BIT);
  {$EXTERNALSYM FD_CONNECT}

  FD_CLOSE_BIT                    = 5;
  {$EXTERNALSYM FD_CLOSE_BIT}
  FD_CLOSE                        = (1 shl FD_CLOSE_BIT);
  {$EXTERNALSYM FD_CLOSE}

  FD_QOS_BIT                      = 6;
  {$EXTERNALSYM FD_QOS_BIT}
  FD_QOS                          = (1 shl FD_QOS_BIT);
  {$EXTERNALSYM FD_QOS}

  FD_GROUP_QOS_BIT                = 7;
  {$EXTERNALSYM FD_GROUP_QOS_BIT}
  FD_GROUP_QOS                    = (1 shl FD_GROUP_QOS_BIT);
  {$EXTERNALSYM FD_GROUP_QOS}

  FD_ROUTING_INTERFACE_CHANGE_BIT = 8;
  {$EXTERNALSYM FD_ROUTING_INTERFACE_CHANGE_BIT}
  FD_ROUTING_INTERFACE_CHANGE     = (1 shl FD_ROUTING_INTERFACE_CHANGE_BIT);
  {$EXTERNALSYM FD_ROUTING_INTERFACE_CHANGE}

  FD_ADDRESS_LIST_CHANGE_BIT      = 9;
  {$EXTERNALSYM FD_ADDRESS_LIST_CHANGE_BIT}
  FD_ADDRESS_LIST_CHANGE          = (1 shl FD_ADDRESS_LIST_CHANGE_BIT);
  {$EXTERNALSYM FD_ADDRESS_LIST_CHANGE}

  FD_MAX_EVENTS                   = 10;
  {$EXTERNALSYM FD_MAX_EVENTS}
  FD_ALL_EVENTS                   = ((1 shl FD_MAX_EVENTS) - 1);
  {$EXTERNALSYM FD_ALL_EVENTS}

//
// All Windows Sockets error constants are biased by WSABASEERR from
// the "normal"
//

  WSABASEERR = 10000;
  {$EXTERNALSYM WSABASEERR}

//
// Windows Sockets definitions of regular Microsoft C error constants
//

  WSAEINTR  = (WSABASEERR+4);
  {$EXTERNALSYM WSAEINTR}
  WSAEBADF  = (WSABASEERR+9);
  {$EXTERNALSYM WSAEBADF}
  WSAEACCES = (WSABASEERR+13);
  {$EXTERNALSYM WSAEACCES}
  WSAEFAULT = (WSABASEERR+14);
  {$EXTERNALSYM WSAEFAULT}
  WSAEINVAL = (WSABASEERR+22);
  {$EXTERNALSYM WSAEINVAL}
  WSAEMFILE = (WSABASEERR+24);
  {$EXTERNALSYM WSAEMFILE}

//
// Windows Sockets definitions of regular Berkeley error constants
//

  WSAEWOULDBLOCK     = (WSABASEERR+35);
  {$EXTERNALSYM WSAEWOULDBLOCK}
  WSAEINPROGRESS     = (WSABASEERR+36);
  {$EXTERNALSYM WSAEINPROGRESS}
  WSAEALREADY        = (WSABASEERR+37);
  {$EXTERNALSYM WSAEALREADY}
  WSAENOTSOCK        = (WSABASEERR+38);
  {$EXTERNALSYM WSAENOTSOCK}
  WSAEDESTADDRREQ    = (WSABASEERR+39);
  {$EXTERNALSYM WSAEDESTADDRREQ}
  WSAEMSGSIZE        = (WSABASEERR+40);
  {$EXTERNALSYM WSAEMSGSIZE}
  WSAEPROTOTYPE      = (WSABASEERR+41);
  {$EXTERNALSYM WSAEPROTOTYPE}
  WSAENOPROTOOPT     = (WSABASEERR+42);
  {$EXTERNALSYM WSAENOPROTOOPT}
  WSAEPROTONOSUPPORT = (WSABASEERR+43);
  {$EXTERNALSYM WSAEPROTONOSUPPORT}
  WSAESOCKTNOSUPPORT = (WSABASEERR+44);
  {$EXTERNALSYM WSAESOCKTNOSUPPORT}
  WSAEOPNOTSUPP      = (WSABASEERR+45);
  {$EXTERNALSYM WSAEOPNOTSUPP}
  WSAEPFNOSUPPORT    = (WSABASEERR+46);
  {$EXTERNALSYM WSAEPFNOSUPPORT}
  WSAEAFNOSUPPORT    = (WSABASEERR+47);
  {$EXTERNALSYM WSAEAFNOSUPPORT}
  WSAEADDRINUSE      = (WSABASEERR+48);
  {$EXTERNALSYM WSAEADDRINUSE}
  WSAEADDRNOTAVAIL   = (WSABASEERR+49);
  {$EXTERNALSYM WSAEADDRNOTAVAIL}
  WSAENETDOWN        = (WSABASEERR+50);
  {$EXTERNALSYM WSAENETDOWN}
  WSAENETUNREACH     = (WSABASEERR+51);
  {$EXTERNALSYM WSAENETUNREACH}
  WSAENETRESET       = (WSABASEERR+52);
  {$EXTERNALSYM WSAENETRESET}
  WSAECONNABORTED    = (WSABASEERR+53);
  {$EXTERNALSYM WSAECONNABORTED}
  WSAECONNRESET      = (WSABASEERR+54);
  {$EXTERNALSYM WSAECONNRESET}
  WSAENOBUFS         = (WSABASEERR+55);
  {$EXTERNALSYM WSAENOBUFS}
  WSAEISCONN         = (WSABASEERR+56);
  {$EXTERNALSYM WSAEISCONN}
  WSAENOTCONN        = (WSABASEERR+57);
  {$EXTERNALSYM WSAENOTCONN}
  WSAESHUTDOWN       = (WSABASEERR+58);
  {$EXTERNALSYM WSAESHUTDOWN}
  WSAETOOMANYREFS    = (WSABASEERR+59);
  {$EXTERNALSYM WSAETOOMANYREFS}
  WSAETIMEDOUT       = (WSABASEERR+60);
  {$EXTERNALSYM WSAETIMEDOUT}
  WSAECONNREFUSED    = (WSABASEERR+61);
  {$EXTERNALSYM WSAECONNREFUSED}
  WSAELOOP           = (WSABASEERR+62);
  {$EXTERNALSYM WSAELOOP}
  WSAENAMETOOLONG    = (WSABASEERR+63);
  {$EXTERNALSYM WSAENAMETOOLONG}
  WSAEHOSTDOWN       = (WSABASEERR+64);
  {$EXTERNALSYM WSAEHOSTDOWN}
  WSAEHOSTUNREACH    = (WSABASEERR+65);
  {$EXTERNALSYM WSAEHOSTUNREACH}
  WSAENOTEMPTY       = (WSABASEERR+66);
  {$EXTERNALSYM WSAENOTEMPTY}
  WSAEPROCLIM        = (WSABASEERR+67);
  {$EXTERNALSYM WSAEPROCLIM}
  WSAEUSERS          = (WSABASEERR+68);
  {$EXTERNALSYM WSAEUSERS}
  WSAEDQUOT          = (WSABASEERR+69);
  {$EXTERNALSYM WSAEDQUOT}
  WSAESTALE          = (WSABASEERR+70);
  {$EXTERNALSYM WSAESTALE}
  WSAEREMOTE         = (WSABASEERR+71);
  {$EXTERNALSYM WSAEREMOTE}

//
// Extended Windows Sockets error constant definitions
//

  WSASYSNOTREADY         = (WSABASEERR+91);
  {$EXTERNALSYM WSASYSNOTREADY}
  WSAVERNOTSUPPORTED     = (WSABASEERR+92);
  {$EXTERNALSYM WSAVERNOTSUPPORTED}
  WSANOTINITIALISED      = (WSABASEERR+93);
  {$EXTERNALSYM WSANOTINITIALISED}
  WSAEDISCON             = (WSABASEERR+101);
  {$EXTERNALSYM WSAEDISCON}
  WSAENOMORE             = (WSABASEERR+102);
  {$EXTERNALSYM WSAENOMORE}
  WSAECANCELLED          = (WSABASEERR+103);
  {$EXTERNALSYM WSAECANCELLED}
  WSAEINVALIDPROCTABLE   = (WSABASEERR+104);
  {$EXTERNALSYM WSAEINVALIDPROCTABLE}
  WSAEINVALIDPROVIDER    = (WSABASEERR+105);
  {$EXTERNALSYM WSAEINVALIDPROVIDER}
  WSAEPROVIDERFAILEDINIT = (WSABASEERR+106);
  {$EXTERNALSYM WSAEPROVIDERFAILEDINIT}
  WSASYSCALLFAILURE      = (WSABASEERR+107);
  {$EXTERNALSYM WSASYSCALLFAILURE}
  WSASERVICE_NOT_FOUND   = (WSABASEERR+108);
  {$EXTERNALSYM WSASERVICE_NOT_FOUND}
  WSATYPE_NOT_FOUND      = (WSABASEERR+109);
  {$EXTERNALSYM WSATYPE_NOT_FOUND}
  WSA_E_NO_MORE          = (WSABASEERR+110);
  {$EXTERNALSYM WSA_E_NO_MORE}
  WSA_E_CANCELLED        = (WSABASEERR+111);
  {$EXTERNALSYM WSA_E_CANCELLED}
  WSAEREFUSED            = (WSABASEERR+112);
  {$EXTERNALSYM WSAEREFUSED}

//
// Error return codes from gethostbyname() and gethostbyaddr()
// (when using the resolver). Note that these errors are
// retrieved via WSAGetLastError() and must therefore follow
// the rules for avoiding clashes with error numbers from
// specific implementations or language run-time systems.
// For this reason the codes are based at WSABASEERR+1001.
// Note also that [WSA]NO_ADDRESS is defined only for
// compatibility purposes.
//

// Authoritative Answer: Host not found

  WSAHOST_NOT_FOUND = (WSABASEERR+1001);
  {$EXTERNALSYM WSAHOST_NOT_FOUND}

// Non-Authoritative: Host not found, or SERVERFAIL

  WSATRY_AGAIN = (WSABASEERR+1002);
  {$EXTERNALSYM WSATRY_AGAIN}

// Non-recoverable errors, FORMERR, REFUSED, NOTIMP

  WSANO_RECOVERY = (WSABASEERR+1003);
  {$EXTERNALSYM WSANO_RECOVERY}

// Valid name, no data record of requested type

  WSANO_DATA = (WSABASEERR+1004);
  {$EXTERNALSYM WSANO_DATA}

//
// Define QOS related error return codes
//
//

  WSA_QOS_RECEIVERS          = (WSABASEERR + 1005); // at least one Reserve has arrived
  {$EXTERNALSYM WSA_QOS_RECEIVERS}
  WSA_QOS_SENDERS            = (WSABASEERR + 1006); // at least one Path has arrived
  {$EXTERNALSYM WSA_QOS_SENDERS}
  WSA_QOS_NO_SENDERS         = (WSABASEERR + 1007); // there are no senders
  {$EXTERNALSYM WSA_QOS_NO_SENDERS}
  WSA_QOS_NO_RECEIVERS       = (WSABASEERR + 1008); // there are no receivers
  {$EXTERNALSYM WSA_QOS_NO_RECEIVERS}
  WSA_QOS_REQUEST_CONFIRMED  = (WSABASEERR + 1009); // Reserve has been confirmed
  {$EXTERNALSYM WSA_QOS_REQUEST_CONFIRMED}
  WSA_QOS_ADMISSION_FAILURE  = (WSABASEERR + 1010); // error due to lack of resources
  {$EXTERNALSYM WSA_QOS_ADMISSION_FAILURE}
  WSA_QOS_POLICY_FAILURE     = (WSABASEERR + 1011); // rejected for administrative reasons - bad credentials
  {$EXTERNALSYM WSA_QOS_POLICY_FAILURE}
  WSA_QOS_BAD_STYLE          = (WSABASEERR + 1012); // unknown or conflicting style
  {$EXTERNALSYM WSA_QOS_BAD_STYLE}
  WSA_QOS_BAD_OBJECT         = (WSABASEERR + 1013); // problem with some part of the filterspec or providerspecific buffer in general
  {$EXTERNALSYM WSA_QOS_BAD_OBJECT}
  WSA_QOS_TRAFFIC_CTRL_ERROR = (WSABASEERR + 1014); // problem with some part of the flowspec
  {$EXTERNALSYM WSA_QOS_TRAFFIC_CTRL_ERROR}
  WSA_QOS_GENERIC_ERROR      = (WSABASEERR + 1015); // general error
  {$EXTERNALSYM WSA_QOS_GENERIC_ERROR}
  WSA_QOS_ESERVICETYPE       = (WSABASEERR + 1016); // invalid service type in flowspec
  {$EXTERNALSYM WSA_QOS_ESERVICETYPE}
  WSA_QOS_EFLOWSPEC          = (WSABASEERR + 1017); // invalid flowspec
  {$EXTERNALSYM WSA_QOS_EFLOWSPEC}
  WSA_QOS_EPROVSPECBUF       = (WSABASEERR + 1018); // invalid provider specific buffer
  {$EXTERNALSYM WSA_QOS_EPROVSPECBUF}
  WSA_QOS_EFILTERSTYLE       = (WSABASEERR + 1019); // invalid filter style
  {$EXTERNALSYM WSA_QOS_EFILTERSTYLE}
  WSA_QOS_EFILTERTYPE        = (WSABASEERR + 1020); // invalid filter type
  {$EXTERNALSYM WSA_QOS_EFILTERTYPE}
  WSA_QOS_EFILTERCOUNT       = (WSABASEERR + 1021); // incorrect number of filters
  {$EXTERNALSYM WSA_QOS_EFILTERCOUNT}
  WSA_QOS_EOBJLENGTH         = (WSABASEERR + 1022); // invalid object length
  {$EXTERNALSYM WSA_QOS_EOBJLENGTH}
  WSA_QOS_EFLOWCOUNT         = (WSABASEERR + 1023); // incorrect number of flows
  {$EXTERNALSYM WSA_QOS_EFLOWCOUNT}
  WSA_QOS_EUNKOWNPSOBJ       = (WSABASEERR + 1024); // unknown object in provider specific buffer
  {$EXTERNALSYM WSA_QOS_EUNKOWNPSOBJ}
  WSA_QOS_EPOLICYOBJ         = (WSABASEERR + 1025); // invalid policy object in provider specific buffer
  {$EXTERNALSYM WSA_QOS_EPOLICYOBJ}
  WSA_QOS_EFLOWDESC          = (WSABASEERR + 1026); // invalid flow descriptor in the list
  {$EXTERNALSYM WSA_QOS_EFLOWDESC}
  WSA_QOS_EPSFLOWSPEC        = (WSABASEERR + 1027); // inconsistent flow spec in provider specific buffer
  {$EXTERNALSYM WSA_QOS_EPSFLOWSPEC}
  WSA_QOS_EPSFILTERSPEC      = (WSABASEERR + 1028); // invalid filter spec in provider specific buffer
  {$EXTERNALSYM WSA_QOS_EPSFILTERSPEC}
  WSA_QOS_ESDMODEOBJ         = (WSABASEERR + 1029); // invalid shape discard mode object in provider specific buffer
  {$EXTERNALSYM WSA_QOS_ESDMODEOBJ}
  WSA_QOS_ESHAPERATEOBJ      = (WSABASEERR + 1030); // invalid shaping rate object in provider specific buffer
  {$EXTERNALSYM WSA_QOS_ESHAPERATEOBJ}
  WSA_QOS_RESERVED_PETYPE    = (WSABASEERR + 1031); // reserved policy element in provider specific buffer
  {$EXTERNALSYM WSA_QOS_RESERVED_PETYPE}

//
// Compatibility macros.
//

function h_errno: Integer;
{$EXTERNALSYM h_errno}

const
  HOST_NOT_FOUND = WSAHOST_NOT_FOUND;
  {$EXTERNALSYM HOST_NOT_FOUND}
  TRY_AGAIN      = WSATRY_AGAIN;
  {$EXTERNALSYM TRY_AGAIN}
  NO_RECOVERY    = WSANO_RECOVERY;
  {$EXTERNALSYM NO_RECOVERY}
  NO_DATA        = WSANO_DATA;
  {$EXTERNALSYM NO_DATA}

// no address, look for MX record

  WSANO_ADDRESS = WSANO_DATA;
  {$EXTERNALSYM WSANO_ADDRESS}
  NO_ADDRESS    = WSANO_ADDRESS;
  {$EXTERNALSYM NO_ADDRESS}

//
// Windows Sockets errors redefined as regular Berkeley error constants.
// These are commented out in Windows NT to avoid conflicts with errno.h.
// Use the WSA constants instead.
//

{$IFDEF FALSE}

const
  EWOULDBLOCK     = WSAEWOULDBLOCK;
  {$EXTERNALSYM EWOULDBLOCK}
  EINPROGRESS     = WSAEINPROGRESS;
  {$EXTERNALSYM EINPROGRESS}
  EALREADY        = WSAEALREADY;
  {$EXTERNALSYM EALREADY}
  ENOTSOCK        = WSAENOTSOCK;
  {$EXTERNALSYM ENOTSOCK}
  EDESTADDRREQ    = WSAEDESTADDRREQ;
  {$EXTERNALSYM EDESTADDRREQ}
  EMSGSIZE        = WSAEMSGSIZE;
  {$EXTERNALSYM EMSGSIZE}
  EPROTOTYPE      = WSAEPROTOTYPE;
  {$EXTERNALSYM EPROTOTYPE}
  ENOPROTOOPT     = WSAENOPROTOOPT;
  {$EXTERNALSYM ENOPROTOOPT}
  EPROTONOSUPPORT = WSAEPROTONOSUPPORT;
  {$EXTERNALSYM EPROTONOSUPPORT}
  ESOCKTNOSUPPORT = WSAESOCKTNOSUPPORT;
  {$EXTERNALSYM ESOCKTNOSUPPORT}
  EOPNOTSUPP      = WSAEOPNOTSUPP;
  {$EXTERNALSYM EOPNOTSUPP}
  EPFNOSUPPORT    = WSAEPFNOSUPPORT;
  {$EXTERNALSYM EPFNOSUPPORT}
  EAFNOSUPPORT    = WSAEAFNOSUPPORT;
  {$EXTERNALSYM EAFNOSUPPORT}
  EADDRINUSE      = WSAEADDRINUSE;
  {$EXTERNALSYM EADDRINUSE}
  EADDRNOTAVAIL   = WSAEADDRNOTAVAIL;
  {$EXTERNALSYM EADDRNOTAVAIL}
  ENETDOWN        = WSAENETDOWN;
  {$EXTERNALSYM ENETDOWN}
  ENETUNREACH     = WSAENETUNREACH;
  {$EXTERNALSYM ENETUNREACH}
  ENETRESET       = WSAENETRESET;
  {$EXTERNALSYM ENETRESET}
  ECONNABORTED    = WSAECONNABORTED;
  {$EXTERNALSYM ECONNABORTED}
  ECONNRESET      = WSAECONNRESET;
  {$EXTERNALSYM ECONNRESET}
  ENOBUFS         = WSAENOBUFS;
  {$EXTERNALSYM ENOBUFS}
  EISCONN         = WSAEISCONN;
  {$EXTERNALSYM EISCONN}
  ENOTCONN        = WSAENOTCONN;
  {$EXTERNALSYM ENOTCONN}
  ESHUTDOWN       = WSAESHUTDOWN;
  {$EXTERNALSYM ESHUTDOWN}
  ETOOMANYREFS    = WSAETOOMANYREFS;
  {$EXTERNALSYM ETOOMANYREFS}
  ETIMEDOUT       = WSAETIMEDOUT;
  {$EXTERNALSYM ETIMEDOUT}
  ECONNREFUSED    = WSAECONNREFUSED;
  {$EXTERNALSYM ECONNREFUSED}
  ELOOP           = WSAELOOP;
  {$EXTERNALSYM ELOOP}
  ENAMETOOLONG    = WSAENAMETOOLONG;
  {$EXTERNALSYM ENAMETOOLONG}
  EHOSTDOWN       = WSAEHOSTDOWN;
  {$EXTERNALSYM EHOSTDOWN}
  EHOSTUNREACH    = WSAEHOSTUNREACH;
  {$EXTERNALSYM EHOSTUNREACH}
  ENOTEMPTY       = WSAENOTEMPTY;
  {$EXTERNALSYM ENOTEMPTY}
  EPROCLIM        = WSAEPROCLIM;
  {$EXTERNALSYM EPROCLIM}
  EUSERS          = WSAEUSERS;
  {$EXTERNALSYM EUSERS}
  EDQUOT          = WSAEDQUOT;
  {$EXTERNALSYM EDQUOT}
  ESTALE          = WSAESTALE;
  {$EXTERNALSYM ESTALE}
  EREMOTE         = WSAEREMOTE;
  {$EXTERNALSYM EREMOTE}

{$ENDIF}

//
// WinSock 2 extension -- new error codes and type definition
//

type
  WSAEVENT = HANDLE;
  {$EXTERNALSYM WSAEVENT}
  LPWSAEVENT = LPHANDLE;
  {$EXTERNALSYM LPWSAEVENT}
  WSAOVERLAPPED = OVERLAPPED;
  {$EXTERNALSYM WSAOVERLAPPED}
  LPWSAOVERLAPPED = ^OVERLAPPED;
  {$EXTERNALSYM LPWSAOVERLAPPED}
  TWsaEvent = WSAEVENT;
  PWsaEvent = LPWSAEVENT;
  TWsaOverlapped = WSAOVERLAPPED;
  PWsaOverlapped = LPWSAOVERLAPPED;

const
  WSA_IO_PENDING        = (ERROR_IO_PENDING);
  {$EXTERNALSYM WSA_IO_PENDING}
  WSA_IO_INCOMPLETE     = (ERROR_IO_INCOMPLETE);
  {$EXTERNALSYM WSA_IO_INCOMPLETE}
  WSA_INVALID_HANDLE    = (ERROR_INVALID_HANDLE);
  {$EXTERNALSYM WSA_INVALID_HANDLE}
  WSA_INVALID_PARAMETER = (ERROR_INVALID_PARAMETER);
  {$EXTERNALSYM WSA_INVALID_PARAMETER}
  WSA_NOT_ENOUGH_MEMORY = (ERROR_NOT_ENOUGH_MEMORY);
  {$EXTERNALSYM WSA_NOT_ENOUGH_MEMORY}
  WSA_OPERATION_ABORTED = (ERROR_OPERATION_ABORTED);
  {$EXTERNALSYM WSA_OPERATION_ABORTED}

  WSA_INVALID_EVENT       = WSAEVENT(nil);
  {$EXTERNALSYM WSA_INVALID_EVENT}
  WSA_MAXIMUM_WAIT_EVENTS = (MAXIMUM_WAIT_OBJECTS);
  {$EXTERNALSYM WSA_MAXIMUM_WAIT_EVENTS}
  WSA_WAIT_FAILED         = (WAIT_FAILED);
  {$EXTERNALSYM WSA_WAIT_FAILED}
  WSA_WAIT_EVENT_0        = (WAIT_OBJECT_0);
  {$EXTERNALSYM WSA_WAIT_EVENT_0}
  WSA_WAIT_IO_COMPLETION  = (WAIT_IO_COMPLETION);
  {$EXTERNALSYM WSA_WAIT_IO_COMPLETION}
  WSA_WAIT_TIMEOUT        = (WAIT_TIMEOUT);
  {$EXTERNALSYM WSA_WAIT_TIMEOUT}
  WSA_INFINITE            = (INFINITE);
  {$EXTERNALSYM WSA_INFINITE}

//
// WinSock 2 extension -- WSABUF and QOS struct, include qos.h
// to pull in FLOWSPEC and related definitions
//

type
  _WSABUF = record
    len: u_long;     // the length of the buffer
    buf: PChar;      // the pointer to the buffer
  end;
  {$EXTERNALSYM _WSABUF}
  WSABUF = _WSABUF;
  {$EXTERNALSYM WSABUF}
  LPWSABUF = ^_WSABUF;
  {$EXTERNALSYM LPWSABUF}
  TWsaBuf = WSABUF;
  PWsaBuf = LPWSABUF;

  _QualityOfService = record
    SendingFlowspec: FLOWSPEC;       // the flow spec for data sending
    ReceivingFlowspec: FLOWSPEC;     // the flow spec for data receiving
    ProviderSpecific: WSABUF;        // additional provider specific stuff
  end;
  {$EXTERNALSYM _QualityOfService}
  QOS = _QualityOfService;
  {$EXTERNALSYM QOS}
  LPQOS = ^_QualityOfService;
  {$EXTERNALSYM LPQOS}
  TQOS = QOS;
  PQOS = LPQOS;

//
// WinSock 2 extension -- manifest constants for return values of the condition function
//

const
  CF_ACCEPT = $0000;
  {$EXTERNALSYM CF_ACCEPT}
  CF_REJECT = $0001;
  {$EXTERNALSYM CF_REJECT}
  CF_DEFER  = $0002;
  {$EXTERNALSYM CF_DEFER}

//
// WinSock 2 extension -- manifest constants for shutdown()
//

  SD_RECEIVE = $00;
  {$EXTERNALSYM SD_RECEIVE}
  SD_SEND    = $01;
  {$EXTERNALSYM SD_SEND}
  SD_BOTH    = $02;
  {$EXTERNALSYM SD_BOTH}

//
// WinSock 2 extension -- data type and manifest constants for socket groups
//

type
  GROUP = Cardinal;
  {$EXTERNALSYM GROUP}
  TGroup = GROUP;
  PGroup = ^GROUP;

const
  SG_UNCONSTRAINED_GROUP = $01;
  {$EXTERNALSYM SG_UNCONSTRAINED_GROUP}
  SG_CONSTRAINED_GROUP   = $02;
  {$EXTERNALSYM SG_CONSTRAINED_GROUP}

//
// WinSock 2 extension -- data type for WSAEnumNetworkEvents()
//

type
  _WSANETWORKEVENTS = record
    lNetworkEvents: Longint;
    iErrorCode: array [0..FD_MAX_EVENTS - 1] of Integer;
  end;
  {$EXTERNALSYM _WSANETWORKEVENTS}
  WSANETWORKEVENTS = _WSANETWORKEVENTS;
  {$EXTERNALSYM WSANETWORKEVENTS}
  LPWSANETWORKEVENTS = ^WSANETWORKEVENTS;
  {$EXTERNALSYM LPWSANETWORKEVENTS}
  TWsaNetworkEvents = WSANETWORKEVENTS;
  PWsaNetworkEvents = LPWSANETWORKEVENTS;

//
// WinSock 2 extension -- WSAPROTOCOL_INFO structure and associated
// manifest constants
//

const
  MAX_PROTOCOL_CHAIN = 7;
  {$EXTERNALSYM MAX_PROTOCOL_CHAIN}

  BASE_PROTOCOL    = 1;
  {$EXTERNALSYM BASE_PROTOCOL}
  LAYERED_PROTOCOL = 0;
  {$EXTERNALSYM LAYERED_PROTOCOL}

type
  _WSAPROTOCOLCHAIN = record
    ChainLen: Integer;                            // the length of the chain,
                                                  // length = 0 means layered protocol,
                                                  // length = 1 means base protocol,
                                                  // length > 1 means protocol chain
    ChainEntries: array [0..MAX_PROTOCOL_CHAIN - 1] of DWORD; // a list of dwCatalogEntryIds
  end;
  {$EXTERNALSYM _WSAPROTOCOLCHAIN}
  WSAPROTOCOLCHAIN = _WSAPROTOCOLCHAIN;
  {$EXTERNALSYM WSAPROTOCOLCHAIN}
  LPWSAPROTOCOLCHAIN = ^WSAPROTOCOLCHAIN;
  {$EXTERNALSYM LPWSAPROTOCOLCHAIN}
  TWsaProtocolChain = WSAPROTOCOLCHAIN;
  PWsaProtocolChain = LPWSAPROTOCOLCHAIN;

const
  WSAPROTOCOL_LEN = 255;
  {$EXTERNALSYM WSAPROTOCOL_LEN}

type
  _WSAPROTOCOL_INFOA = record
    dwServiceFlags1: DWORD;
    dwServiceFlags2: DWORD;
    dwServiceFlags3: DWORD;
    dwServiceFlags4: DWORD;
    dwProviderFlags: DWORD;
    ProviderId: TGUID;
    dwCatalogEntryId: DWORD;
    ProtocolChain: WSAPROTOCOLCHAIN;
    iVersion: Integer;
    iAddressFamily: Integer;
    iMaxSockAddr: Integer;
    iMinSockAddr: Integer;
    iSocketType: Integer;
    iProtocol: Integer;
    iProtocolMaxOffset: Integer;
    iNetworkByteOrder: Integer;
    iSecurityScheme: Integer;
    dwMessageSize: DWORD;
    dwProviderReserved: DWORD;
    szProtocol: array [0..WSAPROTOCOL_LEN] of Char;
  end;
  {$EXTERNALSYM _WSAPROTOCOL_INFOA}
  WSAPROTOCOL_INFOA = _WSAPROTOCOL_INFOA;
  {$EXTERNALSYM WSAPROTOCOL_INFOA}
  LPWSAPROTOCOL_INFOA = ^WSAPROTOCOL_INFOA;
  {$EXTERNALSYM LPWSAPROTOCOL_INFOA}
  TWsaProtocolInfoA = WSAPROTOCOL_INFOA;
  PWsaProtocolInfoA = LPWSAPROTOCOL_INFOA;

  _WSAPROTOCOL_INFOW = record
    dwServiceFlags1: DWORD;
    dwServiceFlags2: DWORD;
    dwServiceFlags3: DWORD;
    dwServiceFlags4: DWORD;
    dwProviderFlags: DWORD;
    ProviderId: TGUID;
    dwCatalogEntryId: DWORD;
    ProtocolChain: WSAPROTOCOLCHAIN;
    iVersion: Integer;
    iAddressFamily: Integer;
    iMaxSockAddr: Integer;
    iMinSockAddr: Integer;
    iSocketType: Integer;
    iProtocol: Integer;
    iProtocolMaxOffset: Integer;
    iNetworkByteOrder: Integer;
    iSecurityScheme: Integer;
    dwMessageSize: DWORD;
    dwProviderReserved: DWORD;
    szProtocol: array [0..WSAPROTOCOL_LEN] of WideChar;
  end;
  {$EXTERNALSYM _WSAPROTOCOL_INFOW}
  WSAPROTOCOL_INFOW = _WSAPROTOCOL_INFOW;
  {$EXTERNALSYM WSAPROTOCOL_INFOW}
  LPWSAPROTOCOL_INFOW = ^WSAPROTOCOL_INFOW;
  {$EXTERNALSYM LPWSAPROTOCOL_INFOW}
  TWsaProtocolInfoW = WSAPROTOCOL_INFOW;
  PWsaProtocolInfoW = LPWSAPROTOCOL_INFOW;

{$IFDEF UNICODE}
  WSAPROTOCOL_INFO = WSAPROTOCOL_INFOW;
  {$EXTERNALSYM WSAPROTOCOL_INFO}
  LPWSAPROTOCOL_INFO = LPWSAPROTOCOL_INFOW;
  {$EXTERNALSYM LPWSAPROTOCOL_INFO}
  TWsaProtocolInfo = TWsaProtocolInfoW;
  PWsaProtocolInfo = PWsaProtocolInfoW;
{$ELSE}
  WSAPROTOCOL_INFO = WSAPROTOCOL_INFOA;
  {$EXTERNALSYM WSAPROTOCOL_INFO}
  LPWSAPROTOCOL_INFO = LPWSAPROTOCOL_INFOA;
  {$EXTERNALSYM LPWSAPROTOCOL_INFO}
  TWsaProtocolInfo = TWsaProtocolInfoA;
  PWsaProtocolInfo = PWsaProtocolInfoA;
{$ENDIF}

// Flag bit definitions for dwProviderFlags

const
  PFL_MULTIPLE_PROTO_ENTRIES  = $00000001;
  {$EXTERNALSYM PFL_MULTIPLE_PROTO_ENTRIES}
  PFL_RECOMMENDED_PROTO_ENTRY = $00000002;
  {$EXTERNALSYM PFL_RECOMMENDED_PROTO_ENTRY}
  PFL_HIDDEN                  = $00000004;
  {$EXTERNALSYM PFL_HIDDEN}
  PFL_MATCHES_PROTOCOL_ZERO   = $00000008;
  {$EXTERNALSYM PFL_MATCHES_PROTOCOL_ZERO}

// Flag bit definitions for dwServiceFlags1

  XP1_CONNECTIONLESS           = $00000001;
  {$EXTERNALSYM XP1_CONNECTIONLESS}
  XP1_GUARANTEED_DELIVERY      = $00000002;
  {$EXTERNALSYM XP1_GUARANTEED_DELIVERY}
  XP1_GUARANTEED_ORDER         = $00000004;
  {$EXTERNALSYM XP1_GUARANTEED_ORDER}
  XP1_MESSAGE_ORIENTED         = $00000008;
  {$EXTERNALSYM XP1_MESSAGE_ORIENTED}
  XP1_PSEUDO_STREAM            = $00000010;
  {$EXTERNALSYM XP1_PSEUDO_STREAM}
  XP1_GRACEFUL_CLOSE           = $00000020;
  {$EXTERNALSYM XP1_GRACEFUL_CLOSE}
  XP1_EXPEDITED_DATA           = $00000040;
  {$EXTERNALSYM XP1_EXPEDITED_DATA}
  XP1_CONNECT_DATA             = $00000080;
  {$EXTERNALSYM XP1_CONNECT_DATA}
  XP1_DISCONNECT_DATA          = $00000100;
  {$EXTERNALSYM XP1_DISCONNECT_DATA}
  XP1_SUPPORT_BROADCAST        = $00000200;
  {$EXTERNALSYM XP1_SUPPORT_BROADCAST}
  XP1_SUPPORT_MULTIPOINT       = $00000400;
  {$EXTERNALSYM XP1_SUPPORT_MULTIPOINT}
  XP1_MULTIPOINT_CONTROL_PLANE = $00000800;
  {$EXTERNALSYM XP1_MULTIPOINT_CONTROL_PLANE}
  XP1_MULTIPOINT_DATA_PLANE    = $00001000;
  {$EXTERNALSYM XP1_MULTIPOINT_DATA_PLANE}
  XP1_QOS_SUPPORTED            = $00002000;
  {$EXTERNALSYM XP1_QOS_SUPPORTED}
  XP1_INTERRUPT                = $00004000;
  {$EXTERNALSYM XP1_INTERRUPT}
  XP1_UNI_SEND                 = $00008000;
  {$EXTERNALSYM XP1_UNI_SEND}
  XP1_UNI_RECV                 = $00010000;
  {$EXTERNALSYM XP1_UNI_RECV}
  XP1_IFS_HANDLES              = $00020000;
  {$EXTERNALSYM XP1_IFS_HANDLES}
  XP1_PARTIAL_MESSAGE          = $00040000;
  {$EXTERNALSYM XP1_PARTIAL_MESSAGE}

  BIGENDIAN    = $0000;
  {$EXTERNALSYM BIGENDIAN}
  LITTLEENDIAN = $0001;
  {$EXTERNALSYM LITTLEENDIAN}

  SECURITY_PROTOCOL_NONE = $0000;
  {$EXTERNALSYM SECURITY_PROTOCOL_NONE}

//
// WinSock 2 extension -- manifest constants for WSAJoinLeaf()
//

  JL_SENDER_ONLY   = $01;
  {$EXTERNALSYM JL_SENDER_ONLY}
  JL_RECEIVER_ONLY = $02;
  {$EXTERNALSYM JL_RECEIVER_ONLY}
  JL_BOTH          = $04;
  {$EXTERNALSYM JL_BOTH}

//
// WinSock 2 extension -- manifest constants for WSASocket()
//

  WSA_FLAG_OVERLAPPED        = $01;
  {$EXTERNALSYM WSA_FLAG_OVERLAPPED}
  WSA_FLAG_MULTIPOINT_C_ROOT = $02;
  {$EXTERNALSYM WSA_FLAG_MULTIPOINT_C_ROOT}
  WSA_FLAG_MULTIPOINT_C_LEAF = $04;
  {$EXTERNALSYM WSA_FLAG_MULTIPOINT_C_LEAF}
  WSA_FLAG_MULTIPOINT_D_ROOT = $08;
  {$EXTERNALSYM WSA_FLAG_MULTIPOINT_D_ROOT}
  WSA_FLAG_MULTIPOINT_D_LEAF = $10;
  {$EXTERNALSYM WSA_FLAG_MULTIPOINT_D_LEAF}

//
// WinSock 2 extension -- manifest constants for WSAIoctl()
//

  IOC_UNIX     = $00000000;
  {$EXTERNALSYM IOC_UNIX}
  IOC_WS2      = $08000000;
  {$EXTERNALSYM IOC_WS2}
  IOC_PROTOCOL = $10000000;
  {$EXTERNALSYM IOC_PROTOCOL}
  IOC_VENDOR   = $18000000;
  {$EXTERNALSYM IOC_VENDOR}

function _WSAIO(x, y: DWORD): DWORD;
{$EXTERNALSYM _WSAIO}

function _WSAIOR(x, y: DWORD): DWORD;
{$EXTERNALSYM _WSAIOR}

function _WSAIOW(x, y: DWORD): DWORD;
{$EXTERNALSYM _WSAIOW}

function _WSAIORW(x, y: DWORD): DWORD;
{$EXTERNALSYM _WSAIORW}

const
  SIO_ASSOCIATE_HANDLE          = IOC_INOUT or IOC_WS2 or 1;
  {$EXTERNALSYM SIO_ASSOCIATE_HANDLE}
  SIO_ENABLE_CIRCULAR_QUEUEING  = IOC_VOID or IOC_WS2 or 2;
  {$EXTERNALSYM SIO_ENABLE_CIRCULAR_QUEUEING}
  SIO_FIND_ROUTE                = IOC_OUT or IOC_WS2 or 3;
  {$EXTERNALSYM SIO_FIND_ROUTE}
  SIO_FLUSH                     = IOC_VOID or IOC_WS2 or 4;
  {$EXTERNALSYM SIO_FLUSH}
  SIO_GET_BROADCAST_ADDRESS     = IOC_OUT or IOC_WS2 or 5;
  {$EXTERNALSYM SIO_GET_BROADCAST_ADDRESS}
  SIO_GET_EXTENSION_FUNCTION_POINTER = IOC_INOUT or IOC_WS2 or 6;
  {$EXTERNALSYM SIO_GET_EXTENSION_FUNCTION_POINTER}
  SIO_GET_QOS                   = IOC_INOUT or IOC_WS2 or 7;
  {$EXTERNALSYM SIO_GET_QOS}
  SIO_GET_GROUP_QOS             = IOC_INOUT or IOC_WS2 or 8;
  {$EXTERNALSYM SIO_GET_GROUP_QOS}
  SIO_MULTIPOINT_LOOPBACK       = IOC_INOUT or IOC_WS2 or 9;
  {$EXTERNALSYM SIO_MULTIPOINT_LOOPBACK}
  SIO_MULTICAST_SCOPE           = IOC_INOUT or IOC_WS2 or 10;
  {$EXTERNALSYM SIO_MULTICAST_SCOPE}
  SIO_SET_QOS                   = IOC_INOUT or IOC_WS2 or 11;
  {$EXTERNALSYM SIO_SET_QOS}
  SIO_SET_GROUP_QOS             = IOC_INOUT or IOC_WS2 or 12;
  {$EXTERNALSYM SIO_SET_GROUP_QOS}
  SIO_TRANSLATE_HANDLE          = IOC_INOUT or IOC_WS2 or 13;
  {$EXTERNALSYM SIO_TRANSLATE_HANDLE}
  SIO_ROUTING_INTERFACE_QUERY   = IOC_INOUT or IOC_WS2 or 20;
  {$EXTERNALSYM SIO_ROUTING_INTERFACE_QUERY}
  SIO_ROUTING_INTERFACE_CHANGE  = IOC_INOUT or IOC_WS2 or 21;
  {$EXTERNALSYM SIO_ROUTING_INTERFACE_CHANGE}
  SIO_ADDRESS_LIST_QUERY        = IOC_OUT or IOC_WS2 or 22;
  {$EXTERNALSYM SIO_ADDRESS_LIST_QUERY}
  SIO_ADDRESS_LIST_CHANGE       = IOC_VOID or IOC_WS2 or 23;
  {$EXTERNALSYM SIO_ADDRESS_LIST_CHANGE}
  SIO_QUERY_TARGET_PNP_HANDLE   = IOC_OUT or IOC_WS2 or 24;
  {$EXTERNALSYM SIO_QUERY_TARGET_PNP_HANDLE}

  SIO_ADDRESS_LIST_SORT         = IOC_INOUT or IOC_WS2 or 25;
  {$EXTERNALSYM SIO_ADDRESS_LIST_SORT}

//
// WinSock 2 extensions -- data types for the condition function in
// WSAAccept() and overlapped I/O completion routine.
//

type
  LPCONDITIONPROC = function (lpCallerId, lpCallerData: LPWSABUF; lpSQOS, lpGQOS: LPQOS; lpCalleeId, lpCalleeData: LPWSABUF;
    g: PGROUP; dwCallbackData: DWORD_PTR): Integer; stdcall;
  {$EXTERNALSYM LPCONDITIONPROC}

  LPWSAOVERLAPPED_COMPLETION_ROUTINE = procedure (dwError, cbTransferred: DWORD; lpOverlapped: LPWSAOVERLAPPED; dwFlags: DWORD); stdcall;
  {$EXTERNALSYM LPWSAOVERLAPPED_COMPLETION_ROUTINE}

//
// WinSock 2 extension -- manifest constants and associated structures
// for WSANSPIoctl()
//

const
  SIO_NSP_NOTIFY_CHANGE       = IOC_IN or IOC_WS2 or 25;
  {$EXTERNALSYM SIO_NSP_NOTIFY_CHANGE}

type
  _WSACOMPLETIONTYPE = (
    NSP_NOTIFY_IMMEDIATELY,
    NSP_NOTIFY_HWND,
    NSP_NOTIFY_EVENT,
    NSP_NOTIFY_PORT,
    NSP_NOTIFY_APC);
  {$EXTERNALSYM _WSACOMPLETIONTYPE}
  WSACOMPLETIONTYPE = _WSACOMPLETIONTYPE;
  {$EXTERNALSYM WSACOMPLETIONTYPE}
  PWSACOMPLETIONTYPE = ^WSACOMPLETIONTYPE;
  {$EXTERNALSYM PWSACOMPLETIONTYPE}
  LPWSACOMPLETIONTYPE = ^WSACOMPLETIONTYPE;
  {$EXTERNALSYM LPWSACOMPLETIONTYPE}
  TWsaCompletionType = WSACOMPLETIONTYPE;

  _WSACOMPLETION = record
    Type_: WSACOMPLETIONTYPE;
    case Integer of // Parameters
      0: ( // WindowMessage
        hWnd: HWND;
        uMsg: UINT;
        context: WPARAM);
      (* TODO
      1: ( // Event
        lpOverlapped: LPWSAOVERLAPPED);
      2: ( // Apc
        lpOverlapped: LPWSAOVERLAPPED;
        lpfnCompletionProc: LPWSAOVERLAPPED_COMPLETION_ROUTINE);
      *)
      3: ( // Port
        lpOverlapped: LPWSAOVERLAPPED;
        hPort: HANDLE;
        Key: ULONG_PTR);
  end;
  {$EXTERNALSYM _WSACOMPLETION}
  WSACOMPLETION = _WSACOMPLETION;
  {$EXTERNALSYM WSACOMPLETION}
  PWSACOMPLETION = ^WSACOMPLETION;
  {$EXTERNALSYM PWSACOMPLETION}
  LPWSACOMPLETION = ^WSACOMPLETION;
  {$EXTERNALSYM LPWSACOMPLETION}
  TWsaCompletion = WSACOMPLETION;

//
// WinSock 2 extension -- manifest constants for SIO_TRANSLATE_HANDLE ioctl
//

const
  TH_NETDEV = $00000001;
  {$EXTERNALSYM TH_NETDEV}
  TH_TAPI   = $00000002;
  {$EXTERNALSYM TH_TAPI}

//
// Microsoft Windows Extended data types required for the functions to
// convert   back  and  forth  between  binary  and  string  forms  of
// addresses.
//

type
  LPSOCKADDR = ^sockaddr;
  {$EXTERNALSYM LPSOCKADDR}

  PSOCKADDR_STORAGE = ^sockaddr_storage;
  {$EXTERNALSYM PSOCKADDR_STORAGE}
  LPSOCKADDR_STORAGE = ^sockaddr_storage;
  {$EXTERNALSYM LPSOCKADDR_STORAGE}

//
// Manifest constants and type definitions related to name resolution and
// registration (RNR) API
//

  _BLOB = record
    cbSize: ULONG;
    pBlobData: LPBYTE;
  end;
  {$EXTERNALSYM _BLOB}
  BLOB = _BLOB;
  {$EXTERNALSYM BLOB}
  LPBLOB = ^BLOB;
  {$EXTERNALSYM LPBLOB}
  TBlob = BLOB;
  PBlob = LPBLOB;

//
// Service Install Flags
//

const
  SERVICE_MULTIPLE = ($00000001);
  {$EXTERNALSYM SERVICE_MULTIPLE}

//
//& Name Spaces
//

  NS_ALL = (0);
  {$EXTERNALSYM NS_ALL}

  NS_SAP         = (1);
  {$EXTERNALSYM NS_SAP}
  NS_NDS         = (2);
  {$EXTERNALSYM NS_NDS}
  NS_PEER_BROWSE = (3);
  {$EXTERNALSYM NS_PEER_BROWSE}
  NS_SLP         = (5);
  {$EXTERNALSYM NS_SLP}
  NS_DHCP        = (6);
  {$EXTERNALSYM NS_DHCP}

  NS_TCPIP_LOCAL = (10);
  {$EXTERNALSYM NS_TCPIP_LOCAL}
  NS_TCPIP_HOSTS = (11);
  {$EXTERNALSYM NS_TCPIP_HOSTS}
  NS_DNS         = (12);
  {$EXTERNALSYM NS_DNS}
  NS_NETBT       = (13);
  {$EXTERNALSYM NS_NETBT}
  NS_WINS        = (14);
  {$EXTERNALSYM NS_WINS}
  NS_NLA         = (15);    // Network Location Awareness
  {$EXTERNALSYM NS_NLA}

  NS_NBP = (20);
  {$EXTERNALSYM NS_NBP}

  NS_MS   = (30);
  {$EXTERNALSYM NS_MS}
  NS_STDA = (31);
  {$EXTERNALSYM NS_STDA}
  NS_NTDS = (32);
  {$EXTERNALSYM NS_NTDS}

  NS_X500    = (40);
  {$EXTERNALSYM NS_X500}
  NS_NIS     = (41);
  {$EXTERNALSYM NS_NIS}
  NS_NISPLUS = (42);
  {$EXTERNALSYM NS_NISPLUS}

  NS_WRQ = (50);
  {$EXTERNALSYM NS_WRQ}

  NS_NETDES = (60); // Network Designers Limited
  {$EXTERNALSYM NS_NETDES}

//
// Resolution flags for WSAGetAddressByName().
// Note these are also used by the 1.1 API GetAddressByName, so
// leave them around.
//

  RES_UNUSED_1    = ($00000001);
  {$EXTERNALSYM RES_UNUSED_1}
  RES_FLUSH_CACHE = ($00000002);
  {$EXTERNALSYM RES_FLUSH_CACHE}
  RES_SERVICE = ($00000004);
  {$EXTERNALSYM RES_SERVICE}

//
// Well known value names for Service Types
//

  SERVICE_TYPE_VALUE_IPXPORTA  = 'IpxSocket';
  {$EXTERNALSYM SERVICE_TYPE_VALUE_IPXPORTA}
  SERVICE_TYPE_VALUE_IPXPORTW  = WideString('IpxSocket');
  {$EXTERNALSYM SERVICE_TYPE_VALUE_IPXPORTW}
  SERVICE_TYPE_VALUE_SAPIDA    = 'SapId';
  {$EXTERNALSYM SERVICE_TYPE_VALUE_SAPIDA}
  SERVICE_TYPE_VALUE_SAPIDW    = WideString('SapId');
  {$EXTERNALSYM SERVICE_TYPE_VALUE_SAPIDW}
  SERVICE_TYPE_VALUE_TCPPORTA  = 'TcpPort';
  {$EXTERNALSYM SERVICE_TYPE_VALUE_TCPPORTA}
  SERVICE_TYPE_VALUE_TCPPORTW  = WideString('TcpPort');
  {$EXTERNALSYM SERVICE_TYPE_VALUE_TCPPORTW}
  SERVICE_TYPE_VALUE_UDPPORTA  = 'UdpPort';
  {$EXTERNALSYM SERVICE_TYPE_VALUE_UDPPORTA}
  SERVICE_TYPE_VALUE_UDPPORTW  = WideString('UdpPort');
  {$EXTERNALSYM SERVICE_TYPE_VALUE_UDPPORTW}
  SERVICE_TYPE_VALUE_OBJECTIDA = 'ObjectId';
  {$EXTERNALSYM SERVICE_TYPE_VALUE_OBJECTIDA}
  SERVICE_TYPE_VALUE_OBJECTIDW = WideString('ObjectId');
  {$EXTERNALSYM SERVICE_TYPE_VALUE_OBJECTIDW}

{$IFDEF UNICODE}

  SERVICE_TYPE_VALUE_SAPID    = SERVICE_TYPE_VALUE_SAPIDW;
  {$EXTERNALSYM SERVICE_TYPE_VALUE_SAPID}
  SERVICE_TYPE_VALUE_TCPPORT  = SERVICE_TYPE_VALUE_TCPPORTW;
  {$EXTERNALSYM SERVICE_TYPE_VALUE_TCPPORT}
  SERVICE_TYPE_VALUE_UDPPORT  = SERVICE_TYPE_VALUE_UDPPORTW;
  {$EXTERNALSYM SERVICE_TYPE_VALUE_UDPPORT}
  SERVICE_TYPE_VALUE_OBJECTID = SERVICE_TYPE_VALUE_OBJECTIDW;
  {$EXTERNALSYM SERVICE_TYPE_VALUE_OBJECTID}

{$ELSE}

  SERVICE_TYPE_VALUE_SAPID    = SERVICE_TYPE_VALUE_SAPIDA;
  {$EXTERNALSYM SERVICE_TYPE_VALUE_SAPID}
  SERVICE_TYPE_VALUE_TCPPORT  = SERVICE_TYPE_VALUE_TCPPORTA;
  {$EXTERNALSYM SERVICE_TYPE_VALUE_TCPPORT}
  SERVICE_TYPE_VALUE_UDPPORT  = SERVICE_TYPE_VALUE_UDPPORTA;
  {$EXTERNALSYM SERVICE_TYPE_VALUE_UDPPORT}
  SERVICE_TYPE_VALUE_OBJECTID = SERVICE_TYPE_VALUE_OBJECTIDA;
  {$EXTERNALSYM SERVICE_TYPE_VALUE_OBJECTID}

{$ENDIF}

//
// SockAddr Information
//

type
  LPSOCKET_ADDRESS = ^SOCKET_ADDRESS;
  {$EXTERNALSYM LPSOCKET_ADDRESS}
  PSOCKET_ADDRESS = ^SOCKET_ADDRESS;
  {$EXTERNALSYM PSOCKET_ADDRESS}
  _SOCKET_ADDRESS = record
    lpSockaddr: LPSOCKADDR;
    iSockaddrLength: Integer;
  end;
  {$EXTERNALSYM _SOCKET_ADDRESS}
  SOCKET_ADDRESS = _SOCKET_ADDRESS;
  {$EXTERNALSYM SOCKET_ADDRESS}
  TSocketAddress = SOCKET_ADDRESS;
  PSocketAddress = PSOCKET_ADDRESS;

//
// CSAddr Information
//

  LPCSADDR_INFO = ^CSADDR_INFO;
  {$EXTERNALSYM LPCSADDR_INFO}
  PCSADDR_INFO = ^CSADDR_INFO;
  {$EXTERNALSYM PCSADDR_INFO}
  _CSADDR_INFO = record
    LocalAddr: SOCKET_ADDRESS;
    RemoteAddr: SOCKET_ADDRESS;
    iSocketType: Integer;
    iProtocol: Integer;
  end;
  {$EXTERNALSYM _CSADDR_INFO}
  CSADDR_INFO = _CSADDR_INFO;
  {$EXTERNALSYM CSADDR_INFO}
  TCsAddrInfo = CSADDR_INFO;
  PCsAddrInfo = PCSADDR_INFO;

//
// Address list returned via SIO_ADDRESS_LIST_QUERY
//

  LPSOCKET_ADDRESS_LIST = ^SOCKET_ADDRESS_LIST;
  {$EXTERNALSYM LPSOCKET_ADDRESS_LIST}
  _SOCKET_ADDRESS_LIST = record
    iAddressCount: Integer;
    Address: array [0..0] of SOCKET_ADDRESS;
  end;
  {$EXTERNALSYM _SOCKET_ADDRESS_LIST}
  SOCKET_ADDRESS_LIST = _SOCKET_ADDRESS_LIST;
  {$EXTERNALSYM SOCKET_ADDRESS_LIST}
  TSocketAddressList = SOCKET_ADDRESS_LIST;
  PSocketAddressList = LPSOCKET_ADDRESS_LIST;

//
//  Address Family/Protocol Tuples
//

  LPAFPROTOCOLS = ^AFPROTOCOLS;
  {$EXTERNALSYM LPAFPROTOCOLS}
  PAFPROTOCOLS = ^AFPROTOCOLS;
  {$EXTERNALSYM PAFPROTOCOLS}
  _AFPROTOCOLS = record
    iAddressFamily: Integer;
    iProtocol: Integer;
  end;
  {$EXTERNALSYM _AFPROTOCOLS}
  AFPROTOCOLS = _AFPROTOCOLS;
  {$EXTERNALSYM AFPROTOCOLS}
  TAfProtocols = AFPROTOCOLS;

//
// Client Query API Typedefs
//

//
// The comparators
//

  _WSAEcomparator = (COMP_EQUAL, COMP_NOTLESS);
  {$EXTERNALSYM _WSAEcomparator}
  WSAECOMPARATOR = _WSAEcomparator;
  {$EXTERNALSYM WSAECOMPARATOR}
  PWSAECOMPARATOR = ^WSAECOMPARATOR;
  {$EXTERNALSYM PWSAECOMPARATOR}
  LPWSAECOMPARATOR = ^WSAECOMPARATOR;
  {$EXTERNALSYM LPWSAECOMPARATOR}

  LPWSAVERSION = ^WSAVERSION;
  {$EXTERNALSYM LPWSAVersion}
  PWSAVERSION = ^WSAVERSION;
  {$EXTERNALSYM PWSAVersion}
  _WSAVersion = record
    dwVersion: DWORD;
    ecHow: WSAECOMPARATOR;
  end;
  {$EXTERNALSYM _WSAVersion}
  WSAVERSION = _WSAVersion;
  {$EXTERNALSYM WSAVERSION}
  TWsaVersion = WSAVERSION;

  _WSAQuerySetA = record
    dwSize: DWORD;
    lpszServiceInstanceName: LPSTR;
    lpServiceClassId: PGUID;
    lpVersion: LPWSAVERSION;
    lpszComment: LPSTR;
    dwNameSpace: DWORD;
    lpNSProviderId: PGUID;
    lpszContext: LPSTR;
    dwNumberOfProtocols: DWORD;
    lpafpProtocols: LPAFPROTOCOLS;
    lpszQueryString: LPSTR;
    dwNumberOfCsAddrs: DWORD;
    lpcsaBuffer: LPCSADDR_INFO;
    dwOutputFlags: DWORD;
    lpBlob: LPBLOB;
  end;
  {$EXTERNALSYM _WSAQuerySetA}
  WSAQUERYSETA = _WSAQuerySetA;
  {$EXTERNALSYM WSAQUERYSETA}
  PWSAQUERYSETA = ^WSAQUERYSETA;
  {$EXTERNALSYM PWSAQUERYSETA}
  LPWSAQUERYSETA = ^WSAQUERYSETA;
  {$EXTERNALSYM LPWSAQUERYSETA}
  TWsaQuerySetA = WSAQUERYSETA;

  _WSAQuerySetW = record
    dwSize: DWORD;
    lpszServiceInstanceName: LPWSTR;
    lpServiceClassId: PGUID;
    lpVersion: LPWSAVERSION;
    lpszComment: LPWSTR;
    dwNameSpace: DWORD;
    lpNSProviderId: PGUID;
    lpszContext: LPWSTR;
    dwNumberOfProtocols: DWORD;
    lpafpProtocols: LPAFPROTOCOLS;
    lpszQueryString: LPWSTR;
    dwNumberOfCsAddrs: DWORD;
    lpcsaBuffer: LPCSADDR_INFO;
    dwOutputFlags: DWORD;
    lpBlob: LPBLOB;
  end;
  {$EXTERNALSYM _WSAQuerySetW}
  WSAQUERYSETW = _WSAQuerySetW;
  {$EXTERNALSYM WSAQUERYSETW}
  PWSAQUERYSETW = ^WSAQUERYSETW;
  {$EXTERNALSYM PWSAQUERYSETW}
  LPWSAQUERYSETW = ^WSAQUERYSETW;
  {$EXTERNALSYM LPWSAQUERYSETW}
  TWsaQuerySetW = WSAQUERYSETW;

{$IFDEF UNICODE}
  WSAQUERYSET = WSAQUERYSETW;
  {$EXTERNALSYM WSAQUERYSET}
  PWSAQUERYSET = PWSAQUERYSETW;
  {$EXTERNALSYM PWSAQUERYSET}
  LPWSAQUERYSET = LPWSAQUERYSETW;
  {$EXTERNALSYM LPWSAQUERYSET}
  TWsaQuerySet = TWsaQuerySetW;
{$ELSE}
  WSAQUERYSET = WSAQUERYSETA;
  {$EXTERNALSYM WSAQUERYSET}
  PWSAQUERYSET = PWSAQUERYSETA;
  {$EXTERNALSYM PWSAQUERYSET}
  LPWSAQUERYSET = LPWSAQUERYSETA;
  {$EXTERNALSYM LPWSAQUERYSET}
  TWsaQuerySet = TWsaQuerySetA;
{$ENDIF}

const
  LUP_DEEP                = $0001;
  {$EXTERNALSYM LUP_DEEP}
  LUP_CONTAINERS          = $0002;
  {$EXTERNALSYM LUP_CONTAINERS}
  LUP_NOCONTAINERS        = $0004;
  {$EXTERNALSYM LUP_NOCONTAINERS}
  LUP_NEAREST             = $0008;
  {$EXTERNALSYM LUP_NEAREST}
  LUP_RETURN_NAME         = $0010;
  {$EXTERNALSYM LUP_RETURN_NAME}
  LUP_RETURN_TYPE         = $0020;
  {$EXTERNALSYM LUP_RETURN_TYPE}
  LUP_RETURN_VERSION      = $0040;
  {$EXTERNALSYM LUP_RETURN_VERSION}
  LUP_RETURN_COMMENT      = $0080;
  {$EXTERNALSYM LUP_RETURN_COMMENT}
  LUP_RETURN_ADDR         = $0100;
  {$EXTERNALSYM LUP_RETURN_ADDR}
  LUP_RETURN_BLOB         = $0200;
  {$EXTERNALSYM LUP_RETURN_BLOB}
  LUP_RETURN_ALIASES      = $0400;
  {$EXTERNALSYM LUP_RETURN_ALIASES}
  LUP_RETURN_QUERY_STRING = $0800;
  {$EXTERNALSYM LUP_RETURN_QUERY_STRING}
  LUP_RETURN_ALL          = $0FF0;
  {$EXTERNALSYM LUP_RETURN_ALL}
  LUP_RES_SERVICE         = $8000;
  {$EXTERNALSYM LUP_RES_SERVICE}

  LUP_FLUSHCACHE    = $1000;
  {$EXTERNALSYM LUP_FLUSHCACHE}
  LUP_FLUSHPREVIOUS = $2000;
  {$EXTERNALSYM LUP_FLUSHPREVIOUS}

//
// Return flags
//

  RESULT_IS_ALIAS = $0001;
  {$EXTERNALSYM RESULT_IS_ALIAS}
  RESULT_IS_ADDED   = $0010;
  {$EXTERNALSYM RESULT_IS_ADDED}
  RESULT_IS_CHANGED = $0020;
  {$EXTERNALSYM RESULT_IS_CHANGED}
  RESULT_IS_DELETED = $0040;
  {$EXTERNALSYM RESULT_IS_DELETED}

//
// Service Address Registration and Deregistration Data Types.
//

type
  _WSAESETSERVICEOP = (RNRSERVICE_REGISTER, RNRSERVICE_DEREGISTER, RNRSERVICE_DELETE);
  {$EXTERNALSYM _WSAESETSERVICEOP}
  WSAESETSERVICEOP = _WSAESETSERVICEOP;
  {$EXTERNALSYM WSAESETSERVICEOP}
  PWSAESETSERVICEOP = ^WSAESETSERVICEOP;
  {$EXTERNALSYM PWSAESETSERVICEOP}
  LPWSAESETSERVICEOP = ^WSAESETSERVICEOP;
  {$EXTERNALSYM LPWSAESETSERVICEOP}

//
// Service Installation/Removal Data Types.
//

  _WSANSClassInfoA = record
    lpszName: LPSTR;
    dwNameSpace: DWORD;
    dwValueType: DWORD;
    dwValueSize: DWORD;
    lpValue: LPVOID;
  end;
  {$EXTERNALSYM _WSANSClassInfoA}
  WSANSCLASSINFOA = _WSANSClassInfoA;
  {$EXTERNALSYM WSANSCLASSINFOA}
  PWSANSCLASSINFOA = ^WSANSCLASSINFOA;
  {$EXTERNALSYM PWSANSCLASSINFOA}
  LPWSANSCLASSINFOA = ^WSANSCLASSINFOA;
  {$EXTERNALSYM LPWSANSCLASSINFOA}
  TWsaNsClassInfoA = WSANSCLASSINFOA;

  _WSANSClassInfoW = record
    lpszName: LPWSTR;
    dwNameSpace: DWORD;
    dwValueType: DWORD;
    dwValueSize: DWORD;
    lpValue: LPVOID;
  end;
  {$EXTERNALSYM _WSANSClassInfoW}
  WSANSCLASSINFOW = _WSANSClassInfoW;
  {$EXTERNALSYM WSANSCLASSINFOW}
  PWSANSCLASSINFOW = ^WSANSCLASSINFOW;
  {$EXTERNALSYM PWSANSCLASSINFOW}
  LPWSANSCLASSINFOW = ^WSANSCLASSINFOW;
  {$EXTERNALSYM LPWSANSCLASSINFOW}
  TWsaNsClassInfoW = WSANSCLASSINFOW;

{$IFDEF UNICODE}
  WSANSCLASSINFO = WSANSCLASSINFOW;
  {$EXTERNALSYM WSANSCLASSINFO}
  PWSANSCLASSINFO = PWSANSCLASSINFOW;
  {$EXTERNALSYM PWSANSCLASSINFO}
  LPWSANSCLASSINFO = LPWSANSCLASSINFOW;
  {$EXTERNALSYM LPWSANSCLASSINFO}
  TWsaNsClassInfo = TWsaNsClassInfoW;
{$ELSE}
  WSANSCLASSINFO = WSANSCLASSINFOA;
  {$EXTERNALSYM WSANSCLASSINFO}
  PWSANSCLASSINFO = PWSANSCLASSINFOA;
  {$EXTERNALSYM PWSANSCLASSINFO}
  LPWSANSCLASSINFO = LPWSANSCLASSINFOA;
  {$EXTERNALSYM LPWSANSCLASSINFO}
  TWsaNsClassInfo = TWsaNsClassInfoA;
{$ENDIF}

  _WSAServiceClassInfoA = record
    lpServiceClassId: PGUID;
    lpszServiceClassName: LPSTR;
    dwCount: DWORD;
    lpClassInfos: LPWSANSCLASSINFOA;
  end;
  {$EXTERNALSYM _WSAServiceClassInfoA}
  WSASERVICECLASSINFOA = _WSAServiceClassInfoA;
  {$EXTERNALSYM WSASERVICECLASSINFOA}
  PWSASERVICECLASSINFOA = ^WSASERVICECLASSINFOA;
  {$EXTERNALSYM PWSASERVICECLASSINFOA}
  LPWSASERVICECLASSINFOA = ^WSASERVICECLASSINFOA;
  {$EXTERNALSYM LPWSASERVICECLASSINFOA}
  TWsaServiceClassInfoA = WSASERVICECLASSINFOA;

  _WSAServiceClassInfoW = record
    lpServiceClassId: PGUID;
    lpszServiceClassName: LPWSTR;
    dwCount: DWORD;
    lpClassInfos: LPWSANSCLASSINFOW;
  end;
  {$EXTERNALSYM _WSAServiceClassInfoW}
  WSASERVICECLASSINFOW = _WSAServiceClassInfoW;
  {$EXTERNALSYM WSASERVICECLASSINFOW}
  PWSASERVICECLASSINFOW = ^WSASERVICECLASSINFOW;
  {$EXTERNALSYM PWSASERVICECLASSINFOW}
  LPWSASERVICECLASSINFOW = ^WSASERVICECLASSINFOW;
  {$EXTERNALSYM LPWSASERVICECLASSINFOW}
  TWsaServiceClassInfoW = WSASERVICECLASSINFOW;

{$IFDEF UNICODE}
  WSASERVICECLASSINFO = WSASERVICECLASSINFOW;
  {$EXTERNALSYM WSASERVICECLASSINFO}
  PWSASERVICECLASSINFO = PWSASERVICECLASSINFOW;
  {$EXTERNALSYM PWSASERVICECLASSINFO}
  LPWSASERVICECLASSINFO = LPWSASERVICECLASSINFOW;
  {$EXTERNALSYM LPWSASERVICECLASSINFO}
  TWsaServiceClassInfo = TWsaServiceClassInfoW;
{$ELSE}
  WSASERVICECLASSINFO = WSASERVICECLASSINFOA;
  {$EXTERNALSYM WSASERVICECLASSINFO}
  PWSASERVICECLASSINFO = PWSASERVICECLASSINFOA;
  {$EXTERNALSYM PWSASERVICECLASSINFO}
  LPWSASERVICECLASSINFO = LPWSASERVICECLASSINFOA;
  {$EXTERNALSYM LPWSASERVICECLASSINFO}
  TWsaServiceClassInfo = TWsaServiceClassInfoA;
{$ENDIF}

  LPWSANAMESPACE_INFOA = ^WSANAMESPACE_INFOA;
  {$EXTERNALSYM LPWSANAMESPACE_INFOA}
  PWSANAMESPACE_INFOA = ^WSANAMESPACE_INFOA;
  {$EXTERNALSYM PWSANAMESPACE_INFOA}
  _WSANAMESPACE_INFOA = record
    NSProviderId: TGUID;
    dwNameSpace: DWORD;
    fActive: BOOL;
    dwVersion: DWORD;
    lpszIdentifier: LPSTR;
  end;
  {$EXTERNALSYM _WSANAMESPACE_INFOA}
  WSANAMESPACE_INFOA = _WSANAMESPACE_INFOA;
  {$EXTERNALSYM WSANAMESPACE_INFOA}
  TWsaNameSpaceInfoA = WSANAMESPACE_INFOA;
  PWsaNameSpaceInfoA = LPWSANAMESPACE_INFOA;

  LPWSANAMESPACE_INFOW = ^WSANAMESPACE_INFOW;
  {$EXTERNALSYM LPWSANAMESPACE_INFOW}
  PWSANAMESPACE_INFOW = ^WSANAMESPACE_INFOW;
  {$EXTERNALSYM PWSANAMESPACE_INFOW}
  _WSANAMESPACE_INFOW = record
    NSProviderId: TGUID;
    dwNameSpace: DWORD;
    fActive: BOOL;
    dwVersion: DWORD;
    lpszIdentifier: LPWSTR;
  end;
  {$EXTERNALSYM _WSANAMESPACE_INFOW}
  WSANAMESPACE_INFOW = _WSANAMESPACE_INFOW;
  {$EXTERNALSYM WSANAMESPACE_INFOW}
  TWsaNameSpaceInfoW = WSANAMESPACE_INFOW;
  PWsaNameSpaceInfoW = PWSANAMESPACE_INFOW;

{$IFDEF UNICODE}
  WSANAMESPACE_INFO = WSANAMESPACE_INFOW;
  {$EXTERNALSYM WSANAMESPACE_INFO}
  PWSANAMESPACE_INFO = PWSANAMESPACE_INFOW;
  {$EXTERNALSYM PWSANAMESPACE_INFO}
  LPWSANAMESPACE_INFO = LPWSANAMESPACE_INFOW;
  {$EXTERNALSYM LPWSANAMESPACE_INFO}
  TWsaNameSpaceInfo = TWsaNameSpaceInfoW;
  PWsaNameSpaceInfo = PWsaNameSpaceInfoW;
{$ELSE}
  WSANAMESPACE_INFO = WSANAMESPACE_INFOA;
  {$EXTERNALSYM WSANAMESPACE_INFO}
  PWSANAMESPACE_INFO = PWSANAMESPACE_INFOA;
  {$EXTERNALSYM PWSANAMESPACE_INFO}
  LPWSANAMESPACE_INFO = LPWSANAMESPACE_INFOA;
  {$EXTERNALSYM LPWSANAMESPACE_INFO}
  TWsaNameSpaceInfo = TWsaNameSpaceInfoA;
  PWsaNameSpaceInfo = PWsaNameSpaceInfoA;
{$ENDIF}

// Socket function prototypes

function accept(s: TSocket; addr: PSockAddr; addrlen: PINT): TSocket; stdcall;
{$EXTERNALSYM accept}
function bind(s: TSocket; name: PSockAddr; namelen: Integer): Integer; stdcall;
{$EXTERNALSYM bind}
function closesocket(s: TSocket): Integer; stdcall;
{$EXTERNALSYM closesocket}
function connect(s: TSocket; name: PSockAddr; namelen: Integer): Integer; stdcall;
{$EXTERNALSYM connect}
function ioctlsocket(s: TSocket; cmd: Longint; var argp: u_long): Integer; stdcall;
{$EXTERNALSYM ioctlsocket}
function getpeername(s: TSocket; name: PSockAddr; var namelen: Integer): Integer; stdcall;
{$EXTERNALSYM getpeername}
function getsockname(s: TSocket; name: PSockAddr; var namelen: Integer): Integer; stdcall;
{$EXTERNALSYM getsockname}
function getsockopt(s: TSocket; level, optname: Integer; optval: PChar; var optlen: Integer): Integer; stdcall;
{$EXTERNALSYM getsockopt}
function htonl(hostlong: u_long): u_long; stdcall;
{$EXTERNALSYM htonl}
function htons(hostshort: u_short): u_short; stdcall;
{$EXTERNALSYM htons}
function inet_addr(cp: PChar): u_long; stdcall;
{$EXTERNALSYM inet_addr}
function inet_ntoa(inaddr: in_addr): PChar; stdcall;
{$EXTERNALSYM inet_ntoa}
function listen(s: TSocket; backlog: Integer): Integer; stdcall;
{$EXTERNALSYM listen}
function ntohl(netlong: u_long): u_long; stdcall;
{$EXTERNALSYM ntohl}
function ntohs(netshort: u_short): u_short; stdcall;
{$EXTERNALSYM ntohs}
function recv(s: TSocket; var buf; len, flags: Integer): Integer; stdcall;
{$EXTERNALSYM recv}
function recvfrom(s: TSocket; var buf; len, flags: Integer; from: PSockAddr; var fromlen: Integer): Integer; stdcall;
{$EXTERNALSYM recvfrom}
function select(nfds: Integer; readfds, writefds, exceptfds: PFdSet; timeout: PTimeVal): Integer; stdcall;
{$EXTERNALSYM select}
function send(s: TSocket; var buf; len, flags: Integer): Integer; stdcall;
{$EXTERNALSYM send}
function sendto(s: TSocket; var buf; len, flags: Integer; toaddr: PSockAddr; tolen: Integer): Integer; stdcall;
{$EXTERNALSYM sendto}
function setsockopt(s: TSocket; level, optname: Integer; optval: PChar; optlen: Integer): Integer; stdcall;
{$EXTERNALSYM setsockopt}
function shutdown(s: TSocket; how: Integer): Integer; stdcall;
{$EXTERNALSYM shutdown}
function socket(af, type_, protocol: Integer): TSocket; stdcall;
{$EXTERNALSYM socket}

// Database function prototypes

function gethostbyaddr(addr: PChar; len, type_: Integer): PHostEnt; stdcall;
{$EXTERNALSYM gethostbyaddr}
function gethostbyname(name: PChar): PHostEnt; stdcall;
{$EXTERNALSYM gethostbyname}
function gethostname(name: PChar; namelen: Integer): Integer; stdcall;
{$EXTERNALSYM gethostname}
function getservbyport(port: Integer; proto: PChar): PServEnt; stdcall;
{$EXTERNALSYM getservbyport}
function getservbyname(name, proto: PChar): PServEnt; stdcall;
{$EXTERNALSYM getservbyname}
function getprotobynumber(number: Integer): PProtoEnt; stdcall;
{$EXTERNALSYM getprotobynumber}
function getprotobyname(name: PChar): PProtoEnt; stdcall;
{$EXTERNALSYM getprotobyname}

// Microsoft Windows Extension function prototypes

function WSAStartup(wVersionRequired: WORD; var lpWSAData: TWSAData): Integer; stdcall;
{$EXTERNALSYM WSAStartup}
function WSACleanup: Integer; stdcall;
{$EXTERNALSYM WSACleanup}
procedure WSASetLastError(iError: Integer); stdcall;
{$EXTERNALSYM WSASetLastError}
function WSAGetLastError: Integer; stdcall;
{$EXTERNALSYM WSAGetLastError}
function WSAIsBlocking: BOOL; stdcall;
{$EXTERNALSYM WSAIsBlocking}
function WSAUnhookBlockingHook: Integer; stdcall;
{$EXTERNALSYM WSAUnhookBlockingHook}
function WSASetBlockingHook(lpBlockFunc: FARPROC): FARPROC; stdcall;
{$EXTERNALSYM WSASetBlockingHook}
function WSACancelBlockingCall: Integer; stdcall;
{$EXTERNALSYM WSACancelBlockingCall}
function WSAAsyncGetServByName(hWnd: HWND; wMsg: u_int; name, proto, buf: PChar;
  buflen: Integer): HANDLE; stdcall;
{$EXTERNALSYM WSAAsyncGetServByName}
function WSAAsyncGetServByPort(hWnd: HWND; wMsg: u_int; port: Integer;
  proto, buf: PChar; buflen: Integer): HANDLE; stdcall;
{$EXTERNALSYM WSAAsyncGetServByPort}
function WSAAsyncGetProtoByName(hWnd: HWND; wMsg: u_int; name, buf: PChar;
  buflen: Integer): HANDLE; stdcall;
{$EXTERNALSYM WSAAsyncGetProtoByName}
function WSAAsyncGetProtoByNumber(hWnd: HWND; wMsg: u_int; number: Integer;
  buf: PChar; buflen: Integer): HANDLE; stdcall;
{$EXTERNALSYM WSAAsyncGetProtoByNumber}
function WSAAsyncGetHostByName(hWnd: HWND; wMsg: u_int; name, buf: PChar;
  buflen: Integer): HANDLE; stdcall;
{$EXTERNALSYM WSAAsyncGetHostByName}
function WSAAsyncGetHostByAddr(hWnd: HWND; wMsg: u_int; addr: PChar;
  len, type_: Integer; buf: PChar; buflen: Integer): HANDLE; stdcall;
{$EXTERNALSYM WSAAsyncGetHostByAddr}
function WSACancelAsyncRequest(hAsyncTaskHandle: HANDLE): Integer; stdcall;
{$EXTERNALSYM WSACancelAsyncRequest}
function WSAAsyncSelect(s: TSocket; hWnd: HWND; wMsg: u_int; lEvent: Longint): Integer; stdcall;
{$EXTERNALSYM WSAAsyncSelect}

// WinSock 2 API new function prototypes

function WSAAccept(s: TSocket; addr: PSockAddr; addrlen: PINT;
  lpfnCondition: LPCONDITIONPROC; dwCallbackData: DWORD): TSocket; stdcall;
{$EXTERNALSYM WSAAccept}
function WSACloseEvent(hEvent: WSAEVENT): BOOL; stdcall;
{$EXTERNALSYM WSACloseEvent}
function WSAConnect(s: TSocket; name: PSockAddr; namelen: Integer; lpCallerData: LPWSABUF;
  lpCalleeData: LPWSABUF; lpSQOS: LPQOS; lpGQOS: LPQOS): Integer; stdcall;
{$EXTERNALSYM WSAConnect}
function WSACreateEvent: WSAEVENT; stdcall;
{$EXTERNALSYM WSACreateEvent}
function WSADuplicateSocketA(s: TSocket; dwProcessId: DWORD; lpProtocolInfo: LPWSAPROTOCOL_INFOA): Integer; stdcall;
{$EXTERNALSYM WSADuplicateSocketA}
function WSADuplicateSocketW(s: TSocket; dwProcessId: DWORD; lpProtocolInfo: LPWSAPROTOCOL_INFOW): Integer; stdcall;
{$EXTERNALSYM WSADuplicateSocketW}
{$IFDEF UNICODE}
function WSADuplicateSocket(s: TSocket; dwProcessId: DWORD; lpProtocolInfo: LPWSAPROTOCOL_INFOW): Integer; stdcall;
{$EXTERNALSYM WSADuplicateSocket}
{$ELSE}
function WSADuplicateSocket(s: TSocket; dwProcessId: DWORD; lpProtocolInfo: LPWSAPROTOCOL_INFOA): Integer; stdcall;
{$EXTERNALSYM WSADuplicateSocket}
{$ENDIF}
function WSAEnumNetworkEvents(s: TSocket; hEventObject: WSAEVENT; lpNetworkEvents: LPWSANETWORKEVENTS): Integer; stdcall;
{$EXTERNALSYM WSAEnumNetworkEvents}
function WSAEnumProtocolsA(lpiProtocols: PINT; lpProtocolBuffer: LPWSAPROTOCOL_INFOA;
  var lpdwBufferLength: DWORD): Integer; stdcall;
{$EXTERNALSYM WSAEnumProtocolsA}
function WSAEnumProtocolsW(lpiProtocols: PINT; lpProtocolBuffer: LPWSAPROTOCOL_INFOW;
  var lpdwBufferLength: DWORD): Integer; stdcall;
{$EXTERNALSYM WSAEnumProtocolsW}
{$IFDEF UNICODE}
function WSAEnumProtocols(lpiProtocols: PINT; lpProtocolBuffer: LPWSAPROTOCOL_INFOW;
  var lpdwBufferLength: DWORD): Integer; stdcall;
{$EXTERNALSYM WSAEnumProtocols}
{$ELSE}
function WSAEnumProtocols(lpiProtocols: PINT; lpProtocolBuffer: LPWSAPROTOCOL_INFOA;
  var lpdwBufferLength: DWORD): Integer; stdcall;
{$EXTERNALSYM WSAEnumProtocols}
{$ENDIF}
function WSAEventSelect(s: TSocket; hEventObject: WSAEVENT; lNetworkEvents: Longint): Integer; stdcall;
{$EXTERNALSYM WSAEventSelect}
function WSAGetOverlappedResult(s: TSocket; lpOverlapped: LPWSAOVERLAPPED;
  var lpcbTransfer: DWORD; fWait: BOOL; var lpdwFlags: DWORD): BOOL; stdcall; // Thanks Kai Henningsen for var on lpdwFlags
{$EXTERNALSYM WSAGetOverlappedResult}
function WSAGetQOSByName(s: TSocket; var lpQOSName: WSABUF; lpQOS: LPQOS): BOOL; stdcall;
{$EXTERNALSYM WSAGetQOSByName}
function WSAHtonl(s: TSocket; hostlong: u_long; var lpnetlong: u_long): Integer; stdcall;
{$EXTERNALSYM WSAHtonl}
function WSAHtons(s: TSocket; hostshort: u_short; var lpnetshort: u_short): Integer; stdcall;
{$EXTERNALSYM WSAHtons}
function WSAIoctl(s: TSocket; dwIoControlCode: DWORD; lpvInBuffer: LPVOID; cbInBuffer: DWORD;
  lpvOutBuffer: LPVOID; cbOutBuffer: DWORD; var lpcbBytesReturned: DWORD;
  lpOverlapped: LPWSAOVERLAPPED; lpCompletionRoutine: LPWSAOVERLAPPED_COMPLETION_ROUTINE): Integer; stdcall;
{$EXTERNALSYM WSAIoctl}
function WSAJoinLeaf(s: TSocket; name: PSockAddr; namelen: Integer; lpCallerData: LPWSABUF;
  lpCalleeData: LPWSABUF; lpSQOS, lpGQOS: LPQOS; dwFlags: DWORD): TSocket; stdcall;
{$EXTERNALSYM WSAJoinLeaf}
function WSANtohl(s: TSocket; netlong: u_long; var lphostlong: u_long): Integer; stdcall;
{$EXTERNALSYM WSANtohl}
function WSANtohs(s: TSocket; netshort: u_short; var lphostshort: u_short): Integer; stdcall;
{$EXTERNALSYM WSANtohs}
function WSARecv(s: TSocket; lpBuffers: LPWSABUF; dwBufferCount: DWORD;
  var lpNumberOfBytesRecvd, lpFlags: DWORD; lpOverlapped: LPWSAOVERLAPPED;
  lpCompletionRoutine: LPWSAOVERLAPPED_COMPLETION_ROUTINE): Integer; stdcall;
{$EXTERNALSYM WSARecv}
function WSARecvDisconnect(s: TSocket; lpInboundDisconnectData: LPWSABUF): Integer; stdcall;
{$EXTERNALSYM WSARecvDisconnect}
function WSARecvFrom(s: TSocket; lpBuffers: LPWSABUF; dwBufferCount: DWORD;
  var lpNumberOfBytesRecvd, lpFlags: DWORD; lpFrom: PSockAddr; lpFromlen: PINT;
  lpOverlapped: LPWSAOVERLAPPED; lpCompletionRoutine: LPWSAOVERLAPPED_COMPLETION_ROUTINE): Integer; stdcall;
{$EXTERNALSYM WSARecvFrom}
function WSAResetEvent(hEvent: WSAEVENT): BOOL; stdcall;
{$EXTERNALSYM WSAResetEvent}
function WSASend(s: TSocket; lpBuffers: LPWSABUF; dwBufferCount: DWORD;
  var lpNumberOfBytesSent: DWORD; dwFlags: DWORD; lpOverlapped: LPWSAOVERLAPPED;
  lpCompletionRoutine: LPWSAOVERLAPPED_COMPLETION_ROUTINE): Integer; stdcall;
{$EXTERNALSYM WSASend}
function WSASendDisconnect(s: TSocket; lpOutboundDisconnectData: LPWSABUF): Integer; stdcall;
{$EXTERNALSYM WSASendDisconnect}
function WSASendTo(s: TSocket; lpBuffers: LPWSABUF; dwBufferCount: DWORD;
  var lpNumberOfBytesSent: DWORD; dwFlags: DWORD; lpTo: PSockAddr; iTolen: Integer;
  lpOverlapped: LPWSAOVERLAPPED; lpCompletionRoutine: LPWSAOVERLAPPED_COMPLETION_ROUTINE): Integer; stdcall;
{$EXTERNALSYM WSASendTo}
function WSASetEvent(hEvent: WSAEVENT): BOOL; stdcall;
{$EXTERNALSYM WSASetEvent}
function WSASocketA(af, type_, protocol: Integer; lpProtocolInfo: LPWSAPROTOCOL_INFOA;
  g: GROUP; dwFlags: DWORD): TSocket; stdcall;
{$EXTERNALSYM WSASocketA}
function WSASocketW(af, type_, protocol: Integer; lpProtocolInfo: LPWSAPROTOCOL_INFOW;
  g: GROUP; dwFlags: DWORD): TSocket; stdcall;
{$EXTERNALSYM WSASocketW}
{$IFDEF UNICODE}
function WSASocket(af, type_, protocol: Integer; lpProtocolInfo: LPWSAPROTOCOL_INFOW;
  g: GROUP; dwFlags: DWORD): TSocket; stdcall;
{$EXTERNALSYM WSASocket}
{$ELSE}
function WSASocket(af, type_, protocol: Integer; lpProtocolInfo: LPWSAPROTOCOL_INFOA;
  g: GROUP; dwFlags: DWORD): TSocket; stdcall;
{$EXTERNALSYM WSASocket}
{$ENDIF}
function WSAWaitForMultipleEvents(cEvents: DWORD; lphEvents: PWSAEVENT;
  fWaitAll: BOOL; dwTimeout: DWORD; fAlertable: BOOL): DWORD; stdcall;
{$EXTERNALSYM WSAWaitForMultipleEvents}
function WSAAddressToStringA(lpsaAddress: LPSOCKADDR; dwAddressLength: DWORD;
  lpProtocolInfo: LPWSAPROTOCOL_INFOA; lpszAddressString: LPSTR;
  var lpdwAddressStringLength: DWORD): Integer; stdcall;
{$EXTERNALSYM WSAAddressToStringA}
function WSAAddressToStringW(lpsaAddress: LPSOCKADDR; dwAddressLength: DWORD;
  lpProtocolInfo: LPWSAPROTOCOL_INFOW; lpszAddressString: LPWSTR;
  var lpdwAddressStringLength: DWORD): Integer; stdcall;
{$EXTERNALSYM WSAAddressToStringW}
{$IFDEF UNICODE}
function WSAAddressToString(lpsaAddress: LPSOCKADDR; dwAddressLength: DWORD;
  lpProtocolInfo: LPWSAPROTOCOL_INFOW; lpszAddressString: LPWSTR;
  var lpdwAddressStringLength: DWORD): Integer; stdcall;
{$EXTERNALSYM WSAAddressToString}
{$ELSE}
function WSAAddressToString(lpsaAddress: LPSOCKADDR; dwAddressLength: DWORD;
  lpProtocolInfo: LPWSAPROTOCOL_INFOA; lpszAddressString: LPSTR;
  var lpdwAddressStringLength: DWORD): Integer; stdcall;
{$EXTERNALSYM WSAAddressToString}
{$ENDIF}
function WSAStringToAddressA(AddressString: LPSTR; AddressFamily: Integer;
  lpProtocolInfo: LPWSAPROTOCOL_INFOA; lpAddress: LPSOCKADDR;
  var lpAddressLength: Integer): Integer; stdcall;
{$EXTERNALSYM WSAStringToAddressA}
function WSAStringToAddressW(AddressString: LPWSTR; AddressFamily: Integer;
  lpProtocolInfo: LPWSAPROTOCOL_INFOW; lpAddress: LPSOCKADDR;
  var lpAddressLength: Integer): Integer; stdcall;
{$EXTERNALSYM WSAStringToAddressW}
{$IFDEF UNICODE}
function WSAStringToAddress(AddressString: LPWSTR; AddressFamily: Integer;
  lpProtocolInfo: LPWSAPROTOCOL_INFOW; lpAddress: LPSOCKADDR;
  var lpAddressLength: Integer): Integer; stdcall;
{$EXTERNALSYM WSAStringToAddress}
{$ELSE}
function WSAStringToAddress(AddressString: LPSTR; AddressFamily: Integer;
  lpProtocolInfo: LPWSAPROTOCOL_INFOA; lpAddress: LPSOCKADDR;
  var lpAddressLength: Integer): Integer; stdcall;
{$EXTERNALSYM WSAStringToAddress}
{$ENDIF}

// Registration and Name Resolution API functions

function WSALookupServiceBeginA(lpqsRestrictions: LPWSAQUERYSETA;
  dwControlFlags: DWORD; var lphLookup: HANDLE): Integer; stdcall;
{$EXTERNALSYM WSALookupServiceBeginA}
function WSALookupServiceBeginW(lpqsRestrictions: LPWSAQUERYSETW;
  dwControlFlags: DWORD; var lphLookup: HANDLE): Integer; stdcall;
{$EXTERNALSYM WSALookupServiceBeginW}
{$IFDEF UNICODE}
function WSALookupServiceBegin(lpqsRestrictions: LPWSAQUERYSETW;
  dwControlFlags: DWORD; var lphLookup: HANDLE): Integer; stdcall;
{$EXTERNALSYM WSALookupServiceBegin}
{$ELSE}
function WSALookupServiceBegin(lpqsRestrictions: LPWSAQUERYSETA;
  dwControlFlags: DWORD; var lphLookup: HANDLE): Integer; stdcall;
{$EXTERNALSYM WSALookupServiceBegin}
{$ENDIF}
function WSALookupServiceNextA(hLookup: HANDLE; dwControlFlags: DWORD;
  var lpdwBufferLength: DWORD; lpqsResults: LPWSAQUERYSETA): Integer; stdcall;
{$EXTERNALSYM WSALookupServiceNextA}
function WSALookupServiceNextW(hLookup: HANDLE; dwControlFlags: DWORD;
  var lpdwBufferLength: DWORD; lpqsResults: LPWSAQUERYSETW): Integer; stdcall;
{$EXTERNALSYM WSALookupServiceNextW}
{$IFDEF UNICODE}
function WSALookupServiceNext(hLookup: HANDLE; dwControlFlags: DWORD;
  var lpdwBufferLength: DWORD; lpqsResults: LPWSAQUERYSETW): Integer; stdcall;
{$EXTERNALSYM WSALookupServiceNext}
{$ELSE}
function WSALookupServiceNext(hLookup: HANDLE; dwControlFlags: DWORD;
  var lpdwBufferLength: DWORD; lpqsResults: LPWSAQUERYSETA): Integer; stdcall;
{$EXTERNALSYM WSALookupServiceNext}
{$ENDIF}
function WSANSPIoctl(hLookup: HANDLE; dwControlCode: DWORD; lpvInBuffer: LPVOID; cbInBuffer: DWORD;
  lpvOutBuffer: LPVOID; cbOutBuffer: DWORD; lpcbBytesReturned: LPDWORD; lpCompletion: LPWSACOMPLETION): Integer; stdcall;
{$EXTERNALSYM WSANSPIoctl}
function WSALookupServiceEnd(hLookup: HANDLE): Integer; stdcall;
{$EXTERNALSYM WSALookupServiceEnd}
function WSAInstallServiceClassA(lpServiceClassInfo: LPWSASERVICECLASSINFOA): Integer; stdcall;
{$EXTERNALSYM WSAInstallServiceClassA}
function WSAInstallServiceClassW(lpServiceClassInfo: LPWSASERVICECLASSINFOW): Integer; stdcall;
{$EXTERNALSYM WSAInstallServiceClassW}
{$IFDEF UNICODE}
function WSAInstallServiceClass(lpServiceClassInfo: LPWSASERVICECLASSINFOW): Integer; stdcall;
{$EXTERNALSYM WSAInstallServiceClass}
{$ELSE}
function WSAInstallServiceClass(lpServiceClassInfo: LPWSASERVICECLASSINFOA): Integer; stdcall;
{$EXTERNALSYM WSAInstallServiceClass}
{$ENDIF}
function WSARemoveServiceClass(const lpServiceClassId: TGUID): Integer; stdcall;
{$EXTERNALSYM WSARemoveServiceClass}
function WSAGetServiceClassInfoA(const lpProviderId, lpServiceClassId: TGUID;
  var lpdwBufSize: DWORD; lpServiceClassInfo: LPWSASERVICECLASSINFOA): Integer; stdcall;
{$EXTERNALSYM WSAGetServiceClassInfoA}
function WSAGetServiceClassInfoW(const lpProviderId, lpServiceClassId: TGUID;
  var lpdwBufSize: DWORD; lpServiceClassInfo: LPWSASERVICECLASSINFOW): Integer; stdcall;
{$EXTERNALSYM WSAGetServiceClassInfoW}
{$IFDEF UNICODE}
function WSAGetServiceClassInfo(const lpProviderId, lpServiceClassId: TGUID;
  var lpdwBufSize: DWORD; lpServiceClassInfo: LPWSASERVICECLASSINFOW): Integer; stdcall;
{$EXTERNALSYM WSAGetServiceClassInfo}
{$ELSE}
function WSAGetServiceClassInfo(const lpProviderId, lpServiceClassId: TGUID;
  var lpdwBufSize: DWORD; lpServiceClassInfo: LPWSASERVICECLASSINFOA): Integer; stdcall;
{$EXTERNALSYM WSAGetServiceClassInfo}
{$ENDIF}
function WSAEnumNameSpaceProvidersA(var lpdwBufferLength: DWORD; lpnspBuffer: LPWSANAMESPACE_INFOA): Integer; stdcall;
{$EXTERNALSYM WSAEnumNameSpaceProvidersA}
function WSAEnumNameSpaceProvidersW(var lpdwBufferLength: DWORD; lpnspBuffer: LPWSANAMESPACE_INFOW): Integer; stdcall;
{$EXTERNALSYM WSAEnumNameSpaceProvidersW}
{$IFDEF UNICODE}
function WSAEnumNameSpaceProviders(var lpdwBufferLength: DWORD; lpnspBuffer: LPWSANAMESPACE_INFOW): Integer; stdcall;
{$EXTERNALSYM WSAEnumNameSpaceProviders}
{$ELSE}
function WSAEnumNameSpaceProviders(var lpdwBufferLength: DWORD; lpnspBuffer: LPWSANAMESPACE_INFOA): Integer; stdcall;
{$EXTERNALSYM WSAEnumNameSpaceProviders}
{$ENDIF}
function WSAGetServiceClassNameByClassIdA(const lpServiceClassId: TGUID;
  lpszServiceClassName: LPSTR; var lpdwBufferLength: DWORD): Integer; stdcall;
{$EXTERNALSYM WSAGetServiceClassNameByClassIdA}
function WSAGetServiceClassNameByClassIdW(const lpServiceClassId: TGUID;
  lpszServiceClassName: LPWSTR; var lpdwBufferLength: DWORD): Integer; stdcall;
{$EXTERNALSYM WSAGetServiceClassNameByClassIdW}
{$IFDEF UNICODE}
function WSAGetServiceClassNameByClassId(const lpServiceClassId: TGUID;
  lpszServiceClassName: LPWSTR; var lpdwBufferLength: DWORD): Integer; stdcall;
{$EXTERNALSYM WSAGetServiceClassNameByClassId}
{$ELSE}
function WSAGetServiceClassNameByClassId(const lpServiceClassId: TGUID;
  lpszServiceClassName: LPSTR; var lpdwBufferLength: DWORD): Integer; stdcall;
{$EXTERNALSYM WSAGetServiceClassNameByClassId}
{$ENDIF}
function WSASetServiceA(lpqsRegInfo: LPWSAQUERYSETA; essoperation: WSAESETSERVICEOP;
  dwControlFlags: DWORD): Integer; stdcall;
{$EXTERNALSYM WSASetServiceA}
function WSASetServiceW(lpqsRegInfo: LPWSAQUERYSETW; essoperation: WSAESETSERVICEOP;
  dwControlFlags: DWORD): Integer; stdcall;
{$EXTERNALSYM WSASetServiceW}
{$IFDEF UNICODE}
function WSASetService(lpqsRegInfo: LPWSAQUERYSETW; essoperation: WSAESETSERVICEOP;
  dwControlFlags: DWORD): Integer; stdcall;
{$EXTERNALSYM WSASetService}
{$ELSE}
function WSASetService(lpqsRegInfo: LPWSAQUERYSETA; essoperation: WSAESETSERVICEOP;
  dwControlFlags: DWORD): Integer; stdcall;
{$EXTERNALSYM WSASetService}
{$ENDIF}
function WSAProviderConfigChange(var lpNotificationHandle: HANDLE;
  lpOverlapped: LPWSAOVERLAPPED; lpCompletionRoutine: LPWSAOVERLAPPED_COMPLETION_ROUTINE): Integer; stdcall;
{$EXTERNALSYM WSAProviderConfigChange}

// Microsoft Windows Extended data types

type
  PSOCKADDR_IN = ^sockaddr_in;
  {$EXTERNALSYM PSOCKADDR_IN}
  LPSOCKADDR_IN = ^sockaddr_in;
  {$EXTERNALSYM LPSOCKADDR_IN}
  LPLINGER = PLINGER;
  {$EXTERNALSYM LPLINGER}
  PIN_ADDR = ^in_addr;
  {$EXTERNALSYM PIN_ADDR}
  LPIN_ADDR = ^in_addr;
  {$EXTERNALSYM LPIN_ADDR}
  PFD_SET = ^fd_set;
  {$EXTERNALSYM PFD_SET}
  LPFD_SET = ^fd_set;
  {$EXTERNALSYM LPFD_SET}
  LPHOSTENT = PHOSTENT;
  {$EXTERNALSYM LPHOSTENT}
  LPSERVENT = PSERVENT;
  {$EXTERNALSYM LPSERVENT}
  LPPROTOENT = PPROTOENT;
  {$EXTERNALSYM LPPROTOENT}
  LPTIMEVAL = PTIMEVAL;
  {$EXTERNALSYM LPTIMEVAL}

//
// Windows message parameter composition and decomposition
// macros.
//
// WSAMAKEASYNCREPLY is intended for use by the Windows Sockets implementation
// when constructing the response to a WSAAsyncGetXByY() routine.
//

function WSAMAKEASYNCREPLY(buflen, error: WORD): DWORD;
{$EXTERNALSYM WSAMAKEASYNCREPLY}

//
// WSAMAKESELECTREPLY is intended for use by the Windows Sockets implementation
// when constructing the response to WSAAsyncSelect().
//

function WSAMAKESELECTREPLY(event, error: WORD): DWORD;
{$EXTERNALSYM WSAMAKESELECTREPLY}

//
// WSAGETASYNCBUFLEN is intended for use by the Windows Sockets application
// to extract the buffer length from the lParam in the response
// to a WSAAsyncGetXByY().
//

function WSAGETASYNCBUFLEN(lParam: DWORD): WORD;
{$EXTERNALSYM WSAGETASYNCBUFLEN}

//
// WSAGETASYNCERROR is intended for use by the Windows Sockets application
// to extract the error code from the lParam in the response
// to a WSAGetXByY().
//

function WSAGETASYNCERROR(lParam: DWORD): WORD;
{$EXTERNALSYM WSAGETASYNCERROR}

//
// WSAGETSELECTEVENT is intended for use by the Windows Sockets application
// to extract the event code from the lParam in the response
// to a WSAAsyncSelect().
//

function WSAGETSELECTEVENT(lParam: DWORD): WORD;
{$EXTERNALSYM WSAGETSELECTEVENT}

//
// WSAGETSELECTERROR is intended for use by the Windows Sockets application
// to extract the error code from the lParam in the response
// to a WSAAsyncSelect().
//

function WSAGETSELECTERROR(lParam: DWORD): WORD;
{$EXTERNALSYM WSAGETSELECTERROR}

implementation

const
  ws2_32 = 'ws2_32.dll';


{$IFDEF DYNAMIC_LINK}
var
  ___WSAFDIsSet: Pointer;

function __WSAFDIsSet;
begin
  GetProcedureAddress(___WSAFDIsSet, ws2_32, '__WSAFDIsSet');
  asm
    mov esp, ebp
    pop ebp
    jmp [___WSAFDIsSet]
  end;
end;
{$ELSE}
function __WSAFDIsSet; external ws2_32 name '__WSAFDIsSet';
{$ENDIF DYNAMIC_LINK}

procedure FD_CLR(fd: TSocket; var fdset: TFdSet);
var
  I: Cardinal;
begin
  I := 0;
  while I < fdset.fd_count do
  begin
    if fdset.fd_array[I] = fd then
    begin
      while I < fdset.fd_count - 1 do
      begin
        fdset.fd_array[I] := fdset.fd_array[I + 1];
        Inc(I);
      end;
      fdset.fd_count := fdset.fd_count - 1;
      Break;
    end;
    Inc(I);
  end;
end;

procedure _FD_SET(fd: TSocket; var fdset: TFDSet);
var
  I: Cardinal;
begin
  I := 0;
  while I < fdset.fd_count do
  begin
    if fdset.fd_array[I] = fd then Break;
    Inc(I);
  end;
  if I = fdset.fd_count then
  begin
    if fdset.fd_count < FD_SETSIZE then
    begin
      fdset.fd_array[I] := fd;
      fdset.fd_count := fdset.fd_count + 1;
    end;
  end;
end;

procedure FD_ZERO(var fdset: TFdSet);
begin
  fdset.fd_count := 0;
end;

function FD_ISSET(fd: TSocket; var fdset: TFdSet): Boolean;
begin
  Result := __WSAFDIsSet(fd, fdset) <> 0;
end;

function timerisset(const tvp: TTimeVal): Boolean;
begin
  Result := (tvp.tv_sec <> 0) or (tvp.tv_usec <> 0);
end;

procedure timerclear(var tvp: TTimeVal);
begin
  tvp.tv_sec := 0;
  tvp.tv_usec := 0;
end;

function _IO(x, y: DWORD): DWORD;
begin
  Result := IOC_VOID or (x shl 8) or y;
end;

function _IOR(x, y, t: DWORD): DWORD;
begin
  Result := IOC_OUT or ((T and IOCPARM_MASK) shl 16) or (x shl 8) or y;
end;

function _IOW(x, y, t: DWORD): DWORD;
begin
  Result := DWORD(IOC_IN or ((T and IOCPARM_MASK) shl 16) or (x shl 8) or y);
end;

function IN_CLASSA(i: DWORD): Boolean;
begin
  Result := i and DWORD($80000000) = 0;
end;

function IN_CLASSB(i: DWORD): Boolean;
begin
  Result := i and DWORD($C0000000) = DWORD($80000000);
end;

function IN_CLASSC(i: DWORD): Boolean;
begin
  Result := (i and DWORD($e0000000)) = DWORD($C0000000);
end;

function IN_CLASSD(i: DWORD): Boolean;
begin
  Result := (i and DWORD($f0000000)) = DWORD($e0000000);
end;

function IN_MULTICAST(i: DWORD): Boolean;
begin
  Result := IN_CLASSD(i);
end;

function h_errno: Integer;
begin
  Result := WSAGetLastError;
end;

function _WSAIO(x, y: DWORD): DWORD;
begin
  Result := IOC_VOID or x or y;
end;

function _WSAIOR(x, y: DWORD): DWORD;
begin
  Result := IOC_OUT or x or y;
end;

function _WSAIOW(x, y: DWORD): DWORD;
begin
  Result := IOC_IN or x or y;
end;

function _WSAIORW(x, y: DWORD): DWORD;
begin
  Result := IOC_INOUT or x or y;
end;


{$IFDEF DYNAMIC_LINK}
var
  _accept: Pointer;

function accept;
begin
  GetProcedureAddress(_accept, ws2_32, 'accept');
  asm
    mov esp, ebp
    pop ebp
    jmp [_accept]
  end;
end;
{$ELSE}
function accept; external ws2_32 name 'accept';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _bind: Pointer;

function bind;
begin
  GetProcedureAddress(_bind, ws2_32, 'bind');
  asm
    mov esp, ebp
    pop ebp
    jmp [_bind]
  end;
end;
{$ELSE}
function bind; external ws2_32 name 'bind';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _closesocket: Pointer;

function closesocket;
begin
  GetProcedureAddress(_closesocket, ws2_32, 'closesocket');
  asm
    mov esp, ebp
    pop ebp
    jmp [_closesocket]
  end;
end;
{$ELSE}
function closesocket; external ws2_32 name 'closesocket';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _connect: Pointer;

function connect;
begin
  GetProcedureAddress(_connect, ws2_32, 'connect');
  asm
    mov esp, ebp
    pop ebp
    jmp [_connect]
  end;
end;
{$ELSE}
function connect; external ws2_32 name 'connect';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ioctlsocket: Pointer;

function ioctlsocket;
begin
  GetProcedureAddress(_ioctlsocket, ws2_32, 'ioctlsocket');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ioctlsocket]
  end;
end;
{$ELSE}
function ioctlsocket; external ws2_32 name 'ioctlsocket';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _getpeername: Pointer;

function getpeername;
begin
  GetProcedureAddress(_getpeername, ws2_32, 'getpeername');
  asm
    mov esp, ebp
    pop ebp
    jmp [_getpeername]
  end;
end;
{$ELSE}
function getpeername; external ws2_32 name 'getpeername';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _getsockname: Pointer;

function getsockname;
begin
  GetProcedureAddress(_getsockname, ws2_32, 'getsockname');
  asm
    mov esp, ebp
    pop ebp
    jmp [_getsockname]
  end;
end;
{$ELSE}
function getsockname; external ws2_32 name 'getsockname';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _getsockopt: Pointer;

function getsockopt;
begin
  GetProcedureAddress(_getsockopt, ws2_32, 'getsockopt');
  asm
    mov esp, ebp
    pop ebp
    jmp [_getsockopt]
  end;
end;
{$ELSE}
function getsockopt; external ws2_32 name 'getsockopt';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _htonl: Pointer;

function htonl;
begin
  GetProcedureAddress(_htonl, ws2_32, 'htonl');
  asm
    mov esp, ebp
    pop ebp
    jmp [_htonl]
  end;
end;
{$ELSE}
function htonl; external ws2_32 name 'htonl';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _htons: Pointer;

function htons;
begin
  GetProcedureAddress(_htons, ws2_32, 'htons');
  asm
    mov esp, ebp
    pop ebp
    jmp [_htons]
  end;
end;
{$ELSE}
function htons; external ws2_32 name 'htons';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _inet_addr: Pointer;

function inet_addr;
begin
  GetProcedureAddress(_inet_addr, ws2_32, 'inet_addr');
  asm
    mov esp, ebp
    pop ebp
    jmp [_inet_addr]
  end;
end;
{$ELSE}
function inet_addr; external ws2_32 name 'inet_addr';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _inet_ntoa: Pointer;

function inet_ntoa;
begin
  GetProcedureAddress(_inet_ntoa, ws2_32, 'inet_ntoa');
  asm
    mov esp, ebp
    pop ebp
    jmp [_inet_ntoa]
  end;
end;
{$ELSE}
function inet_ntoa; external ws2_32 name 'inet_ntoa';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _listen: Pointer;

function listen;
begin
  GetProcedureAddress(_listen, ws2_32, 'listen');
  asm
    mov esp, ebp
    pop ebp
    jmp [_listen]
  end;
end;
{$ELSE}
function listen; external ws2_32 name 'listen';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ntohl: Pointer;

function ntohl;
begin
  GetProcedureAddress(_ntohl, ws2_32, 'ntohl');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ntohl]
  end;
end;
{$ELSE}
function ntohl; external ws2_32 name 'ntohl';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ntohs: Pointer;

function ntohs;
begin
  GetProcedureAddress(_ntohs, ws2_32, 'ntohs');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ntohs]
  end;
end;
{$ELSE}
function ntohs; external ws2_32 name 'ntohs';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _recv: Pointer;

function recv;
begin
  GetProcedureAddress(_recv, ws2_32, 'recv');
  asm
    mov esp, ebp
    pop ebp
    jmp [_recv]
  end;
end;
{$ELSE}
function recv; external ws2_32 name 'recv';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _recvfrom: Pointer;

function recvfrom;
begin
  GetProcedureAddress(_recvfrom, ws2_32, 'recvfrom');
  asm
    mov esp, ebp
    pop ebp
    jmp [_recvfrom]
  end;
end;
{$ELSE}
function recvfrom; external ws2_32 name 'recvfrom';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _select: Pointer;

function select;
begin
  GetProcedureAddress(_select, ws2_32, 'select');
  asm
    mov esp, ebp
    pop ebp
    jmp [_select]
  end;
end;
{$ELSE}
function select; external ws2_32 name 'select';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _send: Pointer;

function send;
begin
  GetProcedureAddress(_send, ws2_32, 'send');
  asm
    mov esp, ebp
    pop ebp
    jmp [_send]
  end;
end;
{$ELSE}
function send; external ws2_32 name 'send';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _sendto: Pointer;

function sendto;
begin
  GetProcedureAddress(_sendto, ws2_32, 'sendto');
  asm
    mov esp, ebp
    pop ebp
    jmp [_sendto]
  end;
end;
{$ELSE}
function sendto; external ws2_32 name 'sendto';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _setsockopt: Pointer;

function setsockopt;
begin
  GetProcedureAddress(_setsockopt, ws2_32, 'setsockopt');
  asm
    mov esp, ebp
    pop ebp
    jmp [_setsockopt]
  end;
end;
{$ELSE}
function setsockopt; external ws2_32 name 'setsockopt';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _shutdown: Pointer;

function shutdown;
begin
  GetProcedureAddress(_shutdown, ws2_32, 'shutdown');
  asm
    mov esp, ebp
    pop ebp
    jmp [_shutdown]
  end;
end;
{$ELSE}
function shutdown; external ws2_32 name 'shutdown';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _socket: Pointer;

function socket;
begin
  GetProcedureAddress(_socket, ws2_32, 'socket');
  asm
    mov esp, ebp
    pop ebp
    jmp [_socket]
  end;
end;
{$ELSE}
function socket; external ws2_32 name 'socket';
{$ENDIF DYNAMIC_LINK}


{$IFDEF DYNAMIC_LINK}
var
  _gethostbyaddr: Pointer;

function gethostbyaddr;
begin
  GetProcedureAddress(_gethostbyaddr, ws2_32, 'gethostbyaddr');
  asm
    mov esp, ebp
    pop ebp
    jmp [_gethostbyaddr]
  end;
end;
{$ELSE}
function gethostbyaddr; external ws2_32 name 'gethostbyaddr';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _gethostbyname: Pointer;

function gethostbyname;
begin
  GetProcedureAddress(_gethostbyname, ws2_32, 'gethostbyname');
  asm
    mov esp, ebp
    pop ebp
    jmp [_gethostbyname]
  end;
end;
{$ELSE}
function gethostbyname; external ws2_32 name 'gethostbyname';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _gethostname: Pointer;

function gethostname;
begin
  GetProcedureAddress(_gethostname, ws2_32, 'gethostname');
  asm
    mov esp, ebp
    pop ebp
    jmp [_gethostname]
  end;
end;
{$ELSE}
function gethostname; external ws2_32 name 'gethostname';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _getservbyport: Pointer;

function getservbyport;
begin
  GetProcedureAddress(_getservbyport, ws2_32, 'getservbyport');
  asm
    mov esp, ebp
    pop ebp
    jmp [_getservbyport]
  end;
end;
{$ELSE}
function getservbyport; external ws2_32 name 'getservbyport';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _getservbyname: Pointer;

function getservbyname;
begin
  GetProcedureAddress(_getservbyname, ws2_32, 'getservbyname');
  asm
    mov esp, ebp
    pop ebp
    jmp [_getservbyname]
  end;
end;
{$ELSE}
function getservbyname; external ws2_32 name 'getservbyname';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _getprotobynumber: Pointer;

function getprotobynumber;
begin
  GetProcedureAddress(_getprotobynumber, ws2_32, 'getprotobynumber');
  asm
    mov esp, ebp
    pop ebp
    jmp [_getprotobynumber]
  end;
end;
{$ELSE}
function getprotobynumber; external ws2_32 name 'getprotobynumber';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _getprotobyname: Pointer;

function getprotobyname;
begin
  GetProcedureAddress(_getprotobyname, ws2_32, 'getprotobyname');
  asm
    mov esp, ebp
    pop ebp
    jmp [_getprotobyname]
  end;
end;
{$ELSE}
function getprotobyname; external ws2_32 name 'getprotobyname';
{$ENDIF DYNAMIC_LINK}


{$IFDEF DYNAMIC_LINK}
var
  _WSAStartup: Pointer;

function WSAStartup;
begin
  GetProcedureAddress(_WSAStartup, ws2_32, 'WSAStartup');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAStartup]
  end;
end;
{$ELSE}
function WSAStartup; external ws2_32 name 'WSAStartup';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSACleanup: Pointer;

function WSACleanup;
begin
  GetProcedureAddress(_WSACleanup, ws2_32, 'WSACleanup');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSACleanup]
  end;
end;
{$ELSE}
function WSACleanup; external ws2_32 name 'WSACleanup';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSASetLastError: Pointer;

procedure WSASetLastError;
begin
  GetProcedureAddress(_WSASetLastError, ws2_32, 'WSASetLastError');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSASetLastError]
  end;
end;
{$ELSE}
procedure WSASetLastError; external ws2_32 name 'WSASetLastError';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSAGetLastError: Pointer;

function WSAGetLastError;
begin
  GetProcedureAddress(_WSAGetLastError, ws2_32, 'WSAGetLastError');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAGetLastError]
  end;
end;
{$ELSE}
function WSAGetLastError; external ws2_32 name 'WSAGetLastError';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSAIsBlocking: Pointer;

function WSAIsBlocking;
begin
  GetProcedureAddress(_WSAIsBlocking, ws2_32, 'WSAIsBlocking');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAIsBlocking]
  end;
end;
{$ELSE}
function WSAIsBlocking; external ws2_32 name 'WSAIsBlocking';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSAUnhookBlockingHook: Pointer;

function WSAUnhookBlockingHook;
begin
  GetProcedureAddress(_WSAUnhookBlockingHook, ws2_32, 'WSAUnhookBlockingHook');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAUnhookBlockingHook]
  end;
end;
{$ELSE}
function WSAUnhookBlockingHook; external ws2_32 name 'WSAUnhookBlockingHook';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSASetBlockingHook: Pointer;

function WSASetBlockingHook;
begin
  GetProcedureAddress(_WSASetBlockingHook, ws2_32, 'WSASetBlockingHook');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSASetBlockingHook]
  end;
end;
{$ELSE}
function WSASetBlockingHook; external ws2_32 name 'WSASetBlockingHook';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSACancelBlockingCall: Pointer;

function WSACancelBlockingCall;
begin
  GetProcedureAddress(_WSACancelBlockingCall, ws2_32, 'WSACancelBlockingCall');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSACancelBlockingCall]
  end;
end;
{$ELSE}
function WSACancelBlockingCall; external ws2_32 name 'WSACancelBlockingCall';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSAAsyncGetServByName: Pointer;

function WSAAsyncGetServByName;
begin
  GetProcedureAddress(_WSAAsyncGetServByName, ws2_32, 'WSAAsyncGetServByName');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAAsyncGetServByName]
  end;
end;
{$ELSE}
function WSAAsyncGetServByName; external ws2_32 name 'WSAAsyncGetServByName';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSAAsyncGetServByPort: Pointer;

function WSAAsyncGetServByPort;
begin
  GetProcedureAddress(_WSAAsyncGetServByPort, ws2_32, 'WSAAsyncGetServByPort');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAAsyncGetServByPort]
  end;
end;
{$ELSE}
function WSAAsyncGetServByPort; external ws2_32 name 'WSAAsyncGetServByPort';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSAAsyncGetProtoByName: Pointer;

function WSAAsyncGetProtoByName;
begin
  GetProcedureAddress(_WSAAsyncGetProtoByName, ws2_32, 'WSAAsyncGetProtoByName');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAAsyncGetProtoByName]
  end;
end;
{$ELSE}
function WSAAsyncGetProtoByName; external ws2_32 name 'WSAAsyncGetProtoByName';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSAAsyncGetProtoByNumber: Pointer;

function WSAAsyncGetProtoByNumber;
begin
  GetProcedureAddress(_WSAAsyncGetProtoByNumber, ws2_32, 'WSAAsyncGetProtoByNumber');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAAsyncGetProtoByNumber]
  end;
end;
{$ELSE}
function WSAAsyncGetProtoByNumber; external ws2_32 name 'WSAAsyncGetProtoByNumber';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSAAsyncGetHostByName: Pointer;

function WSAAsyncGetHostByName;
begin
  GetProcedureAddress(_WSAAsyncGetHostByName, ws2_32, 'WSAAsyncGetHostByName');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAAsyncGetHostByName]
  end;
end;
{$ELSE}
function WSAAsyncGetHostByName; external ws2_32 name 'WSAAsyncGetHostByName';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSAAsyncGetHostByAddr: Pointer;

function WSAAsyncGetHostByAddr;
begin
  GetProcedureAddress(_WSAAsyncGetHostByAddr, ws2_32, 'WSAAsyncGetHostByAddr');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAAsyncGetHostByAddr]
  end;
end;
{$ELSE}
function WSAAsyncGetHostByAddr; external ws2_32 name 'WSAAsyncGetHostByAddr';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSACancelAsyncRequest: Pointer;

function WSACancelAsyncRequest;
begin
  GetProcedureAddress(_WSACancelAsyncRequest, ws2_32, 'WSACancelAsyncRequest');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSACancelAsyncRequest]
  end;
end;
{$ELSE}
function WSACancelAsyncRequest; external ws2_32 name 'WSACancelAsyncRequest';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSAAsyncSelect: Pointer;

function WSAAsyncSelect;
begin
  GetProcedureAddress(_WSAAsyncSelect, ws2_32, 'WSAAsyncSelect');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAAsyncSelect]
  end;
end;
{$ELSE}
function WSAAsyncSelect; external ws2_32 name 'WSAAsyncSelect';
{$ENDIF DYNAMIC_LINK}


{$IFDEF DYNAMIC_LINK}
var
  _WSAAccept: Pointer;

function WSAAccept;
begin
  GetProcedureAddress(_WSAAccept, ws2_32, 'WSAAccept');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAAccept]
  end;
end;
{$ELSE}
function WSAAccept; external ws2_32 name 'WSAAccept';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSACloseEvent: Pointer;

function WSACloseEvent;
begin
  GetProcedureAddress(_WSACloseEvent, ws2_32, 'WSACloseEvent');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSACloseEvent]
  end;
end;
{$ELSE}
function WSACloseEvent; external ws2_32 name 'WSACloseEvent';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSAConnect: Pointer;

function WSAConnect;
begin
  GetProcedureAddress(_WSAConnect, ws2_32, 'WSAConnect');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAConnect]
  end;
end;
{$ELSE}
function WSAConnect; external ws2_32 name 'WSAConnect';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSACreateEvent: Pointer;

function WSACreateEvent;
begin
  GetProcedureAddress(_WSACreateEvent, ws2_32, 'WSACreateEvent');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSACreateEvent]
  end;
end;
{$ELSE}
function WSACreateEvent; external ws2_32 name 'WSACreateEvent';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSADuplicateSocketA: Pointer;

function WSADuplicateSocketA;
begin
  GetProcedureAddress(_WSADuplicateSocketA, ws2_32, 'WSADuplicateSocketA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSADuplicateSocketA]
  end;
end;
{$ELSE}
function WSADuplicateSocketA; external ws2_32 name 'WSADuplicateSocketA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSADuplicateSocketW: Pointer;

function WSADuplicateSocketW;
begin
  GetProcedureAddress(_WSADuplicateSocketW, ws2_32, 'WSADuplicateSocketW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSADuplicateSocketW]
  end;
end;
{$ELSE}
function WSADuplicateSocketW; external ws2_32 name 'WSADuplicateSocketW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _WSADuplicateSocket: Pointer;

function WSADuplicateSocket;
begin
  GetProcedureAddress(_WSADuplicateSocket, ws2_32, 'WSADuplicateSocketW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSADuplicateSocket]
  end;
end;
{$ELSE}
function WSADuplicateSocket; external ws2_32 name 'WSADuplicateSocketW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _WSADuplicateSocket: Pointer;

function WSADuplicateSocket;
begin
  GetProcedureAddress(_WSADuplicateSocket, ws2_32, 'WSADuplicateSocketA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSADuplicateSocket]
  end;
end;
{$ELSE}
function WSADuplicateSocket; external ws2_32 name 'WSADuplicateSocketA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _WSAEnumNetworkEvents: Pointer;

function WSAEnumNetworkEvents;
begin
  GetProcedureAddress(_WSAEnumNetworkEvents, ws2_32, 'WSAEnumNetworkEvents');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAEnumNetworkEvents]
  end;
end;
{$ELSE}
function WSAEnumNetworkEvents; external ws2_32 name 'WSAEnumNetworkEvents';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSAEnumProtocolsA: Pointer;

function WSAEnumProtocolsA;
begin
  GetProcedureAddress(_WSAEnumProtocolsA, ws2_32, 'WSAEnumProtocolsA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAEnumProtocolsA]
  end;
end;
{$ELSE}
function WSAEnumProtocolsA; external ws2_32 name 'WSAEnumProtocolsA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSAEnumProtocolsW: Pointer;

function WSAEnumProtocolsW;
begin
  GetProcedureAddress(_WSAEnumProtocolsW, ws2_32, 'WSAEnumProtocolsW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAEnumProtocolsW]
  end;
end;
{$ELSE}
function WSAEnumProtocolsW; external ws2_32 name 'WSAEnumProtocolsW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _WSAEnumProtocols: Pointer;

function WSAEnumProtocols;
begin
  GetProcedureAddress(_WSAEnumProtocols, ws2_32, 'WSAEnumProtocolsW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAEnumProtocols]
  end;
end;
{$ELSE}
function WSAEnumProtocols; external ws2_32 name 'WSAEnumProtocolsW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _WSAEnumProtocols: Pointer;

function WSAEnumProtocols;
begin
  GetProcedureAddress(_WSAEnumProtocols, ws2_32, 'WSAEnumProtocolsA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAEnumProtocols]
  end;
end;
{$ELSE}
function WSAEnumProtocols; external ws2_32 name 'WSAEnumProtocolsA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _WSAEventSelect: Pointer;

function WSAEventSelect;
begin
  GetProcedureAddress(_WSAEventSelect, ws2_32, 'WSAEventSelect');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAEventSelect]
  end;
end;
{$ELSE}
function WSAEventSelect; external ws2_32 name 'WSAEventSelect';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSAGetOverlappedResult: Pointer;

function WSAGetOverlappedResult;
begin
  GetProcedureAddress(_WSAGetOverlappedResult, ws2_32, 'WSAGetOverlappedResult');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAGetOverlappedResult]
  end;
end;
{$ELSE}
function WSAGetOverlappedResult; external ws2_32 name 'WSAGetOverlappedResult';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSAGetQOSByName: Pointer;

function WSAGetQOSByName;
begin
  GetProcedureAddress(_WSAGetQOSByName, ws2_32, 'WSAGetQOSByName');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAGetQOSByName]
  end;
end;
{$ELSE}
function WSAGetQOSByName; external ws2_32 name 'WSAGetQOSByName';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSAHtonl: Pointer;

function WSAHtonl;
begin
  GetProcedureAddress(_WSAHtonl, ws2_32, 'WSAHtonl');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAHtonl]
  end;
end;
{$ELSE}
function WSAHtonl; external ws2_32 name 'WSAHtonl';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSAHtons: Pointer;

function WSAHtons;
begin
  GetProcedureAddress(_WSAHtons, ws2_32, 'WSAHtons');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAHtons]
  end;
end;
{$ELSE}
function WSAHtons; external ws2_32 name 'WSAHtons';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSAIoctl: Pointer;

function WSAIoctl;
begin
  GetProcedureAddress(_WSAIoctl, ws2_32, 'WSAIoctl');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAIoctl]
  end;
end;
{$ELSE}
function WSAIoctl; external ws2_32 name 'WSAIoctl';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSAJoinLeaf: Pointer;

function WSAJoinLeaf;
begin
  GetProcedureAddress(_WSAJoinLeaf, ws2_32, 'WSAJoinLeaf');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAJoinLeaf]
  end;
end;
{$ELSE}
function WSAJoinLeaf; external ws2_32 name 'WSAJoinLeaf';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSANtohl: Pointer;

function WSANtohl;
begin
  GetProcedureAddress(_WSANtohl, ws2_32, 'WSANtohl');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSANtohl]
  end;
end;
{$ELSE}
function WSANtohl; external ws2_32 name 'WSANtohl';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSANtohs: Pointer;

function WSANtohs;
begin
  GetProcedureAddress(_WSANtohs, ws2_32, 'WSANtohs');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSANtohs]
  end;
end;
{$ELSE}
function WSANtohs; external ws2_32 name 'WSANtohs';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSARecv: Pointer;

function WSARecv;
begin
  GetProcedureAddress(_WSARecv, ws2_32, 'WSARecv');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSARecv]
  end;
end;
{$ELSE}
function WSARecv; external ws2_32 name 'WSARecv';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSARecvDisconnect: Pointer;

function WSARecvDisconnect;
begin
  GetProcedureAddress(_WSARecvDisconnect, ws2_32, 'WSARecvDisconnect');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSARecvDisconnect]
  end;
end;
{$ELSE}
function WSARecvDisconnect; external ws2_32 name 'WSARecvDisconnect';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSARecvFrom: Pointer;

function WSARecvFrom;
begin
  GetProcedureAddress(_WSARecvFrom, ws2_32, 'WSARecvFrom');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSARecvFrom]
  end;
end;
{$ELSE}
function WSARecvFrom; external ws2_32 name 'WSARecvFrom';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSAResetEvent: Pointer;

function WSAResetEvent;
begin
  GetProcedureAddress(_WSAResetEvent, ws2_32, 'WSAResetEvent');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAResetEvent]
  end;
end;
{$ELSE}
function WSAResetEvent; external ws2_32 name 'WSAResetEvent';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSASend: Pointer;

function WSASend;
begin
  GetProcedureAddress(_WSASend, ws2_32, 'WSASend');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSASend]
  end;
end;
{$ELSE}
function WSASend; external ws2_32 name 'WSASend';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSASendDisconnect: Pointer;

function WSASendDisconnect;
begin
  GetProcedureAddress(_WSASendDisconnect, ws2_32, 'WSASendDisconnect');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSASendDisconnect]
  end;
end;
{$ELSE}
function WSASendDisconnect; external ws2_32 name 'WSASendDisconnect';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSASendTo: Pointer;

function WSASendTo;
begin
  GetProcedureAddress(_WSASendTo, ws2_32, 'WSASendTo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSASendTo]
  end;
end;
{$ELSE}
function WSASendTo; external ws2_32 name 'WSASendTo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSASetEvent: Pointer;

function WSASetEvent;
begin
  GetProcedureAddress(_WSASetEvent, ws2_32, 'WSASetEvent');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSASetEvent]
  end;
end;
{$ELSE}
function WSASetEvent; external ws2_32 name 'WSASetEvent';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSASocketA: Pointer;

function WSASocketA;
begin
  GetProcedureAddress(_WSASocketA, ws2_32, 'WSASocketA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSASocketA]
  end;
end;
{$ELSE}
function WSASocketA; external ws2_32 name 'WSASocketA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSASocketW: Pointer;

function WSASocketW;
begin
  GetProcedureAddress(_WSASocketW, ws2_32, 'WSASocketW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSASocketW]
  end;
end;
{$ELSE}
function WSASocketW; external ws2_32 name 'WSASocketW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _WSASocket: Pointer;

function WSASocket;
begin
  GetProcedureAddress(_WSASocket, ws2_32, 'WSASocketW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSASocket]
  end;
end;
{$ELSE}
function WSASocket; external ws2_32 name 'WSASocketW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _WSASocket: Pointer;

function WSASocket;
begin
  GetProcedureAddress(_WSASocket, ws2_32, 'WSASocketA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSASocket]
  end;
end;
{$ELSE}
function WSASocket; external ws2_32 name 'WSASocketA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _WSAWaitForMultipleEvents: Pointer;

function WSAWaitForMultipleEvents;
begin
  GetProcedureAddress(_WSAWaitForMultipleEvents, ws2_32, 'WSAWaitForMultipleEvents');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAWaitForMultipleEvents]
  end;
end;
{$ELSE}
function WSAWaitForMultipleEvents; external ws2_32 name 'WSAWaitForMultipleEvents';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSAAddressToStringA: Pointer;

function WSAAddressToStringA;
begin
  GetProcedureAddress(_WSAAddressToStringA, ws2_32, 'WSAAddressToStringA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAAddressToStringA]
  end;
end;
{$ELSE}
function WSAAddressToStringA; external ws2_32 name 'WSAAddressToStringA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSAAddressToStringW: Pointer;

function WSAAddressToStringW;
begin
  GetProcedureAddress(_WSAAddressToStringW, ws2_32, 'WSAAddressToStringW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAAddressToStringW]
  end;
end;
{$ELSE}
function WSAAddressToStringW; external ws2_32 name 'WSAAddressToStringW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _WSAAddressToString: Pointer;

function WSAAddressToString;
begin
  GetProcedureAddress(_WSAAddressToString, ws2_32, 'WSAAddressToStringW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAAddressToString]
  end;
end;
{$ELSE}
function WSAAddressToString; external ws2_32 name 'WSAAddressToStringW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _WSAAddressToString: Pointer;

function WSAAddressToString;
begin
  GetProcedureAddress(_WSAAddressToString, ws2_32, 'WSAAddressToStringA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAAddressToString]
  end;
end;
{$ELSE}
function WSAAddressToString; external ws2_32 name 'WSAAddressToStringA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _WSAStringToAddressA: Pointer;

function WSAStringToAddressA;
begin
  GetProcedureAddress(_WSAStringToAddressA, ws2_32, 'WSAStringToAddressA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAStringToAddressA]
  end;
end;
{$ELSE}
function WSAStringToAddressA; external ws2_32 name 'WSAStringToAddressA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSAStringToAddressW: Pointer;

function WSAStringToAddressW;
begin
  GetProcedureAddress(_WSAStringToAddressW, ws2_32, 'WSAStringToAddressW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAStringToAddressW]
  end;
end;
{$ELSE}
function WSAStringToAddressW; external ws2_32 name 'WSAStringToAddressW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _WSAStringToAddress: Pointer;

function WSAStringToAddress;
begin
  GetProcedureAddress(_WSAStringToAddress, ws2_32, 'WSAStringToAddressW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAStringToAddress]
  end;
end;
{$ELSE}
function WSAStringToAddress; external ws2_32 name 'WSAStringToAddressW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _WSAStringToAddress: Pointer;

function WSAStringToAddress;
begin
  GetProcedureAddress(_WSAStringToAddress, ws2_32, 'WSAStringToAddressA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAStringToAddress]
  end;
end;
{$ELSE}
function WSAStringToAddress; external ws2_32 name 'WSAStringToAddressA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}


{$IFDEF DYNAMIC_LINK}
var
  _WSALookupServiceBeginA: Pointer;

function WSALookupServiceBeginA;
begin
  GetProcedureAddress(_WSALookupServiceBeginA, ws2_32, 'WSALookupServiceBeginA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSALookupServiceBeginA]
  end;
end;
{$ELSE}
function WSALookupServiceBeginA; external ws2_32 name 'WSALookupServiceBeginA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSALookupServiceBeginW: Pointer;

function WSALookupServiceBeginW;
begin
  GetProcedureAddress(_WSALookupServiceBeginW, ws2_32, 'WSALookupServiceBeginW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSALookupServiceBeginW]
  end;
end;
{$ELSE}
function WSALookupServiceBeginW; external ws2_32 name 'WSALookupServiceBeginW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _WSALookupServiceBegin: Pointer;

function WSALookupServiceBegin;
begin
  GetProcedureAddress(_WSALookupServiceBegin, ws2_32, 'WSALookupServiceBeginW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSALookupServiceBegin]
  end;
end;
{$ELSE}
function WSALookupServiceBegin; external ws2_32 name 'WSALookupServiceBeginW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _WSALookupServiceBegin: Pointer;

function WSALookupServiceBegin;
begin
  GetProcedureAddress(_WSALookupServiceBegin, ws2_32, 'WSALookupServiceBeginA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSALookupServiceBegin]
  end;
end;
{$ELSE}
function WSALookupServiceBegin; external ws2_32 name 'WSALookupServiceBeginA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _WSALookupServiceNextA: Pointer;

function WSALookupServiceNextA;
begin
  GetProcedureAddress(_WSALookupServiceNextA, ws2_32, 'WSALookupServiceNextA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSALookupServiceNextA]
  end;
end;
{$ELSE}
function WSALookupServiceNextA; external ws2_32 name 'WSALookupServiceNextA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSALookupServiceNextW: Pointer;

function WSALookupServiceNextW;
begin
  GetProcedureAddress(_WSALookupServiceNextW, ws2_32, 'WSALookupServiceNextW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSALookupServiceNextW]
  end;
end;
{$ELSE}
function WSALookupServiceNextW; external ws2_32 name 'WSALookupServiceNextW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _WSALookupServiceNext: Pointer;

function WSALookupServiceNext;
begin
  GetProcedureAddress(_WSALookupServiceNext, ws2_32, 'WSALookupServiceNextW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSALookupServiceNext]
  end;
end;
{$ELSE}
function WSALookupServiceNext; external ws2_32 name 'WSALookupServiceNextW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _WSALookupServiceNext: Pointer;

function WSALookupServiceNext;
begin
  GetProcedureAddress(_WSALookupServiceNext, ws2_32, 'WSALookupServiceNextA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSALookupServiceNext]
  end;
end;
{$ELSE}
function WSALookupServiceNext; external ws2_32 name 'WSALookupServiceNextA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _WSANSPIoctl: Pointer;

function WSANSPIoctl;
begin
  GetProcedureAddress(_WSANSPIoctl, ws2_32, 'WSANSPIoctl');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSANSPIoctl]
  end;
end;
{$ELSE}
function WSANSPIoctl; external ws2_32 name 'WSANSPIoctl';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSALookupServiceEnd: Pointer;

function WSALookupServiceEnd;
begin
  GetProcedureAddress(_WSALookupServiceEnd, ws2_32, 'WSALookupServiceEnd');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSALookupServiceEnd]
  end;
end;
{$ELSE}
function WSALookupServiceEnd; external ws2_32 name 'WSALookupServiceEnd';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSAInstallServiceClassA: Pointer;

function WSAInstallServiceClassA;
begin
  GetProcedureAddress(_WSAInstallServiceClassA, ws2_32, 'WSAInstallServiceClassA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAInstallServiceClassA]
  end;
end;
{$ELSE}
function WSAInstallServiceClassA; external ws2_32 name 'WSAInstallServiceClassA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSAInstallServiceClassW: Pointer;

function WSAInstallServiceClassW;
begin
  GetProcedureAddress(_WSAInstallServiceClassW, ws2_32, 'WSAInstallServiceClassW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAInstallServiceClassW]
  end;
end;
{$ELSE}
function WSAInstallServiceClassW; external ws2_32 name 'WSAInstallServiceClassW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _WSAInstallServiceClass: Pointer;

function WSAInstallServiceClass;
begin
  GetProcedureAddress(_WSAInstallServiceClass, ws2_32, 'WSAInstallServiceClassW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAInstallServiceClass]
  end;
end;
{$ELSE}
function WSAInstallServiceClass; external ws2_32 name 'WSAInstallServiceClassW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _WSAInstallServiceClass: Pointer;

function WSAInstallServiceClass;
begin
  GetProcedureAddress(_WSAInstallServiceClass, ws2_32, 'WSAInstallServiceClassA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAInstallServiceClass]
  end;
end;
{$ELSE}
function WSAInstallServiceClass; external ws2_32 name 'WSAInstallServiceClassA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _WSARemoveServiceClass: Pointer;

function WSARemoveServiceClass;
begin
  GetProcedureAddress(_WSARemoveServiceClass, ws2_32, 'WSARemoveServiceClass');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSARemoveServiceClass]
  end;
end;
{$ELSE}
function WSARemoveServiceClass; external ws2_32 name 'WSARemoveServiceClass';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSAGetServiceClassInfoA: Pointer;

function WSAGetServiceClassInfoA;
begin
  GetProcedureAddress(_WSAGetServiceClassInfoA, ws2_32, 'WSAGetServiceClassInfoA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAGetServiceClassInfoA]
  end;
end;
{$ELSE}
function WSAGetServiceClassInfoA; external ws2_32 name 'WSAGetServiceClassInfoA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSAGetServiceClassInfoW: Pointer;

function WSAGetServiceClassInfoW;
begin
  GetProcedureAddress(_WSAGetServiceClassInfoW, ws2_32, 'WSAGetServiceClassInfoW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAGetServiceClassInfoW]
  end;
end;
{$ELSE}
function WSAGetServiceClassInfoW; external ws2_32 name 'WSAGetServiceClassInfoW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _WSAGetServiceClassInfo: Pointer;

function WSAGetServiceClassInfo;
begin
  GetProcedureAddress(_WSAGetServiceClassInfo, ws2_32, 'WSAGetServiceClassInfoW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAGetServiceClassInfo]
  end;
end;
{$ELSE}
function WSAGetServiceClassInfo; external ws2_32 name 'WSAGetServiceClassInfoW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _WSAGetServiceClassInfo: Pointer;

function WSAGetServiceClassInfo;
begin
  GetProcedureAddress(_WSAGetServiceClassInfo, ws2_32, 'WSAGetServiceClassInfoA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAGetServiceClassInfo]
  end;
end;
{$ELSE}
function WSAGetServiceClassInfo; external ws2_32 name 'WSAGetServiceClassInfoA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _WSAEnumNameSpaceProvidersA: Pointer;

function WSAEnumNameSpaceProvidersA;
begin
  GetProcedureAddress(_WSAEnumNameSpaceProvidersA, ws2_32, 'WSAEnumNameSpaceProvidersA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAEnumNameSpaceProvidersA]
  end;
end;
{$ELSE}
function WSAEnumNameSpaceProvidersA; external ws2_32 name 'WSAEnumNameSpaceProvidersA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSAEnumNameSpaceProvidersW: Pointer;

function WSAEnumNameSpaceProvidersW;
begin
  GetProcedureAddress(_WSAEnumNameSpaceProvidersW, ws2_32, 'WSAEnumNameSpaceProvidersW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAEnumNameSpaceProvidersW]
  end;
end;
{$ELSE}
function WSAEnumNameSpaceProvidersW; external ws2_32 name 'WSAEnumNameSpaceProvidersW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _WSAEnumNameSpaceProviders: Pointer;

function WSAEnumNameSpaceProviders;
begin
  GetProcedureAddress(_WSAEnumNameSpaceProviders, ws2_32, 'WSAEnumNameSpaceProvidersW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAEnumNameSpaceProviders]
  end;
end;
{$ELSE}
function WSAEnumNameSpaceProviders; external ws2_32 name 'WSAEnumNameSpaceProvidersW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _WSAEnumNameSpaceProviders: Pointer;

function WSAEnumNameSpaceProviders;
begin
  GetProcedureAddress(_WSAEnumNameSpaceProviders, ws2_32, 'WSAEnumNameSpaceProvidersA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAEnumNameSpaceProviders]
  end;
end;
{$ELSE}
function WSAEnumNameSpaceProviders; external ws2_32 name 'WSAEnumNameSpaceProvidersA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _WSAGetServClassNameByClassIdA: Pointer;

function WSAGetServiceClassNameByClassIdA;
begin
  GetProcedureAddress(_WSAGetServClassNameByClassIdA, ws2_32, 'WSAGetServiceClassNameByClassIdA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAGetServClassNameByClassIdA]
  end;
end;
{$ELSE}
function WSAGetServiceClassNameByClassIdA; external ws2_32 name 'WSAGetServiceClassNameByClassIdA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSAGetServClassNameByClassIdW: Pointer;

function WSAGetServiceClassNameByClassIdW;
begin
  GetProcedureAddress(_WSAGetServClassNameByClassIdW, ws2_32, 'WSAGetServiceClassNameByClassIdW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAGetServClassNameByClassIdW]
  end;
end;
{$ELSE}
function WSAGetServiceClassNameByClassIdW; external ws2_32 name 'WSAGetServiceClassNameByClassIdW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _WSAGetServClassNameByClassId: Pointer;

function WSAGetServiceClassNameByClassId;
begin
  GetProcedureAddress(_WSAGetServClassNameByClassId, ws2_32, 'WSAGetServiceClassNameByClassIdW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAGetServClassNameByClassId]
  end;
end;
{$ELSE}
function WSAGetServiceClassNameByClassId; external ws2_32 name 'WSAGetServiceClassNameByClassIdW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _WSAGetServClassNameByClassId: Pointer;

function WSAGetServiceClassNameByClassId;
begin
  GetProcedureAddress(_WSAGetServClassNameByClassId, ws2_32, 'WSAGetServiceClassNameByClassIdA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAGetServClassNameByClassId]
  end;
end;
{$ELSE}
function WSAGetServiceClassNameByClassId; external ws2_32 name 'WSAGetServiceClassNameByClassIdA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _WSASetServiceA: Pointer;

function WSASetServiceA;
begin
  GetProcedureAddress(_WSASetServiceA, ws2_32, 'WSASetServiceA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSASetServiceA]
  end;
end;
{$ELSE}
function WSASetServiceA; external ws2_32 name 'WSASetServiceA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSASetServiceW: Pointer;

function WSASetServiceW;
begin
  GetProcedureAddress(_WSASetServiceW, ws2_32, 'WSASetServiceW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSASetServiceW]
  end;
end;
{$ELSE}
function WSASetServiceW; external ws2_32 name 'WSASetServiceW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _WSASetService: Pointer;

function WSASetService;
begin
  GetProcedureAddress(_WSASetService, ws2_32, 'WSASetServiceW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSASetService]
  end;
end;
{$ELSE}
function WSASetService; external ws2_32 name 'WSASetServiceW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _WSASetService: Pointer;

function WSASetService;
begin
  GetProcedureAddress(_WSASetService, ws2_32, 'WSASetServiceA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSASetService]
  end;
end;
{$ELSE}
function WSASetService; external ws2_32 name 'WSASetServiceA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _WSAProviderConfigChange: Pointer;

function WSAProviderConfigChange;
begin
  GetProcedureAddress(_WSAProviderConfigChange, ws2_32, 'WSAProviderConfigChange');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAProviderConfigChange]
  end;
end;
{$ELSE}
function WSAProviderConfigChange; external ws2_32 name 'WSAProviderConfigChange';
{$ENDIF DYNAMIC_LINK}

function WSAMAKEASYNCREPLY(buflen, error: WORD): DWORD;
begin
  Result := MAKELONG(buflen, error);
end;

function WSAMAKESELECTREPLY(event, error: WORD): DWORD;
begin
  Result := MAKELONG(event, error);
end;

function WSAGETASYNCBUFLEN(lParam: DWORD): WORD;
begin
  Result := LOWORD(lParam);
end;

function WSAGETASYNCERROR(lParam: DWORD): WORD;
begin
  Result := HIWORD(lParam);
end;

function WSAGETSELECTEVENT(lParam: DWORD): WORD;
begin
  Result := LOWORD(lParam);
end;

function WSAGETSELECTERROR(lParam: DWORD): WORD;
begin
  Result := HIWORD(lParam);
end;

end.


