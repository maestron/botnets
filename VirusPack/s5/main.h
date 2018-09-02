#ifndef __MAIN_H__
#define __MAIN_H__

//Platform specific includes

#pragma comment(lib,"psapi.lib")
#include <winsock2.h>
#include <windows.h>
#include <process.h>
#include <shlobj.h>
#include <direct.h>
#include <lm.h>
#include <wininet.h>
#include <psapi.h>
#include <ras.h>
#include <winsvc.h>
#include <malloc.h>
#include <windns.h>
#ifdef _DEBUG
	#include <crtdbg.h>
#endif // _DEBUG



// Standard includes

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <signal.h>
#include <ctype.h>
#include <time.h>
#include <bitset>
#include <list>
#include <vector>
#include <pthread.h>

#define USE_SOCKETS

#ifndef AGOBOT_NO_OPENSSL
	#include <openssl/ssl.h>
	#include <openssl/rsa.h>
	#include <openssl/md5.h>
	#include <openssl/evp.h>
#endif

#include "md5/global.h"
#include "md5/md5.h"

// Platform specific defines

#pragma warning(disable:4101)
#define SYS_PLATFORM "Win32"
#define DIRCHAR '\\'
#define DIRSTR "\\"
#define xRead(x,y,z) recv(x,y,z,0)
#define xWrite(x,y,z) send(x,y,z,0)
#define xClose closesocket
#define socklen_t int
#define vsnprintf _vsnprintf
#define sprintf wsprintf
#define safe_strncpy lstrcpyn

// Standard defines

#ifdef _DEBUG
#define SYS_BUILD "Debug"
#else
#define SYS_BUILD ""
#endif

#ifndef min
#define min(x,y) ((x)<(y)?(x):(y))
#define max(x,y) ((y)<(x)?(x):(y))
#endif

#if defined (__GNU_LIBRARY__) || defined (__linux__)
#define SOCKLEN unsigned int
#else
#define SOCKLEN int
#endif

#ifndef INADDR_NONE
#define INADDR_NONE (unsigned long)0xFFFFFFFF
#endif

#ifndef INADDR_ANY
#define INADDR_ANY (unsigned long)0x00000000
#endif

#ifndef INADDR_LOOPBACK
#define INADDR_LOOPBACK (unsigned long)0x7F000001
#endif

#ifndef INVALID_SOCKET
#define INVALID_SOCKET (int)(~0)
#endif

#ifndef SOCKET_ERROR
#define SOCKET_ERROR (-1)
#endif

#define ERRNO (WSAGetLastError())
#define SET_SOCK_BLOCK(s,block) { unsigned long __i=block?0:1; ioctlsocket(s,FIONBIO,&__i); }
#define EWOULDBLOCK WSAEWOULDBLOCK
#define EINPROGRESS WSAEWOULDBLOCK

#ifndef SHUT_RDWR
#define SHUT_RDWR 2
#endif

//#define VERSION_FORBOT	"3.3"

#endif // __MAIN_H__
