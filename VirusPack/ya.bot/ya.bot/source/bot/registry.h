/*  ya.bot  */

bool registry_createkey(HKEY hKey, char *pszSubKey, char *pszKey);
bool registry_deletekey(HKEY hKey, char *pszSubKey, char *pszKey);
bool registry_deletevalue(HKEY hKey, char *pszSubKey, char *pszValueName);
bool registry_readvalue(HKEY hKey, char *pszSubKey, char *pszValueName, void *pBuffer, DWORD dwSize);
bool registry_writedword(HKEY hKey, char *pszSubKey, char *pszValueName, DWORD dwValue);
bool registry_writestring(HKEY hKey, char *pszSubKey, char *pszValueName, char *pszValue);