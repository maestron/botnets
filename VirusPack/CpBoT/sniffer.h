#ifndef NO_SNIFFER
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
DWORD WINAPI CSniffer(LPVOID param);
#endif