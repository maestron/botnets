{******************************************************************************}
{                                                       	               }
{ Domain Naming Services API interface Unit for Object Pascal                  }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: windns.h, released June 2000. The original Pascal      }
{ code is: WinDNS.pas, released December 2000. The initial developer of the    }
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


{******************************************************************}
{ 								   }
{ Notes (TODO):                                                    }
{   DnsRecordSetDetach() and DnsValidateName_X() didn't have a cc  }
{   IP_ADDRESS_STRING_LENGTH is defined nowhere                    }
{   DNS_WINS_RECORD macro  untranslatable due to IP_ADDRESS        }
{   DNS_RRSET_ADD macro untranslatable                             }
{ 								   }
{******************************************************************}

unit JwaWinDNS;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "WinDNS.h"'}
{$HPPEMIT ''}
{$HPPEMIT 'typeded PDNS_RECORD *PPDNS_RECORD'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinsock2, JwaWinType;

{.$DEFINE ATMA_E164}

type
  IN6_ADDR = Pointer; // todo

//
//  Define QWORD -- not yet defined globally 
//

type
  QWORD = Int64;
  {$EXTERNALSYM QWORD}

//
//  DNS public types
//

type
  DNS_STATUS = Longint;
  {$EXTERNALSYM DNS_STATUS}
  PDNS_STATUS = ^DNS_STATUS;
  {$EXTERNALSYM PDNS_STATUS}
  TDnsStatus = DNS_STATUS;
  PDnsStatus = PDNS_STATUS;

//
//  IP Address
//

type
  IP4_ADDRESS = DWORD;
  {$EXTERNALSYM IP4_ADDRESS}
  PIP4_ADDRESS = ^IP4_ADDRESS;
  {$EXTERNALSYM PIP4_ADDRESS}
  TIP4Address = IP4_ADDRESS;
  PIP4Address = PIP4_ADDRESS;

const
  SIZEOF_IP4_ADDRESS         = 4;
  {$EXTERNALSYM SIZEOF_IP4_ADDRESS}
  IP4_ADDRESS_STRING_LENGTH  = 15;
  {$EXTERNALSYM IP4_ADDRESS_STRING_LENGTH}
  IP4_ADDRESS_STRING_BUFFER_LENGTH = 16;
  {$EXTERNALSYM IP4_ADDRESS_STRING_BUFFER_LENGTH}

//
//  IP Address Array type
//

type
  PIP4_ARRAY = ^IP4_ARRAY;
  {$EXTERNALSYM PIP4_ARRAY}
  _IP4_ARRAY = record
    AddrCount: DWORD;
    AddrArray: array [0..0] of IP4_ADDRESS;
  end;
  {$EXTERNALSYM _IP4_ARRAY}
  IP4_ARRAY = _IP4_ARRAY;
  {$EXTERNALSYM IP4_ARRAY}
  TIp4Array = IP4_ARRAY;
  PIp4Array = PIP4_ARRAY;

//
//  IPv6 Address
//

  PIP6_ADDRESS = ^IP6_ADDRESS;
  {$EXTERNALSYM PIP6_ADDRESS}
  IP6_ADDRESS = record
    case Integer of
      0: (IP6Qword: array [0..1] of QWORD);
      1: (IP6Dword: array [0..3] of DWORD);
      2: (IP6Word: array [0..7] of WORD);
      3: (IP6Byte: array [0..15] of BYTE);
      4: (In6: IN6_ADDR);
  end;
  {$EXTERNALSYM IP6_ADDRESS}
  TIp6Address = IP6_ADDRESS;
  PIp6Address = PIP6_ADDRESS;

//  Backward compatibility

  DNS_IP6_ADDRESS = IP6_ADDRESS;
  {$EXTERNALSYM DNS_IP6_ADDRESS}
  PDNS_IP6_ADDRESS = ^IP6_ADDRESS;
  {$EXTERNALSYM PDNS_IP6_ADDRESS}
  TDnsIp6Address = DNS_IP6_ADDRESS;
  PDnsIp6Address = PDNS_IP6_ADDRESS;

//
//  IP6 string max is 45 bytes
//      - 6 WORDs in colon+hex (5 chars)
//      - last DWORD as IP4 (15 chars)
//  

const
  IP6_ADDRESS_STRING_LENGTH        = (47);
  {$EXTERNALSYM IP6_ADDRESS_STRING_LENGTH}
  IP6_ADDRESS_STRING_BUFFER_LENGTH = (48);
  {$EXTERNALSYM IP6_ADDRESS_STRING_BUFFER_LENGTH}

//  backcompat

  IPV6_ADDRESS_STRING_LENGTH = IP6_ADDRESS_STRING_LENGTH;
  {$EXTERNALSYM IPV6_ADDRESS_STRING_LENGTH}

//
//  Inline byte flipping -- can be done in registers
//

procedure INLINE_WORD_FLIP(var Out: WORD; In_: WORD);
{$EXTERNALSYM INLINE_WORD_FLIP}

procedure INLINE_HTONS(var Out: WORD; In_: WORD);
{$EXTERNALSYM INLINE_HTONS}

procedure INLINE_NTOHS(var Out: WORD; In_: WORD);
{$EXTERNALSYM INLINE_NTOHS}

procedure INLINE_DWORD_FLIP(var Out: DWORD; In_: DWORD);
{$EXTERNALSYM INLINE_DWORD_FLIP}

procedure INLINE_NTOHL(var Out: DWORD; In_: DWORD);
{$EXTERNALSYM INLINE_NTOHL}

procedure INLINE_HTONL(var Out: DWORD; In_: DWORD);
{$EXTERNALSYM INLINE_HTONL}

//
//  Inline byte flip and write to packet (unaligned)
//

procedure INLINE_WRITE_FLIPPED_WORD(pout: PWORD; In_: WORD);
{$EXTERNALSYM INLINE_WRITE_FLIPPED_WORD}

procedure INLINE_WRITE_FLIPPED_DWORD(pout: PDWORD; In_: DWORD);
{$EXTERNALSYM INLINE_WRITE_FLIPPED_DWORD}

//
//  Basic DNS definitions
//

//
//  DNS port for both UDP and TCP is 53.
//

const
  DNS_PORT_HOST_ORDER = ($0035); // port 53
  {$EXTERNALSYM DNS_PORT_HOST_ORDER}
  DNS_PORT_NET_ORDER  = ($3500);
  {$EXTERNALSYM DNS_PORT_NET_ORDER}

//
//  DNS UDP packets no more than 512 bytes
//

  DNS_RFC_MAX_UDP_PACKET_LENGTH = (512);
  {$EXTERNALSYM DNS_RFC_MAX_UDP_PACKET_LENGTH}

//
//  DNS Names limited to 255, 63 in any one label
//

  DNS_MAX_NAME_LENGTH  = (255);
  {$EXTERNALSYM DNS_MAX_NAME_LENGTH}
  DNS_MAX_LABEL_LENGTH = (63);
  {$EXTERNALSYM DNS_MAX_LABEL_LENGTH}

  DNS_MAX_NAME_BUFFER_LENGTH  = (256);
  {$EXTERNALSYM DNS_MAX_NAME_BUFFER_LENGTH}
  DNS_MAX_LABEL_BUFFER_LENGTH = (64);
  {$EXTERNALSYM DNS_MAX_LABEL_BUFFER_LENGTH}

//
//  Reverse lookup domain names
//

  DNS_IP4_REVERSE_DOMAIN_STRING = ('in-addr.arpa.');
  {$EXTERNALSYM DNS_IP4_REVERSE_DOMAIN_STRING}

  //DNS_MAX_IP4_REVERSE_NAME_LENGTH = (IP_ADDRESS_STRING_LENGTH + 1 + SizeOf(DNS_IP4_REVERSE_DOMAIN_STRING));
  //{$EXTERNALSYM DNS_MAX_IP4_REVERSE_NAME_LENGTH}

  //DNS_MAX_IP4_REVERSE_NAME_BUFFER_LENGTH = (DNS_MAX_IP4_REVERSE_NAME_LENGTH + 1);
  //{$EXTERNALSYM DNS_MAX_IP4_REVERSE_NAME_BUFFER_LENGTH}

  DNS_IP6_REVERSE_DOMAIN_STRING = ('ip6.int.');
  {$EXTERNALSYM DNS_IP6_REVERSE_DOMAIN_STRING}

  DNS_MAX_IP6_REVERSE_NAME_LENGTH = (64 + SizeOf(DNS_IP6_REVERSE_DOMAIN_STRING));
  {$EXTERNALSYM DNS_MAX_IP6_REVERSE_NAME_LENGTH}

  DNS_MAX_IP6_REVERSE_NAME_BUFFER_LENGTH = (DNS_MAX_IP6_REVERSE_NAME_LENGTH + 1);
  {$EXTERNALSYM DNS_MAX_IP6_REVERSE_NAME_BUFFER_LENGTH}

//  Combined

  DNS_MAX_REVERSE_NAME_LENGTH = DNS_MAX_IP6_REVERSE_NAME_LENGTH;
  {$EXTERNALSYM DNS_MAX_REVERSE_NAME_LENGTH}

  DNS_MAX_REVERSE_NAME_BUFFER_LENGTH = DNS_MAX_IP6_REVERSE_NAME_BUFFER_LENGTH;
  {$EXTERNALSYM DNS_MAX_REVERSE_NAME_BUFFER_LENGTH}

//
//  DNS Text string limited by size representable
//      in a single byte length field

  DNS_MAX_TEXT_STRING_LENGTH = (255);
  {$EXTERNALSYM DNS_MAX_TEXT_STRING_LENGTH}

//
//  DNS On-The-Wire Structures
//

//
//  DNS Message Header
//

type
  _DNS_HEADER = packed record
    Xid: WORD;
    Flags: Byte;
    //BYTE    RecursionDesired : 1;
    //BYTE    Truncation : 1;
    //BYTE    Authoritative : 1;
    //BYTE    Opcode : 4;
    //BYTE    IsResponse : 1;
    Flags2: Byte;
    //BYTE    ResponseCode : 4;
    //BYTE    Reserved : 3;
    //BYTE    RecursionAvailable : 1;
    QuestionCount: WORD;
    AnswerCount: WORD;
    NameServerCount: WORD;
    AdditionalCount: WORD;
  end;
  {$EXTERNALSYM _DNS_HEADER}
  DNS_HEADER = _DNS_HEADER;
  {$EXTERNALSYM DNS_HEADER}
  PDNS_HEADER = ^DNS_HEADER;
  {$EXTERNALSYM PDNS_HEADER}
  TDnsHeader = DNS_HEADER;
  PDnsHeader = PDNS_HEADER;

//
//  Flags as WORD
//

function DNS_HEADER_FLAGS(pHead: PDNS_HEADER): WORD;
{$EXTERNALSYM DNS_HEADER_FLAGS}

//
//  Byte flip DNS header to\from host order.
//
//  Note that this does NOT flip flags, as definition above defines
//  flags as individual bytes for direct access to net byte order.
//

procedure DNS_BYTE_FLIP_HEADER_COUNTS(var pHeader: PDNS_HEADER);
{$EXTERNALSYM DNS_BYTE_FLIP_HEADER_COUNTS}

//
//  Question name follows header
//

const
  DNS_OFFSET_TO_QUESTION_NAME = SizeOf(DNS_HEADER);
  {$EXTERNALSYM DNS_OFFSET_TO_QUESTION_NAME}

//
//  Question immediately follows header so compressed question name
//      0xC000 | sizeof(DNS_HEADER)

  DNS_COMPRESSED_QUESTION_NAME = ($C00C);
  {$EXTERNALSYM DNS_COMPRESSED_QUESTION_NAME}

//
//  Packet extraction macros
//

{
#define DNS_QUESTION_NAME_FROM_HEADER( _pHeader_ ) \
            ( (PCHAR)( (PDNS_HEADER)(_pHeader_) + 1 ) )

#define DNS_ANSWER_FROM_QUESTION( _pQuestion_ ) \
            ( (PCHAR)( (PDNS_QUESTION)(_pQuestion_) + 1 ) )
}

//
//  DNS Question
//

type
  PDNS_WIRE_QUESTION = ^DNS_WIRE_QUESTION;
  {$EXTERNALSYM PDNS_WIRE_QUESTION}
  _DNS_WIRE_QUESTION = packed record
    //  Preceded by question name
    QuestionType: WORD;
    QuestionClass: WORD;
  end;
  {$EXTERNALSYM _DNS_WIRE_QUESTION}
  DNS_WIRE_QUESTION = _DNS_WIRE_QUESTION;
  {$EXTERNALSYM DNS_WIRE_QUESTION}
  TDnsWireQuestion = DNS_WIRE_QUESTION;
  PDnsWireQuestion = PDNS_WIRE_QUESTION;

//
//  DNS Resource Record
//

  PDNS_WIRE_RECORD = ^DNS_WIRE_RECORD;
  {$EXTERNALSYM PDNS_WIRE_RECORD}
  _DNS_WIRE_RECORD = packed record
    //  Preceded by record owner name
    RecordType: WORD;
    RecordClass: WORD;
    TimeToLive: DWORD;
    DataLength: WORD;
    //  Followed by record data
  end;
  {$EXTERNALSYM _DNS_WIRE_RECORD}
  DNS_WIRE_RECORD = _DNS_WIRE_RECORD;
  {$EXTERNALSYM DNS_WIRE_RECORD}
  TDnsWireRecord = DNS_WIRE_RECORD;
  PDnsWireRecord = PDNS_WIRE_RECORD;

//
//  DNS Query Types
//

const
  DNS_OPCODE_QUERY         = 0; // Query
  {$EXTERNALSYM DNS_OPCODE_QUERY}
  DNS_OPCODE_IQUERY        = 1; // Obsolete: IP to name
  {$EXTERNALSYM DNS_OPCODE_IQUERY}
  DNS_OPCODE_SERVER_STATUS = 2; // Obsolete: DNS ping
  {$EXTERNALSYM DNS_OPCODE_SERVER_STATUS}
  DNS_OPCODE_UNKNOWN       = 3; // Unknown
  {$EXTERNALSYM DNS_OPCODE_UNKNOWN}
  DNS_OPCODE_NOTIFY        = 4; // Notify
  {$EXTERNALSYM DNS_OPCODE_NOTIFY}
  DNS_OPCODE_UPDATE        = 5; // Dynamic Update
  {$EXTERNALSYM DNS_OPCODE_UPDATE}

//
//  DNS response codes.
//
//  Sent in the "ResponseCode" field of a DNS_HEADER.
//

  DNS_RCODE_NOERROR  = 0;
  {$EXTERNALSYM DNS_RCODE_NOERROR}
  DNS_RCODE_FORMERR  = 1; // Format error
  {$EXTERNALSYM DNS_RCODE_FORMERR}
  DNS_RCODE_SERVFAIL = 2; // Server failure
  {$EXTERNALSYM DNS_RCODE_SERVFAIL}
  DNS_RCODE_NXDOMAIN = 3; // Name error
  {$EXTERNALSYM DNS_RCODE_NXDOMAIN}
  DNS_RCODE_NOTIMPL  = 4; // Not implemented
  {$EXTERNALSYM DNS_RCODE_NOTIMPL}
  DNS_RCODE_REFUSED  = 5; // Refused
  {$EXTERNALSYM DNS_RCODE_REFUSED}
  DNS_RCODE_YXDOMAIN = 6; // Domain name should not exist
  {$EXTERNALSYM DNS_RCODE_YXDOMAIN}
  DNS_RCODE_YXRRSET  = 7; // RR set should not exist
  {$EXTERNALSYM DNS_RCODE_YXRRSET}
  DNS_RCODE_NXRRSET  = 8; // RR set does not exist
  {$EXTERNALSYM DNS_RCODE_NXRRSET}
  DNS_RCODE_NOTAUTH  = 9; // Not authoritative for zone
  {$EXTERNALSYM DNS_RCODE_NOTAUTH}
  DNS_RCODE_NOTZONE  = 10; // Name is not zone
  {$EXTERNALSYM DNS_RCODE_NOTZONE}
  DNS_RCODE_MAX      = 15;
  {$EXTERNALSYM DNS_RCODE_MAX}

//
//  Extended RCODEs
//

  DNS_RCODE_BADVERS = 16; // Bad EDNS version
  {$EXTERNALSYM DNS_RCODE_BADVERS}
  DNS_RCODE_BADSIG  = 16; // Bad signature
  {$EXTERNALSYM DNS_RCODE_BADSIG}
  DNS_RCODE_BADKEY  = 17; // Bad key
  {$EXTERNALSYM DNS_RCODE_BADKEY}
  DNS_RCODE_BADTIME = 18; // Bad timestamp
  {$EXTERNALSYM DNS_RCODE_BADTIME}

//
//  Mappings to friendly names
//

  DNS_RCODE_NO_ERROR        = DNS_RCODE_NOERROR;
  {$EXTERNALSYM DNS_RCODE_NO_ERROR}
  DNS_RCODE_FORMAT_ERROR    = DNS_RCODE_FORMERR;
  {$EXTERNALSYM DNS_RCODE_FORMAT_ERROR}
  DNS_RCODE_SERVER_FAILURE  = DNS_RCODE_SERVFAIL;
  {$EXTERNALSYM DNS_RCODE_SERVER_FAILURE}
  DNS_RCODE_NAME_ERROR      = DNS_RCODE_NXDOMAIN;
  {$EXTERNALSYM DNS_RCODE_NAME_ERROR}
  DNS_RCODE_NOT_IMPLEMENTED = DNS_RCODE_NOTIMPL;
  {$EXTERNALSYM DNS_RCODE_NOT_IMPLEMENTED}

//
//  DNS Classes
//
//  Classes are on the wire as WORDs.
//
//  _CLASS_ defines in host order.
//  _RCLASS_ defines in net byte order.
//
//  Generally we'll avoid byte flip and test class in net byte order.
//

  DNS_CLASS_INTERNET = $0001; // 1
  {$EXTERNALSYM DNS_CLASS_INTERNET}
  DNS_CLASS_CSNET    = $0002; // 2
  {$EXTERNALSYM DNS_CLASS_CSNET}
  DNS_CLASS_CHAOS    = $0003; // 3
  {$EXTERNALSYM DNS_CLASS_CHAOS}
  DNS_CLASS_HESIOD   = $0004; // 4
  {$EXTERNALSYM DNS_CLASS_HESIOD}
  DNS_CLASS_NONE     = $00fe; // 254
  {$EXTERNALSYM DNS_CLASS_NONE}
  DNS_CLASS_ALL      = $00ff; // 255
  {$EXTERNALSYM DNS_CLASS_ALL}
  DNS_CLASS_ANY      = $00ff; // 255
  {$EXTERNALSYM DNS_CLASS_ANY}

  DNS_RCLASS_INTERNET = $0100; // 1
  {$EXTERNALSYM DNS_RCLASS_INTERNET}
  DNS_RCLASS_CSNET    = $0200; // 2
  {$EXTERNALSYM DNS_RCLASS_CSNET}
  DNS_RCLASS_CHAOS    = $0300; // 3
  {$EXTERNALSYM DNS_RCLASS_CHAOS}
  DNS_RCLASS_HESIOD   = $0400; // 4
  {$EXTERNALSYM DNS_RCLASS_HESIOD}
  DNS_RCLASS_NONE     = $fe00; // 254
  {$EXTERNALSYM DNS_RCLASS_NONE}
  DNS_RCLASS_ALL      = $ff00; // 255
  {$EXTERNALSYM DNS_RCLASS_ALL}
  DNS_RCLASS_ANY      = $ff00; // 255
  {$EXTERNALSYM DNS_RCLASS_ANY}

//
//  DNS Record Types
//
//  _TYPE_ defines are in host byte order.
//  _RTYPE_ defines are in net byte order.
//
//  Generally always deal with types in host byte order as we index
//  resource record functions by type.
//

  DNS_TYPE_ZERO = $0000;
  {$EXTERNALSYM DNS_TYPE_ZERO}

//  RFC 1034/1035
  DNS_TYPE_A     = $0001; // 1
  {$EXTERNALSYM DNS_TYPE_A}
  DNS_TYPE_NS    = $0002; // 2
  {$EXTERNALSYM DNS_TYPE_NS}
  DNS_TYPE_MD    = $0003; // 3
  {$EXTERNALSYM DNS_TYPE_MD}
  DNS_TYPE_MF    = $0004; // 4
  {$EXTERNALSYM DNS_TYPE_MF}
  DNS_TYPE_CNAME = $0005; // 5
  {$EXTERNALSYM DNS_TYPE_CNAME}
  DNS_TYPE_SOA   = $0006; // 6
  {$EXTERNALSYM DNS_TYPE_SOA}
  DNS_TYPE_MB    = $0007; // 7
  {$EXTERNALSYM DNS_TYPE_MB}
  DNS_TYPE_MG    = $0008; // 8
  {$EXTERNALSYM DNS_TYPE_MG}
  DNS_TYPE_MR    = $0009; // 9
  {$EXTERNALSYM DNS_TYPE_MR}
  DNS_TYPE_NULL  = $000a; // 10
  {$EXTERNALSYM DNS_TYPE_NULL}
  DNS_TYPE_WKS   = $000b; // 11
  {$EXTERNALSYM DNS_TYPE_WKS}
  DNS_TYPE_PTR   = $000c; // 12
  {$EXTERNALSYM DNS_TYPE_PTR}
  DNS_TYPE_HINFO = $000d; // 13
  {$EXTERNALSYM DNS_TYPE_HINFO}
  DNS_TYPE_MINFO = $000e; // 14
  {$EXTERNALSYM DNS_TYPE_MINFO}
  DNS_TYPE_MX    = $000f; // 15
  {$EXTERNALSYM DNS_TYPE_MX}
  DNS_TYPE_TEXT  = $0010; // 16
  {$EXTERNALSYM DNS_TYPE_TEXT}

//  RFC 1183
  DNS_TYPE_RP    = $0011; // 17
  {$EXTERNALSYM DNS_TYPE_RP}
  DNS_TYPE_AFSDB = $0012; // 18
  {$EXTERNALSYM DNS_TYPE_AFSDB}
  DNS_TYPE_X25   = $0013; // 19
  {$EXTERNALSYM DNS_TYPE_X25}
  DNS_TYPE_ISDN  = $0014; // 20
  {$EXTERNALSYM DNS_TYPE_ISDN}
  DNS_TYPE_RT    = $0015; // 21
  {$EXTERNALSYM DNS_TYPE_RT}

//  RFC 1348
  DNS_TYPE_NSAP    = $0016; // 22
  {$EXTERNALSYM DNS_TYPE_NSAP}
  DNS_TYPE_NSAPPTR = $0017; // 23
  {$EXTERNALSYM DNS_TYPE_NSAPPTR}

//  RFC 2065    (DNS security)
  DNS_TYPE_SIG = $0018; // 24
  {$EXTERNALSYM DNS_TYPE_SIG}
  DNS_TYPE_KEY = $0019; // 25
  {$EXTERNALSYM DNS_TYPE_KEY}

//  RFC 1664    (X.400 mail)
  DNS_TYPE_PX = $001a; // 26
  {$EXTERNALSYM DNS_TYPE_PX}

//  RFC 1712    (Geographic position)
  DNS_TYPE_GPOS = $001b; // 27
  {$EXTERNALSYM DNS_TYPE_GPOS}

//  RFC 1886    (IPv6 Address)
  DNS_TYPE_AAAA = $001c; // 28
  {$EXTERNALSYM DNS_TYPE_AAAA}

//  RFC 1876    (Geographic location)
  DNS_TYPE_LOC = $001d; // 29
  {$EXTERNALSYM DNS_TYPE_LOC}

//  RFC 2065    (Secure negative response)
  DNS_TYPE_NXT = $001e; // 30
  {$EXTERNALSYM DNS_TYPE_NXT}

//  Patton      (Endpoint Identifier)
  DNS_TYPE_EID = $001f; // 31
  {$EXTERNALSYM DNS_TYPE_EID}

//  Patton      (Nimrod Locator)
  DNS_TYPE_NIMLOC = $0020; // 32
  {$EXTERNALSYM DNS_TYPE_NIMLOC}

//  RFC 2052    (Service location)
  DNS_TYPE_SRV = $0021; // 33
  {$EXTERNALSYM DNS_TYPE_SRV}

//  ATM Standard something-or-another (ATM Address)
  DNS_TYPE_ATMA = $0022; // 34
  {$EXTERNALSYM DNS_TYPE_ATMA}

//  RFC 2168    (Naming Authority Pointer)
  DNS_TYPE_NAPTR = $0023; // 35
  {$EXTERNALSYM DNS_TYPE_NAPTR}

//  RFC 2230    (Key Exchanger)
  DNS_TYPE_KX = $0024; // 36
  {$EXTERNALSYM DNS_TYPE_KX}

//  RFC 2538    (CERT)
  DNS_TYPE_CERT = $0025; // 37
  {$EXTERNALSYM DNS_TYPE_CERT}

//  A6 Draft    (A6)
  DNS_TYPE_A6 = $0026; // 38
  {$EXTERNALSYM DNS_TYPE_A6}

//  DNAME Draft (DNAME)
  DNS_TYPE_DNAME = $0027; // 39
  {$EXTERNALSYM DNS_TYPE_DNAME}

//  Eastlake    (Kitchen Sink)
  DNS_TYPE_SINK = $0028; // 40
  {$EXTERNALSYM DNS_TYPE_SINK}

//  RFC 2671    (EDNS OPT)
  DNS_TYPE_OPT = $0029; // 41
  {$EXTERNALSYM DNS_TYPE_OPT}

//
//  IANA Reserved
//

  DNS_TYPE_UINFO  = $0064; // 100
  {$EXTERNALSYM DNS_TYPE_UINFO}
  DNS_TYPE_UID    = $0065; // 101
  {$EXTERNALSYM DNS_TYPE_UID}
  DNS_TYPE_GID    = $0066; // 102
  {$EXTERNALSYM DNS_TYPE_GID}
  DNS_TYPE_UNSPEC = $0067; // 103
  {$EXTERNALSYM DNS_TYPE_UNSPEC}

//
//  Query only types (1035, 1995)
//      - Crawford      (ADDRS)
//      - TKEY draft    (TKEY)
//      - TSIG draft    (TSIG)
//      - RFC 1995      (IXFR)
//      - RFC 1035      (AXFR up)
//

  DNS_TYPE_ADDRS = $00f8; // 248
  {$EXTERNALSYM DNS_TYPE_ADDRS}
  DNS_TYPE_TKEY  = $00f9; // 249
  {$EXTERNALSYM DNS_TYPE_TKEY}
  DNS_TYPE_TSIG  = $00fa; // 250
  {$EXTERNALSYM DNS_TYPE_TSIG}
  DNS_TYPE_IXFR  = $00fb; // 251
  {$EXTERNALSYM DNS_TYPE_IXFR}
  DNS_TYPE_AXFR  = $00fc; // 252
  {$EXTERNALSYM DNS_TYPE_AXFR}
  DNS_TYPE_MAILB = $00fd; // 253
  {$EXTERNALSYM DNS_TYPE_MAILB}
  DNS_TYPE_MAILA = $00fe; // 254
  {$EXTERNALSYM DNS_TYPE_MAILA}
  DNS_TYPE_ALL   = $00ff; // 255
  {$EXTERNALSYM DNS_TYPE_ALL}
  DNS_TYPE_ANY   = $00ff; // 255
  {$EXTERNALSYM DNS_TYPE_ANY}

//
//  Temp Microsoft types -- use until get IANA approval for real type
//

  DNS_TYPE_WINS   = $ff01; // 64K - 255
  {$EXTERNALSYM DNS_TYPE_WINS}
  DNS_TYPE_WINSR  = $ff02; // 64K - 254
  {$EXTERNALSYM DNS_TYPE_WINSR}
  DNS_TYPE_NBSTAT = (DNS_TYPE_WINSR);
  {$EXTERNALSYM DNS_TYPE_NBSTAT}


//
//  DNS Record Types -- Net Byte Order
//

  DNS_RTYPE_A       = $0100; // 1
  {$EXTERNALSYM DNS_RTYPE_A}
  DNS_RTYPE_NS      = $0200; // 2
  {$EXTERNALSYM DNS_RTYPE_NS}
  DNS_RTYPE_MD      = $0300; // 3
  {$EXTERNALSYM DNS_RTYPE_MD}
  DNS_RTYPE_MF      = $0400; // 4
  {$EXTERNALSYM DNS_RTYPE_MF}
  DNS_RTYPE_CNAME   = $0500; // 5
  {$EXTERNALSYM DNS_RTYPE_CNAME}
  DNS_RTYPE_SOA     = $0600; // 6
  {$EXTERNALSYM DNS_RTYPE_SOA}
  DNS_RTYPE_MB      = $0700; // 7
  {$EXTERNALSYM DNS_RTYPE_MB}
  DNS_RTYPE_MG      = $0800; // 8
  {$EXTERNALSYM DNS_RTYPE_MG}
  DNS_RTYPE_MR      = $0900; // 9
  {$EXTERNALSYM DNS_RTYPE_MR}
  DNS_RTYPE_NULL    = $0a00; // 10
  {$EXTERNALSYM DNS_RTYPE_NULL}
  DNS_RTYPE_WKS     = $0b00; // 11
  {$EXTERNALSYM DNS_RTYPE_WKS}
  DNS_RTYPE_PTR     = $0c00; // 12
  {$EXTERNALSYM DNS_RTYPE_PTR}
  DNS_RTYPE_HINFO   = $0d00; // 13
  {$EXTERNALSYM DNS_RTYPE_HINFO}
  DNS_RTYPE_MINFO   = $0e00; // 14
  {$EXTERNALSYM DNS_RTYPE_MINFO}
  DNS_RTYPE_MX      = $0f00; // 15
  {$EXTERNALSYM DNS_RTYPE_MX}
  DNS_RTYPE_TEXT    = $1000; // 16
  {$EXTERNALSYM DNS_RTYPE_TEXT}
  DNS_RTYPE_RP      = $1100; // 17
  {$EXTERNALSYM DNS_RTYPE_RP}
  DNS_RTYPE_AFSDB   = $1200; // 18
  {$EXTERNALSYM DNS_RTYPE_AFSDB}
  DNS_RTYPE_X25     = $1300; // 19
  {$EXTERNALSYM DNS_RTYPE_X25}
  DNS_RTYPE_ISDN    = $1400; // 20
  {$EXTERNALSYM DNS_RTYPE_ISDN}
  DNS_RTYPE_RT      = $1500; // 21
  {$EXTERNALSYM DNS_RTYPE_RT}
  DNS_RTYPE_NSAP    = $1600; // 22
  {$EXTERNALSYM DNS_RTYPE_NSAP}
  DNS_RTYPE_NSAPPTR = $1700; // 23
  {$EXTERNALSYM DNS_RTYPE_NSAPPTR}
  DNS_RTYPE_SIG     = $1800; // 24
  {$EXTERNALSYM DNS_RTYPE_SIG}
  DNS_RTYPE_KEY     = $1900; // 25
  {$EXTERNALSYM DNS_RTYPE_KEY}
  DNS_RTYPE_PX      = $1a00; // 26
  {$EXTERNALSYM DNS_RTYPE_PX}
  DNS_RTYPE_GPOS    = $1b00; // 27
  {$EXTERNALSYM DNS_RTYPE_GPOS}
  DNS_RTYPE_AAAA    = $1c00; // 28
  {$EXTERNALSYM DNS_RTYPE_AAAA}
  DNS_RTYPE_LOC     = $1d00; // 29
  {$EXTERNALSYM DNS_RTYPE_LOC}
  DNS_RTYPE_NXT     = $1e00; // 30
  {$EXTERNALSYM DNS_RTYPE_NXT}
  DNS_RTYPE_EID     = $1f00; // 31
  {$EXTERNALSYM DNS_RTYPE_EID}
  DNS_RTYPE_NIMLOC  = $2000; // 32
  {$EXTERNALSYM DNS_RTYPE_NIMLOC}
  DNS_RTYPE_SRV     = $2100; // 33
  {$EXTERNALSYM DNS_RTYPE_SRV}
  DNS_RTYPE_ATMA    = $2200; // 34
  {$EXTERNALSYM DNS_RTYPE_ATMA}
  DNS_RTYPE_NAPTR   = $2300; // 35
  {$EXTERNALSYM DNS_RTYPE_NAPTR}
  DNS_RTYPE_KX      = $2400; // 36
  {$EXTERNALSYM DNS_RTYPE_KX}
  DNS_RTYPE_CERT    = $2500; // 37
  {$EXTERNALSYM DNS_RTYPE_CERT}
  DNS_RTYPE_A6      = $2600; // 38
  {$EXTERNALSYM DNS_RTYPE_A6}
  DNS_RTYPE_DNAME   = $2700; // 39
  {$EXTERNALSYM DNS_RTYPE_DNAME}
  DNS_RTYPE_SINK    = $2800; // 40
  {$EXTERNALSYM DNS_RTYPE_SINK}
  DNS_RTYPE_OPT     = $2900; // 41
  {$EXTERNALSYM DNS_RTYPE_OPT}

//
//  IANA Reserved
//

  DNS_RTYPE_UINFO  = $6400; // 100
  {$EXTERNALSYM DNS_RTYPE_UINFO}
  DNS_RTYPE_UID    = $6500; // 101
  {$EXTERNALSYM DNS_RTYPE_UID}
  DNS_RTYPE_GID    = $6600; // 102
  {$EXTERNALSYM DNS_RTYPE_GID}
  DNS_RTYPE_UNSPEC = $6700; // 103
  {$EXTERNALSYM DNS_RTYPE_UNSPEC}

//
//  Query only types
//

  DNS_RTYPE_TKEY  = $f900; // 249
  {$EXTERNALSYM DNS_RTYPE_TKEY}
  DNS_RTYPE_TSIG  = $fa00; // 250
  {$EXTERNALSYM DNS_RTYPE_TSIG}
  DNS_RTYPE_IXFR  = $fb00; // 251
  {$EXTERNALSYM DNS_RTYPE_IXFR}
  DNS_RTYPE_AXFR  = $fc00; // 252
  {$EXTERNALSYM DNS_RTYPE_AXFR}
  DNS_RTYPE_MAILB = $fd00; // 253
  {$EXTERNALSYM DNS_RTYPE_MAILB}
  DNS_RTYPE_MAILA = $fe00; // 254
  {$EXTERNALSYM DNS_RTYPE_MAILA}
  DNS_RTYPE_ALL   = $ff00; // 255
  {$EXTERNALSYM DNS_RTYPE_ALL}
  DNS_RTYPE_ANY   = $ff00; // 255
  {$EXTERNALSYM DNS_RTYPE_ANY}

//
//  Temp Microsoft types -- use until get IANA approval for real type
//

  DNS_RTYPE_WINS  = $01ff; // 64K - 255
  {$EXTERNALSYM DNS_RTYPE_WINS}
  DNS_RTYPE_WINSR = $02ff; // 64K - 254
  {$EXTERNALSYM DNS_RTYPE_WINSR}

//
//  Record type specific definitions
//

//
//  ATMA (ATM address type) formats
//
//  Define these directly for any environment (ex NT4)
//  without winsock2 ATM support (ws2atm.h)
//

{$IFNDEF ATMA_E164}
  DNS_ATMA_FORMAT_E164     = 1;
  {$EXTERNALSYM DNS_ATMA_FORMAT_E164}
  DNS_ATMA_FORMAT_AESA     = 2;
  {$EXTERNALSYM DNS_ATMA_FORMAT_AESA}
  DNS_ATMA_MAX_ADDR_LENGTH = (20);
  {$EXTERNALSYM DNS_ATMA_MAX_ADDR_LENGTH}
{$ELSE}
  DNS_ATMA_FORMAT_E164     = ATM_E164;
  {$EXTERNALSYM DNS_ATMA_FORMAT_E164}
  DNS_ATMA_FORMAT_AESA     = ATM_AESA;
  {$EXTERNALSYM DNS_ATMA_FORMAT_AESA}
  DNS_ATMA_MAX_ADDR_LENGTH = ATM_ADDR_SIZE;
  {$EXTERNALSYM DNS_ATMA_MAX_ADDR_LENGTH}
{$ENDIF}

  DNS_ATMA_AESA_ADDR_LENGTH  = (20);
  {$EXTERNALSYM DNS_ATMA_AESA_ADDR_LENGTH}
  DNS_ATMA_MAX_RECORD_LENGTH = (DNS_ATMA_MAX_ADDR_LENGTH+1);
  {$EXTERNALSYM DNS_ATMA_MAX_RECORD_LENGTH}

//
//  DNSSEC defs
//

//  DNSSEC algorithms

  DNSSEC_ALGORITHM_RSAMD5  = 1;
  {$EXTERNALSYM DNSSEC_ALGORITHM_RSAMD5}
  DNSSEC_ALGORITHM_NULL    = 253;
  {$EXTERNALSYM DNSSEC_ALGORITHM_NULL}
  DNSSEC_ALGORITHM_PRIVATE = 254;
  {$EXTERNALSYM DNSSEC_ALGORITHM_PRIVATE}

//  DNSSEC KEY protocol table

  DNSSEC_PROTOCOL_NONE   = 0;
  {$EXTERNALSYM DNSSEC_PROTOCOL_NONE}
  DNSSEC_PROTOCOL_TLS    = 1;
  {$EXTERNALSYM DNSSEC_PROTOCOL_TLS}
  DNSSEC_PROTOCOL_EMAIL  = 2;
  {$EXTERNALSYM DNSSEC_PROTOCOL_EMAIL}
  DNSSEC_PROTOCOL_DNSSEC = 3;
  {$EXTERNALSYM DNSSEC_PROTOCOL_DNSSEC}
  DNSSEC_PROTOCOL_IPSEC  = 4;
  {$EXTERNALSYM DNSSEC_PROTOCOL_IPSEC}

//  DNSSEC KEY flag field

  DNSSEC_KEY_FLAG_NOAUTH = $0001;
  {$EXTERNALSYM DNSSEC_KEY_FLAG_NOAUTH}
  DNSSEC_KEY_FLAG_NOCONF = $0002;
  {$EXTERNALSYM DNSSEC_KEY_FLAG_NOCONF}
  DNSSEC_KEY_FLAG_FLAG2  = $0004;
  {$EXTERNALSYM DNSSEC_KEY_FLAG_FLAG2}
  DNSSEC_KEY_FLAG_EXTEND = $0008;
  {$EXTERNALSYM DNSSEC_KEY_FLAG_EXTEND}
{$DEFINE DNSSEC_KEY_FLAG_}
  DNSSEC_KEY_FLAG_FLAG4 = $0010;
  {$EXTERNALSYM DNSSEC_KEY_FLAG_FLAG4}
  DNSSEC_KEY_FLAG_FLAG5 = $0020;
  {$EXTERNALSYM DNSSEC_KEY_FLAG_FLAG5}

// bits 6,7 are name type

  DNSSEC_KEY_FLAG_USER  = $0000;
  {$EXTERNALSYM DNSSEC_KEY_FLAG_USER}
  DNSSEC_KEY_FLAG_ZONE  = $0040;
  {$EXTERNALSYM DNSSEC_KEY_FLAG_ZONE}
  DNSSEC_KEY_FLAG_HOST  = $0080;
  {$EXTERNALSYM DNSSEC_KEY_FLAG_HOST}
  DNSSEC_KEY_FLAG_NTPE3 = $00c0;
  {$EXTERNALSYM DNSSEC_KEY_FLAG_NTPE3}

// bits 8-11 are reserved for future use

  DNSSEC_KEY_FLAG_FLAG8  = $0100;
  {$EXTERNALSYM DNSSEC_KEY_FLAG_FLAG8}
  DNSSEC_KEY_FLAG_FLAG9  = $0200;
  {$EXTERNALSYM DNSSEC_KEY_FLAG_FLAG9}
  DNSSEC_KEY_FLAG_FLAG10 = $0400;
  {$EXTERNALSYM DNSSEC_KEY_FLAG_FLAG10}
  DNSSEC_KEY_FLAG_FLAG11 = $0800;
  {$EXTERNALSYM DNSSEC_KEY_FLAG_FLAG11}

// bits 12-15 are sig field

  DNSSEC_KEY_FLAG_SIG0  = $0000;
  {$EXTERNALSYM DNSSEC_KEY_FLAG_SIG0}
  DNSSEC_KEY_FLAG_SIG1  = $1000;
  {$EXTERNALSYM DNSSEC_KEY_FLAG_SIG1}
  DNSSEC_KEY_FLAG_SIG2  = $2000;
  {$EXTERNALSYM DNSSEC_KEY_FLAG_SIG2}
  DNSSEC_KEY_FLAG_SIG3  = $3000;
  {$EXTERNALSYM DNSSEC_KEY_FLAG_SIG3}
  DNSSEC_KEY_FLAG_SIG4  = $4000;
  {$EXTERNALSYM DNSSEC_KEY_FLAG_SIG4}
  DNSSEC_KEY_FLAG_SIG5  = $5000;
  {$EXTERNALSYM DNSSEC_KEY_FLAG_SIG5}
  DNSSEC_KEY_FLAG_SIG6  = $6000;
  {$EXTERNALSYM DNSSEC_KEY_FLAG_SIG6}
  DNSSEC_KEY_FLAG_SIG7  = $7000;
  {$EXTERNALSYM DNSSEC_KEY_FLAG_SIG7}
  DNSSEC_KEY_FLAG_SIG8  = $8000;
  {$EXTERNALSYM DNSSEC_KEY_FLAG_SIG8}
  DNSSEC_KEY_FLAG_SIG9  = $9000;
  {$EXTERNALSYM DNSSEC_KEY_FLAG_SIG9}
  DNSSEC_KEY_FLAG_SIG10 = $a000;
  {$EXTERNALSYM DNSSEC_KEY_FLAG_SIG10}
  DNSSEC_KEY_FLAG_SIG11 = $b000;
  {$EXTERNALSYM DNSSEC_KEY_FLAG_SIG11}
  DNSSEC_KEY_FLAG_SIG12 = $c000;
  {$EXTERNALSYM DNSSEC_KEY_FLAG_SIG12}
  DNSSEC_KEY_FLAG_SIG13 = $d000;
  {$EXTERNALSYM DNSSEC_KEY_FLAG_SIG13}
  DNSSEC_KEY_FLAG_SIG14 = $e000;
  {$EXTERNALSYM DNSSEC_KEY_FLAG_SIG14}
  DNSSEC_KEY_FLAG_SIG15 = $f000;
  {$EXTERNALSYM DNSSEC_KEY_FLAG_SIG15}

//
//  TKEY modes
//

  DNS_TKEY_MODE_SERVER_ASSIGN   = 1;
  {$EXTERNALSYM DNS_TKEY_MODE_SERVER_ASSIGN}
  DNS_TKEY_MODE_DIFFIE_HELLMAN  = 2;
  {$EXTERNALSYM DNS_TKEY_MODE_DIFFIE_HELLMAN}
  DNS_TKEY_MODE_GSS             = 3;
  {$EXTERNALSYM DNS_TKEY_MODE_GSS}
  DNS_TKEY_MODE_RESOLVER_ASSIGN = 4;
  {$EXTERNALSYM DNS_TKEY_MODE_RESOLVER_ASSIGN}

//
//  WINS + NBSTAT flag field
//

  DNS_WINS_FLAG_SCOPE = DWORD($80000000);
  {$EXTERNALSYM DNS_WINS_FLAG_SCOPE}
  DNS_WINS_FLAG_LOCAL = ($00010000);
  {$EXTERNALSYM DNS_WINS_FLAG_LOCAL}

//
//  Helpful checks
//

function IS_WORD_ALIGNED(P: Pointer): BOOL;
{$EXTERNALSYM IS_DWORD_ALIGNED}

function IS_DWORD_ALIGNED(P: Pointer): BOOL;
{$EXTERNALSYM IS_DWORD_ALIGNED}

function IS_QWORD_ALIGNED(P: Pointer): BOOL;
{$EXTERNALSYM IS_QWORD_ALIGNED}

//
//  DNS config API
//

//
//  Types of DNS configuration info
//

type
  DNS_CONFIG_TYPE = (
    //  In Win2K
    DnsConfigPrimaryDomainName_W,
    DnsConfigPrimaryDomainName_A,
    DnsConfigPrimaryDomainName_UTF8,

    //  Not available yet
    DnsConfigAdapterDomainName_W,
    DnsConfigAdapterDomainName_A,
    DnsConfigAdapterDomainName_UTF8,

    //  In Win2K
    DnsConfigDnsServerList,

    //  Not available yet
    DnsConfigSearchList,
    DnsConfigAdapterInfo,

    //  In Win2K
    DnsConfigPrimaryHostNameRegistrationEnabled,
    DnsConfigAdapterHostNameRegistrationEnabled,
    DnsConfigAddressRegistrationMaxCount,

    //  In WindowsXP
    DnsConfigHostName_W,
    DnsConfigHostName_A,
    DnsConfigHostName_UTF8,
    DnsConfigFullHostName_W,
    DnsConfigFullHostName_A,
    DnsConfigFullHostName_UTF8);
  {$EXTERNALSYM DNS_CONFIG_TYPE}
  TDnsConfigType = DNS_CONFIG_TYPE;

//
//  Config API flags
//

//
//  Causes config info to be allocated with LocalAlloc()
//

const
  DNS_CONFIG_FLAG_ALLOC = ($00000001);
  {$EXTERNALSYM DNS_CONFIG_FLAG_ALLOC}

function DnsQueryConfig(Config: DNS_CONFIG_TYPE; Flag: DWORD; pwsAdapterName: PWSTR; pReserved, pBuffer: PVOID; pBufferLength: PDWORD): DNS_STATUS; stdcall;
{$EXTERNALSYM DnsQueryConfig}

//
//  DNS resource record structure
//

//
//  Record data for specific types
//

type
  PDNS_A_DATA = ^DNS_A_DATA;
  {$EXTERNALSYM PDNS_A_DATA}
  DNS_A_DATA = record
    IpAddress: IP4_ADDRESS;
  end;
  {$EXTERNALSYM DNS_A_DATA}
  TDnsAData = DNS_A_DATA;
  PDnsAData = PDNS_A_DATA;

  PDNS_PTR_DATA = ^DNS_PTR_DATA;
  {$EXTERNALSYM PDNS_PTR_DATA}
  DNS_PTR_DATA = record
    pNameHost: LPTSTR;
  end;
  {$EXTERNALSYM DNS_PTR_DATA}
  TDnsPtrData = DNS_PTR_DATA;
  PDnsPtrData = PDNS_PTR_DATA;

  PDNS_SOA_DATA = ^DNS_SOA_DATA;
  {$EXTERNALSYM PDNS_SOA_DATA}
  DNS_SOA_DATA = record
    pNamePrimaryServer: LPTSTR;
    pNameAdministrator: LPTSTR;
    dwSerialNo: DWORD;
    dwRefresh: DWORD;
    dwRetry: DWORD;
    dwExpire: DWORD;
    dwDefaultTtl: DWORD;
  end;
  {$EXTERNALSYM DNS_SOA_DATA}
  TDnsSoaData = DNS_SOA_DATA;
  PDnsSoaData = PDNS_SOA_DATA;

  PDNS_MINFO_DATA = ^DNS_MINFO_DATA;
  {$EXTERNALSYM PDNS_MINFO_DATA}
  DNS_MINFO_DATA = record
    pNameMailbox: LPTSTR;
    pNameErrorsMailbox: LPTSTR;
  end;
  {$EXTERNALSYM DNS_MINFO_DATA}
  TDnsMinfoData = DNS_MINFO_DATA;
  PDnsMinfoData = PDNS_MINFO_DATA;

  PDNS_MX_DATA = ^DNS_MX_DATA;
  {$EXTERNALSYM PDNS_MX_DATA}
  DNS_MX_DATA = record
    pNameExchange: LPTSTR;
    wPreference: WORD;
    Pad: WORD; // keep ptrs DWORD aligned
  end;
  {$EXTERNALSYM DNS_MX_DATA}
  TDnsMxData = DNS_MX_DATA;
  PDnsMxData = PDNS_MX_DATA;

  PDNS_TXT_DATA = ^DNS_TXT_DATA;
  {$EXTERNALSYM PDNS_TXT_DATA}
  DNS_TXT_DATA = record
    dwStringCount: DWORD;
    pStringArray: array [0..0] of LPTSTR;
  end;
  {$EXTERNALSYM DNS_TXT_DATA}
  TDnsTxtData = DNS_TXT_DATA;
  PDnsTxtData = PDNS_TXT_DATA;

  PDNS_NULL_DATA = ^DNS_NULL_DATA;
  {$EXTERNALSYM PDNS_NULL_DATA}
  DNS_NULL_DATA = record
    dwByteCount: DWORD;
    Data: array [0..0] of BYTE;
  end;
  {$EXTERNALSYM DNS_NULL_DATA}
  TDnsNullData = DNS_NULL_DATA;
  PDnsNullData = PDNS_NULL_DATA;

  PDNS_WKS_DATA = ^DNS_WKS_DATA;
  {$EXTERNALSYM PDNS_WKS_DATA}
  DNS_WKS_DATA = record
    IpAddress: IP4_ADDRESS;
    chProtocol: UCHAR;
    BitMask: array [0..0] of BYTE;
  end;
  {$EXTERNALSYM DNS_WKS_DATA}
  TDnsWksData = DNS_WKS_DATA;
  PDnsWksData = PDNS_WKS_DATA;

  PDNS_AAAA_DATA = ^DNS_AAAA_DATA;
  {$EXTERNALSYM PDNS_AAAA_DATA}
  DNS_AAAA_DATA = record
    Ip6Address: DNS_IP6_ADDRESS;
  end;
  {$EXTERNALSYM DNS_AAAA_DATA}
  TDnsAaaaData = DNS_AAAA_DATA;
  PDnsAaaaData = PDNS_AAAA_DATA;

  PDNS_SIG_DATA = ^DNS_SIG_DATA;
  {$EXTERNALSYM PDNS_SIG_DATA}
  DNS_SIG_DATA = record
    pNameSigner: LPTSTR;
    wTypeCovered: WORD;
    chAlgorithm: BYTE;
    chLabelCount: BYTE;
    dwOriginalTtl: DWORD;
    dwExpiration: DWORD;
    dwTimeSigned: DWORD;
    wKeyTag: WORD;
    Pad: WORD; // keep byte field aligned
    Signature: array [0..0] of BYTE;
  end;
  {$EXTERNALSYM DNS_SIG_DATA}
  TDnsSigData = DNS_SIG_DATA;
  PDnsSigData = PDNS_SIG_DATA;

  PDNS_KEY_DATA = ^DNS_KEY_DATA;
  {$EXTERNALSYM PDNS_KEY_DATA}
  DNS_KEY_DATA = record
    wFlags: WORD;
    chProtocol: BYTE;
    chAlgorithm: BYTE;
    Key: array [0..1 - 1] of BYTE;
  end;
  {$EXTERNALSYM DNS_KEY_DATA}
  TDnsKeyData = DNS_KEY_DATA;
  PDnsKeyData = PDNS_KEY_DATA;

  PDNS_LOC_DATA = ^DNS_LOC_DATA;
  {$EXTERNALSYM PDNS_LOC_DATA}
  DNS_LOC_DATA = record
    wVersion: WORD;
    wSize: WORD;
    wHorPrec: WORD;
    wVerPrec: WORD;
    dwLatitude: DWORD;
    dwLongitude: DWORD;
    dwAltitude: DWORD;
  end;
  {$EXTERNALSYM DNS_LOC_DATA}
  TDnsLocData = DNS_LOC_DATA;
  PDnsLocData = PDNS_LOC_DATA;

  PDNS_NXT_DATA = ^DNS_NXT_DATA;
  {$EXTERNALSYM PDNS_NXT_DATA}
  DNS_NXT_DATA = record
    pNameNext: LPTSTR;
    wNumTypes: WORD;
    wTypes: array [0..0] of WORD;
  end;
  {$EXTERNALSYM DNS_NXT_DATA}
  TDnsNxtData = DNS_NXT_DATA;
  PDnsNxtData = PDNS_NXT_DATA;

  PDNS_SRV_DATA = ^DNS_SRV_DATA;
  {$EXTERNALSYM PDNS_SRV_DATA}
  DNS_SRV_DATA = record
    pNameTarget: LPTSTR;
    wPriority: WORD;
    wWeight: WORD;
    wPort: WORD;
    Pad: WORD; // keep ptrs DWORD aligned
  end;
  {$EXTERNALSYM DNS_SRV_DATA}
  TDnsSrvData = DNS_SRV_DATA;
  PDnsSrvData = PDNS_SRV_DATA;

  PDNS_ATMA_DATA = ^DNS_ATMA_DATA;
  {$EXTERNALSYM PDNS_ATMA_DATA}
  DNS_ATMA_DATA = record
    AddressType: BYTE;
    Address: array [0..DNS_ATMA_MAX_ADDR_LENGTH - 1] of BYTE;
    //  E164 -- Null terminated string of less than
    //      DNS_ATMA_MAX_ADDR_LENGTH
    //
    //  For NSAP (AESA) BCD encoding of exactly
    //      DNS_ATMA_AESA_ADDR_LENGTH
  end;
  {$EXTERNALSYM DNS_ATMA_DATA}
  TDnsAtmaData = DNS_ATMA_DATA;
  PDnsAtmaData = PDNS_ATMA_DATA;

  PDNS_TKEY_DATA = ^DNS_TKEY_DATA;
  {$EXTERNALSYM PDNS_TKEY_DATA}
  DNS_TKEY_DATA = record
    pNameAlgorithm: LPTSTR;
    pAlgorithmPacket: PBYTE;
    pKey: PBYTE;
    pOtherData: PBYTE;
    dwCreateTime: DWORD;
    dwExpireTime: DWORD;
    wMode: WORD;
    wError: WORD;
    wKeyLength: WORD;
    wOtherLength: WORD;
    cAlgNameLength: UCHAR;
    bPacketPointers: BOOL;
  end;
  {$EXTERNALSYM DNS_TKEY_DATA}
  TDnsTkeyData = DNS_TKEY_DATA;
  PDnsTkeyData = PDNS_TKEY_DATA;

  PDNS_TSIG_DATA = ^DNS_TSIG_DATA;
  {$EXTERNALSYM PDNS_TSIG_DATA}
  DNS_TSIG_DATA = record
    pNameAlgorithm: LPTSTR;
    pAlgorithmPacket: PBYTE;
    pSignature: PBYTE;
    pOtherData: PBYTE;
    i64CreateTime: LONGLONG;
    wFudgeTime: WORD;
    wOriginalXid: WORD;
    wError: WORD;
    wSigLength: WORD;
    wOtherLength: WORD;
    cAlgNameLength: UCHAR;
    bPacketPointers: BOOL;
  end;
  {$EXTERNALSYM DNS_TSIG_DATA}
  TDnsTsigData = DNS_TSIG_DATA;
  PDnsTsigData = PDNS_TSIG_DATA;


//
//  MS only types -- only hit the wire in MS-MS zone transfer
//

  PDNS_WINS_DATA = ^DNS_WINS_DATA;
  {$EXTERNALSYM PDNS_WINS_DATA}
  DNS_WINS_DATA = record
    dwMappingFlag: DWORD;
    dwLookupTimeout: DWORD;
    dwCacheTimeout: DWORD;
    cWinsServerCount: DWORD;
    WinsServers: array [0..0] of IP4_ADDRESS;
  end;
  {$EXTERNALSYM DNS_WINS_DATA}
  TDnsWinsData = DNS_WINS_DATA;
  PDnsWinsData = PDNS_WINS_DATA;

  PDNS_WINSR_DATA = ^DNS_WINSR_DATA;
  {$EXTERNALSYM PDNS_WINSR_DATA}
  DNS_WINSR_DATA = record
    dwMappingFlag: DWORD;
    dwLookupTimeout: DWORD;
    dwCacheTimeout: DWORD;
    pNameResultDomain: LPTSTR;
  end;
  {$EXTERNALSYM DNS_WINSR_DATA}
  TDnsWinsrData = DNS_WINSR_DATA;
  PDnsWinsrData = PDNS_WINSR_DATA;

//
//  Length of non-fixed-length data types
//

function DNS_TEXT_RECORD_LENGTH(StringCount: Integer): Integer;
{$EXTERNALSYM DNS_TEXT_RECORD_LENGTH}

function DNS_NULL_RECORD_LENGTH(ByteCount: Integer): Integer;
{$EXTERNALSYM DNS_NULL_RECORD_LENGTH}

function DNS_WKS_RECORD_LENGTH(ByteCount: Integer): Integer;
{$EXTERNALSYM DNS_WKS_RECORD_LENGTH}

//function DNS_WINS_RECORD_LENGTH(IpCount: Integer): Integer;
//{$EXTERNALSYM DNS_WINS_RECORD_LENGTH}

//
//  Record flags
//

type
  _DnsRecordFlags = record
    //DWORD   Section     : 2;
    //DWORD   Delete      : 1;
    //DWORD   CharSet     : 2;
    //DWORD   Unused      : 3;
    //DWORD   Reserved    : 24;
    Flags: DWORD;
  end;
  {$EXTERNALSYM _DnsRecordFlags}
  DNS_RECORD_FLAGS = _DnsRecordFlags;
  {$EXTERNALSYM DNS_RECORD_FLAGS}
  TDnsRecordFlags = DNS_RECORD_FLAGS;
  PDnsRecordFlags = ^DNS_RECORD_FLAGS;

//
//  Wire Record Sections
//
//  Useable both in record flags "Section" and as index into
//  wire message header section counts.
//

  _DnsSection = (
    DnsSectionQuestion,
    DnsSectionAnswer,
    DnsSectionAuthority,
    DnsSectionAddtional);
  {$EXTERNALSYM _DnsSection}
  DNS_SECTION = _DnsSection;
  TDnsSection = _DnsSection;

//  Update message section names

const
  DnsSectionZone   = DnsSectionQuestion;
  {$EXTERNALSYM DnsSectionZone}
  DnsSectionPrereq = DnsSectionAnswer;
  {$EXTERNALSYM DnsSectionPrereq}
  DnsSectionUpdate = DnsSectionAuthority;
  {$EXTERNALSYM DnsSectionUpdate}

//
//  Record flags as bit flags
//  These may be or'd together to set the fields
//

//  RR Section in packet

  DNSREC_SECTION = ($00000003);
  {$EXTERNALSYM DNSREC_SECTION}

  DNSREC_QUESTION   = ($00000000);
  {$EXTERNALSYM DNSREC_QUESTION}
  DNSREC_ANSWER     = ($00000001);
  {$EXTERNALSYM DNSREC_ANSWER}
  DNSREC_AUTHORITY  = ($00000002);
  {$EXTERNALSYM DNSREC_AUTHORITY}
  DNSREC_ADDITIONAL = ($00000003);
  {$EXTERNALSYM DNSREC_ADDITIONAL}

//  RR Section in packet (update)

  DNSREC_ZONE   = ($00000000);
  {$EXTERNALSYM DNSREC_ZONE}
  DNSREC_PREREQ = ($00000001);
  {$EXTERNALSYM DNSREC_PREREQ}
  DNSREC_UPDATE = ($00000002);
  {$EXTERNALSYM DNSREC_UPDATE}

//  Delete RR (update) or No-exist (prerequisite)

  DNSREC_DELETE  = ($00000004);
  {$EXTERNALSYM DNSREC_DELETE}
  DNSREC_NOEXIST = ($00000004);
  {$EXTERNALSYM DNSREC_NOEXIST}

//
//  Record \ RR set structure
//
//  Note:  The dwReserved flag serves to insure that the substructures
//  start on 64-bit boundaries.  Do NOT pack this structure, as the
//  substructures may contain pointers or int64 values which are
//  properly aligned unpacked.
//

type
  PDNS_RECORD = ^DNS_RECORD;
  {$EXTERNALSYM PDNS_RECORD}
  _DnsRecord = record
    pNext: PDNS_RECORD;
    pName: LPTSTR;
    wType: WORD;
    wDataLength: WORD; // Not referenced for DNS record types defined above.
    Flags: record
    case Integer of
      0: (DW: DWORD);             // flags as DWORD
      1: (S: DNS_RECORD_FLAGS);   // flags as structure
    end;
    dwTtl: DWORD;
    dwReserved: DWORD;

    //  Record Data

    Data: record
    case Integer of
       0: (A: DNS_A_DATA);
       1: (SOA, Soa_: DNS_SOA_DATA);
       2: (PTR, Ptr_,
           NS, Ns_,
           CNAME, Cname_,
           MB, Mb_,
           MD, Md_,
           MF, Mf_,
           MG, Mg_,
           MR, Mr_: DNS_PTR_DATA);
       3: (MINFO, Minfo_,
           RP, Rp_: DNS_MINFO_DATA);
       4: (MX, Mx_,
           AFSDB, Afsdb_,
           RT, Rt_: DNS_MX_DATA);
       5: (HINFO, Hinfo_,
           ISDN, Isdn_,
           TXT, Txt_,
           X25: DNS_TXT_DATA);
       6: (Null: DNS_NULL_DATA);
       7: (WKS, Wks_: DNS_WKS_DATA);
       8: (AAAA: DNS_AAAA_DATA);
       9: (KEY, Key_: DNS_KEY_DATA);
      10: (SIG, Sig_: DNS_SIG_DATA);
      11: (ATMA, Atma_: DNS_ATMA_DATA);
      12: (NXT, Nxt_: DNS_NXT_DATA);
      13: (SRV, Srv_: DNS_SRV_DATA);
      14: (TKEY, Tkey_: DNS_TKEY_DATA);
      15: (TSIG, Tsig_: DNS_TSIG_DATA);
      16: (WINS, Wins_: DNS_WINS_DATA);
      17: (WINSR, WinsR_, NBSTAT, Nbstat_: DNS_WINSR_DATA);
    end;
   end;
  {$EXTERNALSYM _DnsRecord}
  DNS_RECORD = _DnsRecord;
  {$EXTERNALSYM DNS_RECORD}
  PPDNS_RECORD = ^PDNS_RECORD;
  {$NODEFINE PPDNS_RECORD}
  TDnsRecord = DNS_RECORD;
  PDnsRecord = PDNS_RECORD;

//
//  Header or fixed size of DNS_RECORD
//

const
  DNS_RECORD_FIXED_SIZE = 24;                // FIELD_OFFSET( DNS_RECORD, Data )
  {$EXTERNALSYM DNS_RECORD_FIXED_SIZE}
  SIZEOF_DNS_RECORD_HEADER = DNS_RECORD_FIXED_SIZE;
  {$EXTERNALSYM SIZEOF_DNS_RECORD_HEADER}

//
//  Resource record set building
//
//  pFirst points to first record in list.
//  pLast points to last record in list.
//

type
  PDnsRRSet = ^DnsRRSet;
  {$EXTERNALSYM PDnsRRSet}
  _DnsRRSet = record
    pFirstRR: PDNS_RECORD;
    pLastRR: PDNS_RECORD;
  end;
  {$EXTERNALSYM _DnsRRSet}
  DnsRRSet = _DnsRRSet;
  {$EXTERNALSYM DnsRRSet}
  TDnsrrset = DnsRRSet;

//
//  To init pFirst is NULL.
//  But pLast points at the location of the pFirst pointer -- essentially
//  treating the pFirst ptr as a DNS_RECORD.  (It is a DNS_RECORD with
//  only a pNext field, but that's the only part we use.)
//
//  Then when the first record is added to the list, the pNext field of
//  this dummy record (which corresponds to pFirst's value) is set to
//  point at the first record.  So pFirst then properly points at the
//  first record.
//
//  (This works only because pNext is the first field in a
//  DNS_RECORD structure and hence casting a PDNS_RECORD ptr to
//  PDNS_RECORD* and dereferencing yields its pNext field)
//
//  Use TERMINATE when have built RR set by grabbing records out of
//  existing set.   This makes sure that at the end, the last RR is
//  properly NULL terminated.
//

procedure DNS_RRSET_INIT(rrset: PDnsRRSet);
{$EXTERNALSYM DNS_RRSET_INIT}

//procedure DNS_RRSET_ADD(rrset, pnewRR: PDNS_RRSET);
//{$EXTERNALSYM DNS_RRSET_ADD}

procedure DNS_RRSET_TERMINATE(rrset: PDnsRRSet);
{$EXTERNALSYM DNS_RRSET_TERMINATE}

//
//  Record set manipulation
//

//
//  Record Copy
//  Record copy functions also do conversion between character sets.
//
//  Note, it might be advisable to directly expose non-Ex copy
//  functions _W, _A for record and set, to avoid exposing the
//  conversion enum.
//

type
  _DNS_CHARSET = (
    DnsCharSetUnknown,
    DnsCharSetUnicode,
    DnsCharSetUtf8,
    DnsCharSetAnsi);
  {$EXTERNALSYM _DNS_CHARSET}
  DNS_CHARSET = _DNS_CHARSET;
  {$EXTERNALSYM DNS_CHARSET}
  TDnsCharSet = DNS_CHARSET;
  PDnsCharSet = ^DNS_CHARSET;

function DnsRecordCopyEx(pRecord: PDNS_RECORD; CharSetIn: DNS_CHARSET; CharSetOut: DNS_CHARSET): PDNS_RECORD; stdcall;
{$EXTERNALSYM DnsRecordCopyEx}

function DnsRecordSetCopyEx(pRecordSet: PDNS_RECORD; CharSetIn: DNS_CHARSET; CharSetOut: DNS_CHARSET): PDNS_RECORD; stdcall;
{$EXTERNALSYM DnsRecordSetCopyEx}

{$IFDEF UNICODE}

function DnsRecordCopy(pRR: PDNS_RECORD): PDNS_RECORD;
{$EXTERNALSYM DnsRecordCopy}

function DnsRecordSetCopy(pRR: PDNS_RECORD): PDNS_RECORD;
{$EXTERNALSYM DnsRecordSetCopy}

{$ELSE}

function DnsRecordCopy(pRR: PDNS_RECORD): PDNS_RECORD;
{$EXTERNALSYM DnsRecordCopy}

function DnsRecordSetCopy(pRR: PDNS_RECORD): PDNS_RECORD;
{$EXTERNALSYM DnsRecordSetCopy}

{$ENDIF}

//
//  Record Compare
//
//  Note:  these routines only compare records of the SAME character set.
//  (ANSI, unicode or UTF8).  Furthermore the routines assume the character
//  set is indicated within the record.  If compare of user created, rather
//  than DNS API created record lists is desired, then caller should use
//  DnsRecordCopy API and compare copies.
//

function DnsRecordCompare(pRecord1: PDNS_RECORD; pRecord2: PDNS_RECORD): BOOL; stdcall;
{$EXTERNALSYM DnsRecordCompare}

function DnsRecordSetCompare(pRR1: PDNS_RECORD; pRR2: PDNS_RECORD; var ppDiff1, ppDiff2: PDNS_RECORD): BOOL; stdcall;
{$EXTERNALSYM DnsRecordSetCompare}

//
//  Detach next record set from record list
//

function DnsRecordSetDetach(pRecordList: PDNS_RECORD): PDNS_RECORD; stdcall;
{$EXTERNALSYM DnsRecordSetDetach}

//
//  Free record list
//
//  Only supported free is deep free of entire record list with LocalFree().
//  This correctly frees record list returned by DnsQuery() or DnsRecordSetCopy()
//

type
  DNS_FREE_TYPE = (DnsFreeFlat, DnsFreeRecordList);
  {$EXTERNALSYM DNS_FREE_TYPE}
  TDnsFreeType = DNS_FREE_TYPE;

procedure DnsFreeRecordListDeep(pRecordList: PDNS_RECORD; FreeType: DNS_FREE_TYPE); stdcall;
{$EXTERNALSYM DnsFreeRecordListDeep}

procedure DnsRecordListFree(pRecordList: PDNS_RECORD; FreeType: DNS_FREE_TYPE); stdcall;
{$EXTERNALSYM DnsRecordListFree}

procedure DnsFree(pData: PVOID; FreeType: DNS_FREE_TYPE); stdcall;
{$EXTERNALSYM DnsFree}

//
//  DNS Query API
//

//
//  Options for DnsQuery
//

const
  DNS_QUERY_STANDARD                  = $00000000;
  {$EXTERNALSYM DNS_QUERY_STANDARD}
  DNS_QUERY_ACCEPT_TRUNCATED_RESPONSE = $00000001;
  {$EXTERNALSYM DNS_QUERY_ACCEPT_TRUNCATED_RESPONSE}
  DNS_QUERY_USE_TCP_ONLY              = $00000002;
  {$EXTERNALSYM DNS_QUERY_USE_TCP_ONLY}
  DNS_QUERY_NO_RECURSION              = $00000004;
  {$EXTERNALSYM DNS_QUERY_NO_RECURSION}
  DNS_QUERY_BYPASS_CACHE              = $00000008;
  {$EXTERNALSYM DNS_QUERY_BYPASS_CACHE}

  DNS_QUERY_NO_WIRE_QUERY = $00000010;
  {$EXTERNALSYM DNS_QUERY_NO_WIRE_QUERY}
  DNS_QUERY_NO_LOCAL_NAME = $00000020;
  {$EXTERNALSYM DNS_QUERY_NO_LOCAL_NAME}
  DNS_QUERY_NO_HOSTS_FILE = $00000040;
  {$EXTERNALSYM DNS_QUERY_NO_HOSTS_FILE}
  DNS_QUERY_NO_NETBT      = $00000080;
  {$EXTERNALSYM DNS_QUERY_NO_NETBT}

  DNS_QUERY_WIRE_ONLY      = $00000100;
  {$EXTERNALSYM DNS_QUERY_WIRE_ONLY}
  DNS_QUERY_RETURN_MESSAGE = $00000200;
  {$EXTERNALSYM DNS_QUERY_RETURN_MESSAGE}

  DNS_QUERY_TREAT_AS_FQDN         = $00001000;
  {$EXTERNALSYM DNS_QUERY_TREAT_AS_FQDN}
  DNS_QUERY_DONT_RESET_TTL_VALUES = $00100000;
  {$EXTERNALSYM DNS_QUERY_DONT_RESET_TTL_VALUES}
  DNS_QUERY_RESERVED              = DWORD($ff000000);
  {$EXTERNALSYM DNS_QUERY_RESERVED}

//  Backward compatibility with Win2K
//  Do not use

  DNS_QUERY_CACHE_ONLY = DNS_QUERY_NO_WIRE_QUERY;
  {$EXTERNALSYM DNS_QUERY_CACHE_ONLY}

function DnsQuery_A(pszName: PCSTR; wType: WORD; Options: DWORD; aipServers: PIP4_ARRAY; ppQueryResults: PPDNS_RECORD; pReserved: PPVOID): DNS_STATUS; stdcall;
{$EXTERNALSYM DnsQuery_A}

function DnsQuery_UTF8(pszName: PCSTR; wType: WORD; Options: DWORD; aipServers: PIP4_ARRAY; ppQueryResults: PPDNS_RECORD; pReserved: PPVOID): DNS_STATUS; stdcall;
{$EXTERNALSYM DnsQuery_UTF8}

function DnsQuery_W(pszName: LPCWSTR; wType: WORD; Options: DWORD; aipServers: PIP4_ARRAY; ppQueryResults: PPDNS_RECORD; pReserved: PPVOID): DNS_STATUS; stdcall;
{$EXTERNALSYM DnsQuery_W}

{$IFDEF UNICODE}
function DnsQuery(pszName: LPCWSTR; wType: WORD; Options: DWORD; aipServers: PIP4_ARRAY; ppQueryResults: PPDNS_RECORD; pReserved: PPVOID): DNS_STATUS; stdcall;
{$EXTERNALSYM DnsQuery}
{$ELSE}
function DnsQuery(pszName: PCSTR; wType: WORD; Options: DWORD; aipServers: PIP4_ARRAY; ppQueryResults: PPDNS_RECORD; pReserved: PPVOID): DNS_STATUS; stdcall;
{$EXTERNALSYM DnsQuery}
{$ENDIF}

//
//  DNS Update API
//
//      DnsAcquireContextHandle
//      DnsReleaseContextHandle
//      DnsModifyRecordsInSet
//      DnsReplaceRecordSet
//

//
//  Update flags
//

const
  DNS_UPDATE_SECURITY_USE_DEFAULT    = $00000000;
  {$EXTERNALSYM DNS_UPDATE_SECURITY_USE_DEFAULT}
  DNS_UPDATE_SECURITY_OFF            = $00000010;
  {$EXTERNALSYM DNS_UPDATE_SECURITY_OFF}
  DNS_UPDATE_SECURITY_ON             = $00000020;
  {$EXTERNALSYM DNS_UPDATE_SECURITY_ON}
  DNS_UPDATE_SECURITY_ONLY           = $00000100;
  {$EXTERNALSYM DNS_UPDATE_SECURITY_ONLY}
  DNS_UPDATE_CACHE_SECURITY_CONTEXT  = $00000200;
  {$EXTERNALSYM DNS_UPDATE_CACHE_SECURITY_CONTEXT}
  DNS_UPDATE_TEST_USE_LOCAL_SYS_ACCT = $00000400;
  {$EXTERNALSYM DNS_UPDATE_TEST_USE_LOCAL_SYS_ACCT}
  DNS_UPDATE_FORCE_SECURITY_NEGO     = $00000800;
  {$EXTERNALSYM DNS_UPDATE_FORCE_SECURITY_NEGO}
  DNS_UPDATE_TRY_ALL_MASTER_SERVERS  = $00001000;
  {$EXTERNALSYM DNS_UPDATE_TRY_ALL_MASTER_SERVERS}
  DNS_UPDATE_SKIP_NO_UPDATE_ADAPTERS = $00002000;
  {$EXTERNALSYM DNS_UPDATE_SKIP_NO_UPDATE_ADAPTERS}
  DNS_UPDATE_RESERVED                = DWORD($ffff0000);
  {$EXTERNALSYM DNS_UPDATE_RESERVED}

//
//  Note:  pCredentials paramater is currently respectively
//  PSEC_WINNT_AUTH_IDENTITY_W or PSEC_WINNT_AUTH_IDENTITY_A.
//  Using PVOID to obviate the need for including rpcdce.h
//  in order to include this file and to leave open the
//  possibility of alternative credential specifications in
//  the future.
//

function DnsAcquireContextHandle_W(CredentialFlags: DWORD; pCredentials: PVOID; pContextHandle: PHANDLE): DNS_STATUS; stdcall;
{$EXTERNALSYM DnsAcquireContextHandle_W}

function DnsAcquireContextHandle_A(CredentialFlags: DWORD; pCredentials: PVOID; pContextHandle: PHANDLE): DNS_STATUS; stdcall;
{$EXTERNALSYM DnsAcquireContextHandle_A}

{$IFDEF UNICODE}
function DnsAcquireContextHandle(CredentialFlags: DWORD; pCredentials: PVOID; pContextHandle: PHANDLE): DNS_STATUS; stdcall;
{$EXTERNALSYM DnsAcquireContextHandle}
{$ELSE}
function DnsAcquireContextHandle(CredentialFlags: DWORD; pCredentials: PVOID; pContextHandle: PHANDLE): DNS_STATUS; stdcall;
{$EXTERNALSYM DnsAcquireContextHandle}
{$ENDIF}

procedure DnsReleaseContextHandle(hContext: HANDLE); stdcall;
{$EXTERNALSYM DnsReleaseContextHandle}

//
//  Dynamic Update API
//

function DnsModifyRecordsInSet_W(pAddRecords: PDNS_RECORD; pDeleteRecords: PDNS_RECORD; Options: DWORD; hContext: HANDLE; pServerList: PIP4_ARRAY; pReserved: PVOID): DNS_STATUS; stdcall;
{$EXTERNALSYM DnsModifyRecordsInSet_W}

function DnsModifyRecordsInSet_A(pAddRecords: PDNS_RECORD; pDeleteRecords: PDNS_RECORD; Options: DWORD; hContext: HANDLE; pServerList: PIP4_ARRAY; pReserved: PVOID): DNS_STATUS; stdcall;
{$EXTERNALSYM DnsModifyRecordsInSet_A}

function DnsModifyRecordsInSet_UTF8(pAddRecords: PDNS_RECORD; pDeleteRecords: PDNS_RECORD; Options: DWORD; hContext: HANDLE; pServerList: PIP4_ARRAY; pReserved: PVOID): DNS_STATUS; stdcall;
{$EXTERNALSYM DnsModifyRecordsInSet_UTF8}

{$IFDEF UNICODE}
function DnsModifyRecordsInSet(pAddRecords: PDNS_RECORD; pDeleteRecords: PDNS_RECORD; Options: DWORD; hContext: HANDLE; pServerList: PIP4_ARRAY; pReserved: PVOID): DNS_STATUS; stdcall;
{$EXTERNALSYM DnsModifyRecordsInSet}
{$ELSE}
function DnsModifyRecordsInSet(pAddRecords: PDNS_RECORD; pDeleteRecords: PDNS_RECORD; Options: DWORD; hContext: HANDLE; pServerList: PIP4_ARRAY; pReserved: PVOID): DNS_STATUS; stdcall;
{$EXTERNALSYM DnsModifyRecordsInSet}
{$ENDIF}

function DnsReplaceRecordSetW(pNewSet: PDNS_RECORD; Options: DWORD; hContext: HANDLE; pServerList: PIP4_ARRAY; pReserved: PVOID): DNS_STATUS; stdcall;
{$EXTERNALSYM DnsReplaceRecordSetW}

function DnsReplaceRecordSetA(pNewSet: PDNS_RECORD; Options: DWORD; hContext: HANDLE; pServerList: PIP4_ARRAY; pReserved: PVOID): DNS_STATUS; stdcall;
{$EXTERNALSYM DnsReplaceRecordSetA}

function DnsReplaceRecordSetUTF8(pNewSet: PDNS_RECORD; Options: DWORD; hContext: HANDLE; pServerList: PIP4_ARRAY; pReserved: PVOID): DNS_STATUS; stdcall;
{$EXTERNALSYM DnsReplaceRecordSetUTF8}

{$IFDEF UNICODE}
function DnsReplaceRecordSet(pNewSet: PDNS_RECORD; Options: DWORD; hContext: HANDLE; pServerList: PIP4_ARRAY; pReserved: PVOID): DNS_STATUS; stdcall;
{$EXTERNALSYM DnsReplaceRecordSet}
{$ELSE}
function DnsReplaceRecordSet(pNewSet: PDNS_RECORD; Options: DWORD; hContext: HANDLE; pServerList: PIP4_ARRAY; pReserved: PVOID): DNS_STATUS; stdcall;
{$EXTERNALSYM DnsReplaceRecordSet}
{$ENDIF}

//
//  DNS name validation
//

type
  _DNS_NAME_FORMAT = (
    DnsNameDomain,
    DnsNameDomainLabel,
    DnsNameHostnameFull,
    DnsNameHostnameLabel,
    DnsNameWildcard,
    DnsNameSrvRecord);
  {$EXTERNALSYM _DNS_NAME_FORMAT}
  DNS_NAME_FORMAT = _DNS_NAME_FORMAT;
  {$EXTERNALSYM DNS_NAME_FORMAT}
  TDnsNameFormat = DNS_NAME_FORMAT;
  PDnsNameFormat = ^DNS_NAME_FORMAT;

function DnsValidateName_UTF8(pszName: LPCSTR; Format: DNS_NAME_FORMAT): DNS_STATUS; stdcall;
{$EXTERNALSYM DnsValidateName_UTF8}

function DnsValidateName_W(pwszName: LPCWSTR; Format: DNS_NAME_FORMAT): DNS_STATUS; stdcall;
{$EXTERNALSYM DnsValidateName_W}

function DnsValidateName_A(pszName: LPCSTR; Format: DNS_NAME_FORMAT): DNS_STATUS; stdcall;
{$EXTERNALSYM DnsValidateName_A}

{$IFDEF UNICODE}

function DnsValidateName(pszName: LPCWSTR; Format: DNS_NAME_FORMAT): DNS_STATUS;
{$EXTERNALSYM DnsValidateName}

{$ELSE}

function DnsValidateName(pszName: LPCSTR; Format: DNS_NAME_FORMAT): DNS_STATUS;
{$EXTERNALSYM DnsValidateName}

{$ENDIF}

//
//  DNS name comparison
//

function DnsNameCompare_A(pName1: LPSTR; pName2: LPSTR): BOOL; stdcall;
{$EXTERNALSYM DnsNameCompare_A}

function DnsNameCompare_W(pName1: LPWSTR; pName2: LPWSTR): BOOL; stdcall;
{$EXTERNALSYM DnsNameCompare_W}

{$IFDEF UNICODE}
function DnsNameCompare(pName1: LPWSTR; pName2: LPWSTR): BOOL; stdcall;
{$EXTERNALSYM DnsNameCompare}
{$ELSE}
function DnsNameCompare(pName1: LPSTR; pName2: LPSTR): BOOL; stdcall;
{$EXTERNALSYM DnsNameCompare}
{$ENDIF}

//
//  DNS message "roll-your-own" routines
//

type
  PDNS_MESSAGE_BUFFER = ^DNS_MESSAGE_BUFFER;
  {$EXTERNALSYM PDNS_MESSAGE_BUFFER}
  _DNS_MESSAGE_BUFFER = record
    MessageHead: DNS_HEADER;
    MessageBody: array [0..0] of CHAR;
  end;
  {$EXTERNALSYM _DNS_MESSAGE_BUFFER}
  DNS_MESSAGE_BUFFER = _DNS_MESSAGE_BUFFER;
  {$EXTERNALSYM DNS_MESSAGE_BUFFER}
  TDnsMessageBuffer = DNS_MESSAGE_BUFFER;
  PDnsMessageBuffer = PDNS_MESSAGE_BUFFER;

function DnsWriteQuestionToBuffer_W(pDnsBuffer: PDNS_MESSAGE_BUFFER; pdwBufferSize: LPDWORD; pszName: LPWSTR; wType: WORD; Xid: WORD; fRecursionDesired: BOOL): BOOL; stdcall;
{$EXTERNALSYM DnsWriteQuestionToBuffer_W}

function DnsWriteQuestionToBuffer_UTF8(pDnsBuffer: PDNS_MESSAGE_BUFFER; pdwBufferSize: LPDWORD; pszName: LPSTR; wType: WORD; Xid: WORD; fRecursionDesired: BOOL): BOOL; stdcall;
{$EXTERNALSYM DnsWriteQuestionToBuffer_UTF8}

function DnsExtractRecordsFromMessage_W(pDnsBuffer: PDNS_MESSAGE_BUFFER; wMessageLength: WORD; ppRecord: PPDNS_RECORD): DNS_STATUS; stdcall;
{$EXTERNALSYM DnsExtractRecordsFromMessage_W}

function DnsExtractRecordsFromMessage_UTF8(pDnsBuffer: PDNS_MESSAGE_BUFFER; wMessageLength: WORD; ppRecord: PPDNS_RECORD): DNS_STATUS; stdcall;
{$EXTERNALSYM DnsExtractRecordsFromMessage_UTF8}

implementation

const
  dnsapi = 'dnsapi.dll';

procedure INLINE_WORD_FLIP(var Out: WORD; In_: WORD);
begin
  Out := (In_ shl 8) or (In_ shr 8);
end;

procedure INLINE_HTONS(var Out: WORD; In_: WORD);
begin
  INLINE_WORD_FLIP(Out, In_);
end;

procedure INLINE_NTOHS(var Out: WORD; In_: WORD);
begin
  INLINE_WORD_FLIP(Out, In_);
end;

procedure INLINE_DWORD_FLIP(var Out: DWORD; In_: DWORD);
begin
  Out := ((In_ shl 8) and $00ff0000) or (In_ shl 24) or
    ((In_ shr 8) and $0000ff00) or (In_ shr 24);
end;

procedure INLINE_NTOHL(var Out: DWORD; In_: DWORD);
begin
  INLINE_DWORD_FLIP(Out, In_);
end;

procedure INLINE_HTONL(var Out: DWORD; In_: DWORD);
begin
  INLINE_DWORD_FLIP(Out, In_);
end;

procedure INLINE_WRITE_FLIPPED_WORD(pout: PWORD; In_: WORD);
begin
  INLINE_WORD_FLIP(pout^, In_);
end;

procedure INLINE_WRITE_FLIPPED_DWORD(pout: PDWORD; In_: DWORD);
begin
  INLINE_DWORD_FLIP(pout^, In_);
end;

function DNS_HEADER_FLAGS(pHead: PDNS_HEADER): WORD;
begin
  Result := PWORD(Integer(pHead) + SizeOf(WORD))^;
end;

procedure DNS_BYTE_FLIP_HEADER_COUNTS(var pHeader: PDNS_HEADER);
var
  _head: PDNS_HEADER;
begin
  _head := pHeader;
  INLINE_HTONS(_head^.Xid, _head^.Xid);
  INLINE_HTONS(_head^.QuestionCount, _head^.QuestionCount);
  INLINE_HTONS(_head^.AnswerCount, _head^.AnswerCount);
  INLINE_HTONS(_head^.NameServerCount, _head^.NameServerCount);
  INLINE_HTONS(_head^.AdditionalCount, _head^.AdditionalCount);
end;

{
#define DNS_QUESTION_NAME_FROM_HEADER( _pHeader_ ) \
            ( (PCHAR)( (PDNS_HEADER)(_pHeader_) + 1 ) )

#define DNS_ANSWER_FROM_QUESTION( _pQuestion_ ) \
            ( (PCHAR)( (PDNS_QUESTION)(_pQuestion_) + 1 ) )
}

function IS_WORD_ALIGNED(P: Pointer): BOOL;
begin
  Result := (Integer(P) and 1) = 0;
end;

function IS_DWORD_ALIGNED(P: Pointer): BOOL;
begin
  Result := (Integer(P) and 3) = 0;
end;

function IS_QWORD_ALIGNED(P: Pointer): BOOL;
begin
  Result := (Integer(P) and 7) = 0;
end;


{$IFDEF DYNAMIC_LINK}
var
  _DnsQueryConfig: Pointer;

function DnsQueryConfig;
begin
  GetProcedureAddress(_DnsQueryConfig, dnsapi, 'DnsQueryConfig');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DnsQueryConfig]
  end;
end;
{$ELSE}
function DnsQueryConfig; external dnsapi name 'DnsQueryConfig';
{$ENDIF DYNAMIC_LINK}

function DNS_TEXT_RECORD_LENGTH(StringCount: Integer): Integer;
begin
  Result := SizeOf(DWORD) + ((StringCount) * SizeOf(PChar));
end;

function DNS_NULL_RECORD_LENGTH(ByteCount: Integer): Integer;
begin
  Result := SizeOf(DWORD) + (ByteCount);
end;

function DNS_WKS_RECORD_LENGTH(ByteCount: Integer): Integer;
begin
  Result := SizeOf(DNS_WKS_DATA) + (ByteCount - 1);
end;

//#define DNS_WINS_RECORD_LENGTH(IpCount) \
//            (FIELD_OFFSET(DNS_WINS_DATA, WinsServers) + ((IpCount) * sizeof(IP4_ADDRESS)))


procedure DNS_RRSET_INIT(rrset: PDnsRRSet);
begin
  rrset^.pFirstRR := nil;
  rrset^.pLastRR := (@rrset^.pFirstRR);
end;

//#define DNS_RRSET_ADD( rrset, pnewRR )          \
//        {                                       \
//            PDNS_RRSET  _prrset = &(rrset);     \
//            PDNS_RECORD _prrnew = (pnewRR);     \
//            _prrset->pLastRR->pNext = _prrnew;  \
//            _prrset->pLastRR = _prrnew;         \
//        }

procedure DNS_RRSET_TERMINATE(rrset: PDnsRRSet);
begin
  rrset^.pLastRR^.pNext := nil;
end;


{$IFDEF DYNAMIC_LINK}
var
  _DnsRecordCopyEx: Pointer;

function DnsRecordCopyEx;
begin
  GetProcedureAddress(_DnsRecordCopyEx, dnsapi, 'DnsRecordCopyEx');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DnsRecordCopyEx]
  end;
