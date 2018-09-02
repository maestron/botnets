{******************************************************************************}
{                                                       	               }
{ Internet Protocol Helper API interface Unit for Object Pascal                }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: ipexport.h, released August 2001. The original Pascal  }
{ code is: IpExport.pas, released September 2000. The initial developer of the }
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

unit JwaIpExport;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "ipexport.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinType;

//
// IP type definitions.
//

type
  IPAddr = ULONG;     // An IP address.
  {$EXTERNALSYM IPAddr}
  IPMask = ULONG;     // An IP subnet mask.
  {$EXTERNALSYM IPMask}
  IP_STATUS = ULONG;  // Status code returned from IP APIs.
  {$EXTERNALSYM IP_STATUS}

{$IFNDEF s6_addr}

//
// Duplicate these definitions here so that this file can be included by
// kernel-mode components which cannot include ws2tcpip.h, as well as
// by user-mode components which do.
//

type
  IN6_ADDR = record
    case Integer of
      0: (Byte: array [0..15] of UCHAR);
      1: (Word: array [0..7] of USHORT);
  end;
  {$EXTERNALSYM IN6_ADDR}
  TIn6Addr = IN6_ADDR;
  PIn6Addr = ^IN6_ADDR;

  in_addr6 = in6_addr;
  {$EXTERNALSYM in_addr6}
  TInAddr6 = in_addr6;
  PInAddr6 = ^in_addr6;

{$ENDIF}

type
  IPv6Addr = in6_addr;
  {$EXTERNALSYM IPv6Addr}
  TIPv6Addr = IPv6Addr;
  PIPv6Addr = ^IPv6Addr;

//#ifndef s_addr

  in_addr = record
    case Integer of
      0: (
        s_b1, s_b2, s_b3, s_b4: UCHAR;
        );
      1: (
        s_w1, s_w2: USHORT
        );
      2: (
        S_addr: ULONG
        );
  end;
  {$EXTERNALSYM in_addr}

//#define s_addr  S_un.S_addr /* can be used for most tcp & ip code */

//#endif

//
// The ip_option_information structure describes the options to be
// included in the header of an IP packet. The TTL, TOS, and Flags
// values are carried in specific fields in the header. The OptionsData
// bytes are carried in the options area following the standard IP header.
// With the exception of source route options, this data must be in the
// format to be transmitted on the wire as specified in RFC 791. A source
// route option should contain the full route - first hop thru final
// destination - in the route data. The first hop will be pulled out of the
// data and the option will be reformatted accordingly. Otherwise, the route
// option should be formatted as specified in RFC 791.
//

type
  IP_OPTION_INFORMATION = record
    Ttl: UCHAR;          // Time To Live
    Tos: UCHAR;          // Type Of Service
    Flags: UCHAR;        // IP header flags
    OptionsSize: UCHAR;  // Size in bytes of options data
    OptionsData: PUCHAR; // Pointer to options data
  end;
  {$EXTERNALSYM IP_OPTION_INFORMATION}
  PIP_OPTION_INFORMATION = ^IP_OPTION_INFORMATION;
  {$EXTERNALSYM PIP_OPTION_INFORMATION}
  TIpOptionInformation = IP_OPTION_INFORMATION;
  PIpOptionInformation = PIP_OPTION_INFORMATION;

