typedef struct ALIAS 
{
	 char name[30];
	 char command[MAXCMDLEN];

} ALIAS;

typedef struct SHOWLOG
{
	SOCKET sock;
	char chan[MAXCHANLEN];
	char filter[LOGLINE];
	int threadnum;
	BOOL checkcase;
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
BOOL searchlog(char *filter, BOOL checkcase=FALSE);
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