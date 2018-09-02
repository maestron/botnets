/*
antisandbox.h
-> antisandbox prototyping
*/

#ifndef _mAntisandbox_h_
#define _mAntiSandbox_h_
#ifndef NO_ANTISANDBOX


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
BOOL AntiSandBox();

#endif
#endif