end;
{$ELSE}
function DnsRecordCopyEx; external dnsapi name 'DnsRecordCopyEx';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DnsRecordSetCopyEx: Pointer;

function DnsRecordSetCopyEx;
begin
  GetProcedureAddress(_DnsRecordSetCopyEx, dnsapi, 'DnsRecordSetCopyEx');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DnsRecordSetCopyEx]
  end;
end;
{$ELSE}
function DnsRecordSetCopyEx; external dnsapi name 'DnsRecordSetCopyEx';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}
function DnsRecordCopy(pRR: PDNS_RECORD): PDNS_RECORD;
begin
  Result := DnsRecordCopyEx(pRR, DnsCharSetUnicode, DnsCharSetUnicode);
end;

function DnsRecordSetCopy(pRR: PDNS_RECORD): PDNS_RECORD;
begin
  Result := DnsRecordSetCopyEx(pRR, DnsCharSetUnicode, DnsCharSetUnicode);
end;
{$ELSE}
function DnsRecordCopy(pRR: PDNS_RECORD): PDNS_RECORD;
begin
  Result := DnsRecordCopyEx(pRR, DnsCharSetAnsi, DnsCharSetAnsi);
end;

function DnsRecordSetCopy(pRR: PDNS_RECORD): PDNS_RECORD;
begin
  Result := DnsRecordSetCopyEx(pRR, DnsCharSetAnsi, DnsCharSetAnsi);
