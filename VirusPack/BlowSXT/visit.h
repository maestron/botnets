#ifndef NO_VISIT
// visit structure
typedef struct vs {
	 char host[128];
	 char referer[128];
	 char chan[128];
	 int threadnum;
	 SOCKET sock;
	 BOOL silent;
	 BOOL notice;
	 BOOL gotinfo;
} vs;

DWORD WINAPI visit(LPVOID param);
#endif
