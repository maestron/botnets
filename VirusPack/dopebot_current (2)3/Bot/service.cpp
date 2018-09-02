

#ifndef NO_SERVICE
#include "bt1.h"

//Install Service
bool install_service(char *szServiceName, char *szServicePath, DWORD dwServiceType, DWORD dwServiceStartup, bool bStartService)
{
	SC_HANDLE hManager, hService;

#ifndef NO_DEBUG
		printf("[DEBUG] Installing service, install_service()...\n");
#endif
		
		hManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
		hService = CreateService(hManager, szServiceName, szServiceName, SERVICE_ALL_ACCESS, dwServiceType, dwServiceStartup, SERVICE_ERROR_NORMAL, szServicePath, NULL, NULL, NULL,  NULL, NULL);
	if (hService == NULL)
	{
			CloseServiceHandle(hService);
			CloseServiceHandle(hManager);
			return FALSE;
	}
	if (bStartService)
	{
			hService = OpenService(hManager, szServiceName, SERVICE_ALL_ACCESS);
		if (hService == NULL) return FALSE;
			StartService(hService, 0, NULL);
			CloseServiceHandle(hService);
			CloseServiceHandle(hManager);
	}
		return TRUE;
}

//Uninstall Service
bool uninstall_service(char *szServiceName)
{
	SC_HANDLE hManager, hService;
	SERVICE_STATUS serviceStatus;

#ifndef NO_DEBUG
		printf("[DEBUG] Uninstalling service, uninstall_service()...\n");
#endif

		hManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
		hService = OpenService(hManager, szServiceName, SERVICE_ALL_ACCESS);
	if (hService == NULL)
	{
			CloseServiceHandle(hService);
			CloseServiceHandle(hManager);
			return FALSE;
	}
		ControlService(hService, SERVICE_CONTROL_STOP, &serviceStatus);
	if (hService == NULL) return FALSE;
		DeleteService(hService);
		CloseServiceHandle(hService);
		CloseServiceHandle(hManager);
		return TRUE;
}
#endif;