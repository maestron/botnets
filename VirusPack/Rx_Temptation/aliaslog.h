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
	bool notice;
	bool silent;
	bool gotinfo;

} SHOWLOG;

int addalias(char *name, char *command);
void aliaslist(SOCKET sock, char *chan, bool notice);
void addlog(char *desc);
void addlogv(char *desc, ...);
void showlog(SOCKET sock, char *chan, bool notice, bool silent, char *filter);
void clearlog(SOCKET sock, char *chan, bool notice, bool silent);
bool searchlog(char *filter);
DWORD WINAPI ShowLogThread(LPVOID param);
#ifdef DEBUG_LOGGING
void opendebuglog(void);
void debuglog(char *buffer,bool crlf=true);
void closedebuglog(void);
#endif
#ifdef DEBUG_CONSOLE
bool WINAPI HandlerRoutine(DWORD dwCtrlType);
void OpenConsole(void);
#endif