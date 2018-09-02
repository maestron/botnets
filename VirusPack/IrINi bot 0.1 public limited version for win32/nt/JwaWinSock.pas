{******************************************************************************}
{                                                       	               }
{ Winsock API interface Unit for Object Pascal                                 }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: winsock.h, released June 2000. The original Pascal     }
{ code is: WinSock.pas, released December 2000. The initial developer of the   }
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

unit JwaWinSock;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "winsock.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinType, JwaWinBase;

(*
 * Basic system type definitions, taken from the BSD file sys/types.h.
 *)

type
  u_char = Byte;
  {$EXTERNALSYM u_char}
  u_short = Word;
  {$EXTERNALSYM u_short}
  u_int = Cardinal;
  {$EXTERNALSYM u_int}
  u_long = Cardinal;
  {$EXTERNALSYM u_long}

(*
 * The new type to be used in all
 * instances which refer to sockets.
 *)

type
  TSocket = UINT_PTR;

(*
 * Select uses arrays of SOCKETs.  These macros manipulate such
 * arrays.  FD_SETSIZE may be defined by the user before including
 * this file, but the default here should be >= 64.
 *
 * CAVEAT IMPLEMENTOR and USER: THESE MACROS AND TYPES MUST BE
 * INCLUDED IN WINSOCK.H EXACTLY AS SHOWN HERE.
 *)

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

(*
 * Structure used in select() call, taken from the BSD file sys/time.h.
 *)

type
  timeval = record
    tv_sec: Longint;         // seconds
    tv_usec: Longint;        // and microseconds
  end;
  {$EXTERNALSYM timeval}
  TTimeVal = timeval;
  PTimeVal = ^timeval;

(*
 * Operations on timevals.
 *
 * NB: timercmp does not work for >= or <=.
 *)

function timerisset(const tvp: TTimeVal): Boolean;
{$EXTERNALSYM timerisset}

//function timercmp(const tvp, uvp: TTimeVal; cmp): Boolean;
//{$EXTERNALSYM timercmp}

procedure timerclear(var tvp: TTimeVal);
{$EXTERNALSYM timerclear}

(*
 * Commands for ioctlsocket(),  taken from the BSD file fcntl.h.
 *
 *
 * Ioctl's have the command encoded in the lower word,
 * and the size of any in or out parameters in the upper
 * word.  The high 2 bits of the upper word are used
 * to encode the in/out status of the parameter; for now
 * we restrict parameters to at most 128 bytes.
 *)

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
  FIONBIO = IOC_OUT or ((SizeOf(u_long) and IOCPARM_MASK) shl 16) or (Ord('f') shl 8) or 126; // set/clear non-blocking i/o
  {$EXTERNALSYM FIONBIO}
  FIOASYNC = IOC_OUT or ((SizeOf(u_long) and IOCPARM_MASK) shl 16) or (Ord('f') shl 8) or 125; // set/clear async i/o
  {$EXTERNALSYM FIOASYNC}

(* Socket I/O Controls *)

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

(*
 * Structures returned by network data base library, taken from the
 * BSD file netdb.h.  All addresses are supplied in host order, and
 * returned in network order (suitable for use in system calls).
 *)

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

(*
 * It is assumed here that a network number
 * fits in 32 bits.
 *)

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

(*
 * Constants and structures defined by the internet system,
 * Per RFC 790, September 1981, taken from the BSD file netinet/in.h.
 *)

(*
 * Protocols
 *)

const
  IPPROTO_IP   = 0; // dummy for IP
  {$EXTERNALSYM IPPROTO_IP}
  IPPROTO_ICMP = 1; // control message protocol
  {$EXTERNALSYM IPPROTO_ICMP}
  IPPROTO_IGMP = 2; // internet group management protocol
  {$EXTERNALSYM IPPROTO_IGMP}
  IPPROTO_GGP  = 3; // gateway^2 (deprecated)
  {$EXTERNALSYM IPPROTO_GGP}
  IPPROTO_TCP  = 6; // tcp
  {$EXTERNALSYM IPPROTO_TCP}
  IPPROTO_PUP  = 12; // pup
  {$EXTERNALSYM IPPROTO_PUP}
  IPPROTO_UDP  = 17; // user datagram protocol
  {$EXTERNALSYM IPPROTO_UDP}
  IPPROTO_IDP  = 22; // xns idp
  {$EXTERNALSYM IPPROTO_IDP}
  IPPROTO_ND   = 77; // UNOFFICIAL net disk proto
  {$EXTERNALSYM IPPROTO_ND}

  IPPROTO_RAW  = 255; // raw IP packet
  {$EXTERNALSYM IPPROTO_RAW}
  IPPROTO_MAX  = 256;
  {$EXTERNALSYM IPPROTO_MAX}

(*
 * Port/socket numbers: network standard functions
 *)

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

(*
 * Port/socket numbers: host specific functions
 *)

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

