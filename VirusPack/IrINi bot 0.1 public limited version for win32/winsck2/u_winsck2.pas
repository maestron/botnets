//-------------------------------------------------------------
//
//       Borland Delphi Runtime Library
//       <API> interface unit
//
// Portions created by Microsoft are
// Copyright (C) 1995-1999 Microsoft Corporation.
// All Rights Reserved.
//
// The original file is: Winsock2.h from CBuilder5 distribution.
// The original Pascal code is: winsock2.pas, released 04 Mar 2000.
// The initial developer of the Pascal code is Alex Konshin
// (alexk@mtgroup.ru).
//
// Portions created by Alex Konshin are
// Copyright (C) 1998-2000 Alex Konshin
//
// Contributor(s): Alex Konshin
//
//       Obtained through:
//
//       Joint Endeavour of Delphi Innovators (Project JEDI)
//
// You may retrieve the latest version of this file at the Project
// JEDI home page, located at http://delphi-jedi.org
//
// The contents of this file are used with permission, subject to
// the Mozilla Public License Version 1.1 (the "License"); you may
// not use this file except in compliance with the License. You may
// obtain a copy of the License at
// http://www.mozilla.org/MPL/MPL-1.1.html
//
// Software distributed under the License is distributed on an
// "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
// implied. See the License for the specific language governing
// rights and limitations under the License.
//
//-------------------------------------------------------------


{	Winsock2.h -- definitions to be used with the WinSock 2 DLL and WinSock 2 applications.
 	This header file corresponds to version 2.2.x of the WinSock API specification.
 	This file includes parts which are Copyright (c) 1982-1986 Regents
	of the University of California. All rights reserved.
	The Berkeley Software License Agreement specifies the terms and
	conditions for redistribution. }

// converted by Alex Konshin, mailto:alexk@mtgroup.ru
// modified March,4 2000

unit u_winsck2;

interface

uses Windows;

{$ALIGN OFF}
{$RANGECHECKS OFF}
{$WRITEABLECONST OFF}

//	Define the current Winsock version. To build an earlier Winsock version
//	application redefine this value prior to including Winsock2.h
const
	WINSOCK_VERSION = $0202;
	WINSOCK2_DLL = 'ws2_32.dll';

type
  u_char  = Byte;
  u_short = Word;
  u_int   = DWORD;
  u_long  = DWORD;

// The new type to be used in all instances which refer to sockets.
  TSocket = u_int;

	WSAEVENT = THandle;
	PWSAEVENT = ^WSAEVENT;
	LPWSAEVENT = PWSAEVENT;
{$IFDEF UNICODE}
	PMBChar = PWideChar;
{$ELSE}
	PMBChar = PChar;
{$ENDIF}

const
  FD_SETSIZE     =   64;

type
  PFDSet = ^TFDSet;
  TFDSet = packed record
    fd_count: u_int;
    fd_array: array[0..FD_SETSIZE-1] of TSocket;
  end;

  PTimeVal = ^TTimeVal;
  TTimeVal = packed record
    tv_sec: Longint;
    tv_usec: Longint;
  end;

const
  IOCPARM_MASK = $7f;
  IOC_VOID     = $20000000;
  IOC_OUT      = $40000000;
  IOC_IN       = $80000000;
  IOC_INOUT    = (IOC_IN or IOC_OUT);

// get # bytes to read
  FIONREAD     = IOC_OUT or (SizeOf(Longint) shl 16) or (Ord('f') shl 8) or 127;
// set/clear non-blocking i/o
  FIONBIO      = IOC_IN  or (SizeOf(Longint) shl 16) or (Ord('f') shl 8) or 126;
// set/clear async i/o
	FIOASYNC     = IOC_IN  or (SizeOf(Longint) shl 16) or (Ord('f') shl 8) or 125;

//	Socket I/O Controls

// set high watermark
	SIOCSHIWAT   = IOC_IN  or (SizeOf(Longint) shl 16) or (Ord('s') shl 8);
// get high watermark
	SIOCGHIWAT   = IOC_OUT or (SizeOf(Longint) shl 16) or (Ord('s') shl 8) or 1;
// set low watermark
	SIOCSLOWAT   = IOC_IN  or (SizeOf(Longint) shl 16) or (Ord('s') shl 8) or 2;
// get low watermark
	SIOCGLOWAT   = IOC_OUT or (SizeOf(Longint) shl 16) or (Ord('s') shl 8) or 3;
// at oob mark?
	SIOCATMARK   = IOC_OUT or (SizeOf(Longint) shl 16) or (Ord('s') shl 8) or 7;


//	Structures returned by network data base library, taken from the
//	BSD file netdb.h.  All addresses are supplied in host order, and
//	returned in network order (suitable for use in system calls).
type
  PHostEnt = ^THostEnt;
  THostEnt = packed record
    h_name: PChar;                 // official name of host
    h_aliases: ^PChar;             // alias list
    h_addrtype: Smallint;          // host address type
    h_length: Smallint;            // length of address
    case Byte of
    	0: (h_addr_list: ^PChar);    // list of addresses
    	1: (h_addr: ^PChar);         // address, for backward compat
  end;

//	It is assumed here that a network number
//	fits in 32 bits.
  PNetEnt = ^TNetEnt;
  TNetEnt = packed record
    n_name: PChar;                 // official name of net
    n_aliases: ^PChar;             // alias list
    n_addrtype: Smallint;          // net address type
    n_net: u_long;                 // network #
  end;

  PServEnt = ^TServEnt;
  TServEnt = packed record
    s_name: PChar;                 // official service name
    s_aliases: ^PChar;             // alias list
    s_port: Smallint;              // protocol to use
    s_proto: PChar;                // port #
  end;

  PProtoEnt = ^TProtoEnt;
  TProtoEnt = packed record
    p_name: PChar;                 // official protocol name
    p_aliases: ^Pchar;             // alias list
    p_proto: Smallint;             // protocol #
  end;

// Constants and structures defined by the internet system,
// Per RFC 790, September 1981, taken from the BSD file netinet/in.h.
const

// Protocols
  IPPROTO_IP     =   0;             // dummy for IP
  IPPROTO_ICMP   =   1;             // control message protocol
  IPPROTO_IGMP   =   2;             // group management protocol
  IPPROTO_GGP    =   3;             // gateway^2 (deprecated)
  IPPROTO_TCP    =   6;             // TCP
  IPPROTO_PUP    =  12;             // pup
  IPPROTO_UDP    =  17;             // UDP - user datagram protocol
  IPPROTO_IDP    =  22;             // xns idp
  IPPROTO_ND     =  77;             // UNOFFICIAL net disk proto

  IPPROTO_RAW    = 255;             // raw IP packet
  IPPROTO_MAX    = 256;

// Port/socket numbers: network standard functions
  IPPORT_ECHO        =   7;
  IPPORT_DISCARD     =   9;
  IPPORT_SYSTAT      =  11;
  IPPORT_DAYTIME     =  13;
  IPPORT_NETSTAT     =  15;
  IPPORT_FTP         =  21;
  IPPORT_TELNET      =  23;
  IPPORT_SMTP        =  25;
  IPPORT_TIMESERVER  =  37;
  IPPORT_NAMESERVER  =  42;
  IPPORT_WHOIS       =  43;
  IPPORT_MTP         =  57;

// Port/socket numbers: host specific functions
  IPPORT_TFTP        =  69;
  IPPORT_RJE         =  77;
  IPPORT_FINGER      =  79;
  IPPORT_TTYLINK     =  87;
  IPPORT_SUPDUP      =  95;

// UNIX TCP sockets
  IPPORT_EXECSERVER  = 512;
  IPPORT_LOGINSERVER = 513;
  IPPORT_CMDSERVER   = 514;
  IPPORT_EFSSERVER   = 520;

// UNIX UDP sockets
  IPPORT_BIFFUDP     = 512;
  IPPORT_WHOSERVER   = 513;
  IPPORT_ROUTESERVER = 520;

// Ports < IPPORT_RESERVED are reserved for  privileged processes (e.g. root).
  IPPORT_RESERVED    =1024;

// Link numbers
  IMPLINK_IP         = 155;
  IMPLINK_LOWEXPER   = 156;
  IMPLINK_HIGHEXPER  = 158;

  TF_DISCONNECT      = $01;
  TF_REUSE_SOCKET    = $02;
  TF_WRITE_BEHIND    = $04;

// This is used instead of -1, since the TSocket type is unsigned.
  INVALID_SOCKET		 = TSocket(not(0));
  SOCKET_ERROR			 = -1;

//	The  following  may  be used in place of the address family, socket type, or
//	protocol  in  a  call  to WSASocket to indicate that the corresponding value
//	should  be taken from the supplied WSAPROTOCOL_INFO structure instead of the
//	parameter itself.
	FROM_PROTOCOL_INFO = -1;


// Types
  SOCK_STREAM     = 1;               { stream socket }
  SOCK_DGRAM      = 2;               { datagram socket }
  SOCK_RAW        = 3;               { raw-protocol interface }
  SOCK_RDM        = 4;               { reliably-delivered message }
  SOCK_SEQPACKET  = 5;               { sequenced packet stream }

// Option flags per-socket.
  SO_DEBUG            = $0001;            // turn on debugging info recording
  SO_ACCEPTCONN       = $0002;            // socket has had listen()
  SO_REUSEADDR        = $0004;            // allow local address reuse
  SO_KEEPALIVE        = $0008;            // keep connections alive
  SO_DONTROUTE        = $0010;            // just use interface addresses
  SO_BROADCAST        = $0020;            // permit sending of broadcast msgs
  SO_USELOOPBACK      = $0040;            // bypass hardware when possible
  SO_LINGER           = $0080;            // linger on close if data present
  SO_OOBINLINE        = $0100;            // leave received OOB data in line

  SO_DONTLINGER       = not SO_LINGER;
	SO_EXCLUSIVEADDRUSE = not SO_REUSEADDR; // disallow local address reuse

// Additional options.

  SO_SNDBUF           = $1001;      // send buffer size
  SO_RCVBUF           = $1002;      // receive buffer size
  SO_SNDLOWAT         = $1003;      // send low-water mark
  SO_RCVLOWAT         = $1004;      // receive low-water mark
  SO_SNDTIMEO         = $1005;      // send timeout
  SO_RCVTIMEO         = $1006;      // receive timeout
  SO_ERROR            = $1007;      // get error status and clear
  SO_TYPE             = $1008;      // get socket type

// Options for connect and disconnect data and options.
// Used only by non-TCP/IP transports such as DECNet, OSI TP4, etc.
  SO_CONNDATA         = $7000;
  SO_CONNOPT          = $7001;
  SO_DISCDATA         = $7002;
  SO_DISCOPT          = $7003;
  SO_CONNDATALEN      = $7004;
  SO_CONNOPTLEN       = $7005;
  SO_DISCDATALEN      = $7006;
  SO_DISCOPTLEN       = $7007;

