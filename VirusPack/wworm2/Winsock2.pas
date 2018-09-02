{
  Delphi Winsock2 Static Unit by Aphex
  http://www.iamaphex.cjb.net
  unremote@knology.net
}

unit Winsock2;
{$D-,L-,O+,Q-,R-,Y-,S-}
interface

{$ALIGN OFF}
{$RANGECHECKS OFF}
{$WRITEABLECONST OFF}

uses Windows;

const
  WINSOCK_VERSION = $0202;
  WINSOCK2_DLL = 'WS2_32.DLL';

type
  u_char  = Byte;
  u_short = Word;
  u_int   = DWORD;
  u_long  = DWORD;
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
  FD_SETSIZE = 64;

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
  IOC_VOID = $20000000;
  IOC_OUT = $40000000;
  IOC_IN = $80000000;
  IOC_INOUT = (IOC_IN or IOC_OUT);
  FIONREAD = IOC_OUT or (SizeOf(Longint) shl 16) or (Ord('f') shl 8) or 127;
  FIONBIO  = IOC_IN  or (SizeOf(Longint) shl 16) or (Ord('f') shl 8) or 126;
  FIOASYNC = IOC_IN  or (SizeOf(Longint) shl 16) or (Ord('f') shl 8) or 125;
  SIOCSHIWAT   = IOC_IN  or (SizeOf(Longint) shl 16) or (Ord('s') shl 8);
  SIOCGHIWAT   = IOC_OUT or (SizeOf(Longint) shl 16) or (Ord('s') shl 8) or 1;
  SIOCSLOWAT   = IOC_IN  or (SizeOf(Longint) shl 16) or (Ord('s') shl 8) or 2;
  SIOCGLOWAT   = IOC_OUT or (SizeOf(Longint) shl 16) or (Ord('s') shl 8) or 3;
  SIOCATMARK   = IOC_OUT or (SizeOf(Longint) shl 16) or (Ord('s') shl 8) or 7;

type
  PHostEnt = ^THostEnt;
  THostEnt = packed record
    h_name: PChar;
    h_aliases: ^PChar;
    h_addrtype: Smallint;
    h_length: Smallint;
    case Byte of
      0: (h_addr_list: ^PChar);
      1: (h_addr: ^PChar);
  end;
  PNetEnt = ^TNetEnt;
  TNetEnt = packed record
    n_name: PChar;
    n_aliases: ^PChar;
    n_addrtype: Smallint;
    n_net: u_long;
  end;
  PServEnt = ^TServEnt;
  TServEnt = packed record
    s_name: PChar;
    s_aliases: ^PChar;
    s_port: Smallint;
    s_proto: PChar;
  end;
  PProtoEnt = ^TProtoEnt;
  TProtoEnt = packed record
    p_name: PChar;
    p_aliases: ^Pchar;
    p_proto: Smallint;
  end;