(*
 * UNIX TCP sockets
 *)

  IPPORT_EXECSERVER  = 512;
  {$EXTERNALSYM IPPORT_EXECSERVER}
  IPPORT_LOGINSERVER = 513;
  {$EXTERNALSYM IPPORT_LOGINSERVER}
  IPPORT_CMDSERVER   = 514;
  {$EXTERNALSYM IPPORT_CMDSERVER}
  IPPORT_EFSSERVER   = 520;
  {$EXTERNALSYM IPPORT_EFSSERVER}

(*
 * UNIX UDP sockets
 *)

  IPPORT_BIFFUDP     = 512;
  {$EXTERNALSYM IPPORT_BIFFUDP}
  IPPORT_WHOSERVER   = 513;
  {$EXTERNALSYM IPPORT_WHOSERVER}
  IPPORT_ROUTESERVER = 520;
  {$EXTERNALSYM IPPORT_ROUTESERVER}

  (* 520+1 also used *)

(*
 * Ports < IPPORT_RESERVED are reserved for
 * privileged processes (e.g. root).
 *)

  IPPORT_RESERVED = 1024;
  {$EXTERNALSYM IPPORT_RESERVED}

(*
 * Link numbers
 *)

  IMPLINK_IP        = 155;
  {$EXTERNALSYM IMPLINK_IP}
  IMPLINK_LOWEXPER  = 156;
  {$EXTERNALSYM IMPLINK_LOWEXPER}
  IMPLINK_HIGHEXPER = 158;
  {$EXTERNALSYM IMPLINK_HIGHEXPER}

(*
 * Internet address (old style... should be updated)
 *)

type
  SunB = packed record
    s_b1, s_b2, s_b3, s_b4: u_char;
  end;
  {$EXTERNALSYM SunB}

  SunW = packed record
    s_w1, s_w2: u_short;
  end;
  {$EXTERNALSYM SunW}

  in_addr = record
    case Integer of
      0: (S_un_b: SunB);
      1: (S_un_w: SunW);
      2: (S_addr: u_long);
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

(*
 * Definitions of bits in internet address integers.
 * On subnets, the decomposition of addresses to host and net parts
 * is done according to subnet mask, not the masks here.
 *)

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

const
  INADDR_ANY       = u_long($00000000);
  {$EXTERNALSYM INADDR_ANY}
  INADDR_LOOPBACK  = $7f000001;
  {$EXTERNALSYM INADDR_LOOPBACK}
  INADDR_BROADCAST = u_long($ffffffff);
  {$EXTERNALSYM INADDR_BROADCAST}
  INADDR_NONE      = DWORD($ffffffff);
  {$EXTERNALSYM INADDR_NONE}

(*
 * Socket address, internet style.
 *)

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

(*
 * Options for use with [gs]etsockopt at the IP level.
 *)

