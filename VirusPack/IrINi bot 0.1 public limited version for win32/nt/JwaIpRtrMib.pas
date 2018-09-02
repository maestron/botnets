{******************************************************************************}
{                                                       	               }
{ Management Information Base API interface Unit for Object Pascal             }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: iprtrmib.h, released August 2001. The original Pascal  }
{ code is: IpRtrMib.pas, released September 2000. The initial developer of the }
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

unit JwaIpRtrMib;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "iprtrmib.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinType;

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Included to get the value of MAX_INTERFACE_NAME_LEN                      //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

// #include <mprapi.h>

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Included to get the necessary constants                                  //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

// #include <ipifcons.h>

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// This is the Id for IP Router Manager.  The Router Manager handles        //
// MIB-II, Forwarding MIB and some enterprise specific information.         //
// Calls made with any other ID are passed on to the corresponding protocol //
// For example, an MprAdminMIBXXX call with a protocol ID of PID_IP and    //
// a routing Id of 0xD will be sent to the IP Router Manager and then       //
// forwarded to OSPF                                                        //
// This lives in the same number space as the protocol Ids of RIP, OSPF     //
// etc, so any change made to it should be done keeping this in mind        //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

const
  MAX_INTERFACE_NAME_LEN = 256; // MPRAPI.H
  {$EXTERNALSYM MAX_INTERFACE_NAME_LEN}
  
  IPRTRMGR_PID = 10000;
  {$EXTERNALSYM IPRTRMGR_PID}

  ANY_SIZE = 1;
  {$EXTERNALSYM ANY_SIZE}

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// The following #defines are the Ids of the MIB variables made accessible  //
// to the user via MprAdminMIBXXX Apis.  It will be noticed that these are  //
// not the same as RFC 1213, since the MprAdminMIBXXX APIs work on rows and //
// groups instead of scalar variables                                       //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

  IF_NUMBER        = 0;
  {$EXTERNALSYM IF_NUMBER}
  IF_TABLE         = IF_NUMBER + 1;
  {$EXTERNALSYM IF_TABLE}
  IF_ROW           = IF_TABLE + 1;
  {$EXTERNALSYM IF_ROW}
  IP_STATS         = IF_ROW + 1;
  {$EXTERNALSYM IP_STATS}
  IP_ADDRTABLE     = IP_STATS + 1;
  {$EXTERNALSYM IP_ADDRTABLE}
  IP_ADDRROW       = IP_ADDRTABLE + 1;
  {$EXTERNALSYM IP_ADDRROW}
  IP_FORWARDNUMBER = IP_ADDRROW + 1;
  {$EXTERNALSYM IP_FORWARDNUMBER}
  IP_FORWARDTABLE  = IP_FORWARDNUMBER + 1;
  {$EXTERNALSYM IP_FORWARDTABLE}
  IP_FORWARDROW    = IP_FORWARDTABLE + 1;
  {$EXTERNALSYM IP_FORWARDROW}
  IP_NETTABLE      = IP_FORWARDROW + 1;
  {$EXTERNALSYM IP_NETTABLE}
  IP_NETROW        = IP_NETTABLE + 1;
  {$EXTERNALSYM IP_NETROW}
  ICMP_STATS       = IP_NETROW + 1;
  {$EXTERNALSYM ICMP_STATS}
  TCP_STATS        = ICMP_STATS + 1;
  {$EXTERNALSYM TCP_STATS}
  TCP_TABLE        = TCP_STATS + 1;
  {$EXTERNALSYM TCP_TABLE}
  TCP_ROW          = TCP_TABLE + 1;
  {$EXTERNALSYM TCP_ROW}
  UDP_STATS        = TCP_ROW + 1;
  {$EXTERNALSYM UDP_STATS}
  UDP_TABLE        = UDP_STATS + 1;
  {$EXTERNALSYM UDP_TABLE}
  UDP_ROW          = UDP_TABLE + 1;
  {$EXTERNALSYM UDP_ROW}
  MCAST_MFE        = UDP_ROW + 1;
  {$EXTERNALSYM MCAST_MFE}
  MCAST_MFE_STATS  = MCAST_MFE + 1;
  {$EXTERNALSYM MCAST_MFE_STATS}
  BEST_IF          = MCAST_MFE_STATS + 1;
  {$EXTERNALSYM BEST_IF}
  BEST_ROUTE       = BEST_IF + 1;
  {$EXTERNALSYM BEST_ROUTE}
  PROXY_ARP        = BEST_ROUTE + 1;
  {$EXTERNALSYM PROXY_ARP}
  MCAST_IF_ENTRY   = PROXY_ARP + 1;
  {$EXTERNALSYM MCAST_IF_ENTRY}
  MCAST_GLOBAL     = MCAST_IF_ENTRY + 1;
  {$EXTERNALSYM MCAST_GLOBAL}
  IF_STATUS        = MCAST_GLOBAL + 1;
  {$EXTERNALSYM IF_STATUS}
  MCAST_BOUNDARY   = IF_STATUS + 1;
  {$EXTERNALSYM MCAST_BOUNDARY}
  MCAST_SCOPE      = MCAST_BOUNDARY + 1;
  {$EXTERNALSYM MCAST_SCOPE}
  DEST_MATCHING    = MCAST_SCOPE + 1;
  {$EXTERNALSYM DEST_MATCHING}
  DEST_LONGER      = DEST_MATCHING + 1;
  {$EXTERNALSYM DEST_LONGER}
  DEST_SHORTER     = DEST_LONGER + 1;
  {$EXTERNALSYM DEST_SHORTER}
  ROUTE_MATCHING   = DEST_SHORTER + 1;
  {$EXTERNALSYM ROUTE_MATCHING}
  ROUTE_LONGER     = ROUTE_MATCHING + 1;
  {$EXTERNALSYM ROUTE_LONGER}
  ROUTE_SHORTER    = ROUTE_LONGER + 1;
  {$EXTERNALSYM ROUTE_SHORTER}
  ROUTE_STATE      = ROUTE_SHORTER + 1;
  {$EXTERNALSYM ROUTE_STATE}
  MCAST_MFE_STATS_EX = ROUTE_STATE + 1;
  {$EXTERNALSYM MCAST_MFE_STATS_EX}
  IP6_STATS          = MCAST_MFE_STATS_EX + 1;
  {$EXTERNALSYM IP6_STATS}
  UDP6_STATS         = IP6_STATS + 1;
  {$EXTERNALSYM UDP6_STATS}
  TCP6_STATS         = UDP6_STATS + 1;
  {$EXTERNALSYM TCP6_STATS}

  NUMBER_OF_EXPORTED_VARIABLES = TCP6_STATS + 1;
  {$EXTERNALSYM NUMBER_OF_EXPORTED_VARIABLES}

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// MIB_OPAQUE_QUERY is the structure filled in by the user to identify a    //
// MIB variable                                                             //
//                                                                          //
//  dwVarId     ID of MIB Variable (One of the Ids #defined above)          //
//  dwVarIndex  Variable sized array containing the indices needed to       //
//              identify a variable. NOTE: Unlike SNMP we dont require that //
//              a scalar variable be indexed by 0                           //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

type
  PMIB_OPAQUE_QUERY = ^MIB_OPAQUE_QUERY;
  {$EXTERNALSYM PMIB_OPAQUE_QUERY}
  _MIB_OPAQUE_QUERY = record
    dwVarId: DWORD;
    rgdwVarIndex: array [0..ANY_SIZE - 1] of DWORD;
  end;
  {$EXTERNALSYM _MIB_OPAQUE_QUERY}
  MIB_OPAQUE_QUERY = _MIB_OPAQUE_QUERY;
  {$EXTERNALSYM MIB_OPAQUE_QUERY}
  TMibOpaqueQuery = MIB_OPAQUE_QUERY;
  PMibOpaqueQuery = PMIB_OPAQUE_QUERY;

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// The following are the structures which are filled in and returned to the //
// user when a query is made, OR  are filled in BY THE USER when a set is   //
// done                                                                     //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