const
  IPPROTO_IP = 0;
  IPPROTO_ICMP = 1;
  IPPROTO_IGMP = 2;
  IPPROTO_GGP = 3;
  IPPROTO_TCP = 6;
  IPPROTO_PUP = 12;
  IPPROTO_UDP = 17;
  IPPROTO_IDP = 22;
  IPPROTO_IPV6 = 41;
  IPPROTO_ND = 77;
  IPPROTO_ICLFXBM = 78;
  IPPROTO_RAW = 255;
  IPPROTO_MAX = 256;
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
  IPPORT_TFTP        =  69;
  IPPORT_RJE         =  77;
  IPPORT_FINGER      =  79;
  IPPORT_TTYLINK     =  87;
  IPPORT_SUPDUP      =  95;
  IPPORT_EXECSERVER  = 512;
  IPPORT_LOGINSERVER = 513;
  IPPORT_CMDSERVER   = 514;
  IPPORT_EFSSERVER   = 520;
  IPPORT_BIFFUDP     = 512;
  IPPORT_WHOSERVER   = 513;
  IPPORT_ROUTESERVER = 520;
  IPPORT_RESERVED    =1024;
  IMPLINK_IP         = 155;
  IMPLINK_LOWEXPER   = 156;
  IMPLINK_HIGHEXPER  = 158;
  TF_DISCONNECT      = $01;
  TF_REUSE_SOCKET    = $02;
  TF_WRITE_BEHIND    = $04;
  INVALID_SOCKET     = TSocket(not(0));
  SOCKET_ERROR       = -1;
  FROM_PROTOCOL_INFO = -1;
  SOCK_STREAM     = 1;
  SOCK_DGRAM      = 2;
  SOCK_RAW        = 3;
  SOCK_RDM        = 4;
  SOCK_SEQPACKET  = 5;
  SO_DEBUG            = $0001;
  SO_ACCEPTCONN       = $0002;
  SO_REUSEADDR        = $0004;
  SO_KEEPALIVE        = $0008;
  SO_DONTROUTE        = $0010;
  SO_BROADCAST        = $0020;
  SO_USELOOPBACK      = $0040;
  SO_LINGER           = $0080;
  SO_OOBINLINE        = $0100;
  SO_DONTLINGER       = not SO_LINGER;
  SO_EXCLUSIVEADDRUSE = not SO_REUSEADDR;
  SO_SNDBUF           = $1001;
  SO_RCVBUF           = $1002;
  SO_SNDLOWAT         = $1003;
  SO_RCVLOWAT         = $1004;
  SO_SNDTIMEO         = $1005;
  SO_RCVTIMEO         = $1006;
  SO_ERROR            = $1007;
  SO_TYPE             = $1008;
  SO_CONNDATA         = $7000;
  SO_CONNOPT          = $7001;
  SO_DISCDATA         = $7002;
  SO_DISCOPT          = $7003;
  SO_CONNDATALEN      = $7004;
  SO_CONNOPTLEN       = $7005;
  SO_DISCDATALEN      = $7006;
  SO_DISCOPTLEN       = $7007;
  SO_OPENTYPE         = $7008;
  SO_SYNCHRONOUS_ALERT    = $10;
  SO_SYNCHRONOUS_NONALERT = $20;
  SO_MAXDG                 = $7009;
  SO_MAXPATHDG             = $700A;
  SO_UPDATE_ACCEPT_CONTEXT = $700B;
  SO_CONNECT_TIME          = $700C;
  TCP_NODELAY              = $0001;
  TCP_BSDURGENT            = $7000;
  SO_GROUP_ID              = $2001;
  SO_GROUP_PRIORITY        = $2002;
  SO_MAX_MSG_SIZE          = $2003;
  SO_Protocol_InfoA        = $2004;
  SO_Protocol_InfoW        = $2005;
{$IFDEF UNICODE}
  SO_Protocol_Info         = SO_Protocol_InfoW;
{$ELSE}
  SO_Protocol_Info         = SO_Protocol_InfoA;
{$ENDIF}
  PVD_CONFIG               = $3001;
  SO_CONDITIONAL_ACCEPT    = $3002;
  AF_UNSPEC       = 0;
  AF_UNIX         = 1;
  AF_INET         = 2;
  AF_IMPLINK      = 3;
  AF_PUP          = 4;
  AF_CHAOS        = 5;
  AF_IPX          = 6;
  AF_NS           = AF_IPX;
  AF_ISO          = 7;
  AF_OSI          = AF_ISO;
  AF_ECMA         = 8;
  AF_DATAKIT      = 9;
  AF_CCITT        = 10;
  AF_SNA          = 11;
  AF_DECnet       = 12;
  AF_DLI          = 13;
  AF_LAT          = 14;
  AF_HYLINK       = 15;
  AF_APPLETALK    = 16;
  AF_NETBIOS      = 17;
  AF_VOICEVIEW    = 18;
  AF_FIREFOX      = 19;
  AF_UNKNOWN1     = 20;
  AF_BAN          = 21;
  AF_ATM          = 22;
  AF_INET6        = 23;
  AF_CLUSTER      = 24;
  AF_12844        = 25;
  AF_IRDA         = 26;
  AF_NETDES       = 28;
  AF_TCNPROCESS   = 29;
  AF_TCNMESSAGE   = 30;
  AF_ICLFXBM      = 31;
  AF_MAX          = 32;
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
  PSockProto = ^TSockProto;
  TSockProto = packed record
    sp_family   : u_short;
    sp_protocol : u_short;
  end;
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
  SOL_SOCKET       = $ffff;
  MSG_OOB          = $1;
  MSG_PEEK         = $2;
  MSG_DONTROUTE    = $4;
  MSG_PARTIAL      = $8000;
  MSG_INTERRUPT    = $10;
  MSG_MAXIOVLEN    = 16;
  MAXGETHOSTSTRUCT = 1024;
  SOMAXCONN        = $7fffffff;
  FD_READ_BIT                     = 0;
  FD_WRITE_BIT                    = 1;
  FD_OOB_BIT                      = 2;
  FD_ACCEPT_BIT                   = 3;
  FD_CONNECT_BIT                  = 4;
  FD_CLOSE_BIT                    = 5;
  FD_QOS_BIT                      = 6;
  FD_GROUP_QOS_BIT                = 7;
  FD_ROUTING_INTERFACE_CHANGE_BIT = 8;
  FD_ADDRESS_LIST_CHANGE_BIT      = 9;
  FD_MAX_EVENTS    = 10;
  FD_READ       = (1 shl FD_READ_BIT);
  FD_WRITE      = (1 shl FD_WRITE_BIT);
  FD_OOB        = (1 shl FD_OOB_BIT);
  FD_ACCEPT     = (1 shl FD_ACCEPT_BIT);
  FD_CONNECT    = (1 shl FD_CONNECT_BIT);
  FD_CLOSE      = (1 shl FD_CLOSE_BIT);
  FD_QOS        = (1 shl FD_QOS_BIT);
  FD_GROUP_QOS  = (1 shl FD_GROUP_QOS_BIT);
  FD_ROUTING_INTERFACE_CHANGE = (1 shl FD_ROUTING_INTERFACE_CHANGE_BIT);
  FD_ADDRESS_LIST_CHANGE      = (1 shl FD_ADDRESS_LIST_CHANGE_BIT);
  FD_ALL_EVENTS = (1 shl FD_MAX_EVENTS) - 1;
  WSABASEERR                 = 10000;
  WSAEINTR                   = WSABASEERR+  4;
  WSAEBADF                   = WSABASEERR+  9;
  WSAEACCES                  = WSABASEERR+ 13;
  WSAEFAULT                  = WSABASEERR+ 14;
  WSAEINVAL                  = WSABASEERR+ 22;
  WSAEMFILE                  = WSABASEERR+ 24;
  WSAEWOULDBLOCK             = WSABASEERR+ 35;
  WSAEINPROGRESS             = WSABASEERR+ 36;
  WSAEALREADY                = WSABASEERR+ 37;
  WSAENOTSOCK                = WSABASEERR+ 38;
  WSAEDESTADDRREQ            = WSABASEERR+ 39;
  WSAEMSGSIZE                = WSABASEERR+ 40;
  WSAEPROTOTYPE              = WSABASEERR+ 41;
  WSAENOPROTOOPT             = WSABASEERR+ 42;
  WSAEPROTONOSUPPORT         = WSABASEERR+ 43;
  WSAESOCKTNOSUPPORT         = WSABASEERR+ 44;
  WSAEOPNOTSUPP              = WSABASEERR+ 45;
  WSAEPFNOSUPPORT            = WSABASEERR+ 46;
  WSAEAFNOSUPPORT            = WSABASEERR+ 47;
  WSAEADDRINUSE              = WSABASEERR+ 48;
  WSAEADDRNOTAVAIL           = WSABASEERR+ 49;
  WSAENETDOWN                = WSABASEERR+ 50;
  WSAENETUNREACH             = WSABASEERR+ 51;
  WSAENETRESET               = WSABASEERR+ 52;
  WSAECONNABORTED            = WSABASEERR+ 53;
  WSAECONNRESET              = WSABASEERR+ 54;
  WSAENOBUFS                 = WSABASEERR+ 55;
  WSAEISCONN                 = WSABASEERR+ 56;
  WSAENOTCONN                = WSABASEERR+ 57;
  WSAESHUTDOWN               = WSABASEERR+ 58;
  WSAETOOMANYREFS            = WSABASEERR+ 59;
  WSAETIMEDOUT               = WSABASEERR+ 60;
  WSAECONNREFUSED            = WSABASEERR+ 61;
  WSAELOOP                   = WSABASEERR+ 62;
  WSAENAMETOOLONG            = WSABASEERR+ 63;
  WSAEHOSTDOWN               = WSABASEERR+ 64;
  WSAEHOSTUNREACH            = WSABASEERR+ 65;
  WSAENOTEMPTY               = WSABASEERR+ 66;
  WSAEPROCLIM                = WSABASEERR+ 67;
  WSAEUSERS                  = WSABASEERR+ 68;
  WSAEDQUOT                  = WSABASEERR+ 69;
  WSAESTALE                  = WSABASEERR+ 70;
  WSAEREMOTE                 = WSABASEERR+ 71;
  WSASYSNOTREADY             = WSABASEERR+ 91;
  WSAVERNOTSUPPORTED         = WSABASEERR+ 92;
  WSANOTINITIALISED          = WSABASEERR+ 93;
  WSAEDISCON                 = WSABASEERR+101;
  WSAENOMORE                 = WSABASEERR+102;
  WSAECANCELLED              = WSABASEERR+103;
  WSAEINVALIDPROCTABLE       = WSABASEERR+104;
  WSAEINVALIDPROVIDER        = WSABASEERR+105;
  WSAEPROVIDERFAILEDINIT     = WSABASEERR+106;
  WSASYSCALLFAILURE          = WSABASEERR+107;
  WSASERVICE_NOT_FOUND       = WSABASEERR+108;
  WSATYPE_NOT_FOUND          = WSABASEERR+109;
  WSA_E_NO_MORE              = WSABASEERR+110;
  WSA_E_CANCELLED            = WSABASEERR+111;
  WSAEREFUSED                = WSABASEERR+112;
  WSAHOST_NOT_FOUND          = WSABASEERR+1001;
  HOST_NOT_FOUND             = WSAHOST_NOT_FOUND;
  WSATRY_AGAIN               = WSABASEERR+1002;
  TRY_AGAIN                  = WSATRY_AGAIN;
  WSANO_RECOVERY             = WSABASEERR+1003;
  NO_RECOVERY                = WSANO_RECOVERY;
  WSANO_DATA                 = WSABASEERR+1004;
  NO_DATA                    = WSANO_DATA;
  WSANO_ADDRESS              = WSANO_DATA;
  NO_ADDRESS                 = WSANO_ADDRESS;
  WSA_QOS_RECEIVERS          = WSABASEERR+1005;
  WSA_QOS_SENDERS            = WSABASEERR+1006;
  WSA_QOS_NO_SENDERS         = WSABASEERR+1007;
  WSA_QOS_NO_RECEIVERS       = WSABASEERR+1008;
  WSA_QOS_REQUEST_CONFIRMED  = WSABASEERR+1009;
  WSA_QOS_ADMISSION_FAILURE  = WSABASEERR+1010;
  WSA_QOS_POLICY_FAILURE     = WSABASEERR+1011;
  WSA_QOS_BAD_STYLE          = WSABASEERR+1012;
  WSA_QOS_BAD_OBJECT         = WSABASEERR+1013;
  WSA_QOS_TRAFFIC_CTRL_ERROR = WSABASEERR+1014;
  WSA_QOS_GENERIC_ERROR      = WSABASEERR+1015;
  WSA_QOS_ESERVICETYPE       = WSABASEERR+1016;
  WSA_QOS_EFLOWSPEC          = WSABASEERR+1017;
  WSA_QOS_EPROVSPECBUF       = WSABASEERR+1018;
  WSA_QOS_EFILTERSTYLE       = WSABASEERR+1019;
  WSA_QOS_EFILTERTYPE        = WSABASEERR+1020;
  WSA_QOS_EFILTERCOUNT       = WSABASEERR+1021;
  WSA_QOS_EOBJLENGTH         = WSABASEERR+1022;
  WSA_QOS_EFLOWCOUNT         = WSABASEERR+1023;
  WSA_QOS_EUNKOWNPSOBJ       = WSABASEERR+1024;
  WSA_QOS_EPOLICYOBJ         = WSABASEERR+1025;
  WSA_QOS_EFLOWDESC          = WSABASEERR+1026;
  WSA_QOS_EPSFLOWSPEC        = WSABASEERR+1027;
  WSA_QOS_EPSFILTERSPEC      = WSABASEERR+1028;
  WSA_QOS_ESDMODEOBJ         = WSABASEERR+1029;
  WSA_QOS_ESHAPERATEOBJ      = WSABASEERR+1030;
  WSA_QOS_RESERVED_PETYPE    = WSABASEERR+1031;
  WSA_IO_PENDING             = ERROR_IO_PENDING;
  WSA_IO_INCOMPLETE          = ERROR_IO_INCOMPLETE;
  WSA_INVALID_HANDLE         = ERROR_INVALID_HANDLE;
  WSA_INVALID_PARAMETER      = ERROR_INVALID_PARAMETER;
  WSA_NOT_ENOUGH_MEMORY      = ERROR_NOT_ENOUGH_MEMORY;
  WSA_OPERATION_ABORTED      = ERROR_OPERATION_ABORTED;
  WSA_INVALID_EVENT          = WSAEVENT(nil);
  WSA_MAXIMUM_WAIT_EVENTS    = MAXIMUM_WAIT_OBJECTS;
  WSA_WAIT_FAILED            = $ffffffff;
  WSA_WAIT_EVENT_0           = WAIT_OBJECT_0;
  WSA_WAIT_IO_COMPLETION     = WAIT_IO_COMPLETION;
  WSA_WAIT_TIMEOUT           = WAIT_TIMEOUT;
  WSA_INFINITE               = INFINITE;
  WSADESCRIPTION_LEN         = 256;
  WSASYS_STATUS_LEN          = 128;

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
  WSAOVERLAPPED   = TOverlapped;
  TWSAOverlapped  = WSAOverlapped;
  PWSAOverlapped  = ^WSAOverlapped;
  LPWSAOVERLAPPED = PWSAOverlapped;
  WSABUF = packed record
    len: U_LONG;
    buf: PChar;
  end;
  PWSABUF = ^WSABUF;
  LPWSABUF = PWSABUF;
  TServiceType = LongInt;
  TFlowSpec = packed record
    TokenRate,
    TokenBucketSize,
    PeakBandwidth,
    Latency,
    DelayVariation : LongInt;
    ServiceType : TServiceType;
    MaxSduSize, MinimumPolicedSize : LongInt;
  end;
  PFlowSpec = ^TFLOWSPEC;
  QOS = packed record
    SendingFlowspec: TFlowSpec;
    ReceivingFlowspec: TFlowSpec;
    ProviderSpecific: WSABUF;
  end;
  TQualityOfService = QOS;
  PQOS = ^QOS;
  LPQOS = PQOS;