const
  IP_OPTIONS         = 1;           (* set/get IP per-packet options    *)
  {$EXTERNALSYM IP_OPTIONS}
  IP_MULTICAST_IF    = 2;           (* set/get IP multicast interface   *)
  {$EXTERNALSYM IP_MULTICAST_IF}
  IP_MULTICAST_TTL   = 3;           (* set/get IP multicast timetolive  *)
  {$EXTERNALSYM IP_MULTICAST_TTL}
  IP_MULTICAST_LOOP  = 4;           (* set/get IP multicast loopback    *)
  {$EXTERNALSYM IP_MULTICAST_LOOP}
  IP_ADD_MEMBERSHIP  = 5;           (* add  an IP group membership      *)
  {$EXTERNALSYM IP_ADD_MEMBERSHIP}
  IP_DROP_MEMBERSHIP = 6;           (* drop an IP group membership      *)
  {$EXTERNALSYM IP_DROP_MEMBERSHIP}
  IP_TTL             = 7;           (* set/get IP Time To Live          *)
  {$EXTERNALSYM IP_TTL}
  IP_TOS             = 8;           (* set/get IP Type Of Service       *)
  {$EXTERNALSYM IP_TOS}
  IP_DONTFRAGMENT    = 9;           (* set/get IP Don't Fragment flag   *)
  {$EXTERNALSYM IP_DONTFRAGMENT}

  IP_DEFAULT_MULTICAST_TTL  = 1;    (* normally limit m'casts to 1 hop  *)
  {$EXTERNALSYM IP_DEFAULT_MULTICAST_TTL}
  IP_DEFAULT_MULTICAST_LOOP = 1;    (* normally hear sends if a member  *)
  {$EXTERNALSYM IP_DEFAULT_MULTICAST_LOOP}
  IP_MAX_MEMBERSHIPS        = 20;   (* per socket; must fit in one mbuf *)
  {$EXTERNALSYM IP_MAX_MEMBERSHIPS}

(*
 * Argument structure for IP_ADD_MEMBERSHIP and IP_DROP_MEMBERSHIP.
 *)

type
  ip_mreq = record
    imr_multiaddr: in_addr;  (* IP multicast address of group *)
    mr_interface: in_addr;  (* local IP address of interface *)
  end;
  {$EXTERNALSYM ip_mreq}
  TIpMReq = ip_mreq;
  PIpMReq = ^ip_mreq;  

(*
 * Definitions related to sockets: types, address families, options,
 * taken from the BSD file sys/socket.h.
 *)

(*
 * This is used instead of -1, since the
 * SOCKET type is unsigned.
 *)

const
  INVALID_SOCKET = TSocket(not 0);
  {$EXTERNALSYM INVALID_SOCKET}
  SOCKET_ERROR   = -1;
  {$EXTERNALSYM SOCKET_ERROR}

(*
 * Types
 *)

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

(*
 * Option flags per-socket.
 *)

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

(*
 * Additional options.
 *)

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

(*
 * Options for connect and disconnect data and options.  Used only by
 * non-TCP/IP transports such as DECNet, OSI TP4, etc.
 *)

  SO_CONNDATA    = $7000;
  {$EXTERNALSYM SO_CONNDATA}
  SO_CONNOPT     = $7001;
  {$EXTERNALSYM SO_CONNOPT}
  SO_DISCDATA    = $7002;
  {$EXTERNALSYM SO_DISCDATA}
  SO_DISCOPT     = $7003;
  {$EXTERNALSYM SO_DISCOPT}
  SO_CONNDATALEN = $7004;
  {$EXTERNALSYM SO_CONNDATALEN}
  SO_CONNOPTLEN  = $7005;
  {$EXTERNALSYM SO_CONNOPTLEN}
  SO_DISCDATALEN = $7006;
  {$EXTERNALSYM SO_DISCDATALEN}
  SO_DISCOPTLEN  = $7007;
  {$EXTERNALSYM SO_DISCOPTLEN}

(*
 * Option for opening sockets for synchronous access.
 *)

  SO_OPENTYPE    = $7008;
  {$EXTERNALSYM SO_OPENTYPE}

  SO_SYNCHRONOUS_ALERT    = $10;
  {$EXTERNALSYM SO_SYNCHRONOUS_ALERT}
  SO_SYNCHRONOUS_NONALERT = $20;
  {$EXTERNALSYM SO_SYNCHRONOUS_NONALERT}

(*
 * Other NT-specific options.
 *)

  SO_MAXDG        = $7009;
  {$EXTERNALSYM SO_MAXDG}
  SO_MAXPATHDG    = $700A;
  {$EXTERNALSYM SO_MAXPATHDG}
  SO_UPDATE_ACCEPT_CONTEXT = $700B;
  {$EXTERNALSYM SO_UPDATE_ACCEPT_CONTEXT}
  SO_CONNECT_TIME = $700C;
  {$EXTERNALSYM SO_CONNECT_TIME}

(*
 * TCP options.
 *)

  TCP_NODELAY = $0001;
  {$EXTERNALSYM TCP_NODELAY}
  TCP_BSDURGENT = $7000;
  {$EXTERNALSYM TCP_BSDURGENT}

(*
 * Address families.
 *)

  AF_UNSPEC = 0; // unspecified
  {$EXTERNALSYM AF_UNSPEC}
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

  AF_MAX = 22;
  {$EXTERNALSYM AF_MAX}

(*
 * Structure used by kernel to store most
 * addresses.
 *)

type
  sockaddr = record
    sa_family: u_short;              // address family
    sa_data: array [0..13] of Char;            // up to 14 bytes of direct address
  end;
  {$EXTERNALSYM sockaddr}
  TSockAddr = sockaddr;
  PSockAddr = ^sockaddr;

(*
 * Structure used by kernel to pass protocol
 * information in raw sockets.
 *)

  sockproto = record
    sp_family: u_short;              // address family
    sp_protocol: u_short;            // protocol
  end;
  {$EXTERNALSYM sockproto}
  TSockProto = sockproto;
  PSockProto = ^sockproto;

(*
 * Protocol families, same as address families for now.
 *)

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

  PF_MAX = AF_MAX;
  {$EXTERNALSYM PF_MAX}


(*
 * Structure used for manipulating linger option.
 *)

type
  linger = record
    l_onoff: u_short;                // option on/off
    l_linger: u_short;               // linger time
  end;
  {$EXTERNALSYM linger}
  TLinger = linger;
  PLinger = ^linger;

(*
 * Level number for (get/set)sockopt() to apply to socket itself.
 *)

const
  SOL_SOCKET = $ffff; // options for socket level
  {$EXTERNALSYM SOL_SOCKET}

(*
 * Maximum queue length specifiable by listen.
 *)

  SOMAXCONN = $7fffffff;
  {$EXTERNALSYM SOMAXCONN}

  MSG_OOB       = $1; // process out-of-band data
  {$EXTERNALSYM MSG_OOB}
  MSG_PEEK      = $2; // peek at incoming message
  {$EXTERNALSYM MSG_PEEK}
  MSG_DONTROUTE = $4; // send without using routing tables
  {$EXTERNALSYM MSG_DONTROUTE}

  MSG_MAXIOVLEN = 16;
  {$EXTERNALSYM MSG_MAXIOVLEN}

  MSG_PARTIAL   = $8000; // partial send or recv for message xport
  {$EXTERNALSYM MSG_PARTIAL}

(*
 * Define constant based on rfc883, used by gethostbyxxxx() calls.
 *)

  MAXGETHOSTSTRUCT = 1024;
  {$EXTERNALSYM MAXGETHOSTSTRUCT}

(*
 * Define flags to be used with the WSAAsyncSelect() call.
 *)

  FD_READ        = $01;
  {$EXTERNALSYM FD_READ}
  FD_WRITE       = $02;
  {$EXTERNALSYM FD_WRITE}
  FD_OOB         = $04;
  {$EXTERNALSYM FD_OOB}
  FD_ACCEPT      = $08;
  {$EXTERNALSYM FD_ACCEPT}
  FD_CONNECT     = $10;
  {$EXTERNALSYM FD_CONNECT}
  FD_CLOSE       = $20;
  {$EXTERNALSYM FD_CLOSE}

(*
 * All Windows Sockets error constants are biased by WSABASEERR from
 * the "normal"
 *)

  WSABASEERR = 10000;
  {$EXTERNALSYM WSABASEERR}

(*
 * Windows Sockets definitions of regular Microsoft C error constants
 *)

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

(*
 * Windows Sockets definitions of regular Berkeley error constants
 *)

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

  WSAEDISCON         = (WSABASEERR+101);
  {$EXTERNALSYM WSAEDISCON}

(*
 * Extended Windows Sockets error constant definitions
 *)

  WSASYSNOTREADY         = (WSABASEERR+91);
  {$EXTERNALSYM WSASYSNOTREADY}
  WSAVERNOTSUPPORTED     = (WSABASEERR+92);
  {$EXTERNALSYM WSAVERNOTSUPPORTED}
  WSANOTINITIALISED      = (WSABASEERR+93);
  {$EXTERNALSYM WSANOTINITIALISED}

(*
 * Error return codes from gethostbyname() and gethostbyaddr()
 * (when using the resolver). Note that these errors are
 * retrieved via WSAGetLastError() and must therefore follow
 * the rules for avoiding clashes with error numbers from
 * specific implementations or language run-time systems.
 * For this reason the codes are based at WSABASEERR+1001.
 * Note also that [WSA]NO_ADDRESS is defined only for
 * compatibility purposes.
 *)

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

(*
 * Compatibility macros.
 *)

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

(*
 * Windows Sockets errors redefined as regular Berkeley error constants.
 * These are commented out in Windows NT to avoid conflicts with errno.h.
 * Use the WSA constants instead.
 *)

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

(* Socket function prototypes *)

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

(* Database function prototypes *)

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

(* Microsoft Windows Extension function prototypes *)

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

function WSARecvEx(s: TSocket; var buf; len: Integer; var flags: Integer): Integer; stdcall;
{$EXTERNALSYM WSARecvEx}

type
  _TRANSMIT_FILE_BUFFERS = record
    Head: LPVOID;
    HeadLength: DWORD;
    Tail: LPVOID;
    TailLength: DWORD;
  end;
  {$EXTERNALSYM _TRANSMIT_FILE_BUFFERS}
  TRANSMIT_FILE_BUFFERS = _TRANSMIT_FILE_BUFFERS;
  {$EXTERNALSYM TRANSMIT_FILE_BUFFERS}
  PTRANSMIT_FILE_BUFFERS = ^TRANSMIT_FILE_BUFFERS;
  {$EXTERNALSYM PTRANSMIT_FILE_BUFFERS}
  LPTRANSMIT_FILE_BUFFERS = ^TRANSMIT_FILE_BUFFERS;
  {$EXTERNALSYM LPTRANSMIT_FILE_BUFFERS}
  TTransmitFileBuffers = TRANSMIT_FILE_BUFFERS;
  PTransmitFileBuffers = LPTRANSMIT_FILE_BUFFERS;

const
  TF_DISCONNECT           = $01;
  {$EXTERNALSYM TF_DISCONNECT}
  TF_REUSE_SOCKET         = $02;
  {$EXTERNALSYM TF_REUSE_SOCKET}
  TF_WRITE_BEHIND         = $04;
  {$EXTERNALSYM TF_WRITE_BEHIND}

function TransmitFile(hSocket: TSocket; hFile: HANDLE; nNumberOfBytesToWrite: DWORD;
  nNumberOfBytesPerSend: DWORD; lpOverlapped: LPOVERLAPPED;
  lpTransmitBuffers: LPTRANSMIT_FILE_BUFFERS; dwReserved: DWORD): BOOL; stdcall;
{$EXTERNALSYM TransmitFile}
function AcceptEx(sListenSocket, sAcceptSocket: TSocket;
  lpOutputBuffer: LPVOID; dwReceiveDataLength, dwLocalAddressLength,
  dwRemoteAddressLength: DWORD; var lpdwBytesReceived: DWORD;
  lpOverlapped: LPOVERLAPPED): BOOL; stdcall;
{$EXTERNALSYM AcceptEx}
procedure GetAcceptExSockaddrs(lpOutputBuffer: Pointer;
  dwReceiveDataLength, dwLocalAddressLength, dwRemoteAddressLength: DWORD;
  out LocalSockaddr: PSockAddr; var LocalSockaddrLength: Integer;
  out RemoteSockaddr: PSockAddr; var RemoteSockaddrLength: Integer); stdcall;
{$EXTERNALSYM GetAcceptExSockaddrs}

(* Microsoft Windows Extended data types *)

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

(*
 * Windows message parameter composition and decomposition
 * macros.
 *
 * WSAMAKEASYNCREPLY is intended for use by the Windows Sockets implementation
 * when constructing the response to a WSAAsyncGetXByY() routine.
 *)

function WSAMAKEASYNCREPLY(buflen, error: WORD): DWORD;
{$EXTERNALSYM WSAMAKEASYNCREPLY}

(*
 * WSAMAKESELECTREPLY is intended for use by the Windows Sockets implementation
 * when constructing the response to WSAAsyncSelect().
 *)

function WSAMAKESELECTREPLY(event, error: WORD): DWORD;
{$EXTERNALSYM WSAMAKESELECTREPLY}

(*
 * WSAGETASYNCBUFLEN is intended for use by the Windows Sockets application
 * to extract the buffer length from the lParam in the response
 * to a WSAGetXByY().
 *)

function WSAGETASYNCBUFLEN(lParam: DWORD): WORD;
{$EXTERNALSYM WSAGETASYNCBUFLEN}

(*
 * WSAGETASYNCERROR is intended for use by the Windows Sockets application
 * to extract the error code from the lParam in the response
 * to a WSAGetXByY().
 *)

function WSAGETASYNCERROR(lParam: DWORD): WORD;
{$EXTERNALSYM WSAGETASYNCERROR}

(*
 * WSAGETSELECTEVENT is intended for use by the Windows Sockets application
 * to extract the event code from the lParam in the response
 * to a WSAAsyncSelect().
 *)

function WSAGETSELECTEVENT(lParam: DWORD): WORD;
{$EXTERNALSYM WSAGETSELECTEVENT}

(*
 * WSAGETSELECTERROR is intended for use by the Windows Sockets application
 * to extract the error code from the lParam in the response
 * to a WSAAsyncSelect().
 *)

function WSAGETSELECTERROR(lParam: DWORD): WORD;
{$EXTERNALSYM WSAGETSELECTERROR}

implementation

const
  wsock32 = 'wsock32.dll';


{$IFDEF DYNAMIC_LINK}
var
  ___WSAFDIsSet: Pointer;

function __WSAFDIsSet;
begin
  GetProcedureAddress(___WSAFDIsSet, wsock32, '__WSAFDIsSet');
  asm
    mov esp, ebp
    pop ebp
    jmp [___WSAFDIsSet]
  end;
end;
{$ELSE}
function __WSAFDIsSet; external wsock32 name '__WSAFDIsSet';
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

function h_errno: Integer;
begin
  Result := WSAGetLastError;
end;


{$IFDEF DYNAMIC_LINK}
var
  _accept: Pointer;

function accept;
begin
  GetProcedureAddress(_accept, wsock32, 'accept');
  asm
    mov esp, ebp
    pop ebp
    jmp [_accept]
  end;
end;
{$ELSE}
function accept; external wsock32 name 'accept';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _bind: Pointer;

function bind;
begin
  GetProcedureAddress(_bind, wsock32, 'bind');
  asm
    mov esp, ebp
    pop ebp
    jmp [_bind]
  end;
end;
{$ELSE}
function bind; external wsock32 name 'bind';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _closesocket: Pointer;

function closesocket;
begin
  GetProcedureAddress(_closesocket, wsock32, 'closesocket');
  asm
    mov esp, ebp
    pop ebp
    jmp [_closesocket]
  end;
end;
{$ELSE}
function closesocket; external wsock32 name 'closesocket';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _connect: Pointer;

function connect;
begin
  GetProcedureAddress(_connect, wsock32, 'connect');
  asm
    mov esp, ebp
    pop ebp
    jmp [_connect]
  end;
end;
{$ELSE}
function connect; external wsock32 name 'connect';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ioctlsocket: Pointer;

function ioctlsocket;
begin
  GetProcedureAddress(_ioctlsocket, wsock32, 'ioctlsocket');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ioctlsocket]
  end;
end;
{$ELSE}
function ioctlsocket; external wsock32 name 'ioctlsocket';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _getpeername: Pointer;

function getpeername;
begin
  GetProcedureAddress(_getpeername, wsock32, 'getpeername');
  asm
    mov esp, ebp
    pop ebp
    jmp [_getpeername]
  end;
end;
{$ELSE}
function getpeername; external wsock32 name 'getpeername';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _getsockname: Pointer;

function getsockname;
begin
  GetProcedureAddress(_getsockname, wsock32, 'getsockname');
  asm
    mov esp, ebp
    pop ebp
    jmp [_getsockname]
  end;
end;
{$ELSE}
function getsockname; external wsock32 name 'getsockname';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _getsockopt: Pointer;

function getsockopt;
begin
  GetProcedureAddress(_getsockopt, wsock32, 'getsockopt');
  asm
    mov esp, ebp
    pop ebp
    jmp [_getsockopt]
  end;
end;
{$ELSE}
function getsockopt; external wsock32 name 'getsockopt';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _htonl: Pointer;

function htonl;
begin
  GetProcedureAddress(_htonl, wsock32, 'htonl');
  asm
    mov esp, ebp
    pop ebp
    jmp [_htonl]
  end;
end;
{$ELSE}
function htonl; external wsock32 name 'htonl';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _htons: Pointer;

function htons;
begin
  GetProcedureAddress(_htons, wsock32, 'htons');
  asm
    mov esp, ebp
    pop ebp
    jmp [_htons]
  end;
end;
{$ELSE}
function htons; external wsock32 name 'htons';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _inet_addr: Pointer;

function inet_addr;
begin
  GetProcedureAddress(_inet_addr, wsock32, 'inet_addr');
  asm
    mov esp, ebp
    pop ebp
    jmp [_inet_addr]
  end;
end;
{$ELSE}
function inet_addr; external wsock32 name 'inet_addr';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _inet_ntoa: Pointer;

function inet_ntoa;
begin
  GetProcedureAddress(_inet_ntoa, wsock32, 'inet_ntoa');
  asm
    mov esp, ebp
    pop ebp
    jmp [_inet_ntoa]
  end;
end;
{$ELSE}
function inet_ntoa; external wsock32 name 'inet_ntoa';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _listen: Pointer;

function listen;
begin
  GetProcedureAddress(_listen, wsock32, 'listen');
  asm
    mov esp, ebp
    pop ebp
    jmp [_listen]
  end;
end;
{$ELSE}
function listen; external wsock32 name 'listen';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ntohl: Pointer;

function ntohl;
begin
  GetProcedureAddress(_ntohl, wsock32, 'ntohl');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ntohl]
  end;
