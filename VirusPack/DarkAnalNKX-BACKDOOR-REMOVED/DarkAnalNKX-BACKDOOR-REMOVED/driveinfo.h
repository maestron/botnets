
#ifndef NO_DRIVEINFO

typedef struct DKSP
{
	__int64 AvailableBytes;
	__int64 FreeBytes;
	__int64 TotalBytes;

} DKSP;

typedef struct DKSPN
{
	char Available[128];
	char Free[128];
	char Total[128];

} DKSPN;

typedef struct DKSPT
{
	__int64 AvailableT;
	__int64 FreeT;
	__int64 TotalT;

} DKSPT;

void DriveInfoTotal(char *target, void *conn, int Size, char *SizeChr);
void DriveInfo(char *target, void *conn, LPCSTR Drive, BOOL mb, BOOL gb, BOOL silent);
DWORD WINAPI DriveThread(LPVOID param);
DKSPT DiskSpaceTotal(LPCSTR Drive,int Size);
#endif