/*
		Aspergillus V1.3 by D
		Copyright (c) 2007
*/

#ifndef NO_PATCHER

typedef struct PATCHER {
	SOCKET	Sock;
	int		tnum;
} PATCHER;

DWORD WINAPI PatcherThread(LPVOID param);

#endif