type
  PMIB_IFNUMBER = ^MIB_IFNUMBER;
  {$EXTERNALSYM PMIB_IFNUMBER}
  _MIB_IFNUMBER = record
    dwValue: DWORD;
  end;
  {$EXTERNALSYM _MIB_IFNUMBER}
  MIB_IFNUMBER = _MIB_IFNUMBER;
  {$EXTERNALSYM MIB_IFNUMBER}
  TMibIfnumber = MIB_IFNUMBER;
  PMibIfnumber = PMIB_IFNUMBER;

const
  MAXLEN_IFDESCR  = 256;
  {$EXTERNALSYM MAXLEN_IFDESCR}
  MAXLEN_PHYSADDR = 8;
  {$EXTERNALSYM MAXLEN_PHYSADDR}

type
  PMIB_IFROW = ^MIB_IFROW;
  {$EXTERNALSYM PMIB_IFROW}
  _MIB_IFROW = record
    wszName: array [0..MAX_INTERFACE_NAME_LEN - 1] of WCHAR;
    dwIndex: DWORD;
    dwType: DWORD;
    dwMtu: DWORD;
    dwSpeed: DWORD;
    dwPhysAddrLen: DWORD;
    bPhysAddr: array [0..MAXLEN_PHYSADDR - 1] of BYTE;
    dwAdminStatus: DWORD;
    dwOperStatus: DWORD;
    dwLastChange: DWORD;
    dwInOctets: DWORD;
    dwInUcastPkts: DWORD;
    dwInNUcastPkts: DWORD;
    dwInDiscards: DWORD;
    dwInErrors: DWORD;
    dwInUnknownProtos: DWORD;
    dwOutOctets: DWORD;
    dwOutUcastPkts: DWORD;
    dwOutNUcastPkts: DWORD;
    dwOutDiscards: DWORD;
    dwOutErrors: DWORD;
    dwOutQLen: DWORD;
    dwDescrLen: DWORD;
    bDescr: array[0..MAXLEN_IFDESCR - 1] of BYTE;
  end;
  {$EXTERNALSYM _MIB_IFROW}
  MIB_IFROW = _MIB_IFROW;
  {$EXTERNALSYM MIB_IFROW}
  TMibIfRow = MIB_IFROW;
  PMibIfRow = PMIB_IFROW;

  PMIB_IFTABLE = ^MIB_IFTABLE;
  {$EXTERNALSYM PMIB_IFTABLE}
  _MIB_IFTABLE = record
    dwNumEntries: DWORD;
    table: array [0..ANY_SIZE - 1] of MIB_IFROW;
  end;
  {$EXTERNALSYM _MIB_IFTABLE}
  MIB_IFTABLE = _MIB_IFTABLE;
  {$EXTERNALSYM MIB_IFTABLE}
  TMibIftable = MIB_IFTABLE;
  PMibIftable = PMIB_IFTABLE;

// #define SIZEOF_IFTABLE(X) (FIELD_OFFSET(MIB_IFTABLE,table[0]) + ((X) * sizeof(MIB_IFROW)) + ALIGN_SIZE)

type
  PMibIcmpStats = ^TMibIcmpStats;
  _MIBICMPSTATS = record
    dwMsgs: DWORD;
    dwErrors: DWORD;
    dwDestUnreachs: DWORD;
    dwTimeExcds: DWORD;
    dwParmProbs: DWORD;
    dwSrcQuenchs: DWORD;
    dwRedirects: DWORD;
    dwEchos: DWORD;
    dwEchoReps: DWORD;
    dwTimestamps: DWORD;
    dwTimestampReps: DWORD;
    dwAddrMasks: DWORD;
    dwAddrMaskReps: DWORD;
  end;
  {$EXTERNALSYM _MIBICMPSTATS}
  MIBICMPSTATS = _MIBICMPSTATS;
  {$EXTERNALSYM MIBICMPSTATS}
  TMibIcmpStats = _MIBICMPSTATS;

  _MIBICMPINFO = record
    icmpInStats: MIBICMPSTATS;
    icmpOutStats: MIBICMPSTATS;
  end;
  {$EXTERNALSYM _MIBICMPINFO}
  MIBICMPINFO = _MIBICMPINFO;
  {$EXTERNALSYM MIBICMPINFO}
  PMIBICMPINFO = ^MIBICMPINFO;
  {$EXTERNALSYM PMIBICMPINFO}
  TMibIcmpInfo = MIBICMPINFO;

  PMIB_ICMP = ^MIB_ICMP;
  {$EXTERNALSYM PMIB_ICMP}
  _MIB_ICMP = record
    stats: MIBICMPINFO;
  end;
  {$EXTERNALSYM _MIB_ICMP}
  MIB_ICMP = _MIB_ICMP;
  {$EXTERNALSYM MIB_ICMP}
  TMibIcmp = MIB_ICMP;
  PMibIcmp = PMIB_ICMP;

//
// ICMPv6 Type Values from RFC 2292.
//

const
  ICMP6_DST_UNREACH          = 1;
  {$EXTERNALSYM ICMP6_DST_UNREACH}
  ICMP6_PACKET_TOO_BIG       = 2;
  {$EXTERNALSYM ICMP6_PACKET_TOO_BIG}
  ICMP6_TIME_EXCEEDED        = 3;
  {$EXTERNALSYM ICMP6_TIME_EXCEEDED}
  ICMP6_PARAM_PROB           = 4;
  {$EXTERNALSYM ICMP6_PARAM_PROB}
  ICMP6_ECHO_REQUEST         = 128;
  {$EXTERNALSYM ICMP6_ECHO_REQUEST}
  ICMP6_ECHO_REPLY           = 129;
  {$EXTERNALSYM ICMP6_ECHO_REPLY}
  ICMP6_MEMBERSHIP_QUERY     = 130;
  {$EXTERNALSYM ICMP6_MEMBERSHIP_QUERY}
  ICMP6_MEMBERSHIP_REPORT    = 131;
  {$EXTERNALSYM ICMP6_MEMBERSHIP_REPORT}
  ICMP6_MEMBERSHIP_REDUCTION = 132;
  {$EXTERNALSYM ICMP6_MEMBERSHIP_REDUCTION}
  ND_ROUTER_SOLICIT          = 133;
  {$EXTERNALSYM ND_ROUTER_SOLICIT}
  ND_ROUTER_ADVERT           = 134;
  {$EXTERNALSYM ND_ROUTER_ADVERT}
  ND_NEIGHBOR_SOLICIT        = 135;
  {$EXTERNALSYM ND_NEIGHBOR_SOLICIT}
  ND_NEIGHBOR_ADVERT         = 136;
  {$EXTERNALSYM ND_NEIGHBOR_ADVERT}
  ND_REDIRECT                = 137;
  {$EXTERNALSYM ND_REDIRECT}

type
  ICMP6_TYPE = DWORD;
  {$EXTERNALSYM ICMP6_TYPE}
  PICMP6_TYPE = ^ICMP6_TYPE;
  {$EXTERNALSYM PICMP6_TYPE}
  TIcmp6Type = ICMP6_TYPE;
  PIcmp6Type = PICMP6_TYPE;

//
// There are no RFC-specified defines for ICMPv4 message types, so we try to
// use the ICMP6 values from RFC 2292 modified to be prefixed with ICMP4.
//