end;
{$ELSE}
function ntohl; external wsock32 name 'ntohl';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ntohs: Pointer;

function ntohs;
begin
  GetProcedureAddress(_ntohs, wsock32, 'ntohs');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ntohs]
  end;
end;
{$ELSE}
function ntohs; external wsock32 name 'ntohs';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _recv: Pointer;

function recv;
begin
  GetProcedureAddress(_recv, wsock32, 'recv');
  asm
    mov esp, ebp
    pop ebp
    jmp [_recv]
  end;
end;
{$ELSE}
function recv; external wsock32 name 'recv';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _recvfrom: Pointer;

function recvfrom;
begin
  GetProcedureAddress(_recvfrom, wsock32, 'recvfrom');
  asm
    mov esp, ebp
    pop ebp
    jmp [_recvfrom]
  end;
end;
{$ELSE}
function recvfrom; external wsock32 name 'recvfrom';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _select: Pointer;

function select;
begin
  GetProcedureAddress(_select, wsock32, 'select');
  asm
    mov esp, ebp
    pop ebp
    jmp [_select]
  end;
end;
{$ELSE}
function select; external wsock32 name 'select';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _send: Pointer;

function send;
begin
  GetProcedureAddress(_send, wsock32, 'send');
  asm
    mov esp, ebp
    pop ebp
    jmp [_send]
  end;
