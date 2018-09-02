

#define IP_HDRINCL 2
#define SIO_RCVALL _WSAIOW(IOC_VENDOR,1)

#define ACK 0x10
#define FIN 0x01
#define PSH 0x08
#define RST 0x04
#define SYN 0x02
#define URG 0x20

typedef struct tcphdr
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

typedef struct iphdr
{
	unsigned char h_verlen;
	unsigned char tos;
	unsigned short total_len;
	unsigned short ident;
	unsigned short frag_and_flags;
	unsigned char  ttl;
	unsigned char proto;
	unsigned short checksum;
	unsigned int sourceIP;
	unsigned int destIP;
} IPHEADER;

typedef struct psdhdr
{
	unsigned long saddr;
	unsigned long daddr;
	char mbz;
	char ptcl;
	unsigned short tcpl;
} PSDHEADER; 

typedef struct udphdr
{
	unsigned short source;
	unsigned short dest;
    unsigned short length;
    unsigned short checksum;
} UDPHEADER;
        
typedef struct icmphdr
{
	unsigned char  type;
    unsigned char  subcode;
    unsigned short checksum;
	unsigned short id;
	unsigned short seq;

} ICMPHEADER;