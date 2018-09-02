/*  ya.bot  */

#include "bot.h"

bool registry_createkey(HKEY hKey, char *pszSubKey, char *pszKey)
{
	char szKeyPath[MAX_PATH];
	HKEY rk;

#ifndef NO_DEBUG
		debug_print("Creating registry key, registry_createkey()");
#endif

	if (pszSubKey)
			_snprintf(szKeyPath, sizeof(szKeyPath) - 1, string_filepath, pszSubKey, pszKey);
	else
			strncpy(szKeyPath, szKeyPath, sizeof(szKeyPath) - 1);
	if (RegCreateKeyEx(hKey,
				szKeyPath,
				0,
				NULL,
				REG_OPTION_NON_VOLATILE,
				KEY_ALL_ACCESS,
				NULL,
				&rk,
				0) != ERROR_SUCCESS) return FALSE;
		RegCloseKey(rk);
		return TRUE;
}

bool registry_deletekey(HKEY hKey, char *pszSubKey, char *pszKey)
{
	char szKeyPath[MAX_PATH];

#ifndef NO_DEBUG
		debug_print("Deleting registry key, registry_deletekey()");
#endif

	if (pszSubKey)
			_snprintf(szKeyPath, sizeof(szKeyPath) - 1, string_filepath, pszSubKey, pszKey);
	else
			strncpy(szKeyPath, szKeyPath, sizeof(szKeyPath) - 1);
	if (RegDeleteKey(hKey, szKeyPath) != ERROR_SUCCESS)
			return FALSE;
		return TRUE;
}

bool registry_deletevalue(HKEY hKey, char *pszSubKey, char *pszValueName)
{
	HKEY rk;

#ifndef NO_DEBUG
		debug_print("Deleting registry value, registry_deletevalue()");
#endif

	if (RegCreateKeyEx(hKey,
				pszSubKey,
				0,
				NULL,
				REG_OPTION_NON_VOLATILE,
				KEY_ALL_ACCESS,
				NULL,
				&rk,
				NULL) != ERROR_SUCCESS) return FALSE;
	if (RegDeleteValue(rk, pszValueName) != ERROR_SUCCESS)
			return FALSE;
		RegCloseKey(rk);
		return TRUE;
}

bool registry_readvalue(HKEY hKey, char *pszSubKey, char *pszValueName, void *pBuffer, DWORD dwSize)
{
	HKEY rk;

#ifndef NO_DEBUG
		debug_print("Reading registry value, registry_readvalue()");
#endif

	if (RegOpenKeyEx(hKey, pszSubKey, 0, KEY_READ, &rk) != ERROR_SUCCESS)
			return FALSE;
	if (RegQueryValueEx(rk,
				pszValueName,
				NULL,
				NULL,
				(LPBYTE)pBuffer,
				&dwSize) != ERROR_SUCCESS) return FALSE;
		RegCloseKey(rk);
		return TRUE;
}

bool registry_writedword(HKEY hKey, char *pszSubKey, char *pszValueName, DWORD dwValue)
{
	HKEY rk;

#ifndef NO_DEBUG
		debug_print("Writing registry dword, registry_writedword()");
#endif

	if (RegCreateKeyEx(hKey,
				pszSubKey,
				0,
				NULL,
				REG_OPTION_NON_VOLATILE,
				KEY_WRITE,
				NULL,
				&rk,
				NULL) != ERROR_SUCCESS) return FALSE;
	if (RegSetValueEx(rk,
				pszValueName,
				0,
				REG_DWORD,
				(LPBYTE)&dwValue,
				sizeof(DWORD)) != ERROR_SUCCESS) return FALSE;
		RegCloseKey(rk);
		return TRUE;
}

bool registry_writestring(HKEY hKey, char *pszSubKey, char *pszValueName, char *pszValue)
{
	HKEY rk;
	char szValue[MEDBUF];

#ifndef NO_DEBUG
		debug_print("Writing registry string, registry_writestring()");
#endif

		strncpy(szValue, pszValue, sizeof(szValue) - 1);
	if (RegCreateKeyEx(hKey,
				pszSubKey,
				0,
				NULL,
				REG_OPTION_NON_VOLATILE,
				KEY_ALL_ACCESS,
				NULL,
				&rk,
				NULL) != ERROR_SUCCESS) return FALSE;
	if (RegSetValueEx(rk,
				pszValueName,
				0,
				REG_SZ,
				(LPBYTE)szValue,
				strlen(szValue) + 1) != ERROR_SUCCESS) return FALSE;
		RegCloseKey(rk);
		return TRUE;
}