end;
{$ELSE}
function send; external wsock32 name 'send';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _sendto: Pointer;

function sendto;
begin
  GetProcedureAddress(_sendto, wsock32, 'sendto');
  asm
    mov esp, ebp
    pop ebp
    jmp [_sendto]
  end;
end;
{$ELSE}
function sendto; external wsock32 name 'sendto';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _setsockopt: Pointer;

function setsockopt;
begin
  GetProcedureAddress(_setsockopt, wsock32, 'setsockopt');
  asm
    mov esp, ebp
    pop ebp
    jmp [_setsockopt]
  end;
end;
{$ELSE}
function setsockopt; external wsock32 name 'setsockopt';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _shutdown: Pointer;

function shutdown;
begin
  GetProcedureAddress(_shutdown, wsock32, 'shutdown');
  asm
    mov esp, ebp
    pop ebp
    jmp [_shutdown]
  end;
end;
{$ELSE}
function shutdown; external wsock32 name 'shutdown';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _socket: Pointer;

function socket;
begin
  GetProcedureAddress(_socket, wsock32, 'socket');
  asm
    mov esp, ebp
    pop ebp
    jmp [_socket]
  end;
end;
{$ELSE}
function socket; external wsock32 name 'socket';
{$ENDIF DYNAMIC_LINK}


