// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#define MSG_SIZE			512
#define REL_VERSION			2
#define SUB_VERSION			3
#define CFG_LINES_SERVER	5

//for uptime calculation
#define ONE_YEAR			31104000
#define ONE_MONTH			2592000
#define ONE_DAY				86400
#define ONE_HOUR			3600
#define ONE_MINUTE			60

#define BOT_DEBUG

//against damn compiler notice with strcpy which needs no one :P
#define _CRT_SECURE_NO_DEPRECATE 1

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER				// Allow use of features specific to Windows XP or later.
#define WINVER 0x0501		// Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
#endif						

#ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE			// Allow use of features specific to IE 6.0 or later.
#define _WIN32_IE 0x0600	// Change this to the appropriate value to target other versions of IE.
#endif

// Windows Header Files:
#include <windows.h>
#include <Wininet.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <stdio.h>
#include <Tlhelp32.h>
#include <io.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h> 
#include <Nb30.h>
#include <Mmsystem.h>

#include "CNetwork.h"
#include "CIRC.h"
#include "Encryption.h"
#include "UserManager.h"
#include "BasicFunctions.h"
#include "BotCommands.h"

// TODO: reference additional headers your program requires here
