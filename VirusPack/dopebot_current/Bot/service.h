

#ifndef NO_SERVICE
bool install_service(char *szServiceName, char *szServicePath, DWORD dwServiceType, DWORD dwServiceStartup, bool bStartService);
bool uninstall_service(char *szServiceName);
#endif