const
  SERVICETYPE_NOTRAFFIC             =  $00000000;
  SERVICETYPE_BESTEFFORT            =  $00000001;
  SERVICETYPE_CONTROLLEDLOAD        =  $00000002;
  SERVICETYPE_GUARANTEED            =  $00000003;
  SERVICETYPE_NETWORK_UNAVAILABLE   =  $00000004;
  SERVICETYPE_GENERAL_INFORMATION   =  $00000005;
  SERVICETYPE_NOCHANGE              =  $00000006;
  SERVICE_IMMEDIATE_TRAFFIC_CONTROL =  $80000000;
  CF_ACCEPT = $0000;
  CF_REJECT = $0001;
  CF_DEFER  = $0002;
  SD_RECEIVE = $00;
  SD_SEND    = $01;
  SD_BOTH    = $02;
  SG_UNCONSTRAINED_GROUP = $01;
  SG_CONSTRAINED_GROUP   = $02;

type
  GROUP = DWORD;
  TWSANetworkEvents = record
    lNetworkEvents: LongInt;
    iErrorCode: Array[0..FD_MAX_EVENTS-1] of Integer;
  end;
  PWSANetworkEvents = ^TWSANetworkEvents;
  LPWSANetworkEvents = PWSANetworkEvents;
  TGUID = packed record
    D1: LongInt;
    D2: Word;
    D3: Word;
    D4: Array[0..7] of Byte;
  end;
  PGUID = ^TGUID;
  LPGUID = PGUID;