const
  ICMP4_ECHO_REPLY        = 0;  // Echo Reply
  {$EXTERNALSYM ICMP4_ECHO_REPLY}
  ICMP4_DST_UNREACH       = 3;  // Destination Unreachable
  {$EXTERNALSYM ICMP4_DST_UNREACH}
  ICMP4_SOURCE_QUENCH     = 4;  // Source Quench
  {$EXTERNALSYM ICMP4_SOURCE_QUENCH}
  ICMP4_REDIRECT          = 5;  // Redirect
  {$EXTERNALSYM ICMP4_REDIRECT}
  ICMP4_ECHO_REQUEST      = 8;  // Echo Request
  {$EXTERNALSYM ICMP4_ECHO_REQUEST}
  ICMP4_ROUTER_ADVERT     = 9;  // Router Advertisement
  {$EXTERNALSYM ICMP4_ROUTER_ADVERT}
  ICMP4_ROUTER_SOLICIT    = 10; // Router Solicitation
  {$EXTERNALSYM ICMP4_ROUTER_SOLICIT}
  ICMP4_TIME_EXCEEDED     = 11; // Time Exceeded
  {$EXTERNALSYM ICMP4_TIME_EXCEEDED}
  ICMP4_PARAM_PROB        = 12; // Parameter Problem
  {$EXTERNALSYM ICMP4_PARAM_PROB}
  ICMP4_TIMESTAMP_REQUEST = 13; // Timestamp Request
  {$EXTERNALSYM ICMP4_TIMESTAMP_REQUEST}
  ICMP4_TIMESTAMP_REPLY   = 14; // Timestamp Reply
  {$EXTERNALSYM ICMP4_TIMESTAMP_REPLY}
  ICMP4_MASK_REQUEST      = 17; // Address Mask Request
  {$EXTERNALSYM ICMP4_MASK_REQUEST}
  ICMP4_MASK_REPLY        = 18; // Address Mask Reply
  {$EXTERNALSYM ICMP4_MASK_REPLY}

type
  ICMP4_TYPE = DWORD;
  {$EXTERNALSYM ICMP4_TYPE}
  PICMP4_TYPE = ^ICMP4_TYPE;
  {$EXTERNALSYM PICMP4_TYPE}
  TIcmp4Type = ICMP4_TYPE;
  PIcmp4Type = PICMP4_TYPE;

  _MIBICMPSTATS_EX = record
    dwMsgs: DWORD;
    dwErrors: DWORD;
    rgdwTypeCount: array [0..255] of DWORD;
  end;
  {$EXTERNALSYM _MIBICMPSTATS_EX}
  MIBICMPSTATS_EX = _MIBICMPSTATS_EX;
  {$EXTERNALSYM MIBICMPSTATS_EX}
  PMIBICMPSTATS_EX = ^MIBICMPSTATS_EX;
  {$EXTERNALSYM PMIBICMPSTATS_EX}
  TMibIcmpStatsEx = MIBICMPSTATS_EX;
  PMibIcmpStatsEx = PMIBICMPSTATS_EX;

  _MIB_ICMP_EX = record
    icmpInStats: MIBICMPSTATS_EX;
    icmpOutStats: MIBICMPSTATS_EX;
  end;
  {$EXTERNALSYM _MIB_ICMP_EX}
  MIB_ICMP_EX = _MIB_ICMP_EX;
  {$EXTERNALSYM MIB_ICMP_EX}
  PMIB_ICMP_EX = ^MIB_ICMP_EX;
  {$EXTERNALSYM PMIB_ICMP_EX}
  TMibIcmpEx = MIB_ICMP_EX;
  PMibIcmpEx = PMIB_ICMP_EX;  

  PMIB_UDPSTATS = ^MIB_UDPSTATS;
  {$EXTERNALSYM PMIB_UDPSTATS}
  _MIB_UDPSTATS = record
    dwInDatagrams: DWORD;
    dwNoPorts: DWORD;
    dwInErrors: DWORD;
    dwOutDatagrams: DWORD;
    dwNumAddrs: DWORD;
  end;
  {$EXTERNALSYM _MIB_UDPSTATS}
  MIB_UDPSTATS = _MIB_UDPSTATS;
  {$EXTERNALSYM MIB_UDPSTATS}
  TMibUdpStats = MIB_UDPSTATS;
  PMibUdpStats = PMIB_UDPSTATS;

  PMIB_UDPROW = ^MIB_UDPROW;
  {$EXTERNALSYM PMIB_UDPROW}
  _MIB_UDPROW = record
    dwLocalAddr: DWORD;
    dwLocalPort: DWORD;
  end;
  {$EXTERNALSYM _MIB_UDPROW}
  MIB_UDPROW = _MIB_UDPROW;
  {$EXTERNALSYM MIB_UDPROW}
  TMibUdpRow = MIB_UDPROW;
  PMibUdpRow = PMIB_UDPROW;

  PMIB_UDPTABLE = ^MIB_UDPTABLE;
  {$EXTERNALSYM PMIB_UDPTABLE}
  _MIB_UDPTABLE = record
    dwNumEntries: DWORD;
    table: array [0..ANY_SIZE - 1] of MIB_UDPROW;
  end;
  {$EXTERNALSYM _MIB_UDPTABLE}
  MIB_UDPTABLE = _MIB_UDPTABLE;
  {$EXTERNALSYM MIB_UDPTABLE}
  TMibUdpTable = MIB_UDPTABLE;
  PMibUdpTable = PMIB_UDPTABLE;

// #define SIZEOF_UDPTABLE(X) (FIELD_OFFSET(MIB_UDPTABLE, table[0]) + ((X) * sizeof(MIB_UDPROW)) + ALIGN_SIZE)

  PMIB_TCPSTATS = ^MIB_TCPSTATS;
  {$EXTERNALSYM PMIB_TCPSTATS}
  _MIB_TCPSTATS = record
    dwRtoAlgorithm: DWORD;
    dwRtoMin: DWORD;
    dwRtoMax: DWORD;
    dwMaxConn: DWORD;
    dwActiveOpens: DWORD;
    dwPassiveOpens: DWORD;
    dwAttemptFails: DWORD;
    dwEstabResets: DWORD;
    dwCurrEstab: DWORD;
    dwInSegs: DWORD;
    dwOutSegs: DWORD;
    dwRetransSegs: DWORD;
    dwInErrs: DWORD;
    dwOutRsts: DWORD;
    dwNumConns: DWORD;
  end;
  {$EXTERNALSYM _MIB_TCPSTATS}
  MIB_TCPSTATS = _MIB_TCPSTATS;
  {$EXTERNALSYM MIB_TCPSTATS}
  TMibTcpStats = MIB_TCPSTATS;
  PMibTcpStats = PMIB_TCPSTATS;

const
  MIB_TCP_RTO_OTHER    = 1;
  {$EXTERNALSYM MIB_TCP_RTO_OTHER}
  MIB_TCP_RTO_CONSTANT = 2;
  {$EXTERNALSYM MIB_TCP_RTO_CONSTANT}
  MIB_TCP_RTO_RSRE     = 3;
  {$EXTERNALSYM MIB_TCP_RTO_RSRE}
  MIB_TCP_RTO_VANJ     = 4;
  {$EXTERNALSYM MIB_TCP_RTO_VANJ}

  MIB_TCP_MAXCONN_DYNAMIC = DWORD(-1);
  {$EXTERNALSYM MIB_TCP_MAXCONN_DYNAMIC}

type
  PMIB_TCPROW = ^MIB_TCPROW;
  {$EXTERNALSYM PMIB_TCPROW}
  _MIB_TCPROW = record
    dwState: DWORD;
    dwLocalAddr: DWORD;
    dwLocalPort: DWORD;
    dwRemoteAddr: DWORD;
    dwRemotePort: DWORD;
  end;
  {$EXTERNALSYM _MIB_TCPROW}
  MIB_TCPROW = _MIB_TCPROW;
  {$EXTERNALSYM MIB_TCPROW}
  TMibTcpRow = MIB_TCPROW;
  PMibTcpRow = PMIB_TCPROW;