{$IFDEF DYNAMIC_LINK}
var
  _gethostbyaddr: Pointer;

function gethostbyaddr;
begin
  GetProcedureAddress(_gethostbyaddr, wsock32, 'gethostbyaddr');
  asm
    mov esp, ebp
    pop ebp
    jmp [_gethostbyaddr]
  end;
end;
{$ELSE}
function gethostbyaddr; external wsock32 name 'gethostbyaddr';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _gethostbyname: Pointer;

function gethostbyname;
begin
  GetProcedureAddress(_gethostbyname, wsock32, 'gethostbyname');
  asm
    mov esp, ebp
    pop ebp
    jmp [_gethostbyname]
  end;
end;
{$ELSE}
function gethostbyname; external wsock32 name 'gethostbyname';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _gethostname: Pointer;

function gethostname;
begin
  GetProcedureAddress(_gethostname, wsock32, 'gethostname');
  asm
    mov esp, ebp
    pop ebp
    jmp [_gethostname]
  end;
end;
{$ELSE}
function gethostname; external wsock32 name 'gethostname';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _getservbyport: Pointer;

function getservbyport;
begin
  GetProcedureAddress(_getservbyport, wsock32, 'getservbyport');
  asm
    mov esp, ebp
    pop ebp
    jmp [_getservbyport]
  end;