//
// The icmp_echo_reply structure describes the data returned in response
// to an echo request.
//

  ICMP_ECHO_REPLY = record
    Address: IPAddr;      // Replying address
    Status: ULONG;        // Reply IP_STATUS
    RoundTripTime: ULONG; // RTT in milliseconds
    DataSize: USHORT;     // Reply data size in bytes
    Reserved: USHORT;     // Reserved for system use
    Data: LPVOID;         // Pointer to the reply data
    Options: ip_option_information; // Reply options
  end;
  {$EXTERNALSYM ICMP_ECHO_REPLY}
  PICMP_ECHO_REPLY = ^ICMP_ECHO_REPLY;
  {$EXTERNALSYM PICMP_ECHO_REPLY}
  TIcmpEchoReply = ICMP_ECHO_REPLY;
  PIcmpEchoReply = PICMP_ECHO_REPLY;

  ARP_SEND_REPLY = record
    DestAddress: IPAddr;
    SrcAddress: IPAddr;
  end;
  {$EXTERNALSYM ARP_SEND_REPLY}
  PARP_SEND_REPLY = ^ARP_SEND_REPLY;
  {$EXTERNALSYM PARP_SEND_REPLY}
  TArpSendReply = ARP_SEND_REPLY;
  PArpSendReply = PARP_SEND_REPLY;

  TCP_RESERVE_PORT_RANGE = record
    UpperRange: USHORT;
    LowerRange: USHORT;
  end;
  {$EXTERNALSYM TCP_RESERVE_PORT_RANGE}
  PTCP_RESERVE_PORT_RANGE = ^TCP_RESERVE_PORT_RANGE;
  {$EXTERNALSYM PTCP_RESERVE_PORT_RANGE}
  TTcpReservePortRange = TCP_RESERVE_PORT_RANGE;
  PTcpReservePortRange = PTCP_RESERVE_PORT_RANGE;
  
const
  MAX_ADAPTER_NAME = 128;
  {$EXTERNALSYM MAX_ADAPTER_NAME}

type
  PIP_ADAPTER_INDEX_MAP = ^IP_ADAPTER_INDEX_MAP;
  {$EXTERNALSYM PIP_ADAPTER_INDEX_MAP}
  _IP_ADAPTER_INDEX_MAP = record
    Index: ULONG;
    Name: array [0..MAX_ADAPTER_NAME - 1] of WCHAR;
  end;
  {$EXTERNALSYM _IP_ADAPTER_INDEX_MAP}
  IP_ADAPTER_INDEX_MAP = _IP_ADAPTER_INDEX_MAP;
  {$EXTERNALSYM IP_ADAPTER_INDEX_MAP}
  TIpAdapterIndexMap = IP_ADAPTER_INDEX_MAP;
  PIpAdapterIndexMap = PIP_ADAPTER_INDEX_MAP;

  PIP_INTERFACE_INFO = ^IP_INTERFACE_INFO;
  {$EXTERNALSYM PIP_INTERFACE_INFO}
  _IP_INTERFACE_INFO = record
    NumAdapters: Longint;
    Adapter: array [0..0] of IP_ADAPTER_INDEX_MAP;
  end;
  {$EXTERNALSYM _IP_INTERFACE_INFO}
  IP_INTERFACE_INFO = _IP_INTERFACE_INFO;
  {$EXTERNALSYM IP_INTERFACE_INFO}
  TIpInterfaceInfo = IP_INTERFACE_INFO;
  PIpInterfaceInfo = PIP_INTERFACE_INFO;

  PIP_UNIDIRECTIONAL_ADAPTER_ADDRESS = ^IP_UNIDIRECTIONAL_ADAPTER_ADDRESS;
  {$EXTERNALSYM PIP_UNIDIRECTIONAL_ADAPTER_ADDRESS}
  _IP_UNIDIRECTIONAL_ADAPTER_ADDRESS = record
    NumAdapters: ULONG;
    Address: array [0..0] of IPAddr;
  end;
  {$EXTERNALSYM _IP_UNIDIRECTIONAL_ADAPTER_ADDRESS}
  IP_UNIDIRECTIONAL_ADAPTER_ADDRESS = _IP_UNIDIRECTIONAL_ADAPTER_ADDRESS;
  {$EXTERNALSYM IP_UNIDIRECTIONAL_ADAPTER_ADDRESS}
  TIpUnidirectionalAdapterAddress = IP_UNIDIRECTIONAL_ADAPTER_ADDRESS;
  PIpUnidirectionalAdapterAddress = PIP_UNIDIRECTIONAL_ADAPTER_ADDRESS;

  PIP_ADAPTER_ORDER_MAP = ^IP_ADAPTER_ORDER_MAP;
  {$EXTERNALSYM PIP_ADAPTER_ORDER_MAP}
  _IP_ADAPTER_ORDER_MAP = record
    NumAdapters: ULONG;
    AdapterOrder: array [0..0] of ULONG;
  end;
  {$EXTERNALSYM _IP_ADAPTER_ORDER_MAP}
  IP_ADAPTER_ORDER_MAP = _IP_ADAPTER_ORDER_MAP;
  {$EXTERNALSYM IP_ADAPTER_ORDER_MAP}
  TIpAdapterOrderMap = IP_ADAPTER_ORDER_MAP;
  PIpAdapterOrderMap = PIP_ADAPTER_ORDER_MAP;

  _IP_MCAST_COUNTER_INFO = record
    InMcastOctets: ULONG64;
    OutMcastOctets: ULONG64;
    InMcastPkts: ULONG64;
    OutMcastPkts: ULONG64;
  end;
  {$EXTERNALSYM _IP_MCAST_COUNTER_INFO}
  IP_MCAST_COUNTER_INFO = _IP_MCAST_COUNTER_INFO;
  {$EXTERNALSYM IP_MCAST_COUNTER_INFO}
  PIP_MCAST_COUNTER_INFO = ^IP_MCAST_COUNTER_INFO;
  {$EXTERNALSYM PIP_MCAST_COUNTER_INFO}
  TIpMCastCounterInfo = IP_MCAST_COUNTER_INFO;
  PIpMCastCounterInfo = PIP_MCAST_COUNTER_INFO;