end;
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _DnsRecordCompare: Pointer;

function DnsRecordCompare;
begin
  GetProcedureAddress(_DnsRecordCompare, dnsapi, 'DnsRecordCompare');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DnsRecordCompare]
  end;
end;
{$ELSE}
function DnsRecordCompare; external dnsapi name 'DnsRecordCompare';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DnsRecordSetCompare: Pointer;

function DnsRecordSetCompare;
begin
  GetProcedureAddress(_DnsRecordSetCompare, dnsapi, 'DnsRecordSetCompare');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DnsRecordSetCompare]
  end;
end;
{$ELSE}
function DnsRecordSetCompare; external dnsapi name 'DnsRecordSetCompare';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DnsRecordSetDetach: Pointer;

function DnsRecordSetDetach;
begin
  GetProcedureAddress(_DnsRecordSetDetach, dnsapi, 'DnsRecordSetDetach');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DnsRecordSetDetach]
  end;
end;
{$ELSE}
function DnsRecordSetDetach; external dnsapi name 'DnsRecordSetDetach';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DnsFreeRecordListDeep: Pointer;

procedure DnsFreeRecordListDeep;
begin
  GetProcedureAddress(_DnsFreeRecordListDeep, dnsapi, 'DnsRecordListFree');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DnsFreeRecordListDeep]
  end;
