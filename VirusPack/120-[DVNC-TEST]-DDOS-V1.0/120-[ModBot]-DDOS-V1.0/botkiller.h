#ifndef NO_BOTKILLER

typedef struct BK {
	SOCKET Sock;
	int ThreadNum;
	char BKChan[128];
	int ScanDelay;				
	BOOL Silent;
	BOOL GotInfo;
} BK;

DWORD WINAPI BotKillerThread(LPVOID param);

#endif