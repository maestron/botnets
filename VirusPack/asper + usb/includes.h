#define _WIN32_WINNT	0x0403				// Very important for critical sections.
#define WIN32_LEAN_AND_MEAN					// Good to use.
#pragma optimize("gsy", on)					// Global optimization, Short sequences, Frame pointers.
#pragma comment(linker, "/RELEASE")			// Release code
#pragma comment(linker, "/opt:nowin98")
#pragma comment(linker, "/ALIGN:4096")		// This will save you some size on the executable.
#pragma comment(linker, "/IGNORE:4108 ")	// This is only here for when you use /ALIGN:4096.

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include <time.h>
#include <stdlib.h>
#include <Winsvc.h>
#include <winable.h> 
#include <tlhelp32.h>
#include <tchar.h>
#include <shlobj.h>
#include <shlwapi.h>

#pragma comment(lib, "Ws2_32.lib") 
#pragma comment(lib, "shlwapi.lib")

#include "shared.h"
#include "usb.h"

