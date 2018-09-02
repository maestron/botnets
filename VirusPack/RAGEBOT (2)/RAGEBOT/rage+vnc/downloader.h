typedef struct DOWNLOAD {
	SOCKET Sock;
	char Url[256];
	char Destination[MAX_PATH];
	char CurrentChannel[256];
	int ThreadNum;
	BOOL Text;
	int Run;
	BOOL Silent;
	BOOL GotInfo;
}DOWNLOAD;

DWORD WINAPI DownloadThread(LPVOID param);