//
// IP_STATUS codes returned from IP APIs
//

const
  IP_STATUS_BASE = 11000;
  {$EXTERNALSYM IP_STATUS_BASE}

  IP_SUCCESS               = 0;
  {$EXTERNALSYM IP_SUCCESS}
  IP_BUF_TOO_SMALL         = IP_STATUS_BASE + 1;
  {$EXTERNALSYM IP_BUF_TOO_SMALL}
  IP_DEST_NET_UNREACHABLE  = IP_STATUS_BASE + 2;
  {$EXTERNALSYM IP_DEST_NET_UNREACHABLE}
  IP_DEST_HOST_UNREACHABLE = IP_STATUS_BASE + 3;
  {$EXTERNALSYM IP_DEST_HOST_UNREACHABLE}
  IP_DEST_PROT_UNREACHABLE = IP_STATUS_BASE + 4;
  {$EXTERNALSYM IP_DEST_PROT_UNREACHABLE}
  IP_DEST_PORT_UNREACHABLE = IP_STATUS_BASE + 5;
  {$EXTERNALSYM IP_DEST_PORT_UNREACHABLE}
  IP_NO_RESOURCES          = IP_STATUS_BASE + 6;
  {$EXTERNALSYM IP_NO_RESOURCES}
  IP_BAD_OPTION            = IP_STATUS_BASE + 7;
  {$EXTERNALSYM IP_BAD_OPTION}
  IP_HW_ERROR              = IP_STATUS_BASE + 8;
  {$EXTERNALSYM IP_HW_ERROR}
  IP_PACKET_TOO_BIG        = IP_STATUS_BASE + 9;
  {$EXTERNALSYM IP_PACKET_TOO_BIG}
  IP_REQ_TIMED_OUT         = IP_STATUS_BASE + 10;
  {$EXTERNALSYM IP_REQ_TIMED_OUT}
  IP_BAD_REQ               = IP_STATUS_BASE + 11;
  {$EXTERNALSYM IP_BAD_REQ}
  IP_BAD_ROUTE             = IP_STATUS_BASE + 12;
  {$EXTERNALSYM IP_BAD_ROUTE}
  IP_TTL_EXPIRED_TRANSIT   = IP_STATUS_BASE + 13;
  {$EXTERNALSYM IP_TTL_EXPIRED_TRANSIT}
  IP_TTL_EXPIRED_REASSEM   = IP_STATUS_BASE + 14;
  {$EXTERNALSYM IP_TTL_EXPIRED_REASSEM}
  IP_PARAM_PROBLEM         = IP_STATUS_BASE + 15;
  {$EXTERNALSYM IP_PARAM_PROBLEM}
  IP_SOURCE_QUENCH         = IP_STATUS_BASE + 16;
  {$EXTERNALSYM IP_SOURCE_QUENCH}
  IP_OPTION_TOO_BIG        = IP_STATUS_BASE + 17;
  {$EXTERNALSYM IP_OPTION_TOO_BIG}
  IP_BAD_DESTINATION       = IP_STATUS_BASE + 18;
  {$EXTERNALSYM IP_BAD_DESTINATION}