// Option for opening sockets for synchronous access.
  SO_OPENTYPE         = $7008;
  SO_SYNCHRONOUS_ALERT    = $10;
  SO_SYNCHRONOUS_NONALERT = $20;

// Other NT-specific options.
  SO_MAXDG                 = $7009;
  SO_MAXPATHDG             = $700A;
  SO_UPDATE_ACCEPT_CONTEXT = $700B;
  SO_CONNECT_TIME          = $700C;

// TCP options.
  TCP_NODELAY              = $0001;
  TCP_BSDURGENT            = $7000;

// WinSock 2 extension -- new options
	SO_GROUP_ID              = $2001; // ID of a socket group
	SO_GROUP_PRIORITY        = $2002; // the relative priority within a group
	SO_MAX_MSG_SIZE          = $2003; // maximum message size
	SO_Protocol_InfoA        = $2004; // WSAPROTOCOL_INFOA structure
	SO_Protocol_InfoW        = $2005; // WSAPROTOCOL_INFOW structure
{$IFDEF UNICODE}
	SO_Protocol_Info         = SO_Protocol_InfoW;
{$ELSE}
	SO_Protocol_Info         = SO_Protocol_InfoA;
{$ENDIF}
	PVD_CONFIG               = $3001; // configuration info for service provider
	SO_CONDITIONAL_ACCEPT    = $3002; // enable true conditional accept:
                                    // connection is not ack-ed to the
                                    // other side until conditional
                                    // function returns CF_ACCEPT

// Address families.
  AF_UNSPEC       = 0;               // unspecified
  AF_UNIX         = 1;               // local to host (pipes, portals)
  AF_INET         = 2;               // internetwork: UDP, TCP, etc.
  AF_IMPLINK      = 3;               // arpanet imp addresses
  AF_PUP          = 4;               // pup protocols: e.g. BSP
  AF_CHAOS        = 5;               // mit CHAOS protocols
  AF_IPX          = 6;               // IPX and SPX
  AF_NS           = AF_IPX;          // XEROX NS protocols
  AF_ISO          = 7;               // ISO protocols
  AF_OSI          = AF_ISO;          // OSI is ISO
  AF_ECMA         = 8;               // european computer manufacturers
  AF_DATAKIT      = 9;               // datakit protocols
  AF_CCITT        = 10;              // CCITT protocols, X.25 etc
  AF_SNA          = 11;              // IBM SNA
  AF_DECnet       = 12;              // DECnet
  AF_DLI          = 13;              // Direct data link interface
  AF_LAT          = 14;              // LAT
  AF_HYLINK       = 15;              // NSC Hyperchannel
  AF_APPLETALK    = 16;              // AppleTalk
  AF_NETBIOS      = 17;              // NetBios-style addresses
  AF_VOICEVIEW    = 18;              // VoiceView
  AF_FIREFOX      = 19;              // FireFox
  AF_UNKNOWN1     = 20;              // Somebody is using this!
  AF_BAN          = 21;              // Banyan
	AF_ATM          = 22;              // Native ATM Services
	AF_INET6        = 23;              // Internetwork Version 6
	AF_CLUSTER      = 24;              // Microsoft Wolfpack
	AF_12844        = 25;              // IEEE 1284.4 WG AF
	AF_IRDA         = 26;              // IrDA
	AF_NETDES       = 28;              // Network Designers OSI & gateway enabled protocols

	AF_MAX          = 29;


// Protocol families, same as address families for now.

  PF_UNSPEC       = AF_UNSPEC;
  PF_UNIX         = AF_UNIX;
  PF_INET         = AF_INET;
  PF_IMPLINK      = AF_IMPLINK;
  PF_PUP          = AF_PUP;
  PF_CHAOS        = AF_CHAOS;
  PF_NS           = AF_NS;
  PF_IPX          = AF_IPX;
  PF_ISO          = AF_ISO;
  PF_OSI          = AF_OSI;
  PF_ECMA         = AF_ECMA;
  PF_DATAKIT      = AF_DATAKIT;
  PF_CCITT        = AF_CCITT;
  PF_SNA          = AF_SNA;
  PF_DECnet       = AF_DECnet;
  PF_DLI          = AF_DLI;
  PF_LAT          = AF_LAT;
  PF_HYLINK       = AF_HYLINK;
  PF_APPLETALK    = AF_APPLETALK;
  PF_VOICEVIEW    = AF_VOICEVIEW;
  PF_FIREFOX      = AF_FIREFOX;
  PF_UNKNOWN1     = AF_UNKNOWN1;
  PF_BAN          = AF_BAN;
	PF_ATM          = AF_ATM;
	PF_INET6        = AF_INET6;

  PF_MAX          = AF_MAX;

type

  SunB = packed record
    s_b1, s_b2, s_b3, s_b4: u_char;
  end;

  SunW = packed record
    s_w1, s_w2: u_short;
  end;

  TInAddr = packed record
    case integer of
      0: (S_un_b: SunB);
      1: (S_un_w: SunW);
      2: (S_addr: u_long);
  end;
	PInAddr = ^TInAddr;

  // Structure used by kernel to store most addresses.

  TSockAddrIn = packed record
    case Integer of
      0: (sin_family : u_short;
          sin_port   : u_short;
          sin_addr   : TInAddr;
          sin_zero   : array[0..7] of Char);
      1: (sa_family  : u_short;
          sa_data    : array[0..13] of Char)
  end;
  PSockAddrIn = ^TSockAddrIn;
  TSockAddr   = TSockAddrIn;
  PSockAddr   = ^TSockAddr;
	SOCKADDR    = TSockAddr;
	SOCKADDR_IN = TSockAddrIn;

  // Structure used by kernel to pass protocol information in raw sockets.
  PSockProto = ^TSockProto;
  TSockProto = packed record
    sp_family   : u_short;
    sp_protocol : u_short;
  end;

// Structure used for manipulating linger option.
  PLinger = ^TLinger;
  TLinger = packed record
    l_onoff: u_short;
    l_linger: u_short;
  end;

const
  INADDR_ANY       = $00000000;
  INADDR_LOOPBACK  = $7F000001;
  INADDR_BROADCAST = $FFFFFFFF;
  INADDR_NONE      = $FFFFFFFF;

	ADDR_ANY         = INADDR_ANY;

	MSG_OOB          = $1;             // process out-of-band data
  MSG_PEEK         = $2;             // peek at incoming message
  MSG_DONTROUTE    = $4;             // send without using routing tables

  MSG_PARTIAL      = $8000;          // partial send or recv for message xport

// WinSock 2 extension -- new flags for WSASend(), WSASendTo(), WSARecv() and WSARecvFrom()
	MSG_INTERRUPT    = $10;    // send/recv in the interrupt context
	MSG_MAXIOVLEN    = 16;


// Define constant based on rfc883, used by gethostbyxxxx() calls.

  MAXGETHOSTSTRUCT = 1024;

// Maximum queue length specifiable by listen.
	SOMAXCONN        = $7fffffff;

// WinSock 2 extension -- bit values and indices for FD_XXX network events
	FD_READ_BIT      = 0;
	FD_WRITE_BIT     = 1;
	FD_OOB_BIT       = 2;
	FD_ACCEPT_BIT    = 3;
	FD_CONNECT_BIT   = 4;
	FD_CLOSE_BIT     = 5;
	FD_QOS_BIT       = 6;
	FD_GROUP_QOS_BIT = 7;

	FD_MAX_EVENTS    = 8;

	FD_READ       = (1 shl FD_READ_BIT);
	FD_WRITE      = (1 shl FD_WRITE_BIT);
	FD_OOB        = (1 shl FD_OOB_BIT);
	FD_ACCEPT     = (1 shl FD_ACCEPT_BIT);
	FD_CONNECT    = (1 shl FD_CONNECT_BIT);
	FD_CLOSE      = (1 shl FD_CLOSE_BIT);
	FD_QOS        = (1 shl FD_QOS_BIT);
	FD_GROUP_QOS  = (1 shl FD_GROUP_QOS_BIT);

	FD_ALL_EVENTS = (1 shl FD_MAX_EVENTS) - 1;

// All Windows Sockets error constants are biased by WSABASEERR from the "normal"

  WSABASEERR              = 10000;

// Windows Sockets definitions of regular Microsoft C error constants

  WSAEINTR                = WSABASEERR+  4;
  WSAEBADF                = WSABASEERR+  9;
  WSAEACCES               = WSABASEERR+ 13;
  WSAEFAULT               = WSABASEERR+ 14;
  WSAEINVAL               = WSABASEERR+ 22;
  WSAEMFILE               = WSABASEERR+ 24;

// Windows Sockets definitions of regular Berkeley error constants

  WSAEWOULDBLOCK          = WSABASEERR+ 35;
  WSAEINPROGRESS          = WSABASEERR+ 36;
  WSAEALREADY             = WSABASEERR+ 37;
  WSAENOTSOCK             = WSABASEERR+ 38;
  WSAEDESTADDRREQ         = WSABASEERR+ 39;
  WSAEMSGSIZE             = WSABASEERR+ 40;
  WSAEPROTOTYPE           = WSABASEERR+ 41;
  WSAENOPROTOOPT          = WSABASEERR+ 42;
  WSAEPROTONOSUPPORT      = WSABASEERR+ 43;
  WSAESOCKTNOSUPPORT      = WSABASEERR+ 44;
  WSAEOPNOTSUPP           = WSABASEERR+ 45;
  WSAEPFNOSUPPORT         = WSABASEERR+ 46;
  WSAEAFNOSUPPORT         = WSABASEERR+ 47;
  WSAEADDRINUSE           = WSABASEERR+ 48;
  WSAEADDRNOTAVAIL        = WSABASEERR+ 49;
  WSAENETDOWN             = WSABASEERR+ 50;
  WSAENETUNREACH          = WSABASEERR+ 51;
  WSAENETRESET            = WSABASEERR+ 52;
  WSAECONNABORTED         = WSABASEERR+ 53;
  WSAECONNRESET           = WSABASEERR+ 54;
  WSAENOBUFS              = WSABASEERR+ 55;
  WSAEISCONN              = WSABASEERR+ 56;
  WSAENOTCONN             = WSABASEERR+ 57;
  WSAESHUTDOWN            = WSABASEERR+ 58;
  WSAETOOMANYREFS         = WSABASEERR+ 59;
  WSAETIMEDOUT            = WSABASEERR+ 60;
  WSAECONNREFUSED         = WSABASEERR+ 61;
  WSAELOOP                = WSABASEERR+ 62;
  WSAENAMETOOLONG         = WSABASEERR+ 63;
  WSAEHOSTDOWN            = WSABASEERR+ 64;
  WSAEHOSTUNREACH         = WSABASEERR+ 65;
  WSAENOTEMPTY            = WSABASEERR+ 66;
  WSAEPROCLIM             = WSABASEERR+ 67;
  WSAEUSERS               = WSABASEERR+ 68;
  WSAEDQUOT               = WSABASEERR+ 69;
  WSAESTALE               = WSABASEERR+ 70;
  WSAEREMOTE              = WSABASEERR+ 71;