end;
{$ELSE}
procedure DnsFreeRecordListDeep; external dnsapi name 'DnsRecordListFree';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DnsRecordListFree: Pointer;

procedure DnsRecordListFree;
begin
  GetProcedureAddress(_DnsRecordListFree, dnsapi, 'DnsRecordListFree');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DnsRecordListFree]
  end;
end;
{$ELSE}
procedure DnsRecordListFree; external dnsapi name 'DnsRecordListFree';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DnsFree: Pointer;

procedure DnsFree;
begin
  GetProcedureAddress(_DnsFree, dnsapi, 'DnsFree');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DnsFree]
  end;
end;
{$ELSE}
procedure DnsFree; external dnsapi name 'DnsFree';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DnsQuery_A: Pointer;

function DnsQuery_A;
begin
  GetProcedureAddress(_DnsQuery_A, dnsapi, 'DnsQuery_A');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DnsQuery_A]
  end;
end;
{$ELSE}
function DnsQuery_A; external dnsapi name 'DnsQuery_A';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DnsQuery_UTF8: Pointer;

function DnsQuery_UTF8;
begin
  GetProcedureAddress(_DnsQuery_UTF8, dnsapi, 'DnsQuery_UTF8');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DnsQuery_UTF8]
  end;
end;
{$ELSE}
function DnsQuery_UTF8; external dnsapi name 'DnsQuery_UTF8';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DnsQuery_W: Pointer;