const
  MAX_PROTOCOL_CHAIN = 7;
  BASE_PROTOCOL      = 1;
  LAYERED_PROTOCOL   = 0;
  WSAPROTOCOL_LEN    = 255;

type
  TWSAProtocolChain = record
    ChainLen: Integer;
    ChainEntries: Array[0..MAX_PROTOCOL_CHAIN-1] of LongInt;
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
  end;
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
  PFL_MULTIPLE_PROTO_ENTRIES   = $00000001;
  PFL_RECOMMENDED_PROTO_ENTRY  = $00000002;
  PFL_HIDDEN                   = $00000004;
  PFL_MATCHES_PROTOCOL_ZERO    = $00000008;
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
  JL_SENDER_ONLY   = $01;
  JL_RECEIVER_ONLY = $02;
  JL_BOTH          = $04;
  WSA_FLAG_OVERLAPPED        = $01;
  WSA_FLAG_MULTIPOINT_C_ROOT = $02;
  WSA_FLAG_MULTIPOINT_C_LEAF = $04;
  WSA_FLAG_MULTIPOINT_D_ROOT = $08;
  WSA_FLAG_MULTIPOINT_D_LEAF = $10;
  IOC_UNIX      = $00000000;
  IOC_WS2       = $08000000;
  IOC_PROTOCOL  = $10000000;
  IOC_VENDOR    = $18000000;
  SIO_ASSOCIATE_HANDLE                =  1 or IOC_WS2 or IOC_IN;
  SIO_ENABLE_CIRCULAR_QUEUEING        =  2 or IOC_WS2 or IOC_VOID;
  SIO_FIND_ROUTE                      =  3 or IOC_WS2 or IOC_OUT;
  SIO_FLUSH                           =  4 or IOC_WS2 or IOC_VOID;
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
  SIO_ADDRESS_LIST_CHANGE             = 23 or IOC_WS2 or IOC_VOID;
  SIO_QUERY_TARGET_PNP_HANDLE         = 24 or IOC_WS2 or IOC_OUT;
  SIO_ADDRESS_LIST_SORT               = 25 or IOC_WS2 or IOC_INOUT;

  TH_NETDEV = $00000001;
  TH_TAPI   = $00000002;

type
  TBLOB = packed record
    cbSize : U_LONG;
    pBlobData : PBYTE;
  end;
  PBLOB = ^TBLOB;

const
  SERVICE_MULTIPLE = $00000001;
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
  RES_UNUSED_1    = $00000001;
  RES_FLUSH_CACHE = $00000002;
  RES_SERVICE     = $00000004;
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

type
  SOCKET_ADDRESS = packed record
    lpSockaddr : PSockAddr;
    iSockaddrLength : Integer;
  end;
  PSOCKET_ADDRESS = ^SOCKET_ADDRESS;

  CSADDR_INFO = packed record
    LocalAddr, RemoteAddr  : SOCKET_ADDRESS;
    iSocketType, iProtocol : LongInt;
  end;
  PCSADDR_INFO = ^CSADDR_INFO;
  LPCSADDR_INFO = ^CSADDR_INFO;
  SOCKET_ADDRESS_LIST = packed record
    iAddressCount : Integer;
    Address       : Array [0..0] of SOCKET_ADDRESS;
  end;
  LPSOCKET_ADDRESS_LIST = ^SOCKET_ADDRESS_LIST;
  AFProtocols = record
    iAddressFamily : Integer;
    iProtocol      : Integer;
  end;
  TAFProtocols = AFProtocols;
  PAFProtocols = ^TAFProtocols;
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

  RESULT_IS_ALIAS = $0001;