end;
{$ELSE}
function getservbyport; external wsock32 name 'getservbyport';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _getservbyname: Pointer;

function getservbyname;
begin
  GetProcedureAddress(_getservbyname, wsock32, 'getservbyname');
  asm
    mov esp, ebp
    pop ebp
    jmp [_getservbyname]
  end;
end;
{$ELSE}
function getservbyname; external wsock32 name 'getservbyname';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _getprotobynumber: Pointer;

function getprotobynumber;
begin
  GetProcedureAddress(_getprotobynumber, wsock32, 'getprotobynumber');
  asm
    mov esp, ebp
    pop ebp
    jmp [_getprotobynumber]
  end;
end;
{$ELSE}
function getprotobynumber; external wsock32 name 'getprotobynumber';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _getprotobyname: Pointer;

function getprotobyname;
begin
  GetProcedureAddress(_getprotobyname, wsock32, 'getprotobyname');
  asm
    mov esp, ebp
    pop ebp
    jmp [_getprotobyname]
  end;
end;
{$ELSE}
function getprotobyname; external wsock32 name 'getprotobyname';
{$ENDIF DYNAMIC_LINK}


{$IFDEF DYNAMIC_LINK}
var
  _WSAStartup: Pointer;

function WSAStartup;
begin
  GetProcedureAddress(_WSAStartup, wsock32, 'WSAStartup');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAStartup]
  end;
end;
{$ELSE}
function WSAStartup; external wsock32 name 'WSAStartup';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSACleanup: Pointer;

function WSACleanup;
begin
  GetProcedureAddress(_WSACleanup, wsock32, 'WSACleanup');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSACleanup]
  end;
end;
{$ELSE}
function WSACleanup; external wsock32 name 'WSACleanup';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSASetLastError: Pointer;

procedure WSASetLastError;
begin
  GetProcedureAddress(_WSASetLastError, wsock32, 'WSASetLastError');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSASetLastError]
  end;
end;
{$ELSE}
procedure WSASetLastError; external wsock32 name 'WSASetLastError';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSAGetLastError: Pointer;

function WSAGetLastError;
begin
  GetProcedureAddress(_WSAGetLastError, wsock32, 'WSAGetLastError');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAGetLastError]
  end;
end;
{$ELSE}
function WSAGetLastError; external wsock32 name 'WSAGetLastError';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSAIsBlocking: Pointer;

function WSAIsBlocking;
begin
  GetProcedureAddress(_WSAIsBlocking, wsock32, 'WSAIsBlocking');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAIsBlocking]
  end;
end;
{$ELSE}
function WSAIsBlocking; external wsock32 name 'WSAIsBlocking';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSAUnhookBlockingHook: Pointer;

function WSAUnhookBlockingHook;
begin
  GetProcedureAddress(_WSAUnhookBlockingHook, wsock32, 'WSAUnhookBlockingHook');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAUnhookBlockingHook]
  end;
end;
{$ELSE}
function WSAUnhookBlockingHook; external wsock32 name 'WSAUnhookBlockingHook';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSASetBlockingHook: Pointer;

function WSASetBlockingHook;
begin
  GetProcedureAddress(_WSASetBlockingHook, wsock32, 'WSASetBlockingHook');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSASetBlockingHook]
  end;
end;
{$ELSE}
function WSASetBlockingHook; external wsock32 name 'WSASetBlockingHook';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSACancelBlockingCall: Pointer;