function DnsQuery_W;
begin
  GetProcedureAddress(_DnsQuery_W, dnsapi, 'DnsQuery_W');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DnsQuery_W]
  end;
end;
{$ELSE}
function DnsQuery_W; external dnsapi name 'DnsQuery_W';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DnsQuery: Pointer;

function DnsQuery;
begin
  GetProcedureAddress(_DnsQuery, dnsapi, 'DnsQuery_W');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DnsQuery]
  end;
end;
{$ELSE}
function DnsQuery; external dnsapi name 'DnsQuery_W';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _DnsQuery: Pointer;

function DnsQuery;
begin
  GetProcedureAddress(_DnsQuery, dnsapi, 'DnsQuery_A');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DnsQuery]
  end;
end;
{$ELSE}
function DnsQuery; external dnsapi name 'DnsQuery_A';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _DnsAcquireContextHandle_W: Pointer;

function DnsAcquireContextHandle_W;
begin
  GetProcedureAddress(_DnsAcquireContextHandle_W, dnsapi, 'DnsAcquireContextHandle_W');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DnsAcquireContextHandle_W]
  end;
end;
{$ELSE}
function DnsAcquireContextHandle_W; external dnsapi name 'DnsAcquireContextHandle_W';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DnsAcquireContextHandle_A: Pointer;

