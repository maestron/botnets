/*++

Copyright (c) 1996-2002  Microsoft Corporation

Module Name:

    windns.h

Abstract:

    Domain Name System (DNS)

    DNS definitions and DNS API.

Author:

    Jim Gilroy (jamesg)     December 7, 1996

Revision History:

--*/


#ifndef _WINDNS_INCLUDED_
#define _WINDNS_INCLUDED_


#ifdef __cplusplus
extern "C"
{
#endif  // __cplusplus


//
//  Define QWORD -- not yet defined globally 
//

typedef unsigned __int64 QWORD, *PQWORD;

//
//  DNS public types
//

typedef LONG    DNS_STATUS, *PDNS_STATUS;

//
//  IP Address
//

typedef DWORD   IP4_ADDRESS, *PIP4_ADDRESS;

#define SIZEOF_IP4_ADDRESS                  (4)
#define IP4_ADDRESS_STRING_LENGTH           (15)
#define IP4_ADDRESS_STRING_BUFFER_LENGTH    (16)


//
//  IP Address Array type
//

typedef struct  _IP4_ARRAY
{
    DWORD           AddrCount;
#ifdef MIDL_PASS
    [size_is( AddrCount )]  IP4_ADDRESS  AddrArray[];
#else
    IP4_ADDRESS     AddrArray[1];
#endif
}
IP4_ARRAY, *PIP4_ARRAY;


//
//  IPv6 Address
//

#ifdef MIDL_PASS
typedef struct
{
#ifdef _WIN64
    QWORD       IP6Qword[2];
#else
    DWORD       IP6Dword[4];
#endif
}
IP6_ADDRESS, *PIP6_ADDRESS;
#else
typedef union
{
#ifdef _WIN64
    QWORD       IP6Qword[2];
#endif
    DWORD       IP6Dword[4];
    WORD        IP6Word[8];
    BYTE        IP6Byte[16];
#ifdef  IN6_ADDR
    IN6_ADDR    In6;
#endif
}
IP6_ADDRESS, *PIP6_ADDRESS;
#endif

//  Backward compatibility

//typedef IP6_ADDRESS  DNS_IP6_ADDRESS, *PDNS_IP6_ADDRESS;

//
//  IP6 string max is 45 bytes
//      - 6 WORDs in colon+hex (5 chars)
//      - last DWORD as IP4 (15 chars)
//  

#undef  IP6_ADDRESS_STRING_LENGTH
#define IP6_ADDRESS_STRING_LENGTH           (47)
#define IP6_ADDRESS_STRING_BUFFER_LENGTH    (48)

//  backcompat
//#define IPV6_ADDRESS_STRING_LENGTH      IP6_ADDRESS_STRING_LENGTH


//
//  Inline byte flipping -- can be done in registers
//

#define INLINE_WORD_FLIP(out, in)   \
        {                           \
            WORD _in = (in);        \
            (out) = (_in << 8) | (_in >> 8);  \
        }
#define INLINE_HTONS(out, in)   INLINE_WORD_FLIP(out, in)
#define INLINE_NTOHS(out, in)   INLINE_WORD_FLIP(out, in)

#define INLINE_DWORD_FLIP(out, in)  \
        {                           \
            DWORD _in = (in);       \
            (out) = ((_in << 8) & 0x00ff0000) | \
                    (_in << 24)               | \
                    ((_in >> 8) & 0x0000ff00) | \
                    (_in >> 24);                \
        }
#define INLINE_NTOHL(out, in) INLINE_DWORD_FLIP(out, in)
#define INLINE_HTONL(out, in) INLINE_DWORD_FLIP(out, in)


//
//  Inline byte flip and write to packet (unaligned)
//

#define INLINE_WRITE_FLIPPED_WORD( pout, in ) \
            INLINE_WORD_FLIP( *((UNALIGNED WORD *)(pout)), in )

#define INLINE_WRITE_FLIPPED_DWORD( pout, in ) \
            INLINE_DWORD_FLIP( *((UNALIGNED DWORD *)(pout)), in )




//
//  Basic DNS definitions
//

//
//  DNS port for both UDP and TCP is 53.
//

#define DNS_PORT_HOST_ORDER     (0x0035)    // port 53
#define DNS_PORT_NET_ORDER      (0x3500)

//
//  DNS UDP packets no more than 512 bytes
//

#define DNS_RFC_MAX_UDP_PACKET_LENGTH   (512)


//
//  DNS Names limited to 255, 63 in any one label
//

#define DNS_MAX_NAME_LENGTH             (255)
#define DNS_MAX_LABEL_LENGTH            (63)

#define DNS_MAX_NAME_BUFFER_LENGTH      (256)
#define DNS_MAX_LABEL_BUFFER_LENGTH     (64)

//
//  Reverse lookup domain names
//

#define DNS_IP4_REVERSE_DOMAIN_STRING_A ("in-addr.arpa.")
#define DNS_IP4_REVERSE_DOMAIN_STRING_W (L"in-addr.arpa.")

#define DNS_MAX_IP4_REVERSE_NAME_LENGTH \
            (IP4_ADDRESS_STRING_LENGTH+1+sizeof(DNS_IP4_REVERSE_DOMAIN_STRING_A))

#define DNS_MAX_IP4_REVERSE_NAME_BUFFER_LENGTH \
            (DNS_MAX_IP4_REVERSE_NAME_LENGTH + 1)


#define DNS_IP6_REVERSE_DOMAIN_STRING_A ("ip6.arpa.")
#define DNS_IP6_REVERSE_DOMAIN_STRING_W (L"ip6.arpa.")

#define DNS_MAX_IP6_REVERSE_NAME_LENGTH \
            (64+sizeof(DNS_IP6_REVERSE_DOMAIN_STRING_A))

#define DNS_MAX_IP6_REVERSE_NAME_BUFFER_LENGTH \
            (DNS_MAX_IP6_REVERSE_NAME_LENGTH + 1)

//  Combined

#define DNS_MAX_REVERSE_NAME_LENGTH         DNS_MAX_IP6_REVERSE_NAME_LENGTH
#define DNS_MAX_REVERSE_NAME_BUFFER_LENGTH  DNS_MAX_IP6_REVERSE_NAME_BUFFER_LENGTH

#ifdef UNICODE
#define DNS_IP4_REVERSE_DOMAIN_STRING   DNS_IP4_REVERSE_DOMAIN_STRING_W
#define DNS_IP6_REVERSE_DOMAIN_STRING   DNS_IP6_REVERSE_DOMAIN_STRING_W
#else
#define DNS_IP4_REVERSE_DOMAIN_STRING   DNS_IP4_REVERSE_DOMAIN_STRING_A
#define DNS_IP6_REVERSE_DOMAIN_STRING   DNS_IP6_REVERSE_DOMAIN_STRING_A
#endif


//
//  DNS Text string limited by size representable
//      in a single byte length field

#define DNS_MAX_TEXT_STRING_LENGTH  (255)




//
//  DNS On-The-Wire Structures
//

#pragma pack(1)

//
//  DNS Message Header
//

typedef struct _DNS_HEADER
{
    WORD    Xid;

    BYTE    RecursionDesired : 1;
    BYTE    Truncation : 1;
    BYTE    Authoritative : 1;
    BYTE    Opcode : 4;
    BYTE    IsResponse : 1;

    BYTE    ResponseCode : 4;
    BYTE    Reserved : 3;
    BYTE    RecursionAvailable : 1;

    WORD    QuestionCount;
    WORD    AnswerCount;
    WORD    NameServerCount;
    WORD    AdditionalCount;
}
DNS_HEADER, *PDNS_HEADER;


//
//  Flags as WORD
//

#define DNS_HEADER_FLAGS(pHead)     ( *((PWORD)(pHead)+1) )


//
//  Byte flip DNS header to\from host order.
//
//  Note that this does NOT flip flags, as definition above defines
//  flags as individual bytes for direct access to net byte order.
//

#define DNS_BYTE_FLIP_HEADER_COUNTS(pHeader)       \
        {                                   \
            PDNS_HEADER _head = (pHeader);  \
            INLINE_HTONS(_head->Xid,            _head->Xid             ); \
            INLINE_HTONS(_head->QuestionCount,  _head->QuestionCount   ); \
            INLINE_HTONS(_head->AnswerCount,    _head->AnswerCount     ); \
            INLINE_HTONS(_head->NameServerCount,_head->NameServerCount ); \
            INLINE_HTONS(_head->AdditionalCount,_head->AdditionalCount ); \
        }

//
//  Question name follows header
//

#define DNS_OFFSET_TO_QUESTION_NAME     sizeof(DNS_HEADER)

//
//  Question immediately follows header so compressed question name
//      0xC000 | sizeof(DNS_HEADER)

#define DNS_COMPRESSED_QUESTION_NAME  (0xC00C)


//
//  Packet extraction macros
//

#define DNS_QUESTION_NAME_FROM_HEADER( _pHeader_ ) \
            ( (PCHAR)( (PDNS_HEADER)(_pHeader_) + 1 ) )

#define DNS_ANSWER_FROM_QUESTION( _pQuestion_ ) \
            ( (PCHAR)( (PDNS_QUESTION)(_pQuestion_) + 1 ) )


//
//  DNS Question
//

typedef struct _DNS_WIRE_QUESTION
{
    //  Preceded by question name

    WORD    QuestionType;
    WORD    QuestionClass;
}
DNS_WIRE_QUESTION, *PDNS_WIRE_QUESTION;


//
//  DNS Resource Record
//

typedef struct _DNS_WIRE_RECORD
{
    //  Preceded by record owner name

    WORD    RecordType;
    WORD    RecordClass;
    DWORD   TimeToLive;
    WORD    DataLength;

    //  Followed by record data
}
DNS_WIRE_RECORD, *PDNS_WIRE_RECORD;

#pragma pack()


//
//  DNS Query Types
//

#define DNS_OPCODE_QUERY            0   // Query
#define DNS_OPCODE_IQUERY           1   // Obsolete: IP to name
#define DNS_OPCODE_SERVER_STATUS    2   // Obsolete: DNS ping
#define DNS_OPCODE_UNKNOWN          3   // Unknown
#define DNS_OPCODE_NOTIFY           4   // Notify
#define DNS_OPCODE_UPDATE           5   // Dynamic Update

//
//  DNS response codes.
//
//  Sent in the "ResponseCode" field of a DNS_HEADER.
//

#define DNS_RCODE_NOERROR       0
#define DNS_RCODE_FORMERR       1       // Format error
#define DNS_RCODE_SERVFAIL      2       // Server failure
#define DNS_RCODE_NXDOMAIN      3       // Name error
#define DNS_RCODE_NOTIMPL       4       // Not implemented
#define DNS_RCODE_REFUSED       5       // Refused
#define DNS_RCODE_YXDOMAIN      6       // Domain name should not exist
#define DNS_RCODE_YXRRSET       7       // RR set should not exist
#define DNS_RCODE_NXRRSET       8       // RR set does not exist
#define DNS_RCODE_NOTAUTH       9       // Not authoritative for zone
#define DNS_RCODE_NOTZONE       10      // Name is not zone
#define DNS_RCODE_MAX           15

//
//  Extended RCODEs
//

#define DNS_RCODE_BADVERS       16      // Bad EDNS version
#define DNS_RCODE_BADSIG        16      // Bad signature
#define DNS_RCODE_BADKEY        17      // Bad key
#define DNS_RCODE_BADTIME       18      // Bad timestamp

//
//  Mappings to friendly names
//

#define DNS_RCODE_NO_ERROR          DNS_RCODE_NOERROR
#define DNS_RCODE_FORMAT_ERROR      DNS_RCODE_FORMERR
#define DNS_RCODE_SERVER_FAILURE    DNS_RCODE_SERVFAIL
#define DNS_RCODE_NAME_ERROR        DNS_RCODE_NXDOMAIN
#define DNS_RCODE_NOT_IMPLEMENTED   DNS_RCODE_NOTIMPL


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

#define DNS_CLASS_INTERNET  0x0001      //  1
#define DNS_CLASS_CSNET     0x0002      //  2
#define DNS_CLASS_CHAOS     0x0003      //  3
#define DNS_CLASS_HESIOD    0x0004      //  4
#define DNS_CLASS_NONE      0x00fe      //  254
#define DNS_CLASS_ALL       0x00ff      //  255
#define DNS_CLASS_ANY       0x00ff      //  255

#define DNS_RCLASS_INTERNET 0x0100      //  1
#define DNS_RCLASS_CSNET    0x0200      //  2
#define DNS_RCLASS_CHAOS    0x0300      //  3
#define DNS_RCLASS_HESIOD   0x0400      //  4
#define DNS_RCLASS_NONE     0xfe00      //  254
#define DNS_RCLASS_ALL      0xff00      //  255
#define DNS_RCLASS_ANY      0xff00      //  255



//
//  DNS Record Types
//
//  _TYPE_ defines are in host byte order.
//  _RTYPE_ defines are in net byte order.
//
//  Generally always deal with types in host byte order as we index
//  resource record functions by type.
//

#define DNS_TYPE_ZERO       0x0000

//  RFC 1034/1035
#define DNS_TYPE_A          0x0001      //  1
#define DNS_TYPE_NS         0x0002      //  2
#define DNS_TYPE_MD         0x0003      //  3
#define DNS_TYPE_MF         0x0004      //  4
#define DNS_TYPE_CNAME      0x0005      //  5
#define DNS_TYPE_SOA        0x0006      //  6
#define DNS_TYPE_MB         0x0007      //  7
#define DNS_TYPE_MG         0x0008      //  8
#define DNS_TYPE_MR         0x0009      //  9
#define DNS_TYPE_NULL       0x000a      //  10
#define DNS_TYPE_WKS        0x000b      //  11
#define DNS_TYPE_PTR        0x000c      //  12
#define DNS_TYPE_HINFO      0x000d      //  13
#define DNS_TYPE_MINFO      0x000e      //  14
#define DNS_TYPE_MX         0x000f      //  15
#define DNS_TYPE_TEXT       0x0010      //  16

//  RFC 1183
#define DNS_TYPE_RP         0x0011      //  17
#define DNS_TYPE_AFSDB      0x0012      //  18
#define DNS_TYPE_X25        0x0013      //  19
#define DNS_TYPE_ISDN       0x0014      //  20
#define DNS_TYPE_RT         0x0015      //  21

//  RFC 1348
#define DNS_TYPE_NSAP       0x0016      //  22
#define DNS_TYPE_NSAPPTR    0x0017      //  23

//  RFC 2065    (DNS security)
#define DNS_TYPE_SIG        0x0018      //  24
#define DNS_TYPE_KEY        0x0019      //  25

//  RFC 1664    (X.400 mail)
#define DNS_TYPE_PX         0x001a      //  26

//  RFC 1712    (Geographic position)
#define DNS_TYPE_GPOS       0x001b      //  27

//  RFC 1886    (IPv6 Address)
#define DNS_TYPE_AAAA       0x001c      //  28

//  RFC 1876    (Geographic location)
#define DNS_TYPE_LOC        0x001d      //  29

//  RFC 2065    (Secure negative response)
#define DNS_TYPE_NXT        0x001e      //  30

//  Patton      (Endpoint Identifier)
#define DNS_TYPE_EID        0x001f      //  31

//  Patton      (Nimrod Locator)
#define DNS_TYPE_NIMLOC     0x0020      //  32

//  RFC 2052    (Service location)
#define DNS_TYPE_SRV        0x0021      //  33

//  ATM Standard something-or-another (ATM Address)
#define DNS_TYPE_ATMA       0x0022      //  34

//  RFC 2168    (Naming Authority Pointer)
#define DNS_TYPE_NAPTR      0x0023      //  35

//  RFC 2230    (Key Exchanger)
#define DNS_TYPE_KX         0x0024      //  36

//  RFC 2538    (CERT)
#define DNS_TYPE_CERT       0x0025      //  37

//  A6 Draft    (A6)
#define DNS_TYPE_A6         0x0026      //  38

//  DNAME Draft (DNAME)
#define DNS_TYPE_DNAME      0x0027      //  39

//  Eastlake    (Kitchen Sink)
#define DNS_TYPE_SINK       0x0028      //  40

//  RFC 2671    (EDNS OPT)
#define DNS_TYPE_OPT        0x0029      //  41

//
//  IANA Reserved
//

#define DNS_TYPE_UINFO      0x0064      //  100
#define DNS_TYPE_UID        0x0065      //  101
#define DNS_TYPE_GID        0x0066      //  102
#define DNS_TYPE_UNSPEC     0x0067      //  103

//
//  Query only types (1035, 1995)
//      - Crawford      (ADDRS)
//      - TKEY draft    (TKEY)
//      - TSIG draft    (TSIG)
//      - RFC 1995      (IXFR)
//      - RFC 1035      (AXFR up)
//

#define DNS_TYPE_ADDRS      0x00f8      //  248
#define DNS_TYPE_TKEY       0x00f9      //  249
#define DNS_TYPE_TSIG       0x00fa      //  250
#define DNS_TYPE_IXFR       0x00fb      //  251
#define DNS_TYPE_AXFR       0x00fc      //  252
#define DNS_TYPE_MAILB      0x00fd      //  253
#define DNS_TYPE_MAILA      0x00fe      //  254
#define DNS_TYPE_ALL        0x00ff      //  255
#define DNS_TYPE_ANY        0x00ff      //  255

//
//  Temp Microsoft types -- use until get IANA approval for real type
//

#define DNS_TYPE_WINS       0xff01      //  64K - 255
#define DNS_TYPE_WINSR      0xff02      //  64K - 254
#define DNS_TYPE_NBSTAT     (DNS_TYPE_WINSR)


//
//  DNS Record Types -- Net Byte Order
//

#define DNS_RTYPE_A         0x0100      //  1
#define DNS_RTYPE_NS        0x0200      //  2
#define DNS_RTYPE_MD        0x0300      //  3
#define DNS_RTYPE_MF        0x0400      //  4
#define DNS_RTYPE_CNAME     0x0500      //  5
#define DNS_RTYPE_SOA       0x0600      //  6
#define DNS_RTYPE_MB        0x0700      //  7
#define DNS_RTYPE_MG        0x0800      //  8
#define DNS_RTYPE_MR        0x0900      //  9
#define DNS_RTYPE_NULL      0x0a00      //  10
#define DNS_RTYPE_WKS       0x0b00      //  11
#define DNS_RTYPE_PTR       0x0c00      //  12
#define DNS_RTYPE_HINFO     0x0d00      //  13
#define DNS_RTYPE_MINFO     0x0e00      //  14
#define DNS_RTYPE_MX        0x0f00      //  15
#define DNS_RTYPE_TEXT      0x1000      //  16
#define DNS_RTYPE_RP        0x1100      //  17
#define DNS_RTYPE_AFSDB     0x1200      //  18
#define DNS_RTYPE_X25       0x1300      //  19
#define DNS_RTYPE_ISDN      0x1400      //  20
#define DNS_RTYPE_RT        0x1500      //  21
#define DNS_RTYPE_NSAP      0x1600      //  22
#define DNS_RTYPE_NSAPPTR   0x1700      //  23
#define DNS_RTYPE_SIG       0x1800      //  24
#define DNS_RTYPE_KEY       0x1900      //  25
#define DNS_RTYPE_PX        0x1a00      //  26
#define DNS_RTYPE_GPOS      0x1b00      //  27
#define DNS_RTYPE_AAAA      0x1c00      //  28
#define DNS_RTYPE_LOC       0x1d00      //  29
#define DNS_RTYPE_NXT       0x1e00      //  30
#define DNS_RTYPE_EID       0x1f00      //  31
#define DNS_RTYPE_NIMLOC    0x2000      //  32
#define DNS_RTYPE_SRV       0x2100      //  33
#define DNS_RTYPE_ATMA      0x2200      //  34
#define DNS_RTYPE_NAPTR     0x2300      //  35
#define DNS_RTYPE_KX        0x2400      //  36
#define DNS_RTYPE_CERT      0x2500      //  37
#define DNS_RTYPE_A6        0x2600      //  38
#define DNS_RTYPE_DNAME     0x2700      //  39
#define DNS_RTYPE_SINK      0x2800      //  40
#define DNS_RTYPE_OPT       0x2900      //  41

//
//  IANA Reserved
//

#define DNS_RTYPE_UINFO     0x6400      //  100
#define DNS_RTYPE_UID       0x6500      //  101
#define DNS_RTYPE_GID       0x6600      //  102
#define DNS_RTYPE_UNSPEC    0x6700      //  103

//
//  Query only types
//

#define DNS_RTYPE_TKEY      0xf900      //  249
#define DNS_RTYPE_TSIG      0xfa00      //  250
#define DNS_RTYPE_IXFR      0xfb00      //  251
#define DNS_RTYPE_AXFR      0xfc00      //  252
#define DNS_RTYPE_MAILB     0xfd00      //  253
#define DNS_RTYPE_MAILA     0xfe00      //  254
#define DNS_RTYPE_ALL       0xff00      //  255
#define DNS_RTYPE_ANY       0xff00      //  255

//
//  Temp Microsoft types -- use until get IANA approval for real type
//

#define DNS_RTYPE_WINS      0x01ff      //  64K - 255
#define DNS_RTYPE_WINSR     0x02ff      //  64K - 254




//
//  Record type specific definitions
//

//
//  ATMA (ATM address type) formats
//
//  Define these directly for any environment (ex NT4)
//  without winsock2 ATM support (ws2atm.h)
//

#ifndef  ATMA_E164
#define DNS_ATMA_FORMAT_E164            1
#define DNS_ATMA_FORMAT_AESA            2
#define DNS_ATMA_MAX_ADDR_LENGTH        (20)
#else
#define DNS_ATMA_FORMAT_E164            ATM_E164
#define DNS_ATMA_FORMAT_AESA            ATM_AESA
#define DNS_ATMA_MAX_ADDR_LENGTH        ATM_ADDR_SIZE
#endif

#define DNS_ATMA_AESA_ADDR_LENGTH       (20)
#define DNS_ATMA_MAX_RECORD_LENGTH      (DNS_ATMA_MAX_ADDR_LENGTH+1)


//
//  DNSSEC defs
//

//  DNSSEC algorithms

#define DNSSEC_ALGORITHM_RSAMD5     1
#define DNSSEC_ALGORITHM_NULL       253
#define DNSSEC_ALGORITHM_PRIVATE    254

//  DNSSEC KEY protocol table

#define DNSSEC_PROTOCOL_NONE        0
#define DNSSEC_PROTOCOL_TLS         1
#define DNSSEC_PROTOCOL_EMAIL       2
#define DNSSEC_PROTOCOL_DNSSEC      3
#define DNSSEC_PROTOCOL_IPSEC       4

//  DNSSEC KEY flag field

#define DNSSEC_KEY_FLAG_NOAUTH          0x0001
#define DNSSEC_KEY_FLAG_NOCONF          0x0002
#define DNSSEC_KEY_FLAG_FLAG2           0x0004
#define DNSSEC_KEY_FLAG_EXTEND          0x0008
#define DNSSEC_KEY_FLAG_
#define DNSSEC_KEY_FLAG_FLAG4           0x0010
#define DNSSEC_KEY_FLAG_FLAG5           0x0020

// bits 6,7 are name type

#define DNSSEC_KEY_FLAG_USER            0x0000
#define DNSSEC_KEY_FLAG_ZONE            0x0040
#define DNSSEC_KEY_FLAG_HOST            0x0080
#define DNSSEC_KEY_FLAG_NTPE3           0x00c0

// bits 8-11 are reserved for future use

#define DNSSEC_KEY_FLAG_FLAG8           0x0100
#define DNSSEC_KEY_FLAG_FLAG9           0x0200
#define DNSSEC_KEY_FLAG_FLAG10          0x0400
#define DNSSEC_KEY_FLAG_FLAG11          0x0800

// bits 12-15 are sig field

#define DNSSEC_KEY_FLAG_SIG0            0x0000
#define DNSSEC_KEY_FLAG_SIG1            0x1000
#define DNSSEC_KEY_FLAG_SIG2            0x2000
#define DNSSEC_KEY_FLAG_SIG3            0x3000
#define DNSSEC_KEY_FLAG_SIG4            0x4000
#define DNSSEC_KEY_FLAG_SIG5            0x5000
#define DNSSEC_KEY_FLAG_SIG6            0x6000
#define DNSSEC_KEY_FLAG_SIG7            0x7000
#define DNSSEC_KEY_FLAG_SIG8            0x8000
#define DNSSEC_KEY_FLAG_SIG9            0x9000
#define DNSSEC_KEY_FLAG_SIG10           0xa000
#define DNSSEC_KEY_FLAG_SIG11           0xb000
#define DNSSEC_KEY_FLAG_SIG12           0xc000
#define DNSSEC_KEY_FLAG_SIG13           0xd000
#define DNSSEC_KEY_FLAG_SIG14           0xe000
#define DNSSEC_KEY_FLAG_SIG15           0xf000


//
//  TKEY modes
//

#define DNS_TKEY_MODE_SERVER_ASSIGN         1
#define DNS_TKEY_MODE_DIFFIE_HELLMAN        2
#define DNS_TKEY_MODE_GSS                   3
#define DNS_TKEY_MODE_RESOLVER_ASSIGN       4

//
//  WINS + NBSTAT flag field
//

#define DNS_WINS_FLAG_SCOPE     (0x80000000)
#define DNS_WINS_FLAG_LOCAL     (0x00010000)


//
//  Helpful checks
//

#define IS_WORD_ALIGNED(p)      ( !((UINT_PTR)(p) & (UINT_PTR)1) )
#define IS_DWORD_ALIGNED(p)     ( !((UINT_PTR)(p) & (UINT_PTR)3) )
#define IS_QWORD_ALIGNED(p)     ( !((UINT_PTR)(p) & (UINT_PTR)7) )




//
//  DNS config API
//

//
//  Types of DNS configuration info
//

typedef enum
{
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
    DnsConfigFullHostName_UTF8

    //  In XP-SP1 (Server.net)
}
DNS_CONFIG_TYPE;

//
//  Config API flags
//

//
//  Causes config info to be allocated.
//  Free with DnsFree().
//

#define DNS_CONFIG_FLAG_ALLOC   (0x00000001)

DNS_STATUS
WINAPI
DnsQueryConfig(
    IN      DNS_CONFIG_TYPE     Config,
    IN      DWORD               Flag,
    IN      PWSTR               pwsAdapterName,
    IN      PVOID               pReserved,
    OUT     PVOID               pBuffer,
    IN OUT  PDWORD              pBufferLength
    );



//
//  DNS resource record structure
//

//
//  Record data for specific types
//

typedef struct
{
    IP4_ADDRESS     IpAddress;
}
DNS_A_DATA, *PDNS_A_DATA;

typedef struct
{
    PWSTR           pNameHost;
}
DNS_PTR_DATAW, *PDNS_PTR_DATAW;

typedef struct
{
    PSTR            pNameHost;
}
DNS_PTR_DATAA, *PDNS_PTR_DATAA;

typedef struct
{
    PWSTR           pNamePrimaryServer;
    PWSTR           pNameAdministrator;
    DWORD           dwSerialNo;
    DWORD           dwRefresh;
    DWORD           dwRetry;
    DWORD           dwExpire;
    DWORD           dwDefaultTtl;
}
DNS_SOA_DATAW, *PDNS_SOA_DATAW;

typedef struct
{
    PSTR            pNamePrimaryServer;
    PSTR            pNameAdministrator;
    DWORD           dwSerialNo;
    DWORD           dwRefresh;
    DWORD           dwRetry;
    DWORD           dwExpire;
    DWORD           dwDefaultTtl;
}
DNS_SOA_DATAA, *PDNS_SOA_DATAA;

typedef struct
{
    PWSTR           pNameMailbox;
    PWSTR           pNameErrorsMailbox;
}
DNS_MINFO_DATAW, *PDNS_MINFO_DATAW;

typedef struct
{
    PSTR            pNameMailbox;
    PSTR            pNameErrorsMailbox;
}
DNS_MINFO_DATAA, *PDNS_MINFO_DATAA;

typedef struct
{
    PWSTR           pNameExchange;
    WORD            wPreference;
    WORD            Pad;        // keep ptrs DWORD aligned
}
DNS_MX_DATAW, *PDNS_MX_DATAW;

typedef struct
{
    PSTR            pNameExchange;
    WORD            wPreference;
    WORD            Pad;        // keep ptrs DWORD aligned
}
DNS_MX_DATAA, *PDNS_MX_DATAA;

typedef struct
{
    DWORD           dwStringCount;
#ifdef MIDL_PASS
    [size_is(dwStringCount)] PWSTR pStringArray[];
#else
    PWSTR           pStringArray[1];
#endif
}
DNS_TXT_DATAW, *PDNS_TXT_DATAW;

typedef struct
{
    DWORD           dwStringCount;
#ifdef MIDL_PASS
    [size_is(dwStringCount)] PSTR  pStringArray[];
#else
    PSTR            pStringArray[1];
#endif
}
DNS_TXT_DATAA, *PDNS_TXT_DATAA;

typedef struct
{
    DWORD           dwByteCount;
#ifdef MIDL_PASS
    [size_is(dwByteCount)] BYTE Data[];
#else
    BYTE            Data[1];
#endif
}
DNS_NULL_DATA, *PDNS_NULL_DATA;

typedef struct
{
    IP4_ADDRESS     IpAddress;
    UCHAR           chProtocol;
    BYTE            BitMask[1];
}
DNS_WKS_DATA, *PDNS_WKS_DATA;

typedef struct
{
    IP6_ADDRESS     Ip6Address;
}
DNS_AAAA_DATA, *PDNS_AAAA_DATA;

typedef struct
{
    PWSTR           pNameSigner;
    WORD            wTypeCovered;
    BYTE            chAlgorithm;
    BYTE            chLabelCount;
    DWORD           dwOriginalTtl;
    DWORD           dwExpiration;
    DWORD           dwTimeSigned;
    WORD            wKeyTag;
    WORD            Pad;            // keep byte field aligned
    BYTE            Signature[1];
}
DNS_SIG_DATAW, *PDNS_SIG_DATAW;

typedef struct
{
    PSTR            pNameSigner;
    WORD            wTypeCovered;
    BYTE            chAlgorithm;
    BYTE            chLabelCount;
    DWORD           dwOriginalTtl;
    DWORD           dwExpiration;
    DWORD           dwTimeSigned;
    WORD            wKeyTag;
    WORD            Pad;            // keep byte field aligned
    BYTE            Signature[1];
}
DNS_SIG_DATAA, *PDNS_SIG_DATAA;

typedef struct
{
    WORD            wFlags;
    BYTE            chProtocol;
    BYTE            chAlgorithm;
    BYTE            Key[1];
}
DNS_KEY_DATA, *PDNS_KEY_DATA;

typedef struct
{
    WORD            wVersion;
    WORD            wSize;
    WORD            wHorPrec;
    WORD            wVerPrec;
    DWORD           dwLatitude;
    DWORD           dwLongitude;
    DWORD           dwAltitude;
}
DNS_LOC_DATA, *PDNS_LOC_DATA;

typedef struct
{
    PWSTR           pNameNext;
    WORD            wNumTypes;
    WORD            wTypes[1];
}
DNS_NXT_DATAW, *PDNS_NXT_DATAW;

typedef struct
{
    PSTR            pNameNext;
    WORD            wNumTypes;
    WORD            wTypes[1];
}
DNS_NXT_DATAA, *PDNS_NXT_DATAA;

typedef struct
{
    PWSTR           pNameTarget;
    WORD            wPriority;
    WORD            wWeight;
    WORD            wPort;
    WORD            Pad;            // keep ptrs DWORD aligned
}
DNS_SRV_DATAW, *PDNS_SRV_DATAW;

typedef struct
{
    PSTR            pNameTarget;
    WORD            wPriority;
    WORD            wWeight;
    WORD            wPort;
    WORD            Pad;            // keep ptrs DWORD aligned
}
DNS_SRV_DATAA, *PDNS_SRV_DATAA;

typedef struct
{
    BYTE            AddressType;
    BYTE            Address[ DNS_ATMA_MAX_ADDR_LENGTH ];

    //  E164 -- Null terminated string of less than
    //      DNS_ATMA_MAX_ADDR_LENGTH
    //
    //  For NSAP (AESA) BCD encoding of exactly
    //      DNS_ATMA_AESA_ADDR_LENGTH
}
DNS_ATMA_DATA, *PDNS_ATMA_DATA;

typedef struct
{
    PWSTR           pNameAlgorithm;
    PBYTE           pAlgorithmPacket;
    PBYTE           pKey;
    PBYTE           pOtherData;
    DWORD           dwCreateTime;
    DWORD           dwExpireTime;
    WORD            wMode;
    WORD            wError;
    WORD            wKeyLength;
    WORD            wOtherLength;
    UCHAR           cAlgNameLength;
    BOOL            bPacketPointers;
}
DNS_TKEY_DATAW, *PDNS_TKEY_DATAW;

typedef struct
{
    PSTR            pNameAlgorithm;
    PBYTE           pAlgorithmPacket;
    PBYTE           pKey;
    PBYTE           pOtherData;
    DWORD           dwCreateTime;
    DWORD           dwExpireTime;
    WORD            wMode;
    WORD            wError;
    WORD            wKeyLength;
    WORD            wOtherLength;
    UCHAR           cAlgNameLength;
    BOOL            bPacketPointers;
}
DNS_TKEY_DATAA, *PDNS_TKEY_DATAA;

typedef struct
{
    PWSTR           pNameAlgorithm;
    PBYTE           pAlgorithmPacket;
    PBYTE           pSignature;
    PBYTE           pOtherData;
    LONGLONG        i64CreateTime;
    WORD            wFudgeTime;
    WORD            wOriginalXid;
    WORD            wError;
    WORD            wSigLength;
    WORD            wOtherLength;
    UCHAR           cAlgNameLength;
    BOOL            bPacketPointers;
}
DNS_TSIG_DATAW, *PDNS_TSIG_DATAW;

typedef struct
{
    PSTR            pNameAlgorithm;
    PBYTE           pAlgorithmPacket;
    PBYTE           pSignature;
    PBYTE           pOtherData;
    LONGLONG        i64CreateTime;
    WORD            wFudgeTime;
    WORD            wOriginalXid;
    WORD            wError;
    WORD            wSigLength;
    WORD            wOtherLength;
    UCHAR           cAlgNameLength;
    BOOL            bPacketPointers;
}
DNS_TSIG_DATAA, *PDNS_TSIG_DATAA;

//
//  MS only types -- only hit the wire in MS-MS zone transfer
//

typedef struct
{
    DWORD           dwMappingFlag;
    DWORD           dwLookupTimeout;
    DWORD           dwCacheTimeout;
    DWORD           cWinsServerCount;
    IP4_ADDRESS     WinsServers[1];
}
DNS_WINS_DATA, *PDNS_WINS_DATA;

typedef struct
{
    DWORD           dwMappingFlag;
    DWORD           dwLookupTimeout;
    DWORD           dwCacheTimeout;
    PWSTR           pNameResultDomain;
}
DNS_WINSR_DATAW, *PDNS_WINSR_DATAW;

typedef struct
{
    DWORD           dwMappingFlag;
    DWORD           dwLookupTimeout;
    DWORD           dwCacheTimeout;
    PSTR            pNameResultDomain;
}
DNS_WINSR_DATAA, *PDNS_WINSR_DATAA;

//
//  Unicode/ANSI record types
//

#ifdef UNICODE
typedef DNS_PTR_DATAW   DNS_PTR_DATA,   *PDNS_PTR_DATA;
typedef DNS_SOA_DATAW   DNS_SOA_DATA,   *PDNS_SOA_DATA;
typedef DNS_MINFO_DATAW DNS_MINFO_DATA, *PDNS_MINFO_DATA;
typedef DNS_MX_DATAW    DNS_MX_DATA,    *PDNS_MX_DATA;
typedef DNS_TXT_DATAW   DNS_TXT_DATA,   *PDNS_TXT_DATA;
typedef DNS_SIG_DATAW   DNS_SIG_DATA,   *PDNS_SIG_DATA;
typedef DNS_NXT_DATAW   DNS_NXT_DATA,   *PDNS_NXT_DATA;
typedef DNS_SRV_DATAW   DNS_SRV_DATA,   *PDNS_SRV_DATA;
typedef DNS_TKEY_DATAW  DNS_TKEY_DATA,  *PDNS_TKEY_DATA;
typedef DNS_TSIG_DATAW  DNS_TSIG_DATA,  *PDNS_TSIG_DATA;
typedef DNS_WINSR_DATAW DNS_WINSR_DATA, *PDNS_WINSR_DATA;
#else
typedef DNS_PTR_DATAA   DNS_PTR_DATA,   *PDNS_PTR_DATA;
typedef DNS_SOA_DATAA   DNS_SOA_DATA,   *PDNS_SOA_DATA;
typedef DNS_MINFO_DATAA DNS_MINFO_DATA, *PDNS_MINFO_DATA;
typedef DNS_MX_DATAA    DNS_MX_DATA,    *PDNS_MX_DATA;
typedef DNS_TXT_DATAA   DNS_TXT_DATA,   *PDNS_TXT_DATA;
typedef DNS_SIG_DATAA   DNS_SIG_DATA,   *PDNS_SIG_DATA;
typedef DNS_NXT_DATAA   DNS_NXT_DATA,   *PDNS_NXT_DATA;
typedef DNS_SRV_DATAA   DNS_SRV_DATA,   *PDNS_SRV_DATA;
typedef DNS_TKEY_DATAA  DNS_TKEY_DATA,  *PDNS_TKEY_DATA;
typedef DNS_TSIG_DATAA  DNS_TSIG_DATA,  *PDNS_TSIG_DATA;
typedef DNS_WINSR_DATAA DNS_WINSR_DATA, *PDNS_WINSR_DATA;
#endif

//
//  Length of non-fixed-length data types
//

#define DNS_TEXT_RECORD_LENGTH(StringCount) \
            (FIELD_OFFSET(DNS_TXT_DATA, pStringArray) + ((StringCount) * sizeof(PCHAR)))

#define DNS_NULL_RECORD_LENGTH(ByteCount) \
            (FIELD_OFFSET(DNS_NULL_DATA, Data) + (ByteCount))

#define DNS_WKS_RECORD_LENGTH(ByteCount) \
            (FIELD_OFFSET(DNS_WKS_DATA, BitMask) + (ByteCount))

#define DNS_WINS_RECORD_LENGTH(IpCount) \
            (FIELD_OFFSET(DNS_WINS_DATA, WinsServers) + ((IpCount) * sizeof(IP4_ADDRESS)))


//
//  Record flags
//

typedef struct _DnsRecordFlags
{
    DWORD   Section     : 2;
    DWORD   Delete      : 1;
    DWORD   CharSet     : 2;
    DWORD   Unused      : 3;

    DWORD   Reserved    : 24;
}
DNS_RECORD_FLAGS;


//
//  Wire Record Sections
//
//  Useable both in record flags "Section" and as index into
//  wire message header section counts.
//

typedef enum _DnsSection
{
    DnsSectionQuestion,
    DnsSectionAnswer,
    DnsSectionAuthority,
    DnsSectionAddtional,
}
DNS_SECTION;

//  Update message section names

#define DnsSectionZone      DnsSectionQuestion
#define DnsSectionPrereq    DnsSectionAnswer
#define DnsSectionUpdate    DnsSectionAuthority


//
//  Record flags as bit flags
//  These may be or'd together to set the fields
//

//  RR Section in packet

#define     DNSREC_SECTION      (0x00000003)

#define     DNSREC_QUESTION     (0x00000000)
#define     DNSREC_ANSWER       (0x00000001)
#define     DNSREC_AUTHORITY    (0x00000002)
#define     DNSREC_ADDITIONAL   (0x00000003)

//  RR Section in packet (update)

#define     DNSREC_ZONE         (0x00000000)
#define     DNSREC_PREREQ       (0x00000001)
#define     DNSREC_UPDATE       (0x00000002)

//  Delete RR (update) or No-exist (prerequisite)

#define     DNSREC_DELETE       (0x00000004)
#define     DNSREC_NOEXIST      (0x00000004)


//
//  Record \ RR set structure
//
//  Note:  The dwReserved flag serves to insure that the substructures
//  start on 64-bit boundaries.  Do NOT pack this structure, as the
//  substructures may contain pointers or int64 values which are
//  properly aligned unpacked.
//

#ifdef MIDL_PASS

#define PDNS_RECORD     PVOID

#else

typedef struct _DnsRecordW
{
    struct _DnsRecordW *    pNext;
    PWSTR                   pName;
    WORD                    wType;
    WORD                    wDataLength;    // Not referenced for DNS record types
                                            // defined above.
    union
    {
        DWORD               DW;     // flags as DWORD
        DNS_RECORD_FLAGS    S;      // flags as structure

    } Flags;

    DWORD                   dwTtl;
    DWORD                   dwReserved;

    //  Record Data

    union
    {
        DNS_A_DATA          A;
        DNS_SOA_DATAW       SOA, Soa;
        DNS_PTR_DATAW       PTR, Ptr,
                            NS, Ns,
                            CNAME, Cname,
                            MB, Mb,
                            MD, Md,
                            MF, Mf,
                            MG, Mg,
                            MR, Mr;
        DNS_MINFO_DATAW     MINFO, Minfo,
                            RP, Rp;
        DNS_MX_DATAW        MX, Mx,
                            AFSDB, Afsdb,
                            RT, Rt;
        DNS_TXT_DATAW       HINFO, Hinfo,
                            ISDN, Isdn,
                            TXT, Txt,
                            X25;
        DNS_NULL_DATA       Null;
        DNS_WKS_DATA        WKS, Wks;
        DNS_AAAA_DATA       AAAA;
        DNS_KEY_DATA        KEY, Key;
        DNS_SIG_DATAW       SIG, Sig;
        DNS_ATMA_DATA       ATMA, Atma;
        DNS_NXT_DATAW       NXT, Nxt;
        DNS_SRV_DATAW       SRV, Srv;
        DNS_TKEY_DATAW      TKEY, Tkey;
        DNS_TSIG_DATAW      TSIG, Tsig;
        DNS_WINS_DATA       WINS, Wins;
        DNS_WINSR_DATAW     WINSR, WinsR, NBSTAT, Nbstat;

    } Data;
}
DNS_RECORDW, *PDNS_RECORDW;

typedef struct _DnsRecordA
{
    struct _DnsRecordA *    pNext;
    PSTR                    pName;
    WORD                    wType;
    WORD                    wDataLength; // Not referenced for DNS record types
                                     // defined above.
    union
    {
        DWORD               DW;     // flags as DWORD
        DNS_RECORD_FLAGS    S;      // flags as structure

    } Flags;

    DWORD                   dwTtl;
    DWORD                   dwReserved;

    //  Record Data

    union
    {
        DNS_A_DATA          A;
        DNS_SOA_DATAA       SOA, Soa;
        DNS_PTR_DATAA       PTR, Ptr,
                            NS, Ns,
                            CNAME, Cname,
                            MB, Mb,
                            MD, Md,
                            MF, Mf,
                            MG, Mg,
                            MR, Mr;
        DNS_MINFO_DATAA     MINFO, Minfo,
                            RP, Rp;
        DNS_MX_DATAA        MX, Mx,
                            AFSDB, Afsdb,
                            RT, Rt;
        DNS_TXT_DATAA       HINFO, Hinfo,
                            ISDN, Isdn,
                            TXT, Txt,
                            X25;
        DNS_NULL_DATA       Null;
        DNS_WKS_DATA        WKS, Wks;
        DNS_AAAA_DATA       AAAA;
        DNS_KEY_DATA        KEY, Key;
        DNS_SIG_DATAA       SIG, Sig;
        DNS_ATMA_DATA       ATMA, Atma;
        DNS_NXT_DATAA       NXT, Nxt;
        DNS_SRV_DATAA       SRV, Srv;
        DNS_TKEY_DATAA      TKEY, Tkey;
        DNS_TSIG_DATAA      TSIG, Tsig;
        DNS_WINS_DATA       WINS, Wins;
        DNS_WINSR_DATAA     WINSR, WinsR, NBSTAT, Nbstat;

    } Data;
}
DNS_RECORDA, *PDNS_RECORDA;

#ifdef UNICODE
typedef DNS_RECORDW     DNS_RECORD, *PDNS_RECORD;
#else
typedef DNS_RECORDA     DNS_RECORD, *PDNS_RECORD;
#endif

//
//  Header or fixed size of DNS_RECORD
//

#define DNS_RECORD_FIXED_SIZE       FIELD_OFFSET( DNS_RECORD, Data )
#define SIZEOF_DNS_RECORD_HEADER    DNS_RECORD_FIXED_SIZE

#endif  // PRIVATE_DNS_RECORD



//
//  Resource record set building
//
//  pFirst points to first record in list.
//  pLast points to last record in list.
//

typedef struct _DnsRRSet
{
    PDNS_RECORD     pFirstRR;
    PDNS_RECORD     pLastRR;
}
DNS_RRSET, *PDNS_RRSET;


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

#define DNS_RRSET_INIT( rrset )                 \
        {                                       \
            PDNS_RRSET  _prrset = &(rrset);     \
            _prrset->pFirstRR = NULL;           \
            _prrset->pLastRR = (PDNS_RECORD) &_prrset->pFirstRR; \
        }

#define DNS_RRSET_ADD( rrset, pnewRR )          \
        {                                       \
            PDNS_RRSET  _prrset = &(rrset);     \
            PDNS_RECORD _prrnew = (pnewRR);     \
            _prrset->pLastRR->pNext = _prrnew;  \
            _prrset->pLastRR = _prrnew;         \
        }

#define DNS_RRSET_TERMINATE( rrset )            \
        {                                       \
            PDNS_RRSET  _prrset = &(rrset);     \
            _prrset->pLastRR->pNext = NULL;     \
        }


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

typedef enum _DNS_CHARSET
{
    DnsCharSetUnknown,
    DnsCharSetUnicode,
    DnsCharSetUtf8,
    DnsCharSetAnsi,
}
DNS_CHARSET;


PDNS_RECORD
WINAPI
DnsRecordCopyEx(
    IN      PDNS_RECORD     pRecord,
    IN      DNS_CHARSET     CharSetIn,
    IN      DNS_CHARSET     CharSetOut
    );

PDNS_RECORD
WINAPI
DnsRecordSetCopyEx(
    IN      PDNS_RECORD     pRecordSet,
    IN      DNS_CHARSET     CharSetIn,
    IN      DNS_CHARSET     CharSetOut
    );

#ifdef UNICODE
#define DnsRecordCopy(pRR)  \
        DnsRecordCopyEx( (pRR), DnsCharSetUnicode, DnsCharSetUnicode )
#define DnsRecordSetCopy(pRR)  \
        DnsRecordSetCopyEx( (pRR), DnsCharSetUnicode, DnsCharSetUnicode )
#else
#define DnsRecordCopy(pRR)  \
        DnsRecordCopyEx( (pRR), DnsCharSetAnsi, DnsCharSetAnsi )
#define DnsRecordSetCopy(pRR)  \
        DnsRecordSetCopyEx( (pRR), DnsCharSetAnsi, DnsCharSetAnsi )
#endif


//
//  Record Compare
//
//  Note:  these routines only compare records of the SAME character set.
//  (ANSI, unicode or UTF8).  Furthermore the routines assume the character
//  set is indicated within the record.  If compare of user created, rather
//  than DNS API created record lists is desired, then caller should use
//  DnsRecordCopy API and compare copies.
//

BOOL
WINAPI
DnsRecordCompare(
    IN      PDNS_RECORD     pRecord1,
    IN      PDNS_RECORD     pRecord2
    );

BOOL
WINAPI
DnsRecordSetCompare(
    IN OUT  PDNS_RECORD     pRR1,
    IN OUT  PDNS_RECORD     pRR2,
    OUT     PDNS_RECORD *   ppDiff1,
    OUT     PDNS_RECORD *   ppDiff2
    );

//
//  Detach next record set from record list
//

PDNS_RECORD
DnsRecordSetDetach(
    IN OUT  PDNS_RECORD     pRecordList
    );

//
//  Free structures returned from dnsapi.dll
//
//  Currently supported free structures:
//      Flat -- flat structure, including those allocated by DnsQueryConfig()
//      RecordList -- deep record list free, including sub-fields of DNS_RECORD;
//          includes those returned by DnsQuery() or DnsRecordSetCopy()
//

typedef enum
{
    DnsFreeFlat = 0,
    DnsFreeRecordList,
    DnsFreeParsedMessageFields
}
DNS_FREE_TYPE;

VOID
WINAPI
DnsFree(
    IN OUT  PVOID           pData,
    IN      DNS_FREE_TYPE   FreeType
    );

//
//  Backward compatibility with Win2K, do not use for XP+ applications
//
//  To free record lists, code
//      DnsFree( pRecordList, DnsFreeRecordList );
//

#define DnsFreeRecordListDeep   DnsFreeRecordList

VOID
WINAPI
DnsRecordListFree(
    IN OUT  PDNS_RECORD     pRecordList,
    IN      DNS_FREE_TYPE   FreeType
    );



//
//  DNS Query API
//

//
//  Options for DnsQuery
//

#define DNS_QUERY_STANDARD                  0x00000000
#define DNS_QUERY_ACCEPT_TRUNCATED_RESPONSE 0x00000001
#define DNS_QUERY_USE_TCP_ONLY              0x00000002
#define DNS_QUERY_NO_RECURSION              0x00000004
#define DNS_QUERY_BYPASS_CACHE              0x00000008

#define DNS_QUERY_NO_WIRE_QUERY             0x00000010
#define DNS_QUERY_NO_LOCAL_NAME             0x00000020
#define DNS_QUERY_NO_HOSTS_FILE             0x00000040
#define DNS_QUERY_NO_NETBT                  0x00000080

#define DNS_QUERY_WIRE_ONLY                 0x00000100
#define DNS_QUERY_RETURN_MESSAGE            0x00000200

#define DNS_QUERY_TREAT_AS_FQDN             0x00001000
#define DNS_QUERY_DONT_RESET_TTL_VALUES     0x00100000
#define DNS_QUERY_RESERVED                  0xff000000



//  Backward compatibility with Win2K
//  Do not use

#define DNS_QUERY_CACHE_ONLY                DNS_QUERY_NO_WIRE_QUERY



DNS_STATUS
WINAPI
DnsQuery_A(
    IN      PCSTR           pszName,
    IN      WORD            wType,
    IN      DWORD           Options,
    IN      PIP4_ARRAY      aipServers            OPTIONAL,
    IN OUT  PDNS_RECORD *   ppQueryResults        OPTIONAL,
    IN OUT  PVOID *         pReserved             OPTIONAL
    );

DNS_STATUS
WINAPI
DnsQuery_UTF8(
    IN      PCSTR           pszName,
    IN      WORD            wType,
    IN      DWORD           Options,
    IN      PIP4_ARRAY      aipServers            OPTIONAL,
    IN OUT  PDNS_RECORD *   ppQueryResults        OPTIONAL,
    IN OUT  PVOID *         pReserved             OPTIONAL
    );

DNS_STATUS
WINAPI
DnsQuery_W(
    IN      PCWSTR          pszName,
    IN      WORD            wType,
    IN      DWORD           Options,
    IN      PIP4_ARRAY      aipServers            OPTIONAL,
    IN OUT  PDNS_RECORD *   ppQueryResults        OPTIONAL,
    IN OUT  PVOID *         pReserved             OPTIONAL
    );

#ifdef UNICODE
#define DnsQuery DnsQuery_W
#else
#define DnsQuery DnsQuery_A
#endif




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

#define DNS_UPDATE_SECURITY_USE_DEFAULT     0x00000000
#define DNS_UPDATE_SECURITY_OFF             0x00000010
#define DNS_UPDATE_SECURITY_ON              0x00000020
#define DNS_UPDATE_SECURITY_ONLY            0x00000100
#define DNS_UPDATE_CACHE_SECURITY_CONTEXT   0x00000200
#define DNS_UPDATE_TEST_USE_LOCAL_SYS_ACCT  0x00000400
#define DNS_UPDATE_FORCE_SECURITY_NEGO      0x00000800
#define DNS_UPDATE_TRY_ALL_MASTER_SERVERS   0x00001000
#define DNS_UPDATE_SKIP_NO_UPDATE_ADAPTERS  0x00002000
#define DNS_UPDATE_REMOTE_SERVER            0x00004000
#define DNS_UPDATE_RESERVED                 0xffff0000


//
//  Note:  pCredentials paramater is currently respectively
//  PSEC_WINNT_AUTH_IDENTITY_W or PSEC_WINNT_AUTH_IDENTITY_A.
//  Using PVOID to obviate the need for including rpcdce.h
//  in order to include this file and to leave open the
//  possibility of alternative credential specifications in
//  the future.
//

DNS_STATUS
WINAPI
DnsAcquireContextHandle_W(
    IN      DWORD           CredentialFlags,
    IN      PVOID           pCredentials,       OPTIONAL
    //IN      PSEC_WINNT_AUTH_IDENTITY_W  pCredentials,
    OUT     PHANDLE         pContextHandle
    );

DNS_STATUS
WINAPI
DnsAcquireContextHandle_A(
    IN      DWORD           CredentialFlags,
    IN      PVOID           pCredentials,       OPTIONAL
    //IN      PSEC_WINNT_AUTH_IDENTITY_A  pCredentials,
    OUT     PHANDLE         pContextHandle
    );

#ifdef UNICODE
#define DnsAcquireContextHandle DnsAcquireContextHandle_W
#else
#define DnsAcquireContextHandle DnsAcquireContextHandle_A
#endif


VOID
WINAPI
DnsReleaseContextHandle(
    IN      HANDLE          hContext
    );

//
//  Dynamic Update API
//

DNS_STATUS
WINAPI
DnsModifyRecordsInSet_W(
    IN      PDNS_RECORD     pAddRecords,
    IN      PDNS_RECORD     pDeleteRecords,
    IN      DWORD           Options,
    IN      HANDLE          hContext,       OPTIONAL
    IN      PIP4_ARRAY      pServerList,    OPTIONAL
    IN      PVOID           pReserved
    );

DNS_STATUS
WINAPI
DnsModifyRecordsInSet_A(
    IN      PDNS_RECORD     pAddRecords,
    IN      PDNS_RECORD     pDeleteRecords,
    IN      DWORD           Options,
    IN      HANDLE          hContext,       OPTIONAL
    IN      PIP4_ARRAY      pServerList,    OPTIONAL
    IN      PVOID           pReserved
    );

DNS_STATUS
WINAPI
DnsModifyRecordsInSet_UTF8(
    IN      PDNS_RECORD     pAddRecords,
    IN      PDNS_RECORD     pDeleteRecords,
    IN      DWORD           Options,
    IN      HANDLE          hContext,       OPTIONAL
    IN      PIP4_ARRAY      pServerList,    OPTIONAL
    IN      PVOID           pReserved
    );

#ifdef UNICODE
#define DnsModifyRecordsInSet  DnsModifyRecordsInSet_W
#else
#define DnsModifyRecordsInSet  DnsModifyRecordsInSet_A
#endif


DNS_STATUS
WINAPI
DnsReplaceRecordSetW(
    IN      PDNS_RECORD     pNewSet,
    IN      DWORD           Options,
    IN      HANDLE          hContext,       OPTIONAL
    IN      PIP4_ARRAY      pServerList,    OPTIONAL
    IN      PVOID           pReserved
    );

DNS_STATUS
WINAPI
DnsReplaceRecordSetA(
    IN      PDNS_RECORD     pNewSet,
    IN      DWORD           Options,
    IN      HANDLE          hContext,       OPTIONAL
    IN      PIP4_ARRAY      pServerList,    OPTIONAL
    IN      PVOID           pReserved
    );

DNS_STATUS
WINAPI
DnsReplaceRecordSetUTF8(
    IN      PDNS_RECORD     pNewSet,
    IN      DWORD           Options,
    IN      HANDLE          hContext,       OPTIONAL
    IN      PIP4_ARRAY      pServerList,    OPTIONAL
    IN      PVOID           pReserved
    );

#ifdef UNICODE
#define DnsReplaceRecordSet  DnsReplaceRecordSetW
#else
#define DnsReplaceRecordSet  DnsReplaceRecordSetA
#endif



//
//  DNS name validation
//

typedef enum _DNS_NAME_FORMAT
{
    DnsNameDomain,
    DnsNameDomainLabel,
    DnsNameHostnameFull,
    DnsNameHostnameLabel,
    DnsNameWildcard,
    DnsNameSrvRecord
}
DNS_NAME_FORMAT;


DNS_STATUS
DnsValidateName_UTF8(
    IN      LPCSTR          pszName,
    IN      DNS_NAME_FORMAT Format
    );

DNS_STATUS
DnsValidateName_W(
    IN      LPCWSTR         pwszName,
    IN      DNS_NAME_FORMAT Format
    );

DNS_STATUS
DnsValidateName_A(
    IN      LPCSTR          pszName,
    IN      DNS_NAME_FORMAT Format
    );

#ifdef UNICODE
#define DnsValidateName(p,f)    DnsValidateName_W( (p), (f) )
#else
#define DnsValidateName(p,f)    DnsValidateName_A( (p), (f) )
#endif


//
//  DNS name comparison
//

BOOL
WINAPI
DnsNameCompare_A(
    IN      LPSTR           pName1,
    IN      LPSTR           pName2
    );

BOOL
WINAPI
DnsNameCompare_W(
    IN      LPWSTR          pName1,
    IN      LPWSTR          pName2
    );

#ifdef UNICODE
#define DnsNameCompare(n1,n2)   DnsNameCompare_W( (n1),(n2) )
#else
#define DnsNameCompare(n1,n2)   DnsNameCompare_A( (n1),(n2) )
#endif



//
//  DNS message "roll-your-own" routines
//

typedef struct _DNS_MESSAGE_BUFFER
{
    DNS_HEADER  MessageHead;
    CHAR        MessageBody[1];
}
DNS_MESSAGE_BUFFER, *PDNS_MESSAGE_BUFFER;

BOOL
WINAPI
DnsWriteQuestionToBuffer_W(
    IN OUT  PDNS_MESSAGE_BUFFER pDnsBuffer,
    IN OUT  PDWORD              pdwBufferSize,
    IN      LPWSTR              pszName,
    IN      WORD                wType,
    IN      WORD                Xid,
    IN      BOOL                fRecursionDesired
    );

BOOL WINAPI
DnsWriteQuestionToBuffer_UTF8(
    IN OUT  PDNS_MESSAGE_BUFFER pDnsBuffer,
    IN OUT  LPDWORD             pdwBufferSize,
    IN      LPSTR               pszName,
    IN      WORD                wType,
    IN      WORD                Xid,
    IN      BOOL                fRecursionDesired
    );

DNS_STATUS
WINAPI
DnsExtractRecordsFromMessage_W(
    IN      PDNS_MESSAGE_BUFFER pDnsBuffer,
    IN      WORD                wMessageLength,
    OUT     PDNS_RECORD *       ppRecord
    );

DNS_STATUS
WINAPI
DnsExtractRecordsFromMessage_UTF8(
    IN      PDNS_MESSAGE_BUFFER pDnsBuffer,
    IN      WORD                wMessageLength,
    OUT     PDNS_RECORD *       ppRecord
    );


#ifdef __cplusplus
}
#endif  // __cplusplus

#endif // _WINDNS_INCLUDED_