const
  MIB_TCP_STATE_CLOSED     = 1;
  {$EXTERNALSYM MIB_TCP_STATE_CLOSED}
  MIB_TCP_STATE_LISTEN     = 2;
  {$EXTERNALSYM MIB_TCP_STATE_LISTEN}
  MIB_TCP_STATE_SYN_SENT   = 3;
  {$EXTERNALSYM MIB_TCP_STATE_SYN_SENT}
  MIB_TCP_STATE_SYN_RCVD   = 4;
  {$EXTERNALSYM MIB_TCP_STATE_SYN_RCVD}
  MIB_TCP_STATE_ESTAB      = 5;
  {$EXTERNALSYM MIB_TCP_STATE_ESTAB}
  MIB_TCP_STATE_FIN_WAIT1  = 6;
  {$EXTERNALSYM MIB_TCP_STATE_FIN_WAIT1}
  MIB_TCP_STATE_FIN_WAIT2  = 7;
  {$EXTERNALSYM MIB_TCP_STATE_FIN_WAIT2}
  MIB_TCP_STATE_CLOSE_WAIT = 8;
  {$EXTERNALSYM MIB_TCP_STATE_CLOSE_WAIT}
  MIB_TCP_STATE_CLOSING    = 9;
  {$EXTERNALSYM MIB_TCP_STATE_CLOSING}
  MIB_TCP_STATE_LAST_ACK   = 10;
  {$EXTERNALSYM MIB_TCP_STATE_LAST_ACK}
  MIB_TCP_STATE_TIME_WAIT  = 11;
  {$EXTERNALSYM MIB_TCP_STATE_TIME_WAIT}
  MIB_TCP_STATE_DELETE_TCB = 12;
  {$EXTERNALSYM MIB_TCP_STATE_DELETE_TCB}

type
  PMIB_TCPTABLE = ^MIB_TCPTABLE;
  {$EXTERNALSYM PMIB_TCPTABLE}
  _MIB_TCPTABLE = record
    dwNumEntries: DWORD;
    table: array [0..ANY_SIZE - 1] of MIB_TCPROW;
  end;
  {$EXTERNALSYM _MIB_TCPTABLE}
  MIB_TCPTABLE = _MIB_TCPTABLE;
  {$EXTERNALSYM MIB_TCPTABLE}
  TMibTcpTable = MIB_TCPTABLE;
  PMibTcpTable = PMIB_TCPTABLE;

// #define SIZEOF_TCPTABLE(X) (FIELD_OFFSET(MIB_TCPTABLE,table[0]) + ((X) * sizeof(MIB_TCPROW)) + ALIGN_SIZE)

const
  MIB_USE_CURRENT_TTL        = DWORD(-1);
  {$EXTERNALSYM MIB_USE_CURRENT_TTL}
  MIB_USE_CURRENT_FORWARDING = DWORD(-1);
  {$EXTERNALSYM MIB_USE_CURRENT_FORWARDING}

type
  PMIB_IPSTATS = ^MIB_IPSTATS;
  {$EXTERNALSYM PMIB_IPSTATS}
  _MIB_IPSTATS = record
    dwForwarding: DWORD;
    dwDefaultTTL: DWORD;
    dwInReceives: DWORD;
    dwInHdrErrors: DWORD;
    dwInAddrErrors: DWORD;
    dwForwDatagrams: DWORD;
    dwInUnknownProtos: DWORD;
    dwInDiscards: DWORD;
    dwInDelivers: DWORD;
    dwOutRequests: DWORD;
    dwRoutingDiscards: DWORD;
    dwOutDiscards: DWORD;
    dwOutNoRoutes: DWORD;
    dwReasmTimeout: DWORD;
    dwReasmReqds: DWORD;
    dwReasmOks: DWORD;
    dwReasmFails: DWORD;
    dwFragOks: DWORD;
    dwFragFails: DWORD;
    dwFragCreates: DWORD;
    dwNumIf: DWORD;
    dwNumAddr: DWORD;
    dwNumRoutes: DWORD;
  end;
  {$EXTERNALSYM _MIB_IPSTATS}
  MIB_IPSTATS = _MIB_IPSTATS;
  {$EXTERNALSYM MIB_IPSTATS}
  TMibIpStats = MIB_IPSTATS;
  PMibIpStats = PMIB_IPSTATS;

const
  MIB_IP_FORWARDING     = 1;
  {$EXTERNALSYM MIB_IP_FORWARDING}
  MIB_IP_NOT_FORWARDING = 2;
  {$EXTERNALSYM MIB_IP_NOT_FORWARDING}

// Note: These addr types have dependency on ipdef.h

  MIB_IPADDR_PRIMARY      = $0001;  // Primary ipaddr
  {$EXTERNALSYM MIB_IPADDR_PRIMARY}
  MIB_IPADDR_DYNAMIC      = $0004;  // Dynamic ipaddr
  {$EXTERNALSYM MIB_IPADDR_DYNAMIC}
  MIB_IPADDR_DISCONNECTED = $0008;  // Address is on disconnected interface
  {$EXTERNALSYM MIB_IPADDR_DISCONNECTED}
  MIB_IPADDR_DELETED      = $0040;  // Address being deleted
  {$EXTERNALSYM MIB_IPADDR_DELETED}
  MIB_IPADDR_TRANSIENT    = $0080;  // Transient address
  {$EXTERNALSYM MIB_IPADDR_TRANSIENT}

type
  PMIB_IPADDRROW = ^MIB_IPADDRROW;
  {$EXTERNALSYM PMIB_IPADDRROW}
  _MIB_IPADDRROW = record
    dwAddr: DWORD;
    dwIndex: DWORD;
    dwMask: DWORD;
    dwBCastAddr: DWORD;
    dwReasmSize: DWORD;
    unused1: Word;
    wType: Word;
  end;
  {$EXTERNALSYM _MIB_IPADDRROW}
  MIB_IPADDRROW = _MIB_IPADDRROW;
  {$EXTERNALSYM MIB_IPADDRROW}
  TMibIpAddrRow = MIB_IPADDRROW;
  PMibIpAddrRow = PMIB_IPADDRROW;

  PMIB_IPADDRTABLE = ^MIB_IPADDRTABLE;
  {$EXTERNALSYM PMIB_IPADDRTABLE}
  _MIB_IPADDRTABLE = record
    dwNumEntries: DWORD;
    table: array [0..ANY_SIZE - 1] of MIB_IPADDRROW;
  end;
  {$EXTERNALSYM _MIB_IPADDRTABLE}
  MIB_IPADDRTABLE = _MIB_IPADDRTABLE;
  {$EXTERNALSYM MIB_IPADDRTABLE}
  TMibIpAddrTable = _MIB_IPADDRTABLE;
  PMibIpAddrTable = PMIB_IPADDRTABLE;

// #define SIZEOF_IPADDRTABLE(X) (FIELD_OFFSET(MIB_IPADDRTABLE,table[0]) + ((X) * sizeof(MIB_IPADDRROW)) + ALIGN_SIZE)