type
  TWSAeSetServiceOp = ( RNRSERVICE_REGISTER{=0}, RNRSERVICE_DEREGISTER, RNRSERVICE_DELETE );
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
  end;
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
{$ENDIF}
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
    fActive        : DWORD;
    dwVersion      : DWORD;
    lpszIdentifier : PChar;
  end;
  PWSANameSpace_InfoA = ^TWSANameSpace_InfoA;
  LPWSANameSpace_InfoA = PWSANameSpace_InfoA;

  TWSANameSpace_InfoW = packed record
    NSProviderId   : TGUID;
    dwNameSpace    : DWORD;
    fActive        : DWORD;
    dwVersion      : DWORD;
    lpszIdentifier : PWideChar;
  end;
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

type
  LPCONDITIONPROC = function (lpCallerId: LPWSABUF; lpCallerData : LPWSABUF; lpSQOS,lpGQOS : LPQOS; lpCalleeId,lpCalleeData : LPWSABUF; g : GROUP; dwCallbackData : DWORD ) : Integer; stdcall;
  LPWSAOVERLAPPED_COMPLETION_ROUTINE = procedure ( const dwError, cbTransferred : DWORD; const lpOverlapped : LPWSAOVERLAPPED; const dwFlags : DWORD ); stdcall;

function WSAStartup( const wVersionRequired: word; var WSData: TWSAData ): Integer; stdcall;
function WSACleanup: Integer; stdcall;
function accept( const s: TSocket; addr: PSockAddr; addrlen: PInteger ): TSocket; stdcall;
function bind( const s: TSocket; const name: PSockAddr; const namelen: Integer ): Integer; stdcall;
function closesocket( const s: TSocket ): Integer; stdcall;
function connect( const s: TSocket; const name: PSockAddr; const namelen: Integer): Integer; stdcall;
function ioctlsocket( const s: TSocket; const cmd: DWORD; var arg: u_long ): Integer; stdcall;
function getpeername( const s: TSocket; const name: PSockAddr; var namelen: Integer ): Integer; stdcall;
function getsockname( const s: TSocket; const name: PSockAddr; var namelen: Integer ): Integer; stdcall;
function getsockopt( const s: TSocket; const level, optname: Integer; optval: PChar; var optlen: Integer ): Integer; stdcall;
function htonl(hostlong: u_long): u_long; stdcall;
function htons(hostshort: u_short): u_short; stdcall;
function inet_addr(cp: PChar): u_long; stdcall;
function inet_ntoa(inaddr: TInAddr): PChar; stdcall;
function listen( const s: TSocket; backlog: Integer ): Integer; stdcall;
function ntohl(netlong: u_long): u_long; stdcall;
function ntohs(netshort: u_short): u_short; stdcall;
function recv( const s: TSocket; var Buf; len, flags: Integer ): Integer; stdcall;
function recvfrom( const s: TSocket; var Buf; len, flags: Integer; from: PSockAddr; fromlen: PInteger ): Integer; stdcall;
function select(nfds: Integer; readfds, writefds, exceptfds: PFDSet; timeout: PTimeVal ): Integer; stdcall;
function send( const s: TSocket; var Buf; len, flags: Integer ): Integer; stdcall;
function sendto( const s: TSocket; var Buf; const len, flags: Integer; var addrto: TSockAddr; const tolen: Integer ): Integer; stdcall;
function setsockopt( const s: TSocket; const level, optname: Integer; optval: PChar; const optlen: Integer ): Integer; stdcall;
function shutdown( const s: TSocket; const how: Integer ): Integer; stdcall;
function socket( const af, struct, protocol: Integer ): TSocket; stdcall;
function gethostbyaddr( addr: Pointer; const len, addrtype: Integer ): PHostEnt; stdcall;
function gethostbyname( name: PChar ): PHostEnt; stdcall;
function gethostname( name: PChar; len: Integer ): Integer; stdcall;
function getservbyport( const port: Integer; const proto: PChar ): PServEnt; stdcall;
function getservbyname( const name, proto: PChar ): PServEnt; stdcall;
function getprotobynumber( const proto: Integer ): PProtoEnt; stdcall;
function getprotobyname( const name: PChar ): PProtoEnt; stdcall;
procedure WSASetLastError( const iError: Integer ); stdcall;
function WSAGetLastError: Integer; stdcall;
function WSAIsBlocking: BOOL; stdcall;
function WSAUnhookBlockingHook: Integer; stdcall;
function WSASetBlockingHook( lpBlockFunc: TFarProc ): TFarProc; stdcall;
function WSACancelBlockingCall: Integer; stdcall;
function WSAAsyncGetServByName( HWindow: HWND; wMsg: u_int; name, proto, buf: PChar; buflen: Integer ): THandle; stdcall;
function WSAAsyncGetServByPort( HWindow: HWND; wMsg, port: u_int; proto, buf: PChar; buflen: Integer ): THandle; stdcall;
function WSAAsyncGetProtoByName( HWindow: HWND; wMsg: u_int; name, buf: PChar; buflen: Integer ): THandle; stdcall;
function WSAAsyncGetProtoByNumber( HWindow: HWND; wMsg: u_int; number: Integer; buf: PChar; buflen: Integer ): THandle; stdcall;
function WSAAsyncGetHostByName( HWindow: HWND; wMsg: u_int; name, buf: PChar; buflen: Integer ): THandle; stdcall;
function WSAAsyncGetHostByAddr( HWindow: HWND; wMsg: u_int; addr: PChar; len, struct: Integer; buf: PChar; buflen: Integer ): THandle; stdcall;
function WSACancelAsyncRequest( hAsyncTaskHandle: THandle ): Integer; stdcall;
function WSAAsyncSelect( const s: TSocket; HWindow: HWND; wMsg: u_int; lEvent: Longint ): Integer; stdcall;
function __WSAFDIsSet( const s: TSocket; var FDSet: TFDSet ): Bool; stdcall;
function WSAAccept( const s : TSocket; addr : PSockAddr; addrlen : PInteger; lpfnCondition : LPCONDITIONPROC; const dwCallbackData : DWORD ): TSocket; stdcall;
function WSACloseEvent( const hEvent : WSAEVENT ) : WordBool; stdcall;
function WSAConnect( const s : TSocket; const name : PSockAddr; const namelen : Integer; lpCallerData,lpCalleeData : LPWSABUF; lpSQOS,lpGQOS : LPQOS ) : Integer; stdcall;
function WSACreateEvent : WSAEVENT; stdcall;
function WSADuplicateSocketA( const s : TSocket; const dwProcessId : DWORD; lpProtocolInfo : LPWSAProtocol_InfoA ) : Integer; stdcall;
function WSADuplicateSocketW( const s : TSocket; const dwProcessId : DWORD; lpProtocolInfo : LPWSAProtocol_InfoW ) : Integer; stdcall;
function WSADuplicateSocket( const s : TSocket; const dwProcessId : DWORD; lpProtocolInfo : LPWSAProtocol_Info ) : Integer; stdcall;
function WSAEnumNetworkEvents( const s : TSocket; const hEventObject : WSAEVENT; lpNetworkEvents : LPWSANETWORKEVENTS ) :Integer; stdcall;
function WSAEnumProtocolsA( lpiProtocols : PInteger; lpProtocolBuffer : LPWSAProtocol_InfoA; var lpdwBufferLength : DWORD ) : Integer; stdcall;
function WSAEnumProtocolsW( lpiProtocols : PInteger; lpProtocolBuffer : LPWSAProtocol_InfoW; var lpdwBufferLength : DWORD ) : Integer; stdcall;
function WSAEnumProtocols( lpiProtocols : PInteger; lpProtocolBuffer : LPWSAProtocol_Info; var lpdwBufferLength : DWORD ) : Integer; stdcall;
function WSAEventSelect( const s : TSocket; const hEventObject : WSAEVENT; lNetworkEvents : LongInt ): Integer; stdcall;
function WSAGetOverlappedResult( const s : TSocket; lpOverlapped : LPWSAOVERLAPPED; lpcbTransfer : LPDWORD; fWait : BOOL; var lpdwFlags : DWORD ) : WordBool; stdcall;
function WSAGetQosByName( const s : TSocket; lpQOSName : LPWSABUF; lpQOS : LPQOS ): WordBool; stdcall;
function WSAHtonl( const s : TSocket; hostlong : u_long; var lpnetlong : DWORD ): Integer; stdcall;
function WSAHtons( const s : TSocket; hostshort : u_short; var lpnetshort : WORD ): Integer; stdcall;
function WSAIoctl( const s : TSocket; dwIoControlCode : DWORD; lpvInBuffer : Pointer; cbInBuffer : DWORD; lpvOutBuffer : Pointer; cbOutBuffer : DWORD;
  lpcbBytesReturned : LPDWORD; lpOverlapped : LPWSAOVERLAPPED; lpCompletionRoutine : LPWSAOVERLAPPED_COMPLETION_ROUTINE ) : Integer; stdcall;
