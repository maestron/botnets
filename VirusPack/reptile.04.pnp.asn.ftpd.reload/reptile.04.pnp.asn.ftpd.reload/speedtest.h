#ifndef NO_SPEEDTEST
typedef struct STSERVERS {
	char host[MAX_HOSTNAME];
	BOOL download;
	char path[MAX_PATH];
	int mb;
} STSERVERS;

DWORD WINAPI SpeedTestThread(LPVOID param);

int testftp(void *conn, char *target, BOOL silent, BOOL verbose, char *host, char *folder, int option);
void statistics(float speed, int option);
void ResetSpeedtestStats(BOOL ul, BOOL dl);
#endif