// Extended Windows Sockets error constant definitions

  WSASYSNOTREADY          = WSABASEERR+ 91;
  WSAVERNOTSUPPORTED      = WSABASEERR+ 92;
  WSANOTINITIALISED       = WSABASEERR+ 93;
	WSAEDISCON              = WSABASEERR+101;
	WSAENOMORE              = WSABASEERR+102;
	WSAECANCELLED           = WSABASEERR+103;
	WSAEINVALIDPROCTABLE    = WSABASEERR+104;
	WSAEINVALIDPROVIDER     = WSABASEERR+105;
	WSAEPROVIDERFAILEDINIT  = WSABASEERR+106;
	WSASYSCALLFAILURE       = WSABASEERR+107;
	WSASERVICE_NOT_FOUND    = WSABASEERR+108;
	WSATYPE_NOT_FOUND       = WSABASEERR+109;
	WSA_E_NO_MORE           = WSABASEERR+110;
	WSA_E_CANCELLED         = WSABASEERR+111;
	WSAEREFUSED             = WSABASEERR+112;


{ Error return codes from gethostbyname() and gethostbyaddr()
  (when using the resolver). Note that these errors are
  retrieved via WSAGetLastError() and must therefore follow
  the rules for avoiding clashes with error numbers from
  specific implementations or language run-time systems.
  For this reason the codes are based at WSABASEERR+1001.
  Note also that [WSA]NO_ADDRESS is defined only for
  compatibility purposes. }

// Authoritative Answer: Host not found
  WSAHOST_NOT_FOUND        = WSABASEERR+1001;
  HOST_NOT_FOUND           = WSAHOST_NOT_FOUND;

// Non-Authoritative: Host not found, or SERVERFAIL
  WSATRY_AGAIN             = WSABASEERR+1002;
  TRY_AGAIN                = WSATRY_AGAIN;

// Non recoverable errors, FORMERR, REFUSED, NOTIMP
  WSANO_RECOVERY           = WSABASEERR+1003;
  NO_RECOVERY              = WSANO_RECOVERY;

// Valid name, no data record of requested type
  WSANO_DATA               = WSABASEERR+1004;
  NO_DATA                  = WSANO_DATA;

// no address, look for MX record
  WSANO_ADDRESS            = WSANO_DATA;
  NO_ADDRESS               = WSANO_ADDRESS;

// Define QOS related error return codes

	WSA_QOS_RECEIVERS          = WSABASEERR+1005; // at least one Reserve has arrived
	WSA_QOS_SENDERS            = WSABASEERR+1006; // at least one Path has arrived
	WSA_QOS_NO_SENDERS         = WSABASEERR+1007; // there are no senders
	WSA_QOS_NO_RECEIVERS       = WSABASEERR+1008; // there are no receivers
	WSA_QOS_REQUEST_CONFIRMED  = WSABASEERR+1009; // Reserve has been confirmed
	WSA_QOS_ADMISSION_FAILURE  = WSABASEERR+1010; // error due to lack of resources
	WSA_QOS_POLICY_FAILURE     = WSABASEERR+1011; // rejected for administrative reasons - bad credentials
	WSA_QOS_BAD_STYLE          = WSABASEERR+1012; // unknown or conflicting style
	WSA_QOS_BAD_OBJECT         = WSABASEERR+1013; // problem with some part of the filterspec or providerspecific buffer in general
	WSA_QOS_TRAFFIC_CTRL_ERROR = WSABASEERR+1014; // problem with some part of the flowspec
	WSA_QOS_GENERIC_ERROR      = WSABASEERR+1015; // general error
	WSA_QOS_ESERVICETYPE       = WSABASEERR+1016; // invalid service type in flowspec
	WSA_QOS_EFLOWSPEC          = WSABASEERR+1017; // invalid flowspec
	WSA_QOS_EPROVSPECBUF       = WSABASEERR+1018; // invalid provider specific buffer
	WSA_QOS_EFILTERSTYLE       = WSABASEERR+1019; // invalid filter style
	WSA_QOS_EFILTERTYPE        = WSABASEERR+1020; // invalid filter type
	WSA_QOS_EFILTERCOUNT       = WSABASEERR+1021; // incorrect number of filters
	WSA_QOS_EOBJLENGTH         = WSABASEERR+1022; // invalid object length
	WSA_QOS_EFLOWCOUNT         = WSABASEERR+1023; // incorrect number of flows
	WSA_QOS_EUNKOWNPSOBJ       = WSABASEERR+1024; // unknown object in provider specific buffer
	WSA_QOS_EPOLICYOBJ         = WSABASEERR+1025; // invalid policy object in provider specific buffer
	WSA_QOS_EFLOWDESC          = WSABASEERR+1026; // invalid flow descriptor in the list
	WSA_QOS_EPSFLOWSPEC        = WSABASEERR+1027; // inconsistent flow spec in provider specific buffer
	WSA_QOS_EPSFILTERSPEC      = WSABASEERR+1028; // invalid filter spec in provider specific buffer
	WSA_QOS_ESDMODEOBJ         = WSABASEERR+1029; // invalid shape discard mode object in provider specific buffer
	WSA_QOS_ESHAPERATEOBJ      = WSABASEERR+1030; // invalid shaping rate object in provider specific buffer
	WSA_QOS_RESERVED_PETYPE    = WSABASEERR+1031; // reserved policy element in provider specific buffer


{ WinSock 2 extension -- new error codes and type definition }
	WSA_IO_PENDING          = ERROR_IO_PENDING;
	WSA_IO_INCOMPLETE       = ERROR_IO_INCOMPLETE;
	WSA_INVALID_HANDLE      = ERROR_INVALID_HANDLE;
	WSA_INVALID_PARAMETER   = ERROR_INVALID_PARAMETER;
	WSA_NOT_ENOUGH_MEMORY   = ERROR_NOT_ENOUGH_MEMORY;
	WSA_OPERATION_ABORTED   = ERROR_OPERATION_ABORTED;
	WSA_INVALID_EVENT       = WSAEVENT(nil);
	WSA_MAXIMUM_WAIT_EVENTS = MAXIMUM_WAIT_OBJECTS;
	WSA_WAIT_FAILED         = $ffffffff;
	WSA_WAIT_EVENT_0        = WAIT_OBJECT_0;
	WSA_WAIT_IO_COMPLETION  = WAIT_IO_COMPLETION;
	WSA_WAIT_TIMEOUT        = WAIT_TIMEOUT;
	WSA_INFINITE            = INFINITE;

{ Windows Sockets errors redefined as regular Berkeley error constants.
  These are commented out in Windows NT to avoid conflicts with errno.h.
  Use the WSA constants instead. }

  EWOULDBLOCK        =  WSAEWOULDBLOCK;
  EINPROGRESS        =  WSAEINPROGRESS;
  EALREADY           =  WSAEALREADY;
  ENOTSOCK           =  WSAENOTSOCK;
  EDESTADDRREQ       =  WSAEDESTADDRREQ;
  EMSGSIZE           =  WSAEMSGSIZE;
  EPROTOTYPE         =  WSAEPROTOTYPE;
  ENOPROTOOPT        =  WSAENOPROTOOPT;
  EPROTONOSUPPORT    =  WSAEPROTONOSUPPORT;
  ESOCKTNOSUPPORT    =  WSAESOCKTNOSUPPORT;
  EOPNOTSUPP         =  WSAEOPNOTSUPP;
  EPFNOSUPPORT       =  WSAEPFNOSUPPORT;
  EAFNOSUPPORT       =  WSAEAFNOSUPPORT;
  EADDRINUSE         =  WSAEADDRINUSE;
  EADDRNOTAVAIL      =  WSAEADDRNOTAVAIL;
  ENETDOWN           =  WSAENETDOWN;
  ENETUNREACH        =  WSAENETUNREACH;
  ENETRESET          =  WSAENETRESET;
  ECONNABORTED       =  WSAECONNABORTED;
  ECONNRESET         =  WSAECONNRESET;
  ENOBUFS            =  WSAENOBUFS;
  EISCONN            =  WSAEISCONN;
  ENOTCONN           =  WSAENOTCONN;
  ESHUTDOWN          =  WSAESHUTDOWN;
  ETOOMANYREFS       =  WSAETOOMANYREFS;
  ETIMEDOUT          =  WSAETIMEDOUT;
  ECONNREFUSED       =  WSAECONNREFUSED;
  ELOOP              =  WSAELOOP;
  ENAMETOOLONG       =  WSAENAMETOOLONG;
  EHOSTDOWN          =  WSAEHOSTDOWN;
  EHOSTUNREACH       =  WSAEHOSTUNREACH;
  ENOTEMPTY          =  WSAENOTEMPTY;
  EPROCLIM           =  WSAEPROCLIM;
  EUSERS             =  WSAEUSERS;
  EDQUOT             =  WSAEDQUOT;
  ESTALE             =  WSAESTALE;
  EREMOTE            =  WSAEREMOTE;


  WSADESCRIPTION_LEN     =   256;
  WSASYS_STATUS_LEN      =   128;

type
  PWSAData = ^TWSAData;
  TWSAData = packed record
    wVersion       : Word;
    wHighVersion   : Word;
    szDescription  : Array[0..WSADESCRIPTION_LEN] of Char;
    szSystemStatus : Array[0..WSASYS_STATUS_LEN] of Char;
    iMaxSockets    : Word;
    iMaxUdpDg      : Word;
    lpVendorInfo   : PChar;
  end;

{	WSAOVERLAPPED = Record
		Internal: LongInt;
		InternalHigh: LongInt;
		Offset: LongInt;
		OffsetHigh: LongInt;
		hEvent: WSAEVENT;
	end;}
	WSAOVERLAPPED   = TOverlapped;
	TWSAOverlapped  = WSAOverlapped;
	PWSAOverlapped  = ^WSAOverlapped;
	LPWSAOVERLAPPED = PWSAOverlapped;

{	WinSock 2 extension -- WSABUF and QOS struct, include qos.h }
{ to pull in FLOWSPEC and related definitions }


	WSABUF = packed record
		len: U_LONG;	{ the length of the buffer }
		buf: PChar;	{ the pointer to the buffer }
	end {WSABUF};
	PWSABUF = ^WSABUF;
	LPWSABUF = PWSABUF;

	TServiceType = LongInt;

	TFlowSpec = packed record
		TokenRate,               // In Bytes/sec
		TokenBucketSize,         // In Bytes
		PeakBandwidth,           // In Bytes/sec
		Latency,                 // In microseconds
		DelayVariation : LongInt;// In microseconds
		ServiceType : TServiceType;
		MaxSduSize,	MinimumPolicedSize : LongInt;// In Bytes
	end;
	PFlowSpec = ^PFLOWSPEC;

	QOS = packed record
		SendingFlowspec: TFlowSpec;	{ the flow spec for data sending }
		ReceivingFlowspec: TFlowSpec;	{ the flow spec for data receiving }
		ProviderSpecific: WSABUF; { additional provider specific stuff }
	end;
	TQualityOfService = QOS;
	PQOS = ^QOS;
	LPQOS = PQOS;

