{
	WS2TCPIP.H - WinSock2 Extension for TCP/IP protocols

	This file contains TCP/IP specific information for use
	by WinSock2 compatible applications.

	Copyright (c) 1995-1999  Microsoft Corporation

	To provide the backward compatibility, all the TCP/IP
	specific definitions that were included in the WINSOCK.H
	file are now included in WINSOCK2.H file. WS2TCPIP.H
	file includes only the definitions  introduced in the
	"WinSock 2 Protocol-Specific Annex" document.

	Rev 0.3	Nov 13, 1995
	Rev 0.4	Dec 15, 1996
}

// Argument structure for IP_ADD_MEMBERSHIP and IP_DROP_MEMBERSHIP
type
	ip_mreq = packed record
		imr_multiaddr : TInAddr; // IP multicast address of group
		imr_interface : TInAddr; // local IP address of interface
  end;

// TCP/IP specific Ioctl codes
const

	SIO_GET_INTERFACE_LIST    = IOC_OUT or (SizeOf(Longint) shl 16) or (Ord('t') shl 8) or 127;
// New IOCTL with address size independent address array
	SIO_GET_INTERFACE_LIST_EX = IOC_OUT or (SizeOf(Longint) shl 16) or (Ord('t') shl 8) or 126;

// Options for use with [gs]etsockopt at the IP level.
	IP_OPTIONS         =  1; // set/get IP options
	IP_HDRINCL         =  2; // header is included with data
	IP_TOS             =  3; // IP type of service and preced
	IP_TTL             =  4; // IP time to live
	IP_MULTICAST_IF    =  9; // set/get IP multicast i/f
	IP_MULTICAST_TTL   = 10; // set/get IP multicast ttl
	IP_MULTICAST_LOOP  = 11; // set/get IP multicast loopback
	IP_ADD_MEMBERSHIP  = 12; // add an IP group membership
	IP_DROP_MEMBERSHIP = 13; // drop an IP group membership
	IP_DONTFRAGMENT    = 14; // don't fragment IP datagrams

  IP_DEFAULT_MULTICAST_TTL   = 1;    // normally limit m'casts to 1 hop
  IP_DEFAULT_MULTICAST_LOOP  = 1;    // normally hear sends if a member
  IP_MAX_MEMBERSHIPS         = 20;   // per socket; must fit in one mbuf

// Option to use with [gs]etsockopt at the IPPROTO_UDP level
	UDP_NOCHECKSUM     = 1;

// Option to use with [gs]etsockopt at the IPPROTO_TCP level
  TCP_EXPEDITED_1122 = $0002;


// IPv6 definitions
type
	IN_ADDR6 = packed record
		s6_addr : array[0..15] of u_char; // IPv6 address
	end;
  TIn6Addr   = IN_ADDR6;
  PIn6Addr   = ^IN_ADDR6;
  IN6_ADDR   = IN_ADDR6;
  PIN6_ADDR  = ^IN_ADDR6;
  LPIN6_ADDR = ^IN_ADDR6;

// Old IPv6 socket address structure (retained for sockaddr_gen definition below)
	SOCKADDR_IN6_OLD = packed record
		sin6_family   : Smallint;         // AF_INET6
		sin6_port     : u_short;          // Transport level port number
		sin6_flowinfo : u_long;           // IPv6 flow information
		sin6_addr     : IN_ADDR6;         // IPv6 address
	end;

// IPv6 socket address structure, RFC 2553
	SOCKADDR_IN6 = packed record
		sin6_family   : Smallint;         // AF_INET6
		sin6_port     : u_short;          // Transport level port number
		sin6_flowinfo : u_long;           // IPv6 flow information
		sin6_addr     : IN_ADDR6;         // IPv6 address
		sin6_scope_id : u_long;           // set of interfaces for a scope
	end;
  TSockAddrIn6   = SOCKADDR_IN6;
  PSockAddrIn6   = ^SOCKADDR_IN6;
  PSOCKADDR_IN6  = ^SOCKADDR_IN6;
  LPSOCKADDR_IN6 = ^SOCKADDR_IN6;

	sockaddr_gen = packed record
		case Integer of
		1 : ( Address : SOCKADDR; );
		2 : ( AddressIn : SOCKADDR_IN; );
		3 : ( AddressIn6 : SOCKADDR_IN6_OLD; );
	end;

// Structure to keep interface specific information
	INTERFACE_INFO = packed record
		iiFlags            : u_long;       // Interface flags
		iiAddress          : sockaddr_gen; // Interface address
		iiBroadcastAddress : sockaddr_gen; // Broadcast address
		iiNetmask          : sockaddr_gen; // Network mask
	end;
	TINTERFACE_INFO  = INTERFACE_INFO;
	LPINTERFACE_INFO = ^INTERFACE_INFO;

// New structure that does not have dependency on the address size
	INTERFACE_INFO_EX = packed record
		iiFlags            : u_long;         // Interface flags
		iiAddress          : SOCKET_ADDRESS; // Interface address
		iiBroadcastAddress : SOCKET_ADDRESS; // Broadcast address
		iiNetmask : SOCKET_ADDRESS;          // Network mask
	end;
	TINTERFACE_INFO_EX  = INTERFACE_INFO_EX;
	LPINTERFACE_INFO_EX = ^INTERFACE_INFO_EX;

// Possible flags for the  iiFlags - bitmask

const
	IFF_UP           = $00000001;  // Interface is up
	IFF_BROADCAST    = $00000002;  // Broadcast is  supported
	IFF_LOOPBACK     = $00000004;  // this is loopback interface
	IFF_POINTTOPOINT = $00000008;  // this is point-to-point interface
	IFF_MULTICAST    = $00000010;  // multicast is supported

