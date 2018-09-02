
#ifndef NO_KILLP

#include <vector>
#include <windows.h>

void GetProcessID(LPCTSTR pProcessName, std::vector<DWORD>& SetOfPID);
int ifproc();

#endif