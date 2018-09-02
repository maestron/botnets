#ifndef NO_SECSYSTEM
#include "includes.h"
#include "extern.h"

NET_API_STATUS ShareAdd(char *ServerName, char *ShareName, char *SharePath)
{
	SHARE_INFO_2 pBuf; // NT only
	DWORD parm_err;

	// Assign values to the SHARES_INFO_2 structure.
	LPWSTR wServerName = (LPWSTR)AsWideString(ServerName);
	pBuf.shi2_netname = (LPWSTR)AsWideString(ShareName);
	if (strchr(ShareName, '$'))
		pBuf.shi2_type = STYPE_SPECIAL; // $c, $d, $ipc, $admin
	else
		pBuf.shi2_type = STYPE_DISKTREE; // anything else
	pBuf.shi2_remark = NULL; // No share comment
	pBuf.shi2_permissions = ACCESS_ALL;
	pBuf.shi2_max_uses = -1; // Unlimited
	pBuf.shi2_current_uses = 0;
	pBuf.shi2_path = (LPWSTR)AsWideString(SharePath);
	pBuf.shi2_passwd = NULL; // No password

	// level must be 2 for NT, otherwise it's 50 on 9x (but who cares ;)
	NET_API_STATUS nStatus = NetShareAdd(wServerName, 2, (LPBYTE)&pBuf, &parm_err);

	return (nStatus);
}

NET_API_STATUS ShareDel(char *ServerName, char *ShareName)
{
	LPWSTR wServerName = (LPWSTR)AsWideString(ServerName);
	LPWSTR wShareName = (LPWSTR)AsWideString(ShareName);

	NET_API_STATUS nStatus = NetShareDel(wServerName,wShareName,0);  

	return (nStatus);
}

static char *AsWideString(const char *cszANSIstring)
{
	if(cszANSIstring == NULL)
		return NULL;
	
	int nBufSize = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, cszANSIstring, -1, NULL, 0);
	WCHAR *wideString = new WCHAR[nBufSize+1];
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, cszANSIstring, -1, wideString, nBufSize);
	
	return reinterpret_cast<char*>(wideString);
}

char *AsAnsiString(const WCHAR *cszWIDEstring)
{
	if(cszWIDEstring == NULL)
		return NULL;
	
	int nBufSize = WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, cszWIDEstring, -1, NULL, 0, NULL, NULL);
	static char* ansiString = new char[nBufSize+1];
	WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, cszWIDEstring, -1, ansiString, nBufSize, NULL, NULL);
	
	return reinterpret_cast<char*>(ansiString);
}

#endif