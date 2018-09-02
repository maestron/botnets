

#ifndef NO_REGISTRY
bool regwritedword(HKEY hKey, char *szPath, char *szKey, DWORD dwValue);
bool regdeletekey(HKEY hKey, char *szPath, char *szKey);
bool regwritekey(HKEY hKey, char *szPath, char *szKey, char *szValue);
#endif