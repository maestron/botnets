/*  ya.bot  */

#define IP_HDRINCL 2
#define SIO_RCVALL _WSAIOW(IOC_VENDOR,1)

#define ACK 0x10
#define FIN 0x01
#define PSH 0x08
#define RST 0x04
#define SYN 0x02
#define URG 0x20

typedef struct ICMPHEADER
{
	unsigned char type;
	unsigned char subcode;
	unsigned short checksum;
	unsigned short id;
	unsigned short seq;
} ICMPHEADER;

typedef struct IPHEADER
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

typedef struct PSDHEADER
{
	unsigned int saddr;
	unsigned int daddr;
	unsigned char mbz;
	unsigned char ptcl;
	unsigned short tcpl;
} PSDHEADER; 

typedef struct TCPHEADER
{
	unsigned short th_sport;
	unsigned short th_dport;
	unsigned int th_seq;
	unsigned int th_ack;
	unsigned char th_lenres;
	unsigned char th_flags;
	unsigned short th_win;
	unsigned short th_sum;
	unsigned short th_urp;
} TCPHEADER;

typedef struct UDPHEADER
{
	unsigned short source;
	unsigned short dest;
	unsigned short length;
	unsigned short checksum;
} UDPHEADER;