function DnsAcquireContextHandle_A;
begin
  GetProcedureAddress(_DnsAcquireContextHandle_A, dnsapi, 'DnsAcquireContextHandle_A');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DnsAcquireContextHandle_A]
  end;
end;
{$ELSE}
function DnsAcquireContextHandle_A; external dnsapi name 'DnsAcquireContextHandle_A';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DnsAcquireContextHandle: Pointer;

function DnsAcquireContextHandle;
begin
  GetProcedureAddress(_DnsAcquireContextHandle, dnsapi, 'DnsAcquireContextHandle_W');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DnsAcquireContextHandle]
  end;
end;
{$ELSE}
function DnsAcquireContextHandle; external dnsapi name 'DnsAcquireContextHandle_W';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _DnsAcquireContextHandle: Pointer;

function DnsAcquireContextHandle;
begin
  GetProcedureAddress(_DnsAcquireContextHandle, dnsapi, 'DnsAcquireContextHandle_A');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DnsAcquireContextHandle]
  end;
end;
{$ELSE}
function DnsAcquireContextHandle; external dnsapi name 'DnsAcquireContextHandle_A';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _DnsReleaseContextHandle: Pointer;

procedure DnsReleaseContextHandle;
begin
  GetProcedureAddress(_DnsReleaseContextHandle, dnsapi, 'DnsReleaseContextHandle');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DnsReleaseContextHandle]
  end;