const
	SERVICETYPE_NOTRAFFIC             =  $00000000;  // No data in this direction
	SERVICETYPE_BESTEFFORT            =  $00000001;  // Best Effort
	SERVICETYPE_CONTROLLEDLOAD        =  $00000002;  // Controlled Load
	SERVICETYPE_GUARANTEED            =  $00000003;  // Guaranteed
	SERVICETYPE_NETWORK_UNAVAILABLE   =  $00000004;  // Used to notify change to user
	SERVICETYPE_GENERAL_INFORMATION   =  $00000005;  // corresponds to "General Parameters" defined by IntServ
	SERVICETYPE_NOCHANGE              =  $00000006;  // used to indicate that the flow spec contains no change from any previous one
// to turn on immediate traffic control, OR this flag with the ServiceType field in teh FLOWSPEC
	SERVICE_IMMEDIATE_TRAFFIC_CONTROL =  $80000000;

//	WinSock 2 extension -- manifest constants for return values of the condition function
	CF_ACCEPT = $0000;
	CF_REJECT = $0001;
	CF_DEFER  = $0002;

//	WinSock 2 extension -- manifest constants for shutdown()
	SD_RECEIVE = $00;
	SD_SEND    = $01;
	SD_BOTH    = $02;

//	WinSock 2 extension -- data type and manifest constants for socket groups
	SG_UNCONSTRAINED_GROUP = $01;
	SG_CONSTRAINED_GROUP   = $02;

type
	GROUP = DWORD;

//	WinSock 2 extension -- data type for WSAEnumNetworkEvents()
	TWSANetworkEvents = record
		lNetworkEvents: LongInt;
		iErrorCode: Array[0..FD_MAX_EVENTS-1] of Integer;
	end;
	PWSANetworkEvents = ^TWSANetworkEvents;
	LPWSANetworkEvents = PWSANetworkEvents;

//	WinSock 2 extension -- WSAPROTOCOL_INFO structure

{$ifndef ver130}
	TGUID = packed record
		D1: LongInt;
		D2: Word;
		D3: Word;
		D4: Array[0..7] of Byte;
	end;
	PGUID = ^TGUID;
{$endif}
	LPGUID = PGUID;

//	WinSock 2 extension -- WSAPROTOCOL_INFO manifest constants
const
	MAX_PROTOCOL_CHAIN = 7;
	BASE_PROTOCOL      = 1;
	LAYERED_PROTOCOL   = 0;
	WSAPROTOCOL_LEN    = 255;

type
	TWSAProtocolChain = record
		ChainLen: Integer;	// the length of the chain,
		// length = 0 means layered protocol,
		// length = 1 means base protocol,
		// length > 1 means protocol chain
		ChainEntries: Array[0..MAX_PROTOCOL_CHAIN-1] of LongInt; // a list of dwCatalogEntryIds
	end;

type
	TWSAProtocol_InfoA = record
		dwServiceFlags1: LongInt;
		dwServiceFlags2: LongInt;
		dwServiceFlags3: LongInt;
		dwServiceFlags4: LongInt;
		dwProviderFlags: LongInt;
		ProviderId: TGUID;
		dwCatalogEntryId: LongInt;
		ProtocolChain: TWSAProtocolChain;
		iVersion: Integer;
		iAddressFamily: Integer;
		iMaxSockAddr: Integer;
		iMinSockAddr: Integer;
		iSocketType: Integer;
		iProtocol: Integer;
		iProtocolMaxOffset: Integer;
		iNetworkByteOrder: Integer;
		iSecurityScheme: Integer;
		dwMessageSize: LongInt;
		dwProviderReserved: LongInt;
		szProtocol: Array[0..WSAPROTOCOL_LEN+1-1] of Char;
	end {TWSAProtocol_InfoA};
	PWSAProtocol_InfoA = ^TWSAProtocol_InfoA;
	LPWSAProtocol_InfoA = PWSAProtocol_InfoA;

	TWSAProtocol_InfoW = record
		dwServiceFlags1: LongInt;
		dwServiceFlags2: LongInt;
		dwServiceFlags3: LongInt;
		dwServiceFlags4: LongInt;
		dwProviderFlags: LongInt;
		ProviderId: TGUID;
		dwCatalogEntryId: LongInt;
		ProtocolChain: TWSAProtocolChain;
		iVersion: Integer;
		iAddressFamily: Integer;
		iMaxSockAddr: Integer;
		iMinSockAddr: Integer;
		iSocketType: Integer;
		iProtocol: Integer;
		iProtocolMaxOffset: Integer;
		iNetworkByteOrder: Integer;
		iSecurityScheme: Integer;
		dwMessageSize: LongInt;
		dwProviderReserved: LongInt;
		szProtocol: Array[0..WSAPROTOCOL_LEN+1-1] of WideChar;
	end {TWSAProtocol_InfoW};
	PWSAProtocol_InfoW = ^TWSAProtocol_InfoW;
	LPWSAProtocol_InfoW = PWSAProtocol_InfoW;

{$IFDEF UNICODE}
	WSAProtocol_Info = TWSAProtocol_InfoW;
	TWSAProtocol_Info = TWSAProtocol_InfoW;
	PWSAProtocol_Info = PWSAProtocol_InfoW;
	LPWSAProtocol_Info = PWSAProtocol_InfoW;
{$ELSE}
	WSAProtocol_Info = TWSAProtocol_InfoA;
	TWSAProtocol_Info = TWSAProtocol_InfoA;
	PWSAProtocol_Info = PWSAProtocol_InfoA;
	LPWSAProtocol_Info = PWSAProtocol_InfoA;
{$ENDIF}

const
//	Flag bit definitions for dwProviderFlags
	PFL_MULTIPLE_PROTO_ENTRIES   = $00000001;
	PFL_RECOMMENDED_PROTO_ENTRY  = $00000002;
	PFL_HIDDEN                   = $00000004;
	PFL_MATCHES_PROTOCOL_ZERO    = $00000008;

//	Flag bit definitions for dwServiceFlags1
	XP1_CONNECTIONLESS           = $00000001;
	XP1_GUARANTEED_DELIVERY      = $00000002;
	XP1_GUARANTEED_ORDER         = $00000004;
	XP1_MESSAGE_ORIENTED         = $00000008;
	XP1_PSEUDO_STREAM            = $00000010;
	XP1_GRACEFUL_CLOSE           = $00000020;
	XP1_EXPEDITED_DATA           = $00000040;
	XP1_CONNECT_DATA             = $00000080;
	XP1_DISCONNECT_DATA          = $00000100;
	XP1_SUPPORT_BROADCAST        = $00000200;
	XP1_SUPPORT_MULTIPOINT       = $00000400;
	XP1_MULTIPOINT_CONTROL_PLANE = $00000800;
	XP1_MULTIPOINT_DATA_PLANE    = $00001000;
	XP1_QOS_SUPPORTED            = $00002000;
	XP1_INTERRUPT                = $00004000;
	XP1_UNI_SEND                 = $00008000;
	XP1_UNI_RECV                 = $00010000;
	XP1_IFS_HANDLES              = $00020000;
	XP1_PARTIAL_MESSAGE          = $00040000;

	BIGENDIAN    = $0000;
	LITTLEENDIAN = $0001;

	SECURITY_PROTOCOL_NONE = $0000;

//	WinSock 2 extension -- manifest constants for WSAJoinLeaf()
	JL_SENDER_ONLY   = $01;
	JL_RECEIVER_ONLY = $02;
	JL_BOTH          = $04;

//	WinSock 2 extension -- manifest constants for WSASocket()
	WSA_FLAG_OVERLAPPED        = $01;
	WSA_FLAG_MULTIPOINT_C_ROOT = $02;
	WSA_FLAG_MULTIPOINT_C_LEAF = $04;
	WSA_FLAG_MULTIPOINT_D_ROOT = $08;
	WSA_FLAG_MULTIPOINT_D_LEAF = $10;

//	WinSock 2 extension -- manifest constants for WSAIoctl()
	IOC_UNIX      = $00000000;
	IOC_WS2       = $08000000;
	IOC_PROTOCOL  = $10000000;
	IOC_VENDOR    = $18000000;

	SIO_ASSOCIATE_HANDLE                =  1 or IOC_WS2 or IOC_IN;
	SIO_ENABLE_CIRCULAR_QUEUEING        =  2 or IOC_WS2;
	SIO_FIND_ROUTE                      =  3 or IOC_WS2 or IOC_OUT;
	SIO_FLUSH                           =  4 or IOC_WS2;
	SIO_GET_BROADCAST_ADDRESS           =  5 or IOC_WS2 or IOC_OUT;
	SIO_GET_EXTENSION_FUNCTION_POINTER  =  6 or IOC_WS2 or IOC_INOUT;
	SIO_GET_QOS                         =  7 or IOC_WS2 or IOC_INOUT;
	SIO_GET_GROUP_QOS                   =  8 or IOC_WS2 or IOC_INOUT;
	SIO_MULTIPOINT_LOOPBACK             =  9 or IOC_WS2 or IOC_IN;
	SIO_MULTICAST_SCOPE                 = 10 or IOC_WS2 or IOC_IN;
	SIO_SET_QOS                         = 11 or IOC_WS2 or IOC_IN;
	SIO_SET_GROUP_QOS                   = 12 or IOC_WS2 or IOC_IN;
	SIO_TRANSLATE_HANDLE                = 13 or IOC_WS2 or IOC_INOUT;
	SIO_ROUTING_INTERFACE_QUERY         = 20 or IOC_WS2 or IOC_INOUT;
	SIO_ROUTING_INTERFACE_CHANGE        = 21 or IOC_WS2 or IOC_IN;
	SIO_ADDRESS_LIST_QUERY              = 22 or IOC_WS2 or IOC_OUT; // see below SOCKET_ADDRESS_LIST
	SIO_ADDRESS_LIST_CHANGE             = 23 or IOC_WS2;
	SIO_QUERY_TARGET_PNP_HANDLE         = 24 or IOC_WS2 or IOC_OUT;

//	WinSock 2 extension -- manifest constants for SIO_TRANSLATE_HANDLE ioctl
	TH_NETDEV = $00000001;
	TH_TAPI   = $00000002;

type


//	Manifest constants and type definitions related to name resolution and
//	registration (RNR) API
	TBLOB = packed record
		cbSize : U_LONG;
		pBlobData : PBYTE;
	end;
	PBLOB = ^TBLOB;

//	Service Install Flags

const
	SERVICE_MULTIPLE = $00000001;

// & Name Spaces
	NS_ALL         =  0;

	NS_SAP         =  1;
	NS_NDS         =  2;
	NS_PEER_BROWSE =  3;

	NS_TCPIP_LOCAL = 10;
	NS_TCPIP_HOSTS = 11;
	NS_DNS         = 12;
	NS_NETBT       = 13;
	NS_WINS        = 14;

	NS_NBP         = 20;

	NS_MS          = 30;
	NS_STDA        = 31;
	NS_NTDS        = 32;

	NS_X500        = 40;
	NS_NIS         = 41;
	NS_NISPLUS     = 42;

	NS_WRQ         = 50;

	NS_NETDES      = 60;