//
// Variants of the above using IPv6 terminology, where different
//

  IP_DEST_NO_ROUTE            = (IP_STATUS_BASE + 2);
  {$EXTERNALSYM IP_DEST_NO_ROUTE}
  IP_DEST_ADDR_UNREACHABLE    = (IP_STATUS_BASE + 3);
  {$EXTERNALSYM IP_DEST_ADDR_UNREACHABLE}
  IP_DEST_PROHIBITED          = (IP_STATUS_BASE + 4);
  {$EXTERNALSYM IP_DEST_PROHIBITED}
  //IP_DEST_PORT_UNREACHABLE    = (IP_STATUS_BASE + 5);
  //{$EXTERNALSYM IP_DEST_PORT_UNREACHABLE}
  IP_HOP_LIMIT_EXCEEDED       = (IP_STATUS_BASE + 13);
  {$EXTERNALSYM IP_HOP_LIMIT_EXCEEDED}
  IP_REASSEMBLY_TIME_EXCEEDED = (IP_STATUS_BASE + 14);
  {$EXTERNALSYM IP_REASSEMBLY_TIME_EXCEEDED}
  IP_PARAMETER_PROBLEM        = (IP_STATUS_BASE + 15);
  {$EXTERNALSYM IP_PARAMETER_PROBLEM}

//
// IPv6-only status codes
//

  IP_DEST_UNREACHABLE         = (IP_STATUS_BASE + 40);
  {$EXTERNALSYM IP_DEST_UNREACHABLE}
  IP_TIME_EXCEEDED            = (IP_STATUS_BASE + 41);
  {$EXTERNALSYM IP_TIME_EXCEEDED}
  IP_BAD_HEADER               = (IP_STATUS_BASE + 42);
  {$EXTERNALSYM IP_BAD_HEADER}
  IP_UNRECOGNIZED_NEXT_HEADER = (IP_STATUS_BASE + 43);
  {$EXTERNALSYM IP_UNRECOGNIZED_NEXT_HEADER}
  IP_ICMP_ERROR               = (IP_STATUS_BASE + 44);
  {$EXTERNALSYM IP_ICMP_ERROR}
  IP_DEST_SCOPE_MISMATCH      = (IP_STATUS_BASE + 45);
  {$EXTERNALSYM IP_DEST_SCOPE_MISMATCH}

//
// The next group are status codes passed up on status indications to
// transport layer protocols.
//

  IP_ADDR_DELETED                    = IP_STATUS_BASE + 19;
  {$EXTERNALSYM IP_ADDR_DELETED}
  IP_SPEC_MTU_CHANGE                 = IP_STATUS_BASE + 20;
  {$EXTERNALSYM IP_SPEC_MTU_CHANGE}
  IP_MTU_CHANGE                      = IP_STATUS_BASE + 21;
  {$EXTERNALSYM IP_MTU_CHANGE}
  IP_UNLOAD                          = IP_STATUS_BASE + 22;
  {$EXTERNALSYM IP_UNLOAD}
  IP_ADDR_ADDED                      = IP_STATUS_BASE + 23;
  {$EXTERNALSYM IP_ADDR_ADDED}
  IP_MEDIA_CONNECT                   = IP_STATUS_BASE + 24;
  {$EXTERNALSYM IP_MEDIA_CONNECT}
  IP_MEDIA_DISCONNECT                = IP_STATUS_BASE + 25;
  {$EXTERNALSYM IP_MEDIA_DISCONNECT}
  IP_BIND_ADAPTER                    = IP_STATUS_BASE + 26;
  {$EXTERNALSYM IP_BIND_ADAPTER}
  IP_UNBIND_ADAPTER                  = IP_STATUS_BASE + 27;
  {$EXTERNALSYM IP_UNBIND_ADAPTER}
  IP_DEVICE_DOES_NOT_EXIST           = IP_STATUS_BASE + 28;
  {$EXTERNALSYM IP_DEVICE_DOES_NOT_EXIST}
  IP_DUPLICATE_ADDRESS               = IP_STATUS_BASE + 29;
  {$EXTERNALSYM IP_DUPLICATE_ADDRESS}
  IP_INTERFACE_METRIC_CHANGE         = IP_STATUS_BASE + 30;
  {$EXTERNALSYM IP_INTERFACE_METRIC_CHANGE}
  IP_RECONFIG_SECFLTR                = IP_STATUS_BASE + 31;
  {$EXTERNALSYM IP_RECONFIG_SECFLTR}
  IP_NEGOTIATING_IPSEC               = IP_STATUS_BASE + 32;
  {$EXTERNALSYM IP_NEGOTIATING_IPSEC}
  IP_INTERFACE_WOL_CAPABILITY_CHANGE = IP_STATUS_BASE + 33;
  {$EXTERNALSYM IP_INTERFACE_WOL_CAPABILITY_CHANGE}
  IP_DUPLICATE_IPADD                 = IP_STATUS_BASE + 34;
  {$EXTERNALSYM IP_DUPLICATE_IPADD}

  IP_GENERAL_FAILURE = IP_STATUS_BASE + 50;
  {$EXTERNALSYM IP_GENERAL_FAILURE}
  MAX_IP_STATUS      = IP_GENERAL_FAILURE;
  {$EXTERNALSYM MAX_IP_STATUS}
  IP_PENDING         = IP_STATUS_BASE + 255;
  {$EXTERNALSYM IP_PENDING}

