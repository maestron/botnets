//================================================================
//	Copyright (c) JIURL, All Rights Reserved
//================================================================

// jiurl // IPSNMPInfo structure is defined from RFC 2011 
// jiurl // so I defined TCPSNMPInfo structure from RFC 2022 £¬as IPSNMPInfo. 
// jiurl // some more analysis to get some extended definiens.

typedef struct TCPSNMPInfo {
    ULONG       tcpsi_RtoAlgorithm;
    ULONG       tcpsi_RtoMin;
    ULONG       tcpsi_RtoMax;
    ULONG       tcpsi_MaxConn;
    ULONG       tcpsi_ActiveOpens;
    ULONG       tcpsi_PassiveOpens;
    ULONG       tcpsi_AttemptFails;
    ULONG       tcpsi_EstabResets;
    ULONG       tcpsi_CurrEstab;
    ULONG       tcpsi_InSegs;
    ULONG       tcpsi_OutSegs;
    ULONG       tcpsi_RetransSegs;
	ULONG       tcpsi_unknown1;
	ULONG       tcpsi_unknown2;
	ULONG       tcpsi_numconn;
} TCPSNMPInfo;

#define tcpRtoAlgorithm_other    1 // none of the following
#define tcpRtoAlgorithm_constant 2 // a constant rto
#define tcpRtoAlgorithm_rsre     3 // MIL-STD-1778, Appendix B
#define tcpRtoAlgorithm_vanj     4 // Van Jacobson's algorithm

#define TCP_MIB_STATS_ID              1
#define TCP_MIB_ADDRTABLE_ENTRY_ID    0x101
#define TCP_MIB_ADDRTABLE_ENTRY_EX_ID 0x102


typedef struct TCPAddrEntry {
    ULONG       tae_ConnState;
    ULONG       tae_ConnLocalAddress;
    ULONG       tae_ConnLocalPort;
    ULONG       tae_ConnRemAddress;
    ULONG       tae_ConnRemPort;
} TCPAddrEntry;

#define tcpConnState_closed      1
#define tcpConnState_listen      2
#define tcpConnState_synSent     3
#define tcpConnState_synReceived 4
#define tcpConnState_established 5
#define tcpConnState_finWait1    6
#define tcpConnState_finWait2    7
#define tcpConnState_closeWait   8
#define tcpConnState_lastAck     9
#define tcpConnState_closing     10
#define tcpConnState_timeWait    11
#define tcpConnState_deleteTCB   12

typedef struct TCPAddrExEntry {
    ULONG       tae_ConnState;
    ULONG       tae_ConnLocalAddress;
    ULONG       tae_ConnLocalPort;
    ULONG       tae_ConnRemAddress;
    ULONG       tae_ConnRemPort;
    ULONG       pid;
} TCPAddrExEntry;