function WSAJoinLeaf( const s : TSocket; name : PSockAddr; namelen : Integer; lpCallerData,lpCalleeData : LPWSABUF;
  lpSQOS,lpGQOS : LPQOS; dwFlags : DWORD ) : TSocket; stdcall;
function WSANtohl( const s : TSocket; netlong : u_long; var lphostlong : DWORD ): Integer; stdcall;
function WSANtohs( const s : TSocket; netshort : u_short; var lphostshort : WORD ): Integer; stdcall;
function WSARecv( const s : TSocket; lpBuffers : LPWSABUF; dwBufferCount : DWORD; var lpNumberOfBytesRecvd : DWORD; var lpFlags : DWORD;
  lpOverlapped : LPWSAOVERLAPPED; lpCompletionRoutine : LPWSAOVERLAPPED_COMPLETION_ROUTINE ): Integer; stdcall;
function WSARecvDisconnect( const s : TSocket; lpInboundDisconnectData : LPWSABUF ): Integer; stdcall;
function WSARecvFrom( const s : TSocket; lpBuffers : LPWSABUF; dwBufferCount : DWORD; var lpNumberOfBytesRecvd : DWORD; var lpFlags : DWORD;
  lpFrom : PSockAddr; lpFromlen : PInteger; lpOverlapped : LPWSAOVERLAPPED; lpCompletionRoutine : LPWSAOVERLAPPED_COMPLETION_ROUTINE ): Integer; stdcall;
function WSAResetEvent( hEvent : WSAEVENT ): WordBool; stdcall;
function WSASend( const s : TSocket; lpBuffers : LPWSABUF; dwBufferCount : DWORD; var lpNumberOfBytesSent : DWORD; dwFlags : DWORD;
  lpOverlapped : LPWSAOVERLAPPED; lpCompletionRoutine : LPWSAOVERLAPPED_COMPLETION_ROUTINE ): Integer; stdcall;