type
  PMIB_IPFORWARDNUMBER = ^MIB_IPFORWARDNUMBER;
  {$EXTERNALSYM PMIB_IPFORWARDNUMBER}
  _MIB_IPFORWARDNUMBER = record
    dwValue: DWORD;
  end;
  {$EXTERNALSYM _MIB_IPFORWARDNUMBER}
  MIB_IPFORWARDNUMBER = _MIB_IPFORWARDNUMBER;
  {$EXTERNALSYM MIB_IPFORWARDNUMBER}
  TMibIpForwardNumber = MIB_IPFORWARDNUMBER;
  PMibIpForwardNumber = PMIB_IPFORWARDNUMBER;

  PMIB_IPFORWARDROW = ^MIB_IPFORWARDROW;
  {$EXTERNALSYM PMIB_IPFORWARDROW}
  _MIB_IPFORWARDROW = record
    dwForwardDest: DWORD;
    dwForwardMask: DWORD;
    dwForwardPolicy: DWORD;
    dwForwardNextHop: DWORD;
    dwForwardIfIndex: DWORD;
    dwForwardType: DWORD;
    dwForwardProto: DWORD;
    dwForwardAge: DWORD;
    dwForwardNextHopAS: DWORD;
    dwForwardMetric1: DWORD;
    dwForwardMetric2: DWORD;
    dwForwardMetric3: DWORD;
    dwForwardMetric4: DWORD;
    dwForwardMetric5: DWORD;
  end;
  {$EXTERNALSYM _MIB_IPFORWARDROW}
  MIB_IPFORWARDROW = _MIB_IPFORWARDROW;
  {$EXTERNALSYM MIB_IPFORWARDROW}
  TMibIpForwardRow = MIB_IPFORWARDROW;
  PMibIpForwardRow = PMIB_IPFORWARDROW;

const
  MIB_IPROUTE_TYPE_OTHER    = 1;
  {$EXTERNALSYM MIB_IPROUTE_TYPE_OTHER}
  MIB_IPROUTE_TYPE_INVALID  = 2;
  {$EXTERNALSYM MIB_IPROUTE_TYPE_INVALID}
  MIB_IPROUTE_TYPE_DIRECT   = 3;
  {$EXTERNALSYM MIB_IPROUTE_TYPE_DIRECT}
  MIB_IPROUTE_TYPE_INDIRECT = 4;
  {$EXTERNALSYM MIB_IPROUTE_TYPE_INDIRECT}

  MIB_IPROUTE_METRIC_UNUSED = DWORD(-1);
  {$EXTERNALSYM MIB_IPROUTE_METRIC_UNUSED}

//
// THESE MUST MATCH the ids in routprot.h
//

const
  MIB_IPPROTO_OTHER   = 1;
  {$EXTERNALSYM MIB_IPPROTO_OTHER}
  MIB_IPPROTO_LOCAL   = 2;
  {$EXTERNALSYM MIB_IPPROTO_LOCAL}
  MIB_IPPROTO_NETMGMT = 3;
  {$EXTERNALSYM MIB_IPPROTO_NETMGMT}
  MIB_IPPROTO_ICMP    = 4;
  {$EXTERNALSYM MIB_IPPROTO_ICMP}
  MIB_IPPROTO_EGP     = 5;
  {$EXTERNALSYM MIB_IPPROTO_EGP}
  MIB_IPPROTO_GGP     = 6;
  {$EXTERNALSYM MIB_IPPROTO_GGP}
  MIB_IPPROTO_HELLO   = 7;
  {$EXTERNALSYM MIB_IPPROTO_HELLO}
  MIB_IPPROTO_RIP     = 8;
  {$EXTERNALSYM MIB_IPPROTO_RIP}
  MIB_IPPROTO_IS_IS   = 9;
  {$EXTERNALSYM MIB_IPPROTO_IS_IS}
  MIB_IPPROTO_ES_IS   = 10;
  {$EXTERNALSYM MIB_IPPROTO_ES_IS}
  MIB_IPPROTO_CISCO   = 11;
  {$EXTERNALSYM MIB_IPPROTO_CISCO}
  MIB_IPPROTO_BBN     = 12;
  {$EXTERNALSYM MIB_IPPROTO_BBN}
  MIB_IPPROTO_OSPF    = 13;
  {$EXTERNALSYM MIB_IPPROTO_OSPF}
  MIB_IPPROTO_BGP     = 14;
  {$EXTERNALSYM MIB_IPPROTO_BGP}

  MIB_IPPROTO_NT_AUTOSTATIC     = 10002;
  {$EXTERNALSYM MIB_IPPROTO_NT_AUTOSTATIC}
  MIB_IPPROTO_NT_STATIC         = 10006;
  {$EXTERNALSYM MIB_IPPROTO_NT_STATIC}
  MIB_IPPROTO_NT_STATIC_NON_DOD = 10007;
  {$EXTERNALSYM MIB_IPPROTO_NT_STATIC_NON_DOD}

type
  PMIB_IPFORWARDTABLE = ^MIB_IPFORWARDTABLE;
  {$EXTERNALSYM PMIB_IPFORWARDTABLE}
  _MIB_IPFORWARDTABLE = record
    dwNumEntries: DWORD;
    table: array [0..ANY_SIZE - 1] of MIB_IPFORWARDROW;
  end;
  {$EXTERNALSYM _MIB_IPFORWARDTABLE}
  MIB_IPFORWARDTABLE = _MIB_IPFORWARDTABLE;
  {$EXTERNALSYM MIB_IPFORWARDTABLE}
  TMibIpForwardTable = MIB_IPFORWARDTABLE;
  PMibIpForwardTable = PMIB_IPFORWARDTABLE;

// #define SIZEOF_IPFORWARDTABLE(X) (FIELD_OFFSET(MIB_IPFORWARDTABLE,table[0]) + ((X) * sizeof(MIB_IPFORWARDROW)) + ALIGN_SIZE)

type
  PMIB_IPNETROW = ^MIB_IPNETROW;
  {$EXTERNALSYM PMIB_IPNETROW}
  _MIB_IPNETROW = record
    dwIndex: DWORD;
    dwPhysAddrLen: DWORD;
    bPhysAddr: array [0..MAXLEN_PHYSADDR - 1] of BYTE;
    dwAddr: DWORD;
    dwType: DWORD;
  end;
  {$EXTERNALSYM _MIB_IPNETROW}
  MIB_IPNETROW = _MIB_IPNETROW;
  {$EXTERNALSYM MIB_IPNETROW}
  TMibIpNetRow = MIB_IPNETROW;
  PMibIpNetRow = PMIB_IPNETROW;

const
  MIB_IPNET_TYPE_OTHER   = 1;
  {$EXTERNALSYM MIB_IPNET_TYPE_OTHER}
  MIB_IPNET_TYPE_INVALID = 2;
  {$EXTERNALSYM MIB_IPNET_TYPE_INVALID}
  MIB_IPNET_TYPE_DYNAMIC = 3;
  {$EXTERNALSYM MIB_IPNET_TYPE_DYNAMIC}
  MIB_IPNET_TYPE_STATIC  = 4;
  {$EXTERNALSYM MIB_IPNET_TYPE_STATIC}

type
  PMIB_IPNETTABLE = ^MIB_IPNETTABLE;
  {$EXTERNALSYM PMIB_IPNETTABLE}
  _MIB_IPNETTABLE = record
    dwNumEntries: DWORD;
    table: array [0..ANY_SIZE - 1] of MIB_IPNETROW;
  end;
  {$EXTERNALSYM _MIB_IPNETTABLE}
  MIB_IPNETTABLE = _MIB_IPNETTABLE;
  {$EXTERNALSYM MIB_IPNETTABLE}
  TMibIpNetTable = MIB_IPNETTABLE;
  PMibIpNetTable = PMIB_IPNETTABLE;

// #define SIZEOF_IPNETTABLE(X) (FIELD_OFFSET(MIB_IPNETTABLE, table[0]) + ((X) * sizeof(MIB_IPNETROW)) + ALIGN_SIZE)