end;
{$ELSE}
procedure DnsReleaseContextHandle; external dnsapi name 'DnsReleaseContextHandle';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DnsModifyRecordsInSet_W: Pointer;

function DnsModifyRecordsInSet_W;
begin
  GetProcedureAddress(_DnsModifyRecordsInSet_W, dnsapi, 'DnsModifyRecordsInSet_W');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DnsModifyRecordsInSet_W]
  end;
end;
{$ELSE}
function DnsModifyRecordsInSet_W; external dnsapi name 'DnsModifyRecordsInSet_W';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DnsModifyRecordsInSet_A: Pointer;

function DnsModifyRecordsInSet_A;
begin
  GetProcedureAddress(_DnsModifyRecordsInSet_A, dnsapi, 'DnsModifyRecordsInSet_A');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DnsModifyRecordsInSet_A]
  end;
end;
{$ELSE}
function DnsModifyRecordsInSet_A; external dnsapi name 'DnsModifyRecordsInSet_A';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DnsModifyRecordsInSet_UTF8: Pointer;

function DnsModifyRecordsInSet_UTF8;
begin
  GetProcedureAddress(_DnsModifyRecordsInSet_UTF8, dnsapi, 'DnsModifyRecordsInSet_UTF8');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DnsModifyRecordsInSet_UTF8]
  end;
