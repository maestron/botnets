//	wsnetbs.h
//	Copyright (c) 1994-1999, Microsoft Corp. All rights reserved.
//
//	Windows Sockets include file for NETBIOS.  This file contains all
//	standardized NETBIOS information.  Include this header file after
//	winsock.h.

//	To open a NetBIOS socket, call the socket() function as follows:
//
//		s = socket( AF_NETBIOS, {SOCK_SEQPACKET|SOCK_DGRAM}, -Lana );
//
//	where Lana is the NetBIOS Lana number of interest.  For example, to
//	open a socket for Lana 2, specify -2 as the "protocol" parameter
//	to the socket() function.


//	This is the structure of the SOCKADDR structure for NETBIOS.

const
 NETBIOS_NAME_LENGTH = 16;

type
	SOCKADDR_NB = packed record
		snb_family : Smallint;
		snb_type   : u_short;
		snb_name   : array[0..NETBIOS_NAME_LENGTH-1] of Char;
	end;
  TSockAddr_NB  = SOCKADDR_NB;
  PSOCKADDR_NB  = ^SOCKADDR_NB;
  LPSOCKADDR_NB = ^PSOCKADDR_NB;

//	Bit values for the snb_type field of SOCKADDR_NB.
const
	NETBIOS_UNIQUE_NAME       = $0000;
	NETBIOS_GROUP_NAME        = $0001;
	NETBIOS_TYPE_QUICK_UNIQUE = $0002;
	NETBIOS_TYPE_QUICK_GROUP  = $0003;

//	A macro convenient for setting up NETBIOS SOCKADDRs.
procedure SET_NETBIOS_SOCKADDR( snb : PSOCKADDR_NB; const SnbType : Word; const Name : PChar; const Port : Char );