function WSASendDisconnect( const s : TSocket; lpOutboundDisconnectData : LPWSABUF ): Integer; stdcall;
function WSASendTo( const s : TSocket; lpBuffers : LPWSABUF; dwBufferCount : DWORD; var lpNumberOfBytesSent : DWORD; dwFlags : DWORD;
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
function WSAStringToAddressW( const AddressString : PWideChar; const AddressFamily: Integer; const lpProtocolInfo : LPWSAProtocol_InfoW;
  var lpAddress : TSockAddr; var lpAddressLength : Integer ): Integer; stdcall;
function WSAStringToAddress( const AddressString : PMBChar; const AddressFamily: Integer; const lpProtocolInfo : LPWSAProtocol_Info;
  var lpAddress : TSockAddr; var lpAddressLength : Integer ): Integer; stdcall;
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
function WSAGetServiceClassNameByClassIdA( const lpServiceClassId: PGUID; lpszServiceClassName: PChar; var lpdwBufferLength: DWORD ): Integer; stdcall;
function WSAGetServiceClassNameByClassIdW( const lpServiceClassId: PGUID; lpszServiceClassName: PWideChar; var lpdwBufferLength: DWORD ): Integer; stdcall;
function WSAGetServiceClassNameByClassId( const lpServiceClassId: PGUID; lpszServiceClassName: PMBChar; var lpdwBufferLength: DWORD ): Integer; stdcall;
function WSASetServiceA( const lpqsRegInfo: LPWSAQuerySetA; const essoperation: TWSAeSetServiceOp; const dwControlFlags: DWORD ): Integer; stdcall;
function WSASetServiceW( const lpqsRegInfo: LPWSAQuerySetW; const essoperation: TWSAeSetServiceOp; const dwControlFlags: DWORD ): Integer; stdcall;
function WSASetService( const lpqsRegInfo: LPWSAQuerySet; const essoperation: TWSAeSetServiceOp; const dwControlFlags: DWORD ): Integer; stdcall;
function WSAProviderConfigChange( var lpNotificationHandle : THandle; lpOverlapped : LPWSAOVERLAPPED; lpCompletionRoutine : LPWSAOVERLAPPED_COMPLETION_ROUTINE ) : Integer; stdcall;

function WSAStartup; external WINSOCK2_DLL name 'WSAStartup';
function WSACleanup; external WINSOCK2_DLL name 'WSACleanup';
function accept; external WINSOCK2_DLL name 'accept';
function bind; external WINSOCK2_DLL name 'bind';
function closesocket; external WINSOCK2_DLL name 'closesocket';
function connect; external WINSOCK2_DLL name 'connect';
function ioctlsocket; external WINSOCK2_DLL name 'ioctlsocket';
function getpeername; external WINSOCK2_DLL name 'getpeername';
function getsockname; external WINSOCK2_DLL name 'getsockname';
function getsockopt; external WINSOCK2_DLL name 'getsockopt';
function htonl; external WINSOCK2_DLL name 'htonl';
function htons; external WINSOCK2_DLL name 'htons';
function inet_addr; external WINSOCK2_DLL name 'inet_addr';
function inet_ntoa; external WINSOCK2_DLL name 'inet_ntoa';
function listen; external WINSOCK2_DLL name 'listen';
function ntohl; external WINSOCK2_DLL name 'ntohl';
function ntohs; external WINSOCK2_DLL name 'ntohs';
function recv; external WINSOCK2_DLL name 'recv';
function recvfrom; external WINSOCK2_DLL name 'recvfrom';
function select; external WINSOCK2_DLL name 'select';
function send; external WINSOCK2_DLL name 'send';
function sendto; external WINSOCK2_DLL name 'sendto';
function setsockopt; external WINSOCK2_DLL name 'setsockopt';
function shutdown; external WINSOCK2_DLL name 'shutdown';
function socket; external WINSOCK2_DLL name 'socket';
function gethostbyaddr; external WINSOCK2_DLL name 'gethostbyaddr';
function gethostbyname; external WINSOCK2_DLL name 'gethostbyname';
function gethostname; external WINSOCK2_DLL name 'gethostname';
function getservbyport; external WINSOCK2_DLL name 'getservbyport';
function getservbyname; external WINSOCK2_DLL name 'getservbyname';
function getprotobynumber; external WINSOCK2_DLL name 'getprotobynumber';
function getprotobyname; external WINSOCK2_DLL name 'getprotobyname';
procedure WSASetLastError; external WINSOCK2_DLL name 'WSASetLastError';
function WSAGetLastError; external WINSOCK2_DLL name 'WSAGetLastError';
function WSAIsBlocking; external WINSOCK2_DLL name 'WSAIsBlocking';
function WSAUnhookBlockingHook; external WINSOCK2_DLL name 'WSAUnhookBlockingHook';
function WSASetBlockingHook; external WINSOCK2_DLL name 'WSASetBlockingHook';
function WSACancelBlockingCall; external WINSOCK2_DLL name 'WSACancelBlockingCall';
function WSAAsyncGetServByName; external WINSOCK2_DLL name 'WSAAsyncGetServByName';
function WSAAsyncGetServByPort; external WINSOCK2_DLL name 'WSAAsyncGetServByPort';
function WSAAsyncGetProtoByName; external WINSOCK2_DLL name 'WSAAsyncGetProtoByName';
function WSAAsyncGetProtoByNumber; external WINSOCK2_DLL name 'WSAAsyncGetProtoByNumber';
function WSAAsyncGetHostByName; external WINSOCK2_DLL name 'WSAAsyncGetHostByName';
function WSAAsyncGetHostByAddr; external WINSOCK2_DLL name 'WSAAsyncGetHostByAddr';
function WSACancelAsyncRequest; external WINSOCK2_DLL name 'WSACancelAsyncRequest';
function WSAAsyncSelect; external WINSOCK2_DLL name 'WSAAsyncSelect';
function __WSAFDIsSet; external WINSOCK2_DLL name '__WSAFDIsSet';
function WSAAccept; external WINSOCK2_DLL name 'WSAAccept';
function WSACloseEvent; external WINSOCK2_DLL name 'WSACloseEvent';
function WSAConnect; external WINSOCK2_DLL name 'WSAConnect';
function WSACreateEvent ; external WINSOCK2_DLL name 'WSACreateEvent ';
function WSADuplicateSocketA; external WINSOCK2_DLL name 'WSADuplicateSocketA';
function WSADuplicateSocketW; external WINSOCK2_DLL name 'WSADuplicateSocketW';
function WSAEnumNetworkEvents; external WINSOCK2_DLL name 'WSAEnumNetworkEvents';
function WSAEnumProtocolsA; external WINSOCK2_DLL name 'WSAEnumProtocolsA';
function WSAEnumProtocolsW; external WINSOCK2_DLL name 'WSAEnumProtocolsW';
function WSAEventSelect; external WINSOCK2_DLL name 'WSAEventSelect';
function WSAGetOverlappedResult; external WINSOCK2_DLL name 'WSAGetOverlappedResult';
function WSAGetQosByName; external WINSOCK2_DLL name 'WSAGetQosByName';
function WSAHtonl; external WINSOCK2_DLL name 'WSAHtonl';
function WSAHtons; external WINSOCK2_DLL name 'WSAHtons';
function WSAIoctl; external WINSOCK2_DLL name 'WSAIoctl';
function WSAJoinLeaf; external WINSOCK2_DLL name 'WSAJoinLeaf';
function WSANtohl; external WINSOCK2_DLL name 'WSANtohl';
function WSANtohs; external WINSOCK2_DLL name 'WSANtohs';
function WSARecv; external WINSOCK2_DLL name 'WSARecv';
function WSARecvDisconnect; external WINSOCK2_DLL name 'WSARecvDisconnect';
function WSARecvFrom; external WINSOCK2_DLL name 'WSARecvFrom';
function WSAResetEvent; external WINSOCK2_DLL name 'WSAResetEvent';
function WSASend; external WINSOCK2_DLL name 'WSASend';
function WSASendDisconnect; external WINSOCK2_DLL name 'WSASendDisconnect';
function WSASendTo; external WINSOCK2_DLL name 'WSASendTo';
function WSASetEvent; external WINSOCK2_DLL name 'WSASetEvent';
function WSASocketA; external WINSOCK2_DLL name 'WSASocketA';
function WSASocketW; external WINSOCK2_DLL name 'WSASocketW';
function WSAWaitForMultipleEvents; external WINSOCK2_DLL name 'WSAWaitForMultipleEvents';
function WSAAddressToStringA; external WINSOCK2_DLL name 'WSAAddressToStringA';
function WSAAddressToStringW; external WINSOCK2_DLL name 'WSAAddressToStringW';
function WSAStringToAddressA; external WINSOCK2_DLL name 'WSAStringToAddressA';
function WSAStringToAddressW; external WINSOCK2_DLL name 'WSAStringToAddressW';
function WSALookupServiceBeginA; external WINSOCK2_DLL name 'WSALookupServiceBeginA';
function WSALookupServiceBeginW; external WINSOCK2_DLL name 'WSALookupServiceBeginW';
function WSALookupServiceNextA; external WINSOCK2_DLL name 'WSALookupServiceNextA';
function WSALookupServiceNextW; external WINSOCK2_DLL name 'WSALookupServiceNextW';
function WSALookupServiceEnd; external WINSOCK2_DLL name 'WSALookupServiceEnd';
function WSAInstallServiceClassA; external WINSOCK2_DLL name 'WSAInstallServiceClassA';
function WSAInstallServiceClassW; external WINSOCK2_DLL name 'WSAInstallServiceClassW';
function WSARemoveServiceClass; external WINSOCK2_DLL name 'WSARemoveServiceClass';
function WSAGetServiceClassInfoA; external WINSOCK2_DLL name 'WSAGetServiceClassInfoA';
function WSAGetServiceClassInfoW; external WINSOCK2_DLL name 'WSAGetServiceClassInfoW';
function WSAEnumNameSpaceProvidersA; external WINSOCK2_DLL name 'WSAEnumNameSpaceProvidersA';
function WSAEnumNameSpaceProvidersW; external WINSOCK2_DLL name 'WSAEnumNameSpaceProvidersW';
function WSAGetServiceClassNameByClassIdA; external WINSOCK2_DLL name 'WSAGetServiceClassNameByClassIdA';
function WSAGetServiceClassNameByClassIdW; external WINSOCK2_DLL name 'WSAGetServiceClassNameByClassIdW';
function WSASetServiceA; external WINSOCK2_DLL name 'WSASetServiceA';
function WSASetServiceW; external WINSOCK2_DLL name 'WSASetServiceW';
function WSAProviderConfigChange; external WINSOCK2_DLL name 'WSAProviderConfigChange';
{$IFDEF UNICODE}
function WSADuplicateSocket; external WINSOCK2_DLL name 'WSADuplicateSocketW';
function WSAEnumProtocols; external WINSOCK2_DLL name 'WSAEnumProtocolsW';
function WSASocket; external WINSOCK2_DLL name 'WSASocketW';
function WSAAddressToString; external WINSOCK2_DLL name 'WSAAddressToStringW';
function WSAStringToAddress; external WINSOCK2_DLL name 'WSAStringToAddressW';
function WSALookupServiceBegin; external WINSOCK2_DLL name 'WSALookupServiceBeginW';
function WSALookupServiceNext; external WINSOCK2_DLL name 'WSALookupServiceNextW';
function WSAInstallServiceClass; external WINSOCK2_DLL name 'WSAInstallServiceClassW';
function WSAGetServiceClassInfo; external WINSOCK2_DLL name 'WSAGetServiceClassInfoW';
function WSAEnumNameSpaceProviders; external WINSOCK2_DLL name 'WSAEnumNameSpaceProvidersW';
function WSAGetServiceClassNameByClassId; external WINSOCK2_DLL name 'WSAGetServiceClassNameByClassIdW';
function WSASetService; external WINSOCK2_DLL name 'WSASetServiceW';
{$ELSE}
function WSADuplicateSocket; external WINSOCK2_DLL name 'WSADuplicateSocketA';
function WSAEnumProtocols; external WINSOCK2_DLL name 'WSAEnumProtocolsA';
function WSASocket; external WINSOCK2_DLL name 'WSASocketA';
function WSAAddressToString; external WINSOCK2_DLL name 'WSAAddressToStringA';
function WSAStringToAddress; external WINSOCK2_DLL name 'WSAStringToAddressA';
function WSALookupServiceBegin; external WINSOCK2_DLL name 'WSALookupServiceBeginA';
function WSALookupServiceNext; external WINSOCK2_DLL name 'WSALookupServiceNextA';
function WSAInstallServiceClass; external WINSOCK2_DLL name 'WSAInstallServiceClassA';
function WSAGetServiceClassInfo; external WINSOCK2_DLL name 'WSAGetServiceClassInfoA';
function WSAEnumNameSpaceProviders; external WINSOCK2_DLL name 'WSAEnumNameSpaceProvidersA';
function WSAGetServiceClassNameByClassId; external WINSOCK2_DLL name 'WSAGetServiceClassNameByClassIdA';
function WSASetService; external WINSOCK2_DLL name 'WSASetServiceA';
{$ENDIF}
        
implementation

begin
end.