type
  PMIB_IPMCAST_OIF = ^MIB_IPMCAST_OIF;
  {$EXTERNALSYM PMIB_IPMCAST_OIF}
  _MIB_IPMCAST_OIF = record
    dwOutIfIndex: DWORD;
    dwNextHopAddr: DWORD;
    dwReserved: DWORD;
    dwReserved1: DWORD;
  end;
  {$EXTERNALSYM _MIB_IPMCAST_OIF}
  MIB_IPMCAST_OIF = _MIB_IPMCAST_OIF;
  {$EXTERNALSYM MIB_IPMCAST_OIF}
  TMibIpmCastOif = MIB_IPMCAST_OIF;
  PMibIpmCastOif = PMIB_IPMCAST_OIF;

  PMIB_IPMCAST_MFE = ^MIB_IPMCAST_MFE;
  {$EXTERNALSYM PMIB_IPMCAST_MFE}
  _MIB_IPMCAST_MFE = record
    dwGroup: DWORD;
    dwSource: DWORD;
    dwSrcMask: DWORD;
    dwUpStrmNgbr: DWORD;
    dwInIfIndex: DWORD;
    dwInIfProtocol: DWORD;
    dwRouteProtocol: DWORD;
    dwRouteNetwork: DWORD;
    dwRouteMask: DWORD;
    ulUpTime: ULONG;
    ulExpiryTime: ULONG;
    ulTimeOut: ULONG;
    ulNumOutIf: ULONG;
    fFlags: DWORD;
    dwReserved: DWORD;
    rgmioOutInfo: array [0..ANY_SIZE - 1] of MIB_IPMCAST_OIF;
  end;
  {$EXTERNALSYM _MIB_IPMCAST_MFE}
  MIB_IPMCAST_MFE = _MIB_IPMCAST_MFE;
  {$EXTERNALSYM MIB_IPMCAST_MFE}
  TMibIpmCastMfe = MIB_IPMCAST_MFE;
  PMibIpmCastMfe = PMIB_IPMCAST_MFE;

  PMIB_MFE_TABLE = ^MIB_MFE_TABLE;
  {$EXTERNALSYM PMIB_MFE_TABLE}
  _MIB_MFE_TABLE = record
    dwNumEntries: DWORD;
    table: array [0..ANY_SIZE - 1] of MIB_IPMCAST_MFE;
  end;
  {$EXTERNALSYM _MIB_MFE_TABLE}
  MIB_MFE_TABLE = _MIB_MFE_TABLE;
  {$EXTERNALSYM MIB_MFE_TABLE}
  TMibMfeTable = MIB_MFE_TABLE;
  PMibMfeTable = PMIB_MFE_TABLE;


// #define SIZEOF_BASIC_MIB_MFE          \
//    (ULONG)(FIELD_OFFSET(MIB_IPMCAST_MFE, rgmioOutInfo[0]))

// #define SIZEOF_MIB_MFE(X)             \
//    (SIZEOF_BASIC_MIB_MFE + ((X) * sizeof(MIB_IPMCAST_OIF)))

type
  PMIB_IPMCAST_OIF_STATS = ^MIB_IPMCAST_OIF_STATS;
  {$EXTERNALSYM PMIB_IPMCAST_OIF_STATS}
  _MIB_IPMCAST_OIF_STATS = record
    dwOutIfIndex: DWORD;
    dwNextHopAddr: DWORD;
    dwDialContext: DWORD;
    ulTtlTooLow: ULONG;
    ulFragNeeded: ULONG;
    ulOutPackets: ULONG;
    ulOutDiscards: ULONG;
  end;
  {$EXTERNALSYM _MIB_IPMCAST_OIF_STATS}
  MIB_IPMCAST_OIF_STATS = _MIB_IPMCAST_OIF_STATS;
  {$EXTERNALSYM MIB_IPMCAST_OIF_STATS}
  TMibIpmCastOifStats = MIB_IPMCAST_OIF_STATS;
  PMibIpmCastOifStats = PMIB_IPMCAST_OIF_STATS;

  PMIB_IPMCAST_MFE_STATS = ^MIB_IPMCAST_MFE_STATS;
  {$EXTERNALSYM PMIB_IPMCAST_MFE_STATS}
  _MIB_IPMCAST_MFE_STATS = record
    dwGroup: DWORD;
    dwSource: DWORD;
    dwSrcMask: DWORD;
    dwUpStrmNgbr: DWORD;
    dwInIfIndex: DWORD;
    dwInIfProtocol: DWORD;
    dwRouteProtocol: DWORD;
    dwRouteNetwork: DWORD;
    dwRouteMask: DWORD;
    ulUpTime: ULONG;
    ulExpiryTime: ULONG;
    ulNumOutIf: ULONG;
    ulInPkts: ULONG;
    ulInOctets: ULONG;
    ulPktsDifferentIf: ULONG;
    ulQueueOverflow: ULONG;
    rgmiosOutStats: array [0..ANY_SIZE - 1] of MIB_IPMCAST_OIF_STATS;
  end;
  {$EXTERNALSYM _MIB_IPMCAST_MFE_STATS}
  MIB_IPMCAST_MFE_STATS = _MIB_IPMCAST_MFE_STATS;
  {$EXTERNALSYM MIB_IPMCAST_MFE_STATS}
  TMibIpmCastMfeStats = MIB_IPMCAST_MFE_STATS;
  PMibIpmCastMfeStats = PMIB_IPMCAST_MFE_STATS;

  PMIB_MFE_STATS_TABLE = ^MIB_MFE_STATS_TABLE;
  {$EXTERNALSYM PMIB_MFE_STATS_TABLE}
  _MIB_MFE_STATS_TABLE = record
    dwNumEntries: DWORD;
    table: array [0..ANY_SIZE - 1] of MIB_IPMCAST_MFE_STATS;
  end;
  {$EXTERNALSYM _MIB_MFE_STATS_TABLE}
  MIB_MFE_STATS_TABLE = _MIB_MFE_STATS_TABLE;
  {$EXTERNALSYM MIB_MFE_STATS_TABLE}
  TMibMfeStatsTable = MIB_MFE_STATS_TABLE;
  PMibMfeStatsTable = PMIB_MFE_STATS_TABLE;

// #define SIZEOF_BASIC_MIB_MFE_STATS    \
//    (ULONG)(FIELD_OFFSET(MIB_IPMCAST_MFE_STATS, rgmiosOutStats[0]))

// #define SIZEOF_MIB_MFE_STATS(X)       \
//    (SIZEOF_BASIC_MIB_MFE_STATS + ((X) * sizeof(MIB_IPMCAST_OIF_STATS)))

