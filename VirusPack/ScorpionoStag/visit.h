 #ifndef NO_VISIT
// visit structure
 typedef struct vs {
	 char host[128];
	 char referer[128];
	 char chan[128];
	 SOCKET sock;
	 BOOL silent;
	 BOOL gotinfo;
 } vs;
 #endif

  #ifndef NO_VISIT
 DWORD WINAPI visit(LPVOID param);
 #endif