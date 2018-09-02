#include "includes.h"

BOOL registry_WriteString(HKEY hKey, char *pszSubKey, char *pszValueName, char *pszValue) {
    HKEY rk;
    char szValue[256];
	
    strncpy(szValue, pszValue, sizeof(szValue) - 1);
    if (RegCreateKeyEx(hKey, pszSubKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &rk, NULL) != ERROR_SUCCESS)
		return FALSE;
    if (RegSetValueEx(rk, pszValueName, 0, REG_SZ, (LPBYTE)szValue, strlen(szValue) + 1) != ERROR_SUCCESS)
		return FALSE;
    RegCloseKey(rk);
    return TRUE;
}


BOOL registry_AddCommonStartup(char *pszKeyName, char *pszCmdLine) {
	BOOL bError;
	
	bError = registry_WriteString(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", pszKeyName, pszCmdLine);
	return bError;
}