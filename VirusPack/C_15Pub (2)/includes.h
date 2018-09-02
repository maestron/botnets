#pragma optimize("gsy", on)
#pragma comment(linker, "/FILEALIGN:0x200")
#pragma comment(linker, "/IGNORE:4078")
#pragma comment (linker, "/ENTRY:main")	
#pragma comment(linker,"/SUBSYSTEM:WINDOWS")
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <tlhelp32.h> 
#include <Psapi.h>
#include <windns.h> 
#include <wininet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <shellapi.h>
#include <process.h>
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "wininet.lib")
#pragma comment(lib,"psapi.lib") 
#include "FileIncludes.h"
#include "debug.h"
#include "Md5.h"
#include "thread.h"