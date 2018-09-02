/*  ya.bot  */

#ifndef NO_HTTP
DWORD WINAPI http_download(LPVOID param);
DWORD WINAPI http_update(LPVOID param);
bool http_visit(char *pszUrl);

typedef struct SHTTPDownload
{
	char m_szUrl[MEDBUF];
	char m_szFilePath[MAX_PATH];
	bool m_bRun;
	SOCKET m_bsock;
	WSAEVENT m_wsaEvent;
	char m_szAction[LOWBUF];
	char m_szDestination[LOWBUF];
	bool m_bSilent;
	bool m_bVerbose;
} SHTTPDownload;
#endif