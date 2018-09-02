/////////////////////////////////////////
///                                   ///
///  TsGh By TsGh Sniper              ///
///                                   ///
/////////////////////////////////////////


#ifndef NO_DOWNLOAD
// download/update structure
typedef struct DOWNLOAD 
{
	SOCKET sock;
	char chan[MAXCHANLEN];
	char url[MAXURLLEN];
	char dest[MAX_PATH];
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