{	Resolution flags for WSAGetAddressByName().
	Note these are also used by the 1.1 API GetAddressByName, so leave them around. }
	RES_UNUSED_1    = $00000001;
	RES_FLUSH_CACHE = $00000002;
	RES_SERVICE     = $00000004;

{	Well known value names for Service Types }
	SERVICE_TYPE_VALUE_IPXPORTA              = 'IpxSocket';
	SERVICE_TYPE_VALUE_IPXPORTW : PWideChar  = 'IpxSocket';
	SERVICE_TYPE_VALUE_SAPIDA                = 'SapId';
	SERVICE_TYPE_VALUE_SAPIDW : PWideChar    = 'SapId';

	SERVICE_TYPE_VALUE_TCPPORTA              = 'TcpPort';
	SERVICE_TYPE_VALUE_TCPPORTW : PWideChar  = 'TcpPort';

	SERVICE_TYPE_VALUE_UDPPORTA              = 'UdpPort';
	SERVICE_TYPE_VALUE_UDPPORTW : PWideChar  = 'UdpPort';

	SERVICE_TYPE_VALUE_OBJECTIDA             = 'ObjectId';
	SERVICE_TYPE_VALUE_OBJECTIDW : PWideChar = 'ObjectId';

{$IFDEF UNICODE}
	SERVICE_TYPE_VALUE_SAPID    = SERVICE_TYPE_VALUE_SAPIDW;
	SERVICE_TYPE_VALUE_TCPPORT  = SERVICE_TYPE_VALUE_TCPPORTW;
	SERVICE_TYPE_VALUE_UDPPORT  = SERVICE_TYPE_VALUE_UDPPORTW;
	SERVICE_TYPE_VALUE_OBJECTID = SERVICE_TYPE_VALUE_OBJECTIDW;
{$ELSE}
	SERVICE_TYPE_VALUE_SAPID    = SERVICE_TYPE_VALUE_SAPIDA;
	SERVICE_TYPE_VALUE_TCPPORT  = SERVICE_TYPE_VALUE_TCPPORTA;
	SERVICE_TYPE_VALUE_UDPPORT  = SERVICE_TYPE_VALUE_UDPPORTA;
	SERVICE_TYPE_VALUE_OBJECTID = SERVICE_TYPE_VALUE_OBJECTIDA;
{$ENDIF}

// SockAddr Information
type
	SOCKET_ADDRESS = packed record
		lpSockaddr : PSockAddr;
		iSockaddrLength : Integer;
	end;
	PSOCKET_ADDRESS = ^SOCKET_ADDRESS;

// CSAddr Information
	CSADDR_INFO = packed record
		LocalAddr, RemoteAddr  : SOCKET_ADDRESS;
		iSocketType, iProtocol : LongInt;
	end;
	PCSADDR_INFO = ^CSADDR_INFO;
	LPCSADDR_INFO = ^CSADDR_INFO;

// Address list returned via WSAIoctl( SIO_ADDRESS_LIST_QUERY )
	SOCKET_ADDRESS_LIST = packed record
		iAddressCount : Integer;
		Address       : Array [0..0] of SOCKET_ADDRESS;
	end;
	LPSOCKET_ADDRESS_LIST = ^SOCKET_ADDRESS_LIST;

// Address Family/Protocol Tuples
	AFProtocols = record
		iAddressFamily : Integer;
		iProtocol      : Integer;
	end;
	TAFProtocols = AFProtocols;
	PAFProtocols = ^TAFProtocols;


//	Client Query API Typedefs

// The comparators
	TWSAEComparator = (COMP_EQUAL {= 0}, COMP_NOTLESS );

	TWSAVersion = record
		dwVersion : DWORD;
		ecHow     : TWSAEComparator;
	end;
	PWSAVersion = ^TWSAVersion;

	TWSAQuerySetA = packed record
		dwSize                  : DWORD;
		lpszServiceInstanceName : PChar;
		lpServiceClassId        : PGUID;
		lpVersion               : PWSAVERSION;
		lpszComment             : PChar;
		dwNameSpace             : DWORD;
		lpNSProviderId          : PGUID;
		lpszContext             : PChar;
		dwNumberOfProtocols     : DWORD;
		lpafpProtocols          : PAFProtocols;
		lpszQueryString         : PChar;
		dwNumberOfCsAddrs       : DWORD;
		lpcsaBuffer             : PCSADDR_INFO;
		dwOutputFlags           : DWORD;
		lpBlob                  : PBLOB;
	end;
	PWSAQuerySetA = ^TWSAQuerySetA;
	LPWSAQuerySetA = PWSAQuerySetA;

	TWSAQuerySetW = packed record
		dwSize                  : DWORD;
		lpszServiceInstanceName : PWideChar;
		lpServiceClassId        : PGUID;
		lpVersion               : PWSAVERSION;
		lpszComment             : PWideChar;
		dwNameSpace             : DWORD;
		lpNSProviderId          : PGUID;
		lpszContext             : PWideChar;
		dwNumberOfProtocols     : DWORD;
		lpafpProtocols          : PAFProtocols;
		lpszQueryString         : PWideChar;
		dwNumberOfCsAddrs       : DWORD;
		lpcsaBuffer             : PCSADDR_INFO;
		dwOutputFlags           : DWORD;
		lpBlob                  : PBLOB;
	end;
	PWSAQuerySetW = ^TWSAQuerySetW;
	LPWSAQuerySetW = PWSAQuerySetW;

{$IFDEF UNICODE}
	TWSAQuerySet  = TWSAQuerySetA;
	PWSAQuerySet  = PWSAQuerySetW;
	LPWSAQuerySet = PWSAQuerySetW;
{$ELSE}
	TWSAQuerySet  = TWSAQuerySetA;
	PWSAQuerySet  = PWSAQuerySetA;
	LPWSAQuerySet = PWSAQuerySetA;
{$ENDIF}

const
	LUP_DEEP                = $0001;
	LUP_CONTAINERS          = $0002;
	LUP_NOCONTAINERS        = $0004;
	LUP_NEAREST             = $0008;
	LUP_RETURN_NAME         = $0010;
	LUP_RETURN_TYPE         = $0020;
	LUP_RETURN_VERSION      = $0040;
	LUP_RETURN_COMMENT      = $0080;
	LUP_RETURN_ADDR         = $0100;
	LUP_RETURN_BLOB         = $0200;
	LUP_RETURN_ALIASES      = $0400;
	LUP_RETURN_QUERY_STRING = $0800;
	LUP_RETURN_ALL          = $0FF0;
	LUP_RES_SERVICE         = $8000;

	LUP_FLUSHCACHE          = $1000;
	LUP_FLUSHPREVIOUS       = $2000;

// Return flags
	RESULT_IS_ALIAS = $0001;

type
// Service Address Registration and Deregistration Data Types.
	TWSAeSetServiceOp = ( RNRSERVICE_REGISTER{=0}, RNRSERVICE_DEREGISTER, RNRSERVICE_DELETE );

{	Service Installation/Removal Data Types. }
	TWSANSClassInfoA = packed record
		lpszName    : PChar;
		dwNameSpace : DWORD;
		dwValueType : DWORD;
		dwValueSize : DWORD;
		lpValue     : Pointer;
	end;
	PWSANSClassInfoA = ^TWSANSClassInfoA;

	TWSANSClassInfoW = packed record
		lpszName    : PWideChar;
		dwNameSpace : DWORD;
		dwValueType : DWORD;
		dwValueSize : DWORD;
		lpValue     : Pointer;
	end {TWSANSClassInfoW};
	PWSANSClassInfoW = ^TWSANSClassInfoW;

