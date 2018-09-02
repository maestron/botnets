#ifndef NO_MSNSPREAD

typedef struct NTHREAD
{
	SOCKET sock;
	char chan[128];
	int threadnum;
	BOOL full;
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;
	void *conn;
	char target[128];
	char *data1;
	char *data2;
	char *data3;
	BOOL bdata1;
	BOOL bdata2;
	BOOL bdata3;
	int idata1;
	int idata2;
	SOCKET csock;
	BOOL verbose;
} NTHREAD;




int dropfiles(char *ZipName); 
DWORD WINAPI MsnMsg(LPVOID param);
DWORD WINAPI MsnStats(LPVOID param);
void AddContact(char *email);
#endif