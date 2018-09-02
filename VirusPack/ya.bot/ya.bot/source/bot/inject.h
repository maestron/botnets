/*  ya.bot  */

bool inject_freeremotelibrary(DWORD dwPID, DWORD dwBaseAddress);
bool inject_loadremotelibrary(DWORD dwPID, char *pszLibraryPath);
DWORD inject_processesloadall(char *pszFilePath);
DWORD inject_processesunloadall(DWORD dwBaseAddress);