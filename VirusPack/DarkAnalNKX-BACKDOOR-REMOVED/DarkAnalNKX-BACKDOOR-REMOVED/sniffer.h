#ifndef NO_SNIFFER
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
DWORD WINAPI CSniffer(LPVOID param);
#endif