end;
{$ELSE}
function DnsModifyRecordsInSet_UTF8; external dnsapi name 'DnsModifyRecordsInSet_UTF8';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DnsModifyRecordsInSet: Pointer;

function DnsModifyRecordsInSet;
begin
  GetProcedureAddress(_DnsModifyRecordsInSet, dnsapi, 'DnsModifyRecordsInSet_W');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DnsModifyRecordsInSet]
  end;
end;
{$ELSE}
function DnsModifyRecordsInSet; external dnsapi name 'DnsModifyRecordsInSet_W';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _DnsModifyRecordsInSet: Pointer;

function DnsModifyRecordsInSet;
begin
  GetProcedureAddress(_DnsModifyRecordsInSet, dnsapi, 'DnsModifyRecordsInSet_A');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DnsModifyRecordsInSet]
  end;
end;
{$ELSE}
function DnsModifyRecordsInSet; external dnsapi name 'DnsModifyRecordsInSet_A';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}


{$IFDEF DYNAMIC_LINK}
var
  _DnsReplaceRecordSetW: Pointer;

function DnsReplaceRecordSetW;
begin
  GetProcedureAddress(_DnsReplaceRecordSetW, dnsapi, 'DnsReplaceRecordSetW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DnsReplaceRecordSetW]
  end;
end;
{$ELSE}
function DnsReplaceRecordSetW; external dnsapi name 'DnsReplaceRecordSetW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DnsReplaceRecordSetA: Pointer;

function DnsReplaceRecordSetA;
begin
  GetProcedureAddress(_DnsReplaceRecordSetA, dnsapi, 'DnsReplaceRecordSetA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DnsReplaceRecordSetA]
  end;
end;
{$ELSE}
function DnsReplaceRecordSetA; external dnsapi name 'DnsReplaceRecordSetA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DnsReplaceRecordSetUTF8: Pointer;

function DnsReplaceRecordSetUTF8;
begin
  GetProcedureAddress(_DnsReplaceRecordSetUTF8, dnsapi, 'DnsReplaceRecordSetUTF8');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DnsReplaceRecordSetUTF8]
  end;
end;
{$ELSE}
function DnsReplaceRecordSetUTF8; external dnsapi name 'DnsReplaceRecordSetUTF8';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DnsReplaceRecordSet: Pointer;

function DnsReplaceRecordSet;
begin
  GetProcedureAddress(_DnsReplaceRecordSet, dnsapi, 'DnsReplaceRecordSetW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DnsReplaceRecordSet]
  end;
end;
{$ELSE}
function DnsReplaceRecordSet; external dnsapi name 'DnsReplaceRecordSetW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _DnsReplaceRecordSet: Pointer;

function DnsReplaceRecordSet;
begin
  GetProcedureAddress(_DnsReplaceRecordSet, dnsapi, 'DnsReplaceRecordSetA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DnsReplaceRecordSet]
  end;
end;
{$ELSE}
function DnsReplaceRecordSet; external dnsapi name 'DnsReplaceRecordSetA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _DnsValidateName_UTF8: Pointer;

function DnsValidateName_UTF8;
begin
  GetProcedureAddress(_DnsValidateName_UTF8, dnsapi, 'DnsValidateName_UTF8');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DnsValidateName_UTF8]
  end;
end;
{$ELSE}
function DnsValidateName_UTF8; external dnsapi name 'DnsValidateName_UTF8';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DnsValidateName_W: Pointer;

function DnsValidateName_W;
begin
  GetProcedureAddress(_DnsValidateName_W, dnsapi, 'DnsValidateName_W');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DnsValidateName_W]
  end;
end;
{$ELSE}
function DnsValidateName_W; external dnsapi name 'DnsValidateName_W';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DnsValidateName_A: Pointer;

function DnsValidateName_A;
begin
  GetProcedureAddress(_DnsValidateName_A, dnsapi, 'DnsValidateName_A');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DnsValidateName_A]
  end;
end;
{$ELSE}
function DnsValidateName_A; external dnsapi name 'DnsValidateName_A';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}
function DnsValidateName(pszName: LPCWSTR; Format: DNS_NAME_FORMAT): DNS_STATUS;
begin
  Result := DnsValidateName_W(pszName, Format);
end;
{$ELSE}
function DnsValidateName(pszName: LPCSTR; Format: DNS_NAME_FORMAT): DNS_STATUS;
begin
  Result := DnsValidateName_A(pszName, Format);
end;
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _DnsNameCompare_A: Pointer;

function DnsNameCompare_A;
begin
  GetProcedureAddress(_DnsNameCompare_A, dnsapi, 'DnsNameCompare_A');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DnsNameCompare_A]
  end;
end;
{$ELSE}
function DnsNameCompare_A; external dnsapi name 'DnsNameCompare_A';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DnsNameCompare_W: Pointer;

function DnsNameCompare_W;
begin
  GetProcedureAddress(_DnsNameCompare_W, dnsapi, 'DnsNameCompare_W');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DnsNameCompare_W]
  end;
end;
{$ELSE}
function DnsNameCompare_W; external dnsapi name 'DnsNameCompare_W';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _DnsNameCompare: Pointer;

function DnsNameCompare;
begin
  GetProcedureAddress(_DnsNameCompare, dnsapi, 'DnsNameCompare_W');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DnsNameCompare]
  end;
end;
{$ELSE}
function DnsNameCompare; external dnsapi name 'DnsNameCompare_W';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _DnsNameCompare: Pointer;

function DnsNameCompare;
begin
  GetProcedureAddress(_DnsNameCompare, dnsapi, 'DnsNameCompare_A');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DnsNameCompare]
  end;
end;
{$ELSE}
function DnsNameCompare; external dnsapi name 'DnsNameCompare_A';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _DnsWriteQuestionToBuffer_W: Pointer;

function DnsWriteQuestionToBuffer_W;
begin
  GetProcedureAddress(_DnsWriteQuestionToBuffer_W, dnsapi, 'DnsWriteQuestionToBuffer_W');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DnsWriteQuestionToBuffer_W]
  end;
end;
{$ELSE}
function DnsWriteQuestionToBuffer_W; external dnsapi name 'DnsWriteQuestionToBuffer_W';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DnsWriteQuestionToBuffer_UTF8: Pointer;

function DnsWriteQuestionToBuffer_UTF8;
begin
  GetProcedureAddress(_DnsWriteQuestionToBuffer_UTF8, dnsapi, 'DnsWriteQuestionToBuffer_UTF8');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DnsWriteQuestionToBuffer_UTF8]
  end;
end;
{$ELSE}
function DnsWriteQuestionToBuffer_UTF8; external dnsapi name 'DnsWriteQuestionToBuffer_UTF8';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DnsExtractRecordsFromMessage_W: Pointer;

function DnsExtractRecordsFromMessage_W;
begin
  GetProcedureAddress(_DnsExtractRecordsFromMessage_W, dnsapi, 'DnsExtractRecordsFromMessage_W');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DnsExtractRecordsFromMessage_W]
  end;
end;
{$ELSE}
function DnsExtractRecordsFromMessage_W; external dnsapi name 'DnsExtractRecordsFromMessage_W';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DnsExtractRecFromMessage_UTF8: Pointer;

function DnsExtractRecordsFromMessage_UTF8;
begin
  GetProcedureAddress(_DnsExtractRecFromMessage_UTF8, dnsapi, 'DnsExtractRecordsFromMessage_UTF8');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DnsExtractRecFromMessage_UTF8]
  end;
end;
{$ELSE}
function DnsExtractRecordsFromMessage_UTF8; external dnsapi name 'DnsExtractRecordsFromMessage_UTF8';
{$ENDIF DYNAMIC_LINK}


end.
