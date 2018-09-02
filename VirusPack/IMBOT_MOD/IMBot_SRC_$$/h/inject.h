#define MakePtr( cast, ptr, addValue ) (cast)( (DWORD)(ptr) + (addValue) )

BOOL Inject(DWORD dwPid, LPTHREAD_START_ROUTINE lpStartProc, LPVOID lpParam);
BOOL PerformRebase(LPVOID lpAddress, DWORD dwNewBase);
void WINAPI Guard(LPVOID lpParam);
DWORD GetPID(char pname[]);
int Check(char pname[]);