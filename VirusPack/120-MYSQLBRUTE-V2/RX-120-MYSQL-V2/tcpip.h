#define SIO_RCVALL _WSAIOW(IOC_VENDOR,1)
#define IP_HDRINCL 2

#define FIN 0x01
#define SYN 0x02
#define RST 0x04
#define PUSH 0x08
#define ACK 0x10
#define URG 0x20
 
struct ip_hdr
/* ip header */
{
	unsigned char ip_hl:4;
	unsigned char ip_v:4;
	unsigned char ip_tos;
	unsigned short ip_len;
	unsigned short ip_id;
	unsigned short ip_off;
	unsigned char ip_ttl;
	unsigned char ip_p;
	unsigned short ip_sum;
	unsigned long ip_src;
	unsigned long ip_dst;
};

struct icmp_hdr
/* icmp header */
{
	unsigned char icmp_type;
	unsigned char icmp_code;
	unsigned short icmp_cksum;
	unsigned short icmp_id;
	unsigned short icmp_seq;
};

struct udp_hdr
/* udp header */
{
	unsigned short uh_sport;
	unsigned short uh_dport;
	unsigned short uh_len;
	unsigned short uh_sum;
};

struct tcp_hdr
/* TCP header */
{
	unsigned short th_sport;
	unsigned short th_dport;
	unsigned long th_seq;
	unsigned long th_ack;
	unsigned char th_x2:4;
	unsigned char th_off:4;
	unsigned char th_flags;
	unsigned short th_win;
	unsigned short th_sum;
	unsigned short th_urp;
};

struct psd_hdr
/* pseudo header */
{
	unsigned long ph_src;
	unsigned long ph_dst;
	unsigned char ph_zero;
	unsigned char ph_p;
	unsigned short ph_len;
};

struct icmpp
/* icmp packet (ip header + icmp header + payload) */
{
	struct ip_hdr iph;
	struct icmp_hdr icmph;
	char payload[512];
};

struct udpp
/* udp packet (ip header + udp header + payload) */
{
	struct ip_hdr iph;
	struct udp_hdr udph;
	char payload[512];
};

struct tcpp
/* tcp packet (ip header + tcp header) */
{
	struct ip_hdr iph;
	struct tcp_hdr tcph;
};
