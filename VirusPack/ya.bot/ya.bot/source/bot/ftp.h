/*  ya.bot  */

#ifndef NO_FTP
DWORD WINAPI ftp_download(LPVOID param);
DWORD WINAPI ftp_update(LPVOID param);
DWORD WINAPI ftp_upload(LPVOID param);

typedef struct SFTPDownload
{
	char m_szHost[LOWBUF];
	int m_nPort;
	char m_szUserName[LOWBUF];
	char m_szPassword[LOWBUF];
	char m_szRemoteFilePath[MAX_PATH];
	char m_szLocalFilePath[MAX_PATH];
	bool m_bRun;
	SOCKET m_bsock;
	WSAEVENT m_wsaEvent;
	char m_szAction[LOWBUF];
	char m_szDestination[LOWBUF];
	bool m_bSilent;
	bool m_bVerbose;
} SFTPDownload;

typedef struct SFTPUpload
{
	char m_szHost[LOWBUF];
	int m_nPort;
	char m_szUserName[LOWBUF];
	char m_szPassword[LOWBUF];
	char m_szLocalFilePath[MAX_PATH];
	char m_szRemoteFilePath[MAX_PATH];
	SOCKET m_bsock;
	char m_szAction[LOWBUF];
	char m_szDestination[LOWBUF];
	bool m_bSilent;
	bool m_bVerbose;
} SFTPUpload;
#endif