type
  _MIB_IPMCAST_MFE_STATS_EX = record
    dwGroup: DWORD;
    dwSource: DWORD;
    dwSrcMask: DWORD;
    dwUpStrmNgbr: DWORD;
    dwInIfIndex: DWORD;
    dwInIfProtocol: DWORD;
    dwRouteProtocol: DWORD;
    dwRouteNetwork: DWORD;
    dwRouteMask: DWORD;
    ulUpTime: ULONG;
    ulExpiryTime: ULONG;
    ulNumOutIf: ULONG;
    ulInPkts: ULONG;
    ulInOctets: ULONG;
    ulPktsDifferentIf: ULONG;
    ulQueueOverflow: ULONG;
    ulUninitMfe: ULONG;
    ulNegativeMfe: ULONG;
    ulInDiscards: ULONG;
    ulInHdrErrors: ULONG;
    ulTotalOutPackets: ULONG;

    rgmiosOutStats: array [0..ANY_SIZE - 1] of MIB_IPMCAST_OIF_STATS;
  end;
  {$EXTERNALSYM _MIB_IPMCAST_MFE_STATS_EX}
  MIB_IPMCAST_MFE_STATS_EX = _MIB_IPMCAST_MFE_STATS_EX;
  {$EXTERNALSYM MIB_IPMCAST_MFE_STATS_EX}
  PMIB_IPMCAST_MFE_STATS_EX = ^MIB_IPMCAST_MFE_STATS_EX;
  {$EXTERNALSYM PMIB_IPMCAST_MFE_STATS_EX}
  TMibIpMCastMfeStatsEx = MIB_IPMCAST_MFE_STATS_EX;
  PMibIpMCastMfeStatsEx = PMIB_IPMCAST_MFE_STATS_EX;  

  _MIB_MFE_STATS_TABLE_EX = record
    dwNumEntries: DWORD;
    table: array [0..ANY_SIZE - 1] of MIB_IPMCAST_MFE_STATS_EX;
  end;
  {$EXTERNALSYM _MIB_MFE_STATS_TABLE_EX}
  MIB_MFE_STATS_TABLE_EX = _MIB_MFE_STATS_TABLE_EX;
  {$EXTERNALSYM MIB_MFE_STATS_TABLE_EX}
  PMIB_MFE_STATS_TABLE_EX = ^MIB_MFE_STATS_TABLE_EX;
  {$EXTERNALSYM PMIB_MFE_STATS_TABLE_EX}
  TMibMfeStatsTableEx = MIB_MFE_STATS_TABLE_EX;
  PMibMfeStatsTableEx = PMIB_MFE_STATS_TABLE_EX;

//#define SIZEOF_BASIC_MIB_MFE_STATS_EX    \
//    (ULONG)(FIELD_OFFSET(MIB_IPMCAST_MFE_STATS_EX, rgmiosOutStats[0]))

//#define SIZEOF_MIB_MFE_STATS_EX(X)       \
//    (SIZEOF_BASIC_MIB_MFE_STATS_EX + ((X) * sizeof(MIB_IPMCAST_OIF_STATS)))

type
  PMIB_IPMCAST_GLOBAL = ^MIB_IPMCAST_GLOBAL;
  {$EXTERNALSYM PMIB_IPMCAST_GLOBAL}
  _MIB_IPMCAST_GLOBAL = record
    dwEnable: DWORD;
  end;
  {$EXTERNALSYM _MIB_IPMCAST_GLOBAL}
  MIB_IPMCAST_GLOBAL = _MIB_IPMCAST_GLOBAL;
  {$EXTERNALSYM MIB_IPMCAST_GLOBAL}
  TMibIpmCastGlobal = MIB_IPMCAST_GLOBAL;
  PMibIpmCastGlobal = PMIB_IPMCAST_GLOBAL;

  PMIB_IPMCAST_IF_ENTRY = ^MIB_IPMCAST_IF_ENTRY;
  {$EXTERNALSYM PMIB_IPMCAST_IF_ENTRY}
  _MIB_IPMCAST_IF_ENTRY = record
    dwIfIndex: DWORD;
    dwTtl: DWORD;
    dwProtocol: DWORD;
    dwRateLimit: DWORD;
    ulInMcastOctets: ULONG;
    ulOutMcastOctets: ULONG;
  end;
  {$EXTERNALSYM _MIB_IPMCAST_IF_ENTRY}
  MIB_IPMCAST_IF_ENTRY = _MIB_IPMCAST_IF_ENTRY;
  {$EXTERNALSYM MIB_IPMCAST_IF_ENTRY}
  TMibIpmCastIfEntry = MIB_IPMCAST_IF_ENTRY;
  PMibIpmCastIfEntry = PMIB_IPMCAST_IF_ENTRY;

  PMIB_IPMCAST_IF_TABLE = ^MIB_IPMCAST_IF_TABLE;
  {$EXTERNALSYM PMIB_IPMCAST_IF_TABLE}
  _MIB_IPMCAST_IF_TABLE = record
    dwNumEntries: DWORD;
    table: array [0..ANY_SIZE - 1] of MIB_IPMCAST_IF_ENTRY;
  end;
  {$EXTERNALSYM _MIB_IPMCAST_IF_TABLE}
  MIB_IPMCAST_IF_TABLE = _MIB_IPMCAST_IF_TABLE;
  {$EXTERNALSYM MIB_IPMCAST_IF_TABLE}
  TMibIpmCastIfTable = MIB_IPMCAST_IF_TABLE;
  PMibIpmCastIfTable = PMIB_IPMCAST_IF_TABLE;

// #define SIZEOF_MCAST_IF_TABLE(X) (FIELD_OFFSET(MIB_IPMCAST_IF_TABLE,table[0]) + ((X) * sizeof(MIB_IPMCAST_IF_ENTRY)) + ALIGN_SIZE)

type
  PMIB_IPMCAST_BOUNDARY = ^MIB_IPMCAST_BOUNDARY;
  {$EXTERNALSYM PMIB_IPMCAST_BOUNDARY}
  _MIB_IPMCAST_BOUNDARY = record
    dwIfIndex: DWORD;
    dwGroupAddress: DWORD;
    dwGroupMask: DWORD;
    dwStatus: DWORD;
  end;
  {$EXTERNALSYM _MIB_IPMCAST_BOUNDARY}
  MIB_IPMCAST_BOUNDARY = _MIB_IPMCAST_BOUNDARY;
  {$EXTERNALSYM MIB_IPMCAST_BOUNDARY}
  TMibIpmCastBoundary = MIB_IPMCAST_BOUNDARY;
  PMibIpmCastBoundary = PMIB_IPMCAST_BOUNDARY;

  PMIB_IPMCAST_BOUNDARY_TABLE = ^MIB_IPMCAST_BOUNDARY_TABLE;
  {$EXTERNALSYM PMIB_IPMCAST_BOUNDARY_TABLE}
  _MIB_IPMCAST_BOUNDARY_TABLE = record
    dwNumEntries: DWORD;
    table: array [0..ANY_SIZE - 1] of MIB_IPMCAST_BOUNDARY;
  end;
  {$EXTERNALSYM _MIB_IPMCAST_BOUNDARY_TABLE}
  MIB_IPMCAST_BOUNDARY_TABLE = _MIB_IPMCAST_BOUNDARY_TABLE;
  {$EXTERNALSYM MIB_IPMCAST_BOUNDARY_TABLE}
  TMibIpmCastBoundaryTable = MIB_IPMCAST_BOUNDARY_TABLE;
  PMibIpmCastBoundaryTable = PMIB_IPMCAST_BOUNDARY_TABLE;

// #define SIZEOF_BOUNDARY_TABLE(X) (FIELD_OFFSET(MIB_IPMCAST_BOUNDARY_TABLE,table[0]) + ((X) * sizeof(MIB_IPMCAST_BOUNDARY)) + ALIGN_SIZE)

type
  PMIB_BOUNDARYROW = ^MIB_BOUNDARYROW;
  {$EXTERNALSYM PMIB_BOUNDARYROW}
  MIB_BOUNDARYROW = record
    dwGroupAddress: DWORD;
    dwGroupMask: DWORD;
  end;
  {$EXTERNALSYM MIB_BOUNDARYROW}
  TMibBoundaryRow = MIB_BOUNDARYROW;
  PMibBoundaryRow = PMIB_BOUNDARYROW;

// Structure matching what goes in the registry in a block of type
// IP_MCAST_LIMIT_INFO.  This contains the fields of
// MIB_IPMCAST_IF_ENTRY which are configurable.

  PMIB_MCAST_LIMIT_ROW = ^MIB_MCAST_LIMIT_ROW;
  {$EXTERNALSYM PMIB_MCAST_LIMIT_ROW}
  MIB_MCAST_LIMIT_ROW = record
    dwTtl: DWORD;
    dwRateLimit: DWORD;
  end;
  {$EXTERNALSYM MIB_MCAST_LIMIT_ROW}
  TMibMcastLimitRow = MIB_MCAST_LIMIT_ROW;
  PMibMcastLimitRow = PMIB_MCAST_LIMIT_ROW;

