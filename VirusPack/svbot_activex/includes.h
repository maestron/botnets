#define _CRT_SECURE_NO_DEPRECATE
#define WIN32_LEAN_AND_MEAN

#include < winsock2.h >
#include < windows.h >
#include < stdio.h >
#include < stdlib.h >
#include < shellapi.h >

#pragma comment( lib, "ws2_32" )
//#pragma comment( lib, "shell32" )

//#define DBG_LOG
#define CRYPTO

#include "crypto.h"
#include "loaddlls.h"
#include "main.h"
#include "util.h"
#include "irc.h"
#include "cmds.h"
#include "install.h"
#include "extern.h"
