#define SOCKS_VERSION 0x05
#define SOCKS_SUCCESS 0x00
#define SOCKS_FAILURE 0x01
#define SOCKS_CONNECTION_REFUSED 0x05
#define SOCKS_CMD_NOT_SUPPORTED 0x07
#define SOCKS5_METHOD 0x02

#define BUFF_SIZE 1024

typedef UINT in_addr_t;

typedef struct
{

  char* _ConnectStruct;
  SOCKET From;
  SOCKET To;
  char Buff[BUFF_SIZE];
  char* Error;

} SOCKSPIPE;

typedef SOCKSPIPE* LPSOCKSPIPE;

typedef struct _CONNECTSTRUCT
{

  SOCKSPIPE FromStruct;
  SOCKSPIPE ToStruct;
  char Error;

} CONNECTSTRUCT;

typedef CONNECTSTRUCT* LPCONNECTSTRUCT;

/*unsigned int socks5port;
char socks5username[32];
char socks5password[32];*/

typedef struct {
	unsigned int port;
	char username[32];
	char password[32];
	int threadnum;
	int cthreadnum;
	BOOL gotinfo;
	BOOL cgotinfo;
	SOCKET sock;
} socks5;
//unsigned int port, char *user, char *pass

//void Socks5(socks5 s5, DWORD ThreadID);
DWORD WINAPI StartSock5(LPVOID param);
void create_thread(void* func, void* param);
char* _malloc(int BuffSize);
void bzero(void* lpBuff, int BuffSize);
LPCONNECTSTRUCT CreateConnectStruct(SOCKET From, SOCKET To);
bool swrite(SOCKET s, char* Buff, int buff_size);
bool sread(SOCKET s, char* Buff, int buff_size);
__stdcall SocksPipe(LPSOCKSPIPE PipeStruct);
bool Socks5SendCode(SOCKET s, char Code, char* TempBuff, char* ip, char* port);
SOCKET Socks5ServConnect(SOCKET s, char* TempBuff, char* ip, u_short port);
bool Socks5CmdIsSupported(SOCKET s, char cmd, char* TempBuff, char* ip, char* port);
bool Socks5GetCmd(SOCKET s, char* TempBuff, char* cmd, char* ip, char* port);
bool Socks5Auth(SOCKET s, char* TempBuff);
bool Socks5Accept(SOCKET s, char* TempBuff);
//__stdcall AcceptThread(SOCKET s);
DWORD WINAPI AcceptThread(LPVOID param);