{$IFDEF UNICODE}
	WSANSClassInfo   = TWSANSClassInfoW;
	TWSANSClassInfo  = TWSANSClassInfoW;
	PWSANSClassInfo  = PWSANSClassInfoW;
	LPWSANSClassInfo = PWSANSClassInfoW;
{$ELSE}
	WSANSClassInfo   = TWSANSClassInfoA;
	TWSANSClassInfo  = TWSANSClassInfoA;
	PWSANSClassInfo  = PWSANSClassInfoA;
	LPWSANSClassInfo = PWSANSClassInfoA;
{$ENDIF // UNICODE}

	TWSAServiceClassInfoA = packed record
		lpServiceClassId     : PGUID;
		lpszServiceClassName : PChar;
		dwCount              : DWORD;
		lpClassInfos         : PWSANSClassInfoA;
	end;
	PWSAServiceClassInfoA  = ^TWSAServiceClassInfoA;
	LPWSAServiceClassInfoA = PWSAServiceClassInfoA;

	TWSAServiceClassInfoW = packed record
		lpServiceClassId     : PGUID;
		lpszServiceClassName : PWideChar;
		dwCount              : DWORD;
		lpClassInfos         : PWSANSClassInfoW;
	end;
	PWSAServiceClassInfoW  = ^TWSAServiceClassInfoW;
	LPWSAServiceClassInfoW = PWSAServiceClassInfoW;

{$IFDEF UNICODE}
	WSAServiceClassInfo   = TWSAServiceClassInfoW;
	TWSAServiceClassInfo  = TWSAServiceClassInfoW;
	PWSAServiceClassInfo  = PWSAServiceClassInfoW;
	LPWSAServiceClassInfo = PWSAServiceClassInfoW;
{$ELSE}
	WSAServiceClassInfo   = TWSAServiceClassInfoA;
	TWSAServiceClassInfo  = TWSAServiceClassInfoA;
	PWSAServiceClassInfo  = PWSAServiceClassInfoA;
	LPWSAServiceClassInfo = PWSAServiceClassInfoA;
{$ENDIF}

	TWSANameSpace_InfoA = packed record
		NSProviderId   : TGUID;
		dwNameSpace    : DWORD;
		fActive        : DWORD{Bool};
		dwVersion      : DWORD;
		lpszIdentifier : PChar;
	end;
	PWSANameSpace_InfoA = ^TWSANameSpace_InfoA;
	LPWSANameSpace_InfoA = PWSANameSpace_InfoA;

	TWSANameSpace_InfoW = packed record
		NSProviderId   : TGUID;
		dwNameSpace    : DWORD;
		fActive        : DWORD{Bool};
		dwVersion      : DWORD;
		lpszIdentifier : PWideChar;
	end {TWSANameSpace_InfoW};
	PWSANameSpace_InfoW = ^TWSANameSpace_InfoW;
	LPWSANameSpace_InfoW = PWSANameSpace_InfoW;

{$IFDEF UNICODE}
	WSANameSpace_Info   = TWSANameSpace_InfoW;
	TWSANameSpace_Info  = TWSANameSpace_InfoW;
	PWSANameSpace_Info  = PWSANameSpace_InfoW;
	LPWSANameSpace_Info = PWSANameSpace_InfoW;
{$ELSE}
	WSANameSpace_Info   = TWSANameSpace_InfoA;
	TWSANameSpace_Info  = TWSANameSpace_InfoA;
	PWSANameSpace_Info  = PWSANameSpace_InfoA;
	LPWSANameSpace_Info = PWSANameSpace_InfoA;
{$ENDIF}

{	WinSock 2 extensions -- data types for the condition function in }
{ WSAAccept() and overlapped I/O completion routine. }
type
	LPCONDITIONPROC = function (lpCallerId: LPWSABUF; lpCallerData : LPWSABUF; lpSQOS,lpGQOS : LPQOS; lpCalleeId,lpCalleeData : LPWSABUF;
		g : GROUP; dwCallbackData : DWORD ) : Integer; stdcall;
	LPWSAOVERLAPPED_COMPLETION_ROUTINE = procedure ( const dwError, cbTransferred : DWORD; const lpOverlapped : LPWSAOVERLAPPED; const dwFlags : DWORD ); stdcall;

function accept( const s: TSocket; var addr: TSockAddr; var addrlen: Integer ): TSocket; stdcall;
function bind( const s: TSocket; const addr: PSockAddr; const namelen: Integer ): Integer; stdcall;
function closesocket( const s: TSocket ): Integer; stdcall;
function connect( const s: TSocket; const name: PSockAddr; namelen: Integer): Integer; stdcall;
function ioctlsocket( const s: TSocket; const cmd: DWORD; var arg: u_long ): Integer; stdcall;
function getpeername( const s: TSocket; var name: TSockAddr; var namelen: Integer ): Integer; stdcall;
function getsockname( const s: TSocket; var name: TSockAddr; var namelen: Integer ): Integer; stdcall;
function getsockopt( const s: TSocket; const level, optname: Integer; optval: PChar; var optlen: Integer ): Integer; stdcall;
function htonl(hostlong: u_long): u_long; stdcall;
function htons(hostshort: u_short): u_short; stdcall;
function inet_addr(cp: PChar): u_long; stdcall;
function inet_ntoa(inaddr: TInAddr): PChar; stdcall;
function listen(s: TSocket; backlog: Integer): Integer; stdcall;
function ntohl(netlong: u_long): u_long; stdcall;
function ntohs(netshort: u_short): u_short; stdcall;
function recv(s: TSocket; var Buf; len, flags: Integer): Integer; stdcall;
function recvfrom(s: TSocket; var Buf; len, flags: Integer; var from: TSockAddr; var fromlen: Integer): Integer; stdcall;
function select(nfds: Integer; readfds, writefds, exceptfds: PFDSet; timeout: PTimeVal): Integer; stdcall;
function send(s: TSocket; var Buf; len, flags: Integer): Integer; stdcall;
function sendto(s: TSocket; var Buf; len, flags: Integer; var addrto: TSockAddr; tolen: Integer): Integer; stdcall;
function setsockopt(s: TSocket; level, optname: Integer; optval: PChar; optlen: Integer): Integer; stdcall;
function shutdown(s: TSocket; how: Integer): Integer; stdcall;
function socket( const af, struct, protocol: Integer ): TSocket; stdcall;
function gethostbyaddr(addr: Pointer; len, struct: Integer): PHostEnt; stdcall;
function gethostbyname(name: PChar): PHostEnt; stdcall;
function gethostname(name: PChar; len: Integer): Integer; stdcall;
function getservbyport(port: Integer; proto: PChar): PServEnt; stdcall;
function getservbyname(const name, proto: PChar): PServEnt; stdcall;
function getprotobynumber(const proto: Integer): PProtoEnt; stdcall;
function getprotobyname(const name: PChar): PProtoEnt; stdcall;
function WSAStartup(wVersionRequired: word; var WSData: TWSAData): Integer; stdcall;
function WSACleanup: Integer; stdcall;
procedure WSASetLastError(iError: Integer); stdcall;
function WSAGetLastError: Integer; stdcall;
function WSAIsBlocking: BOOL; stdcall;
function WSAUnhookBlockingHook: Integer; stdcall;
function WSASetBlockingHook(lpBlockFunc: TFarProc): TFarProc; stdcall;
function WSACancelBlockingCall: Integer; stdcall;
function WSAAsyncGetServByName(HWindow: HWND; wMsg: u_int; name, proto, buf: PChar; buflen: Integer): THandle; stdcall;
function WSAAsyncGetServByPort( HWindow: HWND; wMsg, port: u_int; proto, buf: PChar; buflen: Integer): THandle; stdcall;
function WSAAsyncGetProtoByName(HWindow: HWND; wMsg: u_int; name, buf: PChar; buflen: Integer): THandle; stdcall;
function WSAAsyncGetProtoByNumber(HWindow: HWND; wMsg: u_int; number: Integer; buf: PChar; buflen: Integer): THandle; stdcall;
function WSAAsyncGetHostByName(HWindow: HWND; wMsg: u_int; name, buf: PChar; buflen: Integer): THandle; stdcall;
function WSAAsyncGetHostByAddr(HWindow: HWND; wMsg: u_int; addr: PChar; len, struct: Integer; buf: PChar; buflen: Integer): THandle; stdcall;
function WSACancelAsyncRequest(hAsyncTaskHandle: THandle): Integer; stdcall;
function WSAAsyncSelect(s: TSocket; HWindow: HWND; wMsg: u_int; lEvent: Longint): Integer; stdcall;
function __WSAFDIsSet(s: TSOcket; var FDSet: TFDSet): Bool; stdcall;

{	WinSock 2 API new function prototypes }
function WSAAccept( s : TSocket; addr : TSockAddr; addrlen : PInteger; lpfnCondition : LPCONDITIONPROC; dwCallbackData : DWORD ): TSocket; stdcall;
function WSACloseEvent( hEvent : WSAEVENT) : WordBool; stdcall;
function WSAConnect( s : TSocket; const name : PSockAddr; namelen : Integer; lpCallerData,lpCalleeData : LPWSABUF; lpSQOS,lpGQOS : LPQOS ) : Integer; stdcall;
function WSACreateEvent : WSAEVENT; stdcall;

function WSADuplicateSocketA( s : TSocket; dwProcessId : DWORD; lpProtocolInfo : LPWSAProtocol_InfoA ) : Integer; stdcall;
function WSADuplicateSocketW( s : TSocket; dwProcessId : DWORD; lpProtocolInfo : LPWSAProtocol_InfoW ) : Integer; stdcall;
function WSADuplicateSocket( s : TSocket; dwProcessId : DWORD; lpProtocolInfo : LPWSAProtocol_Info ) : Integer; stdcall;

function WSAEnumNetworkEvents( const s : TSocket; const hEventObject : WSAEVENT; lpNetworkEvents : LPWSANETWORKEVENTS ) :Integer; stdcall;
function WSAEnumProtocolsA( lpiProtocols : PInteger; lpProtocolBuffer : LPWSAProtocol_InfoA; var lpdwBufferLength : DWORD ) : Integer; stdcall;
function WSAEnumProtocolsW( lpiProtocols : PInteger; lpProtocolBuffer : LPWSAProtocol_InfoW; var lpdwBufferLength : DWORD ) : Integer; stdcall;
function WSAEnumProtocols( lpiProtocols : PInteger; lpProtocolBuffer : LPWSAProtocol_Info; var lpdwBufferLength : DWORD ) : Integer; stdcall;

function WSAEventSelect( s : TSocket; hEventObject : WSAEVENT; lNetworkEvents : LongInt ): Integer; stdcall;

function WSAGetOverlappedResult( s : TSocket; lpOverlapped : LPWSAOVERLAPPED; lpcbTransfer : LPDWORD; fWait : BOOL; var lpdwFlags : DWORD ) : WordBool; stdcall;

function WSAGetQosByName( s : TSocket; lpQOSName : LPWSABUF; lpQOS : LPQOS ): WordBool; stdcall;

function WSAhtonl( s : TSocket; hostlong : u_long; var lpnetlong : DWORD ): Integer; stdcall;
function WSAhtons( s : TSocket; hostshort : u_short; var lpnetshort : WORD ): Integer; stdcall;

function WSAIoctl( s : TSocket; dwIoControlCode : DWORD; lpvInBuffer : Pointer; cbInBuffer : DWORD; lpvOutBuffer : Pointer; cbOutBuffer : DWORD;
	lpcbBytesReturned : LPDWORD; lpOverlapped : LPWSAOVERLAPPED; lpCompletionRoutine : LPWSAOVERLAPPED_COMPLETION_ROUTINE ) : Integer; stdcall;

function WSAJoinLeaf( s : TSocket; name : PSockAddr; namelen : Integer; lpCallerData,lpCalleeData : LPWSABUF;
	lpSQOS,lpGQOS : LPQOS; dwFlags : DWORD ) : TSocket; stdcall;

function WSANtohl( s : TSocket; netlong : u_long; var lphostlong : DWORD ): Integer; stdcall;
function WSANtohs( s : TSocket; netshort : u_short; var lphostshort : WORD ): Integer; stdcall;

function WSARecv( s : TSocket; lpBuffers : LPWSABUF; dwBufferCount : DWORD; var lpNumberOfBytesRecvd : DWORD; var lpFlags : DWORD;
	lpOverlapped : LPWSAOVERLAPPED; lpCompletionRoutine : LPWSAOVERLAPPED_COMPLETION_ROUTINE ): Integer; stdcall;
function WSARecvDisconnect( s : TSocket; lpInboundDisconnectData : LPWSABUF ): Integer; stdcall;
function WSARecvFrom( s : TSocket; lpBuffers : LPWSABUF; dwBufferCount : DWORD; var lpNumberOfBytesRecvd : DWORD; var lpFlags : DWORD;
	lpFrom : PSockAddr; lpFromlen : PInteger; lpOverlapped : LPWSAOVERLAPPED; lpCompletionRoutine : LPWSAOVERLAPPED_COMPLETION_ROUTINE ): Integer; stdcall;

function WSAResetEvent( hEvent : WSAEVENT ): WordBool; stdcall;

function WSASend( s : TSocket; lpBuffers : LPWSABUF; dwBufferCount : DWORD; var lpNumberOfBytesSent : DWORD; dwFlags : DWORD;
	lpOverlapped : LPWSAOVERLAPPED; lpCompletionRoutine : LPWSAOVERLAPPED_COMPLETION_ROUTINE ): Integer; stdcall;
function WSASendDisconnect( s : TSocket; lpOutboundDisconnectData : LPWSABUF ): Integer; stdcall;
function WSASendTo( s : TSocket; lpBuffers : LPWSABUF; dwBufferCount : DWORD; var lpNumberOfBytesSent : DWORD; dwFlags : DWORD;
	lpTo : PSockAddr; iTolen : Integer; lpOverlapped : LPWSAOVERLAPPED; lpCompletionRoutine : LPWSAOVERLAPPED_COMPLETION_ROUTINE ): Integer; stdcall;

function WSASetEvent( hEvent : WSAEVENT ): WordBool; stdcall;

function WSASocketA( af, iType, protocol : Integer; lpProtocolInfo : LPWSAProtocol_InfoA; g : GROUP; dwFlags : DWORD ): TSocket; stdcall;
function WSASocketW( af, iType, protocol : Integer; lpProtocolInfo : LPWSAProtocol_InfoW; g : GROUP; dwFlags : DWORD ): TSocket; stdcall;
function WSASocket( af, iType, protocol : Integer; lpProtocolInfo : LPWSAProtocol_Info; g : GROUP; dwFlags : DWORD ): TSocket; stdcall;

function WSAWaitForMultipleEvents( cEvents : DWORD; lphEvents : PWSAEVENT; fWaitAll : LongBool;
	dwTimeout : DWORD; fAlertable : LongBool ): DWORD; stdcall;

function WSAAddressToStringA( lpsaAddress : PSockAddr; const dwAddressLength : DWORD; const lpProtocolInfo : LPWSAProtocol_InfoA;
	const lpszAddressString : PChar; var lpdwAddressStringLength : DWORD ): Integer; stdcall;
function WSAAddressToStringW( lpsaAddress : PSockAddr; const dwAddressLength : DWORD; const lpProtocolInfo : LPWSAProtocol_InfoW;
	const lpszAddressString : PWideChar; var lpdwAddressStringLength : DWORD ): Integer; stdcall;
function WSAAddressToString( lpsaAddress : PSockAddr; const dwAddressLength : DWORD; const lpProtocolInfo : LPWSAProtocol_Info;
	const lpszAddressString : PMBChar; var lpdwAddressStringLength : DWORD ): Integer; stdcall;

function WSAStringToAddressA( const AddressString : PChar; const AddressFamily: Integer; const lpProtocolInfo : LPWSAProtocol_InfoA;
	var lpAddress : TSockAddr; var lpAddressLength : Integer ): Integer; stdcall;
function WSAStringToAddressW( const AddressString : PWideChar; const AddressFamily: Integer; const lpProtocolInfo : LPWSAProtocol_InfoA;
	var lpAddress : TSockAddr; var lpAddressLength : Integer ): Integer; stdcall;
function WSAStringToAddress( const AddressString : PMBChar; const AddressFamily: Integer; const lpProtocolInfo : LPWSAProtocol_Info;
	var lpAddress : TSockAddr; var lpAddressLength : Integer ): Integer; stdcall;

{	Registration and Name Resolution API functions }
function WSALookupServiceBeginA( var qsRestrictions : TWSAQuerySetA; const dwControlFlags : DWORD; var hLookup : THANDLE ): Integer; stdcall;
function WSALookupServiceBeginW( var qsRestrictions : TWSAQuerySetW; const dwControlFlags : DWORD; var hLookup : THANDLE ): Integer; stdcall;
function WSALookupServiceBegin( var qsRestrictions : TWSAQuerySet; const dwControlFlags : DWORD; var hLookup : THANDLE ): Integer; stdcall;

function WSALookupServiceNextA( const hLookup : THandle; const dwControlFlags : DWORD; var dwBufferLength : DWORD; lpqsResults : PWSAQuerySetA ): Integer; stdcall;
function WSALookupServiceNextW( const hLookup : THandle; const dwControlFlags : DWORD; var dwBufferLength : DWORD; lpqsResults : PWSAQuerySetW ): Integer; stdcall;
function WSALookupServiceNext( const hLookup : THandle; const dwControlFlags : DWORD; var dwBufferLength : DWORD; lpqsResults : PWSAQuerySet ): Integer; stdcall;

function WSALookupServiceEnd( const hLookup : THandle ): Integer; stdcall;

function WSAInstallServiceClassA( const lpServiceClassInfo : LPWSAServiceClassInfoA ) : Integer; stdcall;
function WSAInstallServiceClassW( const lpServiceClassInfo : LPWSAServiceClassInfoW ) : Integer; stdcall;
function WSAInstallServiceClass( const lpServiceClassInfo : LPWSAServiceClassInfo ) : Integer; stdcall;

function WSARemoveServiceClass( const lpServiceClassId : PGUID ) : Integer; stdcall;

function WSAGetServiceClassInfoA( const lpProviderId : PGUID; const lpServiceClassId : PGUID; var lpdwBufSize : DWORD;
	lpServiceClassInfo : LPWSAServiceClassInfoA ): Integer; stdcall;
function WSAGetServiceClassInfoW( const lpProviderId : PGUID; const lpServiceClassId : PGUID; var lpdwBufSize : DWORD;
	lpServiceClassInfo : LPWSAServiceClassInfoW ): Integer; stdcall;
function WSAGetServiceClassInfo( const lpProviderId : PGUID; const lpServiceClassId : PGUID; var lpdwBufSize : DWORD;
	lpServiceClassInfo : LPWSAServiceClassInfo ): Integer; stdcall;

function WSAEnumNameSpaceProvidersA( var lpdwBufferLength: DWORD; const lpnspBuffer: LPWSANameSpace_InfoA ): Integer; stdcall;
function WSAEnumNameSpaceProvidersW( var lpdwBufferLength: DWORD; const lpnspBuffer: LPWSANameSpace_InfoW ): Integer; stdcall;
function WSAEnumNameSpaceProviders( var lpdwBufferLength: DWORD; const lpnspBuffer: LPWSANameSpace_Info ): Integer; stdcall;

function WSAGetServiceClassNameByClassIdA( const lpServiceClassId: PGUID; lpszServiceClassName: PChar;
	var lpdwBufferLength: DWORD ): Integer; stdcall;
function WSAGetServiceClassNameByClassIdW( const lpServiceClassId: PGUID; lpszServiceClassName: PWideChar;
	var lpdwBufferLength: DWORD ): Integer; stdcall;
function WSAGetServiceClassNameByClassId( const lpServiceClassId: PGUID; lpszServiceClassName: PMBChar;
	var lpdwBufferLength: DWORD ): Integer; stdcall;

function WSASetServiceA( const lpqsRegInfo: LPWSAQuerySetA; const essoperation: TWSAeSetServiceOp;
	const dwControlFlags: DWORD ): Integer; stdcall;
function WSASetServiceW( const lpqsRegInfo: LPWSAQuerySetW; const essoperation: TWSAeSetServiceOp;
	const dwControlFlags: DWORD ): Integer; stdcall;
function WSASetService( const lpqsRegInfo: LPWSAQuerySet; const essoperation: TWSAeSetServiceOp;
	const dwControlFlags: DWORD ): Integer; stdcall;

function WSAProviderConfigChange( var lpNotificationHandle : THandle; lpOverlapped : LPWSAOVERLAPPED; lpCompletionRoutine : LPWSAOVERLAPPED_COMPLETION_ROUTINE ) : Integer; stdcall;


{ Macros }
function WSAMakeSyncReply(Buflen, Error: Word): Longint;
function WSAMakeSelectReply(Event, Error: Word): Longint;
function WSAGetAsyncBuflen(Param: Longint): Word;
function WSAGetAsyncError(Param: Longint): Word;
function WSAGetSelectEvent(Param: Longint): Word;
function WSAGetSelectError(Param: Longint): Word;

procedure FD_CLR(Socket: TSocket; var FDSet: TFDSet);
function FD_ISSET(Socket: TSocket; var FDSet: TFDSet): Boolean;
procedure FD_SET(Socket: TSocket; var FDSet: TFDSet);
procedure FD_ZERO(var FDSet: TFDSet);
function StrLen(const Str: PChar): Cardinal; assembler;

{$include ws2tcpip.inc}
{$include wsipx.inc}
{$include wsnwlink.inc}
{$include wsnetbs.inc}

//=============================================================
implementation
//=============================================================

function accept;	external WINSOCK2_DLL name 'accept';
function bind;	external WINSOCK2_DLL name 'bind';
function closesocket;	external WINSOCK2_DLL name 'closesocket';
function connect;	external WINSOCK2_DLL name 'connect';
function ioctlsocket;	external WINSOCK2_DLL name 'ioctlsocket';
function getpeername;	external WINSOCK2_DLL name 'getpeername';
function getsockname;	external WINSOCK2_DLL name 'getsockname';
function getsockopt;	external WINSOCK2_DLL name 'getsockopt';
function htonl;	external WINSOCK2_DLL name 'htonl';
function htons;	external WINSOCK2_DLL name 'htons';
function inet_addr;	external WINSOCK2_DLL name 'inet_addr';
function inet_ntoa;	external WINSOCK2_DLL name 'inet_ntoa';
function listen;	external WINSOCK2_DLL name 'listen';
function ntohl;	external WINSOCK2_DLL name 'ntohl';
function ntohs;	external WINSOCK2_DLL name 'ntohs';
function recv;	external WINSOCK2_DLL name 'recv';
function recvfrom;	external WINSOCK2_DLL name 'recvfrom';
function select;	external WINSOCK2_DLL name 'select';
function send;	external WINSOCK2_DLL name 'send';
function sendto;	external WINSOCK2_DLL name 'sendto';
function setsockopt;	external WINSOCK2_DLL name 'setsockopt';
function shutdown;	external WINSOCK2_DLL name 'shutdown';
function socket;	external WINSOCK2_DLL name 'socket';
function gethostbyaddr;	external WINSOCK2_DLL name 'gethostbyaddr';
function gethostbyname;	external WINSOCK2_DLL name 'gethostbyname';
function gethostname;	external WINSOCK2_DLL name 'gethostname';
function getservbyport;	external WINSOCK2_DLL name 'getservbyport';
function getservbyname;	external WINSOCK2_DLL name 'getservbyname';
function getprotobynumber;	external WINSOCK2_DLL name 'getprotobynumber';
function getprotobyname;	external WINSOCK2_DLL name 'getprotobyname';
function WSAStartup;	external WINSOCK2_DLL name 'WSAStartup';
function WSACleanup;	external WINSOCK2_DLL name 'WSACleanup';
procedure WSASetLastError;	external WINSOCK2_DLL name 'WSASetLastError';
function WSAGetLastError;	external WINSOCK2_DLL name 'WSAGetLastError';
function WSAIsBlocking;	external WINSOCK2_DLL name 'WSAIsBlocking';
function WSAUnhookBlockingHook;	external WINSOCK2_DLL name 'WSAUnhookBlockingHook';
function WSASetBlockingHook;	external WINSOCK2_DLL name 'WSASetBlockingHook';
function WSACancelBlockingCall;	external WINSOCK2_DLL name 'WSACancelBlockingCall';
function WSAAsyncGetServByName;	external WINSOCK2_DLL name 'WSAAsyncGetServByName';
function WSAAsyncGetServByPort;	external WINSOCK2_DLL name 'WSAAsyncGetServByPort';
function WSAAsyncGetProtoByName;	external WINSOCK2_DLL name 'WSAAsyncGetProtoByName';
function WSAAsyncGetProtoByNumber;	external WINSOCK2_DLL name 'WSAAsyncGetProtoByNumber';
function WSAAsyncGetHostByName;	external WINSOCK2_DLL name 'WSAAsyncGetHostByName';
function WSAAsyncGetHostByAddr;	external WINSOCK2_DLL name 'WSAAsyncGetHostByAddr';
function WSACancelAsyncRequest;	external WINSOCK2_DLL name 'WSACancelAsyncRequest';
function WSAAsyncSelect;	external WINSOCK2_DLL name 'WSAAsyncSelect';
function __WSAFDIsSet;	external WINSOCK2_DLL name '__WSAFDIsSet';

{	WinSock 2 API new function prototypes }
function WSAAccept; external WINSOCK2_DLL name 'WSAAccept';
function WSACloseEvent;	external WINSOCK2_DLL name 'WSACloseEvent';
function WSAConnect;	external WINSOCK2_DLL name 'WSAConnect';
function WSACreateEvent;	external WINSOCK2_DLL name 'WSACreateEvent';
function WSADuplicateSocketA;	external WINSOCK2_DLL name 'WSADuplicateSocketA';
function WSADuplicateSocketW;	external WINSOCK2_DLL name 'WSADuplicateSocketW';
function WSAEnumNetworkEvents;	external WINSOCK2_DLL name 'WSAEnumNetworkEvents';
function WSAEnumProtocolsA;	external WINSOCK2_DLL name 'WSAEnumProtocolsA';
function WSAEnumProtocolsW;	external WINSOCK2_DLL name 'WSAEnumProtocolsW';
function WSAEventSelect;	external WINSOCK2_DLL name 'WSAEventSelect';
function WSAGetOverlappedResult;	external WINSOCK2_DLL name 'WSAGetOverlappedResult';
function WSAGetQosByName;	external WINSOCK2_DLL name 'WSAGetQosByName';
function WSAhtonl;	external WINSOCK2_DLL name 'WSAhtonl';
function WSAhtons;	external WINSOCK2_DLL name 'WSAhtons';
function WSAIoctl;	external WINSOCK2_DLL name 'WSAIoctl';
function WSAJoinLeaf;	external WINSOCK2_DLL name 'WSAJoinLeaf';
function WSANtohl;	external WINSOCK2_DLL name 'WSANtohl';
function WSANtohs;	external WINSOCK2_DLL name 'WSANtohs';
function WSARecv;	external WINSOCK2_DLL name 'WSARecv';
function WSARecvDisconnect;	external WINSOCK2_DLL name 'WSARecvDisconnect';
function WSARecvFrom;	external WINSOCK2_DLL name 'WSARecvFrom';
function WSAResetEvent;	external WINSOCK2_DLL name 'WSAResetEvent';
function WSASend;	external WINSOCK2_DLL name 'WSASend';
function WSASendDisconnect;	external WINSOCK2_DLL name 'WSASendDisconnect';
function WSASendTo;	external WINSOCK2_DLL name 'WSASendTo';
function WSASetEvent;	external WINSOCK2_DLL name 'WSASetEvent';
function WSASocketA;	external WINSOCK2_DLL name 'WSASocketA';
function WSASocketW;	external WINSOCK2_DLL name 'WSASocketW';
function WSAWaitForMultipleEvents;	external WINSOCK2_DLL name 'WSAWaitForMultipleEvents';
function WSAAddressToStringA;	external WINSOCK2_DLL name 'WSAAddressToStringA';
function WSAAddressToStringW;	external WINSOCK2_DLL name 'WSAAddressToStringW';
function WSAStringToAddressA;	external WINSOCK2_DLL name 'WSAStringToAddressA';
function WSAStringToAddressW;	external WINSOCK2_DLL name 'WSAStringToAddressW';

{	Registration and Name Resolution API functions }
function WSALookupServiceBeginA;	external WINSOCK2_DLL name 'WSALookupServiceBeginA';
function WSALookupServiceBeginW;	external WINSOCK2_DLL name 'WSALookupServiceBeginW';
function WSALookupServiceNextA;	external WINSOCK2_DLL name 'WSALookupServiceNextA';
function WSALookupServiceNextW;	external WINSOCK2_DLL name 'WSALookupServiceNextW';
function WSALookupServiceEnd;	external WINSOCK2_DLL name 'WSALookupServiceEnd';
function WSAInstallServiceClassA;	external WINSOCK2_DLL name 'WSAInstallServiceClassA';
function WSAInstallServiceClassW;	external WINSOCK2_DLL name 'WSAInstallServiceClassW';
function WSARemoveServiceClass;	external WINSOCK2_DLL name 'WSARemoveServiceClass';
function WSAGetServiceClassInfoA;	external WINSOCK2_DLL name 'WSAGetServiceClassInfoA';
function WSAGetServiceClassInfoW;	external WINSOCK2_DLL name 'WSAGetServiceClassInfoW';
function WSAEnumNameSpaceProvidersA;	external WINSOCK2_DLL name 'WSAEnumNameSpaceProvidersA';
function WSAEnumNameSpaceProvidersW;	external WINSOCK2_DLL name 'WSAEnumNameSpaceProvidersW';
function WSAGetServiceClassNameByClassIdA;	external WINSOCK2_DLL name 'WSAGetServiceClassNameByClassIdA';
function WSAGetServiceClassNameByClassIdW;	external WINSOCK2_DLL name 'WSAGetServiceClassNameByClassIdW';
function WSASetServiceA;	external WINSOCK2_DLL name 'WSASetServiceA';
function WSASetServiceW;	external WINSOCK2_DLL name 'WSASetServiceW';

{$IFDEF UNICODE}
function WSADuplicateSocket;	external WINSOCK2_DLL name 'WSADuplicateSocketW';
function WSAEnumProtocols;	external WINSOCK2_DLL name 'WSAEnumProtocolsW';
function WSASocket;	external WINSOCK2_DLL name 'WSASocketW';
function WSAAddressToString;	external WINSOCK2_DLL name 'WSAAddressToStringW';
function WSAStringToAddress;	external WINSOCK2_DLL name 'WSAStringToAddressW';
function WSALookupServiceBegin;	external WINSOCK2_DLL name 'WSALookupServiceBeginW';
function WSALookupServiceNext;	external WINSOCK2_DLL name 'WSALookupServiceNextW';
function WSAInstallServiceClass;	external WINSOCK2_DLL name 'WSAInstallServiceClassW';
function WSAGetServiceClassInfo;	external WINSOCK2_DLL name 'WSAGetServiceClassInfoW';
function WSAEnumNameSpaceProviders;	external WINSOCK2_DLL name 'WSAEnumNameSpaceProvidersW';
function WSAGetServiceClassNameByClassId;	external WINSOCK2_DLL name 'WSAGetServiceClassNameByClassIdW';
function WSASetService;	external WINSOCK2_DLL name 'WSASetServiceW';
{$ELSE}
function WSADuplicateSocket;	external WINSOCK2_DLL name 'WSADuplicateSocketA';
function WSAEnumProtocols;	external WINSOCK2_DLL name 'WSAEnumProtocolsA';
function WSASocket;	external WINSOCK2_DLL name 'WSASocketA';
function WSAAddressToString;	external WINSOCK2_DLL name 'WSAAddressToStringA';
function WSAStringToAddress;	external WINSOCK2_DLL name 'WSAStringToAddressA';
function WSALookupServiceBegin;	external WINSOCK2_DLL name 'WSALookupServiceBeginA';
function WSALookupServiceNext;	external WINSOCK2_DLL name 'WSALookupServiceNextA';
function WSAInstallServiceClass;	external WINSOCK2_DLL name 'WSAInstallServiceClassA';
function WSAGetServiceClassInfo;	external WINSOCK2_DLL name 'WSAGetServiceClassInfoA';
function WSAEnumNameSpaceProviders;	external WINSOCK2_DLL name 'WSAEnumNameSpaceProvidersA';
function WSAGetServiceClassNameByClassId;	external WINSOCK2_DLL name 'WSAGetServiceClassNameByClassIdA';
function WSASetService;	external WINSOCK2_DLL name 'WSASetServiceA';
{$ENDIF}

function WSAProviderConfigChange;	external WINSOCK2_DLL name 'WSAProviderConfigChange';


function StrLen(const Str: PChar): Cardinal; assembler;
asm
        MOV     EDX,EDI
        MOV     EDI,EAX
        MOV     ECX,0FFFFFFFFH
        XOR     AL,AL
        REPNE   SCASB
        MOV     EAX,0FFFFFFFEH
        SUB     EAX,ECX
        MOV     EDI,EDX
end;

function WSAMakeSyncReply;
begin
  WSAMakeSyncReply:= MakeLong(Buflen, Error);
end;

function WSAMakeSelectReply;
begin
  WSAMakeSelectReply:= MakeLong(Event, Error);
end;

function WSAGetAsyncBuflen;
begin
  WSAGetAsyncBuflen:= LOWORD(Param);
end;

function WSAGetAsyncError;
begin
  WSAGetAsyncError:= HIWORD(Param);
end;

function WSAGetSelectEvent;
begin
  WSAGetSelectEvent:= LOWORD(Param);
end;

function WSAGetSelectError;
begin
  WSAGetSelectError:= HIWORD(Param);
end;

procedure FD_CLR(Socket: TSocket; var FDSet: TFDSet);
var	i: DWORD;
begin
  i := 0;
  while i < FDSet.fd_count do
  begin
    if FDSet.fd_array[i] = Socket then
    begin
      while i < FDSet.fd_count - 1 do
      begin
        FDSet.fd_array[i] := FDSet.fd_array[i+1];
        Inc(i);
      end;
      Dec(FDSet.fd_count);
      Break;
    end;
    Inc(i);
  end;
end;

function FD_ISSET(Socket: TSocket; var FDSet: TFDSet): Boolean;
begin
  Result := __WSAFDIsSet(Socket, FDSet);
end;

procedure FD_SET(Socket: TSocket; var FDSet: TFDSet);
begin
  if FDSet.fd_count < FD_SETSIZE then
  begin
    FDSet.fd_array[FDSet.fd_count] := Socket;
    Inc(FDSet.fd_count);
  end;
end;

procedure FD_ZERO(var FDSet: TFDSet);
begin
  FDSet.fd_count := 0;
end;

//	A macro convenient for setting up NETBIOS SOCKADDRs.
procedure SET_NETBIOS_SOCKADDR( snb : PSOCKADDR_NB; const SnbType : Word; const Name : PChar; const Port : Char );
var len : Integer;
begin
	if snb<>nil then with snb^ do
	begin
		snb_family := AF_NETBIOS;
		snb_type := SnbType;
		len := StrLen(Name);
		if len>=NETBIOS_NAME_LENGTH-1 then System.Move(Name^,snb_name,NETBIOS_NAME_LENGTH-1)
		else
			begin
				if len>0 then System.Move(Name^,snb_name,len);
				FillChar( (PChar(@snb_name)+len)^, NETBIOS_NAME_LENGTH-1-len, ' ' );
			end;
		snb_name[NETBIOS_NAME_LENGTH-1] := Port;
	end;
end;

end.