//
// Values used in the IP header Flags field.
//

  IP_FLAG_DF = $2; // Don't fragment this packet.
  {$EXTERNALSYM IP_FLAG_DF}

//
// Supported IP Option Types.
//
// These types define the options which may be used in the OptionsData field
// of the ip_option_information structure.  See RFC 791 for a complete
// description of each.
//

  IP_OPT_EOL          = 0; // End of list option
  {$EXTERNALSYM IP_OPT_EOL}
  IP_OPT_NOP          = 1; // No operation
  {$EXTERNALSYM IP_OPT_NOP}
  IP_OPT_SECURITY     = $82; // Security option
  {$EXTERNALSYM IP_OPT_SECURITY}
  IP_OPT_LSRR         = $83; // Loose source route
  {$EXTERNALSYM IP_OPT_LSRR}
  IP_OPT_SSRR         = $89; // Strict source route
  {$EXTERNALSYM IP_OPT_SSRR}
  IP_OPT_RR           = $7; // Record route
  {$EXTERNALSYM IP_OPT_RR}
  IP_OPT_TS           = $44; // Timestamp
  {$EXTERNALSYM IP_OPT_TS}
  IP_OPT_SID          = $88; // Stream ID (obsolete)
  {$EXTERNALSYM IP_OPT_SID}
  IP_OPT_ROUTER_ALERT = $94; // Router Alert Option
  {$EXTERNALSYM IP_OPT_ROUTER_ALERT}

  MAX_OPT_SIZE = 40; // Maximum length of IP options in bytes
  {$EXTERNALSYM MAX_OPT_SIZE}

// Ioctls code exposed by Memphis tcpip stack.
// For NT these ioctls are define in ntddip.h  (private\inc)

  IOCTL_IP_RTCHANGE_NOTIFY_REQUEST        = 101;
  {$EXTERNALSYM IOCTL_IP_RTCHANGE_NOTIFY_REQUEST}
  IOCTL_IP_ADDCHANGE_NOTIFY_REQUEST       = 102;
  {$EXTERNALSYM IOCTL_IP_ADDCHANGE_NOTIFY_REQUEST}
  IOCTL_ARP_SEND_REQUEST                  = 103;
  {$EXTERNALSYM IOCTL_ARP_SEND_REQUEST}
  IOCTL_IP_INTERFACE_INFO                 = 104;
  {$EXTERNALSYM IOCTL_IP_INTERFACE_INFO}
  IOCTL_IP_GET_BEST_INTERFACE             = 105;
  {$EXTERNALSYM IOCTL_IP_GET_BEST_INTERFACE}
  IOCTL_IP_UNIDIRECTIONAL_ADAPTER_ADDRESS = 106;
  {$EXTERNALSYM IOCTL_IP_UNIDIRECTIONAL_ADAPTER_ADDRESS}

implementation

end.