const
  MAX_SCOPE_NAME_LEN = 255;
  {$EXTERNALSYM MAX_SCOPE_NAME_LEN}

//
// Scope names are unicode.  SNMP and MZAP use UTF-8 encoding.
//

type
  SN_CHAR = WCHAR;
  {$EXTERNALSYM SN_CHAR}
  SCOPE_NAME_BUFFER = array [0..MAX_SCOPE_NAME_LEN] of SN_CHAR;
  {$EXTERNALSYM SCOPE_NAME_BUFFER}
  SCOPE_NAME = ^SN_CHAR;
  {$EXTERNALSYM SCOPE_NAME}

  PMIB_IPMCAST_SCOPE = ^MIB_IPMCAST_SCOPE;
  {$EXTERNALSYM PMIB_IPMCAST_SCOPE}
  _MIB_IPMCAST_SCOPE = record
    dwGroupAddress: DWORD;
    dwGroupMask: DWORD;
    snNameBuffer: SCOPE_NAME_BUFFER;
    dwStatus: DWORD;
  end;
  {$EXTERNALSYM _MIB_IPMCAST_SCOPE}
  MIB_IPMCAST_SCOPE = _MIB_IPMCAST_SCOPE;
  {$EXTERNALSYM MIB_IPMCAST_SCOPE}
  TMibIpmCastScope = MIB_IPMCAST_SCOPE;
  PMibIpmCastScope = PMIB_IPMCAST_SCOPE;

  PMIB_IPDESTROW = ^MIB_IPDESTROW;
  {$EXTERNALSYM PMIB_IPDESTROW}
  _MIB_IPDESTROW = record
    ForwardRow: MIB_IPFORWARDROW;
    dwForwardPreference: DWORD;
    dwForwardViewSet: DWORD;
  end;
  {$EXTERNALSYM _MIB_IPDESTROW}
  MIB_IPDESTROW = _MIB_IPDESTROW;
  {$EXTERNALSYM MIB_IPDESTROW}
  TMibIpDestRow = MIB_IPDESTROW;
  PMibIpDestRow = PMIB_IPDESTROW;

  PMIB_IPDESTTABLE = ^MIB_IPDESTTABLE;
  {$EXTERNALSYM PMIB_IPDESTTABLE}
  _MIB_IPDESTTABLE = record
    dwNumEntries: DWORD;
    table: array [0..ANY_SIZE - 1] of MIB_IPDESTROW;
  end;
  {$EXTERNALSYM _MIB_IPDESTTABLE}
  MIB_IPDESTTABLE = _MIB_IPDESTTABLE;
  {$EXTERNALSYM MIB_IPDESTTABLE}
  TMibIpDestTable = MIB_IPDESTTABLE;
  PMibIpDestTable = PMIB_IPDESTTABLE;

  PMIB_BEST_IF = ^MIB_BEST_IF;
  {$EXTERNALSYM PMIB_BEST_IF}
  _MIB_BEST_IF = record
    dwDestAddr: DWORD;
    dwIfIndex: DWORD;
  end;
  {$EXTERNALSYM _MIB_BEST_IF}
  MIB_BEST_IF = _MIB_BEST_IF;
  {$EXTERNALSYM MIB_BEST_IF}
  TMibBestIf = MIB_BEST_IF;
  PMibBestIf = PMIB_BEST_IF;

  PMIB_PROXYARP = ^MIB_PROXYARP;
  {$EXTERNALSYM PMIB_PROXYARP}
  _MIB_PROXYARP = record
    dwAddress: DWORD;
    dwMask: DWORD;
    dwIfIndex: DWORD;
  end;
  {$EXTERNALSYM _MIB_PROXYARP}
  MIB_PROXYARP = _MIB_PROXYARP;
  {$EXTERNALSYM MIB_PROXYARP}
  TMibProxyArp = MIB_PROXYARP;
  PMibProxyArp = PMIB_PROXYARP;

  PMIB_IFSTATUS = ^MIB_IFSTATUS;
  {$EXTERNALSYM PMIB_IFSTATUS}
  _MIB_IFSTATUS = record
    dwIfIndex: DWORD;
    dwAdminStatus: DWORD;
    dwOperationalStatus: DWORD;
    bMHbeatActive: BOOL;
    bMHbeatAlive: BOOL;
  end;
  {$EXTERNALSYM _MIB_IFSTATUS}
  MIB_IFSTATUS = _MIB_IFSTATUS;
  {$EXTERNALSYM MIB_IFSTATUS}
  TMibIfStatus = MIB_IFSTATUS;
  PMibIfStatus = PMIB_IFSTATUS;

  PMIB_ROUTESTATE = ^MIB_ROUTESTATE;
  {$EXTERNALSYM PMIB_ROUTESTATE}
  _MIB_ROUTESTATE = record
    bRoutesSetToStack: BOOL;
  end;
  {$EXTERNALSYM _MIB_ROUTESTATE}
  MIB_ROUTESTATE = _MIB_ROUTESTATE;
  {$EXTERNALSYM MIB_ROUTESTATE}
  TMibRouteState = MIB_ROUTESTATE;
  PMibRouteState = PMIB_ROUTESTATE;

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// All the info passed to (SET/CREATE) and from (GET/GETNEXT/GETFIRST)      //
// IP Router Manager is encapsulated in the following "discriminated"       //
// union.  To pass, say MIB_IFROW, use the following code                   //
//                                                                          //
//  PMIB_OPAQUE_INFO    pInfo;                                              //
//  PMIB_IFROW          pIfRow;                                             //
//  DWORD rgdwBuff[(MAX_MIB_OFFSET + sizeof(MIB_IFROW))/sizeof(DWORD) + 1]; //
//                                                                          //
//  pInfo   = (PMIB_OPAQUE_INFO)rgdwBuffer;                                 //
//  pIfRow  = (MIB_IFROW *)(pInfo->rgbyData);                               //
//                                                                          //
//  This can also be accomplished by using the following macro              //
//                                                                          //
//  DEFINE_MIB_BUFFER(pInfo,MIB_IFROW, pIfRow);                             //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

type
  PMibOpaqueInfo = ^TMibOpaqueInfo;
  _MIB_OPAQUE_INFO = record
    dwId: DWORD;
    case Integer of
      0: (ullAlign: Int64); // ULONGLONG (unsigned!)
      1: (rgbyData: array [0..0] of BYTE);
  end;
  {$EXTERNALSYM _MIB_OPAQUE_INFO}
  MIB_OPAQUE_INFO = _MIB_OPAQUE_INFO;
  {$EXTERNALSYM MIB_OPAQUE_INFO}
  TMibOpaqueInfo = MIB_OPAQUE_INFO;

const
  MAX_MIB_OFFSET = 8;
  {$EXTERNALSYM MAX_MIB_OFFSET}

// #define MIB_INFO_SIZE(S)    (MAX_MIB_OFFSET + sizeof(S))

// #define MIB_INFO_SIZE_IN_DWORDS(S)      \
//    ((MIB_INFO_SIZE(S))/sizeof(DWORD) + 1)

// #define DEFINE_MIB_BUFFER(X,Y,Z)                                        \
//    DWORD		__rgdwBuff[MIB_INFO_SIZE_IN_DWORDS(Y)]; \
//    PMIB_OPAQUE_INFO    X = (PMIB_OPAQUE_INFO)__rgdwBuff;               \
//    Y *                 Z = (Y *)(X->rgbyData)

// #define CAST_MIB_INFO(X,Y,Z)    Z = (Y)(X->rgbyData)

implementation

end.