function WSACancelBlockingCall;
begin
  GetProcedureAddress(_WSACancelBlockingCall, wsock32, 'WSACancelBlockingCall');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSACancelBlockingCall]
  end;
end;
{$ELSE}
function WSACancelBlockingCall; external wsock32 name 'WSACancelBlockingCall';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSAAsyncGetServByName: Pointer;

function WSAAsyncGetServByName;
begin
  GetProcedureAddress(_WSAAsyncGetServByName, wsock32, 'WSAAsyncGetServByName');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAAsyncGetServByName]
  end;
end;
{$ELSE}
function WSAAsyncGetServByName; external wsock32 name 'WSAAsyncGetServByName';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSAAsyncGetServByPort: Pointer;

function WSAAsyncGetServByPort;
begin
  GetProcedureAddress(_WSAAsyncGetServByPort, wsock32, 'WSAAsyncGetServByPort');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAAsyncGetServByPort]
  end;
end;
{$ELSE}
function WSAAsyncGetServByPort; external wsock32 name 'WSAAsyncGetServByPort';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSAAsyncGetProtoByName: Pointer;

function WSAAsyncGetProtoByName;
begin
  GetProcedureAddress(_WSAAsyncGetProtoByName, wsock32, 'WSAAsyncGetProtoByName');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAAsyncGetProtoByName]
  end;
end;
{$ELSE}
function WSAAsyncGetProtoByName; external wsock32 name 'WSAAsyncGetProtoByName';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSAAsyncGetProtoByNumber: Pointer;

function WSAAsyncGetProtoByNumber;
begin
  GetProcedureAddress(_WSAAsyncGetProtoByNumber, wsock32, 'WSAAsyncGetProtoByNumber');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAAsyncGetProtoByNumber]
  end;
end;
{$ELSE}
function WSAAsyncGetProtoByNumber; external wsock32 name 'WSAAsyncGetProtoByNumber';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSAAsyncGetHostByName: Pointer;

function WSAAsyncGetHostByName;
begin
  GetProcedureAddress(_WSAAsyncGetHostByName, wsock32, 'WSAAsyncGetHostByName');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAAsyncGetHostByName]
  end;
end;
{$ELSE}
function WSAAsyncGetHostByName; external wsock32 name 'WSAAsyncGetHostByName';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSAAsyncGetHostByAddr: Pointer;

function WSAAsyncGetHostByAddr;
begin
  GetProcedureAddress(_WSAAsyncGetHostByAddr, wsock32, 'WSAAsyncGetHostByAddr');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAAsyncGetHostByAddr]
  end;
end;
{$ELSE}
function WSAAsyncGetHostByAddr; external wsock32 name 'WSAAsyncGetHostByAddr';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSACancelAsyncRequest: Pointer;

function WSACancelAsyncRequest;
begin
  GetProcedureAddress(_WSACancelAsyncRequest, wsock32, 'WSACancelAsyncRequest');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSACancelAsyncRequest]
  end;
end;
{$ELSE}
function WSACancelAsyncRequest; external wsock32 name 'WSACancelAsyncRequest';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WSAAsyncSelect: Pointer;

function WSAAsyncSelect;
begin
  GetProcedureAddress(_WSAAsyncSelect, wsock32, 'WSAAsyncSelect');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSAAsyncSelect]
  end;
end;
{$ELSE}
function WSAAsyncSelect; external wsock32 name 'WSAAsyncSelect';
{$ENDIF DYNAMIC_LINK}


{$IFDEF DYNAMIC_LINK}
var
  _WSARecvEx: Pointer;

function WSARecvEx;
begin
  GetProcedureAddress(_WSARecvEx, wsock32, 'WSARecvEx');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WSARecvEx]
  end;
end;
{$ELSE}
function WSARecvEx; external wsock32 name 'WSARecvEx';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _TransmitFile: Pointer;

function TransmitFile;
begin
  GetProcedureAddress(_TransmitFile, wsock32, 'TransmitFile');
  asm
    mov esp, ebp
    pop ebp
    jmp [_TransmitFile]
  end;
end;
{$ELSE}
function TransmitFile; external wsock32 name 'TransmitFile';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _AcceptEx: Pointer;

function AcceptEx;
begin
  GetProcedureAddress(_AcceptEx, wsock32, 'AcceptEx');
  asm
    mov esp, ebp
    pop ebp
    jmp [_AcceptEx]
  end;
end;
{$ELSE}
function AcceptEx; external wsock32 name 'AcceptEx';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetAcceptExSockaddrs: Pointer;

procedure GetAcceptExSockaddrs;
begin
  GetProcedureAddress(_GetAcceptExSockaddrs, wsock32, 'GetAcceptExSockaddrs');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetAcceptExSockaddrs]
  end;
end;
{$ELSE}
procedure GetAcceptExSockaddrs; external wsock32 name 'GetAcceptExSockaddrs';
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
